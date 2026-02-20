# MORIA DOS 1.9.8.7 — Magic System (Potions, Wands, Scrolls, Status Effects)

Reverse-engineered from `MORIA_with_constants.C` functions: `drink_potion_effect` (line 10044),
`FUN_1000_aa1d` (line 8666, wand targeting monsters), `FUN_1000_b032` (line 8897, wand targeting environment),
`execute_spell_effect` (line 9495), `learn_spell` / `remove_spell` (lines 7181, 7071),
`show_spell_info` / `check_spell_cast_chance` (lines 9354, 9462), `use_item_from_inventory` (line 10573),
`check_confusion_recovery` (line 10536), `apply_heroism_effect` (line 5930). Cross-referenced with
`ENTITY_DATABASE.md` (item subtypes and identification tables).

---

## Table of Contents

1. [Potion Effects (24 subtypes)](#1-potion-effects-24-subtypes)
2. [Wand Effects (22 subtypes)](#2-wand-effects-22-subtypes)
3. [Scroll Effects (25 subtypes)](#3-scroll-effects-25-subtypes)
4. [Status Effect System](#4-status-effect-system)
5. [Item Identification System](#5-item-identification-system)
6. [Spell/Magic System](#6-spellmagic-system)
7. [Special Mechanics](#7-special-mechanics)

---

## 1. Potion Effects (24 subtypes)

**Function**: `drink_potion_effect(param_1, potion)` (line 10044)

All potions add `200 + random(100)` to `food_level` before their effect triggers.

### Complete Potion Table

| Sub | French Name | English | Effect | Duration/Value | Special |
|----:|-------------|---------|--------|----------------|---------|
| 1 | de guérison | Healing | Heal HP | `2*level + random(3*level)` or `+1d6 max HP` | Full heal if at max |
| 2 | d'extra-guérison | Extra-healing | Full HP | `+0d15 max HP` if at max, else full | Cures blindness |
| 3 | de constitution | Constitution | Restore food | `+1d4/3 current, +1 max` | |
| 4 | de force | Strength | Full food | Full restore or `+2d2` | |
| 5 | de confusion | Confusion | Speed boost | 100-149 turns | |
| 6 | empoisonnée | Poison | Acid damage | `-1d3-1 food` (fatal at 0) | Needs anti-acid item |
| 7 | amnésiante | Amnesia | Full detect | Reveals all; clears IDs | Unidentifies all items! |
| 8 | paralysante | Paralysis | Poison | 20-29 turn death timer | |
| 9 | accélérante | Speed boost | Paralyze OR anti-haste | 10-14 turns | Cancels haste if active |
| 10 | ralentissante | Slow | Haste OR anti-paralyze | 30-34 turns | Cancels paralysis if active |
| 11 | hallucinogène | Hallucination | Hallucination | 350-399 turns, -1 INT | Fatal if INT reaches 0 |
| 12 | aveuglante | Blindness | Blindness | 200-299 turns | |
| 13 | nourrissante | Nourishing | Time warp | +500-599 turns | Advances turn counter |
| 14 | d'expérience | Experience | Level up | Gain 1 level | XP set to mid-level |
| 15 | de perte de niveau | Level drain | Lose level | -1 level | XP reset to level threshold |
| 16 | d'extralucidité | Clairvoyance | Teleport effect | 300-399 turns | Calls FUN_1000_53c9 |
| 17 | de désorientation | Disorientation | Teleport | 150-249 turns | Full screen clear |
| 18 | passe muraille | Pass-through-walls | Phase door | 15-24 turns | |
| 19 | de lévitation | Levitation | Levitation | 100-149 turns | |
| 20 | désaltérante | Thirst-quenching | Food boost | +400-599 food | |
| 21 | d'invisibilité | Invisibility | Unknown status | 25-39 turns | Sets status_flag_5 |
| 22 | gazéifiante | Gasification | Wizard mode | 25-39 turns | **Destroys inventory!** |
| 23 | de dexterité | Dexterity | Gain strength | +1 strength | |
| 24 | de régénération | Regeneration | Learn spell | Consume food item | Max 4 spells |

### Key Potion Mechanics

#### Healing (subtype 1)

```python
def potion_healing():
    food_level += 200 + random(100)

    if current_hp == max_hp:
        # Already at max — increase max HP
        max_hp += 1 + random(6)
        current_hp = max_hp
    else:
        # Heal based on level
        current_hp += player_level * 2 + random(player_level * 3)
        if current_hp > max_hp:
            current_hp = max_hp

    display_character_stats()
```

#### Extra-Healing (subtype 2)

```python
def potion_extra_healing():
    food_level += 200 + random(100)

    if current_hp == max_hp:
        # Increase max HP significantly
        max_hp += 1 + random(15)
        current_hp = max_hp
    else:
        # Full heal
        current_hp = max_hp

    # Cure blindness
    if is_blind:
        is_blind = 0
        needs_full_update = 0
        redraw_dungeon_level(0x17)

    display_character_stats()
```

#### Amnesia (subtype 7) — DANGEROUS!

```python
def potion_amnesia():
    # Clear screen and reset all identification
    clear_screen_double()
    display_character_stats()
    needs_full_update = 1
    detect_timer = 50 + random(75)  # 50-124 turns

    # UNIDENTIFY ALL ITEMS (types 2-5: potions, scrolls, rings, wands)
    for item_type in [2, 3, 4, 5]:
        for subtype in range(1, 25):
            identified_table[item_type * 0x18 + subtype] = 0
            alt_check_table[item_type * 0x18 + subtype] = 0

    # Unidentify all items in inventory (types 7, 6 = weapons, armor)
    for item in inventory:
        if item.type in [7, 6]:
            item.is_identified = 0

    # Clear all explored tiles on all levels
    for level in range(1, 16):
        for y in range(1, 24):
            for x in range(1, 80):
                explored_map[level][y][x] = 0

    # Regenerate randomized names
    generate_random_names()
    randomize_item_appearances()
```

#### Wizard Mode (subtype 22 = 0x16) — EXTREMELY DANGEROUS!

```python
def potion_wizard_mode():
    is_wizard = 1
    wizard_mode_timer = 25 + random(15)  # 25-39 turns

    # DESTROY MOST INVENTORY!
    # Keeps: equipped items, spell items, food (quantity 1), light sources (subtype 22)
    for item in inventory:
        keep = False

        # Check if equipped
        if item in [wielded_weapon, equipped_shield, equipped_armor, equipped_ring1, equipped_ring2]:
            keep = True

        # Check if in spell list
        if item in spell_list:
            keep = True

        # Keep food with quantity 1
        if item.type == 1 and item.quantity == 1:
            keep = True

        # Keep light source subtype 22
        if item.type == 2 and item.subtype == 22:
            keep = True

        # Special check for weapon subtype 12
        if is_type_7_subtype_12(item):
            keep = True

        if not keep:
            destroy_or_consume_item(item)

    # Clear all belt slots
    for i in range(1, 11):
        belt[i] = None
```

#### Learn Spell (subtype 24 = 0x18)

```python
def potion_learn_spell():
    if spell_count >= 4:
        display_score_with_fatal(0xFE57)  # "You can't learn more spells"
        return

    # Check if player has food item
    if equipped_food is None or not check_inventory_has_item(ITEM_FOOD):
        display_score_with_fatal(0xFE57)
        return

    # Consume food item and learn spell
    decrement_item_quantity(9)
    destroy_or_consume_item(equipped_food)
    spell_count += 1
    display_score_with_fatal(0xFF2F)  # "You learned a new spell"
```

---

## 2. Wand Effects (22 subtypes)

Wands have **charges** (stored in `item.power`). Each use consumes 1 charge.

### Wand Effects Table

| Sub | French Name | English | Target | Effect | Boss Behavior |
|----:|-------------|---------|--------|--------|---------------|
| 1 | de téléportation | Teleportation | Monster | Teleport to random position, cure confusion | Normal |
| 2 | de transmorphie | Polymorph | Monster | Pick random non-stationary template, copy stats | Can't polymorph bosses |
| 5 | de ralentissement | Slow monster | Monster | Wake/alert (10-19 turns) or sleep if awake | 5-9 turns for bosses |
| 6 | d'accélération | Haste monster | Monster | Sleep (10-19 turns) or remove alert if alerted | N/A |
| 7 | d'affaiblissement | Weakening | Monster | HP to 1/5; player HP to half | HP to half for bosses |
| 8 | pour effrayer | Fear | Monster | Make flee | N/A |
| 12 | de combat | Combat | Monster | Damage: `-(player_level + dungeon_level - 10)` HP | Boss: `random(11)` HP |
| 14 | assoupissante | Sleep | Monster | Make hostile (clear passive flag) | N/A |
| 15 | paralysante | Paralyze | Monster | Stun 10-16 turns | 2-4 turns for bosses |
| 16 | d'invisibilité | Invisibility | Monster | Make invisible | N/A |
| 18 | de renforcement | Strengthening | Monster | Monster HP +half +1; player HP +half +1 | N/A |
| 19 | capricieuse | Capricious | Monster | 50%: HP to 1, heal player; 50%: restore HP, player to 1 | N/A |
| 20 | d'illusion | Illusion | Monster | Change visible_char to random template | Can't polymorph bosses |
| 22 | d'absorption d'énergie | Energy drain | Monster | -1d3 to_hit; random(10)×? HP dmg; heal player | Boss: -1 to_hit |
| 3 | de destruction | Destruction | Environment | Dig/destroy walls/doors | |
| 4 | pour créer des murs | Create walls | Environment | Dig door; kill non-stationary monster | |
| 9 | de sourcier | Dowsing | Environment | Create trap tile (0xF7) | |
| 10 | d'invocation de monstre | Summon monster | Environment | Teleport first monster to target | |
| 11 | d'invocation d'objet | Summon item | Environment | Spawn random item (type 1-5) | |
| 13 | pour combler les trappes | Fill traps | Environment | Destroy door tiles (0x00-0x03) | |
| 17 | de création de trappes | Create traps | Environment | Place wall tile (0x01) if empty | |
| 21 | de purification | Purification | Environment | Disarm trap (0xF7 → clear) | |

### Monster-Targeting Wands (FUN_1000_aa1d)

```python
def use_wand_on_monster(wand, target_x, target_y):
    monster = find_item_at_coords(target_x, target_y)
    if monster is None:
        return

    # Increment unknown counter
    monster.unknown_2c += 1

    subtype = wand.subtype

    # Teleportation (1) or Invisibility (16)
    if subtype in [1, 0x10]:
        # Check if monster can teleport (bitmask check at 0xb82f)
        if is_teleportable(monster):
            find_random_empty_floor_space(monster)
            map_overlay[target_y * MAP_WIDTH + target_x] = ' '
            put_char_at_pos(' ', target_x, target_y)
            map_overlay[monster.y * MAP_WIDTH + monster.x] = monster.visible_char

            if is_confused:
                is_confused = 0
            monster.is_visible = 0

        if subtype == 0x10:  # Invisibility
            monster.is_invisible = 1

    # Polymorph (2)
    elif subtype == 2:
        if not monster.is_stationary:
            # Pick random non-stationary template
            while True:
                new_template = random_mod(0x23) + 1  # 1-35
                if monster_templates[new_template].is_stationary == 0:
                    break

            # Copy template stats
            monster.visible_char = monster_templates[new_template].attack_char
            monster.attack_char = monster.visible_char
            monster.template_index = new_template
            monster.original_template_index = new_template
            monster.to_hit = monster_templates[new_template].to_hit
            monster.experience_value = monster_templates[new_template].experience_value
            monster.hit_points = monster_templates[new_template].hit_points
            monster.armor_class = monster_templates[new_template].armor_class
            monster.damage_per_attack = monster_templates[new_template].damage_per_attack
            monster.num_attacks = monster_templates[new_template].num_attacks

            # Reset state
            monster.is_fleeing = 0
            monster.is_visible = 0
            monster.is_hostile = 0
            monster.stun_timer = 0
            monster.carried_item = None

            if is_confused:
                is_confused = 0

            # Update map
            map_overlay[monster.y * MAP_WIDTH + monster.x] = monster.visible_char
            put_char_at_pos(monster.visible_char, monster.x, monster.y)

    # Slow/Wake (5)
    elif subtype == 5:
        if not monster.is_awake:
            monster.is_alerted = 1
            if not monster.is_stationary:
                monster.status_timer = 10 + random(10)  # 10-19 turns
            else:
                monster.status_timer = 5 + random(5)    # 5-9 turns
        else:
            monster.is_awake = 0

    # Haste/Sleep (6)
    elif subtype == 6:
        if not monster.is_alerted:
            monster.unknown_2c -= 1  # Revert increment
            monster.is_awake = 1
            monster.status_timer = 10 + random(10)  # 10-19 turns
        else:
            monster.is_alerted = 0

    # Weakening (7)
    elif subtype == 7:
        if not monster.is_stationary:
            # Normal monster: HP to 1/5
            monster.hit_points = monster.hit_points // 5 + 1
        else:
            # Boss: HP to half (also hits player!)
            monster.hit_points = max_hp // 2 + 1

        # Player takes half damage
        current_hp = current_hp // 2 + 1
        display_character_stats()

    # Fear (8)
    elif subtype == 8:
        if not monster.is_stationary:
            monster.is_fleeing = 1

    # Combat/Damage (12 = 0xC)
    elif subtype == 0xC:
        if not monster.is_stationary:
            # Damage based on player level + dungeon level
            damage = (player_level + dungeon_level) - 10
            monster.hit_points -= random_mod(damage + 1)
        else:
            # Boss: random 0-10 damage
            monster.hit_points -= random_mod(11)

        if monster.hit_points <= 0:
            kill_monster(monster)

    # Sleep/Make Hostile (14 = 0xE)
    elif subtype == 0xE:
        if not monster.is_stationary:
            monster.is_hostile = 1  # Actually clears passive flag

    # Paralyze (15 = 0xF)
    elif subtype == 0xF:
        if not monster.is_stationary:
            monster.stun_timer = 10 + random(7)  # 10-16 turns
        else:
            monster.stun_timer = 2 + random(3)   # 2-4 turns

    # Strengthening (18 = 0x12)
    elif subtype == 0x12:
        # Heal both monster and player by half
        monster.hit_points += current_hp // 2 + 1
        current_hp = current_hp // 2 + 1
        display_character_stats()

    # Capricious (19 = 0x13 = CMD_SAVE)
    elif subtype == CMD_SAVE:
        if random_mod(2) == 1:
            # 50%: Monster to 1 HP, heal player
            if not monster.is_stationary:
                monster.hit_points = 1
                current_hp = 1 + random(max_hp)
        else:
            # 50%: Restore monster HP, player to 1 HP
            monster.hit_points = monster_templates[monster.template_index].hit_points
            current_hp = 1

        display_character_stats()

    # Illusion (20 = 0x14)
    elif subtype == 0x14:
        # Pick random non-stationary template
        while True:
            new_template = random_mod(0x23) + 1
            if monster_templates[new_template].is_stationary == 0:
                break

        monster.template_index = new_template
        monster.visible_char = monster_templates[new_template].attack_char

    # Energy Drain (22 = 0x15 = MAP_HEIGHT)
    elif subtype == MAP_HEIGHT:
        if not monster.is_stationary:
            # Reduce to_hit by 1-3
            reduction = random_mod(3) + 1
            monster.to_hit -= reduction
        else:
            # Boss: reduce by 1
            monster.to_hit -= 1

        # Damage monster HP
        random_mod(10)  # Some multiplier calculation
        damage = multiply_integers()  # Result of complex calc
        monster.hit_points -= damage

        if monster.to_hit < 1 or monster.hit_points < 0:
            kill_monster(monster)

        # Mark boss defeated flag
        if monster.is_stationary:
            boss_defeated_flag = 1

        # Heal player
        random_mod(10)
        heal = multiply_integers()
        current_hp += heal
        if current_hp > max_hp:
            current_hp = max_hp
        display_character_stats()
```

### Environment-Targeting Wands (FUN_1000_b032)

```python
def use_wand_on_environment(wand, target_x, target_y):
    if wand.power == 0:
        display_score_with_fatal(0x15)  # "The wand has no charges"
        return

    subtype = wand.subtype

    # Destruction (3)
    if subtype == 3:
        # Dig/destroy walls and doors
        tile_char = dungeon_map[target_y * MAP_WIDTH + target_x]

        # Check if passable or door
        if is_passable(tile_char) and (target_y % 2 == 1 or target_x % 2 == 1):
            # Destroy wall/door
            if is_passable_alt(tile_char):
                FUN_1000_2214(target_x, target_y)  # Update visibility
            else:
                FUN_1000_2138(target_x, target_y)  # Different update

            redraw_dungeon_level(player_y + 1)

    # Create Walls / Kill Monster (4)
    elif subtype == 4:
        tile_char = dungeon_map[target_y * MAP_WIDTH + target_x]

        # Destroy door
        if tile_char == 0xEF:  # Door tile
            if is_passable_alt(tile_char):
                FUN_1000_2214(target_x, target_y)

            FUN_1000_21b0(target_x, target_y)

            # Kill non-stationary monster at position
            if map_overlay[target_y * MAP_WIDTH + target_x] != ' ':
                if is_passable(dungeon_map[target_y * MAP_WIDTH + target_x]):
                    monster = find_item_at_coords(target_x, target_y)
                    if monster and not monster.is_stationary:
                        kill_monster(monster)

            redraw_dungeon_level(player_y + 1)

    # Dowsing / Create Trap (9)
    elif subtype == 9:
        tile_char = dungeon_map[target_y * MAP_WIDTH + target_x]

        # Place trap tile
        if is_passable(tile_char) or tile_char == 0xEF:
            if is_passable_alt(tile_char):
                FUN_1000_2214(target_x, target_y)

            dungeon_map[target_y * MAP_WIDTH + target_x] = 0xF7  # Trap tile
            render_field_of_view()

    # Summon Monster (10 = 0xA)
    elif subtype == 0xA:
        if map_overlay[target_y * MAP_WIDTH + target_x] == ' ':
            if is_passable(dungeon_map[target_y * MAP_WIDTH + target_x]):
                # Spawn monster at current level
                populate_level_with_monsters()

                if monster_list[dungeon_level]:
                    first_monster = monster_list[dungeon_level]

                    # Clear old position
                    map_overlay[first_monster.y * MAP_WIDTH + first_monster.x] = ' '

                    # Move to target
                    first_monster.y = target_y
                    first_monster.x = target_x

                    # Update map
                    map_overlay[target_y * MAP_WIDTH + target_x] = first_monster.visible_char
                    render_field_of_view()

    # Summon Item (11 = 0xB)
    elif subtype == 0xB:
        tile_char = dungeon_map[target_y * MAP_WIDTH + target_x]

        # Spawn random item (type 1-5)
        if is_passable(tile_char) or tile_char in [0xEF, 0xF7]:
            item_type = random_mod(5) + 1
            item = initialize_monster_or_item(dungeon_level, item_type)
            place_object_on_map(dungeon_level, item)

            # Clear old position
            dungeon_map[item.y * MAP_WIDTH + item.x] = ' '

            # Move to target
            item.y = target_y
            item.x = target_x

            # Display on map
            display_char = lookup_table_b9c7(item)
            dungeon_map[target_y * MAP_WIDTH + target_x] = display_char
            render_field_of_view()

    # Fill Traps / Destroy Doors (13 = 0xD)
    elif subtype == 0xD:
        tile_char = dungeon_map[target_y * MAP_WIDTH + target_x]

        # Destroy door tiles (0x00-0x03)
        if tile_char in [0x00, 0x01, 0x02, 0x03]:
            validate_window_coords(target_y + 1, target_x)
            write_bytes(0, ' ')
            flush_output()

            dungeon_map[target_y * MAP_WIDTH + target_x] = ' '

    # Create Traps / Place Wall (17 = 0x11)
    elif subtype == 0x11:
        if dungeon_map[target_y * MAP_WIDTH + target_x] == ' ':
            # Place wall tile
            dungeon_map[target_y * MAP_WIDTH + target_x] = 0x01

    # Purification / Disarm Trap (21 = 0x15)
    elif subtype == 0x15:
        if dungeon_map[target_y * MAP_WIDTH + target_x] == 0xF7:  # Trap
            # Clear trap flag
            trap_cleared_flag = 0

    # Default: use monster-targeting version
    else:
        FUN_1000_aa1d(wand, target_x - player_x, target_y - player_y)

    # Consume charge
    wand.power -= 1
```

---

## 3. Scroll Effects (25 subtypes)

**Function**: `execute_spell_effect(param_1, scroll)` (line 9495)

Scrolls are called "spells" in the code, but they're consumable items (not learned magic).

### Scroll Effects Table

| Sub | French Name | English | Effect | Special |
|----:|-------------|---------|--------|---------|
| 1 | de régénération | Regeneration | Enchant shield/armor/ring2 +1 | Priority: shield > armor > ring2; max +5 |
| 2 | pour enchanter les armures | Enchant armor | Protect shield | Make rust-proof (set is_enchanted) |
| 3 | pour enchanter son arme | Enchant weapon | Enchant weapon +1, +1 CON | Max +10 power |
| 4 | topographique | Map reveal | Reveal map | Explore current dungeon level |
| 5 | d'identification | Identify | Identify item | Mark item as identified |
| 6 | de téléportation | Teleport | Teleport player | Random position on current level |
| 7 | d'hyper téléportation | Hyper-teleport | Level warp | Move to random dungeon level |
| 8 | pour invoquer un monstre | Summon monster | Spawn monster | Near player position |
| 9 | de protection | Protection | AC boost | Temporary AC increase |
| 10 | pour détecter la magie | Detect magic | Detect magic items | Reveal magic items |
| 11 | pour détecter la nouriture | Detect food | Detect food | Reveal food items |
| 12 | pour repérer les monstres | Detect monsters | Detect monsters | Reveal all monsters |
| 13 | pour détecter l'or | Detect gold | Detect gold | Reveal gold piles |
| 14 | d'ensorcellement | Enchantment | Unknown | Complex spell effect |
| 15 | de sommeil | Sleep | Sleep monsters | Put nearby monsters to sleep |
| 16 | vierge | Blank | No effect | Does nothing |
| 17 | pour enlever les sorts | Remove curses | Uncurse items | Remove curse from equipped items |
| 18 | de démolition | Demolition | Destroy walls | Targeted destruction |
| 19 | de destruction | Destruction | Mass destruction | Area effect |
| 20 | pour effrayer les monstres | Scare monsters | Fear effect | Make monsters flee |
| 21 | d'éparpillement | Scatter | Scatter effect | Unknown teleport effect |
| 22 | pour enchanter les anneaux | Enchant rings | Enchant ring | +1 to equipped ring |
| 23 | de dégradation d'anneaux | Degrade rings | Degrade ring | -1 to equipped ring |
| 24 | d'intelligence | Intelligence | +1 INT | Permanent stat increase |

### Key Scroll Mechanics

#### Enchant Shield/Armor/Ring (subtype 1)

```python
def scroll_regeneration(scroll):
    # Cast chance check
    roll = random_mod(21)
    threshold = player_level // 2 + intelligence

    if threshold < roll:
        if equipped_artifact:  # 0xB8A0
            # Second chance with harder roll
            roll2 = random_mod(25)
            if threshold < roll2:
                display_score_with_fatal(0xFF34)  # "Failed to cast"
                check_spell_cast_chance(scroll)
                return

    # Priority: shield > armor > ring2
    if equipped_shield and equipped_shield.power < 5:
        display_score_with_fatal(0x12F)  # "Your shield glows"
        wisdom += 1
        equipped_shield.power += 1
        equipped_shield.is_cursed = 0
    elif equipped_armor and equipped_armor.power < 5:
        equipped_armor.power += 1
        equipped_armor.is_cursed = 0
        dexterity = (get_sign(equipped_armor.power) + equipped_armor.power) // 2
    elif equipped_ring2 and equipped_ring2.power < 5:
        equipped_ring2.power += 1
        equipped_ring2.is_cursed = 0

    base_ac = wisdom + dexterity
    display_character_stats()
```

#### Protect Armor (subtype 2)

```python
def scroll_protect_armor(scroll):
    if equipped_shield:
        display_score_with_fatal(7)  # "Your shield is now protected"
        equipped_shield.is_enchanted = 1  # Rust-proof
```

#### Enchant Weapon (subtype 3)

```python
def scroll_enchant_weapon(scroll):
    if wielded_weapon:
        display_score_with_fatal(8)  # "Your weapon glows"
        wielded_weapon.power += 1
        constitution += 1

        # Cap weapon power at 10
        if wielded_weapon.power > 10:
            wielded_weapon.power = 10

        display_character_stats()
```

---

## 4. Status Effect System

MORIA tracks player status via global flags and timers. Each turn, timers decrement; at 0, effects end.

### Status Effect Flags & Timers

| Effect | Flag Address | Timer Address | Trigger | Duration |
|--------|--------------|---------------|---------|----------|
| Speed boost | `speed_boost_active` | `speed_timer` | Potion 5 | 100-149 turns |
| Haste | `is_hasted` | `haste_timer` | Potion 10 | 30-34 turns |
| Paralysis | `is_paralyzed` | `paralyze_timer` | Potion 9 | 10-14 turns |
| Blindness | `is_blind` | `blind_timer` | Potion 12 | 200-299 turns |
| Hallucination | `hallucination_active` | `hallucination_timer` | Potion 11 | 350-399 turns |
| Confusion | `confusion_lock` | — | Potion 11, check_confusion_recovery | 30-49 turns (from hallucination) |
| Dying | `is_dying` | `death_timer` | Potion 8 | 20-29 turns (fatal) |
| Detect | — | `detect_timer` | Potion 7 | 50-124 turns |
| Teleport | `is_teleporting` | `teleport_timer` | Potion 17 | 150-249 turns |
| Teleport effect | `teleport_effect_flag` | `effect_timer_16` | Potion 16 | 300-399 turns |
| Phase door | `status_flag_3` | `status_timer_3` | Potion 18 | 15-24 turns |
| Levitation | `status_flag_1` | `status_timer_1` | Potion 19 | 100-149 turns |
| Unknown (invisible?) | `status_flag_5` | `status_timer_5` | Potion 21 | 25-39 turns |
| Wizard mode | `is_wizard` | `wizard_mode_timer` | Potion 22 | 25-39 turns |

### Confusion Recovery System

**Function**: `check_confusion_recovery()` (line 10536)

When `hallucination_active` is cleared (timer expires), confusion may continue:

```python
def check_confusion_recovery():
    if hallucination_active:
        # Hallucination still active — convert to confusion
        confusion_lock = 1
        hallucination_timer = 30 + random(20)  # 30-49 turns
        display_character_stats()
```

### Heroism Effect

**Function**: `apply_heroism_effect()` (line 5930)

Triggered when 10+ monsters on current level:

```python
def apply_heroism_effect():
    # Make Eye and Huorn monsters flee
    for monster in monster_list[dungeon_level]:
        if monster.attack_char in [0x45, 0x48]:  # 'E' (Eye), 'H' (Huorn)
            monster.is_fleeing = 1
            monster.is_hostile = 0
            monster.to_hit += 1  # Also buff monster slightly

    # Reset some counter
    some_counter[dungeon_level] = 4
```

---

## 5. Item Identification System

MORIA uses **two parallel identification tables** to track which item types the player has identified.

### Identification Tables

**Address**: `type * 0x18 + subtype`

| Table | Base Address | Purpose |
|-------|-------------|---------|
| `identified_table` | `-0x65a2` | Primary ID flag (0=unknown, nonzero=identified) |
| `alt_check_table` | `-0x6542` | Secondary ID flag (used for certain checks) |

**Stride**: `0x18` = 24 bytes per item type (supports subtypes 0-23)

### Auto-Identification

Certain items auto-identify when used or equipped:

```python
def show_spell_info(item):
    # Check if already identified
    if identified_table[item.type * 0x18 + item.subtype]:
        return
    if alt_check_table[item.type * 0x18 + item.subtype]:
        return

    # Scroll subtypes 0xF (15), 0x10 (16) auto-identify
    if item.type == 3 and item.subtype in [0xF, 0x10]:
        return

    # Potion subtype 7 (Amnesia) is hidden
    if item.type == 2 and item.subtype == 7:
        return

    # Potion subtypes 0x10 (16), 0x12 (18) auto-identify
    if item.type == 2 and item.subtype in [0x10, 0x12]:
        return

    # Scroll subtypes 1-3, 5, 0x14 (20), 0x15 (21) require special handling
    if item.type == 3:
        if item.subtype in [1, 2, 3]:
            # ... special checks ...
            pass
        elif item.subtype in [5, 0x14, 0x15]:
            # ... more checks ...
            pass

    # Display unidentified name
    display_message("You read the scroll")
    print(" ")

    # Read from unidentified description table
    read_string_from_file(0x1C, item.type * 0x2B8 + item.subtype * 0x1D + (-0x75DE))

    # ... possibly identify based on correct naming ...
```

### Identification on Equip

```python
def equip_item(item):
    # Equipping auto-identifies
    item.is_identified = 1

    # Also mark in global table
    identified_table[item.type * 0x18 + item.subtype] = 1
```

### Potion Auto-ID Exceptions

Some potions always identify on use (from `drink_potion_effect`, lines 10507-10528):

```python
# Potions 5, 6 auto-identify
if potion.subtype in [5, 6]:
    identified_table[2 * 0x18 + potion.subtype] = 1

# Potions 8-10 auto-identify
if potion.subtype in [8, 9, 10]:
    identified_table[2 * 0x18 + potion.subtype] = 1

# Potions 12, 17, 18, 21, 22 auto-identify
if potion.subtype in [0xC, 0x11, 0x12, 0x15, 0x16]:
    identified_table[2 * 0x18 + potion.subtype] = 1
```

---

## 6. Spell/Magic System

### Spell Learning

Spells are **scroll/wand items** stored in a **spell list** (max 4).

**Function**: `learn_spell(spell_item)` (line 7181)

```python
def learn_spell(spell_item):
    # Mark item as identified
    spell_item.is_cursed = 1  # Reused field for "learned" flag

    # Find empty spell slot
    for slot in range(1, spell_count + 1):
        if spell_list[slot] is None:
            spell_list[slot] = spell_item
            display_score_with_fatal(0xFFAC)  # "You learned a spell"
            break
    else:
        # No empty slot — try to replace used spell
        for slot in range(1, spell_count + 1):
            if spell_list[slot].power == 0:  # No charges left
                spell_list[slot] = spell_item
                display_score_with_fatal(0xFFAC)
                break

    # Special: Light source subtype 8 with power 1 → reset food flags
    if spell_item.type == 8 and spell_item.power == 1:
        reset_food_flags()
        spell_item.power = 0

    # Special: Subtype 0xC → remove spell
    if spell_item.subtype == 0xC:
        remove_spell(slot)
```

### Spell Removal

**Function**: `remove_spell(slot)` (line 7071)

```python
def remove_spell(slot):
    # Get last spell
    last_index = spell_count
    spell_list[last_index] = None
    spell_count -= 1
    strength -= 2  # Penalty for losing spell!

    # Shift remaining spells down
    for i in range(slot + 1, spell_count + 1):
        spell_list[i - 1] = spell_list[i]

    display_character_stats()
    display_score_with_fatal(0xFE59)  # "You forgot a spell"
```

### Spell Casting Chance

**Function**: `check_spell_cast_chance(item)` (line 9462)

```python
def check_spell_cast_chance(item):
    if item.type == 2:  # Potion
        # Always consume (no check)
        destroy_or_consume_item(item)
    elif item.type == 3:  # Scroll
        # Scroll durability check
        durability = scroll_durability_table[item.subtype]  # At -0x6305
        if random_mod(durability) == 0:
            # Scroll survives
            return
        else:
            # Scroll is destroyed
            destroy_or_consume_item(item)
```

---

## 7. Special Mechanics

### Shield Destruction at High Food (Potion side-effect)

```python
def drink_potion_effect(potion):
    # ... apply potion effect ...

    # After effect, check food level
    if current_food > 28:  # 0x1C
        # Destroy equipped shield!
        if equipped_shield:
            destroy_or_consume_item(equipped_shield)
            equipped_shield = None
            wisdom = 0
            base_ac = dexterity
            display_score_with_fatal(0xFFAA)  # "Your shield dissolves!"
```

### Cast Failure Penalty

From `execute_spell_effect` (line 9495):

```python
def execute_spell_effect(scroll):
    # Casting check
    roll = random_mod(21)
    threshold = player_level // 2 + intelligence

    if threshold < roll:
        # Casting failed!
        display_score_with_fatal(0xFF34)  # "You failed to cast the spell"
        check_spell_cast_chance(scroll)  # May destroy scroll
        return

    # ... execute scroll effect ...
```

### Item Usage Dispatcher

**Function**: `use_item_from_inventory(result_ptr, command_key)` (line 10573)

```python
def use_item_from_inventory(result_ptr, command_key):
    check_minimum_stats()

    # Command: 'T' (0x54), 'R' (0x52), 'a' (0x61) — throw/read/activate
    if command_key in [0x54, 0x52, 0x61]:
        if item_count < 1:
            show_message_and_clear_flag(0x4B)  # "You have nothing"
            return

        if command_key == 0x61:  # 'a' = activate wand
            tile_char = dungeon_map[player_y * MAP_WIDTH + player_x]
            if tile_char != ' ':
                show_message_and_clear_flag(0x4C)  # "You can't use that here"
                return

    # Command: 'I' (0x49) — identify
    elif command_key == 0x49:
        if item_count < 1:
            show_message_and_clear_flag(0xB)
            return

    # Command: 'l' (0x6C) — look at light source
    elif command_key == 0x6C:
        if light_source_lo == 0 and light_source_hi == 0:
            show_message_and_clear_flag(1)
            return

    # Command: 'b' (0x62) — use belt item
    elif command_key == 0x62:
        if belt_item_lo == 0 and belt_item_hi == 0:
            show_message_and_clear_flag(0x16)
            return

    # Command: 'L' (0x4C) — learn spell
    elif command_key == 0x4C:
        if spell_item_lo == 0 and spell_item_hi == 0:
            show_message_and_clear_flag(0x1B)
            return

    # Command: 'E' (0x45 = ATTACK_FEAR) — equip
    elif command_key == ATTACK_FEAR:
        if equipped_item_lo == 0 and equipped_item_hi == 0:
            show_message_and_clear_flag(0x22)
            return
        else:
            # Check if spell list has room
            if spell_count > 0:
                for slot in range(1, spell_count + 1):
                    if spell_list[slot] is None:
                        break
                else:
                    # No room for spell
                    return

    # ... dispatch to appropriate handler ...
```

---

## Summary

### Complete Magic System

| System | Count | Mechanics |
|--------|------:|-----------|
| **Potions** | 24 | Consumable, randomized colors, auto-identify on use |
| **Wands** | 22 | Charges, target monster or environment, wood names |
| **Scrolls** | 25 | Durability check, random gibberish names, "spells" |
| **Status Effects** | 13+ | Timed flags, timers decrement each turn |
| **Spells** | Max 4 | Learned from scrolls/wands, stored in spell list |

### Key Addresses

| Data | Address | Formula | Size |
|------|---------|---------|------|
| Identified table | `-0x65a2` | `type * 0x18 + subtype` | 8 types × 24 subtypes |
| Alt check table | `-0x6542` | `type * 0x18 + subtype` | 8 types × 24 subtypes |
| Spell list | `-0x46cc` | `slot * 4` | 4 slots × 4 bytes (far pointer) |
| Spell count | `0xB936` | — | 1 word (max 4) |
| Scroll durability | `-0x6305` | `subtype * 4` | 25 entries × 4 bytes |

### Dangerous Items

**AVOID**:
- **Potion 7 (Amnesia)**: Unidentifies ALL items, clears explored map, resets names
- **Potion 22 (Gasification)**: Destroys most inventory items!
- **Potion 8 (Poison)**: Death timer (20-29 turns to find cure)
- **Potion 11 (Hallucination)**: -1 INT (fatal if INT reaches 0)

**USE CAREFULLY**:
- **Wand 7 (Weakening)**: Reduces player HP to half
- **Wand 19 (Capricious)**: 50% chance to set player HP to 1
- **Scroll 23 (Degrade rings)**: -1 to equipped ring

### Implementation Notes for Python Rewrite

1. **Potion effects**: Each subtype has unique effect; implement as dict lookup
2. **Wand charges**: Store in `item.power`, decrement on use, check before casting
3. **Status effects**: Implement as flags + timers, decrement each turn in main loop
4. **Identification**: Two parallel tables, mark on equip/use, show real name if identified
5. **Spell system**: Max 4 spell slots, learned from items, strength penalty on removal
6. **Auto-ID exceptions**: Certain potion/scroll subtypes always identify
7. **Randomized names**: Shuffle at game start, display unidentified name until ID'd
8. **Cast failure**: Roll vs `(player_level // 2 + intelligence)`, may destroy scroll
9. **Food side-effect**: Destroy shield if `current_food > 28` after drinking potion
10. **Heroism**: Trigger when 10+ monsters, make Eye/Huorn flee
