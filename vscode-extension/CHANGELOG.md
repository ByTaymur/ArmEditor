# Changelog

All notable changes to the "hopeide" extension will be documented in this file.

## [1.0.0] - 2025-11-23

### Added - Initial Release 🎉
- ✅ **Build System Integration**
  - Makefile-based compilation
  - Build timeout (2 minutes)
  - Clean build support
  
- ✅ **Flash Programming**
  - ST-Link support via st-flash
  - Retry logic (3 attempts) - Phase 0 fix!
  - Timeout handling (60 seconds) - Phase 0 fix!
  - Verify after flash (optional)
  - Reset after flash (optional)
  
- ✅ **GDB Debugging (DAP)**
  - Full Debug Adapter Protocol implementation
  - Breakpoint support
  - Step over/into/out
  - Continue/pause
  - Timeout on all commands (5s) - Phase 0 fix!
  
- ✅ **OpenOCD Integration**
  - Automatic startup with retry (3 attempts) - Phase 0 fix!
  - SWD/JTAG support
  - Multiple STM32 families
  
- ✅ **Device Auto-Detection**
  - ST-Link device detection
  - Chip ID parsing
  - Family identification (F0/F1/F4/F7/H7/L4)
  
- ✅ **Register Viewer**
  - Real-time CPU register display
  - Change tracking
  - Decimal and hex values
  
- ✅ **Memory Viewer**
  - Hex editor
  - ASCII display
  - Jump to address
  
### Fixed
- All Phase 0 critical issues:
  - Connection stability (retry logic)
  - Flash reliability (timeout + verify)
  - GDB command timeout
  - Error handling and recovery

### Technical
- TypeScript implementation
- Event-driven architecture
- Comprehensive error handling
- User-friendly error messages

## [Unreleased]

### Planned
- [ ] Peripheral Viewer (SVD-based)
- [ ] SWO Trace viewer
- [ ] Conditional breakpoints
- [ ] RTOS task viewer
- [ ] ESP32 support
- [ ] RP2040 support
