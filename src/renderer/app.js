const { ipcRenderer } = require('electron');
const fs = require('fs');
const path = require('path');
const { spawn } = require('child_process');

// Monaco Editor integration will be loaded from CDN or local copy
let editor = null;
let currentProject = null;
let openFiles = new Map();
let activeFile = null;

// Initialize application
function initApp() {
    console.log('Initializing ArmEditor...');

    // Load Monaco Editor
    loadMonacoEditor();

    // Setup terminal
    setupTerminal();

    // Listen to menu events
    setupMenuListeners();

    // Check for VS Code integration
    checkVSCodeIntegration();
}

// Load Monaco Editor
function loadMonacoEditor() {
    const script = document.createElement('script');
    script.src = 'https://cdnjs.cloudflare.com/ajax/libs/monaco-editor/0.44.0/min/vs/loader.min.js';
    script.onload = () => {
        require.config({ paths: { vs: 'https://cdnjs.cloudflare.com/ajax/libs/monaco-editor/0.44.0/min/vs' }});
        require(['vs/editor/editor.main'], function() {
            createEditor();
        });
    };
    document.head.appendChild(script);
}

function createEditor() {
    editor = monaco.editor.create(document.getElementById('editor'), {
        value: '',
        language: 'c',
        theme: 'vs-dark',
        automaticLayout: true,
        minimap: { enabled: true },
        fontSize: 14,
        fontFamily: "'Fira Code', 'Courier New', monospace",
        fontLigatures: true,
        scrollBeyondLastLine: false,
        renderWhitespace: 'selection',
        rulers: [80, 120],
        bracketPairColorization: { enabled: true },
        suggest: {
            showKeywords: true,
            showSnippets: true
        }
    });

    // Update line/col in status bar
    editor.onDidChangeCursorPosition((e) => {
        document.getElementById('status-line-col').textContent =
            `Ln ${e.position.lineNumber}, Col ${e.position.column}`;
    });

    console.log('Monaco Editor initialized');
}

// Setup terminal (xterm.js)
function setupTerminal() {
    const script = document.createElement('script');
    script.src = 'https://cdnjs.cloudflare.com/ajax/libs/xterm/5.3.0/xterm.min.js';
    script.onload = () => {
        const term = new Terminal({
            theme: {
                background: '#1e1e1e',
                foreground: '#d4d4d4'
            },
            fontSize: 13,
            fontFamily: "'Fira Code', 'Courier New', monospace",
            cursorBlink: true
        });
        term.open(document.getElementById('terminal'));
        term.writeln('ArmEditor Terminal - Ready');
        term.writeln('Type "help" for available commands\r\n');

        // Store terminal globally
        window.terminal = term;
    };
    document.head.appendChild(script);

    const css = document.createElement('link');
    css.rel = 'stylesheet';
    css.href = 'https://cdnjs.cloudflare.com/ajax/libs/xterm/5.3.0/xterm.min.css';
    document.head.appendChild(css);
}

// Menu event listeners
function setupMenuListeners() {
    ipcRenderer.on('menu-new-project', () => newProject());
    ipcRenderer.on('menu-open-project', () => openProject());
    ipcRenderer.on('menu-save', () => saveFile());
    ipcRenderer.on('menu-save-all', () => saveAllFiles());
    ipcRenderer.on('menu-build', () => buildProject());
    ipcRenderer.on('menu-clean', () => cleanProject());
    ipcRenderer.on('menu-rebuild', () => rebuildProject());
    ipcRenderer.on('menu-debug-start', () => startDebug());
    ipcRenderer.on('menu-debug-stop', () => stopDebug());
    ipcRenderer.on('menu-debug-step-over', () => debugStepOver());
    ipcRenderer.on('menu-debug-step-into', () => debugStepInto());
    ipcRenderer.on('menu-debug-step-out', () => debugStepOut());
    ipcRenderer.on('menu-toggle-terminal', () => toggleTerminal());
}

// Window controls
function minimizeWindow() {
    ipcRenderer.send('window-minimize');
}

function maximizeWindow() {
    ipcRenderer.send('window-maximize');
}

function closeWindow() {
    ipcRenderer.send('window-close');
}

// Project operations
function newProject() {
    const { dialog } = require('electron').remote || require('@electron/remote');

    dialog.showOpenDialog({
        properties: ['openDirectory', 'createDirectory'],
        title: 'Select Project Location'
    }).then(result => {
        if (!result.canceled && result.filePaths.length > 0) {
            const projectPath = result.filePaths[0];
            createNewProject(projectPath);
        }
    });
}

function createNewProject(projectPath) {
    // Create project structure
    const structure = {
        'src': {},
        'inc': {},
        'lib': {},
        'build': {},
        'Makefile': getMakefileTemplate(),
        '.vscode': {
            'tasks.json': getVSCodeTasksTemplate(),
            'launch.json': getVSCodeLaunchTemplate(),
            'c_cpp_properties.json': getVSCodeCppPropertiesTemplate(),
            'armeditor.json': getArmEditorConfigTemplate()
        }
    };

    createProjectStructure(projectPath, structure);
    loadProject(projectPath);

    console.log('New project created at:', projectPath);
}

function createProjectStructure(basePath, structure) {
    for (const [name, content] of Object.entries(structure)) {
        const fullPath = path.join(basePath, name);

        if (typeof content === 'object' && content !== null) {
            // Directory
            if (!fs.existsSync(fullPath)) {
                fs.mkdirSync(fullPath, { recursive: true });
            }
            createProjectStructure(fullPath, content);
        } else {
            // File
            fs.writeFileSync(fullPath, content);
        }
    }
}

function openProject() {
    const { dialog } = require('electron').remote || require('@electron/remote');

    dialog.showOpenDialog({
        properties: ['openDirectory'],
        title: 'Open Project'
    }).then(result => {
        if (!result.canceled && result.filePaths.length > 0) {
            loadProject(result.filePaths[0]);
        }
    });
}

function loadProject(projectPath) {
    currentProject = projectPath;
    document.getElementById('welcome-screen').style.display = 'none';
    document.getElementById('editor').style.display = 'block';

    // Load file tree
    loadFileTree(projectPath);

    // Notify VS Code if integration is active
    notifyVSCode('project-opened', { path: projectPath });
}

function loadFileTree(projectPath) {
    const fileTree = document.getElementById('file-tree');
    fileTree.innerHTML = '';

    function buildTree(dir, container) {
        const files = fs.readdirSync(dir);

        files.forEach(file => {
            const filePath = path.join(dir, file);
            const stat = fs.statSync(filePath);

            // Skip build directories and hidden files
            if (file.startsWith('.') && file !== '.vscode') return;
            if (file === 'build') return;

            const item = document.createElement('div');
            item.className = 'file-item';

            if (stat.isDirectory()) {
                item.innerHTML = `📁 ${file}`;
                item.onclick = () => {
                    item.classList.toggle('expanded');
                };
            } else {
                const icon = getFileIcon(file);
                item.innerHTML = `${icon} ${file}`;
                item.onclick = () => openFile(filePath);
            }

            container.appendChild(item);
        });
    }

    buildTree(projectPath, fileTree);
}

function getFileIcon(filename) {
    const ext = path.extname(filename).toLowerCase();
    const icons = {
        '.c': '📄',
        '.h': '📋',
        '.cpp': '📄',
        '.hpp': '📋',
        '.s': '📝',
        '.ld': '🔗',
        '.json': '⚙️',
        '.md': '📖',
        '.txt': '📝'
    };
    return icons[ext] || '📄';
}

function openFile(filePath) {
    const content = fs.readFileSync(filePath, 'utf-8');
    const filename = path.basename(filePath);

    // Add to open files
    openFiles.set(filePath, content);
    activeFile = filePath;

    // Update editor
    if (editor) {
        editor.setValue(content);
        const ext = path.extname(filePath).toLowerCase();
        const language = getLanguageFromExt(ext);
        monaco.editor.setModelLanguage(editor.getModel(), language);
    }

    // Add tab
    addTab(filename, filePath);
}

function getLanguageFromExt(ext) {
    const languages = {
        '.c': 'c',
        '.h': 'c',
        '.cpp': 'cpp',
        '.hpp': 'cpp',
        '.s': 'asm',
        '.ld': 'c',
        '.json': 'json',
        '.md': 'markdown',
        '.txt': 'plaintext'
    };
    return languages[ext] || 'plaintext';
}

function addTab(filename, filePath) {
    const tabs = document.getElementById('tabs');

    // Remove existing tab if present
    const existingTab = tabs.querySelector(`[data-path="${filePath}"]`);
    if (existingTab) {
        existingTab.classList.add('active');
        return;
    }

    // Remove active class from all tabs
    tabs.querySelectorAll('.tab').forEach(tab => tab.classList.remove('active'));

    const tab = document.createElement('div');
    tab.className = 'tab active';
    tab.dataset.path = filePath;
    tab.innerHTML = `
        ${getFileIcon(filename)} ${filename}
        <span class="tab-close" onclick="closeTab(event, '${filePath}')">✕</span>
    `;
    tab.onclick = () => switchTab(filePath);

    tabs.appendChild(tab);
}

function switchTab(filePath) {
    activeFile = filePath;
    const content = openFiles.get(filePath);

    if (editor && content) {
        editor.setValue(content);
    }

    // Update active tab
    document.querySelectorAll('.tab').forEach(tab => {
        tab.classList.toggle('active', tab.dataset.path === filePath);
    });
}

function closeTab(event, filePath) {
    event.stopPropagation();

    openFiles.delete(filePath);

    const tabs = document.getElementById('tabs');
    const tab = tabs.querySelector(`[data-path="${filePath}"]`);
    if (tab) {
        tab.remove();
    }

    // Open another tab if available
    if (openFiles.size > 0) {
        const [firstPath] = openFiles.keys();
        switchTab(firstPath);
    } else {
        editor.setValue('');
        document.getElementById('welcome-screen').style.display = 'flex';
        document.getElementById('editor').style.display = 'none';
    }
}

function saveFile() {
    if (!activeFile || !editor) return;

    const content = editor.getValue();
    fs.writeFileSync(activeFile, content);
    openFiles.set(activeFile, content);

    console.log('File saved:', activeFile);
}

function saveAllFiles() {
    openFiles.forEach((content, filePath) => {
        fs.writeFileSync(filePath, content);
    });

    console.log('All files saved');
}

// Build operations
function buildProject() {
    if (!currentProject) {
        alert('No project open');
        return;
    }

    executeCommand('make', ['all'], currentProject);
}

function cleanProject() {
    if (!currentProject) {
        alert('No project open');
        return;
    }

    executeCommand('make', ['clean'], currentProject);
}

function rebuildProject() {
    if (!currentProject) {
        alert('No project open');
        return;
    }

    executeCommand('make', ['clean'], currentProject, () => {
        executeCommand('make', ['all'], currentProject);
    });
}

function executeCommand(cmd, args, cwd, callback) {
    const term = window.terminal;
    if (!term) return;

    term.writeln(`\r\n$ ${cmd} ${args.join(' ')}`);

    const proc = spawn(cmd, args, { cwd, shell: true });

    proc.stdout.on('data', (data) => {
        term.write(data.toString().replace(/\n/g, '\r\n'));
    });

    proc.stderr.on('data', (data) => {
        term.write(`\x1b[31m${data.toString().replace(/\n/g, '\r\n')}\x1b[0m`);
    });

    proc.on('close', (code) => {
        if (code === 0) {
            term.writeln(`\x1b[32m✓ Success\x1b[0m\r\n`);
        } else {
            term.writeln(`\x1b[31m✗ Error (exit code: ${code})\x1b[0m\r\n`);
        }

        if (callback) callback(code);
    });
}

// Debug operations
function startDebug() {
    if (!currentProject) {
        alert('No project open');
        return;
    }

    // First build, then start debug
    executeCommand('make', ['debug'], currentProject, (code) => {
        if (code === 0) {
            launchDebugger();
        }
    });
}

function launchDebugger() {
    // Launch OpenOCD + GDB
    const term = window.terminal;
    term.writeln('\r\n🔍 Starting debugger...\r\n');

    // This will be implemented with GDB integration
    executeCommand('openocd', ['-f', 'openocd.cfg'], currentProject);

    // Notify VS Code debugger if integration is active
    notifyVSCode('debug-start', { project: currentProject });
}

function stopDebug() {
    const term = window.terminal;
    term.writeln('\r\n⏹️ Stopping debugger...\r\n');

    // Kill OpenOCD and GDB processes
    // Implementation here

    notifyVSCode('debug-stop', {});
}

function debugStepOver() {
    // Send GDB command: next
    notifyVSCode('debug-step-over', {});
}

function debugStepInto() {
    // Send GDB command: step
    notifyVSCode('debug-step-into', {});
}

function debugStepOut() {
    // Send GDB command: finish
    notifyVSCode('debug-step-out', {});
}

function flashDevice() {
    if (!currentProject) {
        alert('No project open');
        return;
    }

    executeCommand('make', ['flash'], currentProject);
}

// Bottom panel
function switchBottomTab(tab) {
    document.querySelectorAll('.bottom-tab').forEach(t => {
        t.classList.remove('active');
    });
    event.target.classList.add('active');
}

function toggleTerminal() {
    const panel = document.querySelector('.bottom-panel');
    panel.style.display = panel.style.display === 'none' ? 'flex' : 'none';
}

// VS Code Integration
function checkVSCodeIntegration() {
    // Check if running as VS Code task or from VS Code
    if (process.env.VSCODE_PID || process.env.TERM_PROGRAM === 'vscode') {
        console.log('VS Code integration detected');
        enableVSCodeIntegration();
    }
}

function enableVSCodeIntegration() {
    // Start WebSocket server for VS Code communication
    const WebSocket = require('ws');
    const wss = new WebSocket.Server({ port: 9876 });

    wss.on('connection', (ws) => {
        console.log('VS Code connected');

        ws.on('message', (message) => {
            const data = JSON.parse(message);
            handleVSCodeMessage(data);
        });

        window.vscodeWS = ws;
    });
}

function notifyVSCode(event, data) {
    if (window.vscodeWS && window.vscodeWS.readyState === 1) {
        window.vscodeWS.send(JSON.stringify({ event, data }));
    }
}

function handleVSCodeMessage(message) {
    switch(message.event) {
        case 'open-file':
            openFile(message.data.path);
            break;
        case 'build':
            buildProject();
            break;
        case 'debug':
            startDebug();
            break;
    }
}

// Templates
function getMakefileTemplate() {
    return `# ARM Makefile Template
PROJECT = arm_project
BUILD_DIR = build

# Toolchain
PREFIX = arm-none-eabi-
CC = \${PREFIX}gcc
AS = \${PREFIX}as
LD = \${PREFIX}ld
OBJCOPY = \${PREFIX}objcopy
SIZE = \${PREFIX}size

# MCU
MCU = cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard

# Compiler flags
CFLAGS = -mcpu=\${MCU} \${FPU} \${FLOAT-ABI} -mthumb
CFLAGS += -Wall -Wextra -Os -g3

# Linker flags
LDFLAGS = -mcpu=\${MCU} \${FPU} \${FLOAT-ABI} -mthumb

# Sources
C_SOURCES = \$(wildcard src/*.c)
ASM_SOURCES = \$(wildcard src/*.s)

# Build
all:
\t@echo "Building \${PROJECT}..."
\t\${CC} \${CFLAGS} \${C_SOURCES} \${ASM_SOURCES} -o \${BUILD_DIR}/\${PROJECT}.elf
\t\${SIZE} \${BUILD_DIR}/\${PROJECT}.elf

clean:
\t@rm -rf \${BUILD_DIR}/*

debug: CFLAGS += -O0 -g3
debug: all

flash:
\topenocd -f openocd.cfg -c "program \${BUILD_DIR}/\${PROJECT}.elf verify reset exit"

.PHONY: all clean debug flash
`;
}

function getVSCodeTasksTemplate() {
    return JSON.stringify({
        "version": "2.0.0",
        "tasks": [
            {
                "label": "Build with ArmEditor",
                "type": "shell",
                "command": "armeditor",
                "args": ["--build"],
                "group": {
                    "kind": "build",
                    "isDefault": true
                }
            }
        ]
    }, null, 2);
}

function getVSCodeLaunchTemplate() {
    return JSON.stringify({
        "version": "0.2.0",
        "configurations": [
            {
                "name": "Debug with ArmEditor",
                "type": "armeditor",
                "request": "launch",
                "program": "${workspaceFolder}/build/arm_project.elf"
            }
        ]
    }, null, 2);
}

function getVSCodeCppPropertiesTemplate() {
    return JSON.stringify({
        "configurations": [
            {
                "name": "ARM",
                "includePath": [
                    "${workspaceFolder}/**"
                ],
                "defines": [],
                "compilerPath": "/usr/bin/arm-none-eabi-gcc",
                "cStandard": "c11",
                "cppStandard": "c++17",
                "intelliSenseMode": "gcc-arm"
            }
        ],
        "version": 4
    }, null, 2);
}

function getArmEditorConfigTemplate() {
    return JSON.stringify({
        "name": "ARM Project",
        "type": "arm-cortex-m",
        "mcu": "STM32F4",
        "buildSystem": "make",
        "debugger": {
            "type": "openocd",
            "interface": "stlink-v2",
            "target": "stm32f4x"
        },
        "armeditor": {
            "version": "1.0.0",
            "integration": {
                "vscode": true,
                "standalone": true
            }
        }
    }, null, 2);
}

// Initialize on load
window.addEventListener('DOMContentLoaded', initApp);
