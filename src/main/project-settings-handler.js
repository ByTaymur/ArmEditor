
// ============================================================================
// PROJECT SETTINGS
// ============================================================================

let settingsWindow = null;

function openProjectSettings() {
    if (settingsWindow) {
        settingsWindow.focus();
        return;
    }

    settingsWindow = new BrowserWindow({
        width: 900,
        height: 700,
        parent: mainWindow,
        modal: false,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false
        },
        backgroundColor: '#1e1e1e',
        title: 'Project Settings'
    });

    settingsWindow.loadFile(path.join(__dirname, '../renderer/project-settings.html'));

    settingsWindow.on('closed', () => {
        settingsWindow = null;
    });

    // Load current project configuration
    settingsWindow.webContents.on('did-finish-load', () => {
        if (currentProjectPath) {
            projectManager = projectManager || new ProjectManager(currentProjectPath);
            const config = projectManager.config;
            settingsWindow.webContents.send('load-config', config);
        }
    });
}

ipcMain.on('open-project-settings', () => {
    openProjectSettings();
});

ipcMain.on('project-settings-apply', (event, config) => {
    if (!currentProjectPath) {
        console.error('[ProjectSettings] No project loaded');
        return;
    }

    try {
        projectManager = projectManager || new ProjectManager(currentProjectPath);

        // Validate configuration
        const validation = projectManager.validateConfig(config);
        if (!validation.valid) {
            mainWindow.webContents.send('output-append',
                `❌ Invalid project configuration:\n` +
                validation.errors.map(e => `   - ${e}\n`).join('')
            );
            return;
        }

        // Save configuration
        projectManager.config = config;
        projectManager.saveConfig();

        // Regenerate Makefile
        projectManager.saveMakefile();

        mainWindow.webContents.send('output-append', '✅ Project settings applied\n');
        mainWindow.webContents.send('output-append', '📝 Makefile regenerated\n');

    } catch (error) {
        console.error('[ProjectSettings] Apply error:', error);
        mainWindow.webContents.send('output-append', `❌ Settings error: ${error.message}\n`);
    }
});

ipcMain.on('project-settings-save', (event, config) => {
    if (!currentProjectPath) {
        console.error('[ProjectSettings] No project loaded');
        return;
    }

    try {
        projectManager = projectManager || new ProjectManager(currentProjectPath);

        // Validate configuration
        const validation = projectManager.validateConfig(config);
        if (!validation.valid) {
            mainWindow.webContents.send('output-append',
                `❌ Invalid project configuration:\n` +
                validation.errors.map(e => `   - ${e}\n`).join('')
            );
            event.reply('project-settings-error', validation.errors);
            return;
        }

        // Save configuration
        projectManager.config = config;
        projectManager.saveConfig();

        // Regenerate Makefile
        projectManager.saveMakefile();

        mainWindow.webContents.send('output-append', '✅ Project settings saved\n');
        mainWindow.webContents.send('output-append', '📝 Makefile regenerated from project.json\n');

        event.reply('project-settings-saved');

    } catch (error) {
        console.error('[ProjectSettings] Save error:', error);
        mainWindow.webContents.send('output-append', `❌ Settings save error: ${error.message}\n`);
        event.reply('project-settings-error', [error.message]);
    }
});
