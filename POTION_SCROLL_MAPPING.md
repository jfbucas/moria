# Moria - Complete Potion & Scroll Mapping
## Extracted from Memory Dump (French Version)

---

## 🧪 Complete Potion List (In Order from Memory Dump)

Based on extraction from `reverse/memory.dump` at offset 0x2a967:

| # | French Name | English Translation | Effect Code | Duration/Notes |
|---|-------------|---------------------|-------------|----------------|
| 1 | de guérison | of healing | POTION_HEAL (1) | Heal HP (modest) |
| 2 | d'extra-guérison | of extra healing | POTION_GREATER_HEAL (2) | Heal HP (full) |
| 3 | de constitution | of constitution | ? | Increase constitution |
| 4 | de force | of strength | POTION_STRENGTH (23) | Increase strength |
| 5 | de confusion | of confusion | ? | Causes confusion |
| 6 | empoisonnée | poisoned | ? | Poison effect |
| 7 | amnésiante | of amnesia | ? | Memory loss |
| 8 | paralysante | paralyzing | POTION_PARALYZE (9) | Paralyze (10-15 turns) |
| 9 | accélérante | accelerating | POTION_SPEED (5) or POTION_HASTE (10) | Speed boost |
| 10 | ralentissante | slowing | ? | Slowing effect |
| 11 | hallucinogène | hallucinogenic | POTION_HALLUCINATION (11) | Hallucination (350-400 turns) |
| 12 | aveuglante | blinding | POTION_BLINDNESS (12) | Blindness (200-300 turns) |
| 13 | nourrissante | nourishing | POTION_STAMINA (3) | Increase food/stamina |
| 14 | d'expérience | of experience | POTION_GAIN_LEVEL (14) | Gain experience level |
| 15 | de perte de niveau | of level loss | POTION_LOSE_LEVEL (15) | Lose experience level |
| 16 | d'extralucidité | of clairvoyance | POTION_DETECT_MONSTERS (7) | Detect monsters (50-125 turns) |
| 17 | de désorientation | of disorientation | ? | Disorientation |
| 18 | passe muraille | pass through walls | ? | Ethereal/ghostly |
| 19 | de lévitation | of levitation | ? | Levitation (see ITEM_LEVITATION 0x12) |
| 20 | désaltérante | thirst quenching | POTION_RESTORE_FOOD (4) | Restore food/satiation |
| 21 | d'invisibilité | of invisibility | POTION_EFFECT_16/17/18 (?) | Invisibility |
| 22 | gazifiante | gasifying | ? | Unknown gas effect |

---

## 📜 Complete Scroll List (In Order from Memory Dump)

Based on extraction from `reverse/memory.dump` at offset ~0x2abe6:

| # | French Name | English Translation | Effect Code | Notes |
|---|-------------|---------------------|-------------|-------|
| 1 | de dextérité | of dexterity | ? | Increase dexterity |
| 2 | de régénération | of regeneration | ? | Regeneration |
| 3 | pour enchanter les armures | to enchant armors | ? | Enchant armor |
| 4 | pour protéger les armures | to protect armors | ? | Protect armor |
| 5 | pour enchanter son arme | to enchant one's weapon | ? | Enchant weapon |
| 6 | topographique | topographic | SPELL_REVEAL_MAP (5) | Reveal map |
| 7 | d'identification | of identification | SPELL_IDENTIFY_ONE (11) | Identify item |
| 8 | de téléportation | of teleportation | SPELL_TELEPORT (6) | Teleport |
| 9 | d'hyper téléportation | of hyper teleportation | ? | Major teleport |
| 10 | pour invoquer un monstre | to summon a monster | SPELL_SUMMON (9) | Summon monster |
| 11 | de protection | of protection | ? | Protection spell |
| 12 | pour détecter la magie | to detect magic | ? | Detect magic |
| 13 | pour détecter la nourriture | to detect food | ? | Detect food |
| 14 | pour repérer les ... | to locate the ... | ? | Detection scroll |
| 15 | de démolition | of demolition | ? | Destroy walls |
| 16 | de destruction | of destruction | ? | Destruction |
| 17 | pour effrayer les monstres | to frighten monsters | ? | Fear monsters |
| 18 | d'éparpillement | of scattering | ? | Scatter/disperse |
| 19 | pour enchanter les anneaux | to enchant rings | ? | Enchant ring |
| 20 | de dégradation d'anneaux | of ring degradation | ? | Curse ring |

---

## 📝 Effect Messages (What Happens When You Use Items)

### Potion Effects

| French Message | English Translation | Context |
|----------------|---------------------|---------|
| Vous vous sentez plus fort. Whaoo! Quels muscles!.. | You feel stronger. Wow! What muscles!.. | Strength potion |
| Vous vous sentez plus calme, maintenant. | You feel calmer now. | Calm/peace potion |
| Vous vous sentez vraiment en pleine forme ! | You feel really great! | Full healing |
| Miam, en voilà une bonne potion ! | Yum, that's a good potion! | Food/nourishing potion |
| Un lourd voile de ténèbres s'abat sur vous. | A heavy veil of darkness falls upon you. | Blindness |

### Scroll Effects

| French Message | English Translation | Context |
|----------------|---------------------|---------|
| Le parchemin disparait dans un nuage de fumée... | The scroll disappears in a cloud of smoke... | Reading scroll |
| Il faut être un très bon magicien, pour lancer un sort avec ça. | You must be a very good wizard to cast a spell with this. | Spell failure |

### Questions/Prompts

| French Message | English Translation |
|----------------|---------------------|
| Quelle potion voulez-vous boire ? | Which potion do you want to drink? |
| Quel parchemin voulez-vous lire ? | Which scroll do you want to read? |
| Et où voulez-vous que je trouve une potion ? | And where do you want me to find a potion? |

---

## 🔍 Updated Potion Effect Enum

Based on memory dump analysis, here's the corrected enum:

```c
typedef enum {
    POTION_HEAL         = 1,    // de guérison - Heal HP (modest)
    POTION_GREATER_HEAL = 2,    // d'extra-guérison - Heal HP (full)
    POTION_STAMINA      = 3,    // nourrissante - Increase food/stamina
    POTION_RESTORE_FOOD = 4,    // désaltérante - Restore food to maximum
    POTION_SPEED        = 5,    // accélérante - Speed boost (100-150 turns)
    POTION_UNKNOWN_6    = 6,    // ??? - Unknown effect
    POTION_DETECT_MONSTERS = 7, // d'extralucidité - Detect monsters (50-125 turns)
    POTION_UNKNOWN_8    = 8,    // ??? - Unknown effect
    POTION_PARALYZE     = 9,    // paralysante - Paralyze or remove haste (10-15 turns)
    POTION_HASTE        = 10,   // accélérante - Haste or cure paralysis (30-35 turns)
    POTION_HALLUCINATION = 11,  // hallucinogène - Hallucination (350-400 turns)
    POTION_BLINDNESS    = 12,   // aveuglante - Blindness (200-300 turns)
    POTION_GAIN_TURNS   = 13,   // ??? - Gain 500+ turns
    POTION_GAIN_LEVEL   = 14,   // d'expérience - Gain experience level
    POTION_LOSE_LEVEL   = 15,   // de perte de niveau - Lose experience level
    POTION_EFFECT_16    = 16,   // d'invisibilité? - Unknown (300-400 turns)
    POTION_TELEPORT     = 17,   // de téléportation? - Teleport (150-250 turns)
    POTION_EFFECT_18    = 18,   // ??? - Unknown (15-25 turns)
    POTION_EFFECT_19    = 19,   // ??? - Unknown (100-150 turns)
    POTION_UNKNOWN_20   = 20,   // ??? - Unknown effect
    POTION_EFFECT_21    = 21,   // ??? - Unknown (25-40 turns)
    POTION_WIZARD_MODE  = 22,   // ??? - Wizard mode (25-40 turns)
    POTION_STRENGTH     = 23,   // de force - Increase strength (permanent)
} PotionEffect;
```

---

## 🗺️ Additional Findings

### Potions Not Yet Mapped to Effects:
- **de constitution** - Likely increases constitution stat
- **de confusion** - Causes confusion (different from hallucination)
- **empoisonnée** - Poison potion
- **amnésiante** - Memory loss/amnesia
- **ralentissante** - Slowing potion
- **de désorientation** - Disorientation
- **passe muraille** - Pass through walls/ethereal
- **de lévitation** - Levitation (might be item, not consumable?)
- **gazifiante** - Gas/gasifying effect

### Scrolls to Research:
Most scrolls appear to be standard roguelike fare:
- Enchant weapons/armor/rings
- Protection/detection spells
- Map revealing
- Monster manipulation (summon, frighten, scatter)

---

## 🎯 Next Steps for Complete Reverse Engineering

1. **Map remaining potion effects** - Effects 6, 8, 13, 16-21 need names
2. **Correlate with code behavior** - Match French names to actual in-game effects
3. **Extract monster data** - Memory dump likely contains monster names/stats
4. **Extract item data** - Weapon/armor descriptions
5. **Build complete game database** - All items, monsters, spells, potions

---

## 📚 Translation Reference

### Common French Game Terms:
- **potion** = potion
- **parchemin** = scroll/parchment
- **boire** = to drink
- **lire** = to read
- **guérison** = healing
- **force** = strength/force
- **nourrissante** = nourishing
- **aveuglante** = blinding
- **enchanter** = to enchant
- **invoquer** = to summon
- **téléportation** = teleportation

---

**Generated**: 2026-02-08
**Source**: reverse/memory.dump (736KB French Moria binary)
**Extraction Method**: Pascal string parsing (length byte + data)
