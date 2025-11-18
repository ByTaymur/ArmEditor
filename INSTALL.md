# ArmEditor - Kurulum Kılavuzu

## 🇹🇷 Türkçe Kurulum

### Gereksinimler

```bash
# Ubuntu/Debian için
sudo apt update
sudo apt install -y nodejs npm git

# ARM Derleyici Araçları
sudo apt install -y gcc-arm-none-eabi gdb-multiarch openocd stlink-tools
```

### Yöntem 1: .deb Paketi ile Kurulum (Önerilen)

```bash
# 1. Projeyi klonlayın
git clone https://github.com/ByTaymur/ArmEditor.git
cd ArmEditor

# 2. .deb paketi oluşturun
chmod +x build-deb.sh
./build-deb.sh

# 3. Paketi kurun
sudo apt install ./dist/arm-editor_1.0.0_amd64.deb

# 4. Çalıştırın
armeditor
```

### Yöntem 2: Geliştirme Modunda Çalıştırma

```bash
# 1. Projeyi klonlayın
git clone https://github.com/ByTaymur/ArmEditor.git
cd ArmEditor

# 2. Bağımlılıkları yükleyin
npm install

# 3. Geliştirme modunda çalıştırın
npm run dev
```

## 🚀 İlk Proje Oluşturma

### 1. ArmEditor'ü Başlatın

```bash
armeditor
```

Ya da Uygulamalar menüsünden: **Geliştirme → ArmEditor**

### 2. Yeni Proje Oluşturun

- **"Create New Project"** butonuna tıklayın
- Proje konumunu seçin (örn: `~/Desktop/MySTM32Project`)
- Proje otomatik olarak oluşturulacak

### 3. Proje Yapısı

```
MySTM32Project/
├── src/
│   └── main.c          # Ana kaynak dosyanız
├── inc/
│   └── main.h          # Header dosyalar
├── lib/                # Kütüphaneler
├── build/              # Derleme çıktıları
├── Makefile            # Derleme yapılandırması
└── .vscode/            # VS Code entegrasyonu
    ├── tasks.json
    ├── launch.json
    ├── c_cpp_properties.json
    └── armeditor.json  # ArmEditor yapılandırması
```

### 4. Kod Yazma

`src/main.c` dosyasını açın:

```c
#include "stm32f4xx.h"

// ✅ Debug için volatile kullanın!
volatile uint32_t sayac = 0;
volatile float sicaklik = 25.0f;

int main(void) {
    HAL_Init();
    SystemClock_Config();

    while(1) {
        sayac++;
        sicaklik += 0.1f;
        HAL_Delay(100);
    }
}
```

### 5. Derleme

**F7** tuşuna basın veya **"Build"** butonuna tıklayın.

```bash
# Terminal'de:
make all

# Debug modunda:
make debug  # -O0 -g3 ile derler
```

### 6. Flash (Yükleme)

**"Flash"** butonuna tıklayın veya:

```bash
make flash
```

### 7. Debug (Hata Ayıklama)

**F5** tuşuna basın veya **"Debug"** butonuna tıklayın.

#### Breakpoint Koyma
- Satır numarasına tıklayın veya **F9** basın

#### Değişken İzleme
- WATCH panelinden değişken ekleyin
- Değişkenler gerçek zamanlı güncellenecek

#### Debug Kısayolları
- **F5**: Devam et (Continue)
- **F10**: Üzerinden geç (Step Over)
- **F11**: İçine gir (Step Into)
- **Shift+F11**: Dışarı çık (Step Out)
- **Shift+F5**: Debug'ı durdur

## 🔌 VS Code Entegrasyonu

### Otomatik Kurulum

ArmEditor'ü kurduğunuzda VS Code extension'ı otomatik kurulur.

### Manuel Kurulum

```bash
code --install-extension /opt/ArmEditor/vscode-extension
```

### VS Code'da Kullanım

1. ARM projenizi VS Code ile açın
2. `.vscode/armeditor.json` dosyası varsa ArmEditor otomatik aktif olur
3. Komutlar:
   - **Ctrl+Shift+P** → `ArmEditor: Build Project`
   - **Ctrl+Shift+P** → `ArmEditor: Flash Device`
   - **Ctrl+Shift+P** → `ArmEditor: Open in ArmEditor IDE`

### Hem ArmEditor Hem VS Code Kullanımı

```bash
# Terminal 1: ArmEditor'ü başlat
armeditor

# Terminal 2: VS Code'u başlat
code ~/Desktop/MySTM32Project

# İki program birbirleriyle haberleşecek!
# - VS Code'da düzenleme yapın
# - ArmEditor'de derleyip debug edin
# - Veya tam tersi!
```

## 🛠️ Yapılandırma

### ARM Derleyici Ayarları

`/etc/armeditor/config.json`:

```json
{
  "toolchain": {
    "prefix": "arm-none-eabi-",
    "path": "/usr/bin"
  },
  "debugger": {
    "gdb": "arm-none-eabi-gdb",
    "openocd": "openocd"
  }
}
```

### Proje Ayarları

`.vscode/armeditor.json`:

```json
{
  "name": "Benim STM32 Projem",
  "type": "arm-cortex-m",
  "mcu": "STM32F407VG",
  "buildSystem": "make",
  "debugger": {
    "type": "openocd",
    "interface": "stlink-v2",
    "target": "stm32f4x"
  }
}
```

### Makefile Özelleştirme

```makefile
# MCU Seçimi
MCU = cortex-m4

# Optimizasyon
OPT = -Os        # Boyut için optimize et
OPT = -O2        # Hız için optimize et
OPT = -O0 -g3    # Debug için optimize etme

# FPU Desteği (STM32F4 için)
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
```

## 🐛 Sorun Giderme

### 1. ARM Derleyici Bulunamadı

```bash
sudo apt install gcc-arm-none-eabi gdb-multiarch openocd

# Kontrol et
arm-none-eabi-gcc --version
```

### 2. ST-Link Algılanmıyor

```bash
# ST-Link araçlarını kur
sudo apt install stlink-tools

# Kullanıcıyı dialout grubuna ekle
sudo usermod -a -G dialout $USER

# Oturumu kapat ve tekrar aç
```

### 3. OpenOCD Bağlantı Hatası

```bash
# OpenOCD test et
openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg

# Çıktıda "target halted" görmelisiniz
```

### 4. Debug'da Değişkenler Görünmüyor

```c
// ❌ YANLIŞ
uint32_t sayac = 0;

// ✅ DOĞRU
volatile uint32_t sayac = 0;

// Debug modunda derle
make clean
make debug  # -O0 -g3 ile
```

### 5. VS Code Entegrasyonu Çalışmıyor

```bash
# WebSocket bağlantısını kontrol et
netstat -tulpn | grep 9876

# ArmEditor çalışıyor olmalı
```

## 📦 Güncelleme

```bash
# Yeni versiyon için
cd ArmEditor
git pull
./build-deb.sh
sudo apt install --reinstall ./dist/arm-editor_1.0.0_amd64.deb
```

## 🗑️ Kaldırma

```bash
sudo apt remove arm-editor

# Ayar dosyalarını da silmek için
sudo apt purge arm-editor
```

## 💡 İpuçları

### 1. Hızlı Klavye Kısayolları

- **Ctrl+N**: Yeni proje
- **Ctrl+O**: Proje aç
- **Ctrl+S**: Kaydet
- **F7**: Derle
- **F5**: Debug başlat
- **F9**: Breakpoint

### 2. Terminal Kullanımı

```bash
# ArmEditor terminalinde
make all          # Derle
make clean        # Temizle
make flash        # Yükle
make debug        # Debug derlemesi
```

### 3. Serial Monitor

- **Tools** → **Serial Monitor**
- UART çıktılarını izleyin
- 115200 baud varsayılan

### 4. Çoklu Proje

```bash
# Farklı terminallerde
armeditor ~/Projects/Project1
armeditor ~/Projects/Project2
```

## 🎓 Örnekler

### STM32 LED Yakma

```c
#include "stm32f4xx.h"

int main(void) {
    HAL_Init();

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    while(1) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(500);
    }
}
```

### ADC Okuma

```c
volatile uint16_t adc_deger = 0;

int main(void) {
    HAL_Init();
    ADC_Init();

    while(1) {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        adc_deger = HAL_ADC_GetValue(&hadc1);
        HAL_Delay(100);
    }
}
```

## 🌟 Daha Fazla

- **Dokümantasyon**: [https://armeditor.dev/docs](https://armeditor.dev/docs)
- **Video Eğitimler**: [YouTube Kanalı](#)
- **Forum**: [https://forum.armeditor.dev](https://forum.armeditor.dev)
- **Discord**: [Discord Sunucusu](#)

---

**Başarılar! 🚀**

Sorularınız için: [GitHub Issues](https://github.com/ByTaymur/ArmEditor/issues)
