/**
 * Real-time Variable Graphing - BETTER than IAR!
 * Live plotting without stopping execution
 */

class RealtimeGrapher {
    constructor(containerId) {
        this.container = document.getElementById(containerId);
        this.charts = new Map();
        this.dataBuffers = new Map();
        this.maxDataPoints = 1000;
        this.updateInterval = 100; // ms
        this.isRunning = false;
    }

    /**
     * Add variable to graph
     */
    addVariable(varName, color = null) {
        if (this.charts.has(varName)) {
            return; // Already exists
        }

        // Create chart container
        const chartDiv = document.createElement('div');
        chartDiv.className = 'realtime-chart';
        chartDiv.id = `chart-${varName}`;

        const header = document.createElement('div');
        header.className = 'chart-header';
        header.innerHTML = `
            <span class="chart-title">${varName}</span>
            <span class="chart-value" id="value-${varName}">0</span>
            <button class="chart-close" onclick="realtimeGrapher.removeVariable('${varName}')">×</button>
        `;

        const canvas = document.createElement('canvas');
        canvas.id = `canvas-${varName}`;
        canvas.width = 800;
        canvas.height = 200;

        chartDiv.appendChild(header);
        chartDiv.appendChild(canvas);
        this.container.appendChild(chartDiv);

        // Initialize Chart.js
        const ctx = canvas.getContext('2d');
        const chart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: [],
                datasets: [{
                    label: varName,
                    data: [],
                    borderColor: color || this.getRandomColor(),
                    backgroundColor: 'rgba(0, 0, 0, 0)',
                    borderWidth: 2,
                    pointRadius: 0,
                    tension: 0.4
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: false,
                animation: false,
                scales: {
                    x: {
                        display: true,
                        title: {
                            display: true,
                            text: 'Time (s)'
                        }
                    },
                    y: {
                        display: true,
                        title: {
                            display: true,
                            text: 'Value'
                        }
                    }
                },
                plugins: {
                    legend: {
                        display: false
                    },
                    tooltip: {
                        enabled: true
                    }
                }
            }
        });

        this.charts.set(varName, chart);
        this.dataBuffers.set(varName, {
            timestamps: [],
            values: [],
            startTime: Date.now()
        });
    }

    /**
     * Update variable value (called from GDB)
     */
    updateValue(varName, value) {
        if (!this.dataBuffers.has(varName)) {
            this.addVariable(varName);
        }

        const buffer = this.dataBuffers.get(varName);
        const timestamp = (Date.now() - buffer.startTime) / 1000; // seconds

        buffer.timestamps.push(timestamp);
        buffer.values.push(value);

        // Keep only last N points
        if (buffer.timestamps.length > this.maxDataPoints) {
            buffer.timestamps.shift();
            buffer.values.shift();
        }

        // Update chart
        const chart = this.charts.get(varName);
        chart.data.labels = buffer.timestamps;
        chart.data.datasets[0].data = buffer.values;
        chart.update('none'); // No animation for performance

        // Update value display
        const valueElem = document.getElementById(`value-${varName}`);
        if (valueElem) {
            valueElem.textContent = value.toFixed(4);
        }
    }

    /**
     * Remove variable from graph
     */
    removeVariable(varName) {
        const chart = this.charts.get(varName);
        if (chart) {
            chart.destroy();
            this.charts.delete(varName);
        }

        this.dataBuffers.delete(varName);

        const chartDiv = document.getElementById(`chart-${varName}`);
        if (chartDiv) {
            chartDiv.remove();
        }
    }

    /**
     * Start real-time updates
     */
    start(gdbInterface) {
        this.isRunning = true;
        this.gdb = gdbInterface;

        this.updateLoop = setInterval(() => {
            // Read all variables from GDB without stopping
            this.charts.forEach((chart, varName) => {
                this.gdb.readVariableAsync(varName).then(value => {
                    this.updateValue(varName, value);
                });
            });
        }, this.updateInterval);
    }

    /**
     * Stop updates
     */
    stop() {
        this.isRunning = false;
        if (this.updateLoop) {
            clearInterval(this.updateLoop);
        }
    }

    /**
     * Export data to CSV
     */
    exportToCSV(varName) {
        const buffer = this.dataBuffers.get(varName);
        if (!buffer) return;

        let csv = 'Time (s),Value\n';
        for (let i = 0; i < buffer.timestamps.length; i++) {
            csv += `${buffer.timestamps[i]},${buffer.values[i]}\n`;
        }

        // Download
        const blob = new Blob([csv], { type: 'text/csv' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = `${varName}_data.csv`;
        a.click();
    }

    /**
     * Take screenshot
     */
    takeScreenshot(varName) {
        const canvas = document.getElementById(`canvas-${varName}`);
        if (!canvas) return;

        canvas.toBlob(blob => {
            const url = URL.createObjectURL(blob);
            const a = document.createElement('a');
            a.href = url;
            a.download = `${varName}_chart.png`;
            a.click();
        });
    }

    /**
     * Set trigger (alert when value crosses threshold)
     */
    setTrigger(varName, condition, threshold, callback) {
        const buffer = this.dataBuffers.get(varName);
        if (!buffer) return;

        buffer.trigger = {
            condition, // 'above', 'below', 'equals'
            threshold,
            callback,
            triggered: false
        };
    }

    /**
     * Check triggers
     */
    checkTriggers() {
        this.dataBuffers.forEach((buffer, varName) => {
            if (!buffer.trigger || buffer.values.length === 0) return;

            const latestValue = buffer.values[buffer.values.length - 1];
            const trigger = buffer.trigger;

            let shouldTrigger = false;

            switch(trigger.condition) {
                case 'above':
                    shouldTrigger = latestValue > trigger.threshold;
                    break;
                case 'below':
                    shouldTrigger = latestValue < trigger.threshold;
                    break;
                case 'equals':
                    shouldTrigger = Math.abs(latestValue - trigger.threshold) < 0.001;
                    break;
            }

            if (shouldTrigger && !trigger.triggered) {
                trigger.triggered = true;
                trigger.callback(varName, latestValue);
            } else if (!shouldTrigger) {
                trigger.triggered = false;
            }
        });
    }

    getRandomColor() {
        const colors = [
            '#FF6384', '#36A2EB', '#FFCE56', '#4BC0C0',
            '#9966FF', '#FF9F40', '#FF6384', '#C9CBCF'
        ];
        return colors[Math.floor(Math.random() * colors.length)];
    }
}

// Statistics calculator
class VariableStats {
    constructor(varName, dataBuffer) {
        this.varName = varName;
        this.data = dataBuffer.values;
    }

    mean() {
        return this.data.reduce((a, b) => a + b, 0) / this.data.length;
    }

    min() {
        return Math.min(...this.data);
    }

    max() {
        return Math.max(...this.data);
    }

    stdDev() {
        const mean = this.mean();
        const variance = this.data.reduce((sum, val) => {
            return sum + Math.pow(val - mean, 2);
        }, 0) / this.data.length;
        return Math.sqrt(variance);
    }

    range() {
        return this.max() - this.min();
    }

    peakToPeak() {
        return this.range();
    }

    rms() {
        const sumSquares = this.data.reduce((sum, val) => sum + val * val, 0);
        return Math.sqrt(sumSquares / this.data.length);
    }

    getReport() {
        return {
            variable: this.varName,
            count: this.data.length,
            mean: this.mean().toFixed(4),
            min: this.min().toFixed(4),
            max: this.max().toFixed(4),
            stdDev: this.stdDev().toFixed(4),
            range: this.range().toFixed(4),
            rms: this.rms().toFixed(4)
        };
    }
}

// Global instance
let realtimeGrapher = null;

// Initialize on load
window.addEventListener('DOMContentLoaded', () => {
    realtimeGrapher = new RealtimeGrapher('realtime-graphs-container');
});
