#!/usr/bin/python3
"""
Extract individual functions for manual analysis
"""
import re
import json

# Read the C source
with open('reverse/MORIA.C', 'r') as f:
    lines = f.readlines()

# Find function boundaries
functions = []
current_func = None
brace_count = 0
in_function = False

for i, line in enumerate(lines):
    line_num = i + 1

    # Check for function definition
    func_match = re.match(r'^([\w\s\*]+?)\s+(FUN_([0-9a-f]+)_([0-9a-f]+))\s*\(([^)]*)\)\s*$', line)

    if func_match and i + 1 < len(lines) and lines[i + 1].strip() == '{':
        # Start of new function
        if current_func:
            functions.append(current_func)

        current_func = {
            'name': func_match.group(2),
            'return_type': func_match.group(1).strip(),
            'params': func_match.group(5).strip(),
            'start_line': line_num,
            'signature': line.strip(),
            'body_lines': []
        }
        in_function = True
        brace_count = 0
        continue

    if in_function:
        # Track braces
        brace_count += line.count('{') - line.count('}')

        current_func['body_lines'].append(line.rstrip())

        # End of function
        if brace_count <= 0 and '}' in line:
            current_func['end_line'] = line_num
            current_func['body'] = '\n'.join(current_func['body_lines'])
            functions.append(current_func)
            current_func = None
            in_function = False

print(f"Extracted {len(functions)} complete functions\n")

# Create individual function files for analysis
import os
os.makedirs('functions', exist_ok=True)

# Also create a manifest
manifest = []

for func in functions:
    # Save each function to its own file
    filename = f"functions/{func['name']}.c"

    with open(filename, 'w') as f:
        f.write(f"// {func['name']}\n")
        f.write(f"// Address: lines {func['start_line']}-{func['end_line']}\n")
        f.write(f"// Signature: {func['return_type']} {func['name']}({func['params']})\n")
        f.write(f"\n")
        f.write(func['body'])

    manifest.append({
        'name': func['name'],
        'file': filename,
        'start_line': func['start_line'],
        'end_line': func['end_line'],
        'signature': func['signature'],
        'return_type': func['return_type'],
        'params': func['params'],
    })

with open('functions/manifest.json', 'w') as f:
    json.dump(manifest, f, indent=2)

print(f"Created individual function files in functions/ directory")
print(f"Manifest saved to functions/manifest.json")

# Show statistics
print(f"\nStatistics:")
print(f"  Total functions: {len(functions)}")

# Count by return type
from collections import Counter
return_types = Counter(f['return_type'] for f in functions)
print(f"\nBy return type:")
for rt, count in return_types.most_common(10):
    print(f"  {rt:20s}: {count}")
