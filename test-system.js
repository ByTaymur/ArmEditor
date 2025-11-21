#!/usr/bin/env node

/**
 * COMPREHENSIVE AUTO-DETECTION TEST
 * Tests the entire auto-detection system step by step
 */

const STM32Detector = require('./src/compiler/stm32-detector');
const { OpenOCDFlasher } = require('./src/compiler/arm-toolchain');

console.log('═'.repeat(70));
console.log('  🧪 AUTO-DETECTION SYSTEM - COMPREHENSIVE TEST');
console.log('═'.repeat(70));
console.log('');

async function runTests() {
    // TEST 1: STM32Detector Basic Detection
    console.log('📋 TEST 1: STM32Detector.detect()');
    console.log('─'.repeat(70));

    const detector = new STM32Detector();

    try {
        const result = await detector.detect();

        if (result.success) {
            console.log('✅ Detection: SUCCESS');
            console.log(`   Chip: ${result.chip.name}`);
            console.log(`   Family: ${result.chip.family}`);
            console.log(`   Series: ${result.chip.series}`);
            console.log(`   IDCODE: ${result.idcode}`);
            console.log(`   Target: ${result.chip.target}`);
            console.log(`   Interface: ${result.interface}`);
            console.log(`   Voltage: ${result.voltage ? result.voltage.toFixed(3) + 'V' : 'N/A'}`);

            // Get compiler flags
            const flags = detector.getCompilerFlags(result.chip);
            console.log(`   CPU: ${flags.cpu}`);
            console.log(`   FPU: ${flags.fpu || 'none'}`);
            console.log(`   Defines: ${flags.defines.join(', ')}`);

            console.log('');

            // TEST 2: OpenOCDFlasher Detection
            console.log('📋 TEST 2: OpenOCDFlasher.detectAndConfigure()');
            console.log('─'.repeat(70));

            const flasher = new OpenOCDFlasher({
                autoDetect: true
            });

            const config = await flasher.detectAndConfigure();

            if (config.success) {
                console.log('✅ Configuration: SUCCESS');
                console.log(`   Mode: ${config.mode}`);
                console.log(`   Chip: ${config.chip.name}`);
                console.log(`   Target: ${config.target}`);
                console.log(`   Message: ${config.message}`);

                if (config.compilerFlags) {
                    console.log('');
                    console.log('   📝 Recommended Compiler Flags:');
                    console.log(`      -mcpu=${config.compilerFlags.cpu}`);
                    if (config.compilerFlags.fpu) {
                        console.log(`      ${config.compilerFlags.fpu}`);
                    }
                    config.compilerFlags.defines.forEach(def => {
                        console.log(`      -D${def}`);
                    });
                }
            } else {
                console.log('❌ Configuration: FAILED');
                console.log(`   ${config.message}`);
            }

        } else {
            console.log('❌ Detection: FAILED');
            console.log(`   Message: ${result.message}`);

            if (result.suggestion) {
                console.log('');
                console.log('   💡 Suggestions:');
                result.suggestion.split('\n').forEach(line => {
                    if (line.trim()) console.log(`   ${line}`);
                });
            }
        }

    } catch (error) {
        console.log('❌ ERROR:', error.message);
        console.log('');
        console.log('Stack:', error.stack);
    }

    console.log('');
    console.log('═'.repeat(70));
    console.log('  TEST COMPLETE');
    console.log('═'.repeat(70));
}

runTests();
