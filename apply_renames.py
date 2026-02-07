#!/usr/bin/python3
"""
Apply function renames to MORIA.C based on function_analysis.json
"""
import json
import re
import sys

# Load the analysis
with open('function_analysis.json', 'r') as f:
    analysis = json.load(f)

# Read the C source
with open('reverse/MORIA.C', 'r') as f:
    c_source = f.read()

# Build rename mapping
renames = {}
for func in analysis['functions']:
    if func.get('suggested_name'):
        old_name = func['name']
        suggested = func['suggested_name']

        # Clean up the name to be a valid C identifier
        # Remove accents and special chars
        clean_name = suggested
        # Remove common patterns that are too verbose
        clean_name = clean_name.replace('_et_', '_')
        clean_name = clean_name.replace('monte_attaque', 'attack')
        clean_name = clean_name.replace('personnage_standard', 'char_creation')
        clean_name = clean_name[:40]  # Limit length

        renames[old_name] = clean_name

print(f"Prepared {len(renames)} renames")
print("\nSample renames:")
for i, (old, new) in enumerate(list(renames.items())[:10]):
    print(f"  {old:30s} -> {new}")

if len(sys.argv) > 1 and sys.argv[1] == '--dry-run':
    print("\nDry run mode - no changes made")
    print("\nTo apply renames, run: python3 apply_renames.py --apply")
    sys.exit(0)

if len(sys.argv) > 1 and sys.argv[1] == '--apply':
    print("\nApplying renames...")

    # Apply renames
    modified_source = c_source
    for old_name, new_name in renames.items():
        # Use word boundaries to avoid partial matches
        pattern = r'\b' + re.escape(old_name) + r'\b'
        modified_source = re.sub(pattern, new_name, modified_source)

    # Write to new file
    output_file = 'reverse/MORIA_renamed.C'
    with open(output_file, 'w') as f:
        f.write(modified_source)

    print(f"\nRenamed source written to: {output_file}")
    print(f"Applied {len(renames)} function renames")

    # Show some statistics
    print("\nStatistics:")
    print(f"  Total functions: {analysis['total_functions']}")
    print(f"  Renamed: {len(renames)}")
    print(f"  Remaining: {analysis['total_functions'] - len(renames)}")
else:
    print("\nUsage:")
    print("  python3 apply_renames.py --dry-run   # Preview changes")
    print("  python3 apply_renames.py --apply     # Apply renames")
