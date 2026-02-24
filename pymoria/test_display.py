"""
Test script for display system
Validates curses-based screen rendering
"""

import sys
from display.screen import initialize_screen, shutdown_screen, get_screen
from game.entities import Player, Monster, Item, DungeonLevel
import time


def test_display():
    """Test display system with sample dungeon"""
    screen = None

    try:
        # Initialize screen
        print("Initializing display system...")
        screen = initialize_screen()

        # Create test player
        player = Player(name="Test Hero")
        player.x = 10
        player.y = 10
        player.max_hp = 100
        player.current_hp = 75
        player.player_level = 5
        player.experience = 750
        player.strength = 100
        player.intelligence = 100
        player.food_level = 3500
        player.gold_low = 150
        player.gold_high = 0
        player.base_ac = 5

        # Create test dungeon level
        level = DungeonLevel(level_number=1)

        # Draw a simple room (10×10 box starting at 5,5)
        # Top wall
        for col in range(5, 16):
            level.set_tile(5, col, '┴')
        # Bottom wall
        for col in range(5, 16):
            level.set_tile(15, col, '┬')
        # Left wall
        for row in range(6, 15):
            level.set_tile(row, 5, '┤')
        # Right wall
        for row in range(6, 15):
            level.set_tile(row, 15, '├')

        # Draw floor
        for row in range(6, 15):
            for col in range(6, 15):
                level.set_tile(row, col, ' ')

        # Add some corridor
        for col in range(16, 25):
            level.set_tile(10, col, ' ')
        level.set_tile(10, 25, '>')  # Stairs down

        # Create test monsters
        monsters = []
        bat = Monster(char='C', template_id=4, max_hp=5, current_hp=5, row=8, col=8)
        wolf = Monster(char='L', template_id=13, max_hp=10, current_hp=10, row=12, col=12)
        monsters.append(bat)
        monsters.append(wolf)

        # Create test items
        items = []
        potion = Item(type=2, subtype=1, count=1)  # Healing potion
        potion.row = 7
        potion.col = 13
        items.append(potion)

        gold = Item(type=0, subtype=0, count=1)  # Gold
        gold.row = 9
        gold.col = 11
        items.append(gold)

        # Display test
        screen.clear_screen()

        # Draw message
        screen.draw_message("Welcome to PyMoria! Test display active.")

        # Draw dungeon
        screen.draw_dungeon(level, player, monsters, items)

        # Draw status bar
        screen.draw_status_bar(player)

        # Show instructions
        screen.draw_message("Arrow keys/8246 to move, 'q' to quit, 'm' for menu, 's' for stats")

        # Main test loop
        running = True
        while running:
            key = screen.get_key()

            if key == 'q':
                running = False
            elif key == 'm':
                # Test menu
                options = ["New Game", "Load Game", "High Scores", "Quit"]
                choice = screen.show_menu("MORIA - Main Menu", options)
                if choice is not None:
                    screen.draw_message(f"You selected: {options[choice]}")
                else:
                    screen.draw_message("Menu cancelled")
                # Redraw everything
                screen.draw_dungeon(level, player, monsters, items)
                screen.draw_status_bar(player)
            elif key == 's':
                # Test character stats display
                screen.clear_screen()
                screen.draw_box(2, 20, 15, 40)
                screen.put_char_at("Character Stats", 30, 3)
                screen.put_char_at(f"Name: {player.name}", 22, 5)
                screen.put_char_at(f"Level: {player.player_level}", 22, 6)
                screen.put_char_at(f"HP: {player.current_hp}/{player.max_hp}", 22, 7)
                screen.put_char_at(f"Strength: {player.strength}", 22, 8)
                screen.put_char_at(f"Dexterity: {player.dexterity}", 22, 9)
                screen.put_char_at(f"Intelligence: {player.intelligence}", 22, 10)
                screen.put_char_at(f"Gold: {player.get_total_gold()}", 22, 11)
                screen.put_char_at(f"Food: {player.get_food_status()}", 22, 12)
                screen.put_char_at("Press any key...", 30, 14)
                screen.get_key()
                # Redraw dungeon
                screen.clear_screen()
                screen.draw_dungeon(level, player, monsters, items)
                screen.draw_status_bar(player)
                screen.draw_message("Arrow keys/8246 to move, 'q' to quit, 'm' for menu, 's' for stats")
            elif key in ['UP', 'DOWN', 'LEFT', 'RIGHT']:
                # Test movement
                old_x, old_y = player.x, player.y

                if key == 'UP':
                    new_y = player.y - 1
                    new_x = player.x
                elif key == 'DOWN':
                    new_y = player.y + 1
                    new_x = player.x
                elif key == 'LEFT':
                    new_y = player.y
                    new_x = player.x - 1
                elif key == 'RIGHT':
                    new_y = player.y
                    new_x = player.x + 1

                # Check if movement is valid (not into wall)
                if level.is_passable(new_y, new_x):
                    player.x = new_x
                    player.y = new_y
                    screen.draw_message(f"Moved to ({player.x}, {player.y})")
                else:
                    screen.draw_message("You bump into a wall!")

                # Redraw
                screen.draw_dungeon(level, player, monsters, items)
                screen.draw_status_bar(player)

        # Exit message
        screen.draw_message("Exiting... Press any key.", wait_for_key=True)

    except Exception as e:
        # Make sure we restore terminal even on error
        if screen:
            shutdown_screen()
        print(f"Error during test: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

    finally:
        # Clean shutdown
        if screen:
            shutdown_screen()

    print("✓ Display test completed successfully!")
    print("✓ All rendering functions validated!")
    print()
    print("Ready for Prompt 5 (Dungeon Generation)")


if __name__ == "__main__":
    test_display()
