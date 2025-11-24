/**
 * HopeIDE VS Code Extension
 * Professional ARM Cortex-M Development & Debugging
 */

import * as vscode from 'vscode';
import * as fs from 'fs';
import * as path from 'path';
import { BuildService } from './services/buildService';
import { FlashService } from './services/flashService';
import { DeviceDetector } from './services/deviceDetector';
import { RegisterViewerProvider } from './providers/registerViewerProvider';
import { MemoryViewerProvider } from './providers/memoryViewerProvider';
import { DevicesTreeProvider } from './providers/devicesTreeProvider';
import { HopeIDEConfigProvider } from './providers/debugConfigProvider';

let buildService: BuildService;
let flashService: FlashService;
let deviceDetector: DeviceDetector;
let outputChannel: vscode.OutputChannel;

export function activate(context: vscode.ExtensionContext) {
    console.log('HopeIDE extension is now active!');

    // Create output channel
    outputChannel = vscode.window.createOutputChannel('HopeIDE');
    outputChannel.appendLine('🚀 HopeIDE activated!');
    outputChannel.appendLine('Building for ARM Cortex-M microcontrollers...');

    // Initialize services
    buildService = new BuildService(outputChannel);
    flashService = new FlashService(outputChannel);
    deviceDetector = new DeviceDetector();

    // Register tree provider for devices
    const devicesProvider = new DevicesTreeProvider();
    context.subscriptions.push(
        vscode.window.registerTreeDataProvider('hopeide.devices', devicesProvider)
    );

    // Register webview providers
    const registerProvider = new RegisterViewerProvider(context.extensionUri);
    const memoryProvider = new MemoryViewerProvider(context.extensionUri);

    context.subscriptions.push(
        vscode.window.registerWebviewViewProvider('hopeide.registers', registerProvider)
    );

    context.subscriptions.push(
        vscode.window.registerWebviewViewProvider('hopeide.memory', memoryProvider)
    );

    // Register debug configuration provider (AUTO-DETECT!)
    const debugConfigProvider = new HopeIDEConfigProvider();
    context.subscriptions.push(
        vscode.debug.registerDebugConfigurationProvider('hopeide', debugConfigProvider)
    );

    outputChannel.appendLine('✅ All providers registered (Devices, Registers, Memory, Debug Config)');

    // Register commands
    registerCommands(context, devicesProvider);

    // Show welcome message
    vscode.window.showInformationMessage(
        '🚀 HopeIDE is ready! Professional ARM debugging at your fingertips.',
        'Show Commands'
    ).then(selection => {
        if (selection === 'Show Commands') {
            vscode.commands.executeCommand('workbench.action.showCommands');
        }
    });
}

function registerCommands(context: vscode.ExtensionContext, devicesProvider: DevicesTreeProvider) {
    // Refresh devices command
    context.subscriptions.push(
        vscode.commands.registerCommand('hopeide.refreshDevices', () => {
            devicesProvider.refresh();
        })
    );

    // Build command
    context.subscriptions.push(
        vscode.commands.registerCommand('hopeide.build', async () => {
            const workspaceFolder = vscode.workspace.workspaceFolders?.[0];
            if (!workspaceFolder) {
                vscode.window.showErrorMessage('No workspace folder open');
                return;
            }

            outputChannel.show();
            outputChannel.appendLine('');
            outputChannel.appendLine('━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━');
            outputChannel.appendLine('🔨 Building ARM project...');
            outputChannel.appendLine('━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━');

            const success = await buildService.build(workspaceFolder.uri.fsPath);

            if (success) {
                vscode.window.showInformationMessage('✅ Build successful!');

                // Auto-create .vscode files after successful build
                const vscodeDir = path.join(workspaceFolder.uri.fsPath, '.vscode');
                const launchPath = path.join(vscodeDir, 'launch.json');
                const tasksPath = path.join(vscodeDir, 'tasks.json');

                // Create .vscode directory if not exists
                if (!fs.existsSync(vscodeDir)) {
                    fs.mkdirSync(vscodeDir, { recursive: true });
                }

                // Find ELF file
                const buildDir = path.join(workspaceFolder.uri.fsPath, 'build');
                let elfFile = '';
                if (fs.existsSync(buildDir)) {
                    const files = fs.readdirSync(buildDir);
                    const elf = files.find((f: string) => f.endsWith('.elf'));
                    if (elf) {
                        elfFile = `\${workspaceFolder}/build/${elf}`;
                    }
                }

                if (!elfFile) {
                    elfFile = '${workspaceFolder}/build/${workspaceFolderBasename}.elf';
                }

                // Create launch.json if not exists or update it
                if (!fs.existsSync(launchPath)) {
                    const launchJson = {
                        version: '0.2.0',
                        configurations: [{
                            type: 'hopeide',
                            request: 'launch',
                            name: 'HopeIDE: Debug STM32',
                            program: elfFile,
                            interface: 'swd'
                        }]
                    };
                    fs.writeFileSync(launchPath, JSON.stringify(launchJson, null, 2));
                    outputChannel.appendLine('✅ Created .vscode/launch.json');
                }

                // Create tasks.json if not exists
                if (!fs.existsSync(tasksPath)) {
                    const tasksJson = {
                        version: '2.0.0',
                        tasks: [{
                            label: 'Build STM32',
                            type: 'shell',
                            command: 'make',
                            group: {
                                kind: 'build',
                                isDefault: true
                            },
                            problemMatcher: ['$gcc']
                        }]
                    };
                    fs.writeFileSync(tasksPath, JSON.stringify(tasksJson, null, 2));
                    outputChannel.appendLine('✅ Created .vscode/tasks.json');
                }
            } else {
                vscode.window.showErrorMessage('❌ Build failed. Check output for details.');
            }
        })
    );

    // Flash command
    context.subscriptions.push(
        vscode.commands.registerCommand('hopeide.flash', async () => {
            const workspaceFolder = vscode.workspace.workspaceFolders?.[0];
            if (!workspaceFolder) {
                vscode.window.showErrorMessage('No workspace folder open');
                return;
            }

            outputChannel.show();
            outputChannel.appendLine('');
            outputChannel.appendLine('━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━');
            outputChannel.appendLine('⚡ Flashing device...');
            outputChannel.appendLine('━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━');

            const success = await flashService.flash(workspaceFolder.uri.fsPath);

            if (success) {
                vscode.window.showInformationMessage('✅ Flash successful!');
            } else {
                vscode.window.showErrorMessage('❌ Flash failed. Check output for details.');
            }
        })
    );

    // Clean command
    context.subscriptions.push(
        vscode.commands.registerCommand('hopeide.clean', async () => {
            const workspaceFolder = vscode.workspace.workspaceFolders?.[0];
            if (!workspaceFolder) {
                vscode.window.showErrorMessage('No workspace folder open');
                return;
            }

            outputChannel.show();
            outputChannel.appendLine('');
            outputChannel.appendLine('🧹 Cleaning build...');

            const success = await buildService.clean(workspaceFolder.uri.fsPath);

            if (success) {
                vscode.window.showInformationMessage('✅ Clean successful!');
            }
        })
    );

    // Size analysis
    context.subscriptions.push(
        vscode.commands.registerCommand('hopeide.size', async () => {
            const workspaceFolder = vscode.workspace.workspaceFolders?.[0];
            if (!workspaceFolder) {
                vscode.window.showErrorMessage('No workspace folder open');
                return;
            }

            const terminal = vscode.window.createTerminal('HopeIDE Size');
            terminal.show();
            terminal.sendText('arm-none-eabi-size -A build/*.elf');
        })
    );

    // Reset device
    context.subscriptions.push(
        vscode.commands.registerCommand('hopeide.reset', async () => {
            const terminal = vscode.window.createTerminal('HopeIDE Reset');
            terminal.show();
            terminal.sendText('openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init" -c "reset run" -c "exit"');
            vscode.window.showInformationMessage('🔄 Resetting device...');
        })
    );

    // Erase chip
    context.subscriptions.push(
        vscode.commands.registerCommand('hopeide.erase', async () => {
            const result = await vscode.window.showWarningMessage(
                '⚠️ This will erase the entire chip! Continue?',
                'Yes', 'No'
            );

            if (result === 'Yes') {
                const terminal = vscode.window.createTerminal('HopeIDE Erase');
                terminal.show();
                terminal.sendText('openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init" -c "reset halt" -c "flash erase_sector 0 0 last" -c "exit"');
                vscode.window.showInformationMessage('🔥 Erasing chip...');
            }
        })
    );

    // Detect device command
    context.subscriptions.push(
        vscode.commands.registerCommand('hopeide.detectDevice', async () => {
            outputChannel.show();
            outputChannel.appendLine('');
            outputChannel.appendLine('🔍 Detecting connected STM32 device...');

            try {
                const device = await deviceDetector.detect();

                if (device) {
                    outputChannel.appendLine('');
                    outputChannel.appendLine('✅ Device detected!');
                    outputChannel.appendLine(`   Name: ${device.name}`);
                    outputChannel.appendLine(`   Family: ${device.family}`);
                    outputChannel.appendLine(`   Chip ID: ${device.chipId}`);
                    outputChannel.appendLine(`   Flash: ${device.flashSize} bytes`);

                    // Refresh tree to show detected device
                    devicesProvider.refresh();

                    vscode.window.showInformationMessage(
                        `Found: ${device.name} (${device.family})`
                    );
                } else {
                    outputChannel.appendLine('❌ No device detected');
                    devicesProvider.refresh(); // Refresh to show "No device"
                    vscode.window.showWarningMessage('No STM32 device detected. Check connection.');
                }
            } catch (error: any) {
                outputChannel.appendLine(`❌ Detection failed: ${error.message}`);
                devicesProvider.refresh(); // Refresh to show error
                vscode.window.showErrorMessage('Device detection failed. Is ST-Link connected?');
            }
        })
    );

    // Show registers command
    context.subscriptions.push(
        vscode.commands.registerCommand('hopeide.showRegisters', async () => {
            vscode.window.showInformationMessage('Register viewer coming soon!');
        })
    );

    // Show memory command
    context.subscriptions.push(
        vscode.commands.registerCommand('hopeide.showMemory', async () => {
            vscode.window.showInformationMessage('Memory viewer coming soon!');
        })
    );
}

export function deactivate() {
    outputChannel.appendLine('👋 HopeIDE deactivated');
    outputChannel.dispose();
}
