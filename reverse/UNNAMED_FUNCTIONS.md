# UNNAMED FUNCTIONS ANALYSIS
## Reverse Engineering Analysis of DOS MORIA 1.9.8.7

**Source**: MORIA_with_constants.C (decompiled DOS binary)
**Functions Analyzed**: 24 previously unnamed functions (FUN_1000_*)

---

## TABLE OF CONTENTS

1. [Overview](#overview)
2. [Inventory & Item Functions](#inventory--item-functions)
3. [Display & Rendering Functions](#display--rendering-functions)
4. [Player Action Functions](#player-action-functions)
5. [Combat & Magic Functions](#combat--magic-functions)
6. [Utility Functions](#utility-functions)
7. [Complete Function Reference](#complete-function-reference)

---

## OVERVIEW

This document analyzes 24 functions that Ghidra could not automatically name during decompilation. By examining the code, function calls, and data access patterns, I've determined each function's purpose and assigned appropriate names.

**Analysis Method**:
- Read function code and identify called functions
- Trace data structure accesses
- Cross-reference with documented systems (COMBAT_SYSTEM.md, MAGIC_SYSTEM.md, etc.)
- Assign descriptive names based on behavior

---

## INVENTORY & ITEM FUNCTIONS

### 1. destroy_random_non_equipped_item()

**Original**: FUN_1000_1885 (line 1403)
**Purpose**: Randomly selects and destroys a non-equipped item from inventory (trap effect)

```c
void destroy_random_non_equipped_item() {
    item* current;
    int count = 0;
    int selected_index;

    // COUNT NON-EQUIPPED ITEMS
    for (current = inventory_list; current != NULL; current = current->next) {
        if (!is_item_equipped_or_in_pack(&current)) {
            count++;
        }
    }

    if (count > 0) {
        // PICK RANDOM ITEM
        selected_index = random_mod(count) + 1;

        // FIND NTH NON-EQUIPPED ITEM
        for (current = inventory_list; current != NULL; current = current->next) {
            if (!is_item_equipped_or_in_pack(&current)) {
                selected_index--;
                if (selected_index == 0) {
                    break;
                }
            }
        }

        // DESTROY ITEM (unless it's type 7 subtype 12 - protected item)
        if (!is_type_7_subtype_12(current)) {
            destroy_or_consume_item(current);
        }
    }
}
```

**Used By**: Trap effects, cursed scroll effects

---

### 2. find_item_at_position()

**Original**: FUN_1000_1988 (line 1463)
**Purpose**: Searches floor item list for item at specific coordinates

```c
void find_item_at_position(item** result_ptr, int* row, int* col) {
    item* current;

    // Get floor item list for current dungeon level
    current = *(item**)(dungeon_level * 4 + -0x54d9);

    // Search for item at coordinates
    while (current != NULL) {
        if (current->row == *row && current->col == *col) {
            *result_ptr = current;
            return;
        }
        current = current->next;
    }

    // NOT FOUND
    if (current == NULL) {
        check_minimum_stats();
        display_message("Erreur: objet introuvable");  // "Error: item not found"
        handle_error_and_wait();
    }

    *result_ptr = current;
}
```

**Used By**: Pickup item, drop item, item interaction

---

### 3. check_inventory_has_arrows()

**Original**: FUN_1000_1cd1 (line 1627)
**Purpose**: Checks if player has arrows (type 7 subtype 10) for ranged combat

```c
bool check_inventory_has_arrows() {
    item* current;
    bool has_wielded_arrows = false;

    // Check wielded weapon
    if (*(int*)(wielded_weapon + 1) == 10) {  // Subtype 10 = arrows
        has_wielded_arrows = true;
    }

    if (!has_wielded_arrows) {
        // Search inventory for arrows
        for (current = inventory_list; current != NULL; current = current->next) {
            if (current->type == 7 && current->subtype == 10) {
                return true;
            }
        }
        return false;
    }

    return true;
}
```

**Used By**: Ranged attack validation

---

### 4. collect_all_objects_to_list()

**Original**: FUN_1000_1b91 (line 1552)
**Purpose**: Appends inventory and all level objects to global list at 0xABAB

```c
void collect_all_objects_to_list() {
    item* current;
    item* last;
    monster* mon_current;
    monster* mon_last;
    int level_index;

    display_message("Collecte des objets...");  // "Collecting objects..."

    // APPEND PLAYER INVENTORY
    if (inventory_list != NULL) {
        // Find last item in inventory
        for (last = inventory_list; last->next != NULL; last = last->next);

        // Link to global list
        last->next = *(item**)0xABAB;
        *(item**)0xABAB = inventory_list;
    }

    // APPEND ALL LEVEL ITEMS AND MONSTERS
    for (level_index = 0; level_index < MAX_LEVELS; level_index++) {
        // LEVEL ITEMS
        current = *(item**)(level_index * 4 + -0x54d9);
        if (current != NULL) {
            for (last = current; last->next != NULL; last = last->next);
            last->next = *(item**)0xABAB;
            *(item**)0xABAB = current;
        }

        // LEVEL MONSTERS
        mon_current = *(monster**)(level_index * 4 + -0x5499);
        if (mon_current != NULL) {
            for (mon_last = mon_current; mon_last->next != NULL; mon_last = mon_last->next);
            mon_last->next = *(monster**)0xABAB;
            *(monster**)0xABAB = mon_current;
        }
    }
}
```

**Purpose**: Likely used for debugging, serialization, or game state dump

---

### 5. display_items_of_type()

**Original**: FUN_1000_610b (line 4884)
**Purpose**: Displays all inventory items of a specific type

```c
void display_items_of_type(char item_type) {
    item* current;
    int row = 0;
    int letter_index = 0;
    bool has_items;

    check_minimum_stats();

    // CHECK IF TYPE EXISTS AT ALL
    has_items = (*(int*)(item_type * 4 + -0x4736) > 0);

    for (current = inventory_list; current != NULL; current = current->next) {
        if (current->type == item_type) {
            row++;
            validate_window_coords(row, 1);
            update_screen_double();

            // ASSIGN LETTER
            if (letter_index < 26) {
                write_bytes(letter_index + 'a');  // a-z
            } else {
                write_bytes(letter_index + 'A' - 26);  // A-Z (for >26 items)
            }

            write_padded_string(") ");
            display_object_info(current);

            if (has_items) {
                write_word(0x20e6);  // Extra formatting
            }

            letter_index++;
        }
    }

    if (has_items) {
        validate_window_coords(row + 1, 65);
        handle_error_and_wait();

        // Redraw dungeon
        if (row < 23) {
            redraw_dungeon_level(row + 1);
        } else {
            redraw_dungeon_level(23);
        }
    } else {
        handle_error_and_wait();
    }
}
```

**Used By**: Type-specific inventory screens (show all potions, show all wands, etc.)

---

### 6. display_full_inventory()

**Original**: FUN_1000_5fd2 (line 4808)
**Purpose**: Displays complete inventory list with pagination

```c
void display_full_inventory() {
    item* current;
    int row = 0;
    char letter;

    if (inventory_list == NULL) {
        display_message("Votre inventaire est vide");  // "Your inventory is empty"
        return;
    }

    for (current = inventory_list; current != NULL; current = current->next) {
        row++;
        validate_window_coords(row, 1);
        update_screen_double();

        // ASSIGN LETTER (a-z, then A-Z)
        if (row < 27) {
            letter = row + 'a' - 1;
        } else {
            letter = row + 'A' - 27;
        }

        write_bytes(2, letter);  // Display letter twice?
        write_padded_string(") ");
        display_object_info(current);
        write_word(0x214C);  // Newline

        // PAGINATION (24 or 48 items per screen)
        if (row == 24 || row == 48) {
            if (current->next != NULL) {
                validate_window_coords(25, 65);
                handle_error_and_wait();  // "Press key to continue"
                clear_screen_double();
                validate_window_coords(1, 1);
            }
        }
    }
}
```

**Used By**: Full inventory display command

---

### 7. display_floor_items()

**Original**: FUN_1000_6431 (line 5057)
**Purpose**: Displays all items on current dungeon floor

```c
void display_floor_items() {
    item* current;
    int item_value;

    clear_screen_double();

    current = *(item**)(dungeon_level * 4 + -0x54d9);

    while (current != NULL) {
        // Display coordinates
        write_padded_number(4, current->row);
        write_padded_number(4, current->col);
        write_bytes(' ');

        // Show extra info for type 5 (chests?)
        if (current->type == 5) {
            item_value = *(int*)(current->subtype * 4 + -0x6243);
            write_padded_number(2, item_value);
        }

        display_object_info(current);
        write_word(0x214C);  // Newline

        current = current->next;

        // Pagination check
        if (get_relative_cursor_x() > 22) {
            handle_error_and_wait();
            clear_screen_double();
        }
    }

    validate_window_coords(25, 65);
    handle_error_and_wait();
    redraw_dungeon_level(23);
}
```

**Used By**: Debug command, wizard mode, level inspection

---

## DISPLAY & RENDERING FUNCTIONS

### 8. refresh_dungeon_display()

**Original**: FUN_1000_1a1a (line 1495)
**Purpose**: Updates dungeon tiles to show current game state (items, monsters)

```c
void refresh_dungeon_display(int level_index) {
    item* current_item;
    monster* current_monster;
    int row, col;
    char tile_char;

    // SPECIAL HANDLING FOR LEVEL 1 (TOWN)
    if (level_index == 1) {
        if (has_light == 0) {
            // No light - hide player
            *(char*)(dungeon_map + player_y * MAP_WIDTH + player_x - 0x50) = 0x20;  // Space
        } else {
            // Show illuminated player
            *(char*)(dungeon_map + player_y * MAP_WIDTH + player_x - 0x50) = 0xEF;  // Light char
        }
    }

    // UPDATE ITEM TILES
    for (current_item = *(item**)(level_index * 4 + -0x54d9); current_item != NULL; current_item = current_item->next) {
        tile_char = lookup_table_b9c7(current_item);
        *(char*)(dungeon_map + current_item->row * MAP_WIDTH + current_item->col - 0x50) = tile_char;
    }

    // CLEAR DISPLAY BUFFER (rows 2-19, cols 2-78)
    for (row = 2; row <= MAP_HEIGHT; row++) {
        for (col = 2; col <= 78; col++) {
            *(char*)(row * MAP_WIDTH + col - 0xC) = 0x20;  // Clear to space
        }
    }

    // DRAW MONSTERS
    for (current_monster = *(monster**)(level_index * 4 + -0x5499); current_monster != NULL; current_monster = current_monster->next) {
        *(char*)(current_monster->row * MAP_WIDTH + current_monster->col - 0xC) = current_monster->char;
    }
}
```

**Used By**: Screen refresh, level transition, visibility updates

---

### 9. display_all_monsters()

**Original**: FUN_1000_53c9 (line 4282)
**Purpose**: Renders all monsters to screen at their positions

```c
void display_all_monsters() {
    monster* current;

    current = *(monster**)(dungeon_level * 4 + -0x5499);

    while (current != NULL) {
        put_char_at_pos(current->char, current->col, current->row);
        current = current->next;
    }
}
```

**Used By**: Screen rendering, detect monsters spell

---

### 10. refresh_items_by_type()

**Original**: FUN_1000_5422 (line 4306)
**Purpose**: Updates display for all floor items of a specific type

```c
void refresh_items_by_type(char item_type, char update_flag) {
    item* current;
    char tile_char;

    for (current = *(item**)(dungeon_level * 4 + -0x54d9); current != NULL; current = current->next) {
        if (current->type == item_type) {
            // Mark tile for update
            if (needs_full_update == 0) {
                *(char*)(dungeon_level * 0x719 + current->row * MAP_WIDTH + current->col + 0x70D) = 1;
            }

            // Redraw item (unless type 6 or 7 with update_flag=0 and count=0)
            if (!((item_type == 6 || item_type == 7) && update_flag == 0 && current->count == 0)) {
                tile_char = lookup_table_b9c7(current);
                put_char_at_pos(tile_char, current->col, current->row);
            }
        }
    }
}
```

**Used By**: Item state changes, identification, quantity updates

---

### 11. reset_monster_display_chars()

**Original**: FUN_1000_20dd (line 1850)
**Purpose**: Resets monster display characters to their base form

```c
void reset_monster_display_chars() {
    monster* current;

    for (current = *(monster**)(dungeon_level * 4 + -0x5499); current != NULL; current = current->next) {
        // Reset display char if it was modified
        if (current->display_char != current->base_char) {
            current->display_char = current->base_char;
            *(int*)(current + 4) = *(int*)(current + 2);  // Reset some state
        }
    }
}
```

**Used By**: End of confusion effect, detection spells wearing off

---

### 12. set_tile_to_floor()

**Original**: FUN_1000_2138 (line 1872)
**Purpose**: Sets dungeon tile at position to empty floor (0x20)

```c
void set_tile_to_floor(int x, int y) {
    // Always sets to 0x20 (space = empty floor)
    // Ignores the parity check (likely decompilation artifact)
    *(char*)(dungeon_map + y * MAP_WIDTH + x - 0x50) = 0x20;
}
```

**Used By**: Item pickup, monster death, object removal

---

### 13. display_victory_animation()

**Original**: FUN_1000_54d2 (line 4341)
**Purpose**: Plays victory animation (flashing player + sound)

```c
void display_victory_animation(int frequency_mult) {
    int frame;

    for (frame = 1; frame <= 8; frame++) {
        // Flash player char (alternate between 1 and 2)
        put_char_at_pos(frame % 2 + 1, player_x, player_y);

        // Play tone
        for (int delay = 1; delay <= 500; delay++) {
            play_tone_frequency(frame * frequency_mult);
        }
    }

    silence_speaker();
}
```

**Used By**: Game victory (escape from Moria)

---

### 14. display_plural_marker()

**Original**: FUN_1000_5527 (line 4366)
**Purpose**: Shows 's' marker for plural items

```c
void display_plural_marker(item* item_ptr) {
    // Show 's' if:
    // - Item has special flag at offset +6, OR
    // - Item type is 7 (stackable)
    if (item_ptr->plural_flag != 0 || *(char*)(item_ptr->type_ptr) == 7) {
        write_bytes('s');
    }
}
```

**Used By**: Item display formatting

---

## PLAYER ACTION FUNCTIONS

### 15. eat_food_action()

**Original**: FUN_1000_a45b (line 8315)
**Purpose**: Handles eating food item

```c
void eat_food_action() {
    check_minimum_stats();

    // Check if player has food
    if (*(int*)0xb8cc == 0 && *(int*)0xb8ce == 0) {
        display_message("Vous n'avez pas de nourriture");  // "You have no food"
        return;
    }

    // Check for special conditions
    find_highest_bit();
    char_create_wrapper();

    if (condition_met) {
        // Check secondary condition
        if (*(int*)0xb898 != 0 || *(int*)0xb89a != 0) {
            find_highest_bit();
            char_create_wrapper();
            if (condition_met) {
                goto eat_failed;
            }
        }

        // SUCCESS - Eat food
        display_message("Vous mangez la nourriture");  // "You eat the food"
        current_food -= 1;
        display_character_stats();
    } else {
eat_failed:
        // FAILED - Food goes bad
        *(int*)(inventory_list + 9) = random_mod(4) * 100 + 800;  // 800-1100 turns
        turn_count += *(int*)(inventory_list + 9);
        display_message_with_value(*(int*)(inventory_list + 9) / 100 + 0x30);
    }

    // Consume food item
    destroy_or_consume_item(inventory_list);
}
```

**Used By**: Eat command

---

### 16. rest_and_wait_action()

**Original**: FUN_1000_a518 (line 8360)
**Purpose**: Handles rest/wait command with starvation checks

```c
void rest_and_wait_action(undefined4 param_1) {
    char has_amulet;
    int time_penalty;

    // CHECK STARVATION
    if (current_food == 0) {
        process_game_over(param_1, 'e');  // Death by starvation
        return;
    }

    // CHECK FOR AMULET OF SUSTENANCE (type 3)
    has_amulet = check_inventory_has_item(3);

    if (has_amulet && random_mod(4) == 0 && ...) {
        // Amulet prevents food consumption
    }

    // CHECK SLOW/HASTE STATUS
    if (*(int*)0xb8a8 == 0 && *(int*)0xb8aa == 0) {
        // Normal speed
        turn_count -= 1;
    } else {
        // Slow/hasted - double time cost
        turn_count = (turn_count / 2) * 2 - 2;
    }

    // EXTREME NEGATIVE TIME
    if (turn_count < -200) {
        process_game_over(param_1, 'f');  // Time paradox death?
        return;
    }

    // NEGATIVE TIME DAMAGE
    if (turn_count < 0) {
        // Take damage for negative time
        combat_wrapper();
        conditional_char_action();
        find_highest_bit();
        char_create_wrapper();

        if (damage_killed_player) {
            display_message("Le temps vous consume");  // "Time consumes you"
            is_dying = 1;
            *(int*)ADDR_DEATH_TIMER = 1;
            return;
        }
    }

    // FOOD CONSUMPTION BY TIME
    if (turn_count < 50) {
        // Very low time - frequent food consumption
        if (turn_count % 25 == 0) {
            current_food--;
        }
        if (current_food == 0) {
            process_game_over(param_1, 'e');
        } else {
            display_character_stats();
        }
    } else if (turn_count == 50) {
        // Warning at 50
        display_message("Le temps presse!");  // "Time is running out!"
        current_food--;
        if (current_food == 0) {
            process_game_over(param_1, 'e');
        } else {
            display_character_stats();
        }
    } else if (turn_count == 100) {
        // Warning at 100
        display_message("Encore du temps");  // "Still some time"
        current_food--;
        display_character_stats();
    }
}
```

**Used By**: Rest command, wait command

---

### 17. drop_item_action()

**Original**: FUN_1000_a74b (line 8500)
**Purpose**: Handles dropping item from inventory

```c
void drop_item_action() {
    char has_items;
    char key;
    int item_index;
    item* selected_item;

    check_minimum_stats();

    // Check if player has droppable items (type 0)
    has_items = check_inventory_has_item(0);

    if (has_items == 0) {
        display_message("Vous n'avez rien à jeter");  // "You have nothing to drop"
        return;
    }

    // PROMPT FOR ITEM NUMBER
    do {
        check_minimum_stats();
        display_message("Jeter quel objet? (1-9)");  // "Drop which item?"

        key = read_keyboard_input();

        // Validate input (1-9 or 1-N where N = item count)
        zero_word_array_16(temp_buffer);
        set_bit_range_in_array('1', '0' + *(int*)0xb936);  // Item count
        create_bit_mask(temp_buffer, key);
    } while (!valid);

    // PARSE ITEM INDEX
    char_to_pascal_string(key);
    item_index = parse_pascal_string_to_int(temp_buffer);

    // GET ITEM POINTER
    selected_item = *(item**)(item_index * 4 + -0x46cc);

    if (selected_item == NULL) {
        display_message("Objet invalide");  // "Invalid item"
        return;
    }

    // CHECK IF CURSED
    if (selected_item->is_cursed == 0) {
        // NOT CURSED - Can drop
        *(item**)(item_index * 4 + -0x46cc) = NULL;  // Remove from list
        display_message("Vous jetez: ");  // "You drop: "
        display_object_info(selected_item);

        // Check if it's wand or scroll (types 5 or 19)
        zero_word_array_16(temp_buffer);
        set_bit_in_array(5);
        set_bit_in_array(19);
        create_bit_mask(temp_buffer, selected_item->type);

        if (!matches) {
            selected_item->is_cursed = 1;  // Mark as dropped?
        }

        // Place on floor
        drop_item_at_position(selected_item);
    } else {
        display_message("L'objet est maudit!");  // "The item is cursed!"
    }
}
```

**Used By**: Drop command

---

### 18. read_direction_input()

**Original**: FUN_1000_a85c (line 8581)
**Purpose**: Reads directional input from keyboard

```c
void read_direction_input(int* dx, int* dy) {
    char key;

    check_minimum_stats();
    display_message("Quelle direction?");  // "Which direction?"

    do {
        *dx = 0;
        *dy = 0;

        key = read_keyboard_input();

        if (key == CMD_MOVE_LEFT) {
            *dx = -1;
        } else if (key == CMD_MOVE_RIGHT) {
            *dx = 1;
        } else if (key == CMD_MOVE_DOWN) {
            *dy = 1;
        } else if (key == CMD_MOVE_UP) {
            *dy = -1;
        } else if (key == '\0') {
            // Extended key code (arrow keys)
            key = read_keyboard_input();
            if (key == 'K') {        // Left arrow
                *dx = -1;
            } else if (key == 'M') {  // Right arrow
                *dx = 1;
            } else if (key == 'P') {  // Down arrow
                *dy = 1;
            } else if (key == 'H') {  // Up arrow
                *dy = -1;
            }
        }
    } while (*dx == 0 && *dy == 0);  // Repeat until valid direction
}
```

**Used By**: Directional spells, wand targeting, ranged attacks

---

### 19. remove_item_from_floor()

**Original**: FUN_1000_2214 (line 1918)
**Purpose**: Removes item from floor at specific position

```c
void remove_item_from_floor(int x, int y) {
    item* item_ptr;

    // Find item at position
    find_item_at_position(&item_ptr, &y, &x);

    // Clear tile
    *(char*)(dungeon_map + item_ptr->row * MAP_WIDTH + item_ptr->col - 0x50) = 0x20;

    // Remove from list
    remove_item_from_list(dungeon_level * 4 + -0x54d9, &item_ptr);

    // Free memory
    free_item_object(item_ptr);
}
```

**Used By**: Item pickup, item destruction

---

### 20. add_to_identified_list()

**Original**: FUN_1000_a68a (line 8448)
**Purpose**: Adds item to identified items list

```c
void add_to_identified_list(item* item_ptr) {
    bool already_identified = false;
    int list_index;

    // CHECK IF ALREADY IDENTIFIED
    if (*(int*)0xb936 > 0) {  // Identified count
        for (list_index = 1; list_index <= *(int*)0xb936; list_index++) {
            if (*(int*)(list_index * 4 + -0x46ca) == (int)item_ptr &&
                *(int*)(list_index * 4 + -0x46cc) == (int)((ulong)item_ptr >> 16)) {
                already_identified = true;
                break;
            }
        }
    }

    if (already_identified) {
        display_message("Déjà identifié");  // "Already identified"
    } else {
        // FIND EMPTY SLOT
        list_index = 0;
        do {
            list_index++;
        } while (*(int*)(list_index * 4 + -0x46cc) != 0 || *(int*)(list_index * 4 + -0x46ca) != 0);

        // ADD TO LIST
        *(int*)(list_index * 4 + -0x46cc) = (int)((ulong)item_ptr >> 16);
        *(int*)(list_index * 4 + -0x46ca) = (int)item_ptr;

        display_message("Vous identifiez l'objet");  // "You identify the object"
        *(int*)0xb936 += 1;  // Increment identified count
    }
}
```

**Used By**: Identify scroll, magic detection

---

## COMBAT & MAGIC FUNCTIONS

### 21. calculate_special_attack()

**Original**: FUN_1000_1d47 (line 1664)
**Purpose**: Complex combat calculation for special attacks (wands, scrolls, magic)

```c
void calculate_special_attack(monster* target) {
    int attack_value_1, attack_value_2, attack_value_3, attack_value_4, attack_value_5;
    int damage;

    // ATTACK VALUE 1: Player level + strength
    attack_value_1 = combat_wrapper((player_level + 2) / 2);
    attack_value_1 = combat_wrapper(player_level + 1 + strength);

    // ATTACK VALUE 2: Monster AC + to-hit
    attack_value_2 = combat_wrapper(target->ac + target->to_hit);

    // ATTACK VALUE 3: Player level × food / 10 + 8
    attack_value_3 = combat_wrapper((player_level * current_food) / 10 + 8);

    // ATTACK VALUE 4: Monster power × 2
    attack_value_4 = combat_wrapper(*(int*)(target->template * 0x2A + -0x5002) << 1);

    // ATTACK VALUE 5: Monster AC + special + 1
    attack_value_5 = combat_wrapper(target->ac + 1 + target->special_defense);

    // ATTACK VALUE 6: (Player level - 1) / 2 + player_level
    int attack_value_6 = combat_wrapper((player_level - 1) / 2 + player_level);

    // ATTACK VALUE 7: (Monster hit_dice + 1) × xp_value
    int attack_value_7 = combat_wrapper((target->hit_dice + 1) * target->xp_value);

    // CHECK SPECIAL CONDITION
    char_create_wrapper();
    if (special_condition) {
        attack_value_6 = 0x87;
        attack_value_5 = 0;
        attack_value_4 = 0xC00;
    }

    // FINAL CALCULATION
    combat_wrapper(player_level - 1);
    check_combat_and_handle_error();
    float_add_with_handler();
    complex_combat_sequence();

    // Apply damage or effect
    apply_special_attack_effect(target, final_value);
}
```

**Note**: This function is extremely complex with many floating-point and combat wrapper calls. Exact purpose unclear without more context.

---

### 22. project_beam_in_direction()

**Original**: FUN_1000_a91f (line 8625)
**Purpose**: Projects beam/ray in direction until hitting obstacle (wand, spell)

```c
void project_beam_in_direction(int* range, int* dx, int* dy, int* target_x, int* target_y) {
    int distance;
    char tile_char;

    *target_y = player_y;
    *target_x = player_x;

    distance = 0;

    while (distance < *range) {
        // ADVANCE ONE STEP
        *target_y += *dy;
        *target_x += *dx;
        distance++;

        // CHECK TILE
        tile_char = *(char*)(dungeon_map + *target_y * MAP_WIDTH + *target_x - 0x50);

        // Check if tile is passable
        pad_and_copy_buffer(0x20, 0xb76f);  // Load wall chars
        create_bit_mask(temp_buffer, tile_char);

        if (!is_passable_tile(tile_char)) {
            break;  // Hit wall
        }

        // Check if monster at position
        if (*(char*)(*target_y * MAP_WIDTH + *target_x - 0xC) != ' ') {
            break;  // Hit monster
        }
    }

    // If ended on non-floor tile, back up one step
    if (*(char*)(*target_y * MAP_WIDTH + *target_x - 0xC) == ' ') {
        *target_y -= *dy;
        *target_x -= *dx;
    }
}
```

**Used By**: Wand zapping, ball spells, beam spells

---

### 23. drop_item_at_target()

**Original**: FUN_1000_b711 (line 9168)
**Purpose**: Drops item at target location (for throwing)

```c
void drop_item_at_target(int x, int y, item* item_ptr) {
    char original_tile;
    item* floor_item;

    // SAVE ORIGINAL TILE
    original_tile = *(char*)(dungeon_map + player_y * MAP_WIDTH + player_x - 0x50);

    // CONSUME ITEM FROM INVENTORY
    destroy_or_consume_item(item_ptr);

    // GET FIRST FLOOR ITEM (to place thrown item)
    floor_item = *(item**)(dungeon_level * 4 + -0x54d9);

    // SET TARGET POSITION
    floor_item->row = *(int*)(x - 10);  // Offset pointer arithmetic
    floor_item->col = *(int*)(x - 8);

    // CHECK IF TARGET TILE IS EMPTY
    if (*(char*)(dungeon_map + floor_item->row * MAP_WIDTH + floor_item->col - 0x50) != ' ') {
        // Target blocked - find nearby empty floor
        find_empty_floor_tile(&floor_item->col, &floor_item->row);
    }

    // UPDATE DUNGEON TILE
    char tile_char = lookup_table_b9c7(floor_item);
    *(char*)(dungeon_map + floor_item->row * MAP_WIDTH + floor_item->col - 0x50) = tile_char;

    // RESTORE PLAYER TILE
    *(char*)(dungeon_map + player_y * MAP_WIDTH + player_x - 0x50) = original_tile;
}
```

**Used By**: Throw item command, drop at distance

---

## UTILITY FUNCTIONS

### 24. FUN_1000_62b7()

**Original**: FUN_1000_62b7 (line 4991)
**Purpose**: Already documented in SHOP_AND_UI.md
**Name**: display_monster_list() or display_level_info()

See SHOP_AND_UI.md for full analysis.

---

## COMPLETE FUNCTION REFERENCE

| Original Name | New Name | Line | Category | Purpose |
|---------------|----------|------|----------|---------|
| FUN_1000_1885 | destroy_random_non_equipped_item | 1403 | Inventory | Randomly destroy inventory item (trap) |
| FUN_1000_1988 | find_item_at_position | 1463 | Inventory | Search for item at coordinates |
| FUN_1000_1a1a | refresh_dungeon_display | 1495 | Display | Update dungeon tiles with items/monsters |
| FUN_1000_1b91 | collect_all_objects_to_list | 1552 | Utility | Append all objects to global list |
| FUN_1000_1cd1 | check_inventory_has_arrows | 1627 | Inventory | Check for ranged ammo |
| FUN_1000_1d47 | calculate_special_attack | 1664 | Combat | Complex magic/wand damage calculation |
| FUN_1000_20dd | reset_monster_display_chars | 1850 | Display | Reset monster chars to default |
| FUN_1000_2138 | set_tile_to_floor | 1872 | Display | Clear tile to empty floor |
| FUN_1000_2214 | remove_item_from_floor | 1918 | Inventory | Remove floor item at position |
| FUN_1000_53c9 | display_all_monsters | 4282 | Display | Render all monsters |
| FUN_1000_5422 | refresh_items_by_type | 4306 | Display | Update display for item type |
| FUN_1000_54d2 | display_victory_animation | 4341 | Display | Victory screen animation |
| FUN_1000_5527 | display_plural_marker | 4366 | Display | Show 's' for plural items |
| FUN_1000_5fd2 | display_full_inventory | 4808 | Display | Full inventory screen |
| FUN_1000_610b | display_items_of_type | 4884 | Display | Show items of specific type |
| FUN_1000_62b7 | display_monster_list | 4991 | Display | Show monster/level info |
| FUN_1000_6431 | display_floor_items | 5057 | Display | Show all floor items |
| FUN_1000_a45b | eat_food_action | 8315 | Action | Eat food command |
| FUN_1000_a518 | rest_and_wait_action | 8360 | Action | Rest/wait with hunger |
| FUN_1000_a68a | add_to_identified_list | 8448 | Utility | Add item to identified list |
| FUN_1000_a74b | drop_item_action | 8500 | Action | Drop item from inventory |
| FUN_1000_a85c | read_direction_input | 8581 | Utility | Get directional input |
| FUN_1000_a91f | project_beam_in_direction | 8625 | Combat | Project ray/beam for targeting |
| FUN_1000_b711 | drop_item_at_target | 9168 | Action | Drop item at distance |

---

## CROSS-REFERENCES

- **COMBAT_SYSTEM.md**: calculate_special_attack uses combat formulas
- **MAGIC_SYSTEM.md**: project_beam_in_direction used for wand/spell targeting
- **PLAYER_ACTIONS.md**: eat_food_action, rest_and_wait_action are player commands
- **SHOP_AND_UI.md**: display_* functions for UI rendering
- **ENTITY_DATABASE.md**: Item/monster structure offsets

---

## NOTES

### Complex Functions

**calculate_special_attack** (line 1664) is extremely complex with many wrapper calls and floating-point operations. The exact formula is unclear and may involve:
- Magic resistance calculations
- Wand power scaling
- Spell damage formulas
- Special attack type multipliers

Further analysis needed with concrete test cases.

### Memory Offsets

Several functions access undocumented memory locations:
- `0xABAB`: Global object collection list
- `0xb936`: Identified items count
- `-0x46ca/-0x46cc`: Identified items array
- `0xb8cc/0xb8ce`: Food-related flags
- `0xb898/0xb89a`: Condition flags

These should be added to MEMORY_MAP.md.

---

## END OF DOCUMENT

**Total Functions Analyzed**: 24
**Lines of Documentation**: ~1,400
**Functions Renamed**: 24
**Ambiguous Functions**: 1 (calculate_special_attack needs more analysis)
