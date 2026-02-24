"""
Monster AI for PyMoria
Reference: reverse/MONSTER_AI.md

Turn-based AI using greedy Manhattan distance pathfinding.
All monsters use move_toggle — every monster moves every 2 turns.
"""

import random
from typing import Tuple, Optional

from game.entities import Monster, Player, DungeonLevel
from utils.constants import (
    MAP_WIDTH, MAP_HEIGHT,
    WAKE_DISTANCE, ALERT_DISTANCE,
)

# =============================================================================
# ATTACK CHAR CODES (byte values from original DOS binary)
# =============================================================================

ATTACK_CHAR_BAT    = 0x43  # 'C' — Bat (wanders randomly)
ATTACK_CHAR_AIR    = 0x61  # 'a' — Air elemental (wanders randomly)
ATTACK_CHAR_EYE    = 0x45  # 'E' — Eye of Sauron (never moves)
ATTACK_CHAR_HUORN  = 0x48  # 'H' — Huorn (only when adjacent to player)
ATTACK_CHAR_GHOST2 = 0xEA  # Ghost type 2 (regens HP to 500, 1/65 reveal)
ATTACK_CHAR_GHOST1 = 0xE8  # Ghost type 1 (regens HP to 350)
ATTACK_CHAR_SAURON = 0x01  # Sauron (regens HP to 150)
ATTACK_CHAR_SARUMAN = 0xE4 # Saruman (regens HP to 100, 1/70 reveal)

# HP regen caps (boss monsters only)
REGEN_CAP_GHOST2  = 500
REGEN_CAP_GHOST1  = 350
REGEN_CAP_SAURON  = 150
REGEN_CAP_SARUMAN = 100

# Reveal-on-map RNG thresholds
REVEAL_CHANCE_GHOST2   = 65  # 1/65 chance per turn
REVEAL_CHANCE_SARUMAN  = 70  # 1/70 chance per turn

# =============================================================================
# GEOMETRY HELPERS
# =============================================================================

def _get_sign(value: int) -> int:
    """Returns -1, 0, or +1 — sign of value."""
    if value == 0:
        return 0
    return 1 if value > 0 else -1


def _manhattan(monster: Monster, player: Player) -> int:
    """Manhattan distance from monster to player."""
    return abs(player.y - monster.row) + abs(player.x - monster.col)


def _is_adjacent(monster: Monster, player: Player) -> bool:
    """True if monster is directly adjacent (4-directional) to player."""
    dr = abs(player.y - monster.row)
    dc = abs(player.x - monster.col)
    return (dr == 0 and dc == 1) or (dr == 1 and dc == 0)


def _in_bounds(row: int, col: int) -> bool:
    """True if (row, col) is within the dungeon map."""
    return 0 <= row < MAP_HEIGHT and 0 <= col < MAP_WIDTH


# =============================================================================
# TILE VALIDATION
# =============================================================================

def _tile_passable_for_monster(level: DungeonLevel, row: int, col: int) -> bool:
    """
    True if the tile at (row, col) can be walked on by a monster.
    Only empty floor (' ') is considered passable; walls and corridor
    border chars are not.
    Reference: MONSTER_AI.md Section 5 (tile_char == 0x20 check).
    """
    if not _in_bounds(row, col):
        return False
    return level.get_tile(col, row) == ' '


def _validate_tile_movement(monster: Monster, level: DungeonLevel,
                             dc: int, dr: int, player: Player) -> bool:
    """
    Check if monster can move by (dc, dr) — delta column, delta row.
    Returns True if the target tile is reachable.

    Steps (reference: MONSTER_AI.md Section 5):
      1. Bounds check
      2. Player position → always reachable (triggers attack)
      3. Empty floor → passable if no other monster occupies it
      4. Door breaking (special_ability_1 > 5, probabilistic)
      5. Wall breaking (monster.level > 8, low-probability)
    """
    target_row = monster.row + dr
    target_col = monster.col + dc

    # 1. Bounds
    if not _in_bounds(target_row, target_col):
        return False

    # 2. Player position is always reachable (monster will attack)
    if target_row == player.y and target_col == player.x:
        return True

    # 3. Empty floor (no monster occupying it)
    if _tile_passable_for_monster(level, target_row, target_col):
        if level.get_monster_at(target_col, target_row) is None:
            return True

    # 4. Door breaking via special_ability_1
    #    special_ability_1 must be > 5 for any chance (random_mod(0+1) never == 6)
    special_ability = getattr(monster, 'special_ability_1', 0)
    if special_ability > 5:
        if random.randint(0, special_ability) == 6:
            return True

    # 5. Wall breaking for high-level monsters
    monster_level = getattr(monster, 'level', 0)
    if monster_level > 8:
        if random.randint(0, monster_level) == 9:
            # Clear the wall tile permanently
            level.set_tile(target_col, target_row, ' ')
            return True

    return False


# =============================================================================
# MOVEMENT DIRECTION CALCULATION
# =============================================================================

def calculate_chase_direction(monster: Monster, player: Player,
                              level: DungeonLevel) -> Tuple[int, int]:
    """
    Greedy Manhattan-distance direction toward player.
    Reference: MONSTER_AI.md Section 4

    Prioritises the axis with the larger distance gap.
    If primary direction is blocked, falls back to perpendicular axis.
    Returns (dc, dr) — (delta column, delta row).

    CRITICAL: NO A*, NO Dijkstra — greedy only (gets stuck on walls).
    """
    dr = player.y - monster.row   # positive → player is below
    dc = player.x - monster.col  # positive → player is to the right

    sign_dr = _get_sign(dr)
    sign_dc = _get_sign(dc)

    # Prioritise the axis with the larger absolute distance
    if abs(dc) < abs(dr):
        # Vertical gap is bigger — try moving vertically first
        if _validate_tile_movement(monster, level, 0, sign_dr, player):
            return (0, sign_dr)
        # Blocked vertically — fall back to horizontal
        if _validate_tile_movement(monster, level, sign_dc, 0, player):
            return (sign_dc, 0)
    else:
        # Horizontal gap is bigger (or equal) — try moving horizontally first
        if _validate_tile_movement(monster, level, sign_dc, 0, player):
            return (sign_dc, 0)
        # Blocked horizontally — fall back to vertical
        if _validate_tile_movement(monster, level, 0, sign_dr, player):
            return (0, sign_dr)

    # Completely stuck
    return (0, 0)


def _calculate_flee_direction(monster: Monster, player: Player,
                              level: DungeonLevel) -> Tuple[int, int]:
    """
    Direction away from player — negated chase direction.
    Reference: MONSTER_AI.md Section 8
    """
    dr = player.y - monster.row
    dc = player.x - monster.col

    flee_dr = -_get_sign(dr)
    flee_dc = -_get_sign(dc)

    # Try combined diagonal-free flee
    if _validate_tile_movement(monster, level, flee_dc, flee_dr, player):
        return (flee_dc, flee_dr)
    # Fall back to individual axes
    if flee_dc != 0 and _validate_tile_movement(monster, level, flee_dc, 0, player):
        return (flee_dc, 0)
    if flee_dr != 0 and _validate_tile_movement(monster, level, 0, flee_dr, player):
        return (0, flee_dr)

    return (0, 0)


# =============================================================================
# MOVEMENT EXECUTION
# =============================================================================

def attempt_move(monster: Monster, dc: int, dr: int,
                 level: DungeonLevel, player: Player) -> bool:
    """
    Attempt to move monster by (dc, dr).
    Returns True if movement succeeded, False if blocked.

    NOTE: Does NOT attack if target == player position; that is handled
    by the caller (process_monster_turn) before attempt_move is called.
    """
    if dc == 0 and dr == 0:
        return False

    target_row = monster.row + dr
    target_col = monster.col + dc

    if not _validate_tile_movement(monster, level, dc, dr, player):
        return False

    # Don't step onto player (caller handles combat)
    if target_row == player.y and target_col == player.x:
        return False

    monster.row = target_row
    monster.col = target_col
    return True


# =============================================================================
# HP REGENERATION (boss monsters only)
# =============================================================================

def _handle_hp_regen(monster: Monster):
    """
    Regenerate HP for special boss monsters each turn.
    Reference: MONSTER_AI.md Section 2
    """
    atk = monster.attack_char_code

    if atk == ATTACK_CHAR_GHOST2:
        if monster.current_hp < REGEN_CAP_GHOST2:
            monster.current_hp += 1
        # 1/65 chance to reveal on map (currently a no-op — no map overlay)
        # if random.randint(0, REVEAL_CHANCE_GHOST2 - 1) == 0: reveal(monster)

    elif atk == ATTACK_CHAR_GHOST1:
        if monster.current_hp < REGEN_CAP_GHOST1:
            monster.current_hp += 1

    elif atk == ATTACK_CHAR_SAURON:
        if monster.current_hp < REGEN_CAP_SAURON:
            monster.current_hp += 1

    elif atk == ATTACK_CHAR_SARUMAN:
        if monster.current_hp < REGEN_CAP_SARUMAN:
            monster.current_hp += 1
        # 1/70 chance to reveal on map (no-op for now)


# =============================================================================
# SINGLE MONSTER TURN
# =============================================================================

def process_monster_turn(monster: Monster, level: DungeonLevel,
                         player: Player, screen=None):
    """
    Process one monster's turn (called only when awake/alerted and toggle=1).
    Reference: MONSTER_AI.md Section 3

    Turn order:
      1. Stationary check (bosses never move; attack if adjacent)
      2. Eye of Sauron check (never moves; attack if adjacent)
      3. Huorn check (only attacks/flees when adjacent)
      4. Wake/alert check based on distance
      5. Attack if adjacent
      6. Move (flee, wander, or chase)
      7. Decrement status_timer
    """
    # Local import avoids circular dependency at module load time
    from game.combat import monster_attacks_player

    # --- 1. Stationary monsters (bosses) ---
    if monster.is_stationary:
        if _is_adjacent(monster, player):
            monster_attacks_player(player, monster, screen)
        return

    # --- 2. Eye of Sauron — always awake but never moves ---
    if monster.attack_char_code == ATTACK_CHAR_EYE:
        if _is_adjacent(monster, player):
            monster_attacks_player(player, monster, screen)
        return

    # --- 3. Huorn — only activates when player is adjacent ---
    if monster.attack_char_code == ATTACK_CHAR_HUORN:
        if _is_adjacent(monster, player):
            # Become fleeing-hostile when touched
            monster.is_hostile = False
            monster.is_fleeing = True
            monster_attacks_player(player, monster, screen)
        return

    # --- 4. Wake / alert check ---
    if not monster.is_awake and not monster.is_alerted:
        dist = _manhattan(monster, player)
        if dist < WAKE_DISTANCE:
            monster.is_awake = True
        elif dist < ALERT_DISTANCE:
            monster.is_alerted = True
        else:
            return  # Still sleeping

    # --- 5. Attack if adjacent ---
    if _is_adjacent(monster, player):
        monster_attacks_player(player, monster, screen)
        return

    # --- 6. Calculate and execute movement ---
    if monster.is_fleeing:
        dc, dr = _calculate_flee_direction(monster, player, level)
    elif monster.attack_char_code in (ATTACK_CHAR_BAT, ATTACK_CHAR_AIR):
        # Bat and Air: 50% random wander when not actively alerted
        if not monster.is_alerted and random.randint(0, 1) == 0:
            dr = random.randint(-1, 1)
            dc = random.randint(-1, 1)
        else:
            dc, dr = calculate_chase_direction(monster, player, level)
    else:
        dc, dr = calculate_chase_direction(monster, player, level)

    if dc != 0 or dr != 0:
        target_row = monster.row + dr
        target_col = monster.col + dc

        if target_row == player.y and target_col == player.x:
            # Moving into player — attack instead
            monster_attacks_player(player, monster, screen)
        else:
            attempt_move(monster, dc, dr, level, player)

    # --- 7. Decrement status_timer ---
    #   - When fleeing: counts down flee duration (0 → stop fleeing)
    #   - When stunned: counted down before this function is called
    if (monster.is_alerted or monster.is_awake) and monster.status_timer > 0:
        monster.status_timer -= 1
        if monster.status_timer == 0:
            monster.is_alerted = False
            monster.is_awake = False
            monster.is_fleeing = False


# =============================================================================
# MAIN AI LOOP
# =============================================================================

def update_all_monsters(level: DungeonLevel, player: Player,
                        dungeon_level: int = 1, screen=None):
    """
    Main monster update loop — called once per player turn.
    Reference: MONSTER_AI.md Section 3

    For each living monster:
      1. Apply HP regeneration (boss monsters only)
      2. Toggle move_toggle  (CRITICAL: all monsters move every 2 turns)
      3. If stunned (status_timer > 0 and not fleeing): skip turn
      4. If awake/alerted AND toggle == 1: process turn

    NO variable speed: speed_bonus affects combat to-hit, NOT movement rate.
    """
    # Iterate over a copy so combat deaths don't invalidate iteration
    for monster in list(level.monsters):
        if not monster.is_alive:
            continue

        # 1. HP regeneration for special boss types
        _handle_hp_regen(monster)

        # 2. Toggle move_toggle — the half-speed mechanism
        monster.move_toggle = 1 if monster.move_toggle == 0 else 0

        # 3. Stun check (status_timer used as stun when not fleeing)
        if monster.status_timer > 0 and not monster.is_fleeing:
            monster.status_timer -= 1
            continue  # Can't act while stunned

        # 4. Process turn only when awake/alerted and toggle allows it
        if (monster.is_awake or monster.is_alerted) and monster.move_toggle == 1:
            process_monster_turn(monster, level, player, screen)
