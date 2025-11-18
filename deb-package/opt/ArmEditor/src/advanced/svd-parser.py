#!/usr/bin/env python3
"""
STM32 SVD (System View Description) Parser
Peripheral registers viewer - BETTER than Keil!
"""

import xml.etree.ElementTree as ET
import json
from typing import Dict, List, Optional

class SVDParser:
    """Parse ARM SVD files for peripheral register access"""

    def __init__(self, svd_file_path: str):
        self.svd_file = svd_file_path
        self.tree = None
        self.root = None
        self.device_info = {}
        self.peripherals = {}

    def parse(self) -> Dict:
        """Parse SVD file and return structured data"""
        try:
            self.tree = ET.parse(self.svd_file)
            self.root = self.tree.getroot()

            # Get device info
            self.device_info = {
                'name': self._get_text('name'),
                'version': self._get_text('version'),
                'description': self._get_text('description'),
                'cpu': self._parse_cpu(),
                'addressUnitBits': self._get_text('addressUnitBits'),
                'width': self._get_text('width')
            }

            # Parse peripherals
            peripherals_elem = self.root.find('peripherals')
            if peripherals_elem:
                for peripheral in peripherals_elem.findall('peripheral'):
                    p_data = self._parse_peripheral(peripheral)
                    self.peripherals[p_data['name']] = p_data

            return {
                'device': self.device_info,
                'peripherals': self.peripherals
            }

        except Exception as e:
            print(f"Error parsing SVD: {e}")
            return {}

    def _get_text(self, tag: str, element=None) -> str:
        """Get text from XML element"""
        elem = element if element is not None else self.root
        found = elem.find(tag)
        return found.text if found is not None else ""

    def _parse_cpu(self) -> Dict:
        """Parse CPU information"""
        cpu = self.root.find('cpu')
        if cpu is None:
            return {}

        return {
            'name': self._get_text('name', cpu),
            'revision': self._get_text('revision', cpu),
            'endian': self._get_text('endian', cpu),
            'mpuPresent': self._get_text('mpuPresent', cpu),
            'fpuPresent': self._get_text('fpuPresent', cpu),
            'nvicPrioBits': self._get_text('nvicPrioBits', cpu),
            'vendorSystickConfig': self._get_text('vendorSystickConfig', cpu)
        }

    def _parse_peripheral(self, peripheral) -> Dict:
        """Parse a peripheral"""
        p_data = {
            'name': self._get_text('name', peripheral),
            'description': self._get_text('description', peripheral),
            'baseAddress': self._get_text('baseAddress', peripheral),
            'registers': []
        }

        # Parse registers
        registers = peripheral.find('registers')
        if registers:
            for register in registers.findall('register'):
                reg_data = self._parse_register(register)
                p_data['registers'].append(reg_data)

        return p_data

    def _parse_register(self, register) -> Dict:
        """Parse a register"""
        reg_data = {
            'name': self._get_text('name', register),
            'description': self._get_text('description', register),
            'addressOffset': self._get_text('addressOffset', register),
            'size': self._get_text('size', register),
            'access': self._get_text('access', register),
            'resetValue': self._get_text('resetValue', register),
            'fields': []
        }

        # Parse fields
        fields = register.find('fields')
        if fields:
            for field in fields.findall('field'):
                field_data = {
                    'name': self._get_text('name', field),
                    'description': self._get_text('description', field),
                    'bitOffset': self._get_text('bitOffset', field),
                    'bitWidth': self._get_text('bitWidth', field),
                    'access': self._get_text('access', field)
                }
                reg_data['fields'].append(field_data)

        return reg_data

    def get_peripheral_address(self, peripheral_name: str) -> Optional[int]:
        """Get base address of a peripheral"""
        if peripheral_name in self.peripherals:
            addr = self.peripherals[peripheral_name]['baseAddress']
            return int(addr, 16) if addr.startswith('0x') else int(addr)
        return None

    def get_register_info(self, peripheral_name: str, register_name: str) -> Optional[Dict]:
        """Get register information"""
        if peripheral_name not in self.peripherals:
            return None

        for reg in self.peripherals[peripheral_name]['registers']:
            if reg['name'] == register_name:
                return reg
        return None

    def format_register_value(self, peripheral_name: str, register_name: str, value: int) -> str:
        """Format register value with field breakdown"""
        reg_info = self.get_register_info(peripheral_name, register_name)
        if not reg_info:
            return f"0x{value:08X}"

        result = f"0x{value:08X}\n"

        for field in reg_info['fields']:
            bit_offset = int(field['bitOffset'])
            bit_width = int(field['bitWidth'])
            mask = (1 << bit_width) - 1
            field_value = (value >> bit_offset) & mask

            result += f"  {field['name']}: {field_value} "
            result += f"(bits {bit_offset}-{bit_offset + bit_width - 1})\n"

        return result


def download_stm32_svd(mcu: str) -> str:
    """Download SVD file for STM32 MCU"""
    # SVD files are available from ARM CMSIS
    svd_urls = {
        'STM32F407': 'https://raw.githubusercontent.com/posborne/cmsis-svd/master/data/STMicro/STM32F407.svd',
        'STM32F103': 'https://raw.githubusercontent.com/posborne/cmsis-svd/master/data/STMicro/STM32F103.svd',
        'STM32F746': 'https://raw.githubusercontent.com/posborne/cmsis-svd/master/data/STMicro/STM32F746.svd',
    }

    import urllib.request
    import os

    if mcu not in svd_urls:
        return ""

    svd_dir = os.path.expanduser('~/.armeditor/svd')
    os.makedirs(svd_dir, exist_ok=True)

    svd_file = os.path.join(svd_dir, f'{mcu}.svd')

    if not os.path.exists(svd_file):
        try:
            urllib.request.urlretrieve(svd_urls[mcu], svd_file)
            print(f"Downloaded SVD for {mcu}")
        except Exception as e:
            print(f"Failed to download SVD: {e}")
            return ""

    return svd_file


if __name__ == '__main__':
    # Test
    svd_file = download_stm32_svd('STM32F407')
    if svd_file:
        parser = SVDParser(svd_file)
        data = parser.parse()
        print(json.dumps(data, indent=2))
