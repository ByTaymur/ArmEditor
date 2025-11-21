#!/bin/bash
# STM32CubeProgrammer Installation Script
# Auto-downloads and installs STM32CubeProgrammer CLI

set -e

echo "🔧 Installing STM32CubeProgrammer CLI..."

# Check if already installed
if command -v STM32_Programmer_CLI &> /dev/null; then
    echo "✅ STM32CubeProgrammer already installed!"
    STM32_Programmer_CLI --version
    exit 0
fi

# Create temp directory
TEMP_DIR=$(mktemp -d)
cd "$TEMP_DIR"

echo "📥 Downloading STM32CubeProgrammer..."
# Note: User must download from ST website due to login requirement
echo ""
echo "⚠️  Please download STM32CubeProgrammer from:"
echo "   https://www.st.com/en/development-tools/stm32cubeprog.html"
echo ""
echo "   Select: Linux version (ZIP)"
echo "   Copy the downloaded file to: /tmp/stm32cubeprog.zip"
echo ""
read -p "Press Enter after downloading to /tmp/stm32cubeprog.zip..."

if [ ! -f "/tmp/stm32cubeprog.zip" ]; then
    echo "❌ File not found: /tmp/stm32cubeprog.zip"
    exit 1
fi

echo "📦 Extracting..."
unzip -q /tmp/stm32cubeprog.zip -d "$TEMP_DIR"

# Find the installer
INSTALLER=$(find "$TEMP_DIR" -name "SetupSTM32CubeProgrammer*.linux" | head -1)

if [ -z "$INSTALLER" ]; then
    echo "❌ Installer not found in ZIP file"
    exit 1
fi

echo "🚀 Running installer..."
chmod +x "$INSTALLER"
sudo "$INSTALLER" --mode silent --prefix /opt/STM32CubeProgrammer

# Add to PATH
if ! grep -q "STM32CubeProgrammer" ~/.bashrc; then
    echo 'export PATH="/opt/STM32CubeProgrammer/bin:$PATH"' >> ~/.bashrc
    echo "✅ Added to ~/.bashrc"
fi

# Source for current session
export PATH="/opt/STM32CubeProgrammer/bin:$PATH"

echo ""
echo "✅ Installation complete!"
echo ""
echo "Version:"
STM32_Programmer_CLI --version || echo "   (Restart terminal for PATH update)"

echo ""
echo "💡 Restart your terminal or run: source ~/.bashrc"

# Cleanup
rm -rf "$TEMP_DIR"
rm -f /tmp/stm32cubeprog.zip
