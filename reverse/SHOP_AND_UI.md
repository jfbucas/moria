# SHOPS, SCORING & UI SCREENS
## Reverse Engineering Analysis of DOS MORIA 1.9.8.7

**Source**: MORIA_with_constants.C (decompiled DOS binary)
**Functions Analyzed**: 12 UI, shop, and scoring system functions

---

## TABLE OF CONTENTS

1. [Overview](#overview)
2. [Shop System](#shop-system)
3. [Score Calculation](#score-calculation)
4. [High Score System](#high-score-system)
5. [Death & Game Over](#death--game-over)
6. [Save File Format](#save-file-format)
7. [UI Screens](#ui-screens)
8. [Function Reference](#function-reference)

---

## OVERVIEW

This document covers the remaining UI systems in DOS MORIA:
- **Shops**: Two shop types, purchasing mechanics, pricing
- **Scoring**: How player score is calculated (spoiler: it's just gold)
- **High Scores**: File format for "moria4.scr", leaderboard display
- **Death Screen**: Game over sequence, high score insertion
- **Save System**: NO save game feature (only high scores persist)
- **UI Menus**: Help, inventory, options, command list

All findings based on direct analysis of decompiled C source code.

---

## SHOP SYSTEM

### Shop Overview

DOS MORIA has **TWO shops** on dungeon level 0 (town):
- **Shop Type 0**: Unknown (likely weapons/general items)
- **Shop Type 1**: Unknown (likely armor/magic items)

Shop inventory and prices are stored in **static data arrays** loaded at startup.

### Shop Data Structure

**Item Names**: Offset `0x75fa + (shop_type × 0x2b8) + (item_id × 0x1d)`
**Item Prices**: Offset `-0x71d3 + (shop_type × 0x30) + (item_id × 2)`
**Shop Count**: Offset `0x79b3 + (shop_type × 4)` → item count per shop

```c
// Shop data layout (per item)
struct ShopItem {
    char name[29];        // At 0x75fa + offsets (0x1d = 29 bytes each)
    int price;            // At -0x71d3 + offsets (2 bytes each)
};

// Shop inventory count
int shop_item_counts[2];  // At 0x79b3 (4 bytes per shop)
```

### Shop Purchase Menu

**Function**: `shop_purchase_menu` (line 7483)

```c
void shop_purchase_menu() {
    char selected_items[256];
    int shop_type, item_index, selected_index;
    int item_count, price;

    // PROMPT: Select shop (1 or 2)
    clear_screen();
    display_message("Boutique 1 ou 2?");  // "Shop 1 or 2?"

    key = read_keyboard_input();
    if (key == '1') {
        shop_type = 6;  // Shop type offset
    } else {
        shop_type = 7;
    }

    // BUILD AFFORDABLE ITEM LIST
    selected_items[1] = 0;  // Count of affordable items
    item_count = *(int*)(shop_type * 4 + 0x79b3);  // Get item count

    for (item_index = 0; item_index < item_count; item_index++) {
        price = *(int*)(shop_type * 0x30 + item_index * 2 - 0x71d3);

        // Check if player can afford (gold >= price)
        if (gold_low >= price || (gold_high > 0 && price != 0)) {
            selected_items[1]++;  // Increment count
            selected_items[selected_items[1] + 1] = item_index + 0x28;  // Store item ID

            // Display item in list
            display_shop_item(item_index, shop_type, selected_items[1]);
        }
    }

    // NO AFFORDABLE ITEMS
    if (selected_items[1] == 0) {
        return;  // Exit shop
    }

    // NAVIGATION LOOP
    selected_index = 1;
    highlight_item = selected_items[2] - 0x28;  // First item
    display_shop_item(highlight_item, shop_type, selected_index, 0x0F);  // Highlight

    while (true) {
        key = read_keyboard_input();

        if (key == '\r') {  // ENTER - Purchase
            break;
        } else if (key == 'P' || key == CMD_MOVE_DOWN) {  // Down arrow
            // Move selection down (wrap to top)
            if (selected_index < selected_items[1]) {
                selected_index++;
            } else {
                selected_index = 1;  // Wrap to first
            }
            highlight_item = selected_items[selected_index + 1] - 0x28;
        } else if (key == 'H' || key == CMD_MOVE_UP) {  // Up arrow
            // Move selection up (wrap to bottom)
            if (selected_index > 1) {
                selected_index--;
            } else {
                selected_index = selected_items[1];  // Wrap to last
            }
            highlight_item = selected_items[selected_index + 1] - 0x28;
        }

        // Redraw highlighting
        display_shop_item(old_highlight, shop_type, old_index, 0x00);  // Un-highlight
        display_shop_item(highlight_item, shop_type, selected_index, 0x0F);  // Highlight
    }

    // PURCHASE ITEM
    price = *(int*)(shop_type * 0x30 + highlight_item * 2 - 0x71d3);

    // Deduct gold
    gold_low -= price;
    if (gold_low < 0) {
        gold_high--;
        gold_low += 0x10000;  // Borrow from high word
    }

    // CREATE ITEM OBJECT
    allocate_item_object(&item_ptr);
    item_ptr->type = shop_type;
    item_ptr->subtype = highlight_item;
    item_ptr->count = 1;
    item_ptr->flags = 0;

    // PLACE ITEM AT PLAYER'S FEET
    place_object_on_map(dungeon_level, &item_ptr);

    // Update tile at player position to show item
    tile = lookup_table_b9c7(player_x, player_y);
    set_tile_at(player_x, player_y, tile);

    redraw_dungeon_level();
    display_character_stats();
}
```

### Shop Item Display

**Function**: `display_shop_item` (line 7459)

```c
void display_shop_item(int row, int color, int item_id, int shop_type) {
    char* item_name;
    int price;

    set_background_color(color);  // 0x00 = normal, 0x0F = highlighted

    validate_window_coords(row, 1);  // Position cursor

    // Get item name from data table
    item_name = (char*)(shop_type * 0x2b8 + item_id * 0x1d + 0x75fa);
    write_padded_string(item_name);

    // Get item price
    price = *(int*)(shop_type * 0x30 + item_id * 2 - 0x71d3);
    write_padded_number(6, price);

    write_padded_string(" PO");  // " GP" (gold pieces)
    write_word(0x214c);  // Newline

    set_background_color(0x00);  // Reset to normal
}
```

### Shop Mechanics Summary

| Feature | Behavior |
|---------|----------|
| **Shop Count** | 2 shops (indexed 0-1) |
| **Location** | Dungeon level 0 (town) |
| **Item Display** | Shows only affordable items |
| **Navigation** | Up/Down arrows to select |
| **Purchase** | ENTER key confirms |
| **Payment** | Gold deducted immediately |
| **Item Delivery** | Placed at player's feet |
| **No Selling** | Players cannot sell items back |

**Important**: There is **NO selling mechanic**. Shops are purchase-only.

---

## SCORE CALCULATION

### The Score Formula

**SURPRISE**: Player score is simply **total gold owned**.

```c
// Score calculation (from process_game_over, line 5752)
score_low = gold_low;
score_high = gold_high;

// Score is a 32-bit value:
// score = (gold_high << 16) | gold_low
```

### Gold Sources

Gold accumulates from:
1. **Finding gold on floor** (random amounts)
2. **Killing monsters** (some drop gold)
3. **Selling items** - **NOT POSSIBLE** (no sell mechanic)
4. **Inventory items with type 0x08** - converted to gold on death

### Gold Conversion on Death

**From `process_game_over` (line 5785-5798)**:

```c
void process_game_over(char death_cause) {
    item* current;

    // CONVERT ALL TYPE 0x08 ITEMS TO GOLD
    for (current = inventory_list; current != NULL; current = current->next) {
        if (current->type == 0x08 && current->count > 0) {
            // Add item value to gold
            gold_low += current->value_low;
            gold_high += current->value_high;

            // Handle 32-bit carry
            if (gold_low < current->value_low) {
                gold_high++;
            }
        }
    }

    // Score = final gold total
    display_death_screen(death_cause);
    check_high_scores();
}
```

**Item type 0x08**: Likely "Treasure" or "Gems" that convert to gold value on death.

### Score Display

Score is displayed as:
- **Low word** (0-65535)
- **High word** × 65536
- **Total**: `score = gold_high * 65536 + gold_low`

Example: `gold_high = 2, gold_low = 30000` → Score = `2 × 65536 + 30000 = 161,072 PO`

---

## HIGH SCORE SYSTEM

### High Score File Format

**File**: `moria4.scr` (DOS 8.3 filename)
**Location**: Same directory as MORIA.EXE
**Format**: Binary, fixed-size records

```c
// High score entry structure (24 bytes = 0x18)
struct HighScoreEntry {
    char player_name[15];     // Offset -0x45db (Pascal string, length-prefixed)
    uint32_t score;           // Offset -0x45c9 (low) + -0x45c7 (high)
    uint16_t dungeon_level;   // Offset -0x45cb
    uint8_t death_cause;      // Offset -0x45c5 (character code)
    uint8_t checksum;         // Offset -0x45c4 (validation byte)
};

// File structure
HighScoreEntry high_scores[16];  // 16 entries × 24 bytes = 384 bytes
```

### High Score Entry Layout

| Offset | Size | Field | Description |
|--------|------|-------|-------------|
| 0x00 | 15 bytes | player_name | Pascal string (1 byte length + 14 char name) |
| 0x0F | 4 bytes | score | 32-bit gold total (little-endian) |
| 0x13 | 2 bytes | dungeon_level | How deep player descended |
| 0x15 | 1 byte | death_cause | 'g' = won, other = death reason code |
| 0x16 | 1 byte | checksum | Validation byte (sum of name + score + level + cause) |
| 0x17 | 1 byte | padding | Alignment byte |

### Load High Scores

**Function**: `load_high_scores` (line 5449)

```c
void load_high_scores() {
    FILE* file;
    int entry_index, checksum;
    uint8_t byte1, byte2, byte3, byte4;

    init_fcb("moria4.scr", &file);
    file_open_wrapper(&file);

    if (get_error_code() != 0) {
        return;  // File not found - empty high scores
    }

    entry_index = 0;
    while (skip_whitespace(file) == 0 && entry_index < 16) {
        // READ 4-BYTE SCORE (little-endian)
        byte1 = getc(file);
        byte2 = getc(file);
        byte3 = getc(file);
        byte4 = getc(file);

        high_scores[entry_index].score_low = byte1 | (byte2 << 8);
        high_scores[entry_index].score_high = byte3 | (byte4 << 8);

        // READ DUNGEON LEVEL (encoded as: value = (byte - 0x32) / 2)
        byte1 = getc(file);
        high_scores[entry_index].dungeon_level = (byte1 - 0x32) / 2;

        // READ DEATH CAUSE
        high_scores[entry_index].death_cause = getc(file);

        // READ PLAYER NAME (15 bytes, Pascal string)
        read_string_from_file(15, high_scores[entry_index].player_name);

        // READ CHECKSUM
        checksum = getc(file);

        // VALIDATE CHECKSUM
        calculated = (player_name[0] + player_name[1] + score_low + dungeon_level + death_cause) % 256;

        if (calculated == checksum) {
            entry_index++;  // Valid entry
        }
    }
}
```

### Save High Scores

**Function**: `save_high_scores` (line 5689)

```c
void save_high_scores() {
    FILE* file;
    int entry_index;
    uint8_t checksum;

    init_fcb("moria4.scr", &file);
    file_open_wrapper2(&file);  // Create/overwrite

    entry_index = 1;
    while (entry_index < 16 && (high_scores[entry_index].score_low != 0 || high_scores[entry_index].score_high != 0)) {
        // WRITE 4-BYTE SCORE (little-endian)
        write_bytes(file, high_scores[entry_index].score_low & 0xFF);
        write_bytes(file, (high_scores[entry_index].score_low >> 8) & 0xFF);
        write_bytes(file, high_scores[entry_index].score_high & 0xFF);
        write_bytes(file, (high_scores[entry_index].score_high >> 8) & 0xFF);

        // WRITE DUNGEON LEVEL (encoded)
        write_bytes(file, high_scores[entry_index].dungeon_level * 2 + 0x32);

        // WRITE DEATH CAUSE
        write_bytes(file, high_scores[entry_index].death_cause);

        // WRITE CHECKSUM
        checksum = (player_name[0] + player_name[1] + score_low + dungeon_level + death_cause) % 256;
        write_bytes(file, checksum);

        // WRITE PLAYER NAME (15 bytes)
        write_string_to_file(15, high_scores[entry_index].player_name);

        entry_index++;
    }

    close_file(file);
}
```

### Display High Scores

**Function**: `display_high_scores` (line 5548)

```c
void display_high_scores() {
    int entry_index;
    uint32_t score;

    // DRAW BORDER
    write_bytes(0xDA);  // Top-left corner ┌
    for (i = 1; i <= 74; i++) {
        write_bytes(0xC4);  // Horizontal line ─
    }
    write_bytes(0xBF);  // Top-right corner ┐

    // HEADER
    validate_window_coords(34, row);
    display_message("Table des scores");  // "Score table"

    write_bytes(0xB3);  // Left border │
    write_bytes(0xB3);  // Right border │

    // DISPLAY EACH ENTRY
    for (entry_index = 1; entry_index < 16; entry_index++) {
        score = (high_scores[entry_index].score_high << 16) | high_scores[entry_index].score_low;

        if (score == 0) break;  // End of list

        write_bytes(0xB3);  // Left border │

        // Player name
        write_padded_string(high_scores[entry_index].player_name);

        validate_window_coords(20, row);

        // Death cause or victory
        if (high_scores[entry_index].death_cause == 'g') {
            // WON THE GAME
            display_message("Sorti de Moria");  // "Left Moria"
        } else {
            // DIED
            display_character_status_message(high_scores[entry_index].death_cause);
        }

        // Level reached (if not winner)
        if (high_scores[entry_index].death_cause != 'g') {
            write_padded_string("Niveau ");  // "Level "
            write_padded_number(high_scores[entry_index].dungeon_level);
        }

        // Score
        write_padded_string("Score: ");
        write_padded_number(score);
        write_padded_string(" PO");  // " GP"

        // Show 's' if winner (pluriel marker?)
        if (score > 1) {
            write_bytes('s');
        }

        write_bytes(0xB3);  // Right border │
    }
}
```

### High Score Insertion

**From `process_game_over` (line 5840-5878)**:

```c
void process_game_over(char death_cause) {
    int insert_position;

    load_high_scores();

    // FIND INSERTION POSITION
    insert_position = 1;

    if (death_cause == 'g') {
        // WINNER - Insert before first non-winner OR lower score
        for (; insert_position < 16; insert_position++) {
            if (gold_high > high_scores[insert_position].score_high ||
                (gold_high == high_scores[insert_position].score_high && gold_low > high_scores[insert_position].score_low) ||
                high_scores[insert_position].death_cause != 'g') {
                break;
            }
        }
    } else {
        // DIED - Skip all winners, then insert by score
        while (insert_position < 16 && high_scores[insert_position].death_cause == 'g') {
            insert_position++;
        }

        for (; insert_position < 16; insert_position++) {
            if (gold_high > high_scores[insert_position].score_high ||
                (gold_high == high_scores[insert_position].score_high && gold_low > high_scores[insert_position].score_low)) {
                break;
            }
        }
    }

    // SHIFT ENTRIES DOWN (make room)
    if (insert_position < 16) {
        for (i = 15; i > insert_position; i--) {
            memcpy(&high_scores[i], &high_scores[i-1], 24);
        }

        // INSERT NEW ENTRY
        high_scores[insert_position].score_low = gold_low;
        high_scores[insert_position].score_high = gold_high;
        high_scores[insert_position].dungeon_level = dungeon_level;
        high_scores[insert_position].death_cause = death_cause;
        copy_pascal_string(high_scores[insert_position].player_name, player_name);
    }

    display_high_scores();

    // SAVE IF QUALIFIED (not space filler ' ')
    if (insert_position < 16 && death_cause != ' ') {
        save_high_scores();
    }
}
```

### High Score Sorting Rules

1. **Winners ('g') always rank above non-winners**
2. **Within winners**: Sort by score (descending)
3. **Within non-winners**: Sort by score (descending)
4. **Maximum 16 entries**

Example ranking:
```
1. Jean      Sorti de Moria      Score: 500,000 PO
2. Marie     Sorti de Moria      Score: 300,000 PO
3. Pierre    Tué par dragon      Niveau 20    Score: 150,000 PO
4. Sophie    Mort de faim        Niveau 15    Score: 80,000 PO
```

---

## DEATH & GAME OVER

### Death Trigger

**Function**: `handle_player_death` (line 3863)

```c
void handle_player_death() {
    check_minimum_stats();
    display_score_with_fatal(0x1a2);  // Display death message
    // Triggers game over sequence
}
```

**Death Causes**:
- HP ≤ 0 from combat
- HP ≤ 0 from starvation
- HP ≤ 0 from poison
- HP ≤ 0 from fall damage (stairs)
- Special death effects (instant kill attacks)

### Game Over Sequence

**Function**: `process_game_over` (line 5752)

```c
void process_game_over(char death_cause) {
    item* current;
    uint32_t total_gold;
    int insert_position;

    wait_for_memory_match(1000);  // Delay for dramatic effect
    clear_screen();

    // STEP 1: CONVERT TREASURE ITEMS TO GOLD
    for (current = inventory_list; current != NULL; current = current->next) {
        if (current->type == 0x08 && current->count > 0) {
            gold_low += current->value_low;
            gold_high += current->value_high + (carry ? 1 : 0);
        }
    }

    validate_window_coords(2, 20);

    // STEP 2: DISPLAY DEATH OR VICTORY MESSAGE
    if (death_cause == 'g') {
        // WON THE GAME
        clear_screen();
        validate_window_coords(10, 30);
        write_padded_string("Félicitations!");  // "Congratulations!"
        display_message("Vous êtes sorti de Moria!");  // "You left Moria!"
        validate_window_coords(12, 35);
        write_padded_string("Votre aventure est terminée.");  // "Your adventure is over."
    } else {
        // DIED
        validate_window_coords(3, 15);
        display_character_status_message(death_cause);  // Display cause of death

        write_padded_string("Niveau ");
        write_padded_number(dungeon_level);
        write_padded_string("Or: ");
        write_padded_number(gold_low, gold_high);

        display_message("Vous êtes mort!");  // "You are dead!"
        validate_window_coords(4, 35);
        display_message("Repose en paix...");  // "Rest in peace..."
    }

    // STEP 3: CHECK HIGH SCORES
    if (death_cause != 'Q') {  // 'Q' = quit without saving
        load_high_scores();

        // Find insertion position (winners before non-winners, then by score)
        insert_position = find_high_score_position(gold_low, gold_high, death_cause);

        if (insert_position < 16) {
            // QUALIFIED FOR HIGH SCORES
            shift_high_scores_down(insert_position);

            // Insert new entry
            high_scores[insert_position].score_low = gold_low;
            high_scores[insert_position].score_high = gold_high;
            high_scores[insert_position].dungeon_level = dungeon_level;
            high_scores[insert_position].death_cause = death_cause;
            copy_pascal_string(high_scores[insert_position].player_name, player_name);
        }
    }

    // STEP 4: DISPLAY HIGH SCORES TABLE
    display_high_scores();

    // STEP 5: SAVE HIGH SCORES
    if (insert_position < 16 && death_cause != ' ') {
        save_high_scores();
    }

    validate_window_coords(25, 60);
    handle_error_and_wait();  // Wait for keypress

    return;  // Exit to main menu
}
```

### Confirm Save or Quit

**Function**: `confirm_save_or_quit` (line 5894)

```c
void confirm_save_or_quit(char command) {
    char response;

    check_minimum_stats();
    display_message("Attention!");  // "Warning!"

    if (command == CMD_SEARCH) {
        display_message("Sauvegarder et quitter?");  // "Save and quit?"
    } else {
        display_message("Quitter sans sauvegarder?");  // "Quit without saving?"
    }

    response = read_keyboard_input();

    if (response == 'o' || response == 'O') {  // 'o' = "oui" (yes)
        if (command == CMD_SEARCH) {
            // SAVE GAME - NOT IMPLEMENTED
            // This branch exists but does nothing (no save mechanic)
        } else {
            // QUIT WITHOUT SAVING
            process_game_over('Q');  // 'Q' = quit, don't record high score
        }
    }
}
```

**Important**: The "save game" option **does nothing**. There is no save/load game feature.

---

## SAVE FILE FORMAT

### The Truth About Saves

**DOS MORIA HAS NO SAVE GAME FEATURE.**

Only **high scores** are saved to disk in `moria4.scr`.

### Evidence

1. **No save_game() function exists** in the codebase
2. **No load_game() function exists** (only `load_game_data()` for static tables)
3. **confirm_save_or_quit()** displays "save" option but executes no code
4. **All level data stored in RAM** (not disk) - see PLAYER_ACTIONS.md
5. **Quitting exits to DOS** immediately

### What IS Saved

| File | Content | Format |
|------|---------|--------|
| `moria4.scr` | High scores (16 entries) | Binary, 384 bytes |
| `moria.txt` | Game data (loaded at startup) | Text, static |
| `moria4.don` | Unknown data file | Unknown |

### Why No Save Feature?

This was common for early roguelikes:
- **Permadeath philosophy**: One life, no reloading
- **Anti-cheating**: Can't savescum before risky actions
- **Technical limits**: DOS memory constraints
- **Design choice**: Emphasizes careful play

Players who quit lose all progress. The only persistence is the high score table.

---

## UI SCREENS

### Help Screen

**Function**: `display_help_file` (line 5256)

```c
void display_help_file() {
    FILE* file;
    char line_buffer[81];
    int line_count;
    char key;

    init_fcb("MORIA.HLP", &file);  // Help file (if exists)
    file_open_wrapper(&file);

    if (get_error_code() != 0) {
        return;  // No help file found
    }

    while (skip_whitespace(file) == 0) {
        clear_screen();
        line_count = 1;

        // Read 24 lines (one screenful)
        while (skip_whitespace(file) == 0 && line_count <= 24) {
            read_string_from_file(80, line_buffer);
            write_padded_string(line_buffer);
            write_word(0x214c);  // Newline
            line_count++;
        }

        validate_window_coords(25, 40);
        display_message("Appuyez sur une touche...");  // "Press a key..."

        key = read_keyboard_input();

        if (key == 0x1B) {  // ESC key
            break;  // Exit help
        }
    }

    close_file(file);
}
```

**Help File**: `MORIA.HLP` (not found in memory dump - may not exist in French version)

### Command List Display

**Function**: `FUN_1000_6249` (line 4961)

```c
void FUN_1000_6249() {
    int message_id;

    clear_screen();

    // Display command list (messages 0x134 to 0x146)
    for (message_id = 0x134; message_id <= 0x146; message_id++) {
        // Special formatting for specific entries
        if (message_id == 0x13E || message_id == 0x144) {
            write_word(0x214C);  // Extra newline
        }

        display_score_with_fatal(message_id);  // Display command description
        write_word(0x214C);  // Newline
    }

    validate_window_coords(25, 65);
    handle_error_and_wait();  // Wait for keypress

    redraw_dungeon_level();
}
```

**Messages 0x134-0x146**: Command list text (extracted from string table)
- Movement commands
- Action commands
- Spell/item commands
- System commands

### Inventory List Display

**Function**: `display_inventory_list` (line 5324)

```c
void display_inventory_list() {
    int slot_index, row, col;
    char item_char;
    int item_count;

    clear_screen();

    row = 3;
    col = 1;

    display_message("Inventaire:");  // "Inventory:"
    write_bytes(' ');
    write_padded_string("Qu'avez-vous?");  // "What do you have?"
    write_word(0x214C);
    write_word(0x214C);

    // Display each inventory slot (35 slots = 0x23)
    for (slot_index = 1; slot_index <= 35; slot_index++) {
        item_char = *(char*)(slot_index * 0x2A - 0x5007);  // Item type character

        if (item_char != 0) {
            item_count = *(int*)(slot_index * 2 - 0x460B);  // Item count

            if (item_count > 0) {
                validate_window_coords(row, col);

                // Compare item to equipped list
                if (!is_item_equipped(slot_index)) {
                    // Show count if > 1
                    if (item_count > 1) {
                        write_padded_number(4, item_count);
                        write_bytes(' ');
                    }

                    // Show item name
                    write_padded_string(slot_index * 0x2A - 0x5017);  // Item name string

                    // Show (E) if equippable
                    if (item_count >= 2 && *(char*)(slot_index * 0x2A - 0x5017 + 0x10) == 'E') {
                        write_padded_string("(s)");  // Plural marker
                    }
                }

                write_word(0x214C);
                row++;

                // Wrap to second column after 20 items
                if (row > 23) {
                    col += 39;  // 0x27 in hex
                    row = 3;
                }
            }
        }
    }
}
```

**Inventory Layout**:
- 35 slots maximum (0x23)
- Two-column display (20 items per column)
- Shows item count if > 1
- Marks equipped items differently

### Options Menu (Debug/Cheat)

**Function**: `process_options_menu` (line 5110)

```c
void process_options_menu() {
    char key;
    int value;

    clear_screen();

    // Display current stats
    write_padded_string("HP: ");
    write_padded_number(current_hp);
    write_padded_number(max_hp);
    write_word(0x214C);

    write_padded_string("Tours: ");
    write_padded_number(turn_count);
    write_padded_string("Nourriture: ");
    write_padded_number(food_level);
    write_word(0x214C);

    write_padded_number(gold_low);
    write_bytes('/');
    write_padded_number(gold_high);
    write_padded_string("Or en banque: ");
    write_padded_number(banked_gold);
    write_word(0x214C);

    // Menu options
    write_padded_string("v - Modifier HP actuels");
    write_word(0x214C);
    write_padded_string("m - Modifier HP max");
    write_word(0x214C);
    write_padded_string("e - Modifier niveau");
    write_word(0x214C);
    write_padded_string("x - Modifier XP");
    write_word(0x214C);
    write_padded_string("f - Modifier nourriture");
    write_word(0x214C);
    write_padded_string("s - Modifier faim");
    write_word(0x214C);
    write_padded_string("a - Modifier CA");
    write_word(0x214C);
    write_padded_string("d - Modifier Force");
    write_word(0x214C);
    write_padded_string("i - Modifier Intelligence");
    write_word(0x214C);
    write_padded_string("o - Modifier Dextérité");
    write_word(0x214C);

    key = read_keyboard_input();

    // Process cheat commands
    switch (key) {
        case 'v':  // Modify current HP
            value = read_token_and_parse_number();
            current_hp = value;
            break;
        case 'm':  // Modify max HP (CMD_CAST_SPELL key)
            value = read_token_and_parse_number();
            max_hp = value;
            break;
        case 'e':  // Modify level (CMD_EQUIPMENT key)
            value = read_token_and_parse_number();
            player_level = value;
            break;
        case 'x':  // Modify XP
            value = read_token_and_parse_number();
            experience = value;
            break;
        case 'f':  // Modify food
            value = read_token_and_parse_number();
            current_food = value;
            break;
        case 's':  // Modify hunger (CMD_SEARCH key)
            value = read_token_and_parse_number();
            food_level = value;
            break;
        case 'a':  // Modify AC
            value = read_token_and_parse_number();
            base_ac = value;
            break;
        case 'd':  // Modify Strength
            value = read_token_and_parse_number();
            strength = value;
            break;
        case 'i':  // Modify Intelligence (CMD_INVENTORY key)
            value = read_token_and_parse_number();
            intelligence = value;
            break;
        case 'o':  // Modify Dexterity
            value = read_token_and_parse_number();
            dexterity = value;
            break;
    }
}
```

**Note**: This appears to be a **debug/cheat menu**, not accessible in normal gameplay.

---

## FUNCTION REFERENCE

### Function List (12 Functions Analyzed)

| Function | Line | Purpose |
|----------|------|---------|
| `handle_player_death` | 3863 | Trigger death sequence |
| `FUN_1000_6249` | 4961 | Display command list screen |
| `process_options_menu` | 5110 | Debug menu (stat editing) |
| `display_help_file` | 5256 | Display MORIA.HLP file |
| `display_inventory_list` | 5324 | Show inventory screen |
| `load_high_scores` | 5449 | Read moria4.scr file |
| `display_high_scores` | 5548 | Show high score table |
| `save_high_scores` | 5689 | Write moria4.scr file |
| `process_game_over` | 5752 | Death/victory sequence |
| `confirm_save_or_quit` | 5894 | Quit confirmation (no save) |
| `display_shop_item` | 7459 | Render shop item line |
| `shop_purchase_menu` | 7483 | Shop interface and purchase |

---

## KEY FINDINGS SUMMARY

### 1. The Shop System

**What's Sold**:
- 2 shop types (indices 0-1)
- Item names stored at offset `0x75fa + (shop_type × 0x2b8) + (item_id × 0x1d)`
- Prices stored at offset `-0x71d3 + (shop_type × 0x30) + (item_id × 2)`

**Pricing**:
- Fixed prices (no haggling)
- Prices in "PO" (pièces d'or = gold pieces)
- Affordable items filtered automatically

**Buy/Sell Mechanics**:
- **Buy**: Select item → deduct gold → place at feet
- **Sell**: **NOT POSSIBLE** (no sell mechanic exists)
- Navigation: Up/Down arrows, ENTER to confirm
- Items placed at player's feet after purchase

### 2. The Score Calculation Formula

**Score = Total Gold Owned**

```
score = (gold_high << 16) | gold_low
```

- No XP component
- No level component
- No item value component (except type 0x08 items converted on death)
- Simple 32-bit gold total

### 3. High Score File Format

**File**: `moria4.scr` (384 bytes)
**Structure**: 16 entries × 24 bytes each

```c
struct HighScoreEntry {
    char player_name[15];     // Pascal string
    uint32_t score;           // 4-byte gold total
    uint16_t dungeon_level;   // 2-byte level depth
    uint8_t death_cause;      // 1-byte status ('g' = won)
    uint8_t checksum;         // 1-byte validation
};
```

**Sorting**:
- Winners ('g') always rank above non-winners
- Within each group, sort by score descending
- Maximum 16 entries

### 4. The Death/Game Over Sequence

**Steps**:
1. Convert type 0x08 items to gold
2. Display death message or victory message
3. Load high scores from `moria4.scr`
4. Find insertion position (winners first, then by score)
5. Shift entries down if qualified
6. Insert new entry
7. Display high score table
8. Save to `moria4.scr`
9. Wait for keypress
10. Return to main menu

**Death Causes**:
- Combat (HP ≤ 0)
- Starvation (food ≤ 0)
- Poison damage
- Fall damage (stairs)
- 'Q' = quit (not recorded)
- 'g' = won (escaped Moria)

### 5. Save File Format (Spoiler: NONE)

**NO SAVE GAME FEATURE EXISTS**

- No save_game() function
- No load_game() function
- "Save and quit" option displays but does nothing
- Permadeath design: quit = lose all progress
- Only high scores persist to disk

**Files That Exist**:
- `moria4.scr` - High scores (binary, 384 bytes)
- `moria.txt` - Game data (text, loaded at startup)
- `moria4.don` - Unknown data file

---

## CROSS-REFERENCES

- **COMBAT_SYSTEM.md**: XP thresholds (for leveling, not score)
- **PLAYER_ACTIONS.md**: Level persistence (RAM only, not disk)
- **MAGIC_SYSTEM.md**: Item type 0x08 (treasure conversion)
- **ENTITY_DATABASE.md**: Item structures

---

## END OF DOCUMENT

**Total Functions Analyzed**: 12
**Lines of Documentation**: ~1,100
**Key Discovery**: Score is just gold, no save game feature
