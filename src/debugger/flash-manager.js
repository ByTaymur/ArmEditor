/**
 * Advanced Flash Manager
 * Option bytes, protection, bootloader, firmware management
 * Keil/IAR level flash operations
 */

const OpenOCDInterface = require('./openocd-interface');
const fs = require('fs');
const path = require('path');

class FlashManager {
    constructor(openocd) {
        this.openocd = openocd;
        this.flashInfo = null;
    }

    /**
     * Initialize flash info
     */
    async initialize() {
        this.flashInfo = await this.openocd.getFlashInfo();
        return this.flashInfo;
    }

    /**
     * Simple flash method (for UI)
     */
    async flash(file, options = {}) {
        const verify = options.verify !== false;
        const reset = options.reset !== false;
        const erase = options.erase !== false;

        try {
            // Halt target
            await this.openocd.halt();

            // Erase if requested
            if (erase) {
                await this.eraseFlash(options.fullErase || false);
            }

            // Program flash
            await this.programFlash(file);

            // Verify if requested
            if (verify) {
                await this.verifyFlash(file);
            }

            // Reset and run if requested
            if (reset) {
                await this.openocd.reset(false);
            }

            return { success: true };
        } catch (error) {
            throw new Error(`Flash failed: ${error.message}`);
        }
    }

    /**
     * Erase entire chip (for UI)
     */
    async eraseChip() {
        try {
            await this.openocd.halt();
            await this.eraseFlash(true); // Full chip erase
            return { success: true };
        } catch (error) {
            throw new Error(`Erase failed: ${error.message}`);
        }
    }

    /**
     * Complete flash programming workflow (Keil-style)
     */
    async programAndRun(file, verify = true, reset = true) {
        const steps = [];

        try {
            // 1. Halt target
            steps.push('Halting target...');
            await this.openocd.halt();

            // 2. Unlock flash
            steps.push('Unlocking flash...');
            await this.unlockFlash();

            // 3. Erase sectors
            steps.push('Erasing flash...');
            await this.eraseFlash();

            // 4. Program flash
            steps.push(`Programming ${path.basename(file)}...`);
            await this.programFlash(file);

            // 5. Verify if requested
            if (verify) {
                steps.push('Verifying...');
                const ok = await this.verifyFlash(file);
                if (!ok) {
                    throw new Error('Verification failed!');
                }
            }

            // 6. Lock flash
            steps.push('Locking flash...');
            await this.lockFlash();

            // 7. Reset and run
            if (reset) {
                steps.push('Resetting target...');
                await this.openocd.reset(false); // Reset and run
            }

            return { success: true, steps };
        } catch (error) {
            return { success: false, steps, error: error.message };
        }
    }

    /**
     * Flash unlock/lock (STM32 specific)
     */
    async unlockFlash() {
        // STM32 flash unlock sequence
        await this.openocd.writeMemory(0x40023C04, 0x45670123); // FLASH_KEYR
        await this.openocd.writeMemory(0x40023C04, 0xCDEF89AB);
    }

    async lockFlash() {
        const cr = await this.openocd.readMemory(0x40023C10, 1); // FLASH_CR
        await this.openocd.writeMemory(0x40023C10, cr[0].values[0] | 0x80000000); // Set LOCK bit
    }

    /**
     * Flash erase operations
     */
    async eraseFlash(fullChip = false) {
        if (fullChip) {
            // Mass erase
            await this.openocd.sendCommand('stm32f4x mass_erase 0');
        } else {
            // Erase all sectors
            await this.openocd.flashErase(0, 0);
        }
    }

    async eraseSector(sectorNum) {
        const sectorInfo = this.flashInfo.sectors[sectorNum];
        if (!sectorInfo) {
            throw new Error(`Invalid sector ${sectorNum}`);
        }

        await this.openocd.flashErase(sectorInfo.address, sectorInfo.size);
    }

    async eraseAddress(address, length) {
        await this.openocd.flashErase(address, length);
    }

    /**
     * Flash programming
     */
    async programFlash(file) {
        const ext = path.extname(file).toLowerCase();

        if (ext === '.hex') {
            await this.openocd.sendCommand(`program ${file} verify reset`);
        } else if (ext === '.bin') {
            // Need to specify address for .bin files
            await this.openocd.sendCommand(`program ${file} 0x08000000 verify reset`);
        } else if (ext === '.elf') {
            await this.openocd.sendCommand(`program ${file} verify reset`);
        } else {
            throw new Error(`Unsupported file format: ${ext}`);
        }
    }

    async programBinary(binFile, address = 0x08000000) {
        await this.openocd.sendCommand(`program ${binFile} ${address} verify reset`);
    }

    /**
     * Flash verification
     */
    async verifyFlash(file) {
        try {
            await this.openocd.sendCommand(`verify_image ${file}`);
            return true;
        } catch (error) {
            return false;
        }
    }

    async readFlash(address, length) {
        return await this.openocd.readMemory(address, Math.ceil(length / 4));
    }

    async compareFlash(address, expectedData) {
        const actual = await this.readFlash(address, expectedData.length);

        for (let i = 0; i < expectedData.length; i++) {
            const actualByte = actual[Math.floor(i / 4)].values[i % 4];
            if (actualByte !== expectedData[i]) {
                return false;
            }
        }

        return true;
    }

    /**
     * Option Bytes (STM32-specific, Keil has this!)
     */
    async readOptionBytes() {
        // STM32F4 option bytes at 0x1FFFC000
        const ob = await this.openocd.readMemory(0x1FFFC000, 4);

        return {
            RDP: (ob[0].values[0] >> 0) & 0xFF,    // Read protection
            USER: (ob[0].values[0] >> 8) & 0xFF,   // User option bytes
            nBOR: (ob[0].values[1] >> 0) & 0xFF,   // BOR level
            WRP: ob[1].values[0]                    // Write protection
        };
    }

    async writeOptionBytes(options) {
        // Unlock option bytes
        await this.openocd.writeMemory(0x40023C08, 0x08192A3B); // FLASH_OPTKEYR
        await this.openocd.writeMemory(0x40023C08, 0x4C5D6E7F);

        // Modify option bytes
        let optcr = 0;
        optcr |= (options.RDP & 0xFF) << 0;
        optcr |= (options.USER & 0xFF) << 8;
        optcr |= (options.nBOR & 0xFF) << 16;

        await this.openocd.writeMemory(0x40023C14, optcr); // FLASH_OPTCR

        // Start programming
        await this.openocd.writeMemory(0x40023C14, optcr | 0x02); // OPTSTRT bit

        // Wait for completion
        await this.waitFlashReady();

        // Lock option bytes
        await this.openocd.writeMemory(0x40023C14, optcr | 0x01); // OPTLOCK bit
    }

    async setReadProtection(level = 1) {
        // Level 0: No protection
        // Level 1: Memory read protection
        // Level 2: Chip read protection (IRREVERSIBLE!)

        const rdp = {
            0: 0xAA,
            1: 0x00,
            2: 0xCC
        }[level];

        if (rdp === undefined) {
            throw new Error('Invalid protection level');
        }

        if (level === 2) {
            throw new Error('Level 2 protection is PERMANENT! Use with extreme caution!');
        }

        const ob = await this.readOptionBytes();
        ob.RDP = rdp;
        await this.writeOptionBytes(ob);
    }

    async setWriteProtection(sectors) {
        const ob = await this.readOptionBytes();

        // Calculate WRP bits
        let wrp = 0xFFF; // All sectors writable
        for (const sector of sectors) {
            wrp &= ~(1 << sector); // Protect sector
        }

        ob.WRP = wrp;
        await this.writeOptionBytes(ob);
    }

    async disableWriteProtection() {
        const ob = await this.readOptionBytes();
        ob.WRP = 0xFFF; // All sectors writable
        await this.writeOptionBytes(ob);
    }

    /**
     * BOR (Brown-out Reset) configuration
     */
    async setBORLevel(level) {
        // Level 0: BOR off
        // Level 1: 2.1V
        // Level 2: 2.4V
        // Level 3: 2.7V

        const borLevels = {
            0: 0x0C,
            1: 0x08,
            2: 0x04,
            3: 0x00
        };

        const ob = await this.readOptionBytes();
        ob.nBOR = borLevels[level];
        await this.writeOptionBytes(ob);
    }

    /**
     * Boot configuration
     */
    async setBootMode(mode) {
        // mode: 'flash', 'system', 'sram'
        const bootModes = {
            'flash': 0x00, // Boot from main flash
            'system': 0x01, // Boot from system memory (bootloader)
            'sram': 0x03   // Boot from SRAM
        };

        const ob = await this.readOptionBytes();
        ob.USER = (ob.USER & 0xF0) | bootModes[mode];
        await this.writeOptionBytes(ob);
    }

    /**
     * Bootloader operations
     */
    async jumpToBootloader() {
        // Set SP and PC to bootloader values
        const bootloaderAddr = 0x1FFF0000; // STM32F4 system memory

        // Read bootloader stack pointer
        const sp = await this.openocd.readMemory(bootloaderAddr, 1);
        await this.openocd.writeRegister('sp', sp[0].values[0]);

        // Read bootloader entry point
        const pc = await this.openocd.readMemory(bootloaderAddr + 4, 1);
        await this.openocd.writeRegister('pc', pc[0].values[0]);

        // Resume
        await this.openocd.resume();
    }

    async writeBootloaderFlag(address = 0x2001FFF0, magic = 0xDEADBEEF) {
        // Write magic value to RAM for application bootloader
        await this.openocd.writeMemory(address, magic);
    }

    /**
     * Firmware update workflow
     */
    async updateFirmware(newFirmware, backup = true) {
        const backupFile = backup ? await this.backupFirmware() : null;

        try {
            // Program new firmware
            await this.programAndRun(newFirmware, true, false);

            return { success: true, backup: backupFile };
        } catch (error) {
            // Restore backup if update failed
            if (backupFile) {
                await this.programAndRun(backupFile, false, false);
            }

            return { success: false, error: error.message };
        }
    }

    async backupFirmware(outputFile = null) {
        if (!outputFile) {
            outputFile = `backup_${Date.now()}.bin`;
        }

        // Dump entire flash
        const flashSize = this.flashInfo.size || (512 * 1024); // Default 512KB
        await this.openocd.sendCommand(`dump_image ${outputFile} 0x08000000 ${flashSize}`);

        return outputFile;
    }

    /**
     * Flash protection status
     */
    async getProtectionStatus() {
        const ob = await this.readOptionBytes();

        return {
            readProtection: ob.RDP === 0xAA ? 'None' : (ob.RDP === 0xCC ? 'Level 2 (PERMANENT)' : 'Level 1'),
            writeProtectedSectors: this.getWriteProtectedSectors(ob.WRP),
            borLevel: this.getBORLevel(ob.nBOR),
            bootMode: this.getBootMode(ob.USER)
        };
    }

    getWriteProtectedSectors(wrp) {
        const protectedSectors = [];
        for (let i = 0; i < 12; i++) {
            if ((wrp & (1 << i)) === 0) {
                protectedSectors.push(i);
            }
        }
        return protectedSectors;
    }

    getBORLevel(nbor) {
        const levels = {
            0x0C: 'Off',
            0x08: '2.1V',
            0x04: '2.4V',
            0x00: '2.7V'
        };
        return levels[nbor] || 'Unknown';
    }

    getBootMode(user) {
        const boot = user & 0x03;
        const modes = {
            0x00: 'Main Flash',
            0x01: 'System Memory (Bootloader)',
            0x03: 'SRAM'
        };
        return modes[boot] || 'Unknown';
    }

    /**
     * Utility: Wait for flash ready
     */
    async waitFlashReady(timeout = 5000) {
        const startTime = Date.now();

        while (Date.now() - startTime < timeout) {
            const sr = await this.openocd.readMemory(0x40023C0C, 1); // FLASH_SR
            const bsy = sr[0].values[0] & 0x10000;

            if (!bsy) {
                return true;
            }

            await new Promise(resolve => setTimeout(resolve, 10));
        }

        throw new Error('Flash timeout');
    }
}

module.exports = FlashManager;
