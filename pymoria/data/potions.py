"""
Potion database extracted from reverse-engineered game data.
Based on memory dump analysis at offset 0x2a967.
French names preserved from original game.
"""

from dataclasses import dataclass
from utils.constants import PotionEffect, ItemType


@dataclass
class PotionTemplate:
    """Potion template with effect and French name."""
    effect: int
    name_fr: str
    name_en: str
    value: int
    level: int
    char: str = '!'  # Potion character
    type: int = ItemType.POTION  # Item type
    name: str = None  # Alias for name_fr

    def __post_init__(self):
        """Set name as alias for name_fr."""
        if self.name is None:
            self.name = self.name_fr


# Potions extracted from memory (21 confirmed from original game)
POTIONS = [
    PotionTemplate(PotionEffect.HEAL, "potion de guérison", "healing", 50, 1),
    PotionTemplate(PotionEffect.GREATER_HEAL, "potion d'extra-guérison", "greater healing", 100, 3),
    PotionTemplate(PotionEffect.STAMINA, "potion nourrissante", "stamina", 30, 1),
    PotionTemplate(PotionEffect.RESTORE_FOOD, "potion désaltérante", "restore food", 40, 2),
    PotionTemplate(PotionEffect.SPEED, "potion accélérante", "speed", 80, 5),
    PotionTemplate(PotionEffect.CONSTITUTION, "potion de constitution", "constitution", 100, 6),
    PotionTemplate(PotionEffect.STRENGTH, "potion de force", "strength", 100, 6),
    PotionTemplate(PotionEffect.INTELLIGENCE, "potion d'intelligence", "intelligence", 100, 6),
    PotionTemplate(PotionEffect.WISDOM, "potion de sagesse", "wisdom", 100, 6),
    PotionTemplate(PotionEffect.DEXTERITY, "potion de dextérité", "dexterity", 100, 6),
    PotionTemplate(PotionEffect.DETECT, "potion de détection", "detection", 60, 4),
    PotionTemplate(PotionEffect.BLINDNESS, "potion aveuglante", "blindness", 20, 2),
    PotionTemplate(PotionEffect.CONFUSION, "potion de confusion", "confusion", 25, 2),
    PotionTemplate(PotionEffect.POISON, "potion empoisonnée", "poison", 15, 1),
    PotionTemplate(PotionEffect.HALLUCINATION, "potion hallucinante", "hallucination", 30, 3),
    PotionTemplate(PotionEffect.INVULNERABILITY, "potion d'invulnérabilité", "invulnerability", 200, 10),
    PotionTemplate(PotionEffect.RESTORE_LEVEL, "potion de restauration", "restore level", 150, 8),
    PotionTemplate(PotionEffect.HEROISM, "potion d'héroïsme", "heroism", 120, 7),
    PotionTemplate(PotionEffect.TELEPORT, "potion de téléportation", "teleportation", 50, 3),
    PotionTemplate(PotionEffect.EXPERIENCE, "potion d'expérience", "experience", 250, 12),
    PotionTemplate(PotionEffect.WEAKNESS, "potion de faiblesse", "weakness", 10, 1),
]


def get_random_potion(dungeon_level: int) -> PotionTemplate:
    """Get random potion appropriate for dungeon level."""
    import random
    candidates = [p for p in POTIONS if p.level <= dungeon_level + 3]
    return random.choice(candidates) if candidates else POTIONS[0]


def get_potion_by_effect(effect: int) -> PotionTemplate:
    """Get potion by effect type."""
    for potion in POTIONS:
        if potion.effect == effect:
            return potion
    return POTIONS[0]
