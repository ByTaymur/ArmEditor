/**
 * STM32-Specific Tools
 * Device ID, Programmer, Monitor, Runtime Debug
 * Like ST-Link Utility + ST Monitor
 */

class STM32Tools {
    constructor(openocd) {
        this.openocd = openocd;
        this.deviceInfo = null;
    }

    /**
     * STM32 Device Identification
     */
    async getDeviceID() {
        // Read DBGMCU_IDCODE (0xE0042000)
        const idcode = await this.openocd.readMemory(0xE0042000, 1);
        const id = idcode[0].values[0];

        const devId = (id >> 0) & 0xFFF;
        const revId = (id >> 16) & 0xFFFF;

        return {
            deviceID: `0x${devId.toString(16).padStart(3, '0').toUpperCase()}`,
            revisionID: `0x${revId.toString(16).padStart(4, '0').toUpperCase()}`,
            deviceName: this.getDeviceName(devId),
            revision: this.getRevisionName(devId, revId)
        };
    }

    async getUniqueID() {
        // STM32 96-bit Unique ID at 0x1FFF7A10 (F4 series)
        const uid = await this.openocd.readMemory(0x1FFF7A10, 3);

        const uid0 = uid[0].values[0];
        const uid1 = uid[1].values[0];
        const uid2 = uid[2].values[0];

        return {
            uid: [uid0, uid1, uid2],
            uidString: `${uid0.toString(16).padStart(8, '0')}-${uid1.toString(16).padStart(8, '0')}-${uid2.toString(16).padStart(8, '0')}`.toUpperCase(),
            lotNumber: `LOT_NUM: ${(uid2 >> 0) & 0xFF}`,
            wafNumber: `WAF_NUM: ${(uid2 >> 8) & 0xFF}`,
            coordinates: `X:${(uid1 >> 16) & 0xFFFF} Y:${uid1 & 0xFFFF}`
        };
    }

    async getFlashSize() {
        // Read flash size register (F4: 0x1FFF7A22)
        const flashSize = await this.openocd.readMemory(0x1FFF7A22, 1, 16);
        return {
            size: flashSize[0].values[0],
            sizeKB: `${flashSize[0].values[0]} KB`,
            sizeMB: `${(flashSize[0].values[0] / 1024).toFixed(2)} MB`
        };
    }

    async getDeviceInfo() {
        const [deviceID, uniqueID, flashSize] = await Promise.all([
            this.getDeviceID(),
            this.getUniqueID(),
            this.getFlashSize()
        ]);

        this.deviceInfo = {
            ...deviceID,
            ...uniqueID,
            flash: flashSize
        };

        return this.deviceInfo;
    }

    /**
     * STM32 Programmer (Like ST-Link Utility)
     */
    async programmerConnect() {
        await this.openocd.reset(true);
        const info = await this.getDeviceInfo();

        return {
            connected: true,
            device: info.deviceName,
            deviceID: info.deviceID,
            flash: info.flash.sizeKB
        };
    }

    async programmerReadMemory(address, length, saveToFile = null) {
        const data = await this.openocd.readMemory(address, Math.ceil(length / 4));

        // Convert to byte array
        const bytes = [];
        for (const block of data) {
            for (const value of block.values) {
                bytes.push((value >> 0) & 0xFF);
                bytes.push((value >> 8) & 0xFF);
                bytes.push((value >> 16) & 0xFF);
                bytes.push((value >> 24) & 0xFF);
            }
        }

        if (saveToFile) {
            const fs = require('fs');
            fs.writeFileSync(saveToFile, Buffer.from(bytes.slice(0, length)));
        }

        return bytes.slice(0, length);
    }

    async programmerWriteMemory(address, data) {
        // Write in chunks
        const chunkSize = 256;
        for (let i = 0; i < data.length; i += chunkSize) {
            const chunk = data.slice(i, Math.min(i + chunkSize, data.length));

            // Pack bytes into words
            const words = [];
            for (let j = 0; j < chunk.length; j += 4) {
                const word = (chunk[j] || 0) |
                           ((chunk[j + 1] || 0) << 8) |
                           ((chunk[j + 2] || 0) << 16) |
                           ((chunk[j + 3] || 0) << 24);
                words.push(word);
            }

            // Write words
            for (let j = 0; j < words.length; j++) {
                await this.openocd.writeMemory(address + i + j * 4, words[j]);
            }
        }
    }

    async programmerEraseChip() {
        await this.openocd.sendCommand('stm32f4x mass_erase 0');
    }

    async programmerEraseSectors(sectors) {
        for (const sector of sectors) {
            const sectorAddr = this.getSectorAddress(sector);
            const sectorSize = this.getSectorSize(sector);
            await this.openocd.flashErase(sectorAddr, sectorSize);
        }
    }

    /**
     * STM32 Monitor (Serial/SWO)
     */
    async monitorStartSWO(port = 0, cpuFreq = 168000000, swoFreq = 2000000) {
        // Configure SWO
        await this.openocd.sendCommand(`tpiu config internal - uart off ${cpuFreq}`);
        await this.openocd.sendCommand(`itm port ${port} on`);

        return { enabled: true, port, frequency: swoFreq };
    }

    async monitorStopSWO() {
        await this.openocd.sendCommand('itm ports off');
    }

    async monitorReadSWO() {
        // This would typically read from SWO output
        // Implementation depends on OpenOCD SWO capture
        return [];
    }

    /**
     * Runtime Debug & Code Execution
     */
    async executeFunction(address, args = []) {
        // Save current register state
        const savedRegs = await this.openocd.readRegisters();

        try {
            // Set arguments in R0-R3
            for (let i = 0; i < Math.min(args.length, 4); i++) {
                await this.openocd.writeRegister(`r${i}`, args[i]);
            }

            // Set PC to function address
            await this.openocd.writeRegister('pc', address);

            // Set breakpoint at return address
            const returnAddr = savedRegs.lr || 0;
            await this.openocd.setBreakpoint(returnAddr);

            // Resume execution
            await this.openocd.resume();

            // Wait for breakpoint hit
            await this.waitForHalt();

            // Read return value from R0
            const regs = await this.openocd.readRegisters();
            const returnValue = regs.r0;

            // Remove breakpoint
            await this.openocd.removeBreakpoint(returnAddr);

            return { success: true, returnValue };
        } catch (error) {
            return { success: false, error: error.message };
        } finally {
            // Restore registers
            for (const [reg, value] of Object.entries(savedRegs)) {
                await this.openocd.writeRegister(reg, value);
            }
        }
    }

    async executeCode(code, address = 0x20000000) {
        // Write machine code to RAM
        await this.programmerWriteMemory(address, code);

        // Execute from address
        return await this.executeFunction(address, []);
    }

    async runToAddress(address, timeout = 5000) {
        // Set temporary breakpoint
        await this.openocd.setBreakpoint(address);

        // Resume
        await this.openocd.resume();

        // Wait for breakpoint
        const hit = await this.waitForHalt(timeout);

        // Remove breakpoint
        await this.openocd.removeBreakpoint(address);

        return hit;
    }

    async stepUntilReturn() {
        const initialSP = await this.openocd.readRegister('sp');

        while (true) {
            await this.openocd.step();

            const currentSP = await this.openocd.readRegister('sp');
            if (currentSP > initialSP) {
                // SP increased, we returned
                break;
            }
        }
    }

    /**
     * Performance Profiling
     */
    async profileFunction(address, args = [], iterations = 100) {
        const times = [];

        for (let i = 0; i < iterations; i++) {
            // Enable DWT cycle counter
            await this.enableCycleCounter();

            // Reset cycle count
            await this.openocd.writeMemory(0xE0001004, 0); // DWT_CYCCNT

            // Execute function
            await this.executeFunction(address, args);

            // Read cycle count
            const cycles = await this.openocd.readMemory(0xE0001004, 1);
            times.push(cycles[0].values[0]);
        }

        return {
            min: Math.min(...times),
            max: Math.max(...times),
            avg: times.reduce((a, b) => a + b) / times.length,
            iterations
        };
    }

    async enableCycleCounter() {
        // Enable DWT and cycle counter
        await this.openocd.writeMemory(0xE0001000, 0x40000001); // DWT_CTRL: Enable cycle counter
        await this.openocd.writeMemory(0xE000EDFC, 0x01000000); // DEMCR: Enable trace
    }

    /**
     * STM32 Peripheral Access
     */
    async readPeripheral(peripheral, register) {
        const addr = this.getPeripheralAddress(peripheral, register);
        if (!addr) {
            throw new Error(`Unknown peripheral: ${peripheral}.${register}`);
        }

        const value = await this.openocd.readMemory(addr, 1);
        return value[0].values[0];
    }

    async writePeripheral(peripheral, register, value) {
        const addr = this.getPeripheralAddress(peripheral, register);
        if (!addr) {
            throw new Error(`Unknown peripheral: ${peripheral}.${register}`);
        }

        await this.openocd.writeMemory(addr, value);
    }

    getPeripheralAddress(peripheral, register) {
        // STM32F4 peripheral base addresses
        const peripherals = {
            'GPIOA': { base: 0x40020000, MODER: 0x00, ODR: 0x14, IDR: 0x10 },
            'GPIOB': { base: 0x40020400, MODER: 0x00, ODR: 0x14, IDR: 0x10 },
            'GPIOC': { base: 0x40020800, MODER: 0x00, ODR: 0x14, IDR: 0x10 },
            'RCC': { base: 0x40023800, CR: 0x00, CFGR: 0x08, AHB1ENR: 0x30 },
            'USART1': { base: 0x40011000, SR: 0x00, DR: 0x04, BRR: 0x08, CR1: 0x0C },
            'TIM2': { base: 0x40000000, CR1: 0x00, CNT: 0x24, PSC: 0x28, ARR: 0x2C },
            'ADC1': { base: 0x40012000, SR: 0x00, DR: 0x4C, CR1: 0x04, CR2: 0x08 }
        };

        const periph = peripherals[peripheral.toUpperCase()];
        if (!periph || !periph[register]) {
            return null;
        }

        return periph.base + periph[register];
    }

    /**
     * Helpers
     */
    async waitForHalt(timeout = 5000) {
        const startTime = Date.now();

        while (Date.now() - startTime < timeout) {
            // Check if halted (implementation specific to OpenOCD)
            try {
                await this.openocd.readRegister('pc');
                return true;
            } catch {
                await new Promise(resolve => setTimeout(resolve, 50));
            }
        }

        return false;
    }

    getDeviceName(devId) {
        const devices = {
            0x413: 'STM32F405/407/415/417',
            0x419: 'STM32F427/437/429/439',
            0x423: 'STM32F401xB/C',
            0x433: 'STM32F401xD/E',
            0x431: 'STM32F411xC/E',
            0x421: 'STM32F446',
            0x434: 'STM32F469/479',
            0x463: 'STM32F413/423',
            0x441: 'STM32F412',
            0x450: 'STM32H7 Series',
            0x451: 'STM32F76x/77x'
        };

        return devices[devId] || `Unknown (0x${devId.toString(16)})`;
    }

    getRevisionName(devId, revId) {
        // Device-specific revision names
        return `Rev ${String.fromCharCode(65 + (revId - 0x1000) / 0x1000)}`;
    }

    getSectorAddress(sector) {
        // STM32F4 sector addresses
        const sectors = [
            0x08000000, 0x08004000, 0x08008000, 0x0800C000,  // 16KB sectors 0-3
            0x08010000,                                        // 64KB sector 4
            0x08020000, 0x08040000, 0x08060000, 0x08080000,  // 128KB sectors 5-8
            0x080A0000, 0x080C0000, 0x080E0000               // 128KB sectors 9-11
        ];

        return sectors[sector] || 0x08000000;
    }

    getSectorSize(sector) {
        // STM32F4 sector sizes
        if (sector < 4) return 16 * 1024;      // 16KB
        if (sector === 4) return 64 * 1024;    // 64KB
        return 128 * 1024;                      // 128KB
    }
}

module.exports = STM32Tools;
