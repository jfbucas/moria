"""
Main game engine.
"""

import sys
import curses
from typing import Optional
from game.player import Player
from game.dungeon import Dungeon
from display.screen import Screen
from data.potions import get_potion_by_effect, initialize_potion_colors
from data.items import initialize_wand_names
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
                self.running = False
                return
            elif choice == 'new':
                self.player = menu.create_character()

            # Randomize potion colors and wand wood names for this game session
            initialize_potion_colors()
            initialize_wand_names()

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
            # Eye of Sauron never moves (speed=0)
            if monster['template'].speed == 0:
                # Still attacks if player is adjacent
                dx_abs = abs(monster['x'] - self.player.x)
                dy_abs = abs(monster['y'] - self.player.y)
                if dx_abs + dy_abs == 1:
                    self.monster_attack_player(monster)
                continue

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
        self.screen.draw_status(self.player.get_status_string(self.current_level))
        if self.message:
            self.screen.draw_message(self.message)
        self.screen.refresh()

    def handle_input(self):
        """Handle player input."""
        key = self.screen.get_key()

        if not self.player.can_act():
            self.message = "Vous ne pouvez pas agir!"
            return

        # Movement (numpad + arrow keys, no diagonals - matching original MORIA)
        if key == ord('4') or key == curses.KEY_LEFT:  # Left
            self.try_move(-1, 0)
        elif key == ord('6') or key == curses.KEY_RIGHT:  # Right
            self.try_move(1, 0)
        elif key == ord('8') or key == curses.KEY_UP:  # Up
            self.try_move(0, -1)
        elif key == ord('2') or key == curses.KEY_DOWN:  # Down
            self.try_move(0, 1)

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
        elif key == ord('L'):  # Lancer un sort (use wand)
            self.cast_spell()
        elif key == ord('.'):  # Rester sur place
            pass  # Skip turn
        elif key == ord('>'):  # Descendre escalier
            self.try_descend()
        elif key == ord('<'):  # Monter escalier
            self.try_ascend()
        elif key == ord('c'):  # Fiche de personage
            self.show_character_sheet()
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
        """Show command list (?). Matches original FUN_1000_6249 messages 0x134-0x146."""
        # Page 1: messages 0x134-0x13D
        page1 = [
            "a    abandonner un objet",
            "b    boire une potion                       l    lire un parchemin",
            "B    brandir une arme                       i,*  faire l'inventaire",
            "e    enlever une armure                     r    revêtir une armure",
            "E    enfiler un anneau                      N    eNlever un anneau",
            "m    manger quelque chose",
            "R    renommer un objet",
            "c    fiche de personage",
            "?    liste des commandes                    s    table des scores",
            "L    lancer un sort                         T    lancer un objet",
        ]
        # Page 2: messages 0x13E-0x143
        page2 = [
            ">    monter                                 <    descendre",
            "2 \u25bc  mouvement vers le bas de l'\u00e9cran",
            "4 \u25ba  mouvement vers la gauche de l'\u00e9cran",
            "6 \u25c4  mouvement vers la droite de l'\u00e9cran",
            "8 \u25b2  mouvement vers le haut de l'\u00e9cran",
            ".    rester sur place",
        ]
        # Page 3: messages 0x144-0x146
        page3 = [
            "^G    couper/retablir le son                 ^T   tableau de chasse",
            "^S    se suicider                            ^F   abandonner la partie",
            "^P    raffraichir l'\u00e9cran                    ^H   help...",
        ]
        for page in [page1, page2, page3]:
            self.screen.stdscr.clear()
            for i, line in enumerate(page):
                try:
                    self.screen.stdscr.addstr(i, 0, line)
                except curses.error:
                    pass
            try:
                self.screen.stdscr.addstr(len(page) + 1, 0, "Appuyez sur ESPACE...")
            except curses.error:
                pass
            self.screen.stdscr.refresh()
            while self.screen.stdscr.getch() != ord(' '):
                pass
        self.screen.stdscr.clear()

    def cast_spell(self):
        """Cast a spell using a wand (L command).
        Original: use_item_from_inventory with param_2=0x4c.
        Message 0x9e: 'Avec quelle baguette ?'"""
        from utils.constants import ItemType
        import random

        # Find wands in inventory
        wand_indices = []
        for idx in range(self.player.inventory.max_size):
            item = self.player.inventory.get_item(idx)
            if item and item.type == ItemType.WAND:
                wand_indices.append(idx)

        if not wand_indices:
            self.message = "Vous n'avez pas de baguette!"
            return

        # Show prompt (message 0x9e from original)
        self.message = "Avec quelle baguette ? (a-z)"
        self.draw()
        ch = self.screen.get_key()
        if not (ord('a') <= ch <= ord('z')):
            self.message = ""
            return

        idx = ch - ord('a')
        item = self.player.inventory.get_item(idx)
        if not item or item.type != ItemType.WAND:
            self.message = "Ce n'est pas une baguette!"
            return

        # Apply wand effect based on the english effect name stored in damage field
        effect = item.damage

        if effect in ("teleport", "transmorph", "slow_monster", "haste_monster",
                       "weaken", "fear", "combat", "sleep", "paralyze",
                       "illusion", "energy_drain"):
            self._wand_direction_effect(effect)
        elif effect == "destruction":
            self._effect_destruction()
            self.message = "La zone est d\u00e9vast\u00e9e!"
        elif effect == "create_wall":
            self._wand_create_wall()
        elif effect == "dowsing":
            self._effect_dowsing()
            self.message = "Vous d\u00e9tectez des objets!"
        elif effect == "summon_monster":
            self._effect_summon_monster()
            self.message = "Un monstre appara\u00eet!"
        elif effect == "create_item":
            self._effect_create_item()
            self.message = "Un objet appara\u00eet!"
        elif effect == "fill_traps":
            self.message = "Les trappes sont combl\u00e9es!"
        elif effect == "invisibility":
            self.message = "Vous devenez invisible!"
        elif effect == "create_traps":
            self.message = "Des trappes apparaissent!"
        elif effect == "reinforce":
            self.message = "Vous vous sentez renforc\u00e9!"
        elif effect == "capricious":
            self.message = "La baguette fait un effet al\u00e9atoire!"
        elif effect == "purify":
            self.message = "La zone est purifi\u00e9e!"
        else:
            self.message = "La baguette n'a aucun effet."

    def _wand_direction_effect(self, effect):
        """Ask direction and apply wand effect to first monster in line.
        Message 0x9f: 'Dans quelle direction ?'"""
        import random
        self.message = "Dans quelle direction ? (2/4/6/8)"
        self.draw()
        ch = self.screen.get_key()

        dx, dy = 0, 0
        if ch == ord('4') or ch == curses.KEY_LEFT:
            dx = -1
        elif ch == ord('6') or ch == curses.KEY_RIGHT:
            dx = 1
        elif ch == ord('8') or ch == curses.KEY_UP:
            dy = -1
        elif ch == ord('2') or ch == curses.KEY_DOWN:
            dy = 1
        else:
            self.message = ""
            return

        # Find first monster in that direction (max range 10)
        x, y = self.player.x + dx, self.player.y + dy
        target = None
        for _ in range(10):
            if not (0 <= x < self.dungeon.width and 0 <= y < self.dungeon.height):
                break
            if not self.dungeon.is_walkable(x, y):
                break
            for m in self.dungeon.monsters:
                if m['x'] == x and m['y'] == y:
                    target = m
                    break
            if target:
                break
            x += dx
            y += dy

        if not target:
            self.message = "Rien dans cette direction."
            return

        # Apply effect to target monster
        if effect == "teleport":
            for _ in range(100):
                nx = random.randint(1, self.dungeon.width - 2)
                ny = random.randint(1, self.dungeon.height - 2)
                if self.dungeon.is_walkable(nx, ny) and not self.dungeon.has_monster(nx, ny):
                    target['x'] = nx
                    target['y'] = ny
                    break
            self.message = f"Le {target['template'].name} dispara\u00eet!"
        elif effect == "transmorph":
            from data.monsters import get_monster_by_level
            new_t = get_monster_by_level(self.current_level)
            target['template'] = new_t
            target['hp'] = new_t.hp
            self.message = f"Le monstre se transforme en {new_t.name}!"
        elif effect == "slow_monster":
            self.message = f"Le {target['template'].name} ralentit!"
        elif effect == "haste_monster":
            self.message = f"Le {target['template'].name} acc\u00e9l\u00e8re!"
        elif effect == "weaken":
            damage = random.randint(5, 15)
            target['hp'] -= damage
            if target['hp'] <= 0:
                self.message = f"Le {target['template'].name} est d\u00e9truit!"
                self.dungeon.monsters.remove(target)
                self.player.gain_experience(target['template'].experience)
            else:
                self.message = f"Le {target['template'].name} s'affaiblit! ({damage} d\u00e9g\u00e2ts)"
        elif effect == "fear":
            self.message = f"Le {target['template'].name} prend peur!"
        elif effect == "combat":
            damage = random.randint(10, 25)
            target['hp'] -= damage
            if target['hp'] <= 0:
                self.message = f"Le {target['template'].name} est d\u00e9truit!"
                self.dungeon.monsters.remove(target)
                self.player.gain_experience(target['template'].experience)
            else:
                self.message = f"Le {target['template'].name} est frapp\u00e9! ({damage} d\u00e9g\u00e2ts)"
        elif effect == "sleep":
            self.message = f"Le {target['template'].name} s'endort!"
        elif effect == "paralyze":
            self.message = f"Le {target['template'].name} est paralys\u00e9!"
        elif effect == "illusion":
            self.message = f"Le {target['template'].name} est aveugl\u00e9!"
        elif effect == "energy_drain":
            damage = random.randint(8, 20)
            target['hp'] -= damage
            self.player.heal(damage // 2)
            if target['hp'] <= 0:
                self.message = f"Le {target['template'].name} est d\u00e9truit!"
                self.dungeon.monsters.remove(target)
                self.player.gain_experience(target['template'].experience)
            else:
                self.message = f"L'\u00e9nergie du {target['template'].name} est absorb\u00e9e!"

    def _effect_destruction(self):
        """Destroy walls and monsters around player (baguette de destruction)."""
        px, py = self.player.x, self.player.y
        for dy in range(-2, 3):
            for dx in range(-2, 3):
                x, y = px + dx, py + dy
                if 1 <= x < self.dungeon.width - 1 and 1 <= y < self.dungeon.height - 1:
                    if (x, y) != (px, py):
                        self.dungeon.map[y][x] = ' '
        for m in self.dungeon.monsters[:]:
            if abs(m['x'] - px) <= 2 and abs(m['y'] - py) <= 2:
                self.player.gain_experience(m['template'].experience)
                self.dungeon.monsters.remove(m)

    def _wand_create_wall(self):
        """Create a wall in a direction (baguette pour cr\u00e9er des murs)."""
        self.message = "Dans quelle direction ? (2/4/6/8)"
        self.draw()
        ch = self.screen.get_key()
        dx, dy = 0, 0
        if ch == ord('4') or ch == curses.KEY_LEFT:
            dx = -1
        elif ch == ord('6') or ch == curses.KEY_RIGHT:
            dx = 1
        elif ch == ord('8') or ch == curses.KEY_UP:
            dy = -1
        elif ch == ord('2') or ch == curses.KEY_DOWN:
            dy = 1
        else:
            self.message = ""
            return
        x, y = self.player.x + dx, self.player.y + dy
        if 1 <= x < self.dungeon.width - 1 and 1 <= y < self.dungeon.height - 1:
            if self.dungeon.map[y][x] == ' ':
                self.dungeon.map[y][x] = '\u253c'
                self.message = "Un mur appara\u00eet!"
            else:
                self.message = "Il y a d\u00e9j\u00e0 quelque chose ici."
        else:
            self.message = ""

    def _effect_dowsing(self):
        """Detect objects on the level (baguette de sourcier)."""
        for item in self.dungeon.items:
            self.dungeon.discovered[item['y']][item['x']] = True

    def _effect_summon_monster(self):
        """Summon a monster near the player."""
        from data.monsters import get_monster_by_level
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            x, y = self.player.x + dx, self.player.y + dy
            if self.dungeon.is_walkable(x, y) and not self.dungeon.has_monster(x, y):
                monster = get_monster_by_level(self.current_level)
                self.dungeon.monsters.append({
                    'template': monster, 'x': x, 'y': y, 'hp': monster.hp
                })
                return

    def _effect_create_item(self):
        """Create a random item near the player."""
        from data.items import get_random_item
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            x, y = self.player.x + dx, self.player.y + dy
            if self.dungeon.is_walkable(x, y):
                item = get_random_item(self.current_level)
                self.dungeon.items.append({'template': item, 'x': x, 'y': y})
                return

    def show_character_sheet(self):
        """Show character info (c command - fiche de personage)."""
        self.screen.stdscr.clear()
        lines = [
            f"=== {self.player.name} ===",
            "",
            f"Niveau   : {self.player.level}",
            f"PV       : {self.player.current_hp}/{self.player.max_hp}",
            f"Force    : {self.player.stats.strength}",
            f"Dext\u00e9rit\u00e9: {self.player.stats.dexterity}",
            f"Intellig.: {self.player.stats.intelligence}",
            f"CA       : {self.player.base_ac}",
            f"Or       : {self.player.gold}",
            f"Exp      : {self.player.experience}",
            f"\u00c9tage    : {self.current_level}",
            "",
            "Appuyez sur une touche...",
        ]
        for i, line in enumerate(lines):
            try:
                self.screen.stdscr.addstr(i, 0, line)
            except curses.error:
                pass
        self.screen.stdscr.refresh()
        self.screen.stdscr.getch()
