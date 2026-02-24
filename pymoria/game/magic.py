"""
Magic System for PyMoria — Potions, Wands, Scrolls, Identification
Reference: reverse/MAGIC_SYSTEM.md

Functions:
  use_potion(potion, player, level, dungeon_level, screen)
  use_wand(wand, player, target_monster, level, dungeon_level, screen)
  use_scroll(scroll, player, level, dungeon_level, screen)
  identify_item(item)
  is_item_identified(item_type, subtype)
  unidentify_all(player)
"""

import random
from typing import Optional

from game.entities import Player, Item, Monster, DungeonLevel, ITEM_POTION, ITEM_SCROLL, ITEM_WAND, ITEM_RING
from utils.constants import (
    EFFECT_BLINDNESS, EFFECT_CONFUSION, EFFECT_FEAR,
    EFFECT_PARALYSIS, EFFECT_POISON, EFFECT_SPEED_BOOST,
    EFFECT_SLOW, EFFECT_PROTECTION, EFFECT_DETECT_MONSTERS,
    EFFECT_DETECT_OBJECTS, EFFECT_INVISIBILITY, EFFECT_INFRAVISION,
    EFFECT_WIZARD_MODE,
    MAP_WIDTH, MAP_HEIGHT,
)


# =============================================================================
# ITEM IDENTIFICATION TABLES
# Reference: MAGIC_SYSTEM.md Section 5
# Index formula: type * 0x18 + subtype
# Two parallel tables (primary + secondary).
# =============================================================================

_identified_table: dict = {}   # type*0x18+subtype → True
_alt_check_table: dict = {}    # secondary ID flag


def _id_key(item_type: int, subtype: int) -> int:
    """Compute identification table index (matches DOS formula)."""
    return item_type * 0x18 + subtype


def is_item_identified(item_type: int, subtype: int) -> bool:
    """Return True if this item type/subtype is globally identified."""
    key = _id_key(item_type, subtype)
    return _identified_table.get(key, False) or _alt_check_table.get(key, False)


def identify_item(item: Item):
    """
    Mark an item as identified (both instance flag and global table).
    Reference: MAGIC_SYSTEM.md Section 5 (Identification on Equip)
    """
    item.is_identified = True
    _identified_table[_id_key(item.type, item.subtype)] = True


def unidentify_all(player: Player):
    """
    Clear all identification tables and unidentify all inventory items.
    Called by Amnesia potion.
    Reference: MAGIC_SYSTEM.md Section 1 (subtype 7)
    """
    global _identified_table, _alt_check_table

    # Unidentify type tables for potions(1), scrolls(2), wands(3), rings(4)
    for item_type in (ITEM_POTION, ITEM_SCROLL, ITEM_WAND, ITEM_RING):
        for subtype in range(25):
            key = _id_key(item_type, subtype)
            _identified_table[key] = False
            _alt_check_table[key] = False

    # Unidentify all items in inventory
    for item in player.inventory:
        item.is_identified = False

    # Unidentify wielded weapon and worn armor
    if player.wielded_weapon:
        player.wielded_weapon.is_identified = False
    if player.worn_armor:
        player.worn_armor.is_identified = False


def _auto_identify_potion(potion: Item):
    """
    Auto-identify certain potions on use.
    Reference: MAGIC_SYSTEM.md Section 5 (Potion Auto-ID Exceptions)
    """
    AUTO_ID_SUBTYPES = {5, 6, 8, 9, 10, 12, 17, 18, 21, 22}
    if potion.subtype in AUTO_ID_SUBTYPES:
        identify_item(potion)


# =============================================================================
# HELPERS
# =============================================================================

def _msg(screen, text: str):
    """Display a message if screen is available."""
    if screen:
        screen.draw_message(text)


def _set_effect(player: Player, effect_idx: int, duration: int):
    """Activate a timed effect on the player."""
    player.effect_active[effect_idx] = True
    player.effect_timer[effect_idx] = duration


def _clear_effect(player: Player, effect_idx: int):
    """Deactivate a timed effect on the player."""
    player.effect_active[effect_idx] = False
    player.effect_timer[effect_idx] = 0


def _find_random_floor(level: DungeonLevel) -> Optional[tuple]:
    """Find a random empty floor tile position on the level."""
    empties = []
    for row in range(MAP_HEIGHT):
        for col in range(MAP_WIDTH):
            if level.get_tile(col, row) == ' ':
                if level.get_monster_at(col, row) is None:
                    empties.append((col, row))
    if empties:
        return random.choice(empties)
    return None


def _teleport_player(player: Player, level: DungeonLevel, screen):
    """Teleport player to a random empty floor tile."""
    pos = _find_random_floor(level)
    if pos:
        player.x, player.y = pos
        _msg(screen, "Vous vous téléportez!")


def _level_up_player(player: Player, dungeon_level: int, screen):
    """Award one character level to the player."""
    from game.combat import _level_up
    _level_up(player, dungeon_level, screen)


def _level_down_player(player: Player, screen):
    """Remove one character level from the player."""
    if player.player_level <= 1:
        _msg(screen, "Vous ne pouvez pas perdre plus de niveaux!")
        return

    player.player_level -= 1
    # Reset XP to the threshold of the new level
    player.experience = Player.get_xp_for_level(player.player_level)
    _msg(screen, f"Vous perdez un niveau! Niveau {player.player_level}")


# =============================================================================
# POTIONS
# Reference: MAGIC_SYSTEM.md Section 1
# Subtypes 1-24, matching POTION_EFFECTS in data/items.py
# ALL potions add 200+random(100) food before their specific effect.
# =============================================================================

def use_potion(potion: Item, player: Player, level: DungeonLevel,
               dungeon_level: int = 1, screen=None):
    """
    Apply potion effect to player.
    Reference: MAGIC_SYSTEM.md Section 1 (drink_potion_effect)

    ALL potions first add food: 200 + random(100)
    CRITICAL: Use exact formulas from MAGIC_SYSTEM.md.
    """
    # Always add food first
    player.food_level += 200 + random.randint(0, 99)

    sub = potion.subtype

    # --- 1: Healing ---
    if sub == 1:
        if player.current_hp >= player.max_hp:
            gain = 1 + random.randint(0, 5)
            player.max_hp += gain
            player.current_hp = player.max_hp
            _msg(screen, "Vous vous sentez plus résistant!")
        else:
            heal = player.player_level * 2 + random.randint(0, player.player_level * 3 - 1)
            player.current_hp = min(player.current_hp + heal, player.max_hp)
            _msg(screen, "Vous vous sentez mieux!")

    # --- 2: Extra-healing ---
    elif sub == 2:
        if player.current_hp >= player.max_hp:
            gain = 1 + random.randint(0, 14)
            player.max_hp += gain
            player.current_hp = player.max_hp
            _msg(screen, "Vous vous sentez beaucoup plus résistant!")
        else:
            player.current_hp = player.max_hp
            _msg(screen, "Vous vous sentez complètement guéri!")
        # Cure blindness
        if player.effect_active[EFFECT_BLINDNESS]:
            _clear_effect(player, EFFECT_BLINDNESS)
            _msg(screen, "Vous voyez à nouveau!")

    # --- 3: Constitution (food restore) ---
    elif sub == 3:
        restore = player.food_level // 3 + random.randint(1, 4)
        player.food_level = min(player.food_level + restore, 6000)
        player.max_hp += 1
        _msg(screen, "Vous vous sentez constitué!")

    # --- 4: Strength (full food) ---
    elif sub == 4:
        player.food_level = 6000
        player.strength = min(player.strength + random.randint(1, 4), 255)
        _msg(screen, "Vous vous sentez plus fort!")

    # --- 5: Confusion (speed boost 100-149 turns) ---
    elif sub == 5:
        duration = 100 + random.randint(0, 49)
        _set_effect(player, EFFECT_SPEED_BOOST, duration)
        _msg(screen, "Vous vous sentez plus rapide!")

    # --- 6: Poison (acid damage: -1d3-1 food, fatal at 0) ---
    elif sub == 6:
        damage = random.randint(1, 3) + 1
        player.food_level -= damage
        _msg(screen, "Vous êtes empoisonné!")
        if player.food_level <= 0:
            player.food_level = 0
            player.current_hp -= random.randint(1, 5)
            _msg(screen, "Le poison vous ronge!")

    # --- 7: Amnesia (full detect + unidentify all) ---
    elif sub == 7:
        _set_effect(player, EFFECT_DETECT_MONSTERS, 50 + random.randint(0, 74))
        _set_effect(player, EFFECT_DETECT_OBJECTS,  50 + random.randint(0, 74))
        unidentify_all(player)
        _msg(screen, "Votre mémoire s'efface...")

    # --- 8: Paralysis (20-29 turn death timer from poison) ---
    elif sub == 8:
        timer = 20 + random.randint(0, 9)
        _set_effect(player, EFFECT_POISON, timer)
        player.death_timer = timer
        _msg(screen, "Vous êtes paralysé! Trouvez un antidote!")

    # --- 9: Speed boost → Paralyze OR cancel haste ---
    elif sub == 9:
        if player.effect_active[EFFECT_SPEED_BOOST]:
            # Cancel haste
            _clear_effect(player, EFFECT_SPEED_BOOST)
            _msg(screen, "Vous ralentissez!")
        else:
            duration = 10 + random.randint(0, 4)
            _set_effect(player, EFFECT_PARALYSIS, duration)
            _msg(screen, "Vous êtes paralysé!")

    # --- 10: Slow → Haste OR cancel paralysis ---
    elif sub == 10:
        if player.effect_active[EFFECT_PARALYSIS]:
            # Cancel paralysis
            _clear_effect(player, EFFECT_PARALYSIS)
            _msg(screen, "Vous pouvez bouger à nouveau!")
        else:
            duration = 30 + random.randint(0, 4)
            _set_effect(player, EFFECT_SPEED_BOOST, duration)
            _msg(screen, "Vous vous sentez plus rapide!")

    # --- 11: Hallucination (350-399 turns, -1 INT, fatal at 0) ---
    elif sub == 11:
        duration = 350 + random.randint(0, 49)
        _set_effect(player, EFFECT_CONFUSION, duration)
        player.intelligence = max(0, player.intelligence - 1)
        _msg(screen, "Vous hallucinez!")
        if player.intelligence <= 0:
            player.current_hp = 0
            _msg(screen, "Votre esprit s'effondre!")

    # --- 12: Blindness (200-299 turns) ---
    elif sub == 12:
        duration = 200 + random.randint(0, 99)
        _set_effect(player, EFFECT_BLINDNESS, duration)
        _msg(screen, "Vous êtes aveugle!")

    # --- 13: Nourishing (+500-599 food) ---
    elif sub == 13:
        player.food_level += 500 + random.randint(0, 99)
        _msg(screen, "Vous êtes rassasié!")

    # --- 14: Experience (gain 1 level) ---
    elif sub == 14:
        _level_up_player(player, dungeon_level, screen)
        _msg(screen, "Vous gagnez un niveau d'expérience!")

    # --- 15: Level drain (lose 1 level) ---
    elif sub == 15:
        _level_down_player(player, screen)

    # --- 16: Clairvoyance (detect timer 300-399 turns) ---
    elif sub == 16:
        duration = 300 + random.randint(0, 99)
        _set_effect(player, EFFECT_DETECT_MONSTERS, duration)
        _set_effect(player, EFFECT_DETECT_OBJECTS,  duration)
        _msg(screen, "Vous voyez tout!")

    # --- 17: Disorientation (teleport player) ---
    elif sub == 17:
        # Teleport duration 150-249 turns + immediate teleport
        _teleport_player(player, level, screen)
        _msg(screen, "Vous êtes désorienté!")

    # --- 18: Phase door (15-24 turns — allows passing walls) ---
    elif sub == 18:
        duration = 15 + random.randint(0, 9)
        # Use EFFECT_SLOW slot as phase-door proxy (no dedicated slot)
        _set_effect(player, EFFECT_SLOW, duration)
        _msg(screen, "Vous pouvez traverser les murs!")

    # --- 19: Levitation (100-149 turns) ---
    elif sub == 19:
        duration = 100 + random.randint(0, 49)
        _set_effect(player, EFFECT_INFRAVISION, duration)  # Levitation proxy
        _msg(screen, "Vous lévitez!")

    # --- 20: Thirst-quenching (+400-599 food) ---
    elif sub == 20:
        player.food_level += 400 + random.randint(0, 199)
        _msg(screen, "Vous n'avez plus soif!")

    # --- 21: Invisibility (25-39 turns) ---
    elif sub == 21:
        duration = 25 + random.randint(0, 14)
        _set_effect(player, EFFECT_INVISIBILITY, duration)
        _msg(screen, "Vous devenez invisible!")

    # --- 22: Gasification (wizard mode 25-39 turns + DESTROY inventory) ---
    elif sub == 22:
        player.is_wizard = True
        duration = 25 + random.randint(0, 14)
        _set_effect(player, EFFECT_WIZARD_MODE, duration)

        # Destroy all non-equipped, non-food, non-light items
        to_destroy = []
        for item in player.inventory:
            keep = item.is_equipped
            # Keep food with quantity 1
            if item.type == 0 and item.count == 1:  # ITEM_FOOD
                keep = True
            # Keep wielded weapon and worn armor references
            if item is player.wielded_weapon or item is player.worn_armor:
                keep = True
            if not keep:
                to_destroy.append(item)

        for item in to_destroy:
            player.inventory.remove(item)

        _msg(screen, "Vous vous gasifiez! Votre sac est détruit!")

    # --- 23: Dexterity → gains +1 Strength ---
    elif sub == 23:
        player.strength = min(player.strength + 1, 255)
        _msg(screen, "Vous vous sentez plus fort!")

    # --- 24: Regeneration (learn spell from food item) ---
    elif sub == 24:
        # Consume one food item from inventory
        food_item = None
        for item in player.inventory:
            if item.type == 0:  # ITEM_FOOD
                food_item = item
                break

        if food_item is None:
            _msg(screen, "Vous n'avez pas de nourriture!")
        else:
            food_item.count -= 1
            if food_item.count <= 0:
                player.inventory.remove(food_item)
            _msg(screen, "Vous apprenez un nouveau sort!")
            # (Spell slot system not yet fully implemented)

    _auto_identify_potion(potion)


# =============================================================================
# WANDS
# Reference: MAGIC_SYSTEM.md Section 2
# Subtypes 1-22, matching WAND_EFFECTS in data/items.py
# Each use consumes 1 charge (item.power).
# target_monster is None for environment-targeting wands.
# =============================================================================

def use_wand(wand: Item, player: Player,
             target_monster: Optional[Monster],
             level: DungeonLevel,
             dungeon_level: int = 1, screen=None):
    """
    Apply wand effect.
    Reference: MAGIC_SYSTEM.md Section 2

    Monster-targeting subtypes: 1,2,5,6,7,8,12,14,15,16,18,19,20,22
    Environment-targeting subtypes: 3,4,9,10,11,13,17,21
    """
    if wand.power <= 0:
        _msg(screen, "La baguette n'a plus de charges!")
        return

    sub = wand.subtype

    # ------------------------------------------------------------------ #
    # Monster-targeting wands                                             #
    # ------------------------------------------------------------------ #
    if target_monster is not None:
        m = target_monster

        # 1: Teleportation — teleport monster to random floor tile
        if sub == 1:
            pos = _find_random_floor(level)
            if pos:
                m.col, m.row = pos
            m.is_fleeing = False
            _msg(screen, f"{m.name_french} est téléporté!")

        # 2: Polymorph — pick random non-stationary template
        elif sub == 2:
            if not m.is_stationary:
                from data.monsters import MONSTER_TEMPLATES
                candidates = [t for t in MONSTER_TEMPLATES
                              if t is not None and not t.is_stationary]
                if candidates:
                    tmpl = random.choice(candidates)
                    m.char = tmpl.char
                    m.display_char = tmpl.char
                    m.attack_char_code = ord(tmpl.char) if len(tmpl.char) == 1 else 0
                    m.to_hit = tmpl.to_hit
                    m.armor_class = tmpl.armor_class
                    m.max_hp = tmpl.hit_points
                    m.current_hp = tmpl.hit_points
                    m.damage_per_attack = tmpl.damage_per_attack
                    m.num_attacks = tmpl.num_attacks
                    m.experience = tmpl.experience
                    m.is_fleeing = False
                    m.is_hostile = tmpl.is_hostile
                    m.status_timer = 0
                    m.name_french = tmpl.name_french
                    _msg(screen, f"Le monstre est métamorphosé!")

        # 5: Slow monster — wake/alert OR put to sleep
        elif sub == 5:
            if not m.is_awake:
                m.is_alerted = True
                m.status_timer = 10 + random.randint(0, 9) if not m.is_stationary \
                    else 5 + random.randint(0, 4)
                _msg(screen, f"{m.name_french} est alerté!")
            else:
                m.is_awake = False
                _msg(screen, f"{m.name_french} s'endort!")

        # 6: Haste monster — sleep OR remove alert
        elif sub == 6:
            if not m.is_alerted:
                m.is_awake = True
                m.status_timer = 10 + random.randint(0, 9)
                _msg(screen, f"{m.name_french} est accéléré!")
            else:
                m.is_alerted = False
                _msg(screen, f"{m.name_french} est désorienté!")

        # 7: Weakening — HP to 1/5; also hurts player
        elif sub == 7:
            if not m.is_stationary:
                m.current_hp = m.current_hp // 5 + 1
            else:
                m.current_hp = player.max_hp // 2 + 1

            player.current_hp = player.current_hp // 2 + 1
            _msg(screen, f"{m.name_french} est affaibli! Vous aussi!")

        # 8: Fear — make non-stationary monsters flee
        elif sub == 8:
            if not m.is_stationary:
                m.is_fleeing = True
                _msg(screen, f"{m.name_french} fuit!")

        # 12: Combat — damage based on player+dungeon level
        elif sub == 12:
            if not m.is_stationary:
                dmg_range = max(1, player.player_level + dungeon_level - 10)
                dmg = random.randint(0, dmg_range)
            else:
                dmg = random.randint(0, 10)

            m.current_hp -= dmg
            _msg(screen, f"La baguette frappe {m.name_french} pour {dmg} dégâts!")

            if m.current_hp <= 0:
                _kill_wand_monster(m, player, level, dungeon_level, screen)

        # 14: Sleep / Make Hostile — set hostile flag
        elif sub == 14:
            if not m.is_stationary:
                m.is_hostile = True
                m.is_awake = True
                _msg(screen, f"{m.name_french} devient hostile!")

        # 15: Paralyze — stun timer
        elif sub == 15:
            if not m.is_stationary:
                m.status_timer = 10 + random.randint(0, 6)
            else:
                m.status_timer = 2 + random.randint(0, 2)
            m.is_fleeing = False
            _msg(screen, f"{m.name_french} est paralysé!")

        # 16: Invisibility — make monster invisible
        elif sub == 16:
            m.is_invisible = True
            _msg(screen, f"{m.name_french} devient invisible!")

        # 18: Strengthening — heal both monster and player by half
        elif sub == 18:
            m.current_hp += player.current_hp // 2 + 1
            player.current_hp = player.current_hp // 2 + 1
            _msg(screen, "Vous renforcez le monstre... et lui aussi vous soigne!")

        # 19: Capricious — 50% good, 50% bad
        elif sub == 19:
            if random.randint(0, 1) == 1:
                # 50%: Monster to 1 HP, player healed
                if not m.is_stationary:
                    m.current_hp = 1
                heal = 1 + random.randint(0, player.max_hp - 1)
                player.current_hp = min(heal, player.max_hp)
                _msg(screen, "La magie capricieuse vous favorise!")
            else:
                # 50%: Restore monster HP, player to 1 HP
                m.current_hp = m.max_hp
                player.current_hp = 1
                _msg(screen, "La magie capricieuse vous trahit!")

        # 20: Illusion — change monster display char to random template
        elif sub == 20:
            from data.monsters import MONSTER_TEMPLATES
            candidates = [t for t in MONSTER_TEMPLATES
                          if t is not None and not t.is_stationary]
            if candidates:
                tmpl = random.choice(candidates)
                m.display_char = tmpl.char
            _msg(screen, "Le monstre change d'apparence!")

        # 22: Energy drain — reduce to_hit, damage monster, heal player
        elif sub == 22:
            if not m.is_stationary:
                reduction = random.randint(1, 3)
                m.to_hit = max(0, m.to_hit - reduction)
                dmg = random.randint(0, 9) * random.randint(1, 5)
            else:
                m.to_hit = max(0, m.to_hit - 1)
                dmg = random.randint(0, 9)

            m.current_hp -= dmg
            heal = random.randint(0, 9)
            player.current_hp = min(player.current_hp + heal, player.max_hp)
            _msg(screen, f"La baguette draine l'énergie de {m.name_french}!")

            if m.to_hit < 1 or m.current_hp <= 0:
                _kill_wand_monster(m, player, level, dungeon_level, screen)

    # ------------------------------------------------------------------ #
    # Environment-targeting wands (no monster target)                     #
    # ------------------------------------------------------------------ #
    else:
        # 3: Destruction — destroy targeted wall/door (not implemented fully)
        if sub == 3:
            _msg(screen, "La baguette détruit un obstacle!")

        # 4: Create walls / kill non-stationary monster at target
        elif sub == 4:
            _msg(screen, "La baguette crée un obstacle!")

        # 9: Dowsing — create trap tile at target
        elif sub == 9:
            _msg(screen, "La baguette crée un piège!")

        # 10: Summon monster — spawn monster near target
        elif sub == 10:
            _msg(screen, "Un monstre est invoqué!")

        # 11: Summon item — spawn random item at target
        elif sub == 11:
            _msg(screen, "Un objet est invoqué!")

        # 13: Fill traps — disarm trap tiles
        elif sub == 13:
            _msg(screen, "Les pièges sont détruits!")

        # 17: Create traps — place wall/trap tile
        elif sub == 17:
            _msg(screen, "Un piège est créé!")

        # 21: Purification — disarm trap at target
        elif sub == 21:
            _msg(screen, "Le piège est désarmé!")

    # Consume one charge
    wand.power -= 1
    if wand.power == 0:
        _msg(screen, "La baguette est épuisée.")


def _kill_wand_monster(monster: Monster, player: Player,
                       level: DungeonLevel, dungeon_level: int, screen):
    """Kill a monster hit by a wand effect and award XP."""
    from game.combat import award_experience
    monster.is_alive = False
    if monster in level.monsters:
        level.monsters.remove(monster)
    award_experience(player, monster.experience, dungeon_level, screen)
    _msg(screen, f"{monster.name_french} est tué!")


# =============================================================================
# SCROLLS
# Reference: MAGIC_SYSTEM.md Section 3
# Subtypes 0-24, matching SCROLL_EFFECTS in data/items.py
# Scroll usage includes a cast-failure check before the effect.
# =============================================================================

def _scroll_cast_check(scroll: Item, player: Player, screen) -> bool:
    """
    Roll for scroll cast success.
    Reference: MAGIC_SYSTEM.md Section 6 (check_spell_cast_chance)

    Success if: random(21) <= player_level // 2 + intelligence
    At normal INT (100), always succeeds.
    Only fails if INT has been heavily drained (e.g. Hallucination).
    Returns True on success.
    """
    roll = random.randint(0, 20)
    threshold = player.player_level // 2 + player.intelligence

    if threshold < roll:
        _msg(screen, "Vous avez échoué à lire le parchemin!")
        # Scroll may survive (simplified: always consumed on failure too)
        return False

    return True


def use_scroll(scroll: Item, player: Player, level: DungeonLevel,
               dungeon_level: int = 1, screen=None):
    """
    Apply scroll effect to player/level.
    Reference: MAGIC_SYSTEM.md Section 3 (execute_spell_effect)

    Cast failure check: roll(0-20) vs (player_level//2 + intelligence).
    Scroll is consumed after use (caller is responsible for removal).
    """
    if not _scroll_cast_check(scroll, player, screen):
        return

    sub = scroll.subtype

    # --- 0: Enchant armor/shield/ring (+1, max +5) ---
    if sub == 0:
        if player.worn_armor and player.worn_armor.power < 5:
            player.worn_armor.power += 1
            player.worn_armor.is_cursed = False
            player.base_ac = max(player.base_ac, player.worn_armor.power)
            _msg(screen, "Votre armure brille!")
        else:
            _msg(screen, "Rien à enchanter.")

    # --- 1: Protect armor (rust-proof) ---
    elif sub == 1:
        if player.worn_armor:
            player.worn_armor.is_cursed = False  # "is_enchanted" proxy
            _msg(screen, "Votre armure est maintenant protégée!")
        else:
            _msg(screen, "Vous ne portez pas d'armure.")

    # --- 2: Enchant weapon (+1 power, +1 constitution, max power 10) ---
    elif sub == 2:
        if player.wielded_weapon:
            if player.wielded_weapon.power < 10:
                player.wielded_weapon.power += 1
            player.wielded_weapon.is_cursed = False
            player.strength = min(player.strength + 1, 255)
            _msg(screen, "Votre arme brille!")
        else:
            _msg(screen, "Vous ne tenez pas d'arme.")

    # --- 3: Map reveal — explore entire current level ---
    elif sub == 3:
        _msg(screen, "La carte se révèle!")
        # (Full map reveal requires dungeon renderer integration;
        #  mark detection active as proxy)
        _set_effect(player, EFFECT_DETECT_MONSTERS, 200)
        _set_effect(player, EFFECT_DETECT_OBJECTS,  200)

    # --- 4: Identify — mark one item as identified ---
    elif sub == 4:
        identified_something = False
        for item in player.inventory:
            if not item.is_identified:
                identify_item(item)
                _msg(screen, f"Vous identifiez: {item}")
                identified_something = True
                break
        if not identified_something:
            _msg(screen, "Tout est déjà identifié.")

    # --- 5: Teleport player ---
    elif sub == 5:
        _teleport_player(player, level, screen)

    # --- 6: Hyper-teleport (level warp — stub, full impl needs level manager) ---
    elif sub == 6:
        new_level = random.randint(1, 19)
        _msg(screen, f"Vous êtes téléporté au niveau {new_level}!")
        # (Full implementation requires game state access — flagged for game_loop)
        player.dungeon_level = new_level

    # --- 7: Summon monster near player ---
    elif sub == 7:
        _msg(screen, "Un monstre est invoqué!")
        # (Full implementation requires monster spawning system — stub)

    # --- 8: Protection (temporary AC boost) ---
    elif sub == 8:
        bonus = 1 + random.randint(0, 4)
        player.base_ac += bonus
        duration = 50 + random.randint(0, 49)
        _set_effect(player, EFFECT_PROTECTION, duration)
        _msg(screen, f"Vous êtes protégé! (+{bonus} CA)")

    # --- 9: Detect magic items ---
    elif sub == 9:
        duration = 100 + random.randint(0, 49)
        _set_effect(player, EFFECT_DETECT_OBJECTS, duration)
        _msg(screen, "Vous détectez les objets magiques!")

    # --- 10: Detect food ---
    elif sub == 10:
        _set_effect(player, EFFECT_DETECT_OBJECTS, 50 + random.randint(0, 24))
        _msg(screen, "Vous détectez la nourriture!")

    # --- 11: Detect monsters ---
    elif sub == 11:
        duration = 50 + random.randint(0, 49)
        _set_effect(player, EFFECT_DETECT_MONSTERS, duration)
        _msg(screen, "Vous détectez les monstres!")

    # --- 12: Detect gold ---
    elif sub == 12:
        _set_effect(player, EFFECT_DETECT_OBJECTS, 50 + random.randint(0, 24))
        _msg(screen, "Vous détectez l'or!")

    # --- 13: Enchantment (complex; simplified to HP boost) ---
    elif sub == 13:
        heal = random.randint(5, 15)
        player.current_hp = min(player.current_hp + heal, player.max_hp)
        _msg(screen, "Un charme vous enveloppe!")

    # --- 14: Sleep monsters — put all awake monsters to sleep ---
    elif sub == 14:
        count = 0
        for m in level.monsters:
            if m.is_awake and m.is_alive and not m.is_stationary:
                m.is_awake = False
                m.is_alerted = False
                count += 1
        _msg(screen, f"{count} monstre(s) s'endorment!")

    # --- 15: Blank — no effect ---
    elif sub == 15:
        _msg(screen, "Le parchemin est vierge.")

    # --- 16: Remove curses — uncurse all equipped items ---
    elif sub == 16:
        count = 0
        for item in player.inventory:
            if item.is_cursed and item.is_equipped:
                item.is_cursed = False
                count += 1
        if player.wielded_weapon and player.wielded_weapon.is_cursed:
            player.wielded_weapon.is_cursed = False
            count += 1
        if player.worn_armor and player.worn_armor.is_cursed:
            player.worn_armor.is_cursed = False
            count += 1
        _msg(screen, f"{count} malédiction(s) levée(s)!")

    # --- 17: Demolition (targeted wall destruction — stub) ---
    elif sub == 17:
        _msg(screen, "Une explosion démolît les murs!")

    # --- 18: Mass destruction (area effect — stub) ---
    elif sub == 18:
        _msg(screen, "Une explosion massive!")

    # --- 19: Scare monsters — make all visible monsters flee ---
    elif sub == 19:
        count = 0
        for m in level.monsters:
            if m.is_alive and not m.is_stationary:
                m.is_fleeing = True
                m.status_timer = 15 + random.randint(0, 9)
                count += 1
        _msg(screen, f"{count} monstre(s) fuient!")

    # --- 20: Scatter (teleport all monsters to random positions) ---
    elif sub == 20:
        count = 0
        for m in level.monsters:
            if m.is_alive and not m.is_stationary:
                pos = _find_random_floor(level)
                if pos:
                    m.col, m.row = pos
                    count += 1
        _msg(screen, f"{count} monstre(s) éparpillé(s)!")

    # --- 21: Enchant ring (+1 power to first ring in inventory) ---
    elif sub == 21:
        for item in player.inventory:
            if item.type == ITEM_RING:
                if item.power < 5:
                    item.power += 1
                    item.is_cursed = False
                    _msg(screen, "Votre anneau brille!")
                else:
                    _msg(screen, "L'anneau est déjà au maximum!")
                break
        else:
            _msg(screen, "Vous ne portez pas d'anneau.")

    # --- 22: Degrade ring (-1 power to first ring in inventory) ---
    elif sub == 22:
        for item in player.inventory:
            if item.type == ITEM_RING:
                item.power -= 1
                _msg(screen, "Votre anneau s'affaiblit!")
                break
        else:
            _msg(screen, "Vous ne portez pas d'anneau.")

    # --- 23: Intelligence (+1 INT, permanent stat increase) ---
    elif sub == 23:
        player.intelligence = min(player.intelligence + 1, 255)
        _msg(screen, "Vous vous sentez plus intelligent!")

    # Identify the scroll on successful use
    identify_item(scroll)
