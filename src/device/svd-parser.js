/**
 * SVDParser - Parse CMSIS-SVD files for peripheral definitions
 * SVD files describe microcontroller peripherals, registers, and bitfields
 */

const fs = require('fs');
const path = require('path');

class SVDParser {
    constructor(svdPath) {
        this.svdPath = svdPath;
        this.peripherals = new Map();
    }

    /**
     * Parse SVD XML file
     * NOTE: This is a simplified parser. Real implementation would use xml2js
     * @returns {Object} Parsed peripheral data
     */
    parse() {
        if (!fs.existsSync(this.svdPath)) {
            console.warn(`SVD file not found: ${this.svdPath}`);
            return this.getMockData();
        }

        // Real implementation would parse XML here
        // For now, return mock data
        return this.getMockData();
    }

    /**
     * Get mock peripheral data (placeholder for real SVD parsing)
     * @private
     */
    getMockData() {
        return {
            device: {
                name: 'STM32F407',
                version: '1.0',
                description: 'STM32F407 Device',
                addressUnitBits: 8,
                width: 32
            },
            peripherals: [
                {
                    name: 'GPIOA',
                    description: 'General-purpose I/Os',
                    baseAddress: '0x40020000',
                    registers: [
                        {
                            name: 'MODER',
                            description: 'GPIO port mode register',
                            addressOffset: '0x00',
                            size: 32,
                            access: 'read-write',
                            resetValue: '0xA8000000',
                            fields: [
                                {
                                    name: 'MODER0',
                                    description: 'Port x configuration bits (y = 0..15)',
                                    bitOffset: 0,
                                    bitWidth: 2
                                },
                                {
                                    name: 'MODER1',
                                    description: 'Port x configuration bits (y = 0..15)',
                                    bitOffset: 2,
                                    bitWidth: 2
                                }
                                // ... more fields
                            ]
                        },
                        {
                            name: 'ODR',
                            description: 'GPIO port output data register',
                            addressOffset: '0x14',
                            size: 32,
                            access: 'read-write',
                            resetValue: '0x00000000'
                        },
                        {
                            name: 'IDR',
                            description: 'GPIO port input data register',
                            addressOffset: '0x10',
                            size: 32,
                            access: 'read-only',
                            resetValue: '0x00000000'
                        }
                    ]
                },
                {
                    name: 'TIM2',
                    description: 'General-purpose timers',
                    baseAddress: '0x40000000',
                    registers: [
                        {
                            name: 'CR1',
                            description: 'control register 1',
                            addressOffset: '0x00',
                            size: 32,
                            access: 'read-write',
                            resetValue: '0x0000'
                        },
                        {
                            name: 'CNT',
                            description: 'counter',
                            addressOffset: '0x24',
                            size: 32,
                            access: 'read-write',
                            resetValue: '0x00000000'
                        }
                    ]
                },
                {
                    name: 'USART1',
                    description: 'Universal synchronous asynchronous receiver transmitter',
                    baseAddress: '0x40011000',
                    registers: [
                        {
                            name: 'SR',
                            description: 'Status register',
                            addressOffset: '0x00',
                            size: 32,
                            access: 'read-write',
                            resetValue: '0x00C00000'
                        },
                        {
                            name: 'DR',
                            description: 'Data register',
                            addressOffset: '0x04',
                            size: 32,
                            access: 'read-write',
                            resetValue: '0x00000000'
                        }
                    ]
                }
            ]
        };
    }

    /**
     * Get peripheral by name
     * @param {string} name - Peripheral name (e.g., "GPIOA")
     * @returns {Object|null} Peripheral definition
     */
    getPeripheral(name) {
        const data = this.parse();
        return data.peripherals.find(p => p.name === name) || null;
    }

    /**
     * Get all peripherals
     * @returns {Array} All peripheral definitions
     */
    getAllPeripherals() {
        const data = this.parse();
        return data.peripherals;
    }

    /**
     * Get register address
     * @param {string} peripheral - Peripheral name
     * @param {string} register - Register name
     * @returns {number|null} Register absolute address
     */
    getRegisterAddress(peripheral, register) {
        const p = this.getPeripheral(peripheral);
        if (!p) return null;

        const reg = p.registers.find(r => r.name === register);
        if (!reg) return null;

        const baseAddr = parseInt(p.baseAddress, 16);
        const offset = parseInt(reg.addressOffset, 16);
        return baseAddr + offset;
    }

    /**
     * Static method to load SVD for a device
     * @param {string} deviceName - Device name
     * @returns {SVDParser} Parser instance
     */
    static forDevice(deviceName) {
        const DeviceDatabase = require('./device-database');
        const db = new DeviceDatabase();
        const device = db.getDevice(deviceName);

        if (!device || !device.svd) {
            throw new Error(`No SVD file defined for ${deviceName}`);
        }

        const svdPath = path.join(__dirname, '../../data/svd', device.svd);
        return new SVDParser(svdPath);
    }
}

module.exports = SVDParser;
