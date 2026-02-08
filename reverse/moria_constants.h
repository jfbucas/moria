/**
 * Moria Game Constants
 * Extracted from reverse-engineered code
 *
 * This header defines all magic numbers used throughout the Moria codebase
 */

#ifndef MORIA_CONSTANTS_H
#define MORIA_CONSTANTS_H

/* ========================================================================
 * MAP DIMENSIONS
 * ======================================================================== */
#define MAP_WIDTH           79      // 0x4f - Map width in tiles
#define MAP_HEIGHT          22      // 0x16 - Map height in tiles
#define MAP_STRIDE          80      // 0x50 - Bytes per row (includes boundary)

#define HALF_SCREEN_WIDTH   39      // 0x27 - For centering
#define HALF_SCREEN_HEIGHT  12      // 0x0c - For centering

/* ========================================================================
 * OBJECT SIZES
 * ======================================================================== */
#define MONSTER_SIZE        54      // 0x36 - Monster structure size in bytes
#define ITEM_SIZE           26      // 0x1a - Item structure size in bytes

/* ========================================================================
 * ITEM TYPES
 * ======================================================================== */
typedef enum {
    ITEM_UNKNOWN_0      = 0x00,
    ITEM_UNKNOWN_1      = 0x01,
    ITEM_UNKNOWN_2      = 0x02,
    ITEM_UNKNOWN_3      = 0x03,
    ITEM_SCROLL         = 0x04,     // Scrolls
    ITEM_UNKNOWN_5      = 0x05,
    ITEM_LIGHT_SOURCE   = 0x06,     // Torch/lantern (decrements each turn)
    ITEM_WEAPON         = 0x07,     // Weapons
    ITEM_UNKNOWN_8      = 0x08,
    ITEM_FOOD           = 0x09,     // Food rations
    ITEM_UNKNOWN_A      = 0x0a,
    ITEM_CURSED_SPECIAL = 0x0b,     // Special cursed item (extra monster spawns)
    ITEM_UNKNOWN_C      = 0x0c,
    ITEM_UNKNOWN_D      = 0x0d,
    ITEM_UNKNOWN_E      = 0x0e,
    ITEM_UNKNOWN_F      = 0x0f,
    ITEM_UNKNOWN_10     = 0x10,
    ITEM_LAMP           = 0x11,     // Lamp/permanent light source
    ITEM_LEVITATION     = 0x12,     // Boots of Levitation (decrements each turn)
    ITEM_DRAIN_STAT     = 0x13,     // Item that drains stats/mana (cursed?)
} ItemType;

/* ========================================================================
 * MONSTER TYPES
 * ======================================================================== */
typedef enum {
    MONSTER_TYPE_1D     = 0x1d,
    MONSTER_TYPE_1E     = 0x1e,
    MONSTER_TYPE_1F     = 0x1f,
    MONSTER_TYPE_20     = 0x20,
    MONSTER_TYPE_22     = 0x22,     // Special monster with scroll
    MONSTER_TYPE_23     = 0x23,     // Unique monster
} MonsterType;

/* ========================================================================
 * MONSTER ATTACK TYPES
 * ======================================================================== */
typedef enum {
    ATTACK_FEAR         = 0x45,     // 69 - Induces fear
    ATTACK_STEAL_ITEM   = 0x46,     // 70 - Steals item from inventory
    ATTACK_ACID_1       = 0x47,     // 71 - Acid attack type 1
    ATTACK_CONFUSE      = 0x48,     // 72 - Causes confusion
    ATTACK_REMOVE_MAGIC = 0x4d,     // 77 - Removes enchantments
    ATTACK_ACID_2       = 0x4e,     // 78 - Acid attack type 2
    ATTACK_STEAL_GOLD   = 0x56,     // 86 - Steals gold
    ATTACK_DRAIN_EXP    = 0x73,     // 115 - Drains experience
    ATTACK_DRAIN_STR    = 0x9c,     // 156 - Drains strength
    ATTACK_DRAIN_CON    = 0x9e,     // 158 - Drains constitution
    ATTACK_GHOST_1      = 0xe8,     // 232 - Ghost touch
    ATTACK_GHOST_2      = 0xea,     // 234 - Ghost touch variant
} AttackType;

/* ========================================================================
 * TILE TYPES (Map Characters)
 * ======================================================================== */
#define TILE_SPACE          ' '     // 0x20 - Empty floor
#define TILE_WALL_H         0xc4    // Horizontal wall (─)
#define TILE_WALL_V         0xb3    // Vertical wall (│)
#define TILE_CROSS          0xc5    // Cross intersection (┼)
#define TILE_CORNER_TL      0xda    // Top-left corner (┌)
#define TILE_CORNER_TR      0xbf    // Top-right corner (┐)
#define TILE_CORNER_BL      0xc0    // Bottom-left corner (└)
#define TILE_CORNER_BR      0xd9    // Bottom-right corner (┘)
#define TILE_STAIRS_DOWN    0x9b    // Stairs down
#define TILE_STAIRS_UP      0xef    // Stairs up (0x11 negated)
#define TILE_TREASURE       0xf7    // Treasure marker
#define TILE_LAVA           -9      // 0xf7 - Dangerous lava/trap tile
#define TILE_SPECIAL_1      -0x11   // Special tile type 1
#define TILE_TRAP           2       // Trap tile
#define TILE_DANGEROUS      3       // Dangerous floor

/* ========================================================================
 * PLAYER STATS (Memory Addresses)
 * ======================================================================== */
#define ADDR_PLAYER_Y       0xb86c
#define ADDR_PLAYER_X       0xb86e
#define ADDR_CURRENT_HP     0xb870
#define ADDR_MAX_HP         0xb872
#define ADDR_CURRENT_FOOD   0xb874  // Food/satiation level (NOT mana!)
#define ADDR_MAX_FOOD       0xb876  // Maximum food/satiation (NOT mana!)
#define ADDR_STRENGTH       0xb878
#define ADDR_INTELLIGENCE   0xb87a
#define ADDR_BASE_AC        0xb880
#define ADDR_EXPERIENCE     0xb886
#define ADDR_PLAYER_LEVEL   0xb888
#define ADDR_TURN_COUNT     0xb892
#define ADDR_GOLD_LOW       0xb8c8
#define ADDR_GOLD_HIGH      0xb8ca

/* ========================================================================
 * PLAYER STATUS FLAGS (Memory Addresses)
 * ======================================================================== */
#define ADDR_IS_PARALYZED   0xb8ec  // Paralysis flag
#define ADDR_IS_BLIND       0xb8ed  // Blindness flag
#define ADDR_NEEDS_UPDATE   0xb8ee  // Full screen redraw needed
#define ADDR_SPEED_ACTIVE   0xb8ef  // Speed boost active (potion 5)
#define ADDR_CONFUSION_LOCK 0xb8f0  // Confusion lock state
#define ADDR_STATUS_FLAG_1  0xb8f1  // Status flag (potion 19)
#define ADDR_IS_TELEPORTING 0xb8f2  // Teleportation in progress
#define ADDR_STATUS_FLAG_3  0xb8f3  // Status flag (potion 18)
#define ADDR_STATUS_FLAG_5  0xb8f5  // Status flag (potion 21)
#define ADDR_IS_WIZARD      0xb8f6  // Wizard mode active
#define ADDR_IS_STUNNED     0xb8f7  // Stunned state
#define ADDR_TELEPORT_FLAG  0xb8f8  // Teleport/effect flag (potions 16/17)
#define ADDR_HALLUCINATION  0xb913  // Hallucination active (potion 11)
#define ADDR_IS_DYING       0xb915  // Death countdown active
#define ADDR_IS_HASTED      0xb916  // Haste effect active
#define ADDR_HAS_LIGHT      0xb918  // Light source active
#define ADDR_IS_CONFUSED    0xb919  // Confused state

/* ========================================================================
 * TIMED EFFECT TIMERS (Memory Addresses)
 * ======================================================================== */
#define ADDR_PARALYZE_TIMER 0xb8f9  // Paralysis duration (potion 9)
#define ADDR_BLIND_TIMER    0xb8fb  // Blindness duration (potion 12)
#define ADDR_DETECT_TIMER   0xb8fd  // Detect monsters duration (potion 7)
#define ADDR_SPEED_TIMER    0xb8ff  // Speed boost duration (potion 5)
#define ADDR_HALLUC_TIMER   0xb901  // Hallucination duration (potion 11)
#define ADDR_STATUS_TIMER_1 0xb903  // Status timer (potion 19)
#define ADDR_TELEPORT_TIMER 0xb905  // Teleport timer (potion 17)
#define ADDR_STATUS_TIMER_3 0xb907  // Status timer (potion 18)
#define ADDR_FOOD_LEVEL     0xb909  // Food/satiation level
#define ADDR_STATUS_TIMER_5 0xb90b  // Status timer (potion 21)
#define ADDR_WIZARD_TIMER   0xb90d  // Wizard mode duration (potion 22)
#define ADDR_EFFECT_TIMER_16 0xb911 // Effect timer (potion 16)
#define ADDR_DEATH_TIMER    0xb91a  // Death countdown timer
#define ADDR_HASTE_TIMER    0xb91c  // Haste duration timer

/* ========================================================================
 * INVENTORY & EQUIPMENT (Memory Addresses)
 * ======================================================================== */
#define ADDR_INVENTORY_LIST 0xb91e
#define ADDR_WIELDED_WEAPON 0xb922
#define ADDR_EQUIPPED_SHIELD 0xb926
#define ADDR_EQUIPPED_ARMOR 0xb92a
#define ADDR_EQUIPPED_RING1 0xb92e
#define ADDR_EQUIPPED_RING2 0xb932

/* ========================================================================
 * WORLD STATE (Memory Addresses)
 * ======================================================================== */
#define ADDR_DUNGEON_LEVEL  0xe52d
#define ADDR_MIN_VISIBLE_ROW 0xe535
#define ADDR_MAX_VISIBLE_ROW 0xe537

/* ========================================================================
 * COMMAND KEYS
 * ======================================================================== */
#define CMD_MOVE_DOWN       '2'
#define CMD_MOVE_LEFT       '4'
#define CMD_MOVE_RIGHT      '6'
#define CMD_MOVE_UP         '8'
#define CMD_STAIRS_UP       '<'     // 0x3c
#define CMD_STAIRS_DOWN     '>'     // 0x3e
#define CMD_QUIT            'q'     // 0x71
#define CMD_HELP            '?'     // 0x3f
#define CMD_INVENTORY       'i'     // 0x69
#define CMD_EQUIPMENT       'e'     // 0x65
#define CMD_PICKUP          ','
#define CMD_DROP            'd'
#define CMD_SEARCH          's'     // 0x73
#define CMD_CAST_SPELL      'm'     // 0x6d
#define CMD_SAVE            0x13    // Ctrl+S
#define CMD_REPEAT_MSG      0x10    // Ctrl+P
#define CMD_VERSION         0x16    // Ctrl+V

/* ========================================================================
 * SPELL EFFECTS
 * ======================================================================== */
typedef enum {
    SPELL_HEAL          = 1,
    SPELL_BLESS         = 2,
    SPELL_LIGHT         = 3,
    SPELL_RESTORE_STAT  = 4,
    SPELL_REVEAL_MAP    = 5,
    SPELL_TELEPORT      = 6,
    SPELL_CHANGE_LEVEL  = 7,
    SPELL_GO_DOWN       = 8,
    SPELL_SUMMON        = 9,
    SPELL_BLESS_CURSE   = 10,
    SPELL_IDENTIFY_ONE  = 11,
    SPELL_IDENTIFY_ALL  = 12,
    SPELL_REMOVE_CURSE  = 13,
    // ... more spells
} SpellEffect;

/* ========================================================================
 * POTION EFFECTS (French names from memory dump)
 * ======================================================================== */
typedef enum {
    POTION_HEAL         = 1,    // de guérison - Heal HP (modest)
    POTION_GREATER_HEAL = 2,    // d'extra-guérison - Heal HP (full)
    POTION_STAMINA      = 3,    // nourrissante - Increase food/stamina
    POTION_RESTORE_FOOD = 4,    // désaltérante - Restore food to maximum
    POTION_SPEED        = 5,    // accélérante - Speed boost (100-150 turns)
    POTION_CONSTITUTION = 6,    // de constitution - Increase constitution
    POTION_DETECT_MONSTERS = 7, // d'extralucidité - Detect monsters (50-125 turns)
    POTION_AMNESIA      = 8,    // amnésiante - Memory loss/amnesia
    POTION_PARALYZE     = 9,    // paralysante - Paralyze or remove haste (10-15 turns)
    POTION_HASTE        = 10,   // accélérante - Haste or cure paralysis (30-35 turns)
    POTION_HALLUCINATION = 11,  // hallucinogène - Hallucination (350-400 turns)
    POTION_BLINDNESS    = 12,   // aveuglante - Blindness (200-300 turns)
    POTION_GAIN_TURNS   = 13,   // ??? - Gain 500+ turns (not in names list)
    POTION_GAIN_LEVEL   = 14,   // d'expérience - Gain experience level
    POTION_LOSE_LEVEL   = 15,   // de perte de niveau - Lose experience level
    POTION_INVISIBILITY = 16,   // d'invisibilité - Invisibility (300-400 turns)
    POTION_TELEPORT     = 17,   // de téléportation - Teleport (150-250 turns)
    POTION_PASS_WALL    = 18,   // passe muraille - Pass through walls (15-25 turns)
    POTION_LEVITATION   = 19,   // de lévitation - Levitation (100-150 turns)
    POTION_CONFUSION    = 20,   // de confusion - Causes confusion
    POTION_POISON       = 21,   // empoisonnée - Poison effect (25-40 turns)
    POTION_WIZARD_MODE  = 22,   // ??? - Wizard mode (25-40 turns)
    POTION_STRENGTH     = 23,   // de force - Increase strength (permanent)
} PotionEffect;

/* ========================================================================
 * TIMED EFFECTS
 * ======================================================================== */
#define NUM_TIMED_EFFECTS   12      // 0x0c - Number of timed effect slots
#define EFFECT_ARRAY_OFFSET -0x4714  // Array of active effect flags
#define TIMER_ARRAY_OFFSET  -0x4707  // Array of effect timers

/* ========================================================================
 * GAME CONSTANTS
 * ======================================================================== */
#define SPAWN_INTERVAL      20      // Monsters spawn every 20 turns
#define TURN_THRESHOLD      4000    // Game turn counter threshold
#define REGEN_HP_AMOUNT     1       // HP regenerated per cycle
#define MAX_INVENTORY_SLOTS 35      // 0x23 - Maximum inventory size

/* ========================================================================
 * CHARACTER DISPLAY
 * ======================================================================== */
#define CHAR_PLAYER         '@'     // Normal player character
#define CHAR_WIZARD         '~'     // 0x7e - Wizard mode character
#define CHAR_SPACE          0x20    // Space character

/* ========================================================================
 * ERROR/MESSAGE CODES
 * ======================================================================== */
#define MSG_DEATH           0x1a2   // Death message ID (418)
#define MSG_LEVEL_UP        0x91    // Level up message
#define MSG_GAME_OVER       0x61    // Game over code

#endif /* MORIA_CONSTANTS_H */
