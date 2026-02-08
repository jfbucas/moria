#!/usr/bin/python3
"""
Improved monster extraction - search for actual data patterns
"""
import struct

MONSTER_TEMPLATE_SIZE = 0x2a  # 42 bytes

def is_valid_monster_template(data, offset):
    """Check if data at offset looks like a valid monster template"""
    if offset + MONSTER_TEMPLATE_SIZE > len(data):
        return False, None

    try:
        template_data = data[offset:offset+MONSTER_TEMPLATE_SIZE]

        # Parse key fields
        display_char = template_data[0]
        true_form = template_data[1]
        monster_level = struct.unpack('<H', template_data[8:10])[0]
        hp = struct.unpack('<H', template_data[10:12])[0]
        num_attacks = struct.unpack('<H', template_data[14:16])[0]
        damage = struct.unpack('<H', template_data[20:22])[0]

        # Validation criteria for a valid monster:
        # 1. Display char should be printable or specific monster chars
        # 2. Monster level should be 1-50
        # 3. HP should be 1-5000
        # 4. Num attacks should be 1-9
        # 5. Damage should be 1-500

        valid = True

        # Display char should be printable (letters, symbols) or common monster chars
        if not (32 <= display_char <= 126):
            valid = False

        # Reasonable game stats
        if not (1 <= monster_level <= 50):
            valid = False
        if not (1 <= hp <= 5000):
            valid = False
        if not (0 <= num_attacks <= 9):
            valid = False
        if not (0 <= damage <= 500):
            valid = False

        if valid:
            monster = {
                'offset': offset,
                'display_char': chr(display_char),
                'true_form': chr(true_form) if 32 <= true_form <= 126 else f'0x{true_form:02x}',
                'monster_level': monster_level,
                'hp': hp,
                'num_attacks': num_attacks,
                'damage': damage,
                'raw_data': template_data
            }
            return True, monster

        return False, None

    except:
        return False, None

def find_monster_arrays(data):
    """Find consecutive monster templates in the data"""
    arrays = []
    i = 0

    while i < len(data) - MONSTER_TEMPLATE_SIZE * 5:
        # Check if this position starts a sequence of valid monsters
        valid_count = 0
        monsters = []

        for j in range(20):  # Try to find up to 20 consecutive monsters
            offset = i + (j * MONSTER_TEMPLATE_SIZE)
            is_valid, monster = is_valid_monster_template(data, offset)

            if is_valid:
                monsters.append(monster)
                valid_count += 1
            else:
                break

        # If we found at least 5 consecutive valid monsters, this is likely a monster array
        if valid_count >= 5:
            arrays.append({
                'start_offset': i,
                'count': valid_count,
                'monsters': monsters
            })
            i += valid_count * MONSTER_TEMPLATE_SIZE
        else:
            i += MONSTER_TEMPLATE_SIZE

    return arrays

def extract_pascal_string(data, offset):
    """Extract a Pascal string at given offset"""
    if offset >= len(data):
        return None

    length = data[offset]
    if length == 0 or length > 100 or offset + 1 + length > len(data):
        return None

    try:
        text = data[offset+1:offset+1+length].decode('latin-1', errors='ignore')
        if sum(1 for c in text if c.isprintable()) >= len(text) * 0.7:
            return text.strip()
    except:
        pass

    return None

# Read memory dump
with open('reverse/memory.dump', 'rb') as f:
    data = f.read()

print("="*80)
print("IMPROVED MORIA MONSTER EXTRACTION")
print("="*80)
print(f"Memory dump size: {len(data):,} bytes\n")

print("Scanning for monster template arrays...")
arrays = find_monster_arrays(data)

print(f"Found {len(arrays)} monster arrays\n")

if not arrays:
    print("No monster arrays found. Trying looser criteria...")
    # Try a single pass looking for any valid templates
    print("\nSearching for individual valid monster templates...")

    monsters_found = []
    for i in range(0, len(data) - MONSTER_TEMPLATE_SIZE, MONSTER_TEMPLATE_SIZE):
        is_valid, monster = is_valid_monster_template(data, i)
        if is_valid:
            monsters_found.append(monster)
            if len(monsters_found) <= 20:
                print(f"Found at 0x{i:05x}: {monster['display_char']} Lvl {monster['monster_level']} HP {monster['hp']}")

    print(f"\nTotal individual monsters found: {len(monsters_found)}")

else:
    # Display the best arrays
    arrays.sort(key=lambda x: -x['count'])

    print("Top 5 monster arrays:")
    print("-"*80)

    for idx, array in enumerate(arrays[:5], 1):
        print(f"\n#{idx} Array at 0x{array['start_offset']:05x} - {array['count']} monsters")
        print(f"{'#':>3} {'Offset':8} {'Chr':3} {'Lvl':>3} {'HP':>5} {'Atk':>2} {'Dmg':>4}")
        print("-"*40)

        for i, m in enumerate(array['monsters'][:10], 1):
            print(f"{i:3d} 0x{m['offset']:05x} {m['display_char']:3} {m['monster_level']:3d} {m['hp']:5d} {m['num_attacks']:2d} {m['damage']:4d}")

        if array['count'] > 10:
            print(f"    ... and {array['count'] - 10} more")

    # Take the largest array as the main monster database
    main_array = arrays[0]

    print("\n" + "="*80)
    print(f"COMPLETE MONSTER DATABASE ({main_array['count']} monsters)")
    print("="*80)

    # Search for monster names near the monster array
    # Names might be stored before the array
    search_start = max(0, main_array['start_offset'] - 10000)
    search_end = main_array['start_offset']

    monster_names = []
    for offset in range(search_start, search_end):
        name = extract_pascal_string(data, offset)
        if name and 3 <= len(name) <= 25:
            # Check if it contains monster-like words
            lower = name.lower()
            if any(word in lower for word in ['dragon', 'orc', 'goblin', 'rat', 'serpent',
                                               'araigne', 'zombie', 'fantme', 'gant',
                                               'loup', 'ours', 'troll', 'ogre', 'squelette']):
                monster_names.append({'offset': offset, 'name': name})

    if monster_names:
        print(f"\nFound {len(monster_names)} potential monster names:")
        print("-"*80)
        for entry in monster_names[:30]:
            print(f"0x{entry['offset']:05x}: {entry['name']}")

    # Save full database
    print("\n" + "="*80)
    print("Saving complete database...")

    with open('monster_database.txt', 'w') as f:
        f.write("MORIA MONSTER DATABASE\n")
        f.write("="*80 + "\n")
        f.write(f"Extracted from: reverse/memory.dump\n")
        f.write(f"Array offset: 0x{main_array['start_offset']:05x}\n")
        f.write(f"Total monsters: {main_array['count']}\n\n")

        f.write(f"{'#':>3} {'Offset':8} {'Display':7} {'Form':7} {'Lvl':>3} {'HP':>5} {'Atk':>2} {'Dmg':>4}\n")
        f.write("-"*80 + "\n")

        for i, m in enumerate(main_array['monsters'], 1):
            f.write(f"{i:3d} 0x{m['offset']:05x} {m['display_char']:7} {m['true_form']:7} "
                   f"{m['monster_level']:3d} {m['hp']:5d} {m['num_attacks']:2d} {m['damage']:4d}\n")

        if monster_names:
            f.write("\n\nPOTENTIAL MONSTER NAMES\n")
            f.write("="*80 + "\n")
            for entry in monster_names:
                f.write(f"0x{entry['offset']:05x}: {entry['name']}\n")

    print("✓ Database saved to: monster_database.txt")

    # Also create a summary
    print("\nMONSTER STATISTICS:")
    print("-"*80)

    levels = [m['monster_level'] for m in main_array['monsters']]
    hps = [m['hp'] for m in main_array['monsters']]

    print(f"Level range: {min(levels)} - {max(levels)}")
    print(f"HP range: {min(hps)} - {max(hps)}")
    print(f"Average level: {sum(levels)/len(levels):.1f}")
    print(f"Average HP: {sum(hps)/len(hps):.1f}")

    # Count unique display characters
    chars = set(m['display_char'] for m in main_array['monsters'])
    print(f"Unique display characters: {len(chars)}")
    print(f"Characters used: {sorted(chars)}")
