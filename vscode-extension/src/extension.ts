/**
 * HopeIDE VS Code Extension
 * Professional ARM Cortex-M Development & Debugging
 */

import * as vscode from 'vscode';
import { BuildService } from './services/buildService';
import { FlashService } from './services/flashService';

let buildService: BuildService;
let flashService: FlashService;
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

            // TODO: Implement device detection
            vscode.window.showInformationMessage('Device detection coming soon!');
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
