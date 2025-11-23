/**
 * Register Viewer Provider
 * Displays CPU registers in a Webview panel
 */

import * as vscode from 'vscode';
import { GDBBackend } from '../services/gdbBackend';

export class RegisterViewerProvider implements vscode.WebviewViewProvider {
    private _view?: vscode.WebviewView;
    private gdb?: GDBBackend;

    constructor(private readonly extensionUri: vscode.Uri) { }

    public setGDB(gdb: GDBBackend) {
        this.gdb = gdb;
        this.updateRegisters();
    }

    public resolveWebviewView(
        webviewView: vscode.WebviewView,
        context: vscode.WebviewViewResolveContext,
        _token: vscode.CancellationToken
    ) {
        this._view = webviewView;

        webviewView.webview.options = {
            enableScripts: true,
            localResourceRoots: [this.extensionUri]
        };

        webviewView.webview.html = this.getHtmlForWebview(webviewView.webview);

        // Handle messages from webview
        webviewView.webview.onDidReceiveMessage(data => {
            switch (data.type) {
                case 'refresh':
                    this.updateRegisters();
                    break;
            }
        });
    }

    private async updateRegisters() {
        if (!this.gdb || !this._view) return;

        try {
            const registers = await this.gdb.readRegisters();
            this._view.webview.postMessage({
                type: 'update',
                registers
            });
        } catch (error) {
            // Silently fail during update
        }
    }

    private getHtmlForWebview(webview: vscode.Webview): string {
        return `<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Registers</title>
    <style>
        body {
            padding: 10px;
            font-family: var(--vscode-font-family);
            font-size: var(--vscode-font-size);
            color: var(--vscode-foreground);
        }
        
        table {
            width: 100%;
            border-collapse: collapse;
        }
        
        th, td {
            padding: 8px;
            text-align: left;
            border-bottom: 1px solid var(--vscode-panel-border);
        }
        
        th {
            background-color: var(--vscode-editor-background);
            font-weight: bold;
        }
        
        tr:hover {
            background-color: var(--vscode-list-hoverBackground);
        }
        
        .changed {
            color: var(--vscode-gitDecoration-modifiedResourceForeground);
            font-weight: bold;
        }
        
        button {
            background-color: var(--vscode-button-background);
            color: var(--vscode-button-foreground);
            border: none;
            padding: 8px 16px;
            cursor: pointer;
            margin-bottom: 10px;
        }
        
        button:hover {
            background-color: var(--vscode-button-hoverBackground);
        }
    </style>
</head>
<body>
    <button onclick="refresh()">🔄 Refresh</button>
    
    <table id="registers">
        <thead>
            <tr>
                <th>Register</th>
                <th>Value</th>
                <th>Decimal</th>
            </tr>
        </thead>
        <tbody id="tbody">
            <tr><td colspan="3">No data yet. Start debugging...</td></tr>
        </tbody>
    </table>
    
    <script>
        const vscode = acquireVsCodeApi();
        let previousValues = {};
        
        window.addEventListener('message', event => {
            const message = event.data;
            
            switch (message.type) {
                case 'update':
                    updateTable(message.registers);
                    break;
            }
        });
        
        function updateTable(registers) {
            const tbody = document.getElementById('tbody');
            tbody.innerHTML = '';
            
            const regNames = ['r0', 'r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7',
                            'r8', 'r9', 'r10', 'r11', 'r12', 'sp', 'lr', 'pc'];
            
            regNames.forEach(name => {
                const row = document.createElement('tr');
                const value = registers[name] || '0x00000000';
                const isChanged = previousValues[name] && previousValues[name] !== value;
                
                row.innerHTML = \`
                    <td>\${name.toUpperCase()}</td>
                    <td class="\${isChanged ? 'changed' : ''}">\${value}</td>
                    <td>\${parseInt(value, 16)}</td>
                \`;
                
                tbody.appendChild(row);
                previousValues[name] = value;
            });
        }
        
        function refresh() {
            vscode.postMessage({ type: 'refresh' });
        }
    </script>
</body>
</html>`;
    }
}
