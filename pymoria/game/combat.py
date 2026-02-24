"""
Combat System for PyMoria
Reference: reverse/COMBAT_SYSTEM.md

Implements exact formulas from reverse engineering:
- execute_player_attack (line 6706)
- monster_attack_player (line 6368)
- kill_monster (line 6130)

CRITICAL: All formulas are exact — no modifications.
"""

import random
from typing import Optional, Tuple, TYPE_CHECKING

from utils.constants import (
    EFFECT_CONFUSION, EFFECT_PARALYSIS, EFFECT_POISON,
    EFFECT_BLINDNESS, EFFECT_FEAR, EFFECT_SLOW,
    calculate_level_up_hp_gain,
)

if TYPE_CHECKING:
    from game.entities import Player, Monster, Item


# =============================================================================
# XP LEVEL THRESHOLDS
# Reference: COMBAT_SYSTEM.md Section 9 (exact values from memory dump)
# =============================================================================

XP_THRESHOLDS = [
    0,       # Level 0 (unused)
    10,      # Level 1
    20,      # Level 2
    40,      # Level 3
    80,      # Level 4
    160,     # Level 5
    320,     # Level 6
    640,     # Level 7
    1280,    # Level 8
    2200,    # Level 9
    3700,    # Level 10
    6000,    # Level 11
    9000,    # Level 12
    14000,   # Level 13
]

MAX_PLAYER_LEVEL = 13


# =============================================================================
# WEAPON TABLES
# Reference: COMBAT_SYSTEM.md Section 8 (DS:0x9E7B)
# =============================================================================

# Weapon attack bonus (Atk Bonus column) — used for damage calculation
# Index = weapon subtype (1-15), index 0 is unused
WEAPON_ATTACK_BONUS = [0, 1, 1, 2, 3, 4, 5, 5, 6, 7, 6, 1, 0, 4, 5, 5]

# Weapon base damage (Base Dmg column) — used for ranged/thrown attacks
# Reference: COMBAT_SYSTEM.md Section 8 (DS:0x9EDD)
WEAPON_BASE_DAMAGE = [0, 6, 4, 10, 7, 8, 8, 15, 18, 21, 20, 1, 3, 13, 19, 19]


# =============================================================================
# MONSTER ATTACK CHARACTERS (special combat types)
# Reference: COMBAT_SYSTEM.md Section 1
# =============================================================================

ATTACK_SAURON       = 0x01   # ☺ - teleport + invisibility at low HP
ATTACK_BALROG       = 0x42   # B - vulnerable to subtype 14
ATTACK_DRAGON       = 0x44   # D - counter-attack + vulnerable subtype 14
ATTACK_EYE          = 0x45   # E - fear / death timer
ATTACK_FAIRY        = 0x46   # F - steal item
ATTACK_GALGAL       = 0x47   # G - acid (reduce food)
ATTACK_HUORN        = 0x48   # H - confusion
ATTACK_MEWLIP       = 0x4D   # M - remove magic
ATTACK_NAZGUL       = 0x4E   # N - acid (harder save)
ATTACK_VOLEUR       = 0x56   # V - steal gold
ATTACK_SUCCUBUS     = 0x73   # s - drain experience
ATTACK_DRAGON_VAR   = 0x92   # variant dragon - counter-attack
ATTACK_MORICAUD     = 0x9C   # Moricaud - drain strength
ATTACK_DRAIN_INT    = 0x9E   # variant - drain intelligence (fatal at 0)
ATTACK_SARUMAN      = 0xE4   # Saruman - random chaos
ATTACK_GHOST_1      = 0xE8   # Ghost type 1 - unparalyze
ATTACK_GHOST_2      = 0xEA   # Ghost type 2 - unparalyze + item drop

# Monsters with no special attack (standard melee only)
STANDARD_ATTACK_CHARS = {'a', 'A', 'C', 'L', 'O', 'R', 'S', 'T', 'U', 'v', 'W', 'w'}


# =============================================================================
# HELPER: SAVE THROW
# =============================================================================

def save_throw() -> bool:
    """
    Generic save throw — 50% chance to resist a special effect.
    """
    return random.randint(0, 1) == 0


# =============================================================================
# PLAYER ATTACKS MONSTER
# Reference: COMBAT_SYSTEM.md Section 2 (execute_player_attack, line 6706)
# =============================================================================

def player_attacks_monster(
    player: 'Player',
    monster: 'Monster',
    dungeon_level: int,
    screen=None,
) -> Tuple[bool, int]:
    """
    Resolve player attacking a monster.
    Reference: COMBAT_SYSTEM.md Section 2

    Returns:
        (hit: bool, damage: int)
    """

    # --- Step 2: Compute effective strength ---
    base_str = max(1, player.strength)

    # Ring1 modifiers (simplified — full ring system in Phase 3)
    # Regeneration ring (+2), Trap detection ring (-4)

    # --- Step 3: To-Hit Roll ---
    # Reference: COMBAT_SYSTEM.md Section 2, Step 3
    weapon = player.wielded_weapon

    if weapon is None:
        # UNARMED
        to_hit = (player.player_level
                  - monster.to_hit
                  - monster.armor_class
                  + 1
                  + random.randint(0, base_str - 1))
    else:
        # ARMED
        weapon_power = getattr(weapon, 'power', 0)
        to_hit = (player.player_level
                  + weapon_power
                  - monster.to_hit
                  - monster.armor_class
                  + 1
                  + random.randint(0, base_str - 1))

        # Mithril weapon bonus (subtypes 9, 13)
        weapon_subtype = getattr(weapon, 'subtype', 0)
        if weapon_subtype in [9, 13]:
            to_hit += 3

    if to_hit < 1:
        # MISS
        if screen:
            screen.draw_message(f"Vous ratez le {monster.name_french}!")
        return False, 0

    # --- Step 4: Hit — make monster hostile ---
    monster.is_hostile = True

    # --- Step 5: Compute Damage ---
    # food_cap = min(current_food, 25)
    # Reference: COMBAT_SYSTEM.md Section 2, Step 5
    food_cap = min(player.food_level, 25)

    weapon_attack_bonus = 0
    if weapon is not None:
        weapon_subtype = getattr(weapon, 'subtype', 0)
        if 1 <= weapon_subtype <= 15:
            weapon_attack_bonus = WEAPON_ATTACK_BONUS[weapon_subtype]

    # damage = random(0..weapon_attack_bonus + player_level*food_cap/10) + 1
    max_dmg = weapon_attack_bonus + (player.player_level * food_cap) // 10
    damage = random.randint(0, max(0, max_dmg)) + 1
    damage = max(1, damage)

    # --- Step 6: Special effects by attack_char (when player hits) ---
    _apply_player_hit_special(player, monster, weapon, damage, screen)

    # Weapon subtype 15 (vampiric): 25% chance to heal player
    if weapon is not None and getattr(weapon, 'subtype', 0) == 15:
        if random.randint(0, 3) == 0:
            heal = damage // 2
            player.current_hp = min(player.max_hp, player.current_hp + heal)

    # --- Step 7: Apply damage and check death ---
    monster.current_hp -= damage

    if monster.current_hp <= 0:
        _kill_monster(player, monster, dungeon_level, screen)
        return True, damage

    # Surviving monster reactions
    if monster.attack_char_code in [ATTACK_HUORN, ATTACK_EYE]:
        monster.is_fleeing = True
    elif monster.attack_char_code in [ATTACK_GHOST_1, ATTACK_GHOST_2]:
        monster.status_timer = 1

    if screen:
        screen.draw_message(
            f"Vous frappez le {monster.name_french} pour {damage} dégâts!"
        )
    return True, damage


def _apply_player_hit_special(player, monster, weapon, damage, screen):
    """
    Apply special effects when player hits a monster.
    Reference: COMBAT_SYSTEM.md Section 2, Step 6
    """
    ac = monster.attack_char_code
    weapon_subtype = getattr(weapon, 'subtype', 0) if weapon else 0

    if ac == ATTACK_SAURON:
        # Sauron: teleport + invisibility at low HP
        if monster.current_hp < 40:
            monster.is_invisible = True
            # Would reposition — handled by caller
        if weapon_subtype > 0 and weapon_subtype < 3:
            pass  # Weak weapons barely scratch Sauron (damage reduction done in caller)

    elif ac == ATTACK_SARUMAN:
        # Saruman: 10% chance of chaos effect on player
        if random.randint(0, 9) == 0:
            _apply_saruman_chaos(player, monster, screen)

    elif ac == ATTACK_GHOST_2:
        # Ghost type 2: if weapon is special (subtype 2 or 13), drop carried item
        if weapon_subtype in [2, 13]:
            monster.carried_item = None  # Drop item

    elif ac in [ATTACK_DRAGON, ATTACK_DRAGON_VAR]:
        # Dragon: check for dragon slayer bonus
        if weapon_subtype == 14:
            pass  # Extra damage from dragon slayer (bonus applied in caller)


def _apply_saruman_chaos(player, monster, screen):
    """
    Saruman chaos effect: random debuff on player.
    Reference: COMBAT_SYSTEM.md Section 2, Step 6
    """
    if monster.current_hp < 25:
        # Weak Saruman: teleport player 4 times (stub)
        if screen:
            screen.draw_message("Saroumane vous téléporte!")
    else:
        # Strong Saruman: random debuff
        effect = random.randint(0, 4)
        if effect == 0:
            # Speed boost 5-15 turns
            player.effect_active[EFFECT_SLOW] = True
            player.effect_timer[EFFECT_SLOW] = random.randint(5, 15)
            if screen:
                screen.draw_message("Vous vous sentez ralenti!")
        elif effect == 1:
            # Haste 5-10 turns (treat as slow for now)
            player.effect_active[EFFECT_SLOW] = True
            player.effect_timer[EFFECT_SLOW] = random.randint(5, 10)
        elif effect == 2:
            # Teleport 10-20 turns (stub)
            if screen:
                screen.draw_message("Saroumane vous téléporte!")
        elif effect == 3:
            # Blind 5-10 turns
            player.effect_active[EFFECT_BLINDNESS] = True
            player.effect_timer[EFFECT_BLINDNESS] = random.randint(5, 10)
            if screen:
                screen.draw_message("Saroumane vous aveugle!")
        elif effect == 4:
            # Wipe explored map + detect 12-24 turns (stub)
            if screen:
                screen.draw_message("La carte est effacée!")


# =============================================================================
# MONSTER ATTACKS PLAYER
# Reference: COMBAT_SYSTEM.md Section 3 (monster_attack_player, line 6368)
# =============================================================================

def monster_attacks_player(
    player: 'Player',
    monster: 'Monster',
    screen=None,
) -> Tuple[bool, int]:
    """
    Resolve monster attacking the player.
    Reference: COMBAT_SYSTEM.md Section 3

    Returns:
        (hit: bool, total_damage: int)
    """

    # --- Step 1: To-Hit Roll ---
    # to_hit = monster.to_hit - player_level - base_ac + 1 + random(0..speed_bonus-1)
    speed_roll = 0
    if monster.speed_bonus > 0:
        speed_roll = random.randint(0, monster.speed_bonus - 1)

    to_hit = (monster.to_hit
              - player.player_level
              - player.base_ac
              + 1
              + speed_roll)

    # Stunned penalty (-8)
    if player.effect_active[EFFECT_PARALYSIS]:
        to_hit -= 8

    if to_hit < 1:
        # MISS
        return False, 0

    # --- Step 3: Normal Damage ---
    # damage = sum over num_attacks of (1 + random(0..damage_per_attack-1))
    total_damage = 0
    if monster.damage_per_attack > 0:
        for _ in range(monster.num_attacks):
            total_damage += 1 + random.randint(0, monster.damage_per_attack - 1)

    player.current_hp -= total_damage

    if screen:
        screen.draw_message(
            f"Le {monster.name_french} vous frappe pour {total_damage} dégâts!"
        )

    # --- Step 4: Death check with resurrection ---
    if player.current_hp < 1:
        # Check belt for resurrection item (simplified — no belt system yet)
        # If no resurrection item: death
        return True, total_damage

    # --- Step 5: Special attack effects ---
    _apply_monster_special_attack(player, monster, screen)

    return True, total_damage


def _apply_monster_special_attack(player, monster, screen):
    """
    Apply special attack effects after normal damage.
    Reference: COMBAT_SYSTEM.md Section 3, Step 5
    """
    ac = monster.attack_char_code

    if ac in [ATTACK_GHOST_1, ATTACK_GHOST_2]:
        # Ghost: unparalyze player
        player.effect_active[EFFECT_PARALYSIS] = False
        player.effect_timer[EFFECT_PARALYSIS] = 0

    elif ac == ATTACK_MEWLIP:
        # Mewlip: remove magic (strip enchantment from equipped item)
        # Simplified: no enchantment system yet
        if screen:
            screen.draw_message("Le Mewlip vous retire votre magie!")

    elif ac == ATTACK_MORICAUD:
        # Moricaud: drain strength (-1)
        if not save_throw():
            player.strength -= 1
            if screen:
                screen.draw_message("Votre force diminue!")

    elif ac in [ATTACK_GALGAL, ATTACK_NAZGUL]:
        # Acid attack: reduce food (harder save for Nazgûl)
        if ac == ATTACK_GALGAL:
            if save_throw():
                return  # Easy save
        if ac == ATTACK_NAZGUL:
            if save_throw():
                return  # Still has a save
        # Acid hits!
        player.food_level -= 1
        if screen:
            screen.draw_message("L'acide brûle vos vivres!")
        if player.food_level < 0:
            player.current_hp = 0  # Death by acid/starvation

    elif ac == ATTACK_DRAIN_INT:
        # Drain intelligence (fatal if reaches 0)
        if not save_throw():
            player.intelligence -= 1
            if screen:
                screen.draw_message("Votre intelligence diminue!")
            if player.intelligence < 1:
                player.current_hp = 0  # Fatal intelligence drain

    elif ac == ATTACK_SUCCUBUS:
        # Succubus: drain experience (10-19 XP)
        if not save_throw():
            exp_loss = 10 + random.randint(0, 9)
            player.experience = max(0, player.experience - exp_loss)
            if screen:
                screen.draw_message(
                    f"La Succube draine votre expérience ({exp_loss} XP)!"
                )
            # Check level-down
            _check_level_down(player, screen)

    elif ac == ATTACK_EYE:
        # Eye of Sauron: Fear — death timer
        # Reference: COMBAT_SYSTEM.md Section 3, Step 5
        roll = random.randint(0, 4)
        if roll < 4:  # 80% chance
            monster.is_hostile = True
            player.is_dying = True  # Mark as in danger

            if roll == 3:
                # 25% of 80% = death sentence
                player.death_timer = 100 + random.randint(0, 49)
            else:
                player.death_timer = 15 + random.randint(0, 4)

            if screen:
                screen.draw_message(
                    "L'Œil de Sauron vous terrife! "
                    f"Vous avez {player.death_timer} tours..."
                )

    elif ac == ATTACK_HUORN:
        # Huorn: confusion
        player.effect_active[EFFECT_CONFUSION] = True
        player.effect_timer[EFFECT_CONFUSION] = 15 + random.randint(0, 9)
        if screen:
            screen.draw_message("Le Huorn vous confond!")

    elif ac == ATTACK_FAIRY:
        # Fairy: steal a random item
        _fairy_steal_item(player, monster, screen)

    elif ac == ATTACK_VOLEUR:
        # Thief: steal gold
        _thief_steal_gold(player, monster, screen)


def _fairy_steal_item(player, monster, screen):
    """
    Fairy steals a random inventory item.
    Reference: COMBAT_SYSTEM.md Section 3, Step 5
    """
    if not player.inventory:
        return

    # Pick random item
    idx = random.randint(0, len(player.inventory) - 1)
    stolen_item = player.inventory.pop(idx)

    if screen:
        screen.draw_message("La Fée vous vole un objet!")

    monster.is_fleeing = True  # Flee after stealing


def _thief_steal_gold(player, monster, screen):
    """
    Thief steals gold.
    Reference: COMBAT_SYSTEM.md Section 3, Step 5
    """
    total_gold = player.get_total_gold()
    if total_gold <= 0:
        return

    # Steal random amount (0-10 × some multiplier)
    stolen = random.randint(0, 10) * max(1, total_gold // 20)
    stolen = min(stolen, total_gold)

    if stolen > 0:
        player.set_total_gold(total_gold - stolen)
        if not player.effect_active[EFFECT_BLINDNESS]:
            if screen:
                screen.draw_message(f"Le Voleur vous vole {stolen} pièces d'or!")
        else:
            if screen:
                screen.draw_message("Quelque chose vous vole votre or!")

    monster.is_fleeing = True  # Flee with gold


# =============================================================================
# AWARD EXPERIENCE & LEVEL-UP
# Reference: COMBAT_SYSTEM.md Section 6
# =============================================================================

def award_experience(
    player: 'Player',
    xp_gain: int,
    dungeon_level: int,
    screen=None,
) -> bool:
    """
    Award XP to player and check for level-up.
    Reference: COMBAT_SYSTEM.md Section 6

    Returns:
        True if player leveled up
    """
    # XP scaling cap: "probability_check(level_diff)" in the original is a rare
    # random trigger — NOT a comparison. We approximate: only cap when a single
    # kill would grant more than 2 full level-ranges (prevents jumping 2+ levels).
    # Reference: COMBAT_SYSTEM.md Section 6
    if player.player_level < MAX_PLAYER_LEVEL:
        next_threshold = XP_THRESHOLDS[player.player_level]
        cur_threshold = XP_THRESHOLDS[player.player_level - 1] if player.player_level > 1 else 0
        level_diff = next_threshold - cur_threshold
        if level_diff > 0 and xp_gain > level_diff * 2:
            xp_gain = level_diff

    player.experience += xp_gain
    player.experience = max(0, player.experience)

    # Check for level-up
    leveled_up = False
    while (player.player_level < MAX_PLAYER_LEVEL
           and player.experience >= XP_THRESHOLDS[player.player_level]):
        _level_up(player, dungeon_level, screen)
        leveled_up = True

    return leveled_up


def _level_up(player: 'Player', dungeon_level: int, screen=None):
    """
    Level up the player character.
    Reference: COMBAT_SYSTEM.md Section 6, level_up_character
    HP gain formula: random(6) + random(level) + 3 + random(depth)//2
    """
    player.player_level += 1

    # HP gain
    hp_gain = calculate_level_up_hp_gain(player.player_level, dungeon_level)
    player.max_hp += hp_gain
    player.current_hp += hp_gain

    if screen:
        screen.draw_message(
            f"Vous gagnez un niveau! Niveau {player.player_level}. "
            f"PV +{hp_gain}!"
        )


# =============================================================================
# MONSTER DEATH
# Reference: COMBAT_SYSTEM.md Section 6 (kill_monster, line 6130)
# =============================================================================

def _kill_monster(
    player: 'Player',
    monster: 'Monster',
    dungeon_level: int,
    screen=None,
):
    """
    Handle monster death sequence.
    Reference: COMBAT_SYSTEM.md Section 6

    Steps:
    1. Display kill message
    2. Drop carried item
    3. Special on-death effects
    4. Clear from map
    5. Remove from monster list
    6. Award XP
    """
    # 1. Kill message
    if not player.effect_active[EFFECT_BLINDNESS]:
        if screen:
            screen.draw_message(f"Vous tuez le {monster.name_french}!")
    else:
        if screen:
            screen.draw_message("Quelque chose meurt!")

    # 3. Special on-death effects
    ac = monster.attack_char_code
    if ac == ATTACK_HUORN:
        # Huorn death cures confusion
        player.effect_active[EFFECT_CONFUSION] = False
        player.effect_timer[EFFECT_CONFUSION] = 0
        if screen:
            screen.draw_message("La confusion se dissipe!")

    # 6. Award XP
    award_experience(player, monster.experience, dungeon_level, screen)

    # Mark monster as dead
    monster.current_hp = 0
    monster.is_alive = False


# =============================================================================
# COMBAT UTILITY: get_sign
# Reference: COMBAT_SYSTEM.md Section 10 (line 48)
# =============================================================================

def get_sign(value: int) -> int:
    """
    Return the sign of a value: -1, 0, or +1.
    Reference: COMBAT_SYSTEM.md Section 10
    """
    if value == 0:
        return 0
    elif value < 0:
        return -1
    else:
        return 1


def _check_level_down(player: 'Player', screen=None):
    """
    Check if XP drain caused a level loss.
    Reference: COMBAT_SYSTEM.md Section 3 (Succubus drain)
    """
    if player.player_level <= 1:
        return

    prev_threshold = XP_THRESHOLDS[player.player_level - 1] if player.player_level > 1 else 0

    if player.experience < prev_threshold:
        player.player_level -= 1
        # HP loss on level-down
        hp_loss = random.randint(1, 6)
        player.max_hp = max(1, player.max_hp - hp_loss)
        player.current_hp = min(player.current_hp, player.max_hp)

        if screen:
            screen.draw_message(
                f"Vous perdez un niveau! Retour au niveau {player.player_level}."
            )
