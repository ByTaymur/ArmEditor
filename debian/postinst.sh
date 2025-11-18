#!/bin/bash
# Post-installation script for ArmEditor

set -e

echo "Configuring ArmEditor..."

# Create symbolic link
ln -sf /opt/ArmEditor/armeditor /usr/local/bin/armeditor

# Install desktop entry
cat > /usr/share/applications/armeditor.desktop <<EOF
[Desktop Entry]
Name=ArmEditor
Comment=ARM Development IDE
Exec=/usr/local/bin/armeditor
Icon=/opt/ArmEditor/resources/icon.png
Terminal=false
Type=Application
Categories=Development;IDE;
EOF

# Update desktop database
if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database /usr/share/applications
fi

# Register as ARM compiler/debugger
mkdir -p /etc/armeditor
cat > /etc/armeditor/config.json <<EOF
{
  "version": "1.0.0",
  "toolchain": {
    "prefix": "arm-none-eabi-",
    "path": "/usr/bin"
  },
  "debugger": {
    "gdb": "arm-none-eabi-gdb",
    "openocd": "openocd"
  },
  "vscode": {
    "integration": true,
    "port": 9876
  }
}
EOF

# Check for ARM toolchain
if ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
    echo "=================================================="
    echo "WARNING: ARM toolchain not found!"
    echo ""
    echo "Please install with:"
    echo "  sudo apt install gcc-arm-none-eabi gdb-multiarch openocd"
    echo "=================================================="
fi

# Install VS Code extension if VS Code is installed
if command -v code >/dev/null 2>&1; then
    echo "Installing VS Code extension..."
    if [ -d "/opt/ArmEditor/vscode-extension" ]; then
        code --install-extension /opt/ArmEditor/vscode-extension || true
    fi
fi

echo "ArmEditor installation complete!"
echo ""
echo "Launch with: armeditor"
echo "Or from Applications menu"

exit 0
