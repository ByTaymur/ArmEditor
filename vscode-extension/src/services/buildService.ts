/**
 * Build Service
 * Handles ARM project compilation via Makefile
 */

import * as vscode from 'vscode';
import { exec } from 'child_process';
import { promisify } from 'util';
import * as path from 'path';
import * as fs from 'fs';

const execAsync = promisify(exec);

export class BuildService {
    constructor(private outputChannel: vscode.OutputChannel) { }

    /**
     * Build ARM project
     */
    async build(projectPath: string): Promise<boolean> {
        try {
            // Check if Makefile exists
            const makefilePath = path.join(projectPath, 'Makefile');
            if (!fs.existsSync(makefilePath)) {
                this.outputChannel.appendLine('❌ No Makefile found in project');
                vscode.window.showErrorMessage('No Makefile found. Is this an ARM project?');
                return false;
            }

            this.outputChannel.appendLine(`📁 Project: ${projectPath}`);
            this.outputChannel.appendLine(`🔨 Running: make all`);
            this.outputChannel.appendLine('');

            // Run make with timeout
            const { stdout, stderr } = await Promise.race([
                execAsync('make all', {
                    cwd: projectPath,
                    maxBuffer: 1024 * 1024 // 1MB buffer
                }),
                this.timeout(120000, 'Build timeout after 2 minutes')
            ]);

            // Output build results
            if (stdout) {
                this.outputChannel.appendLine(stdout);
            }

            if (stderr) {
                // Some build output goes to stderr (not always errors)
                this.outputChannel.appendLine(stderr);
            }

            this.outputChannel.appendLine('');
            this.outputChannel.appendLine('✅ Build completed successfully!');

            return true;

        } catch (error: any) {
            this.outputChannel.appendLine('');
            this.outputChannel.appendLine(`❌ Build failed: ${error.message}`);

            if (error.stdout) {
                this.outputChannel.appendLine(error.stdout);
            }
            if (error.stderr) {
                this.outputChannel.appendLine(error.stderr);
            }

            return false;
        }
    }

    /**
     * Clean build artifacts
     */
    async clean(projectPath: string): Promise<boolean> {
        try {
            this.outputChannel.appendLine(`🧹 Cleaning build directory...`);

            const { stdout, stderr } = await execAsync('make clean', {
                cwd: projectPath
            });

            if (stdout) this.outputChannel.appendLine(stdout);
            if (stderr) this.outputChannel.appendLine(stderr);

            this.outputChannel.appendLine('✅ Clean completed!');
            return true;

        } catch (error: any) {
            this.outputChannel.appendLine(`❌ Clean failed: ${error.message}`);
            return false;
        }
    }

    /**
     * Get build output file (.elf, .hex, .bin)
     */
    getBuildOutput(projectPath: string): { elf?: string; hex?: string; bin?: string } {
        const buildDir = path.join(projectPath, 'build');

        if (!fs.existsSync(buildDir)) {
            return {};
        }

        const files = fs.readdirSync(buildDir);
        const result: any = {};

        for (const file of files) {
            const fullPath = path.join(buildDir, file);
            if (file.endsWith('.elf')) {
                result.elf = fullPath;
            } else if (file.endsWith('.hex')) {
                result.hex = fullPath;
            } else if (file.endsWith('.bin')) {
                result.bin = fullPath;
            }
        }

        return result;
    }

    /**
     * Helper: Timeout promise
     */
    private timeout(ms: number, message: string): Promise<never> {
        return new Promise((_, reject) => {
            setTimeout(() => reject(new Error(message)), ms);
        });
    }
}
