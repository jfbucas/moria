#!/usr/bin/python3
"""
Compile ALL 266 function names from all analysis batches
"""
import json

# Load existing 123 names
with open('function_names_compiled.json', 'r') as f:
    names = json.load(f)

print(f"Starting with {len(names)} names")

# Add batch 9 (161-180)
batch9 = {
    "FUN_20e6_020d": "clear_screen_double",
    "FUN_20e6_0227": "update_screen_double",
    "FUN_20e6_0260": "validate_window_coords",
    "FUN_20e6_028c": "get_relative_cursor_y",
    "FUN_20e6_0298": "get_relative_cursor_x",
    "FUN_20e6_02a4": "set_text_color_attribute",
    "FUN_20e6_02be": "set_background_color",
    "FUN_20e6_02e9": "wait_for_memory_match",
    "FUN_20e6_0309": "scan_memory_for_byte",
    "FUN_20e6_0311": "play_tone_frequency",
    "FUN_20e6_033e": "silence_speaker",
    "FUN_20e6_0357": "read_keyboard_input",
    "FUN_20e6_0379": "init_file_control_block",
    "FUN_20e6_03dc": "line_editor_main_loop",
    "FUN_20e6_04bf": "output_crlf",
    "FUN_20e6_04c6": "output_char_with_controls",
    "FUN_20e6_051f": "check_and_scroll_window",
    "FUN_20e6_0653": "call_video_bios",
    "FUN_214c_0000": "c_runtime_startup",
    "FUN_214c_01ec": "exit_program_handler",
}

# Add batch 10 (181-200)
batch10 = {
    "FUN_214c_01f3": "dos_interrupt_handler_init",
    "FUN_214c_026d": "get_and_clear_error_code",
    "FUN_214c_0277": "check_and_handle_error",
    "FUN_214c_0285": "validate_range_bounds",
    "FUN_214c_02ad": "validate_stack_space",
    "FUN_214c_02c0": "memcpy",
    "FUN_214c_02dc": "multiply_integers",
    "FUN_214c_02f7": "divide_long_signed",
    "FUN_214c_038e": "read_stream_data",
    "FUN_214c_04a2": "manage_buffer_list",
    "FUN_214c_0615": "pop_buffer_entry",
    "FUN_214c_062a": "check_buffer_empty",
    "FUN_214c_0674": "normalize_far_pointer",
    "FUN_214c_0693": "copy_pascal_string",
    "FUN_214c_06ad": "copy_pascal_string_limited",
    "FUN_214c_06df": "substring_pascal",
    "FUN_214c_0720": "concat_pascal_string",
    "FUN_214c_074c": "find_pascal_substring",
    "FUN_214c_0783": "compare_pascal_strings",
    "FUN_214c_07ae": "char_to_pascal_string",
}

# Add batch 11 (201-220)
batch11 = {
    "FUN_214c_07db": "format_string_with_buffers",
    "FUN_214c_082f": "conditional_string_format",
    "FUN_214c_0885": "pad_and_copy_buffer",
    "FUN_214c_08af": "zero_word_array_16",
    "FUN_214c_08be": "set_bit_in_array",
    "FUN_214c_08df": "set_bit_range_in_array",
    "FUN_214c_0913": "copy_buffer_with_offset",
    "FUN_214c_0933": "create_bit_mask",
    "FUN_214c_0954": "bitwise_or_word_arrays",
    "FUN_214c_096f": "bitwise_clear_word_arrays",
    "FUN_214c_09db": "float_add_subtract",
    "FUN_214c_09df": "float_add_subtract_near",
    "FUN_214c_0ab5": "float_multiply",
    "FUN_214c_0b32": "float_divide",
    "FUN_214c_0bbb": "float_adjust_exponent",
    "FUN_214c_0bde": "float_compare_signs",
    "FUN_214c_0bf5": "float_nop_stub",
    "FUN_214c_0c08": "float_normalize",
    "FUN_214c_0c47": "float_to_fixed_point",
    "FUN_214c_0ca3": "float_add_with_handler",
}

# Add batch 12 (221-240)
batch12 = {
    "FUN_214c_0ca9": "combat_check_and_handle_error",
    "FUN_214c_0cb5": "check_combat_and_handle_error",
    "FUN_214c_0cbb": "conditional_char_action",
    "FUN_214c_0cc5": "char_create_wrapper",
    "FUN_214c_0cc9": "combat_wrapper",
    "FUN_214c_0ccd": "combat_check_with_error",
    "FUN_214c_0cd5": "combat_check_with_error_alt",
    "FUN_214c_0cef": "combat_near_wrapper",
    "FUN_214c_0e79": "complex_combat_sequence",
    "FUN_214c_0f22": "calculate_combat_value",
    "FUN_214c_10fa": "combat_char_combat_sequence",
    "FUN_214c_1113": "process_combat_array",
    "FUN_214c_1162": "random_mod",
    "FUN_214c_1178": "find_highest_bit",
    "FUN_214c_11b0": "rand_lcg",
    "FUN_214c_11e8": "seed_rng",
    "FUN_214c_11f5": "int32_to_string",
    "FUN_214c_126f": "string_to_int32",
    "FUN_214c_1352": "parse_pascal_string_to_int",
    "FUN_214c_1383": "init_fcb",
}

# Add batch 13 (241-260)
batch13 = {
    "FUN_214c_13f3": "file_open_wrapper",
    "FUN_214c_13f8": "file_open_wrapper2",
    "FUN_214c_1400": "device_open_handler",
    "FUN_214c_1456": "device_close_handler",
    "FUN_214c_146d": "validate_device_type",
    "FUN_214c_1484": "call_device_handler",
    "FUN_214c_1490": "device_cleanup",
    "FUN_214c_1496": "call_indexed_handler",
    "FUN_214c_1618": "input_device_dispatch",
    "FUN_214c_1640": "read_byte_buffered",
    "FUN_214c_167d": "finalize_read",
    "FUN_214c_1687": "output_device_dispatch",
    "FUN_214c_16af": "write_byte_buffered",
    "FUN_214c_16e5": "finalize_write",
    "FUN_214c_16ef": "read_line",
    "FUN_214c_1712": "flush_input",
    "FUN_214c_173c": "write_word",
    "FUN_214c_1755": "flush_output",
    "FUN_214c_177f": "getc",
    "FUN_214c_1799": "write_bytes",
}

# Add batch 14 (261-266) - Final batch!
batch14 = {
    "FUN_214c_17be": "read_string_from_file",
    "FUN_214c_17f7": "write_padded_string",
    "FUN_214c_182b": "read_token_and_parse_number",
    "FUN_214c_1882": "write_padded_number",
    "FUN_214c_18d2": "skip_whitespace",
    "FUN_214c_190c": "to_uppercase",
}

# Combine all batches
names.update(batch9)
names.update(batch10)
names.update(batch11)
names.update(batch12)
names.update(batch13)
names.update(batch14)

print(f"Total functions named: {len(names)}")

# Save complete database
with open('function_names_complete.json', 'w') as f:
    json.dump(names, f, indent=2, sort_keys=True)

print("✓ Complete database saved to function_names_complete.json")

# Create summary statistics
from collections import Counter
categories = {
    'combat': 0,
    'inventory': 0,
    'display': 0,
    'io': 0,
    'math': 0,
    'string': 0,
    'memory': 0,
    'system': 0,
    'other': 0
}

for name in names.values():
    name_lower = name.lower()
    if any(x in name_lower for x in ['combat', 'attack', 'monster', 'kill', 'damage']):
        categories['combat'] += 1
    elif any(x in name_lower for x in ['inventory', 'item', 'equip', 'drop', 'pickup']):
        categories['inventory'] += 1
    elif any(x in name_lower for x in ['display', 'draw', 'render', 'show', 'print', 'screen']):
        categories['display'] += 1
    elif any(x in name_lower for x in ['read', 'write', 'file', 'device', 'input', 'output']):
        categories['io'] += 1
    elif any(x in name_lower for x in ['float', 'multiply', 'divide', 'random', 'calculate']):
        categories['math'] += 1
    elif any(x in name_lower for x in ['string', 'pascal', 'char', 'substring']):
        categories['string'] += 1
    elif any(x in name_lower for x in ['memory', 'buffer', 'alloc', 'free', 'copy']):
        categories['memory'] += 1
    elif any(x in name_lower for x in ['init', 'exit', 'startup', 'runtime', 'bios']):
        categories['system'] += 1
    else:
        categories['other'] += 1

print("\nFunction categories:")
for cat, count in sorted(categories.items(), key=lambda x: -x[1]):
    print(f"  {cat:12s}: {count:3d}")

