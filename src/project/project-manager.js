// ProjectManager - Handle project configuration and Makefile generation
const fs = require('fs');
const path = require('path');

class ProjectManager {
    constructor(projectPath) {
        this.projectPath = projectPath;
        this.configPath = path.join(projectPath, 'project.json');
        this.config = this.loadConfig();
    }

    loadConfig() {
        if (fs.existsSync(this.configPath)) {
            try {
                return JSON.parse(fs.readFileSync(this.configPath, 'utf8'));
            } catch (e) {
                console.error('[ProjectManager] Failed to load config:', e);
            }
        }
        return this.getDefaultConfig();
    }

    getDefaultConfig() {
        return {
            name: path.basename(this.projectPath),
            version: "1.0.0",
            target: {
                mcu: "STM32F407VGT6",
                family: "STM32F4",
                clock: 168000000,
                flash: 1048576,
                ram: 196608
            },
            build: {
                optimization: "-O2",
                defines: ["USE_HAL_DRIVER", "STM32F407xx"],
                cflags: ["-Wall", "-g", "-fdata-sections", "-ffunction-sections"],
                includes: ["Inc", "Drivers/STM32F4xx_HAL_Driver/Inc"]
            },
            linker: {
                script: "STM32F407VGTx_FLASH.ld",
                libraries: ["-lc", "-lm", "-lnosys"],
                ldflags: ["-Wl,--gc-sections"]
            }
        };
    }

    saveConfig() {
        fs.writeFileSync(this.configPath, JSON.stringify(this.config, null, 2), 'utf8');
    }

    validateConfig(config) {
        const errors = [];
        if (!config.name) errors.push("Project name is required");
        if (!config.target?.mcu) errors.push("Target MCU is required");
        return { valid: errors.length === 0, errors };
    }

    generateMakefile() {
        const c = this.config;
        return `# Auto-generated Makefile
PROJECT = ${c.name}
MCU = ${c.target.mcu}
OPTIMIZATION = ${c.build.optimization}

# Defines
DEFS = ${c.build.defines.map(d => `-D${d}`).join(' ')}

# Includes  
INCLUDES = ${c.build.includes.map(i => `-I${i}`).join(' ')}

# C flags
CFLAGS = -mcpu=cortex-m4 -mthumb ${this.config.build.cflags.join(' ')} $(DEFS) $(INCLUDES)

# Linker
LDSCRIPT = ${c.linker.script}
LIBS = ${c.linker.libraries.join(' ')}
LDFLAGS = ${c.linker.ldflags.join(' ')}

# Sources
SOURCES = $(wildcard Src/*.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(PROJECT).hex

$(PROJECT).elf: $(OBJECTS)
\tarm-none-eabi-gcc $(OBJECTS) $(LDFLAGS) -T$(LDSCRIPT) -o $@ $(LIBS)

$(PROJECT).hex: $(PROJECT).elf
\tarm-none-eabi-objcopy -O ihex $< $@

%.o: %.c
\tarm-none-eabi-gcc -c $(CFLAGS) $< -o $@

clean:
\trm -f $(OBJECTS) $(PROJECT).elf $(PROJECT).hex

.PHONY: all clean
`;
    }

    saveMakefile() {
        const makefile = this.generateMakefile();
        fs.writeFileSync(path.join(this.projectPath, 'Makefile'), makefile, 'utf8');
    }

    static getMCUDatabase() {
        return {
            'STM32F4': [
                { name: 'STM32F407VGT6', flash: 1024, ram: 192 },
                { name: 'STM32F429ZIT6', flash: 2048, ram: 256 }
            ]
        };
    }
}

module.exports = ProjectManager;
