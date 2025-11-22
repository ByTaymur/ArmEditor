# Commit Log – HopeIDE Development Branch

## v3.1.2 (2025-11-22)
- **Fix flash‑binary IPC handler**: Added parameter validation, file‑existence check, progress updates, and forwarding of `st-flash` output to UI.
- **Improved logging**: Added detailed console logs for debugging flash flow.
- **Version bump**: Updated `package.json` version to `3.1.2`.

## v3.1.3 (2025-11-22)
- **Status bar layout fix**: Adjusted `.main‑container` CSS to reserve space for the fixed status bar (`bottom: 24px`).
- **Project‑opened IPC**: Fixed handling of `projectInfo` object vs string, ensuring `currentProjectPath` is set correctly.
- **Version bump**: Updated `package.json` to `3.1.3`.

## v3.1.4 (2025-11-22)
- **GDB backend auto‑detection**: Added `detectGDB()` to prefer `gdb‑multiarch` when available, fallback to `arm‑none‑eabi‑gdb`.
- **Version bump**: Updated `package.json` to `3.1.4`.

## v3.1.5 (2025-11-22)
- **Build & Flash UI**: Added **Build & Flash** button to the top menu.
- **`buildAndFlash()` implementation**: Calls `build-project` IPC with auto‑flash flag, validates project path, and displays progress.
- **Version bump**: Updated `package.json` to `3.1.5`.

## v3.1.6 (2025-11-22)
- **Auto‑flash logic overhaul** in `electron‑main.js`:
  - Detects whether the connected ST‑Link provides a direct `flashBinary` method (Open‑Source ST‑Link) or an OpenOCD interface.
  - Uses appropriate flashing path (`FlashManager` via OpenOCD or direct `flashBinary`).
  - For `flashBinary` streams output events to the UI.
  - Added robust error handling and user feedback.
- **Version bump**: Updated `package.json` to `3.1.6`.

## Miscellaneous fixes
- Fixed syntax error (`missing ) after argument list`) introduced during the auto‑flash refactor.
- Updated status‑bar CSS to ensure UI does not overlap with main content.
- Adjusted `project-opened` IPC listener to correctly parse object vs string payloads.
- Added console logs for connection, flashing, and build steps to aid troubleshooting.

*All changes have been committed locally and are ready for push.*
