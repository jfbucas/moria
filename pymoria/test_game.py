#!/usr/bin/env python3
"""
Quick test to verify game components work.
"""

import sys

def test_imports():
    """Test that all modules import correctly."""
    print("Testing imports...")
    try:
        from game.player import Player
        from game.dungeon import Dungeon
        from game.stats import Stats, StatusEffects
        from data.monsters import MONSTERS
        from data.items import WEAPONS, ARMOR
        from data.potions import POTIONS
        from utils.constants import MAP_WIDTH, MAP_HEIGHT
        print("✓ All imports successful")
        return True
    except Exception as e:
        print(f"✗ Import failed: {e}")
        return False

def test_player():
    """Test player creation."""
    print("\nTesting player...")
    try:
        from game.player import Player
        player = Player("Test")
        assert player.name == "Test"
        assert player.current_hp > 0
        assert player.is_alive()
        print(f"✓ Player created: {player.name}, HP: {player.current_hp}/{player.max_hp}")
        return True
    except Exception as e:
        print(f"✗ Player test failed: {e}")
        return False

def test_dungeon():
    """Test dungeon generation."""
    print("\nTesting dungeon generation...")
    try:
        from game.dungeon import Dungeon
        dungeon = Dungeon(1)
        assert dungeon.width > 0
        assert dungeon.height > 0
        assert dungeon.stairs_up is not None
        print(f"✓ Dungeon generated: {dungeon.width}x{dungeon.height}")
        print(f"  Monsters: {len(dungeon.monsters)}")
        print(f"  Items: {len(dungeon.items)}")
        print(f"  Stairs: up={dungeon.stairs_up}, down={dungeon.stairs_down}")
        return True
    except Exception as e:
        print(f"✗ Dungeon test failed: {e}")
        import traceback
        traceback.print_exc()
        return False

def test_data():
    """Test game data."""
    print("\nTesting game data...")
    try:
        from data.monsters import MONSTERS
        from data.items import WEAPONS, ARMOR
        from data.potions import POTIONS
        
        print(f"✓ Monsters: {len(MONSTERS)} templates")
        print(f"  Examples: {', '.join(m.name for m in MONSTERS[:3])}")
        
        print(f"✓ Weapons: {len(WEAPONS)} types")
        print(f"  Examples: {', '.join(w.name for w in WEAPONS[:3])}")
        
        print(f"✓ Armor: {len(ARMOR)} types")
        print(f"  Examples: {', '.join(a.name for a in ARMOR[:3])}")
        
        print(f"✓ Potions: {len(POTIONS)} types")
        print(f"  Examples: {', '.join(p.name_fr for p in POTIONS[:3])}")
        
        return True
    except Exception as e:
        print(f"✗ Data test failed: {e}")
        return False

def main():
    """Run all tests."""
    print("=" * 60)
    print("PyMoria Component Tests")
    print("=" * 60)
    
    tests = [
        test_imports,
        test_player,
        test_dungeon,
        test_data,
    ]
    
    results = [test() for test in tests]
    
    print("\n" + "=" * 60)
    print(f"Results: {sum(results)}/{len(results)} tests passed")
    print("=" * 60)
    
    if all(results):
        print("\n✓ All tests passed! Game is ready to run.")
        print("\nTo play: python3 main.py")
        return 0
    else:
        print("\n✗ Some tests failed. Check errors above.")
        return 1

if __name__ == "__main__":
    sys.exit(main())
