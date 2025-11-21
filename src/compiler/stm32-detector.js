const { spawn, execSync } = require('child_process');

/**
 * STM32 Auto-Detection System
 * Automatically detects connected STM32 microcontroller and selects correct OpenOCD configuration
 */
class STM32Detector {
    constructor() {
        // Comprehensive IDCODE database for all STM32 families
        this.idcodeDatabase = {
            // STM32F0 Series
            '0x0bb11477': { family: 'STM32F0', series: 'F030', target: 'stm32f0x', name: 'STM32F030' },
            '0x0bb11477': { family: 'STM32F0', series: 'F051', target: 'stm32f0x', name: 'STM32F051' },
            '0x0bb11477': { family: 'STM32F0', series: 'F072', target: 'stm32f0x', name: 'STM32F072' },
            '0x0bb11477': { family: 'STM32F0', series: 'F091', target: 'stm32f0x', name: 'STM32F091' },

            // STM32F1 Series
            '0x1ba01477': { family: 'STM32F1', series: 'F103', target: 'stm32f1x', name: 'STM32F103' },
            '0x2ba01477': { family: 'STM32F1', series: 'F105', target: 'stm32f1x', name: 'STM32F105' },
            '0x3ba01477': { family: 'STM32F1', series: 'F107', target: 'stm32f1x', name: 'STM32F107' },

            // STM32F2 Series
            '0x4ba00477': { family: 'STM32F2', series: 'F205', target: 'stm32f2x', name: 'STM32F205' },
            '0x4ba00477': { family: 'STM32F2', series: 'F207', target: 'stm32f2x', name: 'STM32F207' },

            // STM32F3 Series
            '0x0ba01477': { family: 'STM32F3', series: 'F303', target: 'stm32f3x', name: 'STM32F303' },
            '0x0ba02477': { family: 'STM32F3', series: 'F334', target: 'stm32f3x', name: 'STM32F334' },
            '0x0ba04477': { family: 'STM32F3', series: 'F373', target: 'stm32f3x', name: 'STM32F373' },

            // STM32F4 Series
            '0x2ba01477': { family: 'STM32F4', series: 'F401', target: 'stm32f4x', name: 'STM32F401' },
            '0x2ba01477': { family: 'STM32F4', series: 'F405', target: 'stm32f4x', name: 'STM32F405' },
            '0x2ba01477': { family: 'STM32F4', series: 'F407', target: 'stm32f4x', name: 'STM32F407' },
            '0x2ba01477': { family: 'STM32F4', series: 'F411', target: 'stm32f4x', name: 'STM32F411' },
            '0x2ba01477': { family: 'STM32F4', series: 'F427', target: 'stm32f4x', name: 'STM32F427' },
            '0x2ba01477': { family: 'STM32F4', series: 'F429', target: 'stm32f4x', name: 'STM32F429' },
            '0x2ba01477': { family: 'STM32F4', series: 'F446', target: 'stm32f4x', name: 'STM32F446' },
            '0x2ba01477': { family: 'STM32F4', series: 'F469', target: 'stm32f4x', name: 'STM32F469' },

            // STM32F7 Series
            '0x5ba02477': { family: 'STM32F7', series: 'F722', target: 'stm32f7x', name: 'STM32F722' },
            '0x5ba02477': { family: 'STM32F7', series: 'F730', target: 'stm32f7x', name: 'STM32F730' },
            '0x5ba02477': { family: 'STM32F7', series: 'F732', target: 'stm32f7x', name: 'STM32F732' },
            '0x5ba02477': { family: 'STM32F7', series: 'F745', target: 'stm32f7x', name: 'STM32F745' },
            '0x5ba02477': { family: 'STM32F7', series: 'F746', target: 'stm32f7x', name: 'STM32F746' },
            '0x5ba02477': { family: 'STM32F7', series: 'F750', target: 'stm32f7x', name: 'STM32F750' },
            '0x5ba02477': { family: 'STM32F7', series: 'F756', target: 'stm32f7x', name: 'STM32F756' },
            '0x5ba02477': { family: 'STM32F7', series: 'F765', target: 'stm32f7x', name: 'STM32F765' },
            '0x5ba02477': { family: 'STM32F7', series: 'F767', target: 'stm32f7x', name: 'STM32F767' },
            '0x5ba02477': { family: 'STM32F7', series: 'F769', target: 'stm32f7x', name: 'STM32F769' },
            '0x5ba02477': { family: 'STM32F7', series: 'F777', target: 'stm32f7x', name: 'STM32F777' },

            // STM32H7 Series
            '0x6ba02477': { family: 'STM32H7', series: 'H743', target: 'stm32h7x', name: 'STM32H743' },
            '0x6ba02477': { family: 'STM32H7', series: 'H750', target: 'stm32h7x', name: 'STM32H750' },
            '0x6ba02477': { family: 'STM32H7', series: 'H753', target: 'stm32h7x', name: 'STM32H753' },

            // STM32L0 Series
            '0x0bc11477': { family: 'STM32L0', series: 'L031', target: 'stm32l0', name: 'STM32L031' },
            '0x0bc11477': { family: 'STM32L0', series: 'L051', target: 'stm32l0', name: 'STM32L051' },
            '0x0bc11477': { family: 'STM32L0', series: 'L071', target: 'stm32l0', name: 'STM32L071' },

            // STM32L1 Series
            '0x4ba00477': { family: 'STM32L1', series: 'L151', target: 'stm32l1x', name: 'STM32L151' },
            '0x4ba00477': { family: 'STM32L1', series: 'L152', target: 'stm32l1x', name: 'STM32L152' },

            // STM32L4 Series
            '0x4ba00477': { family: 'STM32L4', series: 'L432', target: 'stm32l4x', name: 'STM32L432' },
            '0x4ba00477': { family: 'STM32L4', series: 'L433', target: 'stm32l4x', name: 'STM32L433' },
            '0x4ba00477': { family: 'STM32L4', series: 'L476', target: 'stm32l4x', name: 'STM32L476' },
            '0x4ba00477': { family: 'STM32L4', series: 'L486', target: 'stm32l4x', name: 'STM32L486' },

            // STM32L5 Series
            '0x4ba01477': { family: 'STM32L5', series: 'L552', target: 'stm32l5x', name: 'STM32L552' },
            '0x4ba01477': { family: 'STM32L5', series: 'L562', target: 'stm32l5x', name: 'STM32L562' },

            // STM32G0 Series
            '0x0bc11477': { family: 'STM32G0', series: 'G030', target: 'stm32g0x', name: 'STM32G030' },
            '0x0bc11477': { family: 'STM32G0', series: 'G031', target: 'stm32g0x', name: 'STM32G031' },
            '0x0bc11477': { family: 'STM32G0', series: 'G070', target: 'stm32g0x', name: 'STM32G070' },
            '0x0bc11477': { family: 'STM32G0', series: 'G071', target: 'stm32g0x', name: 'STM32G071' },

            // STM32G4 Series
            '0x4ba01477': { family: 'STM32G4', series: 'G431', target: 'stm32g4x', name: 'STM32G431' },
            '0x4ba01477': { family: 'STM32G4', series: 'G441', target: 'stm32g4x', name: 'STM32G441' },
            '0x4ba01477': { family: 'STM32G4', series: 'G473', target: 'stm32g4x', name: 'STM32G473' },
            '0x4ba01477': { family: 'STM32G4', series: 'G474', target: 'stm32g4x', name: 'STM32G474' },
            '0x4ba01477': { family: 'STM32G4', series: 'G483', target: 'stm32g4x', name: 'STM32G483' },
            '0x4ba01477': { family: 'STM32G4', series: 'G484', target: 'stm32g4x', name: 'STM32G484' },

            // STM32WB Series (Wireless)
            '0x4ba01477': { family: 'STM32WB', series: 'WB55', target: 'stm32wbx', name: 'STM32WB55' },

            // STM32WL Series (Wireless)
            '0x4ba01477': { family: 'STM32WL', series: 'WL55', target: 'stm32wlx', name: 'STM32WL55' }
        };
    }

    /**
     * Detect connected STM32 microcontroller
     * @returns {Promise<Object>} Detection result with chip info
     */
    async detect() {
        try {
            // Try to read IDCODE using OpenOCD
            const result = await this.readIDCODE();

            if (result.idcode) {
                const chipInfo = this.idcodeDatabase[result.idcode];

                if (chipInfo) {
                    return {
                        success: true,
                        detected: true,
                        idcode: result.idcode,
                        chip: chipInfo,
                        interface: result.interface || 'stlink',
                        voltage: result.voltage,
                        message: `✅ ${chipInfo.name} detected successfully!`
                    };
                } else {
                    // Unknown IDCODE
                    return {
                        success: false,
                        detected: true,
                        idcode: result.idcode,
                        chip: null,
                        message: `⚠️ Unknown STM32 chip detected (IDCODE: ${result.idcode}). Please check your device.`,
                        suggestion: 'This chip is not in our database. Please verify your connection or update ArmEditor.'
                    };
                }
            } else {
                return {
                    success: false,
                    detected: false,
                    message: '❌ No STM32 chip detected. Please check your ST-Link connection.',
                    suggestion: 'Make sure:\n1. ST-Link is connected via USB\n2. Target board is powered\n3. SWDIO/SWCLK cables are properly connected'
                };
            }
        } catch (error) {
            return {
                success: false,
                detected: false,
                error: error.message,
                message: '❌ Detection failed: ' + error.message
            };
        }
    }

    /**
     * Read IDCODE from connected device using OpenOCD
     * Strategy: Quick probe without full init to avoid disrupting debug sessions
     */
    async readIDCODE() {
        return new Promise((resolve, reject) => {
            // Quick probe - just check connection and get IDCODE from error messages
            const args = [
                '-f', 'interface/stlink.cfg',
                '-c', 'transport select hla_swd',
                '-c', 'adapter speed 2000',
                // Try F7 first (common), will get IDCODE in error if wrong
                '-f', 'target/stm32f7x.cfg',
                '-c', 'init',
                '-c', 'exit'  // Exit immediately, don't stay running
            ];

            const proc = spawn('openocd', args);
            let allOutput = '';

            proc.stdout.on('data', (data) => {
                allOutput += data.toString();
            });

            proc.stderr.on('data', (data) => {
                allOutput += data.toString();
            });

            proc.on('close', (code) => {
                // Check if STLink was found
                if (!allOutput.includes('STLINK')) {
                    reject(new Error('No ST-Link found'));
                    return;
                }

                // Extract voltage
                const voltageMatch = allOutput.match(/Target voltage:\s*([\d.]+)/);
                const voltage = voltageMatch ? parseFloat(voltageMatch[1]) : null;

                // Extract IDCODE from any source
                // 1. From UNEXPECTED/warning (chip mismatch - ideal!)
                let idcodeMatch = allOutput.match(/(?:UNEXPECTED|Warn).*?idcode:?\s*(0x[0-9a-fA-F]+)/i);

                // 2. From normal idcode line
                if (!idcodeMatch) {
                    idcodeMatch = allOutput.match(/idcode:?\s*(0x[0-9a-fA-F]+)/i);
                }

                // 3. From expected vs actual
                if (!idcodeMatch) {
                    const mismatch = allOutput.match(/expected.*?(0x[0-9a-fA-F]+).*?got.*?(0x[0-9a-fA-F]+)/is);
                    if (mismatch) {
                        idcodeMatch = [null, mismatch[2]]; // Use the "got" value
                    }
                }

                if (idcodeMatch) {
                    resolve({
                        idcode: idcodeMatch[1].toLowerCase(),
                        interface: 'stlink',
                        voltage: voltage,
                        output: allOutput
                    });
                } else {
                    reject(new Error('No debugger found'));
                }
            });

            proc.on('error', (err) => {
                reject(new Error('OpenOCD not found: ' + err.message));
            });
        });
    }

    /**
     * Get OpenOCD configuration for detected chip
     */
    getOpenOCDConfig(chipInfo) {
        if (!chipInfo) return null;

        return {
            interface: 'stlink',
            target: chipInfo.target,
            interfaceConfig: 'interface/stlink.cfg',
            targetConfig: `target/${chipInfo.target}.cfg`
        };
    }

    /**
     * Get suggested compiler flags for detected chip
     */
    getCompilerFlags(chipInfo) {
        if (!chipInfo) return null;

        const cpuMap = {
            'STM32F0': 'cortex-m0',
            'STM32F1': 'cortex-m3',
            'STM32F2': 'cortex-m3',
            'STM32F3': 'cortex-m4',
            'STM32F4': 'cortex-m4',
            'STM32F7': 'cortex-m7',
            'STM32H7': 'cortex-m7',
            'STM32L0': 'cortex-m0plus',
            'STM32L1': 'cortex-m3',
            'STM32L4': 'cortex-m4',
            'STM32L5': 'cortex-m33',
            'STM32G0': 'cortex-m0plus',
            'STM32G4': 'cortex-m4',
            'STM32WB': 'cortex-m4',
            'STM32WL': 'cortex-m4'
        };

        const fpuMap = {
            'STM32F4': '-mfpu=fpv4-sp-d16 -mfloat-abi=hard',
            'STM32F7': '-mfpu=fpv5-sp-d16 -mfloat-abi=hard',
            'STM32H7': '-mfpu=fpv5-d16 -mfloat-abi=hard',
            'STM32L4': '-mfpu=fpv4-sp-d16 -mfloat-abi=hard',
            'STM32G4': '-mfpu=fpv4-sp-d16 -mfloat-abi=hard'
        };

        return {
            cpu: cpuMap[chipInfo.family] || 'cortex-m4',
            fpu: fpuMap[chipInfo.family] || '',
            defines: [`${chipInfo.family}`, `USE_HAL_DRIVER`]
        };
    }
}

module.exports = STM32Detector;
