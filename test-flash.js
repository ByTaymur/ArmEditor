#!/usr/bin/env node

/**
 * Test Flash Operation with Auto-Detection
 */

const { OpenOCDFlasher } = require('./src/compiler/arm-toolchain');
const path = require('path');

async function testFlash() {
    console.log('⚡ Flash Test with Auto-Detection\n');
    console.log('━'.repeat(60));

    // Create flasher with auto-detection
    const flasher = new OpenOCDFlasher({
        autoDetect: true,
        timeout: 30000
    });

    console.log('\n🔍 Attempting to detect and flash...\n');

    try {
        // Try to flash an example .elf file (if exists)
        const elfFile = path.join(__dirname, 'examples/blink-led/build/blink-led.elf');

        await flasher.flash(elfFile, (type, text) => {
            process.stdout.write(text);
        });

        console.log('\n✅ Flash completed successfully!');

    } catch (error) {
        console.error('\n❌ Flash failed:', error.message);
        console.log('\nℹ️  This is expected if:');
        console.log('  - STLink is not connected');
        console.log('  - No .elf file exists');
        console.log('  - Target board is not powered');
    }

    console.log('\n' + '━'.repeat(60));
}

testFlash();
