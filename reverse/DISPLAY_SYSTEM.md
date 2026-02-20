# MORIA Display System

Reverse-engineered from `MORIA_with_constants.C` (DOS MORIA 1.9.8.7 French).

## Table of Contents

1. [Screen Layout](#1-screen-layout)
2. [put_char_at_pos — Drawing Characters](#2-put_char_at_pos--drawing-characters)
3. [Display Character Table — Item Type to Glyph](#3-display-character-table--item-type-to-glyph)
4. [Fog of War / Explored Map](#4-fog-of-war--explored-map)
5. [explore_tile_at_position — Tile Rendering Logic](#5-explore_tile_at_position--tile-rendering-logic)
6. [render_field_of_view — The FOV Algorithm](#6-render_field_of_view--the-fov-algorithm)
7. [redraw_dungeon_level — Full Screen Redraw](#7-redraw_dungeon_level--full-screen-redraw)
8. [redraw_screen_map — Wizard Mode Full Map](#8-redraw_screen_map--wizard-mode-full-map)
9. [display_character_stats — Status Bar](#9-display_character_stats--status-bar)
10. [display_food_status — Weapon Attack Cap](#10-display_food_status--weapon-attack-cap)
11. [draw_game_hud — Character Sheet HUD](#11-draw_game_hud--character-sheet-hud)
12. [display_object_info — Item Description](#12-display_object_info--item-description)

---

## 1. Screen Layout

The DOS 80×25 text mode screen is divided as:

```
Row 1–24 (0-indexed: 0–23):  Dungeon map (MAP_WIDTH=79 cols × 23 rows)
Row 25 (0-indexed: 24):      Status bar
```

DOS `gotoxy` is 1-indexed. The C code uses `validate_window_coords(row, col)` where row 1 = top of screen. The dungeon map occupies rows 1–24 (but effectively rows 2–24 for dungeon tiles, with row 1 sometimes used for messages). The status bar is at row 25 (0x19).

### Map Buffer Access

Three layers per map cell:

| Layer | Formula | Description |
|-------|---------|-------------|
| Tile | `buf + row * 79 + col - 0x50` | Dungeon geometry (walls, floors, items) |
| Monster overlay | `row * 79 + col - 0x0C` | Monster display chars (global, not per-level) |
| Explored flags | `level * 0x719 + row * 79 + col + 0x70D` | Per-level fog of war (0=unexplored, 1=explored) |

Where `buf = map_buffer_ptr[dungeon_level]` (at `dungeon_level * 4 + 4`).

---

## 2. put_char_at_pos — Drawing Characters

**Line 283.** Low-level function to draw a single character at a map position.

```
function put_char_at_pos(char: byte, col: int, row: int):
    saved_y = get_cursor_y()
    saved_x = get_cursor_x()
    gotoxy(col, row + 1)             // +1: map row → screen row
    write_byte(char)
    flush()
    gotoxy(saved_x, saved_y)        // restore cursor position
```

The `row + 1` offset converts 0-based map coordinates to 1-based screen coordinates (row 0 of map = screen row 1, but tiles start at screen row 2 in practice).

---

## 3. Display Character Table — Item Type to Glyph

**`lookup_table_b9c7` (line 305)** maps item type to its display character on the map.

```
function lookup_table_b9c7(item: ItemObject*) -> byte:
    return display_char_table[item.item_type]
    // table at DS-relative: item_type + (-0x4639) = item_type + 0xB9C7
```

Extracted from memory dump at `CS:0xB9C7`:

| Type | Value | CP437 Hex | Glyph | Description |
|------|-------|-----------|-------|-------------|
| 0 | Gold | 0x24 | `$` | Gold pile |
| 1 | Food | 0x3A | `:` | Food ration |
| 2 | Potion | 0xAD | `¡` | Potion (CP437 inverted !) |
| 3 | Scroll | 0x3F | `?` | Scroll |
| 4 | Ring | 0xF8 | `°` | Ring (degree symbol) |
| 5 | Gem | 0x2F | `/` | Gem/wand |
| 6 | Equipment | 0x7F | `⌂` | Armor/shield (CP437 0x7F = house) |
| 7 | Weapon | 0x3D | `=` | Weapon |
| 8 | Light | 0x0F | `☼` | Light source (CP437 sun) |
| 9 | Silmaril | 0xEF | `∩` | The Silmaril (CP437 intersection) |

The table has 11 entries (`0xB9C6` = count = 11, types 0–10).

### Tile Characters (CP437)

| Hex | Glyph | Meaning |
|-----|-------|---------|
| 0x20 | (space) | Empty floor / corridor |
| 0xB3 | `│` | Vertical wall |
| 0xB4 | `┤` | Room left wall |
| 0xC1 | `┴` | Room top wall |
| 0xC2 | `┬` | Room bottom wall |
| 0xC3 | `├` | Room right wall |
| 0xC4 | `─` | Horizontal wall |
| 0xC5 | `┼` | Wall intersection |
| 0xDA | `┌` | Top-left corner |
| 0xBF | `┐` | Top-right corner |
| 0xC0 | `└` | Bottom-left corner |
| 0xD9 | `┘` | Bottom-right corner |
| 0x02 | `☻` | Player character (normal mode) |
| 0x7E | `~` | Player character (wizard mode) |

### Monster Characters

Monsters use their `visible_char` field (offset +0x01 in the monster object). This is the same as `attack_char` by default, but can change during confusion/shapeshift.

---

## 4. Fog of War / Explored Map

### Data Structure

Per-level boolean array (1 byte per tile):

```
explored[level][row][col] = *(level * 0x719 + row * MAP_WIDTH + col + 0x70D)
// 0x719 = 1817 = 23 rows × 79 cols per level
```

- `0` = tile never seen (draws as blank)
- `1` = tile previously seen (draws dimmed / green)

### Behavior

1. **When exploring a tile** (`explore_tile_at_position`): sets `explored[level][row][col] = 1`
2. **When redrawing** (`redraw_dungeon_level`): explored-but-not-currently-visible tiles are drawn with color attribute **10** (bright green on black). Currently visible tiles are drawn with normal attribute **15** (bright white on black).
3. **Explored tiles persist** when the player returns to a previously visited level.
4. **The `needs_full_update` flag** (set during teleportation or level change) triggers a complete FOV recalculation without setting explored flags, to avoid marking the entire map as seen.

---

## 5. explore_tile_at_position — Tile Rendering Logic

**Line 723.** Called by `render_field_of_view` for each tile within the visible radius. Determines what to draw at a given (col, row) position.

```
function explore_tile_at_position(stack_frame, col: int, row: int):
    // Bounds check (when teleporting, check against screen offsets)
    if is_teleporting and not is_position_in_bounds(col, row):
        return

    tile_overlay = monster_overlay[row * MAP_WIDTH + col]

    if tile_overlay == ' ':
        // ═══ NO MONSTER HERE — draw the map tile ═══

        // Already explored? Check explored flag
        if explored[level][row][col] != 0:
            tile = tile_map[row][col]
            // Check if tile is a "wall" type (uses bitmask against wall set)
            if tile is in wall_set and not is_teleporting and not needs_full_update:
                return  // wall already drawn, skip

        // Mark as explored (unless doing full update)
        if not needs_full_update:
            explored[level][row][col] = 1

        tile = tile_map[row][col]

        // Check if tile is a special char (not space, not player, not stairs)
        if tile is not in {' ', 0x01, 0x03}:
            if not confusion_lock:
                // Normal rendering: draw the tile character
                gotoxy(col + x_offset, row + y_offset + 1)
                write_byte(tile)
            else:
                // HALLUCINATION: draw a random character!
                gotoxy(col + x_offset, row + y_offset + 1)
                random_type = random_mod(total_entity_types)
                write_byte(display_char_table[random_type])
        else:
            // Tile is on floor — check for traps/items
            if tile != ' ':
                // Parse numeric value, check belt for trap detection item
                trap_value = parse_tile_as_number(tile)
                for slot = 1 to belt_slot_count:
                    if belt[slot] != NULL
                            and belt[slot].subtype == 10  // trap detection
                            and belt[slot].power > 0:
                        found_trap_detector = belt[slot]
                if found_trap_detector != NULL:
                    found_trap_detector.power -= 1
                    // Replace map tile with decoded trap symbol
                    tile_map[row][col] = trap_table[trap_value * 2 - 2]

    else:
        // ═══ MONSTER HERE — draw the monster ═══
        find_monster_at_coords(col, row) -> monster

        if monster.is_invisible == 0:
            // Draw monster's visible character
            gotoxy(col + x_offset, row + y_offset + 1)
            write_byte(monster.visible_char)

        // Mark monster as visible to player
        monster.is_visible = 1
```

**Key details**:
- Tile overlay ≠ space means a monster is present at that position.
- Invisible monsters (`is_invisible = 1`) are NOT drawn but still marked as "visible" (for AI purposes).
- During hallucination (`confusion_lock`), all non-wall tiles show as random item-type characters.
- Trap tiles have numeric values that decode to trap symbols when the player has a trap-detection ring equipped.

---

## 6. render_field_of_view — The FOV Algorithm

**Line 854.** The core visibility algorithm. **NOT raycasting and NOT shadowcasting.** It uses a **cross-shaped axial scan** plus an optional **lamp square**.

```
function render_field_of_view():
    if is_blind:
        return                          // blind = see nothing

    save_cursor_position()
    light_radius = player_level + 5     // visibility range grows with level

    // Teleport mode: offset calculation for centered view
    if is_teleporting:
        y_offset = 12 - player_y        // center on row 12
        x_offset = 39 - player_x        // center on col 39
    else:
        y_offset = 0
        x_offset = 0

    // ═══ PHASE 0: CLEAR PREVIOUSLY VISIBLE ROWS ═══
    if is_teleporting:
        // Clear rows outside new visible range
        for row = min_visible_row - 1 to max_visible_row + 1:
            if row is within screen bounds:
                gotoxy(1, row + 13 - player_y)
                clear_to_end_of_line()
    else if needs_full_update:
        // Clear all rows in current visible range
        for row = min_visible_row to max_visible_row:
            gotoxy(1, row + 1)
            clear_to_end_of_line()

    // ═══ PHASE 1: SCAN UPWARD (north) ═══
    row = player_y
    do:
        row -= 1
        for col_offset = -1 to 1:       // explore 3 tiles wide
            explore_tile_at_position(col_offset + player_x, row)
        tile = tile_map[row][player_x]
    while tile is in floor_set            // stop at wall
          and player_y - row < light_radius
    min_visible_row = row

    // ═══ PHASE 2: SCAN DOWNWARD (south) ═══
    row = player_y
    do:
        row += 1
        for col_offset = -1 to 1:
            explore_tile_at_position(col_offset + player_x, row)
        tile = tile_map[row][player_x]
    while tile is in floor_set
          and row - player_y < light_radius
    max_visible_row = row

    // ═══ PHASE 3: SCAN LEFT (west) ═══
    col = player_x
    do:
        col -= 1
        for row_offset = -1 to 1:
            explore_tile_at_position(col, player_y + row_offset)
        tile = tile_map[player_y][col]
    while tile is in floor_set
          and player_x - col < light_radius

    // ═══ PHASE 4: SCAN RIGHT (east) ═══
    col = player_x
    do:
        col += 1
        for row_offset = -1 to 1:
            explore_tile_at_position(col, player_y + row_offset)
        tile = tile_map[player_y][col]
    while tile is in floor_set
          and col - player_x < light_radius

    // ═══ PHASE 5: LAMP LIGHT (5×5 square) ═══
    has_lamp = check_inventory_has_item(ITEM_LAMP)
    if has_lamp:
        for row = player_y - 2 to player_y + 2:
            for col = player_x - 2 to player_x + 2:
                // Skip the immediate 3×3 center (already explored by axes)
                if abs(row - player_y) < 2 and abs(col - player_x) < 2:
                    continue
                explore_tile_at_position(col, row)

    // ═══ PHASE 6: DRAW PLAYER CHARACTER ═══
    screen_row = player_y + y_offset
    screen_col = player_x + x_offset
    if is_wizard:
        put_char_at_pos(0x7E, screen_col, screen_row)   // '~'
    else:
        put_char_at_pos(0x02, screen_col, screen_row)   // '☻'

    restore_cursor_position()
```

### FOV Algorithm Summary

The MORIA FOV is a **simple cross + lamp** algorithm:

```
        ···
        ···
        ···
   ···LLLLLLL···
   ···LL☻LL···
   ···LLLLLLL···
        ···
        ···
        ···
```

Where:
- `·` = axial scan (3 tiles wide, extends up to `player_level + 5` in each cardinal direction)
- `L` = lamp light (5×5 square around player, only if lamp equipped)
- `☻` = player

Each axial ray stops when it hits a **wall** (any non-floor tile on the center column/row). The ray explores a 3-tile-wide band centered on the player's row/column.

**This means diagonal vision is extremely limited** — the player can only see diagonally within the 5×5 lamp area. Without a lamp, diagonal tiles are invisible. This is characteristic of old dungeon crawlers with cardinal-only movement.

### Light Radius

```
light_radius = player_level + 5
```

At level 1: radius 6. At level 15: radius 20 (can see most of the map vertically).

### Wall Stopping

Each axis scan stops when the **center tile** of the 3-wide band is not in the "floor set" (i.e., is a wall). The stopping wall itself IS explored (the `do...while` loop explores before testing). So walls are visible but block further vision.

---

## 7. redraw_dungeon_level — Full Screen Redraw

**Line 1064.** Called on level change, teleportation, or screen refresh.

```
function redraw_dungeon_level(max_row: int):
    // Phase 1: Clear screen rows
    if max_row >= 0:
        for row = 0 to max_row:
            gotoxy(1, row + 1)
            clear_to_end_of_line()

    // Phase 2: Check if full FOV recalculation needed
    if is_teleporting or needs_full_update or is_blind or max_row < 1:
        goto RENDER_FOV

    // Phase 3: Redraw explored tiles with color coding
    for row = 1 to max_row:
        for col = 1 to MAP_WIDTH:
            tile = tile_map[row][col]

            if explored[level][row][col] == 0:
                // Not explored: check if it's a "special" tile to dim-draw
                if map_has_been_generated:
                    // Tile is a wall type in explored-adjacent bitmask?
                    if tile is in wall_or_special_set:
                        set_text_color(10)    // bright green (dimmed)
                        gotoxy(col, row + 1)
                        write_byte(tile)
                        set_text_color(15)    // restore white
            else:
                // Explored: check if it's a visible character
                if tile not in {' ', 0x01, 0x03}:
                    // Draw the tile normally
                    gotoxy(col, row + 1)
                    write_byte(tile)

    // Phase 4: Render FOV
    RENDER_FOV:
    display_character_stats()

    if is_teleporting:
        // Teleport mode: just draw player at screen center (row 13, col 40)
        put_char_at_pos(0x02, 0x27, 0x0C)
    else:
        render_field_of_view()
```

**Key details**:
- `max_row` parameter controls how many rows to clear/redraw. Typically 0x17 (23) for a full redraw.
- Explored-but-not-visible tiles are drawn in **color 10** (bright green foreground, black background) — this is the "memory" effect, showing dungeon geometry the player has seen before.
- Currently visible tiles (within FOV) are drawn by `render_field_of_view` in the default color 15 (bright white).

---

## 8. redraw_screen_map — Wizard Mode Full Map

**Line 5220.** Draws every non-space tile on the entire map. Used for the map scroll (`parchemin topographique`) and wizard debug mode.

```
function redraw_screen_map():
    for row = 1 to 23:                  // 0x17 = 23
        for col = 1 to MAP_WIDTH:        // 79
            tile = tile_map[row][col]
            if tile != ' ':
                gotoxy(col, row + 1)
                write_byte(tile)
```

Simple brute-force: draws every non-space tile without any fog-of-war or visibility checks. Also called after the topographic scroll effect (message ID 9, `parchemin topographique`) to reveal the full map.

---

## 9. display_character_stats — Status Bar

**Line 223.** Renders the bottom status line at screen row 25.

### Extracted Label Strings

From code segment at `CS:0x1000`:

| Address | Length | Text |
|---------|--------|------|
| 0x0261 | 4 | `Niv ` |
| 0x0266 | 3 | ` Or` |
| 0x026A | 5 | `   PV` |
| 0x0270 | 6 | `   Int` |
| 0x0277 | 6 | `   Dex` |
| 0x027E | 6 | `   For` |
| 0x0285 | 5 | `   CA` |
| 0x028B | 2 | ` +` |
| 0x028E | 7 | `   Exp ` |

### Pseudocode

```
function display_character_stats():
    save_cursor_position()
    gotoxy(1, 25)                       // row 25 = status bar

    print "Niv "                        // Niveau (level)
    print_number(2, dungeon_level)

    print " Or"                         // Or (gold)
    print_number(6, gold)

    print "   PV"                       // Points de Vie (HP)
    print_number(4, current_hp)
    print "/"
    print_number(3, max_hp)

    print "   Int"                      // Intelligence
    print_number(3, intelligence)

    print "   Dex"                      // Dextérité
    print_number(3, strength)           // NOTE: variable name in C is 'strength'
                                        // but label says 'Dex' — see note below

    print "   For"                      // Force (strength)
    print_number(3, current_food)       // NOTE: variable is 'current_food'
                                        // but label says 'For' — see note below

    print "   CA"                       // Classe d'Armure (AC)
    if base_ac < 1:
        print " "                       // space for negative/zero AC
    else:
        print " +"                      // plus sign for positive AC
    print_number(1, base_ac)

    print "   Exp "                     // Expérience
    print_number(2, player_level)
    print "/"
    print_number(4, experience)

    flush_screen()
    restore_cursor_position()
```

### Status Bar Format

```
Niv NN Or NNNNNN   PVNNNN/NNN   IntNNN   DexNNN   ForNNN   CA +N   Exp NN/NNNN
```

Example at level 3, 150 gold, 45/50 HP, INT 12, DEX 15, STR 100, AC 3, level 5/2400 XP:
```
Niv  3 Or   150   PV  45/ 50   Int 12   Dex 15   For100   CA +3   Exp  5/2400
```

**Note on stat labels**: The C code prints `intelligence` under "Int", `strength` under "Dex", and `current_food` under "For". This confirms the original game has only 3 stats but the label ordering in the status bar is **Int / Dex / For** displaying **intelligence / strength / food** respectively. The "For" (Force) position actually shows food level, acting as a hunger meter disguised under the strength label.

---

## 10. display_food_status — Weapon Attack Cap

**Line 1940.** Despite its name, this function caps the weapon attack bonus based on weapon subtype.

```
function display_food_status():
    weapon_subtype = wielded_weapon.subtype

    if weapon_subtype in range(9, 14):  // subtypes 9–13 (axes, bows, special)
        if weapon_attack_bonus > 10:
            weapon_attack_bonus = 10    // cap at 10
    else:
        if weapon_attack_bonus > 13:
            weapon_attack_bonus = 13    // cap at 13
```

This is NOT actually a display function — it's a stat-capping function called after equipping a weapon. The cap depends on weapon subtype:
- Subtypes 9–13 (axes, bows, arrows, elfin daggers, special swords): max attack bonus = **10**
- All other subtypes (daggers, swords, lances, maces, etc.): max attack bonus = **13**

---

## 11. draw_game_hud — Character Sheet HUD

**Line 3873.** Draws a popup character information panel using double-line box-drawing characters. Displayed when the player presses `c` (fiche de personnage).

### HUD Layout

The HUD is drawn in a box at columns 18–62 (0x12–0x3E), rows 1–15:

```
╔═══════════════════════════════════════════╗    Row 1
║                                           ║    Row 2 (player name, centered)
║                                           ║    Row 3
║                                           ║    Row 4
╠═══════════════╤═══════════════════════════╣    Row 5 (divider)
║ Niveau      :       │ Expérience  :       ║    Row 6
╟───────────────┼───────────────────────────╢    Row 7
║ Pts de vie  :       │ Maxvie      :       ║    Row 8
╟───────────────┼───────────────────────────╢    Row 9
║ Force       :       │ Maxforce    :       ║    Row 10
╟───────────────┼───────────────────────────╢    Row 11
║ Dextérité   :       │ Intelligence:       ║    Row 12
╟───────────────┼───────────────────────────╢    Row 13
║ Or          :       │ C A         :       ║    Row 14
╚═══════════════╧═══════════════════════════╝    Row 15
```

### CP437 Box Drawing Characters Used

| Hex | Glyph | Position |
|-----|-------|----------|
| 0xC9 | `╔` | Top-left |
| 0xBB | `╗` | Top-right |
| 0xC8 | `╚` | Bottom-left (0xBC) |
| 0xBC | `╝` | Bottom-right |
| 0xCD | `═` | Double horizontal |
| 0xBA | `║` | Double vertical |
| 0xCC | `╠` | Double T-left |
| 0xB9 | `╣` | Double T-right |
| 0xD1 | `╤` | Double-horiz single-vert down |
| 0xCF | `╧` | Double-horiz single-vert up |
| 0xC7 | `╟` | Single-horiz double-vert left |
| 0xB6 | `╢` | Single-horiz double-vert right |
| 0xC4 | `─` | Single horizontal |
| 0xC5 | `┼` | Single cross |

### Pseudocode

```
function draw_game_hud():
    clear_screen()

    // Draw the double-line box frame (rows 1–15, cols 18–62)
    draw_top_border()       // ╔═══...═══╗
    draw_empty_rows(2-4)    // ║ (spaces with blue bg) ║
    draw_divider_row(5)     // ╠═══╤═══╣
    draw_label_row(6)       // ║ Niveau : _ │ Expérience : _ ║
    draw_separator(7)       // ╟───┼───╢
    draw_label_row(8)       // ║ Pts de vie : _ │ Maxvie : _ ║
    draw_separator(9)
    draw_label_row(10)      // ║ Force : _ │ Maxforce : _ ║
    draw_separator(11)
    draw_label_row(12)      // ║ Dextérité : _ │ Intelligence : _ ║
    draw_separator(13)
    draw_label_row(14)      // ║ Or : _ │ C A : _ ║
    draw_bottom_border(15)  // ╚═══╧═══╝

    // Fill in player name (centered in row 3, blue background)
    set_background_color(BLUE)
    name_col = 40 - strlen(player_name) / 2
    gotoxy(name_col, 3)
    print(player_name)
    set_background_color(BLACK)

    // Fill in stat values (right-aligned in each cell)
    gotoxy(34, 6):  print(player_level)
    gotoxy(56, 6):  print(experience)
    gotoxy(34, 8):  print(current_hp)
    gotoxy(56, 8):  print(max_hp)
    gotoxy(34, 10): print(current_food)  // labeled "Force"
    gotoxy(56, 10): print(max_food)      // labeled "Maxforce"
    gotoxy(34, 12): print(strength)      // labeled "Dextérité"
    gotoxy(56, 12): print(intelligence)
    gotoxy(34, 14): print(gold)          // labeled "Or"
    gotoxy(56, 14): print(base_ac)       // labeled "C A"

    // Wait for keypress, then redraw dungeon
    gotoxy(65, 25)
    wait_for_space()
    redraw_dungeon_level(0x17)
```

### HUD Values Summary

| Row | Left Label | Left Value | Right Label | Right Value |
|-----|-----------|------------|-------------|-------------|
| 6 | Niveau | `player_level` | Expérience | `experience` |
| 8 | Pts de vie | `current_hp` | Maxvie | `max_hp` |
| 10 | Force | `current_food` | Maxforce | `max_food` |
| 12 | Dextérité | `strength` | Intelligence | `intelligence` |
| 14 | Or | `gold` | C A | `base_ac` |

**Note**: "Force" displays `current_food` and "Dextérité" displays `strength`. This matches the status bar behavior — the 3 stats are internally: intelligence, strength (displayed as "Dex"), and food/hunger (displayed as "For").

---

## 12. display_object_info — Item Description

**Line 4383.** Complex function that generates the text description of an item based on its type, identification state, and properties. Called whenever an item needs to be displayed to the player (pickup, drop, inventory, etc.).

### Parameters

- `param_1`: force_identify (show true name regardless of identification state)
- `param_2`: show_quantity (if nonzero and quantity > 1, show count)
- `flags`: pointer to the item object

### Name Resolution Tables

| Table | Address Formula | Description |
|-------|----------------|-------------|
| Effect name (identified) | `type * 0x2B8 + subtype * 0x1D + 0x75FA` | True item name (e.g., "de guérison") |
| User-assigned name | `type * 0x2B8 + subtype * 0x1D + (-0x75DE)` | Custom name entered by player |
| Type identification | `type * 0x18 + subtype + (-0x65A2)` | Has this type+subtype been discovered? |
| User-naming flag | `type * 0x18 + subtype + (-0x6542)` | Has player named this type+subtype? |
| Randomized appearance | `subtype * 0x10 + (-0x5CC9)` | Potion color name |
| Scroll appearance | `subtype * 0x1D + (-0x610E)` | Scroll gibberish name |
| Wand appearance | `subtype * 0x10 + (-0x5A19)` | Wand wood name |
| Gem appearance | `subtype * 0x10 + (-0x5789)` | Gem material name |
| Weapon/equip name | `type * 0x2B8 + subtype * 0x1D + 0x75FA` | True name (same as effect) |
| Unique item name | `unique_id * 0x10 + (-0x5629)` | Named unique item |

### Pseudocode

```
function display_object_info(force_id: bool, show_qty: bool, item: ItemObject*):
    plural = show_qty and item.quantity >= 2
    print_space()

    switch item.item_type:

    case 1 (FOOD):
        if plural: print(item.quantity)
        else: print("un")               // "a/one"
        print " ration"                  // msg 0x193
        print_plural_suffix()
        print " alimentaire"             // msg 0x194
        print_plural_suffix()

    case 2 (POTION):
        if plural: print(item.quantity)
        elif type == 2: print("un")      // masculine
        else: print("une")               // feminine
        if type == 2: print " potion"    // msg 0x196
        else: print " parchemin"         // msg 0x197
        print_plural_suffix()

        if type_identified[type][subtype] or force_id:
            // Show true name: "potion de guérison"
            print " "
            print effect_name[type][subtype]
            if type == 2:
                // Potion subtypes 6-13: show color in parentheses
                print " ("
                print color_name[subtype]
                print ")"
        elif user_named[type][subtype]:
            // Show user's custom name: "renommé(e) <name>"
            print " renommé"             // msg 0x198 or 0x199
            if type == 2: print "e"      // feminine suffix
            print_plural_suffix()
            print " "
            print user_name[type][subtype]
            if type == 2:
                // Also show color: "(rouge)"
                print " ("
                print color_name[subtype]
                print ")"
                print_plural_suffix()
        else:
            if type == 3 (SCROLL):
                // Show scroll title: "intitulé <gibberish>"
                print " intitulé"        // msg 0x199
                print_plural_suffix()
                print " "
                print scroll_name[subtype]
            else:
                // Show color: "potion rouge"
                print " "
                print color_name[subtype]
                print_plural_suffix()

    case 4 (RING):
        print "un anneau"                // msg 0x19A "a ring"
        if not type_identified and not force_id:
            if user_named:
                print " renommé "        // msg 0x19B
                print user_name
                print " ("
                print wand_wood_name[subtype]
                print ")"
            else:
                print " "
                print wand_wood_name[subtype]
        else:
            print " "
            print effect_name[type][subtype]
            // Show power bonus if identified
            if item.is_identified or force_id:
                if item.power < 0:
                    print_number(3, item.power)   // negative = cursed
                else:
                    print " +"
                    print_number(0, item.power)
            print " ("
            print wand_wood_name[subtype]
            print ")"
        // Show belt slot number if in belt
        for slot = 1 to belt_slot_count:
            if belt[slot] == item:
                print " ("
                print_number(0, slot)
                print ")"

    case 5 (GEM):
        print "une baguette"             // msg 0x19C "a wand"
        if not type_identified and not force_id:
            if user_named:
                print " renommée "       // msg 0x19D (feminine)
                print user_name
                print " ("
                print gem_name[subtype]
                print ")"
            else:
                print " "
                print gem_name[subtype]
        else:
            print " "
            print effect_name[type][subtype]
            // Show charges
            if item.is_identified or force_id:
                print " ("
                charges = abs(item.power)
                print_number(0, charges)
                print " charges)"
            print " ("
            print gem_name[subtype]
            print ")"

    case 6 (EQUIPMENT):
        // Equipment: check subtype for ring vs armor vs shield
        if subtype in [9, 10, 11]:        // rings
            if not item.is_identified:
                print "des gantelets"     // msg 0x1A8 "gauntlets"
            else:
                print effect_name[type][subtype]
            // ... show power, equipped status

        if subtype == 12 (ARROWS):
            print_number(0, item.quantity) // show count for arrows

        print effect_name[type][subtype]  // "une armure de cuir", etc.
        if item.quantity > 1:
            print_plural_suffix()

        if item.is_identified or force_id:
            if item.power < 0:
                print_number(3, item.power)
            else:
                print " +"
                print_number(0, item.power)

    case 7 (WEAPON):
        if subtype == 12:                 // arrows: show quantity
            print_number(0, item.quantity)
        print effect_name[type][subtype]  // "un poignard", "une épée", etc.
        if item.quantity > 1:
            print_plural_suffix()
        if item.is_identified or force_id:
            if item.power < 0:
                print_number(3, item.power)
            else:
                print " +"
                print_number(0, item.power)

    case 8 (LIGHT SOURCE):
        if subtype == 0:
            print "Un Silmaril"          // msg 0x19E (actually torch)
        else:
            // Named light source
            print unique_name[item.unique_id]
            if item.is_identified:
                print effect_name[type][subtype]
            if not item.is_cursed:
                print " (valeur "
                print_number(0, item.gold_value)
                print " or)"

    case 0 (GOLD):
        print_number(0, item.power)
        print " pièces d'or"             // msg 0x19F "gold coins"
```

### Description Examples

| Item State | Output |
|------------|--------|
| Unidentified red potion | `un potion rouge` |
| User-named red potion | `un potion renommée guérison (rouge)` |
| Identified healing potion | `un potion de guérison (rouge)` |
| Stack of 3 scrolls | `3 parchemins intitulé BLAH XYZZ` |
| Identified +2 sword | `une épée +2` |
| Cursed -1 armor | `une armure de cuir -1` |
| 15 arrows | `15 fleche` |
| 200 gold | `200 pièces d'or` |
| The Silmaril | `Un Silmaril` |

---

## Answers to Key Questions

### 1. What is the exact FOV algorithm?

**Cross-shaped axial scan + lamp square.** NOT raycasting, NOT shadowcasting.

Four cardinal rays (N/S/E/W) extend from the player, each 3 tiles wide, stopping at walls. Radius = `player_level + 5`. If the player has a lamp, an additional 5×5 area (±2 tiles) around the player is also explored. This gives very limited diagonal visibility.

### 2. What character represents each tile/entity type?

See [Section 3](#3-display-character-table--item-type-to-glyph) for the complete item-type-to-glyph table. Player is `☻` (0x02), wizard is `~` (0x7E). Monsters use their `visible_char` field.

### 3. What is the exact status bar format string?

```
Niv NN Or NNNNNN   PVNNNN/NNN   IntNNN   DexNNN   ForNNN   CA +N   Exp NN/NNNN
```

Labels: Niv=level, Or=gold, PV=HP, Int=intelligence, Dex=strength(!!), For=food(!!), CA=AC, Exp=level/XP. See [Section 9](#9-display_character_stats--status-bar).

### 4. How does the "discovered" (fog of war) system work?

Per-level byte array at `level * 0x719 + row * 79 + col + 0x70D`. Set to 1 when a tile is first explored by the FOV algorithm. On redraw, explored-but-not-visible tiles are drawn in **color 10** (bright green), giving a "memory" effect. Currently visible tiles are drawn in **color 15** (bright white). The explored state persists when revisiting levels.
