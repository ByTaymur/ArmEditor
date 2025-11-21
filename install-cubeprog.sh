#!/bin/bash
# STM32CubeProgrammer Installation Script

echo "🔧 STM32CubeProgrammer Installation Script"
echo "=========================================="
echo ""

# Check if already installed
if command -v STM32_Programmer_CLI &> /dev/null; then
    echo "✅ STM32CubeProgrammer is already installed"
    STM32_Programmer_CLI --version
    exit 0
fi

echo "📥 STM32CubeProgrammer needs to be installed manually"
echo ""
echo "Steps:"
echo "1. Download from: https://www.st.com/en/development-tools/stm32cubeprog.html"
echo "   (You need to create a free ST account)"
echo ""
echo "2. Extract the ZIP file"
echo "   unzip ~/Downloads/en.stm32cubeprog-lin*.zip"
echo ""
echo "3. Run the installer:"
echo "   cd SetupSTM32CubeProgrammer-*/"
echo "   sudo ./SetupSTM32CubeProgrammer-*.linux"
echo ""
echo "4. Add to PATH (add to ~/.bashrc):"
echo "   export PATH=\"/usr/local/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin:\$PATH\""
echo ""
echo "5. Reload shell:"
echo "   source ~/.bashrc"
echo ""
echo "6. Verify installation:"
echo "   STM32_Programmer_CLI --version"
echo ""

read -p "Do you want to open the download page? (y/n) " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    xdg-open "https://www.st.com/en/development-tools/stm32cubeprog.html" 2>/dev/null || \
    open "https://www.st.com/en/development-tools/stm32cubeprog.html" 2>/dev/null || \
    echo "Please visit: https://www.st.com/en/development-tools/stm32cubeprog.html"
fi
