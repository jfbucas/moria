"""
Main Game Loop for PyMoria
Turn-based game loop following exact order from PLAYER_ACTIONS.md
Reference: MORIA_COMPLETE.md Section 1.4 (Game Flow)
"""

import random
from typing import Optional
from game.entities import Player, DungeonLevel, Monster
from game.input import InputHandler, get_movement_vector
from game.monster_ai import update_all_monsters
from game.dungeon import generate_dungeon_level, initialize_boss_monsters, populate_level_with_monsters
from game.level_manager import advance_to_next_level
from display.screen import Screen
from utils.constants import *
from data.messages import *


class Game:
    """
    Main game controller
    Manages game state, turn processing, and game loop
    """

    def __init__(self, screen: Screen):
        """
        Initialize game

        Args:
            screen: Display screen instance
        """
        self.screen = screen
        self.input_handler = InputHandler(screen)

        # Game state
        self.player: Optional[Player] = None
        self.current_level: Optional[DungeonLevel] = None
        self.dungeon_level: int = 1
        self.turn_count: int = 0
        self.victory: bool = False

        # Level data
        self.levels: dict = {}  # Store all dungeon levels

    def create_new_game(self, player_name: str) -> Player:
        """
        Create a new game with player

        Args:
            player_name: Name for the player character

        Returns:
            New Player instance
        """
        # Create player
        self.player = Player(name=player_name)
        self.player.max_hp = 50
        self.player.current_hp = 50
        self.player.player_level = 1
        self.player.experience = 0
        self.player.x = 10
        self.player.y = 10
        self.player.dungeon_level = 1
        self.player.base_ac = 0

        # Generate first dungeon level
        self.dungeon_level = 1
        self.current_level = generate_dungeon_level(1, self.player)
        self.levels[1] = self.current_level

        # Place player at the up-stairs position
        self.player.x = self.current_level.stairs_up_col
        self.player.y = self.current_level.stairs_up_row

        # Place all boss monsters once at game start
        initialize_boss_monsters(self.levels, self.player)

        return self.player

    def process_player_action(self, key: str) -> bool:
        """
        Process player action and return whether a turn was consumed

        Args:
            key: Key pressed by player

        Returns:
            True if action consumed a turn, False otherwise
        """
        # Movement commands
        vector = get_movement_vector(key)
        if vector:
            return self._try_move_player(vector)

        # Inventory
        elif key == CMD_INVENTORY:
            self._show_inventory()
            return False  # No turn consumed

        # Equipment
        elif key == CMD_EQUIPMENT:
            self.screen.draw_message("Equipment screen not yet implemented")
            return False

        # Drop
        elif key == CMD_DROP:
            self.screen.draw_message("Drop not yet implemented")
            return False

        # Pickup
        elif key == CMD_PICKUP:
            self.screen.draw_message("Pickup not yet implemented")
            return False

        # Search
        elif key == CMD_SEARCH:
            self.screen.draw_message("You search the area...")
            return True  # Consumes a turn

        # Rest
        elif key == CMD_REST:
            self.screen.draw_message("You rest...")
            return True  # Consumes a turn

        # Cast spell
        elif key == CMD_CAST_SPELL:
            self.screen.draw_message("Spell casting not yet implemented")
            return False

        # Help
        elif key == CMD_HELP:
            self._show_help()
            return False

        # Quit
        elif key == CMD_QUIT:
            if self.input_handler.confirm_yes_no("Quitter le jeu? (o/n)"):
                self.player.is_dying = True  # Trigger quit
            return False

        # Unknown command
        else:
            return False

    def _try_move_player(self, vector: tuple) -> bool:
        """
        Try to move player in direction

        Args:
            vector: (dx, dy) movement vector

        Returns:
            True if movement succeeded (turn consumed)
        """
        dx, dy = vector
        new_x = self.player.x + dx
        new_y = self.player.y + dy

        # Check bounds
        if new_y < 0 or new_y >= MAP_HEIGHT or new_x < 0 or new_x >= MAP_WIDTH:
            self.screen.draw_message(MSG_WALL)
            return False

        # Check if passable
        if self.current_level.is_passable(new_y, new_x):
            self.player.x = new_x
            self.player.y = new_y

            # Check for stairs under the player
            tile = self.current_level.get_tile(new_x, new_y)
            if tile == TILE_STAIRS_DOWN:
                if self.input_handler.confirm_yes_no(MSG_STAIRS_DOWN + " (o/n)"):
                    advance_to_next_level(0, self, self.screen)
            elif tile == TILE_STAIRS_UP:
                if self.input_handler.confirm_yes_no(MSG_STAIRS_UP + " (o/n)"):
                    advance_to_next_level(1, self, self.screen)

            return True  # Movement consumes a turn
        else:
            self.screen.draw_message(MSG_WALL)
            return False

    def _show_inventory(self):
        """Display inventory screen"""
        self.screen.clear_screen()
        self.screen.put_char_at("=== INVENTAIRE ===", 30, 2)

        if len(self.player.inventory) == 0:
            self.screen.put_char_at(MSG_EMPTY_INVENTORY, 25, 5)
        else:
            for i, item in enumerate(self.player.inventory):
                self.screen.put_char_at(f"{i+1}. {item}", 10, 5 + i)

        self.screen.put_char_at("Appuyez sur une touche...", 25, 20)
        self.screen.stdscr.refresh()
        self.input_handler.wait_for_keypress()

    def _show_help(self):
        """Display help screen"""
        self.screen.clear_screen()
        help_lines = [
            "=== AIDE - MORIA ===",
            "",
            "Déplacement:",
            "  Flèches ou 8,2,4,6 (pavé numérique)",
            "  Pas de diagonales!",
            "",
            "Commandes:",
            "  i - Inventaire",
            "  e - Équipement",
            "  d - Jeter",
            "  , - Ramasser",
            "  s - Chercher",
            "  r - Se reposer",
            "  m - Lancer un sort",
            "  ? - Aide",
            "  q - Quitter",
            "",
            "Appuyez sur une touche...",
        ]

        for i, line in enumerate(help_lines):
            self.screen.put_char_at(line, 25, 3 + i)

        self.screen.stdscr.refresh()
        self.input_handler.wait_for_keypress()

    def handle_food_consumption(self):
        """
        Handle food consumption per turn
        Reference: PLAYER_ACTIONS.md Section 3
        """
        self.player.food_level -= FOOD_CONSUMPTION_PER_TURN

        # Starvation damage
        if self.player.food_level <= FOOD_DYING:
            damage = random.randint(STARVATION_DAMAGE_MIN, STARVATION_DAMAGE_MAX)
            self.player.current_hp -= damage
            self.screen.draw_message(MSG_STARVING)

    def handle_poison_damage(self):
        """
        Handle poison damage per turn
        Reference: PLAYER_ACTIONS.md Section 7
        """
        if self.player.effect_active[EFFECT_POISON]:
            damage = random.randint(POISON_DAMAGE_MIN, POISON_DAMAGE_MAX)
            self.player.current_hp -= damage
            self.screen.draw_message("Le poison vous affaiblit...")

    def handle_timed_effects(self):
        """
        Tick down all timed effects
        Reference: PLAYER_ACTIONS.md Section 7
        """
        for i in range(NUM_TIMED_EFFECTS):
            if self.player.effect_active[i]:
                self.player.effect_timer[i] -= 1

                if self.player.effect_timer[i] <= 0:
                    self.player.effect_active[i] = False

                    # Display expiration message
                    if i in EFFECT_EXPIRE_MESSAGES:
                        self.screen.draw_message(EFFECT_EXPIRE_MESSAGES[i])

    def handle_hp_regeneration(self):
        """
        Handle HP regeneration
        Reference: PLAYER_ACTIONS.md Section 4
        """
        regen_delay = get_regen_delay(self.dungeon_level)

        self.player.regen_counter += 1

        if self.player.regen_counter >= regen_delay:
            if self.player.current_hp < self.player.max_hp:
                self.player.current_hp += 1
            self.player.regen_counter = 0

    def update_monsters(self):
        """
        Update all monsters using the monster AI module.
        Reference: MONSTER_AI.md
        """
        update_all_monsters(
            self.current_level,
            self.player,
            dungeon_level=self.dungeon_level,
            screen=self.screen,
        )

    def spawn_monsters(self):
        """
        Wandering monster spawner — called every 20 turns.
        Reference: MONSTER_SPAWNING.md §4 populate_level_with_monsters
        """
        populate_level_with_monsters(
            self.current_level,
            self.dungeon_level,
            self.player,
        )

    def check_death(self) -> bool:
        """
        Check if player has died

        Returns:
            True if player is dead
        """
        if self.player.current_hp <= 0:
            self.player.is_dying = True
            return True
        return False

    def handle_death(self):
        """
        Handle player death
        Reference: SHOP_AND_UI.md Section 4 (Death & Game Over)
        """
        self.screen.clear_screen()

        death_msg = [
            "",
            "",
            "╔════════════════════════════════════╗",
            "║                                    ║",
            "║        VOUS ÊTES MORT!             ║",
            "║                                    ║",
            "║      Repose en paix...             ║",
            "║                                    ║",
            "╚════════════════════════════════════╝",
            "",
            f"Niveau atteint: {self.dungeon_level}",
            f"Or collecté: {self.player.get_total_gold()}",
            f"Expérience: {self.player.experience}",
            "",
            "Appuyez sur une touche...",
        ]

        for i, line in enumerate(death_msg):
            col = (SCREEN_WIDTH - len(line)) // 2
            self.screen.put_char_at(line, col, 5 + i)

        self.screen.stdscr.refresh()
        self.input_handler.wait_for_keypress()

    def run_game_loop(self):
        """
        Main game loop
        Reference: MORIA_COMPLETE.md Section 1.4 (Game Flow)
        CRITICAL: Follow exact order from PLAYER_ACTIONS.md
        """
        # Main game loop
        while not self.player.is_dying and not self.victory:
            # 1. Display
            self.screen.draw_dungeon(self.current_level, self.player)
            self.screen.draw_status_bar(self.player)

            # 2. Player input
            key = self.input_handler.read_key()

            # 3. Process player action
            turn_consumed = self.process_player_action(key)

            if turn_consumed:
                # Action consumed a turn - process turn effects

                # 4. Food consumption
                self.handle_food_consumption()

                # 5. Poison damage
                self.handle_poison_damage()

                # 6. Tick down timed effects
                self.handle_timed_effects()

                # 7. HP regeneration
                self.handle_hp_regeneration()

                # 8. Update all monsters
                self.update_monsters()

                # 9. Monster spawning (every 20 turns)
                self.turn_count += 1
                if self.turn_count % MONSTER_SPAWN_INTERVAL == 0:
                    self.spawn_monsters()

                # 10. Check death
                if self.check_death():
                    break

        # Game over
        if self.player.is_dying:
            self.handle_death()
        elif self.victory:
            self.screen.draw_message(MSG_VICTORY, wait_for_key=True)
