const { spawn } = require('child_process');
const EventEmitter = require('events');
const readline = require('readline');

class GDBInterface extends EventEmitter {
    constructor(options = {}) {
        super();

        this.gdbPath = options.gdbPath || 'arm-none-eabi-gdb';
        this.elfFile = options.elfFile;
        this.port = options.port || 3333;
        this.host = options.host || 'localhost';

        this.process = null;
        this.isRunning = false;
        this.breakpoints = new Map();
        this.variables = new Map();
        this.currentLine = null;
        this.currentFile = null;
    }

    async start() {
        return new Promise((resolve, reject) => {
            const args = [
                '--interpreter=mi',
                '--quiet',
                this.elfFile
            ];

            this.process = spawn(this.gdbPath, args);
            this.isRunning = true;

            const rl = readline.createInterface({
                input: this.process.stdout,
                crlfDelay: Infinity
            });

            rl.on('line', (line) => {
                this.handleOutput(line);
            });

            this.process.stderr.on('data', (data) => {
                this.emit('error', data.toString());
            });

            this.process.on('close', (code) => {
                this.isRunning = false;
                this.emit('exit', code);
            });

            // Connect to OpenOCD
            this.sendCommand(`target extended-remote ${this.host}:${this.port}`);
            this.sendCommand('monitor reset halt');
            this.sendCommand('load');

            setTimeout(() => resolve(), 1000);
        });
    }

    sendCommand(command) {
        if (!this.process || !this.isRunning) {
            throw new Error('GDB is not running');
        }

        this.process.stdin.write(command + '\n');
        this.emit('command', command);
    }

    handleOutput(line) {
        this.emit('output', line);

        // Parse MI output
        if (line.startsWith('~')) {
            // Console output
            const text = this.parseMIString(line.substring(1));
            this.emit('console', text);
        } else if (line.startsWith('*stopped')) {
            // Stopped event
            const reason = this.extractValue(line, 'reason');
            const frame = this.extractFrame(line);

            this.currentFile = frame.file;
            this.currentLine = frame.line;

            this.emit('stopped', { reason, frame });
        } else if (line.startsWith('=breakpoint-modified')) {
            // Breakpoint modified
            const bp = this.extractBreakpoint(line);
            this.emit('breakpoint-modified', bp);
        }
    }

    // Execution control
    async continue() {
        this.sendCommand('-exec-continue');
    }

    async stepOver() {
        this.sendCommand('-exec-next');
    }

    async stepInto() {
        this.sendCommand('-exec-step');
    }

    async stepOut() {
        this.sendCommand('-exec-finish');
    }

    async pause() {
        this.process.kill('SIGINT');
    }

    // Breakpoints
    async setBreakpoint(file, line) {
        const location = `${file}:${line}`;
        this.sendCommand(`-break-insert ${location}`);

        const id = this.breakpoints.size + 1;
        this.breakpoints.set(id, { file, line, enabled: true });

        return id;
    }

    async removeBreakpoint(id) {
        this.sendCommand(`-break-delete ${id}`);
        this.breakpoints.delete(id);
    }

    async enableBreakpoint(id) {
        this.sendCommand(`-break-enable ${id}`);
        const bp = this.breakpoints.get(id);
        if (bp) bp.enabled = true;
    }

    async disableBreakpoint(id) {
        this.sendCommand(`-break-disable ${id}`);
        const bp = this.breakpoints.get(id);
        if (bp) bp.enabled = false;
    }

    async listBreakpoints() {
        this.sendCommand('-break-list');
    }

    // Variables and expressions
    async evaluateExpression(expression) {
        return new Promise((resolve) => {
            const handler = (line) => {
                if (line.includes('^done')) {
                    const value = this.extractValue(line, 'value');
                    this.removeListener('output', handler);
                    resolve(value);
                }
            };

            this.on('output', handler);
            this.sendCommand(`-data-evaluate-expression ${expression}`);
        });
    }

    async listVariables() {
        this.sendCommand('-stack-list-variables --simple-values');
    }

    async watchVariable(variable) {
        this.sendCommand(`-break-watch ${variable}`);
    }

    async readMemory(address, count) {
        return new Promise((resolve) => {
            const handler = (line) => {
                if (line.includes('^done')) {
                    const memory = this.extractMemory(line);
                    this.removeListener('output', handler);
                    resolve(memory);
                }
            };

            this.on('output', handler);
            this.sendCommand(`-data-read-memory-bytes ${address} ${count}`);
        });
    }

    async writeMemory(address, value) {
        this.sendCommand(`-data-write-memory-bytes ${address} ${value}`);
    }

    // Stack and backtrace
    async backtrace() {
        this.sendCommand('-stack-list-frames');
    }

    async selectFrame(frameNumber) {
        this.sendCommand(`-stack-select-frame ${frameNumber}`);
    }

    async listLocals() {
        this.sendCommand('-stack-list-locals --simple-values');
    }

    // Registers
    async listRegisters() {
        this.sendCommand('-data-list-register-names');
    }

    async readRegister(register) {
        return new Promise((resolve) => {
            const handler = (line) => {
                if (line.includes('^done')) {
                    const value = this.extractValue(line, 'value');
                    this.removeListener('output', handler);
                    resolve(value);
                }
            };

            this.on('output', handler);
            this.sendCommand(`-data-evaluate-expression $${register}`);
        });
    }

    async writeRegister(register, value) {
        this.sendCommand(`-gdb-set $${register}=${value}`);
    }

    // Utility methods
    parseMIString(str) {
        return str.replace(/^"|"$/g, '').replace(/\\n/g, '\n').replace(/\\t/g, '\t');
    }

    extractValue(line, key) {
        const regex = new RegExp(`${key}="([^"]*)"`, 'i');
        const match = line.match(regex);
        return match ? match[1] : null;
    }

    extractFrame(line) {
        return {
            file: this.extractValue(line, 'file') || this.extractValue(line, 'fullname'),
            line: parseInt(this.extractValue(line, 'line') || '0'),
            func: this.extractValue(line, 'func'),
            addr: this.extractValue(line, 'addr')
        };
    }

    extractBreakpoint(line) {
        return {
            id: parseInt(this.extractValue(line, 'number') || '0'),
            file: this.extractValue(line, 'file'),
            line: parseInt(this.extractValue(line, 'line') || '0'),
            enabled: this.extractValue(line, 'enabled') === 'y'
        };
    }

    extractMemory(line) {
        const content = this.extractValue(line, 'contents');
        if (!content) return [];

        const bytes = [];
        for (let i = 0; i < content.length; i += 2) {
            bytes.push(parseInt(content.substr(i, 2), 16));
        }
        return bytes;
    }

    async stop() {
        if (this.process && this.isRunning) {
            this.sendCommand('-gdb-exit');
            this.process.kill();
            this.isRunning = false;
        }
    }
}

module.exports = GDBInterface;
