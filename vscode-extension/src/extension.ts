/**
 * HopeIDE VS Code Extension
 * Professional ARM Cortex-M Development & Debugging
 */

import * as vscode from 'vscode';
import { BuildService } from './services/buildService';
import { FlashService } from './services/flashService';
import { DeviceDetector } from './services/deviceDetector';
import { RegisterViewerProvider } from './providers/registerViewerProvider';
import { MemoryViewerProvider } from './providers/memoryViewerProvider';

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

    // Register webview providers
    const registerProvider = new RegisterViewerProvider(context.extensionUri);
    const memoryProvider = new MemoryViewerProvider(context.extensionUri);

    context.subscriptions.push(
        vscode.window.registerWebviewViewProvider('hopeide.registers', registerProvider)
    );

    context.subscriptions.push(
        vscode.window.registerWebviewViewProvider('hopeide.memory', memoryProvider)
    );

    outputChannel.appendLine('✅ Webview providers registered');

    // Register commands
    registerCommands(context);

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

function registerCommands(context: vscode.ExtensionContext) {
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

                    vscode.window.showInformationMessage(
                        `Found: ${device.name} (${device.family})`
                    );
                } else {
                    outputChannel.appendLine('❌ No device detected');
                    vscode.window.showWarningMessage('No STM32 device detected. Check connection.');
                }
            } catch (error: any) {
                outputChannel.appendLine(`❌ Detection failed: ${error.message}`);
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
