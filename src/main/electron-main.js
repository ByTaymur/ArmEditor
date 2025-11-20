/**
 * ArmEditor - Electron Main Process
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
        title: 'ArmEditor - Professional ARM IDE',
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
        console.log('ArmEditor window ready');
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
                    label: 'About ArmEditor',
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
function buildProject() {
    if (!currentProjectPath) {
        dialog.showErrorBox('Error', 'No project opened');
        return;
    }

    mainWindow.webContents.send('output-clear');
    mainWindow.webContents.send('output-append', '🔨 Building project...\n');

    const make = spawn('make', ['all'], {
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
            mainWindow.webContents.send('output-append', '\n✅ Build successful!\n');
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
        title: 'About ArmEditor',
        message: 'ArmEditor v1.0.0',
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
ipcMain.on('build-project', () => {
    console.log('[IPC] build-project received');
    buildProject();
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
    switch(ext) {
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

// Connect to ST-Link and read MCU info
ipcMain.on('connect-stlink', async (event, deviceId) => {
    try {
        const device = stlinkDevices.find(d => d.id === deviceId);
        if (!device) {
            mainWindow.webContents.send('output-append', `❌ Device not found\n`);
            return;
        }

        mainWindow.webContents.send('output-append', `🔌 Connecting to ${device.name}...\n`);

        // Start OpenOCD
        const openocd = new OpenOCDInterface();

        // Listen to OpenOCD output
        openocd.on('output', (data) => {
            console.log('[OpenOCD]', data);
        });

        try {
            await openocd.start('stm32f4x', 'stlink');
            mainWindow.webContents.send('output-append', '✅ OpenOCD started\n');
        } catch (err) {
            // Check for common errors
            if (err.message.includes('USB permission')) {
                mainWindow.webContents.send('output-append',
                    `❌ USB Permission Error!\n` +
                    `   Run: sudo dpkg-reconfigure armeditor\n` +
                    `   Or: sudo udevadm control --reload-rules && sudo udevadm trigger\n`
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

        // Get device info using STM32Tools
        const stm32Tools = new STM32Tools(openocd);
        const deviceInfo = await stm32Tools.getDeviceInfo();

        mainWindow.webContents.send('output-append',
            `📱 MCU: ${deviceInfo.deviceName}\n` +
            `   ID: ${deviceInfo.deviceID}\n` +
            `   Flash: ${deviceInfo.flash.sizeKB} KB\n`
        );

        // Update device with MCU info
        device.connected = true;
        device.mcu = {
            name: deviceInfo.deviceName,
            deviceId: deviceInfo.deviceID,
            flashSize: deviceInfo.flash.sizeKB + ' KB',
            revisionId: deviceInfo.revisionID
        };

        connectedStLink = {
            id: deviceId,
            openocd: openocd,
            mcu: device.mcu
        };

        // Send updated devices
        mainWindow.webContents.send('stlink-devices', stlinkDevices);

    } catch (error) {
        console.error('[ST-Link Connect Error]', error);
        mainWindow.webContents.send('output-append', `❌ Connection failed: ${error.message}\n`);
    }
});

// Disconnect ST-Link
ipcMain.on('disconnect-stlink', async (event, deviceId) => {
    try {
        if (connectedStLink && connectedStLink.openocd) {
            await connectedStLink.openocd.stop();
        }

        const device = stlinkDevices.find(d => d.id === deviceId);
        if (device) {
            device.connected = false;
            device.mcu = null;
        }

        connectedStLink = null;

        mainWindow.webContents.send('output-append', '🔴 ST-Link disconnected\n');
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
        defaultPath: path.join(app.getPath('documents'), 'armeditor-log.txt'),
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
        const memoryData = await stm32Tools.readMemory(address, size);

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
    if (process.platform !== 'darwin') {
        app.quit();
    }
});

console.log('ArmEditor Electron app started');
