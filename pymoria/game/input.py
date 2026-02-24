"""
Input Handling for PyMoria
Keyboard input, command mapping, direction prompts
Based on reverse/SHOP_AND_UI.md
"""

from typing import Tuple, Optional
from utils.constants import *
from data.messages import MSG_WHICH_DIRECTION


class InputHandler:
    """
    Handles all keyboard input for the game
    Maps keys to commands, handles direction input
    """

    def __init__(self, screen=None):
        """
        Initialize input handler

        Args:
            screen: Screen object for getting keys and displaying prompts
        """
        self.screen = screen
        self.last_key = ''

    def read_key(self) -> str:
        """
        Read a single keypress and return normalized command

        Returns:
            Command string or character
        """
        if not self.screen:
            return ''

        key = self.screen.get_key()
        self.last_key = key

        # Normalize movement keys
        # Arrow keys already mapped to UP/DOWN/LEFT/RIGHT by screen.get_key()
        if key == 'UP':
            return CMD_MOVE_UP
        elif key == 'DOWN':
            return CMD_MOVE_DOWN
        elif key == 'LEFT':
            return CMD_MOVE_LEFT
        elif key == 'RIGHT':
            return CMD_MOVE_RIGHT

        # Return the key as-is for other commands
        return key

    def get_command(self) -> Optional[str]:
        """
        Get a command from user
        Returns the command character or None

        This is a convenience wrapper around read_key()
        """
        return self.read_key()

    def get_direction(self, prompt: str = None) -> Optional[Tuple[int, int]]:
        """
        Prompt for direction and return (dx, dy) tuple
        NO diagonals - only 4 cardinal directions allowed

        Args:
            prompt: Optional custom prompt (defaults to French "Quelle direction?")

        Returns:
            (dx, dy) tuple or None if cancelled
            Valid returns: (0, -1), (0, 1), (-1, 0), (1, 0)
        """
        if not self.screen:
            return None

        # Display prompt
        if prompt is None:
            prompt = MSG_WHICH_DIRECTION

        self.screen.draw_message(prompt)

        # Get direction key
        key = self.read_key()

        # Map to direction tuple (dx, dy)
        # NO DIAGONALS - only 4 directions
        direction_map = {
            '8': (0, -1),      # North (up)
            CMD_MOVE_UP: (0, -1),
            '2': (0, 1),       # South (down)
            CMD_MOVE_DOWN: (0, 1),
            '4': (-1, 0),      # West (left)
            CMD_MOVE_LEFT: (-1, 0),
            '6': (1, 0),       # East (right)
            CMD_MOVE_RIGHT: (1, 0),
        }

        direction = direction_map.get(key)

        # Clear the prompt
        self.screen.clear_message()

        return direction

    def wait_for_keypress(self, message: str = None) -> str:
        """
        Display message and wait for any keypress

        Args:
            message: Optional message to display

        Returns:
            The key that was pressed
        """
        if message and self.screen:
            self.screen.draw_message(message, wait_for_key=True)
            return self.last_key
        elif self.screen:
            return self.screen.get_key()
        return ''

    def confirm_yes_no(self, question: str) -> bool:
        """
        Ask a yes/no question in French

        Args:
            question: Question to ask

        Returns:
            True if 'o' (oui) or 'O', False otherwise
        """
        if not self.screen:
            return False

        self.screen.draw_message(question)
        key = self.read_key()
        self.screen.clear_message()

        return key in ['o', 'O']  # 'o' = "oui" (yes in French)

    def get_number_input(self, prompt: str, min_val: int = 0, max_val: int = 9) -> Optional[int]:
        """
        Get a single digit number from user

        Args:
            prompt: Prompt to display
            min_val: Minimum valid value (inclusive)
            max_val: Maximum valid value (inclusive)

        Returns:
            Integer value or None if cancelled
        """
        if not self.screen:
            return None

        self.screen.draw_message(prompt)
        key = self.read_key()
        self.screen.clear_message()

        # Check if valid digit
        if key.isdigit():
            value = int(key)
            if min_val <= value <= max_val:
                return value

        return None

    def get_inventory_slot(self) -> Optional[int]:
        """
        Get inventory slot selection (1-9)

        Returns:
            Slot number (1-9) or None if cancelled
        """
        return self.get_number_input("Quel objet? (1-9)", min_val=1, max_val=9)


# Command categories for reference
MOVEMENT_COMMANDS = {CMD_MOVE_UP, CMD_MOVE_DOWN, CMD_MOVE_LEFT, CMD_MOVE_RIGHT}
INVENTORY_COMMANDS = {CMD_INVENTORY, CMD_EQUIPMENT, CMD_DROP, CMD_PICKUP}
ACTION_COMMANDS = {CMD_SEARCH, CMD_REST, CMD_CAST_SPELL}
SYSTEM_COMMANDS = {CMD_QUIT, CMD_HELP}

# Direction vectors (for reference)
DIRECTION_VECTORS = {
    'north': (0, -1),
    'south': (0, 1),
    'west': (-1, 0),
    'east': (1, 0),
}


def is_movement_command(cmd: str) -> bool:
    """Check if command is a movement command"""
    return cmd in MOVEMENT_COMMANDS


def is_inventory_command(cmd: str) -> bool:
    """Check if command is an inventory command"""
    return cmd in INVENTORY_COMMANDS


def is_action_command(cmd: str) -> bool:
    """Check if command is an action command"""
    return cmd in ACTION_COMMANDS


def is_system_command(cmd: str) -> bool:
    """Check if command is a system command"""
    return cmd in SYSTEM_COMMANDS


def get_movement_vector(cmd: str) -> Optional[Tuple[int, int]]:
    """
    Convert movement command to (dx, dy) vector

    Args:
        cmd: Movement command character

    Returns:
        (dx, dy) tuple or None if not a movement command
    """
    movement_map = {
        CMD_MOVE_UP: (0, -1),     # North
        CMD_MOVE_DOWN: (0, 1),    # South
        CMD_MOVE_LEFT: (-1, 0),   # West
        CMD_MOVE_RIGHT: (1, 0),   # East
    }
    return movement_map.get(cmd)
