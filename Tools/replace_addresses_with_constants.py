#!/usr/bin/python3
"""
Replace all memory address literals with proper constants
Converts patterns like:
  *(int *)0xb86c /* player_y */
to:
  *(int *)ADDR_PLAYER_Y /* player_y */

Or better yet, to the global variable macro:
  player_y
"""
import re

# Read the source
with open('reverse/MORIA.C', 'r') as f:
    source = f.read()

# Define all address to constant name mappings
# Format: (address, constant_name, is_pointer)
address_mappings = [
    # Player position
    (0xb86c, 'ADDR_PLAYER_Y', True),
    (0xb86e, 'ADDR_PLAYER_X', True),

    # Player stats
    (0xb870, 'ADDR_CURRENT_HP', True),
    (0xb872, 'ADDR_MAX_HP', True),
    (0xb874, 'ADDR_CURRENT_FOOD', True),  # Was MAX_MANA - FIXED!
    (0xb876, 'ADDR_MAX_FOOD', True),       # Was MAX_MANA - FIXED!
    (0xb878, 'ADDR_STRENGTH', True),
    (0xb87a, 'ADDR_INTELLIGENCE', True),
    (0xb87c, 'ADDR_WISDOM', True),
    (0xb87e, 'ADDR_DEXTERITY', True),
    (0xb880, 'ADDR_BASE_AC', True),
    (0xb882, 'ADDR_CONSTITUTION', True),
    (0xb886, 'ADDR_EXPERIENCE', True),
    (0xb888, 'ADDR_PLAYER_LEVEL', True),
    (0xb892, 'ADDR_TURN_COUNT', True),
    (0xb8c8, 'ADDR_GOLD_LOW', True),
    (0xb8ca, 'ADDR_GOLD_HIGH', True),

    # Player status flags
    (0xb8ec, 'ADDR_IS_PARALYZED', True),
    (0xb8ed, 'ADDR_IS_BLIND', True),
    (0xb8ee, 'ADDR_NEEDS_UPDATE', True),
    (0xb8ef, 'ADDR_SPEED_ACTIVE', True),
    (0xb8f0, 'ADDR_CONFUSION_LOCK', True),
    (0xb8f1, 'ADDR_STATUS_FLAG_1', True),
    (0xb8f2, 'ADDR_IS_TELEPORTING', True),
    (0xb8f3, 'ADDR_STATUS_FLAG_3', True),
    (0xb8f5, 'ADDR_STATUS_FLAG_5', True),
    (0xb8f6, 'ADDR_IS_WIZARD', True),
    (0xb8f7, 'ADDR_IS_STUNNED', True),
    (0xb8f8, 'ADDR_TELEPORT_FLAG', True),
    (0xb913, 'ADDR_HALLUCINATION', True),
    (0xb915, 'ADDR_IS_DYING', True),
    (0xb916, 'ADDR_IS_HASTED', True),
    (0xb918, 'ADDR_HAS_LIGHT', True),
    (0xb919, 'ADDR_IS_CONFUSED', True),

    # Timers
    (0xb8f9, 'ADDR_PARALYZE_TIMER', True),
    (0xb8fb, 'ADDR_BLIND_TIMER', True),
    (0xb8fd, 'ADDR_DETECT_TIMER', True),
    (0xb8ff, 'ADDR_SPEED_TIMER', True),
    (0xb901, 'ADDR_HALLUC_TIMER', True),
    (0xb903, 'ADDR_STATUS_TIMER_1', True),
    (0xb905, 'ADDR_TELEPORT_TIMER', True),
    (0xb907, 'ADDR_STATUS_TIMER_3', True),
    (0xb909, 'ADDR_FOOD_LEVEL', True),
    (0xb90b, 'ADDR_STATUS_TIMER_5', True),
    (0xb90d, 'ADDR_WIZARD_TIMER', True),
    (0xb911, 'ADDR_EFFECT_TIMER_16', True),
    (0xb91a, 'ADDR_DEATH_TIMER', True),
    (0xb91c, 'ADDR_HASTE_TIMER', True),

    # Inventory & Equipment
    (0xb91e, 'ADDR_INVENTORY_LIST', True),
    (0xb922, 'ADDR_WIELDED_WEAPON', True),
    (0xb926, 'ADDR_EQUIPPED_SHIELD', True),
    (0xb92a, 'ADDR_EQUIPPED_ARMOR', True),
    (0xb92e, 'ADDR_EQUIPPED_RING1', True),
    (0xb932, 'ADDR_EQUIPPED_RING2', True),

    # World state
    (0xe52d, 'ADDR_DUNGEON_LEVEL', True),
    (0xe535, 'ADDR_MIN_VISIBLE_ROW', True),
    (0xe537, 'ADDR_MAX_VISIBLE_ROW', True),
]

# Sort by address (descending) to replace longer hex values first
address_mappings.sort(key=lambda x: -x[0])

print("="*80)
print("REPLACING MEMORY ADDRESSES WITH CONSTANTS")
print("="*80)
print()

modified = source
total_replacements = 0

for addr, const_name, is_pointer in address_mappings:
    hex_addr = f"0x{addr:x}"

    # Pattern: 0xADDR /* comment */
    # Replace with: CONST_NAME /* comment */
    pattern = rf'{hex_addr}\s*/\*[^*]*\*/'

    matches = list(re.finditer(pattern, modified))
    if matches:
        count = len(matches)

        # Replace each match
        for match in reversed(matches):  # Reverse to maintain positions
            comment = re.search(r'/\*([^*]*)\*/', match.group()).group()
            replacement = f"{const_name} {comment}"
            modified = modified[:match.start()] + replacement + modified[match.end():]

        total_replacements += count
        print(f"{const_name:30s} ({hex_addr}): {count:4d} replacements")

    # Also replace bare addresses without comments (but be more careful)
    # Pattern: 0xADDR (not followed by /*)
    bare_pattern = rf'{hex_addr}(?!\s*/\*)'
    bare_matches = list(re.finditer(bare_pattern, modified))

    if bare_matches:
        # Be more selective - only replace if it looks like a memory access
        for match in reversed(bare_matches):
            # Check context - should be in a pointer dereference or similar
            start = max(0, match.start() - 20)
            context = modified[start:match.start()]

            # Replace if it's clearly a memory reference
            if any(indicator in context for indicator in ['*(', '(int *)', '(char *)', '(undefined']):
                replacement = const_name
                modified = modified[:match.start()] + replacement + modified[match.end():]
                total_replacements += 1

print()
print("="*80)
print(f"Total replacements: {total_replacements}")
print("="*80)

# Fix specific mana → food comments
print("\nFixing mana → food terminology...")

mana_fixes = [
    (r'/\* current_mana \*/', '/* current_food */'),
    (r'/\* max_mana \*/', '/* max_food */'),
    (r'ADDR_CURRENT_MANA', 'ADDR_CURRENT_FOOD'),
    (r'ADDR_MAX_MANA', 'ADDR_MAX_FOOD'),
]

for pattern, replacement in mana_fixes:
    count = len(re.findall(pattern, modified))
    if count > 0:
        modified = re.sub(pattern, replacement, modified)
        print(f"  Fixed {count} instances of '{pattern}'")

# Add header includes at the top
header_include = '''/* Moria Game - Reverse Engineered with Proper Constants
 *
 * This version includes:
 * - All memory addresses replaced with named constants
 * - Fixed food/satiation system (was incorrectly labeled as "mana")
 * - Improved readability with ADDR_* constants
 *
 * Include moria_constants.h to compile this file
 */

#include "moria_constants.h"

'''

# Find the first typedef and insert before it
typedef_pos = modified.find('typedef')
if typedef_pos > 0:
    modified = modified[:typedef_pos] + header_include + modified[typedef_pos:]
else:
    # Insert at beginning if no typedef found
    modified = header_include + modified

# Write output
output_file = 'reverse/MORIA_with_constants.C'
with open(output_file, 'w') as f:
    f.write(modified)

print()
print("="*80)
print(f"✓ Created: {output_file}")
print(f"  Size: {len(modified):,} bytes")
print()
print("This file uses ADDR_* constants instead of raw memory addresses.")
print("For the version with global variable macros, use: MORIA_with_globals.C")
print("="*80)

# Create a summary document
with open('CONSTANTS_REPLACEMENT_SUMMARY.md', 'w') as f:
    f.write("# Memory Address Constants Replacement Summary\n\n")
    f.write("## Overview\n\n")
    f.write(f"Replaced **{total_replacements}** raw memory addresses with named constants.\n\n")
    f.write("## Files\n\n")
    f.write("- **Input**: `reverse/MORIA.C` (original with raw addresses)\n")
    f.write("- **Output**: `reverse/MORIA_with_constants.C` (with ADDR_* constants)\n")
    f.write("- **Constants**: `moria_constants.h` (constant definitions)\n\n")
    f.write("## Example Improvements\n\n")
    f.write("### Before:\n")
    f.write("```c\n")
    f.write("if (*(int *)0xb870 /* current_hp */ < *(int *)0xb872 /* max_hp */) {\n")
    f.write("  *(int *)0xb874 /* current_mana */ = *(int *)0xb874 /* current_mana */ + 1;\n")
    f.write("}\n")
    f.write("```\n\n")
    f.write("### After:\n")
    f.write("```c\n")
    f.write("if (*(int *)ADDR_CURRENT_HP /* current_hp */ < *(int *)ADDR_MAX_HP /* max_hp */) {\n")
    f.write("  *(int *)ADDR_CURRENT_FOOD /* current_food */ = *(int *)ADDR_CURRENT_FOOD /* current_food */ + 1;\n")
    f.write("}\n")
    f.write("```\n\n")
    f.write("### Even Better (with moria_globals.h):\n")
    f.write("```c\n")
    f.write("if (current_hp < max_hp) {\n")
    f.write("  current_food = current_food + 1;\n")
    f.write("}\n")
    f.write("```\n\n")
    f.write("## Major Fixes\n\n")
    f.write("### Food System (Previously Mislabeled)\n")
    f.write("- `0xb874` was labeled `current_mana` → now `ADDR_CURRENT_FOOD`\n")
    f.write("- `0xb876` was labeled `max_mana` → now `ADDR_MAX_FOOD`\n\n")
    f.write("**Moria has NO mana system!** It uses food/satiation instead.\n\n")
    f.write("## All Replaced Addresses\n\n")
    f.write("| Address | Constant Name | Description |\n")
    f.write("|---------|---------------|-------------|\n")

    for addr, const_name, _ in sorted(address_mappings, key=lambda x: x[0]):
        desc = const_name.replace('ADDR_', '').replace('_', ' ').title()
        f.write(f"| 0x{addr:04x} | {const_name:30s} | {desc} |\n")

print("✓ Summary saved to: CONSTANTS_REPLACEMENT_SUMMARY.md")
