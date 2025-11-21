const { spawn, execSync } = require('child_process');
const EventEmitter = require('events');
const readline = require('readline');
const net = require('net');

class GDBInterface extends EventEmitter {
    constructor(options = {}) {
        super();

        // Prevent memory leak warnings - we use many event listeners for commands
        this.setMaxListeners(50);

        this.gdbPath = options.gdbPath || this.detectGDBPath();
        this.elfFile = options.elfFile;
        this.port = options.port || 3333;
        this.host = options.host || 'localhost';
        this.commandTimeout = options.commandTimeout || 10000; // 10 saniye default timeout

        this.process = null;
        this.isRunning = false;
        this.breakpoints = new Map();
        this.variables = new Map();
        this.currentLine = null;
        this.currentFile = null;
        this.pendingCommands = new Map();
        this.commandId = 0;
    }

    // Auto-detect available GDB
    detectGDBPath() {
        const candidates = ['gdb-multiarch', 'arm-none-eabi-gdb'];

        for (const candidate of candidates) {
            try {
                execSync(`which ${candidate}`, { stdio: 'ignore' });
                return candidate;
            } catch (e) {
                // Try next candidate
            }
        }

        // Fallback
        return 'arm-none-eabi-gdb';
    }

    // Timeout ile komut çalıştırma helper
    withTimeout(promise, ms, errorMsg = 'Command timeout') {
        return Promise.race([
            promise,
            new Promise((_, reject) =>
                setTimeout(() => reject(new Error(`${errorMsg} after ${ms}ms`)), ms)
            )
        ]);
    }

    // Port kullanımda mı kontrol et
    async isPortInUse(port) {
        return new Promise((resolve) => {
            const server = net.createServer();
            server.once('error', () => resolve(true));
            server.once('listening', () => {
                server.close();
                resolve(false);
            });
            server.listen(port);
        });
    }

    // Eski OpenOCD process'lerini temizle
    async killExistingOpenOCD() {
        try {
            if (process.platform === 'linux' || process.platform === 'darwin') {
                execSync('pkill -f openocd 2>/dev/null || true', { stdio: 'ignore' });
            } else if (process.platform === 'win32') {
                execSync('taskkill /F /IM openocd.exe 2>nul || exit 0', { stdio: 'ignore' });
            }
            // Port'un serbest kalması için bekle
            await new Promise(resolve => setTimeout(resolve, 500));
        } catch (e) {
            // Ignore errors
        }
    }

    async start() {
        // Önce eski OpenOCD process'lerini temizle
        await this.killExistingOpenOCD();

        // Port kontrolü
        const gdbPortInUse = await this.isPortInUse(this.port);
        if (gdbPortInUse) {
            this.emit('warning', `Port ${this.port} zaten kullanımda, temizleniyor...`);
            await this.killExistingOpenOCD();
            await new Promise(resolve => setTimeout(resolve, 1000));
        }

        return new Promise((resolve, reject) => {
            const args = [
                '--interpreter=mi',
                '--quiet',
                this.elfFile
            ];

            const startTimeout = setTimeout(() => {
                reject(new Error('GDB başlatma timeout (15 saniye)'));
                this.stop();
            }, 15000);

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

            this.process.on('error', (err) => {
                clearTimeout(startTimeout);
                reject(new Error(`GDB başlatılamadı: ${err.message}`));
            });

            // Connect to OpenOCD with timeout
            setTimeout(async () => {
                try {
                    this.sendCommand(`target extended-remote ${this.host}:${this.port}`);

                    // Bağlantı için bekle
                    await new Promise(resolve => setTimeout(resolve, 1000));

                    this.sendCommand('monitor reset halt');
                    await new Promise(resolve => setTimeout(resolve, 500));

                    this.sendCommand('load');

                    clearTimeout(startTimeout);
                    resolve();
                } catch (err) {
                    clearTimeout(startTimeout);
                    reject(err);
                }
            }, 500);
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
    async evaluateExpression(expression, timeout = null) {
        const ms = timeout || this.commandTimeout;
        return this.withTimeout(
            new Promise((resolve, reject) => {
                const handler = (line) => {
                    if (line.includes('^done')) {
                        const value = this.extractValue(line, 'value');
                        this.removeListener('output', handler);
                        resolve(value);
                    } else if (line.includes('^error')) {
                        this.removeListener('output', handler);
                        reject(new Error(this.extractValue(line, 'msg') || 'Expression evaluation failed'));
                    }
                };

                this.on('output', handler);
                this.sendCommand(`-data-evaluate-expression ${expression}`);
            }),
            ms,
            `evaluateExpression(${expression}) timeout`
        );
    }

    async listVariables() {
        this.sendCommand('-stack-list-variables --simple-values');
    }

    async watchVariable(variable) {
        this.sendCommand(`-break-watch ${variable}`);
    }

    async readMemory(address, count, timeout = null) {
        const ms = timeout || this.commandTimeout;
        return this.withTimeout(
            new Promise((resolve, reject) => {
                const handler = (line) => {
                    if (line.includes('^done')) {
                        const memory = this.extractMemory(line);
                        this.removeListener('output', handler);
                        resolve(memory);
                    } else if (line.includes('^error')) {
                        this.removeListener('output', handler);
                        reject(new Error(this.extractValue(line, 'msg') || 'Memory read failed'));
                    }
                };

                this.on('output', handler);
                this.sendCommand(`-data-read-memory-bytes ${address} ${count}`);
            }),
            ms,
            `readMemory(${address}, ${count}) timeout`
        );
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

    async readRegister(register, timeout = null) {
        const ms = timeout || this.commandTimeout;
        return this.withTimeout(
            new Promise((resolve, reject) => {
                const handler = (line) => {
                    if (line.includes('^done')) {
                        const value = this.extractValue(line, 'value');
                        this.removeListener('output', handler);
                        resolve(value);
                    } else if (line.includes('^error')) {
                        this.removeListener('output', handler);
                        reject(new Error(this.extractValue(line, 'msg') || 'Register read failed'));
                    }
                };

                this.on('output', handler);
                this.sendCommand(`-data-evaluate-expression $${register}`);
            }),
            ms,
            `readRegister(${register}) timeout`
        );
    }

    /**
     * Read variable asynchronously (for real-time graphing)
     */
    async readVariableAsync(varName) {
        return new Promise((resolve, reject) => {
            const timeout = setTimeout(() => {
                this.removeListener('output', handler);
                reject(new Error('Timeout reading variable'));
            }, 1000);

            const handler = (line) => {
                if (line.includes('^done')) {
                    clearTimeout(timeout);
                    const value = this.extractValue(line, 'value');
                    this.removeListener('output', handler);
                    resolve(parseFloat(value) || 0);
                } else if (line.includes('^error')) {
                    clearTimeout(timeout);
                    this.removeListener('output', handler);
                    resolve(0); // Return 0 on error
                }
            };

            this.on('output', handler);
            this.sendCommand(`-data-evaluate-expression ${varName}`);
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
            try {
                this.sendCommand('-gdb-exit');
            } catch (e) {
                // Ignore
            }
            this.process.kill();
            this.isRunning = false;
        }

        // OpenOCD process'lerini de temizle
        await this.killExistingOpenOCD();

        this.emit('stopped');
    }

    // Tüm register'ları oku (batch)
    async readAllRegisters(timeout = null) {
        const registers = ['r0', 'r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7',
            'r8', 'r9', 'r10', 'r11', 'r12', 'sp', 'lr', 'pc'];
        const results = {};

        for (const reg of registers) {
            try {
                results[reg] = await this.readRegister(reg, timeout);
            } catch (e) {
                results[reg] = 'ERROR';
            }
        }

        return results;
    }
}

module.exports = GDBInterface;
