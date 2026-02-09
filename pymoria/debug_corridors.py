#!/usr/bin/env python3
"""Debug corridor placement."""

import random
from game.dungeon import UnionFind

# Simulate corridor placement
ROOM_COLS = 39
ROOM_ROWS = 10
total_rooms = ROOM_ROWS * ROOM_COLS

uf = UnionFind(total_rooms)
corridors = list(range(1, 809))
random.shuffle(corridors)

vertical_count = 0
horizontal_count = 0
skipped_vertical = 0
skipped_horizontal = 0

for position in corridors[:20]:  # Just first 20 for debugging
    if position <= 391:  # Vertical
        row = (position - 1) // ROOM_COLS
        col = (position - 1) % ROOM_COLS

        room1 = row * ROOM_COLS + col
        room2 = (row + 1) * ROOM_COLS + col

        if room2 >= total_rooms:
            skipped_vertical += 1
            continue

        map_y = row * 2 + 1
        map_x = col * 2

        print(f"Vertical {position}: row={row}, col={col}, rooms={room1}->{room2}, map=({map_x},{map_y})")

        if uf.find(room1) != uf.find(room2):
            uf.union(room1, room2)
            vertical_count += 1
    else:  # Horizontal
        adj_pos = position - 390
        row = (adj_pos - 1) // 11
        col = (adj_pos - 1) % 11

        room1 = col * ROOM_COLS + row
        room2 = col * ROOM_COLS + row + 1

        if room2 >= total_rooms:
            skipped_horizontal += 1
            continue

        map_y = col * 2
        map_x = row * 2 + 1

        print(f"Horizontal {position} (adj={adj_pos}): row={row}, col={col}, rooms={room1}->{room2}, map=({map_x},{map_y})")

        if uf.find(room1) != uf.find(room2):
            uf.union(room1, room2)
            horizontal_count += 1

print(f"\nPlaced: {vertical_count} vertical, {horizontal_count} horizontal")
print(f"Skipped: {skipped_vertical} vertical, {skipped_horizontal} horizontal")
