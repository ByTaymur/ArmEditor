/**
 * Device Detection Service  
 * Auto-detect connected STM32 devices
 */

import { exec } from 'child_process';
import { promisify } from 'util';

const execAsync = promisify(exec);

export interface STM32Device {
    name: string;
    family: string;
    chipId: string;
    flashSize: number;
    ramSize: number;
}

export class DeviceDetector {
    /**
     * Detect connected STM32 device via st-info
     */
    async detect(): Promise<STM32Device | null> {
        try {
            const { stdout } = await execAsync('st-info --probe');
            return this.parseStInfo(stdout);
        } catch (error) {
            // Try OpenOCD
            return await this.detectViaOpenOCD();
        }
    }

    private parseStInfo(output: string): STM32Device | null {
        const chipIdMatch = output.match(/chipid:\s*0x([0-9a-fA-F]+)/);
        const descrMatch = output.match(/descr:\s*(.+)/);
        const flashMatch = output.match(/flash:\s*(\d+)/);

        if (!chipIdMatch) return null;

        const chipId = chipIdMatch[1];
        const name = this.chipIdToName(chipId);

        return {
            name: name || (descrMatch ? descrMatch[1] : 'Unknown'),
            family: this.getFamily(name),
            chipId: '0x' + chipId,
            flashSize: flashMatch ? parseInt(flashMatch[1]) : 0,
            ramSize: 0
        };
    }

    private async detectViaOpenOCD(): Promise<STM32Device | null> {
        // TODO: Implement OpenOCD detection
        return null;
    }

    private chipIdToName(chipId: string): string {
        const map: Record<string, string> = {
            '413': 'STM32F407VGT6',
            '419': 'STM32F429ZIT6',
            '449': 'STM32F746NGH6',
            '450': 'STM32H743ZIT6',
            '444': 'STM32F103C8T6',
            '440': 'STM32F030F4P6'
        };
        return map[chipId] || 'Unknown STM32';
    }

    private getFamily(name: string): string {
        if (name.includes('F0')) return 'STM32F0';
        if (name.includes('F1')) return 'STM32F1';
        if (name.includes('F4')) return 'STM32F4';
        if (name.includes('F7')) return 'STM32F7';
        if (name.includes('H7')) return 'STM32H7';
        if (name.includes('L4')) return 'STM32L4';
        return 'Unknown';
    }
}
