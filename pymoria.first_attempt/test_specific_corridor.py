#!/usr/bin/env python3
"""Test a specific corridor placement visually."""

import random
from game.dungeon import Dungeon, UnionFind

# Create dungeon
dungeon = Dungeon(level=1)

# Manually test first vertical corridor
# Should connect room(0,0) to room(1,0)
ROOM_COLS = 39
position = 1  # First vertical corridor

row = (position - 1) // ROOM_COLS  # 0
col = (position - 1) % ROOM_COLS   # 0

room1 = row * ROOM_COLS + col      # 0
room2 = (row + 1) * ROOM_COLS + col  # 39

# Corridor should be placed at:
map_y = (row + 1) * 2 + 1  # (0+1)*2+1 = 3
map_x = col * 2 + 2         # 0*2+2 = 2

print(f"Vertical corridor {position}:")
print(f"  Connects room {room1} to room {room2}")
print(f"  Room grid: ({row},{col}) to ({row+1},{col})")
print(f"  Corridor at map position: ({map_x}, {map_y})")
print()

# Show room(0,0) area
print("Room (0,0) area (map coordinates [1-2, 1-2]):")
for y in range(0, 5):
    row_str = ""
    for x in range(0, 5):
        if x == map_x and y == map_y:
            row_str += "C"  # Corridor
        else:
            row_str += dungeon.map[y][x]
    print(f"  y={y}: {row_str}")

print()
print(f"Character at corridor position ({map_x},{map_y}): '{dungeon.map[map_y][map_x]}'")

# Check if we can walk from room(0,0) to room(1,0)
print()
print("Checking walkability:")
print(f"  (2,2) in room(0,0): walkable = {dungeon.is_walkable(2,2)}")
print(f"  ({map_x},{map_y}) corridor: walkable = {dungeon.is_walkable(map_x,map_y)}")
print(f"  (2,4) in room(1,0): walkable = {dungeon.is_walkable(2,4)}")

# BFS to check if room(0,0) connects to room(1,0)
from collections import deque
start = (2, 2)  # Center of room(0,0)
target = (2, 4)  # Center of room(1,0)

visited = {start}
queue = deque([start])
found = False

while queue:
    x, y = queue.popleft()
    if (x, y) == target:
        found = True
        break

    for dx, dy in [(-1,0),(1,0),(0,-1),(0,1)]:
        nx, ny = x+dx, y+dy
        if (nx, ny) not in visited and dungeon.is_walkable(nx, ny):
            visited.add((nx, ny))
            queue.append((nx, ny))

print(f"\nCan reach room(1,0) from room(0,0): {found}")
print(f"Visited {len(visited)} tiles during search")
