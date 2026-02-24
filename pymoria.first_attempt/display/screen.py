"""
Terminal display manager using curses.
Handles CP437-like box drawing characters in Linux terminal.
"""

import curses
from typing import Optional, Tuple


class Screen:
    """Terminal screen manager."""

    def __init__(self):
        self.stdscr = None
        self.height = 0
        self.width = 0
        self.message_window = None
        self.status_window = None
        self.map_window = None

    def initialize(self):
        """Initialize curses display."""
        self.stdscr = curses.initscr()
        curses.noecho()
        curses.cbreak()
        curses.curs_set(0)  # Hide cursor
        self.stdscr.keypad(True)
        self.stdscr.nodelay(False)

        # Ensure stdscr uses full terminal
        self.stdscr.scrollok(False)  # Disable scrolling
        self.stdscr.idlok(False)     # Disable insert/delete line
        self.stdscr.leaveok(False)   # Update cursor position

        # Initialize colors if available
        if curses.has_colors():
            curses.start_color()
            curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_BLACK)   # Normal
            curses.init_pair(2, curses.COLOR_YELLOW, curses.COLOR_BLACK)  # Player
            curses.init_pair(3, curses.COLOR_RED, curses.COLOR_BLACK)     # Monster
            curses.init_pair(4, curses.COLOR_CYAN, curses.COLOR_BLACK)    # Item
            curses.init_pair(5, curses.COLOR_MAGENTA, curses.COLOR_BLACK) # Warning
            curses.init_pair(6, curses.COLOR_GREEN, curses.COLOR_BLACK)   # Status
            # Use a valid color for dimmed - blue is dark/subtle
            curses.init_pair(7, curses.COLOR_BLUE, curses.COLOR_BLACK)    # Dimmed (discovered but not visible)

        self.height, self.width = self.stdscr.getmaxyx()

        # Create windows
        self._create_windows()

    def _create_windows(self):
        """Create sub-windows for different UI areas."""
        # Map area is drawn directly to stdscr (no subwindow needed)
        map_height = self.height - 4

        # Status window (1 line below map)
        self.status_window = curses.newwin(1, self.width, map_height, 0)

        # Message window (2 lines at bottom)
        self.message_window = curses.newwin(2, self.width, map_height + 1, 0)

    def cleanup(self):
        """Cleanup curses display."""
        if self.stdscr:
            curses.nocbreak()
            self.stdscr.keypad(False)
            curses.echo()
            curses.curs_set(1)
            curses.endwin()

    def clear(self):
        """Clear screen."""
        if self.stdscr:
            self.stdscr.clear()

    def refresh(self):
        """Refresh display."""
        if self.stdscr:
            self.stdscr.refresh()
        if self.status_window:
            self.status_window.refresh()
        if self.message_window:
            self.message_window.refresh()

    def draw_map(self, dungeon, player, visible_tiles: set = None):
        """Draw dungeon map with fog of war and line-of-sight."""
        if not self.stdscr:
            return

        # Clear the entire stdscr before drawing
        self.stdscr.erase()

        # Get currently visible tiles (with line-of-sight)
        if visible_tiles is None:
            visible_tiles = dungeon.compute_fov(player.x, player.y, radius=8)

        # Draw directly to stdscr to avoid window offset issues
        map_height = self.height - 4  # Leave room for status/message

        # Draw the dungeon starting from terminal (0,0)
        for world_y in range(min(map_height, dungeon.height)):
            for world_x in range(min(self.width, dungeon.width)):
                # Check if tile has been discovered
                if not dungeon.discovered[world_y][world_x]:
                    self._put_char(world_x, world_y, ' ', 1)  # Undiscovered = blank
                    continue

                # Check if currently visible
                is_visible = (world_x, world_y) in visible_tiles

                # Draw player
                if world_x == player.x and world_y == player.y:
                    self._put_char(world_x, world_y, player.char, 2)
                    continue

                # Only show monsters/items if currently visible
                if is_visible:
                    # Check for monsters
                    monster_here = None
                    for monster in dungeon.monsters:
                        if monster['x'] == world_x and monster['y'] == world_y:
                            monster_here = monster
                            break

                    if monster_here:
                        char = monster_here['template'].char
                        # Hallucination shows wrong characters
                        if player.status.is_hallucinating:
                            import random
                            char = random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
                        self._put_char(world_x, world_y, char, 3)
                        continue

                    # Check for items
                    item_here = None
                    for item in dungeon.items:
                        if item['x'] == world_x and item['y'] == world_y:
                            item_here = item
                            break

                    if item_here:
                        self._put_char(world_x, world_y, item_here['template'].char, 4)
                        continue

                # Draw terrain
                char = dungeon.get_char_at(world_x, world_y)
                if player.status.is_blind:
                    char = ' '  # Can't see anything

                # If discovered but not currently visible, show dimmed (terrain only)
                color = 1 if is_visible else 7  # Color 7 for dimmed
                self._put_char(world_x, world_y, char, color)

    def _put_char(self, x: int, y: int, char: str, color: int):
        """Put character at position with color - draw directly to stdscr."""
        if self.stdscr:
            try:
                self.stdscr.addstr(y, x, char, curses.color_pair(color))
            except curses.error:
                pass  # Ignore errors at screen edges

    def draw_status(self, status_text: str):
        """Draw status line."""
        if not self.status_window:
            return

        self.status_window.clear()
        try:
            self.status_window.addstr(0, 0, status_text[:self.width-1],
                                     curses.color_pair(6))
        except curses.error:
            pass

    def draw_message(self, message: str):
        """Draw message at bottom."""
        if not self.message_window:
            return

        try:
            self.message_window.addstr(0, 0, message[:self.width-1],
                                      curses.color_pair(1))
        except curses.error:
            pass

    def draw_help(self):
        """Draw help screen."""
        self.clear()
        help_text = [
            "=== MORIA - AIDE ===",
            "",
            "Déplacement (pavé numérique):",
            "  8 : Haut        2 : Bas",
            "  4 : Gauche      6 : Droite",
            "",
            "Actions:",
            "  i : Inventaire",
            "  a : Abandonner un objet",
            "  b : Boire une potion",
            "  m : Manger de la nourriture",
            "  l : Lire un parchemin",
            "  w : Porter/Brandir une arme",
            "  W : Enlever une arme",
            "  r : Revêtir une armure",
            "  R : Enlever une armure",
            "  > : Descendre un escalier",
            "  < : Monter un escalier",
            "",
            "Appuyez sur une touche pour continuer..."
        ]

        for i, line in enumerate(help_text):
            try:
                self.stdscr.addstr(i, 2, line)
            except curses.error:
                pass

        self.stdscr.refresh()
        self.stdscr.getch()

    def get_key(self) -> int:
        """Get key press."""
        if self.stdscr:
            return self.stdscr.getch()
        return -1

    def prompt_string(self, prompt: str) -> str:
        """Prompt for string input."""
        if not self.message_window:
            return ""

        curses.echo()
        curses.curs_set(1)

        self.message_window.clear()
        self.message_window.addstr(0, 0, prompt)
        self.message_window.refresh()

        result = self.message_window.getstr(0, len(prompt), 20).decode('utf-8')

        curses.noecho()
        curses.curs_set(0)

        return result

    def prompt_char(self, prompt: str) -> str:
        """Prompt for single character."""
        self.draw_message(prompt)
        self.message_window.refresh()
        ch = self.get_key()
        return chr(ch) if 0 <= ch < 256 else ''
