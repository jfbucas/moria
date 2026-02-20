"""
FIXED MORIA dungeon - proper bounds checking and connectivity.
"""

import random
from typing import List, Tuple, Optional


class UnionFind:
    def __init__(self, size: int):
        self.parent = list(range(size))

    def find(self, x: int) -> int:
        while self.parent[x] != x:
            root = self.parent[x]
            self.parent[x] = self.parent[root]
            x = root
        return x

    def union(self, x: int, y: int) -> bool:
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        if root_x < root_y:
            self.parent[root_y] = root_x
        else:
            self.parent[root_x] = root_y
        return True


class Dungeon:
    def __init__(self, level: int):
        self.level = level
        self.width = 79
        self.height = 21
        self.map = [[' ' for _ in range(self.width)] for _ in range(self.height)]
        self.discovered = [[False for _ in range(self.width)] for _ in range(self.height)]  # Fog of war
        self.rooms = []
        self.monsters = []
        self.items = []
        self.stairs_up = None
        self.stairs_down = None
        self.generate()

    def generate(self):
        self._draw_border()
        self._create_room_grid()
        self._generate_corridors()
        self._generate_room()
        self._place_stairs()
        self._populate()

    def _draw_border(self):
        """Draw grid of walls separating 390 rooms and outer border.

        Layout (0-indexed): 10 room rows × 39 room cols.
        Rooms at odd×odd positions (rows 1,3,...,19 × cols 1,3,...,77).
        """
        # Vertical walls │ between horizontally adjacent rooms
        for a in range(1, 11):       # 10 room rows
            for b in range(1, 39):   # 38 vertical walls per row
                self.map[2*a - 1][2*b] = '│'

        # Horizontal walls ─ between vertically adjacent rooms
        for a in range(1, 10):       # 9 wall rows between 10 room rows
            for b in range(1, 40):
                self.map[2*a][2*b - 1] = '─'

        # Intersections ┼ at wall crossings
        for a in range(1, 10):
            for b in range(1, 39):
                self.map[2*a][2*b] = '┼'

        # Outer border
        # Top: ┌─┬─┬─...─┬─┐
        self.map[0][0] = '┌'
        self.map[0][self.width - 1] = '┐'
        for c in range(1, self.width - 1):
            self.map[0][c] = '┬' if c % 2 == 0 else '─'

        # Bottom: └─┴─┴─...─┴─┘
        self.map[self.height - 1][0] = '└'
        self.map[self.height - 1][self.width - 1] = '┘'
        for c in range(1, self.width - 1):
            self.map[self.height - 1][c] = '┴' if c % 2 == 0 else '─'

        # Left and right edges
        for r in range(1, self.height - 1):
            if r % 2 == 0:
                self.map[r][0] = '├'
                self.map[r][self.width - 1] = '┤'
            else:
                self.map[r][0] = '│'
                self.map[r][self.width - 1] = '│'

    def _create_room_grid(self):
        """Initialize union-find for 390 rooms (10 rows × 39 cols).

        Room at grid (r, c) has ID = (r-1)*39 + c, where r=1..10, c=1..39.
        Room map position: Python (2*r-1, 2*c-1).
        """
        self.uf = UnionFind(391)  # 1-indexed, rooms 1..390

    def _generate_corridors(self):
        """Connect rooms via Kruskal's MST.

        731 possible walls: 351 horizontal + 380 vertical.
        Randomly selects walls and removes them if they connect
        different components in the union-find structure.
        """
        unions_done = 0

        while unions_done < 389:  # Need 389 edges for 390-room spanning tree
            w = random.randint(1, 731)

            if w <= 351:  # Horizontal wall ─
                row_idx = (w - 1) // 39 + 1   # 1..9
                col_idx = (w - 1) % 39 + 1     # 1..39
                map_row = 2 * row_idx           # even row (2,4,...,18)
                map_col = 2 * col_idx - 1       # odd col (1,3,...,77)
                room1 = w
                room2 = w + 39  # room directly below
            else:  # Vertical wall │
                adjusted = w - 351              # 1..380
                col_idx = (adjusted - 1) // 10 + 1  # 1..38
                row_idx = (adjusted - 1) % 10 + 1   # 1..10
                map_row = 2 * row_idx - 1       # odd row (1,3,...,19)
                map_col = 2 * col_idx           # even col (2,4,...,76)
                room1 = (row_idx - 1) * 39 + col_idx
                room2 = room1 + 1  # room to the right

            # Skip if wall already removed
            if self.map[map_row][map_col] == ' ':
                continue

            # Only remove if connecting different components
            if self.uf.find(room1) != self.uf.find(room2):
                self.map[map_row][map_col] = ' '
                self.uf.union(room1, room2)
                unions_done += 1

    def _generate_room(self):
        """Generate one large room overlay per level (from generate_dungeon_level).

        Room size shrinks with dungeon depth. Draws walls ┴┬┤├ and
        clears interior to space, overlaying the corridor grid.
        """
        if self.level <= 0 or self.level > 15:
            return

        # Room dimensions (C: local_12=width, local_10=height)
        width = random.randrange(16 - self.level) * 2 + 8    # C: random_mod(0x10-value)*2+8
        height_range = (19 - self.level) // 3                 # C: (0x13-value)/3
        if height_range <= 0:
            return
        height = random.randrange(height_range) * 2 + 4      # C: random_mod(...)*2+4

        # Room position in C coords (odd values: local_c, local_e)
        col_range = 38 - width // 2                           # C: 0x26 - local_12/2
        row_range = 9 - height // 2
        if col_range <= 0 or row_range <= 0:
            return
        c_col = random.randrange(col_range) * 2 + 3
        c_row = random.randrange(row_range) * 2 + 3

        # Convert to 0-indexed Python coords (even values)
        pr = c_row - 1
        pc = c_col - 1
        half_w = width // 2 - 1
        half_h = height // 2 - 1

        # Top wall ┴ (0xc1), space below, bottom wall ┬ (0xc2)
        for i in range(1, half_w + 1):
            col = pc + i * 2
            self.map[pr][col] = '┴'
            self.map[pr + 1][col] = ' '
            self.map[pr + height][col] = '┬'

        # Left wall ┤ (0xb4), space right, right wall ├ (0xc3)
        for j in range(1, half_h + 1):
            row = pr + j * 2
            self.map[row][pc] = '┤'
            self.map[row][pc + 1] = ' '
            self.map[row][pc + width] = '├'

        # Clear interior (3 cells per grid position)
        for i in range(1, half_w + 1):
            for j in range(1, half_h + 1):
                r = pr + j * 2
                c = pc + i * 2
                self.map[r][c] = ' '       # intersection
                self.map[r + 1][c] = ' '   # cell below
                self.map[r][c + 1] = ' '   # cell to right

    def _place_stairs(self):
        floor_tiles = []
        for y in range(2, self.height - 2):
            for x in range(2, self.width - 2):
                if self.map[y][x] == ' ':
                    neighbors = sum(1 for dx, dy in [(-1,0),(1,0),(0,-1),(0,1)] 
                                  if self.map[y+dy][x+dx] == ' ')
                    if neighbors >= 2:
                        floor_tiles.append((x, y))
        
        if len(floor_tiles) >= 2:
            random.shuffle(floor_tiles)
            self.stairs_up = floor_tiles[0]
            if self.level != 1:  # Level 1: stairs up only appear with Silmaril
                self.map[self.stairs_up[1]][self.stairs_up[0]] = '<'
            
            best = max(floor_tiles[1:min(20, len(floor_tiles))], 
                      key=lambda p: abs(p[0]-self.stairs_up[0])+abs(p[1]-self.stairs_up[1]))
            self.stairs_down = best
            self.map[self.stairs_down[1]][self.stairs_down[0]] = '>'

    def _populate(self):
        from data.monsters import get_monster_by_level
        from data.items import get_random_item
        from data.potions import get_random_potion
        
        floor_tiles = [(x,y) for y in range(1, self.height-1) for x in range(1, self.width-1)
                      if self.map[y][x] == ' ' and (x,y) not in (self.stairs_up, self.stairs_down)]
        random.shuffle(floor_tiles)
        
        # Original game spawning algorithm (from MORIA.C analysis)
        # Max 25 monsters per level (0x19 from line 2973)
        # Density increases with depth: level 1 = ~8 monsters, level 15 = ~15 monsters
        base_monsters = 8 + (self.level // 2)
        num_monsters = min(25, base_monsters)

        for i in range(min(num_monsters, len(floor_tiles))):
            x, y = floor_tiles[i]
            monster = get_monster_by_level(self.level)
            self.monsters.append({'template': monster, 'x': x, 'y': y, 'hp': monster.hp})

        # Items spawn rate from original: roughly 1 per 80 tiles
        num_items = min(12, max(3, len(floor_tiles) // 80))
        for i in range(num_monsters, min(num_monsters + num_items, len(floor_tiles))):
            x, y = floor_tiles[i]
            item = get_random_item(self.level) if random.random() < 0.6 else get_random_potion(self.level)
            self.items.append({'template': item, 'x': x, 'y': y})

    def is_walkable(self, x: int, y: int) -> bool:
        if not (0 <= x < self.width and 0 <= y < self.height):
            return False
        return self.map[y][x] in (' ', '<', '>')

    def has_monster(self, x: int, y: int) -> bool:
        return any(m['x'] == x and m['y'] == y for m in self.monsters)

    def has_item(self, x: int, y: int) -> bool:
        return any(i['x'] == x and i['y'] == y for i in self.items)

    def get_char_at(self, x: int, y: int) -> str:
        if not (0 <= x < self.width and 0 <= y < self.height):
            return ' '
        return self.map[y][x]

    def is_transparent(self, x: int, y: int) -> bool:
        """Check if a tile blocks line of sight (walls block vision)."""
        if not (0 <= x < self.width and 0 <= y < self.height):
            return False
        char = self.map[y][x]
        # Walls, borders block vision; spaces, stairs don't
        return char in (' ', '<', '>')

    def compute_fov(self, px: int, py: int, radius: int = 8) -> set:
        """
        Compute field of view from player position using shadowcasting.
        Returns set of (x, y) tuples that are visible.
        Walls block line of sight!
        """
        visible = {(px, py)}  # Player can always see their own tile

        # Shadowcasting algorithm - cast rays in all directions
        for angle in range(0, 360, 2):  # Every 2 degrees for smooth FOV
            import math
            rad = math.radians(angle)
            dx = math.cos(rad)
            dy = math.sin(rad)

            # Cast ray from player position
            for step in range(1, radius + 1):
                x = int(px + dx * step)
                y = int(py + dy * step)

                if not (0 <= x < self.width and 0 <= y < self.height):
                    break  # Out of bounds

                visible.add((x, y))

                # If we hit a wall, stop the ray (wall blocks further vision)
                if not self.is_transparent(x, y):
                    break

        return visible

    def update_fov(self, px: int, py: int, radius: int = 8):
        """Update discovered tiles based on current FOV."""
        visible = self.compute_fov(px, py, radius)
        for x, y in visible:
            self.discovered[y][x] = True
        return visible
