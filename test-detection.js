#!/usr/bin/env node

/**
 * Test STM32 Auto-Detection System
 */

const STM32Detector = require('./src/compiler/stm32-detector');

async function test() {
    console.log('🔍 STM32 Auto-Detection Test\n');
    console.log('━'.repeat(50));

    const detector = new STM32Detector();

    console.log('Scanning for connected STM32...\n');

    try {
        const result = await detector.detect();

        console.log('\n📊 Detection Results:');
        console.log('━'.repeat(50));

        if (result.success) {
            console.log('✅ Status:', 'SUCCESS');
            console.log('🎯 Chip:', result.chip.name);
            console.log('📋 Family:', result.chip.family);
            console.log('🔧 OpenOCD Target:', result.chip.target);
            console.log('🔌 IDCODE:', result.idcode);
            console.log('⚡ Voltage:', result.voltage ? result.voltage.toFixed(2) + 'V' : 'N/A');

            const config = detector.getOpenOCDConfig(result.chip);
            console.log('\n📝 OpenOCD Configuration:');
            console.log('  Interface:', config.interfaceConfig);
            console.log('  Target:', config.targetConfig);

            const flags = detector.getCompilerFlags(result.chip);
            console.log('\n💻 Compiler Flags:');
            console.log('  CPU:', flags.cpu);
            console.log('  FPU:', flags.fpu || 'none');
            console.log('  Defines:', flags.defines.join(', '));

        } else {
            console.log('❌ Status:', 'FAILED');
            console.log('💬 Message:', result.message);
            if (result.suggestion) {
                console.log('\n💡 Suggestion:');
                console.log(result.suggestion);
            }
        }

        console.log('\n' + '━'.repeat(50));

    } catch (error) {
        console.error('\n❌ Error:', error.message);
    }
}

test();
