// Project Manager - Handle project.json configuration and Makefile generation
const fs = require('fs');
const path = require('path');

class ProjectManager {
    constructor(projectPath) {
        this.projectPath = projectPath;
        this.configPath = path.join(projectPath, 'project.json');
        this.makefilePath = path.join(projectPath, 'Makefile');
        this.config = this.loadConfig();
    }

    /**
     * Load project.json configuration
     */
    loadConfig() {
        if (fs.existsSync(this.configPath)) {
            try {
                const data = fs.readFileSync(this.configPath, 'utf8');
                return JSON.parse(data);
            } catch (e) {
                console.error('[ProjectManager] Failed to load config:', e);
            }
        }

        // Return default config
        return this.getDefaultConfig();
    }

    /**
     * Get default project configuration
     */
    getDefaultConfig() {
        return {
            name: path.basename(this.projectPath),
            version: "1.0.0",
            target: {
                mcu: "STM32F407VGT6",
                family: "STM32F4",
                clock: 168000000,
                flash: 1048576,
                ram: 196608,
                series: "STM32F4xx"
            },
            build: {
                optimization: "-O2",
                defines: ["USE_HAL_DRIVER", "STM32F407xx"],
                cflags: ["-Wall", "-g", "-fdata-sections", "-ffunction-sections"],
                includes: [
                    "Inc",
                    "Drivers/STM32F4xx_HAL_Driver/Inc",
                    "Drivers/CMSIS/Device/ST/STM32F4xx/Include",
                    "Drivers/CMSIS/Include"
                ]
            },
            linker: {
                script: "STM32F407VGTx_FLASH.ld",
                libraries: ["-lc", "-lm", "-lnosys"],
                ldflags: ["-Wl,--gc-sections"]
            },
            sources: {
                dirs: ["Src", "Drivers/STM32F4xx_HAL_Driver/Src"],
                exclude: ["*_template.c"]
            }
        };
    }

    /**
     * Save configuration to project.json
     */
    saveConfig(config = null) {
        if (config) {
            this.config = config;
        }

        try {
            fs.writeFileSync(
                this.configPath,
                JSON.stringify(this.config, null, 2),
                'utf8'
            );
            return true;
        } catch (e) {
            console.error('[ProjectManager] Failed to save config:', e);
            return false;
        }
    }

    /**
     * Generate Makefile from project.json
     */
    generateMakefile() {
        const cfg = this.config;

        let makefile = `# AUTO-GENERATED MAKEFILE - DO NOT EDIT MANUALLY
# Edit project.json and regenerate using Project Settings dialog

# Project name
PROJECT = ${cfg.name}

# Target MCU
MCU = ${cfg.target.family.toLowerCase()}

# Optimization
OPT = ${cfg.build.optimization}

# Build path
BUILD_DIR = build

######################################
# Source files
######################################

# C sources
C_SOURCES = \\
`;

        // Add source files from configured directories
        for (const srcDir of cfg.sources.dirs) {
            const fullPath = path.join(this.projectPath, srcDir);
            if (fs.existsSync(fullPath)) {
                const files = this.findSourceFiles(fullPath, '.c', cfg.sources.exclude || []);
                for (const file of files) {
                    makefile += `${file} \\\n`;
                }
            }
        }

        makefile += `

# ASM sources
ASM_SOURCES = \\
`;

        // Find startup file
        const startupFile = this.findStartupFile();
        if (startupFile) {
            makefile += `${startupFile} \\\n`;
        }

        makefile += `

######################################
# Binaries
######################################
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

######################################
# CFLAGS
######################################

# CPU
CPU = -mcpu=cortex-m4

# FPU
FPU = -mfpu=fpv4-sp-d16

# Float ABI
FLOAT-ABI = -mfloat-abi=hard

# MCU
MCU_FLAGS = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# C defines
`;

        for (const define of cfg.build.defines) {
            makefile += `C_DEFS += -D${define}\n`;
        }

        makefile += `
# C includes
`;

        for (const inc of cfg.build.includes) {
            makefile += `C_INCLUDES += -I${inc}\n`;
        }

        makefile += `
# Compile flags
CFLAGS = $(MCU_FLAGS) $(C_DEFS) $(C_INCLUDES) $(OPT) ${cfg.build.cflags.join(' ')}

# Assembler flags
ASFLAGS = $(MCU_FLAGS) $(OPT) -Wall -fdata-sections -ffunction-sections

######################################
# LDFLAGS
######################################

# Link script
LDSCRIPT = ${cfg.linker.script}

# Libraries
LIBS = ${cfg.linker.libraries.join(' ')}
LIBDIR =
LDFLAGS = $(MCU_FLAGS) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) ${cfg.linker.ldflags.join(' ')} -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map,--cref

# Default action: build all
all: $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).hex $(BUILD_DIR)/$(PROJECT).bin

######################################
# Build rules
######################################

# List of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
\t$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
\t$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(PROJECT).elf: $(OBJECTS) Makefile
\t$(CC) $(OBJECTS) $(LDFLAGS) -o $@
\t$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
\t$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
\t$(BIN) $< $@

$(BUILD_DIR):
\tmkdir $@

######################################
# Clean up
######################################
clean:
\t-rm -fR $(BUILD_DIR)

######################################
# Dependencies
######################################
-include $(wildcard $(BUILD_DIR)/*.d)
`;

        return makefile;
    }

    /**
     * Save generated Makefile
     */
    saveMakefile() {
        const makefile = this.generateMakefile();
        try {
            fs.writeFileSync(this.makefilePath, makefile, 'utf8');
            return true;
        } catch (e) {
            console.error('[ProjectManager] Failed to save Makefile:', e);
            return false;
        }
    }

    /**
     * Find source files in directory
     */
    findSourceFiles(dir, ext, exclude = []) {
        const files = [];

        const walk = (currentDir) => {
            const items = fs.readdirSync(currentDir);

            for (const item of items) {
                const fullPath = path.join(currentDir, item);
                const stat = fs.statSync(fullPath);

                if (stat.isDirectory()) {
                    walk(fullPath);
                } else if (item.endsWith(ext)) {
                    // Check if excluded
                    let excluded = false;
                    for (const pattern of exclude) {
                        if (item.includes(pattern.replace('*', ''))) {
                            excluded = true;
                            break;
                        }
                    }

                    if (!excluded) {
                        const relativePath = path.relative(this.projectPath, fullPath);
                        files.push(relativePath);
                    }
                }
            }
        };

        if (fs.existsSync(dir)) {
            walk(dir);
        }

        return files;
    }

    /**
     * Find startup assembly file
     */
    findStartupFile() {
        const startupDirs = ['Src', 'startup', 'Startup', '.'];

        for (const dir of startupDirs) {
            const fullPath = path.join(this.projectPath, dir);
            if (fs.existsSync(fullPath)) {
                const files = fs.readdirSync(fullPath);
                for (const file of files) {
                    if (file.startsWith('startup_') && file.endsWith('.s')) {
                        return path.join(dir, file);
                    }
                }
            }
        }

        return null;
    }

    /**
     * Validate configuration
     */
    validateConfig(config) {
        const errors = [];

        // Required fields
        if (!config.name) errors.push('Project name is required');
        if (!config.target) errors.push('Target configuration is required');
        if (!config.target.mcu) errors.push('MCU is required');
        if (!config.build) errors.push('Build configuration is required');
        if (!config.linker) errors.push('Linker configuration is required');
        if (!config.linker.script) errors.push('Linker script is required');

        return {
            valid: errors.length === 0,
            errors: errors
        };
    }

    /**
     * Get MCU database (simplified)
     */
    static getMCUDatabase() {
        return {
            'STM32F4': [
                { name: 'STM32F407VGT6', flash: 1024, ram: 192, family: 'STM32F4' },
                { name: 'STM32F401RET6', flash: 512, ram: 96, family: 'STM32F4' },
                { name: 'STM32F411RET6', flash: 512, ram: 128, family: 'STM32F4' },
                { name: 'STM32F429ZIT6', flash: 2048, ram: 256, family: 'STM32F4' }
            ],
            'STM32F7': [
                { name: 'STM32F730V8T6', flash: 64, ram: 256, family: 'STM32F7' },
                { name: 'STM32F746ZGT6', flash: 1024, ram: 320, family: 'STM32F7' },
                { name: 'STM32F767ZIT6', flash: 2048, ram: 512, family: 'STM32F7' }
            ]
        };
    }
}

module.exports = ProjectManager;
