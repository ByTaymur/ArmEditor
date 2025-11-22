/**
 * GDB MI (Machine Interface) Backend
 * Full debugging support: breakpoints, step, continue, registers, memory, variables
 */

const { spawn, execSync } = require('child_process');
const EventEmitter = require('events');

class GDBBackend extends EventEmitter {
    constructor() {
        super();
        this.gdb = null;
        this.token = 1;
        this.callbacks = new Map();
        this.buffer = '';
        this.running = false;
        this.breakpoints = new Map();
    }

    /**
     * Detect available GDB executable
     */
    detectGDB() {
        const candidates = ['arm-none-eabi-gdb', 'gdb-multiarch'];
        for (const cmd of candidates) {
            try {
                execSync(`which ${cmd}`, { stdio: 'ignore' });
                return cmd;
            } catch (e) {
                // Continue
            }
        }
        return 'arm-none-eabi-gdb'; // Default fallback
    }

    /**
     * Start GDB with target ELF file
     */
    async start(elfFile, gdbPath = null) {
        // Auto-detect if not provided
        if (!gdbPath) {
            gdbPath = this.detectGDB();
            console.log(`[GDBBackend] Using GDB: ${gdbPath}`);
        }

        return new Promise((resolve, reject) => {
            // Launch GDB in MI mode
            this.gdb = spawn(gdbPath, [
                '--interpreter=mi3',
                '--quiet',
                elfFile
            ]);

            this.gdb.stdout.on('data', (data) => {
                this.buffer += data.toString();
                this.processOutput();
            });

            this.gdb.stderr.on('data', (data) => {
                console.error('GDB error:', data.toString());
            });

            this.gdb.on('close', (code) => {
                this.emit('closed', code);
                this.running = false;
            });

            // Wait for GDB ready
            setTimeout(() => {
                this.running = true;
                resolve();
            }, 500);
        });
    }

    /**
     * Process GDB MI output
     */
    processOutput() {
        const lines = this.buffer.split('\n');
        this.buffer = lines.pop() || '';

        for (const line of lines) {
            if (!line.trim()) continue;

            // Parse MI output
            if (line.startsWith('(gdb)')) {
                continue;
            }

            // Result record: ^done, ^error, ^running
            if (line.match(/^(\d+)\^/)) {
                const match = line.match(/^(\d+)\^(\w+),?(.*)$/);
                if (match) {
                    const [, token, status, data] = match;
                    const callback = this.callbacks.get(parseInt(token));
                    if (callback) {
                        callback(status, this.parseData(data));
                        this.callbacks.delete(parseInt(token));
                    }
                }
            }

            // Async record: *stopped, *running
            else if (line.startsWith('*')) {
                const match = line.match(/^\*(\w+),?(.*)$/);
                if (match) {
                    const [, event, data] = match;
                    this.emit('async', event, this.parseData(data));
                }
            }

            // Stream record: ~"console", @"target", &"log"
            else if (line.match(/^[~@&]"(.*)"$/)) {
                const match = line.match(/^[~@&]"(.*)"$/);
                if (match) {
                    this.emit('console', this.unescapeString(match[1]));
                }
            }
        }
    }

    /**
     * Send MI command
     */
    sendCommand(command, args = '') {
        return new Promise((resolve, reject) => {
            if (!this.running) {
                reject(new Error('GDB not running'));
                return;
            }

            const token = this.token++;
            const cmd = args ? `${token}-${command} ${args}\n` : `${token}-${command}\n`;

            this.callbacks.set(token, (status, data) => {
                if (status === 'done') {
                    resolve(data);
                } else {
                    reject(new Error(`GDB error: ${status}`));
                }
            });

            this.gdb.stdin.write(cmd);
        });
    }

    /**
     * Connect to OpenOCD (for STM32 debugging)
     */
    async connectOpenOCD(host = 'localhost', port = 3333) {
        await this.sendCommand('target-select', `extended-remote ${host}:${port}`);
        await this.sendCommand('monitor', 'reset halt');
        this.emit('connected');
    }

    /**
     * Load program to target
     */
    async load() {
        await this.sendCommand('target-download');
        this.emit('loaded');
    }

    /**
     * Breakpoint operations
     */
    async setBreakpoint(file, line) {
        const result = await this.sendCommand('break-insert', `${file}:${line}`);
        const bpNum = result.bkpt?.number;
        if (bpNum) {
            this.breakpoints.set(bpNum, { file, line });
            this.emit('breakpoint-set', { number: bpNum, file, line });
        }
        return bpNum;
    }

    async deleteBreakpoint(number) {
        await this.sendCommand('break-delete', number);
        this.breakpoints.delete(number);
        this.emit('breakpoint-deleted', number);
    }

    async listBreakpoints() {
        return await this.sendCommand('break-list');
    }

    /**
     * Execution control
     */
    async continue() {
        await this.sendCommand('exec-continue');
    }

    async stepOver() {
        await this.sendCommand('exec-next');
    }

    async stepInto() {
        await this.sendCommand('exec-step');
    }

    async stepOut() {
        await this.sendCommand('exec-finish');
    }

    async pause() {
        await this.sendCommand('exec-interrupt');
    }

    async run() {
        await this.sendCommand('exec-run');
    }

    get isConnected() {
        return this.running;
    }

    /**
     * Register operations
     */
    async getRegisterNames() {
        if (this.registerNames) return this.registerNames;

        const result = await this.sendCommand('data-list-register-names');
        this.registerNames = result['register-names'] || [];
        return this.registerNames;
    }

    async readRegisters() {
        // Ensure we have names
        const names = await this.getRegisterNames();

        const result = await this.sendCommand('data-list-register-values', 'x');
        return this.parseRegisters(result, names);
    }

    async readRegister(name) {
        const result = await this.sendCommand('data-evaluate-expression', `$${name}`);
        return result.value;
    }

    async writeRegister(name, value) {
        await this.sendCommand('gdb-set', `$${name}=${value}`);
    }

    // ... memory operations ...

    parseRegisters(data, names) {
        const registers = {};
        if (data['register-values']) {
            for (const reg of data['register-values']) {
                const num = parseInt(reg.number);
                const name = names[num] || `r${num}`;
                // Filter out empty names (unused registers)
                if (name) {
                    registers[name] = reg.value;
                }
            }
        }
        return registers;
    }

    /**
     * Memory operations
     */
    async readMemory(address, length = 64) {
        const result = await this.sendCommand('data-read-memory-bytes', `${address} ${length}`);
        return this.parseMemory(result);
    }

    async writeMemory(address, data) {
        const hexData = Array.from(data).map(b => b.toString(16).padStart(2, '0')).join('');
        await this.sendCommand('data-write-memory-bytes', `${address} ${hexData}`);
    }

    /**
     * Variable operations
     */
    async evaluateExpression(expression) {
        const result = await this.sendCommand('data-evaluate-expression', `"${expression}"`);
        return result.value;
    }

    async listLocals() {
        const result = await this.sendCommand('stack-list-locals', '1');
        return result.variables || [];
    }

    async listVariables() {
        const result = await this.sendCommand('stack-list-variables', '1');
        return result.variables || [];
    }

    /**
     * Call stack
     */
    async getCallStack() {
        const result = await this.sendCommand('stack-list-frames');
        return result.stack || [];
    }

    async selectFrame(frameNum) {
        await this.sendCommand('stack-select-frame', frameNum);
    }

    /**
     * Disassembly
     */
    async disassemble(address, length = 20) {
        const result = await this.sendCommand('data-disassemble',
            `-s ${address} -e ${address + length * 4} -- 0`);
        return result.asm_insns || [];
    }

    /**
     * Helpers
     */
    parseData(data) {
        if (!data) return {};

        // Simple MI parser (basic implementation)
        const result = {};
        const pairs = data.match(/(\w+)=({[^}]*}|"[^"]*"|\[[^\]]*\]|[^,]*)/g);

        if (pairs) {
            for (const pair of pairs) {
                const [key, value] = pair.split('=');
                result[key] = this.parseValue(value);
            }
        }

        return result;
    }

    parseValue(value) {
        if (!value) return null;

        // Remove quotes
        if (value.startsWith('"') && value.endsWith('"')) {
            return this.unescapeString(value.slice(1, -1));
        }

        // Parse array
        if (value.startsWith('[') && value.endsWith(']')) {
            return value.slice(1, -1).split(',').map(v => this.parseValue(v.trim()));
        }

        // Parse object
        if (value.startsWith('{') && value.endsWith('}')) {
            return this.parseData(value.slice(1, -1));
        }

        return value;
    }

    parseRegisters(data, names) {
        const registers = {};
        if (data['register-values']) {
            for (const reg of data['register-values']) {
                const num = parseInt(reg.number);
                const name = (names && names[num]) ? names[num] : `R${num}`;
                if (name && name.length > 0) {
                    registers[name] = reg.value;
                }
            }
        }
        return registers;
    }

    parseMemory(data) {
        if (!data.memory || !data.memory[0]) return null;

        const mem = data.memory[0];
        return {
            address: mem.begin,
            contents: mem.contents
        };
    }

    unescapeString(str) {
        return str.replace(/\\n/g, '\n')
            .replace(/\\t/g, '\t')
            .replace(/\\r/g, '\r')
            .replace(/\\"/g, '"')
            .replace(/\\\\/g, '\\');
    }

    /**
     * Cleanup
     */
    async quit() {
        if (this.gdb) {
            await this.sendCommand('gdb-exit');
            this.gdb.kill();
            this.gdb = null;
            this.running = false;
        }
    }
}

module.exports = GDBBackend;
