# MORIA DOS 1.9.8.7 — Complete Memory Map

Reverse-engineered from `MORIA_with_constants.C` (Ghidra decompilation) and `memory.dump` (DOS runtime snapshot).

All addresses are within the DOS data segment (DS = 0x22DE).

---

## Table of Contents

1. [Map Buffer Layout](#1-map-buffer-layout)
2. [Monster Object Structure (54 bytes)](#2-monster-object-structure-0x36--54-bytes)
3. [Monster Template Table (42 bytes each)](#3-monster-template-table-0x2a--42-bytes-each)
4. [Item Object Structure (26 bytes)](#4-item-object-structure-0x1a--26-bytes)
5. [Player Data Block (0xb86c–0xb948)](#5-player-data-block-0xb86c0xb948)
6. [Per-Level Arrays (0x78ed–0x79b0)](#6-per-level-arrays-0x78ed0x79b0)
7. [Game State Variables (0xe52d–0xe554)](#7-game-state-variables-0xe52d0xe554)
8. [Object System Linked Lists (0xABxx)](#8-object-system-linked-lists-0xabxx)
9. [Message Buffers (0xb72f–0xb84f)](#9-message-buffers-0xb72f0xb84f)
10. [High Score Entry (24 bytes)](#10-high-score-entry-0x18--24-bytes)
11. [Video/Terminal System (0xe53a–0xe554)](#11-videoterminal-system-0xe53a0xe554)
12. [DOS Runtime / Heap (0xe754–0xe78b)](#12-dos-runtime--heap-0xe7540xe78b)

---

## 1. Map Buffer Layout

### Buffer Pointer Table

Each dungeon level has a far pointer to its map buffer:

```
map_buffer_ptr[level] = *(uint32_t *)(level * 4 + 4)
```

16 entries (levels 0–15), allocated via `read_stream_data()` at init.

### Three Map Layers

**Layer 1 — Tile Map (offset -0x50)**

```c
tile = *(buf + row * MAP_WIDTH + col - 0x50)
// where buf = map_buffer_ptr[level], MAP_WIDTH = 79
```

- Stores dungeon geometry: walls, floors, stairs, items on ground
- The -0x50 offset (decimal 80 = MAP_WIDTH + 1) means `tile_base = buf - 0x50`
- Effective formula: `tile_base[row * 79 + col]`

**Layer 2 — Monster/Object Overlay (offset -0x0c)**

```c
overlay = *(row * MAP_WIDTH + col - 0x0c)
// Flat global buffer, NOT per-level
```

- Stores monster display characters drawn on top of tiles
- Written when monster moves: `overlay[pos] = monster[+1]` (visible_char)
- Cleared with 0x20 (space) when monster leaves

**Layer 3 — Visibility/Explored (offset +0x70d)**

```c
explored = *(level * 0x719 + row * MAP_WIDTH + col + 0x70d)
// 0x719 = 1817 = 23 rows × 79 cols per level
```

- Per-level explored flag array (0 = unexplored, 1 = explored)
- Each level also has flags at `buf + 0x719` and `buf + 0x71a` (level-generated flags)

### Room Grid Coordinate System

The dungeon is a 10×39 room grid. Each room occupies a 2×2 cell in map coordinates:

| Room Grid | Map Position |
|-----------|-------------|
| Room (R, C) | Map row `2*R - 1`, col `2*C - 1` |
| Vertical wall between (R,C) and (R,C+1) | Row `2*R - 1`, col `2*C` |
| Horizontal wall between (R,C) and (R+1,C) | Row `2*R`, col `2*C - 1` |
| Wall intersection | Row `2*R`, col `2*C` |

The 0x9e multiplier (158 = 2 × MAP_WIDTH) converts room rows to map rows for vertical wall access:
```c
vertical_wall = *(buf + room_row * 0x9e + room_col * 2 - 0x4f)
// -0x4f = -0x50 + 1 (accesses odd columns)
```

### Tile Characters (CP437)

| Hex | CP437 | Meaning |
|-----|-------|---------|
| 0x20 | (space) | Empty floor |
| 0xB3 | `│` | Vertical wall |
| 0xB4 | `┤` | Room left wall |
| 0xBF | `┐` | Top-right corner |
| 0xC0 | `└` | Bottom-left corner |
| 0xC1 | `┴` | Room top wall |
| 0xC2 | `┬` | Room bottom wall |
| 0xC3 | `├` | Room right wall |
| 0xC4 | `─` | Horizontal wall |
| 0xC5 | `┼` | Wall intersection |
| 0xD9 | `┘` | Bottom-right corner |
| 0xDA | `┌` | Top-left corner |
| 0xEF | | Stairs up |
| 0x9B | | Stairs down (level 1 special) |

### Corridor Generation (Kruskal's MST)

808 total possible walls (= 0x328, the random range):
- 390 horizontal walls (9 rows × 39 cols = 351 between-row + 39 bottom = ~390)
- 418 vertical walls (10 rows × 38 cols = 380 + extras)

Wall index `w` maps to:
- `w ≤ 351`: Horizontal wall. `row = (w-1)/39 + 1`, `col = (w-1)%39 + 1`. Map pos: row `2*row_idx`, col `2*col_idx - 1`
- `w > 351`: Vertical wall. `adj = w - 351`, `col = (adj-1)/10 + 1`, `row = (adj-1)%10 + 1`. Map pos: row `2*row_idx - 1`, col `2*col_idx`

389 unions needed for a spanning tree of 390 rooms.

---

## 2. Monster Object Structure (0x36 = 54 bytes)

Allocated by `allocate_monster_object` with `read_stream_data(0x36, ...)`.
Per-level linked lists at `level * 4 + (-0x5499)`.
Free list head at `0xABA7/0xABA9`.
Next-pointer chain at offsets +0x32/+0x34.

| Offset | Size | Type | Name | Description |
|--------|------|------|------|-------------|
| 0x00 | 1 | char | `attack_char` | Attack type identifier; copied from template byte 0. Checked for special types: 'V' (vampire), 'F' (fairy), 'H' (huorn) |
| 0x01 | 1 | char | `visible_char` | Character drawn on map. Initially = `attack_char`. Changes during confusion/shapeshift |
| 0x02 | 2 | int16 | `template_index` | Index into monster template table. Used for kill counts (`index * 2 + -0x460b`) |
| 0x04 | 2 | int16 | `original_template_index` | Backup of template_index; restored on shapeshift reveal. Used for name display |
| 0x06 | 2 | int16 | `experience_value` | XP granted on kill. Complex formula adds to player XP |
| 0x08 | 2 | int16 | `to_hit` | Attack bonus. Combat formula: `to_hit - player_level - base_ac + 1 + random` |
| 0x0A | 2 | int16 | `hit_points` | Current HP. Regenerates over time (checked against 500/350/150/100 thresholds) |
| 0x0C | 2 | int16 | `armor_class` | Defense value. Used with `to_hit` in combat: `to_hit + armor_class` |
| 0x0E | 2 | int16 | `num_attacks` | Number of attacks per round. Loop count for damage dealing |
| 0x10 | 2 | int16 | `damage_per_attack` | Max damage per hit. Actual: `random_mod(damage_per_attack)` |
| 0x12 | 2 | int16 | `level` | Monster difficulty level. If > 9, adds +10 speed bonus |
| 0x14 | 2 | int16 | `speed_bonus` | Random factor in to-hit. `random_mod(speed_bonus)` added to attack roll |
| 0x16 | 2 | int16 | `item_drop_chance` | Chance denominator for carrying item. `random_mod(chance) == 0` → has item |
| 0x18 | 2 | int16 | `item_drop_type` | Item type parameter for dropped item generation |
| 0x1A | 2 | int16 | `special_ability_1` | Special ability flag from template |
| 0x1C | 2 | int16 | `y_position` | Map row. Set by `find_random_empty_floor_space`. Updated during movement |
| 0x1E | 2 | int16 | `x_position` | Map column. Paired with y_position. Map access: `y * MAP_WIDTH + x` |
| 0x20 | 2 | int16 | `status_timer` | Countdown timer (flee/sleep duration). Decremented each turn; clears flags when 0. Eye of Sauron: -1 (0xFFFF) |
| 0x22 | 1 | char | `is_fleeing` | Flee flag. When set, monster moves away from player instead of toward |
| 0x23 | 1 | char | `is_visible` | Visibility to player. Controls whether monster is rendered on screen |
| 0x24 | 1 | char | `is_awake` | Active/alert flag. Eye of Sauron: always 1. Cleared when timer expires |
| 0x25 | 1 | char | `is_alerted` | Pursuit mode. Controls whether monster actively chases player |
| 0x26 | 1 | char | `move_toggle` | Toggles 0↔1 each turn. Implements half-speed movement (only moves when nonzero) |
| 0x27 | 1 | char | `is_invisible` | From template. If set, monster not drawn even when `is_visible = 1` |
| 0x28 | 1 | char | `is_hostile` | Aggression flag. Non-hostile (0) monsters skip attack behavior |
| 0x29 | 1 | char | `is_stationary` | Never-moves flag. If 0, can sense player without light |
| 0x2A | 2 | int16 | `stun_timer` | Paralysis countdown. Decremented each turn; monster can't act while > 0 |
| 0x2C | 2 | int16 | `unknown_2c` | Initialized to 1. Purpose unclear (multiplier or flag) |
| 0x2E | 2 | int16 | `carried_item_lo` | Far pointer (low word) to item carried by monster. Dropped on kill |
| 0x30 | 2 | int16 | `carried_item_hi` | Far pointer (high word) to carried item |
| 0x32 | 2 | int16 | `next_ptr_lo` | Far pointer (low word) to next monster in linked list |
| 0x34 | 2 | int16 | `next_ptr_hi` | Far pointer (high word) to next monster |

---

## 3. Monster Template Table (0x2A = 42 bytes each)

Base address formula: `template_index * 0x2A + (-0x5007)`

| Template Offset | Monster Field | Field Name |
|-----------------|--------------|------------|
| +0 | 0x00 | `attack_char` (display character) |
| +1..+2 | 0x06 | `experience_value` |
| +3..+4 | 0x08 | `to_hit` |
| +5..+6 | 0x0A | `hit_points` |
| +7..+8 | 0x0C | `armor_class` |
| +9..+10 | 0x0E | `num_attacks` |
| +11..+12 | 0x10 | `damage_per_attack` |
| +13..+14 | 0x14 | `speed_bonus` |
| +15..+16 | 0x12 | `level` |
| +17..+18 | 0x16 | `item_drop_chance` |
| +19..+20 | 0x18 | `item_drop_type` |
| +21..+22 | 0x1A | `special_ability_1` |
| +23 | 0x27 | `is_invisible` |
| +24 | 0x28 | `is_hostile` |
| +25 | 0x29 | `is_stationary` |

---

## 4. Item Object Structure (0x1A = 26 bytes)

Allocated by `allocate_item_object` with `read_stream_data(0x1a, ...)`.
Per-level ground item lists at `level * 4 + (-0x54D9)`.
Player inventory linked list head at `0xB91E`.
Free list head at `0xABAB/0xABAD`.
Next-pointer chain at offsets +0x16/+0x18.

| Offset | Size | Type | Name | Description |
|--------|------|------|------|-------------|
| 0x00 | 1 | char | `item_type` | Type: 0=gold, 1=food, 2=potion, 3=scroll, 4=wand, 5=?, 6=equipment, 7=weapon, 8=light_source |
| 0x01 | 2 | int16 | `subtype` | Sub-ID within type. Indexes identification tables: `type * 0x18 + subtype` |
| 0x03 | 2 | int16 | `quantity` | Stack count. Init=1. Incremented when stacking: `dest.qty += src.qty` |
| 0x05 | 2 | int16 | `y_position` | Map row (ground items only). Set to player_y on drop |
| 0x07 | 2 | int16 | `x_position` | Map column. Map access: `y * MAP_WIDTH + x` |
| 0x09 | 2 | int16 | `power` | Bonus/charges/value. Equipment: defense bonus. Wands: charges. Weapons: attack bonus. Negative = cursed |
| 0x0B | 2 | int16 | `weight` | Encumbrance value. Added/removed from `carried_weight` (0xB8C4) on pickup/drop |
| 0x0D | 4 | int32 | `gold_value` | Monetary value (32-bit). Mainly for gold and treasures |
| 0x11 | 2 | int16 | `unique_id` | Serial number for unique items. `index * 0x10 + (-0x5629)` indexes name table. Used for stack matching |
| 0x13 | 1 | char | `is_identified` | 0=unidentified, nonzero=identified. Equipping auto-identifies |
| 0x14 | 1 | char | `is_cursed` | Cursed flag. Prevents unequipping. Set when `power` < 0 |
| 0x15 | 1 | char | `is_enchanted` | Enchant/rust-proof flag. Prevents acid damage to equipment |
| 0x16 | 2 | int16 | `next_ptr_lo` | Far pointer (low word) to next item in list |
| 0x18 | 2 | int16 | `next_ptr_hi` | Far pointer (high word) to next item |

### Item Type Values

| Type | Name | Display | Notes |
|------|------|---------|-------|
| 0 | Gold | `$` | `gold_value` field used for amount |
| 1 | Food | `:` | `power` = nutrition value |
| 2 | Potion | `•` | `subtype` selects effect; named by color until identified |
| 3 | Scroll | `?` | `subtype` selects effect |
| 4 | Wand | `/` | `power` = charges remaining; named by wood type |
| 5 | (unknown) | | |
| 6 | Equipment | `` | Shield, armor, rings. `subtype` 7=armor, 8=ring2, 9-11=ring1 |
| 7 | Weapon | `=` | `subtype` indexes weapon table at `subtype * 4 + (-0x6185)` |
| 8 | Light source | | `subtype` 0=lantern, 4=special. `power` = fuel remaining |

---

## 5. Player Data Block (0xB86c–0xB948)

### Core Stats

| Address | Size | Constant Name | Field | Init Value |
|---------|------|---------------|-------|------------|
| 0xB86C | word | `ADDR_PLAYER_Y` | Player row position | — |
| 0xB86E | word | `ADDR_PLAYER_X` | Player column position | — |
| 0xB870 | word | `ADDR_CURRENT_HP` | Current hit points | 1000 |
| 0xB872 | word | `ADDR_MAX_HP` | Maximum hit points | 1000 |
| 0xB874 | word | `ADDR_CURRENT_FOOD` | Current food level | — |
| 0xB876 | word | `ADDR_MAX_FOOD` | Maximum food level | — |
| 0xB878 | word | `ADDR_STRENGTH` | Strength (force) | — |
| 0xB87A | word | `ADDR_INTELLIGENCE` | Intelligence | — |

### Equipment-Derived Bonuses

| Address | Size | Constant Name | Field | Notes |
|---------|------|---------------|-------|-------|
| 0xB87C | word | `ADDR_WISDOM`* | Shield AC bonus | Zeroed when shield unequipped. *Misleading name — actually equipment bonus |
| 0xB87E | word | `ADDR_DEXTERITY`* | Armor AC bonus | Zeroed when armor unequipped. *Misleading name |
| 0xB880 | word | `ADDR_BASE_AC` | Total armor class | = shield_ac + armor_ac (computed at lines 671, 8308) |
| 0xB882 | word | `ADDR_CONSTITUTION`* | Weapon attack bonus | From `weapon_table[subtype] + item.power`. Capped at 10–13. *Misleading name |
| 0xB884 | word | — | Ring2 bonus | Set from ring2's `power` field (+9) |

### Combat/Progression

| Address | Size | Field | Init |
|---------|------|-------|------|
| 0xB886 | word | Experience points (`ADDR_EXPERIENCE`) | — |
| 0xB888 | word | Player level (`ADDR_PLAYER_LEVEL`) | 0x80 (128) |
| 0xB88A | word | Saved monster row | 0 |
| 0xB88C | word | Saved monster col | 0 |
| 0xB88E | word | Saved monster value | 0 |
| 0xB890 | word | HP regen timer | 5 (set to `(15-level)/2` on regen tick) |
| 0xB892 | word | Turn counter (`ADDR_TURN_COUNT`) | 1000 |

### Effect Pointers (far pointer pairs, low + high word)

| Address | Size | Field |
|---------|------|-------|
| 0xB894–0xB896 | dword | Effect pointer/flag |
| 0xB898–0xB89A | dword | Paralysis/speed effect flag |
| 0xB89C–0xB89E | dword | Effect flag |
| 0xB8A0–0xB8A2 | dword | Wand/spell effect active |
| 0xB8A4–0xB8A6 | dword | Active light source pointer (decrements `power` field each turn) |
| 0xB8A8–0xB8AA | dword | Effect flag |
| 0xB8B0–0xB8B2 | dword | Carried food item pointer |
| 0xB8B4–0xB8B6 | dword | Special combat flag (adds random bonus to hit when nonzero) |
| 0xB8B8–0xB8BA | dword | Weapon enchant flag |
| 0xB8BC–0xB8BE | dword | Monster position tracking flag |

### Inventory / Weight

| Address | Size | Field | Init |
|---------|------|-------|------|
| 0xB8C0 | word | Item count (total items carried) | 3 |
| 0xB8C2 | word | Distinct item stacks | 3 |
| 0xB8C4 | word | Current carry weight | 6 |
| 0xB8C6 | word | Max carry weight | 0x26 (38). Formula: `0x26 - (food * -2 + 0x20)`, min 0x0F |
| 0xB8C8 | word | Gold (low word) (`ADDR_GOLD_LOW`) | 0 |
| 0xB8CA | word | Gold (high word) (`ADDR_GOLD_HIGH`) | 0 |

### Timers and Counters

| Address | Size | Field | Init |
|---------|------|-------|------|
| 0xB8CC–0xB8CE | dword | Turn counter effect 1 | 1/0 |
| 0xB8D0–0xB8D6 | 4 words | Stat value pairs (death if negative) | — |
| 0xB8D8–0xB8DE | 4 words | More stat pairs (death if negative) | — |
| 0xB8E0–0xB8E2 | dword | Unknown timer | 1/0 |
| 0xB8E4–0xB8E6 | dword | Arrows/projectile count | 3/0 |

### Status Flags (single bytes)

| Address | Size | Field |
|---------|------|-------|
| 0xB8EC | byte | Is paralyzed |
| 0xB8ED | byte | Is blind |
| 0xB8EE | byte | Needs full screen redraw |
| 0xB8EF | byte | Speed boost active |
| 0xB8F0 | byte | Confusion lock |
| 0xB8F1 | byte | Status flag 1 (potion 19) |
| 0xB8F2 | byte | Is teleporting |
| 0xB8F3 | byte | Pass-through-walls (`ADDR_STATUS_FLAG_3`) |
| 0xB8F4 | byte | Unknown flag (init=1) |
| 0xB8F5 | byte | Status flag 5 (potion 21) |
| 0xB8F6 | byte | Wizard mode active |
| 0xB8F7 | byte | Is stunned |
| 0xB8F8 | byte | Teleport flag (`ADDR_TELEPORT_FLAG`) |

### Timed Effect Durations (words)

| Address | Size | Field |
|---------|------|-------|
| 0xB8F9 | word | Paralysis duration |
| 0xB8FB | word | Blindness duration |
| 0xB8FD | word | Detect monsters duration |
| 0xB8FF | word | Speed boost duration |
| 0xB901 | word | Hallucination duration |
| 0xB903 | word | Status timer 1 |
| 0xB905 | word | Teleport timer |
| 0xB907 | word | Status timer 3 |
| 0xB909 | word | Food depletion timer (`ADDR_FOOD_LEVEL`, init=3000) |
| 0xB90B | word | Status timer 5 |
| 0xB90D | word | Wizard mode duration |
| 0xB90F | word | Monster attack type (set to `value + 0x46`) |
| 0xB911 | word | Invisibility timer (`ADDR_EFFECT_TIMER_16`) |

### More Status Bytes

| Address | Size | Field |
|---------|------|-------|
| 0xB913 | byte | Hallucination active |
| 0xB914 | byte | Auto-search / stair detection flag |
| 0xB915 | byte | Is dying |
| 0xB916 | byte | Is hasted |
| 0xB917 | byte | Wizard/reveal mode (extensively checked, 20+ refs) |
| 0xB918 | byte | Has light source |
| 0xB919 | byte | Is confused |
| 0xB91A | word | Death countdown timer (`ADDR_DEATH_TIMER`) |
| 0xB91C | word | Haste duration |

### Equipment Slot Pointers (far pointers = low + high word)

| Address | Size | Constant Name | Field |
|---------|------|---------------|-------|
| 0xB91E–0xB920 | dword | `ADDR_INVENTORY_LIST` | Inventory linked list head |
| 0xB922–0xB924 | dword | `ADDR_WIELDED_WEAPON` | Current weapon |
| 0xB926–0xB928 | dword | `ADDR_EQUIPPED_SHIELD` | Shield slot |
| 0xB92A–0xB92C | dword | `ADDR_EQUIPPED_ARMOR` | Armor slot |
| 0xB92E–0xB930 | dword | `ADDR_EQUIPPED_RING1` | Ring slot 1 |
| 0xB932–0xB934 | dword | `ADDR_EQUIPPED_RING2` | Ring slot 2 |
| 0xB936 | word | — | Belt/quick-access item count (init=4, max=4) |
| 0xB948 | word | — | Unknown flag (zeroed at init) |

### String Buffers

| Address | Size | Field |
|---------|------|-------|
| 0xB84F | ~11 bytes | Player name (Pascal string, length-prefixed) |
| 0xB9C6 | 11 bytes | Monster name table entry |
| 0xB9ED | 9 bytes | Item/keyword search string |

---

## 6. Per-Level Arrays (0x78ED–0x79B0)

### Staircase Positions

**Stairs up** (array base 0x78ED):
```
upstair_row[level] = *(int16 *)(level * 4 + 0x78ED)
upstair_col[level] = *(int16 *)(level * 4 + 0x78EF)
```

**Stairs down** (array base 0x792D):
```
downstair_row[level] = *(int16 *)(level * 4 + 0x792D)
downstair_col[level] = *(int16 *)(level * 4 + 0x792F)
```

Generated: `row = random_mod(10) * 2 + 2`, `col = random_mod(0x26) * 2 + 2`

**Eye of Sauron position** (fixed addresses):

| Address | Field |
|---------|-------|
| 0x78F1 | Eye of Sauron row |
| 0x78F3 | Eye of Sauron column |

### Level Flags and Counters

**Level visited flags** (array base 0x796D):
```
level_visited[level] = *(byte *)(level + 0x796D)
```

**Monster count per level** (array base 0x797D):
```
monster_count[level] = *(int16 *)(level * 2 + 0x797D)
```
Max 25 (0x19) per level.

**Item/treasure count per level** (array base 0x799B):
```
item_count[level] = *(int16 *)(level * 2 + 0x799B)
```

### Other Per-Level Arrays

| Base Formula | Size | Description |
|-------------|------|-------------|
| `level * 4 + (-0x5499)` | dword | Monster linked list head per level |
| `level * 4 + (-0x54D9)` | dword | Item linked list head per level |
| `level * 4 + (-0x476C)` | dword | Level init data (zeroed for levels 1–10) |
| `slot * 4 + (-0x46CC)` | dword | Belt/quick-access item pointers (4 slots) |
| `type * 4 + (-0x4738)` | dword | Per-item-type count table (9 types, 0–8) |

---

## 7. Game State Variables (0xE52D–0xE554)

| Address | Size | Constant Name | Field | Init |
|---------|------|---------------|-------|------|
| 0xE52D | word | `ADDR_DUNGEON_LEVEL` | Current dungeon level (1–15) | 1 |
| 0xE52F | word | — | Monsters killed total | 0 |
| 0xE531 | word | — | Items consumed/used total | 0 |
| 0xE533 | word | — | Spawn cycle counter | 1 |
| 0xE535 | word | `ADDR_MIN_VISIBLE_ROW` | Top row of visible area | — |
| 0xE537 | word | `ADDR_MAX_VISIBLE_ROW` | Bottom row of visible area | — |
| 0xE539 | byte | — | Detect monsters active | 1 |

---

## 8. Object System Linked Lists (0xABxx)

All are far pointers (low word + high word = 4 bytes).

| Address | Pair | Field | Stride |
|---------|------|-------|--------|
| 0xABA7–0xABA9 | lo/hi | Monster free list head | 0x36 (54 bytes per monster) |
| 0xABAB–0xABAD | lo/hi | Item free list head | 0x1A (26 bytes per item) |
| 0xABAF–0xABB1 | lo/hi | Active projectile/special item pointer | — |
| 0xAB8F–0xAB91 | lo/hi | Object pointer (general) | — |
| 0xAB9F–0xABA1 | lo/hi | Dungeon object pointer 1 | — |
| 0xABA3–0xABA5 | lo/hi | Dungeon object pointer 2 | — |

---

## 9. Message Buffers (0xB72F–0xB84F)

Eight 32-byte message buffers for status line / combat messages:

| Address | Buffer # | Primary Use |
|---------|----------|-------------|
| 0xB72F | 1 | `pad_and_copy_buffer` output |
| 0xB74F | 2 | Secondary message |
| 0xB76F | 3 | **Primary message line** (most frequent — combat, movement, item use) |
| 0xB78F | 4 | Message line 4 |
| 0xB7AF | 5 | Message line 5 |
| 0xB7CF | 6 | Secondary message line (combat details, item descriptions) |
| 0xB80F | 7 | Equipment/stats display |
| 0xB82F | 8 | File/data operations |

---

## 10. High Score Entry (0x18 = 24 bytes)

Stored at base formula: `entry * 0x18 + (-0x45DB)`. Up to 15 entries.

| Offset | Size | Field |
|--------|------|-------|
| 0x00 | ~16 bytes | Player name (Pascal string) |
| 0x10 | 2 | Level reached |
| 0x12 | 4 | Score (32-bit) |
| 0x16 | 1 | Victory type ('g' = special) |

---

## 11. Video/Terminal System (0xE53A–0xE554)

| Address | Size | Field |
|---------|------|-------|
| 0xE53A | byte | Video init flag (set to 1) |
| 0xE53B | byte | Cursor visibility flag |
| 0xE53C | byte | Window active flag |
| 0xE53D | byte | Window parameter |
| 0xE53E | word | Window dimension |
| 0xE540 | byte | Current video attribute (text color/background) |
| 0xE541 | byte | Window left column (scroll region) |
| 0xE542 | byte | Window top row |
| 0xE543 | byte | Window right column / max column |
| 0xE544 | byte | Window bottom row / max row |
| 0xE54F | word | Window size parameter |
| 0xE551 | byte | Saved video attribute (backup) |
| 0xE552 | byte | Pending character buffer |
| 0xE553 | byte | Character available flag |
| 0xE554 | 32+ bytes | File Control Block (FCB) for save/load |

---

## 12. DOS Runtime / Heap (0xE754–0xE78B)

| Address | Size | Field |
|---------|------|-------|
| 0xE75A–0xE75C | dword | Heap free list pointer |
| 0xE75E–0xE762 | dword | Current heap allocation pointer |
| 0xE760 | word | Heap top / memory limit |
| 0xE764–0xE766 | dword | Function pointer / interrupt vector |
| 0xE768–0xE76A | dword | Error handler function pointer |
| 0xE76C | word | Return value AX |
| 0xE76E | word | Return value stack[0] |
| 0xE770 | word | Return value stack[2] |
| 0xE772–0xE774 | dword | Random number seed (low/high) |
| 0xE776–0xE788 | 7 × dword | Saved register pairs (BX/ES for interrupt handlers) |
| 0xE78A | word | System flag (init=2) |
| 0xE78B | word | I/O error code / file operation result |

---

## Summary Statistics

- **~120 unique memory addresses** used as direct memory accesses
- **31 named ADDR_ constants** defined in `moria_constants.h`
- **3 additional ADDR_ names** in code but absent from header (WISDOM, DEXTERITY, CONSTITUTION — actually equipment bonuses)
- **Monster object**: 54 bytes, 27 fields, linked list at +0x32
- **Item object**: 26 bytes, 15 fields, linked list at +0x16
- **Player data block**: ~220 bytes (0xB86C–0xB948)
- **Map buffer**: 3 layers (tile, overlay, visibility), 79×23 per level
- **Per-level arrays**: stair positions, monster/item counts, linked list heads
