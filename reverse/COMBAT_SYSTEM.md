# MORIA DOS 1.9.8.7 — Combat System

Reverse-engineered from `MORIA_with_constants.C` functions: `execute_player_attack` (line 6706),
`monster_attack_player` (line 6368), `handle_attack_action` (line 9233), `calculate_dice_or_damage`
(line 2148), `apply_armor_damage_reduction` (line 9205), `kill_monster` (line 6130),
`cleanup_after_monster_death` (line 6346), `reveal_shapeshifter` (line 6283),
`process_monster_breeding` (line 6304), `get_sign` (line 48). Cross-referenced with
`memory.dump` (weapon tables, XP thresholds) and `moria_constants.h` (attack type values).

---

## Table of Contents

1. [Attack Type System](#1-attack-type-system)
2. [Player Attacks Monster (execute_player_attack)](#2-player-attacks-monster)
3. [Monster Attacks Player (monster_attack_player)](#3-monster-attacks-player)
4. [Ranged/Thrown Attack (handle_attack_action)](#4-rangedthrown-attack)
5. [Armor Damage Reduction](#5-armor-damage-reduction)
6. [Monster Death & XP (kill_monster)](#6-monster-death--xp)
7. [Special Combat Mechanics](#7-special-combat-mechanics)
8. [Weapon Damage Table](#8-weapon-damage-table)
9. [Experience Level Thresholds](#9-experience-level-thresholds)
10. [Helper Functions](#10-helper-functions)

---

## 1. Attack Type System

Each monster's `attack_char` (byte 0x00 of the monster object) doubles as both its display
character and its combat behavior type. The attack type determines special effects applied
after normal damage.

| Value | Char | Monster | Special Attack Effect |
|------:|------|---------|----------------------|
| 0x01 | ☺ | Sauron | Teleport escape + invisibility at low HP |
| 0x42 | `B` | Balrog | Vulnerable to weapon subtype 14 |
| 0x44 | `D` | Dragon | Vulnerable to subtype 14; counter-attacks |
| 0x45 | `E` | Eye (oEil) | Fear: death timer or flee |
| 0x46 | `F` | Fairy (Fée) | Steal item from inventory |
| 0x47 | `G` | Galgal | Acid attack type 1 (with saves) |
| 0x48 | `H` | Huorn | Confusion |
| 0x4D | `M` | Mewlip | Remove magic (strip enchantment) |
| 0x4E | `N` | Nazgûl | Acid attack type 2 (harder saves) |
| 0x56 | `V` | Voleur | Steal gold; flee after |
| 0x73 | `s` | Succubus | Drain experience (10–20 XP) |
| 0x92 | — | (variant) | Vulnerable to subtype 14; counter-attacks |
| 0x9C | — | Moricaud | Drain strength (-1) |
| 0x9E | — | (variant) | Drain intelligence (-1, fatal if reaches 0) |
| 0xE4 | — | Saruman | Random chaos effect on player |
| 0xE8 | — | Ghost 1 | Unparalyze; status timer on survive |
| 0xEA | — | Ghost 2 | Unparalyze; drop carried item if conditions met |

Monsters without special attack types (standard `attack_char` values like `a`, `A`, `C`, `L`,
`O`, `R`, `S`, etc.) deal only normal melee damage with no additional effects.

---

## 2. Player Attacks Monster

**Function**: `execute_player_attack(param_1, target_x, target_y)` (line 6706)

### Step 1: Find Target

```python
monster = find_item_at_coords(target_x, target_y)
if monster is None:
    print("Nothing there!")
    return
```

### Step 2: Compute Effective Strength

```python
base_str = strength
if base_str == 0:
    base_str = 1

# Ring1 modifiers
if equipped_ring1 and ring1.subtype == 9:    # Regeneration ring
    base_str += 2
elif equipped_ring1 and ring1.subtype == 10:  # Trap detection ring
    base_str -= 4
    if base_str < 1:
        base_str = 1
```

### Step 3: To-Hit Roll

```python
if wielded_weapon is None:
    # UNARMED
    to_hit = (player_level - monster.to_hit - monster.armor_class + 1)
             + random_mod(base_str)
else:
    # ARMED
    to_hit = (player_level + weapon.power - monster.to_hit - monster.armor_class + 1)
             + random_mod(base_str)

    # Mithril weapon bonus (subtypes 9, 13)
    if weapon.subtype in [9, 13]:
        to_hit += 3

if to_hit < 1:
    # MISS - display miss message
    return
```

### Step 4: Hit — Shapeshifter Check

```python
# On hit, make monster hostile
monster.is_hostile = 0  # Actually clears passive flag

# Reveal shapeshifter if attack_char != visible_char
if monster.attack_char == 0x01 and monster.attack_char != monster.visible_char:
    reveal_shapeshifter(monster)
```

### Step 5: Compute Damage

```python
damage = 0

# Food-based damage cap
food_cap = min(current_food, 25)
if equipped_ring1 and ring1.subtype == 11:  # Monster detect ring
    food_cap += 2

# Weapon attack bonus (ADDR_CONSTITUTION = 0xB882 = weapon_attack_bonus)
if weapon_attack_bonus >= 0:
    max_dmg = weapon_attack_bonus + 1 + (player_level * food_cap) // 10
    damage = random_mod(max_dmg) + 1

# Add thrown item bonus (arrows, etc.)
thrown_bonus = count_item_total_quantity(4)
damage += thrown_bonus
if damage < 0:
    damage = 1
```

### Step 6: Apply Special Effects by Attack Type

Based on `monster.attack_char`:

**Ghost (0xE8, 0xEA)**:
```python
is_paralyzed = 0  # Unparalyze player
if monster.attack_char == 0xEA and not monster.is_fleeing:
    if weapon.subtype in [2, 13]:  # Special weapons vs ghosts
        # Drop monster's carried item on the ground
        if monster.carried_item:
            place_carried_item_on_map(monster)
            monster.carried_item = None
    if weapon.power < 5:
        damage = 2  # Weak weapons do minimal damage to ghosts
```

**Sauron (0x01)**:
```python
if monster.hit_points < 40 and monster.carried_item:
    if monster.carried_item.type == 4 and monster.carried_item.subtype == 6:
        # Carrying Ring of Invisibility
        # Clear monster from map, teleport to random position
        monster.is_invisible = 1
        monster.is_visible = 0
        find_random_empty_floor_space(monster)
    if weapon.power < 3:
        damage = 1  # Weak weapons barely scratch Sauron
```

**Saruman (0xE4)** — random chaos effect:
```python
# 10% chance per hit to trigger (complex probability check)
if probability_check(0.1):
    FUN_1000_54d2(200)  # Sound/visual effect
    if monster.hit_points < 25:
        # Weak Saruman: teleport player 4 times
        for _ in range(4):
            teleport_player()
    else:
        # Strong Saruman: random debuff
        effect = random_mod(5)
        if effect == 0: speed_boost for 5-15 turns
        if effect == 1: haste for 5-10 turns
        if effect == 2: teleport for 10-20 turns
        if effect == 3: blind for 5-10 turns
        if effect == 4: wipe explored map + detect for 12-24 turns
    if weapon.power < 4:
        damage = 1
```

**Confuse (0x48)**: Weapon subtype 10 does extra HP damage
**Balrog (0x42), Sauron (0x01)**: Weapon subtype 14 does extra HP damage
**Drain Exp (0x73)**: Weapon power < 4 → damage reduced to 1
**Dragon (0x44), variant (0x92)**: Weapon subtype 14 does extra damage; triggers counter-attack

### Step 7: Apply Damage and Check Death

```python
monster.hit_points -= damage

# Weapon subtype 15: Life Steal (25% chance)
if weapon.subtype == 15 and random_mod(4) == 0:
    current_hp += damage // 2
    if current_hp > max_hp:
        current_hp = max_hp

if monster.hit_points <= 0:
    # Filter certain types from item count decrement
    if monster.attack_char not in [0x48, 0x45]:  # Not Huorn/Eye
        item_count[dungeon_level] -= 1
    kill_monster(monster)
else:
    # Surviving monster reactions
    if monster.attack_char in [0x48, 0x45]:  # Confuse/Fear type
        monster.is_fleeing = 1               # Start fleeing
    elif monster.attack_char in [0xE8, 0xEA]:  # Ghost type
        monster.status_timer = 1              # Brief stun
```

---

## 3. Monster Attacks Player

**Function**: `monster_attack_player(monster_x, monster_y, flags, monster_ptr)` (line 6368)

### Step 1: To-Hit Roll

```python
speed_roll = random_mod(monster.speed_bonus)
to_hit = (monster.to_hit - player_level - base_ac + 1) + speed_roll

# Stunned penalty
if player.is_stunned:
    to_hit -= 8

# Ring2 protection bonus
ring2_ac = count_item_total_quantity(7)  # Ring2 armor bonus
to_hit -= ring2_ac

# Special combat item bonus
if special_combat_flag:  # 0xB8B4 nonzero
    to_hit += 1 + random_mod(5)

if to_hit < 1:
    # MISS
    return
```

### Step 2: Shapeshifter Reveal

```python
if monster.attack_char == 0x01 and monster.attack_char != monster.visible_char:
    reveal_shapeshifter(monster)
```

### Step 3: Normal Damage

```python
if monster.damage_per_attack > 0:
    total_damage = 0
    for i in range(monster.num_attacks):
        total_damage += 1 + random_mod(monster.damage_per_attack)
    current_hp -= total_damage
```

### Step 4: Death Check — Resurrection

```python
if current_hp < 1:
    # Check belt slots for resurrection item (type 0x0F, power >= 1)
    rez_slot = None
    for slot in range(1, 5):
        item = belt[slot]
        if item and item.subtype == 0x0F and item.power >= 1:
            rez_slot = slot
            break

    if rez_slot is None:
        process_game_over(monster.template_index)  # DEATH
        return

    # RESURRECT with stat penalties
    current_hp = max_hp - 5 - random_mod(6)
    max_hp = current_hp
    max_food -= 2
    current_food -= 2
    intelligence -= 1
    belt[rez_slot].power -= 1  # Consume one charge
    return
```

### Step 5: Special Attack Effects

Applied after normal damage, based on `monster.attack_char`:

**Ghost (0xE8, 0xEA)**:
```python
is_paralyzed = 0  # Unparalyze
```

**Remove Magic (0x4D)** — Mewlip:
```python
remove_magic_item()  # Strip enchantment from a random equipped item
```

**Drain Strength (0x9C)** — Moricaud:
```python
if not save_throw():  # Random save chance
    strength -= 1
    print("Your strength fades!")
```

**Acid (0x47, 0x4E)** — Galgal / Nazgûl:
```python
# Multiple save throws (Nazgûl is harder to save against)
if attack_char == 0x47:  # Galgal
    if save_throw(): return  # Easier save

if attack_char == 0x4E:  # Nazgûl
    if save_throw(): return  # Harder save

if player_has_item(2):  # Has potion (acid resistance?)
    if save_throw(): return

# Acid hits!
current_food -= 1
if current_food < 0:
    process_game_over(0x65)  # Death by starvation/acid
```

**Drain Intelligence (0x9E)**:
```python
if not save_throw():
    intelligence -= 1
    if intelligence < 1:
        process_game_over(100)  # Fatal intelligence drain
```

**Drain Experience (0x73)** — Succubus:
```python
if not save_throw():
    exp_loss = 10 + random_mod(10)  # 10-19 XP lost
    experience -= exp_loss
    if experience < level_threshold[player_level - 1]:
        lose_experience_level()  # Level down!
```

**Fear (0x45)** — Eye of Sauron:
```python
roll = random_mod(5)
if roll < 4:  # 80% chance
    monster.is_fleeing = 0   # Eye stops being hostile after attack
    monster.is_hostile = 1
    is_dying = 1

    if roll == 3:  # 25% of triggers = death sentence
        death_timer = 100 + random_mod(50)   # 100-149 turns to live
    else:
        death_timer = 15 + random_mod(5)     # 15-19 turns to live
```

**Confuse (0x48)** — Huorn:
```python
is_confused = 1
```

**Steal Item (0x46)** — Fairy:
```python
# Try to steal shield first (if unenchanted, subtype >= 6)
if equipped_shield and not shield.is_enchanted:
    if shield.subtype >= 6 and save_throw():
        handle_item_drop_or_unequip(shield)
        # goto end

# Otherwise pick random item from inventory
attempts = 0
while attempts < 10:
    attempts += 1
    idx = random_mod(item_count) + 1
    # Walk inventory list to find item at position idx
    item = walk_inventory(idx)
    success = handle_item_drop_or_unequip(item)
    if success:
        break

if success:
    # Special: if stolen item is light source (type 8) on level 1
    if item.type == 8:
        has_light = 0
        if dungeon_level == 1:
            # Remove Eye of Sauron from map
            map[eye_row * 79 + eye_col] = ' '

    cleanup_after_monster_death()  # Monster flees
    destroy_or_consume_item(item)
```

**Steal Gold (0x56)** — Voleur (Thief):
```python
stolen = random_mod(11) * (some_multiplier)
if stolen > gold:
    stolen = gold
gold -= stolen
if stolen > 0:
    if not is_blind:
        print("The thief steals your gold!")
    else:
        print("Something steals your gold!")
    cleanup_after_monster_death()  # Monster flees with gold
```

---

## 4. Ranged/Thrown Attack

**Function**: `handle_attack_action(item)` (line 9233)

Handles throwing items (weapons, armor) at monsters. The item is consumed on use.

```python
def handle_attack_action(item):
    # Unequip/remove item from inventory
    handle_item_drop_or_unequip(item)
    if not success: return

    # Calculate throw distance
    distance = current_food // 4 + random_mod(current_food // 4 + 1) + 1

    # Determine landing position (projectile path)
    target = compute_projectile_path(distance)
    manhattan_dist = abs(target.x - player_x) + abs(target.y - player_y)

    if no_monster_at(target):
        # Item lands on empty floor
        if target == player_position:
            print("It hits you!")
        else:
            # Item falls to ground (becomes floor item)
            drop_item_at(target, item)
        return

    # Monster found at target position
    monster = find_item_at_coords(target)

    # Check if monster is passive and not hostile
    if manhattan_dist < 2 and not monster.is_hostile:
        # Check if monster type is non-aggressive
        if is_passive_type(monster.attack_char):
            print("The monster ignores the attack")
            return

    # To-hit roll for ranged attack
    to_hit_check = (player_level + strength - monster.to_hit - manhattan_dist)
    if probability_check(to_hit_check):
        # HIT
        monster.is_hostile = 0  # Engage monster

        # Damage based on thrown item type
        if item.type == 7:  # Weapon
            apply_armor_damage_reduction(monster, item)
        elif item.type == 6:  # Armor/equipment
            monster.hp -= item.power + weapon_table[item.subtype]
        else:
            monster.hp -= 1  # Other items do 1 damage

        if monster.hp <= 0:
            kill_monster(monster)
    else:
        # MISS
        drop_item_at(target, item)  # Item falls near monster

    destroy_or_consume_item(item)
```

---

## 5. Armor Damage Reduction

**Function**: `apply_armor_damage_reduction(monster, weapon)` (line 9205)

Calculates weapon damage when throwing/using a weapon against a monster:

```python
def apply_armor_damage_reduction(monster, weapon):
    # Special combo: weapon subtype 12 + wielded weapon subtype 11
    if weapon.subtype == 12 and wielded_weapon and wielded_weapon.subtype == 11:
        # Combined special attack
        base = 6 + random_mod(7)  # 6-12
        total = base + wielded_weapon.power + weapon.power
        monster.hp -= total
    else:
        # Standard: look up base damage from weapon table
        base_damage = weapon_damage_table[weapon.subtype]  # DS:-0x6123
        monster.hp -= base_damage
```

---

## 6. Monster Death & XP

**Function**: `kill_monster(show_message, monster)` (line 6130)

### Death Sequence

```python
def kill_monster(show_message, monster):
    if show_message:
        # 1. Display kill message
        if detect_monsters_active:
            write_bytes(7)  # Bell/notification

        if not is_blind:
            display_monster_name(monster.original_template_index)
            # "You killed the [monster]!"
        else:
            print("Something dies!")

        # 2. Drop carried item
        if monster.carried_item:
            item = monster.carried_item
            item.y = player_y
            item.x = player_x
            find_empty_floor_tile(item)  # Find nearby empty spot
            display_char = lookup_table_b9c7(item)
            map[item.y * 79 + item.x] = display_char
            prepend_item_to_list(dungeon_level, item)

        # 3. Special on-death effects
        if monster.attack_char == 'V':   # Vampire
            place_player_on_level(1)     # Level warp
        elif monster.attack_char == 'F':  # Fairy
            place_player_on_level(0)     # Level warp
        elif monster.attack_char == 'H':  # Huorn
            is_confused = 0              # Cure confusion

    # 4. Clear from map
    map_overlay[monster.y * 79 + monster.x] = ' '
    put_char_at_pos(' ', monster.x, monster.y)

    # 5. Remove from linked list
    FUN_1000_1d47(monster)  # Unlink from level list

    if show_message:
        # 6. XP reward
        xp_gain = monster.experience_value

        # Bonus XP tracking via saved monster data
        if monster_tracking_active:  # 0xB8BC
            # Additional XP calculation
            pass

        # XP scaling check
        level_diff = level_threshold[player_level] - level_threshold[player_level - 1]
        if probability_check(level_diff):
            # Cap XP to half the level-up requirement
            xp_gain = level_diff // 2

        experience += xp_gain
        if experience < 0:
            experience = 0

        # Level up check
        if experience >= level_threshold[player_level]:
            level_up_character()

        # Increment kill counter for this template
        kill_count[monster.template_index] += 1
        display_character_stats()

    # 7. Unlink from level monster list
    # Walk list to find and remove monster
    if monster_list[dungeon_level] == monster:
        monster_list[dungeon_level] = monster.next
    else:
        prev = monster_list[dungeon_level]
        while prev.next != monster:
            prev = prev.next
        prev.next = monster.next

    # 8. Free object and update count
    free_monster_object(monster)
    monster_count[dungeon_level] -= 1
    render_field_of_view()
```

### XP Rewards by Monster

| Monster | XP | Monster | XP |
|---------|---:|---------|---:|
| Spider | 1 | Galgal | 10 |
| Bat | 1 | Werewolf | 10 |
| Rat | 1 | Troll | 10 |
| Snake | 2 | Huorn | 15 |
| Wolf | 2 | Woose | 15 |
| Goblin | 3 | Fairy | 20 |
| Crebain | 3 | Thief | 20 |
| Mewlip | 4 | Dragon | 25 |
| Orc | 5 | Air | 28 |
| Eye | 5 | Dr. Aile | 30 |
| Moricaud | 6 | Succubus | 30 |
| Uruk-hai | 6 | Carcharoth | 30 |
| Variag | 6 | Nazgul | 35 |
| Warg | 7 | Oliphant | 35 |
| Balrog | 40 | Saruman | 50 |
| Glaurung | 70 | Sauron | 100 |
| Ungoliant | 150 | Morgoth | 200 |

---

## 7. Special Combat Mechanics

### Shapeshifter Reveal

**Function**: `reveal_shapeshifter(monster)` (line 6283)

When a disguised monster (attack_char != visible_char) is hit, it is revealed:

```python
def reveal_shapeshifter(monster):
    if not is_blind and not confusion_lock:
        print("The creature reveals its true form!")
        intelligence -= 5  # Shock penalty
    monster.visible_char = monster.attack_char
    monster.original_template_index = monster.template_index
```

This primarily affects disguised Sauron (appears as a random normal monster but has
Sauron's stats). The intelligence loss is the "shock" of discovering the true nature.

### Monster Breeding / Consumable Destruction

**Function**: `process_monster_breeding()` (line 6304)

Called after certain counter-attack events. Walks the player's inventory and has a
5% chance to destroy each potion (type 2) or scroll (type 3):

```python
def process_monster_breeding():
    item = inventory_list
    while item:
        next_item = item.next  # Save next before potential destruction
        if item.type in [2, 3]:  # Potion or Scroll
            if random_mod(20) == 0:  # 5% chance
                destroy_or_consume_item(item)
        item = next_item
```

### Counter-Attack Mechanic

When attacking certain monster types (Dragon 0x44, variant 0x92), if the monster
survives and a probability check passes (based on ring2_bonus + weapon_enchant):

```python
# Monster retaliates
counter_damage = 0
for i in range(monster.num_attacks):
    counter_damage += 1 + random_mod(monster.damage_per_attack)

# Damage reduction item (ITEM_UNKNOWN_D)
if player_has_item(ITEM_UNKNOWN_D):
    counter_damage = counter_damage // 3 + 1

current_hp -= counter_damage
if current_hp < 1:
    process_game_over(monster.template_index)

# Also destroys some consumables
process_monster_breeding()
```

### Cleanup After Monster Death (Flee)

**Function**: `cleanup_after_monster_death()` (line 6346)

Used when a monster flees (after stealing gold/items). Saves the next monster pointer,
then kills the current monster without displaying the death message or granting XP:

```python
def cleanup_after_monster_death():
    # Save next pointer before killing
    next_monster = current_monster_in_loop.next
    current_monster_in_loop.flag = 1  # Mark for cleanup
    kill_monster(show_message=False, monster=current_monster_in_loop)
    # Restore next pointer to continue monster processing loop
    current_monster_in_loop = next_monster
```

---

## 8. Weapon Damage Table

Base damage values at `DS:0x9EDD` (formula: `subtype * 2 + DS:0x9EDD`), and
weapon attack bonus at `DS:0x9E7B` (formula: `subtype * 4 + DS:0x9E7B`):

| Sub | Base Dmg | Atk Bonus | Weight | Name (from context) |
|----:|---------:|----------:|-------:|---------------------|
| 1 | 6 | 1 | 2 | Dagger |
| 2 | 4 | 1 | 2 | Short sword |
| 3 | 10 | 2 | 4 | Long sword |
| 4 | 7 | 3 | 4 | Mace |
| 5 | 8 | 4 | 4 | Flail |
| 6 | 8 | 5 | 4 | War hammer |
| 7 | 15 | 5 | 4 | Battle axe |
| 8 | 18 | 6 | 5 | Great sword |
| 9 | 21 | 7 | 4 | Mithril sword |
| 10 | 20 | 6 | 5 | Great axe |
| 11 | 1 | 1 | 2 | Staff |
| 12 | 3 | 0 | 2 | Arrow/bolt |
| 13 | 13 | 4 | 2 | Mithril dagger |
| 14 | 19 | 5 | 4 | Dragon slayer |
| 15 | 19 | 5 | 4 | Vampiric blade |

### Special Weapon Properties

| Subtype | Property |
|--------:|----------|
| 9 | Mithril sword: +3 to-hit bonus |
| 10 | Undead weapon: extra HP damage vs Confuse types (Huorn) |
| 11 | Staff combo: combined damage with thrown weapon subtype 12 |
| 12 | Arrow: special combo with staff (subtype 11) |
| 13 | Mithril dagger: +3 to-hit bonus; extra damage vs ghost/Balrog |
| 14 | Dragon slayer: extra damage vs Dragon (0x44), Balrog (0x42), variant (0x92) |
| 15 | Vampiric blade: 25% chance to heal player for half damage dealt |

---

## 9. Experience Level Thresholds

Player levels up when XP reaches these thresholds (`level * 2 + DS:0xB948`):

| Level | XP Needed | Level | XP Needed |
|------:|----------:|------:|----------:|
| 1 | 10 | 8 | 1,280 |
| 2 | 20 | 9 | 2,200 |
| 3 | 40 | 10 | 3,700 |
| 4 | 80 | 11 | 6,000 |
| 5 | 160 | 12 | 9,000 |
| 6 | 320 | 13 | 14,000 |
| 7 | 640 | | |

XP doubles each level through 8, then scales more gradually. Player level is initialized
to 0x80 (128) and decremented on each level-up (unusual reverse-counting scheme).

---

## 10. Helper Functions

### get_sign (line 48)

Returns the sign of a value: -1, 0, or +1.

```python
def get_sign(value):
    if value == 0: return 0
    elif value < 0: return -1
    else: return 1
```

Used in movement/direction calculations for combat positioning.

### calculate_dice_or_damage (line 2148)

Calculates item weight based on type and subtype (see ENTITY_DATABASE.md):

```python
def calculate_dice_or_damage(subtype, item_type):
    if item_type in [2, 3, 4]:      # Potion, Scroll, Ring
        return 1
    elif item_type in [5, 1, 8]:     # Wand, Food, Light
        return 2
    elif item_type == 7:             # Weapon (varies by subtype)
        if subtype in [1,2,11,12,13]: return 2
        elif subtype in [3,4,5,6,7,9,14,15]: return 4
        elif subtype in [8,10]: return 5
    elif item_type == 6:             # Armor
        if 1 <= subtype <= 6: return subtype // 2 + 4  # 4-7
        elif 7 <= subtype <= 11: return 2
```

---

## Answers to Key Questions

### 1. Full Attack Resolution Formula

**Player → Monster (melee)**:
```
to_hit = player_level + [weapon.power] - monster.to_hit - monster.AC + 1
       + random(0..strength-1) [+ 3 if mithril weapon]
if to_hit >= 1: HIT
damage = random(0..weapon_attack_bonus + player_level*food_cap/10) + 1 + thrown_bonus
monster.hp -= damage
```

**Monster → Player**:
```
to_hit = monster.to_hit - player_level - base_ac + 1
       + random(0..speed_bonus-1) [- 8 if stunned] - ring2_bonus
if to_hit >= 1: HIT
damage = sum(num_attacks × (1 + random(0..damage_per_attack-1)))
current_hp -= damage
```

### 2. Special Attack Types

12 distinct special attack types tied to monster identity (see table in section 1):
- **Stat drains**: Strength (Moricaud), Intelligence (variant), Experience (Succubus)
- **Status effects**: Fear/death timer (Eye), Confusion (Huorn), Paralysis removal (Ghosts)
- **Theft**: Items (Fairy), Gold (Thief)
- **Damage over time**: Acid reducing food (Galgal, Nazgûl)
- **Debuff**: Remove enchantments (Mewlip)
- **Boss abilities**: Teleport escape (Sauron), Random chaos (Saruman)

### 3. Monster Special Abilities and Flags

- `is_hostile` (0x28): Controls whether monster attacks. Cleared when player hits it.
- `is_fleeing` (0x22): Set by fear effects or after theft; monster moves away.
- `is_stationary` (0x29): Boss monsters never move. Cannot be repositioned.
- `is_invisible` (0x27): Sauron can become invisible mid-combat.
- `attack_char` (0x00): Determines all special combat behavior.
- `special_ability` (0x1A): Template-based ability (25 for Saruman, 13 for Air elemental).

### 4. Death/XP Rewards

- XP = `monster.experience_value` (1–200 range, see table)
- XP can be capped to half the level-up requirement (probability-based)
- Kill counter incremented per template type
- On-death effects: Vampire warps level, Fairy warps level, Huorn cures confusion
- Carried items drop near player's position
- Resurrection via belt item (type 0x0F) with stat penalties

### 5. Counter-Attack Mechanics

Certain monster types (Dragon, variant 0x92) can counter-attack when the player hits them:
- Triggers based on ring2_bonus + weapon_enchant threshold
- Monster deals full melee damage (num_attacks × random damage)
- Reduced by 2/3 if player has ITEM_UNKNOWN_D
- Can kill the player
- Also triggers `process_monster_breeding` (5% chance to destroy each potion/scroll)
