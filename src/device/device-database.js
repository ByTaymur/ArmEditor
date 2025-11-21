/**
 * DeviceDatabase - Manages STM32 device specifications
 * Provides device information for project configuration
 */

const fs = require('fs');
const path = require('path');

class DeviceDatabase {
    constructor() {
        this.database = null;
        this.load();
    }

    /**
     * Load device database from JSON file
     */
    load() {
        const dbPath = path.join(__dirname, '../../data/devices/stm32-database.json');

        if (!fs.existsSync(dbPath)) {
            throw new Error('Device database not found');
        }

        const data = fs.readFileSync(dbPath, 'utf8');
        this.database = JSON.parse(data);
    }

    /**
     * Get all supported device families
     * @returns {Object} Family definitions
     */
    getFamilies() {
        return this.database.families;
    }

    /**
     * Get all devices or filter by family
     * @param {string} family - Optional family filter (e.g., "STM32F4")
     * @returns {Object} Device definitions
     */
    getDevices(family = null) {
        if (!family) {
            return this.database.devices;
        }

        const filtered = {};
        for (const [name, device] of Object.entries(this.database.devices)) {
            if (device.family === family) {
                filtered[name] = device;
            }
        }
        return filtered;
    }

    /**
     * Get device by exact name
     * @param {string} deviceName - Full device name (e.g., "STM32F407VGT6")
     * @returns {Object|null} Device specification
     */
    getDevice(deviceName) {
        return this.database.devices[deviceName] || null;
    }

    /**
     * Search devices by partial name
     * @param {string} query - Search query
     * @returns {Array} Matching devices
     */
    searchDevices(query) {
        const results = [];
        const queryLower = query.toLowerCase();

        for (const [name, device] of Object.entries(this.database.devices)) {
            if (name.toLowerCase().includes(queryLower)) {
                results.push({
                    name: name,
                    ...device
                });
            }
        }

        return results;
    }

    /**
     * Get memory map for device
     * @param {string} deviceName - Device name
     * @returns {Object} Memory regions
     */
    getMemoryMap(deviceName) {
        const device = this.getDevice(deviceName);
        return device ? device.memoryMap : null;
    }

    /**
     * Get SVD file path for device
     * @param {string} deviceName - Device name
     * @returns {string|null} SVD file name
     */
    getSVDFile(deviceName) {
        const device = this.getDevice(deviceName);
        return device ? device.svd : null;
    }

    /**
     * Get startup file for device
     * @param {string} deviceName - Device name
     * @returns {string|null} Startup file name
     */
    getStartupFile(deviceName) {
        const device = this.getDevice(deviceName);
        return device ? device.startupFile : null;
    }

    /**
     * Get linker script for device
     * @param {string} deviceName - Device name
     * @returns {string|null} Linker script name
     */
    getLinkerScript(deviceName) {
        const device = this.getDevice(deviceName);
        return device ? device.linkerScript : null;
    }

    /**
     * Get device features (FPU, DSP, etc.)
     * @param {string} deviceName - Device name
     * @returns {Array} Feature list
     */
    getFeatures(deviceName) {
        const device = this.getDevice(deviceName);
        return device ? (device.features || []) : [];
    }

    /**
     * Get compiler flags for device
     * @param {string} deviceName - Device name
     * @returns {Object} Compiler configuration
     */
    getCompilerFlags(deviceName) {
        const device = this.getDevice(deviceName);
        if (!device) return null;

        const flags = {
            cpu: this.getCPUFlag(device.core),
            fpu: this.getFPUFlag(device),
            defines: this.getDefines(deviceName)
        };

        return flags;
    }

    /**
     * Get CPU flag for core type
     * @private
     */
    getCPUFlag(core) {
        const cpuMap = {
            'Cortex-M0': '-mcpu=cortex-m0',
            'Cortex-M3': '-mcpu=cortex-m3',
            'Cortex-M4': '-mcpu=cortex-m4',
            'Cortex-M7': '-mcpu=cortex-m7'
        };
        return cpuMap[core] || '-mcpu=cortex-m4';
    }

    /**
     * Get FPU flags
     * @private
     */
    getFPUFlag(device) {
        if (device.features && device.features.includes('FPU')) {
            return {
                fpu: '-mfpu=fpv4-sp-d16',
                floatAbi: '-mfloat-abi=hard'
            };
        }
        return {
            fpu: '',
            floatAbi: '-mfloat-abi=soft'
        };
    }

    /**
     * Get preprocessor defines for device
     * @private
     */
    getDefines(deviceName) {
        const defines = ['USE_HAL_DRIVER'];

        // Add device-specific define (e.g., STM32F407xx)
        const match = deviceName.match(/STM32([A-Z]\d+)[A-Z]+/);
        if (match) {
            const baseDefine = `STM32${match[1]}xx`;
            defines.push(baseDefine);
        }

        return defines;
    }

    /**
     * Get device statistics
     * @returns {Object} Database stats
     */
    getStatistics() {
        const families = Object.keys(this.database.families);
        const devices = Object.keys(this.database.devices);

        const familyCounts = {};
        for (const device of Object.values(this.database.devices)) {
            familyCounts[device.family] = (familyCounts[device.family] || 0) + 1;
        }

        return {
            totalFamilies: families.length,
            totalDevices: devices.length,
            familyCounts: familyCounts
        };
    }
}

module.exports = DeviceDatabase;
