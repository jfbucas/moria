#!/usr/bin/python3
"""
Extract and identify magic number constants used as function parameters
"""
import re
from collections import defaultdict

# Read the improved source
with open('reverse/MORIA_improved.C', 'r') as f:
    source = f.read()

print("Analyzing magic number constants...\n")

# Find all function calls with numeric parameters
call_pattern = re.compile(r'(\w+)\s*\(([^)]*)\)')

# Track which numbers are used with which functions
func_params = defaultdict(lambda: defaultdict(int))

for match in call_pattern.finditer(source):
    func_name = match.group(1)
    params = match.group(2)

    # Extract numeric parameters
    numbers = re.findall(r'\b(0x[0-9a-f]+|\d+)\b', params)

    for num in numbers:
        # Skip obvious non-constants (like coordinates that change)
        if num in ['0', '1', '2', '3', '4', '5']:
            continue
        func_params[func_name][num] += 1

# Focus on the most important functions
important_funcs = [
    'check_inventory_has_item',
    'use_item_from_inventory',
    'display_object_info',
    'spawn_monster_from_template',
    'execute_spell_effect',
    'drink_potion_effect',
    'handle_timed_effect',
]

print("="*80)
print("MAGIC NUMBERS BY FUNCTION")
print("="*80)

for func in important_funcs:
    if func in func_params:
        print(f"\n{func}:")
        sorted_params = sorted(func_params[func].items(), key=lambda x: -x[1])
        for param, count in sorted_params[:15]:  # Top 15
            print(f"  {param:10s} - used {count:3d} times")

# Analyze specific patterns
print("\n" + "="*80)
print("ANALYZING check_inventory_has_item CALLS")
print("="*80)

check_item_pattern = re.compile(r'check_inventory_has_item\s*\(\s*(0x[0-9a-f]+|\d+)\s*\)')
item_checks = defaultdict(list)

for match in check_item_pattern.finditer(source):
    item_num = match.group(1)
    # Get context (surrounding line)
    start = max(0, match.start() - 200)
    end = min(len(source), match.end() + 200)
    context = source[start:end]

    # Try to find nearby comments or function names
    context_line = context.split('\n')[0]
    item_checks[item_num].append(context_line[:80])

print("\nItem type usage with context:")
for item_id, contexts in sorted(item_checks.items()):
    print(f"\n0x{item_id} (appears {len(contexts)} times):")
    for ctx in contexts[:3]:  # Show first 3 contexts
        print(f"  ...{ctx.strip()}")

# Look for item type patterns in the load_game_data function
print("\n" + "="*80)
print("SEARCHING FOR ITEM/MONSTER TYPE DEFINITIONS")
print("="*80)

# Find load_game_data and analyze it
load_data_match = re.search(
    r'void.*load_game_data.*?\{(.*?)^\}',
    source,
    re.DOTALL | re.MULTILINE
)

if load_data_match:
    load_body = load_data_match.group(1)

    # Look for loops that read object types
    # Pattern: reading multiple objects with type identifiers
    type_patterns = re.findall(r'iVar\d+\s*\*\s*0x[0-9a-f]+', load_body)

    print(f"Found {len(type_patterns)} potential type definitions in load_game_data")

    # Look for comments or strings near these
    strings_in_load = re.findall(r'"([^"]*)"', load_body)
    if strings_in_load:
        print(f"\nStrings found (might be item/monster names):")
        for s in strings_in_load[:10]:
            print(f"  '{s}'")

# Analyze spell/potion effect IDs
print("\n" + "="*80)
print("SPELL AND POTION EFFECT IDs")
print("="*80)

spell_pattern = re.compile(r'execute_spell_effect.*?case\s+(0x[0-9a-f]+|\d+)\s*:', re.DOTALL)
potion_pattern = re.compile(r'drink_potion_effect.*?case\s+(0x[0-9a-f]+|\d+)\s*:', re.DOTALL)

print("\nSearching for switch cases in effect functions...")

# Find the spell effect function
spell_func = re.search(r'void.*execute_spell_effect.*?\{(.*?)^\}', source, re.DOTALL | re.MULTILINE)
if spell_func:
    spell_body = spell_func.group(1)
    spell_cases = re.findall(r'case\s+(0x[0-9a-f]+|\d+)\s*:', spell_body)
    print(f"\nSpell effect IDs found: {len(spell_cases)}")
    for i, case_id in enumerate(spell_cases[:15], 1):
        print(f"  {case_id:6s} - Spell {i}")

# Find the potion effect function
potion_func = re.search(r'void.*drink_potion_effect.*?\{(.*?)^\}', source, re.DOTALL | re.MULTILINE)
if potion_func:
    potion_body = potion_func.group(1)
    potion_cases = re.findall(r'case\s+(0x[0-9a-f]+|\d+)\s*:', potion_body)
    print(f"\nPotion effect IDs found: {len(potion_cases)}")
    for i, case_id in enumerate(potion_cases[:15], 1):
        print(f"  {case_id:6s} - Potion {i}")

print("\n" + "="*80)
print("RECOMMENDATIONS")
print("="*80)
print("""
Next steps to eliminate magic numbers:
1. Define enums for item types (ITEM_TYPE_*)
2. Define enums for monster types (MONSTER_TYPE_*)
3. Define enums for spell effects (SPELL_*)
4. Define enums for potion effects (POTION_*)
5. Define enums for status effects
6. Replace all numeric literals with named constants

This will require detailed analysis of each category.
""")
