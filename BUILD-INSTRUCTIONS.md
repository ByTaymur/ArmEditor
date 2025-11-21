# ArmEditor - Kurulum Talimatları

## Yöntem 1: Kendi Bilgisayarınızda Build Edin (ÖNERİLEN)

```bash
# 1. Projeyi clone edin
git clone -b claude/setup-arm-compiler-015bn4WDFqfRHccswmMaA8Dq \
  https://github.com/ByTaymur/ArmEditor.git
cd ArmEditor

# 2. Build edin (otomatik)
chmod +x build-electron-deb.sh
./build-electron-deb.sh

# 3. ArmEditor.deb oluşacak!
# Kurulum:
sudo dpkg -i ArmEditor.deb

# Çalıştırma:
armeditor
```

## Ne Kurulur?

✅ **Electron Desktop App** - Kendi GUI'si
✅ **Monaco Editor** - VS Code editörü
✅ **AI Code Assistant** - Otomatik bug bulma
✅ **Memory Analyzer** - Leak detection
✅ **Performance Profiler** - Optimization tips
✅ **STM32CubeMX Importer** - .ioc projeler
✅ **Örnek Projeler** - LED, UART, Motor Control

## Gereksinimler

```bash
# Node.js ve npm kurulu olmalı
sudo apt install nodejs npm

# Build araçları
sudo apt install build-essential
```

## Build Süresi

- Dependencies install: ~20 saniye
- Electron build: ~15 saniye
- **TOPLAM: ~35 saniye**

## Dosya Boyutu

- Kaynak kod: ~2 MB
- Build sonrası .deb: **69 MB**
- Kurulu boyut: **253 MB**

## ARM Toolchain (İsteğe Bağlı)

STM32 projelerini derlemek için:

```bash
sudo apt install gcc-arm-none-eabi gdb-multiarch openocd
```

## Özellikler

### 🎯 Keil/IAR'dan Üstünlükler:

| Özellik | Keil µVision | ArmEditor |
|---------|--------------|-----------|
| Fiyat | $5,000+ | **BEDAVA** |
| AI Asistan | ❌ | ✅ |
| Modern UI | ❌ | ✅ |
| CubeMX 1-Click | ❌ | ✅ |
| Memory Leak Detection | ❌ | ✅ |
| Performance Profiler | ❌ | ✅ |

### 🚀 Menüler:

- **File**: New, Open, Save, Recent Files
- **Build**: Compile, Clean, Rebuild
- **Debug**: Start, Stop, Breakpoints, Watch
- **AI Tools**: Analyze Code, Check Memory, Profile Performance
- **Tools**: CubeMX Import, Terminal

### ⌨️ Klavye Kısayolları:

- `Ctrl+O` - Dosya Aç
- `Ctrl+S` - Kaydet
- `F7` - Build
- `F5` - Debug Başlat
- `Ctrl+Shift+A` - AI Analiz

## Sorun Giderme

### Bağımlılık Hatası:

```bash
sudo apt --fix-broken install
```

### Electron Çalışmıyor:

```bash
# Root olarak çalıştırmayın!
# Normal kullanıcı ile:
armeditor
```

### Build Hatası:

```bash
# Node modules temizle
rm -rf node_modules package-lock.json
npm install
./build-electron-deb.sh
```

## Destek

GitHub: https://github.com/ByTaymur/ArmEditor

---

**KEIL'DEN İYİ, BEDAVA, AÇIK KAYNAK! 🚀**
