#!/bin/bash
# Test script for HopeIDE extension
# Tests build, flash, and debug functionality

set -e

echo "🧪 HopeIDE Extension Test Suite"
echo "================================"

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Test counters
PASS=0
FAIL=0

function test_command() {
    local name=$1
    local command=$2
    
    echo -n "Testing: $name... "
    
    if eval "$command" > /dev/null 2>&1; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((PASS++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        ((FAIL++))
    fi
}

# 1. Check dependencies
echo ""
echo "1️⃣ Checking Dependencies..."
test_command "ARM GCC" "which arm-none-eabi-gcc || which gcc-arm-none-eabi"
test_command "GDB" "which gdb-multiarch || which arm-none-eabi-gdb"
test_command "ST-Flash" "which st-flash"
test_command "OpenOCD" "which openocd"
test_command "Make" "which make"

# 2. Check TypeScript compilation
echo ""
echo "2️⃣ Checking TypeScript Compilation..."
cd "$(dirname "$0")"
test_command "TypeScript Compile" "npm run compile"

# 3. Check extension files
echo ""
echo "3️⃣ Checking Extension Files..."
test_command "package.json exists" "test -f package.json"
test_command "extension.ts exists" "test -f src/extension.ts"
test_command "debugAdapter.ts exists" "test -f src/debugAdapter.ts"
test_command "out/extension.js exists" "test -f out/extension.js"

# 4. Check services
echo ""
echo "4️⃣ Checking Services..."
test_command "BuildService" "test -f src/services/buildService.ts"
test_command "FlashService" "test -f src/services/flashService.ts"
test_command "GDBBackend" "test -f src/services/gdbBackend.ts"
test_command "OpenOCDService" "test -f src/services/openocdService.ts"
test_command "DeviceDetector" "test -f src/services/deviceDetector.ts"

# 5. Check providers
echo ""
echo "5️⃣ Checking Providers..."
test_command "RegisterViewer" "test -f src/providers/registerViewerProvider.ts"
test_command "MemoryViewer" "test -f src/providers/memoryViewerProvider.ts"

# Summary
echo ""
echo "================================"
echo "Test Results:"
echo -e "${GREEN}PASS: $PASS${NC}"
echo -e "${RED}FAIL: $FAIL${NC}"
echo ""

if [ $FAIL -eq 0 ]; then
    echo -e "${GREEN}✅ All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}❌ Some tests failed!${NC}"
    exit 1
fi
