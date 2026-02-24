"""
Test script to validate monster and item templates
"""

from data.monsters import MONSTER_TEMPLATES, get_monster_template, get_all_normal_monsters, get_all_boss_monsters
from data.items import (
    randomize_all_item_appearances,
    get_potion_name, get_wand_name, get_ring_name, get_scroll_name,
    POTION_COLORS_MASTER, WAND_WOODS_MASTER, RING_MATERIALS_MASTER,
    ARMOR_NAMES, WEAPON_NAMES, WEAPON_BASE_ATTACK
)


def test_templates():
    """Test all monster and item templates"""
    print("PyMoria - Monster & Item Templates Test")
    print("=" * 60)
    print()

    # Test monster templates
    print("Monster Templates:")
    print(f"  Total templates: {len([t for t in MONSTER_TEMPLATES if t])}")
    print()

    # Test normal monsters
    normal_monsters = get_all_normal_monsters()
    print(f"Normal Monsters ({len(normal_monsters)}):")
    for monster in normal_monsters[:5]:  # Show first 5
        print(f"  {monster.char} - {monster.name_french} ({monster.name_english})")
        print(f"      HP: {monster.hit_points}, AC: {monster.armor_class}, XP: {monster.experience}")
    print(f"  ... and {len(normal_monsters) - 5} more")
    print()

    # Test boss monsters
    boss_monsters = get_all_boss_monsters()
    print(f"Boss Monsters ({len(boss_monsters)}):")
    for monster in boss_monsters:
        print(f"  {monster.char} - {monster.name_french} ({monster.name_english})")
        print(f"      HP: {monster.hit_points}, AC: {monster.armor_class}, XP: {monster.experience}")
        print(f"      Stationary: {monster.is_stationary}, Special: {monster.special_ability}")
    print()

    # Test specific monsters
    print("Specific Monster Tests:")
    bat = get_monster_template(4)
    print(f"  Bat (index 4): char='{bat.char}', HP={bat.hit_points}, speed={bat.speed_bonus}")

    eye = get_monster_template(8)
    print(f"  Eye (index 8): char='{eye.char}', hostile={eye.is_hostile}, attacks={eye.num_attacks}")

    sauron = get_monster_template(34)
    print(f"  Sauron (index 34): char='{sauron.char}', HP={sauron.hit_points}, special={sauron.special_ability}")
    print()

    # Randomize item appearances
    print("Randomizing item appearances...")
    randomize_all_item_appearances()
    print("✓ Item appearances randomized")
    print()

    # Test potion names
    print("Potion Names:")
    print(f"  Master list: {len(POTION_COLORS_MASTER)} colors")
    print(f"  Sample unidentified: {get_potion_name(1, identified=False)}")
    print(f"  Sample identified: {get_potion_name(1, identified=True)}")
    print()

    # Test wand names
    print("Wand Names:")
    print(f"  Master list: {len(WAND_WOODS_MASTER)} woods")
    print(f"  Sample unidentified: {get_wand_name(1, identified=False)}")
    print(f"  Sample identified: {get_wand_name(1, identified=True)}")
    print()

    # Test ring names
    print("Ring Names:")
    print(f"  Master list: {len(RING_MATERIALS_MASTER)} materials")
    print(f"  Sample unidentified: {get_ring_name(0, identified=False)}")
    print(f"  Sample identified: {get_ring_name(0, identified=True)}")
    print()

    # Test scroll names
    print("Scroll Names:")
    print(f"  Generated 25 random scroll names")
    print(f"  Sample unidentified: {get_scroll_name(5, identified=False)}")
    print(f"  Sample identified: {get_scroll_name(5, identified=True)}")
    print()

    # Test armor
    print("Armor Templates:")
    print(f"  Total armor types: {len([a for a in ARMOR_NAMES if a])}")
    print(f"  Sample: {ARMOR_NAMES[1]} (leather armor)")
    print(f"  Sample: {ARMOR_NAMES[6]} (mithril armor)")
    print()

    # Test weapons
    print("Weapon Templates:")
    print(f"  Total weapon types: {len([w for w in WEAPON_NAMES if w])}")
    print(f"  Sample: {WEAPON_NAMES[1]} (base attack: {WEAPON_BASE_ATTACK[1]})")
    print(f"  Sample: {WEAPON_NAMES[9]} (base attack: {WEAPON_BASE_ATTACK[9]})")
    print()

    # Validate critical features
    print("Critical Features Validation:")

    # Check that Eye of Sauron has 0 attacks (doesn't attack)
    eye = get_monster_template(8)
    assert eye.num_attacks == 0, "Eye of Sauron should have 0 attacks"
    print("  ✓ Eye of Sauron has 0 attacks (correct)")

    # Check that boss monsters are stationary
    for boss in boss_monsters:
        assert boss.is_stationary, f"{boss.name_french} should be stationary"
    print(f"  ✓ All {len(boss_monsters)} boss monsters are stationary")

    # Check special abilities on bosses
    saruman = get_monster_template(32)
    assert saruman.special_ability == 25, "Saruman should have special ability 25"
    print("  ✓ Saruman has special ability 25 (1/25 chance per turn)")

    # Check Bat character
    bat = get_monster_template(4)
    assert bat.char == 'C', "Bat should have character 'C'"
    print("  ✓ Bat has character 'C'")

    # Check Wolf character
    wolf = get_monster_template(13)
    assert wolf.char == 'L', "Wolf should have character 'L'"
    print("  ✓ Wolf has character 'L'")

    print()
    print("✓ All templates loaded successfully!")
    print("✓ All validations passed!")
    print()
    print("Ready for Prompt 4 (Dungeon Generation)")


if __name__ == "__main__":
    test_templates()
