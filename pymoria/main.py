"""
PyMoria - Main entry point
DOS MORIA 1.9.8.7 (French) reimplementation in Python
"""

from game.entities import Player, Monster, Item, DungeonLevel


def main():
    """Main game entry point"""
    print("PyMoria - Python reimplementation of DOS MORIA 1.9.8.7")
    print("=" * 60)
    print()

    # Test data structures
    print("Creating player...")
    player = Player(name="Test Hero")
    player.max_hp = 50
    player.current_hp = 50

    print(f"  Name: {player.name}")
    print(f"  Stats: Force={player.strength}, Dext={player.dexterity}, Int={player.intelligence}")
    print(f"  HP: {player.current_hp}/{player.max_hp}")
    print(f"  Level: {player.player_level}, XP: {player.experience}")
    print(f"  Gold: {player.get_total_gold()}")
    print(f"  Food: {player.get_food_status()}")
    print()

    # Test XP formula
    print("XP thresholds:")
    for level in range(1, 11):
        xp = Player.get_xp_for_level(level)
        print(f"  Level {level}: {xp:,} XP")
    print()

    # Test monster
    print("Creating monster...")
    monster = Monster(
        char='C',
        template_id=0,
        max_hp=10,
        current_hp=10,
        row=5,
        col=5
    )
    print(f"  Char: {monster.char}")
    print(f"  HP: {monster.current_hp}/{monster.max_hp}")
    print(f"  Position: ({monster.col}, {monster.row})")
    print(f"  Move toggle: {monster.move_toggle}")
    print()

    # Test item
    print("Creating item...")
    item = Item(type=1, subtype=0, count=1)  # Potion
    item.set_total_value(50)
    print(f"  Type: {item.type}, Subtype: {item.subtype}")
    print(f"  Count: {item.count}")
    print(f"  Value: {item.get_total_value()} gold")
    print()

    # Test dungeon level
    print("Creating dungeon level...")
    level = DungeonLevel(level_number=1)
    level.set_tile(10, 10, '>')  # Stairs down
    tile = level.get_tile(10, 10)
    print(f"  Level: {level.level_number}")
    print(f"  Visited: {level.visited_flag}")
    print(f"  Tile at (10,10): '{tile}'")
    print(f"  Passable at (10,10): {level.is_passable(10, 10)}")
    print()

    print("Data structures initialized successfully!")
    print("Ready for game implementation.")


if __name__ == "__main__":
    main()
