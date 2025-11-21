// Template Manager - Handle project templates and new project creation
const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

class TemplateManager {
    constructor() {
        this.templatesDir = path.join(__dirname, '../../templates');
    }

    /**
     * List available templates
     */
    listTemplates() {
        if (!fs.existsSync(this.templatesDir)) {
            return [];
        }

        const templates = [];
        const dirs = fs.readdirSync(this.templatesDir);

        for (const dir of dirs) {
            const templatePath = path.join(this.templatesDir, dir);
            const configPath = path.join(templatePath, 'project.json');

            if (fs.statSync(templatePath).isDirectory() && fs.existsSync(configPath)) {
                try {
                    const config = JSON.parse(fs.readFileSync(configPath, 'utf8'));
                    templates.push({
                        id: dir,
                        name: config.name || dir,
                        description: config.description || '',
                        family: config.target?.family || 'Unknown',
                        mcu: config.target?.mcu || 'Unknown'
                    });
                } catch (e) {
                    console.error(`[TemplateManager] Failed to load template ${dir}:`, e);
                }
            }
        }

        return templates;
    }

    /**
     * Create new project from template
     * @param {string} templateId - Template ID (directory name)
     * @param {string} destPath - Destination directory
     * @param {object} options - Customization options
     */
    async createFromTemplate(templateId, destPath, options = {}) {
        const templatePath = path.join(this.templatesDir, templateId);

        if (!fs.existsSync(templatePath)) {
            throw new Error(`Template not found: ${templateId}`);
        }

        if (fs.existsSync(destPath)) {
            throw new Error(`Destination already exists: ${destPath}`);
        }

        // Create destination directory
        fs.mkdirSync(destPath, { recursive: true });

        // Copy template files
        this.copyDirectory(templatePath, destPath);

        // Load and customize project.json
        const configPath = path.join(destPath, 'project.json');
        let config = JSON.parse(fs.readFileSync(configPath, 'utf8'));

        // Apply customizations
        if (options.projectName) {
            config.name = options.projectName;
        }

        if (options.mcu) {
            config.target.mcu = options.mcu;
        }

        if (options.clock) {
            config.target.clock = options.clock;
        }

        // Save customized config
        fs.writeFileSync(configPath, JSON.stringify(config, null, 2), 'utf8');

        // Download HAL drivers if not present
        if (options.downloadHAL !== false) {
            await this.ensureHALDrivers(destPath, config.target.family);
        }

        return {
            success: true,
            projectPath: destPath,
            config: config
        };
    }

    /**
     * Copy directory recursively
     */
    copyDirectory(src, dest) {
        const entries = fs.readdirSync(src, { withFileTypes: true });

        for (const entry of entries) {
            const srcPath = path.join(src, entry.name);
            const destPath = path.join(dest, entry.name);

            if (entry.isDirectory()) {
                fs.mkdirSync(destPath, { recursive: true });
                this.copyDirectory(srcPath, destPath);
            } else {
                fs.copyFileSync(srcPath, destPath);
            }
        }
    }

    /**
     * Ensure HAL drivers are present
     */
    async ensureHALDrivers(projectPath, family) {
        const driversPath = path.join(projectPath, 'Drivers');

        // Check if drivers already exist
        if (fs.existsSync(path.join(driversPath, `${family}xx_HAL_Driver`))) {
            console.log('[TemplateManager] HAL drivers already present');
            return;
        }

        // Try to download from STM32Cube repository
        try {
            console.log(`[TemplateManager] Downloading ${family} HAL drivers...`);

            const cubeRepo = this.getCubeRepoURL(family);
            if (!cubeRepo) {
                console.warn('[TemplateManager] No repository URL for ' + family);
                return;
            }

            // Clone specific folders (sparse checkout)
            const tempDir = path.join('/tmp', `stm32cube_${family}_${Date.now()}`);

            execSync(`git clone --depth 1 --filter=blob:none --sparse ${cubeRepo} ${tempDir}`, {
                stdio: 'pipe'
            });

            execSync(`cd ${tempDir} && git sparse-checkout set Drivers`, {
                stdio: 'pipe'
            });

            // Copy drivers to project
            const srcDrivers = path.join(tempDir, 'Drivers');
            if (fs.existsSync(srcDrivers)) {
                this.copyDirectory(srcDrivers, driversPath);
                console.log('[TemplateManager] HAL drivers downloaded successfully');
            }

            // Cleanup
            execSync(`rm -rf ${tempDir}`, { stdio: 'pipe' });

        } catch (e) {
            console.error('[TemplateManager] Failed to download HAL drivers:', e.message);
            console.warn('[TemplateManager] You may need to download HAL drivers manually');
        }
    }

    /**
     * Get STM32Cube repository URL for family
     */
    getCubeRepoURL(family) {
        const repos = {
            'STM32F4': 'https://github.com/STMicroelectronics/STM32CubeF4.git',
            'STM32F7': 'https://github.com/STMicroelectronics/STM32CubeF7.git',
            'STM32F0': 'https://github.com/STMicroelectronics/STM32CubeF0.git',
            'STM32F1': 'https://github.com/STMicroelectronics/STM32CubeF1.git',
            'STM32F2': 'https://github.com/STMicroelectronics/STM32CubeF2.git',
            'STM32F3': 'https://github.com/STMicroelectronics/STM32CubeF3.git',
            'STM32L4': 'https://github.com/STMicroelectronics/STM32CubeL4.git',
            'STM32H7': 'https://github.com/STMicroelectronics/STM32CubeH7.git'
        };

        return repos[family] || null;
    }

    /**
     * Get template info
     */
    getTemplateInfo(templateId) {
        const templatePath = path.join(this.templatesDir, templateId);
        const configPath = path.join(templatePath, 'project.json');

        if (!fs.existsSync(configPath)) {
            return null;
        }

        try {
            const config = JSON.parse(fs.readFileSync(configPath, 'utf8'));
            return {
                id: templateId,
                path: templatePath,
                config: config
            };
        } catch (e) {
            return null;
        }
    }
}

module.exports = TemplateManager;
