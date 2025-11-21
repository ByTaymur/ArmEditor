const STM32Tools = require('./src/stm32/stm32-tools');

console.log("==================================================");
console.log("🔍 STM32 DETECTION TEST");
console.log("==================================================");

// Mock OpenOCD Interface
class MockOpenOCD {
    constructor() {
        this.connected = true;
        console.log("[Mock] OpenOCD Initialized");
    }

    async readMemory(address, count, width = 32) {
        console.log(`[Mock] Read Memory: 0x${address.toString(16).toUpperCase()} (Count: ${count}, Width: ${width})`);

        // Simulate STM32F407 Response
        if (address === 0xE0042000) { // DBGMCU_IDCODE
            // DevID: 0x413 (STM32F405/407), RevID: 0x1000 (Rev A)
            return [{ values: [0x10006413] }];
        }

        if (address === 0x1FFF7A10) { // Unique ID (96-bit)
            // Random UID
            return [
                { values: [0x00350042] }, // UID0
                { values: [0x30345115] }, // UID1
                { values: [0x30345115] }  // UID2
            ];
        }

        if (address === 0x1FFF7A22) { // Flash Size
            // 1024 KB
            return [{ values: [1024] }];
        }

        return [{ values: Array(count).fill(0) }];
    }
}

async function runTest() {
    try {
        const mockOpenOCD = new MockOpenOCD();
        const tools = new STM32Tools(mockOpenOCD);

        console.log("\nTesting getDeviceInfo()...");
        const info = await tools.getDeviceInfo();

        console.log("\n[Result]");
        console.log(JSON.stringify(info, null, 2));

        // Verification
        let passed = true;
        if (info.deviceID !== '0x413') {
            console.log("❌ Device ID mismatch");
            passed = false;
        }
        if (info.deviceName !== 'STM32F405/407/415/417') {
            console.log("❌ Device Name mismatch");
            passed = false;
        }
        if (info.flash.size !== 1024) {
            console.log("❌ Flash Size mismatch");
            passed = false;
        }

        if (passed) {
            console.log("\n🎉 DETECTION TEST PASSED");
            process.exit(0);
        } else {
            console.log("\n❌ DETECTION TEST FAILED");
            process.exit(1);
        }

    } catch (error) {
        console.error("\n❌ TEST ERROR:", error);
        process.exit(1);
    }
}

runTest();
