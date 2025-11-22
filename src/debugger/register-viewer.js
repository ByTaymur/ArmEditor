/**
 * RegisterViewer - Display and modify CPU and peripheral registers
 */

const EventEmitter = require('events');

class RegisterViewer extends EventEmitter {
    constructor(gdbBackend) {
        super();
        this.gdb = gdbBackend;
        this.registers = new Map();
        this.peripheralRegisters = new Map();
    }

    /**
     * Read all CPU registers
     */
    async readCPURegisters() {
        if (!this.gdb || !this.gdb.isConnected) {
            throw new Error('GDB not connected');
        }

        try {
            // Use GDBBackend's robust MI implementation
            this.registers = await this.gdb.readRegisters();

            // Convert Map/Object if needed (gdb.readRegisters returns Object)
            if (!(this.registers instanceof Map)) {
                this.registers = new Map(Object.entries(this.registers));
            }

            this.emit('registers-updated', this.getRegisterSnapshot());
            return this.registers;
        } catch (error) {
            console.error('[RegisterViewer] Failed to read registers:', error);
            throw error;
        }
    }

    /**
     * Parse GDB register output (Deprecated - using MI now)
     * @private
     */
    parseRegisterOutput(output) {
        // Kept for compatibility if needed
        return new Map();
    }

    /**
     * Read specific register
     */
    async readRegister(name) {
        const response = await this.gdb.sendCommand(`info register ${name}`);
        const match = response.match(/0x[0-9a-fA-F]+/);
        return match ? parseInt(match[0], 16) : null;
    }

    /**
     * Write to register
     */
    async writeRegister(name, value) {
        const hexValue = typeof value === 'number'
            ? `0x${value.toString(16).toUpperCase()}`
            : value;

        await this.gdb.sendCommand(`set $${name} = ${hexValue}`);
        await this.readCPURegisters(); // Refresh
    }

    /**
     * Read peripheral register via memory read
     */
    async readPeripheralRegister(address) {
        const response = await this.gdb.sendCommand(`x/1xw ${address}`);
        const match = response.match(/0x[0-9a-fA-F]+:\s+0x([0-9a-fA-F]+)/);
        return match ? parseInt(match[1], 16) : null;
    }

    /**
     * Write peripheral register via memory write
     */
    async writePeripheralRegister(address, value) {
        const hexAddr = typeof address === 'number'
            ? `0x${address.toString(16).toUpperCase()}`
            : address;
        const hexValue = typeof value === 'number'
            ? `0x${value.toString(16).toUpperCase()}`
            : value;

        await this.gdb.sendCommand(`set {unsigned int}${hexAddr} = ${hexValue}`);
    }

    /**
     * Read peripheral registers from SVD definition
     */
    async readPeripheralFromSVD(peripheral, svdParser) {
        const peripheralDef = svdParser.getPeripheral(peripheral);
        if (!peripheralDef) {
            throw new Error(`Peripheral not found: ${peripheral}`);
        }

        const values = {};

        for (const register of peripheralDef.registers) {
            const address = svdParser.getRegisterAddress(peripheral, register.name);
            if (address !== null) {
                try {
                    const value = await this.readPeripheralRegister(`0x${address.toString(16)}`);
                    values[register.name] = {
                        value: value,
                        description: register.description,
                        access: register.access
                    };
                } catch (e) {
                    console.error(`Failed to read ${register.name}:`, e);
                }
            }
        }

        this.peripheralRegisters.set(peripheral, values);
        this.emit('peripheral-updated', { peripheral, values });

        return values;
    }

    /**
     * Get snapshot of all registers for UI
     */
    getRegisterSnapshot() {
        return {
            cpu: Object.fromEntries(this.registers),
            peripherals: Object.fromEntries(this.peripheralRegisters),
            timestamp: Date.now()
        };
    }

    /**
     * Auto-refresh registers at interval
     */
    startAutoRefresh(intervalMs = 1000) {
        if (this.refreshInterval) {
            clearInterval(this.refreshInterval);
        }

        this.refreshInterval = setInterval(async () => {
            try {
                await this.readCPURegisters();
            } catch (e) {
                // Ignore errors during auto-refresh
            }
        }, intervalMs);
    }

    /**
     * Stop auto-refresh
     */
    stopAutoRefresh() {
        if (this.refreshInterval) {
            clearInterval(this.refreshInterval);
            this.refreshInterval = null;
        }
    }

    /**
     * Get register groups for organized display
     */
    getRegisterGroups() {
        return {
            'General Purpose': ['r0', 'r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12'],
            'Special': ['sp', 'lr', 'pc'],
            'Status': ['cpsr', 'xpsr'],
            'Control': ['control', 'msp', 'psp']
        };
    }
}

module.exports = RegisterViewer;
