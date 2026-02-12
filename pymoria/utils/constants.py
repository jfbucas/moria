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
CHAR_PLAYER = '\u263b'  # ☻ (CP437 0x02)
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

# Wand effects (from memory dump at 0x2b18f, matched to C code handlers)
# FUN_1000_aa1d: monster-targeting (1,2,5,6,7,8,12,14,15,16,18,19,20,24)
# FUN_1000_b032: environment (3,4,9,10,11,13,17,21)
class WandEffect:
    TELEPORT = 1          # de téléportation
    TRANSMORPH = 2        # de transmorphie
    DESTRUCTION = 3       # de destruction
    CREATE_WALL = 4       # pour créer des murs
    SLOW_MONSTER = 5      # de ralentissement de monstre
    HASTE_MONSTER = 6     # d'accélération de monstre
    WEAKEN = 7            # d'affaiblissement
    FEAR = 8              # pour effrayer
    DOWSING = 9           # de sourcier
    SUMMON_MONSTER = 10   # d'invocation de monstre
    CREATE_ITEM = 11      # d'invocation d'objet
    COMBAT = 12           # de combat
    FILL_TRAPS = 13       # pour combler les trappes
    SLEEP = 14            # assoupissante
    PARALYZE = 15         # paralysante
    INVISIBILITY = 16     # d'invisibilité
    CREATE_TRAPS = 17     # de création de trappes
    REINFORCE = 18        # de renforcement
    CAPRICIOUS = 19       # capricieuse
    ILLUSION = 20         # d'illusion
    PURIFY = 21           # de purification
    ENERGY_DRAIN = 22     # d'absorption d'énergie

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
    WAND = 8
