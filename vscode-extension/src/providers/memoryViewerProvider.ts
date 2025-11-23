/**
 * Memory Viewer Provider
 * Hex viewer with ASCII display
 */

import * as vscode from 'vscode';
import { GDBBackend } from '../services/gdbBackend';

export class MemoryViewerProvider implements vscode.WebviewViewProvider {
    private _view?: vscode.WebviewView;
    private gdb?: GDBBackend;
    private currentAddress: string = '0x20000000';

    constructor(private readonly extensionUri: vscode.Uri) { }

    public setGDB(gdb: GDBBackend) {
        this.gdb = gdb;
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

        webviewView.webview.onDidReceiveMessage(async data => {
            switch (data.type) {
                case 'read':
                    this.currentAddress = data.address;
                    await this.readMemory(data.address, data.length || 256);
                    break;
            }
        });
    }

    private async readMemory(address: string, length: number) {
        if (!this.gdb || !this._view) return;

        try {
            const memory = await this.gdb.readMemory(address, length);
            this._view.webview.postMessage({
                type: 'update',
                address,
                memory
            });
        } catch (error: any) {
            vscode.window.showErrorMessage(`Memory read failed: ${error.message}`);
        }
    }

    private getHtmlForWebview(webview: vscode.Webview): string {
        return `<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Memory Viewer</title>
    <style>
        body {
            padding: 10px;
            font-family: 'Courier New', monospace;
            font-size: 12px;
            color: var(--vscode-foreground);
        }
        
        .controls {
            margin-bottom: 10px;
        }
        
        input {
            background-color: var(--vscode-input-background);
            color: var(--vscode-input-foreground);
            border: 1px solid var(--vscode-input-border);
            padding: 4px 8px;
            width: 120px;
        }
        
        button {
            background-color: var(--vscode-button-background);
            color: var(--vscode-button-foreground);
            border: none;
            padding: 4px 12px;
            cursor: pointer;
            margin-left: 5px;
        }
        
        .memory-view {
            font-family: 'Courier New', monospace;
        }
        
        .memory-line {
            margin: 2px 0;
        }
        
        .address {
            color: var(--vscode-debugTokenExpression-name);
        }
        
        .hex {
            margin: 0 5px;
        }
        
        .ascii {
            color: var(--vscode-debugTokenExpression-string);
        }
    </style>
</head>
<body>
    <div class="controls">
        <input type="text" id="address" value="0x20000000" placeholder="Address">
        <button onclick="readMemory()">📖 Read</button>
        <button onclick="readMemory(256)">Read 256</button>
        <button onclick="readMemory(1024)">Read 1KB</button>
    </div>
    
    <div id="memory" class="memory-view">
        <div>Enter address and click Read...</div>
    </div>
    
    <script>
        const vscode = acquireVsCodeApi();
        
        window.addEventListener('message', event => {
            const message = event.data;
            
            if (message.type === 'update') {
                displayMemory(message.address, message.memory);
            }
        });
        
        function readMemory(length = 256) {
            const address = document.getElementById('address').value;
            vscode.postMessage({
                type: 'read',
                address,
                length
            });
        }
        
        function displayMemory(startAddr, hexData) {
            const memDiv = document.getElementById('memory');
            memDiv.innerHTML = '';
            
            // Parse hex data (format from GDB may vary)
            const bytes = hexData.match(/.{1,2}/g) || [];
            const bytesPerLine = 16;
            
            for (let i = 0; i < bytes.length; i += bytesPerLine) {
                const line = bytes.slice(i, i + bytesPerLine);
                const addr = (parseInt(startAddr, 16) + i).toString(16).padStart(8, '0');
                
                const hex = line.map(b => b.padStart(2, '0')).join(' ');
                const ascii = line.map(b => {
                    const code = parseInt(b, 16);
                    return (code >= 32 && code <= 126) ? String.fromCharCode(code) : '.';
                }).join('');
                
                const lineDiv = document.createElement('div');
                lineDiv.className = 'memory-line';
                lineDiv.innerHTML = \`
                    <span class="address">0x\${addr}</span>
                    <span class="hex">\${hex}</span>
                    <span class="ascii">| \${ascii}</span>
                \`;
                memDiv.appendChild(lineDiv);
            }
        }
    </script>
</body>
</html>`;
    }
}
