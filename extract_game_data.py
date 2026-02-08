#!/usr/bin/python3
"""
Extract structured game data (potions, spells, monsters) from memory dump
Focused on finding potion/scroll/spell effect descriptions
"""

def extract_pascal_strings_at(data, start_offset, count, stride=None):
    """Extract Pascal strings at specific offsets"""
    strings = []
    offset = start_offset

    for i in range(count):
        if offset >= len(data):
            break

        length = data[offset]
        if length == 0 or length > 100:
            if stride:
                offset += stride
            else:
                offset += 1
            continue

        if offset + 1 + length <= len(data):
            try:
                text = data[offset+1:offset+1+length].decode('latin-1', errors='ignore')
                strings.append({
                    'index': i,
                    'offset': f'0x{offset:05x}',
                    'length': length,
                    'text': text.strip()
                })
            except:
                pass

        if stride:
            offset += stride
        else:
            offset += length + 1

    return strings

def search_pascal_strings(data, search_term, max_results=100):
    """Search for Pascal strings containing a term"""
    results = []
    i = 0

    while i < len(data) - 1 and len(results) < max_results:
        length = data[i]

        if 3 <= length <= 100 and i + 1 + length <= len(data):
            try:
                text = data[i+1:i+1+length].decode('latin-1', errors='ignore')
                if search_term.lower() in text.lower():
                    results.append({
                        'offset': f'0x{i:05x}',
                        'length': length,
                        'text': text.strip()
                    })
            except:
                pass

        i += 1

    return results

# Read memory dump
with open('reverse/memory.dump', 'rb') as f:
    data = f.read()

print("MORIA MEMORY DUMP - GAME DATA EXTRACTION")
print("="*80)

# French keywords for different categories
french_keywords = {
    'potions': ['potion de', 'potion d\'', 'de gu', 'd\'extra', 'empoisonn', 'ralentiss', 'nourriss', 'd\'invisib'],
    'scrolls': ['parchemin', 'enchanter', 'prot', 'topographique', 'destruction'],
    'spells': ['sort', 'magie', 'enchant', 'invoquer', 'lancer'],
    'effects': ['vous sentez', 'vous vous', 'miam', 'en voil', 'abat sur vous'],
}

print("\n" + "="*80)
print("POTION NAMES (searching for potion-related strings)")
print("="*80)

potion_strings = []
for keyword in french_keywords['potions']:
    found = search_pascal_strings(data, keyword, max_results=30)
    potion_strings.extend(found)

# Remove duplicates
seen = set()
unique_potions = []
for s in potion_strings:
    if s['text'] not in seen:
        seen.add(s['text'])
        unique_potions.append(s)

for i, s in enumerate(sorted(unique_potions, key=lambda x: x['offset'])[:40], 1):
    print(f"{i:2d}. {s['offset']} [{s['length']:3d}]: {s['text']}")

print("\n" + "="*80)
print("SCROLL NAMES (searching for scroll-related strings)")
print("="*80)

scroll_strings = []
for keyword in french_keywords['scrolls']:
    found = search_pascal_strings(data, keyword, max_results=30)
    scroll_strings.extend(found)

seen = set()
unique_scrolls = []
for s in scroll_strings:
    if s['text'] not in seen:
        seen.add(s['text'])
        unique_scrolls.append(s)

for i, s in enumerate(sorted(unique_scrolls, key=lambda x: x['offset'])[:40], 1):
    print(f"{i:2d}. {s['offset']} [{s['length']:3d}]: {s['text']}")

print("\n" + "="*80)
print("EFFECT MESSAGES (what happens when you use items)")
print("="*80)

effect_strings = []
for keyword in french_keywords['effects']:
    found = search_pascal_strings(data, keyword, max_results=50)
    effect_strings.extend(found)

seen = set()
unique_effects = []
for s in effect_strings:
    if s['text'] not in seen and len(s['text']) > 10:
        seen.add(s['text'])
        unique_effects.append(s)

for i, s in enumerate(sorted(unique_effects, key=lambda x: x['offset'])[:50], 1):
    print(f"{i:2d}. {s['offset']} [{s['length']:3d}]: {s['text']}")

# Try to find structured data - potion effects might be in an array
print("\n" + "="*80)
print("SEARCHING FOR STRUCTURED POTION DATA")
print("="*80)

# Look for common potion-related French words to find clusters
potion_cluster_keywords = [
    "gu", "extra", "poison", "ralenti", "nourri", "invisib",
    "force", "accrois", "affaibli", "aveugl", "confus"
]

# Search for areas with high density of these keywords
window_size = 1000
stride = 100
best_clusters = []

for start in range(0, len(data) - window_size, stride):
    window = data[start:start+window_size]
    text = window.decode('latin-1', errors='ignore').lower()

    matches = sum(1 for keyword in potion_cluster_keywords if keyword in text)
    if matches >= 3:
        best_clusters.append((start, matches))

best_clusters.sort(key=lambda x: -x[1])

print(f"\nFound {len(best_clusters)} regions with high concentration of potion keywords")
print("Top 10 regions:")
for offset, count in best_clusters[:10]:
    print(f"  Offset 0x{offset:05x}: {count} keyword matches")

# Extract strings from the best region
if best_clusters:
    best_offset = best_clusters[0][0]
    print(f"\nExtracting strings from best region (0x{best_offset:05x}):")
    print("-"*80)

    # Try to extract 30 consecutive Pascal strings
    region_strings = extract_pascal_strings_at(data, best_offset, 50)

    for s in region_strings[:30]:
        print(f"{s['index']:2d}. {s['offset']} [{s['length']:3d}]: {s['text']}")

print("\n" + "="*80)
print("✓ Game data extraction complete")
print(f"  Found {len(unique_potions)} unique potion-related strings")
print(f"  Found {len(unique_scrolls)} unique scroll-related strings")
print(f"  Found {len(unique_effects)} unique effect messages")
