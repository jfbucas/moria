#!/usr/bin/python3
"""
Analyze function parameters and local variables to suggest better names
"""
import re
from collections import defaultdict

# Read the renamed source
with open('reverse/MORIA_renamed.C', 'r') as f:
    c_source = f.read()

# Extract functions with their parameters and bodies
func_pattern = re.compile(
    r'^([\w\s\*]+?)\s+(\w+)\s*\(([^)]*)\)\s*\n\{(.*?)^\}',
    re.MULTILINE | re.DOTALL
)

print("Analyzing parameters and variables...\n")

# Common patterns to look for
patterns = {
    'coordinates': {
        'patterns': [r'\*\s*(\w+)\s*==\s*0xb86[ce]', r'(\w+)\s*\*\s*0x4f', r'(\w+)\s*==\s*(1|79|23)'],
        'suggestions': {'x_coord', 'y_coord', 'row', 'col', 'position'}
    },
    'pointers': {
        'patterns': [r'\*\s*\(int\s*\*\)\s*(\w+)', r'(\w+)\s*\+\s*0x[0-9a-f]+', r'\*\s*(\w+)\s*='],
        'suggestions': {'ptr', 'obj_ptr', 'item_ptr', 'monster_ptr', 'node_ptr'}
    },
    'counters': {
        'patterns': [r'for\s*\([^;]*(\w+)\s*=\s*0', r'while\s*\(\s*(\w+)\s*[<>]', r'(\w+)\s*\+\+'],
        'suggestions': {'count', 'index', 'i', 'n', 'num_items'}
    },
    'flags': {
        'patterns': [r'if\s*\(\s*(\w+)\s*==\s*[01]\)', r'(\w+)\s*=\s*(true|false|0|1)\s*;'],
        'suggestions': {'flag', 'is_valid', 'found', 'success'}
    },
    'stats': {
        'patterns': [r'0xb87[0-9a-f]', r'0xb88[0-9a-f]'],
        'suggestions': {'hp', 'max_hp', 'strength', 'experience', 'gold', 'stat'}
    },
}

# Analyze each function
function_vars = []
for match in func_pattern.finditer(c_source):
    return_type = match.group(1).strip()
    func_name = match.group(2)
    params = match.group(3).strip()
    body = match.group(4)

    # Extract parameter names
    param_pattern = re.compile(r'(\w+)\s+(\**)(\w+)(?:\s*,|\s*$)')
    param_matches = list(param_pattern.finditer(params))

    # Extract local variables
    local_pattern = re.compile(r'^\s+(\w+(?:\s+\*)?)\s+(\w+)(?:\[.*?\])?;', re.MULTILINE)
    local_matches = list(local_pattern.finditer(body))

    if param_matches or local_matches:
        function_vars.append({
            'name': func_name,
            'return_type': return_type,
            'params': [(m.group(1), m.group(2), m.group(3)) for m in param_matches],
            'locals': [(m.group(1).strip(), m.group(2)) for m in local_matches],
            'body': body,
            'line': c_source[:match.start()].count('\n') + 1
        })

print(f"Found {len(function_vars)} functions with parameters/variables\n")

# Analyze specific high-priority functions
priority_funcs = [
    'main_game_loop',
    'main_game_command_loop',
    'monster_attack_player',
    'execute_player_attack',
    'move_player_in_direction',
    'render_field_of_view',
    'generate_dungeon_level',
    'load_game_data',
]

print("=" * 80)
print("HIGH PRIORITY FUNCTIONS - PARAMETER/VARIABLE ANALYSIS")
print("=" * 80)

for func_data in function_vars[:20]:  # Show first 20
    if any(pf in func_data['name'] for pf in priority_funcs) or func_data['name'].startswith('FUN_'):
        print(f"\n{func_data['name']} (line {func_data['line']})")
        print(f"  Return: {func_data['return_type']}")

        if func_data['params']:
            print(f"  Parameters:")
            for ptype, stars, pname in func_data['params']:
                # Suggest better name based on type
                suggestion = pname
                if 'param' in pname:
                    if 'int' in ptype and '*' not in stars:
                        if '_1' in pname:
                            suggestion = 'value/count/index'
                        elif '_2' in pname or '_3' in pname:
                            suggestion = 'x/y/coord'
                    elif '*' in stars:
                        suggestion = 'ptr/buffer/array'
                print(f"    {ptype}{stars} {pname} → {suggestion}")

        if func_data['locals'][:5]:  # First 5 locals
            print(f"  Local variables (showing first 5):")
            for ltype, lname in func_data['locals'][:5]:
                suggestion = lname
                if 'local' in lname or 'Var' in lname:
                    if 'int' in ltype:
                        suggestion = 'temp/count/index'
                    elif 'char' in ltype:
                        suggestion = 'ch/byte/buffer'
                print(f"    {ltype} {lname} → {suggestion}")

print("\n" + "=" * 80)
print("COMMON VARIABLE PATTERNS DETECTED")
print("=" * 80)

# Count common patterns
param_types = defaultdict(int)
local_types = defaultdict(int)

for func in function_vars:
    for ptype, stars, pname in func['params']:
        if 'param' in pname:
            param_types[ptype + stars] += 1
    for ltype, lname in func['locals']:
        if 'local' in lname or 'Var' in lname:
            local_types[ltype] += 1

print("\nMost common parameter types needing rename:")
for ptype, count in sorted(param_types.items(), key=lambda x: -x[1])[:10]:
    print(f"  {ptype:20s}: {count:4d} occurrences")

print("\nMost common local variable types needing rename:")
for ltype, count in sorted(local_types.items(), key=lambda x: -x[1])[:10]:
    print(f"  {ltype:20s}: {count:4d} occurrences")

print(f"\n\nTotal functions to process: {len(function_vars)}")
print("This will require systematic analysis of each function's context.")
