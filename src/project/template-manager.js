// TemplateManager - Handle project templates
const fs = require('fs');
const path = require('path');

class TemplateManager {
    constructor() {
        this.templatesDir = path.join(__dirname, '../../templates');
    }

    listTemplates() {
        if (!fs.existsSync(this.templatesDir)) return [];

        const templates = [];
        const dirs = fs.readdirSync(this.templatesDir);

        for (const dir of dirs) {
            const templatePath = path.join(this.templatesDir, dir);
            const configPath = path.join(templatePath, 'project.json');

            if (fs.existsSync(configPath)) {
                try {
                    const config = JSON.parse(fs.readFileSync(configPath, 'utf8'));
                    templates.push({
                        id: dir,
                        name: config.name || dir,
                        description: config.description || '',
                        family: config.target?.family || 'Unknown'
                    });
                } catch (e) {
                    console.error(`[TemplateManager] Failed to load ${dir}:`, e);
                }
            }
        }

        return templates;
    }

    async createFromTemplate(templateId, destPath, options = {}) {
        const templatePath = path.join(this.templatesDir, templateId);

        if (!fs.existsSync(templatePath)) {
            throw new Error(`Template not found: ${templateId}`);
        }

        if (fs.existsSync(destPath)) {
            throw new Error(`Destination already exists: ${destPath}`);
        }

        fs.mkdirSync(destPath, { recursive: true });
        this.copyDirectory(templatePath, destPath);

        const configPath = path.join(destPath, 'project.json');
        let config = JSON.parse(fs.readFileSync(configPath, 'utf8'));

        if (options.projectName) config.name = options.projectName;

        fs.writeFileSync(configPath, JSON.stringify(config, null, 2), 'utf8');

        return { success: true, projectPath: destPath, config };
    }

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
}

module.exports = TemplateManager;
