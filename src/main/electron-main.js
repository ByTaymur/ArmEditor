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
// v2.1.0 Professional IDE Features
const STM32CubeProgrammer = require('../programmer/stm32-cube-programmer');
const ProjectManager = require('../project/project-manager');
const TemplateManager = require('../project/template-manager');
// v3.0.0 Professional Debugger & Options
const DeviceDatabase = require('../device/device-database');
const OptionsManager = require('../project/options-manager');
const RegisterViewer = require('../debugger/register-viewer');
const MemoryBrowser = require('../debugger/memory-browser');
const PeripheralViewer = require('../debugger/peripheral-viewer');
const MCUDetector = require('../stm32/mcu-detector');
const CubeMXIntegration = require('../project/cubemx-integration');
const OpenSourceSTLink = require('../programmer/open-source-stlink');

let mainWindow;
let currentProjectPath = null;
let currentFilePath = null;

// Debug instances
let gdbBackend = null;
let openocdInterface = null;
let flashManager = null;
let stm32Tools = null;
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
    mainWindow.loadFile(path.join(__dirname, '../renderer/ide-professional.html'));

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

        if (!openocdInterface) {
            openocdInterface = new OpenOCDInterface();
            await openocdInterface.start();
            await openocdInterface.connectTCL();
        }

        flashManager = flashManager || new FlashManager(openocdInterface);

        const result = await flashManager.programAndRun(filePath, true, true);

        if (result.success) {
            mainWindow.webContents.send('output-append', '✅ Flash successful!\n');
            for (const step of result.steps) {
                mainWindow.webContents.send('output-append', `   ${step}\n`);
            }
        } else {
            mainWindow.webContents.send('output-append', `❌ Flash failed: ${result.error}\n`);
        }

    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Flash error: ${error.message}\n`);
    }
});

ipcMain.on('flash-binary', async (event, { filePath, address, tool }) => {
    try {
        mainWindow.webContents.send('output-append', `⚡ Flashing ${path.basename(filePath)}...\n`);
        mainWindow.webContents.send('flash-progress', 10);

        let result;
        if (tool === 'stlink-org') {
            const stLinkOrg = new OpenSourceSTLink();
            result = await stLinkOrg.flashBinary(filePath, address);
        } else {
            // Default: STM32CubeProgrammer
            const programmer = new STM32CubeProgrammer();
            result = await programmer.flashBinary(filePath, address);
        }
        mainWindow.webContents.send('flash-progress', 100);
        mainWindow.webContents.send('output-append', `✅ Flash successful!\n`);

    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Flash failed: ${error.message}\n`);
        mainWindow.webContents.send('flash-progress', 0);
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
        let openocd = null;

        try {
            // Start OpenOCD
            openocd = new OpenOCDInterface();

            // Listen to OpenOCD output
            openocd.on('output', (data) => {
                console.log('[OpenOCD]', data);
            });

            // If auto-detect, try to probe the device first
            if (mcuType === 'auto') {
                mainWindow.webContents.send('output-append', `🔍 Auto-detecting MCU type...\n`);

                // Try with a generic config first to read device ID
                try {
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
                                `✅ Detected: ${getMCUName(mcuType)} (ID: ${deviceInfo.deviceID})\n`
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
                    try {
                        await openocd.stop();
                        await new Promise(resolve => setTimeout(resolve, 500));
                    } catch (e) { /* ignore */ }
                    mcuType = 'stm32f4x';
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

            // Create minimal device info
            deviceInfo = {
                deviceName: getMCUName(mcuType),
                deviceID: 'Unknown',
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
ipcMain.on('read-memory', async (event, { address, size, outputFile, tool }) => {
    try {
        mainWindow.webContents.send('output-append', `📖 Reading memory from ${address}...\n`);

        let result;
        if (tool === 'stlink-org') {
            const stLinkOrg = new OpenSourceSTLink();
            result = await stLinkOrg.readMemory(address, size, outputFile);
        } else {
            const programmer = new STM32CubeProgrammer();
            result = await programmer.readMemory(address, size, outputFile);
        }

        // Send memory data to renderer
        mainWindow.webContents.send('memory-data', { address, data: result.data }); // Assuming result.data contains the memory buffer
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

ipcMain.on('scan-stlinks', async (event, tool = 'cubeprogrammer') => {
    console.log(`[scan-stlinks] Called with tool: ${tool}`);
    try {
        let devices = [];
        let toolUsed = tool;

        if (tool === 'stlink-org') {
            console.log('[scan-stlinks] Using stlink-org path');
            mainWindow.webContents.send('output-append', '🔍 Scanning with Open Source ST-Link...\n');
            const stLinkOrg = new OpenSourceSTLink();

            // Check if stlink tools are installed
            const isInstalled = await stLinkOrg.isInstalled();
            console.log(`[scan-stlinks] st-info installed: ${isInstalled}`);
            if (!isInstalled) {
                mainWindow.webContents.send('output-append', '⚠️ st-info not found. Install stlink-tools or switch to CubeProgrammer.\n');
                event.reply('stlink-scan-complete', []);
                return;
            }

            devices = await stLinkOrg.listDevices();
            console.log(`[scan-stlinks] Found ${devices.length} devices via stlink-org:`, devices);
        } else {
            console.log('[scan-stlinks] Using CubeProgrammer path');
            // Default: STM32CubeProgrammer
            mainWindow.webContents.send('output-append', '🔍 Scanning with STM32CubeProgrammer...\n');

            const cubeProg = new STM32CubeProgrammer();
            const isInstalled = await cubeProg.isInstalled();
            console.log(`[scan-stlinks] CubeProgrammer installed: ${isInstalled}`);

            if (!isInstalled) {
                mainWindow.webContents.send('output-append', '⚠️ STM32_Programmer_CLI not found.\n');

                // Try fallback to Open Source ST-Link
                console.log('[scan-stlinks] Falling back to stlink-org');
                mainWindow.webContents.send('output-append', '🔄 Trying Open Source ST-Link as fallback...\n');
                const stLinkOrg = new OpenSourceSTLink();
                const stlinkInstalled = await stLinkOrg.isInstalled();
                console.log(`[scan-stlinks] Fallback st-info installed: ${stlinkInstalled}`);

                if (stlinkInstalled) {
                    devices = await stLinkOrg.listDevices();
                    console.log(`[scan-stlinks] Found ${devices.length} devices via fallback:`, devices);
                    toolUsed = 'stlink-org';
                    mainWindow.webContents.send('output-append', '✅ Using Open Source ST-Link\n');
                } else {
                    mainWindow.webContents.send('output-append', '❌ No programmer tools found. Install STM32CubeProgrammer or stlink-tools.\n');
                    event.reply('stlink-scan-complete', []);
                    return;
                }
            } else {
                // CubeProgrammer is installed, use STM32Tools
                if (!stm32Tools) {
                    stm32Tools = new STM32Tools();
                }
                devices = await stm32Tools.scanSTLink();
                console.log(`[scan-stlinks] Found ${devices.length} devices via STM32Tools:`, devices);
            }
        }

        console.log(`[scan-stlinks] Total devices found: ${devices.length}`);
        if (devices.length > 0) {
            const device = devices[0];
            console.log(`[scan-stlinks] Selected device:`, device);
            mainWindow.webContents.send('output-append', `✅ Found: ${device.serial || device.name || 'ST-Link'}\n`);
            mainWindow.webContents.send('stlink-detected', device);

            // AUTO MCU DETECTION (only if we actually have a connected device)
            // Skip if we're using fallback tools that may not work
            if (toolUsed === 'cubeprogrammer' && !isInstalled) {
                console.log('[scan-stlinks] Skipping MCU detection - no CubeProgrammer');
                mainWindow.webContents.send('output-append', '⚠️ Skipping MCU auto-detection (no CubeProgrammer)\n');
            } else {
                console.log('[scan-stlinks] Starting MCU auto-detection');
                mainWindow.webContents.send('output-append', '🤖 Auto-detecting MCU...\n');
                try {
                    const mcuDetector = new MCUDetector();
                    const detected = await mcuDetector.autoDetect();
                    console.log('[scan-stlinks] MCU detection result:', detected);

                    if (detected.success) {
                        mainWindow.webContents.send('output-append',
                            `✅ Detected: ${detected.deviceName} (${detected.core})\n`);

                        // Match with database
                        if (deviceDb) {
                            const dbDevice = mcuDetector.matchWithDatabase(deviceDb);
                            if (dbDevice) {
                                mainWindow.webContents.send('output-append',
                                    `📦 Found in database: ${dbDevice.name}\n`);
                                mainWindow.webContents.send('mcu-auto-detected', {
                                    detected: detected,
                                    dbDevice: dbDevice
                                });

                                // Auto-apply to project if open
                                if (currentProjectPath && optionsManager) {
                                    optionsManager.setDevice(dbDevice.name);
                                    mainWindow.webContents.send('output-append',
                                        `⚙️ Auto-configured project for ${dbDevice.name}\n`);
                                }
                            } else {
                                mainWindow.webContents.send('output-append',
                                    `⚠️ ${detected.deviceName} not in database\n`);
                            }
                        }
                    } else {
                        mainWindow.webContents.send('output-append', '⚠️ MCU auto-detection failed\n');
                    }
                } catch (detectionError) {
                    console.log('[scan-stlinks] MCU detection error:', detectionError.message);
                    // Don't spam logs on detection failure
                    mainWindow.webContents.send('output-append',
                        `⚠️ Auto-detection unavailable\n`);
                }
            }
        } else {
            console.log('[scan-stlinks] No devices found');
            mainWindow.webContents.send('output-append', '❌ No ST-Link devices found\n');
        }

        console.log('[scan-stlinks] Sending stlink-scan-complete event');
        event.reply('stlink-scan-complete', devices);
    } catch (error) {
        console.error('[scan-stlinks Error]', error);
        mainWindow.webContents.send('output-append', `❌ Scan error: ${error.message}\n`);
        event.reply('stlink-scan-complete', []);
    }
});

// Erase chip handler
ipcMain.on('erase-chip', async (event, tool) => {
    try {
        mainWindow.webContents.send('output-append', '🗑️ Erasing chip...\n');

        let result;
        if (tool === 'stlink-org') {
            const stLinkOrg = new OpenSourceSTLink();
            result = await stLinkOrg.eraseChip();
        } else {
            const programmer = new STM32CubeProgrammer();
            result = await programmer.eraseChip();
        }

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
// v2.1.0: PROJECT SETTINGS & NEW PROJECT
// ============================================================================

let settingsWindow = null;
let newProjectWindow = null;
let projectManager = null;
let templateManager = null;

ipcMain.on('open-project-settings', () => {
    if (settingsWindow) {
        settingsWindow.focus();
        return;
    }

    settingsWindow = new BrowserWindow({
        width: 900,
        height: 700,
        parent: mainWindow,
        modal: false,
        webPreferences: { nodeIntegration: true, contextIsolation: false },
        backgroundColor: '#1e1e1e',
        title: 'Project Settings'
    });

    settingsWindow.loadFile(path.join(__dirname, '../renderer/project-settings.html'));
    settingsWindow.on('closed', () => { settingsWindow = null; });

    settingsWindow.webContents.on('did-finish-load', () => {
        if (currentProjectPath) {
            projectManager = projectManager || new ProjectManager(currentProjectPath);
            settingsWindow.webContents.send('load-config', projectManager.config);
        }
    });
});

ipcMain.on('project-settings-apply', (event, config) => {
    if (!currentProjectPath) return;

    projectManager = projectManager || new ProjectManager(currentProjectPath);
    const validation = projectManager.validateConfig(config);

    if (validation.valid) {
        projectManager.config = config;
        projectManager.saveConfig();
        projectManager.saveMakefile();
        mainWindow.webContents.send('output-append', '✅ Settings applied\n');
    }
});

ipcMain.on('project-settings-save', (event, config) => {
    if (!currentProjectPath) return;

    projectManager = projectManager || new ProjectManager(currentProjectPath);
    projectManager.config = config;
    projectManager.saveConfig();
    projectManager.saveMakefile();
    event.reply('project-settings-saved');
});

ipcMain.on('open-new-project', () => {
    if (newProjectWindow) {
        newProjectWindow.focus();
        return;
    }

    newProjectWindow = new BrowserWindow({
        width: 800,
        height: 600,
        parent: mainWindow,
        modal: false,
        webPreferences: { nodeIntegration: true, contextIsolation: false },
        backgroundColor: '#1e1e1e',
        title: 'New Project'
    });

    newProjectWindow.loadFile(path.join(__dirname, '../renderer/new-project.html'));
    newProjectWindow.on('closed', () => { newProjectWindow = null; });

    newProjectWindow.webContents.on('did-finish-load', () => {
        templateManager = templateManager || new TemplateManager();
        const templates = templateManager.listTemplates();
        newProjectWindow.webContents.send('templates-list', templates);
    });
});

ipcMain.on('get-templates-list', (event) => {
    templateManager = templateManager || new TemplateManager();
    event.reply('templates-list', templateManager.listTemplates());
});

ipcMain.on('create-project-from-template', async (event, options) => {
    try {
        templateManager = templateManager || new TemplateManager();

        mainWindow.webContents.send('output-append', `🆕 Creating: ${options.projectName}\n`);

        const result = await templateManager.createFromTemplate(
            options.templateId,
            options.projectPath,
            options
        );

        if (result.success) {
            currentProjectPath = result.projectPath;
            projectManager = new ProjectManager(currentProjectPath);
            mainWindow.webContents.send('output-append', '✅ Project created!\n');
            event.reply('project-created', { success: true });
        }
    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Error: ${error.message}\n`);
        event.reply('project-created', { success: false, error: error.message });
    }
});

// ============================================================================
// v3.0.0: PROFESSIONAL DEBUGGER & OPTIONS
// ============================================================================

let registerWindow = null;
let memoryWindow = null;
let optionsWindow = null;
let deviceDb = null;
let optionsManager = null;
let registerViewer = null;
let memoryBrowser = null;
let peripheralViewer = null;

// Initialize device database
try {
    deviceDb = new DeviceDatabase();
    console.log('[HopeIDE] Device database loaded:', deviceDb.getStatistics());
} catch (e) {
    console.error('[HopeIDE] Failed to load device database:', e);
}

// ===== DEBUGGER WINDOWS =====

ipcMain.on('open-register-window', () => {
    if (registerWindow) {
        registerWindow.focus();
        return;
    }

    registerWindow = new BrowserWindow({
        width: 600,
        height: 700,
        title: 'Register Viewer',
        webPreferences: { nodeIntegration: true, contextIsolation: false },
        backgroundColor: '#1e1e1e'
    });

    registerWindow.loadFile(path.join(__dirname, '../renderer/register-window.html'));
    registerWindow.on('closed', () => { registerWindow = null; });
});

ipcMain.on('open-memory-window', () => {
    if (memoryWindow) {
        memoryWindow.focus();
        return;
    }

    memoryWindow = new BrowserWindow({
        width: 800,
        height: 600,
        title: 'Memory Browser',
        webPreferences: { nodeIntegration: true, contextIsolation: false },
        backgroundColor: '#1e1e1e'
    });

    memoryWindow.loadFile(path.join(__dirname, '../renderer/memory-window.html'));
    memoryWindow.on('closed', () => { memoryWindow = null; });
});

ipcMain.on('open-options-dialog', () => {
    if (optionsWindow) {
        optionsWindow.focus();
        return;
    }

    optionsWindow = new BrowserWindow({
        width: 900,
        height: 700,
        title: 'Options for Target',
        webPreferences: { nodeIntegration: true, contextIsolation: false },
        backgroundColor: '#1e1e1e',
        parent: mainWindow,
        modal: false
    });

    optionsWindow.loadFile(path.join(__dirname, '../renderer/options-dialog.html'));
    optionsWindow.on('closed', () => { optionsWindow = null; });
});

// ===== REGISTER VIEWER =====

ipcMain.on('debug-read-registers', async () => {
    if (!gdbBackend || !gdbBackend.isConnected) {
        if (registerWindow) {
            registerWindow.webContents.send('registers-data', {
                cpu: {},
                error: 'GDB not connected'
            });
        }
        return;
    }

    try {
        if (!registerViewer) {
            registerViewer = new RegisterViewer(gdbBackend);
        }
        const data = await registerViewer.readCPURegisters();
        if (registerWindow) {
            registerWindow.webContents.send('registers-data', registerViewer.getRegisterSnapshot());
        }
    } catch (e) {
        console.error('[RegisterViewer] Error:', e);
    }
});

ipcMain.on('debug-write-register', async (event, { name, value }) => {
    if (!registerViewer || !gdbBackend) return;
    try {
        await registerViewer.writeRegister(name, value);
    } catch (e) {
        console.error('[RegisterViewer] Write error:', e);
    }
});

// ===== MEMORY BROWSER =====

ipcMain.on('debug-read-memory', async (event, { address, size }) => {
    if (!gdbBackend || !gdbBackend.isConnected) {
        if (memoryWindow) {
            memoryWindow.webContents.send('memory-data', []);
        }
        return;
    }

    try {
        if (!memoryBrowser) {
            memoryBrowser = new MemoryBrowser(gdbBackend);
        }
        const data = await memoryBrowser.readMemory(address, size);
        const formatted = memoryBrowser.formatHexView(data, address);
        if (memoryWindow) {
            memoryWindow.webContents.send('memory-data', formatted);
        }
    } catch (e) {
        console.error('[MemoryBrowser] Error:', e);
    }
});

// ===== OPTIONS DIALOG =====

ipcMain.on('get-device-list', (event) => {
    if (!deviceDb) return;
    const devices = Object.keys(deviceDb.getDevices());
    event.reply('device-list', devices);
});

ipcMain.on('load-options', (event) => {
    if (!currentProjectPath) {
        event.reply('options-loaded', {});
        return;
    }

    try {
        // Check if CubeMX project
        if (CubeMXIntegration.isCubeMXProject(currentProjectPath)) {
            console.log('[HopeIDE] CubeMX project detected, loading from CubeMX files...');
            const cubemx = new CubeMXIntegration(currentProjectPath);
            cubemx.loadAll();
            const config = cubemx.getOptionsConfig();

            mainWindow.webContents.send('output-append',
                '📦 CubeMX project: Configuration loaded (READ-ONLY)\n');

            event.reply('options-loaded', config);
        } else {
            // Regular project
            if (!optionsManager) {
                optionsManager = new OptionsManager(currentProjectPath);
            }
            event.reply('options-loaded', optionsManager.options);
        }
    } catch (e) {
        console.error('[OptionsManager] Load error:', e);
        event.reply('options-loaded', {});
    }
});

ipcMain.on('save-options', async (event, options) => {
    if (!currentProjectPath) return;

    try {
        if (!optionsManager) {
            optionsManager = new OptionsManager(currentProjectPath);
        }
        optionsManager.options = { ...optionsManager.options, ...options };
        optionsManager.save();
        optionsManager.generateMakefile();

        if (mainWindow) {
            mainWindow.webContents.send('output-append', '✅ Options saved\n');
        }
    } catch (e) {
        console.error('[OptionsManager] Save error:', e);
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
