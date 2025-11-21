/**
 * MemoryManager - Handles memory layout and linker script generation
 */

const fs = require('fs');
const path = require('path');

class MemoryManager {
    constructor(device) {
        this.device = device;
        this.memoryMap = device.memoryMap;
    }

    /**
     * Generate linker script for device
     * @param {Object} config - Memory configuration
     * @returns {string} Linker script content
     */
    generateLinkerScript(config = {}) {
        const stackSize = config.stackSize || 0x400;
        const heapSize = config.heapSize || 0x200;

        return `/* Linker script for ${this.device.name} */

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Stack and heap sizes */
_Min_Heap_Size = ${heapSize};
_Min_Stack_Size = ${stackSize};

/* Memory Definitions */
MEMORY
{
${this.generateMemoryRegions()}
}

/* Sections */
SECTIONS
{
    /* Vector table */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >FLASH

    /* Program code and constants */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.glue_7)
        *(.glue_7t)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    /* Data section */
    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT> FLASH

    /* BSS section */
    .bss :
    {
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    } >RAM

    /* Heap and stack */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } >RAM
}
`;
    }

    /**
     * Generate memory region definitions
     * @private
     */
    generateMemoryRegions() {
        let regions = '';

        for (const [name, region] of Object.entries(this.memoryMap)) {
            const regionName = name.toUpperCase();
            const origin = region.start;
            const size = region.size;

            regions += `    ${regionName.padEnd(8)} (${this.getPermissions(name)}) : ORIGIN = ${origin}, LENGTH = ${size}\n`;
        }

        return regions;
    }

    /**
     * Get memory region permissions
     * @private
     */
    getPermissions(regionName) {
        if (regionName.toLowerCase().includes('flash')) {
            return 'rx';  // Read + Execute
        } else {
            return 'xrw'; // Execute + Read + Write
        }
    }

    /**
     * Get memory usage for a built project
     * @param {string} elfFile - Path to ELF file
     * @returns {Object} Memory usage statistics
     */
    async getMemoryUsage(elfFile) {
        // This would parse the ELF file to get actual memory usage
        // For now, return a placeholder
        return {
            flash: {
                used: 0,
                total: parseInt(this.memoryMap.flash.size, 16),
                percentage: 0
            },
            ram: {
                used: 0,
                total: parseInt(this.memoryMap.sram?.size || this.memoryMap.ram?.size || '0', 16),
                percentage: 0
            }
        };
    }

    /**
     * Validate memory configuration
     * @param {Object} config - Configuration to validate
     * @returns {Object} Validation result
     */
    validate(config) {
        const errors = [];
        const warnings = [];

        const stackSize = config.stackSize || 0;
        const heapSize = config.heapSize || 0;
        const ramSize = parseInt(this.memoryMap.ram?.size || this.memoryMap.sram?.size || '0', 16);

        if (stackSize + heapSize > ramSize) {
            errors.push('Stack + Heap size exceeds available RAM');
        }

        if (stackSize < 0x100) {
            warnings.push('Stack size is very small (< 256 bytes)');
        }

        return {
            valid: errors.length === 0,
            errors,
            warnings
        };
    }

    /**
     * Get memory map visualization data
     * @returns {Array} Memory sections for visualization
     */
    getVisualization() {
        const sections = [];

        for (const [name, region] of Object.entries(this.memoryMap)) {
            sections.push({
                name: name.toUpperCase(),
                start: region.start,
                size: parseInt(region.size, 16),
                color: this.getColorForRegion(name)
            });
        }

        return sections;
    }

    /**
     * Get color for memory region visualization
     * @private
     */
    getColorForRegion(name) {
        const colors = {
            flash: '#e74c3c',
            ram: '#3498db',
            sram: '#3498db',
            ccm: '#2ecc71',
            dtcm: '#f39c12'
        };
        return colors[name.toLowerCase()] || '#95a5a6';
    }
}

module.exports = MemoryManager;
