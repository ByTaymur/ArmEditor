# HopeIDE – Project Context (AI Assistant Probe)

> **Purpose:** Quick reference for AI assistants starting new conversations  
> **Last Updated:** 2025-11-23  
> **Current Version:** v3.1.8-stable  
> **Status:** 🚨 Stability Crisis - Core fixes needed!

---

## 🎯 Project Overview

**HopeIDE** is an open-source embedded development IDE for ARM Cortex-M microcontrollers, starting with STM32. Goal: Become the free, open-source alternative to Keil μVision and IAR EWARM.

### Mission Statement
> **"Professional ARM debugging without the $5000 license fee"**

### Current Focus
- **STM32 family support** (F0, F1, F4, F7, H7, L4)
- **Professional debugging** (registers, memory, variables, peripherals)  
- **Modern UI** (Electron, dark theme)
- **100% open-source** (MIT license)

---

## 📊 Current Status (v3.1.8-stable)

### What Works ✅
```
✅ Build system (Makefile-based)
✅ Flash via ST-Link (st-flash)
✅ Basic GDB debugging (breakpoints, step)
✅ Register viewer (real-time updates)
✅ Memory browser (hex viewer)
✅ Project templates (STM32 HAL)
✅ Options Dialog (device, build, debug settings)
✅ Status bar (project, device, connection)
```

### What's Broken ❌
```
❌ ST-Link connection sometimes drops
❌ Flash occasionally fails (no retry logic)
❌ GDB startup can timeout
❌ UI is cluttered, many non-functional buttons
❌ Error messages are cryptic ("undefined")
```

### Critical Issues (Phase 0)
```
🚨 Priority 1: ST-Link connection stability
🚨 Priority 2: Flash reliability (10/10 success rate)
🚨 Priority 3: GDB startup robustness  
🚨 Priority 4: UI simplification
```

---

## 🗂️ Project Structure

```
ArmEditor/
├── src/
│   ├── main/
│   │   └── electron-main.js          # Main process, IPC handlers
│   ├── renderer/
│   │   └── ide-professional.html     # UI, frontend logic
│   ├── debugger/
│   │   ├── gdb-backend.js            # GDB MI interface
│   │   ├── openocd-interface.js      # OpenOCD wrapper
│   │   ├── register-viewer.js        # Register management
│   │   ├── memory-browser.js         # Memory operations
│   │   └── flash-manager.js          # Flash operations
│   ├── programmer/
│   │   ├── open-source-stlink.js     # st-flash wrapper
│   │   └── stm32-cube-programmer.js  # STM32CubeProg (future)
│   ├── project/
│   │   ├── project-manager.js        # Project CRUD
│   │   ├── template-manager.js       # Project templates
│   │   └── options-manager.js        # Build/debug options
│   ├── device/
│   │   ├── device-database.js        # STM32 device info
│   │   └── svd-parser.js             # SVD file parsing (peripheral)
│   └── stm32/
│       ├── stm32-tools.js            # Device info via OpenOCD
│       └── mcu-detector.js           # Auto-detect MCU
├── templates/
│   └── STM32F4_HAL_Basic/            # Project template
├── data/
│   └── devices/
│       └── stm32-database.json       # Device definitions
└── package.json                      # Electron app metadata
```

---

## 🛠️ Technology Stack

### Core
- **Framework:** Electron 28.x
- **Language:** JavaScript (Node.js 18.x)
- **UI:** HTML/CSS (no framework, vanilla JS)
- **Editor:** Monaco Editor (planned, not implemented)

### Build & Debug
- **Build System:** GNU Make
- **Toolchain:** ARM GCC (arm-none-eabi-gcc)
- **Debugger:** GDB (arm-none-eabi-gdb / gdb-multiarch)
- **Debug Server:** OpenOCD 0.12+ OR st-flash (stlink-tools)
- **ST-Link:** stlink-tools (open-source)

### Libraries
- **GDB MI:** Custom implementation (gdb-backend.js)
- **SVD Parsing:** Custom (svd-parser.js)
- **IPC:** Electron ipcMain/ipcRenderer

---

## 🚨 Known Issues & Workarounds

### Issue 1: ST-Link Connection Drops
```javascript
// Problem: OpenOCD doesn't retry on failure
// Location: src/debugger/openocd-interface.js

// WORKAROUND (to implement):
async startWithRetry(maxRetries = 3) {
  for (let i = 0; i < maxRetries; i++) {
    try {
      await this.start();
      return true;
    } catch (e) {
      if (i === maxRetries - 1) throw e;
      await sleep(2000);
    }
  }
}
```

### Issue 2: Flash Failures
```javascript
// Problem: No timeout, no verify
// Location: src/main/electron-main.js (buildProject function)

// WORKAROUND (to implement):
await flashManager.flash(file, {
  verify: true,
  timeout: 60000,
  onProgress: (pct) => updateUI(pct)
});
```

### Issue 3: GDB Hangs
```javascript
// Problem: No timeout on GDB commands
// Location: src/debugger/gdb-backend.js

// WORKAROUND (to implement):
const result = await Promise.race([
  gdb.sendCommand('info registers'),
  timeout(5000) // 5 second timeout
]);
```

---

## 📚 Key Documents (Artifacts)

### Essential Reading
1. **[master_roadmap.md](file:///home/tymr/.gemini/antigravity/brain/1685ecef-0b27-4f77-b8bf-8094b5bf704a/master_roadmap.md)** ⭐ MOST IMPORTANT
   - 6-phase roadmap
   - Phase 0: Core Fixes (1-2 weeks)
   - Known issues + solutions
   - 7-day action plan

2. **[task.md](file:///home/tymr/.gemini/antigravity/brain/1685ecef-0b27-4f77-b8bf-8094b5bf704a/task.md)**
   - Current tasks (Phase 0: URGENT!)
   - Progress tracking

3. **[commit_log.md](file:///home/tymr/Belgeler/GitHub/ArmEditor/commit_log.md)**
   - Detailed version history
   - Every change documented

### Strategic Docs
4. **[competitive_analysis.md](file:///home/tymr/.gemini/antigravity/brain/1685ecef-0b27-4f77-b8bf-8094b5bf704a/competitive_analysis.md)**
   - Market positioning
   - Competitors: PlatformIO, Eclipse, Keil, Segger

5. **[project_vision_roadmap.md](file:///home/tymr/.gemini/antigravity/brain/1685ecef-0b27-4f77-b8bf-8094b5bf704a/project_vision_roadmap.md)**
   - Long-term vision (12+ months)
   - Multi-platform expansion

---

## 🎯 Current Priorities (Phase 0)

### This Week (7 Days)
```
Day 1-2: ST-Link connection stability
  - Add retry logic to OpenOCD
  - Test: 10/10 successful start/stop

Day 3-4: Flash reliability
  - Error handling + verify
  - Test: 10/10 successful flash

Day 5-7: UI cleanup
  - Remove non-functional elements
  - Test all buttons

Goal: v3.2.0-stable (100% working flash+debug)
```

---

## 🧑‍💻 Coding Standards

### Commit Messages
```bash
# Feature
git commit -m "feat: <description>
- Added <component>
- Implemented <functionality>"

# Bug Fix
git commit -m "fix: <issue>
- Corrected <problem>
- Resolved <error>"
```

### Code Style
```javascript
// Use async/await (not callbacks)
async function flashDevice(file) {
  try {
    await openocd.start();
    await flashManager.flash(file);
  } catch (e) {
    console.error('[Flash]', e.message);
  }
}

// IPC naming: kebab-case
ipcMain.on('build-project', async (event, path) => { ... });

// UI listeners: camelCase
function buildAndFlash() { ... }
```

### Error Handling
```javascript
// Always catch, always log, always inform user
try {
  await doSomething();
} catch (e) {
  console.error('[Component]', e);
  mainWindow.webContents.send('output-append', `❌ Failed: ${e.message}\n`);
  dialog.showErrorBox('Error', e.message);
}
```

---

## 🔧 Quick Commands

### Development
```bash
# Start IDE
npm start

# Check syntax
node -c src/main/electron-main.js

# Test build (from template project)
cd templates/STM32F4_HAL_Basic
make
```

### Git Workflow
```bash
# Feature branch
git checkout -b feat/my-feature

# Bug fix branch
git checkout -b fix/issue-name

# Commit + push
git add .
git commit -m "feat: description"
git push origin feat/my-feature
```

### Testing
```bash
# Flash test (manual)
# 1. Open IDE
# 2. Click "Build & Flash" 10 times
# 3. Success rate should be 10/10

# Debug test (manual)
# 1. Click "Start Debug" 10 times
# 2. Should start 10/10
```

---

## 📞 User Communication

### Status Messages (User-Facing)
```javascript
// Good ✅
"Flash successful! Firmware uploaded to device."
"Building project... Please wait."

// Bad ❌
"Error: undefined"
"Process exited with code 1"
```

### Version Messages
```
v3.1.8: "Stability improvements!"
v3.2.0: "Flash now 100% reliable!"
v3.3.0: "UI simplified, all buttons work!"
```

---

## 🎯 Success Criteria

### Phase 0 Complete When:
```
✅ Flash 10 times → 10/10 success
✅ Debug start 10 times → 10/10 success
✅ Connection never drops
✅ UI clean, all buttons functional
✅ Error messages are descriptive
```

### Phase 1 Complete When:
```
✅ New user can flash in 10 minutes
✅ No "undefined" errors
✅ Demo video possible
```

---

## 🚀 Next Steps (Always Check)

1. Read **[master_roadmap.md](file:///home/tymr/.gemini/antigravity/brain/1685ecef-0b27-4f77-b8bf-8094b5bf704a/master_roadmap.md)** for current phase
2. Check **[task.md](file:///home/tymr/.gemini/antigravity/brain/1685ecef-0b27-4f77-b8bf-8094b5bf704a/task.md)** for today's tasks
3. Review **[commit_log.md](file:///home/tymr/Belgeler/GitHub/ArmEditor/commit_log.md)** for recent changes
4. Follow coding standards above
5. Test thoroughly before committing

---

**Remember:** 
> _"Önce çalışsın, sonra havalı olsun."_  
> _("First make it work, then make it cool.")_

**Version:** v3.1.8-stable  
**Phase:** 0 (Core Fixes – URGENT!)  
**Goal:** v3.2.0-stable (100% reliable flash+debug)
