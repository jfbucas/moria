#!/usr/bin/env python3
"""Test overall map connectivity using flood fill."""

from collections import deque
from game.dungeon import Dungeon

dungeon = Dungeon(level=1)

# Find all walkable tiles
walkable_tiles = []
for y in range(dungeon.height):
    for x in range(dungeon.width):
        if dungeon.is_walkable(x, y):
            walkable_tiles.append((x, y))

print(f"Total walkable tiles: {len(walkable_tiles)}")

# Flood fill to find connected components
components = []
unvisited = set(walkable_tiles)

while unvisited:
    # Start a new component from an unvisited tile
    start = next(iter(unvisited))
    component = set()
    queue = deque([start])
    component.add(start)
    unvisited.remove(start)

    # BFS to find all tiles in this component
    while queue:
        x, y = queue.popleft()

        for dx, dy in [(-1,0),(1,0),(0,-1),(0,1)]:
            nx, ny = x+dx, y+dy
            if (nx, ny) in unvisited and dungeon.is_walkable(nx, ny):
                unvisited.remove((nx, ny))
                component.add((nx, ny))
                queue.append((nx, ny))

    components.append(component)

print(f"Connected components: {len(components)}")
for i, comp in enumerate(sorted(components, key=len, reverse=True)):
    print(f"  Component {i+1}: {len(comp)} tiles")
    if i >= 9:  # Show only first 10
        print(f"  ... and {len(components) - 10} more components")
        break

# Check if stairs are in same component
if dungeon.stairs_up and dungeon.stairs_down:
    up_comp = None
    down_comp = None
    for i, comp in enumerate(components):
        if dungeon.stairs_up in comp:
            up_comp = i
        if dungeon.stairs_down in comp:
            down_comp = i

    print(f"\nStairs up in component: {up_comp+1 if up_comp is not None else 'None'}")
    print(f"Stairs down in component: {down_comp+1 if down_comp is not None else 'None'}")
    if up_comp == down_comp:
        print("✅ Stairs are in the same component!")
    else:
        print("❌ Stairs are in DIFFERENT components!")
