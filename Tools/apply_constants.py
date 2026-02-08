#!/usr/bin/python3
"""
Apply named constants to replace magic numbers in function calls
"""
import re

# Read the improved source
with open('reverse/MORIA_improved.C', 'r') as f:
    source = f.read()

# Define replacements
replacements = {
    # Item types in check_inventory_has_item calls
    r'check_inventory_has_item\(0x12\)': 'check_inventory_has_item(ITEM_LEVITATION)',
    r'check_inventory_has_item\(0x13\)': 'check_inventory_has_item(ITEM_DRAIN_STAT)',
    r'check_inventory_has_item\(0x11\)': 'check_inventory_has_item(ITEM_LAMP)',
    r'check_inventory_has_item\(0xb\)': 'check_inventory_has_item(ITEM_CURSED_SPECIAL)',
    r'check_inventory_has_item\(6\)': 'check_inventory_has_item(ITEM_LIGHT_SOURCE)',
    r'check_inventory_has_item\(9\)': 'check_inventory_has_item(ITEM_FOOD)',
    r'check_inventory_has_item\(0xd\)': 'check_inventory_has_item(ITEM_UNKNOWN_D)',
    r'check_inventory_has_item\(0xe\)': 'check_inventory_has_item(ITEM_UNKNOWN_E)',
    r'check_inventory_has_item\(0x10\)': 'check_inventory_has_item(ITEM_UNKNOWN_10)',

    # decrement_item_quantity calls
    r'decrement_item_quantity\(0x12\)': 'decrement_item_quantity(ITEM_LEVITATION)',
    r'decrement_item_quantity\(0x13\)': 'decrement_item_quantity(ITEM_DRAIN_STAT)',

    # Monster spawning
    r'spawn_monster_from_template\(0x22\)': 'spawn_monster_from_template(MONSTER_TYPE_22)',
    r'spawn_monster_from_template\(0x23\)': 'spawn_monster_from_template(MONSTER_TYPE_23)',
    r'spawn_monster_from_template\(0x1f\)': 'spawn_monster_from_template(MONSTER_TYPE_1F)',
    r'spawn_monster_from_template\(0x1d\)': 'spawn_monster_from_template(MONSTER_TYPE_1D)',
    r'spawn_monster_from_template\(0x1e\)': 'spawn_monster_from_template(MONSTER_TYPE_1E)',
    r'spawn_monster_from_template\(0x20\)': 'spawn_monster_from_template(MONSTER_TYPE_20)',

    # Attack types
    r'== 0x45\b': '== ATTACK_FEAR',
    r'== 0x46\b': '== ATTACK_STEAL_ITEM',
    r'== 0x47\b': '== ATTACK_ACID_1',
    r'== 0x48\b': '== ATTACK_CONFUSE',
    r'== 0x4d\b': '== ATTACK_REMOVE_MAGIC',
    r'== 0x4e\b': '== ATTACK_ACID_2',
    r'== 0x56\b': '== ATTACK_STEAL_GOLD',
    r'== 0x73\b': '== ATTACK_DRAIN_EXP',
    r'== 0x9c\b': '== ATTACK_DRAIN_STR',
    r'== 0x9e\b': '== ATTACK_DRAIN_CON',
    r'== 0xe8\b': '== ATTACK_GHOST_1',
    r'== 0xea\b': '== ATTACK_GHOST_2',

    # Common numeric patterns (only in specific contexts)
    r'% 20 ==': '% SPAWN_INTERVAL ==',
    r'< 4000': '< TURN_THRESHOLD',

    # Command keys (in comparisons)
    r"== '2'": '== CMD_MOVE_DOWN',
    r"== '4'": '== CMD_MOVE_LEFT',
    r"== '6'": '== CMD_MOVE_RIGHT',
    r"== '8'": '== CMD_MOVE_UP',
    r"== '<'": '== CMD_STAIRS_UP',
    r"== '>'": '== CMD_STAIRS_DOWN',
    r"== 'q'": '== CMD_QUIT',
    r"== '\?'": '== CMD_HELP',
    r"== 'i'": '== CMD_INVENTORY',
    r"== 'e'": '== CMD_EQUIPMENT',
    r"== 's'": '== CMD_SEARCH',
    r"== 'm'": '== CMD_CAST_SPELL',
    r'== 0x13\b(?!.*/)': '== CMD_SAVE',  # Ctrl+S (avoid in comments)
}

modified = source
count = 0

print("Applying named constants...")
for pattern, replacement in replacements.items():
    matches = len(re.findall(pattern, modified))
    if matches > 0:
        modified = re.sub(pattern, replacement, modified)
        count += matches
        print(f"  {replacement.split('(')[1] if '(' in replacement else replacement:30s}: {matches:3d} replacements")

print(f"\nTotal replacements: {count}")

# Add header include at top
header_include = '''/* Moria Game - Reverse Engineered and Improved
 *
 * This version includes:
 * - Named functions (229/269 = 85% coverage)
 * - Meaningful variable names (497+ improvements)
 * - Memory address documentation
 * - Named constants replacing magic numbers
 *
 * See moria_constants.h for all constant definitions
 */

#include "moria_constants.h"

'''

# Find the first typedef and insert before it
typedef_pos = modified.find('typedef')
if typedef_pos > 0:
    modified = modified[:typedef_pos] + header_include + modified[typedef_pos:]

# Write output
output_file = 'reverse/MORIA_final_constants.C'
with open(output_file, 'w') as f:
    f.write(modified)

print(f"\n✓ Created: {output_file}")
print(f"  Size: {len(modified):,} bytes")
print(f"\nAlso created: moria_constants.h")
print("\nBoth files should be used together.")
