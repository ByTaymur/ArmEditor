/**
 * Devices Tree Provider
 * Shows connected STM32 devices and quick actions
 */

import * as vscode from 'vscode';
import { DeviceDetector } from '../services/deviceDetector';

export class DevicesTreeProvider implements vscode.TreeDataProvider<TreeItem> {
    private _onDidChangeTreeData = new vscode.EventEmitter<TreeItem | undefined | null | void>();
    readonly onDidChangeTreeData = this._onDidChangeTreeData.event;

    private detector: DeviceDetector;

    constructor() {
        this.detector = new DeviceDetector();
    }

    refresh(): void {
        this._onDidChangeTreeData.fire();
    }

    getTreeItem(element: TreeItem): vscode.TreeItem {
        return element;
    }

    async getChildren(element?: TreeItem): Promise<TreeItem[]> {
        if (!element) {
            // Root level - show actions and detected devices
            const items: TreeItem[] = [];

            // Quick Actions
            items.push(new TreeItem(
                '🔨 Build Project',
                vscode.TreeItemCollapsibleState.None,
                { command: 'hopeide.build', title: 'Build' }
            ));

            items.push(new TreeItem(
                '⚡ Flash Device',
                vscode.TreeItemCollapsibleState.None,
                { command: 'hopeide.flash', title: 'Flash' }
            ));

            items.push(new TreeItem(
                '🧹 Clean Build',
                vscode.TreeItemCollapsibleState.None,
                { command: 'hopeide.clean', title: 'Clean' }
            ));

            items.push(new TreeItem(
                '🔍 Detect Device',
                vscode.TreeItemCollapsibleState.None,
                { command: 'hopeide.detectDevice', title: 'Detect' }
            ));

            // Separator
            items.push(new TreeItem('──────────', vscode.TreeItemCollapsibleState.None));

            // Try to detect device
            try {
                const device = await this.detector.detect();
                if (device) {
                    const deviceItem = new TreeItem(
                        `📱 ${device.name}`,
                        vscode.TreeItemCollapsibleState.Expanded
                    );
                    deviceItem.description = device.family;
                    items.push(deviceItem);

                    // Device info children will be returned when deviceItem is the element
                    return items;
                } else {
                    items.push(new TreeItem(
                        '❌ No device detected',
                        vscode.TreeItemCollapsibleState.None
                    ));
                }
            } catch (error) {
                items.push(new TreeItem(
                    '⚠️ ST-Link not found',
                    vscode.TreeItemCollapsibleState.None
                ));
            }

            return items;
        } else if (element.label?.toString().includes('📱')) {
            // Device info children
            try {
                const device = await this.detector.detect();
                if (device) {
                    return [
                        new TreeItem(`Chip ID: ${device.chipId}`, vscode.TreeItemCollapsibleState.None),
                        new TreeItem(`Flash: ${device.flashSize} bytes`, vscode.TreeItemCollapsibleState.None),
                        new TreeItem(`Family: ${device.family}`, vscode.TreeItemCollapsibleState.None)
                    ];
                }
            } catch { }
        }

        return [];
    }
}

class TreeItem extends vscode.TreeItem {
    constructor(
        public readonly label: string,
        public readonly collapsibleState: vscode.TreeItemCollapsibleState,
        public readonly command?: vscode.Command
    ) {
        super(label, collapsibleState);

        // Set icons for actions
        if (label.includes('🔨')) {
            this.iconPath = new vscode.ThemeIcon('tools');
        } else if (label.includes('⚡')) {
            this.iconPath = new vscode.ThemeIcon('zap');
        } else if (label.includes('🧹')) {
            this.iconPath = new vscode.ThemeIcon('trash');
        } else if (label.includes('🔍')) {
            this.iconPath = new vscode.ThemeIcon('search');
        } else if (label.includes('📱')) {
            this.iconPath = new vscode.ThemeIcon('device-mobile');
        }
    }
}
