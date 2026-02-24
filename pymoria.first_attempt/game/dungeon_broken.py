"""
Dungeon generation using Randomized Kruskal's MST algorithm.
Based on reverse-engineered corridor generation from original game.
"""

import random
from typing import List, Tuple, Optional
from utils.constants import (
    MAP_WIDTH, MAP_HEIGHT, ROOM_COLS, ROOM_ROWS,
    TOTAL_CORRIDORS, VERTICAL_CORRIDORS,
    CHAR_FLOOR, CHAR_WALL_VERTICAL, CHAR_WALL_HORIZONTAL, CHAR_WALL_CROSS,
    CHAR_STAIRS_DOWN, CHAR_STAIRS_UP
)


class UnionFind:
    """Union-Find data structure for Kruskal's algorithm."""

    def __init__(self, size: int):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, x: int) -> int:
        """Find root with path compression."""
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        """Union two sets. Returns True if they were separate."""
        root_x = self.find(x)
        root_y = self.find(y)

        if root_x == root_y:
            return False

        # Union by rank
        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        elif self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1

        return True


class Dungeon:
    """Dungeon level with procedural generation."""

    def __init__(self, level: int):
        self.level = level
        self.width = MAP_WIDTH
        self.height = MAP_HEIGHT
        self.map = [[' ' for _ in range(MAP_WIDTH)] for _ in range(MAP_HEIGHT)]
        self.rooms = []  # List of room rectangles
        self.monsters = []
        self.items = []
        self.stairs_up: Optional[Tuple[int, int]] = None
        self.stairs_down: Optional[Tuple[int, int]] = None

        self.generate()

    def generate(self):
        """Generate dungeon level."""
        # Initialize with walls
        self._fill_walls()

        # Generate rooms using Kruskal's algorithm
        self._generate_rooms()

        # Place stairs
        self._place_stairs()

        # Populate with monsters and items
        self._populate()

    def _fill_walls(self):
        """Fill map with walls."""
        for y in range(self.height):
            for x in range(self.width):
                # Border walls with proper box-drawing characters
                if y == 0:
                    if x == 0:
                        self.map[y][x] = '┌'  # Top-left corner
                    elif x == self.width - 1:
                        self.map[y][x] = '┐'  # Top-right corner
                    else:
                        self.map[y][x] = CHAR_WALL_HORIZONTAL
                elif y == self.height - 1:
                    if x == 0:
                        self.map[y][x] = '└'  # Bottom-left corner
                    elif x == self.width - 1:
                        self.map[y][x] = '┘'  # Bottom-right corner
                    else:
                        self.map[y][x] = CHAR_WALL_HORIZONTAL
                elif x == 0 or x == self.width - 1:
                    self.map[y][x] = CHAR_WALL_VERTICAL
                else:
                    self.map[y][x] = '█'  # Solid block for walls (CP437: 219)

    def _generate_rooms(self):
        """Generate connected rooms using Kruskal's MST."""
        # Create union-find for room connectivity
        total_rooms = ROOM_ROWS * ROOM_COLS
        uf = UnionFind(total_rooms)

        # Generate random corridors
        corridors = list(range(1, TOTAL_CORRIDORS + 1))
        random.shuffle(corridors)

        placed_corridors = 0
        for corridor_id in corridors:
            if corridor_id <= VERTICAL_CORRIDORS:
                # Vertical corridor
                row = (corridor_id - 1) // ROOM_COLS + 1
                col = (corridor_id - 1) % ROOM_COLS + 1

                # Connects room at (row, col) to room at (row+1, col)
                room1 = (row - 1) * ROOM_COLS + (col - 1)
                room2 = row * ROOM_COLS + (col - 1)

                if row < ROOM_ROWS and uf.union(room1, room2):
                    self._place_vertical_corridor(row, col)
                    placed_corridors += 1
            else:
                # Horizontal corridor
                adj = corridor_id - VERTICAL_CORRIDORS - 1
                row = adj // ROOM_ROWS + 1
                col = adj % ROOM_ROWS + 1

                # Connects room at (row, col) to room at (row, col+1)
                room1 = (col - 1) * ROOM_COLS + (row - 1)
                room2 = (col - 1) * ROOM_COLS + row

                if row < ROOM_COLS and uf.union(room1, room2):
                    self._place_horizontal_corridor(row, col)
                    placed_corridors += 1

            # Stop when we have enough corridors
            if placed_corridors >= total_rooms:
                break

        # Create actual room spaces
        self._carve_rooms()

    def _place_vertical_corridor(self, row: int, col: int):
        """Place a vertical corridor."""
        # Map coordinates
        y = row * 2 + 1
        x = col * 2

        if 0 < y < self.height and 0 < x < self.width:
            self.map[y][x] = CHAR_FLOOR

    def _place_horizontal_corridor(self, row: int, col: int):
        """Place a horizontal corridor."""
        # Map coordinates
        y = col * 2
        x = row * 2 + 1

        if 0 < y < self.height and 0 < x < self.width:
            self.map[y][x] = CHAR_FLOOR

    def _carve_rooms(self):
        """Carve out room spaces in the grid."""
        for room_row in range(ROOM_ROWS):
            for room_col in range(ROOM_COLS):
                # Each room is a small area
                y_start = room_row * 2 + 1
                x_start = room_col * 2 + 1

                # Small chance to create actual room
                if random.random() < 0.3:
                    room_height = random.randint(1, 2)
                    room_width = random.randint(1, 3)

                    for dy in range(room_height):
                        for dx in range(room_width):
                            y = y_start + dy
                            x = x_start + dx
                            if 0 < y < self.height - 1 and 0 < x < self.width - 1:
                                self.map[y][x] = CHAR_FLOOR

                    self.rooms.append((x_start, y_start, room_width, room_height))

    def _place_stairs(self):
        """Place up and down stairs."""
        # Find empty floor spaces
        floor_spaces = []
        for y in range(1, self.height - 1):
            for x in range(1, self.width - 1):
                if self.map[y][x] == CHAR_FLOOR:
                    floor_spaces.append((x, y))

        if len(floor_spaces) >= 2:
            # Place stairs randomly
            self.stairs_up = random.choice(floor_spaces)
            self.map[self.stairs_up[1]][self.stairs_up[0]] = CHAR_STAIRS_UP

            # Remove used position
            floor_spaces.remove(self.stairs_up)

            # Place down stairs
            self.stairs_down = random.choice(floor_spaces)
            self.map[self.stairs_down[1]][self.stairs_down[0]] = CHAR_STAIRS_DOWN

    def _populate(self):
        """Populate dungeon with monsters and items."""
        # Count floor spaces
        floor_count = sum(1 for y in range(self.height)
                         for x in range(self.width)
                         if self.map[y][x] == CHAR_FLOOR)

        # Place monsters (roughly 1 per 20 floor tiles)
        num_monsters = max(3, floor_count // 20)
        self._place_monsters(num_monsters)

        # Place items (roughly 1 per 30 floor tiles)
        num_items = max(2, floor_count // 30)
        self._place_items(num_items)

    def _place_monsters(self, count: int):
        """Place monsters randomly."""
        from data.monsters import get_monster_by_level

        placed = 0
        attempts = 0
        max_attempts = count * 10

        while placed < count and attempts < max_attempts:
            x = random.randint(1, self.width - 2)
            y = random.randint(1, self.height - 2)

            if self.is_walkable(x, y) and not self.has_monster(x, y):
                monster_template = get_monster_by_level(self.level)
                # Will create actual Monster instance later
                self.monsters.append({
                    'template': monster_template,
                    'x': x,
                    'y': y,
                    'hp': monster_template.hp
                })
                placed += 1

            attempts += 1

    def _place_items(self, count: int):
        """Place items randomly."""
        from data.items import get_random_item
        from data.potions import get_random_potion

        placed = 0
        attempts = 0
        max_attempts = count * 10

        while placed < count and attempts < max_attempts:
            x = random.randint(1, self.width - 2)
            y = random.randint(1, self.height - 2)

            if self.is_walkable(x, y) and not self.has_item(x, y):
                # 60% items, 40% potions
                if random.random() < 0.6:
                    item = get_random_item(self.level)
                else:
                    item = get_random_potion(self.level)

                self.items.append({
                    'template': item,
                    'x': x,
                    'y': y
                })
                placed += 1

            attempts += 1

    def is_walkable(self, x: int, y: int) -> bool:
        """Check if position is walkable."""
        if not (0 <= x < self.width and 0 <= y < self.height):
            return False
        return self.map[y][x] in (CHAR_FLOOR, CHAR_STAIRS_UP, CHAR_STAIRS_DOWN)

    def has_monster(self, x: int, y: int) -> bool:
        """Check if position has a monster."""
        return any(m['x'] == x and m['y'] == y for m in self.monsters)

    def has_item(self, x: int, y: int) -> bool:
        """Check if position has an item."""
        return any(i['x'] == x and i['y'] == y for i in self.items)

    def get_char_at(self, x: int, y: int) -> str:
        """Get character at position."""
        if not (0 <= x < self.width and 0 <= y < self.height):
            return ' '
        return self.map[y][x]
