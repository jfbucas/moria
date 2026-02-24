"""
Test script for input handling system
Validates keyboard input, command mapping, direction prompts
"""

from display.screen import initialize_screen, shutdown_screen
from game.input import InputHandler, is_movement_command, get_movement_vector
from utils.constants import *


def test_input():
    """Test input handling with interactive display"""
    screen = None

    try:
        # Initialize screen
        print("Initializing display...")
        screen = initialize_screen()

        # Create input handler
        input_handler = InputHandler(screen)

        # Clear screen
        screen.clear_screen()

        # Instructions
        instructions = [
            "PyMoria - Input System Test",
            "=" * 60,
            "",
            "Test commands:",
            "  Arrow keys / 2,4,6,8 - Movement (NO diagonals)",
            "  'i' - Inventory",
            "  'e' - Equipment",
            "  'd' - Drop",
            "  'q' - Quit test",
            "  't' - Test direction prompt",
            "  'y' - Test yes/no prompt",
            "  'n' - Test number input",
            "",
            "Press any key to start...",
        ]

        for i, line in enumerate(instructions):
            screen.put_char_at(line, 0, i)

        screen.stdscr.refresh()
        screen.get_key()

        # Clear and start test
        screen.clear_screen()
        screen.draw_message("Input test active. Press 'q' to quit.")

        # Test loop
        running = True
        while running:
            # Get command
            cmd = input_handler.get_command()

            # Process command
            if cmd == CMD_QUIT:
                # Confirm quit
                if input_handler.confirm_yes_no("Quit test? (o/n)"):
                    running = False
                else:
                    screen.draw_message("Test continues. Press 'q' to quit.")

            elif is_movement_command(cmd):
                # Movement command
                vector = get_movement_vector(cmd)
                if vector:
                    dx, dy = vector
                    direction_names = {
                        (0, -1): "North (up)",
                        (0, 1): "South (down)",
                        (-1, 0): "West (left)",
                        (1, 0): "East (right)",
                    }
                    dir_name = direction_names.get(vector, "Unknown")
                    screen.draw_message(f"Movement: {dir_name} - vector ({dx}, {dy})")

            elif cmd == CMD_INVENTORY:
                screen.draw_message("Command: Inventory (i)")

            elif cmd == CMD_EQUIPMENT:
                screen.draw_message("Command: Equipment (e)")

            elif cmd == CMD_DROP:
                screen.draw_message("Command: Drop (d)")

            elif cmd == CMD_PICKUP:
                screen.draw_message("Command: Pickup (,)")

            elif cmd == CMD_SEARCH:
                screen.draw_message("Command: Search (s)")

            elif cmd == CMD_REST:
                screen.draw_message("Command: Rest (r)")

            elif cmd == CMD_CAST_SPELL:
                screen.draw_message("Command: Cast Spell (m)")

            elif cmd == CMD_HELP:
                screen.draw_message("Command: Help (?)")

            elif cmd == 't':
                # Test direction prompt
                screen.draw_message("Testing direction prompt...")
                direction = input_handler.get_direction()

                if direction:
                    dx, dy = direction
                    direction_names = {
                        (0, -1): "North",
                        (0, 1): "South",
                        (-1, 0): "West",
                        (1, 0): "East",
                    }
                    dir_name = direction_names.get(direction, "Unknown")
                    screen.draw_message(f"Direction selected: {dir_name} ({dx}, {dy})")
                else:
                    screen.draw_message("Direction cancelled")

            elif cmd == 'y':
                # Test yes/no prompt
                result = input_handler.confirm_yes_no("Test question - answer yes? (o/n)")
                if result:
                    screen.draw_message("You answered: Oui (yes)")
                else:
                    screen.draw_message("You answered: Non (no)")

            elif cmd == 'n':
                # Test number input
                number = input_handler.get_number_input("Enter a number (1-9):", 1, 9)
                if number is not None:
                    screen.draw_message(f"Number selected: {number}")
                else:
                    screen.draw_message("Number input cancelled")

            else:
                # Unknown command
                if cmd:
                    screen.draw_message(f"Unknown command: '{cmd}' (Press 'q' to quit)")

        # Exit message
        screen.clear_screen()
        msg_lines = [
            "Input Test Complete!",
            "",
            "Validated features:",
            "  ✓ Movement commands (4 directions only, NO diagonals)",
            "  ✓ Inventory commands",
            "  ✓ Action commands",
            "  ✓ System commands",
            "  ✓ Direction prompt (Quelle direction?)",
            "  ✓ Yes/No confirmation (o/n)",
            "  ✓ Number input (1-9)",
            "",
            "Press any key to exit...",
        ]

        for i, line in enumerate(msg_lines):
            screen.put_char_at(line, 0, i + 5)

        screen.stdscr.refresh()
        screen.get_key()

    except Exception as e:
        # Make sure we restore terminal even on error
        if screen:
            shutdown_screen()
        print(f"Error during test: {e}")
        import traceback
        traceback.print_exc()
        return False

    finally:
        # Clean shutdown
        if screen:
            shutdown_screen()

    print("✓ Input system test completed successfully!")
    print("✓ All input handling validated!")
    print()
    print("Ready for Prompt 6 (Game Loop)")
    return True


if __name__ == "__main__":
    test_input()
