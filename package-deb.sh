#!/bin/bash
###########################################
# ArmEditor .deb Package Builder
# Creates ready-to-install Debian package
###########################################

set -e

echo "==========================================="
echo "🚀 Building ArmEditor .deb Package"
echo "==========================================="
echo ""

# Configuration
PKG_NAME="armeditor"
PKG_VERSION="1.0.0"
PKG_ARCH="amd64"
PKG_MAINTAINER="ArmEditor Team <armeditor@github.com>"
PKG_DESCRIPTION="Professional ARM Development IDE with AI features"

BUILD_DIR="deb-package"
DEB_DIR="$BUILD_DIR/DEBIAN"
OPT_DIR="$BUILD_DIR/opt/ArmEditor"
BIN_DIR="$BUILD_DIR/usr/bin"
APPS_DIR="$BUILD_DIR/usr/share/applications"
ICONS_DIR="$BUILD_DIR/usr/share/icons/hicolor/256x256/apps"

# Clean previous build
echo "🧹 Cleaning previous build..."
rm -rf "$BUILD_DIR"
rm -f *.deb

# Create directory structure
echo "📁 Creating directory structure..."
mkdir -p "$DEB_DIR"
mkdir -p "$OPT_DIR"
mkdir -p "$BIN_DIR"
mkdir -p "$APPS_DIR"
mkdir -p "$ICONS_DIR"

# Copy application files
echo "📦 Copying application files..."

# Main app
cp -r src "$OPT_DIR/"
cp -r examples "$OPT_DIR/"
cp -r resources "$OPT_DIR/" 2>/dev/null || mkdir -p "$OPT_DIR/resources"

# Documentation
cp README.md "$OPT_DIR/"
cp HOW-TO-USE.md "$OPT_DIR/"
cp INSTALL.md "$OPT_DIR/"
cp DEMO.md "$OPT_DIR/"
cp LICENSE "$OPT_DIR/"

# package.json and dependencies info
cp package.json "$OPT_DIR/"

# Create launcher script
echo "📝 Creating launcher script..."
cat > "$BIN_DIR/armeditor" << 'EOFSCRIPT'
#!/bin/bash
# ArmEditor launcher

ARMEDITOR_DIR="/opt/ArmEditor"

# Check if Node.js is installed
if ! command -v node >/dev/null 2>&1; then
    echo "❌ Error: Node.js is not installed"
    echo "Install with: sudo apt install nodejs npm"
    exit 1
fi

# Check if dependencies are installed
if [ ! -d "$ARMEDITOR_DIR/node_modules" ]; then
    echo "⚙️  Installing dependencies (first run)..."
    cd "$ARMEDITOR_DIR"
    npm install --production
fi

# Launch ArmEditor
cd "$ARMEDITOR_DIR"

# Check for arguments
if [ "$1" == "--ai" ]; then
    # AI Code Assistant
    shift
    node src/ai/code-assistant.js "$@"
elif [ "$1" == "--analyze" ]; then
    # Full analysis
    shift
    node src/ai/code-assistant.js "$1"
    node src/ai/memory-analyzer.js "$1"
    node src/ai/performance-profiler.js "$1"
elif [ "$1" == "--cubemx" ]; then
    # CubeMX import
    shift
    node src/advanced/cubemx-importer.js "$@"
elif [ "$1" == "--test" ]; then
    # Run tests
    bash test-all.sh
elif [ "$1" == "--gui" ]; then
    # GUI mode (Electron)
    npm start
else
    # Show help
    echo "ArmEditor - Professional ARM Development IDE"
    echo ""
    echo "Usage:"
    echo "  armeditor --gui              Launch GUI (Electron app)"
    echo "  armeditor --ai <file.c>      AI code analysis"
    echo "  armeditor --analyze <elf>    Full analysis (AI + Memory + Perf)"
    echo "  armeditor --cubemx <dir>     Import STM32CubeMX project"
    echo "  armeditor --test             Run test suite"
    echo ""
    echo "Examples:"
    echo "  armeditor --ai main.c"
    echo "  armeditor --analyze build/app.elf"
    echo "  armeditor --cubemx ~/MyProject"
    echo ""
    echo "Documentation:"
    echo "  /opt/ArmEditor/README.md"
    echo "  /opt/ArmEditor/HOW-TO-USE.md"
    echo "  /opt/ArmEditor/DEMO.md"
fi
EOFSCRIPT

chmod +x "$BIN_DIR/armeditor"

# Create desktop entry
echo "🖼️  Creating desktop entry..."
cat > "$APPS_DIR/armeditor.desktop" << EOFDESKTOP
[Desktop Entry]
Version=1.0
Type=Application
Name=ArmEditor
Comment=Professional ARM Development IDE with AI
Exec=/usr/bin/armeditor --gui
Icon=armeditor
Terminal=false
Categories=Development;IDE;
Keywords=ARM;STM32;Embedded;IDE;Cortex-M;
EOFDESKTOP

# Create icon (simple text-based for now)
echo "🎨 Creating icon..."
cat > "$ICONS_DIR/armeditor.png" << 'EOFICON'
# Placeholder - In real package, add PNG icon here
EOFICON

# Create control file
echo "📄 Creating DEBIAN/control..."
cat > "$DEB_DIR/control" << EOFCONTROL
Package: $PKG_NAME
Version: $PKG_VERSION
Section: devel
Priority: optional
Architecture: $PKG_ARCH
Depends: nodejs (>= 14.0), npm
Recommends: gcc-arm-none-eabi, gdb-multiarch, openocd, stlink-tools
Maintainer: $PKG_MAINTAINER
Description: $PKG_DESCRIPTION
 ArmEditor is a professional ARM development IDE with AI-powered features.
 .
 Features:
  - AI Code Assistant (bug detection, performance tips)
  - Memory Analyzer (leak detection)
  - Performance Profiler (cycle estimation)
  - STM32CubeMX project import
  - SVD peripheral viewer
  - Real-time variable graphing
  - VS Code integration
  - Better than Keil/IAR, completely free!
 .
 This package includes all necessary tools for ARM Cortex-M development.
EOFCONTROL

# Create postinst script
echo "📝 Creating postinst script..."
cat > "$DEB_DIR/postinst" << 'EOFPOSTINST'
#!/bin/bash
set -e

echo "⚙️  Configuring ArmEditor..."

# Create config directory
mkdir -p /etc/armeditor

# Create default config
cat > /etc/armeditor/config.json << EOFCONFIG
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
  "features": {
    "ai_assistant": true,
    "memory_analyzer": true,
    "performance_profiler": true,
    "svd_viewer": true,
    "cubemx_import": true
  }
}
EOFCONFIG

# Install Node.js dependencies
echo "📦 Installing Node.js dependencies..."
cd /opt/ArmEditor
npm install --production --silent || true

# Update desktop database
if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database /usr/share/applications || true
fi

# Print success message
echo ""
echo "========================================="
echo "✅ ArmEditor installed successfully!"
echo "========================================="
echo ""
echo "Launch with:"
echo "  armeditor --gui       # GUI mode"
echo "  armeditor --ai file.c # AI analysis"
echo ""
echo "Documentation:"
echo "  /opt/ArmEditor/README.md"
echo "  /opt/ArmEditor/HOW-TO-USE.md"
echo "  /opt/ArmEditor/DEMO.md"
echo ""

# Check ARM toolchain
if ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
    echo "⚠️  ARM toolchain not found!"
    echo "Install with:"
    echo "  sudo apt install gcc-arm-none-eabi gdb-multiarch openocd"
    echo ""
fi

exit 0
EOFPOSTINST

chmod +x "$DEB_DIR/postinst"

# Create prerm script
echo "📝 Creating prerm script..."
cat > "$DEB_DIR/prerm" << 'EOFPRERM'
#!/bin/bash
set -e

echo "🗑️  Removing ArmEditor..."

exit 0
EOFPRERM

chmod +x "$DEB_DIR/prerm"

# Build .deb package
echo ""
echo "🔨 Building .deb package..."
DEB_FILE="${PKG_NAME}_${PKG_VERSION}_${PKG_ARCH}.deb"

# Fix permissions
find "$BUILD_DIR" -type d -exec chmod 755 {} \;
find "$BUILD_DIR" -type f -exec chmod 644 {} \;
chmod +x "$DEB_DIR/postinst"
chmod +x "$DEB_DIR/prerm"
chmod +x "$BIN_DIR/armeditor"

# Build package
dpkg-deb --build "$BUILD_DIR" "$DEB_FILE"

# Package info
echo ""
echo "==========================================="
echo "✅ Package built successfully!"
echo "==========================================="
echo ""
echo "📦 Package: $DEB_FILE"
echo "📊 Size: $(du -h $DEB_FILE | cut -f1)"
echo ""
echo "Install with:"
echo "  sudo dpkg -i $DEB_FILE"
echo "  sudo apt-get install -f"
echo ""
echo "Or:"
echo "  sudo apt install ./$DEB_FILE"
echo ""

# Verify package
echo "🔍 Package contents:"
dpkg-deb -c "$DEB_FILE" | head -20
echo "..."
echo ""

echo "🎉 Ready to install!"
