# Deep Analysis: `generate_dungeon_corridors()` Function

## Overview

`generate_dungeon_corridors()` is a **maze generation algorithm** that uses **Randomized Kruskal's Minimum Spanning Tree (MST)** with a **Union-Find (Disjoint Set)** data structure to create dungeon corridors connecting rooms.

This is a **single iteration** of the corridor generation process, called repeatedly by `draw_dungeon_border()` until the entire dungeon is connected.

---

## Function Signature

```c
void generate_dungeon_corridors(int value)
```

**Parameter:**
- `value` (int): Stack pointer / frame pointer for accessing local variables and dungeon state

**Returns:** void

---

## Algorithm Type: Randomized Kruskal's MST

The function implements a classic **maze generation algorithm**:

1. **Start**: Each room is its own isolated region
2. **Iterate**: Randomly select potential corridors (edges)
3. **Check**: If corridor connects two different regions, add it
4. **Union**: Merge the two regions into one
5. **Repeat**: Until all rooms are connected (forming a spanning tree)

This creates a **perfect maze** (no loops initially), with some extra corridors added to create alternative paths.

---

## Dungeon Grid Structure

### Room Layout

The dungeon is conceptually a **10 × 39 grid** of rooms:

```
         Columns (1-39)
      ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐
   1  │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
      ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
   2  │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
R     ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
o  3  │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
w     ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
s     │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
      ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
(     │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
1  ...│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
-     ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
1     │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
0     ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
)  10 │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
      └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘

Total rooms: 10 rows × 39 columns = 390 rooms
```

### Corridor Types

**Two types of corridors connect adjacent rooms:**

#### 1. Vertical Corridors (391 total)

Connect rooms **vertically** (from row N to row N+1 in the same column):

```
Position = 1 to 391

Formula to convert position to (row, col):
  row = (position - 1) / 39 + 1
  col = (position - 1) % 39 + 1

Example:
  ┌─────┐
  │ R   │  Room at (row=5, col=12)
  └─────┘
     ║      ← Vertical corridor
  ┌─────┐
  │ R   │  Room at (row=6, col=12)
  └─────┘

Map coordinates:
  Y = row * 2 + 1
  X = col * 2
```

#### 2. Horizontal Corridors (417 total)

Connect rooms **horizontally** (from column N to column N+1 in the same row):

```
Position = 392 to 808

Formula to convert position to (row, col):
  adjusted_pos = position - 390
  row = (adjusted_pos - 1) / 11 + 1
  col = (adjusted_pos - 1) % 11 + 1

Example:
  ┌─────┐     ┌─────┐
  │ R   │═════│ R   │  Row 3, Cols 5-6
  └─────┘  ↑  └─────┘
           │
    Horizontal corridor

Map coordinates:
  Y = col * 158  (MAP_WIDTH = 158 bytes)
  X = row * 2 + 1
```

---

## Code Flow Diagram

```
┌──────────────────────────────────────────────────────────────────┐
│ generate_dungeon_corridors(value)                                │
└──────────────────────────────────────────────────────────────────┘
                          │
                          ▼
           ┌───────────────────────────────┐
           │ random_val = random_mod(808)  │
           │ position = random_val + 1     │
           │ (Select random corridor 1-808)│
           └───────────────────────────────┘
                          │
                          ▼
                  ┌───────────────┐
                  │ position < 391│
                  │  (0x187)?     │
                  └───────────────┘
                    │           │
              Yes   │           │  No
       (Vertical)   │           │  (Horizontal)
                    │           │
        ┌───────────▼─────┐     │
        │ Vertical Corridor│     │
        │                  │     │
        │ row = (pos-1)/39+1│    │
        │ col = (pos-1)%39+1│    │
        │                  │     │
        │ Map position:    │     │
        │ Y = row*2 + 1    │     │
        │ X = col*2        │     │
        └───────────┬──────┘     │
                    │            │
                    │    ┌───────▼──────────┐
                    │    │Horizontal Corridor│
                    │    │                   │
                    │    │adj = pos - 390    │
                    │    │row = (adj-1)/11+1 │
                    │    │col = (adj-1)%11+1 │
                    │    │                   │
                    │    │Map position:      │
                    │    │Y = col*158        │
                    │    │X = row*2 + 1      │
                    │    └───────┬───────────┘
                    │            │
                    └────┬───────┘
                         │
                         ▼
           ┌──────────────────────────────┐
           │ Check if corridor position   │
           │ is already occupied          │
           │ (read byte from map)         │
           └──────────────────────────────┘
                         │
                 ┌───────┴────────┐
                 │                │
              Empty             Occupied
            (proceed)           (skip)
                 │                │
                 ▼                │
    ┌─────────────────────────┐   │
    │ Calculate room indices: │   │
    │                         │   │
    │ room1 = position        │   │
    │ room2 = position + Δ    │   │
    │                         │   │
    │ Δ = 39 (vertical)       │   │
    │ Δ = 1  (horizontal)     │   │
    └─────────────────────────┘   │
                 │                │
                 ▼                │
    ┌──────────────────────────┐  │
    │ Union-Find Check:        │  │
    │                          │  │
    │ region1 =                │  │
    │   find_dungeon_region(   │  │
    │       value, room1)      │  │
    │                          │  │
    │ region2 =                │  │
    │   find_dungeon_region(   │  │
    │       value, room2)      │  │
    └──────────────────────────┘  │
                 │                │
                 ▼                │
    ┌────────────────────────────┐│
    │ Decision:                  ││
    │                            ││
    │ if (region1 != region2) OR ││
    │    (first corridor) :      ││
    └────────────────────────────┘│
          │            │          │
        Yes           No          │
          │            │          │
          ▼            └──────────┘
┌─────────────────────┐
│ PLACE CORRIDOR:     │
│                     │
│ 1. Write 0x20 (' ') │
│    at map position  │
│                     │
│ 2. corridor_count++ │
│                     │
│ 3. Union regions:   │
│    parent[region2]  │
│       = region1     │
└─────────────────────┘
          │
          ▼
       RETURN
```

---

## Detailed Code Analysis

### Part 1: Random Corridor Selection

```c
random_val = random_mod(0x328);  // 0x328 = 808 decimal
*(int *)(value + -2) = random_val + 1;
```

**Purpose**: Randomly select one of 808 possible corridor positions (numbered 1-808).

### Part 2A: Vertical Corridor (Positions 1-391)

```c
if (*(int *)(value + -2) < 0x187) {  // 0x187 = 391
    // Calculate room grid position
    *(int *)(value + -8) = (*(int *)(value + -2) + -1) / 0x27 + 1;  // row
    *(int *)(value + -6) = (*(int *)(value + -2) + -1) % 0x27 + 1;  // col

    // 0x27 = 39 (number of columns)
    // row = (position - 1) / 39 + 1
    // col = (position - 1) % 39 + 1

    // Calculate memory address
    random_val = (*(int *)(value + -8) * 2 + 1) * MAP_WIDTH;
    uVar1 = *(undefined4 *)(*(int *)(value + 4) * 4 + 4);
    flag = (int)uVar1 + random_val + *(int *)(value + -6) * 2;

    // flag now points to the map cell at:
    //   Y = row * 2 + 1
    //   X = col * 2

    // Read the current cell value
    uVar3 = CONCAT11((char)((uint)random_val >> 8),
                     *(undefined1 *)(flag + -0x50));

    // Check if cell is occupied
    if (!(bool)uVar6) {
        // Calculate connected room indices
        *(undefined2 *)(value + -0x10) = *(undefined2 *)(value + -2);  // room1
        *(int *)(value + -0xe) = *(int *)(value + -0x10) + 0x27;       // room2

        // room2 = room1 + 39 (connects to room below)

        // Find which region each room belongs to
        uVar4 = find_dungeon_region(value, *(undefined2 *)(value + -0x10));
        *(undefined2 *)(value + -0xc) = uVar4;  // region1

        uVar4 = find_dungeon_region(value, *(undefined2 *)(value + -0xe));
        *(undefined2 *)(value + -10) = uVar4;   // region2

        // Union decision
        if ((*(int *)(value + -0xc) != *(int *)(value + -10)) ||
            (*(char *)(value + -0x36b) == '\0')) {  // first corridor flag

            // PLACE THE CORRIDOR
            uVar1 = *(undefined4 *)(*(int *)(value + 4) * 4 + 4);
            *(undefined1 *)((int)uVar1 +
                (*(int *)(value + -8) * 2 + 1) * MAP_WIDTH +
                *(int *)(value + -6) * 2 + -0x50) = 0x20;  // ' ' space

            // Increment corridor count
            *(int *)(value + -4) = *(int *)(value + -4) + 1;

            // UNION THE REGIONS
            if (*(int *)(value + -0xc) < *(int *)(value + -10)) {
                *(undefined2 *)(value + *(int *)(value + -10) * 2 + -0x36c) =
                    *(undefined2 *)(value + -0xc);
            }
            else {
                *(undefined2 *)(value + *(int *)(value + -0xc) * 2 + -0x36c) =
                    *(undefined2 *)(value + -10);
            }
        }
    }
}
```

### Part 2B: Horizontal Corridor (Positions 392-808)

```c
else {
    // Adjust position: subtract 390 (0x186)
    *(int *)(value + -2) = *(int *)(value + -2) + -0x186;

    // Calculate grid position
    *(int *)(value + -8) = (*(int *)(value + -2) + -1) / 0xb + 1;  // row
    *(int *)(value + -6) = (*(int *)(value + -2) + -1) % 0xb + 1;  // col

    // 0xb = 11 (different grid dimension for horizontal corridors)
    // row = (adj_position - 1) / 11 + 1
    // col = (adj_position - 1) % 11 + 1

    // Calculate memory address
    random_val = *(int *)(value + -6) * 0x9e;  // 0x9e = 158 = MAP_WIDTH
    uVar1 = *(undefined4 *)(*(int *)(value + 4) * 4 + 4);
    flag = (int)uVar1 + random_val + *(int *)(value + -8) * 2 + 1;

    // flag now points to the map cell at:
    //   Y = col * 158  (one full row per column)
    //   X = row * 2 + 1

    // Rest of logic similar to vertical corridors
    // but connects room1 to room1 + 1 (horizontal connection)

    *(int *)(value + -0x10) = (*(int *)(value + -6) + -1) * 0x27 +
                              *(int *)(value + -8);  // room1
    *(int *)(value + -0xe) = *(int *)(value + -0x10) + 1;  // room2

    // (same union-find logic follows...)
}
```

---

## Helper Function: `find_dungeon_region()`

This implements the **Union-Find** data structure with **path compression**:

```c
int find_dungeon_region(int value, int count)
{
  int value;
  undefined2 unaff_SS;
  undefined2 local_8;

  local_8 = count;

  // Traverse parent pointers until we find the root
  while (*(int *)(value + local_8 * 2 + -0x36c) != local_8) {
    value = *(int *)(value + local_8 * 2 + -0x36c);

    // PATH COMPRESSION: Make each node point directly to root
    *(undefined2 *)(value + local_8 * 2 + -0x36c) =
        *(undefined2 *)(value + value * 2 + -0x36c);

    local_8 = value;
  }

  return local_8;  // Return root of tree
}
```

**How it works:**

```
Initial state (all rooms are separate regions):
  parent[1] = 1
  parent[2] = 2
  parent[3] = 3
  ...

After connecting rooms 1-2:
  parent[1] = 1  (root)
  parent[2] = 1  (points to 1)

After connecting rooms 2-3:
  parent[1] = 1  (root)
  parent[2] = 1
  parent[3] = 1  (points to 1)

Path compression during find:
  Before: 5 → 4 → 3 → 1 (root)
  After:  5 → 1, 4 → 1, 3 → 1 (all point to root)
```

**Why path compression?**
- Makes future lookups O(1) instead of O(n)
- Flattens the tree structure
- Critical for performance when called thousands of times

---

## Memory Layout

### Map Memory Structure

```
DOS Text Mode Memory:
  Each cell = 2 bytes (character + attribute)
  MAP_WIDTH = 158 = 79 * 2

Map dimensions:
  Width:  79 characters (0-78)
  Height: ~22 rows (typical DOS screen)

Row storage:
  Row 0: bytes 0-157
  Row 1: bytes 158-315
  Row 2: bytes 316-473
  ...
```

### Stack Variables

```
Offset from 'value' parameter:
  value + -2   : Random position (1-808)
  value + -4   : Corridor counter
  value + -6   : Column coordinate
  value + -8   : Row coordinate
  value + -0xc : Region ID of room1
  value + -10  : Region ID of room2
  value + -0xe : Room2 index
  value + -0x10: Room1 index
  value + -0x36b: First corridor flag
  value + -0x36c + (room_index * 2): Parent pointer array
```

---

## Character Constants

```c
0x20 = ' '  (space)     - Walkable corridor floor
0xb3 = '│'  (box vert)  - Vertical wall/border
0xc4 = '─'  (box horiz) - Horizontal wall/border
0xc5 = '┼'  (box cross) - Intersection/cross
0xef = '⌠'  (stairs)    - Stairs up/down
```

---

## Example Execution

Let's trace one iteration:

### Initial State

```
All rooms disconnected:
  parent[1..390] = [1, 2, 3, ..., 390]

Corridor count = 0
Map is filled with walls
```

### Iteration 1

```
1. random_mod(808) returns 145
2. position = 146 (vertical corridor)
3. row = (146-1) / 39 + 1 = 145/39 + 1 = 4
   col = (146-1) % 39 + 1 = 145%39 + 1 = 29
4. This corridor connects:
   - room1 = 146 (row 4, col 29)
   - room2 = 185 (row 5, col 29)
5. find_dungeon_region(146) = 146 (self)
   find_dungeon_region(185) = 185 (self)
6. Regions are different!
7. Place corridor at map position:
   Y = 4*2+1 = 9
   X = 29*2 = 58
   map[9][58] = ' '
8. Union: parent[185] = 146
9. corridor_count = 1
```

### Iteration 2

```
1. random_mod(808) returns 500
2. position = 501 (horizontal corridor)
3. adj = 501 - 390 = 111
   row = (111-1) / 11 + 1 = 11
   col = (111-1) % 11 + 1 = 1
4. This corridor connects:
   - room1 = (1-1)*39 + 11 = 11
   - room2 = 12
5. find_dungeon_region(11) = 11
   find_dungeon_region(12) = 12
6. Different regions, place corridor!
7. Union: parent[12] = 11
8. corridor_count = 2
```

### After Many Iterations

```
Eventually all 390 rooms are connected in one spanning tree.
The algorithm continues to add extra corridors for loops.
```

---

## Visual Example of Generated Maze

```
Initial Grid (no corridors):
┌─┬─┬─┬─┬─┐
│ │ │ │ │ │  Rooms are isolated
├─┼─┼─┼─┼─┤
│ │ │ │ │ │
├─┼─┼─┼─┼─┤
│ │ │ │ │ │
└─┴─┴─┴─┴─┘

After Corridor Generation:
┌─┬─┬─┬─┬─┐
│ ║ │ │ ═ │  ║ = vertical corridor
├─╬─┼─┼─╬─┤  ═ = horizontal corridor
│ ║ │ │ ═ │  ╬ = intersection
├─╬─┼─┼─╬─┤
│ ║ │ │ ═ │
└─┴─┴─┴─┴─┘

All rooms now connected via corridors!
```

---

## Why This Algorithm?

### Advantages of Randomized Kruskal + Union-Find

1. **Guarantees connectivity**: Every room is reachable
2. **Creates natural maze**: Winding paths, not straight lines
3. **Efficient**: O(E α(V)) where α is inverse Ackermann (nearly constant)
4. **Simple**: Easy to implement in C with arrays
5. **Reproducible**: Same random seed = same dungeon

### Compared to Other Maze Algorithms

| Algorithm | Speed | Memory | Quality |
|-----------|-------|--------|---------|
| **Kruskal (this)** | Fast | Medium | Excellent |
| DFS Backtracking | Medium | Low | Good |
| Prim's | Fast | Medium | Excellent |
| Recursive Division | Fast | Low | Good |

Kruskal's is ideal for roguelikes because:
- Creates interesting layouts
- Fast enough for real-time generation
- Easy to add extra loops (cycle detection)

---

## Integration with Larger System

### Called By: `draw_dungeon_border()`

```c
void draw_dungeon_border(int value) {
    // ... draw walls and borders ...

    // Initialize parent array
    for (local_a = 1;
         *(int *)(&stack0xfc92 + local_a * 2) = local_a,
         local_a != 0x1ad;  // 0x1ad = 429 rooms?
         local_a = local_a + 1) {
    }

    // Generate corridors until complete
    do {
        generate_dungeon_corridors(&stack0xfffe);
    } while(true);  // Exits internally when done
}
```

### Calls To:

1. **`random_mod(808)`**: Get random corridor
2. **`find_dungeon_region()`**: Union-Find lookup
3. **Map memory writes**: Place corridor character

---

## Potential Issues and Observations

### 1. Infinite Loop Risk

```c
do {
    generate_dungeon_corridors(&stack0xfffe);
} while(true);
```

**Issue**: No visible exit condition in the decompiled code!

**Likely resolution**:
- Function probably modifies a counter that reaches a threshold
- Or sets a flag when all rooms are connected
- Decompiler may have missed the exit logic

### 2. Memory Addressing Complexity

The function uses complex offset calculations:
```c
*(int *)(value + local_8 * 2 + -0x36c)
```

This is **stack-relative addressing** - the decompiler couldn't determine the original variable names.

### 3. First Corridor Flag

```c
if ((region1 != region2) || (*(char *)(value + -0x36b) == '\0'))
```

The OR condition allows placing corridors even if rooms are already connected, **creating loops** in the maze for more interesting gameplay.

---

## Summary

`generate_dungeon_corridors()` is a **sophisticated maze generation algorithm** that:

✅ Uses **Randomized Kruskal's MST** algorithm
✅ Implements **Union-Find with path compression** for O(1) region queries
✅ Generates **connected dungeons** with 10×39 room grid
✅ Supports **808 possible corridors** (391 vertical + 417 horizontal)
✅ Creates **perfect mazes** with optional loops
✅ Writes directly to **DOS text mode video memory**
✅ Handles both **vertical and horizontal** corridor placement
✅ Uses **efficient randomization** for varied layouts

**Algorithm Complexity:**
- Time: O(E α(V)) ≈ O(E) where E=808 corridors, V=390 rooms
- Space: O(V) for parent array
- α(V) is inverse Ackermann function (grows incredibly slowly)

This is a **classic computer science algorithm** beautifully applied to procedural dungeon generation in a 1980s roguelike game!
