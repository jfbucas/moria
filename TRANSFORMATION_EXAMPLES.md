# Moria Code Transformation Examples

Real examples from MORIA_renamed.C showing before and after applying the variable naming guide.

## Example 1: Display Character Stats Function

### Before:
```c
void __cdecl16near display_character_stats(void)
{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 unaff_DS;
  undefined2 uVar3;
  undefined2 uVar4;

  uVar1 = get_relative_cursor_y();
  uVar2 = get_relative_cursor_x(uVar1);
  validate_window_coords(0x19,1);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x261,0x20e6);
  write_padded_number(2,*(int *)0xe52d,*(int *)0xe52d >> 0xf);
  flush_output(uVar3,uVar4);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x266,0x214c);
  write_padded_number(6,*(undefined2 *)0xb8c8,*(undefined2 *)0xb8ca);
  write_padded_string(0,0x26a,0x214c);
  write_padded_number(4,*(int *)0xb870,*(int *)0xb870 >> 0xf);
  write_bytes(0,CONCAT11(extraout_AH,0x2f));
  write_padded_number(3,*(int *)0xb872,*(int *)0xb872 >> 0xf);
  write_padded_string(0,0x270,0x214c);
  write_padded_number(3,*(int *)0xb87a,*(int *)0xb87a >> 0xf);
  write_padded_string(0,0x277,0x214c);
  write_padded_number(3,*(int *)0xb878,*(int *)0xb878 >> 0xf);
  write_padded_string(0,0x27e,0x214c);
  write_padded_number(3,*(int *)0xb874,*(int *)0xb874 >> 0xf);
  write_padded_string(0,0x285,0x214c);
  flush_output(uVar3,uVar4);
  if (*(int *)0xb880 < 1) {
    print_space();
  }
  else {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_padded_string(0,0x28b,0x214c);
    flush_output(uVar3,uVar4);
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(1,*(int *)0xb880,*(int *)0xb880 >> 0xf);
  write_padded_string(0,0x28e,0x214c);
  write_padded_number(2,*(int *)0xb888,*(int *)0xb888 >> 0xf);
  write_bytes(0,CONCAT11(extraout_AH_00,0x2f));
  write_padded_number(4,*(int *)0xb886,*(int *)0xb886 >> 0xf);
  flush_output(uVar3,uVar4);
  update_screen_double();
  validate_window_coords(CONCAT11(extraout_AH_01,uVar2),CONCAT11(extraout_AH_01,uVar1));
  return;
}
```

### After:
```c
void display_character_stats(void)
{
  uint8_t saved_y;
  uint8_t saved_x;

  // Save current cursor position
  saved_y = get_relative_cursor_y();
  saved_x = get_relative_cursor_x(saved_y);

  // Display character stats screen at row 25
  validate_window_coords(25, 1);

  // Display level
  write_padded_string(0, 0x261, STRING_SEGMENT_2);
  write_padded_number(2, current_level_index, current_level_index >> 0xf);
  flush_output(display_segment, display_segment_ds);

  // Display experience
  write_padded_string(0, 0x266, STRING_SEGMENT_3);
  write_padded_number(6, player_experience_32bit, player_experience_high);

  // Display HP
  write_padded_string(0, 0x26a, STRING_SEGMENT_3);
  write_padded_number(4, player_hp_current, player_hp_current >> 0xf);
  write_bytes(0, '/');  // Separator
  write_padded_number(3, player_hp_max, player_hp_max >> 0xf);

  // Display Wisdom
  write_padded_string(0, 0x270, STRING_SEGMENT_3);
  write_padded_number(3, player_stat_wis, player_stat_wis >> 0xf);

  // Display Intelligence
  write_padded_string(0, 0x277, STRING_SEGMENT_3);
  write_padded_number(3, player_stat_int, player_stat_int >> 0xf);

  // Display Strength
  write_padded_string(0, 0x27e, STRING_SEGMENT_3);
  write_padded_number(3, player_stat_str, player_stat_str >> 0xf);
  write_padded_string(0, 0x285, STRING_SEGMENT_3);
  flush_output(display_segment, display_segment_ds);

  // Display armor class (with sign indicator if positive)
  if (player_armor_class_total < 1) {
    print_space();
  } else {
    write_padded_string(0, 0x28b, STRING_SEGMENT_3);  // "+" sign
    flush_output(display_segment, display_segment_ds);
  }

  write_padded_number(1, player_armor_class_total, player_armor_class_total >> 0xf);
  write_padded_string(0, 0x28e, STRING_SEGMENT_3);

  // Display level and experience
  write_padded_number(2, player_level, player_level >> 0xf);
  write_bytes(0, '/');
  write_padded_number(4, player_experience, player_experience >> 0xf);
  flush_output(display_segment, display_segment_ds);

  update_screen_double();

  // Restore cursor position
  validate_window_coords(saved_x, saved_y);
}
```

---

## Example 2: Allocate Item Object

### Before:
```c
void allocate_item_object(undefined4 *param_1)
{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;

  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  if (*(int *)0xabab == 0 && *(int *)0xabad == 0) {
    read_stream_data(0x1a,(undefined4 *)param_1,uVar3);
    *(int *)0xe531 = *(int *)0xe531 + 1;
  }
  else {
    uVar1 = *(undefined4 *)0xabab;
    *(int *)param_1 = (int)uVar1;
    *(undefined2 *)((int)(undefined4 *)param_1 + 2) = (int)((ulong)uVar1 >> 0x10);
    uVar1 = *(undefined4 *)((int)*(undefined4 *)0xabab + 0x16);
    *(undefined2 *)0xabab = (int)uVar1;
    *(undefined2 *)0xabad = (int)((ulong)uVar1 >> 0x10);
  }
  uVar3 = (undefined2)((ulong)*param_1 >> 0x10);
  iVar2 = (int)*param_1;
  *(undefined2 *)(iVar2 + 0x16) = 0;
  *(undefined2 *)(iVar2 + 0x18) = 0;
  *(undefined2 *)((int)*param_1 + 3) = 1;
  return;
}
```

### After:
```c
void allocate_item_object(item_t** out_item)
{
  item_t* new_item;
  item_t* next_free;

  // Check if free list is empty
  if (item_free_list == NULL) {
    // No free items - allocate new one from data stream
    read_stream_data(ITEM_SIZE, (void**)out_item);
    item_object_count++;
  } else {
    // Reuse item from free list
    new_item = item_free_list;
    *out_item = new_item;

    // Update free list to next item
    next_free = new_item->next;
    item_free_list = next_free;
  }

  // Initialize new item
  new_item = *out_item;
  new_item->next = NULL;
  new_item->quantity = 1;
}
```

---

## Example 3: Inventory Item Check

### Before:
```c
void decrement_item_quantity(int param_1)
{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined2 unaff_DS;
  undefined2 local_4;

  local_4 = 0;
  bVar3 = false;
  do {
    local_4 = local_4 + 1;
    if ((*(int *)(local_4 * 4 + -0x46cc) != 0 || *(int *)(local_4 * 4 + -0x46ca) != 0) &&
       (uVar1 = *(undefined4 *)(local_4 * 4 + -0x46cc), *(int *)((int)uVar1 + 1) == param_1)) {
      uVar1 = *(undefined4 *)(local_4 * 4 + -0x46cc);
      uVar2 = *(undefined4 *)(local_4 * 4 + -0x46cc);
      *(int *)((int)uVar2 + 9) = *(int *)((int)uVar1 + 9) + -1;
      bVar3 = true;
    }
  } while ((local_4 != *(int *)0xb936) && (!bVar3));
  return;
}
```

### After:
```c
void decrement_item_quantity(int item_id)
{
  item_t* item;
  bool found;
  int slot_index;

  found = false;

  // Search through inventory for item with matching ID
  for (slot_index = 1; slot_index <= inventory_size && !found; slot_index++) {
    item = inventory_items[slot_index];

    if (item != NULL && item->id == item_id) {
      item->uses_remaining--;
      found = true;
    }
  }
}
```

---

## Example 4: Render Field of View

### Before:
```c
local_e = *(int *)0xb86c;
do {
  local_e = local_e + -1;
  local_c = -1;
  while (explore_tile_at_position(&stack0xfffe,local_c + *(int *)0xb86e,local_e), local_c != 1) {
    local_c = local_c + 1;
  }
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  iVar3 = (int)uVar1 + local_e * 0x4f + *(int *)0xb86e;
  uVar6 = iVar3 == 0;
  uVar4 = CONCAT11((char)(local_e * 0x4f >> 8),*(undefined1 *)(iVar3 + -0x50));
  puVar7 = local_34;
  uVar8 = unaff_SS;
  pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
  create_bit_mask(puVar7,uVar8,uVar4);
} while (((bool)uVar6) && (*(int *)0xb86c - local_e != local_14));
```

### After:
```c
// Scan upward from player position
int scan_y = player_x;
do {
  scan_y--;

  // Explore tiles horizontally at this Y level
  for (int offset_x = -1; offset_x <= 1; offset_x++) {
    explore_tile_at_position(offset_x + player_y, scan_y);
  }

  // Get tile character at player's X position
  level_data_t* level = level_data_array[current_level_index];
  int tile_offset = scan_y * MAP_WIDTH + player_y;
  char tile_char = level->tiles[tile_offset];

  // Check if tile blocks vision
  bool blocks_vision = is_tile_in_mask(tile_char, terrain_wall_mask);

} while (!blocks_vision && (player_x - scan_y != view_range));

viewport_top = scan_y;
```

---

## Example 5: Initialize New Game

### Before:
```c
void __cdecl16near initialize_new_game(void)
{
  // ... setup code ...

  *(undefined2 *)0xb886 = 0;
  *(undefined2 *)0xb888 = 0x80;
  *(undefined2 *)0xb870 = 1000;
  *(undefined2 *)0xb872 = 1000;
  *(undefined2 *)0xb88a = 0;
  *(undefined2 *)0xb88c = 0;
  *(undefined2 *)0xb88e = 0;

  // ... more code ...

  *(undefined2 *)0xb874 = 100;
  *(undefined2 *)0xb876 = 100;
  *(undefined2 *)0xb878 = 100;
  *(undefined2 *)0xb87a = 100;

  // ... more code ...

  *(undefined2 *)0xb892 = 1000;
  *(undefined2 *)0xb936 = 4;

  *(undefined2 *)0xb8c2 = 3;
  *(undefined2 *)0xb8c0 = 3;
  *(undefined2 *)0xb8c6 = 0x26;
  *(undefined2 *)0xb87c = 0;
  *(undefined2 *)0xb87e = 0;
  *(undefined2 *)0xb880 = 0;
  *(undefined2 *)0xb882 = 0;
}
```

### After:
```c
void initialize_new_game(void)
{
  // Initialize player stats
  player_experience = 0;
  player_level = 128;  // Starting level
  player_hp_current = 1000;
  player_hp_max = 1000;
  player_temp_var_1 = 0;
  player_temp_var_2 = 0;
  player_temp_var_3 = 0;

  // Set base stats (can be modified during character creation)
  player_stat_str = 100;
  player_stat_str_max = 100;
  player_stat_int = 100;
  player_stat_wis = 100;

  // Initialize resources
  player_gold = 1000;
  inventory_size = 4;  // Start with 4 inventory slots

  // Initialize game state
  game_state_counter_1 = 3;
  game_state_counter_2 = 3;
  game_state_value_1 = 38;

  // Reset equipment bonuses
  player_armor_bonus_1 = 0;
  player_armor_bonus_2 = 0;
  player_armor_class_total = 0;
  player_weapon_damage = 0;
}
```

---

## Example 6: Equipment Check

### Before:
```c
if ((((((int)((ulong)*param_3 >> 0x10) == *(int *)0xb928) && ((int)*param_3 == *(int *)0xb926)) ||
     (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb92c && ((int)*param_3 == *(int *)0xb92a)))) ||
    (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb934 && ((int)*param_3 == *(int *)0xb932)))) ||
   (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb930 && ((int)*param_3 == *(int *)0xb92e)))) {
  // Item is equipped
  if (*(char *)((int)*param_3 + 0x14) == '\0') {
    if (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb928) && ((int)*param_3 == *(int *)0xb926)) {
      *(undefined2 *)0xb926 = 0;
      *(undefined2 *)0xb928 = 0;
      *(undefined2 *)0xb87c = 0;
    }
  }
}
```

### After:
```c
// Check if item is currently equipped
if (item_ptr == equipped_weapon ||
    item_ptr == equipped_armor ||
    item_ptr == equipped_helmet ||
    item_ptr == equipped_shield) {

  // Only allow unequip if item is not cursed
  if (!item_ptr->cursed) {
    if (item_ptr == equipped_weapon) {
      equipped_weapon = NULL;
      player_armor_bonus_1 = 0;  // Weapon contributes to armor?
    }
    // Similar for other equipment slots...
  } else {
    // Cannot unequip cursed item
    *can_unequip = false;
    if (show_message) {
      display_score_with_fatal(ERROR_MSG_CURSED_ITEM);
    }
  }
}
```

---

## Example 7: Coordinate Bounds Check

### Before:
```c
undefined1 is_position_in_bounds(undefined2 param_1,int param_2,int param_3)
{
  undefined1 uVar1;

  if ((((param_3 < 1) || (0x16 < param_3)) || (param_2 < 1)) || (0x4f < param_2)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}
```

### After:
```c
bool is_position_in_bounds(int x, int y)
{
  // Check if coordinates are within map boundaries
  // Map is 79 tiles wide (1-79) and 22 tiles high (1-22)
  if (y < 1 || y > MAP_HEIGHT || x < 1 || x > MAP_WIDTH) {
    return false;
  }
  return true;
}
```

---

## Example 8: Tile Exploration

### Before:
```c
if (*(char *)(param_3 * 0x4f + param_2 + -0xc) == ' ') {
  if (*(char *)(*(int *)0xe52d * 0x719 + param_3 * 0x4f + param_2 + 0x70d) != '\0') {
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    iVar3 = (int)uVar1 + param_3 * 0x4f + param_2;
    uVar4 = iVar3 == 0;
    uVar7 = CONCAT11((char)((uint)(param_3 * 0x4f) >> 8),*(undefined1 *)(iVar3 + -0x50));
  }
  if (*(char *)0xb8ee == '\0') {
    *(undefined1 *)(*(int *)0xe52d * 0x719 + param_3 * 0x4f + param_2 + 0x70d) = 1;
  }
}
```

### After:
```c
int tile_index = y * MAP_WIDTH + x;
char display_char = display_buffer[tile_index];

if (display_char == CHAR_FLOOR) {
  // Check if tile was already explored
  if (level_data->explored[tile_index]) {
    // Get actual tile character from level data
    char tile_char = level_data->tiles[tile_index];
    // Process visible explored tile...
  }

  // Mark tile as explored (unless in wizard mode)
  if (!flag_show_all_terrain) {
    level_data->explored[tile_index] = 1;
  }
}
```

---

## Key Transformation Patterns

### Pattern 1: Memory Address Access
```c
// Before
*(int *)0xb86c

// After
player_x
```

### Pattern 2: Array with Negative Offset
```c
// Before
*(int *)(index * 4 + -0x46cc)

// After
inventory_items[index]
```

### Pattern 3: Structure Field Access
```c
// Before
*(int *)((int)item_ptr + 0x09)

// After
item_ptr->uses_remaining
```

### Pattern 4: Loop Counter
```c
// Before
local_4 = 1;
while (true) {
  // code
  if (local_4 == max) break;
  local_4 = local_4 + 1;
}

// After
for (int index = 1; index <= max; index++) {
  // code
}
```

### Pattern 5: Boolean Flag
```c
// Before
char local_4 = '\0';
if (condition) {
  local_4 = '\x01';
}

// After
bool found = false;
if (condition) {
  found = true;
}
```

---

## Notes on Transformations

1. **Segment Offsets**: The `>> 0x10` pattern extracts the high word (segment) from a far pointer
2. **Sign Extension**: The `>> 0xf` pattern extracts the sign bit (bit 15) for signed number display
3. **CONCAT11**: Combines high byte and low byte - usually can be simplified
4. **Coordinate Order**: Sometimes X and Y are swapped; verify against actual gameplay
5. **Array Indices**: Many arrays use 1-based indexing, not 0-based
6. **Pascal Strings**: First byte is length, then characters (no null terminator)

---

For complete reference, see:
- `VARIABLE_NAMING_GUIDE.md` - Full documentation
- `variable_mappings.json` - Machine-readable mappings
- `QUICK_REFERENCE.md` - Quick lookup cheat sheet
