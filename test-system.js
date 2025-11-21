const { execSync } = require('child_process');
const os = require('os');
const fs = require('fs');
const path = require('path');

console.log("==================================================");
console.log("🖥️  SYSTEM DIAGNOSTICS");
console.log("==================================================");

// 1. OS Information
console.log(`\n[OS Info]`);
console.log(`Platform: ${os.platform()}`);
console.log(`Release: ${os.release()}`);
console.log(`Arch: ${os.arch()}`);
console.log(`CPUs: ${os.cpus().length}`);
console.log(`Memory: ${Math.round(os.totalmem() / 1024 / 1024 / 1024)} GB`);

// 2. Node.js Environment
console.log(`\n[Node.js Environment]`);
console.log(`Node Version: ${process.version}`);
console.log(`Path: ${process.execPath}`);

// 3. Check Dependencies
console.log(`\n[External Tools]`);

function checkCommand(name, cmd) {
    try {
        const output = execSync(cmd, { stdio: 'pipe' }).toString().trim().split('\n')[0];
        console.log(`✅ ${name}: Found (${output})`);
        return true;
    } catch (e) {
        console.log(`❌ ${name}: NOT FOUND`);
        return false;
    }
}

const tools = [
    { name: 'OpenOCD', cmd: 'openocd --version 2>&1' },
    { name: 'ARM GCC', cmd: 'arm-none-eabi-gcc --version' },
    { name: 'GDB', cmd: 'arm-none-eabi-gdb --version || gdb-multiarch --version' },
    { name: 'Make', cmd: 'make --version' },
    { name: 'Python 3', cmd: 'python3 --version' }
];

let allToolsFound = true;
for (const tool of tools) {
    if (!checkCommand(tool.name, tool.cmd)) {
        allToolsFound = false;
    }
}

// 4. Check Project Structure
console.log(`\n[Project Structure]`);
const requiredDirs = ['src', 'resources', 'node_modules'];
let structureOk = true;

for (const dir of requiredDirs) {
    if (fs.existsSync(path.join(__dirname, dir))) {
        console.log(`✅ ${dir}/ exists`);
    } else {
        console.log(`❌ ${dir}/ MISSING`);
        structureOk = false;
    }
}

console.log("\n==================================================");
if (allToolsFound && structureOk) {
    console.log("🎉 SYSTEM CHECK PASSED");
    process.exit(0);
} else {
    console.log("⚠️  SYSTEM CHECK FAILED - Missing dependencies");
    process.exit(1);
}
