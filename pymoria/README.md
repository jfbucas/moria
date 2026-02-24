# PyMoria

Python reimplementation of DOS MORIA 1.9.8.7 (French version) based on complete reverse engineering documentation.

## Project Status

**Phase 1 - Foundation: COMPLETE ✓**
- [x] Project structure
- [x] Core data structures (Player, Monster, Item, DungeonLevel)
- [x] XP formula implementation
- [x] 32-bit gold handling
- [x] Timed effects system (13 effects)
- [x] Game constants (all tile chars, food states, effects, items)
- [x] French message catalog (100+ messages)
- [x] Monster templates (35 templates with exact stats)
- [x] Item templates (potions, wands, rings, scrolls, weapons, armor)
- [x] Randomized item appearances (colors, woods, materials)
- [x] Display system (curses-based 80×25 terminal)
- [x] Status bar (French labels, exact DOS format)
- [x] Map rendering (20×79 viewport)
- [x] Input handling (keyboard commands, direction prompts)
- [x] Command mapping (movement, inventory, actions)
- [x] 4-direction only (NO diagonals)
- [x] Main game loop (turn-based)
- [x] Turn order (exact from PLAYER_ACTIONS.md)
- [x] Food/poison/regeneration/effects
- [x] Combat system (player attack, monster attack, XP/level-up)
- [x] All special attacks (Fear, Confusion, Drain, Steal, Acid, etc.)
- [x] 13 monster special types (Eye, Succubus, Fairy, Thief, Huorn, ...)

- [x] Monster AI (move_toggle half-speed, greedy pathfinding, special behaviors)
- [x] Wake/alert/flee/wander per monster type (Eye static, Bat random, Huorn adjacent-only)
- [x] HP regeneration for bosses (Ghost, Sauron, Saruman)

- [x] Magic system — potions (24), wands (22), scrolls (25)
- [x] Item identification (dual tables, auto-ID, unidentify-all via Amnesia)
- [x] Scroll cast-failure check (roll vs player_level//2 + intelligence)
- [x] Gasification (destroys inventory), Amnesia (unidentifies all), Hallucination (-1 INT)

- [x] Dungeon generation (10×39 cell grid, Kruskal's MST corridors, one extra enclosed room with ┴┬┤├ walls)
- [x] Item spawning per level depth (gold, food, potions, scrolls, rings, wands, armor, weapons)
- [x] Monster spawning (weighted by template × dungeon level, wandering spawner every 20 turns)
- [x] Boss initialization (Carcharoth, Sauron, Saruman, Glaurung, Ungoliant, Morgoth pre-placed)
- [x] Connectivity repair (BFS detects and tunnels through any disconnected passable regions)

- [x] Level transitions (advance_to_next_level: down=fall damage, up=safe, level persistence via visited_flag)
- [x] Stair prompts on tile entry ("Descendre?", "Monter?" with o/n confirmation)
- [x] Boss monsters transferred from placeholder levels to freshly generated levels

**Next Steps**: Prompt 12 (Combat System)

## Project Structure

```
pymoria/
├── __init__.py
├── main.py              # Entry point ✓
├── test_constants.py    # Constants validation ✓
├── test_templates.py    # Templates validation ✓
├── test_display.py      # Display system test ✓
├── test_input.py        # Input handling test ✓
├── test_game_loop.py    # Game loop test ✓
├── test_combat.py       # Combat system tests ✓
├── main_game.py         # Main game entry point ✓
├── README.md            # This file
├── game/                # Game logic
│   ├── __init__.py
│   ├── entities.py      # Core data structures ✓
│   ├── input.py         # Input handling ✓
│   ├── game_loop.py     # Main game loop ✓
│   ├── combat.py        # Combat system ✓
│   ├── dungeon.py       # Dungeon generation (Kruskal's MST) ✓
│   └── level_manager.py # Level transitions & persistence ✓
├── data/                # Constants, templates
│   ├── __init__.py
│   ├── messages.py      # French message catalog ✓
│   ├── monsters.py      # 35 monster templates ✓
│   └── items.py         # Item templates & randomization ✓
├── display/             # Rendering
│   ├── __init__.py
│   └── screen.py        # Curses display system ✓
└── utils/               # Helpers
    ├── __init__.py
    └── constants.py     # Game constants ✓
```

## Core Data Structures

Based on `reverse/MORIA_COMPLETE.md Section 2`:

### Player
- **3 stats**: strength, dexterity, intelligence (0-255, default 100)
- **HP**: current_hp, max_hp
- **Level & XP**: Uses formula `XP[n] = 50 × (2^(n-1) - 1)`
- **Gold**: 32-bit value (gold_low, gold_high)
- **Position**: (x, y)
- **Food**: Decreases by 1/turn
- **Inventory**: List of items
- **Timed effects**: 13 effect timers

### Monster
- **Template-based**: 35 templates from ENTITY_DATABASE.md (28 normal + 7 bosses)
- **Position**: (row, col)
- **Stats**: HP, AC, to_hit, damage_dice/sides
- **AI state**: is_awake, is_alerted, ai_state
- **CRITICAL**: `move_toggle` (0/1) - all monsters move every 2 turns
- **Special attacks**: List of attack codes
- **Notable**: Eye of Sauron (E) = 0 attacks, bosses are stationary

### Item
- **Type/Subtype**: 9 types (food, potion, scroll, wand, etc.)
- **Count**: Stackable items
- **Position**: If on floor
- **Value**: 32-bit gold value
- **Flags**: is_cursed, is_equipped, is_identified

### DungeonLevel
- **Tiles**: 20×79 2D array
- **visited_flag**: Level persistence
- **floor_items**: Items on floor
- **monsters**: Monsters on level

## Testing

Run the data structures test:

```bash
cd pymoria
python3 main.py
```

Run the constants test:

```bash
cd pymoria
python3 test_constants.py
```

Run the templates test:

```bash
cd pymoria
python3 test_templates.py
```

Run the display system test (requires terminal with curses support):

```bash
cd pymoria
python3 test_display.py
```

Run the input handling test (requires terminal with curses support):

```bash
cd pymoria
python3 test_input.py
```

Run the game loop test (requires terminal with curses support):

```bash
cd pymoria
python3 test_game_loop.py
```

Play the game (requires terminal with curses support):

```bash
cd pymoria
python3 main_game.py
```

All tests validate correct initialization with exact values from documentation.

## Key Implementation Details

### XP Formula (Exact from Original)
```python
def get_xp_for_level(level: int) -> int:
    if level <= 1:
        return 0
    return 50 * ((2 ** (level - 1)) - 1)
```

**Results**:
- Level 2: 50 XP
- Level 3: 150 XP
- Level 5: 750 XP
- Level 10: 25,550 XP

### 32-bit Gold Handling
```python
def get_total_gold(self) -> int:
    return (self.gold_high << 16) | self.gold_low
```

### Food States
```python
def get_food_status(self) -> str:
    if self.food_level > 5000: return "Rassasié"   # Full
    elif self.food_level > 3000: return "Normal"
    elif self.food_level > 1500: return "Faible"   # Weak
    elif self.food_level > 0: return "Affamé"      # Hungry
    else: return "Mourant"                          # Dying
```

## Critical Features (Must Match Original)

- ✓ **3 stats only** (Force, Dextérité, Intelligence)
- ✓ **XP formula**: `50 × (2^(n-1) - 1)`
- ✓ **32-bit gold** (low/high word split)
- ✓ **13 timed effects** (blindness, confusion, etc.)
- ✓ **Monster move_toggle** (all move every 2 turns)
- ✓ **Food decreases by 1/turn**
- ✓ **35 monster templates** (exact stats from original)
- ✓ **Randomized item names** (potions, wands, rings shuffled at game start)
- ✓ **Bat = 'C', Wolf = 'L', Eye = 'E'** (original monster chars)
- ✓ **80×25 DOS terminal** (curses-based display)
- ✓ **Status bar format** (French labels: Niv/Or/PV/Int/Dex/For/CA/Exp)
- ✓ **Player char = ☻** (CP437 0x02)
- ✓ **4-direction movement** (arrow keys + numpad 2/4/6/8, NO diagonals)
- ✓ **Command mapping** (i/e/d/q/s/r/m/? for inventory/equipment/drop/quit/etc.)
- ✓ **Direction prompts** ("Quelle direction?" for targeted actions)
- ✓ **Turn-based loop** (exact order: display→input→action→food→poison→effects→regen→monsters→spawn→death)
- ✓ **Food consumption** (-1 per turn, starvation damage)
- ✓ **HP regeneration** (formula: (15-level)//2 turns, min 1)

## Reference Documentation

All implementations based on:
- `reverse/MORIA_COMPLETE.md` - Main reference
- `reverse/COMBAT_SYSTEM.md` - Combat & XP formulas
- `reverse/PLAYER_ACTIONS.md` - Food, regeneration, effects
- `reverse/ENTITY_DATABASE.md` - Monster/item templates
- `Python_Implementation_Prompts.txt` - Implementation guide

## Development Notes

**Coordinate Systems**:
- Original: 1-indexed (DOS gotoxy)
- Python: 0-indexed (standard arrays)
- Conversion needed when porting algorithms

**String Encoding**:
- Original: CP850 (French characters: é, à, ê, â)
- Python: UTF-8 (direct Unicode equivalents)

**Tile Characters**:
- Original: CP437 box-drawing (┴┬┤├─│)
- Python: UTF-8 Unicode equivalents

## License

Original game: DOS MORIA 1.9.8.7
Reimplementation: Based on reverse engineering documentation
For educational purposes
