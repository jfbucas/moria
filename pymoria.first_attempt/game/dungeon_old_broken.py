"""
Fixed dungeon generation - creates more open, playable mazes.
"""

import random
from typing import List, Tuple, Optional

class Dungeon:
    """Improved dungeon generator."""

    def __init__(self, level: int, width: int = 79, height: int = 22):
        self.level = level
        self.width = width
        self.height = height
        self.map = [[' ' for _ in range(width)] for _ in range(height)]
        self.rooms = []
        self.monsters = []
        self.items = []
        self.stairs_up = None
        self.stairs_down = None

        self.generate()

    def generate(self):
        """Generate a better dungeon."""
        # Draw border
        self._draw_border()

        # Fill with walls initially
        for y in range(1, self.height - 1):
            for x in range(1, self.width - 1):
                self.map[y][x] = '█'

        # Generate rooms (fewer, larger rooms)
        num_rooms = random.randint(6, 10)
        for _ in range(num_rooms):
            self._try_add_room()

        # Connect rooms with corridors
        self._connect_rooms()

        # Place stairs
        self._place_stairs()

        # Populate with monsters and items
        self._populate()

    def _draw_border(self):
        """Draw border walls."""
        for y in range(self.height):
            for x in range(self.width):
                if y == 0:
                    if x == 0:
                        self.map[y][x] = '┌'
                    elif x == self.width - 1:
                        self.map[y][x] = '┐'
                    else:
                        self.map[y][x] = '─'
                elif y == self.height - 1:
                    if x == 0:
                        self.map[y][x] = '└'
                    elif x == self.width - 1:
                        self.map[y][x] = '┘'
                    else:
                        self.map[y][x] = '─'
                elif x == 0 or x == self.width - 1:
                    self.map[y][x] = '│'

    def _try_add_room(self):
        """Try to add a room to the dungeon."""
        max_attempts = 30
        for _ in range(max_attempts):
            # Random room size
            room_width = random.randint(5, 12)
            room_height = random.randint(3, 6)

            # Random position
            x = random.randint(2, self.width - room_width - 2)
            y = random.randint(2, self.height - room_height - 2)

            # Check if room overlaps with existing rooms
            if self._can_place_room(x, y, room_width, room_height):
                self._carve_room(x, y, room_width, room_height)
                self.rooms.append((x, y, room_width, room_height))
                return True
        return False

    def _can_place_room(self, x: int, y: int, w: int, h: int) -> bool:
        """Check if room can be placed."""
        # Check bounds
        if x < 1 or y < 1 or x + w >= self.width - 1 or y + h >= self.height - 1:
            return False

        # Check for overlap with existing rooms (with 1-tile buffer)
        for rx, ry, rw, rh in self.rooms:
            if not (x + w + 1 < rx or x > rx + rw + 1 or
                    y + h + 1 < ry or y > ry + rh + 1):
                return False

        return True

    def _carve_room(self, x: int, y: int, w: int, h: int):
        """Carve out a room."""
        for dy in range(h):
            for dx in range(w):
                self.map[y + dy][x + dx] = ' '

    def _connect_rooms(self):
        """Connect all rooms with corridors."""
        if len(self.rooms) < 2:
            return

        # Connect each room to the next
        for i in range(len(self.rooms) - 1):
            x1, y1, w1, h1 = self.rooms[i]
            x2, y2, w2, h2 = self.rooms[i + 1]

            # Centers of rooms
            cx1 = x1 + w1 // 2
            cy1 = y1 + h1 // 2
            cx2 = x2 + w2 // 2
            cy2 = y2 + h2 // 2

            # Create L-shaped corridor
            if random.random() < 0.5:
                # Horizontal then vertical
                self._carve_h_corridor(cx1, cx2, cy1)
                self._carve_v_corridor(cy1, cy2, cx2)
            else:
                # Vertical then horizontal
                self._carve_v_corridor(cy1, cy2, cx1)
                self._carve_h_corridor(cx1, cx2, cy2)

        # Add some extra connections for loops
        if len(self.rooms) >= 4:
            for _ in range(len(self.rooms) // 3):
                i = random.randint(0, len(self.rooms) - 1)
                j = random.randint(0, len(self.rooms) - 1)
                if i != j:
                    x1, y1, w1, h1 = self.rooms[i]
                    x2, y2, w2, h2 = self.rooms[j]
                    cx1 = x1 + w1 // 2
                    cy1 = y1 + h1 // 2
                    cx2 = x2 + w2 // 2
                    cy2 = y2 + h2 // 2
                    self._carve_h_corridor(cx1, cx2, cy1)
                    self._carve_v_corridor(cy1, cy2, cx2)

    def _carve_h_corridor(self, x1: int, x2: int, y: int):
        """Carve horizontal corridor."""
        if x1 > x2:
            x1, x2 = x2, x1
        for x in range(x1, x2 + 1):
            if 0 < x < self.width - 1 and 0 < y < self.height - 1:
                self.map[y][x] = ' '

    def _carve_v_corridor(self, y1: int, y2: int, x: int):
        """Carve vertical corridor."""
        if y1 > y2:
            y1, y2 = y2, y1
        for y in range(y1, y2 + 1):
            if 0 < x < self.width - 1 and 0 < y < self.height - 1:
                self.map[y][x] = ' '

    def _place_stairs(self):
        """Place stairs in random rooms."""
        if len(self.rooms) >= 2:
            # Stairs up in first room
            x, y, w, h = self.rooms[0]
            self.stairs_up = (x + w // 2, y + h // 2)
            self.map[self.stairs_up[1]][self.stairs_up[0]] = '<'

            # Stairs down in last room
            x, y, w, h = self.rooms[-1]
            self.stairs_down = (x + w // 2, y + h // 2)
            self.map[self.stairs_down[1]][self.stairs_down[0]] = '>'

    def _populate(self):
        """Add monsters and items."""
        from data.monsters import get_monster_by_level
        from data.items import get_random_item
        from data.potions import get_random_potion

        # Count floor spaces
        floor_tiles = sum(1 for row in self.map for cell in row if cell == ' ')

        # Monsters (1 per 25 tiles)
        num_monsters = max(3, floor_tiles // 25)
        for _ in range(num_monsters):
            pos = self._random_floor_pos()
            if pos:
                x, y = pos
                monster_template = get_monster_by_level(self.level)
                self.monsters.append({
                    'template': monster_template,
                    'x': x,
                    'y': y,
                    'hp': monster_template.hp
                })

        # Items (1 per 35 tiles)
        num_items = max(2, floor_tiles // 35)
        for _ in range(num_items):
            pos = self._random_floor_pos()
            if pos:
                x, y = pos
                if random.random() < 0.6:
                    item = get_random_item(self.level)
                else:
                    item = get_random_potion(self.level)
                self.items.append({
                    'template': item,
                    'x': x,
                    'y': y
                })

    def _random_floor_pos(self) -> Optional[Tuple[int, int]]:
        """Get random floor position."""
        attempts = 0
        while attempts < 100:
            x = random.randint(1, self.width - 2)
            y = random.randint(1, self.height - 2)
            if self.map[y][x] == ' ':
                # Make sure no monster/item already there
                if not self.has_monster(x, y) and not self.has_item(x, y):
                    return (x, y)
            attempts += 1
        return None

    def is_walkable(self, x: int, y: int) -> bool:
        """Check if position is walkable."""
        if not (0 <= x < self.width and 0 <= y < self.height):
            return False
        return self.map[y][x] in (' ', '<', '>')

    def has_monster(self, x: int, y: int) -> bool:
        """Check for monster at position."""
        return any(m['x'] == x and m['y'] == y for m in self.monsters)

    def has_item(self, x: int, y: int) -> bool:
        """Check for item at position."""
        return any(i['x'] == x and i['y'] == y for i in self.items)

    def get_char_at(self, x: int, y: int) -> str:
        """Get character at position."""
        if not (0 <= x < self.width and 0 <= y < self.height):
            return ' '
        return self.map[y][x]
