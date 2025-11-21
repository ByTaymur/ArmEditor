/**
 * OptionsManager - Professional project configuration manager
 * Manages all project settings similar to Keil's "Options for Target"
 */

const fs = require('fs');
const path = require('path');
const DeviceDatabase = require('../device/device-database');
const MemoryManager = require('../device/memory-manager');

class OptionsManager {
    constructor(projectPath) {
        this.projectPath = projectPath;
        this.configPath = path.join(projectPath, '.hopeide', 'options.json');
        this.deviceDb = new DeviceDatabase();
        this.options = this.loadOptions();
    }

    /**
     * Load project options
     */
    loadOptions() {
        if (fs.existsSync(this.configPath)) {
            try {
                return JSON.parse(fs.readFileSync(this.configPath, 'utf8'));
            } catch (e) {
                console.error('[OptionsManager] Failed to load options:', e);
            }
        }
        return this.getDefaultOptions();
    }

    /**
     * Get default options
     */
    getDefaultOptions() {
        return {
            // Device Tab
            device: {
                name: 'STM32F407VGT6',
                crystal: 8000000,
                clockSpeed: 168000000
            },

            // Target Tab
            target: {
                memoryLayout: 'default',
                stackSize: 0x400,
                heapSize: 0x200,
                useStartupFile: true,
                startupFile: ''
            },

            // Output Tab
            output: {
                buildDirectory: 'build',
                executableName: '$(ProjectName)',
                createHex: true,
                createBin: true,
                createList: true
            },

            // C/C++ Tab
            cc: {
                optimization: '-O2',
                defines: [],
                includes: ['Inc'],
                cFlags: ['-Wall', '-g', '-fdata-sections', '-ffunction-sections'],
                cxxFlags: ['-std=c++11']
            },

            // Assembler Tab
            asm: {
                defines: [],
                includes: [],
                asmFlags: ['-g']
            },

            // Linker Tab
            linker: {
                useDefaultScript: true,
                scriptFile: '',
                libraries: ['-lc', '-lm', '-lnosys'],
                libraryPaths: [],
                ldFlags: ['-Wl,--gc-sections', '-Wl,-Map=$(BuildDir)/$(ProjectName).map']
            },

            // Debug Tab
            debug: {
                debugger: 'gdb',
                interface: 'swd',
                speed: 4000,
                resetMode: 'sysresetreq',
                runToMain: true,
                initScript: ''
            },

            // Utilities Tab
            utilities: {
                flashTool: 'openocd',
                verifyDownload: true,
                eraseFullChip: false,
                resetAndRun: true
            },

            // Build Profiles
            activeProfile: 'Debug',
            profiles: {
                Debug: {
                    optimization: '-O0',
                    defines: ['DEBUG'],
                    debugInfo: true
                },
                Release: {
                    optimization: '-O2',
                    defines: ['NDEBUG'],
                    debugInfo: false
                }
            }
        };
    }

    /**
     * Set device and update related settings
     */
    setDevice(deviceName) {
        const device = this.deviceDb.getDevice(deviceName);
        if (!device) {
            throw new Error(`Device not found: ${deviceName}`);
        }

        this.options.device.name = deviceName;

        // Update compiler flags based on device
        const compilerFlags = this.deviceDb.getCompilerFlags(deviceName);
        if (compilerFlags) {
            this.options.cc.defines = compilerFlags.defines;
        }

        // Update startup file
        const startupFile = this.deviceDb.getStartupFile(deviceName);
        if (startupFile) {
            this.options.target.startupFile = startupFile;
        }

        // Update linker script
        const linkerScript = this.deviceDb.getLinkerScript(deviceName);
        if (linkerScript) {
            this.options.linker.scriptFile = linkerScript;
        }

        this.save();
    }

    /**
     * Set build profile (Debug/Release)
     */
    setBuildProfile(profile) {
        if (!this.options.profiles[profile]) {
            throw new Error(`Profile not found: ${profile}`);
        }

        this.options.activeProfile = profile;
        const profileSettings = this.options.profiles[profile];

        // Apply profile settings
        this.options.cc.optimization = profileSettings.optimization;
        this.options.cc.defines = [
            ...this.deviceDb.getCompilerFlags(this.options.device.name).defines,
            ...profileSettings.defines
        ];

        this.save();
    }

    /**
     * Get current build profile
     */
    getCurrentProfile() {
        return this.options.profiles[this.options.activeProfile];
    }

    /**
     * Generate GCC compiler flags
     */
    getCompilerFlags() {
        const device = this.deviceDb.getDevice(this.options.device.name);
        const flags = this.deviceDb.getCompilerFlags(this.options.device.name);

        const allFlags = [
            flags.cpu,
            '-mthumb',
            flags.fpu.fpu,
            flags.fpu.floatAbi,
            this.options.cc.optimization,
            ...this.options.cc.cFlags,
            ...this.options.cc.defines.map(d => `-D${d}`),
            ...this.options.cc.includes.map(i => `-I${i}`)
        ];

        return allFlags.filter(f => f).join(' ');
    }

    /**
     * Generate linker flags
     */
    getLinkerFlags() {
        const scriptPath = this.options.linker.useDefaultScript
            ? this.generateLinkerScript()
            : this.options.linker.scriptFile;

        const allFlags = [
            `-T${scriptPath}`,
            ...this.options.linker.ldFlags,
            ...this.options.linker.libraries
        ];

        return allFlags.join(' ');
    }

    /**
     * Generate linker script
     */
    generateLinkerScript() {
        const device = this.deviceDb.getDevice(this.options.device.name);
        const memMgr = new MemoryManager({
            name: this.options.device.name,
            memoryMap: device.memoryMap
        });

        const script = memMgr.generateLinkerScript({
            stackSize: this.options.target.stackSize,
            heapSize: this.options.target.heapSize
        });

        const scriptPath = path.join(this.projectPath, 'linker.ld');
        fs.writeFileSync(scriptPath, script, 'utf8');

        return 'linker.ld';
    }

    /**
     * Generate Makefile
     */
    generateMakefile() {
        const ProjectManager = require('./project-manager');
        const pm = new ProjectManager(this.projectPath);

        // Update project manager with our options
        pm.config = this.convertToProjectConfig();
        pm.saveMakefile();
    }

    /**
     * Convert options to project config format
     */
    convertToProjectConfig() {
        return {
            name: path.basename(this.projectPath),
            target: {
                mcu: this.options.device.name,
                ...this.deviceDb.getDevice(this.options.device.name)
            },
            build: {
                optimization: this.options.cc.optimization,
                defines: this.options.cc.defines,
                cflags: this.options.cc.cFlags,
                includes: this.options.cc.includes
            },
            linker: {
                script: this.options.linker.scriptFile || 'linker.ld',
                libraries: this.options.linker.libraries,
                ldflags: this.options.linker.ldFlags
            }
        };
    }

    /**
     * Save options
     */
    save() {
        const dir = path.dirname(this.configPath);
        if (!fs.existsSync(dir)) {
            fs.mkdirSync(dir, { recursive: true });
        }

        fs.writeFileSync(
            this.configPath,
            JSON.stringify(this.options, null, 2),
            'utf8'
        );
    }

    /**
     * Validate options
     */
    validate() {
        const errors = [];

        // Validate device
        if (!this.deviceDb.getDevice(this.options.device.name)) {
            errors.push(`Invalid device: ${this.options.device.name}`);
        }

        // Validate memory sizes
        const device = this.deviceDb.getDevice(this.options.device.name);
        if (device) {
            const memMgr = new MemoryManager({
                name: this.options.device.name,
                memoryMap: device.memoryMap
            });

            const validation = memMgr.validate(this.options.target);
            errors.push(...validation.errors);
        }

        return {
            valid: errors.length === 0,
            errors
        };
    }
}

module.exports = OptionsManager;
