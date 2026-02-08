#!/usr/bin/python3
"""
Analyze drink_potion_effect to document all timer and flag addresses
"""
import re

# Read the function
with open('reverse/MORIA_final_constants.C', 'r') as f:
    content = f.read()

# Extract drink_potion_effect function
func_match = re.search(
    r'void drink_potion_effect.*?\{(.*?)^(?=\w)',
    content,
    re.DOTALL | re.MULTILINE
)

if not func_match:
    print("ERROR: Could not find drink_potion_effect")
    exit(1)

func_body = func_match.group(0)

# Find all potion effect cases
potion_effects = {}
current_effect = None
current_code = []

for line in func_body.split('\n'):
    # Check for effect ID
    effect_match = re.match(r'\s*if \(iVar4 == (0x[0-9a-f]+|\d+)\)', line)
    if effect_match:
        if current_effect is not None:
            potion_effects[current_effect] = '\n'.join(current_code)
        current_effect = effect_match.group(1)
        current_code = [line]
    elif current_effect is not None:
        current_code.append(line)
        # Check for end of effect
        if 'goto LAB_1000_d16b' in line or 'else if' in line:
            potion_effects[current_effect] = '\n'.join(current_code)
            current_effect = None
            current_code = []

# Analyze each effect for memory addresses
print("="*80)
print("POTION EFFECT MEMORY ADDRESS ANALYSIS")
print("="*80)

address_usage = {}

for effect_id, code in sorted(potion_effects.items(), key=lambda x: int(x[0], 0) if x[0].startswith('0x') else int(x[0])):
    # Find all memory addresses
    addresses = re.findall(r'\*\([^*]*\)(0xb[89][0-9a-f][0-9a-f])', code)

    # Find flag assignments (= 1 or = 0)
    flags_set = re.findall(r'\*\([^*]*\)(0xb[89][0-9a-f][0-9a-f])[^=]*=\s*[01]\b', code)

    # Find timer assignments (= some calculation)
    timers_set = re.findall(r'\*\([^*]*\)(0xb[89][0-9a-f][0-9a-f])[^=]*=.*random', code)

    # Find messages displayed
    messages = re.findall(r'display_score_with_fatal\((0x[0-9a-f]+|\d+)\)', code)

    if addresses or flags_set or timers_set:
        effect_num = int(effect_id, 0) if effect_id.startswith('0x') else int(effect_id)
        print(f"\nEffect {effect_num} ({effect_id}):")
        if messages:
            print(f"  Messages: {', '.join(messages)}")

        if flags_set:
            print(f"  Flags set: {set(flags_set)}")
            for addr in set(flags_set):
                if addr not in address_usage:
                    address_usage[addr] = []
                address_usage[addr].append(f"Effect {effect_num} (flag)")

        if timers_set:
            print(f"  Timers set: {set(timers_set)}")
            for addr in set(timers_set):
                if addr not in address_usage:
                    address_usage[addr] = []
                address_usage[addr].append(f"Effect {effect_num} (timer)")

print("\n" + "="*80)
print("ADDRESS USAGE SUMMARY")
print("="*80)

for addr in sorted(address_usage.keys()):
    print(f"\n{addr}:")
    for usage in address_usage[addr]:
        print(f"  - {usage}")

# Check for food/mana references
print("\n" + "="*80)
print("FOOD vs MANA ANALYSIS")
print("="*80)

food_refs = re.findall(r'(.*0xb874[^\n]*)', func_body)
print(f"\nReferences to 0xb874 (labeled 'current_mana'):")
for ref in food_refs[:10]:
    print(f"  {ref.strip()[:100]}")

print(f"\nReferences to 0xb876 (labeled 'max_mana'):")
mana_refs = re.findall(r'(.*0xb876[^\n]*)', func_body)
for ref in mana_refs[:10]:
    print(f"  {ref.strip()[:100]}")

# Check effect 3 and 4 (stamina/food related)
if '3' in potion_effects:
    print("\nEffect 3 (Stamina/Food increase):")
    print(potion_effects['3'][:500])

if '4' in potion_effects:
    print("\nEffect 4 (Restore Food):")
    print(potion_effects['4'][:500])
