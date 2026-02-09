#!/usr/bin/env python3
"""Debug full corridor placement."""

import random
from game.dungeon import UnionFind

ROOM_COLS = 39
ROOM_ROWS = 10
total_rooms = ROOM_ROWS * ROOM_COLS

uf = UnionFind(total_rooms)
corridors = list(range(1, 809))
random.shuffle(corridors)

vertical_placed = 0
horizontal_placed = 0
vertical_skipped_bounds = 0
vertical_skipped_connected = 0
horizontal_skipped_bounds = 0
horizontal_skipped_connected = 0

for position in corridors:
    if position <= 391:  # Vertical
        row = (position - 1) // ROOM_COLS
        col = (position - 1) % ROOM_COLS

        room1 = row * ROOM_COLS + col
        room2 = (row + 1) * ROOM_COLS + col

        if room2 >= total_rooms:
            vertical_skipped_bounds += 1
            continue

        if uf.find(room1) != uf.find(room2):
            uf.union(room1, room2)
            vertical_placed += 1
        else:
            vertical_skipped_connected += 1
    else:  # Horizontal
        adj_pos = position - 390
        row = (adj_pos - 1) // 11
        col = (adj_pos - 1) % 11

        room1 = col * ROOM_COLS + row
        room2 = col * ROOM_COLS + row + 1

        if room2 >= total_rooms:
            horizontal_skipped_bounds += 1
            continue

        if uf.find(room1) != uf.find(room2):
            uf.union(room1, room2)
            horizontal_placed += 1
        else:
            horizontal_skipped_connected += 1

print(f"Vertical corridors:")
print(f"  Placed: {vertical_placed}")
print(f"  Skipped (bounds): {vertical_skipped_bounds}")
print(f"  Skipped (already connected): {vertical_skipped_connected}")

print(f"\nHorizontal corridors:")
print(f"  Placed: {horizontal_placed}")
print(f"  Skipped (bounds): {horizontal_skipped_bounds}")
print(f"  Skipped (already connected): {horizontal_skipped_connected}")

print(f"\nTotal placed: {vertical_placed + horizontal_placed}")
print(f"Expected for MST: {total_rooms - 1} = {total_rooms - 1}")

# Check how many components we have
components = len(set(uf.find(i) for i in range(total_rooms)))
print(f"\nConnected components: {components}")
if components == 1:
    print("✅ All rooms are connected!")
else:
    print(f"❌ Dungeon is fragmented into {components} components!")
