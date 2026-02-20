# MORIA Inventory & Object Management System

Reverse-engineered from `MORIA_with_constants.C` (DOS MORIA 1.9.8.7 French).

## Table of Contents

1. [Data Structures](#1-data-structures)
2. [Memory Allocation](#2-memory-allocation)
3. [Linked List Operations](#3-linked-list-operations)
4. [Item Pickup](#4-item-pickup)
5. [Item Drop](#5-item-drop)
6. [Equipment System](#6-equipment-system)
7. [Identification & Discovery](#7-identification--discovery)
8. [Belt / Quick-Access Slots](#8-belt--quick-access-slots)
9. [Item Flow Diagram](#9-item-flow-diagram)

---

## 1. Data Structures

### Monster Object (54 bytes, 0x36)

```
struct MonsterObject {
    char   attack_char;          // +0x00  Display/attack character
    char   visible_char;         // +0x01  Currently rendered character
    int16  template_index;       // +0x02  Monster template ID
    int16  original_template;    // +0x04  Backup for shapeshift
    int16  experience_value;     // +0x06  XP on kill
    int16  to_hit;               // +0x08  Attack bonus
    int16  hit_points;           // +0x0A  Current HP
    int16  armor_class;          // +0x0C  Defense
    int16  num_attacks;          // +0x0E  Attacks per round
    int16  damage_per_attack;    // +0x10  Max damage per hit
    int16  level;                // +0x12  Difficulty level
    int16  speed_bonus;          // +0x14  Random to-hit factor
    int16  item_drop_chance;     // +0x16  1/N chance of carrying item
    int16  item_drop_type;       // +0x18  Item type for drop
    int16  special_ability_1;    // +0x1A  Special ability flag
    int16  y_position;           // +0x1C  Map row
    int16  x_position;           // +0x1E  Map column
    int16  status_timer;         // +0x20  Flee/sleep countdown
    char   is_fleeing;           // +0x22  Flee behavior
    char   is_visible;           // +0x23  Player can see it
    char   is_awake;             // +0x24  Alert state
    char   is_alerted;           // +0x25  Pursuit mode
    char   move_toggle;          // +0x26  Half-speed toggle (0↔1)
    char   is_invisible;         // +0x27  Monster invisibility
    char   is_hostile;           // +0x28  Aggression flag
    char   is_stationary;        // +0x29  Never-moves flag
    int16  stun_timer;           // +0x2A  Paralysis countdown
    int16  unknown_2c;           // +0x2C  Init=1, purpose unclear
    far*   carried_item;         // +0x2E  Pointer to carried item (lo/hi)
    far*   next_ptr;             // +0x32  Next in linked list (lo/hi)
};
```

**Linked list pointer**: `+0x32/+0x34` (far pointer, lo/hi words)
**Free list head**: `0xABA7/0xABA9`
**Per-level list head**: `dungeon_level * 4 + (-0x5499)`

### Item Object (26 bytes, 0x1A)

```
struct ItemObject {
    char   item_type;            // +0x00  Type (0=gold..8=light_source)
    int16  subtype;              // +0x01  Sub-ID within type
    int16  quantity;             // +0x03  Stack count (init=1)
    int16  y_position;           // +0x05  Map row (ground items)
    int16  x_position;           // +0x07  Map column
    int16  power;                // +0x09  Bonus/charges/attack value
    int16  weight;               // +0x0B  Encumbrance
    int32  gold_value;           // +0x0D  Monetary value (32-bit)
    int16  unique_id;            // +0x11  Serial number for matching
    char   is_identified;        // +0x13  0=unidentified
    char   is_cursed;            // +0x14  Prevents unequipping
    char   is_enchanted;         // +0x15  Prevents acid damage
    far*   next_ptr;             // +0x16  Next in linked list (lo/hi)
};
```

**Linked list pointer**: `+0x16/+0x18` (far pointer, lo/hi words)
**Free list head**: `0xABAB/0xABAD`
**Per-level ground list head**: `dungeon_level * 4 + (-0x54D9)`
**Inventory list head**: `0xB91E` (ADDR_INVENTORY_LIST)

### Global Pointers

| Address | Name | Description |
|---------|------|-------------|
| 0xB91E | `inventory_list` | Head of player inventory linked list |
| 0xB920 | `inventory_list_hi` | High word of inventory list pointer |
| 0xB922 | `wielded_weapon` | Equipped weapon pointer (lo) |
| 0xB924 | `wielded_weapon_hi` | High word |
| 0xB926 | `equipped_shield` | Equipped shield pointer (lo) |
| 0xB928 | `equipped_shield_hi` | High word |
| 0xB92A | `equipped_armor` | Equipped armor pointer (lo) |
| 0xB92C | `equipped_armor_hi` | High word |
| 0xB92E | `equipped_ring1` | Ring slot 1 pointer (lo) |
| 0xB930 | `equipped_ring1_hi` | High word |
| 0xB932 | `equipped_ring2` | Ring slot 2 pointer (lo) |
| 0xB934 | `equipped_ring2_hi` | High word |
| 0xB936 | `belt_slot_count` | Number of belt/quick-access slots in use |
| 0xB8C0 | `total_item_type_count` | Sum of all item-type counters |
| 0xB8C2 | `inventory_item_count` | Number of distinct items in inventory list |
| 0xB8C4 | `carried_weight` | Total weight of inventory |
| 0xB8C6 | `max_carry_weight` | Weight capacity |

### Per-Type Index Table

`type * 4 + (-0x4738)` — 32-bit counter of items of each type in inventory.

### Light Source Index

`subtype * 4 + (-0x476C)` — pointer to light source item by subtype.
Rebuilt by `build_object_index()` whenever a light source is added/removed.

### Belt Slot Array

`slot * 4 + (-0x46CC)` — array of 4 far pointers to belt items (1-indexed, slots 1..belt_slot_count).

---

## 2. Memory Allocation

### allocate_monster_object (line 371)

```
function allocate_monster_object() -> MonsterObject*:
    if monster_free_list == NULL:
        ptr = heap_alloc(0x36)          // 54 bytes
        total_monster_allocs += 1       // counter at 0xE52F
    else:
        ptr = monster_free_list         // pop from free list
        monster_free_list = ptr.next_ptr
    ptr.next_ptr = NULL                 // clear linkage
    return ptr
```

### free_monster_object (line 401)

```
function free_monster_object(ptr: MonsterObject*):
    ptr.next_ptr = monster_free_list    // push onto free list
    monster_free_list = ptr
```

### allocate_item_object (line 421)

```
function allocate_item_object() -> ItemObject*:
    if item_free_list == NULL:
        ptr = heap_alloc(0x1A)          // 26 bytes
        total_item_allocs += 1          // counter at 0xE531
    else:
        ptr = item_free_list            // pop from free list
        item_free_list = ptr.next_ptr
    ptr.next_ptr = NULL                 // clear linkage
    ptr.quantity = 1                    // always init to 1
    return ptr
```

### free_item_object (line 452)

```
function free_item_object(ptr: ItemObject*):
    ptr.next_ptr = item_free_list       // push onto free list
    item_free_list = ptr
```

**Pattern**: Both monster and item allocators use a singly-linked free list as a memory pool. When the free list is empty, they fall back to heap allocation (`read_stream_data`). Objects are never returned to the heap — once allocated, they cycle between active lists and the free list for the rest of the game.

---

## 3. Linked List Operations

### prepend_item_to_list (line 1266)

```
function prepend_item_to_list(list_head: far*, item: ItemObject*):
    item.next_ptr = *list_head          // point to current head
    *list_head = item                   // new head
```

Simple O(1) prepend. Used for adding items to floor lists and some inventory operations.

### remove_item_from_list (line 1211)

```
function remove_item_from_list(list_head: far*, target: ItemObject*):
    if *list_head == NULL:
        return                          // empty list, nothing to do

    if *list_head == target:            // removing head
        *list_head = target.next_ptr
    else:
        prev = *list_head               // walk list to find predecessor
        while prev.next_ptr != NULL and prev.next_ptr != target:
            prev = prev.next_ptr
        if prev.next_ptr == NULL:
            FATAL_ERROR("item not found in list")
        else:
            prev.next_ptr = target.next_ptr   // unlink target

    // If removing a light source (type 8), rebuild light index
    if target.item_type == 8:
        light_index[target.subtype] = NULL
        build_object_index()            // rescan inventory for lights
```

Standard singly-linked list removal with O(n) predecessor search. Fatal error if item not found. Special handling for light sources: clearing and rebuilding the light source index table.

### find_item_at_coords (line 123)

```
function find_item_at_coords(result: far*, y: int, x: int):
    ptr = level_monster_list[dungeon_level]
    while ptr != NULL:
        if ptr.y_position == y and ptr.x_position == x:
            *result = ptr
            return
        ptr = ptr.next_ptr              // monster next at +0x32

    // Not found — fatal error
    FATAL_ERROR("no item at coordinates")
```

Walks the per-level monster list matching (y, x) coordinates. Note: despite the name, this searches the **monster** list (using +0x32 offset for next_ptr, which is the monster chain offset). Used to find a monster at a specific map position.

### build_object_index (line 581)

```
function build_object_index():
    ptr = inventory_list                // walk entire inventory
    while ptr != NULL:
        if ptr.item_type == 8:          // light source
            light_index[ptr.subtype] = ptr
        ptr = ptr.next_ptr              // item next at +0x16
```

Rebuilds the light source index by scanning the entire inventory list. Called after any removal of a light source item.

---

## 4. Item Pickup

### pickup_item (line 7233)

The most complex function in the inventory system. Handles gold, spell scrolls, stacking, and sorted insertion.

```
function pickup_item():
    find_ground_item_at_player_position(floor_item)
    display_message("Vous ramassez:")    // msg 0x75 "You pick up:"
    display_item_description(floor_item)

    // === GOLD HANDLING ===
    if floor_item.item_type == 0:        // gold
        gold += floor_item.power         // add to purse (32-bit)
        remove_item_from_list(level_ground_list, floor_item)
        free_item_object(floor_item)
        map[player_y][player_x] = ' '   // clear floor tile
        display_stats()
        return

    // === WEIGHT CHECK ===
    over_weight = (carried_weight + floor_item.weight > max_carry_weight)

    // === SPELL SCROLL HANDLING ===
    if floor_item.item_type == 4:        // wand/scroll type
        if floor_item.subtype > 6:       // spell scroll
            learn_spell(floor_item)
            // skip normal pickup, consume scroll
            return

    // === STANDARD PICKUP ===
    // Increment per-type counter
    type_count[floor_item.item_type] += 1
    total_item_type_count += 1
    carried_weight += floor_item.weight

    // Special: picking up a torch (type 8, subtype 0)
    if floor_item.item_type == 8 and floor_item.subtype == 0:
        has_light = 1

    // Remove from floor
    remove_item_from_list(level_ground_list, floor_item)
    map[floor_item.y][floor_item.x] = ' '

    // Update light source index
    if floor_item.item_type == 8:
        light_index[floor_item.subtype] = floor_item

    // === TRY TO STACK ===
    stacked = false
    slot_num = 1
    inv_ptr = inventory_list
    while inv_ptr != NULL and not stacked:
        if inv_ptr.item_type == floor_item.item_type:
            // Types 2,3 (potion, scroll): stack by matching subtype
            if inv_ptr.subtype == floor_item.subtype
                    and floor_item.item_type != 1:   // not food
                goto STACK

            // Type 7 subtype 12 (arrows): stack by matching unique_id
            if is_type_7_subtype_12(floor_item):
                if is_type_7_subtype_12(inv_ptr)
                        and floor_item.unique_id == inv_ptr.unique_id:
                    goto STACK

        slot_num += 1
        inv_ptr = inv_ptr.next_ptr
        continue

    STACK:
        stacked = true

        // If stackable ammo (type 7 sub 12), undo the per-type count
        if is_type_7_subtype_12(floor_item)
                and floor_item.unique_id == inv_ptr.unique_id:
            type_count[floor_item.item_type] -= 1
            total_item_type_count -= 1
            carried_weight -= floor_item.weight

        // Merge quantities
        inv_ptr.quantity += floor_item.quantity

        // Display: "ramassé  a)" or similar slot label
        display_slot_letter(slot_num)
        free_item_object(floor_item)

    // === INSERT SORTED BY TYPE ===
    if not stacked:
        inventory_item_count += 1

        if inventory_list == NULL
                or floor_item.item_type < inventory_list.item_type:
            // Insert at head
            floor_item.next_ptr = inventory_list
            inventory_list = floor_item
            display_message("rangé dans le sac")  // msg 0x9093
        else:
            // Walk list to find insertion point (sorted by type)
            slot_num = 2
            prev = inventory_list
            while prev.next_ptr != NULL
                    and floor_item.item_type > prev.next_ptr.item_type:
                prev = prev.next_ptr
                slot_num += 1

            // Insert after prev
            floor_item.next_ptr = prev.next_ptr
            prev.next_ptr = floor_item

            // Display slot label
            display_slot_letter(slot_num)

    if over_weight:
        FATAL_ERROR("Trop lourd!")       // msg 0x4A "Too heavy!"
```

**Key details**:
- Gold is handled as a special case — added directly to purse, never enters inventory.
- Spell scrolls (type 4, subtype > 6) trigger `learn_spell` and are consumed.
- Items are inserted into inventory **sorted by `item_type`** (ascending).
- Stacking matches by type+subtype for potions/scrolls, or by type+unique_id for arrows (type 7, subtype 12).
- When arrows stack, the per-type counter is decremented (since they merge into one logical item).
- Slot labels use letters: slots 1-26 → 'a'-'z', slots 27+ → 'A'-'Z'.

---

## 5. Item Drop

### drop_item (line 7647)

```
function drop_item(item: ItemObject*):
    // Check if equipped, handle unequip
    success = false
    handle_item_drop_or_unequip(0, &success, item)

    if success:
        display_message("Vous posez:")   // msg 0x76 "You put down:"
        display_item_description(item)

        // Remove from inventory, place on floor
        destroy_or_consume_item(1, 1, item)    // force_remove=1, drop_to_floor=1

        // If dropping last light source
        if item.item_type == 8:
            build_object_index()
            if light_index[0] == NULL:   // no torches left
                has_light = 0
                // Clear special tile if on level 1
```

### handle_item_drop_or_unequip (line 632)

Checks all equipment slots and belt slots, prevents dropping cursed items.

```
function handle_item_drop_or_unequip(silent: bool, success: &bool, item: ItemObject*):
    *success = true

    // Check against each equipment slot
    if item == equipped_shield:
        if item.is_cursed:
            *success = false
            if not silent: display_message("Maudit!")   // msg 0x4F "Cursed!"
        else:
            equipped_shield = NULL
            shield_ac_bonus = 0

    else if item == equipped_armor:
        if item.is_cursed:
            *success = false
            if not silent: display_message("Maudit!")
        else:
            equipped_armor = NULL
            armor_ac_bonus = 0

    else if item == equipped_ring2:
        if item.is_cursed:
            *success = false
            if not silent: display_message("Maudit!")
        else:
            equipped_ring2 = NULL
            ring2_bonus = 0

    else if item == equipped_ring1:
        if item.is_cursed:
            *success = false
            if not silent: display_message("Maudit!")
        else:
            equipped_ring1 = NULL

    // Recalculate base AC
    base_ac = shield_ac_bonus + armor_ac_bonus

    else if item == wielded_weapon:
        wielded_weapon = NULL
        weapon_attack_bonus = 0

    else:
        // Check belt slots
        for slot = 1 to belt_slot_count:
            if belt[slot] == item:
                if item.is_cursed:
                    *success = false
                    if not silent: display_message("Maudit!")  // msg 0x4E
                else:
                    belt[slot] = NULL
```

### destroy_or_consume_item (line 1286)

Handles removing an item from inventory — either consuming one from a stack or removing entirely.

```
function destroy_or_consume_item(force_remove: bool, drop_to_floor: bool, item: ItemObject*):
    is_ammo = is_type_7_subtype_12(item)

    // Full removal: quantity==1, or force_remove on ammo
    if (not is_ammo) or force_remove or item.quantity == 1:
        // Decrement per-type counter
        type_count[item.item_type] -= 1
        total_item_type_count -= 1

    if item.quantity == 1
            or (is_ammo and force_remove):
        // Remove entire item from inventory list
        remove_item_from_list(&inventory_list, item)
        inventory_item_count -= 1
        carried_weight -= item.weight

        if drop_to_floor:
            // Move to ground: prepend to level ground list
            prepend_item_to_list(&level_ground_list[dungeon_level], item)
            item.y_position = player_y
            item.x_position = player_x
            map_char = lookup_display_char(item)
            map[item.y][item.x] = map_char
        else:
            // Destroy permanently
            free_item_object(item)
    else:
        // Decrement stack quantity
        item.quantity -= 1
        if not is_ammo:
            carried_weight -= item.weight

        if drop_to_floor:
            // Create a new single item on floor
            new_item = allocate_item_object()
            memcpy(new_item, item, 0x1A)     // copy 26 bytes
            new_item.quantity = 1
            prepend_item_to_list(&level_ground_list[dungeon_level], new_item)
            new_item.y_position = player_y
            new_item.x_position = player_x
            map_char = lookup_display_char(new_item)
            map[new_item.y][new_item.x] = map_char
```

**Key details**:
- `is_type_7_subtype_12` checks for arrows/ammunition — these use special stacking rules.
- If `quantity > 1` and not force-removing, only one item is split off: a new `ItemObject` is allocated, the original's quantity is decremented, and the clone is placed on the floor.
- If `quantity == 1`, the entire item node is unlinked from inventory and either freed or moved to the ground list.
- The `drop_to_floor` parameter controls whether the item is destroyed (consumed potion) or dropped (player action).

---

## 6. Equipment System

### equip_item (line 7841)

```
function equip_item(item: ItemObject*):
    // Already wielding this weapon?
    if item == wielded_weapon:
        display_message("Déjà équipé")   // msg 0x78 "Already equipped"
        return

    if item.item_type == 7:              // WEAPON
        display_message("Vous brandissez:")  // msg 0xAF "You brandish:"
        display_item_description(item)
        wielded_weapon = item
        // Attack bonus: base_weapon_attack[subtype] + item.power
        weapon_attack_bonus = weapon_base_attack[item.subtype] + item.power
        display_food_status()

    else if item.item_type == 6:         // EQUIPMENT
        if current_food >= 29:           // need food > 0x1D to equip
            display_message("Trop faible")  // msg 0xC8 "Too weak"
            return

        subtype = item.subtype
        equipped = false

        if subtype == 7:                 // ARMOR
            if equipped_armor == NULL:
                equipped_armor = item
                // AC = average(sign(power), power)
                armor_ac_bonus = (sign(item.power) + item.power) / 2
                equipped = true
            else:
                display_message("Déjà porté")  // "Already wearing"

        else if subtype == 8:            // RING (slot 2)
            if equipped_ring2 == NULL:
                equipped_ring2 = item
                ring2_bonus = item.power
                equipped = true
            else:
                display_message("Déjà porté")

        else if subtype >= 9 and subtype <= 11:  // RING (slot 1)
            if equipped_ring1 == NULL:
                equipped_ring1 = item
                equipped = true
            else:
                display_message("Déjà porté")

        else:                            // SHIELD (all other subtypes)
            if equipped_shield == NULL:
                equipped_shield = item
                // AC = base_shield_defense[subtype] + item.power
                shield_ac_bonus = shield_base_defense[item.subtype] + item.power
                equipped = true
            else:
                display_message("Déjà porté")

        // Recalculate total AC
        base_ac = shield_ac_bonus + armor_ac_bonus

        // Auto-identify rings on equip (subtypes 9-11)
        if equipped:
            if item.subtype in [9, 10, 11]:
                item.is_identified = 1

    display_stats()
```

**Equipment slot mapping** (type 6 subtypes):

| Subtype | Slot | Equipment |
|---------|------|-----------|
| 7 | Armor | `equipped_armor` (0xB92A) |
| 8 | Ring 2 | `equipped_ring2` (0xB932) |
| 9, 10, 11 | Ring 1 | `equipped_ring1` (0xB92E) |
| Other | Shield | `equipped_shield` (0xB926) |

**AC calculation**: `base_ac = shield_ac_bonus + armor_ac_bonus`
- Shield: `shield_base_defense[subtype] + item.power` (table at `subtype * 4 + (-0x61E5)`)
- Armor: `(sign(power) + power) / 2`
- Weapon: `weapon_base_attack[subtype] + item.power` (table at `subtype * 4 + (-0x6185)`)

### remove_equipped_item_menu (line 7960)

Interactive menu for removing equipped items.

```
function remove_equipped_item_menu():
    options = ""
    valid_keys = {}

    if equipped_shield != NULL:
        options += "a"                   // 'a' = shield (bouclier/armure)
        valid_keys.add('a')

    if equipped_armor != NULL:
        options += "h"                   // 'h' = harnois (armor)
        valid_keys.add('h')

    if equipped_ring2 != NULL:
        options += "c"                   // 'c' = chaînette (ring chain)
        valid_keys.add('c')

    if equipped_ring1 != NULL:
        options += "g"                   // 'g' = gemme (gem/ring)
        valid_keys.add('g')

    if options is empty:
        display_message("Rien à retirer")  // msg 0x46 "Nothing to remove"
        return

    // Find default selection (last valid key)
    // ... cascading fallback logic to pick default ...

    // Prompt player for choice
    repeat:
        display_message("Retirer quoi?")  // msg 0x57 "Remove what?"
        key = read_keyboard()
        if key not in valid_keys:
            beep()
    until key in valid_keys

    // Process removal
    if key == 'a':
        if equipped_shield == NULL:
            display_message("Pas d'armure")
        else if equipped_shield.is_cursed:
            display_message("Maudit!")      // msg 0x147
        else:
            equipped_shield = NULL
            shield_ac_bonus = 0
            success = true

    if key == 'h':
        if equipped_armor == NULL:
            display_message("Pas d'armure")
        else if equipped_armor.is_cursed:
            display_message("Maudit!")      // msg 0x58
        else:
            equipped_armor = NULL
            armor_ac_bonus = 0
            success = true

    if key == 'c':
        if equipped_ring2 == NULL:
            display_message("Pas d'anneau")
        else if equipped_ring2.is_cursed:
            display_message("Maudit!")      // msg 0x147
        else:
            equipped_ring2 = NULL
            ring2_bonus = 0
            success = true

    if key == 'g':
        if equipped_ring1 == NULL:
            display_message("Pas d'anneau")
        else if equipped_ring1.is_cursed:
            display_message("Maudit!")      // msg 0x4F
        else:
            equipped_ring1 = NULL
            success = true

    // Show removed item info
    if success and not item.is_cursed:
        display_message("Retiré:")      // msg 0xB8 "Removed:"
        display_item_description(item)

    // Recalculate AC
    base_ac = shield_ac_bonus + armor_ac_bonus
    display_stats()
```

**Menu key assignments**:
- `a` (0x61) = Shield (bouclier)
- `h` (0x68) = Armor (harnois)
- `c` (0x63) = Ring 2 (chaînette)
- `g` (0x67) = Ring 1 (gemme)

---

## 7. Identification & Discovery

Two separate systems control whether an item's true nature is revealed:

### Per-Type Identification Table

Address: `type * 0x18 + subtype + (-0x65A2)`

One byte per (type, subtype) pair. When set to 1, all items of that type+subtype show their true name instead of the randomized appearance name (e.g., "potion rouge" → "potion de guérison").

### Per-Type User-Naming Table

Address: `type * 0x18 + subtype + (-0x6542)`

One byte per (type, subtype). Set to 1 when the player has entered a custom description for this item kind.

### Per-Type Custom Description

Address: `type * 0x2B8 + subtype * 0x1D + (-0x75DE)`

Pascal-style string (max 28 chars). Player-entered description for a type+subtype combo (e.g., "guérison" for a red potion). Read/written via `read_string_from_file` / `read_line`.

### identify_item (line 7686)

Called when the player uses an identify action on an inventory item.

```
function identify_item(item: ItemObject*):
    type = item.item_type

    // Only identifiable types: 2 (potion), 3 (scroll), 4 (wand), 5 (gem)
    if type in [1, 7, 6, 8]:
        display_message("Non identifiable")  // msg 0x40
        return

    if type not in [2, 3, 4, 5]:
        return                           // silently ignore other types

    // Already identified at type level?
    if identification_table[type * 0x18 + item.subtype] != 0:
        display_message("Déjà identifié")  // msg 0x77 "Already identified"
        return

    // Display identification message
    if item.quantity == 1:
        display_message("C'est un(e):")  // msg: singular
    else:
        display_message("Ce sont des:")  // msg: plural

    display_item_description(item)
    wait_for_keypress()

    // Ask player to name this item type
    if item.quantity < 2:
        display_message("Mémoriser sous le nom de (singulier):")
    else if item.quantity >= 2:
        display_message("Mémoriser sous le nom de (pluriel):")

    display_message("Entrez le nom:")    // msg 0x9A83

    // Read player input into custom description buffer
    read_string_to(custom_desc[type][item.subtype], max=28)

    // Check if user-entered name is non-empty
    if user_naming_table[type * 0x18 + item.subtype] == 0:
        if custom_desc[type][item.subtype] == "":
            user_naming_table[type * 0x18 + item.subtype] = 0
        else:
            user_naming_table[type * 0x18 + item.subtype] = 1
```

**Key point**: `identify_item` does NOT set the per-type identification table — it only lets the player assign a custom name. The actual type-level identification is done by `discover_item`.

### discover_item (line 7795)

Called when the player uses/consumes an item, revealing its true identity.

```
function discover_item(item: ItemObject*):
    type = item.item_type

    // Only discover types 2-5 (potion, scroll, wand, gem)
    if type not in [2, 3, 4, 5]:
        // do nothing for other types
    else:
        // Set type-level identification
        identification_table[type * 0x18 + item.subtype] = 1

    // Set item-level identification
    if item.item_type == 8:              // light source
        if item.is_cursed == 0:
            item.is_identified = 1       // identify if not cursed
        else:
            item.is_cursed = 0           // un-curse instead
    else:
        item.is_identified = 1

    // Special: identifying the Silmaril (type 1, qty 1)
    if item.item_type == 1 and item.quantity == 1:
        display_message("Silmaril!")     // msg 0xB7
    else:
        display_item_description(item)
```

**Key point**: `discover_item` sets the per-type identification table entry, making ALL items of that type+subtype permanently identified for the rest of the game. It also sets the individual item's `is_identified` flag. For light sources (type 8), discovering an uncursed one identifies it, but discovering a cursed one removes the curse instead.

### Identification Flow Summary

1. **Unidentified state**: Item displays randomized appearance name (e.g., "potion rouge").
2. **Player identifies** (`identify_item`): Can assign a custom name (e.g., "guérison"). Does NOT reveal true type.
3. **Player uses/consumes** (`discover_item`): Sets `identification_table[type][subtype] = 1`. From now on, ALL items of this type+subtype show their true name.
4. **Equipping rings** (subtypes 9-11): Auto-sets `is_identified = 1` on the individual item (but not the type-level table).

---

## 8. Belt / Quick-Access Slots

The belt system provides 4 quick-access slots for consumable items, separate from the main inventory list.

### Data Layout

- `belt[slot]` = `slot * 4 + (-0x46CC)` — far pointer to item (1-indexed)
- `belt_slot_count` = `0xB936` — number of active belt slots

### decrement_item_quantity (line 472)

Used when a belt item is consumed (e.g., drinking a potion from belt).

```
function decrement_item_quantity(subtype: int):
    for slot = 1 to belt_slot_count:
        if belt[slot] != NULL
                and belt[slot].subtype == subtype:
            belt[slot].power -= 1        // decrement charges/uses
            return                       // stop at first match
```

### check_inventory_has_item (line 498)

Checks if a specific item type exists in the belt slots.

```
function check_inventory_has_item(type: int) -> bool:
    if type == 0:
        // Check if any belt slot is occupied
        for slot = 1 to belt_slot_count:
            if belt[slot] != NULL:
                return true
        return false
    else:
        // Check for specific type with positive power
        for slot = 1 to belt_slot_count:
            if belt[slot] != NULL
                    and belt[slot].subtype == type
                    and belt[slot].power > 0:
                return true
        return false
```

### count_item_total_quantity (line 605)

Counts total charges/power across all belt items of a given subtype.

```
function count_item_total_quantity(result: &int, subtype: int):
    *result = 0
    for slot = 1 to belt_slot_count:
        if belt[slot] != NULL
                and belt[slot].subtype == subtype:
            *result += belt[slot].power
```

### is_item_equipped_or_in_pack (line 1360)

Checks if a given item pointer is in any equipment slot or belt slot.

```
function is_item_equipped_or_in_pack(item: ItemObject*) -> bool:
    // Check equipment slots
    if item == equipped_shield
            or item == wielded_weapon
            or item == equipped_ring2
            or item == equipped_armor
            or item == equipped_ring1:
        return true

    // Check belt slots
    for slot = 1 to belt_slot_count:
        if belt[slot] != NULL and belt[slot] == item:
            return true

    return false
```

---

## 9. Item Flow Diagram

```
                        ┌─────────────────┐
                        │   FLOOR          │
                        │ (per-level list) │
                        │ level*4+(-54D9)  │
                        └───────┬─────────┘
                                │
                    pickup_item │ ▲ destroy_or_consume_item
                    (remove +   │ │ (drop_to_floor=1)
                     sorted     │ │
                     insert)    ▼ │
                        ┌─────────────────┐
                        │   INVENTORY      │
                        │ (linked list)    │
                        │ head: 0xB91E     │
                        │ sorted by type   │
                        └──┬──────────┬────┘
                           │          │
              equip_item   │          │ handle_item_drop_or_unequip
              (set slot    │          │ (clear slot ptr)
               pointer)    ▼          │
                    ┌─────────────────┐
                    │  EQUIPMENT      │
                    │  SLOTS          │
                    │  weapon: 0xB922 │
                    │  shield: 0xB926 │
                    │  armor:  0xB92A │
                    │  ring1:  0xB92E │
                    │  ring2:  0xB932 │
                    └─────────────────┘

                    ┌─────────────────┐
                    │  BELT SLOTS     │
                    │  slot*4+(-46CC) │
                    │  max 4 slots    │
                    │  count: 0xB936  │
                    └─────────────────┘

                    ┌─────────────────┐
                    │  FREE LIST      │
                    │  items:  0xABAB │
                    │  monsters:0xABA7│
                    └─────────────────┘
```

### Item Lifecycle

1. **Spawning**: `initialize_monster_or_item()` creates an item from templates via `allocate_item_object()`, places it on the floor list.

2. **Pickup**: `pickup_item()` removes from floor list. Gold goes directly to purse. Otherwise: try to stack with existing inventory item (matching type+subtype or type+unique_id for ammo). If no stack target, insert sorted by `item_type` into the inventory linked list.

3. **Equipment**: `equip_item()` sets a global equipment slot pointer to the item (item remains in inventory list). Equipment slots are just pointers into the inventory list — the item is not moved.

4. **Unequip**: `remove_equipped_item_menu()` or `handle_item_drop_or_unequip()` clears the slot pointer and recalculates AC. Cursed items cannot be unequipped.

5. **Drop**: `drop_item()` → `handle_item_drop_or_unequip()` (unequip if needed) → `destroy_or_consume_item(force=1, drop=1)` (move to floor).

6. **Consume**: Using a potion/scroll → `destroy_or_consume_item(force=0, drop=0)` → if stacked, decrement quantity; if last one, unlink and free.

7. **Free**: `free_item_object()` pushes the 26-byte block onto the item free list for reuse.

### Stacking Rules

| Item Type | Stack Match | Notes |
|-----------|------------|-------|
| Type 2 (Potion) | type + subtype | All potions of same kind stack |
| Type 3 (Scroll) | type + subtype | All scrolls of same kind stack |
| Type 7 sub 12 (Arrows) | type + unique_id | Arrows from same source stack |
| All others | No stacking | Each is a separate inventory entry |

### Equipment ≠ Separate Storage

A critical design detail: **equipment slots are pointers into the inventory list, not separate storage**. When you equip a sword, the sword item stays in the inventory linked list — the `wielded_weapon` global simply points to that same node. This means:
- The item appears in both inventory traversal and equipment checks.
- Dropping an equipped item requires clearing the equipment pointer first.
- `is_item_equipped_or_in_pack()` checks both equipment slot pointers and belt slot pointers.
