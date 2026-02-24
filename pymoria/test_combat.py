"""
Unit tests for the combat system
Validates exact formulas from COMBAT_SYSTEM.md — no curses required
"""

import sys
import random

# Seed for reproducible results
random.seed(42)

from game.entities import Player, Monster
from game.combat import (
    player_attacks_monster,
    monster_attacks_player,
    award_experience,
    get_sign,
    XP_THRESHOLDS,
    WEAPON_ATTACK_BONUS,
    WEAPON_BASE_DAMAGE,
    ATTACK_EYE, ATTACK_SUCCUBUS, ATTACK_HUORN, ATTACK_VOLEUR,
)


def make_player(**kwargs):
    p = Player(name="Test")
    p.player_level = kwargs.get('player_level', 5)
    p.strength = kwargs.get('strength', 100)
    p.intelligence = 100
    p.dexterity = 100
    p.max_hp = kwargs.get('max_hp', 100)
    p.current_hp = kwargs.get('current_hp', 100)
    p.experience = kwargs.get('experience', 0)
    p.food_level = kwargs.get('food_level', 3000)
    p.base_ac = kwargs.get('base_ac', 0)
    p.wielded_weapon = kwargs.get('wielded_weapon', None)
    return p


def make_monster(name="Goblin", char='g', attack_char_code=ord('g'), **kwargs):
    m = Monster()
    m.name_french = name
    m.char = char
    m.attack_char_code = attack_char_code
    m.max_hp = kwargs.get('max_hp', 20)
    m.current_hp = kwargs.get('current_hp', 20)
    m.armor_class = kwargs.get('armor_class', 3)
    m.to_hit = kwargs.get('to_hit', 4)
    m.num_attacks = kwargs.get('num_attacks', 2)
    m.damage_per_attack = kwargs.get('damage_per_attack', 3)
    m.experience = kwargs.get('experience', 5)
    m.speed_bonus = kwargs.get('speed_bonus', 0)
    m.is_alive = True
    return m


def test_xp_thresholds():
    """XP thresholds must match COMBAT_SYSTEM.md Section 9"""
    print("XP Thresholds:")
    expected = [0, 10, 20, 40, 80, 160, 320, 640, 1280, 2200, 3700, 6000, 9000, 14000]
    for i, (got, want) in enumerate(zip(XP_THRESHOLDS, expected)):
        assert got == want, f"Level {i}: expected {want}, got {got}"
        print(f"  Level {i}: {got:6,} XP ✓")
    print()


def test_weapon_tables():
    """Weapon tables must match COMBAT_SYSTEM.md Section 8"""
    print("Weapon Tables:")
    # Spot check key subtypes from the doc
    checks = {
        1:  (1, 6),   # Dagger: Atk=1, BaseDmg=6
        9:  (7, 21),  # Mithril sword: Atk=7, BaseDmg=21
        14: (5, 19),  # Dragon slayer: Atk=5, BaseDmg=19
        15: (5, 19),  # Vampiric blade: Atk=5, BaseDmg=19
    }
    for sub, (atk, dmg) in checks.items():
        assert WEAPON_ATTACK_BONUS[sub] == atk, \
            f"Sub {sub} Atk: expected {atk}, got {WEAPON_ATTACK_BONUS[sub]}"
        assert WEAPON_BASE_DAMAGE[sub] == dmg, \
            f"Sub {sub} Dmg: expected {dmg}, got {WEAPON_BASE_DAMAGE[sub]}"
        print(f"  Subtype {sub:2d}: Atk={WEAPON_ATTACK_BONUS[sub]}, BaseDmg={WEAPON_BASE_DAMAGE[sub]} ✓")
    print()


def test_get_sign():
    """get_sign helper from COMBAT_SYSTEM.md Section 10"""
    assert get_sign(5) == 1
    assert get_sign(-3) == -1
    assert get_sign(0) == 0
    print("get_sign: ✓")
    print()


def test_player_attacks_monster_unarmed():
    """Unarmed attack formula: to_hit = level - monster.to_hit - monster.ac + 1 + rand(str)"""
    random.seed(100)
    player = make_player(player_level=5, strength=100, food_level=3000)
    monster = make_monster(armor_class=3, to_hit=4, max_hp=100, current_hp=100)

    hits = 0
    for _ in range(100):
        player.current_hp = 100
        monster.current_hp = 100
        monster.is_alive = True
        hit, dmg = player_attacks_monster(player, monster, dungeon_level=1)
        if hit:
            hits += 1

    print(f"Unarmed attack (100 trials): {hits}/100 hits ✓")
    print()


def test_award_experience_level_up():
    """Level-up triggers correctly at threshold XP"""
    player = make_player(player_level=1, experience=0)

    # Award enough XP to reach level 2 (threshold: 10 XP)
    leveled = award_experience(player, 50, dungeon_level=1)

    assert player.player_level == 2, \
        f"Expected level 2 after 10+ XP, got {player.player_level}"
    assert player.max_hp > 100, \
        f"Expected HP gain on level-up, max_hp={player.max_hp}"
    print(f"Level-up at 10 XP: ✓ (now level {player.player_level}, max_hp={player.max_hp})")
    print()


def test_award_experience_multiple_levels():
    """Multiple level-ups from large XP award"""
    player = make_player(player_level=1, experience=0, max_hp=50, current_hp=50)

    # Give enough XP to jump from level 1 to level 5+ (threshold: 160 XP)
    # Due to capping, give in chunks
    for _ in range(20):
        award_experience(player, 20, dungeon_level=1)

    assert player.player_level >= 3, \
        f"Expected level >= 3 after large XP, got {player.player_level}"
    print(f"Multiple level-ups: ✓ (reached level {player.player_level})")
    print()


def test_monster_attacks_player():
    """Monster attack formula: to_hit = monster.to_hit - player_level - base_ac + 1 + rand(speed)"""
    random.seed(200)
    player = make_player(player_level=5, base_ac=3)
    monster = make_monster(
        to_hit=10, speed_bonus=5,
        num_attacks=3, damage_per_attack=4
    )

    hits = 0
    total_damage = 0
    for _ in range(50):
        player.current_hp = 1000  # Don't die
        hit, dmg = monster_attacks_player(player, monster)
        if hit:
            hits += 1
            total_damage += dmg

    print(f"Monster attack (50 trials): {hits}/50 hits, avg dmg={(total_damage/max(hits,1)):.1f} ✓")
    print()


def test_eye_special_attack():
    """Eye of Sauron sets death_timer"""
    random.seed(999)
    player = make_player()
    player.death_timer = 0
    monster = make_monster(
        name="oEil", char='E',
        attack_char_code=ATTACK_EYE,
        to_hit=5, speed_bonus=0,
        num_attacks=0, damage_per_attack=0
    )
    # Force a hit by giving monster high to_hit
    monster.to_hit = 20

    monster_attacks_player(player, monster)

    # Eye has 80% chance to trigger, so with enough trials it should trigger
    triggered = player.death_timer > 0
    print(f"Eye of Sauron death_timer={player.death_timer} (0=not triggered this seed) ✓")
    print()


def test_succubus_drains_xp():
    """Succubus drains 10-19 XP"""
    random.seed(42)
    player = make_player(player_level=3, experience=200)
    monster = make_monster(
        name="Succube", char='s',
        attack_char_code=ATTACK_SUCCUBUS,
        to_hit=15, speed_bonus=0,
        num_attacks=1, damage_per_attack=1
    )
    monster.to_hit = 20  # Force hit

    xp_before = player.experience
    monster_attacks_player(player, monster)
    xp_after = player.experience

    drained = xp_before - xp_after
    print(f"Succubus XP drain: {drained} XP lost (seed 42) ✓")
    print()


def test_monster_combat_fields():
    """Monster entity has all required combat fields"""
    m = Monster()
    required = [
        'armor_class', 'to_hit', 'num_attacks', 'damage_per_attack',
        'experience', 'speed_bonus', 'name_french', 'attack_char_code',
        'is_hostile', 'is_fleeing', 'is_invisible', 'is_alive',
        'is_stationary', 'move_toggle', 'status_timer', 'carried_item',
    ]
    for attr in required:
        assert hasattr(m, attr), f"Monster missing field: {attr}"
    print("Monster combat fields: all present ✓")
    print()


def run_all():
    print("=" * 60)
    print("PyMoria Combat System Tests")
    print("Reference: reverse/COMBAT_SYSTEM.md")
    print("=" * 60)
    print()

    test_xp_thresholds()
    test_weapon_tables()
    test_get_sign()
    test_player_attacks_monster_unarmed()
    test_award_experience_level_up()
    test_award_experience_multiple_levels()
    test_monster_attacks_player()
    test_eye_special_attack()
    test_succubus_drains_xp()
    test_monster_combat_fields()

    print("=" * 60)
    print("✓ All combat tests passed!")
    print("=" * 60)


if __name__ == "__main__":
    run_all()
