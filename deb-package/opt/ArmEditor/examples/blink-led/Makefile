######################################
# ArmEditor Example: LED Blink
# STM32F407VG (Discovery Board)
######################################

PROJECT = blink-led
MCU = cortex-m4
MCU_MODEL = STM32F407VG

BUILD_DIR = build

######################################
# Source files
######################################
C_SOURCES = main.c

ASM_SOURCES = startup_stm32f407xx.s

######################################
# Toolchain
######################################
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
OBJDUMP = $(PREFIX)objdump

######################################
# Compiler flags
######################################
CPU = -mcpu=$(MCU)
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard

# C defines
C_DEFS = -DSTM32F407xx

# C flags
CFLAGS = $(CPU) -mthumb $(FPU) $(FLOAT-ABI) $(C_DEFS)
CFLAGS += -Wall -Wextra -fdata-sections -ffunction-sections
CFLAGS += -std=c11

# Debug vs Release
ifeq ($(PROFILE), debug)
OPT = -O0 -g3 -gdwarf-4
CFLAGS += $(OPT) -DDEBUG
TARGET = $(BUILD_DIR)/$(PROJECT)-debug.elf
else
OPT = -O2
CFLAGS += $(OPT)
TARGET = $(BUILD_DIR)/$(PROJECT).elf
endif

######################################
# Linker flags
######################################
LDSCRIPT = STM32F407VGTx_FLASH.ld

LIBS = -lc -lm -lnosys
LDFLAGS = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
LDFLAGS += -specs=nano.specs -T$(LDSCRIPT) $(LIBS)
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map,--cref
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--print-memory-usage

######################################
# Build
######################################
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))

all: $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).hex $(BUILD_DIR)/$(PROJECT).bin
\t@echo ""
\t@echo "✅ Build complete!"
\t@echo "   ELF: $(BUILD_DIR)/$(PROJECT).elf"
\t@echo "   HEX: $(BUILD_DIR)/$(PROJECT).hex"
\t@echo "   BIN: $(BUILD_DIR)/$(PROJECT).bin"
\t@echo ""

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
\t@echo "🔨 Compiling: $<"
\t@$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
\t@echo "🔧 Assembling: $<"
\t@$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(PROJECT).elf: $(OBJECTS) Makefile
\t@echo "🔗 Linking: $@"
\t@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
\t@$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
\t@echo "📦 Creating HEX: $@"
\t@$(CP) -O ihex $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
\t@echo "📦 Creating BIN: $@"
\t@$(CP) -O binary -S $< $@

$(BUILD_DIR):
\t@mkdir -p $@

######################################
# Disassembly
######################################
disasm: $(BUILD_DIR)/$(PROJECT).elf
\t@$(OBJDUMP) -D -S $< > $(BUILD_DIR)/$(PROJECT).disasm
\t@echo "📄 Disassembly: $(BUILD_DIR)/$(PROJECT).disasm"

######################################
# Flash
######################################
flash: all
\t@echo "⚡ Flashing..."
\t@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \\
\t\t-c "program $(BUILD_DIR)/$(PROJECT).elf verify reset exit"
\t@echo "✅ Flash complete!"

flash-fast: all
\t@st-flash write $(BUILD_DIR)/$(PROJECT).bin 0x8000000

######################################
# Debug
######################################
debug: PROFILE=debug
debug: clean all

gdb-server:
\t@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

gdb-client: debug
\t@arm-none-eabi-gdb $(BUILD_DIR)/$(PROJECT)-debug.elf \\
\t\t-ex "target extended-remote localhost:3333" \\
\t\t-ex "monitor reset halt" \\
\t\t-ex "load" \\
\t\t-ex "monitor reset halt"

######################################
# Clean
######################################
clean:
\t@rm -rf $(BUILD_DIR)
\t@echo "🧹 Cleaned!"

######################################
# Info
######################################
info:
\t@echo "Project: $(PROJECT)"
\t@echo "MCU: $(MCU_MODEL)"
\t@echo "Profile: $(if $(PROFILE),$(PROFILE),release)"
\t@echo "Toolchain: $(PREFIX)"
\t@echo ""
\t@echo "Targets:"
\t@echo "  make          - Build project"
\t@echo "  make debug    - Build with debug symbols (-O0 -g3)"
\t@echo "  make flash    - Flash to device (OpenOCD)"
\t@echo "  make clean    - Clean build files"
\t@echo "  make disasm   - Generate disassembly"
\t@echo "  make info     - Show this info"

.PHONY: all clean flash debug info disasm gdb-server gdb-client
