#!/usr/bin/python3
"""
Extract Pascal-format strings from memory dump
Pascal strings: length byte + string data (no null terminator)
"""
import sys

def extract_pascal_strings(data, min_length=3, max_length=100):
    """Extract Pascal strings from binary data"""
    strings = []
    i = 0

    while i < len(data) - 1:
        # Read length byte
        length = data[i]

        # Skip if length is unreasonable
        if length < min_length or length > max_length:
            i += 1
            continue

        # Check if we have enough data
        if i + 1 + length > len(data):
            i += 1
            continue

        # Extract string
        try:
            string_data = data[i+1:i+1+length]
            # Try to decode as ASCII/Latin-1
            text = string_data.decode('latin-1', errors='ignore')

            # Check if it's mostly printable
            printable_count = sum(1 for c in text if c.isprintable() or c in '\n\r\t')
            if printable_count >= len(text) * 0.8:  # At least 80% printable
                strings.append({
                    'offset': f'0x{i:04x}',
                    'length': length,
                    'text': text
                })
        except:
            pass

        i += 1

    return strings

# Read the memory dump
with open('reverse/memory.dump', 'rb') as f:
    data = f.read()

print(f"Memory dump size: {len(data)} bytes")
print("="*80)

# Extract strings
strings = extract_pascal_strings(data)

print(f"\nFound {len(strings)} potential Pascal strings")
print("="*80)

# Group by categories (heuristic based on content)
categories = {
    'potions': [],
    'spells': [],
    'monsters': [],
    'items': [],
    'scrolls': [],
    'messages': [],
    'other': []
}

keywords = {
    'potions': ['potion', 'drink', 'quaff', 'feel', 'restore', 'cure'],
    'spells': ['spell', 'magic', 'cast', 'enchant'],
    'monsters': ['attacks', 'creature', 'dragon', 'orc', 'goblin', 'zombie', 'ghost'],
    'scrolls': ['scroll', 'read', 'parchment'],
    'items': ['sword', 'armor', 'shield', 'ring', 'weapon', 'helm', 'boots'],
    'messages': ['you', 'your', 'the', 'is', 'are']
}

for s in strings:
    text_lower = s['text'].lower()
    categorized = False

    for category, words in keywords.items():
        if any(word in text_lower for word in words):
            categories[category].append(s)
            categorized = True
            break

    if not categorized:
        categories['other'].append(s)

# Print by category
for category in ['potions', 'spells', 'monsters', 'scrolls', 'items']:
    if categories[category]:
        print(f"\n{'='*80}")
        print(f"{category.upper()} ({len(categories[category])} strings)")
        print('='*80)
        for s in categories[category][:50]:  # Limit to first 50 per category
            print(f"{s['offset']} [{s['length']:3d}]: {s['text'][:100]}")

# Show some interesting messages
print(f"\n{'='*80}")
print(f"INTERESTING MESSAGES (first 30)")
print('='*80)
for s in categories['messages'][:30]:
    if len(s['text']) > 10:  # Skip very short messages
        print(f"{s['offset']} [{s['length']:3d}]: {s['text'][:100]}")

# Save all strings to a file for detailed analysis
with open('memory_strings_extracted.txt', 'w', encoding='utf-8') as f:
    f.write("MORIA MEMORY DUMP - EXTRACTED STRINGS\n")
    f.write("="*80 + "\n\n")

    for category in categories:
        if categories[category]:
            f.write(f"\n{'='*80}\n")
            f.write(f"{category.upper()} ({len(categories[category])} strings)\n")
            f.write('='*80 + "\n")
            for s in categories[category]:
                f.write(f"{s['offset']} [{s['length']:3d}]: {s['text']}\n")

print(f"\n{'='*80}")
print(f"✓ Full extraction saved to: memory_strings_extracted.txt")
print(f"  Total strings extracted: {len(strings)}")
