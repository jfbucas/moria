# Deep Analysis: `display_score_with_fatal()` Function

## Overview

`display_score_with_fatal()` is the **primary message display system** in Moria. It's responsible for showing game messages, warnings, and fatal errors to the player.

The function name reveals its dual purpose:
- **display_score**: Display a message from the string table
- **with_fatal**: Optionally trigger fatal error handling (when value is negative)

---

## Function Signature

```c
void display_score_with_fatal(int value)
```

**Parameter:**
- `value` (int): Message index into the string table
  - **Positive value**: Display message normally
  - **Negative value**: Display message + trigger fatal error handling

---

## How It Works

### 1. Architecture: Multi-Region String Table

The game stores hundreds of messages in 4 separate string table regions, optimized by message length:

```
┌─────────────────────────────────────────────────────────────┐
│  MESSAGE TABLE LAYOUT (in DOS memory)                       │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  Region 1: Short messages (indices 0-100)                   │
│    • ~51 bytes per message                                  │
│    • Formula: offset = value × 51 - 15287                   │
│    • Examples: "Vous n'avez rien!", "-- encore --"          │
│                                                              │
│  Region 2: Medium messages (indices 101-300)                │
│    • ~31 bytes per message                                  │
│    • Formula: offset = (value - 100) × 31 - 10677           │
│    • Examples: status updates, item descriptions            │
│                                                              │
│  Region 3: Long messages (indices 301-400)                  │
│    • ~73 bytes per message                                  │
│    • Formula: offset = (value - 300) × 73 - 17572           │
│    • Examples: help text, detailed descriptions             │
│                                                              │
│  Region 4: Variable messages (indices 401+)                 │
│    • ~16 bytes per message                                  │
│    • Formula: offset = (value - 400) × 16 - 7283            │
│    • Examples: short status messages                        │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 2. Execution Flow

```
┌──────────────────────────────────────────────────────────┐
│ display_score_with_fatal(value)                          │
└──────────────────────────────────────────────────────────┘
                    │
                    ▼
         ┌──────────────────┐
         │  value < 0 ?     │────No────┐
         └──────────────────┘          │
                    │                   │
                   Yes                  │
                    │                   │
                    ▼                   │
      ┌──────────────────────────┐     │
      │ check_minimum_stats()    │     │
      │  - Check turn_count      │     │
      │  - Check food_level      │     │
      │  - Show warnings if low  │     │
      └──────────────────────────┘     │
                    │                   │
                    │◄──────────────────┘
                    ▼
         ┌──────────────────┐
         │ value = abs(value)│
         └──────────────────┘
                    │
                    ▼
         ┌──────────────────────────────┐
         │ Calculate offset based on:   │
         │  • value 0-100    → Region 1 │
         │  • value 101-300  → Region 2 │
         │  • value 301-400  → Region 3 │
         │  • value 401+     → Region 4 │
         └──────────────────────────────┘
                    │
                    ▼
         ┌──────────────────────────────┐
         │ write_padded_string(         │
         │    row=0,                    │
         │    offset=calculated,        │
         │    segment=data_segment      │
         │ )                            │
         │ → Displays message on screen │
         └──────────────────────────────┘
                    │
                    ▼
         ┌──────────────────┐
         │ flush_output()   │
         │ → Update display │
         └──────────────────┘
                    │
                    ▼
         ┌──────────────────┐
         │ value < 0 ?      │────No─────► RETURN
         └──────────────────┘
                    │
                   Yes (FATAL ERROR!)
                    │
                    ▼
      ┌──────────────────────────────────┐
      │ handle_error_and_wait()          │
      │  1. Display message 0xc0 (192)   │
      │     "Press space to continue"    │
      │  2. Wait for SPACE key           │
      │  3. Redraw screen or check stats │
      └──────────────────────────────────┘
                    │
                    ▼
                  RETURN
```

### 3. Code Implementation

Here's the actual decompiled code with annotations:

```c
void display_score_with_fatal(int value)
{
  int iVar1;
  undefined2 unaff_DS;
  undefined2 uVar2;

  iVar1 = value;

  // STEP 1: Check if this is a fatal error (negative value)
  if (value < 0) {
    check_minimum_stats();  // Display turn/food warnings if needed
    iVar1 = -value;         // Use absolute value for string lookup
  }

  // STEP 2: Calculate offset based on value range

  // Region 4: value >= 401 (0x191)
  if (iVar1 < 0x191) {
    iVar1 = value;
    if (value < 0) {
      iVar1 = -value;
    }

    // Region 3: value 301-400 (0x12d - 0x190)
    if (iVar1 < 0x12d) {
      iVar1 = value;
      if (value < 0) {
        iVar1 = -value;
      }

      // Region 2: value 101-300 (0x65 - 0x12c)
      if (iVar1 < 0x65) {
        // Region 1: value 0-100
        uVar2 = 0xe654;
        iVar1 = value;
        if (value < 0) {
          iVar1 = -value;
        }
        // offset = value * 0x33 + -0x3bb7
        //        = value * 51 - 15287
        write_padded_string(0, iVar1 * 0x33 + -0x3bb7, unaff_DS);
        flush_output(uVar2, unaff_DS);
      }
      else {
        // Region 2: value 101-300
        uVar2 = 0xe654;
        iVar1 = value;
        if (value < 0) {
          iVar1 = -value;
        }
        // offset = (value - 100) * 0x1f + -0x29b5
        //        = (value - 100) * 31 - 10677
        write_padded_string(0, (iVar1 + -100) * 0x1f + -0x29b5, unaff_DS);
        flush_output(uVar2, unaff_DS);
      }
    }
    else {
      // Region 3: value 301-400
      uVar2 = 0xe654;
      iVar1 = value;
      if (value < 0) {
        iVar1 = -value;
      }
      // offset = (value - 300) * 0x49 + -0x44a4
      //        = (value - 300) * 73 - 17572
      write_padded_string(0, (iVar1 + -300) * 0x49 + -0x44a4, unaff_DS);
      flush_output(uVar2, unaff_DS);
    }
  }
  else {
    // Region 4: value >= 401
    uVar2 = 0xe654;
    iVar1 = value;
    if (value < 0) {
      iVar1 = -value;
    }
    // offset = (value - 400) * 0x10 + -0x1c73
    //        = (value - 400) * 16 - 7283
    write_padded_string(0, (iVar1 + -400) * 0x10 + -0x1c73, unaff_DS);
    flush_output(uVar2, unaff_DS);
  }

  // STEP 3: Handle fatal error if value was negative
  if (value < 0) {
    handle_error_and_wait();  // Display "press space", wait for key, redraw
  }
  return;
}
```

---

## Helper Functions

### `check_minimum_stats()`

Called when displaying a fatal error message. Checks game state and displays warnings:

```c
void check_minimum_stats(void)
{
  validate_window_coords(1, 1);
  update_screen_double();

  // Warn if game just started
  if (turn_count < 100) {
    write_padded_string(0, 0x34, 0x20e6);  // Early game warning
    flush_output(0xe654, unaff_DS);
  }

  // Warn if starving
  if (food_level < 400) {
    write_padded_string(0, 0x3a, 0x214c);  // Low food warning
    flush_output(0xe654, unaff_DS);
  }
}
```

**Purpose**: Provide context before showing a fatal error. If the player dies or encounters a serious problem, this shows whether it was due to:
- Being a new player (turn_count < 100)
- Starvation (food_level < 400)

### `handle_error_and_wait()`

Called after displaying a fatal error message. Forces player acknowledgment:

```c
void handle_error_and_wait(void)
{
  char cVar1;

  // Display "Press space to continue" message
  display_score_with_fatal(0xc0);  // Message #192
  update_screen_double();

  // Wait for space key
  do {
    cVar1 = read_keyboard_input();
  } while (cVar1 != ' ');

  // Clean up and refresh screen
  cVar1 = get_relative_cursor_x();
  if (cVar1 == '\x02') {
    redraw_dungeon_level(1);  // Redraw full dungeon
  }
  else {
    check_minimum_stats();    // Re-check and display stats
  }
}
```

**Purpose**:
1. Pause the game so player can read the fatal error
2. Wait for explicit acknowledgment (space key)
3. Refresh the display to clean up any visual artifacts

---

## Usage Examples

### Example 1: Normal Message Display

```c
// From line 3465: Display stat label
validate_window_coords(flag * 2 + 9, 10);
display_score_with_fatal(flag + 0x2a);  // Message #42-45 (stats labels)
```

**Effect**: Displays a message (like "Force:", "Intelligence:", etc.) without any error handling.

### Example 2: Item Action Feedback

```c
// From line 668: Can't drop an item
if (param_1 == '\0') {
  display_score_with_fatal(0x4f);  // Message #79: "Vous ne pouvez pas..."
}
```

**Effect**: Shows a message explaining why an action failed.

### Example 3: Fatal Error (Hypothetical)

```c
// If the game were to call with negative value:
if (player_died) {
  display_score_with_fatal(-0x1a2);  // Message #418 + FATAL ERROR
}
```

**Effect**:
1. Check if player is starving or new (check_minimum_stats)
2. Display death message #418
3. Display "Press space to continue" (message #192)
4. Wait for space key
5. Redraw screen

---

## Message Index Examples

Based on code usage patterns:

| Value (hex) | Value (dec) | Region | Likely Content (French) |
|-------------|-------------|--------|-------------------------|
| 0x26 | 38 | 1 | Stat label or status |
| 0x2a | 42 | 1 | Stat label |
| 0x45 | 69 | 1 | Action feedback |
| 0x4e | 78 | 1 | Error message |
| 0x4f | 79 | 1 | Error message |
| 0xc0 | 192 | 2 | "Press space" / wait message |
| 0xce-0xd0 | 206-208 | 2 | Special condition messages |
| 0x193-0x194 | 403-404 | 4 | Short status messages |
| 0x19a | 410 | 4 | Short message |
| 0x1a2 | 418 | 4 | Short message |

---

## Why "Fatal"?

The function is called "with_fatal" because:

1. **Sign bit = severity flag**: The clever use of negative values to indicate fatal errors allows a single function to handle both:
   - Normal messages (positive values)
   - Fatal errors (negative values)

2. **Forced acknowledgment**: Fatal errors **require** player interaction (press space) before continuing.

3. **Context display**: Fatal errors show game state (turn count, food level) to help understand **why** the error occurred.

4. **Screen recovery**: After fatal errors, the screen is redrawn to ensure clean visual state.

---

## Design Patterns

This function demonstrates several interesting DOS-era game programming patterns:

### 1. **Segmented Memory Addressing**
```c
write_padded_string(0, offset, segment);
```
Uses DOS segment:offset addressing to access string tables in different memory segments.

### 2. **Variable-Length Message Packing**
Different regions use different message sizes (16, 31, 51, 73 bytes) to optimize memory usage based on message content.

### 3. **Sign Bit as Flag**
Using negative values as a flag is memory-efficient in 16-bit DOS:
- No need for separate boolean parameter
- Single comparison `if (value < 0)` handles both checks

### 4. **Modal Error Handling**
Fatal errors make the game **modal** - it stops and waits for acknowledgment, ensuring critical messages aren't missed.

---

## Real-World Game Messages (French)

Here are actual messages found in the memory dump around offset 0x2f000-0x32000:

```
"Il semble que votre armure soit ensorcellée."
  (It seems that your armor is cursed.)

"Vous y voyez un peu plus clair."
  (You can see a bit more clearly.)

"Vous êtes devenu esclave de l'Anneau"
  (You have become a slave to the Ring)

"! Vous ne portez pas d'armure !"
  (! You're not wearing any armor !)

"Votre armure rouille !"
  (Your armor is rusting!)

"mort de faim"
  (dead from starvation)

"-- encore --"
  (-- more --)
```

These are displayed using this function!

---

## Summary

`display_score_with_fatal()` is a **sophisticated message display system** that:

✅ Handles **400+ game messages** through indexed lookup
✅ Optimizes memory with **variable-length message regions**
✅ Provides **dual-mode operation** (normal vs. fatal)
✅ Implements **modal error handling** for critical messages
✅ Uses **DOS segmented memory** architecture
✅ Displays **context information** before fatal errors
✅ Ensures **player acknowledgment** of important messages

It's a core system that touches almost every aspect of the game, from combat messages to death screens to item descriptions. The name "with_fatal" reflects its ability to escalate from simple message display to full game-stopping error handling based on a single parameter sign!
