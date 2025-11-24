import * as vscode from 'vscode';
import * as fs from 'fs';
import * as path from 'path';
import * as os from 'os';
import * as net from 'net';
import { execSync, spawn, ChildProcess } from 'child_process';

// ============================================
// MAKEFILE
// ============================================
const MAKEFILE = String.raw`include Makefile.cubemx

PROFILE ?= debug

ifeq ($(PROFILE),debug)
override OPT := -O0
override CFLAGS += -g3 -gdwarf-4
override CFLAGS += -fno-eliminate-unused-debug-types
override CFLAGS += -fno-inline
override CFLAGS += -fno-inline-functions
override DEBUG := 1
endif

ifeq ($(PROFILE),release)
override OPT := -O2 -flto
override LDFLAGS += -flto
override DEBUG := 0
endif

ifeq ($(PROFILE),O0)
override OPT := -O0
override DEBUG := 1
endif

ifeq ($(PROFILE),Og)
override OPT := -Og
override DEBUG := 1
endif

ifeq ($(PROFILE),O2)
override OPT := -O2 -flto
override DEBUG := 0
endif

ifeq ($(PROFILE),O3)
override OPT := -O3 -flto
override DEBUG := 0
endif

ifeq ($(PROFILE),Os)
override OPT := -Os -flto
override DEBUG := 0
endif

override CFLAGS += -fstack-usage
override LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

MCU_DEFINE := $(shell grep -oP 'STM32\w+' Makefile.cubemx 2>/dev/null | head -1)
MCU_FAMILY := $(shell echo $(MCU_DEFINE) | grep -oP 'STM32[FGHLUWf][0-9]')

ifeq ($(MCU_FAMILY),STM32F0)
OPENOCD_TARGET = stm32f0x.cfg
else ifeq ($(MCU_FAMILY),STM32F1)
OPENOCD_TARGET = stm32f1x.cfg
else ifeq ($(MCU_FAMILY),STM32F2)
OPENOCD_TARGET = stm32f2x.cfg
else ifeq ($(MCU_FAMILY),STM32F3)
OPENOCD_TARGET = stm32f3x.cfg
else ifeq ($(MCU_FAMILY),STM32F4)
OPENOCD_TARGET = stm32f4x.cfg
else ifeq ($(MCU_FAMILY),STM32F7)
OPENOCD_TARGET = stm32f7x.cfg
else ifeq ($(MCU_FAMILY),STM32G0)
OPENOCD_TARGET = stm32g0x.cfg
else ifeq ($(MCU_FAMILY),STM32G4)
OPENOCD_TARGET = stm32g4x.cfg
else ifeq ($(MCU_FAMILY),STM32H7)
OPENOCD_TARGET = stm32h7x.cfg
else ifeq ($(MCU_FAMILY),STM32L0)
OPENOCD_TARGET = stm32l0.cfg
else ifeq ($(MCU_FAMILY),STM32L1)
OPENOCD_TARGET = stm32l1.cfg
else ifeq ($(MCU_FAMILY),STM32L4)
OPENOCD_TARGET = stm32l4x.cfg
else ifeq ($(MCU_FAMILY),STM32L5)
OPENOCD_TARGET = stm32l5x.cfg
else ifeq ($(MCU_FAMILY),STM32U5)
OPENOCD_TARGET = stm32u5x.cfg
else ifeq ($(MCU_FAMILY),STM32WB)
OPENOCD_TARGET = stm32wbx.cfg
else ifeq ($(MCU_FAMILY),STM32WL)
OPENOCD_TARGET = stm32wlx.cfg
else
OPENOCD_TARGET = stm32f4x.cfg
endif

DEBUGGER_CFG := interface/stlink.cfg

.PHONY: connect debug release O0 Og O2 O3 Os flash full-flash erase reset size

connect:
	@echo "🔌 Testing..."
	@openocd -f $(DEBUGGER_CFG) -f target/$(OPENOCD_TARGET) -c "init" -c "targets" -c "exit" 2>&1 | grep -q "Cortex" && echo "✅ Connected!" || echo "❌ Failed!"

debug:
	@echo "🐛 Building DEBUG (-O0)..."
	@$(MAKE) clean
	@$(MAKE) PROFILE=debug -j$(shell nproc)
	@echo "✅ Done!"

release:
	@echo "📦 Building RELEASE..."
	@$(MAKE) clean
	@$(MAKE) PROFILE=release -j$(shell nproc)
	@echo "✅ Done!"

O0:
	@echo "⚡ Building O0..."
	@$(MAKE) clean
	@$(MAKE) PROFILE=O0 -j$(shell nproc)
	@echo "✅ Done!"

Og:
	@echo "🐛 Building Og..."
	@$(MAKE) clean
	@$(MAKE) PROFILE=Og -j$(shell nproc)
	@echo "✅ Done!"

O2:
	@echo "⚙️ Building O2..."
	@$(MAKE) clean
	@$(MAKE) PROFILE=O2 -j$(shell nproc)
	@echo "✅ Done!"

O3:
	@echo "🚀 Building O3..."
	@$(MAKE) clean
	@$(MAKE) PROFILE=O3 -j$(shell nproc)
	@echo "✅ Done!"

Os:
	@echo "📦 Building Os..."
	@$(MAKE) clean
	@$(MAKE) PROFILE=Os -j$(shell nproc)
	@echo "✅ Done!"

flash: connect
	@openocd -f $(DEBUGGER_CFG) -f target/$(OPENOCD_TARGET) -c "transport select hla_swd" -c "init" -c "reset halt" -c "flash write_image erase $(BUILD_DIR)/$(TARGET).elf" -c "reset run" -c "exit" && echo "✅ Flashed!"

full-flash: debug flash reset

erase: connect
	@openocd -f $(DEBUGGER_CFG) -f target/$(OPENOCD_TARGET) -c "init" -c "reset halt" -c "flash erase_sector 0 0 last" -c "exit" && echo "✅ Erased!"

reset: connect
	@openocd -f $(DEBUGGER_CFG) -f target/$(OPENOCD_TARGET) -c "init" -c "reset run" -c "exit" && echo "✅ Reset!"

size:
	@$(SZ) -A $(BUILD_DIR)/$(TARGET).elf
`;

// ============================================
// OPENOCD DAEMON
// ============================================
class OpenOCDDaemon {
    private static instance: OpenOCDDaemon;
    private process?: ChildProcess;
    private isRunning = false;
    private telnetPort = 4444;

    static getInstance(): OpenOCDDaemon {
        if (!OpenOCDDaemon.instance) {
            OpenOCDDaemon.instance = new OpenOCDDaemon();
        }
        return OpenOCDDaemon.instance;
    }

    async start(target = 'stm32f4x.cfg'): Promise<boolean> {
        if (this.isRunning) return true;

        return new Promise((resolve) => {
            try {
                this.process = spawn('openocd', [
                    '-f', 'interface/stlink.cfg',
                    '-f', `target/${target}`
                ]);

                this.process.stdout?.on('data', (data) => {
                    if (data.toString().includes('Listening on port')) {
                        this.isRunning = true;
                        resolve(true);
                    }
                });

                this.process.on('exit', () => {
                    this.isRunning = false;
                });

                setTimeout(() => resolve(this.isRunning), 3000);
            } catch {
                resolve(false);
            }
        });
    }

    stop() {
        if (this.process) {
            this.process.kill();
            this.isRunning = false;
        }
    }

    async readMemory(address: string): Promise<number | null> {
        return new Promise((resolve) => {
            const client = new net.Socket();
            client.connect(this.telnetPort, 'localhost', () => {
                client.write(`mdw ${address}\n`);
            });

            let buffer = '';
            client.on('data', (data) => {
                buffer += data.toString();
                const match = buffer.match(/0x[0-9a-fA-F]+:\s+([0-9a-fA-F]+)/);
                if (match) {
                    client.destroy();
                    resolve(parseInt(match[1], 16));
                }
            });

            client.on('error', () => {
                client.destroy();
                resolve(null);
            });

            setTimeout(() => {
                client.destroy();
                resolve(null);
            }, 1000);
        });
    }

    async writeMemory(address: string, value: number): Promise<boolean> {
        return new Promise((resolve) => {
            const client = new net.Socket();
            const hexValue = '0x' + value.toString(16).padStart(8, '0');
            
            client.connect(this.telnetPort, 'localhost', () => {
                client.write(`mww ${address} ${hexValue}\n`);
            });

            client.on('data', () => {
                client.destroy();
                resolve(true);
            });

            client.on('error', () => {
                client.destroy();
                resolve(false);
            });

            setTimeout(() => {
                client.destroy();
                resolve(false);
            }, 1000);
        });
    }

    getStatus(): boolean {
        return this.isRunning;
    }
}

// ============================================
// ACTIVATION
// ============================================
export function activate(context: vscode.ExtensionContext) {
    const daemon = OpenOCDDaemon.getInstance();

    context.subscriptions.push(
        vscode.commands.registerCommand('stm32.setup', () => setup(context)),
        vscode.commands.registerCommand('stm32.variableMonitor', () => openVariableMonitor(context)),
        vscode.commands.registerCommand('stm32.gdbViewer', () => openGDBViewer(context)),
        vscode.commands.registerCommand('stm32.buildDebug', () => buildWithLevel('debug')),
        vscode.commands.registerCommand('stm32.buildRelease', () => buildWithLevel('release')),
        vscode.commands.registerCommand('stm32.buildO0', () => buildWithLevel('O0')),
        vscode.commands.registerCommand('stm32.buildOg', () => buildWithLevel('Og')),
        vscode.commands.registerCommand('stm32.buildO2', () => buildWithLevel('O2')),
        vscode.commands.registerCommand('stm32.buildO3', () => buildWithLevel('O3')),
        vscode.commands.registerCommand('stm32.buildOs', () => buildWithLevel('Os')),
        vscode.commands.registerCommand('stm32.clean', () => runMake('clean')),
        vscode.commands.registerCommand('stm32.flash', () => runMake('flash')),
        vscode.commands.registerCommand('stm32.fullFlash', () => runMake('full-flash')),
        vscode.commands.registerCommand('stm32.erase', () => runMake('erase')),
        vscode.commands.registerCommand('stm32.reset', () => runMake('reset')),
        vscode.commands.registerCommand('stm32.size', () => runMake('size')),
        vscode.commands.registerCommand('stm32.connect', testConnection),
        vscode.commands.registerCommand('stm32.disconnect', () => { daemon.stop(); disconnect(); })
    );

    vscode.window.registerTreeDataProvider('stm32.setup', new TreeProvider([
        ['🚀 Setup Project', 'stm32.setup']
    ]));

    vscode.window.registerTreeDataProvider('stm32.build', new TreeProvider([
        ['🔌 Connect', 'stm32.connect'],
        ['🔴 Disconnect', 'stm32.disconnect'],
        ['🐛 Build Debug (-O0)', 'stm32.buildDebug'],
        ['📦 Build Release', 'stm32.buildRelease'],
        ['🗑️ Clean', 'stm32.clean'],
        ['📊 Size', 'stm32.size']
    ]));

    vscode.window.registerTreeDataProvider('stm32.optimize', new TreeProvider([
        ['⚡ O0 - No optimization ⭐', 'stm32.buildO0'],
        ['🐛 Og - Debug optimized', 'stm32.buildOg'],
        ['⚙️ O2 - Balanced', 'stm32.buildO2'],
        ['🚀 O3 - Maximum', 'stm32.buildO3'],
        ['📦 Os - Size', 'stm32.buildOs']
    ]));

    vscode.window.registerTreeDataProvider('stm32.flash', new TreeProvider([
        ['⚡ Flash', 'stm32.flash'],
        ['🚀 Full Flash', 'stm32.fullFlash'],
        ['🔥 Erase', 'stm32.erase'],
        ['🔄 Reset', 'stm32.reset']
    ]));

    vscode.window.registerTreeDataProvider('stm32.monitor', new TreeProvider([
        ['📊 Variable Monitor (Charts)', 'stm32.variableMonitor'],
        ['🔍 GDB Viewer', 'stm32.gdbViewer']
    ]));

    const statusBar = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Left);
    statusBar.text = '$(rocket) STM32';
    statusBar.command = 'stm32.buildDebug';
    statusBar.show();
    context.subscriptions.push(statusBar);

    autoSetup(context);
}

// ============================================
// SETUP
// ============================================
async function setup(context: vscode.ExtensionContext) {
    const ws = vscode.workspace.workspaceFolders?.[0]?.uri.fsPath;
    if (!ws) return;

    const mk = path.join(ws, 'Makefile');
    if (!fs.existsSync(mk)) {
        vscode.window.showErrorMessage('No Makefile!');
        return;
    }

    if (!fs.existsSync(path.join(ws, 'Makefile.original'))) {
        fs.copyFileSync(mk, path.join(ws, 'Makefile.original'));
    }
    if (!fs.existsSync(path.join(ws, 'Makefile.cubemx'))) {
        fs.renameSync(mk, path.join(ws, 'Makefile.cubemx'));
    }
    fs.writeFileSync(mk, MAKEFILE);

    const mcu = detectMCU(ws);
    const target = detectTarget(mcu);
    const vsc = path.join(ws, '.vscode');
    if (!fs.existsSync(vsc)) {
        fs.mkdirSync(vsc);
    }

    const proj = path.basename(ws);

    // launch.json
    fs.writeFileSync(path.join(vsc, 'launch.json'), JSON.stringify({
        version: '0.2.0',
        configurations: [{
            name: 'Debug STM32',
            type: 'cortex-debug',
            request: 'launch',
            cwd: '${workspaceFolder}',
            executable: '${workspaceFolder}/build/' + proj + '.elf',
            servertype: 'openocd',
            device: mcu,
            interface: 'swd',
            runToEntryPoint: 'main',
            preLaunchTask: 'Build & Flash',
            configFiles: ['interface/stlink.cfg', 'target/' + target],
            liveWatch: {
                enabled: true,
                samplesPerSecond: 10
            }
        }]
    }, null, 4));

    // tasks.json
    fs.writeFileSync(path.join(vsc, 'tasks.json'), JSON.stringify({
        version: '2.0.0',
        tasks: [{
            label: 'Build & Flash',
            type: 'shell',
            command: 'make debug && make flash',
            group: { kind: 'build', isDefault: true },
            problemMatcher: ['$gcc']
        }]
    }, null, 4));

    // Example code
    const exampleC = `// STM32 Live Variables Example

// ✅ Use volatile + global!
volatile uint32_t TimeOut2 = 0;
volatile uint32_t g_counter = 0;
volatile float g_temperature = 25.0f;

void main(void) {
    HAL_Init();
    
    while(1) {
        TimeOut2++;
        g_counter++;
        g_temperature += 0.1f;
        HAL_Delay(100);
    }
}`;
    fs.writeFileSync(path.join(ws, 'live_variables_example.c'), exampleC);

    vscode.window.showInformationMessage(
        `✅ Setup complete!\n\n` +
        `MCU: ${mcu}\n` +
        `Build: -O0\n` +
        `Live Watch: 10 Hz\n\n` +
        `Next:\n` +
        `1. Add volatile variables\n` +
        `2. Run & Debug → Debug STM32\n` +
        `3. WATCH panel → Add variables`,
        'Open Debug', 'Open Monitor'
    ).then(sel => {
        if (sel === 'Open Debug') {
            vscode.commands.executeCommand('workbench.view.debug');
        } else if (sel === 'Open Monitor') {
            openVariableMonitor(context);
        }
    });
}

// ============================================
// VARIABLE MONITOR (WITH CHARTS!)
// ============================================
function openVariableMonitor(context: vscode.ExtensionContext) {
    const daemon = OpenOCDDaemon.getInstance();
    const ws = vscode.workspace.workspaceFolders?.[0]?.uri.fsPath;
    if (!ws) return;

    vscode.window.showInformationMessage('📊 Starting Variable Monitor with Charts...');

    daemon.start().then(() => {
        const panel = vscode.window.createWebviewPanel(
            'variableMonitor',
            '📊 STM32 Variable Monitor',
            vscode.ViewColumn.Two,
            { enableScripts: true, retainContextWhenHidden: true }
        );

        panel.webview.html = getVariableMonitorHTML();

        panel.webview.onDidReceiveMessage(async (message) => {
            if (message.command === 'findVariable') {
                const address = await findVariableAddress(message.varname);
                if (address) {
                    panel.webview.postMessage({
                        command: 'variableFound',
                        varname: message.varname,
                        address: address
                    });
                } else {
                    panel.webview.postMessage({
                        command: 'error',
                        text: 'Variable not found! Build first.'
                    });
                }
            } else if (message.command === 'readVariable') {
                const value = await daemon.readMemory(message.address);
                if (value !== null) {
                    panel.webview.postMessage({
                        command: 'updateValue',
                        varname: message.varname,
                        value: value
                    });
                }
            } else if (message.command === 'writeVariable') {
                const success = await daemon.writeMemory(message.address, message.value);
                panel.webview.postMessage({
                    command: success ? 'writeSuccess' : 'writeFailed'
                });
            }
        }, undefined, context.subscriptions);
    });
}

function getVariableMonitorHTML(): string {
    return `<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <script src="https://cdn.jsdelivr.net/npm/chart.js@4.4.0/dist/chart.umd.min.js"></script>
    <style>
        body { 
            background: #1e1e1e; 
            color: #d4d4d4; 
            font-family: 'Segoe UI', sans-serif;
            padding: 20px;
            margin: 0;
        }
        h1 { color: #4ec9b0; margin-bottom: 20px; }
        
        .controls {
            background: #252526;
            padding: 20px;
            border-radius: 8px;
            margin-bottom: 20px;
            border: 1px solid #3e3e42;
        }
        
        input {
            background: #3c3c3c;
            border: 1px solid #3e3e42;
            color: #d4d4d4;
            padding: 10px;
            border-radius: 4px;
            margin-right: 10px;
        }
        
        input[type="text"] { width: 250px; }
        input[type="number"] { width: 150px; }
        
        button {
            background: #0e639c;
            border: none;
            color: white;
            padding: 10px 20px;
            border-radius: 4px;
            cursor: pointer;
            margin: 5px;
        }
        button:hover { background: #1177bb; }
        button.stop { background: #d13438; }
        button.add { background: #107c10; }
        
        .variable-card {
            background: #252526;
            border: 1px solid #3e3e42;
            border-radius: 8px;
            padding: 20px;
            margin-bottom: 20px;
        }
        
        .variable-card h3 {
            margin: 0 0 15px 0;
            color: #4ec9b0;
        }
        
        .value-display {
            font-size: 48px;
            font-weight: bold;
            color: #569cd6;
            text-align: center;
            margin: 15px 0;
        }
        
        .chart-container {
            position: relative;
            height: 200px;
            margin-top: 15px;
        }
        
        .info {
            background: #1e5f3a;
            padding: 10px;
            border-radius: 4px;
            margin: 10px 0;
            font-size: 14px;
        }
        
        .status {
            text-align: center;
            margin: 15px 0;
            padding: 10px;
            background: #3c3c3c;
            border-radius: 4px;
        }
    </style>
</head>
<body>
    <h1>📊 STM32 Variable Monitor with Charts</h1>
    
    <div class="controls">
        <input type="text" id="varname" placeholder="Variable name (e.g., TimeOut2, g_counter)">
        <button class="add" onclick="addVariable()">➕ Add Variable</button>
        <button class="stop" onclick="stopAll()">⏹️ Stop All</button>
    </div>

    <div class="status" id="status">Add variables to start monitoring</div>

    <div id="variables"></div>

    <script>
        const vscode = acquireVsCodeApi();
        const variables = new Map();
        const charts = new Map();
        const intervals = new Map();
        const maxDataPoints = 100;

        function addVariable() {
            const varname = document.getElementById('varname').value.trim();
            if (!varname || variables.has(varname)) return;
            
            document.getElementById('status').textContent = 'Finding ' + varname + '...';
            vscode.postMessage({ command: 'findVariable', varname: varname });
        }

        function createVariableCard(varname, address) {
            const card = document.createElement('div');
            card.className = 'variable-card';
            card.id = 'card-' + varname;
            card.innerHTML = \`
                <h3>\${varname}</h3>
                <div class="info">Address: \${address}</div>
                <div class="value-display" id="value-\${varname}">0</div>
                <div>
                    <input type="number" id="input-\${varname}" placeholder="Set value">
                    <button onclick="writeVariable('\${varname}')">✏️ Write</button>
                    <button class="stop" onclick="stopVariable('\${varname}')">⏹️ Stop</button>
                    <button class="stop" onclick="removeVariable('\${varname}')">🗑️ Remove</button>
                </div>
                <div class="chart-container">
                    <canvas id="chart-\${varname}"></canvas>
                </div>
            \`;
            document.getElementById('variables').appendChild(card);
            
            // Create chart
            const ctx = document.getElementById('chart-' + varname).getContext('2d');
            const chart = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: [],
                    datasets: [{
                        label: varname,
                        data: [],
                        borderColor: '#569cd6',
                        backgroundColor: 'rgba(86, 156, 214, 0.1)',
                        tension: 0.4,
                        borderWidth: 2
                    }]
                },
                options: {
                    responsive: true,
                    maintainAspectRatio: false,
                    animation: false,
                    scales: {
                        x: { 
                            display: false
                        },
                        y: { 
                            ticks: { color: '#d4d4d4' },
                            grid: { color: '#3e3e42' }
                        }
                    },
                    plugins: {
                        legend: { 
                            labels: { color: '#d4d4d4' }
                        }
                    }
                }
            });
            charts.set(varname, chart);
            
            // Start reading at 10 Hz
            const interval = setInterval(() => {
                vscode.postMessage({
                    command: 'readVariable',
                    varname: varname,
                    address: address
                });
            }, 100); // 10 Hz
            
            intervals.set(varname, interval);
        }

        function updateValue(varname, value) {
            document.getElementById('value-' + varname).textContent = value;
            
            const chart = charts.get(varname);
            if (!chart) return;
            
            const now = new Date().toLocaleTimeString();
            chart.data.labels.push(now);
            chart.data.datasets[0].data.push(value);
            
            if (chart.data.labels.length > maxDataPoints) {
                chart.data.labels.shift();
                chart.data.datasets[0].data.shift();
            }
            
            chart.update('none');
        }

        function writeVariable(varname) {
            const value = parseInt(document.getElementById('input-' + varname).value);
            const address = variables.get(varname);
            if (!address || isNaN(value)) return;
            
            vscode.postMessage({
                command: 'writeVariable',
                varname: varname,
                address: address,
                value: value
            });
        }

        function stopVariable(varname) {
            const interval = intervals.get(varname);
            if (interval) {
                clearInterval(interval);
                intervals.delete(varname);
            }
        }

        function removeVariable(varname) {
            stopVariable(varname);
            const card = document.getElementById('card-' + varname);
            if (card) card.remove();
            variables.delete(varname);
            charts.delete(varname);
        }

        function stopAll() {
            intervals.forEach((interval, varname) => {
                clearInterval(interval);
            });
            intervals.clear();
            document.getElementById('status').textContent = 'All monitoring stopped';
        }

        window.addEventListener('message', event => {
            const msg = event.data;
            
            if (msg.command === 'variableFound') {
                variables.set(msg.varname, msg.address);
                createVariableCard(msg.varname, msg.address);
                document.getElementById('status').textContent = 'Monitoring ' + msg.varname + ' at 10 Hz';
                document.getElementById('varname').value = '';
                
            } else if (msg.command === 'updateValue') {
                updateValue(msg.varname, msg.value);
                
            } else if (msg.command === 'writeSuccess') {
                document.getElementById('status').textContent = '✅ Write successful!';
                setTimeout(() => {
                    document.getElementById('status').textContent = 'Monitoring...';
                }, 2000);
                
            } else if (msg.command === 'error') {
                document.getElementById('status').textContent = '❌ ' + msg.text;
            }
        });
    </script>
</body>
</html>`;
}

// ============================================
// GDB VIEWER
// ============================================
function openGDBViewer(context: vscode.ExtensionContext) {
    const daemon = OpenOCDDaemon.getInstance();
    
    vscode.window.showInformationMessage('🔍 Starting GDB Viewer...');
    
    daemon.start().then(() => {
        const panel = vscode.window.createWebviewPanel(
            'gdbViewer',
            '🔍 GDB Variable Viewer',
            vscode.ViewColumn.Two,
            { enableScripts: true, retainContextWhenHidden: true }
        );

        panel.webview.html = getGDBViewerHTML();

        panel.webview.onDidReceiveMessage(async (message) => {
            if (message.command === 'findVariable') {
                const address = await findVariableAddress(message.varname);
                if (address) {
                    panel.webview.postMessage({
                        command: 'variableFound',
                        varname: message.varname,
                        address: address
                    });
                } else {
                    panel.webview.postMessage({
                        command: 'variableNotFound',
                        varname: message.varname
                    });
                }
            } else if (message.command === 'readVariable') {
                const value = await daemon.readMemory(message.address);
                if (value !== null) {
                    panel.webview.postMessage({
                        command: 'updateValue',
                        value: value.toString()
                    });
                }
            } else if (message.command === 'writeVariable') {
                const success = await daemon.writeMemory(message.address, message.value);
                panel.webview.postMessage({
                    command: success ? 'writeSuccess' : 'writeFailed'
                });
            }
        }, undefined, context.subscriptions);
    });
}

function getGDBViewerHTML(): string {
    return `<!DOCTYPE html>
<html>
<head>
    <style>
        body { background: #1e1e1e; color: #d4d4d4; font-family: Arial; padding: 20px; }
        h1 { color: #4ec9b0; }
        input { background: #3c3c3c; border: 1px solid #3e3e42; color: #d4d4d4; padding: 10px; border-radius: 4px; width: 300px; margin: 10px; }
        button { background: #0e639c; border: none; color: white; padding: 10px 20px; border-radius: 4px; cursor: pointer; margin: 5px; }
        button:hover { background: #1177bb; }
        button.stop { background: #d13438; }
        .value { font-size: 48px; font-weight: bold; color: #569cd6; text-align: center; margin: 30px 0; }
        .status { text-align: center; margin: 20px 0; }
        .info { background: #1e5f3a; padding: 15px; border-radius: 8px; margin: 15px 0; }
    </style>
</head>
<body>
    <h1>🔍 GDB Variable Viewer</h1>
    <div>
        <input type="text" id="varname" placeholder="Variable name (e.g., g_counter)">
        <button onclick="find()">🔍 Find & Monitor</button>
        <button class="stop" onclick="stop()">⏹️ Stop</button>
    </div>
    <div id="info" style="display:none;" class="info">
        <strong>Variable:</strong> <span id="varName">-</span><br>
        <strong>Address:</strong> <span id="address">-</span>
    </div>
    <div class="value" id="value">---</div>
    <div class="status" id="status">Enter variable name</div>
    <div>
        <input type="number" id="writeValue" placeholder="New value" style="width:150px;">
        <button onclick="write()">✏️ Write</button>
    </div>
    
    <script>
        const vscode = acquireVsCodeApi();
        let intervalId = null;
        let currentAddress = null;

        function find() {
            const varname = document.getElementById('varname').value.trim();
            if (!varname) return;
            document.getElementById('status').textContent = 'Finding...';
            vscode.postMessage({ command: 'findVariable', varname: varname });
        }

        function stop() {
            if (intervalId) {
                clearInterval(intervalId);
                intervalId = null;
                document.getElementById('status').textContent = 'Stopped';
            }
        }

        function write() {
            const value = parseInt(document.getElementById('writeValue').value);
            if (!currentAddress || isNaN(value)) return;
            vscode.postMessage({
                command: 'writeVariable',
                address: currentAddress,
                value: value
            });
        }

        window.addEventListener('message', event => {
            const msg = event.data;
            
            if (msg.command === 'variableFound') {
                currentAddress = msg.address;
                document.getElementById('info').style.display = 'block';
                document.getElementById('varName').textContent = msg.varname;
                document.getElementById('address').textContent = msg.address;
                document.getElementById('status').textContent = 'Monitoring at 10 Hz...';
                
                intervalId = setInterval(() => {
                    vscode.postMessage({
                        command: 'readVariable',
                        address: currentAddress
                    });
                }, 100); // 10 Hz
                
            } else if (msg.command === 'updateValue') {
                document.getElementById('value').textContent = msg.value;
                
            } else if (msg.command === 'writeSuccess') {
                document.getElementById('status').textContent = '✅ Write OK!';
                
            } else if (msg.command === 'variableNotFound') {
                document.getElementById('status').textContent = '❌ Variable not found!';
            }
        });
    </script>
</body>
</html>`;
}

// ============================================
// UTILITIES
// ============================================
async function findVariableAddress(varname: string): Promise<string | null> {
    const ws = vscode.workspace.workspaceFolders?.[0]?.uri.fsPath;
    if (!ws) return null;

    try {
        const elfFiles = execSync(`find ${ws}/build -name "*.elf" 2>/dev/null`, {
            encoding: 'utf-8'
        }).trim().split('\n').filter(f => f);

        if (elfFiles.length === 0) return null;

        const output = execSync(
            `arm-none-eabi-nm -S ${elfFiles[0]} | grep -w "${varname}"`,
            { encoding: 'utf-8' }
        );

        const match = output.match(/([0-9a-f]{8})/);
        return match ? '0x' + match[1] : null;
    } catch {
        return null;
    }
}

function buildWithLevel(level: string) {
    const ws = vscode.workspace.workspaceFolders?.[0]?.uri.fsPath;
    if (!ws) return;

    const term = vscode.window.createTerminal(`Build ${level}`);
    term.show();
    term.sendText(`cd "${ws}" && make ${level}`);
}

function runMake(target: string) {
    const ws = vscode.workspace.workspaceFolders?.[0]?.uri.fsPath;
    if (!ws) return;

    const term = vscode.window.createTerminal(`STM32: ${target}`);
    term.show();
    term.sendText(`cd "${ws}" && make ${target}`);
}

function detectMCU(ws: string): string {
    const mk = path.join(ws, 'Makefile.cubemx');
    if (!fs.existsSync(mk)) return 'STM32F4';
    const content = fs.readFileSync(mk, 'utf-8');
    const match = content.match(/-D(STM32[A-Z0-9]+)/);
    return match ? match[1] : 'STM32F4';
}

function detectTarget(mcu: string): string {
    const family = mcu.match(/STM32[FGHLUWf][0-9]/)?.[0] || 'STM32F4';
    const targets: { [key: string]: string } = {
        'STM32F0': 'stm32f0x.cfg', 'STM32F1': 'stm32f1x.cfg',
        'STM32F2': 'stm32f2x.cfg', 'STM32F3': 'stm32f3x.cfg',
        'STM32F4': 'stm32f4x.cfg', 'STM32F7': 'stm32f7x.cfg',
        'STM32G0': 'stm32g0x.cfg', 'STM32G4': 'stm32g4x.cfg',
        'STM32H7': 'stm32h7x.cfg', 'STM32L0': 'stm32l0.cfg',
        'STM32L1': 'stm32l1.cfg', 'STM32L4': 'stm32l4x.cfg',
        'STM32L5': 'stm32l5x.cfg', 'STM32U5': 'stm32u5x.cfg',
        'STM32WB': 'stm32wbx.cfg', 'STM32WL': 'stm32wlx.cfg'
    };
    return targets[family] || 'stm32f4x.cfg';
}

async function autoSetup(context: vscode.ExtensionContext) {
    const ws = vscode.workspace.workspaceFolders?.[0]?.uri.fsPath;
    if (!ws) return;
    
    const launch = path.join(ws, '.vscode', 'launch.json');
    if (fs.existsSync(launch)) return;
    
    const mk = path.join(ws, 'Makefile');
    if (!fs.existsSync(mk)) return;
    
    const answer = await vscode.window.showInformationMessage(
        '🚀 STM32 project detected!\n\nSetup with live variables + charts?',
        'Yes', 'Later'
    );
    
    if (answer === 'Yes') {
        setup(context);
    }
}

async function testConnection() {
    const ws = vscode.workspace.workspaceFolders?.[0]?.uri.fsPath;
    if (!ws) return;

    try {
        execSync('make connect', { cwd: ws, timeout: 5000 });
        vscode.window.showInformationMessage('✅ Connected!');
    } catch {
        vscode.window.showErrorMessage('❌ Failed!');
    }
}

function disconnect() {
    try {
        execSync('pkill -9 openocd', { stdio: 'ignore' });
    } catch {}
    vscode.window.showInformationMessage('🔴 Disconnected');
}

class TreeProvider implements vscode.TreeDataProvider<TreeItem> {
    constructor(private items: [string, string][]) {}
    getTreeItem(element: TreeItem): vscode.TreeItem { return element; }
    getChildren(): TreeItem[] {
        return this.items.map(([label, cmd]) => new TreeItem(label, cmd));
    }
}

class TreeItem extends vscode.TreeItem {
    constructor(label: string, cmd: string) {
        super(label, vscode.TreeItemCollapsibleState.None);
        this.command = { command: cmd, title: label };
    }
}

export function deactivate() {
    OpenOCDDaemon.getInstance().stop();
}
