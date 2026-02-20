# PLAYER ACTIONS & LEVEL TRANSITIONS
## Reverse Engineering Analysis of DOS MORIA 1.9.8.7

**Source**: MORIA_with_constants.C (decompiled DOS binary)
**Functions Analyzed**: 12 core player movement, progression, and time-based systems

---

## TABLE OF CONTENTS

1. [Overview](#overview)
2. [Stairs & Level Transitions](#stairs--level-transitions)
3. [Level Persistence System](#level-persistence-system)
4. [Player Movement](#player-movement)
5. [Food & Hunger System](#food--hunger-system)
6. [Natural Regeneration](#natural-regeneration)
7. [Level-Up System](#level-up-system)
8. [Timed Effects System](#timed-effects-system)
9. [Main Game Loop](#main-game-loop)
10. [Function Reference](#function-reference)

---

## OVERVIEW

This document covers the core player action systems in DOS MORIA:
- **Stairs**: Transitioning between dungeon levels (up/down)
- **Level Persistence**: Whether levels are regenerated or saved
- **Movement**: Walking, running, traps, and terrain interaction
- **Food/Hunger**: Hunger states and timing
- **Regeneration**: Natural HP recovery system
- **Leveling**: XP thresholds and stat gains on level-up
- **Timed Effects**: How temporary status effects decay

All findings are based on direct analysis of the decompiled C source code.

---

## STAIRS & LEVEL TRANSITIONS

### Going Down Stairs

**Function**: `advance_to_next_level` (line 11670)
**Direction**: 0 = down, 1 = up

When the player descends stairs:

```c
void advance_to_next_level(int direction) {
    int current_tile;

    if (direction == 0) {  // Going DOWN
        // Store current tile type at player position
        current_tile = get_tile_at(player.row, player.col);
        set_tile_at(player.row, player.col, current_tile);

        // Increment dungeon level
        dungeon_level++;

        // HP DAMAGE unless protected
        if (!has_item_in_inventory(ITEM_UNKNOWN_E)) {
            damage_amount = random(dungeon_level * 2);
            current_hp -= damage_amount;

            if (current_hp < 1) {
                display_message(176);  // Death message
                player_is_dead = 1;
                return;
            }

            display_message(177);  // "Vous vous blessez en descendant" (You hurt yourself going down)
        }

        // Check if level was previously visited
        if (dungeon_map[dungeon_level][0x71a] == 0) {
            // NEW LEVEL - Generate it
            draw_dungeon_border();
            generate_dungeon_level();
            spawn_monsters();
            dungeon_map[dungeon_level][0x71a] = 1;  // Mark as visited
        }

        // Place player at up-stairs position on new level
        place_player_on_level();
    }
}
```

**Key Points**:
- Going down **damages HP** by `random(dungeon_level * 2)`
- ITEM_UNKNOWN_E (likely "Feather Fall" or "Soft Boots") **prevents damage**
- Death is possible if HP drops below 1
- Level persistence checked via offset `+0x71a`

### Going Up Stairs

```c
void advance_to_next_level(int direction) {
    if (direction == 1) {  // Going UP
        // Cannot go up from level 0 (town)
        if (dungeon_level == 0) {
            display_message(178);  // "Vous ne pouvez pas monter" (You cannot go up)
            return;
        }

        // Decrement dungeon level
        dungeon_level--;

        // Retrieve stored up-stairs coordinates
        player.row = stored_upstairs_row[dungeon_level];
        player.col = stored_upstairs_col[dungeon_level];

        // NO HP DAMAGE when going up
        // Level already exists (was previously visited)
    }
}
```

**Key Points**:
- Going up is **safe** (no HP damage)
- Cannot ascend from level 0 (town level)
- Returns to exact position where you entered stairs
- All levels above are already generated (you came from there)

### Player Placement After Transition

**Function**: `place_player_on_level` (line 3814)

```c
void place_player_on_level() {
    int attempts = 0;
    int random_row, random_col;

    // Find stairs tile (0x3C for down-stairs, 0x3E for up-stairs)
    for (row = 1; row <= 19; row++) {
        for (col = 1; col <= 78; col++) {
            if (get_tile_at(row, col) == 0x3C) {  // Down-stairs
                player.row = row;
                player.col = col;
                return;
            }
        }
    }

    // If no stairs found, place randomly on floor tile
    while (attempts < 100) {
        random_row = 1 + random(19);
        random_col = 1 + random(78);

        if (get_tile_at(random_row, random_col) == 0x2E) {  // Floor tile '.'
            player.row = random_row;
            player.col = random_col;
            return;
        }
        attempts++;
    }
}
```

---

## LEVEL PERSISTENCE SYSTEM

### How Levels Are Stored

DOS MORIA uses a **per-level flag** at offset `+0x71a` to track visited levels:

```c
// Memory structure per level
dungeon_map[level][0x000 ... 0x719]  // Tile data (20 rows × 79 cols × 2 bytes)
dungeon_map[level][0x71a]            // Visited flag (0 = not visited, 1 = visited)
```

### Level Generation Logic

**Function**: `initialize_new_level` (line 12004)

```c
void initialize_new_level() {
    if (dungeon_map[dungeon_level][0x71a] == 0) {
        // FIRST VISIT - Generate fresh level
        draw_dungeon_border();           // Draw outer walls
        generate_dungeon_level();        // Create rooms + corridors
        spawn_monsters();                // Populate with monsters
        place_objects();                 // Place items
        dungeon_map[dungeon_level][0x71a] = 1;  // Mark as visited
    } else {
        // RETURNING TO VISITED LEVEL
        // Level data already exists in memory
        // Monsters/items persist in their last state
        redraw_entire_screen();
    }
}
```

### What Persists vs. What Regenerates

| Element | Persistence Behavior |
|---------|---------------------|
| **Dungeon Layout** | Persists - rooms/corridors unchanged |
| **Monsters** | Persist - same monsters, same positions |
| **Items** | Persist - dropped items remain |
| **Tile Changes** | Persist - doors opened, traps triggered |
| **Monster Spawning** | Continues - new monsters spawn every 20 turns |

**Important**: Levels are **NOT saved to disk**. They exist only in RAM during the current game session. Quitting the game loses all level data.

---

## PLAYER MOVEMENT

### Main Movement Function

**Function**: `move_player_in_direction` (line 11761)

```c
void move_player_in_direction(int direction) {
    int target_row, target_col, target_tile;

    // Calculate target position (4 directions only: 2,4,6,8)
    switch (direction) {
        case 2: target_row = player.row + 1; target_col = player.col; break;     // Down
        case 4: target_row = player.row; target_col = player.col - 1; break;     // Left
        case 6: target_row = player.row; target_col = player.col + 1; break;     // Right
        case 8: target_row = player.row - 1; target_col = player.col; break;     // Up
    }

    target_tile = get_tile_at(target_row, target_col);

    // SPEED BOOST EFFECT - Random movement
    if (speed_boost_active) {
        direction = random(4) * 2 + 2;  // Random direction: 2,4,6,8
        // Recalculate target with random direction
    }

    // WALL CHECK
    if (is_wall_tile(target_tile)) {
        display_message(179);  // "Vous vous cognez contre un mur" (You bump into a wall)
        return;
    }

    // MONSTER CHECK
    monster = get_monster_at(target_row, target_col);
    if (monster != NULL) {
        attack_monster(monster);  // Combat instead of movement
        return;
    }

    // MOVE PLAYER
    player.row = target_row;
    player.col = target_col;

    // TILE-SPECIFIC EFFECTS
    switch (target_tile) {
        case 0x3C:  // Down-stairs
            if (user_confirms_stairs()) {
                advance_to_next_level(0);  // Go down
            }
            break;

        case 0x3E:  // Up-stairs
            if (user_confirms_stairs()) {
                advance_to_next_level(1);  // Go up
            }
            break;

        case 0xF7:  // TRAP TILE
            display_message(180);  // "Un piège!" (A trap!)
            remove_magic_item();   // Random item degraded/destroyed
            food_level = 3000;     // Set to "Faible" (Weak) hunger state
            break;

        case 0xB0:  // Door (closed)
            set_tile_at(target_row, target_col, 0x2D);  // Open door (change to '-')
            break;
    }

    // ITEM PICKUP
    item = get_item_at(target_row, target_col);
    if (item != NULL) {
        display_item_description(item);
        prompt_pickup_item(item);
    }
}
```

### Movement Rules

1. **4 Directions Only**: No diagonal movement (2,4,6,8 on numpad)
2. **Walls Block**: Cannot move into wall tiles
3. **Monsters Block**: Moving into monster initiates combat
4. **Speed Boost**: Randomizes direction when active
5. **Traps**: Damage items AND set hunger to "Faible"

---

## FOOD & HUNGER SYSTEM

### Hunger States

**Function**: `display_food_status` (line 1940)

```c
void display_food_status() {
    char* hunger_message;

    if (food_level > 5000) {
        hunger_message = "Rassasié";     // Full (5000+)
    } else if (food_level > 3000) {
        hunger_message = "Normal";       // Normal (3001-5000)
    } else if (food_level > 1500) {
        hunger_message = "Faible";       // Weak (1501-3000)
    } else if (food_level > 0) {
        hunger_message = "Affamé";       // Hungry (1-1500)
    } else {
        hunger_message = "Mourant";      // Dying (0 or below)
    }

    display_at_position(24, 40, hunger_message);
}
```

### Hunger Thresholds

| Range | Status | French |
|-------|--------|--------|
| 5001+ | Full | Rassasié |
| 3001-5000 | Normal | Normal |
| 1501-3000 | Weak | Faible |
| 1-1500 | Hungry | Affamé |
| ≤ 0 | Dying | Mourant |

### Food Consumption Rate

**From Main Game Loop** (line 12509):

```c
// Every turn
food_level--;

if (food_level < 1) {
    // STARVATION DAMAGE
    damage_amount = random(10) + 1;
    current_hp -= damage_amount;

    if (current_hp < 1) {
        display_message(181);  // "Vous mourez de faim" (You die of starvation)
        player_is_dead = 1;
    }
}
```

**Key Facts**:
- Food decreases by **1 per turn**
- At food ≤ 0, take **random(10) + 1 damage per turn**
- Death occurs when HP ≤ 0

### Food Sources

1. **Eating Food Items**: Adds 2000-5000 to food_level
2. **Drinking Potions**: ALL potions add `200 + random(100)` food
3. **Traps**: Set food to exactly 3000 (Weak state)

---

## NATURAL REGENERATION

### HP Regeneration Rules

**Function**: `rest_and_regenerate` (line 12445)
**Also**: Main game loop (line 12509)

```c
// In main game loop - EVERY TURN
if (current_hp < max_hp) {
    regen_counter++;

    regen_delay = (15 - dungeon_level) / 2;

    if (regen_delay < 1) {
        regen_delay = 1;  // Minimum delay of 1 turn
    }

    if (regen_counter >= regen_delay) {
        current_hp++;
        regen_counter = 0;
    }
}
```

### Regeneration Speed by Level

| Dungeon Level | Delay Formula | Turns per +1 HP |
|---------------|---------------|-----------------|
| 1 | (15-1)/2 = 7 | 7 turns |
| 2 | (15-2)/2 = 6 | 6 turns |
| 5 | (15-5)/2 = 5 | 5 turns |
| 10 | (15-10)/2 = 2 | 2 turns |
| 13+ | (15-13)/2 = 1 | 1 turn (minimum) |

**Key Points**:
- Regeneration **speeds up** on deeper levels
- Minimum delay is **1 turn** (levels 13+)
- Regeneration only occurs when **current_hp < max_hp**
- Resting (doing nothing) still triggers regeneration

### Rest Command

**Function**: `rest_and_regenerate` (line 12445)

```c
void rest_and_regenerate() {
    display_message(182);  // "Vous vous reposez..." (You rest...)

    // Rest until HP full OR interrupted
    while (current_hp < max_hp) {
        // Wait for regen delay
        for (int i = 0; i < regen_delay; i++) {
            process_monster_turns();  // Monsters still move!
            food_level--;

            if (monster_nearby() || current_hp >= max_hp) {
                return;  // Interrupt rest
            }
        }

        current_hp++;
    }

    display_message(183);  // "Vous êtes reposé" (You are rested)
}
```

**Rest Interruptions**:
- Monster comes into view
- HP reaches maximum
- Food reaches 0 (starvation damage)

---

## LEVEL-UP SYSTEM

### Experience Thresholds

**From COMBAT_SYSTEM.md**:

| Level | XP Required | XP Difference |
|-------|-------------|---------------|
| 1 | 0 | - |
| 2 | 50 | 50 |
| 3 | 150 | 100 |
| 4 | 350 | 200 |
| 5 | 750 | 400 |
| 6 | 1550 | 800 |
| 7 | 3150 | 1600 |
| 8 | 6350 | 3200 |
| 9 | 12750 | 6400 |
| 10 | 25550 | 12800 |

Formula: `XP[n] = 50 × (2^(n-1) - 1)` for n ≥ 1

### Level-Up Stat Gains

**Function**: `level_up_character` (line 5974)

```c
void level_up_character() {
    int hp_gain_max, hp_gain_current;

    // Increment player level
    player_level++;

    // MAX HP INCREASE
    hp_gain_max = random(6) + random(player_level) + 3 + random(dungeon_level) / 2;
    max_hp += hp_gain_max;

    // CURRENT HP INCREASE
    hp_gain_current = 1 + random(player_level + 6 + dungeon_level);
    current_hp += hp_gain_current;

    // Display level-up message
    display_message(184);  // "Bienvenue au niveau X" (Welcome to level X)
    sprintf(message_buffer, "Vous gagnez %d PV", hp_gain_max);
    display_message_buffer();
}
```

### Level-Up HP Gain Formulas

**Maximum HP Gain**:
```
max_hp += random(6) + random(player_level) + 3 + random(dungeon_level) / 2
```

**Current HP Gain**:
```
current_hp += 1 + random(player_level + 6 + dungeon_level)
```

### Example Level-Up Gains

**Level 5 → 6 on Dungeon Level 10**:
- Max HP gain: `random(6) + random(6) + 3 + random(10)/2` = **5-14 HP**
- Current HP gain: `1 + random(22)` = **1-22 HP**

**Level 10 → 11 on Dungeon Level 20**:
- Max HP gain: `random(6) + random(11) + 3 + random(20)/2` = **4-29 HP**
- Current HP gain: `1 + random(36)` = **1-36 HP**

### Losing Levels (Experience Drain)

**Function**: `lose_experience_level` (line 6012)

```c
void lose_experience_level() {
    int hp_loss;

    if (player_level > 1) {
        player_level--;

        // MAX HP DECREASE
        hp_loss = 3 + random(player_level + 6);
        max_hp -= hp_loss;

        if (max_hp < 1) {
            max_hp = 1;  // Minimum 1 HP
        }

        // Adjust current HP if over new maximum
        if (current_hp > max_hp) {
            current_hp = max_hp;
        }

        display_message(185);  // "Vous perdez un niveau" (You lose a level)
    }
}
```

**Level Loss Formula**:
```
max_hp -= 3 + random(player_level + 6)
```

**Note**: Level loss HP penalty is **smaller** than level gain HP bonus (encourages leveling).

---

## TIMED EFFECTS SYSTEM

### Effect Indices

**From Main Game Loop** (line 12524-12533):

```c
// 13 timed effects (indices 0-12)
int effect_active[13];   // Boolean: is effect currently active?
int effect_timer[13];    // Turns remaining
```

### Effect Tick-Down Mechanism

```c
// EVERY TURN in main game loop
for (effect_index = 0; effect_index <= 12; effect_index++) {
    if (effect_active[effect_index]) {
        effect_timer[effect_index]--;

        if (effect_timer[effect_index] < 1) {
            // Effect expired
            effect_active[effect_index] = 0;
            handle_timed_effect(effect_index);
        }
    }
}
```

### Effect Expiration Handler

**Function**: `handle_timed_effect` (line 12026)

```c
void handle_timed_effect(int effect_index) {
    switch (effect_index) {
        case 0:  // BLINDNESS
            display_message(186);  // "Vous voyez à nouveau" (You can see again)
            redraw_entire_screen();
            break;

        case 1:  // CONFUSION
            display_message(187);  // "Vous n'êtes plus confus" (You are no longer confused)
            break;

        case 2:  // FEAR
            display_message(188);  // "Vous n'avez plus peur" (You are no longer afraid)
            break;

        case 3:  // PARALYSIS
            display_message(189);  // "Vous pouvez bouger à nouveau" (You can move again)
            break;

        case 4:  // POISON
            display_message(190);  // "Le poison s'estompe" (The poison fades)
            // NO MORE HP DAMAGE
            break;

        case 5:  // SPEED BOOST
            display_message(191);  // "Vous ralentissez" (You slow down)
            break;

        case 6:  // SLOW
            display_message(192);  // "Vous accélérez" (You speed up)
            break;

        case 7:  // PROTECTION
            display_message(193);  // "Votre protection disparaît" (Your protection fades)
            armor_class -= 20;  // Remove AC bonus
            break;

        case 8:  // DETECT MONSTERS
            display_message(194);  // "Vous perdez la détection" (You lose detection)
            redraw_entire_screen();
            break;

        case 9:  // DETECT OBJECTS
            display_message(195);  // "Vous perdez la détection" (You lose detection)
            redraw_entire_screen();
            break;

        case 10: // INVISIBILITY
            display_message(196);  // "Vous redevenez visible" (You become visible again)
            break;

        case 11: // INFRAVISION
            display_message(197);  // "L'infravision s'estompe" (Infravision fades)
            break;

        case 12: // WIZARD MODE (from Potion 22 - Gasification)
            is_wizard = 0;
            player.char = 0x02;  // Change from '~' back to '☻'
            display_message(198);  // "Vous redevenez normal" (You return to normal)
            break;
    }
}
```

### Effect Duration Sources

Most effects are set by potions, wands, or scrolls (see MAGIC_SYSTEM.md):

| Effect | Source | Duration Formula |
|--------|--------|------------------|
| Blindness | Potion 8 | 100 + random(100) turns |
| Confusion | Potion 10 | 25 + random(15) turns |
| Paralysis | Scroll 18 | 15 + random(10) turns |
| Poison | Potion 17 | 100 + random(50) turns |
| Speed | Potion 15 | 50 + random(25) turns |
| Protection | Potion 14 | 100 + random(50) turns |
| Invisibility | Potion 19 | 50 + random(30) turns |
| Wizard Mode | Potion 22 | 25 + random(15) turns |

### Poison Damage Per Turn

**From Main Game Loop**:

```c
if (effect_active[4]) {  // Poison effect index
    // POISON DAMAGE EVERY TURN
    damage_amount = random(5) + 1;
    current_hp -= damage_amount;

    if (current_hp < 1) {
        display_message(199);  // "Vous mourez empoisonné" (You die poisoned)
        player_is_dead = 1;
    }
}
```

**Poison damage**: `random(5) + 1` per turn (1-5 HP/turn)

---

## MAIN GAME LOOP

### Turn-Based Processing

**Function**: Main game loop continuation (line 12509)

```c
void main_game_loop() {
    while (!player_is_dead && !quit_game) {
        // 1. PLAYER INPUT
        key = get_keypress();
        process_player_action(key);

        // 2. FOOD CONSUMPTION
        food_level--;
        if (food_level < 1) {
            current_hp -= random(10) + 1;  // Starvation damage
        }

        // 3. POISON DAMAGE
        if (effect_active[4]) {  // Poison
            current_hp -= random(5) + 1;
        }

        // 4. TIMED EFFECTS TICK-DOWN
        for (effect_index = 0; effect_index <= 12; effect_index++) {
            if (effect_active[effect_index]) {
                effect_timer[effect_index]--;
                if (effect_timer[effect_index] < 1) {
                    effect_active[effect_index] = 0;
                    handle_timed_effect(effect_index);
                }
            }
        }

        // 5. NATURAL HP REGENERATION
        if (current_hp < max_hp) {
            regen_counter++;
            regen_delay = (15 - dungeon_level) / 2;
            if (regen_delay < 1) regen_delay = 1;

            if (regen_counter >= regen_delay) {
                current_hp++;
                regen_counter = 0;
            }
        }

        // 6. MONSTER TURNS
        update_all_monsters();

        // 7. MONSTER SPAWNING (every 20 turns)
        turn_count++;
        if (turn_count % 20 == 0) {
            populate_level_with_monsters();

            // 4x SPAWN RATE if cursed item equipped
            if (has_cursed_item_equipped()) {
                populate_level_with_monsters();
                populate_level_with_monsters();
                populate_level_with_monsters();
            }
        }

        // 8. UPDATE DISPLAY
        display_status_bar();
        display_food_status();
        refresh_screen();
    }
}
```

### Turn Order Summary

1. **Player Action** - Movement, attack, item use, etc.
2. **Food Consumption** - Lose 1 food per turn
3. **Poison Damage** - Take 1-5 damage if poisoned
4. **Timed Effects** - Decrement all active effect timers
5. **Regeneration** - Gain HP if below max (level-dependent)
6. **Monster Turns** - All monsters move/attack
7. **Monster Spawning** - New monsters every 20 turns (4× if cursed)
8. **Display Update** - Redraw screen

---

## FUNCTION REFERENCE

### Function List (12 Functions Analyzed)

| Function | Line | Purpose |
|----------|------|---------|
| `display_food_status` | 1940 | Show hunger state in status bar |
| `place_player_on_level` | 3814 | Position player after level transition |
| `level_up_character` | 5974 | Grant HP on level-up |
| `lose_experience_level` | 6012 | Handle level drain attacks |
| `remove_magic_item` | 6032 | Trap effect - degrade/destroy item |
| `teleport_player` | 6102 | Random teleportation |
| `advance_to_next_level` | 11670 | Stairs up/down mechanics |
| `move_player_in_direction` | 11761 | Process movement (240 lines) |
| `initialize_new_level` | 12004 | Check persistence, generate if new |
| `handle_timed_effect` | 12026 | Effect expiration messages |
| `rest_and_regenerate` | 12445 | Rest command - wait until healed |
| Main game loop | 12509 | Per-turn processing |

---

## KEY FINDINGS SUMMARY

### 1. What Happens When Going Up/Down Stairs?

**Going Down**:
- Damages HP by `random(dungeon_level × 2)` unless protected by ITEM_UNKNOWN_E
- Can cause death if HP < 1
- Increments dungeon level
- Checks if new level needs generation (offset +0x71a flag)
- Places player at up-stairs position

**Going Up**:
- No HP damage (safe)
- Cannot ascend from level 0
- Decrements dungeon level
- Returns to exact position where you entered stairs
- Level already exists (was previously visited)

### 2. Level Persistence (Are Levels Saved or Regenerated?)

**Persistence Model**: Levels persist in **RAM only** during current session.

- Each level has a "visited" flag at offset `+0x71a`
- First visit: flag = 0 → generate new level, set flag = 1
- Subsequent visits: flag = 1 → use existing level data
- **Everything persists**: dungeon layout, monsters, items, tile states
- Quitting game loses all level data (no disk save)

### 3. The Food/Hunger System with Exact Timings

**Hunger States**:
- **Rassasié** (Full): 5001+ food
- **Normal**: 3001-5000 food
- **Faible** (Weak): 1501-3000 food
- **Affamé** (Hungry): 1-1500 food
- **Mourant** (Dying): ≤ 0 food

**Consumption**:
- Lose **1 food per turn**
- At 0 food: take **random(10) + 1 damage per turn**

**Food Sources**:
- Eating food item: +2000-5000
- Any potion: +200-300
- Traps: set to exactly 3000

### 4. Natural Regeneration Rules

**Formula**: Regenerate +1 HP every `(15 - dungeon_level) / 2` turns (minimum 1).

**Speed by Level**:
- Level 1: +1 HP per 7 turns
- Level 5: +1 HP per 5 turns
- Level 10: +1 HP per 2 turns
- Level 13+: +1 HP per turn

Only regenerates when `current_hp < max_hp`.

### 5. Level-Up Stat Gains

**Max HP Gain**:
```
max_hp += random(6) + random(player_level) + 3 + random(dungeon_level) / 2
```
Range: 4 to (6 + player_level + 3 + dungeon_level/2) HP

**Current HP Gain**:
```
current_hp += 1 + random(player_level + 6 + dungeon_level)
```
Range: 1 to (player_level + 6 + dungeon_level) HP

**Level Loss Penalty**:
```
max_hp -= 3 + random(player_level + 6)
```
Smaller than gain, so leveling is beneficial long-term.

### 6. How Timed Effects Tick Down

**13 Timed Effects** (indices 0-12):
- Blindness, Confusion, Fear, Paralysis, Poison, Speed, Slow, Protection, Detect Monsters, Detect Objects, Invisibility, Infravision, Wizard Mode

**Mechanism**:
- Each effect has `effect_timer[index]` (turns remaining)
- **Every turn**: decrement all active timers
- When timer ≤ 0: call `handle_timed_effect(index)` for cleanup
- Some effects have per-turn damage (Poison: 1-5 HP/turn)

**Duration**: Set by potions/wands/scrolls, typically 25-100 turns.

---

## END OF DOCUMENT

**Total Functions Analyzed**: 12
**Lines of Documentation**: ~950
**Cross-References**: COMBAT_SYSTEM.md, MAGIC_SYSTEM.md, ENTITY_DATABASE.md, MEMORY_MAP.md
