"""
Core data structures for PyMoria
Based on reverse/MORIA_COMPLETE.md Section 2
"""

from typing import List, Optional
from dataclasses import dataclass, field


@dataclass
class Player:
    """
    Player character data structure
    Reference: MORIA_COMPLETE.md Section 2.1
    """
    # Identity
    name: str = ""  # 15 chars max (Pascal string in original)

    # Core Stats (0-255 range, default 100)
    strength: int = 100        # Force
    dexterity: int = 100       # Dextérité
    intelligence: int = 100    # Intelligence

    # Hit Points
    current_hp: int = 0
    max_hp: int = 0

    # Experience & Level
    player_level: int = 1
    experience: int = 0  # Combined 32-bit value (not split in Python)

    # Gold (32-bit total - we'll use single int in Python)
    gold_low: int = 0
    gold_high: int = 0

    # Position (1-indexed in original, 0-indexed in Python)
    x: int = 0
    y: int = 0

    # Food & Survival
    food_level: int = 5000  # Starts at "Normal" (3001-5000)
    current_food: int = 0

    # Time & Turns
    turn_count: int = 0
    regen_counter: int = 0

    # Equipment Slots
    wielded_weapon: Optional['Item'] = None
    worn_armor: Optional['Item'] = None
    inventory: List['Item'] = field(default_factory=list)

    # Flags & States
    is_wizard: bool = False
    has_light: bool = False
    is_dying: bool = False
    death_timer: int = 0

    # Character Display
    player_char: str = '☻'  # 0x02 in CP437

    # Combat Stats
    base_ac: int = 0  # Armor Class

    # Timed Effects (13 effects, indices 0-12)
    # 0: Blindness, 1: Confusion, 2: Fear, 3: Paralysis, 4: Poison,
    # 5: Speed Boost, 6: Slow, 7: Protection, 8: Detect Monsters,
    # 9: Detect Objects, 10: Invisibility, 11: Infravision, 12: Wizard Mode
    effect_active: List[bool] = field(default_factory=lambda: [False] * 13)
    effect_timer: List[int] = field(default_factory=lambda: [0] * 13)

    def get_total_gold(self) -> int:
        """Calculate total gold as 32-bit value"""
        return (self.gold_high << 16) | self.gold_low

    def set_total_gold(self, value: int):
        """Set gold from 32-bit value"""
        self.gold_low = value & 0xFFFF
        self.gold_high = (value >> 16) & 0xFFFF

    def add_gold(self, amount: int):
        """Add gold with proper 32-bit carry handling"""
        total = self.get_total_gold() + amount
        self.set_total_gold(total)

    @staticmethod
    def get_xp_for_level(level: int) -> int:
        """
        Calculate XP required for level
        Formula: XP[n] = 50 × (2^(n-1) - 1)
        Reference: COMBAT_SYSTEM.md
        """
        if level <= 1:
            return 0
        return 50 * ((2 ** (level - 1)) - 1)

    def get_current_level(self) -> int:
        """Determine current level based on XP"""
        level = 1
        while self.experience >= self.get_xp_for_level(level + 1):
            level += 1
        return level

    def get_food_status(self) -> str:
        """
        Get hunger state message
        Reference: PLAYER_ACTIONS.md
        """
        if self.food_level > 5000:
            return "Rassasié"  # Full
        elif self.food_level > 3000:
            return "Normal"
        elif self.food_level > 1500:
            return "Faible"  # Weak
        elif self.food_level > 0:
            return "Affamé"  # Hungry
        else:
            return "Mourant"  # Dying


@dataclass
class Monster:
    """
    Monster instance data structure
    Reference: MORIA_COMPLETE.md Section 2.2
    54 bytes in original DOS structure
    """
    # Type & Template
    char: str = 'M'  # Display character (C, L, E, etc.)
    template_id: int = 0  # Index into monster template table

    # Position (1-indexed in original, 0-indexed in Python)
    row: int = 0
    col: int = 0

    # Stats (from template, can be modified)
    max_hp: int = 0
    current_hp: int = 0
    armor_class: int = 0   # Armor class (AC)
    to_hit: int = 0        # To-hit bonus
    num_attacks: int = 1   # Number of attacks per turn
    damage_per_attack: int = 0  # Max damage per attack (1 + random(0..N-1))
    experience: int = 0    # XP awarded on death
    speed_bonus: int = 0   # Speed bonus added to to-hit roll

    # French name for display
    name_french: str = "monstre"

    # Combat character code (integer value of attack_char)
    # Controls special attack behavior — see COMBAT_SYSTEM.md Section 1
    attack_char_code: int = 0

    # AI State
    is_awake: bool = False   # 0 = sleeping, 1 = awake
    is_alerted: bool = False # Heard player nearby
    is_hostile: bool = False # Will attack on sight
    is_fleeing: bool = False # Running away from player
    is_invisible: bool = False
    is_alive: bool = True
    is_stationary: bool = False  # Boss monsters never move
    move_toggle: int = 0   # CRITICAL: 0/1 toggle (monsters move every 2 turns)
    ai_state: int = 0      # 0 = wander, 1 = chase
    status_timer: int = 0  # General purpose timer (stun, etc.)

    # Carried item (monsters can carry one item)
    carried_item: Optional['Item'] = None

    # Flags
    is_unique: bool = False     # Unique monster (only one per game)

    # Display
    display_char: str = 'M'    # Current display char (may differ from base)
    base_char: str = 'M'       # Original character

    def __post_init__(self):
        """Ensure display_char and base_char match initial char"""
        if self.display_char == 'M':
            self.display_char = self.char
        if self.base_char == 'M':
            self.base_char = self.char


@dataclass
class Item:
    """
    Item object data structure
    Reference: MORIA_COMPLETE.md Section 2.3
    26 bytes in original DOS structure
    """
    # Type & Identity
    type: int = 0  # Item type (0-8: food, potion, scroll, wand, etc.)
    subtype: int = 0  # Subtype within type
    count: int = 1  # Stack count

    # Position (if on floor, 0-indexed in Python)
    row: int = 0
    col: int = 0

    # Properties
    power: int = 0  # Weapon power, armor AC, wand charges, etc.
    value_low: int = 0  # Gold value (low word)
    value_high: int = 0  # Gold value (high word)

    # Flags
    is_cursed: bool = False  # Cursed item (can't drop)
    is_equipped: bool = False  # Currently equipped
    is_identified: bool = False  # Item type/powers known
    plural_flag: bool = False  # Show 's' in display

    # Display
    display_char: str = '*'  # Character shown on map

    def get_total_value(self) -> int:
        """Calculate total gold value as 32-bit"""
        return (self.value_high << 16) | self.value_low

    def set_total_value(self, value: int):
        """Set gold value from 32-bit value"""
        self.value_low = value & 0xFFFF
        self.value_high = (value >> 16) & 0xFFFF


# Item type constants (from ENTITY_DATABASE.md)
ITEM_FOOD = 0
ITEM_POTION = 1
ITEM_SCROLL = 2
ITEM_WAND = 3
ITEM_RING = 4
ITEM_CHEST = 5
ITEM_WEAPON = 6
ITEM_AMMUNITION = 7
ITEM_TREASURE = 8  # Converts to gold on death


@dataclass
class DungeonLevel:
    """
    Dungeon level data structure
    Reference: MORIA_COMPLETE.md Section 2.4
    """
    # Tile Data (20 rows × 79 cols in original)
    # Using list of strings for each row (easier to work with in Python)
    tiles: List[List[str]] = field(default_factory=lambda:
        [[' ' for _ in range(79)] for _ in range(20)])

    # Level state
    visited_flag: bool = False  # Has this level been generated?
    level_number: int = 0  # Dungeon level (0 = town, 1-19 = depths)

    # Object Lists
    floor_items: List[Item] = field(default_factory=list)
    monsters: List[Monster] = field(default_factory=list)

    # Stairs positions (stored for up-stairs placement)
    stairs_up_row: int = 0
    stairs_up_col: int = 0
    stairs_down_row: int = 0
    stairs_down_col: int = 0

    def get_tile(self, x: int, y: int) -> str:
        """Get tile character at position (with bounds check)"""
        if 0 <= y < 20 and 0 <= x < 79:
            return self.tiles[y][x]
        return '#'  # Wall if out of bounds

    def set_tile(self, x: int, y: int, char: str):
        """Set tile character at position (with bounds check)"""
        if 0 <= y < 20 and 0 <= x < 79:
            self.tiles[y][x] = char

    def is_passable(self, x: int, y: int) -> bool:
        """Check if tile is passable for movement"""
        tile = self.get_tile(x, y)
        # Walls and closed doors are not passable
        wall_chars = {'#', '┴', '┬', '┤', '├', '─', '│', '+'}
        return tile not in wall_chars

    def get_monster_at(self, x: int, y: int) -> Optional[Monster]:
        """Find monster at position"""
        for monster in self.monsters:
            if monster.col == x and monster.row == y:
                return monster
        return None

    def get_item_at(self, x: int, y: int) -> Optional[Item]:
        """Find item at position"""
        for item in self.floor_items:
            if item.col == x and item.row == y:
                return item
        return None


# Timed effect indices (for reference)
EFFECT_BLINDNESS = 0
EFFECT_CONFUSION = 1
EFFECT_FEAR = 2
EFFECT_PARALYSIS = 3
EFFECT_POISON = 4
EFFECT_SPEED_BOOST = 5
EFFECT_SLOW = 6
EFFECT_PROTECTION = 7
EFFECT_DETECT_MONSTERS = 8
EFFECT_DETECT_OBJECTS = 9
EFFECT_INVISIBILITY = 10
EFFECT_INFRAVISION = 11
EFFECT_WIZARD_MODE = 12
