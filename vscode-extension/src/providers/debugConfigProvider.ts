/**
 * HopeIDE Debug Configuration Provider
 * Auto-generates debug configurations based on detected device
 */

import * as vscode from 'vscode';
import { DeviceDetector } from '../services/deviceDetector';
import * as path from 'path';
import * as fs from 'fs';

export class HopeIDEConfigProvider implements vscode.DebugConfigurationProvider {
    private detector: DeviceDetector;

    constructor() {
        this.detector = new DeviceDetector();
    }

    /**
     * Provide initial debug configurations
     * Called when user clicks "Add Configuration" in launch.json
     */
    async provideDebugConfigurations(
        folder: vscode.WorkspaceFolder | undefined
    ): Promise<vscode.DebugConfiguration[]> {
        if (!folder) {
            // Return default config even without folder
            return [{
                type: 'hopeide',
                request: 'launch',
                name: 'HopeIDE: Debug STM32 (Auto-Detect)',
                program: '${workspaceFolder}/build/${workspaceFolderBasename}.elf',
                interface: 'swd'
            }];
        }

        // Try to detect device (but don't fail if not found)
        let deviceName = '';
        try {
            const device = await this.detector.detect();
            if (device) {
                deviceName = device.name;
            }
        } catch {
            // Silent fail - will auto-detect later
        }

        // Find ELF file
        const elfPath = this.findElfFile(folder.uri.fsPath);
        const programPath = elfPath
            ? elfPath.replace(folder.uri.fsPath, '${workspaceFolder}')
            : '${workspaceFolder}/build/${workspaceFolderBasename}.elf';

        // Return config - device will be auto-detected if empty
        const config: vscode.DebugConfiguration = {
            type: 'hopeide',
            request: 'launch',
            name: deviceName
                ? `HopeIDE: Debug ${deviceName}`
                : 'HopeIDE: Debug STM32 (Auto-Detect)',
            program: programPath,
            interface: 'swd'
        };

        // Only add device if detected
        if (deviceName) {
            config.device = deviceName;
        }

        return [config];
    }

    /**
     * Resolve a debug configuration before starting
     */
    async resolveDebugConfiguration(
        folder: vscode.WorkspaceFolder | undefined,
        config: vscode.DebugConfiguration,
        token?: vscode.CancellationToken
    ): Promise<vscode.DebugConfiguration | undefined> {

        // If no config, create default with auto-detection
        if (!config.type && !config.request && !config.name) {
            const configs = await this.provideDebugConfigurations(folder);
            config = configs[0];
        }

        // Auto-create .vscode folder and files if needed
        if (folder && config.type === 'hopeide') {
            await this.ensureVSCodeFiles(folder);
        }

        // Auto-detect device if not specified (UNIVERSAL!)
        if (config.type === 'hopeide' && !config.device) {
            try {
                const device = await this.detector.detect();
                if (device) {
                    config.device = device.name;
                    vscode.window.showInformationMessage(
                        `🎯 Auto-detected: ${device.name} (${device.family})`
                    );
                } else {
                    vscode.window.showWarningMessage(
                        '⚠️ No STM32 device detected. Using default config.'
                    );
                    config.device = 'STM32F4'; // Generic fallback
                }
            } catch {
                vscode.window.showWarningMessage(
                    '⚠️ Device detection failed. Using default config.'
                );
                config.device = 'STM32F4'; // Generic fallback
            }
        }

        // Find ELF file if not specified
        if (config.type === 'hopeide' && !config.program && folder) {
            const elfPath = this.findElfFile(folder.uri.fsPath);
            if (elfPath) {
                config.program = elfPath;
            }
        }

        return config;
    }

    /**
     * Ensure .vscode/launch.json and tasks.json exist
     */
    private async ensureVSCodeFiles(folder: vscode.WorkspaceFolder): Promise<void> {
        const fs = require('fs');
        const path = require('path');

        const vscodeDir = path.join(folder.uri.fsPath, '.vscode');
        const launchPath = path.join(vscodeDir, 'launch.json');
        const tasksPath = path.join(vscodeDir, 'tasks.json');

        // Create .vscode directory if not exists
        if (!fs.existsSync(vscodeDir)) {
            fs.mkdirSync(vscodeDir, { recursive: true });
        }

        // Create launch.json if not exists
        if (!fs.existsSync(launchPath)) {
            const configs = await this.provideDebugConfigurations(folder);
            const launchJson = {
                version: '0.2.0',
                configurations: configs
            };
            fs.writeFileSync(launchPath, JSON.stringify(launchJson, null, 2));
            vscode.window.showInformationMessage('✅ Created .vscode/launch.json');
        }

        // Create tasks.json if not exists
        if (!fs.existsSync(tasksPath)) {
            const tasksJson = {
                version: '2.0.0',
                tasks: [
                    {
                        label: 'Build STM32',
                        type: 'shell',
                        command: 'make',
                        group: {
                            kind: 'build',
                            isDefault: true
                        },
                        problemMatcher: ['$gcc']
                    }
                ]
            };
            fs.writeFileSync(tasksPath, JSON.stringify(tasksJson, null, 2));
            vscode.window.showInformationMessage('✅ Created .vscode/tasks.json');
        }
    }

    /**
     * Find .elf file in build directory
     */
    private findElfFile(workspaceRoot: string): string | null {
        const buildDir = path.join(workspaceRoot, 'build');

        if (!fs.existsSync(buildDir)) {
            return null;
        }

        try {
            const files = fs.readdirSync(buildDir);
            const elfFile = files.find(f => f.endsWith('.elf'));

            if (elfFile) {
                return path.join(buildDir, elfFile);
            }
        } catch { }

        return null;
    }
}
