#!/usr/bin/python3
"""
Apply all function renames to create final MORIA_renamed.C
"""
import json
import re
import sys

print("Loading function names...")
with open('function_names_complete.json', 'r') as f:
    renames = json.load(f)

print(f"Loaded {len(renames)} function renames")

print("Reading MORIA.C...")
with open('reverse/MORIA.C', 'r') as f:
    c_source = f.read()

print(f"File size: {len(c_source):,} bytes")

print("\nApplying renames...")
modified_source = c_source
rename_count = 0

for old_name, new_name in sorted(renames.items()):
    # Use word boundaries to avoid partial matches
    pattern = r'\b' + re.escape(old_name) + r'\b'
    count = len(re.findall(pattern, modified_source))
    if count > 0:
        modified_source = re.sub(pattern, new_name, modified_source)
        rename_count += 1
        if rename_count % 20 == 0:
            print(f"  Processed {rename_count}/{len(renames)}...")

print(f"\nRenamed {rename_count} functions")

output_file = 'reverse/MORIA_renamed.C'
print(f"\nWriting to {output_file}...")
with open(output_file, 'w') as f:
    f.write(modified_source)

print("✓ Complete!")
print(f"\nStatistics:")
print(f"  Total functions in original: 269")
print(f"  Functions renamed: {rename_count}")
print(f"  Coverage: {rename_count/269*100:.1f}%")
print(f"  Output file: {output_file}")
print(f"  Output size: {len(modified_source):,} bytes")
