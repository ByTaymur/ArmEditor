/**
 * HopeIDE - Electron Main Process
 * Native Desktop Application
 */

const { app, BrowserWindow, ipcMain, dialog, Menu } = require('electron');
const path = require('path');
const fs = require('fs');
const { spawn, execSync } = require('child_process');

// Debug modules
const GDBInterface = require('../debugger/gdb-interface');
const { OpenOCDFlasher } = require('../compiler/arm-toolchain');

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

// Debug state
let gdbInterface = null;
let openocdFlasher = null;
let openocdProcess = null;
let debugActive = false;

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
    }).catch(err => {
        dialog.showErrorBox('Error', `Failed to open dialog: ${err.message}`);
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
    }).catch(err => {
        dialog.showErrorBox('Error', `Failed to open project: ${err.message}`);
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
    }).catch(err => {
        dialog.showErrorBox('Error', `Failed to save file: ${err.message}`);
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
async function startDebug() {
    if (debugActive) {
        mainWindow.webContents.send('output-append', '⚠️ Debug already running\n');
        return;
    }

    if (!currentProjectPath) {
        dialog.showErrorBox('Error', 'No project opened');
        return;
    }

    mainWindow.webContents.send('output-append', '\n🔍 Starting debugger...\n');

    // Find .elf file
    const elfFiles = findFiles(currentProjectPath, '.elf');
    if (elfFiles.length === 0) {
        mainWindow.webContents.send('output-append', '❌ No .elf file found. Build first!\n');
        return;
    }

    const elfFile = elfFiles[0];
    mainWindow.webContents.send('output-append', `📁 Using: ${path.basename(elfFile)}\n`);

    try {
        // Initialize OpenOCD flasher - auto-detect will determine the target
        openocdFlasher = new OpenOCDFlasher({
            autoDetect: true  // Auto-detect connected STM32
        });

        // Start OpenOCD server
        mainWindow.webContents.send('output-append', '🔌 Starting OpenOCD server...\n');
        const serverResult = await openocdFlasher.startDebugServer((type, text) => {
            mainWindow.webContents.send('output-append', text);
        });
        openocdProcess = serverResult.process;

        mainWindow.webContents.send('output-append', '✅ OpenOCD server started\n');

        // Initialize GDB interface
        gdbInterface = new GDBInterface({
            elfFile: elfFile,
            port: 3333,
            commandTimeout: 10000
        });

        gdbInterface.on('output', (line) => {
            if (line.includes('^error')) {
                mainWindow.webContents.send('output-append', `❌ GDB Error: ${line}\n`);
            }
        });

        gdbInterface.on('stopped', (info) => {
            mainWindow.webContents.send('debug-status-update', 'Stopped');
            refreshDebugInfo();
        });

        gdbInterface.on('error', (err) => {
            mainWindow.webContents.send('output-append', `❌ Error: ${err}\n`);
        });

        // Start GDB
        mainWindow.webContents.send('output-append', '🔗 Connecting GDB...\n');
        await gdbInterface.start();

        debugActive = true;
        mainWindow.webContents.send('output-append', '✅ Debug session started!\n');
        mainWindow.webContents.send('debug-status-update', 'Running');

        // Initial register read
        refreshDebugInfo();

    } catch (error) {
        mainWindow.webContents.send('output-append', `❌ Debug start failed: ${error.message}\n`);
        await stopDebug();
    }
}

async function stopDebug() {
    mainWindow.webContents.send('output-append', '\n⏹️ Stopping debugger...\n');

    try {
        if (gdbInterface) {
            await gdbInterface.stop();
            gdbInterface = null;
        }
    } catch (e) {
        // Ignore
    }

    try {
        if (openocdProcess) {
            openocdProcess.kill();
            openocdProcess = null;
        }
    } catch (e) {
        // Ignore
    }

    // Kill any remaining OpenOCD processes
    try {
        if (process.platform === 'linux' || process.platform === 'darwin') {
            execSync('pkill -9 -f openocd 2>/dev/null || true', { stdio: 'ignore' });
        }
    } catch (e) {
        // Ignore
    }

    debugActive = false;
    mainWindow.webContents.send('output-append', '✅ Debugger stopped\n');
    mainWindow.webContents.send('debug-status-update', 'Stopped');
}

async function refreshDebugInfo() {
    if (!gdbInterface || !debugActive) return;

    try {
        const registers = await gdbInterface.readAllRegisters(5000);
        mainWindow.webContents.send('debug-registers', registers);
    } catch (e) {
        mainWindow.webContents.send('output-append', `⚠️ Register read error: ${e.message}\n`);
    }
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
function findFiles(dir, ext, fileList = [], depth = 0) {
    if (depth > 10) return fileList; // Prevent infinite recursion

    try {
        if (!fs.existsSync(dir)) return fileList;

        const files = fs.readdirSync(dir);

        files.forEach(file => {
            try {
                const filePath = path.join(dir, file);
                const stat = fs.statSync(filePath);

                if (stat.isDirectory() && !file.startsWith('.')) {
                    findFiles(filePath, ext, fileList, depth + 1);
                } else if (file.endsWith(ext)) {
                    fileList.push(filePath);
                }
            } catch (err) {
                // Skip files we can't access
            }
        });
    } catch (err) {
        console.error(`Error reading directory ${dir}: ${err.message}`);
    }

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

// File tree click handler
ipcMain.on('open-file-path', (event, filePath) => {
    try {
        const content = fs.readFileSync(filePath, 'utf-8');
        const fileName = path.basename(filePath);
        currentFilePath = filePath;

        mainWindow.webContents.send('open-file', {
            path: filePath,
            name: fileName,
            content: content
        });
    } catch (err) {
        mainWindow.webContents.send('output-append', `❌ Error opening file: ${err.message}\n`);
    }
});


// Debug IPC Handlers
ipcMain.on('debug-start', () => startDebug());
ipcMain.on('debug-stop', () => stopDebug());

ipcMain.on('debug-continue', async () => {
    if (gdbInterface && debugActive) {
        try {
            await gdbInterface.continue();
            mainWindow.webContents.send('debug-status-update', 'Running');
        } catch (e) {
            mainWindow.webContents.send('output-append', `❌ Continue failed: ${e.message}\n`);
        }
    }
});

// Target Setup IPC Handlers
ipcMain.on('get-target-info', async () => {
    try {
        const detector = new STM32Detector();
        // We use a quick detection
        const result = await detector.readIDCODE();

        // Find chip name from database
        let chipName = 'Unknown';
        for (const [family, chips] of Object.entries(detector.idcodeDatabase)) {
            for (const [name, idcode] of Object.entries(chips)) {
                if (idcode.toLowerCase() === result.idcode.toLowerCase()) {
                    chipName = name;
                    break;
                }
            }
        }

        mainWindow.webContents.send('target-info-result', {
            stlink: result.stlink,
            chip: {
                idcode: result.idcode,
                name: chipName,
                voltage: result.voltage
            }
        });
    } catch (err) {
        // Send empty/error result
        mainWindow.webContents.send('target-info-result', {
            error: err.message
        });
    }
});

ipcMain.on('save-target-settings', (event, settings) => {
    // Store settings for future use (e.g. in OpenOCDFlasher)
    global.targetSettings = settings;
    mainWindow.webContents.send('output-append', '✅ Target settings saved\n');
});

ipcMain.on('debug-pause', async () => {
    if (gdbInterface && debugActive) {
        try {
            await gdbInterface.pause();
            mainWindow.webContents.send('debug-status-update', 'Paused');
            refreshDebugInfo();
        } catch (e) {
            mainWindow.webContents.send('output-append', `❌ Pause failed: ${e.message}\n`);
        }
    }
});

ipcMain.on('debug-step-over', async () => {
    if (gdbInterface && debugActive) {
        try {
            await gdbInterface.stepOver();
            refreshDebugInfo();
        } catch (e) {
            mainWindow.webContents.send('output-append', `❌ Step over failed: ${e.message}\n`);
        }
    }
});

ipcMain.on('debug-step-into', async () => {
    if (gdbInterface && debugActive) {
        try {
            await gdbInterface.stepInto();
            refreshDebugInfo();
        } catch (e) {
            mainWindow.webContents.send('output-append', `❌ Step into failed: ${e.message}\n`);
        }
    }
});

ipcMain.on('debug-step-out', async () => {
    if (gdbInterface && debugActive) {
        try {
            await gdbInterface.stepOut();
            refreshDebugInfo();
        } catch (e) {
            mainWindow.webContents.send('output-append', `❌ Step out failed: ${e.message}\n`);
        }
    }
});

ipcMain.on('debug-reset', async () => {
    mainWindow.webContents.send('output-append', '🔄 Resetting target...\n');
    if (gdbInterface && debugActive) {
        try {
            gdbInterface.sendCommand('monitor reset halt');
            await new Promise(resolve => setTimeout(resolve, 500));
            refreshDebugInfo();
            mainWindow.webContents.send('output-append', '✅ Reset complete\n');
        } catch (e) {
            mainWindow.webContents.send('output-append', `❌ Reset failed: ${e.message}\n`);
        }
    }
});

ipcMain.on('debug-read-memory', async (event, address) => {
    if (gdbInterface && debugActive) {
        try {
            const memory = await gdbInterface.readMemory(address, 64);
            const hexStr = memory.map(b => b.toString(16).padStart(2, '0')).join(' ');
            mainWindow.webContents.send('debug-memory', hexStr);
        } catch (e) {
            mainWindow.webContents.send('debug-memory', `Error: ${e.message}`);
        }
    }
});

ipcMain.on('debug-add-breakpoint', async (event, location) => {
    if (gdbInterface && debugActive) {
        try {
            const [file, line] = location.split(':');
            await gdbInterface.setBreakpoint(file, parseInt(line));
            mainWindow.webContents.send('output-append', `🔴 Breakpoint set: ${location}\n`);
        } catch (e) {
            mainWindow.webContents.send('output-append', `❌ Breakpoint failed: ${e.message}\n`);
        }
    }
});

ipcMain.on('flash-device', async () => {
    if (!currentProjectPath) {
        dialog.showErrorBox('Error', 'No project opened');
        return;
    }

    const elfFiles = findFiles(currentProjectPath, '.elf');
    if (elfFiles.length === 0) {
        mainWindow.webContents.send('output-append', '❌ No .elf file found. Build first!\n');
        return;
    }

    mainWindow.webContents.send('output-append', '\n⚡ Flashing firmware...\n');

    try {
        const flasher = new OpenOCDFlasher({
            autoDetect: true,  // Auto-detect connected STM32
            timeout: 60000
        });

        await flasher.flash(elfFiles[0], (type, text) => {
            mainWindow.webContents.send('output-append', text);
        });

        mainWindow.webContents.send('output-append', '✅ Flash successful!\n');
    } catch (e) {
        mainWindow.webContents.send('output-append', `❌ Flash failed: ${e.error || e.message}\n`);
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
