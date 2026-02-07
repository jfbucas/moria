#!/usr/bin/python3
"""
Interactive function renamer - review and approve each rename
"""
import json
import re
import sys

# Load the analysis
with open('function_analysis.json', 'r') as f:
    analysis = json.load(f)

# Load the C source for context
with open('reverse/MORIA.C', 'r') as f:
    c_lines = f.readlines()

print("=" * 80)
print("INTERACTIVE FUNCTION RENAMER")
print("=" * 80)
print("\nFor each function, you can:")
print("  [ENTER]  - Accept suggested name")
print("  [type]   - Enter a custom name")
print("  [s]      - Skip this function")
print("  [q]      - Quit and save renames so far")
print()

approved_renames = {}

# Filter to functions with suggestions
functions_to_review = [f for f in analysis['functions'] if f.get('suggested_name')]

print(f"Reviewing {len(functions_to_review)} functions with suggestions...\n")

for i, func in enumerate(functions_to_review):
    print(f"\n[{i+1}/{len(functions_to_review)}] " + "=" * 60)
    print(f"Function: {func['name']}")
    print(f"Address:  {func['address']}")
    print(f"Line:     {func['line']}")

    # Show the function signature
    line_num = func['line'] - 1
    if 0 <= line_num < len(c_lines):
        print(f"\nSignature:")
        # Show a few lines of context
        for j in range(max(0, line_num), min(len(c_lines), line_num + 3)):
            print(f"  {c_lines[j].rstrip()}")

    # Show execution contexts
    if func.get('contexts'):
        print(f"\nExecution contexts:")
        for ctx, count in func['contexts'][:5]:
            print(f"  • {ctx} ({count} times)")

    # Show suggestion
    suggested = func['suggested_name']
    print(f"\nSuggested name: {suggested}")

    # Get user input
    choice = input("\nYour choice [ENTER=accept, custom name, s=skip, q=quit]: ").strip()

    if choice.lower() == 'q':
        print("\nQuitting...")
        break
    elif choice.lower() == 's':
        print("Skipped")
        continue
    elif choice == '':
        # Accept suggestion
        approved_renames[func['name']] = suggested
        print(f"✓ Approved: {func['name']} -> {suggested}")
    else:
        # Custom name
        # Validate it's a valid C identifier
        if re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', choice):
            approved_renames[func['name']] = choice
            print(f"✓ Custom: {func['name']} -> {choice}")
        else:
            print(f"✗ Invalid C identifier: {choice}")
            print("Skipped")

print("\n" + "=" * 80)
print(f"Review complete! Approved {len(approved_renames)} renames")
print("=" * 80)

if approved_renames:
    # Save the approved renames
    with open('approved_renames.json', 'w') as f:
        json.dump(approved_renames, f, indent=2)
    print(f"\nApproved renames saved to: approved_renames.json")

    # Optionally apply them
    apply = input("\nApply these renames now? [y/N]: ").strip().lower()
    if apply == 'y':
        # Read source
        with open('reverse/MORIA.C', 'r') as f:
            c_source = f.read()

        # Apply renames
        modified_source = c_source
        for old_name, new_name in approved_renames.items():
            pattern = r'\b' + re.escape(old_name) + r'\b'
            modified_source = re.sub(pattern, new_name, modified_source)

        # Write output
        output_file = 'reverse/MORIA_renamed.C'
        with open(output_file, 'w') as f:
            f.write(modified_source)

        print(f"\n✓ Renamed source written to: {output_file}")
    else:
        print("\nRenames saved but not applied.")
        print("To apply later, use the approved_renames.json file")
else:
    print("\nNo renames approved")
