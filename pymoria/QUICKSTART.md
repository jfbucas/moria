# PyMoria - Quick Start Guide

## Installation

```bash
cd /home/edo/prog/moria2014/moria/pymoria
python3 main.py
```

No dependencies needed! Python 3 with curses (standard on Linux).

## Controls

### Movement
- **hjkl** or **8246** (numpad) - Move in 4 directions
- **yubn** or **7913** (numpad) - Move diagonally

### Actions
- **i** - Show inventory
- **d** - Drop item
- **e** - Equip/wear item
- **q** - Quaff (drink) potion
- **r** - Read scroll
- **>** - Descend stairs (go deeper)
- **<** - Ascend stairs (go up)

### Other
- **?** - Help screen
- **Q** - Quit game
- **S** - Save game (TODO)

## Game Mechanics

### Stats
- **Force (Strength)**: Melee damage
- **Dextérité (Dexterity)**: Armor class
- **Constitution**: Hit points
- **Intelligence/Sagesse/Charisme**: Magic and interactions

### Resources
- **HP (Hit Points)**: Health - don't let it reach 0!
- **Nourriture (Food)**: Decreases over time - eat or starve!
- **Or (Gold)**: Money from monsters and treasure

### Combat
- Walk into a monster to attack it
- Damage based on weapon and strength
- Monster retaliates immediately
- Kill monsters for experience and gold

### Items
- **Weapons (`)`)**: Increase attack damage
- **Armor ([)**: Decrease armor class (lower is better)
- **Potions (!)**: Various magical effects
- **Scrolls (?)**: Magical spells
- **Rings (=)**: Passive bonuses
- **Food (%)**: Restore satiation

### Dungeon
- **16 levels deep** - reach the bottom to win!
- **Procedurally generated** - different every time
- **Monsters get stronger** as you descend
- **Find stairs (< >)** to move between levels

## Tips

1. **Don't forget to eat!** Food depletes every 10 turns
2. **Explore carefully** - stronger monsters appear deeper
3. **Equip better gear** as you find it
4. **Save potions** for emergencies
5. **Run from tough monsters** early on
6. **Check your stats** frequently (bottom status line)

## Status Effects

- **Aveugle (Blind)**: Can't see the map
- **Confus (Confused)**: Movement is randomized
- **Paralysé (Paralyzed)**: Can't move
- **Empoisonné (Poisoned)**: Take damage over time
- **Rapide (Hasted)**: Move twice as fast

## French Terms

The game preserves the original French text:

- **Niveau**: Level
- **Nourriture**: Food/Satiation
- **Or**: Gold
- **CA**: Armor Class
- **Vous êtes mort**: You are dead
- **Inventaire**: Inventory
- **Escalier**: Stairs

## Winning

Descend all 16 levels and defeat the final boss to win!

Good luck, adventurer!
