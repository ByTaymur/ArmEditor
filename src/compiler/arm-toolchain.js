const { spawn, exec } = require('child_process');
const path = require('path');
const fs = require('fs');

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
        this.interface = config.interface || 'stlink-v2';
        this.target = config.target || 'stm32f4x';
        this.openocdPath = config.openocdPath || 'openocd';
    }

    async flash(elfFile, onProgress = null) {
        const args = [
            '-f', `interface/${this.interface}.cfg`,
            '-f', `target/${this.target}.cfg`,
            '-c', 'init',
            '-c', 'reset halt',
            '-c', `flash write_image erase ${elfFile}`,
            '-c', 'reset run',
            '-c', 'exit'
        ];

        return new Promise((resolve, reject) => {
            const proc = spawn(this.openocdPath, args);

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

    async erase() {
        const args = [
            '-f', `interface/${this.interface}.cfg`,
            '-f', `target/${this.target}.cfg`,
            '-c', 'init',
            '-c', 'reset halt',
            '-c', 'flash erase_sector 0 0 last',
            '-c', 'exit'
        ];

        return new Promise((resolve, reject) => {
            const proc = spawn(this.openocdPath, args);

            proc.on('close', (code) => {
                if (code === 0) {
                    resolve({ success: true });
                } else {
                    reject({ success: false, code });
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
