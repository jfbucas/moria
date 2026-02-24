"""
Item database extracted from reverse-engineered game data.
Based on memory dump analysis at offset 0x2b000-0x2d800.
"""

import random
from dataclasses import dataclass, field
from typing import Optional, List
from utils.constants import ItemType, WandEffect


@dataclass
class ItemTemplate:
    """Item template with properties."""
    name: str
    type: int
    char: str
    ac_bonus: int = 0
    damage: str = ""
    tohit_bonus: int = 0
    value: int = 0
    weight: int = 1
    level: int = 1


# Weapons (14 from extracted data) - Using '=' per MORIA.TXT manual
WEAPONS = [
    ItemTemplate("dague", ItemType.WEAPON, "=", damage="1d4", tohit_bonus=0, value=2, weight=1, level=1),
    ItemTemplate("lance", ItemType.WEAPON, "=", damage="1d6", tohit_bonus=0, value=5, weight=3, level=1),
    ItemTemplate("masse", ItemType.WEAPON, "=", damage="1d8", tohit_bonus=0, value=8, weight=4, level=2),
    ItemTemplate("sabre", ItemType.WEAPON, "=", damage="1d8", tohit_bonus=0, value=10, weight=3, level=2),
    ItemTemplate("cimeterre", ItemType.WEAPON, "=", damage="1d8", tohit_bonus=1, value=15, weight=3, level=3),
    ItemTemplate("épée", ItemType.WEAPON, "=", damage="1d10", tohit_bonus=0, value=20, weight=4, level=3),
    ItemTemplate("épée à deux mains", ItemType.WEAPON, "=", damage="2d6", tohit_bonus=0, value=35, weight=6, level=5),
    ItemTemplate("épée elfique", ItemType.WEAPON, "=", damage="1d10", tohit_bonus=2, value=100, weight=3, level=8),
    ItemTemplate("épée de glace", ItemType.WEAPON, "=", damage="1d12+cold", tohit_bonus=1, value=200, weight=4, level=10),
    ItemTemplate("épée vampirique", ItemType.WEAPON, "=", damage="1d10+drain", tohit_bonus=2, value=300, weight=4, level=12),
    ItemTemplate("hache", ItemType.WEAPON, "=", damage="1d10", tohit_bonus=0, value=15, weight=5, level=3),
    ItemTemplate("arc", ItemType.WEAPON, "=", damage="1d8", tohit_bonus=0, value=25, weight=2, level=2),
    ItemTemplate("flèches", ItemType.WEAPON, "=", damage="1d6", tohit_bonus=0, value=1, weight=0, level=1),
    ItemTemplate("dague elfique", ItemType.WEAPON, "=", damage="1d5", tohit_bonus=2, value=50, weight=1, level=6),
]

# Armor (11 from extracted data)
ARMOR = [
    ItemTemplate("armure de cuir", ItemType.ARMOR, "", ac_bonus=2, value=10, weight=8, level=1),
    ItemTemplate("armure de cuir renforcé", ItemType.ARMOR, "", ac_bonus=3, value=20, weight=10, level=2),
    ItemTemplate("cotte de mailles", ItemType.ARMOR, "", ac_bonus=4, value=40, weight=15, level=3),
    ItemTemplate("armure de fer", ItemType.ARMOR, "", ac_bonus=5, value=80, weight=20, level=5),
    ItemTemplate("cuirasse d'acier", ItemType.ARMOR, "", ac_bonus=6, value=150, weight=22, level=7),
    ItemTemplate("armure de mithril", ItemType.ARMOR, "", ac_bonus=8, value=500, weight=10, level=12),
    ItemTemplate("heaume", ItemType.ARMOR, "", ac_bonus=1, value=15, weight=3, level=2),
    ItemTemplate("cape elfique", ItemType.ARMOR, "", ac_bonus=1, value=100, weight=1, level=8),
    ItemTemplate("gants de force", ItemType.ARMOR, "", ac_bonus=0, value=80, weight=1, level=6),
    ItemTemplate("gants de dextérité", ItemType.ARMOR, "", ac_bonus=0, value=80, weight=1, level=6),
    ItemTemplate("gants de maladresse", ItemType.ARMOR, "", ac_bonus=0, value=5, weight=1, level=1),
]

# Rings (various magical effects)
RINGS = [
    ItemTemplate("anneau de force", ItemType.RING, "=", value=100, level=5),
    ItemTemplate("anneau de protection", ItemType.RING, "=", ac_bonus=2, value=150, level=6),
    ItemTemplate("anneau de vitesse", ItemType.RING, "=", value=200, level=8),
    ItemTemplate("anneau de régénération", ItemType.RING, "=", value=250, level=10),
    ItemTemplate("anneau de téléportation", ItemType.RING, "=", value=50, level=3),
]

# Food items
FOOD_ITEMS = [
    ItemTemplate("ration de nourriture", ItemType.FOOD, ":", value=3, weight=1, level=1),
    ItemTemplate("morceau de pain", ItemType.FOOD, ":", value=1, weight=0, level=1),
]

# Wand wood names from original game memory dump
WAND_WOODS = [
    "d'acajou", "d'if", "d'olivier", "d'orme", "d'érable",
    "de bambou", "de cerisier", "de châtaignier", "de chêne", "de frêne",
    "de merisier", "de noisetier", "de peuplier", "de pin", "de platane",
    "de rose noire", "de roseau", "de saule", "de teck", "de verre",
]

# Wand effects from original game memory dump at 0x2b18f-0x2b407
# (effect_id, french_name, english_desc, value, level)
_WAND_EFFECTS = [
    (WandEffect.TELEPORT, "de téléportation", "teleport", 60, 3),
    (WandEffect.TRANSMORPH, "de transmorphie", "transmorph", 120, 8),
    (WandEffect.DESTRUCTION, "de destruction", "destruction", 100, 6),
    (WandEffect.CREATE_WALL, "pour créer des murs", "create_wall", 40, 3),
    (WandEffect.SLOW_MONSTER, "de ralentissement de monstre", "slow_monster", 50, 4),
    (WandEffect.HASTE_MONSTER, "d'accélération de monstre", "haste_monster", 10, 1),
    (WandEffect.WEAKEN, "d'affaiblissement", "weaken", 60, 5),
    (WandEffect.FEAR, "pour effrayer", "fear", 50, 4),
    (WandEffect.DOWSING, "de sourcier", "dowsing", 40, 2),
    (WandEffect.SUMMON_MONSTER, "d'invocation de monstre", "summon_monster", 10, 1),
    (WandEffect.CREATE_ITEM, "d'invocation d'objet", "create_item", 80, 5),
    (WandEffect.COMBAT, "de combat", "combat", 90, 6),
    (WandEffect.FILL_TRAPS, "pour combler les trappes", "fill_traps", 40, 3),
    (WandEffect.SLEEP, "assoupissante", "sleep", 50, 4),
    (WandEffect.PARALYZE, "paralysante", "paralyze", 70, 5),
    (WandEffect.INVISIBILITY, "d'invisibilité", "invisibility", 150, 8),
    (WandEffect.CREATE_TRAPS, "de création de trappes", "create_traps", 10, 1),
    (WandEffect.REINFORCE, "de renforcement", "reinforce", 80, 6),
    (WandEffect.CAPRICIOUS, "capricieuse", "capricious", 30, 2),
    (WandEffect.ILLUSION, "d'illusion", "illusion", 60, 5),
    (WandEffect.PURIFY, "de purification", "purify", 70, 7),
    (WandEffect.ENERGY_DRAIN, "d'absorption d'énergie", "energy_drain", 100, 9),
]

# Wands list (populated by initialize_wand_names)
WANDS: List[ItemTemplate] = []


def initialize_wand_names():
    """Assign random wood names to wand types for a new game."""
    WANDS.clear()
    woods = WAND_WOODS[:]
    random.shuffle(woods)
    for i, (effect_id, effect_fr, effect_en, value, level) in enumerate(_WAND_EFFECTS):
        wood = woods[i % len(woods)]
        WANDS.append(ItemTemplate(
            name=f"baguette {wood}",
            type=ItemType.WAND,
            char="/",
            damage=effect_en,
            value=value,
            weight=1,
            level=level,
        ))


def get_random_weapon(dungeon_level: int) -> ItemTemplate:
    """Get random weapon appropriate for dungeon level."""
    candidates = [w for w in WEAPONS if w.level <= dungeon_level + 3]
    return random.choice(candidates) if candidates else WEAPONS[0]


def get_random_armor(dungeon_level: int) -> ItemTemplate:
    """Get random armor appropriate for dungeon level."""
    candidates = [a for a in ARMOR if a.level <= dungeon_level + 3]
    return random.choice(candidates) if candidates else ARMOR[0]


def get_random_wand(dungeon_level: int) -> ItemTemplate:
    """Get random wand appropriate for dungeon level."""
    if not WANDS:
        initialize_wand_names()
    candidates = [w for w in WANDS if w.level <= dungeon_level + 3]
    return random.choice(candidates) if candidates else WANDS[0]


def get_random_item(dungeon_level: int) -> ItemTemplate:
    """Get random item appropriate for dungeon level."""
    if not WANDS:
        initialize_wand_names()
    all_items = WEAPONS + ARMOR + RINGS + FOOD_ITEMS + WANDS
    candidates = [i for i in all_items if i.level <= dungeon_level + 3]
    return random.choice(candidates) if candidates else all_items[0]
