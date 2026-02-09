"""
Game constants extracted from reverse-engineered Moria DOS game.
"""

# Map dimensions
MAP_WIDTH = 79
MAP_HEIGHT = 22
ROOM_COLS = 39
ROOM_ROWS = 10
MAX_DUNGEON_LEVEL = 15  # 15 levels total, Silmaril at level 12

# Corridor generation (Kruskal's algorithm)
TOTAL_CORRIDORS = 808
VERTICAL_CORRIDORS = 391
HORIZONTAL_CORRIDORS = 417

# Player stats
MAX_STAT = 18
MIN_STAT = 3
STARTING_HP = 20
STARTING_FOOD = 1000
FOOD_WARNING_THRESHOLD = 400

# Game timers
TURNS_PER_FOOD_DECREASE = 10
HALLUCINATION_DURATION = 100
PARALYSIS_DURATION = 10
BLINDNESS_DURATION = 20

# Memory addresses (for reference from original game)
ADDR_PLAYER_Y = 0xb86c
ADDR_PLAYER_X = 0xb86e
ADDR_CURRENT_HP = 0xb870
ADDR_MAX_HP = 0xb872
ADDR_CURRENT_FOOD = 0xb874
ADDR_MAX_FOOD = 0xb876
ADDR_DUNGEON_LEVEL = 0xe52d

# CP437 Characters (DOS box-drawing)
CHAR_FLOOR = ' '
CHAR_WALL_VERTICAL = '│'      # 0xb3
CHAR_WALL_HORIZONTAL = '─'    # 0xc4
CHAR_WALL_CROSS = '┼'         # 0xc5
CHAR_WALL_TL = '┌'
CHAR_WALL_TR = '┐'
CHAR_WALL_BL = '└'
CHAR_WALL_BR = '┘'
CHAR_PLAYER = '@'
CHAR_STAIRS_DOWN = '>'
CHAR_STAIRS_UP = '<'
CHAR_GOLD = '$'
CHAR_POTION = '•'            # From manual
CHAR_SCROLL = '?'
CHAR_WEAPON = '='            # From manual (not ')')
CHAR_ARMOR = ''             # From manual (not '[')
CHAR_RING = '°'              # From manual (not '=')
CHAR_FOOD = ':'              # From manual (not '%')
CHAR_WAND = '/'
CHAR_CUBE = '□'
CHAR_SILMARIL = '◊'          # Main objective!

# Colors (curses color pairs)
COLOR_NORMAL = 1
COLOR_PLAYER = 2
COLOR_MONSTER = 3
COLOR_ITEM = 4
COLOR_WARNING = 5
COLOR_STATUS = 6

# Potion effects (from extracted game data)
class PotionEffect:
    HEAL = 1              # de guérison
    GREATER_HEAL = 2      # d'extra-guérison
    STAMINA = 3           # nourrissante
    RESTORE_FOOD = 4      # désaltérante
    SPEED = 5             # accélérante
    CONSTITUTION = 6      # de constitution
    STRENGTH = 7          # de force
    INTELLIGENCE = 8      # d'intelligence
    WISDOM = 9            # de sagesse
    DEXTERITY = 10        # de dextérité
    DETECT = 11           # de détection
    BLINDNESS = 12        # aveuglante
    CONFUSION = 13        # de confusion
    POISON = 14           # empoisonnée
    HALLUCINATION = 15    # hallucinante
    INVULNERABILITY = 16  # d'invulnérabilité
    RESTORE_LEVEL = 17    # de restauration
    HEROISM = 18          # d'héroïsme
    TELEPORT = 19         # de téléportation
    EXPERIENCE = 20       # d'expérience
    WEAKNESS = 21         # de faiblesse

# Equipment slots
class EquipSlot:
    WEAPON = 0
    SHIELD = 1
    ARMOR = 2
    RING1 = 3
    RING2 = 4

# Item types
class ItemType:
    WEAPON = 0
    ARMOR = 1
    SHIELD = 2
    RING = 3
    POTION = 4
    SCROLL = 5
    FOOD = 6
    GOLD = 7
