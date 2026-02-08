# Moria Codebase Variable Naming Guide

This comprehensive guide provides naming conventions for variables in the Moria reverse-engineered codebase based on analysis of MORIA_renamed.C.

## Table of Contents
1. [Memory Address Mappings](#memory-address-mappings)
2. [Parameter Naming Patterns](#parameter-naming-patterns)
3. [Local Variable Patterns](#local-variable-patterns)
4. [Pointer Type Patterns](#pointer-type-patterns)
5. [Common Operations](#common-operations)
6. [Reusable Mapping Tables](#reusable-mapping-tables)

---

## 1. Memory Address Mappings

### Player State (0xb86x - 0xb89x)

| Address | Variable Name | Type | Description |
|---------|--------------|------|-------------|
| 0xb86c | player_x | int | Player X coordinate |
| 0xb86e | player_y | int | Player Y coordinate |
| 0xb870 | player_hp_current | int | Current hit points |
| 0xb872 | player_hp_max | int | Maximum hit points |
| 0xb874 | player_stat_str | int | Strength stat |
| 0xb876 | player_stat_str_max | int | Maximum strength |
| 0xb878 | player_stat_int | int | Intelligence stat |
| 0xb87a | player_stat_wis | int | Wisdom stat |
| 0xb87c | player_armor_bonus_1 | int | Armor bonus from equipment slot 1 |
| 0xb87e | player_armor_bonus_2 | int | Armor bonus from equipment slot 2 |
| 0xb880 | player_armor_class_total | int | Total armor class |
| 0xb882 | player_weapon_damage | int | Weapon damage bonus (capped at 10 or 13) |
| 0xb884 | player_light_radius | int | Light radius |
| 0xb886 | player_experience | int | Experience points |
| 0xb888 | player_level | int | Character level |
| 0xb88a | player_temp_var_1 | int | Temporary storage variable 1 |
| 0xb88c | player_temp_var_2 | int | Temporary storage variable 2 |
| 0xb88e | player_temp_var_3 | int | Temporary storage variable 3 |
| 0xb890 | player_search_range | int | Search range (default 5) |
| 0xb892 | player_gold | int | Gold amount (starts at 1000) |

### Player Name and Character Info (0xb84x - 0xb85x)

| Address | Variable Name | Type | Description |
|---------|--------------|------|-------------|
| 0xb84f | player_name | char* | Player name (Pascal string with length byte) |
| 0xb82f | player_name_buffer | char[32] | Buffer for player name |

### Game State Flags (0xb8cx - 0xb8fx)

| Address | Variable Name | Type | Description |
|---------|--------------|------|-------------|
| 0xb8c0 | game_state_counter_1 | int | State counter 1 (starts at 3) |
| 0xb8c2 | game_state_counter_2 | int | State counter 2 (starts at 3) |
| 0xb8c4 | dungeon_level | int | Current dungeon level (starts at 6) |
| 0xb8c6 | game_state_value_1 | int | State value 1 (starts at 0x26) |
| 0xb8c8 | player_experience_32bit | int32 | 32-bit experience value |
| 0xb8ca | player_experience_high | int | High word of experience |
| 0xb8cc | game_state_value_2 | int | State value 2 (starts at 1) |
| 0xb8ce | game_state_value_3 | int | State value 3 (starts at 0) |
| 0xb8e0 | game_state_value_4 | int | State value 4 (starts at 1) |
| 0xb8e2 | game_state_value_5 | int | State value 5 (starts at 0) |
| 0xb8e4 | game_state_value_6 | int | State value 6 (starts at 3) |
| 0xb8e6 | game_state_value_7 | int | State value 7 (starts at 0) |
| 0xb8ed | flag_game_mode_1 | char | Game mode flag 1 |
| 0xb8ee | flag_show_all_terrain | char | Show all terrain flag |
| 0xb8f0 | flag_random_display | char | Random display mode flag |
| 0xb8f2 | flag_full_map_mode | char | Full map view mode flag |
| 0xb8f4 | flag_game_active | char | Game active flag (set to 1) |
| 0xb8f6 | flag_viewport_mode | char | Viewport mode flag |

### Equipment Slots (0xb92x - 0xb93x)

| Address | Variable Name | Type | Description |
|---------|--------------|------|-------------|
| 0xb922 | equipped_ring | undefined4* | Pointer to equipped ring |
| 0xb924 | equipped_ring_seg | int | Segment for ring pointer |
| 0xb926 | equipped_weapon | undefined4* | Pointer to equipped weapon |
| 0xb928 | equipped_weapon_seg | int | Segment for weapon pointer |
| 0xb92a | equipped_armor | undefined4* | Pointer to equipped armor |
| 0xb92c | equipped_armor_seg | int | Segment for armor pointer |
| 0xb92e | equipped_shield | undefined4* | Pointer to equipped shield |
| 0xb930 | equipped_shield_seg | int | Segment for shield pointer |
| 0xb932 | equipped_helmet | undefined4* | Pointer to equipped helmet |
| 0xb934 | equipped_helmet_seg | int | Segment for helmet pointer |
| 0xb936 | inventory_size | int | Number of inventory slots (starts at 4) |

### Game Lists and Pointers (0xb91x - 0xb9cx)

| Address | Variable Name | Type | Description |
|---------|--------------|------|-------------|
| 0xb909 | game_score_threshold | int | Score threshold (starts at 3000) |
| 0xb913 | flag_game_status_1 | char | Game status flag 1 |
| 0xb915 | flag_game_status_2 | char | Game status flag 2 |
| 0xb916 | flag_game_status_3 | char | Game status flag 3 |
| 0xb917 | flag_game_status_4 | char | Game status flag 4 |
| 0xb918 | flag_game_status_5 | char | Game status flag 5 |
| 0xb919 | flag_game_status_6 | char | Game status flag 6 |
| 0xb91e | item_list_head | undefined4* | Head of item linked list |
| 0xb9c6 | lookup_table_size | char | Size of lookup table |

### Memory Management (0xabax)

| Address | Variable Name | Type | Description |
|---------|--------------|------|-------------|
| 0xaba7 | monster_free_list | undefined4* | Free list for monster objects |
| 0xaba9 | monster_free_list_seg | int | Segment for monster free list |
| 0xabab | item_free_list | undefined4* | Free list for item objects |
| 0xabad | item_free_list_seg | int | Segment for item free list |

### Global Game State (0xe5xx)

| Address | Variable Name | Type | Description |
|---------|--------------|------|-------------|
| 0xe52d | current_level_index | int | Current dungeon level index |
| 0xe52f | monster_object_count | int | Count of allocated monster objects |
| 0xe531 | item_object_count | int | Count of allocated item objects |
| 0xe535 | viewport_top | int | Top boundary of viewport |
| 0xe537 | viewport_bottom | int | Bottom boundary of viewport |
| 0xe554 | input_parse_buffer | int | Buffer for parsing numeric input |

### Display Constants (0xe654, 0x20e6, 0x214c)

| Address | Variable Name | Type | Description |
|---------|--------------|------|-------------|
| 0xe654 | display_segment | int | Display memory segment |
| 0x1000 | string_segment_1 | int | String data segment 1 |
| 0x20e6 | string_segment_2 | int | String data segment 2 |
| 0x214c | string_segment_3 | int | String data segment 3 |

### Inventory Arrays (negative offsets from 0xb934)

| Offset | Variable Name | Type | Description |
|--------|--------------|------|-------------|
| -0x46cc | inventory_items | undefined4[64] | Array of inventory item pointers |
| -0x46ca | inventory_items_seg | int[64] | Segment values for inventory items |
| -0x476c | object_type_table | undefined4[10] | Object type lookup table |
| -0x476a | object_type_table_seg | int[10] | Segments for object types |
| -0x4738 | item_array_1 | undefined4[8] | Item array 1 |
| -0x4736 | item_array_1_seg | int[8] | Segments for item array 1 |
| -0x4714 | flag_array | char[12] | Array of game flags |
| -0x4707 | value_array | int[12] | Array of game values |
| -0x46b8 | level_exp_table | int[] | Experience points per level table |
| -0x464e | direction_dy_table | int[4] | Y-direction offset table |
| -0x464c | direction_dx_table | int[4] | X-direction offset table |
| -0x4639 | lookup_table_b9c7 | char[] | Character lookup table |
| -0x4985 | class_name_table_1 | char[] | Class names (mode 1) |
| -0x4a34 | class_name_table_2 | char[] | Class names (mode 2) |
| -0x5017 | class_desc_table | char[] | Class descriptions |
| -0x54d9 | level_data_array | undefined4[] | Level-specific data pointers |
| -0x54d7 | level_data_array_seg | int[] | Segments for level data |

### Terrain Bit Masks and Lookup Tables

| Offset | Variable Name | Type | Description |
|--------|--------------|------|-------------|
| 0xb76f | terrain_wall_mask | char[32] | Bit mask for wall tiles |
| 0xb7cf | terrain_door_mask | char[32] | Bit mask for door tiles |

---

## 2. Parameter Naming Patterns

### Function Parameter Conventions

When reversing function parameters, follow these naming patterns:

| Pattern | Recommended Name | Type | Context |
|---------|-----------------|------|---------|
| param_1 (int*) | out_result / out_value / dest_ptr | int* | Output parameter (when written to) |
| param_1 (int) | value / amount / count | int | Scalar input value |
| param_1 (char*) | str / buffer / name | char* | String parameter |
| param_2 (int) | x_coord / col / index | int | Commonly X coordinate or column |
| param_3 (int) | y_coord / row / offset | int | Commonly Y coordinate or row |
| param_1 (undefined4*) | item_ptr / obj_ptr / entity_ptr | undefined4* | Pointer to game object |
| param_1 (char) | flag / mode / type | char | Boolean or enumeration |

### Common Parameter Combinations

```c
// Coordinate pairs
void function(int x_coord, int y_coord)
void function(int* out_x, int* out_y)

// Item/object manipulation
void function(undefined4* item_ptr, int item_id)
void function(undefined4* dest_ptr, undefined4* src_ptr)

// Display functions
void function(int row, int col, char display_char)
void function(int offset, int string_addr, int segment)

// Conditional operations
void function(char should_process, undefined1* buffer, undefined4* object_ptr)
```

---

## 3. Local Variable Patterns

### Local Variable Naming by Type

| Pattern | Recommended Name | Type | Usage |
|---------|-----------------|------|-------|
| local_4 | result / return_value / temp | undefined2 | Simple return value |
| local_6 | loop_counter / index / i | int | Loop counter |
| local_8 | temp_value / count / max | int | Temporary storage |
| local_c | iterator / offset | int | Loop iterator |
| local_XX (array) | buffer / temp_buffer | char[n] | Local buffer |
| local_28[32] | bit_mask / flags | char[32] | Bit mask array |
| local_16c[256] | string_buffer / large_buffer | char[256] | Large string buffer |

### Semantic Naming Based on Usage

```c
// Loop counters (always initialize and increment)
for (slot_index = 0; slot_index < inventory_size; slot_index++)
for (level_num = 1; level_num < max_level; level_num++)
for (item_index = 1; item_index <= item_count; item_index++)

// Flags and booleans
char found_item = '\0';      // Boolean flag
char is_equipped = '\x01';   // Boolean true
char should_continue = '\0'; // Control flag

// Coordinates
int target_x, target_y;      // Target position
int tile_x, tile_y;          // Tile coordinates
int offset_x, offset_y;      // Relative offsets

// Pointers
undefined4* current_item;    // Current item in iteration
char* item_data;             // Item data pointer
undefined4* next_node;       // Next in linked list

// Calculations
int distance;                // Calculated distance
int damage_total;            // Total damage
int exp_gained;              // Experience gained
```

---

## 4. Pointer Type Patterns

### Pointer Type Conventions

| Type | Usage | Example Name |
|------|-------|--------------|
| undefined4* | Generic 32-bit far pointer to object | item_ptr, monster_ptr, obj_ptr |
| int* | Pointer to integer (often output param) | out_x, out_y, result_ptr |
| char* | String or byte array pointer | name_str, buffer_ptr, text |
| undefined1* | Pointer to byte/char buffer | byte_buffer, data_ptr |
| undefined2* | Pointer to 16-bit value | word_ptr, value_ptr |

### Segmented Pointer Patterns (16-bit Real Mode)

In 16-bit DOS, pointers are often stored as segment:offset pairs:

```c
// Pattern: Store both offset and segment
undefined4* item_ptr;                    // Full 32-bit pointer (offset in low word)
undefined2 item_seg = (item_ptr >> 16);  // Segment in high word

// Common pattern for dereferencing
*(int*)(item_ptr + offset)              // Access field at offset
*(char*)((int)item_ptr + field_offset)  // Cast and offset

// Array access pattern
*(undefined4*)(index * 4 + base_offset)  // Access array element
*(int*)(index * 4 + base_offset + 2)     // Access high word
```

### Linked List Pointer Patterns

```c
// Linked list node structure
typedef struct {
    char type;           // Offset +0x00
    int id;              // Offset +0x01
    int field_x;         // Offset +0x03
    // ... more fields
    undefined4* next;    // Offset +0x16 (items) or +0x32 (monsters)
} node_t;

// Traversal pattern
undefined4* current_node = list_head;
while (current_node != NULL && current_node_seg != 0) {
    // Process node
    current_node = *(undefined4*)((int)current_node + 0x16);
}
```

---

## 5. Common Operations

### Loop Patterns

#### Forward Array Iteration
```c
// Pattern: 1-indexed loop with equality check
int slot_index = 1;
while (true) {
    // Process inventory[slot_index]
    if (slot_index == inventory_size) break;
    slot_index = slot_index + 1;
}

// Recommended refactoring:
for (int slot_index = 1; slot_index <= inventory_size; slot_index++) {
    // Process inventory[slot_index]
}
```

#### Range Iteration with Bounds
```c
// Pattern: Iterate within coordinate bounds
int y = player_y - 2;
if (y <= player_y + 2) {
    do {
        int x = player_x - 2;
        while (x <= player_x + 2) {
            // Process tile at (x, y)
            x++;
        }
        y++;
    } while (y <= player_y + 2);
}
```

#### Search with Early Exit
```c
// Pattern: Search for item with flag
char found = '\0';
int index = 1;
while (true) {
    if (inventory[index] != NULL && inventory[index]->id == target_id) {
        found = '\x01';
    }
    if (index == max_slots) break;
    index++;
}
```

### Conditional Patterns

#### Memory Address Comparison (Equipment Slots)
```c
// Pattern: Check if item is equipped
if (((item_ptr == equipped_weapon) || (item_ptr == equipped_armor)) ||
    ((item_ptr == equipped_helmet) || (item_ptr == equipped_shield))) {
    // Item is equipped
}
```

#### Bit Mask Testing
```c
// Pattern: Test if tile type is in bit mask
undefined4 tile_data = level_data[y * 0x4f + x];
char tile_char = *(char*)((int)tile_data + offset);
create_bit_mask(mask_buffer, segment, tile_char);
if (matches_mask) {
    // Tile matches mask
}
```

### Function Call Patterns

#### Display Functions
```c
// Pattern: Position cursor, write, flush
validate_window_coords(y + 1, x);
write_bytes(0, display_char);
flush_output(0xe654, display_segment);

// Pattern: Write padded string
write_padded_string(0, string_offset, string_segment);
flush_output(0xe654, display_segment);

// Pattern: Write number
write_padded_number(width, value, value >> 0xf);  // >> 0xf gets sign bit
```

#### Memory Allocation
```c
// Pattern: Allocate item from pool or create new
if (item_free_list == NULL) {
    read_stream_data(0x1a, &new_item, segment);
    item_object_count++;
} else {
    new_item = item_free_list;
    item_free_list = *(undefined4*)((int)item_free_list + 0x16);
}
```

---

## 6. Reusable Mapping Tables

### Quick Reference: Common Variable Name Mappings

Copy this table and fill in project-specific details:

```json
{
  "memory_addresses": {
    "0xb86c": "player_x",
    "0xb86e": "player_y",
    "0xb870": "player_hp_current",
    "0xb872": "player_hp_max",
    "0xb874": "player_stat_str",
    "0xb876": "player_stat_str_max",
    "0xb878": "player_stat_int",
    "0xb87a": "player_stat_wis",
    "0xb880": "player_armor_class_total",
    "0xb886": "player_experience",
    "0xb888": "player_level",
    "0xb892": "player_gold",
    "0xb8c4": "dungeon_level",
    "0xb936": "inventory_size",
    "0xe52d": "current_level_index"
  },

  "common_offsets": {
    "+0x00": "type",
    "+0x01": "id",
    "+0x03": "quantity",
    "+0x05": "pos_y",
    "+0x07": "pos_x",
    "+0x09": "uses_remaining",
    "+0x0b": "weight",
    "+0x0d": "value",
    "+0x11": "flags",
    "+0x13": "identified",
    "+0x14": "cursed",
    "+0x16": "next_item_ptr",
    "+0x1c": "creature_y",
    "+0x1e": "creature_x",
    "+0x23": "visible",
    "+0x27": "hidden",
    "+0x2e": "related_item_ptr",
    "+0x32": "next_monster_ptr"
  },

  "function_naming": {
    "get_sign": "Get sign of integer (-1, 0, or 1)",
    "check_minimum_stats": "Validate minimum player stats",
    "print_space": "Output single space character",
    "print_prompt": "Display prompt string",
    "find_item_at_coords": "Find item at given coordinates",
    "display_score_with_fatal": "Display score message, optionally fatal",
    "display_character_stats": "Show character stat screen",
    "put_char_at_pos": "Place character at screen position",
    "lookup_table_b9c7": "Look up character from table",
    "display_class_info": "Display character class information",
    "allocate_monster_object": "Allocate monster from pool",
    "free_monster_object": "Return monster to free pool",
    "allocate_item_object": "Allocate item from pool",
    "free_item_object": "Return item to free pool",
    "decrement_item_quantity": "Decrease item quantity by 1",
    "check_inventory_has_item": "Check if inventory contains item type",
    "build_object_index": "Build index of all objects",
    "count_item_total_quantity": "Count total quantity of item type",
    "handle_item_drop_or_unequip": "Handle dropping or unequipping item",
    "is_position_in_bounds": "Check if position is within bounds",
    "explore_tile_at_position": "Reveal tile at position",
    "render_field_of_view": "Render player's field of view",
    "initialize_new_game": "Initialize new game state",
    "initialize_game": "Full game initialization",
    "find_empty_floor_tile": "Find adjacent empty floor space",
    "place_player_on_level": "Place player on current level",
    "handle_player_death": "Handle player death event",
    "draw_game_hud": "Draw game HUD/interface"
  }
}
```

### Structure Field Offsets Reference

Use this template to document structure fields:

```c
// Item Structure (0x1a bytes, 26 decimal)
typedef struct {
    char type;              // +0x00: Item type (1-8+)
    int id;                 // +0x01: Item ID within type
    int quantity;           // +0x03: Stack quantity
    // ... more fields ...
    int uses_remaining;     // +0x09: Uses/charges left
    int weight;             // +0x0b: Item weight
    char cursed;            // +0x14: Cursed flag
    undefined4* next;       // +0x16: Next item in list
} item_t;

// Monster Structure (0x36 bytes, 54 decimal)
typedef struct {
    char type;              // +0x00: Monster type
    int id;                 // +0x01: Monster ID
    int y_pos;              // +0x05: Y position
    int x_pos;              // +0x07: X position
    // ... more fields ...
    char visible;           // +0x23: Visibility flag
    char hidden;            // +0x27: Hidden flag
    undefined4* item;       // +0x2e: Carried item
    undefined4* next;       // +0x32: Next monster in list
} monster_t;

// Level Data Structure
typedef struct {
    char tiles[0x719];      // 0x4f * 0x16 + extra = tile map
    char explored[0x719];   // Exploration flags
} level_t;
```

### Common Constant Values

| Value | Name | Meaning |
|-------|------|---------|
| 0x4f | MAP_WIDTH | Width of dungeon map (79 tiles) |
| 0x16 | MAP_HEIGHT | Height of dungeon map (22 tiles) |
| 0x719 | MAP_SIZE | Total map tiles (79 * 22 + 1 = 1817) |
| 0x1a | ITEM_SIZE | Size of item structure (26 bytes) |
| 0x36 | MONSTER_SIZE | Size of monster structure (54 bytes) |
| 0xff | STAT_MAX | Maximum stat value (255) |
| 0xc | INVENTORY_MAX | Maximum inventory slots (12) |
| 0x20 | CHAR_FLOOR | Floor tile character (space) |

---

## Usage Guidelines

### When Renaming Variables

1. **Start with memory addresses**: Use the memory address mapping tables to rename global variables first
2. **Identify parameters by usage**: Look at how parameters are used to determine their purpose
3. **Name locals semantically**: Use the variable's role in the function, not just its position
4. **Document structures**: Build structure definitions as you identify field offsets
5. **Use consistent patterns**: Follow the naming patterns established in this guide

### Verification Checklist

- [ ] All memory addresses from 0xb8xx range are renamed
- [ ] Function parameters have semantic names (not param_1, param_2)
- [ ] Loop counters have clear names (index, slot_index, etc.)
- [ ] Pointer variables indicate what they point to
- [ ] Boolean flags use is_/has_/should_ prefixes or _flag suffix
- [ ] Coordinate variables are named x/y or row/col consistently
- [ ] Structure field offsets are documented

---

## Example Refactoring

### Before:
```c
void FUN_1234(int *param_1, int param_2, int param_3) {
    undefined2 local_4;
    local_4 = 0;
    if (*(int *)(param_3 * 0x4f + param_2 + -0xc) == 0x20) {
        *(int *)0xb86c = param_3;
        *(int *)0xb86e = param_2;
        local_4 = 1;
    }
    *param_1 = local_4;
}
```

### After:
```c
void check_and_move_to_floor_tile(int* out_success, int target_x, int target_y) {
    char success = '\0';

    // Check if target tile is floor (space character)
    char tile_char = *(char*)(target_y * MAP_WIDTH + target_x + TILE_OFFSET);
    if (tile_char == CHAR_FLOOR) {
        player_x = target_y;  // Note: Y/X swapped in original
        player_y = target_x;
        success = '\x01';
    }

    *out_success = success;
}
```

---

## Appendix: Type Definitions

```c
// Ghidra type mappings
typedef unsigned char   undefined;
typedef unsigned char   undefined1;
typedef unsigned short  undefined2;
typedef unsigned long   undefined4;
typedef unsigned short  word;

// Common game types
typedef undefined4* far_ptr;     // 16:16 segmented pointer
typedef char bool8;               // 8-bit boolean
typedef undefined2 segment_t;     // Memory segment

// Common value constants
#define FALSE   '\0'
#define TRUE    '\x01'
#define NULL    0
```

---

**Last Updated**: Based on analysis of MORIA_renamed.C (484KB, 16-bit DOS executable reversed with Ghidra)

**Note**: This guide is based on static analysis. Some variable names may need adjustment based on runtime behavior or additional context.
