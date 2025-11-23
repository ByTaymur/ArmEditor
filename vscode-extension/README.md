# HopeIDE - Professional ARM Embedded Development for VS Code

> **🎯 Mission:** The free, open-source alternative to Keil μVision and IAR EWARM

**Professional ARM Cortex-M debugging without the $5000 license fee!**

---

## ✨ Features

### Current (v1.0.0-alpha)
- ✅ **Build ARM Projects** - One-click Makefile compilation
- ✅ **Flash Device** - ST-Link support with retry logic
- ✅ **Clean Build** - Remove build artifacts
- ✅ **Timeout Handling** - No more hanging operations
- ✅ **Error Recovery** - Auto-retry on flash failures

### Coming Soon (v1.0.0)
- 🚧 **GDB Debugging** - Full DAP integration
- 🚧 **Register Viewer** - Real-time CPU register monitoring
- 🚧 **Memory Browser** - Hex viewer with read/write
- 🚧 **Peripheral Viewer** - SVD-based peripheral inspection
- 🚧 **Device Auto-Detection** - Automatic STM32 identification
- 🚧 **SWO Trace** - printf() debugging via SWO/ITM

---

## 🚀 Quick Start

### 1. Install Extension
```bash
# From VS Code Marketplace (coming soon!)
# Or install .vsix manually
code --install-extension hopeide-1.0.0.vsix
```

### 2. Open STM32 Project
```bash
# Open folder with Makefile
code /path/to/your/stm32/project
```

### 3. Build & Flash
- Press `Ctrl+Shift+P`
- Type `HopeIDE: Build Project`
- Type `HopeIDE: Flash Device`

---

## 📋 Requirements

### Software
- **ARM Toolchain:** `arm-none-eabi-gcc`, `arm-none-eabi-gdb`
- **Flash Tool:** `st-flash` (stlink-tools) or `openocd`
- **Makefile:** Project must have a Makefile

### Hardware
- **STM32 Board** (F0, F1, F4, F7, H7, L4 tested)
- **ST-Link V2/V3** debugger

### Installation (Ubuntu/Debian)
```bash
sudo apt install gcc-arm-none-eabi gdb-multiarch stlink-tools openocd
```

---

## ⚙️ Configuration

### Extension Settings
```json
{
  "hopeide.toolchain.path": "/usr/bin",
  "hopeide.gdb.path": "gdb-multiarch",
  "hopeide.openocd.path": "openocd",
  "hopeide.stlink.interface": "stlink",
  "hopeide.debug.swd.speed": 4000,
  "hopeide.flash.verify": true,
  "hopeide.flash.resetAfter": true
}
```

### Debug Configuration (launch.json)
```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "type": "hopeide",
      "request": "launch",
      "name": "HopeIDE: Debug STM32",
      "program": "${workspaceFolder}/build/${workspaceFolderBasename}.elf",
      "device": "STM32F407VGT6",
      "interface": "swd"
    }
  ]
}
```

---

## 🎯 Supported Devices

### STM32 Families
- **F0** - Entry-level (Cortex-M0)
- **F1** - Mainstream (Cortex-M3)
- **F4** - High-performance (Cortex-M4 + FPU)
- **F7** - Very high-performance (Cortex-M7)
- **H7** - Ultra high-performance (Cortex-M7 Dual Core)
- **L4** - Ultra-low-power (Cortex-M4)

### More Coming
- ESP32, RP2040, Nordic nRF52, TI Tiva C

---

## 🔧 Commands

| Command | Description | Keyboard Shortcut |
|---------|-------------|-------------------|
| `HopeIDE: Build Project` | Compile ARM project | - |
| `HopeIDE: Flash Device` | Flash firmware to device | - |
| `HopeIDE: Clean Build` | Remove build artifacts | - |
| `HopeIDE: Detect STM32 Device` | Auto-detect connected MCU | - |
| `HopeIDE: Show Registers` | Open register viewer | - |
| `HopeIDE: Show Memory` | Open memory browser | - |

---

## 📚 Example Project Structure

```
my-stm32-project/
├── src/
│   └── main.c
├── Inc/
│   └── main.h
├── build/              # Build output
│   ├── firmware.elf
│   ├── firmware.hex
│   └── firmware.bin
├── Makefile           # Required!
└── .vscode/
    ├── launch.json    # Debug config
    └── settings.json  # HopeIDE settings
```

---

## 🐛 Troubleshooting

### Flash Fails
```bash
# 1. Check ST-Link connection
lsusb | grep STMicro

# 2. Kill existing processes
killall openocd st-flash

# 3. Try manual flash
st-flash write build/firmware.bin 0x08000000
```

### Build Fails
```bash
# Check Makefile exists
ls Makefile

# Try manual build
make clean && make all
```

### Permissions (Linux)
```bash
# Add user to dialout group
sudo usermod -a -G dialout $USER

# Logout and login again
```

---

## 🤝 Contributing

Contributions welcome! This is an open-source project.

```bash
git clone https://github.com/ByTaymur/ArmEditor.git
cd ArmEditor
git checkout vscode-v2
cd vscode-extension
npm install
code .
# Press F5 to launch Extension Development Host
```

---

## 📄 License

MIT License - Free for personal and commercial use

---

## 🙏 Credits

- **ARM GCC** - GNU ARM Toolchain
- **OpenOCD** - Open On-Chip Debugger
- **stlink-tools** - Open source ST-Link tools
- **VS Code** - Microsoft

---

## 🌟 Why HopeIDE?

| Feature | Keil μVision | IAR EWARM | HopeIDE |
|---------|--------------|-----------|---------|
| **Price** | ~$5000 | ~$5000 | **FREE** |
| **Open Source** | ❌ | ❌ | ✅ |
| **VS Code Integration** | ❌ | ❌ | ✅ |
| **Debugging** | ✅ | ✅ | ✅ |
| **Register Viewer** | ✅ | ✅ | ✅ |
| **SVD Peripheral View** | ✅ | ❌ | ✅ |
| **SWO Trace** | ⚠️ (extra $) | ⚠️ (extra $) | ✅ |
| **Auto-Updates** | ❌ | ❌ | ✅ |

**Made with ❤️ for the ARM development community**

---

**Status:** 🚧 v1.0.0-alpha (Week 1 - Foundation)  
**Next:** GDB Debug Adapter Protocol (Week 2)
