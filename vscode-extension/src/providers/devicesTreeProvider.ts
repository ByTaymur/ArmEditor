/**
 * Devices Tree Provider
 * Shows connected STM32 devices and quick actions
 */

import * as vscode from 'vscode';
import { DeviceDetector } from '../services/deviceDetector';

export class DevicesTreeProvider implements vscode.TreeDataProvider<vscode.TreeItem> {
    private _onDidChangeTreeData = new vscode.EventEmitter<vscode.TreeItem | undefined | null | void>();
    readonly onDidChangeTreeData = this._onDidChangeTreeData.event;

    private detector: DeviceDetector;

    constructor() {
        this.detector = new DeviceDetector();
    }

    refresh(): void {
        this._onDidChangeTreeData.fire();
    }

    getTreeItem(element: vscode.TreeItem): vscode.TreeItem {
        return element;
    }

    async getChildren(element?: vscode.TreeItem): Promise<vscode.TreeItem[]> {
        if (!element) {
            const items: vscode.TreeItem[] = [];

            // QUICK ACTIONS Header
            const actionsHeader = new vscode.TreeItem('⚡ QUICK ACTIONS', vscode.TreeItemCollapsibleState.None);
            actionsHeader.contextValue = 'header';
            items.push(actionsHeader);

            // Build
            const build = new vscode.TreeItem('Build Project', vscode.TreeItemCollapsibleState.None);
            build.iconPath = new vscode.ThemeIcon('tools');
            build.command = { command: 'hopeide.build', title: 'Build' };
            items.push(build);

            // Flash
            const flash = new vscode.TreeItem('Flash Device', vscode.TreeItemCollapsibleState.None);
            flash.iconPath = new vscode.ThemeIcon('zap');
            flash.command = { command: 'hopeide.flash', title: 'Flash' };
            items.push(flash);

            // Clean
            const clean = new vscode.TreeItem('Clean Build', vscode.TreeItemCollapsibleState.None);
            clean.iconPath = new vscode.ThemeIcon('trash');
            clean.command = { command: 'hopeide.clean', title: 'Clean' };
            items.push(clean);

            // Detect
            const detect = new vscode.TreeItem('Detect Device', vscode.TreeItemCollapsibleState.None);
            detect.iconPath = new vscode.ThemeIcon('search');
            detect.command = { command: 'hopeide.detectDevice', title: 'Detect' };
            items.push(detect);

            // Start Debug - NEW!
            const startDebug = new vscode.TreeItem('Start Debug', vscode.TreeItemCollapsibleState.None);
            startDebug.iconPath = new vscode.ThemeIcon('debug-start', new vscode.ThemeColor('debugIcon.startForeground'));
            startDebug.command = { command: 'workbench.action.debug.start', title: 'Start Debug' };
            startDebug.tooltip = 'Start debugging with HopeIDE';
            items.push(startDebug);

            // DEVICES Header
            const devicesHeader = new vscode.TreeItem('📱 CONNECTED DEVICES', vscode.TreeItemCollapsibleState.None);
            devicesHeader.contextValue = 'header';
            items.push(devicesHeader);

            // Try to detect device
            try {
                const device = await this.detector.detect();
                if (device) {
                    const deviceItem = new vscode.TreeItem(device.name, vscode.TreeItemCollapsibleState.Collapsed);
                    deviceItem.description = device.family;
                    deviceItem.iconPath = new vscode.ThemeIcon('chip', new vscode.ThemeColor('charts.green'));
                    deviceItem.tooltip = `${device.name} (${device.family})`;
                    deviceItem.contextValue = 'device';
                    items.push(deviceItem);
                } else {
                    const noDevice = new vscode.TreeItem('No device detected', vscode.TreeItemCollapsibleState.None);
                    noDevice.iconPath = new vscode.ThemeIcon('circle-slash');
                    noDevice.description = 'Connect ST-Link';
                    items.push(noDevice);
                }
            } catch {
                const error = new vscode.TreeItem('ST-Link not found', vscode.TreeItemCollapsibleState.None);
                error.iconPath = new vscode.ThemeIcon('warning', new vscode.ThemeColor('errorForeground'));
                error.description = 'Install st-flash';
                items.push(error);
            }

            return items;

        } else if (element.contextValue === 'device') {
            try {
                const device = await this.detector.detect();
                if (device) {
                    const details: vscode.TreeItem[] = [];

                    const chipId = new vscode.TreeItem(`Chip ID: ${device.chipId}`, vscode.TreeItemCollapsibleState.None);
                    chipId.iconPath = new vscode.ThemeIcon('symbol-key');
                    details.push(chipId);

                    const flash = new vscode.TreeItem(`Flash: ${(device.flashSize / 1024).toFixed(0)}KB`, vscode.TreeItemCollapsibleState.None);
                    flash.iconPath = new vscode.ThemeIcon('database');
                    details.push(flash);

                    const family = new vscode.TreeItem(`Family: ${device.family}`, vscode.TreeItemCollapsibleState.None);
                    family.iconPath = new vscode.ThemeIcon('symbol-namespace');
                    details.push(family);

                    return details;
                }
            } catch { }
        }

        return [];
    }
}
