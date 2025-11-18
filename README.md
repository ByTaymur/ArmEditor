# ArmEditor - Open Source ARM Development IDE

![ArmEditor](resources/banner.png)

**ArmEditor** is a modern, open-source integrated development environment (IDE) specifically designed for ARM Cortex-M microcontroller development. It provides a complete toolchain with compilation, debugging, and flashing capabilities, similar to Keil µVision but free and open source.

## 🎯 Features

### Core Features
- ✅ **Monaco Editor** - Same editor as VS Code with syntax highlighting, IntelliSense, and more
- ✅ **ARM Toolchain Integration** - Full support for `arm-none-eabi-gcc` compiler
- ✅ **GDB Debugger** - Integrated ARM GDB debugger with breakpoints, watch variables, and step execution
- ✅ **OpenOCD Support** - Flash and debug with OpenOCD (ST-Link, J-Link, etc.)
- ✅ **Project Management** - Easy project creation and management
- ✅ **Makefile Support** - Build automation with Make
- ✅ **VS Code Integration** - Can work standalone or integrate with VS Code
- ✅ **Terminal** - Built-in terminal for command execution
- ✅ **Serial Monitor** - UART/Serial communication monitoring

### Supported Targets
- STM32 (All series: F0, F1, F4, F7, H7, L0, L4, etc.)
- NXP LPC Series
- NXP Kinetis
- TI Tiva C
- Atmel SAM
- Any ARM Cortex-M microcontroller

### Supported Debuggers
- ST-Link V2/V3
- J-Link
- CMSIS-DAP
- DAPLink

## 📦 Installation

### Ubuntu/Debian (.deb package)

```bash
# Download the .deb package
wget https://github.com/your-repo/armeditor/releases/latest/download/arm-editor_1.0.0_amd64.deb

# Install
sudo apt install ./arm-editor_1.0.0_amd64.deb

# Install ARM toolchain (if not already installed)
sudo apt install gcc-arm-none-eabi gdb-multiarch openocd
```

### Build from Source

```bash
# Clone repository
git clone https://github.com/your-repo/ArmEditor.git
cd ArmEditor

# Install dependencies
npm install

# Run in development mode
npm run dev

# Build .deb package
chmod +x build-deb.sh
./build-deb.sh
```

## 🚀 Quick Start

### 1. Create New Project

```bash
# Launch ArmEditor
armeditor

# Or from Applications menu
# Applications → Development → ArmEditor
```

Click **"Create New Project"** and select your project location.

### 2. Configure Project

The project structure will be created:

```
my-project/
├── src/           # Source files (.c)
├── inc/           # Header files (.h)
├── lib/           # Libraries
├── build/         # Build output
├── Makefile       # Build configuration
└── .vscode/       # VS Code integration
    ├── tasks.json
    ├── launch.json
    └── armeditor.json
```

### 3. Write Code

Open `src/main.c` and write your code:

```c
#include "stm32f4xx.h"

volatile uint32_t counter = 0;

int main(void) {
    HAL_Init();
    SystemClock_Config();

    while(1) {
        counter++;
        HAL_Delay(100);
    }
}
```

### 4. Build

Press **F7** or click **"Build"** button.

```bash
# Or in terminal
make all
```

### 5. Flash

Click **"Flash"** button or:

```bash
make flash
```

### 6. Debug

Press **F5** or click **"Debug"** button.

- Set breakpoints (F9)
- Step over (F10)
- Step into (F11)
- Watch variables in real-time

## 🔧 Configuration

### Toolchain Configuration

Edit `/etc/armeditor/config.json`:

```json
{
  "version": "1.0.0",
  "toolchain": {
    "prefix": "arm-none-eabi-",
    "path": "/usr/bin"
  },
  "debugger": {
    "gdb": "arm-none-eabi-gdb",
    "openocd": "openocd"
  },
  "vscode": {
    "integration": true,
    "port": 9876
  }
}
```

### Project Configuration

Edit `.vscode/armeditor.json` in your project:

```json
{
  "name": "My ARM Project",
  "type": "arm-cortex-m",
  "mcu": "STM32F4",
  "buildSystem": "make",
  "debugger": {
    "type": "openocd",
    "interface": "stlink-v2",
    "target": "stm32f4x"
  }
}
```

## 🔌 VS Code Integration

ArmEditor can work standalone or integrate with VS Code.

### Installation

The VS Code extension is automatically installed when you install ArmEditor.

Or manually:

```bash
code --install-extension /opt/ArmEditor/vscode-extension
```

### Usage

1. Open your ARM project in VS Code
2. ArmEditor will detect `.vscode/armeditor.json`
3. Use VS Code commands:
   - `ArmEditor: Build Project`
   - `ArmEditor: Flash Device`
   - `ArmEditor: Open in ArmEditor IDE`

### Debug in VS Code

```json
// .vscode/launch.json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug with ArmEditor",
      "type": "armeditor",
      "request": "launch",
      "program": "${workspaceFolder}/build/my_project.elf"
    }
  ]
}
```

## 🎨 User Interface

```
┌─────────────────────────────────────────────────────────┐
│ ArmEditor - ARM Development IDE                     _□X │
├─────────────────────────────────────────────────────────┤
│ 📁 New  📂 Open  🔨 Build  🧹 Clean  ▶️ Debug  ⏹️ Stop  │
├─────────┬───────────────────────────────────────────────┤
│ PROJECT │ main.c                                    ✕   │
│ ├─ src  ├───────────────────────────────────────────────┤
│ │  └─main.c  #include "stm32f4xx.h"                    │
│ ├─ inc  │                                               │
│ └─ lib  │  volatile uint32_t counter = 0;              │
│         │                                               │
│         │  int main(void) {                             │
│         │      HAL_Init();                              │
│         │      while(1) {                               │
│         │          counter++;                           │
│         │      }                                        │
│         │  }                                            │
├─────────┴───────────────────────────────────────────────┤
│ TERMINAL │ OUTPUT │ PROBLEMS                            │
├─────────────────────────────────────────────────────────┤
│ $ make all                                              │
│ 🔨 Building ARM project...                              │
│ ✅ Build successful!                                     │
├─────────────────────────────────────────────────────────┤
│ ⚙️ Ready  Ln 8, Col 10  ARM Cortex-M  Debug            │
└─────────────────────────────────────────────────────────┘
```

## 📚 Documentation

### Build System

ArmEditor uses Makefiles for building:

```makefile
# Makefile
PROJECT = my_project
MCU = cortex-m4

# Sources
C_SOURCES = $(wildcard src/*.c)

# Compiler flags
CFLAGS = -mcpu=$(MCU) -mthumb -Wall -Os

# Build
all:
    arm-none-eabi-gcc $(CFLAGS) $(C_SOURCES) -o build/$(PROJECT).elf

debug: CFLAGS += -O0 -g3
debug: all

flash:
    openocd -f openocd.cfg -c "program build/$(PROJECT).elf verify reset exit"
```

### Debugging

#### Set Breakpoints

Click on line number or press **F9**.

#### Watch Variables

```c
// Add volatile for real-time watching
volatile uint32_t counter = 0;
volatile float temperature = 25.0;
```

#### GDB Commands

```bash
# In terminal
(gdb) break main
(gdb) continue
(gdb) next
(gdb) print counter
(gdb) watch counter
```

## 🛠️ Troubleshooting

### ARM Toolchain Not Found

```bash
sudo apt install gcc-arm-none-eabi gdb-multiarch openocd
```

### ST-Link Not Detected

```bash
# Install ST-Link udev rules
sudo apt install stlink-tools

# Add user to dialout group
sudo usermod -a -G dialout $USER

# Logout and login again
```

### Variables Not Visible in Debugger

```c
// Use volatile
volatile uint32_t counter = 0;

// Build with debug symbols
make clean
make debug  # -O0 -g3
```

## 🤝 Contributing

Contributions are welcome!

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Credits

- **Monaco Editor** - Microsoft (VS Code editor)
- **Electron** - GitHub
- **ARM GCC** - ARM & GNU
- **OpenOCD** - Open On-Chip Debugger

## 📧 Contact

- **Website**: https://armeditor.dev
- **GitHub**: https://github.com/your-repo/ArmEditor
- **Issues**: https://github.com/your-repo/ArmEditor/issues

## 🌟 Star History

If you like this project, please give it a ⭐!

---

**Made with ❤️ for the ARM development community**
