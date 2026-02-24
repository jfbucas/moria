"""
Game Constants for PyMoria
Based on reverse/MORIA_COMPLETE.md Section 4
"""

# =============================================================================
# MAP CONSTANTS
# =============================================================================

MAP_WIDTH = 79
MAP_HEIGHT = 20
MAX_LEVELS = 20

# =============================================================================
# TILE CHARACTERS (CP437/CP850 → Unicode)
# Reference: MORIA_COMPLETE.md Section 2.4
# =============================================================================

# Basic tiles
TILE_FLOOR = ' '
TILE_WALL = '#'
TILE_DOOR_CLOSED = '+'
TILE_DOOR_OPEN = '-'
TILE_STAIRS_UP = '<'
TILE_STAIRS_DOWN = '>'

# Room wall characters (CP437 box-drawing)
TILE_ROOM_TOP = '┴'      # 0xC1 - top wall
TILE_ROOM_BOTTOM = '┬'   # 0xC2 - bottom wall
TILE_ROOM_LEFT = '┤'     # 0xB4 - left wall
TILE_ROOM_RIGHT = '├'    # 0xC3 - right wall

# Corridor characters
TILE_CORRIDOR_HORIZONTAL = '─'  # 0xC4
TILE_CORRIDOR_VERTICAL = '│'    # 0xB3

# Player characters
TILE_PLAYER = '☻'           # 0x02 - normal player
TILE_PLAYER_WIZARD = '~'    # 0x7E - wizard mode
TILE_PLAYER_LIT = '▯'       # 0xEF - illuminated player

# Trap
TILE_TRAP = 'τ'  # 0xF7 in original

# Set of all wall/impassable tiles
WALL_TILES = {
    TILE_WALL,
    TILE_ROOM_TOP,
    TILE_ROOM_BOTTOM,
    TILE_ROOM_LEFT,
    TILE_ROOM_RIGHT,
    TILE_CORRIDOR_HORIZONTAL,
    TILE_CORRIDOR_VERTICAL,
    TILE_DOOR_CLOSED
}

# =============================================================================
# FOOD & HUNGER CONSTANTS
# Reference: MORIA_COMPLETE.md Section 4.4
# =============================================================================

FOOD_FULL = 5001        # Rassasié (Full)
FOOD_NORMAL = 3001      # Normal
FOOD_WEAK = 1501        # Faible (Weak)
FOOD_HUNGRY = 1         # Affamé (Hungry)
FOOD_DYING = 0          # Mourant (Dying)

# Food consumption
FOOD_CONSUMPTION_PER_TURN = 1

# Starvation damage (when food <= 0)
STARVATION_DAMAGE_MIN = 1
STARVATION_DAMAGE_MAX = 10

# =============================================================================
# TIMED EFFECT INDICES
# Reference: MORIA_COMPLETE.md Section 4.6
# =============================================================================

EFFECT_BLINDNESS = 0
EFFECT_CONFUSION = 1
EFFECT_FEAR = 2
EFFECT_PARALYSIS = 3
EFFECT_POISON = 4        # 1-5 damage per turn
EFFECT_SPEED_BOOST = 5
EFFECT_SLOW = 6
EFFECT_PROTECTION = 7    # +20 AC
EFFECT_DETECT_MONSTERS = 8
EFFECT_DETECT_OBJECTS = 9
EFFECT_INVISIBILITY = 10
EFFECT_INFRAVISION = 11
EFFECT_WIZARD_MODE = 12

NUM_TIMED_EFFECTS = 13

# Effect names for display
EFFECT_NAMES = {
    EFFECT_BLINDNESS: "Blindness",
    EFFECT_CONFUSION: "Confusion",
    EFFECT_FEAR: "Fear",
    EFFECT_PARALYSIS: "Paralysis",
    EFFECT_POISON: "Poison",
    EFFECT_SPEED_BOOST: "Speed Boost",
    EFFECT_SLOW: "Slow",
    EFFECT_PROTECTION: "Protection",
    EFFECT_DETECT_MONSTERS: "Detect Monsters",
    EFFECT_DETECT_OBJECTS: "Detect Objects",
    EFFECT_INVISIBILITY: "Invisibility",
    EFFECT_INFRAVISION: "Infravision",
    EFFECT_WIZARD_MODE: "Wizard Mode"
}

# =============================================================================
# ITEM TYPE CONSTANTS
# Reference: MORIA_COMPLETE.md Section 2.3
# =============================================================================

ITEM_FOOD = 0
ITEM_POTION = 1
ITEM_SCROLL = 2
ITEM_WAND = 3
ITEM_RING = 4
ITEM_CHEST = 5
ITEM_WEAPON = 6
ITEM_AMMUNITION = 7
ITEM_TREASURE = 8  # Converts to gold on death

NUM_ITEM_TYPES = 9

# Item type names
ITEM_TYPE_NAMES = {
    ITEM_FOOD: "Food",
    ITEM_POTION: "Potion",
    ITEM_SCROLL: "Scroll",
    ITEM_WAND: "Wand",
    ITEM_RING: "Ring",
    ITEM_CHEST: "Chest",
    ITEM_WEAPON: "Weapon",
    ITEM_AMMUNITION: "Ammunition",
    ITEM_TREASURE: "Treasure"
}

# =============================================================================
# COMBAT CONSTANTS
# Reference: MORIA_COMPLETE.md Section 6.3
# =============================================================================

CRITICAL_HIT = 20  # Natural 20 on d20
DICE_SIDES = 20    # d20 for to-hit rolls

# Protection effect AC bonus
PROTECTION_AC_BONUS = 20

# Poison damage per turn
POISON_DAMAGE_MIN = 1
POISON_DAMAGE_MAX = 5

# =============================================================================
# REGENERATION CONSTANTS
# Reference: MORIA_COMPLETE.md Section 4.5
# =============================================================================

REGEN_BASE_DELAY = 15  # Base turns for regeneration
MIN_REGEN_DELAY = 1    # Minimum delay (at deep levels)

def get_regen_delay(dungeon_level: int) -> int:
    """
    Calculate HP regeneration delay based on dungeon level
    Formula: (15 - dungeon_level) // 2, minimum 1

    Level 1:  7 turns per +1 HP
    Level 10: 2 turns per +1 HP
    Level 13+: 1 turn per +1 HP
    """
    delay = (REGEN_BASE_DELAY - dungeon_level) // 2
    return max(MIN_REGEN_DELAY, delay)

# =============================================================================
# MONSTER SPAWNING CONSTANTS
# Reference: MORIA_COMPLETE.md Section 4.7
# =============================================================================

MONSTER_SPAWN_INTERVAL = 20  # Spawn monsters every 20 turns
CURSED_SPAWN_MULTIPLIER = 4   # 4× spawn rate if cursed item equipped

# =============================================================================
# LEVEL TRANSITION CONSTANTS
# Reference: PLAYER_ACTIONS.md Section 2
# =============================================================================

# Going down stairs damage
def get_stairs_damage(dungeon_level: int) -> int:
    """
    Calculate damage from going down stairs
    Formula: random(dungeon_level × 2)
    """
    import random
    return random.randint(1, dungeon_level * 2) if dungeon_level > 0 else 0

# =============================================================================
# SHOP CONSTANTS
# Reference: SHOP_AND_UI.md Section 1
# =============================================================================

NUM_SHOPS = 2  # Two shops (indices 0-1)

# Shop data offsets (for reference, not used in Python)
SHOP_ITEM_NAME_OFFSET = 0x75FA
SHOP_PRICE_OFFSET = -0x71D3
SHOP_COUNT_OFFSET = 0x79B3

# =============================================================================
# HIGH SCORE CONSTANTS
# Reference: SHOP_AND_UI.md Section 3
# =============================================================================

HIGH_SCORE_FILE = "moria4.scr"
MAX_HIGH_SCORES = 16
HIGH_SCORE_ENTRY_SIZE = 24
HIGH_SCORE_FILE_SIZE = 384  # 16 × 24 bytes

# Death cause codes
DEATH_CAUSE_STARVATION = 'e'
DEATH_CAUSE_TIME_PARADOX = 'f'
DEATH_CAUSE_VICTORY = 'g'  # Escaped from Moria
DEATH_CAUSE_QUIT = 'Q'     # Quit without saving (not recorded)

# =============================================================================
# PLAYER STATS CONSTANTS
# =============================================================================

STAT_MIN = 0
STAT_MAX = 255
STAT_DEFAULT = 100
NUM_STATS = 3  # Force, Dextérité, Intelligence

# =============================================================================
# INVENTORY CONSTANTS
# =============================================================================

MAX_INVENTORY_SLOTS = 35

# =============================================================================
# COMMAND KEYS
# Reference: SHOP_AND_UI.md
# =============================================================================

# Movement (4 directions only - NO DIAGONALS)
CMD_MOVE_UP = '8'
CMD_MOVE_DOWN = '2'
CMD_MOVE_LEFT = '4'
CMD_MOVE_RIGHT = '6'

# Actions
CMD_INVENTORY = 'i'
CMD_EQUIPMENT = 'e'
CMD_DROP = 'd'
CMD_PICKUP = ','
CMD_SEARCH = 's'
CMD_REST = 'r'
CMD_CAST_SPELL = 'm'
CMD_QUIT = 'q'
CMD_HELP = '?'

# =============================================================================
# GAME DATA FILES
# Reference: MORIA_COMPLETE.md Section 1.3
# =============================================================================

GAME_DATA_FILE = "moria.txt"      # Loaded at startup
HELP_FILE = "MORIA.HLP"           # Help text (may not exist)
UNKNOWN_DATA_FILE = "moria4.don"  # Unknown purpose

# =============================================================================
# DUNGEON GENERATION CONSTANTS
# Reference: MORIA_COMPLETE.md Section 6.4
# =============================================================================

ROOM_GRID_WIDTH = 39
ROOM_GRID_HEIGHT = 10
ROOM_GENERATION_CHANCE = 0.5  # 50% chance per grid cell
EXTRA_ROOMS = 1  # One extra room beyond grid

# =============================================================================
# MONSTER AI CONSTANTS
# Reference: MONSTER_AI.md
# =============================================================================

WAKE_DISTANCE = 5      # Distance at which monsters wake up
ALERT_DISTANCE = 10    # Distance at which monsters become alerted

# AI states
AI_STATE_WANDER = 0
AI_STATE_CHASE = 1

# =============================================================================
# XP FORMULA
# Reference: COMBAT_SYSTEM.md
# =============================================================================

def get_xp_for_level(level: int) -> int:
    """
    Calculate XP required for level
    Formula: XP[n] = 50 × (2^(n-1) - 1)
    """
    if level <= 1:
        return 0
    return 50 * ((2 ** (level - 1)) - 1)

# =============================================================================
# LEVEL-UP HP GAIN
# Reference: COMBAT_SYSTEM.md
# =============================================================================

def calculate_level_up_hp_gain(player_level: int, dungeon_level: int) -> int:
    """
    Calculate HP gain on level-up
    Formula: random(6) + random(player_level) + 3 + random(dungeon_level) // 2
    """
    import random
    return (random.randint(1, 6) +
            random.randint(1, player_level) +
            3 +
            random.randint(0, dungeon_level) // 2)

# =============================================================================
# SPECIAL ITEM CONSTANTS
# =============================================================================

# Item that prevents stairs damage (likely "Feather Fall" or "Soft Boots")
ITEM_UNKNOWN_E = "ITEM_UNKNOWN_E"  # Type/subtype unknown

# Arrow subtype (for ammunition type 7)
ARROW_SUBTYPE = 10
