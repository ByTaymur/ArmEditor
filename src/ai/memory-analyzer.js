#!/usr/bin/env node
/**
 * Memory Leak & Stack Overflow Detector
 * Analyzes ARM binaries for memory issues
 */

const fs = require('fs');
const { execSync } = require('child_process');

class MemoryAnalyzer {
    constructor(elfFile) {
        this.elfFile = elfFile;
        this.symbols = [];
        this.stackUsage = new Map();
        this.heapUsage = new Map();
    }

    /**
     * Analyze ELF file
     */
    analyze() {
        console.log('🔍 Analyzing memory usage...\n');

        // Get symbols
        this.loadSymbols();

        // Analyze stack
        this.analyzeStack();

        // Analyze heap
        this.analyzeHeap();

        // Analyze data sections
        this.analyzeDataSections();

        // Generate report
        return this.generateReport();
    }

    /**
     * Load symbols from ELF
     */
    loadSymbols() {
        try {
            const output = execSync(`arm-none-eabi-nm -S -l ${this.elfFile}`).toString();
            const lines = output.split('\n');

            for (const line of lines) {
                const match = line.match(/([0-9a-f]+)\s+([0-9a-f]+)\s+([A-Z])\s+(.+)/);
                if (match) {
                    this.symbols.push({
                        address: parseInt(match[1], 16),
                        size: parseInt(match[2], 16),
                        type: match[3],
                        name: match[4]
                    });
                }
            }

            console.log(`📋 Loaded ${this.symbols.length} symbols`);
        } catch (err) {
            console.error('Failed to load symbols:', err.message);
        }
    }

    /**
     * Analyze stack usage
     */
    analyzeStack() {
        console.log('\n📊 STACK ANALYSIS:');

        try {
            // Get stack usage from compiler
            const output = execSync(`arm-none-eabi-objdump -d ${this.elfFile}`).toString();

            // Find stack allocation patterns
            const stackPattern = /sub\s+sp,\s*#(\d+)/g;
            let match;
            let maxStackFrame = 0;
            let totalStack = 0;

            while ((match = stackPattern.exec(output)) !== null) {
                const size = parseInt(match[1]);
                totalStack += size;
                if (size > maxStackFrame) {
                    maxStackFrame = size;
                }
            }

            console.log(`  Total stack allocation: ${totalStack} bytes`);
            console.log(`  Max stack frame: ${maxStackFrame} bytes`);

            // Check for large arrays
            const largeBssSymbols = this.symbols.filter(s => s.type === 'B' && s.size > 1024);
            if (largeBssSymbols.length > 0) {
                console.log('\n  ⚠️  Large BSS sections (potential stack issue):');
                largeBssSymbols.forEach(s => {
                    console.log(`    ${s.name}: ${s.size} bytes`);
                });
            }

            // Estimate total stack need
            const estimatedStack = totalStack + 1024; // Add buffer for interrupts
            console.log(`\n  📏 Estimated stack need: ${estimatedStack} bytes`);

            // Check stack size from linker script
            this.checkStackSize(estimatedStack);

        } catch (err) {
            console.error('Stack analysis failed:', err.message);
        }
    }

    /**
     * Check configured stack size
     */
    checkStackSize(needed) {
        try {
            // Get stack size from ELF
            const output = execSync(`arm-none-eabi-readelf -s ${this.elfFile}`).toString();
            const stackMatch = output.match(/_Min_Stack_Size.*?(\d+)/);

            if (stackMatch) {
                const configured = parseInt(stackMatch[1], 16);
                console.log(`  Configured stack: ${configured} bytes`);

                if (needed > configured) {
                    console.log(`  ❌ STACK TOO SMALL! Need at least ${needed} bytes`);
                } else {
                    console.log(`  ✅ Stack size OK (margin: ${configured - needed} bytes)`);
                }
            }
        } catch (err) {
            // Ignore
        }
    }

    /**
     * Analyze heap usage
     */
    analyzeHeap() {
        console.log('\n💾 HEAP ANALYSIS:');

        // Find malloc/free calls
        const mallocSymbols = this.symbols.filter(s =>
            s.name.includes('malloc') ||
            s.name.includes('calloc') ||
            s.name.includes('realloc') ||
            s.name.includes('free')
        );

        if (mallocSymbols.length === 0) {
            console.log('  ✅ No dynamic memory allocation detected');
        } else {
            console.log(`  ⚠️  Found ${mallocSymbols.length} heap functions:`);
            mallocSymbols.forEach(s => {
                console.log(`    ${s.name} at 0x${s.address.toString(16)}`);
            });
            console.log('\n  💡 Recommendation: Avoid dynamic allocation in embedded systems');
        }
    }

    /**
     * Analyze data sections
     */
    analyzeDataSections() {
        console.log('\n📦 SECTION SIZES:');

        try {
            const output = execSync(`arm-none-eabi-size -A ${this.elfFile}`).toString();
            console.log(output);

            // Parse sections
            const textMatch = output.match(/\.text\s+(\d+)/);
            const dataMatch = output.match(/\.data\s+(\d+)/);
            const bssMatch = output.match(/\.bss\s+(\d+)/);

            if (textMatch && dataMatch && bssMatch) {
                const text = parseInt(textMatch[1]);
                const data = parseInt(dataMatch[1]);
                const bss = parseInt(bssMatch[1]);

                const total = text + data + bss;
                const flash = text + data;
                const ram = data + bss;

                console.log('Summary:');
                console.log(`  Flash: ${flash} bytes (${(flash / 1024).toFixed(2)} KB)`);
                console.log(`  RAM:   ${ram} bytes (${(ram / 1024).toFixed(2)} KB)`);
                console.log(`  Total: ${total} bytes (${(total / 1024).toFixed(2)} KB)`);
            }

        } catch (err) {
            console.error('Section analysis failed:', err.message);
        }
    }

    /**
     * Detect memory leaks (static analysis)
     */
    detectLeaks(sourceCode) {
        console.log('\n🔍 LEAK DETECTION:');

        const leaks = [];

        // Find malloc without free
        const mallocPattern = /(\w+)\s*=\s*(malloc|calloc)\s*\(/g;
        const freePattern = /free\s*\((\w+)\)/g;

        const allocations = new Set();
        let match;

        while ((match = mallocPattern.exec(sourceCode)) !== null) {
            allocations.add(match[1]);
        }

        while ((match = freePattern.exec(sourceCode)) !== null) {
            allocations.delete(match[1]);
        }

        if (allocations.size > 0) {
            console.log(`  ⚠️  Potential memory leaks:`);
            allocations.forEach(var_name => {
                console.log(`    Variable '${var_name}' allocated but not freed`);
                leaks.push({
                    variable: var_name,
                    type: 'leak',
                    severity: 'high'
                });
            });
        } else {
            console.log('  ✅ No obvious memory leaks detected');
        }

        return leaks;
    }

    /**
     * Detect buffer overflows
     */
    detectBufferOverflows(sourceCode) {
        console.log('\n🛡️  BUFFER OVERFLOW CHECK:');

        const issues = [];

        // Dangerous functions
        const dangerous = [
            { func: 'strcpy', safe: 'strncpy' },
            { func: 'sprintf', safe: 'snprintf' },
            { func: 'gets', safe: 'fgets' },
            { func: 'scanf', safe: 'fscanf with width' }
        ];

        for (const { func, safe } of dangerous) {
            const regex = new RegExp(`\\b${func}\\s*\\(`, 'g');
            const matches = sourceCode.match(regex);

            if (matches) {
                console.log(`  ⚠️  Found ${matches.length} uses of ${func}()`);
                console.log(`     Recommendation: Use ${safe} instead`);
                issues.push({
                    function: func,
                    count: matches.length,
                    safe: safe,
                    severity: 'high'
                });
            }
        }

        if (issues.length === 0) {
            console.log('  ✅ No dangerous functions detected');
        }

        return issues;
    }

    /**
     * Generate full report
     */
    generateReport() {
        return {
            symbols: this.symbols.length,
            stack: this.stackUsage,
            heap: this.heapUsage,
            timestamp: new Date().toISOString()
        };
    }
}

// CLI usage
if (require.main === module) {
    const elfFile = process.argv[2];

    if (!elfFile) {
        console.log('Usage: node memory-analyzer.js <file.elf>');
        console.log('\nOptional: Analyze source code');
        console.log('  node memory-analyzer.js <file.elf> <main.c>');
        process.exit(1);
    }

    const analyzer = new MemoryAnalyzer(elfFile);
    analyzer.analyze();

    // Analyze source code if provided
    const sourceFile = process.argv[3];
    if (sourceFile && fs.existsSync(sourceFile)) {
        console.log('\n' + '='.repeat(60));
        console.log('SOURCE CODE ANALYSIS');
        console.log('='.repeat(60));

        const sourceCode = fs.readFileSync(sourceFile, 'utf-8');
        analyzer.detectLeaks(sourceCode);
        analyzer.detectBufferOverflows(sourceCode);
    }

    console.log('\n✅ Analysis complete!');
}

module.exports = MemoryAnalyzer;
