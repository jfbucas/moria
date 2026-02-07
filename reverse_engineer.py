#!/usr/bin/python3
"""
Proper reverse engineering - analyze what functions actually do based on their code
"""
import re
from collections import defaultdict

# Read the C source
with open('reverse/MORIA.C', 'r') as f:
    c_source = f.read()

# Extract function definitions with their bodies
func_pattern = re.compile(
    r'^([\w\s\*]+?)\s+(FUN_([0-9a-f]+)_([0-9a-f]+))\s*\(([^)]*)\)\s*\n\{(.*?)^\}',
    re.MULTILINE | re.DOTALL
)

print("Extracting and analyzing functions...")

functions = []
for match in func_pattern.finditer(c_source):
    return_type = match.group(1).strip()
    func_name = match.group(2)
    segment = match.group(3).upper()
    offset = match.group(4).upper()
    params = match.group(5).strip()
    body = match.group(6)

    # Get line number
    line_num = c_source[:match.start()].count('\n') + 1

    functions.append({
        'name': func_name,
        'segment': segment,
        'offset': offset,
        'return_type': return_type,
        'params': params,
        'body': body,
        'line': line_num,
        'address': f"{segment}:{offset}"
    })

print(f"Extracted {len(functions)} functions with bodies\n")

def analyze_function(func):
    """Analyze what a function does based on its code"""
    body = func['body']
    params = func['params']
    return_type = func['return_type']

    patterns = {
        # String operations
        'string_ops': [
            r'strlen\s*\(',
            r'strcpy\s*\(',
            r'strcmp\s*\(',
            r'strcat\s*\(',
            r'sprintf\s*\(',
            r'char\s*\*',
        ],

        # Screen/Display operations
        'display': [
            r'0xb8\d+',  # Video memory addresses
            r'FUN_\w+_\w+\(.*0x[0-9a-f]+.*\)',  # Calls with hex addresses
            r'putc|printf|print',
            r'screen|display|show',
        ],

        # Memory operations
        'memory': [
            r'malloc\s*\(',
            r'free\s*\(',
            r'memcpy\s*\(',
            r'memset\s*\(',
            r'mem\w+',
        ],

        # Math operations
        'math': [
            r'\+\+|\-\-',
            r'[\+\-\*/%]\s*=',
            r'rand\s*\(',
            r'random',
        ],

        # Conditionals (decision making)
        'conditional': [
            r'if\s*\(',
            r'switch\s*\(',
            r'case\s+',
        ],

        # Loops (iteration)
        'loop': [
            r'for\s*\(',
            r'while\s*\(',
            r'do\s*\{',
        ],

        # Input operations
        'input': [
            r'getc|getch|getchar|scanf|read',
            r'keyboard|key|input',
        ],

        # Return patterns
        'returns_bool': [
            r'return\s+(0|1|true|false)',
            r'return\s+\(.*[<>=!]',
        ],

        # Pointer/array access
        'array_access': [
            r'\[\s*\w+\s*\]',
            r'\*\s*\w+',
        ],
    }

    # Count pattern matches
    scores = defaultdict(int)
    for category, pattern_list in patterns.items():
        for pattern in pattern_list:
            matches = len(re.findall(pattern, body, re.IGNORECASE))
            scores[category] += matches

    # Analyze function calls
    called_funcs = re.findall(r'(FUN_[0-9a-f]+_[0-9a-f]+)\s*\(', body)
    scores['calls_others'] = len(set(called_funcs))

    # Analyze body complexity
    lines = body.split('\n')
    non_empty_lines = [l for l in lines if l.strip() and not l.strip().startswith('//')]
    scores['complexity'] = len(non_empty_lines)

    # Check for specific addresses/constants
    if re.search(r'0xb8[0-9a-f]{3}', body):
        scores['video_memory'] = 10

    # Look for string literals
    string_literals = re.findall(r'"([^"]*)"', body)
    scores['has_strings'] = len(string_literals)

    # Analyze return statements
    returns = re.findall(r'return\s+([^;]+);', body)

    return {
        'scores': dict(scores),
        'called_functions': list(set(called_funcs)),
        'string_literals': string_literals,
        'returns': returns,
        'body_lines': len(non_empty_lines),
    }

def suggest_name_from_analysis(func, analysis):
    """Suggest a function name based on static analysis"""
    scores = analysis['scores']
    return_type = func['return_type']
    params = func['params']

    # Very simple function - likely a wrapper or getter
    if analysis['body_lines'] < 5:
        if 'void' not in return_type:
            return 'get_value'
        return 'simple_func'

    # Check for specific patterns
    suggestions = []

    # Video/display functions
    if scores.get('video_memory', 0) > 0 or scores.get('display', 0) > 3:
        suggestions.append('display')

    # Input functions
    if scores.get('input', 0) > 0:
        suggestions.append('handle_input')

    # String manipulation
    if scores.get('string_ops', 0) > 2:
        suggestions.append('string_op')

    # Memory management
    if scores.get('memory', 0) > 2:
        suggestions.append('mem_alloc')

    # Math/calculations
    if scores.get('math', 0) > 3:
        suggestions.append('calculate')

    # Boolean check functions
    if scores.get('returns_bool', 0) > 0 and 'void' not in return_type:
        suggestions.append('check')

    # Complex logic
    if scores.get('conditional', 0) > 3 and scores.get('loop', 0) > 0:
        suggestions.append('process')

    # Initialization (many assignments, few conditionals)
    if scores.get('math', 0) > 5 and scores.get('conditional', 0) < 3:
        suggestions.append('init')

    # Calls many other functions - likely a coordinator
    if scores.get('calls_others', 0) > 5:
        suggestions.append('handler')

    if suggestions:
        return suggestions[0]

    # Fallback based on return type
    if 'void' in return_type:
        return 'do_action'
    else:
        return 'get_result'

# Analyze all functions
print("Analyzing function implementations...\n")

for func in functions:
    analysis = analyze_function(func)
    func['analysis'] = analysis
    func['suggested_name'] = suggest_name_from_analysis(func, analysis)

# Print results
print("=" * 100)
print("REVERSE ENGINEERING RESULTS")
print("=" * 100)
print()

# Show some interesting findings
print("Sample analysis (first 10 functions):")
print("-" * 100)

for func in functions[:10]:
    print(f"\n{func['name']} at line {func['line']}")
    print(f"  Address: {func['address']}")
    print(f"  Signature: {func['return_type']} ({func['params']})")
    print(f"  Body: {func['analysis']['body_lines']} lines")
    print(f"  Calls: {len(func['analysis']['called_functions'])} other functions")

    if func['analysis']['string_literals']:
        print(f"  Strings: {', '.join(repr(s[:30]) for s in func['analysis']['string_literals'][:3])}")

    top_scores = sorted(func['analysis']['scores'].items(), key=lambda x: -x[1])[:3]
    if top_scores and top_scores[0][1] > 0:
        print(f"  Patterns: {', '.join(f'{k}({v})' for k, v in top_scores if v > 0)}")

    print(f"  → Suggested: {func['suggested_name']}")

# Save detailed analysis
import json
output = {
    'total_functions': len(functions),
    'functions': functions
}

# Make analysis serializable
for func in output['functions']:
    # Keep only JSON-serializable data
    func.pop('body', None)  # Remove large body text from JSON

with open('reverse_engineering_analysis.json', 'w') as f:
    json.dump(output, f, indent=2)

print(f"\n\nDetailed analysis saved to: reverse_engineering_analysis.json")
print(f"Analyzed {len(functions)} functions")
