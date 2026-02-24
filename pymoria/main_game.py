"""
PyMoria - Main Entry Point
DOS MORIA 1.9.8.7 (French) reimplementation in Python
"""

import sys
from display.screen import initialize_screen, shutdown_screen
from game.game_loop import Game
from data.items import randomize_all_item_appearances


def show_title_screen(screen):
    """Display title screen and main menu"""
    screen.clear_screen()

    title = [
        "",
        "╔═══════════════════════════════════════════════════════════╗",
        "║                                                           ║",
        "║                MORIA (TM) Version 1.9.8.7                 ║",
        "║                                                           ║",
        "║                 Copyright AJM86                           ║",
        "║                                                           ║",
        "║            Python Reimplementation 2026                   ║",
        "║                                                           ║",
        "╚═══════════════════════════════════════════════════════════╝",
        "",
        "",
        "      [N] Nouvelle partie",
        "      [Q] Quitter",
        "",
        "",
        "Choisissez une option...",
    ]

    for i, line in enumerate(title):
        col = (80 - len(line)) // 2
        screen.put_char_at(line, max(0, col), 4 + i)

    screen.stdscr.refresh()

    # Get choice
    while True:
        key = screen.get_key()
        if key in ['n', 'N']:
            return 'new_game'
        elif key in ['q', 'Q']:
            return 'quit'


def get_player_name(screen):
    """Get player name from user"""
    import curses

    screen.clear_screen()

    prompt = "Entrez votre nom (15 caractères max):"
    screen.put_char_at(prompt, (80 - len(prompt)) // 2, 10)

    # Enable cursor and echo for name input
    curses.curs_set(1)
    curses.echo()

    # Get name
    screen.stdscr.move(12, 30)
    name = screen.stdscr.getstr(12, 30, 15).decode('utf-8')

    # Disable cursor and echo
    curses.noecho()
    curses.curs_set(0)

    if not name:
        name = "Aventurier"

    return name


def main():
    """Main entry point"""
    screen = None

    try:
        # Initialize display
        screen = initialize_screen()

        # Randomize item appearances at game start
        randomize_all_item_appearances()

        # Main menu loop
        while True:
            choice = show_title_screen(screen)

            if choice == 'quit':
                break

            elif choice == 'new_game':
                # Get player name
                player_name = get_player_name(screen)

                # Create game
                game = Game(screen)
                game.create_new_game(player_name)

                # Show welcome message
                screen.clear_screen()
                welcome_lines = [
                    "",
                    "",
                    f"Bienvenue, {player_name}!",
                    "",
                    "Vous allez entrer dans le labyrinthe de la Moria.",
                    "",
                    "Préparez-vous à affronter les ténèbres...",
                    "",
                    "",
                    "Appuyez sur une touche pour commencer...",
                ]

                for i, line in enumerate(welcome_lines):
                    col = (80 - len(line)) // 2
                    screen.put_char_at(line, max(0, col), 7 + i)

                screen.stdscr.refresh()
                screen.get_key()

                # Run game loop
                game.run_game_loop()

                # After game ends, return to menu

    except KeyboardInterrupt:
        # Handle Ctrl+C gracefully
        pass

    except Exception as e:
        # Make sure we restore terminal even on error
        if screen:
            shutdown_screen()
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

    finally:
        # Clean shutdown
        if screen:
            shutdown_screen()

    print("Merci d'avoir joué à PyMoria!")


if __name__ == "__main__":
    main()
