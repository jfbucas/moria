"""
Display System for PyMoria using curses
Based on reverse/DISPLAY_SYSTEM.md
Standard DOS 80×25 terminal layout
"""

import curses
from typing import Optional, Tuple
import sys


# Screen layout constants
SCREEN_WIDTH = 80
SCREEN_HEIGHT = 25
MAP_WIDTH = 79
MAP_HEIGHT = 20
MESSAGE_ROW = 23
STATUS_ROW = 24

# Color pair indices
COLOR_NORMAL = 1        # White on black (normal tiles)
COLOR_PLAYER = 2        # Bright white on black (player)
COLOR_MONSTER = 3       # Red on black (monsters)
COLOR_ITEM = 4          # Yellow on black (items)
COLOR_WALL = 5          # Gray on black (walls)
COLOR_EXPLORED = 6      # Green on black (explored but not visible)
COLOR_STATUS = 7        # Cyan on black (status bar)


class Screen:
    """
    Curses-based display manager for PyMoria
    Handles all screen rendering in 80×25 DOS-style layout
    """

    def __init__(self):
        """Initialize curses screen"""
        self.stdscr = None
        self.color_enabled = False
        self.last_message = ""

    def initialize(self):
        """
        Initialize curses display
        Called once at game start
        """
        self.stdscr = curses.initscr()
        curses.noecho()
        curses.cbreak()
        self.stdscr.keypad(True)
        curses.curs_set(0)  # Hide cursor

        # Verify terminal is large enough (need 25 rows × 80 cols)
        rows, cols = self.stdscr.getmaxyx()
        if rows < SCREEN_HEIGHT or cols < SCREEN_WIDTH:
            curses.endwin()
            print(f"Terminal trop petit: {cols}×{rows}. Minimum requis: {SCREEN_WIDTH}×{SCREEN_HEIGHT}.")
            print(f"Agrandissez votre terminal et relancez le jeu.")
            raise SystemExit(1)

        # Initialize colors if available
        if curses.has_colors():
            curses.start_color()
            curses.use_default_colors()

            # Define color pairs
            curses.init_pair(COLOR_NORMAL, curses.COLOR_WHITE, curses.COLOR_BLACK)
            curses.init_pair(COLOR_PLAYER, curses.COLOR_WHITE, curses.COLOR_BLACK)
            curses.init_pair(COLOR_MONSTER, curses.COLOR_RED, curses.COLOR_BLACK)
            curses.init_pair(COLOR_ITEM, curses.COLOR_YELLOW, curses.COLOR_BLACK)
            curses.init_pair(COLOR_WALL, curses.COLOR_WHITE, curses.COLOR_BLACK)
            curses.init_pair(COLOR_EXPLORED, curses.COLOR_GREEN, curses.COLOR_BLACK)
            curses.init_pair(COLOR_STATUS, curses.COLOR_CYAN, curses.COLOR_BLACK)

            self.color_enabled = True

        # Clear screen
        self.clear_screen()
        self.stdscr.refresh()

    def shutdown(self):
        """
        Restore terminal to normal state
        Called on game exit
        """
        if self.stdscr:
            curses.nocbreak()
            self.stdscr.keypad(False)
            curses.echo()
            curses.endwin()

    def clear_screen(self):
        """Clear the entire screen"""
        if self.stdscr:
            self.stdscr.clear()
            self.stdscr.refresh()

    def put_char_at(self, char: str, col: int, row: int, color: int = COLOR_NORMAL):
        """
        Place a character at screen position (col, row)
        Reference: DISPLAY_SYSTEM.md Section 2 (put_char_at_pos)

        Args:
            char: Character to display (1 char or Unicode)
            col: Column (0-78 for map, 0-79 for full screen)
            row: Row (0-19 for map, 0-24 for full screen)
            color: Color pair index
        """
        if not self.stdscr:
            return

        # Bounds check
        if row < 0 or row >= SCREEN_HEIGHT:
            return
        if col < 0 or col >= SCREEN_WIDTH:
            return

        try:
            if self.color_enabled:
                self.stdscr.addstr(row, col, char, curses.color_pair(color))
            else:
                self.stdscr.addstr(row, col, char)
        except curses.error:
            # Ignore errors at bottom-right corner (curses limitation)
            pass

    def draw_dungeon(self, level, player, monsters=None, items=None):
        """
        Render the dungeon level (20×79 map area)
        Reference: DISPLAY_SYSTEM.md Section 7 (redraw_dungeon_level)

        Args:
            level: DungeonLevel object with tiles
            player: Player object with position
            monsters: List of Monster objects (optional)
            items: List of Item objects on floor (optional)
        """
        if not self.stdscr:
            return

        # Draw all tiles (rows 0-19, cols 0-78)
        # get_tile(x, y) = get_tile(col, row) per DungeonLevel convention
        for row in range(MAP_HEIGHT):
            for col in range(MAP_WIDTH):
                tile = level.get_tile(col, row)

                # Determine color based on tile type
                if tile in ['#', '┴', '┬', '┤', '├', '─', '│', '+']:
                    color = COLOR_WALL
                else:
                    color = COLOR_NORMAL

                # Draw the tile
                if tile and tile != ' ':
                    self.put_char_at(tile, col, row, color)
                else:
                    self.put_char_at(' ', col, row, COLOR_NORMAL)

        # Draw items on floor (if provided)
        if items:
            for item in items:
                if hasattr(item, 'row') and hasattr(item, 'col'):
                    if item.row is not None and item.col is not None:
                        # Item display character based on type
                        item_chars = {
                            0: '$',  # Gold
                            1: ':',  # Food
                            2: '•',  # Potion (using bullet instead of inverted !)
                            3: '?',  # Scroll
                            4: '=',  # Ring
                            5: '/',  # Wand
                            6: '⌂',  # Armor (CP437 house symbol, fallback to [ if not supported)
                            7: ')',  # Weapon
                            8: '*',  # Light source
                        }
                        char = item_chars.get(item.type, '?')
                        try:
                            self.put_char_at(char, item.col, item.row, COLOR_ITEM)
                        except:
                            # Fallback for unsupported Unicode
                            self.put_char_at('?', item.col, item.row, COLOR_ITEM)

        # Draw monsters (if provided)
        if monsters:
            for monster in monsters:
                if hasattr(monster, 'row') and hasattr(monster, 'col'):
                    if monster.row is not None and monster.col is not None:
                        if not monster.is_invisible:
                            self.put_char_at(monster.char, monster.col, monster.row, COLOR_MONSTER)

        # Draw player at their position
        player_char = '☻'  # CP437 0x02 - smiling face
        try:
            self.put_char_at(player_char, player.x, player.y, COLOR_PLAYER | curses.A_BOLD)
        except:
            # Fallback if ☻ not supported
            self.put_char_at('@', player.x, player.y, COLOR_PLAYER | curses.A_BOLD)

        self.stdscr.refresh()

    def draw_status_bar(self, player):
        """
        Draw status bar at row 24
        Reference: DISPLAY_SYSTEM.md Section 9 (display_character_stats)

        Format (French labels):
        Niv NN Or NNNNNN   PVNNNN/NNN   IntNNN   DexNNN   ForNNN   CA +N   Exp NN/NNNN

        Note from original: Labels are Int/Dex/For but values are intelligence/strength/food
        """
        if not self.stdscr:
            return

        # Clear status row
        try:
            self.stdscr.move(STATUS_ROW, 0)
            self.stdscr.clrtoeol()
        except curses.error:
            return  # Terminal too small — skip status bar

        # Build status bar string
        status_parts = []

        # Niv (dungeon level) - assume level 1 for now if no dungeon_level attr
        dungeon_level = getattr(player, 'dungeon_level', 1)
        status_parts.append(f"Niv {dungeon_level:2d}")

        # Or (gold)
        gold = player.get_total_gold()
        status_parts.append(f" Or {gold:6d}")

        # PV (Hit Points)
        status_parts.append(f"   PV{player.current_hp:4d}/{player.max_hp:3d}")

        # Int (Intelligence)
        status_parts.append(f"   Int{player.intelligence:3d}")

        # Dex (displays strength - mislabeled in original!)
        status_parts.append(f"   Dex{player.strength:3d}")

        # For (displays food - mislabeled in original!)
        status_parts.append(f"   For{player.food_level:3d}")

        # CA (Armor Class) - assume base_ac attribute
        base_ac = getattr(player, 'base_ac', 0)
        if base_ac < 1:
            status_parts.append(f"   CA {base_ac:1d}")
        else:
            status_parts.append(f"   CA +{base_ac:1d}")

        # Exp (Level / Experience)
        status_parts.append(f"   Exp {player.player_level:2d}/{player.experience:4d}")

        status_text = ''.join(status_parts)

        # Draw status bar
        try:
            if self.color_enabled:
                self.stdscr.addstr(STATUS_ROW, 0, status_text, curses.color_pair(COLOR_STATUS))
            else:
                self.stdscr.addstr(STATUS_ROW, 0, status_text)
        except curses.error:
            pass

        self.stdscr.refresh()

    def draw_message(self, text: str, wait_for_key: bool = False):
        """
        Display message at row 23 (message area)
        Reference: DISPLAY_SYSTEM.md Section 1

        Args:
            text: Message text to display
            wait_for_key: If True, show "-- Plus --" and wait for keypress
        """
        if not self.stdscr:
            return

        # Clear message row
        try:
            self.stdscr.move(MESSAGE_ROW, 0)
            self.stdscr.clrtoeol()
        except curses.error:
            return

        # Truncate message if too long
        max_len = SCREEN_WIDTH - 12 if wait_for_key else SCREEN_WIDTH - 1
        if len(text) > max_len:
            text = text[:max_len]

        # Draw message
        try:
            self.stdscr.addstr(MESSAGE_ROW, 0, text)
        except curses.error:
            pass

        # Add "-- Plus --" prompt if waiting
        if wait_for_key:
            prompt = "-- Plus --"
            self.stdscr.addstr(MESSAGE_ROW, SCREEN_WIDTH - len(prompt) - 1, prompt)
            self.stdscr.refresh()
            self.stdscr.getch()  # Wait for key
            # Clear message after keypress
            self.stdscr.move(MESSAGE_ROW, 0)
            self.stdscr.clrtoeol()

        self.last_message = text
        self.stdscr.refresh()

    def clear_message(self):
        """Clear the message area"""
        if self.stdscr:
            self.stdscr.move(MESSAGE_ROW, 0)
            self.stdscr.clrtoeol()
            self.stdscr.refresh()
            self.last_message = ""

    def get_key(self) -> str:
        """
        Get a single keypress from user
        Returns: Character as string, or special key name
        """
        if not self.stdscr:
            return ''

        key = self.stdscr.getch()

        # Map special keys
        if key == curses.KEY_UP or key == ord('8'):
            return 'UP'
        elif key == curses.KEY_DOWN or key == ord('2'):
            return 'DOWN'
        elif key == curses.KEY_LEFT or key == ord('4'):
            return 'LEFT'
        elif key == curses.KEY_RIGHT or key == ord('6'):
            return 'RIGHT'
        elif key == 27:  # ESC
            return 'ESC'
        elif key >= 0 and key < 256:
            return chr(key)
        else:
            return ''

    def show_menu(self, title: str, options: list, start_row: int = 5) -> Optional[int]:
        """
        Display a menu and return selected option index

        Args:
            title: Menu title
            options: List of menu option strings
            start_row: Starting row for menu display

        Returns:
            Selected option index (0-based), or None if cancelled
        """
        if not self.stdscr:
            return None

        selected = 0

        while True:
            # Clear area
            for i in range(len(options) + 3):
                self.stdscr.move(start_row + i, 0)
                self.stdscr.clrtoeol()

            # Draw title
            title_col = (SCREEN_WIDTH - len(title)) // 2
            self.stdscr.addstr(start_row, title_col, title, curses.A_BOLD)

            # Draw options
            for i, option in enumerate(options):
                row = start_row + i + 2
                if i == selected:
                    # Highlight selected option
                    self.stdscr.addstr(row, 10, f"> {option}", curses.A_REVERSE)
                else:
                    self.stdscr.addstr(row, 10, f"  {option}")

            self.stdscr.refresh()

            # Get input
            key = self.get_key()

            if key == 'UP' and selected > 0:
                selected -= 1
            elif key == 'DOWN' and selected < len(options) - 1:
                selected += 1
            elif key == '\n' or key == ' ':
                return selected
            elif key == 'ESC' or key == 'q':
                return None

    def draw_box(self, top: int, left: int, height: int, width: int):
        """
        Draw a box with Unicode box-drawing characters
        Reference: DISPLAY_SYSTEM.md Section 11 (draw_game_hud)
        """
        if not self.stdscr:
            return

        # Box characters (Unicode)
        tl = '╔'  # Top-left
        tr = '╗'  # Top-right
        bl = '╚'  # Bottom-left
        br = '╝'  # Bottom-right
        h = '═'   # Horizontal
        v = '║'   # Vertical

        try:
            # Top border
            self.stdscr.addstr(top, left, tl + h * (width - 2) + tr)

            # Sides
            for i in range(1, height - 1):
                self.stdscr.addstr(top + i, left, v)
                self.stdscr.addstr(top + i, left + width - 1, v)

            # Bottom border
            self.stdscr.addstr(top + height - 1, left, bl + h * (width - 2) + br)

        except:
            # Fallback to ASCII if Unicode not supported
            self.stdscr.addstr(top, left, '+' + '-' * (width - 2) + '+')
            for i in range(1, height - 1):
                self.stdscr.addstr(top + i, left, '|')
                self.stdscr.addstr(top + i, left + width - 1, '|')
            self.stdscr.addstr(top + height - 1, left, '+' + '-' * (width - 2) + '+')

        self.stdscr.refresh()


# Global screen instance
_screen_instance: Optional[Screen] = None


def get_screen() -> Screen:
    """Get the global screen instance"""
    global _screen_instance
    if _screen_instance is None:
        _screen_instance = Screen()
    return _screen_instance


def initialize_screen() -> Screen:
    """Initialize and return the screen"""
    screen = get_screen()
    screen.initialize()
    return screen


def shutdown_screen():
    """Shutdown the screen"""
    global _screen_instance
    if _screen_instance:
        _screen_instance.shutdown()
        _screen_instance = None
