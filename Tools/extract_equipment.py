#!/usr/bin/python3
"""
Extract all equipment (weapons, armor, rings) from Moria memory dump
"""

def extract_pascal_string(data, offset):
    """Extract Pascal string at offset"""
    if offset >= len(data):
        return None

    length = data[offset]
    if length == 0 or length > 60 or offset + 1 + length > len(data):
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
print("MORIA EQUIPMENT EXTRACTION")
print("="*80)
print()

# Equipment regions to search (based on nearby potion/monster data)
# Potions: 0x2a967
# Scrolls: 0x2abe6
# Monsters: 0x2ddf3 - 0x2e387
# Equipment likely: 0x2b000 - 0x2d000

equipment_regions = [
    (0x2b000, 0x2d000, "Main Equipment Region"),
    (0x2d400, 0x2e000, "Secondary Equipment Region"),
]

all_equipment = {
    'weapons': [],
    'armor': [],
    'rings': [],
    'misc': []
}

# French equipment keywords
keywords = {
    'weapons': ['épée', 'dague', 'hache', 'masse', 'marteau', 'arc', 'flèche',
                'lance', 'pique', 'bâton', 'gourdin', 'fléau', 'rapière',
                'hallebarde', 'trident', 'morgenstern', 'sabre', 'cimeterre'],
    'armor': ['armure', 'cotte', 'heaume', 'casque', 'bouclier', 'gantelets',
              'gants', 'bottes', 'jambières', 'cuirasse', 'plastron',
              'cape', 'manteau', 'robe', 'ceinture'],
    'rings': ['anneau', 'bague'],
    'materials': ['mithril', 'adamant', 'cuir', 'fer', 'acier', 'bronze',
                  'argent', 'or', 'platine', 'bois', 'chêne', 'frêne',
                  'if', 'ébène', 'elfique', 'nain', 'dragon']
}

print("Extracting Pascal strings from equipment regions...")
print("-"*80)

for start, end, region_name in equipment_regions:
    print(f"\nScanning {region_name} (0x{start:05x} - 0x{end:05x})...")

    region_items = []

    for offset in range(start, end):
        item_name = extract_pascal_string(data, offset)

        if item_name and len(item_name) >= 4:
            item_lower = item_name.lower()

            # Categorize the item
            categorized = False

            # Check weapons
            if any(keyword in item_lower for keyword in keywords['weapons']):
                all_equipment['weapons'].append({
                    'offset': offset,
                    'name': item_name
                })
                categorized = True

            # Check armor
            elif any(keyword in item_lower for keyword in keywords['armor']):
                all_equipment['armor'].append({
                    'offset': offset,
                    'name': item_name
                })
                categorized = True

            # Check rings
            elif any(keyword in item_lower for keyword in keywords['rings']):
                all_equipment['rings'].append({
                    'offset': offset,
                    'name': item_name
                })
                categorized = True

            # Check for equipment-like items (contains materials)
            elif any(keyword in item_lower for keyword in keywords['materials']):
                if len(item_name) > 8:  # Likely a full item description
                    all_equipment['misc'].append({
                        'offset': offset,
                        'name': item_name
                    })
                    categorized = True

            # Store if it looks like equipment
            if categorized:
                region_items.append(item_name)

    print(f"  Found {len(region_items)} equipment items")

# Remove duplicates
for category in all_equipment:
    seen = set()
    unique = []
    for item in all_equipment[category]:
        if item['name'] not in seen:
            seen.add(item['name'])
            unique.append(item)
    all_equipment[category] = sorted(unique, key=lambda x: x['offset'])

print()
print("="*80)
print("EQUIPMENT SUMMARY")
print("="*80)

for category, items in all_equipment.items():
    print(f"\n{category.upper()}: {len(items)} items")

# Display all equipment
print()
print("="*80)
print("WEAPONS")
print("="*80)
print(f"{'#':>3} {'Offset':8} {'Name'}")
print("-"*80)

for i, item in enumerate(all_equipment['weapons'], 1):
    print(f"{i:3d} 0x{item['offset']:05x} {item['name']}")

print()
print("="*80)
print("ARMOR & CLOTHING")
print("="*80)
print(f"{'#':>3} {'Offset':8} {'Name'}")
print("-"*80)

for i, item in enumerate(all_equipment['armor'], 1):
    print(f"{i:3d} 0x{item['offset']:05x} {item['name']}")

print()
print("="*80)
print("RINGS & JEWELRY")
print("="*80)
print(f"{'#':>3} {'Offset':8} {'Name'}")
print("-"*80)

for i, item in enumerate(all_equipment['rings'], 1):
    print(f"{i:3d} 0x{item['offset']:05x} {item['name']}")

print()
print("="*80)
print("MISCELLANEOUS EQUIPMENT")
print("="*80)
print(f"{'#':>3} {'Offset':8} {'Name'}")
print("-"*80)

for i, item in enumerate(all_equipment['misc'], 1):
    print(f"{i:3d} 0x{item['offset']:05x} {item['name']}")

# Save to file
print()
print("="*80)
print("Saving complete equipment database...")

with open('EQUIPMENT_DATABASE.md', 'w', encoding='utf-8') as f:
    f.write("# Moria Equipment Database\n")
    f.write("## Extracted from Memory Dump\n\n")
    f.write("---\n\n")

    f.write(f"## Summary\n\n")
    f.write(f"- **Weapons**: {len(all_equipment['weapons'])}\n")
    f.write(f"- **Armor & Clothing**: {len(all_equipment['armor'])}\n")
    f.write(f"- **Rings & Jewelry**: {len(all_equipment['rings'])}\n")
    f.write(f"- **Miscellaneous**: {len(all_equipment['misc'])}\n")
    f.write(f"- **Total Items**: {sum(len(items) for items in all_equipment.values())}\n\n")
    f.write("---\n\n")

    # Weapons
    f.write("## ⚔️ Weapons\n\n")
    f.write("| # | Offset | French Name | English Translation |\n")
    f.write("|---|--------|-------------|---------------------|\n")

    weapon_translations = {
        'épée': 'sword',
        'dague': 'dagger',
        'hache': 'axe',
        'masse': 'mace',
        'marteau': 'hammer',
        'arc': 'bow',
        'bâton': 'staff',
        'lance': 'spear',
        'gourdin': 'club',
        'fléau': 'flail',
        'hallebarde': 'halberd',
    }

    for i, item in enumerate(all_equipment['weapons'], 1):
        english = ""
        for fr, en in weapon_translations.items():
            if fr in item['name'].lower():
                english = en.title()
                break
        f.write(f"| {i:2d} | 0x{item['offset']:05x} | {item['name']:40s} | {english} |\n")

    # Armor
    f.write("\n## 🛡️ Armor & Clothing\n\n")
    f.write("| # | Offset | French Name | English Translation |\n")
    f.write("|---|--------|-------------|---------------------|\n")

    armor_translations = {
        'armure de mithril': 'Mithril Armor',
        'armure de cuir': 'Leather Armor',
        'armure de fer': 'Iron Armor',
        'cotte de mailles': 'Chain Mail',
        'heaume': 'Helm',
        'casque': 'Helmet',
        'bouclier': 'Shield',
        'gantelets': 'Gauntlets',
        'bottes': 'Boots',
        'cape': 'Cloak',
        'robe': 'Robe',
    }

    for i, item in enumerate(all_equipment['armor'], 1):
        english = ""
        item_lower = item['name'].lower()
        for fr, en in armor_translations.items():
            if fr in item_lower:
                english = en
                break
        f.write(f"| {i:2d} | 0x{item['offset']:05x} | {item['name']:40s} | {english} |\n")

    # Rings
    f.write("\n## 💍 Rings & Jewelry\n\n")
    f.write("| # | Offset | French Name | English Translation |\n")
    f.write("|---|--------|-------------|---------------------|\n")

    for i, item in enumerate(all_equipment['rings'], 1):
        english = "Ring"
        if 'bague' in item['name'].lower():
            english = "Wand"
        f.write(f"| {i:2d} | 0x{item['offset']:05x} | {item['name']:40s} | {english} |\n")

    # Misc
    f.write("\n## 🎒 Miscellaneous Equipment\n\n")
    f.write("| # | Offset | French Name | Type |\n")
    f.write("|---|--------|-------------|------|\n")

    for i, item in enumerate(all_equipment['misc'], 1):
        item_type = "Other"
        if any(mat in item['name'].lower() for mat in ['mithril', 'adamant']):
            item_type = "Rare Material"
        elif any(mat in item['name'].lower() for mat in ['bois', 'chêne', 'frêne']):
            item_type = "Wood/Projectile"
        f.write(f"| {i:2d} | 0x{item['offset']:05x} | {item['name']:40s} | {item_type} |\n")

print("✓ Equipment database saved to: EQUIPMENT_DATABASE.md")
print()
print("="*80)
print("✓ Equipment extraction complete!")
print(f"  Total items found: {sum(len(items) for items in all_equipment.values())}")
