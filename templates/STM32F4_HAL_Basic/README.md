# STM32F4 HAL Basic Template

This is a basic STM32F4 HAL project template with GPIO LED blink example.

## Features

- ✅ STM32F407VGT6 target (configurable)
- ✅ HAL driver configuration
- ✅ System clock configuration (168 MHz)
- ✅ GPIO LED blink example (PD12)
- ✅ Ready-to-build project structure

## Usage

1. Create new project from this template using HopeIDE
2. Customize MCU and settings if needed
3. Build and flash

## Example Code

The template includes a simple LED blink on GPIO PD12:

```c
while (1) {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
    HAL_Delay(500);
}
```

## Customization

Edit `project.json` to change:
- Target MCU
- Clock speed
- Compiler optimization
- Include paths

Or use **Project Settings** GUI (Alt+P) in HopeIDE.

## Building

```bash
make
```

## Flashing

Use HopeIDE flash button or:

```bash
# Via HopeIDE (recommended)
# Build → Flash Firmware

# Or manual:
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
  -c "program build/firmware.hex verify reset exit"
```
