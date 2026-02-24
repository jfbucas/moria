#!/usr/bin/env python3
"""Test monster list and movement."""

from data.monsters import MONSTERS, get_monster_by_level
from game.dungeon import Dungeon

print("=== Monster List from Manual ===")
print(f"Total monsters: {len(MONSTERS)}\n")

for monster in MONSTERS:
    print(f"  {monster.char} - {monster.name:20s} | Level {monster.level:2d} | XP: {monster.experience:3d} | HP: {monster.hp:3d} | Damage: {monster.damage}")

print("\n=== Monster Distribution by Level ===")
for level in [1, 3, 5, 8, 10, 12, 15]:
    monsters_for_level = [get_monster_by_level(level).name for _ in range(10)]
    unique = set(monsters_for_level)
    print(f"  Level {level:2d}: {', '.join(sorted(unique))}")

print("\n=== Test Monster Movement ===")
dungeon = Dungeon(level=1)
print(f"  Generated {len(dungeon.monsters)} monsters")

if len(dungeon.monsters) > 0:
    print(f"  First monster: {dungeon.monsters[0]['template'].name} at ({dungeon.monsters[0]['x']}, {dungeon.monsters[0]['y']})")
    print("  ✅ Monsters spawned successfully")
else:
    print("  ❌ No monsters spawned!")

# Check monster types
monster_types = [m['template'].name for m in dungeon.monsters]
print(f"\n  Monster types in level 1: {set(monster_types)}")
