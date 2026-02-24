"""
Monster Templates for PyMoria
Based on reverse/ENTITY_DATABASE.md Section 1
All 35 monster templates with exact stats from original game
"""

from dataclasses import dataclass
from typing import List


@dataclass
class MonsterTemplate:
    """Monster template structure matching original game data"""
    template_id: int
    char: str
    name_french: str
    name_english: str
    experience: int
    to_hit: int
    hit_points: int
    armor_class: int
    num_attacks: int
    damage_per_attack: int
    speed_bonus: int
    level: int
    item_drop_chance: int  # numerator
    item_drop_type: int     # item type to drop
    special_ability: int    # wand-like ability trigger (1/N chance)
    is_invisible: bool
    is_hostile: bool
    is_stationary: bool
    article_indef: str      # French indefinite article (un/une/l')
    article_def: str        # French definite article (le/la/l')


# Monster Templates (indices 1-35)
# Reference: ENTITY_DATABASE.md Section 1
MONSTER_TEMPLATES: List[MonsterTemplate] = [
    # Index 0 - placeholder (unused)
    None,

    # Index 1 - Air elemental
    MonsterTemplate(
        template_id=1, char='a', name_french="Air", name_english="Air elemental",
        experience=28, to_hit=8, hit_points=50, armor_class=6,
        num_attacks=3, damage_per_attack=4, speed_bonus=0, level=18,
        item_drop_chance=0, item_drop_type=0, special_ability=13,
        is_invisible=True, is_hostile=False, is_stationary=False,
        article_indef="l'", article_def="l'"
    ),

    # Index 2 - Spider
    MonsterTemplate(
        template_id=2, char='A', name_french="Araignée", name_english="Spider",
        experience=1, to_hit=1, hit_points=5, armor_class=2,
        num_attacks=1, damage_per_attack=2, speed_bonus=0, level=12,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="une", article_def="l'"
    ),

    # Index 3 - Balrog
    MonsterTemplate(
        template_id=3, char='B', name_french="Balrog", name_english="Balrog",
        experience=40, to_hit=11, hit_points=140, armor_class=9,
        num_attacks=8, damage_per_attack=5, speed_bonus=60, level=18,
        item_drop_chance=3, item_drop_type=7, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 4 - Bat
    MonsterTemplate(
        template_id=4, char='C', name_french="Chauve Souris", name_english="Bat",
        experience=1, to_hit=3, hit_points=5, armor_class=4,
        num_attacks=1, damage_per_attack=4, speed_bonus=0, level=15,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="une", article_def="la"
    ),

    # Index 5 - Crebain (crows)
    MonsterTemplate(
        template_id=5, char='â', name_french="Crébain", name_english="Crebain",
        experience=3, to_hit=5, hit_points=15, armor_class=4,
        num_attacks=3, damage_per_attack=3, speed_bonus=0, level=17,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 6 - Dragon
    MonsterTemplate(
        template_id=6, char='D', name_french="Dragon", name_english="Dragon",
        experience=25, to_hit=9, hit_points=90, armor_class=9,
        num_attacks=10, damage_per_attack=3, speed_bonus=0, level=13,
        item_drop_chance=6, item_drop_type=3, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 7 - Winged Dragon
    MonsterTemplate(
        template_id=7, char='§', name_french="Dragon Ailé", name_english="Winged Dragon",
        experience=30, to_hit=10, hit_points=100, armor_class=9,
        num_attacks=8, damage_per_attack=4, speed_bonus=0, level=16,
        item_drop_chance=10, item_drop_type=5, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 8 - Eye of Sauron (stationary, hostile)
    MonsterTemplate(
        template_id=8, char='E', name_french="oEil", name_english="Eye of Sauron",
        experience=5, to_hit=5, hit_points=10, armor_class=6,
        num_attacks=0, damage_per_attack=0, speed_bonus=0, level=15,
        item_drop_chance=20, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=True, is_stationary=False,
        article_indef="un", article_def="l'"
    ),

    # Index 9 - Fairy
    MonsterTemplate(
        template_id=9, char='F', name_french="Fée", name_english="Fairy",
        experience=20, to_hit=6, hit_points=30, armor_class=6,
        num_attacks=0, damage_per_attack=0, speed_bonus=0, level=20,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="une", article_def="la"
    ),

    # Index 10 - Barrow-wight
    MonsterTemplate(
        template_id=10, char='G', name_french="Galgal", name_english="Barrow-wight",
        experience=10, to_hit=7, hit_points=30, armor_class=6,
        num_attacks=6, damage_per_attack=2, speed_bonus=0, level=15,
        item_drop_chance=15, item_drop_type=6, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 11 - Goblin
    MonsterTemplate(
        template_id=11, char='g', name_french="Gobelin", name_english="Goblin",
        experience=3, to_hit=4, hit_points=12, armor_class=3,
        num_attacks=4, damage_per_attack=2, speed_bonus=0, level=12,
        item_drop_chance=10, item_drop_type=1, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 12 - Huorn (tree - hostile, stationary in original)
    MonsterTemplate(
        template_id=12, char='H', name_french="Huorn", name_english="Huorn",
        experience=15, to_hit=8, hit_points=50, armor_class=7,
        num_attacks=10, damage_per_attack=2, speed_bonus=80, level=18,
        item_drop_chance=4, item_drop_type=2, special_ability=0,
        is_invisible=False, is_hostile=True, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 13 - Wolf
    MonsterTemplate(
        template_id=13, char='L', name_french="Loup", name_english="Wolf",
        experience=2, to_hit=3, hit_points=10, armor_class=3,
        num_attacks=2, damage_per_attack=3, speed_bonus=0, level=14,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 14 - Werewolf
    MonsterTemplate(
        template_id=14, char='¶', name_french="Loup Garou", name_english="Werewolf",
        experience=10, to_hit=8, hit_points=40, armor_class=6,
        num_attacks=3, damage_per_attack=4, speed_bonus=0, level=18,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 15 - Mewlip
    MonsterTemplate(
        template_id=15, char='M', name_french="Mewlip", name_english="Mewlip",
        experience=4, to_hit=7, hit_points=20, armor_class=6,
        num_attacks=1, damage_per_attack=5, speed_bonus=0, level=13,
        item_drop_chance=10, item_drop_type=5, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 16 - Southron
    MonsterTemplate(
        template_id=16, char='æ', name_french="Moricaud", name_english="Southron",
        experience=6, to_hit=6, hit_points=26, armor_class=5,
        num_attacks=4, damage_per_attack=4, speed_bonus=0, level=15,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 17 - Nazgûl
    MonsterTemplate(
        template_id=17, char='N', name_french="Nazgûl", name_english="Nazgûl",
        experience=35, to_hit=10, hit_points=110, armor_class=6,
        num_attacks=6, damage_per_attack=5, speed_bonus=60, level=18,
        item_drop_chance=3, item_drop_type=6, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 18 - Oliphant
    MonsterTemplate(
        template_id=18, char='↕', name_french="Oliphant", name_english="Oliphant",
        experience=35, to_hit=10, hit_points=120, armor_class=7,
        num_attacks=6, damage_per_attack=6, speed_bonus=70, level=17,
        item_drop_chance=4, item_drop_type=3, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="l'"
    ),

    # Index 19 - Orc
    MonsterTemplate(
        template_id=19, char='O', name_french="Orc", name_english="Orc",
        experience=5, to_hit=5, hit_points=16, armor_class=4,
        num_attacks=3, damage_per_attack=4, speed_bonus=0, level=13,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="l'"
    ),

    # Index 20 - Rat
    MonsterTemplate(
        template_id=20, char='R', name_french="Rat", name_english="Rat",
        experience=1, to_hit=5, hit_points=17, armor_class=1,
        num_attacks=1, damage_per_attack=2, speed_bonus=0, level=15,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 21 - Snake
    MonsterTemplate(
        template_id=21, char='S', name_french="Serpent", name_english="Snake",
        experience=2, to_hit=2, hit_points=10, armor_class=2,
        num_attacks=1, damage_per_attack=3, speed_bonus=0, level=12,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 22 - Succubus
    MonsterTemplate(
        template_id=22, char='s', name_french="Succube", name_english="Succubus",
        experience=30, to_hit=11, hit_points=80, armor_class=9,
        num_attacks=5, damage_per_attack=5, speed_bonus=0, level=16,
        item_drop_chance=4, item_drop_type=2, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="une", article_def="la"
    ),

    # Index 23 - Troll
    MonsterTemplate(
        template_id=23, char='T', name_french="Troll", name_english="Troll",
        experience=10, to_hit=7, hit_points=50, armor_class=7,
        num_attacks=10, damage_per_attack=2, speed_bonus=0, level=13,
        item_drop_chance=7, item_drop_type=2, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 24 - Uruk-hai
    MonsterTemplate(
        template_id=24, char='U', name_french="Uruk-haï", name_english="Uruk-hai",
        experience=6, to_hit=6, hit_points=25, armor_class=4,
        num_attacks=3, damage_per_attack=5, speed_bonus=0, level=15,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="l'"
    ),

    # Index 25 - Variag
    MonsterTemplate(
        template_id=25, char='v', name_french="Variag", name_english="Variag",
        experience=6, to_hit=5, hit_points=23, armor_class=4,
        num_attacks=2, damage_per_attack=8, speed_bonus=0, level=14,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 26 - Thief
    MonsterTemplate(
        template_id=26, char='V', name_french="Voleur", name_english="Thief",
        experience=20, to_hit=6, hit_points=30, armor_class=6,
        num_attacks=0, damage_per_attack=0, speed_bonus=0, level=20,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 27 - Warg
    MonsterTemplate(
        template_id=27, char='W', name_french="Wharg", name_english="Warg",
        experience=7, to_hit=7, hit_points=30, armor_class=5,
        num_attacks=2, damage_per_attack=7, speed_bonus=0, level=14,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # Index 28 - Wose
    MonsterTemplate(
        template_id=28, char='w', name_french="Woose", name_english="Wose",
        experience=15, to_hit=9, hit_points=50, armor_class=4,
        num_attacks=4, damage_per_attack=6, speed_bonus=0, level=19,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=False,
        article_indef="un", article_def="le"
    ),

    # =========================================================================
    # UNIQUE / BOSS MONSTERS (Stationary)
    # =========================================================================

    # Index 29 - Carcharoth (unique wolf boss)
    MonsterTemplate(
        template_id=29, char='L', name_french="Carcharoth", name_english="Carcharoth",
        experience=30, to_hit=10, hit_points=120, armor_class=9,
        num_attacks=9, damage_per_attack=3, speed_bonus=40, level=19,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=True,
        article_indef="", article_def=""
    ),

    # Index 30 - Glaurung (unique dragon boss)
    MonsterTemplate(
        template_id=30, char='D', name_french="Glaurung", name_english="Glaurung",
        experience=70, to_hit=13, hit_points=150, armor_class=10,
        num_attacks=15, damage_per_attack=3, speed_bonus=35, level=22,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=True,
        article_indef="", article_def=""
    ),

    # Index 31 - Ungoliant (unique spider boss)
    MonsterTemplate(
        template_id=31, char='è', name_french="Ungoliant", name_english="Ungoliant",
        experience=150, to_hit=15, hit_points=195, armor_class=11,
        num_attacks=10, damage_per_attack=7, speed_bonus=30, level=27,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=True,
        article_indef="", article_def=""
    ),

    # Index 32 - Saruman (unique wizard boss)
    MonsterTemplate(
        template_id=32, char='ä', name_french="Saroumane", name_english="Saruman",
        experience=50, to_hit=11, hit_points=150, armor_class=7,
        num_attacks=4, damage_per_attack=5, speed_bonus=0, level=28,
        item_drop_chance=0, item_drop_type=0, special_ability=25,
        is_invisible=False, is_hostile=False, is_stationary=True,
        article_indef="", article_def=""
    ),

    # Index 33 - The Watcher (unique boss - hostile, stationary)
    MonsterTemplate(
        template_id=33, char='X', name_french="Le Guetteur", name_english="The Watcher",
        experience=190, to_hit=14, hit_points=200, armor_class=12,
        num_attacks=15, damage_per_attack=2, speed_bonus=0, level=24,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=True, is_stationary=True,
        article_indef="", article_def=""
    ),

    # Index 34 - Sauron (unique final boss)
    MonsterTemplate(
        template_id=34, char='☺', name_french="Sauron", name_english="Sauron",
        experience=100, to_hit=12, hit_points=180, armor_class=11,
        num_attacks=10, damage_per_attack=6, speed_bonus=50, level=25,
        item_drop_chance=0, item_drop_type=0, special_ability=20,
        is_invisible=False, is_hostile=False, is_stationary=True,
        article_indef="", article_def=""
    ),

    # Index 35 - Morgoth (ultimate boss)
    MonsterTemplate(
        template_id=35, char='ê', name_french="Morgoth", name_english="Morgoth",
        experience=200, to_hit=17, hit_points=210, armor_class=12,
        num_attacks=10, damage_per_attack=10, speed_bonus=40, level=30,
        item_drop_chance=0, item_drop_type=0, special_ability=0,
        is_invisible=False, is_hostile=False, is_stationary=True,
        article_indef="", article_def=""
    ),
]


def get_monster_template(template_id: int) -> MonsterTemplate:
    """
    Get monster template by ID (1-35)
    Returns None if invalid ID
    """
    if 1 <= template_id <= 35:
        return MONSTER_TEMPLATES[template_id]
    return None


def get_all_normal_monsters():
    """Get all non-stationary monsters (for random spawning)"""
    return [t for t in MONSTER_TEMPLATES[1:29] if t and not t.is_stationary]


def get_all_boss_monsters():
    """Get all unique/boss monsters (stationary)"""
    return [t for t in MONSTER_TEMPLATES[29:36] if t and t.is_stationary]
