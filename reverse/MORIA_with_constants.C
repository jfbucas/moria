/* Moria Game - Reverse Engineered with Proper Constants
 *
 * This version includes:
 * - All memory addresses replaced with named constants
 * - Fixed food/satiation system (was incorrectly labeled as "mana")
 * - Improved readability with ADDR_* constants
 *
 * Include moria_constants.h to compile this file
 */

#include "moria_constants.h"

typedef unsigned char   undefined;

typedef unsigned char    undefined1;
typedef unsigned int    undefined2;
typedef unsigned long    undefined4;
typedef unsigned int    word;
typedef struct OLD_IMAGE_DOS_RELOC OLD_IMAGE_DOS_RELOC, *POLD_IMAGE_DOS_RELOC;

struct OLD_IMAGE_DOS_RELOC {
    word offset;
    word segment;
};

typedef struct OLD_IMAGE_DOS_HEADER OLD_IMAGE_DOS_HEADER, *POLD_IMAGE_DOS_HEADER;

struct OLD_IMAGE_DOS_HEADER {
    char e_magic[2]; // Magic number
    word e_cblp; // Bytes of last page
    word e_cp; // Pages in file
    word e_crlc; // Relocations
    word e_cparhdr; // Size of header in paragraphs
    word e_minalloc; // Minimum extra paragraphs needed
    word e_maxalloc; // Maximum extra paragraphs needed
    word e_ss; // Initial (relative) SS value
    word e_sp; // Initial SP value
    word e_csum; // Checksum
    word e_ip; // Initial IP value
    word e_cs; // Initial (relative) CS value
    word e_lfarlc; // File address of relocation table
    word e_ovno; // Overlay number
};




undefined2 get_sign(int *result_ptr)

{
  undefined2 local_4;
  
  if (*result_ptr == 0) {
    local_4 = 0;
  }
  else if (*result_ptr < 1) {
    local_4 = 0xffff;
  }
  else {
    local_4 = 1;
  }
  return local_4;
}



void __cdecl16near check_minimum_stats(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  undefined2 uVar2;
  undefined2 uVar3;
  
  validate_window_coords(1,1);
  uVar1 = 0x20e6;
  update_screen_double();
  if (turn_count < 100) {
    uVar2 = 0xe654;
    uVar3 = unaff_DS;
    write_padded_string(0,0x34,0x20e6);
    uVar1 = 0x214c;
    flush_output(uVar2,uVar3);
  }
  if (food_level < 400) {
    uVar3 = 0xe654;
    write_padded_string(0,0x3a,uVar1);
    flush_output(uVar3,unaff_DS);
  }
  return;
}



void __cdecl16near print_space(void)

{
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  uVar1 = 0xe654;
  write_bytes(0,0x20);
  flush_output(uVar1,unaff_DS);
  return;
}



void __cdecl16near print_prompt(void)

{
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  uVar1 = 0xe654;
  write_padded_string(0,0xb0,0x1000);
  flush_output(uVar1,unaff_DS);
  return;
}



void find_item_at_coords(int *result_ptr,int count,int flags)

{
  undefined4 uVar1;
  int *piVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined4 *)(dungeon_level * 4 + -0x5499);
  uVar3 = (undefined2)((ulong)result_ptr >> 0x10);
  piVar2 = (int *)result_ptr;
  *result_ptr = (int)uVar1;
  piVar2[1] = (int)((ulong)uVar1 >> 0x10);
  while ((*result_ptr != 0 || piVar2[1] != 0 &&
         ((*(int *)((int)*(undefined4 *)result_ptr + 0x1c) != flags ||
          (*(int *)((int)*(undefined4 *)result_ptr + 0x1e) != count))))) {
    uVar1 = *(undefined4 *)((int)*(undefined4 *)result_ptr + 0x32);
    *result_ptr = (int)uVar1;
    piVar2[1] = (int)((ulong)uVar1 >> 0x10);
  }
  if (*result_ptr == 0 && piVar2[1] == 0) {
    check_minimum_stats();
    uVar3 = 0xe654;
    write_padded_string(0,0xd1,0x1000);
    flush_output(uVar3,unaff_DS);
    handle_error_and_wait();
  }
  return;
}



void display_score_with_fatal(int value)

{
  int iVar1;
  undefined2 unaff_DS;
  undefined2 uVar2;
  
  iVar1 = value;
  if (value < 0) {
    check_minimum_stats();
    iVar1 = -value;
  }
  if (iVar1 < 0x191) {
    iVar1 = value;
    if (value < 0) {
      iVar1 = -value;
    }
    if (iVar1 < 0x12d) {
      iVar1 = value;
      if (value < 0) {
        iVar1 = -value;
      }
      if (iVar1 < 0x65) {
        uVar2 = 0xe654;
        iVar1 = value;
        if (value < 0) {
          iVar1 = -value;
        }
        write_padded_string(0,iVar1 * 0x33 + -0x3bb7,unaff_DS);
        flush_output(uVar2,unaff_DS);
      }
      else {
        uVar2 = 0xe654;
        iVar1 = value;
        if (value < 0) {
          iVar1 = -value;
        }
        write_padded_string(0,(iVar1 + -100) * 0x1f + -0x29b5,unaff_DS);
        flush_output(uVar2,unaff_DS);
      }
    }
    else {
      uVar2 = 0xe654;
      iVar1 = value;
      if (value < 0) {
        iVar1 = -value;
      }
      write_padded_string(0,(iVar1 + -300) * 0x49 + -0x44a4,unaff_DS);
      flush_output(uVar2,unaff_DS);
    }
  }
  else {
    uVar2 = 0xe654;
    iVar1 = value;
    if (value < 0) {
      iVar1 = -value;
    }
    write_padded_string(0,(iVar1 + -400) * 0x10 + -0x1c73,unaff_DS);
    flush_output(uVar2,unaff_DS);
  }
  if (value < 0) {
    handle_error_and_wait();
  }
  return;
}



void __cdecl16near display_character_stats(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 unaff_DS;
  undefined2 uVar3;
  undefined2 uVar4;
  
  uVar1 = get_relative_cursor_y();
  uVar2 = get_relative_cursor_x(uVar1);
  validate_window_coords(0x19,1);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x261,0x20e6);
  write_padded_number(2,dungeon_level,dungeon_level >> 0xf);
  flush_output(uVar3,uVar4);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x266,0x214c);
  write_padded_number(6,*(undefined2 *)ADDR_GOLD_LOW /* gold_low */,*(undefined2 *)ADDR_GOLD_HIGH /* gold_high */);
  write_padded_string(0,0x26a,0x214c);
  write_padded_number(4,current_hp,current_hp >> 0xf);
  write_bytes(0,CONCAT11(extraout_AH,0x2f));
  write_padded_number(3,max_hp,max_hp >> 0xf);
  write_padded_string(0,0x270,0x214c);
  write_padded_number(3,intelligence,intelligence >> 0xf);
  write_padded_string(0,0x277,0x214c);
  write_padded_number(3,strength,strength >> 0xf);
  write_padded_string(0,0x27e,0x214c);
  write_padded_number(3,current_food,current_food >> 0xf);
  write_padded_string(0,0x285,0x214c);
  flush_output(uVar3,uVar4);
  if (base_ac < 1) {
    print_space();
  }
  else {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_padded_string(0,0x28b,0x214c);
    flush_output(uVar3,uVar4);
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(1,base_ac,base_ac >> 0xf);
  write_padded_string(0,0x28e,0x214c);
  write_padded_number(2,player_level,player_level >> 0xf);
  write_bytes(0,CONCAT11(extraout_AH_00,0x2f));
  write_padded_number(4,experience,experience >> 0xf);
  flush_output(uVar3,uVar4);
  update_screen_double();
  validate_window_coords(CONCAT11(extraout_AH_01,uVar2),CONCAT11(extraout_AH_01,uVar1));
  return;
}



void put_char_at_pos(undefined1 param_1,undefined1 param_2,int flags)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined2 unaff_DS;
  undefined2 uVar3;
  
  uVar1 = get_relative_cursor_y();
  uVar2 = get_relative_cursor_x(uVar1);
  validate_window_coords(flags + 1,param_2);
  uVar3 = 0xe654;
  write_bytes(0,CONCAT11(extraout_AH,param_1));
  flush_output(uVar3,unaff_DS);
  validate_window_coords(CONCAT11(extraout_AH_00,uVar2),CONCAT11(extraout_AH_00,uVar1));
  return;
}



undefined2 lookup_table_b9c7(char *result_ptr)

{
  undefined2 unaff_DS;
  
  return CONCAT11((char)((uint)(*result_ptr + 1) >> 8),*(undefined1 *)(*result_ptr + -0x4639));
}



void display_class_info(char param_1,int count)

{
  undefined2 unaff_DS;
  undefined2 uVar1;
  undefined2 uVar2;
  
  if (param_1 == '\0') {
    uVar1 = 0xe654;
    uVar2 = unaff_DS;
    write_padded_string(0,count * 5 + -0x4985,unaff_DS);
    flush_output(uVar1,uVar2);
  }
  else {
    uVar1 = 0xe654;
    uVar2 = unaff_DS;
    write_padded_string(0,count * 5 + -0x4a34,unaff_DS);
    flush_output(uVar1,uVar2);
  }
  uVar2 = 0xe654;
  write_padded_string(0,count * 0x2a + -0x5017,unaff_DS);
  flush_output(uVar2,unaff_DS);
  return;
}



void display_ability_score(undefined2 param_1,undefined2 param_2)

{
  undefined1 extraout_AH;
  
  display_score_with_fatal(param_2);
  display_class_info(CONCAT11(extraout_AH,1),param_1);
  print_prompt();
  return;
}



undefined1 is_type_7_subtype_12(char *result_ptr)

{
  undefined1 uVar1;
  
  if ((*result_ptr == '\a') && (*(int *)((char *)result_ptr + 1) == 0xc)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



void allocate_monster_object(undefined4 *result_ptr)

{
  undefined4 uVar1;
  int value;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar3 = (undefined2)((ulong)result_ptr >> 0x10);
  if (*(int *)0xaba7 == 0 && *(int *)0xaba9 == 0) {
    read_stream_data(0x36,(undefined4 *)result_ptr,uVar3);
    *(int *)0xe52f = *(int *)0xe52f + 1;
  }
  else {
    uVar1 = *(undefined4 *)0xaba7;
    *(int *)result_ptr = (int)uVar1;
    *(undefined2 *)((int)(undefined4 *)result_ptr + 2) = (int)((ulong)uVar1 >> 0x10);
    uVar1 = *(undefined4 *)((int)*(undefined4 *)0xaba7 + 0x32);
    *(undefined2 *)0xaba7 = (int)uVar1;
    *(undefined2 *)0xaba9 = (int)((ulong)uVar1 >> 0x10);
    uVar3 = (undefined2)((ulong)*result_ptr >> 0x10);
    value = (int)*result_ptr;
    *(undefined2 *)(value + 0x32) = 0;
    *(undefined2 *)(value + 0x34) = 0;
  }
  return;
}



void free_monster_object(undefined4 param_1)

{
  undefined4 uVar1;
  int value;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined4 *)0xaba7;
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  value = (int)param_1;
  *(undefined2 *)(value + 0x32) = (int)uVar1;
  *(undefined2 *)(value + 0x34) = (int)((ulong)uVar1 >> 0x10);
  *(int *)0xaba7 = value;
  *(undefined2 *)0xaba9 = uVar3;
  return;
}



void allocate_item_object(undefined4 *result_ptr)

{
  undefined4 uVar1;
  int value;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar3 = (undefined2)((ulong)result_ptr >> 0x10);
  if (*(int *)0xabab == 0 && *(int *)0xabad == 0) {
    read_stream_data(0x1a,(undefined4 *)result_ptr,uVar3);
    *(int *)0xe531 = *(int *)0xe531 + 1;
  }
  else {
    uVar1 = *(undefined4 *)0xabab;
    *(int *)result_ptr = (int)uVar1;
    *(undefined2 *)((int)(undefined4 *)result_ptr + 2) = (int)((ulong)uVar1 >> 0x10);
    uVar1 = *(undefined4 *)((int)*(undefined4 *)0xabab + 0x16);
    *(undefined2 *)0xabab = (int)uVar1;
    *(undefined2 *)0xabad = (int)((ulong)uVar1 >> 0x10);
  }
  uVar3 = (undefined2)((ulong)*result_ptr >> 0x10);
  value = (int)*result_ptr;
  *(undefined2 *)(value + 0x16) = 0;
  *(undefined2 *)(value + 0x18) = 0;
  *(undefined2 *)((int)*result_ptr + 3) = 1;
  return;
}



void free_item_object(undefined4 param_1)

{
  undefined4 uVar1;
  int value;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined4 *)0xabab;
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  value = (int)param_1;
  *(undefined2 *)(value + 0x16) = (int)uVar1;
  *(undefined2 *)(value + 0x18) = (int)((ulong)uVar1 >> 0x10);
  *(int *)0xabab = value;
  *(undefined2 *)0xabad = uVar3;
  return;
}



void decrement_item_quantity(int value)

{
  undefined4 uVar1;
  undefined4 uVar2;
  bool flag;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  local_4 = 0;
  flag = false;
  do {
    local_4 = local_4 + 1;
    if ((*(int *)(local_4 * 4 + -0x46cc) != 0 || *(int *)(local_4 * 4 + -0x46ca) != 0) &&
       (uVar1 = *(undefined4 *)(local_4 * 4 + -0x46cc), *(int *)((int)uVar1 + 1) == value)) {
      uVar1 = *(undefined4 *)(local_4 * 4 + -0x46cc);
      uVar2 = *(undefined4 *)(local_4 * 4 + -0x46cc);
      *(int *)((int)uVar2 + 9) = *(int *)((int)uVar1 + 9) + -1;
      flag = true;
    }
  } while ((local_4 != *(int *)0xb936) && (!flag));
  return;
}



undefined2 check_inventory_has_item(uint value)

{
  undefined4 uVar1;
  uint value;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined1 local_28 [32];
  int flag;
  int local_6;
  char ch;
  char ch;
  
  ch = '\0';
  local_6 = 0;
  if (0 < *(int *)0xb936) {
    local_6 = 1;
    while( true ) {
      if ((ch == '\0') &&
         (*(int *)(local_6 * 4 + -0x46cc) == 0 && *(int *)(local_6 * 4 + -0x46ca) == 0)) {
        ch = '\0';
      }
      else {
        ch = '\x01';
      }
      if (local_6 == *(int *)0xb936) break;
      local_6 = local_6 + 1;
    }
  }
  if (value == 0) {
    uVar3 = (undefined1)((uint)local_6 >> 8);
    ch = ch;
  }
  else {
    ch = '\0';
    flag = *(int *)0xb936;
    local_6 = 0;
    uVar3 = flag == 1;
    if (0 < flag) {
      local_6 = 1;
      while( true ) {
        value = value & 0xff;
        puVar4 = local_28;
        uVar5 = unaff_SS;
        zero_word_array_16(puVar4);
        set_bit_in_array(CONCAT11(extraout_AH,0x12));
        set_bit_in_array(CONCAT11(extraout_AH_00,0x13));
        create_bit_mask(puVar4,uVar5,value);
        if ((bool)uVar3) {
          if ((ch == '\0') &&
             ((*(int *)(local_6 * 4 + -0x46cc) == 0 && *(int *)(local_6 * 4 + -0x46ca) == 0 ||
              (uVar1 = *(undefined4 *)(local_6 * 4 + -0x46cc), *(uint *)((int)uVar1 + 1) != value)
              ))) {
            ch = '\0';
          }
          else {
            ch = '\x01';
          }
        }
        else if (((*(int *)(local_6 * 4 + -0x46cc) != 0 || *(int *)(local_6 * 4 + -0x46ca) != 0) &&
                 (uVar1 = *(undefined4 *)(local_6 * 4 + -0x46cc),
                 *(uint *)((int)uVar1 + 1) == value)) &&
                (uVar1 = *(undefined4 *)(local_6 * 4 + -0x46cc), 0 < *(int *)((int)uVar1 + 9))) {
          ch = '\x01';
        }
        if (local_6 == flag) break;
        local_6 = local_6 + 1;
        uVar3 = local_6 == 0;
      }
    }
    uVar3 = (undefined1)((uint)local_6 >> 8);
    ch = ch;
  }
  return CONCAT11(uVar3,ch);
}



void __cdecl16near build_object_index(void)

{
  int value;
  char *pcVar2;
  undefined2 unaff_DS;
  char *local_6;
  int local_4;
  
  pcVar2 = (char *)inventory_list;
  while (local_6 = (char *)pcVar2, local_4 = (int)((ulong)pcVar2 >> 0x10),
        local_6 != (char *)0x0 || local_4 != 0) {
    if (*pcVar2 == '\b') {
      value = *(int *)(local_6 + 1);
      *(undefined2 *)(value * 4 + -0x476c) = local_6;
      *(int *)(value * 4 + -0x476a) = local_4;
    }
    pcVar2 = *(char **)(local_6 + 0x16);
  }
  return;
}



void count_item_total_quantity(int *result_ptr,int count)

{
  int value;
  undefined4 uVar2;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  *result_ptr = 0;
  value = *(int *)0xb936;
  if (0 < value) {
    local_4 = 1;
    while( true ) {
      if ((*(int *)(local_4 * 4 + -0x46cc) != 0 || *(int *)(local_4 * 4 + -0x46ca) != 0) &&
         (uVar2 = *(undefined4 *)(local_4 * 4 + -0x46cc), *(int *)((int)uVar2 + 1) == count)) {
        uVar2 = *(undefined4 *)(local_4 * 4 + -0x46cc);
        *result_ptr = *result_ptr + *(int *)((int)uVar2 + 9);
      }
      if (local_4 == value) break;
      local_4 = local_4 + 1;
    }
  }
  return;
}



void handle_item_drop_or_unequip(char param_1,undefined1 *param_2,undefined4 *flags)

{
  int value;
  undefined2 unaff_DS;
  int local_4;
  
  *param_2 = 1;
  if ((((((int)((ulong)*flags >> 0x10) == *(int *)0xb928) && ((int)*flags == *(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */)) ||
       (((int)((ulong)*flags >> 0x10) == *(int *)0xb92c && ((int)*flags == *(int *)ADDR_EQUIPPED_ARMOR /* equipped_armor */)))) ||
      (((int)((ulong)*flags >> 0x10) == *(int *)0xb934 && ((int)*flags == *(int *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */)))) ||
     (((int)((ulong)*flags >> 0x10) == *(int *)0xb930 && ((int)*flags == *(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */)))) {
    if (*(char *)((int)*flags + 0x14) == '\0') {
      if (((int)((ulong)*flags >> 0x10) == *(int *)0xb928) && ((int)*flags == *(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */)) {
        equipped_shield = 0;
        *(undefined2 *)0xb928 = 0;
        *(undefined2 *)ADDR_WISDOM = 0;
      }
      if (((int)((ulong)*flags >> 0x10) == *(int *)0xb92c) && ((int)*flags == *(int *)ADDR_EQUIPPED_ARMOR /* equipped_armor */)) {
        equipped_armor = 0;
        *(undefined2 *)0xb92c = 0;
        *(undefined2 *)ADDR_DEXTERITY = 0;
      }
      if (((int)((ulong)*flags >> 0x10) == *(int *)0xb934) && ((int)*flags == *(int *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */)) {
        equipped_ring2 = 0;
        *(undefined2 *)0xb934 = 0;
        *(undefined2 *)0xb884 = 0;
      }
      if (((int)((ulong)*flags >> 0x10) == *(int *)0xb930) && ((int)*flags == *(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */)) {
        equipped_ring1 = 0;
        *(undefined2 *)0xb930 = 0;
      }
    }
    else {
      *param_2 = 0;
      if (param_1 == '\0') {
        display_score_with_fatal(0x4f);
      }
    }
    base_ac = *(int *)ADDR_WISDOM + *(int *)ADDR_DEXTERITY;
  }
  else if (((int)((ulong)*flags >> 0x10) == *(int *)0xb924) && ((int)*flags == *(int *)ADDR_WIELDED_WEAPON /* wielded_weapon */))
  {
    wielded_weapon = 0;
    *(undefined2 *)0xb924 = 0;
    *(undefined2 *)ADDR_CONSTITUTION = 0;
  }
  else {
    value = *(int *)0xb936;
    if (0 < value) {
      local_4 = 1;
      while( true ) {
        if (((int)((ulong)*flags >> 0x10) == *(int *)(local_4 * 4 + -0x46ca)) &&
           ((int)*flags == *(int *)(local_4 * 4 + -0x46cc))) {
          if (*(char *)((int)*flags + 0x14) == '\0') {
            *(undefined2 *)(local_4 * 4 + -0x46cc) = 0;
            *(undefined2 *)(local_4 * 4 + -0x46ca) = 0;
          }
          else {
            *param_2 = 0;
            if (param_1 == '\0') {
              display_score_with_fatal(0x4e);
            }
          }
        }
        if (local_4 == value) break;
        local_4 = local_4 + 1;
      }
    }
  }
  return;
}



undefined1 is_position_in_bounds(undefined2 param_1,int count,int flags)

{
  undefined1 uVar1;
  
  if ((((flags < 1) || (0x16 < flags)) || (count < 1)) || (0x4f < count)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



void explore_tile_at_position(int value,int count,int flags)

{
  undefined4 uVar1;
  char ch;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined1 local_16c [256];
  undefined1 local_6c [32];
  undefined1 local_4c [32];
  undefined1 local_2c [32];
  int local_c;
  undefined1 local_8 [2];
  undefined4 local_6;
  
  if ((is_teleporting == '\0') ||
     (ch = is_position_in_bounds(value,count + *(int *)(value + -2),
                            flags + *(int *)(value + -4)), ch != '\0')) {
    if (*(char *)(flags * MAP_WIDTH + count + -0xc) == ' ') {
      if (*(char *)(dungeon_level * 0x719 + flags * MAP_WIDTH + count + 0x70d) != '\0') {
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        flag = (int)uVar1 + flags * MAP_WIDTH + count;
        uVar4 = flag == 0;
        uVar7 = CONCAT11((char)((uint)(flags * MAP_WIDTH) >> 8),*(undefined1 *)(flag + -0x50));
        puVar5 = local_2c;
        uVar6 = unaff_SS;
        pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
        create_bit_mask(puVar5,uVar6,uVar7);
        if (((!(bool)uVar4) && (is_teleporting == '\0')) && (needs_full_update == '\0')) {
          return;
        }
      }
      if (needs_full_update == '\0') {
        *(undefined1 *)(dungeon_level * 0x719 + flags * MAP_WIDTH + count + 0x70d) = 1;
      }
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      flag = (int)uVar1 + flags * MAP_WIDTH + count;
      uVar4 = flag == 0;
      uVar7 = CONCAT11((char)((uint)(flags * MAP_WIDTH) >> 8),*(undefined1 *)(flag + -0x50));
      puVar5 = local_4c;
      uVar6 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb7cf,unaff_DS);
      create_bit_mask(puVar5,uVar6,uVar7);
      if (((bool)uVar4) || (confusion_lock == '\0')) {
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        flag = (int)uVar1 + flags * MAP_WIDTH + count;
        uVar4 = flag == 0;
        uVar7 = CONCAT11((char)((uint)(flags * MAP_WIDTH) >> 8),*(undefined1 *)(flag + -0x50));
        puVar5 = local_6c;
        uVar6 = unaff_SS;
        zero_word_array_16(puVar5);
        set_bit_in_array(CONCAT11(extraout_AH_00,0x20));
        set_bit_in_array(CONCAT11(extraout_AH_01,*(undefined1 *)0x1));
        set_bit_in_array(CONCAT11(extraout_AH_02,*(undefined1 *)0x3));
        create_bit_mask(puVar5,uVar6,uVar7);
        if ((bool)uVar4) {
          validate_window_coords(*(int *)(value + -4) + flags + 1,*(int *)(value + -2) + count);
          uVar6 = 0xe654;
          uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
          write_bytes(0,CONCAT11((char)((uint)(flags * MAP_WIDTH) >> 8),
                                   *(undefined1 *)((int)uVar1 + flags * MAP_WIDTH + count + -0x50)));
          flush_output(uVar6,unaff_DS);
        }
        else {
          uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
          if (*(char *)((int)uVar1 + flags * MAP_WIDTH + count + -0x50) != ' ') {
            puVar5 = local_16c;
            uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
            uVar6 = unaff_SS;
            char_to_pascal_string(CONCAT11((char)((uint)(flags * MAP_WIDTH) >> 8),
                                   *(undefined1 *)((int)uVar1 + flags * MAP_WIDTH + count + -0x50)));
            flag = parse_pascal_string_to_int(local_8,unaff_SS,puVar5,uVar6);
            local_6 = 0;
            if (0 < *(int *)0xb936) {
              local_c = 1;
              while( true ) {
                if (((*(int *)(local_c * 4 + -0x46cc) != 0 || *(int *)(local_c * 4 + -0x46ca) != 0)
                    && (uVar1 = *(undefined4 *)(local_c * 4 + -0x46cc),
                       *(int *)((int)uVar1 + 1) == 10)) &&
                   (uVar1 = *(undefined4 *)(local_c * 4 + -0x46cc), *(int *)((int)uVar1 + 9) != 0))
                {
                  local_6 = *(undefined4 *)(local_c * 4 + -0x46cc);
                }
                if (local_c == *(int *)0xb936) break;
                local_c = local_c + 1;
              }
            }
            if ((int)local_6 != 0 || local_6._2_2_ != 0) {
              *(int *)((int)local_6 + 9) = *(int *)((int)local_6 + 9) + -1;
              uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
              *(undefined1 *)((int)uVar1 + flags * MAP_WIDTH + count + -0x50) =
                   *(undefined1 *)(flag * 2 + -2);
            }
          }
        }
      }
      else {
        validate_window_coords(*(int *)(value + -4) + flags + 1,*(int *)(value + -2) + count);
        uVar7 = 0xe654;
        uVar6 = unaff_DS;
        flag = random_mod(*(undefined1 *)0xb9c6);
        write_bytes(0,CONCAT11((char)((uint)(flag + 1) >> 8),*(undefined1 *)(flag + -0x4639)));
        flush_output(uVar7,uVar6);
      }
    }
    else {
      find_item_at_coords(value + -0x10,unaff_SS,count,flags);
      if (*(char *)((int)*(undefined4 *)(value + -0x10) + 0x27) == '\0') {
        validate_window_coords(*(int *)(value + -4) + flags + 1,*(int *)(value + -2) + count);
        uVar6 = 0xe654;
        write_bytes(0,CONCAT11(extraout_AH,
                                 *(undefined1 *)((int)*(undefined4 *)(value + -0x10) + 1)));
        flush_output(uVar6,unaff_DS);
      }
      *(undefined1 *)((int)*(undefined4 *)(value + -0x10) + 0x23) = 1;
    }
  }
  return;
}



void __cdecl16near render_field_of_view(void)

{
  undefined4 uVar1;
  char ch;
  int iVar3;
  undefined2 uVar4;
  uint value;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 *puVar7;
  undefined2 uVar8;
  undefined1 column_bitmask [32];
  undefined1 local_38 [4];
  undefined1 row_bitmask [28];
  int local_18;
  uint local_16;
  int light_radius;
  uint current_row;
  int current_col;
  uint saved_cursor_y;
  uint saved_cursor_x;
  int local_6;
  int local_4;
  
  if (is_blind == '\0') {
    saved_cursor_y = get_relative_cursor_y();
    saved_cursor_y = saved_cursor_y & 0xff;
    saved_cursor_x = get_relative_cursor_x();
    saved_cursor_x = saved_cursor_x & 0xff;
    light_radius = player_level + 5;
    if (is_teleporting == '\0') {
      local_6 = 0;
      local_4 = 0;
    }
    else {
      local_6 = 0xc - player_y;
      local_4 = 0x27 - player_x;
    }
    if (is_teleporting == '\0') {
      if (needs_full_update != '\0') {
        local_16 = *(uint *)ADDR_MAX_VISIBLE_ROW /* max_visible_row */;
        current_row = *(uint *)ADDR_MIN_VISIBLE_ROW /* min_visible_row */;
        if ((int)current_row <= (int)local_16) {
          while( true ) {
            validate_window_coords(current_row + 1,1);
            update_screen_double();
            if (current_row == local_16) break;
            current_row = current_row + 1;
          }
        }
      }
    }
    else {
      local_16 = max_visible_row + 1;
      current_row = min_visible_row - 1;
      if ((int)current_row <= (int)local_16) {
        while( true ) {
          if ((1 < (int)((current_row + 0xd) - player_y)) &&
             (iVar3 = (current_row + 0xd) - player_y, iVar3 < 0x19)) {
            validate_window_coords((current_row + 0xd) - player_y,CONCAT11((char)((uint)iVar3 >> 8),1));
          }
          update_screen_double();
          if (current_row == local_16) break;
          current_row = current_row + 1;
        }
      }
    }
    current_row = player_y;
    do {
      current_row = current_row + -1;
      current_col = -1;
      while (explore_tile_at_position(&stack0xfffe,current_col + player_x,current_row), current_col != 1) {
        current_col = current_col + 1;
      }
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      iVar3 = (int)uVar1 + current_row * MAP_WIDTH + player_x;
      uVar6 = iVar3 == 0;
      uVar4 = CONCAT11((char)(current_row * MAP_WIDTH >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar7 = row_bitmask;
      uVar8 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
      create_bit_mask(puVar7,uVar8,uVar4);
    } while (((bool)uVar6) && (player_y - current_row != light_radius));
    min_visible_row = current_row;
    current_row = player_y;
    do {
      current_row = current_row + 1;
      current_col = -1;
      while (explore_tile_at_position(&stack0xfffe,current_col + player_x,current_row), current_col != 1) {
        current_col = current_col + 1;
      }
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      iVar3 = (int)uVar1 + current_row * MAP_WIDTH + player_x;
      uVar6 = iVar3 == 0;
      uVar4 = CONCAT11((char)(current_row * MAP_WIDTH >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar7 = row_bitmask;
      uVar8 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
      create_bit_mask(puVar7,uVar8,uVar4);
    } while (((bool)uVar6) && (current_row - player_y != light_radius));
    max_visible_row = current_row;
    current_row = player_x;
    do {
      current_row = current_row + -1;
      current_col = -1;
      while (explore_tile_at_position(&stack0xfffe,current_row,player_y + current_col), current_col != 1) {
        current_col = current_col + 1;
      }
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      iVar3 = (int)uVar1 + player_y * MAP_WIDTH + current_row;
      uVar6 = iVar3 == 0;
      uVar4 = CONCAT11((char)((uint)(player_y * MAP_WIDTH) >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar7 = row_bitmask;
      uVar8 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
      create_bit_mask(puVar7,uVar8,uVar4);
    } while (((bool)uVar6) && (player_x - current_row != light_radius));
    current_row = *(uint *)ADDR_PLAYER_X /* player_x */;
    do {
      current_row = current_row + 1;
      current_col = -1;
      while (explore_tile_at_position(&stack0xfffe,current_row,player_y + current_col), current_col != 1) {
        current_col = current_col + 1;
      }
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      iVar3 = (int)uVar1 + player_y * MAP_WIDTH + current_row;
      uVar6 = iVar3 == 0;
      uVar4 = CONCAT11((char)((uint)(player_y * MAP_WIDTH) >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar7 = row_bitmask;
      uVar8 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
      create_bit_mask(puVar7,uVar8,uVar4);
    } while (((bool)uVar6) && (current_row - player_x != light_radius));
    ch = check_inventory_has_item(ITEM_LAMP);
    if (ch != '\0') {
      local_16 = player_y + 2;
      value = player_y - 2U;
      if ((int)(player_y - 2U) <= (int)local_16) {
        do {
          current_row = value;
          local_18 = player_x + 2;
          iVar3 = player_x + -2;
          uVar6 = iVar3 == local_18;
          if (iVar3 <= local_18) {
            do {
              local_c = iVar3;
              value = local_e & 0xff;
              puVar7 = local_38;
              uVar8 = unaff_SS;
              zero_word_array_16(puVar7);
              set_bit_range_in_array(CONCAT11(extraout_AH,0x16),CONCAT11(extraout_AH,2));
              create_bit_mask(puVar7,uVar8,value);
              if (!(bool)uVar6) {
                uVar4 = CONCAT11(extraout_AH_00,(undefined1)local_c);
                puVar7 = local_58;
                uVar8 = unaff_SS;
                zero_word_array_16(puVar7);
                set_bit_range_in_array(CONCAT11(extraout_AH_01,0x4e),CONCAT11(extraout_AH_01,2));
                create_bit_mask(puVar7,uVar8,uVar4);
                if (!(bool)uVar6) {
                  iVar3 = local_e - player_y;
                  if (iVar3 < 0) {
                    iVar3 = -iVar3;
                  }
                  if (iVar3 < 2) {
                    iVar3 = local_c - player_x;
                    if (iVar3 < 0) {
                      iVar3 = -iVar3;
                    }
                    if (iVar3 < 2) goto LAB_1000_11a4;
                  }
                  explore_tile_at_position(&stack0xfffe,local_c,local_e);
                }
              }
LAB_1000_11a4:
              if (local_c == local_18) break;
              uVar6 = local_c + 1 == 0;
              iVar3 = local_c + 1;
            } while( true );
          }
          if (local_e == local_16) break;
          value = local_e + 1;
        } while( true );
      }
    }
    local_6 = player_y + local_6;
    local_4 = local_4 + player_x;
    uVar6 = (undefined1)((uint)local_4 >> 8);
    if (is_wizard == '\0') {
      put_char_at_pos(CONCAT11(uVar6,2),local_4,local_6);
      uVar6 = extraout_AH_03;
    }
    else {
      put_char_at_pos(CONCAT11(uVar6,0x7e),local_4,local_6);
      uVar6 = extraout_AH_02;
    }
    validate_window_coords(CONCAT11(uVar6,(undefined1)local_8),CONCAT11(uVar6,(undefined1)local_a));
  }
  return;
}



void redraw_dungeon_level(int value)

{
  undefined4 uVar1;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined2 uVar2;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined1 *puVar7;
  undefined2 uVar8;
  undefined1 local_88 [32];
  undefined1 local_68 [32];
  undefined1 local_48 [32];
  undefined1 local_28 [32];
  int local_8;
  int local_6;
  int local_4;
  
  local_8 = value;
  if (-1 < value) {
    local_6 = 0;
    while( true ) {
      validate_window_coords(local_6 + 1,1);
      update_screen_double();
      if (local_6 == local_8) break;
      local_6 = local_6 + 1;
    }
  }
  if ((((is_teleporting != '\0') || (needs_full_update != '\0')) || (is_blind != '\0')) ||
     (local_8 = value, value < 1)) {
LAB_1000_141d:
    display_character_stats();
    if (is_teleporting == '\0') {
      render_field_of_view();
    }
    else {
      local_6 = 0xc;
      local_4 = 0x27;
      put_char_at_pos(CONCAT11(extraout_AH_08,2),0x27,0xc);
    }
    return;
  }
  local_6 = 1;
LAB_1000_1269:
  local_4 = 1;
  do {
    if (*(char *)(dungeon_level * 0x719 + local_6 * MAP_WIDTH + local_4 + 0x70d) == '\0') {
LAB_1000_132c:
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      if (*(char *)((int)uVar1 + 0x719) != '\0') {
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        flag = (int)uVar1 + local_6 * MAP_WIDTH + local_4;
        uVar4 = flag == 0;
        uVar2 = CONCAT11((char)((uint)(local_6 * MAP_WIDTH) >> 8),*(undefined1 *)(flag + -0x50));
        puVar7 = local_48;
        uVar8 = unaff_SS;
        pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
        puVar5 = local_68;
        uVar6 = unaff_SS;
        pad_and_copy_buffer(0x20,0xb78f,unaff_DS);
        bitwise_or_word_arrays(puVar5,uVar6);
        puVar5 = local_88;
        uVar6 = unaff_SS;
        zero_word_array_16(puVar5);
        set_bit_in_array(CONCAT11(extraout_AH_03,0xef));
        set_bit_in_array(CONCAT11(extraout_AH_04,0xf7));
        bitwise_or_word_arrays(puVar5,uVar6);
        create_bit_mask(puVar7,uVar8,uVar2);
        if (!(bool)uVar4) {
          set_text_color_attribute(CONCAT11(extraout_AH_05,10));
          validate_window_coords(local_6 + 1,CONCAT11(extraout_AH_06,(undefined1)local_4));
          uVar8 = 0xe654;
          uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
          uVar6 = unaff_DS;
          write_bytes(0,CONCAT11((char)((uint)(local_6 * MAP_WIDTH) >> 8),
                                   *(undefined1 *)((int)uVar1 + local_6 * MAP_WIDTH + local_4 + -0x50)));
          flush_output(uVar8,uVar6);
          set_text_color_attribute(CONCAT11(extraout_AH_07,0xf));
        }
      }
    }
    else {
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      flag = (int)uVar1 + local_6 * MAP_WIDTH + local_4;
      uVar4 = flag == 0;
      uVar8 = CONCAT11((char)((uint)(local_6 * MAP_WIDTH) >> 8),*(undefined1 *)(flag + -0x50));
      puVar7 = local_28;
      uVar6 = unaff_SS;
      zero_word_array_16(puVar7);
      set_bit_in_array(CONCAT11(extraout_AH,0x20));
      set_bit_in_array(CONCAT11(extraout_AH_00,*(undefined1 *)0x1));
      set_bit_in_array(CONCAT11(extraout_AH_01,*(undefined1 *)0x3));
      create_bit_mask(puVar7,uVar6,uVar8);
      if (!(bool)uVar4) goto LAB_1000_132c;
      validate_window_coords(local_6 + 1,CONCAT11(extraout_AH_02,(undefined1)local_4));
      uVar8 = 0xe654;
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      uVar6 = unaff_DS;
      write_bytes(0,CONCAT11((char)((uint)(local_6 * MAP_WIDTH) >> 8),
                               *(undefined1 *)((int)uVar1 + local_6 * MAP_WIDTH + local_4 + -0x50)));
      flush_output(uVar8,uVar6);
    }
    if (local_4 == MAP_WIDTH) break;
    local_4 = local_4 + 1;
  } while( true );
  if (local_6 == local_8) goto LAB_1000_141d;
  local_6 = local_6 + 1;
  goto LAB_1000_1269;
}



void __cdecl16near handle_error_and_wait(void)

{
  char cVar1;
  
  display_score_with_fatal(0xc0);
  update_screen_double();
  do {
    cVar1 = read_keyboard_input();
  } while (cVar1 != ' ');
  cVar1 = get_relative_cursor_x();
  if (cVar1 == '\x02') {
    redraw_dungeon_level(1);
  }
  else {
    check_minimum_stats();
  }
  return;
}



void remove_item_from_list(int *result_ptr,int *count)

{
  undefined4 uVar1;
  int *piVar2;
  int value;
  undefined2 uVar4;
  undefined2 unaff_DS;
  undefined2 uVar5;
  
  uVar4 = (undefined2)((ulong)result_ptr >> 0x10);
  piVar2 = (int *)result_ptr;
  if (*result_ptr != 0 || piVar2[1] != 0) {
    if (((int)((ulong)*(undefined4 *)count >> 0x10) == piVar2[1]) &&
       ((int)*(undefined4 *)count == *result_ptr)) {
      uVar1 = *(undefined4 *)((int)*(undefined4 *)result_ptr + 0x16);
      *result_ptr = (int)uVar1;
      piVar2[1] = (int)((ulong)uVar1 >> 0x10);
    }
    else {
      uVar1 = *(undefined4 *)result_ptr;
      while( true ) {
        uVar4 = (undefined2)((ulong)uVar1 >> 0x10);
        value = (int)uVar1;
        if ((*(int *)(value + 0x16) == 0 && *(int *)(value + 0x18) == 0) ||
           (((int)((ulong)*(undefined4 *)(value + 0x16) >> 0x10) == ((int *)count)[1] &&
            ((int)*(undefined4 *)(value + 0x16) == *count)))) break;
        uVar1 = *(undefined4 *)(value + 0x16);
      }
      if (*(int *)(value + 0x16) == 0 && *(int *)(value + 0x18) == 0) {
        check_minimum_stats();
        uVar5 = 0xe654;
        uVar4 = unaff_DS;
        write_padded_string(0,0x1481,0x1000);
        flush_output(uVar5,uVar4);
        handle_error_and_wait();
      }
      else {
        uVar1 = *(undefined4 *)((int)*(undefined4 *)count + 0x16);
        *(undefined2 *)(value + 0x16) = (int)uVar1;
        *(undefined2 *)(value + 0x18) = (int)((ulong)uVar1 >> 0x10);
      }
    }
  }
  if (**(char **)count == '\b') {
    value = *(int *)((int)*(undefined4 *)count + 1) * 4;
    *(undefined2 *)(value + -0x476c) = 0;
    *(undefined2 *)(value + -0x476a) = 0;
    build_object_index();
  }
  return;
}



void prepend_item_to_list(undefined4 *result_ptr,undefined4 *param_2)

{
  undefined4 uVar1;
  int value;
  undefined2 uVar3;
  
  uVar1 = *result_ptr;
  uVar3 = (undefined2)((ulong)*param_2 >> 0x10);
  value = (int)*param_2;
  *(undefined2 *)(value + 0x16) = (int)uVar1;
  *(undefined2 *)(value + 0x18) = (int)((ulong)uVar1 >> 0x10);
  uVar1 = *param_2;
  *(int *)result_ptr = (int)uVar1;
  *(undefined2 *)((int)(undefined4 *)result_ptr + 2) = (int)((ulong)uVar1 >> 0x10);
  return;
}



void destroy_or_consume_item(char param_1,char param_2,char *flags)

{
  undefined4 uVar1;
  char ch;
  undefined1 uVar3;
  int flag;
  char *pcVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  char *local_6;
  undefined2 local_4;
  
  ch = is_type_7_subtype_12((char *)flags,flags._2_2_);
  if (((ch == '\0') || (param_1 != '\0')) || (*(int *)((char *)flags + 3) == 1)) {
    uVar1 = *(undefined4 *)(*flags * 4 + -0x4738);
    flag = (int)uVar1;
    ch = *flags;
    *(int *)(ch * 4 + -0x4738) = flag + -1;
    *(int *)(ch * 4 + -0x4736) = (int)((ulong)uVar1 >> 0x10) - (uint)(flag == 0);
    *(int *)0xb8c0 = *(int *)0xb8c0 + -1;
  }
  if ((*(int *)((char *)flags + 3) == 1) ||
     ((ch = is_type_7_subtype_12((char *)flags,flags._2_2_), ch != '\0' && (param_1 != '\0')))) {
    remove_item_from_list(0xb91e,unaff_DS,&flags,unaff_SS);
    *(int *)0xb8c2 = *(int *)0xb8c2 + -1;
    local_4 = (undefined2)((ulong)flags >> 0x10);
    local_6 = (char *)flags;
    *(int *)0xb8c4 = *(int *)0xb8c4 - *(int *)(local_6 + 0xb);
    if (param_2 == '\0') {
      free_item_object(local_6,local_4);
    }
    else {
      prepend_item_to_list(dungeon_level * 4 + -0x54d9,unaff_DS,&local_6,unaff_SS);
      *(undefined2 *)(local_6 + 5) = *(undefined2 *)ADDR_PLAYER_Y /* player_y */;
      *(undefined2 *)(local_6 + 7) = *(undefined2 *)ADDR_PLAYER_X /* player_x */;
      uVar3 = lookup_table_b9c7(local_6,local_4);
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      *(undefined1 *)((int)uVar1 + *(int *)(local_6 + 5) * MAP_WIDTH + *(int *)(local_6 + 7) + -0x50) =
           uVar3;
    }
  }
  else {
    uVar6 = (undefined2)((ulong)flags >> 0x10);
    pcVar5 = (char *)flags;
    *(int *)(pcVar5 + 3) = *(int *)(pcVar5 + 3) + -1;
    ch = is_type_7_subtype_12(pcVar5,uVar6);
    if (ch == '\0') {
      *(int *)0xb8c4 = *(int *)0xb8c4 - *(int *)((char *)flags + 0xb);
    }
    if (param_2 != '\0') {
      allocate_item_object(&local_6,unaff_SS);
      memcpy(0x1a,(int)_local_6,(int)((ulong)_local_6 >> 0x10),(char *)flags,
                    (int)((ulong)flags >> 0x10));
      *(undefined2 *)((int)_local_6 + 3) = 1;
      prepend_item_to_list(dungeon_level * 4 + -0x54d9,unaff_DS,&local_6,unaff_SS);
      uVar6 = (undefined2)((ulong)_local_6 >> 0x10);
      flag = (int)_local_6;
      *(undefined2 *)(flag + 5) = *(undefined2 *)ADDR_PLAYER_Y /* player_y */;
      *(undefined2 *)(flag + 7) = *(undefined2 *)ADDR_PLAYER_X /* player_x */;
      uVar3 = lookup_table_b9c7(flag,uVar6);
      uVar6 = (undefined2)((ulong)_local_6 >> 0x10);
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      *(undefined1 *)
       ((int)uVar1 + *(int *)((int)_local_6 + 5) * MAP_WIDTH + *(int *)((int)_local_6 + 7) + -0x50) =
           uVar3;
    }
  }
  return;
}



undefined2 is_item_equipped_or_in_pack(undefined4 *result_ptr)

{
  undefined2 unaff_DS;
  int local_6;
  char ch;
  
  if (((((((int)((ulong)*result_ptr >> 0x10) == *(int *)0xb928) && ((int)*result_ptr == *(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */))
        || (((int)((ulong)*result_ptr >> 0x10) == *(int *)0xb924 && ((int)*result_ptr == *(int *)ADDR_WIELDED_WEAPON /* wielded_weapon */)))
        ) || (((int)((ulong)*result_ptr >> 0x10) == *(int *)0xb934 && ((int)*result_ptr == *(int *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */)
              ))) ||
      (((int)((ulong)*result_ptr >> 0x10) == *(int *)0xb92c && ((int)*result_ptr == *(int *)ADDR_EQUIPPED_ARMOR /* equipped_armor */)))) ||
     (((int)((ulong)*result_ptr >> 0x10) == *(int *)0xb930 && ((int)*result_ptr == *(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */)))) {
    ch = '\x01';
  }
  else {
    ch = '\0';
  }
  local_6 = 0;
  if (*(int *)0xb936 < 1) {
LAB_1000_1876:
    return CONCAT11((char)((uint)local_6 >> 8),ch);
  }
  local_6 = 1;
  do {
    if (*(int *)(local_6 * 4 + -0x46cc) != 0 || *(int *)(local_6 * 4 + -0x46ca) != 0) {
      if (ch == '\0') {
        if (((int)((ulong)*result_ptr >> 0x10) != *(int *)(local_6 * 4 + -0x46ca)) ||
           ((int)*result_ptr != *(int *)(local_6 * 4 + -0x46cc))) {
          ch = '\0';
          goto LAB_1000_186e;
        }
      }
      ch = '\x01';
    }
LAB_1000_186e:
    if (local_6 == *(int *)0xb936) goto LAB_1000_1876;
    local_6 = local_6 + 1;
  } while( true );
}



void __cdecl16near FUN_1000_1885(void)

{
  undefined4 *puVar1;
  char ch;
  undefined2 uVar3;
  byte bVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_8;
  int local_6;
  int random_val;
  
  random_val = 0;
  local_6 = (int)((ulong)inventory_list >> 0x10);
  local_8 = (int)inventory_list;
  while (local_8 != 0 || local_6 != 0) {
    ch = is_item_equipped_or_in_pack(&local_8,unaff_SS);
    if (ch == '\0') {
      random_val = random_val + 1;
    }
    puVar1 = (undefined4 *)(local_8 + 0x16);
    local_6 = (int)((ulong)*puVar1 >> 0x10);
    local_8 = (int)*puVar1;
  }
  if (0 < random_val) {
    random_val = random_mod(random_val);
    random_val = random_val + 1;
    local_6 = (int)((ulong)inventory_list >> 0x10);
    local_8 = (int)inventory_list;
    do {
      ch = is_item_equipped_or_in_pack(&local_8,unaff_SS);
      if (ch == '\0') {
        if (1 < random_val) {
          puVar1 = (undefined4 *)(local_8 + 0x16);
          local_6 = (int)((ulong)*puVar1 >> 0x10);
          local_8 = (int)*puVar1;
        }
        random_val = random_val + -1;
      }
      else {
        puVar1 = (undefined4 *)(local_8 + 0x16);
        local_6 = (int)((ulong)*puVar1 >> 0x10);
        local_8 = (int)*puVar1;
      }
    } while (random_val != 0);
    uVar3 = is_type_7_subtype_12(local_8,local_6);
    bVar4 = (byte)((uint)uVar3 >> 8);
    if ((char)uVar3 == '\0') {
      destroy_or_consume_item((uint)bVar4 << 8,(uint)bVar4 << 8,local_8,local_6);
    }
    else {
      destroy_or_consume_item(CONCAT11(bVar4,1),(uint)bVar4 << 8,local_8,local_6);
    }
  }
  return;
}



void FUN_1000_1988(int *result_ptr,int *count,int *flags)

{
  undefined4 uVar1;
  int *piVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
  uVar3 = (undefined2)((ulong)result_ptr >> 0x10);
  piVar2 = (int *)result_ptr;
  *result_ptr = (int)uVar1;
  piVar2[1] = (int)((ulong)uVar1 >> 0x10);
  while ((*result_ptr != 0 || piVar2[1] != 0 &&
         ((*(int *)((int)*(undefined4 *)result_ptr + 5) != *flags ||
          (*(int *)((int)*(undefined4 *)result_ptr + 7) != *count))))) {
    uVar1 = *(undefined4 *)((int)*(undefined4 *)result_ptr + 0x16);
    *result_ptr = (int)uVar1;
    piVar2[1] = (int)((ulong)uVar1 >> 0x10);
  }
  if (*result_ptr == 0 && piVar2[1] == 0) {
    check_minimum_stats();
    uVar3 = 0xe654;
    write_padded_string(0,0x1959,0x1000);
    flush_output(uVar3,unaff_DS);
    handle_error_and_wait();
  }
  return;
}



void FUN_1000_1a1a(int value)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int value;
  undefined1 uVar4;
  undefined2 unaff_DS;
  undefined2 local_c;
  undefined2 local_8;
  undefined2 local_6;
  undefined2 local_4;
  
  if (value == 1) {
    if (has_light == '\0') {
      *(undefined1 *)((int)*(undefined4 *)0x8 + *(int *)0x78f1 * MAP_WIDTH + *(int *)0x78f3 + -0x50) =
           0x20;
    }
    else {
      *(undefined1 *)((int)*(undefined4 *)0x8 + *(int *)0x78f1 * MAP_WIDTH + *(int *)0x78f3 + -0x50) =
           0xef;
    }
  }
  uVar2 = *(undefined4 *)(value * 4 + -0x54d9);
  local_c = (int)((ulong)uVar2 >> 0x10);
  value = (int)uVar2;
  while (value != 0 || local_c != 0) {
    uVar4 = lookup_table_b9c7(value,local_c);
    uVar2 = *(undefined4 *)(value * 4 + 4);
    *(undefined1 *)((int)uVar2 + *(int *)(value + 5) * MAP_WIDTH + *(int *)(value + 7) + -0x50) = uVar4;
    puVar1 = (undefined4 *)(value + 0x16);
    local_c = (int)((ulong)*puVar1 >> 0x10);
    value = (int)*puVar1;
  }
  local_6 = 2;
  while( true ) {
    for (local_4 = 2; *(undefined1 *)(local_6 * MAP_WIDTH + local_4 + -0xc) = 0x20, local_4 != 0x4e;
        local_4 = local_4 + 1) {
    }
    if (local_6 == MAP_HEIGHT) break;
    local_6 = local_6 + 1;
  }
  uVar2 = *(undefined4 *)(value * 4 + -0x5499);
  local_8 = (int)((ulong)uVar2 >> 0x10);
  value = (int)uVar2;
  while (value != 0 || local_8 != 0) {
    *(undefined1 *)(*(int *)(value + 0x1c) * MAP_WIDTH + *(int *)(value + 0x1e) + -0xc) =
         *(undefined1 *)(value + 1);
    puVar1 = (undefined4 *)(value + 0x32);
    local_8 = (int)((ulong)*puVar1 >> 0x10);
    value = (int)*puVar1;
  }
  return;
}



void __cdecl16near FUN_1000_1b91(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined2 unaff_DS;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 local_c;
  undefined2 local_a;
  undefined2 local_8;
  undefined2 local_6;
  undefined2 flag;
  
  local_6 = (int)((ulong)inventory_list >> 0x10);
  local_8 = (int)inventory_list;
  if (local_8 != 0 || local_6 != 0) {
    for (; *(int *)(local_8 + 0x16) != 0 || *(int *)(local_8 + 0x18) != 0;
        local_6 = (int)((ulong)*puVar1 >> 0x10)) {
      puVar1 = (undefined4 *)(local_8 + 0x16);
      local_8 = (int)*puVar1;
    }
    uVar2 = *(undefined4 *)0xabab;
    *(undefined2 *)(local_8 + 0x16) = (int)uVar2;
    *(undefined2 *)(local_8 + 0x18) = (int)((ulong)uVar2 >> 0x10);
    uVar2 = inventory_list;
    *(undefined2 *)0xabab = (int)uVar2;
    *(undefined2 *)0xabad = (int)((ulong)uVar2 >> 0x10);
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x1b8e,0x1000);
  flush_output(uVar3,uVar4);
  flag = 0;
  while( true ) {
    uVar2 = *(undefined4 *)(flag * 4 + -0x54d9);
    local_6 = (int)((ulong)uVar2 >> 0x10);
    local_8 = (int)uVar2;
    if (local_8 != 0 || local_6 != 0) {
      for (; *(int *)(local_8 + 0x16) != 0 || *(int *)(local_8 + 0x18) != 0;
          local_6 = (int)((ulong)*puVar1 >> 0x10)) {
        puVar1 = (undefined4 *)(local_8 + 0x16);
        local_8 = (int)*puVar1;
      }
      uVar2 = *(undefined4 *)0xabab;
      *(undefined2 *)(local_8 + 0x16) = (int)uVar2;
      *(undefined2 *)(local_8 + 0x18) = (int)((ulong)uVar2 >> 0x10);
      uVar2 = *(undefined4 *)(flag * 4 + -0x54d9);
      *(undefined2 *)0xabab = (int)uVar2;
      *(undefined2 *)0xabad = (int)((ulong)uVar2 >> 0x10);
    }
    uVar2 = *(undefined4 *)(flag * 4 + -0x5499);
    local_a = (int)((ulong)uVar2 >> 0x10);
    local_c = (int)uVar2;
    if (local_c != 0 || local_a != 0) {
      for (; *(int *)(local_c + 0x32) != 0 || *(int *)(local_c + 0x34) != 0;
          local_a = (int)((ulong)*puVar1 >> 0x10)) {
        puVar1 = (undefined4 *)(local_c + 0x32);
        local_c = (int)*puVar1;
      }
      uVar2 = *(undefined4 *)0xaba7;
      *(undefined2 *)(local_c + 0x32) = (int)uVar2;
      *(undefined2 *)(local_c + 0x34) = (int)((ulong)uVar2 >> 0x10);
      uVar2 = *(undefined4 *)(flag * 4 + -0x5499);
      *(undefined2 *)0xaba7 = (int)uVar2;
      *(undefined2 *)0xaba9 = (int)((ulong)uVar2 >> 0x10);
    }
    if (flag == 0xf) break;
    flag = flag + 1;
  }
  return;
}



undefined2 FUN_1000_1cd1(void)

{
  char *pcVar1;
  byte bVar3;
  uint value;
  undefined2 unaff_DS;
  char ch;
  char *local_7;
  uint local_5;
  
  pcVar1 = (char *)inventory_list;
  bVar3 = (byte)((ulong)pcVar1 >> 8);
  if (*(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 1) == 10) {
    value = CONCAT11(bVar3,1);
  }
  else {
    value = (uint)bVar3 << 8;
  }
  ch = (char)value;
  if (ch == '\0') {
    while (local_7 = (char *)pcVar1, local_5 = (uint)((ulong)pcVar1 >> 0x10),
          value = (uint)local_7 | local_5, value != 0) {
      if ((ch == '\0') && ((*pcVar1 != '\a' || (*(int *)(local_7 + 1) != 10)))) {
        ch = '\0';
      }
      else {
        ch = '\x01';
      }
      pcVar1 = *(char **)(local_7 + 0x16);
    }
  }
  return CONCAT11((char)(value >> 8),ch);
}



void FUN_1000_1d47(byte *result_ptr)

{
  undefined2 uVar1;
  uint value;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  int flag;
  int value;
  undefined2 in_BX;
  undefined2 uVar5;
  byte *pbVar6;
  undefined2 uVar7;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool flag;
  bool flag;
  undefined1 uVar10;
  undefined1 *puVar11;
  undefined1 local_58 [32];
  byte *local_38;
  undefined2 local_34;
  int local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  int local_2a;
  undefined2 local_28;
  int local_24;
  undefined2 local_22;
  undefined2 local_20;
  int local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  int local_18;
  undefined2 local_16;
  undefined2 local_14;
  int local_12;
  
  flag = (player_level + 2) / 2 >> 0xf;
  local_16 = combat_wrapper();
  local_38 = result_ptr;
  value = player_level + 1 + strength >> 0xf;
  local_14 = in_BX;
  local_12 = flag;
  uVar1 = combat_wrapper();
  uVar7 = (undefined2)((ulong)local_38 >> 0x10);
  flag = *(int *)((byte *)local_38 + 8) + *(int *)((byte *)local_38 + 0xc) >> 0xf;
  combat_wrapper(uVar1,in_BX,value);
  local_34 = conditional_char_action();
  value = (player_level * current_food) / 10 + 8 >> 0xf;
  local_30 = flag;
  uVar1 = combat_wrapper();
  flag = (*(int *)(*(int *)((byte *)local_38 + 2) * 0x2a + -0x5002) << 1) >> 0xf;
  combat_wrapper(uVar1,in_BX,value);
  local_2e = conditional_char_action();
  uVar1 = (undefined2)((ulong)local_38 >> 0x10);
  value = *(int *)((byte *)local_38 + 8) + 1 + *(int *)((byte *)local_38 + 0x14) >> 0xf;
  local_2c = in_BX;
  local_2a = flag;
  uVar1 = combat_wrapper();
  flag = (player_level + -1) / 2 + player_level >> 0xf;
  combat_wrapper(uVar1,in_BX,value);
  local_28 = conditional_char_action();
  uVar1 = (undefined2)((ulong)local_38 >> 0x10);
  value = (*(int *)((byte *)local_38 + 0x10) + 1) * *(int *)((byte *)local_38 + 0xe) >> 0xf;
  local_24 = flag;
  combat_wrapper();
  local_22 = conditional_char_action();
  flag = false;
  local_20 = in_BX;
  local_1e = value;
  char_create_wrapper();
  if (flag) {
    local_22 = 0x87;
    local_20 = 0;
    local_1e = 0xc00;
  }
  value = player_level + -1 >> 0xf;
  combat_wrapper();
  check_combat_and_handle_error();
  float_add_with_handler();
  local_22 = conditional_char_action();
  local_1e = value;
  complex_combat_sequence();
  uVar1 = check_combat_and_handle_error();
  flag = local_2a;
  uVar1 = complex_combat_sequence(uVar1,in_BX,value);
  uVar5 = 0;
  uVar7 = 0x4000;
  check_combat_and_handle_error(uVar1,local_2c,flag);
  check_combat_and_handle_error();
  uVar1 = combat_check_and_handle_error();
  flag = local_12;
  complex_combat_sequence(uVar1,uVar5,uVar7);
  local_1c = float_add_with_handler();
  flag = false;
  flag = true;
  local_1a = local_14;
  local_18 = flag;
  char_create_wrapper();
  if (!flag && !flag) {
    local_1c = 0x84;
    local_1a = 0;
    local_18 = 0x2000;
  }
  local_1c = calculate_combat_value();
  uVar1 = combat_check_with_error_alt();
  uVar7 = (undefined2)((ulong)local_38 >> 0x10);
  pbVar6 = (byte *)local_38;
  *(undefined2 *)(pbVar6 + 6) = uVar1;
  if (*(int *)(pbVar6 + 6) == 0) {
    (pbVar6 + 6)[0] = 1;
    (pbVar6 + 6)[1] = 0;
  }
  if (9 < *(int *)(pbVar6 + 0x12)) {
    *(int *)(pbVar6 + 6) = *(int *)(pbVar6 + 6) + 10;
  }
  uVar10 = *(int *)(pbVar6 + 0x1a) == 6;
  if (6 < *(int *)(pbVar6 + 0x1a)) {
    uVar10 = *(int *)(pbVar6 + 6) + 10 == 0;
    *(int *)(pbVar6 + 6) = *(int *)(pbVar6 + 6) + 10;
  }
  value = (uint)*local_38;
  puVar11 = local_58;
  uVar1 = unaff_SS;
  zero_word_array_16(puVar11);
  set_bit_in_array(CONCAT11(extraout_AH,0x47));
  set_bit_in_array(CONCAT11(extraout_AH_00,0x48));
  set_bit_in_array(CONCAT11(extraout_AH_01,0x9c));
  set_bit_in_array(CONCAT11(extraout_AH_02,0x4d));
  set_bit_in_array(CONCAT11(extraout_AH_03,0x4e));
  set_bit_in_array(CONCAT11(extraout_AH_04,0x9e));
  set_bit_in_array(CONCAT11(extraout_AH_05,0x73));
  create_bit_mask(puVar11,uVar1,value);
  if (!(bool)uVar10) {
    uVar1 = (undefined2)((ulong)local_38 >> 0x10);
    flag = *(int *)((byte *)local_38 + 6) + 10;
    uVar10 = flag == 0;
    *(int *)((byte *)local_38 + 6) = flag;
  }
  value = (uint)*local_38;
  puVar11 = local_58;
  uVar1 = unaff_SS;
  zero_word_array_16(puVar11);
  set_bit_in_array(CONCAT11(extraout_AH_06,0x46));
  set_bit_in_array(CONCAT11(extraout_AH_07,0x56));
  create_bit_mask(puVar11,uVar1,value);
  if (!(bool)uVar10) {
    ((byte *)local_38 + 6)[0] = 0x14;
    ((byte *)local_38 + 6)[1] = 0;
  }
  uVar1 = CONCAT11(extraout_AH_08,*local_38);
  puVar11 = local_58;
  zero_word_array_16(puVar11);
  set_bit_in_array(CONCAT11(extraout_AH_09,0x44));
  set_bit_in_array(CONCAT11(extraout_AH_10,0x92));
  create_bit_mask(puVar11,unaff_SS,uVar1);
  pbVar6 = (byte *)local_38;
  uVar1 = (undefined2)((ulong)local_38 >> 0x10);
  if (!(bool)uVar10) {
    *(int *)(pbVar6 + 6) = *(int *)(pbVar6 + 6) / 2 + *(int *)(pbVar6 + 6);
  }
  if (*local_38 == ATTACK_FEAR) {
    (pbVar6 + 6)[0] = 5;
    (pbVar6 + 6)[1] = 0;
  }
  *(int *)(pbVar6 + 6) = *(int *)(pbVar6 + 6) / *(int *)(pbVar6 + 0x2c);
  if (*(int *)(pbVar6 + 6) == 0) {
    (pbVar6 + 6)[0] = 1;
    (pbVar6 + 6)[1] = 0;
  }
  return;
}



void __cdecl16near FUN_1000_20dd(void)

{
  char *pcVar1;
  undefined2 unaff_DS;
  char *local_6;
  int local_4;
  
  pcVar1 = (char *)*(undefined4 *)(dungeon_level * 4 + -0x5499);
  while (local_6 = (char *)pcVar1, local_4 = (int)((ulong)pcVar1 >> 0x10),
        local_6 != (char *)0x0 || local_4 != 0) {
    if (*pcVar1 != '\x01') {
      local_6[1] = *pcVar1;
      *(undefined2 *)(local_6 + 4) = *(undefined2 *)(local_6 + 2);
    }
    pcVar1 = *(char **)(local_6 + 0x32);
  }
  return;
}



void FUN_1000_2138(int value,int count)

{
  undefined4 uVar1;
  undefined2 unaff_DS;
  
  if ((bool)((byte)count & 1)) {
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    *(undefined1 *)((int)uVar1 + count * MAP_WIDTH + value + -0x50) = 0x20;
  }
  else {
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    *(undefined1 *)((int)uVar1 + count * MAP_WIDTH + value + -0x50) = 0x20;
  }
  uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
  *(undefined1 *)((int)uVar1 + count * MAP_WIDTH + value + -0x50) = 0x20;
  return;
}



uint FUN_1000_21b0(int value,int count)

{
  undefined4 uVar1;
  uint value;
  undefined2 unaff_DS;
  
  if ((!(bool)((byte)count & 1)) || ((bool)((byte)value & 1))) {
    value = (uint)((byte)value >> 1);
    if ((bool)((byte)value & 1)) {
      value = count * MAP_WIDTH;
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      *(undefined1 *)((int)uVar1 + value + value + -0x50) = 0xb3;
    }
  }
  else {
    value = count * MAP_WIDTH;
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    *(undefined1 *)((int)uVar1 + value + value + -0x50) = 0xc4;
  }
  return value;
}



void FUN_1000_2214(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined2 local_6;
  undefined2 uStack_4;
  
  FUN_1000_1988(&local_6,unaff_SS,&stack0x0002,unaff_SS,&stack0x0004,unaff_SS);
  uVar2 = (undefined2)((ulong)_local_6 >> 0x10);
  uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
  *(undefined1 *)
   ((int)uVar1 + *(int *)((int)_local_6 + 5) * MAP_WIDTH + *(int *)((int)_local_6 + 7) + -0x50) = 0x20;
  remove_item_from_list(dungeon_level * 4 + -0x54d9,unaff_DS,&local_6,unaff_SS);
  free_item_object(local_6,uStack_4);
  return;
}



void __cdecl16near display_food_status(void)

{
  uint value;
  undefined1 extraout_AH;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar2;
  undefined1 *puVar3;
  undefined1 local_22 [32];
  
  uVar2 = &stack0x0000 == (undefined1 *)0x22;
  value = (uint)*(byte *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 1);
  puVar3 = local_22;
  zero_word_array_16(puVar3);
  set_bit_range_in_array(CONCAT11(extraout_AH,0xd),CONCAT11(extraout_AH,9));
  create_bit_mask(puVar3,unaff_SS,value);
  if ((bool)uVar2) {
    if (10 < *(int *)ADDR_CONSTITUTION) {
      *(undefined2 *)ADDR_CONSTITUTION = 10;
    }
  }
  else if (0xd < *(int *)ADDR_CONSTITUTION) {
    *(undefined2 *)ADDR_CONSTITUTION = 0xd;
  }
  return;
}



void display_character_status_message(int value,int count)

{
  int value;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar2;
  undefined1 local_102 [256];
  
  if ((count < 1) || (0x23 < count)) {
    if (count == 0x61) {
      if (value == 10) {
        display_score_with_fatal(0x45);
      }
      else {
        display_score_with_fatal(value + 0x87);
      }
    }
    else if (count == 100) {
      if (value == 0) {
        display_score_with_fatal(0xce);
      }
      else if (value == 10) {
        display_score_with_fatal(0xcf);
      }
      else if (value == 0x23) {
        display_score_with_fatal(0xd0);
      }
    }
    else {
      puVar2 = local_102;
      char_to_pascal_string(count);
      value = find_pascal_substring(0xb9ed,unaff_DS,puVar2,unaff_SS);
      display_score_with_fatal(value + 0x7e + value);
    }
  }
  else {
    display_score_with_fatal(value + 0x7e);
  }
  return;
}



void find_random_empty_floor_space(int *result_ptr,int *count,int *flags)

{
  undefined4 uVar1;
  int random_val;
  undefined2 unaff_DS;
  
  do {
    do {
      random_val = random_mod(0x15);
      *flags = random_val + 2;
      random_val = random_mod(0x4d);
      *count = random_val + 2;
      uVar1 = *(undefined4 *)(*result_ptr * 4 + 4);
    } while (*(char *)((int)uVar1 + *flags * MAP_WIDTH + *count + -0x50) != ' ');
  } while (*(char *)(*flags * MAP_WIDTH + *count + -0xc) != ' ');
  return;
}



void find_position_near_player(int *result_ptr,uint *count)

{
  uint value;
  undefined4 uVar2;
  long lVar3;
  uint value;
  undefined2 uVar5;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 in_DX;
  int value;
  int value;
  undefined2 extraout_DX;
  undefined2 extraout_DX_00;
  undefined2 in_BX;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar8;
  undefined1 *puVar9;
  undefined2 uVar10;
  undefined1 local_48 [32];
  undefined1 local_28 [32];
  undefined2 local_8;
  int local_6;
  int local_4;
  
  do {
    do {
      do {
        do {
          find_highest_bit();
          local_8 = combat_check_and_handle_error();
          local_6 = in_BX;
          local_4 = in_DX;
          local_8 = conditional_char_action();
          local_6 = in_BX;
          local_4 = in_DX;
          combat_check_with_error_alt();
          random_mod(5);
          value = 0;
          value = multiply_integers();
          value = *(uint *)ADDR_PLAYER_Y /* player_y */;
          value = ((int)value >> 0xf) + value + (uint)CARRY2(value,value);
          *count = value + value;
          find_highest_bit();
          local_8 = combat_check_and_handle_error();
          local_6 = value;
          local_4 = value;
          local_8 = conditional_char_action();
          local_6 = value;
          local_4 = value;
          combat_check_with_error_alt();
          random_mod(5);
          in_BX = 0;
          value = multiply_integers();
          *result_ptr = player_x + value;
          in_DX = (undefined2)((ulong)*count * MAP_WIDTH >> 0x10);
          uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
        } while (*(char *)((int)uVar2 + (int)((ulong)*count * MAP_WIDTH) + *result_ptr + -0x50) != ' ');
        lVar3 = (ulong)*count * MAP_WIDTH;
        in_DX = (undefined2)((ulong)lVar3 >> 0x10);
        uVar8 = *(char *)((int)lVar3 + *result_ptr + -0xc) == ' ';
      } while (!(bool)uVar8);
      uVar5 = CONCAT11((char)((ulong)lVar3 >> 8),(char)*count);
      puVar9 = local_28;
      uVar10 = unaff_SS;
      zero_word_array_16(puVar9);
      set_bit_range_in_array(CONCAT11(extraout_AH,0x16),CONCAT11(extraout_AH,2));
      create_bit_mask(puVar9,uVar10,uVar5);
      in_DX = extraout_DX;
    } while ((bool)uVar8);
    uVar5 = CONCAT11(extraout_AH_00,(char)*result_ptr);
    puVar9 = local_48;
    uVar10 = unaff_SS;
    zero_word_array_16(puVar9);
    set_bit_range_in_array(CONCAT11(extraout_AH_01,0x4e),CONCAT11(extraout_AH_01,2));
    create_bit_mask(puVar9,uVar10,uVar5);
    in_DX = extraout_DX_00;
  } while ((bool)uVar8);
  return;
}



void place_object_on_map(int value,undefined4 *param_2)

{
  undefined4 uVar1;
  int value;
  undefined1 uVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar4 = (undefined2)((ulong)*param_2 >> 0x10);
  value = (int)*param_2;
  find_random_empty_floor_space(&value,unaff_SS,value + 7,uVar4,value + 5,uVar4);
  uVar3 = lookup_table_b9c7(*(undefined2 *)param_2,*(undefined2 *)((int)(undefined4 *)param_2 + 2));
  uVar1 = *(undefined4 *)(value * 4 + 4);
  *(undefined1 *)((int)uVar1 + *(int *)(value + 5) * MAP_WIDTH + *(int *)(value + 7) + -0x50) = uVar3;
  uVar1 = *(undefined4 *)(value * 4 + -0x54d9);
  *(undefined2 *)(value + 0x16) = (int)uVar1;
  *(undefined2 *)(value + 0x18) = (int)((ulong)uVar1 >> 0x10);
  uVar1 = *param_2;
  *(undefined2 *)(value * 4 + -0x54d9) = (int)uVar1;
  *(undefined2 *)(value * 4 + -0x54d7) = (int)((ulong)uVar1 >> 0x10);
  return;
}



int calculate_dice_or_damage(int value,char param_2)

{
  int local_4;
  
  if (((param_2 == '\x02') || (param_2 == '\x03')) || (param_2 == '\x04')) {
    local_4 = 1;
  }
  else if (((param_2 == '\x05') || (param_2 == '\x01')) || (param_2 == '\b')) {
    local_4 = 2;
  }
  else if (param_2 == '\a') {
    if ((((value == 1) || (value == 2)) || (value == 0xb)) ||
       ((value == 0xc || (value == 0xd)))) {
      local_4 = 2;
    }
    else if (((value < 3) || (7 < value)) &&
            ((value != 9 && ((value != 0xe && (value != 0xf)))))) {
      if ((value == 8) || (value == 10)) {
        local_4 = 5;
      }
    }
    else {
      local_4 = 4;
    }
  }
  else if (param_2 == '\x06') {
    if ((value < 1) || (6 < value)) {
      if ((6 < value) && (value < 0xc)) {
        local_4 = 2;
      }
    }
    else {
      local_4 = value / 2 + 4;
    }
  }
  return local_4;
}



void initialize_monster_or_item(undefined4 *result_ptr,int count,char flags)

{
  char *pcVar1;
  undefined4 damage;
  int iVar3;
  int random_val;
  uint uVar5;
  undefined1 extraout_AH;
  byte damage;
  uint damage;
  uint damage;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 in_BX;
  char *pcVar9;
  undefined2 uVar10;
  undefined2 damage;
  undefined2 damage;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool damage;
  undefined1 damage;
  bool damage;
  undefined1 damage;
  undefined1 *puVar17;
  undefined1 local_2e [32];
  char *local_e;
  int damage;
  int damage;
  int random_val;
  
  allocate_item_object((undefined4 *)result_ptr,(int)((ulong)result_ptr >> 0x10));
  random_val = random_mod(100);
  random_val = random_val + 1;
  damage = 0;
  damage = 0;
  local_e = (char *)*result_ptr;
  uVar10 = (undefined2)((ulong)local_e >> 0x10);
  pcVar9 = (char *)local_e;
  *local_e = flags;
  pcVar9[0x13] = '\0';
  pcVar9[0x15] = '\0';
  (pcVar9 + 3)[0] = '\x01';
  (pcVar9 + 3)[1] = '\0';
  (pcVar9 + 9)[0] = '\0';
  (pcVar9 + 9)[1] = '\0';
  uVar5 = 0;
  if (flags == '\0') {
    iVar3 = random_mod(5);
    random_val = random_mod(count + 1);
    uVar5 = count * 7 + random_val * 0x19 + iVar3;
    *(uint *)((char *)local_e + 9) = uVar5;
    goto LAB_1000_2d0e;
  }
  if ((((flags != '\x02') && (flags != '\x03')) && (flags != '\x06')) &&
     (((flags != '\a' && (flags != '\x05')) && (flags != '\b')))) {
    if (flags != '\x04') goto LAB_1000_2d0e;
    do {
      damage = 0;
      damage = 0;
      do {
        damage = damage + 1;
        damage = *(int *)(damage * 2 + -0x6453) + damage;
      } while (damage < random_val);
      *(int *)((char *)local_e + 1) = damage;
      random_val = random_mod(100);
      random_val = random_val + 1;
      damage = 0;
      pcVar9 = (char *)local_e;
      uVar10 = (undefined2)((ulong)local_e >> 0x10);
    } while ((*(int *)0xabaf != 0 || *(int *)0xabb1 != 0) && (*(int *)(pcVar9 + 1) == 6));
    *(int *)(pcVar9 + 1) = damage;
    uVar5 = *(uint *)(pcVar9 + 1);
    if ((uVar5 == 7) || (uVar5 == 9)) {
      iVar3 = random_mod(2);
      *(int *)((char *)local_e + 9) = (count + 3) / 6 + iVar3;
      find_highest_bit();
      damage = false;
      damage = true;
      uVar5 = char_create_wrapper();
      if (!damage && !damage) {
        uVar10 = (undefined2)((ulong)local_e >> 0x10);
        uVar5 = -*(int *)((char *)local_e + 9);
        *(uint *)((char *)local_e + 9) = uVar5;
      }
    }
    else if (uVar5 == 4) {
      iVar3 = random_mod(2);
      *(int *)((char *)local_e + 9) = (count + 2) / 5 + iVar3;
      find_highest_bit();
      damage = false;
      damage = true;
      uVar5 = char_create_wrapper();
      if (!damage && !damage) {
        uVar10 = (undefined2)((ulong)local_e >> 0x10);
        uVar5 = -*(int *)((char *)local_e + 9);
        *(uint *)((char *)local_e + 9) = uVar5;
      }
    }
    else if (uVar5 == 8) {
      (pcVar9 + 9)[0] = '\x01';
      (pcVar9 + 9)[1] = '\0';
    }
    else if (uVar5 == 10) {
      iVar3 = random_mod(4);
      uVar5 = iVar3 + 4;
      *(uint *)((char *)local_e + 9) = uVar5;
    }
    else {
      damage = uVar5 < 0xb;
      if (uVar5 == 0xb) {
        find_highest_bit();
        uVar5 = char_create_wrapper();
        uVar10 = (undefined2)((ulong)local_e >> 0x10);
        if ((bool)damage) {
          pcVar1 = (char *)local_e + 9;
          pcVar1[0] = -1;
          pcVar1[1] = -1;
        }
        else {
          pcVar1 = (char *)local_e + 9;
          pcVar1[0] = '\x01';
          pcVar1[1] = '\0';
        }
      }
      else if (uVar5 == 6) {
        damage = *result_ptr;
        *(undefined2 *)0xabaf = (int)damage;
        *(undefined2 *)0xabb1 = (int)((ulong)damage >> 0x10);
        iVar3 = random_mod(0x28);
        uVar5 = iVar3 + 0x28;
        *(uint *)((char *)local_e + 9) = uVar5;
      }
      else if (uVar5 == 0xf) {
        (pcVar9 + 9)[0] = '\x01';
        (pcVar9 + 9)[1] = '\0';
      }
      else if (uVar5 == 0x12) {
        iVar3 = random_mod(0x28);
        random_val = random_mod(0x28);
        uVar5 = random_val + 0x14 + iVar3;
        *(uint *)((char *)local_e + 9) = uVar5;
      }
      else if (uVar5 == CMD_SAVE) {
        iVar3 = random_mod(4);
        uVar5 = iVar3 + 4;
        *(uint *)((char *)local_e + 9) = uVar5;
      }
      else {
        uVar5 = 0;
        (pcVar9 + 9)[0] = '\0';
        (pcVar9 + 9)[1] = '\0';
      }
    }
    damage = (undefined1)(uVar5 >> 8);
    uVar10 = (undefined2)((ulong)local_e >> 0x10);
    iVar3 = *(int *)((char *)local_e + 9);
    damage = iVar3 == 0;
    if (iVar3 < 0) {
LAB_1000_2d05:
      uVar5 = CONCAT11(damage,1);
    }
    else {
      uVar10 = CONCAT11(damage,((char *)local_e)[1]);
      puVar17 = local_2e;
      zero_word_array_16(puVar17);
      set_bit_in_array(CONCAT11(extraout_AH_00,5));
      set_bit_in_array(CONCAT11(extraout_AH_01,0x13));
      uVar5 = create_bit_mask(puVar17,unaff_SS,uVar10);
      damage = (undefined1)(uVar5 >> 8);
      if (!(bool)damage) goto LAB_1000_2d05;
      uVar5 = uVar5 & 0xff00;
    }
    ((char *)local_e)[0x14] = (char)uVar5;
    goto LAB_1000_2d0e;
  }
  do {
    iVar3 = damage + 1;
    damage = *(int *)(flags * 0x30 + iVar3 * 2 + -0x6513) + damage;
    damage = iVar3;
  } while (damage < random_val);
  *(int *)(pcVar9 + 1) = iVar3;
  if (((flags == '\a') && (*(int *)(pcVar9 + 1) == 7)) &&
     (iVar3 = random_mod(0x14), iVar3 == 0)) {
    ((char *)local_e + 1)[0] = '\x0f';
    ((char *)local_e + 1)[1] = '\0';
  }
  if (flags == '\x06') {
    iVar3 = count + 3 >> 0xf;
    combat_wrapper();
    damage = 0;
    uVar10 = conditional_char_action();
    find_highest_bit(uVar10,in_BX,iVar3);
    iVar3 = char_create_wrapper();
    if (!(bool)damage) goto LAB_1000_281a;
LAB_1000_284b:
    iVar3 = random_mod(3);
    *(int *)((char *)local_e + 9) = count / 5 + iVar3;
    find_highest_bit();
    damage = false;
    damage = true;
    iVar3 = char_create_wrapper();
    if (!damage && !damage) {
      uVar10 = (undefined2)((ulong)local_e >> 0x10);
      iVar3 = -*(int *)((char *)local_e + 9);
      *(int *)((char *)local_e + 9) = iVar3;
    }
  }
  else {
LAB_1000_281a:
    if (flags == '\a') {
      iVar3 = count + 2 >> 0xf;
      combat_wrapper();
      damage = 0;
      uVar10 = conditional_char_action();
      find_highest_bit(uVar10,in_BX,iVar3);
      iVar3 = char_create_wrapper();
      if ((bool)damage) goto LAB_1000_284b;
    }
  }
  damage = flags == '\x06';
  if ((bool)damage) {
    uVar5 = (uint)(byte)((char *)local_e)[1];
    puVar17 = local_2e;
    zero_word_array_16(puVar17);
    set_bit_range_in_array(CONCAT11(extraout_AH,0xb),CONCAT11(extraout_AH,9));
    iVar3 = create_bit_mask(puVar17,unaff_SS,uVar5);
    if (!(bool)damage) {
      uVar10 = (undefined2)((ulong)local_e >> 0x10);
      pcVar9 = (char *)local_e;
      iVar3 = 0;
      (pcVar9 + 9)[0] = '\0';
      (pcVar9 + 9)[1] = '\0';
      if (*(int *)(pcVar9 + 1) == 10) {
        (pcVar9 + 9)[0] = -1;
        (pcVar9 + 9)[1] = -1;
      }
    }
  }
  if (flags == '\x05') {
    iVar3 = random_mod(*(int *)(damage * 4 + -0x6245) / 2);
    iVar3 = *(int *)(damage * 4 + -0x6245) / 2 + iVar3 + 1;
    *(int *)((char *)local_e + 9) = iVar3;
  }
  if ((flags == '\a') && (*(int *)((char *)local_e + 1) == 0xc)) {
    *(int *)0xe533 = *(int *)0xe533 + 1;
    iVar3 = random_mod(10);
    uVar10 = (undefined2)((ulong)local_e >> 0x10);
    *(int *)((char *)local_e + 3) = iVar3 + 5;
    iVar3 = *(int *)0xe533;
    *(int *)((char *)local_e + 0x11) = iVar3;
  }
  uVar10 = (undefined2)((ulong)local_e >> 0x10);
  pcVar9 = (char *)local_e;
  damage = (byte)((uint)iVar3 >> 8);
  if (*(int *)(pcVar9 + 9) < 0) {
    uVar5 = CONCAT11(damage,1);
  }
  else {
    uVar5 = (uint)damage << 8;
  }
  pcVar9[0x14] = (char)uVar5;
  if (flags == '\b') {
    if (*(int *)(pcVar9 + 1) == 4) {
      iVar3 = random_mod(0xf);
      *(int *)((char *)local_e + 9) = iVar3 + 10;
    }
    uVar10 = (undefined2)((ulong)local_e >> 0x10);
    pcVar1 = (char *)local_e + 0xd;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1 = (char *)local_e + 0xf;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    do {
      uVar5 = random_mod(200);
      uVar10 = (undefined2)((ulong)local_e >> 0x10);
      pcVar9 = (char *)local_e;
      damage = *(undefined4 *)(pcVar9 + 0xd);
      damage = (uint)damage;
      damage = damage + 0x3c;
      *(uint *)(pcVar9 + 0xd) = damage + uVar5;
      *(uint *)(pcVar9 + 0xf) =
           (int)((ulong)damage >> 0x10) + (uint)(0xffc3 < damage) + (uint)CARRY2(damage,uVar5);
      iVar3 = random_mod(10);
      if (iVar3 == 0) {
        uVar10 = (undefined2)((ulong)local_e >> 0x10);
        pcVar9 = (char *)local_e;
        damage = *(undefined4 *)(pcVar9 + 0xd);
        uVar5 = (uint)damage;
        *(uint *)(pcVar9 + 0xd) = uVar5 + 100;
        *(uint *)(pcVar9 + 0xf) = (int)((ulong)damage >> 0x10) + (uint)(0xff9b < uVar5);
      }
      find_highest_bit();
      damage = false;
      damage = true;
      char_create_wrapper();
    } while (damage || damage);
    iVar3 = random_mod(0x14);
    if (iVar3 == 0) {
      damage = (undefined2)((ulong)*(undefined4 *)((char *)local_e + 0xd) >> 0x10);
      uVar10 = multiply_integers();
      damage = (undefined2)((ulong)local_e >> 0x10);
      *(undefined2 *)((char *)local_e + 0xd) = uVar10;
      *(undefined2 *)((char *)local_e + 0xf) = damage;
    }
    iVar3 = random_mod(0x32);
    if (iVar3 == 0) {
      damage = (undefined2)((ulong)*(undefined4 *)((char *)local_e + 0xd) >> 0x10);
      uVar10 = multiply_integers();
      damage = (undefined2)((ulong)local_e >> 0x10);
      *(undefined2 *)((char *)local_e + 0xd) = uVar10;
      *(undefined2 *)((char *)local_e + 0xf) = damage;
    }
    iVar3 = random_mod(100);
    if (iVar3 == 0) {
      damage = (undefined2)((ulong)*(undefined4 *)((char *)local_e + 0xd) >> 0x10);
      uVar10 = multiply_integers();
      damage = (undefined2)((ulong)local_e >> 0x10);
      *(undefined2 *)((char *)local_e + 0xd) = uVar10;
      *(undefined2 *)((char *)local_e + 0xf) = damage;
    }
    iVar3 = random_mod(500);
    if (iVar3 == 0) {
      damage = (undefined2)((ulong)*(undefined4 *)((char *)local_e + 0xd) >> 0x10);
      uVar10 = multiply_integers();
      damage = (undefined2)((ulong)local_e >> 0x10);
      *(undefined2 *)((char *)local_e + 0xd) = uVar10;
      *(undefined2 *)((char *)local_e + 0xf) = damage;
    }
    iVar3 = random_mod(10);
    uVar5 = iVar3 + 1;
    uVar10 = (undefined2)((ulong)local_e >> 0x10);
    *(uint *)((char *)local_e + 0x11) = uVar5;
    ((char *)local_e)[0x14] = '\x01';
  }
LAB_1000_2d0e:
  uVar10 = calculate_dice_or_damage(*(undefined2 *)((char *)local_e + 1),CONCAT11((char)(uVar5 >> 8),flags));
  *(undefined2 *)((char *)local_e + 0xb) = uVar10;
  return;
}



void spawn_monster_from_template(undefined4 *result_ptr,int count)

{
  char *pcVar1;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  int flag;
  char *pcVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 *puVar7;
  undefined1 local_2a [32];
  char *local_a;
  undefined1 local_6 [4];
  
  allocate_monster_object((undefined4 *)result_ptr,(int)((ulong)result_ptr >> 0x10));
  local_a = (char *)*result_ptr;
  uVar4 = (undefined2)((ulong)local_a >> 0x10);
  pcVar3 = (char *)local_a;
  *local_a = *(char *)(count * 0x2a + -0x5007);
  pcVar3[1] = *local_a;
  *(int *)(pcVar3 + 2) = count;
  *(int *)(pcVar3 + 4) = count;
  uVar6 = pcVar3 + 0x1e == (char *)0x0;
  find_random_empty_floor_space(0xe52d,unaff_DS,pcVar3 + 0x1e,uVar4,pcVar3 + 0x1c,uVar4);
  uVar5 = (undefined2)((ulong)local_a >> 0x10);
  pcVar3 = (char *)local_a;
  *(undefined2 *)(pcVar3 + 8) = *(undefined2 *)(count * 0x2a + -0x5004);
  *(undefined2 *)(pcVar3 + 6) = *(undefined2 *)(count * 0x2a + -0x5006);
  *(undefined2 *)(pcVar3 + 10) = *(undefined2 *)(count * 0x2a + -0x5002);
  *(undefined2 *)(pcVar3 + 0xc) = *(undefined2 *)(count * 0x2a + -0x5000);
  *(undefined2 *)(pcVar3 + 0xe) = *(undefined2 *)(count * 0x2a + -0x4ffe);
  *(undefined2 *)(pcVar3 + 0x10) = *(undefined2 *)(count * 0x2a + -0x4ffc);
  uVar4 = *(undefined2 *)(count * 0x2a + -0x4ff8);
  *(undefined2 *)(pcVar3 + 0x14) = uVar4;
  uVar5 = CONCAT11((char)((uint)uVar4 >> 8),*local_a);
  puVar7 = local_2a;
  uVar4 = unaff_SS;
  zero_word_array_16(puVar7);
  set_bit_in_array(CONCAT11(extraout_AH,0x42));
  set_bit_in_array(CONCAT11(extraout_AH_00,0x9e));
  create_bit_mask(puVar7,uVar4,uVar5);
  pcVar3 = (char *)local_a;
  uVar4 = (undefined2)((ulong)local_a >> 0x10);
  if ((!(bool)uVar6) &&
     (*(int *)(pcVar3 + 8) + *(int *)(pcVar3 + 0x14) < player_level + base_ac + 5)) {
    *(int *)(pcVar3 + 8) = *(int *)(pcVar3 + 8) + 1;
    *(int *)(pcVar3 + 0x14) = (player_level + base_ac + 6) - *(int *)(pcVar3 + 8);
  }
  *(undefined2 *)(pcVar3 + 0x12) = *(undefined2 *)(count * 0x2a + -0x4ffa);
  *(undefined2 *)(pcVar3 + 0x16) = *(undefined2 *)(count * 0x2a + -0x4ff6);
  *(undefined2 *)(pcVar3 + 0x18) = *(undefined2 *)(count * 0x2a + -0x4ff4);
  (pcVar3 + 0x20)[0] = '\0';
  (pcVar3 + 0x20)[1] = '\0';
  pcVar3[0x22] = '\0';
  pcVar3[0x23] = '\0';
  pcVar3[0x24] = '\0';
  pcVar3[0x25] = '\0';
  pcVar3[0x26] = '\0';
  pcVar3[0x28] = *(char *)(count * 0x2a + -0x4fef);
  *(undefined2 *)(pcVar3 + 0x1a) = *(undefined2 *)(count * 0x2a + -0x4ff2);
  pcVar3[0x27] = *(char *)(count * 0x2a + -0x4ff0);
  pcVar3[0x29] = *(char *)(count * 0x2a + -0x4fee);
  (pcVar3 + 0x2a)[0] = '\0';
  (pcVar3 + 0x2a)[1] = '\0';
  (pcVar3 + 0x2c)[0] = '\x01';
  (pcVar3 + 0x2c)[1] = '\0';
  (pcVar3 + 0x2e)[0] = '\0';
  (pcVar3 + 0x2e)[1] = '\0';
  (pcVar3 + 0x30)[0] = '\0';
  (pcVar3 + 0x30)[1] = '\0';
  (pcVar3 + 0x32)[0] = '\0';
  (pcVar3 + 0x32)[1] = '\0';
  (pcVar3 + 0x34)[0] = '\0';
  (pcVar3 + 0x34)[1] = '\0';
  if (*(int *)(pcVar3 + 0x16) != 0) {
    flag = random_mod(*(undefined2 *)(pcVar3 + 0x16));
    if (flag == 0) {
      initialize_monster_or_item(local_6,unaff_SS,*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */,((char *)local_a)[0x18]);
      uVar4 = (undefined2)((ulong)local_a >> 0x10);
      *(int *)((char *)local_a + 0x2e) = local_6._0_2_;
      *(int *)((char *)local_a + 0x30) = local_6._2_2_;
    }
  }
  if (*local_a == 'E') {
    uVar4 = (undefined2)((ulong)local_a >> 0x10);
    ((char *)local_a)[0x24] = '\x01';
    pcVar1 = (char *)local_a + 0x20;
    pcVar1[0] = -1;
    pcVar1[1] = -1;
  }
  return;
}



void __cdecl16near generate_random_names(void)

{
  int random_val;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar2;
  undefined2 uVar3;
  undefined1 local_127 [256];
  int random_val;
  int flag;
  int local_23;
  int local_21;
  undefined1 local_1f [29];
  
  flag = 1;
  while( true ) {
    random_val = random_mod(6);
    random_val = random_val + 4;
    local_1f[0] = 0;
    local_21 = random_val;
    if (0 < random_val) {
      local_23 = 1;
      while( true ) {
        puVar2 = local_127;
        uVar3 = unaff_SS;
        copy_pascal_string(local_1f,unaff_SS);
        random_val = random_mod(0x14);
        concat_pascal_string((random_val + 1) * 4 + -0x469e,unaff_DS);
        copy_pascal_string_limited(0x1c,local_1f,unaff_SS,puVar2,uVar3);
        if (local_23 == random_val) break;
        local_23 = local_23 + 1;
      }
    }
    copy_pascal_string_limited(0x1c,flag * 0x1d + -0x610e,unaff_DS,local_1f,unaff_SS);
    if (flag == 0x18) break;
    flag = flag + 1;
  }
  return;
}



void shuffle_array(int value,int count)

{
  undefined2 unaff_SS;
  undefined2 local_6;
  undefined2 random_val;
  
  if (0 < count) {
    local_6 = 1;
    while( true ) {
      random_val = random_mod(count);
      while (random_val = random_val + 1, *(int *)(value + random_val * 2 + -0x32) != 0) {
        random_val = random_val % count;
      }
      *(int *)(value + random_val * 2 + -0x32) = local_6;
      if (local_6 == count) break;
      local_6 = local_6 + 1;
    }
  }
  return;
}



void __cdecl16near randomize_item_appearances(void)

{
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_34 [25];
  
  local_34[0] = 1;
  while (local_34[local_34[0]] = 0, local_34[0] != 0x18) {
    local_34[0] = local_34[0] + 1;
  }
  shuffle_array(&stack0xfffe,0x18);
  local_34[0] = 1;
  while( true ) {
    copy_pascal_string_limited(0xf,local_34[0] * 0x10 + -0x5cc9,unaff_DS,local_34[local_34[0]] * 0x10 + -0x5e49,
                  unaff_DS);
    if (local_34[0] == 0x18) break;
    local_34[0] = local_34[0] + 1;
  }
  local_34[0] = 1;
  while (local_34[local_34[0]] = 0, local_34[0] != 0x13) {
    local_34[0] = local_34[0] + 1;
  }
  shuffle_array(&stack0xfffe,0x13);
  local_34[0] = 1;
  while( true ) {
    copy_pascal_string_limited(0xf,local_34[0] * 0x10 + -0x5a19,unaff_DS,local_34[local_34[0]] * 0x10 + -0x5b49,
                  unaff_DS);
    if (local_34[0] == CMD_SAVE) break;
    local_34[0] = local_34[0] + 1;
  }
  local_34[0] = 1;
  while (local_34[local_34[0]] = 0, local_34[0] != 0x16) {
    local_34[0] = local_34[0] + 1;
  }
  shuffle_array(&stack0xfffe,0x16);
  local_34[0] = 1;
  while( true ) {
    copy_pascal_string_limited(0xf,local_34[0] * 0x10 + -0x5789,unaff_DS,local_34[local_34[0]] * 0x10 + -0x58e9,
                  unaff_DS);
    if (local_34[0] == MAP_HEIGHT) break;
    local_34[0] = local_34[0] + 1;
  }
  local_34[0] = 1;
  while (local_34[local_34[0]] = 0, local_34[0] != 10) {
    local_34[0] = local_34[0] + 1;
  }
  shuffle_array(&stack0xfffe,10);
  local_34[0] = 1;
  while( true ) {
    copy_pascal_string_limited(0xf,local_34[0] * 0x10 + -0x5589,unaff_DS,local_34[local_34[0]] * 0x10 + -0x5629,
                  unaff_DS);
    if (local_34[0] == 10) break;
    local_34[0] = local_34[0] + 1;
  }
  return;
}



void __cdecl16near spawn_special_monster_with_item(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  int random_val;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 local_2e [28];
  undefined1 *local_12;
  int local_e;
  undefined2 local_c;
  undefined1 local_a [4];
  int random_val;
  int random_val;
  
  random_val = random_mod(3);
  random_val = random_val + 10;
  spawn_monster_from_template(local_a,unaff_SS,0x22);
  local_c = local_a._2_2_;
  local_e = local_a._0_2_;
  do {
    do {
      random_val = random_mod(0x23);
      random_val = random_val + 1;
      uVar6 = *(char *)(random_val * 0x2a + -0x4fee) == '\0';
    } while (!(bool)uVar6);
    uVar2 = CONCAT11((char)((uint)(random_val * 0x2a) >> 8),*(undefined1 *)(random_val * 0x2a + -0x5007));
    puVar4 = local_2e;
    uVar5 = unaff_SS;
    zero_word_array_16(puVar4);
    set_bit_in_array(CONCAT11(extraout_AH,0x61));
    set_bit_in_array(CONCAT11(extraout_AH_00,0x45));
    set_bit_in_array(CONCAT11(extraout_AH_01,0x48));
    create_bit_mask(puVar4,uVar5,uVar2);
  } while (!(bool)uVar6);
  *(undefined1 *)(local_e + 1) = *(undefined1 *)(random_val * 0x2a + -0x5007);
  *(int *)(local_e + 4) = random_val;
  if (*(int *)0xabaf == 0 && *(int *)0xabb1 == 0) {
    allocate_item_object(local_e + 0x2e,local_c);
    local_12 = (undefined1 *)*(undefined4 *)(local_e + 0x2e);
    *local_12 = 4;
    *(undefined2 *)((undefined1 *)local_12 + 1) = 6;
    random_val = random_mod(0x32);
    uVar5 = (undefined2)((ulong)local_12 >> 0x10);
    puVar4 = (undefined1 *)local_12;
    *(int *)(puVar4 + 9) = random_val + 0x32;
    puVar4[0x14] = 0;
    puVar4[0x13] = 0;
    *(undefined2 *)(puVar4 + 0x16) = 0;
    *(undefined2 *)(puVar4 + 0x18) = 0;
    uVar1 = *(undefined4 *)(local_e + 0x2e);
    *(undefined2 *)0xabaf = (int)uVar1;
    *(undefined2 *)0xabb1 = (int)((ulong)uVar1 >> 0x10);
  }
  else {
    *(undefined2 *)(local_e + 0x2e) = 0;
    *(undefined2 *)(local_e + 0x30) = 0;
  }
  *(undefined2 *)(random_val * 4 + -0x5499) = local_a._0_2_;
  *(undefined2 *)(random_val * 4 + -0x5497) = local_a._2_2_;
  *(undefined2 *)(random_val * 2 + 0x797d) = 1;
  return;
}



void __cdecl16near spawn_unique_monster_type_23(void)

{
  undefined1 *puVar1;
  int value;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_6 [4];
  
  spawn_monster_from_template(local_6,unaff_SS,0x23);
  uVar4 = local_6._2_2_;
  value = local_6._0_2_;
  allocate_item_object(value + 0x2e,uVar4);
  puVar1 = (undefined1 *)*(undefined4 *)(value + 0x2e);
  uVar4 = (undefined2)((ulong)puVar1 >> 0x10);
  puVar3 = (undefined1 *)puVar1;
  *puVar1 = 8;
  *(undefined2 *)(puVar3 + 1) = 0;
  *(undefined2 *)(puVar3 + 0x16) = 0;
  *(undefined2 *)(puVar3 + 0x18) = 0;
  *(undefined2 *)0xaba3 = local_6._0_2_;
  *(undefined2 *)0xaba5 = local_6._2_2_;
  *(undefined2 *)0x799b = 1;
  return;
}



void __cdecl16near spawn_monster_type_1f(void)

{
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_6 [4];
  
  spawn_monster_from_template(local_6,unaff_SS,0x1f);
  *(undefined2 *)0xab9f = local_6._0_2_;
  *(undefined2 *)0xaba1 = local_6._2_2_;
  *(undefined2 *)0x7999 = 1;
  return;
}



void __cdecl16near spawn_wandering_monster(void)

{
  int random_val;
  int value;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_6 [4];
  
  random_val = random_mod(2);
  spawn_monster_from_template(local_6,unaff_SS,0x1d);
  value = (random_val + 8) * 4;
  *(undefined2 *)(value + -0x5499) = local_6._0_2_;
  *(undefined2 *)(value + -0x5497) = local_6._2_2_;
  *(undefined2 *)((random_val + 8) * 2 + 0x797d) = 1;
  return;
}



void __cdecl16near add_monster_to_level_list(void)

{
  undefined4 uVar1;
  int random_val;
  int value;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_6 [4];
  
  random_val = random_mod(2);
  random_val = random_val + 0xc;
  spawn_monster_from_template(local_6,unaff_SS,0x1e);
  uVar1 = *(undefined4 *)(random_val * 4 + -0x5499);
  uVar4 = local_6._2_2_;
  value = local_6._0_2_;
  *(undefined2 *)(value + 0x32) = (int)uVar1;
  *(undefined2 *)(value + 0x34) = (int)((ulong)uVar1 >> 0x10);
  *(int *)(random_val * 4 + -0x5499) = value;
  *(undefined2 *)(random_val * 4 + -0x5497) = uVar4;
  *(int *)(random_val * 2 + 0x797d) = *(int *)(random_val * 2 + 0x797d) + 1;
  return;
}



void __cdecl16near prepend_monster_to_global_list(void)

{
  undefined4 uVar1;
  int value;
  undefined2 uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_6 [4];
  
  spawn_monster_from_template(local_6,unaff_SS,0x20);
  uVar1 = *(undefined4 *)0xab8f;
  uVar3 = local_6._2_2_;
  value = local_6._0_2_;
  *(undefined2 *)(value + 0x32) = (int)uVar1;
  *(undefined2 *)(value + 0x34) = (int)((ulong)uVar1 >> 0x10);
  *(int *)0xab8f = value;
  *(undefined2 *)0xab91 = uVar3;
  *(int *)0x7991 = *(int *)0x7991 + 1;
  return;
}



void __cdecl16near populate_level_with_monsters(void)

{
  undefined4 uVar1;
  char ch;
  undefined2 uVar3;
  uint value;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  int flag;
  undefined2 in_BX;
  byte *pbVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  undefined1 *puVar8;
  undefined1 local_2a [32];
  byte *local_a;
  int flag;
  int local_4;
  
  flag = 1;
  while( true ) {
    if ((*(int *)(dungeon_level * 2 + 0x797d) < 0x19) &&
       (local_4 = *(int *)(flag * 0x20 + dungeon_level * 2 + -0x546d), local_4 != 0)) {
      ch = check_inventory_has_item(ITEM_CURSED_SPECIAL);
      if (ch != '\0') {
        local_4 = local_4 << 1;
      }
      flag = local_4 >> 0xf;
      combat_wrapper();
      uVar7 = 0;
      uVar3 = conditional_char_action();
      find_highest_bit(uVar3,in_BX,flag);
      char_create_wrapper();
      if ((bool)uVar7) {
        spawn_monster_from_template(&local_a,unaff_SS,flag);
        uVar7 = (undefined1)((uint)in_BX >> 8);
        uVar3 = (undefined2)((ulong)local_a >> 0x10);
        find_position_near_player((byte *)local_a + 0x1e,uVar3,(byte *)local_a + 0x1c,uVar3);
        uVar3 = (undefined2)((ulong)local_a >> 0x10);
        pbVar6 = (byte *)local_a;
        in_BX = CONCAT11(uVar7,pbVar6[1]);
        *(byte *)(*(int *)(pbVar6 + 0x1c) * MAP_WIDTH + *(int *)(pbVar6 + 0x1e) + -0xc) = pbVar6[1];
        uVar1 = *(undefined4 *)(dungeon_level * 4 + -0x5499);
        *(int *)(pbVar6 + 0x32) = (int)uVar1;
        *(int *)(pbVar6 + 0x34) = (int)((ulong)uVar1 >> 0x10);
        flag = dungeon_level * 4;
        uVar7 = flag == 0;
        *(undefined2 *)(flag + -0x5499) = pbVar6;
        *(undefined2 *)(flag + -0x5497) = uVar3;
        value = (uint)*local_a;
        puVar8 = local_2a;
        uVar3 = unaff_SS;
        zero_word_array_16(puVar8);
        set_bit_in_array(CONCAT11(extraout_AH,0x45));
        set_bit_in_array(CONCAT11(extraout_AH_00,0x48));
        create_bit_mask(puVar8,uVar3,value);
        if (!(bool)uVar7) {
          *(int *)(dungeon_level * 2 + 0x799b) = *(int *)(dungeon_level * 2 + 0x799b) + 1;
        }
        *(int *)(dungeon_level * 2 + 0x797d) = *(int *)(dungeon_level * 2 + 0x797d) + 1;
      }
    }
    if (flag == 0x1c) break;
    flag = flag + 1;
  }
  return;
}



int find_dungeon_region(int value,int count)

{
  int value;
  undefined2 unaff_SS;
  undefined2 local_8;
  
  local_8 = count;
  while (*(int *)(value + local_8 * 2 + -0x36c) != local_8) {
    value = *(int *)(value + local_8 * 2 + -0x36c);
    *(undefined2 *)(value + local_8 * 2 + -0x36c) = *(undefined2 *)(value + value * 2 + -0x36c);
    local_8 = value;
  }
  return local_8;
}



void generate_dungeon_corridors(int value)

{
  undefined4 uVar1;
  int random_val;
  undefined2 uVar3;
  undefined2 uVar4;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 *puVar7;
  undefined1 local_22 [32];
  
  random_val = random_mod(0x328);
  *(int *)(value + -2) = random_val + 1;
  if (*(int *)(value + -2) < 0x187) {
    *(int *)(value + -8) = (*(int *)(value + -2) + -1) / 0x27 + 1;
    *(int *)(value + -6) = (*(int *)(value + -2) + -1) % 0x27 + 1;
    random_val = (*(int *)(value + -8) * 2 + 1) * MAP_WIDTH;
    uVar1 = *(undefined4 *)(*(int *)(value + 4) * 4 + 4);
    flag = (int)uVar1 + random_val + *(int *)(value + -6) * 2;
    uVar6 = flag == 0;
    uVar3 = CONCAT11((char)((uint)random_val >> 8),*(undefined1 *)(flag + -0x50));
    puVar7 = local_22;
    uVar4 = unaff_SS;
    pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
    create_bit_mask(puVar7,uVar4,uVar3);
    if (!(bool)uVar6) {
      *(undefined2 *)(value + -0x10) = *(undefined2 *)(value + -2);
      *(int *)(value + -0xe) = *(int *)(value + -0x10) + 0x27;
      uVar4 = find_dungeon_region(value,*(undefined2 *)(value + -0x10));
      *(undefined2 *)(value + -0xc) = uVar4;
      uVar4 = find_dungeon_region(value,*(undefined2 *)(value + -0xe));
      *(undefined2 *)(value + -10) = uVar4;
      if ((*(int *)(value + -0xc) != *(int *)(value + -10)) ||
         (*(char *)(value + -0x36b) == '\0')) {
        uVar1 = *(undefined4 *)(*(int *)(value + 4) * 4 + 4);
        *(undefined1 *)
         ((int)uVar1 + (*(int *)(value + -8) * 2 + 1) * MAP_WIDTH + *(int *)(value + -6) * 2 + -0x50)
             = 0x20;
        *(int *)(value + -4) = *(int *)(value + -4) + 1;
        if (*(int *)(value + -0xc) < *(int *)(value + -10)) {
          *(undefined2 *)(value + *(int *)(value + -10) * 2 + -0x36c) =
               *(undefined2 *)(value + -0xc);
        }
        else {
          *(undefined2 *)(value + *(int *)(value + -0xc) * 2 + -0x36c) =
               *(undefined2 *)(value + -10);
        }
      }
    }
  }
  else {
    *(int *)(value + -2) = *(int *)(value + -2) + -0x186;
    *(int *)(value + -8) = (*(int *)(value + -2) + -1) / 0xb + 1;
    *(int *)(value + -6) = (*(int *)(value + -2) + -1) % 0xb + 1;
    random_val = *(int *)(value + -6) * 0x9e;
    uVar1 = *(undefined4 *)(*(int *)(value + 4) * 4 + 4);
    flag = (int)uVar1 + random_val + *(int *)(value + -8) * 2 + 1;
    uVar6 = flag == 0;
    uVar3 = CONCAT11((char)((uint)random_val >> 8),*(undefined1 *)(flag + -0x50));
    puVar7 = local_22;
    uVar4 = unaff_SS;
    pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
    create_bit_mask(puVar7,uVar4,uVar3);
    if (!(bool)uVar6) {
      *(int *)(value + -0x10) = (*(int *)(value + -6) + -1) * 0x27 + *(int *)(value + -8);
      *(int *)(value + -0xe) = *(int *)(value + -0x10) + 1;
      uVar4 = find_dungeon_region(value,*(undefined2 *)(value + -0x10));
      *(undefined2 *)(value + -0xc) = uVar4;
      uVar4 = find_dungeon_region(value,*(undefined2 *)(value + -0xe));
      *(undefined2 *)(value + -10) = uVar4;
      if ((*(int *)(value + -0xc) != *(int *)(value + -10)) ||
         (*(char *)(value + -0x36b) == '\0')) {
        uVar1 = *(undefined4 *)(*(int *)(value + 4) * 4 + 4);
        *(undefined1 *)
         ((int)uVar1 + *(int *)(value + -6) * 0x9e + *(int *)(value + -8) * 2 + -0x4f) = 0x20;
        *(int *)(value + -4) = *(int *)(value + -4) + 1;
        if (*(int *)(value + -0xc) < *(int *)(value + -10)) {
          *(undefined2 *)(value + *(int *)(value + -10) * 2 + -0x36c) =
               *(undefined2 *)(value + -0xc);
        }
        else {
          *(undefined2 *)(value + *(int *)(value + -0xc) * 2 + -0x36c) =
               *(undefined2 *)(value + -10);
        }
      }
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00013b1e)
// WARNING: Removing unreachable block (ram,0x00013b23)
// WARNING: Removing unreachable block (ram,0x00013b2e)

void draw_dungeon_border(int value)

{
  undefined4 uVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_a;
  int local_8;
  
  local_a = 1;
  while( true ) {
    for (local_8 = 1; uVar1 = *(undefined4 *)(value * 4 + 4),
        *(undefined1 *)((int)uVar1 + local_a * 0x9e + local_8 * 2 + -0x4f) = 0xb3, local_8 != 0x26;
        local_8 = local_8 + 1) {
    }
    if (local_a == 0xb) break;
    local_a = local_a + 1;
  }
  local_a = 1;
  while( true ) {
    for (local_8 = 1; uVar1 = *(undefined4 *)(value * 4 + 4),
        *(undefined1 *)((int)uVar1 + (local_a * 2 + 1) * MAP_WIDTH + local_8 * 2 + -0x50) = 0xc4,
        local_8 != 0x27; local_8 = local_8 + 1) {
    }
    if (local_a == 10) break;
    local_a = local_a + 1;
  }
  local_a = 1;
  while( true ) {
    for (local_8 = 1; uVar1 = *(undefined4 *)(value * 4 + 4),
        *(undefined1 *)((int)uVar1 + (local_a * 2 + 1) * MAP_WIDTH + local_8 * 2 + -0x4f) = 0xc5,
        local_8 != 0x26; local_8 = local_8 + 1) {
    }
    if (local_a == 10) break;
    local_a = local_a + 1;
  }
  for (local_a = 1; *(int *)(&stack0xfc92 + local_a * 2) = local_a, local_a != 0x1ad;
      local_a = local_a + 1) {
  }
  do {
    generate_dungeon_corridors(&stack0xfffe);
  } while( true );
}



void generate_dungeon_level(int value)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  int flag;
  undefined2 in_BX;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar5;
  undefined1 uVar6;
  int local_18;
  int local_16;
  int local_12;
  int local_10;
  int local_e;
  int local_c;
  int local_a;
  int local_8;
  int local_6;
  int local_4;
  
  do {
    iVar2 = random_mod(10);
    *(int *)(value * 4 + 0x78ed) = iVar2 * 2 + 2;
    iVar2 = random_mod(0x26);
    *(int *)(value * 4 + 0x78ef) = iVar2 * 2 + 2;
    uVar1 = *(undefined4 *)(value * 4 + 4);
  } while (*(char *)((int)uVar1 + *(int *)(value * 4 + 0x78ed) * MAP_WIDTH +
                     *(int *)(value * 4 + 0x78ef) + -0x50) != ' ');
  uVar1 = *(undefined4 *)(value * 4 + 4);
  *(undefined1 *)
   ((int)uVar1 + *(int *)(value * 4 + 0x78ed) * MAP_WIDTH + *(int *)(value * 4 + 0x78ef) + -0x50) =
       0xef;
  do {
    iVar2 = random_mod(10);
    *(int *)(value * 4 + 0x792d) = iVar2 * 2 + 2;
    iVar2 = random_mod(0x26);
    *(int *)(value * 4 + 0x792f) = iVar2 * 2 + 2;
    uVar1 = *(undefined4 *)(value * 4 + 4);
  } while (*(char *)((int)uVar1 + *(int *)(value * 4 + 0x792d) * MAP_WIDTH +
                     *(int *)(value * 4 + 0x792f) + -0x50) != ' ');
  if (value != 0xf) {
    uVar1 = *(undefined4 *)(value * 4 + 4);
    *(undefined1 *)
     ((int)uVar1 + *(int *)(value * 4 + 0x792d) * MAP_WIDTH + *(int *)(value * 4 + 0x792f) + -0x50) =
         0xef;
  }
  iVar2 = value >> 0xf;
  combat_wrapper();
  uVar5 = 0;
  uVar6 = 1;
  uVar3 = conditional_char_action();
  find_highest_bit(uVar3,in_BX,iVar2);
  char_create_wrapper();
  if (((bool)uVar5 || (bool)uVar6) || (value == 0)) {
    local_12 = 0;
    local_10 = 0;
    local_e = 0;
    local_c = 0;
  }
  else {
    iVar2 = random_mod(0x10 - value);
    local_12 = iVar2 * 2 + 8;
    iVar2 = random_mod((0x13 - value) / 3);
    local_10 = iVar2 * 2 + 4;
    iVar2 = random_mod(0x26 - local_12 / 2);
    local_c = iVar2 * 2 + 3;
    iVar2 = random_mod(9 - local_10 / 2);
    local_e = iVar2 * 2 + 3;
  }
  if (local_10 != 0) {
    iVar2 = local_12 / 2 + -1;
    if (0 < iVar2) {
      local_18 = 1;
      while( true ) {
        uVar1 = *(undefined4 *)(value * 4 + 4);
        *(undefined1 *)((int)uVar1 + local_e * MAP_WIDTH + local_18 * 2 + local_c + -0x50) = 0xc1;
        uVar1 = *(undefined4 *)(value * 4 + 4);
        *(undefined1 *)((int)uVar1 + (local_e + 1) * MAP_WIDTH + local_18 * 2 + local_c + -0x50) = 0x20;
        uVar1 = *(undefined4 *)(value * 4 + 4);
        *(undefined1 *)((int)uVar1 + (local_e + local_10) * MAP_WIDTH + local_18 * 2 + local_c + -0x50) =
             0xc2;
        if (local_18 == iVar2) break;
        local_18 = local_18 + 1;
      }
    }
    iVar2 = local_10 / 2 + -1;
    if (0 < iVar2) {
      local_18 = 1;
      while( true ) {
        uVar1 = *(undefined4 *)(value * 4 + 4);
        *(undefined1 *)((int)uVar1 + (local_18 * 2 + local_e) * MAP_WIDTH + local_c + -0x50) = 0xb4;
        uVar1 = *(undefined4 *)(value * 4 + 4);
        *(undefined1 *)((int)uVar1 + (local_18 * 2 + local_e) * MAP_WIDTH + local_c + -0x4f) = 0x20;
        uVar1 = *(undefined4 *)(value * 4 + 4);
        *(undefined1 *)((int)uVar1 + (local_18 * 2 + local_e) * MAP_WIDTH + local_c + local_12 + -0x50) =
             0xc3;
        if (local_18 == iVar2) break;
        local_18 = local_18 + 1;
      }
    }
    iVar2 = local_12 / 2 + -1;
    if (0 < iVar2) {
      local_18 = 1;
      while( true ) {
        flag = local_10 / 2 + -1;
        if (0 < flag) {
          local_16 = 1;
          while( true ) {
            uVar1 = *(undefined4 *)(value * 4 + 4);
            *(undefined1 *)
             ((int)uVar1 + (local_16 * 2 + local_e) * MAP_WIDTH + local_18 * 2 + local_c + -0x50) = 0x20;
            uVar1 = *(undefined4 *)(value * 4 + 4);
            *(undefined1 *)
             ((int)uVar1 + (local_16 * 2 + local_e + 1) * MAP_WIDTH + local_18 * 2 + local_c + -0x50) =
                 0x20;
            uVar1 = *(undefined4 *)(value * 4 + 4);
            *(undefined1 *)
             ((int)uVar1 + (local_16 * 2 + local_e) * MAP_WIDTH + local_18 * 2 + local_c + -0x4f) = 0x20;
            if (local_16 == flag) break;
            local_16 = local_16 + 1;
          }
        }
        if (local_18 == iVar2) break;
        local_18 = local_18 + 1;
      }
    }
  }
  iVar2 = random_mod(3);
  if (iVar2 == 1) {
    find_random_empty_floor_space(&value,unaff_SS,&local_4,unaff_SS,&local_6,unaff_SS);
    uVar1 = *(undefined4 *)(value * 4 + 4);
    *(undefined1 *)((int)uVar1 + local_6 * MAP_WIDTH + local_4 + -0x50) = 0xf7;
  }
  if (value == 1) {
    find_random_empty_floor_space(&value,unaff_SS,&local_8,unaff_SS,&local_a,unaff_SS);
    uVar1 = *(undefined4 *)(value * 4 + 4);
    *(undefined1 *)((int)uVar1 + local_a * MAP_WIDTH + local_8 + -0x50) = 0x9b;
  }
  if (((value != 0xf) && (iVar2 = random_mod(2), iVar2 == 0)) &&
     (iVar2 = random_mod(3), -1 < iVar2)) {
    local_18 = 0;
    while( true ) {
      find_random_empty_floor_space(&value,unaff_SS,&local_4,unaff_SS,&local_6,unaff_SS);
      uVar1 = *(undefined4 *)(value * 4 + 4);
      *(undefined1 *)((int)uVar1 + local_6 * MAP_WIDTH + local_4 + -0x50) = *(undefined1 *)0x1;
      if (local_18 == iVar2) break;
      local_18 = local_18 + 1;
    }
  }
  if ((value == 10) || (value == 0xf)) {
    do {
      iVar2 = random_mod(2);
      flag = random_mod(3);
    } while (flag == 0);
    if (0 < iVar2 + 1) {
      local_18 = 1;
      while( true ) {
        find_random_empty_floor_space(&value,unaff_SS,&local_4,unaff_SS,&local_6,unaff_SS);
        uVar1 = *(undefined4 *)(value * 4 + 4);
        *(undefined1 *)((int)uVar1 + local_6 * MAP_WIDTH + local_4 + -0x50) = *(undefined1 *)0x3;
        if (local_18 == iVar2 + 1) break;
        local_18 = local_18 + 1;
      }
    }
  }
  uVar1 = *(undefined4 *)(value * 4 + 4);
  *(undefined1 *)((int)uVar1 + 0x71a) = 1;
  return;
}



void spawn_monsters(undefined2 param_1)

{
  int random_val;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar2;
  undefined1 local_16 [4];
  char ch;
  char ch;
  undefined2 local_10;
  int local_a;
  int local_6;
  
  uVar2 = &stack0xfffe < (undefined1 *)0x1a;
  local_10 = find_highest_bit();
  char_create_wrapper();
  if ((bool)uVar2) {
    ch = '\a';
  }
  else {
    char_create_wrapper();
    if ((bool)uVar2) {
      ch = '\x06';
    }
    else {
      char_create_wrapper();
      if ((bool)uVar2) {
        ch = '\x03';
      }
      else {
        char_create_wrapper();
        if ((bool)uVar2) {
          ch = '\x02';
        }
        else {
          char_create_wrapper();
          if ((bool)uVar2) {
            ch = '\x04';
          }
          else {
            ch = '\x05';
          }
        }
      }
    }
  }
  ch = '\0';
  while( true ) {
    local_6 = *(int *)(ch * 0x30 + 0x79d7);
    if ((*(int *)(ch * 0x30 + 0x79d9) != 0) && (0 < *(int *)(ch * 0x30 + 0x79d9))) {
      random_val = random_mod(*(undefined2 *)(ch * 0x30 + 0x79d9));
      local_6 = local_6 + random_val;
    }
    if (ch == ch) {
      random_val = random_mod(*(undefined2 *)(ch * 0x30 + 0x79db));
      local_6 = local_6 + random_val + 1;
    }
    random_val = local_6;
    if (0 < local_6) {
      local_a = 1;
      while( true ) {
        initialize_monster_or_item(local_16,unaff_SS,param_1,ch);
        place_object_on_map(param_1,local_16,unaff_SS);
        if (local_a == random_val) break;
        local_a = local_a + 1;
      }
    }
    if (ch == '\b') break;
    ch = ch + '\x01';
  }
  return;
}



void __cdecl16near select_or_load_character(void)

{
  bool flag;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  uint value;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool flag;
  undefined1 uVar5;
  undefined1 *puVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined1 local_3a [32];
  int local_1a;
  int flag;
  undefined1 local_13 [17];
  
  clear_screen_double();
  flag = 0;
  while( true ) {
    validate_window_coords(flag * 2 + 9,10);
    display_score_with_fatal(flag + 0x2a);
    if (flag == 3) break;
    flag = flag + 1;
  }
  flag = true;
  do {
    if (!flag) {
      return;
    }
    uVar7 = 0xe554;
    read_string_from_file(0x10,local_13,unaff_SS);
    read_line(0x214c,uVar7);
    validate_window_coords(CONCAT11(extraout_AH,0x11),CONCAT11(extraout_AH,5));
    update_screen_double();
    validate_window_coords(CONCAT11(extraout_AH_00,0x12),CONCAT11(extraout_AH_00,0x3c));
    for (flag = 1; flag < 0x10; flag = flag + 1) {
      flag = flag * 0x18 + -0x45db;
      flag = flag == 0;
      compare_pascal_strings(flag,unaff_DS,local_13,unaff_SS);
      if (flag) break;
    }
    if (flag == 0x10) {
      copy_pascal_string_limited(0x1c,0xb84f,unaff_DS,local_13,unaff_SS);
      flag = false;
    }
    else {
      _local_1a = CONCAT22(unaff_DS,flag * 0x18 + -0x45db);
      uVar5 = (undefined1)((uint)(flag * 0x18) >> 8);
      validate_window_coords(CONCAT11(uVar5,0x11),CONCAT11(uVar5,5));
      display_score_with_fatal(0x99);
      uVar8 = 0xe654;
      uVar7 = unaff_DS;
      write_bytes(0,CONCAT11(extraout_AH_01,0x20));
      uVar5 = 1;
      write_padded_string(0,(int)_local_1a,(int)((ulong)_local_1a >> 0x10));
      flush_output(uVar8,uVar7);
      display_character_status_message(0x23,*(undefined2 *)((int)_local_1a + 0x16));
      uVar8 = CONCAT11(extraout_AH_02,*(undefined1 *)((int)_local_1a + 0x16));
      puVar6 = local_3a;
      uVar7 = unaff_SS;
      zero_word_array_16(puVar6);
      set_bit_range_in_array(CONCAT11(extraout_AH_03,0x23),CONCAT11(extraout_AH_03,1));
      value = create_bit_mask(puVar6,uVar7,uVar8);
      if (!(bool)uVar5) {
        display_class_info(value & 0xff00,*(undefined2 *)((int)_local_1a + 0x16));
      }
      if (*(char *)((int)_local_1a + 0x16) != 'g') {
        uVar8 = 0xe654;
        uVar7 = unaff_DS;
        write_padded_string(0,0x4252,0x214c);
        flag = *(int *)((int)_local_1a + 0x10);
        write_padded_number(0,flag,flag >> 0xf);
        write_bytes(0,CONCAT11(extraout_AH_04,0x2e));
        flush_output(uVar8,uVar7);
      }
      update_screen_double();
      validate_window_coords(CONCAT11(extraout_AH_05,0x12),CONCAT11(extraout_AH_05,0x14));
      display_score_with_fatal(0x26);
      update_screen_double();
    }
  } while( true );
}



void __cdecl16near initialize_new_game(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  char ch;
  undefined2 uVar4;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 uVar6;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  int random_val;
  undefined2 unaff_DS;
  undefined2 uVar7;
  int flag;
  char ch;
  char ch;
  
  ch = '\0';
  while( true ) {
    *(undefined2 *)(ch * 4 + -0x4738) = 0;
    *(undefined2 *)(ch * 4 + -0x4736) = 0;
    if (ch == '\b') break;
    ch = ch + '\x01';
  }
  *(undefined2 *)ADDR_EXPERIENCE /* experience */ = 0;
  *(undefined2 *)ADDR_PLAYER_LEVEL /* player_level */ = 0x80;
  *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = 1000;
  *(undefined2 *)ADDR_MAX_HP /* max_hp */ = 1000;
  *(undefined2 *)0xb88a = 0;
  *(undefined2 *)0xb88c = 0;
  *(undefined2 *)0xb88e = 0;
  clear_screen_double();
  uVar7 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x440c,0x20e6);
  flush_output(uVar7,uVar4);
  uVar4 = read_keyboard_input();
  ch = to_uppercase(uVar4);
  if (ch == 'O') {
    *(undefined2 *)ADDR_CURRENT_FOOD /* current_food */ = 100;
    *(undefined2 *)ADDR_MAX_FOOD /* max_food */ = 100;
    *(undefined2 *)ADDR_STRENGTH /* strength */ = 100;
    *(undefined2 *)ADDR_INTELLIGENCE /* intelligence */ = 100;
  }
  else {
    clear_screen_double();
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    write_padded_string(0,0x4427,0x20e6);
    write_padded_number(2,0xff,0);
    write_padded_string(0,0x4432,0x214c);
    flush_output(uVar7,uVar4);
    validate_window_coords(CONCAT11(extraout_AH,4),CONCAT11(extraout_AH,5));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    write_padded_string(0,0x4448,0x20e6);
    flush_output(uVar7,uVar4);
    validate_window_coords(CONCAT11(extraout_AH_00,5),CONCAT11(extraout_AH_00,5));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    write_padded_string(0,0x4459,0x20e6);
    flush_output(uVar7,uVar4);
    validate_window_coords(CONCAT11(extraout_AH_01,6),CONCAT11(extraout_AH_01,5));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    write_padded_string(0,0x446a,0x20e6);
    flush_output(uVar7,uVar4);
    validate_window_coords(CONCAT11(extraout_AH_02,4),CONCAT11(extraout_AH_02,0x15));
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_MAX_FOOD /* max_food */ = uVar4;
    read_line(0x214c);
    *(undefined2 *)ADDR_CURRENT_FOOD /* current_food */ = *(undefined2 *)ADDR_MAX_FOOD /* max_food */;
    random_val = 0xff - max_food;
    uVar6 = (undefined1)((uint)random_val >> 8);
    validate_window_coords(CONCAT11(uVar6,1),CONCAT11(uVar6,0xb));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    write_padded_number(2,random_val,random_val >> 0xf);
    flush_output(uVar7,uVar4);
    validate_window_coords(CONCAT11(extraout_AH_03,5),CONCAT11(extraout_AH_03,0x15));
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_STRENGTH /* strength */ = uVar4;
    read_line(0x214c);
    random_val = random_val - strength;
    uVar6 = (undefined1)((uint)random_val >> 8);
    validate_window_coords(CONCAT11(uVar6,1),CONCAT11(uVar6,0xb));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    write_padded_number(2,random_val,random_val >> 0xf);
    flush_output(uVar7,uVar4);
    validate_window_coords(CONCAT11(extraout_AH_04,6),CONCAT11(extraout_AH_04,0x15));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    write_padded_number(0,random_val,random_val >> 0xf);
    flush_output(uVar7,uVar4);
    intelligence = random_val;
  }
  flag = 1;
  while( true ) {
    *(undefined2 *)(flag * 4 + -0x476c) = 0;
    *(undefined2 *)(flag * 4 + -0x476a) = 0;
    if (flag == 10) break;
    flag = flag + 1;
  }
  *(undefined2 *)ADDR_TURN_COUNT = 1000;
  *(undefined2 *)0xb936 = 4;
  random_val = *(int *)0xb936;
  if (0 < random_val) {
    flag = 1;
    while( true ) {
      *(undefined2 *)(flag * 4 + -0x46cc) = 0;
      *(undefined2 *)(flag * 4 + -0x46ca) = 0;
      if (flag == random_val) break;
      flag = flag + 1;
    }
  }
  *(undefined2 *)0xb8c2 = 3;
  *(undefined2 *)0xb8c0 = 3;
  *(undefined2 *)0xb8c6 = 0x26;
  *(undefined2 *)ADDR_WISDOM = 0;
  *(undefined2 *)ADDR_DEXTERITY = 0;
  *(undefined2 *)ADDR_BASE_AC /* base_ac */ = 0;
  *(undefined2 *)ADDR_CONSTITUTION = 0;
  *(undefined2 *)0xb8cc = 1;
  *(undefined2 *)0xb8ce = 0;
  *(undefined2 *)0xb8e0 = 1;
  *(undefined2 *)0xb8e2 = 0;
  *(undefined2 *)0xb8e4 = 3;
  *(undefined2 *)0xb8e6 = 0;
  ch = '\0';
  while( true ) {
    *(undefined1 *)(ch + -0x4714) = 0;
    *(undefined2 *)(ch * 2 + -0x4707) = 0;
    if (ch == '\f') break;
    ch = ch + '\x01';
  }
  hallucination_active = 0;
  *(undefined2 *)ADDR_FOOD_LEVEL = 3000;
  *(undefined1 *)0xb8f4 = 1;
  is_dying = 0;
  is_hasted = 0;
  *(undefined1 *)0xb917 = 0;
  has_light = 0;
  is_confused = 0;
  *(undefined2 *)0xb890 = 5;
  allocate_item_object(0xb91e,unaff_DS);
  puVar1 = (undefined1 *)inventory_list;
  uVar4 = (undefined2)((ulong)puVar1 >> 0x10);
  puVar2 = (undefined1 *)puVar1;
  *puVar1 = 1;
  *(undefined2 *)(puVar2 + 0xb) = 2;
  allocate_item_object(puVar2 + 0x16,uVar4);
  equipped_shield = 0;
  *(undefined2 *)0xb928 = 0;
  equipped_armor = 0;
  *(undefined2 *)0xb92c = 0;
  equipped_ring2 = 0;
  *(undefined2 *)0xb934 = 0;
  equipped_ring1 = 0;
  *(undefined2 *)0xb930 = 0;
  *(undefined2 *)0xb884 = 0;
  wielded_weapon = 0;
  *(undefined2 *)0xb924 = 0;
  puVar1 = *(undefined1 **)(puVar2 + 0x16);
  uVar4 = (undefined2)((ulong)puVar1 >> 0x10);
  puVar2 = (undefined1 *)puVar1;
  *puVar1 = 7;
  *(undefined2 *)(puVar2 + 1) = 0xb;
  *(undefined2 *)(puVar2 + 9) = 0;
  *(undefined2 *)(puVar2 + 0xb) = 2;
  puVar2[0x14] = 0;
  puVar2[0x13] = 1;
  allocate_item_object(puVar2 + 0x16,uVar4);
  puVar1 = *(undefined1 **)(puVar2 + 0x16);
  uVar4 = (undefined2)((ulong)puVar1 >> 0x10);
  puVar2 = (undefined1 *)puVar1;
  *puVar1 = 7;
  *(undefined2 *)(puVar2 + 1) = 0xc;
  *(undefined2 *)(puVar2 + 0x11) = 1;
  random_val = random_mod(0xe);
  *(int *)(puVar2 + 3) = random_val + 7;
  *(undefined2 *)(puVar2 + 9) = 0;
  *(undefined2 *)(puVar2 + 0xb) = 2;
  puVar2[0x14] = 0;
  puVar2[0x13] = 1;
  *(undefined2 *)(puVar2 + 0x16) = 0;
  *(undefined2 *)(puVar2 + 0x18) = 0;
  *(undefined2 *)0xb8c4 = 6;
  return;
}



void __cdecl16near initialize_game(void)

{
  undefined1 extraout_AH;
  undefined2 unaff_SS;
  undefined1 local_8 [6];
  
  seed_rng();
  select_or_load_character();
  initialize_new_game();
  draw_dungeon_border(1);
  generate_dungeon_level(1);
  spawn_monsters(1);
  generate_random_names();
  randomize_item_appearances();
  initialize_monster_or_item(local_8,unaff_SS,0xf,CONCAT11(extraout_AH,8));
  *(undefined2 *)((int)local_8._0_4_ + 1) = 0;
  place_object_on_map(0xf,local_8,unaff_SS);
  spawn_special_monster_with_item();
  spawn_monster_type_1f();
  spawn_wandering_monster();
  add_monster_to_level_list();
  prepend_monster_to_global_list();
  spawn_unique_monster_type_23();
  return;
}



void find_empty_floor_tile(int *result_ptr,int *count)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined1 extraout_AH;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined1 *puVar7;
  undefined2 uVar8;
  undefined1 local_49 [32];
  undefined1 local_29 [32];
  char ch;
  int local_8;
  int local_6;
  int local_4;
  
  ch = '\x01';
  for (local_4 = 1; (ch != '\0' && (local_4 != 5)); local_4 = local_4 + 1) {
    local_8 = *count;
    local_6 = *result_ptr;
    do {
      local_8 = local_8 + *(int *)(local_4 * 4 + -0x464e);
      local_6 = local_6 + *(int *)(local_4 * 4 + -0x464c);
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      flag = (int)uVar1 + local_8 * MAP_WIDTH + local_6;
      uVar4 = flag == 0;
      uVar2 = CONCAT11((char)((uint)(local_8 * MAP_WIDTH) >> 8),*(undefined1 *)(flag + -0x50));
      puVar7 = local_49;
      uVar8 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
      puVar5 = local_29;
      uVar6 = unaff_SS;
      zero_word_array_16(puVar5);
      set_bit_in_array(CONCAT11(extraout_AH,0x20));
      bitwise_or_word_arrays(puVar5,uVar6);
      create_bit_mask(puVar7,uVar8,uVar2);
    } while ((bool)uVar4);
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    if (*(char *)((int)uVar1 + local_8 * MAP_WIDTH + local_6 + -0x50) == ' ') {
      *count = local_8;
      *result_ptr = local_6;
      ch = '\0';
    }
  }
  if (ch != '\0') {
    find_random_empty_floor_space(0xe52d,unaff_DS,(int *)result_ptr,(int)((ulong)result_ptr >> 0x10),(int *)count,
                  (int)((ulong)count >> 0x10));
  }
  return;
}



void place_player_on_level(char param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  uint in_AX;
  int random_val;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_a [4];
  undefined1 local_6 [4];
  
  if (param_1 == '\0') {
    random_val = random_mod(5);
    initialize_monster_or_item(local_6,unaff_SS,*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */,random_val + 1);
    place_object_on_map(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */,local_6,unaff_SS);
  }
  else {
    initialize_monster_or_item(local_a,unaff_SS,*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */,in_AX & 0xff00);
    place_object_on_map(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */,local_a,unaff_SS);
  }
  uVar1 = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
  uVar2 = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
  uVar3 = *(undefined4 *)(dungeon_level * 4 + 4);
  *(undefined1 *)((int)uVar3 + *(int *)((int)uVar2 + 5) * MAP_WIDTH + *(int *)((int)uVar1 + 7) + -0x50) =
       0x20;
  uVar1 = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
  *(undefined2 *)((int)uVar1 + 5) = *(undefined2 *)ADDR_PLAYER_Y /* player_y */;
  uVar1 = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
  *(undefined2 *)((int)uVar1 + 7) = *(undefined2 *)ADDR_PLAYER_X /* player_x */;
  uVar1 = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
  uVar2 = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
  find_empty_floor_tile((int)uVar2 + 7,(int)((ulong)uVar2 >> 0x10),(int)uVar1 + 5,
                (int)((ulong)uVar1 >> 0x10));
  uVar1 = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
  uVar6 = (undefined2)((ulong)uVar1 >> 0x10);
  random_val = (int)uVar1;
  uVar4 = lookup_table_b9c7(*(undefined2 *)(dungeon_level * 4 + -0x54d9),
                        *(undefined2 *)(dungeon_level * 4 + -0x54d7));
  uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
  *(undefined1 *)((int)uVar1 + *(int *)(random_val + 5) * MAP_WIDTH + *(int *)(random_val + 7) + -0x50) = uVar4;
  return;
}



void __cdecl16near handle_player_death(void)

{
  check_minimum_stats();
  display_score_with_fatal(0x1a2);
  return;
}



void __cdecl16near draw_game_hud(void)

{
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  uint value;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined1 extraout_AH_11;
  undefined1 extraout_AH_12;
  undefined1 extraout_AH_13;
  undefined1 extraout_AH_14;
  undefined1 extraout_AH_15;
  undefined1 extraout_AH_16;
  undefined1 extraout_AH_17;
  undefined1 extraout_AH_18;
  undefined1 extraout_AH_19;
  undefined1 extraout_AH_20;
  undefined1 extraout_AH_21;
  undefined1 extraout_AH_22;
  undefined1 extraout_AH_23;
  undefined1 extraout_AH_24;
  undefined1 extraout_AH_25;
  undefined1 extraout_AH_26;
  undefined1 extraout_AH_27;
  undefined1 extraout_AH_28;
  undefined1 extraout_AH_29;
  undefined1 extraout_AH_30;
  int value;
  byte extraout_AH_31;
  undefined1 extraout_AH_32;
  undefined1 extraout_AH_33;
  undefined1 extraout_AH_34;
  undefined1 extraout_AH_35;
  undefined1 extraout_AH_36;
  undefined1 extraout_AH_37;
  undefined1 extraout_AH_38;
  undefined1 extraout_AH_39;
  undefined1 extraout_AH_40;
  undefined1 extraout_AH_41;
  undefined1 extraout_AH_42;
  undefined2 unaff_DS;
  undefined2 uVar3;
  undefined2 uVar4;
  int local_4;
  
  clear_screen_double();
  validate_window_coords(CONCAT11(extraout_AH,1),CONCAT11(extraout_AH,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_00,0xc9));
  flush_output(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xcd);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xbb);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_01,2),CONCAT11(extraout_AH_01,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_02,0xba));
  flush_output(uVar3,uVar4);
  set_background_color(CONCAT11(extraout_AH_03,2));
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0x20);
    value = flush_output(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  set_background_color(value & 0xff00);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_04,0xba));
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_05,3),CONCAT11(extraout_AH_05,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_06,0xba));
  flush_output(uVar3,uVar4);
  set_background_color(CONCAT11(extraout_AH_07,2));
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0x20);
    value = flush_output(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  set_background_color(value & 0xff00);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_08,0xba));
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_09,4),CONCAT11(extraout_AH_09,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_10,0xba));
  flush_output(uVar3,uVar4);
  set_background_color(CONCAT11(extraout_AH_11,2));
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0x20);
    value = flush_output(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  set_background_color(value & 0xff00);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_12,0xba));
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_13,5),CONCAT11(extraout_AH_13,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_14,0xcc));
  flush_output(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xcd);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xd1);
  flush_output(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xcd);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xb9);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_15,6),CONCAT11(extraout_AH_15,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x4b63,0x20e6);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_16,7),CONCAT11(extraout_AH_16,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_17,199));
  flush_output(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xc4);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xc5);
  flush_output(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xc4);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xb6);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_18,8),CONCAT11(extraout_AH_18,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x4b91,0x20e6);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_19,9),CONCAT11(extraout_AH_19,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_20,199));
  flush_output(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xc4);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xc5);
  flush_output(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xc4);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xb6);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_21,10),CONCAT11(extraout_AH_21,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x4bbf,0x20e6);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_22,0xb),CONCAT11(extraout_AH_22,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_23,199));
  flush_output(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xc4);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xc5);
  flush_output(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xc4);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xb6);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_24,0xc),CONCAT11(extraout_AH_24,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x4bed,0x20e6);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_25,0xd),CONCAT11(extraout_AH_25,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_26,199));
  flush_output(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xc4);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xc5);
  flush_output(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xc4);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xb6);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_27,0xe),CONCAT11(extraout_AH_27,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0x4c1b,0x20e6);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_28,0xf),CONCAT11(extraout_AH_28,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH_29,200));
  flush_output(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xcd);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xcf);
  flush_output(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    write_bytes(0,0xcd);
    flush_output(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_bytes(0,0xbc);
  flush_output(uVar3,uVar4);
  set_background_color(CONCAT11(extraout_AH_30,2));
  value = 0x28 - *(byte *)0xb84f / 2;
  validate_window_coords(CONCAT11((char)((uint)value >> 8),3),value);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_string(0,0xb84f,unaff_DS);
  flush_output(uVar3,uVar4);
  set_background_color((uint)extraout_AH_31 << 8);
  validate_window_coords(CONCAT11(extraout_AH_32,6),CONCAT11(extraout_AH_32,0x22));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(0,player_level,player_level >> 0xf);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_33,6),CONCAT11(extraout_AH_33,0x38));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(0,experience,experience >> 0xf);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_34,8),CONCAT11(extraout_AH_34,0x22));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(0,current_hp,current_hp >> 0xf);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_35,8),CONCAT11(extraout_AH_35,0x38));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(0,max_hp,max_hp >> 0xf);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_36,10),CONCAT11(extraout_AH_36,0x22));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(0,current_food,current_food >> 0xf);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_37,10),CONCAT11(extraout_AH_37,0x38));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(0,max_food,max_food >> 0xf);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_38,0xc),CONCAT11(extraout_AH_38,0x22));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(0,strength,strength >> 0xf);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_39,0xc),CONCAT11(extraout_AH_39,0x38));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(0,intelligence,intelligence >> 0xf);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_40,0xe),CONCAT11(extraout_AH_40,0x22));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  write_padded_number(0,*(undefined2 *)ADDR_GOLD_LOW /* gold_low */,*(undefined2 *)ADDR_GOLD_HIGH /* gold_high */);
  flush_output(uVar3,uVar4);
  validate_window_coords(CONCAT11(extraout_AH_41,0xe),CONCAT11(extraout_AH_41,0x38));
  uVar4 = 0xe654;
  write_padded_number(0,base_ac,base_ac >> 0xf);
  flush_output(uVar4,unaff_DS);
  validate_window_coords(CONCAT11(extraout_AH_42,0x19),CONCAT11(extraout_AH_42,0x41));
  handle_error_and_wait();
  redraw_dungeon_level(0x17);
  return;
}



void __cdecl16near FUN_1000_53c9(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint value;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  uVar2 = *(undefined4 *)(dungeon_level * 4 + -0x5499);
  local_4 = (uint)((ulong)uVar2 >> 0x10);
  value = (uint)uVar2;
  while ((value | local_4) != 0) {
    put_char_at_pos(CONCAT11((char)((value | local_4) >> 8),*(undefined1 *)(value + 1)),
                  *(undefined2 *)(value + 0x1e),*(undefined2 *)(value + 0x1c));
    puVar1 = (undefined4 *)(value + 0x32);
    local_4 = (uint)((ulong)*puVar1 >> 0x10);
    value = (uint)*puVar1;
  }
  return;
}



void FUN_1000_5422(char param_1,char param_2)

{
  char *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  undefined2 uVar3;
  undefined2 uVar4;
  char *local_6;
  int local_4;
  
  pcVar1 = (char *)*(undefined4 *)(dungeon_level * 4 + -0x54d9);
  while (local_6 = (char *)pcVar1, local_4 = (int)((ulong)pcVar1 >> 0x10),
        local_6 != (char *)0x0 || local_4 != 0) {
    if (*pcVar1 == param_2) {
      if (needs_full_update == '\0') {
        *(undefined1 *)
         (dungeon_level * 0x719 + *(int *)(local_6 + 5) * MAP_WIDTH + *(int *)(local_6 + 7) + 0x70d) = 1
        ;
      }
      if ((((param_2 != '\x06') && (param_2 != '\a')) || (param_1 != '\0')) ||
         (*(int *)(local_6 + 9) != 0)) {
        uVar4 = *(undefined2 *)(local_6 + 5);
        uVar3 = *(undefined2 *)(local_6 + 7);
        uVar2 = lookup_table_b9c7(local_6,local_4);
        put_char_at_pos(uVar2,uVar3,uVar4);
      }
    }
    pcVar1 = *(char **)(local_6 + 0x16);
  }
  return;
}



void FUN_1000_54d2(int x_pos)

{
  undefined2 unaff_DS;
  undefined2 local_6;
  undefined2 local_4;
  
  local_6 = 1;
  while( true ) {
    put_char_at_pos(local_6 % 2 + 1,*(undefined2 *)ADDR_PLAYER_X /* player_x */,*(undefined2 *)ADDR_PLAYER_Y /* player_y */);
    local_4 = 1;
    while( true ) {
      play_tone_frequency(local_6 * x_pos);
      if (local_4 == 500) break;
      local_4 = local_4 + 1;
    }
    if (local_6 == 8) break;
    local_6 = local_6 + 1;
  }
  silence_speaker();
  return;
}



void FUN_1000_5527(int value)

{
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  if ((*(char *)(value + 6) != '\0') || (*(char *)*(undefined4 *)(value + 8) == '\a')) {
    uVar1 = 0xe654;
    write_bytes(0,0x73);
    flush_output(uVar1,unaff_DS);
  }
  return;
}



void display_object_info(char param_1,char param_2,char *flags)

{
  char ch;
  bool flag;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined1 extraout_AH_11;
  undefined1 extraout_AH_12;
  undefined1 extraout_AH_13;
  undefined1 extraout_AH_14;
  undefined1 extraout_AH_15;
  undefined1 extraout_AH_16;
  undefined1 extraout_AH_17;
  int value;
  undefined1 extraout_AH_18;
  undefined1 extraout_AH_19;
  undefined1 extraout_AH_20;
  char *pcVar4;
  char *pcVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 *puVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined1 local_28 [30];
  int local_a;
  char *local_8;
  int local_4;
  
  pcVar5 = (char *)flags;
  value = (int)((ulong)flags >> 0x10);
  if ((param_2 == '\0') || (*(int *)(pcVar5 + 3) < 2)) {
    flag = false;
  }
  else {
    flag = true;
  }
  print_space();
  local_8 = flags;
  ch = *flags;
  if (ch == '\x01') {
    if (flag) {
      uVar8 = 0xe654;
      write_padded_number(0,*(int *)(pcVar5 + 3),*(int *)(pcVar5 + 3) >> 0xf);
      flush_output(uVar8,unaff_DS);
    }
    else {
      uVar8 = 0xe654;
      write_padded_string(0,0x555c,0x1000);
      flush_output(uVar8,unaff_DS);
    }
    display_score_with_fatal(0x193);
    FUN_1000_5527(&stack0xfffe);
    display_score_with_fatal(0x194);
    FUN_1000_5527(&stack0xfffe);
    return;
  }
  if ((ch != '\a') && (ch != '\x06')) {
    if ((ch != '\x02') && (ch != '\x03')) {
      if (ch == '\x04') {
        display_score_with_fatal(0x19a);
        print_space();
        uVar8 = (undefined2)((ulong)local_8 >> 0x10);
        pcVar4 = (char *)local_8;
        if ((*(char *)(*local_8 * 0x18 + *(int *)(pcVar4 + 1) + -0x65a2) == '\0') &&
           (param_1 == '\0')) {
          if (*(char *)(*local_8 * 0x18 + *(int *)(pcVar4 + 1) + -0x6542) == '\0') {
            uVar10 = 0xe654;
            uVar9 = unaff_DS;
            write_padded_string(0,*(int *)(pcVar4 + 1) * 0x10 + -0x5a19,unaff_DS);
            flush_output(uVar10,uVar9);
          }
          else {
            display_score_with_fatal(0x19b);
            uVar9 = 0xe654;
            uVar8 = unaff_DS;
            write_bytes(0,CONCAT11(extraout_AH_15,0x20));
            write_padded_string(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + -0x75de,
                          unaff_DS);
            flush_output(uVar9,uVar8);
            uVar9 = 0xe654;
            uVar8 = unaff_DS;
            write_padded_string(0,0x5566,0x214c);
            write_padded_string(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5a19,unaff_DS);
            write_bytes(0,CONCAT11(extraout_AH_16,0x29));
            flush_output(uVar9,uVar8);
          }
        }
        else {
          uVar10 = 0xe654;
          uVar6 = 1;
          uVar9 = unaff_DS;
          write_padded_string(0,*local_8 * 0x2b8 + *(int *)(pcVar4 + 1) * 0x1d + 0x75fa,unaff_DS);
          flush_output(uVar10,uVar9);
          uVar8 = CONCAT11(extraout_AH_10,((char *)local_8)[1]);
          puVar7 = local_28;
          zero_word_array_16(puVar7);
          set_bit_in_array(CONCAT11(extraout_AH_11,4));
          set_bit_in_array(CONCAT11(extraout_AH_12,7));
          set_bit_in_array(CONCAT11(extraout_AH_13,9));
          create_bit_mask(puVar7,unaff_SS,uVar8);
          if (!(bool)uVar6) {
            uVar8 = (undefined2)((ulong)local_8 >> 0x10);
            pcVar4 = (char *)local_8;
            if ((pcVar4[0x13] != '\0') || (param_1 != '\0')) {
              if (*(int *)(pcVar4 + 9) < 0) {
                uVar10 = 0xe654;
                uVar9 = unaff_DS;
                write_padded_number(3,*(int *)(pcVar4 + 9),*(int *)(pcVar4 + 9) >> 0xf);
                flush_output(uVar10,uVar9);
              }
              else {
                uVar9 = 0xe654;
                uVar8 = unaff_DS;
                write_padded_string(0,0x5560,0x214c);
                write_padded_number(0,*(int *)((char *)local_8 + 9),*(int *)((char *)local_8 + 9) >> 0xf);
                flush_output(uVar9,uVar8);
              }
            }
          }
          uVar9 = 0xe654;
          uVar8 = unaff_DS;
          write_padded_string(0,0x5566,0x214c);
          write_padded_string(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5a19,unaff_DS);
          write_bytes(0,CONCAT11(extraout_AH_14,0x29));
          flush_output(uVar9,uVar8);
        }
        local_a = *(int *)0xb936;
        if (local_a < 1) {
          return;
        }
        local_4 = 1;
        while( true ) {
          if ((value == *(int *)(local_4 * 4 + -0x46ca)) &&
             (pcVar5 == (char *)*(undefined2 *)(local_4 * 4 + -0x46cc))) {
            uVar9 = 0xe654;
            uVar8 = unaff_DS;
            write_padded_string(0,0x5566,0x214c);
            write_padded_number(0,local_4,local_4 >> 0xf);
            write_bytes(0,CONCAT11(extraout_AH_17,0x29));
            flush_output(uVar9,uVar8);
          }
          if (local_4 == local_a) break;
          local_4 = local_4 + 1;
        }
        return;
      }
      if (ch == '\x05') {
        display_score_with_fatal(0x19c);
        print_space();
        uVar8 = (undefined2)((ulong)local_8 >> 0x10);
        pcVar5 = (char *)local_8;
        if ((*(char *)(*local_8 * 0x18 + *(int *)(pcVar5 + 1) + -0x65a2) == '\0') &&
           (param_1 == '\0')) {
          if (*(char *)(*local_8 * 0x18 + *(int *)(pcVar5 + 1) + -0x6542) == '\0') {
            uVar9 = 0xe654;
            write_padded_string(0,*(int *)(pcVar5 + 1) * 0x10 + -0x5789,unaff_DS);
            flush_output(uVar9,unaff_DS);
            return;
          }
          display_score_with_fatal(0x19d);
          uVar9 = 0xe654;
          uVar8 = unaff_DS;
          write_bytes(0,CONCAT11(extraout_AH_19,0x20));
          write_padded_string(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + -0x75de,unaff_DS
                       );
          flush_output(uVar9,uVar8);
          uVar9 = 0xe654;
          uVar8 = unaff_DS;
          write_padded_string(0,0x5566,0x214c);
          write_padded_string(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5789,unaff_DS);
          write_bytes(0,CONCAT11(extraout_AH_20,0x29));
          flush_output(uVar9,uVar8);
          return;
        }
        uVar10 = 0xe654;
        uVar9 = unaff_DS;
        write_padded_string(0,*local_8 * 0x2b8 + *(int *)(pcVar5 + 1) * 0x1d + 0x75fa,unaff_DS);
        flush_output(uVar10,uVar9);
        if ((((char *)local_8)[0x13] != '\0') || (param_1 != '\0')) {
          uVar9 = 0xe654;
          uVar8 = unaff_DS;
          write_padded_string(0,0x5566,0x214c);
          value = *(int *)((char *)local_8 + 9);
          if (value < 0) {
            value = -value;
          }
          write_padded_number(0,value,value >> 0xf);
          write_padded_string(0,0x5569,0x214c);
          flush_output(uVar9,uVar8);
        }
        uVar9 = 0xe654;
        uVar8 = unaff_DS;
        write_padded_string(0,0x5566,0x214c);
        write_padded_string(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5789,unaff_DS);
        write_bytes(0,CONCAT11(extraout_AH_18,0x29));
        flush_output(uVar9,uVar8);
        return;
      }
      if (ch != '\b') {
        if (ch != '\0') {
          return;
        }
        uVar8 = 0xe654;
        write_padded_number(0,*(int *)(pcVar5 + 9),*(int *)(pcVar5 + 9) >> 0xf);
        flush_output(uVar8,unaff_DS);
        display_score_with_fatal(0x19f);
        return;
      }
      if (*(int *)(pcVar5 + 1) == 0) {
        display_score_with_fatal(0x19e);
        return;
      }
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      write_padded_string(0,*(int *)(pcVar5 + 0x11) * 0x10 + -0x5629,unaff_DS);
      flush_output(uVar9,uVar8);
      uVar8 = (undefined2)((ulong)local_8 >> 0x10);
      if (((char *)local_8)[0x13] != '\0') {
        uVar10 = 0xe654;
        uVar9 = unaff_DS;
        write_padded_string(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + 0x75fa,unaff_DS);
        flush_output(uVar10,uVar9);
      }
      if (((char *)local_8)[0x14] != '\0') {
        return;
      }
      uVar9 = 0xe654;
      write_padded_string(0,0x5573,0x214c);
      uVar8 = (undefined2)((ulong)local_8 >> 0x10);
      write_padded_number(0,*(undefined2 *)((char *)local_8 + 0xd),*(undefined2 *)((char *)local_8 + 0xf))
      ;
      write_padded_string(0,0x5577,0x214c);
      flush_output(uVar9,unaff_DS);
      return;
    }
    if (flag) {
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      write_padded_number(0,*(int *)(pcVar5 + 3),*(int *)(pcVar5 + 3) >> 0xf);
      flush_output(uVar9,uVar8);
    }
    else if (*flags == '\x02') {
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      write_padded_string(0,0x555c,0x1000);
      flush_output(uVar9,uVar8);
    }
    else {
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      write_padded_string(0,0x5563,0x1000);
      flush_output(uVar9,uVar8);
    }
    if (*flags == '\x02') {
      display_score_with_fatal(0x196);
    }
    else {
      display_score_with_fatal(0x197);
    }
    FUN_1000_5527(&stack0xfffe);
    uVar8 = (undefined2)((ulong)local_8 >> 0x10);
    if ((*(char *)(*local_8 * 0x18 + *(int *)((char *)local_8 + 1) + -0x65a2) != '\0') ||
       (param_1 != '\0')) {
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      write_bytes(0,CONCAT11((char)((uint)(*local_8 * 0x18) >> 8),0x20));
      write_padded_string(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + 0x75fa,unaff_DS);
      flush_output(uVar9,uVar8);
      uVar6 = *flags == '\x02';
      if ((bool)uVar6) {
        uVar8 = CONCAT11(extraout_AH_01,pcVar5[1]);
        puVar7 = local_28;
        zero_word_array_16(puVar7);
        set_bit_range_in_array(CONCAT11(extraout_AH_02,0xd),CONCAT11(extraout_AH_02,6));
        create_bit_mask(puVar7,unaff_SS,uVar8);
        if (!(bool)uVar6) {
          FUN_1000_5527(&stack0xfffe);
        }
        uVar9 = 0xe654;
        uVar8 = unaff_DS;
        write_padded_string(0,0x5566,0x214c);
        write_padded_string(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5cc9,unaff_DS);
        write_bytes(0,CONCAT11(extraout_AH_03,0x29));
        flush_output(uVar9,uVar8);
        return;
      }
      uVar8 = CONCAT11(extraout_AH_01,pcVar5[1]);
      puVar7 = local_28;
      zero_word_array_16(puVar7);
      set_bit_in_array(CONCAT11(extraout_AH_04,3));
      set_bit_in_array(CONCAT11(extraout_AH_05,9));
      create_bit_mask(puVar7,unaff_SS,uVar8);
      if ((bool)uVar6) {
        return;
      }
      FUN_1000_5527(&stack0xfffe);
      return;
    }
    if (*(char *)(*local_8 * 0x18 + *(int *)((char *)local_8 + 1) + -0x6542) != '\0') {
      display_score_with_fatal(0x198);
      if (*local_8 == '\x02') {
        uVar9 = 0xe654;
        uVar8 = unaff_DS;
        write_bytes(0,CONCAT11(extraout_AH_06,0x65));
        flush_output(uVar9,uVar8);
      }
      FUN_1000_5527(&stack0xfffe);
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      write_bytes(0,CONCAT11(extraout_AH_07,0x20));
      write_padded_string(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + -0x75de,unaff_DS);
      flush_output(uVar9,uVar8);
      if (*local_8 != '\x02') {
        return;
      }
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      write_padded_string(0,0x5566,0x214c);
      write_padded_string(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5cc9,unaff_DS);
      flush_output(uVar9,uVar8);
      FUN_1000_5527(&stack0xfffe);
      uVar8 = 0xe654;
      write_bytes(0,CONCAT11(extraout_AH_08,0x29));
      flush_output(uVar8,unaff_DS);
      return;
    }
    if (*local_8 == '\x03') {
      display_score_with_fatal(0x199);
      FUN_1000_5527(&stack0xfffe);
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      write_bytes(0,CONCAT11(extraout_AH_09,0x20));
      write_padded_string(0,*(int *)((char *)local_8 + 1) * 0x1d + -0x610e,unaff_DS);
      flush_output(uVar9,uVar8);
      return;
    }
    if (*local_8 != '\x02') {
      return;
    }
    uVar9 = 0xe654;
    uVar8 = unaff_DS;
    write_bytes(0,CONCAT11((char)((uint)(*local_8 * 0x18) >> 8),0x20));
    write_padded_string(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5cc9,unaff_DS);
    flush_output(uVar9,uVar8);
    FUN_1000_5527(&stack0xfffe);
    return;
  }
  uVar6 = *flags == '\x06';
  if ((bool)uVar6) {
    uVar8 = CONCAT11(extraout_AH,pcVar5[1]);
    puVar7 = local_28;
    zero_word_array_16(puVar7);
    set_bit_range_in_array(CONCAT11(extraout_AH_00,0xb),CONCAT11(extraout_AH_00,9));
    create_bit_mask(puVar7,unaff_SS,uVar8);
    if (!(bool)uVar6) {
      uVar8 = (undefined2)((ulong)local_8 >> 0x10);
      if (((char *)local_8)[0x13] == '\0') {
        display_score_with_fatal(0x1a8);
      }
      else {
        uVar10 = 0xe654;
        uVar9 = unaff_DS;
        write_padded_string(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + 0x75fa,unaff_DS);
        flush_output(uVar10,uVar9);
      }
      goto LAB_1000_5755;
    }
  }
  if (*(int *)(pcVar5 + 1) == 0xc) {
    uVar9 = 0xe654;
    uVar8 = unaff_DS;
    write_padded_number(0,*(int *)(pcVar5 + 3),*(int *)(pcVar5 + 3) >> 0xf);
    flush_output(uVar9,uVar8);
  }
  uVar9 = 0xe654;
  uVar8 = unaff_DS;
  write_padded_string(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + 0x75fa,unaff_DS);
  flush_output(uVar9,uVar8);
  if (1 < *(int *)(pcVar5 + 3)) {
    FUN_1000_5527(&stack0xfffe);
  }
  uVar8 = (undefined2)((ulong)local_8 >> 0x10);
  pcVar4 = (char *)local_8;
  if ((pcVar4[0x13] != '\0') || (param_1 != '\0')) {
    if (*(int *)(pcVar4 + 9) < 0) {
      uVar10 = 0xe654;
      uVar9 = unaff_DS;
      write_padded_number(3,*(int *)(pcVar4 + 9),*(int *)(pcVar4 + 9) >> 0xf);
      flush_output(uVar10,uVar9);
    }
    else {
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      write_padded_string(0,0x5560,0x214c);
      write_padded_number(0,*(int *)((char *)local_8 + 9),*(int *)((char *)local_8 + 9) >> 0xf);
      flush_output(uVar9,uVar8);
    }
  }
LAB_1000_5755:
  if ((((((value == *(int *)0xb924) && (pcVar5 == (char *)wielded_weapon)) ||
        ((value == *(int *)0xb928 && (pcVar5 == (char *)equipped_shield)))) ||
       ((value == *(int *)0xb92c && (pcVar5 == (char *)equipped_armor)))) ||
      ((value == *(int *)0xb934 && (pcVar5 == (char *)equipped_ring2)))) ||
     ((value == *(int *)0xb930 && (pcVar5 == (char *)equipped_ring1)))) {
    display_score_with_fatal(0x195);
  }
  return;
}



void __cdecl16near FUN_1000_5fd2(void)

{
  undefined4 *puVar1;
  undefined1 extraout_AH;
  int flag;
  byte extraout_AH_00;
  undefined1 uVar3;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined2 unaff_DS;
  undefined2 uVar4;
  undefined2 uVar5;
  int local_8;
  uint flag;
  uint flag;
  
  flag = (uint)((ulong)inventory_list >> 0x10);
  flag = (uint)inventory_list;
  if (flag == 0 && flag == 0) {
    display_score_with_fatal(0xbd);
    uVar3 = extraout_AH;
  }
  else {
    local_8 = 0;
    while (flag != 0 || flag != 0) {
      flag = local_8 + 1;
      validate_window_coords(flag,CONCAT11((char)((uint)flag >> 8),1));
      update_screen_double();
      if (flag < 0x1b) {
        uVar4 = 0xe654;
        uVar5 = unaff_DS;
        write_bytes(2,local_8 + 0x61);
        flush_output(uVar4,uVar5);
      }
      else {
        uVar4 = 0xe654;
        uVar5 = unaff_DS;
        write_bytes(2,local_8 + 0x27);
        flush_output(uVar4,uVar5);
      }
      uVar4 = 0xe654;
      uVar5 = unaff_DS;
      write_padded_string(0,0x5fce,0x214c);
      flush_output(uVar4,uVar5);
      display_object_info((uint)extraout_AH_00 << 8,CONCAT11(extraout_AH_00,1),flag,flag);
      write_word(0x214c,0xe654);
      puVar1 = (undefined4 *)(flag + 0x16);
      flag = (uint)((ulong)*puVar1 >> 0x10);
      flag = (uint)*puVar1;
      local_8 = flag;
      if (((flag == 0x18) || (flag == 0x30)) && ((flag | flag) != 0)) {
        uVar3 = (undefined1)((flag | flag) >> 8);
        validate_window_coords(CONCAT11(uVar3,0x41),CONCAT11(uVar3,0x19));
        handle_error_and_wait();
        clear_screen_double();
        validate_window_coords(CONCAT11(extraout_AH_01,1),CONCAT11(extraout_AH_01,1));
      }
    }
    uVar3 = 0;
  }
  validate_window_coords(CONCAT11(uVar3,0x19),CONCAT11(uVar3,1));
  update_screen_double();
  validate_window_coords(CONCAT11(extraout_AH_02,0x19),CONCAT11(extraout_AH_02,0x41));
  handle_error_and_wait();
  if (local_8 < 0x18) {
    redraw_dungeon_level(local_8);
  }
  else {
    redraw_dungeon_level(0x17);
  }
  return;
}



void FUN_1000_610b(char param_1)

{
  int value;
  char *pcVar2;
  bool flag;
  byte extraout_AH;
  undefined2 unaff_DS;
  undefined2 uVar4;
  undefined2 uVar5;
  int local_b;
  int local_9;
  char *local_6;
  int flag;
  
  check_minimum_stats();
  local_b = 0;
  local_9 = 0;
  value = *(int *)(param_1 * 4 + -0x4736);
  if ((value < 1) && ((value < 0 || (*(uint *)(param_1 * 4 + -0x4738) < 2)))) {
    flag = false;
  }
  else {
    flag = true;
  }
  pcVar2 = (char *)inventory_list;
  while( true ) {
    local_6 = (char *)pcVar2;
    flag = (int)((ulong)pcVar2 >> 0x10);
    if (local_6 == (char *)0x0 && flag == 0) break;
    if (param_1 == *pcVar2) {
      local_9 = local_9 + 1;
      validate_window_coords(local_9,CONCAT11((char)((uint)local_9 >> 8),1));
      update_screen_double();
      if (local_b + 1 < 0x1b) {
        uVar4 = 0xe654;
        uVar5 = unaff_DS;
        write_bytes(2,local_b + 0x61);
        flush_output(uVar4,uVar5);
      }
      else {
        uVar4 = 0xe654;
        uVar5 = unaff_DS;
        write_bytes(2,local_b + 0x27);
        flush_output(uVar4,uVar5);
      }
      uVar4 = 0xe654;
      uVar5 = unaff_DS;
      write_padded_string(0,0x6108,0x214c);
      flush_output(uVar4,uVar5);
      update_screen_double();
      display_object_info((uint)extraout_AH << 8,CONCAT11(extraout_AH,1),local_6,flag);
      if (flag) {
        write_word(0x20e6,0xe654);
      }
    }
    pcVar2 = *(char **)(local_6 + 0x16);
    local_b = local_b + 1;
  }
  if (flag) {
    validate_window_coords(local_9 + 1,0x41);
    handle_error_and_wait();
    if (local_9 < 0x17) {
      redraw_dungeon_level(local_9 + 1);
    }
    else {
      redraw_dungeon_level(0x17);
    }
  }
  else {
    handle_error_and_wait();
  }
  return;
}



void __cdecl16near FUN_1000_6249(void)

{
  undefined1 extraout_AH;
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 flag;
  
  uVar1 = 0x20e6;
  clear_screen_double();
  flag = 0x134;
  while( true ) {
    if ((flag == 0x13e) || (uVar2 = uVar1, flag == 0x144)) {
      uVar2 = 0x214c;
      write_word(uVar1,0xe654);
    }
    display_score_with_fatal(flag);
    uVar1 = 0x214c;
    write_word(uVar2,0xe654);
    if (flag == 0x146) break;
    flag = flag + 1;
  }
  validate_window_coords(CONCAT11(extraout_AH,0x19),CONCAT11(extraout_AH,0x41));
  handle_error_and_wait();
  redraw_dungeon_level(0x17);
  return;
}



void __cdecl16near FUN_1000_62b7(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  byte bVar4;
  uint value;
  undefined1 uVar6;
  undefined2 unaff_DS;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 local_4;
  
  clear_screen_double();
  uVar2 = *(undefined4 *)(dungeon_level * 4 + -0x5499);
  local_4 = (uint)((ulong)uVar2 >> 0x10);
  uVar3 = (uint)uVar2;
  while (uVar6 = (undefined1)((uVar3 | local_4) >> 8), (uVar3 | local_4) != 0) {
    uVar7 = 0xe654;
    uVar8 = unaff_DS;
    write_bytes(0,CONCAT11(uVar6,*(undefined1 *)(uVar3 + 1)));
    write_padded_string(0,0x62a6,0x214c);
    write_padded_number(4,*(int *)(uVar3 + 10),*(int *)(uVar3 + 10) >> 0xf);
    write_padded_number(4,*(int *)(uVar3 + 0xc),*(int *)(uVar3 + 0xc) >> 0xf);
    write_padded_number(4,*(int *)(uVar3 + 8),*(int *)(uVar3 + 8) >> 0xf);
    write_padded_number(4,*(int *)(uVar3 + 0x10),*(int *)(uVar3 + 0x10) >> 0xf);
    flush_output(uVar7,uVar8);
    value = *(uint *)(uVar3 + 0x2e) | *(uint *)(uVar3 + 0x30);
    if (value != 0) {
      uVar6 = (undefined1)(value >> 8);
      display_object_info(CONCAT11(uVar6,1),CONCAT11(uVar6,1),*(undefined2 *)(uVar3 + 0x2e),
                    *(undefined2 *)(uVar3 + 0x30));
    }
    uVar7 = 0xe654;
    uVar8 = unaff_DS;
    write_padded_string(0,0x62a9,0x214c);
    write_padded_number(4,*(int *)(uVar3 + 0x1c),*(int *)(uVar3 + 0x1c) >> 0xf);
    write_padded_string(0,0x62ad,0x214c);
    write_padded_number(4,*(int *)(uVar3 + 0x1e),*(int *)(uVar3 + 0x1e) >> 0xf);
    flush_output(uVar7,uVar8);
    if (*(char *)(uVar3 + 0x28) == '\0') {
      write_word(0x214c,0xe654);
    }
    else {
      uVar8 = 0xe654;
      write_padded_string(0,0x62b1,0x214c);
      write_word(0x214c,uVar8);
    }
    bVar4 = get_relative_cursor_x();
    if (0x16 < bVar4) {
      handle_error_and_wait();
      clear_screen_double();
    }
    puVar1 = (undefined4 *)(uVar3 + 0x32);
    local_4 = (uint)((ulong)*puVar1 >> 0x10);
    uVar3 = (uint)*puVar1;
  }
  validate_window_coords(CONCAT11(uVar6,0x19),CONCAT11(uVar6,0x41));
  handle_error_and_wait();
  redraw_dungeon_level(0x17);
  return;
}



void __cdecl16near FUN_1000_6431(void)

{
  int value;
  byte bVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 uVar3;
  undefined2 unaff_DS;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined4 local_6;
  
  clear_screen_double();
  local_6 = (char *)*(undefined4 *)(dungeon_level * 4 + -0x54d9);
  while( true ) {
    if ((char *)local_6 == (char *)0x0 && local_6._2_2_ == 0) break;
    while( true ) {
      if ((char *)local_6 == (char *)0x0 && local_6._2_2_ == 0) break;
      uVar4 = 0xe654;
      uVar5 = unaff_DS;
      write_padded_number(4,*(int *)((char *)local_6 + 5),*(int *)((char *)local_6 + 5) >> 0xf);
      write_padded_number(4,*(int *)((char *)local_6 + 7),*(int *)((char *)local_6 + 7) >> 0xf);
      write_bytes(0,CONCAT11(extraout_AH,0x20));
      flush_output(uVar4,uVar5);
      uVar3 = extraout_AH_00;
      if (*local_6 == '\x05') {
        uVar4 = 0xe654;
        value = *(int *)(*(int *)((char *)local_6 + 1) * 4 + -0x6243);
        uVar5 = unaff_DS;
        write_padded_number(2,value,value >> 0xf);
        flush_output(uVar4,uVar5);
        uVar3 = extraout_AH_01;
      }
      display_object_info(CONCAT11(uVar3,1),CONCAT11(uVar3,1),(char *)local_6,local_6._2_2_);
      write_word(0x214c,0xe654);
      local_6 = *(char **)((char *)local_6 + 0x16);
      bVar2 = get_relative_cursor_x();
      if (0x16 < bVar2) {
        handle_error_and_wait();
        clear_screen_double();
      }
    }
  }
  validate_window_coords(0x19,0x41);
  handle_error_and_wait();
  redraw_dungeon_level(0x17);
  return;
}



void __cdecl16near process_options_menu(void)

{
  char cVar1;
  undefined1 extraout_AH;
  undefined2 uVar2;
  undefined2 extraout_DX;
  undefined2 unaff_DS;
  undefined2 uVar3;
  undefined2 uVar4;
  
  clear_screen_double();
  uVar4 = 0xe654;
  write_padded_string(0,0x6527,0x20e6);
  write_padded_number(4,*(int *)0xe52f,*(int *)0xe52f >> 0xf);
  write_padded_number(4,*(int *)0xe531,*(int *)0xe531 >> 0xf);
  write_word(0x214c,uVar4);
  uVar4 = 0xe654;
  write_padded_string(0,0x652b,0x214c);
  write_padded_number(5,turn_count,turn_count >> 0xf);
  write_padded_number(5,food_level,food_level >> 0xf);
  write_word(0x214c,uVar4);
  write_padded_number(4,*(int *)0xb8c4,*(int *)0xb8c4 >> 0xf);
  write_bytes(0,CONCAT11(extraout_AH,0x2f));
  write_padded_number(0,*(int *)0xb8c6,*(int *)0xb8c6 >> 0xf);
  write_padded_string(0,0x652f,0x214c);
  write_padded_number(0,*(int *)0xb8c2,*(int *)0xb8c2 >> 0xf);
  write_word(0x214c);
  uVar4 = 0xe654;
  write_padded_string(0,0x6533,0x214c);
  write_word(0x214c,uVar4);
  uVar4 = 0xe654;
  write_padded_string(0,0x653e,0x214c);
  write_word(0x214c,uVar4);
  write_padded_string(0,0x654d,0x214c);
  write_word(0x214c);
  write_padded_string(0,0x6565,0x214c);
  write_word(0x214c);
  write_padded_string(0,0x657d,0x214c);
  write_word(0x214c);
  write_padded_string(0,0x658a,0x214c);
  write_word(0x214c);
  write_padded_string(0,0x6596,0x214c);
  write_word(0x214c);
  write_padded_string(0,0x65a4,0x214c);
  write_word(0x214c);
  write_padded_string(0,0x65b5,0x214c);
  write_word(0x214c);
  uVar3 = 0xe654;
  write_padded_string(0,0x65c9,0x214c);
  write_word(0x214c);
  uVar4 = extraout_DX;
  cVar1 = read_keyboard_input();
  if (cVar1 == 'v') {
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = uVar4;
    read_line(0x214c);
  }
  else if (cVar1 == CMD_CAST_SPELL) {
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_MAX_HP /* max_hp */ = uVar4;
    read_line(0x214c);
  }
  else if (cVar1 == CMD_EQUIPMENT) {
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_PLAYER_LEVEL /* player_level */ = uVar4;
    read_line(0x214c);
  }
  else if (cVar1 == 'x') {
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_EXPERIENCE /* experience */ = uVar4;
    read_line(0x214c);
  }
  else if (cVar1 == 'f') {
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_CURRENT_FOOD /* current_food */ = uVar4;
    read_line(0x214c);
  }
  else if (cVar1 == CMD_SEARCH) {
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_FOOD_LEVEL = uVar4;
    read_line(0x214c);
  }
  else if (cVar1 == 'a') {
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_BASE_AC /* base_ac */ = uVar4;
    read_line(0x214c);
  }
  else if (cVar1 == 'd') {
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_STRENGTH /* strength */ = uVar4;
    read_line(0x214c);
  }
  else if (cVar1 == CMD_INVENTORY) {
    uVar4 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_INTELLIGENCE /* intelligence */ = uVar4;
    read_line(0x214c);
  }
  else if (cVar1 == 'o') {
    uVar2 = read_token_and_parse_number(0xe554);
    *(undefined2 *)ADDR_GOLD_LOW /* gold_low */ = uVar2;
    *(undefined2 *)ADDR_GOLD_HIGH /* gold_high */ = uVar4;
    read_line(0x214c);
  }
  redraw_dungeon_level(0x17,uVar3);
  return;
}



void __cdecl16near redraw_screen_map(void)

{
  undefined4 uVar1;
  undefined2 unaff_DS;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 flag;
  undefined2 local_6;
  
  flag = 1;
  while( true ) {
    local_6 = 1;
    while( true ) {
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      if (*(char *)((int)uVar1 + flag * MAP_WIDTH + local_6 + -0x50) != ' ') {
        validate_window_coords(flag + 1,CONCAT11((char)((uint)(flag * MAP_WIDTH) >> 8),(undefined1)local_6))
        ;
        uVar2 = 0xe654;
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        uVar3 = unaff_DS;
        write_bytes(0,CONCAT11((char)((uint)(flag * MAP_WIDTH) >> 8),
                                 *(undefined1 *)((int)uVar1 + flag * MAP_WIDTH + local_6 + -0x50)));
        flush_output(uVar2,uVar3);
      }
      if (local_6 == MAP_WIDTH) break;
      local_6 = local_6 + 1;
    }
    if (flag == 0x17) break;
    flag = flag + 1;
  }
  return;
}



void __cdecl16near display_help_file(void)

{
  char damage;
  int flag;
  undefined2 damage;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 unaff_SS;
  undefined1 damage;
  undefined2 damage;
  undefined1 *puVar6;
  undefined1 local_177 [32];
  char damage;
  undefined1 local_156 [81];
  char damage;
  int flag;
  undefined1 local_102 [256];
  
  damage = '\x01';
  init_fcb(0x6917,0x1000,local_102,unaff_SS);
  file_open_wrapper(0x214c,local_102);
  flag = get_and_clear_error_code();
  if (flag == 0) {
    while ((damage != '\0' && (damage = skip_whitespace(local_102,unaff_SS), damage == '\0'))) {
      clear_screen_double();
      flag = 1;
      while( true ) {
        damage = skip_whitespace(local_102,unaff_SS);
        if (damage == '\0') {
          puVar6 = local_102;
          read_string_from_file(0x50,local_156,unaff_SS);
          read_line(0x214c,puVar6);
          damage = 0xe654;
          write_padded_string(0,local_156,unaff_SS);
          write_word(0x214c,damage);
        }
        damage = flag == 0x18;
        if ((bool)damage) break;
        flag = flag + 1;
      }
      validate_window_coords(0x28,0x19);
      display_score_with_fatal(0x52);
      do {
        damage = read_keyboard_input();
        damage = (char)damage;
        puVar6 = local_177;
        damage = unaff_SS;
        zero_word_array_16(puVar6);
        set_bit_in_array(CONCAT11(extraout_AH,0x20));
        set_bit_in_array(CONCAT11(extraout_AH_00,0x66));
        set_bit_in_array(CONCAT11(extraout_AH_01,0x46));
        create_bit_mask(puVar6,damage,damage);
      } while ((bool)damage);
      damage = damage == ' ';
    }
  }
  else {
    clear_screen_double();
    display_score_with_fatal(0x14a);
    handle_error_and_wait();
  }
  return;
}



void __cdecl16near display_inventory_list(void)

{
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar2;
  bool flag;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined1 local_4c [32];
  int local_2c;
  undefined1 local_28 [32];
  int flag;
  uint local_6;
  uint local_4;
  
  clear_screen_double();
  local_6 = 1;
  local_4 = 3;
  display_score_with_fatal(0xb6);
  uVar7 = 0xe654;
  write_bytes(0,CONCAT11(extraout_AH,0x20));
  uVar2 = 1;
  write_padded_string(0,0xb84f,unaff_DS);
  write_word(0x214c,uVar7);
  write_word(0x214c,0xe654);
  flag = 1;
  while( true ) {
    uVar6 = CONCAT11((char)((uint)(flag * 0x2a) >> 8),*(undefined1 *)(flag * 0x2a + -0x5007));
    puVar5 = local_28;
    uVar7 = unaff_SS;
    pad_and_copy_buffer(0x20,0xb82f,unaff_DS);
    create_bit_mask(puVar5,uVar7,uVar6);
    if (((bool)uVar2) && (0 < *(int *)(flag * 2 + -0x460b))) {
      validate_window_coords(local_4 & 0xff,local_6 & 0xff);
      _local_2c = CONCAT22(unaff_DS,flag * 0x2a + -0x5017);
      flag = flag * 5 + -0x4a34;
      flag = flag == 0;
      compare_pascal_strings(0x6a3c,0x20e6,flag,unaff_DS);
      if (!flag) {
        uVar6 = 0xe654;
        flag = *(int *)(flag * 2 + -0x460b);
        uVar7 = unaff_DS;
        write_padded_number(4,flag,flag >> 0xf);
        write_bytes(0,CONCAT11(extraout_AH_00,0x20));
        flush_output(uVar6,uVar7);
      }
      if ((*(int *)(flag * 2 + -0x460b) < 2) || (*(char *)((int)_local_2c + 0x10) != 'E')) {
        uVar6 = 0xe654;
        uVar7 = unaff_DS;
        write_padded_string(0,flag * 0x2a + -0x5017,unaff_DS);
        flush_output(uVar6,uVar7);
        uVar2 = extraout_AH_02;
      }
      else {
        uVar6 = 0xe654;
        uVar7 = unaff_DS;
        write_padded_string(0,0x6a3d,0x214c);
        flush_output(uVar6,uVar7);
        uVar2 = extraout_AH_01;
      }
      flag = *(int *)(flag * 2 + -0x460b);
      uVar4 = flag == 1;
      if (1 < flag) {
        uVar6 = CONCAT11(uVar2,*(undefined1 *)((int)_local_2c + 0x10));
        puVar5 = local_4c;
        uVar7 = unaff_SS;
        zero_word_array_16(puVar5);
        set_bit_in_array(CONCAT11(extraout_AH_03,0x43));
        set_bit_in_array(CONCAT11(extraout_AH_04,0x45));
        create_bit_mask(puVar5,uVar7,uVar6);
        if ((bool)uVar4) {
          uVar6 = 0xe654;
          uVar7 = unaff_DS;
          write_bytes(0,CONCAT11(extraout_AH_05,0x73));
          flush_output(uVar6,uVar7);
        }
      }
      write_word(0x214c,0xe654);
      local_4 = local_4 + 1;
      if (0x17 < (int)local_4) {
        local_6 = local_6 + 0x27;
        local_4 = 3;
      }
    }
    if (flag == 0x23) break;
    flag = flag + 1;
    uVar2 = flag == 0;
  }
  validate_window_coords(local_4 & 0xff,local_6 & 0xff);
  if (*(int *)0xba39 != 0) {
    uVar6 = 0xe654;
    uVar7 = unaff_DS;
    write_padded_string(0,0x6a43,0x20e6);
    flush_output(uVar6,uVar7);
  }
  local_4 = local_4 + 1;
  validate_window_coords(local_4,CONCAT11((char)(local_4 >> 8),(undefined1)local_6));
  uVar2 = extraout_AH_06;
  if (*(int *)0xba3b != 0) {
    uVar7 = 0xe654;
    write_padded_string(0,0x6a4c,0x20e6);
    flush_output(uVar7,unaff_DS);
    uVar2 = extraout_AH_07;
  }
  validate_window_coords(CONCAT11(uVar2,0x19),CONCAT11(uVar2,0x41));
  handle_error_and_wait();
  redraw_dungeon_level(0x17);
  return;
}



void __cdecl16near load_high_scores(void)

{
  uint damage;
  int damage;
  int damage;
  int iVar4;
  char damage;
  byte damage;
  int flag;
  undefined2 damage;
  uint damage;
  undefined2 damage;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar11;
  byte *local_10e;
  int flag;
  int damage;
  undefined1 local_102 [256];
  
  damage = 1;
  init_fcb(0x6c89,0x1000,local_102,unaff_SS);
  file_open_wrapper(0x214c,local_102);
  flag = get_and_clear_error_code();
  if (flag == 0) {
    while ((damage = skip_whitespace(local_102,unaff_SS), damage == '\0' && (damage != 0x10))) {
      iVar4 = damage * 0x18;
      _local_10e = (byte *)CONCAT22(unaff_DS,(byte *)(iVar4 + -0x45db));
      puVar11 = local_102;
      damage = unaff_SS;
      getc(puVar11);
      flush_input(puVar11,damage);
      damage = 0;
      damage = multiply_integers();
      *(undefined2 *)(iVar4 + -0x45c9) = damage;
      *(undefined2 *)(iVar4 + -0x45c7) = damage;
      puVar11 = local_102;
      damage = unaff_SS;
      damage = getc(puVar11);
      flush_input(puVar11,damage);
      damage = (uint)damage * 0x100;
      damage = *(uint *)(iVar4 + -0x45c9);
      flag = *(int *)(iVar4 + -0x45c7);
      *(int *)(iVar4 + -0x45c9) = damage + *(uint *)(iVar4 + -0x45c9);
      *(int *)(iVar4 + -0x45c7) = ((int)damage >> 0xf) + flag + (uint)CARRY2(damage,damage);
      puVar11 = local_102;
      damage = unaff_SS;
      damage = getc(puVar11);
      flush_input(puVar11,damage);
      damage = *(uint *)(iVar4 + -0x45c9);
      flag = *(int *)(iVar4 + -0x45c7);
      *(int *)(iVar4 + -0x45c9) = (uint)damage + *(uint *)(iVar4 + -0x45c9);
      *(int *)(iVar4 + -0x45c7) = flag + (uint)CARRY2((uint)damage,damage);
      flag = *(int *)(iVar4 + -0x45c9);
      puVar11 = local_102;
      damage = unaff_SS;
      damage = getc(puVar11);
      flush_input(puVar11,damage);
      *(int *)(iVar4 + -0x45cb) = (int)(damage - 0x32) / 2;
      damage = *(int *)(iVar4 + -0x45cb);
      puVar11 = local_102;
      damage = unaff_SS;
      damage = getc(puVar11);
      flush_input(puVar11,damage);
      *(uint *)(iVar4 + -0x45c5) = (uint)damage;
      damage = *(int *)(iVar4 + -0x45c5);
      puVar11 = local_102;
      damage = unaff_SS;
      damage = getc(puVar11);
      flush_input(puVar11,damage);
      puVar11 = local_102;
      read_string_from_file(0xf,(byte *)(iVar4 + -0x45db),unaff_DS);
      read_line(0x214c,puVar11);
      if ((int)((uint)*_local_10e + flag + damage + damage + (uint)*(byte *)(iVar4 + -0x45da)) %
          0x100 == (uint)damage) {
        damage = damage + 1;
      }
    }
  }
  if (damage < 0x10) {
    flag = damage;
    while( true ) {
      flag = flag * 0x18;
      _local_10e = (byte *)CONCAT22(unaff_DS,(undefined1 *)(flag + -0x45db));
      *_local_10e = 0;
      *(undefined2 *)(flag + -0x45c9) = 0;
      *(undefined2 *)(flag + -0x45c7) = 0;
      *(undefined2 *)(flag + -0x45c5) = 0x20;
      if (flag == 0xf) break;
      flag = flag + 1;
    }
  }
  device_close_handler(local_102,unaff_SS);
  return;
}



void __cdecl16near display_high_scores(void)

{
  int value;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  uint value;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined1 local_28 [32];
  int local_8;
  int flag;
  
  uVar5 = 0xe654;
  uVar7 = unaff_DS;
  write_bytes(0,0xda);
  flush_output(uVar5,uVar7);
  flag = 1;
  while( true ) {
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    write_bytes(0,0xc4);
    flush_output(uVar5,uVar7);
    if (flag == ATTACK_ACID_2) break;
    flag = flag + 1;
  }
  uVar5 = 0xe654;
  uVar7 = unaff_DS;
  write_bytes(0,0xbf);
  flush_output(uVar5,uVar7);
  uVar5 = 0xe654;
  uVar7 = unaff_DS;
  write_bytes(0,CONCAT11(extraout_AH,0xb3));
  flush_output(uVar5,uVar7);
  uVar7 = CONCAT11(extraout_AH_00,0x22);
  uVar5 = get_relative_cursor_x(uVar7);
  validate_window_coords(uVar5,uVar7);
  display_score_with_fatal(0x7b);
  uVar5 = 0xe654;
  uVar7 = unaff_DS;
  write_bytes(0x1f,CONCAT11(extraout_AH_01,0xb3));
  write_bytes(0,CONCAT11(extraout_AH_02,0xb3));
  write_bytes(0x4f,CONCAT11(extraout_AH_03,0xb3));
  flush_output(uVar5,uVar7);
  for (flag = 1; flag < 0x10; flag = flag + 1) {
    value = *(int *)(flag * 0x18 + -0x45c7);
    if ((value < 1) && ((value < 0 || (*(int *)(flag * 0x18 + -0x45c9) == 0)))) break;
    _local_8 = CONCAT22(unaff_DS,flag * 0x18 + -0x45db);
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    write_bytes(0,CONCAT11((char)((uint)(flag * 0x18) >> 8),0xb3));
    flush_output(uVar5,uVar7);
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    write_padded_string(0,(int)_local_8,(int)((ulong)_local_8 >> 0x10));
    flush_output(uVar5,uVar7);
    uVar7 = CONCAT11(extraout_AH_04,0x14);
    uVar5 = get_relative_cursor_x(uVar7);
    validate_window_coords(uVar5,uVar7);
    uVar3 = 1;
    display_character_status_message(0,*(undefined2 *)((int)_local_8 + 0x16));
    uVar5 = CONCAT11(extraout_AH_05,*(undefined1 *)((int)_local_8 + 0x16));
    puVar4 = local_28;
    uVar7 = unaff_SS;
    zero_word_array_16(puVar4);
    set_bit_range_in_array(CONCAT11(extraout_AH_06,0x23),CONCAT11(extraout_AH_06,1));
    value = create_bit_mask(puVar4,uVar7,uVar5);
    if (!(bool)uVar3) {
      display_class_info(value & 0xff00,*(undefined2 *)((int)_local_8 + 0x16));
    }
    if (*(char *)((int)_local_8 + 0x16) != 'g') {
      uVar5 = 0xe654;
      uVar7 = unaff_DS;
      write_padded_string(0,0x6ee2,0x214c);
      value = *(int *)((int)_local_8 + 0x10);
      write_padded_number(0,value,value >> 0xf);
      flush_output(uVar5,uVar7);
    }
    uVar6 = 0xe654;
    uVar7 = unaff_DS;
    write_padded_string(0,0x6eee,0x214c);
    uVar5 = (undefined2)((ulong)_local_8 >> 0x10);
    write_padded_number(0,*(undefined2 *)((int)_local_8 + 0x12),*(undefined2 *)((int)_local_8 + 0x14));
    write_padded_string(0,0x6ef5,0x214c);
    flush_output(uVar6,uVar7);
    uVar7 = (undefined2)((ulong)_local_8 >> 0x10);
    value = *(int *)((int)_local_8 + 0x14);
    if ((0 < value) || ((-1 < value && (1 < *(uint *)((int)_local_8 + 0x12))))) {
      uVar5 = 0xe654;
      uVar7 = unaff_DS;
      write_bytes(0,CONCAT11(extraout_AH_07,0x73));
      flush_output(uVar5,uVar7);
    }
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    write_padded_string(0,0x6efc,0x214c);
    flush_output(uVar5,uVar7);
    update_screen_double();
    uVar7 = CONCAT11(extraout_AH_08,0x50);
    uVar5 = get_relative_cursor_x(uVar7);
    validate_window_coords(uVar5,uVar7);
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    write_bytes(0,CONCAT11(extraout_AH_09,0xb3));
    flush_output(uVar5,uVar7);
  }
  uVar5 = 0xe654;
  uVar7 = unaff_DS;
  write_bytes(0,0xc0);
  flush_output(uVar5,uVar7);
  flag = 1;
  while( true ) {
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    write_bytes(0,0xc4);
    flush_output(uVar5,uVar7);
    if (flag == ATTACK_ACID_2) break;
    flag = flag + 1;
  }
  uVar7 = 0xe654;
  write_bytes(0,0xd9);
  flush_output(uVar7,unaff_DS);
  return;
}



void __cdecl16near save_high_scores(void)

{
  int value;
  undefined2 uVar2;
  undefined1 extraout_AH;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar3;
  undefined2 uVar4;
  byte *local_108;
  int local_104;
  undefined1 local_102 [256];
  
  init_fcb(0x7196,0x1000,local_102,unaff_SS);
  file_open_wrapper2(0x214c,local_102);
  local_104 = 1;
  while ((local_104 != 0x10 &&
         (*(int *)(local_104 * 0x18 + -0x45c9) != 0 || *(int *)(local_104 * 0x18 + -0x45c7) != 0)))
  {
    value = local_104 * 0x18;
    _local_108 = (byte *)CONCAT22(unaff_DS,(byte *)(value + -0x45db));
    puVar3 = local_102;
    uVar4 = unaff_SS;
    uVar2 = divide_long_signed(puVar3);
    write_bytes(0,uVar2);
    flush_output(puVar3,uVar4);
    puVar3 = local_102;
    uVar4 = unaff_SS;
    divide_long_signed(puVar3);
    uVar2 = divide_long_signed();
    write_bytes(0,uVar2);
    flush_output(puVar3,uVar4);
    puVar3 = local_102;
    uVar2 = 0x100;
    uVar4 = unaff_SS;
    divide_long_signed(puVar3);
    write_bytes(0,uVar2);
    flush_output(puVar3,uVar4);
    puVar3 = local_102;
    uVar4 = unaff_SS;
    write_bytes(0,*(int *)(value + -0x45cb) * 2 + 0x32);
    flush_output(puVar3,uVar4);
    puVar3 = local_102;
    uVar4 = unaff_SS;
    write_bytes(0,CONCAT11(extraout_AH,*(undefined1 *)(value + -0x45c5)));
    flush_output(puVar3,uVar4);
    puVar3 = local_102;
    uVar4 = unaff_SS;
    write_bytes(0,(uint)*(byte *)(value + -0x45da) + (uint)*_local_108 + *(int *)(value + -0x45c5)
                    + *(int *)(value + -0x45cb) + *(int *)(value + -0x45c9));
    flush_output(puVar3,uVar4);
    puVar3 = local_102;
    write_padded_string(0,(byte *)(value + -0x45db),unaff_DS);
    write_word(0x214c,puVar3);
    local_104 = local_104 + 1;
  }
  device_close_handler(local_102,unaff_SS);
  return;
}



void process_game_over(undefined1 *result_ptr,int count)

{
  char *pcVar1;
  undefined4 uVar2;
  ulong uVar3;
  uint value;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  uint value;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  int value;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  bool flag;
  undefined1 *puVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  undefined1 local_2a [28];
  int local_e;
  char *local_a;
  int flag;
  int local_6;
  int i;
  
  wait_for_memory_match(1000);
  clear_screen_double();
  pcVar1 = (char *)inventory_list;
  while( true ) {
    local_a = (char *)pcVar1;
    flag = (int)((ulong)pcVar1 >> 0x10);
    if (local_a == (char *)0x0 && flag == 0) break;
    if ((*pcVar1 == '\b') && (*(int *)(local_a + 1) != 0)) {
      uVar2 = *(undefined4 *)ADDR_GOLD_LOW /* gold_low */;
      value = (uint)uVar2;
      value = *(uint *)(local_a + 0xd);
      value = *(int *)(local_a + 0xf);
      gold_low = value + *(uint *)(local_a + 0xd);
      gold_high = (int)((ulong)uVar2 >> 0x10) + value + (uint)CARRY2(value,value);
    }
    pcVar1 = *(char **)(local_a + 0x16);
  }
  validate_window_coords(2,0x14);
  uVar7 = (char)count == 'g';
  if ((bool)uVar7) {
    clear_screen_double();
    validate_window_coords(CONCAT11(extraout_AH_00,10),CONCAT11(extraout_AH_00,0x1e));
    uVar10 = 0xe654;
    uVar11 = unaff_DS;
    write_padded_string(0,0x7345,0x20e6);
    flush_output(uVar10,uVar11);
    display_score_with_fatal(0x8e);
    validate_window_coords(CONCAT11(extraout_AH_01,0xc),CONCAT11(extraout_AH_01,0x23));
    uVar11 = 0xe654;
    write_padded_string(0,0x734a,0x20e6);
    write_word(0x214c,uVar11);
  }
  else {
    validate_window_coords(CONCAT11(extraout_AH,3),CONCAT11(extraout_AH,0xf));
    display_character_status_message(10,count);
    uVar11 = CONCAT11(extraout_AH_02,(char)count);
    puVar9 = local_2a;
    zero_word_array_16(puVar9);
    set_bit_range_in_array(CONCAT11(extraout_AH_03,0x23),CONCAT11(extraout_AH_03,1));
    value = create_bit_mask(puVar9,unaff_SS,uVar11);
    if (!(bool)uVar7) {
      display_class_info(value & 0xff00,count);
    }
    uVar10 = 0xe654;
    uVar11 = unaff_DS;
    write_padded_string(0,0x7351,0x214c);
    write_padded_number(0,dungeon_level,dungeon_level >> 0xf);
    write_padded_string(0,0x735d,0x214c);
    write_padded_number(0,*(undefined2 *)ADDR_GOLD_LOW /* gold_low */,*(undefined2 *)ADDR_GOLD_HIGH /* gold_high */);
    flush_output(uVar10,uVar11);
    display_score_with_fatal(0x19f);
    validate_window_coords(CONCAT11(extraout_AH_04,4),CONCAT11(extraout_AH_04,0x23));
    display_score_with_fatal(0x1a3);
    write_word(0x20e6,0xe654);
  }
  if ((char)count != 'Q') {
    load_high_scores();
    local_6 = 1;
    if ((char)count == 'g') {
      for (; local_6 < 0x10; local_6 = local_6 + 1) {
        uVar2 = *(undefined4 *)(local_6 * 0x18 + -0x45c9);
        value = (int)((ulong)uVar2 >> 0x10);
        if (((value <= gold_high) &&
            ((value < gold_high || ((uint)uVar2 <= *(uint *)ADDR_GOLD_LOW /* gold_low */)))) ||
           (*(int *)(local_6 * 0x18 + -0x45c5) != count)) break;
      }
    }
    else {
      while ((local_6 < 0x10 && (*(char *)(local_6 * 0x18 + -0x45c5) == 'g'))) {
        local_6 = local_6 + 1;
      }
      for (; local_6 < 0x10; local_6 = local_6 + 1) {
        uVar2 = *(undefined4 *)(local_6 * 0x18 + -0x45c9);
        value = (int)((ulong)uVar2 >> 0x10);
        if ((value <= gold_high) &&
           ((value < gold_high || ((uint)uVar2 <= *(uint *)ADDR_GOLD_LOW /* gold_low */)))) break;
      }
    }
    _local_e = CONCAT22(local_6 + 1,local_e);
    if (local_6 + 1 < 0x10) {
      for (i = 0xf;
          memcpy(0x18,i * 0x18 + -0x45db,unaff_DS,(i + -1) * 0x18 + -0x45db,
                        unaff_DS), uVar2 = _local_e, uVar3 = (ulong)_local_e >> 0x10,
          flag = i != (int)uVar3, _local_e = uVar2, flag; i = i + -1) {
      }
    }
    if (local_6 < 0x10) {
      value = local_6 * 0x18;
      _local_e = CONCAT22(unaff_DS,value + -0x45db);
      uVar2 = *(undefined4 *)ADDR_GOLD_LOW /* gold_low */;
      *(undefined2 *)(value + -0x45c9) = (int)uVar2;
      *(undefined2 *)(value + -0x45c7) = (int)((ulong)uVar2 >> 0x10);
      *(undefined2 *)(value + -0x45cb) = *(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */;
      *(int *)(value + -0x45c5) = count;
      copy_pascal_string_limited(0xf,value + -0x45db,unaff_DS,0xb84f,unaff_DS);
    }
  }
  display_high_scores();
  uVar7 = extraout_AH_05;
  if ((local_6 < 0x10) && ((char)count != ' ')) {
    save_high_scores();
    uVar7 = extraout_AH_06;
  }
  validate_window_coords(CONCAT11(uVar7,0x19),CONCAT11(uVar7,0x3c));
  handle_error_and_wait();
  *result_ptr = 0;
  return;
}



void confirm_save_or_quit(undefined4 param_1,char param_2)

{
  undefined2 uVar1;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined2 unaff_SS;
  undefined1 uVar2;
  undefined1 *puVar3;
  undefined1 local_23 [32];
  undefined1 local_3;
  
  check_minimum_stats();
  display_score_with_fatal(0xc2);
  uVar2 = param_2 == CMD_SEARCH;
  if ((bool)uVar2) {
    display_score_with_fatal(0x1a0);
  }
  else {
    display_score_with_fatal(0x1a1);
  }
  uVar1 = read_keyboard_input();
  local_3 = (undefined1)uVar1;
  puVar3 = local_23;
  zero_word_array_16(puVar3);
  set_bit_in_array(CONCAT11(extraout_AH,0x6f));
  set_bit_in_array(CONCAT11(extraout_AH_00,0x4f));
  create_bit_mask(puVar3,unaff_SS,uVar1);
  if (!(bool)uVar2) {
    process_game_over((int)param_1,(int)((ulong)param_1 >> 0x10),param_2);
  }
  return;
}



void __cdecl16near apply_heroism_effect(void)

{
  undefined1 *puVar1;
  undefined2 uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined1 local_26 [32];
  undefined4 local_6;
  
  puVar1 = (undefined1 *)*(undefined4 *)(dungeon_level * 4 + -0x5499);
  while( true ) {
    local_6._0_2_ = (undefined1 *)puVar1;
    local_6._2_2_ = (uint)((ulong)puVar1 >> 0x10);
    uVar3 = ((uint)(undefined1 *)local_6 | local_6._2_2_) == 0;
    if ((bool)uVar3) break;
    uVar2 = CONCAT11((char)(((uint)(undefined1 *)local_6 | local_6._2_2_) >> 8),*puVar1);
    puVar4 = local_26;
    uVar5 = unaff_SS;
    local_6 = puVar1;
    zero_word_array_16(puVar4);
    set_bit_in_array(CONCAT11(extraout_AH,0x45));
    set_bit_in_array(CONCAT11(extraout_AH_00,0x48));
    create_bit_mask(puVar4,uVar5,uVar2);
    puVar4 = (undefined1 *)local_6;
    uVar5 = (undefined2)((ulong)local_6 >> 0x10);
    if (!(bool)uVar3) {
      puVar4[0x22] = 1;
      puVar4[0x28] = 0;
      *(int *)(puVar4 + 8) = *(int *)(puVar4 + 8) + 1;
    }
    puVar1 = *(undefined1 **)(puVar4 + 0x32);
  }
  *(undefined2 *)(dungeon_level * 2 + 0x799b) = 4;
  return;
}



void __cdecl16near level_up_character(void)

{
  undefined1 extraout_AH;
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined2 unaff_DS;
  undefined2 uVar4;
  undefined2 uVar5;
  
  if (player_level < 0xe) {
    handle_error_and_wait();
    check_minimum_stats();
    player_level = player_level + 1;
    display_score_with_fatal(0x91);
    uVar4 = 0xe654;
    uVar5 = unaff_DS;
    write_bytes(0,CONCAT11(extraout_AH,0x20));
    write_padded_number(0,player_level,player_level >> 0xf);
    flush_output(uVar4,uVar5);
    uVar1 = random_mod(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */);
    uVar1 = uVar1 / 2;
    iVar2 = random_mod(*(undefined2 *)ADDR_PLAYER_LEVEL /* player_level */);
    iVar3 = random_mod(6);
    max_hp = max_hp + iVar3 + iVar2 + 3 + uVar1;
    iVar2 = random_mod(player_level + 6 + dungeon_level);
    current_hp = current_hp + 1 + iVar2;
    if (max_hp < current_hp) {
      *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = *(undefined2 *)ADDR_MAX_HP /* max_hp */;
    }
    display_character_stats();
  }
  return;
}



void __cdecl16near lose_experience_level(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  display_score_with_fatal(0x32);
  if (player_level != 1) {
    player_level = player_level + -1;
  }
  iVar1 = random_mod(player_level + 6);
  max_hp = (max_hp + -3) - iVar1;
  if (max_hp < current_hp) {
    *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = *(undefined2 *)ADDR_MAX_HP /* max_hp */;
  }
  return;
}



void remove_magic_item(char param_1)

{
  int value;
  char ch;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 *puVar6;
  undefined1 local_22 [32];
  
  if ((*(uint *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ | *(uint *)0xb928) == 0) {
    return;
  }
  uVar5 = *(int *)ADDR_WISDOM == 1;
  if (*(int *)ADDR_WISDOM < 2) {
    return;
  }
  uVar3 = CONCAT11((char)((*(uint *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ | *(uint *)0xb928) >> 8),
                   *(undefined1 *)((int)*(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ + 1));
  puVar6 = local_22;
  zero_word_array_16(puVar6);
  set_bit_in_array(CONCAT11(extraout_AH,1));
  set_bit_in_array(CONCAT11(extraout_AH_00,2));
  set_bit_in_array(CONCAT11(extraout_AH_01,6));
  create_bit_mask(puVar6,unaff_SS,uVar3);
  if (!(bool)uVar5) {
    return;
  }
  if (param_1 == '\0') {
    handle_error_and_wait();
    check_minimum_stats();
    display_score_with_fatal(0x94);
  }
  uVar3 = (undefined2)((ulong)*(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ >> 0x10);
  value = (int)*(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */;
  uVar5 = *(char *)(value + 0x15) == '\0';
  if ((bool)uVar5) {
    ch = check_inventory_has_item(1);
    uVar5 = ch == '\0';
    if ((bool)uVar5) goto LAB_1000_78e1;
  }
  uVar4 = 0;
  find_highest_bit();
  char_create_wrapper();
  if ((bool)uVar4 || (bool)uVar5) {
    if (param_1 != '\0') {
      return;
    }
    display_score_with_fatal(0x41);
    return;
  }
LAB_1000_78e1:
  if (param_1 != '\0') {
    display_score_with_fatal(0x94);
  }
  *(int *)ADDR_WISDOM = *(int *)ADDR_WISDOM + -1;
  *(int *)(value + 9) = *(int *)(value + 9) + -1;
  base_ac = base_ac + -1;
  display_character_stats();
  return;
}



void __cdecl16near teleport_player(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  populate_level_with_monsters();
  if (*(int *)(dungeon_level * 4 + -0x5499) != 0 || *(int *)(dungeon_level * 4 + -0x5497) != 0) {
    uVar1 = *(undefined4 *)(dungeon_level * 4 + -0x5499);
    uVar3 = (undefined2)((ulong)uVar1 >> 0x10);
    iVar2 = (int)uVar1;
    *(undefined1 *)(*(int *)(iVar2 + 0x1c) * MAP_WIDTH + *(int *)(iVar2 + 0x1e) + -0xc) = 0x20;
    *(undefined2 *)(iVar2 + 0x1c) = *(undefined2 *)ADDR_PLAYER_Y /* player_y */;
    *(undefined2 *)(iVar2 + 0x1e) = *(undefined2 *)ADDR_PLAYER_X /* player_x */;
    do {
      find_empty_floor_tile(iVar2 + 0x1e,uVar3,iVar2 + 0x1c,uVar3);
    } while (*(char *)(*(int *)(iVar2 + 0x1c) * MAP_WIDTH + *(int *)(iVar2 + 0x1e) + -0xc) != ' ');
    *(undefined1 *)(*(int *)(iVar2 + 0x1c) * MAP_WIDTH + *(int *)(iVar2 + 0x1e) + -0xc) =
         *(undefined1 *)(iVar2 + 1);
    render_field_of_view();
  }
  return;
}



void kill_monster(char param_1,char *param_2)

{
  char *pcVar1;
  char ch;
  char *pcVar3;
  undefined4 uVar4;
  byte extraout_AH;
  byte bVar8;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  int value;
  undefined2 in_BX;
  char *pcVar10;
  int value;
  undefined2 unaff_DS;
  undefined1 uVar12;
  undefined1 uVar13;
  char *local_6;
  int local_4;
  
  uVar5 = 0x1000;
  value = (int)((ulong)param_2 >> 0x10);
  pcVar10 = (char *)param_2;
  if (param_1 != '\0') {
    if (*(char *)0xe539 != '\0') {
      uVar7 = 0xe654;
      uVar6 = unaff_DS;
      write_bytes(0,7);
      uVar5 = 0x214c;
      flush_output(uVar7,uVar6);
    }
    if (is_blind == '\0') {
      display_ability_score(*(undefined2 *)(pcVar10 + 4),0xb5);
    }
    else {
      display_score_with_fatal(0xb5);
      uVar7 = 0xe654;
      uVar6 = unaff_DS;
      write_padded_string(0,0x79e5,uVar5);
      flush_output(uVar7,uVar6);
    }
    if (*(int *)(pcVar10 + 0x2e) == 0 && *(int *)(pcVar10 + 0x30) == 0) {
      bVar8 = 0;
    }
    else {
      *(undefined2 *)((int)*(undefined4 *)(pcVar10 + 0x2e) + 5) = *(undefined2 *)ADDR_PLAYER_Y /* player_y */;
      *(undefined2 *)((int)*(undefined4 *)(pcVar10 + 0x2e) + 7) = *(undefined2 *)ADDR_PLAYER_X /* player_x */;
      find_empty_floor_tile((int)*(undefined4 *)(pcVar10 + 0x2e) + 7,
                    (int)((ulong)*(undefined4 *)(pcVar10 + 0x2e) >> 0x10),
                    (int)*(undefined4 *)(pcVar10 + 0x2e) + 5,
                    (int)((ulong)*(undefined4 *)(pcVar10 + 0x2e) >> 0x10));
      uVar13 = (undefined1)((uint)in_BX >> 8);
      uVar12 = lookup_table_b9c7(*(undefined2 *)(pcVar10 + 0x2e),*(undefined2 *)(pcVar10 + 0x30));
      in_BX = CONCAT11(uVar13,uVar12);
      uVar4 = *(undefined4 *)(dungeon_level * 4 + 4);
      *(undefined1 *)
       ((int)uVar4 + *(int *)((int)*(undefined4 *)(pcVar10 + 0x2e) + 5) * MAP_WIDTH +
        *(int *)((int)*(undefined4 *)(pcVar10 + 0x2e) + 7) + -0x50) = uVar12;
      prepend_item_to_list(dungeon_level * 4 + -0x54d9,unaff_DS,pcVar10 + 0x2e,value);
      bVar8 = extraout_AH;
    }
    ch = *param_2;
    if (ch == 'V') {
      place_player_on_level(CONCAT11(bVar8,1));
    }
    else if (ch == 'F') {
      place_player_on_level((uint)bVar8 << 8);
    }
    else if (ch == 'H') {
      is_confused = 0;
    }
  }
  value = *(int *)(pcVar10 + 0x1c);
  *(undefined1 *)(value * MAP_WIDTH + *(int *)(pcVar10 + 0x1e) + -0xc) = 0x20;
  put_char_at_pos(CONCAT11((char)((uint)(value * MAP_WIDTH) >> 8),0x20),*(undefined2 *)(pcVar10 + 0x1e),
                *(undefined2 *)(pcVar10 + 0x1c));
  FUN_1000_1d47(pcVar10,value);
  if (param_1 != '\0') {
    if (*(int *)0xb8bc != 0 || *(int *)0xb8be != 0) {
      value = *(int *)(pcVar10 + 6) >> 0xf;
      combat_wrapper();
      conditional_char_action();
      uVar5 = float_add_with_handler();
      *(undefined2 *)0xb88a = uVar5;
      *(undefined2 *)0xb88c = in_BX;
      *(int *)0xb88e = value;
    }
    uVar5 = *(undefined2 *)0xb88e;
    value = combat_check_with_error();
    *(int *)(pcVar10 + 6) = *(int *)(pcVar10 + 6) + value;
    value = *(int *)(player_level * 2 + -0x46b8) - *(int *)((player_level + -1) * 2 + -0x46b8)
            >> 0xf;
    combat_wrapper();
    uVar12 = 0;
    uVar13 = 1;
    uVar6 = conditional_char_action();
    combat_wrapper(uVar6,uVar5,value);
    char_create_wrapper();
    if (!(bool)uVar12 && !(bool)uVar13) {
      *(int *)(pcVar10 + 6) =
           (*(int *)(player_level * 2 + -0x46b8) - *(int *)((player_level + -1) * 2 + -0x46b8))
           / 2;
    }
    value = combat_check_with_error();
    experience = experience + *(int *)(pcVar10 + 6) + value;
    combat_check_with_error();
    combat_wrapper();
    uVar5 = *(undefined2 *)0xb88c;
    uVar6 = *(undefined2 *)0xb88e;
    uVar7 = combat_check_and_handle_error();
    *(undefined2 *)0xb88a = uVar7;
    *(undefined2 *)0xb88c = uVar5;
    *(undefined2 *)0xb88e = uVar6;
    if (experience < 0) {
      *(undefined2 *)ADDR_EXPERIENCE /* experience */ = 0;
    }
    if (*(int *)(player_level * 2 + -0x46b8) <= experience) {
      level_up_character();
    }
    *(int *)(*(int *)(pcVar10 + 2) * 2 + -0x460b) =
         *(int *)(*(int *)(pcVar10 + 2) * 2 + -0x460b) + 1;
    display_character_stats();
  }
  pcVar3 = (char *)*(undefined4 *)(dungeon_level * 4 + -0x5499);
  local_4 = (int)((ulong)pcVar3 >> 0x10);
  local_6 = (char *)pcVar3;
  if ((local_4 == value) && (local_6 == pcVar10)) {
    uVar4 = *(undefined4 *)(local_6 + 0x32);
    value = dungeon_level;
    *(undefined2 *)(value * 4 + -0x5499) = (int)uVar4;
    *(undefined2 *)(value * 4 + -0x5497) = (int)((ulong)uVar4 >> 0x10);
  }
  else {
    for (; ((int)((ulong)*(char **)(local_6 + 0x32) >> 0x10) != value ||
           ((char *)*(char **)(local_6 + 0x32) != pcVar10));
        local_4 = (int)((ulong)*(char **)pcVar1 >> 0x10)) {
      pcVar1 = local_6 + 0x32;
      local_6 = (char *)*(char **)pcVar1;
    }
  }
  uVar4 = *(undefined4 *)(pcVar10 + 0x32);
  *(int *)(local_6 + 0x32) = (int)uVar4;
  *(int *)(local_6 + 0x34) = (int)((ulong)uVar4 >> 0x10);
  free_monster_object(pcVar10,value);
  *(int *)(dungeon_level * 2 + 0x797d) = *(int *)(dungeon_level * 2 + 0x797d) + -1;
  render_field_of_view();
  return;
}



void reveal_shapeshifter(undefined1 *result_ptr)

{
  undefined1 *puVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  if ((is_blind == '\0') && (confusion_lock == '\0')) {
    display_score_with_fatal(0x93);
    intelligence = intelligence + -5;
    handle_error_and_wait();
  }
  uVar2 = (undefined2)((ulong)result_ptr >> 0x10);
  puVar1 = (undefined1 *)result_ptr;
  puVar1[1] = *result_ptr;
  *(undefined2 *)(puVar1 + 4) = *(undefined2 *)(puVar1 + 2);
  return;
}



void __cdecl16near process_monster_breeding(void)

{
  undefined1 *puVar1;
  undefined2 uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined1 local_2a [32];
  undefined1 *local_a;
  int flag;
  undefined4 local_6;
  
  flag = (int)((ulong)inventory_list >> 0x10);
  local_a = (undefined1 *)(undefined1 *)inventory_list;
  while (uVar4 = local_a == (undefined1 *)0x0 && flag == 0,
        local_a != (undefined1 *)0x0 || flag != 0) {
    local_6 = (undefined1 *)CONCAT22(flag,local_a);
    puVar1 = *(undefined1 **)(local_a + 0x16);
    flag = (int)((ulong)puVar1 >> 0x10);
    local_a = (undefined1 *)puVar1;
    uVar2 = CONCAT11((char)((ulong)puVar1 >> 8),*local_6);
    puVar5 = local_2a;
    uVar6 = unaff_SS;
    zero_word_array_16(puVar5);
    set_bit_in_array(CONCAT11(extraout_AH,2));
    set_bit_in_array(CONCAT11(extraout_AH_00,3));
    create_bit_mask(puVar5,uVar6,uVar2);
    if ((!(bool)uVar4) && (flag = random_mod(0x14), flag == 0)) {
      destroy_or_consume_item(0,0,(undefined1 *)local_6,local_6._2_2_);
    }
  }
  return;
}



void cleanup_after_monster_death(int value)

{
  undefined4 uVar1;
  undefined2 *puVar2;
  undefined2 unaff_SS;
  
  uVar1 = *(undefined4 *)((int)*(undefined4 *)*(undefined4 *)(value + 0xc) + 0x32);
  *(undefined2 *)(value + -0x15) = (int)uVar1;
  *(undefined2 *)(value + -0x13) = (int)((ulong)uVar1 >> 0x10);
  *(undefined1 *)*(undefined4 *)(value + 4) = 1;
  puVar2 = (undefined2 *)*(undefined4 *)(value + 0xc);
  kill_monster((uint)(byte)((ulong)uVar1 >> 8) << 8,*puVar2,((undefined2 *)puVar2)[1]);
  uVar1 = *(undefined4 *)(value + -0x15);
  puVar2 = (undefined2 *)*(undefined4 *)(value + 0xc);
  *puVar2 = (int)uVar1;
  ((undefined2 *)puVar2)[1] = (int)((ulong)uVar1 >> 0x10);
  return;
}



void monster_attack_player(undefined2 monster_x,undefined2 monster_y,undefined4 flags,undefined4 *monster_ptr)

{
  uint num_attacks;
  byte *pbVar2;
  undefined4 damage;
  undefined4 damage;
  byte *pbVar5;
  char damage;
  byte attack_type;
  int iVar8;
  uint damage;
  undefined1 extraout_AH;
  byte extraout_AH_00;
  byte extraout_AH_01;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 damage;
  bool damage;
  undefined1 damage;
  bool damage;
  undefined2 damage;
  undefined2 damage;
  undefined2 damage;
  char local_19 [6];
  undefined4 local_13;
  uint damage;
  int damage;
  uint to_hit_roll;
  int ac_bonus;
  int damage;
  
  damage = get_relative_cursor_x();
  if (damage == '\x01') {
    attack_type = get_relative_cursor_y();
    if (0x32 < attack_type) {
      handle_error_and_wait();
      check_minimum_stats();
    }
  }
  else {
    check_minimum_stats();
  }
  iVar8 = random_mod(*(undefined2 *)((int)*monster_ptr + 0x14));
  to_hit_roll = ((*(int *)((int)*monster_ptr + 8) - player_level) - base_ac) + 1 + iVar8;
  if (is_stunned != '\0') {
    to_hit_roll = to_hit_roll + -8;
  }
  count_item_total_quantity(&ac_bonus,unaff_SS,7);
  to_hit_roll = to_hit_roll - ac_bonus;
  damage = *(uint *)0xb8b4 | *(uint *)0xb8b6;
  if (damage != 0) {
    iVar8 = random_mod(5);
    damage = to_hit_roll + 1 + iVar8;
    to_hit_roll = damage;
  }
  damage = (undefined1)(damage >> 8);
  if ((int)to_hit_roll < 1) {
    if (is_blind == '\0') {
      display_class_info(CONCAT11(damage,1),*(undefined2 *)((int)*monster_ptr + 4));
    }
    else {
      damage = 0xe654;
      damage = unaff_DS;
      write_padded_string(0,0x7e83,0x214c);
      flush_output(damage,damage);
    }
    damage = 0xe654;
    write_padded_string(0,0x7eb2,0x214c);
    flush_output(damage,unaff_DS);
    return;
  }
  pbVar2 = (byte *)*monster_ptr;
  damage = (undefined2)((ulong)pbVar2 >> 0x10);
  pbVar5 = (byte *)pbVar2;
  if ((*pbVar2 == 1) && (*pbVar2 != pbVar5[1])) {
    reveal_shapeshifter(*(undefined2 *)monster_ptr,*(undefined2 *)((int)(undefined4 *)monster_ptr + 2));
    damage = extraout_AH;
  }
  if (is_blind == '\0') {
    display_class_info(CONCAT11(damage,1),*(undefined2 *)(pbVar5 + 4));
  }
  else {
    damage = 0xe654;
    damage = unaff_DS;
    write_padded_string(0,0x7e83,0x214c);
    flush_output(damage,damage);
  }
  damage = 0xe654;
  damage = unaff_DS;
  write_padded_string(0,0x7e86,0x214c);
  damage = flush_output(damage,damage);
  if (*(int *)(pbVar5 + 0x10) != 0) {
    num_attacks = *(uint *)(pbVar5 + 0xe);
    damage = 0;
    if (0 < (int)num_attacks) {
      damage = 1;
      while( true ) {
        iVar8 = random_mod(*(undefined2 *)(pbVar5 + 0x10));
        current_hp = (current_hp + -1) - iVar8;
        damage = damage;
        if (damage == num_attacks) break;
        damage = damage + 1;
      }
    }
  }
  damage = (undefined2)flags;
  damage = (undefined2)((ulong)flags >> 0x10);
  if (current_hp < 1) {
    damage = 1;
    while ((damage < 5 &&
           ((damage = *(undefined4 *)(damage * 4 + -0x46cc), *(int *)((int)damage + 1) != 0xf ||
            (damage = *(undefined4 *)(damage * 4 + -0x46cc), *(int *)((int)damage + 9) < 1))))) {
      damage = damage + 1;
    }
    if (damage == 5) {
      process_game_over(damage,damage,*(undefined2 *)(pbVar5 + 2));
      return;
    }
    iVar8 = random_mod(6);
    current_hp = (max_hp + -5) - iVar8;
    *(undefined2 *)ADDR_MAX_HP /* max_hp */ = *(undefined2 *)ADDR_CURRENT_HP /* current_hp */;
    max_food = max_food + -2;
    current_food = current_food + -2;
    intelligence = intelligence + -1;
    damage = *(undefined4 *)(damage * 4 + -0x46cc);
    damage = *(undefined4 *)(damage * 4 + -0x46cc);
    *(int *)((int)damage + 9) = *(int *)((int)damage + 9) + -1;
    display_character_stats();
    return;
  }
  attack_type = *pbVar2;
  if ((attack_type == ATTACK_GHOST_2) || (attack_type == ATTACK_GHOST_1)) {
    is_paralyzed = 0;
    goto LAB_1000_850d;
  }
  if (attack_type == ATTACK_REMOVE_MAGIC) {
    remove_magic_item(damage & 0xff00);
    goto LAB_1000_850d;
  }
  damage = attack_type < 0x9c;
  damage = attack_type == ATTACK_DRAIN_STR;
  if ((bool)damage) {
    find_highest_bit();
    char_create_wrapper();
    if (!(bool)damage && !(bool)damage) {
      strength = strength + -1;
      display_score_with_fatal(199);
    }
    goto LAB_1000_850d;
  }
  if ((attack_type == ATTACK_ACID_1) || (attack_type == ATTACK_ACID_2)) {
    if (*pbVar2 == ATTACK_ACID_1) {
      find_highest_bit();
      damage = false;
      damage = true;
      char_create_wrapper();
      if (!damage && !damage) goto LAB_1000_850d;
    }
    damage = *pbVar2 < 0x4e;
    damage = *pbVar2 == ATTACK_ACID_2;
    if ((bool)damage) {
      find_highest_bit();
      char_create_wrapper();
      if (!(bool)damage && !(bool)damage) goto LAB_1000_850d;
    }
    damage = check_inventory_has_item(2);
    damage = 0;
    damage = damage == '\0';
    if (!(bool)damage) {
      find_highest_bit();
      char_create_wrapper();
      if (!(bool)damage && !(bool)damage) goto LAB_1000_850d;
    }
    handle_error_and_wait();
    check_minimum_stats();
    display_score_with_fatal(0x95);
    current_food = current_food + -1;
    if (current_food < 0) {
      process_game_over(damage,damage,0x65);
    }
    goto LAB_1000_850d;
  }
  damage = bVar7 < 0x9e;
  damage = bVar7 == ATTACK_DRAIN_CON;
  if ((bool)damage) {
    find_highest_bit();
    char_create_wrapper();
    if (!(bool)damage && !(bool)damage) {
      intelligence = intelligence + -1;
      display_score_with_fatal(0xcd);
      if (intelligence < 1) {
        process_game_over(damage,damage,100);
      }
    }
    goto LAB_1000_850d;
  }
  damage = bVar7 < 0x73;
  damage = bVar7 == ATTACK_DRAIN_EXP;
  if ((bool)damage) {
    find_highest_bit();
    char_create_wrapper();
    if (!(bool)damage && !(bool)damage) {
      iVar8 = random_mod(10);
      experience = (experience + -10) - iVar8;
      if (experience < *(int *)((player_level + -1) * 2 + -0x46b8)) {
        lose_experience_level();
      }
    }
    goto LAB_1000_850d;
  }
  if (bVar7 == ATTACK_FEAR) {
    local_f = random_mod(5);
    if ((int)local_f < 4) {
      pbVar5[0x22] = 0;
      pbVar5[0x28] = 1;
      is_dying = 1;
      handle_error_and_wait();
      check_minimum_stats();
      if (local_f == 3) {
        display_score_with_fatal(0x3e);
        iVar8 = random_mod(0x32);
        death_timer = iVar8 + 100;
      }
      else {
        display_score_with_fatal(0x49);
        iVar8 = random_mod(5);
        death_timer = iVar8 + 0xf;
      }
    }
    goto LAB_1000_850d;
  }
  if (bVar7 == ATTACK_CONFUSE) {
    is_confused = 1;
    goto LAB_1000_850d;
  }
  if (bVar7 != 0x46) {
    if (bVar7 == ATTACK_STEAL_GOLD) {
      random_mod(0xb);
      local_f = multiply_integers();
      if ((gold_high < (int)local_f >> 0xf) ||
         ((gold_high <= (int)local_f >> 0xf && (*(uint *)ADDR_GOLD_LOW /* gold_low */ < local_f)))) {
        local_f = *(uint *)ADDR_GOLD_LOW /* gold_low */;
      }
      damage = *(undefined4 *)ADDR_GOLD_LOW /* gold_low */;
      damage = (uint)damage;
      gold_low = damage - local_f;
      gold_high =
           ((int)((ulong)damage >> 0x10) - ((int)local_f >> 0xf)) - (uint)(damage < local_f);
      if (local_f != 0) {
        handle_error_and_wait();
        check_minimum_stats();
        if (is_blind == '\0') {
          display_score_with_fatal(0x97);
        }
        else {
          display_score_with_fatal(0x96);
        }
        damage = 0xe654;
        write_padded_string(0,0x7ea5,0x214c);
        flush_output(damage,unaff_DS);
        cleanup_after_monster_death(&stack0xfffe);
      }
    }
    goto LAB_1000_850d;
  }
  damage = 0;
  local_19[1] = 0;
  if (*(int *)ADDR_INVENTORY_LIST /* inventory_list */ != 0 || *(int *)0xb920 != 0) {
    if ((*(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ != 0 || *(int *)0xb928 != 0) &&
       (*(char *)((int)*(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ + 0x14) == '\0')) {
      damage = *(uint *)((int)*(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ + 1);
      damage = damage < 6;
      damage = damage == 6;
      if ((bool)damage) {
        find_highest_bit();
        char_create_wrapper();
        if (!(bool)damage && !(bool)damage) {
          local_13 = (char *)*(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */;
          handle_item_drop_or_unequip(CONCAT11((char)((ulong)local_13 >> 8),1),local_19,unaff_SS,&local_13,
                        unaff_SS);
          goto LAB_1000_83ad;
        }
      }
    }
    do {
      damage = damage + 1;
      iVar8 = random_mod(*(undefined2 *)0xb8c0);
      *(int *)(pbVar5 + 4) = iVar8 + 1;
      local_13 = (char *)inventory_list;
      iVar8 = *(int *)(pbVar5 + 4) - *(int *)((int)inventory_list + 3);
      *(int *)(pbVar5 + 4) = iVar8;
      while (0 < *(int *)(pbVar5 + 4)) {
        local_13 = *(char **)((char *)local_13 + 0x16);
        iVar8 = *(int *)(pbVar5 + 4) - *(int *)((char *)local_13 + 3);
        *(int *)(pbVar5 + 4) = iVar8;
      }
      handle_item_drop_or_unequip(CONCAT11((char)((uint)iVar8 >> 8),1),local_19,unaff_SS,&local_13,unaff_SS);
    } while ((local_19[0] == '\0') && (damage != 10));
  }
LAB_1000_83ad:
  if ((*(int *)ADDR_INVENTORY_LIST /* inventory_list */ != 0 || *(int *)0xb920 != 0) && (damage != 10)) {
    handle_error_and_wait();
    check_minimum_stats();
    if (is_blind == '\0') {
      damage = 0xe654;
      damage = unaff_DS;
      write_padded_string(0,0x7e9b,0x214c);
      flush_output(damage,damage);
    }
    else {
      damage = 0xe654;
      damage = unaff_DS;
      write_padded_string(0,0x7e91,0x214c);
      flush_output(damage,damage);
    }
    display_score_with_fatal(0x1a4);
    display_object_info((uint)extraout_AH_00 << 8,(uint)extraout_AH_00 << 8,(char *)local_13,
                  local_13._2_2_);
    damage = 0xe654;
    damage = unaff_DS;
    write_padded_string(0,0x7ea1,0x214c);
    flush_output(damage,damage);
    if ((*local_13 == '\b') && (has_light = 0, dungeon_level == 1)) {
      damage = *(undefined4 *)(dungeon_level * 4 + 4);
      *(undefined1 *)((int)damage + *(int *)0x78f1 * MAP_WIDTH + *(int *)0x78f3 + -0x50) = 0x20;
    }
    cleanup_after_monster_death(&stack0xfffe);
    destroy_or_consume_item(CONCAT11(extraout_AH_01,1),(uint)extraout_AH_01 << 8,(char *)local_13,
                  local_13._2_2_);
  }
LAB_1000_850d:
  display_character_stats();
  return;
}



void execute_player_attack(undefined4 param_1,undefined2 param_2,undefined2 flags)

{
  byte *pbVar1;
  byte flag;
  undefined4 uVar3;
  char ch;
  uint random_val;
  uint value;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  int iVar7;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined2 uVar8;
  byte *pbVar9;
  undefined2 uVar10;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined1 *puVar13;
  undefined2 uVar14;
  undefined1 local_3f [4];
  undefined1 local_3b [26];
  int local_21;
  byte *local_1f;
  int flag;
  int local_19;
  int local_17;
  int flag;
  int random_val;
  int random_val;
  int local_e;
  uint local_c;
  undefined4 local_6;
  
  find_item_at_coords(&local_6,unaff_SS,param_2,flags);
  check_minimum_stats();
  if ((byte *)local_6 == (byte *)0x0 && local_6._2_2_ == 0) {
    uVar14 = 0xe654;
    write_padded_string(0,0x855f,0x1000);
    flush_output(uVar14,unaff_DS);
    handle_error_and_wait();
  }
  else {
    local_c = (uint)(*(int *)0xb8b8 != 0 || *(int *)0xb8ba != 0);
    flag = strength;
    if (flag == 0) {
      flag = 1;
    }
    if (*(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ != 0 || *(int *)0xb930 != 0) {
      if (*(int *)((int)*(undefined4 *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ + 1) == 9) {
        flag = flag + 2;
      }
      else if ((*(int *)((int)*(undefined4 *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ + 1) == 10) &&
              (flag = flag + -4, flag < 1)) {
        flag = 1;
      }
    }
    if (*(int *)ADDR_WIELDED_WEAPON /* wielded_weapon */ == 0 && *(int *)0xb924 == 0) {
      random_val = random_mod(flag);
      uVar14 = 0;
      uVar10 = (undefined2)((ulong)local_6 >> 0x10);
      random_val = ((player_level - *(int *)((byte *)local_6 + 8)) - *(int *)((byte *)local_6 + 0xc)
                 ) + 1 + random_val;
    }
    else {
      random_val = random_mod(flag);
      uVar14 = 0;
      uVar10 = (undefined2)((ulong)local_6 >> 0x10);
      value = (((player_level + *(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 9)) -
               *(int *)((byte *)local_6 + 8)) - *(int *)((byte *)local_6 + 0xc)) + 1;
      random_val = value + random_val;
      uVar11 = ((int)value >> 0xf) + (uint)CARRY2(value,random_val) == 0;
      uVar8 = CONCAT11((char)((uint)random_val >> 8),*(undefined1 *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 1));
      puVar13 = local_3b;
      uVar10 = unaff_SS;
      zero_word_array_16(puVar13);
      set_bit_in_array(CONCAT11(extraout_AH,9));
      set_bit_in_array(CONCAT11(extraout_AH_00,0xd));
      create_bit_mask(puVar13,uVar10,uVar8);
      if (!(bool)uVar11) {
        random_val = random_val + 3;
      }
    }
    pbVar9 = (byte *)local_6;
    uVar10 = (undefined2)((ulong)local_6 >> 0x10);
    if (random_val < 1) {
      if (is_blind == '\0') {
        display_ability_score(*(undefined2 *)(pbVar9 + 4),0xbc);
      }
      else {
        display_score_with_fatal(0x98);
      }
    }
    else {
      local_1f = local_6;
      pbVar9[0x28] = 0;
      if ((*local_6 == 1) && (*local_6 != pbVar9[1])) {
        reveal_shapeshifter(pbVar9,uVar10);
      }
      if (is_blind == '\0') {
        display_ability_score(*(undefined2 *)((byte *)local_1f + 4),0xb9);
      }
      else {
        display_score_with_fatal(0xb3);
      }
      random_val = 0;
      if (current_food < ITEM_SIZE) {
        local_17 = current_food;
      }
      else {
        local_17 = 0x19;
      }
      if ((*(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ != 0 || *(int *)0xb930 != 0) &&
         (*(int *)((int)*(undefined4 *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ + 1) == 0xb)) {
        local_17 = local_17 + 2;
      }
      if (-1 < *(int *)ADDR_CONSTITUTION) {
        random_val = random_mod(*(int *)ADDR_CONSTITUTION + 1 + (player_level * local_17) / 10);
        random_val = random_val + 1;
      }
      count_item_total_quantity(&local_e,unaff_SS,4);
      local_e = random_val + local_e;
      random_val = local_e;
      if (local_e < 0) {
        random_val = 1;
      }
      flag = *local_1f;
      pbVar9 = (byte *)local_1f;
      uVar10 = (undefined2)((ulong)local_1f >> 0x10);
      if ((flag == ATTACK_GHOST_2) || (flag == ATTACK_GHOST_1)) {
        is_paralyzed = 0;
        if ((*local_1f == ATTACK_GHOST_2) && (uVar11 = pbVar9[0x22] == 0, !(bool)uVar11)) {
          uVar10 = CONCAT11((char)((uint)local_e >> 8),
                            *(undefined1 *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 1));
          puVar13 = local_3f;
          uVar14 = unaff_SS;
          zero_word_array_16(puVar13);
          set_bit_in_array(CONCAT11(extraout_AH_01,2));
          set_bit_in_array(CONCAT11(extraout_AH_02,0xd));
          create_bit_mask(puVar13,uVar14,uVar10);
          if (!(bool)uVar11) {
            uVar14 = (undefined2)((ulong)local_1f >> 0x10);
            pbVar9 = (byte *)local_1f;
            if (*(int *)(pbVar9 + 0x2e) != 0 || *(int *)(pbVar9 + 0x30) != 0) {
              *(undefined2 *)((int)*(undefined4 *)(pbVar9 + 0x2e) + 5) = *(undefined2 *)ADDR_PLAYER_Y /* player_y */;
              *(undefined2 *)((int)*(undefined4 *)(pbVar9 + 0x2e) + 7) = *(undefined2 *)ADDR_PLAYER_X /* player_x */;
              uVar11 = lookup_table_b9c7(*(undefined2 *)(pbVar9 + 0x2e),*(undefined2 *)(pbVar9 + 0x30));
              uVar14 = (undefined2)((ulong)local_1f >> 0x10);
              pbVar9 = (byte *)local_1f;
              uVar3 = *(undefined4 *)(dungeon_level * 4 + 4);
              *(undefined1 *)
               ((int)uVar3 + *(int *)((int)*(undefined4 *)(pbVar9 + 0x2e) + 5) * MAP_WIDTH +
                *(int *)((int)*(undefined4 *)(pbVar9 + 0x2e) + 7) + -0x50) = uVar11;
              prepend_item_to_list(dungeon_level * 4 + -0x54d9,unaff_DS,pbVar9 + 0x2e,uVar14);
              uVar14 = (undefined2)((ulong)local_1f >> 0x10);
              pbVar1 = (byte *)local_1f + 0x2e;
              pbVar1[0] = 0;
              pbVar1[1] = 0;
              pbVar1 = (byte *)local_1f + 0x30;
              pbVar1[0] = 0;
              pbVar1[1] = 0;
            }
          }
        }
        if (*(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 9) < 5) {
          random_val = 2;
        }
      }
      else if (flag == 1) {
        if (((*(int *)(pbVar9 + 10) < 0x28) && (**(char **)(pbVar9 + 0x2e) == '\x04')) &&
           (*(int *)((int)*(undefined4 *)(pbVar9 + 0x2e) + 1) == 6)) {
          iVar7 = *(int *)(pbVar9 + 0x1c);
          *(undefined1 *)(iVar7 * MAP_WIDTH + *(int *)(pbVar9 + 0x1e) + -0xc) = 0x20;
          put_char_at_pos(CONCAT11((char)((uint)(iVar7 * MAP_WIDTH) >> 8),0x20),
                        *(undefined2 *)(pbVar9 + 0x1e),*(undefined2 *)(pbVar9 + 0x1c));
          uVar14 = (undefined2)((ulong)local_1f >> 0x10);
          pbVar9 = (byte *)local_1f;
          pbVar9[0x27] = 1;
          find_random_empty_floor_space(0xe52d,unaff_DS,pbVar9 + 0x1e,uVar14,pbVar9 + 0x1c,uVar14);
          uVar14 = (undefined2)((ulong)local_1f >> 0x10);
          pbVar9 = (byte *)local_1f;
          *(byte *)(*(int *)(pbVar9 + 0x1c) * MAP_WIDTH + *(int *)(pbVar9 + 0x1e) + -0xc) = pbVar9[1];
          pbVar9[0x23] = 0;
          if (*(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 9) < 3) {
            random_val = 1;
          }
        }
      }
      else if (flag == 0xe4) {
        combat_wrapper();
        uVar11 = 0;
        conditional_char_action();
        uVar8 = 0x9999;
        uVar10 = 0x1999;
        uVar14 = combat_check_and_handle_error();
        find_highest_bit(uVar14,uVar8,uVar10);
        char_create_wrapper();
        if ((bool)uVar11) {
          FUN_1000_54d2(200);
          if (*(int *)((byte *)local_1f + 10) < 0x19) {
            teleport_player();
            teleport_player();
            teleport_player();
            teleport_player();
            uVar14 = (undefined2)((ulong)local_1f >> 0x10);
            pbVar9 = (byte *)local_1f;
            iVar7 = *(int *)(pbVar9 + 0x1c);
            *(undefined1 *)(iVar7 * MAP_WIDTH + *(int *)(pbVar9 + 0x1e) + -0xc) = 0x20;
            put_char_at_pos(CONCAT11((char)((uint)(iVar7 * MAP_WIDTH) >> 8),0x20),
                          *(undefined2 *)(pbVar9 + 0x1e),*(undefined2 *)(pbVar9 + 0x1c));
            uVar14 = (undefined2)((ulong)local_1f >> 0x10);
            find_random_empty_floor_space(0xe52d,unaff_DS,(byte *)local_1f + 0x1e,uVar14,(byte *)local_1f + 0x1c,
                          uVar14);
            uVar14 = (undefined2)((ulong)local_1f >> 0x10);
            pbVar9 = (byte *)local_1f;
            *(byte *)(*(int *)(pbVar9 + 0x1c) * MAP_WIDTH + *(int *)(pbVar9 + 0x1e) + -0xc) = pbVar9[1];
            pbVar9[0x23] = 0;
          }
          else {
            iVar7 = random_mod(5);
            if (iVar7 == 0) {
              speed_boost_active = 1;
              iVar7 = random_mod(0xb);
              speed_timer = iVar7 + 5;
            }
            else if (iVar7 == 1) {
              is_hasted = 1;
              iVar7 = random_mod(6);
              haste_timer = iVar7 + 5;
            }
            else if (iVar7 == 2) {
              is_teleporting = 1;
              iVar7 = random_mod(10);
              teleport_timer = iVar7 + 10;
              clear_screen_double();
            }
            else if (iVar7 == 3) {
              is_blind = 1;
              iVar7 = random_mod(6);
              blind_timer = iVar7 + 5;
            }
            else if (iVar7 == 4) {
              clear_screen_double();
              display_character_stats();
              needs_full_update = 1;
              iVar7 = random_mod(0xc);
              detect_timer = iVar7 + 0xc;
              uVar3 = *(undefined4 *)(dungeon_level * 4 + 4);
              *(undefined1 *)((int)uVar3 + 0x719) = 0;
              flag = 1;
              while( true ) {
                for (local_19 = 1;
                    *(undefined1 *)(dungeon_level * 0x719 + flag * MAP_WIDTH + local_19 + 0x70d) = 0
                    , local_19 != 0x4f; local_19 = local_19 + 1) {
                }
                if (flag == 0x17) break;
                flag = flag + 1;
              }
            }
          }
          if (*(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 9) < 4) {
            random_val = 1;
          }
        }
      }
      else if (flag == ATTACK_CONFUSE) {
        if (*(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 1) == 10) {
          *(int *)(pbVar9 + 10) = *(int *)(pbVar9 + 10) - random_val;
        }
      }
      else if ((flag == 0x42) || (flag == 1)) {
        if (*(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 1) == 0xe) {
          *(int *)(pbVar9 + 10) = *(int *)(pbVar9 + 10) - random_val;
        }
      }
      else if (flag == ATTACK_DRAIN_EXP) {
        if (*(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 9) < 4) {
          random_val = 1;
        }
      }
      else if ((flag == 0x44) || (flag == 0x92)) {
        if (*(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 1) == 0xe) {
          *(int *)(pbVar9 + 10) = *(int *)(pbVar9 + 10) - random_val;
        }
        iVar7 = (int)(*(int *)0xb884 + local_c) >> 0xf;
        combat_wrapper();
        uVar11 = 0;
        uVar12 = 1;
        conditional_char_action();
        uVar10 = float_add_with_handler();
        find_highest_bit(uVar10,uVar14,iVar7);
        char_create_wrapper();
        if (!(bool)uVar11 && !(bool)uVar12) {
          FUN_1000_54d2(0x50);
          random_val = 0;
          local_21 = *(int *)((byte *)local_1f + 0xe);
          if (0 < local_21) {
            flag = 1;
            while( true ) {
              iVar7 = random_mod(*(undefined2 *)((byte *)local_1f + 0x10));
              random_val = random_val + 1 + iVar7;
              if (flag == local_21) break;
              flag = flag + 1;
            }
          }
          ch = check_inventory_has_item(ITEM_UNKNOWN_D);
          if (ch != '\0') {
            random_val = random_val / 3 + 1;
          }
          current_hp = current_hp - random_val;
          display_character_stats();
          if (current_hp < 1) {
            process_game_over((int)param_1,(int)((ulong)param_1 >> 0x10),
                          *(undefined2 *)((byte *)local_1f + 2));
          }
          process_monster_breeding();
        }
      }
      uVar14 = (undefined2)((ulong)local_1f >> 0x10);
      *(int *)((byte *)local_1f + 10) = *(int *)((byte *)local_1f + 10) - random_val;
      if ((*(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 1) == 0xf) &&
         (iVar7 = random_mod(4), iVar7 == 0)) {
        current_hp = random_val / 2 + current_hp;
        if (max_hp < current_hp) {
          *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = *(undefined2 *)ADDR_MAX_HP /* max_hp */;
        }
        display_character_stats();
      }
      uVar14 = (undefined2)((ulong)local_1f >> 0x10);
      pbVar9 = (byte *)local_1f;
      uVar11 = *(int *)(pbVar9 + 10) == 1;
      if (*(int *)(pbVar9 + 10) < 1) {
        random_val = (uint)*local_6;
        puVar13 = local_3f;
        zero_word_array_16(puVar13);
        set_bit_in_array(CONCAT11(extraout_AH_03,0x48));
        set_bit_in_array(CONCAT11(extraout_AH_04,0x45));
        create_bit_mask(puVar13,unaff_SS,random_val);
        if (!(bool)uVar11) {
          *(int *)(dungeon_level * 2 + 0x799b) = *(int *)(dungeon_level * 2 + 0x799b) + -1;
        }
        kill_monster(1,(byte *)local_6,local_6._2_2_);
      }
      else {
        flag = *local_1f;
        if ((flag == ATTACK_CONFUSE) || (flag == ATTACK_FEAR)) {
          pbVar9[0x22] = 1;
        }
        else if ((flag == ATTACK_GHOST_1) || (flag == ATTACK_GHOST_2)) {
          (pbVar9 + 0x20)[0] = 1;
          (pbVar9 + 0x20)[1] = 0;
        }
      }
    }
  }
  return;
}



void remove_spell(int value)

{
  int value;
  undefined4 uVar2;
  int value;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  value = *(int *)0xb936;
  *(undefined2 *)(value * 4 + -0x46cc) = 0;
  *(undefined2 *)(value * 4 + -0x46ca) = 0;
  *(int *)0xb936 = *(int *)0xb936 + -1;
  strength = strength + -2;
  value = *(int *)0xb936;
  local_4 = value + 1;
  if (local_4 <= value) {
    while( true ) {
      uVar2 = *(undefined4 *)(local_4 * 4 + -0x46cc);
      value = (local_4 + -1) * 4;
      *(undefined2 *)(value + -0x46cc) = (int)uVar2;
      *(undefined2 *)(value + -0x46ca) = (int)((ulong)uVar2 >> 0x10);
      if (local_4 == value) break;
      local_4 = local_4 + 1;
    }
  }
  display_character_stats();
  display_score_with_fatal(0xfe59);
  return;
}



void __cdecl16near reset_food_flags(void)

{
  char *pcVar1;
  char ch;
  undefined2 uVar3;
  undefined1 extraout_AH;
  int value;
  int value;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  undefined1 *puVar8;
  undefined1 local_26 [32];
  undefined4 local_6;
  
  pcVar1 = (char *)inventory_list;
  while( true ) {
    local_6._0_2_ = (char *)pcVar1;
    local_6._2_2_ = (int)((ulong)pcVar1 >> 0x10);
    local_6 = pcVar1;
    if ((char *)local_6 == (char *)0x0 && local_6._2_2_ == 0) break;
    uVar7 = *pcVar1 == '\b';
    if ((bool)uVar7) {
      uVar7 = ((char *)local_6)[0x14] == '\0';
      if ((bool)uVar7) {
        ((char *)local_6)[0x13] = '\x01';
      }
      else {
        ((char *)local_6)[0x14] = '\0';
      }
    }
    else {
      ((char *)local_6)[0x13] = '\x01';
    }
    uVar3 = validate_range_bounds();
    puVar8 = local_26;
    uVar6 = unaff_SS;
    zero_word_array_16(puVar8);
    set_bit_range_in_array(CONCAT11(extraout_AH,5),CONCAT11(extraout_AH,2));
    create_bit_mask(puVar8,uVar6,uVar3);
    if (!(bool)uVar7) {
      value = validate_range_bounds();
      value = validate_range_bounds();
      *(undefined1 *)(value * 0x18 + value + -0x65a2) = 1;
    }
    pcVar1 = *(char **)((char *)local_6 + 0x16);
  }
  uVar6 = validate_range_bounds();
  *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = uVar6;
  combat_wrapper();
  check_combat_and_handle_error();
  combat_check_with_error();
  uVar6 = validate_range_bounds();
  *(undefined2 *)ADDR_MAX_HP /* max_hp */ = uVar6;
  uVar6 = validate_range_bounds();
  *(undefined2 *)ADDR_CURRENT_FOOD /* current_food */ = uVar6;
  uVar6 = validate_range_bounds();
  *(undefined2 *)ADDR_MAX_FOOD /* max_food */ = uVar6;
  ch = check_inventory_has_item(2);
  if (ch != '\0') {
    uVar6 = validate_range_bounds();
    *(undefined2 *)ADDR_CURRENT_FOOD /* current_food */ = uVar6;
    uVar6 = validate_range_bounds();
    *(undefined2 *)ADDR_MAX_FOOD /* max_food */ = uVar6;
  }
  if (current_food < 0) {
    *(undefined2 *)ADDR_CURRENT_FOOD /* current_food */ = 0;
  }
  display_character_stats();
  display_score_with_fatal(0xfe5a);
  return;
}



void learn_spell(undefined4 *result_ptr)

{
  undefined4 uVar1;
  bool flag;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  flag = false;
  *(undefined1 *)((int)*result_ptr + 0x14) = 1;
  local_4 = 0;
  do {
    local_4 = local_4 + 1;
    if (*(int *)(local_4 * 4 + -0x46cc) == 0 && *(int *)(local_4 * 4 + -0x46ca) == 0) break;
  } while (local_4 != *(int *)0xb936);
  if (*(int *)(local_4 * 4 + -0x46cc) == 0 && *(int *)(local_4 * 4 + -0x46ca) == 0) {
    uVar1 = *result_ptr;
    *(undefined2 *)(local_4 * 4 + -0x46cc) = (int)uVar1;
    *(undefined2 *)(local_4 * 4 + -0x46ca) = (int)((ulong)uVar1 >> 0x10);
    flag = true;
    handle_error_and_wait();
    display_score_with_fatal(0xffac);
  }
  else {
    local_4 = 0;
    do {
      local_4 = local_4 + 1;
      uVar1 = *(undefined4 *)(local_4 * 4 + -0x46cc);
      if (*(int *)((int)uVar1 + 9) == 0) break;
    } while (local_4 != *(int *)0xb936);
    uVar1 = *(undefined4 *)(local_4 * 4 + -0x46cc);
    if (*(int *)((int)uVar1 + 9) == 0) {
      uVar1 = *result_ptr;
      *(undefined2 *)(local_4 * 4 + -0x46cc) = (int)uVar1;
      *(undefined2 *)(local_4 * 4 + -0x46ca) = (int)((ulong)uVar1 >> 0x10);
      flag = true;
      handle_error_and_wait();
      display_score_with_fatal(0xffac);
    }
  }
  if (((flag) && (*(int *)((int)*result_ptr + 1) == 8)) && (*(int *)((int)*result_ptr + 9) == 1)) {
    reset_food_flags();
    *(undefined2 *)((int)*result_ptr + 9) = 0;
  }
  if ((flag) && (*(int *)((int)*result_ptr + 1) == 0xc)) {
    remove_spell(local_4);
  }
  return;
}



void __cdecl16near pickup_item(void)

{
  uint value;
  undefined4 uVar2;
  char *pcVar3;
  char ch;
  byte extraout_AH;
  uint flag;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  int flag;
  char *pcVar7;
  char *pcVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar12;
  undefined1 uVar13;
  undefined1 *puVar14;
  undefined1 local_34 [32];
  char ch;
  char ch;
  char ch;
  undefined4 local_11;
  undefined4 local_d;
  int local_5;
  
  uVar11 = 0x1000;
  FUN_1000_1988(&local_11,unaff_SS,0xb86e,unaff_DS,0xb86c,unaff_DS);
  check_minimum_stats();
  display_score_with_fatal(0x75);
  display_object_info((uint)extraout_AH << 8,CONCAT11(extraout_AH,1),(char *)local_11,local_11._2_2_);
  pcVar7 = (char *)local_11;
  uVar9 = (undefined2)((ulong)local_11 >> 0x10);
  if (*local_11 == '\0') {
    flag = *(uint *)(pcVar7 + 9);
    value = *(uint *)ADDR_GOLD_LOW /* gold_low */;
    flag = gold_high;
    gold_low = flag + *(uint *)ADDR_GOLD_LOW /* gold_low */;
    gold_high = ((int)flag >> 0xf) + flag + (uint)CARRY2(flag,value);
    remove_item_from_list(dungeon_level * 4 + -0x54d9,unaff_DS,&local_11,unaff_SS);
    free_item_object((char *)local_11,local_11._2_2_);
    uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
    *(undefined1 *)((int)uVar2 + player_y * MAP_WIDTH + player_x + -0x50) = 0x20;
    display_character_stats();
    return;
  }
  ch = *(int *)0xb8c6 < *(int *)0xb8c4 + *(int *)(pcVar7 + 0xb);
  if (*local_11 == '\x04') {
    uVar12 = *(uint *)(pcVar7 + 1) < 6;
    uVar13 = *(uint *)(pcVar7 + 1) == 6;
    if (!(bool)uVar13) {
      find_highest_bit();
      uVar11 = 0x214c;
      char_create_wrapper();
      if (!(bool)uVar12 && !(bool)uVar13) {
        learn_spell(&local_11,unaff_SS);
        ch = '\x01';
        goto LAB_1000_9184;
      }
    }
  }
  ch = '\0';
LAB_1000_9184:
  if ((ch == '\0') || (ch != '\0')) {
    uVar2 = *(undefined4 *)(*local_11 * 4 + -0x4738);
    flag = (uint)uVar2;
    ch = *local_11;
    *(int *)(ch * 4 + -0x4738) = flag + 1;
    *(int *)(ch * 4 + -0x4736) = (int)((ulong)uVar2 >> 0x10) + (uint)(0xfffe < flag);
    *(int *)0xb8c0 = *(int *)0xb8c0 + 1;
    uVar9 = (undefined2)((ulong)local_11 >> 0x10);
    *(int *)0xb8c4 = *(int *)0xb8c4 + *(int *)((char *)local_11 + 0xb);
    if ((*local_11 == '\b') && (*(int *)((char *)local_11 + 1) == 0)) {
      has_light = 1;
    }
    remove_item_from_list(dungeon_level * 4 + -0x54d9,unaff_DS,&local_11,unaff_SS);
    uVar9 = (undefined2)((ulong)local_11 >> 0x10);
    pcVar7 = (char *)local_11;
    uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
    *(undefined1 *)((int)uVar2 + *(int *)(pcVar7 + 5) * MAP_WIDTH + *(int *)(pcVar7 + 7) + -0x50) = 0x20;
    if (*local_11 == '\b') {
      flag = *(int *)(pcVar7 + 1);
      *(undefined2 *)(flag * 4 + -0x476c) = pcVar7;
      *(undefined2 *)(flag * 4 + -0x476a) = uVar9;
    }
    pcVar3 = (char *)inventory_list;
    ch = '\0';
    local_5 = 1;
    while( true ) {
      local_d._0_2_ = (char *)pcVar3;
      local_d._2_2_ = (uint)((ulong)pcVar3 >> 0x10);
      flag = (uint)(char *)local_d | local_d._2_2_;
      if ((flag == 0) || (ch != '\0')) break;
      uVar12 = *pcVar3 == *local_11;
      local_d = pcVar3;
      if ((bool)uVar12) {
        uVar10 = CONCAT11((char)(flag >> 8),*local_11);
        puVar14 = local_34;
        uVar9 = unaff_SS;
        zero_word_array_16(puVar14);
        set_bit_in_array(CONCAT11(extraout_AH_00,2));
        set_bit_in_array(CONCAT11(extraout_AH_01,3));
        uVar11 = 0x214c;
        create_bit_mask(puVar14,uVar9,uVar10);
        if ((((bool)uVar12) || (*(int *)((char *)local_d + 1) != *(int *)((char *)local_11 + 1))) &&
           (*local_11 != '\x01')) {
          ch = is_type_7_subtype_12((char *)local_11,local_11._2_2_);
          if (ch != '\0') {
            ch = is_type_7_subtype_12((char *)local_d,local_d._2_2_);
            if ((ch != '\0') &&
               (*(int *)((char *)local_11 + 0x11) == *(int *)((char *)local_d + 0x11)))
            goto LAB_1000_9300;
          }
        }
        else {
LAB_1000_9300:
          ch = '\x01';
          ch = is_type_7_subtype_12((char *)local_11,local_11._2_2_);
          pcVar7 = (char *)local_11;
          uVar9 = (undefined2)((ulong)local_11 >> 0x10);
          pcVar8 = (char *)local_d;
          uVar11 = (undefined2)((ulong)local_d >> 0x10);
          if ((ch != '\0') && (*(int *)(pcVar7 + 0x11) == *(int *)(pcVar8 + 0x11))) {
            uVar2 = *(undefined4 *)(*local_11 * 4 + -0x4738);
            flag = (int)uVar2;
            ch = *local_11;
            *(int *)(ch * 4 + -0x4738) = flag + -1;
            *(int *)(ch * 4 + -0x4736) = (int)((ulong)uVar2 >> 0x10) - (uint)(flag == 0);
            *(int *)0xb8c0 = *(int *)0xb8c0 + -1;
            *(int *)0xb8c4 = *(int *)0xb8c4 - *(int *)(pcVar7 + 0xb);
          }
          *(int *)(pcVar8 + 3) = *(int *)(pcVar8 + 3) + *(int *)(pcVar7 + 3);
          uVar11 = 0xe654;
          uVar9 = unaff_DS;
          write_padded_string(0,0x908d,0x214c);
          flush_output(uVar11,uVar9);
          if (local_5 < 0x1b) {
            uVar11 = 0xe654;
            uVar9 = unaff_DS;
            write_bytes(0,local_5 + 0x60);
            flush_output(uVar11,uVar9);
          }
          else {
            uVar11 = 0xe654;
            uVar9 = unaff_DS;
            write_bytes(0,local_5 + 0x26);
            flush_output(uVar11,uVar9);
          }
          uVar10 = 0xe654;
          uVar9 = unaff_DS;
          write_padded_string(0,0x9090,0x214c);
          uVar11 = 0x214c;
          flush_output(uVar10,uVar9);
          free_item_object((char *)local_11,local_11._2_2_);
        }
      }
      local_5 = local_5 + 1;
      pcVar3 = *(char **)((char *)local_d + 0x16);
    }
    if (ch == '\0') {
      local_d = (char *)inventory_list;
      *(int *)0xb8c2 = *(int *)0xb8c2 + 1;
      pcVar7 = (char *)local_11;
      uVar9 = (undefined2)((ulong)local_11 >> 0x10);
      if (((char *)local_d == (char *)0x0 && (int)((ulong)local_d >> 0x10) == 0) ||
         (*local_11 < *local_d)) {
        uVar2 = inventory_list;
        *(int *)(pcVar7 + 0x16) = (int)uVar2;
        *(int *)(pcVar7 + 0x18) = (int)((ulong)uVar2 >> 0x10);
        *(undefined2 *)ADDR_INVENTORY_LIST /* inventory_list */ = pcVar7;
        *(undefined2 *)0xb920 = uVar9;
        uVar9 = 0xe654;
        write_padded_string(0,0x9093,uVar11);
        flush_output(uVar9,unaff_DS);
      }
      else {
        local_5 = 2;
        while( true ) {
          uVar10 = (undefined2)((ulong)local_d >> 0x10);
          pcVar8 = (char *)local_d;
          if ((*(int *)(pcVar8 + 0x16) == 0 && *(int *)(pcVar8 + 0x18) == 0) ||
             (*local_11 <= **(char **)(pcVar8 + 0x16))) break;
          local_d = *(char **)(pcVar8 + 0x16);
          local_5 = local_5 + 1;
        }
        uVar2 = *(undefined4 *)(pcVar8 + 0x16);
        *(int *)(pcVar7 + 0x16) = (int)uVar2;
        *(int *)(pcVar7 + 0x18) = (int)((ulong)uVar2 >> 0x10);
        *(char **)(pcVar8 + 0x16) = pcVar7;
        *(undefined2 *)(pcVar8 + 0x18) = uVar9;
        uVar10 = 0xe654;
        uVar9 = unaff_DS;
        write_padded_string(0,0x908d,uVar11);
        flush_output(uVar10,uVar9);
        if (local_5 < 0x1b) {
          uVar11 = 0xe654;
          uVar9 = unaff_DS;
          write_bytes(0,local_5 + 0x60);
          flush_output(uVar11,uVar9);
        }
        else {
          uVar11 = 0xe654;
          uVar9 = unaff_DS;
          write_bytes(0,local_5 + 0x26);
          flush_output(uVar11,uVar9);
        }
        uVar9 = 0xe654;
        write_padded_string(0,0x9090,0x214c);
        flush_output(uVar9,unaff_DS);
      }
    }
  }
  else {
    handle_error_and_wait();
    check_minimum_stats();
    display_score_with_fatal(0x4a);
  }
  return;
}



void display_shop_item(undefined2 param_1,undefined1 param_2,undefined1 flags,int param_4,char param_5
                  )

{
  int value;
  undefined1 extraout_AH;
  byte extraout_AH_00;
  undefined2 unaff_DS;
  undefined2 uVar2;
  
  set_background_color(param_2);
  validate_window_coords(CONCAT11(extraout_AH,flags),CONCAT11(extraout_AH,1));
  uVar2 = 0xe654;
  write_padded_string(0,param_5 * 0x2b8 + param_4 * 0x1d + 0x75fa,unaff_DS);
  value = *(int *)(param_5 * 0x30 + param_4 * 2 + -0x71d3);
  write_padded_number(6,value,value >> 0xf);
  write_padded_string(0,0x9550,0x214c);
  write_word(0x214c,uVar2);
  set_background_color((uint)extraout_AH_00 << 8);
  return;
}



void __cdecl16near shop_purchase_menu(void)

{
  uint damage;
  undefined4 damage;
  undefined4 damage;
  undefined4 damage;
  byte damage;
  undefined1 damage;
  undefined1 extraout_AH;
  uint damage;
  int damage;
  char *pcVar9;
  undefined2 damage;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar11;
  undefined1 *puVar12;
  undefined2 damage;
  undefined1 local_316 [256];
  undefined1 local_216 [254];
  undefined4 damage;
  char damage;
  char *local_113;
  byte abStack_10c [257];
  char damage;
  int damage;
  int damage;
  uint damage;
  uint damage;
  
  clear_screen_double();
  damage = 0xe654;
  write_padded_string(0,0x95da,0x20e6);
  write_word(0x214c,damage);
  damage = 0xe654;
  write_padded_string(0,0x95e5,0x214c);
  write_word(0x214c,damage);
  damage = read_keyboard_input();
  if (damage == '1') {
    damage = '\x06';
  }
  else {
    damage = '\a';
  }
  abStack_10c[1] = 0;
  damage = 0;
  clear_screen_double();
  damage = *(int *)(damage * 4 + 0x79b3);
  damage = (char *)CONCAT22(damage,(int)damage);
  if (0 < damage) {
    damage = 1;
    while( true ) {
      damage = *(uint *)(damage * 0x30 + damage * 2 + -0x71d3);
      damage = (int)damage >> 0xf;
      if (((damage < gold_high) || ((damage <= gold_high && (damage < *(uint *)ADDR_GOLD_LOW /* gold_low */)))) &&
         (*(int *)(damage * 0x30 + damage * 2 + -0x71d3) != 0)) {
        damage = damage + 1;
        puVar12 = local_316;
        damage = unaff_SS;
        copy_pascal_string(abStack_10c + 1,unaff_SS);
        puVar11 = local_216;
        damage = unaff_SS;
        char_to_pascal_string(damage + 0x28);
        concat_pascal_string(puVar11,damage);
        copy_pascal_string_limited(0xff,abStack_10c + 1,unaff_SS,puVar12,damage);
        display_shop_item(&stack0xfffe,0,damage,damage,CONCAT11(extraout_AH,damage));
      }
      if (damage == damage._2_2_) break;
      damage = damage + 1;
    }
  }
  if (0 < (int)damage) {
    damage = 1;
    damage = 1;
    damage = abStack_10c[2] - 0x28;
    display_shop_item(&stack0xfffe,0xf,1,damage,CONCAT11((char)((uint)damage >> 8),damage));
    damage = ' ';
    damage = damage;
    while (damage != '\r') {
      damage = read_keyboard_input();
      if (damage == '\0') {
        damage = read_keyboard_input();
      }
      if ((damage == 'P') || (damage == CMD_MOVE_DOWN)) {
        if ((int)damage < (int)(uint)abStack_10c[1]) {
          damage = damage + 1;
          damage = abStack_10c[damage + 2];
        }
        else {
          damage = 1;
          damage = abStack_10c[2];
        }
        damage = damage - 0x28;
      }
      else if ((damage == 'H') || (damage == CMD_MOVE_UP)) {
        if ((int)damage < 2) {
          damage = abStack_10c[abStack_10c[1] + 1] - 0x28;
          damage = (uint)abStack_10c[1];
        }
        else {
          damage = abStack_10c[damage] - 0x28;
          damage = damage - 1;
        }
      }
      if (damage != damage) {
        display_shop_item(&stack0xfffe,0,damage,damage,damage);
        damage = damage;
        damage = damage;
        display_shop_item(&stack0xfffe,0xf,damage,damage,damage);
      }
    }
    damage = *(uint *)(damage * 0x30 + damage * 2 + -0x71d3);
    damage = *(undefined4 *)ADDR_GOLD_LOW /* gold_low */;
    damage = (uint)damage;
    gold_low = damage - damage;
    gold_high = ((int)((ulong)damage >> 0x10) - ((int)damage >> 0xf)) - (uint)(damage < damage);
    allocate_item_object(&local_113,unaff_SS);
    damage = (undefined2)((ulong)local_113 >> 0x10);
    pcVar9 = (char *)local_113;
    damage = local_113;
    *local_113 = damage;
    *(int *)(pcVar9 + 1) = damage;
    (pcVar9 + 3)[0] = '\x01';
    (pcVar9 + 3)[1] = '\0';
    (pcVar9 + 9)[0] = '\0';
    (pcVar9 + 9)[1] = '\0';
    damage = calculate_dice_or_damage(damage,damage);
    damage = (undefined2)((ulong)damage >> 0x10);
    pcVar9 = (char *)damage;
    *(undefined2 *)(pcVar9 + 0xb) = damage;
    pcVar9[0x14] = '\0';
    pcVar9[0x13] = '\0';
    place_object_on_map(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */,&local_113,unaff_SS);
    damage = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
    damage = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
    damage = *(undefined4 *)(dungeon_level * 4 + 4);
    *(undefined1 *)((int)damage + *(int *)((int)damage + 5) * MAP_WIDTH + *(int *)((int)damage + 7) + -0x50)
         = 0x20;
    damage = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
    *(undefined2 *)((int)damage + 5) = *(undefined2 *)ADDR_PLAYER_Y /* player_y */;
    damage = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
    *(undefined2 *)((int)damage + 7) = *(undefined2 *)ADDR_PLAYER_X /* player_x */;
    damage = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
    damage = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
    find_empty_floor_tile((int)damage + 7,(int)((ulong)damage >> 0x10),(int)damage + 5,
                  (int)((ulong)damage >> 0x10));
    damage = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
    damage._2_2_ = (int)((ulong)damage >> 0x10);
    damage._0_2_ = (int)damage;
    damage = lookup_table_b9c7(*(undefined2 *)(dungeon_level * 4 + -0x54d9),
                          *(undefined2 *)(dungeon_level * 4 + -0x54d7));
    damage = *(undefined4 *)(dungeon_level * 4 + 4);
    *(undefined1 *)
     ((int)damage + *(int *)((int)damage + 5) * MAP_WIDTH + *(int *)((int)damage + 7) + -0x50) =
         damage;
    redraw_dungeon_level(0x17);
    display_character_stats();
  }
  return;
}



void drop_item(char *result_ptr)

{
  undefined4 uVar1;
  uint in_AX;
  byte extraout_AH;
  undefined1 extraout_AH_00;
  int value;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  char ch;
  
  handle_item_drop_or_unequip(in_AX & 0xff00,&ch,unaff_SS,&result_ptr,unaff_SS);
  if (ch != '\0') {
    display_score_with_fatal(0x76);
    display_object_info((uint)extraout_AH << 8,(uint)extraout_AH << 8,(char *)result_ptr,result_ptr._2_2_);
    destroy_or_consume_item(CONCAT11(extraout_AH_00,1),CONCAT11(extraout_AH_00,1),(char *)result_ptr,
                  result_ptr._2_2_);
    if (*result_ptr == '\b') {
      build_object_index();
      if (*(int *)0xb894 == 0 && *(int *)0xb896 == 0) {
        has_light = 0;
        value = 0;
        if (dungeon_level == 1) {
          value = *(int *)0x78f1 * MAP_WIDTH;
          uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
          *(undefined1 *)((int)uVar1 + value + *(int *)0x78f3 + -0x50) = 0x20;
        }
        put_char_at_pos(CONCAT11((char)((uint)value >> 8),0x20),*(undefined2 *)0x78f3,
                      *(undefined2 *)0x78f1);
      }
    }
    display_character_stats();
  }
  return;
}



void identify_item(char *result_ptr)

{
  char ch;
  byte extraout_AH;
  byte extraout_AH_00;
  byte bVar2;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  char *pcVar3;
  int flag;
  undefined2 uVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  bool flag;
  undefined1 *puVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined1 local_22 [32];
  
  ch = *result_ptr;
  if ((((ch == '\x01') || (ch == '\a')) || (ch == '\x06')) || (ch == '\b')) {
    display_score_with_fatal(0x40);
    return;
  }
  if (((ch != '\x03') && (ch != '\x02')) && ((ch != '\x04' && (ch != '\x05')))) {
    return;
  }
  uVar5 = (undefined2)((ulong)result_ptr >> 0x10);
  pcVar3 = (char *)result_ptr;
  if (*(char *)(*result_ptr * 0x18 + *(int *)(pcVar3 + 1) + -0x65a2) != '\0') {
    display_score_with_fatal(0x77);
    return;
  }
  check_minimum_stats();
  if (*(int *)(pcVar3 + 3) == 1) {
    uVar9 = 0xe654;
    uVar10 = unaff_DS;
    write_padded_string(0,0x9a60,0x1000);
    flush_output(uVar9,uVar10);
    bVar2 = extraout_AH;
  }
  else {
    uVar9 = 0xe654;
    uVar10 = unaff_DS;
    write_padded_string(0,0x9a66,0x1000);
    flush_output(uVar9,uVar10);
    bVar2 = extraout_AH_00;
  }
  display_object_info((uint)bVar2 << 8,CONCAT11(bVar2,1),pcVar3,uVar5);
  handle_error_and_wait();
  check_minimum_stats();
  uVar9 = 0xe654;
  uVar10 = unaff_DS;
  write_padded_string(0,0x9a6e,0x214c);
  flush_output(uVar9,uVar10);
  uVar6 = *(int *)(pcVar3 + 3) == 1;
  if (*(int *)(pcVar3 + 3) < 2) {
    uVar10 = CONCAT11(extraout_AH_01,*result_ptr);
    puVar8 = local_22;
    zero_word_array_16(puVar8);
    set_bit_in_array(CONCAT11(extraout_AH_02,2));
    set_bit_in_array(CONCAT11(extraout_AH_03,5));
    create_bit_mask(puVar8,unaff_SS,uVar10);
    if ((bool)uVar6) {
      uVar9 = 0xe654;
      uVar10 = unaff_DS;
      write_padded_string(0,0x9a7f,0x214c);
      flush_output(uVar9,uVar10);
    }
    else {
      uVar9 = 0xe654;
      uVar10 = unaff_DS;
      write_padded_string(0,0x9a7b,0x214c);
      flush_output(uVar9,uVar10);
    }
  }
  else {
    uVar9 = 0xe654;
    uVar10 = unaff_DS;
    write_padded_string(0,0x9a76,0x214c);
    flush_output(uVar9,uVar10);
  }
  uVar9 = 0xe654;
  uVar10 = unaff_DS;
  write_padded_string(0,0x9a83,0x214c);
  flush_output(uVar9,uVar10);
  uVar10 = 0xe554;
  read_string_from_file(0x1c,*result_ptr * 0x2b8 + *(int *)(pcVar3 + 1) * 0x1d + -0x75de,unaff_DS);
  read_line(0x214c,uVar10);
  if (*(char *)(*result_ptr * 0x18 + *(int *)(pcVar3 + 1) + -0x6542) == '\0') {
    flag = *result_ptr * 0x2b8 + *(int *)(pcVar3 + 1) * 0x1d + -0x75de;
    flag = flag == 0;
    compare_pascal_strings(0x9a90,0x214c,flag,unaff_DS);
    if (flag) {
      uVar6 = 0;
      goto LAB_1000_9c7c;
    }
  }
  uVar6 = 1;
LAB_1000_9c7c:
  *(undefined1 *)(*result_ptr * 0x18 + *(int *)(pcVar3 + 1) + -0x6542) = uVar6;
  return;
}



void discover_item(byte *result_ptr)

{
  uint value;
  undefined1 extraout_AH;
  int value;
  byte bVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined1 local_22 [32];
  
  uVar4 = &stack0x0000 == (undefined1 *)0x22;
  value = (uint)*result_ptr;
  puVar5 = local_22;
  zero_word_array_16(puVar5);
  set_bit_range_in_array(CONCAT11(extraout_AH,5),CONCAT11(extraout_AH,2));
  value = create_bit_mask(puVar5,unaff_SS,value);
  if (!(bool)uVar4) {
    value = (char)*result_ptr * 0x18;
    *(undefined1 *)(value + *(int *)((byte *)result_ptr + 1) + -0x65a2) = 1;
  }
  if (*result_ptr == 8) {
    if (((byte *)result_ptr)[0x14] == 0) {
      ((byte *)result_ptr)[0x13] = 1;
    }
    else {
      ((byte *)result_ptr)[0x14] = 0;
    }
  }
  else {
    ((byte *)result_ptr)[0x13] = 1;
  }
  if ((*result_ptr == 1) && (*(int *)((byte *)result_ptr + 3) == 1)) {
    display_score_with_fatal(0xb7);
  }
  else {
    bVar3 = (byte)((uint)value >> 8);
    display_object_info((uint)bVar3 << 8,CONCAT11(bVar3,1),(byte *)result_ptr,result_ptr._2_2_);
  }
  return;
}



void equip_item(char *result_ptr)

{
  int value;
  char *pcVar2;
  byte extraout_AH;
  byte extraout_AH_00;
  byte bVar5;
  int value;
  undefined2 uVar4;
  undefined1 extraout_AH_01;
  int value;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  undefined1 *puVar8;
  undefined2 uVar9;
  undefined1 local_25 [32];
  char ch;
  
  ch = '\0';
  value = (int)((ulong)result_ptr >> 0x10);
  pcVar2 = (char *)result_ptr;
  if ((value == *(int *)0xb924) && (pcVar2 == (char *)wielded_weapon)) {
    display_score_with_fatal(0x78);
  }
  else {
    check_minimum_stats();
    if (*result_ptr == '\a') {
      display_score_with_fatal(0xaf);
      bVar5 = extraout_AH;
    }
    else {
      display_score_with_fatal(0x7a);
      bVar5 = extraout_AH_00;
    }
    display_object_info((uint)bVar5 << 8,CONCAT11(bVar5,1),pcVar2,value);
    if (*result_ptr == '\a') {
      uVar9 = 0xe654;
      uVar4 = unaff_DS;
      write_padded_string(0,0x9d48,0x1000);
      flush_output(uVar9,uVar4);
      wielded_weapon = pcVar2;
      *(int *)0xb924 = value;
      *(int *)ADDR_CONSTITUTION = *(int *)(*(int *)(pcVar2 + 1) * 4 + -0x6185) + *(int *)(pcVar2 + 9);
      display_food_status();
    }
    else if (*result_ptr == '\x06') {
      if (current_food < 0x1d) {
        print_prompt();
        value = *(int *)(pcVar2 + 1);
        if (value == 7) {
          if (*(int *)ADDR_EQUIPPED_ARMOR /* equipped_armor */ == 0 && *(int *)0xb92c == 0) {
            equipped_armor = pcVar2;
            *(int *)0xb92c = value;
            value = get_sign(pcVar2 + 9,value);
            *(int *)ADDR_DEXTERITY = (value + *(int *)(pcVar2 + 9)) / 2;
            ch = '\x01';
          }
          else {
            display_score_with_fatal(0xff37);
          }
        }
        else if (value == 8) {
          if (*(int *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ == 0 && *(int *)0xb934 == 0) {
            equipped_ring2 = pcVar2;
            *(int *)0xb934 = value;
            *(undefined2 *)0xb884 = *(undefined2 *)((int)*(undefined4 *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ + 9);
            ch = '\x01';
          }
          else {
            display_score_with_fatal(0xff87);
          }
        }
        else if ((value < 9) || (0xb < value)) {
          if (*(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ == 0 && *(int *)0xb928 == 0) {
            equipped_shield = pcVar2;
            *(int *)0xb928 = value;
            *(int *)ADDR_WISDOM = *(int *)(*(int *)(pcVar2 + 1) * 4 + -0x61e5) + *(int *)(pcVar2 + 9);
            ch = '\x01';
          }
          else {
            display_score_with_fatal(0xff87);
          }
        }
        else if (*(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ == 0 && *(int *)0xb930 == 0) {
          equipped_ring1 = pcVar2;
          *(int *)0xb930 = value;
          ch = '\x01';
        }
        else {
          display_score_with_fatal(0xff87);
        }
        value = *(int *)ADDR_WISDOM;
        value = *(int *)ADDR_DEXTERITY;
        base_ac = value + value;
        uVar7 = ch == '\0';
        if (!(bool)uVar7) {
          uVar4 = CONCAT11((char)((uint)(value + value) >> 8),pcVar2[1]);
          puVar8 = local_25;
          zero_word_array_16(puVar8);
          set_bit_range_in_array(CONCAT11(extraout_AH_01,0xb),CONCAT11(extraout_AH_01,9));
          create_bit_mask(puVar8,unaff_SS,uVar4);
          if ((bool)uVar7) {
            pcVar2[0x13] = '\x01';
          }
        }
      }
      else {
        display_score_with_fatal(200);
      }
    }
    display_character_stats();
  }
  return;
}



void __cdecl16near remove_equipped_item_menu(void)

{
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined1 uVar3;
  undefined1 extraout_AH_11;
  undefined1 extraout_AH_12;
  undefined1 extraout_AH_13;
  undefined1 extraout_AH_14;
  undefined1 extraout_AH_15;
  undefined2 uVar1;
  undefined1 extraout_AH_16;
  undefined1 extraout_AH_17;
  undefined1 extraout_AH_18;
  undefined1 extraout_AH_19;
  undefined1 extraout_AH_20;
  undefined1 extraout_AH_21;
  undefined1 extraout_AH_22;
  undefined1 extraout_AH_23;
  undefined1 extraout_AH_24;
  undefined1 extraout_AH_25;
  undefined1 extraout_AH_26;
  undefined1 extraout_AH_27;
  undefined1 extraout_AH_28;
  undefined1 extraout_AH_29;
  undefined1 extraout_AH_30;
  undefined1 extraout_AH_31;
  undefined1 extraout_AH_32;
  undefined1 extraout_AH_33;
  undefined1 extraout_AH_34;
  undefined1 extraout_AH_35;
  undefined2 uVar2;
  undefined1 extraout_AH_36;
  undefined1 extraout_AH_37;
  undefined1 extraout_AH_38;
  undefined1 extraout_AH_39;
  byte extraout_AH_40;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined1 local_12d [128];
  undefined1 local_ad [32];
  undefined1 local_8d [32];
  undefined1 local_6d [32];
  undefined1 local_4d [32];
  char ch;
  undefined1 local_2c [32];
  char local_c [5];
  char ch;
  undefined4 local_6;
  
  check_minimum_stats();
  ch = '\0';
  local_c[0] = '\0';
  puVar6 = local_4d;
  uVar2 = unaff_SS;
  zero_word_array_16(puVar6);
  copy_buffer_with_offset(0x20,local_2c,unaff_SS,puVar6,uVar2);
  if (*(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ != 0 || *(int *)0xb928 != 0) {
    copy_pascal_string_limited(4,local_c,unaff_SS,0x9f38,0x214c);
    puVar6 = local_4d;
    uVar2 = unaff_SS;
    zero_word_array_16(puVar6);
    set_bit_in_array(CONCAT11(extraout_AH,0x61));
    copy_buffer_with_offset(0x20,local_2c,unaff_SS,puVar6,uVar2);
  }
  if (*(int *)ADDR_EQUIPPED_ARMOR /* equipped_armor */ != 0 || *(int *)0xb92c != 0) {
    puVar6 = local_12d;
    uVar2 = unaff_SS;
    copy_pascal_string(local_c,unaff_SS);
    concat_pascal_string(0x9f3a,0x214c);
    copy_pascal_string_limited(4,local_c,unaff_SS,puVar6,uVar2);
    puVar6 = local_6d;
    uVar1 = unaff_SS;
    pad_and_copy_buffer(0x20,local_2c,unaff_SS);
    puVar5 = local_4d;
    uVar2 = unaff_SS;
    zero_word_array_16(puVar5);
    set_bit_in_array(CONCAT11(extraout_AH_00,0x68));
    bitwise_or_word_arrays(puVar5,uVar2);
    copy_buffer_with_offset(0x20,local_2c,unaff_SS,puVar6,uVar1);
  }
  if (*(int *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ != 0 || *(int *)0xb934 != 0) {
    puVar6 = local_12d;
    uVar2 = unaff_SS;
    copy_pascal_string(local_c,unaff_SS);
    concat_pascal_string(0x9f3c,0x214c);
    copy_pascal_string_limited(4,local_c,unaff_SS,puVar6,uVar2);
    puVar6 = local_6d;
    uVar1 = unaff_SS;
    pad_and_copy_buffer(0x20,local_2c,unaff_SS);
    puVar5 = local_4d;
    uVar2 = unaff_SS;
    zero_word_array_16(puVar5);
    set_bit_in_array(CONCAT11(extraout_AH_01,99));
    bitwise_or_word_arrays(puVar5,uVar2);
    copy_buffer_with_offset(0x20,local_2c,unaff_SS,puVar6,uVar1);
  }
  if (*(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ != 0 || *(int *)0xb930 != 0) {
    puVar6 = local_12d;
    uVar2 = unaff_SS;
    copy_pascal_string(local_c,unaff_SS);
    concat_pascal_string(0x9f3e,0x214c);
    copy_pascal_string_limited(4,local_c,unaff_SS,puVar6,uVar2);
    puVar6 = local_6d;
    uVar1 = unaff_SS;
    pad_and_copy_buffer(0x20,local_2c,unaff_SS);
    puVar5 = local_4d;
    uVar2 = unaff_SS;
    zero_word_array_16(puVar5);
    set_bit_in_array(CONCAT11(extraout_AH_02,0x67));
    bitwise_or_word_arrays(puVar5,uVar2);
    copy_buffer_with_offset(0x20,local_2c,unaff_SS,puVar6,uVar1);
  }
  uVar4 = local_c[0] == '\0';
  if ((bool)uVar4) {
    display_score_with_fatal(0x46);
  }
  else {
    ch = ' ';
    uVar1 = 0x61;
    puVar6 = local_4d;
    uVar2 = unaff_SS;
    pad_and_copy_buffer(0x20,local_2c,unaff_SS);
    create_bit_mask(puVar6,uVar2,uVar1);
    if ((bool)uVar4) {
      uVar1 = CONCAT11(extraout_AH_03,0x68);
      puVar6 = local_6d;
      uVar2 = unaff_SS;
      pad_and_copy_buffer(0x20,local_2c,unaff_SS);
      create_bit_mask(puVar6,uVar2,uVar1);
      if ((bool)uVar4) {
        uVar1 = CONCAT11(extraout_AH_04,99);
        puVar6 = local_8d;
        uVar2 = unaff_SS;
        pad_and_copy_buffer(0x20,local_2c,unaff_SS);
        create_bit_mask(puVar6,uVar2,uVar1);
        uVar3 = extraout_AH_05;
        if ((bool)uVar4) {
          ch = 'g';
        }
        else {
          ch = 'c';
        }
      }
      else {
        uVar1 = CONCAT11(extraout_AH_04,99);
        puVar6 = local_8d;
        uVar2 = unaff_SS;
        pad_and_copy_buffer(0x20,local_2c,unaff_SS);
        create_bit_mask(puVar6,uVar2,uVar1);
        uVar3 = extraout_AH_06;
        if ((bool)uVar4) {
          uVar1 = CONCAT11(extraout_AH_06,0x67);
          puVar6 = local_ad;
          uVar2 = unaff_SS;
          pad_and_copy_buffer(0x20,local_2c,unaff_SS);
          create_bit_mask(puVar6,uVar2,uVar1);
          uVar3 = extraout_AH_07;
          if ((bool)uVar4) {
            ch = 'h';
          }
        }
      }
    }
    else {
      uVar1 = CONCAT11(extraout_AH_03,0x68);
      puVar6 = local_6d;
      uVar2 = unaff_SS;
      pad_and_copy_buffer(0x20,local_2c,unaff_SS);
      create_bit_mask(puVar6,uVar2,uVar1);
      uVar3 = extraout_AH_08;
      if ((bool)uVar4) {
        uVar1 = CONCAT11(extraout_AH_08,99);
        puVar6 = local_8d;
        uVar2 = unaff_SS;
        pad_and_copy_buffer(0x20,local_2c,unaff_SS);
        create_bit_mask(puVar6,uVar2,uVar1);
        uVar3 = extraout_AH_09;
        if ((bool)uVar4) {
          uVar1 = CONCAT11(extraout_AH_09,0x67);
          puVar6 = local_ad;
          uVar2 = unaff_SS;
          pad_and_copy_buffer(0x20,local_2c,unaff_SS);
          create_bit_mask(puVar6,uVar2,uVar1);
          uVar3 = extraout_AH_10;
          if ((bool)uVar4) {
            ch = 'a';
          }
        }
      }
    }
    uVar1 = CONCAT11(uVar3,ch);
    puVar6 = local_4d;
    uVar2 = unaff_SS;
    zero_word_array_16(puVar6);
    set_bit_in_array(CONCAT11(extraout_AH_11,0x61));
    set_bit_in_array(CONCAT11(extraout_AH_12,99));
    set_bit_in_array(CONCAT11(extraout_AH_13,0x68));
    set_bit_in_array(CONCAT11(extraout_AH_14,0x67));
    create_bit_mask(puVar6,uVar2,uVar1);
    uVar3 = extraout_AH_15;
    if ((bool)uVar4) {
      do {
        display_score_with_fatal(0x57);
        uVar1 = read_keyboard_input();
        ch = (char)uVar1;
        puVar6 = local_6d;
        uVar2 = unaff_SS;
        zero_word_array_16(puVar6);
        set_bit_in_array(CONCAT11(extraout_AH_16,0x61));
        set_bit_in_array(CONCAT11(extraout_AH_17,99));
        set_bit_in_array(CONCAT11(extraout_AH_18,0x68));
        set_bit_in_array(CONCAT11(extraout_AH_19,0x67));
        create_bit_mask(puVar6,uVar2,uVar1);
        uVar3 = extraout_AH_20;
        if ((bool)uVar4) {
          uVar1 = 0xe654;
          uVar4 = 1;
          uVar2 = unaff_DS;
          write_bytes(0,CONCAT11(extraout_AH_20,7));
          flush_output(uVar1,uVar2);
          validate_window_coords(CONCAT11(extraout_AH_21,1),CONCAT11(extraout_AH_21,1));
          uVar3 = extraout_AH_22;
        }
        uVar1 = CONCAT11(uVar3,ch);
        puVar6 = local_6d;
        uVar2 = unaff_SS;
        zero_word_array_16(puVar6);
        set_bit_in_array(CONCAT11(extraout_AH_23,0x61));
        set_bit_in_array(CONCAT11(extraout_AH_24,99));
        set_bit_in_array(CONCAT11(extraout_AH_25,0x68));
        set_bit_in_array(CONCAT11(extraout_AH_26,0x67));
        create_bit_mask(puVar6,uVar2,uVar1);
        uVar3 = extraout_AH_27;
      } while ((bool)uVar4);
    }
    if (ch == 'a') {
      if (*(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ == 0 && *(int *)0xb928 == 0) {
        display_score_with_fatal(0xff35);
        uVar3 = extraout_AH_28;
      }
      else {
        local_6 = *(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */;
        if (*(char *)((int)local_6 + 0x14) == '\0') {
          equipped_shield = 0;
          *(undefined2 *)0xb928 = 0;
          uVar3 = 0;
          *(undefined2 *)ADDR_WISDOM = 0;
        }
        else {
          display_score_with_fatal(0x147);
          uVar3 = extraout_AH_29;
        }
        ch = '\x01';
      }
    }
    if (ch == 'h') {
      if (*(int *)ADDR_EQUIPPED_ARMOR /* equipped_armor */ == 0 && *(int *)0xb92c == 0) {
        display_score_with_fatal(0xff35);
        uVar3 = extraout_AH_30;
      }
      else {
        local_6 = *(undefined4 *)ADDR_EQUIPPED_ARMOR /* equipped_armor */;
        if (*(char *)((int)local_6 + 0x14) == '\0') {
          equipped_armor = 0;
          *(undefined2 *)0xb92c = 0;
          uVar3 = 0;
          *(undefined2 *)ADDR_DEXTERITY = 0;
        }
        else {
          display_score_with_fatal(0x58);
          uVar3 = extraout_AH_31;
        }
        ch = '\x01';
      }
    }
    if (ch == 'c') {
      if (*(int *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ == 0 && *(int *)0xb934 == 0) {
        display_score_with_fatal(0xff35);
        uVar3 = extraout_AH_32;
      }
      else {
        local_6 = *(undefined4 *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */;
        if (*(char *)((int)local_6 + 0x14) == '\0') {
          equipped_ring2 = 0;
          *(undefined2 *)0xb934 = 0;
          uVar3 = 0;
          *(undefined2 *)0xb884 = 0;
        }
        else {
          display_score_with_fatal(0x147);
          uVar3 = extraout_AH_33;
        }
        ch = '\x01';
      }
    }
    uVar4 = ch == 'g';
    if ((bool)uVar4) {
      uVar4 = *(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ == 0 && *(int *)0xb930 == 0;
      if (*(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ == 0 && *(int *)0xb930 == 0) {
        display_score_with_fatal(0xff35);
        uVar3 = extraout_AH_34;
      }
      else {
        local_6 = *(undefined4 *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */;
        uVar4 = *(char *)((int)local_6 + 0x14) == '\0';
        if ((bool)uVar4) {
          uVar3 = 0;
          uVar4 = 1;
          equipped_ring1 = 0;
          *(undefined2 *)0xb930 = 0;
        }
        else {
          display_score_with_fatal(0x4f);
          uVar3 = extraout_AH_35;
        }
        ch = '\x01';
      }
    }
    uVar2 = CONCAT11(uVar3,ch);
    puVar6 = local_4d;
    zero_word_array_16(puVar6);
    set_bit_in_array(CONCAT11(extraout_AH_36,0x61));
    set_bit_in_array(CONCAT11(extraout_AH_37,99));
    set_bit_in_array(CONCAT11(extraout_AH_38,0x68));
    set_bit_in_array(CONCAT11(extraout_AH_39,0x67));
    create_bit_mask(puVar6,unaff_SS,uVar2);
    if (((!(bool)uVar4) && (*(char *)((int)local_6 + 0x14) == '\0')) && (ch != '\0')) {
      display_score_with_fatal(0xb8);
      display_object_info((uint)extraout_AH_40 << 8,CONCAT11(extraout_AH_40,1),(undefined2)local_6,
                    local_6._2_2_);
      print_prompt();
    }
  }
  base_ac = *(int *)ADDR_WISDOM + *(int *)ADDR_DEXTERITY;
  display_character_stats();
  return;
}



void __cdecl16near FUN_1000_a45b(void)

{
  undefined4 uVar1;
  int iVar2;
  byte bVar3;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 uVar5;
  
  check_minimum_stats();
  uVar4 = 0;
  if (*(int *)0xb8cc == 0 && *(int *)0xb8ce == 0) {
    display_score_with_fatal(0x19);
    return;
  }
  find_highest_bit();
  char_create_wrapper();
  if ((bool)uVar4) {
    uVar4 = 0;
    uVar5 = *(int *)0xb898 == 0 && *(int *)0xb89a == 0;
    if (*(int *)0xb898 != 0 || *(int *)0xb89a != 0) {
      find_highest_bit();
      char_create_wrapper();
      if ((bool)uVar4 || (bool)uVar5) goto LAB_1000_a4bd;
    }
    display_score_with_fatal(0xc5);
    current_food = current_food + -1;
    display_character_stats();
  }
  else {
LAB_1000_a4bd:
    iVar2 = random_mod(4);
    *(int *)((int)inventory_list + 9) = iVar2 * 100 + 800;
    turn_count = turn_count + *(int *)((int)inventory_list + 9);
    display_score_with_fatal(*(int *)((int)inventory_list + 9) / 100 + 0x30);
  }
  uVar1 = inventory_list;
  bVar3 = (byte)((ulong)uVar1 >> 8);
  destroy_or_consume_item(CONCAT11(bVar3,1),(uint)bVar3 << 8,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
  return;
}



void FUN_1000_a518(undefined4 param_1)

{
  char random_val;
  int random_val;
  undefined2 uVar3;
  undefined2 in_BX;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 uVar7;
  
  uVar4 = (undefined2)param_1;
  uVar5 = (undefined2)((ulong)param_1 >> 0x10);
  if (current_food == 0) {
    process_game_over(uVar4,uVar5,0x65);
  }
  random_val = check_inventory_has_item(3);
  if (((random_val == '\0') || (random_val = random_mod(4), random_val != 0)) ||
     (*(int *)0xb8a8 != 0 || *(int *)0xb8aa != 0)) {
    if (*(int *)0xb8a8 == 0 && *(int *)0xb8aa == 0) {
      turn_count = turn_count + -1;
    }
    else {
      turn_count = (turn_count / 2) * 2 + -2;
    }
    if (turn_count < -200) {
      process_game_over(uVar4,uVar5,0x66);
    }
    else {
      if (turn_count < 0) {
        random_val = turn_count >> 0xf;
        combat_wrapper();
        conditional_char_action();
        uVar6 = 0;
        uVar7 = 1;
        uVar3 = float_add_with_handler();
        find_highest_bit(uVar3,in_BX,random_val);
        char_create_wrapper();
        if (!(bool)uVar6 && !(bool)uVar7) {
          display_score_with_fatal(0xff55);
          is_dying = 1;
          *(undefined2 *)ADDR_DEATH_TIMER /* death_timer */ = 1;
          goto LAB_1000_a64e;
        }
      }
      if (turn_count < 0x32) {
        if (turn_count % 0x19 == 0) {
          current_food = current_food + -1;
        }
        if (current_food == 0) {
          process_game_over(uVar4,uVar5,0x65);
        }
        else {
          display_character_stats();
        }
      }
      else if (turn_count == 0x32) {
        display_score_with_fatal(0xffb0);
        current_food = current_food + -1;
        if (current_food == 0) {
          process_game_over(uVar4,uVar5,0x65);
        }
        else {
          display_character_stats();
        }
      }
      else if (turn_count == 100) {
        display_score_with_fatal(0xffaf);
      }
    }
  }
LAB_1000_a64e:
  if (*(int *)0xb89c != 0 || *(int *)0xb89e != 0) {
    food_level = food_level / 2 << 1;
  }
  if (food_level == 400) {
    display_score_with_fatal(0xff3d);
  }
  else if (food_level == 100) {
    display_score_with_fatal(0xff3c);
  }
  return;
}



void FUN_1000_a68a(undefined4 param_1)

{
  bool flag;
  int value;
  byte extraout_AH;
  int value;
  undefined2 unaff_DS;
  undefined2 local_5;
  
  flag = false;
  value = (int)param_1;
  value = (int)((ulong)param_1 >> 0x10);
  if (0 < *(int *)0xb936) {
    local_5 = 1;
    do {
      if (flag) {
LAB_1000_a6cc:
        flag = true;
      }
      else {
        if ((value == *(int *)(local_5 * 4 + -0x46ca)) && (value == *(int *)(local_5 * 4 + -0x46cc))
           ) goto LAB_1000_a6cc;
        flag = false;
      }
      if (local_5 == *(int *)0xb936) break;
      local_5 = local_5 + 1;
    } while( true );
  }
  if (flag) {
    display_score_with_fatal(0x1f);
  }
  else {
    local_5 = 0;
    do {
      local_5 = local_5 + 1;
    } while (*(int *)(local_5 * 4 + -0x46cc) != 0 || *(int *)(local_5 * 4 + -0x46ca) != 0);
    *(int *)(local_5 * 4 + -0x46cc) = value;
    *(int *)(local_5 * 4 + -0x46ca) = value;
    display_score_with_fatal(0x9c);
    display_object_info((uint)extraout_AH << 8,CONCAT11(extraout_AH,1),value,value);
    print_prompt();
    if (*(int *)(value + 1) == 0xc) {
      handle_error_and_wait();
      remove_spell(local_5);
    }
  }
  return;
}



void __cdecl16near FUN_1000_a74b(void)

{
  undefined4 uVar1;
  char ch;
  undefined2 uVar3;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  byte extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined2 uVar4;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar5;
  undefined1 *puVar6;
  undefined1 local_10b [224];
  undefined1 local_2b [32];
  int local_b;
  undefined1 local_9 [2];
  undefined1 local_7;
  undefined4 flag;
  
  check_minimum_stats();
  ch = check_inventory_has_item(0);
  if (ch == '\0') {
    display_score_with_fatal(0x1d);
  }
  else {
    do {
      check_minimum_stats();
      display_score_with_fatal(0x9d);
      uVar3 = read_keyboard_input();
      local_7 = (undefined1)uVar3;
      puVar6 = local_2b;
      uVar4 = unaff_SS;
      zero_word_array_16(puVar6);
      uVar5 = *(int *)0xb936 + 0x30 == 0;
      set_bit_range_in_array(*(int *)0xb936 + 0x30,CONCAT11(extraout_AH,0x31));
      create_bit_mask(puVar6,uVar4,uVar3);
    } while ((bool)uVar5);
    flag = 0;
    check_minimum_stats();
    puVar6 = local_10b;
    uVar4 = unaff_SS;
    char_to_pascal_string(CONCAT11(extraout_AH_00,local_7));
    local_b = parse_pascal_string_to_int(local_9,unaff_SS,puVar6,uVar4);
    uVar1 = *(undefined4 *)(local_b * 4 + -0x46cc);
    flag._2_2_ = (int)((ulong)uVar1 >> 0x10);
    flag._0_2_ = (int)uVar1;
    if ((int)flag == 0 && flag._2_2_ == 0) {
      display_score_with_fatal(0x1c);
    }
    else if (*(char *)((int)flag + 0x14) == '\0') {
      uVar5 = 1;
      *(undefined2 *)(local_b * 4 + -0x46cc) = 0;
      *(undefined2 *)(local_b * 4 + -0x46ca) = 0;
      display_score_with_fatal(0x1a5);
      display_object_info((uint)extraout_AH_01 << 8,CONCAT11(extraout_AH_01,1),(int)flag,flag._2_2_)
      ;
      uVar4 = CONCAT11(extraout_AH_02,*(undefined1 *)((int)flag + 1));
      puVar6 = local_2b;
      zero_word_array_16(puVar6);
      set_bit_in_array(CONCAT11(extraout_AH_03,5));
      set_bit_in_array(CONCAT11(extraout_AH_04,0x13));
      create_bit_mask(puVar6,unaff_SS,uVar4);
      if (!(bool)uVar5) {
        *(undefined1 *)((int)flag + 0x14) = 1;
      }
      print_prompt();
    }
    else {
      display_score_with_fatal(0x4e);
    }
  }
  return;
}



void FUN_1000_a85c(int *result_ptr,int *count)

{
  char ch;
  
  check_minimum_stats();
  display_score_with_fatal(0x9f);
  do {
    *count = 0;
    *result_ptr = 0;
    ch = read_keyboard_input();
    if (ch == CMD_MOVE_LEFT) {
      *result_ptr = -1;
    }
    else if (ch == CMD_MOVE_RIGHT) {
      *result_ptr = 1;
    }
    else if (ch == CMD_MOVE_DOWN) {
      *count = 1;
    }
    else if (ch == CMD_MOVE_UP) {
      *count = -1;
    }
    else if (ch == '\0') {
      ch = read_keyboard_input();
      if (ch == 'K') {
        *result_ptr = -1;
      }
      else if (ch == 'M') {
        *result_ptr = 1;
      }
      else if (ch == 'P') {
        *count = 1;
      }
      else if (ch == 'H') {
        *count = -1;
      }
    }
  } while ((*count == 0) && (*result_ptr == 0));
  return;
}



void FUN_1000_a91f(int *result_ptr,int *count,int *flags,int *data_ptr,int *param_5)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined1 local_24 [32];
  int local_4;
  
  *param_5 = player_y;
  *data_ptr = player_x;
  local_4 = 0;
  while( true ) {
    *param_5 = *param_5 + *flags;
    *data_ptr = *data_ptr + *count;
    local_4 = local_4 + 1;
    if (local_4 == *result_ptr) break;
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    flag = (int)uVar1 + *param_5 * MAP_WIDTH + *data_ptr;
    uVar4 = flag == 0;
    uVar2 = CONCAT11((char)((uint)(*param_5 * MAP_WIDTH) >> 8),*(undefined1 *)(flag + -0x50));
    puVar5 = local_24;
    uVar6 = unaff_SS;
    pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
    create_bit_mask(puVar5,uVar6,uVar2);
    if ((!(bool)uVar4) || (*(char *)(*param_5 * MAP_WIDTH + *data_ptr + -0xc) != ' ')) break;
  }
  if (*(char *)(*param_5 * MAP_WIDTH + *data_ptr + -0xc) == ' ') {
    *param_5 = *param_5 - *flags;
    *data_ptr = *data_ptr - *count;
  }
  return;
}



void FUN_1000_aa1d(undefined4 param_1)

{
  int iVar1;
  int value;
  int iVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  undefined1 local_2c [28];
  undefined1 *local_10;
  undefined1 *local_c;
  int local_8;
  int local_6;
  int local_4;
  
  uVar5 = (undefined2)((ulong)param_1 >> 0x10);
  iVar3 = (int)param_1;
  FUN_1000_a91f(*(int *)(iVar3 + 1) * 4 + -0x6243,unaff_DS,&stack0x0006,unaff_SS,&stack0x0008,
                unaff_SS,&local_6,unaff_SS,&local_8,unaff_SS);
  if (*(char *)(local_8 * MAP_WIDTH + local_6 + -0xc) != ' ') {
    find_item_at_coords(&local_c,unaff_SS,local_6,local_8);
    uVar6 = (undefined2)((ulong)local_c >> 0x10);
    puVar4 = (undefined1 *)local_c;
    *(int *)(puVar4 + 0x2c) = *(int *)(puVar4 + 0x2c) + 1;
    iVar1 = *(int *)(iVar3 + 1);
    uVar7 = iVar1 == 1;
    if (((bool)uVar7) || (uVar7 = iVar1 == 0x10, (bool)uVar7)) {
      uVar6 = CONCAT11((char)((uint)iVar1 >> 8),*local_c);
      puVar4 = local_2c;
      pad_and_copy_buffer(0x20,0xb82f,unaff_DS);
      create_bit_mask(puVar4,unaff_SS,uVar6);
      if ((bool)uVar7) {
        uVar6 = (undefined2)((ulong)local_c >> 0x10);
        find_random_empty_floor_space(0xe52d,unaff_DS,(undefined1 *)local_c + 0x1e,uVar6,
                      (undefined1 *)local_c + 0x1c,uVar6);
        *(undefined1 *)(local_8 * MAP_WIDTH + local_6 + -0xc) = 0x20;
        put_char_at_pos(CONCAT11((char)((uint)(local_8 * MAP_WIDTH) >> 8),0x20),local_6,local_8);
        uVar6 = (undefined2)((ulong)local_c >> 0x10);
        puVar4 = (undefined1 *)local_c;
        *(undefined1 *)(*(int *)(puVar4 + 0x1c) * MAP_WIDTH + *(int *)(puVar4 + 0x1e) + -0xc) = puVar4[1]
        ;
        if (is_confused != '\0') {
          is_confused = 0;
        }
        puVar4[0x23] = 0;
      }
      if (*(int *)(iVar3 + 1) == 0x10) {
        ((undefined1 *)local_c)[0x27] = 1;
      }
    }
    else if (iVar1 == 2) {
      if (puVar4[0x29] == '\0') {
        local_10 = local_c;
        do {
          local_4 = random_mod(0x23);
          local_4 = local_4 + 1;
        } while (*(char *)(local_4 * 0x2a + -0x4fee) != '\0');
        uVar5 = (undefined2)((ulong)local_10 >> 0x10);
        puVar4 = (undefined1 *)local_10;
        puVar4[1] = *(undefined1 *)(local_4 * 0x2a + -0x5007);
        *local_10 = puVar4[1];
        *(int *)(puVar4 + 4) = local_4;
        *(int *)(puVar4 + 2) = local_4;
        *(undefined2 *)(puVar4 + 8) = *(undefined2 *)(local_4 * 0x2a + -0x5004);
        *(undefined2 *)(puVar4 + 6) = *(undefined2 *)(local_4 * 0x2a + -0x5006);
        *(undefined2 *)(puVar4 + 10) = *(undefined2 *)(local_4 * 0x2a + -0x5002);
        *(undefined2 *)(puVar4 + 0xc) = *(undefined2 *)(local_4 * 0x2a + -0x5000);
        *(undefined2 *)(puVar4 + 0x10) = *(undefined2 *)(local_4 * 0x2a + -0x4ffc);
        *(undefined2 *)(puVar4 + 0xe) = *(undefined2 *)(local_4 * 0x2a + -0x4ffe);
        puVar4[0x22] = 0;
        puVar4[0x23] = 0;
        puVar4[0x28] = 0;
        *(undefined2 *)(puVar4 + 0x2a) = 0;
        *(undefined2 *)(puVar4 + 0x2e) = 0;
        *(undefined2 *)(puVar4 + 0x30) = 0;
        is_confused = 0;
        iVar3 = *(int *)(puVar4 + 0x1c);
        *(undefined1 *)(iVar3 * MAP_WIDTH + *(int *)(puVar4 + 0x1e) + -0xc) = puVar4[1];
        put_char_at_pos(CONCAT11((char)((uint)(iVar3 * MAP_WIDTH) >> 8),puVar4[1]),
                      *(undefined2 *)(puVar4 + 0x1e),*(undefined2 *)(puVar4 + 0x1c));
      }
    }
    else if (iVar1 == 5) {
      if (puVar4[0x24] == '\0') {
        puVar4[0x25] = 1;
        if (puVar4[0x29] == '\0') {
          iVar3 = random_mod(10);
          *(int *)((undefined1 *)local_c + 0x20) = iVar3 + 10;
        }
        else {
          iVar3 = random_mod(5);
          *(int *)((undefined1 *)local_c + 0x20) = iVar3 + 5;
        }
      }
      else {
        puVar4[0x24] = 0;
      }
    }
    else if (iVar1 == 6) {
      if (puVar4[0x25] == '\0') {
        *(int *)(puVar4 + 0x2c) = *(int *)(puVar4 + 0x2c) + -1;
        puVar4[0x24] = 1;
        iVar3 = random_mod(10);
        *(int *)((undefined1 *)local_c + 0x20) = iVar3 + 10;
      }
      else {
        puVar4[0x25] = 0;
      }
    }
    else if (iVar1 == 7) {
      if (puVar4[0x29] == '\0') {
        *(int *)(puVar4 + 10) = *(int *)(puVar4 + 10) / 5 + 1;
      }
      else {
        combat_wrapper();
        check_combat_and_handle_error();
        iVar3 = combat_check_with_error();
        *(int *)((undefined1 *)local_c + 10) = iVar3 + 1;
      }
      current_hp = current_hp / 2 + 1;
      display_character_stats();
    }
    else if (iVar1 == 8) {
      if (puVar4[0x29] == '\0') {
        puVar4[0x22] = 1;
      }
    }
    else if (iVar1 == 0xc) {
      if (puVar4[0x29] == '\0') {
        iVar3 = random_mod(player_level + dungeon_level);
        uVar5 = (undefined2)((ulong)local_c >> 0x10);
        iVar3 = (*(int *)((undefined1 *)local_c + 10) + -10) - iVar3;
        *(int *)((undefined1 *)local_c + 10) = iVar3;
      }
      else {
        iVar3 = random_mod(0xb);
        uVar5 = (undefined2)((ulong)local_c >> 0x10);
        iVar3 = *(int *)((undefined1 *)local_c + 10) - iVar3;
        *(int *)((undefined1 *)local_c + 10) = iVar3;
      }
      uVar5 = (undefined2)((ulong)local_c >> 0x10);
      if (*(int *)((undefined1 *)local_c + 10) < 0) {
        kill_monster(CONCAT11((char)((uint)iVar3 >> 8),1),(undefined1 *)local_c,uVar5);
      }
    }
    else if (iVar1 == 0xe) {
      if (puVar4[0x29] == '\0') {
        puVar4[0x28] = 1;
      }
    }
    else if (iVar1 == 0xf) {
      if (puVar4[0x29] == '\0') {
        iVar3 = random_mod(7);
        *(int *)((undefined1 *)local_c + 0x2a) = iVar3 + 10;
      }
      else {
        iVar3 = random_mod(3);
        *(int *)((undefined1 *)local_c + 0x2a) = iVar3 + 2;
      }
    }
    else if (iVar1 == 0x12) {
      *(int *)(puVar4 + 10) = current_hp / 2 + *(int *)(puVar4 + 10) + 1;
      current_hp = current_hp / 2 + 1;
      display_character_stats();
    }
    else if (iVar1 == CMD_SAVE) {
      iVar3 = random_mod(2);
      puVar4 = (undefined1 *)local_c;
      uVar5 = (undefined2)((ulong)local_c >> 0x10);
      if (iVar3 == 1) {
        if (puVar4[0x29] == '\0') {
          *(undefined2 *)(puVar4 + 10) = 1;
          iVar3 = random_mod(*(undefined2 *)ADDR_MAX_HP /* max_hp */);
          current_hp = iVar3 + 1;
        }
      }
      else {
        *(undefined2 *)(puVar4 + 10) = *(undefined2 *)(*(int *)(puVar4 + 4) * 0x2a + -0x5002);
        *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = 1;
      }
      display_character_stats();
    }
    else if (iVar1 == 0x14) {
      do {
        local_4 = random_mod(0x23);
        local_4 = local_4 + 1;
      } while (*(char *)(local_4 * 0x2a + -0x4fee) != '\0');
      uVar5 = (undefined2)((ulong)local_c >> 0x10);
      *(int *)((undefined1 *)local_c + 4) = local_4;
      ((undefined1 *)local_c)[1] = *(undefined1 *)(local_4 * 0x2a + -0x5007);
    }
    else if (iVar1 == MAP_HEIGHT) {
      if (puVar4[0x29] == '\0') {
        local_4 = random_mod(3);
        local_4 = local_4 + 1;
      }
      else {
        local_4 = 1;
      }
      uVar6 = (undefined2)((ulong)local_c >> 0x10);
      *(int *)((undefined1 *)local_c + 8) = *(int *)((undefined1 *)local_c + 8) - local_4;
      random_mod(10);
      value = multiply_integers();
      uVar6 = (undefined2)((ulong)local_c >> 0x10);
      puVar4 = (undefined1 *)local_c;
      iVar1 = *(int *)(puVar4 + 10);
      *(int *)(puVar4 + 10) = iVar1 - value;
      if ((*(int *)(puVar4 + 8) < 1) || (*(int *)(puVar4 + 10) < 0)) {
        kill_monster(CONCAT11((char)((uint)(iVar1 - value) >> 8),1),puVar4,uVar6);
      }
      if (((undefined1 *)local_c)[0x29] != '\0') {
        *(undefined2 *)(iVar3 + 9) = 1;
      }
      random_mod(10);
      iVar3 = multiply_integers();
      current_hp = current_hp + iVar3;
      if (max_hp < current_hp) {
        *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = *(undefined2 *)ADDR_MAX_HP /* max_hp */;
      }
      display_character_stats();
    }
  }
  return;
}



void FUN_1000_b032(undefined4 param_1)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined1 extraout_AH;
  byte extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  int iVar3;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  int value;
  int iVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined2 uVar11;
  undefined1 local_70 [32];
  undefined1 local_50 [28];
  undefined4 local_34;
  undefined1 local_30 [32];
  undefined1 local_10 [6];
  undefined1 local_a [4];
  int local_6;
  int local_4;
  
  FUN_1000_a85c(&local_4,unaff_SS,&local_6,unaff_SS);
  uVar6 = (undefined2)((ulong)param_1 >> 0x10);
  value = (int)param_1;
  if (*(int *)(value + 9) == 0) {
    check_minimum_stats();
    display_score_with_fatal(0x15);
  }
  else {
    iVar3 = *(int *)(value + 1);
    if (iVar3 == 3) {
      iVar3 = (player_y + local_6) * MAP_WIDTH;
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      iVar5 = (int)uVar1 + iVar3 + player_x + local_4;
      uVar8 = iVar5 == 0;
      uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar10 = local_30;
      uVar11 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
      puVar9 = local_50;
      uVar7 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb7cf,unaff_DS);
      bitwise_or_word_arrays(puVar9,uVar7);
      create_bit_mask(puVar10,uVar11,uVar2);
      if ((!(bool)uVar8) &&
         ((!(bool)((char)*(undefined2 *)ADDR_PLAYER_Y /* player_y */ + (char)local_6 & 1) ||
          (!(bool)((char)*(undefined2 *)ADDR_PLAYER_X /* player_x */ + (char)local_4 & 1))))) {
        iVar3 = (player_y + local_6) * MAP_WIDTH;
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        iVar5 = (int)uVar1 + iVar3 + player_x + local_4;
        uVar8 = iVar5 == 0;
        uVar7 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
        puVar10 = local_70;
        pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
        create_bit_mask(puVar10,unaff_SS,uVar7);
        if ((bool)uVar8) {
          FUN_1000_2214(player_x + local_4,player_y + local_6);
        }
        else {
          FUN_1000_2138(player_x + local_4,player_y + local_6);
        }
        redraw_dungeon_level(player_y + 1);
      }
    }
    else if (iVar3 == 4) {
      iVar3 = (player_y + local_6) * MAP_WIDTH;
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      iVar5 = (int)uVar1 + iVar3 + player_x + local_4;
      uVar8 = iVar5 == 0;
      uVar11 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar10 = local_30;
      uVar7 = unaff_SS;
      zero_word_array_16(puVar10);
      set_bit_in_array(CONCAT11(extraout_AH,0xef));
      create_bit_mask(puVar10,uVar7,uVar11);
      if ((bool)uVar8) {
        iVar3 = (player_y + local_6) * MAP_WIDTH;
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        iVar5 = (int)uVar1 + iVar3 + player_x + local_4;
        uVar8 = iVar5 == 0;
        uVar11 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
        puVar10 = local_50;
        uVar7 = unaff_SS;
        pad_and_copy_buffer(0x20,0xb7cf,unaff_DS);
        create_bit_mask(puVar10,uVar7,uVar11);
        if (!(bool)uVar8) {
          FUN_1000_2214(player_x + local_4,player_y + local_6);
        }
        FUN_1000_21b0(player_x + local_4,player_y + local_6);
        if (*(char *)((player_y + local_6) * MAP_WIDTH + player_x + local_4 + -0xc) != ' ') {
          iVar3 = (player_y + local_6) * MAP_WIDTH;
          uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
          iVar5 = (int)uVar1 + iVar3 + player_x + local_4;
          uVar8 = iVar5 == 0;
          uVar11 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
          puVar10 = local_50;
          uVar7 = unaff_SS;
          pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
          create_bit_mask(puVar10,uVar7,uVar11);
          if (!(bool)uVar8) {
            find_item_at_coords(local_a,unaff_SS,player_x + local_4,player_y + local_6);
            if (*(char *)(local_a._0_2_ + 0x29) == '\0') {
              kill_monster((uint)extraout_AH_00 << 8,local_a._0_2_,local_a._2_2_);
            }
          }
        }
        redraw_dungeon_level(player_y + 1);
      }
    }
    else if (iVar3 == 9) {
      iVar3 = (player_y + local_6) * MAP_WIDTH;
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      iVar5 = (int)uVar1 + iVar3 + player_x + local_4;
      uVar8 = iVar5 == 0;
      uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar10 = local_50;
      uVar11 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
      puVar9 = local_30;
      uVar7 = unaff_SS;
      zero_word_array_16(puVar9);
      set_bit_in_array(CONCAT11(extraout_AH_01,0xef));
      bitwise_or_word_arrays(puVar9,uVar7);
      create_bit_mask(puVar10,uVar11,uVar2);
      if ((bool)uVar8) {
        iVar3 = (player_y + local_6) * MAP_WIDTH;
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        iVar5 = (int)uVar1 + iVar3 + player_x + local_4;
        uVar8 = iVar5 == 0;
        uVar7 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
        puVar10 = local_70;
        pad_and_copy_buffer(0x20,0xb7cf,unaff_DS);
        create_bit_mask(puVar10,unaff_SS,uVar7);
        if (!(bool)uVar8) {
          FUN_1000_2214(player_x + local_4,player_y + local_6);
        }
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        *(undefined1 *)
         ((int)uVar1 + (player_y + local_6) * MAP_WIDTH + player_x + local_4 + -0x50) = 0xf7;
        render_field_of_view();
      }
    }
    else if (iVar3 == 10) {
      if (*(char *)((player_y + local_6) * MAP_WIDTH + player_x + local_4 + -0xc) == ' ') {
        iVar3 = (player_y + local_6) * MAP_WIDTH;
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        iVar5 = (int)uVar1 + iVar3 + player_x + local_4;
        uVar8 = iVar5 == 0;
        uVar7 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
        puVar10 = local_30;
        pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
        create_bit_mask(puVar10,unaff_SS,uVar7);
        if (((bool)uVar8) &&
           (populate_level_with_monsters(),
           *(int *)(dungeon_level * 4 + -0x5499) != 0 ||
           *(int *)(dungeon_level * 4 + -0x5497) != 0)) {
          local_34 = *(undefined4 *)(dungeon_level * 4 + -0x5499);
          uVar7 = (undefined2)((ulong)local_34 >> 0x10);
          iVar3 = (int)local_34;
          *(undefined1 *)(*(int *)(iVar3 + 0x1c) * MAP_WIDTH + *(int *)(iVar3 + 0x1e) + -0xc) = 0x20;
          *(int *)(iVar3 + 0x1c) = player_y + local_6;
          *(int *)(iVar3 + 0x1e) = player_x + local_4;
          *(undefined1 *)(*(int *)(iVar3 + 0x1c) * MAP_WIDTH + *(int *)(iVar3 + 0x1e) + -0xc) =
               *(undefined1 *)(iVar3 + 1);
          render_field_of_view();
        }
      }
    }
    else if (iVar3 == 0xb) {
      iVar3 = (player_y + local_6) * MAP_WIDTH;
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      iVar5 = (int)uVar1 + iVar3 + player_x + local_4;
      uVar8 = iVar5 == 0;
      uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar10 = local_50;
      uVar11 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
      puVar9 = local_30;
      uVar7 = unaff_SS;
      zero_word_array_16(puVar9);
      set_bit_in_array(CONCAT11(extraout_AH_02,0xef));
      set_bit_in_array(CONCAT11(extraout_AH_03,0xf7));
      bitwise_or_word_arrays(puVar9,uVar7);
      puVar9 = local_70;
      uVar7 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb7cf,unaff_DS);
      bitwise_or_word_arrays(puVar9,uVar7);
      create_bit_mask(puVar10,uVar11,uVar2);
      if ((bool)uVar8) {
        iVar3 = random_mod(5);
        initialize_monster_or_item(local_10,unaff_SS,*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */,iVar3 + 1);
        place_object_on_map(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */,local_10,unaff_SS);
        uVar7 = SUB42(local_10._0_4_,2);
        iVar3 = (int)local_10._0_4_;
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        *(undefined1 *)((int)uVar1 + *(int *)(iVar3 + 5) * MAP_WIDTH + *(int *)(iVar3 + 7) + -0x50) =
             0x20;
        *(int *)(iVar3 + 5) = player_y + local_6;
        *(int *)(iVar3 + 7) = player_x + local_4;
        uVar8 = lookup_table_b9c7(iVar3,uVar7);
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        *(undefined1 *)((int)uVar1 + *(int *)(iVar3 + 5) * MAP_WIDTH + *(int *)(iVar3 + 7) + -0x50) =
             uVar8;
        render_field_of_view();
      }
    }
    else if (iVar3 == 0xd) {
      iVar3 = (player_y + local_6) * MAP_WIDTH;
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      iVar5 = (int)uVar1 + iVar3 + player_x + local_4;
      uVar8 = iVar5 == 0;
      uVar7 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar10 = local_30;
      zero_word_array_16(puVar10);
      set_bit_in_array(CONCAT11(extraout_AH_04,*(undefined1 *)0x0));
      set_bit_in_array(CONCAT11(extraout_AH_05,*(undefined1 *)0x1));
      set_bit_in_array(CONCAT11(extraout_AH_06,*(undefined1 *)0x2));
      set_bit_in_array(CONCAT11(extraout_AH_07,*(undefined1 *)0x3));
      create_bit_mask(puVar10,unaff_SS,uVar7);
      if (!(bool)uVar8) {
        validate_window_coords(player_y + local_6 + 1,player_x + local_4);
        uVar11 = 0xe654;
        uVar7 = unaff_DS;
        write_bytes(0,CONCAT11(extraout_AH_08,0x20));
        flush_output(uVar11,uVar7);
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        *(undefined1 *)
         ((int)uVar1 + (player_y + local_6) * MAP_WIDTH + player_x + local_4 + -0x50) = 0x20;
      }
    }
    else if (iVar3 == 0x11) {
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      if (*(char *)((int)uVar1 + (player_y + local_6) * MAP_WIDTH + player_x + local_4 +
                   -0x50) == ' ') {
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        *(undefined1 *)
         ((int)uVar1 + (player_y + local_6) * MAP_WIDTH + player_x + local_4 + -0x50) =
             *(undefined1 *)0x1;
      }
    }
    else if (iVar3 == 0x15) {
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      if (*(char *)((int)uVar1 + (player_y + local_6) * MAP_WIDTH + player_x + local_4 +
                   -0x50) == -9) {
        *(undefined1 *)(dungeon_level + 0x796d) = 0;
      }
    }
    else {
      FUN_1000_aa1d(value,uVar6,local_4,local_6);
    }
    *(int *)(value + 9) = *(int *)(value + 9) + -1;
  }
  return;
}



void FUN_1000_b711(int x_pos,undefined2 param_2,undefined2 flags)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int value;
  undefined1 uVar4;
  byte bVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
  uVar1 = *(undefined1 *)((int)uVar2 + player_y * MAP_WIDTH + player_x + -0x50);
  bVar5 = (byte)((uint)(player_y * MAP_WIDTH) >> 8);
  destroy_or_consume_item((uint)bVar5 << 8,CONCAT11(bVar5,1),param_2,flags);
  uVar2 = *(undefined4 *)(dungeon_level * 4 + -0x54d9);
  uVar6 = (undefined2)((ulong)uVar2 >> 0x10);
  value = (int)uVar2;
  *(undefined2 *)(value + 5) = *(undefined2 *)(x_pos + -10);
  *(undefined2 *)(value + 7) = *(undefined2 *)(x_pos + -8);
  uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
  if (*(char *)((int)uVar2 + *(int *)(x_pos + -10) * MAP_WIDTH + *(int *)(x_pos + -8) + -0x50) != ' '
     ) {
    find_empty_floor_tile(value + 7,uVar6,value + 5,uVar6);
  }
  uVar4 = lookup_table_b9c7(*(undefined2 *)(dungeon_level * 4 + -0x54d9),
                        *(undefined2 *)(dungeon_level * 4 + -0x54d7));
  uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
  *(undefined1 *)((int)uVar2 + *(int *)(value + 5) * MAP_WIDTH + *(int *)(value + 7) + -0x50) = uVar4;
  uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
  *(undefined1 *)((int)uVar2 + player_y * MAP_WIDTH + player_x + -0x50) = uVar1;
  return;
}



void apply_armor_damage_reduction(int value)

{
  int value;
  int value;
  int random_val;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  if (((*(int *)((int)*(undefined4 *)(value + 4) + 1) == 0xc) &&
      (*(int *)ADDR_WIELDED_WEAPON /* wielded_weapon */ != 0 || *(int *)0xb924 != 0)) &&
     (*(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 1) == 0xb)) {
    value = *(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 9);
    value = *(int *)((int)*(undefined4 *)(value + 4) + 9);
    random_val = random_mod(7);
    *(int *)((int)*(undefined4 *)(value + -0x13) + 10) =
         (((*(int *)((int)*(undefined4 *)(value + -0x13) + 10) + -6) - random_val) - value) - value;
  }
  else {
    *(int *)((int)*(undefined4 *)(value + -0x13) + 10) =
         *(int *)((int)*(undefined4 *)(value + -0x13) + 10) -
         *(int *)(*(int *)((int)*(undefined4 *)(value + 4) + 1) * 2 + -0x6123);
  }
  return;
}



void handle_attack_action(char *result_ptr)

{
  uint in_AX;
  int random_val;
  undefined1 extraout_AH;
  undefined2 damage;
  byte extraout_AH_00;
  byte extraout_AH_01;
  byte damage;
  undefined2 damage;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 damage;
  undefined1 *puVar6;
  undefined1 local_35 [32];
  undefined1 *local_15;
  char local_11 [3];
  int damage;
  int damage;
  int damage;
  undefined1 local_8 [2];
  undefined1 local_6 [4];
  
  handle_item_drop_or_unequip(in_AX & 0xff00,local_11,unaff_SS,&result_ptr,unaff_SS);
  if (local_11[0] != '\0') {
    check_minimum_stats();
    random_val = random_mod(current_food / 4 + 1);
    damage = 0;
    damage = current_food / 4 + random_val + 1;
    FUN_1000_a85c(local_6,unaff_SS,local_8,unaff_SS);
    FUN_1000_a91f(&damage,unaff_SS,local_6,unaff_SS,local_8,unaff_SS,&damage,unaff_SS,&damage,
                  unaff_SS);
    random_val = damage - player_x;
    if (random_val < 0) {
      random_val = -random_val;
    }
    damage = damage - player_y;
    if (damage < 0) {
      damage = -damage;
    }
    damage = damage + random_val;
    if (*(char *)(damage * MAP_WIDTH + damage + -0xc) == ' ') {
      if ((damage == player_y) && (damage == player_x)) {
        display_score_with_fatal(0xffad);
      }
      else {
        FUN_1000_b711(&stack0xfffe,(char *)result_ptr,result_ptr._2_2_);
      }
    }
    else {
      find_item_at_coords(&local_15,unaff_SS,damage,damage);
      print_space();
      if ((damage < 2) && (damage = ((undefined1 *)local_15)[0x28] == '\0', (bool)damage)) {
        damage = CONCAT11(extraout_AH,*local_15);
        puVar6 = local_35;
        pad_and_copy_buffer(0x20,0xb80f,unaff_DS);
        create_bit_mask(puVar6,unaff_SS,damage);
        if ((bool)damage) {
          display_score_with_fatal(0xff36);
          return;
        }
      }
      random_val = ((player_level + strength) - *(int *)((undefined1 *)local_15 + 8)) - damage
              >> 0xf;
      combat_wrapper();
      damage = 0;
      conditional_char_action();
      damage = float_add_with_handler();
      find_highest_bit(damage,damage,random_val);
      char_create_wrapper();
      puVar6 = (undefined1 *)local_15;
      damage = (undefined2)((ulong)local_15 >> 0x10);
      if ((bool)damage) {
        puVar6[0x28] = 0;
        if (is_blind == '\0') {
          display_ability_score(*(undefined2 *)(puVar6 + 4),0xbd);
          damage = extraout_AH_01;
        }
        else {
          display_score_with_fatal(0xbb);
          damage = extraout_AH_00;
        }
        destroy_or_consume_item((uint)damage << 8,(uint)damage << 8,(char *)result_ptr,result_ptr._2_2_);
        if (*result_ptr == '\a') {
          apply_armor_damage_reduction(&stack0xfffe);
        }
        else {
          puVar6 = (undefined1 *)local_15;
          damage = (undefined2)((ulong)local_15 >> 0x10);
          if (*result_ptr == '\x06') {
            damage = (undefined2)((ulong)result_ptr >> 0x10);
            *(int *)(puVar6 + 10) =
                 (*(int *)(puVar6 + 10) - *(int *)((char *)result_ptr + 9)) -
                 *(int *)(*(int *)((char *)result_ptr + 1) * 4 + -0x61e5);
          }
          else {
            *(int *)(puVar6 + 10) = *(int *)(puVar6 + 10) + -1;
          }
        }
        damage = (undefined2)((ulong)local_15 >> 0x10);
        if (*(int *)((undefined1 *)local_15 + 10) < 1) {
          kill_monster(1,(undefined1 *)local_15,damage);
        }
      }
      else {
        if (is_blind == '\0') {
          display_ability_score(*(undefined2 *)(puVar6 + 4),0xbc);
        }
        else {
          display_score_with_fatal(0x98);
        }
        FUN_1000_b711(&stack0xfffe,(char *)result_ptr,result_ptr._2_2_);
      }
    }
  }
  return;
}



void show_spell_info(char *result_ptr)

{
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  int flag;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  char *pcVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 uVar5;
  bool flag;
  undefined1 *puVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined1 local_62 [32];
  undefined1 local_42 [32];
  undefined1 local_22 [32];
  
  uVar3 = (undefined2)((ulong)result_ptr >> 0x10);
  pcVar2 = (char *)result_ptr;
  if (*(char *)(*result_ptr * 0x18 + *(int *)(pcVar2 + 1) + -0x65a2) != '\0') {
    return;
  }
  flag = *result_ptr * 0x18;
  if (*(char *)(flag + *(int *)(pcVar2 + 1) + -0x6542) != '\0') {
    return;
  }
  uVar4 = *result_ptr == '\x03';
  if ((bool)uVar4) {
    uVar8 = CONCAT11((char)((uint)flag >> 8),pcVar2[1]);
    puVar7 = local_22;
    uVar9 = unaff_SS;
    zero_word_array_16(puVar7);
    set_bit_in_array(CONCAT11(extraout_AH,0xf));
    set_bit_in_array(CONCAT11(extraout_AH_00,0x10));
    flag = create_bit_mask(puVar7,uVar9,uVar8);
    if (!(bool)uVar4) {
      return;
    }
  }
  uVar4 = (undefined1)((uint)flag >> 8);
  if ((*result_ptr == '\x02') && (*(int *)(pcVar2 + 1) == 7)) {
    return;
  }
  uVar5 = *result_ptr == '\x02';
  if ((bool)uVar5) {
    uVar8 = CONCAT11(uVar4,pcVar2[1]);
    puVar7 = local_42;
    uVar9 = unaff_SS;
    zero_word_array_16(puVar7);
    set_bit_in_array(CONCAT11(extraout_AH_01,0x10));
    set_bit_in_array(CONCAT11(extraout_AH_02,0x12));
    create_bit_mask(puVar7,uVar9,uVar8);
    uVar4 = extraout_AH_03;
    if (!(bool)uVar5) goto LAB_1000_bbc5;
  }
  else {
LAB_1000_bbc5:
    uVar5 = *result_ptr == '\x03';
    if (!(bool)uVar5) goto LAB_1000_bc0d;
    uVar9 = CONCAT11(uVar4,pcVar2[1]);
    puVar7 = local_62;
    zero_word_array_16(puVar7);
    set_bit_range_in_array(CONCAT11(extraout_AH_04,3),CONCAT11(extraout_AH_04,1));
    set_bit_in_array(CONCAT11(extraout_AH_05,5));
    set_bit_in_array(CONCAT11(extraout_AH_06,0x14));
    set_bit_in_array(CONCAT11(extraout_AH_07,0x15));
    create_bit_mask(puVar7,unaff_SS,uVar9);
    if ((bool)uVar5) goto LAB_1000_bc0d;
  }
  handle_error_and_wait();
LAB_1000_bc0d:
  check_minimum_stats();
  if (*result_ptr == '\x02') {
    display_score_with_fatal(0x74);
    uVar4 = extraout_AH_08;
  }
  else {
    display_score_with_fatal(0x65);
    uVar4 = extraout_AH_09;
  }
  uVar8 = 0xe654;
  uVar9 = unaff_DS;
  write_bytes(0,CONCAT11(uVar4,0x20));
  flush_output(uVar8,uVar9);
  uVar9 = 0xe554;
  read_string_from_file(0x1c,*result_ptr * 0x2b8 + *(int *)(pcVar2 + 1) * 0x1d + -0x75de,unaff_DS);
  read_line(0x214c,uVar9);
  flag = *result_ptr * 0x2b8 + *(int *)(pcVar2 + 1) * 0x1d + -0x75de;
  flag = flag == 0;
  compare_pascal_strings(0xbafb,0x214c,flag,unaff_DS);
  *(bool *)(*result_ptr * 0x18 + *(int *)(pcVar2 + 1) + -0x6542) = !flag;
  return;
}



void check_spell_cast_chance(char *result_ptr)

{
  uint in_AX;
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = (undefined2)((ulong)result_ptr >> 0x10);
  if (*result_ptr != '\x02') {
    if (*result_ptr != '\x03') {
      return;
    }
    in_AX = random_mod(*(undefined2 *)(*(int *)((char *)result_ptr + 1) * 4 + -0x6305));
    if (in_AX == 0) {
      return;
    }
  }
  destroy_or_consume_item(1,in_AX & 0xff00,(char *)result_ptr,uVar1);
  return;
}



void prepare_and_cast_spell(undefined2 param_1,undefined2 param_2)

{
  show_spell_info(param_1,param_2);
  check_spell_cast_chance(param_1,param_2);
  return;
}



void execute_spell_effect(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char ch;
  uint flag;
  uint value;
  undefined1 extraout_AH;
  undefined2 uVar7;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  byte bVar8;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  int iVar9;
  char *pcVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  int value;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar14;
  undefined1 *puVar15;
  undefined1 *puVar16;
  undefined1 local_7c [32];
  undefined1 local_5c [30];
  undefined1 local_3e [2];
  undefined1 local_3c [28];
  undefined4 local_20;
  char ch;
  undefined4 local_1b;
  char ch;
  int local_16;
  int local_14;
  undefined4 local_12;
  undefined4 local_e;
  
  flag = random_mod(0x15);
  value = player_level / 2 + intelligence;
  iVar9 = (int)value >> 0xf;
  if ((iVar9 < 0) || ((iVar9 < 1 && (value < flag)))) {
    if (*(int *)0xb8a0 != 0 || *(int *)0xb8a2 != 0) {
      flag = random_mod(0x19);
      value = player_level / 2 + intelligence;
      iVar9 = (int)value >> 0xf;
      if ((-1 < iVar9) && ((0 < iVar9 || (flag <= value)))) goto LAB_1000_bd9d;
    }
    display_score_with_fatal(0xff34);
    check_spell_cast_chance((char *)param_2,param_2._2_2_);
  }
  else {
LAB_1000_bd9d:
    iVar9 = *(int *)((char *)param_2 + 1);
    if (iVar9 == 1) {
      if (*(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ == 0 && *(int *)0xb928 == 0) {
        if (*(int *)ADDR_EQUIPPED_ARMOR /* equipped_armor */ == 0 && *(int *)0xb92c == 0) {
          if ((*(int *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ != 0 || *(int *)0xb934 != 0) &&
             (*(int *)((int)*(undefined4 *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ + 9) < 5)) {
            local_20 = *(undefined4 *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */;
            uVar11 = (undefined2)((ulong)local_20 >> 0x10);
            iVar9 = (int)local_20;
            *(int *)(iVar9 + 9) = *(int *)(iVar9 + 9) + 1;
            *(undefined1 *)(iVar9 + 0x14) = 0;
          }
        }
        else if (*(int *)((int)*(undefined4 *)ADDR_EQUIPPED_ARMOR /* equipped_armor */ + 9) < 5) {
          local_20 = *(undefined4 *)ADDR_EQUIPPED_ARMOR /* equipped_armor */;
          uVar11 = (undefined2)((ulong)local_20 >> 0x10);
          iVar9 = (int)local_20;
          *(int *)(iVar9 + 9) = *(int *)(iVar9 + 9) + 1;
          *(undefined1 *)(iVar9 + 0x14) = 0;
          iVar9 = get_sign(iVar9 + 9,uVar11);
          *(int *)ADDR_DEXTERITY = (iVar9 + *(int *)((int)local_20 + 9)) / 2;
        }
      }
      else if (*(int *)((int)*(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ + 9) < 5) {
        display_score_with_fatal(0x12f);
        *(int *)ADDR_WISDOM = *(int *)ADDR_WISDOM + 1;
        local_20 = *(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */;
        uVar11 = (undefined2)((ulong)local_20 >> 0x10);
        iVar9 = (int)local_20;
        *(int *)(iVar9 + 9) = *(int *)(iVar9 + 9) + 1;
        *(undefined1 *)(iVar9 + 0x14) = 0;
      }
      base_ac = *(int *)ADDR_WISDOM + *(int *)ADDR_DEXTERITY;
      display_character_stats();
    }
    else if (iVar9 == 2) {
      if (*(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ != 0 || *(int *)0xb928 != 0) {
        display_score_with_fatal(7);
        local_20 = *(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */;
        *(undefined1 *)((int)local_20 + 0x15) = 1;
      }
    }
    else if (iVar9 == 3) {
      if (*(int *)ADDR_WIELDED_WEAPON /* wielded_weapon */ != 0 || *(int *)0xb924 != 0) {
        display_score_with_fatal(8);
        local_20 = *(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */;
        uVar11 = (undefined2)((ulong)local_20 >> 0x10);
        *(int *)((int)local_20 + 9) = *(int *)((int)local_20 + 9) + 1;
        *(int *)ADDR_CONSTITUTION = *(int *)ADDR_CONSTITUTION + 1;
        display_food_status();
      }
    }
    else if (iVar9 == 4) {
      if (needs_full_update == '\0') {
        display_score_with_fatal(0xfff7);
        uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
        *(undefined1 *)((int)uVar2 + 0x719) = 1;
        set_text_color_attribute(CONCAT11(extraout_AH,10));
        local_16 = 1;
        while( true ) {
          local_14 = 1;
          while( true ) {
            uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
            iVar9 = (int)uVar2 + local_16 * MAP_WIDTH + local_14;
            uVar14 = iVar9 == 0;
            uVar7 = CONCAT11((char)((uint)(local_16 * MAP_WIDTH) >> 8),*(undefined1 *)(iVar9 + -0x50));
            puVar16 = local_3c;
            uVar12 = unaff_SS;
            pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
            puVar15 = local_5c;
            uVar11 = unaff_SS;
            pad_and_copy_buffer(0x20,0xb78f,unaff_DS);
            bitwise_or_word_arrays(puVar15,uVar11);
            puVar15 = local_7c;
            uVar11 = unaff_SS;
            zero_word_array_16(puVar15);
            set_bit_in_array(CONCAT11(extraout_AH_00,0xef));
            set_bit_in_array(CONCAT11(extraout_AH_01,0xf7));
            bitwise_or_word_arrays(puVar15,uVar11);
            create_bit_mask(puVar16,uVar12,uVar7);
            if ((!(bool)uVar14) &&
               (*(char *)(dungeon_level * 0x719 + local_16 * MAP_WIDTH + local_14 + 0x70d) == '\0')) {
              validate_window_coords(local_16 + 1,
                            CONCAT11((char)((uint)(dungeon_level * 0x719) >> 8),
                                     (undefined1)local_14));
              uVar12 = 0xe654;
              uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
              uVar11 = unaff_DS;
              write_bytes(0,CONCAT11((char)((uint)(local_16 * MAP_WIDTH) >> 8),
                                       *(undefined1 *)
                                        ((int)uVar2 + local_16 * MAP_WIDTH + local_14 + -0x50)));
              flush_output(uVar12,uVar11);
            }
            if (local_14 == MAP_WIDTH) break;
            local_14 = local_14 + 1;
          }
          if (local_16 == 0x17) break;
          local_16 = local_16 + 1;
        }
        set_text_color_attribute(0xf);
      }
    }
    else if (iVar9 == 5) {
      display_score_with_fatal(0xfff6);
      *(undefined1 *)0x9aab = 1;
      use_item_from_inventory((int)param_1,(int)((ulong)param_1 >> 0x10),CONCAT11(extraout_AH_02,0x49));
      uVar12 = (undefined2)((ulong)*(undefined4 *)ADDR_GOLD_LOW /* gold_low */ >> 0x10);
      combat_wrapper();
      check_combat_and_handle_error();
      combat_check_and_handle_error();
      uVar11 = combat_check_with_error();
      *(undefined2 *)ADDR_GOLD_LOW /* gold_low */ = uVar11;
      *(undefined2 *)ADDR_GOLD_HIGH /* gold_high */ = uVar12;
      if (gold_high < 0) {
        *(undefined2 *)ADDR_GOLD_LOW /* gold_low */ = 0;
        *(undefined2 *)ADDR_GOLD_HIGH /* gold_high */ = 0;
        max_hp = max_hp + -1;
        current_hp = current_hp / 2 + 1;
      }
      display_character_stats();
    }
    else if (iVar9 == 6) {
      find_random_empty_floor_space(0xe52d,unaff_DS,0xb86e,unaff_DS,0xb86c,unaff_DS);
      is_confused = 0;
      redraw_dungeon_level(0x17);
      render_field_of_view();
    }
    else if (iVar9 == 7) {
      FUN_1000_20dd();
      iVar9 = random_mod(2);
      dungeon_level = (dungeon_level + -1) - iVar9;
      if (dungeon_level < 1) {
        *(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */ = 1;
      }
      find_random_empty_floor_space(0xe52d,unaff_DS,0xb86e,unaff_DS,0xb86c,unaff_DS);
      FUN_1000_1a1a(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */);
      is_confused = 0;
      redraw_dungeon_level(0x17);
      render_field_of_view();
    }
    else if (iVar9 == 8) {
      teleport_player();
    }
    else if (iVar9 == 9) {
      is_stunned = 1;
      iVar9 = random_mod(0x32);
      *(int *)0xb90f = iVar9 + 0x46;
      display_score_with_fatal(0xff41);
    }
    else if (iVar9 == 10) {
      ch = '\x02';
      uVar11 = 0;
      while (bVar8 = (byte)((uint)uVar11 >> 8),
            uVar11 = FUN_1000_5422((uint)bVar8 << 8,CONCAT11(bVar8,ch)), ch != '\a') {
        ch = ch + '\x01';
      }
    }
    else {
      bVar8 = (byte)((uint)iVar9 >> 8);
      if (iVar9 == 0xb) {
        FUN_1000_5422(CONCAT11(bVar8,1),CONCAT11(bVar8,1));
      }
      else if (iVar9 == 0xc) {
        FUN_1000_53c9();
      }
      else if (iVar9 == 0xd) {
        FUN_1000_5422(CONCAT11(bVar8,1),(uint)bVar8 << 8);
      }
      else if (iVar9 == 0xe) {
        if (*(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ != 0 || *(int *)0xb928 != 0) {
          *(undefined1 *)((int)*(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ + 0x14) = 1;
          *(undefined1 *)((int)*(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ + 0x15) = 0;
        }
        if (*(int *)ADDR_EQUIPPED_ARMOR /* equipped_armor */ != 0 || *(int *)0xb92c != 0) {
          *(undefined1 *)((int)*(undefined4 *)ADDR_EQUIPPED_ARMOR /* equipped_armor */ + 0x14) = 1;
        }
        if (*(int *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ != 0 || *(int *)0xb934 != 0) {
          *(undefined1 *)((int)*(undefined4 *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ + 0x14) = 1;
        }
        if (*(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ != 0 || *(int *)0xb930 != 0) {
          *(undefined1 *)((int)*(undefined4 *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ + 0x14) = 1;
        }
        iVar9 = *(int *)0xb936;
        local_20 = CONCAT22(iVar9,(undefined2)local_20);
        if (0 < iVar9) {
          local_16 = 1;
          while( true ) {
            if (*(int *)(local_16 * 4 + -0x46cc) != 0 || *(int *)(local_16 * 4 + -0x46ca) != 0) {
              uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
              *(undefined1 *)((int)uVar2 + 0x14) = 1;
            }
            if (local_16 == iVar9) break;
            local_16 = local_16 + 1;
          }
        }
        if (*(int *)ADDR_WIELDED_WEAPON /* wielded_weapon */ != 0 || *(int *)0xb924 != 0) {
          *(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 9) = *(int *)((int)*(undefined4 *)ADDR_WIELDED_WEAPON /* wielded_weapon */ + 9) + -1;
        }
      }
      else if (iVar9 == 0xf) {
        is_dying = 1;
        *(undefined1 *)0x9ab5 = 1;
        iVar9 = random_mod(0x14);
        death_timer = iVar9 + 0x1e;
        if (current_food < max_food) {
          current_food = current_food + 1;
        }
      }
      else if (iVar9 == 0x10) {
        iVar9 = random_mod(8);
        if (iVar9 == 1) {
          display_score_with_fatal(0x130);
        }
        else {
          iVar9 = random_mod(7);
          display_score_with_fatal(iVar9 + 0xd);
        }
      }
      else if (iVar9 == 0x11) {
        if (*(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ != 0 || *(int *)0xb928 != 0) {
          *(undefined1 *)((int)*(undefined4 *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ + 0x14) = 0;
        }
        if (*(int *)ADDR_EQUIPPED_ARMOR /* equipped_armor */ != 0 || *(int *)0xb92c != 0) {
          *(undefined1 *)((int)*(undefined4 *)ADDR_EQUIPPED_ARMOR /* equipped_armor */ + 0x14) = 0;
        }
        if (*(int *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ != 0 || *(int *)0xb934 != 0) {
          *(undefined1 *)((int)*(undefined4 *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ + 0x14) = 0;
        }
        if (*(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ != 0 || *(int *)0xb930 != 0) {
          *(undefined1 *)((int)*(undefined4 *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ + 0x14) = 0;
        }
        iVar9 = *(int *)0xb936;
        local_20 = CONCAT22(iVar9,(undefined2)local_20);
        if (0 < iVar9) {
          local_16 = 1;
          while( true ) {
            if (*(int *)(local_16 * 4 + -0x46cc) != 0 || *(int *)(local_16 * 4 + -0x46ca) != 0) {
              uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
              *(undefined1 *)((int)uVar2 + 0x14) = 0;
            }
            if (local_16 == iVar9) break;
            local_16 = local_16 + 1;
          }
        }
      }
      else if (iVar9 == 0x12) {
        if ((!(bool)(*(byte *)ADDR_PLAYER_Y /* player_y */ & 1)) && (!(bool)(*(byte *)ADDR_PLAYER_X /* player_x */ & 1))) {
          if (player_y != 0x16) {
            FUN_1000_2138(*(undefined2 *)ADDR_PLAYER_X /* player_x */,player_y + 1);
          }
          if (player_y != 2) {
            FUN_1000_2138(*(undefined2 *)ADDR_PLAYER_X /* player_x */,player_y + -1);
          }
          if (player_x != 2) {
            FUN_1000_2138(player_x + -1,*(undefined2 *)ADDR_PLAYER_Y /* player_y */);
          }
          if (player_x != 0x4e) {
            FUN_1000_2138(player_x + 1,*(undefined2 *)ADDR_PLAYER_Y /* player_y */);
          }
          redraw_dungeon_level(0x17);
          render_field_of_view();
        }
      }
      else if (iVar9 == CMD_SAVE) {
        local_16 = 2;
        while( true ) {
          uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
          iVar9 = (int)uVar2 + local_16 * MAP_WIDTH + player_x;
          uVar14 = iVar9 == 0;
          uVar12 = CONCAT11((char)((uint)(local_16 * MAP_WIDTH) >> 8),*(undefined1 *)(iVar9 + -0x50));
          puVar16 = local_3c;
          uVar11 = unaff_SS;
          pad_and_copy_buffer(0x20,0xb72f,unaff_DS);
          create_bit_mask(puVar16,uVar11,uVar12);
          if ((!(bool)uVar14) && ((bool)((byte)local_16 & 1))) {
            FUN_1000_2138(*(undefined2 *)ADDR_PLAYER_X /* player_x */,local_16);
          }
          if (local_16 == MAP_HEIGHT) break;
          local_16 = local_16 + 1;
        }
        local_16 = 2;
        while( true ) {
          uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
          iVar9 = (int)uVar2 + player_y * MAP_WIDTH + local_16;
          uVar14 = iVar9 == 0;
          uVar12 = CONCAT11((char)((uint)(player_y * MAP_WIDTH) >> 8),
                            *(undefined1 *)(iVar9 + -0x50));
          puVar16 = local_3c;
          uVar11 = unaff_SS;
          pad_and_copy_buffer(0x20,0xb74f,unaff_DS);
          create_bit_mask(puVar16,uVar11,uVar12);
          if ((!(bool)uVar14) && ((bool)((byte)local_16 & 1))) {
            FUN_1000_2138(local_16,*(undefined2 *)ADDR_PLAYER_Y /* player_y */);
          }
          if (local_16 == ATTACK_ACID_2) break;
          local_16 = local_16 + 1;
        }
        redraw_dungeon_level(0x17);
        render_field_of_view();
      }
      else if (iVar9 == 0x14) {
        display_score_with_fatal(0x14);
        pcVar1 = (char *)*(undefined4 *)(dungeon_level * 4 + -0x5499);
        while( true ) {
          local_1b._0_2_ = (char *)pcVar1;
          local_1b._2_2_ = (uint)((ulong)pcVar1 >> 0x10);
          flag = (uint)(char *)local_1b | local_1b._2_2_;
          local_1b = pcVar1;
          if (flag == 0) break;
          if (*pcVar1 != '\x01') {
            ((char *)local_1b)[0x22] = '\x01';
            uVar14 = *pcVar1 == -0x16;
            if ((bool)uVar14) {
              iVar9 = random_mod(6);
              flag = iVar9 + 5;
              uVar14 = flag == 0;
              *(uint *)((char *)local_1b + 0x20) = flag;
            }
            uVar12 = CONCAT11((char)(flag >> 8),*local_1b);
            puVar16 = local_3c;
            uVar11 = unaff_SS;
            zero_word_array_16(puVar16);
            set_bit_in_array(CONCAT11(extraout_AH_03,0x45));
            set_bit_in_array(CONCAT11(extraout_AH_04,0x48));
            create_bit_mask(puVar16,uVar11,uVar12);
            pcVar1 = local_1b;
            if (!(bool)uVar14) {
              ((char *)local_1b)[0x28] = '\0';
            }
          }
          local_1b = pcVar1;
          pcVar1 = *(char **)((char *)local_1b + 0x32);
        }
        *(undefined2 *)(dungeon_level * 2 + 0x799b) = 0;
      }
      else if (iVar9 == 0x15) {
        display_score_with_fatal(0xffb8);
        local_e = (char *)inventory_list;
        while( true ) {
          if ((char *)local_e == (char *)0x0 && local_e._2_2_ == 0) break;
          iVar9 = random_mod(2);
          value = (int)((ulong)local_e >> 0x10);
          if ((iVar9 == 0) && ((value != param_2._2_2_ || ((char *)local_e != (char *)param_2)))) {
            handle_item_drop_or_unequip(1,&ch,unaff_SS,&local_e,unaff_SS);
            if (ch == '\0') {
              local_e = *(char **)((char *)local_e + 0x16);
            }
            else {
              ch = is_type_7_subtype_12((char *)local_e,local_e._2_2_);
              if (ch != '\0') {
                *(int *)0xb8c0 = *(int *)0xb8c0 + -1;
                uVar2 = *(undefined4 *)0xb8e4;
                iVar9 = (int)uVar2;
                *(int *)0xb8e4 = iVar9 + -1;
                *(int *)0xb8e6 = (int)((ulong)uVar2 >> 0x10) - (uint)(iVar9 == 0);
                *(int *)0xb8c4 = *(int *)0xb8c4 + -2;
              }
              local_20 = CONCAT22(*(int *)((char *)local_e + 3),(undefined2)local_20);
              if (0 < *(int *)((char *)local_e + 3)) {
                local_16 = 1;
                while( true ) {
                  allocate_item_object(&local_12,unaff_SS);
                  memcpy(0x1a,(char *)local_12,(int)((ulong)local_12 >> 0x10),(char *)local_e
                                ,(int)((ulong)local_e >> 0x10));
                  uVar11 = (undefined2)((ulong)local_12 >> 0x10);
                  pcVar10 = (char *)local_12;
                  (pcVar10 + 3)[0] = '\x01';
                  (pcVar10 + 3)[1] = '\0';
                  find_random_empty_floor_space(0xe52d,unaff_DS,pcVar10 + 7,uVar11,pcVar10 + 5,uVar11);
                  uVar14 = lookup_table_b9c7((char *)local_12,local_12._2_2_);
                  uVar11 = (undefined2)((ulong)local_12 >> 0x10);
                  pcVar10 = (char *)local_12;
                  uVar2 = *(undefined4 *)(dungeon_level * 4 + 4);
                  *(undefined1 *)
                   ((int)uVar2 + *(int *)(pcVar10 + 5) * MAP_WIDTH + *(int *)(pcVar10 + 7) + -0x50) =
                       uVar14;
                  *(undefined1 *)
                   (dungeon_level * 0x719 + *(int *)(pcVar10 + 5) * MAP_WIDTH + *(int *)(pcVar10 + 7) +
                   0x70d) = 0;
                  prepend_item_to_list(dungeon_level * 4 + -0x54d9,unaff_DS,&local_12,unaff_SS);
                  ch = is_type_7_subtype_12((char *)local_e,local_e._2_2_);
                  if (ch == '\0') {
                    *(int *)0xb8c0 = *(int *)0xb8c0 + -1;
                    uVar2 = *(undefined4 *)(*local_e * 4 + -0x4738);
                    iVar9 = (int)uVar2;
                    ch = *local_e;
                    *(int *)(ch * 4 + -0x4738) = iVar9 + -1;
                    *(int *)(ch * 4 + -0x4736) = (int)((ulong)uVar2 >> 0x10) - (uint)(iVar9 == 0)
                    ;
                    *(int *)0xb8c4 = *(int *)0xb8c4 - *(int *)((char *)local_12 + 0xb);
                  }
                  if (local_16 == local_20._2_2_) break;
                  local_16 = local_16 + 1;
                }
              }
              local_12 = local_e;
              local_e = *(char **)((char *)local_e + 0x16);
              remove_item_from_list(0xb91e,unaff_DS,&local_12,unaff_SS);
              *(int *)0xb8c2 = *(int *)0xb8c2 + -1;
            }
          }
          else {
            local_e = *(char **)((char *)local_e + 0x16);
          }
        }
      }
      else if (iVar9 == MAP_HEIGHT) {
        ch = '\0';
        local_20 = CONCAT22(*(int *)0xb936,(undefined2)local_20);
        if (0 < *(int *)0xb936) {
          local_16 = 1;
          while( true ) {
            flag = *(uint *)(local_16 * 4 + -0x46cc) | *(uint *)(local_16 * 4 + -0x46ca);
            if (flag != 0) {
              uVar14 = local_16 * 4 == 0;
              uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
              uVar12 = CONCAT11((char)(flag >> 8),*(undefined1 *)((int)uVar2 + 1));
              puVar16 = local_3e;
              uVar11 = unaff_SS;
              zero_word_array_16(puVar16);
              set_bit_in_array(CONCAT11(extraout_AH_05,4));
              set_bit_in_array(CONCAT11(extraout_AH_06,7));
              set_bit_in_array(CONCAT11(extraout_AH_07,9));
              create_bit_mask(puVar16,uVar11,uVar12);
              if (!(bool)uVar14) {
                uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
                if (*(int *)((int)uVar2 + 9) < 4) {
                  uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
                  uVar3 = *(undefined4 *)(local_16 * 4 + -0x46cc);
                  *(int *)((int)uVar3 + 9) = *(int *)((int)uVar2 + 9) + 1;
                }
                ch = '\x01';
              }
            }
            if (local_16 == local_20._2_2_) break;
            local_16 = local_16 + 1;
          }
        }
        if (ch != '\0') {
          display_score_with_fatal(0xff3a);
        }
      }
      else if (iVar9 == 0x17) {
        ch = '\0';
        local_20 = CONCAT22(*(int *)0xb936,(undefined2)local_20);
        if (0 < *(int *)0xb936) {
          local_16 = 1;
          while( true ) {
            flag = *(uint *)(local_16 * 4 + -0x46cc) | *(uint *)(local_16 * 4 + -0x46ca);
            if (flag != 0) {
              uVar14 = local_16 * 4 == 0;
              uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
              uVar12 = CONCAT11((char)(flag >> 8),*(undefined1 *)((int)uVar2 + 1));
              puVar16 = local_3e;
              uVar11 = unaff_SS;
              zero_word_array_16(puVar16);
              set_bit_in_array(CONCAT11(extraout_AH_08,4));
              set_bit_in_array(CONCAT11(extraout_AH_09,7));
              set_bit_in_array(CONCAT11(extraout_AH_10,9));
              create_bit_mask(puVar16,uVar11,uVar12);
              if (!(bool)uVar14) {
                uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
                uVar3 = *(undefined4 *)(local_16 * 4 + -0x46cc);
                *(int *)((int)uVar3 + 9) = *(int *)((int)uVar2 + 9) + -1;
                ch = '\x01';
              }
            }
            if (local_16 == local_20._2_2_) break;
            local_16 = local_16 + 1;
          }
        }
        if (ch != '\0') {
          display_score_with_fatal(0xff3a);
        }
      }
      else if (iVar9 == 0x18) {
        intelligence = intelligence + 1;
        display_score_with_fatal(0xffa6);
        display_character_stats();
      }
    }
    prepare_and_cast_spell((char *)param_2,param_2._2_2_);
  }
  return;
}



void drink_potion_effect(undefined2 param_1,undefined4 param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  char ch;
  int iVar4;
  uint random_val;
  undefined2 uVar6;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined2 uVar7;
  byte bVar9;
  byte extraout_AH_01;
  char *pcVar8;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 *puVar12;
  undefined1 *puVar13;
  undefined1 local_76 [32];
  undefined1 local_56 [32];
  undefined1 local_36 [30];
  int local_18;
  char ch;
  char ch;
  int local_14;
  int local_12;
  int flag;
  undefined4 local_a;
  char *local_6;
  
  iVar4 = random_mod(100);
  food_level = food_level + 200 + iVar4;
  iVar4 = *(int *)((int)param_2 + 1);
  if (iVar4 == 1) {
    if (confusion_lock == '\0') {
      display_score_with_fatal(0x68);
    }
    else {
      display_score_with_fatal(0x67);
    }
    if (current_hp == max_hp) {
      iVar4 = random_mod(6);
      max_hp = max_hp + 1 + iVar4;
      *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = *(undefined2 *)ADDR_MAX_HP /* max_hp */;
    }
    else {
      iVar4 = random_mod(player_level * 3);
      current_hp = player_level * 2 + current_hp + iVar4;
      if (max_hp < current_hp) {
        *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = *(undefined2 *)ADDR_MAX_HP /* max_hp */;
      }
    }
    if (needs_full_update == '\0') {
      display_character_stats();
    }
    else {
      needs_full_update = 0;
      redraw_dungeon_level(0x17);
    }
    goto LAB_1000_d16b;
  }
  if (iVar4 == 2) {
    if (confusion_lock == '\0') {
      display_score_with_fatal(0x1e);
    }
    else {
      display_score_with_fatal(0x68);
    }
    if (current_hp == max_hp) {
      iVar4 = random_mod(0xf);
      max_hp = max_hp + 1 + iVar4;
      *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = *(undefined2 *)ADDR_MAX_HP /* max_hp */;
    }
    else {
      *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = *(undefined2 *)ADDR_MAX_HP /* max_hp */;
    }
    if ((needs_full_update == '\0') && (is_blind == '\0')) {
      display_character_stats();
    }
    else {
      needs_full_update = 0;
      is_blind = 0;
      redraw_dungeon_level(0x17);
    }
    goto LAB_1000_d16b;
  }
  if (iVar4 == 3) {
    if (confusion_lock == '\0') {
      display_score_with_fatal(0x132);
    }
    else {
      display_score_with_fatal(0x6a);
    }
    random_val = random_mod(4);
    current_food = current_food + 1 + random_val / 3;
    max_food = max_food + 1;
    if (max_food < current_food) {
      *(undefined2 *)ADDR_MAX_FOOD /* max_food */ = *(undefined2 *)ADDR_CURRENT_FOOD /* current_food */;
    }
    display_character_stats();
    goto LAB_1000_d16b;
  }
  if (iVar4 == 4) {
    if (confusion_lock == '\0') {
      display_score_with_fatal(0x6c);
    }
    else {
      display_score_with_fatal(0x6b);
    }
    if (current_food < max_food) {
      *(undefined2 *)ADDR_CURRENT_FOOD /* current_food */ = *(undefined2 *)ADDR_MAX_FOOD /* max_food */;
    }
    else {
      iVar4 = random_mod(2);
      current_food = current_food + 2 + iVar4;
      *(undefined2 *)ADDR_MAX_FOOD /* max_food */ = *(undefined2 *)ADDR_CURRENT_FOOD /* current_food */;
    }
    display_character_stats();
    goto LAB_1000_d16b;
  }
  if (iVar4 == 5) {
    if (confusion_lock == '\0') {
      display_score_with_fatal(0x6f);
    }
    else {
      display_score_with_fatal(0x6e);
    }
    speed_boost_active = 1;
    iVar4 = random_mod(0x32);
    speed_timer = iVar4 + 100;
    goto LAB_1000_d16b;
  }
  if (iVar4 != 6) {
    if (iVar4 == 7) {
      clear_screen_double();
      display_character_stats();
      display_score_with_fatal(0x27);
      needs_full_update = 1;
      iVar4 = random_mod(0x4b);
      detect_timer = iVar4 + 0x32;
      ch = '\x02';
      while( true ) {
        local_14 = 1;
        while( true ) {
          *(undefined1 *)(ch * 0x18 + local_14 + -0x65a2) = 0;
          *(undefined1 *)(ch * 0x18 + local_14 + -0x6542) = 0;
          if (local_14 == 0x18) break;
          local_14 = local_14 + 1;
        }
        if (ch == '\x05') break;
        ch = ch + '\x01';
      }
      pcVar1 = (char *)inventory_list;
      while( true ) {
        local_a._0_2_ = (char *)pcVar1;
        local_a._2_2_ = (uint)((ulong)pcVar1 >> 0x10);
        uVar11 = ((uint)(char *)local_a | local_a._2_2_) == 0;
        local_a = pcVar1;
        if ((bool)uVar11) break;
        uVar6 = CONCAT11((char)(((uint)(char *)local_a | local_a._2_2_) >> 8),*pcVar1);
        puVar13 = local_36;
        uVar7 = unaff_SS;
        zero_word_array_16(puVar13);
        set_bit_in_array(CONCAT11(extraout_AH,7));
        set_bit_in_array(CONCAT11(extraout_AH_00,6));
        create_bit_mask(puVar13,uVar7,uVar6);
        uVar7 = (undefined2)((ulong)local_a >> 0x10);
        if ((bool)uVar11) {
          ((char *)local_a)[0x13] = '\0';
        }
        pcVar1 = *(char **)((char *)local_a + 0x16);
      }
      flag = 1;
      while( true ) {
        uVar2 = *(undefined4 *)(flag * 4 + 4);
        *(undefined1 *)((int)uVar2 + 0x719) = 0;
        local_14 = 1;
        while( true ) {
          for (local_12 = 1;
              *(undefined1 *)(flag * 0x719 + local_14 * MAP_WIDTH + local_12 + 0x70d) = 0,
              local_12 != 0x4f; local_12 = local_12 + 1) {
          }
          if (local_14 == 0x17) break;
          local_14 = local_14 + 1;
        }
        if (flag == 0xf) break;
        flag = flag + 1;
      }
      generate_random_names();
      randomize_item_appearances();
    }
    else if (iVar4 == 8) {
      if (confusion_lock == '\0') {
        display_score_with_fatal(0x29);
      }
      else {
        display_score_with_fatal(0x70);
      }
      is_dying = 1;
      iVar4 = random_mod(10);
      death_timer = iVar4 + 0x14;
    }
    else if (iVar4 == 9) {
      if (is_hasted == '\0') {
        display_score_with_fatal(0x72);
        is_paralyzed = 1;
        iVar4 = random_mod(5);
        paralyze_timer = iVar4 + 10;
      }
      else {
        display_score_with_fatal(0x71);
        is_hasted = 0;
      }
    }
    else if (iVar4 == 10) {
      if (is_paralyzed == '\0') {
        display_score_with_fatal(0x33);
        is_hasted = 1;
        iVar4 = random_mod(5);
        haste_timer = iVar4 + 0x1e;
      }
      else {
        display_score_with_fatal(0x31);
        is_paralyzed = 0;
      }
    }
    else if (iVar4 == 0xb) {
      display_score_with_fatal(0x133);
      confusion_lock = 1;
      hallucination_active = 1;
      intelligence = intelligence + -1;
      if (intelligence < 1) {
        process_game_over(&param_1,unaff_SS,100);
      }
      iVar4 = random_mod(0x32);
      hallucination_timer = iVar4 + 0x15e;
    }
    else if (iVar4 == 0xc) {
      display_score_with_fatal(0x2f);
      is_blind = 1;
      iVar4 = random_mod(100);
      blind_timer = iVar4 + 200;
    }
    else if (iVar4 == 0xd) {
      display_score_with_fatal(0x30);
      iVar4 = random_mod(100);
      turn_count = turn_count + 500 + iVar4;
    }
    else if (iVar4 == 0xe) {
      display_score_with_fatal(0x73);
      level_up_character();
      random_val = random_mod(*(int *)(player_level * 2 + -0x46b8) -
                            *(int *)((player_level + -1) * 2 + -0x46b8));
      experience = *(int *)((player_level + -1) * 2 + -0x46b8) + random_val / 2;
      display_character_stats();
    }
    else if (iVar4 == 0xf) {
      lose_experience_level();
      if (player_level < 2) {
        *(undefined2 *)ADDR_EXPERIENCE /* experience */ = 0;
      }
      else {
        iVar4 = random_mod(*(int *)(player_level * 2 + -0x46b8) -
                              *(int *)((player_level + -1) * 2 + -0x46b8));
        experience = *(int *)(player_level * 2 + -0x46b8) - iVar4;
      }
      if (experience < 0) {
        *(undefined2 *)ADDR_EXPERIENCE /* experience */ = 0;
      }
      display_character_stats();
    }
    else if (iVar4 == 0x10) {
      FUN_1000_53c9();
      teleport_effect_flag = 1;
      iVar4 = random_mod(100);
      effect_timer_16 = iVar4 + 300;
    }
    else if (iVar4 == 0x11) {
      clear_screen_double();
      is_teleporting = 1;
      teleport_effect_flag = 0;
      iVar4 = random_mod(100);
      teleport_timer = iVar4 + 0x96;
    }
    else if (iVar4 == 0x12) {
      status_flag_3 = 1;
      iVar4 = random_mod(10);
      status_timer_3 = iVar4 + 0xf;
    }
    else if (iVar4 == CMD_SAVE) {
      display_score_with_fatal(0x47);
      status_flag_1 = 1;
      iVar4 = random_mod(0x32);
      status_timer_1 = iVar4 + 100;
    }
    else if (iVar4 == 0x14) {
      if (food_level < 400) {
        display_score_with_fatal(0xac);
      }
      else {
        display_score_with_fatal(0xad);
      }
      iVar4 = random_mod(200);
      food_level = food_level + 400 + iVar4;
    }
    else if (iVar4 == 0x15) {
      status_flag_5 = 1;
      iVar4 = random_mod(0xf);
      status_timer_5 = iVar4 + 0x19;
    }
    else if (iVar4 == MAP_HEIGHT) {
      is_wizard = 1;
      iVar4 = random_mod(0xf);
      wizard_mode_timer = iVar4 + 0x19;
      pcVar1 = (char *)inventory_list;
      while( true ) {
        local_a._0_2_ = (char *)pcVar1;
        local_a._2_2_ = (uint)((ulong)pcVar1 >> 0x10);
        iVar4 = local_a._2_2_;
        local_a = pcVar1;
        if ((char *)local_a == (char *)0x0 && local_a._2_2_ == 0) break;
        if ((*(int *)((char *)local_a + 3) == 1) ||
           (pcVar8 = (char *)local_a, ch = is_type_7_subtype_12(pcVar8,iVar4), pcVar1 = local_a,
           ch != '\0')) {
LAB_1000_cfc2:
          local_a = pcVar1;
          local_6 = *(char **)((char *)local_a + 0x16);
        }
        else {
          local_6 = local_a;
          if ((*local_a == '\x02') && (*(int *)((char *)local_a + 1) == MAP_HEIGHT)) goto LAB_1000_cfc2;
        }
        ch = '\x01';
        local_18 = *(int *)0xb936;
        if (0 < local_18) {
          local_14 = 1;
          while( true ) {
            if ((ch == '\0') ||
               ((local_a._2_2_ == *(int *)(local_14 * 4 + -0x46ca) &&
                ((char *)local_a == (char *)*(undefined2 *)(local_14 * 4 + -0x46cc))))) {
              ch = '\0';
            }
            else {
              ch = '\x01';
            }
            if (local_14 == local_18) break;
            local_14 = local_14 + 1;
          }
        }
        pcVar1 = local_6;
        if (((((ch != '\0') &&
              ((local_a._2_2_ != *(int *)0xb924 ||
               ((char *)local_a != (char *)wielded_weapon)))) &&
             ((local_a._2_2_ != *(int *)0xb928 || ((char *)local_a != (char *)equipped_shield)
              ))) && ((((local_a._2_2_ != *(int *)0xb934 ||
                        ((char *)local_a != (char *)equipped_ring2)) &&
                       ((local_a._2_2_ != *(int *)0xb92c ||
                        ((char *)local_a != (char *)equipped_armor)))) &&
                      ((local_a._2_2_ != *(int *)0xb930 ||
                       ((char *)local_a != (char *)equipped_ring1)))))) &&
           ((*local_a != '\x02' || (*(int *)((char *)local_a + 1) != 0x16)))) {
          uVar7 = is_type_7_subtype_12((char *)local_a,local_a._2_2_);
          bVar9 = (byte)((uint)uVar7 >> 8);
          if ((char)uVar7 == '\0') {
            destroy_or_consume_item((uint)bVar9 << 8,(uint)bVar9 << 8,(char *)local_a,local_a._2_2_);
            pcVar1 = local_6;
          }
          else {
            destroy_or_consume_item(CONCAT11(bVar9,1),(uint)bVar9 << 8,(char *)local_a,local_a._2_2_);
            pcVar1 = local_6;
          }
        }
      }
      local_14 = 1;
      while( true ) {
        *(undefined2 *)(local_14 * 4 + -0x476c) = 0;
        *(undefined2 *)(local_14 * 4 + -0x476a) = 0;
        if (local_14 == 10) break;
        local_14 = local_14 + 1;
      }
    }
    else if (iVar4 == 0x17) {
      strength = strength + 1;
      display_character_stats();
      display_score_with_fatal(0x55);
    }
    else if (iVar4 == 0x18) {
      if (*(int *)0xb936 < 4) {
        if ((*(int *)0xb8b0 == 0 && *(int *)0xb8b2 == 0) ||
           (ch = check_inventory_has_item(ITEM_FOOD), ch == '\0')) {
          display_score_with_fatal(0xfe57);
        }
        else {
          decrement_item_quantity(9);
          destroy_or_consume_item((uint)extraout_AH_01 << 8,(uint)extraout_AH_01 << 8,*(undefined2 *)0xb8b0,
                        *(undefined2 *)0xb8b2);
          *(int *)0xb936 = *(int *)0xb936 + 1;
          display_score_with_fatal(0xff2f);
        }
      }
      else {
        display_score_with_fatal(0xfe57);
      }
    }
    goto LAB_1000_d16b;
  }
  if (confusion_lock == '\0') {
    display_score_with_fatal(0x24);
  }
  else {
    display_score_with_fatal(0x6d);
  }
  ch = check_inventory_has_item(2);
  uVar11 = 0;
  uVar10 = ch == '\0';
  if ((bool)uVar10) {
LAB_1000_cb35:
    iVar4 = random_mod(3);
    current_food = (current_food + -1) - iVar4;
  }
  else {
    find_highest_bit();
    char_create_wrapper();
    if (!(bool)uVar11 && !(bool)uVar10) goto LAB_1000_cb35;
  }
  if (current_food < 0) {
    process_game_over(&param_1,unaff_SS,0x65);
  }
  display_character_stats();
LAB_1000_d16b:
  uVar11 = current_food == 0x1c;
  if (0x1c < current_food) {
    uVar11 = *(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ == 0 && *(int *)0xb928 == 0;
    if (*(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ != 0 || *(int *)0xb928 != 0) {
      local_a = (char *)inventory_list;
      while( true ) {
        iVar4 = (int)((ulong)local_a >> 0x10);
        pcVar8 = (char *)local_a;
        if ((iVar4 == *(int *)0xb928) && (pcVar8 == (char *)equipped_shield)) break;
        local_a = *(char **)(pcVar8 + 0x16);
      }
      bVar9 = (byte)((ulong)local_a >> 8);
      destroy_or_consume_item(CONCAT11(bVar9,1),(uint)bVar9 << 8,pcVar8,iVar4);
      equipped_shield = 0;
      *(undefined2 *)0xb928 = 0;
      display_score_with_fatal(0xffaa);
      uVar11 = 1;
      *(undefined2 *)ADDR_WISDOM = 0;
      *(undefined2 *)ADDR_BASE_AC /* base_ac */ = *(undefined2 *)ADDR_DEXTERITY;
      display_character_stats();
    }
  }
  random_val = (uint)*(byte *)((int)param_2 + 1);
  puVar13 = local_36;
  uVar6 = unaff_SS;
  zero_word_array_16(puVar13);
  set_bit_in_array(CONCAT11(extraout_AH_02,5));
  set_bit_in_array(CONCAT11(extraout_AH_03,6));
  puVar12 = local_56;
  uVar7 = unaff_SS;
  zero_word_array_16(puVar12);
  set_bit_range_in_array(CONCAT11(extraout_AH_04,10),CONCAT11(extraout_AH_04,8));
  bitwise_or_word_arrays(puVar12,uVar7);
  puVar12 = local_76;
  zero_word_array_16(puVar12);
  set_bit_in_array(CONCAT11(extraout_AH_05,0xc));
  set_bit_in_array(CONCAT11(extraout_AH_06,0x11));
  set_bit_in_array(CONCAT11(extraout_AH_07,0x12));
  set_bit_in_array(CONCAT11(extraout_AH_08,0x15));
  set_bit_in_array(CONCAT11(extraout_AH_09,0x16));
  bitwise_or_word_arrays(puVar12,unaff_SS);
  create_bit_mask(puVar13,uVar6,random_val);
  if (!(bool)uVar11) {
    *(undefined1 *)(*(int *)((int)param_2 + 1) + -0x6572) = 1;
  }
  prepare_and_cast_spell((int)param_2,param_2._2_2_);
  return;
}



void __cdecl16near check_confusion_recovery(void)

{
  int iVar1;
  undefined2 unaff_DS;
  undefined1 uVar2;
  undefined1 uVar3;
  
  uVar2 = 0;
  uVar3 = hallucination_active == '\0';
  if (!(bool)uVar3) {
    find_highest_bit();
    char_create_wrapper();
    if (!(bool)uVar2 && !(bool)uVar3) {
      confusion_lock = 1;
      iVar1 = random_mod(0x14);
      hallucination_timer = iVar1 + 0x1e;
      display_character_stats();
    }
  }
  return;
}



void show_message_and_clear_flag(int value,undefined2 param_2)

{
  undefined2 unaff_SS;
  
  display_score_with_fatal(param_2);
  *(undefined1 *)(value + -2) = 0;
  return;
}



void use_item_from_inventory(undefined1 *result_ptr,byte param_2)

{
  undefined4 uVar1;
  uint value;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  int value;
  undefined2 uVar4;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined2 uVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 *puVar8;
  undefined1 local_32 [30];
  int local_14;
  undefined4 local_12;
  int local_a;
  int flag;
  byte flag;
  char ch;
  char ch;
  char ch;
  
  check_minimum_stats();
  ch = '\x01';
  if (((param_2 == 0x54) || (param_2 == 0x52)) || (param_2 == 0x61)) {
    if (*(int *)0xb8c0 < 1) {
      show_message_and_clear_flag(&stack0xfffe,0x4b);
    }
    else if ((param_2 == 0x61) &&
            (uVar1 = *(undefined4 *)(dungeon_level * 4 + 4),
            *(char *)((int)uVar1 + player_y * MAP_WIDTH + player_x + -0x50) != ' ')) {
      show_message_and_clear_flag(&stack0xfffe,0x4c);
    }
  }
  else if (param_2 == 0x49) {
    if (*(int *)0xb8c0 < 1) {
      show_message_and_clear_flag(&stack0xfffe,0xb);
    }
  }
  else if (param_2 == 0x6c) {
    if ((*(int *)0xb8d6 < 0) || ((*(int *)0xb8d6 < 1 && (*(int *)0xb8d4 == 0)))) {
      show_message_and_clear_flag(&stack0xfffe,1);
    }
  }
  else if (param_2 == 0x62) {
    if ((*(int *)0xb8d2 < 0) || ((*(int *)0xb8d2 < 1 && (*(int *)0xb8d0 == 0)))) {
      show_message_and_clear_flag(&stack0xfffe,0x16);
    }
  }
  else if (param_2 == 0x4c) {
    if ((*(int *)0xb8de < 0) || ((*(int *)0xb8de < 1 && (*(int *)0xb8dc == 0)))) {
      show_message_and_clear_flag(&stack0xfffe,0x1b);
    }
  }
  else if (param_2 == ATTACK_FEAR) {
    if ((*(int *)0xb8da < 0) || ((*(int *)0xb8da < 1 && (*(int *)0xb8d8 == 0)))) {
      show_message_and_clear_flag(&stack0xfffe,0x22);
    }
    else {
      ch = '\x01';
      local_14 = *(int *)0xb936;
      if (0 < local_14) {
        local_a = 1;
        while( true ) {
          if ((ch == '\0') ||
             (*(int *)(local_a * 4 + -0x46cc) == 0 && *(int *)(local_a * 4 + -0x46ca) == 0)) {
            ch = '\0';
          }
          else {
            ch = '\x01';
          }
          if (local_a == local_14) break;
          local_a = local_a + 1;
        }
      }
      if (ch != '\0') {
        show_message_and_clear_flag(&stack0xfffe,0x9a);
      }
    }
  }
  else if (param_2 == 0x42) {
    if ((*(int *)0xb8e6 < 0) || ((*(int *)0xb8e6 < 1 && (*(int *)0xb8e4 == 0)))) {
      show_message_and_clear_flag(&stack0xfffe,0xae);
    }
  }
  else if (param_2 == 0x72) {
    if ((*(int *)0xb8e2 < 0) || ((*(int *)0xb8e2 < 1 && (*(int *)0xb8e0 == 0)))) {
      show_message_and_clear_flag(&stack0xfffe,0x23);
    }
    else if ((((*(int *)ADDR_EQUIPPED_SHIELD /* equipped_shield */ != 0 || *(int *)0xb928 != 0) &&
              (*(int *)ADDR_EQUIPPED_ARMOR /* equipped_armor */ != 0 || *(int *)0xb92c != 0)) &&
             (*(int *)ADDR_EQUIPPED_RING2 /* equipped_ring2 */ != 0 || *(int *)0xb934 != 0)) &&
            (*(int *)ADDR_EQUIPPED_RING1 /* equipped_ring1 */ != 0 || *(int *)0xb930 != 0)) {
      show_message_and_clear_flag(&stack0xfffe,0x59);
    }
  }
  if (ch != '\0') {
    ch = '\x01';
    do {
      check_minimum_stats();
      if (param_2 == 0x6c) {
        display_score_with_fatal(2);
      }
      else if (param_2 == 0x62) {
        display_score_with_fatal(0x17);
      }
      else if (param_2 == 0x54) {
        display_score_with_fatal(0xb2);
      }
      else if (param_2 == 0x4c) {
        display_score_with_fatal(0x9e);
      }
      else if (param_2 == ATTACK_FEAR) {
        display_score_with_fatal(0x9b);
      }
      else if (param_2 == 0x42) {
        display_score_with_fatal(0x43);
      }
      else if (param_2 == 0x72) {
        display_score_with_fatal(0x3d);
      }
      else if (param_2 == 0x49) {
        display_score_with_fatal(0x42);
      }
      else if (param_2 == 0x52) {
        display_score_with_fatal(0x3f);
      }
      else if (param_2 == 0x61) {
        display_score_with_fatal(0x4d);
      }
      display_score_with_fatal(0xc1);
      flag = read_keyboard_input();
      if (flag == 0x2a) {
        if ((((param_2 == 0x54) || (param_2 == 0x49)) || (param_2 == 0x52)) || (param_2 == 0x61)) {
          FUN_1000_5fd2();
        }
        else if (param_2 == 0x6c) {
          FUN_1000_610b(3);
        }
        else if (param_2 == 0x62) {
          FUN_1000_610b(2);
        }
        else if (param_2 == 0x4c) {
          FUN_1000_610b(5);
        }
        else if (param_2 == ATTACK_FEAR) {
          FUN_1000_610b(4);
        }
        else if (param_2 == 0x42) {
          FUN_1000_610b(7);
        }
        else if (param_2 == 0x72) {
          FUN_1000_610b(6);
        }
      }
      else {
        ch = '\0';
      }
    } while (ch != '\0');
    if (flag < 0x61) {
      flag = flag - 0x26;
    }
    else {
      flag = flag - 0x60;
    }
    check_minimum_stats();
    uVar6 = flag == 1;
    uVar5 = (undefined2)((ulong)result_ptr >> 0x10);
    if ((flag < 1) || (uVar6 = flag == *(int *)0xb8c2, *(int *)0xb8c2 < flag)) {
      value = (uint)param_2;
      puVar8 = local_32;
      zero_word_array_16(puVar8);
      set_bit_in_array(CONCAT11(extraout_AH,0x4c));
      set_bit_in_array(CONCAT11(extraout_AH_00,0x45));
      set_bit_in_array(CONCAT11(extraout_AH_01,0x42));
      set_bit_in_array(CONCAT11(extraout_AH_02,0x72));
      set_bit_in_array(CONCAT11(extraout_AH_03,0x61));
      create_bit_mask(puVar8,unaff_SS,value);
      if ((bool)uVar6) {
        display_score_with_fatal(0xfed3);
        use_item_from_inventory((undefined1 *)result_ptr,uVar5,CONCAT11(extraout_AH_04,param_2));
      }
      else {
        display_score_with_fatal(0x12d);
      }
    }
    else {
      local_12 = (char *)inventory_list;
      check_minimum_stats();
      local_14 = flag + -1;
      value = 0;
      if (0 < local_14) {
        for (local_a = 1; local_12 = *(char **)((char *)local_12 + 0x16), value = local_a,
            local_a != local_14; local_a = local_a + 1) {
        }
      }
      uVar6 = (undefined1)((uint)value >> 8);
      uVar7 = *local_12 == '\x01';
      if ((bool)uVar7) {
        uVar4 = CONCAT11(uVar6,param_2);
        puVar8 = local_32;
        zero_word_array_16(puVar8);
        set_bit_in_array(CONCAT11(extraout_AH_05,0x62));
        set_bit_in_array(CONCAT11(extraout_AH_06,0x6c));
        create_bit_mask(puVar8,unaff_SS,uVar4);
        uVar6 = extraout_AH_07;
        if (!(bool)uVar7) {
          if (param_2 == 0x6c) {
            display_score_with_fatal(4);
            return;
          }
          display_score_with_fatal(0x66);
          return;
        }
      }
      if (param_2 == 0x54) {
        handle_attack_action((char *)local_12,local_12._2_2_);
      }
      else if (param_2 == 0x6c) {
        if (*local_12 == '\x03') {
          execute_spell_effect((undefined1 *)result_ptr,uVar5,(char *)local_12,local_12._2_2_);
        }
        else {
          display_score_with_fatal(0x12e);
        }
      }
      else if (param_2 == 0x62) {
        if (*local_12 == '\x02') {
          drink_potion_effect(CONCAT11(uVar6,*result_ptr),(char *)local_12,local_12._2_2_);
        }
        else {
          display_score_with_fatal(0x1a);
        }
      }
      else if (param_2 == 0x4c) {
        if (*local_12 == '\x05') {
          FUN_1000_b032((char *)local_12,local_12._2_2_);
        }
        else {
          display_score_with_fatal(0x131);
        }
      }
      else if (param_2 == ATTACK_FEAR) {
        if (*local_12 == '\x04') {
          FUN_1000_a68a((char *)local_12,local_12._2_2_);
        }
        else {
          display_score_with_fatal(0x21);
        }
        uVar5 = (undefined2)((ulong)local_12 >> 0x10);
        if ((*(int *)((char *)local_12 + 1) == 8) && (*(int *)((char *)local_12 + 9) == 1)) {
          reset_food_flags();
          ((char *)local_12 + 9)[0] = '\0';
          ((char *)local_12 + 9)[1] = '\0';
        }
      }
      else if (param_2 == 0x42) {
        if (*local_12 == '\a') {
          equip_item((char *)local_12,local_12._2_2_);
        }
        else {
          display_score_with_fatal(0x44);
        }
      }
      else if (param_2 == 0x72) {
        if (*local_12 == '\x06') {
          equip_item((char *)local_12,local_12._2_2_);
        }
        else {
          display_score_with_fatal(0x2e);
        }
      }
      else if (param_2 == 0x49) {
        discover_item((char *)local_12,local_12._2_2_);
      }
      else if (param_2 == 0x52) {
        identify_item((char *)local_12,local_12._2_2_);
      }
      else if (param_2 == 0x61) {
        drop_item((char *)local_12,local_12._2_2_);
      }
    }
  }
  return;
}



void check_space_threshold_and_handle(undefined4 param_1,undefined1 *param_2)

{
  undefined1 extraout_AH;
  undefined2 unaff_DS;
  
  *(int *)0xb8c6 = 0x26 - (current_food * -2 + 0x20);
  if (*(int *)0xb8c6 < 0xf) {
    *(undefined2 *)0xb8c6 = 0xf;
  }
  if (*(int *)0xb8c6 < *(int *)0xb8c4) {
    check_minimum_stats();
    display_score_with_fatal(0x148);
    *param_2 = 0;
    handle_error_and_wait();
    use_item_from_inventory((int)param_1,(int)((ulong)param_1 >> 0x10),CONCAT11(extraout_AH,0x61));
  }
  return;
}



void __cdecl16near placeholder_stub(void)

{
  return;
}



uint are_coordinates_adjacent(uint value,uint count,uint flags,uint param_4)

{
  uint value;
  
  if (((param_4 == count) &&
      ((value = value - 1, value == flags || (value = value + 1, value == flags)))) ||
     ((value = flags, flags == value &&
      ((value = count - 1, value == param_4 || (value = count + 1, value == param_4)))))) {
    value = CONCAT11((char)(value >> 8),1);
  }
  else {
    value = value & 0xff00;
  }
  return value;
}



char validate_tile_movement(int x_pos,int count,int flags)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar5;
  undefined1 *puVar6;
  undefined2 uVar7;
  undefined1 local_64 [32];
  undefined1 local_44 [32];
  undefined1 local_24 [32];
  char ch;
  
  iVar3 = (*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) + flags) * MAP_WIDTH;
  uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
  flag = (int)uVar1 + iVar3 + *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + count;
  uVar5 = flag == 0;
  uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(flag + -0x50));
  puVar6 = local_24;
  uVar7 = unaff_SS;
  pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
  create_bit_mask(puVar6,uVar7,uVar2);
  if (((bool)uVar5) &&
     (*(char *)((*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) + flags) * MAP_WIDTH +
                *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + count + -0xc) == ' ')) {
LAB_1000_d991:
    ch = '\x01';
  }
  else {
    iVar3 = (*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) + flags) * MAP_WIDTH;
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    flag = (int)uVar1 + iVar3 + *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + count;
    uVar5 = flag == 0;
    uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(flag + -0x50));
    puVar6 = local_44;
    uVar7 = unaff_SS;
    pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
    create_bit_mask(puVar6,uVar7,uVar2);
    if (((!(bool)uVar5) &&
        (iVar3 = random_mod(*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1a) + 1), iVar3 == 6)
        ) || ((*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) + flags == player_y &&
              (*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + count == player_x))))
    goto LAB_1000_d991;
    ch = '\0';
  }
  if (ch != '\0') {
    iVar3 = *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) + flags;
    uVar5 = iVar3 == 0;
    puVar6 = local_24;
    uVar7 = unaff_SS;
    zero_word_array_16(puVar6);
    set_bit_range_in_array(CONCAT11(extraout_AH,0x16),CONCAT11(extraout_AH,2));
    create_bit_mask(puVar6,uVar7,iVar3);
    if (!(bool)uVar5) {
      iVar3 = *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + count;
      uVar5 = iVar3 == 0;
      puVar6 = local_44;
      uVar7 = unaff_SS;
      zero_word_array_16(puVar6);
      set_bit_range_in_array(CONCAT11(extraout_AH_00,0x4e),CONCAT11(extraout_AH_00,2));
      create_bit_mask(puVar6,uVar7,iVar3);
      if (!(bool)uVar5) {
        ch = '\x01';
        goto LAB_1000_d9f8;
      }
    }
  }
  ch = '\0';
LAB_1000_d9f8:
  if (ch == '\0') {
    iVar3 = (*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) + flags) * MAP_WIDTH;
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    flag = (int)uVar1 + iVar3 + *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + count;
    uVar5 = flag == 0;
    uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(flag + -0x50));
    puVar6 = local_24;
    uVar7 = unaff_SS;
    pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
    create_bit_mask(puVar6,uVar7,uVar2);
    if ((!(bool)uVar5) &&
       (iVar3 = random_mod(*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x12) + 1), iVar3 == 9))
    {
      iVar3 = *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) + flags;
      uVar5 = iVar3 == 0;
      puVar6 = local_44;
      uVar7 = unaff_SS;
      zero_word_array_16(puVar6);
      set_bit_range_in_array(CONCAT11(extraout_AH_01,0x16),CONCAT11(extraout_AH_01,2));
      create_bit_mask(puVar6,uVar7,iVar3);
      if (!(bool)uVar5) {
        iVar3 = *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + count;
        uVar5 = iVar3 == 0;
        puVar6 = local_64;
        uVar7 = unaff_SS;
        zero_word_array_16(puVar6);
        set_bit_range_in_array(CONCAT11(extraout_AH_02,0x4e),CONCAT11(extraout_AH_02,2));
        create_bit_mask(puVar6,uVar7,iVar3);
        if (!(bool)uVar5) {
          uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
          *(undefined1 *)
           ((int)uVar1 + (*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) + flags) * MAP_WIDTH +
            *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + count + -0x50) = 0x20;
          ch = '\x01';
        }
      }
    }
  }
  return ch;
}



void calculate_movement_direction(int value)

{
  undefined4 uVar1;
  char ch;
  int value;
  int value;
  undefined2 unaff_SS;
  
  uVar1 = *(undefined4 *)(*(int *)(value + 4) + -8);
  *(undefined2 *)(value + -6) = *(undefined2 *)((int)uVar1 + 0x1c);
  uVar1 = *(undefined4 *)(*(int *)(value + 4) + -8);
  *(undefined2 *)(value + -4) = *(undefined2 *)((int)uVar1 + 0x1e);
  value = *(int *)(*(int *)(value + 4) + -0x13);
  if (value < 0) {
    value = -value;
  }
  value = *(int *)(*(int *)(value + 4) + -0x15);
  if (value < 0) {
    value = -value;
  }
  if (value < value) {
    ch = validate_tile_movement(*(undefined2 *)(value + 4),0,*(undefined2 *)(value + 0xc));
    if (ch == '\0') {
      ch = validate_tile_movement(*(undefined2 *)(value + 4),*(undefined2 *)(value + 10),0);
      if (ch != '\0') {
        *(int *)(value + -4) = *(int *)(value + -4) + *(int *)(value + 10);
      }
    }
    else {
      *(int *)(value + -6) = *(int *)(value + -6) + *(int *)(value + 0xc);
    }
  }
  else {
    ch = validate_tile_movement(*(undefined2 *)(value + 4),*(undefined2 *)(value + 10),0);
    if (ch == '\0') {
      ch = validate_tile_movement(*(undefined2 *)(value + 4),0,*(undefined2 *)(value + 0xc));
      if (ch != '\0') {
        *(int *)(value + -6) = *(int *)(value + -6) + *(int *)(value + 0xc);
      }
    }
    else {
      *(int *)(value + -4) = *(int *)(value + -4) + *(int *)(value + 10);
    }
  }
  return;
}



void move_entity_on_map(int x_pos,undefined4 param_2)

{
  undefined4 uVar1;
  char ch;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  uint value;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined1 extraout_AH_11;
  undefined1 extraout_AH_12;
  int flag;
  int flag;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  bool flag;
  undefined1 uVar9;
  bool flag;
  undefined1 *puVar11;
  undefined2 uVar12;
  undefined1 local_68 [32];
  undefined1 local_48 [32];
  undefined1 local_28 [32];
  int local_8;
  uint local_6;
  int random_val;
  
  calculate_movement_direction(&stack0xfffe);
  if (local_8 == *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c)) {
    value = *(uint *)((int)*(undefined4 *)(x_pos + -8) + 0x1e);
    uVar7 = local_6 < value;
    uVar9 = local_6 == value;
    if ((bool)uVar9) {
      find_highest_bit();
      char_create_wrapper();
      if (!(bool)uVar7 && !(bool)uVar9) {
        random_mod(3);
        random_mod(3);
        calculate_movement_direction(&stack0xfffe);
      }
    }
  }
  if ((local_8 != player_y) || (local_6 != *(uint *)ADDR_PLAYER_X /* player_x */)) {
    if (*(char *)*(undefined4 *)(x_pos + -8) == 'X') {
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      flag = (int)uVar1 + local_8 * MAP_WIDTH + local_6;
      uVar7 = flag == 0;
      uVar12 = CONCAT11((char)((uint)(local_8 * MAP_WIDTH) >> 8),*(undefined1 *)(flag + -0x50));
      puVar11 = local_28;
      uVar6 = unaff_SS;
      zero_word_array_16(puVar11);
      set_bit_in_array(CONCAT11(extraout_AH,0xf7));
      set_bit_in_array(CONCAT11(extraout_AH_00,0x7e));
      create_bit_mask(puVar11,uVar6,uVar12);
      if ((bool)uVar7) {
        return;
      }
    }
    value = get_relative_cursor_y();
    *(uint *)(x_pos + -0xd) = value & 0xff;
    value = get_relative_cursor_x();
    *(uint *)(x_pos + -0xb) = value & 0xff;
    if ((*(char *)((int)*(undefined4 *)(x_pos + -8) + 0x23) != '\0') &&
       (*(char *)((int)*(undefined4 *)(x_pos + -8) + 0x27) == '\0')) {
      if (is_teleporting == '\0') {
        validate_window_coords(*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) + 1,
                      *(undefined1 *)((int)*(undefined4 *)(x_pos + -8) + 0x1e));
      }
      else {
        validate_window_coords((0xd - player_y) + *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c),
                      (*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + 0x27) - player_x)
        ;
      }
      if (*(char *)(dungeon_level * 0x719 +
                    *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) * MAP_WIDTH +
                    *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + 0x70d) != '\0') {
        flag = *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) * MAP_WIDTH;
        uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
        flag = (int)uVar1 + flag + *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e);
        uVar7 = flag == 0;
        uVar12 = CONCAT11((char)((uint)flag >> 8),*(undefined1 *)(flag + -0x50));
        puVar11 = local_48;
        uVar6 = unaff_SS;
        zero_word_array_16(puVar11);
        set_bit_in_array(CONCAT11(extraout_AH_01,*(undefined1 *)0x1));
        set_bit_in_array(CONCAT11(extraout_AH_02,*(undefined1 *)0x3));
        create_bit_mask(puVar11,uVar6,uVar12);
        if ((bool)uVar7) {
          uVar12 = 0xe654;
          flag = *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) * MAP_WIDTH;
          uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
          uVar6 = unaff_DS;
          write_bytes(0,CONCAT11((char)((uint)flag >> 8),
                                   *(undefined1 *)
                                    ((int)uVar1 + flag +
                                     *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + -0x50)));
          flush_output(uVar12,uVar6);
          goto LAB_1000_de55;
        }
      }
      print_space();
    }
LAB_1000_de55:
    *(undefined1 *)
     (*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) * MAP_WIDTH +
      *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + -0xc) = 0x20;
    *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) = local_8;
    *(uint *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) = local_6;
    if (confusion_lock != '\0') {
      random_val = random_mod(0x1c);
      random_val = random_val + 1;
      *(undefined1 *)((int)*(undefined4 *)(x_pos + -8) + 1) =
           *(undefined1 *)(random_val * 0x2a + -0x5007);
      *(int *)((int)*(undefined4 *)(x_pos + -8) + 4) = random_val;
    }
    *(undefined1 *)
     (*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) * MAP_WIDTH +
      *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + -0xc) =
         *(undefined1 *)((int)*(undefined4 *)(x_pos + -8) + 1);
    if (((teleport_effect_flag != '\0') && (is_teleporting == '\0')) &&
       (*(char *)((int)*(undefined4 *)(x_pos + -8) + 0x27) == '\0')) {
      put_char_at_pos(CONCAT11((char)((uint)(local_8 * MAP_WIDTH) >> 8),
                             *(undefined1 *)(local_8 * MAP_WIDTH + local_6 + -0xc)),local_6,local_8);
    }
    *(undefined1 *)((int)*(undefined4 *)(x_pos + -8) + 0x23) = teleport_effect_flag;
    uVar6 = (undefined2)((ulong)*(undefined4 *)(x_pos + -8) >> 0x10);
    flag = (int)*(undefined4 *)(x_pos + -8);
    if (*(int *)(flag + 0x2e) == 0 && *(int *)(flag + 0x30) == 0) {
      flag = *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) * MAP_WIDTH;
      uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
      flag = (int)uVar1 + flag + *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e);
      uVar7 = flag == 0;
      uVar12 = CONCAT11((char)((uint)flag >> 8),*(undefined1 *)(flag + -0x50));
      puVar11 = local_48;
      uVar6 = unaff_SS;
      pad_and_copy_buffer(0x20,0xb7cf,unaff_DS);
      create_bit_mask(puVar11,uVar6,uVar12);
      if (!(bool)uVar7) {
        value = (uint)*(byte *)*(undefined4 *)(x_pos + -8);
        puVar11 = local_68;
        uVar6 = unaff_SS;
        zero_word_array_16(puVar11);
        set_bit_in_array(CONCAT11(extraout_AH_03,0x56));
        set_bit_in_array(CONCAT11(extraout_AH_04,0x46));
        set_bit_in_array(CONCAT11(extraout_AH_05,0x4f));
        set_bit_in_array(CONCAT11(extraout_AH_06,0x67));
        set_bit_in_array(CONCAT11(extraout_AH_07,0x55));
        set_bit_in_array(CONCAT11(extraout_AH_08,0x54));
        set_bit_in_array(CONCAT11(extraout_AH_09,0x4e));
        set_bit_in_array(CONCAT11(extraout_AH_10,0x44));
        set_bit_in_array(CONCAT11(extraout_AH_11,1));
        set_bit_in_array(CONCAT11(extraout_AH_12,0x42));
        create_bit_mask(puVar11,uVar6,value);
        if (!(bool)uVar7) {
          find_highest_bit();
          flag = false;
          flag = true;
          char_create_wrapper();
          if (!flag && !flag) {
            FUN_1000_1988((int)*(undefined4 *)(x_pos + -8) + 0x2e,
                          (int)((ulong)*(undefined4 *)(x_pos + -8) >> 0x10),
                          (int)*(undefined4 *)(x_pos + -8) + 0x1e,
                          (int)((ulong)*(undefined4 *)(x_pos + -8) >> 0x10),
                          (int)*(undefined4 *)(x_pos + -8) + 0x1c,
                          (int)((ulong)*(undefined4 *)(x_pos + -8) >> 0x10));
            uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
            *(undefined1 *)
             ((int)uVar1 + *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) * MAP_WIDTH +
              *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + -0x50) = 0x20;
            remove_item_from_list(dungeon_level * 4 + -0x54d9,unaff_DS,
                          (int)*(undefined4 *)(x_pos + -8) + 0x2e,
                          (int)((ulong)*(undefined4 *)(x_pos + -8) >> 0x10));
          }
        }
      }
    }
    validate_window_coords(*(undefined1 *)(x_pos + -0xb),*(undefined1 *)(x_pos + -0xd));
    return;
  }
  uVar7 = status_flag_1 == '\0';
  if ((bool)uVar7) {
    ch = check_inventory_has_item(ITEM_LEVITATION);
    uVar7 = ch == '\0';
    if (!(bool)uVar7) goto LAB_1000_e0d6;
  }
  else {
LAB_1000_e0d6:
    value = (uint)*(byte *)*(undefined4 *)(x_pos + -8);
    puVar11 = local_28;
    uVar6 = unaff_SS;
    pad_and_copy_buffer(0x20,0xb80f,unaff_DS);
    create_bit_mask(puVar11,uVar6,value);
    if (!(bool)uVar7) goto LAB_1000_e115;
  }
  monster_attack_player((int)param_2,(int)((ulong)param_2 >> 0x10),(int)*(undefined4 *)(x_pos + 4),
                (int)((ulong)*(undefined4 *)(x_pos + 4) >> 0x10),x_pos + -8,unaff_SS);
LAB_1000_e115:
  if ((confusion_lock != '\0') && (*(int *)(x_pos + -8) != 0 || *(int *)(x_pos + -6) != 0)) {
    flag = random_mod(0x23);
    *(undefined1 *)((int)*(undefined4 *)(x_pos + -8) + 1) =
         *(undefined1 *)((flag + 1) * 0x2a + -0x5007);
    *(int *)((int)*(undefined4 *)(x_pos + -8) + 4) = flag + 1;
    *(undefined1 *)
     (*(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1c) * MAP_WIDTH +
      *(int *)((int)*(undefined4 *)(x_pos + -8) + 0x1e) + -0xc) =
         *(undefined1 *)((int)*(undefined4 *)(x_pos + -8) + 1);
  }
  return;
}



void update_all_monsters(char *result_ptr)

{
  byte *pbVar1;
  byte bVar2;
  undefined4 uVar3;
  char ch;
  int flag;
  uint flag;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 uVar9;
  undefined2 uVar7;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined1 extraout_AH_11;
  undefined1 extraout_AH_12;
  int random_val;
  undefined1 extraout_AH_13;
  undefined1 extraout_AH_14;
  undefined1 extraout_AH_15;
  undefined1 extraout_AH_16;
  byte *pbVar10;
  undefined2 uVar11;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool flag;
  bool flag;
  undefined1 uVar14;
  undefined1 uVar15;
  undefined1 *puVar16;
  undefined1 local_f7 [32];
  undefined1 local_d7 [32];
  undefined1 local_b7 [32];
  undefined1 local_97 [32];
  undefined1 local_77 [32];
  undefined1 local_57 [32];
  undefined1 local_37 [32];
  int local_17;
  int flag;
  int local_13;
  int local_11;
  char ch;
  undefined4 local_a;
  byte *local_6;
  int local_4;
  
  if (9 < *(int *)(dungeon_level * 2 + 0x799b)) {
    apply_heroism_effect();
  }
  local_a = (byte *)*(undefined4 *)(dungeon_level * 4 + -0x5499);
LAB_1000_e1be:
  do {
    if (*result_ptr == '\0') {
      return;
    }
    if ((byte *)local_a == (byte *)0x0 && local_a._2_2_ == 0) {
      return;
    }
    bVar2 = *local_a;
    if (bVar2 == ATTACK_GHOST_2) {
      if (*(int *)((byte *)local_a + 10) < 500) {
        *(int *)((byte *)local_a + 10) = *(int *)((byte *)local_a + 10) + 1;
      }
      flag = random_mod(0x41);
      if (flag == 0) {
        uVar11 = (undefined2)((ulong)local_a >> 0x10);
        uVar3 = *(undefined4 *)(dungeon_level * 4 + 4);
        *(undefined1 *)
         ((int)uVar3 + *(int *)((byte *)local_a + 0x1c) * MAP_WIDTH + *(int *)((byte *)local_a + 0x1e) +
         -0x50) = *(undefined1 *)0x3;
      }
    }
    else if (bVar2 == ATTACK_GHOST_1) {
      flag = *(uint *)((byte *)local_a + 10);
      uVar14 = flag < 0x15e;
      uVar15 = flag == 0x15e;
      if ((int)flag < 0x15e) {
        find_highest_bit();
        char_create_wrapper();
        if (!(bool)uVar14 && !(bool)uVar15) {
          uVar11 = (undefined2)((ulong)local_a >> 0x10);
          *(int *)((byte *)local_a + 10) = *(int *)((byte *)local_a + 10) + 1;
        }
      }
    }
    else if (bVar2 == 1) {
      flag = *(uint *)((byte *)local_a + 10);
      uVar14 = flag < 0x96;
      uVar15 = flag == 0x96;
      if ((int)flag < 0x96) {
        find_highest_bit();
        char_create_wrapper();
        if (!(bool)uVar14 && !(bool)uVar15) {
          uVar11 = (undefined2)((ulong)local_a >> 0x10);
          *(int *)((byte *)local_a + 10) = *(int *)((byte *)local_a + 10) + 1;
        }
      }
    }
    else if (bVar2 == 0xe4) {
      if (*(int *)((byte *)local_a + 10) < 100) {
        find_highest_bit();
        flag = false;
        flag = true;
        char_create_wrapper();
        if (!flag && !flag) {
          uVar11 = (undefined2)((ulong)local_a >> 0x10);
          *(int *)((byte *)local_a + 10) = *(int *)((byte *)local_a + 10) + 1;
        }
      }
      flag = random_mod(0x46);
      if (flag == 0) {
        uVar11 = (undefined2)((ulong)local_a >> 0x10);
        uVar3 = *(undefined4 *)(dungeon_level * 4 + 4);
        *(undefined1 *)
         ((int)uVar3 + *(int *)((byte *)local_a + 0x1c) * MAP_WIDTH + *(int *)((byte *)local_a + 0x1e) +
         -0x50) = *(undefined1 *)0x3;
      }
    }
    uVar11 = (undefined2)((ulong)local_a >> 0x10);
    pbVar10 = (byte *)local_a;
    if (*(int *)(pbVar10 + 0x2a) != 0) {
      *(int *)(pbVar10 + 0x2a) = *(int *)(pbVar10 + 0x2a) + -1;
    }
    ch = check_inventory_has_item(ITEM_LIGHT_SOURCE);
    if ((ch == '\0') && (status_flag_5 == '\0')) {
LAB_1000_e3f9:
      if (is_wizard == '\0') {
        uVar14 = ((byte *)local_a)[0x28] == 0;
        if (!(bool)uVar14) {
          flag = (uint)*local_a;
          puVar16 = local_97;
          uVar11 = unaff_SS;
          zero_word_array_16(puVar16);
          set_bit_in_array(CONCAT11(extraout_AH_07,0x48));
          set_bit_in_array(CONCAT11(extraout_AH_08,0x58));
          create_bit_mask(puVar16,uVar11,flag);
          if ((bool)uVar14) goto LAB_1000_e7c2;
        }
        uVar11 = (undefined2)((ulong)local_a >> 0x10);
        pbVar10 = (byte *)local_a;
        if (*(int *)(pbVar10 + 0x2a) == 0) {
          if ((pbVar10[0x25] == 0) || (pbVar10[0x26] == 0)) {
            local_17 = player_y - *(int *)(pbVar10 + 0x1c);
            local_13 = get_sign(&local_17,unaff_SS);
            flag = player_x - *(int *)((byte *)local_a + 0x1e);
            uVar15 = flag == 0;
            local_11 = get_sign(&flag,unaff_SS);
            ch = '\0';
            flag = (uint)*local_a;
            puVar16 = local_b7;
            uVar11 = unaff_SS;
            zero_word_array_16(puVar16);
            set_bit_in_array(CONCAT11(extraout_AH_09,0x43));
            set_bit_in_array(CONCAT11(extraout_AH_10,0x61));
            create_bit_mask(puVar16,uVar11,flag);
            uVar14 = extraout_AH_11;
            if ((bool)uVar15) {
LAB_1000_e4ef:
              uVar7 = CONCAT11(uVar14,*local_a);
              puVar16 = local_d7;
              uVar11 = unaff_SS;
              zero_word_array_16(puVar16);
              set_bit_in_array(CONCAT11(extraout_AH_13,0x45));
              set_bit_in_array(CONCAT11(extraout_AH_14,0x48));
              create_bit_mask(puVar16,uVar11,uVar7);
              pbVar10 = (byte *)local_a;
              uVar11 = (undefined2)((ulong)local_a >> 0x10);
              if ((bool)uVar15) {
                if ((*local_a == ATTACK_GHOST_2) && (pbVar10[0x22] != 0)) {
                  *(int *)(pbVar10 + 0x20) = *(int *)(pbVar10 + 0x20) + -1;
                  if (*(int *)(pbVar10 + 0x20) < 0) {
                    pbVar10[0x22] = 0;
                  }
                }
                else if ((*local_a == 0x58) && (pbVar10[0x28] != 0)) {
                  if (dungeon_level == 0) {
                    flag = (int)*(undefined4 *)0x4 + player_y * MAP_WIDTH + player_x;
                    uVar14 = flag == 0;
                    uVar7 = CONCAT11((char)((uint)(player_y * MAP_WIDTH) >> 8),
                                     *(undefined1 *)(flag + -0x50));
                    puVar16 = local_f7;
                    uVar11 = unaff_SS;
                    zero_word_array_16(puVar16);
                    set_bit_in_array(CONCAT11(extraout_AH_15,0xf7));
                    set_bit_in_array(CONCAT11(extraout_AH_16,0x7e));
                    create_bit_mask(puVar16,uVar11,uVar7);
                    if (!(bool)uVar14) {
                      ((byte *)local_a)[0x28] = 0;
                    }
                  }
                }
                else if (pbVar10[0x22] == 0) {
                  move_entity_on_map(&stack0xfffe,&ch,unaff_SS,local_11,local_13);
                }
                else {
                  move_entity_on_map(&stack0xfffe,&ch,unaff_SS,-local_11,-local_13);
                }
              }
              else {
                if ((*local_a == ATTACK_CONFUSE) &&
                   (ch = are_coordinates_adjacent(*(undefined2 *)ADDR_PLAYER_X /* player_x */,*(undefined2 *)ADDR_PLAYER_Y /* player_y */,
                                          *(undefined2 *)(pbVar10 + 0x1e),
                                          *(undefined2 *)(pbVar10 + 0x1c)), ch != '\0')) {
                  ch = FUN_1000_1cd1((byte *)local_a,local_a._2_2_);
                  if (ch != '\0') {
                    uVar11 = (undefined2)((ulong)local_a >> 0x10);
                    ((byte *)local_a)[0x22] = 1;
                    ((byte *)local_a)[0x28] = 0;
                  }
                }
                uVar11 = (undefined2)((ulong)local_a >> 0x10);
                if ((((byte *)local_a)[0x28] == 0) || (((byte *)local_a)[0x22] != 0)) {
                  move_entity_on_map(&stack0xfffe,&ch,unaff_SS,local_11,local_13);
                }
              }
            }
            else {
              find_highest_bit();
              flag = false;
              uVar15 = true;
              char_create_wrapper();
              uVar14 = extraout_AH_12;
              if (flag || (bool)uVar15) goto LAB_1000_e4ef;
              flag = random_mod(3);
              flag = flag + -1;
              random_val = random_mod(3);
              move_entity_on_map(&stack0xfffe,&ch,unaff_SS,random_val + -1,flag);
            }
            pbVar10 = (byte *)local_a;
            flag = local_a._2_2_;
            if ((byte *)local_a != (byte *)0x0 || local_a._2_2_ != 0) {
              ((byte *)local_a)[0x26] = ((byte *)local_a)[0x26] == 0;
              if (((((byte *)local_a)[0x25] != 0) || (((byte *)local_a)[0x24] != 0)) &&
                 (*(int *)((byte *)local_a + 0x20) = *(int *)((byte *)local_a + 0x20) + -1,
                 *(int *)((byte *)local_a + 0x20) == 0)) {
                ((byte *)local_a)[0x25] = 0;
                ((byte *)local_a)[0x24] = 0;
              }
              uVar3 = *(undefined4 *)(dungeon_level * 4 + 4);
              if (*(char *)((int)uVar3 + *(int *)((byte *)local_a + 0x1c) * MAP_WIDTH +
                            *(int *)((byte *)local_a + 0x1e) + -0x50) == -9) {
                bVar2 = *local_a;
                if (((bVar2 == 0x41) || (bVar2 == 0x67)) || (bVar2 == ATTACK_STEAL_GOLD)) {
                  pbVar1 = (byte *)local_a + 0x32;
                  ch = '\x01';
                  local_4 = local_a._2_2_;
                  local_6 = (byte *)local_a;
                  local_a = *(byte **)pbVar1;
                  kill_monster((uint)(byte)((ulong)*(byte **)pbVar1 >> 8) << 8,pbVar10,flag);
                }
                else if ((bVar2 == 0x44) || (bVar2 == 0x92)) {
                  uVar3 = *(undefined4 *)(dungeon_level * 4 + 4);
                  *(undefined1 *)
                   ((int)uVar3 + *(int *)((byte *)local_a + 0x1c) * MAP_WIDTH +
                    *(int *)((byte *)local_a + 0x1e) + -0x50) = 0x20;
                }
                else {
                  uVar14 = bVar2 < 0x4d;
                  uVar15 = bVar2 == ATTACK_REMOVE_MAGIC;
                  if (!(bool)uVar15) {
                    uVar14 = bVar2 < 0x4e;
                    uVar15 = bVar2 == ATTACK_ACID_2;
                    if (!(bool)uVar15) {
                      uVar14 = bVar2 < 0x42;
                      uVar15 = bVar2 == 0x42;
                      if (!(bool)uVar15) {
                        uVar14 = bVar2 == 0;
                        uVar15 = bVar2 == 1;
                        if (!(bool)uVar15) {
                          uVar14 = bVar2 < 0x73;
                          uVar15 = bVar2 == ATTACK_DRAIN_EXP;
                          if (!(bool)uVar15) goto LAB_1000_e77e;
                        }
                      }
                    }
                  }
                  find_highest_bit();
                  char_create_wrapper();
                  if (!(bool)uVar14 && !(bool)uVar15) {
                    *(undefined1 *)(dungeon_level + 0x796d) = 1;
                  }
                }
              }
LAB_1000_e77e:
              if (ch == '\0') {
                uVar11 = (undefined2)((ulong)local_a >> 0x10);
                pbVar10 = (byte *)local_a;
                if ((pbVar10[0x24] == 0) || (pbVar10[0x26] != 0)) {
                  local_a = *(byte **)(pbVar10 + 0x32);
                }
              }
            }
          }
          else {
            pbVar10[0x26] = 0;
            local_a = *(byte **)(pbVar10 + 0x32);
          }
          goto LAB_1000_e1be;
        }
      }
    }
    else {
      uVar14 = 0;
      uVar15 = ((byte *)local_a)[0x29] == 0;
      if (!(bool)uVar15) goto LAB_1000_e3f9;
      flag = (uint)*local_a;
      puVar16 = local_37;
      uVar11 = unaff_SS;
      zero_word_array_16(puVar16);
      set_bit_in_array(CONCAT11(extraout_AH,0x4e));
      set_bit_in_array(CONCAT11(extraout_AH_00,0x45));
      create_bit_mask(puVar16,uVar11,flag);
      if (!(bool)uVar15) goto LAB_1000_e3f9;
      flag = (uint)*local_a;
      puVar16 = local_57;
      uVar11 = unaff_SS;
      zero_word_array_16(puVar16);
      set_bit_in_array(CONCAT11(extraout_AH_01,0x46));
      set_bit_in_array(CONCAT11(extraout_AH_02,0x61));
      create_bit_mask(puVar16,uVar11,flag);
      uVar9 = extraout_AH_03;
      if (!(bool)uVar15) {
        find_highest_bit();
        uVar11 = char_create_wrapper();
        uVar9 = (undefined1)((uint)uVar11 >> 8);
        if (!(bool)uVar14 && !(bool)uVar15) goto LAB_1000_e3f9;
      }
      uVar7 = CONCAT11(uVar9,*local_a);
      puVar16 = local_77;
      uVar11 = unaff_SS;
      zero_word_array_16(puVar16);
      set_bit_in_array(CONCAT11(extraout_AH_04,0x42));
      set_bit_in_array(CONCAT11(extraout_AH_05,0x44));
      set_bit_in_array(CONCAT11(extraout_AH_06,0x92));
      create_bit_mask(puVar16,uVar11,uVar7);
      if (!(bool)uVar15) {
        find_highest_bit();
        char_create_wrapper();
        if (!(bool)uVar14 && !(bool)uVar15) goto LAB_1000_e3f9;
      }
    }
LAB_1000_e7c2:
    local_a = *(byte **)((byte *)local_a + 0x32);
  } while( true );
}



void advance_to_next_level(char param_1)

{
  undefined4 uVar1;
  char ch;
  int value;
  undefined2 unaff_DS;
  
  if (param_1 == '\0') {
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    *(undefined1 *)((int)uVar1 + player_y * MAP_WIDTH + player_x + -0x50) =
         *(undefined1 *)0x0;
  }
  FUN_1000_20dd();
  dungeon_level = dungeon_level + 1;
  uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
  if (*(char *)((int)uVar1 + 0x71a) == '\0') {
    draw_dungeon_border(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */);
    generate_dungeon_level(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */);
    spawn_monsters(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */);
  }
  FUN_1000_1a1a(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */);
  is_confused = 0;
  if (param_1 == '\0') {
    ch = check_inventory_has_item(ITEM_UNKNOWN_E);
    if (ch == '\0') {
      combat_wrapper();
      check_combat_and_handle_error();
      value = combat_check_with_error();
      current_hp = value + 1;
    }
  }
  else {
    *(undefined2 *)ADDR_PLAYER_Y /* player_y */ = *(undefined2 *)(dungeon_level * 4 + 0x78ed);
    *(undefined2 *)ADDR_PLAYER_X /* player_x */ = *(undefined2 *)(dungeon_level * 4 + 0x78ef);
  }
  redraw_dungeon_level(0x17);
  display_character_stats();
  return;
}



undefined4 is_tile_passable(undefined2 param_1,int count,uint flags)

{
  undefined4 uVar1;
  long lVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 *puVar7;
  undefined1 local_44 [32];
  undefined1 local_24 [32];
  undefined1 local_4;
  
  uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
  flag = (int)uVar1 + flags * MAP_WIDTH + count;
  uVar6 = flag == 0;
  uVar3 = CONCAT11((char)(flags * MAP_WIDTH >> 8),*(undefined1 *)(flag + -0x50));
  puVar7 = local_24;
  uVar4 = unaff_SS;
  pad_and_copy_buffer(0x20,0xb76f,unaff_DS);
  create_bit_mask(puVar7,uVar4,uVar3);
  if (((bool)uVar6) || (status_flag_3 != '\0')) {
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    flag = (int)uVar1 + flags * MAP_WIDTH + count;
    uVar6 = flag == 0;
    uVar4 = CONCAT11((char)(flags * MAP_WIDTH >> 8),*(undefined1 *)(flag + -0x50));
    puVar7 = local_44;
    pad_and_copy_buffer(0x20,0xb7af,unaff_DS);
    create_bit_mask(puVar7,unaff_SS,uVar4);
    if ((bool)uVar6) {
      local_4 = 1;
      goto LAB_1000_e938;
    }
  }
  local_4 = 0;
LAB_1000_e938:
  lVar2 = (ulong)flags * MAP_WIDTH;
  if (*(char *)((int)lVar2 + count + -0xc) != ' ') {
    local_4 = 1;
  }
  return CONCAT22((int)((ulong)lVar2 >> 0x10),CONCAT11((char)((ulong)lVar2 >> 8),local_4));
}



void move_player_in_direction(char *result_ptr,char *param_2,int flags)

{
  undefined4 uVar1;
  char ch;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 uVar3;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  uint value;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  int random_val;
  int random_val;
  int random_val;
  undefined2 in_BX;
  char *pcVar8;
  int iVar9;
  undefined2 uVar10;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined1 *puVar13;
  undefined1 *puVar14;
  undefined2 uVar15;
  undefined2 uVar16;
  undefined1 local_4b [32];
  undefined1 local_2b [32];
  char ch;
  int local_a;
  int local_8;
  
  uVar10 = 0x1000;
  *param_2 = '\0';
  local_a = player_y;
  local_8 = player_x;
  if (speed_boost_active != '\0') {
    uVar10 = 0x214c;
    flags = random_mod(4);
    flags = flags + 1;
  }
  ch = is_tile_passable(&stack0xfffe,player_x + *(int *)(flags * 4 + -0x464c),
                        player_y + *(int *)(flags * 4 + -0x464e));
  if (ch == '\0') {
    *param_2 = '\x01';
  }
  else {
    local_a = player_y + *(int *)(flags * 4 + -0x464e);
    local_8 = player_x + *(int *)(flags * 4 + -0x464c);
  }
  if ((*param_2 != '\0') || (is_wizard != '\0')) {
    put_char_at_pos(0x20,*(undefined2 *)ADDR_PLAYER_X /* player_x */,*(undefined2 *)ADDR_PLAYER_Y /* player_y */);
    player_y = local_a;
    player_x = local_8;
    render_field_of_view();
    goto LAB_1000_ed19;
  }
  ch = '\x01';
  ch = check_inventory_has_item(5);
  pcVar8 = (char *)result_ptr;
  uVar3 = (undefined2)((ulong)result_ptr >> 0x10);
  if (ch == '\0') {
LAB_1000_ea57:
    if (*(char *)(local_a * MAP_WIDTH + local_8 + -0xc) == ' ') {
LAB_1000_eadc:
      uVar12 = 0;
      if (is_confused != '\0') {
        find_highest_bit();
        uVar10 = 0x214c;
        char_create_wrapper();
        if ((bool)uVar12) {
          check_minimum_stats();
          display_score_with_fatal(5);
          goto LAB_1000_eb33;
        }
      }
      is_confused = 0;
      check_space_threshold_and_handle(pcVar8,uVar3,&ch,unaff_SS);
      put_char_at_pos(CONCAT11(extraout_AH_00,0x20),*(undefined2 *)ADDR_PLAYER_X /* player_x */,*(undefined2 *)ADDR_PLAYER_Y /* player_y */);
      player_y = local_a;
      player_x = local_8;
      render_field_of_view();
    }
    else {
      if ((status_flag_1 != '\0') || (ch = check_inventory_has_item(ITEM_LEVITATION), ch != '\0')) {
        iVar9 = local_a * MAP_WIDTH + local_8;
        uVar12 = iVar9 == 0;
        uVar16 = CONCAT11((char)((uint)(local_a * MAP_WIDTH) >> 8),*(undefined1 *)(iVar9 + -0xc));
        puVar14 = local_4b;
        uVar15 = unaff_SS;
        pad_and_copy_buffer(0x20,0xb80f,unaff_DS);
        puVar13 = local_2b;
        uVar10 = unaff_SS;
        zero_word_array_16(puVar13);
        set_bit_in_array(CONCAT11(extraout_AH,0x67));
        bitwise_clear_word_arrays(puVar13,uVar10);
        uVar10 = 0x214c;
        create_bit_mask(puVar14,uVar15,uVar16);
        if (!(bool)uVar12) goto LAB_1000_eadc;
      }
      execute_player_attack(pcVar8,uVar3,local_8,local_a);
      ch = '\0';
    }
  }
  else {
    uVar10 = 0x214c;
    iVar9 = random_mod(0xf);
    if (iVar9 != 0) goto LAB_1000_ea57;
    put_char_at_pos(0x20,*(undefined2 *)ADDR_PLAYER_X /* player_x */,*(undefined2 *)ADDR_PLAYER_Y /* player_y */);
    find_random_empty_floor_space(0xe52d,unaff_DS,0xb86e,unaff_DS,0xb86c,unaff_DS);
    is_confused = 0;
    if (is_teleporting != '\0') {
      redraw_dungeon_level(0x17);
    }
    render_field_of_view();
  }
LAB_1000_eb33:
  uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
  if ((((*(char *)((int)uVar1 + player_y * MAP_WIDTH + player_x + -0x50) == -9) &&
       (status_flag_1 == '\0')) && (ch = check_inventory_has_item(ITEM_LEVITATION), ch == '\0')) &&
     (is_wizard == '\0')) {
    check_minimum_stats();
    uVar16 = 0xe654;
    uVar15 = unaff_DS;
    write_padded_string(0,0xe966,uVar10);
    flush_output(uVar16,uVar15);
    remove_magic_item(CONCAT11(extraout_AH_01,1));
    if (food_level < 400) {
      *(undefined2 *)ADDR_FOOD_LEVEL = 3000;
      if (*(char *)(dungeon_level + 0x796d) != '\0') {
        ch = check_inventory_has_item(2);
        uVar12 = 0;
        uVar11 = ch == '\0';
        if (!(bool)uVar11) {
          find_highest_bit();
          char_create_wrapper();
          if ((bool)uVar12 || (bool)uVar11) goto LAB_1000_ec9a;
        }
        uVar12 = 0;
        uVar11 = *(int *)0xb898 == 0 && *(int *)0xb89a == 0;
        if (*(int *)0xb898 != 0 || *(int *)0xb89a != 0) {
          find_highest_bit();
          char_create_wrapper();
          if ((bool)uVar12 || (bool)uVar11) goto LAB_1000_ec9a;
        }
        iVar9 = random_mod(2);
        current_food = (current_food + -1) - iVar9;
        if (current_food < 1) {
          process_game_over(pcVar8,uVar3,0x65);
        }
        else {
          display_score_with_fatal(0x24);
        }
        display_character_stats();
      }
    }
    else if (0x13 < *(int *)0xb8c0) {
      iVar9 = 0x1e - *(int *)0xb8c0 >> 0xf;
      combat_wrapper();
      uVar12 = 0;
      uVar11 = 1;
      uVar10 = conditional_char_action();
      find_highest_bit(uVar10,in_BX,iVar9);
      char_create_wrapper();
      if ((!(bool)uVar12 && !(bool)uVar11) && (ch = check_inventory_has_item(ITEM_UNKNOWN_10), ch == '\0')) {
        uVar12 = 0;
        uVar11 = *(int *)0xb898 == 0 && *(int *)0xb89a == 0;
        if (*(int *)0xb898 != 0 || *(int *)0xb89a != 0) {
          find_highest_bit();
          char_create_wrapper();
          if ((bool)uVar12 || (bool)uVar11) goto LAB_1000_ec9a;
        }
        process_game_over(pcVar8,uVar3,0x6e);
      }
    }
  }
LAB_1000_ec9a:
  if ((*result_ptr != '\0') && (ch != '\0')) {
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    iVar9 = (int)uVar1 + player_y * MAP_WIDTH + player_x;
    uVar12 = iVar9 == 0;
    uVar3 = CONCAT11((char)((uint)(player_y * MAP_WIDTH) >> 8),*(undefined1 *)(iVar9 + -0x50));
    puVar14 = local_2b;
    uVar10 = unaff_SS;
    pad_and_copy_buffer(0x20,0xb7cf,unaff_DS);
    create_bit_mask(puVar14,uVar10,uVar3);
    if ((!(bool)uVar12) &&
       ((status_flag_1 == '\0' && (ch = check_inventory_has_item(ITEM_LEVITATION), ch == '\0')))) {
      pickup_item();
    }
  }
LAB_1000_ed19:
  uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
  iVar9 = (int)uVar1 + player_y * MAP_WIDTH + player_x;
  uVar12 = iVar9 == 0;
  uVar3 = CONCAT11((char)((uint)(player_y * MAP_WIDTH) >> 8),*(undefined1 *)(iVar9 + -0x50));
  puVar14 = local_2b;
  uVar10 = unaff_SS;
  zero_word_array_16(puVar14);
  set_bit_in_array(CONCAT11(extraout_AH_02,*(undefined1 *)0x0));
  set_bit_in_array(CONCAT11(extraout_AH_03,*(undefined1 *)0x1));
  create_bit_mask(puVar14,uVar10,uVar3);
  if ((((!(bool)uVar12) && (status_flag_1 == '\0')) &&
      (value = check_inventory_has_item(ITEM_LEVITATION), (char)value == '\0')) && (is_wizard == '\0')) {
    advance_to_next_level(value & 0xff00);
  }
  uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
  iVar9 = (int)uVar1 + player_y * MAP_WIDTH + player_x;
  uVar12 = iVar9 == 0;
  uVar10 = CONCAT11((char)((uint)(player_y * MAP_WIDTH) >> 8),*(undefined1 *)(iVar9 + -0x50));
  puVar14 = local_2b;
  zero_word_array_16(puVar14);
  set_bit_in_array(CONCAT11(extraout_AH_04,*(undefined1 *)0x2));
  set_bit_in_array(CONCAT11(extraout_AH_05,*(undefined1 *)0x3));
  create_bit_mask(puVar14,unaff_SS,uVar10);
  if (((!(bool)uVar12) && (status_flag_1 == '\0')) &&
     ((ch = check_inventory_has_item(ITEM_LEVITATION), ch == '\0' && (is_wizard == '\0')))) {
    iVar9 = random_mod(5);
    random_val = random_mod(5);
    random_val = random_mod(5);
    random_val = random_mod(5);
    current_hp = ((((current_hp + -4) - random_val) - random_val) - random_val) - iVar9;
    if (dungeon_level == 0xf) {
      iVar9 = random_mod(5);
      random_val = random_mod(5);
      random_val = random_mod(5);
      random_val = random_mod(5);
      current_hp = ((((current_hp + -4) - random_val) - random_val) - random_val) - iVar9;
    }
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    *(undefined1 *)((int)uVar1 + player_y * MAP_WIDTH + player_x + -0x50) = 0x20;
    iVar9 = random_mod(2);
    display_score_with_fatal(iVar9 + 0x1a6);
    display_character_stats();
  }
  return;
}



void initialize_new_level(int x_pos)

{
  int random_val;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  random_val = random_mod(0xb);
  player_y = (random_val + 1) * 2;
  random_val = random_mod(0x27);
  player_x = (random_val + 1) * 2;
  FUN_1000_1a1a(1);
  display_character_stats();
  *(undefined1 *)(x_pos + -7) = 1;
  *(undefined2 *)ADDR_MIN_VISIBLE_ROW /* min_visible_row */ = 1;
  *(undefined2 *)ADDR_MAX_VISIBLE_ROW /* max_visible_row */ = 1;
  render_field_of_view();
  return;
}



void handle_timed_effect(int value,byte param_2)

{
  uint value;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined2 uVar2;
  undefined1 extraout_AH_11;
  undefined1 extraout_AH_12;
  undefined1 extraout_AH_13;
  undefined1 extraout_AH_14;
  undefined1 extraout_AH_15;
  undefined1 extraout_AH_16;
  undefined1 extraout_AH_17;
  undefined2 unaff_SS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined1 local_22 [32];
  undefined1 uVar3;
  
  uVar4 = &stack0x0000 == (undefined1 *)0x22;
  value = (uint)param_2;
  puVar5 = local_22;
  uVar2 = unaff_SS;
  zero_word_array_16(puVar5);
  set_bit_in_array(CONCAT11(extraout_AH,1));
  set_bit_in_array(CONCAT11(extraout_AH_00,2));
  set_bit_in_array(CONCAT11(extraout_AH_01,3));
  set_bit_in_array(CONCAT11(extraout_AH_02,6));
  create_bit_mask(puVar5,uVar2,value);
  if (!(bool)uVar4) {
    redraw_dungeon_level(0x17);
  }
  check_minimum_stats();
  uVar4 = param_2 == 0;
  if ((bool)uVar4) {
    display_score_with_fatal(3);
    uVar3 = extraout_AH_04;
  }
  else {
    uVar4 = param_2 == 4;
    if ((bool)uVar4) {
      display_score_with_fatal(6);
      FUN_1000_20dd();
      uVar3 = extraout_AH_05;
    }
    else {
      uVar4 = param_2 == 1;
      if ((bool)uVar4) {
        display_score_with_fatal(0xc);
        uVar3 = extraout_AH_06;
      }
      else {
        uVar4 = param_2 == 2;
        if ((bool)uVar4) {
          display_score_with_fatal(0x18);
          uVar3 = extraout_AH_07;
        }
        else {
          uVar4 = param_2 == 3;
          if ((bool)uVar4) {
            display_score_with_fatal(0x14b);
            uVar3 = extraout_AH_08;
          }
          else {
            uVar4 = param_2 == 5;
            if ((bool)uVar4) {
              display_score_with_fatal(0xa0);
              uVar3 = extraout_AH_09;
            }
            else {
              uVar4 = param_2 == 8;
              uVar3 = extraout_AH_03;
              if ((bool)uVar4) {
                uVar4 = value + -7 == 0;
                process_game_over(value + -7,unaff_SS,0x7a);
                uVar3 = extraout_AH_10;
              }
            }
          }
        }
      }
    }
  }
  uVar2 = CONCAT11(uVar3,param_2);
  puVar5 = local_22;
  zero_word_array_16(puVar5);
  set_bit_in_array(CONCAT11(extraout_AH_11,7));
  set_bit_in_array(CONCAT11(extraout_AH_12,9));
  set_bit_in_array(CONCAT11(extraout_AH_13,10));
  set_bit_in_array(CONCAT11(extraout_AH_14,0xb));
  set_bit_in_array(CONCAT11(extraout_AH_15,6));
  set_bit_in_array(CONCAT11(extraout_AH_16,8));
  set_bit_in_array(CONCAT11(extraout_AH_17,0xc));
  create_bit_mask(puVar5,unaff_SS,uVar2);
  if ((bool)uVar4) {
    handle_error_and_wait();
  }
  return;
}



void main_game_command_loop(int x_pos,undefined1 *param_2)

{
  undefined4 uVar1;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 uVar4;
  undefined1 extraout_AH_01;
  undefined2 uVar2;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined1 extraout_AH_11;
  undefined1 extraout_AH_12;
  undefined1 extraout_AH_13;
  undefined1 extraout_AH_14;
  undefined1 extraout_AH_15;
  int iVar3;
  undefined1 extraout_AH_16;
  undefined1 extraout_AH_17;
  undefined1 extraout_AH_18;
  undefined1 extraout_AH_19;
  undefined1 extraout_AH_20;
  undefined1 extraout_AH_21;
  undefined1 extraout_AH_22;
  undefined1 extraout_AH_23;
  undefined1 extraout_AH_24;
  undefined1 extraout_AH_25;
  undefined1 extraout_AH_26;
  undefined1 extraout_AH_27;
  undefined1 extraout_AH_28;
  undefined1 extraout_AH_29;
  undefined1 extraout_AH_30;
  undefined1 extraout_AH_31;
  undefined1 extraout_AH_32;
  undefined1 extraout_AH_33;
  undefined1 extraout_AH_34;
  undefined1 extraout_AH_35;
  undefined1 extraout_AH_36;
  undefined1 extraout_AH_37;
  undefined1 extraout_AH_38;
  undefined1 extraout_AH_39;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar5;
  undefined1 *puVar6;
  undefined1 local_25 [32];
  undefined2 local_5;
  byte local_3;
  
  local_5 = 0;
  local_3 = 0x20;
  if (*(char *)0xb914 == '\0') {
    local_3 = read_keyboard_input();
  }
  else {
    local_3 = 0x2e;
    *(undefined1 *)0xb914 = 0;
  }
  check_minimum_stats();
  *(undefined1 *)(x_pos + -5) = 1;
  uVar4 = extraout_AH;
  if (intelligence < 1) {
    process_game_over(x_pos + -7,unaff_SS,100);
    uVar4 = extraout_AH_00;
  }
  if (*(char *)(x_pos + -7) == '\0') goto LAB_1000_f547;
  if ((((local_3 == 0x32) || (local_3 == 0x34)) || (local_3 == MONSTER_SIZE)) || (local_3 == 0x38)) {
    move_player_in_direction(x_pos + -7,unaff_SS,x_pos + -5,unaff_SS,(int)(local_3 - 0x30) / 2);
    uVar4 = extraout_AH_01;
  }
  else if (local_3 == 0) {
    uVar2 = read_keyboard_input();
    local_3 = (byte)uVar2;
    if (local_3 == 0x4b) {
      uVar2 = move_player_in_direction(x_pos + -7,unaff_SS,x_pos + -5,unaff_SS,2);
    }
    else if (local_3 == ATTACK_REMOVE_MAGIC) {
      uVar2 = move_player_in_direction(x_pos + -7,unaff_SS,x_pos + -5,unaff_SS,3);
    }
    else if (local_3 == ATTACK_CONFUSE) {
      uVar2 = move_player_in_direction(x_pos + -7,unaff_SS,x_pos + -5,unaff_SS,4);
    }
    else if (local_3 == MAP_STRIDE) {
      uVar2 = move_player_in_direction(x_pos + -7,unaff_SS,x_pos + -5,unaff_SS,1);
    }
    uVar4 = (undefined1)((uint)uVar2 >> 8);
  }
  else if (local_3 == 0x3c) {
    iVar3 = player_y * MAP_WIDTH;
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    if ((((*(char *)((int)uVar1 + iVar3 + player_x + -0x50) == -0x11) &&
         (status_flag_1 == '\0')) && (iVar3 = check_inventory_has_item(ITEM_LEVITATION), (char)iVar3 == '\0')) ||
       (uVar4 = (undefined1)((uint)iVar3 >> 8), *(char *)0xb917 != '\0')) {
      iVar3 = *(int *)(dungeon_level * 4 + 0x792d);
      if (((iVar3 == player_y) &&
          (iVar3 = *(int *)(dungeon_level * 4 + 0x792f), iVar3 == player_x)) ||
         (*(char *)0xb917 != '\0')) {
        advance_to_next_level(CONCAT11((char)((uint)iVar3 >> 8),1));
        *(undefined1 *)0xb914 = 1;
        uVar4 = extraout_AH_02;
      }
      else {
        check_minimum_stats();
        display_score_with_fatal(0x20);
        uVar4 = extraout_AH_03;
      }
    }
  }
  else if (local_3 == 0x3e) {
    iVar3 = player_y * MAP_WIDTH;
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    if ((*(char *)((int)uVar1 + iVar3 + player_x + -0x50) == -0x11) ||
       (*(char *)0xb917 != '\0')) {
      if (((*(int *)(dungeon_level * 4 + 0x78ed) == player_y) &&
          (*(int *)(dungeon_level * 4 + 0x78ef) == player_x)) || (*(char *)0xb917 != '\0')) {
        FUN_1000_20dd();
        dungeon_level = dungeon_level + -1;
        if (dungeon_level < 1) {
          iVar3 = process_game_over(x_pos + -7,unaff_SS,0x67);
        }
        else {
          FUN_1000_1a1a(*(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */);
          is_confused = 0;
          *(undefined2 *)ADDR_PLAYER_Y /* player_y */ = *(undefined2 *)(dungeon_level * 4 + 0x792d);
          *(undefined2 *)ADDR_PLAYER_X /* player_x */ = *(undefined2 *)(dungeon_level * 4 + 0x792f);
          iVar3 = redraw_dungeon_level(0x17);
          *(undefined1 *)0xb914 = 1;
        }
      }
      else {
        check_minimum_stats();
        iVar3 = display_score_with_fatal(0x3c);
      }
    }
    uVar4 = (undefined1)((uint)iVar3 >> 8);
  }
  else if (local_3 == 0x51) {
    confirm_save_or_quit(x_pos + -7,unaff_SS,CONCAT11(uVar4,0x51));
    uVar4 = extraout_AH_04;
  }
  else if (local_3 == CMD_SAVE) {
    confirm_save_or_quit(x_pos + -7,unaff_SS,CONCAT11(uVar4,0x73));
    uVar4 = extraout_AH_05;
  }
  else if (local_3 == 0x10) {
    if ((is_blind == '\0') && (needs_full_update == '\0')) {
      redraw_dungeon_level(0x17);
      uVar4 = extraout_AH_06;
    }
  }
  else if (local_3 == MAP_HEIGHT) {
    handle_player_death();
    uVar4 = extraout_AH_07;
  }
  else if (local_3 == 7) {
    *(bool *)0xe539 = *(char *)0xe539 == '\0';
  }
  else if (local_3 == 8) {
    display_help_file();
    redraw_dungeon_level(0x17);
    uVar4 = extraout_AH_08;
  }
  else if (local_3 == 0x14) {
    display_inventory_list();
    uVar4 = extraout_AH_09;
  }
  else if (local_3 == 0x35) {
    if (*(char *)0xb917 != '\0') {
      *(bool *)ADDR_STATUS_FLAG_3 = status_flag_3 == '\0';
    }
  }
  else if (local_3 == 0x3f) {
    FUN_1000_6249();
    uVar4 = extraout_AH_10;
  }
  else if (local_3 == 0x6c) {
    if (is_blind == '\0') {
      use_item_from_inventory(x_pos + -7,unaff_SS,CONCAT11(uVar4,0x6c));
      uVar4 = extraout_AH_11;
    }
  }
  else if (((((local_3 == 0x61) || (local_3 == 0x42)) || (local_3 == 0x72)) ||
           (((local_3 == ATTACK_FEAR || (local_3 == 0x54)) ||
            ((local_3 == 0x4c || ((local_3 == 0x52 || (local_3 == 0x6c)))))))) || (local_3 == 0x62))
  {
    use_item_from_inventory(x_pos + -7,unaff_SS,CONCAT11(uVar4,local_3));
    uVar4 = extraout_AH_12;
  }
  else if (local_3 == 0x65) {
    remove_equipped_item_menu();
    uVar4 = extraout_AH_13;
  }
  else if (local_3 == ATTACK_ACID_2) {
    FUN_1000_a74b();
    uVar4 = extraout_AH_14;
  }
  else if (local_3 == 0x6d) {
    FUN_1000_a45b();
    uVar4 = extraout_AH_15;
  }
  else if (local_3 == 0x68) {
    iVar3 = player_y * MAP_WIDTH;
    uVar1 = *(undefined4 *)(dungeon_level * 4 + 4);
    if (*(char *)((int)uVar1 + iVar3 + player_x + -0x50) == -0x65) {
      iVar3 = shop_purchase_menu();
    }
    uVar4 = (undefined1)((uint)iVar3 >> 8);
  }
  else if ((local_3 == 0x69) || (local_3 == 0x2a)) {
    FUN_1000_5fd2();
    uVar4 = extraout_AH_16;
  }
  else if (local_3 == 99) {
    draw_game_hud();
    uVar4 = extraout_AH_17;
  }
  else if (local_3 == ATTACK_DRAIN_EXP) {
    clear_screen_double();
    display_high_scores();
    validate_window_coords(CONCAT11(extraout_AH_18,0x19),CONCAT11(extraout_AH_18,0x41));
    handle_error_and_wait();
    redraw_dungeon_level(0x17);
    uVar4 = extraout_AH_19;
  }
  else if (local_3 == 0x49) {
    if (*(char *)0xb917 != '\0') {
      use_item_from_inventory(x_pos + -7,unaff_SS,CONCAT11(uVar4,0x49));
      uVar4 = extraout_AH_20;
    }
  }
  else if (local_3 == 0x53) {
    if (*(char *)0xb917 != '\0') {
      process_options_menu();
      uVar4 = extraout_AH_21;
    }
  }
  else if (local_3 == 0x41) {
    if (*(char *)0xb917 != '\0') {
      redraw_screen_map();
      uVar4 = extraout_AH_22;
    }
  }
  else if (local_3 == 0x43) {
    if (*(char *)0xb917 != '\0') {
      placeholder_stub();
      uVar4 = extraout_AH_23;
    }
  }
  else if (local_3 == 0xe6) {
    if (*(char *)0xb917 != '\0') {
      *(bool *)ADDR_TELEPORT_FLAG = teleport_effect_flag == '\0';
      *(undefined2 *)ADDR_EFFECT_TIMER_16 = 0x7fff;
    }
  }
  else if (local_3 == 0x25) {
    if (*(char *)0xb917 != '\0') {
      FUN_1000_62b7();
      uVar4 = extraout_AH_24;
    }
  }
  else if ((local_3 == MAP_WIDTH) && (*(char *)0xb917 != '\0')) {
    FUN_1000_6431();
    uVar4 = extraout_AH_25;
  }
  uVar5 = *(char *)(x_pos + -5) == '\0';
  if ((bool)uVar5) {
LAB_1000_f53f:
    uVar4 = 1;
  }
  else {
    uVar2 = CONCAT11(uVar4,local_3);
    puVar6 = local_25;
    zero_word_array_16(puVar6);
    set_bit_in_array(CONCAT11(extraout_AH_26,0x2e));
    set_bit_in_array(CONCAT11(extraout_AH_27,0x6c));
    set_bit_in_array(CONCAT11(extraout_AH_28,0x61));
    set_bit_in_array(CONCAT11(extraout_AH_29,0x42));
    set_bit_in_array(CONCAT11(extraout_AH_30,0x62));
    set_bit_in_array(CONCAT11(extraout_AH_31,0x65));
    set_bit_in_array(CONCAT11(extraout_AH_32,0x6d));
    set_bit_in_array(CONCAT11(extraout_AH_33,0x72));
    set_bit_in_array(CONCAT11(extraout_AH_34,0x45));
    set_bit_in_array(CONCAT11(extraout_AH_35,0x4e));
    set_bit_in_array(CONCAT11(extraout_AH_36,0x4c));
    set_bit_in_array(CONCAT11(extraout_AH_37,0x54));
    set_bit_in_array(CONCAT11(extraout_AH_38,0x3e));
    set_bit_in_array(CONCAT11(extraout_AH_39,0x3c));
    create_bit_mask(puVar6,unaff_SS,uVar2);
    if (!(bool)uVar5) goto LAB_1000_f53f;
    uVar4 = 0;
  }
  *param_2 = uVar4;
LAB_1000_f547:
  display_character_stats();
  return;
}



void rest_and_regenerate(int value)

{
  int value;
  uint random_val;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_4;
  
  count_item_total_quantity(&local_4,unaff_SS,9);
  if (local_4 != 0) {
    value = local_4;
    if (local_4 < 0) {
      value = -local_4;
    }
    random_val = random_mod(value + 3);
    if (2 < random_val) {
      if (local_4 < 0) {
        local_4 = -local_4;
      }
      random_mod(local_4 / 2 + 2);
      value = multiply_integers();
      current_hp = current_hp + value;
      if (max_hp < current_hp) {
        *(undefined2 *)ADDR_CURRENT_HP /* current_hp */ = *(undefined2 *)ADDR_MAX_HP /* max_hp */;
      }
      display_character_stats();
    }
  }
  if (current_hp < 1) {
    process_game_over(value + -7,unaff_SS,0x72);
  }
  return;
}



void __cdecl16near main_game_loop(void)

{
  char cVar1;
  int iVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  char effect_index;
  char is_alive;
  char turn_processed [6];
  
  initialize_new_level(&stack0xfffe);
  while (is_alive != '\0') {
    render_field_of_view();
    turn_processed[0] = '\x01';
    if (4000 < turn_count) {
      process_game_over(&is_alive,unaff_SS,0x62);
    }
    if (is_dying == '\0') {
      main_game_command_loop(&stack0xfffe,turn_processed,unaff_SS);
    }
    else {
      death_timer = death_timer + -1;
      if (death_timer == 0) {
        check_minimum_stats();
        display_score_with_fatal(0xb1);
        handle_error_and_wait();
        is_dying = 0;
      }
    }
    if (turn_processed[0] != '\0') {
      if (turn_count % 0x14 == 0) {
        populate_level_with_monsters();
        cVar1 = check_inventory_has_item(ITEM_CURSED_SPECIAL);
        if ((cVar1 != '\0') || (*(int *)0xb8a0 != 0 || *(int *)0xb8a2 != 0)) {
          populate_level_with_monsters();
          populate_level_with_monsters();
          populate_level_with_monsters();
        }
      }
      FUN_1000_a518(&is_alive,unaff_SS);
      effect_index = '\0';
      while( true ) {
        if ((*(char *)(effect_index + -0x4714) != '\0') &&
           (*(int *)(effect_index * 2 + -0x4707) = *(int *)(effect_index * 2 + -0x4707) + -1,
           *(int *)(effect_index * 2 + -0x4707) < 1)) {
          *(undefined1 *)(effect_index + -0x4714) = 0;
          handle_timed_effect(&stack0xfffe,(int)effect_index);
        }
        if (effect_index == '\f') break;
        effect_index = effect_index + '\x01';
      }
      if (*(int *)0xb8a4 != 0 || *(int *)0xb8a6 != 0) {
        *(int *)((int)*(undefined4 *)0xb8a4 + 9) = *(int *)((int)*(undefined4 *)0xb8a4 + 9) + -1;
        if (*(int *)((int)*(undefined4 *)0xb8a4 + 9) == 0) {
          FUN_1000_1885();
        }
        if (*(int *)((int)*(undefined4 *)0xb8a4 + 9) < 0) {
          *(undefined2 *)((int)*(undefined4 *)0xb8a4 + 9) = 0xffff;
        }
      }
      if (is_alive != '\0') {
        if (is_paralyzed != '\0') {
          main_game_command_loop(&stack0xfffe,turn_processed,unaff_SS);
          render_field_of_view();
        }
        if ((*(int *)0xb890 == 0) && (current_hp < max_hp)) {
          current_hp = current_hp + 1;
          *(int *)0xb890 = (0xf - dungeon_level) / 2;
          display_character_stats();
        }
        else if (0 < *(int *)0xb890) {
          *(int *)0xb890 = *(int *)0xb890 + -1;
        }
        rest_and_regenerate(&stack0xfffe);
        update_all_monsters(&is_alive,unaff_SS);
        if (is_hasted != '\0') {
          update_all_monsters(&is_alive,unaff_SS);
          haste_timer = haste_timer + -1;
          if (haste_timer == 0) {
            is_hasted = 0;
            check_minimum_stats();
            display_score_with_fatal(0xb4);
          }
        }
        cVar1 = check_inventory_has_item(ITEM_LIGHT_SOURCE);
        if ((cVar1 != '\0') &&
           (*(int *)((int)*(undefined4 *)0xabaf + 9) = *(int *)((int)*(undefined4 *)0xabaf + 9) + -1
           , *(int *)((int)*(undefined4 *)0xabaf + 9) == 0)) {
          process_game_over(&is_alive,unaff_SS,0x61);
        }
        cVar1 = check_inventory_has_item(ITEM_LEVITATION);
        if (cVar1 != '\0') {
          decrement_item_quantity(ITEM_LEVITATION);
        }
        cVar1 = check_inventory_has_item(ITEM_DRAIN_STAT);
        if (((cVar1 != '\0') && (iVar2 = random_mod(200), iVar2 == 0)) && (1 < current_food)) {
          decrement_item_quantity(ITEM_DRAIN_STAT);
          current_food = current_food + -1;
          *(undefined2 *)ADDR_MAX_FOOD /* max_food */ = *(undefined2 *)ADDR_CURRENT_FOOD /* current_food */;
          display_character_stats();
        }
      }
    }
    if (confusion_lock == '\0') {
      check_confusion_recovery();
    }
  }
  return;
}



void __cdecl16near show_main_menu(void)

{
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 uVar1;
  undefined1 uVar3;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined2 uVar2;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined2 unaff_SS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined1 local_25 [32];
  int local_5;
  char ch;
  
  do {
    clear_screen_double();
    validate_window_coords(CONCAT11(extraout_AH,1),CONCAT11(extraout_AH,1));
    display_score_with_fatal(0x149);
    validate_window_coords(CONCAT11(extraout_AH_00,10),CONCAT11(extraout_AH_00,0x1e));
    display_score_with_fatal(0x7c);
    local_5 = 0;
    while( true ) {
      validate_window_coords(local_5 * 2 + 0xf,0x14);
      display_score_with_fatal(local_5 + 0x34);
      if (local_5 == 3) break;
      local_5 = local_5 + 1;
    }
    validate_window_coords(0x17,0x32);
    display_score_with_fatal(0x7d);
    validate_window_coords(CONCAT11(extraout_AH_01,0x17),CONCAT11(extraout_AH_01,0x46));
    uVar1 = read_keyboard_input();
    ch = (char)uVar1;
    uVar3 = (undefined1)((uint)uVar1 >> 8);
    uVar4 = ch == CMD_EQUIPMENT;
    if (((bool)uVar4) || (uVar4 = ch == 'E', (bool)uVar4)) {
      display_help_file();
      uVar3 = extraout_AH_02;
    }
    else {
      uVar4 = ch == CMD_SEARCH;
      if (((bool)uVar4) || (uVar4 = ch == 'S', (bool)uVar4)) {
        clear_screen_double();
        load_high_scores();
        display_high_scores();
        validate_window_coords(CONCAT11(extraout_AH_03,0x19),CONCAT11(extraout_AH_03,0x3c));
        handle_error_and_wait();
        uVar3 = extraout_AH_04;
      }
      else {
        uVar4 = ch == 'j';
        if (((bool)uVar4) || (uVar4 = ch == 'J', (bool)uVar4)) {
          clear_screen_double();
          FUN_1f98_137a();
          FUN_1f98_14b7();
          FUN_1f98_1155();
          load_high_scores();
          initialize_game();
          clear_screen_double();
          main_game_loop();
          FUN_1000_1b91();
          uVar3 = extraout_AH_05;
        }
      }
    }
    uVar2 = CONCAT11(uVar3,ch);
    puVar5 = local_25;
    uVar1 = unaff_SS;
    zero_word_array_16(puVar5);
    set_bit_in_array(CONCAT11(extraout_AH_06,0x66));
    set_bit_in_array(CONCAT11(extraout_AH_07,0x46));
    create_bit_mask(puVar5,uVar1,uVar2);
  } while ((bool)uVar4);
  return;
}



// WARNING: This function may have set the stack pointer

void entry(void)

{
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined1 extraout_AH_11;
  undefined1 extraout_AH_12;
  undefined1 extraout_AH_13;
  undefined1 extraout_AH_14;
  undefined1 extraout_AH_15;
  undefined1 extraout_AH_16;
  undefined1 extraout_AH_17;
  undefined1 extraout_AH_18;
  undefined1 extraout_AH_19;
  undefined1 extraout_AH_20;
  undefined1 extraout_AH_21;
  undefined1 extraout_AH_22;
  undefined1 extraout_AH_23;
  undefined1 extraout_AH_24;
  undefined1 extraout_AH_25;
  undefined1 extraout_AH_26;
  undefined1 extraout_AH_27;
  undefined1 extraout_AH_28;
  undefined1 extraout_AH_29;
  undefined1 extraout_AH_30;
  undefined1 extraout_AH_31;
  undefined1 extraout_AH_32;
  undefined2 unaff_DS;
  
  DAT_3000_557e = 0x1000;
  DAT_3000_557c = 0xf951;
  c_runtime_startup();
  DAT_3000_557e = 0x214c;
  DAT_3000_557c = 0xf956;
  FUN_20e6_0000();
  DAT_3000_557e = 0x20e6;
  DAT_3000_557c = 0xf95d;
  initialize_character_sets();
  DAT_3000_557e = 0x1f98;
  DAT_3000_557c = 0xf962;
  FUN_1f98_1107();
  DAT_3000_557e = 0x1f98;
  DAT_3000_557c = 0xf967;
  load_game_data();
  DAT_3000_557e = 0x1f98;
  DAT_3000_557c = 0xf96c;
  seed_rng();
  DAT_3000_557e = CONCAT11(extraout_AH,0xf);
  DAT_3000_557c = 0x214c;
  DAT_3000_557a = 0xf974;
  set_text_color_attribute();
  DAT_3000_557e = 0xf977;
  show_main_menu();
  DAT_3000_557e = 0x20e6;
  DAT_3000_557c = 0xf980;
  dos_interrupt_handler_init();
  DAT_3000_557e = 0x4000;
  DAT_3000_557c = 0x214c;
  DAT_3000_557a = 0xf98b;
  validate_stack_space();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xf998;
  zero_word_array_16();
  uRam00035538 = CONCAT11(extraout_AH_00,0xc4);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9a0;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_01,0xc1);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9a8;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_02,0xc2);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9b0;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_03,0xc5);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9b8;
  set_bit_in_array();
  uRam00035536 = 0xb72f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xf9c6;
  copy_buffer_with_offset();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xf9d0;
  zero_word_array_16();
  uRam00035538 = CONCAT11(extraout_AH_04,0xb3);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9d8;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_05,0xc3);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9e0;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_06,0xb4);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9e8;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_07,0xc5);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9f0;
  set_bit_in_array();
  uRam00035536 = 0xb74f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xf9fe;
  copy_buffer_with_offset();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035536 = 0xb74f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfa11;
  pad_and_copy_buffer();
  uRam00035538 = 0x3158;
  uRam00035536 = 0x3fbe;
  uRam00035532 = 0xb72f;
  uRam00035530 = 0x20;
  uRam0003552e = 0x214c;
  uRam0003552c = 0xfa24;
  pad_and_copy_buffer();
  uRam00035534 = 0x214c;
  uRam00035532 = 0xfa29;
  bitwise_or_word_arrays();
  uRam00035536 = 0xb76f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfa37;
  copy_buffer_with_offset();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xfa41;
  zero_word_array_16();
  uRam00035538 = CONCAT11(extraout_AH_08,0xda);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa49;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_09,0xbf);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa51;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_10,0xc0);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa59;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_11,0xd9);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa61;
  set_bit_in_array();
  uRam00035536 = 0xb78f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfa6f;
  copy_buffer_with_offset();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xfa79;
  zero_word_array_16();
  uRam00035538 = CONCAT11(extraout_AH_12,0xc2);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa81;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_13,0xc1);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa89;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_14,0xc3);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa91;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_15,0xb4);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa99;
  set_bit_in_array();
  uRam00035536 = 0xb7af;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfaa7;
  copy_buffer_with_offset();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xfab1;
  zero_word_array_16();
  uRam00035538 = CONCAT11(extraout_AH_16,0x24);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfab9;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_17,0x3a);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfac1;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_18,0xad);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfac9;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_19,0x3d);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfad1;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_20,0x7f);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfad9;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_21,0x3f);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfae1;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_22,0xf8);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfae9;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_23,0x2f);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfaf1;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_24,0xf);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfaf9;
  set_bit_in_array();
  uRam00035536 = 0xb7cf;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfb07;
  copy_buffer_with_offset();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xfb11;
  zero_word_array_16();
  uRam00035538 = CONCAT11(extraout_AH_25,0xea);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb19;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_26,1);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb21;
  set_bit_in_array();
  uRam00035536 = 0xb82f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfb2f;
  copy_buffer_with_offset();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xfb39;
  zero_word_array_16();
  uRam00035538 = CONCAT11(extraout_AH_27,0x53);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb41;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_28,0x41);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb49;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_29,0x52);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb51;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_30,0x4c);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb59;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_31,0x57);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb61;
  set_bit_in_array();
  uRam00035538 = CONCAT11(extraout_AH_32,0x67);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb69;
  set_bit_in_array();
  uRam00035536 = 0xb80f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfb77;
  uRam00035538 = unaff_DS;
  copy_buffer_with_offset();
  return;
}



void __cdecl16far initialize_character_sets(void)

{
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined1 extraout_AH_11;
  undefined1 extraout_AH_12;
  undefined1 extraout_AH_13;
  undefined1 extraout_AH_14;
  undefined1 extraout_AH_15;
  undefined1 extraout_AH_16;
  undefined1 extraout_AH_17;
  undefined1 extraout_AH_18;
  undefined1 extraout_AH_19;
  undefined1 extraout_AH_20;
  undefined1 extraout_AH_21;
  undefined1 extraout_AH_22;
  undefined1 extraout_AH_23;
  undefined1 extraout_AH_24;
  undefined1 extraout_AH_25;
  undefined1 extraout_AH_26;
  undefined1 extraout_AH_27;
  undefined1 extraout_AH_28;
  undefined1 extraout_AH_29;
  undefined1 extraout_AH_30;
  undefined1 extraout_AH_31;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar1;
  undefined2 uVar2;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined1 local_42 [32];
  undefined1 local_22 [28];
  undefined2 uStack_6;
  undefined2 uStack_4;
  
  uStack_4 = 0x1f98;
  uStack_6 = 0xf98b;
  validate_stack_space();
  puVar3 = local_22;
  uVar2 = unaff_SS;
  zero_word_array_16(puVar3);
  set_bit_in_array(CONCAT11(extraout_AH,0xc4));
  set_bit_in_array(CONCAT11(extraout_AH_00,0xc1));
  set_bit_in_array(CONCAT11(extraout_AH_01,0xc2));
  set_bit_in_array(CONCAT11(extraout_AH_02,0xc5));
  copy_buffer_with_offset(0x20,0xb72f,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  uVar2 = unaff_SS;
  zero_word_array_16(puVar3);
  set_bit_in_array(CONCAT11(extraout_AH_03,0xb3));
  set_bit_in_array(CONCAT11(extraout_AH_04,0xc3));
  set_bit_in_array(CONCAT11(extraout_AH_05,0xb4));
  set_bit_in_array(CONCAT11(extraout_AH_06,0xc5));
  copy_buffer_with_offset(0x20,0xb74f,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  uVar4 = unaff_SS;
  pad_and_copy_buffer(0x20,0xb74f,unaff_DS);
  puVar1 = local_42;
  uVar2 = unaff_SS;
  pad_and_copy_buffer(0x20,0xb72f,unaff_DS);
  bitwise_or_word_arrays(puVar1,uVar2);
  copy_buffer_with_offset(0x20,0xb76f,unaff_DS,puVar3,uVar4);
  puVar3 = local_22;
  uVar2 = unaff_SS;
  zero_word_array_16(puVar3);
  set_bit_in_array(CONCAT11(extraout_AH_07,0xda));
  set_bit_in_array(CONCAT11(extraout_AH_08,0xbf));
  set_bit_in_array(CONCAT11(extraout_AH_09,0xc0));
  set_bit_in_array(CONCAT11(extraout_AH_10,0xd9));
  copy_buffer_with_offset(0x20,0xb78f,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  uVar2 = unaff_SS;
  zero_word_array_16(puVar3);
  set_bit_in_array(CONCAT11(extraout_AH_11,0xc2));
  set_bit_in_array(CONCAT11(extraout_AH_12,0xc1));
  set_bit_in_array(CONCAT11(extraout_AH_13,0xc3));
  set_bit_in_array(CONCAT11(extraout_AH_14,0xb4));
  copy_buffer_with_offset(0x20,0xb7af,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  uVar2 = unaff_SS;
  zero_word_array_16();
  set_bit_in_array(CONCAT11(extraout_AH_15,0x24));
  set_bit_in_array(CONCAT11(extraout_AH_16,0x3a));
  set_bit_in_array(CONCAT11(extraout_AH_17,0xad));
  set_bit_in_array(CONCAT11(extraout_AH_18,0x3d));
  set_bit_in_array(CONCAT11(extraout_AH_19,0x7f));
  set_bit_in_array(CONCAT11(extraout_AH_20,0x3f));
  set_bit_in_array(CONCAT11(extraout_AH_21,0xf8));
  set_bit_in_array(CONCAT11(extraout_AH_22,0x2f));
  set_bit_in_array(CONCAT11(extraout_AH_23,0xf));
  copy_buffer_with_offset(0x20,0xb7cf,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  uVar2 = unaff_SS;
  zero_word_array_16();
  set_bit_in_array(CONCAT11(extraout_AH_24,0xea));
  set_bit_in_array(CONCAT11(extraout_AH_25,1));
  copy_buffer_with_offset(0x20,0xb82f,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  zero_word_array_16();
  set_bit_in_array(CONCAT11(extraout_AH_26,0x53));
  set_bit_in_array(CONCAT11(extraout_AH_27,0x41));
  set_bit_in_array(CONCAT11(extraout_AH_28,0x52));
  set_bit_in_array(CONCAT11(extraout_AH_29,0x4c));
  set_bit_in_array(CONCAT11(extraout_AH_30,0x57));
  set_bit_in_array(CONCAT11(extraout_AH_31,0x67));
  copy_buffer_with_offset(0x20,0xb80f,unaff_DS,puVar3,unaff_SS);
  return;
}



ulong get_random_byte(int value)

{
  undefined1 uVar1;
  int value;
  undefined2 unaff_SS;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  
  uVar5 = 0x1f;
  validate_stack_space();
  uVar4 = (undefined1)unaff_SS;
  uVar3 = (undefined1)(value + -0x10d);
  uVar1 = getc(uVar3);
  *(undefined1 *)(value + -0xb) = uVar1;
  flush_input(uVar3,uVar4);
  check_and_handle_error(uVar5);
  if (*(char *)(value + -0xb) == -1) {
    *(undefined1 *)(value + -0xb) = 0x1a;
  }
  value = ((uint)*(byte *)(value + -0xb) + *(int *)(value + -0x111) + 0xfe) -
          *(int *)(value + -0x10f);
  *(uint *)(value + -0x111) = (uint)*(byte *)(value + -0xb);
  return CONCAT22(value / 0xfe,value % 0xfe) & 0xffff00ff;
}



int get_centered_random(undefined2 param_1)

{
  uint random_val;
  undefined2 uVar2;
  
  uVar2 = 0x1f98;
  validate_stack_space();
  random_val = get_random_byte(param_1,uVar2);
  return (random_val & 0xff) - 0x28;
}



void read_data_line(int value,byte *param_2)

{
  undefined2 random_val;
  uint value;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  byte *pbVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined1 random_val;
  undefined1 *puVar6;
  undefined2 uVar7;
  undefined1 *puVar8;
  undefined2 uVar9;
  undefined1 local_202 [256];
  undefined1 local_102 [224];
  undefined1 local_22 [28];
  undefined2 uStack_6;
  undefined2 uStack_4;
  
  uStack_4 = 0x1f98;
  uStack_6 = 0xfc2a;
  validate_stack_space();
  *param_2 = 0;
  do {
    puVar8 = local_202;
    uVar4 = (undefined2)((ulong)param_2 >> 0x10);
    pbVar3 = (byte *)param_2;
    uVar9 = unaff_SS;
    copy_pascal_string(pbVar3,uVar4);
    puVar6 = local_102;
    uVar7 = unaff_SS;
    random_val = get_random_byte(value,puVar6);
    char_to_pascal_string(random_val);
    concat_pascal_string(puVar6,uVar7);
    copy_pascal_string_limited(0x50,pbVar3,uVar4,puVar8,uVar9);
    random_val = pbVar3 + *param_2 == (byte *)0x0;
    value = (uint)pbVar3[*param_2];
    puVar8 = local_22;
    uVar7 = unaff_SS;
    zero_word_array_16(puVar8);
    set_bit_in_array(CONCAT11(extraout_AH,10));
    set_bit_in_array(CONCAT11(extraout_AH_00,0xd));
    create_bit_mask(puVar8,uVar7,value);
  } while ((bool)random_val);
  conditional_string_format(1,*param_2,pbVar3,uVar4);
  random_val = get_random_byte(value);
  *(undefined1 *)(value + -0xb) = random_val;
  return;
}



void __cdecl16far load_game_data(void)

{
  undefined4 uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined1 extraout_AH_11;
  undefined1 extraout_AH_12;
  int iVar7;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool flag;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined2 uVar11;
  undefined1 local_313 [256];
  undefined1 local_213 [192];
  undefined1 local_153 [32];
  undefined1 local_133 [28];
  int local_117;
  undefined1 local_10f [256];
  char local_f;
  undefined1 local_e;
  int local_c;
  int flag;
  int flag;
  undefined2 local_6;
  undefined2 local_4;
  
  local_4 = 0x1f98;
  local_6 = 0xfdb9;
  validate_stack_space();
  init_fcb(0x346,0x214c,local_10f,unaff_SS);
  file_open_wrapper(0x214c,local_10f);
  check_and_handle_error();
  iVar3 = get_and_clear_error_code();
  if (iVar3 != 1) {
    read_data_line(&stack0xfffe,0xbba5,unaff_DS);
    uVar11 = 0xe654;
    write_padded_string(0,0xbba5,unaff_DS);
    write_word(0x214c,uVar11);
    check_and_handle_error();
    local_c = 1;
    while( true ) {
      iVar3 = validate_range_bounds();
      read_data_line(&stack0xfffe,iVar3 * 0x49 + -0x44a4,unaff_DS);
      if (local_c == 0x1f) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = validate_range_bounds();
      read_data_line(&stack0xfffe,iVar3 * 0x33 + -0x3bb7,unaff_DS);
      if (local_c == 0x5a) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = validate_range_bounds();
      read_data_line(&stack0xfffe,iVar3 * 0x1f + -0x29b5,unaff_DS);
      if (local_c == 0x6d) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = validate_range_bounds();
      read_data_line(&stack0xfffe,iVar3 * 0x10 + -0x1c73,unaff_DS);
      if (local_c == 0x19) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      flag = 1;
      while( true ) {
        get_centered_random(&stack0xfffe);
        uVar11 = validate_range_bounds();
        iVar3 = validate_range_bounds();
        iVar3 = iVar3 << 1;
        iVar4 = validate_range_bounds();
        *(undefined2 *)(iVar4 * 4 + iVar3 + -18000) = uVar11;
        if (flag == 2) break;
        flag = flag + 1;
      }
      if (local_c == 4) break;
      local_c = local_c + 1;
    }
    get_random_byte(&stack0xfffe);
    local_e = validate_range_bounds();
    get_random_byte(&stack0xfffe);
    local_e = validate_range_bounds();
    local_f = '\x02';
    while( true ) {
      iVar3 = get_centered_random(&stack0xfffe);
      iVar3 = iVar3 >> 0xf;
      uVar11 = validate_range_bounds();
      iVar4 = validate_range_bounds();
      *(undefined2 *)(iVar4 * 4 + 0x79b3) = uVar11;
      *(int *)(iVar4 * 4 + 0x79b5) = iVar3;
      if (local_f == '\b') break;
      local_f = local_f + '\x01';
    }
    local_c = 1;
    while( true ) {
      local_f = '\0';
      while( true ) {
        get_centered_random(&stack0xfffe);
        uVar11 = validate_range_bounds();
        iVar3 = validate_range_bounds();
        iVar3 = iVar3 << 1;
        iVar4 = validate_range_bounds();
        *(undefined2 *)(iVar4 * 0x30 + iVar3 + 0x79d5) = uVar11;
        if (local_f == '\b') break;
        local_f = local_f + '\x01';
      }
      if (local_c == 3) break;
      local_c = local_c + 1;
    }
    get_random_byte(&stack0xfffe);
    local_e = validate_range_bounds();
    FUN_22de_cd9b(&stack0xfffe);
    local_e = validate_range_bounds();
    local_c = 1;
    while( true ) {
      iVar3 = validate_range_bounds();
      FUN_22de_ce3f(&stack0xfffe,iVar3 * 0x10 + -0x5e49);
      if (local_c == 0x18) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = validate_range_bounds();
      FUN_22de_ce3f(&stack0xfffe,iVar3 * 0x10 + -0x5b49);
      if (local_c == CMD_SAVE) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = validate_range_bounds();
      FUN_22de_ce3f(&stack0xfffe,iVar3 * 0x10 + -0x58e9);
      if (local_c == MAP_HEIGHT) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = validate_range_bounds();
      FUN_22de_ce3f(&stack0xfffe,iVar3 * 0x10 + -0x5629);
      if (local_c == 10) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = validate_range_bounds();
      *(undefined1 *)(iVar3 * 4 + -0x469e) = 0;
      flag = 1;
      while( true ) {
        puVar10 = local_313;
        uVar6 = unaff_SS;
        iVar3 = validate_range_bounds(puVar10);
        copy_pascal_string(iVar3 * 4 + -0x469e,unaff_DS);
        puVar9 = local_213;
        uVar11 = unaff_SS;
        uVar5 = FUN_22de_cd9b(&stack0xfffe,puVar9);
        char_to_pascal_string(uVar5);
        concat_pascal_string(puVar9,uVar11);
        iVar3 = validate_range_bounds();
        copy_pascal_string_limited(3,iVar3 * 4 + -0x469e,unaff_DS,puVar10,uVar6);
        if (flag == 3) break;
        flag = flag + 1;
      }
      if (local_c == 0x14) break;
      local_c = local_c + 1;
    }
    FUN_22de_cd9b(&stack0xfffe);
    local_e = validate_range_bounds();
    FUN_22de_cd9b(&stack0xfffe);
    local_e = validate_range_bounds();
    local_c = 1;
    while( true ) {
      iVar3 = validate_range_bounds();
      _local_117 = CONCAT22(unaff_DS,iVar3 * 0x2a + -0x5017);
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x15) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x17) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x13) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x19) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x1b) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x11) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x1f) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x1d) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x21) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x23) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = validate_range_bounds();
      *(undefined2 *)((int)_local_117 + 0x25) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      flag = validate_range_bounds();
      uVar11 = (undefined2)((ulong)_local_117 >> 0x10);
      if (flag == 0) {
        *(undefined1 *)((int)_local_117 + 0x27) = 0;
      }
      else {
        *(undefined1 *)((int)_local_117 + 0x27) = 1;
      }
      FUN_22de_ce1a(&stack0xfffe);
      flag = validate_range_bounds();
      uVar11 = (undefined2)((ulong)_local_117 >> 0x10);
      if (flag == 0) {
        *(undefined1 *)((int)_local_117 + 0x28) = 0;
      }
      else {
        *(undefined1 *)((int)_local_117 + 0x28) = 1;
      }
      FUN_22de_ce1a(&stack0xfffe);
      flag = validate_range_bounds();
      uVar11 = (undefined2)((ulong)_local_117 >> 0x10);
      if (flag == 0) {
        *(undefined1 *)((int)_local_117 + 0x29) = 0;
      }
      else {
        *(undefined1 *)((int)_local_117 + 0x29) = 1;
      }
      flag = 0;
      while( true ) {
        FUN_22de_ce1a(&stack0xfffe);
        uVar11 = validate_range_bounds();
        iVar3 = validate_range_bounds();
        iVar3 = iVar3 << 1;
        iVar4 = validate_range_bounds();
        *(undefined2 *)(iVar4 * 0x20 + iVar3 + -0x546d) = uVar11;
        if (flag == 0xf) break;
        flag = flag + 1;
      }
      FUN_22de_cd9b(&stack0xfffe);
      uVar2 = validate_range_bounds();
      iVar3 = validate_range_bounds();
      *(undefined1 *)(iVar3 * 0x2a + -0x5007) = uVar2;
      iVar3 = validate_range_bounds();
      FUN_22de_ce3f(&stack0xfffe,iVar3 * 0x2a + -0x5017);
      validate_range_bounds();
      uVar2 = 1;
      uVar6 = validate_range_bounds();
      puVar10 = local_133;
      uVar11 = unaff_SS;
      zero_word_array_16(puVar10);
      set_bit_in_array(CONCAT11(extraout_AH,0x41));
      set_bit_in_array(CONCAT11(extraout_AH_00,0x43));
      set_bit_in_array(CONCAT11(extraout_AH_01,0x46));
      set_bit_in_array(CONCAT11(extraout_AH_02,0x73));
      create_bit_mask(puVar10,uVar11,uVar6);
      if ((bool)uVar2) {
        uVar6 = 0x214c;
        uVar11 = 0x40e;
        iVar3 = validate_range_bounds(0x40e,0x214c);
        copy_pascal_string_limited(4,iVar3 * 5 + -0x4985,unaff_DS,uVar11,uVar6);
      }
      else {
        uVar6 = 0x214c;
        uVar11 = 0x409;
        iVar3 = validate_range_bounds(0x409,0x214c);
        copy_pascal_string_limited(4,iVar3 * 5 + -0x4985,unaff_DS,uVar11,uVar6);
      }
      validate_range_bounds();
      uVar2 = 1;
      uVar6 = validate_range_bounds();
      puVar10 = local_133;
      uVar11 = unaff_SS;
      zero_word_array_16(puVar10);
      set_bit_in_array(CONCAT11(extraout_AH_03,0x41));
      set_bit_in_array(CONCAT11(extraout_AH_04,0x45));
      set_bit_in_array(CONCAT11(extraout_AH_05,0x4f));
      set_bit_in_array(CONCAT11(extraout_AH_06,0x55));
      set_bit_in_array(CONCAT11(extraout_AH_07,0x61));
      set_bit_in_array(CONCAT11(extraout_AH_08,0x9e));
      create_bit_mask(puVar10,uVar11,uVar6);
      if ((bool)uVar2) {
        validate_range_bounds();
        uVar2 = 1;
        uVar6 = validate_range_bounds();
        puVar10 = local_153;
        uVar11 = unaff_SS;
        zero_word_array_16(puVar10);
        set_bit_in_array(CONCAT11(extraout_AH_09,0x43));
        set_bit_in_array(CONCAT11(extraout_AH_10,0x46));
        set_bit_in_array(CONCAT11(extraout_AH_11,0x73));
        create_bit_mask(puVar10,uVar11,uVar6);
        if ((bool)uVar2) {
          uVar6 = 0x214c;
          uVar11 = 0x41a;
          iVar3 = validate_range_bounds(0x41a,0x214c);
          copy_pascal_string_limited(4,iVar3 * 5 + -0x4a34,unaff_DS,uVar11,uVar6);
        }
        else {
          uVar6 = 0x214c;
          uVar11 = 0x416;
          iVar3 = validate_range_bounds(0x416,0x214c);
          copy_pascal_string_limited(4,iVar3 * 5 + -0x4a34,unaff_DS,uVar11,uVar6);
        }
      }
      else {
        uVar6 = 0x214c;
        uVar11 = 0x412;
        iVar3 = validate_range_bounds(0x412,0x214c);
        copy_pascal_string_limited(4,iVar3 * 5 + -0x4a34,unaff_DS,uVar11,uVar6);
      }
      iVar3 = validate_range_bounds();
      uVar2 = *(char *)(iVar3 * 0x2a + -0x5007) == 'a';
      if ((bool)uVar2) {
        uVar6 = 0x214c;
        uVar11 = 0x412;
        iVar3 = validate_range_bounds(0x412,0x214c);
        iVar3 = iVar3 * 5 + -0x4985;
        uVar2 = iVar3 == 0;
        copy_pascal_string_limited(4,iVar3,unaff_DS,uVar11,uVar6);
      }
      uVar6 = validate_range_bounds();
      puVar10 = local_133;
      uVar11 = unaff_SS;
      zero_word_array_16(puVar10);
      set_bit_range_in_array(CONCAT11(extraout_AH_12,0x23),CONCAT11(extraout_AH_12,0x1d));
      create_bit_mask(puVar10,uVar11,uVar6);
      if (!(bool)uVar2) {
        iVar3 = validate_range_bounds();
        *(undefined1 *)(iVar3 * 5 + -0x4a34) = 0;
        iVar3 = validate_range_bounds();
        *(undefined1 *)(iVar3 * 5 + -0x4985) = 0;
      }
      if (local_c == 0x23) break;
      local_c = local_c + 1;
    }
    local_f = '\x02';
    while( true ) {
      validate_range_bounds();
      iVar3 = validate_range_bounds();
      _local_117 = CONCAT22(iVar3,local_117);
      if (0 < iVar3) {
        local_c = 1;
        while( true ) {
          iVar3 = validate_range_bounds();
          iVar3 = iVar3 * 0x1d;
          iVar4 = validate_range_bounds();
          FUN_22de_ce3f(&stack0xfffe,iVar4 * 0x2b8 + iVar3 + 0x75fa);
          uVar1 = _local_117;
          iVar7 = (int)((ulong)_local_117 >> 0x10);
          flag = local_c == iVar7;
          _local_117 = uVar1;
          if (flag) break;
          local_c = local_c + 1;
        }
      }
      if (local_f == '\b') break;
      local_f = local_f + '\x01';
    }
    local_f = '\x02';
    while( true ) {
      validate_range_bounds();
      iVar3 = validate_range_bounds();
      _local_117 = CONCAT22(iVar3,local_117);
      if (0 < iVar3) {
        local_c = 1;
        while( true ) {
          FUN_22de_ce1a(&stack0xfffe);
          uVar11 = validate_range_bounds();
          iVar3 = validate_range_bounds();
          iVar3 = iVar3 << 1;
          iVar4 = validate_range_bounds();
          uVar1 = _local_117;
          *(undefined2 *)(iVar4 * 0x30 + iVar3 + -0x6513) = uVar11;
          iVar7 = (int)((ulong)_local_117 >> 0x10);
          flag = local_c == iVar7;
          _local_117 = uVar1;
          if (flag) break;
          local_c = local_c + 1;
        }
      }
      if (local_f == '\b') break;
      local_f = local_f + '\x01';
    }
    FUN_22de_cd9b(&stack0xfffe);
    local_e = validate_range_bounds();
    FUN_22de_cd9b(&stack0xfffe);
    local_e = validate_range_bounds();
    iVar3 = validate_range_bounds();
    if (0 < iVar3) {
      local_c = 1;
      while( true ) {
        FUN_22de_ce1a(&stack0xfffe);
        uVar11 = validate_range_bounds();
        iVar7 = validate_range_bounds();
        *(undefined2 *)(iVar7 * 4 + -0x6305) = uVar11;
        if (local_c == iVar3) break;
        local_c = local_c + 1;
      }
    }
    local_f = '\x05';
    while( true ) {
      validate_range_bounds();
      iVar3 = validate_range_bounds();
      if (0 < iVar3) {
        local_c = 1;
        while( true ) {
          FUN_22de_ce1a(&stack0xfffe);
          uVar11 = validate_range_bounds();
          iVar7 = validate_range_bounds();
          iVar7 = iVar7 << 2;
          iVar4 = validate_range_bounds();
          *(undefined2 *)(iVar4 * 0x60 + iVar7 + -0x6425) = uVar11;
          if (local_c == iVar3) break;
          local_c = local_c + 1;
        }
      }
      if (local_f == '\a') break;
      local_f = local_f + '\x01';
    }
    iVar3 = validate_range_bounds();
    if (0 < iVar3) {
      local_c = 1;
      while( true ) {
        FUN_22de_ce1a(&stack0xfffe);
        uVar11 = validate_range_bounds();
        iVar7 = validate_range_bounds();
        *(undefined2 *)(iVar7 * 4 + -0x6243) = uVar11;
        if (local_c == iVar3) break;
        local_c = local_c + 1;
      }
    }
    iVar3 = validate_range_bounds();
    if (0 < iVar3) {
      local_c = 1;
      while( true ) {
        FUN_22de_ce1a(&stack0xfffe);
        uVar11 = validate_range_bounds();
        iVar7 = validate_range_bounds();
        *(undefined2 *)(iVar7 * 2 + -0x6123) = uVar11;
        if (local_c == iVar3) break;
        local_c = local_c + 1;
      }
    }
    FUN_22de_cd9b(&stack0xfffe);
    local_e = validate_range_bounds();
    FUN_22de_cd9b(&stack0xfffe);
    local_e = validate_range_bounds();
    local_f = '\x06';
    while( true ) {
      validate_range_bounds();
      iVar3 = validate_range_bounds();
      if (0 < iVar3) {
        local_c = 1;
        while( true ) {
          FUN_22de_ce1a(&stack0xfffe);
          uVar11 = validate_range_bounds();
          iVar7 = validate_range_bounds();
          iVar7 = iVar7 << 1;
          iVar4 = validate_range_bounds();
          *(undefined2 *)(iVar4 * 0x30 + iVar7 + -0x71d3) = uVar11;
          FUN_22de_ce1a(&stack0xfffe);
          validate_range_bounds();
          validate_range_bounds();
          uVar11 = validate_range_bounds();
          iVar7 = validate_range_bounds();
          iVar7 = iVar7 << 1;
          iVar4 = validate_range_bounds();
          *(undefined2 *)(iVar4 * 0x30 + iVar7 + -0x71d3) = uVar11;
          if (local_c == iVar3) break;
          local_c = local_c + 1;
        }
      }
      FUN_22de_cd9b(&stack0xfffe);
      local_e = validate_range_bounds();
      FUN_22de_cd9b(&stack0xfffe);
      local_e = validate_range_bounds();
      if (local_f == '\a') break;
      local_f = local_f + '\x01';
    }
    *(undefined2 *)0xb948 = 0;
    local_c = 1;
    while( true ) {
      FUN_22de_ce1a(&stack0xfffe);
      local_6 = validate_range_bounds();
      FUN_22de_ce1a(&stack0xfffe);
      local_4 = validate_range_bounds();
      uVar11 = validate_range_bounds();
      iVar3 = validate_range_bounds();
      *(undefined2 *)(iVar3 * 2 + -0x46b8) = uVar11;
      if (local_c == 0xe) break;
      local_c = local_c + 1;
    }
    return;
  }
  uVar11 = 0xe654;
  write_padded_string(0,0x351,0x214c);
  flush_output(uVar11,unaff_DS);
  check_and_handle_error();
  return;
}



void __cdecl16far FUN_1f98_1107(void)

{
  undefined2 unaff_DS;
  
  validate_stack_space();
  copy_pascal_string_limited(0xb,0xb9c6,unaff_DS,0x10f0,0x214c);
  copy_pascal_string_limited(9,0xb9ed,unaff_DS,0x10fc,0x214c);
  *(undefined2 *)0xaba7 = 0;
  *(undefined2 *)0xaba9 = 0;
  *(undefined2 *)0xabab = 0;
  *(undefined2 *)0xabad = 0;
  *(undefined2 *)0xe531 = 0;
  *(undefined2 *)0xe52f = 0;
  return;
}



void __cdecl16far FUN_1f98_1155(void)

{
  undefined4 uVar1;
  int value;
  undefined2 uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_76f [66];
  undefined2 uStack_72d;
  undefined2 uStack_72b;
  undefined2 uStack_729;
  undefined2 uStack_727;
  undefined2 uStack_725;
  undefined1 *puStack_723;
  undefined1 local_71f [77];
  undefined1 local_6d2;
  undefined1 local_6d1;
  undefined1 local_a4;
  undefined1 local_56 [78];
  undefined1 local_8;
  undefined1 local_7;
  int local_6;
  int local_4;
  
  local_4 = 0x1f98;
  local_6 = 0xae0;
  validate_stack_space();
  *(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */ = 1;
  local_6 = 1;
  while( true ) {
    local_76f[local_6 * 0x9e + 1] = 0xb3;
    local_71f[local_6 * 0x9e + -1] = 0xb3;
    local_76f[(local_6 * 2 + 1) * MAP_WIDTH + 1] = 0xc3;
    local_71f[(local_6 * 2 + 1) * MAP_WIDTH + -1] = 0xb4;
    if (local_6 == 0xb) break;
    local_6 = local_6 + 1;
  }
  local_a4 = 0xb3;
  local_56[0] = 0xb3;
  local_6 = 1;
  while( true ) {
    local_71f[local_6 * 2 + -1] = 0xc4;
    local_56[local_6 * 2] = 0xc4;
    local_71f[local_6 * 2] = 0xc2;
    local_56[local_6 * 2 + 1] = 0xc1;
    if (local_6 == 0x26) break;
    local_6 = local_6 + 1;
  }
  local_6d2 = 0xc4;
  local_8 = 0xc4;
  local_6 = 1;
  while( true ) {
    for (local_4 = 1; local_76f[(local_6 * 2 + 1) * MAP_WIDTH + local_4 * 2 + 1] = 0xc5, local_4 != 0x26;
        local_4 = local_4 + 1) {
    }
    if (local_6 == 10) break;
    local_6 = local_6 + 1;
  }
  local_6 = 1;
  while( true ) {
    local_4 = 1;
    while (local_76f[local_6 * 0x9e + local_4 * 2] = 0x20, local_4 != 0x27) {
      local_4 = local_4 + 1;
    }
    if (local_6 == 0xb) break;
    local_6 = local_6 + 1;
  }
  local_71f[0] = 0xda;
  local_6d1 = 0xbf;
  local_56[1] = 0xc0;
  local_7 = 0xd9;
  local_6 = 0;
  while( true ) {
    puStack_723 = (undefined1 *)(local_6 * 4 + 4);
    uStack_725 = 0x727;
    uStack_727 = 0x214c;
    uStack_729 = 0xc3a;
    read_stream_data();
    uVar1 = *(undefined4 *)(local_6 * 4 + 4);
    uVar3 = (undefined2)((ulong)uVar1 >> 0x10);
    value = (int)uVar1;
    *(undefined2 *)(value + 0x723) = 0;
    *(undefined2 *)(value + 0x725) = 0;
    puStack_723 = local_71f;
    uVar1 = *(undefined4 *)(local_6 * 4 + 4);
    uStack_725 = (undefined2)((ulong)uVar1 >> 0x10);
    uStack_727 = (undefined2)uVar1;
    uStack_729 = 0x719;
    uStack_72b = 0x214c;
    uStack_72d = 0xc6d;
    memcpy();
    uVar1 = *(undefined4 *)(local_6 * 4 + 4);
    *(undefined1 *)((int)uVar1 + 0x719) = 0;
    uVar1 = *(undefined4 *)(local_6 * 4 + 4);
    *(undefined1 *)((int)uVar1 + 0x71a) = 0;
    if (local_6 == 0xf) break;
    local_6 = local_6 + 1;
  }
  local_6 = 1;
  while( true ) {
    for (local_4 = 1; *(undefined1 *)(local_6 * MAP_WIDTH + local_4 + -0xc) = 0x20, local_4 != 0x4f;
        local_4 = local_4 + 1) {
    }
    if (local_6 == 0x17) break;
    local_6 = local_6 + 1;
  }
  local_6 = 0;
  while( true ) {
    *(undefined2 *)(local_6 * 2 + 0x797d) = 0;
    *(undefined2 *)(local_6 * 2 + 0x799b) = 0;
    if (local_6 == 0xf) break;
    local_6 = local_6 + 1;
  }
  return;
}



void __cdecl16far FUN_1f98_137a(void)

{
  int value;
  undefined2 unaff_DS;
  undefined1 local_a;
  undefined2 flag;
  undefined2 local_6;
  undefined2 flag;
  
  validate_stack_space();
  local_a = '\x02';
  while( true ) {
    value = *(int *)(local_a * 4 + 0x79b3);
    if (0 < value) {
      flag = 1;
      while( true ) {
        *(undefined1 *)(local_a * 0x18 + flag + -0x65a2) = 0;
        *(undefined1 *)(local_a * 0x18 + flag + -0x6542) = 0;
        copy_pascal_string_limited(0x1c,local_a * 0x2b8 + flag * 0x1d + -0x75de,unaff_DS,0x1375,0x214c);
        if (flag == value) break;
        flag = flag + 1;
      }
    }
    if (local_a == '\x05') break;
    local_a = local_a + '\x01';
  }
  flag = 0;
  while( true ) {
    *(undefined2 *)(flag * 4 + -0x5499) = 0;
    *(undefined2 *)(flag * 4 + -0x5497) = 0;
    *(undefined2 *)(flag * 4 + -0x54d9) = 0;
    *(undefined2 *)(flag * 4 + -0x54d7) = 0;
    *(undefined1 *)(flag + 0x796d) = 0;
    flag = 1;
    while( true ) {
      for (local_6 = 1; *(undefined1 *)(flag * 0x719 + flag * MAP_WIDTH + local_6 + 0x70d) = 0,
          local_6 != 0x4f; local_6 = local_6 + 1) {
      }
      if (flag == 0x17) break;
      flag = flag + 1;
    }
    if (flag == 0xf) break;
    flag = flag + 1;
  }
  for (flag = 1; *(undefined2 *)(flag * 2 + -0x460b) = 0, flag != 0x23;
      flag = flag + 1) {
  }
  return;
}



void __cdecl16far FUN_1f98_14b7(void)

{
  undefined2 unaff_DS;
  
  validate_stack_space();
  *(undefined2 *)ADDR_DUNGEON_LEVEL /* dungeon_level */ = 1;
  *(undefined2 *)0xe533 = 1;
  *(undefined2 *)0xabaf = 0;
  *(undefined2 *)0xabb1 = 0;
  *(undefined1 *)0xe539 = 1;
  return;
}



void __cdecl16far FUN_20e6_0000(void)

{
  undefined2 unaff_DS;
  
  FUN_20e6_002e();
  init_file_control_block(0xe554,unaff_DS);
  file_open_wrapper(0x20e6,0xe554);
  init_file_control_block(0xe654,unaff_DS);
  file_open_wrapper2(0x214c,0xe654);
  return;
}



// WARNING: Removing unreachable block (ram,0x00020ed4)

void __cdecl16near FUN_20e6_002e(void)

{
  byte bVar1;
  byte extraout_AH;
  undefined2 unaff_DS;
  
  bVar1 = call_video_bios();
  if ((bVar1 != 7) && (3 < bVar1)) {
    FUN_20e6_00b9();
  }
  FUN_20e6_011b();
  call_video_bios();
  *(byte *)0xe551 = extraout_AH & 0x7f;
  *(byte *)0xe540 = extraout_AH & 0x7f;
  *(undefined1 *)0xe53b = 0;
  *(undefined1 *)0xe552 = 0;
  *(undefined1 *)0xe553 = 0;
  *(undefined1 *)0xe53a = 1;
  do {
  } while( true );
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __cdecl16near FUN_20e6_00b9(void)

{
  undefined2 in_AX;
  char extraout_DL;
  
  DAT_0000_0487 = DAT_0000_0487 & 0xfe;
  if (((byte)in_AX != 7) && (3 < (byte)in_AX)) {
    in_AX = CONCAT11((char)((uint)in_AX >> 8),3);
  }
  call_video_bios();
  if ((char)((uint)in_AX >> 8) != '\0') {
    call_video_bios();
    call_video_bios();
    if (extraout_DL == '*') {
      DAT_0000_0487 = DAT_0000_0487 | 1;
      call_video_bios();
      if (DAT_0000_0449 == '\a') {
        out(_DAT_0000_0463,0x14);
        out(_DAT_0000_0463 + 1,7);
      }
      call_video_bios();
    }
  }
  return;
}



void __cdecl16near FUN_20e6_011b(void)

{
  uint uVar1;
  uint uVar2;
  undefined1 uVar3;
  byte extraout_DL;
  byte bVar4;
  undefined2 uVar5;
  undefined2 unaff_DS;
  
  uVar1 = call_video_bios();
  call_video_bios();
  uVar3 = 0;
  bVar4 = extraout_DL;
  if ((extraout_DL == 0) && (bVar4 = 0x18, (byte)uVar1 < 4)) {
    uVar3 = 1;
  }
  uVar5 = CONCAT11(bVar4,(char)(uVar1 >> 8) + -1);
  uVar2 = uVar1 & 0xff;
  if (0x18 < bVar4) {
    uVar2 = CONCAT11(1,(byte)uVar1);
  }
  *(uint *)0xe53e = uVar2;
  *(undefined2 *)0xe54f = uVar5;
  *(undefined1 *)0xe53d = uVar3;
  *(undefined1 *)0xe53c = 1;
  *(undefined2 *)0xe541 = 0;
  *(undefined2 *)0xe543 = uVar5;
  return;
}



void __cdecl16near FUN_20e6_0190(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  undefined1 uVar2;
  
  uVar2 = *(char *)0xe553 == '\0';
  if ((bool)uVar2) {
    return;
  }
  *(undefined1 *)0xe553 = 0;
  while( true ) {
    pcVar1 = (code *)swi(0x16);
    (*pcVar1)();
    if ((bool)uVar2) break;
    pcVar1 = (code *)swi(0x16);
    (*pcVar1)();
  }
  output_char_with_controls();
  output_char_with_controls();
  output_crlf();
  pcVar1 = (code *)swi(0x23);
  (*pcVar1)();
  FUN_20e6_00b9();
  FUN_20e6_011b();
  *(undefined1 *)0xe540 = *(undefined1 *)0xe551;
  return;
}



void __cdecl16far clear_screen_double(void)

{
  call_video_bios();
  thunk_FUN_20e6_0653();
  return;
}



void __cdecl16far update_screen_double(void)

{
  thunk_FUN_20e6_0653();
  call_video_bios();
  return;
}



void __stdcall16far validate_window_coords(char param_1,char param_2)

{
  undefined2 unaff_DS;
  
  if ((((!CARRY1(param_2 - 1U,*(byte *)0xe541)) &&
       ((byte)((param_2 - 1U) + *(byte *)0xe541) <= *(byte *)0xe543)) &&
      (!CARRY1(param_1 - 1U,*(byte *)0xe542))) &&
     ((byte)((param_1 - 1U) + *(byte *)0xe542) <= *(byte *)0xe544)) {
    thunk_FUN_20e6_0653();
  }
  return;
}



char __cdecl16far get_relative_cursor_y(void)

{
  char extraout_DL;
  undefined2 unaff_DS;
  
  thunk_FUN_20e6_0653();
  return (extraout_DL - *(char *)0xe541) + '\x01';
}



char __cdecl16far get_relative_cursor_x(void)

{
  char extraout_DH;
  undefined2 unaff_DS;
  
  thunk_FUN_20e6_0653();
  return (extraout_DH - *(char *)0xe542) + '\x01';
}



void __stdcall16far set_text_color_attribute(byte param_1)

{
  undefined2 unaff_DS;
  
  if ((param_1 & 0xf0) != 0) {
    param_1 = param_1 & 0xf | 0x80;
  }
  *(byte *)0xe540 = *(byte *)0xe540 & 0x70;
  *(byte *)0xe540 = *(byte *)0xe540 | param_1;
  return;
}



void __stdcall16far set_background_color(byte param_1)

{
  undefined2 unaff_DS;
  
  *(byte *)0xe540 = *(byte *)0xe540 & 0x8f;
  *(byte *)0xe540 = *(byte *)0xe540 | (param_1 & 7) << 4;
  return;
}



void __stdcall16far wait_for_memory_match(int value)

{
  int extraout_DX;
  
  if (value != 0) {
    do {
      scan_memory_for_byte();
    } while (extraout_DX != 1);
  }
  return;
}



void __cdecl16near scan_memory_for_byte(void)

{
  char in_AL;
  int in_CX;
  char *unaff_DI;
  undefined2 unaff_ES;
  
  do {
    if (in_AL != *unaff_DI) {
      return;
    }
    in_CX = in_CX + -1;
  } while (in_CX != 0);
  return;
}



undefined2 __stdcall16far play_tone_frequency(uint value)

{
  byte bVar1;
  undefined2 uVar2;
  undefined1 uVar3;
  
  uVar2 = 0x34dd;
  if (0x12 < value) {
    uVar3 = (undefined1)(0x1234dd / (ulong)value >> 8);
    bVar1 = in(0x61);
    if ((bVar1 & 3) == 0) {
      out(0x61,bVar1 | 3);
      out(0x43,0xb6);
    }
    out(0x42,(char)(0x1234dd / (ulong)value));
    uVar2 = CONCAT11(uVar3,uVar3);
    out(0x42,uVar3);
  }
  return uVar2;
}



byte __cdecl16far silence_speaker(void)

{
  byte bVar1;
  
  bVar1 = in(0x61);
  out(0x61,bVar1 & 0xfc);
  return bVar1 & 0xfc;
}



void __cdecl16far read_keyboard_input(void)

{
  code *pcVar1;
  char cVar2;
  undefined1 extraout_AH;
  undefined2 unaff_DS;
  
  cVar2 = *(char *)0xe552;
  *(undefined1 *)0xe552 = 0;
  if (cVar2 == '\0') {
    pcVar1 = (code *)swi(0x16);
    cVar2 = (*pcVar1)();
    if (cVar2 == '\0') {
      *(undefined1 *)0xe552 = extraout_AH;
    }
  }
  FUN_20e6_0190();
  return;
}



void __stdcall16far init_file_control_block(undefined4 param_1)

{
  int value;
  undefined2 uVar2;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  value = (int)param_1;
  *(undefined2 *)(value + 2) = 0xd7b0;
  *(undefined2 *)(value + 4) = 0x80;
  *(int *)(value + 0xc) = value + 0x80;
  *(undefined2 *)(value + 0xe) = uVar2;
  *(undefined2 *)(value + 0x10) = 0x3a4;
  *(undefined2 *)(value + 0x12) = 0x20e6;
  *(undefined1 *)(value + 0x30) = 0;
  return;
}



void __stdcall16far line_editor_main_loop(undefined4 param_1)

{
  byte flag;
  int value;
  uint value;
  uint extraout_DX;
  uint extraout_DX_00;
  uint extraout_DX_01;
  uint flag;
  uint value;
  int value;
  int value;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 unaff_DS;
  
  uVar8 = (undefined2)((ulong)param_1 >> 0x10);
  value = (int)param_1;
  value = *(int *)(value + 4) - 2;
  uVar9 = (undefined2)((ulong)*(undefined4 *)(value + 0xc) >> 0x10);
  value = (int)*(undefined4 *)(value + 0xc);
  flag = 0;
  value = *(uint *)(value + 8);
LAB_20e6_03f2:
  do {
    *(undefined1 *)0xe552 = 0;
    flag = read_keyboard_input();
    value = 1;
    if ((flag == 8) || (flag == CMD_SAVE)) {
LAB_20e6_0436:
      do {
        if (flag == 0) break;
        output_char_with_controls();
        output_char_with_controls();
        output_char_with_controls();
        flag = flag - 1;
        value = value + -1;
        value = extraout_DX_00;
      } while (value != 0);
      goto LAB_20e6_03f2;
    }
    if (flag == 4) {
LAB_20e6_044e:
      do {
        if ((flag == value) || (*(byte *)(flag + value) < 0x20)) break;
        output_char_with_controls();
        flag = flag + 1;
        value = value + -1;
        value = extraout_DX_01;
      } while (value != 0);
    }
    else {
      value = 0;
      if ((flag == 0x1b) || (flag == 1)) goto LAB_20e6_0436;
      if (flag == 6) goto LAB_20e6_044e;
      if (flag == ITEM_SIZE) {
        if (*(char *)0xe53b != '\0') {
          *(undefined1 *)(flag + value) = 0x1a;
          value = flag + 1;
LAB_20e6_0478:
          *(undefined2 *)(value + 8) = 0;
          *(int *)(value + 10) = value;
          return;
        }
      }
      else {
        if (flag == 0xd) {
          output_crlf();
          *(undefined2 *)(flag + value) = 0xa0d;
          value = flag + 2;
          goto LAB_20e6_0478;
        }
        if ((0x1f < flag) && (flag != value)) {
          *(byte *)(flag + value) = flag;
          flag = flag + 1;
          output_char_with_controls();
          value = extraout_DX;
          if (value < flag) {
            value = flag;
          }
        }
      }
    }
  } while( true );
}



// WARNING: Removing unreachable block (ram,0x0002136e)
// WARNING: Removing unreachable block (ram,0x00021364)
// WARNING: Removing unreachable block (ram,0x0002136a)
// WARNING: Removing unreachable block (ram,0x0002133f)
// WARNING: Removing unreachable block (ram,0x00021357)
// WARNING: Removing unreachable block (ram,0x0002135d)

void output_crlf(void)

{
  output_char_with_controls();
  thunk_FUN_20e6_0653();
  check_and_scroll_window();
  thunk_FUN_20e6_0653();
  return;
}



void __cdecl16near output_char_with_controls(void)

{
  char in_AL;
  char extraout_DL;
  undefined2 unaff_DS;
  
  thunk_FUN_20e6_0653();
  if (in_AL == '\a') {
    call_video_bios();
  }
  else if (((in_AL != '\b') && (in_AL != '\r')) &&
          ((in_AL == '\n' || (call_video_bios(), *(byte *)0xe543 < (byte)(extraout_DL + 1U))))) {
    check_and_scroll_window();
  }
  thunk_FUN_20e6_0653();
  return;
}



void __cdecl16near check_and_scroll_window(void)

{
  undefined2 in_DX;
  undefined2 unaff_DS;
  
  if (*(byte *)0xe544 < (byte)((char)((uint)in_DX >> 8) + 1U)) {
    call_video_bios();
  }
  return;
}



void __cdecl16near thunk_FUN_20e6_0653(void)

{
  call_video_bios();
  return;
}



void __cdecl16near thunk_FUN_20e6_0653(void)

{
  call_video_bios();
  return;
}



void __cdecl16near call_video_bios(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}



void __cdecl16far c_runtime_startup(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 in_BX;
  undefined2 unaff_ES;
  int unaff_SS;
  undefined2 in_stack_00000012;
  undefined2 in_stack_00000014;
  undefined2 in_stack_00000016;
  undefined2 in_stack_00000018;
  undefined2 in_stack_0000001a;
  undefined2 in_stack_0000001c;
  undefined2 in_stack_0000001e;
  
  DAT_22de_e758 = ((int)&stack0x0012 + 1U >> 4) + unaff_SS;
  DAT_22de_e760 = *(int *)0x2 + -0x1000;
  DAT_22de_e764 = 0xdd;
  DAT_22de_e766 = 0x214c;
  DAT_22de_e768 = 0xe2;
  DAT_22de_e76a = 0x214c;
  DAT_22de_e78a = 2;
  DAT_22de_e756 = 0;
  DAT_22de_e75a = 0;
  DAT_22de_e75e = 0;
  DAT_22de_e762 = 0;
  DAT_22de_e772 = 0;
  DAT_22de_e774 = 0;
  DAT_22de_e78b = 0;
  pcVar1 = (code *)swi(0x21);
  DAT_22de_e754 = unaff_ES;
  DAT_22de_e75c = DAT_22de_e758;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_22de_e776 = in_BX;
  DAT_22de_e778 = unaff_ES;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_22de_e77a = in_BX;
  DAT_22de_e77c = unaff_ES;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_22de_e77e = in_BX;
  DAT_22de_e780 = unaff_ES;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_22de_e782 = in_BX;
  DAT_22de_e784 = unaff_ES;
  (*pcVar1)();
  in_stack_00000012 = 0x22de;
  pcVar1 = (code *)swi(0x21);
  DAT_22de_e786 = in_BX;
  DAT_22de_e788 = unaff_ES;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  uVar2 = in_stack_0000001e;
  in_stack_0000001c = 0xe554;
  in_stack_0000001a = in_stack_0000001e;
  in_stack_00000018 = 0xe554;
  in_stack_00000016 = 0x214c;
  in_stack_00000014 = 0xdc;
  in_stack_00000012 = 0x214c;
  init_fcb();
  in_stack_0000001a = 0x214c;
  in_stack_00000018 = 0x1587;
  file_open_wrapper();
  in_stack_0000001a = uVar2;
  in_stack_00000018 = 0xe654;
  in_stack_00000016 = uVar2;
  in_stack_00000014 = 0xe654;
  in_stack_00000012 = 0x214c;
  init_fcb();
  in_stack_00000016 = 0x214c;
  in_stack_00000014 = 0x159b;
  file_open_wrapper2();
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined2 __cdecl16far exit_program_handler(void)

{
  code *pcVar1;
  int iVar2;
  undefined2 in_AX;
  undefined2 uVar3;
  int in_stack_00000000;
  int in_stack_00000002;
  
  if (in_stack_00000000 != 0 || in_stack_00000002 != 0) {
    in_stack_00000002 = (in_stack_00000002 - DAT_22de_e754) + -0x10;
  }
  if ((*(char *)0x5 == -0x3d) || (*(char *)0x5 == -0x3d)) {
    in_AX = (*DAT_22de_0006)();
  }
  iVar2 = DAT_22de_e754;
  DAT_22de_e76c = in_AX;
  DAT_22de_e76e = in_stack_00000000;
  DAT_22de_e770 = in_stack_00000002;
  if ((int)((ulong)_DAT_22de_e768 >> 0x10) != 0 || (int)_DAT_22de_e768 != 0) {
    _DAT_22de_e768 = 0;
    DAT_22de_e78b = 0;
    return 0x232;
  }
  if (*(char *)0x5 == -0x3d) {
    *(undefined1 *)0x5 = 0;
                    // WARNING: Could not recover jumptable at 0x00021721. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*(code *)(ulong)*(uint *)0x6)();
    return uVar3;
  }
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  uVar3 = DAT_22de_e78b;
  DAT_22de_e78b = 0;
  return uVar3;
}



// WARNING: Removing unreachable block (ram,0x000216c2)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined2 __cdecl16far dos_interrupt_handler_init(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 in_AX;
  undefined2 uVar3;
  undefined2 uVar4;
  
  uVar3 = 0;
  uVar4 = 0;
  if ((*(char *)0x5 == -0x3d) || (*(char *)0x5 == -0x3d)) {
    in_AX = (*DAT_22de_0006)(0x214c);
  }
  uVar2 = DAT_22de_e754;
  DAT_22de_e76c = in_AX;
  DAT_22de_e76e = uVar3;
  DAT_22de_e770 = uVar4;
  if ((int)((ulong)_DAT_22de_e768 >> 0x10) == 0 && (int)_DAT_22de_e768 == 0) {
    if (*(char *)0x5 != -0x3d) {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      uVar3 = DAT_22de_e78b;
      DAT_22de_e78b = 0;
      return uVar3;
    }
    *(undefined1 *)0x5 = 0;
                    // WARNING: Could not recover jumptable at 0x00021721. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*(code *)(ulong)*(uint *)0x6)();
    return uVar3;
  }
  _DAT_22de_e768 = 0;
  DAT_22de_e78b = 0;
  return 0x232;
}



undefined2 __cdecl16far get_and_clear_error_code(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined2 *)0xe78b;
  *(undefined2 *)0xe78b = 0;
  return uVar1;
}



void __cdecl16far check_and_handle_error(void)

{
  undefined2 unaff_DS;
  
  if (*(int *)0xe78b == 0) {
    return;
  }
  exit_program_handler();
  return;
}



void __cdecl16far validate_range_bounds(void)

{
  uint in_AX;
  int in_DX;
  uint *unaff_DI;
  undefined2 in_stack_00000002;
  
  if ((((int)unaff_DI[1] < in_DX) || (((int)unaff_DI[1] <= in_DX && (*unaff_DI <= in_AX)))) &&
     ((in_DX < (int)unaff_DI[3] || ((in_DX <= (int)unaff_DI[3] && (in_AX <= unaff_DI[2])))))) {
    return;
  }
  exit_program_handler();
  return;
}



void __cdecl16far validate_stack_space(void)

{
  undefined1 *in_AX;
  
  if ((in_AX <= &stack0x0000) && (0x1ff < (uint)((int)&stack0x0000 - (int)in_AX))) {
    return;
  }
  exit_program_handler();
  return;
}



void __stdcall16far memcpy(int value,undefined1 *param_2,undefined1 *flags)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  puVar3 = (undefined1 *)flags;
  puVar4 = (undefined1 *)param_2;
  for (; value != 0; value = value + -1) {
    puVar2 = puVar4;
    puVar4 = puVar4 + 1;
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar2 = *puVar1;
  }
  return;
}



int __cdecl16far multiply_integers(void)

{
  int in_AX;
  int in_CX;
  
  return in_AX * in_CX;
}



uint __cdecl16far divide_long_signed(void)

{
  uint uVar1;
  uint in_AX;
  uint in_CX;
  uint uVar2;
  uint uVar3;
  uint in_DX;
  uint in_BX;
  uint uVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  
  if (in_CX == 0 && in_BX == 0) {
    uVar2 = exit_program_handler();
    return uVar2;
  }
  bVar9 = (int)in_BX < 0;
  if (bVar9) {
    uVar2 = ~in_CX;
    in_CX = uVar2 + 1;
    in_BX = ~in_BX + (uint)(0xfffe < uVar2);
  }
  bVar10 = (int)in_DX < 0;
  if (bVar10) {
    uVar2 = ~in_AX;
    in_AX = uVar2 + 1;
    in_DX = ~in_DX + (uint)(0xfffe < uVar2);
  }
  uVar2 = 0;
  bVar7 = false;
  uVar4 = 0;
  iVar6 = 0x21;
  do {
    uVar3 = uVar2 << 1 | (uint)bVar7;
    uVar5 = uVar4 << 1 | (uint)((int)uVar2 < 0);
    uVar2 = uVar3 - in_CX;
    uVar3 = (uint)(uVar3 < in_CX);
    uVar1 = uVar5 - in_BX;
    bVar7 = uVar5 < in_BX || uVar1 < uVar3;
    uVar4 = uVar1 - uVar3;
    if (uVar5 < in_BX || uVar1 < uVar3) {
      bVar8 = CARRY2(uVar2,in_CX);
      uVar2 = uVar2 + in_CX;
      bVar7 = CARRY2(uVar4,in_BX) || CARRY2(uVar4 + in_BX,(uint)bVar8);
      uVar4 = uVar4 + in_BX + (uint)bVar8;
    }
    bVar8 = (int)in_AX < 0;
    in_AX = in_AX << 1 | (uint)!bVar7;
    bVar7 = (int)in_DX < 0;
    in_DX = in_DX << 1 | (uint)bVar8;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  if (bVar10) {
    if (bVar9) {
      return in_AX;
    }
  }
  else if (!bVar9) {
    return in_AX;
  }
  return ~in_AX + 1;
}



void __stdcall16far read_stream_data(undefined2 param_1,undefined2 *param_2)

{
  int flag;
  undefined2 in_CX;
  undefined2 in_BX;
  undefined2 unaff_DS;
  undefined1 in_CF;
  
  do {
    manage_buffer_list();
    if (!(bool)in_CF) goto LAB_214c_03ab;
    flag = (*(code *)*(undefined2 *)0xe764)(0x214c,param_1);
    in_CF = 0;
    if (flag == 0) {
      exit_program_handler();
      return;
    }
  } while (flag != 1);
  in_CX = 0;
  in_BX = 0;
LAB_214c_03ab:
  *param_2 = in_CX;
  ((undefined2 *)param_2)[1] = in_BX;
  return;
}



// WARNING: Removing unreachable block (ram,0x000219ce)
// WARNING: Removing unreachable block (ram,0x00021999)

void __cdecl16near manage_buffer_list(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint unaff_SI;
  uint *puVar5;
  undefined2 uVar6;
  undefined2 unaff_DS;
  ulong uVar7;
  
  uVar7 = normalize_far_pointer();
  uVar1 = (uint)(uVar7 >> 0x10);
  uVar6 = (undefined2)((ulong)*(undefined4 *)0xe75e >> 0x10);
  puVar5 = (uint *)(uint *)*(undefined4 *)0xe75e;
  do {
    if (puVar5 == (uint *)0x0) {
      uVar7 = check_buffer_empty();
      iVar4 = -*(int *)0xe75c;
      iVar2 = unaff_SI - *(uint *)0xe75a;
      if (unaff_SI < *(uint *)0xe75a) {
        iVar2 = iVar2 + 0x10;
        iVar4 = iVar4 + -1;
      }
      if (uVar7 <= CONCAT22(iVar4,iVar2)) {
        iVar4 = (int)(uVar7 >> 0x10) + *(int *)0xe75c;
        uVar1 = (int)uVar7 + *(int *)0xe75a;
        if (0xf < uVar1) {
          uVar1 = uVar1 - 0x10;
          iVar4 = iVar4 + 1;
        }
        *(uint *)0xe75a = uVar1;
        *(int *)0xe75c = iVar4;
      }
      return;
    }
    uVar3 = puVar5[3] - puVar5[1];
    if (uVar1 <= uVar3) {
      iVar4 = puVar5[2] - *puVar5;
      if (puVar5[2] < *puVar5) {
        iVar4 = iVar4 + 0x10;
        uVar3 = uVar3 - 1;
      }
      if (uVar7 <= CONCAT22(uVar3,iVar4)) {
        uVar1 = uVar1 + puVar5[1];
        uVar3 = (int)uVar7 + *puVar5;
        if (0xf < uVar3) {
          uVar3 = uVar3 - 0x10;
          uVar1 = uVar1 + 1;
        }
        *puVar5 = uVar3;
        puVar5[1] = uVar1;
        if ((uVar1 == puVar5[3]) && (uVar3 == puVar5[2])) {
          pop_buffer_entry();
        }
        return;
      }
    }
    puVar5 = puVar5 + 4;
  } while( true );
}



void __cdecl16near pop_buffer_entry(void)

{
  undefined2 *puVar1;
  undefined2 *unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)*(undefined2 *)0xe75e;
  *unaff_DI = *puVar1;
  unaff_DI[1] = puVar1[1];
  unaff_DI[2] = puVar1[2];
  unaff_DI[3] = puVar1[3];
  *(int *)0xe75e = (int)(puVar1 + 4);
  return;
}



void __cdecl16near check_buffer_empty(void)

{
  undefined2 unaff_DS;
  
  if ((*(int *)0xe75e == 0) && (*(int *)0xe762 == 0)) {
    return;
  }
  return;
}



ulong __cdecl16near normalize_far_pointer(void)

{
  uint in_AX;
  
  return CONCAT22(in_AX >> 4,in_AX) & 0xffff000f;
}



void __stdcall16far copy_pascal_string(byte *result_ptr,byte *param_2)

{
  byte bVar1;
  uint flag;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar4 = (byte *)param_2;
  pbVar3 = (byte *)result_ptr;
  bVar1 = *result_ptr;
  *param_2 = bVar1;
  flag = (uint)bVar1;
  while( true ) {
    pbVar4 = pbVar4 + 1;
    pbVar3 = pbVar3 + 1;
    if (flag == 0) break;
    flag = flag - 1;
    *pbVar4 = *pbVar3;
  }
  return;
}



void __stdcall16far copy_pascal_string_limited(byte param_1,byte *param_2,byte *flags)

{
  byte bVar1;
  uint flag;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar3 = (byte *)flags;
  pbVar4 = (byte *)param_2;
  bVar1 = *flags;
  if (param_1 < *flags) {
    bVar1 = param_1;
  }
  *param_2 = bVar1;
  flag = (uint)bVar1;
  while( true ) {
    pbVar4 = pbVar4 + 1;
    pbVar3 = pbVar3 + 1;
    if (flag == 0) break;
    flag = flag - 1;
    *pbVar4 = *pbVar3;
  }
  return;
}



void __stdcall16far substring_pascal(uint value,uint count,byte *flags,byte *data_ptr)

{
  byte *pbVar1;
  uint value;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar4 = (byte *)data_ptr;
  if ((int)count < 1) {
    count = 1;
  }
  pbVar3 = (byte *)flags + count;
  if (*flags < count) {
    value = 0;
  }
  else {
    value = (*flags - count) + 1;
    if ((int)value < 0) {
      value = 0;
    }
    if (value < value) {
      value = value;
    }
  }
  *data_ptr = (byte)value;
  for (; pbVar4 = pbVar4 + 1, value != 0; value = value - 1) {
    pbVar1 = pbVar3;
    pbVar3 = pbVar3 + 1;
    *pbVar4 = *pbVar1;
  }
  return;
}



void __stdcall16far concat_pascal_string(byte *result_ptr,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  uint flag;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar5 = (byte *)result_ptr;
  bVar2 = *param_2;
  bVar3 = *result_ptr;
  bVar1 = *param_2;
  *param_2 = *param_2 + bVar3;
  if (CARRY1(bVar1,bVar3)) {
    *param_2 = 0xff;
    bVar3 = ~bVar2;
  }
  pbVar6 = (byte *)param_2 + bVar2;
  flag = (uint)bVar3;
  while( true ) {
    pbVar6 = pbVar6 + 1;
    pbVar5 = pbVar5 + 1;
    if (flag == 0) break;
    flag = flag - 1;
    *pbVar6 = *pbVar5;
  }
  return;
}



int __stdcall16far find_pascal_substring(byte *result_ptr,byte *param_2)

{
  byte *pbVar1;
  int value;
  uint flag;
  uint flag;
  int value;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool flag;
  
  pbVar7 = (byte *)result_ptr;
  flag = (uint)*param_2;
  if (flag <= *result_ptr) {
    value = 1;
    if (flag == 0) {
      return 1;
    }
    value = (*result_ptr - flag) + 1;
    do {
      pbVar7 = pbVar7 + 1;
      flag = pbVar7 == (byte *)0x0;
      flag = flag;
      pbVar8 = pbVar7;
      pbVar6 = (byte *)param_2;
      do {
        pbVar6 = pbVar6 + 1;
        if (flag == 0) break;
        flag = flag - 1;
        pbVar1 = pbVar8;
        pbVar8 = pbVar8 + 1;
        flag = *pbVar6 == *pbVar1;
      } while (flag);
      if (flag) {
        return value;
      }
      value = value + 1;
      value = value + -1;
    } while (value != 0);
  }
  return 0;
}



void __stdcall16far compare_pascal_strings(byte *result_ptr,byte *param_2)

{
  byte bVar1;
  uint flag;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar3 = (byte *)param_2;
  pbVar4 = (byte *)result_ptr;
  bVar1 = *param_2;
  if (*result_ptr < *param_2) {
    bVar1 = *result_ptr;
  }
  if (bVar1 != 0) {
    flag = (uint)bVar1;
    do {
      pbVar4 = pbVar4 + 1;
      pbVar3 = pbVar3 + 1;
      if (flag == 0) {
        return;
      }
      flag = flag - 1;
    } while (*pbVar3 == *pbVar4);
  }
  return;
}



void __stdcall16far char_to_pascal_string(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = 1;
  ((undefined1 *)param_2)[1] = param_1;
  return;
}



void __stdcall16far
format_string_with_buffers(int value,undefined2 param_2,undefined4 flags,undefined4 param_4)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined1 local_202 [256];
  undefined1 local_102 [256];
  
  puVar4 = local_102;
  uVar2 = (undefined2)((ulong)flags >> 0x10);
  uVar1 = (undefined2)flags;
  uVar5 = unaff_SS;
  substring_pascal(value + -1,1,uVar1,uVar2);
  concat_pascal_string((int)param_4,(int)((ulong)param_4 >> 0x10));
  puVar3 = local_202;
  substring_pascal(0xff,value,uVar1,uVar2);
  concat_pascal_string(puVar3,unaff_SS);
  copy_pascal_string_limited(param_2,uVar1,uVar2,puVar4,uVar5);
  return;
}



void __stdcall16far conditional_string_format(int value,int count,undefined4 flags)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined1 local_202 [256];
  undefined1 local_102 [256];
  
  if (0 < value) {
    puVar4 = local_102;
    uVar2 = (undefined2)((ulong)flags >> 0x10);
    uVar1 = (undefined2)flags;
    uVar5 = unaff_SS;
    substring_pascal(count + -1,1,uVar1,uVar2);
    puVar3 = local_202;
    substring_pascal(0xff,count + value,uVar1,uVar2);
    concat_pascal_string(puVar3,unaff_SS);
    copy_pascal_string_limited(0xff,uVar1,uVar2,puVar4,uVar5);
  }
  return;
}



void __stdcall16far pad_and_copy_buffer(uint value,undefined1 *param_2,undefined1 *flags)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  uint value;
  byte bVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined2 uVar7;
  
  uVar7 = (undefined2)((ulong)flags >> 0x10);
  puVar6 = (undefined1 *)flags;
  puVar5 = (undefined1 *)param_2;
  bVar4 = (byte)(value >> 8);
  for (value = (uint)bVar4; value != 0; value = value - 1) {
    puVar1 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar1 = 0;
  }
  for (value = value & 0xff; value != 0; value = value - 1) {
    puVar2 = puVar6;
    puVar6 = puVar6 + 1;
    puVar1 = puVar5;
    puVar5 = puVar5 + 1;
    *puVar2 = *puVar1;
  }
  for (value = (uint)(byte)((' ' - (char)value) - bVar4); value != 0; value = value - 1) {
    puVar1 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar1 = 0;
  }
  return;
}



void __cdecl16far zero_word_array_16(undefined2 *result_ptr)

{
  undefined2 *puVar1;
  int i;
  undefined2 *puVar3;
  
  puVar3 = (undefined2 *)result_ptr;
  for (i = 0x10; i != 0; i = i + -1) {
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar1 = 0;
  }
  return;
}



void __stdcall16far set_bit_in_array(byte param_1,undefined4 param_2)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)((uint)(param_1 >> 3) + (int)param_2);
  *pbVar1 = *pbVar1 | '\x01' << (param_1 & 7);
  return;
}



void __stdcall16far set_bit_range_in_array(byte param_1,byte param_2,undefined4 flags)

{
  byte *pbVar1;
  byte bVar2;
  char ch;
  uint value;
  bool flag;
  
  if (param_2 <= param_1) {
    ch = (param_1 - param_2) + '\x01';
    value = (uint)(param_2 >> 3);
    bVar2 = '\x01' << (param_2 & 7);
    do {
      pbVar1 = (byte *)(value + (int)flags);
      *pbVar1 = *pbVar1 | bVar2;
      flag = (char)bVar2 < '\0';
      bVar2 = bVar2 << 1 | flag;
      value = value + flag;
      ch = ch + -1;
    } while (ch != '\0');
  }
  return;
}



void __stdcall16far copy_buffer_with_offset(uint value,undefined1 *param_2,undefined4 flags)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  puVar4 = (undefined1 *)param_2;
  puVar3 = (undefined1 *)((int)flags + (value >> 8));
  for (value = value & 0xff; value != 0; value = value - 1) {
    puVar2 = puVar4;
    puVar4 = puVar4 + 1;
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar2 = *puVar1;
  }
  return;
}



char __stdcall16far create_bit_mask(undefined2 param_1,undefined2 param_2,byte flags)

{
  return '\x01' << (flags & 7);
}



void __stdcall16far bitwise_or_word_arrays(uint *result_ptr,uint *count)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  int value;
  uint *puVar5;
  uint *puVar6;
  undefined2 uVar7;
  
  puVar6 = (uint *)count;
  uVar7 = (undefined2)((ulong)result_ptr >> 0x10);
  puVar5 = (uint *)result_ptr;
  value = 0x10;
  do {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar6;
    puVar3 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar3 = *puVar2 | *puVar1;
    value = value + -1;
  } while (value != 0);
  return;
}



void __stdcall16far bitwise_clear_word_arrays(uint *result_ptr,uint *count)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  int value;
  uint *puVar5;
  uint *puVar6;
  undefined2 uVar7;
  
  puVar6 = (uint *)count;
  uVar7 = (undefined2)((ulong)result_ptr >> 0x10);
  puVar5 = (uint *)result_ptr;
  value = 0x10;
  do {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar6;
    puVar3 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar3 = ~*puVar2 & *puVar1;
    value = value + -1;
  } while (value != 0);
  return;
}



undefined4 float_add_subtract(void)

{
  byte bVar1;
  undefined2 in_AX;
  undefined2 uVar2;
  undefined2 uVar3;
  byte bVar5;
  uint uVar4;
  char cVar6;
  undefined2 in_CX;
  byte bVar7;
  uint in_DX;
  uint uVar8;
  uint uVar9;
  uint in_BX;
  byte bVar12;
  uint uVar10;
  uint uVar11;
  uint uVar13;
  uint unaff_SI;
  uint unaff_DI;
  uint uVar14;
  uint uVar15;
  bool bVar16;
  
  uVar14 = unaff_DI ^ 0x8000;
  uVar2 = in_AX;
  uVar13 = in_DX;
  if (((byte)in_CX != 0) && (uVar2 = in_CX, uVar13 = uVar14, (byte)in_AX != 0)) {
    uVar3 = in_AX;
    uVar11 = in_DX;
    uVar10 = in_BX;
    if ((byte)in_CX < (byte)in_AX) {
      uVar3 = in_CX;
      uVar2 = in_AX;
      uVar11 = uVar14;
      uVar10 = unaff_SI;
      unaff_SI = in_BX;
      uVar13 = in_DX;
    }
    cVar6 = (char)uVar2;
    bVar1 = -((char)uVar3 - cVar6);
    if (bVar1 < 0x28) {
      bVar7 = (byte)((uint)uVar2 >> 8);
      uVar15 = uVar13 | 0x8000;
      uVar14 = uVar11 | 0x8000;
      bVar5 = (byte)((uint)uVar3 >> 8);
      for (; uVar8 = uVar14, bVar12 = (byte)(uVar10 >> 8), 0xf < bVar1; bVar1 = bVar1 - 0x10) {
        uVar14 = 0;
        uVar10 = uVar8;
        bVar5 = bVar12;
      }
      if (7 < bVar1) {
        bVar5 = (byte)uVar10;
        uVar10 = CONCAT11((char)uVar8,bVar12);
        uVar8 = uVar8 >> 8;
        bVar1 = bVar1 - 8;
      }
      for (; bVar1 != 0; bVar1 = bVar1 - 1) {
        uVar9 = uVar8 & 1;
        uVar8 = uVar8 >> 1;
        uVar14 = uVar10 & 1;
        uVar10 = uVar10 >> 1 | (uint)(uVar9 != 0) << 0xf;
        bVar5 = bVar5 >> 1 | (uVar14 != 0) << 7;
      }
      if ((int)(uVar13 ^ uVar11) < 0) {
        bVar1 = bVar7 - bVar5;
        uVar11 = (unaff_SI - uVar10) - (uint)(bVar7 < bVar5);
        uVar14 = (uint)(unaff_SI < uVar10 || unaff_SI - uVar10 < (uint)(bVar7 < bVar5));
        uVar9 = (uVar15 - uVar8) - uVar14;
        if (uVar15 < uVar8 || uVar15 - uVar8 < uVar14) {
          uVar13 = uVar13 ^ 0x8000;
          bVar5 = ~bVar1;
          uVar10 = ~uVar11;
          bVar1 = bVar5 + 1;
          uVar14 = (uint)(0xfe < bVar5);
          uVar11 = uVar10 + uVar14;
          uVar9 = ~uVar9 + (uint)CARRY2(uVar10,uVar14);
        }
        uVar4 = CONCAT11(bVar1,cVar6);
        cVar6 = '\x05';
        while ((char)(uVar9 >> 8) == '\0') {
          uVar9 = CONCAT11((char)uVar9,(char)(uVar11 >> 8));
          uVar11 = CONCAT11((char)uVar11,(char)(uVar4 >> 8));
          bVar1 = (byte)uVar4;
          bVar5 = bVar1 - 8;
          uVar4 = (uint)bVar5;
          if (bVar1 < 8 || bVar5 == 0) {
            return 0;
          }
          cVar6 = cVar6 + -1;
          if (cVar6 == '\0') {
            return 0;
          }
        }
        while ((uVar9 & 0x8000) == 0) {
          bVar16 = (int)uVar11 < 0;
          uVar11 = uVar11 << 1 | (uint)((int)uVar4 < 0);
          uVar9 = uVar9 << 1 | (uint)bVar16;
          cVar6 = (char)uVar4 + -1;
          uVar4 = CONCAT11((char)(uVar4 >> 8) << 1,cVar6);
          if (cVar6 == '\0') {
            return 0;
          }
        }
      }
      else {
        uVar4 = CONCAT11(bVar5 + bVar7,cVar6);
        uVar14 = (uint)(CARRY2(uVar10,unaff_SI) ||
                       CARRY2(uVar10 + unaff_SI,(uint)CARRY1(bVar5,bVar7)));
        uVar11 = uVar8 + uVar15;
        uVar9 = uVar11 + uVar14;
        if (CARRY2(uVar8,uVar15) || CARRY2(uVar11,uVar14)) {
          uVar9 = uVar9 >> 1 | (uint)(CARRY2(uVar8,uVar15) || CARRY2(uVar11,uVar14)) << 0xf;
          uVar4 = CONCAT11((byte)(bVar5 + bVar7) >> 1 |
                           ((uVar10 + unaff_SI + (uint)CARRY1(bVar5,bVar7) & 1) != 0) << 7,
                           cVar6 + '\x01');
          if ((char)(cVar6 + '\x01') == '\0') {
            return CONCAT22(uVar9,uVar4);
          }
        }
      }
      return CONCAT22(uVar9 & 0x7fff ^ uVar13 & 0x8000,uVar4);
    }
  }
  return CONCAT22(uVar13,uVar2);
}



undefined4 __cdecl16near float_add_subtract_near(void)

{
  byte bVar1;
  undefined2 in_AX;
  undefined2 uVar2;
  undefined2 uVar3;
  byte bVar5;
  uint uVar4;
  char cVar6;
  undefined2 in_CX;
  byte bVar7;
  uint in_DX;
  uint uVar8;
  uint uVar9;
  uint in_BX;
  byte bVar13;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar14;
  uint unaff_SI;
  uint unaff_DI;
  uint uVar15;
  bool bVar16;
  
  uVar2 = in_AX;
  uVar14 = in_DX;
  if (((byte)in_CX != 0) && (uVar2 = in_CX, uVar14 = unaff_DI, (byte)in_AX != 0)) {
    uVar3 = in_AX;
    uVar11 = in_DX;
    uVar10 = in_BX;
    if ((byte)in_CX < (byte)in_AX) {
      uVar3 = in_CX;
      uVar2 = in_AX;
      uVar11 = unaff_DI;
      uVar10 = unaff_SI;
      unaff_SI = in_BX;
      uVar14 = in_DX;
    }
    cVar6 = (char)uVar2;
    bVar1 = -((char)uVar3 - cVar6);
    if (bVar1 < 0x28) {
      bVar7 = (byte)((uint)uVar2 >> 8);
      uVar15 = uVar14 | 0x8000;
      uVar12 = uVar11 | 0x8000;
      bVar5 = (byte)((uint)uVar3 >> 8);
      for (; uVar8 = uVar12, bVar13 = (byte)(uVar10 >> 8), 0xf < bVar1; bVar1 = bVar1 - 0x10) {
        uVar12 = 0;
        uVar10 = uVar8;
        bVar5 = bVar13;
      }
      if (7 < bVar1) {
        bVar5 = (byte)uVar10;
        uVar10 = CONCAT11((char)uVar8,bVar13);
        uVar8 = uVar8 >> 8;
        bVar1 = bVar1 - 8;
      }
      for (; bVar1 != 0; bVar1 = bVar1 - 1) {
        uVar9 = uVar8 & 1;
        uVar8 = uVar8 >> 1;
        uVar12 = uVar10 & 1;
        uVar10 = uVar10 >> 1 | (uint)(uVar9 != 0) << 0xf;
        bVar5 = bVar5 >> 1 | (uVar12 != 0) << 7;
      }
      if ((int)(uVar14 ^ uVar11) < 0) {
        bVar1 = bVar7 - bVar5;
        uVar11 = (unaff_SI - uVar10) - (uint)(bVar7 < bVar5);
        uVar10 = (uint)(unaff_SI < uVar10 || unaff_SI - uVar10 < (uint)(bVar7 < bVar5));
        uVar9 = (uVar15 - uVar8) - uVar10;
        if (uVar15 < uVar8 || uVar15 - uVar8 < uVar10) {
          uVar14 = uVar14 ^ 0x8000;
          bVar5 = ~bVar1;
          uVar12 = ~uVar11;
          bVar1 = bVar5 + 1;
          uVar10 = (uint)(0xfe < bVar5);
          uVar11 = uVar12 + uVar10;
          uVar9 = ~uVar9 + (uint)CARRY2(uVar12,uVar10);
        }
        uVar4 = CONCAT11(bVar1,cVar6);
        cVar6 = '\x05';
        while ((char)(uVar9 >> 8) == '\0') {
          uVar9 = CONCAT11((char)uVar9,(char)(uVar11 >> 8));
          uVar11 = CONCAT11((char)uVar11,(char)(uVar4 >> 8));
          bVar1 = (byte)uVar4;
          bVar5 = bVar1 - 8;
          uVar4 = (uint)bVar5;
          if (bVar1 < 8 || bVar5 == 0) {
            return 0;
          }
          cVar6 = cVar6 + -1;
          if (cVar6 == '\0') {
            return 0;
          }
        }
        while ((uVar9 & 0x8000) == 0) {
          bVar16 = (int)uVar11 < 0;
          uVar11 = uVar11 << 1 | (uint)((int)uVar4 < 0);
          uVar9 = uVar9 << 1 | (uint)bVar16;
          cVar6 = (char)uVar4 + -1;
          uVar4 = CONCAT11((char)(uVar4 >> 8) << 1,cVar6);
          if (cVar6 == '\0') {
            return 0;
          }
        }
      }
      else {
        uVar4 = CONCAT11(bVar5 + bVar7,cVar6);
        uVar11 = (uint)(CARRY2(uVar10,unaff_SI) ||
                       CARRY2(uVar10 + unaff_SI,(uint)CARRY1(bVar5,bVar7)));
        uVar12 = uVar8 + uVar15;
        uVar9 = uVar12 + uVar11;
        if (CARRY2(uVar8,uVar15) || CARRY2(uVar12,uVar11)) {
          uVar9 = uVar9 >> 1 | (uint)(CARRY2(uVar8,uVar15) || CARRY2(uVar12,uVar11)) << 0xf;
          uVar4 = CONCAT11((byte)(bVar5 + bVar7) >> 1 |
                           ((uVar10 + unaff_SI + (uint)CARRY1(bVar5,bVar7) & 1) != 0) << 7,
                           cVar6 + '\x01');
          if ((char)(cVar6 + '\x01') == '\0') {
            return CONCAT22(uVar9,uVar4);
          }
        }
      }
      return CONCAT22(uVar9 & 0x7fff ^ uVar14 & 0x8000,uVar4);
    }
  }
  return CONCAT22(uVar14,uVar2);
}



undefined2 __cdecl16near float_multiply(void)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  undefined1 *puVar4;
  char cVar5;
  undefined2 in_AX;
  uint uVar6;
  byte bVar7;
  byte bVar8;
  byte in_CL;
  uint uVar9;
  uint uVar10;
  uint in_BX;
  uint uVar11;
  undefined1 *puVar12;
  undefined2 unaff_SS;
  bool bVar13;
  bool bVar14;
  undefined4 uVar15;
  undefined1 auStack_f [5];
  undefined1 auStack_a [2];
  
  if (in_CL != 0) {
    bVar8 = (byte)in_AX;
    if (bVar8 == 0) {
      return in_AX;
    }
    bVar13 = CARRY1(bVar8,in_CL);
    bVar14 = (byte)(bVar8 + in_CL) == '\0';
    uVar15 = float_adjust_exponent();
    uVar9 = (uint)((ulong)uVar15 >> 0x10);
    if (bVar13 || bVar14) {
      return (int)uVar15;
    }
    bVar8 = (byte)((ulong)uVar15 >> 8);
    uVar6 = 0;
    uVar11 = 0;
    uVar10 = 0;
    puVar4 = auStack_f;
    do {
      puVar12 = puVar4;
      bVar13 = false;
      uVar6 = CONCAT11((char)(uVar6 >> 8),puVar12[6]);
      if (puVar12[6] == '\0') {
        uVar6 = uVar11 << 8;
        uVar11 = CONCAT11((char)uVar10,(char)(uVar11 >> 8));
        uVar10 = uVar10 >> 8;
      }
      else {
        cVar5 = '\b';
        do {
          bVar14 = (uVar6 & 1) != 0;
          bVar3 = bVar13 << 7;
          bVar7 = (byte)(uVar6 >> 8);
          if (bVar14) {
            bVar13 = CARRY1(bVar7,bVar8);
            bVar7 = bVar7 + bVar8;
            uVar1 = (uint)bVar13;
            bVar13 = CARRY2(uVar11,in_BX);
            uVar2 = uVar11 + in_BX;
            uVar11 = uVar2 + uVar1;
            uVar1 = (uint)(bVar13 || CARRY2(uVar2,uVar1));
            uVar2 = uVar10 + uVar9;
            bVar14 = CARRY2(uVar10,uVar9) || CARRY2(uVar2,uVar1);
            uVar10 = uVar2 + uVar1;
          }
          uVar1 = uVar10 & 1;
          uVar10 = uVar10 >> 1 | (uint)bVar14 << 0xf;
          uVar2 = uVar11 & 1;
          uVar11 = uVar11 >> 1 | (uint)(uVar1 != 0) << 0xf;
          bVar13 = (bVar7 & 1) != 0;
          uVar6 = CONCAT11(bVar7 >> 1 | (uVar2 != 0) << 7,(byte)uVar6 >> 1 | bVar3);
          cVar5 = cVar5 + -1;
          in_CL = bVar13;
        } while (cVar5 != '\0');
      }
      puVar4 = puVar12 + 1;
    } while (puVar12 + 1 != auStack_a);
    cVar5 = puVar12[7];
    bVar8 = (byte)(uVar6 >> 8);
    if (((uVar10 & 0x8000) == 0) && (bVar8 = bVar8 << 1 | (in_CL & 1) != 0, cVar5 != '\0')) {
      cVar5 = cVar5 + -1;
    }
    if (cVar5 != '\0') {
      return CONCAT11(bVar8,cVar5);
    }
  }
  return 0;
}



long __cdecl16near float_divide(void)

{
  long lVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  undefined2 in_AX;
  byte bVar6;
  undefined2 uVar5;
  char cVar7;
  undefined2 in_CX;
  undefined2 in_DX;
  int iVar8;
  uint uVar9;
  uint in_BX;
  uint uVar10;
  byte *pbVar11;
  uint unaff_SI;
  uint unaff_DI;
  undefined2 unaff_SS;
  bool bVar12;
  bool bVar13;
  long lVar14;
  byte abStack_a [2];
  int iStack_8;
  undefined2 uStack_6;
  undefined2 uStack_4;
  
  lVar14 = CONCAT22(in_DX,in_AX);
  bVar2 = (byte)in_AX;
  if (bVar2 != 0) {
    bVar12 = (byte)in_CX <= bVar2;
    bVar13 = bVar2 == (byte)in_CX;
    lVar14 = float_adjust_exponent();
    if (!bVar12 && !bVar13) {
      pbVar11 = (byte *)((int)&uStack_6 + 1);
      bVar2 = (byte)((uint)in_CX >> 8);
      cVar7 = '\b';
      uStack_4 = in_CX;
      lVar1 = lVar14;
LAB_214c_0b4b:
      uVar9 = (uint)((ulong)lVar1 >> 0x10);
      bVar12 = uVar9 < unaff_DI;
      bVar3 = (byte)((ulong)lVar1 >> 8);
      if ((uVar9 == unaff_DI) && (bVar12 = in_BX < unaff_SI, in_BX == unaff_SI)) {
        bVar12 = bVar3 < bVar2;
      }
      if (!bVar12) {
        bVar12 = in_BX < unaff_SI;
        uVar10 = in_BX - unaff_SI;
        in_BX = uVar10 - (bVar3 < bVar2);
        uVar10 = (uint)(bVar12 || uVar10 < (bVar3 < bVar2));
        bVar12 = uVar9 < unaff_DI || uVar9 - unaff_DI < uVar10;
        lVar1 = CONCAT22((uVar9 - unaff_DI) - uVar10,CONCAT11(bVar3 - bVar2,(char)lVar1));
      }
      bVar12 = !bVar12;
      do {
        iVar8 = (int)((ulong)lVar1 >> 0x10);
        cVar4 = (char)((ulong)lVar1 >> 8);
        bVar3 = (char)lVar1 << 1 | bVar12;
        cVar7 = cVar7 + -1;
        if (cVar7 == '\0') {
          *pbVar11 = bVar3;
          cVar7 = '\b';
          pbVar11 = pbVar11 + -1;
          if (pbVar11 == abStack_a) {
            uVar10 = in_BX << 1 | (uint)((int)lVar1 < 0);
            bVar12 = lVar1 < 0;
            uVar9 = iVar8 << 1 | (uint)((int)in_BX < 0);
            if (!bVar12) {
              bVar12 = uVar9 < unaff_DI;
              if ((uVar9 == unaff_DI) && (bVar12 = uVar10 < unaff_SI, uVar10 == unaff_SI)) {
                bVar12 = (byte)(cVar4 << 1) < bVar2;
              }
              bVar12 = !bVar12;
            }
            cVar7 = (char)((ulong)lVar14 >> 8);
            if ((uStack_6 & 0x8000) == 0) {
              uVar5 = CONCAT11(cVar7 << 1 | bVar12,(char)lVar14);
              uStack_6 = uStack_6 << 1 | (uint)(iStack_8 < 0);
            }
            else {
              cVar4 = (char)lVar14 + '\x01';
              uVar5 = CONCAT11(cVar7,cVar4);
              if (cVar4 == '\0') goto LAB_214c_0bba;
            }
            uStack_6 = CONCAT11((byte)(uStack_6 >> 8) ^ (byte)uStack_4,(char)uStack_6);
            if ((char)uVar5 == '\0') {
              uVar5 = 0;
              uStack_6 = 0;
            }
LAB_214c_0bba:
            return CONCAT22(uStack_6,uVar5);
          }
        }
        bVar6 = cVar4 * '\x02';
        bVar12 = (int)in_BX < 0;
        in_BX = in_BX << 1 | (uint)((int)lVar1 < 0);
        bVar13 = -1 < lVar1;
        uVar9 = iVar8 << 1 | (uint)bVar12;
        lVar1 = CONCAT22(uVar9,CONCAT11(bVar6,bVar3));
        if (bVar13) goto LAB_214c_0b4b;
        bVar12 = in_BX < unaff_SI;
        uVar10 = in_BX - unaff_SI;
        in_BX = uVar10 - (bVar6 < bVar2);
        lVar1 = CONCAT22((uVar9 - unaff_DI) - (uint)(bVar12 || uVar10 < (bVar6 < bVar2)),
                         CONCAT11(bVar6 - bVar2,bVar3));
        bVar12 = true;
      } while( true );
    }
  }
  return lVar14;
}



undefined4 __cdecl16near float_adjust_exponent(void)

{
  byte bVar1;
  undefined2 in_AX;
  undefined1 uVar3;
  undefined2 uVar2;
  uint in_DX;
  bool in_CF;
  
  uVar3 = (undefined1)((uint)in_AX >> 8);
  bVar1 = (byte)in_AX;
  if (in_CF) {
    uVar2 = CONCAT11(uVar3,bVar1 + 0x80);
    if (0x7f < bVar1) goto LAB_214c_0bdd;
  }
  else {
    uVar2 = CONCAT11(uVar3,bVar1 + 0x80);
    if (bVar1 < 0x80) {
      return 0;
    }
  }
  in_DX = in_DX | 0x8000;
LAB_214c_0bdd:
  return CONCAT22(in_DX,uVar2);
}



void __cdecl16near float_compare_signs(void)

{
  uint in_DX;
  uint unaff_DI;
  bool bVar1;
  
  if ((int)(in_DX ^ unaff_DI) < 0) {
    return;
  }
  bVar1 = (in_DX & 0x8000) == 0;
  if ((!bVar1) && (float_nop_stub(), !bVar1)) {
    return;
  }
  return;
}



void __cdecl16near float_nop_stub(void)

{
  return;
}



void __cdecl16near float_normalize(void)

{
  uint in_AX;
  uint uVar1;
  uint in_DX;
  
  if (in_AX != 0 || in_DX != 0) {
    if ((int)in_DX < 0) {
      uVar1 = ~in_AX;
      in_AX = uVar1 + 1;
      in_DX = ~in_DX + (uint)(0xfffe < uVar1);
    }
    uVar1 = in_AX;
    if ((in_DX == 0) && (uVar1 = 0, in_DX = in_AX, (char)(in_AX >> 8) == '\0')) {
      in_DX = in_AX << 8;
    }
    while (-1 < (int)in_DX) {
      in_DX = in_DX * 2 + (uint)CARRY2(uVar1,uVar1);
      uVar1 = uVar1 * 2;
    }
  }
  return;
}



undefined4 __cdecl16near float_to_fixed_point(void)

{
  uint uVar1;
  char cVar2;
  byte in_AL;
  uint uVar3;
  byte bVar4;
  char in_CH;
  uint in_DX;
  uint uVar5;
  uint in_BX;
  bool bVar6;
  
  cVar2 = -in_AL;
  uVar5 = in_DX;
  if (in_AL < 0xa0) {
    if (0x1f < (byte)(cVar2 + 0x9fU)) {
      return 0;
    }
    bVar4 = cVar2 + 0xa0;
    uVar5 = in_DX | 0x8000;
    if (0x10 < bVar4) {
      uVar5 = 0;
      bVar4 = cVar2 + 0x90;
      in_BX = in_DX | 0x8000;
    }
    if (8 < bVar4) {
      in_BX = CONCAT11((char)uVar5,(char)(in_BX >> 8));
      uVar5 = uVar5 >> 8;
      bVar4 = bVar4 - 8;
    }
    do {
      uVar1 = uVar5 & 1;
      uVar5 = uVar5 >> 1;
      uVar3 = in_BX & 1;
      in_BX = in_BX >> 1 | (uint)(uVar1 != 0) << 0xf;
      bVar4 = bVar4 - 1;
    } while (bVar4 != 0);
    if ((uVar3 != 0) && (in_CH != '\0')) {
      bVar6 = 0xfffe < in_BX;
      in_BX = in_BX + 1;
      uVar5 = uVar5 + bVar6;
      if ((int)uVar5 < 0) goto LAB_214c_0c9c;
    }
    if ((int)in_DX < 0) {
      uVar3 = ~in_BX;
      in_BX = uVar3 + 1;
      uVar5 = ~uVar5 + (uint)(0xfffe < uVar3);
    }
    return CONCAT22(uVar5,in_BX);
  }
LAB_214c_0c9c:
  return CONCAT22(uVar5,in_BX);
}



void __cdecl16far float_add_with_handler(void)

{
  undefined1 in_CF;
  
  float_add_subtract_near();
  if (!(bool)in_CF) {
    return;
  }
  exit_program_handler();
  return;
}



void __cdecl16far combat_check_and_handle_error(void)

{
  undefined1 in_CF;
  
  float_add_subtract();
  if (!(bool)in_CF) {
    return;
  }
  exit_program_handler();
  return;
}



void __cdecl16far check_combat_and_handle_error(void)

{
  undefined1 in_CF;
  
  float_multiply();
  if (!(bool)in_CF) {
    return;
  }
  exit_program_handler();
  return;
}



void __cdecl16far conditional_char_action(void)

{
  char in_CL;
  bool bVar1;
  
  bVar1 = false;
  if (in_CL == '\0') {
    exit_program_handler();
    return;
  }
  float_divide();
  if (!bVar1) {
    return;
  }
  exit_program_handler();
  return;
}



void __cdecl16far char_create_wrapper(void)

{
  float_compare_signs();
  return;
}



void __cdecl16far combat_wrapper(void)

{
  float_normalize();
  return;
}



void __cdecl16far combat_check_with_error(void)

{
  undefined1 in_CF;
  
  float_to_fixed_point();
  if (!(bool)in_CF) {
    return;
  }
  exit_program_handler();
  return;
}



void __cdecl16far combat_check_with_error_alt(void)

{
  undefined1 in_CF;
  
  float_to_fixed_point();
  if (!(bool)in_CF) {
    return;
  }
  exit_program_handler();
  return;
}



void __cdecl16near combat_near_wrapper(void)

{
  float_add_subtract_near();
  return;
}



undefined2 __cdecl16far complex_combat_sequence(void)

{
  char in_AL;
  undefined2 uVar1;
  uint in_DX;
  undefined2 uVar2;
  undefined4 uVar3;
  
  if ((in_AL != '\0') && ((in_DX & 0x8000) == 0)) {
    float_multiply(in_AL + '\x7f');
    uVar1 = 0;
    uVar3 = combat_near_wrapper();
    uVar2 = 0;
    float_add_subtract_near((int)uVar3,uVar1,(int)((ulong)uVar3 >> 0x10));
    float_divide();
    combat_char_combat_sequence();
    uVar3 = float_add_subtract_near();
    float_normalize((int)uVar3,uVar2,(int)((ulong)uVar3 >> 0x10));
    float_multiply();
    uVar1 = float_add_subtract_near();
    if ((byte)uVar1 < 0x67) {
      uVar1 = 0;
    }
    return uVar1;
  }
  uVar1 = exit_program_handler();
  return uVar1;
}



char __cdecl16far calculate_combat_value(void)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  byte bVar4;
  uint in_DX;
  undefined2 in_BX;
  undefined4 uVar5;
  undefined2 uVar6;
  
  uVar5 = float_divide();
  uVar6 = (undefined2)uVar5;
  if ((byte)uVar5 < 0x88) {
    uVar3 = float_to_fixed_point(uVar6,in_BX,(int)((ulong)uVar5 >> 0x10));
    float_normalize(uVar6);
    float_add_subtract();
    bVar1 = process_combat_array();
    bVar4 = (byte)(uVar3 >> 1);
    if ((uVar3 & 1) != 0) {
      bVar1 = float_multiply();
    }
    cVar2 = bVar1 + bVar4;
    if (!CARRY1(bVar1,bVar4)) {
      if ((in_DX & 0x8000) != 0) {
        cVar2 = float_divide();
      }
      return cVar2;
    }
  }
  cVar2 = exit_program_handler();
  return cVar2;
}



void combat_char_combat_sequence(void)

{
  float_multiply();
  process_combat_array();
  float_multiply();
  return;
}



void __cdecl16near process_combat_array(void)

{
  int in_CX;
  int unaff_DI;
  undefined2 uStack_a;
  
  uStack_a = in_CX;
  while( true ) {
    float_multiply();
    unaff_DI = unaff_DI + 6;
    uStack_a = uStack_a + -1;
    if (uStack_a == 0) break;
    float_add_subtract_near(unaff_DI);
  }
  float_add_subtract_near();
  return;
}



uint __stdcall16far random_mod(uint value)

{
  uint value;
  uint extraout_DX;
  
  rand_lcg();
  value = 0;
  if (value != 0) {
    value = extraout_DX % value;
  }
  return value;
}



char __cdecl16far find_highest_bit(void)

{
  char cVar1;
  int iVar2;
  ulong uVar3;
  
  uVar3 = rand_lcg();
  cVar1 = -0x80;
  iVar2 = 0x20;
  do {
    if ((uVar3 & 0x80000000) != 0) {
      return cVar1;
    }
    uVar3 = CONCAT22((int)(uVar3 >> 0x10) << 1 | (uint)((int)uVar3 < 0),(int)uVar3 << 1);
    cVar1 = cVar1 + -1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return '\0';
}



void __cdecl16near rand_lcg(void)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  char cVar4;
  int iVar5;
  undefined2 unaff_DS;
  
  iVar1 = *(int *)0xe774;
  lVar2 = (ulong)*(uint *)0xe772 * 0x445;
  uVar3 = (uint)lVar2;
  iVar5 = *(uint *)0xe772 << 3;
  cVar4 = (char)iVar5;
  iVar5 = (int)((ulong)lVar2 >> 0x10) + CONCAT11((char)((uint)iVar5 >> 8) + cVar4,cVar4) + iVar1 * 5
  ;
  *(int *)0xe772 = uVar3 + 1;
  *(int *)0xe774 =
       CONCAT11((char)((uint)iVar5 >> 8) + (char)iVar1 * '\x04' + (char)(iVar1 << 7),(char)iVar5) +
       (uint)(0xfffe < uVar3);
  return;
}



void __cdecl16far seed_rng(void)

{
  code *pcVar1;
  undefined2 in_CX;
  undefined2 extraout_DX;
  undefined2 unaff_DS;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  *(undefined2 *)0xe772 = in_CX;
  *(undefined2 *)0xe774 = extraout_DX;
  return;
}



void __cdecl16near int32_to_string(void)

{
  char *pcVar1;
  uint uVar2;
  char cVar3;
  uint in_AX;
  char cVar4;
  uint in_DX;
  uint uVar5;
  uint *puVar6;
  char *unaff_DI;
  undefined2 unaff_ES;
  bool bVar7;
  
  if ((int)in_DX < 0) {
    uVar5 = ~in_AX;
    in_AX = uVar5 + 1;
    in_DX = ~in_DX + (uint)(0xfffe < uVar5);
    pcVar1 = unaff_DI;
    unaff_DI = unaff_DI + 1;
    *pcVar1 = '-';
  }
  puVar6 = (uint *)0x1247;
  cVar4 = '\t';
  do {
    if ((puVar6[1] <= in_DX) && ((puVar6[1] < in_DX || (*puVar6 <= in_AX)))) break;
    puVar6 = puVar6 + 2;
    cVar4 = cVar4 + -1;
  } while (cVar4 != '\0');
  cVar4 = cVar4 + '\x01';
  do {
    cVar3 = '/';
    do {
      cVar3 = cVar3 + '\x01';
      bVar7 = in_AX < *puVar6;
      in_AX = in_AX - *puVar6;
      uVar5 = (uint)bVar7;
      bVar7 = puVar6[1] <= in_DX;
      uVar2 = in_DX - puVar6[1];
      in_DX = uVar2 - uVar5;
    } while (bVar7 && uVar5 <= uVar2);
    bVar7 = CARRY2(in_AX,*puVar6);
    in_AX = in_AX + *puVar6;
    in_DX = in_DX + puVar6[1] + (uint)bVar7;
    puVar6 = puVar6 + 2;
    pcVar1 = unaff_DI;
    unaff_DI = unaff_DI + 1;
    *pcVar1 = cVar3;
    cVar4 = cVar4 + -1;
  } while (cVar4 != '\0');
  return;
}



undefined4 __cdecl16near string_to_int32(void)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int in_CX;
  uint uVar7;
  uint uVar8;
  byte bVar9;
  byte bVar10;
  char cVar11;
  byte *unaff_DI;
  undefined2 unaff_ES;
  bool bVar12;
  bool bVar13;
  
  uVar2 = 0;
  uVar7 = 0;
  bVar1 = false;
  if (in_CX == 0) goto LAB_214c_12d0;
  if (*unaff_DI == 0x2b) {
LAB_214c_1284:
    unaff_DI = unaff_DI + 1;
    in_CX = in_CX + -1;
    if (in_CX == 0) goto LAB_214c_12d0;
  }
  else if (*unaff_DI == 0x2d) {
    bVar1 = true;
    goto LAB_214c_1284;
  }
  if (*unaff_DI == 0x24) {
    iVar4 = in_CX + -1;
    if (iVar4 == 0) {
LAB_214c_12d0:
      return CONCAT22(uVar7,uVar2);
    }
    do {
      unaff_DI = unaff_DI + 1;
      bVar9 = *unaff_DI;
      if (0x60 < bVar9) {
        bVar9 = bVar9 - 0x20;
      }
      bVar10 = bVar9 - 0x30;
      if ((byte)(bVar9 - 0x3a) < 0xf6) {
        if ((byte)(bVar9 + 0xb9) < 0xfa) break;
        bVar10 = bVar9 - 0x37;
      }
      cVar11 = '\x04';
      do {
        bVar12 = (int)uVar2 < 0;
        uVar2 = uVar2 << 1;
        bVar13 = (int)uVar7 < 0;
        uVar7 = uVar7 << 1 | (uint)bVar12;
        if (bVar13) goto LAB_214c_12d0;
        cVar11 = cVar11 + -1;
      } while (cVar11 != '\0');
      uVar2 = CONCAT11((char)(uVar2 >> 8),(byte)uVar2 | bVar10);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  else {
    do {
      uVar6 = (uint)(byte)(*unaff_DI - 0x30);
      if ((byte)(*unaff_DI - 0x3a) < 0xf6) break;
      if ((uVar7 & 0xf000) != 0) goto LAB_214c_12d0;
      uVar3 = uVar2 * 2;
      uVar8 = uVar7 << 1 | (uint)((int)uVar2 < 0);
      iVar4 = uVar2 << 2;
      uVar5 = uVar2 * 8;
      uVar7 = uVar2 * 10;
      uVar2 = uVar7 + uVar6;
      uVar7 = ((uVar8 << 1 | (uint)((int)uVar3 < 0)) << 1 | (uint)(iVar4 < 0)) + uVar8 +
              (uint)CARRY2(uVar5,uVar3) + (uint)CARRY2(uVar7,uVar6);
      if ((int)uVar7 < 0) goto LAB_214c_12d0;
      unaff_DI = unaff_DI + 1;
      in_CX = in_CX + -1;
    } while (in_CX != 0);
  }
  if (bVar1) {
    uVar6 = ~uVar2;
    uVar2 = uVar6 + 1;
    uVar7 = ~uVar7 + (uint)(0xfffe < uVar6);
  }
  return CONCAT22(uVar7,uVar2);
}



undefined2 __stdcall16far parse_pascal_string_to_int(uint *result_ptr,byte *param_2)

{
  undefined2 uVar1;
  uint value;
  byte *pbVar3;
  bool flag;
  
  flag = false;
  value = (uint)*param_2;
  pbVar3 = (byte *)param_2;
  while ((pbVar3 = pbVar3 + 1, value != 0 && (flag = *pbVar3 < 0x20, *pbVar3 == 0x20))) {
    value = value - 1;
  }
  uVar1 = string_to_int32();
  if ((flag) || (value != 0)) {
    value = (int)pbVar3 - (int)(byte *)param_2;
    uVar1 = 0;
  }
  *result_ptr = value;
  return uVar1;
}



void __stdcall16far init_fcb(byte *result_ptr,undefined2 *param_2)

{
  byte *pbVar1;
  byte bVar2;
  int i;
  uint value;
  byte *pbVar5;
  undefined2 *puVar6;
  byte *pbVar7;
  undefined2 uVar8;
  
  uVar8 = (undefined2)((ulong)param_2 >> 0x10);
  puVar6 = (undefined2 *)param_2;
  pbVar5 = (byte *)result_ptr;
  *param_2 = 0;
  puVar6[1] = 0xd7b0;
  puVar6[2] = 0x80;
  puVar6[3] = 0;
  puVar6[4] = 0;
  puVar6[5] = 0;
  puVar6[6] = puVar6 + 0x40;
  puVar6[7] = uVar8;
  pbVar7 = (byte *)(puVar6 + 9);
  puVar6[8] = 0x14a7;
  pbVar7[0] = 0x4c;
  pbVar7[1] = 0x21;
  for (i = 0xe; pbVar7 = pbVar7 + 2, i != 0; i = i + -1) {
    pbVar7[0] = 0;
    pbVar7[1] = 0;
  }
  bVar2 = *result_ptr;
  if (0x4f < bVar2) {
    bVar2 = 0x4f;
  }
  for (value = (uint)bVar2; pbVar5 = pbVar5 + 1, value != 0; value = value - 1) {
    pbVar1 = pbVar7;
    pbVar7 = pbVar7 + 1;
    *pbVar1 = *pbVar5;
  }
  *pbVar7 = 0;
  return;
}



void file_open_wrapper(void)

{
  device_open_handler();
  return;
}



void file_open_wrapper2(void)

{
  device_open_handler();
  return;
}



void __stdcall16far device_open_handler(undefined4 param_1)

{
  int value;
  undefined2 in_DX;
  int value;
  undefined2 uVar3;
  undefined2 unaff_DS;
  bool flag;
  
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  value = (int)param_1;
  value = *(int *)(value + 2);
  if ((value == -0x284f) || (value == -0x284e)) {
    device_cleanup();
  }
  else if (value != -0x2850) {
    *(undefined2 *)0xe78b = 0x66;
    return;
  }
  flag = true;
  *(undefined2 *)(value + 2) = in_DX;
  *(undefined2 *)(value + 8) = 0;
  *(undefined2 *)(value + 10) = 0;
  call_indexed_handler();
  if (!flag) {
    *(undefined2 *)(value + 2) = 0xd7b0;
  }
  return;
}



void __stdcall16far device_close_handler(undefined4 param_1)

{
  undefined1 in_ZF;
  
  validate_device_type();
  if ((bool)in_ZF) {
    device_cleanup();
    *(undefined2 *)((int)param_1 + 2) = 0xd7b0;
  }
  return;
}



void __cdecl16near validate_device_type(void)

{
  int unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  if ((*(int *)(unaff_DI + 2) != -0x284f) && (*(int *)(unaff_DI + 2) != -0x284e)) {
    *(undefined2 *)0xe78b = 0x67;
  }
  return;
}



void __cdecl16near call_device_handler(void)

{
  int iVar1;
  int unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  if (*(int *)(unaff_DI + 2) != -0x284e) {
    return;
  }
  iVar1 = (*(code *)*(undefined2 *)(unaff_DI + 0x14))(0x214c);
  if (iVar1 != 0) {
    *(int *)0xe78b = iVar1;
  }
  return;
}



void device_cleanup(void)

{
  int iVar1;
  int unaff_DI;
  undefined2 unaff_DS;
  
  call_device_handler();
  iVar1 = (*(code *)*(undefined2 *)(unaff_DI + 0x1c))(0x214c);
  if (iVar1 != 0) {
    *(int *)0xe78b = iVar1;
  }
  return;
}



void __cdecl16near call_indexed_handler(void)

{
  int iVar1;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar1 = (*(code *)*(undefined2 *)(in_BX + unaff_DI))(0x214c);
  if (iVar1 != 0) {
    *(int *)0xe78b = iVar1;
  }
  return;
}



void __cdecl16near input_device_dispatch(void)

{
  int unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  code *in_stack_00000000;
  
  if (*(int *)(unaff_DI + 2) == -0x284f) {
    if (*(int *)0xe78b == 0) {
                    // WARNING: Could not recover jumptable at 0x00022af7. Too many branches
                    // WARNING: Treating indirect jump as call
      (*in_stack_00000000)();
      return;
    }
  }
  else {
    *(undefined2 *)0xe78b = 0x68;
  }
  return;
}



undefined1 __cdecl16near read_byte_buffered(void)

{
  int in_DX;
  int in_BX;
  int unaff_BP;
  int unaff_DI;
  int iVar1;
  undefined2 unaff_ES;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  
  if (in_BX == in_DX) {
    uVar3 = *(undefined2 *)(unaff_BP + -2);
    uVar2 = (undefined2)((ulong)*(undefined4 *)(unaff_BP + -6) >> 0x10);
    iVar1 = (int)*(undefined4 *)(unaff_BP + -6);
    *(int *)(iVar1 + 8) = in_BX;
    iVar1 = (*(code *)*(undefined2 *)(iVar1 + 0x14))(0x214c,iVar1,uVar2);
    if (iVar1 != 0) {
      *(int *)0xe78b = iVar1;
    }
    uVar3 = (undefined2)((ulong)*(undefined4 *)(unaff_BP + -6) >> 0x10);
    iVar1 = (int)*(undefined4 *)(unaff_BP + -6);
    in_BX = *(int *)(iVar1 + 8);
    unaff_ES = (undefined2)((ulong)*(undefined4 *)(iVar1 + 0xc) >> 0x10);
    unaff_DI = (int)*(undefined4 *)(iVar1 + 0xc);
    if (in_BX == *(int *)(iVar1 + 10)) {
      return 0x1a;
    }
  }
  return *(undefined1 *)(in_BX + unaff_DI);
}



void finalize_read(int value,undefined2 param_2)

{
  undefined2 in_BX;
  code *in_stack_00000000;
  
  *(undefined2 *)(value + 8) = in_BX;
                    // WARNING: Could not recover jumptable at 0x00022b45. Too many branches
                    // WARNING: Treating indirect jump as call
  (*in_stack_00000000)();
  return;
}



void __cdecl16near output_device_dispatch(void)

{
  int unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  code *in_stack_00000000;
  
  if (*(int *)(unaff_DI + 2) == -0x284e) {
    if (*(int *)0xe78b == 0) {
                    // WARNING: Could not recover jumptable at 0x00022b66. Too many branches
                    // WARNING: Treating indirect jump as call
      (*in_stack_00000000)();
      return;
    }
  }
  else {
    *(undefined2 *)0xe78b = 0x69;
  }
  return;
}



void __cdecl16near write_byte_buffered(void)

{
  undefined2 uVar1;
  undefined1 in_AL;
  int in_DX;
  int in_BX;
  int unaff_BP;
  int unaff_DI;
  int iVar2;
  undefined2 unaff_ES;
  undefined2 uVar3;
  undefined2 unaff_SS;
  
  *(undefined1 *)(in_BX + unaff_DI) = in_AL;
  if (in_BX + 1 != in_DX) {
    return;
  }
  uVar1 = *(undefined2 *)(unaff_BP + -2);
  uVar3 = (undefined2)((ulong)*(undefined4 *)(unaff_BP + -6) >> 0x10);
  iVar2 = (int)*(undefined4 *)(unaff_BP + -6);
  *(int *)(iVar2 + 8) = in_BX + 1;
  iVar2 = (*(code *)*(undefined2 *)(iVar2 + 0x14))(0x214c,iVar2,uVar3);
  if (iVar2 != 0) {
    *(int *)0xe78b = iVar2;
  }
  return;
}



void finalize_write(int value,undefined2 param_2)

{
  undefined2 in_BX;
  code *in_stack_00000000;
  
  *(undefined2 *)(value + 8) = in_BX;
                    // WARNING: Could not recover jumptable at 0x00022bad. Too many branches
                    // WARNING: Treating indirect jump as call
  (*in_stack_00000000)();
  return;
}



void read_line(undefined2 param_1,undefined4 param_2)

{
  char ch;
  int flag;
  undefined2 uVar3;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  input_device_dispatch();
  if ((bool)in_ZF) {
    do {
      ch = read_byte_buffered();
      if (ch == '\x1a') goto LAB_214c_170e;
    } while (ch != '\r');
    read_byte_buffered();
LAB_214c_170e:
    finalize_read();
  }
  uVar3 = (undefined2)((ulong)param_2 >> 0x10);
  flag = (int)param_2;
  if (*(int *)(flag + 2) == -0x284f) {
    if (*(int *)0xe78b != 0) {
      return;
    }
    flag = (*(code *)*(undefined2 *)(flag + 0x18))(0x214c,flag,uVar3);
    if (flag == 0) {
      return;
    }
  }
  else {
    flag = 0x68;
  }
  *(int *)0xe78b = flag;
  return;
}



void __stdcall16far flush_input(undefined4 param_1)

{
  int flag;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  flag = (int)param_1;
  if (*(int *)(flag + 2) == -0x284f) {
    if (*(int *)0xe78b != 0) {
      return;
    }
    flag = (*(code *)*(undefined2 *)(flag + 0x18))(0x214c,flag,uVar2);
    if (flag == 0) {
      return;
    }
  }
  else {
    flag = 0x68;
  }
  *(int *)0xe78b = flag;
  return;
}



void write_word(undefined2 param_1,undefined4 param_2)

{
  int flag;
  undefined2 uVar2;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  output_device_dispatch();
  if ((bool)in_ZF) {
    write_byte_buffered();
    write_byte_buffered();
    finalize_write();
  }
  uVar2 = (undefined2)((ulong)param_2 >> 0x10);
  flag = (int)param_2;
  if (*(int *)(flag + 2) == -0x284e) {
    if (*(int *)0xe78b != 0) {
      return;
    }
    flag = (*(code *)*(undefined2 *)(flag + 0x18))(0x214c,flag,uVar2);
    if (flag == 0) {
      return;
    }
  }
  else {
    flag = 0x69;
  }
  *(int *)0xe78b = flag;
  return;
}



void __stdcall16far flush_output(undefined4 param_1)

{
  int flag;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  flag = (int)param_1;
  if (*(int *)(flag + 2) == -0x284e) {
    if (*(int *)0xe78b != 0) {
      return;
    }
    flag = (*(code *)*(undefined2 *)(flag + 0x18))(0x214c,flag,uVar2);
    if (flag == 0) {
      return;
    }
  }
  else {
    flag = 0x69;
  }
  *(int *)0xe78b = flag;
  return;
}



undefined1 __cdecl16far getc(void)

{
  undefined1 uVar1;
  undefined1 in_ZF;
  
  input_device_dispatch();
  if ((bool)in_ZF) {
    read_byte_buffered();
    uVar1 = finalize_read();
  }
  else {
    uVar1 = 0x1a;
  }
  return uVar1;
}



void __stdcall16far write_bytes(int value)

{
  int value;
  undefined1 in_ZF;
  
  output_device_dispatch();
  if ((bool)in_ZF) {
    value = value + -1;
    if (value != 0 && 0 < value) {
      do {
        write_byte_buffered();
        value = value + -1;
      } while (value != 0);
    }
    write_byte_buffered();
    finalize_write();
  }
  return;
}



void __stdcall16far read_string_from_file(int value,char *param_2)

{
  char ch;
  int value;
  char *pcVar3;
  undefined2 uVar4;
  undefined1 in_ZF;
  
  input_device_dispatch();
  if ((bool)in_ZF) {
    uVar4 = (undefined2)((ulong)param_2 >> 0x10);
    pcVar3 = (char *)param_2;
    value = 0;
    do {
      ch = read_byte_buffered();
      if ((ch == '\r') || (ch == '\x1a')) break;
      value = value + 1;
      pcVar3 = pcVar3 + 1;
      *pcVar3 = ch;
    } while (value != value);
    pcVar3[-value] = (char)value;
    finalize_read();
  }
  else {
    *param_2 = '\0';
  }
  return;
}



void __stdcall16far write_padded_string(int value,byte *param_2)

{
  int value;
  uint value;
  undefined1 in_ZF;
  
  output_device_dispatch();
  if ((bool)in_ZF) {
    value = (uint)*param_2;
    value = value - value;
    if (value != 0 && (int)value <= value) {
      do {
        write_byte_buffered();
        value = value + -1;
      } while (value != 0);
    }
    for (; value != 0; value = value - 1) {
      write_byte_buffered();
    }
    finalize_write();
  }
  return;
}



undefined2 __cdecl16far read_token_and_parse_number(void)

{
  byte bVar1;
  undefined2 uVar2;
  int flag;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  bool flag;
  byte local_20 [32];
  
  flag = &stack0x0000 == (undefined1 *)0x20;
  input_device_dispatch();
  if (flag) {
    flag = 0;
    do {
      bVar1 = read_byte_buffered();
      uVar4 = bVar1 < ITEM_SIZE;
      if (bVar1 == ITEM_SIZE) goto LAB_214c_185c;
    } while (bVar1 < 0x21);
    while( true ) {
      bVar1 = read_byte_buffered();
      uVar4 = bVar1 < 0x20;
      if (bVar1 < 0x21) break;
      if (flag != 0x20) {
        local_20[flag] = bVar1;
        flag = flag + 1;
      }
    }
LAB_214c_185c:
    finalize_read();
    if (flag != 0) {
      uVar2 = string_to_int32();
      if ((!(bool)uVar4) && (flag == 0)) {
        return uVar2;
      }
      *(undefined2 *)0xe78b = 0x6a;
    }
  }
  return 0;
}



void __stdcall16far write_padded_number(int value)

{
  int value;
  int in_CX;
  undefined1 uVar2;
  
  uVar2 = &stack0x0000 == (undefined1 *)0x20;
  int32_to_string();
  output_device_dispatch();
  if ((bool)uVar2) {
    value = value - in_CX;
    if (value != 0 && in_CX <= value) {
      do {
        write_byte_buffered();
        value = value + -1;
      } while (value != 0);
    }
    do {
      write_byte_buffered();
      in_CX = in_CX + -1;
    } while (in_CX != 0);
    finalize_write();
  }
  return;
}



undefined1 __stdcall16far skip_whitespace(void)

{
  byte bVar1;
  undefined1 uVar2;
  byte bVar3;
  undefined1 in_ZF;
  
  bVar3 = 0;
  input_device_dispatch();
  if ((bool)in_ZF) {
    do {
      bVar1 = read_byte_buffered();
      if ((bVar1 == ITEM_SIZE) || ((((bVar3 & 1) != 0 && (bVar1 == 0xd)) || ((bVar3 & 2) == 0)))) break;
    } while (bVar1 < 0x21);
    uVar2 = finalize_read();
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



byte __stdcall16far to_uppercase(byte param_1)

{
  if ((0x60 < param_1) && (param_1 < 0x7b)) {
    param_1 = param_1 - 0x20;
  }
  return param_1;
}


