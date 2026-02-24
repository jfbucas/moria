"""
Test script to validate constants and messages
"""

from utils.constants import *
from data.messages import *


def test_constants():
    """Test all constant definitions"""
    print("PyMoria - Constants & Configuration Test")
    print("=" * 60)
    print()

    # Map constants
    print("Map Constants:")
    print(f"  Dimensions: {MAP_WIDTH}×{MAP_HEIGHT}")
    print(f"  Max levels: {MAX_LEVELS}")
    print()

    # Tile characters
    print("Tile Characters:")
    print(f"  Floor: '{TILE_FLOOR}'")
    print(f"  Wall: '{TILE_WALL}'")
    print(f"  Stairs down: '{TILE_STAIRS_DOWN}'")
    print(f"  Stairs up: '{TILE_STAIRS_UP}'")
    print(f"  Player: '{TILE_PLAYER}'")
    print(f"  Room walls: '{TILE_ROOM_TOP}' '{TILE_ROOM_BOTTOM}' '{TILE_ROOM_LEFT}' '{TILE_ROOM_RIGHT}'")
    print(f"  Corridors: '{TILE_CORRIDOR_HORIZONTAL}' '{TILE_CORRIDOR_VERTICAL}'")
    print()

    # Food states
    print("Food Thresholds:")
    print(f"  Full (Rassasié): {FOOD_FULL}+")
    print(f"  Normal: {FOOD_NORMAL}-{FOOD_FULL-1}")
    print(f"  Weak (Faible): {FOOD_WEAK}-{FOOD_NORMAL-1}")
    print(f"  Hungry (Affamé): {FOOD_HUNGRY}-{FOOD_WEAK-1}")
    print(f"  Dying (Mourant): ≤{FOOD_DYING}")
    print()

    # Timed effects
    print("Timed Effects:")
    for i in range(NUM_TIMED_EFFECTS):
        print(f"  {i}: {EFFECT_NAMES[i]}")
    print()

    # Item types
    print("Item Types:")
    for i in range(NUM_ITEM_TYPES):
        print(f"  {i}: {ITEM_TYPE_NAMES[i]}")
    print()

    # Combat constants
    print("Combat:")
    print(f"  Critical hit: {CRITICAL_HIT} (natural 20)")
    print(f"  Dice sides: {DICE_SIDES}")
    print(f"  Protection AC bonus: {PROTECTION_AC_BONUS}")
    print()

    # Regeneration
    print("HP Regeneration Delays:")
    for level in [1, 5, 10, 13, 15]:
        delay = get_regen_delay(level)
        print(f"  Level {level}: +1 HP per {delay} turn(s)")
    print()

    # XP formula
    print("XP Thresholds:")
    for level in range(1, 11):
        xp = get_xp_for_level(level)
        print(f"  Level {level}: {xp:,} XP")
    print()

    # Messages
    print("Sample Messages (French):")
    print(f"  Death: {MSG_DEATH}")
    print(f"  Victory: {MSG_VICTORY}")
    print(f"  Empty inventory: {MSG_EMPTY_INVENTORY}")
    print(f"  Cursed item: {MSG_CURSED}")
    print()

    # Food status messages
    print("Food Status Messages:")
    for status, msg in FOOD_STATUS.items():
        print(f"  {status}: {msg}")
    print()

    # Death messages
    print("Death Messages:")
    for code, msg in DEATH_MESSAGES.items():
        print(f"  '{code}': {msg}")
    print()

    # Effect expiration
    print("Effect Expiration Messages (sample):")
    for i in [0, 3, 4, 7]:
        print(f"  {EFFECT_NAMES[i]}: {EFFECT_EXPIRE_MESSAGES[i]}")
    print()

    # Wall tiles set
    print(f"Wall Tiles Set: {len(WALL_TILES)} impassable tile types")
    print()

    # Command keys
    print("Command Keys:")
    print(f"  Movement: {CMD_MOVE_UP}/{CMD_MOVE_DOWN}/{CMD_MOVE_LEFT}/{CMD_MOVE_RIGHT}")
    print(f"  Inventory: {CMD_INVENTORY}")
    print(f"  Drop: {CMD_DROP}")
    print(f"  Quit: {CMD_QUIT}")
    print()

    print("✓ All constants loaded successfully!")
    print("✓ All messages loaded successfully!")
    print()
    print("Ready for Prompt 3 (Monster & Item Templates)")


if __name__ == "__main__":
    test_constants()
