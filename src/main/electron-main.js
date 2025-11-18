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

    // Load the HTML file
    mainWindow.loadFile(path.join(__dirname, '../renderer/ide.html'));

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

            mainWindow.webContents.send('open-project', projectInfo);
            mainWindow.webContents.send('output-append',
                `✅ Project loaded: ${path.basename(currentProjectPath)}\n` +
                `   Files: ${projectInfo.files.length}\n` +
                `   Type: ${projectInfo.type}\n`
            );
        }
    });
}

function parseProjectStructure(projectPath) {
    const files = [];
    const info = {
        path: projectPath,
        name: path.basename(projectPath),
        type: 'unknown',
        files: [],
        iocFile: null,
        makefile: null
    };

    // Check for CubeMX project (.ioc file)
    const iocFiles = fs.readdirSync(projectPath).filter(f => f.endsWith('.ioc'));
    if (iocFiles.length > 0) {
        info.type = 'STM32CubeMX';
        info.iocFile = path.join(projectPath, iocFiles[0]);
    }

    // Check for Makefile
    const makefilePath = path.join(projectPath, 'Makefile');
    if (fs.existsSync(makefilePath)) {
        info.makefile = makefilePath;
        if (info.type === 'unknown') info.type = 'Makefile';
    }

    // Recursively find all source files
    function scanDirectory(dir, baseDir = dir) {
        const items = fs.readdirSync(dir);

        for (const item of items) {
            const fullPath = path.join(dir, item);
            const stats = fs.statSync(fullPath);

            if (stats.isDirectory()) {
                // Skip build directories
                if (!['build', 'Build', 'Debug', 'Release', '.git'].includes(item)) {
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

    scanDirectory(projectPath);
    info.files = files;

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
    try {
        if (!filePath && debugSession.elfFile) {
            filePath = debugSession.elfFile.replace('.elf', '.hex');
        }

        if (!filePath) {
            mainWindow.webContents.send('output-append', '❌ No file to flash\n');
            return;
        }

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
