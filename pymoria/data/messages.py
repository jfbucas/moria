"""
Message Catalog for PyMoria (French)
Based on reverse/MORIA_COMPLETE.md Section 5
All messages in French (CP850 encoding in original, UTF-8 in Python)
"""

# =============================================================================
# FOOD STATUS MESSAGES
# Reference: PLAYER_ACTIONS.md Section 3
# =============================================================================

FOOD_STATUS = {
    'full': "Rassasié",      # Full (5001+)
    'normal': "Normal",       # Normal (3001-5000)
    'weak': "Faible",        # Weak (1501-3000)
    'hungry': "Affamé",      # Hungry (1-1500)
    'dying': "Mourant"       # Dying (≤0)
}

# =============================================================================
# DEATH MESSAGES
# Reference: SHOP_AND_UI.md Section 4
# =============================================================================

DEATH_MESSAGES = {
    'e': "Mort de faim",                # Died of starvation
    'f': "Paradoxe temporel",           # Time paradox
    'g': "Sorti de Moria",              # Escaped from Moria (VICTORY)
    'Q': "Abandon",                      # Quit (not recorded)
    'fall': "Mort en tombant",          # Died from fall damage
    'poison': "Mort empoisonné",        # Died poisoned
    'combat': "Tué au combat"           # Killed in combat
}

# =============================================================================
# CRITICAL GAME MESSAGES
# Reference: MORIA_COMPLETE.md Section 5.1
# =============================================================================

MSG_DEATH = "Vous êtes mort!"                           # You are dead!
MSG_RIP = "Repose en paix..."                          # Rest in peace...
MSG_VICTORY = "Félicitations!"                         # Congratulations!
MSG_ESCAPED = "Vous êtes sorti de Moria!"             # You escaped from Moria!
MSG_SAVE_QUIT = "Sauvegarder et quitter?"             # Save and quit?
MSG_QUIT_NO_SAVE = "Quitter sans sauvegarder?"       # Quit without saving?

# =============================================================================
# INVENTORY MESSAGES
# =============================================================================

MSG_INVENTORY = "Inventaire:"                          # Inventory:
MSG_EMPTY_INVENTORY = "Votre inventaire est vide"     # Your inventory is empty
MSG_DROP_WHAT = "Jeter quel objet? (1-9)"             # Drop which item?
MSG_YOU_DROP = "Vous jetez:"                          # You drop:
MSG_NOTHING_TO_DROP = "Vous n'avez rien à jeter"     # You have nothing to drop
MSG_CURSED = "L'objet est maudit!"                    # The item is cursed!
MSG_IDENTIFIED = "Vous identifiez l'objet"            # You identify the object
MSG_ALREADY_IDENTIFIED = "Déjà identifié"             # Already identified

# =============================================================================
# FOOD & EATING MESSAGES
# =============================================================================

MSG_NO_FOOD = "Vous n'avez pas de nourriture"        # You have no food
MSG_EAT_FOOD = "Vous mangez la nourriture"           # You eat the food
MSG_FOOD_SPOILED = "La nourriture est avariée"       # Food is spoiled

# =============================================================================
# COMBAT MESSAGES
# =============================================================================

MSG_MISS = "Vous manquez"                             # You miss
MSG_HIT = "Vous touchez"                              # You hit
MSG_CRITICAL = "Coup critique!"                       # Critical hit!
MSG_MONSTER_MISS = "Le monstre manque"                # The monster misses
MSG_MONSTER_HIT = "Le monstre vous touche"           # The monster hits you

# =============================================================================
# MOVEMENT & EXPLORATION MESSAGES
# =============================================================================

MSG_WALL = "Vous vous cognez contre un mur"          # You bump into a wall
MSG_DOOR_LOCKED = "La porte est fermée"              # The door is locked
MSG_TRAP = "Un piège!"                                # A trap!
MSG_STAIRS_DOWN = "Descendre?"                        # Go down?
MSG_STAIRS_UP = "Monter?"                             # Go up?
MSG_CANT_GO_UP = "Vous ne pouvez pas monter"         # You cannot go up
MSG_FALL_DAMAGE = "Vous vous blessez en descendant"  # You hurt yourself going down

# =============================================================================
# DIRECTION PROMPT
# =============================================================================

MSG_WHICH_DIRECTION = "Quelle direction?"             # Which direction?

# =============================================================================
# TIMED EFFECT EXPIRATION MESSAGES
# Reference: PLAYER_ACTIONS.md Section 7
# =============================================================================

EFFECT_EXPIRE_MESSAGES = {
    0: "Vous voyez à nouveau",                        # Blindness - You can see again
    1: "Vous n'êtes plus confus",                    # Confusion - You are no longer confused
    2: "Vous n'avez plus peur",                      # Fear - You are no longer afraid
    3: "Vous pouvez bouger à nouveau",               # Paralysis - You can move again
    4: "Le poison s'estompe",                        # Poison - The poison fades
    5: "Vous ralentissez",                           # Speed - You slow down
    6: "Vous accélérez",                             # Slow - You speed up
    7: "Votre protection disparaît",                 # Protection - Your protection fades
    8: "Vous perdez la détection",                   # Detect Monsters - You lose detection
    9: "Vous perdez la détection",                   # Detect Objects - You lose detection
    10: "Vous redevenez visible",                    # Invisibility - You become visible
    11: "L'infravision s'estompe",                   # Infravision - Infravision fades
    12: "Vous redevenez normal"                      # Wizard Mode - You return to normal
}

# =============================================================================
# SHOP MESSAGES
# =============================================================================

MSG_SHOP_PROMPT = "Boutique 1 ou 2?"                 # Shop 1 or 2?
MSG_NOT_ENOUGH_GOLD = "Vous n'avez pas assez d'or"  # You don't have enough gold
MSG_PURCHASE = "Vous achetez:"                       # You buy:

# =============================================================================
# HIGH SCORE MESSAGES
# =============================================================================

MSG_HIGH_SCORES = "Table des scores"                  # Score table
MSG_LEVEL = "Niveau"                                  # Level
MSG_SCORE = "Score"                                   # Score
MSG_GOLD = "Or:"                                      # Gold:

# =============================================================================
# STARVATION MESSAGES
# =============================================================================

MSG_STARVING = "Vous mourez de faim"                 # You die of starvation
MSG_TIME_PARADOX = "Le temps vous consume"           # Time consumes you

# =============================================================================
# MAGIC EFFECT MESSAGES
# =============================================================================

MSG_POTION_DRINK = "Vous buvez la potion"            # You drink the potion
MSG_SCROLL_READ = "Vous lisez le parchemin"          # You read the scroll
MSG_WAND_ZAP = "Vous utilisez la baguette"           # You use the wand
MSG_SPELL_CAST = "Vous lancez un sort"               # You cast a spell

# =============================================================================
# ERROR MESSAGES
# =============================================================================

MSG_ERROR_GENERAL = "Erreur"                          # Error
MSG_ITEM_NOT_FOUND = "Objet introuvable"             # Item not found
MSG_INVALID_COMMAND = "Commande invalide"            # Invalid command

# =============================================================================
# MISCELLANEOUS MESSAGES
# =============================================================================

MSG_PRESS_KEY = "Appuyez sur une touche..."          # Press a key...
MSG_MORE = "-- Plus --"                               # -- More --
MSG_WAIT = "Vous attendez"                           # You wait
MSG_REST = "Vous vous reposez..."                    # You rest...
MSG_RESTED = "Vous êtes reposé"                      # You are rested

# =============================================================================
# MAIN MENU MESSAGES
# =============================================================================

MENU_TITLE = "MORIA (TM) Version 1.9.8.7"
MENU_COPYRIGHT = "Copyright AJM86"
MENU_HELP = "[E] Explications sur le jeu"           # Explanations about the game
MENU_SCORES = "[S] Table des scores"                # Score table
MENU_START = "[Entrée] Commencer"                   # Start

# =============================================================================
# CHARACTER CREATION MESSAGES
# =============================================================================

MSG_ENTER_NAME = "Entrez votre nom:"                 # Enter your name
MSG_ALLOCATE_STATS = "Répartissez vos points de caractéristiques"  # Allocate stats
MSG_FORCE = "Force"                                   # Strength
MSG_DEXTERITE = "Dextérité"                          # Dexterity
MSG_INTELLIGENCE = "Intelligence"                     # Intelligence

# =============================================================================
# WELCOME MESSAGE
# =============================================================================

MSG_WELCOME = "Vous allez entrer dans le labyrinthe de la Moria."  # You will enter the Moria labyrinth
MSG_DIGGING = "Wait a little minute, while I dig the Moria..."

# =============================================================================
# MESSAGE LOOKUP HELPER
# =============================================================================

def get_message(msg_id: str) -> str:
    """
    Get message by ID (for compatibility with original message system)
    """
    # This is a simplified version - original used numeric IDs
    # with complex offset calculations
    message_map = {
        '0x1a2': MSG_DEATH,
        '0x1a3': MSG_RIP,
        '0x19f': MSG_VICTORY,
        '0x1a0': MSG_SAVE_QUIT,
        '0x1a1': MSG_QUIT_NO_SAVE,
        '0x76': MSG_YOU_DROP,
        '0xbd': MSG_EMPTY_INVENTORY,
        '0x19': MSG_NO_FOOD,
        '0x1d': MSG_NOTHING_TO_DROP,
        '0x1f': MSG_ALREADY_IDENTIFIED,
        '0x9c': MSG_IDENTIFIED,
        '0x9d': MSG_DROP_WHAT,
        '0x9f': MSG_WHICH_DIRECTION,
        '0x1a5': MSG_CURSED,
        '0xc5': MSG_EAT_FOOD,
        '0xb6': MSG_INVENTORY,
    }
    return message_map.get(msg_id, MSG_ERROR_GENERAL)

# =============================================================================
# ENCODING NOTE
# =============================================================================
"""
Original encoding: CP850 (DOS French)
Python encoding: UTF-8

CP850 character mappings used in original:
0x82 = é
0x85 = à
0x88 = ê
0x83 = â

These are represented directly as UTF-8 in this file.
"""
