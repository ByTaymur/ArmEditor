# HopeIDE Debug Configuration

Create `.vscode/launch.json` in your project root:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "hopeide",
            "request": "launch",
            "name": "HopeIDE: Debug STM32",
            "program": "${workspaceFolder}/build/firmware.elf",
            "device": "STM32F407VGT6",
            "interface": "swd",
            "servertype": "openocd"
        }
    ]
}
```

Then **HopeIDE: Debug STM32** will appear in the dropdown! 🎯

## Quick Setup:

1. Open your STM32 project in VS Code
2. Create `.vscode` folder if needed
3. Create `launch.json` with above content
4. Reload VS Code or press F5
5. Select "HopeIDE: Debug STM32" from dropdown

**Device auto-detected:** STM32F407ZGT6 ✅
