# HopeIDE Extension - Test Guide

## 🧪 Testing Options

### Option 1: VS Code Development Host (Recommended)
```bash
cd vscode-extension
code .
# Press F5 to launch Extension Development Host
```

This opens a new VS Code window with the extension loaded for testing.

### Option 2: Install VSIX Locally
```bash
# Create VSIX (if package works)
npm run package

# OR use manual script
./package-manual.sh

# Install
code --install-extension hopeide-1.0.0.vsix
```

### Option 3: Manual Testing
```bash
# 1. Open extension folder in VS Code
cd vscode-extension
code .

# 2. Press F5 (Run > Start Debugging)
# This will:
#   - Compile TypeScript
#   - Launch Extension Development Host
#   - Load extension for testing
```

---

## 🎯 Test Checklist

### 1. Extension Activation ✓
- [ ] Extension loads without errors
- [ ] Welcome message appears
- [ ] Output channel "HopeIDE" created

### 2. Commands ✓
- [ ] `HopeIDE: Build Project` - Test with STM32 project
- [ ] `HopeIDE: Flash Device` - Test with ST-Link connected
- [ ] `HopeIDE: Clean Build` - Test cleanup
- [ ] `HopeIDE: Detect STM32 Device` - Test auto-detection

### 3. Debug Configuration ✓
- [ ] Create `.vscode/launch.json` with hopeide type
- [ ] Set breakpoint in .c file
- [ ] Press F5 to start debugging
- [ ] Verify OpenOCD starts
- [ ] Verify GDB connects
- [ ] Verify breakpoint hits

### 4. Viewers ✓
- [ ] Register viewer appears in sidebar
- [ ] Memory viewer appears in sidebar
- [ ] Registers update when paused
- [ ] Memory can be browsed

### 5. Error Handling ✓
- [ ] Disconnect ST-Link, try flash → User-friendly error
- [ ] No Makefile → Clear error message
- [ ] GDB timeout → Clear error (5s timeout)

---

## 🔧 Test Project Setup

### Use blink-led Example
```bash
# Copy example
cp -r examples/blink-led ~/test-hopeide-project
cd ~/test-hopeide-project

# Open in VS Code
code .

# Test:
# 1. Ctrl+Shift+P → "HopeIDE: Build Project"
# 2. Ctrl+Shift+P → "HopeIDE: Flash Device"
# 3. F5 → Start Debugging
```

---

## 📝 Expected Results

### Build Command
```
🔨 Building ARM project...
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
📁 Project: /path/to/project
🔨 Running: make all

Compiling: main.c
Linking: firmware.elf
Creating HEX: firmware.hex
Creating BIN: firmware.bin

✅ Build completed successfully!
```

### Flash Command (Success)
```
⚡ Flashing device...
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
📁 Flash file: firmware.bin
🔄 Verify: Yes
🔁 Max retries: 3

⚡ Flash attempt 1/3...
🔧 Command: st-flash --reset write firmware.bin 0x08000000
st-flash 1.7.0
Mass erasing......
Flash page at addr: 0x08000000 erased
...
✅ Flash completed successfully!
```

### Flash Command (With Retry)
```
⚡ Flash attempt 1/3...
❌ Attempt 1 failed: Connection error
⏳ Waiting 2 seconds before retry...

⚡ Flash attempt 2/3...
✅ Flash completed successfully!
```

### Debug Launch
```
🚀 Starting HopeIDE debugger...
⚡ Starting OpenOCD...
✅ OpenOCD started
🔧 Starting GDB...
✅ GDB started
🔗 Connecting to target...
✅ Connected to target

[Breakpoint hit at main.c:58]
```

---

## 🐛 Known Issues (Node.js v18)

### vsce package fails
**Error:** `ReferenceError: File is not defined`

**Workaround:** Use manual package script
```bash
./package-manual.sh
```

**OR:** Use F5 (Development Host) instead of VSIX

---

## ✅ Success Criteria

Extension passes testing if:
- ✅ Loads without errors
- ✅ All 6 commands work
- ✅ Build succeeds (with timeout)
- ✅ Flash succeeds (with retry)
- ✅ Debug launches (OpenOCD + GDB)
- ✅ No undefined errors
- ✅ User-friendly error messages
