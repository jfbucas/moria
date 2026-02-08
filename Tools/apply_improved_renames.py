#!/usr/bin/python3
"""
Apply improved function renames
"""
import json
import re
import sys

# Load improved renames
with open('improved_renames.json', 'r') as f:
    renames = json.load(f)

print(f"Loaded {len(renames)} improved renames")

if len(sys.argv) < 2:
    print("\nUsage:")
    print("  python3 apply_improved_renames.py --preview  # Show what will change")
    print("  python3 apply_improved_renames.py --apply    # Apply the renames")
    sys.exit(0)

# Read source
with open('reverse/MORIA.C', 'r') as f:
    c_source = f.read()

if sys.argv[1] == '--preview':
    print("\nRename preview:")
    print(f"{'OLD NAME':<30} -> {'NEW NAME':<30}")
    print("-" * 62)
    for old, new in sorted(renames.items())[:30]:
        print(f"{old:<30} -> {new:<30}")
    if len(renames) > 30:
        print(f"... and {len(renames) - 30} more")

elif sys.argv[1] == '--apply':
    print("\nApplying renames...")

    # Apply renames
    modified_source = c_source
    for old_name, new_name in renames.items():
        pattern = r'\b' + re.escape(old_name) + r'\b'
        modified_source = re.sub(pattern, new_name, modified_source)

    # Write output
    output_file = 'reverse/MORIA_renamed.C'
    with open(output_file, 'w') as f:
        f.write(modified_source)

    print(f"\n✓ Renamed source written to: {output_file}")
    print(f"✓ Applied {len(renames)} function renames")

    # Statistics
    print("\nFunction naming summary:")
    print(f"  Total functions:           191")
    print(f"  Renamed automatically:     {len(renames)}")
    print(f"  Need manual naming:        {191 - len(renames)}")
    print(f"  Success rate:              {len(renames)/191*100:.1f}%")
