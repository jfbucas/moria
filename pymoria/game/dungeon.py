"""
Dungeon Generation for PyMoria
Reference: reverse/MORIA_COMPLETE.md Section 6.4, reverse/MONSTER_SPAWNING.md

Dungeon structure (from draw_dungeon_border / generate_dungeon_corridors C source):
  - 10 rows × 39 cols of 1-tile "cells" arranged in a regular grid.
  - Cell (r, c): floor tile at map position (row=r*2, col=c*2), r=0..9, c=0..38.
  - Horizontal separator between (r,c) and (r,c+1): tile at (r*2, c*2+1) = '│' (wall).
  - Vertical   separator between (r,c) and (r+1,c): tile at (r*2+1, c*2) = '─' (wall).
  - Kruskal's MST removes separators to open passages (sets them to ' ').
  - After MST: one extra enclosed room with wall chars ┴┬┤├ is placed.
  - Stairs, items, and monsters are then placed on empty floor tiles.

CRITICAL coordinate convention: level.set_tile(col, row) → tiles[row][col].
"""

import random
from collections import deque
from typing import Optional, Tuple, List

from game.entities import DungeonLevel, Item, Monster
from data.monsters import get_monster_template

# =============================================================================
# CONSTANTS
# =============================================================================

GRID_ROWS = 10   # 10 rows of cells
GRID_COLS = 39   # 39 columns of cells (cell cols: 0,2,...,76; sep cols: 1,3,...,75)

MAX_MONSTERS_PER_LEVEL = 25

# Item spawn config [base, rand, extra] — Reference: MONSTER_SPAWNING.md §2, DS:0x79D7
# Spawn type 0-8: Gold, Food, Potion, Scroll, Ring, Wand, Armor, Weapon, Light
ITEM_SPAWN_CONFIG = [
    [5, 5, 0],   # 0: Gold
    [1, 4, 0],   # 1: Food
    [3, 5, 3],   # 2: Potion
    [3, 4, 3],   # 3: Scroll
    [1, 2, 2],   # 4: Ring
    [1, 3, 2],   # 5: Wand
    [1, 2, 3],   # 6: Armor
    [1, 1, 3],   # 7: Weapon
    [0, 2, 0],   # 8: Light
]

# Display chars by spawn type (for map tiles)
_ITEM_DISPLAY = ['$', '%', '!', '?', '=', '/', ']', ')', '☼']

# Monster spawn weight table: MONSTER_WEIGHTS[template_id][dungeon_level - 1]
# Reference: MONSTER_SPAWNING.md §3, DS:0xAB93 (28 templates × 15 levels)
MONSTER_WEIGHTS: List[List[int]] = [
    [0]*15,                                          #  0: (placeholder)
    [0,0,0,0,0,0,2,4,5,5,2,0,0,0,0],               #  1: Air
    [20,18,12,8,4,0,0,0,0,0,0,0,0,0,0],             #  2: Araignée
    [0,0,0,0,0,0,0,0,0,0,0,2,4,4,6],               #  3: Balrog
    [10,10,10,8,6,2,0,0,0,0,0,0,0,0,0],             #  4: Chauve Souris
    [0,3,9,12,5,0,0,0,0,0,0,0,0,0,0],              #  5: Crébain
    [0,0,0,0,0,0,1,1,2,4,2,0,0,0,0],               #  6: Dragon
    [0,0,0,0,0,0,0,0,0,2,2,4,4,5,5],               #  7: Dragon Ailé
    [2,2,4,6,7,4,4,4,4,4,4,4,4,0,0],               #  8: œil de Sauron
    [0,0,0,0,0,1,2,3,3,4,4,3,3,2,1],               #  9: Fée
    [0,0,0,0,1,3,6,8,10,6,4,2,0,0,0],              # 10: Galgal
    [2,4,8,17,14,12,6,2,0,0,0,0,0,0,0],             # 11: Gobelin
    [0,0,0,1,3,4,5,5,4,0,0,0,0,0,0],               # 12: Huorn
    [5,10,20,12,10,8,4,2,0,0,0,0,0,0,0],            # 13: Loup
    [0,0,0,0,0,2,4,4,2,2,0,0,0,0,0],               # 14: Loup Garou
    [0,0,0,1,1,2,4,8,9,8,8,8,5,4,4],               # 15: Mewlip
    [0,0,1,4,8,12,8,0,0,0,0,0,0,0,0],              # 16: Moricaud
    [0,0,0,0,0,0,0,1,2,4,6,4,3,2,2],               # 17: Nazgûl
    [0,0,0,0,0,0,0,0,0,1,2,4,5,6,6],               # 18: Oliphant
    [0,4,6,10,12,12,10,8,6,0,0,0,0,0,0],            # 19: Orc
    [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10], # 20: Rat
    [15,20,15,15,10,8,6,4,0,0,0,0,0,0,0],           # 21: Serpent
    [0,0,0,0,0,0,0,0,0,0,0,1,3,5,5],               # 22: Succube
    [0,0,0,0,2,3,5,7,5,2,2,2,0,0,0],               # 23: Troll
    [0,0,2,4,9,15,16,10,10,10,10,10,10,10,10],      # 24: Uruk-haï
    [0,1,2,6,10,7,0,0,0,0,0,0,0,0,0],              # 25: Variag
    [0,0,0,0,0,3,4,5,5,6,6,5,5,4,3],               # 26: Voleur
    [0,0,1,3,9,11,13,10,8,4,2,0,0,0,0],             # 27: Wharg
    [0,0,0,0,1,3,5,7,4,0,0,0,0,0,0],               # 28: Woose
]


# =============================================================================
# UNION-FIND (for Kruskal's MST)
# =============================================================================

class _UnionFind:
    """Path-compressed union-find for Kruskal's MST."""

    def __init__(self, n: int):
        self.parent = list(range(n))

    def find(self, x: int) -> int:
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]  # path halving
            x = self.parent[x]
        return x

    def union(self, x: int, y: int) -> bool:
        """Returns True if x and y were in different components (edge was useful)."""
        px, py = self.find(x), self.find(y)
        if px == py:
            return False
        self.parent[px] = py
        return True


# =============================================================================
# HELPER: FIND EMPTY FLOOR TILE
# =============================================================================

def _find_empty_floor(level: DungeonLevel) -> Optional[Tuple[int, int]]:
    """
    Find a random empty floor tile (space ' ').
    Returns (col, row) = (x, y), or None if none found after 200 tries.
    Reference: MONSTER_SPAWNING.md §8 find_random_empty_floor_space
    """
    for _ in range(200):
        row = random.randint(0, 19)
        col = random.randint(0, 78)
        if level.get_tile(col, row) == ' ':
            return (col, row)
    return None


# =============================================================================
# ITEM CREATION & SPAWNING
# =============================================================================

def _favored_type(dungeon_level: int) -> int:
    """
    Determine 'favored' item spawn type for a given depth.
    Reference: MONSTER_SPAWNING.md §2
    """
    if dungeon_level >= 12:
        return 7   # Weapon
    if dungeon_level >= 9:
        return 6   # Armor
    if dungeon_level >= 6:
        return 3   # Scroll
    if dungeon_level >= 4:
        return 2   # Potion
    if dungeon_level >= 2:
        return 4   # Ring
    return 5       # Wand (level 1)


def _make_item(spawn_type: int, dungeon_level: int) -> Item:
    """
    Create one Item of the given spawn-config type (0-8).
    Maps spawn types to entities.py Item type constants.
    """
    item = Item()
    item.display_char = _ITEM_DISPLAY[spawn_type]

    if spawn_type == 0:    # Gold
        item.type = 8      # ITEM_TREASURE
        item.subtype = 0
        item.set_total_value(random.randint(1, dungeon_level * 10 + 10))

    elif spawn_type == 1:  # Food
        item.type = 0      # ITEM_FOOD
        item.subtype = random.randint(1, 4)

    elif spawn_type == 2:  # Potion
        item.type = 1      # ITEM_POTION
        item.subtype = random.randint(1, 24)

    elif spawn_type == 3:  # Scroll
        item.type = 2      # ITEM_SCROLL
        item.subtype = random.randint(0, 24)

    elif spawn_type == 4:  # Ring
        item.type = 4      # ITEM_RING
        item.subtype = random.randint(1, 8)

    elif spawn_type == 5:  # Wand
        item.type = 3      # ITEM_WAND
        item.subtype = random.randint(1, 22)
        item.power = random.randint(3, 10)   # charges

    elif spawn_type == 6:  # Armor (no dedicated type in entities.py; use 5 = ITEM_CHEST)
        item.type = 5
        item.subtype = random.randint(1, 10)
        item.power = random.randint(0, 4)

    elif spawn_type == 7:  # Weapon
        item.type = 6      # ITEM_WEAPON
        item.subtype = random.randint(1, 10)
        item.power = random.randint(0, 4)

    elif spawn_type == 8:  # Light
        item.type = 7      # ITEM_AMMUNITION (repurposed for light)
        item.subtype = random.randint(1, 5)

    return item


def _spawn_items(level: DungeonLevel, dungeon_level: int) -> None:
    """
    Populate level with items using the spawn config table.
    Reference: MONSTER_SPAWNING.md §2
    """
    favored = _favored_type(dungeon_level)

    for spawn_type in range(9):
        base, rand_v, extra = ITEM_SPAWN_CONFIG[spawn_type]
        count = base + (random.randint(0, rand_v - 1) if rand_v > 0 else 0)
        if spawn_type == favored and extra > 0:
            count += random.randint(0, extra - 1) + 1

        for _ in range(count):
            pos = _find_empty_floor(level)
            if pos is None:
                break
            col, row = pos
            item = _make_item(spawn_type, dungeon_level)
            item.col = col
            item.row = row
            # Write display char to tile (original writes to map buffer layer -0x50)
            level.set_tile(col, row, item.display_char)
            level.floor_items.append(item)


# =============================================================================
# MONSTER CREATION & SPAWNING
# =============================================================================

def spawn_monster_from_template(template_id: int, dungeon_level: int,
                                player=None) -> Optional[Monster]:
    """
    Create a Monster instance from a template.
    Reference: MONSTER_SPAWNING.md §8 spawn_monster_from_template (line 2534)

    Args:
        template_id: 1-35 monster template index
        dungeon_level: current dungeon level (for level-scaling)
        player: Player instance (for level-scaling threshold)

    Returns:
        Populated Monster, or None if invalid template.
    """
    tmpl = get_monster_template(template_id)
    if tmpl is None:
        return None

    m = Monster()
    m.template_id = template_id
    m.char = tmpl.char
    m.display_char = tmpl.char
    m.base_char = tmpl.char
    m.name_french = tmpl.name_french
    m.max_hp = tmpl.hit_points
    m.current_hp = tmpl.hit_points
    m.armor_class = tmpl.armor_class
    m.to_hit = tmpl.to_hit
    m.num_attacks = tmpl.num_attacks
    m.damage_per_attack = tmpl.damage_per_attack
    m.speed_bonus = tmpl.speed_bonus
    m.experience = tmpl.experience
    m.is_invisible = tmpl.is_invisible
    m.is_hostile = tmpl.is_hostile
    m.is_stationary = tmpl.is_stationary
    m.is_unique = tmpl.is_stationary
    m.is_alive = True
    m.move_toggle = 0
    m.is_awake = False
    m.is_alerted = False
    m.is_fleeing = False
    m.status_timer = 0

    # attack_char_code: single-byte chars map directly to their code point (matches monster_ai constants)
    ch = tmpl.char
    if len(ch) == 1:
        code = ord(ch)
        m.attack_char_code = code if code <= 0xFF else 0
    else:
        m.attack_char_code = 0

    # Extra fields used by monster_ai via getattr (not declared in Monster dataclass).
    # Non-frozen dataclass allows dynamic attribute assignment.
    m.level = tmpl.level                     # type: ignore[attr-defined]
    m.special_ability_1 = tmpl.special_ability  # type: ignore[attr-defined]

    # Level scaling: buff weak monsters to match player
    # Reference: MONSTER_SPAWNING.md §8, line 536-538
    if player is not None:
        threshold = player.player_level + player.base_ac + 5
        if m.to_hit + m.speed_bonus < threshold:
            m.to_hit += 1
            m.speed_bonus = player.player_level + player.base_ac + 6 - m.to_hit

    # Eye of Sauron: always awake, permanent status_timer
    if tmpl.char == 'E':
        m.is_awake = True
        m.status_timer = 0xFFFF   # permanent

    return m


def _spawn_initial_monsters(level: DungeonLevel, dungeon_level: int,
                             player=None) -> None:
    """
    Place a small initial monster population on a freshly-generated level.

    NOTE: The original spawns monsters via populate_level_with_monsters every
    20 turns (not at generation time). We place ~3 monsters at generation to
    give the player something to encounter immediately; the rest arrive during
    gameplay via game_loop.spawn_monsters().
    """
    if not 1 <= dungeon_level <= 15:
        return

    level_idx = dungeon_level - 1

    # Build weighted pool of template IDs for this level
    pool: List[int] = []
    for tid in range(1, 29):
        weight = MONSTER_WEIGHTS[tid][level_idx]
        if weight > 0:
            pool.extend([tid] * weight)

    if not pool:
        return

    for _ in range(3):
        if len(level.monsters) >= MAX_MONSTERS_PER_LEVEL:
            break
        tid = random.choice(pool)
        monster = spawn_monster_from_template(tid, dungeon_level, player)
        if monster is None:
            continue
        pos = _find_empty_floor(level)
        if pos is None:
            continue
        monster.col, monster.row = pos
        level.monsters.append(monster)


def populate_level_with_monsters(level: DungeonLevel, dungeon_level: int,
                                  player=None) -> None:
    """
    Wandering monster spawner — called from game loop every 20 turns.
    Reference: MONSTER_SPAWNING.md §4 populate_level_with_monsters (line 2950)

    Iterates all 28 templates; each has a level-dependent weight.
    Monsters spawn near the player position.
    """
    if not 1 <= dungeon_level <= 15:
        return

    level_idx = dungeon_level - 1

    for template_id in range(1, 29):
        if len(level.monsters) >= MAX_MONSTERS_PER_LEVEL:
            break

        weight = MONSTER_WEIGHTS[template_id][level_idx]
        if weight == 0:
            continue

        # Probability check: higher weight = more likely to spawn
        # Simplified from garbled decompilation: random threshold vs weight
        if random.randint(0, 200) >= weight:
            continue

        monster = spawn_monster_from_template(template_id, dungeon_level, player)
        if monster is None:
            continue

        # Spawn near player if player provided, else random empty floor
        pos = None
        if player is not None:
            for _ in range(50):
                dy = random.randint(-2, 2)
                dx = random.randint(-2, 2)
                row = max(0, min(19, player.y + dy))
                col = max(0, min(78, player.x + dx))
                if level.get_tile(col, row) == ' ' and level.get_monster_at(col, row) is None:
                    pos = (col, row)
                    break
        if pos is None:
            pos = _find_empty_floor(level)
        if pos is None:
            continue

        monster.col, monster.row = pos
        level.monsters.append(monster)


# =============================================================================
# BOSS MONSTER INITIALIZATION
# =============================================================================

def initialize_boss_monsters(levels: dict, player=None) -> None:
    """
    Place all unique boss monsters once at game initialization.
    Reference: MONSTER_SPAWNING.md §5

    Boss monsters are pre-placed at game start on their assigned levels.
    They are NOT generated by the normal monster spawner.
    """
    def _ensure_level(lvl_num: int) -> DungeonLevel:
        if lvl_num not in levels:
            levels[lvl_num] = DungeonLevel(level_number=lvl_num)
        return levels[lvl_num]

    def _add_boss(template_id: int, lvl_num: int,
                  carried: Optional[Item] = None) -> None:
        lvl = _ensure_level(lvl_num)
        m = spawn_monster_from_template(template_id, lvl_num, player)
        if m is None:
            return
        # Placeholder position — will be moved to a valid floor tile when
        # the level is first generated
        m.row = 10
        m.col = 39
        m.is_stationary = True
        m.carried_item = carried
        lvl.monsters.append(m)

    # Carcharoth (template 29): level 8 or 9
    # Reference: MONSTER_SPAWNING.md spawn_wandering_monster
    _add_boss(29, random.randint(8, 9))

    # Disguised Sauron (template 34): level 10–12, carries Ring of Invisibility
    # Reference: MONSTER_SPAWNING.md spawn_special_monster_with_item
    ring = Item(type=4, subtype=6, power=random.randint(50, 99),
                display_char='=')
    _add_boss(34, random.randint(10, 12), ring)

    # Saruman (template 32): level 10
    # Reference: MONSTER_SPAWNING.md prepend_monster_to_global_list
    _add_boss(32, 10)

    # Glaurung (template 30): level 12 or 13
    # Reference: MONSTER_SPAWNING.md add_monster_to_level_list
    _add_boss(30, random.randint(12, 13))

    # Ungoliant (template 31): level 14
    # Reference: MONSTER_SPAWNING.md spawn_monster_type_1f
    _add_boss(31, 14)

    # Morgoth (template 35): level 15, carries Silmaril
    # Reference: MONSTER_SPAWNING.md spawn_unique_monster_type_23
    silmaril_carried = Item(type=7, subtype=0, display_char='☼')
    _add_boss(35, 15, silmaril_carried)

    # Floor Silmaril on level 15 (separate from Morgoth's)
    # Reference: MONSTER_SPAWNING.md §6 (line ~3742)
    lvl15 = _ensure_level(15)
    floor_silmaril = Item(type=7, subtype=0, display_char='☼')
    floor_silmaril.row = 10
    floor_silmaril.col = 40
    lvl15.floor_items.append(floor_silmaril)


# =============================================================================
# CONNECTIVITY REPAIR
# =============================================================================

_IMPASSABLE = {'#', '┴', '┬', '┤', '├', '─', '│', '+'}


def _repair_connectivity(tiles: List[List[str]]) -> None:
    """
    After room placement, some passable tiles may be unreachable because
    the room boundary walls block spanning-tree paths.  Find every
    disconnected passable region and carve an L-shaped corridor back to
    the main component.

    Runs in O(n²) on the 20×79 = 1 580-tile map — fast enough.
    """
    def _passable(r: int, c: int) -> bool:
        return 0 <= r < 20 and 0 <= c < 79 and tiles[r][c] not in _IMPASSABLE

    def _bfs(sr: int, sc: int) -> set:
        """Return the set of all passable tiles reachable from (sr, sc)."""
        vis: set = set()
        q: deque = deque()
        q.append((sr, sc))
        vis.add((sr, sc))
        while q:
            r, c = q.popleft()
            for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                nr, nc = r + dr, c + dc
                if _passable(nr, nc) and (nr, nc) not in vis:
                    vis.add((nr, nc))
                    q.append((nr, nc))
        return vis

    # Find any starting passable tile (top-left sweep)
    start = next(
        ((r, c) for r in range(20) for c in range(79) if _passable(r, c)),
        None
    )
    if start is None:
        return

    for _ in range(400):          # safety cap — normally converges in <10 iters
        main = _bfs(*start)

        # Find first unreachable passable tile
        unreachable = next(
            ((r, c) for r in range(20) for c in range(79)
             if _passable(r, c) and (r, c) not in main),
            None
        )
        if unreachable is None:
            break                  # fully connected

        ur, uc = unreachable

        # Find the closest tile in the main component (Manhattan distance)
        best_dist = 99999
        best_mr, best_mc = start
        for mr, mc in main:
            d = abs(ur - mr) + abs(uc - mc)
            if d < best_dist:
                best_dist = d
                best_mr, best_mc = mr, mc

        # Carve L-shaped tunnel: move vertically first, then horizontally
        r, c = best_mr, best_mc
        while r != ur:
            r += 1 if ur > r else -1
            if tiles[r][c] in _IMPASSABLE:
                tiles[r][c] = ' '
        while c != uc:
            c += 1 if uc > c else -1
            if tiles[r][c] in _IMPASSABLE:
                tiles[r][c] = ' '


# =============================================================================
# MAIN DUNGEON GENERATION
# =============================================================================

def generate_dungeon_level(dungeon_level: int, player=None) -> DungeonLevel:
    """
    Generate a complete dungeon level.
    Reference: MORIA_COMPLETE.md §6.4, draw_dungeon_border + generate_dungeon_level C functions.

    Algorithm:
    1. Initialize 20×79 tile map with '#' (solid wall).
    2. Place 10×39 grid of floor cells at even (row, col) positions.
    3. Place separator walls between adjacent cells (│ horizontal, ─ vertical).
    4. Kruskal's random spanning tree opens passages through separators.
    5. Place one extra enclosed room with wall chars ┴┬┤├.
    6. Place stairs '<' (up) and '>' (down) on random empty floor tiles.
    7. Spawn items via _spawn_items().
    8. Place initial monster population via _spawn_initial_monsters().

    Returns:
        Fully populated DungeonLevel instance.
    """
    level = DungeonLevel(level_number=dungeon_level)
    tiles = level.tiles  # tiles[row][col], 20 rows × 79 cols

    # -------------------------------------------------------------------------
    # STEP 1: Fill map with solid walls
    # -------------------------------------------------------------------------
    for row in range(20):
        for col in range(79):
            tiles[row][col] = '#'

    # -------------------------------------------------------------------------
    # STEP 2 & 3: Place cell floors and separator walls
    #
    # Cell (r, c): floor tile at (row=r*2, col=c*2)        r=0..9, c=0..38
    # H-sep (r,c)↔(r,c+1): '│' at (r*2, c*2+1)
    # V-sep (r,c)↔(r+1,c): '─' at (r*2+1, c*2)
    # -------------------------------------------------------------------------
    for r in range(GRID_ROWS):
        for c in range(GRID_COLS):
            tiles[r * 2][c * 2] = ' '
            if c < GRID_COLS - 1:
                tiles[r * 2][c * 2 + 1] = '│'
            if r < GRID_ROWS - 1:
                tiles[r * 2 + 1][c * 2] = '─'

    # -------------------------------------------------------------------------
    # STEP 4: Kruskal's random spanning tree
    #
    # All edges have equal cost → shuffle → use union-find to connect
    # components. This creates a random spanning tree (every cell reachable).
    # Reference: generate_dungeon_corridors C function (line 3040)
    # -------------------------------------------------------------------------
    edges: List[Tuple[str, int, int]] = []
    for r in range(GRID_ROWS):
        for c in range(GRID_COLS):
            if c < GRID_COLS - 1:
                edges.append(('H', r, c))   # (r,c) ↔ (r, c+1)
            if r < GRID_ROWS - 1:
                edges.append(('V', r, c))   # (r,c) ↔ (r+1, c)
    random.shuffle(edges)

    uf = _UnionFind(GRID_ROWS * GRID_COLS)
    for kind, r, c in edges:
        if kind == 'H':
            idx1 = r * GRID_COLS + c
            idx2 = r * GRID_COLS + (c + 1)
            if uf.union(idx1, idx2):
                tiles[r * 2][c * 2 + 1] = ' '   # open H-sep
        else:  # 'V'
            idx1 = r * GRID_COLS + c
            idx2 = (r + 1) * GRID_COLS + c
            if uf.union(idx1, idx2):
                tiles[r * 2 + 1][c * 2] = ' '   # open V-sep

    # -------------------------------------------------------------------------
    # STEP 5: One extra enclosed room with proper wall chars
    #
    # The room boundary uses wall chars (┴┬┤├) at cell positions (even row/col).
    # The separator slots between wall chars are set to '#' to seal the boundary.
    # Explicit entrances are carved per wall side to guarantee connectivity.
    # Reference: generate_dungeon_level C function (line 3257–3313)
    # Wall chars: ┴ top (0xC1), ┬ bottom (0xC2), ┤ left (0xB4), ├ right (0xC3)
    # -------------------------------------------------------------------------
    # Room size in grid cells (internal size, excluding boundary wall row/col)
    room_rows = random.randint(2, 4)   # internal rows of cells
    room_cols = random.randint(3, 6)   # internal cols of cells

    max_gr = GRID_ROWS - 2 - room_rows
    max_gc = GRID_COLS - 2 - room_cols
    if max_gr > 0 and max_gc > 0:
        room_gr = random.randint(0, max_gr)   # grid row of top wall
        room_gc = random.randint(0, max_gc)   # grid col of left wall

        # Map row/col of the four boundary walls (at even positions = cell positions)
        top_row   = room_gr * 2
        left_col  = room_gc * 2
        bot_row   = (room_gr + room_rows + 1) * 2
        right_col = (room_gc + room_cols + 1) * 2

        # Draw solid boundary: wall chars at even positions, '#' at odd positions
        for col in range(left_col, right_col + 1):
            tiles[top_row][col] = '┴' if col % 2 == 0 else '#'
            tiles[bot_row][col] = '┬' if col % 2 == 0 else '#'
        for row in range(top_row, bot_row + 1):
            tiles[row][left_col]  = '┤' if row % 2 == 0 else '#'
            tiles[row][right_col] = '├' if row % 2 == 0 else '#'

        # Clear interior (all positions inside the boundary walls)
        for row in range(top_row + 1, bot_row):
            for col in range(left_col + 1, right_col):
                tiles[row][col] = ' '

        # ---- CARVE ENTRANCES: one per wall side ----
        # Pick a mid-point cell on each wall and clear wall + separator + interior.
        def _carve(wr: int, wc: int, sr: int, sc: int) -> None:
            """Clear wall tile and its external separator to space."""
            if 0 <= wr < 20 and 0 <= wc < 79:
                tiles[wr][wc] = ' '
            if 0 <= sr < 20 and 0 <= sc < 79:
                tiles[sr][sc] = ' '

        # Choose internal cell positions for entrances
        mid_gc = room_gc + 1 + random.randint(0, room_cols - 1)   # col within room
        mid_gr = room_gr + 1 + random.randint(0, room_rows - 1)   # row within room

        # Top entrance: clear wall at top_row and separator row above
        _carve(top_row, mid_gc * 2, top_row - 1, mid_gc * 2)
        # Bottom entrance
        _carve(bot_row, mid_gc * 2, bot_row + 1, mid_gc * 2)
        # Left entrance
        _carve(mid_gr * 2, left_col, mid_gr * 2, left_col - 1)
        # Right entrance
        _carve(mid_gr * 2, right_col, mid_gr * 2, right_col + 1)

    # Repair any connectivity broken by the room boundary walls
    _repair_connectivity(tiles)

    # -------------------------------------------------------------------------
    # STEP 6: Stairs
    #
    # Stairs up '<' always placed (needed on all levels for going up).
    # Stairs down '>' placed on all levels except level 15 (deepest).
    # Reference: generate_dungeon_level C function (lines 3208–3232)
    # -------------------------------------------------------------------------
    pos = _find_empty_floor(level)
    if pos:
        col, row = pos
        tiles[row][col] = '<'
        level.stairs_up_row = row
        level.stairs_up_col = col

    if dungeon_level < 15:
        pos = _find_empty_floor(level)
        if pos:
            col, row = pos
            tiles[row][col] = '>'
            level.stairs_down_row = row
            level.stairs_down_col = col

    # -------------------------------------------------------------------------
    # STEP 7: Spawn items
    # -------------------------------------------------------------------------
    _spawn_items(level, dungeon_level)

    # -------------------------------------------------------------------------
    # STEP 8: Initial monster population
    # -------------------------------------------------------------------------
    _spawn_initial_monsters(level, dungeon_level, player)

    # Mark as generated
    level.visited_flag = True
    return level
