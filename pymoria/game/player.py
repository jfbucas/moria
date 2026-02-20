"""
Player character class.
"""

from typing import List, Optional, Dict
from game.stats import Stats, StatusEffects
from data.items import ItemTemplate
from utils.constants import EquipSlot, STARTING_HP, STARTING_FOOD


class Inventory:
    """Player inventory management."""

    def __init__(self, max_size: int = 26):
        self.items: List[Optional[ItemTemplate]] = [None] * max_size
        self.max_size = max_size

    def add_item(self, item: ItemTemplate) -> bool:
        """Add item to inventory. Returns True if successful."""
        for i in range(self.max_size):
            if self.items[i] is None:
                self.items[i] = item
                return True
        return False  # Inventory full

    def remove_item(self, index: int) -> Optional[ItemTemplate]:
        """Remove and return item at index."""
        if 0 <= index < self.max_size:
            item = self.items[index]
            self.items[index] = None
            return item
        return None

    def get_item(self, index: int) -> Optional[ItemTemplate]:
        """Get item at index without removing."""
        if 0 <= index < self.max_size:
            return self.items[index]
        return None

    def is_full(self) -> bool:
        """Check if inventory is full."""
        return all(item is not None for item in self.items)

    def count_items(self) -> int:
        """Count non-empty slots."""
        return sum(1 for item in self.items if item is not None)


class Player:
    """Player character."""

    def __init__(self, name: str = "Aventurier"):
        self.name = name
        self.x: int = 0
        self.y: int = 0
        self.char = '\u263b'  # ☻ (CP437 0x02)

        # Stats
        self.stats = Stats(
            strength=12,
            intelligence=12,
            wisdom=12,
            dexterity=12,
            constitution=12,
            charisma=12
        )

        # Health and resources
        self.max_hp = STARTING_HP
        self.current_hp = self.max_hp
        self.max_food = STARTING_FOOD
        self.current_food = self.max_food

        # Experience and level
        self.level = 1
        self.experience = 0
        self.experience_to_next = 100

        # Gold
        self.gold = 0

        # Combat stats
        self.base_ac = 10
        self.current_ac = self.base_ac

        # Equipment
        self.equipment: Dict[int, Optional[ItemTemplate]] = {
            EquipSlot.WEAPON: None,
            EquipSlot.SHIELD: None,
            EquipSlot.ARMOR: None,
            EquipSlot.RING1: None,
            EquipSlot.RING2: None,
        }

        # Inventory
        self.inventory = Inventory()

        # Status effects
        self.status = StatusEffects()

        # Turn counter
        self.turn_count = 0

    def move(self, dx: int, dy: int):
        """Move player by delta."""
        self.x += dx
        self.y += dy

    def set_position(self, x: int, y: int):
        """Set player position."""
        self.x = x
        self.y = y

    def take_damage(self, amount: int) -> int:
        """Take damage. Returns actual damage taken."""
        if self.status.is_invulnerable:
            return 0

        self.current_hp -= amount
        if self.current_hp < 0:
            self.current_hp = 0

        return amount

    def heal(self, amount: int) -> int:
        """Heal HP. Returns actual amount healed."""
        old_hp = self.current_hp
        self.current_hp = min(self.current_hp + amount, self.max_hp)
        return self.current_hp - old_hp

    def restore_food(self, amount: int):
        """Restore food/satiation."""
        self.current_food = min(self.current_food + amount, self.max_food)

    def consume_food(self, amount: int = 1):
        """Consume food each turn."""
        self.current_food -= amount
        if self.current_food < 0:
            self.current_food = 0

    def is_starving(self) -> bool:
        """Check if player is starving."""
        return self.current_food <= 0

    def is_hungry(self) -> bool:
        """Check if player is getting hungry."""
        return self.current_food < 400  # FOOD_WARNING_THRESHOLD

    def is_alive(self) -> bool:
        """Check if player is alive."""
        return self.current_hp > 0

    def gain_experience(self, amount: int):
        """Gain experience points."""
        self.experience += amount

        # Check for level up
        while self.experience >= self.experience_to_next:
            self.level_up()

    def level_up(self):
        """Level up the player."""
        self.level += 1
        self.experience_to_next = int(self.experience_to_next * 1.5)

        # Increase max HP based on constitution
        hp_gain = max(1, self.stats.constitution // 3)
        self.max_hp += hp_gain
        self.current_hp = self.max_hp

        # Restore food
        self.current_food = self.max_food

    def equip_item(self, slot: int, item: Optional[ItemTemplate]):
        """Equip an item in a slot."""
        old_item = self.equipment[slot]
        self.equipment[slot] = item
        self.recalculate_ac()
        return old_item

    def unequip_item(self, slot: int) -> Optional[ItemTemplate]:
        """Unequip item from slot."""
        item = self.equipment[slot]
        self.equipment[slot] = None
        self.recalculate_ac()
        return item

    def recalculate_ac(self):
        """Recalculate armor class from equipment."""
        self.current_ac = self.base_ac

        # Add AC bonuses from equipment
        for slot, item in self.equipment.items():
            if item and hasattr(item, 'ac_bonus'):
                self.current_ac -= item.ac_bonus  # Lower AC is better

        # Dexterity bonus
        dex_bonus = (self.stats.dexterity - 10) // 2
        self.current_ac -= dex_bonus

    def get_weapon_damage(self) -> str:
        """Get weapon damage dice."""
        weapon = self.equipment[EquipSlot.WEAPON]
        if weapon and hasattr(weapon, 'damage'):
            return weapon.damage
        return "1d3"  # Unarmed

    def get_to_hit_bonus(self) -> int:
        """Get to-hit bonus from weapon and strength."""
        bonus = (self.stats.strength - 10) // 2

        weapon = self.equipment[EquipSlot.WEAPON]
        if weapon and hasattr(weapon, 'tohit_bonus'):
            bonus += weapon.tohit_bonus

        return bonus

    def update(self):
        """Update player each turn."""
        self.turn_count += 1

        # Update status effects
        self.status.update()

        # Consume food every 10 turns
        if self.turn_count % 10 == 0:
            self.consume_food(1)

        # Starvation damage
        if self.is_starving():
            self.take_damage(1)

        # Natural regeneration
        if self.turn_count % 20 == 0 and self.current_hp < self.max_hp:
            if not self.is_starving():
                self.heal(1)

    def can_act(self) -> bool:
        """Check if player can take actions."""
        return self.is_alive() and self.status.can_act()

    def get_status_string(self, dungeon_level: int = 1) -> str:
        """Get status bar string matching original MORIA display_character_stats."""
        ac = self.base_ac
        ac_sign = " +" if ac >= 1 else " "
        return (
            f"Niv {dungeon_level:2d}"
            f" Or{self.gold:6d}"
            f"   PV{self.current_hp:4d}/{self.max_hp:3d}"
            f"   Int{self.stats.intelligence:3d}"
            f"   Dex{self.stats.dexterity:3d}"
            f"   For{self.stats.strength:3d}"
            f"   CA{ac_sign}{ac}"
            f"   Exp {self.level:2d}/{self.experience:4d}"
        )
