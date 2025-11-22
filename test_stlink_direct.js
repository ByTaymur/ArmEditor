const OpenSourceSTLink = require('./src/programmer/open-source-stlink');

async function testDirect() {
    console.log('Testing OpenSourceSTLink wrapper...\n');
    const stlink = new OpenSourceSTLink();

    try {
        console.log('1. Checking if installed...');
        const installed = await stlink.isInstalled();
        console.log(`   Result: ${installed}\n`);

        if (installed) {
            console.log('2. Getting version...');
            const version = await stlink.getVersion();
            console.log(`   Version: ${version}\n`);

            console.log('3. Listing devices...');
            const devices = await stlink.listDevices();
            console.log(`   Found ${devices.length} device(s):`);
            devices.forEach(d => {
                console.log(`   - ${JSON.stringify(d, null, 2)}`);
            });

            console.log('\n4. Getting device info...');
            const info = await stlink.getDeviceInfo();
            console.log(`   Info: ${JSON.stringify(info, null, 2)}`);
        }

    } catch (error) {
        console.error('ERROR:', error.message);
        console.error(error.stack);
    }
}

testDirect();
