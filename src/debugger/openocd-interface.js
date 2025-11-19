/**
 * OpenOCD Interface
 * Flash programming, reset control, SWO trace
 */

const { spawn } = require('child_process');
const net = require('net');
const EventEmitter = require('events');

class OpenOCDInterface extends EventEmitter {
    constructor() {
        super();
        this.process = null;
        this.tclClient = null;
        this.running = false;
    }

    /**
     * Start OpenOCD with board configuration
     */
    async start(boardConfig = 'stm32f4x', probe = 'stlink') {
        return new Promise((resolve, reject) => {
            const configFiles = [
                `interface/${probe}.cfg`,
                `target/${boardConfig}.cfg`
            ];

            // Launch OpenOCD
            this.process = spawn('openocd', [
                ...configFiles.flatMap(f => ['-f', f]),
                '-c', 'gdb_port 3333',
                '-c', 'tcl_port 6666',
                '-c', 'telnet_port 4444'
            ]);

            this.process.stdout.on('data', (data) => {
                const output = data.toString();
                this.emit('output', output);

                // Check if ready
                if (output.includes('Info : Listening on port 3333')) {
                    this.running = true;
                    resolve();
                }
            });

            this.process.stderr.on('data', (data) => {
                this.emit('error', data.toString());
            });

            this.process.on('close', (code) => {
                this.emit('closed', code);
                this.running = false;
            });

            // Timeout after 5 seconds
            setTimeout(() => {
                if (!this.running) {
                    reject(new Error('OpenOCD startup timeout'));
                }
            }, 5000);
        });
    }

    /**
     * Connect to OpenOCD TCL port for commands
     */
    async connectTCL(port = 6666) {
        return new Promise((resolve, reject) => {
            this.tclClient = new net.Socket();

            this.tclClient.connect(port, 'localhost', () => {
                resolve();
            });

            this.tclClient.on('error', (err) => {
                reject(err);
            });

            this.tclClient.on('data', (data) => {
                this.emit('tcl-response', data.toString());
            });
        });
    }

    /**
     * Send TCL command to OpenOCD
     */
    async sendCommand(command) {
        return new Promise((resolve, reject) => {
            if (!this.tclClient) {
                reject(new Error('TCL client not connected'));
                return;
            }

            let response = '';

            const handler = (data) => {
                response += data;
                // Wait for prompt
                if (response.includes('> ')) {
                    this.tclClient.removeListener('tcl-response', handler);
                    resolve(response.replace('> ', '').trim());
                }
            };

            this.emit('tcl-response', handler);
            this.tclClient.write(command + '\n');

            // Timeout
            setTimeout(() => {
                this.tclClient.removeListener('tcl-response', handler);
                reject(new Error('Command timeout'));
            }, 10000);
        });
    }

    /**
     * Flash operations
     */
    async flashProgram(hexFile, verify = true) {
        this.emit('flash-start');

        try {
            // Halt target
            await this.sendCommand('reset halt');

            // Flash program
            await this.sendCommand(`program ${hexFile} verify reset`);

            this.emit('flash-complete');
            return true;
        } catch (error) {
            this.emit('flash-error', error);
            throw error;
        }
    }

    async flashErase(address = 0, length = 0) {
        if (length > 0) {
            await this.sendCommand(`flash erase_address ${address} ${length}`);
        } else {
            await this.sendCommand('flash erase_sector 0 0 last');
        }
    }

    async flashWrite(address, data) {
        const hexData = Array.from(data).map(b => b.toString(16).padStart(2, '0')).join('');
        await this.sendCommand(`flash write_image erase ${address} ${hexData}`);
    }

    /**
     * Target control
     */
    async reset(halt = true) {
        await this.sendCommand(halt ? 'reset halt' : 'reset run');
    }

    async halt() {
        await this.sendCommand('halt');
    }

    async resume() {
        await this.sendCommand('resume');
    }

    async step() {
        await this.sendCommand('step');
    }

    /**
     * Memory operations
     */
    async readMemory(address, count, width = 32) {
        const widthCmd = {
            8: 'mdh',
            16: 'mdh',
            32: 'mdw'
        }[width] || 'mdw';

        const result = await this.sendCommand(`${widthCmd} ${address} ${count}`);
        return this.parseMemoryDump(result);
    }

    async writeMemory(address, value, width = 32) {
        const widthCmd = {
            8: 'mwb',
            16: 'mwh',
            32: 'mww'
        }[width] || 'mww';

        await this.sendCommand(`${widthCmd} ${address} ${value}`);
    }

    /**
     * Register operations
     */
    async readRegisters() {
        const result = await this.sendCommand('reg');
        return this.parseRegisters(result);
    }

    async readRegister(name) {
        const result = await this.sendCommand(`reg ${name}`);
        return this.parseRegisterValue(result);
    }

    async writeRegister(name, value) {
        await this.sendCommand(`reg ${name} ${value}`);
    }

    /**
     * SWO (Serial Wire Output) trace
     */
    async enableSWO(port = 0, frequency = 2000000) {
        await this.sendCommand(`tpiu config internal - uart off ${frequency}`);
        await this.sendCommand(`itm port ${port} on`);
        this.emit('swo-enabled');
    }

    async disableSWO() {
        await this.sendCommand('itm ports off');
    }

    /**
     * Breakpoint/Watchpoint
     */
    async setBreakpoint(address) {
        await this.sendCommand(`bp ${address} 2 hw`);
    }

    async removeBreakpoint(address) {
        await this.sendCommand(`rbp ${address}`);
    }

    async setWatchpoint(address, type = 'r') {
        // type: r (read), w (write), a (access)
        await this.sendCommand(`wp ${address} 4 ${type}`);
    }

    async removeWatchpoint(address) {
        await this.sendCommand(`rwp ${address}`);
    }

    /**
     * Target information
     */
    async getTargetInfo() {
        const result = await this.sendCommand('targets');
        return result;
    }

    async getFlashInfo() {
        const result = await this.sendCommand('flash info 0');
        return this.parseFlashInfo(result);
    }

    /**
     * Parsers
     */
    parseMemoryDump(dump) {
        const lines = dump.split('\n');
        const memory = [];

        for (const line of lines) {
            const match = line.match(/0x([0-9a-f]+):\s+([0-9a-f\s]+)/i);
            if (match) {
                const address = parseInt(match[1], 16);
                const values = match[2].trim().split(/\s+/).map(v => parseInt(v, 16));
                memory.push({ address, values });
            }
        }

        return memory;
    }

    parseRegisters(dump) {
        const registers = {};
        const lines = dump.split('\n');

        for (const line of lines) {
            const match = line.match(/(\w+)\s*\(\d+\):\s*0x([0-9a-f]+)/i);
            if (match) {
                registers[match[1]] = `0x${match[2]}`;
            }
        }

        return registers;
    }

    parseRegisterValue(output) {
        const match = output.match(/0x([0-9a-f]+)/i);
        return match ? `0x${match[1]}` : null;
    }

    parseFlashInfo(info) {
        const result = {
            banks: [],
            sectors: []
        };

        const lines = info.split('\n');
        for (const line of lines) {
            // Parse flash bank info
            if (line.includes('flash bank')) {
                const match = line.match(/size:\s*(\d+)/i);
                if (match) {
                    result.size = parseInt(match[1]);
                }
            }

            // Parse sectors
            const sectorMatch = line.match(/#(\d+):\s*0x([0-9a-f]+)\s+\(0x([0-9a-f]+)\s+(\d+)kB\)/i);
            if (sectorMatch) {
                result.sectors.push({
                    number: parseInt(sectorMatch[1]),
                    address: parseInt(sectorMatch[2], 16),
                    size: parseInt(sectorMatch[4]) * 1024
                });
            }
        }

        return result;
    }

    /**
     * Cleanup
     */
    async stop() {
        if (this.tclClient) {
            this.tclClient.destroy();
            this.tclClient = null;
        }

        if (this.process) {
            this.process.kill();
            this.process = null;
            this.running = false;
        }
    }
}

module.exports = OpenOCDInterface;
