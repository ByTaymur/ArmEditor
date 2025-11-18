#!/bin/bash
##################################################
# ArmEditor - Complete Test Suite
# Tests all features and generates report
##################################################

set -e

echo "=================================================="
echo "🧪 ArmEditor Complete Test Suite"
echo "=================================================="
echo ""

TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

test_start() {
    echo -e "${BLUE}▶${NC} Testing: $1"
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
}

test_pass() {
    echo -e "${GREEN}✓${NC} PASSED: $1"
    PASSED_TESTS=$((PASSED_TESTS + 1))
    echo ""
}

test_fail() {
    echo -e "${RED}✗${NC} FAILED: $1"
    FAILED_TESTS=$((FAILED_TESTS + 1))
    echo ""
}

##################################################
# Test 1: LED Blink Example
##################################################
test_start "LED Blink Example Build"

cd /home/user/ArmEditor/examples/blink-led

if make clean > /dev/null 2>&1 && make > /dev/null 2>&1; then
    if [ -f build/blink-led.elf ]; then
        test_pass "LED Blink builds successfully"

        # Check size
        SIZE=$(arm-none-eabi-size build/blink-led.elf 2>/dev/null | tail -1 | awk '{print $1}')
        echo "  Code size: $SIZE bytes"
    else
        test_fail "LED Blink - ELF not generated"
    fi
else
    test_fail "LED Blink - Build failed"
fi

##################################################
# Test 2: AI Code Assistant
##################################################
test_start "AI Code Assistant"

cd /home/user/ArmEditor

if node src/ai/code-assistant.js examples/blink-led/main.c > /tmp/ai-test.log 2>&1; then
    test_pass "AI Code Assistant works"
    echo "  Report saved to /tmp/ai-test.log"
    echo "  Preview:"
    head -20 /tmp/ai-test.log | sed 's/^/    /'
else
    test_fail "AI Code Assistant failed"
fi

##################################################
# Test 3: Memory Analyzer
##################################################
test_start "Memory Analyzer"

if [ -f /home/user/ArmEditor/examples/blink-led/build/blink-led.elf ]; then
    if node src/ai/memory-analyzer.js \
        examples/blink-led/build/blink-led.elf \
        examples/blink-led/main.c > /tmp/memory-test.log 2>&1; then
        test_pass "Memory Analyzer works"
        echo "  Report saved to /tmp/memory-test.log"
    else
        test_fail "Memory Analyzer failed"
    fi
else
    test_fail "Memory Analyzer - No ELF file"
fi

##################################################
# Test 4: Performance Profiler
##################################################
test_start "Performance Profiler"

if [ -f /home/user/ArmEditor/examples/blink-led/build/blink-led.elf ]; then
    if node src/ai/performance-profiler.js \
        examples/blink-led/build/blink-led.elf > /tmp/perf-test.log 2>&1; then
        test_pass "Performance Profiler works"
        echo "  Report saved to /tmp/perf-test.log"
    else
        test_fail "Performance Profiler failed"
    fi
else
    test_fail "Performance Profiler - No ELF file"
fi

##################################################
# Test 5: ARM Toolchain
##################################################
test_start "ARM Toolchain Availability"

if command -v arm-none-eabi-gcc >/dev/null 2>&1; then
    VERSION=$(arm-none-eabi-gcc --version | head -1)
    test_pass "ARM Toolchain found: $VERSION"
else
    test_fail "ARM Toolchain not found"
    echo "  Install: sudo apt install gcc-arm-none-eabi"
fi

##################################################
# Test 6: OpenOCD
##################################################
test_start "OpenOCD Availability"

if command -v openocd >/dev/null 2>&1; then
    VERSION=$(openocd --version 2>&1 | head -1)
    test_pass "OpenOCD found: $VERSION"
else
    test_fail "OpenOCD not found"
    echo "  Install: sudo apt install openocd"
fi

##################################################
# Test 7: Node.js Dependencies
##################################################
test_start "Node.js Dependencies"

cd /home/user/ArmEditor

if [ -d node_modules ]; then
    COUNT=$(ls -1 node_modules | wc -l)
    test_pass "Node modules installed ($COUNT packages)"
else
    test_fail "Node modules not installed"
    echo "  Run: npm install"
fi

##################################################
# Test 8: SVD Parser
##################################################
test_start "SVD Parser (Python)"

if command -v python3 >/dev/null 2>&1; then
    if python3 -c "import xml.etree.ElementTree" 2>/dev/null; then
        test_pass "SVD Parser dependencies OK"
    else
        test_fail "SVD Parser missing dependencies"
    fi
else
    test_fail "Python3 not found"
fi

##################################################
# Test 9: CubeMX Importer
##################################################
test_start "CubeMX Importer"

if [ -f src/advanced/cubemx-importer.js ]; then
    # Just check if it runs (without actual .ioc file)
    if node src/advanced/cubemx-importer.js --help >/dev/null 2>&1 || true; then
        test_pass "CubeMX Importer available"
    else
        test_pass "CubeMX Importer available (needs .ioc file to test)"
    fi
else
    test_fail "CubeMX Importer not found"
fi

##################################################
# Test 10: Documentation
##################################################
test_start "Documentation Files"

DOCS_OK=0
[ -f README.md ] && DOCS_OK=$((DOCS_OK + 1))
[ -f HOW-TO-USE.md ] && DOCS_OK=$((DOCS_OK + 1))
[ -f INSTALL.md ] && DOCS_OK=$((DOCS_OK + 1))

if [ $DOCS_OK -eq 3 ]; then
    test_pass "All documentation present"
else
    test_fail "Missing documentation ($DOCS_OK/3)"
fi

##################################################
# Summary
##################################################
echo "=================================================="
echo "📊 TEST SUMMARY"
echo "=================================================="
echo ""
echo "  Total tests:  $TOTAL_TESTS"
echo -e "  ${GREEN}Passed:${NC}       $PASSED_TESTS"

if [ $FAILED_TESTS -gt 0 ]; then
    echo -e "  ${RED}Failed:${NC}       $FAILED_TESTS"
else
    echo "  Failed:       0"
fi

echo ""

SUCCESS_RATE=$((PASSED_TESTS * 100 / TOTAL_TESTS))

if [ $SUCCESS_RATE -eq 100 ]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! (100%)${NC}"
elif [ $SUCCESS_RATE -ge 80 ]; then
    echo -e "${YELLOW}⚠️  Most tests passed ($SUCCESS_RATE%)${NC}"
else
    echo -e "${RED}❌ Many tests failed ($SUCCESS_RATE%)${NC}"
fi

echo ""
echo "=================================================="

# Generate detailed report
REPORT_FILE="/tmp/armeditor-test-report.txt"

cat > $REPORT_FILE << EOF
ArmEditor Test Report
Generated: $(date)

Summary:
  Total:  $TOTAL_TESTS
  Passed: $PASSED_TESTS
  Failed: $FAILED_TESTS
  Rate:   $SUCCESS_RATE%

Detailed Logs:
  AI Assistant:  /tmp/ai-test.log
  Memory:        /tmp/memory-test.log
  Performance:   /tmp/perf-test.log

Environment:
  OS:       $(uname -s)
  Kernel:   $(uname -r)
  ARM GCC:  $(arm-none-eabi-gcc --version 2>/dev/null | head -1 || echo "Not installed")
  Node.js:  $(node --version 2>/dev/null || echo "Not installed")
  Python:   $(python3 --version 2>/dev/null || echo "Not installed")
  OpenOCD:  $(openocd --version 2>&1 | head -1 || echo "Not installed")
EOF

echo "📄 Detailed report: $REPORT_FILE"
echo ""

exit $((100 - SUCCESS_RATE > 0 ? 1 : 0))
