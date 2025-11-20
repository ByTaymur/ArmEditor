#!/bin/bash
# ST-Link Diagnostic and Fix Script

echo "==================================="
echo "ST-Link Diagnostic Tool"
echo "==================================="
echo ""

# Check if running as root
if [ "$EUID" -ne 0 ]; then
    echo "⚠️  This script needs sudo privileges"
    echo "Run: sudo /opt/ArmEditor/resources/stlink-fix.sh"
    exit 1
fi

# 1. Kill any running OpenOCD instances
echo "1. Killing any running OpenOCD instances..."
killall -9 openocd 2>/dev/null
killall -9 st-util 2>/dev/null
sleep 1
echo "✅ Done"
echo ""

# 2. Check for ST-Link devices
echo "2. Checking for ST-Link USB devices..."
if command -v lsusb &> /dev/null; then
    STLINK_FOUND=$(lsusb | grep "0483:" || true)
    if [ -n "$STLINK_FOUND" ]; then
        echo "✅ ST-Link detected:"
        echo "$STLINK_FOUND"
    else
        echo "❌ No ST-Link device found!"
        echo "   - Check USB cable connection"
        echo "   - Try different USB port"
        echo "   - Check if LED on ST-Link is on"
        exit 1
    fi
else
    echo "⚠️  lsusb not found. Installing usbutils..."
    apt-get update -qq && apt-get install -y usbutils
fi
echo ""

# 3. Fix udev rules
echo "3. Fixing udev rules..."
if [ -f /opt/ArmEditor/resources/99-stlink.rules ]; then
    cp /opt/ArmEditor/resources/99-stlink.rules /etc/udev/rules.d/
    chmod 644 /etc/udev/rules.d/99-stlink.rules
    udevadm control --reload-rules
    udevadm trigger
    echo "✅ Udev rules installed and reloaded"
else
    echo "❌ Udev rules file not found!"
fi
echo ""

# 4. Fix USB permissions directly
echo "4. Fixing USB device permissions..."
for device in /dev/bus/usb/*/*; do
    VENDOR=$(cat "$device" 2>/dev/null | grep -a "0483" || true)
    if [ -n "$VENDOR" ]; then
        chmod 666 "$device" 2>/dev/null || true
        echo "✅ Fixed permissions for $device"
    fi
done
echo ""

# 5. Unplug/replug prompt
echo "5. ST-Link Reset"
echo "   Please unplug and replug your ST-Link USB cable now"
echo "   Waiting for device..."
echo ""

# Wait for device
TIMEOUT=30
COUNT=0
while [ $COUNT -lt $TIMEOUT ]; do
    if lsusb | grep -q "0483:"; then
        echo "✅ ST-Link reconnected!"
        break
    fi
    sleep 1
    COUNT=$((COUNT + 1))
    echo -n "."
done
echo ""

if [ $COUNT -eq $TIMEOUT ]; then
    echo "❌ Timeout waiting for ST-Link"
    exit 1
fi

# 6. Test OpenOCD connection
echo "6. Testing OpenOCD connection..."
if command -v openocd &> /dev/null; then
    timeout 5 openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init; targets; exit" 2>&1 | grep -q "target halted" && echo "✅ OpenOCD connection successful!" || echo "⚠️  OpenOCD test inconclusive (may still work)"
else
    echo "⚠️  OpenOCD not found. Install it with: sudo apt install openocd"
fi
echo ""

echo "==================================="
echo "Diagnostic complete!"
echo ""
echo "If ST-Link still doesn't work:"
echo "  1. Try a different USB cable"
echo "  2. Update ST-Link firmware using STM32CubeProgrammer"
echo "  3. Check for kernel driver conflicts"
echo "==================================="
