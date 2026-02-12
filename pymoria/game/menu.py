"""
Start menu and character creation for Moria.
"""

import curses
from game.player import Player
from game.stats import Stats


class Menu:
    """Start menu and character creation."""

    def __init__(self, stdscr):
        self.stdscr = stdscr

    def show_title(self):
        """Display title screen matching original MORIA layout."""
        while True:
            self.stdscr.clear()
            try:
                self.stdscr.addstr(0, 0,
                    "               MORIA  (TM)  Version 1.9.8.7     Copyright AJM86")
                self.stdscr.addstr(9, 29, "Vous d\u00e9sirez :")
                self.stdscr.addstr(14, 19,
                    "Avoir des explications sur le jeu   --->  entrez E")
                self.stdscr.addstr(16, 19,
                    "Consulter la table des scores       --->  entrez S")
                self.stdscr.addstr(18, 19,
                    "Commencer \u00e0 jouer                   --->  entrez J")
                self.stdscr.addstr(20, 19,
                    "Finir                               --->  entrez F")
                self.stdscr.addstr(22, 49, "votre choix  :")
                self.stdscr.move(22, 69)
            except curses.error:
                pass
            self.stdscr.refresh()

            ch = self.stdscr.getch()
            if ch == ord('e') or ch == ord('E'):
                self.show_help()
            elif ch == ord('s') or ch == ord('S'):
                self.show_scores()
            elif ch == ord('j') or ch == ord('J'):
                return 'new'
            elif ch == ord('f') or ch == ord('F'):
                return 'quit'

    def show_help(self):
        """Show help screen matching original messages 0x134-0x146."""
        import curses
        # Same 3-page layout as FUN_1000_6249
        page1 = [
            "a    abandonner un objet",
            "b    boire une potion                       l    lire un parchemin",
            "B    brandir une arme                       i,*  faire l'inventaire",
            "e    enlever une armure                     r    rev\u00eatir une armure",
            "E    enfiler un anneau                      N    eNlever un anneau",
            "m    manger quelque chose",
            "R    renommer un objet",
            "c    fiche de personage",
            "?    liste des commandes                    s    table des scores",
            "L    lancer un sort                         T    lancer un objet",
        ]
        page2 = [
            ">    monter                                 <    descendre",
            "2 \u25bc  mouvement vers le bas de l'\u00e9cran",
            "4 \u25ba  mouvement vers la gauche de l'\u00e9cran",
            "6 \u25c4  mouvement vers la droite de l'\u00e9cran",
            "8 \u25b2  mouvement vers le haut de l'\u00e9cran",
            ".    rester sur place",
        ]
        page3 = [
            "^G    couper/retablir le son                 ^T   tableau de chasse",
            "^S    se suicider                            ^F   abandonner la partie",
            "^P    raffraichir l'\u00e9cran                    ^H   help...",
        ]
        for page in [page1, page2, page3]:
            self.stdscr.clear()
            for i, line in enumerate(page):
                try:
                    self.stdscr.addstr(i, 0, line)
                except curses.error:
                    pass
            try:
                self.stdscr.addstr(len(page) + 1, 0, "Appuyez sur ESPACE...")
            except curses.error:
                pass
            self.stdscr.refresh()
            while self.stdscr.getch() != ord(' '):
                pass

    def show_scores(self):
        """Display high scores screen."""
        self.stdscr.clear()
        try:
            self.stdscr.addstr(0, 0, "Table des scores")
            self.stdscr.addstr(22, 49, "Appuyez sur ESPACE pour continuer...")
        except curses.error:
            pass
        self.stdscr.refresh()
        while self.stdscr.getch() != ord(' '):
            pass

    def create_character(self):
        """Character creation matching original MORIA flow."""
        name = self._ask_name()
        force, dexterite, intelligence = self._allocate_stats()

        player = Player(name)
        player.stats = Stats(
            strength=force,
            dexterity=dexterite,
            intelligence=intelligence,
        )
        player.max_food = force
        player.current_food = force
        return player

    def _ask_name(self):
        """Display intro text and ask for player name (select_or_load_character)."""
        self.stdscr.clear()
        try:
            self.stdscr.addstr(8, 9,
                "Salut, t\u00e9m\u00e9raire aventurier ....")
            self.stdscr.addstr(10, 9,
                "Vous allez entrer dans le labyrinthe de la Moria.")
            self.stdscr.addstr(12, 9,
                "... mais auparavant, veuillez me donner votre nom,")
            self.stdscr.addstr(14, 9,
                "il me sera utile pour inscrire sur votre tombe ...")
        except curses.error:
            pass
        curses.echo()
        curses.curs_set(1)
        self.stdscr.addstr(16, 9, "Votre nom : ")
        self.stdscr.refresh()
        name = self.stdscr.getstr(16, 21, 16).decode('utf-8').strip()
        curses.noecho()
        curses.curs_set(0)
        if not name:
            name = "Aventurier"
        return name

    def _allocate_stats(self):
        """Stat allocation matching original initialize_new_game."""
        self.stdscr.clear()
        try:
            self.stdscr.addstr(0, 0, "Personnage standard (o/n)?")
        except curses.error:
            pass
        self.stdscr.refresh()

        ch = self.stdscr.getch()
        if ch == ord('o') or ch == ord('O'):
            return 100, 100, 100

        # Custom character: distribute 255 points
        total = 255
        self.stdscr.clear()
        try:
            self.stdscr.addstr(0, 0, f"Vous avez {total:3d} point(s) \u00e0 r\u00e9partir")
            self.stdscr.addstr(3, 4, "force         : ")
            self.stdscr.addstr(4, 4, "dext\u00e9rit\u00e9     : ")
            self.stdscr.addstr(5, 4, "intelligence  : ")
        except curses.error:
            pass

        curses.echo()
        curses.curs_set(1)

        # Read force
        self.stdscr.move(3, 20)
        self.stdscr.refresh()
        force = self._read_stat_value(3, 20, total)
        remaining = total - force
        self.stdscr.addstr(0, 10, f"{remaining:3d}")
        self.stdscr.refresh()

        # Read dexterite
        self.stdscr.move(4, 20)
        self.stdscr.refresh()
        dexterite = self._read_stat_value(4, 20, remaining)
        remaining = remaining - dexterite
        self.stdscr.addstr(0, 10, f"{remaining:3d}")

        # Intelligence gets the remainder
        self.stdscr.addstr(5, 20, str(remaining))
        self.stdscr.refresh()
        intelligence = remaining

        curses.noecho()
        curses.curs_set(0)
        return force, dexterite, intelligence

    def _read_stat_value(self, row, col, maximum):
        """Read a numeric stat value from the user, clamped to [0, maximum]."""
        self.stdscr.move(row, col)
        self.stdscr.clrtoeol()
        self.stdscr.refresh()
        try:
            raw = self.stdscr.getstr(row, col, 5).decode('utf-8').strip()
            value = int(raw)
        except (ValueError, UnicodeDecodeError):
            value = 0
        return max(0, min(maximum, value))
