"""
Level Transition & Persistence for PyMoria
Reference: reverse/PLAYER_ACTIONS.md Section 2-3

Key rules (from advance_to_next_level C function, line 11670):
  - Going DOWN: damage = random(dungeon_level × 2), unless protected.
    Player placed at the '<' (up-stairs) of the new level.
  - Going UP: safe (no damage). Cannot ascend from level 1 (no town).
    Player placed at the '>' (down-stairs) of the level above.
  - Level persistence: visited_flag per level; levels are stored in game.levels
    dict and never regenerated once visited.  NO disk save.
"""

import random
from typing import Optional, Tuple

from game.entities import DungeonLevel, Monster
from game.dungeon import generate_dungeon_level
from utils.constants import (
    MAX_LEVELS, TILE_STAIRS_UP, TILE_STAIRS_DOWN,
    get_stairs_damage, ITEM_UNKNOWN_E,
)
from data.messages import MSG_FALL_DAMAGE, MSG_CANT_GO_UP


# =============================================================================
# HELPERS
# =============================================================================

def _find_floor_position(level: DungeonLevel) -> Optional[Tuple[int, int]]:
    """Return a random empty floor (col, row) or None."""
    for _ in range(200):
        row = random.randint(0, 19)
        col = random.randint(0, 78)
        if level.get_tile(col, row) == ' ':
            return (col, row)
    return None


def _has_feather_fall(player) -> bool:
    """
    Return True if the player carries ITEM_UNKNOWN_E (feather-fall / soft boots).
    Reference: advance_to_next_level C line 61, has_item_in_inventory(ITEM_UNKNOWN_E).
    """
    for item in player.inventory:
        if getattr(item, 'name', '') == ITEM_UNKNOWN_E:
            return True
    return False


def _generate_and_store_level(game, level_num: int) -> DungeonLevel:
    """
    Generate a fresh dungeon level, then re-attach any boss monsters that were
    pre-placed by initialize_boss_monsters() on an empty placeholder level.

    initialize_boss_monsters() may have stored stationary bosses in
    game.levels[level_num] before the level was ever generated.  We transfer
    those to the newly generated level and place them on valid floor tiles.
    """
    # Collect pre-placed stationary bosses from the placeholder entry (if any)
    pre_bosses: list[Monster] = []
    if level_num in game.levels:
        pre_bosses = [m for m in game.levels[level_num].monsters
                      if m.is_stationary]

    # Generate fully connected, item-stocked dungeon level
    new_level = generate_dungeon_level(level_num, game.player)

    # Re-attach bosses at valid floor positions
    for boss in pre_bosses:
        pos = _find_floor_position(new_level)
        if pos:
            boss.col, boss.row = pos
        new_level.monsters.append(boss)

    game.levels[level_num] = new_level
    return new_level


# =============================================================================
# MAIN TRANSITION FUNCTION
# =============================================================================

def advance_to_next_level(direction: int, game, screen) -> None:
    """
    Handle a stair transition.

    Args:
        direction: 0 = going down ('>'), 1 = going up ('<')
        game:   Game instance with .player, .dungeon_level, .levels,
                .current_level attributes.
        screen: Screen instance for messages.

    Reference: advance_to_next_level C function (line 11670).
    """
    player = game.player

    # ------------------------------------------------------------------
    # GOING DOWN
    # ------------------------------------------------------------------
    if direction == 0:
        new_level_num = game.dungeon_level + 1

        if new_level_num > MAX_LEVELS:
            screen.draw_message("Vous ne pouvez pas descendre plus bas")
            return

        game.dungeon_level = new_level_num
        player.dungeon_level = new_level_num

        # HP damage unless the player carries feather-fall protection
        # Reference: PLAYER_ACTIONS.md §2, random(dungeon_level × 2)
        if not _has_feather_fall(player):
            damage = get_stairs_damage(new_level_num)
            if damage > 0:
                player.current_hp -= damage
                screen.draw_message(MSG_FALL_DAMAGE)

                if player.current_hp < 1:
                    player.current_hp = 0
                    player.is_dying = True
                    return

        # Generate level on first visit (visited_flag == False)
        existing = game.levels.get(new_level_num)
        if existing is None or not existing.visited_flag:
            new_level = _generate_and_store_level(game, new_level_num)
        else:
            new_level = existing

        game.current_level = new_level

        # Place player at up-stairs '<' so they can return
        player.x = new_level.stairs_up_col
        player.y = new_level.stairs_up_row

    # ------------------------------------------------------------------
    # GOING UP
    # ------------------------------------------------------------------
    elif direction == 1:
        if game.dungeon_level <= 1:
            screen.draw_message(MSG_CANT_GO_UP)
            return

        new_level_num = game.dungeon_level - 1
        game.dungeon_level = new_level_num
        player.dungeon_level = new_level_num

        # The upper level is always already generated (we came from there)
        upper_level = game.levels[new_level_num]
        game.current_level = upper_level

        # Place player at down-stairs '>' — the stairs they descended from
        player.x = upper_level.stairs_down_col
        player.y = upper_level.stairs_down_row
