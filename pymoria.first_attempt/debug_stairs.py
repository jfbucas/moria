#!/usr/bin/env python3
"""Debug stairs placement."""

from game.dungeon import Dungeon

dungeon = Dungeon(level=1)

# Check stairs placement candidates
candidates = []
for y in range(2, dungeon.height - 2):
    for x in range(2, dungeon.width - 2):
        if dungeon.map[y][x] == ' ':
            neighbors = sum(1 for dx, dy in [(-1,0),(1,0),(0,-1),(0,1)]
                          if dungeon.map[y+dy][x+dx] == ' ')
            candidates.append((x, y, neighbors))

print(f"Total walkable tiles: {len([c for c in candidates])}")
print(f"Tiles with 0 neighbors: {len([c for c in candidates if c[2] == 0])}")
print(f"Tiles with 1 neighbor: {len([c for c in candidates if c[2] == 1])}")
print(f"Tiles with 2 neighbors: {len([c for c in candidates if c[2] == 2])}")
print(f"Tiles with 3 neighbors: {len([c for c in candidates if c[2] == 3])}")
print(f"Tiles with 4 neighbors: {len([c for c in candidates if c[2] == 4])}")

if len([c for c in candidates if c[2] >= 2]) > 0:
    print("\nFirst 10 tiles with 2+ neighbors:")
    for x, y, n in [c for c in candidates if c[2] >= 2][:10]:
        print(f"  ({x}, {y}): {n} neighbors")
        # Show surrounding area
        for dy in range(-1, 2):
            row = ""
            for dx in range(-1, 2):
                if dx == 0 and dy == 0:
                    row += '@'
                else:
                    row += dungeon.map[y+dy][x+dx]
            print(f"    {row}")
