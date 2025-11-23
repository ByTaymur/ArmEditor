/**
 * OpenOCD Interface Service
 * Handles OpenOCD for flashing and debugging
 * Phase 0 Fix: Retry logic + timeout handling!
 */

import { spawn, ChildProcess } from 'child_process';
import { EventEmitter } from 'events';
import * as vscode from 'vscode';

export class OpenOCDService extends EventEmitter {
    private proc: ChildProcess | null = null;
    private running: boolean = false;

    /**
     * Start OpenOCD with retry logic (Phase 0 fix!)
     */
    async startWithRetry(device: string = 'stm32f4x', maxRetries: number = 3): Promise<void> {
        for (let i = 0; i < maxRetries; i++) {
            try {
                await this.start(device);
                return;
            } catch (error: any) {
                if (i === maxRetries - 1) {
                    throw error;
                }
                console.log(`[OpenOCD] Retry ${i + 1}/${maxRetries}...`);
                await this.sleep(2000);
            }
        }
    }

    /**
     * Start OpenOCD
     */
    private start(device: string): Promise<void> {
        return new Promise((resolve, reject) => {
            const config = vscode.workspace.getConfiguration('hopeide');
            const interface_type = config.get<string>('stlink.interface', 'stlink');

            let output = '';
            let errorOutput = '';

            this.proc = spawn('openocd', [
                '-f', `interface/${interface_type}.cfg`,
                '-f', `target/${device}.cfg`,
                '-c', 'gdb_port 3333',
                '-c', 'tcl_port 6666',
                '-c', 'telnet_port 4444'
            ]);

            this.proc.stdout?.on('data', (data) => {
                const text = data.toString();
                output += text;
                this.emit('output', text);

                if (text.includes('Listening on port 3333')) {
                    this.running = true;
                    setTimeout(() => resolve(), 500);
                }
            });

            this.proc.stderr?.on('data', (data) => {
                const text = data.toString();
                errorOutput += text;
                this.emit('output', text);

                if (text.includes('Listening on port 3333')) {
                    this.running = true;
                    setTimeout(() => resolve(), 500);
                }
            });

            this.proc.on('close', (code) => {
                this.running = false;
                this.emit('closed', code);
            });

            this.proc.on('error', (error) => {
                reject(error);
            });

            // Timeout (15 seconds)
            setTimeout(() => {
                if (!this.running) {
                    reject(new Error('OpenOCD startup timeout'));
                }
            }, 15000);
        });
    }

    /**
     * Stop OpenOCD
     */
    async stop(): Promise<void> {
        if (this.proc) {
            this.proc.kill();
            this.proc = null;
            this.running = false;
        }
    }

    /**
     * Check if running
     */
    isRunning(): boolean {
        return this.running;
    }

    /**
     * Sleep utility
     */
    private sleep(ms: number): Promise<void> {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
}
