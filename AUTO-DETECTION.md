# STM32 Evrensel Otomatik Tespit Sistemi 🚀

## Özellikler

### ✅ Tamamlanan Geliştirmeler

1. **🔍 Otomatik STM32 Tespiti**
   - Bağlı işlemci otomatik tespit edilir
   - IDCODE okuma ve analiz
   - Tüm STM32 aileleri desteklenir (F0-F7, H7, L0-L5, G0-G4, WB, WL)

2. **🎯 Akıllı Konfigürasyon**
   - OpenOCD target otomatik seçilir
   - Compiler bayrakları otomatik belirlenir
   - CPU tipi (Cortex-M0/M3/M4/M7/M33) otomatik algılanır
   - FPU ayarları otomatik yapılandırılır

3. **💡 Kullanıcı Bildirimleri**
   - Tespit edilen işlemci adı gösterilir
   - Voltage uyarıları (düşük voltaj)
   - Desteklenmeyen işlemci uyarıları
   - Bağlantı problemleri için öneriler

## Desteklenen STM32 Aileleri

### STM32F Serisi (Performance)
- **F0**: STM32F030, F051, F072, F091
- **F1**: STM32F103, F105, F107
- **F2**: STM32F205, F207
- **F3**: STM32F303, F334, F373
- **F4**: STM32F401, F405, F407, F411, F427, F429, F446, F469
- **F7**: STM32F722, F730, F732, F745, F746, F750, F756, F765, F767, F769, F777

### STM32H Serisi (High Performance)
- **H7**: STM32H743, H750, H753

### STM32L Serisi (Ultra Low Power)
- **L0**: STM32L031, L051, L071
- **L1**: STM32L151, L152
- **L4**: STM32L432, L433, L476, L486
- **L5**: STM32L552, L562

### STM32G Serisi (Mainstream)
- **G0**: STM32G030, G031, G070, G071
- **G4**: STM32G431, G441, G473, G474, G483, G484

### STM32W Serisi (Wireless)
- **WB**: STM32WB55 (Bluetooth)
- **WL**: STM32WL55 (LoRa)

## Kullanım

### Flash İşlemi
```javascript
const flasher = new OpenOCDFlasher({
    autoDetect: true  // Otomatik tespit aktif
});

await flasher.flash('firmware.elf', (type, text) => {
    console.log(text);
});
```

Çıktı:
```
🔍 Detecting connected STM32 chip...
✅ STM32F746 detected successfully!
📋 Target: STM32F746 (STM32F7)
🎯 OpenOCD Config: stm32f7x
💻 CPU: cortex-m7
⚠️ Warning: Low target voltage (0.00V). Normal is 3.3V.

🧹 Cleaning old OpenOCD processes...
⚡ Starting flash operation...
```

### Debug Oturumu
```javascript
const flasher = new OpenOCDFlasher({
    autoDetect: true
});

await flasher.startDebugServer((type, text) => {
    console.log(text);
});
```

### Manuel Konfigürasyon (Opsiyonel)
```javascript
const flasher = new OpenOCDFlasher({
    autoDetect: false,
    interface: 'stlink',
    target: 'stm32f4x'  // Manuel olarak belirt
});
```

## Test

Test scripti ile sistemi kontrol edebilirsiniz:

```bash
node test-detection.js
```

Örnek çıktı:
```
🔍 STM32 Auto-Detection Test

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Scanning for connected STM32...

📊 Detection Results:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✅ Status: SUCCESS
🎯 Chip: STM32F746
📋 Family: STM32F7
🔧 OpenOCD Target: stm32f7x
🔌 IDCODE: 0x5ba02477
⚡ Voltage: 3.30V

📝 OpenOCD Configuration:
  Interface: interface/stlink.cfg
  Target: target/stm32f7x.cfg

💻 Compiler Flags:
  CPU: cortex-m7
  FPU: -mfpu=fpv5-sp-d16 -mfloat-abi=hard
  Defines: STM32F7, USE_HAL_DRIVER
```

## Hata Durumları

### STLink Bulunamadı
```
❌ No STM32 chip detected. Please check your ST-Link connection.

💡 Suggestion:
Make sure:
1. ST-Link is connected via USB
2. Target board is powered
3. SWDIO/SWCLK cables are properly connected
```

### Desteklenmeyen İşlemci
```
⚠️ Unknown STM32 chip detected (IDCODE: 0xXXXXXXXX). 
Please check your device.

This chip is not in our database. Please verify your 
connection or update ArmEditor.
```

### Düşük Voltaj Uyarısı
```
⚠️ Warning: Low target voltage (1.20V). Normal is 3.3V.
```

## Teknik Detaylar

### IDCODE Database
- 70+ farklı STM32 modeli
- ARM CoreSight Debug TAP ID'leri
- Family/Series/Target mapping

### OpenOCD Konfigürasyonu
- Interface: `stlink.cfg` (deprecated `stlink-v2.cfg` yerine)
- Transport: `hla_swd` (otomatik seçilir)
- Speed: 2000 kHz

### Compiler Flag Mapping
| Family | CPU | FPU |
|--------|-----|-----|
| F0 | Cortex-M0 | - |
| F1 | Cortex-M3 | - |
| F3 | Cortex-M4 | - |
| F4 | Cortex-M4 | FPv4-SP-D16 |
| F7 | Cortex-M7 | FPv5-SP-D16 |
| H7 | Cortex-M7 | FPv5-D16 |
| L0 | Cortex-M0+ | - |
| L4 | Cortex-M4 | FPv4-SP-D16 |
| L5 | Cortex-M33 | - |
| G0 | Cortex-M0+ | - |
| G4 | Cortex-M4 | FPv4-SP-D16 |

## Avantajlar

✅ **Kullanıcı Dostu**: İşlemci tipini bilmeye gerek yok
✅ **Hata Önleme**: Yanlış konfigürasyon hatalarını önler
✅ **Profesyonel**: Keil/IAR gibi çalışır
✅ **Evrensel**: Tüm STM32 aileleri desteklenir
✅ **Genişletilebilir**: Yeni işlemciler kolayca eklenebilir

## Gelecek Geliştirmeler

- [ ] STM32MP (Multiprocessor) desteği
- [ ] STM32C (China) serisi desteği
- [ ] Diğer ARM MCU'lar (NXP, TI, Nordic, etc.)
- [ ] Flash size/RAM size otomatik tespiti
- [ ] Bootloader versiyonu gösterimi
