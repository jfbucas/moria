# Add this to screen.py - fixed draw_map method
def draw_map_full(self, dungeon, player):
    """Draw entire dungeon level (not centered on player)."""
    if not self.map_window:
        return

    self.map_window.clear()
    map_height, map_width = self.map_window.getmaxyx()

    # Draw the entire dungeon (79x22)
    for y in range(min(dungeon.height, map_height)):
        for x in range(min(dungeon.width, map_width)):
            # Draw player
            if x == player.x and y == player.y:
                try:
                    self.map_window.addstr(y, x, '@', self.stdscr.color_pair(2) if hasattr(self.stdscr, 'color_pair') else 0)
                except:
                    pass
                continue

            # Check monsters
            monster_here = None
            for monster in dungeon.monsters:
                if monster['x'] == x and monster['y'] == y:
                    monster_here = monster
                    break

            if monster_here:
                try:
                    self.map_window.addstr(y, x, monster_here['template'].char, self.stdscr.color_pair(3) if hasattr(self.stdscr, 'color_pair') else 0)
                except:
                    pass
                continue

            # Check items
            item_here = None
            for item in dungeon.items:
                if item['x'] == x and item['y'] == y:
                    item_here = item
                    break

            if item_here:
                try:
                    self.map_window.addstr(y, x, item_here['template'].char, self.stdscr.color_pair(4) if hasattr(self.stdscr, 'color_pair') else 0)
                except:
                    pass
                continue

            # Draw terrain
            try:
                self.map_window.addstr(y, x, dungeon.get_char_at(x, y), 0)
            except:
                pass
