const WebSocket = require('ws');
const fs = require('fs');
const path = require('path');

/**
 * VS Code Integration Bridge
 * Allows ArmEditor to communicate with VS Code via WebSocket
 */
class VSCodeBridge {
    constructor(port = 9876) {
        this.port = port;
        this.server = null;
        this.clients = new Set();
        this.callbacks = new Map();
    }

    start() {
        this.server = new WebSocket.Server({ port: this.port });

        this.server.on('connection', (ws) => {
            console.log('VS Code client connected');
            this.clients.add(ws);

            ws.on('message', (message) => {
                this.handleMessage(ws, message);
            });

            ws.on('close', () => {
                console.log('VS Code client disconnected');
                this.clients.delete(ws);
            });

            ws.on('error', (error) => {
                console.error('WebSocket error:', error);
            });

            // Send handshake
            this.send(ws, {
                type: 'handshake',
                data: {
                    version: '1.0.0',
                    capabilities: [
                        'build',
                        'debug',
                        'flash',
                        'editor-sync'
                    ]
                }
            });
        });

        console.log(`VS Code Bridge listening on port ${this.port}`);
    }

    handleMessage(ws, message) {
        try {
            const data = JSON.parse(message);

            switch(data.type) {
                case 'open-file':
                    this.emit('open-file', data.data);
                    break;

                case 'save-file':
                    this.emit('save-file', data.data);
                    break;

                case 'build':
                    this.emit('build', data.data);
                    break;

                case 'debug-start':
                    this.emit('debug-start', data.data);
                    break;

                case 'debug-stop':
                    this.emit('debug-stop', data.data);
                    break;

                case 'debug-step-over':
                    this.emit('debug-step-over', data.data);
                    break;

                case 'debug-step-into':
                    this.emit('debug-step-into', data.data);
                    break;

                case 'debug-step-out':
                    this.emit('debug-step-out', data.data);
                    break;

                case 'set-breakpoint':
                    this.emit('set-breakpoint', data.data);
                    break;

                case 'remove-breakpoint':
                    this.emit('remove-breakpoint', data.data);
                    break;

                case 'evaluate-expression':
                    this.handleEvaluateExpression(ws, data.data);
                    break;

                default:
                    console.log('Unknown message type:', data.type);
            }
        } catch (error) {
            console.error('Error handling message:', error);
        }
    }

    send(ws, data) {
        if (ws.readyState === WebSocket.OPEN) {
            ws.send(JSON.stringify(data));
        }
    }

    broadcast(data) {
        this.clients.forEach(client => {
            this.send(client, data);
        });
    }

    // Events to VS Code
    notifyBuildStarted(project) {
        this.broadcast({
            type: 'build-started',
            data: { project }
        });
    }

    notifyBuildCompleted(success, output) {
        this.broadcast({
            type: 'build-completed',
            data: { success, output }
        });
    }

    notifyDebugStarted() {
        this.broadcast({
            type: 'debug-started',
            data: {}
        });
    }

    notifyDebugStopped(reason, line, file) {
        this.broadcast({
            type: 'debug-stopped',
            data: { reason, line, file }
        });
    }

    notifyBreakpointHit(id, line, file) {
        this.broadcast({
            type: 'breakpoint-hit',
            data: { id, line, file }
        });
    }

    notifyVariableChanged(name, value) {
        this.broadcast({
            type: 'variable-changed',
            data: { name, value }
        });
    }

    // VS Code Extension API
    async handleEvaluateExpression(ws, data) {
        // This will be handled by GDB interface
        this.emit('evaluate-expression', {
            expression: data.expression,
            callback: (result) => {
                this.send(ws, {
                    type: 'expression-result',
                    data: {
                        expression: data.expression,
                        result
                    }
                });
            }
        });
    }

    emit(event, data) {
        if (this.callbacks.has(event)) {
            this.callbacks.get(event).forEach(callback => callback(data));
        }
    }

    on(event, callback) {
        if (!this.callbacks.has(event)) {
            this.callbacks.set(event, []);
        }
        this.callbacks.get(event).push(callback);
    }

    stop() {
        if (this.server) {
            this.clients.forEach(client => client.close());
            this.server.close();
            console.log('VS Code Bridge stopped');
        }
    }
}

/**
 * Generate VS Code Extension for ArmEditor
 */
function generateVSCodeExtension(outputPath) {
    const extensionPath = path.join(outputPath, 'armeditor-vscode');

    if (!fs.existsSync(extensionPath)) {
        fs.mkdirSync(extensionPath, { recursive: true });
    }

    // package.json
    const packageJson = {
        "name": "armeditor-vscode",
        "displayName": "ArmEditor Integration",
        "description": "VS Code integration for ArmEditor ARM Development IDE",
        "version": "1.0.0",
        "publisher": "armeditor",
        "engines": {
            "vscode": "^1.80.0"
        },
        "categories": ["Debuggers", "Programming Languages"],
        "activationEvents": [
            "onDebugResolve:armeditor",
            "onCommand:armeditor.build",
            "onCommand:armeditor.flash",
            "workspaceContains:.vscode/armeditor.json"
        ],
        "main": "./extension.js",
        "contributes": {
            "commands": [
                {
                    "command": "armeditor.build",
                    "title": "ArmEditor: Build Project"
                },
                {
                    "command": "armeditor.clean",
                    "title": "ArmEditor: Clean Project"
                },
                {
                    "command": "armeditor.flash",
                    "title": "ArmEditor: Flash Device"
                },
                {
                    "command": "armeditor.openIDE",
                    "title": "ArmEditor: Open in ArmEditor IDE"
                }
            ],
            "debuggers": [
                {
                    "type": "armeditor",
                    "label": "ArmEditor Debug",
                    "program": "./debugAdapter.js",
                    "runtime": "node",
                    "configurationAttributes": {
                        "launch": {
                            "required": ["program"],
                            "properties": {
                                "program": {
                                    "type": "string",
                                    "description": "Path to ELF file"
                                },
                                "openocdConfig": {
                                    "type": "string",
                                    "description": "OpenOCD configuration file"
                                }
                            }
                        }
                    }
                }
            ],
            "taskDefinitions": [
                {
                    "type": "armeditor",
                    "required": ["task"],
                    "properties": {
                        "task": {
                            "type": "string",
                            "description": "The ArmEditor task to run"
                        }
                    }
                }
            ]
        }
    };

    fs.writeFileSync(
        path.join(extensionPath, 'package.json'),
        JSON.stringify(packageJson, null, 2)
    );

    // extension.js
    const extensionJs = `
const vscode = require('vscode');
const WebSocket = require('ws');

let ws = null;

function activate(context) {
    console.log('ArmEditor extension activated');

    // Connect to ArmEditor
    connectToArmEditor();

    // Register commands
    context.subscriptions.push(
        vscode.commands.registerCommand('armeditor.build', () => {
            sendToArmEditor({ type: 'build' });
        })
    );

    context.subscriptions.push(
        vscode.commands.registerCommand('armeditor.clean', () => {
            sendToArmEditor({ type: 'clean' });
        })
    );

    context.subscriptions.push(
        vscode.commands.registerCommand('armeditor.flash', () => {
            sendToArmEditor({ type: 'flash' });
        })
    );

    context.subscriptions.push(
        vscode.commands.registerCommand('armeditor.openIDE', () => {
            const { exec } = require('child_process');
            exec('armeditor');
        })
    );
}

function connectToArmEditor() {
    try {
        ws = new WebSocket('ws://localhost:9876');

        ws.on('open', () => {
            console.log('Connected to ArmEditor');
        });

        ws.on('message', (message) => {
            const data = JSON.parse(message);
            handleArmEditorMessage(data);
        });

        ws.on('close', () => {
            console.log('Disconnected from ArmEditor');
            // Reconnect after 5 seconds
            setTimeout(connectToArmEditor, 5000);
        });

    } catch (error) {
        console.error('Failed to connect to ArmEditor:', error);
    }
}

function sendToArmEditor(data) {
    if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify(data));
    } else {
        vscode.window.showErrorMessage('ArmEditor is not running');
    }
}

function handleArmEditorMessage(data) {
    switch(data.type) {
        case 'build-completed':
            if (data.data.success) {
                vscode.window.showInformationMessage('Build successful');
            } else {
                vscode.window.showErrorMessage('Build failed');
            }
            break;

        case 'debug-stopped':
            // Update debug UI
            break;
    }
}

function deactivate() {
    if (ws) {
        ws.close();
    }
}

module.exports = {
    activate,
    deactivate
};
`;

    fs.writeFileSync(
        path.join(extensionPath, 'extension.js'),
        extensionJs
    );

    console.log(`VS Code extension generated at: ${extensionPath}`);
    console.log('Install with: code --install-extension ' + extensionPath);
}

module.exports = {
    VSCodeBridge,
    generateVSCodeExtension
};
