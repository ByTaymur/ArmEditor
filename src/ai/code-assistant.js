#!/usr/bin/env node
/**
 * AI-Powered Code Assistant for ArmEditor
 * Features:
 * - Code completion
 * - Bug detection
 * - Performance suggestions
 * - Documentation generation
 * - Code review
 */

const fs = require('fs');
const path = require('path');

class AICodeAssistant {
    constructor() {
        this.knowledgeBase = this.loadKnowledgeBase();
        this.bugPatterns = this.loadBugPatterns();
        this.performanceRules = this.loadPerformanceRules();
    }

    /**
     * Load ARM/STM32 knowledge base
     */
    loadKnowledgeBase() {
        return {
            registers: {
                'GPIOD': {
                    address: '0x40020C00',
                    registers: ['MODER', 'OTYPER', 'OSPEEDR', 'PUPDR', 'IDR', 'ODR', 'BSRR', 'LCKR', 'AFR']
                },
                'RCC': {
                    address: '0x40023800',
                    registers: ['CR', 'PLLCFGR', 'CFGR', 'CIR', 'AHB1ENR', 'APB1ENR', 'APB2ENR']
                },
                'TIM1': {
                    address: '0x40010000',
                    registers: ['CR1', 'CR2', 'SMCR', 'DIER', 'SR', 'EGR', 'CCMR1', 'CCMR2', 'CCER', 'CNT', 'PSC', 'ARR']
                }
            },
            peripherals: {
                'GPIO': {
                    clock: 'RCC_AHB1ENR',
                    example: 'RCC_AHB1ENR |= (1 << 3); // Enable GPIOD'
                },
                'TIM': {
                    clock: 'RCC_APB1ENR or RCC_APB2ENR',
                    example: 'RCC_APB1ENR |= (1 << 0); // Enable TIM2'
                },
                'USART': {
                    clock: 'RCC_APB1ENR or RCC_APB2ENR',
                    example: 'RCC_APB2ENR |= (1 << 4); // Enable USART1'
                }
            },
            commonPatterns: {
                'led_blink': {
                    description: 'LED blinking pattern',
                    code: `
// LED Blink Pattern
#define LED_PIN (1 << 12)

// Initialize
RCC_AHB1ENR |= (1 << 3);     // Enable GPIOD clock
GPIOD_MODER |= (0x1 << 24);  // Set PD12 as output

// Toggle
GPIOD_ODR ^= LED_PIN;
`
                },
                'delay': {
                    description: 'Delay function',
                    code: `
void delay_ms(uint32_t ms) {
    // For 168MHz clock
    for (uint32_t i = 0; i < ms * 10000; i++) {
        __asm("nop");
    }
}
`
                }
            }
        };
    }

    /**
     * Load common bug patterns
     */
    loadBugPatterns() {
        return [
            {
                pattern: /volatile\s+/,
                missing: true,
                severity: 'high',
                message: 'Missing volatile keyword for hardware register',
                suggestion: 'Use: volatile uint32_t *reg = ...'
            },
            {
                pattern: /while\s*\(\s*1\s*\)/,
                check: (code) => !code.includes('volatile'),
                severity: 'medium',
                message: 'Infinite loop without volatile may be optimized away',
                suggestion: 'Add volatile to variables modified in interrupt/hardware'
            },
            {
                pattern: /malloc|calloc|free/,
                severity: 'warning',
                message: 'Dynamic memory allocation in embedded systems',
                suggestion: 'Consider static allocation for predictable memory usage'
            },
            {
                pattern: /printf|sprintf/,
                severity: 'warning',
                message: 'Heavy printf usage can bloat code size',
                suggestion: 'Use lightweight alternatives or conditional compilation'
            },
            {
                pattern: /\*\s*\(\s*uint32_t\s*\*\s*\)/,
                check: (code) => !code.includes('volatile'),
                severity: 'high',
                message: 'Hardware register access without volatile',
                suggestion: 'Use: *((volatile uint32_t *)address)'
            }
        ];
    }

    /**
     * Load performance rules
     */
    loadPerformanceRules() {
        return [
            {
                name: 'Division by constant',
                pattern: /\/\s*(\d+)/,
                suggestion: 'Replace division by powers of 2 with bit shift',
                example: 'x / 4  →  x >> 2'
            },
            {
                name: 'Modulo by power of 2',
                pattern: /%\s*(\d+)/,
                check: (match) => {
                    const num = parseInt(match[1]);
                    return (num & (num - 1)) === 0; // Is power of 2?
                },
                suggestion: 'Replace modulo with bitwise AND',
                example: 'x % 16  →  x & 15'
            },
            {
                name: 'Multiplication by constant',
                pattern: /\*\s*(\d+)/,
                check: (match) => {
                    const num = parseInt(match[1]);
                    return (num & (num - 1)) === 0; // Is power of 2?
                },
                suggestion: 'Replace multiplication by powers of 2 with bit shift',
                example: 'x * 8  →  x << 3'
            },
            {
                name: 'Function inlining',
                pattern: /^(?!inline\s).*function.*\{[\s\S]{0,100}\}/,
                suggestion: 'Consider inline keyword for small functions',
                example: 'inline uint32_t get_value() { return val; }'
            }
        ];
    }

    /**
     * Analyze code for bugs
     */
    analyzeBugs(code) {
        const bugs = [];

        for (const pattern of this.bugPatterns) {
            const matches = code.match(pattern.pattern);

            if (pattern.missing && !matches) {
                // Check if this is register access code
                if (code.includes('0x4') || code.includes('_BASE')) {
                    bugs.push({
                        severity: pattern.severity,
                        message: pattern.message,
                        suggestion: pattern.suggestion,
                        line: this.findLineNumber(code, pattern.pattern)
                    });
                }
            } else if (matches && pattern.check) {
                if (pattern.check(code)) {
                    bugs.push({
                        severity: pattern.severity,
                        message: pattern.message,
                        suggestion: pattern.suggestion,
                        line: this.findLineNumber(code, matches[0])
                    });
                }
            } else if (matches && !pattern.check) {
                bugs.push({
                    severity: pattern.severity,
                    message: pattern.message,
                    suggestion: pattern.suggestion,
                    line: this.findLineNumber(code, matches[0])
                });
            }
        }

        return bugs;
    }

    /**
     * Suggest performance improvements
     */
    suggestPerformance(code) {
        const suggestions = [];

        for (const rule of this.performanceRules) {
            const regex = new RegExp(rule.pattern, 'g');
            let match;

            while ((match = regex.exec(code)) !== null) {
                if (rule.check && !rule.check(match)) {
                    continue;
                }

                suggestions.push({
                    name: rule.name,
                    line: this.findLineNumber(code, match[0]),
                    original: match[0],
                    suggestion: rule.suggestion,
                    example: rule.example
                });
            }
        }

        return suggestions;
    }

    /**
     * Auto-complete code
     */
    autoComplete(code, cursorPosition) {
        const lineUpToCursor = this.getLineUpToCursor(code, cursorPosition);
        const lastWord = this.getLastWord(lineUpToCursor);

        const suggestions = [];

        // Check if typing register name
        for (const [peripheral, info] of Object.entries(this.knowledgeBase.registers)) {
            if (peripheral.toLowerCase().startsWith(lastWord.toLowerCase())) {
                suggestions.push({
                    text: peripheral,
                    type: 'peripheral',
                    description: `Base address: ${info.address}`,
                    insertText: peripheral,
                    registers: info.registers
                });
            }

            // Check register names
            for (const reg of info.registers) {
                const fullName = `${peripheral}_${reg}`;
                if (fullName.toLowerCase().startsWith(lastWord.toLowerCase())) {
                    suggestions.push({
                        text: fullName,
                        type: 'register',
                        description: `${peripheral} register`,
                        insertText: fullName
                    });
                }
            }
        }

        // Check common patterns
        for (const [name, pattern] of Object.entries(this.knowledgeBase.commonPatterns)) {
            if (name.toLowerCase().includes(lastWord.toLowerCase())) {
                suggestions.push({
                    text: name,
                    type: 'snippet',
                    description: pattern.description,
                    insertText: pattern.code
                });
            }
        }

        return suggestions;
    }

    /**
     * Generate documentation
     */
    generateDocumentation(code) {
        const functions = this.extractFunctions(code);
        const documentation = [];

        for (const func of functions) {
            const doc = {
                name: func.name,
                description: this.inferDescription(func),
                parameters: func.parameters.map(p => ({
                    name: p,
                    type: this.inferType(p),
                    description: this.inferParamDescription(p)
                })),
                returns: this.inferReturnType(func),
                example: this.generateExample(func)
            };

            documentation.push(doc);
        }

        return documentation;
    }

    /**
     * Code review
     */
    reviewCode(code) {
        const review = {
            bugs: this.analyzeBugs(code),
            performance: this.suggestPerformance(code),
            style: this.checkStyle(code),
            security: this.checkSecurity(code),
            score: 0
        };

        // Calculate score
        review.score = 100
            - (review.bugs.filter(b => b.severity === 'high').length * 10)
            - (review.bugs.filter(b => b.severity === 'medium').length * 5)
            - (review.performance.length * 2)
            - (review.style.length * 1);

        review.score = Math.max(0, review.score);

        return review;
    }

    /**
     * Check coding style
     */
    checkStyle(code) {
        const issues = [];

        // Check indentation
        const lines = code.split('\n');
        for (let i = 0; i < lines.length; i++) {
            const line = lines[i];

            // Inconsistent indentation
            if (line.match(/^\s+/) && !line.match(/^    /) && !line.match(/^\t/)) {
                issues.push({
                    line: i + 1,
                    message: 'Inconsistent indentation',
                    suggestion: 'Use 4 spaces or tabs consistently'
                });
            }

            // Line too long
            if (line.length > 100) {
                issues.push({
                    line: i + 1,
                    message: 'Line too long',
                    suggestion: 'Keep lines under 100 characters'
                });
            }
        }

        return issues;
    }

    /**
     * Check security issues
     */
    checkSecurity(code) {
        const issues = [];

        // Buffer overflow risk
        if (code.includes('strcpy') || code.includes('sprintf')) {
            issues.push({
                severity: 'high',
                message: 'Potential buffer overflow',
                suggestion: 'Use strncpy or snprintf instead'
            });
        }

        // Unchecked return values
        const funcCalls = code.match(/\w+\([^)]*\);/g) || [];
        for (const call of funcCalls) {
            if (!code.includes(`= ${call}`)) {
                issues.push({
                    severity: 'medium',
                    message: 'Unchecked return value',
                    suggestion: 'Check return values for error handling'
                });
            }
        }

        return issues;
    }

    /**
     * Helper: Extract functions from code
     */
    extractFunctions(code) {
        const funcRegex = /(\w+)\s+(\w+)\s*\(([^)]*)\)\s*\{/g;
        const functions = [];
        let match;

        while ((match = funcRegex.exec(code)) !== null) {
            functions.push({
                returnType: match[1],
                name: match[2],
                parameters: match[3].split(',').map(p => p.trim()).filter(p => p)
            });
        }

        return functions;
    }

    /**
     * Helper: Find line number
     */
    findLineNumber(code, search) {
        const lines = code.split('\n');
        for (let i = 0; i < lines.length; i++) {
            if (lines[i].includes(search)) {
                return i + 1;
            }
        }
        return 0;
    }

    /**
     * Helper: Get line up to cursor
     */
    getLineUpToCursor(code, pos) {
        const lineStart = code.lastIndexOf('\n', pos) + 1;
        return code.substring(lineStart, pos);
    }

    /**
     * Helper: Get last word
     */
    getLastWord(text) {
        const match = text.match(/[\w_]+$/);
        return match ? match[0] : '';
    }

    /**
     * Helper: Infer description from function name
     */
    inferDescription(func) {
        const name = func.name.toLowerCase();

        if (name.includes('init')) return 'Initialize peripheral/module';
        if (name.includes('read')) return 'Read data/register';
        if (name.includes('write')) return 'Write data/register';
        if (name.includes('enable')) return 'Enable feature';
        if (name.includes('disable')) return 'Disable feature';
        if (name.includes('get')) return 'Get value';
        if (name.includes('set')) return 'Set value';

        return 'Function description';
    }

    /**
     * Helper: Infer type
     */
    inferType(param) {
        if (param.includes('uint32_t')) return 'uint32_t';
        if (param.includes('uint16_t')) return 'uint16_t';
        if (param.includes('uint8_t')) return 'uint8_t';
        if (param.includes('int')) return 'int';
        if (param.includes('*')) return 'pointer';
        return 'type';
    }

    /**
     * Helper: Infer parameter description
     */
    inferParamDescription(param) {
        const name = param.toLowerCase();

        if (name.includes('addr')) return 'Memory address';
        if (name.includes('data')) return 'Data value';
        if (name.includes('len')) return 'Length';
        if (name.includes('size')) return 'Size in bytes';
        if (name.includes('count')) return 'Count/number';

        return 'Parameter description';
    }

    /**
     * Helper: Infer return type
     */
    inferReturnType(func) {
        return func.returnType;
    }

    /**
     * Helper: Generate example
     */
    generateExample(func) {
        return `${func.name}(/* parameters */);`;
    }
}

// CLI Usage
if (require.main === module) {
    const assistant = new AICodeAssistant();

    const filePath = process.argv[2];
    if (!filePath) {
        console.log('Usage: node ai-assistant.js <file.c>');
        process.exit(1);
    }

    const code = fs.readFileSync(filePath, 'utf-8');

    console.log('🤖 AI Code Assistant Analysis\n');
    console.log('=' .repeat(60));

    // Bug analysis
    const bugs = assistant.analyzeBugs(code);
    console.log('\n🐛 BUG DETECTION:');
    if (bugs.length === 0) {
        console.log('  ✅ No critical bugs found!');
    } else {
        bugs.forEach(bug => {
            console.log(`\n  [${bug.severity.toUpperCase()}] Line ${bug.line}`);
            console.log(`  ${bug.message}`);
            console.log(`  💡 ${bug.suggestion}`);
        });
    }

    // Performance suggestions
    const perf = assistant.suggestPerformance(code);
    console.log('\n⚡ PERFORMANCE:');
    if (perf.length === 0) {
        console.log('  ✅ No performance issues!');
    } else {
        perf.forEach(suggestion => {
            console.log(`\n  Line ${suggestion.line}: ${suggestion.name}`);
            console.log(`  Original: ${suggestion.original}`);
            console.log(`  💡 ${suggestion.suggestion}`);
            console.log(`  Example: ${suggestion.example}`);
        });
    }

    // Code review
    const review = assistant.reviewCode(code);
    console.log('\n📊 CODE REVIEW SCORE:');
    console.log(`  Score: ${review.score}/100`);
    console.log(`  Bugs: ${review.bugs.length}`);
    console.log(`  Performance issues: ${review.performance.length}`);
    console.log(`  Style issues: ${review.style.length}`);

    console.log('\n' + '='.repeat(60));
}

module.exports = AICodeAssistant;
