#!/bin/bash

echo "🔍 HopeIDE Extension Kontrolü"
echo "=============================="
echo ""

# Extension yüklü mü?
echo "1️⃣ Extension yüklü mü kontrol ediliyor..."
if code --list-extensions | grep -q "hopeide"; then
    echo "✅ HopeIDE extension YÜKLÜ"
    code --list-extensions | grep hopeide
else
    echo "❌ HopeIDE extension YÜKLÜ DEĞİL!"
    echo ""
    echo "📦 Yüklemek için:"
    echo "   code --install-extension $(pwd)/hopeide-1.3.2.vsix"
fi

echo ""
echo "2️⃣ VSIX dosyası kontrol ediliyor..."
if [ -f "hopeide-1.3.2.vsix" ]; then
    echo "✅ VSIX bulundu: hopeide-1.3.2.vsix"
    ls -lh hopeide-1.3.2.vsix
else
    echo "❌ VSIX bulunamadı!"
    echo "   Mevcut VSIX dosyaları:"
    ls -lh hopeide-*.vsix 2>/dev/null || echo "   Hiç VSIX yok!"
fi

echo ""
echo "3️⃣ Debugger contribution kontrol ediliyor..."
if [ -f "package.json" ]; then
    if grep -q '"type": "hopeide"' package.json; then
        echo "✅ Debugger contribution package.json'da mevcut"
    else
        echo "❌ Debugger contribution eksik!"
    fi
else
    echo "❌ package.json bulunamadı!"
fi

echo ""
echo "=============================="
echo "🎯 SONUÇ:"
echo ""
echo "Extension yüklü değilse şunu çalıştır:"
echo "  code --install-extension $(pwd)/hopeide-1.3.2.vsix"
echo ""
echo "Sonra VS Code'u reload et:"
echo "  Ctrl+Shift+P → 'Reload Window'"
