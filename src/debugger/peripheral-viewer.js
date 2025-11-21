/**
 * PeripheralViewer - SVD-based peripheral register viewer
 */

const EventEmitter = require('events');
const SVDParser = require('../device/svd-parser');

class PeripheralViewer extends EventEmitter {
    constructor(gdbBackend, deviceName) {
        super();
        this.gdb = gdbBackend;
        this.deviceName = deviceName;
        this.svdParser = null;
        this.peripheralValues = new Map();

        try {
            this.svdParser = SVDParser.forDevice(deviceName);
        } catch (e) {
            console.warn('[PeripheralViewer] SVD not available:', e.message);
        }
    }

    /**
     * Get all available peripherals
     */
    getPeripherals() {
        if (!this.svdParser) return [];
        return this.svdParser.getAllPeripherals();
    }

    /**
     * Read peripheral registers
     */
    async readPeripheral(peripheralName) {
        if (!this.svdParser) {
            throw new Error('SVD parser not available');
        }

        const peripheral = this.svdParser.getPeripheral(peripheralName);
        if (!peripheral) {
            throw new Error(`Peripheral not found: ${peripheralName}`);
        }

        const values = {};
        const baseAddr = parseInt(peripheral.baseAddress, 16);

        for (const register of peripheral.registers) {
            const offset = parseInt(register.addressOffset, 16);
            const address = baseAddr + offset;

            try {
                const value = await this.readRegister(address);
                values[register.name] = {
                    value: value,
                    description: register.description,
                    access: register.access,
                    fields: register.fields ? this.parseFields(value, register.fields) : null
                };
            } catch (e) {
                console.error(`[PeripheralViewer] Failed to read ${register.name}:`, e);
                values[register.name] = { error: e.message };
            }
        }

        this.peripheralValues.set(peripheralName, values);
        this.emit('peripheral-read', { peripheral: peripheralName, values });

        return values;
    }

    /**
     * Read single register value
     * @private
     */
    async readRegister(address) {
        const cmd = `x/1xw 0x${address.toString(16)}`;
        const response = await this.gdb.sendCommand(cmd);
        const match = response.match(/0x[0-9a-fA-F]+:\s+0x([0-9a-fA-F]+)/);
        return match ? parseInt(match[1], 16) : 0;
    }

    /**
     * Write peripheral register
     */
    async writePeripheral(peripheralName, registerName, value) {
        if (!this.svdParser) {
            throw new Error('SVD parser not available');
        }

        const address = this.svdParser.getRegisterAddress(peripheralName, registerName);
        if (address === null) {
            throw new Error(`Register not found: ${peripheralName}.${registerName}`);
        }

        const cmd = `set {unsigned int}0x${address.toString(16)} = 0x${value.toString(16)}`;
        await this.gdb.sendCommand(cmd);

        // Re-read to confirm
        await this.readPeripheral(peripheralName);
    }

    /**
     * Parse register fields from value
     * @private
     */
    parseFields(value, fields) {
        if (!fields) return null;

        const parsed = {};
        for (const field of fields) {
            const mask = (1 << field.bitWidth) - 1;
            const fieldValue = (value >> field.bitOffset) & mask;

            parsed[field.name] = {
                value: fieldValue,
                description: field.description,
                bitOffset: field.bitOffset,
                bitWidth: field.bitWidth
            };
        }
        return parsed;
    }

    /**
     * Get peripheral tree structure for UI
     */
    getPeripheralTree() {
        const peripherals = this.getPeripherals();

        return peripherals.map(peripheral => ({
            name: peripheral.name,
            description: peripheral.description,
            baseAddress: peripheral.baseAddress,
            registers: peripheral.registers.map(reg => ({
                name: reg.name,
                description: reg.description,
                offset: reg.addressOffset,
                access: reg.access,
                hasFields: !!reg.fields
            }))
        }));
    }

    /**
     * Auto-refresh peripheral
     */
    startAutoRefresh(peripheralName, intervalMs = 1000) {
        const key = `refresh_${peripheralName}`;

        if (this[key]) {
            clearInterval(this[key]);
        }

        this[key] = setInterval(async () => {
            try {
                await this.readPeripheral(peripheralName);
            } catch (e) {
                // Ignore errors
            }
        }, intervalMs);
    }

    /**
     * Stop auto-refresh
     */
    stopAutoRefresh(peripheralName) {
        const key = `refresh_${peripheralName}`;
        if (this[key]) {
            clearInterval(this[key]);
            this[key] = null;
        }
    }

    /**
     * Get commonly used peripherals
     */
    getCommonPeripherals() {
        return ['GPIOA', 'GPIOB', 'GPIOC', 'GPIOD',
            'TIM2', 'TIM3', 'TIM4',
            'USART1', 'USART2', 'USART3',
            'SPI1', 'SPI2',
            'I2C1', 'I2C2',
            'ADC1', 'DAC'];
    }
}

module.exports = PeripheralViewer;
