/**
 * CubeMXIntegration - Read CubeMX project configuration
 * Display settings in Options dialog (READ-ONLY)
 */

const fs = require('fs');
const path = require('path');

class CubeMXIntegration {
    constructor(projectPath) {
        this.projectPath = projectPath;
        this.iocFile = null;
        this.config = {};
    }

    /**
     * Find .ioc file in project
     */
    findIOCFile() {
        const files = fs.readdirSync(this.projectPath);
        const iocFile = files.find(f => f.endsWith('.ioc'));

        if (iocFile) {
            this.iocFile = path.join(this.projectPath, iocFile);
            return true;
        }
        return false;
    }

    /**
     * Parse .ioc file for MCU and config
     */
    parseIOCFile() {
        if (!this.iocFile || !fs.existsSync(this.iocFile)) {
            return null;
        }

        const content = fs.readFileSync(this.iocFile, 'utf8');
        const lines = content.split('\n');
        const config = {};

        for (const line of lines) {
            // MCU Selection
            if (line.startsWith('Mcu.Family=')) {
                config.mcuFamily = line.split('=')[1].trim();
            }
            if (line.startsWith('Mcu.Name=')) {
                config.mcuName = line.split('=')[1].trim();
            }
            if (line.startsWith('Mcu.Package=')) {
                config.mcuPackage = line.split('=')[1].trim();
            }

            // Clock Configuration
            if (line.startsWith('RCC.SYSCLKFreq_VALUE=')) {
                config.systemClock = parseInt(line.split('=')[1]);
            }
            if (line.startsWith('RCC.HSE_VALUE=')) {
                config.crystalFreq = parseInt(line.split('=')[1]);
            }

            // Toolchain
            if (line.startsWith('ProjectManager.TargetToolchain=')) {
                config.toolchain = line.split('=')[1].trim();
            }
        }

        this.config.ioc = config;
        return config;
    }

    /**
     * Read CubeMX generated Makefile
     */
    readMakefile() {
        const makefilePath = path.join(this.projectPath, 'Makefile');

        if (!fs.existsSync(makefilePath)) {
            return null;
        }

        const content = fs.readFileSync(makefilePath, 'utf8');
        const config = {
            target: null,
            mcuFlags: [],
            cDefs: [],
            asIncludes: [],
            cIncludes: [],
            sources: [],
            ldscript: null
        };

        const lines = content.split('\n');

        for (const line of lines) {
            const trimmed = line.trim();

            // Target name
            if (trimmed.startsWith('TARGET =')) {
                config.target = trimmed.split('=')[1].trim();
            }

            // MCU flags
            if (trimmed.startsWith('CPU =')) {
                config.mcuFlags.push(trimmed.split('=')[1].trim());
            }
            if (trimmed.startsWith('FPU =')) {
                const fpu = trimmed.split('=')[1].trim();
                if (fpu !== '-mfpu=none') config.mcuFlags.push(fpu);
            }
            if (trimmed.startsWith('FLOAT-ABI =')) {
                config.mcuFlags.push(trimmed.split('=')[1].trim());
            }
            if (trimmed.startsWith('MCU =')) {
                const mcu = trimmed.split('=')[1].trim();
                config.mcuFlags = config.mcuFlags.concat(mcu.split(/\s+/));
            }

            // C Defines
            if (trimmed.startsWith('C_DEFS =')) {
                const defs = trimmed.substring('C_DEFS ='.length).trim();
                config.cDefs = defs.split(/\s+/).filter(d => d.startsWith('-D')).map(d => d.substring(2));
            }

            // C Includes
            if (trimmed.startsWith('C_INCLUDES =')) {
                const includes = trimmed.substring('C_INCLUDES ='.length).trim();
                config.cIncludes = includes.split(/\s+/).filter(i => i.startsWith('-I')).map(i => i.substring(2));
            }

            // Linker script
            if (trimmed.startsWith('LDSCRIPT =')) {
                config.ldscript = trimmed.split('=')[1].trim();
            }
        }

        this.config.makefile = config;
        return config;
    }

    /**
     * Read startup file for memory info
     */
    readStartupFile() {
        const startupFiles = fs.readdirSync(this.projectPath)
            .filter(f => f.startsWith('startup_') && f.endsWith('.s'));

        if (startupFiles.length === 0) {
            return null;
        }

        const startupPath = path.join(this.projectPath, startupFiles[0]);
        const content = fs.readFileSync(startupPath, 'utf8');

        const config = {
            stackSize: 0x400, // Default
            heapSize: 0x200   // Default
        };

        // Parse stack/heap from startup
        const stackMatch = content.match(/Stack_Size\s+EQU\s+0x([0-9A-Fa-f]+)/);
        const heapMatch = content.match(/Heap_Size\s+EQU\s+0x([0-9A-Fa-f]+)/);

        if (stackMatch) {
            config.stackSize = parseInt(stackMatch[1], 16);
        }
        if (heapMatch) {
            config.heapSize = parseInt(heapMatch[1], 16);
        }

        this.config.startup = config;
        return config;
    }

    /**
     * Read linker script for memory layout
     */
    readLinkerScript() {
        let ldscript = this.config.makefile?.ldscript;

        if (!ldscript) {
            // Find *.ld file
            const ldFiles = fs.readdirSync(this.projectPath).filter(f => f.endsWith('.ld'));
            if (ldFiles.length === 0) return null;
            ldscript = ldFiles[0];
        }

        const ldPath = path.join(this.projectPath, ldscript);

        if (!fs.existsSync(ldPath)) {
            return null;
        }

        const content = fs.readFileSync(ldPath, 'utf8');
        const config = {
            memories: []
        };

        // Parse MEMORY section
        const memoryMatch = content.match(/MEMORY\s*\{([^}]+)\}/s);
        if (memoryMatch) {
            const memorySection = memoryMatch[1];
            const memoryLines = memorySection.split('\n');

            for (const line of memoryLines) {
                const match = line.match(/(\w+)\s*\((\w+)\)\s*:\s*ORIGIN\s*=\s*0x([0-9A-Fa-f]+)\s*,\s*LENGTH\s*=\s*0x([0-9A-Fa-f]+)/);
                if (match) {
                    config.memories.push({
                        name: match[1],
                        attributes: match[2],
                        origin: parseInt(match[3], 16),
                        length: parseInt(match[4], 16)
                    });
                }
            }
        }

        this.config.linker = config;
        return config;
    }

    /**
     * Load all CubeMX configuration
     */
    loadAll() {
        const found = this.findIOCFile();

        if (found) {
            this.parseIOCFile();
        }

        this.readMakefile();
        this.readStartupFile();
        this.readLinkerScript();

        return this.config;
    }

    /**
     * Get formatted configuration for Options dialog
     */
    getOptionsConfig() {
        const cfg = this.config;

        return {
            device: {
                name: cfg.ioc?.mcuName || 'Unknown',
                family: cfg.ioc?.mcuFamily || 'Unknown',
                package: cfg.ioc?.mcuPackage || 'Unknown',
                clockSpeed: cfg.ioc?.systemClock || 0,
                crystal: cfg.ioc?.crystalFreq || 0
            },
            target: {
                stackSize: cfg.startup?.stackSize || 0x400,
                heapSize: cfg.startup?.heapSize || 0x200
            },
            output: {
                buildDirectory: 'build',
                executableName: cfg.makefile?.target || 'firmware',
                createHex: true,
                createBin: true
            },
            cc: {
                mcuFlags: cfg.makefile?.mcuFlags || [],
                defines: cfg.makefile?.cDefs || [],
                includes: cfg.makefile?.cIncludes || []
            },
            linker: {
                scriptFile: cfg.makefile?.ldscript || '',
                memories: cfg.linker?.memories || []
            },
            toolchain: cfg.ioc?.toolchain || 'Makefile',
            readOnly: true, // CubeMX managed
            source: 'CubeMX'
        };
    }

    /**
     * Check if project uses CubeMX
     */
    static isCubeMXProject(projectPath) {
        const files = fs.readdirSync(projectPath);
        return files.some(f => f.endsWith('.ioc'));
    }
}

module.exports = CubeMXIntegration;
