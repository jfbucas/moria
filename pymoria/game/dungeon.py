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
        self.height = 22
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
        for y in range(self.height):
            for x in range(self.width):
                if y == 0:
                    self.map[y][x] = '┌' if x == 0 else ('┐' if x == self.width - 1 else '─')
                    self.discovered[y][x] = True  # Border always visible
                elif y == self.height - 1:
                    self.map[y][x] = '└' if x == 0 else ('┘' if x == self.width - 1 else '─')
                    self.discovered[y][x] = True  # Border always visible
                elif x == 0 or x == self.width - 1:
                    self.map[y][x] = '│'
                    self.discovered[y][x] = True  # Border always visible

    def _create_room_grid(self):
        """Create a grid of rooms with walls between them.
        Translated from draw_dungeon_border() at lines 3148-3174.

        The grid has:
        - 10 rows x 39 columns = 390 rooms
        - Each room is 2x2 walkable tiles
        - Walls drawn between rooms
        """
        # Fill everything with SPACES first (rooms are walkable)
        for y in range(1, self.height - 1):
            for x in range(1, self.width - 1):
                self.map[y][x] = ' '

        # Draw vertical walls between room columns
        # Lines 3148-3154: vertical walls (0xb3 = │)
        # These are at x = col*2+1 for col = 1..38
        for row in range(0, 11+1):  # rows 0-10
            for col in range(1, 39):  # cols 1-38 (between columns)
                map_y = row * 2       +1
                map_x = col * 2 #+ 1
                if 1 <= map_y < self.height - 1 and 1 <= map_x < self.width - 1:
                    self.map[map_y][map_x] = '│'
                    #self.map[map_y][map_x] = 'a'

        # Draw horizontal walls between room rows
        # Lines 3157-3165: horizontal walls (0xc4 = ─)
        # These are at y = row*2+1 for row = 1..9
        for row in range(1, 10):  # rows 1-9 (between rows)
            for col in range(0, 39+1):  # cols 0-38
                map_y = row * 2 #+ 1
                map_x = col * 2  +1    
                if 1 <= map_y < self.height - 1 and 1 <= map_x < self.width - 1:
                    self.map[map_y][map_x] = '─'

        # Draw crosses at intersections
        # Lines 3166-3174: crosses (0xc5 = ┼)
        for row in range(1, 10):  # rows 1-9
            for col in range(1, 39):  # cols 1-38
                map_y = row * 2 #+ 1
                map_x = col * 2 #+ 1
                if 1 <= map_y < self.height - 1 and 1 <= map_x < self.width - 1:
                    self.map[map_y][map_x] = '┼'

    def _generate_corridors(self):
        """Generate dungeon corridors using Kruskal's MST algorithm.
        Translated from MORIA.C generate_dungeon_corridors() at lines 3040-3131.

        The algorithm:
        - 391 vertical corridors connect rooms vertically (row i to row i+1)
        - 417 horizontal corridors connect rooms horizontally (col i to col i+1)
        - Total: 808 corridor positions
        - Uses Union-Find to build minimum spanning tree
        """
        ROOM_COLS = 39  # 0x27
        ROOM_ROWS = 10  # 0xa
        total_rooms = ROOM_ROWS * ROOM_COLS  # 390

        # Initialize union-find for all rooms
        uf = UnionFind(total_rooms)

        # Generate all 808 corridors in random order (Kruskal's algorithm)
        corridors = list(range(1, 809))
        random.shuffle(corridors)

        for position in corridors:
            if position <= 391:  # Vertical corridor
                # Lines 3057-3058: Calculate room coordinates
                row = (position - 1) // ROOM_COLS  # (pos-1)/0x27
                col = (position - 1) % ROOM_COLS   # (pos-1)%0x27

                # This vertical corridor connects room(row,col) to room(row+1,col)
                # Line 3070: position + 0x27 (position + 39)
                room1 = row * ROOM_COLS + col
                room2 = (row + 1) * ROOM_COLS + col

                # Check bounds
                if room2 >= total_rooms:
                    continue

                # Lines 3071-3074: Check if rooms are in different regions
                if uf.find(room1) != uf.find(room2):
                    # Vertical corridor opens the horizontal wall between vertically adjacent rooms
                    # Wall is at y = (row+1)*2+1 (between row and row+1)
                    # Corridor opens one cell in the middle of wall at x = col*2+1 or col*2+2
                    map_y = (row + 1) * 2 + 1  # The horizontal wall position
                    map_x = col * 2 + 2  # Middle of the room column

                    if 1 <= map_y < self.height - 1 and 1 <= map_x < self.width - 1:
                        # Line 3080: Write 0x20 (space) at corridor position
                        self.map[map_y][map_x] = ' '

                        # Lines 3082-3089: Union the two rooms
                        uf.union(room1, room2)

            else:  # Horizontal corridor
                # Line 3094: Adjust position for horizontal corridors
                adj_pos = position - 390  # position - 0x186

                # Lines 3095-3096: Calculate coordinates
                row = (adj_pos - 1) // 11  # (pos-1)/0xb
                col = (adj_pos - 1) % 11   # (pos-1)%0xb

                # Line 3107: This connects room at (col-1)*39+row to (col-1)*39+row+1
                room1 = col * ROOM_COLS + row
                room2 = col * ROOM_COLS + row + 1

                # Check bounds
                if room2 >= total_rooms:
                    continue

                # Lines 3109-3112: Check if rooms are in different regions
                if uf.find(room1) != uf.find(room2):
                    # Horizontal corridor opens the vertical wall between horizontally adjacent rooms
                    # room1 = col*39 + row is at grid position (row=col, col=row) - confusing naming!
                    # room2 = room1+1 means columns differ by 1
                    # Wall is at x = (row+1)*2+1 (between columns row and row+1)
                    # Corridor opens one cell in the middle of wall at y = col*2+1 or col*2+2
                    map_y = col * 2 + 2  # Middle of the room row
                    map_x = (row + 1) * 2 + 1  # The vertical wall position

                    if 1 <= map_y < self.height - 1 and 1 <= map_x < self.width - 1:
                        # Line 3117: Write 0x20 at corridor position
                        self.map[map_y][map_x] = ' '

                        # Lines 3119-3126: Union the two rooms
                        uf.union(room1, room2)

    def _generate_room(self):
        """Generate one room per level, matching original generate_dungeon_level().
        Lines 3185-3356 in MORIA_with_constants.C.
        Room overlays the grid, using T-junction chars for walls:
          ┴ (0xc1) top wall, ┬ (0xc2) bottom wall,
          ┤ (0xb4) left wall, ├ (0xc3) right wall.
        Interior grid walls are cleared to spaces."""
        if self.level < 1:
            return

        # Room dimensions (from original formulas)
        max_w_rand = max(1, 16 - self.level)
        room_w = random.randint(0, max_w_rand - 1) * 2 + 8
        max_h_rand = max(1, (19 - self.level) // 3)
        room_h = random.randint(0, max_h_rand - 1) * 2 + 4

        # Room position (converted from 1-indexed original to 0-indexed)
        max_x_rand = max(1, 38 - room_w // 2)
        room_x = random.randint(0, max_x_rand - 1) * 2 + 2
        max_y_rand = max(1, 9 - room_h // 2)
        room_y = random.randint(0, max_y_rand - 1) * 2 + 2

        # Clamp to dungeon bounds
        if room_x + room_w >= self.width - 1:
            room_w = ((self.width - 2 - room_x) // 2) * 2
        if room_y + room_h >= self.height - 1:
            room_h = ((self.height - 2 - room_y) // 2) * 2

        if room_w < 4 or room_h < 4:
            return

        # Phase 1: Top and bottom walls
        for i in range(1, room_w // 2):
            x = room_x + i * 2
            if 1 <= x < self.width - 1:
                if 1 <= room_y < self.height - 1:
                    self.map[room_y][x] = '┴'
                if 1 <= room_y + 1 < self.height - 1:
                    self.map[room_y + 1][x] = ' '
                if 1 <= room_y + room_h < self.height - 1:
                    self.map[room_y + room_h][x] = '┬'

        # Phase 2: Left and right walls
        for i in range(1, room_h // 2):
            y = room_y + i * 2
            if 1 <= y < self.height - 1:
                if 1 <= room_x < self.width - 1:
                    self.map[y][room_x] = '┤'
                if 1 <= room_x + 1 < self.width - 1:
                    self.map[y][room_x + 1] = ' '
                if 1 <= room_x + room_w < self.width - 1:
                    self.map[y][room_x + room_w] = '├'

        # Phase 3: Interior fill - clear ALL cells inside room walls.
        # Original C code (lines 3288-3313) clears 3 cells per grid unit:
        #   crossing (even,even), vertical wall below, horizontal wall right.
        # The 4th cell (odd,odd) is already space in the C grid layout.
        # Our Python grid has ┼ at (odd,odd) instead, so we must clear all 4.
        for y in range(room_y + 1, room_y + room_h):
            for x in range(room_x + 1, room_x + room_w):
                if 1 <= x < self.width - 1 and 1 <= y < self.height - 1:
                    self.map[y][x] = ' '

        self.rooms.append((room_x, room_y, room_w, room_h))

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
