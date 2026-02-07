#!/usr/bin/python3
"""
Function Namer - Suggests names for reverse-engineered functions based on execution traces
"""
import json
import re
from collections import Counter

# Load the mapping
mapping = json.load(open('mapping.json', 'r'))

# Read the C source
c_source = open('reverse/MORIA.C').read()

# Extract all function definitions
# Pattern matches: return_type [qualifiers] FUN_XXXX_YYYY(params)
func_pattern = re.compile(r'^(\w+(?:\s+\*)?)\s+(?:__cdecl16near\s+)?(FUN_([0-9a-f]+)_([0-9a-f]+))\s*\(', re.MULTILINE)

def suggest_name_from_context(trace_counts):
    """Suggest a function name based on execution context"""
    if not trace_counts:
        return None

    most_common = trace_counts.most_common(1)[0][0]

    # Simple naming heuristics
    name_map = {
        'Initialization': 'init',
        'Drawing': 'draw',
        'Input': 'handle_input',
        'Movement': 'move',
        'Combat': 'combat',
        'Inventory': 'inventory',
        'Display': 'display',
        'Menu': 'show_menu',
        'Save': 'save_game',
        'Load': 'load_game',
    }

    # Try to find a match
    for key, name in name_map.items():
        if key.lower() in most_common.lower():
            return name

    # If no match, create a name from the context
    # Remove special chars and make snake_case
    clean = re.sub(r'[^a-zA-Z0-9\s]', '', most_common)
    clean = re.sub(r'\s+', '_', clean).lower()
    return clean[:30]  # Limit length

functions = []
for match in func_pattern.finditer(c_source):
    return_type = match.group(1)
    func_name = match.group(2)
    segment = match.group(3).upper()
    offset = match.group(4).upper()

    # Convert to address format used in mapping.json
    address = f"{segment}:{offset.upper()}"

    functions.append({
        'name': func_name,
        'segment': segment,
        'offset': offset,
        'address': address,
        'return_type': return_type,
        'line': c_source[:match.start()].count('\n') + 1
    })

print(f"Found {len(functions)} functions to name\n")

# For each function, find related execution traces
for func in functions:
    # Look for entries in the mapping that match this function's address space
    related_traces = []

    # Check if exact address exists
    if func['address'] in mapping:
        related_traces.extend(mapping[func['address']])

    # Check nearby addresses (within the function)
    # This is a simple heuristic - look at addresses that start with same segment and similar offset
    seg = func['segment']
    offset_int = int(func['offset'], 16)

    # Search for nearby addresses (within ~256 bytes as a heuristic)
    for addr, traces in mapping.items():
        if ':' in addr:
            addr_seg, addr_off = addr.split(':')
            if addr_seg.upper() == seg:
                addr_off_int = int(addr_off, 16)
                # If within reasonable range of the function start
                if offset_int <= addr_off_int < offset_int + 256:
                    related_traces.extend(traces)

    # Analyze traces to suggest a name
    if related_traces:
        # Count most common contexts
        trace_counts = Counter(related_traces)
        top_contexts = trace_counts.most_common(3)

        func['contexts'] = top_contexts
        func['suggested_name'] = suggest_name_from_context(trace_counts)
    else:
        func['contexts'] = []
        func['suggested_name'] = None

# Update function suggestions
for func in functions:
    if func.get('contexts'):
        trace_counts = Counter([ctx for ctx, _ in func['contexts']])
        func['suggested_name'] = suggest_name_from_context(trace_counts)

# Print summary
print("=" * 80)
print("FUNCTION NAMING SUGGESTIONS")
print("=" * 80)
print()

named_count = sum(1 for f in functions if f.get('suggested_name'))
print(f"Functions with suggestions: {named_count}/{len(functions)}")
print()

# Show functions with suggestions
print("Functions with execution trace data:")
print("-" * 80)
for func in functions:
    if func.get('contexts') and func['suggested_name']:
        print(f"\nLine {func['line']:5d}: {func['name']}")
        print(f"  Address: {func['address']}")
        print(f"  Contexts: {', '.join([f'{ctx} ({cnt})' for ctx, cnt in func['contexts'][:3]])}")
        print(f"  SUGGESTED: {func['suggested_name']}")

# Show functions without suggestions
print("\n" + "=" * 80)
print("Functions WITHOUT execution trace data (need manual naming):")
print("-" * 80)
for func in functions:
    if not func.get('contexts'):
        print(f"Line {func['line']:5d}: {func['name']} at {func['address']}")

# Save results to JSON for further processing
output = {
    'total_functions': len(functions),
    'functions_with_traces': named_count,
    'functions': functions
}

with open('function_analysis.json', 'w') as f:
    json.dump(output, f, indent=2)

print(f"\n\nDetailed analysis saved to function_analysis.json")
