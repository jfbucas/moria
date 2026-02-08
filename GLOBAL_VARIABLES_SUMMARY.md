# Global Variables Replacement Summary

## Statistics
- Total memory address replacements: 862
- Global variables defined: 54

## Key Improvements

### 1. Fixed Food/Satiation System
The game does NOT have a mana system! Addresses 0xb874 and 0xb876 were incorrectly
labeled as "current_mana" and "max_mana" but are actually the food/satiation system.

**Before:**
```c
*(int *)0xb874 /* current_mana */ = *(int *)0xb874 /* current_mana */ + 1;
if (*(int *)0xb874 /* current_mana */ < 0) {
  process_game_over(&param_1, unaff_SS, 0x65);  // Die from starvation!
}
```

**After:**
```c
current_food = current_food + 1;
if (current_food < 0) {
  process_game_over(&param_1, unaff_SS, 0x65);  // Die from starvation!
}
```

### 2. Documented All Potion Effect Timers
All previously undocumented timer addresses from drink_potion_effect are now mapped:

- 0xb8ef → speed_boost_active
- 0xb8ff → speed_timer
- 0xb8f9 → paralyze_timer
- 0xb8fb → blind_timer
- 0xb8fd → detect_timer
- 0xb901 → hallucination_timer
- 0xb903 → status_timer_1
- 0xb905 → teleport_timer
- 0xb907 → status_timer_3
- 0xb909 → food_level
- 0xb90b → status_timer_5
- 0xb90d → wizard_mode_timer
- 0xb911 → effect_timer_16
- 0xb913 → hallucination_active

### 3. Clean Global Variable Access
Instead of memory address dereferencing with comments, use clean variable names.

**Before:**
```c
if (*(char *)0xb916 /* is_hasted */ == '\0') {
  *(undefined1 *)0xb916 /* is_hasted */ = 1;
  *(int *)0xb91c /* haste_timer */ = iVar4 + 0x1e;
}
```

**After:**
```c
if (is_hasted == '\0') {
  is_hasted = 1;
  haste_timer = iVar4 + 0x1e;
}
```

## Files Generated

1. **moria_constants.h** (updated)
   - Fixed ADDR_CURRENT_MANA → ADDR_CURRENT_FOOD
   - Fixed ADDR_MAX_MANA → ADDR_MAX_FOOD
   - Added all potion effect timer addresses
   - Updated potion effect enum with correct names

2. **moria_globals.h** (new)
   - Defines all 54 global variable macros
   - Clean variable names for all game state
   - Properly typed (int, char, void*, etc.)

3. **MORIA_with_globals.C** (new)
   - All memory address dereferencing replaced with variables
   - 862 replacements applied
   - Includes both headers
   - Most readable version yet!

## Usage

To compile (after porting to modern C):
```c
#include "moria_constants.h"
#include "moria_globals.h"

// Now you can use:
if (current_hp < max_hp) {
  current_hp += player_level;
}

if (is_hasted) {
  haste_timer--;
}

if (current_food < 0) {
  // Player starves!
}
```

## Next Steps (Optional)

1. Define proper structures for Monster, Item, etc.
2. Replace remaining magic addresses (0xb924, 0xb928, etc.)
3. Port to modern C with flat memory model
4. Remove DOS/BIOS dependencies

---

Generated: 2026-02-08
Total improvements applied: 862 replacements across 54 variables
