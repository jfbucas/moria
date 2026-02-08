/**
 * Moria Game - Global Variables
 *
 * This header provides proper variable declarations for all game state
 * stored at fixed memory addresses in the original DOS version.
 *
 * Usage: Include this header and use the variable names directly instead
 *        of memory address dereferencing like *(int *)0xb870
 */

#ifndef MORIA_GLOBALS_H
#define MORIA_GLOBALS_H

#include "moria_constants.h"

/* ========================================================================
 * PLAYER POSITION
 * ======================================================================== */
#define player_y            (*(int *)ADDR_PLAYER_Y)         // 0xb86c
#define player_x            (*(int *)ADDR_PLAYER_X)         // 0xb86e

/* ========================================================================
 * PLAYER STATS
 * ======================================================================== */
#define current_hp          (*(int *)ADDR_CURRENT_HP)       // 0xb870
#define max_hp              (*(int *)ADDR_MAX_HP)           // 0xb872
#define current_food        (*(int *)ADDR_CURRENT_FOOD)     // 0xb874 - NOT mana!
#define max_food            (*(int *)ADDR_MAX_FOOD)         // 0xb876 - NOT mana!
#define strength            (*(int *)ADDR_STRENGTH)         // 0xb878
#define intelligence        (*(int *)ADDR_INTELLIGENCE)     // 0xb87a
#define base_ac             (*(int *)ADDR_BASE_AC)          // 0xb880
#define experience          (*(int *)ADDR_EXPERIENCE)       // 0xb886
#define player_level        (*(int *)ADDR_PLAYER_LEVEL)     // 0xb888
#define turn_count          (*(int *)ADDR_TURN_COUNT)       // 0xb892
#define gold_low            (*(int *)ADDR_GOLD_LOW)         // 0xb8c8
#define gold_high           (*(int *)ADDR_GOLD_HIGH)        // 0xb8ca

/* ========================================================================
 * PLAYER STATUS FLAGS
 * ======================================================================== */
#define is_paralyzed        (*(char *)ADDR_IS_PARALYZED)    // 0xb8ec
#define is_blind            (*(char *)ADDR_IS_BLIND)        // 0xb8ed
#define needs_full_update   (*(char *)ADDR_NEEDS_UPDATE)    // 0xb8ee
#define speed_boost_active  (*(char *)ADDR_SPEED_ACTIVE)    // 0xb8ef
#define confusion_lock      (*(char *)ADDR_CONFUSION_LOCK)  // 0xb8f0
#define status_flag_1       (*(char *)ADDR_STATUS_FLAG_1)   // 0xb8f1
#define is_teleporting      (*(char *)ADDR_IS_TELEPORTING)  // 0xb8f2
#define status_flag_3       (*(char *)ADDR_STATUS_FLAG_3)   // 0xb8f3
#define status_flag_5       (*(char *)ADDR_STATUS_FLAG_5)   // 0xb8f5
#define is_wizard           (*(char *)ADDR_IS_WIZARD)       // 0xb8f6
#define is_stunned          (*(char *)ADDR_IS_STUNNED)      // 0xb8f7
#define teleport_effect_flag (*(char *)ADDR_TELEPORT_FLAG)  // 0xb8f8
#define hallucination_active (*(char *)ADDR_HALLUCINATION)  // 0xb913
#define is_dying            (*(char *)ADDR_IS_DYING)        // 0xb915
#define is_hasted           (*(char *)ADDR_IS_HASTED)       // 0xb916
#define has_light           (*(char *)ADDR_HAS_LIGHT)       // 0xb918
#define is_confused         (*(char *)ADDR_IS_CONFUSED)     // 0xb919

/* ========================================================================
 * TIMED EFFECT TIMERS
 * ======================================================================== */
#define paralyze_timer      (*(int *)ADDR_PARALYZE_TIMER)   // 0xb8f9
#define blind_timer         (*(int *)ADDR_BLIND_TIMER)      // 0xb8fb
#define detect_timer        (*(int *)ADDR_DETECT_TIMER)     // 0xb8fd
#define speed_timer         (*(int *)ADDR_SPEED_TIMER)      // 0xb8ff
#define hallucination_timer (*(int *)ADDR_HALLUC_TIMER)     // 0xb901
#define status_timer_1      (*(int *)ADDR_STATUS_TIMER_1)   // 0xb903
#define teleport_timer      (*(int *)ADDR_TELEPORT_TIMER)   // 0xb905
#define status_timer_3      (*(int *)ADDR_STATUS_TIMER_3)   // 0xb907
#define food_level          (*(int *)ADDR_FOOD_LEVEL)       // 0xb909
#define status_timer_5      (*(int *)ADDR_STATUS_TIMER_5)   // 0xb90b
#define wizard_mode_timer   (*(int *)ADDR_WIZARD_TIMER)     // 0xb90d
#define effect_timer_16     (*(int *)ADDR_EFFECT_TIMER_16)  // 0xb911
#define death_timer         (*(int *)ADDR_DEATH_TIMER)      // 0xb91a
#define haste_timer         (*(int *)ADDR_HASTE_TIMER)      // 0xb91c

/* ========================================================================
 * INVENTORY & EQUIPMENT (Pointers)
 * ======================================================================== */
#define inventory_list      (*(void **)ADDR_INVENTORY_LIST) // 0xb91e
#define wielded_weapon      (*(int *)ADDR_WIELDED_WEAPON)   // 0xb922
#define equipped_shield     (*(int *)ADDR_EQUIPPED_SHIELD)  // 0xb926
#define equipped_armor      (*(int *)ADDR_EQUIPPED_ARMOR)   // 0xb92a
#define equipped_ring1      (*(int *)ADDR_EQUIPPED_RING1)   // 0xb92e
#define equipped_ring2      (*(int *)ADDR_EQUIPPED_RING2)   // 0xb932

/* ========================================================================
 * WORLD STATE
 * ======================================================================== */
#define dungeon_level       (*(int *)ADDR_DUNGEON_LEVEL)    // 0xe52d
#define min_visible_row     (*(int *)ADDR_MIN_VISIBLE_ROW)  // 0xe535
#define max_visible_row     (*(int *)ADDR_MAX_VISIBLE_ROW)  // 0xe537

#endif /* MORIA_GLOBALS_H */
