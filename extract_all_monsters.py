#!/usr/bin/python3
"""
Extract all monster names and data from Moria memory dump
Based on discovered monster name offsets
"""

def extract_pascal_string(data, offset):
    """Extract Pascal string at offset"""
    if offset >= len(data):
        return None

    length = data[offset]
    if length == 0 or length > 50 or offset + 1 + length > len(data):
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

# Known monster names and their offsets from search
known_monsters = [
    (0x2de1d, "Araignée"),
    (0x2de71, "Chauve Souris"),
    (0x2df97, "Gobelin"),
    (0x2dfeb, "Loup"),
    (0x2e015, "Loup Garou"),
    (0x2e0e7, "Orc"),
    (0x2e111, "Rat"),
    (0x2e13b, "Serpent"),
    (0x2e18f, "Troll"),
    (0x2e20d, "Voleur"),
]

print("="*80)
print("MORIA MONSTER DATABASE EXTRACTION")
print("="*80)
print()

# The monster names seem to be in the range 0x2de00 - 0x2e300
# Let's extract all Pascal strings in this range

monster_region_start = 0x2dc00
monster_region_end = 0x2e500

print(f"Extracting Pascal strings from monster region 0x{monster_region_start:05x} - 0x{monster_region_end:05x}")
print("-"*80)

all_monsters = []

for offset in range(monster_region_start, monster_region_end):
    name = extract_pascal_string(data, offset)
    if name and len(name) >= 3:
        all_monsters.append({
            'offset': offset,
            'name': name
        })

# Remove duplicates and sort by offset
seen = set()
unique_monsters = []
for m in all_monsters:
    if m['name'] not in seen:
        seen.add(m['name'])
        unique_monsters.append(m)

unique_monsters.sort(key=lambda x: x['offset'])

print(f"\nFound {len(unique_monsters)} unique monster names\n")

print(f"{'Offset':10} {'Name'}")
print("-"*80)

for m in unique_monsters:
    print(f"0x{m['offset']:05x}   {m['name']}")

# Save to file
with open('MONSTER_NAMES.md', 'w', encoding='utf-8') as f:
    f.write("# Moria Monster Names (French)\n")
    f.write("## Extracted from Memory Dump\n\n")
    f.write(f"Total monsters found: {len(unique_monsters)}\n\n")
    f.write("| # | Offset | Monster Name (French) | English Translation |\n")
    f.write("|---|--------|----------------------|---------------------|\n")

    # Provide English translations for common names
    translations = {
        "Araignée": "Spider",
        "Chauve Souris": "Bat",
        "Gobelin": "Gobelin",
        "Loup": "Wolf",
        "Loup Garou": "Werewolf",
        "Orc": "Orc",
        "Rat": "Rat",
        "Serpent": "Serpent/Snake",
        "Troll": "Troll",
        "Voleur": "Thief/Rogue",
        "Géant": "Giant",
        "Nain": "Dwarf",
        "Dragon": "Dragon",
        "Squelette": "Skeleton",
        "Zombie": "Zombie",
        "Fantôme": "Ghost",
        "Spectre": "Spectre",
        "Ombre": "Shadow",
        "Démon": "Demon",
        "Ange": "Angel",
        "Guerrier": "Warrior",
        "Mage": "Mage",
        "Prêtre": "Priest",
        "Elfe": "Elf",
        "Ours": "Bear",
        "Aigle": "Eagle",
        "Corbeau": "Raven",
    }

    for i, m in enumerate(unique_monsters, 1):
        english = translations.get(m['name'], "")
        f.write(f"| {i:2d} | 0x{m['offset']:05x} | {m['name']:30s} | {english} |\n")

print(f"\n✓ Monster names saved to: MONSTER_NAMES.md")

# Now try to find the monster template data
# Monster templates should be 42 bytes each, likely near or before the names

print("\n" + "="*80)
print("SEARCHING FOR MONSTER TEMPLATE DATA")
print("="*80)

# Try the region before monster names
template_search_start = 0x2d000
template_search_end = monster_region_start

print(f"\nSearching for 42-byte monster templates in 0x{template_search_start:05x} - 0x{template_search_end:05x}...")

# The templates might start at a nice aligned offset
# Monster count is likely around 50-100

# Check for sequences that could be monster stats
# Format: bytes that could be level (1-50), HP (1-1000 as 2 bytes), etc.

for start_offset in range(template_search_start, template_search_end, 42):
    # Try to parse as monster template
    if start_offset + 420 > len(data):  # Need space for at least 10 monsters
        break

    # Check if this looks like a sequence of monster templates
    valid_count = 0

    for i in range(10):
        offset = start_offset + (i * 42)

        # Check bytes at key positions
        # Byte 0: display char (should be printable)
        # Bytes 8-9: level (should be 1-50)
        # Bytes 10-11: HP (should be reasonable)

        if offset + 12 > len(data):
            break

        display_char = data[offset]
        level = data[offset + 8] | (data[offset + 9] << 8)
        hp = data[offset + 10] | (data[offset + 11] << 8)

        if (32 <= display_char <= 126 and
            1 <= level <= 50 and
            1 <= hp <= 2000):
            valid_count += 1

    if valid_count >= 5:
        print(f"\nPotential monster template array at 0x{start_offset:05x}")
        print(f"Displaying first 10 templates:")
        print(f"{'#':>3} {'Offset':8} {'Char':4} {'Lvl':>3} {'HP':>5}")
        print("-"*40)

        for i in range(min(10, valid_count)):
            offset = start_offset + (i * 42)
            display_char = chr(data[offset]) if 32 <= data[offset] <= 126 else f'0x{data[offset]:02x}'
            level = data[offset + 8] | (data[offset + 9] << 8)
            hp = data[offset + 10] | (data[offset + 11] << 8)

            print(f"{i+1:3d} 0x{offset:05x} {display_char:4} {level:3d} {hp:5d}")

print("\n" + "="*80)
print("✓ Monster extraction complete!")
print("  - Monster names: MONSTER_NAMES.md")
print("  - All strings: all_pascal_strings.txt")
