#!/usr/bin/env python3
"""Test border characters in dungeon map."""

from game.dungeon import Dungeon

dungeon = Dungeon(level=1)

print("Testing border characters:")
print(f"Dungeon dimensions: {dungeon.width} x {dungeon.height}")
print()

# Check top row (y=0)
print("Top row (y=0):")
for x in range(min(10, dungeon.width)):
    char = dungeon.map[0][x]
    walkable = dungeon.is_walkable(x, 0)
    print(f"  ({x},0): '{char}' (walkable: {walkable})")

print()

# Check left column (x=0)
print("Left column (x=0):")
for y in range(min(10, dungeon.height)):
    char = dungeon.map[y][0]
    walkable = dungeon.is_walkable(0, y)
    print(f"  (0,{y}): '{char}' (walkable: {walkable})")

print()

# Check some interior positions
print("Interior positions:")
for y in range(1, min(5, dungeon.height)):
    for x in range(1, min(5, dungeon.width)):
        char = dungeon.map[y][x]
        walkable = dungeon.is_walkable(x, y)
        if walkable:
            print(f"  ({x},{y}): '{char}' (walkable: {walkable})")
