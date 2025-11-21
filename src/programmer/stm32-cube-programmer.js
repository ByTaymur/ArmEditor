// STM32CubeProgrammer CLI Wrapper
// Robust flash programming that works even at low voltages (2.8V+)

const { spawn, execSync } = require('child_process');
const fs = require('fs');
const path = require('path');
const EventEmitter = require('events');

class STM32CubeProgrammer extends EventEmitter {
    constructor() {
        super();
        this.cliPath = this.findCLI();
        this.running = false;
    }

    /**
     * Find STM32_Programmer_CLI executable
     */
    findCLI() {
        // Try common locations
        const paths = [
            '/opt/STM32CubeProgrammer/bin/STM32_Programmer_CLI',
            '/usr/local/STM32CubeProgrammer/bin/STM32_Programmer_CLI',
            process.env.HOME + '/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI'
        ];

        for (const p of paths) {
            if (fs.existsSync(p)) {
                return p;
            }
        }

        // Try PATH
        try {
            const result = execSync('which STM32_Programmer_CLI', { encoding: 'utf8' }).trim();
            if (result) return result;
        } catch (e) {
            // Not in PATH
        }

        return null;
    }

    /**
     * Check if CubeProgrammer is installed
     */
    isInstalled() {
        return this.cliPath !== null;
    }

    /**
     * Get version
     */
    getVersion() {
        if (!this.isInstalled()) {
            throw new Error('STM32CubeProgrammer not installed');
        }

        try {
            const output = execSync(`"${this.cliPath}" --version`, { encoding: 'utf8' });
            const match = output.match(/STM32CubeProgrammer\s+v([\d.]+)/);
            return match ? match[1] : 'Unknown';
        } catch (e) {
            return 'Unknown';
        }
    }

    /**
     * List connected ST-Link devices
     * Returns: Array of {index, serialNumber, deviceID}
     */
    async listDevices() {
        if (!this.isInstalled()) {
            throw new Error('STM32CubeProgrammer not installed');
        }

        return new Promise((resolve, reject) => {
            const proc = spawn(this.cliPath, ['-l']);
            let output = '';

            proc.stdout.on('data', (data) => {
                output += data.toString();
            });

            proc.stderr.on('data', (data) => {
                output += data.toString();
            });

            proc.on('close', (code) => {
                const devices = [];

                // Parse output
                // Example: ST-Link SN  : 0670FF484849897267161951
                //          Voltage     : 3.30V
                const lines = output.split('\n');
                let currentDevice = null;

                for (const line of lines) {
                    if (line.includes('ST-Link SN')) {
                        const match = line.match(/:\s*([A-F0-9]+)/);
                        if (match) {
                            currentDevice = { serialNumber: match[1] };
                        }
                    } else if (currentDevice && line.includes('Voltage')) {
                        const match = line.match(/([\d.]+)V/);
                        if (match) {
                            currentDevice.voltage = parseFloat(match[1]);
                            devices.push(currentDevice);
                            currentDevice = null;
                        }
                    }
                }

                resolve(devices);
            });
        });
    }

    /**
     * Connect to device and get info
     * @param {number} index - Device index (0 for first device)
     */
    async getDeviceInfo(index = 0) {
        if (!this.isInstalled()) {
            throw new Error('STM32CubeProgrammer not installed');
        }

        return new Promise((resolve, reject) => {
            const args = ['-c', `port=SWD`, 'index=' + index, '-q'];
            const proc = spawn(this.cliPath, args);
            let output = '';

            proc.stdout.on('data', (data) => {
                output += data.toString();
                this.emit('output', data.toString());
            });

            proc.stderr.on('data', (data) => {
                output += data.toString();
            });

            proc.on('close', (code) => {
                if (code !== 0) {
                    reject(new Error('Connection failed: ' + output));
                    return;
                }

                // Parse device info
                const info = {};

                const deviceMatch = output.match(/Device ID\s*:\s*(0x[0-9A-F]+)/i);
                if (deviceMatch) info.deviceID = deviceMatch[1];

                const flashMatch = output.match(/Flash size\s*:\s*(\d+)\s*KBytes/i);
                if (flashMatch) info.flashSize = parseInt(flashMatch[1]) * 1024;

                const voltageMatch = output.match(/Voltage\s*:\s*([\d.]+)V/i);
                if (voltageMatch) info.voltage = parseFloat(voltageMatch[1]);

                resolve(info);
            });
        });
    }

    /**
     * Flash binary file to device
     * @param {string} binPath - Path to .bin or .hex file
     * @param {number} address - Flash address (default: 0x08000000)
     * @param {number} index - Device index
     */
    async flashBinary(binPath, address = 0x08000000, index = 0) {
        if (!this.isInstalled()) {
            throw new Error('STM32CubeProgrammer not installed');
        }

        if (!fs.existsSync(binPath)) {
            throw new Error(`File not found: ${binPath}`);
        }

        return new Promise((resolve, reject) => {
            const args = [
                '-c', `port=SWD`, `index=${index}`,
                '-w', binPath, address.toString(16),
                '-v',  // Verify after programming
                '-rst' // Reset after programming
            ];

            this.emit('output', `📝 Flashing: ${binPath}\n`);
            this.emit('output', `📍 Address: 0x${address.toString(16)}\n`);

            const proc = spawn(this.cliPath, args);
            this.running = true;

            proc.stdout.on('data', (data) => {
                this.emit('output', data.toString());
            });

            proc.stderr.on('data', (data) => {
                this.emit('output', data.toString());
            });

            proc.on('close', (code) => {
                this.running = false;

                if (code === 0) {
                    this.emit('output', '✅ Flash successful!\n');
                    resolve();
                } else {
                    reject(new Error('Flash failed with code ' + code));
                }
            });
        });
    }

    /**
     * Erase chip
     */
    async eraseChip(index = 0) {
        if (!this.isInstalled()) {
            throw new Error('STM32CubeProgrammer not installed');
        }

        return new Promise((resolve, reject) => {
            const args = [
                '-c', `port=SWD`, `index=${index}`,
                '-e', 'all'
            ];

            const proc = spawn(this.cliPath, args);

            proc.stdout.on('data', (data) => {
                this.emit('output', data.toString());
            });

            proc.stderr.on('data', (data) => {
                this.emit('output', data.toString());
            });

            proc.on('close', (code) => {
                if (code === 0) {
                    resolve();
                } else {
                    reject(new Error('Erase failed'));
                }
            });
        });
    }

    /**
     * Read memory
     * @param {number} address - Memory address
     * @param {number} size - Number of bytes
     * @param {string} outputFile - Output file path
     */
    async readMemory(address, size, outputFile) {
        if (!this.isInstalled()) {
            throw new Error('STM32CubeProgrammer not installed');
        }

        return new Promise((resolve, reject) => {
            const args = [
                '-c', 'port=SWD',
                '-r', outputFile, address.toString(16), size.toString()
            ];

            const proc = spawn(this.cliPath, args);

            proc.on('close', (code) => {
                if (code === 0 && fs.existsSync(outputFile)) {
                    const data = fs.readFileSync(outputFile);
                    resolve(data);
                } else {
                    reject(new Error('Memory read failed'));
                }
            });
        });
    }
}

module.exports = STM32CubeProgrammer;
