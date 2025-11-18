#!/bin/bash
# Pre-removal script for ArmEditor

set -e

echo "Removing ArmEditor..."

# Remove symbolic link
rm -f /usr/local/bin/armeditor

# Remove desktop entry
rm -f /usr/share/applications/armeditor.desktop

# Update desktop database
if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database /usr/share/applications
fi

# Uninstall VS Code extension
if command -v code >/dev/null 2>&1; then
    code --uninstall-extension armeditor.armeditor-vscode || true
fi

exit 0
