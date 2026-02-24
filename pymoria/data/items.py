"""
Item Templates for PyMoria
Based on reverse/ENTITY_DATABASE.md Sections 6-13
Item appearance randomization, potion colors, wand woods, scroll names
"""

import random
from typing import List


# =============================================================================
# POTION COLORS (24 colors, randomized at game start)
# Reference: ENTITY_DATABASE.md Section 6
# =============================================================================

# Master list of 24 potion colors (French)
POTION_COLORS_MASTER = [
    "rouge",         # 1 - red
    "blanche",       # 2 - white
    "gludure",       # 3 - viscous
    "brune",         # 4 - brown
    "verte",         # 5 - green
    "noire",         # 6 - black
    "fluorescente",  # 7 - fluorescent
    "argentee",      # 8 - silver
    "orange",        # 9 - orange
    "violette",      # 10 - violet
    "incolore",      # 11 - colorless
    "mordoree",      # 12 - golden-brown
    "bleue",         # 13 - blue
    "mauve",         # 14 - mauve
    "rose",          # 15 - pink
    "grise",         # 16 - gray
    "jaune",         # 17 - yellow
    "chinée",        # 18 - mottled
    "cuivrée",       # 19 - copper
    "moirée",        # 20 - shimmering
    "beige",         # 21 - beige
    "dorée",         # 22 - golden
    "multicolore",   # 23 - multicolored
    "albatre",       # 24 - alabaster
]

# Randomized table (shuffled at game start)
POTION_COLORS_RANDOMIZED = POTION_COLORS_MASTER.copy()


# Potion effects (French names)
# Reference: ENTITY_DATABASE.md Section 6
POTION_EFFECTS = [
    None,                           # 0 - unused
    "de guérison",                  # 1 - Healing
    "d'extra-guérison",             # 2 - Extra-healing
    "de constitution",              # 3 - Constitution
    "de force",                     # 4 - Strength
    "de confusion",                 # 5 - Confusion
    "empoisonnée",                  # 6 - Poison
    "amnésiante",                   # 7 - Amnesia
    "paralysante",                  # 8 - Paralysis
    "accélérante",                  # 9 - Speed boost
    "ralentissante",                # 10 - Slow
    "hallucinogène",                # 11 - Hallucination
    "aveuglante",                   # 12 - Blindness
    "nourrissante",                 # 13 - Nourishing
    "d'expérience",                 # 14 - Experience
    "de perte de niveau",           # 15 - Level drain
    "d'extralucidité",              # 16 - Clairvoyance
    "de désorientation",            # 17 - Disorientation
    "passe muraille",               # 18 - Pass-through-walls
    "de lévitation",                # 19 - Levitation
    "désaltérante",                 # 20 - Thirst-quenching
    "d'invisibilité",               # 21 - Invisibility
    "gazéifiante",                  # 22 - Gasification
    "de dexterité",                 # 23 - Dexterity
    "de régénération",              # 24 - Regeneration
]


# =============================================================================
# WAND WOODS (22 woods, randomized at game start)
# Reference: ENTITY_DATABASE.md Section 9
# =============================================================================

# Master list of 22 wand woods (French)
WAND_WOODS_MASTER = [
    "de chêne",         # 1 - oak
    "de peuplier",      # 2 - poplar
    "de teck",          # 3 - teak
    "de saule",         # 4 - willow
    "de merisier",      # 5 - cherry
    "de châtaigner",    # 6 - chestnut
    "de frêne",         # 7 - ash
    "de noisetier",     # 8 - hazel
    "de charme",        # 9 - hornbeam
    "de cerisier",      # 10 - cherry tree
    "d'acajou",         # 11 - mahogany
    "de pin",           # 12 - pine
    "d'olivier",        # 13 - olive
    "d'érable",         # 14 - maple
    "de platane",       # 15 - sycamore
    "d'if",             # 16 - yew
    "de hêtre",         # 17 - beech
    "d'orme",           # 18 - elm
    "de bambou",        # 19 - bamboo
    "de verre",         # 20 - glass
    "de rose noire",    # 21 - black rose
    "de roseau",        # 22 - reed
]

# Randomized table (shuffled at game start, 21 used according to doc)
WAND_WOODS_RANDOMIZED = WAND_WOODS_MASTER[:21].copy()


# Wand effects (French names)
# Reference: ENTITY_DATABASE.md Section 9
WAND_EFFECTS = [
    None,                               # 0 - unused
    "de téléportation",                 # 1 - Teleportation
    "de transmorphie",                  # 2 - Polymorph
    "de destruction",                   # 3 - Destruction
    "pour créer des murs",              # 4 - Create walls
    "de ralentissement de monstre",     # 5 - Slow monster
    "d'accélération de monstre",        # 6 - Haste monster
    "d'affaiblissement",                # 7 - Weakening
    "pour effrayer",                    # 8 - Fear
    "de sourcier",                      # 9 - Dowsing
    "d'invocation de monstre",          # 10 - Summon monster
    "d'invocation d'objet",             # 11 - Summon item
    "de combat",                        # 12 - Combat
    "pour combler les trappes",         # 13 - Fill traps
    "assoupissante",                    # 14 - Sleep
    "paralysante",                      # 15 - Paralyze
    "d'invisibilité",                   # 16 - Invisibility
    "de création de trappes",           # 17 - Create traps
    "de renforcement",                  # 18 - Strengthening
    "capricieuse",                      # 19 - Capricious
    "d'illusion",                       # 20 - Illusion
    "de purification",                  # 21 - Purification
    "d'absorption d'énergie",           # 22 - Energy drain
]


# =============================================================================
# RING MATERIALS (19 materials, randomized at game start)
# Reference: ENTITY_DATABASE.md Section 8
# =============================================================================

# Master list of 19 ring materials (French)
RING_MATERIALS_MASTER = [
    "d'or",          # 1 - gold
    "d'argent",      # 2 - silver
    "de platine",    # 3 - platinum
    "de jaspe",      # 4 - jasper
    "de rubis",      # 5 - ruby
    "de saphir",     # 6 - sapphire
    "d'onyx",        # 7 - onyx
    "d'opale",       # 8 - opal
    "d'ivoire",      # 9 - ivory
    "de diamant",    # 10 - diamond
    "d'émeraude",    # 11 - emerald
    "de bronze",     # 12 - bronze
    "de jade",       # 13 - jade
    "de mithril",    # 14 - mithril
    "d'os",          # 15 - bone
    "d'adamantite",  # 16 - adamantite
    "d'agathe",      # 17 - agate
    "de cristal",    # 18 - crystal
    "d'étain",       # 19 - tin
]

# Randomized table (shuffled at game start)
RING_MATERIALS_RANDOMIZED = RING_MATERIALS_MASTER.copy()


# Ring effects (French names)
# Reference: ENTITY_DATABASE.md Section 8
RING_EFFECTS = [
    "d'intelligence",               # 0 - Intelligence
    "pour protéger son armure",     # 1 - Protect armor
    "pour conserver sa force",      # 2 - Sustain strength
    "pour ralentir sa digestion",   # 3 - Slow digestion
    "d'augmentation des dégats",    # 4 - Damage boost
    "de téléportation",             # 5 - Teleportation
    "d'invisibilité",               # 6 - Invisibility
    "de protection",                # 7 - Protection
    "d'identification",             # 8 - Identification
    "de régénération",              # 9 - Regeneration
    "de détection de trappes",      # 10 - Trap detection
    "de monstres",                  # 11 - Monster detect
    "coupe doigt",                  # 12 - Finger-cutter
    "anti feu",                     # 13 - Fire resist
    "de chute de plume",            # 14 - Feather fall
    "de résurrection",              # 15 - Resurrection
    "de nage",                      # 16 - Swimming
    "de rayon X",                   # 17 - X-ray vision
    "de lévitation",                # 18 - Levitation
    "de faiblesse",                 # 19 - Weakness
]


# =============================================================================
# SCROLL NAMES (25 scrolls, procedurally generated)
# Reference: ENTITY_DATABASE.md Section 7
# =============================================================================

# Scroll names are random 4-9 character gibberish strings
# Generated once at game start
SCROLL_NAMES_RANDOMIZED = []


def generate_scroll_names():
    """
    Generate 25 random scroll names (4-9 characters of gibberish)
    Called once at game start
    """
    global SCROLL_NAMES_RANDOMIZED
    SCROLL_NAMES_RANDOMIZED = []

    # Characters to use for gibberish (avoid confusing chars)
    chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    for _ in range(25):
        length = random.randint(4, 9)
        name = ''.join(random.choice(chars) for _ in range(length))
        SCROLL_NAMES_RANDOMIZED.append(name)


# Scroll effects (French names)
# Reference: ENTITY_DATABASE.md Section 7
SCROLL_EFFECTS = [
    "de régénération",                  # 0 - Regeneration
    "pour enchanter les armures",       # 1 - Enchant armor
    "pour protéger les armures",        # 2 - Protect armor
    "pour enchanter son arme",          # 3 - Enchant weapon
    "topographique",                    # 4 - Map reveal
    "d'identification",                 # 5 - Identify
    "de teleportation",                 # 6 - Teleport
    "d'hyper téléportation",            # 7 - Hyper-teleport
    "pour invoquer un monstre",         # 8 - Summon monster
    "de protection",                    # 9 - Protection
    "pour détecter la magie",           # 10 - Detect magic
    "pour détecter la nouriture",       # 11 - Detect food
    "pour repérer les monstres",        # 12 - Detect monsters
    "pour détecter l'or",               # 13 - Detect gold
    "d'ensorcellement",                 # 14 - Enchantment
    "de sommeil",                       # 15 - Sleep
    "vierge",                           # 16 - Blank
    "pour enlever les sorts",           # 17 - Remove curses
    "de démolition",                    # 18 - Demolition
    "de destruction",                   # 19 - Destruction
    "pour effrayer les monstres",       # 20 - Scare monsters
    "d'éparpillement",                  # 21 - Scatter
    "pour enchanter les anneaux",       # 22 - Enchant rings
    "de dégradation d'anneaux",         # 23 - Degrade rings
    "d'intelligence",                   # 24 - Intelligence
]


# =============================================================================
# GEM NAMES (10 gems, randomized at game start)
# Reference: ENTITY_DATABASE.md Section 13
# =============================================================================

GEM_NAMES_MASTER = [
    "un rubis",         # 1 - ruby
    "une émeraude",     # 2 - emerald
    "un diamant",       # 3 - diamond
    "un topaze",        # 4 - topaz
    "un saphir",        # 5 - sapphire
    "une agathe",       # 6 - agate
    "une améthyste",    # 7 - amethyst
    "un chrysobéryl",   # 8 - chrysoberyl
    "une turquoise",    # 9 - turquoise
    "une opale",        # 10 - opal
]

GEM_NAMES_RANDOMIZED = GEM_NAMES_MASTER.copy()


# =============================================================================
# RANDOMIZATION FUNCTIONS
# =============================================================================

def randomize_all_item_appearances():
    """
    Randomize all item appearance tables at game start
    Called once when starting a new game
    Reference: ENTITY_DATABASE.md Section 13
    """
    global POTION_COLORS_RANDOMIZED, WAND_WOODS_RANDOMIZED
    global RING_MATERIALS_RANDOMIZED, GEM_NAMES_RANDOMIZED

    # Shuffle potion colors (24 colors)
    POTION_COLORS_RANDOMIZED = POTION_COLORS_MASTER.copy()
    random.shuffle(POTION_COLORS_RANDOMIZED)

    # Shuffle wand woods (22 master, use 21)
    WAND_WOODS_RANDOMIZED = WAND_WOODS_MASTER[:21].copy()
    random.shuffle(WAND_WOODS_RANDOMIZED)

    # Shuffle ring materials (19 materials)
    RING_MATERIALS_RANDOMIZED = RING_MATERIALS_MASTER.copy()
    random.shuffle(RING_MATERIALS_RANDOMIZED)

    # Shuffle gem names (10 gems)
    GEM_NAMES_RANDOMIZED = GEM_NAMES_MASTER.copy()
    random.shuffle(GEM_NAMES_RANDOMIZED)

    # Generate random scroll names (25 scrolls, 4-9 char gibberish)
    generate_scroll_names()


def get_potion_name(subtype: int, identified: bool = False) -> str:
    """Get potion name (randomized color or identified effect)"""
    if identified and 1 <= subtype <= 24:
        return f"potion {POTION_EFFECTS[subtype]}"
    elif 1 <= subtype <= 24:
        color = POTION_COLORS_RANDOMIZED[subtype - 1]
        return f"potion {color}"
    return "potion"


def get_wand_name(subtype: int, identified: bool = False) -> str:
    """Get wand name (randomized wood or identified effect)"""
    if identified and 1 <= subtype <= 22:
        return f"baguette {WAND_EFFECTS[subtype]}"
    elif 1 <= subtype <= 21:
        wood = WAND_WOODS_RANDOMIZED[subtype - 1]
        return f"baguette {wood}"
    return "baguette"


def get_ring_name(subtype: int, identified: bool = False) -> str:
    """Get ring name (randomized material or identified effect)"""
    if identified and 0 <= subtype <= 19:
        return f"anneau {RING_EFFECTS[subtype]}"
    elif 0 <= subtype <= 18:
        material = RING_MATERIALS_RANDOMIZED[subtype]
        return f"anneau {material}"
    return "anneau"


def get_scroll_name(subtype: int, identified: bool = False) -> str:
    """Get scroll name (random gibberish or identified effect)"""
    if identified and 0 <= subtype <= 24:
        return f"parchemin {SCROLL_EFFECTS[subtype]}"
    elif 0 <= subtype <= 24:
        if subtype < len(SCROLL_NAMES_RANDOMIZED):
            return f"parchemin '{SCROLL_NAMES_RANDOMIZED[subtype]}'"
        return "parchemin"
    return "parchemin"


# =============================================================================
# WEAPON AND ARMOR TEMPLATES (Fixed names, no randomization)
# Reference: ENTITY_DATABASE.md Sections 10-11
# =============================================================================

ARMOR_NAMES = [
    None,                           # 0 - unused
    "une armure de cuir",           # 1 - Leather armor
    "une armure de cuir renforcé",  # 2 - Studded leather
    "une cotte de mailles",         # 3 - Chainmail
    "une armure de fer",            # 4 - Iron armor
    "une cuirasse d'acier",         # 5 - Steel breastplate
    "une armure de Mithril",        # 6 - Mithril armor
    "un heaume",                    # 7 - Helm
    "une cape elfique",             # 8 - Elven cloak
    "des gantelets de dextérité",   # 9 - Gauntlets of dexterity
    "des gantelets de maladresse",  # 10 - Gauntlets of clumsiness
    "des gantelets de force",       # 11 - Gauntlets of strength
]

WEAPON_NAMES = [
    None,                       # 0 - unused
    "un poignard",              # 1 - Dagger
    "une dague",                # 2 - Stiletto
    "une lance",                # 3 - Spear
    "une massue",               # 4 - Mace
    "un sabre",                 # 5 - Saber
    "un cimeterre",             # 6 - Scimitar
    "une épée",                 # 7 - Sword
    "une épée à deux mains",    # 8 - Two-handed sword
    "une épée elfique",         # 9 - Elven sword
    "une hache",                # 10 - Axe
    "un arc",                   # 11 - Bow
    "fleche",                   # 12 - Arrow
    "une dague elfique",        # 13 - Elven dagger
    "une épée de glace",        # 14 - Ice sword
    "une épée vampirique",      # 15 - Vampiric sword
]

# Weapon base attack values (0-7)
WEAPON_BASE_ATTACK = [0, 1, 1, 2, 3, 4, 5, 5, 6, 7, 6, 1, 0, 4, 5, 5]


# =============================================================================
# LIGHT SOURCE NAMES
# Reference: ENTITY_DATABASE.md Section 12
# =============================================================================

LIGHT_SOURCE_EFFECTS = [
    None,                   # 0 - unused
    "de chance",            # 1 - Luck
    "de dessèchement",      # 2 - Desiccation
    "de monstres",          # 3 - Monster detect
    "d'annulation",         # 4 - Cancellation
    "de faim",              # 5 - Hunger
    "de force",             # 6 - Strength
    "de régénération",      # 7 - Regeneration
    "de vulnérabilité",     # 8 - Vulnerability
    "d'antimagie",          # 9 - Antimagic
    "d'expérience",         # 10 - Experience
]
