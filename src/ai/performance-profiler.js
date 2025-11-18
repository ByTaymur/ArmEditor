#!/usr/bin/env node
/**
 * Performance Profiler for ARM Cortex-M
 * Analyzes execution time, cycle counts, and hotspots
 */

const fs = require('fs');
const { execSync } = require('child_process');

class PerformanceProfiler {
    constructor(elfFile) {
        this.elfFile = elfFile;
        this.functions = [];
        this.hotspots = [];
        this.cycleEstimates = new Map();
    }

    /**
     * Profile application
     */
    profile() {
        console.log('⚡ Performance Profiling\n');
        console.log('='.repeat(60));

        // Analyze functions
        this.analyzeFunctions();

        // Estimate cycles
        this.estimateCycles();

        // Find hotspots
        this.findHotspots();

        // Generate optimization suggestions
        this.suggestOptimizations();

        console.log('\n' + '='.repeat(60));
    }

    /**
     * Analyze all functions
     */
    analyzeFunctions() {
        console.log('\n📊 FUNCTION ANALYSIS:');

        try {
            const output = execSync(`arm-none-eabi-nm -S ${this.elfFile}`).toString();
            const lines = output.split('\n');

            for (const line of lines) {
                const match = line.match(/([0-9a-f]+)\s+([0-9a-f]+)\s+T\s+(.+)/);
                if (match) {
                    const func = {
                        address: parseInt(match[1], 16),
                        size: parseInt(match[2], 16),
                        name: match[3]
                    };
                    this.functions.push(func);
                }
            }

            // Sort by size (largest first)
            this.functions.sort((a, b) => b.size - a.size);

            console.log(`\n  Top 10 largest functions:`);
            this.functions.slice(0, 10).forEach((f, i) => {
                console.log(`  ${i + 1}. ${f.name.padEnd(30)} ${f.size} bytes`);
            });

        } catch (err) {
            console.error('Function analysis failed:', err.message);
        }
    }

    /**
     * Estimate cycle counts
     */
    estimateCycles() {
        console.log('\n⏱️  CYCLE ESTIMATION:');

        try {
            const disasm = execSync(`arm-none-eabi-objdump -d ${this.elfFile}`).toString();

            // Instruction cycle costs (Cortex-M4)
            const cycleCosts = {
                'ldr': 2,    // Load
                'str': 2,    // Store
                'push': 1,   // Push
                'pop': 1,    // Pop
                'add': 1,    // Add
                'sub': 1,    // Subtract
                'mul': 1,    // Multiply (single cycle on M4)
                'div': 12,   // Divide (slow!)
                'bl': 3,     // Branch with link
                'b': 1,      // Branch
                'cmp': 1,    // Compare
                'mov': 1     // Move
            };

            // Parse disassembly
            const instructions = disasm.match(/\t[a-z]+/g) || [];
            const instructionCounts = {};

            for (const inst of instructions) {
                const instr = inst.trim();
                instructionCounts[instr] = (instructionCounts[instr] || 0) + 1;
            }

            // Calculate total cycles
            let totalCycles = 0;
            console.log('\n  Instruction breakdown:');

            for (const [instr, count] of Object.entries(instructionCounts)) {
                const cycles = cycleCosts[instr] || 1;
                const totalInstrCycles = count * cycles;
                totalCycles += totalInstrCycles;

                if (count > 10) {  // Only show significant instructions
                    console.log(`    ${instr.padEnd(10)} ${count.toString().padStart(6)} x ${cycles} = ${totalInstrCycles} cycles`);
                }
            }

            console.log(`\n  Estimated total cycles: ${totalCycles.toLocaleString()}`);

            // At 168 MHz
            const timeUs = (totalCycles / 168).toFixed(2);
            console.log(`  Estimated time @ 168 MHz: ${timeUs} µs`);

        } catch (err) {
            console.error('Cycle estimation failed:', err.message);
        }
    }

    /**
     * Find performance hotspots
     */
    findHotspots() {
        console.log('\n🔥 PERFORMANCE HOTSPOTS:');

        // Analyze disassembly for problematic patterns
        try {
            const disasm = execSync(`arm-none-eabi-objdump -d ${this.elfFile}`).toString();

            // Find divisions
            const divisions = (disasm.match(/\tudiv/g) || []).length;
            const sdivisions = (disasm.match(/\tsdiv/g) || []).length;

            if (divisions + sdivisions > 0) {
                console.log(`\n  ⚠️  Division operations: ${divisions + sdivisions}`);
                console.log(`     Divisions take 12 cycles on Cortex-M4`);
                console.log(`     Consider: Multiply by reciprocal or bit shifts`);
                this.hotspots.push({
                    type: 'division',
                    count: divisions + sdivisions,
                    impact: 'high'
                });
            }

            // Find modulo operations
            const modulos = (disasm.match(/%/g) || []).length;
            if (modulos > 10) {
                console.log(`\n  ⚠️  Modulo operations: ${modulos}`);
                console.log(`     Modulo is implemented as division`);
                console.log(`     Consider: Bitwise AND for powers of 2`);
                this.hotspots.push({
                    type: 'modulo',
                    count: modulos,
                    impact: 'medium'
                });
            }

            // Find loops
            const loops = (disasm.match(/\tb\.w\s+[0-9a-f]+\s+</g) || []).length;
            console.log(`\n  🔄 Loop count: ${loops}`);

            // Find function calls
            const calls = (disasm.match(/\tbl\s+/g) || []).length;
            console.log(`  📞 Function calls: ${calls}`);

            if (calls > 100) {
                console.log(`     Consider: Inline small frequently-called functions`);
                this.hotspots.push({
                    type: 'function_calls',
                    count: calls,
                    impact: 'low'
                });
            }

            if (this.hotspots.length === 0) {
                console.log('\n  ✅ No major hotspots detected!');
            }

        } catch (err) {
            console.error('Hotspot analysis failed:', err.message);
        }
    }

    /**
     * Suggest optimizations
     */
    suggestOptimizations() {
        console.log('\n💡 OPTIMIZATION SUGGESTIONS:');

        const suggestions = [];

        // Check optimization level
        try {
            const objdump = execSync(`arm-none-eabi-objdump -h ${this.elfFile}`).toString();

            // Check if debug symbols present
            if (objdump.includes('.debug')) {
                suggestions.push({
                    priority: 'medium',
                    suggestion: 'Remove debug symbols for production',
                    command: 'arm-none-eabi-strip <file.elf>'
                });
            }

        } catch (err) {
            // Ignore
        }

        // Check large functions
        const largeFunctions = this.functions.filter(f => f.size > 1000);
        if (largeFunctions.length > 0) {
            suggestions.push({
                priority: 'low',
                suggestion: `${largeFunctions.length} functions > 1KB`,
                detail: 'Consider splitting large functions for better cache usage'
            });
        }

        // Hotspot-based suggestions
        for (const hotspot of this.hotspots) {
            if (hotspot.type === 'division') {
                suggestions.push({
                    priority: 'high',
                    suggestion: 'Replace divisions with shifts',
                    detail: 'x / 4 → x >> 2, saves ~10 cycles per division'
                });
            }

            if (hotspot.type === 'function_calls' && hotspot.count > 100) {
                suggestions.push({
                    priority: 'medium',
                    suggestion: 'Use inline functions',
                    detail: 'inline keyword can eliminate function call overhead'
                });
            }
        }

        // Compiler flags
        suggestions.push({
            priority: 'high',
            suggestion: 'Use -O2 or -O3 for release',
            detail: 'Enables aggressive optimizations'
        });

        suggestions.push({
            priority: 'medium',
            suggestion: 'Enable LTO (Link-Time Optimization)',
            detail: 'CFLAGS += -flto'
        });

        suggestions.push({
            priority: 'low',
            suggestion: 'Use -ffunction-sections -fdata-sections',
            detail: 'Allows linker to remove unused code (--gc-sections)'
        });

        // Print suggestions
        suggestions.forEach((s, i) => {
            console.log(`\n  ${i + 1}. [${s.priority.toUpperCase()}] ${s.suggestion}`);
            if (s.detail) {
                console.log(`     ${s.detail}`);
            }
            if (s.command) {
                console.log(`     Command: ${s.command}`);
            }
        });
    }

    /**
     * Compare two builds
     */
    compare(otherElf) {
        console.log('\n📊 BUILD COMPARISON:');

        try {
            const size1 = execSync(`arm-none-eabi-size ${this.elfFile}`).toString();
            const size2 = execSync(`arm-none-eabi-size ${otherElf}`).toString();

            console.log('\n  Current build:');
            console.log(size1);

            console.log('  Comparing to:');
            console.log(size2);

        } catch (err) {
            console.error('Comparison failed:', err.message);
        }
    }
}

// CLI usage
if (require.main === module) {
    const elfFile = process.argv[2];

    if (!elfFile) {
        console.log('Usage: node performance-profiler.js <file.elf>');
        console.log('\nOptional: Compare two builds');
        console.log('  node performance-profiler.js <new.elf> <old.elf>');
        process.exit(1);
    }

    const profiler = new PerformanceProfiler(elfFile);
    profiler.profile();

    // Compare if second file provided
    const compareElf = process.argv[3];
    if (compareElf && fs.existsSync(compareElf)) {
        profiler.compare(compareElf);
    }
}

module.exports = PerformanceProfiler;
