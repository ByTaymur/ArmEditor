/**
 * GDB Backend Service
 * GDB MI (Machine Interface) wrapper with timeout handling
 * Phase 0 Fix: All commands have timeout!
 */

import { spawn, ChildProcess } from 'child_process';
import { EventEmitter } from 'events';
import * as vscode from 'vscode';

interface GDBCommand {
    command: string;
    resolve: (data: any) => void;
    reject: (error: Error) => void;
    timeout: NodeJS.Timeout;
}

export class GDBBackend extends EventEmitter {
    private gdb: ChildProcess | null = null;
    private token: number = 1;
    private commands: Map<number, GDBCommand> = new Map();
    private buffer: string = '';
    private running: boolean = false;

    /**
     * Start GDB with ELF file
     */
    async start(elfFile: string, gdbPath?: string): Promise<void> {
        if (!gdbPath) {
            gdbPath = await this.detectGDB();
        }

        return new Promise((resolve, reject) => {
            this.gdb = spawn(gdbPath!, [
                '--interpreter=mi3',
                '--quiet',
                elfFile
            ]);

            this.gdb.stdout?.on('data', (data) => {
                this.buffer += data.toString();
                this.processOutput();
            });

            this.gdb.stderr?.on('data', (data) => {
                console.error('[GDB stderr]', data.toString());
            });

            this.gdb.on('close', (code) => {
                this.emit('closed', code);
                this.running = false;
            });

            this.gdb.on('error', (error) => {
                reject(error);
            });

            // Wait for GDB ready
            setTimeout(() => {
                this.running = true;
                resolve();
            }, 500);
        });
    }

    /**
     * Detect available GDB
     */
    private async detectGDB(): Promise<string> {
        const candidates = ['gdb-multiarch', 'arm-none-eabi-gdb'];

        for (const gdb of candidates) {
            try {
                const { exec } = require('child_process');
                const { promisify } = require('util');
                await promisify(exec)(`which ${gdb}`);
                return gdb;
            } catch { }
        }

        throw new Error('No ARM GDB found (gdb-multiarch or arm-none-eabi-gdb)');
    }

    /**
     * Send MI command with timeout (Phase 0 fix!)
     */
    sendCommand(command: string, args: string = '', timeoutMs: number = 5000): Promise<any> {
        return new Promise((resolve, reject) => {
            if (!this.running) {
                reject(new Error('GDB not running'));
                return;
            }

            const token = this.token++;
            const cmd = args ? `${token}-${command} ${args}\n` : `${token}-${command}\n`;

            const timeout = setTimeout(() => {
                this.commands.delete(token);
                reject(new Error(`GDB command timeout: ${command}`));
            }, timeoutMs);

            this.commands.set(token, {
                command,
                resolve: (data) => {
                    clearTimeout(timeout);
                    resolve(data);
                },
                reject: (error) => {
                    clearTimeout(timeout);
                    reject(error);
                },
                timeout
            });

            this.gdb?.stdin?.write(cmd);
        });
    }

    /**
     * Process GDB MI output
     */
    private processOutput() {
        const lines = this.buffer.split('\n');
        this.buffer = lines.pop() || '';

        for (const line of lines) {
            if (!line.trim()) continue;

            // Result record: ^done, ^error
            const resultMatch = line.match(/^(\d+)\^(\w+),?(.*)$/);
            if (resultMatch) {
                const [, tokenStr, status, data] = resultMatch;
                const token = parseInt(tokenStr);
                const cmd = this.commands.get(token);

                if (cmd) {
                    if (status === 'done') {
                        cmd.resolve(this.parseData(data));
                    } else {
                        cmd.reject(new Error(`GDB error: ${status}`));
                    }
                    this.commands.delete(token);
                }
            }

            // Async record: *stopped, *running
            const asyncMatch = line.match(/^\*(\w+),?(.*)$/);
            if (asyncMatch) {
                const [, event, data] = asyncMatch;
                this.emit('async', event, this.parseData(data));
            }
        }
    }

    /**
     * Parse GDB MI data
     */
    private parseData(data: string): any {
        if (!data) return {};
        // Simple parsing - can be enhanced
        return { raw: data };
    }

    /**
     * Connect to OpenOCD
     */
    async connect(host: string = 'localhost', port: number = 3333): Promise<void> {
        await this.sendCommand('target-select', `extended-remote ${host}:${port}`);
        this.emit('connected');
    }

    /**
     * Set breakpoint
     */
    async setBreakpoint(file: string, line: number): Promise<number> {
        const result = await this.sendCommand('break-insert', `${file}:${line}`);
        return result.bkpt?.number || 0;
    }

    /**
     * Delete breakpoint
     */
    async deleteBreakpoint(number: number): Promise<void> {
        await this.sendCommand('break-delete', number.toString());
    }

    /**
     * Continue execution
     */
    async continue(): Promise<void> {
        await this.sendCommand('exec-continue');
    }

    /**
     * Step over
     */
    async stepOver(): Promise<void> {
        await this.sendCommand('exec-next');
    }

    /**
     * Step into
     */
    async stepInto(): Promise<void> {
        await this.sendCommand('exec-step');
    }

    /**
     * Pause execution
     */
    async pause(): Promise<void> {
        await this.sendCommand('exec-interrupt');
    }

    /**
     * Read registers
     */
    async readRegisters(): Promise<any[]> {
        const result = await this.sendCommand('data-list-register-values', 'x');
        return result.raw || [];
    }

    /**
     * Read memory
     */
    async readMemory(address: string, length: number = 64): Promise<string> {
        const result = await this.sendCommand('data-read-memory-bytes', `${address} ${length}`);
        return result.raw || '';
    }

    /**
     * Evaluate expression
     */
    async evaluate(expression: string): Promise<string> {
        const result = await this.sendCommand('data-evaluate-expression', `"${expression}"`);
        return result.value || '';
    }

    /**
     * Quit GDB
     */
    async quit(): Promise<void> {
        if (this.gdb) {
            await this.sendCommand('gdb-exit');
            this.gdb.kill();
            this.gdb = null;
            this.running = false;
        }
    }
}
