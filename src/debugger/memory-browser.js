/**
 * MemoryBrowser - Read and write memory with hex viewer
 */

const EventEmitter = require('events');

class MemoryBrowser extends EventEmitter {
    constructor(gdbBackend) {
        super();
        this.gdb = gdbBackend;
        this.currentAddress = 0x08000000; // Default: Flash start
        this.viewSize = 256; // Bytes to display
        this.wordSize = 4; // 32-bit
    }

    /**
     * Read memory block
     * @param {number} address - Start address
     * @param {number} size - Number of bytes
     * @returns {Buffer} Memory data
     */
    async readMemory(address, size) {
        if (!this.gdb || !this.gdb.isConnected) {
            throw new Error('GDB not connected');
        }

        try {
            // GDB command: x/[length][format][size] address
            // Format: x=hex, size: b=byte, h=halfword, w=word
            const count = Math.ceil(size / this.wordSize);
            const cmd = `x/${count}xw 0x${address.toString(16)}`;

            const response = await this.gdb.sendCommand(cmd);
            const data = this.parseMemoryOutput(response, size);

            this.emit('memory-read', { address, size, data });
            return data;
        } catch (error) {
            console.error('[MemoryBrowser] Read failed:', error);
            throw error;
        }
    }

    /**
     * Parse GDB memory output
     * @private
     */
    parseMemoryOutput(output, size) {
        const buffer = Buffer.alloc(size);
        const lines = output.split('\n');
        let offset = 0;

        // Expected format: "0x08000000:  0x12345678  0xabcdef00"
        for (const line of lines) {
            const matches = line.matchAll(/0x([0-9a-fA-F]{8})/g);
            for (const match of matches) {
                if (offset < size) {
                    const value = parseInt(match[1], 16);
                    // Write as little-endian 32-bit
                    buffer.writeUInt32LE(value, offset);
                    offset += 4;
                }
            }
        }

        return buffer;
    }

    /**
     * Write memory
     * @param {number} address - Write address
     * @param {Buffer|Array} data - Data to write
     */
    async writeMemory(address, data) {
        if (!this.gdb || !this.gdb.isConnected) {
            throw new Error('GDB not connected');
        }

        const buffer = Buffer.isBuffer(data) ? data : Buffer.from(data);

        try {
            // Write 32-bit words
            for (let i = 0; i < buffer.length; i += 4) {
                const addr = address + i;
                const value = buffer.readUInt32LE(i);
                const cmd = `set {unsigned int}0x${addr.toString(16)} = 0x${value.toString(16)}`;
                await this.gdb.sendCommand(cmd);
            }

            this.emit('memory-written', { address, size: buffer.length });
        } catch (error) {
            console.error('[MemoryBrowser] Write failed:', error);
            throw error;
        }
    }

    /**
     * Read byte at address
     */
    async readByte(address) {
        const cmd = `x/1xb 0x${address.toString(16)}`;
        const response = await this.gdb.sendCommand(cmd);
        const match = response.match(/0x[0-9a-fA-F]+:\s+0x([0-9a-fA-F]{2})/);
        return match ? parseInt(match[1], 16) : null;
    }

    /**
     * Read word (32-bit) at address
     */
    async readWord(address) {
        const cmd = `x/1xw 0x${address.toString(16)}`;
        const response = await this.gdb.sendCommand(cmd);
        const match = response.match(/0x[0-9a-fA-F]+:\s+0x([0-9a-fA-F]+)/);
        return match ? parseInt(match[1], 16) : null;
    }

    /**
     * Format memory for hex viewer display
     * @param {Buffer} data - Memory data
     * @param {number} startAddress - Start address
     * @returns {Array} Formatted lines
     */
    formatHexView(data, startAddress) {
        const lines = [];
        const bytesPerLine = 16;

        for (let i = 0; i < data.length; i += bytesPerLine) {
            const address = startAddress + i;
            const chunk = data.slice(i, i + bytesPerLine);

            // Hex bytes
            const hex = Array.from(chunk)
                .map(b => b.toString(16).padStart(2, '0').toUpperCase())
                .join(' ');

            // ASCII representation
            const ascii = Array.from(chunk)
                .map(b => (b >= 32 && b < 127) ? String.fromCharCode(b) : '.')
                .join('');

            lines.push({
                address: `0x${address.toString(16).toUpperCase().padStart(8, '0')}`,
                hex: hex.padEnd(bytesPerLine * 3 - 1, ' '),
                ascii: ascii.padEnd(bytesPerLine, ' ')
            });
        }

        return lines;
    }

    /**
     * Search for pattern in memory
     * @param {number} startAddress - Search start
     * @param {number} endAddress - Search end
     * @param {Array} pattern - Byte pattern to find
     * @returns {Array} Addresses where pattern found
     */
    async searchMemory(startAddress, endAddress, pattern) {
        const results = [];
        const chunkSize = 1024;

        for (let addr = startAddress; addr < endAddress; addr += chunkSize) {
            const size = Math.min(chunkSize, endAddress - addr);
            const data = await this.readMemory(addr, size);

            // Search for pattern
            for (let i = 0; i <= data.length - pattern.length; i++) {
                let match = true;
                for (let j = 0; j < pattern.length; j++) {
                    if (data[i + j] !== pattern[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    results.push(addr + i);
                }
            }
        }

        return results;
    }

    /**
     * Compare memory regions
     * @param {number} addr1 - First address
     * @param {number} addr2 - Second address  
     * @param {number} size - Size to compare
     * @returns {Array} Differences
     */
    async compareMemory(addr1, addr2, size) {
        const data1 = await this.readMemory(addr1, size);
        const data2 = await this.readMemory(addr2, size);

        const differences = [];
        for (let i = 0; i < size; i++) {
            if (data1[i] !== data2[i]) {
                differences.push({
                    offset: i,
                    address1: addr1 + i,
                    address2: addr2 + i,
                    value1: data1[i],
                    value2: data2[i]
                });
            }
        }

        return differences;
    }

    /**
     * Fill memory with pattern
     * @param {number} address - Start address
     * @param {number} size - Size to fill
     * @param {number} pattern - Byte pattern
     */
    async fillMemory(address, size, pattern = 0x00) {
        const buffer = Buffer.alloc(size, pattern);
        await this.writeMemory(address, buffer);
    }
}

module.exports = MemoryBrowser;
