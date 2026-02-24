"""
Monster database from MORIA.TXT manual.
All monsters, stats, and XP values taken directly from the manual.
"""

from dataclasses import dataclass
from typing import List


@dataclass
class MonsterTemplate:
    """Monster template with stats and attributes."""
    name: str
    char: str
    level: int
    hp: int
    ac: int
    damage: str
    speed: int
    experience: int
    flags: int = 0


# Monster database from MORIA.TXT manual
MONSTERS: List[MonsterTemplate] = [
    # Level 1-2: Weak monsters
    MonsterTemplate("chauve-souris", "C", 1, 3, 9, "1d2", 12, 1),
    MonsterTemplate("araignée", "a", 1, 3, 9, "1d2", 11, 1),
    MonsterTemplate("rat", "r", 1, 5, 8, "1d3", 10, 4),
    MonsterTemplate("serpent", "s", 2, 8, 8, "1d4", 10, 2),
    MonsterTemplate("loup", "L", 2, 12, 7, "1d6", 12, 2),

    # Level 3-5: Medium monsters
    MonsterTemplate("orc", "o", 3, 15, 7, "1d6", 10, 3),
    MonsterTemplate("yEux de Sauron", "E", 4, 20, 7, "1d8", 0, 5),  # speed=0: does not move

    # Level 5-9: Strong monsters
    MonsterTemplate("troll", "T", 7, 40, 6, "2d6", 9, 10),
    MonsterTemplate("mewlip", "m", 7, 35, 6, "2d5", 10, 10),
    MonsterTemplate("huorn", "H", 6, 50, 5, "1d10", 5, 15),  # Don't move unless disturbed

    # Level 5-12: Galgals (become Nêzguls at level 12)
    MonsterTemplate("galgal", "g", 5, 45, 6, "2d6", 10, 30),

    # Level 8+: Dangerous monsters
    MonsterTemplate("dragon", "D", 10, 80, 4, "3d8", 10, 30),
    MonsterTemplate("nêzgul", "N", 12, 100, 3, "3d10", 11, 50),  # Mutated galgal
    MonsterTemplate("sphinx", "?", 11, 70, 5, "2d8", 10, 40),
    MonsterTemplate("fée", "f", 8, 40, 7, "1d6", 13, 20),  # Some good, some bad
    MonsterTemplate("sorcière", "F", 9, 50, 6, "2d6", 12, 25),  # Evil fairy
    MonsterTemplate("voleur", "v", 9, 45, 6, "2d7", 12, 30),

    # Level 10-12: Bosses
    MonsterTemplate("Sauron", "S", 11, 200, 2, "5d10", 11, 50),
    MonsterTemplate("Morgoth", "M", 12, 250, 1, "6d12", 10, 100),  # Has Silmaril
]


def get_monster_by_level(dungeon_level: int) -> MonsterTemplate:
    """Get appropriate monster for dungeon level."""
    # Filter monsters that could appear on this level
    candidates = [m for m in MONSTERS if m.level <= dungeon_level + 2]

    if not candidates:
        return MONSTERS[0]  # Default to weakest

    # Weight by relative level (prefer monsters closer to dungeon level)
    import random

    # Filter out bosses unless we're on appropriate levels
    if dungeon_level < 10:
        candidates = [m for m in candidates if m.name not in ("Sauron", "Morgoth")]

    # Galgals only appear levels 5-12
    if dungeon_level < 5 or dungeon_level > 12:
        candidates = [m for m in candidates if "galgal" not in m.name.lower()]

    # Nêzguls only appear at level 12+
    if dungeon_level < 12:
        candidates = [m for m in candidates if "nêzgul" not in m.name.lower()]

    if not candidates:
        candidates = [MONSTERS[0]]

    return random.choice(candidates)


def get_boss_monsters() -> List[MonsterTemplate]:
    """Get list of unique boss monsters."""
    return [m for m in MONSTERS if m.name in ("Sauron", "Morgoth")]
