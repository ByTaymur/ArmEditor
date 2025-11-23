# HopeIDE VS Code Extension - Quick Start Guide

## 🚀 Installation

### From VSIX (Manual)
```bash
# Download hopeide-1.0.0.vsix
code --install-extension hopeide-1.0.0.vsix
```

### From Marketplace (Coming Soon!)
```
Extensions → Search "HopeIDE" → Install
```

---

## ⚙️ Prerequisites

### 1. ARM Toolchain
```bash
# Ubuntu/Debian
sudo apt install gcc-arm-none-eabi gdb-multiarch

# Arch Linux
sudo pacman -S arm-none-eabi-gcc arm-none-eabi-gdb

# macOS
brew install arm-none-eabi-gcc
```

### 2. Flash Tools
```bash
# ST-Link Tools
sudo apt install stlink-tools

# OR OpenOCD
sudo apt install openocd
```

### 3. Permissions (Linux)
```bash
sudo usermod -a -G dialout $USER
# Logout and login again!
```

---

## 🎯 First Project

### 1. Open STM32 Project
```bash
code /path/to/your/stm32-project
```

Your project should have:
- `Makefile` (required)
- `src/` folder
- `Inc/` folder (headers)

### 2. Build Project
```
Ctrl+Shift+P → "HopeIDE: Build Project"
```

Or click the 🔨 icon in the editor toolbar.

### 3. Flash Device
```
Ctrl+Shift+P → "HopeIDE: Flash Device"
```

Connect your ST-Link before flashing!

### 4. Debug
```
F5 (Start Debugging)
```

Or create `.vscode/launch.json`:
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "hopeide",
            "request": "launch",
            "name": "Debug STM32",
            "program": "${workspaceFolder}/build/firmware.elf",
            "device": "STM32F407VGT6"
        }
    ]
}
```

---

## 🔧 Configuration

### Settings (File → Preferences → Settings)
```json
{
    "hopeide.toolchain.path": "/usr/bin",
    "hopeide.gdb.path": "gdb-multiarch",
    "hopeide.flash.verify": true,
    "hopeide.flash.resetAfter": true
}
```

---

## 🐛 Troubleshooting

### Flash Fails
```bash
# Check ST-Link connection
lsusb | grep STMicro

# Kill existing processes
killall openocd st-flash gdb

# Try manual flash
st-flash write build/firmware.bin 0x08000000
```

### Build Fails
```bash
# Check Makefile
cat Makefile

# Try manual build
make clean && make all
```

### No Device Detected
```bash
# Check permissions
groups | grep dialout

# Check connection
st-info --probe
```

---

## 📚 Commands

| Command | Keyboard | Description |
|---------|----------|-------------|
| Build Project | - | Compile firmware |
| Flash Device | - | Program STM32 |
| Clean Build | - | Remove build files |
| Detect Device | - | Auto-detect STM32 |
| Show Registers | - | CPU register viewer |
| Show Memory | - | Memory hex viewer |

---

## 🎯 Next Steps

1. ✅ Build your first project
2. ✅ Flash to device
3. ✅ Set breakpoints (F9)
4. ✅ Start debugging (F5)
5. ✅ View registers during debug
6. ✅ Browse memory

---

## 💬 Support

- Issues: https://github.com/ByTaymur/ArmEditor/issues
- Discussions: https://github.com/ByTaymur/ArmEditor/discussions
- Documentation: See README.md

---

**Happy Coding! 🚀**
