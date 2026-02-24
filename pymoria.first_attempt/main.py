#!/usr/bin/env python3
"""
PyMoria - Python rewrite of Moria roguelike
Main entry point
"""

import sys
from game.engine import GameEngine


def main():
    """Main entry point."""
    print("Bienvenue dans Moria!")
    print("Initialisation...")

    game = GameEngine()

    try:
        game.initialize()
        if not game.running:
            return 0
        game.run()
    except Exception as e:
        print(f"\nErreur: {e}")
        import traceback
        traceback.print_exc()
        return 1
    finally:
        game.cleanup()

    if not game.player.is_alive():
        print("\n" + "=" * 40)
        print("VOUS ÊTES MORT")
        print("=" * 40)
        print(f"Niveau atteint: {game.current_level}")
        print(f"Niveau personnage: {game.player.level}")
        print(f"Expérience: {game.player.experience}")
        print(f"Or: {game.player.gold}")
        print("=" * 40)
    else:
        print("\nMerci d'avoir joué!")

    return 0


if __name__ == "__main__":
    sys.exit(main())
