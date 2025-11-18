# 🚀 ArmEditor - KURULUM

## ⚡ HIZLI KURULUM (1 Dakika!)

### 1️⃣ .deb Paketini Kur

```bash
cd /home/user/ArmEditor

# Paketi kur
sudo apt install ./armeditor_1.0.0_amd64.deb
```

**VEYA:**

```bash
# Alternatif yöntem
sudo dpkg -i armeditor_1.0.0_amd64.deb
sudo apt-get install -f  # Eksik bağımlılıkları kur
```

### 2️⃣ ARM Toolchain Kur (Gerekli!)

```bash
sudo apt install gcc-arm-none-eabi gdb-multiarch openocd stlink-tools
```

### 3️⃣ ÇALIŞIR! ✅

```bash
# AI Code Analysis
armeditor --ai examples/blink-led/main.c

# CubeMX Import
armeditor --cubemx ~/MySTM32Project

# Test Suite
armeditor --test

# GUI Mode (Electron)
armeditor --gui
```

---

## 📦 PAKET BİLGİLERİ

```
Paket Adı:    armeditor
Versiyon:     1.0.0
Boyut:        52 KB (kod + örnekler)
Mimari:       amd64
Bağımlılık:   nodejs (>= 14.0), npm
```

**İçindekiler:**
- ✅ AI Code Assistant
- ✅ Memory Analyzer
- ✅ Performance Profiler
- ✅ CubeMX Importer
- ✅ 3 Örnek Proje (LED blink, UART echo, Motor control)
- ✅ Tüm dokümantasyon
- ✅ Test suite

---

## 🎯 KULLANIM

### AI Code Analysis

```bash
# C dosyasını analiz et
armeditor --ai main.c
```

**Çıktı:**
```
🤖 AI Code Assistant Analysis
============================================================

🐛 BUG DETECTION:
  [HIGH] Line 12
  Missing volatile keyword for hardware register
  💡 Use: volatile uint32_t *reg = ...

⚡ PERFORMANCE:
  Line 73: counter % 4 → counter & 3 (4x faster!)

📊 CODE REVIEW SCORE: 81/100
```

### Full Analysis

```bash
# ELF + Source analizi
armeditor --analyze build/app.elf
```

**Çıktı:**
```
🤖 AI Code Analysis...
💾 Memory Analysis...
⚡ Performance Analysis...
```

### CubeMX Import

```bash
# STM32CubeMX projesini import et
armeditor --cubemx ~/Desktop/MyCubeMXProject
```

**Oluşturulur:**
- ✅ Makefile
- ✅ Build configuration
- ✅ ArmEditor config

### Test Suite

```bash
# Tüm testleri çalıştır
armeditor --test
```

---

## 📁 KURULUM SONRASI

### Dosya Konumları

```
/opt/ArmEditor/              # Ana dizin
├── src/                     # Kaynak kodlar
│   ├── ai/                  # AI features
│   ├── advanced/            # Advanced tools
│   ├── compiler/            # Toolchain
│   ├── debugger/            # GDB
│   └── ...
├── examples/                # Örnek projeler
│   ├── blink-led/
│   ├── uart-echo/
│   └── motor-control-pro/
├── README.md               # Dokümantasyon
├── HOW-TO-USE.md
├── DEMO.md
└── INSTALL.md

/usr/bin/armeditor          # Launcher script
/etc/armeditor/             # Configuration
└── config.json

~/.armeditor/               # User data
```

### Komutlar

```bash
# Yardım
armeditor

# AI analiz
armeditor --ai <file.c>

# Full analiz
armeditor --analyze <file.elf>

# CubeMX import
armeditor --cubemx <project-dir>

# Test
armeditor --test

# GUI
armeditor --gui
```

---

## 🛠️ SORUN GİDERME

### Node.js Modülleri Eksik

```bash
cd /opt/ArmEditor
sudo npm install --production
```

### ARM Toolchain Eksik

```bash
sudo apt install gcc-arm-none-eabi gdb-multiarch openocd
```

### Permisyon Hatası

```bash
# User grubuna ekle
sudo usermod -a -G dialout $USER

# Oturumu kapat/aç
```

---

## 🗑️ KALDIRMA

```bash
# Paketi kaldır
sudo apt remove armeditor

# Tüm ayarlarla beraber
sudo apt purge armeditor

# User data'yı da sil (opsiyonel)
rm -rf ~/.armeditor
```

---

## 📊 ÖRNEKLER

### Örnek 1: LED Blink Analiz

```bash
cd /opt/ArmEditor/examples/blink-led

# AI analiz
armeditor --ai main.c

# Derle
make

# AI analiz (derlenmiş)
armeditor --analyze build/blink-led.elf
```

### Örnek 2: Motor Control

```bash
cd /opt/ArmEditor/examples/motor-control-pro

# Kodu oku
cat README.md

# AI analiz
armeditor --ai main.c

# Derle
make

# Full analiz
make analyze
```

### Örnek 3: CubeMX Projesi

```bash
# CubeMX projen varsa
armeditor --cubemx ~/Desktop/MySTM32Project

# Sonra
cd ~/Desktop/MySTM32Project
make
```

---

## ✅ BAŞARILI KURULUM KONTROLÜ

```bash
# 1. Paket kurulu mu?
dpkg -l | grep armeditor

# 2. Komut çalışıyor mu?
armeditor

# 3. AI çalışıyor mu?
armeditor --ai /opt/ArmEditor/examples/blink-led/main.c

# 4. Test geçiyor mu?
armeditor --test
```

**Hepsi çalışıyorsa:**
```
✅ ArmEditor başarıyla kuruldu!
```

---

## 🚀 İLK ADIMLAR

### 1. Örnekleri İncele

```bash
cd /opt/ArmEditor/examples

# LED Blink
cd blink-led
cat README.md

# Motor Control (PRO!)
cd ../motor-control-pro
cat README.md
```

### 2. Kendi Projeni Oluştur

```bash
mkdir ~/MyARMProject
cd ~/MyARMProject

# main.c yaz
vim main.c

# AI ile analiz et
armeditor --ai main.c
```

### 3. CubeMX Projesini İçe Aktar

```bash
# CubeMX ile proje oluştur
# STM32CubeMX → Generate Code

# ArmEditor ile import et
armeditor --cubemx .

# Derle!
make
```

---

## 🎉 HAZIR!

**ArmEditor kuruldu ve çalışıyor!**

**Keil/IAR'dan DAHA İYİ, BEDAVA, AI-POWERED!**

```bash
# Hemen test et:
armeditor --test
```
