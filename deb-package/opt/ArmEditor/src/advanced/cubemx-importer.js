#!/usr/bin/env node
/**
 * STM32CubeMX Project Importer
 * Import CubeMX projects directly into ArmEditor
 */

const fs = require('fs');
const path = require('path');
const xml2js = require('xml2js');

class CubeMXImporter {
    constructor(projectPath) {
        this.projectPath = projectPath;
        this.iocFile = null;
        this.projectConfig = {};
    }

    /**
     * Find .ioc file in project
     */
    findIOCFile() {
        const files = fs.readdirSync(this.projectPath);
        const iocFile = files.find(f => f.endsWith('.ioc'));

        if (!iocFile) {
            throw new Error('No .ioc file found in project');
        }

        this.iocFile = path.join(this.projectPath, iocFile);
        return this.iocFile;
    }

    /**
     * Parse .ioc file
     */
    async parseIOC() {
        const content = fs.readFileSync(this.iocFile, 'utf-8');
        const lines = content.split('\n');

        const config = {};

        for (const line of lines) {
            if (line.includes('=')) {
                const [key, value] = line.split('=').map(s => s.trim());
                config[key] = value;
            }
        }

        this.projectConfig = config;
        return config;
    }

    /**
     * Get MCU information
     */
    getMCUInfo() {
        const mcu = this.projectConfig['Mcu.Name'] ||
                    this.projectConfig['Mcu.Family'] ||
                    'STM32';

        const family = this.projectConfig['Mcu.Family'] || 'STM32F4';
        const package = this.projectConfig['Mcu.Package'] || 'LQFP100';

        return {
            name: mcu,
            family: family,
            package: package,
            frequency: this.projectConfig['Mcu.UserConstants.HCLK'] || '168000000',
            flash: this.extractNumber(this.projectConfig['Mcu.UserConstants.FLASH_SIZE']),
            ram: this.extractNumber(this.projectConfig['Mcu.UserConstants.RAM_SIZE'])
        };
    }

    /**
     * Get enabled peripherals
     */
    getEnabledPeripherals() {
        const peripherals = [];

        for (const [key, value] of Object.entries(this.projectConfig)) {
            if (key.includes('.Mode') && value !== 'Disable') {
                const peripheral = key.split('.')[0];
                if (!peripherals.includes(peripheral)) {
                    peripherals.push(peripheral);
                }
            }
        }

        return peripherals;
    }

    /**
     * Get pin configuration
     */
    getPinConfig() {
        const pins = {};

        for (const [key, value] of Object.entries(this.projectConfig)) {
            if (key.startsWith('P') && key.includes('.Signal')) {
                const pin = key.split('.')[0];
                const signal = value;
                pins[pin] = signal;
            }
        }

        return pins;
    }

    /**
     * Generate Makefile for the project
     */
    generateMakefile() {
        const mcuInfo = this.getMCUInfo();
        const peripherals = this.getEnabledPeripherals();

        // Detect source files
        const srcDir = path.join(this.projectPath, 'Src');
        const incDir = path.join(this.projectPath, 'Inc');
        const driverDir = path.join(this.projectPath, 'Drivers');

        let sources = [];
        let includes = [incDir];

        // Add source files
        if (fs.existsSync(srcDir)) {
            sources = fs.readdirSync(srcDir)
                .filter(f => f.endsWith('.c'))
                .map(f => `Src/${f}`);
        }

        // Add HAL drivers
        if (fs.existsSync(driverDir)) {
            const halPath = path.join(driverDir, 'STM32F4xx_HAL_Driver', 'Src');
            if (fs.existsSync(halPath)) {
                const halSources = fs.readdirSync(halPath)
                    .filter(f => f.endsWith('.c'))
                    .map(f => `Drivers/STM32F4xx_HAL_Driver/Src/${f}`);
                sources.push(...halSources);

                includes.push('Drivers/STM32F4xx_HAL_Driver/Inc');
                includes.push('Drivers/CMSIS/Device/ST/STM32F4xx/Include');
                includes.push('Drivers/CMSIS/Include');
            }
        }

        // Generate Makefile
        const makefile = this.generateMakefileContent(mcuInfo, sources, includes);

        fs.writeFileSync(path.join(this.projectPath, 'Makefile'), makefile);

        return makefile;
    }

    /**
     * Generate Makefile content
     */
    generateMakefileContent(mcuInfo, sources, includes) {
        return `######################################
# ArmEditor Makefile (Generated from CubeMX)
######################################

# Project name
PROJECT = ${path.basename(this.projectPath)}

# MCU
MCU = ${this.getMCUArch(mcuInfo.family)}
MCU_MODEL = ${mcuInfo.name}

# FPU
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard

# Build directory
BUILD_DIR = build

######################################
# Source files
######################################
C_SOURCES = \\
${sources.join(' \\\n')}

# ASM sources
ASM_SOURCES = \\
startup_${mcuInfo.name.toLowerCase()}.s

######################################
# Includes
######################################
C_INCLUDES = \\
${includes.map(i => `-I${i}`).join(' \\\n')}

######################################
# Compiler
######################################
PREFIX = arm-none-eabi-
CC = \${PREFIX}gcc
AS = \${PREFIX}gcc -x assembler-with-cpp
CP = \${PREFIX}objcopy
SZ = \${PREFIX}size

######################################
# Compiler flags
######################################
CPU = -mcpu=\${MCU}

# C defines
C_DEFS = \\
-DUSE_HAL_DRIVER \\
-D\${MCU_MODEL}

# C flags
CFLAGS = \${CPU} -mthumb \${FPU} \${FLOAT-ABI} \${C_DEFS} \${C_INCLUDES}
CFLAGS += -Wall -Wextra -fdata-sections -ffunction-sections

# Optimization
ifeq (\${PROFILE}, debug)
OPT = -O0 -g3 -gdwarf-4
CFLAGS += \${OPT} -DDEBUG
else
OPT = -O2
CFLAGS += \${OPT}
endif

# Dependency flags
CFLAGS += -MMD -MP -MF"\$(@:%.o=%.d)"

######################################
# Linker flags
######################################
LDSCRIPT = \${MCU_MODEL}_FLASH.ld

LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = \${CPU} -mthumb \${FPU} \${FLOAT-ABI}
LDFLAGS += -specs=nano.specs -T\${LDSCRIPT} \${LIBDIR} \${LIBS}
LDFLAGS += -Wl,-Map=\${BUILD_DIR}/\${PROJECT}.map,--cref
LDFLAGS += -Wl,--gc-sections

######################################
# Build targets
######################################
all: \${BUILD_DIR}/\${PROJECT}.elf \${BUILD_DIR}/\${PROJECT}.hex \${BUILD_DIR}/\${PROJECT}.bin

# C objects
OBJECTS = \$(addprefix \${BUILD_DIR}/,\$(notdir \$(C_SOURCES:.c=.o)))
vpath %.c \$(sort \$(dir \$(C_SOURCES)))

# ASM objects
OBJECTS += \$(addprefix \${BUILD_DIR}/,\$(notdir \$(ASM_SOURCES:.s=.o)))
vpath %.s \$(sort \$(dir \$(ASM_SOURCES)))

\${BUILD_DIR}/%.o: %.c Makefile | \${BUILD_DIR}
\t@echo "CC \$<"
\t@\${CC} -c \${CFLAGS} -Wa,-a,-ad,-alms=\${BUILD_DIR}/\$(notdir \$(<:.c=.lst)) \$< -o \$@

\${BUILD_DIR}/%.o: %.s Makefile | \${BUILD_DIR}
\t@echo "AS \$<"
\t@\${AS} -c \${CFLAGS} \$< -o \$@

\${BUILD_DIR}/\${PROJECT}.elf: \${OBJECTS} Makefile
\t@echo "LD \$@"
\t@\${CC} \${OBJECTS} \${LDFLAGS} -o \$@
\t@\${SZ} \$@

\${BUILD_DIR}/%.hex: \${BUILD_DIR}/%.elf | \${BUILD_DIR}
\t@echo "HEX \$@"
\t@\${CP} -O ihex \$< \$@

\${BUILD_DIR}/%.bin: \${BUILD_DIR}/%.elf | \${BUILD_DIR}
\t@echo "BIN \$@"
\t@\${CP} -O binary -S \$< \$@

\${BUILD_DIR}:
\t@mkdir -p \$@

######################################
# Clean
######################################
clean:
\t@rm -rf \${BUILD_DIR}

######################################
# Flash
######################################
flash: all
\t@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \\
\t\t-c "program \${BUILD_DIR}/\${PROJECT}.elf verify reset exit"

######################################
# Debug
######################################
debug: PROFILE=debug
debug: clean all

.PHONY: all clean flash debug
`;
    }

    /**
     * Get ARM architecture from MCU family
     */
    getMCUArch(family) {
        const archMap = {
            'STM32F0': 'cortex-m0',
            'STM32F1': 'cortex-m3',
            'STM32F2': 'cortex-m3',
            'STM32F3': 'cortex-m4',
            'STM32F4': 'cortex-m4',
            'STM32F7': 'cortex-m7',
            'STM32H7': 'cortex-m7',
            'STM32L0': 'cortex-m0plus',
            'STM32L1': 'cortex-m3',
            'STM32L4': 'cortex-m4'
        };

        return archMap[family] || 'cortex-m4';
    }

    /**
     * Extract number from string
     */
    extractNumber(str) {
        if (!str) return 0;
        const match = str.match(/\d+/);
        return match ? parseInt(match[0]) : 0;
    }

    /**
     * Create ArmEditor project config
     */
    createArmEditorConfig() {
        const mcuInfo = this.getMCUInfo();
        const peripherals = this.getEnabledPeripherals();
        const pins = this.getPinConfig();

        const config = {
            name: path.basename(this.projectPath),
            type: 'stm32-cubemx',
            mcu: mcuInfo,
            peripherals: peripherals,
            pins: pins,
            source: 'STM32CubeMX',
            armeditor: {
                version: '1.0.0',
                features: {
                    realtime_graphing: true,
                    svd_viewer: true,
                    rtos_debugging: false,
                    swo_trace: true
                }
            },
            build: {
                toolchain: 'arm-none-eabi-gcc',
                debugger: 'gdb',
                programmer: 'openocd'
            }
        };

        const configPath = path.join(this.projectPath, '.vscode', 'armeditor.json');

        // Create .vscode directory if it doesn't exist
        const vscodeDir = path.join(this.projectPath, '.vscode');
        if (!fs.existsSync(vscodeDir)) {
            fs.mkdirSync(vscodeDir, { recursive: true });
        }

        fs.writeFileSync(configPath, JSON.stringify(config, null, 2));

        return config;
    }

    /**
     * Full import process
     */
    async import() {
        console.log('Importing STM32CubeMX project...');

        // Find .ioc file
        this.findIOCFile();
        console.log(`Found: ${this.iocFile}`);

        // Parse .ioc
        await this.parseIOC();
        console.log('Parsed IOC file');

        // Get project info
        const mcuInfo = this.getMCUInfo();
        console.log(`MCU: ${mcuInfo.name}`);

        const peripherals = this.getEnabledPeripherals();
        console.log(`Peripherals: ${peripherals.join(', ')}`);

        // Generate Makefile
        this.generateMakefile();
        console.log('Generated Makefile');

        // Create ArmEditor config
        this.createArmEditorConfig();
        console.log('Created ArmEditor config');

        console.log('\n✅ Import complete!');
        console.log(`\nTo build:\n  cd ${this.projectPath}\n  make`);

        return {
            mcu: mcuInfo,
            peripherals: peripherals
        };
    }
}

// CLI usage
if (require.main === module) {
    const projectPath = process.argv[2] || process.cwd();

    const importer = new CubeMXImporter(projectPath);
    importer.import().catch(err => {
        console.error('Import failed:', err.message);
        process.exit(1);
    });
}

module.exports = CubeMXImporter;
