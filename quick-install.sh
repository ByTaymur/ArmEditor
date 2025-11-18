#!/bin/bash
# ArmEditor Quick Install Script
# Runs in 35 seconds!

set -e

echo "================================================"
echo "🚀 ArmEditor Quick Install"
echo "================================================"
echo ""

# Check if in git repo
if [ ! -d ".git" ]; then
    echo "📥 Cloning ArmEditor repository..."
    git clone -b claude/setup-arm-compiler-015bn4WDFqfRHccswmMaA8Dq \
        https://github.com/ByTaymur/ArmEditor.git
    cd ArmEditor
else
    echo "✅ Already in ArmEditor directory"
fi

# Check dependencies
if ! command -v node &> /dev/null; then
    echo "❌ Node.js not found!"
    echo "Install with: sudo apt install nodejs npm"
    exit 1
fi

echo ""
echo "🔨 Building ArmEditor.deb..."
echo "This will take ~35 seconds..."
echo ""

# Make build script executable
chmod +x build-electron-deb.sh

# Run build
./build-electron-deb.sh

echo ""
echo "================================================"
echo "✅ SUCCESS! ArmEditor.deb READY!"
echo "================================================"
echo ""
echo "📦 File: $(pwd)/ArmEditor.deb"
echo "📊 Size: $(du -h ArmEditor.deb | cut -f1)"
echo ""
echo "📥 INSTALL:"
echo "   sudo dpkg -i ArmEditor.deb"
echo ""
echo "🚀 RUN:"
echo "   armeditor"
echo ""
echo "================================================"
