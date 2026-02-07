# Function Renaming Guide for MORIA

## Summary

Your reverse-engineered MORIA.C has **191 functions** that need naming.
Based on your execution traces (mapping.json with 4,338 addresses), we can automatically suggest names for **163 functions**.

**26 functions** were never executed and need manual naming.

## Tools Available

### 1. `function_namer.py` - Analysis Tool
Analyzes all functions and generates suggestions based on execution traces.

**Usage:**
```bash
python3 function_namer.py
```

**Output:**
- Console summary of all functions with suggestions
- `function_analysis.json` - detailed JSON with all analysis data

### 2. `apply_renames.py` - Bulk Rename Tool
Automatically renames all functions based on suggestions.

**Usage:**
```bash
# Preview what will be renamed
python3 apply_renames.py --dry-run

# Apply all renames at once
python3 apply_renames.py --apply
```

**Output:**
- Creates `reverse/MORIA_renamed.C` with all functions renamed

**Pros:** Fast, renames everything at once
**Cons:** No control over individual names, some may need manual fixes

### 3. `interactive_renamer.py` - Interactive Tool
Review each function one-by-one and approve/modify/skip names.

**Usage:**
```bash
python3 interactive_renamer.py
```

**Features:**
- Shows function signature and execution contexts
- Accept suggestion, provide custom name, or skip
- Saves progress to `approved_renames.json`
- Can quit anytime and resume later

**Pros:** Full control, see context for each function
**Cons:** Slower, requires manual review of 163 functions

## Execution Context Examples

Your execution traces are in French and describe gameplay actions:

| Context (French) | English | Likely Function Type |
|-----------------|---------|---------------------|
| Monte et attaque chauve souris | Go up and attack bat | Combat/Movement |
| Personnage standard oui | Standard character yes | Character creation |
| Initialization | Initialization | Init/Setup |
| Droite | Right | Movement |
| Manger | Eat | Item/Food action |
| Lire parchemin | Read scroll | Item/Scroll action |

## Functions Without Traces (Need Manual Naming)

These 26 functions were never called during your gameplay sessions:

```
FUN_1000_2138  FUN_1000_53c9  FUN_1000_5422  FUN_1000_62b7
FUN_1000_6431  FUN_1000_65d3  FUN_1000_71a1  FUN_1000_76a4
FUN_1000_772e  FUN_1000_77fe  FUN_1000_7849  FUN_1000_7d66
FUN_1000_7dab  FUN_1000_8d6d  FUN_1000_8e03  FUN_1000_9554
FUN_1000_95ee  FUN_1000_9a91  FUN_1000_9f40  FUN_1000_a85c
FUN_1000_a91f  FUN_1000_aa1d  FUN_1000_b032  FUN_1000_b711
FUN_1000_b821  FUN_1000_b8c7
```

These likely handle rare events, error conditions, or features you didn't use during testing.

## Recommended Workflow

### Option A: Quick and Dirty
1. Run bulk rename: `python3 apply_renames.py --apply`
2. Manually fix any problematic names in `MORIA_renamed.C`
3. Manually name the 26 untraced functions

### Option B: Careful and Thorough
1. Run interactive renamer: `python3 interactive_renamer.py`
2. Review each function with its context
3. Approve good names, provide better names where needed
4. Apply the approved renames
5. Manually name the 26 untraced functions

### Option C: Hybrid
1. Review the analysis: `python3 function_namer.py | less`
2. Identify functions that need special attention
3. Run bulk rename for most functions
4. Manually fix the problematic ones
5. Name the untraced functions

## Tips for Better Names

1. **Keep names descriptive but concise**
   - Bad: `monte_attaque_chauve_souris_tue_chauve_souris`
   - Good: `attack_monster` or `combat_handler`

2. **Use standard naming conventions**
   - Movement: `move_up`, `move_down`, `move_left`, `move_right`
   - Combat: `attack_monster`, `take_damage`, `calculate_hit`
   - UI: `show_menu`, `display_stats`, `draw_screen`
   - Items: `use_item`, `drop_item`, `pickup_item`

3. **Group related functions**
   - If multiple functions handle character creation, name them:
     `char_init`, `char_set_stats`, `char_choose_race`, etc.

4. **Look at the function signature for hints**
   - Functions taking int pointers might be stat modifiers
   - Functions with no params might be UI/display functions
   - Functions returning undefined2 might be boolean checks

## Next Steps

1. Choose your approach (bulk, interactive, or hybrid)
2. Run the appropriate tool
3. Review and refine the output
4. Manually name the 26 untraced functions by:
   - Reading their code in MORIA.C
   - Looking for strings or patterns
   - Checking what other functions call them
   - Tracing them manually if needed

Good luck with the naming!
