#!/usr/bin/env python3
"""Visualize a small section of the generated dungeon."""

from game.dungeon import Dungeon

dungeon = Dungeon(level=1)

# Print first 30x15 section
print("Dungeon visualization (first 30x15 area):")
print()
for y in range(min(15, dungeon.height)):
    row = ""
    for x in range(min(30, dungeon.width)):
        row += dungeon.map[y][x]
    print(row)

print(f"\nTotal walkable (' ') tiles: {sum(1 for y in range(dungeon.height) for x in range(dungeon.width) if dungeon.map[y][x] == ' ')}")

# Count tile types
from collections import Counter
tile_counts = Counter()
for y in range(dungeon.height):
    for x in range(dungeon.width):
        tile_counts[dungeon.map[y][x]] += 1

print(f"\nTile counts:")
for char, count in sorted(tile_counts.items(), key=lambda x: -x[1]):
    print(f"  '{char}': {count}")
