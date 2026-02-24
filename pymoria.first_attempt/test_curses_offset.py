#!/usr/bin/env python3
"""Minimal test to diagnose curses coordinate offset."""

import curses

def test_coordinates(stdscr):
    """Test if (0,0) actually draws at terminal (0,0)."""
    curses.noecho()
    curses.cbreak()
    curses.curs_set(0)
    stdscr.keypad(True)

    if curses.has_colors():
        curses.start_color()
        curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_BLACK)

    height, width = stdscr.getmaxyx()

    # Clear everything
    stdscr.clear()

    # Draw test characters at specific coordinates
    try:
        # Top-left corner
        stdscr.addstr(0, 0, 'A', curses.color_pair(1))
        # Top-right corner
        stdscr.addstr(0, width-1, 'B', curses.color_pair(1))
        # Bottom-left corner
        stdscr.addstr(height-1, 0, 'C', curses.color_pair(1))

        # Draw a grid pattern to see offset
        for y in range(min(10, height)):
            for x in range(min(10, width)):
                stdscr.addstr(y, x, str((y * 10 + x) % 10), curses.color_pair(1))

        stdscr.addstr(height-2, 0, f"Terminal size: {height}x{width}", curses.color_pair(1))
        stdscr.addstr(height-3, 0, "Does 'A' appear at top-left corner? Press any key...", curses.color_pair(1))

    except curses.error as e:
        stdscr.addstr(height//2, 0, f"Error: {e}", curses.color_pair(1))

    stdscr.refresh()
    stdscr.getch()

    # Cleanup
    curses.nocbreak()
    stdscr.keypad(False)
    curses.echo()
    curses.curs_set(1)

if __name__ == "__main__":
    curses.wrapper(test_coordinates)
