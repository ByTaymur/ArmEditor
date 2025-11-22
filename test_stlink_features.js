const OpenSourceSTLink = require('./src/programmer/open-source-stlink');

async function testOpenSourceSTLink() {
    console.log('🧪 Testing Open Source ST-Link Wrapper...');
    const stlink = new OpenSourceSTLink();

    try {
        const isInstalled = await stlink.isInstalled();
        console.log(`📦 Installed: ${isInstalled ? '✅ Yes' : '❌ No'}`);

        if (isInstalled) {
            const version = await stlink.getVersion();
            console.log(`ℹ️ Version: ${version}`);

            console.log('🔍 Scanning for devices...');
            const devices = await stlink.listDevices();
            console.log(`📱 Devices Found: ${devices.length}`);
            devices.forEach(d => console.log(`   - ${d.name} (${d.serial})`));
        } else {
            console.log('⚠️ st-info not found. Please install stlink-tools.');
        }

    } catch (error) {
        console.error('❌ Test Failed:', error);
    }
}

testOpenSourceSTLink();
