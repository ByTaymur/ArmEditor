#!/bin/bash
# Post-install script for HopeIDE

# Fix chrome-sandbox permissions (required for Electron)
if [ -f /opt/HopeIDE/chrome-sandbox ]; then
    echo "Fixing chrome-sandbox permissions..."
    chown root:root /opt/HopeIDE/chrome-sandbox
    chmod 4755 /opt/HopeIDE/chrome-sandbox
    echo "✅ Chrome sandbox configured!"
fi

# Create symlink to make 'hopeide' command available
echo "Creating hopeide command..."
ln -sf /opt/HopeIDE/hopeide /usr/bin/hopeide
chmod +x /opt/HopeIDE/hopeide
echo "✅ Command 'hopeide' is now available!"

# Install udev rules for ST-Link and J-Link
if [ -f /opt/HopeIDE/resources/99-stlink.rules ]; then
    echo "Installing udev rules for ST-Link..."
    cp /opt/HopeIDE/resources/99-stlink.rules /etc/udev/rules.d/
    udevadm control --reload-rules
    udevadm trigger
    echo "✅ Udev rules installed!"
fi

# Add user to dialout group for serial port access
if groups $SUDO_USER | grep -q dialout; then
    echo "User already in dialout group"
else
    echo "Adding user to dialout group..."
    usermod -a -G dialout $SUDO_USER
    echo "✅ User added to dialout group (re-login required)"
fi

# Install usbutils if not present (needed for lsusb)
if ! command -v lsusb &> /dev/null; then
    echo "Installing usbutils (for ST-Link detection)..."
    apt-get update -qq && apt-get install -y usbutils 2>/dev/null || echo "⚠️  Could not install usbutils automatically"
fi

# Make ST-Link fix script executable
if [ -f /opt/HopeIDE/resources/stlink-fix.sh ]; then
    chmod +x /opt/HopeIDE/resources/stlink-fix.sh
    echo ""
    echo "======================================"
    echo "ST-Link Troubleshooting:"
    echo "If ST-Link doesn't connect, run:"
    echo "  sudo /opt/HopeIDE/resources/stlink-fix.sh"
    echo "======================================"
fi

exit 0
