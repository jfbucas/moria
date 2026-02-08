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
#define ADDR_CURRENT_MANA   0xb874
#define ADDR_MAX_MANA       0xb876
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
#define ADDR_IS_PARALYZED   0xb8ec
#define ADDR_IS_BLIND       0xb8ed
#define ADDR_NEEDS_UPDATE   0xb8ee
#define ADDR_CONFUSION_LOCK 0xb8f0
#define ADDR_IS_TELEPORTING 0xb8f2
#define ADDR_IS_WIZARD      0xb8f6
#define ADDR_IS_STUNNED     0xb8f7
#define ADDR_IS_DYING       0xb915
#define ADDR_IS_HASTED      0xb916
#define ADDR_HAS_LIGHT      0xb918
#define ADDR_IS_CONFUSED    0xb919
#define ADDR_DEATH_TIMER    0xb91a
#define ADDR_HASTE_TIMER    0xb91c

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
 * POTION EFFECTS
 * ======================================================================== */
typedef enum {
    POTION_HEAL         = 1,
    POTION_GREATER_HEAL = 2,
    POTION_STAMINA      = 3,
    POTION_RESTORE_MANA = 4,
    POTION_SPEED        = 5,
    POTION_CURE_BLIND   = 7,
    POTION_DETECT_MONSTER = 8,
    POTION_CURE_POISON  = 9,
    POTION_CURE_CONFUSION = 10,
    POTION_HALLUCINATION = 11,
    POTION_CONFUSION    = 12,
    POTION_GAIN_GOLD    = 13,
    POTION_GAIN_LEVEL   = 14,
    POTION_LOSE_LEVEL   = 15,
    // ... more potions
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
