"""
Main game engine.
"""

import sys
from typing import Optional
from game.player import Player
from game.dungeon import Dungeon
from display.screen import Screen
from data.potions import get_potion_by_effect
from utils.constants import PotionEffect


class GameEngine:
    """Main game loop and logic."""

    def __init__(self):
        self.screen = Screen()
        self.player: Optional[Player] = None
        self.dungeon: Optional[Dungeon] = None
        self.running = False
        self.current_level = 1
        self.message = ""

    def initialize(self):
        """Initialize game."""
        try:
            self.screen.initialize()

            # Show start menu
            from game.menu import Menu
            menu = Menu(self.screen.stdscr)
            choice = menu.show_title()

            if choice == 'quit':
                self.cleanup()
                sys.exit(0)
            elif choice == 'new':
                # Character creation
                self.player = menu.create_character()
            elif choice == 'load':
                self.message = "Chargement non implémenté. Nouvelle partie."
                self.player = menu.create_character()

            self.new_level(1)
            self.running = True
            self.message = f"Bienvenue {self.player.name} ! Trouvez le Silmaril au niveau 12 !"
        except Exception as e:
            self.cleanup()
            print(f"Erreur d'initialisation: {e}")
            import traceback
            traceback.print_exc()
            sys.exit(1)

    def cleanup(self):
        """Cleanup resources."""
        self.screen.cleanup()

    def new_level(self, level: int):
        """Generate new dungeon level."""
        self.current_level = level
        self.dungeon = Dungeon(level)

        # Place player at stairs up
        if self.dungeon.stairs_up:
            self.player.set_position(*self.dungeon.stairs_up)
        else:
            # Fallback: find any floor space
            for y in range(self.dungeon.height):
                for x in range(self.dungeon.width):
                    if self.dungeon.is_walkable(x, y):
                        self.player.set_position(x, y)
                        return

        # Compute initial field of view
        self.dungeon.update_fov(self.player.x, self.player.y, radius=8)

    def run(self):
        """Main game loop."""
        while self.running and self.player.is_alive():
            try:
                self.update()
                self.draw()
                self.handle_input()
            except KeyboardInterrupt:
                self.running = False

    def update(self):
        """Update game state."""
        self.player.update()

        # Update monsters (they move after player acts)
        self.update_monsters()

        # Check death
        if not self.player.is_alive():
            self.message = "Vous êtes mort! Appuyez sur une touche..."
            self.running = False

    def update_monsters(self):
        """Update all monsters - movement and attacks."""
        import random

        for monster in self.dungeon.monsters[:]:  # Copy list to allow removal
            # Huorns don't move unless disturbed
            if "huorn" in monster['template'].name.lower():
                # Only move if player is adjacent
                dx = abs(monster['x'] - self.player.x)
                dy = abs(monster['y'] - self.player.y)
                if dx > 1 or dy > 1:
                    continue

            # Simple AI: move towards player if nearby, otherwise wander
            dx = self.player.x - monster['x']
            dy = self.player.y - monster['y']
            distance = abs(dx) + abs(dy)  # Manhattan distance

            # If adjacent to player, attack
            if distance == 1:
                self.monster_attack_player(monster)
                continue

            # If player is visible (within 10 tiles), chase
            if distance <= 10:
                # Move towards player (one step)
                move_x = 0 if dx == 0 else (1 if dx > 0 else -1)
                move_y = 0 if dy == 0 else (1 if dy > 0 else -1)
            else:
                # Wander randomly
                move_x = random.choice([-1, 0, 1])
                move_y = random.choice([-1, 0, 1])

            # Try to move
            new_x = monster['x'] + move_x
            new_y = monster['y'] + move_y

            # Check if destination is walkable and not occupied
            if (self.dungeon.is_walkable(new_x, new_y) and
                not self.dungeon.has_monster(new_x, new_y) and
                (new_x, new_y) != (self.player.x, self.player.y)):
                monster['x'] = new_x
                monster['y'] = new_y

    def monster_attack_player(self, monster):
        """Monster attacks the player."""
        import random

        # Parse damage dice (e.g., "2d6" or "1d8+poison")
        damage_str = monster['template'].damage
        base_damage = damage_str.split('+')[0]  # Remove special effects

        # Roll damage
        try:
            if 'd' in base_damage:
                num_dice, dice_size = map(int, base_damage.split('d'))
                damage = sum(random.randint(1, dice_size) for _ in range(num_dice))
            else:
                damage = int(base_damage)
        except:
            damage = 5  # Default

        # Apply damage to player
        self.player.take_damage(damage)
        self.message = f"Le {monster['template'].name} vous frappe! ({damage} dégâts)"

    def draw(self):
        """Draw game state."""
        # Update field of view and discovered tiles
        visible_tiles = self.dungeon.update_fov(self.player.x, self.player.y, radius=8)

        self.screen.draw_map(self.dungeon, self.player, visible_tiles)
        self.screen.draw_status(self.player.get_status_string())
        if self.message:
            self.screen.draw_message(self.message)
        self.screen.refresh()

    def handle_input(self):
        """Handle player input."""
        key = self.screen.get_key()

        if not self.player.can_act():
            self.message = "Vous ne pouvez pas agir!"
            return

        # Movement (vi keys + numpad)
        if key == ord('h') or key == ord('4'):  # Left
            self.try_move(-1, 0)
        elif key == ord('l') or key == ord('6'):  # Right
            self.try_move(1, 0)
        elif key == ord('k') or key == ord('8'):  # Up
            self.try_move(0, -1)
        elif key == ord('j') or key == ord('2'):  # Down
            self.try_move(0, 1)
        elif key == ord('y') or key == ord('7'):  # Up-left
            self.try_move(-1, -1)
        elif key == ord('u') or key == ord('9'):  # Up-right
            self.try_move(1, -1)
        elif key == ord('b') or key == ord('1'):  # Down-left
            self.try_move(-1, 1)
        elif key == ord('n') or key == ord('3'):  # Down-right
            self.try_move(1, 1)

        # Actions (matching MORIA.TXT manual)
        elif key == ord('i'):  # Inventaire
            self.show_inventory()
        elif key == ord('a'):  # Abandonner un objet
            self.drop_item()
        elif key == ord('b'):  # Boire une potion
            self.quaff_potion()
        elif key == ord('m'):  # Manger
            self.eat_food()
        elif key == ord('l'):  # Lire un parchemin
            self.read_scroll()
        elif key == ord('w'):  # Wielding weapon / Porter arme
            self.wield_weapon()
        elif key == ord('W'):  # Remove weapon / Enlever arme
            self.remove_weapon()
        elif key == ord('r'):  # Revêtir une armure
            self.wear_armor()
        elif key == ord('R'):  # Enlever une armure
            self.remove_armor()
        elif key == ord('>'):  # Descendre escalier
            self.try_descend()
        elif key == ord('<'):  # Monter escalier
            self.try_ascend()
        elif key == ord('?'):  # Liste des commandes
            self.show_commands()
        elif key == ord('Q'):  # Quitter
            if self.screen.prompt_char("Vraiment quitter? (o/n)") == 'o':
                self.running = False

    def try_move(self, dx: int, dy: int):
        """Try to move player."""
        new_x = self.player.x + dx
        new_y = self.player.y + dy

        # Check bounds and walkability
        if not self.dungeon.is_walkable(new_x, new_y):
            self.message = "Vous ne pouvez pas aller là."
            return

        # Check for monster
        monster = None
        for m in self.dungeon.monsters:
            if m['x'] == new_x and m['y'] == new_y:
                monster = m
                break

        if monster:
            self.attack_monster(monster)
        else:
            self.player.move(dx, dy)
            self.check_items()

    def attack_monster(self, monster):
        """Attack a monster."""
        # Simple combat
        import random
        damage = random.randint(1, 6) + self.player.get_to_hit_bonus()
        monster['hp'] -= damage

        if monster['hp'] <= 0:
            self.message = f"Vous tuez le {monster['template'].name}!"
            self.dungeon.monsters.remove(monster)
            self.player.gain_experience(monster['template'].experience)
        else:
            self.message = f"Vous frappez le {monster['template'].name} ({damage} dégâts)."

            # Monster counter-attack
            monster_damage = random.randint(1, 4)
            self.player.take_damage(monster_damage)
            self.message += f" Il vous frappe ({monster_damage} dégâts)."

    def check_items(self):
        """Check for items at player position."""
        for item in self.dungeon.items[:]:
            if item['x'] == self.player.x and item['y'] == self.player.y:
                if self.player.inventory.is_full():
                    self.message = "Inventaire plein!"
                else:
                    self.player.inventory.add_item(item['template'])
                    self.dungeon.items.remove(item)
                    self.message = f"Vous ramassez: {item['template'].name}"
                break

    def try_descend(self):
        """Try to descend stairs."""
        if (self.player.x, self.player.y) == self.dungeon.stairs_down:
            self.current_level += 1
            self.new_level(self.current_level)
            self.message = f"Vous descendez au niveau {self.current_level}."
        else:
            self.message = "Il n'y a pas d'escalier ici."

    def try_ascend(self):
        """Try to ascend stairs."""
        if (self.player.x, self.player.y) == self.dungeon.stairs_up:
            if self.current_level > 1:
                self.current_level -= 1
                self.new_level(self.current_level)
                self.message = f"Vous montez au niveau {self.current_level}."
            else:
                self.message = "Vous ne pouvez pas remonter plus haut."
        else:
            self.message = "Il n'y a pas d'escalier ici."

    def show_inventory(self):
        """Show inventory screen."""
        self.screen.clear()
        self.screen.stdscr.addstr(0, 0, "=== INVENTAIRE ===")

        y = 2
        for i, item in enumerate(self.player.inventory.items):
            if item:
                label = chr(ord('a') + i)
                self.screen.stdscr.addstr(y, 0, f"{label}) {item.name}")
                y += 1

        if self.player.inventory.count_items() == 0:
            self.screen.stdscr.addstr(2, 0, "(vide)")

        self.screen.stdscr.addstr(y + 1, 0, "Appuyez sur une touche...")
        self.screen.stdscr.refresh()
        self.screen.stdscr.getch()

    def drop_item(self):
        """Drop an item (a command)."""
        self.message = "Abandonner quel objet? (a-z)"
        self.draw()
        ch = self.screen.get_key()
        if ord('a') <= ch <= ord('z'):
            idx = ch - ord('a')
            item = self.player.inventory.remove_item(idx)
            if item:
                self.message = f"Vous abandonnez {item.name}."
                # Place item on ground
                self.dungeon.items.append({
                    'template': item,
                    'x': self.player.x,
                    'y': self.player.y
                })
            else:
                self.message = "Vous n'avez rien à cet emplacement."

    def quaff_potion(self):
        """Drink a potion (b command)."""
        self.message = "Boire quelle potion? (a-z)"
        self.draw()
        ch = self.screen.get_key()
        if ord('a') <= ch <= ord('z'):
            idx = ch - ord('a')
            item = self.player.inventory.get_item(idx)
            if item and item.char == '•':
                self.player.inventory.remove_item(idx)
                self.message = f"Vous buvez {item.name}."
                # TODO: Apply potion effects
            else:
                self.message = "Ce n'est pas une potion!"

    def eat_food(self):
        """Eat food (m command)."""
        # Find food in inventory
        for idx in range(self.player.inventory.max_size):
            item = self.player.inventory.get_item(idx)
            if item and item.char == ':':
                self.player.inventory.remove_item(idx)
                self.player.restore_food(500)
                self.message = "Vous mangez. C'est délicieux!"
                return
        self.message = "Vous n'avez pas de nourriture!"

    def read_scroll(self):
        """Read a scroll (l command)."""
        self.message = "Lire quel parchemin? (a-z)"
        self.draw()
        ch = self.screen.get_key()
        if ord('a') <= ch <= ord('z'):
            idx = ch - ord('a')
            item = self.player.inventory.get_item(idx)
            if item and item.char == '?':
                self.player.inventory.remove_item(idx)
                self.message = f"Vous lisez {item.name}."
                # TODO: Apply scroll effects
            else:
                self.message = "Ce n'est pas un parchemin!"

    def wield_weapon(self):
        """Wield a weapon (w command)."""
        self.message = "Porter quelle arme? (a-z)"
        # TODO: Implement weapon selection

    def remove_weapon(self):
        """Remove weapon (W command)."""
        if self.player.equipment[0]:
            self.message = "Vous enlevez votre arme."
            self.player.unequip_item(0)
        else:
            self.message = "Vous ne portez pas d'arme."

    def wear_armor(self):
        """Wear armor (r command)."""
        self.message = "Revêtir quelle armure? (a-z)"
        # TODO: Implement armor selection

    def remove_armor(self):
        """Remove armor (R command)."""
        if self.player.equipment[2]:
            self.message = "Vous enlevez votre armure."
            self.player.unequip_item(2)
        else:
            self.message = "Vous ne portez pas d'armure."

    def show_commands(self):
        """Show command list (?)."""
        self.screen.stdscr.clear()
        help_text = [
            "═══ COMMANDES ═══",
            "",
            "Déplacement: 2,4,6,8 (pavé numérique)",
            "Diagonales: 7,9,1,3",
            "",
            "i : Inventaire           a : Abandonner objet",
            "b : Boire potion         m : Manger",
            "l : Lire parchemin       w : Porter arme",
            "W : Enlever arme         r : Revêtir armure",
            "R : Enlever armure       > : Descendre",
            "< : Monter               ? : Aide",
            "",
            "Appuyez sur ESPACE..."
        ]
        for i, line in enumerate(help_text):
            try:
                self.screen.stdscr.addstr(i, 0, line)
            except:
                pass
        self.screen.stdscr.refresh()
        while self.screen.stdscr.getch() != ord(' '):
            pass
