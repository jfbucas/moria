#!/usr/bin/python3
"""
Apply variable renaming to MORIA_renamed.C based on analysis
Creates MORIA_final.C with better variable names
"""
import json
import re

print("Loading naming guide...")
with open('variable_naming_guide.json', 'r') as f:
    guide = json.load(f)

print("Reading source...")
with open('reverse/MORIA_renamed.C', 'r') as f:
    source = f.read()

# Apply specific function renamings first
print("\nApplying function-specific variable renames...")
func_specific = guide['function_specific']

for func_name, var_map in func_specific.items():
    # Find the function in source
    func_pattern = rf'(\w+\s+\**{re.escape(func_name)}\s*\([^)]*\)\s*\n\{{)'
    match = re.search(func_pattern, source)

    if match:
        # Find function body (simplified - just rename in next 1000 chars)
        start = match.start()
        # Find the closing brace (simplified)
        end = start + 5000  # Process next 5000 chars

        func_section = source[start:end]
        modified_section = func_section

        for old_var, new_var in var_map.items():
            # Use word boundaries
            pattern = r'\b' + re.escape(old_var) + r'\b'
            modified_section = re.sub(pattern, new_var, modified_section)

        source = source[:start] + modified_section + source[end:]
        print(f"  ✓ {func_name}: renamed {len(var_map)} variables")

# Apply memory address comment hints
print("\nAdding memory address hints...")
mem_addresses = guide['memory_addresses']
address_count = 0

for addr, name in mem_addresses.items():
    # Find patterns like *(int *)0xb86c
    pattern = rf'(\*\s*\(\s*\w+\s*\*\s*\)\s*{re.escape(addr)})'
    matches = re.findall(pattern, source)

    if matches:
        # Add comment after the expression
        source = re.sub(
            pattern,
            rf'\1 /* {name} */',
            source
        )
        address_count += len(matches)

print(f"  ✓ Added {address_count} memory address hints")

# Apply common constant replacements
print("\nReplacing magic numbers with constants...")
constants = guide['constants']
const_count = 0

# Only replace in specific contexts to avoid breaking things
for const_val, const_name in constants.items():
    # Replace in comparisons and arithmetic
    patterns = [
        (rf'==\s*{re.escape(const_val)}\b', f'== {const_name}'),
        (rf'<\s*{re.escape(const_val)}\b', f'< {const_name}'),
        (rf'>\s*{re.escape(const_val)}\b', f'> {const_name}'),
        (rf'\*\s*{re.escape(const_val)}\b', f'* {const_name}'),
    ]

    for pattern, replacement in patterns:
        count = len(re.findall(pattern, source))
        if count > 0:
            source = re.sub(pattern, replacement, source)
            const_count += count

print(f"  ✓ Replaced {const_count} magic numbers")

# Write output
output_file = 'reverse/MORIA_final.C'
print(f"\nWriting to {output_file}...")

with open(output_file, 'w') as f:
    f.write(source)

print("✓ Complete!")
print(f"\nOutput: {output_file}")
print(f"Size: {len(source):,} bytes")

print("\n" + "="*80)
print("SUMMARY")
print("="*80)
print("✓ Function-specific variables renamed in key functions")
print("✓ Memory address hints added as comments")
print("✓ Magic numbers replaced with named constants")
print("\nNext steps:")
print("  1. Review MORIA_final.C")
print("  2. Manually refine remaining generic variable names")
print("  3. Add structure definitions for game objects")
