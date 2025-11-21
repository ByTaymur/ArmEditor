/**
 * STM32CubeProgrammer CLI Wrapper
 * Provides robust flash programming with better low-voltage support
 */

const { spawn } = require('child_process');
const EventEmitter = require('events');
const fs = require('fs');

class STM32CubeProgrammer extends EventEmitter {
    constructor() {
        super();
        this.cliPath = 'STM32_Programmer_CLI';
    }

    /**
     * Check if STM32CubeProgrammer is installed
     */
    async isInstalled() {
        return new Promise((resolve) => {
            const proc = spawn(this.cliPath, ['--version'], { shell: true });

            proc.on('error', () => resolve(false));
            proc.on('exit', (code) => resolve(code === 0));

            setTimeout(() => {
                proc.kill();
                resolve(false);
            }, 2000);
        });
    }

    /**
     * Get version info
     */
    async getVersion() {
        return new Promise((resolve, reject) => {
            const proc = spawn(this.cliPath, ['--version'], { shell: true });
            let output = '';

            proc.stdout.on('data', (data) => {
                output += data.toString();
            });

            proc.on('exit', (code) => {
                if (code === 0) {
                    const match = output.match(/Version\s+:\s+([\d.]+)/);
                    resolve(match ? match[1] : 'Unknown');
                } else {
                    reject(new Error('Failed to get version'));
                }
            });

            proc.on('error', reject);
        });
    }

    /**
     * List connected ST-Link devices
     */
    async listDevices() {
        return new Promise((resolve, reject) => {
            const proc = spawn(this.cliPath, ['-l'], { shell: true });
            let output = '';

            proc.stdout.on('data', (data) => {
                output += data.toString();
                this.emit('output', data.toString());
            });

            proc.stderr.on('data', (data) => {
                output += data.toString();
            });

            proc.on('exit', (code) => {
                if (code === 0 || output.includes('ST-LINK')) {
                    const devices = this.parseDeviceList(output);
                    resolve(devices);
                } else {
                    reject(new Error('No devices found'));
                }
            });

            proc.on('error', reject);
        });
    }

    parseDeviceList(output) {
        const devices = [];
        const lines = output.split('\n');

        for (const line of lines) {
            if (line.includes('ST-LINK')) {
                const serialMatch = line.match(/SN:\s*([A-F0-9]+)/i);
                devices.push({
                    type: 'ST-LINK',
                    serial: serialMatch ? serialMatch[1] : 'Unknown'
                });
            }
        }

        return devices;
    }

    /**
     * Get device information
     */
    async getDeviceInfo(index = 0) {
        return new Promise((resolve, reject) => {
            const proc = spawn(this.cliPath, [
                '-c', `port=SWD`, `index=${index}`,
                '-r'
            ], { shell: true });

            let output = '';

            proc.stdout.on('data', (data) => {
                output += data.toString();
                this.emit('output', data.toString());
            });

            proc.stderr.on('data', (data) => {
                output += data.toString();
            });

            proc.on('exit', (code) => {
                const info = this.parseDeviceInfo(output);
                if (info.name) {
                    resolve(info);
                } else {
                    reject(new Error('Failed to read device info'));
                }
            });

            proc.on('error', reject);
        });
    }

    parseDeviceInfo(output) {
        const info = {};

        const nameMatch = output.match(/Device name\s*:\s*(.+)/i);
        const idMatch = output.match(/Device ID\s*:\s*(0x[0-9A-F]+)/i);
        const flashMatch = output.match(/Flash size\s*:\s*(\d+)\s*KB/i);

        if (nameMatch) info.name = nameMatch[1].trim();
        if (idMatch) info.id = idMatch[1];
        if (flashMatch) info.flash = parseInt(flashMatch[1]) * 1024;

        return info;
    }

    /**
     * Flash binary file
     */
    async flashBinary(binPath, address = '0x08000000', index = 0) {
        if (!fs.existsSync(binPath)) {
            throw new Error(`File not found: ${binPath}`);
        }

        return new Promise((resolve, reject) => {
            const args = [
                '-c', `port=SWD`, `index=${index}`, 'mode=UR', 'reset=HWrst',
                '-w', binPath, address,
                '-v',
                '-rst'
            ];

            this.emit('output', `[CubeProgrammer] Flashing ${binPath} to ${address}\n`);

            const proc = spawn(this.cliPath, args, { shell: true });
            let output = '';

            proc.stdout.on('data', (data) => {
                const text = data.toString();
                output += text;
                this.emit('output', text);
            });

            proc.stderr.on('data', (data) => {
                output += data.toString();
            });

            proc.on('exit', (code) => {
                if (code === 0 || output.includes('Download verified successfully')) {
                    this.emit('output', '[CubeProgrammer] ✅ Flash successful\n');
                    resolve({ success: true, output });
                } else {
                    reject(new Error(`Flash failed: ${output}`));
                }
            });

            proc.on('error', (err) => {
                reject(new Error(`Failed to start CubeProgrammer: ${err.message}`));
            });
        });
    }

    /**
     * Erase chip
     */
    async eraseChip(index = 0) {
        return new Promise((resolve, reject) => {
            const proc = spawn(this.cliPath, [
                '-c', `port=SWD`, `index=${index}`,
                '-e', 'all'
            ], { shell: true });

            let output = '';

            proc.stdout.on('data', (data) => {
                output += data.toString();
                this.emit('output', data.toString());
            });

            proc.on('exit', (code) => {
                if (code === 0) {
                    resolve({ success: true });
                } else {
                    reject(new Error('Erase failed'));
                }
            });

            proc.on('error', reject);
        });
    }

    /**
     * Read memory
     */
    async readMemory(address, size, outputFile, index = 0) {
        return new Promise((resolve, reject) => {
            const proc = spawn(this.cliPath, [
                '-c', `port=SWD`, `index=${index}`,
                '-r', address, size, outputFile
            ], { shell: true });

            proc.on('exit', (code) => {
                if (code === 0) {
                    resolve({ success: true, file: outputFile });
                } else {
                    reject(new Error('Read failed'));
                }
            });

            proc.on('error', reject);
        });
    }
}

module.exports = STM32CubeProgrammer;
