#!/usr/bin/env python3
"""Test corridor coordinate calculations."""

# Room grid: 10 rows x 39 columns
# Room (row, col) should occupy certain map tiles
# Walls are drawn between rooms

# Based on _create_room_grid:
# - Everything starts as spaces
# - Vertical walls at x = col*2+1 for col = 1..38
# - Horizontal walls at y = row*2+1 for row = 1..9
# - Crosses at (col*2+1, row*2+1)

# So room (row=0, col=0) should be:
#   - x: 0, 1 (before first vertical wall at x=3)
#   - y: 0, 1, 2 (before first horizontal wall at y=3)
# Actually with border at 0, room should be at:
#   - x: 1, 2
#   - y: 1, 2

print("Room boundaries:")
for row in range(3):
    for col in range(3):
        # Calculate room boundaries
        if col == 0:
            x_min, x_max = 1, 2
        else:
            x_min = col * 2 + 2
            x_max = x_min + 1

        if row == 0:
            y_min, y_max = 1, 2
        else:
            y_min = row * 2 + 2
            y_max = y_min + 1

        print(f"  Room({row},{col}): x=[{x_min},{x_max}], y=[{y_min},{y_max}]")

# Test vertical corridor connecting room(0,0) to room(1,0)
print("\nVertical corridor test:")
print("  Connecting room(0,0) to room(1,0)")
print("  Should open wall between them")

row, col = 0, 0
room1 = row * 39 + col
room2 = (row + 1) * 39 + col
print(f"  Rooms: {room1} -> {room2}")

# Current formula
map_y = (row + 1) * 2
map_x = (col + 1) * 2 - 1
print(f"  Current formula: ({map_x}, {map_y})")
print(f"  Room(0,0) is at y=[1,2], Room(1,0) is at y=[4,5]")
print(f"  Wall between them is at y=3")
print(f"  Corridor should be at y=3, not y={map_y}")

# Test horizontal corridor connecting room(0,0) to room(0,1)
print("\nHorizontal corridor test:")
print("  Connecting room(0,0) to room(0,1)")
row, col = 0, 0
adj_pos = 1  # First horizontal corridor
row_h = (adj_pos - 1) // 11
col_h = (adj_pos - 1) % 11
room1 = col_h * 39 + row_h
room2 = col_h * 39 + row_h + 1
print(f"  Rooms: {room1} -> {room2}")

map_y = (col_h + 1) * 2 - 1
map_x = (row_h + 1) * 2
print(f"  Current formula: ({map_x}, {map_y})")
print(f"  Room(0,0) is at x=[1,2], Room(0,1) is at x=[4,5]")
print(f"  Wall between them is at x=3")
print(f"  Corridor should be at x=3, not x={map_x}")
