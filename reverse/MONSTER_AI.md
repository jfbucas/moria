# MORIA DOS 1.9.8.7 — Monster AI & Movement

Reverse-engineered from `MORIA_with_constants.C` functions: `update_all_monsters` (line 11313),
`validate_tile_movement` (line 10920), `calculate_movement_direction` (line 11040),
`move_entity_on_map` (line 11090), `is_tile_passable` (line 11713), `is_position_in_bounds`
(line 707). Cross-referenced with `ENTITY_DATABASE.md` (monster templates) and `MEMORY_MAP.md`
(monster object structure).

---

## Table of Contents

1. [Monster Decision-Making Overview](#1-monster-decision-making-overview)
2. [Speed System & Turn Order](#2-speed-system--turn-order)
3. [Main AI Loop (update_all_monsters)](#3-main-ai-loop-update_all_monsters)
4. [Movement Direction Calculation](#4-movement-direction-calculation)
5. [Tile Validation & Pathfinding](#5-tile-validation--pathfinding)
6. [Movement Execution](#6-movement-execution)
7. [Special Monster Behaviors](#7-special-monster-behaviors)
8. [Fleeing Behavior](#8-fleeing-behavior)
9. [Door & Wall Interaction](#9-door--wall-interaction)
10. [Visibility & Awareness](#10-visibility--awareness)
11. [Helper Functions](#11-helper-functions)

---

## 1. Monster Decision-Making Overview

Each monster's behavior is determined by a combination of:

1. **Type flags** (from template):
   - `is_stationary` (0x29): Boss monsters never move
   - `is_hostile` (0x28): Aggressive (always) vs passive (until attacked)
   - `is_invisible` (0x27): Cannot be seen even with light

2. **State flags** (dynamic):
   - `is_awake` (0x24): Monster is active and aware
   - `is_alerted` (0x25): Monster is pursuing the player
   - `is_fleeing` (0x22): Monster moves away from player
   - `move_toggle` (0x26): Toggles 0↔1 each turn (implements half-speed)
   - `stun_timer` (0x2A): Paralysis countdown; can't act while > 0

3. **Special behaviors** (by `attack_char`):
   - `'E'` (Eye of Sauron): Never becomes hostile, doesn't move
   - `'H'` (Huorn): Only becomes hostile when adjacent to player
   - `'X'` (The Watcher): Can't move onto stairs on level 0
   - `'C'`, `'a'` (Bat, Air): Wander randomly when not chasing
   - `0xEA`, `0xE8`, `0x01`, `0xE4` (Ghosts, Sauron, Saruman): HP regeneration

---

## 2. Speed System & Turn Order

### Turn Toggle Mechanism

MORIA implements a **half-speed movement system** using the `move_toggle` field:

```python
def update_all_monsters():
    for monster in monster_list[dungeon_level]:
        # Toggle alternates 0→1→0→1 each turn
        monster.move_toggle = 1 if monster.move_toggle == 0 else 0

        # Monster can only move when toggle is set
        if (monster.is_awake or monster.is_alerted) and monster.move_toggle:
            process_monster_turn(monster)
```

**Result**: All monsters move at **half speed** (every other turn). There is no "fast" movement system — the `speed_bonus` field affects **combat to-hit rolls**, not movement frequency.

### Special Speed Cases

| Monster | `speed_bonus` | Effect |
|---------|--------------|--------|
| Most monsters | 0 | Half-speed movement (every 2 turns) |
| Balrog, Nazgûl | 60 | Same movement speed, but +60 to-hit variance |
| Huorn | 80 | Same movement speed, but +80 to-hit variance |
| Carcharoth | 40 | Same movement speed, but +40 to-hit variance |
| Glaurung | 35 | Same movement speed, but +35 to-hit variance |

**Conclusion**: There are no "fast" or "slow" monsters in terms of movement. All monsters that can move do so at the same rate (every other turn when awake/alerted and toggle is set).

### HP Regeneration (Special Monsters Only)

Some boss monsters regenerate HP over time:

```python
# Ghost type 2 (0xEA) - line 11381
if monster.attack_char == 0xEA:
    if monster.hit_points < 500:
        monster.hit_points += 1
    # Also: 1/65 chance per turn to reveal on map

# Ghost type 1 (0xE8) - line 11394
if monster.attack_char == 0xE8:
    if monster.hit_points < 350:
        monster.hit_points += 1

# Sauron (0x01) - line 11407
if monster.attack_char == 0x01:
    if monster.hit_points < 150:
        monster.hit_points += 1

# Saruman (0xE4) - line 11420
if monster.attack_char == 0xE4:
    if monster.hit_points < 100:
        monster.hit_points += 1
    # Also: 1/70 chance per turn to reveal on map
```

---

## 3. Main AI Loop (update_all_monsters)

**Function**: `update_all_monsters(result_ptr)` (line 11313)

Iterates through all monsters on the current dungeon level, processing each in turn.

### Pseudocode

```python
def update_all_monsters(result_ptr):
    # Trigger special effect if 10+ monsters on level
    if monster_count[dungeon_level] > 9:
        apply_heroism_effect()  # Player buff when outnumbered

    monster = monster_list[dungeon_level]

    while result_ptr != '\0':
        if monster is None:
            return

        # 1. HP Regeneration (boss monsters only)
        if monster.attack_char == 0xEA:  # Ghost 2
            if monster.hit_points < 500:
                monster.hit_points += 1
            if random_mod(0x41) == 0:  # 1/65 chance
                reveal_on_map(monster)

        elif monster.attack_char == 0xE8:  # Ghost 1
            if monster.hit_points < 350:
                monster.hit_points += 1

        elif monster.attack_char == 0x01:  # Sauron
            if monster.hit_points < 150:
                monster.hit_points += 1

        elif monster.attack_char == 0xE4:  # Saruman
            if monster.hit_points < 100:
                monster.hit_points += 1
            if random_mod(0x46) == 0:  # 1/70 chance
                reveal_on_map(monster)

        # 2. Decrement stun timer
        if monster.stun_timer > 0:
            monster.stun_timer -= 1

        # 3. Visibility & Awareness Check
        has_light = check_inventory_has_item(ITEM_LIGHT_SOURCE)

        if not has_light and not status_flag_5:
            # No light — only stationary monsters or special types visible
            if is_wizard:
                goto process_monster  # Wizard mode sees all

            # Check if monster is hostile
            if not monster.is_hostile:
                goto skip_monster

            # Skip if stationary
            if monster.is_stationary:
                goto process_monster

            # Check special visible types (Nazgûl, Eye)
            if monster.attack_char in [0x4E, 0x45]:  # 'N', 'E'
                goto skip_monster

            # Check for Air/Fairy types
            if monster.attack_char in [0x46, 0x61]:  # 'F', 'a'
                goto process_monster

            # Check for Dragons/Balrog
            if monster.attack_char in [0x42, 0x44, 0x92]:  # 'B', 'D', variant
                goto process_monster

            goto skip_monster

        else:
            # Has light — check if monster can be seen
            if monster.is_stationary:
                goto process_monster

            # Check special invisible types (Nazgûl, Eye)
            if monster.attack_char in [0x4E, 0x45]:
                goto process_monster

            # Check for Fairy/Air (can be seen with light)
            if monster.attack_char in [0x46, 0x61]:
                goto process_monster

            goto skip_monster

process_monster:
        # 4. Check stun timer (can't act if stunned)
        if monster.stun_timer > 0:
            monster.move_toggle = 0
            monster = monster.next
            continue

        # 5. Check if awake/alerted
        if not monster.is_awake and not monster.is_alerted:
            # Sleeping monster — skip turn
            monster.move_toggle = 0
            monster = monster.next
            continue

        # 6. Calculate movement direction
        dy = player_y - monster.y_position
        dx = player_x - monster.x_position
        sign_dy = get_sign(dy)
        sign_dx = get_sign(dx)

        # 7. Special monster behaviors

        # Bat/Air: wander randomly when not chasing
        if monster.attack_char in [0x43, 0x61]:  # 'C', 'a'
            # Random wander (50% chance to move randomly)
            if random_mod(2) == 0:
                sign_dy = random_mod(3) - 1  # -1, 0, or 1
                sign_dx = random_mod(3) - 1

        # Eye of Sauron / Huorn: special hostile behavior
        elif monster.attack_char in [0x45, 0x48]:  # 'E', 'H'
            # Huorn only moves when adjacent to player
            if monster.attack_char == 0x48:  # Huorn
                if are_coordinates_adjacent(player_x, player_y, monster.x_position, monster.y_position):
                    # Become hostile and flee
                    if check_some_condition(monster):
                        monster.is_fleeing = 1
                        monster.is_hostile = 0

            # Eye of Sauron never chases
            if monster.is_hostile or monster.is_fleeing:
                # Normal chase/flee logic
                pass
            else:
                # Don't move
                goto skip_movement

        # 8. Fleeing vs Chasing
        if monster.is_fleeing:
            # Move away from player (negate direction)
            move_entity_on_map(monster, -sign_dx, -sign_dy)
        else:
            # Normal chase behavior
            if monster.is_hostile and not monster.is_alerted:
                # Normal movement logic
                move_entity_on_map(monster, sign_dx, sign_dy)

        # 9. Toggle move_toggle for next turn
        monster.move_toggle = 1 if monster.move_toggle == 0 else 0

        # 10. Decrement status_timer
        if (monster.is_alerted or monster.is_awake) and monster.status_timer > 0:
            monster.status_timer -= 1
            if monster.status_timer == 0:
                monster.is_alerted = 0
                monster.is_awake = 0

        # 11. Check for trap tiles (0xF7 = '÷' in CP850)
        map_char = map_overlay[monster.y_position * MAP_WIDTH + monster.x_position]
        if map_char == 0xF7:  # Trap tile
            # Special monster reactions to traps
            if monster.attack_char in [0x41, 0x67, 0x56]:  # 'A', 'g', 'V'
                # Air, goblin, thief die from traps
                kill_monster(monster)
                monster = saved_next_monster
                continue

            elif monster.attack_char in [0x44, 0x92]:  # Dragon types
                # Dragons clear traps
                map_overlay[monster.y_position * MAP_WIDTH + monster.x_position] = 0x20

            else:
                # Other monsters: special trap handling
                # (Balrog, Sauron, Nazgûl, etc. have immunity checks)
                pass

skip_movement:
        # Move to next monster (only if toggle allows or is asleep)
        if monster.is_awake or monster.move_toggle != 0:
            monster = monster.next
        else:
            monster = monster.next

skip_monster:
        monster = monster.next
```

---

## 4. Movement Direction Calculation

**Function**: `calculate_movement_direction(stack_frame)` (line 11040)

Computes the direction toward the player using Manhattan distance prioritization.

### Algorithm

```python
def calculate_movement_direction(monster, target_x, target_y):
    # Store current position
    new_y = monster.y_position
    new_x = monster.x_position

    # Calculate distance components
    dy = target_y - monster.y_position
    dx = target_x - monster.x_position

    # Absolute values for comparison
    abs_dy = abs(dy)
    abs_dx = abs(dx)

    # Prioritize larger distance component
    if abs_dx < abs_dy:
        # Move vertically first
        sign_dy = get_sign(dy)
        if validate_tile_movement(monster, 0, sign_dy):
            new_y += sign_dy
        else:
            # Vertical blocked, try horizontal
            sign_dx = get_sign(dx)
            if validate_tile_movement(monster, sign_dx, 0):
                new_x += sign_dx
    else:
        # Move horizontally first
        sign_dx = get_sign(dx)
        if validate_tile_movement(monster, sign_dx, 0):
            new_x += sign_dx
        else:
            # Horizontal blocked, try vertical
            sign_dy = get_sign(dy)
            if validate_tile_movement(monster, 0, sign_dy):
                new_y += sign_dy

    return (new_y, new_x)
```

**Key insight**: Monster pathfinding is **greedy** — it always moves toward the player along the axis with the greatest distance. No A* or Dijkstra; just "move closer along the bigger gap."

---

## 5. Tile Validation & Pathfinding

**Function**: `validate_tile_movement(monster, dx, dy)` (line 10920)

Checks if a monster can move to a target tile.

### Validation Steps

```python
def validate_tile_movement(monster, dx, dy):
    target_y = monster.y_position + dy
    target_x = monster.x_position + dx

    # 1. Check if tile is empty space
    tile_char = map_overlay[target_y * MAP_WIDTH + target_x]

    # Check against passable tile bitmask (0xb76f table)
    if is_in_bitmask(tile_char, PASSABLE_TILES_MASK):
        if tile_char == ' ':  # 0x20 = empty floor
            return True

    # 2. Check if target is player position (for attack)
    if target_y == player_y and target_x == player_x:
        return True

    # 3. Door/obstacle breaking (based on special_ability_1)
    if random_mod(monster.special_ability_1 + 1) == 6:
        # Monster can break through doors/obstacles
        if in_bounds(target_y, target_x):
            return True

    # 4. Final check: bounds validation
    if not in_bounds(target_y, target_x):
        return False

    # 5. Wall breaking (based on level)
    if random_mod(monster.level + 1) == 9:
        # High-level monsters can occasionally break walls
        if in_bounds(target_y, target_x):
            # Clear the wall tile
            map_overlay[target_y * MAP_WIDTH + target_x] = 0x20
            return True

    return False
```

### Bounds Check

```python
def is_position_in_bounds(y, x):
    # Map boundaries: rows 1-22 (0x16), columns 1-79 (0x4f)
    if y < 1 or y > 0x16:  # 22
        return False
    if x < 1 or x > 0x4f:  # 79
        return False
    return True
```

---

## 6. Movement Execution

**Function**: `move_entity_on_map(monster, dx, dy)` (line 11090)

Executes the actual movement after validation.

### Pseudocode

```python
def move_entity_on_map(monster, dx, dy):
    # Calculate new position
    calculate_movement_direction(monster)  # Updates stack locals
    new_y, new_x = get_calculated_position()

    # Check if movement resulted in no change
    if new_y == monster.y_position and new_x == monster.x_position:
        # Stuck — try random movement
        if random_mod(2) == 0:
            new_y = monster.y_position + random_mod(3) - 1
            new_x = monster.x_position + random_mod(3) - 1
            calculate_movement_direction(monster)
            new_y, new_x = get_calculated_position()

    # Check if new position is player position
    if new_y == player_y and new_x == player_x:
        # Attack player instead of moving

        # Special: 'X' (The Watcher) can't attack if player has levitation
        if monster.attack_char == 'X':
            if status_flag_1 or check_inventory_has_item(ITEM_LEVITATION):
                return  # Can't reach floating player

        # Special: flying monsters can't attack if player is on certain tiles
        if monster.attack_char in FLYING_MONSTERS_MASK:
            pass

        # Execute attack
        monster_attack_player(monster)

        # Update monster appearance if confused
        if confusion_lock:
            monster.visible_char = random_monster_char()
            monster.template_index = random_template_index()
            map_overlay[monster.y_position * MAP_WIDTH + monster.x_position] = monster.visible_char

        return  # Don't move, just attack

    # Special: 'X' can't move onto stairs on level 0
    if monster.attack_char == 'X':
        target_tile = map_overlay[new_y * MAP_WIDTH + new_x]
        if target_tile in [0xF7, 0x7E]:  # Stairs (up/down)
            return  # Blocked

    # Save relative cursor position
    saved_cursor_y = get_relative_cursor_y()
    saved_cursor_x = get_relative_cursor_x()

    # If monster is visible and not invisible
    if monster.is_visible and not monster.is_invisible:
        # Erase old position on screen
        if is_teleporting:
            validate_window_coords(monster.y_position + 1, monster.x_position)
        else:
            validate_window_coords(
                (0xD - player_y) + monster.y_position,
                (monster.x_position + 0x27) - player_x
            )

        # Check if tile is visible to player
        if is_tile_explored(monster.y_position, monster.x_position):
            # Restore underlying tile character
            underlying_char = dungeon_map[monster.y_position * MAP_WIDTH + monster.x_position]
            print_char(underlying_char)
        else:
            print_space()

    # Clear old position on map overlay
    map_overlay[monster.y_position * MAP_WIDTH + monster.x_position] = ' '

    # Update position
    monster.y_position = new_y
    monster.x_position = new_x

    # Update appearance if confused
    if confusion_lock:
        monster.visible_char = random_monster_char()
        monster.template_index = random_template_index()

    # Draw monster at new position
    map_overlay[monster.y_position * MAP_WIDTH + monster.x_position] = monster.visible_char

    # Render on screen if visible
    if teleport_effect_flag and not is_teleporting and not monster.is_invisible:
        put_char_at_pos(
            map_overlay[monster.y_position * MAP_WIDTH + monster.x_position],
            monster.x_position,
            monster.y_position
        )

    monster.is_visible = teleport_effect_flag

    # Check for item pickup on new tile
    if monster.carried_item_lo == 0 and monster.carried_item_hi == 0:
        # Monster isn't carrying anything
        item_at_pos = map_overlay[monster.y_position * MAP_WIDTH + monster.x_position]

        # Check if monster type picks up items
        if monster.attack_char in [0x56, 0x46, 0x4F, 0x67, 0x55, 0x54, 0x4E, 0x44, 0x01, 0x42]:
            # 'V', 'F', 'O', 'g', 'U', 'T', 'N', 'D', Sauron, 'B'
            # These monsters can pick up items

            # Pick up item from ground
            item = find_item_at_coords(monster.y_position, monster.x_position)
            if item:
                monster.carried_item_lo = item & 0xFFFF
                monster.carried_item_hi = (item >> 16) & 0xFFFF
                map_overlay[monster.y_position * MAP_WIDTH + monster.x_position] = ' '
                remove_item_from_list(dungeon_level, item)

    # Restore cursor position
    validate_window_coords(saved_cursor_x, saved_cursor_y)
```

---

## 7. Special Monster Behaviors

### Eye of Sauron (0x45 = 'E')

```python
# Never becomes hostile (unless attacked)
# Always has is_awake = 1, status_timer = -1 (0xFFFF = permanent)
# Never moves
# Speed = 0, Attacks = 0

if monster.attack_char == 'E':
    # Spawned with permanent awareness
    monster.is_awake = 1
    monster.status_timer = 0xFFFF

    # Never chases player (skips movement)
    if not monster.is_hostile:
        # Skip movement entirely
        pass
```

### Huorn (0x48 = 'H')

```python
# Only becomes hostile when adjacent to player
# Otherwise sleeps/waits

if monster.attack_char == 'H':
    if are_coordinates_adjacent(player_x, player_y, monster.x_position, monster.y_position):
        # Player is next to Huorn — wake up and attack
        if check_some_condition(monster):
            monster.is_fleeing = 1
            monster.is_hostile = 0
    else:
        # Player is far — don't move
        pass
```

### The Watcher (0x58 = 'X')

```python
# Can't move onto stairs on level 0
# Can't attack player with levitation

if monster.attack_char == 'X':
    if new_y == player_y and new_x == player_x:
        # Check if player is floating
        if status_flag_1 or check_inventory_has_item(ITEM_LEVITATION):
            return  # Can't reach

    # Check for stairs
    if dungeon_level == 0:
        target_tile = map_overlay[new_y * MAP_WIDTH + new_x]
        if target_tile in [0xF7, 0x7E]:  # Stairs
            # On level 0, standing on stairs makes The Watcher passive
            monster.is_hostile = 0
```

### Bat (0x43 = 'C') and Air (0x61 = 'a')

```python
# Wander randomly when not alerted

if monster.attack_char in [0x43, 0x61]:  # 'C', 'a'
    if not monster.is_alerted:
        # 50% chance to move randomly instead of toward player
        if random_mod(2) == 0:
            sign_dy = random_mod(3) - 1  # -1, 0, or 1
            sign_dx = random_mod(3) - 1
```

### Ghost Type 2 (0xEA)

```python
# Regenerates HP to 500
# 1/65 chance per turn to reveal on map

if monster.attack_char == 0xEA:
    if monster.hit_points < 500:
        monster.hit_points += 1

    if random_mod(0x41) == 0:  # 1/65
        # Reveal monster position on dungeon map
        dungeon_map[monster.y_position * MAP_WIDTH + monster.x_position] = 0x03
```

### Sauron (0x01)

```python
# Regenerates HP to 150
# Spawned disguised as random monster

if monster.attack_char == 0x01:
    if monster.hit_points < 150:
        monster.hit_points += 1

    # Initially spawned with different visible_char
    # Reveals true form when hit (see COMBAT_SYSTEM.md)
```

### Saruman (0xE4 = 'ä')

```python
# Regenerates HP to 100
# 1/70 chance per turn to reveal on map

if monster.attack_char == 0xE4:
    if monster.hit_points < 100:
        monster.hit_points += 1

    if random_mod(0x46) == 0:  # 1/70
        # Reveal monster position on dungeon map
        dungeon_map[monster.y_position * MAP_WIDTH + monster.x_position] = 0x03
```

---

## 8. Fleeing Behavior

When `monster.is_fleeing = 1`, the monster moves **away** from the player instead of toward.

```python
def process_monster_movement(monster):
    dy = player_y - monster.y_position
    dx = player_x - monster.x_position
    sign_dy = get_sign(dy)
    sign_dx = get_sign(dx)

    if monster.is_fleeing:
        # Flee: negate direction
        move_entity_on_map(monster, -sign_dx, -sign_dy)
    else:
        # Chase: move toward player
        move_entity_on_map(monster, sign_dx, sign_dy)
```

### Fleeing Triggers

Fleeing is set by:
1. **Fear attack** (Eye of Sauron special attack): sets `is_fleeing = 1`, countdown timer
2. **Huorn adjacency check**: when triggered, sets fleeing
3. **Theft monsters** (Thief 'V', Fairy 'F'): after stealing, call `cleanup_after_monster_death` which makes them flee

### Fleeing Duration

Controlled by `status_timer` (offset 0x20):

```python
# Each turn, decrement timer
if monster.status_timer > 0:
    monster.status_timer -= 1
    if monster.status_timer == 0:
        # Timer expired — stop fleeing
        monster.is_fleeing = 0
        monster.is_alerted = 0
        monster.is_awake = 0
```

---

## 9. Door & Wall Interaction

Monsters can break through doors and walls under certain conditions.

### Door Breaking (Special Ability Check)

```python
def validate_tile_movement(monster, dx, dy):
    # ...

    # Check if monster can break doors/obstacles
    if random_mod(monster.special_ability_1 + 1) == 6:
        # 1/(special_ability_1 + 1) chance to break through
        # Example: Air elemental has special_ability_1 = 13
        #          → 1/14 chance per turn to break doors
        if in_bounds(target_y, target_x):
            return True  # Allow movement through door
```

**Monsters with high `special_ability_1`**:
- Air (13): 1/14 chance to break doors
- Saruman (25): 1/26 chance to break doors
- Most monsters (0): 1/1 = 100% break doors (!)

**Wait, this seems backwards.** Let me re-check the code...

Actually, looking at line 10967:
```c
iVar3 = random_mod(*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1a) + 1), iVar3 == 6
```

This is checking `random_mod(special_ability_1 + 1) == 6`. So:
- special_ability_1 = 0 → random_mod(1) always returns 0, never 6 → **can't break doors**
- special_ability_1 = 13 → random_mod(14) in [0..13], 1/14 chance of 6 → **can break doors**
- special_ability_1 = 25 → random_mod(26) in [0..25], 1/26 chance of 6 → **can break doors**

**Correction**: Monsters with `special_ability_1 > 5` can break doors. Most monsters have 0, so they can't.

### Wall Breaking (Level Check)

```python
def validate_tile_movement(monster, dx, dy):
    # ...

    # High-level monsters can break walls
    if random_mod(monster.level + 1) == 9:
        # 1/(level + 1) chance to break walls
        # Example: Morgoth (level 30) → 1/31 chance per turn
        #          Spider (level 12) → 1/13 chance per turn

        if in_bounds(target_y, target_x):
            # Clear the wall
            map_overlay[target_y * MAP_WIDTH + target_x] = 0x20
            return True
```

**Wall breaking chances**:
- Spider (level 12): 1/13 (~7.7%)
- Balrog (level 18): 1/19 (~5.3%)
- Morgoth (level 30): 1/31 (~3.2%)

---

## 10. Visibility & Awareness

### Light Source Requirement

```python
def update_all_monsters():
    has_light = check_inventory_has_item(ITEM_LIGHT_SOURCE)

    if not has_light and not status_flag_5:
        # No light — can't see most monsters

        if is_wizard:
            # Wizard mode sees all
            goto process_all_monsters

        # Only process hostile, non-stationary monsters
        if not monster.is_hostile:
            goto skip_monster

        # Stationary monsters are always "felt"
        if monster.is_stationary:
            goto process_monster

        # Special monsters visible in dark
        if monster.attack_char in [0x4E, 0x45]:  # Nazgûl, Eye
            goto skip_monster  # Can't see them

        if monster.attack_char in [0x46, 0x61]:  # Fairy, Air
            goto process_monster  # Can see them

        if monster.attack_char in [0x42, 0x44, 0x92]:  # Balrog, Dragon
            goto process_monster  # Can see them
```

### Monster Awareness (Awake vs Asleep)

```python
# Monster starts asleep (is_awake = 0, is_alerted = 0)
# Becomes awake when:
#  - Player attacks it
#  - Player gets close (proximity check, not shown in these functions)
#  - Special: Eye of Sauron always awake (is_awake = 1, status_timer = -1)

if not monster.is_awake and not monster.is_alerted:
    # Monster is asleep — skip turn
    monster.move_toggle = 0
    continue
```

---

## 11. Helper Functions

### get_sign (line 48)

Returns the sign of a value: -1, 0, or +1.

```python
def get_sign(value):
    if value == 0:
        return 0
    elif value < 0:
        return -1
    else:
        return 1
```

### is_position_in_bounds (line 707)

Checks if coordinates are within the dungeon map.

```python
def is_position_in_bounds(y, x):
    # Valid ranges: y in [1, 22], x in [1, 79]
    if y < 1 or y > 0x16:  # 0x16 = 22
        return False
    if x < 1 or x > 0x4f:  # 0x4f = 79
        return False
    return True
```

### is_tile_passable (line 11713)

Checks if a tile can be moved through.

```python
def is_tile_passable(y, x):
    tile_char = dungeon_map[y * MAP_WIDTH + x]

    # Check against bitmask of passable tiles (0xb76f)
    if is_in_bitmask(tile_char, PASSABLE_TILES_MASK):
        if map_overlay[y * MAP_WIDTH + x] == ' ':
            return True

    # Special: status_flag_3 allows passage through certain tiles
    if status_flag_3:
        # Check against alternate bitmask (0xb7af)
        if is_in_bitmask(tile_char, ALTERNATE_PASSABLE_MASK):
            return True

    # Final check: is overlay empty?
    if map_overlay[y * MAP_WIDTH + x] != ' ':
        return True

    return False
```

---

## Answers to Key Questions

### 1. How does each monster type decide where to move?

**Normal monsters**:
- Calculate direction toward player: `sign(player_y - monster_y)`, `sign(player_x - monster_x)`
- Prioritize axis with larger distance (Manhattan distance greedy algorithm)
- Try primary direction first; if blocked, try perpendicular direction

**Wandering monsters** (Bat 'C', Air 'a'):
- 50% chance to move randomly instead of chasing (when not alerted)
- Random: `dx = random_mod(3) - 1`, `dy = random_mod(3) - 1`

**Stationary monsters** (bosses):
- Never move (`is_stationary = 1`)

**Special behaviors**:
- Eye 'E': never moves (even though `is_stationary = 0`)
- Huorn 'H': only moves when adjacent to player
- The Watcher 'X': can't move onto stairs on level 0

### 2. Chase behavior vs wandering

**Chase** (default):
- Triggered when `is_hostile = 0` (aggressive monster)
- Moves toward player using greedy pathfinding (largest distance first)
- Attacks when reaching player position

**Wander**:
- Bat 'C' and Air 'a': 50% chance to move randomly when not alerted
- All other monsters: no wandering, only chase or stand still

**Alerted** state:
- `is_alerted = 1`: monster actively pursues player
- `is_alerted = 0`: monster waits (asleep) or wanders

### 3. Speed system (how often do fast/slow monsters act?)

**ALL monsters move at the same speed**: every other turn when awake/alerted.

**Turn toggle mechanism**:
- `move_toggle` field alternates 0→1→0→1 each turn
- Monster can only move when `(is_awake OR is_alerted) AND move_toggle = 1`
- Result: half-speed movement (every 2 turns)

**No "fast" monsters**: The `speed_bonus` field affects **combat to-hit rolls**, not movement frequency.

**HP regeneration** (boss monsters only):
- Ghost 2 (0xEA): +1 HP/turn up to 500
- Ghost 1 (0xE8): +1 HP/turn up to 350
- Sauron (0x01): +1 HP/turn up to 150
- Saruman (0xE4): +1 HP/turn up to 100

### 4. Special behaviors (Eye doesn't move, Huorn only when disturbed)

**Eye of Sauron** (0x45 = 'E'):
- Always awake (`is_awake = 1`, `status_timer = -1`)
- Never moves (skips movement logic)
- Never hostile unless attacked
- Attacks = 0, Speed = 0

**Huorn** (0x48 = 'H'):
- Only becomes hostile when player is adjacent
- Triggers fleeing behavior on adjacency check
- Otherwise sleeps/waits

**The Watcher** (0x58 = 'X'):
- Can't attack player with levitation
- Can't move onto stairs on level 0
- Standing on stairs makes it passive

**Bat/Air** (0x43/'C', 0x61/'a'):
- Wander randomly 50% of the time when not alerted

**Ghosts/Sauron/Saruman**:
- Regenerate HP over time
- Occasionally reveal on map (1/65 or 1/70 chance per turn)

### 5. Door/wall interaction

**Door breaking**:
- Requires `special_ability_1 > 5`
- Chance: `1 / (special_ability_1 + 1)` per turn to break through
- Example: Air (special_ability_1=13) → 1/14 chance
- Most monsters (special_ability_1=0) **cannot break doors**

**Wall breaking**:
- Requires `level > 8`
- Chance: `1 / (level + 1)` per turn to break walls
- Example: Morgoth (level 30) → 1/31 = 3.2% chance
- Clears the wall tile permanently (sets to 0x20 = empty space)

### 6. Fleeing behavior

**Triggered by**:
- Fear attack from Eye of Sauron
- Huorn adjacency check
- Theft (Thief 'V', Fairy 'F' flee after stealing)

**Mechanism**:
- Sets `is_fleeing = 1`
- Negates movement direction: `move_entity_on_map(monster, -sign_dx, -sign_dy)`
- Monster moves away from player instead of toward

**Duration**:
- Controlled by `status_timer` countdown
- Decrements each turn; when reaches 0, fleeing stops
- Eye fear attack: 15-19 turns (normal) or 100-149 turns (death sentence)

---

## Monster AI Summary Table

| Monster | Stationary | Hostile | Speed | Special Behavior |
|---------|------------|---------|-------|------------------|
| Spider, Bat, Rat, Snake, Wolf | No | No | Half | Bat wanders randomly |
| Goblin, Orc, Uruk-hai, Variag | No | No | Half | Normal chase |
| Crebain, Warg, Woose | No | No | Half | Normal chase |
| Mewlip, Galgal, Troll | No | No | Half | Normal chase |
| Werewolf, Moricaud | No | No | Half | Normal chase |
| Air elemental | No | Yes (INV) | Half | Wanders randomly; can break doors (1/14) |
| Eye of Sauron | No | Yes | **Never moves** | Always awake, 0 attacks, fear effect |
| Fairy | No | No | Half | Steals items, flees after |
| Huorn | No | Yes | Half | Only moves when adjacent to player |
| Thief | No | No | Half | Steals gold, flees after |
| Succubus | No | No | Half | Drains XP |
| Dragon, Winged Dragon | No | No | Half | Normal chase, counter-attack |
| Balrog | No | No | Half | Normal chase, can break doors (never) |
| Nazgûl | No | No | Half | Normal chase |
| Oliphant | No | No | Half | Normal chase |
| **Carcharoth** | Yes | Yes | **0** | Boss, regenerates HP |
| **Glaurung** | Yes | Yes | **0** | Boss, regenerates HP |
| **Ungoliant** | Yes | Yes | **0** | Boss, regenerates HP |
| **Saruman** | Yes | Yes | **0** | Boss, regenerates HP, random chaos, can break doors (1/26) |
| **The Watcher** | Yes | Yes | **0** | Boss, can't move onto stairs (L0) |
| **Sauron** | Yes | Yes | **0** | Boss, disguised, regenerates HP |
| **Morgoth** | Yes | Yes | **0** | Boss, final boss, carries Silmaril |

**Key**: Stationary bosses never move. "Half" speed means every other turn. Hostile=Yes means always aggressive.

---

## Implementation Notes for Python Rewrite

1. **Turn system**: Implement `move_toggle` as a boolean that flips each turn
2. **Pathfinding**: Greedy Manhattan distance (no A*, no Dijkstra)
3. **Speed**: All moving monsters act every 2 turns (when toggle is set)
4. **Boss monsters**: Set `is_stationary = True` to prevent movement
5. **Special behaviors**: Implement as type checks in AI loop (by `attack_char`)
6. **Fleeing**: Negate movement direction when `is_fleeing = True`
7. **Door/wall breaking**: RNG checks based on `special_ability_1` and `level`
8. **Visibility**: Only process monsters that can be seen (light source + proximity)
9. **HP regeneration**: Boss monsters only, each turn in main loop
10. **Wandering**: Bat and Air have 50% chance to move randomly instead of chasing
