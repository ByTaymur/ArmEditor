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
     */
    async provideDebugConfigurations(
        folder: vscode.WorkspaceFolder | undefined
    ): Promise<vscode.DebugConfiguration[]> {
        if (!folder) {
            return [];
        }

        // Try to detect device
        let deviceName = 'STM32F407VGT6'; // Default
        try {
            const device = await this.detector.detect();
            if (device) {
                deviceName = device.name;
            }
        } catch { }

        // Find ELF file
        const elfPath = this.findElfFile(folder.uri.fsPath);

        return [{
            type: 'hopeide',
            request: 'launch',
            name: 'HopeIDE: Debug STM32',
            program: elfPath || '${workspaceFolder}/build/firmware.elf',
            device: deviceName,
            interface: 'swd',
            servertype: 'openocd'
        }];
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
            return configs[0];
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
