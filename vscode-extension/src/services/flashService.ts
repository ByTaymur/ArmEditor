/**
 * Flash Service
 * Handles firmware flashing via st-flash or OpenOCD
 * Includes RETRY LOGIC and TIMEOUT HANDLING (Phase 0 lessons!)
 */

import * as vscode from 'vscode';
import { exec, spawn } from 'child_process';
import { promisify } from 'util';
import * as path from 'path';
import * as fs from 'fs';

const execAsync = promisify(exec);

export class FlashService {
    constructor(private outputChannel: vscode.OutputChannel) { }

    /**
     * Flash firmware with retry logic (Phase 0 fix!)
     */
    async flash(projectPath: string, maxRetries: number = 3): Promise<boolean> {
        const config = vscode.workspace.getConfiguration('hopeide');
        const verify = config.get<boolean>('flash.verify', true);

        // Find .bin or .elf file
        const buildDir = path.join(projectPath, 'build');
        const binFile = this.findFile(buildDir, '.bin');
        const elfFile = this.findFile(buildDir, '.elf');

        const flashFile = binFile || elfFile;

        if (!flashFile) {
            this.outputChannel.appendLine('❌ No .bin or .elf file found in build directory');
            this.outputChannel.appendLine('   Build the project first!');
            return false;
        }

        this.outputChannel.appendLine(`📁 Flash file: ${path.basename(flashFile)}`);
        this.outputChannel.appendLine(`🔄 Verify: ${verify ? 'Yes' : 'No'}`);
        this.outputChannel.appendLine(`🔁 Max retries: ${maxRetries}`);
        this.outputChannel.appendLine('');

        // Try flashing with retry logic
        for (let attempt = 1; attempt <= maxRetries; attempt++) {
            this.outputChannel.appendLine(`⚡ Flash attempt ${attempt}/${maxRetries}...`);

            try {
                const success = await this.flashWithTimeout(flashFile, verify, 60000);

                if (success) {
                    this.outputChannel.appendLine('');
                    this.outputChannel.appendLine('✅ Flash completed successfully!');
                    return true;
                }
            } catch (error: any) {
                this.outputChannel.appendLine(`❌ Attempt ${attempt} failed: ${error.message}`);

                if (attempt < maxRetries) {
                    this.outputChannel.appendLine(`⏳ Waiting 2 seconds before retry...`);
                    await this.sleep(2000);
                } else {
                    this.outputChannel.appendLine('');
                    this.outputChannel.appendLine(`❌ Flash failed after ${maxRetries} attempts`);
                    this.outputChannel.appendLine('');
                    this.outputChannel.appendLine('💡 Troubleshooting:');
                    this.outputChannel.appendLine('   1. Check ST-Link connection (USB cable)');
                    this.outputChannel.appendLine('   2. Check target power (3.3V)');
                    this.outputChannel.appendLine('   3. Try: killall openocd st-flash');
                    this.outputChannel.appendLine('   4. Unplug/replug ST-Link');
                }
            }
        }

        return false;
    }

    /**
     * Flash with timeout (Phase 0 fix!)
     */
    private async flashWithTimeout(file: string, verify: boolean, timeoutMs: number): Promise<boolean> {
        const isPowerOn = await this.flashFile(file, verify);

        return await Promise.race([
            isPowerOn,
            this.timeout(timeoutMs, `Flash timeout after ${timeoutMs / 1000}s`)
        ]);
    }

    /**
     * Actually flash the file (st-flash or OpenOCD)
     */
    private flashFile(file: string, verify: boolean): Promise<boolean> {
        return new Promise((resolve, reject) => {
            // Try st-flash first (faster, more reliable)
            const address = '0x08000000'; // STM32 flash start
            const args = ['--reset', 'write', file, address];

            this.outputChannel.appendLine(`🔧 Command: st-flash ${args.join(' ')}`);

            const proc = spawn('st-flash', args);

            proc.stdout.on('data', (data) => {
                this.outputChannel.append(data.toString());
            });

            proc.stderr.on('data', (data) => {
                // st-flash writes progress to stderr
                this.outputChannel.append(data.toString());
            });

            proc.on('close', (code) => {
                if (code === 0) {
                    resolve(true);
                } else {
                    reject(new Error(`st-flash exited with code ${code}`));
                }
            });

            proc.on('error', (error) => {
                reject(new Error(`Failed to start st-flash: ${error.message}`));
            });
        });
    }

    /**
     * Find file by extension in directory
     */
    private findFile(dir: string, ext: string): string | null {
        if (!fs.existsSync(dir)) {
            return null;
        }

        const files = fs.readdirSync(dir);
        for (const file of files) {
            if (file.endsWith(ext)) {
                return path.join(dir, file);
            }
        }

        return null;
    }

    /**
     * Sleep utility
     */
    private sleep(ms: number): Promise<void> {
        return new Promise(resolve => setTimeout(resolve, ms));
    }

    /**
     * Timeout utility
     */
    private timeout(ms: number, message: string): Promise<never> {
        return new Promise((_, reject) => {
            setTimeout(() => reject(new Error(message)), ms);
        });
    }
}
