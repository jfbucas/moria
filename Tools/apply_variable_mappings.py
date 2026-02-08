#!/usr/bin/env python3
"""
Variable Mapping Application Tool for Moria Codebase

This script helps apply variable naming conventions from variable_mappings.json
to C source files that have been reverse engineered from the Moria executable.

Usage:
    python apply_variable_mappings.py <input_file> [output_file]
    python apply_variable_mappings.py --interactive <input_file>
    python apply_variable_mappings.py --dry-run <input_file>
"""

import json
import re
import sys
import argparse
from pathlib import Path
from typing import Dict, List, Tuple, Set


class VariableMapper:
    """Applies variable naming conventions to reverse engineered C code."""

    def __init__(self, mappings_file: str = "variable_mappings.json"):
        """Initialize with mappings from JSON file."""
        with open(mappings_file, 'r') as f:
            self.mappings = json.load(f)

        # Build quick lookup dictionaries
        self.memory_map = self._build_memory_map()
        self.offset_map = self._build_offset_map()
        self.constants = self.mappings.get('constants', {})

    def _build_memory_map(self) -> Dict[str, str]:
        """Build flat map of memory addresses to variable names."""
        result = {}
        for category in self.mappings.get('memory_addresses', {}).values():
            for addr, info in category.items():
                if isinstance(info, dict) and 'name' in info:
                    result[addr.lower()] = info['name']
        return result

    def _build_offset_map(self) -> Dict[str, str]:
        """Build map of array offsets to names."""
        result = {}
        for offset, info in self.mappings.get('array_offsets', {}).items():
            if isinstance(info, dict) and 'name' in info:
                result[offset.lower()] = info['name']
        return result

    def replace_memory_addresses(self, line: str) -> str:
        """Replace memory address references with named variables."""
        # Pattern: *(type *)0xABCD
        pattern = r'\*\(([\w\s]+)\s*\*\)\s*(0x[0-9a-fA-F]+)'

        def replacer(match):
            type_name = match.group(1).strip()
            address = match.group(2).lower()

            if address in self.memory_map:
                var_name = self.memory_map[address]
                return f"{var_name}"  # Direct access, remove cast
            return match.group(0)  # No change

        return re.sub(pattern, replacer, line)

    def replace_offsets(self, line: str) -> str:
        """Replace negative offset patterns with named arrays."""
        # Pattern: *(type *)(index * N + -0xABCD)
        pattern = r'\*\(([\w\s]+)\s*\*\)\s*\(([\w\s\+\*]+)\s*([\+\-])\s*(0x[0-9a-fA-F]+)\)'

        def replacer(match):
            type_name = match.group(1).strip()
            index_expr = match.group(2).strip()
            operator = match.group(3)
            offset = match.group(4).lower()

            # Check if offset matches known array
            offset_key = f"{operator}{offset}"
            if offset_key in self.offset_map:
                array_name = self.offset_map[offset_key]
                # Try to extract index from expression like "local_4 * 4"
                return f"{array_name}[{index_expr}]"

            return match.group(0)  # No change

        return re.sub(pattern, replacer, line)

    def replace_hex_constants(self, line: str) -> str:
        """Replace hex constants with named constants where applicable."""
        replacements = {
            '0x4f': 'MAP_WIDTH',
            '0x16': 'MAP_HEIGHT',
            '0x719': 'MAP_SIZE',
            '0x1a': 'ITEM_SIZE',
            '0x36': 'MONSTER_SIZE',
            '0xff': 'STAT_MAX',
            '0xc': 'INVENTORY_MAX',
            '0x20': 'CHAR_FLOOR'
        }

        for hex_val, const_name in replacements.items():
            # Only replace in context like: value == 0x4f or value * 0x4f
            line = re.sub(
                r'\b' + re.escape(hex_val) + r'\b',
                const_name,
                line
            )

        return line

    def suggest_parameter_name(self, param_name: str, param_type: str,
                               function_body: str) -> str:
        """Suggest better parameter name based on type and usage."""
        patterns = self.mappings.get('common_patterns', {}).get('parameter_names', {})

        # Analyze usage in function body
        is_written = f'*{param_name}' in function_body or f'{param_name}[' in function_body
        is_compared = any(op in function_body for op in [f'{param_name} ==', f'{param_name} <',
                                                           f'{param_name} >'])

        # Type-based suggestions
        if 'int *' in param_type or 'int*' in param_type:
            if is_written:
                return patterns.get('param_1_int_ptr', ['out_result'])[0]
        elif 'char *' in param_type or 'char*' in param_type:
            return patterns.get('param_1_char_ptr', ['buffer'])[0]
        elif param_name == 'param_2':
            return patterns.get('param_2_int', ['x_coord'])[0]
        elif param_name == 'param_3':
            return patterns.get('param_3_int', ['y_coord'])[0]

        return param_name  # Keep original if no suggestion

    def suggest_local_name(self, local_name: str, var_type: str,
                          usage_context: str) -> str:
        """Suggest better local variable name based on usage."""
        patterns = self.mappings.get('common_patterns', {}).get('local_variable_names', {})

        # Check for loop counter pattern
        if '= 0;' in usage_context or '= 1;' in usage_context:
            if f'{local_name} = {local_name} + 1' in usage_context:
                return 'index'

        # Check for boolean pattern
        if "= '\\0'" in usage_context or "= '\\x01'" in usage_context:
            return 'found' if 'found' not in usage_context else 'flag'

        # Type-based defaults
        if local_name.startswith('local_') and local_name.endswith(('4', '6', '8')):
            return patterns.get('local_' + local_name[-1], [local_name])[0]

        return local_name

    def process_file(self, input_path: str, output_path: str = None,
                    dry_run: bool = False) -> None:
        """Process entire C file with mappings."""
        with open(input_path, 'r') as f:
            lines = f.readlines()

        output_lines = []
        changes_made = []

        for i, line in enumerate(lines, 1):
            original = line

            # Apply transformations
            line = self.replace_memory_addresses(line)
            line = self.replace_offsets(line)
            line = self.replace_hex_constants(line)

            if line != original:
                changes_made.append((i, original.strip(), line.strip()))

            output_lines.append(line)

        if dry_run:
            print(f"Dry run - {len(changes_made)} changes would be made:")
            for line_num, old, new in changes_made[:20]:  # Show first 20
                print(f"Line {line_num}:")
                print(f"  - {old}")
                print(f"  + {new}")
            if len(changes_made) > 20:
                print(f"  ... and {len(changes_made) - 20} more changes")
        else:
            output_path = output_path or input_path
            with open(output_path, 'w') as f:
                f.writelines(output_lines)
            print(f"Processed {input_path} -> {output_path}")
            print(f"Made {len(changes_made)} changes")

    def interactive_rename(self, input_path: str) -> None:
        """Interactive renaming with user confirmation."""
        print("Interactive mode not yet implemented")
        print("Use --dry-run to preview changes first")


def generate_header_file(mappings_file: str = "variable_mappings.json",
                         output_file: str = "moria_types.h") -> None:
    """Generate C header file with all constants and type definitions."""
    with open(mappings_file, 'r') as f:
        mappings = json.load(f)

    with open(output_file, 'w') as f:
        f.write("/* Auto-generated from variable_mappings.json */\n")
        f.write("#ifndef MORIA_TYPES_H\n")
        f.write("#define MORIA_TYPES_H\n\n")

        # Constants
        f.write("/* Game Constants */\n")
        for name, info in mappings.get('constants', {}).items():
            value = info.get('value')
            desc = info.get('description', '')
            f.write(f"#define {name:20s} {value:5}  /* {desc} */\n")
        f.write("\n")

        # Type definitions
        f.write("/* Type Definitions */\n")
        f.write("typedef unsigned char   undefined;\n")
        f.write("typedef unsigned char   undefined1;\n")
        f.write("typedef unsigned short  undefined2;\n")
        f.write("typedef unsigned long   undefined4;\n")
        f.write("typedef unsigned short  word;\n")
        f.write("typedef undefined4*     far_ptr;\n")
        f.write("typedef char            bool8;\n\n")

        # Structure definitions
        for struct_name, struct_info in mappings.get('structure_offsets', {}).items():
            f.write(f"/* {struct_name.title()} Structure */\n")
            f.write(f"typedef struct {struct_name}_s {{\n")

            for offset, field in sorted(struct_info.get('fields', {}).items(),
                                       key=lambda x: int(x[0], 16)):
                field_type = field.get('type', 'int')
                field_name = field.get('name', 'unknown')
                field_desc = field.get('description', '')
                f.write(f"    {field_type:20s} {field_name:20s}; /* {field_desc} */\n")

            f.write(f"}} {struct_name}_t;\n\n")

        # External declarations for global variables
        f.write("/* Global Variables */\n")
        for category in mappings.get('memory_addresses', {}).values():
            for addr, info in category.items():
                if isinstance(info, dict):
                    var_name = info.get('name')
                    var_type = info.get('type', 'int')
                    desc = info.get('description', '')
                    f.write(f"extern {var_type:20s} {var_name:30s}; /* {desc} */\n")

        f.write("\n#endif /* MORIA_TYPES_H */\n")

    print(f"Generated {output_file}")


def main():
    parser = argparse.ArgumentParser(
        description="Apply variable naming conventions to Moria C code"
    )
    parser.add_argument('input_file', help='Input C source file')
    parser.add_argument('output_file', nargs='?', help='Output file (default: overwrite input)')
    parser.add_argument('--dry-run', action='store_true',
                       help='Show changes without applying')
    parser.add_argument('--interactive', action='store_true',
                       help='Interactive mode with confirmations')
    parser.add_argument('--generate-header', action='store_true',
                       help='Generate moria_types.h header file')
    parser.add_argument('--mappings', default='variable_mappings.json',
                       help='Path to mappings JSON file')

    args = parser.parse_args()

    if args.generate_header:
        generate_header_file(args.mappings)
        return

    if not Path(args.input_file).exists():
        print(f"Error: Input file '{args.input_file}' not found")
        sys.exit(1)

    if not Path(args.mappings).exists():
        print(f"Error: Mappings file '{args.mappings}' not found")
        sys.exit(1)

    mapper = VariableMapper(args.mappings)

    if args.interactive:
        mapper.interactive_rename(args.input_file)
    else:
        mapper.process_file(args.input_file, args.output_file, args.dry_run)


if __name__ == '__main__':
    main()
