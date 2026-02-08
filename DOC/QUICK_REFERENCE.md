# Moria Variable Naming - Quick Reference

A condensed cheat sheet for the most commonly encountered patterns when working with the Moria reverse-engineered codebase.

## Most Common Memory Addresses

```c
// Player position and stats (0xb86x - 0xb89x)
0xb86c -> player_x              // Player X coordinate
0xb86e -> player_y              // Player Y coordinate
0xb870 -> player_hp_current     // Current HP
0xb872 -> player_hp_max         // Max HP
0xb874 -> player_stat_str       // Strength
0xb878 -> player_stat_int       // Intelligence
0xb87a -> player_stat_wis       // Wisdom
0xb880 -> player_armor_class_total
0xb886 -> player_experience
0xb888 -> player_level
0xb892 -> player_gold

// Equipment (0xb92x)
0xb926 -> equipped_weapon
0xb92a -> equipped_armor
0xb932 -> equipped_helmet
0xb92e -> equipped_shield
0xb936 -> inventory_size

// Game state (0xe5xx)
0xe52d -> current_level_index
0xe52f -> monster_object_count
0xe531 -> item_object_count
```

## Structure Offsets

### Item Structure (26 bytes)
```c
+0x00  type            // Item type
+0x01  id              // Item ID
+0x03  quantity        // Stack size
+0x09  uses_remaining  // Charges left
+0x0b  weight          // Item weight
+0x13  identified      // Is identified?
+0x14  cursed          // Is cursed?
+0x16  next            // Next in linked list
```

### Monster Structure (54 bytes)
```c
+0x00  type            // Monster type
+0x01  id              // Monster ID
+0x05  pos_y           // Y position
+0x07  pos_x           // X position
+0x23  visible         // Visibility flag
+0x27  hidden          // Hidden flag
+0x32  next            // Next monster
```

## Common Constants

```c
0x4f  = MAP_WIDTH (79)
0x16  = MAP_HEIGHT (22)
0x719 = MAP_SIZE (1817)
0x1a  = ITEM_SIZE (26)
0x36  = MONSTER_SIZE (54)
0x20  = CHAR_FLOOR (space)
```

## Parameter Naming Quick Guide

```c
// Coordinates
void func(int x_coord, int y_coord)

// Output parameters
void func(int* out_result, int* out_value)

// Object pointers
void func(undefined4* item_ptr, undefined4* monster_ptr)

// Flags
void func(char should_process, char is_enabled)
```

## Local Variable Patterns

```c
local_4   -> result / return_value
local_6   -> index / loop_counter
local_8   -> temp_value / count
local_c   -> iterator / offset

// Arrays
local_28[32]   -> bit_mask
local_16c[256] -> string_buffer

// Booleans
'\0'    -> FALSE
'\x01'  -> TRUE
```

## Common Code Patterns

### Loop Pattern
```c
// BEFORE:
local_4 = 1;
while (true) {
    // process
    if (local_4 == max) break;
    local_4 = local_4 + 1;
}

// AFTER:
for (int index = 1; index <= max; index++) {
    // process
}
```

### Equipment Check
```c
if ((item_ptr == equipped_weapon) ||
    (item_ptr == equipped_armor) ||
    (item_ptr == equipped_helmet)) {
    // Item is equipped
}
```

### Tile Access
```c
// Access tile at (x, y)
char tile = *(char*)(y * MAP_WIDTH + x + TILE_OFFSET);
```

### Linked List Traversal
```c
undefined4* current = list_head;
while (current != NULL) {
    // Process node
    current = *(undefined4*)((int)current + 0x16);  // Item: +0x16, Monster: +0x32
}
```

## Search & Replace Patterns

Use these regex patterns for quick bulk renaming:

```regex
# Memory addresses
\*\(int \*\)0xb86c  ->  player_x
\*\(int \*\)0xb86e  ->  player_y
\*\(int \*\)0xb888  ->  player_level

# Common hex values
0x4f\b              ->  MAP_WIDTH
0x16\b              ->  MAP_HEIGHT
0x20\b              ->  CHAR_FLOOR

# Loop counters
local_([468])\s*=\s*local_\1\s*\+\s*1  ->  index++ (after renaming to index)
```

## Boolean Convention

```c
// Always use:
char found = '\0';       // FALSE
if (condition) {
    found = '\x01';      // TRUE
}

// Not: found = 0; found = 1;
```

## Display Functions Pattern

```c
validate_window_coords(y + 1, x);
write_bytes(0, display_char);
flush_output(0xe654, display_segment);
```

## Memory Management Pattern

```c
// Allocate item
if (item_free_list == NULL) {
    // Create new
    read_stream_data(ITEM_SIZE, &new_item, segment);
    item_object_count++;
} else {
    // Reuse from free list
    new_item = item_free_list;
    item_free_list = item_free_list->next;
}

// Free item
item->next = item_free_list;
item_free_list = item;
```

## Common Function Signatures

```c
void get_sign(int* value)                               // Returns -1, 0, or 1
void find_item_at_coords(int* out_item, int x, int y)  // Find item at position
void allocate_item_object(undefined4* out_item)         // Allocate from pool
void free_item_object(undefined4 item_ptr)             // Return to pool
void display_score_with_fatal(int score)               // Show message (fatal if < 0)
```

## Array Access Patterns

```c
// Inventory access (base -0x46cc)
inventory_items[slot_index]

// Object type table (base -0x476c)
object_type_table[type_id]

// Level data array (base -0x54d9)
level_data_array[level_index]
```

## Debugging Tips

1. **Player coordinates reversed?** Check if X and Y are swapped in the original code
2. **Pointer arithmetic?** Segment:offset format means high word is segment
3. **Negative offsets?** These are static arrays in the data segment
4. **`>> 0xf`?** This extracts the sign bit (shift right 15 bits)
5. **`CONCAT11`?** Concatenates high and low bytes into 16-bit value

## Quick Tools

```bash
# Dry run to see what would change
python apply_variable_mappings.py --dry-run MORIA_renamed.C

# Generate C header with all types
python apply_variable_mappings.py --generate-header

# Apply all mappings
python apply_variable_mappings.py MORIA_renamed.C output.c
```

## Variable Naming Decision Tree

```
Is it a memory address (0xABCD)?
├─ Yes: Check memory_addresses in variable_mappings.json
└─ No: Is it a parameter?
    ├─ Yes: Check usage pattern
    │   ├─ Written to (*param)?     -> out_result, out_value
    │   ├─ Position 2?              -> x_coord, col
    │   ├─ Position 3?              -> y_coord, row
    │   └─ Pointer type?            -> item_ptr, buffer
    └─ No: Is it a local variable?
        ├─ Loop counter pattern?    -> index, i, counter
        ├─ Boolean pattern?         -> found, flag, is_X
        ├─ Coordinate pair?         -> x, y or row, col
        └─ Array?                   -> buffer, mask, temp_array
```

---

**Pro Tip**: Start by renaming all memory addresses first (they're global and most impactful), then work on function parameters, then local variables.

**Remember**: The original Moria is 16-bit DOS code, so:
- Pointers are segment:offset (32-bit)
- `undefined4*` is a far pointer
- Arrays often use negative offsets from a base address
- Coordinate systems may be inconsistent (sometimes X/Y swapped)
