#!/usr/bin/python3
"""
Improved function namer with better heuristics and French->English translation
"""
import json
import re
from collections import Counter

# Translation dictionary for common French game terms
TRANSLATIONS = {
    # Actions
    'monte': 'move_up',
    'descend': 'move_down',
    'descendre': 'move_down',
    'droite': 'move_right',
    'gauche': 'move_left',
    'attaque': 'attack',
    'tue': 'kill',
    'tuer': 'kill',
    'frapper': 'hit',
    'manger': 'eat',
    'boire': 'drink',
    'lire': 'read',
    'ramasse': 'pickup',
    'trouve': 'find',
    'trouver': 'find',
    'attendre': 'wait',

    # Entities
    'chauve souris': 'bat',
    'souris': 'mouse',
    'araignee': 'spider',
    'serpent': 'snake',
    'gobelin': 'goblin',
    'orc': 'orc',
    'crebain': 'crebain',

    # Items
    'potion': 'potion',
    'parchemin': 'scroll',
    'anneau': 'ring',
    'pierre': 'stone',
    'arc': 'bow',
    'silmarils': 'silmaril',

    # UI/Game states
    'initialization': 'init',
    'personnage': 'character',
    'standard': 'std',
    'explication': 'help',
    'jeu': 'game',
    'intelligence': 'intelligence',
    'force': 'strength',
    'abandon': 'quit',
    'commencer': 'start',
    'jouer': 'play',
    'encore': 'more',
    'espace': 'space',
    'enter': 'enter',
    'menu': 'menu',
    'aide': 'help',
    'niveau': 'level',
}

def translate_and_simplify(text):
    """Translate French context to English and simplify"""
    text = text.lower()

    # Common patterns to extract key actions
    patterns = [
        # Movement + combat
        (r'(monte|descend|droite|gauche).*?(attaque|tue).*?(chauve souris|araignee|serpent|gobelin|orc)', 'combat'),
        # Item usage
        (r'(lire|boire|manger).*(parchemin|potion)', 'use_item'),
        # Item pickup
        (r'(ramasse|trouve).*(potion|parchemin|anneau|pierre)', 'find_item'),
        # Character creation
        (r'personnage.*standard', 'char_create'),
        # Initialization
        (r'initialization', 'init'),
        # Help/explanation
        (r'explication.*jeu', 'show_help'),
        # Level change
        (r'change.*niveau', 'change_level'),
        # Movement only
        (r'^(monte|descend|droite|gauche)$', 'move'),
        # Wait/idle
        (r'attendre', 'wait'),
        # Quit
        (r'abandon', 'quit'),
    ]

    for pattern, category in patterns:
        if re.search(pattern, text):
            return category

    # If no pattern matched, try word-by-word translation
    words = text.split()
    translated = []
    for word in words:
        # Try to find translation
        for fr, en in TRANSLATIONS.items():
            if fr in word:
                translated.append(en)
                break
        else:
            # Keep untranslated if not too long
            if len(word) <= 10:
                translated.append(word)

    if translated:
        result = '_'.join(translated[:3])  # Max 3 words
        # Clean up
        result = re.sub(r'[^a-z0-9_]', '', result)
        result = re.sub(r'_+', '_', result)
        return result[:40]

    return None

def categorize_function(contexts, return_type):
    """Categorize function based on execution contexts and signature"""
    if not contexts:
        return None

    # Count categories
    categories = Counter()
    for ctx, count in contexts:
        category = translate_and_simplify(ctx)
        if category:
            categories[category] += count

    if not categories:
        return None

    # Get top category
    top_category = categories.most_common(1)[0][0]

    # Add prefix based on return type for clarity
    if return_type in ['void']:
        # Action function
        return top_category
    elif return_type in ['int', 'undefined2']:
        # Query/check function
        if not top_category.startswith('check_') and not top_category.startswith('get_'):
            return f"check_{top_category}"
        return top_category
    else:
        return top_category

# Load analysis
with open('function_analysis.json', 'r') as f:
    analysis = json.load(f)

# Generate improved names
improved_names = {}
for func in analysis['functions']:
    if func.get('contexts'):
        improved = categorize_function(func['contexts'], func['return_type'])
        if improved:
            func['improved_name'] = improved
            improved_names[func['name']] = improved

print(f"Generated {len(improved_names)} improved names")
print("\nSample improved names:")
print(f"{'OLD NAME':<30} {'ORIGINAL':<30} {'IMPROVED':<30}")
print("-" * 90)

for i, func in enumerate(analysis['functions'][:20]):
    if func.get('improved_name'):
        old = func['name']
        orig = func.get('suggested_name', '')
        improved = func['improved_name']
        print(f"{old:<30} {orig:<30} {improved:<30}")

# Save improved analysis
analysis['improved_count'] = len(improved_names)
for func in analysis['functions']:
    if func['name'] in improved_names:
        func['improved_name'] = improved_names[func['name']]

with open('function_analysis_improved.json', 'w') as f:
    json.dump(analysis, f, indent=2)

print(f"\nImproved analysis saved to: function_analysis_improved.json")

# Also save just the rename mapping
with open('improved_renames.json', 'w') as f:
    json.dump(improved_names, f, indent=2)

print(f"Improved renames saved to: improved_renames.json")
print(f"\nTo apply these renames, use apply_improved_renames.py")
