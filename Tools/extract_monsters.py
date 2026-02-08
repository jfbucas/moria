#!/usr/bin/python3
"""
Extract monster data from Moria memory dump
Based on spawn_monster_from_template function analysis
"""
import struct

# Monster template structure (42 bytes = 0x2a)
# From spawn_monster_from_template analysis:
# offset +0x00: char - display character / monster type
# offset +0x02: int - template ID (redundant with count)
# offset +0x04: int - true form
# offset +0x06: word - monster level (or AC)
# offset +0x08: word - monster level
# offset +0x0a: word - HP
# offset +0x0c: word - unknown
# offset +0x0e: word - num_attacks
# offset +0x10: word - unknown
# offset +0x12: word - unknown
# offset +0x14: word - damage
# offset +0x16: word - spawn_chance or item_drop
# offset +0x18: word - item_carried type
# offset +0x1a: word - unknown
# offset +0x27: char - unknown flag
# offset +0x28: char - unknown
# offset +0x29: char - unknown

MONSTER_TEMPLATE_SIZE = 0x2a  # 42 bytes

def extract_monster_template(data, offset):
    """Extract a single monster template"""
    try:
        # Read the template data (42 bytes)
        template_data = data[offset:offset+MONSTER_TEMPLATE_SIZE]
        if len(template_data) < MONSTER_TEMPLATE_SIZE:
            return None

        # Parse fields (little-endian)
        monster = {
            'offset': f'0x{offset:05x}',
            'display_char': chr(template_data[0]) if 32 <= template_data[0] <= 126 else f'0x{template_data[0]:02x}',
            'true_form': chr(template_data[1]) if 32 <= template_data[1] <= 126 else f'0x{template_data[1]:02x}',
            'template_id': struct.unpack('<H', template_data[2:4])[0],
            'true_form_id': struct.unpack('<H', template_data[4:6])[0],
            'level_or_ac': struct.unpack('<H', template_data[6:8])[0],
            'monster_level': struct.unpack('<H', template_data[8:10])[0],
            'hp': struct.unpack('<H', template_data[10:12])[0],
            'unknown_0c': struct.unpack('<H', template_data[12:14])[0],
            'num_attacks': struct.unpack('<H', template_data[14:16])[0],
            'unknown_10': struct.unpack('<H', template_data[16:18])[0],
            'unknown_12': struct.unpack('<H', template_data[18:20])[0],
            'damage': struct.unpack('<H', template_data[20:22])[0],
            'spawn_chance': struct.unpack('<H', template_data[22:24])[0],
            'item_carried': struct.unpack('<H', template_data[24:26])[0],
            'unknown_1a': struct.unpack('<H', template_data[26:28])[0],
            'flag_27': template_data[39],
            'flag_28': template_data[40],
            'flag_29': template_data[41],
        }

        return monster
    except:
        return None

def search_for_monster_templates(data):
    """Search for monster template data in memory dump"""

    # Look for regions that might contain monster templates
    # Monster templates are likely stored sequentially

    # Strategy: Look for patterns of increasing template IDs
    candidates = []

    for start_offset in range(0, len(data) - MONSTER_TEMPLATE_SIZE * 10, 100):
        # Try to extract 5 consecutive templates
        templates = []
        for i in range(5):
            offset = start_offset + (i * MONSTER_TEMPLATE_SIZE)
            monster = extract_monster_template(data, offset)
            if monster:
                templates.append(monster)

        # Check if this looks like valid monster data
        if len(templates) == 5:
            # Check for patterns that indicate monster templates:
            # 1. Template IDs should be sequential or reasonable
            # 2. Monster levels should be 1-50
            # 3. HP should be positive and reasonable
            valid = True
            for m in templates:
                if m['monster_level'] > 100 or m['hp'] > 10000:
                    valid = False
                    break

            if valid:
                candidates.append((start_offset, templates))

    return candidates

def extract_pascal_strings_near(data, offset, radius=1000, min_len=3, max_len=30):
    """Extract Pascal strings near a given offset"""
    strings = []
    start = max(0, offset - radius)
    end = min(len(data), offset + radius)

    i = start
    while i < end - 1:
        length = data[i]
        if min_len <= length <= max_len and i + 1 + length <= len(data):
            try:
                text = data[i+1:i+1+length].decode('latin-1', errors='ignore')
                if sum(1 for c in text if c.isprintable()) >= len(text) * 0.8:
                    strings.append({
                        'offset': f'0x{i:05x}',
                        'rel_offset': i - offset,
                        'length': length,
                        'text': text.strip()
                    })
            except:
                pass
        i += 1

    return strings

# Read memory dump
with open('reverse/memory.dump', 'rb') as f:
    data = f.read()

print("="*80)
print("MORIA MONSTER EXTRACTION FROM MEMORY DUMP")
print("="*80)
print(f"Memory dump size: {len(data):,} bytes")
print(f"Monster template size: {MONSTER_TEMPLATE_SIZE} bytes")
print()

# Calculate expected offsets based on C code
# The code uses: count * 0x2a + base_offset
# Where base_offset is like -0x5007
# In the data segment, this would be: data_segment_base - 0x5007

# Try to find monster templates
print("Searching for monster template data...")
print("-"*80)

candidates = search_for_monster_templates(data)
print(f"Found {len(candidates)} potential monster template regions")
print()

if candidates:
    # Take the best candidate (first one)
    best_offset, sample_templates = candidates[0]

    print(f"Best candidate region starts at: 0x{best_offset:05x}")
    print()
    print("Sample templates from this region:")
    print("-"*80)

    for m in sample_templates:
        print(f"Template at {m['offset']}:")
        print(f"  Display: {m['display_char']:3s}  Level: {m['monster_level']:3d}  HP: {m['hp']:5d}  Attacks: {m['num_attacks']:2d}  Damage: {m['damage']:3d}")

    print()
    print("="*80)
    print("EXTRACTING ALL MONSTERS FROM BEST REGION")
    print("="*80)

    # Extract up to 100 monsters
    all_monsters = []
    for i in range(100):
        offset = best_offset + (i * MONSTER_TEMPLATE_SIZE)
        if offset + MONSTER_TEMPLATE_SIZE > len(data):
            break

        monster = extract_monster_template(data, offset)
        if monster and monster['monster_level'] > 0 and monster['monster_level'] < 100:
            all_monsters.append(monster)
        else:
            # Stop if we hit invalid data
            if i > 10:  # Only stop if we've extracted a reasonable number
                break

    print(f"\nExtracted {len(all_monsters)} monsters")
    print()

    # Display all monsters
    print(f"{'#':>3} {'Offset':8} {'Char':4} {'Lvl':>3} {'HP':>5} {'Atk':>3} {'Dmg':>4} {'Spawn%':>6} {'Item':>4}")
    print("-"*80)

    for i, m in enumerate(all_monsters, 1):
        print(f"{i:3d} {m['offset']:8} {m['display_char']:4} {m['monster_level']:3d} {m['hp']:5d} {m['num_attacks']:3d} {m['damage']:4d} {m['spawn_chance']:6d} {m['item_carried']:4d}")

    # Try to find monster names near the templates
    print()
    print("="*80)
    print("SEARCHING FOR MONSTER NAMES")
    print("="*80)

    # Monster names might be stored before or after the template data
    # Search in both directions
    name_strings = extract_pascal_strings_near(data, best_offset, radius=5000, min_len=4, max_len=25)

    print(f"\nFound {len(name_strings)} potential monster name strings near template data")
    print()

    # Filter for likely monster names (French creatures)
    monster_keywords = ['dragon', 'orc', 'goblin', 'troll', 'ogre', 'zombie', 'squelette',
                        'fantme', 'esprit', 'gant', 'serpent', 'araigne', 'rat', 'chauve-souris',
                        'loup', 'ours', 'aigle', 'faucon', 'corbeau', 'spectre', 'liche',
                        'momie', 'vampire', 'dmon', 'diable', 'ange', 'gorgone', 'mduse',
                        'hydre', 'griffon', 'manticore', 'basilic', 'cocatrice', 'wyvern']

    likely_names = []
    for s in name_strings:
        text_lower = s['text'].lower()
        if any(keyword in text_lower for keyword in monster_keywords):
            likely_names.append(s)

    if likely_names:
        print("Likely monster names found:")
        print("-"*80)
        for s in likely_names[:50]:
            print(f"{s['offset']:8} (rel {s['rel_offset']:+6d}): {s['text']}")
    else:
        print("No obvious monster names found with keywords.")
        print("Showing all strings near template region:")
        print("-"*80)
        for s in name_strings[:40]:
            print(f"{s['offset']:8} (rel {s['rel_offset']:+6d}): {s['text']}")

else:
    print("No clear monster template regions found.")
    print("Trying alternative search...")

    # Alternative: search for specific byte patterns
    # Monster display characters are often printable ASCII
    # Try searching for sequences of monster-like data

# Save detailed results
print()
print("="*80)
print("Saving detailed results...")

with open('monster_extraction_results.txt', 'w') as f:
    f.write("MORIA MONSTER EXTRACTION RESULTS\n")
    f.write("="*80 + "\n\n")

    if candidates:
        f.write(f"Monster template region found at: 0x{best_offset:05x}\n")
        f.write(f"Total monsters extracted: {len(all_monsters)}\n\n")

        f.write("MONSTER DATABASE\n")
        f.write("="*80 + "\n")
        f.write(f"{'#':>3} {'Offset':8} {'Char':4} {'Form':4} {'Lvl':>3} {'HP':>5} {'Atk':>3} {'Dmg':>4} {'Spawn':>6} {'Item':>4}\n")
        f.write("-"*80 + "\n")

        for i, m in enumerate(all_monsters, 1):
            f.write(f"{i:3d} {m['offset']:8} {m['display_char']:4} {m['true_form']:4} "
                   f"{m['monster_level']:3d} {m['hp']:5d} {m['num_attacks']:3d} {m['damage']:4d} "
                   f"{m['spawn_chance']:6d} {m['item_carried']:4d}\n")

        if likely_names or name_strings:
            f.write("\n\nPOTENTIAL MONSTER NAMES\n")
            f.write("="*80 + "\n")
            names_to_show = likely_names if likely_names else name_strings[:100]
            for s in names_to_show:
                f.write(f"{s['offset']:8} (rel {s['rel_offset']:+6d}): {s['text']}\n")

print("✓ Results saved to: monster_extraction_results.txt")
