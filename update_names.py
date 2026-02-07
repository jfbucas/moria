#!/usr/bin/python3
import json

# Load existing names
with open('function_names_compiled.json', 'r') as f:
    names = json.load(f)

# Add new names from batches 5-8
new_names = {
    # Batch 5 (81-100)
    "FUN_1000_65d3": "process_options_menu",
    "FUN_1000_6887": "redraw_screen_map",
    "FUN_1000_6921": "display_help_file",
    "FUN_1000_6a56": "display_inventory_list",
    "FUN_1000_6c94": "load_high_scores",
    "FUN_1000_6f02": "display_high_scores",
    "FUN_1000_71a1": "save_high_scores",
    "FUN_1000_7364": "process_game_over",
    "FUN_1000_763d": "confirm_save_or_quit",
    "FUN_1000_76a4": "apply_heroism_effect",
    "FUN_1000_772e": "level_up_character",
    "FUN_1000_77fe": "lose_experience_level",
    "FUN_1000_7849": "remove_magic_item",
    "FUN_1000_7923": "teleport_player",
    "FUN_1000_79ea": "kill_monster",
    "FUN_1000_7d66": "reveal_shapeshifter",
    "FUN_1000_7dab": "process_monster_breeding",
    "FUN_1000_7e29": "cleanup_after_monster_death",
    "FUN_1000_7ebc": "monster_attack_player",
    "FUN_1000_8573": "execute_player_attack",
    
    # Batch 6 (101-110) 
    "FUN_1000_8d6d": "remove_spell",
    "FUN_1000_8e03": "reset_food_flags",
    "FUN_1000_8f6e": "learn_spell",
    "FUN_1000_9099": "pickup_item",
    "FUN_1000_9554": "display_shop_item",
    "FUN_1000_95ee": "shop_purchase_menu",
    "FUN_1000_99c5": "drop_item",
    "FUN_1000_9a91": "identify_item",
    "FUN_1000_9ca1": "discover_item",
    "FUN_1000_9d52": "equip_item",
    
    # Batch 7 (121-130)
    "FUN_1000_b821": "apply_armor_damage_reduction",
    "FUN_1000_b8c7": "handle_attack_action",
    "FUN_1000_bafc": "show_spell_info",
    "FUN_1000_bcd0": "check_spell_cast_chance",
    "FUN_1000_bd12": "prepare_and_cast_spell",
    "FUN_1000_bd2d": "execute_spell_effect",
    "FUN_1000_c8dd": "drink_potion_effect",
    "FUN_1000_d26a": "check_confusion_recovery",
    "FUN_1000_d2a4": "show_message_and_clear_flag",
    "FUN_1000_d2bb": "use_item_from_inventory",
    
    # Batch 8 (131-150)
    "FUN_1000_d7c9": "check_space_threshold_and_handle",
    "FUN_1000_d81d": "placeholder_stub",
    "FUN_1000_d827": "are_coordinates_adjacent",
    "FUN_1000_d873": "validate_tile_movement",
    "FUN_1000_db14": "calculate_movement_direction",
    "FUN_1000_dc2b": "move_entity_on_map",
    "FUN_1000_e193": "update_all_monsters",
    "FUN_1000_e7da": "advance_to_next_level",
    "FUN_1000_e8ad": "is_tile_passable",
    "FUN_1000_e96e": "move_player_in_direction",
    "FUN_1000_eed5": "initialize_new_level",
    "FUN_1000_ef1d": "handle_timed_effect",
    "FUN_1000_f020": "main_game_command_loop",
    "FUN_1000_f550": "rest_and_regenerate",
    "FUN_1000_f5f2": "main_game_loop",
    "FUN_1000_f841": "show_main_menu",
    "FUN_1f98_0000": "initialize_character_sets",
    "FUN_1f98_01fb": "get_random_byte",
    "FUN_1f98_027a": "get_centered_random",
    "FUN_1f98_029f": "read_data_line",
}

names.update(new_names)
print(f"Total function names: {len(names)}")

with open('function_names_compiled.json', 'w') as f:
    json.dump(names, f, indent=2, sort_keys=True)

print("Updated function_names_compiled.json")
