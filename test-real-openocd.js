const OpenOCDInterface = require('./src/debugger/openocd-interface');
const STM32Tools = require('./src/stm32/stm32-tools');

async function testOpenOCD() {
    console.log('Starting OpenOCD isolation test...');
    const openocd = new OpenOCDInterface();

    openocd.on('output', (data) => {
        console.log('[OpenOCD Output]:', data.trim());
    });

    openocd.on('error', (err) => {
        console.error('[OpenOCD Error]:', err);
    });

    openocd.on('exit', (code) => {
        console.log('[OpenOCD Exit]:', code);
    });

    try {
        console.log('1. Starting OpenOCD (stm32f4x config)...');
        await openocd.start('stm32f4x', 'stlink');
        console.log('✅ OpenOCD started');

        console.log('2. Connecting TCL...');
        await openocd.connectTCL();
        console.log('✅ TCL connected');

        console.log('3. Reading Device Info...');
        const stm32Tools = new STM32Tools(openocd);
        const info = await stm32Tools.getDeviceInfo();
        console.log('✅ Device Info:', info);

        console.log('4. Stopping OpenOCD...');
        await openocd.stop();
        console.log('✅ OpenOCD stopped');

    } catch (error) {
        console.error('❌ Test Failed:', error);
        try {
            await openocd.stop();
        } catch (e) { }
    }
}

testOpenOCD();
