const { spawn, exec, execSync } = require('child_process');
const path = require('path');
const fs = require('fs');
const net = require('net');
const STM32Detector = require('./stm32-detector');

class ARMToolchain {
    constructor() {
        this.prefix = 'arm-none-eabi-';
        this.gcc = `${this.prefix}gcc`;
        this.gxx = `${this.prefix}g++`;
        this.as = `${this.prefix}as`;
        this.ld = `${this.prefix}ld`;
        this.objcopy = `${this.prefix}objcopy`;
        this.objdump = `${this.prefix}objdump`;
        this.size = `${this.prefix}size`;
        this.ar = `${this.prefix}ar`;
        this.gdb = `${this.prefix}gdb`;
        this.nm = `${this.prefix}nm`;

        this.isAvailable = false;
        this.version = null;
    }

    async checkAvailability() {
        return new Promise((resolve) => {
            exec(`${this.gcc} --version`, (error, stdout) => {
                if (error) {
                    this.isAvailable = false;
                    resolve(false);
                } else {
                    this.isAvailable = true;
                    this.version = stdout.split('\n')[0];
                    resolve(true);
                }
            });
        });
    }

    async compile(options) {
        const {
            sources,
            output,
            includePaths = [],
            defines = [],
            flags = [],
            mcu = 'cortex-m4',
            optimization = '-O2'
        } = options;

        const args = [
            `-mcpu=${mcu}`,
            '-mthumb',
            optimization,
            '-Wall',
            '-Wextra',
            '-g3',
            ...flags
        ];

        // Add include paths
        includePaths.forEach(p => args.push('-I', p));

        // Add defines
        defines.forEach(d => args.push('-D', d));

        // Add sources
        args.push(...sources);

        // Output
        args.push('-o', output);

        return this.execute(this.gcc, args);
    }

    async link(options) {
        const {
            objects,
            output,
            linkerScript,
            libPaths = [],
            libs = [],
            flags = []
        } = options;

        const args = [
            ...flags,
            ...objects,
            '-o', output
        ];

        if (linkerScript) {
            args.push('-T', linkerScript);
        }

        libPaths.forEach(p => args.push('-L', p));
        libs.forEach(l => args.push('-l', l));

        return this.execute(this.ld, args);
    }

    async createHex(elfFile, hexFile) {
        return this.execute(this.objcopy, [
            '-O', 'ihex',
            elfFile,
            hexFile
        ]);
    }

    async createBin(elfFile, binFile) {
        return this.execute(this.objcopy, [
            '-O', 'binary',
            elfFile,
            binFile
        ]);
    }

    async getSize(elfFile) {
        return this.execute(this.size, [elfFile]);
    }

    async disassemble(elfFile, outputFile) {
        return this.execute(this.objdump, [
            '-D',
            '-S',
            elfFile
        ], outputFile);
    }

    async getSymbols(elfFile) {
        return this.execute(this.nm, ['-n', elfFile]);
    }

    execute(command, args, outputFile = null) {
        return new Promise((resolve, reject) => {
            const proc = spawn(command, args);

            let stdout = '';
            let stderr = '';

            proc.stdout.on('data', (data) => {
                stdout += data.toString();
            });

            proc.stderr.on('data', (data) => {
                stderr += data.toString();
            });

            proc.on('close', (code) => {
                if (outputFile) {
                    fs.writeFileSync(outputFile, stdout);
                }

                if (code === 0) {
                    resolve({ success: true, stdout, stderr });
                } else {
                    reject({ success: false, stdout, stderr, code });
                }
            });

            proc.on('error', (error) => {
                reject({ success: false, error: error.message });
            });
        });
    }
}

class MakefileBuilder {
    constructor(projectPath, config) {
        this.projectPath = projectPath;
        this.config = config;
    }

    async build(target = 'all', onProgress = null) {
        return new Promise((resolve, reject) => {
            const proc = spawn('make', [target], {
                cwd: this.projectPath,
                shell: true
            });

            let output = '';

            proc.stdout.on('data', (data) => {
                const text = data.toString();
                output += text;
                if (onProgress) onProgress('stdout', text);
            });

            proc.stderr.on('data', (data) => {
                const text = data.toString();
                output += text;
                if (onProgress) onProgress('stderr', text);
            });

            proc.on('close', (code) => {
                if (code === 0) {
                    resolve({ success: true, output });
                } else {
                    reject({ success: false, output, code });
                }
            });
        });
    }

    async clean() {
        return this.build('clean');
    }

    async rebuild(onProgress = null) {
        await this.clean();
        return this.build('all', onProgress);
    }
}

class OpenOCDFlasher {
    constructor(config = {}) {
        this.interface = config.interface || 'stlink';
        this.target = config.target || null; // null = auto-detect
        this.openocdPath = config.openocdPath || 'openocd';
        this.timeout = config.timeout || 60000; // 60 saniye default
        this.gdbPort = config.gdbPort || 3333;
        this.tclPort = config.tclPort || 6666;
        this.telnetPort = config.telnetPort || 4444;
        this.autoDetect = config.autoDetect !== false; // Default true
        this.detector = new STM32Detector();
        this.detectedChip = null;
    }

    /**
     * Auto-detect connected STM32 and configure OpenOCD accordingly
     */
    async detectAndConfigure() {
        if (!this.autoDetect && this.target) {
            // Manual configuration, skip detection
            return {
                success: true,
                mode: 'manual',
                target: this.target,
                message: `Using manual configuration: ${this.target}`
            };
        }

        // Perform auto-detection
        const detection = await this.detector.detect();

        if (detection.success && detection.chip) {
            this.detectedChip = detection.chip;
            this.target = detection.chip.target;

            // Check voltage warning
            let voltageWarning = '';
            if (detection.voltage && detection.voltage < 2.5) {
                voltageWarning = `\n⚠️ Warning: Low target voltage (${detection.voltage.toFixed(2)}V). Normal is 3.3V.`;
            }

            return {
                success: true,
                mode: 'auto',
                chip: detection.chip,
                target: this.target,
                voltage: detection.voltage,
                message: `${detection.message}${voltageWarning}`,
                compilerFlags: this.detector.getCompilerFlags(detection.chip)
            };
        } else {
            // Detection failed
            return {
                success: false,
                mode: 'failed',
                message: detection.message,
                suggestion: detection.suggestion,
                error: detection.error
            };
        }
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
                execSync('pkill -9 -f openocd 2>/dev/null || true', { stdio: 'ignore' });
            } else if (process.platform === 'win32') {
                execSync('taskkill /F /IM openocd.exe 2>nul || exit 0', { stdio: 'ignore' });
            }
            // Port'un serbest kalması için bekle
            await new Promise(resolve => setTimeout(resolve, 1000));
        } catch (e) {
            // Ignore errors
        }
    }

    // Port'ların serbest olmasını bekle
    async waitForPorts(maxRetries = 5) {
        for (let i = 0; i < maxRetries; i++) {
            const gdbInUse = await this.isPortInUse(this.gdbPort);
            const tclInUse = await this.isPortInUse(this.tclPort);
            const telnetInUse = await this.isPortInUse(this.telnetPort);

            if (!gdbInUse && !tclInUse && !telnetInUse) {
                return true;
            }

            // Eski process'leri öldür ve bekle
            await this.killExistingOpenOCD();
            await new Promise(resolve => setTimeout(resolve, 1000));
        }
        return false;
    }

    async flash(elfFile, onProgress = null) {
        // Step 1: Auto-detect chip
        if (onProgress) onProgress('stdout', '🔍 Detecting connected STM32 chip...\n');

        const detection = await this.detectAndConfigure();

        if (!detection.success) {
            if (onProgress) {
                onProgress('stderr', `\n${detection.message}\n`);
                if (detection.suggestion) {
                    onProgress('stderr', `\n${detection.suggestion}\n`);
                }
            }
            throw new Error(detection.message);
        }

        // Show detection results
        if (onProgress) {
            onProgress('stdout', `${detection.message}\n`);
            onProgress('stdout', `📋 Target: ${detection.chip.name} (${detection.chip.family})\n`);
            onProgress('stdout', `🎯 OpenOCD Config: ${this.target}\n`);
            if (detection.compilerFlags) {
                onProgress('stdout', `💻 CPU: ${detection.compilerFlags.cpu}\n`);
            }
            onProgress('stdout', '\n');
        }

        // Step 2: Clean old processes
        if (onProgress) onProgress('stdout', '🧹 Cleaning old OpenOCD processes...\n');
        await this.killExistingOpenOCD();

        // Step 3: Wait for ports
        const portsReady = await this.waitForPorts();
        if (!portsReady) {
            throw new Error('OpenOCD portları (3333, 4444, 6666) hala kullanımda. Lütfen eski debug oturumlarını kapatın.');
        }

        // Step 4: Flash with auto-detected config
        if (onProgress) onProgress('stdout', '⚡ Starting flash operation...\n');

        const args = [
            '-f', `interface/${this.interface}.cfg`,
            '-f', `target/${this.target}.cfg`,
            '-c', 'init',
            '-c', 'reset halt',
            '-c', `flash write_image erase ${elfFile}`,
            '-c', 'verify_image ' + elfFile,
            '-c', 'reset run',
            '-c', 'shutdown'
        ];

        return this.executeWithTimeout(args, onProgress);
    }

    async erase(onProgress = null) {
        await this.killExistingOpenOCD();
        await this.waitForPorts();

        const args = [
            '-f', `interface/${this.interface}.cfg`,
            '-f', `target/${this.target}.cfg`,
            '-c', 'init',
            '-c', 'reset halt',
            '-c', 'flash erase_sector 0 0 last',
            '-c', 'shutdown'
        ];

        return this.executeWithTimeout(args, onProgress);
    }

    executeWithTimeout(args, onProgress = null) {
        return new Promise((resolve, reject) => {
            const proc = spawn(this.openocdPath, args);
            let output = '';
            let killed = false;

            // Timeout ayarla
            const timeoutId = setTimeout(() => {
                killed = true;
                proc.kill('SIGKILL');
                reject({ success: false, error: `OpenOCD timeout (${this.timeout}ms)`, output });
            }, this.timeout);

            proc.stdout.on('data', (data) => {
                const text = data.toString();
                output += text;
                if (onProgress) onProgress('stdout', text);
            });

            proc.stderr.on('data', (data) => {
                const text = data.toString();
                output += text;
                if (onProgress) onProgress('stderr', text);

                // Hata mesajlarını kontrol et
                if (text.includes('Error:') || text.includes('FAILED')) {
                    // Hata var ama process devam edebilir
                }
            });

            proc.on('close', (code) => {
                clearTimeout(timeoutId);
                if (killed) return;

                if (code === 0) {
                    resolve({ success: true, output });
                } else {
                    reject({ success: false, output, code });
                }
            });

            proc.on('error', (error) => {
                clearTimeout(timeoutId);
                reject({ success: false, error: error.message, output });
            });
        });
    }

    // Debug oturumu başlat (OpenOCD server mode)
    async startDebugServer(onProgress = null) {
        // Auto-detect chip if not already done
        if (!this.detectedChip) {
            if (onProgress) onProgress('stdout', '🔍 Detecting connected STM32 chip...\n');

            const detection = await this.detectAndConfigure();

            if (!detection.success) {
                if (onProgress) {
                    onProgress('stderr', `\n${detection.message}\n`);
                    if (detection.suggestion) {
                        onProgress('stderr', `\n${detection.suggestion}\n`);
                    }
                }
                throw new Error(detection.message);
            }

            if (onProgress) {
                onProgress('stdout', `${detection.message}\n`);
                onProgress('stdout', `📋 Target: ${detection.chip.name}\n\n`);
            }
        }

        await this.killExistingOpenOCD();
        await this.waitForPorts();

        const args = [
            '-f', `interface/${this.interface}.cfg`,
            '-f', `target/${this.target}.cfg`,
            '-c', `gdb_port ${this.gdbPort}`,
            '-c', `tcl_port ${this.tclPort}`,
            '-c', `telnet_port ${this.telnetPort}`
        ];

        return new Promise((resolve, reject) => {
            const proc = spawn(this.openocdPath, args);
            let output = '';
            let started = false;

            // Başlatma timeout'u
            const startTimeout = setTimeout(() => {
                if (!started) {
                    proc.kill();
                    reject({ success: false, error: 'OpenOCD başlatma timeout' });
                }
            }, 15000);

            proc.stdout.on('data', (data) => {
                const text = data.toString();
                output += text;
                if (onProgress) onProgress('stdout', text);
            });

            proc.stderr.on('data', (data) => {
                const text = data.toString();
                output += text;
                if (onProgress) onProgress('stderr', text);

                // GDB server başladığını kontrol et
                if (text.includes(`Listening on port ${this.gdbPort} for gdb connections`)) {
                    started = true;
                    clearTimeout(startTimeout);
                    resolve({ success: true, process: proc, output });
                }
            });

            proc.on('error', (error) => {
                clearTimeout(startTimeout);
                reject({ success: false, error: error.message });
            });

            proc.on('close', (code) => {
                clearTimeout(startTimeout);
                if (!started) {
                    reject({ success: false, code, output });
                }
            });
        });
    }
}

module.exports = {
    ARMToolchain,
    MakefileBuilder,
    OpenOCDFlasher
};
