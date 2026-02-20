# MORIA DOS 1.9.8.7 — Entity Template Database

Reverse-engineered from `MORIA_with_constants.C` (functions `initialize_monster_or_item` at line 2189,
`spawn_monster_from_template` at line 2534, `randomize_item_appearances` at line 2700, and data loader
at line ~13393) cross-referenced with `memory.dump` (DOS runtime snapshot, CP850 encoding).

---

## Table of Contents

1. [Monster Templates (35 types)](#1-monster-templates-35-types)
2. [Monster Template Structure](#2-monster-template-structure)
3. [Spawning: Template → Live Object](#3-spawning-template--live-object)
4. [Item Type System](#4-item-type-system)
5. [Item Generation Algorithm](#5-item-generation-algorithm)
6. [Potions (Type 2, 24 subtypes)](#6-potions-type-2-24-subtypes)
7. [Scrolls (Type 3, 25 subtypes)](#7-scrolls-type-3-25-subtypes)
8. [Rings (Type 4, 19 subtypes)](#8-rings-type-4-19-subtypes)
9. [Wands (Type 5, 22 subtypes)](#9-wands-type-5-22-subtypes)
10. [Armor & Equipment (Type 6, 11 subtypes)](#10-armor--equipment-type-6-11-subtypes)
11. [Weapons (Type 7, 15 subtypes)](#11-weapons-type-7-15-subtypes)
12. [Light Sources (Type 8, 10 subtypes)](#12-light-sources-type-8-10-subtypes)
13. [Randomized Appearance Tables](#13-randomized-appearance-tables)
14. [Special Flags & Abilities](#14-special-flags--abilities)
15. [Experience Level Thresholds](#15-experience-level-thresholds)

---

## 1. Monster Templates (35 types)

35 monster templates at indices 1–35. Extracted from `memory.dump` using formula
`DS_BASE + ((index * 0x2A - 0x5017) & 0xFFFF)`.

| Idx | Char | Name (French) | English | XP | Hit | HP | AC | Atk | Dmg | Spd | Lvl | Drop | Spec | Flags |
|-----|------|---------------|---------|---:|----:|---:|---:|----:|----:|----:|----:|------|-----:|-------|
| 1 | `a` | Air | Air elemental | 28 | 8 | 50 | 6 | 3 | 4 | 0 | 18 | 0/0 | 13 | INV |
| 2 | `A` | Araignée | Spider | 1 | 1 | 5 | 2 | 1 | 2 | 0 | 12 | 0/0 | 0 | — |
| 3 | `B` | Balrog | Balrog | 40 | 11 | 140 | 9 | 8 | 5 | 60 | 18 | 3/7 | 0 | — |
| 4 | `C` | Chauve Souris | Bat | 1 | 3 | 5 | 4 | 1 | 4 | 0 | 15 | 0/0 | 0 | — |
| 5 | `â` | Crébain | Crebain (crows) | 3 | 5 | 15 | 4 | 3 | 3 | 0 | 17 | 0/0 | 0 | — |
| 6 | `D` | Dragon | Dragon | 25 | 9 | 90 | 9 | 10 | 3 | 0 | 13 | 6/3 | 0 | — |
| 7 | `` | Dragon Ailé | Winged Dragon | 30 | 10 | 100 | 9 | 8 | 4 | 0 | 16 | 10/5 | 0 | — |
| 8 | `E` | oEil | Eye (of Sauron) | 5 | 5 | 10 | 6 | 0 | 0 | 0 | 15 | 20/0 | 0 | HOS |
| 9 | `F` | Fée | Fairy | 20 | 6 | 30 | 6 | 0 | 0 | 0 | 20 | 0/0 | 0 | — |
| 10 | `G` | Galgal | Barrow-wight | 10 | 7 | 30 | 6 | 6 | 2 | 0 | 15 | 15/6 | 0 | — |
| 11 | `g` | Gobelin | Goblin | 3 | 4 | 12 | 3 | 4 | 2 | 0 | 12 | 10/1 | 0 | — |
| 12 | `H` | Huorn | Huorn (tree) | 15 | 8 | 50 | 7 | 10 | 2 | 80 | 18 | 4/2 | 0 | HOS |
| 13 | `L` | Loup | Wolf | 2 | 3 | 10 | 3 | 2 | 3 | 0 | 14 | 0/0 | 0 | — |
| 14 | `` | Loup Garou | Werewolf | 10 | 8 | 40 | 6 | 3 | 4 | 0 | 18 | 0/0 | 0 | — |
| 15 | `M` | Mewlip | Mewlip | 4 | 7 | 20 | 6 | 1 | 5 | 0 | 13 | 10/5 | 0 | — |
| 16 | `æ` | Moricaud | Southron | 6 | 6 | 26 | 5 | 4 | 4 | 0 | 15 | 0/0 | 0 | — |
| 17 | `N` | Nazgûl | Nazgûl | 35 | 10 | 110 | 6 | 6 | 5 | 60 | 18 | 3/6 | 0 | — |
| 18 | `` | Oliphant | Oliphant | 35 | 10 | 120 | 7 | 6 | 6 | 70 | 17 | 4/3 | 0 | — |
| 19 | `O` | Orc | Orc | 5 | 5 | 16 | 4 | 3 | 4 | 0 | 13 | 0/0 | 0 | — |
| 20 | `R` | Rat | Rat | 1 | 5 | 17 | 1 | 1 | 2 | 0 | 15 | 0/0 | 0 | — |
| 21 | `S` | Serpent | Snake | 2 | 2 | 10 | 2 | 1 | 3 | 0 | 12 | 0/0 | 0 | — |
| 22 | `s` | Succube | Succubus | 30 | 11 | 80 | 9 | 5 | 5 | 0 | 16 | 4/2 | 0 | — |
| 23 | `T` | Troll | Troll | 10 | 7 | 50 | 7 | 10 | 2 | 0 | 13 | 7/2 | 0 | — |
| 24 | `U` | Uruk-haï | Uruk-hai | 6 | 6 | 25 | 4 | 3 | 5 | 0 | 15 | 0/0 | 0 | — |
| 25 | `v` | Variag | Variag | 6 | 5 | 23 | 4 | 2 | 8 | 0 | 14 | 0/0 | 0 | — |
| 26 | `V` | Voleur | Thief | 20 | 6 | 30 | 6 | 0 | 0 | 0 | 20 | 0/0 | 0 | — |
| 27 | `W` | Wharg | Warg | 7 | 7 | 30 | 5 | 2 | 7 | 0 | 14 | 0/0 | 0 | — |
| 28 | `w` | Woose | Wose | 15 | 9 | 50 | 4 | 4 | 6 | 0 | 19 | 0/0 | 0 | — |

### Unique / Boss Monsters (stationary — `is_stationary=1`)

| Idx | Char | Name (French) | English | XP | Hit | HP | AC | Atk | Dmg | Spd | Lvl | Spec | Flags |
|-----|------|---------------|---------|---:|----:|---:|---:|----:|----:|----:|----:|-----:|-------|
| 29 | `L` | Carcharoth | Carcharoth (wolf) | 30 | 10 | 120 | 9 | 9 | 3 | 40 | 19 | 0 | STA |
| 30 | `D` | Glaurung | Glaurung (dragon) | 70 | 13 | 150 | 10 | 15 | 3 | 35 | 22 | 0 | STA |
| 31 | `è` | Ungoliant | Ungoliant (spider) | 150 | 15 | 195 | 11 | 10 | 7 | 30 | 27 | 0 | STA |
| 32 | `ä` | Saroumane | Saruman | 50 | 11 | 150 | 7 | 4 | 5 | 0 | 28 | 25 | STA |
| 33 | `X` | Le Guetteur | The Watcher | 190 | 14 | 200 | 12 | 15 | 2 | 0 | 24 | 0 | HOS STA |
| 34 | 0x01 | Sauron | Sauron | 100 | 12 | 180 | 11 | 10 | 6 | 50 | 25 | 20 | STA |
| 35 | `ê` | Morgoth | Morgoth | 200 | 17 | 210 | 12 | 10 | 10 | 40 | 30 | 0 | STA |

**Flag key**: INV = invisible, HOS = hostile (always aggressive), STA = stationary (never moves, unique boss)

### Monster Articles (French grammar)

Two tables provide grammatical articles for monster name display:

**Table 1** (`index * 5 + -0x4985`): indefinite article — "un" (masculine), "une" (feminine), "l'" (elided)
**Table 2** (`index * 5 + -0x4a34`): definite article — "le" (masculine), "la" (feminine), "l'" (elided)

| Idx | Monster | Indef. | Def. | Gender |
|-----|---------|--------|------|--------|
| 1 | Air | l' | l' | M (elided) |
| 2 | Araignée | une | l' | F |
| 3 | Balrog | un | le | M |
| 4 | Chauve Souris | une | la | F |
| 5 | Crébain | un | le | M |
| 6 | Dragon | un | le | M |
| 7 | Dragon Ailé | un | le | M |
| 8 | oEil | un | l' | M (elided) |
| 9 | Fée | une | la | F |
| 22 | Succube | une | la | F |

---

## 2. Monster Template Structure

42 bytes per template (stride 0x2A), base at `index * 0x2A + (-0x5017)`:

| Offset | Size | Field | Copied to Object |
|--------|------|-------|------------------|
| +0x00 | 16B | `name` (Pascal string, CP850) | — (referenced for display) |
| +0x10 | 1B | `attack_char` | obj+0x00 (attack_char), obj+0x01 (visible_char) |
| +0x11 | 2B | `experience_value` | obj+0x06 |
| +0x13 | 2B | `to_hit` | obj+0x08 |
| +0x15 | 2B | `hit_points` | obj+0x0A |
| +0x17 | 2B | `armor_class` | obj+0x0C |
| +0x19 | 2B | `num_attacks` | obj+0x0E |
| +0x1B | 2B | `damage_per_attack` | obj+0x10 |
| +0x1D | 2B | `level` | obj+0x12 |
| +0x1F | 2B | `speed_bonus` | obj+0x14 |
| +0x21 | 2B | `item_drop_chance` | obj+0x16 |
| +0x23 | 2B | `item_drop_type` | obj+0x18 |
| +0x25 | 2B | `special_ability` | obj+0x1A |
| +0x27 | 1B | `is_invisible` | obj+0x27 |
| +0x28 | 1B | `is_hostile` | obj+0x28 |
| +0x29 | 1B | `is_stationary` | obj+0x29 |

Kill count per template: `index * 2 + (-0x460b)` (16-bit counter, incremented on kill).

---

## 3. Spawning: Template → Live Object

**Function**: `spawn_monster_from_template(result_ptr, template_index)` (line 2534)

### Algorithm

1. **Allocate** 54-byte monster object via `allocate_monster_object`
2. **Copy template fields** from template table to live object (see table above)
3. **Set identity**: `template_index` → obj+0x02 and obj+0x04
4. **Place on map**: `find_random_empty_floor_space` sets obj+0x1C (row) and obj+0x1E (col)
5. **Level adjustment**: if `to_hit + speed_bonus < player_level + base_ac + 5`, buff the monster:
   - `to_hit += 1`
   - `speed_bonus = player_level + base_ac + 6 - to_hit`
6. **Initialize state flags**: fleeing=0, visible=0, awake=0, alerted=0, move_toggle=0, stun=0
7. **Item drop roll**: if `item_drop_chance > 0` and `random_mod(item_drop_chance) == 0`:
   - Call `initialize_monster_or_item` to create a carried item (stored at obj+0x2E/0x30)
8. **Eye of Sauron special**: if `attack_char == 'E'`:
   - Set `is_awake = 1`, `status_timer = -1` (0xFFFF = permanent)

### Special Monster: Shapeshift (line 8720)

When special ability 2 triggers on a non-stationary monster:
- Pick random non-stationary template (`random_mod(0x23) + 1`, skip `is_stationary != 0`)
- Replace visible_char, template_index, and combat stats from new template
- The monster visually transforms into a different creature

### Special Monster Spawn (line 2760)

`spawn_special_monster_with_item` creates a unique encounter:
- Spawns template 0x22 (34 = Sauron)
- Then picks random non-stationary template, filtering out 'a' (Air), 'E' (Eye), 'H' (Huorn)
- Overwrites the monster's visible char and backup template
- If no active projectile exists, gives it a wand (type=4, subtype=6, charges=50-100)

---

## 4. Item Type System

**Function**: `initialize_monster_or_item(result_ptr, dungeon_level, item_type)` (line 2189)

The `item_type` parameter (called `flags` in decompilation) selects the item category:

| Type | Name | Display | Weight | Subtypes | Naming |
|------|------|---------|--------|----------|--------|
| 0 | Gold | `$` | — | — | Shows amount |
| 1 | Food | `:` | 2 | — | Fixed name |
| 2 | Potion | `•` | 1 | 24 | Randomized color |
| 3 | Scroll | `?` | 1 | 25 | Random gibberish |
| 4 | Ring | `=` | 1 | 19 | Randomized material |
| 5 | Wand | `/` | 2 | 22 | Randomized wood |
| 6 | Armor | various | 4-7 | 11 | Fixed name |
| 7 | Weapon | various | 2-5 | 15 | Fixed name |
| 8 | Light Source | `*` | 2 | 10 | Fixed name |

**Weight by type** (from `calculate_dice_or_damage`, line 2148):
- Types 2, 3, 4: weight = 1
- Types 1, 5, 8: weight = 2
- Type 6 (armor): subtype 1-6 → `subtype/2 + 4` (range 4-7); subtype 7-11 → 2
- Type 7 (weapon): subtypes 1-2,11-13 → 2; subtypes 3-7,9,14-15 → 4; subtypes 8,10 → 5

---

## 5. Item Generation Algorithm

### Gold (type 0)

```
random_val = random_mod(100) + 1
random_mod(5) + random_val * count * 7 + random_mod(count+1) * 25
→ stored in item.power
```

Gold scales with dungeon level (`count`).

### Potions, Scrolls, Weapons, Armor, Shields, Wands (types 2,3,5,6,7,8)

**Subtype selection** uses weighted probability tables at `type * 0x30 + subtype * 2 + (-0x6513)`:

```c
random_val = random_mod(100) + 1;  // 1-100
accumulator = 0;
subtype = 0;
do {
    subtype++;
    accumulator += weight_table[type][subtype];
} while (accumulator < random_val);
// selected subtype = subtype
```

### Rings (type 4)

Uses separate probability table at `subtype * 2 + (-0x6453)` with same cumulative algorithm.
After subtype selection, special handling per ring subtype (see Ring section).

### Item Power/Charges

Depends on item type and subtype. For cursed items, `power` is negated.
Curses are determined by `find_highest_bit` / `char_create_wrapper` — a random
check that occasionally makes items cursed.

---

## 6. Potions (Type 2, 24 subtypes)

Spawn weights sum to 100. Unidentified potions show randomized color names.

| Sub | Effect (French) | Effect (English) | Wt |
|----:|-----------------|------------------|---:|
| 1 | de guérison | Healing | 9 |
| 2 | d'extra-guérison | Extra-healing | 5 |
| 3 | de constitution | Constitution | 8 |
| 4 | de force | Strength | 4 |
| 5 | de confusion | Confusion | 4 |
| 6 | empoisonnée | Poison | 4 |
| 7 | amnésiante | Amnesia | 2 |
| 8 | paralysante | Paralysis | 5 |
| 9 | accélérante | Speed boost | 6 |
| 10 | ralentissante | Slow | 6 |
| 11 | hallucinogène | Hallucination | 4 |
| 12 | aveuglante | Blindness | 4 |
| 13 | nourrissante | Nourishing | 6 |
| 14 | d'expérience | Experience | 1 |
| 15 | de perte de niveau | Level drain | 2 |
| 16 | d'extralucidité | Clairvoyance | 2 |
| 17 | de désorientation | Disorientation | 3 |
| 18 | passe muraille | Pass-through-walls | 1 |
| 19 | de lévitation | Levitation | 5 |
| 20 | désaltérante | Thirst-quenching | 4 |
| 21 | d'invisibilité | Invisibility | 3 |
| 22 | gazéifiante | Gasification | 2 |
| 23 | de dexterité | Dexterity | 8 |
| 24 | de régénération | Regeneration | 2 |

### 24 Potion Colors (master list, `-0x5e49`)

| # | Color (French) | # | Color (French) |
|--:|----------------|--:|----------------|
| 1 | rouge | 13 | bleue |
| 2 | blanche | 14 | mauve |
| 3 | gludure | 15 | rose |
| 4 | brune | 16 | grise |
| 5 | verte | 17 | jaune |
| 6 | noire | 18 | chinée |
| 7 | fluorescente | 19 | cuivrée |
| 8 | argentee | 20 | moirée |
| 9 | orange | 21 | beige |
| 10 | violette | 22 | dorée |
| 11 | incolore | 23 | multicolore |
| 12 | mordoree | 24 | albatre |

Shuffled at game start to randomized table (`-0x5cc9`).
Displayed as: "potion *[color]*" until identified.

---

## 7. Scrolls (Type 3, 25 subtypes)

Scroll names are **procedurally generated** random character strings (function
`generate_random_names` at line 2633), 4-9 characters of gibberish per scroll.

| Sub | Effect (French) | Effect (English) | Wt |
|----:|-----------------|------------------|---:|
| 0 | de régénération | Regeneration | 2 |
| 1 | pour enchanter les armures | Enchant armor | 5 |
| 2 | pour protéger les armures | Protect armor | 2 |
| 3 | pour enchanter son arme | Enchant weapon | 5 |
| 4 | topographique | Map reveal | 8 |
| 5 | d'identification | Identify | 21 |
| 6 | de teleportation | Teleport | 4 |
| 7 | d'hyper téléportation | Hyper-teleport | 2 |
| 8 | pour invoquer un monstre | Summon monster | 3 |
| 9 | de protection | Protection | 3 |
| 10 | pour détecter la magie | Detect magic | 5 |
| 11 | pour détecter la nouriture | Detect food | 5 |
| 12 | pour repérer les monstres | Detect monsters | 3 |
| 13 | pour détecter l'or | Detect gold | 5 |
| 14 | d'ensorcellement | Enchantment | 2 |
| 15 | de sommeil | Sleep | 5 |
| 16 | vierge | Blank | 4 |
| 17 | pour enlever les sorts | Remove curses | 5 |
| 18 | de démolition | Demolition | 2 |
| 19 | de destruction | Destruction | 1 |
| 20 | pour effrayer les monstres | Scare monsters | 3 |
| 21 | d'éparpillement | Scatter | 1 |
| 22 | pour enchanter les anneaux | Enchant rings | 1 |
| 23 | de dégradation d'anneaux | Degrade rings | 2 |
| 24 | d'intelligence | Intelligence | 3 |

Total weight: 102 (subtypes 0 and 24 have slight extra chance of being skipped).

---

## 8. Rings (Type 4, 19 subtypes)

Subtype selection uses dedicated table at `-0x6453` (same data as type 4 row at `-0x6513`).

| Sub | Effect (French) | Effect (English) | Wt | Power |
|----:|-----------------|------------------|---:|-------|
| 0 | d'intelligence | Intelligence | 3 | — |
| 1 | pour protéger son armure | Protect armor | 4 | — |
| 2 | pour conserver sa force | Sustain strength | 9 | — |
| 3 | pour ralentir sa digestion | Slow digestion | 8 | — |
| 4 | d'augmentation des dégats | Damage boost | 8 | `(level+2)/5 + random(2)`, can be cursed |
| 5 | de téléportation | Teleportation | 8 | — |
| 6 | d'invisibilité | Invisibility | 1 | — |
| 7 | de protection | Protection | 8 | `(level+3)/6 + random(2)`, can be cursed |
| 8 | d'identification | Identification | 3 | power = 1 (always) |
| 9 | de régénération | Regeneration | 6 | `(level+3)/6 + random(2)`, can be cursed |
| 10 | de détection de trappes | Trap detection | 5 | `random(4) + 4` |
| 11 | de monstres | Monster detect | 7 | cursed: -1; normal: +1 |
| 12 | coupe doigt | Finger-cutter | 4 | — |
| 13 | anti feu | Fire resist | 9 | — |
| 14 | de chute de plume | Feather fall | 5 | — |
| 15 | de résurrection | Resurrection | 1 | power = 1 |
| 16 | de nage | Swimming | 4 | — |
| 17 | de rayon X | X-ray vision | 4 | — |
| 18 | de lévitation | Levitation | 4 | `random(4) + 4` |
| 19 | de faiblesse | Weakness | 2 | — |

Total weight: 101.

### 19 Ring Materials (master list, `-0x5b49`)

| # | Material | # | Material |
|--:|----------|--:|----------|
| 1 | d'or | 11 | d'émeraude |
| 2 | d'argent | 12 | de bronze |
| 3 | de platine | 13 | de jade |
| 4 | de jaspe | 14 | de mithril |
| 5 | de rubis | 15 | d'os |
| 6 | de saphir | 16 | d'adamantite |
| 7 | d'onyx | 17 | d'agathe |
| 8 | d'opale | 18 | de cristal |
| 9 | d'ivoire | 19 | d'étain |
| 10 | de diamant | | |

Shuffled at game start. Displayed as: "anneau *[material]*" until identified.

---

## 9. Wands (Type 5, 22 subtypes)

| Sub | Effect (French) | Effect (English) | Wt |
|----:|-----------------|------------------|---:|
| 1 | de téléportation | Teleportation | 6 |
| 2 | de transmorphie | Polymorph | 3 |
| 3 | de destruction | Destruction | 8 |
| 4 | pour créer des murs | Create walls | 6 |
| 5 | de ralentissement de monstre | Slow monster | 8 |
| 6 | d'accélération de monstre | Haste monster | 5 |
| 7 | d'affaiblissement | Weakening | 5 |
| 8 | pour effrayer | Fear | 7 |
| 9 | de sourcier | Dowsing (detect) | 4 |
| 10 | d'invocation de monstre | Summon monster | 5 |
| 11 | d'invocation d'objet | Summon item | 2 |
| 12 | de combat | Combat | 7 |
| 13 | pour combler les trappes | Fill traps | 4 |
| 14 | assoupissante | Sleep | 5 |
| 15 | paralysante | Paralyze | 5 |
| 16 | d'invisibilité | Invisibility | 4 |
| 17 | de création de trappes | Create traps | 4 |
| 18 | de renforcement | Strengthening | 3 |
| 19 | capricieuse | Capricious | 2 |
| 20 | d'illusion | Illusion | 2 |
| 21 | de purification | Purification | 4 |
| 22 | d'absorption d'énergie | Energy drain | 1 |

Total weight: 100.

**Wand charges** (power): calculated from dungeon level.

### 22 Wand Woods (master list, `-0x58e9`)

| # | Wood (French) | # | Wood (French) |
|--:|---------------|--:|---------------|
| 1 | de chêne (oak) | 12 | de pin (pine) |
| 2 | de peuplier (poplar) | 13 | d'olivier (olive) |
| 3 | de teck (teak) | 14 | d'érable (maple) |
| 4 | de saule (willow) | 15 | de platane (sycamore) |
| 5 | de merisier (cherry) | 16 | d'if (yew) |
| 6 | de châtaigner (chestnut) | 17 | de hêtre (beech) |
| 7 | de frêne (ash) | 18 | d'orme (elm) |
| 8 | de noisetier (hazel) | 19 | de bambou (bamboo) |
| 9 | de charme (hornbeam) | 20 | de verre (glass) |
| 10 | de cerisier (cherry tree) | 21 | de rose noire (black rose) |
| 11 | d'acajou (mahogany) | 22 | de roseau (reed) |

Shuffled at game start (22 shuffled, 21 copied). Displayed as: "baguette *[wood]*" until identified.

---

## 10. Armor & Equipment (Type 6, 11 subtypes)

Armor names are fixed (not randomized). No identification needed.

| Sub | Name (French) | Name (English) | Wt | Weight |
|----:|---------------|----------------|---:|-------:|
| 1 | une armure de cuir | Leather armor | 22 | 4 |
| 2 | une armure de cuir renforcé | Studded leather | 22 | 4 |
| 3 | une cotte de mailles | Chainmail | 18 | 5 |
| 4 | une armure de fer | Iron armor | 12 | 5 |
| 5 | une cuirasse d'acier | Steel breastplate | 4 | 6 |
| 6 | une armure de Mithril | Mithril armor | 1 | 6 |
| 7 | un heaume | Helm | 8 | 2 |
| 8 | une cape elfique | Elven cloak | 4 | 2 |
| 9 | des gantelets de dextérité | Gauntlets of dexterity | 3 | 2 |
| 10 | des gantelets de maladresse | Gauntlets of clumsiness | 3 | 2 |
| 11 | des gantelets de force | Gauntlets of strength | 3 | 2 |

Total weight: 100.

**Power**: for armor (subtypes 1-6), `power = level/5 + random(3)`, can be cursed.
Equipment subtypes 7-11 have fixed or zero power.

---

## 11. Weapons (Type 7, 15 subtypes)

Weapon names are fixed. No identification needed.

| Sub | Name (French) | Name (English) | Wt | Base Atk | Weight |
|----:|---------------|----------------|---:|:--------:|-------:|
| 1 | un poignard | Dagger | 9 | 1 | 2 |
| 2 | une dague | Stiletto | 9 | 1 | 2 |
| 3 | une lance | Spear | 14 | 2 | 4 |
| 4 | une massue | Mace | 13 | 3 | 4 |
| 5 | un sabre | Saber | 10 | 4 | 4 |
| 6 | un cimeterre | Scimitar | 6 | 5 | 4 |
| 7 | une épée | Sword | 4 | 5 | 4 |
| 8 | une épée à deux mains | Two-handed sword | 3 | 6 | 5 |
| 9 | une épée elfique | Elven sword | 1 | 7 | 4 |
| 10 | une hache | Axe | 4 | 6 | 5 |
| 11 | un arc | Bow | 8 | 1 | 2 |
| 12 | fleche | Arrow | 15 | 0 | 2 |
| 13 | une dague elfique | Elven dagger | 2 | 4 | 2 |
| 14 | une épée de glace | Ice sword | 1 | 5 | 4 |
| 15 | une épée vampirique | Vampiric sword | 1 | 5 | 4 |

Total weight: 100.

**Base attack table** (`subtype * 4 + -0x6185`): weapon's inherent attack bonus (0-7).
Player's total attack = `weapon_base[subtype] + item.power` (capped at 10-13).

**Weapon power**: `power = level/5 + random(3)`, can be cursed.

Special weapons:
- **Subtype 12 (arrows)**: quantity-based (`power = level/5 + random(15) + 10`)
- **Subtype 15 (vampiric sword)**: special flag, appears rarely (1/20 chance of replacing subtype 7)

---

## 12. Light Sources (Type 8, 10 subtypes)

| Sub | Effect (French) | Effect (English) | Wt |
|----:|-----------------|------------------|---:|
| 1 | de chance | Luck | 6 |
| 2 | de dessèchement | Desiccation | 20 |
| 3 | de monstres | Monster detect | 6 |
| 4 | d'annulation | Cancellation | 10 |
| 5 | de faim | Hunger | 20 |
| 6 | de force | Strength | 14 |
| 7 | de régénération | Regeneration | 4 |
| 8 | de vulnérabilité | Vulnerability | 14 |
| 9 | d'antimagie | Antimagic | 5 |
| 10 | d'expérience | Experience | 1 |

Total weight: 100.

**Light source special handling** (type 8):
- Subtype 4 (cancellation): `power = random(15) + 10`
- All light sources have a gold value generated by repeated random additions:
  `value += 60 + random(200)` in a loop, with rare multipliers (1/10, 1/20, 1/50, 1/100, 1/500 chances)
- `unique_id = random(10) + 1` for identification
- Always flagged as cursed-ish (`byte[0x14] = 1`)

---

## 13. Randomized Appearance Tables

**Function**: `randomize_item_appearances` (line 2700)

At game start, four item types get shuffled appearance names:

| Item Type | Master Table | Randomized Table | Count | Entry Size |
|-----------|-------------|-----------------|------:|-----------|
| Potion colors | `-0x5e49` | `-0x5cc9` | 24 | 16B Pascal |
| Ring materials | `-0x5b49` | `-0x5a19` | 19 | 16B Pascal |
| Wand woods | `-0x58e9` | `-0x5789` | 22→21 | 16B Pascal |
| Gem names | `-0x5629` | `-0x5589` | 10 | 16B Pascal |

### 10 Gem Names (master list, `-0x5629`)

| # | Gem | # | Gem |
|--:|-----|--:|-----|
| 1 | un rubis | 6 | une agathe |
| 2 | une émeraude | 7 | une améthyste |
| 3 | un diamant | 8 | un chrysobéryl |
| 4 | un topaze | 9 | une turquoise |
| 5 | un saphir | 10 | une opale |

### Identification System

Two tables track item identification per game session:

| Table | Address | Formula | Purpose |
|-------|---------|---------|---------|
| Identified | `-0x65a2` | `type * 0x18 + subtype` | Byte flag: 0=unknown, nonzero=identified |
| Alt check | `-0x6542` | `type * 0x18 + subtype` | Secondary identification flag |

When an item is identified (via scroll, ring, or equipping), the corresponding
byte is set to nonzero, and all future items of that subtype show their real name.

### Item Description Tables

Two parallel string tables provide item descriptions:

| Table | Base | Formula | Purpose |
|-------|------|---------|---------|
| Identified effect | `0x75fa` | `type * 0x2B8 + subtype * 0x1D + 0x75FA` | Shows real effect name |
| Unidentified desc | `-0x75de` | `type * 0x2B8 + subtype * 0x1D + (-0x75DE)` | Shows "Bug!" placeholder |

- 0x2B8 = 696 bytes per type (24 slots × 29 bytes)
- 0x1D = 29 bytes per entry (Pascal string, max 28 chars)

---

## 14. Special Flags & Abilities

### Monster Special Abilities

The `special_ability` field (template offset +0x25) controls wand effect abilities.
When `special > 0`, the monster can use a wand-like ability with `random_mod(special) == 0` chance.

Notable values:
- Saroumane (32): `special = 25` → 1/25 chance per turn of casting
- Sauron (34): `special = 20` → 1/20 chance
- Morgoth (35): `special = 15` → 1/15 chance (most frequent caster)
- Air (1): `special = 13` → 1/13 chance

### Monster Character Codes

Some monsters use extended CP437/CP850 characters:

| Monster | Hex | CP437 | Notes |
|---------|-----|-------|-------|
| Crébain | 0x83 | â | CP850 accented char |
| Dragon Ailé | 0x15 | § | Control char region |
| Loup Garou | 0x14 | ¶ | Control char region |
| Moricaud | 0x91 | æ | CP850 |
| Oliphant | 0x12 | ↕ | Control char |
| Ungoliant | 0x8A | è | CP850 |
| Saroumane | 0x84 | ä | CP850 |
| Sauron | 0x01 | ☺ | Smiley face! |
| Morgoth | 0x88 | ê | CP850 |

### Item Curse System

Items can be cursed during generation. The algorithm:
1. Call `find_highest_bit()` — sets up random check
2. Call `char_create_wrapper()` — returns boolean
3. If curse triggers: `power = -power` (negative bonus)
4. Item's `is_cursed` flag (offset +0x14) set to 1

Affected item types:
- Rings (subtypes 4, 7, 9, 11): power can be negative
- Armor (type 6): defense bonus can be negative
- Weapons (type 7): attack bonus can be negative

### Active Projectile System

Address `0xABAF/0xABB1` tracks a special active item (typically the first food/gold
item created via type 6, subtype 6 — "the One Ring" placeholder). When non-null,
prevents duplicate creation of this unique item.

---

## 15. Experience Level Thresholds

Player levels up when XP reaches these thresholds (`level * 2 + -0x46b8`):

| Level | XP Needed | Level | XP Needed |
|------:|----------:|------:|----------:|
| 1 | 10 | 8 | 1,280 |
| 2 | 20 | 9 | 2,200 |
| 3 | 40 | 10 | 3,700 |
| 4 | 80 | 11 | 6,000 |
| 5 | 160 | 12 | 9,000 |
| 6 | 320 | 13 | 14,000 |
| 7 | 640 | 14 | 810* |

*Level 14 threshold (810) appears to be a data anomaly or wrap-around in the dump.

XP formula doubles each level through 8, then scales more gradually.
Player `ADDR_PLAYER_LEVEL` is initialized to 0x80 (128) and decremented on level-up.

---

## Summary

- **35 monster templates**: 28 normal + 7 unique/boss, indices 1-35
- **8 item types** (0-8): gold, food, potion, scroll, ring, wand, armor, weapon, light source
- **~150 item subtypes** total across all types
- **4 randomized name tables**: 24 colors, 19 materials, 22 woods, 10 gems
- **Template stride**: 0x2A (42 bytes) for monsters, 0x1A (26 bytes) for items
- **Key functions**: `initialize_monster_or_item` (item factory), `spawn_monster_from_template` (monster factory), `randomize_item_appearances` (name shuffler)
