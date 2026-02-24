# PyMoria - Python Rewrite of Moria Roguelike

A faithful recreation of the classic DOS Moria roguelike game in Python for Linux terminals.

## Features

- **Authentic Experience**: Same gameplay, assets, and mechanics as the original
- **CP437 Display**: Classic DOS box-drawing characters in Linux terminal
- **Object-Oriented**: Clean Python class architecture
- **French Language**: Preserves the original French game text
- **Terminal-Based**: Uses Python curses for display

## Requirements

- Python 3.8+
- Linux terminal with Unicode support
- curses library (usually pre-installed)

## Installation

```bash
cd pymoria
pip install -r requirements.txt
```

## Running

```bash
python3 main.py
```

## Architecture

```
pymoria/
├── main.py              # Entry point
├── game/
│   ├── engine.py        # Main game loop
│   ├── player.py        # Player character
│   ├── monster.py       # Monster entities
│   ├── dungeon.py       # Dungeon generation & management
│   ├── item.py          # Items, equipment, potions
│   ├── combat.py        # Combat system
│   └── stats.py         # Character statistics
├── display/
│   ├── screen.py        # Terminal display manager
│   ├── ui.py            # UI components
│   └── messages.py      # Message display system
├── data/
│   ├── monsters.py      # Monster database
│   ├── items.py         # Item database
│   ├── potions.py       # Potion database
│   └── strings.py       # French game strings
└── utils/
    ├── constants.py     # Game constants
    └── helpers.py       # Utility functions
```

## Game Data

All game data (monsters, items, potions) has been extracted from the original DOS game memory dump and preserved in this rewrite.

## Credits

- Original Moria: Robert Alan Koeneke (1983)
- Python Rewrite: Based on reverse-engineered DOS version (2014)
- Reverse Engineering: Analysis of MORIA.EXE and memory dump

## License

This is a clean-room reimplementation for educational and preservation purposes.
