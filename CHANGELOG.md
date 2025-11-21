# Changelog

All notable changes to HopeIDE will be documented in this file.

## [2.0.0] - 2024-11-21

### Added
- **SWV (Serial Wire Viewer)** trace debugging support
- **ST-Link device management** with auto-detection
- **Professional IDE UI** with multiple layouts (ide.html, ide-professional.html, ide-new.html)
- **Build instructions** and quick install script
- **Makefile templates** for STM32 projects
- **STM32 auto-detection** from device ID
- **Flash Manager** with comprehensive firmware programming
- **OpenOCD interface improvements** with better error handling
- **STM32 Tools** enhancements for device info reading
- **USB permission auto-fix** (99-stlink.rules)
- **Memory viewer** and device memory dump
- **Real-time register display**
- **SWV trace console** for printf debugging
- **Multi-MCU support** (F0, F1, F2, F3, F4, F7, G0, G4, H7, L0, L1, L4, L5, WB, WL)

### Fixed
- Electron sandbox issues (`--no-sandbox` flags)
- Error handling in file operations
- Deprecated `electron.remote` API replaced with IPC
- WebSocket moved to main process
- GDB interface timeout and port conflicts
- OpenOCD process cleanup
- Chart.js dynamic loading for realtime grapher
- Missing method `readVariableAsync` in GDB interface

### Changed
- Rebranded from ArmEditor to **HopeIDE (Umut IDE)**
- Version bumped from 1.0.0 to 2.0.0
- Enhanced debug panel with better controls
- Improved project structure parsing
- Better MCU type detection
- Enhanced build system with auto-target detection

### Technical Details
- **+5716 lines added**
- **-3237 lines removed**
- **29 critical issues fixed**
- All branches consolidated into stable version

## [1.0.0] - 2024-11-20

### Initial Release
- Basic ARM development IDE
- Monaco Editor integration
- GDB debugging support
- OpenOCD integration
- STM32CubeMX project import
- AI code assistant
- Memory analyzer
- Performance profiler
- Real-time variable graphing
