# MORIA DOS 1.9.8.7 — Monster Spawning & Population System

Reverse-engineered from `MORIA_with_constants.C` functions: `populate_level_with_monsters` (line 2950),
`spawn_monsters` (line 3360), `spawn_special_monster_with_item` (line 2760), `spawn_unique_monster_type_23`
(line 2833), `spawn_monster_type_1f` (line 2863), `spawn_wandering_monster` (line 2879),
`add_monster_to_level_list` (line 2899), `prepend_monster_to_global_list` (line 2926),
`find_random_empty_floor_space` (line 2014), `find_position_near_player` (line 2035),
`place_object_on_map` (line 2121). Cross-referenced with `memory.dump` (spawn weight tables).

---

## Table of Contents

1. [Initialization Flow](#1-initialization-flow)
2. [Item Spawning per Level (spawn_monsters)](#2-item-spawning-per-level-spawn_monsters)
3. [Monster Spawn Weight Table](#3-monster-spawn-weight-table)
4. [Timed Monster Spawning (populate_level_with_monsters)](#4-timed-monster-spawning-populate_level_with_monsters)
5. [Boss Monster Spawning](#5-boss-monster-spawning)
6. [The Silmaril](#6-the-silmaril)
7. [Wandering Monster System](#7-wandering-monster-system)
8. [Helper Functions](#8-helper-functions)
9. [Key Addresses](#9-key-addresses)

---

## 1. Initialization Flow

**Function**: game initialization (line ~3728)

At game start, the following sequence creates the entire dungeon population:

```
seed_rng()
select_or_load_character()
initialize_new_game()

draw_dungeon_border(1)            // Create wall grid for level 1
generate_dungeon_level(1)         // Place stairs, room overlay, special tiles
spawn_monsters(1)                 // Populate level 1 with ITEMS (gold, potions, etc.)
generate_random_names()           // Generate scroll gibberish names
randomize_item_appearances()      // Shuffle potion colors, ring materials, wand woods

// Place Silmaril on level 15 floor
initialize_monster_or_item(item, level=15, type=8)  // Light source
item.subtype = 0                                     // Force subtype 0 = Silmaril
place_object_on_map(15, item)

// Spawn all boss monsters (once, at game start)
spawn_special_monster_with_item()     // Disguised Sauron (level 10-12)
spawn_monster_type_1f()               // Ungoliant (level 14)
spawn_wandering_monster()             // Carcharoth (level 8-9)
add_monster_to_level_list()           // Glaurung (level 12-13)
prepend_monster_to_global_list()      // Saruman (level 10)
spawn_unique_monster_type_23()        // Morgoth + Silmaril (level 15)
```

**When entering a new dungeon level** (line 11684):
```
dungeon_level += 1
if level_not_yet_generated[dungeon_level]:
    draw_dungeon_border(dungeon_level)
    generate_dungeon_level(dungeon_level)
    spawn_monsters(dungeon_level)           // Items only (not monsters)
```

Levels are generated on first visit and persist. Re-visiting a level uses the saved state.

---

## 2. Item Spawning per Level (spawn_monsters)

**Function**: `spawn_monsters(dungeon_level)` (line 3360)

Despite its name, this function spawns **items** (gold, food, potions, scrolls, etc.), not monsters.
Called once per level when the level is first generated.

### Item Spawn Config Table (DS:0x79D7)

Stride 0x30 (48 bytes) per item type. Three fields per entry:

| Type | Item      | Base | Rand | Extra |
|------|-----------|-----:|-----:|------:|
| 0    | Gold      | 5    | 5    | 0     |
| 1    | Food      | 1    | 4    | 0     |
| 2    | Potion    | 3    | 5    | 3     |
| 3    | Scroll    | 3    | 4    | 3     |
| 4    | Ring      | 1    | 2    | 2     |
| 5    | Wand      | 1    | 3    | 2     |
| 6    | Armor     | 1    | 2    | 3     |
| 7    | Weapon    | 1    | 1    | 3     |
| 8    | Light     | 0    | 2    | 0     |

### Algorithm

```python
# 1. Determine "favored item type" based on dungeon depth
#    (deeper levels favor more powerful equipment)
#    Approximate thresholds (garbled in decompilation):
#    Level >= ~12: favored = 7 (weapon)
#    Level >= ~9:  favored = 6 (armor)
#    Level >= ~6:  favored = 3 (scroll)
#    Level >= ~4:  favored = 2 (potion)
#    Level >= ~2:  favored = 4 (ring)
#    Level 1:      favored = 5 (wand)

# 2. For each item type 0-8:
for item_type in range(9):
    count = table[item_type].base
    if table[item_type].rand > 0:
        count += random_mod(table[item_type].rand)
    if item_type == favored:
        count += random_mod(table[item_type].extra) + 1
    # Spawn 'count' items of this type
    for i in range(count):
        item = initialize_monster_or_item(dungeon_level, item_type)
        place_object_on_map(dungeon_level, item)
```

### Expected Item Counts per Level

| Type    | Count Range    | Average |
|---------|---------------|--------:|
| Gold    | 5–9           | 7.0     |
| Food    | 1–4           | 2.5     |
| Potion  | 3–7 (+1–3)    | 5.0     |
| Scroll  | 3–6 (+1–3)    | 4.5     |
| Ring    | 1–2 (+1–2)    | 1.5     |
| Wand    | 1–3 (+1–2)    | 2.0     |
| Armor   | 1–2 (+1–3)    | 1.5     |
| Weapon  | 1 (+1–3)      | 1.0     |
| Light   | 0–1           | 0.5     |
| **Total** |             | **~25–30** |

("+N" ranges apply only when that type is the favored type for the level.)

---

## 3. Monster Spawn Weight Table

**Address**: `template * 0x20 + dungeon_level * 2 + DS:0xAB93`

28 regular monster templates (1–28) × 15 dungeon levels. Each entry is a 16-bit spawn weight
used as a probability by `populate_level_with_monsters`.

| Idx | Monster       |  L1 |  L2 |  L3 |  L4 |  L5 |  L6 |  L7 |  L8 |  L9 | L10 | L11 | L12 | L13 | L14 | L15 |
|----:|---------------|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|
|   1 | Air           |   0 |   0 |   0 |   0 |   0 |   0 |   2 |   4 |   5 |   5 |   2 |   0 |   0 |   0 |   0 |
|   2 | Araignee      |  20 |  18 |  12 |   8 |   4 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |
|   3 | Balrog        |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   2 |   4 |   4 |   6 |
|   4 | Chauve Souris |  10 |  10 |  10 |   8 |   6 |   2 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |
|   5 | Crebain       |   0 |   3 |   9 |  12 |   5 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |
|   6 | Dragon        |   0 |   0 |   0 |   0 |   0 |   0 |   1 |   1 |   2 |   4 |   2 |   0 |   0 |   0 |   0 |
|   7 | Dragon Aile   |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   2 |   2 |   4 |   4 |   5 |   5 |
|   8 | oEil          |   2 |   2 |   4 |   6 |   7 |   4 |   4 |   4 |   4 |   4 |   4 |   4 |   4 |   0 |   0 |
|   9 | Fee           |   0 |   0 |   0 |   0 |   0 |   1 |   2 |   3 |   3 |   4 |   4 |   3 |   3 |   2 |   1 |
|  10 | Galgal        |   0 |   0 |   0 |   0 |   1 |   3 |   6 |   8 |  10 |   6 |   4 |   2 |   0 |   0 |   0 |
|  11 | Gobelin       |   2 |   4 |   8 |  17 |  14 |  12 |   6 |   2 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |
|  12 | Huorn         |   0 |   0 |   0 |   1 |   3 |   4 |   5 |   5 |   4 |   0 |   0 |   0 |   0 |   0 |   0 |
|  13 | Loup          |   5 |  10 |  20 |  12 |  10 |   8 |   4 |   2 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |
|  14 | Loup Garou    |   0 |   0 |   0 |   0 |   0 |   2 |   4 |   4 |   2 |   2 |   0 |   0 |   0 |   0 |   0 |
|  15 | Mewlip        |   0 |   0 |   0 |   1 |   1 |   2 |   4 |   8 |   9 |   8 |   8 |   8 |   5 |   4 |   4 |
|  16 | Moricaud      |   0 |   0 |   1 |   4 |   8 |  12 |   8 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |
|  17 | Nazgul        |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   1 |   2 |   4 |   6 |   4 |   3 |   2 |   2 |
|  18 | Oliphant      |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   1 |   2 |   4 |   5 |   6 |   6 |
|  19 | Orc           |   0 |   4 |   6 |  10 |  12 |  12 |  10 |   8 |   6 |   0 |   0 |   0 |   0 |   0 |   0 |
|  20 | Rat           |  10 |  10 |  10 |  10 |  10 |  10 |  10 |  10 |  10 |  10 |  10 |  10 |  10 |  10 |  10 |
|  21 | Serpent       |  15 |  20 |  15 |  15 |  10 |   8 |   6 |   4 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |
|  22 | Succube       |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   1 |   3 |   5 |   5 |
|  23 | Troll         |   0 |   0 |   0 |   0 |   2 |   3 |   5 |   7 |   5 |   2 |   2 |   2 |   0 |   0 |   0 |
|  24 | Uruk-hai      |   0 |   0 |   2 |   4 |   9 |  15 |  16 |  10 |  10 |  10 |  10 |  10 |  10 |  10 |  10 |
|  25 | Variag        |   0 |   1 |   2 |   6 |  10 |   7 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |   0 |
|  26 | Voleur        |   0 |   0 |   0 |   0 |   0 |   3 |   4 |   5 |   5 |   6 |   6 |   5 |   5 |   4 |   3 |
|  27 | Wharg         |   0 |   0 |   1 |   3 |   9 |  11 |  13 |  10 |   8 |   4 |   2 |   0 |   0 |   0 |   0 |
|  28 | Woose         |   0 |   0 |   0 |   0 |   1 |   3 |   5 |   7 |   4 |   0 |   0 |   0 |   0 |   0 |   0 |
| — | **Total**      |  64 |  82 |  98 | 110 | 115 | 110 | 108 |  96 |  87 |  66 |  54 |  50 |  53 |  52 |  52 |

### Population Phases by Dungeon Depth

| Levels | Dominant Monsters | Flavor |
|--------|------------------|--------|
| 1–3    | Spider, Bat, Snake, Wolf, Rat | Vermin & wildlife |
| 4–6    | Goblin, Orc, Moricaud, Variag, Crebain | Humanoid enemies |
| 7–9    | Uruk-hai, Wharg, Galgal, Troll, Mewlip | Elite warriors |
| 10–12  | Nazgul, Dragon, Winged Dragon, Fee, Voleur | End-game horrors |
| 13–15  | Balrog, Oliphant, Succube, Mewlip, Rat | Deep dungeon terrors |

Note: **Rats** (weight 10) appear on every level — they are the universal filler monster.

---

## 4. Timed Monster Spawning (populate_level_with_monsters)

**Function**: `populate_level_with_monsters()` (line 2950)

This is the wandering monster system. Called from the main game loop every 20 turns.

### Call Sites

| Location | Trigger | Times Called |
|----------|---------|-------------|
| Line 12513 | Every 20 turns (`turn_count % 20 == 0`) | 1 |
| Line 12517–12519 | If cursed item OR active wand effect | +3 (total 4) |
| Line 6110 | On teleport | 1 |
| Line 9064 | On special movement event | 1 |

### Algorithm

```python
def populate_level_with_monsters():
    for template in range(1, 29):  # Templates 1-28
        # Check level cap
        if monster_count[dungeon_level] >= 25:
            continue

        weight = spawn_table[template][dungeon_level]
        if weight == 0:
            continue

        # Cursed item doubles spawn weight
        if player_has_cursed_item():
            weight *= 2

        # Probability check (exact formula garbled in decompilation)
        # Approximately: random check with weight as probability numerator
        if random_check(weight):
            monster = spawn_monster_from_template(template)

            # Place near player (within ~5 tiles)
            find_position_near_player(monster.x, monster.y)

            # Draw on monster overlay layer
            map_overlay[monster.y * 79 + monster.x] = monster.visible_char

            # Link to current level's monster list
            monster.next = monster_list[dungeon_level]
            monster_list[dungeon_level] = monster

            # Filter out certain chars from count
            # (monsters with char 'E' or 'H' may not count)
            if monster.attack_char not in ['E', 'H']:
                item_count[dungeon_level] += 1

            monster_count[dungeon_level] += 1
```

### Monster Cap

**Maximum 25 monsters per level** (`monster_count[level] < 0x19`).

### Cursed Item Effect on Spawning

When the player carries a cursed item (`ITEM_CURSED_SPECIAL`):
1. Spawn weights are **doubled** inside `populate_level_with_monsters`
2. The function is called **4 times** instead of 1 every 20 turns
3. Combined effect: **~8× monster spawn rate**

---

## 5. Boss Monster Spawning

All boss/unique monsters are spawned **once at game initialization** and placed on fixed level ranges.
They use templates 29–35 (the `is_stationary=1` templates).

### Boss Level Assignments

| Boss | Template | Index | Level(s) | Carried Item |
|------|----------|------:|----------|-------------|
| Carcharoth | Wolf (unique) | 29 (0x1D) | 8 or 9 (random) | — |
| Disguised Sauron | Sauron stats | 34 (0x22) | 10, 11, or 12 (random) | Ring of Invisibility |
| Saruman | Saruman | 32 (0x20) | 10 (fixed) | — |
| Glaurung | Dragon (unique) | 30 (0x1E) | 12 or 13 (random) | — |
| Ungoliant | Spider (unique) | 31 (0x1F) | 14 (fixed) | — |
| Morgoth | Morgoth | 35 (0x23) | 15 (fixed) | Silmaril (Light type 8, sub 0) |

### spawn_special_monster_with_item — Disguised Sauron (line 2760)

```python
def spawn_special_monster_with_item():
    slot = random_mod(3) + 10            # Level 10, 11, or 12
    monster = spawn_monster_from_template(0x22)  # Template 34 = Sauron stats

    # Disguise: pick random non-stationary monster appearance
    while True:
        disguise = random_mod(0x23) + 1  # Template 1-35
        if template[disguise].is_stationary == 0:
            break
        # Also filters: char != 'a' (Air), 'E' (Eye), 'H' (Huorn)

    monster.visible_char = template[disguise].attack_char
    monster.original_template_index = disguise  # Backup for name display

    # Give Ring of Invisibility (if no active projectile exists)
    if active_projectile_ptr == NULL:
        item = allocate_item()
        item.type = 4           # Ring
        item.subtype = 6        # Invisibility
        item.power = random_mod(50) + 50   # 50-99 charges
        item.is_cursed = 0
        item.is_identified = 0
        monster.carried_item = item
        active_projectile_ptr = item

    # Place on selected level
    monster_list[slot] = monster
    monster_count[slot] = 1
```

**Key detail**: Sauron appears as a random normal monster (Wolf, Goblin, Orc, etc.) but has
Sauron's full combat stats (100 XP, 180 HP, AC 11, 10 attacks, damage 6). The player cannot
tell it's Sauron until combat reveals disproportionate difficulty.

### spawn_unique_monster_type_23 — Morgoth (line 2833)

```python
def spawn_unique_monster_type_23():
    monster = spawn_monster_from_template(0x23)  # Template 35 = Morgoth

    # Create Silmaril as carried item
    item = allocate_item()
    item.type = 8           # Light source
    item.subtype = 0        # Silmaril
    # No power/fuel set (marker item only)
    monster.carried_item = item

    # Place on level 15
    monster_list[15] = monster    # DS:0xABA3
    monster_count[15] = 1         # DS:0x799B
```

### spawn_monster_type_1f — Ungoliant (line 2863)

```python
def spawn_monster_type_1f():
    monster = spawn_monster_from_template(0x1F)  # Template 31 = Ungoliant
    monster_list[14] = monster    # DS:0xAB9F
    monster_count[14] = 1         # DS:0x7999
```

### spawn_wandering_monster — Carcharoth (line 2879)

```python
def spawn_wandering_monster():
    slot = random_mod(2) + 8              # Level 8 or 9
    monster = spawn_monster_from_template(0x1D)  # Template 29 = Carcharoth
    monster_list[slot] = monster
    monster_count[slot] = 1
```

### add_monster_to_level_list — Glaurung (line 2899)

```python
def add_monster_to_level_list():
    slot = random_mod(2) + 12             # Level 12 or 13
    monster = spawn_monster_from_template(0x1E)  # Template 30 = Glaurung

    # Prepend to existing list (level may already have monsters from spawn_monsters)
    monster.next = monster_list[slot]
    monster_list[slot] = monster
    monster_count[slot] += 1
```

### prepend_monster_to_global_list — Saruman (line 2926)

```python
def prepend_monster_to_global_list():
    monster = spawn_monster_from_template(0x20)  # Template 32 = Saruman

    # Prepend to level 10's monster list
    monster.next = monster_list[10]    # DS:0xAB8F
    monster_list[10] = monster
    monster_count[10] += 1             # DS:0x7991
```

**Note**: Saruman and disguised Sauron can both be on level 10 (Sauron is random 10-12,
Saruman is always 10). If Sauron lands on level 10, the player faces both bosses.

---

## 6. The Silmaril

The Silmaril is represented as a **light source item** (type 8, subtype 0). It exists in two places:

### Floor Silmaril (level 15)

Created at game init (line 3742):
```python
item = initialize_monster_or_item(level=15, type=8)  # Light source
item.subtype = 0                                      # Force Silmaril subtype
place_object_on_map(level=15, item)                   # Place on random floor tile
```

This Silmaril is a visible item on the floor of level 15 that the player can pick up.
On the map it appears as `☼` (0x0F, light source display character).

### Morgoth's Silmaril

Created inside `spawn_unique_monster_type_23` (line 2847):
```python
item.type = 8      # Light source
item.subtype = 0   # Silmaril
```

Carried by Morgoth. Dropped when Morgoth is killed.

### Win Condition

The player must obtain a Silmaril (either from the floor or from killing Morgoth)
and bring it back up to level 1 to win the game.

---

## 7. Wandering Monster System

The main game loop (line ~12512) drives periodic monster spawning:

```python
# Main game loop, after processing player turn:
if turn_processed:
    if turn_count % 20 == 0:
        populate_level_with_monsters()          # Always: 1 call

        if player_has_cursed_item() or active_wand_effect:
            populate_level_with_monsters()      # Extra: 3 more calls
            populate_level_with_monsters()
            populate_level_with_monsters()
```

### Spawn Rate Summary

| Condition | Calls per 20 turns | Effective Rate |
|-----------|-------------------|----------------|
| Normal | 1 | Baseline |
| Cursed item | 4 | 4× baseline |
| + Doubled weights | 4 | ~8× baseline |

### Monster Arrival Pattern

1. Player enters a new level → no monsters (items only from `spawn_monsters`)
2. Every 20 turns, `populate_level_with_monsters` checks all 28 templates
3. Each template has a level-dependent spawn weight (see table in section 3)
4. Monsters spawn **near the player** (within ~5 tiles) via `find_position_near_player`
5. Level fills up gradually to the cap of **25 monsters**
6. Additional calls from teleportation and special movement events also trigger spawns

---

## 8. Helper Functions

### find_random_empty_floor_space (line 2014)

Finds a random empty tile on a given level.

```python
def find_random_empty_floor_space(level):
    while True:
        row = random_mod(21) + 2      # Range: 2-22
        col = random_mod(77) + 2      # Range: 2-78
        tile = map_buffer[level][row * 79 + col]     # Layer -0x50
        overlay = monster_overlay[row * 79 + col]     # Layer -0x0C
        if tile == ' ' and overlay == ' ':
            return (col, row)
```

Used by: `spawn_monster_from_template`, `place_object_on_map`, `generate_dungeon_level`.

### find_position_near_player (line 2035)

Finds a random empty tile near the player's position.

```python
def find_position_near_player():
    while True:
        dy = random_mod(5)     # Offset range (signed, ~[-2, +2])
        row = player_y + dy
        dx = random_mod(5)
        col = player_x + dx
        tile = map_buffer[dungeon_level][row * 79 + col]
        overlay = monster_overlay[row * 79 + col]
        if tile == ' ' and overlay == ' ':
            # Additional bounds checking: row in [2, 22], col in [2, 78]
            return (col, row)
```

Used by: `populate_level_with_monsters` (wandering monsters spawn near player).

### place_object_on_map (line 2121)

Places an item on the map at a random empty floor tile.

```python
def place_object_on_map(level, item):
    (col, row) = find_random_empty_floor_space(level)
    item.x = col
    item.y = row

    # Draw item's display character on tile map
    display_char = lookup_table_b9c7(item.type)
    map_buffer[level][row * 79 + col] = display_char    # Layer -0x50

    # Link to level's item list
    item.next = item_list[level]
    item_list[level] = item
```

### spawn_monster_from_template (line 2534)

Full monster creation from template. See ENTITY_DATABASE.md for details.

```python
def spawn_monster_from_template(template_index):
    monster = allocate_monster_object()

    # Copy stats from template
    monster.attack_char = template[template_index].attack_char
    monster.visible_char = monster.attack_char
    monster.template_index = template_index
    monster.original_template_index = template_index
    monster.to_hit = template.to_hit
    monster.hit_points = template.hit_points
    monster.armor_class = template.armor_class
    monster.num_attacks = template.num_attacks
    monster.damage_per_attack = template.damage_per_attack
    monster.speed_bonus = template.speed_bonus
    monster.level = template.level
    monster.item_drop_chance = template.item_drop_chance
    monster.item_drop_type = template.item_drop_type
    monster.special_ability = template.special_ability
    monster.is_invisible = template.is_invisible
    monster.is_hostile = template.is_hostile
    monster.is_stationary = template.is_stationary

    # Place at random empty floor space
    (monster.x, monster.y) = find_random_empty_floor_space(dungeon_level)

    # Level scaling: buff weak monsters to match player
    if monster.to_hit + monster.speed_bonus < player_level + base_ac + 5:
        monster.to_hit += 1
        monster.speed_bonus = player_level + base_ac + 6 - monster.to_hit

    # Initialize state flags
    monster.status_timer = 0
    monster.is_fleeing = 0
    monster.is_visible = 0
    monster.is_awake = 0
    monster.is_alerted = 0
    monster.move_toggle = 0
    monster.stun_timer = 0
    monster.unknown_2c = 1
    monster.carried_item = NULL
    monster.next = NULL

    # Item drop roll
    if monster.item_drop_chance > 0:
        if random_mod(monster.item_drop_chance) == 0:
            monster.carried_item = initialize_monster_or_item(
                dungeon_level, monster.item_drop_type)

    # Eye of Sauron special: always awake, permanent timer
    if monster.attack_char == 'E':
        monster.is_awake = 1
        monster.status_timer = 0xFFFF   # -1 = permanent

    return monster
```

---

## 9. Key Addresses

### Per-Level Monster Data

| Formula | Description |
|---------|-------------|
| `level * 4 + DS:0xAB67` | Monster linked list head (far pointer) |
| `level * 2 + DS:0x797D` | Monster count per level (max 25) |
| `level * 4 + DS:0xAB27` | Item linked list head (far pointer) |
| `level * 2 + DS:0x799B` | Item count per level |

### Boss Monster Pointers

| Address | Level | Monster |
|---------|------:|---------|
| DS:0xAB87 or 0xAB8B | 8 or 9 | Carcharoth |
| DS:0xAB8F–0xAB97 | 10–12 | Disguised Sauron |
| DS:0xAB8F | 10 | Saruman |
| DS:0xAB97 or 0xAB9B | 12 or 13 | Glaurung |
| DS:0xAB9F | 14 | Ungoliant |
| DS:0xABA3 | 15 | Morgoth |
| DS:0xABAF | — | Active projectile / Sauron's ring |

### Spawn Table Addresses

| Address | Stride | Description |
|---------|--------|-------------|
| DS:0x79D7 | 0x30 per type | Item spawn config (base/rand/extra) |
| DS:0xAB93 | 0x20 per template | Monster spawn weights (28 templates × 15 levels) |

---

## Answers to Key Questions

### 1. How many monsters per level? What formula?

**Maximum 25 monsters per level** (hard cap checked every spawn attempt). Monsters are NOT spawned
when the level is first generated — only items are placed by `spawn_monsters`. Regular monsters
arrive via `populate_level_with_monsters`, called every 20 turns from the main game loop. Each call
iterates all 28 templates and uses weighted probability (see spawn weight table) to decide which
monsters appear. Boss monsters (1 per assigned level) are pre-placed at game init.

### 2. Which monsters appear on which levels?

See the complete spawn weight table in section 3. Key patterns:
- **Levels 1–3**: Spiders, Bats, Snakes, Wolves (weak wildlife)
- **Levels 4–6**: Goblins, Orcs, Moricauds, Variags (humanoids)
- **Levels 7–9**: Uruk-hai, Wargs, Galgals, Trolls (elite fighters)
- **Levels 10–12**: Nazgul, Dragons, Fairies, Thieves (magical/powerful)
- **Levels 13–15**: Balrogs, Oliphants, Succubi, Winged Dragons (endgame)
- **All levels**: Rats (constant weight 10), Uruk-hai (weight 10 on levels 7+)

### 3. How are boss monsters (Sauron, Morgoth) spawned?

All bosses spawn once at game initialization:
- **Morgoth** (level 15): carries Silmaril, stationary, 210 HP, 12 AC, 10 attacks × 10 damage
- **Sauron** (level 10-12): **disguised as a random normal monster**, carries Ring of Invisibility
- **Saruman** (level 10): stationary, 150 HP, special ability 25
- **Ungoliant** (level 14): stationary, 195 HP, 10 attacks × 7 damage
- **Glaurung** (level 12-13): stationary, 150 HP, 15 attacks × 3 damage
- **Carcharoth** (level 8-9): stationary, 120 HP, 9 attacks × 3 damage

### 4. The wandering monster system

Every 20 turns, `populate_level_with_monsters` checks all 28 templates against the current
dungeon level's spawn weight table. Each template has a probability of spawning based on its weight.
New monsters appear **near the player** (within ~5 tiles). The level caps at 25 monsters.
Carrying a cursed item causes 4× calls and 2× weights = **~8× spawn rate**.

### 5. How is the Silmaril placed/dropped?

Two Silmarils exist (both are light source type 8, subtype 0):
1. **Floor item on level 15**: placed during `generate_dungeon_level` initialization
2. **Carried by Morgoth**: dropped on Morgoth's death

The player can obtain either one. The goal is to bring a Silmaril back to level 1.
