/**
 * MCUDetector - Automatic MCU detection from ST-Link
 * Similar to Keil MDK auto-detection
 */

const { spawn } = require('child_process');
const EventEmitter = require('events');

class MCUDetector extends EventEmitter {
    constructor() {
        super();
        this.detectedMCU = null;
    }

    /**
     * Detect MCU via OpenOCD
     * @returns {Object} Detection result
     */
    async detectViaOpenOCD() {
        return new Promise((resolve, reject) => {
            const args = [
                '-f', 'interface/stlink.cfg',
                '-c', 'transport select hla_swd',
                '-c', 'adapter speed 1800',
                '-c', 'init',
                '-c', 'targets',
                '-c', 'shutdown'
            ];

            let output = '';
            const proc = spawn('openocd', args);

            proc.stdout.on('data', (data) => {
                output += data.toString();
            });

            proc.stderr.on('data', (data) => {
                output += data.toString();
            });

            proc.on('close', (code) => {
                const detection = this.parseOpenOCDOutput(output);
                if (detection.success) {
                    this.detectedMCU = detection;
                    this.emit('mcu-detected', detection);
                    resolve(detection);
                } else {
                    reject(new Error('MCU detection failed'));
                }
            });

            proc.on('error', (error) => {
                reject(error);
            });

            setTimeout(() => {
                proc.kill();
                reject(new Error('Detection timeout'));
            }, 10000);
        });
    }

    /**
     * Detect MCU via STM32_Programmer_CLI
     * @returns {Object} Detection result
     */
    async detectViaCubeProgrammer() {
        return new Promise((resolve, reject) => {
            const args = ['-c', 'port=SWD', '-c', 'mode=UR'];

            let output = '';
            const proc = spawn('STM32_Programmer_CLI', args);

            proc.stdout.on('data', (data) => {
                output += data.toString();
            });

            proc.stderr.on('data', (data) => {
                output += data.toString();
            });

            proc.on('close', (code) => {
                const detection = this.parseCubeProgOutput(output);
                if (detection.success) {
                    this.detectedMCU = detection;
                    this.emit('mcu-detected', detection);
                    resolve(detection);
                } else {
                    reject(new Error('MCU detection failed'));
                }
            });

            proc.on('error', (error) => {
                reject(error);
            });

            setTimeout(() => {
                proc.kill();
                reject(new Error('Detection timeout'));
            }, 10000);
        });
    }

    /**
     * Parse OpenOCD output for MCU info
     * @private
     */
    parseOpenOCDOutput(output) {
        // Example: "target halted due to debug-request, current mode: Thread"
        // "xPSR: 0x01000000 pc: 0x08000194 msp: 0x20020000"
        // "Cortex-M4 r0p1 processor detected"

        const cortexMatch = output.match(/Cortex-M(\d)\s+r(\d)p(\d)/i);
        const deviceMatch = output.match(/(STM32[A-Z]\d+[A-Z]+\d+)/i);
        const flashMatch = output.match(/flash size = (\d+)\s*kbytes/i);

        if (cortexMatch || deviceMatch) {
            return {
                success: true,
                core: cortexMatch ? `Cortex-M${cortexMatch[1]}` : 'Unknown',
                revision: cortexMatch ? `r${cortexMatch[2]}p${cortexMatch[3]}` : '',
                deviceName: deviceMatch ? deviceMatch[1] : 'STM32 (Unknown)',
                flashSize: flashMatch ? parseInt(flashMatch[1]) * 1024 : null,
                detectionMethod: 'OpenOCD'
            };
        }

        return { success: false };
    }

    /**
     * Parse STM32CubeProgrammer output
     * @private
     */
    parseCubeProgOutput(output) {
        // Example output:
        // "Device ID   : 0x413"
        // "Device name : STM32F405xx/STM32F407xx/STM32F415xx/STM32F417xx"
        // "Flash size  : 1 MByte"
        // "Device type : MCU"
        // "Revision ID : Rev X"

        const deviceIdMatch = output.match(/Device ID\s*:\s*0x([0-9A-Fa-f]+)/);
        const deviceNameMatch = output.match(/Device name\s*:\s*(.+)/);
        const flashSizeMatch = output.match(/Flash size\s*:\s*(\d+)\s*([KM])Byte/i);
        const revisionMatch = output.match(/Revision ID\s*:\s*(.+)/);

        if (deviceIdMatch) {
            const deviceId = deviceIdMatch[1];
            const deviceName = this.deviceIdToName(deviceId);

            let flashSize = null;
            if (flashSizeMatch) {
                const size = parseInt(flashSizeMatch[1]);
                const unit = flashSizeMatch[2].toUpperCase();
                flashSize = unit === 'M' ? size * 1024 * 1024 : size * 1024;
            }

            return {
                success: true,
                deviceId: '0x' + deviceId,
                deviceName: deviceName || (deviceNameMatch ? deviceNameMatch[1].split('/')[0] : 'Unknown'),
                flashSize: flashSize,
                revision: revisionMatch ? revisionMatch[1] : '',
                detectionMethod: 'STM32CubeProgrammer'
            };
        }

        return { success: false };
    }

    /**
     * Map Device ID to common name
     * @private
     */
    deviceIdToName(deviceId) {
        const idMap = {
            '413': 'STM32F407VGT6',
            '419': 'STM32F429ZIT6',
            '449': 'STM32F746NGH6',
            '450': 'STM32H743ZIT6',
            '415': 'STM32L476RGT6',
            '444': 'STM32F103C8T6',
            '440': 'STM32F030F4P6'
        };

        return idMap[deviceId] || null;
    }

    /**
     * Auto-detect with fallback
     */
    async autoDetect() {
        try {
            // Try CubeProgrammer first (more reliable)
            return await this.detectViaCubeProgrammer();
        } catch (e) {
            console.log('[MCUDetector] CubeProg failed, trying OpenOCD...');
            try {
                return await this.detectViaOpenOCD();
            } catch (e2) {
                throw new Error('Auto-detection failed with both methods');
            }
        }
    }

    /**
     * Get detected MCU info
     */
    getDetectedMCU() {
        return this.detectedMCU;
    }

    /**
     * Match detected MCU with device database
     */
    matchWithDatabase(deviceDb) {
        if (!this.detectedMCU || !this.detectedMCU.deviceName) {
            return null;
        }

        // Try exact match first
        let device = deviceDb.getDevice(this.detectedMCU.deviceName);

        // If not found, try partial match
        if (!device) {
            const results = deviceDb.searchDevices(this.detectedMCU.deviceName.substring(0, 9));
            if (results.length > 0) {
                device = results[0];
            }
        }

        return device;
    }
}

module.exports = MCUDetector;
