# Memory Address Constants Replacement Summary

## Overview

Replaced **300** raw memory addresses with named constants.

## Files

- **Input**: `reverse/MORIA.C` (original with raw addresses)
- **Output**: `reverse/MORIA_with_constants.C` (with ADDR_* constants)
- **Constants**: `moria_constants.h` (constant definitions)

## Example Improvements

### Before:
```c
if (*(int *)0xb870 /* current_hp */ < *(int *)0xb872 /* max_hp */) {
  *(int *)0xb874 /* current_mana */ = *(int *)0xb874 /* current_mana */ + 1;
}
```

### After:
```c
if (*(int *)ADDR_CURRENT_HP /* current_hp */ < *(int *)ADDR_MAX_HP /* max_hp */) {
  *(int *)ADDR_CURRENT_FOOD /* current_food */ = *(int *)ADDR_CURRENT_FOOD /* current_food */ + 1;
}
```

### Even Better (with moria_globals.h):
```c
if (current_hp < max_hp) {
  current_food = current_food + 1;
}
```

## Major Fixes

### Food System (Previously Mislabeled)
- `0xb874` was labeled `current_mana` → now `ADDR_CURRENT_FOOD`
- `0xb876` was labeled `max_mana` → now `ADDR_MAX_FOOD`

**Moria has NO mana system!** It uses food/satiation instead.

## All Replaced Addresses

| Address | Constant Name | Description |
|---------|---------------|-------------|
| 0xb86c | ADDR_PLAYER_Y                  | Player Y |
| 0xb86e | ADDR_PLAYER_X                  | Player X |
| 0xb870 | ADDR_CURRENT_HP                | Current Hp |
| 0xb872 | ADDR_MAX_HP                    | Max Hp |
| 0xb874 | ADDR_CURRENT_FOOD              | Current Food |
| 0xb876 | ADDR_MAX_FOOD                  | Max Food |
| 0xb878 | ADDR_STRENGTH                  | Strength |
| 0xb87a | ADDR_INTELLIGENCE              | Intelligence |
| 0xb87c | ADDR_WISDOM                    | Wisdom |
| 0xb87e | ADDR_DEXTERITY                 | Dexterity |
| 0xb880 | ADDR_BASE_AC                   | Base Ac |
| 0xb882 | ADDR_CONSTITUTION              | Constitution |
| 0xb886 | ADDR_EXPERIENCE                | Experience |
| 0xb888 | ADDR_PLAYER_LEVEL              | Player Level |
| 0xb892 | ADDR_TURN_COUNT                | Turn Count |
| 0xb8c8 | ADDR_GOLD_LOW                  | Gold Low |
| 0xb8ca | ADDR_GOLD_HIGH                 | Gold High |
| 0xb8ec | ADDR_IS_PARALYZED              | Is Paralyzed |
| 0xb8ed | ADDR_IS_BLIND                  | Is Blind |
| 0xb8ee | ADDR_NEEDS_UPDATE              | Needs Update |
| 0xb8ef | ADDR_SPEED_ACTIVE              | Speed Active |
| 0xb8f0 | ADDR_CONFUSION_LOCK            | Confusion Lock |
| 0xb8f1 | ADDR_STATUS_FLAG_1             | Status Flag 1 |
| 0xb8f2 | ADDR_IS_TELEPORTING            | Is Teleporting |
| 0xb8f3 | ADDR_STATUS_FLAG_3             | Status Flag 3 |
| 0xb8f5 | ADDR_STATUS_FLAG_5             | Status Flag 5 |
| 0xb8f6 | ADDR_IS_WIZARD                 | Is Wizard |
| 0xb8f7 | ADDR_IS_STUNNED                | Is Stunned |
| 0xb8f8 | ADDR_TELEPORT_FLAG             | Teleport Flag |
| 0xb8f9 | ADDR_PARALYZE_TIMER            | Paralyze Timer |
| 0xb8fb | ADDR_BLIND_TIMER               | Blind Timer |
| 0xb8fd | ADDR_DETECT_TIMER              | Detect Timer |
| 0xb8ff | ADDR_SPEED_TIMER               | Speed Timer |
| 0xb901 | ADDR_HALLUC_TIMER              | Halluc Timer |
| 0xb903 | ADDR_STATUS_TIMER_1            | Status Timer 1 |
| 0xb905 | ADDR_TELEPORT_TIMER            | Teleport Timer |
| 0xb907 | ADDR_STATUS_TIMER_3            | Status Timer 3 |
| 0xb909 | ADDR_FOOD_LEVEL                | Food Level |
| 0xb90b | ADDR_STATUS_TIMER_5            | Status Timer 5 |
| 0xb90d | ADDR_WIZARD_TIMER              | Wizard Timer |
| 0xb911 | ADDR_EFFECT_TIMER_16           | Effect Timer 16 |
| 0xb913 | ADDR_HALLUCINATION             | Hallucination |
| 0xb915 | ADDR_IS_DYING                  | Is Dying |
| 0xb916 | ADDR_IS_HASTED                 | Is Hasted |
| 0xb918 | ADDR_HAS_LIGHT                 | Has Light |
| 0xb919 | ADDR_IS_CONFUSED               | Is Confused |
| 0xb91a | ADDR_DEATH_TIMER               | Death Timer |
| 0xb91c | ADDR_HASTE_TIMER               | Haste Timer |
| 0xb91e | ADDR_INVENTORY_LIST            | Inventory List |
| 0xb922 | ADDR_WIELDED_WEAPON            | Wielded Weapon |
| 0xb926 | ADDR_EQUIPPED_SHIELD           | Equipped Shield |
| 0xb92a | ADDR_EQUIPPED_ARMOR            | Equipped Armor |
| 0xb92e | ADDR_EQUIPPED_RING1            | Equipped Ring1 |
| 0xb932 | ADDR_EQUIPPED_RING2            | Equipped Ring2 |
| 0xe52d | ADDR_DUNGEON_LEVEL             | Dungeon Level |
| 0xe535 | ADDR_MIN_VISIBLE_ROW           | Min Visible Row |
| 0xe537 | ADDR_MAX_VISIBLE_ROW           | Max Visible Row |
