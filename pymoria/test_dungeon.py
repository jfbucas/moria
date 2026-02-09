#!/usr/bin/env python3
"""Test dungeon generation to ensure player doesn't spawn trapped."""

import sys
from game.dungeon import Dungeon

def test_dungeon_connectivity():
    """Test that dungeon stairs are properly connected."""
    print("Testing dungeon generation...")

    for test_num in range(5):
        print(f"\n=== Test {test_num + 1} ===")
        dungeon = Dungeon(level=1)

        # Count walkable tiles BEFORE stairs placement
        walkable_before = sum(1 for y in range(dungeon.height)
                            for x in range(dungeon.width)
                            if dungeon.map[y][x] == ' ')
        print(f"Walkable tiles after corridor generation: {walkable_before}")

        # Check stairs exist
        if not dungeon.stairs_up:
            print("❌ ERROR: No stairs_up placed!")
            continue
        if not dungeon.stairs_down:
            print("❌ ERROR: No stairs_down placed!")
            continue

        up_x, up_y = dungeon.stairs_up
        down_x, down_y = dungeon.stairs_down

        print(f"Stairs up: ({up_x}, {up_y})")
        print(f"Stairs down: ({down_x}, {down_y})")

        # Check stairs_up has walkable neighbors
        up_neighbors = []
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = up_x + dx, up_y + dy
            if dungeon.is_walkable(nx, ny):
                up_neighbors.append((nx, ny))

        print(f"Stairs up walkable neighbors: {len(up_neighbors)}")
        if len(up_neighbors) < 1:
            print(f"❌ ERROR: Stairs up has NO walkable neighbors!")
            print(f"  Surrounding tiles:")
            for dy in range(-1, 2):
                row = ""
                for dx in range(-1, 2):
                    char = dungeon.get_char_at(up_x + dx, up_y + dy)
                    row += char
                print(f"    {row}")
            continue

        # Check stairs_down has walkable neighbors
        down_neighbors = []
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = down_x + dx, down_y + dy
            if dungeon.is_walkable(nx, ny):
                down_neighbors.append((nx, ny))

        print(f"Stairs down walkable neighbors: {len(down_neighbors)}")
        if len(down_neighbors) < 1:
            print(f"❌ ERROR: Stairs down has NO walkable neighbors!")
            continue

        # Count total walkable tiles
        walkable_count = sum(1 for y in range(dungeon.height)
                           for x in range(dungeon.width)
                           if dungeon.is_walkable(x, y))
        print(f"Total walkable tiles: {walkable_count}")

        if walkable_count < 50:
            print(f"⚠️  WARNING: Very few walkable tiles!")

        # Try to find path from stairs_up to a neighbor (BFS)
        from collections import deque
        start = up_neighbors[0] if up_neighbors else None
        if start:
            visited = {start}
            queue = deque([start])

            while queue:
                x, y = queue.popleft()

                for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    nx, ny = x + dx, y + dy
                    if (nx, ny) not in visited and dungeon.is_walkable(nx, ny):
                        visited.add((nx, ny))
                        queue.append((nx, ny))

            print(f"Reachable tiles from stairs_up: {len(visited)}")
            if len(visited) < walkable_count * 0.5:
                print(f"⚠️  WARNING: Only {len(visited)}/{walkable_count} tiles reachable!")

        print(f"✅ Test {test_num + 1} passed basic checks")

        # Print a small section around stairs_up
        print(f"\nArea around stairs_up at ({up_x}, {up_y}):")
        for dy in range(-3, 4):
            row = ""
            for dx in range(-5, 6):
                char = dungeon.get_char_at(up_x + dx, up_y + dy)
                if dx == 0 and dy == 0:
                    row += '@'  # Show where player would spawn
                else:
                    row += char
            print(f"  {row}")

if __name__ == '__main__':
    test_dungeon_connectivity()
