/**
 * Open Source ST-Link Wrapper (stlink-org)
 * Wraps st-flash and st-info tools
 */

const { spawn } = require('child_process');
const EventEmitter = require('events');
const fs = require('fs');

class OpenSourceSTLink extends EventEmitter {
    constructor() {
        super();
        this.flashPath = 'st-flash';
        this.infoPath = 'st-info';
    }

    /**
     * Check if st-link tools are installed
     */
    async isInstalled() {
        return new Promise((resolve) => {
            const proc = spawn(this.infoPath, ['--version'], { shell: true });

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
            const proc = spawn(this.infoPath, ['--version'], { shell: true });
            let output = '';

            proc.stdout.on('data', (data) => {
                output += data.toString();
            });

            proc.stderr.on('data', (data) => {
                output += data.toString();
            });

            proc.on('exit', (code) => {
                if (code === 0) {
                    // Output format is usually just the version string or "vX.X.X"
                    resolve(output.trim());
                } else {
                    reject(new Error('Failed to get version'));
                }
            });

            proc.on('error', reject);
        });
    }

    /**
     * List connected ST-Link devices
     * st-info --probe
     */
    async listDevices() {
        return new Promise((resolve, reject) => {
            const proc = spawn(this.infoPath, ['--probe'], { shell: true });
            let output = '';

            proc.stdout.on('data', (data) => {
                output += data.toString();
                this.emit('output', data.toString());
            });

            proc.stderr.on('data', (data) => {
                output += data.toString();
            });

            proc.on('exit', (code) => {
                if (code === 0) {
                    const devices = this.parseDeviceList(output);
                    resolve(devices);
                } else {
                    // st-info returns non-zero if no devices found sometimes
                    resolve([]);
                }
            });

            proc.on('error', reject);
        });
    }

    parseDeviceList(output) {
        const devices = [];
        const lines = output.split('\n');

        // st-info --probe output format varies, but usually contains:
        // Found 1 stlink programmers
        // serial: 303030303030303030303031
        // openocd: "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x31"
        // flash: 1048576 (pagesize: 16384)
        // sram: 196608
        // chipid: 0x0413
        // descr: F4 device

        let currentDevice = {};

        for (const line of lines) {
            const serialMatch = line.match(/serial:\s*([A-F0-9]+)/i);
            const descrMatch = line.match(/descr:\s*(.+)/i);

            if (serialMatch) {
                if (currentDevice.serial) {
                    devices.push(currentDevice);
                    currentDevice = {};
                }
                currentDevice.serial = serialMatch[1];
                currentDevice.type = 'ST-LINK (Open Source)';
            }

            if (descrMatch) {
                currentDevice.name = descrMatch[1];
            }
        }

        if (currentDevice.serial) {
            devices.push(currentDevice);
        }

        return devices;
    }

    /**
     * Get device information
     * st-info --probe
     */
    async getDeviceInfo(index = 0) {
        // st-info doesn't support index selection easily in CLI without serial
        // For MVP we'll just probe and take the first one or match logic later
        return new Promise((resolve, reject) => {
            const proc = spawn(this.infoPath, ['--probe'], { shell: true });
            let output = '';

            proc.stdout.on('data', (data) => {
                output += data.toString();
            });

            proc.on('exit', (code) => {
                if (code === 0) {
                    const info = this.parseDeviceInfo(output);
                    resolve(info);
                } else {
                    reject(new Error('Failed to read device info'));
                }
            });
        });
    }

    parseDeviceInfo(output) {
        const info = {};

        const chipIdMatch = output.match(/chipid:\s*(0x[0-9a-f]+)/i);
        const flashMatch = output.match(/flash:\s*(\d+)/i);
        const descrMatch = output.match(/descr:\s*(.+)/i);

        if (descrMatch) info.name = descrMatch[1].trim();
        if (chipIdMatch) info.id = chipIdMatch[1];
        if (flashMatch) info.flash = parseInt(flashMatch[1]);

        return info;
    }

    /**
     * Flash binary file
     * st-flash write <file> <addr>
     */
    async flashBinary(binPath, address = '0x08000000', index = 0) {
        if (!fs.existsSync(binPath)) {
            throw new Error(`File not found: ${binPath}`);
        }

        return new Promise((resolve, reject) => {
            // st-flash [--reset] write <path> <addr>
            const args = [
                '--reset',
                'write',
                binPath,
                address
            ];

            this.emit('output', `[st-flash] Flashing ${binPath} to ${address}\n`);

            const proc = spawn(this.flashPath, args, { shell: true });
            let output = '';

            proc.stdout.on('data', (data) => {
                const text = data.toString();
                output += text;
                this.emit('output', text);
            });

            proc.stderr.on('data', (data) => {
                const text = data.toString();
                output += text;
                this.emit('output', text); // st-flash often writes progress to stderr
            });

            proc.on('exit', (code) => {
                if (code === 0) {
                    this.emit('output', '[st-flash] ✅ Flash successful\n');
                    resolve({ success: true, output });
                } else {
                    reject(new Error(`Flash failed with code ${code}`));
                }
            });

            proc.on('error', (err) => {
                reject(new Error(`Failed to start st-flash: ${err.message}`));
            });
        });
    }

    /**
     * Erase chip
     * st-flash erase
     */
    async eraseChip(index = 0) {
        return new Promise((resolve, reject) => {
            const proc = spawn(this.flashPath, ['erase'], { shell: true });
            let output = '';

            proc.stdout.on('data', (data) => {
                output += data.toString();
                this.emit('output', data.toString());
            });

            proc.stderr.on('data', (data) => {
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
     * st-flash read <path> <addr> <size>
     */
    async readMemory(address, size, outputFile, index = 0) {
        return new Promise((resolve, reject) => {
            const proc = spawn(this.flashPath, [
                'read',
                outputFile,
                address,
                size
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

module.exports = OpenSourceSTLink;
