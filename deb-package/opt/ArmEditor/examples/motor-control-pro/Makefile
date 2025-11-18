######################################
# Professional Motor Control Makefile
# Better than Keil project files!
######################################

PROJECT = motor-control-pro
MCU = cortex-m4
MCU_MODEL = STM32F407VG

BUILD_DIR = build

######################################
# Source files
######################################
C_SOURCES = \
main.c

ASM_SOURCES = \
startup_stm32f407xx.s

######################################
# Toolchain
######################################
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
OBJDUMP = $(PREFIX)objdump
GDB = $(PREFIX)gdb

######################################
# Compiler flags
######################################
CPU = -mcpu=$(MCU)
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard

# C defines
C_DEFS = \
-DSTM32F407xx \
-DUSE_FULL_ASSERT

# C flags
CFLAGS = $(CPU) -mthumb $(FPU) $(FLOAT-ABI) $(C_DEFS)
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -std=c11

# Debug vs Release
ifeq ($(PROFILE), debug)
OPT = -O0 -g3 -gdwarf-4
CFLAGS += $(OPT) -DDEBUG
CFLAGS += -fno-inline  # Better for debugging
TARGET_ELF = $(BUILD_DIR)/$(PROJECT)-debug.elf
else ifeq ($(PROFILE), release)
OPT = -O2
CFLAGS += $(OPT) -DNDEBUG
CFLAGS += -flto  # Link-time optimization
TARGET_ELF = $(BUILD_DIR)/$(PROJECT).elf
else
# Default: optimized debug
OPT = -Og -g3 -gdwarf-4
CFLAGS += $(OPT) -DDEBUG
TARGET_ELF = $(BUILD_DIR)/$(PROJECT).elf
endif

######################################
# Linker flags
######################################
LDSCRIPT = STM32F407VGTx_FLASH.ld

LIBS = -lc -lm -lnosys
LDFLAGS = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
LDFLAGS += -specs=nano.specs -T$(LDSCRIPT) $(LIBS)
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map,--cref
LDFLAGS += -Wl,--gc-sections  # Remove unused code
LDFLAGS += -Wl,--print-memory-usage

# LTO for release
ifeq ($(PROFILE), release)
LDFLAGS += -flto
endif

######################################
# Build
######################################
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))

all: $(TARGET_ELF) $(BUILD_DIR)/$(PROJECT).hex $(BUILD_DIR)/$(PROJECT).bin size
\t@echo ""
\t@echo "========================================="
\t@echo "✅ Build complete!"
\t@echo "========================================="
\t@echo ""

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
\t@echo "🔨 Compiling: $<"
\t@$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
\t@echo "🔧 Assembling: $<"
\t@$(AS) -c $(CFLAGS) $< -o $@

$(TARGET_ELF): $(OBJECTS) Makefile
\t@echo "🔗 Linking: $@"
\t@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
\t@$(SZ) $@

$(BUILD_DIR)/%.hex: $(TARGET_ELF) | $(BUILD_DIR)
\t@echo "📦 Creating HEX: $@"
\t@$(CP) -O ihex $< $@

$(BUILD_DIR)/%.bin: $(TARGET_ELF) | $(BUILD_DIR)
\t@echo "📦 Creating BIN: $@"
\t@$(CP) -O binary -S $< $@

$(BUILD_DIR):
\t@mkdir -p $@

######################################
# Size report
######################################
size: $(TARGET_ELF)
\t@echo ""
\t@echo "📊 SIZE ANALYSIS:"
\t@$(SZ) -A -d $<
\t@echo ""

######################################
# Disassembly
######################################
disasm: $(TARGET_ELF)
\t@echo "📄 Generating disassembly..."
\t@$(OBJDUMP) -D -S $< > $(BUILD_DIR)/$(PROJECT).disasm
\t@echo "✅ Disassembly saved to $(BUILD_DIR)/$(PROJECT).disasm"

######################################
# AI Analysis
######################################
analyze:
\t@echo "🤖 AI Code Analysis..."
\t@node ../../src/ai/code-assistant.js main.c
\t@echo ""
\t@echo "💾 Memory Analysis..."
\t@node ../../src/ai/memory-analyzer.js $(TARGET_ELF) main.c
\t@echo ""
\t@echo "⚡ Performance Analysis..."
\t@node ../../src/ai/performance-profiler.js $(TARGET_ELF)

######################################
# Flash
######################################
flash: all
\t@echo "⚡ Flashing to device..."
\t@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \\
\t\t-c "program $(TARGET_ELF) verify reset exit"
\t@echo "✅ Flash complete!"

flash-fast: all
\t@st-flash write $(BUILD_DIR)/$(PROJECT).bin 0x8000000

######################################
# Debug
######################################
debug: PROFILE=debug
debug: clean all

release: PROFILE=release
release: clean all

# Start OpenOCD server
gdb-server:
\t@echo "Starting OpenOCD GDB server..."
\t@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

# Start GDB client
gdb-client: debug
\t@$(GDB) $(BUILD_DIR)/$(PROJECT)-debug.elf \\
\t\t-ex "target extended-remote localhost:3333" \\
\t\t-ex "monitor reset halt" \\
\t\t-ex "load" \\
\t\t-ex "monitor reset halt" \\
\t\t-ex "break main" \\
\t\t-ex "continue"

######################################
# Serial monitor
######################################
serial:
\t@echo "Opening serial monitor (115200 baud)..."
\t@minicom -D /dev/ttyUSB0 -b 115200

screen:
\t@screen /dev/ttyUSB0 115200

######################################
# Clean
######################################
clean:
\t@rm -rf $(BUILD_DIR)
\t@echo "🧹 Cleaned!"

######################################
# Help
######################################
help:
\t@echo "ArmEditor Professional Build System"
\t@echo ""
\t@echo "Targets:"
\t@echo "  make          - Build project (optimized debug)"
\t@echo "  make debug    - Build with full debug (-O0 -g3)"
\t@echo "  make release  - Build optimized release (-O2 -flto)"
\t@echo "  make flash    - Flash to device (OpenOCD)"
\t@echo "  make disasm   - Generate disassembly"
\t@echo "  make analyze  - Run AI analysis (BETTER THAN KEIL!)"
\t@echo "  make size     - Show size breakdown"
\t@echo "  make clean    - Clean build files"
\t@echo "  make serial   - Open serial monitor"
\t@echo ""
\t@echo "Debug:"
\t@echo "  make gdb-server  - Start OpenOCD server (Terminal 1)"
\t@echo "  make gdb-client  - Start GDB client (Terminal 2)"
\t@echo ""
\t@echo "AI Features (NOT in Keil!):"
\t@echo "  make analyze  - Bug detection, performance tips, memory analysis"
\t@echo ""

.PHONY: all clean flash debug release size disasm analyze gdb-server gdb-client serial help
