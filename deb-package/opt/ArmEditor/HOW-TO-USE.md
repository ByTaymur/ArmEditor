# 🚀 ArmEditor - NASIL KULLANILIR?

## 📖 5 Dakikada Başla!

### 1️⃣ İLK DERLEME (Test Projesi)

```bash
# Örnek projeye git
cd /home/user/ArmEditor/examples/blink-led

# Derle!
make

# Çıktı:
# 🔨 Compiling: main.c
# 🔧 Assembling: startup_stm32f407xx.s
# 🔗 Linking: build/blink-led.elf
# ✅ Build complete!
```

### 2️⃣ FLASH'A YÜK

```bash
# ST-Link bağlı mı kontrol et
lsusb | grep -i stlink

# Flash et!
make flash

# Veya hızlı yöntem:
make flash-fast
```

### 3️⃣ DEBUG BAŞLAT

```bash
# Terminal 1: OpenOCD başlat
make gdb-server

# Terminal 2: GDB başlat
make gdb-client

# GDB içinde:
(gdb) break main
(gdb) continue
(gdb) print counter
(gdb) print temperature
(gdb) next
```

---

## 🎯 ArmEditor GUI İLE KULLANIM

### Başlatma

```bash
cd /home/user/ArmEditor
npm run dev
```

### Proje Aç
1. **File → Open Project**
2. `/home/user/ArmEditor/examples/blink-led` seç
3. `main.c` dosyası açılacak

### Derleme
- **F7** tuşuna bas VEYA
- **Build** butonuna tıkla

### Debug
1. **F5** tuşuna bas
2. Breakpoint koymak için satır numarasına tıkla veya **F9**
3. **F10**: Step Over
4. **F11**: Step Into
5. **Shift+F5**: Stop Debug

### Watch Variables (Gerçek Zamanlı İzleme)
1. WATCH panel'i aç
2. **+** butonuna tıkla
3. Değişken adını yaz: `counter`, `temperature`, `led_state`
4. **F5** (Continue) - Değişkenler gerçek zamanlı güncellenecek!

---

## 🔥 KEIL/IAR'DAN DAHA İYİ ÖZELLİKLER!

### 1. STM32CubeMX Projelerini İçe Aktar

```bash
# CubeMX projeniz var mı?
cd ~/Desktop/MyCubeMXProject

# ArmEditor'e aktar
node /home/user/ArmEditor/src/advanced/cubemx-importer.js .

# Otomatik olarak:
# ✅ Makefile oluşturuldu
# ✅ .vscode/armeditor.json oluşturuldu
# ✅ Derlemeye hazır!

make
```

### 2. Peripheral Register Görüntüleme (SVD)

**Keil'de:** Sadece read-only gösterir
**ArmEditor'de:** SVD parser ile TÜM peripheral detayları!

```bash
# SVD dosyasını indir
python3 /home/user/ArmEditor/src/advanced/svd-parser.py

# Kullanım:
# - GPIOD register'larını görüntüle
# - TIM1 ayarlarını göster
# - ADC değerlerini oku
# - BIT seviyesinde detay!
```

**Örnek:**
```
GPIOD_ODR = 0x00001000
  ODR12: 1 (bit 12) ← LED GREEN açık
  ODR13: 0 (bit 13) ← LED ORANGE kapalı
  ODR14: 0 (bit 14) ← LED RED kapalı
  ODR15: 0 (bit 15) ← LED BLUE kapalı
```

### 3. Gerçek Zamanlı Grafik (IAR'dan İyi!)

**IAR'de:** Durdurup okursun
**ArmEditor'de:** DURURKEN değişkenleri grafiklerde GÖR!

```javascript
// ArmEditor console'da:
realtimeGrapher.addVariable('counter');
realtimeGrapher.addVariable('temperature');
realtimeGrapher.start(gdb);

// Şimdi F5 bas ve GRAFİKLERİ İZLE! 📊
```

**Özellikler:**
- ✅ 10 Hz güncelleme (durdurmadan!)
- ✅ 1000 data point
- ✅ CSV export
- ✅ Screenshot
- ✅ Min/Max/Average istatistikler
- ✅ Trigger alarm (threshold aşılınca uyarı)

### 4. RTOS Debugging (FreeRTOS)

```bash
# FreeRTOS task'larını gör
(gdb) info threads

# Task switch et
(gdb) thread 2

# Stack kullanımı
(gdb) info stack
```

### 5. SWO Trace Viewer

**Keil'de:** Ekstra lisans gerekir
**ArmEditor'de:** BEDAVA!

```bash
# SWO trace başlat
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \\
  -c "tpiu config internal swo.log uart off 168000000"

# printf() çıktıları swo.log'a yazılır!
```

---

## 📁 YENİ PROJE OLUŞTUR

### Yöntem 1: Sıfırdan

```bash
mkdir ~/Desktop/MyArmProject
cd ~/Desktop/MyArmProject

# main.c oluştur
cat > main.c << 'EOF'
#include <stdint.h>

volatile uint32_t counter = 0;

int main(void) {
    while(1) {
        counter++;
    }
    return 0;
}
EOF

# Makefile kopyala
cp /home/user/ArmEditor/examples/blink-led/Makefile .

# Startup ve linker script kopyala
cp /home/user/ArmEditor/examples/blink-led/startup_*.s .
cp /home/user/ArmEditor/examples/blink-led/*.ld .

# Derle!
make
```

### Yöntem 2: STM32CubeMX

```bash
# 1. CubeMX ile proje oluştur
# 2. Generate Code
# 3. Terminal'de:

cd ~/Desktop/MyCubeMXProject
node /home/user/ArmEditor/src/advanced/cubemx-importer.js .

# ✅ Hazır!
make
```

### Yöntem 3: ArmEditor GUI

```bash
npm run dev

# GUI'de:
# File → New Project → STM32F407
# Project name gir
# ✅ Otomatik oluşturulur!
```

---

## 🐛 DEBUG İPUÇLARI

### Değişkenler Görünmüyor?

```c
// ❌ YANLIŞ
uint32_t counter = 0;

// ✅ DOĞRU
volatile uint32_t counter = 0;

// Debug modunda derle
make debug
```

### Breakpoint Çalışmıyor?

```bash
# Doğru ELF dosyasını kullan
arm-none-eabi-gdb build/blink-led-debug.elf

# Debug info var mı kontrol et
arm-none-eabi-readelf -S build/blink-led-debug.elf | grep debug
```

### Flash Hatası?

```bash
# ST-Link sürücüsü kur
sudo apt install stlink-tools

# Kullanıcı izni ver
sudo usermod -a -G dialout $USER

# Oturumu kapat/aç

# Test et
st-info --probe
```

---

## 📊 GERÇEK ZAMANLI ANALİZ

### Memory Usage

```bash
# Derleme sonrası:
make

# Çıktı:
# text    data     bss     dec     hex filename
#  1234     100     256    1590     636 blink-led.elf
```

### Performance Profiling

```bash
# -pg flag ekle
CFLAGS += -pg

# Çalıştır ve profil çıkar
gprof build/blink-led.elf gmon.out > analysis.txt
```

### Stack Usage

```bash
# Stack kullanımını gör
arm-none-eabi-objdump -h build/blink-led.elf | grep stack
```

---

## 🎓 ÖRNEK PROJELER

### 1. LED Blink (Basit)
```bash
cd /home/user/ArmEditor/examples/blink-led
make && make flash
```

### 2. UART Echo (Seri İletişim)
```bash
cd /home/user/ArmEditor/examples/uart-echo
make && make flash

# Serial monitor aç
minicom -D /dev/ttyUSB0 -b 115200
```

### 3. ADC Read (Analog Okuma)
```bash
cd /home/user/ArmEditor/examples/adc-read
make && make flash
```

### 4. PWM Control (Motor Kontrol)
```bash
cd /home/user/ArmEditor/examples/pwm-motor
make && make flash
```

---

## 💡 PRO İPUÇLARI

### 1. Hızlı Derleme

```bash
# Paralel derleme (4 core)
make -j4
```

### 2. Compiler Warnings

```bash
# Tüm uyarıları aç
CFLAGS += -Wall -Wextra -Wpedantic
```

### 3. Code Size Optimize

```bash
# Release modunda -Os kullan
make PROFILE=release OPT=-Os
```

### 4. Live Variable Update

```c
// GDB script: watch.gdb
display counter
display temperature
display led_state
continue

# Kullan:
arm-none-eabi-gdb -x watch.gdb build/blink-led.elf
```

---

## 🔥 HERŞEYİ BİRARAYA KOYALIM!

### Tam İş Akışı

```bash
# 1. Projeyi oluştur/aç
cd ~/Desktop/MyProject

# 2. Kod yaz
vim main.c

# 3. Debug modunda derle
make debug

# 4. Terminal 1: OpenOCD başlat
make gdb-server

# 5. Terminal 2: ArmEditor GUI başlat
cd /home/user/ArmEditor
npm run dev

# 6. GUI'de:
#    - Proje aç
#    - Breakpoint koy
#    - F5 (Debug başlat)
#    - WATCH panel'e değişken ekle
#    - Realtime graph aç
#    - F5 (Continue)

# 7. CANLI GÖRÜNTÜLE:
#    - Kod editörde satır satır
#    - Watch'ta değişkenler
#    - Graph'ta trend
#    - Memory'de hex
#    - Registers'ta CPU

# 🎉 KEIL/IAR'dan 100x daha iyi!
```

---

## 📞 YARDIM

### Sorun mu var?

```bash
# Log'ları kontrol et
make clean
make V=1  # Verbose mode

# OpenOCD log
openocd -d3 ...

# GDB log
arm-none-eabi-gdb --batch -ex "set logging on" -ex "target remote :3333"
```

### GitHub Issues
https://github.com/ByTaymur/ArmEditor/issues

---

## ✅ HAZIR!

Artık **Keil ve IAR'dan daha iyi** bir ARM geliştirme ortamına sahipsin!

**Özelliklerin Karşılaştırması:**

| Özellik | Keil | IAR | ArmEditor |
|---------|------|-----|-----------|
| Fiyat | $$$$ | $$$$ | **BEDAVA!** |
| CubeMX Import | ❌ | ❌ | ✅ |
| SVD Viewer | ✅ | ❌ | ✅✅ (Daha iyi!) |
| Realtime Graph | ❌ | ⚠️ | ✅ (10 Hz!) |
| VS Code Entegre | ❌ | ❌ | ✅ |
| Açık Kaynak | ❌ | ❌ | ✅ |
| SWO Trace | ⚠️ ($) | ⚠️ ($) | ✅ (Bedava!) |

**🚀 Başarılar!**
