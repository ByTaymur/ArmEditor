#!/bin/bash
# Manual VSIX package creator (workaround for vsce issues)

echo "📦 Creating HopeIDE VSIX package manually..."

cd "$(dirname "$0")"

# Ensure compilation
echo "🔨 Compiling TypeScript..."
npm run compile

if [ $? -ne 0 ]; then
    echo "❌ Compilation failed!"
    exit 1
fi

echo "✅ Compilation successful!"

# Create package structure
echo "📁 Creating package structure..."
mkdir -p vsix-temp/extension

# Copy necessary files
cp -r out vsix-temp/extension/
cp -r resources vsix-temp/extension/
cp package.json vsix-temp/extension/
cp README.md vsix-temp/extension/
cp CHANGELOG.md vsix-temp/extension/
cp LICENSE vsix-temp/extension/

# Create [Content_Types].xml
cat > vsix-temp/[Content_Types].xml << 'EOF'
<?xml version="1.0" encoding="utf-8"?>
<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">
    <Default Extension=".json" ContentType="application/json"/>
    <Default Extension=".vsixmanifest" ContentType="text/xml"/>
    <Default Extension=".md" ContentType="text/plain"/>
    <Default Extension=".js" ContentType="application/javascript"/>
    <Default Extension=".png" ContentType="image/png"/>
</Types>
EOF

# Create extension.vsixmanifest
cat > vsix-temp/extension.vsixmanifest << 'EOF'
<?xml version="1.0" encoding="utf-8"?>
<PackageManifest Version="2.0.0" xmlns="http://schemas.microsoft.com/developer/vsx-schema/2011">
    <Metadata>
        <Identity Id="hopeide" Version="1.0.0" Language="en-US" Publisher="hopeide"/>
        <DisplayName>HopeIDE - ARM Embedded Development</DisplayName>
        <Description>Professional ARM Cortex-M debugging - Free Keil alternative for STM32</Description>
        <Tags>stm32,arm,cortex-m,embedded,debugging</Tags>
        <Categories>Debuggers</Categories>
        <Icon>extension/resources/icon.png</Icon>
        <License>extension/LICENSE</License>
    </Metadata>
    <Installation>
        <InstallationTarget Id="Microsoft.VisualStudio.Code"/>
    </Installation>
    <Dependencies/>
    <Assets>
        <Asset Type="Microsoft.VisualStudio.Code.Manifest" Path="extension/package.json"/>
    </Assets>
</PackageManifest>
EOF

# Create ZIP (VSIX is just a ZIP)
cd vsix-temp
zip -r ../hopeide-1.0.0.vsix . -x "*.DS_Store"
cd ..

# Cleanup
rm -rf vsix-temp

if [ -f hopeide-1.0.0.vsix ]; then
    echo "✅ VSIX package created: hopeide-1.0.0.vsix"
    ls -lh hopeide-1.0.0.vsix
    echo ""
    echo "📦 To install:"
    echo "   code --install-extension hopeide-1.0.0.vsix"
else
    echo "❌ Failed to create VSIX package"
    exit 1
fi
