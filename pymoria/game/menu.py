"""
Start menu and character creation for Moria.
"""

import curses
import random
from game.player import Player
from game.stats import Stats


class Menu:
    """Start menu and character creation."""

    def __init__(self, stdscr):
        self.stdscr = stdscr

    def show_title(self):
        """Display title screen."""
        self.stdscr.clear()
        title = [
            "",
            "      ╔═══════════════════════════════════╗",
            "      ║                                   ║",
            "      ║   MANUEL DU PARFAIT CHEVALIER     ║",
            "      ║                                   ║",
            "      ╚═══════════════════════════════════╝",
            "",
            "              ═══ MORIA ═══",
            "",
            "   Aventurez-vous dans le labyrinthe de la Moria",
            "   15 niveaux de galeries pleines de monstres",
            "",
            "   BUT : Trouver le SILMARIL au niveau 12",
            "         et sortir avec un maximum d'or !",
            "",
            "",
            "   1. Nouvelle partie",
            "   2. Charger une partie",
            "   3. Aide",
            "   Q. Quitter",
            "",
            "   Votre choix : "
        ]

        for i, line in enumerate(title):
            try:
                self.stdscr.addstr(i, 0, line)
            except curses.error:
                pass

        self.stdscr.refresh()

        while True:
            ch = self.stdscr.getch()
            if ch == ord('1'):
                return 'new'
            elif ch == ord('2'):
                return 'load'
            elif ch == ord('3'):
                self.show_help()
                self.show_title()
            elif ch == ord('Q') or ch == ord('q'):
                return 'quit'

    def show_help(self):
        """Show help screen."""
        self.stdscr.clear()
        help_text = [
            "═══ COMMANDES ═══",
            "",
            "Déplacement (pavé numérique):",
            "  8 : Haut        2 : Bas",
            "  4 : Gauche      6 : Droite",
            "  7,9,1,3 : Diagonales",
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
            "Autre:",
            "  ? : Liste des commandes",
            "  ^H : Voir le manuel",
            "  ^S : Sauvegarder",
            "",
            "Symboles:",
            "  @ : Vous          $ : Or",
            "  • : Potion        ? : Parchemin",
            "  = : Arme          ⛨ : Armure",
            "  : : Nourriture    ° : Anneau",
            "  ◊ : Silmaril !",
            "",
            "Appuyez sur ESPACE pour continuer..."
        ]

        for i, line in enumerate(help_text):
            try:
                self.stdscr.addstr(i, 0, line)
            except curses.error:
                pass

        self.stdscr.refresh()

        while self.stdscr.getch() != ord(' '):
            pass

    def create_character(self):
        """Character creation."""
        self.stdscr.clear()

        # Get player name
        curses.echo()
        curses.curs_set(1)

        self.stdscr.addstr(0, 0, "═══ CRÉATION DU PERSONNAGE ═══")
        self.stdscr.addstr(2, 0, "Entrez votre nom : ")
        self.stdscr.refresh()

        name = self.stdscr.getstr(2, 19, 20).decode('utf-8')
        if not name:
            name = "Aventurier"

        curses.noecho()
        curses.curs_set(0)

        # Roll stats
        self.stdscr.addstr(4, 0, "Génération des caractéristiques...")
        self.stdscr.refresh()

        stats = self._roll_stats()

        # Display stats
        y = 6
        self.stdscr.addstr(y, 0, "Vos caractéristiques:")
        y += 1
        self.stdscr.addstr(y, 2, f"Force        : {stats.strength}")
        y += 1
        self.stdscr.addstr(y, 2, f"Intelligence : {stats.intelligence}")
        y += 1
        self.stdscr.addstr(y, 2, f"Sagesse      : {stats.wisdom}")
        y += 1
        self.stdscr.addstr(y, 2, f"Dextérité    : {stats.dexterity}")
        y += 1
        self.stdscr.addstr(y, 2, f"Constitution : {stats.constitution}")
        y += 1
        self.stdscr.addstr(y, 2, f"Charisme     : {stats.charisma}")
        y += 2

        self.stdscr.addstr(y, 0, "Acceptez-vous ces caractéristiques ? (o/n/r=relancer) : ")
        self.stdscr.refresh()

        while True:
            ch = self.stdscr.getch()
            if ch == ord('o') or ch == ord('O'):
                # Create player with these stats
                player = Player(name)
                player.stats = stats
                player.max_hp = 10 + stats.constitution
                player.current_hp = player.max_hp
                return player
            elif ch == ord('r') or ch == ord('R'):
                # Reroll
                return self.create_character()
            elif ch == ord('n') or ch == ord('N'):
                # Start over
                return self.create_character()

    def _roll_stats(self):
        """Roll character stats (3d6 for each)."""
        def roll_3d6():
            return sum(random.randint(1, 6) for _ in range(3))

        return Stats(
            strength=roll_3d6(),
            intelligence=roll_3d6(),
            wisdom=roll_3d6(),
            dexterity=roll_3d6(),
            constitution=roll_3d6(),
            charisma=roll_3d6()
        )
