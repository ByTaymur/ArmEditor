const FlashManager = require('./src/debugger/flash-manager');

console.log("==================================================");
console.log("⚡ FLASH MANAGER TEST");
console.log("==================================================");

// Mock OpenOCD Interface
class MockOpenOCD {
    constructor() {
        this.commands = [];
    }

    async halt() {
        console.log("[Mock] Target Halted");
    }

    async reset(halt) {
        console.log(`[Mock] Target Reset (Halt: ${halt})`);
    }

    async sendCommand(cmd, timeout) {
        console.log(`[Mock] Command: '${cmd}' (Timeout: ${timeout || 'default'})`);
        this.commands.push(cmd);
        return "OK";
    }

    async flashErase(address, length) {
        console.log(`[Mock] Erase: Addr 0x${address.toString(16)}, Len ${length}`);
    }

    async writeMemory(address, value) {
        console.log(`[Mock] Write Mem: 0x${address.toString(16)} = 0x${value.toString(16)}`);
    }

    async readMemory(address, count) {
        console.log(`[Mock] Read Mem: 0x${address.toString(16)}`);
        // Return dummy data for verification
        return [{ values: Array(count).fill(0xFF) }];
    }
}

async function runTest() {
    try {
        const mockOpenOCD = new MockOpenOCD();
        const flashManager = new FlashManager(mockOpenOCD);

        console.log("\nTesting programAndRun()...");
        const result = await flashManager.programAndRun('firmware.bin', true, true);

        console.log("\n[Result]");
        console.log(JSON.stringify(result, null, 2));

        // Verification
        let passed = true;

        // Check command sequence
        const expectedCommands = [
            'stm32f4x mass_erase 0', // from eraseFlash(false) -> wait, actually default is sector erase if not fullChip
            // Wait, let's check the logic in flash-manager.js
            // programAndRun calls eraseFlash() (no args -> fullChip=false) -> flashErase(0,0)
            // Then programFlash -> 'program firmware.bin 0x08000000' (for .bin)
            // Then verify_image
        ];

        // Check if critical commands were sent
        const cmdString = mockOpenOCD.commands.join('|');

        if (!cmdString.includes('program firmware.bin 0x08000000')) {
            console.log("❌ Program command missing");
            passed = false;
        }

        if (!cmdString.includes('verify_image firmware.bin')) {
            console.log("❌ Verify command missing");
            passed = false;
        }

        if (result.success && passed) {
            console.log("\n🎉 FLASH TEST PASSED");
            process.exit(0);
        } else {
            console.log("\n❌ FLASH TEST FAILED");
            process.exit(1);
        }

    } catch (error) {
        console.error("\n❌ TEST ERROR:", error);
        process.exit(1);
    }
}

runTest();
