#!/bin/bash
# Build .deb package for ArmEditor

set -e

echo "=================================================="
echo "Building ArmEditor .deb package"
echo "=================================================="

# Install dependencies
echo "Installing build dependencies..."
npm install

# Build Electron app
echo "Building Electron application..."
npm run build:deb

# The .deb will be in dist/ directory
echo ""
echo "=================================================="
echo "Build complete!"
echo "=================================================="
echo ""
echo "Package location: dist/arm-editor_1.0.0_amd64.deb"
echo ""
echo "Install with:"
echo "  sudo dpkg -i dist/arm-editor_1.0.0_amd64.deb"
echo "  sudo apt-get install -f  # Fix dependencies"
echo ""
echo "Or:"
echo "  sudo apt install ./dist/arm-editor_1.0.0_amd64.deb"
echo ""
