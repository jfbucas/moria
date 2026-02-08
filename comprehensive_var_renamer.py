#!/usr/bin/python3
"""
Comprehensive variable renamer - analyzes context and renames intelligently
"""
import re
import json

def analyze_variable_usage(var_name, func_body):
    """Analyze how a variable is used to suggest a better name"""

    # Check for coordinate patterns
    if re.search(rf'{var_name}\s*\*\s*(0x4f|79|80)', func_body):
        return 'y_coord'
    if re.search(rf'(0x4f|79|80)\s*\*\s*{var_name}', func_body):
        return 'x_coord'

    # Check for loop counters
    if re.search(rf'for\s*\([^;]*{var_name}\s*=\s*0', func_body):
        return 'i'
    if re.search(rf'{var_name}\s*\+\+', func_body):
        return 'counter'

    # Check for pointer patterns
    if re.search(rf'\*\s*{var_name}', func_body):
        return 'ptr'
    if re.search(rf'{var_name}\s*->', func_body):
        return 'obj_ptr'

    # Check for boolean patterns
    if re.search(rf'{var_name}\s*==\s*(0|1|true|false)', func_body):
        return 'flag'

    # Check for random/damage patterns
    if re.search(rf'{var_name}\s*=.*random', func_body):
        return 'random_val'
    if re.search(rf'{var_name}.*hp|damage|hit', func_body, re.I):
        return 'damage'

    return None

def get_better_local_name(var_name, var_type, func_body):
    """Generate better name for local variable"""

    # Context-based analysis
    suggestion = analyze_variable_usage(var_name, func_body)
    if suggestion:
        return suggestion

    # Type-based defaults
    if 'int' in var_type and '*' not in var_type:
        if 'local_' in var_name:
            return 'temp_int'
        return 'value'
    elif 'char' in var_type and '*' not in var_type:
        return 'ch'
    elif '*' in var_type:
        return 'ptr'
    elif 'bool' in var_type:
        return 'flag'

    return var_name  # Keep original if no better option

def get_better_param_name(param_type, param_name, param_index, func_body):
    """Generate better name for parameter"""

    # Check common patterns
    if param_index == 1:  # param_1
        if 'int' in param_type and '*' not in param_type:
            # Check if used as coordinate
            if re.search(r'param_1\s*\*\s*(0x4f|79)', func_body):
                return 'y_pos'
            if '0xb86' in func_body:  # Player position check
                return 'x_pos'
            return 'value'
        elif '*' in param_type:
            return 'result_ptr'

    elif param_index == 2:  # param_2
        if 'int' in param_type:
            # Often second coord
            if 'param_1.*0x4f' in func_body or '0x4f.*param_1' in func_body:
                return 'x_pos'
            return 'count'

    elif param_index == 3:  # param_3
        return 'flags'

    elif param_index == 4:  # param_4
        if '*' in param_type:
            return 'data_ptr'

    return param_name

print("Loading source file...")
with open('reverse/MORIA_final.C', 'r') as f:
    source = f.read()

print("Extracting functions...")
func_pattern = re.compile(
    r'^([\w\s\*]+?)\s+(\w+)\s*\(([^)]*)\)\s*\n\{(.*?)^\}',
    re.MULTILINE | re.DOTALL
)

renamed_count = 0
param_count = 0
local_count = 0

modified_source = source

for match in func_pattern.finditer(source):
    return_type = match.group(1).strip()
    func_name = match.group(2)
    params_str = match.group(3).strip()
    body = match.group(4)
    full_func = match.group(0)

    # Skip if already well-named (no param_ or local_)
    if 'param_' not in full_func and 'local_' not in full_func:
        continue

    modified_func = full_func

    # Rename parameters
    if params_str and 'param_' in params_str:
        param_pattern = re.compile(r'(\w+\s+\**)(param_(\d+))')
        for pm in param_pattern.finditer(params_str):
            param_type = pm.group(1).strip()
            old_name = pm.group(2)
            param_num = int(pm.group(3))

            new_name = get_better_param_name(param_type, old_name, param_num, body)

            if new_name != old_name:
                # Replace in function
                modified_func = re.sub(r'\b' + old_name + r'\b', new_name, modified_func)
                param_count += 1

    # Rename local variables (only obvious ones)
    local_pattern = re.compile(r'^\s+(\w+(?:\s+\*)?)\s+(local_[0-9a-f]+|[iucbp]Var\d+)(\[.*?\])?;', re.MULTILINE)
    for lm in local_pattern.finditer(body):
        var_type = lm.group(1).strip()
        old_name = lm.group(2)
        array_spec = lm.group(3) or ''

        # Skip if it's a complex type
        if len(var_type.split()) > 3:
            continue

        new_name = get_better_local_name(old_name, var_type, body)

        if new_name != old_name and new_name not in ['ptr', 'temp_int']:  # Skip generic names
            # Only rename if used less than 20 times (avoid renaming heavily used vars)
            usage_count = len(re.findall(r'\b' + re.escape(old_name) + r'\b', body))
            if usage_count < 20:
                modified_func = re.sub(r'\b' + old_name + r'\b', new_name, modified_func)
                local_count += 1

    if modified_func != full_func:
        modified_source = modified_source.replace(full_func, modified_func, 1)
        renamed_count += 1

        if renamed_count % 20 == 0:
            print(f"  Processed {renamed_count} functions...")

print(f"\n✓ Renamed variables in {renamed_count} functions")
print(f"  - Parameters: {param_count}")
print(f"  - Locals: {local_count}")

output_file = 'reverse/MORIA_improved.C'
print(f"\nWriting to {output_file}...")
with open(output_file, 'w') as f:
    f.write(modified_source)

print("✓ Complete!")
print(f"\nCreated: {output_file}")
print(f"Size: {len(modified_source):,} bytes")
