#!/usr/bin/python3
"""
Compile all function names from agent analysis outputs
"""
import json

# Manually compiled from agent outputs
function_names = {
    # Batch 1 (1-10)
    "FUN_1000_0000": "get_sign",
    "FUN_1000_0040": "check_minimum_stats",
    "FUN_1000_0094": "print_space",
    "FUN_1000_00b3": "print_prompt",
    "FUN_1000_00de": "find_item_at_coords",
    "FUN_1000_016a": "display_score_with_fatal",
    "FUN_1000_0296": "display_character_stats",
    "FUN_1000_0428": "put_char_at_pos",
    "FUN_1000_0479": "lookup_table_b9c7",
    "FUN_1000_0499": "display_class_info",
    
    # Batch 1 (11-20)
    "FUN_1000_0510": "display_ability_score",
    "FUN_1000_052b": "is_type_7_subtype_12",
    "FUN_1000_0556": "allocate_monster_object",
    "FUN_1000_05b0": "free_monster_object",
    "FUN_1000_05d6": "allocate_item_object",
    "FUN_1000_063c": "free_item_object",
    "FUN_1000_0662": "decrement_item_quantity",
    "FUN_1000_06d5": "check_inventory_has_item",
    "FUN_1000_07fb": "build_object_index",
    "FUN_1000_084b": "count_item_total_quantity",
    
    # Batch 2 (21-30)
    "FUN_1000_08bd": "handle_item_drop_or_unequip",
    "FUN_1000_0a6f": "is_position_in_bounds",
    "FUN_1000_0a9f": "explore_tile_at_position",
    "FUN_1000_0e28": "render_field_of_view",
    "FUN_1000_11fc": "redraw_dungeon_level",
    "FUN_1000_1448": "handle_error_and_wait",
    "FUN_1000_14ab": "remove_item_from_list",
    "FUN_1000_15a2": "prepend_item_to_list",
    "FUN_1000_15d3": "destroy_or_consume_item",
    "FUN_1000_17aa": "is_item_equipped_or_in_pack",
    
    # High priority functions
    "FUN_1f98_042e": "load_game_data",
    "FUN_1000_4c49": "draw_game_hud",
    "FUN_1000_557c": "display_object_info",
    "FUN_1000_c8dd": "apply_potion_effect",
    "FUN_1000_bd2d": "use_scroll_or_cast_spell",
    "FUN_1000_9f40": "remove_equipped_item_menu",
    
    # Batch 3 (41-60)
    "FUN_1000_227b": "display_food_status",
    "FUN_1000_22c8": "display_character_status_message",
    "FUN_1000_2363": "find_random_empty_floor_space",
    "FUN_1000_23da": "find_position_near_player",
    "FUN_1000_2574": "place_object_on_map",
    "FUN_1000_260c": "calculate_dice_or_damage",
    "FUN_1000_26cf": "initialize_monster_or_item",
    "FUN_1000_2d29": "spawn_monster_from_template",
    "FUN_1000_2fe0": "generate_random_names",
    "FUN_1000_3086": "shuffle_array",
    "FUN_1000_30ec": "randomize_item_appearances",
    "FUN_1000_325e": "spawn_special_monster_with_item",
    "FUN_1000_33a1": "spawn_unique_monster_type_23",
    "FUN_1000_3408": "spawn_monster_type_1f",
    "FUN_1000_3442": "spawn_wandering_monster",
    "FUN_1000_3486": "add_monster_to_level_list",
    "FUN_1000_34ea": "prepend_monster_to_global_list",
    "FUN_1000_3544": "populate_level_with_monsters",
    "FUN_1000_3691": "find_dungeon_region",
    "FUN_1000_36f8": "generate_dungeon_corridors",
    
    # Batch 4 (61-70)
    "FUN_1000_3a12": "draw_dungeon_border",
    "FUN_1000_3b34": "generate_dungeon_level",
    "FUN_1000_40c0": "spawn_monsters",
    "FUN_1000_425e": "select_or_load_character",
    "FUN_1000_447b": "initialize_new_game",
    "FUN_1000_48b7": "initialize_game",
    "FUN_1000_491d": "find_empty_floor_tile",
    "FUN_1000_4a27": "place_player_on_level",
    "FUN_1000_4b52": "handle_player_death",
}

print(f"Compiled {len(function_names)} function names")

with open('function_names_compiled.json', 'w') as f:
    json.dump(function_names, f, indent=2, sort_keys=True)

print("Saved to function_names_compiled.json")
