# HopeIDE – Detailed Commit History & Changelog

> **Purpose:** Complete development history for every change, with version numbers, user messages, and technical details.
> **Audience:** Developers, AI assistants, future contributors
> **Updated:** 2025-11-23

---

## 📌 Version Naming Convention
```
Major.Minor.Patch[-tag]
  3  . 1  . 8  [-stable]

Major: Breaking changes, architecture overhaul
Minor: New features, significant improvements
Patch: Bug fixes, small enhancements
Tag: stable, beta, alpha, rc (release candidate)
```

---

## 🚀 Current Version: v3.1.8-stable (2025-11-23)

### User-Facing Message
> **"Stability improvements! Flash and debug now more reliable. Fixed syntax errors and improved error handling."**

### What Changed
- ✅ Fixed syntax error in `buildProject` function (missing braces)
- ✅ Improved GDB backend robustness
- ✅ Clean IPC event handling for debug sessions
- ✅ Verified all core features working

### Technical Details
```javascript
// Fixed in: src/main/electron-main.js
// Lines: 682-688
// Issue: Duplicate error handling block, malformed if-else

// BEFORE (broken):
} catch (flashErr) {
    // ...
}
}
    } else {  // ← SYNTAX ERROR

// AFTER (fixed):
} catch (flashErr) {
    // ...
}
} else {
    // ...
}
```

### Commit
```bash
git commit -m "fix: Stability improvements for v3.1.8

- Fixed syntax error in buildProject (missing braces)
- Verified GDB backend robustness
- Ensured clean IPC event handling for debug sessions
- Bumped version to v3.1.8 (Stable Release Candidate)"
```

---

## v3.1.7 (2025-11-22)

### User-Facing Message
> **"Real-time register updates! Registers now refresh automatically when debugging pauses."**

### What Changed
- ✅ Added GDB event listeners in electron-main.js
- ✅ Auto-refresh registers on debug stop
- ✅ UI listeners for 'registers-update', 'debug-stopped', 'debug-running'

### Technical Details
```javascript
// Added in: src/main/electron-main.js
// Lines: 979-1009

gdbBackend.on('async', async (type, data) => {
    if (type === 'stopped') {
        // Auto-refresh registers
        const regs = await registerViewer.readCPURegisters();
        mainWindow.webContents.send('registers-update', regs);
    }
});

// Added in: src/renderer/ide-professional.html
// Lines: 1919-1938

ipcRenderer.on('registers-update', (event, registers) => {
    updateRegisters(registers);
});
```

### Commits
```bash
# Commit 1
git commit -m "feat: Enable real-time debug updates

- Added GDB event listeners in electron-main.js
- Listens for 'stopped' event to trigger auto-refresh
- Automatically reads registers when execution stops
- Sends updates to UI (debug-stopped, registers-update)
- Initialized RegisterViewer on debug start"

# Commit 2
git commit -m "feat: Connect real-time debug UI

- Added IPC listeners in ide-professional.html for:
  - 'registers-update': Updates register table values
  - 'debug-stopped': Updates status to Paused
  - 'debug-running': Updates status to Running
- This completes the loop for real-time register monitoring"

# Commit 3 (Version bump)
git commit -m "v3.1.7" && git tag v3.1.7 -m "Real-time register updates"
```

### Files Modified
- `src/main/electron-main.js` (+31 lines)
- `src/renderer/ide-professional.html` (+22 lines)
- `package.json` (version: 3.1.6 → 3.1.7)

---

## v3.1.6 (2025-11-22)

### User-Facing Message
> **"Build & Flash button now works correctly! Auto-detects the right programmer (ST-Link) and flashes your firmware."**

### What Changed
- ✅ Fixed auto-flash logic to support Open Source ST-Link
- ✅ Added support for direct `flashBinary` method call
- ✅ Real-time flash progress forwarding
- ✅ Fixed "No rule to make target flash" error

### Technical Details
```javascript
// Fixed in: src/main/electron-main.js
// Lines: 628-682

// BEFORE (broken):
if (autoFlash && connectedStLink && connectedStLink.openocd) {
    // Only worked for OpenOCD-based programmers
}

// AFTER (fixed):
if (autoFlash && connectedStLink) {
    if (connectedStLink.flashBinary) {
        // Open-Source ST-Link (st-flash)
        await connectedStLink.flashBinary(fullPath);
    } else if (connectedStLink.openocd) {
        // OpenOCD-based interface
        const flashManager = new FlashManager(connectedStLink.openocd);
        await flashManager.flash(fullPath, {...});
    }
}
```

### Commits
```bash
git commit -m "fix: Auto-flash logic for Open Source ST-Link

- Updated buildProject to correctly handle OpenSourceSTLink object which doesn't have 'openocd' property
- Added support for direct 'flashBinary' method call
- Added output forwarding for real-time flash progress
- Fixes 'No rule to make target flash' error"
```

### Files Modified
- `src/main/electron-main.js` (+28 lines, -10 lines)
- `package.json` (version: 3.1.5 → 3.1.6)

---

## v3.1.5 (2025-11-22)

### User-Facing Message
> **"New 'Build & Flash' button added! One click to build your project and flash it to the device."**

### What Changed
- ✅ Added "Build & Flash" button to top menu
- ✅ Implemented `buildAndFlash()` function
- ✅ Auto-connect to device if not already connected
- ✅ Progress feedback in console

### Technical Details
```html
<!-- Added in: src/renderer/ide-professional.html -->
<!-- Line: 958 -->
<button onclick="buildAndFlash()">⚡ Build & Flash</button>

<script>
function buildAndFlash() {
    if (!currentProjectPath) {
        appendConsole('⚠️ No project opened', 'warning');
        return;
    }
    
    if (!isConnected) {
        connectToTarget(); // Auto-connect
    }
    
    ipcRenderer.send('build-project', currentProjectPath, true); // autoFlash = true
}
</script>
```

### Commits
```bash
git commit -m "feat: Add Build & Flash button

- Added 'Build & Flash' button to top menu
- Implemented buildAndFlash() function with auto-connect
- Sends build-project IPC with autoFlash flag
- User feedback via console messages"
```

### Files Modified
- `src/renderer/ide-professional.html` (+15 lines)
- `package.json` (version: 3.1.4 → 3.1.5)

---

## v3.1.4 (2025-11-22)

### User-Facing Message
> **"GDB debugger now auto-detects! Works with both arm-none-eabi-gdb and gdb-multiarch."**

### What Changed
- ✅ Added `detectGDB()` function for auto-detection
- ✅ Prefers `gdb-multiarch` if available (Ubuntu/Debian)
- ✅ Falls back to `arm-none-eabi-gdb`
- ✅ Fixes "spawn arm-none-eabi-gdb ENOENT" error

### Technical Details
```javascript
// Added in: src/debugger/gdb-backend.js
// Lines: 6-30

async detectGDB() {
    const candidates = ['gdb-multiarch', 'arm-none-eabi-gdb'];
    
    for (const gdb of candidates) {
        try {
            await execPromise(`which ${gdb}`);
            console.log(`[GDB] Using: ${gdb}`);
            return gdb;
        } catch (e) {
            continue;
        }
    }
    throw new Error('No ARM GDB found!');
}

async start(elfFile, gdbPath) {
    if (!gdbPath) {
        gdbPath = await this.detectGDB();
    }
    // ...
}
```

### Commits
```bash
git commit -m "feat: GDB auto-detection for cross-platform support

- Added detectGDB() function to auto-detect available GDB
- Prefers gdb-multiarch (Ubuntu/Debian standard)
- Falls back to arm-none-eabi-gdb
- Resolves 'ENOENT' error on systems without arm-none-eabi-gdb
- Logs detected GDB path for debugging"
```

### Files Modified
- `src/debugger/gdb-backend.js` (+25 lines)
- `package.json` (version: 3.1.3 → 3.1.4)

---

## v3.1.3 (2025-11-22)

### User-Facing Message
> **"UI layout fixed! Status bar no longer overlaps the editor. Project path now displays correctly."**

### What Changed
- ✅ Fixed `.main-container` CSS to reserve space for status bar
- ✅ Fixed `project-opened` IPC listener to handle object payloads
- ✅ Status bar now correctly positioned at bottom

### Technical Details
```css
/* Fixed in: src/renderer/ide-professional.html */
/* Lines: 89-97 */

.main-container {
    position: absolute;
    top: 60px;
    left: 0;
    right: 0;
    bottom: 24px;  /* ← ADDED: Reserve space for status bar */
    display: flex;
}
```

```javascript
// Fixed in: src/renderer/ide-professional.html
// Lines: 1896-1900

ipcRenderer.on('project-opened', (event, projectInfo) => {
    // BEFORE (broken):
    // currentProjectPath = projectInfo; // Could be object!
    
    // AFTER (fixed):
    const path = (typeof projectInfo === 'object' && projectInfo.path) 
        ? projectInfo.path 
        : projectInfo;
    currentProjectPath = path;
});
```

### Commits
```bash
# Commit 1
git commit -m "fix: Status bar layout overlap

- Adjusted .main-container CSS to include bottom: 24px
- Properly accounts for status bar height
- Prevents editor and panels from being obscured"

# Commit 2
git commit -m "fix: Project path handling in project-opened listener

- Corrected handling of projectInfo object vs string
- Extracts path property correctly
- Resolves [object Object] path error"
```

### Files Modified
- `src/renderer/ide-professional.html` (+2 lines CSS, +5 lines JS)
- `package.json` (version: 3.1.2 → 3.1.3)

---

## v3.1.2 (2025-11-22)

### User-Facing Message
> **"Flash progress now visible! You can see what's happening when uploading firmware to your device."**

### What Changed
- ✅ Enhanced `flash-binary` IPC handler with progress updates
- ✅ Added file existence check before flashing
- ✅ Forward st-flash output to UI in real-time
- ✅ Better error messages

### Technical Details
```javascript
// Enhanced in: src/main/electron-main.js
// Lines: 1023-1063

ipcMain.on('flash-binary', async (event, { filePath, address, tool }) => {
    // Validation
    if (!filePath) {
        mainWindow.webContents.send('output-append', '❌ No file specified\n');
        return;
    }
    
    // File existence check
    if (!fs.existsSync(filePath)) {
        mainWindow.webContents.send('output-append', `❌ File not found: ${filePath}\n`);
        return;
    }
    
    // Progress updates
    mainWindow.webContents.send('flash-progress', 10);
    mainWindow.webContents.send('output-append', `📁 File: ${filePath}\n`);
    
    // Forward st-flash output
    if (connectedStLink.on) {
        connectedStLink.on('output', (data) => {
            mainWindow.webContents.send('output-append', data);
        });
    }
    
    // Flash
    await connectedStLink.flashBinary(filePath, address);
    mainWindow.webContents.send('flash-progress', 100);
});
```

### Commits
```bash
git commit -m "feat: Enhanced flash-binary IPC handler

- Added parameter validation (filePath, address, tool)
- File existence check with clear error message
- Progress updates at each step (10% → 30% → 90% → 100%)
- Forward st-flash output to UI for real-time feedback
- Improved logging for debugging"
```

### Files Modified
- `src/main/electron-main.js` (+41 lines)
- `package.json` (version: 3.1.1 → 3.1.2)

---

## Earlier Versions (v3.0.0 - v3.1.1)

### v3.1.1 (2025-11-21)
- Status bar implementation
- Build feedback messages
- Disconnect button

### v3.1.0 (2025-11-21)
- Initial status bar
- Flash progress display
- Build feedback system

### v3.0.2 (2025-11-20)
- Programmer selection in Options Dialog
- Advanced ST-Link settings

### v3.0.0 (2025-11-15)
- Major release: Professional IDE features
- Device database (7 STM32 families)
- Options Dialog (6 tabs)
- Register/Memory/Peripheral viewers
- Dark theme UI

---

## 📋 Commit Message Templates

### Feature Addition
```bash
git commit -m "feat: <short description>

- Added <component/function>
- Implemented <functionality>
- Integrated with <system>
- User benefit: <what user gains>

Closes #<issue-number>"
```

### Bug Fix
```bash
git commit -m "fix: <issue description>

- Corrected <problem>
- Resolved <error>
- Improved <aspect>

Fixes #<issue-number>"
```

### Refactoring
```bash
git commit -m "refactor: <what was refactored>

- Reorganized <code/structure>
- Simplified <logic>
- Extracted <function/component>
- No functional changes"
```

### Documentation
```bash
git commit -m "docs: <documentation update>

- Updated <doc-file>
- Added <section>
- Clarified <topic>"
```

---

## 🔍 How to Use This Log

### For Developers
1. Find your version number
2. See what changed technically
3. Review commit messages
4. Understand file modifications

### For AI Assistants
1. Read this file at conversation start
2. Understand project history
3. See coding patterns
4. Continue development consistently

### For Users
1. Check "User-Facing Message" for each version
2. Understand what improved
3. Report bugs with version number

---

**Last Updated:** 2025-11-23 14:00 UTC  
**Current Version:** v3.1.8-stable  
**Next Version:** v3.2.0-stable (Phase 0: Core Fixes)

