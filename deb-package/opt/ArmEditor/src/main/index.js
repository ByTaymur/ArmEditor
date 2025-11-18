const { app, BrowserWindow, ipcMain, Menu } = require('electron');
const path = require('path');
const fs = require('fs');

let mainWindow;

function createWindow() {
  mainWindow = new BrowserWindow({
    width: 1400,
    height: 900,
    title: 'ArmEditor - ARM Development IDE',
    icon: path.join(__dirname, '../../resources/icon.png'),
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      enableRemoteModule: true
    },
    backgroundColor: '#1e1e1e',
    show: false
  });

  mainWindow.loadFile(path.join(__dirname, '../renderer/index.html'));

  // Show when ready
  mainWindow.once('ready-to-show', () => {
    mainWindow.show();
  });

  // Development tools
  if (process.argv.includes('--dev')) {
    mainWindow.webContents.openDevTools();
  }

  // Menu
  createMenu();

  mainWindow.on('closed', () => {
    mainWindow = null;
  });
}

function createMenu() {
  const template = [
    {
      label: 'File',
      submenu: [
        {
          label: 'New Project',
          accelerator: 'CmdOrCtrl+N',
          click: () => {
            mainWindow.webContents.send('menu-new-project');
          }
        },
        {
          label: 'Open Project',
          accelerator: 'CmdOrCtrl+O',
          click: () => {
            mainWindow.webContents.send('menu-open-project');
          }
        },
        { type: 'separator' },
        {
          label: 'Save',
          accelerator: 'CmdOrCtrl+S',
          click: () => {
            mainWindow.webContents.send('menu-save');
          }
        },
        {
          label: 'Save All',
          accelerator: 'CmdOrCtrl+Shift+S',
          click: () => {
            mainWindow.webContents.send('menu-save-all');
          }
        },
        { type: 'separator' },
        {
          label: 'Exit',
          accelerator: 'CmdOrCtrl+Q',
          click: () => {
            app.quit();
          }
        }
      ]
    },
    {
      label: 'Edit',
      submenu: [
        { role: 'undo' },
        { role: 'redo' },
        { type: 'separator' },
        { role: 'cut' },
        { role: 'copy' },
        { role: 'paste' },
        { type: 'separator' },
        {
          label: 'Find',
          accelerator: 'CmdOrCtrl+F',
          click: () => {
            mainWindow.webContents.send('menu-find');
          }
        },
        {
          label: 'Replace',
          accelerator: 'CmdOrCtrl+H',
          click: () => {
            mainWindow.webContents.send('menu-replace');
          }
        }
      ]
    },
    {
      label: 'Build',
      submenu: [
        {
          label: 'Build Project',
          accelerator: 'F7',
          click: () => {
            mainWindow.webContents.send('menu-build');
          }
        },
        {
          label: 'Clean',
          click: () => {
            mainWindow.webContents.send('menu-clean');
          }
        },
        {
          label: 'Rebuild',
          accelerator: 'Shift+F7',
          click: () => {
            mainWindow.webContents.send('menu-rebuild');
          }
        },
        { type: 'separator' },
        {
          label: 'Build Configuration',
          submenu: [
            {
              label: 'Debug',
              type: 'radio',
              checked: true,
              click: () => {
                mainWindow.webContents.send('menu-config-debug');
              }
            },
            {
              label: 'Release',
              type: 'radio',
              click: () => {
                mainWindow.webContents.send('menu-config-release');
              }
            }
          ]
        }
      ]
    },
    {
      label: 'Debug',
      submenu: [
        {
          label: 'Start Debugging',
          accelerator: 'F5',
          click: () => {
            mainWindow.webContents.send('menu-debug-start');
          }
        },
        {
          label: 'Stop Debugging',
          accelerator: 'Shift+F5',
          click: () => {
            mainWindow.webContents.send('menu-debug-stop');
          }
        },
        { type: 'separator' },
        {
          label: 'Step Over',
          accelerator: 'F10',
          click: () => {
            mainWindow.webContents.send('menu-debug-step-over');
          }
        },
        {
          label: 'Step Into',
          accelerator: 'F11',
          click: () => {
            mainWindow.webContents.send('menu-debug-step-into');
          }
        },
        {
          label: 'Step Out',
          accelerator: 'Shift+F11',
          click: () => {
            mainWindow.webContents.send('menu-debug-step-out');
          }
        },
        { type: 'separator' },
        {
          label: 'Toggle Breakpoint',
          accelerator: 'F9',
          click: () => {
            mainWindow.webContents.send('menu-debug-toggle-breakpoint');
          }
        }
      ]
    },
    {
      label: 'Tools',
      submenu: [
        {
          label: 'Terminal',
          accelerator: 'Ctrl+`',
          click: () => {
            mainWindow.webContents.send('menu-toggle-terminal');
          }
        },
        {
          label: 'Serial Monitor',
          click: () => {
            mainWindow.webContents.send('menu-serial-monitor');
          }
        },
        { type: 'separator' },
        {
          label: 'Settings',
          accelerator: 'CmdOrCtrl+,',
          click: () => {
            mainWindow.webContents.send('menu-settings');
          }
        }
      ]
    },
    {
      label: 'Help',
      submenu: [
        {
          label: 'Documentation',
          click: () => {
            mainWindow.webContents.send('menu-documentation');
          }
        },
        {
          label: 'About',
          click: () => {
            mainWindow.webContents.send('menu-about');
          }
        },
        { type: 'separator' },
        {
          label: 'Toggle DevTools',
          accelerator: 'F12',
          click: () => {
            mainWindow.webContents.toggleDevTools();
          }
        }
      ]
    }
  ];

  const menu = Menu.buildFromTemplate(template);
  Menu.setApplicationMenu(menu);
}

// IPC handlers
ipcMain.on('window-minimize', () => {
  mainWindow.minimize();
});

ipcMain.on('window-maximize', () => {
  if (mainWindow.isMaximized()) {
    mainWindow.unmaximize();
  } else {
    mainWindow.maximize();
  }
});

ipcMain.on('window-close', () => {
  mainWindow.close();
});

// App lifecycle
app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow();
  }
});

console.log('ArmEditor IDE started successfully!');
