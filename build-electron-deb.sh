#!/bin/bash
###########################################
# Build COMPLETE .deb with Electron GUI
# EVERYTHING IN ONE FILE!
###########################################

set -e

echo "==========================================="
echo "🚀 Building COMPLETE ArmEditor.deb"
echo "   WITH ELECTRON GUI!"
echo "==========================================="
echo ""

# Clean
echo "🧹 Cleaning..."
rm -rf dist/
rm -f *.deb

# Install dependencies (including dev for electron-builder)
echo "📦 Installing dependencies..."
npm install

# Build with electron-builder
echo "🔨 Building Electron .deb package..."
npm run build:deb

# Find the generated .deb
DEB_FILE=$(find dist/ -name "*.deb" | head -1)

if [ -f "$DEB_FILE" ]; then
    # Copy to root with simple name
    cp "$DEB_FILE" ./ArmEditor.deb

    echo ""
    echo "==========================================="
    echo "✅ SUCCESS!"
    echo "==========================================="
    echo ""
    echo "📦 Package: ArmEditor.deb"
    echo "📊 Size: $(du -h ArmEditor.deb | cut -f1)"
    echo ""
    echo "Install with:"
    echo "  sudo dpkg -i ArmEditor.deb"
    echo ""
    echo "Run with:"
    echo "  armeditor"
    echo ""
    echo "🎉 EVERYTHING IN ONE FILE!"
    echo ""
else
    echo "❌ Failed to create .deb package"
    exit 1
fi
