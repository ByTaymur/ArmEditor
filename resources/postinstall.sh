#!/bin/bash
# HopeIDE Post-Install Script

# Set permissions
chmod +x /opt/HopeIDE/hopeide

# Create symbolic link
ln -sf /opt/HopeIDE/hopeide /usr/local/bin/hopeide

echo "HopeIDE installed successfully!"
