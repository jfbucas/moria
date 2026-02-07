#!/usr/bin/python3
"""
Analyze functions in batches for manual reverse engineering
Creates small, focused files for easier analysis
"""
import re
import json
import os

# Read the C source
with open('reverse/MORIA.C', 'r') as f:
    c_source = f.read()

# Extract function with bodies using the working regex
func_pattern = re.compile(
    r'^([\w\s\*]+?)\s+(FUN_([0-9a-f]+)_([0-9a-f]+))\s*\(([^)]*)\)\s*\n\{(.*?)^\}',
    re.MULTILINE | re.DOTALL
)

functions = []
for match in func_pattern.finditer(c_source):
    return_type = match.group(1).strip()
    func_name = match.group(2)
    segment = match.group(3).upper()
    offset = match.group(4).upper()
    params = match.group(5).strip()
    body = match.group(6)

    line_num = c_source[:match.start()].count('\n') + 1
    end_line = c_source[:match.end()].count('\n') + 1

    functions.append({
        'name': func_name,
        'segment': segment,
        'offset': offset,
        'address': f"{segment}:{offset}",
        'return_type': return_type,
        'params': params,
        'body': body,
        'start_line': line_num,
        'end_line': end_line,
        'full_text': match.group(0)
    })

print(f"Extracted {len(functions)} functions\n")

# Create batches of 20 functions each for easier analysis
os.makedirs('function_batches', exist_ok=True)

batch_size = 20
for i in range(0, len(functions), batch_size):
    batch_num = i // batch_size + 1
    batch = functions[i:i+batch_size]

    filename = f"function_batches/batch_{batch_num:03d}.txt"

    with open(filename, 'w') as f:
        f.write(f"=" * 80 + "\n")
        f.write(f"FUNCTION BATCH {batch_num}\n")
        f.write(f"Functions {i+1} to {min(i+batch_size, len(functions))}\n")
        f.write(f"=" * 80 + "\n\n")

        for j, func in enumerate(batch):
            f.write(f"\n{'='*80}\n")
            f.write(f"[{i+j+1}] {func['name']}\n")
            f.write(f"{'='*80}\n")
            f.write(f"Address: {func['address']}\n")
            f.write(f"Lines: {func['start_line']}-{func['end_line']}\n")
            f.write(f"Signature: {func['return_type']} {func['name']}({func['params']})\n")
            f.write(f"\n")
            f.write(func['full_text'])
            f.write(f"\n\n")
            f.write(f"ANALYSIS:\n")
            f.write(f"Name: _______________________________\n")
            f.write(f"Purpose: \n")
            f.write(f"\n")

print(f"Created {(len(functions) + batch_size - 1) // batch_size} batch files in function_batches/")

# Save manifest
manifest = {
    'total_functions': len(functions),
    'batches': (len(functions) + batch_size - 1) // batch_size,
    'batch_size': batch_size,
    'functions': [{
        'index': i+1,
        'name': f['name'],
        'address': f['address'],
        'lines': f"{f['start_line']}-{f['end_line']}",
        'signature': f"{f['return_type']} {f['name']}({f['params']})",
        'batch': (i // batch_size) + 1
    } for i, f in enumerate(functions)]
}

with open('function_batches/manifest.json', 'w') as f:
    json.dump(manifest, f, indent=2)

print(f"Manifest saved to function_batches/manifest.json")

# Create a summary of interesting functions to prioritize
print(f"\nCreating priority list...")

priority_functions = []

for func in functions:
    body = func['body']

    # Score by interesting patterns
    score = 0

    # Has string literals (likely UI or important messages)
    strings = re.findall(r'"([^"]*)"', body)
    if strings:
        score += len(strings) * 2

    # Accesses specific memory locations (game state)
    if re.search(r'\*\(int \*\)0x[0-9a-f]+', body):
        score += 5

    # Complex logic
    if body.count('if') > 3:
        score += 2

    # Calls many functions
    calls = len(re.findall(r'FUN_[0-9a-f]+_[0-9a-f]+', body))
    score += calls

    if score > 10:
        priority_functions.append((score, func))

priority_functions.sort(key=lambda x: x[0], reverse=True)

print(f"Found {len(priority_functions)} high-priority functions")

with open('function_batches/priority_list.txt', 'w') as f:
    f.write("HIGH PRIORITY FUNCTIONS\n")
    f.write("These functions likely have significant game logic\n")
    f.write("="*80 + "\n\n")

    for score, func in priority_functions[:30]:
        f.write(f"{func['name']:30s} [Score: {score:3d}] Line {func['start_line']}\n")
        strings = re.findall(r'"([^"]*)"', func['body'])
        if strings:
            f.write(f"  Strings: {', '.join(repr(s[:40]) for s in strings[:3])}\n")
        f.write(f"\n")

print("Priority list saved to function_batches/priority_list.txt")
