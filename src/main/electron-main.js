/**
 * HopeIDE - Electron Main Process
 * Native Desktop Application
 */

const { app, BrowserWindow, ipcMain, dialog, Menu } = require('electron');
const path = require('path');
const fs = require('fs');
const { spawn } = require('child_process');

// Professional debugging tools
const GDBBackend = require('../debugger/gdb-backend');
const OpenOCDInterface = require('../debugger/openocd-interface');
const FlashManager = require('../debugger/flash-manager');
const STM32Tools = require('../stm32/stm32-tools');
// Debug instances
let gdbBackend = null;
const STM32CubeProgrammer = require('../programmer/stm32-cube-programmer');
const ProjectManager = require('../project/project-manager');
const TemplateManager = require('../project/template-manager');
let openocdInterface = null;
let flashManager = null;
let stm32Tools = null;
let projectManager = null;
let templateManager = null;
let debugSession = {
    active: false,
    breakpoints: new Map(),
    elfFile: null
};

/**
 * Create main window
 */
function createWindow() {
    mainWindow = new BrowserWindow({
        width: 1600,
        height: 1000,
        minWidth: 1200,
        minHeight: 800,
        title: 'HopeIDE - Professional ARM IDE',
        icon: path.join(__dirname, '../../resources/icon.png'),
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
            enableRemoteModule: true
        },
        backgroundColor: '#1e1e1e',
        show: false,
        frame: true,
        titleBarStyle: 'default'
    });

    // Load the NEW professional UI
    mainWindow.loadFile(path.join(__dirname, '../renderer/ide.html'));

    // Show when ready
    mainWindow.once('ready-to-show', () => {
        mainWindow.show();
        console.log('HopeIDE window ready');
    });

    // Open DevTools in development
    if (process.argv.includes('--dev')) {
        mainWindow.webContents.openDevTools();
    }

    // Create menu
    createMenu();

    mainWindow.on('closed', () => {
        mainWindow = null;
    });
}

/**
 * Create application menu
 */
function createMenu() {
    const template = [
        {
            label: 'File',
            submenu: [
                {
                    label: 'New File',
                    accelerator: 'CmdOrCtrl+N',
                    click: () => newFile()
                },
                {
                    label: 'Open File',
                    accelerator: 'CmdOrCtrl+O',
                    click: () => openFile()
                },
                {
                    label: 'Open Project Folder',
                    accelerator: 'CmdOrCtrl+Shift+O',
                    click: () => openProject()
                },
                { type: 'separator' },
                {
                    label: 'Save',
                    accelerator: 'CmdOrCtrl+S',
                    click: () => saveFile()
                },
                {
                    label: 'Save As',
                    accelerator: 'CmdOrCtrl+Shift+S',
                    click: () => saveFileAs()
                },
                { type: 'separator' },
                {
                    label: 'Exit',
                    accelerator: 'CmdOrCtrl+Q',
                    click: () => app.quit()
                }
            ]
        },
        {
            label: 'Edit',
            submenu: [
                { role: 'undo' },
                { role: 'redo' },
                { type: 'separator' },
                { role: 'cut' },
                { role: 'copy' },
                { role: 'paste' },
                { type: 'separator' },
                {
                    label: 'Find',
                    accelerator: 'CmdOrCtrl+F',
                    click: () => mainWindow.webContents.send('menu-find')
                },
                {
                    label: 'Replace',
                    accelerator: 'CmdOrCtrl+H',
                    click: () => mainWindow.webContents.send('menu-replace')
                }
            ]
        },
        {
            label: 'Build',
            submenu: [
                {
                    label: 'Build',
                    accelerator: 'F7',
                    click: () => buildProject()
                },
                {
                    label: 'Clean',
                    click: () => cleanProject()
                },
                {
                    label: 'Rebuild',
                    accelerator: 'Shift+F7',
                    click: () => rebuildProject()
                },
                { type: 'separator' },
                {
                    label: 'Flash to Device',
                    accelerator: 'CmdOrCtrl+F',
                    click: () => flashDevice()
                }
            ]
        },
        {
            label: 'Debug',
            submenu: [
                {
                    label: 'Start Debugging',
                    accelerator: 'F5',
                    click: () => startDebug()
                },
                {
                    label: 'Stop Debugging',
                    accelerator: 'Shift+F5',
                    click: () => stopDebug()
                },
                { type: 'separator' },
                {
                    label: 'Step Over',
                    accelerator: 'F10',
                    click: () => mainWindow.webContents.send('debug-step-over')
                },
                {
                    label: 'Step Into',
                    accelerator: 'F11',
                    click: () => mainWindow.webContents.send('debug-step-into')
                },
                {
                    label: 'Step Out',
                    accelerator: 'Shift+F11',
                    click: () => mainWindow.webContents.send('debug-step-out')
                }
            ]
        },
        {
            label: 'AI Tools',
            submenu: [
                {
                    label: 'Analyze Code',
                    accelerator: 'CmdOrCtrl+Shift+A',
                    click: () => analyzeCode()
                },
                {
                    label: 'Memory Analysis',
                    click: () => analyzeMemory()
                },
                {
                    label: 'Performance Analysis',
                    click: () => analyzePerformance()
                },
                { type: 'separator' },
                {
                    label: 'Import CubeMX Project',
                    click: () => importCubeMX()
                }
            ]
        },
        {
            label: 'Tools',
            submenu: [
                {
                    label: 'Terminal',
                    accelerator: 'Ctrl+`',
                    click: () => mainWindow.webContents.send('toggle-terminal')
                },
                {
                    label: 'Serial Monitor',
                    click: () => mainWindow.webContents.send('open-serial')
                },
                { type: 'separator' },
                {
                    label: 'Settings',
                    accelerator: 'CmdOrCtrl+,',
                    click: () => mainWindow.webContents.send('open-settings')
                }
            ]
        },
        {
            label: 'Help',
            submenu: [
                {
                    label: 'Documentation',
                    click: () => {
                        const docPath = path.join(__dirname, '../../HOW-TO-USE.md');
                        require('electron').shell.openPath(docPath);
                    }
                },
                {
                    label: 'Demo',
                    click: () => {
                        const demoPath = path.join(__dirname, '../../DEMO.md');
                        require('electron').shell.openPath(demoPath);
                    }
                },
                { type: 'separator' },
                {
                    label: 'About HopeIDE',
                    click: () => showAbout()
                },
                { type: 'separator' },
                {
                    label: 'Toggle DevTools',
                    accelerator: 'F12',
                    click: () => mainWindow.webContents.toggleDevTools()
                }
            ]
        }
    ];

    const menu = Menu.buildFromTemplate(template);
    Menu.setApplicationMenu(menu);
}

/**
 * File operations
 */
function newFile() {
    currentFilePath = null;
    mainWindow.webContents.send('new-file');
}

function openFile() {
    dialog.showOpenDialog(mainWindow, {
        properties: ['openFile'],
        filters: [
            { name: 'C/C++ Files', extensions: ['c', 'h', 'cpp', 'hpp'] },
            { name: 'Assembly', extensions: ['s', 'S', 'asm'] },
            { name: 'All Files', extensions: ['*'] }
        ]
    }).then(result => {
        if (!result.canceled && result.filePaths.length > 0) {
            const filePath = result.filePaths[0];

            // Check if it's a file, not a directory
            const stats = fs.statSync(filePath);
            if (!stats.isFile()) {
                dialog.showErrorBox('Error', 'Please select a file, not a directory');
                return;
            }

            const content = fs.readFileSync(filePath, 'utf-8');
            currentFilePath = filePath;
            mainWindow.webContents.send('open-file', {
                path: filePath,
                content: content,
                name: path.basename(filePath)
            });
        }
    });
}

function openProject() {
    dialog.showOpenDialog(mainWindow, {
        properties: ['openDirectory']
    }).then(result => {
        if (!result.canceled && result.filePaths.length > 0) {
            currentProjectPath = result.filePaths[0];

            // Parse project structure
            const projectInfo = parseProjectStructure(currentProjectPath);

            mainWindow.webContents.send('project-opened', projectInfo);
            mainWindow.webContents.send('output-append',
                `✅ Project loaded: ${path.basename(currentProjectPath)}\n` +
                `   Files: ${projectInfo.files.length}\n` +
                `   Type: ${projectInfo.type}\n`
            );
        }
    });
}

/**
 * Auto-setup STM32CubeMX project with optimized Makefile
 */
function setupCubeMXProject(projectPath) {
    const makefilePath = path.join(projectPath, 'Makefile');
    const makefileCubemxPath = path.join(projectPath, 'Makefile.cubemx');

    // Skip if already set up
    if (fs.existsSync(makefileCubemxPath)) {
        return;
    }

    // If Makefile exists, rename it to Makefile.cubemx
    if (fs.existsSync(makefilePath)) {
        try {
            // Backup original
            if (!fs.existsSync(path.join(projectPath, 'Makefile.original'))) {
                fs.copyFileSync(makefilePath, path.join(projectPath, 'Makefile.original'));
            }

            // Rename to Makefile.cubemx
            fs.renameSync(makefilePath, makefileCubemxPath);

            // Copy template
            const templatePath = path.join(__dirname, '../../resources/Makefile.template');
            if (fs.existsSync(templatePath)) {
                fs.copyFileSync(templatePath, makefilePath);

                mainWindow.webContents.send('output-append',
                    '🚀 Auto-setup complete!\n' +
                    '   ✅ Makefile.cubemx created (original CubeMX Makefile)\n' +
                    '   ✅ Makefile created with build profiles\n' +
                    '   📊 Available profiles: debug, release, O0, Og, O2, O3, Os\n' +
                    '   ⚡ Auto-detected MCU family and OpenOCD target\n'
                );
            }
        } catch (err) {
            console.error('Auto-setup error:', err);
        }
    }
}

function parseProjectStructure(projectPath) {
    const files = [];
    const info = {
        path: projectPath,
        name: path.basename(projectPath),
        type: 'unknown',
        files: [],
        folders: null,
        iocFile: null,
        makefile: null
    };

    // Check for CubeMX project (.ioc file)
    const iocFiles = fs.readdirSync(projectPath).filter(f => f.endsWith('.ioc'));
    if (iocFiles.length > 0) {
        info.type = 'STM32CubeMX';
        info.iocFile = path.join(projectPath, iocFiles[0]);

        // Auto-setup CubeMX project
        setupCubeMXProject(projectPath);
    }

    // Check for Makefile
    const makefilePath = path.join(projectPath, 'Makefile');
    if (fs.existsSync(makefilePath)) {
        info.makefile = makefilePath;
        if (info.type === 'unknown') info.type = 'Makefile';
    }

    // Recursively find all source files (flat list for compatibility)
    function scanDirectory(dir, baseDir = dir) {
        const items = fs.readdirSync(dir);

        for (const item of items) {
            const fullPath = path.join(dir, item);
            const stats = fs.statSync(fullPath);

            if (stats.isDirectory()) {
                // Skip build directories
                if (!['build', 'Build', 'Debug', 'Release', '.git', 'node_modules'].includes(item)) {
                    scanDirectory(fullPath, baseDir);
                }
            } else if (stats.isFile()) {
                const ext = path.extname(item).toLowerCase();
                if (['.c', '.h', '.cpp', '.hpp', '.s', '.asm'].includes(ext)) {
                    files.push({
                        name: item,
                        path: fullPath,
                        relativePath: path.relative(baseDir, fullPath),
                        type: ext
                    });
                }
            }
        }
    }

    // Build hierarchical folder structure
    function buildFolderTree(dirPath, baseDir = dirPath) {
        const items = fs.readdirSync(dirPath);
        const tree = {
            name: path.basename(dirPath),
            path: dirPath,
            type: 'folder',
            children: []
        };

        for (const item of items) {
            const fullPath = path.join(dirPath, item);
            const stats = fs.statSync(fullPath);

            if (stats.isDirectory()) {
                // Skip build directories
                if (!['build', 'Build', 'Debug', 'Release', '.git', 'node_modules'].includes(item)) {
                    tree.children.push(buildFolderTree(fullPath, baseDir));
                }
            } else if (stats.isFile()) {
                const ext = path.extname(item).toLowerCase();
                if (['.c', '.h', '.cpp', '.hpp', '.s', '.asm', '.ioc', '.ld'].includes(ext)) {
                    tree.children.push({
                        name: item,
                        path: fullPath,
                        relativePath: path.relative(baseDir, fullPath),
                        type: 'file',
                        ext: ext
                    });
                }
            }
        }

        // Sort: folders first, then files
        tree.children.sort((a, b) => {
            if (a.type === 'folder' && b.type === 'file') return -1;
            if (a.type === 'file' && b.type === 'folder') return 1;
            return a.name.localeCompare(b.name);
        });

        return tree;
    }

    scanDirectory(projectPath);
    info.files = files;

    // Build hierarchical tree
    info.folders = buildFolderTree(projectPath);

    return info;
}

function saveFile() {
    if (!currentFilePath) {
        saveFileAs();
        return;
    }

    mainWindow.webContents.send('get-editor-content', 'save');
}

function saveFileAs() {
    dialog.showSaveDialog(mainWindow, {
        filters: [
            { name: 'C Files', extensions: ['c'] },
            { name: 'Header Files', extensions: ['h'] },
            { name: 'All Files', extensions: ['*'] }
        ]
    }).then(result => {
        if (!result.canceled) {
            currentFilePath = result.filePath;
            mainWindow.webContents.send('get-editor-content', 'save-as');
        }
    });
}

/**
 * Build operations
 */
async function buildProject(autoFlash = false) {
    if (!currentProjectPath) {
        dialog.showErrorBox('Error', 'No project opened');
        return;
    }

    mainWindow.webContents.send('output-clear');
    mainWindow.webContents.send('output-append', '🔨 Building project...\n');

    // Check if Makefile exists
    const makefilePath = path.join(currentProjectPath, 'Makefile');
    if (!fs.existsSync(makefilePath)) {
        // Try to generate Makefile automatically
        mainWindow.webContents.send('output-append', `📝 No Makefile found, attempting to generate...\n`);

        try {
            const MakefileGenerator = require('../build/makefile-generator');
            const generator = new MakefileGenerator(currentProjectPath);
            const result = await generator.generate();

            if (result.success) {
                mainWindow.webContents.send('output-append',
                    `✅ Makefile generated! (${result.sources || 0} sources, ${result.includes || 0} includes)\n`
                );
            } else {
                mainWindow.webContents.send('output-append',
                    `❌ Could not generate Makefile.\n` +
                    `   Please create it manually or use STM32CubeMX.\n`
                );
                return;
            }
        } catch (err) {
            mainWindow.webContents.send('output-append', `❌ Makefile generation failed: ${err.message}\n`);
            return;
        }
    }

    // First check available targets in Makefile
    const makefileContent = fs.readFileSync(makefilePath, 'utf8');
    let buildTarget = 'all';

    // Check if 'all' target exists, if not try other common targets
    if (!makefileContent.includes('all:')) {
        if (makefileContent.includes('build:')) {
            buildTarget = 'build';
        } else if (makefileContent.match(/^[\w-]+\.elf:/m)) {
            // Extract .elf target name
            const match = makefileContent.match(/^([\w-]+)\.elf:/m);
            if (match) {
                buildTarget = match[1] + '.elf';
                mainWindow.webContents.send('output-append', `📝 Using target: ${buildTarget}\n`);
            }
        }
    }

    const make = spawn('make', [buildTarget], {
        cwd: currentProjectPath,
        shell: true
    });

    make.stdout.on('data', (data) => {
        mainWindow.webContents.send('output-append', data.toString());
    });

    make.stderr.on('data', (data) => {
        mainWindow.webContents.send('output-append', data.toString());
    });

    make.on('close', async (code) => {
        if (code === 0) {
            mainWindow.webContents.send('output-append', '\n✅ Build successful!\n');

            // Auto-flash if requested and device is connected
            if (autoFlash && connectedStLink && connectedStLink.openocd) {
                mainWindow.webContents.send('output-append', '\n⚡ Auto-flashing firmware...\n');

                try {
                    // Find built firmware (check build directory)
                    const buildDir = path.join(currentProjectPath, 'build');
                    let firmwareFile = null;

                    if (fs.existsSync(buildDir)) {
                        const files = fs.readdirSync(buildDir);

                        // Prefer .hex, then .bin, then .elf
                        firmwareFile = files.find(f => f.endsWith('.hex')) ||
                            files.find(f => f.endsWith('.bin')) ||
                            files.find(f => f.endsWith('.elf'));

                        if (firmwareFile) {
                            firmwareFile = path.join(buildDir, firmwareFile);
                        }
                    }

                    if (firmwareFile && fs.existsSync(firmwareFile)) {
                        mainWindow.webContents.send('output-append', `📁 Found firmware: ${path.basename(firmwareFile)}\n`);

                        const flashManager = new FlashManager(connectedStLink.openocd);
                        await flashManager.flash(firmwareFile, {
                            verify: true,
                            reset: true,
                            erase: true
                        });

                        mainWindow.webContents.send('output-append', '✅ Firmware flashed successfully!\n');
                        mainWindow.webContents.send('flash-progress', 100);
                    } else {
                        mainWindow.webContents.send('output-append', '⚠️ Could not find firmware file (.hex/.bin/.elf)\n');
                    }
                } catch (flashErr) {
                    mainWindow.webContents.send('output-append', `❌ Flash failed: ${flashErr.message}\n`);
                    mainWindow.webContents.send('flash-progress', 0);
                }
            }
        } else {
            mainWindow.webContents.send('output-append', `\n❌ Build failed (exit code: ${code})\n`);
        }
    });
}

function cleanProject() {
    if (!currentProjectPath) {
        dialog.showErrorBox('Error', 'No project opened');
        return;
    }

    const make = spawn('make', ['clean'], {
        cwd: currentProjectPath,
        shell: true
    });

    make.on('close', (code) => {
        mainWindow.webContents.send('output-append', '🧹 Clean complete\n');
    });
}

function rebuildProject() {
    cleanProject();
    setTimeout(() => buildProject(), 1000);
}

function flashDevice() {
    if (!currentProjectPath) {
        dialog.showErrorBox('Error', 'No project opened');
        return;
    }

    mainWindow.webContents.send('output-append', '\n⚡ Flashing device...\n');

    const make = spawn('make', ['flash'], {
        cwd: currentProjectPath,
        shell: true
    });

    make.stdout.on('data', (data) => {
        mainWindow.webContents.send('output-append', data.toString());
    });

    make.stderr.on('data', (data) => {
        mainWindow.webContents.send('output-append', data.toString());
    });

    make.on('close', (code) => {
        if (code === 0) {
            mainWindow.webContents.send('output-append', '\n✅ Flash successful!\n');
        } else {
            mainWindow.webContents.send('output-append', `\n❌ Flash failed\n`);
        }
    });
}

/**
 * Debug operations
 */
function startDebug() {
    mainWindow.webContents.send('output-append', '\n🔍 Starting debugger...\n');
    // Implement GDB launch
}

function stopDebug() {
    mainWindow.webContents.send('output-append', '\n⏹️ Debugger stopped\n');
}

/**
 * AI Tools
 */
function analyzeCode() {
    if (!currentFilePath) {
        dialog.showErrorBox('Error', 'No file opened');
        return;
    }

    mainWindow.webContents.send('output-append', '\n🤖 AI Code Analysis...\n');

    const aiScript = path.join(__dirname, '../ai/code-assistant.js');
    const analysis = spawn('node', [aiScript, currentFilePath]);

    analysis.stdout.on('data', (data) => {
        mainWindow.webContents.send('output-append', data.toString());
    });

    analysis.on('close', () => {
        mainWindow.webContents.send('output-append', '\n✅ Analysis complete\n');
    });
}

function analyzeMemory() {
    // Find .elf file
    if (!currentProjectPath) {
        dialog.showErrorBox('Error', 'No project opened');
        return;
    }

    const elfFiles = findFiles(currentProjectPath, '.elf');
    if (elfFiles.length === 0) {
        dialog.showErrorBox('Error', 'No .elf file found. Build first!');
        return;
    }

    mainWindow.webContents.send('output-append', '\n💾 Memory Analysis...\n');

    const memScript = path.join(__dirname, '../ai/memory-analyzer.js');
    const analysis = spawn('node', [memScript, elfFiles[0]]);

    analysis.stdout.on('data', (data) => {
        mainWindow.webContents.send('output-append', data.toString());
    });
}

function analyzePerformance() {
    if (!currentProjectPath) {
        dialog.showErrorBox('Error', 'No project opened');
        return;
    }

    const elfFiles = findFiles(currentProjectPath, '.elf');
    if (elfFiles.length === 0) {
        dialog.showErrorBox('Error', 'No .elf file found. Build first!');
        return;
    }

    mainWindow.webContents.send('output-append', '\n⚡ Performance Analysis...\n');

    const perfScript = path.join(__dirname, '../ai/performance-profiler.js');
    const analysis = spawn('node', [perfScript, elfFiles[0]]);

    analysis.stdout.on('data', (data) => {
        mainWindow.webContents.send('output-append', data.toString());
    });
}

function importCubeMX() {
    dialog.showOpenDialog(mainWindow, {
        properties: ['openDirectory'],
        title: 'Select CubeMX Project Folder'
    }).then(result => {
        if (!result.canceled && result.filePaths.length > 0) {
            const projectPath = result.filePaths[0];

            mainWindow.webContents.send('output-append', '\n📦 Importing CubeMX project...\n');

            const importScript = path.join(__dirname, '../advanced/cubemx-importer.js');
            const importer = spawn('node', [importScript, projectPath]);

            importer.stdout.on('data', (data) => {
                mainWindow.webContents.send('output-append', data.toString());
            });

            importer.on('close', () => {
                mainWindow.webContents.send('output-append', '\n✅ Import complete\n');
                currentProjectPath = projectPath;
                mainWindow.webContents.send('open-project', { path: projectPath });
            });
        }
    });
}

/**
 * Utility functions
 */
function findFiles(dir, ext, fileList = []) {
    const files = fs.readdirSync(dir);

    files.forEach(file => {
        const filePath = path.join(dir, file);
        const stat = fs.statSync(filePath);

        if (stat.isDirectory()) {
            findFiles(filePath, ext, fileList);
        } else if (file.endsWith(ext)) {
            fileList.push(filePath);
        }
    });

    return fileList;
}

function showAbout() {
    dialog.showMessageBox(mainWindow, {
        type: 'info',
        title: 'About HopeIDE',
        message: 'HopeIDE (Umut IDE) v1.0.0',
        detail: 'Professional ARM Development IDE\n\n' +
            'Features:\n' +
            '• AI Code Assistant\n' +
            '• Memory Analyzer\n' +
            '• Performance Profiler\n' +
            '• STM32CubeMX Import\n' +
            '• Real-time Debugging\n\n' +
            'Better than Keil/IAR, completely free!\n\n' +
            'Built with Electron + Monaco Editor\n' +
            'License: MIT'
    });
}

/**
 * IPC Handlers
 */
ipcMain.on('save-file-content', (event, content) => {
    if (currentFilePath) {
        fs.writeFileSync(currentFilePath, content, 'utf-8');
        mainWindow.webContents.send('file-saved', currentFilePath);
    }
});

ipcMain.on('save-file-as-content', (event, content) => {
    if (currentFilePath) {
        fs.writeFileSync(currentFilePath, content, 'utf-8');
        mainWindow.webContents.send('file-saved', currentFilePath);
    }
});

// New save-file handler for tab system
ipcMain.on('save-file', (event, data) => {
    try {
        fs.writeFileSync(data.path, data.content, 'utf-8');
        mainWindow.webContents.send('output-append', `💾 Saved: ${path.basename(data.path)}\n`);
    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Save failed: ${error.message}\n`);
    }
});

ipcMain.on('open-file-from-project', (event, filePath) => {
    try {
        const stats = fs.statSync(filePath);
        if (!stats.isFile()) {
            return;
        }

        const content = fs.readFileSync(filePath, 'utf-8');
        currentFilePath = filePath;
        mainWindow.webContents.send('open-file', {
            path: filePath,
            content: content,
            name: path.basename(filePath)
        });
    } catch (error) {
        dialog.showErrorBox('Error', `Failed to open file: ${error.message}`);
    }
});

/**
 * Professional Debug & Flash Operations
 */

// Start debug session
ipcMain.on('debug-start', async (event) => {
    try {
        if (!currentProjectPath) {
            mainWindow.webContents.send('output-append', '❌ No project opened\n');
            return;
        }

        // Find ELF file
        const buildDir = path.join(currentProjectPath, 'build');
        const elfFiles = fs.readdirSync(buildDir).filter(f => f.endsWith('.elf'));

        if (elfFiles.length === 0) {
            mainWindow.webContents.send('output-append', '❌ No ELF file found. Build project first.\n');
            return;
        }

        debugSession.elfFile = path.join(buildDir, elfFiles[0]);

        mainWindow.webContents.send('output-append', '🔌 Starting debug session...\n');

        // Start OpenOCD
        openocdInterface = new OpenOCDInterface();
        await openocdInterface.start('stm32f4x', 'stlink');

        mainWindow.webContents.send('output-append', '✅ OpenOCD started\n');

        // Connect OpenOCD TCL
        await openocdInterface.connectTCL();

        // Start GDB
        gdbBackend = new GDBBackend();
        await gdbBackend.start(debugSession.elfFile);

        mainWindow.webContents.send('output-append', '✅ GDB started\n');

        // Connect GDB to OpenOCD
        await gdbBackend.connectOpenOCD();

        mainWindow.webContents.send('output-append', '✅ Connected to target\n');

        // Load program
        await gdbBackend.load();

        mainWindow.webContents.send('output-append', '✅ Program loaded\n');

        // Initialize tools
        flashManager = new FlashManager(openocdInterface);
        stm32Tools = new STM32Tools(openocdInterface);

        // Get device info
        const deviceInfo = await stm32Tools.getDeviceInfo();
        mainWindow.webContents.send('output-append',
            `📱 Device: ${deviceInfo.deviceName}\n` +
            `   ID: ${deviceInfo.deviceID} Rev: ${deviceInfo.revisionID}\n` +
            `   UID: ${deviceInfo.uidString}\n` +
            `   Flash: ${deviceInfo.flash.sizeKB}\n`
        );

        debugSession.active = true;
        mainWindow.webContents.send('debug-started');

        // Read initial registers
        const registers = await gdbBackend.readRegisters();
        mainWindow.webContents.send('registers-updated', registers);

    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Debug start failed: ${error.message}\n`);
    }
});

// Stop debug session
ipcMain.on('debug-stop', async (event) => {
    try {
        if (gdbBackend) {
            await gdbBackend.quit();
            gdbBackend = null;
        }

        if (openocdInterface) {
            await openocdInterface.stop();
            openocdInterface = null;
        }

        debugSession.active = false;
        debugSession.breakpoints.clear();

        mainWindow.webContents.send('output-append', '🛑 Debug session stopped\n');
        mainWindow.webContents.send('debug-stopped');
    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Error stopping debug: ${error.message}\n`);
    }
});

// Flash program
ipcMain.on('flash-program', async (event, filePath) => {
    console.log('[IPC] flash-program received, filePath:', filePath);
    try {
        if (!filePath && debugSession.elfFile) {
            filePath = debugSession.elfFile.replace('.elf', '.hex');
        }

        if (!filePath) {
            console.log('[Flash] No file specified');
            mainWindow.webContents.send('output-append', '❌ No file to flash\n');
            return;
        }

        console.log('[Flash] Starting flash:', filePath);
        mainWindow.webContents.send('output-append', `⚡ Flashing ${path.basename(filePath)}...\n`);

        // Ensure OpenOCD is running
        if (!openocdInterface) {
            mainWindow.webContents.send('output-append', '   Starting OpenOCD for flashing...\n');
            openocdInterface = new OpenOCDInterface();

            // Listen to output
            openocdInterface.on('output', (data) => {
                console.log('[OpenOCD Flash]', data);
            });

            // Try to detect or use default
            try {
                // Use st-info to get chip ID if possible
                const { execSync } = require('child_process');
                try {
                    const output = execSync('st-info --probe', { stdio: 'pipe' }).toString();
                    const chipIdMatch = output.match(/chipid:\s*(0x[0-9a-fA-F]+)/);
                    if (chipIdMatch) {
                        const mcuType = detectMCUType(chipIdMatch[1]) || 'stm32f4x';
                        console.log('[Flash] Auto-detected MCU for flash:', mcuType);
                        await openocdInterface.start(mcuType, 'stlink');
                    } else {
                        throw new Error('No chip ID');
                    }
                } catch (e) {
                    console.log('[Flash] st-info failed, using default F4 config');
                    await openocdInterface.start('stm32f4x', 'stlink');
                }
            } catch (err) {
                console.error('[Flash] OpenOCD start error:', err);
                await openocdInterface.start('stm32f4x', 'stlink');
            }

            await openocdInterface.connectTCL();
        }

        flashManager = flashManager || new FlashManager(openocdInterface);

        mainWindow.webContents.send('output-append', '   Programming flash memory...\n');
        const result = await flashManager.programAndRun(filePath, true, true);

        if (result.success) {
            mainWindow.webContents.send('output-append', '✅ Flash successful!\n');
            for (const step of result.steps) {
                mainWindow.webContents.send('output-append', `   ${step}\n`);
            }
        } else {
            console.error('[Flash] Failed:', result.error);
            mainWindow.webContents.send('output-append', `❌ Flash failed: ${result.error}\n`);

            // If failed, maybe connection was lost. Try to restart OpenOCD next time.
            try {
                await openocdInterface.stop();
            } catch (e) { }
            openocdInterface = null;
        }

    } catch (error) {
        console.error('[Flash] OpenOCD flash failed:', error);
        mainWindow.webContents.send('output-append', `⚠️  OpenOCD flash failed: ${error.message}\n`);

        // TRY FALLBACK: STM32CubeProgrammer
        try {
            mainWindow.webContents.send('output-append', `\n🔄 Trying STM32CubeProgrammer fallback...\n`);

            const cubeProg = new STM32CubeProgrammer();

            if (!cubeProg.isInstalled()) {
                mainWindow.webContents.send('output-append',
                    `❌ STM32CubeProgrammer not installed\n` +
                    `   Run: ./install-cubeprog.sh to install\n`
                );
                return;
            }

            mainWindow.webContents.send('output-append',
                `✅ Found CubeProgrammer v${cubeProg.getVersion()}\n`
            );

            // Listen to output
            cubeProg.on('output', (data) => {
                mainWindow.webContents.send('output-append', data);
            });

            // Convert .hex to .bin if needed (CubeProgrammer prefers .bin)
            let flashFile = filePath;
            if (filePath.endsWith('.hex')) {
                // For now, try .hex directly, CubeProgrammer supports it
                mainWindow.webContents.send('output-append', `📝 Flashing HEX file: ${path.basename(filePath)}\n`);
            }

            // Flash with CubeProgrammer
            await cubeProg.flashBinary(flashFile, 0x08000000, 0);

            mainWindow.webContents.send('output-append', `\n✅ Flash successful via CubeProgrammer!\n`);

        } catch (fallbackError) {
            console.error('[Flash] CubeProgrammer fallback also failed:', fallbackError);
            mainWindow.webContents.send('output-append',
                `\n❌ All flash methods failed!\n` +
                `   Last error: ${fallbackError.message}\n` +
                `\n📌 Troubleshooting:\n` +
                `   1. Check target voltage (should be 3.0-3.6V)\n` +
                `   2. Verify ST-Link connections\n` +
                `   3. Try power-cycling the target\n` +
                `   4. Install STM32CubeProgrammer: ./install-cubeprog.sh\n`
            );
        }

        // Clean up OpenOCD
        try {
            if (openocdInterface) await openocdInterface.stop();
        } catch (e) { }
        openocdInterface = null;
    }
});

// Debug controls
ipcMain.on('debug-continue', async () => {
    if (gdbBackend) {
        await gdbBackend.continue();
        mainWindow.webContents.send('output-append', '▶️  Continue\n');
    }
});

ipcMain.on('debug-step-over', async () => {
    if (gdbBackend) {
        await gdbBackend.stepOver();
        const registers = await gdbBackend.readRegisters();
        mainWindow.webContents.send('registers-updated', registers);
    }
});

ipcMain.on('debug-step-into', async () => {
    if (gdbBackend) {
        await gdbBackend.stepInto();
        const registers = await gdbBackend.readRegisters();
        mainWindow.webContents.send('registers-updated', registers);
    }
});

ipcMain.on('debug-step-out', async () => {
    if (gdbBackend) {
        await gdbBackend.stepOut();
        const registers = await gdbBackend.readRegisters();
        mainWindow.webContents.send('registers-updated', registers);
    }
});

ipcMain.on('debug-pause', async () => {
    if (gdbBackend) {
        await gdbBackend.pause();
        mainWindow.webContents.send('output-append', '⏸️  Paused\n');
    }
});

// Breakpoints
ipcMain.on('breakpoint-toggle', async (event, { file, line }) => {
    if (!gdbBackend) return;

    const key = `${file}:${line}`;

    if (debugSession.breakpoints.has(key)) {
        const bpNum = debugSession.breakpoints.get(key);
        await gdbBackend.deleteBreakpoint(bpNum);
        debugSession.breakpoints.delete(key);
        mainWindow.webContents.send('output-append', `🔴 Breakpoint removed: ${key}\n`);
    } else {
        const bpNum = await gdbBackend.setBreakpoint(file, line);
        debugSession.breakpoints.set(key, bpNum);
        mainWindow.webContents.send('output-append', `🔴 Breakpoint set: ${key}\n`);
    }
});

// Read memory
ipcMain.on('memory-read', async (event, address) => {
    if (!gdbBackend) return;

    try {
        const memory = await gdbBackend.readMemory(address, 256);
        mainWindow.webContents.send('memory-data', memory);
    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Memory read error: ${error.message}\n`);
    }
});

// Read registers
ipcMain.on('registers-read', async () => {
    if (!gdbBackend) return;

    try {
        const registers = await gdbBackend.readRegisters();
        mainWindow.webContents.send('registers-updated', registers);
    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Register read error: ${error.message}\n`);
    }
});

// Build/Clean/Rebuild from toolbar
ipcMain.on('build-project', (event, autoFlash = false) => {
    console.log('[IPC] build-project received, autoFlash:', autoFlash);
    buildProject(autoFlash);
});

ipcMain.on('clean-project', () => {
    console.log('[IPC] clean-project received');
    cleanProject();
});

ipcMain.on('rebuild-project', () => {
    console.log('[IPC] rebuild-project received');
    rebuildProject();
});

// New File
ipcMain.on('new-file', (event, fileName) => {
    if (!currentProjectPath) {
        // Create standalone file
        dialog.showSaveDialog(mainWindow, {
            defaultPath: fileName,
            filters: [
                { name: 'C Files', extensions: ['c'] },
                { name: 'Header Files', extensions: ['h'] },
                { name: 'All Files', extensions: ['*'] }
            ]
        }).then(result => {
            if (!result.canceled) {
                const template = getFileTemplate(path.extname(fileName));
                fs.writeFileSync(result.filePath, template);

                mainWindow.webContents.send('open-file', {
                    path: result.filePath,
                    content: template,
                    name: path.basename(result.filePath)
                });

                currentFilePath = result.filePath;
            }
        });
    } else {
        // Create in project
        const filePath = path.join(currentProjectPath, fileName);
        const template = getFileTemplate(path.extname(fileName));
        fs.writeFileSync(filePath, template);

        mainWindow.webContents.send('open-file', {
            path: filePath,
            content: template,
            name: fileName
        });

        currentFilePath = filePath;
        mainWindow.webContents.send('output-append', `✅ Created: ${fileName}\n`);
    }
});

// New Project
ipcMain.on('new-project', (event, projectName) => {
    dialog.showOpenDialog(mainWindow, {
        properties: ['openDirectory'],
        title: 'Select folder for new project'
    }).then(result => {
        if (!result.canceled && result.filePaths.length > 0) {
            const projectPath = path.join(result.filePaths[0], projectName);

            // Create project structure
            fs.mkdirSync(projectPath, { recursive: true });
            fs.mkdirSync(path.join(projectPath, 'src'));
            fs.mkdirSync(path.join(projectPath, 'inc'));
            fs.mkdirSync(path.join(projectPath, 'build'));

            // Create main.c
            const mainC = `/**
 * Project: ${projectName}
 * File: main.c
 */

#include <stdint.h>

int main(void) {
    // Initialize

    while(1) {
        // Main loop
    }

    return 0;
}
`;
            fs.writeFileSync(path.join(projectPath, 'src', 'main.c'), mainC);

            // Create Makefile
            const makefile = `# Makefile for ${projectName}

PROJECT = ${projectName}

# Source files
SRCS = src/main.c

# Includes
INCS = -Iinc

# Compiler
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Flags
CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -O2 -g -Wall \$(INCS)
LDFLAGS = -T STM32F407VGTx_FLASH.ld

# Build directory
BUILD_DIR = build

# Objects
OBJS = \$(SRCS:%.c=\$(BUILD_DIR)/%.o)

all: \$(BUILD_DIR)/\$(PROJECT).elf \$(BUILD_DIR)/\$(PROJECT).hex \$(BUILD_DIR)/\$(PROJECT).bin
\t@echo "Build complete!"
\t@\$(SIZE) \$(BUILD_DIR)/\$(PROJECT).elf

\$(BUILD_DIR)/\$(PROJECT).elf: \$(OBJS)
\t@echo "Linking..."
\t@\$(CC) \$(CFLAGS) \$(LDFLAGS) \$^ -o \$@

\$(BUILD_DIR)/%.o: %.c
\t@mkdir -p \$(dir \$@)
\t@echo "Compiling \$<"
\t@\$(CC) \$(CFLAGS) -c \$< -o \$@

\$(BUILD_DIR)/%.hex: \$(BUILD_DIR)/%.elf
\t@\$(OBJCOPY) -O ihex \$< \$@

\$(BUILD_DIR)/%.bin: \$(BUILD_DIR)/%.elf
\t@\$(OBJCOPY) -O binary \$< \$@

clean:
\t@rm -rf \$(BUILD_DIR)
\t@echo "Cleaned!"

flash: all
\t@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program \$(BUILD_DIR)/\$(PROJECT).elf verify reset exit"

.PHONY: all clean flash
`;
            fs.writeFileSync(path.join(projectPath, 'Makefile'), makefile);

            currentProjectPath = projectPath;

            // Open project
            const projectInfo = parseProjectStructure(projectPath);
            mainWindow.webContents.send('open-project', projectInfo);
            mainWindow.webContents.send('output-append',
                `✅ Project created: ${projectName}\n` +
                `   Path: ${projectPath}\n`
            );

            // Open main.c
            mainWindow.webContents.send('open-file', {
                path: path.join(projectPath, 'src', 'main.c'),
                content: mainC,
                name: 'main.c'
            });
        }
    });
});

function getFileTemplate(ext) {
    switch (ext) {
        case '.c':
            return `/**
 * File: ${path.basename(currentFilePath || 'main.c')}
 */

#include <stdint.h>

int main(void) {
    // Your code here

    return 0;
}
`;
        case '.h':
            const guard = `_${path.basename(currentFilePath || 'HEADER').toUpperCase().replace('.', '_')}_`;
            return `/**
 * File: ${path.basename(currentFilePath || 'header.h')}
 */

#ifndef ${guard}
#define ${guard}

// Declarations here

#endif /* ${guard} */
`;
        default:
            return '';
    }
}

/**
 * NEW SIMPLIFIED IPC HANDLERS
 */

// Open project dialog
ipcMain.on('open-project-dialog', () => {
    dialog.showOpenDialog(mainWindow, {
        properties: ['openDirectory'],
        title: 'Open Project Folder'
    }).then(result => {
        if (!result.canceled && result.filePaths.length > 0) {
            const projectPath = result.filePaths[0];
            currentProjectPath = projectPath;

            // Parse project
            const projectInfo = parseProjectStructure(projectPath);

            // Send to renderer
            mainWindow.webContents.send('project-opened', projectInfo);
        }
    });
});

// Read file
ipcMain.on('read-file', (event, filePath) => {
    try {
        const content = fs.readFileSync(filePath, 'utf-8');
        const fileName = path.basename(filePath);

        mainWindow.webContents.send('file-content', {
            path: filePath,
            name: fileName,
            content: content
        });
    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Error reading file: ${error.message}\n`);
    }
});

// Save file (new simple version)
ipcMain.on('save-file', (event, filePath, content) => {
    try {
        fs.writeFileSync(filePath, content, 'utf-8');
        console.log('[Save] File saved:', filePath);
    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Save error: ${error.message}\n`);
    }
});

/**
 * ST-LINK DETECTION AND MANAGEMENT
 */
let stlinkDevices = [];
let connectedStLink = null;

// Scan for ST-Link devices
ipcMain.on('scan-stlinks', async (event) => {
    try {
        // Use lsusb to detect ST-Link devices
        const { execSync } = require('child_process');
        const lsusbOutput = execSync('lsusb').toString();

        const devices = [];
        const lines = lsusbOutput.split('\n');

        for (const line of lines) {
            // ST-Link V2: 0483:3748
            // ST-Link V2-1: 0483:374b, 0483:3752
            // ST-Link V3: 0483:374d, 0483:374e, 0483:374f, 0483:3753, 0483:3754, 0483:3755, 0483:3756
            if (line.includes('0483:3748')) {
                devices.push({
                    id: 'stlink-v2-' + devices.length,
                    name: 'ST-Link V2',
                    usbId: '0483:3748',
                    version: 'V2',
                    connected: connectedStLink && connectedStLink.id === 'stlink-v2-' + devices.length,
                    mcu: connectedStLink && connectedStLink.id === 'stlink-v2-' + devices.length ? connectedStLink.mcu : null
                });
            } else if (line.includes('0483:374b') || line.includes('0483:3752')) {
                devices.push({
                    id: 'stlink-v2.1-' + devices.length,
                    name: 'ST-Link V2-1',
                    usbId: line.includes('0483:374b') ? '0483:374b' : '0483:3752',
                    version: 'V2-1',
                    connected: connectedStLink && connectedStLink.id === 'stlink-v2.1-' + devices.length,
                    mcu: connectedStLink && connectedStLink.id === 'stlink-v2.1-' + devices.length ? connectedStLink.mcu : null
                });
            } else if (line.includes('0483:3754') || line.includes('0483:374d') || line.includes('0483:374e') || line.includes('0483:374f') || line.includes('0483:3753') || line.includes('0483:3755') || line.includes('0483:3756')) {
                const usbId = line.match(/0483:[0-9a-f]{4}/i)[0];
                devices.push({
                    id: 'stlink-v3-' + devices.length,
                    name: 'ST-Link V3',
                    usbId: usbId,
                    version: 'V3',
                    connected: connectedStLink && connectedStLink.id === 'stlink-v3-' + devices.length,
                    mcu: connectedStLink && connectedStLink.id === 'stlink-v3-' + devices.length ? connectedStLink.mcu : null
                });
            }
        }

        stlinkDevices = devices;
        mainWindow.webContents.send('stlink-devices', devices);

    } catch (error) {
        console.error('Error scanning ST-Links:', error);
        mainWindow.webContents.send('stlink-devices', []);
    }
});

// Auto-detect MCU from DEVICE_ID
function detectMCUType(deviceId) {
    const mcuMap = {
        // STM32F0
        '0x440': 'stm32f0x', '0x444': 'stm32f0x', '0x445': 'stm32f0x', '0x448': 'stm32f0x',
        // STM32F1
        '0x412': 'stm32f1x', '0x410': 'stm32f1x', '0x414': 'stm32f1x', '0x418': 'stm32f1x', '0x430': 'stm32f1x',
        // STM32F2
        '0x411': 'stm32f2x',
        // STM32F3
        '0x422': 'stm32f3x', '0x432': 'stm32f3x', '0x438': 'stm32f3x', '0x439': 'stm32f3x', '0x446': 'stm32f3x',
        // STM32F4
        '0x413': 'stm32f4x', '0x419': 'stm32f4x', '0x423': 'stm32f4x', '0x433': 'stm32f4x', '0x458': 'stm32f4x', '0x421': 'stm32f4x', '0x431': 'stm32f4x', '0x441': 'stm32f4x', '0x463': 'stm32f4x',
        // STM32F7
        '0x449': 'stm32f7x', '0x451': 'stm32f7x', '0x452': 'stm32f7x',
        // STM32G0
        '0x460': 'stm32g0x', '0x466': 'stm32g0x', '0x467': 'stm32g0x',
        // STM32G4
        '0x468': 'stm32g4x', '0x469': 'stm32g4x',
        // STM32H7
        '0x450': 'stm32h7x', '0x483': 'stm32h7x', '0x480': 'stm32h7x',
        // STM32L0
        '0x425': 'stm32l0x', '0x417': 'stm32l0x', '0x447': 'stm32l0x',
        // STM32L1
        '0x416': 'stm32l1x', '0x429': 'stm32l1x', '0x427': 'stm32l1x',
        // STM32L4
        '0x435': 'stm32l4x', '0x462': 'stm32l4x', '0x415': 'stm32l4x', '0x461': 'stm32l4x', '0x470': 'stm32l4x', '0x471': 'stm32l4x',
        // STM32L5
        '0x472': 'stm32l5x',
        // STM32WB
        '0x494': 'stm32wbx', '0x495': 'stm32wbx',
        // STM32WL
        '0x497': 'stm32wlx'
    };

    return mcuMap[deviceId] || null;
}

// Get MCU name from type
function getMCUName(mcuType) {
    const names = {
        'stm32f0x': 'STM32F0',
        'stm32f1x': 'STM32F1',
        'stm32f2x': 'STM32F2',
        'stm32f3x': 'STM32F3',
        'stm32f4x': 'STM32F4',
        'stm32f7x': 'STM32F7',
        'stm32g0x': 'STM32G0',
        'stm32g4x': 'STM32G4',
        'stm32h7x': 'STM32H7',
        'stm32l0x': 'STM32L0',
        'stm32l1x': 'STM32L1',
        'stm32l4x': 'STM32L4',
        'stm32l5x': 'STM32L5',
        'stm32wbx': 'STM32WB',
        'stm32wlx': 'STM32WL'
    };
    return names[mcuType] || mcuType;
}

// Connect to ST-Link and read MCU info
ipcMain.on('connect-stlink', async (event, deviceId) => {
    try {
        const device = stlinkDevices.find(d => d.id === deviceId);
        if (!device) {
            mainWindow.webContents.send('output-append', `❌ Device not found\n`);
            return;
        }

        // Clean up any existing OpenOCD connection first
        if (connectedStLink && connectedStLink.openocd) {
            try {
                mainWindow.webContents.send('output-append', `🧹 Cleaning up previous connection...\n`);
                await connectedStLink.openocd.stop();
                connectedStLink = null;
                // Wait a bit for port to be released
                await new Promise(resolve => setTimeout(resolve, 500));
            } catch (cleanupErr) {
                console.error('[Cleanup Error]', cleanupErr);
            }
        }

        // Also kill any orphaned OpenOCD processes
        try {
            const { execSync } = require('child_process');
            execSync('killall -9 openocd 2>/dev/null || true');
            await new Promise(resolve => setTimeout(resolve, 300));
        } catch (killErr) {
            // Ignore errors
        }

        mainWindow.webContents.send('output-append', `🔌 Connecting to ${device.name}...\n`);

        // Get user-selected MCU type or use auto-detect
        const selectedMcuType = mainWindow.webContents.executeJavaScript(
            'document.getElementById("target-mcu").value'
        );

        let mcuType = await selectedMcuType;
        let detectedMcuType = null;
        let detectedChipId = null;
        let openocd = null;
        let targetVoltage = null; // Declare at function scope

        try {
            // Start OpenOCD
            openocd = new OpenOCDInterface();

            // Listen to OpenOCD output and parse voltage
            openocd.on('output', (data) => {
                console.log('[OpenOCD]', data);

                // Parse target voltage from OpenOCD output
                const voltageMatch = data.match(/Target voltage:\s*(\d+\.\d+)/i);
                if (voltageMatch) {
                    targetVoltage = parseFloat(voltageMatch[1]);
                    mainWindow.webContents.send('output-append',
                        `⚡ Target Voltage: ${targetVoltage.toFixed(2)}V\n`
                    );

                    // Warn if voltage is low (but continue)
                    if (targetVoltage < 3.0) {
                        mainWindow.webContents.send('output-append',
                            `⚠️  Low Voltage Warning: ${targetVoltage.toFixed(2)}V (recommended: 3.0-3.6V)\n` +
                            `   This may cause connection instability!\n`
                        );
                    }
                }
            });

            // If auto-detect, try to probe the device first
            if (mcuType === 'auto') {
                mainWindow.webContents.send('output-append', `🔍 Auto-detecting MCU type...\n`);

                // METHOD 1: Try st-info (Most Reliable)
                try {
                    const { execSync } = require('child_process');
                    // Check if st-info exists
                    try {
                        execSync('st-info --version', { stdio: 'ignore' });

                        mainWindow.webContents.send('output-append', `   Trying st-info probe...\n`);
                        const output = execSync('st-info --probe').toString();
                        console.log('[st-info] Output:', output);
                        mainWindow.webContents.send('output-append', `   [st-info] ${output.trim()}\n`);

                        // Parse output
                        // Example: Found 1 stlink programmers... serial: ... openocd: ... flash: ... sram: ... chipid: 0x0413
                        const chipIdMatch = output.match(/chipid:\s*(0x[0-9a-fA-F]+)/);
                        if (chipIdMatch) {
                            const chipId = chipIdMatch[1];
                            detectedChipId = chipId;
                            detectedMcuType = detectMCUType(chipId);

                            if (detectedMcuType) {
                                mcuType = detectedMcuType;
                                mainWindow.webContents.send('output-append',
                                    `✅ Detected via st-info: ${getMCUName(mcuType)} (ID: ${chipId})\n`
                                );
                            }
                        }
                    } catch (e) {
                        console.log('[st-info] Not found or failed:', e.message);
                    }
                } catch (err) {
                    console.error('[Auto-Detect] st-info failed:', err);
                }

                // METHOD 2: OpenOCD Probe (Fallback)
                if (!detectedMcuType) {
                    mainWindow.webContents.send('output-append', `   Trying OpenOCD probe (fallback)...\n`);
                    try {
                        // Try with a generic config first to read device ID
                        await openocd.start('stm32f4x', 'stlink'); // Use F4 as generic probe

                        // Connect TCL
                        await openocd.connectTCL();

                        // Try to read device ID
                        const stm32Tools = new STM32Tools(openocd);
                        const deviceInfo = await stm32Tools.getDeviceInfo();

                        if (deviceInfo && deviceInfo.deviceID) {
                            detectedMcuType = detectMCUType(deviceInfo.deviceID);
                            if (detectedMcuType) {
                                mcuType = detectedMcuType;
                                mainWindow.webContents.send('output-append',
                                    `✅ Detected via OpenOCD: ${getMCUName(mcuType)} (ID: ${deviceInfo.deviceID})\n`
                                );

                                // Restart OpenOCD with correct MCU type if different
                                if (mcuType !== 'stm32f4x') {
                                    await openocd.stop();
                                    await new Promise(resolve => setTimeout(resolve, 500));
                                    await openocd.start(mcuType, 'stlink');
                                    mainWindow.webContents.send('output-append',
                                        `🔄 Reconnecting with ${getMCUName(mcuType)} configuration...\n`
                                    );
                                }
                            } else {
                                mainWindow.webContents.send('output-append',
                                    `⚠️ Unknown MCU ID: ${deviceInfo.deviceID}, using STM32F4 config\n`
                                );
                                mcuType = 'stm32f4x';
                            }
                        }
                    } catch (probeErr) {
                        // If probe fails, clean up and fall back to F4
                        mainWindow.webContents.send('output-append',
                            `⚠️ Auto-detect failed, trying STM32F4 configuration...\n`
                        );
                        console.error('[Auto-Detect] OpenOCD probe failed:', probeErr);
                        try {
                            await openocd.stop();
                            await new Promise(resolve => setTimeout(resolve, 500));
                        } catch (e) { /* ignore */ }
                        mcuType = 'stm32f4x';
                        await openocd.start(mcuType, 'stlink');
                    }
                } else {
                    // Start OpenOCD with detected type (from st-info)
                    await openocd.start(mcuType, 'stlink');
                }
            } else {
                // User selected specific MCU type
                await openocd.start(mcuType, 'stlink');
                mainWindow.webContents.send('output-append',
                    `📝 Using ${getMCUName(mcuType)} configuration\n`
                );
            }

            mainWindow.webContents.send('output-append', '✅ OpenOCD started\n');
        } catch (err) {
            // Check for common errors
            if (err.message.includes('USB permission')) {
                mainWindow.webContents.send('output-append',
                    `❌ USB Permission Error!\n` +
                    `   Run: sudo dpkg-reconfigure armeditor\n` +
                    `   Or: sudo udevadm control --reload-rules && sudo udevadm trigger\n`
                );
            } else if (err.message.includes('target voltage may be too low')) {
                mainWindow.webContents.send('output-append',
                    `❌ Target Voltage Too Low!\n` +
                    `   \n` +
                    `   The ST-Link cannot detect the target MCU voltage.\n` +
                    `   \n` +
                    `   Solutions:\n` +
                    `   1. Power ON your target board (USB or external power)\n` +
                    `   2. Check ST-Link VDD/VAPP pin is connected to target 3.3V\n` +
                    `   3. Verify target MCU is powered (LED should be ON)\n` +
                    `   4. Check all SWD connections (SWDIO, SWCLK, GND, VDD)\n` +
                    `   5. Try another USB cable or port\n` +
                    `   6. Reset your target board\n` +
                    `   \n` +
                    `   💡 ST-Link needs to see target voltage (3.0-3.6V) to work.\n`
                );
            } else if (err.message.includes('not connected') || err.message.includes('not found')) {
                mainWindow.webContents.send('output-append',
                    `❌ ST-Link not detected!\n` +
                    `   1. Check USB cable connection\n` +
                    `   2. Try a different USB port\n` +
                    `   3. Run: lsusb | grep 0483\n`
                );
            } else {
                mainWindow.webContents.send('output-append', `❌ OpenOCD error: ${err.message}\n`);
            }
            throw err;
        }

        // Connect TCL
        await openocd.connectTCL();
        mainWindow.webContents.send('output-append', '✅ TCL connected\n');

        // Get device info using STM32Tools with timeout
        let deviceInfo = null;
        try {
            mainWindow.webContents.send('output-append', '📖 Reading device information...\n');
            const stm32Tools = new STM32Tools(openocd);

            // Add timeout to getDeviceInfo (increased to 15s for slow connections)
            const timeoutPromise = new Promise((_, reject) =>
                setTimeout(() => reject(new Error('Device info read timeout')), 15000)
            );

            deviceInfo = await Promise.race([
                stm32Tools.getDeviceInfo(),
                timeoutPromise
            ]);

            mainWindow.webContents.send('output-append',
                `📱 MCU: ${deviceInfo.deviceName}\n` +
                `   ID: ${deviceInfo.deviceID}\n` +
                `   Flash: ${deviceInfo.flash.sizeKB} KB\n` +
                `   Type: ${getMCUName(mcuType)}\n`
            );
        } catch (infoErr) {
            // Device info failed, but connection is OK
            mainWindow.webContents.send('output-append',
                `⚠️ Could not read device info: ${infoErr.message}\n` +
                `   Connection is OK, but some details are unavailable.\n`
            );

            // Create minimal device info using st-info data if available
            deviceInfo = {
                deviceName: getMCUName(mcuType),
                deviceID: detectedChipId || 'Unknown',
                flash: { sizeKB: 0 },
                ram: { sizeKB: 0 },
                revisionID: 'Unknown'
            };
        }

        // Update device with MCU info
        device.connected = true;
        device.mcu = {
            name: deviceInfo.deviceName,
            deviceId: deviceInfo.deviceID,
            flashSize: deviceInfo.flash.sizeKB ? (deviceInfo.flash.sizeKB + ' KB') : 'Unknown',
            revisionId: deviceInfo.revisionID || 'Unknown',
            type: mcuType,
            typeName: getMCUName(mcuType)
        };

        connectedStLink = {
            id: deviceId,
            openocd: openocd,
            mcu: device.mcu
        };

        // Update dropdown to show detected MCU
        if (mcuType !== 'auto') {
            mainWindow.webContents.executeJavaScript(
                `document.getElementById('target-mcu').value = '${mcuType}';`
            );
        }

        // Send device-connected event with full info
        mainWindow.webContents.send('device-connected', {
            name: device.name,
            mcu: {
                device: deviceInfo.deviceName,
                id: deviceInfo.deviceID,
                flash: deviceInfo.flash.sizeKB ? (deviceInfo.flash.sizeKB + ' KB') : 'Unknown',
                ram: deviceInfo.ram ? (deviceInfo.ram.sizeKB + ' KB') : 'Unknown',
                core: 'ARM Cortex-M',
                type: getMCUName(mcuType)
            },
            stlink: {
                version: device.version,
                firmware: 'V' + device.version
            }
        });

        mainWindow.webContents.send('output-append', '✅ Device connected!\n');

        // Send updated devices list
        mainWindow.webContents.send('stlink-devices', stlinkDevices);

    } catch (error) {
        console.error('[ST-Link Connect Error]', error);
        mainWindow.webContents.send('output-append', `❌ Connection failed: ${error.message}\n`);

        // Clean up OpenOCD on error
        try {
            if (openocd && openocd.running) {
                await openocd.stop();
            }
        } catch (cleanupErr) {
            console.error('[Cleanup on error]', cleanupErr);
        }
    }
});

// Disconnect ST-Link
ipcMain.on('disconnect-stlink', async (event, deviceId) => {
    try {
        mainWindow.webContents.send('output-append', '🔴 Disconnecting ST-Link...\n');

        if (connectedStLink && connectedStLink.openocd) {
            await connectedStLink.openocd.stop();
        }

        // Also kill any orphaned OpenOCD processes
        try {
            const { execSync } = require('child_process');
            execSync('killall -9 openocd 2>/dev/null || true');
        } catch (e) { /* ignore */ }

        const device = stlinkDevices.find(d => d.id === deviceId);
        if (device) {
            device.connected = false;
            device.mcu = null;
        }

        connectedStLink = null;

        mainWindow.webContents.send('output-append', '✅ ST-Link disconnected\n');
        mainWindow.webContents.send('device-disconnected');
        mainWindow.webContents.send('stlink-devices', stlinkDevices);

    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Disconnect error: ${error.message}\n`);
    }
});

// Open project handler
ipcMain.on('open-project', () => {
    openProject();
});

// Save console log handler
ipcMain.on('save-console-log', (event, content) => {
    const options = {
        title: 'Save Console Log',
        defaultPath: path.join(app.getPath('documents'), 'hopeide-log.txt'),
        filters: [
            { name: 'Text Files', extensions: ['txt'] },
            { name: 'All Files', extensions: ['*'] }
        ]
    };

    dialog.showSaveDialog(mainWindow, options).then(result => {
        if (!result.canceled && result.filePath) {
            fs.writeFileSync(result.filePath, content, 'utf8');
            mainWindow.webContents.send('output-append', `✅ Log saved to ${result.filePath}\n`);
        }
    });
});

// Read memory handler
ipcMain.on('read-memory', async (event, data) => {
    try {
        if (!connectedStLink || !connectedStLink.openocd) {
            mainWindow.webContents.send('output-append', '❌ No device connected\n');
            return;
        }

        const address = data.address;
        const size = data.size;

        mainWindow.webContents.send('output-append', `📖 Reading ${size} bytes from ${address}...\n`);

        // Use OpenOCD to read memory
        const stm32Tools = new STM32Tools(connectedStLink.openocd);
        // Use 2s timeout for UI reads to prevent hanging
        const memoryData = await stm32Tools.readMemory(address, size, 2000);

        // Send memory data to renderer
        mainWindow.webContents.send('memory-data', { address, data: memoryData });
        mainWindow.webContents.send('output-append', `✅ Memory read complete\n`);

    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Memory read error: ${error.message}\n`);
    }
});

// Flash firmware handler
ipcMain.on('flash-firmware', async (event, data) => {
    try {
        if (!connectedStLink || !connectedStLink.openocd) {
            mainWindow.webContents.send('output-append', '❌ No device connected\n');
            return;
        }

        const filePath = data.file;
        const options = data.options;

        mainWindow.webContents.send('output-append', `⚡ Flashing firmware: ${path.basename(filePath)}\n`);

        // Use FlashManager to flash firmware
        const flashManager = new FlashManager(connectedStLink.openocd);

        // Flash with options
        await flashManager.flash(filePath, {
            verify: options.verify,
            reset: options.run,
            erase: !options.skipErase
        });

        mainWindow.webContents.send('flash-progress', 100);
        mainWindow.webContents.send('output-append', `✅ Flash complete!\n`);

        if (options.run) {
            mainWindow.webContents.send('output-append', `🚀 Running application...\n`);
        }

    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Flash error: ${error.message}\n`);
        mainWindow.webContents.send('flash-progress', 0);
    }
});

// Erase chip handler
ipcMain.on('erase-chip', async (event) => {
    try {
        if (!connectedStLink || !connectedStLink.openocd) {
            mainWindow.webContents.send('output-append', '❌ No device connected\n');
            return;
        }

        mainWindow.webContents.send('output-append', `🗑️ Erasing chip...\n`);

        const flashManager = new FlashManager(connectedStLink.openocd);
        await flashManager.eraseChip();

        mainWindow.webContents.send('output-append', `✅ Chip erased successfully\n`);

    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Erase error: ${error.message}\n`);
    }
});

// Read device memory handler
ipcMain.on('read-device-memory', async (event) => {
    try {
        if (!connectedStLink || !connectedStLink.openocd) {
            mainWindow.webContents.send('output-append', '❌ No device connected\n');
            return;
        }

        mainWindow.webContents.send('output-append', `📖 Reading device flash memory...\n`);

        // Get flash size from device info
        const flashSize = connectedStLink.mcu ? parseInt(connectedStLink.mcu.flashSize) * 1024 : 0x10000;

        // Read flash memory
        const stm32Tools = new STM32Tools(connectedStLink.openocd);
        const memoryData = await stm32Tools.readMemory('0x08000000', flashSize);

        // Save to file
        const options = {
            title: 'Save Memory Dump',
            defaultPath: path.join(app.getPath('documents'), 'flash-dump.bin'),
            filters: [
                { name: 'Binary Files', extensions: ['bin'] },
                { name: 'All Files', extensions: ['*'] }
            ]
        };

        const result = await dialog.showSaveDialog(mainWindow, options);
        if (!result.canceled && result.filePath) {
            fs.writeFileSync(result.filePath, Buffer.from(memoryData));
            mainWindow.webContents.send('output-append', `✅ Memory saved to ${result.filePath}\n`);
        }

    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Read error: ${error.message}\n`);
    }
});

// SWV Trace handlers
let swvEnabled = false;
let swvBuffer = '';

ipcMain.on('swv-enable', async (event, config) => {
    try {
        if (!connectedStLink || !connectedStLink.openocd) {
            mainWindow.webContents.send('swv-error', 'No device connected');
            return;
        }

        mainWindow.webContents.send('output-append', `📡 Configuring SWV (CPU: ${config.cpuFreq / 1000000} MHz)...\n`);

        const stm32Tools = new STM32Tools(connectedStLink.openocd);
        await stm32Tools.monitorStartSWO(0, config.cpuFreq, config.swoFreq);

        swvEnabled = true;
        swvBuffer = '';

        mainWindow.webContents.send('swv-enabled');
        mainWindow.webContents.send('output-append', `✅ SWV enabled. ITM Port 0 ready.\n`);

    } catch (error) {
        mainWindow.webContents.send('swv-error', error.message);
        mainWindow.webContents.send('output-append', `❌ SWV enable failed: ${error.message}\n`);
    }
});

ipcMain.on('swv-disable', async (event) => {
    try {
        if (connectedStLink && connectedStLink.openocd) {
            const stm32Tools = new STM32Tools(connectedStLink.openocd);
            await stm32Tools.monitorStopSWO();
        }

        swvEnabled = false;
        swvBuffer = '';

        mainWindow.webContents.send('output-append', '⏹️ SWV disabled\n');

    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ SWV disable error: ${error.message}\n`);
    }
});

ipcMain.on('swv-read', async (event) => {
    if (!swvEnabled || !connectedStLink || !connectedStLink.openocd) {
        return;
    }

    try {
        const stm32Tools = new STM32Tools(connectedStLink.openocd);
        const data = await stm32Tools.monitorReadSWO();

        if (data && data.length > 0) {
            // Accumulate data in buffer
            swvBuffer += data;

            // Split by newlines and send complete lines
            const lines = swvBuffer.split('\n');
            swvBuffer = lines.pop(); // Keep incomplete line in buffer

            for (const line of lines) {
                if (line.trim()) {
                    mainWindow.webContents.send('swv-data', line);
                }
            }
        }
    } catch (error) {
        // Ignore read errors during polling
        console.error('[SWV Read Error]', error.message);
    }
});

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

        const validation = projectManager.validateConfig(config);
        if (!validation.valid) {
            mainWindow.webContents.send('output-append',
                `❌ Invalid project configuration:\n` +
                validation.errors.map(e => `   - ${e}\n`).join('')
            );
            return;
        }

        projectManager.config = config;
        projectManager.saveConfig();
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

        const validation = projectManager.validateConfig(config);
        if (!validation.valid) {
            mainWindow.webContents.send('output-append',
                `❌ Invalid project configuration:\n` +
                validation.errors.map(e => `   - ${e}\n`).join('')
            );
            event.reply('project-settings-error', validation.errors);
            return;
        }

        projectManager.config = config;
        projectManager.saveConfig();
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

// ============================================================================
// NEW PROJECT / TEMPLATES
// ============================================================================

let newProjectWindow = null;

function openNewProjectWizard() {
    if (newProjectWindow) {
        newProjectWindow.focus();
        return;
    }

    newProjectWindow = new BrowserWindow({
        width: 800,
        height: 600,
        parent: mainWindow,
        modal: false,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false
        },
        backgroundColor: '#1e1e1e',
        title: 'New Project'
    });

    newProjectWindow.loadFile(path.join(__dirname, '../renderer/new-project.html'));

    newProjectWindow.on('closed', () => {
        newProjectWindow = null;
    });

    // Send template list when window is ready
    newProjectWindow.webContents.on('did-finish-load', () => {
        templateManager = templateManager || new TemplateManager();
        const templates = templateManager.listTemplates();
        newProjectWindow.webContents.send('templates-list', templates);
    });
}

ipcMain.on('open-new-project', () => {
    openNewProjectWizard();
});

ipcMain.on('get-templates-list', (event) => {
    templateManager = templateManager || new TemplateManager();
    const templates = templateManager.listTemplates();
    event.reply('templates-list', templates);
});

ipcMain.on('select-project-path', async (event) => {
    const result = await dialog.showOpenDialog(mainWindow, {
        properties: ['openDirectory', 'createDirectory'],
        title: 'Select Project Location'
    });

    if (!result.canceled && result.filePaths.length > 0) {
        event.reply('project-path-selected', result.filePaths[0]);
    }
});

ipcMain.on('create-project-from-template', async (event, options) => {
    try {
        templateManager = templateManager || new TemplateManager();

        mainWindow.webContents.send('output-append', `\n🆕 Creating new project: ${options.projectName}\n`);
        mainWindow.webContents.send('output-append', `📋 Template: ${options.templateId}\n`);
        mainWindow.webContents.send('output-append', `📁 Location: ${options.projectPath}\n`);

        const result = await templateManager.createFromTemplate(
            options.templateId,
            options.projectPath,
            {
                projectName: options.projectName,
                downloadHAL: true
            }
        );

        if (result.success) {
            mainWindow.webContents.send('output-append', `✅ Project created successfully!\n`);
            mainWindow.webContents.send('output-append', `📝 Configuration saved to project.json\n`);

            // Auto-open the project
            currentProjectPath = result.projectPath;
            projectManager = new ProjectManager(currentProjectPath);

            mainWindow.webContents.send('output-append', `📂 Project opened: ${path.basename(currentProjectPath)}\n`);

            event.reply('project-created', { success: true });
        } else {
            throw new Error('Template creation failed');
        }

    } catch (error) {
        console.error('[NewProject] Error:', error);
        mainWindow.webContents.send('output-append', `❌ Project creation failed: ${error.message}\n`);
        event.reply('project-created', { success: false, error: error.message });
    }
});

/**
 * App lifecycle
 */
app.whenReady().then(() => {
    createWindow();

    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) {
            createWindow();
        }
    });
});

app.on('window-all-closed', () => {
    // Clean up OpenOCD on exit
    if (connectedStLink && connectedStLink.openocd) {
        try {
            connectedStLink.openocd.stop();
        } catch (e) { /* ignore */ }
    }

    // Kill any orphaned OpenOCD processes
    try {
        const { execSync } = require('child_process');
        execSync('killall -9 openocd 2>/dev/null || true');
    } catch (e) { /* ignore */ }

    if (process.platform !== 'darwin') {
        app.quit();
    }
});

app.on('before-quit', () => {
    // Clean up OpenOCD on quit
    if (connectedStLink && connectedStLink.openocd) {
        try {
            connectedStLink.openocd.stop();
        } catch (e) { /* ignore */ }
    }

    // Kill any orphaned OpenOCD processes
    try {
        const { execSync } = require('child_process');
        execSync('killall -9 openocd 2>/dev/null || true');
    } catch (e) { /* ignore */ }
});

console.log('HopeIDE Electron app started');
