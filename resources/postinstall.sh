#!/bin/bash
# Post-install script for ArmEditor

# Install udev rules for ST-Link and J-Link
if [ -f /opt/ArmEditor/resources/99-stlink.rules ]; then
    echo "Installing udev rules for ST-Link..."
    cp /opt/ArmEditor/resources/99-stlink.rules /etc/udev/rules.d/
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

exit 0
