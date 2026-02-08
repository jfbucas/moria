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




undefined2 FUN_1000_0000(int *param_1)

{
  undefined2 local_4;
  
  if (*param_1 == 0) {
    local_4 = 0;
  }
  else if (*param_1 < 1) {
    local_4 = 0xffff;
  }
  else {
    local_4 = 1;
  }
  return local_4;
}



void __cdecl16near FUN_1000_0040(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  undefined2 uVar2;
  undefined2 uVar3;
  
  FUN_20e6_0260(1,1);
  uVar1 = 0x20e6;
  FUN_20e6_0227();
  if (*(int *)0xb892 < 100) {
    uVar2 = 0xe654;
    uVar3 = unaff_DS;
    FUN_214c_17f7(0,0x34,0x20e6);
    uVar1 = 0x214c;
    FUN_214c_1755(uVar2,uVar3);
  }
  if (*(int *)0xb909 < 400) {
    uVar3 = 0xe654;
    FUN_214c_17f7(0,0x3a,uVar1);
    FUN_214c_1755(uVar3,unaff_DS);
  }
  return;
}



void __cdecl16near FUN_1000_0094(void)

{
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  uVar1 = 0xe654;
  FUN_214c_1799(0,0x20);
  FUN_214c_1755(uVar1,unaff_DS);
  return;
}



void __cdecl16near FUN_1000_00b3(void)

{
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  uVar1 = 0xe654;
  FUN_214c_17f7(0,0xb0,0x1000);
  FUN_214c_1755(uVar1,unaff_DS);
  return;
}



void FUN_1000_00de(int *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int *piVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  piVar2 = (int *)param_1;
  *param_1 = (int)uVar1;
  piVar2[1] = (int)((ulong)uVar1 >> 0x10);
  while ((*param_1 != 0 || piVar2[1] != 0 &&
         ((*(int *)((int)*(undefined4 *)param_1 + 0x1c) != param_3 ||
          (*(int *)((int)*(undefined4 *)param_1 + 0x1e) != param_2))))) {
    uVar1 = *(undefined4 *)((int)*(undefined4 *)param_1 + 0x32);
    *param_1 = (int)uVar1;
    piVar2[1] = (int)((ulong)uVar1 >> 0x10);
  }
  if (*param_1 == 0 && piVar2[1] == 0) {
    FUN_1000_0040();
    uVar3 = 0xe654;
    FUN_214c_17f7(0,0xd1,0x1000);
    FUN_214c_1755(uVar3,unaff_DS);
    FUN_1000_1448();
  }
  return;
}



void FUN_1000_016a(int param_1)

{
  int iVar1;
  undefined2 unaff_DS;
  undefined2 uVar2;
  
  iVar1 = param_1;
  if (param_1 < 0) {
    FUN_1000_0040();
    iVar1 = -param_1;
  }
  if (iVar1 < 0x191) {
    iVar1 = param_1;
    if (param_1 < 0) {
      iVar1 = -param_1;
    }
    if (iVar1 < 0x12d) {
      iVar1 = param_1;
      if (param_1 < 0) {
        iVar1 = -param_1;
      }
      if (iVar1 < 0x65) {
        uVar2 = 0xe654;
        iVar1 = param_1;
        if (param_1 < 0) {
          iVar1 = -param_1;
        }
        FUN_214c_17f7(0,iVar1 * 0x33 + -0x3bb7,unaff_DS);
        FUN_214c_1755(uVar2,unaff_DS);
      }
      else {
        uVar2 = 0xe654;
        iVar1 = param_1;
        if (param_1 < 0) {
          iVar1 = -param_1;
        }
        FUN_214c_17f7(0,(iVar1 + -100) * 0x1f + -0x29b5,unaff_DS);
        FUN_214c_1755(uVar2,unaff_DS);
      }
    }
    else {
      uVar2 = 0xe654;
      iVar1 = param_1;
      if (param_1 < 0) {
        iVar1 = -param_1;
      }
      FUN_214c_17f7(0,(iVar1 + -300) * 0x49 + -0x44a4,unaff_DS);
      FUN_214c_1755(uVar2,unaff_DS);
    }
  }
  else {
    uVar2 = 0xe654;
    iVar1 = param_1;
    if (param_1 < 0) {
      iVar1 = -param_1;
    }
    FUN_214c_17f7(0,(iVar1 + -400) * 0x10 + -0x1c73,unaff_DS);
    FUN_214c_1755(uVar2,unaff_DS);
  }
  if (param_1 < 0) {
    FUN_1000_1448();
  }
  return;
}



void __cdecl16near FUN_1000_0296(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 unaff_DS;
  undefined2 uVar3;
  undefined2 uVar4;
  
  uVar1 = FUN_20e6_028c();
  uVar2 = FUN_20e6_0298(uVar1);
  FUN_20e6_0260(0x19,1);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_17f7(0,0x261,0x20e6);
  FUN_214c_1882(2,*(int *)0xe52d,*(int *)0xe52d >> 0xf);
  FUN_214c_1755(uVar3,uVar4);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_17f7(0,0x266,0x214c);
  FUN_214c_1882(6,*(undefined2 *)0xb8c8,*(undefined2 *)0xb8ca);
  FUN_214c_17f7(0,0x26a,0x214c);
  FUN_214c_1882(4,*(int *)0xb870,*(int *)0xb870 >> 0xf);
  FUN_214c_1799(0,CONCAT11(extraout_AH,0x2f));
  FUN_214c_1882(3,*(int *)0xb872,*(int *)0xb872 >> 0xf);
  FUN_214c_17f7(0,0x270,0x214c);
  FUN_214c_1882(3,*(int *)0xb87a,*(int *)0xb87a >> 0xf);
  FUN_214c_17f7(0,0x277,0x214c);
  FUN_214c_1882(3,*(int *)0xb878,*(int *)0xb878 >> 0xf);
  FUN_214c_17f7(0,0x27e,0x214c);
  FUN_214c_1882(3,*(int *)0xb874,*(int *)0xb874 >> 0xf);
  FUN_214c_17f7(0,0x285,0x214c);
  FUN_214c_1755(uVar3,uVar4);
  if (*(int *)0xb880 < 1) {
    FUN_1000_0094();
  }
  else {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_17f7(0,0x28b,0x214c);
    FUN_214c_1755(uVar3,uVar4);
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1882(1,*(int *)0xb880,*(int *)0xb880 >> 0xf);
  FUN_214c_17f7(0,0x28e,0x214c);
  FUN_214c_1882(2,*(int *)0xb888,*(int *)0xb888 >> 0xf);
  FUN_214c_1799(0,CONCAT11(extraout_AH_00,0x2f));
  FUN_214c_1882(4,*(int *)0xb886,*(int *)0xb886 >> 0xf);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0227();
  FUN_20e6_0260(CONCAT11(extraout_AH_01,uVar2),CONCAT11(extraout_AH_01,uVar1));
  return;
}



void FUN_1000_0428(undefined1 param_1,undefined1 param_2,int param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined2 unaff_DS;
  undefined2 uVar3;
  
  uVar1 = FUN_20e6_028c();
  uVar2 = FUN_20e6_0298(uVar1);
  FUN_20e6_0260(param_3 + 1,param_2);
  uVar3 = 0xe654;
  FUN_214c_1799(0,CONCAT11(extraout_AH,param_1));
  FUN_214c_1755(uVar3,unaff_DS);
  FUN_20e6_0260(CONCAT11(extraout_AH_00,uVar2),CONCAT11(extraout_AH_00,uVar1));
  return;
}



undefined2 FUN_1000_0479(char *param_1)

{
  undefined2 unaff_DS;
  
  return CONCAT11((char)((uint)(*param_1 + 1) >> 8),*(undefined1 *)(*param_1 + -0x4639));
}



void FUN_1000_0499(char param_1,int param_2)

{
  undefined2 unaff_DS;
  undefined2 uVar1;
  undefined2 uVar2;
  
  if (param_1 == '\0') {
    uVar1 = 0xe654;
    uVar2 = unaff_DS;
    FUN_214c_17f7(0,param_2 * 5 + -0x4985,unaff_DS);
    FUN_214c_1755(uVar1,uVar2);
  }
  else {
    uVar1 = 0xe654;
    uVar2 = unaff_DS;
    FUN_214c_17f7(0,param_2 * 5 + -0x4a34,unaff_DS);
    FUN_214c_1755(uVar1,uVar2);
  }
  uVar2 = 0xe654;
  FUN_214c_17f7(0,param_2 * 0x2a + -0x5017,unaff_DS);
  FUN_214c_1755(uVar2,unaff_DS);
  return;
}



void FUN_1000_0510(undefined2 param_1,undefined2 param_2)

{
  undefined1 extraout_AH;
  
  FUN_1000_016a(param_2);
  FUN_1000_0499(CONCAT11(extraout_AH,1),param_1);
  FUN_1000_00b3();
  return;
}



undefined1 FUN_1000_052b(char *param_1)

{
  undefined1 uVar1;
  
  if ((*param_1 == '\a') && (*(int *)((char *)param_1 + 1) == 0xc)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



void FUN_1000_0556(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  if (*(int *)0xaba7 == 0 && *(int *)0xaba9 == 0) {
    FUN_214c_038e(0x36,(undefined4 *)param_1,uVar3);
    *(int *)0xe52f = *(int *)0xe52f + 1;
  }
  else {
    uVar1 = *(undefined4 *)0xaba7;
    *(int *)param_1 = (int)uVar1;
    *(undefined2 *)((int)(undefined4 *)param_1 + 2) = (int)((ulong)uVar1 >> 0x10);
    uVar1 = *(undefined4 *)((int)*(undefined4 *)0xaba7 + 0x32);
    *(undefined2 *)0xaba7 = (int)uVar1;
    *(undefined2 *)0xaba9 = (int)((ulong)uVar1 >> 0x10);
    uVar3 = (undefined2)((ulong)*param_1 >> 0x10);
    iVar2 = (int)*param_1;
    *(undefined2 *)(iVar2 + 0x32) = 0;
    *(undefined2 *)(iVar2 + 0x34) = 0;
  }
  return;
}



void FUN_1000_05b0(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined4 *)0xaba7;
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar2 = (int)param_1;
  *(undefined2 *)(iVar2 + 0x32) = (int)uVar1;
  *(undefined2 *)(iVar2 + 0x34) = (int)((ulong)uVar1 >> 0x10);
  *(int *)0xaba7 = iVar2;
  *(undefined2 *)0xaba9 = uVar3;
  return;
}



void FUN_1000_05d6(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  if (*(int *)0xabab == 0 && *(int *)0xabad == 0) {
    FUN_214c_038e(0x1a,(undefined4 *)param_1,uVar3);
    *(int *)0xe531 = *(int *)0xe531 + 1;
  }
  else {
    uVar1 = *(undefined4 *)0xabab;
    *(int *)param_1 = (int)uVar1;
    *(undefined2 *)((int)(undefined4 *)param_1 + 2) = (int)((ulong)uVar1 >> 0x10);
    uVar1 = *(undefined4 *)((int)*(undefined4 *)0xabab + 0x16);
    *(undefined2 *)0xabab = (int)uVar1;
    *(undefined2 *)0xabad = (int)((ulong)uVar1 >> 0x10);
  }
  uVar3 = (undefined2)((ulong)*param_1 >> 0x10);
  iVar2 = (int)*param_1;
  *(undefined2 *)(iVar2 + 0x16) = 0;
  *(undefined2 *)(iVar2 + 0x18) = 0;
  *(undefined2 *)((int)*param_1 + 3) = 1;
  return;
}



void FUN_1000_063c(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined4 *)0xabab;
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar2 = (int)param_1;
  *(undefined2 *)(iVar2 + 0x16) = (int)uVar1;
  *(undefined2 *)(iVar2 + 0x18) = (int)((ulong)uVar1 >> 0x10);
  *(int *)0xabab = iVar2;
  *(undefined2 *)0xabad = uVar3;
  return;
}



void FUN_1000_0662(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  local_4 = 0;
  bVar3 = false;
  do {
    local_4 = local_4 + 1;
    if ((*(int *)(local_4 * 4 + -0x46cc) != 0 || *(int *)(local_4 * 4 + -0x46ca) != 0) &&
       (uVar1 = *(undefined4 *)(local_4 * 4 + -0x46cc), *(int *)((int)uVar1 + 1) == param_1)) {
      uVar1 = *(undefined4 *)(local_4 * 4 + -0x46cc);
      uVar2 = *(undefined4 *)(local_4 * 4 + -0x46cc);
      *(int *)((int)uVar2 + 9) = *(int *)((int)uVar1 + 9) + -1;
      bVar3 = true;
    }
  } while ((local_4 != *(int *)0xb936) && (!bVar3));
  return;
}



undefined2 FUN_1000_06d5(uint param_1)

{
  undefined4 uVar1;
  uint uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined1 local_28 [32];
  int local_8;
  int local_6;
  char local_4;
  char local_3;
  
  local_4 = '\0';
  local_6 = 0;
  if (0 < *(int *)0xb936) {
    local_6 = 1;
    while( true ) {
      if ((local_4 == '\0') &&
         (*(int *)(local_6 * 4 + -0x46cc) == 0 && *(int *)(local_6 * 4 + -0x46ca) == 0)) {
        local_4 = '\0';
      }
      else {
        local_4 = '\x01';
      }
      if (local_6 == *(int *)0xb936) break;
      local_6 = local_6 + 1;
    }
  }
  if (param_1 == 0) {
    uVar3 = (undefined1)((uint)local_6 >> 8);
    local_3 = local_4;
  }
  else {
    local_4 = '\0';
    local_8 = *(int *)0xb936;
    local_6 = 0;
    uVar3 = local_8 == 1;
    if (0 < local_8) {
      local_6 = 1;
      while( true ) {
        uVar2 = param_1 & 0xff;
        puVar4 = local_28;
        uVar5 = unaff_SS;
        FUN_214c_08af(puVar4);
        FUN_214c_08be(CONCAT11(extraout_AH,0x12));
        FUN_214c_08be(CONCAT11(extraout_AH_00,0x13));
        FUN_214c_0933(puVar4,uVar5,uVar2);
        if ((bool)uVar3) {
          if ((local_4 == '\0') &&
             ((*(int *)(local_6 * 4 + -0x46cc) == 0 && *(int *)(local_6 * 4 + -0x46ca) == 0 ||
              (uVar1 = *(undefined4 *)(local_6 * 4 + -0x46cc), *(uint *)((int)uVar1 + 1) != param_1)
              ))) {
            local_4 = '\0';
          }
          else {
            local_4 = '\x01';
          }
        }
        else if (((*(int *)(local_6 * 4 + -0x46cc) != 0 || *(int *)(local_6 * 4 + -0x46ca) != 0) &&
                 (uVar1 = *(undefined4 *)(local_6 * 4 + -0x46cc),
                 *(uint *)((int)uVar1 + 1) == param_1)) &&
                (uVar1 = *(undefined4 *)(local_6 * 4 + -0x46cc), 0 < *(int *)((int)uVar1 + 9))) {
          local_4 = '\x01';
        }
        if (local_6 == local_8) break;
        local_6 = local_6 + 1;
        uVar3 = local_6 == 0;
      }
    }
    uVar3 = (undefined1)((uint)local_6 >> 8);
    local_3 = local_4;
  }
  return CONCAT11(uVar3,local_3);
}



void __cdecl16near FUN_1000_07fb(void)

{
  int iVar1;
  char *pcVar2;
  undefined2 unaff_DS;
  char *local_6;
  int local_4;
  
  pcVar2 = (char *)*(undefined4 *)0xb91e;
  while (local_6 = (char *)pcVar2, local_4 = (int)((ulong)pcVar2 >> 0x10),
        local_6 != (char *)0x0 || local_4 != 0) {
    if (*pcVar2 == '\b') {
      iVar1 = *(int *)(local_6 + 1);
      *(undefined2 *)(iVar1 * 4 + -0x476c) = local_6;
      *(int *)(iVar1 * 4 + -0x476a) = local_4;
    }
    pcVar2 = *(char **)(local_6 + 0x16);
  }
  return;
}



void FUN_1000_084b(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  *param_1 = 0;
  iVar1 = *(int *)0xb936;
  if (0 < iVar1) {
    local_4 = 1;
    while( true ) {
      if ((*(int *)(local_4 * 4 + -0x46cc) != 0 || *(int *)(local_4 * 4 + -0x46ca) != 0) &&
         (uVar2 = *(undefined4 *)(local_4 * 4 + -0x46cc), *(int *)((int)uVar2 + 1) == param_2)) {
        uVar2 = *(undefined4 *)(local_4 * 4 + -0x46cc);
        *param_1 = *param_1 + *(int *)((int)uVar2 + 9);
      }
      if (local_4 == iVar1) break;
      local_4 = local_4 + 1;
    }
  }
  return;
}



void FUN_1000_08bd(char param_1,undefined1 *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined2 unaff_DS;
  int local_4;
  
  *param_2 = 1;
  if ((((((int)((ulong)*param_3 >> 0x10) == *(int *)0xb928) && ((int)*param_3 == *(int *)0xb926)) ||
       (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb92c && ((int)*param_3 == *(int *)0xb92a)))) ||
      (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb934 && ((int)*param_3 == *(int *)0xb932)))) ||
     (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb930 && ((int)*param_3 == *(int *)0xb92e)))) {
    if (*(char *)((int)*param_3 + 0x14) == '\0') {
      if (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb928) && ((int)*param_3 == *(int *)0xb926)) {
        *(undefined2 *)0xb926 = 0;
        *(undefined2 *)0xb928 = 0;
        *(undefined2 *)0xb87c = 0;
      }
      if (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb92c) && ((int)*param_3 == *(int *)0xb92a)) {
        *(undefined2 *)0xb92a = 0;
        *(undefined2 *)0xb92c = 0;
        *(undefined2 *)0xb87e = 0;
      }
      if (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb934) && ((int)*param_3 == *(int *)0xb932)) {
        *(undefined2 *)0xb932 = 0;
        *(undefined2 *)0xb934 = 0;
        *(undefined2 *)0xb884 = 0;
      }
      if (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb930) && ((int)*param_3 == *(int *)0xb92e)) {
        *(undefined2 *)0xb92e = 0;
        *(undefined2 *)0xb930 = 0;
      }
    }
    else {
      *param_2 = 0;
      if (param_1 == '\0') {
        FUN_1000_016a(0x4f);
      }
    }
    *(int *)0xb880 = *(int *)0xb87c + *(int *)0xb87e;
  }
  else if (((int)((ulong)*param_3 >> 0x10) == *(int *)0xb924) && ((int)*param_3 == *(int *)0xb922))
  {
    *(undefined2 *)0xb922 = 0;
    *(undefined2 *)0xb924 = 0;
    *(undefined2 *)0xb882 = 0;
  }
  else {
    iVar1 = *(int *)0xb936;
    if (0 < iVar1) {
      local_4 = 1;
      while( true ) {
        if (((int)((ulong)*param_3 >> 0x10) == *(int *)(local_4 * 4 + -0x46ca)) &&
           ((int)*param_3 == *(int *)(local_4 * 4 + -0x46cc))) {
          if (*(char *)((int)*param_3 + 0x14) == '\0') {
            *(undefined2 *)(local_4 * 4 + -0x46cc) = 0;
            *(undefined2 *)(local_4 * 4 + -0x46ca) = 0;
          }
          else {
            *param_2 = 0;
            if (param_1 == '\0') {
              FUN_1000_016a(0x4e);
            }
          }
        }
        if (local_4 == iVar1) break;
        local_4 = local_4 + 1;
      }
    }
  }
  return;
}



undefined1 FUN_1000_0a6f(undefined2 param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  
  if ((((param_3 < 1) || (0x16 < param_3)) || (param_2 < 1)) || (0x4f < param_2)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



void FUN_1000_0a9f(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  int iVar3;
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
  
  if ((*(char *)0xb8f2 == '\0') ||
     (cVar2 = FUN_1000_0a6f(param_1,param_2 + *(int *)(param_1 + -2),
                            param_3 + *(int *)(param_1 + -4)), cVar2 != '\0')) {
    if (*(char *)(param_3 * 0x4f + param_2 + -0xc) == ' ') {
      if (*(char *)(*(int *)0xe52d * 0x719 + param_3 * 0x4f + param_2 + 0x70d) != '\0') {
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        iVar3 = (int)uVar1 + param_3 * 0x4f + param_2;
        uVar4 = iVar3 == 0;
        uVar7 = CONCAT11((char)((uint)(param_3 * 0x4f) >> 8),*(undefined1 *)(iVar3 + -0x50));
        puVar5 = local_2c;
        uVar6 = unaff_SS;
        FUN_214c_0885(0x20,0xb76f,unaff_DS);
        FUN_214c_0933(puVar5,uVar6,uVar7);
        if (((!(bool)uVar4) && (*(char *)0xb8f2 == '\0')) && (*(char *)0xb8ee == '\0')) {
          return;
        }
      }
      if (*(char *)0xb8ee == '\0') {
        *(undefined1 *)(*(int *)0xe52d * 0x719 + param_3 * 0x4f + param_2 + 0x70d) = 1;
      }
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar3 = (int)uVar1 + param_3 * 0x4f + param_2;
      uVar4 = iVar3 == 0;
      uVar7 = CONCAT11((char)((uint)(param_3 * 0x4f) >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar5 = local_4c;
      uVar6 = unaff_SS;
      FUN_214c_0885(0x20,0xb7cf,unaff_DS);
      FUN_214c_0933(puVar5,uVar6,uVar7);
      if (((bool)uVar4) || (*(char *)0xb8f0 == '\0')) {
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        iVar3 = (int)uVar1 + param_3 * 0x4f + param_2;
        uVar4 = iVar3 == 0;
        uVar7 = CONCAT11((char)((uint)(param_3 * 0x4f) >> 8),*(undefined1 *)(iVar3 + -0x50));
        puVar5 = local_6c;
        uVar6 = unaff_SS;
        FUN_214c_08af(puVar5);
        FUN_214c_08be(CONCAT11(extraout_AH_00,0x20));
        FUN_214c_08be(CONCAT11(extraout_AH_01,*(undefined1 *)0x1));
        FUN_214c_08be(CONCAT11(extraout_AH_02,*(undefined1 *)0x3));
        FUN_214c_0933(puVar5,uVar6,uVar7);
        if ((bool)uVar4) {
          FUN_20e6_0260(*(int *)(param_1 + -4) + param_3 + 1,*(int *)(param_1 + -2) + param_2);
          uVar6 = 0xe654;
          uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
          FUN_214c_1799(0,CONCAT11((char)((uint)(param_3 * 0x4f) >> 8),
                                   *(undefined1 *)((int)uVar1 + param_3 * 0x4f + param_2 + -0x50)));
          FUN_214c_1755(uVar6,unaff_DS);
        }
        else {
          uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
          if (*(char *)((int)uVar1 + param_3 * 0x4f + param_2 + -0x50) != ' ') {
            puVar5 = local_16c;
            uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
            uVar6 = unaff_SS;
            FUN_214c_07ae(CONCAT11((char)((uint)(param_3 * 0x4f) >> 8),
                                   *(undefined1 *)((int)uVar1 + param_3 * 0x4f + param_2 + -0x50)));
            iVar3 = FUN_214c_1352(local_8,unaff_SS,puVar5,uVar6);
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
              uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
              *(undefined1 *)((int)uVar1 + param_3 * 0x4f + param_2 + -0x50) =
                   *(undefined1 *)(iVar3 * 2 + -2);
            }
          }
        }
      }
      else {
        FUN_20e6_0260(*(int *)(param_1 + -4) + param_3 + 1,*(int *)(param_1 + -2) + param_2);
        uVar7 = 0xe654;
        uVar6 = unaff_DS;
        iVar3 = FUN_214c_1162(*(undefined1 *)0xb9c6);
        FUN_214c_1799(0,CONCAT11((char)((uint)(iVar3 + 1) >> 8),*(undefined1 *)(iVar3 + -0x4639)));
        FUN_214c_1755(uVar7,uVar6);
      }
    }
    else {
      FUN_1000_00de(param_1 + -0x10,unaff_SS,param_2,param_3);
      if (*(char *)((int)*(undefined4 *)(param_1 + -0x10) + 0x27) == '\0') {
        FUN_20e6_0260(*(int *)(param_1 + -4) + param_3 + 1,*(int *)(param_1 + -2) + param_2);
        uVar6 = 0xe654;
        FUN_214c_1799(0,CONCAT11(extraout_AH,
                                 *(undefined1 *)((int)*(undefined4 *)(param_1 + -0x10) + 1)));
        FUN_214c_1755(uVar6,unaff_DS);
      }
      *(undefined1 *)((int)*(undefined4 *)(param_1 + -0x10) + 0x23) = 1;
    }
  }
  return;
}



void __cdecl16near FUN_1000_0e28(void)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  undefined2 uVar4;
  uint uVar5;
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
  undefined1 local_58 [32];
  undefined1 local_38 [4];
  undefined1 local_34 [28];
  int local_18;
  uint local_16;
  int local_14;
  uint local_e;
  int local_c;
  uint local_a;
  uint local_8;
  int local_6;
  int local_4;
  
  if (*(char *)0xb8ed == '\0') {
    local_a = FUN_20e6_028c();
    local_a = local_a & 0xff;
    local_8 = FUN_20e6_0298();
    local_8 = local_8 & 0xff;
    local_14 = *(int *)0xb888 + 5;
    if (*(char *)0xb8f2 == '\0') {
      local_6 = 0;
      local_4 = 0;
    }
    else {
      local_6 = 0xc - *(int *)0xb86c;
      local_4 = 0x27 - *(int *)0xb86e;
    }
    if (*(char *)0xb8f2 == '\0') {
      if (*(char *)0xb8ee != '\0') {
        local_16 = *(uint *)0xe537;
        local_e = *(uint *)0xe535;
        if ((int)local_e <= (int)local_16) {
          while( true ) {
            FUN_20e6_0260(local_e + 1,1);
            FUN_20e6_0227();
            if (local_e == local_16) break;
            local_e = local_e + 1;
          }
        }
      }
    }
    else {
      local_16 = *(int *)0xe537 + 1;
      local_e = *(int *)0xe535 - 1;
      if ((int)local_e <= (int)local_16) {
        while( true ) {
          if ((1 < (int)((local_e + 0xd) - *(int *)0xb86c)) &&
             (iVar3 = (local_e + 0xd) - *(int *)0xb86c, iVar3 < 0x19)) {
            FUN_20e6_0260((local_e + 0xd) - *(int *)0xb86c,CONCAT11((char)((uint)iVar3 >> 8),1));
          }
          FUN_20e6_0227();
          if (local_e == local_16) break;
          local_e = local_e + 1;
        }
      }
    }
    local_e = *(int *)0xb86c;
    do {
      local_e = local_e + -1;
      local_c = -1;
      while (FUN_1000_0a9f(&stack0xfffe,local_c + *(int *)0xb86e,local_e), local_c != 1) {
        local_c = local_c + 1;
      }
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar3 = (int)uVar1 + local_e * 0x4f + *(int *)0xb86e;
      uVar6 = iVar3 == 0;
      uVar4 = CONCAT11((char)(local_e * 0x4f >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar7 = local_34;
      uVar8 = unaff_SS;
      FUN_214c_0885(0x20,0xb76f,unaff_DS);
      FUN_214c_0933(puVar7,uVar8,uVar4);
    } while (((bool)uVar6) && (*(int *)0xb86c - local_e != local_14));
    *(int *)0xe535 = local_e;
    local_e = *(int *)0xb86c;
    do {
      local_e = local_e + 1;
      local_c = -1;
      while (FUN_1000_0a9f(&stack0xfffe,local_c + *(int *)0xb86e,local_e), local_c != 1) {
        local_c = local_c + 1;
      }
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar3 = (int)uVar1 + local_e * 0x4f + *(int *)0xb86e;
      uVar6 = iVar3 == 0;
      uVar4 = CONCAT11((char)(local_e * 0x4f >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar7 = local_34;
      uVar8 = unaff_SS;
      FUN_214c_0885(0x20,0xb76f,unaff_DS);
      FUN_214c_0933(puVar7,uVar8,uVar4);
    } while (((bool)uVar6) && (local_e - *(int *)0xb86c != local_14));
    *(int *)0xe537 = local_e;
    local_e = *(int *)0xb86e;
    do {
      local_e = local_e + -1;
      local_c = -1;
      while (FUN_1000_0a9f(&stack0xfffe,local_e,*(int *)0xb86c + local_c), local_c != 1) {
        local_c = local_c + 1;
      }
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar3 = (int)uVar1 + *(int *)0xb86c * 0x4f + local_e;
      uVar6 = iVar3 == 0;
      uVar4 = CONCAT11((char)((uint)(*(int *)0xb86c * 0x4f) >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar7 = local_34;
      uVar8 = unaff_SS;
      FUN_214c_0885(0x20,0xb76f,unaff_DS);
      FUN_214c_0933(puVar7,uVar8,uVar4);
    } while (((bool)uVar6) && (*(int *)0xb86e - local_e != local_14));
    local_e = *(uint *)0xb86e;
    do {
      local_e = local_e + 1;
      local_c = -1;
      while (FUN_1000_0a9f(&stack0xfffe,local_e,*(int *)0xb86c + local_c), local_c != 1) {
        local_c = local_c + 1;
      }
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar3 = (int)uVar1 + *(int *)0xb86c * 0x4f + local_e;
      uVar6 = iVar3 == 0;
      uVar4 = CONCAT11((char)((uint)(*(int *)0xb86c * 0x4f) >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar7 = local_34;
      uVar8 = unaff_SS;
      FUN_214c_0885(0x20,0xb76f,unaff_DS);
      FUN_214c_0933(puVar7,uVar8,uVar4);
    } while (((bool)uVar6) && (local_e - *(int *)0xb86e != local_14));
    cVar2 = FUN_1000_06d5(0x11);
    if (cVar2 != '\0') {
      local_16 = *(int *)0xb86c + 2;
      uVar5 = *(int *)0xb86c - 2U;
      if ((int)(*(int *)0xb86c - 2U) <= (int)local_16) {
        do {
          local_e = uVar5;
          local_18 = *(int *)0xb86e + 2;
          iVar3 = *(int *)0xb86e + -2;
          uVar6 = iVar3 == local_18;
          if (iVar3 <= local_18) {
            do {
              local_c = iVar3;
              uVar5 = local_e & 0xff;
              puVar7 = local_38;
              uVar8 = unaff_SS;
              FUN_214c_08af(puVar7);
              FUN_214c_08df(CONCAT11(extraout_AH,0x16),CONCAT11(extraout_AH,2));
              FUN_214c_0933(puVar7,uVar8,uVar5);
              if (!(bool)uVar6) {
                uVar4 = CONCAT11(extraout_AH_00,(undefined1)local_c);
                puVar7 = local_58;
                uVar8 = unaff_SS;
                FUN_214c_08af(puVar7);
                FUN_214c_08df(CONCAT11(extraout_AH_01,0x4e),CONCAT11(extraout_AH_01,2));
                FUN_214c_0933(puVar7,uVar8,uVar4);
                if (!(bool)uVar6) {
                  iVar3 = local_e - *(int *)0xb86c;
                  if (iVar3 < 0) {
                    iVar3 = -iVar3;
                  }
                  if (iVar3 < 2) {
                    iVar3 = local_c - *(int *)0xb86e;
                    if (iVar3 < 0) {
                      iVar3 = -iVar3;
                    }
                    if (iVar3 < 2) goto LAB_1000_11a4;
                  }
                  FUN_1000_0a9f(&stack0xfffe,local_c,local_e);
                }
              }
LAB_1000_11a4:
              if (local_c == local_18) break;
              uVar6 = local_c + 1 == 0;
              iVar3 = local_c + 1;
            } while( true );
          }
          if (local_e == local_16) break;
          uVar5 = local_e + 1;
        } while( true );
      }
    }
    local_6 = *(int *)0xb86c + local_6;
    local_4 = local_4 + *(int *)0xb86e;
    uVar6 = (undefined1)((uint)local_4 >> 8);
    if (*(char *)0xb8f6 == '\0') {
      FUN_1000_0428(CONCAT11(uVar6,2),local_4,local_6);
      uVar6 = extraout_AH_03;
    }
    else {
      FUN_1000_0428(CONCAT11(uVar6,0x7e),local_4,local_6);
      uVar6 = extraout_AH_02;
    }
    FUN_20e6_0260(CONCAT11(uVar6,(undefined1)local_8),CONCAT11(uVar6,(undefined1)local_a));
  }
  return;
}



void FUN_1000_11fc(int param_1)

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
  int iVar3;
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
  
  local_8 = param_1;
  if (-1 < param_1) {
    local_6 = 0;
    while( true ) {
      FUN_20e6_0260(local_6 + 1,1);
      FUN_20e6_0227();
      if (local_6 == local_8) break;
      local_6 = local_6 + 1;
    }
  }
  if ((((*(char *)0xb8f2 != '\0') || (*(char *)0xb8ee != '\0')) || (*(char *)0xb8ed != '\0')) ||
     (local_8 = param_1, param_1 < 1)) {
LAB_1000_141d:
    FUN_1000_0296();
    if (*(char *)0xb8f2 == '\0') {
      FUN_1000_0e28();
    }
    else {
      local_6 = 0xc;
      local_4 = 0x27;
      FUN_1000_0428(CONCAT11(extraout_AH_08,2),0x27,0xc);
    }
    return;
  }
  local_6 = 1;
LAB_1000_1269:
  local_4 = 1;
  do {
    if (*(char *)(*(int *)0xe52d * 0x719 + local_6 * 0x4f + local_4 + 0x70d) == '\0') {
LAB_1000_132c:
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      if (*(char *)((int)uVar1 + 0x719) != '\0') {
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        iVar3 = (int)uVar1 + local_6 * 0x4f + local_4;
        uVar4 = iVar3 == 0;
        uVar2 = CONCAT11((char)((uint)(local_6 * 0x4f) >> 8),*(undefined1 *)(iVar3 + -0x50));
        puVar7 = local_48;
        uVar8 = unaff_SS;
        FUN_214c_0885(0x20,0xb76f,unaff_DS);
        puVar5 = local_68;
        uVar6 = unaff_SS;
        FUN_214c_0885(0x20,0xb78f,unaff_DS);
        FUN_214c_0954(puVar5,uVar6);
        puVar5 = local_88;
        uVar6 = unaff_SS;
        FUN_214c_08af(puVar5);
        FUN_214c_08be(CONCAT11(extraout_AH_03,0xef));
        FUN_214c_08be(CONCAT11(extraout_AH_04,0xf7));
        FUN_214c_0954(puVar5,uVar6);
        FUN_214c_0933(puVar7,uVar8,uVar2);
        if (!(bool)uVar4) {
          FUN_20e6_02a4(CONCAT11(extraout_AH_05,10));
          FUN_20e6_0260(local_6 + 1,CONCAT11(extraout_AH_06,(undefined1)local_4));
          uVar8 = 0xe654;
          uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
          uVar6 = unaff_DS;
          FUN_214c_1799(0,CONCAT11((char)((uint)(local_6 * 0x4f) >> 8),
                                   *(undefined1 *)((int)uVar1 + local_6 * 0x4f + local_4 + -0x50)));
          FUN_214c_1755(uVar8,uVar6);
          FUN_20e6_02a4(CONCAT11(extraout_AH_07,0xf));
        }
      }
    }
    else {
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar3 = (int)uVar1 + local_6 * 0x4f + local_4;
      uVar4 = iVar3 == 0;
      uVar8 = CONCAT11((char)((uint)(local_6 * 0x4f) >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar7 = local_28;
      uVar6 = unaff_SS;
      FUN_214c_08af(puVar7);
      FUN_214c_08be(CONCAT11(extraout_AH,0x20));
      FUN_214c_08be(CONCAT11(extraout_AH_00,*(undefined1 *)0x1));
      FUN_214c_08be(CONCAT11(extraout_AH_01,*(undefined1 *)0x3));
      FUN_214c_0933(puVar7,uVar6,uVar8);
      if (!(bool)uVar4) goto LAB_1000_132c;
      FUN_20e6_0260(local_6 + 1,CONCAT11(extraout_AH_02,(undefined1)local_4));
      uVar8 = 0xe654;
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      uVar6 = unaff_DS;
      FUN_214c_1799(0,CONCAT11((char)((uint)(local_6 * 0x4f) >> 8),
                               *(undefined1 *)((int)uVar1 + local_6 * 0x4f + local_4 + -0x50)));
      FUN_214c_1755(uVar8,uVar6);
    }
    if (local_4 == 0x4f) break;
    local_4 = local_4 + 1;
  } while( true );
  if (local_6 == local_8) goto LAB_1000_141d;
  local_6 = local_6 + 1;
  goto LAB_1000_1269;
}



void __cdecl16near FUN_1000_1448(void)

{
  char cVar1;
  
  FUN_1000_016a(0xc0);
  FUN_20e6_0227();
  do {
    cVar1 = FUN_20e6_0357();
  } while (cVar1 != ' ');
  cVar1 = FUN_20e6_0298();
  if (cVar1 == '\x02') {
    FUN_1000_11fc(1);
  }
  else {
    FUN_1000_0040();
  }
  return;
}



void FUN_1000_14ab(int *param_1,int *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  undefined2 uVar4;
  undefined2 unaff_DS;
  undefined2 uVar5;
  
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  piVar2 = (int *)param_1;
  if (*param_1 != 0 || piVar2[1] != 0) {
    if (((int)((ulong)*(undefined4 *)param_2 >> 0x10) == piVar2[1]) &&
       ((int)*(undefined4 *)param_2 == *param_1)) {
      uVar1 = *(undefined4 *)((int)*(undefined4 *)param_1 + 0x16);
      *param_1 = (int)uVar1;
      piVar2[1] = (int)((ulong)uVar1 >> 0x10);
    }
    else {
      uVar1 = *(undefined4 *)param_1;
      while( true ) {
        uVar4 = (undefined2)((ulong)uVar1 >> 0x10);
        iVar3 = (int)uVar1;
        if ((*(int *)(iVar3 + 0x16) == 0 && *(int *)(iVar3 + 0x18) == 0) ||
           (((int)((ulong)*(undefined4 *)(iVar3 + 0x16) >> 0x10) == ((int *)param_2)[1] &&
            ((int)*(undefined4 *)(iVar3 + 0x16) == *param_2)))) break;
        uVar1 = *(undefined4 *)(iVar3 + 0x16);
      }
      if (*(int *)(iVar3 + 0x16) == 0 && *(int *)(iVar3 + 0x18) == 0) {
        FUN_1000_0040();
        uVar5 = 0xe654;
        uVar4 = unaff_DS;
        FUN_214c_17f7(0,0x1481,0x1000);
        FUN_214c_1755(uVar5,uVar4);
        FUN_1000_1448();
      }
      else {
        uVar1 = *(undefined4 *)((int)*(undefined4 *)param_2 + 0x16);
        *(undefined2 *)(iVar3 + 0x16) = (int)uVar1;
        *(undefined2 *)(iVar3 + 0x18) = (int)((ulong)uVar1 >> 0x10);
      }
    }
  }
  if (**(char **)param_2 == '\b') {
    iVar3 = *(int *)((int)*(undefined4 *)param_2 + 1) * 4;
    *(undefined2 *)(iVar3 + -0x476c) = 0;
    *(undefined2 *)(iVar3 + -0x476a) = 0;
    FUN_1000_07fb();
  }
  return;
}



void FUN_1000_15a2(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  
  uVar1 = *param_1;
  uVar3 = (undefined2)((ulong)*param_2 >> 0x10);
  iVar2 = (int)*param_2;
  *(undefined2 *)(iVar2 + 0x16) = (int)uVar1;
  *(undefined2 *)(iVar2 + 0x18) = (int)((ulong)uVar1 >> 0x10);
  uVar1 = *param_2;
  *(int *)param_1 = (int)uVar1;
  *(undefined2 *)((int)(undefined4 *)param_1 + 2) = (int)((ulong)uVar1 >> 0x10);
  return;
}



void FUN_1000_15d3(char param_1,char param_2,char *param_3)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  char *pcVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  char *local_6;
  undefined2 local_4;
  
  cVar2 = FUN_1000_052b((char *)param_3,param_3._2_2_);
  if (((cVar2 == '\0') || (param_1 != '\0')) || (*(int *)((char *)param_3 + 3) == 1)) {
    uVar1 = *(undefined4 *)(*param_3 * 4 + -0x4738);
    iVar4 = (int)uVar1;
    cVar2 = *param_3;
    *(int *)(cVar2 * 4 + -0x4738) = iVar4 + -1;
    *(int *)(cVar2 * 4 + -0x4736) = (int)((ulong)uVar1 >> 0x10) - (uint)(iVar4 == 0);
    *(int *)0xb8c0 = *(int *)0xb8c0 + -1;
  }
  if ((*(int *)((char *)param_3 + 3) == 1) ||
     ((cVar2 = FUN_1000_052b((char *)param_3,param_3._2_2_), cVar2 != '\0' && (param_1 != '\0')))) {
    FUN_1000_14ab(0xb91e,unaff_DS,&param_3,unaff_SS);
    *(int *)0xb8c2 = *(int *)0xb8c2 + -1;
    local_4 = (undefined2)((ulong)param_3 >> 0x10);
    local_6 = (char *)param_3;
    *(int *)0xb8c4 = *(int *)0xb8c4 - *(int *)(local_6 + 0xb);
    if (param_2 == '\0') {
      FUN_1000_063c(local_6,local_4);
    }
    else {
      FUN_1000_15a2(*(int *)0xe52d * 4 + -0x54d9,unaff_DS,&local_6,unaff_SS);
      *(undefined2 *)(local_6 + 5) = *(undefined2 *)0xb86c;
      *(undefined2 *)(local_6 + 7) = *(undefined2 *)0xb86e;
      uVar3 = FUN_1000_0479(local_6,local_4);
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      *(undefined1 *)((int)uVar1 + *(int *)(local_6 + 5) * 0x4f + *(int *)(local_6 + 7) + -0x50) =
           uVar3;
    }
  }
  else {
    uVar6 = (undefined2)((ulong)param_3 >> 0x10);
    pcVar5 = (char *)param_3;
    *(int *)(pcVar5 + 3) = *(int *)(pcVar5 + 3) + -1;
    cVar2 = FUN_1000_052b(pcVar5,uVar6);
    if (cVar2 == '\0') {
      *(int *)0xb8c4 = *(int *)0xb8c4 - *(int *)((char *)param_3 + 0xb);
    }
    if (param_2 != '\0') {
      FUN_1000_05d6(&local_6,unaff_SS);
      FUN_214c_02c0(0x1a,(int)_local_6,(int)((ulong)_local_6 >> 0x10),(char *)param_3,
                    (int)((ulong)param_3 >> 0x10));
      *(undefined2 *)((int)_local_6 + 3) = 1;
      FUN_1000_15a2(*(int *)0xe52d * 4 + -0x54d9,unaff_DS,&local_6,unaff_SS);
      uVar6 = (undefined2)((ulong)_local_6 >> 0x10);
      iVar4 = (int)_local_6;
      *(undefined2 *)(iVar4 + 5) = *(undefined2 *)0xb86c;
      *(undefined2 *)(iVar4 + 7) = *(undefined2 *)0xb86e;
      uVar3 = FUN_1000_0479(iVar4,uVar6);
      uVar6 = (undefined2)((ulong)_local_6 >> 0x10);
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      *(undefined1 *)
       ((int)uVar1 + *(int *)((int)_local_6 + 5) * 0x4f + *(int *)((int)_local_6 + 7) + -0x50) =
           uVar3;
    }
  }
  return;
}



undefined2 FUN_1000_17aa(undefined4 *param_1)

{
  undefined2 unaff_DS;
  int local_6;
  char local_4;
  
  if (((((((int)((ulong)*param_1 >> 0x10) == *(int *)0xb928) && ((int)*param_1 == *(int *)0xb926))
        || (((int)((ulong)*param_1 >> 0x10) == *(int *)0xb924 && ((int)*param_1 == *(int *)0xb922)))
        ) || (((int)((ulong)*param_1 >> 0x10) == *(int *)0xb934 && ((int)*param_1 == *(int *)0xb932)
              ))) ||
      (((int)((ulong)*param_1 >> 0x10) == *(int *)0xb92c && ((int)*param_1 == *(int *)0xb92a)))) ||
     (((int)((ulong)*param_1 >> 0x10) == *(int *)0xb930 && ((int)*param_1 == *(int *)0xb92e)))) {
    local_4 = '\x01';
  }
  else {
    local_4 = '\0';
  }
  local_6 = 0;
  if (*(int *)0xb936 < 1) {
LAB_1000_1876:
    return CONCAT11((char)((uint)local_6 >> 8),local_4);
  }
  local_6 = 1;
  do {
    if (*(int *)(local_6 * 4 + -0x46cc) != 0 || *(int *)(local_6 * 4 + -0x46ca) != 0) {
      if (local_4 == '\0') {
        if (((int)((ulong)*param_1 >> 0x10) != *(int *)(local_6 * 4 + -0x46ca)) ||
           ((int)*param_1 != *(int *)(local_6 * 4 + -0x46cc))) {
          local_4 = '\0';
          goto LAB_1000_186e;
        }
      }
      local_4 = '\x01';
    }
LAB_1000_186e:
    if (local_6 == *(int *)0xb936) goto LAB_1000_1876;
    local_6 = local_6 + 1;
  } while( true );
}



void __cdecl16near FUN_1000_1885(void)

{
  undefined4 *puVar1;
  char cVar2;
  undefined2 uVar3;
  byte bVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_8;
  int local_6;
  int local_4;
  
  local_4 = 0;
  local_6 = (int)((ulong)*(undefined4 *)0xb91e >> 0x10);
  local_8 = (int)*(undefined4 *)0xb91e;
  while (local_8 != 0 || local_6 != 0) {
    cVar2 = FUN_1000_17aa(&local_8,unaff_SS);
    if (cVar2 == '\0') {
      local_4 = local_4 + 1;
    }
    puVar1 = (undefined4 *)(local_8 + 0x16);
    local_6 = (int)((ulong)*puVar1 >> 0x10);
    local_8 = (int)*puVar1;
  }
  if (0 < local_4) {
    local_4 = FUN_214c_1162(local_4);
    local_4 = local_4 + 1;
    local_6 = (int)((ulong)*(undefined4 *)0xb91e >> 0x10);
    local_8 = (int)*(undefined4 *)0xb91e;
    do {
      cVar2 = FUN_1000_17aa(&local_8,unaff_SS);
      if (cVar2 == '\0') {
        if (1 < local_4) {
          puVar1 = (undefined4 *)(local_8 + 0x16);
          local_6 = (int)((ulong)*puVar1 >> 0x10);
          local_8 = (int)*puVar1;
        }
        local_4 = local_4 + -1;
      }
      else {
        puVar1 = (undefined4 *)(local_8 + 0x16);
        local_6 = (int)((ulong)*puVar1 >> 0x10);
        local_8 = (int)*puVar1;
      }
    } while (local_4 != 0);
    uVar3 = FUN_1000_052b(local_8,local_6);
    bVar4 = (byte)((uint)uVar3 >> 8);
    if ((char)uVar3 == '\0') {
      FUN_1000_15d3((uint)bVar4 << 8,(uint)bVar4 << 8,local_8,local_6);
    }
    else {
      FUN_1000_15d3(CONCAT11(bVar4,1),(uint)bVar4 << 8,local_8,local_6);
    }
  }
  return;
}



void FUN_1000_1988(int *param_1,int *param_2,int *param_3)

{
  undefined4 uVar1;
  int *piVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  piVar2 = (int *)param_1;
  *param_1 = (int)uVar1;
  piVar2[1] = (int)((ulong)uVar1 >> 0x10);
  while ((*param_1 != 0 || piVar2[1] != 0 &&
         ((*(int *)((int)*(undefined4 *)param_1 + 5) != *param_3 ||
          (*(int *)((int)*(undefined4 *)param_1 + 7) != *param_2))))) {
    uVar1 = *(undefined4 *)((int)*(undefined4 *)param_1 + 0x16);
    *param_1 = (int)uVar1;
    piVar2[1] = (int)((ulong)uVar1 >> 0x10);
  }
  if (*param_1 == 0 && piVar2[1] == 0) {
    FUN_1000_0040();
    uVar3 = 0xe654;
    FUN_214c_17f7(0,0x1959,0x1000);
    FUN_214c_1755(uVar3,unaff_DS);
    FUN_1000_1448();
  }
  return;
}



void FUN_1000_1a1a(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 uVar4;
  undefined2 unaff_DS;
  undefined2 local_c;
  undefined2 local_8;
  undefined2 local_6;
  undefined2 local_4;
  
  if (param_1 == 1) {
    if (*(char *)0xb918 == '\0') {
      *(undefined1 *)((int)*(undefined4 *)0x8 + *(int *)0x78f1 * 0x4f + *(int *)0x78f3 + -0x50) =
           0x20;
    }
    else {
      *(undefined1 *)((int)*(undefined4 *)0x8 + *(int *)0x78f1 * 0x4f + *(int *)0x78f3 + -0x50) =
           0xef;
    }
  }
  uVar2 = *(undefined4 *)(param_1 * 4 + -0x54d9);
  local_c = (int)((ulong)uVar2 >> 0x10);
  iVar3 = (int)uVar2;
  while (iVar3 != 0 || local_c != 0) {
    uVar4 = FUN_1000_0479(iVar3,local_c);
    uVar2 = *(undefined4 *)(param_1 * 4 + 4);
    *(undefined1 *)((int)uVar2 + *(int *)(iVar3 + 5) * 0x4f + *(int *)(iVar3 + 7) + -0x50) = uVar4;
    puVar1 = (undefined4 *)(iVar3 + 0x16);
    local_c = (int)((ulong)*puVar1 >> 0x10);
    iVar3 = (int)*puVar1;
  }
  local_6 = 2;
  while( true ) {
    for (local_4 = 2; *(undefined1 *)(local_6 * 0x4f + local_4 + -0xc) = 0x20, local_4 != 0x4e;
        local_4 = local_4 + 1) {
    }
    if (local_6 == 0x16) break;
    local_6 = local_6 + 1;
  }
  uVar2 = *(undefined4 *)(param_1 * 4 + -0x5499);
  local_8 = (int)((ulong)uVar2 >> 0x10);
  iVar3 = (int)uVar2;
  while (iVar3 != 0 || local_8 != 0) {
    *(undefined1 *)(*(int *)(iVar3 + 0x1c) * 0x4f + *(int *)(iVar3 + 0x1e) + -0xc) =
         *(undefined1 *)(iVar3 + 1);
    puVar1 = (undefined4 *)(iVar3 + 0x32);
    local_8 = (int)((ulong)*puVar1 >> 0x10);
    iVar3 = (int)*puVar1;
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
  undefined2 local_4;
  
  local_6 = (int)((ulong)*(undefined4 *)0xb91e >> 0x10);
  local_8 = (int)*(undefined4 *)0xb91e;
  if (local_8 != 0 || local_6 != 0) {
    for (; *(int *)(local_8 + 0x16) != 0 || *(int *)(local_8 + 0x18) != 0;
        local_6 = (int)((ulong)*puVar1 >> 0x10)) {
      puVar1 = (undefined4 *)(local_8 + 0x16);
      local_8 = (int)*puVar1;
    }
    uVar2 = *(undefined4 *)0xabab;
    *(undefined2 *)(local_8 + 0x16) = (int)uVar2;
    *(undefined2 *)(local_8 + 0x18) = (int)((ulong)uVar2 >> 0x10);
    uVar2 = *(undefined4 *)0xb91e;
    *(undefined2 *)0xabab = (int)uVar2;
    *(undefined2 *)0xabad = (int)((ulong)uVar2 >> 0x10);
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_17f7(0,0x1b8e,0x1000);
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0;
  while( true ) {
    uVar2 = *(undefined4 *)(local_4 * 4 + -0x54d9);
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
      uVar2 = *(undefined4 *)(local_4 * 4 + -0x54d9);
      *(undefined2 *)0xabab = (int)uVar2;
      *(undefined2 *)0xabad = (int)((ulong)uVar2 >> 0x10);
    }
    uVar2 = *(undefined4 *)(local_4 * 4 + -0x5499);
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
      uVar2 = *(undefined4 *)(local_4 * 4 + -0x5499);
      *(undefined2 *)0xaba7 = (int)uVar2;
      *(undefined2 *)0xaba9 = (int)((ulong)uVar2 >> 0x10);
    }
    if (local_4 == 0xf) break;
    local_4 = local_4 + 1;
  }
  return;
}



undefined2 FUN_1000_1cd1(void)

{
  char *pcVar1;
  byte bVar3;
  uint uVar2;
  undefined2 unaff_DS;
  char local_8;
  char *local_7;
  uint local_5;
  
  pcVar1 = (char *)*(undefined4 *)0xb91e;
  bVar3 = (byte)((ulong)pcVar1 >> 8);
  if (*(int *)((int)*(undefined4 *)0xb922 + 1) == 10) {
    uVar2 = CONCAT11(bVar3,1);
  }
  else {
    uVar2 = (uint)bVar3 << 8;
  }
  local_8 = (char)uVar2;
  if (local_8 == '\0') {
    while (local_7 = (char *)pcVar1, local_5 = (uint)((ulong)pcVar1 >> 0x10),
          uVar2 = (uint)local_7 | local_5, uVar2 != 0) {
      if ((local_8 == '\0') && ((*pcVar1 != '\a' || (*(int *)(local_7 + 1) != 10)))) {
        local_8 = '\0';
      }
      else {
        local_8 = '\x01';
      }
      pcVar1 = *(char **)(local_7 + 0x16);
    }
  }
  return CONCAT11((char)(uVar2 >> 8),local_8);
}



void FUN_1000_1d47(byte *param_1)

{
  undefined2 uVar1;
  uint uVar2;
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
  int iVar3;
  int iVar4;
  undefined2 in_BX;
  undefined2 uVar5;
  byte *pbVar6;
  undefined2 uVar7;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar8;
  bool bVar9;
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
  
  iVar3 = (*(int *)0xb888 + 2) / 2 >> 0xf;
  local_16 = FUN_214c_0cc9();
  local_38 = param_1;
  iVar4 = *(int *)0xb888 + 1 + *(int *)0xb878 >> 0xf;
  local_14 = in_BX;
  local_12 = iVar3;
  uVar1 = FUN_214c_0cc9();
  uVar7 = (undefined2)((ulong)local_38 >> 0x10);
  iVar3 = *(int *)((byte *)local_38 + 8) + *(int *)((byte *)local_38 + 0xc) >> 0xf;
  FUN_214c_0cc9(uVar1,in_BX,iVar4);
  local_34 = FUN_214c_0cbb();
  iVar4 = (*(int *)0xb888 * *(int *)0xb874) / 10 + 8 >> 0xf;
  local_30 = iVar3;
  uVar1 = FUN_214c_0cc9();
  iVar3 = (*(int *)(*(int *)((byte *)local_38 + 2) * 0x2a + -0x5002) << 1) >> 0xf;
  FUN_214c_0cc9(uVar1,in_BX,iVar4);
  local_2e = FUN_214c_0cbb();
  uVar1 = (undefined2)((ulong)local_38 >> 0x10);
  iVar4 = *(int *)((byte *)local_38 + 8) + 1 + *(int *)((byte *)local_38 + 0x14) >> 0xf;
  local_2c = in_BX;
  local_2a = iVar3;
  uVar1 = FUN_214c_0cc9();
  iVar3 = (*(int *)0xb888 + -1) / 2 + *(int *)0xb888 >> 0xf;
  FUN_214c_0cc9(uVar1,in_BX,iVar4);
  local_28 = FUN_214c_0cbb();
  uVar1 = (undefined2)((ulong)local_38 >> 0x10);
  iVar4 = (*(int *)((byte *)local_38 + 0x10) + 1) * *(int *)((byte *)local_38 + 0xe) >> 0xf;
  local_24 = iVar3;
  FUN_214c_0cc9();
  local_22 = FUN_214c_0cbb();
  bVar8 = false;
  local_20 = in_BX;
  local_1e = iVar4;
  FUN_214c_0cc5();
  if (bVar8) {
    local_22 = 0x87;
    local_20 = 0;
    local_1e = 0xc00;
  }
  iVar4 = *(int *)0xb888 + -1 >> 0xf;
  FUN_214c_0cc9();
  FUN_214c_0cb5();
  FUN_214c_0ca3();
  local_22 = FUN_214c_0cbb();
  local_1e = iVar4;
  FUN_214c_0e79();
  uVar1 = FUN_214c_0cb5();
  iVar3 = local_2a;
  uVar1 = FUN_214c_0e79(uVar1,in_BX,iVar4);
  uVar5 = 0;
  uVar7 = 0x4000;
  FUN_214c_0cb5(uVar1,local_2c,iVar3);
  FUN_214c_0cb5();
  uVar1 = FUN_214c_0ca9();
  iVar3 = local_12;
  FUN_214c_0e79(uVar1,uVar5,uVar7);
  local_1c = FUN_214c_0ca3();
  bVar8 = false;
  bVar9 = true;
  local_1a = local_14;
  local_18 = iVar3;
  FUN_214c_0cc5();
  if (!bVar8 && !bVar9) {
    local_1c = 0x84;
    local_1a = 0;
    local_18 = 0x2000;
  }
  local_1c = FUN_214c_0f22();
  uVar1 = FUN_214c_0cd5();
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
  uVar2 = (uint)*local_38;
  puVar11 = local_58;
  uVar1 = unaff_SS;
  FUN_214c_08af(puVar11);
  FUN_214c_08be(CONCAT11(extraout_AH,0x47));
  FUN_214c_08be(CONCAT11(extraout_AH_00,0x48));
  FUN_214c_08be(CONCAT11(extraout_AH_01,0x9c));
  FUN_214c_08be(CONCAT11(extraout_AH_02,0x4d));
  FUN_214c_08be(CONCAT11(extraout_AH_03,0x4e));
  FUN_214c_08be(CONCAT11(extraout_AH_04,0x9e));
  FUN_214c_08be(CONCAT11(extraout_AH_05,0x73));
  FUN_214c_0933(puVar11,uVar1,uVar2);
  if (!(bool)uVar10) {
    uVar1 = (undefined2)((ulong)local_38 >> 0x10);
    iVar3 = *(int *)((byte *)local_38 + 6) + 10;
    uVar10 = iVar3 == 0;
    *(int *)((byte *)local_38 + 6) = iVar3;
  }
  uVar2 = (uint)*local_38;
  puVar11 = local_58;
  uVar1 = unaff_SS;
  FUN_214c_08af(puVar11);
  FUN_214c_08be(CONCAT11(extraout_AH_06,0x46));
  FUN_214c_08be(CONCAT11(extraout_AH_07,0x56));
  FUN_214c_0933(puVar11,uVar1,uVar2);
  if (!(bool)uVar10) {
    ((byte *)local_38 + 6)[0] = 0x14;
    ((byte *)local_38 + 6)[1] = 0;
  }
  uVar1 = CONCAT11(extraout_AH_08,*local_38);
  puVar11 = local_58;
  FUN_214c_08af(puVar11);
  FUN_214c_08be(CONCAT11(extraout_AH_09,0x44));
  FUN_214c_08be(CONCAT11(extraout_AH_10,0x92));
  FUN_214c_0933(puVar11,unaff_SS,uVar1);
  pbVar6 = (byte *)local_38;
  uVar1 = (undefined2)((ulong)local_38 >> 0x10);
  if (!(bool)uVar10) {
    *(int *)(pbVar6 + 6) = *(int *)(pbVar6 + 6) / 2 + *(int *)(pbVar6 + 6);
  }
  if (*local_38 == 0x45) {
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
  
  pcVar1 = (char *)*(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
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



void FUN_1000_2138(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined2 unaff_DS;
  
  if ((bool)((byte)param_2 & 1)) {
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    *(undefined1 *)((int)uVar1 + param_2 * 0x4f + param_1 + -0x50) = 0x20;
  }
  else {
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    *(undefined1 *)((int)uVar1 + param_2 * 0x4f + param_1 + -0x50) = 0x20;
  }
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  *(undefined1 *)((int)uVar1 + param_2 * 0x4f + param_1 + -0x50) = 0x20;
  return;
}



uint FUN_1000_21b0(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  undefined2 unaff_DS;
  
  if ((!(bool)((byte)param_2 & 1)) || ((bool)((byte)param_1 & 1))) {
    uVar2 = (uint)((byte)param_1 >> 1);
    if ((bool)((byte)param_1 & 1)) {
      uVar2 = param_2 * 0x4f;
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      *(undefined1 *)((int)uVar1 + uVar2 + param_1 + -0x50) = 0xb3;
    }
  }
  else {
    uVar2 = param_2 * 0x4f;
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    *(undefined1 *)((int)uVar1 + uVar2 + param_1 + -0x50) = 0xc4;
  }
  return uVar2;
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
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  *(undefined1 *)
   ((int)uVar1 + *(int *)((int)_local_6 + 5) * 0x4f + *(int *)((int)_local_6 + 7) + -0x50) = 0x20;
  FUN_1000_14ab(*(int *)0xe52d * 4 + -0x54d9,unaff_DS,&local_6,unaff_SS);
  FUN_1000_063c(local_6,uStack_4);
  return;
}



void __cdecl16near FUN_1000_227b(void)

{
  uint uVar1;
  undefined1 extraout_AH;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar2;
  undefined1 *puVar3;
  undefined1 local_22 [32];
  
  uVar2 = &stack0x0000 == (undefined1 *)0x22;
  uVar1 = (uint)*(byte *)((int)*(undefined4 *)0xb922 + 1);
  puVar3 = local_22;
  FUN_214c_08af(puVar3);
  FUN_214c_08df(CONCAT11(extraout_AH,0xd),CONCAT11(extraout_AH,9));
  FUN_214c_0933(puVar3,unaff_SS,uVar1);
  if ((bool)uVar2) {
    if (10 < *(int *)0xb882) {
      *(undefined2 *)0xb882 = 10;
    }
  }
  else if (0xd < *(int *)0xb882) {
    *(undefined2 *)0xb882 = 0xd;
  }
  return;
}



void FUN_1000_22c8(int param_1,int param_2)

{
  int iVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar2;
  undefined1 local_102 [256];
  
  if ((param_2 < 1) || (0x23 < param_2)) {
    if (param_2 == 0x61) {
      if (param_1 == 10) {
        FUN_1000_016a(0x45);
      }
      else {
        FUN_1000_016a(param_1 + 0x87);
      }
    }
    else if (param_2 == 100) {
      if (param_1 == 0) {
        FUN_1000_016a(0xce);
      }
      else if (param_1 == 10) {
        FUN_1000_016a(0xcf);
      }
      else if (param_1 == 0x23) {
        FUN_1000_016a(0xd0);
      }
    }
    else {
      puVar2 = local_102;
      FUN_214c_07ae(param_2);
      iVar1 = FUN_214c_074c(0xb9ed,unaff_DS,puVar2,unaff_SS);
      FUN_1000_016a(iVar1 + 0x7e + param_1);
    }
  }
  else {
    FUN_1000_016a(param_1 + 0x7e);
  }
  return;
}



void FUN_1000_2363(int *param_1,int *param_2,int *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  do {
    do {
      iVar2 = FUN_214c_1162(0x15);
      *param_3 = iVar2 + 2;
      iVar2 = FUN_214c_1162(0x4d);
      *param_2 = iVar2 + 2;
      uVar1 = *(undefined4 *)(*param_1 * 4 + 4);
    } while (*(char *)((int)uVar1 + *param_3 * 0x4f + *param_2 + -0x50) != ' ');
  } while (*(char *)(*param_3 * 0x4f + *param_2 + -0xc) != ' ');
  return;
}



void FUN_1000_23da(int *param_1,uint *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  long lVar3;
  uint uVar4;
  undefined2 uVar5;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 in_DX;
  int iVar6;
  int iVar7;
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
          FUN_214c_1178();
          local_8 = FUN_214c_0ca9();
          local_6 = in_BX;
          local_4 = in_DX;
          local_8 = FUN_214c_0cbb();
          local_6 = in_BX;
          local_4 = in_DX;
          FUN_214c_0cd5();
          FUN_214c_1162(5);
          iVar6 = 0;
          uVar4 = FUN_214c_02dc();
          uVar1 = *(uint *)0xb86c;
          iVar7 = ((int)uVar1 >> 0xf) + iVar6 + (uint)CARRY2(uVar1,uVar4);
          *param_2 = uVar1 + uVar4;
          FUN_214c_1178();
          local_8 = FUN_214c_0ca9();
          local_6 = iVar6;
          local_4 = iVar7;
          local_8 = FUN_214c_0cbb();
          local_6 = iVar6;
          local_4 = iVar7;
          FUN_214c_0cd5();
          FUN_214c_1162(5);
          in_BX = 0;
          iVar6 = FUN_214c_02dc();
          *param_1 = *(int *)0xb86e + iVar6;
          in_DX = (undefined2)((ulong)*param_2 * 0x4f >> 0x10);
          uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        } while (*(char *)((int)uVar2 + (int)((ulong)*param_2 * 0x4f) + *param_1 + -0x50) != ' ');
        lVar3 = (ulong)*param_2 * 0x4f;
        in_DX = (undefined2)((ulong)lVar3 >> 0x10);
        uVar8 = *(char *)((int)lVar3 + *param_1 + -0xc) == ' ';
      } while (!(bool)uVar8);
      uVar5 = CONCAT11((char)((ulong)lVar3 >> 8),(char)*param_2);
      puVar9 = local_28;
      uVar10 = unaff_SS;
      FUN_214c_08af(puVar9);
      FUN_214c_08df(CONCAT11(extraout_AH,0x16),CONCAT11(extraout_AH,2));
      FUN_214c_0933(puVar9,uVar10,uVar5);
      in_DX = extraout_DX;
    } while ((bool)uVar8);
    uVar5 = CONCAT11(extraout_AH_00,(char)*param_1);
    puVar9 = local_48;
    uVar10 = unaff_SS;
    FUN_214c_08af(puVar9);
    FUN_214c_08df(CONCAT11(extraout_AH_01,0x4e),CONCAT11(extraout_AH_01,2));
    FUN_214c_0933(puVar9,uVar10,uVar5);
    in_DX = extraout_DX_00;
  } while ((bool)uVar8);
  return;
}



void FUN_1000_2574(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar4 = (undefined2)((ulong)*param_2 >> 0x10);
  iVar2 = (int)*param_2;
  FUN_1000_2363(&param_1,unaff_SS,iVar2 + 7,uVar4,iVar2 + 5,uVar4);
  uVar3 = FUN_1000_0479(*(undefined2 *)param_2,*(undefined2 *)((int)(undefined4 *)param_2 + 2));
  uVar1 = *(undefined4 *)(param_1 * 4 + 4);
  *(undefined1 *)((int)uVar1 + *(int *)(iVar2 + 5) * 0x4f + *(int *)(iVar2 + 7) + -0x50) = uVar3;
  uVar1 = *(undefined4 *)(param_1 * 4 + -0x54d9);
  *(undefined2 *)(iVar2 + 0x16) = (int)uVar1;
  *(undefined2 *)(iVar2 + 0x18) = (int)((ulong)uVar1 >> 0x10);
  uVar1 = *param_2;
  *(undefined2 *)(param_1 * 4 + -0x54d9) = (int)uVar1;
  *(undefined2 *)(param_1 * 4 + -0x54d7) = (int)((ulong)uVar1 >> 0x10);
  return;
}



int FUN_1000_260c(int param_1,char param_2)

{
  int local_4;
  
  if (((param_2 == '\x02') || (param_2 == '\x03')) || (param_2 == '\x04')) {
    local_4 = 1;
  }
  else if (((param_2 == '\x05') || (param_2 == '\x01')) || (param_2 == '\b')) {
    local_4 = 2;
  }
  else if (param_2 == '\a') {
    if ((((param_1 == 1) || (param_1 == 2)) || (param_1 == 0xb)) ||
       ((param_1 == 0xc || (param_1 == 0xd)))) {
      local_4 = 2;
    }
    else if (((param_1 < 3) || (7 < param_1)) &&
            ((param_1 != 9 && ((param_1 != 0xe && (param_1 != 0xf)))))) {
      if ((param_1 == 8) || (param_1 == 10)) {
        local_4 = 5;
      }
    }
    else {
      local_4 = 4;
    }
  }
  else if (param_2 == '\x06') {
    if ((param_1 < 1) || (6 < param_1)) {
      if ((6 < param_1) && (param_1 < 0xc)) {
        local_4 = 2;
      }
    }
    else {
      local_4 = param_1 / 2 + 4;
    }
  }
  return local_4;
}



void FUN_1000_26cf(undefined4 *param_1,int param_2,char param_3)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined1 extraout_AH;
  byte bVar8;
  uint uVar6;
  uint uVar7;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 in_BX;
  char *pcVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar13;
  undefined1 uVar14;
  bool bVar15;
  undefined1 uVar16;
  undefined1 *puVar17;
  undefined1 local_2e [32];
  char *local_e;
  int local_a;
  int local_6;
  int local_4;
  
  FUN_1000_05d6((undefined4 *)param_1,(int)((ulong)param_1 >> 0x10));
  local_4 = FUN_214c_1162(100);
  local_4 = local_4 + 1;
  local_a = 0;
  local_6 = 0;
  local_e = (char *)*param_1;
  uVar10 = (undefined2)((ulong)local_e >> 0x10);
  pcVar9 = (char *)local_e;
  *local_e = param_3;
  pcVar9[0x13] = '\0';
  pcVar9[0x15] = '\0';
  (pcVar9 + 3)[0] = '\x01';
  (pcVar9 + 3)[1] = '\0';
  (pcVar9 + 9)[0] = '\0';
  (pcVar9 + 9)[1] = '\0';
  uVar5 = 0;
  if (param_3 == '\0') {
    iVar3 = FUN_214c_1162(5);
    iVar4 = FUN_214c_1162(param_2 + 1);
    uVar5 = param_2 * 7 + iVar4 * 0x19 + iVar3;
    *(uint *)((char *)local_e + 9) = uVar5;
    goto LAB_1000_2d0e;
  }
  if ((((param_3 != '\x02') && (param_3 != '\x03')) && (param_3 != '\x06')) &&
     (((param_3 != '\a' && (param_3 != '\x05')) && (param_3 != '\b')))) {
    if (param_3 != '\x04') goto LAB_1000_2d0e;
    do {
      local_6 = 0;
      local_a = 0;
      do {
        local_a = local_a + 1;
        local_6 = *(int *)(local_a * 2 + -0x6453) + local_6;
      } while (local_6 < local_4);
      *(int *)((char *)local_e + 1) = local_a;
      local_4 = FUN_214c_1162(100);
      local_4 = local_4 + 1;
      local_6 = 0;
      pcVar9 = (char *)local_e;
      uVar10 = (undefined2)((ulong)local_e >> 0x10);
    } while ((*(int *)0xabaf != 0 || *(int *)0xabb1 != 0) && (*(int *)(pcVar9 + 1) == 6));
    *(int *)(pcVar9 + 1) = local_a;
    uVar5 = *(uint *)(pcVar9 + 1);
    if ((uVar5 == 7) || (uVar5 == 9)) {
      iVar3 = FUN_214c_1162(2);
      *(int *)((char *)local_e + 9) = (param_2 + 3) / 6 + iVar3;
      FUN_214c_1178();
      bVar13 = false;
      bVar15 = true;
      uVar5 = FUN_214c_0cc5();
      if (!bVar13 && !bVar15) {
        uVar10 = (undefined2)((ulong)local_e >> 0x10);
        uVar5 = -*(int *)((char *)local_e + 9);
        *(uint *)((char *)local_e + 9) = uVar5;
      }
    }
    else if (uVar5 == 4) {
      iVar3 = FUN_214c_1162(2);
      *(int *)((char *)local_e + 9) = (param_2 + 2) / 5 + iVar3;
      FUN_214c_1178();
      bVar13 = false;
      bVar15 = true;
      uVar5 = FUN_214c_0cc5();
      if (!bVar13 && !bVar15) {
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
      iVar3 = FUN_214c_1162(4);
      uVar5 = iVar3 + 4;
      *(uint *)((char *)local_e + 9) = uVar5;
    }
    else {
      uVar14 = uVar5 < 0xb;
      if (uVar5 == 0xb) {
        FUN_214c_1178();
        uVar5 = FUN_214c_0cc5();
        uVar10 = (undefined2)((ulong)local_e >> 0x10);
        if ((bool)uVar14) {
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
        uVar2 = *param_1;
        *(undefined2 *)0xabaf = (int)uVar2;
        *(undefined2 *)0xabb1 = (int)((ulong)uVar2 >> 0x10);
        iVar3 = FUN_214c_1162(0x28);
        uVar5 = iVar3 + 0x28;
        *(uint *)((char *)local_e + 9) = uVar5;
      }
      else if (uVar5 == 0xf) {
        (pcVar9 + 9)[0] = '\x01';
        (pcVar9 + 9)[1] = '\0';
      }
      else if (uVar5 == 0x12) {
        iVar3 = FUN_214c_1162(0x28);
        iVar4 = FUN_214c_1162(0x28);
        uVar5 = iVar4 + 0x14 + iVar3;
        *(uint *)((char *)local_e + 9) = uVar5;
      }
      else if (uVar5 == 0x13) {
        iVar3 = FUN_214c_1162(4);
        uVar5 = iVar3 + 4;
        *(uint *)((char *)local_e + 9) = uVar5;
      }
      else {
        uVar5 = 0;
        (pcVar9 + 9)[0] = '\0';
        (pcVar9 + 9)[1] = '\0';
      }
    }
    uVar14 = (undefined1)(uVar5 >> 8);
    uVar10 = (undefined2)((ulong)local_e >> 0x10);
    iVar3 = *(int *)((char *)local_e + 9);
    uVar16 = iVar3 == 0;
    if (iVar3 < 0) {
LAB_1000_2d05:
      uVar5 = CONCAT11(uVar14,1);
    }
    else {
      uVar10 = CONCAT11(uVar14,((char *)local_e)[1]);
      puVar17 = local_2e;
      FUN_214c_08af(puVar17);
      FUN_214c_08be(CONCAT11(extraout_AH_00,5));
      FUN_214c_08be(CONCAT11(extraout_AH_01,0x13));
      uVar5 = FUN_214c_0933(puVar17,unaff_SS,uVar10);
      uVar14 = (undefined1)(uVar5 >> 8);
      if (!(bool)uVar16) goto LAB_1000_2d05;
      uVar5 = uVar5 & 0xff00;
    }
    ((char *)local_e)[0x14] = (char)uVar5;
    goto LAB_1000_2d0e;
  }
  do {
    iVar3 = local_a + 1;
    local_6 = *(int *)(param_3 * 0x30 + iVar3 * 2 + -0x6513) + local_6;
    local_a = iVar3;
  } while (local_6 < local_4);
  *(int *)(pcVar9 + 1) = iVar3;
  if (((param_3 == '\a') && (*(int *)(pcVar9 + 1) == 7)) &&
     (iVar3 = FUN_214c_1162(0x14), iVar3 == 0)) {
    ((char *)local_e + 1)[0] = '\x0f';
    ((char *)local_e + 1)[1] = '\0';
  }
  if (param_3 == '\x06') {
    iVar3 = param_2 + 3 >> 0xf;
    FUN_214c_0cc9();
    uVar14 = 0;
    uVar10 = FUN_214c_0cbb();
    FUN_214c_1178(uVar10,in_BX,iVar3);
    iVar3 = FUN_214c_0cc5();
    if (!(bool)uVar14) goto LAB_1000_281a;
LAB_1000_284b:
    iVar3 = FUN_214c_1162(3);
    *(int *)((char *)local_e + 9) = param_2 / 5 + iVar3;
    FUN_214c_1178();
    bVar13 = false;
    bVar15 = true;
    iVar3 = FUN_214c_0cc5();
    if (!bVar13 && !bVar15) {
      uVar10 = (undefined2)((ulong)local_e >> 0x10);
      iVar3 = -*(int *)((char *)local_e + 9);
      *(int *)((char *)local_e + 9) = iVar3;
    }
  }
  else {
LAB_1000_281a:
    if (param_3 == '\a') {
      iVar3 = param_2 + 2 >> 0xf;
      FUN_214c_0cc9();
      uVar14 = 0;
      uVar10 = FUN_214c_0cbb();
      FUN_214c_1178(uVar10,in_BX,iVar3);
      iVar3 = FUN_214c_0cc5();
      if ((bool)uVar14) goto LAB_1000_284b;
    }
  }
  uVar14 = param_3 == '\x06';
  if ((bool)uVar14) {
    uVar5 = (uint)(byte)((char *)local_e)[1];
    puVar17 = local_2e;
    FUN_214c_08af(puVar17);
    FUN_214c_08df(CONCAT11(extraout_AH,0xb),CONCAT11(extraout_AH,9));
    iVar3 = FUN_214c_0933(puVar17,unaff_SS,uVar5);
    if (!(bool)uVar14) {
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
  if (param_3 == '\x05') {
    iVar3 = FUN_214c_1162(*(int *)(local_a * 4 + -0x6245) / 2);
    iVar3 = *(int *)(local_a * 4 + -0x6245) / 2 + iVar3 + 1;
    *(int *)((char *)local_e + 9) = iVar3;
  }
  if ((param_3 == '\a') && (*(int *)((char *)local_e + 1) == 0xc)) {
    *(int *)0xe533 = *(int *)0xe533 + 1;
    iVar3 = FUN_214c_1162(10);
    uVar10 = (undefined2)((ulong)local_e >> 0x10);
    *(int *)((char *)local_e + 3) = iVar3 + 5;
    iVar3 = *(int *)0xe533;
    *(int *)((char *)local_e + 0x11) = iVar3;
  }
  uVar10 = (undefined2)((ulong)local_e >> 0x10);
  pcVar9 = (char *)local_e;
  bVar8 = (byte)((uint)iVar3 >> 8);
  if (*(int *)(pcVar9 + 9) < 0) {
    uVar5 = CONCAT11(bVar8,1);
  }
  else {
    uVar5 = (uint)bVar8 << 8;
  }
  pcVar9[0x14] = (char)uVar5;
  if (param_3 == '\b') {
    if (*(int *)(pcVar9 + 1) == 4) {
      iVar3 = FUN_214c_1162(0xf);
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
      uVar5 = FUN_214c_1162(200);
      uVar10 = (undefined2)((ulong)local_e >> 0x10);
      pcVar9 = (char *)local_e;
      uVar2 = *(undefined4 *)(pcVar9 + 0xd);
      uVar6 = (uint)uVar2;
      uVar7 = uVar6 + 0x3c;
      *(uint *)(pcVar9 + 0xd) = uVar7 + uVar5;
      *(uint *)(pcVar9 + 0xf) =
           (int)((ulong)uVar2 >> 0x10) + (uint)(0xffc3 < uVar6) + (uint)CARRY2(uVar7,uVar5);
      iVar3 = FUN_214c_1162(10);
      if (iVar3 == 0) {
        uVar10 = (undefined2)((ulong)local_e >> 0x10);
        pcVar9 = (char *)local_e;
        uVar2 = *(undefined4 *)(pcVar9 + 0xd);
        uVar5 = (uint)uVar2;
        *(uint *)(pcVar9 + 0xd) = uVar5 + 100;
        *(uint *)(pcVar9 + 0xf) = (int)((ulong)uVar2 >> 0x10) + (uint)(0xff9b < uVar5);
      }
      FUN_214c_1178();
      bVar13 = false;
      bVar15 = true;
      FUN_214c_0cc5();
    } while (bVar13 || bVar15);
    iVar3 = FUN_214c_1162(0x14);
    if (iVar3 == 0) {
      uVar11 = (undefined2)((ulong)*(undefined4 *)((char *)local_e + 0xd) >> 0x10);
      uVar10 = FUN_214c_02dc();
      uVar12 = (undefined2)((ulong)local_e >> 0x10);
      *(undefined2 *)((char *)local_e + 0xd) = uVar10;
      *(undefined2 *)((char *)local_e + 0xf) = uVar11;
    }
    iVar3 = FUN_214c_1162(0x32);
    if (iVar3 == 0) {
      uVar11 = (undefined2)((ulong)*(undefined4 *)((char *)local_e + 0xd) >> 0x10);
      uVar10 = FUN_214c_02dc();
      uVar12 = (undefined2)((ulong)local_e >> 0x10);
      *(undefined2 *)((char *)local_e + 0xd) = uVar10;
      *(undefined2 *)((char *)local_e + 0xf) = uVar11;
    }
    iVar3 = FUN_214c_1162(100);
    if (iVar3 == 0) {
      uVar11 = (undefined2)((ulong)*(undefined4 *)((char *)local_e + 0xd) >> 0x10);
      uVar10 = FUN_214c_02dc();
      uVar12 = (undefined2)((ulong)local_e >> 0x10);
      *(undefined2 *)((char *)local_e + 0xd) = uVar10;
      *(undefined2 *)((char *)local_e + 0xf) = uVar11;
    }
    iVar3 = FUN_214c_1162(500);
    if (iVar3 == 0) {
      uVar11 = (undefined2)((ulong)*(undefined4 *)((char *)local_e + 0xd) >> 0x10);
      uVar10 = FUN_214c_02dc();
      uVar12 = (undefined2)((ulong)local_e >> 0x10);
      *(undefined2 *)((char *)local_e + 0xd) = uVar10;
      *(undefined2 *)((char *)local_e + 0xf) = uVar11;
    }
    iVar3 = FUN_214c_1162(10);
    uVar5 = iVar3 + 1;
    uVar10 = (undefined2)((ulong)local_e >> 0x10);
    *(uint *)((char *)local_e + 0x11) = uVar5;
    ((char *)local_e)[0x14] = '\x01';
  }
LAB_1000_2d0e:
  uVar10 = FUN_1000_260c(*(undefined2 *)((char *)local_e + 1),CONCAT11((char)(uVar5 >> 8),param_3));
  *(undefined2 *)((char *)local_e + 0xb) = uVar10;
  return;
}



void FUN_1000_2d29(undefined4 *param_1,int param_2)

{
  char *pcVar1;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  int iVar2;
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
  
  FUN_1000_0556((undefined4 *)param_1,(int)((ulong)param_1 >> 0x10));
  local_a = (char *)*param_1;
  uVar4 = (undefined2)((ulong)local_a >> 0x10);
  pcVar3 = (char *)local_a;
  *local_a = *(char *)(param_2 * 0x2a + -0x5007);
  pcVar3[1] = *local_a;
  *(int *)(pcVar3 + 2) = param_2;
  *(int *)(pcVar3 + 4) = param_2;
  uVar6 = pcVar3 + 0x1e == (char *)0x0;
  FUN_1000_2363(0xe52d,unaff_DS,pcVar3 + 0x1e,uVar4,pcVar3 + 0x1c,uVar4);
  uVar5 = (undefined2)((ulong)local_a >> 0x10);
  pcVar3 = (char *)local_a;
  *(undefined2 *)(pcVar3 + 8) = *(undefined2 *)(param_2 * 0x2a + -0x5004);
  *(undefined2 *)(pcVar3 + 6) = *(undefined2 *)(param_2 * 0x2a + -0x5006);
  *(undefined2 *)(pcVar3 + 10) = *(undefined2 *)(param_2 * 0x2a + -0x5002);
  *(undefined2 *)(pcVar3 + 0xc) = *(undefined2 *)(param_2 * 0x2a + -0x5000);
  *(undefined2 *)(pcVar3 + 0xe) = *(undefined2 *)(param_2 * 0x2a + -0x4ffe);
  *(undefined2 *)(pcVar3 + 0x10) = *(undefined2 *)(param_2 * 0x2a + -0x4ffc);
  uVar4 = *(undefined2 *)(param_2 * 0x2a + -0x4ff8);
  *(undefined2 *)(pcVar3 + 0x14) = uVar4;
  uVar5 = CONCAT11((char)((uint)uVar4 >> 8),*local_a);
  puVar7 = local_2a;
  uVar4 = unaff_SS;
  FUN_214c_08af(puVar7);
  FUN_214c_08be(CONCAT11(extraout_AH,0x42));
  FUN_214c_08be(CONCAT11(extraout_AH_00,0x9e));
  FUN_214c_0933(puVar7,uVar4,uVar5);
  pcVar3 = (char *)local_a;
  uVar4 = (undefined2)((ulong)local_a >> 0x10);
  if ((!(bool)uVar6) &&
     (*(int *)(pcVar3 + 8) + *(int *)(pcVar3 + 0x14) < *(int *)0xb888 + *(int *)0xb880 + 5)) {
    *(int *)(pcVar3 + 8) = *(int *)(pcVar3 + 8) + 1;
    *(int *)(pcVar3 + 0x14) = (*(int *)0xb888 + *(int *)0xb880 + 6) - *(int *)(pcVar3 + 8);
  }
  *(undefined2 *)(pcVar3 + 0x12) = *(undefined2 *)(param_2 * 0x2a + -0x4ffa);
  *(undefined2 *)(pcVar3 + 0x16) = *(undefined2 *)(param_2 * 0x2a + -0x4ff6);
  *(undefined2 *)(pcVar3 + 0x18) = *(undefined2 *)(param_2 * 0x2a + -0x4ff4);
  (pcVar3 + 0x20)[0] = '\0';
  (pcVar3 + 0x20)[1] = '\0';
  pcVar3[0x22] = '\0';
  pcVar3[0x23] = '\0';
  pcVar3[0x24] = '\0';
  pcVar3[0x25] = '\0';
  pcVar3[0x26] = '\0';
  pcVar3[0x28] = *(char *)(param_2 * 0x2a + -0x4fef);
  *(undefined2 *)(pcVar3 + 0x1a) = *(undefined2 *)(param_2 * 0x2a + -0x4ff2);
  pcVar3[0x27] = *(char *)(param_2 * 0x2a + -0x4ff0);
  pcVar3[0x29] = *(char *)(param_2 * 0x2a + -0x4fee);
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
    iVar2 = FUN_214c_1162(*(undefined2 *)(pcVar3 + 0x16));
    if (iVar2 == 0) {
      FUN_1000_26cf(local_6,unaff_SS,*(undefined2 *)0xe52d,((char *)local_a)[0x18]);
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



void __cdecl16near FUN_1000_2fe0(void)

{
  int iVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar2;
  undefined2 uVar3;
  undefined1 local_127 [256];
  int local_27;
  int local_25;
  int local_23;
  int local_21;
  undefined1 local_1f [29];
  
  local_25 = 1;
  while( true ) {
    local_27 = FUN_214c_1162(6);
    local_27 = local_27 + 4;
    local_1f[0] = 0;
    local_21 = local_27;
    if (0 < local_27) {
      local_23 = 1;
      while( true ) {
        puVar2 = local_127;
        uVar3 = unaff_SS;
        FUN_214c_0693(local_1f,unaff_SS);
        iVar1 = FUN_214c_1162(0x14);
        FUN_214c_0720((iVar1 + 1) * 4 + -0x469e,unaff_DS);
        FUN_214c_06ad(0x1c,local_1f,unaff_SS,puVar2,uVar3);
        if (local_23 == local_27) break;
        local_23 = local_23 + 1;
      }
    }
    FUN_214c_06ad(0x1c,local_25 * 0x1d + -0x610e,unaff_DS,local_1f,unaff_SS);
    if (local_25 == 0x18) break;
    local_25 = local_25 + 1;
  }
  return;
}



void FUN_1000_3086(int param_1,int param_2)

{
  undefined2 unaff_SS;
  undefined2 local_6;
  undefined2 local_4;
  
  if (0 < param_2) {
    local_6 = 1;
    while( true ) {
      local_4 = FUN_214c_1162(param_2);
      while (local_4 = local_4 + 1, *(int *)(param_1 + local_4 * 2 + -0x32) != 0) {
        local_4 = local_4 % param_2;
      }
      *(int *)(param_1 + local_4 * 2 + -0x32) = local_6;
      if (local_6 == param_2) break;
      local_6 = local_6 + 1;
    }
  }
  return;
}



void __cdecl16near FUN_1000_30ec(void)

{
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_34 [25];
  
  local_34[0] = 1;
  while (local_34[local_34[0]] = 0, local_34[0] != 0x18) {
    local_34[0] = local_34[0] + 1;
  }
  FUN_1000_3086(&stack0xfffe,0x18);
  local_34[0] = 1;
  while( true ) {
    FUN_214c_06ad(0xf,local_34[0] * 0x10 + -0x5cc9,unaff_DS,local_34[local_34[0]] * 0x10 + -0x5e49,
                  unaff_DS);
    if (local_34[0] == 0x18) break;
    local_34[0] = local_34[0] + 1;
  }
  local_34[0] = 1;
  while (local_34[local_34[0]] = 0, local_34[0] != 0x13) {
    local_34[0] = local_34[0] + 1;
  }
  FUN_1000_3086(&stack0xfffe,0x13);
  local_34[0] = 1;
  while( true ) {
    FUN_214c_06ad(0xf,local_34[0] * 0x10 + -0x5a19,unaff_DS,local_34[local_34[0]] * 0x10 + -0x5b49,
                  unaff_DS);
    if (local_34[0] == 0x13) break;
    local_34[0] = local_34[0] + 1;
  }
  local_34[0] = 1;
  while (local_34[local_34[0]] = 0, local_34[0] != 0x16) {
    local_34[0] = local_34[0] + 1;
  }
  FUN_1000_3086(&stack0xfffe,0x16);
  local_34[0] = 1;
  while( true ) {
    FUN_214c_06ad(0xf,local_34[0] * 0x10 + -0x5789,unaff_DS,local_34[local_34[0]] * 0x10 + -0x58e9,
                  unaff_DS);
    if (local_34[0] == 0x16) break;
    local_34[0] = local_34[0] + 1;
  }
  local_34[0] = 1;
  while (local_34[local_34[0]] = 0, local_34[0] != 10) {
    local_34[0] = local_34[0] + 1;
  }
  FUN_1000_3086(&stack0xfffe,10);
  local_34[0] = 1;
  while( true ) {
    FUN_214c_06ad(0xf,local_34[0] * 0x10 + -0x5589,unaff_DS,local_34[local_34[0]] * 0x10 + -0x5629,
                  unaff_DS);
    if (local_34[0] == 10) break;
    local_34[0] = local_34[0] + 1;
  }
  return;
}



void __cdecl16near FUN_1000_325e(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  int iVar3;
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
  int local_6;
  int local_4;
  
  local_6 = FUN_214c_1162(3);
  local_6 = local_6 + 10;
  FUN_1000_2d29(local_a,unaff_SS,0x22);
  local_c = local_a._2_2_;
  local_e = local_a._0_2_;
  do {
    do {
      local_4 = FUN_214c_1162(0x23);
      local_4 = local_4 + 1;
      uVar6 = *(char *)(local_4 * 0x2a + -0x4fee) == '\0';
    } while (!(bool)uVar6);
    uVar2 = CONCAT11((char)((uint)(local_4 * 0x2a) >> 8),*(undefined1 *)(local_4 * 0x2a + -0x5007));
    puVar4 = local_2e;
    uVar5 = unaff_SS;
    FUN_214c_08af(puVar4);
    FUN_214c_08be(CONCAT11(extraout_AH,0x61));
    FUN_214c_08be(CONCAT11(extraout_AH_00,0x45));
    FUN_214c_08be(CONCAT11(extraout_AH_01,0x48));
    FUN_214c_0933(puVar4,uVar5,uVar2);
  } while (!(bool)uVar6);
  *(undefined1 *)(local_e + 1) = *(undefined1 *)(local_4 * 0x2a + -0x5007);
  *(int *)(local_e + 4) = local_4;
  if (*(int *)0xabaf == 0 && *(int *)0xabb1 == 0) {
    FUN_1000_05d6(local_e + 0x2e,local_c);
    local_12 = (undefined1 *)*(undefined4 *)(local_e + 0x2e);
    *local_12 = 4;
    *(undefined2 *)((undefined1 *)local_12 + 1) = 6;
    iVar3 = FUN_214c_1162(0x32);
    uVar5 = (undefined2)((ulong)local_12 >> 0x10);
    puVar4 = (undefined1 *)local_12;
    *(int *)(puVar4 + 9) = iVar3 + 0x32;
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
  *(undefined2 *)(local_6 * 4 + -0x5499) = local_a._0_2_;
  *(undefined2 *)(local_6 * 4 + -0x5497) = local_a._2_2_;
  *(undefined2 *)(local_6 * 2 + 0x797d) = 1;
  return;
}



void __cdecl16near FUN_1000_33a1(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_6 [4];
  
  FUN_1000_2d29(local_6,unaff_SS,0x23);
  uVar4 = local_6._2_2_;
  iVar2 = local_6._0_2_;
  FUN_1000_05d6(iVar2 + 0x2e,uVar4);
  puVar1 = (undefined1 *)*(undefined4 *)(iVar2 + 0x2e);
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



void __cdecl16near FUN_1000_3408(void)

{
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_6 [4];
  
  FUN_1000_2d29(local_6,unaff_SS,0x1f);
  *(undefined2 *)0xab9f = local_6._0_2_;
  *(undefined2 *)0xaba1 = local_6._2_2_;
  *(undefined2 *)0x7999 = 1;
  return;
}



void __cdecl16near FUN_1000_3442(void)

{
  int iVar1;
  int iVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_6 [4];
  
  iVar1 = FUN_214c_1162(2);
  FUN_1000_2d29(local_6,unaff_SS,0x1d);
  iVar2 = (iVar1 + 8) * 4;
  *(undefined2 *)(iVar2 + -0x5499) = local_6._0_2_;
  *(undefined2 *)(iVar2 + -0x5497) = local_6._2_2_;
  *(undefined2 *)((iVar1 + 8) * 2 + 0x797d) = 1;
  return;
}



void __cdecl16near FUN_1000_3486(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_6 [4];
  
  iVar2 = FUN_214c_1162(2);
  iVar2 = iVar2 + 0xc;
  FUN_1000_2d29(local_6,unaff_SS,0x1e);
  uVar1 = *(undefined4 *)(iVar2 * 4 + -0x5499);
  uVar4 = local_6._2_2_;
  iVar3 = local_6._0_2_;
  *(undefined2 *)(iVar3 + 0x32) = (int)uVar1;
  *(undefined2 *)(iVar3 + 0x34) = (int)((ulong)uVar1 >> 0x10);
  *(int *)(iVar2 * 4 + -0x5499) = iVar3;
  *(undefined2 *)(iVar2 * 4 + -0x5497) = uVar4;
  *(int *)(iVar2 * 2 + 0x797d) = *(int *)(iVar2 * 2 + 0x797d) + 1;
  return;
}



void __cdecl16near FUN_1000_34ea(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_6 [4];
  
  FUN_1000_2d29(local_6,unaff_SS,0x20);
  uVar1 = *(undefined4 *)0xab8f;
  uVar3 = local_6._2_2_;
  iVar2 = local_6._0_2_;
  *(undefined2 *)(iVar2 + 0x32) = (int)uVar1;
  *(undefined2 *)(iVar2 + 0x34) = (int)((ulong)uVar1 >> 0x10);
  *(int *)0xab8f = iVar2;
  *(undefined2 *)0xab91 = uVar3;
  *(int *)0x7991 = *(int *)0x7991 + 1;
  return;
}



void __cdecl16near FUN_1000_3544(void)

{
  undefined4 uVar1;
  char cVar2;
  undefined2 uVar3;
  uint uVar4;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  int iVar5;
  undefined2 in_BX;
  byte *pbVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  undefined1 *puVar8;
  undefined1 local_2a [32];
  byte *local_a;
  int local_6;
  int local_4;
  
  local_6 = 1;
  while( true ) {
    if ((*(int *)(*(int *)0xe52d * 2 + 0x797d) < 0x19) &&
       (local_4 = *(int *)(local_6 * 0x20 + *(int *)0xe52d * 2 + -0x546d), local_4 != 0)) {
      cVar2 = FUN_1000_06d5(0xb);
      if (cVar2 != '\0') {
        local_4 = local_4 << 1;
      }
      iVar5 = local_4 >> 0xf;
      FUN_214c_0cc9();
      uVar7 = 0;
      uVar3 = FUN_214c_0cbb();
      FUN_214c_1178(uVar3,in_BX,iVar5);
      FUN_214c_0cc5();
      if ((bool)uVar7) {
        FUN_1000_2d29(&local_a,unaff_SS,local_6);
        uVar7 = (undefined1)((uint)in_BX >> 8);
        uVar3 = (undefined2)((ulong)local_a >> 0x10);
        FUN_1000_23da((byte *)local_a + 0x1e,uVar3,(byte *)local_a + 0x1c,uVar3);
        uVar3 = (undefined2)((ulong)local_a >> 0x10);
        pbVar6 = (byte *)local_a;
        in_BX = CONCAT11(uVar7,pbVar6[1]);
        *(byte *)(*(int *)(pbVar6 + 0x1c) * 0x4f + *(int *)(pbVar6 + 0x1e) + -0xc) = pbVar6[1];
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
        *(int *)(pbVar6 + 0x32) = (int)uVar1;
        *(int *)(pbVar6 + 0x34) = (int)((ulong)uVar1 >> 0x10);
        iVar5 = *(int *)0xe52d * 4;
        uVar7 = iVar5 == 0;
        *(undefined2 *)(iVar5 + -0x5499) = pbVar6;
        *(undefined2 *)(iVar5 + -0x5497) = uVar3;
        uVar4 = (uint)*local_a;
        puVar8 = local_2a;
        uVar3 = unaff_SS;
        FUN_214c_08af(puVar8);
        FUN_214c_08be(CONCAT11(extraout_AH,0x45));
        FUN_214c_08be(CONCAT11(extraout_AH_00,0x48));
        FUN_214c_0933(puVar8,uVar3,uVar4);
        if (!(bool)uVar7) {
          *(int *)(*(int *)0xe52d * 2 + 0x799b) = *(int *)(*(int *)0xe52d * 2 + 0x799b) + 1;
        }
        *(int *)(*(int *)0xe52d * 2 + 0x797d) = *(int *)(*(int *)0xe52d * 2 + 0x797d) + 1;
      }
    }
    if (local_6 == 0x1c) break;
    local_6 = local_6 + 1;
  }
  return;
}



int FUN_1000_3691(int param_1,int param_2)

{
  int iVar1;
  undefined2 unaff_SS;
  undefined2 local_8;
  
  local_8 = param_2;
  while (*(int *)(param_1 + local_8 * 2 + -0x36c) != local_8) {
    iVar1 = *(int *)(param_1 + local_8 * 2 + -0x36c);
    *(undefined2 *)(param_1 + local_8 * 2 + -0x36c) = *(undefined2 *)(param_1 + iVar1 * 2 + -0x36c);
    local_8 = iVar1;
  }
  return local_8;
}



void FUN_1000_36f8(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  int iVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 *puVar7;
  undefined1 local_22 [32];
  
  iVar2 = FUN_214c_1162(0x328);
  *(int *)(param_1 + -2) = iVar2 + 1;
  if (*(int *)(param_1 + -2) < 0x187) {
    *(int *)(param_1 + -8) = (*(int *)(param_1 + -2) + -1) / 0x27 + 1;
    *(int *)(param_1 + -6) = (*(int *)(param_1 + -2) + -1) % 0x27 + 1;
    iVar2 = (*(int *)(param_1 + -8) * 2 + 1) * 0x4f;
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 4) * 4 + 4);
    iVar5 = (int)uVar1 + iVar2 + *(int *)(param_1 + -6) * 2;
    uVar6 = iVar5 == 0;
    uVar3 = CONCAT11((char)((uint)iVar2 >> 8),*(undefined1 *)(iVar5 + -0x50));
    puVar7 = local_22;
    uVar4 = unaff_SS;
    FUN_214c_0885(0x20,0xb76f,unaff_DS);
    FUN_214c_0933(puVar7,uVar4,uVar3);
    if (!(bool)uVar6) {
      *(undefined2 *)(param_1 + -0x10) = *(undefined2 *)(param_1 + -2);
      *(int *)(param_1 + -0xe) = *(int *)(param_1 + -0x10) + 0x27;
      uVar4 = FUN_1000_3691(param_1,*(undefined2 *)(param_1 + -0x10));
      *(undefined2 *)(param_1 + -0xc) = uVar4;
      uVar4 = FUN_1000_3691(param_1,*(undefined2 *)(param_1 + -0xe));
      *(undefined2 *)(param_1 + -10) = uVar4;
      if ((*(int *)(param_1 + -0xc) != *(int *)(param_1 + -10)) ||
         (*(char *)(param_1 + -0x36b) == '\0')) {
        uVar1 = *(undefined4 *)(*(int *)(param_1 + 4) * 4 + 4);
        *(undefined1 *)
         ((int)uVar1 + (*(int *)(param_1 + -8) * 2 + 1) * 0x4f + *(int *)(param_1 + -6) * 2 + -0x50)
             = 0x20;
        *(int *)(param_1 + -4) = *(int *)(param_1 + -4) + 1;
        if (*(int *)(param_1 + -0xc) < *(int *)(param_1 + -10)) {
          *(undefined2 *)(param_1 + *(int *)(param_1 + -10) * 2 + -0x36c) =
               *(undefined2 *)(param_1 + -0xc);
        }
        else {
          *(undefined2 *)(param_1 + *(int *)(param_1 + -0xc) * 2 + -0x36c) =
               *(undefined2 *)(param_1 + -10);
        }
      }
    }
  }
  else {
    *(int *)(param_1 + -2) = *(int *)(param_1 + -2) + -0x186;
    *(int *)(param_1 + -8) = (*(int *)(param_1 + -2) + -1) / 0xb + 1;
    *(int *)(param_1 + -6) = (*(int *)(param_1 + -2) + -1) % 0xb + 1;
    iVar2 = *(int *)(param_1 + -6) * 0x9e;
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 4) * 4 + 4);
    iVar5 = (int)uVar1 + iVar2 + *(int *)(param_1 + -8) * 2 + 1;
    uVar6 = iVar5 == 0;
    uVar3 = CONCAT11((char)((uint)iVar2 >> 8),*(undefined1 *)(iVar5 + -0x50));
    puVar7 = local_22;
    uVar4 = unaff_SS;
    FUN_214c_0885(0x20,0xb76f,unaff_DS);
    FUN_214c_0933(puVar7,uVar4,uVar3);
    if (!(bool)uVar6) {
      *(int *)(param_1 + -0x10) = (*(int *)(param_1 + -6) + -1) * 0x27 + *(int *)(param_1 + -8);
      *(int *)(param_1 + -0xe) = *(int *)(param_1 + -0x10) + 1;
      uVar4 = FUN_1000_3691(param_1,*(undefined2 *)(param_1 + -0x10));
      *(undefined2 *)(param_1 + -0xc) = uVar4;
      uVar4 = FUN_1000_3691(param_1,*(undefined2 *)(param_1 + -0xe));
      *(undefined2 *)(param_1 + -10) = uVar4;
      if ((*(int *)(param_1 + -0xc) != *(int *)(param_1 + -10)) ||
         (*(char *)(param_1 + -0x36b) == '\0')) {
        uVar1 = *(undefined4 *)(*(int *)(param_1 + 4) * 4 + 4);
        *(undefined1 *)
         ((int)uVar1 + *(int *)(param_1 + -6) * 0x9e + *(int *)(param_1 + -8) * 2 + -0x4f) = 0x20;
        *(int *)(param_1 + -4) = *(int *)(param_1 + -4) + 1;
        if (*(int *)(param_1 + -0xc) < *(int *)(param_1 + -10)) {
          *(undefined2 *)(param_1 + *(int *)(param_1 + -10) * 2 + -0x36c) =
               *(undefined2 *)(param_1 + -0xc);
        }
        else {
          *(undefined2 *)(param_1 + *(int *)(param_1 + -0xc) * 2 + -0x36c) =
               *(undefined2 *)(param_1 + -10);
        }
      }
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00013b1e)
// WARNING: Removing unreachable block (ram,0x00013b23)
// WARNING: Removing unreachable block (ram,0x00013b2e)

void FUN_1000_3a12(int param_1)

{
  undefined4 uVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_a;
  int local_8;
  
  local_a = 1;
  while( true ) {
    for (local_8 = 1; uVar1 = *(undefined4 *)(param_1 * 4 + 4),
        *(undefined1 *)((int)uVar1 + local_a * 0x9e + local_8 * 2 + -0x4f) = 0xb3, local_8 != 0x26;
        local_8 = local_8 + 1) {
    }
    if (local_a == 0xb) break;
    local_a = local_a + 1;
  }
  local_a = 1;
  while( true ) {
    for (local_8 = 1; uVar1 = *(undefined4 *)(param_1 * 4 + 4),
        *(undefined1 *)((int)uVar1 + (local_a * 2 + 1) * 0x4f + local_8 * 2 + -0x50) = 0xc4,
        local_8 != 0x27; local_8 = local_8 + 1) {
    }
    if (local_a == 10) break;
    local_a = local_a + 1;
  }
  local_a = 1;
  while( true ) {
    for (local_8 = 1; uVar1 = *(undefined4 *)(param_1 * 4 + 4),
        *(undefined1 *)((int)uVar1 + (local_a * 2 + 1) * 0x4f + local_8 * 2 + -0x4f) = 0xc5,
        local_8 != 0x26; local_8 = local_8 + 1) {
    }
    if (local_a == 10) break;
    local_a = local_a + 1;
  }
  for (local_a = 1; *(int *)(&stack0xfc92 + local_a * 2) = local_a, local_a != 0x1ad;
      local_a = local_a + 1) {
  }
  do {
    FUN_1000_36f8(&stack0xfffe);
  } while( true );
}



void FUN_1000_3b34(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  int iVar4;
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
    iVar2 = FUN_214c_1162(10);
    *(int *)(param_1 * 4 + 0x78ed) = iVar2 * 2 + 2;
    iVar2 = FUN_214c_1162(0x26);
    *(int *)(param_1 * 4 + 0x78ef) = iVar2 * 2 + 2;
    uVar1 = *(undefined4 *)(param_1 * 4 + 4);
  } while (*(char *)((int)uVar1 + *(int *)(param_1 * 4 + 0x78ed) * 0x4f +
                     *(int *)(param_1 * 4 + 0x78ef) + -0x50) != ' ');
  uVar1 = *(undefined4 *)(param_1 * 4 + 4);
  *(undefined1 *)
   ((int)uVar1 + *(int *)(param_1 * 4 + 0x78ed) * 0x4f + *(int *)(param_1 * 4 + 0x78ef) + -0x50) =
       0xef;
  do {
    iVar2 = FUN_214c_1162(10);
    *(int *)(param_1 * 4 + 0x792d) = iVar2 * 2 + 2;
    iVar2 = FUN_214c_1162(0x26);
    *(int *)(param_1 * 4 + 0x792f) = iVar2 * 2 + 2;
    uVar1 = *(undefined4 *)(param_1 * 4 + 4);
  } while (*(char *)((int)uVar1 + *(int *)(param_1 * 4 + 0x792d) * 0x4f +
                     *(int *)(param_1 * 4 + 0x792f) + -0x50) != ' ');
  if (param_1 != 0xf) {
    uVar1 = *(undefined4 *)(param_1 * 4 + 4);
    *(undefined1 *)
     ((int)uVar1 + *(int *)(param_1 * 4 + 0x792d) * 0x4f + *(int *)(param_1 * 4 + 0x792f) + -0x50) =
         0xef;
  }
  iVar2 = param_1 >> 0xf;
  FUN_214c_0cc9();
  uVar5 = 0;
  uVar6 = 1;
  uVar3 = FUN_214c_0cbb();
  FUN_214c_1178(uVar3,in_BX,iVar2);
  FUN_214c_0cc5();
  if (((bool)uVar5 || (bool)uVar6) || (param_1 == 0)) {
    local_12 = 0;
    local_10 = 0;
    local_e = 0;
    local_c = 0;
  }
  else {
    iVar2 = FUN_214c_1162(0x10 - param_1);
    local_12 = iVar2 * 2 + 8;
    iVar2 = FUN_214c_1162((0x13 - param_1) / 3);
    local_10 = iVar2 * 2 + 4;
    iVar2 = FUN_214c_1162(0x26 - local_12 / 2);
    local_c = iVar2 * 2 + 3;
    iVar2 = FUN_214c_1162(9 - local_10 / 2);
    local_e = iVar2 * 2 + 3;
  }
  if (local_10 != 0) {
    iVar2 = local_12 / 2 + -1;
    if (0 < iVar2) {
      local_18 = 1;
      while( true ) {
        uVar1 = *(undefined4 *)(param_1 * 4 + 4);
        *(undefined1 *)((int)uVar1 + local_e * 0x4f + local_18 * 2 + local_c + -0x50) = 0xc1;
        uVar1 = *(undefined4 *)(param_1 * 4 + 4);
        *(undefined1 *)((int)uVar1 + (local_e + 1) * 0x4f + local_18 * 2 + local_c + -0x50) = 0x20;
        uVar1 = *(undefined4 *)(param_1 * 4 + 4);
        *(undefined1 *)((int)uVar1 + (local_e + local_10) * 0x4f + local_18 * 2 + local_c + -0x50) =
             0xc2;
        if (local_18 == iVar2) break;
        local_18 = local_18 + 1;
      }
    }
    iVar2 = local_10 / 2 + -1;
    if (0 < iVar2) {
      local_18 = 1;
      while( true ) {
        uVar1 = *(undefined4 *)(param_1 * 4 + 4);
        *(undefined1 *)((int)uVar1 + (local_18 * 2 + local_e) * 0x4f + local_c + -0x50) = 0xb4;
        uVar1 = *(undefined4 *)(param_1 * 4 + 4);
        *(undefined1 *)((int)uVar1 + (local_18 * 2 + local_e) * 0x4f + local_c + -0x4f) = 0x20;
        uVar1 = *(undefined4 *)(param_1 * 4 + 4);
        *(undefined1 *)((int)uVar1 + (local_18 * 2 + local_e) * 0x4f + local_c + local_12 + -0x50) =
             0xc3;
        if (local_18 == iVar2) break;
        local_18 = local_18 + 1;
      }
    }
    iVar2 = local_12 / 2 + -1;
    if (0 < iVar2) {
      local_18 = 1;
      while( true ) {
        iVar4 = local_10 / 2 + -1;
        if (0 < iVar4) {
          local_16 = 1;
          while( true ) {
            uVar1 = *(undefined4 *)(param_1 * 4 + 4);
            *(undefined1 *)
             ((int)uVar1 + (local_16 * 2 + local_e) * 0x4f + local_18 * 2 + local_c + -0x50) = 0x20;
            uVar1 = *(undefined4 *)(param_1 * 4 + 4);
            *(undefined1 *)
             ((int)uVar1 + (local_16 * 2 + local_e + 1) * 0x4f + local_18 * 2 + local_c + -0x50) =
                 0x20;
            uVar1 = *(undefined4 *)(param_1 * 4 + 4);
            *(undefined1 *)
             ((int)uVar1 + (local_16 * 2 + local_e) * 0x4f + local_18 * 2 + local_c + -0x4f) = 0x20;
            if (local_16 == iVar4) break;
            local_16 = local_16 + 1;
          }
        }
        if (local_18 == iVar2) break;
        local_18 = local_18 + 1;
      }
    }
  }
  iVar2 = FUN_214c_1162(3);
  if (iVar2 == 1) {
    FUN_1000_2363(&param_1,unaff_SS,&local_4,unaff_SS,&local_6,unaff_SS);
    uVar1 = *(undefined4 *)(param_1 * 4 + 4);
    *(undefined1 *)((int)uVar1 + local_6 * 0x4f + local_4 + -0x50) = 0xf7;
  }
  if (param_1 == 1) {
    FUN_1000_2363(&param_1,unaff_SS,&local_8,unaff_SS,&local_a,unaff_SS);
    uVar1 = *(undefined4 *)(param_1 * 4 + 4);
    *(undefined1 *)((int)uVar1 + local_a * 0x4f + local_8 + -0x50) = 0x9b;
  }
  if (((param_1 != 0xf) && (iVar2 = FUN_214c_1162(2), iVar2 == 0)) &&
     (iVar2 = FUN_214c_1162(3), -1 < iVar2)) {
    local_18 = 0;
    while( true ) {
      FUN_1000_2363(&param_1,unaff_SS,&local_4,unaff_SS,&local_6,unaff_SS);
      uVar1 = *(undefined4 *)(param_1 * 4 + 4);
      *(undefined1 *)((int)uVar1 + local_6 * 0x4f + local_4 + -0x50) = *(undefined1 *)0x1;
      if (local_18 == iVar2) break;
      local_18 = local_18 + 1;
    }
  }
  if ((param_1 == 10) || (param_1 == 0xf)) {
    do {
      iVar2 = FUN_214c_1162(2);
      iVar4 = FUN_214c_1162(3);
    } while (iVar4 == 0);
    if (0 < iVar2 + 1) {
      local_18 = 1;
      while( true ) {
        FUN_1000_2363(&param_1,unaff_SS,&local_4,unaff_SS,&local_6,unaff_SS);
        uVar1 = *(undefined4 *)(param_1 * 4 + 4);
        *(undefined1 *)((int)uVar1 + local_6 * 0x4f + local_4 + -0x50) = *(undefined1 *)0x3;
        if (local_18 == iVar2 + 1) break;
        local_18 = local_18 + 1;
      }
    }
  }
  uVar1 = *(undefined4 *)(param_1 * 4 + 4);
  *(undefined1 *)((int)uVar1 + 0x71a) = 1;
  return;
}



void FUN_1000_40c0(undefined2 param_1)

{
  int iVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar2;
  undefined1 local_16 [4];
  char local_12;
  char local_11;
  undefined2 local_10;
  int local_a;
  int local_6;
  
  uVar2 = &stack0xfffe < (undefined1 *)0x1a;
  local_10 = FUN_214c_1178();
  FUN_214c_0cc5();
  if ((bool)uVar2) {
    local_12 = '\a';
  }
  else {
    FUN_214c_0cc5();
    if ((bool)uVar2) {
      local_12 = '\x06';
    }
    else {
      FUN_214c_0cc5();
      if ((bool)uVar2) {
        local_12 = '\x03';
      }
      else {
        FUN_214c_0cc5();
        if ((bool)uVar2) {
          local_12 = '\x02';
        }
        else {
          FUN_214c_0cc5();
          if ((bool)uVar2) {
            local_12 = '\x04';
          }
          else {
            local_12 = '\x05';
          }
        }
      }
    }
  }
  local_11 = '\0';
  while( true ) {
    local_6 = *(int *)(local_11 * 0x30 + 0x79d7);
    if ((*(int *)(local_11 * 0x30 + 0x79d9) != 0) && (0 < *(int *)(local_11 * 0x30 + 0x79d9))) {
      iVar1 = FUN_214c_1162(*(undefined2 *)(local_11 * 0x30 + 0x79d9));
      local_6 = local_6 + iVar1;
    }
    if (local_12 == local_11) {
      iVar1 = FUN_214c_1162(*(undefined2 *)(local_11 * 0x30 + 0x79db));
      local_6 = local_6 + iVar1 + 1;
    }
    iVar1 = local_6;
    if (0 < local_6) {
      local_a = 1;
      while( true ) {
        FUN_1000_26cf(local_16,unaff_SS,param_1,local_11);
        FUN_1000_2574(param_1,local_16,unaff_SS);
        if (local_a == iVar1) break;
        local_a = local_a + 1;
      }
    }
    if (local_11 == '\b') break;
    local_11 = local_11 + '\x01';
  }
  return;
}



void __cdecl16near FUN_1000_425e(void)

{
  bool bVar1;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  uint uVar2;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  int iVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar4;
  undefined1 uVar5;
  undefined1 *puVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined1 local_3a [32];
  int local_1a;
  int local_16;
  undefined1 local_13 [17];
  
  FUN_20e6_020d();
  local_16 = 0;
  while( true ) {
    FUN_20e6_0260(local_16 * 2 + 9,10);
    FUN_1000_016a(local_16 + 0x2a);
    if (local_16 == 3) break;
    local_16 = local_16 + 1;
  }
  bVar1 = true;
  do {
    if (!bVar1) {
      return;
    }
    uVar7 = 0xe554;
    FUN_214c_17be(0x10,local_13,unaff_SS);
    FUN_214c_16ef(0x214c,uVar7);
    FUN_20e6_0260(CONCAT11(extraout_AH,0x11),CONCAT11(extraout_AH,5));
    FUN_20e6_0227();
    FUN_20e6_0260(CONCAT11(extraout_AH_00,0x12),CONCAT11(extraout_AH_00,0x3c));
    for (local_16 = 1; local_16 < 0x10; local_16 = local_16 + 1) {
      iVar3 = local_16 * 0x18 + -0x45db;
      bVar4 = iVar3 == 0;
      FUN_214c_0783(iVar3,unaff_DS,local_13,unaff_SS);
      if (bVar4) break;
    }
    if (local_16 == 0x10) {
      FUN_214c_06ad(0x1c,0xb84f,unaff_DS,local_13,unaff_SS);
      bVar1 = false;
    }
    else {
      _local_1a = CONCAT22(unaff_DS,local_16 * 0x18 + -0x45db);
      uVar5 = (undefined1)((uint)(local_16 * 0x18) >> 8);
      FUN_20e6_0260(CONCAT11(uVar5,0x11),CONCAT11(uVar5,5));
      FUN_1000_016a(0x99);
      uVar8 = 0xe654;
      uVar7 = unaff_DS;
      FUN_214c_1799(0,CONCAT11(extraout_AH_01,0x20));
      uVar5 = 1;
      FUN_214c_17f7(0,(int)_local_1a,(int)((ulong)_local_1a >> 0x10));
      FUN_214c_1755(uVar8,uVar7);
      FUN_1000_22c8(0x23,*(undefined2 *)((int)_local_1a + 0x16));
      uVar8 = CONCAT11(extraout_AH_02,*(undefined1 *)((int)_local_1a + 0x16));
      puVar6 = local_3a;
      uVar7 = unaff_SS;
      FUN_214c_08af(puVar6);
      FUN_214c_08df(CONCAT11(extraout_AH_03,0x23),CONCAT11(extraout_AH_03,1));
      uVar2 = FUN_214c_0933(puVar6,uVar7,uVar8);
      if (!(bool)uVar5) {
        FUN_1000_0499(uVar2 & 0xff00,*(undefined2 *)((int)_local_1a + 0x16));
      }
      if (*(char *)((int)_local_1a + 0x16) != 'g') {
        uVar8 = 0xe654;
        uVar7 = unaff_DS;
        FUN_214c_17f7(0,0x4252,0x214c);
        iVar3 = *(int *)((int)_local_1a + 0x10);
        FUN_214c_1882(0,iVar3,iVar3 >> 0xf);
        FUN_214c_1799(0,CONCAT11(extraout_AH_04,0x2e));
        FUN_214c_1755(uVar8,uVar7);
      }
      FUN_20e6_0227();
      FUN_20e6_0260(CONCAT11(extraout_AH_05,0x12),CONCAT11(extraout_AH_05,0x14));
      FUN_1000_016a(0x26);
      FUN_20e6_0227();
    }
  } while( true );
}



void __cdecl16near FUN_1000_447b(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  char cVar3;
  undefined2 uVar4;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 uVar6;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  int iVar5;
  undefined2 unaff_DS;
  undefined2 uVar7;
  int local_c;
  char local_8;
  char local_7;
  
  local_8 = '\0';
  while( true ) {
    *(undefined2 *)(local_8 * 4 + -0x4738) = 0;
    *(undefined2 *)(local_8 * 4 + -0x4736) = 0;
    if (local_8 == '\b') break;
    local_8 = local_8 + '\x01';
  }
  *(undefined2 *)0xb886 = 0;
  *(undefined2 *)0xb888 = 0x80;
  *(undefined2 *)0xb870 = 1000;
  *(undefined2 *)0xb872 = 1000;
  *(undefined2 *)0xb88a = 0;
  *(undefined2 *)0xb88c = 0;
  *(undefined2 *)0xb88e = 0;
  FUN_20e6_020d();
  uVar7 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_17f7(0,0x440c,0x20e6);
  FUN_214c_1755(uVar7,uVar4);
  uVar4 = FUN_20e6_0357();
  cVar3 = FUN_214c_190c(uVar4);
  if (cVar3 == 'O') {
    *(undefined2 *)0xb874 = 100;
    *(undefined2 *)0xb876 = 100;
    *(undefined2 *)0xb878 = 100;
    *(undefined2 *)0xb87a = 100;
  }
  else {
    FUN_20e6_020d();
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_17f7(0,0x4427,0x20e6);
    FUN_214c_1882(2,0xff,0);
    FUN_214c_17f7(0,0x4432,0x214c);
    FUN_214c_1755(uVar7,uVar4);
    FUN_20e6_0260(CONCAT11(extraout_AH,4),CONCAT11(extraout_AH,5));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_17f7(0,0x4448,0x20e6);
    FUN_214c_1755(uVar7,uVar4);
    FUN_20e6_0260(CONCAT11(extraout_AH_00,5),CONCAT11(extraout_AH_00,5));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_17f7(0,0x4459,0x20e6);
    FUN_214c_1755(uVar7,uVar4);
    FUN_20e6_0260(CONCAT11(extraout_AH_01,6),CONCAT11(extraout_AH_01,5));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_17f7(0,0x446a,0x20e6);
    FUN_214c_1755(uVar7,uVar4);
    FUN_20e6_0260(CONCAT11(extraout_AH_02,4),CONCAT11(extraout_AH_02,0x15));
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb876 = uVar4;
    FUN_214c_16ef(0x214c);
    *(undefined2 *)0xb874 = *(undefined2 *)0xb876;
    iVar5 = 0xff - *(int *)0xb876;
    uVar6 = (undefined1)((uint)iVar5 >> 8);
    FUN_20e6_0260(CONCAT11(uVar6,1),CONCAT11(uVar6,0xb));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1882(2,iVar5,iVar5 >> 0xf);
    FUN_214c_1755(uVar7,uVar4);
    FUN_20e6_0260(CONCAT11(extraout_AH_03,5),CONCAT11(extraout_AH_03,0x15));
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb878 = uVar4;
    FUN_214c_16ef(0x214c);
    iVar5 = iVar5 - *(int *)0xb878;
    uVar6 = (undefined1)((uint)iVar5 >> 8);
    FUN_20e6_0260(CONCAT11(uVar6,1),CONCAT11(uVar6,0xb));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1882(2,iVar5,iVar5 >> 0xf);
    FUN_214c_1755(uVar7,uVar4);
    FUN_20e6_0260(CONCAT11(extraout_AH_04,6),CONCAT11(extraout_AH_04,0x15));
    uVar7 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1882(0,iVar5,iVar5 >> 0xf);
    FUN_214c_1755(uVar7,uVar4);
    *(int *)0xb87a = iVar5;
  }
  local_c = 1;
  while( true ) {
    *(undefined2 *)(local_c * 4 + -0x476c) = 0;
    *(undefined2 *)(local_c * 4 + -0x476a) = 0;
    if (local_c == 10) break;
    local_c = local_c + 1;
  }
  *(undefined2 *)0xb892 = 1000;
  *(undefined2 *)0xb936 = 4;
  iVar5 = *(int *)0xb936;
  if (0 < iVar5) {
    local_c = 1;
    while( true ) {
      *(undefined2 *)(local_c * 4 + -0x46cc) = 0;
      *(undefined2 *)(local_c * 4 + -0x46ca) = 0;
      if (local_c == iVar5) break;
      local_c = local_c + 1;
    }
  }
  *(undefined2 *)0xb8c2 = 3;
  *(undefined2 *)0xb8c0 = 3;
  *(undefined2 *)0xb8c6 = 0x26;
  *(undefined2 *)0xb87c = 0;
  *(undefined2 *)0xb87e = 0;
  *(undefined2 *)0xb880 = 0;
  *(undefined2 *)0xb882 = 0;
  *(undefined2 *)0xb8cc = 1;
  *(undefined2 *)0xb8ce = 0;
  *(undefined2 *)0xb8e0 = 1;
  *(undefined2 *)0xb8e2 = 0;
  *(undefined2 *)0xb8e4 = 3;
  *(undefined2 *)0xb8e6 = 0;
  local_7 = '\0';
  while( true ) {
    *(undefined1 *)(local_7 + -0x4714) = 0;
    *(undefined2 *)(local_7 * 2 + -0x4707) = 0;
    if (local_7 == '\f') break;
    local_7 = local_7 + '\x01';
  }
  *(undefined1 *)0xb913 = 0;
  *(undefined2 *)0xb909 = 3000;
  *(undefined1 *)0xb8f4 = 1;
  *(undefined1 *)0xb915 = 0;
  *(undefined1 *)0xb916 = 0;
  *(undefined1 *)0xb917 = 0;
  *(undefined1 *)0xb918 = 0;
  *(undefined1 *)0xb919 = 0;
  *(undefined2 *)0xb890 = 5;
  FUN_1000_05d6(0xb91e,unaff_DS);
  puVar1 = (undefined1 *)*(undefined4 *)0xb91e;
  uVar4 = (undefined2)((ulong)puVar1 >> 0x10);
  puVar2 = (undefined1 *)puVar1;
  *puVar1 = 1;
  *(undefined2 *)(puVar2 + 0xb) = 2;
  FUN_1000_05d6(puVar2 + 0x16,uVar4);
  *(undefined2 *)0xb926 = 0;
  *(undefined2 *)0xb928 = 0;
  *(undefined2 *)0xb92a = 0;
  *(undefined2 *)0xb92c = 0;
  *(undefined2 *)0xb932 = 0;
  *(undefined2 *)0xb934 = 0;
  *(undefined2 *)0xb92e = 0;
  *(undefined2 *)0xb930 = 0;
  *(undefined2 *)0xb884 = 0;
  *(undefined2 *)0xb922 = 0;
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
  FUN_1000_05d6(puVar2 + 0x16,uVar4);
  puVar1 = *(undefined1 **)(puVar2 + 0x16);
  uVar4 = (undefined2)((ulong)puVar1 >> 0x10);
  puVar2 = (undefined1 *)puVar1;
  *puVar1 = 7;
  *(undefined2 *)(puVar2 + 1) = 0xc;
  *(undefined2 *)(puVar2 + 0x11) = 1;
  iVar5 = FUN_214c_1162(0xe);
  *(int *)(puVar2 + 3) = iVar5 + 7;
  *(undefined2 *)(puVar2 + 9) = 0;
  *(undefined2 *)(puVar2 + 0xb) = 2;
  puVar2[0x14] = 0;
  puVar2[0x13] = 1;
  *(undefined2 *)(puVar2 + 0x16) = 0;
  *(undefined2 *)(puVar2 + 0x18) = 0;
  *(undefined2 *)0xb8c4 = 6;
  return;
}



void __cdecl16near FUN_1000_48b7(void)

{
  undefined1 extraout_AH;
  undefined2 unaff_SS;
  undefined1 local_8 [6];
  
  FUN_214c_11e8();
  FUN_1000_425e();
  FUN_1000_447b();
  FUN_1000_3a12(1);
  FUN_1000_3b34(1);
  FUN_1000_40c0(1);
  FUN_1000_2fe0();
  FUN_1000_30ec();
  FUN_1000_26cf(local_8,unaff_SS,0xf,CONCAT11(extraout_AH,8));
  *(undefined2 *)((int)local_8._0_4_ + 1) = 0;
  FUN_1000_2574(0xf,local_8,unaff_SS);
  FUN_1000_325e();
  FUN_1000_3408();
  FUN_1000_3442();
  FUN_1000_3486();
  FUN_1000_34ea();
  FUN_1000_33a1();
  return;
}



void FUN_1000_491d(int *param_1,int *param_2)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined1 extraout_AH;
  int iVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined1 *puVar7;
  undefined2 uVar8;
  undefined1 local_49 [32];
  undefined1 local_29 [32];
  char local_9;
  int local_8;
  int local_6;
  int local_4;
  
  local_9 = '\x01';
  for (local_4 = 1; (local_9 != '\0' && (local_4 != 5)); local_4 = local_4 + 1) {
    local_8 = *param_2;
    local_6 = *param_1;
    do {
      local_8 = local_8 + *(int *)(local_4 * 4 + -0x464e);
      local_6 = local_6 + *(int *)(local_4 * 4 + -0x464c);
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar3 = (int)uVar1 + local_8 * 0x4f + local_6;
      uVar4 = iVar3 == 0;
      uVar2 = CONCAT11((char)((uint)(local_8 * 0x4f) >> 8),*(undefined1 *)(iVar3 + -0x50));
      puVar7 = local_49;
      uVar8 = unaff_SS;
      FUN_214c_0885(0x20,0xb76f,unaff_DS);
      puVar5 = local_29;
      uVar6 = unaff_SS;
      FUN_214c_08af(puVar5);
      FUN_214c_08be(CONCAT11(extraout_AH,0x20));
      FUN_214c_0954(puVar5,uVar6);
      FUN_214c_0933(puVar7,uVar8,uVar2);
    } while ((bool)uVar4);
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    if (*(char *)((int)uVar1 + local_8 * 0x4f + local_6 + -0x50) == ' ') {
      *param_2 = local_8;
      *param_1 = local_6;
      local_9 = '\0';
    }
  }
  if (local_9 != '\0') {
    FUN_1000_2363(0xe52d,unaff_DS,(int *)param_1,(int)((ulong)param_1 >> 0x10),(int *)param_2,
                  (int)((ulong)param_2 >> 0x10));
  }
  return;
}



void FUN_1000_4a27(char param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  uint in_AX;
  int iVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_a [4];
  undefined1 local_6 [4];
  
  if (param_1 == '\0') {
    iVar5 = FUN_214c_1162(5);
    FUN_1000_26cf(local_6,unaff_SS,*(undefined2 *)0xe52d,iVar5 + 1);
    FUN_1000_2574(*(undefined2 *)0xe52d,local_6,unaff_SS);
  }
  else {
    FUN_1000_26cf(local_a,unaff_SS,*(undefined2 *)0xe52d,in_AX & 0xff00);
    FUN_1000_2574(*(undefined2 *)0xe52d,local_a,unaff_SS);
  }
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  uVar3 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  *(undefined1 *)((int)uVar3 + *(int *)((int)uVar2 + 5) * 0x4f + *(int *)((int)uVar1 + 7) + -0x50) =
       0x20;
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  *(undefined2 *)((int)uVar1 + 5) = *(undefined2 *)0xb86c;
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  *(undefined2 *)((int)uVar1 + 7) = *(undefined2 *)0xb86e;
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  FUN_1000_491d((int)uVar2 + 7,(int)((ulong)uVar2 >> 0x10),(int)uVar1 + 5,
                (int)((ulong)uVar1 >> 0x10));
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  uVar6 = (undefined2)((ulong)uVar1 >> 0x10);
  iVar5 = (int)uVar1;
  uVar4 = FUN_1000_0479(*(undefined2 *)(*(int *)0xe52d * 4 + -0x54d9),
                        *(undefined2 *)(*(int *)0xe52d * 4 + -0x54d7));
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  *(undefined1 *)((int)uVar1 + *(int *)(iVar5 + 5) * 0x4f + *(int *)(iVar5 + 7) + -0x50) = uVar4;
  return;
}



void __cdecl16near FUN_1000_4b52(void)

{
  FUN_1000_0040();
  FUN_1000_016a(0x1a2);
  return;
}



void __cdecl16near FUN_1000_4c49(void)

{
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  uint uVar1;
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
  int iVar2;
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
  
  FUN_20e6_020d();
  FUN_20e6_0260(CONCAT11(extraout_AH,1),CONCAT11(extraout_AH,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_00,0xc9));
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xcd);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xbb);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_01,2),CONCAT11(extraout_AH_01,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_02,0xba));
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_02be(CONCAT11(extraout_AH_03,2));
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0x20);
    uVar1 = FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  FUN_20e6_02be(uVar1 & 0xff00);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_04,0xba));
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_05,3),CONCAT11(extraout_AH_05,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_06,0xba));
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_02be(CONCAT11(extraout_AH_07,2));
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0x20);
    uVar1 = FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  FUN_20e6_02be(uVar1 & 0xff00);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_08,0xba));
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_09,4),CONCAT11(extraout_AH_09,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_10,0xba));
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_02be(CONCAT11(extraout_AH_11,2));
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0x20);
    uVar1 = FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  FUN_20e6_02be(uVar1 & 0xff00);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_12,0xba));
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_13,5),CONCAT11(extraout_AH_13,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_14,0xcc));
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xcd);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xd1);
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xcd);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xb9);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_15,6),CONCAT11(extraout_AH_15,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_17f7(0,0x4b63,0x20e6);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_16,7),CONCAT11(extraout_AH_16,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_17,199));
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xc4);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xc5);
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xc4);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xb6);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_18,8),CONCAT11(extraout_AH_18,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_17f7(0,0x4b91,0x20e6);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_19,9),CONCAT11(extraout_AH_19,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_20,199));
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xc4);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xc5);
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xc4);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xb6);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_21,10),CONCAT11(extraout_AH_21,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_17f7(0,0x4bbf,0x20e6);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_22,0xb),CONCAT11(extraout_AH_22,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_23,199));
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xc4);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xc5);
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xc4);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xb6);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_24,0xc),CONCAT11(extraout_AH_24,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_17f7(0,0x4bed,0x20e6);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_25,0xd),CONCAT11(extraout_AH_25,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_26,199));
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xc4);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xc5);
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xc4);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xb6);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_27,0xe),CONCAT11(extraout_AH_27,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_17f7(0,0x4c1b,0x20e6);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_28,0xf),CONCAT11(extraout_AH_28,0x12));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH_29,200));
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x13;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xcd);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x27) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xcf);
  FUN_214c_1755(uVar3,uVar4);
  local_4 = 0x29;
  while( true ) {
    uVar3 = 0xe654;
    uVar4 = unaff_DS;
    FUN_214c_1799(0,0xcd);
    FUN_214c_1755(uVar3,uVar4);
    if (local_4 == 0x3d) break;
    local_4 = local_4 + 1;
  }
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1799(0,0xbc);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_02be(CONCAT11(extraout_AH_30,2));
  iVar2 = 0x28 - *(byte *)0xb84f / 2;
  FUN_20e6_0260(CONCAT11((char)((uint)iVar2 >> 8),3),iVar2);
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_17f7(0,0xb84f,unaff_DS);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_02be((uint)extraout_AH_31 << 8);
  FUN_20e6_0260(CONCAT11(extraout_AH_32,6),CONCAT11(extraout_AH_32,0x22));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1882(0,*(int *)0xb888,*(int *)0xb888 >> 0xf);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_33,6),CONCAT11(extraout_AH_33,0x38));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1882(0,*(int *)0xb886,*(int *)0xb886 >> 0xf);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_34,8),CONCAT11(extraout_AH_34,0x22));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1882(0,*(int *)0xb870,*(int *)0xb870 >> 0xf);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_35,8),CONCAT11(extraout_AH_35,0x38));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1882(0,*(int *)0xb872,*(int *)0xb872 >> 0xf);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_36,10),CONCAT11(extraout_AH_36,0x22));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1882(0,*(int *)0xb874,*(int *)0xb874 >> 0xf);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_37,10),CONCAT11(extraout_AH_37,0x38));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1882(0,*(int *)0xb876,*(int *)0xb876 >> 0xf);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_38,0xc),CONCAT11(extraout_AH_38,0x22));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1882(0,*(int *)0xb878,*(int *)0xb878 >> 0xf);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_39,0xc),CONCAT11(extraout_AH_39,0x38));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1882(0,*(int *)0xb87a,*(int *)0xb87a >> 0xf);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_40,0xe),CONCAT11(extraout_AH_40,0x22));
  uVar3 = 0xe654;
  uVar4 = unaff_DS;
  FUN_214c_1882(0,*(undefined2 *)0xb8c8,*(undefined2 *)0xb8ca);
  FUN_214c_1755(uVar3,uVar4);
  FUN_20e6_0260(CONCAT11(extraout_AH_41,0xe),CONCAT11(extraout_AH_41,0x38));
  uVar4 = 0xe654;
  FUN_214c_1882(0,*(int *)0xb880,*(int *)0xb880 >> 0xf);
  FUN_214c_1755(uVar4,unaff_DS);
  FUN_20e6_0260(CONCAT11(extraout_AH_42,0x19),CONCAT11(extraout_AH_42,0x41));
  FUN_1000_1448();
  FUN_1000_11fc(0x17);
  return;
}



void __cdecl16near FUN_1000_53c9(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
  local_4 = (uint)((ulong)uVar2 >> 0x10);
  uVar3 = (uint)uVar2;
  while ((uVar3 | local_4) != 0) {
    FUN_1000_0428(CONCAT11((char)((uVar3 | local_4) >> 8),*(undefined1 *)(uVar3 + 1)),
                  *(undefined2 *)(uVar3 + 0x1e),*(undefined2 *)(uVar3 + 0x1c));
    puVar1 = (undefined4 *)(uVar3 + 0x32);
    local_4 = (uint)((ulong)*puVar1 >> 0x10);
    uVar3 = (uint)*puVar1;
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
  
  pcVar1 = (char *)*(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  while (local_6 = (char *)pcVar1, local_4 = (int)((ulong)pcVar1 >> 0x10),
        local_6 != (char *)0x0 || local_4 != 0) {
    if (*pcVar1 == param_2) {
      if (*(char *)0xb8ee == '\0') {
        *(undefined1 *)
         (*(int *)0xe52d * 0x719 + *(int *)(local_6 + 5) * 0x4f + *(int *)(local_6 + 7) + 0x70d) = 1
        ;
      }
      if ((((param_2 != '\x06') && (param_2 != '\a')) || (param_1 != '\0')) ||
         (*(int *)(local_6 + 9) != 0)) {
        uVar4 = *(undefined2 *)(local_6 + 5);
        uVar3 = *(undefined2 *)(local_6 + 7);
        uVar2 = FUN_1000_0479(local_6,local_4);
        FUN_1000_0428(uVar2,uVar3,uVar4);
      }
    }
    pcVar1 = *(char **)(local_6 + 0x16);
  }
  return;
}



void FUN_1000_54d2(int param_1)

{
  undefined2 unaff_DS;
  undefined2 local_6;
  undefined2 local_4;
  
  local_6 = 1;
  while( true ) {
    FUN_1000_0428(local_6 % 2 + 1,*(undefined2 *)0xb86e,*(undefined2 *)0xb86c);
    local_4 = 1;
    while( true ) {
      FUN_20e6_0311(local_6 * param_1);
      if (local_4 == 500) break;
      local_4 = local_4 + 1;
    }
    if (local_6 == 8) break;
    local_6 = local_6 + 1;
  }
  FUN_20e6_033e();
  return;
}



void FUN_1000_5527(int param_1)

{
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  if ((*(char *)(param_1 + 6) != '\0') || (*(char *)*(undefined4 *)(param_1 + 8) == '\a')) {
    uVar1 = 0xe654;
    FUN_214c_1799(0,0x73);
    FUN_214c_1755(uVar1,unaff_DS);
  }
  return;
}



void FUN_1000_557c(char param_1,char param_2,char *param_3)

{
  char cVar1;
  bool bVar2;
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
  int iVar3;
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
  
  pcVar5 = (char *)param_3;
  iVar3 = (int)((ulong)param_3 >> 0x10);
  if ((param_2 == '\0') || (*(int *)(pcVar5 + 3) < 2)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  FUN_1000_0094();
  local_8 = param_3;
  cVar1 = *param_3;
  if (cVar1 == '\x01') {
    if (bVar2) {
      uVar8 = 0xe654;
      FUN_214c_1882(0,*(int *)(pcVar5 + 3),*(int *)(pcVar5 + 3) >> 0xf);
      FUN_214c_1755(uVar8,unaff_DS);
    }
    else {
      uVar8 = 0xe654;
      FUN_214c_17f7(0,0x555c,0x1000);
      FUN_214c_1755(uVar8,unaff_DS);
    }
    FUN_1000_016a(0x193);
    FUN_1000_5527(&stack0xfffe);
    FUN_1000_016a(0x194);
    FUN_1000_5527(&stack0xfffe);
    return;
  }
  if ((cVar1 != '\a') && (cVar1 != '\x06')) {
    if ((cVar1 != '\x02') && (cVar1 != '\x03')) {
      if (cVar1 == '\x04') {
        FUN_1000_016a(0x19a);
        FUN_1000_0094();
        uVar8 = (undefined2)((ulong)local_8 >> 0x10);
        pcVar4 = (char *)local_8;
        if ((*(char *)(*local_8 * 0x18 + *(int *)(pcVar4 + 1) + -0x65a2) == '\0') &&
           (param_1 == '\0')) {
          if (*(char *)(*local_8 * 0x18 + *(int *)(pcVar4 + 1) + -0x6542) == '\0') {
            uVar10 = 0xe654;
            uVar9 = unaff_DS;
            FUN_214c_17f7(0,*(int *)(pcVar4 + 1) * 0x10 + -0x5a19,unaff_DS);
            FUN_214c_1755(uVar10,uVar9);
          }
          else {
            FUN_1000_016a(0x19b);
            uVar9 = 0xe654;
            uVar8 = unaff_DS;
            FUN_214c_1799(0,CONCAT11(extraout_AH_15,0x20));
            FUN_214c_17f7(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + -0x75de,
                          unaff_DS);
            FUN_214c_1755(uVar9,uVar8);
            uVar9 = 0xe654;
            uVar8 = unaff_DS;
            FUN_214c_17f7(0,0x5566,0x214c);
            FUN_214c_17f7(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5a19,unaff_DS);
            FUN_214c_1799(0,CONCAT11(extraout_AH_16,0x29));
            FUN_214c_1755(uVar9,uVar8);
          }
        }
        else {
          uVar10 = 0xe654;
          uVar6 = 1;
          uVar9 = unaff_DS;
          FUN_214c_17f7(0,*local_8 * 0x2b8 + *(int *)(pcVar4 + 1) * 0x1d + 0x75fa,unaff_DS);
          FUN_214c_1755(uVar10,uVar9);
          uVar8 = CONCAT11(extraout_AH_10,((char *)local_8)[1]);
          puVar7 = local_28;
          FUN_214c_08af(puVar7);
          FUN_214c_08be(CONCAT11(extraout_AH_11,4));
          FUN_214c_08be(CONCAT11(extraout_AH_12,7));
          FUN_214c_08be(CONCAT11(extraout_AH_13,9));
          FUN_214c_0933(puVar7,unaff_SS,uVar8);
          if (!(bool)uVar6) {
            uVar8 = (undefined2)((ulong)local_8 >> 0x10);
            pcVar4 = (char *)local_8;
            if ((pcVar4[0x13] != '\0') || (param_1 != '\0')) {
              if (*(int *)(pcVar4 + 9) < 0) {
                uVar10 = 0xe654;
                uVar9 = unaff_DS;
                FUN_214c_1882(3,*(int *)(pcVar4 + 9),*(int *)(pcVar4 + 9) >> 0xf);
                FUN_214c_1755(uVar10,uVar9);
              }
              else {
                uVar9 = 0xe654;
                uVar8 = unaff_DS;
                FUN_214c_17f7(0,0x5560,0x214c);
                FUN_214c_1882(0,*(int *)((char *)local_8 + 9),*(int *)((char *)local_8 + 9) >> 0xf);
                FUN_214c_1755(uVar9,uVar8);
              }
            }
          }
          uVar9 = 0xe654;
          uVar8 = unaff_DS;
          FUN_214c_17f7(0,0x5566,0x214c);
          FUN_214c_17f7(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5a19,unaff_DS);
          FUN_214c_1799(0,CONCAT11(extraout_AH_14,0x29));
          FUN_214c_1755(uVar9,uVar8);
        }
        local_a = *(int *)0xb936;
        if (local_a < 1) {
          return;
        }
        local_4 = 1;
        while( true ) {
          if ((iVar3 == *(int *)(local_4 * 4 + -0x46ca)) &&
             (pcVar5 == (char *)*(undefined2 *)(local_4 * 4 + -0x46cc))) {
            uVar9 = 0xe654;
            uVar8 = unaff_DS;
            FUN_214c_17f7(0,0x5566,0x214c);
            FUN_214c_1882(0,local_4,local_4 >> 0xf);
            FUN_214c_1799(0,CONCAT11(extraout_AH_17,0x29));
            FUN_214c_1755(uVar9,uVar8);
          }
          if (local_4 == local_a) break;
          local_4 = local_4 + 1;
        }
        return;
      }
      if (cVar1 == '\x05') {
        FUN_1000_016a(0x19c);
        FUN_1000_0094();
        uVar8 = (undefined2)((ulong)local_8 >> 0x10);
        pcVar5 = (char *)local_8;
        if ((*(char *)(*local_8 * 0x18 + *(int *)(pcVar5 + 1) + -0x65a2) == '\0') &&
           (param_1 == '\0')) {
          if (*(char *)(*local_8 * 0x18 + *(int *)(pcVar5 + 1) + -0x6542) == '\0') {
            uVar9 = 0xe654;
            FUN_214c_17f7(0,*(int *)(pcVar5 + 1) * 0x10 + -0x5789,unaff_DS);
            FUN_214c_1755(uVar9,unaff_DS);
            return;
          }
          FUN_1000_016a(0x19d);
          uVar9 = 0xe654;
          uVar8 = unaff_DS;
          FUN_214c_1799(0,CONCAT11(extraout_AH_19,0x20));
          FUN_214c_17f7(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + -0x75de,unaff_DS
                       );
          FUN_214c_1755(uVar9,uVar8);
          uVar9 = 0xe654;
          uVar8 = unaff_DS;
          FUN_214c_17f7(0,0x5566,0x214c);
          FUN_214c_17f7(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5789,unaff_DS);
          FUN_214c_1799(0,CONCAT11(extraout_AH_20,0x29));
          FUN_214c_1755(uVar9,uVar8);
          return;
        }
        uVar10 = 0xe654;
        uVar9 = unaff_DS;
        FUN_214c_17f7(0,*local_8 * 0x2b8 + *(int *)(pcVar5 + 1) * 0x1d + 0x75fa,unaff_DS);
        FUN_214c_1755(uVar10,uVar9);
        if ((((char *)local_8)[0x13] != '\0') || (param_1 != '\0')) {
          uVar9 = 0xe654;
          uVar8 = unaff_DS;
          FUN_214c_17f7(0,0x5566,0x214c);
          iVar3 = *(int *)((char *)local_8 + 9);
          if (iVar3 < 0) {
            iVar3 = -iVar3;
          }
          FUN_214c_1882(0,iVar3,iVar3 >> 0xf);
          FUN_214c_17f7(0,0x5569,0x214c);
          FUN_214c_1755(uVar9,uVar8);
        }
        uVar9 = 0xe654;
        uVar8 = unaff_DS;
        FUN_214c_17f7(0,0x5566,0x214c);
        FUN_214c_17f7(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5789,unaff_DS);
        FUN_214c_1799(0,CONCAT11(extraout_AH_18,0x29));
        FUN_214c_1755(uVar9,uVar8);
        return;
      }
      if (cVar1 != '\b') {
        if (cVar1 != '\0') {
          return;
        }
        uVar8 = 0xe654;
        FUN_214c_1882(0,*(int *)(pcVar5 + 9),*(int *)(pcVar5 + 9) >> 0xf);
        FUN_214c_1755(uVar8,unaff_DS);
        FUN_1000_016a(0x19f);
        return;
      }
      if (*(int *)(pcVar5 + 1) == 0) {
        FUN_1000_016a(0x19e);
        return;
      }
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      FUN_214c_17f7(0,*(int *)(pcVar5 + 0x11) * 0x10 + -0x5629,unaff_DS);
      FUN_214c_1755(uVar9,uVar8);
      uVar8 = (undefined2)((ulong)local_8 >> 0x10);
      if (((char *)local_8)[0x13] != '\0') {
        uVar10 = 0xe654;
        uVar9 = unaff_DS;
        FUN_214c_17f7(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + 0x75fa,unaff_DS);
        FUN_214c_1755(uVar10,uVar9);
      }
      if (((char *)local_8)[0x14] != '\0') {
        return;
      }
      uVar9 = 0xe654;
      FUN_214c_17f7(0,0x5573,0x214c);
      uVar8 = (undefined2)((ulong)local_8 >> 0x10);
      FUN_214c_1882(0,*(undefined2 *)((char *)local_8 + 0xd),*(undefined2 *)((char *)local_8 + 0xf))
      ;
      FUN_214c_17f7(0,0x5577,0x214c);
      FUN_214c_1755(uVar9,unaff_DS);
      return;
    }
    if (bVar2) {
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      FUN_214c_1882(0,*(int *)(pcVar5 + 3),*(int *)(pcVar5 + 3) >> 0xf);
      FUN_214c_1755(uVar9,uVar8);
    }
    else if (*param_3 == '\x02') {
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      FUN_214c_17f7(0,0x555c,0x1000);
      FUN_214c_1755(uVar9,uVar8);
    }
    else {
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      FUN_214c_17f7(0,0x5563,0x1000);
      FUN_214c_1755(uVar9,uVar8);
    }
    if (*param_3 == '\x02') {
      FUN_1000_016a(0x196);
    }
    else {
      FUN_1000_016a(0x197);
    }
    FUN_1000_5527(&stack0xfffe);
    uVar8 = (undefined2)((ulong)local_8 >> 0x10);
    if ((*(char *)(*local_8 * 0x18 + *(int *)((char *)local_8 + 1) + -0x65a2) != '\0') ||
       (param_1 != '\0')) {
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      FUN_214c_1799(0,CONCAT11((char)((uint)(*local_8 * 0x18) >> 8),0x20));
      FUN_214c_17f7(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + 0x75fa,unaff_DS);
      FUN_214c_1755(uVar9,uVar8);
      uVar6 = *param_3 == '\x02';
      if ((bool)uVar6) {
        uVar8 = CONCAT11(extraout_AH_01,pcVar5[1]);
        puVar7 = local_28;
        FUN_214c_08af(puVar7);
        FUN_214c_08df(CONCAT11(extraout_AH_02,0xd),CONCAT11(extraout_AH_02,6));
        FUN_214c_0933(puVar7,unaff_SS,uVar8);
        if (!(bool)uVar6) {
          FUN_1000_5527(&stack0xfffe);
        }
        uVar9 = 0xe654;
        uVar8 = unaff_DS;
        FUN_214c_17f7(0,0x5566,0x214c);
        FUN_214c_17f7(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5cc9,unaff_DS);
        FUN_214c_1799(0,CONCAT11(extraout_AH_03,0x29));
        FUN_214c_1755(uVar9,uVar8);
        return;
      }
      uVar8 = CONCAT11(extraout_AH_01,pcVar5[1]);
      puVar7 = local_28;
      FUN_214c_08af(puVar7);
      FUN_214c_08be(CONCAT11(extraout_AH_04,3));
      FUN_214c_08be(CONCAT11(extraout_AH_05,9));
      FUN_214c_0933(puVar7,unaff_SS,uVar8);
      if ((bool)uVar6) {
        return;
      }
      FUN_1000_5527(&stack0xfffe);
      return;
    }
    if (*(char *)(*local_8 * 0x18 + *(int *)((char *)local_8 + 1) + -0x6542) != '\0') {
      FUN_1000_016a(0x198);
      if (*local_8 == '\x02') {
        uVar9 = 0xe654;
        uVar8 = unaff_DS;
        FUN_214c_1799(0,CONCAT11(extraout_AH_06,0x65));
        FUN_214c_1755(uVar9,uVar8);
      }
      FUN_1000_5527(&stack0xfffe);
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      FUN_214c_1799(0,CONCAT11(extraout_AH_07,0x20));
      FUN_214c_17f7(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + -0x75de,unaff_DS);
      FUN_214c_1755(uVar9,uVar8);
      if (*local_8 != '\x02') {
        return;
      }
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      FUN_214c_17f7(0,0x5566,0x214c);
      FUN_214c_17f7(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5cc9,unaff_DS);
      FUN_214c_1755(uVar9,uVar8);
      FUN_1000_5527(&stack0xfffe);
      uVar8 = 0xe654;
      FUN_214c_1799(0,CONCAT11(extraout_AH_08,0x29));
      FUN_214c_1755(uVar8,unaff_DS);
      return;
    }
    if (*local_8 == '\x03') {
      FUN_1000_016a(0x199);
      FUN_1000_5527(&stack0xfffe);
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      FUN_214c_1799(0,CONCAT11(extraout_AH_09,0x20));
      FUN_214c_17f7(0,*(int *)((char *)local_8 + 1) * 0x1d + -0x610e,unaff_DS);
      FUN_214c_1755(uVar9,uVar8);
      return;
    }
    if (*local_8 != '\x02') {
      return;
    }
    uVar9 = 0xe654;
    uVar8 = unaff_DS;
    FUN_214c_1799(0,CONCAT11((char)((uint)(*local_8 * 0x18) >> 8),0x20));
    FUN_214c_17f7(0,*(int *)((char *)local_8 + 1) * 0x10 + -0x5cc9,unaff_DS);
    FUN_214c_1755(uVar9,uVar8);
    FUN_1000_5527(&stack0xfffe);
    return;
  }
  uVar6 = *param_3 == '\x06';
  if ((bool)uVar6) {
    uVar8 = CONCAT11(extraout_AH,pcVar5[1]);
    puVar7 = local_28;
    FUN_214c_08af(puVar7);
    FUN_214c_08df(CONCAT11(extraout_AH_00,0xb),CONCAT11(extraout_AH_00,9));
    FUN_214c_0933(puVar7,unaff_SS,uVar8);
    if (!(bool)uVar6) {
      uVar8 = (undefined2)((ulong)local_8 >> 0x10);
      if (((char *)local_8)[0x13] == '\0') {
        FUN_1000_016a(0x1a8);
      }
      else {
        uVar10 = 0xe654;
        uVar9 = unaff_DS;
        FUN_214c_17f7(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + 0x75fa,unaff_DS);
        FUN_214c_1755(uVar10,uVar9);
      }
      goto LAB_1000_5755;
    }
  }
  if (*(int *)(pcVar5 + 1) == 0xc) {
    uVar9 = 0xe654;
    uVar8 = unaff_DS;
    FUN_214c_1882(0,*(int *)(pcVar5 + 3),*(int *)(pcVar5 + 3) >> 0xf);
    FUN_214c_1755(uVar9,uVar8);
  }
  uVar9 = 0xe654;
  uVar8 = unaff_DS;
  FUN_214c_17f7(0,*local_8 * 0x2b8 + *(int *)((char *)local_8 + 1) * 0x1d + 0x75fa,unaff_DS);
  FUN_214c_1755(uVar9,uVar8);
  if (1 < *(int *)(pcVar5 + 3)) {
    FUN_1000_5527(&stack0xfffe);
  }
  uVar8 = (undefined2)((ulong)local_8 >> 0x10);
  pcVar4 = (char *)local_8;
  if ((pcVar4[0x13] != '\0') || (param_1 != '\0')) {
    if (*(int *)(pcVar4 + 9) < 0) {
      uVar10 = 0xe654;
      uVar9 = unaff_DS;
      FUN_214c_1882(3,*(int *)(pcVar4 + 9),*(int *)(pcVar4 + 9) >> 0xf);
      FUN_214c_1755(uVar10,uVar9);
    }
    else {
      uVar9 = 0xe654;
      uVar8 = unaff_DS;
      FUN_214c_17f7(0,0x5560,0x214c);
      FUN_214c_1882(0,*(int *)((char *)local_8 + 9),*(int *)((char *)local_8 + 9) >> 0xf);
      FUN_214c_1755(uVar9,uVar8);
    }
  }
LAB_1000_5755:
  if ((((((iVar3 == *(int *)0xb924) && (pcVar5 == (char *)*(undefined2 *)0xb922)) ||
        ((iVar3 == *(int *)0xb928 && (pcVar5 == (char *)*(undefined2 *)0xb926)))) ||
       ((iVar3 == *(int *)0xb92c && (pcVar5 == (char *)*(undefined2 *)0xb92a)))) ||
      ((iVar3 == *(int *)0xb934 && (pcVar5 == (char *)*(undefined2 *)0xb932)))) ||
     ((iVar3 == *(int *)0xb930 && (pcVar5 == (char *)*(undefined2 *)0xb92e)))) {
    FUN_1000_016a(0x195);
  }
  return;
}



void __cdecl16near FUN_1000_5fd2(void)

{
  undefined4 *puVar1;
  undefined1 extraout_AH;
  int iVar2;
  byte extraout_AH_00;
  undefined1 uVar3;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined2 unaff_DS;
  undefined2 uVar4;
  undefined2 uVar5;
  int local_8;
  uint local_6;
  uint local_4;
  
  local_4 = (uint)((ulong)*(undefined4 *)0xb91e >> 0x10);
  local_6 = (uint)*(undefined4 *)0xb91e;
  if (local_6 == 0 && local_4 == 0) {
    FUN_1000_016a(0xbd);
    uVar3 = extraout_AH;
  }
  else {
    local_8 = 0;
    while (local_6 != 0 || local_4 != 0) {
      iVar2 = local_8 + 1;
      FUN_20e6_0260(iVar2,CONCAT11((char)((uint)iVar2 >> 8),1));
      FUN_20e6_0227();
      if (iVar2 < 0x1b) {
        uVar4 = 0xe654;
        uVar5 = unaff_DS;
        FUN_214c_1799(2,local_8 + 0x61);
        FUN_214c_1755(uVar4,uVar5);
      }
      else {
        uVar4 = 0xe654;
        uVar5 = unaff_DS;
        FUN_214c_1799(2,local_8 + 0x27);
        FUN_214c_1755(uVar4,uVar5);
      }
      uVar4 = 0xe654;
      uVar5 = unaff_DS;
      FUN_214c_17f7(0,0x5fce,0x214c);
      FUN_214c_1755(uVar4,uVar5);
      FUN_1000_557c((uint)extraout_AH_00 << 8,CONCAT11(extraout_AH_00,1),local_6,local_4);
      FUN_214c_173c(0x214c,0xe654);
      puVar1 = (undefined4 *)(local_6 + 0x16);
      local_4 = (uint)((ulong)*puVar1 >> 0x10);
      local_6 = (uint)*puVar1;
      local_8 = iVar2;
      if (((iVar2 == 0x18) || (iVar2 == 0x30)) && ((local_6 | local_4) != 0)) {
        uVar3 = (undefined1)((local_6 | local_4) >> 8);
        FUN_20e6_0260(CONCAT11(uVar3,0x41),CONCAT11(uVar3,0x19));
        FUN_1000_1448();
        FUN_20e6_020d();
        FUN_20e6_0260(CONCAT11(extraout_AH_01,1),CONCAT11(extraout_AH_01,1));
      }
    }
    uVar3 = 0;
  }
  FUN_20e6_0260(CONCAT11(uVar3,0x19),CONCAT11(uVar3,1));
  FUN_20e6_0227();
  FUN_20e6_0260(CONCAT11(extraout_AH_02,0x19),CONCAT11(extraout_AH_02,0x41));
  FUN_1000_1448();
  if (local_8 < 0x18) {
    FUN_1000_11fc(local_8);
  }
  else {
    FUN_1000_11fc(0x17);
  }
  return;
}



void FUN_1000_610b(char param_1)

{
  int iVar1;
  char *pcVar2;
  bool bVar3;
  byte extraout_AH;
  undefined2 unaff_DS;
  undefined2 uVar4;
  undefined2 uVar5;
  int local_b;
  int local_9;
  char *local_6;
  int local_4;
  
  FUN_1000_0040();
  local_b = 0;
  local_9 = 0;
  iVar1 = *(int *)(param_1 * 4 + -0x4736);
  if ((iVar1 < 1) && ((iVar1 < 0 || (*(uint *)(param_1 * 4 + -0x4738) < 2)))) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  pcVar2 = (char *)*(undefined4 *)0xb91e;
  while( true ) {
    local_6 = (char *)pcVar2;
    local_4 = (int)((ulong)pcVar2 >> 0x10);
    if (local_6 == (char *)0x0 && local_4 == 0) break;
    if (param_1 == *pcVar2) {
      local_9 = local_9 + 1;
      FUN_20e6_0260(local_9,CONCAT11((char)((uint)local_9 >> 8),1));
      FUN_20e6_0227();
      if (local_b + 1 < 0x1b) {
        uVar4 = 0xe654;
        uVar5 = unaff_DS;
        FUN_214c_1799(2,local_b + 0x61);
        FUN_214c_1755(uVar4,uVar5);
      }
      else {
        uVar4 = 0xe654;
        uVar5 = unaff_DS;
        FUN_214c_1799(2,local_b + 0x27);
        FUN_214c_1755(uVar4,uVar5);
      }
      uVar4 = 0xe654;
      uVar5 = unaff_DS;
      FUN_214c_17f7(0,0x6108,0x214c);
      FUN_214c_1755(uVar4,uVar5);
      FUN_20e6_0227();
      FUN_1000_557c((uint)extraout_AH << 8,CONCAT11(extraout_AH,1),local_6,local_4);
      if (bVar3) {
        FUN_214c_173c(0x20e6,0xe654);
      }
    }
    pcVar2 = *(char **)(local_6 + 0x16);
    local_b = local_b + 1;
  }
  if (bVar3) {
    FUN_20e6_0260(local_9 + 1,0x41);
    FUN_1000_1448();
    if (local_9 < 0x17) {
      FUN_1000_11fc(local_9 + 1);
    }
    else {
      FUN_1000_11fc(0x17);
    }
  }
  else {
    FUN_1000_1448();
  }
  return;
}



void __cdecl16near FUN_1000_6249(void)

{
  undefined1 extraout_AH;
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 local_4;
  
  uVar1 = 0x20e6;
  FUN_20e6_020d();
  local_4 = 0x134;
  while( true ) {
    if ((local_4 == 0x13e) || (uVar2 = uVar1, local_4 == 0x144)) {
      uVar2 = 0x214c;
      FUN_214c_173c(uVar1,0xe654);
    }
    FUN_1000_016a(local_4);
    uVar1 = 0x214c;
    FUN_214c_173c(uVar2,0xe654);
    if (local_4 == 0x146) break;
    local_4 = local_4 + 1;
  }
  FUN_20e6_0260(CONCAT11(extraout_AH,0x19),CONCAT11(extraout_AH,0x41));
  FUN_1000_1448();
  FUN_1000_11fc(0x17);
  return;
}



void __cdecl16near FUN_1000_62b7(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  undefined1 uVar6;
  undefined2 unaff_DS;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 local_4;
  
  FUN_20e6_020d();
  uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
  local_4 = (uint)((ulong)uVar2 >> 0x10);
  uVar3 = (uint)uVar2;
  while (uVar6 = (undefined1)((uVar3 | local_4) >> 8), (uVar3 | local_4) != 0) {
    uVar7 = 0xe654;
    uVar8 = unaff_DS;
    FUN_214c_1799(0,CONCAT11(uVar6,*(undefined1 *)(uVar3 + 1)));
    FUN_214c_17f7(0,0x62a6,0x214c);
    FUN_214c_1882(4,*(int *)(uVar3 + 10),*(int *)(uVar3 + 10) >> 0xf);
    FUN_214c_1882(4,*(int *)(uVar3 + 0xc),*(int *)(uVar3 + 0xc) >> 0xf);
    FUN_214c_1882(4,*(int *)(uVar3 + 8),*(int *)(uVar3 + 8) >> 0xf);
    FUN_214c_1882(4,*(int *)(uVar3 + 0x10),*(int *)(uVar3 + 0x10) >> 0xf);
    FUN_214c_1755(uVar7,uVar8);
    uVar5 = *(uint *)(uVar3 + 0x2e) | *(uint *)(uVar3 + 0x30);
    if (uVar5 != 0) {
      uVar6 = (undefined1)(uVar5 >> 8);
      FUN_1000_557c(CONCAT11(uVar6,1),CONCAT11(uVar6,1),*(undefined2 *)(uVar3 + 0x2e),
                    *(undefined2 *)(uVar3 + 0x30));
    }
    uVar7 = 0xe654;
    uVar8 = unaff_DS;
    FUN_214c_17f7(0,0x62a9,0x214c);
    FUN_214c_1882(4,*(int *)(uVar3 + 0x1c),*(int *)(uVar3 + 0x1c) >> 0xf);
    FUN_214c_17f7(0,0x62ad,0x214c);
    FUN_214c_1882(4,*(int *)(uVar3 + 0x1e),*(int *)(uVar3 + 0x1e) >> 0xf);
    FUN_214c_1755(uVar7,uVar8);
    if (*(char *)(uVar3 + 0x28) == '\0') {
      FUN_214c_173c(0x214c,0xe654);
    }
    else {
      uVar8 = 0xe654;
      FUN_214c_17f7(0,0x62b1,0x214c);
      FUN_214c_173c(0x214c,uVar8);
    }
    bVar4 = FUN_20e6_0298();
    if (0x16 < bVar4) {
      FUN_1000_1448();
      FUN_20e6_020d();
    }
    puVar1 = (undefined4 *)(uVar3 + 0x32);
    local_4 = (uint)((ulong)*puVar1 >> 0x10);
    uVar3 = (uint)*puVar1;
  }
  FUN_20e6_0260(CONCAT11(uVar6,0x19),CONCAT11(uVar6,0x41));
  FUN_1000_1448();
  FUN_1000_11fc(0x17);
  return;
}



void __cdecl16near FUN_1000_6431(void)

{
  int iVar1;
  byte bVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 uVar3;
  undefined2 unaff_DS;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined4 local_6;
  
  FUN_20e6_020d();
  local_6 = (char *)*(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  while( true ) {
    if ((char *)local_6 == (char *)0x0 && local_6._2_2_ == 0) break;
    while( true ) {
      if ((char *)local_6 == (char *)0x0 && local_6._2_2_ == 0) break;
      uVar4 = 0xe654;
      uVar5 = unaff_DS;
      FUN_214c_1882(4,*(int *)((char *)local_6 + 5),*(int *)((char *)local_6 + 5) >> 0xf);
      FUN_214c_1882(4,*(int *)((char *)local_6 + 7),*(int *)((char *)local_6 + 7) >> 0xf);
      FUN_214c_1799(0,CONCAT11(extraout_AH,0x20));
      FUN_214c_1755(uVar4,uVar5);
      uVar3 = extraout_AH_00;
      if (*local_6 == '\x05') {
        uVar4 = 0xe654;
        iVar1 = *(int *)(*(int *)((char *)local_6 + 1) * 4 + -0x6243);
        uVar5 = unaff_DS;
        FUN_214c_1882(2,iVar1,iVar1 >> 0xf);
        FUN_214c_1755(uVar4,uVar5);
        uVar3 = extraout_AH_01;
      }
      FUN_1000_557c(CONCAT11(uVar3,1),CONCAT11(uVar3,1),(char *)local_6,local_6._2_2_);
      FUN_214c_173c(0x214c,0xe654);
      local_6 = *(char **)((char *)local_6 + 0x16);
      bVar2 = FUN_20e6_0298();
      if (0x16 < bVar2) {
        FUN_1000_1448();
        FUN_20e6_020d();
      }
    }
  }
  FUN_20e6_0260(0x19,0x41);
  FUN_1000_1448();
  FUN_1000_11fc(0x17);
  return;
}



void __cdecl16near FUN_1000_65d3(void)

{
  char cVar1;
  undefined1 extraout_AH;
  undefined2 uVar2;
  undefined2 extraout_DX;
  undefined2 unaff_DS;
  undefined2 uVar3;
  undefined2 uVar4;
  
  FUN_20e6_020d();
  uVar4 = 0xe654;
  FUN_214c_17f7(0,0x6527,0x20e6);
  FUN_214c_1882(4,*(int *)0xe52f,*(int *)0xe52f >> 0xf);
  FUN_214c_1882(4,*(int *)0xe531,*(int *)0xe531 >> 0xf);
  FUN_214c_173c(0x214c,uVar4);
  uVar4 = 0xe654;
  FUN_214c_17f7(0,0x652b,0x214c);
  FUN_214c_1882(5,*(int *)0xb892,*(int *)0xb892 >> 0xf);
  FUN_214c_1882(5,*(int *)0xb909,*(int *)0xb909 >> 0xf);
  FUN_214c_173c(0x214c,uVar4);
  FUN_214c_1882(4,*(int *)0xb8c4,*(int *)0xb8c4 >> 0xf);
  FUN_214c_1799(0,CONCAT11(extraout_AH,0x2f));
  FUN_214c_1882(0,*(int *)0xb8c6,*(int *)0xb8c6 >> 0xf);
  FUN_214c_17f7(0,0x652f,0x214c);
  FUN_214c_1882(0,*(int *)0xb8c2,*(int *)0xb8c2 >> 0xf);
  FUN_214c_173c(0x214c);
  uVar4 = 0xe654;
  FUN_214c_17f7(0,0x6533,0x214c);
  FUN_214c_173c(0x214c,uVar4);
  uVar4 = 0xe654;
  FUN_214c_17f7(0,0x653e,0x214c);
  FUN_214c_173c(0x214c,uVar4);
  FUN_214c_17f7(0,0x654d,0x214c);
  FUN_214c_173c(0x214c);
  FUN_214c_17f7(0,0x6565,0x214c);
  FUN_214c_173c(0x214c);
  FUN_214c_17f7(0,0x657d,0x214c);
  FUN_214c_173c(0x214c);
  FUN_214c_17f7(0,0x658a,0x214c);
  FUN_214c_173c(0x214c);
  FUN_214c_17f7(0,0x6596,0x214c);
  FUN_214c_173c(0x214c);
  FUN_214c_17f7(0,0x65a4,0x214c);
  FUN_214c_173c(0x214c);
  FUN_214c_17f7(0,0x65b5,0x214c);
  FUN_214c_173c(0x214c);
  uVar3 = 0xe654;
  FUN_214c_17f7(0,0x65c9,0x214c);
  FUN_214c_173c(0x214c);
  uVar4 = extraout_DX;
  cVar1 = FUN_20e6_0357();
  if (cVar1 == 'v') {
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb870 = uVar4;
    FUN_214c_16ef(0x214c);
  }
  else if (cVar1 == 'm') {
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb872 = uVar4;
    FUN_214c_16ef(0x214c);
  }
  else if (cVar1 == 'e') {
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb888 = uVar4;
    FUN_214c_16ef(0x214c);
  }
  else if (cVar1 == 'x') {
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb886 = uVar4;
    FUN_214c_16ef(0x214c);
  }
  else if (cVar1 == 'f') {
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb874 = uVar4;
    FUN_214c_16ef(0x214c);
  }
  else if (cVar1 == 's') {
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb909 = uVar4;
    FUN_214c_16ef(0x214c);
  }
  else if (cVar1 == 'a') {
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb880 = uVar4;
    FUN_214c_16ef(0x214c);
  }
  else if (cVar1 == 'd') {
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb878 = uVar4;
    FUN_214c_16ef(0x214c);
  }
  else if (cVar1 == 'i') {
    uVar4 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb87a = uVar4;
    FUN_214c_16ef(0x214c);
  }
  else if (cVar1 == 'o') {
    uVar2 = FUN_214c_182b(0xe554);
    *(undefined2 *)0xb8c8 = uVar2;
    *(undefined2 *)0xb8ca = uVar4;
    FUN_214c_16ef(0x214c);
  }
  FUN_1000_11fc(0x17,uVar3);
  return;
}



void __cdecl16near FUN_1000_6887(void)

{
  undefined4 uVar1;
  undefined2 unaff_DS;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 local_8;
  undefined2 local_6;
  
  local_8 = 1;
  while( true ) {
    local_6 = 1;
    while( true ) {
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      if (*(char *)((int)uVar1 + local_8 * 0x4f + local_6 + -0x50) != ' ') {
        FUN_20e6_0260(local_8 + 1,CONCAT11((char)((uint)(local_8 * 0x4f) >> 8),(undefined1)local_6))
        ;
        uVar2 = 0xe654;
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        uVar3 = unaff_DS;
        FUN_214c_1799(0,CONCAT11((char)((uint)(local_8 * 0x4f) >> 8),
                                 *(undefined1 *)((int)uVar1 + local_8 * 0x4f + local_6 + -0x50)));
        FUN_214c_1755(uVar2,uVar3);
      }
      if (local_6 == 0x4f) break;
      local_6 = local_6 + 1;
    }
    if (local_8 == 0x17) break;
    local_8 = local_8 + 1;
  }
  return;
}



void __cdecl16near FUN_1000_6921(void)

{
  char cVar1;
  int iVar2;
  undefined2 uVar3;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 unaff_SS;
  undefined1 uVar4;
  undefined2 uVar5;
  undefined1 *puVar6;
  undefined1 local_177 [32];
  char local_157;
  undefined1 local_156 [81];
  char local_105;
  int local_104;
  undefined1 local_102 [256];
  
  local_157 = '\x01';
  FUN_214c_1383(0x6917,0x1000,local_102,unaff_SS);
  FUN_214c_13f3(0x214c,local_102);
  iVar2 = FUN_214c_026d();
  if (iVar2 == 0) {
    while ((local_157 != '\0' && (cVar1 = FUN_214c_18d2(local_102,unaff_SS), cVar1 == '\0'))) {
      FUN_20e6_020d();
      local_104 = 1;
      while( true ) {
        cVar1 = FUN_214c_18d2(local_102,unaff_SS);
        if (cVar1 == '\0') {
          puVar6 = local_102;
          FUN_214c_17be(0x50,local_156,unaff_SS);
          FUN_214c_16ef(0x214c,puVar6);
          uVar5 = 0xe654;
          FUN_214c_17f7(0,local_156,unaff_SS);
          FUN_214c_173c(0x214c,uVar5);
        }
        uVar4 = local_104 == 0x18;
        if ((bool)uVar4) break;
        local_104 = local_104 + 1;
      }
      FUN_20e6_0260(0x28,0x19);
      FUN_1000_016a(0x52);
      do {
        uVar3 = FUN_20e6_0357();
        local_105 = (char)uVar3;
        puVar6 = local_177;
        uVar5 = unaff_SS;
        FUN_214c_08af(puVar6);
        FUN_214c_08be(CONCAT11(extraout_AH,0x20));
        FUN_214c_08be(CONCAT11(extraout_AH_00,0x66));
        FUN_214c_08be(CONCAT11(extraout_AH_01,0x46));
        FUN_214c_0933(puVar6,uVar5,uVar3);
      } while ((bool)uVar4);
      local_157 = local_105 == ' ';
    }
  }
  else {
    FUN_20e6_020d();
    FUN_1000_016a(0x14a);
    FUN_1000_1448();
  }
  return;
}



void __cdecl16near FUN_1000_6a56(void)

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
  int iVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar2;
  bool bVar3;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined1 local_4c [32];
  int local_2c;
  undefined1 local_28 [32];
  int local_8;
  uint local_6;
  uint local_4;
  
  FUN_20e6_020d();
  local_6 = 1;
  local_4 = 3;
  FUN_1000_016a(0xb6);
  uVar7 = 0xe654;
  FUN_214c_1799(0,CONCAT11(extraout_AH,0x20));
  uVar2 = 1;
  FUN_214c_17f7(0,0xb84f,unaff_DS);
  FUN_214c_173c(0x214c,uVar7);
  FUN_214c_173c(0x214c,0xe654);
  local_8 = 1;
  while( true ) {
    uVar6 = CONCAT11((char)((uint)(local_8 * 0x2a) >> 8),*(undefined1 *)(local_8 * 0x2a + -0x5007));
    puVar5 = local_28;
    uVar7 = unaff_SS;
    FUN_214c_0885(0x20,0xb82f,unaff_DS);
    FUN_214c_0933(puVar5,uVar7,uVar6);
    if (((bool)uVar2) && (0 < *(int *)(local_8 * 2 + -0x460b))) {
      FUN_20e6_0260(local_4 & 0xff,local_6 & 0xff);
      _local_2c = CONCAT22(unaff_DS,local_8 * 0x2a + -0x5017);
      iVar1 = local_8 * 5 + -0x4a34;
      bVar3 = iVar1 == 0;
      FUN_214c_0783(0x6a3c,0x20e6,iVar1,unaff_DS);
      if (!bVar3) {
        uVar6 = 0xe654;
        iVar1 = *(int *)(local_8 * 2 + -0x460b);
        uVar7 = unaff_DS;
        FUN_214c_1882(4,iVar1,iVar1 >> 0xf);
        FUN_214c_1799(0,CONCAT11(extraout_AH_00,0x20));
        FUN_214c_1755(uVar6,uVar7);
      }
      if ((*(int *)(local_8 * 2 + -0x460b) < 2) || (*(char *)((int)_local_2c + 0x10) != 'E')) {
        uVar6 = 0xe654;
        uVar7 = unaff_DS;
        FUN_214c_17f7(0,local_8 * 0x2a + -0x5017,unaff_DS);
        FUN_214c_1755(uVar6,uVar7);
        uVar2 = extraout_AH_02;
      }
      else {
        uVar6 = 0xe654;
        uVar7 = unaff_DS;
        FUN_214c_17f7(0,0x6a3d,0x214c);
        FUN_214c_1755(uVar6,uVar7);
        uVar2 = extraout_AH_01;
      }
      iVar1 = *(int *)(local_8 * 2 + -0x460b);
      uVar4 = iVar1 == 1;
      if (1 < iVar1) {
        uVar6 = CONCAT11(uVar2,*(undefined1 *)((int)_local_2c + 0x10));
        puVar5 = local_4c;
        uVar7 = unaff_SS;
        FUN_214c_08af(puVar5);
        FUN_214c_08be(CONCAT11(extraout_AH_03,0x43));
        FUN_214c_08be(CONCAT11(extraout_AH_04,0x45));
        FUN_214c_0933(puVar5,uVar7,uVar6);
        if ((bool)uVar4) {
          uVar6 = 0xe654;
          uVar7 = unaff_DS;
          FUN_214c_1799(0,CONCAT11(extraout_AH_05,0x73));
          FUN_214c_1755(uVar6,uVar7);
        }
      }
      FUN_214c_173c(0x214c,0xe654);
      local_4 = local_4 + 1;
      if (0x17 < (int)local_4) {
        local_6 = local_6 + 0x27;
        local_4 = 3;
      }
    }
    if (local_8 == 0x23) break;
    local_8 = local_8 + 1;
    uVar2 = local_8 == 0;
  }
  FUN_20e6_0260(local_4 & 0xff,local_6 & 0xff);
  if (*(int *)0xba39 != 0) {
    uVar6 = 0xe654;
    uVar7 = unaff_DS;
    FUN_214c_17f7(0,0x6a43,0x20e6);
    FUN_214c_1755(uVar6,uVar7);
  }
  local_4 = local_4 + 1;
  FUN_20e6_0260(local_4,CONCAT11((char)(local_4 >> 8),(undefined1)local_6));
  uVar2 = extraout_AH_06;
  if (*(int *)0xba3b != 0) {
    uVar7 = 0xe654;
    FUN_214c_17f7(0,0x6a4c,0x20e6);
    FUN_214c_1755(uVar7,unaff_DS);
    uVar2 = extraout_AH_07;
  }
  FUN_20e6_0260(CONCAT11(uVar2,0x19),CONCAT11(uVar2,0x41));
  FUN_1000_1448();
  FUN_1000_11fc(0x17);
  return;
}



void __cdecl16near FUN_1000_6c94(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  byte bVar6;
  int iVar7;
  undefined2 uVar8;
  uint uVar9;
  undefined2 uVar10;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar11;
  byte *local_10e;
  int local_108;
  int local_106;
  undefined1 local_102 [256];
  
  local_106 = 1;
  FUN_214c_1383(0x6c89,0x1000,local_102,unaff_SS);
  FUN_214c_13f3(0x214c,local_102);
  iVar7 = FUN_214c_026d();
  if (iVar7 == 0) {
    while ((cVar5 = FUN_214c_18d2(local_102,unaff_SS), cVar5 == '\0' && (local_106 != 0x10))) {
      iVar4 = local_106 * 0x18;
      _local_10e = (byte *)CONCAT22(unaff_DS,(byte *)(iVar4 + -0x45db));
      puVar11 = local_102;
      uVar8 = unaff_SS;
      FUN_214c_177f(puVar11);
      FUN_214c_1712(puVar11,uVar8);
      uVar10 = 0;
      uVar8 = FUN_214c_02dc();
      *(undefined2 *)(iVar4 + -0x45c9) = uVar8;
      *(undefined2 *)(iVar4 + -0x45c7) = uVar10;
      puVar11 = local_102;
      uVar8 = unaff_SS;
      bVar6 = FUN_214c_177f(puVar11);
      FUN_214c_1712(puVar11,uVar8);
      uVar9 = (uint)bVar6 * 0x100;
      uVar1 = *(uint *)(iVar4 + -0x45c9);
      iVar7 = *(int *)(iVar4 + -0x45c7);
      *(int *)(iVar4 + -0x45c9) = uVar9 + *(uint *)(iVar4 + -0x45c9);
      *(int *)(iVar4 + -0x45c7) = ((int)uVar9 >> 0xf) + iVar7 + (uint)CARRY2(uVar9,uVar1);
      puVar11 = local_102;
      uVar8 = unaff_SS;
      bVar6 = FUN_214c_177f(puVar11);
      FUN_214c_1712(puVar11,uVar8);
      uVar1 = *(uint *)(iVar4 + -0x45c9);
      iVar7 = *(int *)(iVar4 + -0x45c7);
      *(int *)(iVar4 + -0x45c9) = (uint)bVar6 + *(uint *)(iVar4 + -0x45c9);
      *(int *)(iVar4 + -0x45c7) = iVar7 + (uint)CARRY2((uint)bVar6,uVar1);
      iVar7 = *(int *)(iVar4 + -0x45c9);
      puVar11 = local_102;
      uVar8 = unaff_SS;
      bVar6 = FUN_214c_177f(puVar11);
      FUN_214c_1712(puVar11,uVar8);
      *(int *)(iVar4 + -0x45cb) = (int)(bVar6 - 0x32) / 2;
      iVar2 = *(int *)(iVar4 + -0x45cb);
      puVar11 = local_102;
      uVar8 = unaff_SS;
      bVar6 = FUN_214c_177f(puVar11);
      FUN_214c_1712(puVar11,uVar8);
      *(uint *)(iVar4 + -0x45c5) = (uint)bVar6;
      iVar3 = *(int *)(iVar4 + -0x45c5);
      puVar11 = local_102;
      uVar8 = unaff_SS;
      bVar6 = FUN_214c_177f(puVar11);
      FUN_214c_1712(puVar11,uVar8);
      puVar11 = local_102;
      FUN_214c_17be(0xf,(byte *)(iVar4 + -0x45db),unaff_DS);
      FUN_214c_16ef(0x214c,puVar11);
      if ((int)((uint)*_local_10e + iVar7 + iVar2 + iVar3 + (uint)*(byte *)(iVar4 + -0x45da)) %
          0x100 == (uint)bVar6) {
        local_106 = local_106 + 1;
      }
    }
  }
  if (local_106 < 0x10) {
    local_108 = local_106;
    while( true ) {
      iVar7 = local_108 * 0x18;
      _local_10e = (byte *)CONCAT22(unaff_DS,(undefined1 *)(iVar7 + -0x45db));
      *_local_10e = 0;
      *(undefined2 *)(iVar7 + -0x45c9) = 0;
      *(undefined2 *)(iVar7 + -0x45c7) = 0;
      *(undefined2 *)(iVar7 + -0x45c5) = 0x20;
      if (local_108 == 0xf) break;
      local_108 = local_108 + 1;
    }
  }
  FUN_214c_1456(local_102,unaff_SS);
  return;
}



void __cdecl16near FUN_1000_6f02(void)

{
  int iVar1;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  uint uVar2;
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
  int local_4;
  
  uVar5 = 0xe654;
  uVar7 = unaff_DS;
  FUN_214c_1799(0,0xda);
  FUN_214c_1755(uVar5,uVar7);
  local_4 = 1;
  while( true ) {
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    FUN_214c_1799(0,0xc4);
    FUN_214c_1755(uVar5,uVar7);
    if (local_4 == 0x4e) break;
    local_4 = local_4 + 1;
  }
  uVar5 = 0xe654;
  uVar7 = unaff_DS;
  FUN_214c_1799(0,0xbf);
  FUN_214c_1755(uVar5,uVar7);
  uVar5 = 0xe654;
  uVar7 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(extraout_AH,0xb3));
  FUN_214c_1755(uVar5,uVar7);
  uVar7 = CONCAT11(extraout_AH_00,0x22);
  uVar5 = FUN_20e6_0298(uVar7);
  FUN_20e6_0260(uVar5,uVar7);
  FUN_1000_016a(0x7b);
  uVar5 = 0xe654;
  uVar7 = unaff_DS;
  FUN_214c_1799(0x1f,CONCAT11(extraout_AH_01,0xb3));
  FUN_214c_1799(0,CONCAT11(extraout_AH_02,0xb3));
  FUN_214c_1799(0x4f,CONCAT11(extraout_AH_03,0xb3));
  FUN_214c_1755(uVar5,uVar7);
  for (local_4 = 1; local_4 < 0x10; local_4 = local_4 + 1) {
    iVar1 = *(int *)(local_4 * 0x18 + -0x45c7);
    if ((iVar1 < 1) && ((iVar1 < 0 || (*(int *)(local_4 * 0x18 + -0x45c9) == 0)))) break;
    _local_8 = CONCAT22(unaff_DS,local_4 * 0x18 + -0x45db);
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    FUN_214c_1799(0,CONCAT11((char)((uint)(local_4 * 0x18) >> 8),0xb3));
    FUN_214c_1755(uVar5,uVar7);
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    FUN_214c_17f7(0,(int)_local_8,(int)((ulong)_local_8 >> 0x10));
    FUN_214c_1755(uVar5,uVar7);
    uVar7 = CONCAT11(extraout_AH_04,0x14);
    uVar5 = FUN_20e6_0298(uVar7);
    FUN_20e6_0260(uVar5,uVar7);
    uVar3 = 1;
    FUN_1000_22c8(0,*(undefined2 *)((int)_local_8 + 0x16));
    uVar5 = CONCAT11(extraout_AH_05,*(undefined1 *)((int)_local_8 + 0x16));
    puVar4 = local_28;
    uVar7 = unaff_SS;
    FUN_214c_08af(puVar4);
    FUN_214c_08df(CONCAT11(extraout_AH_06,0x23),CONCAT11(extraout_AH_06,1));
    uVar2 = FUN_214c_0933(puVar4,uVar7,uVar5);
    if (!(bool)uVar3) {
      FUN_1000_0499(uVar2 & 0xff00,*(undefined2 *)((int)_local_8 + 0x16));
    }
    if (*(char *)((int)_local_8 + 0x16) != 'g') {
      uVar5 = 0xe654;
      uVar7 = unaff_DS;
      FUN_214c_17f7(0,0x6ee2,0x214c);
      iVar1 = *(int *)((int)_local_8 + 0x10);
      FUN_214c_1882(0,iVar1,iVar1 >> 0xf);
      FUN_214c_1755(uVar5,uVar7);
    }
    uVar6 = 0xe654;
    uVar7 = unaff_DS;
    FUN_214c_17f7(0,0x6eee,0x214c);
    uVar5 = (undefined2)((ulong)_local_8 >> 0x10);
    FUN_214c_1882(0,*(undefined2 *)((int)_local_8 + 0x12),*(undefined2 *)((int)_local_8 + 0x14));
    FUN_214c_17f7(0,0x6ef5,0x214c);
    FUN_214c_1755(uVar6,uVar7);
    uVar7 = (undefined2)((ulong)_local_8 >> 0x10);
    iVar1 = *(int *)((int)_local_8 + 0x14);
    if ((0 < iVar1) || ((-1 < iVar1 && (1 < *(uint *)((int)_local_8 + 0x12))))) {
      uVar5 = 0xe654;
      uVar7 = unaff_DS;
      FUN_214c_1799(0,CONCAT11(extraout_AH_07,0x73));
      FUN_214c_1755(uVar5,uVar7);
    }
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    FUN_214c_17f7(0,0x6efc,0x214c);
    FUN_214c_1755(uVar5,uVar7);
    FUN_20e6_0227();
    uVar7 = CONCAT11(extraout_AH_08,0x50);
    uVar5 = FUN_20e6_0298(uVar7);
    FUN_20e6_0260(uVar5,uVar7);
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    FUN_214c_1799(0,CONCAT11(extraout_AH_09,0xb3));
    FUN_214c_1755(uVar5,uVar7);
  }
  uVar5 = 0xe654;
  uVar7 = unaff_DS;
  FUN_214c_1799(0,0xc0);
  FUN_214c_1755(uVar5,uVar7);
  local_4 = 1;
  while( true ) {
    uVar5 = 0xe654;
    uVar7 = unaff_DS;
    FUN_214c_1799(0,0xc4);
    FUN_214c_1755(uVar5,uVar7);
    if (local_4 == 0x4e) break;
    local_4 = local_4 + 1;
  }
  uVar7 = 0xe654;
  FUN_214c_1799(0,0xd9);
  FUN_214c_1755(uVar7,unaff_DS);
  return;
}



void __cdecl16near FUN_1000_71a1(void)

{
  int iVar1;
  undefined2 uVar2;
  undefined1 extraout_AH;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar3;
  undefined2 uVar4;
  byte *local_108;
  int local_104;
  undefined1 local_102 [256];
  
  FUN_214c_1383(0x7196,0x1000,local_102,unaff_SS);
  FUN_214c_13f8(0x214c,local_102);
  local_104 = 1;
  while ((local_104 != 0x10 &&
         (*(int *)(local_104 * 0x18 + -0x45c9) != 0 || *(int *)(local_104 * 0x18 + -0x45c7) != 0)))
  {
    iVar1 = local_104 * 0x18;
    _local_108 = (byte *)CONCAT22(unaff_DS,(byte *)(iVar1 + -0x45db));
    puVar3 = local_102;
    uVar4 = unaff_SS;
    uVar2 = FUN_214c_02f7(puVar3);
    FUN_214c_1799(0,uVar2);
    FUN_214c_1755(puVar3,uVar4);
    puVar3 = local_102;
    uVar4 = unaff_SS;
    FUN_214c_02f7(puVar3);
    uVar2 = FUN_214c_02f7();
    FUN_214c_1799(0,uVar2);
    FUN_214c_1755(puVar3,uVar4);
    puVar3 = local_102;
    uVar2 = 0x100;
    uVar4 = unaff_SS;
    FUN_214c_02f7(puVar3);
    FUN_214c_1799(0,uVar2);
    FUN_214c_1755(puVar3,uVar4);
    puVar3 = local_102;
    uVar4 = unaff_SS;
    FUN_214c_1799(0,*(int *)(iVar1 + -0x45cb) * 2 + 0x32);
    FUN_214c_1755(puVar3,uVar4);
    puVar3 = local_102;
    uVar4 = unaff_SS;
    FUN_214c_1799(0,CONCAT11(extraout_AH,*(undefined1 *)(iVar1 + -0x45c5)));
    FUN_214c_1755(puVar3,uVar4);
    puVar3 = local_102;
    uVar4 = unaff_SS;
    FUN_214c_1799(0,(uint)*(byte *)(iVar1 + -0x45da) + (uint)*_local_108 + *(int *)(iVar1 + -0x45c5)
                    + *(int *)(iVar1 + -0x45cb) + *(int *)(iVar1 + -0x45c9));
    FUN_214c_1755(puVar3,uVar4);
    puVar3 = local_102;
    FUN_214c_17f7(0,(byte *)(iVar1 + -0x45db),unaff_DS);
    FUN_214c_173c(0x214c,puVar3);
    local_104 = local_104 + 1;
  }
  FUN_214c_1456(local_102,unaff_SS);
  return;
}



void FUN_1000_7364(undefined1 *param_1,int param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  ulong uVar3;
  uint uVar4;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  uint uVar5;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  int iVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  bool bVar8;
  undefined1 *puVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  undefined1 local_2a [28];
  int local_e;
  char *local_a;
  int local_8;
  int local_6;
  int local_4;
  
  FUN_20e6_02e9(1000);
  FUN_20e6_020d();
  pcVar1 = (char *)*(undefined4 *)0xb91e;
  while( true ) {
    local_a = (char *)pcVar1;
    local_8 = (int)((ulong)pcVar1 >> 0x10);
    if (local_a == (char *)0x0 && local_8 == 0) break;
    if ((*pcVar1 == '\b') && (*(int *)(local_a + 1) != 0)) {
      uVar2 = *(undefined4 *)0xb8c8;
      uVar4 = (uint)uVar2;
      uVar5 = *(uint *)(local_a + 0xd);
      iVar6 = *(int *)(local_a + 0xf);
      *(int *)0xb8c8 = uVar4 + *(uint *)(local_a + 0xd);
      *(int *)0xb8ca = (int)((ulong)uVar2 >> 0x10) + iVar6 + (uint)CARRY2(uVar4,uVar5);
    }
    pcVar1 = *(char **)(local_a + 0x16);
  }
  FUN_20e6_0260(2,0x14);
  uVar7 = (char)param_2 == 'g';
  if ((bool)uVar7) {
    FUN_20e6_020d();
    FUN_20e6_0260(CONCAT11(extraout_AH_00,10),CONCAT11(extraout_AH_00,0x1e));
    uVar10 = 0xe654;
    uVar11 = unaff_DS;
    FUN_214c_17f7(0,0x7345,0x20e6);
    FUN_214c_1755(uVar10,uVar11);
    FUN_1000_016a(0x8e);
    FUN_20e6_0260(CONCAT11(extraout_AH_01,0xc),CONCAT11(extraout_AH_01,0x23));
    uVar11 = 0xe654;
    FUN_214c_17f7(0,0x734a,0x20e6);
    FUN_214c_173c(0x214c,uVar11);
  }
  else {
    FUN_20e6_0260(CONCAT11(extraout_AH,3),CONCAT11(extraout_AH,0xf));
    FUN_1000_22c8(10,param_2);
    uVar11 = CONCAT11(extraout_AH_02,(char)param_2);
    puVar9 = local_2a;
    FUN_214c_08af(puVar9);
    FUN_214c_08df(CONCAT11(extraout_AH_03,0x23),CONCAT11(extraout_AH_03,1));
    uVar5 = FUN_214c_0933(puVar9,unaff_SS,uVar11);
    if (!(bool)uVar7) {
      FUN_1000_0499(uVar5 & 0xff00,param_2);
    }
    uVar10 = 0xe654;
    uVar11 = unaff_DS;
    FUN_214c_17f7(0,0x7351,0x214c);
    FUN_214c_1882(0,*(int *)0xe52d,*(int *)0xe52d >> 0xf);
    FUN_214c_17f7(0,0x735d,0x214c);
    FUN_214c_1882(0,*(undefined2 *)0xb8c8,*(undefined2 *)0xb8ca);
    FUN_214c_1755(uVar10,uVar11);
    FUN_1000_016a(0x19f);
    FUN_20e6_0260(CONCAT11(extraout_AH_04,4),CONCAT11(extraout_AH_04,0x23));
    FUN_1000_016a(0x1a3);
    FUN_214c_173c(0x20e6,0xe654);
  }
  if ((char)param_2 != 'Q') {
    FUN_1000_6c94();
    local_6 = 1;
    if ((char)param_2 == 'g') {
      for (; local_6 < 0x10; local_6 = local_6 + 1) {
        uVar2 = *(undefined4 *)(local_6 * 0x18 + -0x45c9);
        iVar6 = (int)((ulong)uVar2 >> 0x10);
        if (((iVar6 <= *(int *)0xb8ca) &&
            ((iVar6 < *(int *)0xb8ca || ((uint)uVar2 <= *(uint *)0xb8c8)))) ||
           (*(int *)(local_6 * 0x18 + -0x45c5) != param_2)) break;
      }
    }
    else {
      while ((local_6 < 0x10 && (*(char *)(local_6 * 0x18 + -0x45c5) == 'g'))) {
        local_6 = local_6 + 1;
      }
      for (; local_6 < 0x10; local_6 = local_6 + 1) {
        uVar2 = *(undefined4 *)(local_6 * 0x18 + -0x45c9);
        iVar6 = (int)((ulong)uVar2 >> 0x10);
        if ((iVar6 <= *(int *)0xb8ca) &&
           ((iVar6 < *(int *)0xb8ca || ((uint)uVar2 <= *(uint *)0xb8c8)))) break;
      }
    }
    _local_e = CONCAT22(local_6 + 1,local_e);
    if (local_6 + 1 < 0x10) {
      for (local_4 = 0xf;
          FUN_214c_02c0(0x18,local_4 * 0x18 + -0x45db,unaff_DS,(local_4 + -1) * 0x18 + -0x45db,
                        unaff_DS), uVar2 = _local_e, uVar3 = (ulong)_local_e >> 0x10,
          bVar8 = local_4 != (int)uVar3, _local_e = uVar2, bVar8; local_4 = local_4 + -1) {
      }
    }
    if (local_6 < 0x10) {
      iVar6 = local_6 * 0x18;
      _local_e = CONCAT22(unaff_DS,iVar6 + -0x45db);
      uVar2 = *(undefined4 *)0xb8c8;
      *(undefined2 *)(iVar6 + -0x45c9) = (int)uVar2;
      *(undefined2 *)(iVar6 + -0x45c7) = (int)((ulong)uVar2 >> 0x10);
      *(undefined2 *)(iVar6 + -0x45cb) = *(undefined2 *)0xe52d;
      *(int *)(iVar6 + -0x45c5) = param_2;
      FUN_214c_06ad(0xf,iVar6 + -0x45db,unaff_DS,0xb84f,unaff_DS);
    }
  }
  FUN_1000_6f02();
  uVar7 = extraout_AH_05;
  if ((local_6 < 0x10) && ((char)param_2 != ' ')) {
    FUN_1000_71a1();
    uVar7 = extraout_AH_06;
  }
  FUN_20e6_0260(CONCAT11(uVar7,0x19),CONCAT11(uVar7,0x3c));
  FUN_1000_1448();
  *param_1 = 0;
  return;
}



void FUN_1000_763d(undefined4 param_1,char param_2)

{
  undefined2 uVar1;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined2 unaff_SS;
  undefined1 uVar2;
  undefined1 *puVar3;
  undefined1 local_23 [32];
  undefined1 local_3;
  
  FUN_1000_0040();
  FUN_1000_016a(0xc2);
  uVar2 = param_2 == 's';
  if ((bool)uVar2) {
    FUN_1000_016a(0x1a0);
  }
  else {
    FUN_1000_016a(0x1a1);
  }
  uVar1 = FUN_20e6_0357();
  local_3 = (undefined1)uVar1;
  puVar3 = local_23;
  FUN_214c_08af(puVar3);
  FUN_214c_08be(CONCAT11(extraout_AH,0x6f));
  FUN_214c_08be(CONCAT11(extraout_AH_00,0x4f));
  FUN_214c_0933(puVar3,unaff_SS,uVar1);
  if (!(bool)uVar2) {
    FUN_1000_7364((int)param_1,(int)((ulong)param_1 >> 0x10),param_2);
  }
  return;
}



void __cdecl16near FUN_1000_76a4(void)

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
  
  puVar1 = (undefined1 *)*(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
  while( true ) {
    local_6._0_2_ = (undefined1 *)puVar1;
    local_6._2_2_ = (uint)((ulong)puVar1 >> 0x10);
    uVar3 = ((uint)(undefined1 *)local_6 | local_6._2_2_) == 0;
    if ((bool)uVar3) break;
    uVar2 = CONCAT11((char)(((uint)(undefined1 *)local_6 | local_6._2_2_) >> 8),*puVar1);
    puVar4 = local_26;
    uVar5 = unaff_SS;
    local_6 = puVar1;
    FUN_214c_08af(puVar4);
    FUN_214c_08be(CONCAT11(extraout_AH,0x45));
    FUN_214c_08be(CONCAT11(extraout_AH_00,0x48));
    FUN_214c_0933(puVar4,uVar5,uVar2);
    puVar4 = (undefined1 *)local_6;
    uVar5 = (undefined2)((ulong)local_6 >> 0x10);
    if (!(bool)uVar3) {
      puVar4[0x22] = 1;
      puVar4[0x28] = 0;
      *(int *)(puVar4 + 8) = *(int *)(puVar4 + 8) + 1;
    }
    puVar1 = *(undefined1 **)(puVar4 + 0x32);
  }
  *(undefined2 *)(*(int *)0xe52d * 2 + 0x799b) = 4;
  return;
}



void __cdecl16near FUN_1000_772e(void)

{
  undefined1 extraout_AH;
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined2 unaff_DS;
  undefined2 uVar4;
  undefined2 uVar5;
  
  if (*(int *)0xb888 < 0xe) {
    FUN_1000_1448();
    FUN_1000_0040();
    *(int *)0xb888 = *(int *)0xb888 + 1;
    FUN_1000_016a(0x91);
    uVar4 = 0xe654;
    uVar5 = unaff_DS;
    FUN_214c_1799(0,CONCAT11(extraout_AH,0x20));
    FUN_214c_1882(0,*(int *)0xb888,*(int *)0xb888 >> 0xf);
    FUN_214c_1755(uVar4,uVar5);
    uVar1 = FUN_214c_1162(*(undefined2 *)0xe52d);
    uVar1 = uVar1 / 2;
    iVar2 = FUN_214c_1162(*(undefined2 *)0xb888);
    iVar3 = FUN_214c_1162(6);
    *(int *)0xb872 = *(int *)0xb872 + iVar3 + iVar2 + 3 + uVar1;
    iVar2 = FUN_214c_1162(*(int *)0xb888 + 6 + *(int *)0xe52d);
    *(int *)0xb870 = *(int *)0xb870 + 1 + iVar2;
    if (*(int *)0xb872 < *(int *)0xb870) {
      *(undefined2 *)0xb870 = *(undefined2 *)0xb872;
    }
    FUN_1000_0296();
  }
  return;
}



void __cdecl16near FUN_1000_77fe(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  FUN_1000_016a(0x32);
  if (*(int *)0xb888 != 1) {
    *(int *)0xb888 = *(int *)0xb888 + -1;
  }
  iVar1 = FUN_214c_1162(*(int *)0xb888 + 6);
  *(int *)0xb872 = (*(int *)0xb872 + -3) - iVar1;
  if (*(int *)0xb872 < *(int *)0xb870) {
    *(undefined2 *)0xb870 = *(undefined2 *)0xb872;
  }
  return;
}



void FUN_1000_7849(char param_1)

{
  int iVar1;
  char cVar2;
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
  
  if ((*(uint *)0xb926 | *(uint *)0xb928) == 0) {
    return;
  }
  uVar5 = *(int *)0xb87c == 1;
  if (*(int *)0xb87c < 2) {
    return;
  }
  uVar3 = CONCAT11((char)((*(uint *)0xb926 | *(uint *)0xb928) >> 8),
                   *(undefined1 *)((int)*(undefined4 *)0xb926 + 1));
  puVar6 = local_22;
  FUN_214c_08af(puVar6);
  FUN_214c_08be(CONCAT11(extraout_AH,1));
  FUN_214c_08be(CONCAT11(extraout_AH_00,2));
  FUN_214c_08be(CONCAT11(extraout_AH_01,6));
  FUN_214c_0933(puVar6,unaff_SS,uVar3);
  if (!(bool)uVar5) {
    return;
  }
  if (param_1 == '\0') {
    FUN_1000_1448();
    FUN_1000_0040();
    FUN_1000_016a(0x94);
  }
  uVar3 = (undefined2)((ulong)*(undefined4 *)0xb926 >> 0x10);
  iVar1 = (int)*(undefined4 *)0xb926;
  uVar5 = *(char *)(iVar1 + 0x15) == '\0';
  if ((bool)uVar5) {
    cVar2 = FUN_1000_06d5(1);
    uVar5 = cVar2 == '\0';
    if ((bool)uVar5) goto LAB_1000_78e1;
  }
  uVar4 = 0;
  FUN_214c_1178();
  FUN_214c_0cc5();
  if ((bool)uVar4 || (bool)uVar5) {
    if (param_1 != '\0') {
      return;
    }
    FUN_1000_016a(0x41);
    return;
  }
LAB_1000_78e1:
  if (param_1 != '\0') {
    FUN_1000_016a(0x94);
  }
  *(int *)0xb87c = *(int *)0xb87c + -1;
  *(int *)(iVar1 + 9) = *(int *)(iVar1 + 9) + -1;
  *(int *)0xb880 = *(int *)0xb880 + -1;
  FUN_1000_0296();
  return;
}



void __cdecl16near FUN_1000_7923(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  FUN_1000_3544();
  if (*(int *)(*(int *)0xe52d * 4 + -0x5499) != 0 || *(int *)(*(int *)0xe52d * 4 + -0x5497) != 0) {
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
    uVar3 = (undefined2)((ulong)uVar1 >> 0x10);
    iVar2 = (int)uVar1;
    *(undefined1 *)(*(int *)(iVar2 + 0x1c) * 0x4f + *(int *)(iVar2 + 0x1e) + -0xc) = 0x20;
    *(undefined2 *)(iVar2 + 0x1c) = *(undefined2 *)0xb86c;
    *(undefined2 *)(iVar2 + 0x1e) = *(undefined2 *)0xb86e;
    do {
      FUN_1000_491d(iVar2 + 0x1e,uVar3,iVar2 + 0x1c,uVar3);
    } while (*(char *)(*(int *)(iVar2 + 0x1c) * 0x4f + *(int *)(iVar2 + 0x1e) + -0xc) != ' ');
    *(undefined1 *)(*(int *)(iVar2 + 0x1c) * 0x4f + *(int *)(iVar2 + 0x1e) + -0xc) =
         *(undefined1 *)(iVar2 + 1);
    FUN_1000_0e28();
  }
  return;
}



void FUN_1000_79ea(char param_1,char *param_2)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  undefined4 uVar4;
  byte extraout_AH;
  byte bVar8;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  int iVar9;
  undefined2 in_BX;
  char *pcVar10;
  int iVar11;
  undefined2 unaff_DS;
  undefined1 uVar12;
  undefined1 uVar13;
  char *local_6;
  int local_4;
  
  uVar5 = 0x1000;
  iVar11 = (int)((ulong)param_2 >> 0x10);
  pcVar10 = (char *)param_2;
  if (param_1 != '\0') {
    if (*(char *)0xe539 != '\0') {
      uVar7 = 0xe654;
      uVar6 = unaff_DS;
      FUN_214c_1799(0,7);
      uVar5 = 0x214c;
      FUN_214c_1755(uVar7,uVar6);
    }
    if (*(char *)0xb8ed == '\0') {
      FUN_1000_0510(*(undefined2 *)(pcVar10 + 4),0xb5);
    }
    else {
      FUN_1000_016a(0xb5);
      uVar7 = 0xe654;
      uVar6 = unaff_DS;
      FUN_214c_17f7(0,0x79e5,uVar5);
      FUN_214c_1755(uVar7,uVar6);
    }
    if (*(int *)(pcVar10 + 0x2e) == 0 && *(int *)(pcVar10 + 0x30) == 0) {
      bVar8 = 0;
    }
    else {
      *(undefined2 *)((int)*(undefined4 *)(pcVar10 + 0x2e) + 5) = *(undefined2 *)0xb86c;
      *(undefined2 *)((int)*(undefined4 *)(pcVar10 + 0x2e) + 7) = *(undefined2 *)0xb86e;
      FUN_1000_491d((int)*(undefined4 *)(pcVar10 + 0x2e) + 7,
                    (int)((ulong)*(undefined4 *)(pcVar10 + 0x2e) >> 0x10),
                    (int)*(undefined4 *)(pcVar10 + 0x2e) + 5,
                    (int)((ulong)*(undefined4 *)(pcVar10 + 0x2e) >> 0x10));
      uVar13 = (undefined1)((uint)in_BX >> 8);
      uVar12 = FUN_1000_0479(*(undefined2 *)(pcVar10 + 0x2e),*(undefined2 *)(pcVar10 + 0x30));
      in_BX = CONCAT11(uVar13,uVar12);
      uVar4 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      *(undefined1 *)
       ((int)uVar4 + *(int *)((int)*(undefined4 *)(pcVar10 + 0x2e) + 5) * 0x4f +
        *(int *)((int)*(undefined4 *)(pcVar10 + 0x2e) + 7) + -0x50) = uVar12;
      FUN_1000_15a2(*(int *)0xe52d * 4 + -0x54d9,unaff_DS,pcVar10 + 0x2e,iVar11);
      bVar8 = extraout_AH;
    }
    cVar2 = *param_2;
    if (cVar2 == 'V') {
      FUN_1000_4a27(CONCAT11(bVar8,1));
    }
    else if (cVar2 == 'F') {
      FUN_1000_4a27((uint)bVar8 << 8);
    }
    else if (cVar2 == 'H') {
      *(undefined1 *)0xb919 = 0;
    }
  }
  iVar9 = *(int *)(pcVar10 + 0x1c);
  *(undefined1 *)(iVar9 * 0x4f + *(int *)(pcVar10 + 0x1e) + -0xc) = 0x20;
  FUN_1000_0428(CONCAT11((char)((uint)(iVar9 * 0x4f) >> 8),0x20),*(undefined2 *)(pcVar10 + 0x1e),
                *(undefined2 *)(pcVar10 + 0x1c));
  FUN_1000_1d47(pcVar10,iVar11);
  if (param_1 != '\0') {
    if (*(int *)0xb8bc != 0 || *(int *)0xb8be != 0) {
      iVar9 = *(int *)(pcVar10 + 6) >> 0xf;
      FUN_214c_0cc9();
      FUN_214c_0cbb();
      uVar5 = FUN_214c_0ca3();
      *(undefined2 *)0xb88a = uVar5;
      *(undefined2 *)0xb88c = in_BX;
      *(int *)0xb88e = iVar9;
    }
    uVar5 = *(undefined2 *)0xb88e;
    iVar9 = FUN_214c_0ccd();
    *(int *)(pcVar10 + 6) = *(int *)(pcVar10 + 6) + iVar9;
    iVar9 = *(int *)(*(int *)0xb888 * 2 + -0x46b8) - *(int *)((*(int *)0xb888 + -1) * 2 + -0x46b8)
            >> 0xf;
    FUN_214c_0cc9();
    uVar12 = 0;
    uVar13 = 1;
    uVar6 = FUN_214c_0cbb();
    FUN_214c_0cc9(uVar6,uVar5,iVar9);
    FUN_214c_0cc5();
    if (!(bool)uVar12 && !(bool)uVar13) {
      *(int *)(pcVar10 + 6) =
           (*(int *)(*(int *)0xb888 * 2 + -0x46b8) - *(int *)((*(int *)0xb888 + -1) * 2 + -0x46b8))
           / 2;
    }
    iVar9 = FUN_214c_0ccd();
    *(int *)0xb886 = *(int *)0xb886 + *(int *)(pcVar10 + 6) + iVar9;
    FUN_214c_0ccd();
    FUN_214c_0cc9();
    uVar5 = *(undefined2 *)0xb88c;
    uVar6 = *(undefined2 *)0xb88e;
    uVar7 = FUN_214c_0ca9();
    *(undefined2 *)0xb88a = uVar7;
    *(undefined2 *)0xb88c = uVar5;
    *(undefined2 *)0xb88e = uVar6;
    if (*(int *)0xb886 < 0) {
      *(undefined2 *)0xb886 = 0;
    }
    if (*(int *)(*(int *)0xb888 * 2 + -0x46b8) <= *(int *)0xb886) {
      FUN_1000_772e();
    }
    *(int *)(*(int *)(pcVar10 + 2) * 2 + -0x460b) =
         *(int *)(*(int *)(pcVar10 + 2) * 2 + -0x460b) + 1;
    FUN_1000_0296();
  }
  pcVar3 = (char *)*(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
  local_4 = (int)((ulong)pcVar3 >> 0x10);
  local_6 = (char *)pcVar3;
  if ((local_4 == iVar11) && (local_6 == pcVar10)) {
    uVar4 = *(undefined4 *)(local_6 + 0x32);
    iVar9 = *(int *)0xe52d;
    *(undefined2 *)(iVar9 * 4 + -0x5499) = (int)uVar4;
    *(undefined2 *)(iVar9 * 4 + -0x5497) = (int)((ulong)uVar4 >> 0x10);
  }
  else {
    for (; ((int)((ulong)*(char **)(local_6 + 0x32) >> 0x10) != iVar11 ||
           ((char *)*(char **)(local_6 + 0x32) != pcVar10));
        local_4 = (int)((ulong)*(char **)pcVar1 >> 0x10)) {
      pcVar1 = local_6 + 0x32;
      local_6 = (char *)*(char **)pcVar1;
    }
  }
  uVar4 = *(undefined4 *)(pcVar10 + 0x32);
  *(int *)(local_6 + 0x32) = (int)uVar4;
  *(int *)(local_6 + 0x34) = (int)((ulong)uVar4 >> 0x10);
  FUN_1000_05b0(pcVar10,iVar11);
  *(int *)(*(int *)0xe52d * 2 + 0x797d) = *(int *)(*(int *)0xe52d * 2 + 0x797d) + -1;
  FUN_1000_0e28();
  return;
}



void FUN_1000_7d66(undefined1 *param_1)

{
  undefined1 *puVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  if ((*(char *)0xb8ed == '\0') && (*(char *)0xb8f0 == '\0')) {
    FUN_1000_016a(0x93);
    *(int *)0xb87a = *(int *)0xb87a + -5;
    FUN_1000_1448();
  }
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  puVar1 = (undefined1 *)param_1;
  puVar1[1] = *param_1;
  *(undefined2 *)(puVar1 + 4) = *(undefined2 *)(puVar1 + 2);
  return;
}



void __cdecl16near FUN_1000_7dab(void)

{
  undefined1 *puVar1;
  undefined2 uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  int iVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined1 local_2a [32];
  undefined1 *local_a;
  int local_8;
  undefined4 local_6;
  
  local_8 = (int)((ulong)*(undefined4 *)0xb91e >> 0x10);
  local_a = (undefined1 *)(undefined1 *)*(undefined4 *)0xb91e;
  while (uVar4 = local_a == (undefined1 *)0x0 && local_8 == 0,
        local_a != (undefined1 *)0x0 || local_8 != 0) {
    local_6 = (undefined1 *)CONCAT22(local_8,local_a);
    puVar1 = *(undefined1 **)(local_a + 0x16);
    local_8 = (int)((ulong)puVar1 >> 0x10);
    local_a = (undefined1 *)puVar1;
    uVar2 = CONCAT11((char)((ulong)puVar1 >> 8),*local_6);
    puVar5 = local_2a;
    uVar6 = unaff_SS;
    FUN_214c_08af(puVar5);
    FUN_214c_08be(CONCAT11(extraout_AH,2));
    FUN_214c_08be(CONCAT11(extraout_AH_00,3));
    FUN_214c_0933(puVar5,uVar6,uVar2);
    if ((!(bool)uVar4) && (iVar3 = FUN_214c_1162(0x14), iVar3 == 0)) {
      FUN_1000_15d3(0,0,(undefined1 *)local_6,local_6._2_2_);
    }
  }
  return;
}



void FUN_1000_7e29(int param_1)

{
  undefined4 uVar1;
  undefined2 *puVar2;
  undefined2 unaff_SS;
  
  uVar1 = *(undefined4 *)((int)*(undefined4 *)*(undefined4 *)(param_1 + 0xc) + 0x32);
  *(undefined2 *)(param_1 + -0x15) = (int)uVar1;
  *(undefined2 *)(param_1 + -0x13) = (int)((ulong)uVar1 >> 0x10);
  *(undefined1 *)*(undefined4 *)(param_1 + 4) = 1;
  puVar2 = (undefined2 *)*(undefined4 *)(param_1 + 0xc);
  FUN_1000_79ea((uint)(byte)((ulong)uVar1 >> 8) << 8,*puVar2,((undefined2 *)puVar2)[1]);
  uVar1 = *(undefined4 *)(param_1 + -0x15);
  puVar2 = (undefined2 *)*(undefined4 *)(param_1 + 0xc);
  *puVar2 = (int)uVar1;
  ((undefined2 *)puVar2)[1] = (int)((ulong)uVar1 >> 0x10);
  return;
}



void FUN_1000_7ebc(undefined2 param_1,undefined2 param_2,undefined4 param_3,undefined4 *param_4)

{
  uint uVar1;
  byte *pbVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  byte *pbVar5;
  char cVar6;
  byte bVar7;
  int iVar8;
  uint uVar9;
  undefined1 extraout_AH;
  byte extraout_AH_00;
  byte extraout_AH_01;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar10;
  bool bVar11;
  undefined1 uVar12;
  bool bVar13;
  undefined2 uVar14;
  undefined2 uVar15;
  undefined2 uVar16;
  char local_19 [6];
  undefined4 local_13;
  uint local_f;
  int local_d;
  uint local_9;
  int local_7;
  int local_5;
  
  cVar6 = FUN_20e6_0298();
  if (cVar6 == '\x01') {
    bVar7 = FUN_20e6_028c();
    if (0x32 < bVar7) {
      FUN_1000_1448();
      FUN_1000_0040();
    }
  }
  else {
    FUN_1000_0040();
  }
  iVar8 = FUN_214c_1162(*(undefined2 *)((int)*param_4 + 0x14));
  local_9 = ((*(int *)((int)*param_4 + 8) - *(int *)0xb888) - *(int *)0xb880) + 1 + iVar8;
  if (*(char *)0xb8f7 != '\0') {
    local_9 = local_9 + -8;
  }
  FUN_1000_084b(&local_7,unaff_SS,7);
  local_9 = local_9 - local_7;
  uVar9 = *(uint *)0xb8b4 | *(uint *)0xb8b6;
  if (uVar9 != 0) {
    iVar8 = FUN_214c_1162(5);
    uVar9 = local_9 + 1 + iVar8;
    local_9 = uVar9;
  }
  uVar10 = (undefined1)(uVar9 >> 8);
  if ((int)local_9 < 1) {
    if (*(char *)0xb8ed == '\0') {
      FUN_1000_0499(CONCAT11(uVar10,1),*(undefined2 *)((int)*param_4 + 4));
    }
    else {
      uVar15 = 0xe654;
      uVar16 = unaff_DS;
      FUN_214c_17f7(0,0x7e83,0x214c);
      FUN_214c_1755(uVar15,uVar16);
    }
    uVar16 = 0xe654;
    FUN_214c_17f7(0,0x7eb2,0x214c);
    FUN_214c_1755(uVar16,unaff_DS);
    return;
  }
  pbVar2 = (byte *)*param_4;
  uVar16 = (undefined2)((ulong)pbVar2 >> 0x10);
  pbVar5 = (byte *)pbVar2;
  if ((*pbVar2 == 1) && (*pbVar2 != pbVar5[1])) {
    FUN_1000_7d66(*(undefined2 *)param_4,*(undefined2 *)((int)(undefined4 *)param_4 + 2));
    uVar10 = extraout_AH;
  }
  if (*(char *)0xb8ed == '\0') {
    FUN_1000_0499(CONCAT11(uVar10,1),*(undefined2 *)(pbVar5 + 4));
  }
  else {
    uVar14 = 0xe654;
    uVar15 = unaff_DS;
    FUN_214c_17f7(0,0x7e83,0x214c);
    FUN_214c_1755(uVar14,uVar15);
  }
  uVar14 = 0xe654;
  uVar15 = unaff_DS;
  FUN_214c_17f7(0,0x7e86,0x214c);
  uVar9 = FUN_214c_1755(uVar14,uVar15);
  if (*(int *)(pbVar5 + 0x10) != 0) {
    uVar1 = *(uint *)(pbVar5 + 0xe);
    uVar9 = 0;
    if (0 < (int)uVar1) {
      local_f = 1;
      while( true ) {
        iVar8 = FUN_214c_1162(*(undefined2 *)(pbVar5 + 0x10));
        *(int *)0xb870 = (*(int *)0xb870 + -1) - iVar8;
        uVar9 = local_f;
        if (local_f == uVar1) break;
        local_f = local_f + 1;
      }
    }
  }
  uVar15 = (undefined2)param_3;
  uVar14 = (undefined2)((ulong)param_3 >> 0x10);
  if (*(int *)0xb870 < 1) {
    local_5 = 1;
    while ((local_5 < 5 &&
           ((uVar4 = *(undefined4 *)(local_5 * 4 + -0x46cc), *(int *)((int)uVar4 + 1) != 0xf ||
            (uVar4 = *(undefined4 *)(local_5 * 4 + -0x46cc), *(int *)((int)uVar4 + 9) < 1))))) {
      local_5 = local_5 + 1;
    }
    if (local_5 == 5) {
      FUN_1000_7364(uVar15,uVar14,*(undefined2 *)(pbVar5 + 2));
      return;
    }
    iVar8 = FUN_214c_1162(6);
    *(int *)0xb870 = (*(int *)0xb872 + -5) - iVar8;
    *(undefined2 *)0xb872 = *(undefined2 *)0xb870;
    *(int *)0xb876 = *(int *)0xb876 + -2;
    *(int *)0xb874 = *(int *)0xb874 + -2;
    *(int *)0xb87a = *(int *)0xb87a + -1;
    uVar4 = *(undefined4 *)(local_5 * 4 + -0x46cc);
    uVar3 = *(undefined4 *)(local_5 * 4 + -0x46cc);
    *(int *)((int)uVar3 + 9) = *(int *)((int)uVar4 + 9) + -1;
    FUN_1000_0296();
    return;
  }
  bVar7 = *pbVar2;
  if ((bVar7 == 0xea) || (bVar7 == 0xe8)) {
    *(undefined1 *)0xb8ec = 0;
    goto LAB_1000_850d;
  }
  if (bVar7 == 0x4d) {
    FUN_1000_7849(uVar9 & 0xff00);
    goto LAB_1000_850d;
  }
  uVar10 = bVar7 < 0x9c;
  uVar12 = bVar7 == 0x9c;
  if ((bool)uVar12) {
    FUN_214c_1178();
    FUN_214c_0cc5();
    if (!(bool)uVar10 && !(bool)uVar12) {
      *(int *)0xb878 = *(int *)0xb878 + -1;
      FUN_1000_016a(199);
    }
    goto LAB_1000_850d;
  }
  if ((bVar7 == 0x47) || (bVar7 == 0x4e)) {
    if (*pbVar2 == 0x47) {
      FUN_214c_1178();
      bVar11 = false;
      bVar13 = true;
      FUN_214c_0cc5();
      if (!bVar11 && !bVar13) goto LAB_1000_850d;
    }
    uVar10 = *pbVar2 < 0x4e;
    uVar12 = *pbVar2 == 0x4e;
    if ((bool)uVar12) {
      FUN_214c_1178();
      FUN_214c_0cc5();
      if (!(bool)uVar10 && !(bool)uVar12) goto LAB_1000_850d;
    }
    cVar6 = FUN_1000_06d5(2);
    uVar10 = 0;
    uVar12 = cVar6 == '\0';
    if (!(bool)uVar12) {
      FUN_214c_1178();
      FUN_214c_0cc5();
      if (!(bool)uVar10 && !(bool)uVar12) goto LAB_1000_850d;
    }
    FUN_1000_1448();
    FUN_1000_0040();
    FUN_1000_016a(0x95);
    *(int *)0xb874 = *(int *)0xb874 + -1;
    if (*(int *)0xb874 < 0) {
      FUN_1000_7364(uVar15,uVar14,0x65);
    }
    goto LAB_1000_850d;
  }
  uVar10 = bVar7 < 0x9e;
  uVar12 = bVar7 == 0x9e;
  if ((bool)uVar12) {
    FUN_214c_1178();
    FUN_214c_0cc5();
    if (!(bool)uVar10 && !(bool)uVar12) {
      *(int *)0xb87a = *(int *)0xb87a + -1;
      FUN_1000_016a(0xcd);
      if (*(int *)0xb87a < 1) {
        FUN_1000_7364(uVar15,uVar14,100);
      }
    }
    goto LAB_1000_850d;
  }
  uVar10 = bVar7 < 0x73;
  uVar12 = bVar7 == 0x73;
  if ((bool)uVar12) {
    FUN_214c_1178();
    FUN_214c_0cc5();
    if (!(bool)uVar10 && !(bool)uVar12) {
      iVar8 = FUN_214c_1162(10);
      *(int *)0xb886 = (*(int *)0xb886 + -10) - iVar8;
      if (*(int *)0xb886 < *(int *)((*(int *)0xb888 + -1) * 2 + -0x46b8)) {
        FUN_1000_77fe();
      }
    }
    goto LAB_1000_850d;
  }
  if (bVar7 == 0x45) {
    local_f = FUN_214c_1162(5);
    if ((int)local_f < 4) {
      pbVar5[0x22] = 0;
      pbVar5[0x28] = 1;
      *(undefined1 *)0xb915 = 1;
      FUN_1000_1448();
      FUN_1000_0040();
      if (local_f == 3) {
        FUN_1000_016a(0x3e);
        iVar8 = FUN_214c_1162(0x32);
        *(int *)0xb91a = iVar8 + 100;
      }
      else {
        FUN_1000_016a(0x49);
        iVar8 = FUN_214c_1162(5);
        *(int *)0xb91a = iVar8 + 0xf;
      }
    }
    goto LAB_1000_850d;
  }
  if (bVar7 == 0x48) {
    *(undefined1 *)0xb919 = 1;
    goto LAB_1000_850d;
  }
  if (bVar7 != 0x46) {
    if (bVar7 == 0x56) {
      FUN_214c_1162(0xb);
      local_f = FUN_214c_02dc();
      if ((*(int *)0xb8ca < (int)local_f >> 0xf) ||
         ((*(int *)0xb8ca <= (int)local_f >> 0xf && (*(uint *)0xb8c8 < local_f)))) {
        local_f = *(uint *)0xb8c8;
      }
      uVar4 = *(undefined4 *)0xb8c8;
      uVar9 = (uint)uVar4;
      *(int *)0xb8c8 = uVar9 - local_f;
      *(int *)0xb8ca =
           ((int)((ulong)uVar4 >> 0x10) - ((int)local_f >> 0xf)) - (uint)(uVar9 < local_f);
      if (local_f != 0) {
        FUN_1000_1448();
        FUN_1000_0040();
        if (*(char *)0xb8ed == '\0') {
          FUN_1000_016a(0x97);
        }
        else {
          FUN_1000_016a(0x96);
        }
        uVar16 = 0xe654;
        FUN_214c_17f7(0,0x7ea5,0x214c);
        FUN_214c_1755(uVar16,unaff_DS);
        FUN_1000_7e29(&stack0xfffe);
      }
    }
    goto LAB_1000_850d;
  }
  local_d = 0;
  local_19[1] = 0;
  if (*(int *)0xb91e != 0 || *(int *)0xb920 != 0) {
    if ((*(int *)0xb926 != 0 || *(int *)0xb928 != 0) &&
       (*(char *)((int)*(undefined4 *)0xb926 + 0x14) == '\0')) {
      uVar9 = *(uint *)((int)*(undefined4 *)0xb926 + 1);
      uVar10 = uVar9 < 6;
      uVar12 = uVar9 == 6;
      if ((bool)uVar12) {
        FUN_214c_1178();
        FUN_214c_0cc5();
        if (!(bool)uVar10 && !(bool)uVar12) {
          local_13 = (char *)*(undefined4 *)0xb926;
          FUN_1000_08bd(CONCAT11((char)((ulong)local_13 >> 8),1),local_19,unaff_SS,&local_13,
                        unaff_SS);
          goto LAB_1000_83ad;
        }
      }
    }
    do {
      local_d = local_d + 1;
      iVar8 = FUN_214c_1162(*(undefined2 *)0xb8c0);
      *(int *)(pbVar5 + 4) = iVar8 + 1;
      local_13 = (char *)*(undefined4 *)0xb91e;
      iVar8 = *(int *)(pbVar5 + 4) - *(int *)((int)*(undefined4 *)0xb91e + 3);
      *(int *)(pbVar5 + 4) = iVar8;
      while (0 < *(int *)(pbVar5 + 4)) {
        local_13 = *(char **)((char *)local_13 + 0x16);
        iVar8 = *(int *)(pbVar5 + 4) - *(int *)((char *)local_13 + 3);
        *(int *)(pbVar5 + 4) = iVar8;
      }
      FUN_1000_08bd(CONCAT11((char)((uint)iVar8 >> 8),1),local_19,unaff_SS,&local_13,unaff_SS);
    } while ((local_19[0] == '\0') && (local_d != 10));
  }
LAB_1000_83ad:
  if ((*(int *)0xb91e != 0 || *(int *)0xb920 != 0) && (local_d != 10)) {
    FUN_1000_1448();
    FUN_1000_0040();
    if (*(char *)0xb8ed == '\0') {
      uVar15 = 0xe654;
      uVar16 = unaff_DS;
      FUN_214c_17f7(0,0x7e9b,0x214c);
      FUN_214c_1755(uVar15,uVar16);
    }
    else {
      uVar15 = 0xe654;
      uVar16 = unaff_DS;
      FUN_214c_17f7(0,0x7e91,0x214c);
      FUN_214c_1755(uVar15,uVar16);
    }
    FUN_1000_016a(0x1a4);
    FUN_1000_557c((uint)extraout_AH_00 << 8,(uint)extraout_AH_00 << 8,(char *)local_13,
                  local_13._2_2_);
    uVar15 = 0xe654;
    uVar16 = unaff_DS;
    FUN_214c_17f7(0,0x7ea1,0x214c);
    FUN_214c_1755(uVar15,uVar16);
    if ((*local_13 == '\b') && (*(undefined1 *)0xb918 = 0, *(int *)0xe52d == 1)) {
      uVar4 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      *(undefined1 *)((int)uVar4 + *(int *)0x78f1 * 0x4f + *(int *)0x78f3 + -0x50) = 0x20;
    }
    FUN_1000_7e29(&stack0xfffe);
    FUN_1000_15d3(CONCAT11(extraout_AH_01,1),(uint)extraout_AH_01 << 8,(char *)local_13,
                  local_13._2_2_);
  }
LAB_1000_850d:
  FUN_1000_0296();
  return;
}



void FUN_1000_8573(undefined4 param_1,undefined2 param_2,undefined2 param_3)

{
  byte *pbVar1;
  byte bVar2;
  undefined4 uVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
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
  int local_1b;
  int local_19;
  int local_17;
  int local_15;
  int local_12;
  int local_10;
  int local_e;
  uint local_c;
  undefined4 local_6;
  
  FUN_1000_00de(&local_6,unaff_SS,param_2,param_3);
  FUN_1000_0040();
  if ((byte *)local_6 == (byte *)0x0 && local_6._2_2_ == 0) {
    uVar14 = 0xe654;
    FUN_214c_17f7(0,0x855f,0x1000);
    FUN_214c_1755(uVar14,unaff_DS);
    FUN_1000_1448();
  }
  else {
    local_c = (uint)(*(int *)0xb8b8 != 0 || *(int *)0xb8ba != 0);
    local_15 = *(int *)0xb878;
    if (local_15 == 0) {
      local_15 = 1;
    }
    if (*(int *)0xb92e != 0 || *(int *)0xb930 != 0) {
      if (*(int *)((int)*(undefined4 *)0xb92e + 1) == 9) {
        local_15 = local_15 + 2;
      }
      else if ((*(int *)((int)*(undefined4 *)0xb92e + 1) == 10) &&
              (local_15 = local_15 + -4, local_15 < 1)) {
        local_15 = 1;
      }
    }
    if (*(int *)0xb922 == 0 && *(int *)0xb924 == 0) {
      local_12 = FUN_214c_1162(local_15);
      uVar14 = 0;
      uVar10 = (undefined2)((ulong)local_6 >> 0x10);
      local_12 = ((*(int *)0xb888 - *(int *)((byte *)local_6 + 8)) - *(int *)((byte *)local_6 + 0xc)
                 ) + 1 + local_12;
    }
    else {
      uVar5 = FUN_214c_1162(local_15);
      uVar14 = 0;
      uVar10 = (undefined2)((ulong)local_6 >> 0x10);
      uVar6 = (((*(int *)0xb888 + *(int *)((int)*(undefined4 *)0xb922 + 9)) -
               *(int *)((byte *)local_6 + 8)) - *(int *)((byte *)local_6 + 0xc)) + 1;
      local_12 = uVar6 + uVar5;
      uVar11 = ((int)uVar6 >> 0xf) + (uint)CARRY2(uVar6,uVar5) == 0;
      uVar8 = CONCAT11((char)((uint)local_12 >> 8),*(undefined1 *)((int)*(undefined4 *)0xb922 + 1));
      puVar13 = local_3b;
      uVar10 = unaff_SS;
      FUN_214c_08af(puVar13);
      FUN_214c_08be(CONCAT11(extraout_AH,9));
      FUN_214c_08be(CONCAT11(extraout_AH_00,0xd));
      FUN_214c_0933(puVar13,uVar10,uVar8);
      if (!(bool)uVar11) {
        local_12 = local_12 + 3;
      }
    }
    pbVar9 = (byte *)local_6;
    uVar10 = (undefined2)((ulong)local_6 >> 0x10);
    if (local_12 < 1) {
      if (*(char *)0xb8ed == '\0') {
        FUN_1000_0510(*(undefined2 *)(pbVar9 + 4),0xbc);
      }
      else {
        FUN_1000_016a(0x98);
      }
    }
    else {
      local_1f = local_6;
      pbVar9[0x28] = 0;
      if ((*local_6 == 1) && (*local_6 != pbVar9[1])) {
        FUN_1000_7d66(pbVar9,uVar10);
      }
      if (*(char *)0xb8ed == '\0') {
        FUN_1000_0510(*(undefined2 *)((byte *)local_1f + 4),0xb9);
      }
      else {
        FUN_1000_016a(0xb3);
      }
      local_10 = 0;
      if (*(int *)0xb874 < 0x1a) {
        local_17 = *(int *)0xb874;
      }
      else {
        local_17 = 0x19;
      }
      if ((*(int *)0xb92e != 0 || *(int *)0xb930 != 0) &&
         (*(int *)((int)*(undefined4 *)0xb92e + 1) == 0xb)) {
        local_17 = local_17 + 2;
      }
      if (-1 < *(int *)0xb882) {
        local_10 = FUN_214c_1162(*(int *)0xb882 + 1 + (*(int *)0xb888 * local_17) / 10);
        local_10 = local_10 + 1;
      }
      FUN_1000_084b(&local_e,unaff_SS,4);
      local_e = local_10 + local_e;
      local_10 = local_e;
      if (local_e < 0) {
        local_10 = 1;
      }
      bVar2 = *local_1f;
      pbVar9 = (byte *)local_1f;
      uVar10 = (undefined2)((ulong)local_1f >> 0x10);
      if ((bVar2 == 0xea) || (bVar2 == 0xe8)) {
        *(undefined1 *)0xb8ec = 0;
        if ((*local_1f == 0xea) && (uVar11 = pbVar9[0x22] == 0, !(bool)uVar11)) {
          uVar10 = CONCAT11((char)((uint)local_e >> 8),
                            *(undefined1 *)((int)*(undefined4 *)0xb922 + 1));
          puVar13 = local_3f;
          uVar14 = unaff_SS;
          FUN_214c_08af(puVar13);
          FUN_214c_08be(CONCAT11(extraout_AH_01,2));
          FUN_214c_08be(CONCAT11(extraout_AH_02,0xd));
          FUN_214c_0933(puVar13,uVar14,uVar10);
          if (!(bool)uVar11) {
            uVar14 = (undefined2)((ulong)local_1f >> 0x10);
            pbVar9 = (byte *)local_1f;
            if (*(int *)(pbVar9 + 0x2e) != 0 || *(int *)(pbVar9 + 0x30) != 0) {
              *(undefined2 *)((int)*(undefined4 *)(pbVar9 + 0x2e) + 5) = *(undefined2 *)0xb86c;
              *(undefined2 *)((int)*(undefined4 *)(pbVar9 + 0x2e) + 7) = *(undefined2 *)0xb86e;
              uVar11 = FUN_1000_0479(*(undefined2 *)(pbVar9 + 0x2e),*(undefined2 *)(pbVar9 + 0x30));
              uVar14 = (undefined2)((ulong)local_1f >> 0x10);
              pbVar9 = (byte *)local_1f;
              uVar3 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
              *(undefined1 *)
               ((int)uVar3 + *(int *)((int)*(undefined4 *)(pbVar9 + 0x2e) + 5) * 0x4f +
                *(int *)((int)*(undefined4 *)(pbVar9 + 0x2e) + 7) + -0x50) = uVar11;
              FUN_1000_15a2(*(int *)0xe52d * 4 + -0x54d9,unaff_DS,pbVar9 + 0x2e,uVar14);
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
        if (*(int *)((int)*(undefined4 *)0xb922 + 9) < 5) {
          local_10 = 2;
        }
      }
      else if (bVar2 == 1) {
        if (((*(int *)(pbVar9 + 10) < 0x28) && (**(char **)(pbVar9 + 0x2e) == '\x04')) &&
           (*(int *)((int)*(undefined4 *)(pbVar9 + 0x2e) + 1) == 6)) {
          iVar7 = *(int *)(pbVar9 + 0x1c);
          *(undefined1 *)(iVar7 * 0x4f + *(int *)(pbVar9 + 0x1e) + -0xc) = 0x20;
          FUN_1000_0428(CONCAT11((char)((uint)(iVar7 * 0x4f) >> 8),0x20),
                        *(undefined2 *)(pbVar9 + 0x1e),*(undefined2 *)(pbVar9 + 0x1c));
          uVar14 = (undefined2)((ulong)local_1f >> 0x10);
          pbVar9 = (byte *)local_1f;
          pbVar9[0x27] = 1;
          FUN_1000_2363(0xe52d,unaff_DS,pbVar9 + 0x1e,uVar14,pbVar9 + 0x1c,uVar14);
          uVar14 = (undefined2)((ulong)local_1f >> 0x10);
          pbVar9 = (byte *)local_1f;
          *(byte *)(*(int *)(pbVar9 + 0x1c) * 0x4f + *(int *)(pbVar9 + 0x1e) + -0xc) = pbVar9[1];
          pbVar9[0x23] = 0;
          if (*(int *)((int)*(undefined4 *)0xb922 + 9) < 3) {
            local_10 = 1;
          }
        }
      }
      else if (bVar2 == 0xe4) {
        FUN_214c_0cc9();
        uVar11 = 0;
        FUN_214c_0cbb();
        uVar8 = 0x9999;
        uVar10 = 0x1999;
        uVar14 = FUN_214c_0ca9();
        FUN_214c_1178(uVar14,uVar8,uVar10);
        FUN_214c_0cc5();
        if ((bool)uVar11) {
          FUN_1000_54d2(200);
          if (*(int *)((byte *)local_1f + 10) < 0x19) {
            FUN_1000_7923();
            FUN_1000_7923();
            FUN_1000_7923();
            FUN_1000_7923();
            uVar14 = (undefined2)((ulong)local_1f >> 0x10);
            pbVar9 = (byte *)local_1f;
            iVar7 = *(int *)(pbVar9 + 0x1c);
            *(undefined1 *)(iVar7 * 0x4f + *(int *)(pbVar9 + 0x1e) + -0xc) = 0x20;
            FUN_1000_0428(CONCAT11((char)((uint)(iVar7 * 0x4f) >> 8),0x20),
                          *(undefined2 *)(pbVar9 + 0x1e),*(undefined2 *)(pbVar9 + 0x1c));
            uVar14 = (undefined2)((ulong)local_1f >> 0x10);
            FUN_1000_2363(0xe52d,unaff_DS,(byte *)local_1f + 0x1e,uVar14,(byte *)local_1f + 0x1c,
                          uVar14);
            uVar14 = (undefined2)((ulong)local_1f >> 0x10);
            pbVar9 = (byte *)local_1f;
            *(byte *)(*(int *)(pbVar9 + 0x1c) * 0x4f + *(int *)(pbVar9 + 0x1e) + -0xc) = pbVar9[1];
            pbVar9[0x23] = 0;
          }
          else {
            iVar7 = FUN_214c_1162(5);
            if (iVar7 == 0) {
              *(undefined1 *)0xb8ef = 1;
              iVar7 = FUN_214c_1162(0xb);
              *(int *)0xb8ff = iVar7 + 5;
            }
            else if (iVar7 == 1) {
              *(undefined1 *)0xb916 = 1;
              iVar7 = FUN_214c_1162(6);
              *(int *)0xb91c = iVar7 + 5;
            }
            else if (iVar7 == 2) {
              *(undefined1 *)0xb8f2 = 1;
              iVar7 = FUN_214c_1162(10);
              *(int *)0xb905 = iVar7 + 10;
              FUN_20e6_020d();
            }
            else if (iVar7 == 3) {
              *(undefined1 *)0xb8ed = 1;
              iVar7 = FUN_214c_1162(6);
              *(int *)0xb8fb = iVar7 + 5;
            }
            else if (iVar7 == 4) {
              FUN_20e6_020d();
              FUN_1000_0296();
              *(undefined1 *)0xb8ee = 1;
              iVar7 = FUN_214c_1162(0xc);
              *(int *)0xb8fd = iVar7 + 0xc;
              uVar3 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
              *(undefined1 *)((int)uVar3 + 0x719) = 0;
              local_1b = 1;
              while( true ) {
                for (local_19 = 1;
                    *(undefined1 *)(*(int *)0xe52d * 0x719 + local_1b * 0x4f + local_19 + 0x70d) = 0
                    , local_19 != 0x4f; local_19 = local_19 + 1) {
                }
                if (local_1b == 0x17) break;
                local_1b = local_1b + 1;
              }
            }
          }
          if (*(int *)((int)*(undefined4 *)0xb922 + 9) < 4) {
            local_10 = 1;
          }
        }
      }
      else if (bVar2 == 0x48) {
        if (*(int *)((int)*(undefined4 *)0xb922 + 1) == 10) {
          *(int *)(pbVar9 + 10) = *(int *)(pbVar9 + 10) - local_10;
        }
      }
      else if ((bVar2 == 0x42) || (bVar2 == 1)) {
        if (*(int *)((int)*(undefined4 *)0xb922 + 1) == 0xe) {
          *(int *)(pbVar9 + 10) = *(int *)(pbVar9 + 10) - local_10;
        }
      }
      else if (bVar2 == 0x73) {
        if (*(int *)((int)*(undefined4 *)0xb922 + 9) < 4) {
          local_10 = 1;
        }
      }
      else if ((bVar2 == 0x44) || (bVar2 == 0x92)) {
        if (*(int *)((int)*(undefined4 *)0xb922 + 1) == 0xe) {
          *(int *)(pbVar9 + 10) = *(int *)(pbVar9 + 10) - local_10;
        }
        iVar7 = (int)(*(int *)0xb884 + local_c) >> 0xf;
        FUN_214c_0cc9();
        uVar11 = 0;
        uVar12 = 1;
        FUN_214c_0cbb();
        uVar10 = FUN_214c_0ca3();
        FUN_214c_1178(uVar10,uVar14,iVar7);
        FUN_214c_0cc5();
        if (!(bool)uVar11 && !(bool)uVar12) {
          FUN_1000_54d2(0x50);
          local_12 = 0;
          local_21 = *(int *)((byte *)local_1f + 0xe);
          if (0 < local_21) {
            local_1b = 1;
            while( true ) {
              iVar7 = FUN_214c_1162(*(undefined2 *)((byte *)local_1f + 0x10));
              local_12 = local_12 + 1 + iVar7;
              if (local_1b == local_21) break;
              local_1b = local_1b + 1;
            }
          }
          cVar4 = FUN_1000_06d5(0xd);
          if (cVar4 != '\0') {
            local_12 = local_12 / 3 + 1;
          }
          *(int *)0xb870 = *(int *)0xb870 - local_12;
          FUN_1000_0296();
          if (*(int *)0xb870 < 1) {
            FUN_1000_7364((int)param_1,(int)((ulong)param_1 >> 0x10),
                          *(undefined2 *)((byte *)local_1f + 2));
          }
          FUN_1000_7dab();
        }
      }
      uVar14 = (undefined2)((ulong)local_1f >> 0x10);
      *(int *)((byte *)local_1f + 10) = *(int *)((byte *)local_1f + 10) - local_10;
      if ((*(int *)((int)*(undefined4 *)0xb922 + 1) == 0xf) &&
         (iVar7 = FUN_214c_1162(4), iVar7 == 0)) {
        *(int *)0xb870 = local_10 / 2 + *(int *)0xb870;
        if (*(int *)0xb872 < *(int *)0xb870) {
          *(undefined2 *)0xb870 = *(undefined2 *)0xb872;
        }
        FUN_1000_0296();
      }
      uVar14 = (undefined2)((ulong)local_1f >> 0x10);
      pbVar9 = (byte *)local_1f;
      uVar11 = *(int *)(pbVar9 + 10) == 1;
      if (*(int *)(pbVar9 + 10) < 1) {
        uVar5 = (uint)*local_6;
        puVar13 = local_3f;
        FUN_214c_08af(puVar13);
        FUN_214c_08be(CONCAT11(extraout_AH_03,0x48));
        FUN_214c_08be(CONCAT11(extraout_AH_04,0x45));
        FUN_214c_0933(puVar13,unaff_SS,uVar5);
        if (!(bool)uVar11) {
          *(int *)(*(int *)0xe52d * 2 + 0x799b) = *(int *)(*(int *)0xe52d * 2 + 0x799b) + -1;
        }
        FUN_1000_79ea(1,(byte *)local_6,local_6._2_2_);
      }
      else {
        bVar2 = *local_1f;
        if ((bVar2 == 0x48) || (bVar2 == 0x45)) {
          pbVar9[0x22] = 1;
        }
        else if ((bVar2 == 0xe8) || (bVar2 == 0xea)) {
          (pbVar9 + 0x20)[0] = 1;
          (pbVar9 + 0x20)[1] = 0;
        }
      }
    }
  }
  return;
}



void FUN_1000_8d6d(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  iVar1 = *(int *)0xb936;
  *(undefined2 *)(iVar1 * 4 + -0x46cc) = 0;
  *(undefined2 *)(iVar1 * 4 + -0x46ca) = 0;
  *(int *)0xb936 = *(int *)0xb936 + -1;
  *(int *)0xb878 = *(int *)0xb878 + -2;
  iVar1 = *(int *)0xb936;
  local_4 = param_1 + 1;
  if (local_4 <= iVar1) {
    while( true ) {
      uVar2 = *(undefined4 *)(local_4 * 4 + -0x46cc);
      iVar3 = (local_4 + -1) * 4;
      *(undefined2 *)(iVar3 + -0x46cc) = (int)uVar2;
      *(undefined2 *)(iVar3 + -0x46ca) = (int)((ulong)uVar2 >> 0x10);
      if (local_4 == iVar1) break;
      local_4 = local_4 + 1;
    }
  }
  FUN_1000_0296();
  FUN_1000_016a(0xfe59);
  return;
}



void __cdecl16near FUN_1000_8e03(void)

{
  char *pcVar1;
  char cVar2;
  undefined2 uVar3;
  undefined1 extraout_AH;
  int iVar4;
  int iVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  undefined1 *puVar8;
  undefined1 local_26 [32];
  undefined4 local_6;
  
  pcVar1 = (char *)*(undefined4 *)0xb91e;
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
    uVar3 = FUN_214c_0285();
    puVar8 = local_26;
    uVar6 = unaff_SS;
    FUN_214c_08af(puVar8);
    FUN_214c_08df(CONCAT11(extraout_AH,5),CONCAT11(extraout_AH,2));
    FUN_214c_0933(puVar8,uVar6,uVar3);
    if (!(bool)uVar7) {
      iVar4 = FUN_214c_0285();
      iVar5 = FUN_214c_0285();
      *(undefined1 *)(iVar5 * 0x18 + iVar4 + -0x65a2) = 1;
    }
    pcVar1 = *(char **)((char *)local_6 + 0x16);
  }
  uVar6 = FUN_214c_0285();
  *(undefined2 *)0xb870 = uVar6;
  FUN_214c_0cc9();
  FUN_214c_0cb5();
  FUN_214c_0ccd();
  uVar6 = FUN_214c_0285();
  *(undefined2 *)0xb872 = uVar6;
  uVar6 = FUN_214c_0285();
  *(undefined2 *)0xb874 = uVar6;
  uVar6 = FUN_214c_0285();
  *(undefined2 *)0xb876 = uVar6;
  cVar2 = FUN_1000_06d5(2);
  if (cVar2 != '\0') {
    uVar6 = FUN_214c_0285();
    *(undefined2 *)0xb874 = uVar6;
    uVar6 = FUN_214c_0285();
    *(undefined2 *)0xb876 = uVar6;
  }
  if (*(int *)0xb874 < 0) {
    *(undefined2 *)0xb874 = 0;
  }
  FUN_1000_0296();
  FUN_1000_016a(0xfe5a);
  return;
}



void FUN_1000_8f6e(undefined4 *param_1)

{
  undefined4 uVar1;
  bool bVar2;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  bVar2 = false;
  *(undefined1 *)((int)*param_1 + 0x14) = 1;
  local_4 = 0;
  do {
    local_4 = local_4 + 1;
    if (*(int *)(local_4 * 4 + -0x46cc) == 0 && *(int *)(local_4 * 4 + -0x46ca) == 0) break;
  } while (local_4 != *(int *)0xb936);
  if (*(int *)(local_4 * 4 + -0x46cc) == 0 && *(int *)(local_4 * 4 + -0x46ca) == 0) {
    uVar1 = *param_1;
    *(undefined2 *)(local_4 * 4 + -0x46cc) = (int)uVar1;
    *(undefined2 *)(local_4 * 4 + -0x46ca) = (int)((ulong)uVar1 >> 0x10);
    bVar2 = true;
    FUN_1000_1448();
    FUN_1000_016a(0xffac);
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
      uVar1 = *param_1;
      *(undefined2 *)(local_4 * 4 + -0x46cc) = (int)uVar1;
      *(undefined2 *)(local_4 * 4 + -0x46ca) = (int)((ulong)uVar1 >> 0x10);
      bVar2 = true;
      FUN_1000_1448();
      FUN_1000_016a(0xffac);
    }
  }
  if (((bVar2) && (*(int *)((int)*param_1 + 1) == 8)) && (*(int *)((int)*param_1 + 9) == 1)) {
    FUN_1000_8e03();
    *(undefined2 *)((int)*param_1 + 9) = 0;
  }
  if ((bVar2) && (*(int *)((int)*param_1 + 1) == 0xc)) {
    FUN_1000_8d6d(local_4);
  }
  return;
}



void __cdecl16near FUN_1000_9099(void)

{
  uint uVar1;
  undefined4 uVar2;
  char *pcVar3;
  char cVar4;
  byte extraout_AH;
  uint uVar5;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  int iVar6;
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
  char local_14;
  char local_13;
  char local_12;
  undefined4 local_11;
  undefined4 local_d;
  int local_5;
  
  uVar11 = 0x1000;
  FUN_1000_1988(&local_11,unaff_SS,0xb86e,unaff_DS,0xb86c,unaff_DS);
  FUN_1000_0040();
  FUN_1000_016a(0x75);
  FUN_1000_557c((uint)extraout_AH << 8,CONCAT11(extraout_AH,1),(char *)local_11,local_11._2_2_);
  pcVar7 = (char *)local_11;
  uVar9 = (undefined2)((ulong)local_11 >> 0x10);
  if (*local_11 == '\0') {
    uVar5 = *(uint *)(pcVar7 + 9);
    uVar1 = *(uint *)0xb8c8;
    iVar6 = *(int *)0xb8ca;
    *(int *)0xb8c8 = uVar5 + *(uint *)0xb8c8;
    *(int *)0xb8ca = ((int)uVar5 >> 0xf) + iVar6 + (uint)CARRY2(uVar5,uVar1);
    FUN_1000_14ab(*(int *)0xe52d * 4 + -0x54d9,unaff_DS,&local_11,unaff_SS);
    FUN_1000_063c((char *)local_11,local_11._2_2_);
    uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    *(undefined1 *)((int)uVar2 + *(int *)0xb86c * 0x4f + *(int *)0xb86e + -0x50) = 0x20;
    FUN_1000_0296();
    return;
  }
  local_13 = *(int *)0xb8c6 < *(int *)0xb8c4 + *(int *)(pcVar7 + 0xb);
  if (*local_11 == '\x04') {
    uVar12 = *(uint *)(pcVar7 + 1) < 6;
    uVar13 = *(uint *)(pcVar7 + 1) == 6;
    if (!(bool)uVar13) {
      FUN_214c_1178();
      uVar11 = 0x214c;
      FUN_214c_0cc5();
      if (!(bool)uVar12 && !(bool)uVar13) {
        FUN_1000_8f6e(&local_11,unaff_SS);
        local_12 = '\x01';
        goto LAB_1000_9184;
      }
    }
  }
  local_12 = '\0';
LAB_1000_9184:
  if ((local_13 == '\0') || (local_12 != '\0')) {
    uVar2 = *(undefined4 *)(*local_11 * 4 + -0x4738);
    uVar5 = (uint)uVar2;
    cVar4 = *local_11;
    *(int *)(cVar4 * 4 + -0x4738) = uVar5 + 1;
    *(int *)(cVar4 * 4 + -0x4736) = (int)((ulong)uVar2 >> 0x10) + (uint)(0xfffe < uVar5);
    *(int *)0xb8c0 = *(int *)0xb8c0 + 1;
    uVar9 = (undefined2)((ulong)local_11 >> 0x10);
    *(int *)0xb8c4 = *(int *)0xb8c4 + *(int *)((char *)local_11 + 0xb);
    if ((*local_11 == '\b') && (*(int *)((char *)local_11 + 1) == 0)) {
      *(undefined1 *)0xb918 = 1;
    }
    FUN_1000_14ab(*(int *)0xe52d * 4 + -0x54d9,unaff_DS,&local_11,unaff_SS);
    uVar9 = (undefined2)((ulong)local_11 >> 0x10);
    pcVar7 = (char *)local_11;
    uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    *(undefined1 *)((int)uVar2 + *(int *)(pcVar7 + 5) * 0x4f + *(int *)(pcVar7 + 7) + -0x50) = 0x20;
    if (*local_11 == '\b') {
      iVar6 = *(int *)(pcVar7 + 1);
      *(undefined2 *)(iVar6 * 4 + -0x476c) = pcVar7;
      *(undefined2 *)(iVar6 * 4 + -0x476a) = uVar9;
    }
    pcVar3 = (char *)*(undefined4 *)0xb91e;
    local_14 = '\0';
    local_5 = 1;
    while( true ) {
      local_d._0_2_ = (char *)pcVar3;
      local_d._2_2_ = (uint)((ulong)pcVar3 >> 0x10);
      uVar5 = (uint)(char *)local_d | local_d._2_2_;
      if ((uVar5 == 0) || (local_14 != '\0')) break;
      uVar12 = *pcVar3 == *local_11;
      local_d = pcVar3;
      if ((bool)uVar12) {
        uVar10 = CONCAT11((char)(uVar5 >> 8),*local_11);
        puVar14 = local_34;
        uVar9 = unaff_SS;
        FUN_214c_08af(puVar14);
        FUN_214c_08be(CONCAT11(extraout_AH_00,2));
        FUN_214c_08be(CONCAT11(extraout_AH_01,3));
        uVar11 = 0x214c;
        FUN_214c_0933(puVar14,uVar9,uVar10);
        if ((((bool)uVar12) || (*(int *)((char *)local_d + 1) != *(int *)((char *)local_11 + 1))) &&
           (*local_11 != '\x01')) {
          cVar4 = FUN_1000_052b((char *)local_11,local_11._2_2_);
          if (cVar4 != '\0') {
            cVar4 = FUN_1000_052b((char *)local_d,local_d._2_2_);
            if ((cVar4 != '\0') &&
               (*(int *)((char *)local_11 + 0x11) == *(int *)((char *)local_d + 0x11)))
            goto LAB_1000_9300;
          }
        }
        else {
LAB_1000_9300:
          local_14 = '\x01';
          cVar4 = FUN_1000_052b((char *)local_11,local_11._2_2_);
          pcVar7 = (char *)local_11;
          uVar9 = (undefined2)((ulong)local_11 >> 0x10);
          pcVar8 = (char *)local_d;
          uVar11 = (undefined2)((ulong)local_d >> 0x10);
          if ((cVar4 != '\0') && (*(int *)(pcVar7 + 0x11) == *(int *)(pcVar8 + 0x11))) {
            uVar2 = *(undefined4 *)(*local_11 * 4 + -0x4738);
            iVar6 = (int)uVar2;
            cVar4 = *local_11;
            *(int *)(cVar4 * 4 + -0x4738) = iVar6 + -1;
            *(int *)(cVar4 * 4 + -0x4736) = (int)((ulong)uVar2 >> 0x10) - (uint)(iVar6 == 0);
            *(int *)0xb8c0 = *(int *)0xb8c0 + -1;
            *(int *)0xb8c4 = *(int *)0xb8c4 - *(int *)(pcVar7 + 0xb);
          }
          *(int *)(pcVar8 + 3) = *(int *)(pcVar8 + 3) + *(int *)(pcVar7 + 3);
          uVar11 = 0xe654;
          uVar9 = unaff_DS;
          FUN_214c_17f7(0,0x908d,0x214c);
          FUN_214c_1755(uVar11,uVar9);
          if (local_5 < 0x1b) {
            uVar11 = 0xe654;
            uVar9 = unaff_DS;
            FUN_214c_1799(0,local_5 + 0x60);
            FUN_214c_1755(uVar11,uVar9);
          }
          else {
            uVar11 = 0xe654;
            uVar9 = unaff_DS;
            FUN_214c_1799(0,local_5 + 0x26);
            FUN_214c_1755(uVar11,uVar9);
          }
          uVar10 = 0xe654;
          uVar9 = unaff_DS;
          FUN_214c_17f7(0,0x9090,0x214c);
          uVar11 = 0x214c;
          FUN_214c_1755(uVar10,uVar9);
          FUN_1000_063c((char *)local_11,local_11._2_2_);
        }
      }
      local_5 = local_5 + 1;
      pcVar3 = *(char **)((char *)local_d + 0x16);
    }
    if (local_14 == '\0') {
      local_d = (char *)*(undefined4 *)0xb91e;
      *(int *)0xb8c2 = *(int *)0xb8c2 + 1;
      pcVar7 = (char *)local_11;
      uVar9 = (undefined2)((ulong)local_11 >> 0x10);
      if (((char *)local_d == (char *)0x0 && (int)((ulong)local_d >> 0x10) == 0) ||
         (*local_11 < *local_d)) {
        uVar2 = *(undefined4 *)0xb91e;
        *(int *)(pcVar7 + 0x16) = (int)uVar2;
        *(int *)(pcVar7 + 0x18) = (int)((ulong)uVar2 >> 0x10);
        *(undefined2 *)0xb91e = pcVar7;
        *(undefined2 *)0xb920 = uVar9;
        uVar9 = 0xe654;
        FUN_214c_17f7(0,0x9093,uVar11);
        FUN_214c_1755(uVar9,unaff_DS);
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
        FUN_214c_17f7(0,0x908d,uVar11);
        FUN_214c_1755(uVar10,uVar9);
        if (local_5 < 0x1b) {
          uVar11 = 0xe654;
          uVar9 = unaff_DS;
          FUN_214c_1799(0,local_5 + 0x60);
          FUN_214c_1755(uVar11,uVar9);
        }
        else {
          uVar11 = 0xe654;
          uVar9 = unaff_DS;
          FUN_214c_1799(0,local_5 + 0x26);
          FUN_214c_1755(uVar11,uVar9);
        }
        uVar9 = 0xe654;
        FUN_214c_17f7(0,0x9090,0x214c);
        FUN_214c_1755(uVar9,unaff_DS);
      }
    }
  }
  else {
    FUN_1000_1448();
    FUN_1000_0040();
    FUN_1000_016a(0x4a);
  }
  return;
}



void FUN_1000_9554(undefined2 param_1,undefined1 param_2,undefined1 param_3,int param_4,char param_5
                  )

{
  int iVar1;
  undefined1 extraout_AH;
  byte extraout_AH_00;
  undefined2 unaff_DS;
  undefined2 uVar2;
  
  FUN_20e6_02be(param_2);
  FUN_20e6_0260(CONCAT11(extraout_AH,param_3),CONCAT11(extraout_AH,1));
  uVar2 = 0xe654;
  FUN_214c_17f7(0,param_5 * 0x2b8 + param_4 * 0x1d + 0x75fa,unaff_DS);
  iVar1 = *(int *)(param_5 * 0x30 + param_4 * 2 + -0x71d3);
  FUN_214c_1882(6,iVar1,iVar1 >> 0xf);
  FUN_214c_17f7(0,0x9550,0x214c);
  FUN_214c_173c(0x214c,uVar2);
  FUN_20e6_02be((uint)extraout_AH_00 << 8);
  return;
}



void __cdecl16near FUN_1000_95ee(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  byte bVar5;
  undefined1 uVar6;
  undefined1 extraout_AH;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  undefined2 uVar10;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar11;
  undefined1 *puVar12;
  undefined2 uVar13;
  undefined1 local_316 [256];
  undefined1 local_216 [254];
  undefined4 local_118;
  char local_114;
  char *local_113;
  byte abStack_10c [257];
  char local_b;
  int local_a;
  int local_8;
  uint local_6;
  uint local_4;
  
  FUN_20e6_020d();
  uVar13 = 0xe654;
  FUN_214c_17f7(0,0x95da,0x20e6);
  FUN_214c_173c(0x214c,uVar13);
  uVar13 = 0xe654;
  FUN_214c_17f7(0,0x95e5,0x214c);
  FUN_214c_173c(0x214c,uVar13);
  local_b = FUN_20e6_0357();
  if (local_b == '1') {
    local_114 = '\x06';
  }
  else {
    local_114 = '\a';
  }
  abStack_10c[1] = 0;
  local_6 = 0;
  FUN_20e6_020d();
  iVar8 = *(int *)(local_114 * 4 + 0x79b3);
  local_118 = (char *)CONCAT22(iVar8,(int)local_118);
  if (0 < iVar8) {
    local_a = 1;
    while( true ) {
      uVar1 = *(uint *)(local_114 * 0x30 + local_a * 2 + -0x71d3);
      iVar8 = (int)uVar1 >> 0xf;
      if (((iVar8 < *(int *)0xb8ca) || ((iVar8 <= *(int *)0xb8ca && (uVar1 < *(uint *)0xb8c8)))) &&
         (*(int *)(local_114 * 0x30 + local_a * 2 + -0x71d3) != 0)) {
        local_6 = local_6 + 1;
        puVar12 = local_316;
        uVar10 = unaff_SS;
        FUN_214c_0693(abStack_10c + 1,unaff_SS);
        puVar11 = local_216;
        uVar13 = unaff_SS;
        FUN_214c_07ae(local_a + 0x28);
        FUN_214c_0720(puVar11,uVar13);
        FUN_214c_06ad(0xff,abStack_10c + 1,unaff_SS,puVar12,uVar10);
        FUN_1000_9554(&stack0xfffe,0,local_6,local_a,CONCAT11(extraout_AH,local_114));
      }
      if (local_a == local_118._2_2_) break;
      local_a = local_a + 1;
    }
  }
  if (0 < (int)local_6) {
    local_6 = 1;
    local_4 = 1;
    local_a = abStack_10c[2] - 0x28;
    FUN_1000_9554(&stack0xfffe,0xf,1,local_a,CONCAT11((char)((uint)local_a >> 8),local_114));
    local_b = ' ';
    local_8 = local_a;
    while (local_b != '\r') {
      local_b = FUN_20e6_0357();
      if (local_b == '\0') {
        local_b = FUN_20e6_0357();
      }
      if ((local_b == 'P') || (local_b == '2')) {
        if ((int)local_6 < (int)(uint)abStack_10c[1]) {
          local_4 = local_6 + 1;
          bVar5 = abStack_10c[local_6 + 2];
        }
        else {
          local_4 = 1;
          bVar5 = abStack_10c[2];
        }
        local_8 = bVar5 - 0x28;
      }
      else if ((local_b == 'H') || (local_b == '8')) {
        if ((int)local_6 < 2) {
          local_8 = abStack_10c[abStack_10c[1] + 1] - 0x28;
          local_4 = (uint)abStack_10c[1];
        }
        else {
          local_8 = abStack_10c[local_6] - 0x28;
          local_4 = local_6 - 1;
        }
      }
      if (local_8 != local_a) {
        FUN_1000_9554(&stack0xfffe,0,local_6,local_a,local_114);
        local_a = local_8;
        local_6 = local_4;
        FUN_1000_9554(&stack0xfffe,0xf,local_4,local_8,local_114);
      }
    }
    uVar1 = *(uint *)(local_114 * 0x30 + local_a * 2 + -0x71d3);
    uVar2 = *(undefined4 *)0xb8c8;
    uVar7 = (uint)uVar2;
    *(int *)0xb8c8 = uVar7 - uVar1;
    *(int *)0xb8ca = ((int)((ulong)uVar2 >> 0x10) - ((int)uVar1 >> 0xf)) - (uint)(uVar7 < uVar1);
    FUN_1000_05d6(&local_113,unaff_SS);
    uVar13 = (undefined2)((ulong)local_113 >> 0x10);
    pcVar9 = (char *)local_113;
    local_118 = local_113;
    *local_113 = local_114;
    *(int *)(pcVar9 + 1) = local_a;
    (pcVar9 + 3)[0] = '\x01';
    (pcVar9 + 3)[1] = '\0';
    (pcVar9 + 9)[0] = '\0';
    (pcVar9 + 9)[1] = '\0';
    uVar13 = FUN_1000_260c(local_a,local_114);
    uVar10 = (undefined2)((ulong)local_118 >> 0x10);
    pcVar9 = (char *)local_118;
    *(undefined2 *)(pcVar9 + 0xb) = uVar13;
    pcVar9[0x14] = '\0';
    pcVar9[0x13] = '\0';
    FUN_1000_2574(*(undefined2 *)0xe52d,&local_113,unaff_SS);
    uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
    uVar3 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
    uVar4 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    *(undefined1 *)((int)uVar4 + *(int *)((int)uVar3 + 5) * 0x4f + *(int *)((int)uVar2 + 7) + -0x50)
         = 0x20;
    uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
    *(undefined2 *)((int)uVar2 + 5) = *(undefined2 *)0xb86c;
    uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
    *(undefined2 *)((int)uVar2 + 7) = *(undefined2 *)0xb86e;
    uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
    uVar3 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
    FUN_1000_491d((int)uVar3 + 7,(int)((ulong)uVar3 >> 0x10),(int)uVar2 + 5,
                  (int)((ulong)uVar2 >> 0x10));
    uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
    local_118._2_2_ = (int)((ulong)uVar2 >> 0x10);
    local_118._0_2_ = (int)uVar2;
    uVar6 = FUN_1000_0479(*(undefined2 *)(*(int *)0xe52d * 4 + -0x54d9),
                          *(undefined2 *)(*(int *)0xe52d * 4 + -0x54d7));
    uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    *(undefined1 *)
     ((int)uVar2 + *(int *)((int)local_118 + 5) * 0x4f + *(int *)((int)local_118 + 7) + -0x50) =
         uVar6;
    FUN_1000_11fc(0x17);
    FUN_1000_0296();
  }
  return;
}



void FUN_1000_99c5(char *param_1)

{
  undefined4 uVar1;
  uint in_AX;
  byte extraout_AH;
  undefined1 extraout_AH_00;
  int iVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  char local_3;
  
  FUN_1000_08bd(in_AX & 0xff00,&local_3,unaff_SS,&param_1,unaff_SS);
  if (local_3 != '\0') {
    FUN_1000_016a(0x76);
    FUN_1000_557c((uint)extraout_AH << 8,(uint)extraout_AH << 8,(char *)param_1,param_1._2_2_);
    FUN_1000_15d3(CONCAT11(extraout_AH_00,1),CONCAT11(extraout_AH_00,1),(char *)param_1,
                  param_1._2_2_);
    if (*param_1 == '\b') {
      FUN_1000_07fb();
      if (*(int *)0xb894 == 0 && *(int *)0xb896 == 0) {
        *(undefined1 *)0xb918 = 0;
        iVar2 = 0;
        if (*(int *)0xe52d == 1) {
          iVar2 = *(int *)0x78f1 * 0x4f;
          uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
          *(undefined1 *)((int)uVar1 + iVar2 + *(int *)0x78f3 + -0x50) = 0x20;
        }
        FUN_1000_0428(CONCAT11((char)((uint)iVar2 >> 8),0x20),*(undefined2 *)0x78f3,
                      *(undefined2 *)0x78f1);
      }
    }
    FUN_1000_0296();
  }
  return;
}



void FUN_1000_9a91(char *param_1)

{
  char cVar1;
  byte extraout_AH;
  byte extraout_AH_00;
  byte bVar2;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  char *pcVar3;
  int iVar4;
  undefined2 uVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  bool bVar7;
  undefined1 *puVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined1 local_22 [32];
  
  cVar1 = *param_1;
  if ((((cVar1 == '\x01') || (cVar1 == '\a')) || (cVar1 == '\x06')) || (cVar1 == '\b')) {
    FUN_1000_016a(0x40);
    return;
  }
  if (((cVar1 != '\x03') && (cVar1 != '\x02')) && ((cVar1 != '\x04' && (cVar1 != '\x05')))) {
    return;
  }
  uVar5 = (undefined2)((ulong)param_1 >> 0x10);
  pcVar3 = (char *)param_1;
  if (*(char *)(*param_1 * 0x18 + *(int *)(pcVar3 + 1) + -0x65a2) != '\0') {
    FUN_1000_016a(0x77);
    return;
  }
  FUN_1000_0040();
  if (*(int *)(pcVar3 + 3) == 1) {
    uVar9 = 0xe654;
    uVar10 = unaff_DS;
    FUN_214c_17f7(0,0x9a60,0x1000);
    FUN_214c_1755(uVar9,uVar10);
    bVar2 = extraout_AH;
  }
  else {
    uVar9 = 0xe654;
    uVar10 = unaff_DS;
    FUN_214c_17f7(0,0x9a66,0x1000);
    FUN_214c_1755(uVar9,uVar10);
    bVar2 = extraout_AH_00;
  }
  FUN_1000_557c((uint)bVar2 << 8,CONCAT11(bVar2,1),pcVar3,uVar5);
  FUN_1000_1448();
  FUN_1000_0040();
  uVar9 = 0xe654;
  uVar10 = unaff_DS;
  FUN_214c_17f7(0,0x9a6e,0x214c);
  FUN_214c_1755(uVar9,uVar10);
  uVar6 = *(int *)(pcVar3 + 3) == 1;
  if (*(int *)(pcVar3 + 3) < 2) {
    uVar10 = CONCAT11(extraout_AH_01,*param_1);
    puVar8 = local_22;
    FUN_214c_08af(puVar8);
    FUN_214c_08be(CONCAT11(extraout_AH_02,2));
    FUN_214c_08be(CONCAT11(extraout_AH_03,5));
    FUN_214c_0933(puVar8,unaff_SS,uVar10);
    if ((bool)uVar6) {
      uVar9 = 0xe654;
      uVar10 = unaff_DS;
      FUN_214c_17f7(0,0x9a7f,0x214c);
      FUN_214c_1755(uVar9,uVar10);
    }
    else {
      uVar9 = 0xe654;
      uVar10 = unaff_DS;
      FUN_214c_17f7(0,0x9a7b,0x214c);
      FUN_214c_1755(uVar9,uVar10);
    }
  }
  else {
    uVar9 = 0xe654;
    uVar10 = unaff_DS;
    FUN_214c_17f7(0,0x9a76,0x214c);
    FUN_214c_1755(uVar9,uVar10);
  }
  uVar9 = 0xe654;
  uVar10 = unaff_DS;
  FUN_214c_17f7(0,0x9a83,0x214c);
  FUN_214c_1755(uVar9,uVar10);
  uVar10 = 0xe554;
  FUN_214c_17be(0x1c,*param_1 * 0x2b8 + *(int *)(pcVar3 + 1) * 0x1d + -0x75de,unaff_DS);
  FUN_214c_16ef(0x214c,uVar10);
  if (*(char *)(*param_1 * 0x18 + *(int *)(pcVar3 + 1) + -0x6542) == '\0') {
    iVar4 = *param_1 * 0x2b8 + *(int *)(pcVar3 + 1) * 0x1d + -0x75de;
    bVar7 = iVar4 == 0;
    FUN_214c_0783(0x9a90,0x214c,iVar4,unaff_DS);
    if (bVar7) {
      uVar6 = 0;
      goto LAB_1000_9c7c;
    }
  }
  uVar6 = 1;
LAB_1000_9c7c:
  *(undefined1 *)(*param_1 * 0x18 + *(int *)(pcVar3 + 1) + -0x6542) = uVar6;
  return;
}



void FUN_1000_9ca1(byte *param_1)

{
  uint uVar1;
  undefined1 extraout_AH;
  int iVar2;
  byte bVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined1 local_22 [32];
  
  uVar4 = &stack0x0000 == (undefined1 *)0x22;
  uVar1 = (uint)*param_1;
  puVar5 = local_22;
  FUN_214c_08af(puVar5);
  FUN_214c_08df(CONCAT11(extraout_AH,5),CONCAT11(extraout_AH,2));
  iVar2 = FUN_214c_0933(puVar5,unaff_SS,uVar1);
  if (!(bool)uVar4) {
    iVar2 = (char)*param_1 * 0x18;
    *(undefined1 *)(iVar2 + *(int *)((byte *)param_1 + 1) + -0x65a2) = 1;
  }
  if (*param_1 == 8) {
    if (((byte *)param_1)[0x14] == 0) {
      ((byte *)param_1)[0x13] = 1;
    }
    else {
      ((byte *)param_1)[0x14] = 0;
    }
  }
  else {
    ((byte *)param_1)[0x13] = 1;
  }
  if ((*param_1 == 1) && (*(int *)((byte *)param_1 + 3) == 1)) {
    FUN_1000_016a(0xb7);
  }
  else {
    bVar3 = (byte)((uint)iVar2 >> 8);
    FUN_1000_557c((uint)bVar3 << 8,CONCAT11(bVar3,1),(byte *)param_1,param_1._2_2_);
  }
  return;
}



void FUN_1000_9d52(char *param_1)

{
  int iVar1;
  char *pcVar2;
  byte extraout_AH;
  byte extraout_AH_00;
  byte bVar5;
  int iVar3;
  undefined2 uVar4;
  undefined1 extraout_AH_01;
  int iVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  undefined1 *puVar8;
  undefined2 uVar9;
  undefined1 local_25 [32];
  char local_5;
  
  local_5 = '\0';
  iVar6 = (int)((ulong)param_1 >> 0x10);
  pcVar2 = (char *)param_1;
  if ((iVar6 == *(int *)0xb924) && (pcVar2 == (char *)*(undefined2 *)0xb922)) {
    FUN_1000_016a(0x78);
  }
  else {
    FUN_1000_0040();
    if (*param_1 == '\a') {
      FUN_1000_016a(0xaf);
      bVar5 = extraout_AH;
    }
    else {
      FUN_1000_016a(0x7a);
      bVar5 = extraout_AH_00;
    }
    FUN_1000_557c((uint)bVar5 << 8,CONCAT11(bVar5,1),pcVar2,iVar6);
    if (*param_1 == '\a') {
      uVar9 = 0xe654;
      uVar4 = unaff_DS;
      FUN_214c_17f7(0,0x9d48,0x1000);
      FUN_214c_1755(uVar9,uVar4);
      *(undefined2 *)0xb922 = pcVar2;
      *(int *)0xb924 = iVar6;
      *(int *)0xb882 = *(int *)(*(int *)(pcVar2 + 1) * 4 + -0x6185) + *(int *)(pcVar2 + 9);
      FUN_1000_227b();
    }
    else if (*param_1 == '\x06') {
      if (*(int *)0xb874 < 0x1d) {
        FUN_1000_00b3();
        iVar3 = *(int *)(pcVar2 + 1);
        if (iVar3 == 7) {
          if (*(int *)0xb92a == 0 && *(int *)0xb92c == 0) {
            *(undefined2 *)0xb92a = pcVar2;
            *(int *)0xb92c = iVar6;
            iVar3 = FUN_1000_0000(pcVar2 + 9,iVar6);
            *(int *)0xb87e = (iVar3 + *(int *)(pcVar2 + 9)) / 2;
            local_5 = '\x01';
          }
          else {
            FUN_1000_016a(0xff37);
          }
        }
        else if (iVar3 == 8) {
          if (*(int *)0xb932 == 0 && *(int *)0xb934 == 0) {
            *(undefined2 *)0xb932 = pcVar2;
            *(int *)0xb934 = iVar6;
            *(undefined2 *)0xb884 = *(undefined2 *)((int)*(undefined4 *)0xb932 + 9);
            local_5 = '\x01';
          }
          else {
            FUN_1000_016a(0xff87);
          }
        }
        else if ((iVar3 < 9) || (0xb < iVar3)) {
          if (*(int *)0xb926 == 0 && *(int *)0xb928 == 0) {
            *(undefined2 *)0xb926 = pcVar2;
            *(int *)0xb928 = iVar6;
            *(int *)0xb87c = *(int *)(*(int *)(pcVar2 + 1) * 4 + -0x61e5) + *(int *)(pcVar2 + 9);
            local_5 = '\x01';
          }
          else {
            FUN_1000_016a(0xff87);
          }
        }
        else if (*(int *)0xb92e == 0 && *(int *)0xb930 == 0) {
          *(undefined2 *)0xb92e = pcVar2;
          *(int *)0xb930 = iVar6;
          local_5 = '\x01';
        }
        else {
          FUN_1000_016a(0xff87);
        }
        iVar3 = *(int *)0xb87c;
        iVar1 = *(int *)0xb87e;
        *(int *)0xb880 = iVar3 + iVar1;
        uVar7 = local_5 == '\0';
        if (!(bool)uVar7) {
          uVar4 = CONCAT11((char)((uint)(iVar3 + iVar1) >> 8),pcVar2[1]);
          puVar8 = local_25;
          FUN_214c_08af(puVar8);
          FUN_214c_08df(CONCAT11(extraout_AH_01,0xb),CONCAT11(extraout_AH_01,9));
          FUN_214c_0933(puVar8,unaff_SS,uVar4);
          if ((bool)uVar7) {
            pcVar2[0x13] = '\x01';
          }
        }
      }
      else {
        FUN_1000_016a(200);
      }
    }
    FUN_1000_0296();
  }
  return;
}



void __cdecl16near FUN_1000_9f40(void)

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
  char local_2d;
  undefined1 local_2c [32];
  char local_c [5];
  char local_7;
  undefined4 local_6;
  
  FUN_1000_0040();
  local_2d = '\0';
  local_c[0] = '\0';
  puVar6 = local_4d;
  uVar2 = unaff_SS;
  FUN_214c_08af(puVar6);
  FUN_214c_0913(0x20,local_2c,unaff_SS,puVar6,uVar2);
  if (*(int *)0xb926 != 0 || *(int *)0xb928 != 0) {
    FUN_214c_06ad(4,local_c,unaff_SS,0x9f38,0x214c);
    puVar6 = local_4d;
    uVar2 = unaff_SS;
    FUN_214c_08af(puVar6);
    FUN_214c_08be(CONCAT11(extraout_AH,0x61));
    FUN_214c_0913(0x20,local_2c,unaff_SS,puVar6,uVar2);
  }
  if (*(int *)0xb92a != 0 || *(int *)0xb92c != 0) {
    puVar6 = local_12d;
    uVar2 = unaff_SS;
    FUN_214c_0693(local_c,unaff_SS);
    FUN_214c_0720(0x9f3a,0x214c);
    FUN_214c_06ad(4,local_c,unaff_SS,puVar6,uVar2);
    puVar6 = local_6d;
    uVar1 = unaff_SS;
    FUN_214c_0885(0x20,local_2c,unaff_SS);
    puVar5 = local_4d;
    uVar2 = unaff_SS;
    FUN_214c_08af(puVar5);
    FUN_214c_08be(CONCAT11(extraout_AH_00,0x68));
    FUN_214c_0954(puVar5,uVar2);
    FUN_214c_0913(0x20,local_2c,unaff_SS,puVar6,uVar1);
  }
  if (*(int *)0xb932 != 0 || *(int *)0xb934 != 0) {
    puVar6 = local_12d;
    uVar2 = unaff_SS;
    FUN_214c_0693(local_c,unaff_SS);
    FUN_214c_0720(0x9f3c,0x214c);
    FUN_214c_06ad(4,local_c,unaff_SS,puVar6,uVar2);
    puVar6 = local_6d;
    uVar1 = unaff_SS;
    FUN_214c_0885(0x20,local_2c,unaff_SS);
    puVar5 = local_4d;
    uVar2 = unaff_SS;
    FUN_214c_08af(puVar5);
    FUN_214c_08be(CONCAT11(extraout_AH_01,99));
    FUN_214c_0954(puVar5,uVar2);
    FUN_214c_0913(0x20,local_2c,unaff_SS,puVar6,uVar1);
  }
  if (*(int *)0xb92e != 0 || *(int *)0xb930 != 0) {
    puVar6 = local_12d;
    uVar2 = unaff_SS;
    FUN_214c_0693(local_c,unaff_SS);
    FUN_214c_0720(0x9f3e,0x214c);
    FUN_214c_06ad(4,local_c,unaff_SS,puVar6,uVar2);
    puVar6 = local_6d;
    uVar1 = unaff_SS;
    FUN_214c_0885(0x20,local_2c,unaff_SS);
    puVar5 = local_4d;
    uVar2 = unaff_SS;
    FUN_214c_08af(puVar5);
    FUN_214c_08be(CONCAT11(extraout_AH_02,0x67));
    FUN_214c_0954(puVar5,uVar2);
    FUN_214c_0913(0x20,local_2c,unaff_SS,puVar6,uVar1);
  }
  uVar4 = local_c[0] == '\0';
  if ((bool)uVar4) {
    FUN_1000_016a(0x46);
  }
  else {
    local_7 = ' ';
    uVar1 = 0x61;
    puVar6 = local_4d;
    uVar2 = unaff_SS;
    FUN_214c_0885(0x20,local_2c,unaff_SS);
    FUN_214c_0933(puVar6,uVar2,uVar1);
    if ((bool)uVar4) {
      uVar1 = CONCAT11(extraout_AH_03,0x68);
      puVar6 = local_6d;
      uVar2 = unaff_SS;
      FUN_214c_0885(0x20,local_2c,unaff_SS);
      FUN_214c_0933(puVar6,uVar2,uVar1);
      if ((bool)uVar4) {
        uVar1 = CONCAT11(extraout_AH_04,99);
        puVar6 = local_8d;
        uVar2 = unaff_SS;
        FUN_214c_0885(0x20,local_2c,unaff_SS);
        FUN_214c_0933(puVar6,uVar2,uVar1);
        uVar3 = extraout_AH_05;
        if ((bool)uVar4) {
          local_7 = 'g';
        }
        else {
          local_7 = 'c';
        }
      }
      else {
        uVar1 = CONCAT11(extraout_AH_04,99);
        puVar6 = local_8d;
        uVar2 = unaff_SS;
        FUN_214c_0885(0x20,local_2c,unaff_SS);
        FUN_214c_0933(puVar6,uVar2,uVar1);
        uVar3 = extraout_AH_06;
        if ((bool)uVar4) {
          uVar1 = CONCAT11(extraout_AH_06,0x67);
          puVar6 = local_ad;
          uVar2 = unaff_SS;
          FUN_214c_0885(0x20,local_2c,unaff_SS);
          FUN_214c_0933(puVar6,uVar2,uVar1);
          uVar3 = extraout_AH_07;
          if ((bool)uVar4) {
            local_7 = 'h';
          }
        }
      }
    }
    else {
      uVar1 = CONCAT11(extraout_AH_03,0x68);
      puVar6 = local_6d;
      uVar2 = unaff_SS;
      FUN_214c_0885(0x20,local_2c,unaff_SS);
      FUN_214c_0933(puVar6,uVar2,uVar1);
      uVar3 = extraout_AH_08;
      if ((bool)uVar4) {
        uVar1 = CONCAT11(extraout_AH_08,99);
        puVar6 = local_8d;
        uVar2 = unaff_SS;
        FUN_214c_0885(0x20,local_2c,unaff_SS);
        FUN_214c_0933(puVar6,uVar2,uVar1);
        uVar3 = extraout_AH_09;
        if ((bool)uVar4) {
          uVar1 = CONCAT11(extraout_AH_09,0x67);
          puVar6 = local_ad;
          uVar2 = unaff_SS;
          FUN_214c_0885(0x20,local_2c,unaff_SS);
          FUN_214c_0933(puVar6,uVar2,uVar1);
          uVar3 = extraout_AH_10;
          if ((bool)uVar4) {
            local_7 = 'a';
          }
        }
      }
    }
    uVar1 = CONCAT11(uVar3,local_7);
    puVar6 = local_4d;
    uVar2 = unaff_SS;
    FUN_214c_08af(puVar6);
    FUN_214c_08be(CONCAT11(extraout_AH_11,0x61));
    FUN_214c_08be(CONCAT11(extraout_AH_12,99));
    FUN_214c_08be(CONCAT11(extraout_AH_13,0x68));
    FUN_214c_08be(CONCAT11(extraout_AH_14,0x67));
    FUN_214c_0933(puVar6,uVar2,uVar1);
    uVar3 = extraout_AH_15;
    if ((bool)uVar4) {
      do {
        FUN_1000_016a(0x57);
        uVar1 = FUN_20e6_0357();
        local_7 = (char)uVar1;
        puVar6 = local_6d;
        uVar2 = unaff_SS;
        FUN_214c_08af(puVar6);
        FUN_214c_08be(CONCAT11(extraout_AH_16,0x61));
        FUN_214c_08be(CONCAT11(extraout_AH_17,99));
        FUN_214c_08be(CONCAT11(extraout_AH_18,0x68));
        FUN_214c_08be(CONCAT11(extraout_AH_19,0x67));
        FUN_214c_0933(puVar6,uVar2,uVar1);
        uVar3 = extraout_AH_20;
        if ((bool)uVar4) {
          uVar1 = 0xe654;
          uVar4 = 1;
          uVar2 = unaff_DS;
          FUN_214c_1799(0,CONCAT11(extraout_AH_20,7));
          FUN_214c_1755(uVar1,uVar2);
          FUN_20e6_0260(CONCAT11(extraout_AH_21,1),CONCAT11(extraout_AH_21,1));
          uVar3 = extraout_AH_22;
        }
        uVar1 = CONCAT11(uVar3,local_7);
        puVar6 = local_6d;
        uVar2 = unaff_SS;
        FUN_214c_08af(puVar6);
        FUN_214c_08be(CONCAT11(extraout_AH_23,0x61));
        FUN_214c_08be(CONCAT11(extraout_AH_24,99));
        FUN_214c_08be(CONCAT11(extraout_AH_25,0x68));
        FUN_214c_08be(CONCAT11(extraout_AH_26,0x67));
        FUN_214c_0933(puVar6,uVar2,uVar1);
        uVar3 = extraout_AH_27;
      } while ((bool)uVar4);
    }
    if (local_7 == 'a') {
      if (*(int *)0xb926 == 0 && *(int *)0xb928 == 0) {
        FUN_1000_016a(0xff35);
        uVar3 = extraout_AH_28;
      }
      else {
        local_6 = *(undefined4 *)0xb926;
        if (*(char *)((int)local_6 + 0x14) == '\0') {
          *(undefined2 *)0xb926 = 0;
          *(undefined2 *)0xb928 = 0;
          uVar3 = 0;
          *(undefined2 *)0xb87c = 0;
        }
        else {
          FUN_1000_016a(0x147);
          uVar3 = extraout_AH_29;
        }
        local_2d = '\x01';
      }
    }
    if (local_7 == 'h') {
      if (*(int *)0xb92a == 0 && *(int *)0xb92c == 0) {
        FUN_1000_016a(0xff35);
        uVar3 = extraout_AH_30;
      }
      else {
        local_6 = *(undefined4 *)0xb92a;
        if (*(char *)((int)local_6 + 0x14) == '\0') {
          *(undefined2 *)0xb92a = 0;
          *(undefined2 *)0xb92c = 0;
          uVar3 = 0;
          *(undefined2 *)0xb87e = 0;
        }
        else {
          FUN_1000_016a(0x58);
          uVar3 = extraout_AH_31;
        }
        local_2d = '\x01';
      }
    }
    if (local_7 == 'c') {
      if (*(int *)0xb932 == 0 && *(int *)0xb934 == 0) {
        FUN_1000_016a(0xff35);
        uVar3 = extraout_AH_32;
      }
      else {
        local_6 = *(undefined4 *)0xb932;
        if (*(char *)((int)local_6 + 0x14) == '\0') {
          *(undefined2 *)0xb932 = 0;
          *(undefined2 *)0xb934 = 0;
          uVar3 = 0;
          *(undefined2 *)0xb884 = 0;
        }
        else {
          FUN_1000_016a(0x147);
          uVar3 = extraout_AH_33;
        }
        local_2d = '\x01';
      }
    }
    uVar4 = local_7 == 'g';
    if ((bool)uVar4) {
      uVar4 = *(int *)0xb92e == 0 && *(int *)0xb930 == 0;
      if (*(int *)0xb92e == 0 && *(int *)0xb930 == 0) {
        FUN_1000_016a(0xff35);
        uVar3 = extraout_AH_34;
      }
      else {
        local_6 = *(undefined4 *)0xb92e;
        uVar4 = *(char *)((int)local_6 + 0x14) == '\0';
        if ((bool)uVar4) {
          uVar3 = 0;
          uVar4 = 1;
          *(undefined2 *)0xb92e = 0;
          *(undefined2 *)0xb930 = 0;
        }
        else {
          FUN_1000_016a(0x4f);
          uVar3 = extraout_AH_35;
        }
        local_2d = '\x01';
      }
    }
    uVar2 = CONCAT11(uVar3,local_7);
    puVar6 = local_4d;
    FUN_214c_08af(puVar6);
    FUN_214c_08be(CONCAT11(extraout_AH_36,0x61));
    FUN_214c_08be(CONCAT11(extraout_AH_37,99));
    FUN_214c_08be(CONCAT11(extraout_AH_38,0x68));
    FUN_214c_08be(CONCAT11(extraout_AH_39,0x67));
    FUN_214c_0933(puVar6,unaff_SS,uVar2);
    if (((!(bool)uVar4) && (*(char *)((int)local_6 + 0x14) == '\0')) && (local_2d != '\0')) {
      FUN_1000_016a(0xb8);
      FUN_1000_557c((uint)extraout_AH_40 << 8,CONCAT11(extraout_AH_40,1),(undefined2)local_6,
                    local_6._2_2_);
      FUN_1000_00b3();
    }
  }
  *(int *)0xb880 = *(int *)0xb87c + *(int *)0xb87e;
  FUN_1000_0296();
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
  
  FUN_1000_0040();
  uVar4 = 0;
  if (*(int *)0xb8cc == 0 && *(int *)0xb8ce == 0) {
    FUN_1000_016a(0x19);
    return;
  }
  FUN_214c_1178();
  FUN_214c_0cc5();
  if ((bool)uVar4) {
    uVar4 = 0;
    uVar5 = *(int *)0xb898 == 0 && *(int *)0xb89a == 0;
    if (*(int *)0xb898 != 0 || *(int *)0xb89a != 0) {
      FUN_214c_1178();
      FUN_214c_0cc5();
      if ((bool)uVar4 || (bool)uVar5) goto LAB_1000_a4bd;
    }
    FUN_1000_016a(0xc5);
    *(int *)0xb874 = *(int *)0xb874 + -1;
    FUN_1000_0296();
  }
  else {
LAB_1000_a4bd:
    iVar2 = FUN_214c_1162(4);
    *(int *)((int)*(undefined4 *)0xb91e + 9) = iVar2 * 100 + 800;
    *(int *)0xb892 = *(int *)0xb892 + *(int *)((int)*(undefined4 *)0xb91e + 9);
    FUN_1000_016a(*(int *)((int)*(undefined4 *)0xb91e + 9) / 100 + 0x30);
  }
  uVar1 = *(undefined4 *)0xb91e;
  bVar3 = (byte)((ulong)uVar1 >> 8);
  FUN_1000_15d3(CONCAT11(bVar3,1),(uint)bVar3 << 8,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
  return;
}



void FUN_1000_a518(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 in_BX;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 uVar7;
  
  uVar4 = (undefined2)param_1;
  uVar5 = (undefined2)((ulong)param_1 >> 0x10);
  if (*(int *)0xb874 == 0) {
    FUN_1000_7364(uVar4,uVar5,0x65);
  }
  cVar1 = FUN_1000_06d5(3);
  if (((cVar1 == '\0') || (iVar2 = FUN_214c_1162(4), iVar2 != 0)) ||
     (*(int *)0xb8a8 != 0 || *(int *)0xb8aa != 0)) {
    if (*(int *)0xb8a8 == 0 && *(int *)0xb8aa == 0) {
      *(int *)0xb892 = *(int *)0xb892 + -1;
    }
    else {
      *(int *)0xb892 = (*(int *)0xb892 / 2) * 2 + -2;
    }
    if (*(int *)0xb892 < -200) {
      FUN_1000_7364(uVar4,uVar5,0x66);
    }
    else {
      if (*(int *)0xb892 < 0) {
        iVar2 = *(int *)0xb892 >> 0xf;
        FUN_214c_0cc9();
        FUN_214c_0cbb();
        uVar6 = 0;
        uVar7 = 1;
        uVar3 = FUN_214c_0ca3();
        FUN_214c_1178(uVar3,in_BX,iVar2);
        FUN_214c_0cc5();
        if (!(bool)uVar6 && !(bool)uVar7) {
          FUN_1000_016a(0xff55);
          *(undefined1 *)0xb915 = 1;
          *(undefined2 *)0xb91a = 1;
          goto LAB_1000_a64e;
        }
      }
      if (*(int *)0xb892 < 0x32) {
        if (*(int *)0xb892 % 0x19 == 0) {
          *(int *)0xb874 = *(int *)0xb874 + -1;
        }
        if (*(int *)0xb874 == 0) {
          FUN_1000_7364(uVar4,uVar5,0x65);
        }
        else {
          FUN_1000_0296();
        }
      }
      else if (*(int *)0xb892 == 0x32) {
        FUN_1000_016a(0xffb0);
        *(int *)0xb874 = *(int *)0xb874 + -1;
        if (*(int *)0xb874 == 0) {
          FUN_1000_7364(uVar4,uVar5,0x65);
        }
        else {
          FUN_1000_0296();
        }
      }
      else if (*(int *)0xb892 == 100) {
        FUN_1000_016a(0xffaf);
      }
    }
  }
LAB_1000_a64e:
  if (*(int *)0xb89c != 0 || *(int *)0xb89e != 0) {
    *(int *)0xb909 = *(int *)0xb909 / 2 << 1;
  }
  if (*(int *)0xb909 == 400) {
    FUN_1000_016a(0xff3d);
  }
  else if (*(int *)0xb909 == 100) {
    FUN_1000_016a(0xff3c);
  }
  return;
}



void FUN_1000_a68a(undefined4 param_1)

{
  bool bVar1;
  int iVar2;
  byte extraout_AH;
  int iVar3;
  undefined2 unaff_DS;
  undefined2 local_5;
  
  bVar1 = false;
  iVar2 = (int)param_1;
  iVar3 = (int)((ulong)param_1 >> 0x10);
  if (0 < *(int *)0xb936) {
    local_5 = 1;
    do {
      if (bVar1) {
LAB_1000_a6cc:
        bVar1 = true;
      }
      else {
        if ((iVar3 == *(int *)(local_5 * 4 + -0x46ca)) && (iVar2 == *(int *)(local_5 * 4 + -0x46cc))
           ) goto LAB_1000_a6cc;
        bVar1 = false;
      }
      if (local_5 == *(int *)0xb936) break;
      local_5 = local_5 + 1;
    } while( true );
  }
  if (bVar1) {
    FUN_1000_016a(0x1f);
  }
  else {
    local_5 = 0;
    do {
      local_5 = local_5 + 1;
    } while (*(int *)(local_5 * 4 + -0x46cc) != 0 || *(int *)(local_5 * 4 + -0x46ca) != 0);
    *(int *)(local_5 * 4 + -0x46cc) = iVar2;
    *(int *)(local_5 * 4 + -0x46ca) = iVar3;
    FUN_1000_016a(0x9c);
    FUN_1000_557c((uint)extraout_AH << 8,CONCAT11(extraout_AH,1),iVar2,iVar3);
    FUN_1000_00b3();
    if (*(int *)(iVar2 + 1) == 0xc) {
      FUN_1000_1448();
      FUN_1000_8d6d(local_5);
    }
  }
  return;
}



void __cdecl16near FUN_1000_a74b(void)

{
  undefined4 uVar1;
  char cVar2;
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
  undefined4 local_6;
  
  FUN_1000_0040();
  cVar2 = FUN_1000_06d5(0);
  if (cVar2 == '\0') {
    FUN_1000_016a(0x1d);
  }
  else {
    do {
      FUN_1000_0040();
      FUN_1000_016a(0x9d);
      uVar3 = FUN_20e6_0357();
      local_7 = (undefined1)uVar3;
      puVar6 = local_2b;
      uVar4 = unaff_SS;
      FUN_214c_08af(puVar6);
      uVar5 = *(int *)0xb936 + 0x30 == 0;
      FUN_214c_08df(*(int *)0xb936 + 0x30,CONCAT11(extraout_AH,0x31));
      FUN_214c_0933(puVar6,uVar4,uVar3);
    } while ((bool)uVar5);
    local_6 = 0;
    FUN_1000_0040();
    puVar6 = local_10b;
    uVar4 = unaff_SS;
    FUN_214c_07ae(CONCAT11(extraout_AH_00,local_7));
    local_b = FUN_214c_1352(local_9,unaff_SS,puVar6,uVar4);
    uVar1 = *(undefined4 *)(local_b * 4 + -0x46cc);
    local_6._2_2_ = (int)((ulong)uVar1 >> 0x10);
    local_6._0_2_ = (int)uVar1;
    if ((int)local_6 == 0 && local_6._2_2_ == 0) {
      FUN_1000_016a(0x1c);
    }
    else if (*(char *)((int)local_6 + 0x14) == '\0') {
      uVar5 = 1;
      *(undefined2 *)(local_b * 4 + -0x46cc) = 0;
      *(undefined2 *)(local_b * 4 + -0x46ca) = 0;
      FUN_1000_016a(0x1a5);
      FUN_1000_557c((uint)extraout_AH_01 << 8,CONCAT11(extraout_AH_01,1),(int)local_6,local_6._2_2_)
      ;
      uVar4 = CONCAT11(extraout_AH_02,*(undefined1 *)((int)local_6 + 1));
      puVar6 = local_2b;
      FUN_214c_08af(puVar6);
      FUN_214c_08be(CONCAT11(extraout_AH_03,5));
      FUN_214c_08be(CONCAT11(extraout_AH_04,0x13));
      FUN_214c_0933(puVar6,unaff_SS,uVar4);
      if (!(bool)uVar5) {
        *(undefined1 *)((int)local_6 + 0x14) = 1;
      }
      FUN_1000_00b3();
    }
    else {
      FUN_1000_016a(0x4e);
    }
  }
  return;
}



void FUN_1000_a85c(int *param_1,int *param_2)

{
  char cVar1;
  
  FUN_1000_0040();
  FUN_1000_016a(0x9f);
  do {
    *param_2 = 0;
    *param_1 = 0;
    cVar1 = FUN_20e6_0357();
    if (cVar1 == '4') {
      *param_1 = -1;
    }
    else if (cVar1 == '6') {
      *param_1 = 1;
    }
    else if (cVar1 == '2') {
      *param_2 = 1;
    }
    else if (cVar1 == '8') {
      *param_2 = -1;
    }
    else if (cVar1 == '\0') {
      cVar1 = FUN_20e6_0357();
      if (cVar1 == 'K') {
        *param_1 = -1;
      }
      else if (cVar1 == 'M') {
        *param_1 = 1;
      }
      else if (cVar1 == 'P') {
        *param_2 = 1;
      }
      else if (cVar1 == 'H') {
        *param_2 = -1;
      }
    }
  } while ((*param_2 == 0) && (*param_1 == 0));
  return;
}



void FUN_1000_a91f(int *param_1,int *param_2,int *param_3,int *param_4,int *param_5)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined1 local_24 [32];
  int local_4;
  
  *param_5 = *(int *)0xb86c;
  *param_4 = *(int *)0xb86e;
  local_4 = 0;
  while( true ) {
    *param_5 = *param_5 + *param_3;
    *param_4 = *param_4 + *param_2;
    local_4 = local_4 + 1;
    if (local_4 == *param_1) break;
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    iVar3 = (int)uVar1 + *param_5 * 0x4f + *param_4;
    uVar4 = iVar3 == 0;
    uVar2 = CONCAT11((char)((uint)(*param_5 * 0x4f) >> 8),*(undefined1 *)(iVar3 + -0x50));
    puVar5 = local_24;
    uVar6 = unaff_SS;
    FUN_214c_0885(0x20,0xb76f,unaff_DS);
    FUN_214c_0933(puVar5,uVar6,uVar2);
    if ((!(bool)uVar4) || (*(char *)(*param_5 * 0x4f + *param_4 + -0xc) != ' ')) break;
  }
  if (*(char *)(*param_5 * 0x4f + *param_4 + -0xc) == ' ') {
    *param_5 = *param_5 - *param_3;
    *param_4 = *param_4 - *param_2;
  }
  return;
}



void FUN_1000_aa1d(undefined4 param_1)

{
  int iVar1;
  int iVar2;
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
  if (*(char *)(local_8 * 0x4f + local_6 + -0xc) != ' ') {
    FUN_1000_00de(&local_c,unaff_SS,local_6,local_8);
    uVar6 = (undefined2)((ulong)local_c >> 0x10);
    puVar4 = (undefined1 *)local_c;
    *(int *)(puVar4 + 0x2c) = *(int *)(puVar4 + 0x2c) + 1;
    iVar1 = *(int *)(iVar3 + 1);
    uVar7 = iVar1 == 1;
    if (((bool)uVar7) || (uVar7 = iVar1 == 0x10, (bool)uVar7)) {
      uVar6 = CONCAT11((char)((uint)iVar1 >> 8),*local_c);
      puVar4 = local_2c;
      FUN_214c_0885(0x20,0xb82f,unaff_DS);
      FUN_214c_0933(puVar4,unaff_SS,uVar6);
      if ((bool)uVar7) {
        uVar6 = (undefined2)((ulong)local_c >> 0x10);
        FUN_1000_2363(0xe52d,unaff_DS,(undefined1 *)local_c + 0x1e,uVar6,
                      (undefined1 *)local_c + 0x1c,uVar6);
        *(undefined1 *)(local_8 * 0x4f + local_6 + -0xc) = 0x20;
        FUN_1000_0428(CONCAT11((char)((uint)(local_8 * 0x4f) >> 8),0x20),local_6,local_8);
        uVar6 = (undefined2)((ulong)local_c >> 0x10);
        puVar4 = (undefined1 *)local_c;
        *(undefined1 *)(*(int *)(puVar4 + 0x1c) * 0x4f + *(int *)(puVar4 + 0x1e) + -0xc) = puVar4[1]
        ;
        if (*(char *)0xb919 != '\0') {
          *(undefined1 *)0xb919 = 0;
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
          local_4 = FUN_214c_1162(0x23);
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
        *(undefined1 *)0xb919 = 0;
        iVar3 = *(int *)(puVar4 + 0x1c);
        *(undefined1 *)(iVar3 * 0x4f + *(int *)(puVar4 + 0x1e) + -0xc) = puVar4[1];
        FUN_1000_0428(CONCAT11((char)((uint)(iVar3 * 0x4f) >> 8),puVar4[1]),
                      *(undefined2 *)(puVar4 + 0x1e),*(undefined2 *)(puVar4 + 0x1c));
      }
    }
    else if (iVar1 == 5) {
      if (puVar4[0x24] == '\0') {
        puVar4[0x25] = 1;
        if (puVar4[0x29] == '\0') {
          iVar3 = FUN_214c_1162(10);
          *(int *)((undefined1 *)local_c + 0x20) = iVar3 + 10;
        }
        else {
          iVar3 = FUN_214c_1162(5);
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
        iVar3 = FUN_214c_1162(10);
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
        FUN_214c_0cc9();
        FUN_214c_0cb5();
        iVar3 = FUN_214c_0ccd();
        *(int *)((undefined1 *)local_c + 10) = iVar3 + 1;
      }
      *(int *)0xb870 = *(int *)0xb870 / 2 + 1;
      FUN_1000_0296();
    }
    else if (iVar1 == 8) {
      if (puVar4[0x29] == '\0') {
        puVar4[0x22] = 1;
      }
    }
    else if (iVar1 == 0xc) {
      if (puVar4[0x29] == '\0') {
        iVar3 = FUN_214c_1162(*(int *)0xb888 + *(int *)0xe52d);
        uVar5 = (undefined2)((ulong)local_c >> 0x10);
        iVar3 = (*(int *)((undefined1 *)local_c + 10) + -10) - iVar3;
        *(int *)((undefined1 *)local_c + 10) = iVar3;
      }
      else {
        iVar3 = FUN_214c_1162(0xb);
        uVar5 = (undefined2)((ulong)local_c >> 0x10);
        iVar3 = *(int *)((undefined1 *)local_c + 10) - iVar3;
        *(int *)((undefined1 *)local_c + 10) = iVar3;
      }
      uVar5 = (undefined2)((ulong)local_c >> 0x10);
      if (*(int *)((undefined1 *)local_c + 10) < 0) {
        FUN_1000_79ea(CONCAT11((char)((uint)iVar3 >> 8),1),(undefined1 *)local_c,uVar5);
      }
    }
    else if (iVar1 == 0xe) {
      if (puVar4[0x29] == '\0') {
        puVar4[0x28] = 1;
      }
    }
    else if (iVar1 == 0xf) {
      if (puVar4[0x29] == '\0') {
        iVar3 = FUN_214c_1162(7);
        *(int *)((undefined1 *)local_c + 0x2a) = iVar3 + 10;
      }
      else {
        iVar3 = FUN_214c_1162(3);
        *(int *)((undefined1 *)local_c + 0x2a) = iVar3 + 2;
      }
    }
    else if (iVar1 == 0x12) {
      *(int *)(puVar4 + 10) = *(int *)0xb870 / 2 + *(int *)(puVar4 + 10) + 1;
      *(int *)0xb870 = *(int *)0xb870 / 2 + 1;
      FUN_1000_0296();
    }
    else if (iVar1 == 0x13) {
      iVar3 = FUN_214c_1162(2);
      puVar4 = (undefined1 *)local_c;
      uVar5 = (undefined2)((ulong)local_c >> 0x10);
      if (iVar3 == 1) {
        if (puVar4[0x29] == '\0') {
          *(undefined2 *)(puVar4 + 10) = 1;
          iVar3 = FUN_214c_1162(*(undefined2 *)0xb872);
          *(int *)0xb870 = iVar3 + 1;
        }
      }
      else {
        *(undefined2 *)(puVar4 + 10) = *(undefined2 *)(*(int *)(puVar4 + 4) * 0x2a + -0x5002);
        *(undefined2 *)0xb870 = 1;
      }
      FUN_1000_0296();
    }
    else if (iVar1 == 0x14) {
      do {
        local_4 = FUN_214c_1162(0x23);
        local_4 = local_4 + 1;
      } while (*(char *)(local_4 * 0x2a + -0x4fee) != '\0');
      uVar5 = (undefined2)((ulong)local_c >> 0x10);
      *(int *)((undefined1 *)local_c + 4) = local_4;
      ((undefined1 *)local_c)[1] = *(undefined1 *)(local_4 * 0x2a + -0x5007);
    }
    else if (iVar1 == 0x16) {
      if (puVar4[0x29] == '\0') {
        local_4 = FUN_214c_1162(3);
        local_4 = local_4 + 1;
      }
      else {
        local_4 = 1;
      }
      uVar6 = (undefined2)((ulong)local_c >> 0x10);
      *(int *)((undefined1 *)local_c + 8) = *(int *)((undefined1 *)local_c + 8) - local_4;
      FUN_214c_1162(10);
      iVar2 = FUN_214c_02dc();
      uVar6 = (undefined2)((ulong)local_c >> 0x10);
      puVar4 = (undefined1 *)local_c;
      iVar1 = *(int *)(puVar4 + 10);
      *(int *)(puVar4 + 10) = iVar1 - iVar2;
      if ((*(int *)(puVar4 + 8) < 1) || (*(int *)(puVar4 + 10) < 0)) {
        FUN_1000_79ea(CONCAT11((char)((uint)(iVar1 - iVar2) >> 8),1),puVar4,uVar6);
      }
      if (((undefined1 *)local_c)[0x29] != '\0') {
        *(undefined2 *)(iVar3 + 9) = 1;
      }
      FUN_214c_1162(10);
      iVar3 = FUN_214c_02dc();
      *(int *)0xb870 = *(int *)0xb870 + iVar3;
      if (*(int *)0xb872 < *(int *)0xb870) {
        *(undefined2 *)0xb870 = *(undefined2 *)0xb872;
      }
      FUN_1000_0296();
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
  int iVar4;
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
  iVar4 = (int)param_1;
  if (*(int *)(iVar4 + 9) == 0) {
    FUN_1000_0040();
    FUN_1000_016a(0x15);
  }
  else {
    iVar3 = *(int *)(iVar4 + 1);
    if (iVar3 == 3) {
      iVar3 = (*(int *)0xb86c + local_6) * 0x4f;
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar5 = (int)uVar1 + iVar3 + *(int *)0xb86e + local_4;
      uVar8 = iVar5 == 0;
      uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar10 = local_30;
      uVar11 = unaff_SS;
      FUN_214c_0885(0x20,0xb76f,unaff_DS);
      puVar9 = local_50;
      uVar7 = unaff_SS;
      FUN_214c_0885(0x20,0xb7cf,unaff_DS);
      FUN_214c_0954(puVar9,uVar7);
      FUN_214c_0933(puVar10,uVar11,uVar2);
      if ((!(bool)uVar8) &&
         ((!(bool)((char)*(undefined2 *)0xb86c + (char)local_6 & 1) ||
          (!(bool)((char)*(undefined2 *)0xb86e + (char)local_4 & 1))))) {
        iVar3 = (*(int *)0xb86c + local_6) * 0x4f;
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        iVar5 = (int)uVar1 + iVar3 + *(int *)0xb86e + local_4;
        uVar8 = iVar5 == 0;
        uVar7 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
        puVar10 = local_70;
        FUN_214c_0885(0x20,0xb76f,unaff_DS);
        FUN_214c_0933(puVar10,unaff_SS,uVar7);
        if ((bool)uVar8) {
          FUN_1000_2214(*(int *)0xb86e + local_4,*(int *)0xb86c + local_6);
        }
        else {
          FUN_1000_2138(*(int *)0xb86e + local_4,*(int *)0xb86c + local_6);
        }
        FUN_1000_11fc(*(int *)0xb86c + 1);
      }
    }
    else if (iVar3 == 4) {
      iVar3 = (*(int *)0xb86c + local_6) * 0x4f;
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar5 = (int)uVar1 + iVar3 + *(int *)0xb86e + local_4;
      uVar8 = iVar5 == 0;
      uVar11 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar10 = local_30;
      uVar7 = unaff_SS;
      FUN_214c_08af(puVar10);
      FUN_214c_08be(CONCAT11(extraout_AH,0xef));
      FUN_214c_0933(puVar10,uVar7,uVar11);
      if ((bool)uVar8) {
        iVar3 = (*(int *)0xb86c + local_6) * 0x4f;
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        iVar5 = (int)uVar1 + iVar3 + *(int *)0xb86e + local_4;
        uVar8 = iVar5 == 0;
        uVar11 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
        puVar10 = local_50;
        uVar7 = unaff_SS;
        FUN_214c_0885(0x20,0xb7cf,unaff_DS);
        FUN_214c_0933(puVar10,uVar7,uVar11);
        if (!(bool)uVar8) {
          FUN_1000_2214(*(int *)0xb86e + local_4,*(int *)0xb86c + local_6);
        }
        FUN_1000_21b0(*(int *)0xb86e + local_4,*(int *)0xb86c + local_6);
        if (*(char *)((*(int *)0xb86c + local_6) * 0x4f + *(int *)0xb86e + local_4 + -0xc) != ' ') {
          iVar3 = (*(int *)0xb86c + local_6) * 0x4f;
          uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
          iVar5 = (int)uVar1 + iVar3 + *(int *)0xb86e + local_4;
          uVar8 = iVar5 == 0;
          uVar11 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
          puVar10 = local_50;
          uVar7 = unaff_SS;
          FUN_214c_0885(0x20,0xb76f,unaff_DS);
          FUN_214c_0933(puVar10,uVar7,uVar11);
          if (!(bool)uVar8) {
            FUN_1000_00de(local_a,unaff_SS,*(int *)0xb86e + local_4,*(int *)0xb86c + local_6);
            if (*(char *)(local_a._0_2_ + 0x29) == '\0') {
              FUN_1000_79ea((uint)extraout_AH_00 << 8,local_a._0_2_,local_a._2_2_);
            }
          }
        }
        FUN_1000_11fc(*(int *)0xb86c + 1);
      }
    }
    else if (iVar3 == 9) {
      iVar3 = (*(int *)0xb86c + local_6) * 0x4f;
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar5 = (int)uVar1 + iVar3 + *(int *)0xb86e + local_4;
      uVar8 = iVar5 == 0;
      uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar10 = local_50;
      uVar11 = unaff_SS;
      FUN_214c_0885(0x20,0xb76f,unaff_DS);
      puVar9 = local_30;
      uVar7 = unaff_SS;
      FUN_214c_08af(puVar9);
      FUN_214c_08be(CONCAT11(extraout_AH_01,0xef));
      FUN_214c_0954(puVar9,uVar7);
      FUN_214c_0933(puVar10,uVar11,uVar2);
      if ((bool)uVar8) {
        iVar3 = (*(int *)0xb86c + local_6) * 0x4f;
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        iVar5 = (int)uVar1 + iVar3 + *(int *)0xb86e + local_4;
        uVar8 = iVar5 == 0;
        uVar7 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
        puVar10 = local_70;
        FUN_214c_0885(0x20,0xb7cf,unaff_DS);
        FUN_214c_0933(puVar10,unaff_SS,uVar7);
        if (!(bool)uVar8) {
          FUN_1000_2214(*(int *)0xb86e + local_4,*(int *)0xb86c + local_6);
        }
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        *(undefined1 *)
         ((int)uVar1 + (*(int *)0xb86c + local_6) * 0x4f + *(int *)0xb86e + local_4 + -0x50) = 0xf7;
        FUN_1000_0e28();
      }
    }
    else if (iVar3 == 10) {
      if (*(char *)((*(int *)0xb86c + local_6) * 0x4f + *(int *)0xb86e + local_4 + -0xc) == ' ') {
        iVar3 = (*(int *)0xb86c + local_6) * 0x4f;
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        iVar5 = (int)uVar1 + iVar3 + *(int *)0xb86e + local_4;
        uVar8 = iVar5 == 0;
        uVar7 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
        puVar10 = local_30;
        FUN_214c_0885(0x20,0xb76f,unaff_DS);
        FUN_214c_0933(puVar10,unaff_SS,uVar7);
        if (((bool)uVar8) &&
           (FUN_1000_3544(),
           *(int *)(*(int *)0xe52d * 4 + -0x5499) != 0 ||
           *(int *)(*(int *)0xe52d * 4 + -0x5497) != 0)) {
          local_34 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
          uVar7 = (undefined2)((ulong)local_34 >> 0x10);
          iVar3 = (int)local_34;
          *(undefined1 *)(*(int *)(iVar3 + 0x1c) * 0x4f + *(int *)(iVar3 + 0x1e) + -0xc) = 0x20;
          *(int *)(iVar3 + 0x1c) = *(int *)0xb86c + local_6;
          *(int *)(iVar3 + 0x1e) = *(int *)0xb86e + local_4;
          *(undefined1 *)(*(int *)(iVar3 + 0x1c) * 0x4f + *(int *)(iVar3 + 0x1e) + -0xc) =
               *(undefined1 *)(iVar3 + 1);
          FUN_1000_0e28();
        }
      }
    }
    else if (iVar3 == 0xb) {
      iVar3 = (*(int *)0xb86c + local_6) * 0x4f;
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar5 = (int)uVar1 + iVar3 + *(int *)0xb86e + local_4;
      uVar8 = iVar5 == 0;
      uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar10 = local_50;
      uVar11 = unaff_SS;
      FUN_214c_0885(0x20,0xb76f,unaff_DS);
      puVar9 = local_30;
      uVar7 = unaff_SS;
      FUN_214c_08af(puVar9);
      FUN_214c_08be(CONCAT11(extraout_AH_02,0xef));
      FUN_214c_08be(CONCAT11(extraout_AH_03,0xf7));
      FUN_214c_0954(puVar9,uVar7);
      puVar9 = local_70;
      uVar7 = unaff_SS;
      FUN_214c_0885(0x20,0xb7cf,unaff_DS);
      FUN_214c_0954(puVar9,uVar7);
      FUN_214c_0933(puVar10,uVar11,uVar2);
      if ((bool)uVar8) {
        iVar3 = FUN_214c_1162(5);
        FUN_1000_26cf(local_10,unaff_SS,*(undefined2 *)0xe52d,iVar3 + 1);
        FUN_1000_2574(*(undefined2 *)0xe52d,local_10,unaff_SS);
        uVar7 = SUB42(local_10._0_4_,2);
        iVar3 = (int)local_10._0_4_;
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        *(undefined1 *)((int)uVar1 + *(int *)(iVar3 + 5) * 0x4f + *(int *)(iVar3 + 7) + -0x50) =
             0x20;
        *(int *)(iVar3 + 5) = *(int *)0xb86c + local_6;
        *(int *)(iVar3 + 7) = *(int *)0xb86e + local_4;
        uVar8 = FUN_1000_0479(iVar3,uVar7);
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        *(undefined1 *)((int)uVar1 + *(int *)(iVar3 + 5) * 0x4f + *(int *)(iVar3 + 7) + -0x50) =
             uVar8;
        FUN_1000_0e28();
      }
    }
    else if (iVar3 == 0xd) {
      iVar3 = (*(int *)0xb86c + local_6) * 0x4f;
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar5 = (int)uVar1 + iVar3 + *(int *)0xb86e + local_4;
      uVar8 = iVar5 == 0;
      uVar7 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar10 = local_30;
      FUN_214c_08af(puVar10);
      FUN_214c_08be(CONCAT11(extraout_AH_04,*(undefined1 *)0x0));
      FUN_214c_08be(CONCAT11(extraout_AH_05,*(undefined1 *)0x1));
      FUN_214c_08be(CONCAT11(extraout_AH_06,*(undefined1 *)0x2));
      FUN_214c_08be(CONCAT11(extraout_AH_07,*(undefined1 *)0x3));
      FUN_214c_0933(puVar10,unaff_SS,uVar7);
      if (!(bool)uVar8) {
        FUN_20e6_0260(*(int *)0xb86c + local_6 + 1,*(int *)0xb86e + local_4);
        uVar11 = 0xe654;
        uVar7 = unaff_DS;
        FUN_214c_1799(0,CONCAT11(extraout_AH_08,0x20));
        FUN_214c_1755(uVar11,uVar7);
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        *(undefined1 *)
         ((int)uVar1 + (*(int *)0xb86c + local_6) * 0x4f + *(int *)0xb86e + local_4 + -0x50) = 0x20;
      }
    }
    else if (iVar3 == 0x11) {
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      if (*(char *)((int)uVar1 + (*(int *)0xb86c + local_6) * 0x4f + *(int *)0xb86e + local_4 +
                   -0x50) == ' ') {
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        *(undefined1 *)
         ((int)uVar1 + (*(int *)0xb86c + local_6) * 0x4f + *(int *)0xb86e + local_4 + -0x50) =
             *(undefined1 *)0x1;
      }
    }
    else if (iVar3 == 0x15) {
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      if (*(char *)((int)uVar1 + (*(int *)0xb86c + local_6) * 0x4f + *(int *)0xb86e + local_4 +
                   -0x50) == -9) {
        *(undefined1 *)(*(int *)0xe52d + 0x796d) = 0;
      }
    }
    else {
      FUN_1000_aa1d(iVar4,uVar6,local_4,local_6);
    }
    *(int *)(iVar4 + 9) = *(int *)(iVar4 + 9) + -1;
  }
  return;
}



void FUN_1000_b711(int param_1,undefined2 param_2,undefined2 param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 uVar4;
  byte bVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  uVar1 = *(undefined1 *)((int)uVar2 + *(int *)0xb86c * 0x4f + *(int *)0xb86e + -0x50);
  bVar5 = (byte)((uint)(*(int *)0xb86c * 0x4f) >> 8);
  FUN_1000_15d3((uint)bVar5 << 8,CONCAT11(bVar5,1),param_2,param_3);
  uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + -0x54d9);
  uVar6 = (undefined2)((ulong)uVar2 >> 0x10);
  iVar3 = (int)uVar2;
  *(undefined2 *)(iVar3 + 5) = *(undefined2 *)(param_1 + -10);
  *(undefined2 *)(iVar3 + 7) = *(undefined2 *)(param_1 + -8);
  uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  if (*(char *)((int)uVar2 + *(int *)(param_1 + -10) * 0x4f + *(int *)(param_1 + -8) + -0x50) != ' '
     ) {
    FUN_1000_491d(iVar3 + 7,uVar6,iVar3 + 5,uVar6);
  }
  uVar4 = FUN_1000_0479(*(undefined2 *)(*(int *)0xe52d * 4 + -0x54d9),
                        *(undefined2 *)(*(int *)0xe52d * 4 + -0x54d7));
  uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  *(undefined1 *)((int)uVar2 + *(int *)(iVar3 + 5) * 0x4f + *(int *)(iVar3 + 7) + -0x50) = uVar4;
  uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  *(undefined1 *)((int)uVar2 + *(int *)0xb86c * 0x4f + *(int *)0xb86e + -0x50) = uVar1;
  return;
}



void FUN_1000_b821(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  if (((*(int *)((int)*(undefined4 *)(param_1 + 4) + 1) == 0xc) &&
      (*(int *)0xb922 != 0 || *(int *)0xb924 != 0)) &&
     (*(int *)((int)*(undefined4 *)0xb922 + 1) == 0xb)) {
    iVar1 = *(int *)((int)*(undefined4 *)0xb922 + 9);
    iVar2 = *(int *)((int)*(undefined4 *)(param_1 + 4) + 9);
    iVar3 = FUN_214c_1162(7);
    *(int *)((int)*(undefined4 *)(param_1 + -0x13) + 10) =
         (((*(int *)((int)*(undefined4 *)(param_1 + -0x13) + 10) + -6) - iVar3) - iVar2) - iVar1;
  }
  else {
    *(int *)((int)*(undefined4 *)(param_1 + -0x13) + 10) =
         *(int *)((int)*(undefined4 *)(param_1 + -0x13) + 10) -
         *(int *)(*(int *)((int)*(undefined4 *)(param_1 + 4) + 1) * 2 + -0x6123);
  }
  return;
}



void FUN_1000_b8c7(char *param_1)

{
  uint in_AX;
  int iVar1;
  undefined1 extraout_AH;
  undefined2 uVar2;
  byte extraout_AH_00;
  byte extraout_AH_01;
  byte bVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar5;
  undefined1 *puVar6;
  undefined1 local_35 [32];
  undefined1 *local_15;
  char local_11 [3];
  int local_e;
  int local_c;
  int local_a;
  undefined1 local_8 [2];
  undefined1 local_6 [4];
  
  FUN_1000_08bd(in_AX & 0xff00,local_11,unaff_SS,&param_1,unaff_SS);
  if (local_11[0] != '\0') {
    FUN_1000_0040();
    iVar1 = FUN_214c_1162(*(int *)0xb874 / 4 + 1);
    uVar4 = 0;
    local_e = *(int *)0xb874 / 4 + iVar1 + 1;
    FUN_1000_a85c(local_6,unaff_SS,local_8,unaff_SS);
    FUN_1000_a91f(&local_e,unaff_SS,local_6,unaff_SS,local_8,unaff_SS,&local_a,unaff_SS,&local_c,
                  unaff_SS);
    iVar1 = local_a - *(int *)0xb86e;
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    local_e = local_c - *(int *)0xb86c;
    if (local_e < 0) {
      local_e = -local_e;
    }
    local_e = local_e + iVar1;
    if (*(char *)(local_c * 0x4f + local_a + -0xc) == ' ') {
      if ((local_c == *(int *)0xb86c) && (local_a == *(int *)0xb86e)) {
        FUN_1000_016a(0xffad);
      }
      else {
        FUN_1000_b711(&stack0xfffe,(char *)param_1,param_1._2_2_);
      }
    }
    else {
      FUN_1000_00de(&local_15,unaff_SS,local_a,local_c);
      FUN_1000_0094();
      if ((local_e < 2) && (uVar5 = ((undefined1 *)local_15)[0x28] == '\0', (bool)uVar5)) {
        uVar2 = CONCAT11(extraout_AH,*local_15);
        puVar6 = local_35;
        FUN_214c_0885(0x20,0xb80f,unaff_DS);
        FUN_214c_0933(puVar6,unaff_SS,uVar2);
        if ((bool)uVar5) {
          FUN_1000_016a(0xff36);
          return;
        }
      }
      iVar1 = ((*(int *)0xb888 + *(int *)0xb878) - *(int *)((undefined1 *)local_15 + 8)) - local_e
              >> 0xf;
      FUN_214c_0cc9();
      uVar5 = 0;
      FUN_214c_0cbb();
      uVar2 = FUN_214c_0ca3();
      FUN_214c_1178(uVar2,uVar4,iVar1);
      FUN_214c_0cc5();
      puVar6 = (undefined1 *)local_15;
      uVar4 = (undefined2)((ulong)local_15 >> 0x10);
      if ((bool)uVar5) {
        puVar6[0x28] = 0;
        if (*(char *)0xb8ed == '\0') {
          FUN_1000_0510(*(undefined2 *)(puVar6 + 4),0xbd);
          bVar3 = extraout_AH_01;
        }
        else {
          FUN_1000_016a(0xbb);
          bVar3 = extraout_AH_00;
        }
        FUN_1000_15d3((uint)bVar3 << 8,(uint)bVar3 << 8,(char *)param_1,param_1._2_2_);
        if (*param_1 == '\a') {
          FUN_1000_b821(&stack0xfffe);
        }
        else {
          puVar6 = (undefined1 *)local_15;
          uVar4 = (undefined2)((ulong)local_15 >> 0x10);
          if (*param_1 == '\x06') {
            uVar2 = (undefined2)((ulong)param_1 >> 0x10);
            *(int *)(puVar6 + 10) =
                 (*(int *)(puVar6 + 10) - *(int *)((char *)param_1 + 9)) -
                 *(int *)(*(int *)((char *)param_1 + 1) * 4 + -0x61e5);
          }
          else {
            *(int *)(puVar6 + 10) = *(int *)(puVar6 + 10) + -1;
          }
        }
        uVar4 = (undefined2)((ulong)local_15 >> 0x10);
        if (*(int *)((undefined1 *)local_15 + 10) < 1) {
          FUN_1000_79ea(1,(undefined1 *)local_15,uVar4);
        }
      }
      else {
        if (*(char *)0xb8ed == '\0') {
          FUN_1000_0510(*(undefined2 *)(puVar6 + 4),0xbc);
        }
        else {
          FUN_1000_016a(0x98);
        }
        FUN_1000_b711(&stack0xfffe,(char *)param_1,param_1._2_2_);
      }
    }
  }
  return;
}



void FUN_1000_bafc(char *param_1)

{
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  int iVar1;
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
  bool bVar6;
  undefined1 *puVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined1 local_62 [32];
  undefined1 local_42 [32];
  undefined1 local_22 [32];
  
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  pcVar2 = (char *)param_1;
  if (*(char *)(*param_1 * 0x18 + *(int *)(pcVar2 + 1) + -0x65a2) != '\0') {
    return;
  }
  iVar1 = *param_1 * 0x18;
  if (*(char *)(iVar1 + *(int *)(pcVar2 + 1) + -0x6542) != '\0') {
    return;
  }
  uVar4 = *param_1 == '\x03';
  if ((bool)uVar4) {
    uVar8 = CONCAT11((char)((uint)iVar1 >> 8),pcVar2[1]);
    puVar7 = local_22;
    uVar9 = unaff_SS;
    FUN_214c_08af(puVar7);
    FUN_214c_08be(CONCAT11(extraout_AH,0xf));
    FUN_214c_08be(CONCAT11(extraout_AH_00,0x10));
    iVar1 = FUN_214c_0933(puVar7,uVar9,uVar8);
    if (!(bool)uVar4) {
      return;
    }
  }
  uVar4 = (undefined1)((uint)iVar1 >> 8);
  if ((*param_1 == '\x02') && (*(int *)(pcVar2 + 1) == 7)) {
    return;
  }
  uVar5 = *param_1 == '\x02';
  if ((bool)uVar5) {
    uVar8 = CONCAT11(uVar4,pcVar2[1]);
    puVar7 = local_42;
    uVar9 = unaff_SS;
    FUN_214c_08af(puVar7);
    FUN_214c_08be(CONCAT11(extraout_AH_01,0x10));
    FUN_214c_08be(CONCAT11(extraout_AH_02,0x12));
    FUN_214c_0933(puVar7,uVar9,uVar8);
    uVar4 = extraout_AH_03;
    if (!(bool)uVar5) goto LAB_1000_bbc5;
  }
  else {
LAB_1000_bbc5:
    uVar5 = *param_1 == '\x03';
    if (!(bool)uVar5) goto LAB_1000_bc0d;
    uVar9 = CONCAT11(uVar4,pcVar2[1]);
    puVar7 = local_62;
    FUN_214c_08af(puVar7);
    FUN_214c_08df(CONCAT11(extraout_AH_04,3),CONCAT11(extraout_AH_04,1));
    FUN_214c_08be(CONCAT11(extraout_AH_05,5));
    FUN_214c_08be(CONCAT11(extraout_AH_06,0x14));
    FUN_214c_08be(CONCAT11(extraout_AH_07,0x15));
    FUN_214c_0933(puVar7,unaff_SS,uVar9);
    if ((bool)uVar5) goto LAB_1000_bc0d;
  }
  FUN_1000_1448();
LAB_1000_bc0d:
  FUN_1000_0040();
  if (*param_1 == '\x02') {
    FUN_1000_016a(0x74);
    uVar4 = extraout_AH_08;
  }
  else {
    FUN_1000_016a(0x65);
    uVar4 = extraout_AH_09;
  }
  uVar8 = 0xe654;
  uVar9 = unaff_DS;
  FUN_214c_1799(0,CONCAT11(uVar4,0x20));
  FUN_214c_1755(uVar8,uVar9);
  uVar9 = 0xe554;
  FUN_214c_17be(0x1c,*param_1 * 0x2b8 + *(int *)(pcVar2 + 1) * 0x1d + -0x75de,unaff_DS);
  FUN_214c_16ef(0x214c,uVar9);
  iVar1 = *param_1 * 0x2b8 + *(int *)(pcVar2 + 1) * 0x1d + -0x75de;
  bVar6 = iVar1 == 0;
  FUN_214c_0783(0xbafb,0x214c,iVar1,unaff_DS);
  *(bool *)(*param_1 * 0x18 + *(int *)(pcVar2 + 1) + -0x6542) = !bVar6;
  return;
}



void FUN_1000_bcd0(char *param_1)

{
  uint in_AX;
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = (undefined2)((ulong)param_1 >> 0x10);
  if (*param_1 != '\x02') {
    if (*param_1 != '\x03') {
      return;
    }
    in_AX = FUN_214c_1162(*(undefined2 *)(*(int *)((char *)param_1 + 1) * 4 + -0x6305));
    if (in_AX == 0) {
      return;
    }
  }
  FUN_1000_15d3(1,in_AX & 0xff00,(char *)param_1,uVar1);
  return;
}



void FUN_1000_bd12(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_bafc(param_1,param_2);
  FUN_1000_bcd0(param_1,param_2);
  return;
}



void FUN_1000_bd2d(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
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
  int iVar13;
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
  char local_1c;
  undefined4 local_1b;
  char local_17;
  int local_16;
  int local_14;
  undefined4 local_12;
  undefined4 local_e;
  
  uVar5 = FUN_214c_1162(0x15);
  uVar6 = *(int *)0xb888 / 2 + *(int *)0xb87a;
  iVar9 = (int)uVar6 >> 0xf;
  if ((iVar9 < 0) || ((iVar9 < 1 && (uVar6 < uVar5)))) {
    if (*(int *)0xb8a0 != 0 || *(int *)0xb8a2 != 0) {
      uVar5 = FUN_214c_1162(0x19);
      uVar6 = *(int *)0xb888 / 2 + *(int *)0xb87a;
      iVar9 = (int)uVar6 >> 0xf;
      if ((-1 < iVar9) && ((0 < iVar9 || (uVar5 <= uVar6)))) goto LAB_1000_bd9d;
    }
    FUN_1000_016a(0xff34);
    FUN_1000_bcd0((char *)param_2,param_2._2_2_);
  }
  else {
LAB_1000_bd9d:
    iVar9 = *(int *)((char *)param_2 + 1);
    if (iVar9 == 1) {
      if (*(int *)0xb926 == 0 && *(int *)0xb928 == 0) {
        if (*(int *)0xb92a == 0 && *(int *)0xb92c == 0) {
          if ((*(int *)0xb932 != 0 || *(int *)0xb934 != 0) &&
             (*(int *)((int)*(undefined4 *)0xb932 + 9) < 5)) {
            local_20 = *(undefined4 *)0xb932;
            uVar11 = (undefined2)((ulong)local_20 >> 0x10);
            iVar9 = (int)local_20;
            *(int *)(iVar9 + 9) = *(int *)(iVar9 + 9) + 1;
            *(undefined1 *)(iVar9 + 0x14) = 0;
          }
        }
        else if (*(int *)((int)*(undefined4 *)0xb92a + 9) < 5) {
          local_20 = *(undefined4 *)0xb92a;
          uVar11 = (undefined2)((ulong)local_20 >> 0x10);
          iVar9 = (int)local_20;
          *(int *)(iVar9 + 9) = *(int *)(iVar9 + 9) + 1;
          *(undefined1 *)(iVar9 + 0x14) = 0;
          iVar9 = FUN_1000_0000(iVar9 + 9,uVar11);
          *(int *)0xb87e = (iVar9 + *(int *)((int)local_20 + 9)) / 2;
        }
      }
      else if (*(int *)((int)*(undefined4 *)0xb926 + 9) < 5) {
        FUN_1000_016a(0x12f);
        *(int *)0xb87c = *(int *)0xb87c + 1;
        local_20 = *(undefined4 *)0xb926;
        uVar11 = (undefined2)((ulong)local_20 >> 0x10);
        iVar9 = (int)local_20;
        *(int *)(iVar9 + 9) = *(int *)(iVar9 + 9) + 1;
        *(undefined1 *)(iVar9 + 0x14) = 0;
      }
      *(int *)0xb880 = *(int *)0xb87c + *(int *)0xb87e;
      FUN_1000_0296();
    }
    else if (iVar9 == 2) {
      if (*(int *)0xb926 != 0 || *(int *)0xb928 != 0) {
        FUN_1000_016a(7);
        local_20 = *(undefined4 *)0xb926;
        *(undefined1 *)((int)local_20 + 0x15) = 1;
      }
    }
    else if (iVar9 == 3) {
      if (*(int *)0xb922 != 0 || *(int *)0xb924 != 0) {
        FUN_1000_016a(8);
        local_20 = *(undefined4 *)0xb922;
        uVar11 = (undefined2)((ulong)local_20 >> 0x10);
        *(int *)((int)local_20 + 9) = *(int *)((int)local_20 + 9) + 1;
        *(int *)0xb882 = *(int *)0xb882 + 1;
        FUN_1000_227b();
      }
    }
    else if (iVar9 == 4) {
      if (*(char *)0xb8ee == '\0') {
        FUN_1000_016a(0xfff7);
        uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        *(undefined1 *)((int)uVar2 + 0x719) = 1;
        FUN_20e6_02a4(CONCAT11(extraout_AH,10));
        local_16 = 1;
        while( true ) {
          local_14 = 1;
          while( true ) {
            uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
            iVar9 = (int)uVar2 + local_16 * 0x4f + local_14;
            uVar14 = iVar9 == 0;
            uVar7 = CONCAT11((char)((uint)(local_16 * 0x4f) >> 8),*(undefined1 *)(iVar9 + -0x50));
            puVar16 = local_3c;
            uVar12 = unaff_SS;
            FUN_214c_0885(0x20,0xb76f,unaff_DS);
            puVar15 = local_5c;
            uVar11 = unaff_SS;
            FUN_214c_0885(0x20,0xb78f,unaff_DS);
            FUN_214c_0954(puVar15,uVar11);
            puVar15 = local_7c;
            uVar11 = unaff_SS;
            FUN_214c_08af(puVar15);
            FUN_214c_08be(CONCAT11(extraout_AH_00,0xef));
            FUN_214c_08be(CONCAT11(extraout_AH_01,0xf7));
            FUN_214c_0954(puVar15,uVar11);
            FUN_214c_0933(puVar16,uVar12,uVar7);
            if ((!(bool)uVar14) &&
               (*(char *)(*(int *)0xe52d * 0x719 + local_16 * 0x4f + local_14 + 0x70d) == '\0')) {
              FUN_20e6_0260(local_16 + 1,
                            CONCAT11((char)((uint)(*(int *)0xe52d * 0x719) >> 8),
                                     (undefined1)local_14));
              uVar12 = 0xe654;
              uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
              uVar11 = unaff_DS;
              FUN_214c_1799(0,CONCAT11((char)((uint)(local_16 * 0x4f) >> 8),
                                       *(undefined1 *)
                                        ((int)uVar2 + local_16 * 0x4f + local_14 + -0x50)));
              FUN_214c_1755(uVar12,uVar11);
            }
            if (local_14 == 0x4f) break;
            local_14 = local_14 + 1;
          }
          if (local_16 == 0x17) break;
          local_16 = local_16 + 1;
        }
        FUN_20e6_02a4(0xf);
      }
    }
    else if (iVar9 == 5) {
      FUN_1000_016a(0xfff6);
      *(undefined1 *)0x9aab = 1;
      FUN_1000_d2bb((int)param_1,(int)((ulong)param_1 >> 0x10),CONCAT11(extraout_AH_02,0x49));
      uVar12 = (undefined2)((ulong)*(undefined4 *)0xb8c8 >> 0x10);
      FUN_214c_0cc9();
      FUN_214c_0cb5();
      FUN_214c_0ca9();
      uVar11 = FUN_214c_0ccd();
      *(undefined2 *)0xb8c8 = uVar11;
      *(undefined2 *)0xb8ca = uVar12;
      if (*(int *)0xb8ca < 0) {
        *(undefined2 *)0xb8c8 = 0;
        *(undefined2 *)0xb8ca = 0;
        *(int *)0xb872 = *(int *)0xb872 + -1;
        *(int *)0xb870 = *(int *)0xb870 / 2 + 1;
      }
      FUN_1000_0296();
    }
    else if (iVar9 == 6) {
      FUN_1000_2363(0xe52d,unaff_DS,0xb86e,unaff_DS,0xb86c,unaff_DS);
      *(undefined1 *)0xb919 = 0;
      FUN_1000_11fc(0x17);
      FUN_1000_0e28();
    }
    else if (iVar9 == 7) {
      FUN_1000_20dd();
      iVar9 = FUN_214c_1162(2);
      *(int *)0xe52d = (*(int *)0xe52d + -1) - iVar9;
      if (*(int *)0xe52d < 1) {
        *(undefined2 *)0xe52d = 1;
      }
      FUN_1000_2363(0xe52d,unaff_DS,0xb86e,unaff_DS,0xb86c,unaff_DS);
      FUN_1000_1a1a(*(undefined2 *)0xe52d);
      *(undefined1 *)0xb919 = 0;
      FUN_1000_11fc(0x17);
      FUN_1000_0e28();
    }
    else if (iVar9 == 8) {
      FUN_1000_7923();
    }
    else if (iVar9 == 9) {
      *(undefined1 *)0xb8f7 = 1;
      iVar9 = FUN_214c_1162(0x32);
      *(int *)0xb90f = iVar9 + 0x46;
      FUN_1000_016a(0xff41);
    }
    else if (iVar9 == 10) {
      local_1c = '\x02';
      uVar11 = 0;
      while (bVar8 = (byte)((uint)uVar11 >> 8),
            uVar11 = FUN_1000_5422((uint)bVar8 << 8,CONCAT11(bVar8,local_1c)), local_1c != '\a') {
        local_1c = local_1c + '\x01';
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
        if (*(int *)0xb926 != 0 || *(int *)0xb928 != 0) {
          *(undefined1 *)((int)*(undefined4 *)0xb926 + 0x14) = 1;
          *(undefined1 *)((int)*(undefined4 *)0xb926 + 0x15) = 0;
        }
        if (*(int *)0xb92a != 0 || *(int *)0xb92c != 0) {
          *(undefined1 *)((int)*(undefined4 *)0xb92a + 0x14) = 1;
        }
        if (*(int *)0xb932 != 0 || *(int *)0xb934 != 0) {
          *(undefined1 *)((int)*(undefined4 *)0xb932 + 0x14) = 1;
        }
        if (*(int *)0xb92e != 0 || *(int *)0xb930 != 0) {
          *(undefined1 *)((int)*(undefined4 *)0xb92e + 0x14) = 1;
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
        if (*(int *)0xb922 != 0 || *(int *)0xb924 != 0) {
          *(int *)((int)*(undefined4 *)0xb922 + 9) = *(int *)((int)*(undefined4 *)0xb922 + 9) + -1;
        }
      }
      else if (iVar9 == 0xf) {
        *(undefined1 *)0xb915 = 1;
        *(undefined1 *)0x9ab5 = 1;
        iVar9 = FUN_214c_1162(0x14);
        *(int *)0xb91a = iVar9 + 0x1e;
        if (*(int *)0xb874 < *(int *)0xb876) {
          *(int *)0xb874 = *(int *)0xb874 + 1;
        }
      }
      else if (iVar9 == 0x10) {
        iVar9 = FUN_214c_1162(8);
        if (iVar9 == 1) {
          FUN_1000_016a(0x130);
        }
        else {
          iVar9 = FUN_214c_1162(7);
          FUN_1000_016a(iVar9 + 0xd);
        }
      }
      else if (iVar9 == 0x11) {
        if (*(int *)0xb926 != 0 || *(int *)0xb928 != 0) {
          *(undefined1 *)((int)*(undefined4 *)0xb926 + 0x14) = 0;
        }
        if (*(int *)0xb92a != 0 || *(int *)0xb92c != 0) {
          *(undefined1 *)((int)*(undefined4 *)0xb92a + 0x14) = 0;
        }
        if (*(int *)0xb932 != 0 || *(int *)0xb934 != 0) {
          *(undefined1 *)((int)*(undefined4 *)0xb932 + 0x14) = 0;
        }
        if (*(int *)0xb92e != 0 || *(int *)0xb930 != 0) {
          *(undefined1 *)((int)*(undefined4 *)0xb92e + 0x14) = 0;
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
        if ((!(bool)(*(byte *)0xb86c & 1)) && (!(bool)(*(byte *)0xb86e & 1))) {
          if (*(int *)0xb86c != 0x16) {
            FUN_1000_2138(*(undefined2 *)0xb86e,*(int *)0xb86c + 1);
          }
          if (*(int *)0xb86c != 2) {
            FUN_1000_2138(*(undefined2 *)0xb86e,*(int *)0xb86c + -1);
          }
          if (*(int *)0xb86e != 2) {
            FUN_1000_2138(*(int *)0xb86e + -1,*(undefined2 *)0xb86c);
          }
          if (*(int *)0xb86e != 0x4e) {
            FUN_1000_2138(*(int *)0xb86e + 1,*(undefined2 *)0xb86c);
          }
          FUN_1000_11fc(0x17);
          FUN_1000_0e28();
        }
      }
      else if (iVar9 == 0x13) {
        local_16 = 2;
        while( true ) {
          uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
          iVar9 = (int)uVar2 + local_16 * 0x4f + *(int *)0xb86e;
          uVar14 = iVar9 == 0;
          uVar12 = CONCAT11((char)((uint)(local_16 * 0x4f) >> 8),*(undefined1 *)(iVar9 + -0x50));
          puVar16 = local_3c;
          uVar11 = unaff_SS;
          FUN_214c_0885(0x20,0xb72f,unaff_DS);
          FUN_214c_0933(puVar16,uVar11,uVar12);
          if ((!(bool)uVar14) && ((bool)((byte)local_16 & 1))) {
            FUN_1000_2138(*(undefined2 *)0xb86e,local_16);
          }
          if (local_16 == 0x16) break;
          local_16 = local_16 + 1;
        }
        local_16 = 2;
        while( true ) {
          uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
          iVar9 = (int)uVar2 + *(int *)0xb86c * 0x4f + local_16;
          uVar14 = iVar9 == 0;
          uVar12 = CONCAT11((char)((uint)(*(int *)0xb86c * 0x4f) >> 8),
                            *(undefined1 *)(iVar9 + -0x50));
          puVar16 = local_3c;
          uVar11 = unaff_SS;
          FUN_214c_0885(0x20,0xb74f,unaff_DS);
          FUN_214c_0933(puVar16,uVar11,uVar12);
          if ((!(bool)uVar14) && ((bool)((byte)local_16 & 1))) {
            FUN_1000_2138(local_16,*(undefined2 *)0xb86c);
          }
          if (local_16 == 0x4e) break;
          local_16 = local_16 + 1;
        }
        FUN_1000_11fc(0x17);
        FUN_1000_0e28();
      }
      else if (iVar9 == 0x14) {
        FUN_1000_016a(0x14);
        pcVar1 = (char *)*(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
        while( true ) {
          local_1b._0_2_ = (char *)pcVar1;
          local_1b._2_2_ = (uint)((ulong)pcVar1 >> 0x10);
          uVar5 = (uint)(char *)local_1b | local_1b._2_2_;
          local_1b = pcVar1;
          if (uVar5 == 0) break;
          if (*pcVar1 != '\x01') {
            ((char *)local_1b)[0x22] = '\x01';
            uVar14 = *pcVar1 == -0x16;
            if ((bool)uVar14) {
              iVar9 = FUN_214c_1162(6);
              uVar5 = iVar9 + 5;
              uVar14 = uVar5 == 0;
              *(uint *)((char *)local_1b + 0x20) = uVar5;
            }
            uVar12 = CONCAT11((char)(uVar5 >> 8),*local_1b);
            puVar16 = local_3c;
            uVar11 = unaff_SS;
            FUN_214c_08af(puVar16);
            FUN_214c_08be(CONCAT11(extraout_AH_03,0x45));
            FUN_214c_08be(CONCAT11(extraout_AH_04,0x48));
            FUN_214c_0933(puVar16,uVar11,uVar12);
            pcVar1 = local_1b;
            if (!(bool)uVar14) {
              ((char *)local_1b)[0x28] = '\0';
            }
          }
          local_1b = pcVar1;
          pcVar1 = *(char **)((char *)local_1b + 0x32);
        }
        *(undefined2 *)(*(int *)0xe52d * 2 + 0x799b) = 0;
      }
      else if (iVar9 == 0x15) {
        FUN_1000_016a(0xffb8);
        local_e = (char *)*(undefined4 *)0xb91e;
        while( true ) {
          if ((char *)local_e == (char *)0x0 && local_e._2_2_ == 0) break;
          iVar9 = FUN_214c_1162(2);
          iVar13 = (int)((ulong)local_e >> 0x10);
          if ((iVar9 == 0) && ((iVar13 != param_2._2_2_ || ((char *)local_e != (char *)param_2)))) {
            FUN_1000_08bd(1,&local_17,unaff_SS,&local_e,unaff_SS);
            if (local_17 == '\0') {
              local_e = *(char **)((char *)local_e + 0x16);
            }
            else {
              cVar4 = FUN_1000_052b((char *)local_e,local_e._2_2_);
              if (cVar4 != '\0') {
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
                  FUN_1000_05d6(&local_12,unaff_SS);
                  FUN_214c_02c0(0x1a,(char *)local_12,(int)((ulong)local_12 >> 0x10),(char *)local_e
                                ,(int)((ulong)local_e >> 0x10));
                  uVar11 = (undefined2)((ulong)local_12 >> 0x10);
                  pcVar10 = (char *)local_12;
                  (pcVar10 + 3)[0] = '\x01';
                  (pcVar10 + 3)[1] = '\0';
                  FUN_1000_2363(0xe52d,unaff_DS,pcVar10 + 7,uVar11,pcVar10 + 5,uVar11);
                  uVar14 = FUN_1000_0479((char *)local_12,local_12._2_2_);
                  uVar11 = (undefined2)((ulong)local_12 >> 0x10);
                  pcVar10 = (char *)local_12;
                  uVar2 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
                  *(undefined1 *)
                   ((int)uVar2 + *(int *)(pcVar10 + 5) * 0x4f + *(int *)(pcVar10 + 7) + -0x50) =
                       uVar14;
                  *(undefined1 *)
                   (*(int *)0xe52d * 0x719 + *(int *)(pcVar10 + 5) * 0x4f + *(int *)(pcVar10 + 7) +
                   0x70d) = 0;
                  FUN_1000_15a2(*(int *)0xe52d * 4 + -0x54d9,unaff_DS,&local_12,unaff_SS);
                  cVar4 = FUN_1000_052b((char *)local_e,local_e._2_2_);
                  if (cVar4 == '\0') {
                    *(int *)0xb8c0 = *(int *)0xb8c0 + -1;
                    uVar2 = *(undefined4 *)(*local_e * 4 + -0x4738);
                    iVar9 = (int)uVar2;
                    cVar4 = *local_e;
                    *(int *)(cVar4 * 4 + -0x4738) = iVar9 + -1;
                    *(int *)(cVar4 * 4 + -0x4736) = (int)((ulong)uVar2 >> 0x10) - (uint)(iVar9 == 0)
                    ;
                    *(int *)0xb8c4 = *(int *)0xb8c4 - *(int *)((char *)local_12 + 0xb);
                  }
                  if (local_16 == local_20._2_2_) break;
                  local_16 = local_16 + 1;
                }
              }
              local_12 = local_e;
              local_e = *(char **)((char *)local_e + 0x16);
              FUN_1000_14ab(0xb91e,unaff_DS,&local_12,unaff_SS);
              *(int *)0xb8c2 = *(int *)0xb8c2 + -1;
            }
          }
          else {
            local_e = *(char **)((char *)local_e + 0x16);
          }
        }
      }
      else if (iVar9 == 0x16) {
        local_17 = '\0';
        local_20 = CONCAT22(*(int *)0xb936,(undefined2)local_20);
        if (0 < *(int *)0xb936) {
          local_16 = 1;
          while( true ) {
            uVar5 = *(uint *)(local_16 * 4 + -0x46cc) | *(uint *)(local_16 * 4 + -0x46ca);
            if (uVar5 != 0) {
              uVar14 = local_16 * 4 == 0;
              uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
              uVar12 = CONCAT11((char)(uVar5 >> 8),*(undefined1 *)((int)uVar2 + 1));
              puVar16 = local_3e;
              uVar11 = unaff_SS;
              FUN_214c_08af(puVar16);
              FUN_214c_08be(CONCAT11(extraout_AH_05,4));
              FUN_214c_08be(CONCAT11(extraout_AH_06,7));
              FUN_214c_08be(CONCAT11(extraout_AH_07,9));
              FUN_214c_0933(puVar16,uVar11,uVar12);
              if (!(bool)uVar14) {
                uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
                if (*(int *)((int)uVar2 + 9) < 4) {
                  uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
                  uVar3 = *(undefined4 *)(local_16 * 4 + -0x46cc);
                  *(int *)((int)uVar3 + 9) = *(int *)((int)uVar2 + 9) + 1;
                }
                local_17 = '\x01';
              }
            }
            if (local_16 == local_20._2_2_) break;
            local_16 = local_16 + 1;
          }
        }
        if (local_17 != '\0') {
          FUN_1000_016a(0xff3a);
        }
      }
      else if (iVar9 == 0x17) {
        local_17 = '\0';
        local_20 = CONCAT22(*(int *)0xb936,(undefined2)local_20);
        if (0 < *(int *)0xb936) {
          local_16 = 1;
          while( true ) {
            uVar5 = *(uint *)(local_16 * 4 + -0x46cc) | *(uint *)(local_16 * 4 + -0x46ca);
            if (uVar5 != 0) {
              uVar14 = local_16 * 4 == 0;
              uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
              uVar12 = CONCAT11((char)(uVar5 >> 8),*(undefined1 *)((int)uVar2 + 1));
              puVar16 = local_3e;
              uVar11 = unaff_SS;
              FUN_214c_08af(puVar16);
              FUN_214c_08be(CONCAT11(extraout_AH_08,4));
              FUN_214c_08be(CONCAT11(extraout_AH_09,7));
              FUN_214c_08be(CONCAT11(extraout_AH_10,9));
              FUN_214c_0933(puVar16,uVar11,uVar12);
              if (!(bool)uVar14) {
                uVar2 = *(undefined4 *)(local_16 * 4 + -0x46cc);
                uVar3 = *(undefined4 *)(local_16 * 4 + -0x46cc);
                *(int *)((int)uVar3 + 9) = *(int *)((int)uVar2 + 9) + -1;
                local_17 = '\x01';
              }
            }
            if (local_16 == local_20._2_2_) break;
            local_16 = local_16 + 1;
          }
        }
        if (local_17 != '\0') {
          FUN_1000_016a(0xff3a);
        }
      }
      else if (iVar9 == 0x18) {
        *(int *)0xb87a = *(int *)0xb87a + 1;
        FUN_1000_016a(0xffa6);
        FUN_1000_0296();
      }
    }
    FUN_1000_bd12((char *)param_2,param_2._2_2_);
  }
  return;
}



void FUN_1000_c8dd(undefined2 param_1,undefined4 param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
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
  char local_16;
  char local_15;
  int local_14;
  int local_12;
  int local_10;
  undefined4 local_a;
  char *local_6;
  
  iVar4 = FUN_214c_1162(100);
  *(int *)0xb909 = *(int *)0xb909 + 200 + iVar4;
  iVar4 = *(int *)((int)param_2 + 1);
  if (iVar4 == 1) {
    if (*(char *)0xb8f0 == '\0') {
      FUN_1000_016a(0x68);
    }
    else {
      FUN_1000_016a(0x67);
    }
    if (*(int *)0xb870 == *(int *)0xb872) {
      iVar4 = FUN_214c_1162(6);
      *(int *)0xb872 = *(int *)0xb872 + 1 + iVar4;
      *(undefined2 *)0xb870 = *(undefined2 *)0xb872;
    }
    else {
      iVar4 = FUN_214c_1162(*(int *)0xb888 * 3);
      *(int *)0xb870 = *(int *)0xb888 * 2 + *(int *)0xb870 + iVar4;
      if (*(int *)0xb872 < *(int *)0xb870) {
        *(undefined2 *)0xb870 = *(undefined2 *)0xb872;
      }
    }
    if (*(char *)0xb8ee == '\0') {
      FUN_1000_0296();
    }
    else {
      *(undefined1 *)0xb8ee = 0;
      FUN_1000_11fc(0x17);
    }
    goto LAB_1000_d16b;
  }
  if (iVar4 == 2) {
    if (*(char *)0xb8f0 == '\0') {
      FUN_1000_016a(0x1e);
    }
    else {
      FUN_1000_016a(0x68);
    }
    if (*(int *)0xb870 == *(int *)0xb872) {
      iVar4 = FUN_214c_1162(0xf);
      *(int *)0xb872 = *(int *)0xb872 + 1 + iVar4;
      *(undefined2 *)0xb870 = *(undefined2 *)0xb872;
    }
    else {
      *(undefined2 *)0xb870 = *(undefined2 *)0xb872;
    }
    if ((*(char *)0xb8ee == '\0') && (*(char *)0xb8ed == '\0')) {
      FUN_1000_0296();
    }
    else {
      *(undefined1 *)0xb8ee = 0;
      *(undefined1 *)0xb8ed = 0;
      FUN_1000_11fc(0x17);
    }
    goto LAB_1000_d16b;
  }
  if (iVar4 == 3) {
    if (*(char *)0xb8f0 == '\0') {
      FUN_1000_016a(0x132);
    }
    else {
      FUN_1000_016a(0x6a);
    }
    uVar5 = FUN_214c_1162(4);
    *(int *)0xb874 = *(int *)0xb874 + 1 + uVar5 / 3;
    *(int *)0xb876 = *(int *)0xb876 + 1;
    if (*(int *)0xb876 < *(int *)0xb874) {
      *(undefined2 *)0xb876 = *(undefined2 *)0xb874;
    }
    FUN_1000_0296();
    goto LAB_1000_d16b;
  }
  if (iVar4 == 4) {
    if (*(char *)0xb8f0 == '\0') {
      FUN_1000_016a(0x6c);
    }
    else {
      FUN_1000_016a(0x6b);
    }
    if (*(int *)0xb874 < *(int *)0xb876) {
      *(undefined2 *)0xb874 = *(undefined2 *)0xb876;
    }
    else {
      iVar4 = FUN_214c_1162(2);
      *(int *)0xb874 = *(int *)0xb874 + 2 + iVar4;
      *(undefined2 *)0xb876 = *(undefined2 *)0xb874;
    }
    FUN_1000_0296();
    goto LAB_1000_d16b;
  }
  if (iVar4 == 5) {
    if (*(char *)0xb8f0 == '\0') {
      FUN_1000_016a(0x6f);
    }
    else {
      FUN_1000_016a(0x6e);
    }
    *(undefined1 *)0xb8ef = 1;
    iVar4 = FUN_214c_1162(0x32);
    *(int *)0xb8ff = iVar4 + 100;
    goto LAB_1000_d16b;
  }
  if (iVar4 != 6) {
    if (iVar4 == 7) {
      FUN_20e6_020d();
      FUN_1000_0296();
      FUN_1000_016a(0x27);
      *(undefined1 *)0xb8ee = 1;
      iVar4 = FUN_214c_1162(0x4b);
      *(int *)0xb8fd = iVar4 + 0x32;
      local_16 = '\x02';
      while( true ) {
        local_14 = 1;
        while( true ) {
          *(undefined1 *)(local_16 * 0x18 + local_14 + -0x65a2) = 0;
          *(undefined1 *)(local_16 * 0x18 + local_14 + -0x6542) = 0;
          if (local_14 == 0x18) break;
          local_14 = local_14 + 1;
        }
        if (local_16 == '\x05') break;
        local_16 = local_16 + '\x01';
      }
      pcVar1 = (char *)*(undefined4 *)0xb91e;
      while( true ) {
        local_a._0_2_ = (char *)pcVar1;
        local_a._2_2_ = (uint)((ulong)pcVar1 >> 0x10);
        uVar11 = ((uint)(char *)local_a | local_a._2_2_) == 0;
        local_a = pcVar1;
        if ((bool)uVar11) break;
        uVar6 = CONCAT11((char)(((uint)(char *)local_a | local_a._2_2_) >> 8),*pcVar1);
        puVar13 = local_36;
        uVar7 = unaff_SS;
        FUN_214c_08af(puVar13);
        FUN_214c_08be(CONCAT11(extraout_AH,7));
        FUN_214c_08be(CONCAT11(extraout_AH_00,6));
        FUN_214c_0933(puVar13,uVar7,uVar6);
        uVar7 = (undefined2)((ulong)local_a >> 0x10);
        if ((bool)uVar11) {
          ((char *)local_a)[0x13] = '\0';
        }
        pcVar1 = *(char **)((char *)local_a + 0x16);
      }
      local_10 = 1;
      while( true ) {
        uVar2 = *(undefined4 *)(local_10 * 4 + 4);
        *(undefined1 *)((int)uVar2 + 0x719) = 0;
        local_14 = 1;
        while( true ) {
          for (local_12 = 1;
              *(undefined1 *)(local_10 * 0x719 + local_14 * 0x4f + local_12 + 0x70d) = 0,
              local_12 != 0x4f; local_12 = local_12 + 1) {
          }
          if (local_14 == 0x17) break;
          local_14 = local_14 + 1;
        }
        if (local_10 == 0xf) break;
        local_10 = local_10 + 1;
      }
      FUN_1000_2fe0();
      FUN_1000_30ec();
    }
    else if (iVar4 == 8) {
      if (*(char *)0xb8f0 == '\0') {
        FUN_1000_016a(0x29);
      }
      else {
        FUN_1000_016a(0x70);
      }
      *(undefined1 *)0xb915 = 1;
      iVar4 = FUN_214c_1162(10);
      *(int *)0xb91a = iVar4 + 0x14;
    }
    else if (iVar4 == 9) {
      if (*(char *)0xb916 == '\0') {
        FUN_1000_016a(0x72);
        *(undefined1 *)0xb8ec = 1;
        iVar4 = FUN_214c_1162(5);
        *(int *)0xb8f9 = iVar4 + 10;
      }
      else {
        FUN_1000_016a(0x71);
        *(undefined1 *)0xb916 = 0;
      }
    }
    else if (iVar4 == 10) {
      if (*(char *)0xb8ec == '\0') {
        FUN_1000_016a(0x33);
        *(undefined1 *)0xb916 = 1;
        iVar4 = FUN_214c_1162(5);
        *(int *)0xb91c = iVar4 + 0x1e;
      }
      else {
        FUN_1000_016a(0x31);
        *(undefined1 *)0xb8ec = 0;
      }
    }
    else if (iVar4 == 0xb) {
      FUN_1000_016a(0x133);
      *(undefined1 *)0xb8f0 = 1;
      *(undefined1 *)0xb913 = 1;
      *(int *)0xb87a = *(int *)0xb87a + -1;
      if (*(int *)0xb87a < 1) {
        FUN_1000_7364(&param_1,unaff_SS,100);
      }
      iVar4 = FUN_214c_1162(0x32);
      *(int *)0xb901 = iVar4 + 0x15e;
    }
    else if (iVar4 == 0xc) {
      FUN_1000_016a(0x2f);
      *(undefined1 *)0xb8ed = 1;
      iVar4 = FUN_214c_1162(100);
      *(int *)0xb8fb = iVar4 + 200;
    }
    else if (iVar4 == 0xd) {
      FUN_1000_016a(0x30);
      iVar4 = FUN_214c_1162(100);
      *(int *)0xb892 = *(int *)0xb892 + 500 + iVar4;
    }
    else if (iVar4 == 0xe) {
      FUN_1000_016a(0x73);
      FUN_1000_772e();
      uVar5 = FUN_214c_1162(*(int *)(*(int *)0xb888 * 2 + -0x46b8) -
                            *(int *)((*(int *)0xb888 + -1) * 2 + -0x46b8));
      *(int *)0xb886 = *(int *)((*(int *)0xb888 + -1) * 2 + -0x46b8) + uVar5 / 2;
      FUN_1000_0296();
    }
    else if (iVar4 == 0xf) {
      FUN_1000_77fe();
      if (*(int *)0xb888 < 2) {
        *(undefined2 *)0xb886 = 0;
      }
      else {
        iVar4 = FUN_214c_1162(*(int *)(*(int *)0xb888 * 2 + -0x46b8) -
                              *(int *)((*(int *)0xb888 + -1) * 2 + -0x46b8));
        *(int *)0xb886 = *(int *)(*(int *)0xb888 * 2 + -0x46b8) - iVar4;
      }
      if (*(int *)0xb886 < 0) {
        *(undefined2 *)0xb886 = 0;
      }
      FUN_1000_0296();
    }
    else if (iVar4 == 0x10) {
      FUN_1000_53c9();
      *(undefined1 *)0xb8f8 = 1;
      iVar4 = FUN_214c_1162(100);
      *(int *)0xb911 = iVar4 + 300;
    }
    else if (iVar4 == 0x11) {
      FUN_20e6_020d();
      *(undefined1 *)0xb8f2 = 1;
      *(undefined1 *)0xb8f8 = 0;
      iVar4 = FUN_214c_1162(100);
      *(int *)0xb905 = iVar4 + 0x96;
    }
    else if (iVar4 == 0x12) {
      *(undefined1 *)0xb8f3 = 1;
      iVar4 = FUN_214c_1162(10);
      *(int *)0xb907 = iVar4 + 0xf;
    }
    else if (iVar4 == 0x13) {
      FUN_1000_016a(0x47);
      *(undefined1 *)0xb8f1 = 1;
      iVar4 = FUN_214c_1162(0x32);
      *(int *)0xb903 = iVar4 + 100;
    }
    else if (iVar4 == 0x14) {
      if (*(int *)0xb909 < 400) {
        FUN_1000_016a(0xac);
      }
      else {
        FUN_1000_016a(0xad);
      }
      iVar4 = FUN_214c_1162(200);
      *(int *)0xb909 = *(int *)0xb909 + 400 + iVar4;
    }
    else if (iVar4 == 0x15) {
      *(undefined1 *)0xb8f5 = 1;
      iVar4 = FUN_214c_1162(0xf);
      *(int *)0xb90b = iVar4 + 0x19;
    }
    else if (iVar4 == 0x16) {
      *(undefined1 *)0xb8f6 = 1;
      iVar4 = FUN_214c_1162(0xf);
      *(int *)0xb90d = iVar4 + 0x19;
      pcVar1 = (char *)*(undefined4 *)0xb91e;
      while( true ) {
        local_a._0_2_ = (char *)pcVar1;
        local_a._2_2_ = (uint)((ulong)pcVar1 >> 0x10);
        iVar4 = local_a._2_2_;
        local_a = pcVar1;
        if ((char *)local_a == (char *)0x0 && local_a._2_2_ == 0) break;
        if ((*(int *)((char *)local_a + 3) == 1) ||
           (pcVar8 = (char *)local_a, cVar3 = FUN_1000_052b(pcVar8,iVar4), pcVar1 = local_a,
           cVar3 != '\0')) {
LAB_1000_cfc2:
          local_a = pcVar1;
          local_6 = *(char **)((char *)local_a + 0x16);
        }
        else {
          local_6 = local_a;
          if ((*local_a == '\x02') && (*(int *)((char *)local_a + 1) == 0x16)) goto LAB_1000_cfc2;
        }
        local_15 = '\x01';
        local_18 = *(int *)0xb936;
        if (0 < local_18) {
          local_14 = 1;
          while( true ) {
            if ((local_15 == '\0') ||
               ((local_a._2_2_ == *(int *)(local_14 * 4 + -0x46ca) &&
                ((char *)local_a == (char *)*(undefined2 *)(local_14 * 4 + -0x46cc))))) {
              local_15 = '\0';
            }
            else {
              local_15 = '\x01';
            }
            if (local_14 == local_18) break;
            local_14 = local_14 + 1;
          }
        }
        pcVar1 = local_6;
        if (((((local_15 != '\0') &&
              ((local_a._2_2_ != *(int *)0xb924 ||
               ((char *)local_a != (char *)*(undefined2 *)0xb922)))) &&
             ((local_a._2_2_ != *(int *)0xb928 || ((char *)local_a != (char *)*(undefined2 *)0xb926)
              ))) && ((((local_a._2_2_ != *(int *)0xb934 ||
                        ((char *)local_a != (char *)*(undefined2 *)0xb932)) &&
                       ((local_a._2_2_ != *(int *)0xb92c ||
                        ((char *)local_a != (char *)*(undefined2 *)0xb92a)))) &&
                      ((local_a._2_2_ != *(int *)0xb930 ||
                       ((char *)local_a != (char *)*(undefined2 *)0xb92e)))))) &&
           ((*local_a != '\x02' || (*(int *)((char *)local_a + 1) != 0x16)))) {
          uVar7 = FUN_1000_052b((char *)local_a,local_a._2_2_);
          bVar9 = (byte)((uint)uVar7 >> 8);
          if ((char)uVar7 == '\0') {
            FUN_1000_15d3((uint)bVar9 << 8,(uint)bVar9 << 8,(char *)local_a,local_a._2_2_);
            pcVar1 = local_6;
          }
          else {
            FUN_1000_15d3(CONCAT11(bVar9,1),(uint)bVar9 << 8,(char *)local_a,local_a._2_2_);
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
      *(int *)0xb878 = *(int *)0xb878 + 1;
      FUN_1000_0296();
      FUN_1000_016a(0x55);
    }
    else if (iVar4 == 0x18) {
      if (*(int *)0xb936 < 4) {
        if ((*(int *)0xb8b0 == 0 && *(int *)0xb8b2 == 0) ||
           (cVar3 = FUN_1000_06d5(9), cVar3 == '\0')) {
          FUN_1000_016a(0xfe57);
        }
        else {
          FUN_1000_0662(9);
          FUN_1000_15d3((uint)extraout_AH_01 << 8,(uint)extraout_AH_01 << 8,*(undefined2 *)0xb8b0,
                        *(undefined2 *)0xb8b2);
          *(int *)0xb936 = *(int *)0xb936 + 1;
          FUN_1000_016a(0xff2f);
        }
      }
      else {
        FUN_1000_016a(0xfe57);
      }
    }
    goto LAB_1000_d16b;
  }
  if (*(char *)0xb8f0 == '\0') {
    FUN_1000_016a(0x24);
  }
  else {
    FUN_1000_016a(0x6d);
  }
  cVar3 = FUN_1000_06d5(2);
  uVar11 = 0;
  uVar10 = cVar3 == '\0';
  if ((bool)uVar10) {
LAB_1000_cb35:
    iVar4 = FUN_214c_1162(3);
    *(int *)0xb874 = (*(int *)0xb874 + -1) - iVar4;
  }
  else {
    FUN_214c_1178();
    FUN_214c_0cc5();
    if (!(bool)uVar11 && !(bool)uVar10) goto LAB_1000_cb35;
  }
  if (*(int *)0xb874 < 0) {
    FUN_1000_7364(&param_1,unaff_SS,0x65);
  }
  FUN_1000_0296();
LAB_1000_d16b:
  uVar11 = *(int *)0xb874 == 0x1c;
  if (0x1c < *(int *)0xb874) {
    uVar11 = *(int *)0xb926 == 0 && *(int *)0xb928 == 0;
    if (*(int *)0xb926 != 0 || *(int *)0xb928 != 0) {
      local_a = (char *)*(undefined4 *)0xb91e;
      while( true ) {
        iVar4 = (int)((ulong)local_a >> 0x10);
        pcVar8 = (char *)local_a;
        if ((iVar4 == *(int *)0xb928) && (pcVar8 == (char *)*(undefined2 *)0xb926)) break;
        local_a = *(char **)(pcVar8 + 0x16);
      }
      bVar9 = (byte)((ulong)local_a >> 8);
      FUN_1000_15d3(CONCAT11(bVar9,1),(uint)bVar9 << 8,pcVar8,iVar4);
      *(undefined2 *)0xb926 = 0;
      *(undefined2 *)0xb928 = 0;
      FUN_1000_016a(0xffaa);
      uVar11 = 1;
      *(undefined2 *)0xb87c = 0;
      *(undefined2 *)0xb880 = *(undefined2 *)0xb87e;
      FUN_1000_0296();
    }
  }
  uVar5 = (uint)*(byte *)((int)param_2 + 1);
  puVar13 = local_36;
  uVar6 = unaff_SS;
  FUN_214c_08af(puVar13);
  FUN_214c_08be(CONCAT11(extraout_AH_02,5));
  FUN_214c_08be(CONCAT11(extraout_AH_03,6));
  puVar12 = local_56;
  uVar7 = unaff_SS;
  FUN_214c_08af(puVar12);
  FUN_214c_08df(CONCAT11(extraout_AH_04,10),CONCAT11(extraout_AH_04,8));
  FUN_214c_0954(puVar12,uVar7);
  puVar12 = local_76;
  FUN_214c_08af(puVar12);
  FUN_214c_08be(CONCAT11(extraout_AH_05,0xc));
  FUN_214c_08be(CONCAT11(extraout_AH_06,0x11));
  FUN_214c_08be(CONCAT11(extraout_AH_07,0x12));
  FUN_214c_08be(CONCAT11(extraout_AH_08,0x15));
  FUN_214c_08be(CONCAT11(extraout_AH_09,0x16));
  FUN_214c_0954(puVar12,unaff_SS);
  FUN_214c_0933(puVar13,uVar6,uVar5);
  if (!(bool)uVar11) {
    *(undefined1 *)(*(int *)((int)param_2 + 1) + -0x6572) = 1;
  }
  FUN_1000_bd12((int)param_2,param_2._2_2_);
  return;
}



void __cdecl16near FUN_1000_d26a(void)

{
  int iVar1;
  undefined2 unaff_DS;
  undefined1 uVar2;
  undefined1 uVar3;
  
  uVar2 = 0;
  uVar3 = *(char *)0xb913 == '\0';
  if (!(bool)uVar3) {
    FUN_214c_1178();
    FUN_214c_0cc5();
    if (!(bool)uVar2 && !(bool)uVar3) {
      *(undefined1 *)0xb8f0 = 1;
      iVar1 = FUN_214c_1162(0x14);
      *(int *)0xb901 = iVar1 + 0x1e;
      FUN_1000_0296();
    }
  }
  return;
}



void FUN_1000_d2a4(int param_1,undefined2 param_2)

{
  undefined2 unaff_SS;
  
  FUN_1000_016a(param_2);
  *(undefined1 *)(param_1 + -2) = 0;
  return;
}



void FUN_1000_d2bb(undefined1 *param_1,byte param_2)

{
  undefined4 uVar1;
  uint uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  int iVar3;
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
  int local_8;
  byte local_6;
  char local_5;
  char local_4;
  char local_3;
  
  FUN_1000_0040();
  local_4 = '\x01';
  if (((param_2 == 0x54) || (param_2 == 0x52)) || (param_2 == 0x61)) {
    if (*(int *)0xb8c0 < 1) {
      FUN_1000_d2a4(&stack0xfffe,0x4b);
    }
    else if ((param_2 == 0x61) &&
            (uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4),
            *(char *)((int)uVar1 + *(int *)0xb86c * 0x4f + *(int *)0xb86e + -0x50) != ' ')) {
      FUN_1000_d2a4(&stack0xfffe,0x4c);
    }
  }
  else if (param_2 == 0x49) {
    if (*(int *)0xb8c0 < 1) {
      FUN_1000_d2a4(&stack0xfffe,0xb);
    }
  }
  else if (param_2 == 0x6c) {
    if ((*(int *)0xb8d6 < 0) || ((*(int *)0xb8d6 < 1 && (*(int *)0xb8d4 == 0)))) {
      FUN_1000_d2a4(&stack0xfffe,1);
    }
  }
  else if (param_2 == 0x62) {
    if ((*(int *)0xb8d2 < 0) || ((*(int *)0xb8d2 < 1 && (*(int *)0xb8d0 == 0)))) {
      FUN_1000_d2a4(&stack0xfffe,0x16);
    }
  }
  else if (param_2 == 0x4c) {
    if ((*(int *)0xb8de < 0) || ((*(int *)0xb8de < 1 && (*(int *)0xb8dc == 0)))) {
      FUN_1000_d2a4(&stack0xfffe,0x1b);
    }
  }
  else if (param_2 == 0x45) {
    if ((*(int *)0xb8da < 0) || ((*(int *)0xb8da < 1 && (*(int *)0xb8d8 == 0)))) {
      FUN_1000_d2a4(&stack0xfffe,0x22);
    }
    else {
      local_3 = '\x01';
      local_14 = *(int *)0xb936;
      if (0 < local_14) {
        local_a = 1;
        while( true ) {
          if ((local_3 == '\0') ||
             (*(int *)(local_a * 4 + -0x46cc) == 0 && *(int *)(local_a * 4 + -0x46ca) == 0)) {
            local_3 = '\0';
          }
          else {
            local_3 = '\x01';
          }
          if (local_a == local_14) break;
          local_a = local_a + 1;
        }
      }
      if (local_3 != '\0') {
        FUN_1000_d2a4(&stack0xfffe,0x9a);
      }
    }
  }
  else if (param_2 == 0x42) {
    if ((*(int *)0xb8e6 < 0) || ((*(int *)0xb8e6 < 1 && (*(int *)0xb8e4 == 0)))) {
      FUN_1000_d2a4(&stack0xfffe,0xae);
    }
  }
  else if (param_2 == 0x72) {
    if ((*(int *)0xb8e2 < 0) || ((*(int *)0xb8e2 < 1 && (*(int *)0xb8e0 == 0)))) {
      FUN_1000_d2a4(&stack0xfffe,0x23);
    }
    else if ((((*(int *)0xb926 != 0 || *(int *)0xb928 != 0) &&
              (*(int *)0xb92a != 0 || *(int *)0xb92c != 0)) &&
             (*(int *)0xb932 != 0 || *(int *)0xb934 != 0)) &&
            (*(int *)0xb92e != 0 || *(int *)0xb930 != 0)) {
      FUN_1000_d2a4(&stack0xfffe,0x59);
    }
  }
  if (local_4 != '\0') {
    local_5 = '\x01';
    do {
      FUN_1000_0040();
      if (param_2 == 0x6c) {
        FUN_1000_016a(2);
      }
      else if (param_2 == 0x62) {
        FUN_1000_016a(0x17);
      }
      else if (param_2 == 0x54) {
        FUN_1000_016a(0xb2);
      }
      else if (param_2 == 0x4c) {
        FUN_1000_016a(0x9e);
      }
      else if (param_2 == 0x45) {
        FUN_1000_016a(0x9b);
      }
      else if (param_2 == 0x42) {
        FUN_1000_016a(0x43);
      }
      else if (param_2 == 0x72) {
        FUN_1000_016a(0x3d);
      }
      else if (param_2 == 0x49) {
        FUN_1000_016a(0x42);
      }
      else if (param_2 == 0x52) {
        FUN_1000_016a(0x3f);
      }
      else if (param_2 == 0x61) {
        FUN_1000_016a(0x4d);
      }
      FUN_1000_016a(0xc1);
      local_6 = FUN_20e6_0357();
      if (local_6 == 0x2a) {
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
        else if (param_2 == 0x45) {
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
        local_5 = '\0';
      }
    } while (local_5 != '\0');
    if (local_6 < 0x61) {
      local_8 = local_6 - 0x26;
    }
    else {
      local_8 = local_6 - 0x60;
    }
    FUN_1000_0040();
    uVar6 = local_8 == 1;
    uVar5 = (undefined2)((ulong)param_1 >> 0x10);
    if ((local_8 < 1) || (uVar6 = local_8 == *(int *)0xb8c2, *(int *)0xb8c2 < local_8)) {
      uVar2 = (uint)param_2;
      puVar8 = local_32;
      FUN_214c_08af(puVar8);
      FUN_214c_08be(CONCAT11(extraout_AH,0x4c));
      FUN_214c_08be(CONCAT11(extraout_AH_00,0x45));
      FUN_214c_08be(CONCAT11(extraout_AH_01,0x42));
      FUN_214c_08be(CONCAT11(extraout_AH_02,0x72));
      FUN_214c_08be(CONCAT11(extraout_AH_03,0x61));
      FUN_214c_0933(puVar8,unaff_SS,uVar2);
      if ((bool)uVar6) {
        FUN_1000_016a(0xfed3);
        FUN_1000_d2bb((undefined1 *)param_1,uVar5,CONCAT11(extraout_AH_04,param_2));
      }
      else {
        FUN_1000_016a(0x12d);
      }
    }
    else {
      local_12 = (char *)*(undefined4 *)0xb91e;
      FUN_1000_0040();
      local_14 = local_8 + -1;
      iVar3 = 0;
      if (0 < local_14) {
        for (local_a = 1; local_12 = *(char **)((char *)local_12 + 0x16), iVar3 = local_a,
            local_a != local_14; local_a = local_a + 1) {
        }
      }
      uVar6 = (undefined1)((uint)iVar3 >> 8);
      uVar7 = *local_12 == '\x01';
      if ((bool)uVar7) {
        uVar4 = CONCAT11(uVar6,param_2);
        puVar8 = local_32;
        FUN_214c_08af(puVar8);
        FUN_214c_08be(CONCAT11(extraout_AH_05,0x62));
        FUN_214c_08be(CONCAT11(extraout_AH_06,0x6c));
        FUN_214c_0933(puVar8,unaff_SS,uVar4);
        uVar6 = extraout_AH_07;
        if (!(bool)uVar7) {
          if (param_2 == 0x6c) {
            FUN_1000_016a(4);
            return;
          }
          FUN_1000_016a(0x66);
          return;
        }
      }
      if (param_2 == 0x54) {
        FUN_1000_b8c7((char *)local_12,local_12._2_2_);
      }
      else if (param_2 == 0x6c) {
        if (*local_12 == '\x03') {
          FUN_1000_bd2d((undefined1 *)param_1,uVar5,(char *)local_12,local_12._2_2_);
        }
        else {
          FUN_1000_016a(0x12e);
        }
      }
      else if (param_2 == 0x62) {
        if (*local_12 == '\x02') {
          FUN_1000_c8dd(CONCAT11(uVar6,*param_1),(char *)local_12,local_12._2_2_);
        }
        else {
          FUN_1000_016a(0x1a);
        }
      }
      else if (param_2 == 0x4c) {
        if (*local_12 == '\x05') {
          FUN_1000_b032((char *)local_12,local_12._2_2_);
        }
        else {
          FUN_1000_016a(0x131);
        }
      }
      else if (param_2 == 0x45) {
        if (*local_12 == '\x04') {
          FUN_1000_a68a((char *)local_12,local_12._2_2_);
        }
        else {
          FUN_1000_016a(0x21);
        }
        uVar5 = (undefined2)((ulong)local_12 >> 0x10);
        if ((*(int *)((char *)local_12 + 1) == 8) && (*(int *)((char *)local_12 + 9) == 1)) {
          FUN_1000_8e03();
          ((char *)local_12 + 9)[0] = '\0';
          ((char *)local_12 + 9)[1] = '\0';
        }
      }
      else if (param_2 == 0x42) {
        if (*local_12 == '\a') {
          FUN_1000_9d52((char *)local_12,local_12._2_2_);
        }
        else {
          FUN_1000_016a(0x44);
        }
      }
      else if (param_2 == 0x72) {
        if (*local_12 == '\x06') {
          FUN_1000_9d52((char *)local_12,local_12._2_2_);
        }
        else {
          FUN_1000_016a(0x2e);
        }
      }
      else if (param_2 == 0x49) {
        FUN_1000_9ca1((char *)local_12,local_12._2_2_);
      }
      else if (param_2 == 0x52) {
        FUN_1000_9a91((char *)local_12,local_12._2_2_);
      }
      else if (param_2 == 0x61) {
        FUN_1000_99c5((char *)local_12,local_12._2_2_);
      }
    }
  }
  return;
}



void FUN_1000_d7c9(undefined4 param_1,undefined1 *param_2)

{
  undefined1 extraout_AH;
  undefined2 unaff_DS;
  
  *(int *)0xb8c6 = 0x26 - (*(int *)0xb874 * -2 + 0x20);
  if (*(int *)0xb8c6 < 0xf) {
    *(undefined2 *)0xb8c6 = 0xf;
  }
  if (*(int *)0xb8c6 < *(int *)0xb8c4) {
    FUN_1000_0040();
    FUN_1000_016a(0x148);
    *param_2 = 0;
    FUN_1000_1448();
    FUN_1000_d2bb((int)param_1,(int)((ulong)param_1 >> 0x10),CONCAT11(extraout_AH,0x61));
  }
  return;
}



void __cdecl16near FUN_1000_d81d(void)

{
  return;
}



uint FUN_1000_d827(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  
  if (((param_4 == param_2) &&
      ((uVar1 = param_1 - 1, uVar1 == param_3 || (uVar1 = param_1 + 1, uVar1 == param_3)))) ||
     ((uVar1 = param_3, param_3 == param_1 &&
      ((uVar1 = param_2 - 1, uVar1 == param_4 || (uVar1 = param_2 + 1, uVar1 == param_4)))))) {
    uVar1 = CONCAT11((char)(uVar1 >> 8),1);
  }
  else {
    uVar1 = uVar1 & 0xff00;
  }
  return uVar1;
}



char FUN_1000_d873(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  int iVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar5;
  undefined1 *puVar6;
  undefined2 uVar7;
  undefined1 local_64 [32];
  undefined1 local_44 [32];
  undefined1 local_24 [32];
  char local_4;
  
  iVar3 = (*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) + param_3) * 0x4f;
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  iVar4 = (int)uVar1 + iVar3 + *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + param_2;
  uVar5 = iVar4 == 0;
  uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar4 + -0x50));
  puVar6 = local_24;
  uVar7 = unaff_SS;
  FUN_214c_0885(0x20,0xb76f,unaff_DS);
  FUN_214c_0933(puVar6,uVar7,uVar2);
  if (((bool)uVar5) &&
     (*(char *)((*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) + param_3) * 0x4f +
                *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + param_2 + -0xc) == ' ')) {
LAB_1000_d991:
    local_4 = '\x01';
  }
  else {
    iVar3 = (*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) + param_3) * 0x4f;
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    iVar4 = (int)uVar1 + iVar3 + *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + param_2;
    uVar5 = iVar4 == 0;
    uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar4 + -0x50));
    puVar6 = local_44;
    uVar7 = unaff_SS;
    FUN_214c_0885(0x20,0xb76f,unaff_DS);
    FUN_214c_0933(puVar6,uVar7,uVar2);
    if (((!(bool)uVar5) &&
        (iVar3 = FUN_214c_1162(*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1a) + 1), iVar3 == 6)
        ) || ((*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) + param_3 == *(int *)0xb86c &&
              (*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + param_2 == *(int *)0xb86e))))
    goto LAB_1000_d991;
    local_4 = '\0';
  }
  if (local_4 != '\0') {
    iVar3 = *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) + param_3;
    uVar5 = iVar3 == 0;
    puVar6 = local_24;
    uVar7 = unaff_SS;
    FUN_214c_08af(puVar6);
    FUN_214c_08df(CONCAT11(extraout_AH,0x16),CONCAT11(extraout_AH,2));
    FUN_214c_0933(puVar6,uVar7,iVar3);
    if (!(bool)uVar5) {
      iVar3 = *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + param_2;
      uVar5 = iVar3 == 0;
      puVar6 = local_44;
      uVar7 = unaff_SS;
      FUN_214c_08af(puVar6);
      FUN_214c_08df(CONCAT11(extraout_AH_00,0x4e),CONCAT11(extraout_AH_00,2));
      FUN_214c_0933(puVar6,uVar7,iVar3);
      if (!(bool)uVar5) {
        local_4 = '\x01';
        goto LAB_1000_d9f8;
      }
    }
  }
  local_4 = '\0';
LAB_1000_d9f8:
  if (local_4 == '\0') {
    iVar3 = (*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) + param_3) * 0x4f;
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    iVar4 = (int)uVar1 + iVar3 + *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + param_2;
    uVar5 = iVar4 == 0;
    uVar2 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar4 + -0x50));
    puVar6 = local_24;
    uVar7 = unaff_SS;
    FUN_214c_0885(0x20,0xb76f,unaff_DS);
    FUN_214c_0933(puVar6,uVar7,uVar2);
    if ((!(bool)uVar5) &&
       (iVar3 = FUN_214c_1162(*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x12) + 1), iVar3 == 9))
    {
      iVar3 = *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) + param_3;
      uVar5 = iVar3 == 0;
      puVar6 = local_44;
      uVar7 = unaff_SS;
      FUN_214c_08af(puVar6);
      FUN_214c_08df(CONCAT11(extraout_AH_01,0x16),CONCAT11(extraout_AH_01,2));
      FUN_214c_0933(puVar6,uVar7,iVar3);
      if (!(bool)uVar5) {
        iVar3 = *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + param_2;
        uVar5 = iVar3 == 0;
        puVar6 = local_64;
        uVar7 = unaff_SS;
        FUN_214c_08af(puVar6);
        FUN_214c_08df(CONCAT11(extraout_AH_02,0x4e),CONCAT11(extraout_AH_02,2));
        FUN_214c_0933(puVar6,uVar7,iVar3);
        if (!(bool)uVar5) {
          uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
          *(undefined1 *)
           ((int)uVar1 + (*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) + param_3) * 0x4f +
            *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + param_2 + -0x50) = 0x20;
          local_4 = '\x01';
        }
      }
    }
  }
  return local_4;
}



void FUN_1000_db14(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined2 unaff_SS;
  
  uVar1 = *(undefined4 *)(*(int *)(param_1 + 4) + -8);
  *(undefined2 *)(param_1 + -6) = *(undefined2 *)((int)uVar1 + 0x1c);
  uVar1 = *(undefined4 *)(*(int *)(param_1 + 4) + -8);
  *(undefined2 *)(param_1 + -4) = *(undefined2 *)((int)uVar1 + 0x1e);
  iVar3 = *(int *)(*(int *)(param_1 + 4) + -0x13);
  if (iVar3 < 0) {
    iVar3 = -iVar3;
  }
  iVar4 = *(int *)(*(int *)(param_1 + 4) + -0x15);
  if (iVar4 < 0) {
    iVar4 = -iVar4;
  }
  if (iVar3 < iVar4) {
    cVar2 = FUN_1000_d873(*(undefined2 *)(param_1 + 4),0,*(undefined2 *)(param_1 + 0xc));
    if (cVar2 == '\0') {
      cVar2 = FUN_1000_d873(*(undefined2 *)(param_1 + 4),*(undefined2 *)(param_1 + 10),0);
      if (cVar2 != '\0') {
        *(int *)(param_1 + -4) = *(int *)(param_1 + -4) + *(int *)(param_1 + 10);
      }
    }
    else {
      *(int *)(param_1 + -6) = *(int *)(param_1 + -6) + *(int *)(param_1 + 0xc);
    }
  }
  else {
    cVar2 = FUN_1000_d873(*(undefined2 *)(param_1 + 4),*(undefined2 *)(param_1 + 10),0);
    if (cVar2 == '\0') {
      cVar2 = FUN_1000_d873(*(undefined2 *)(param_1 + 4),0,*(undefined2 *)(param_1 + 0xc));
      if (cVar2 != '\0') {
        *(int *)(param_1 + -6) = *(int *)(param_1 + -6) + *(int *)(param_1 + 0xc);
      }
    }
    else {
      *(int *)(param_1 + -4) = *(int *)(param_1 + -4) + *(int *)(param_1 + 10);
    }
  }
  return;
}



void FUN_1000_dc2b(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  uint uVar3;
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
  int iVar4;
  int iVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar7;
  bool bVar8;
  undefined1 uVar9;
  bool bVar10;
  undefined1 *puVar11;
  undefined2 uVar12;
  undefined1 local_68 [32];
  undefined1 local_48 [32];
  undefined1 local_28 [32];
  int local_8;
  uint local_6;
  int local_4;
  
  FUN_1000_db14(&stack0xfffe);
  if (local_8 == *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c)) {
    uVar3 = *(uint *)((int)*(undefined4 *)(param_1 + -8) + 0x1e);
    uVar7 = local_6 < uVar3;
    uVar9 = local_6 == uVar3;
    if ((bool)uVar9) {
      FUN_214c_1178();
      FUN_214c_0cc5();
      if (!(bool)uVar7 && !(bool)uVar9) {
        FUN_214c_1162(3);
        FUN_214c_1162(3);
        FUN_1000_db14(&stack0xfffe);
      }
    }
  }
  if ((local_8 != *(int *)0xb86c) || (local_6 != *(uint *)0xb86e)) {
    if (*(char *)*(undefined4 *)(param_1 + -8) == 'X') {
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar4 = (int)uVar1 + local_8 * 0x4f + local_6;
      uVar7 = iVar4 == 0;
      uVar12 = CONCAT11((char)((uint)(local_8 * 0x4f) >> 8),*(undefined1 *)(iVar4 + -0x50));
      puVar11 = local_28;
      uVar6 = unaff_SS;
      FUN_214c_08af(puVar11);
      FUN_214c_08be(CONCAT11(extraout_AH,0xf7));
      FUN_214c_08be(CONCAT11(extraout_AH_00,0x7e));
      FUN_214c_0933(puVar11,uVar6,uVar12);
      if ((bool)uVar7) {
        return;
      }
    }
    uVar3 = FUN_20e6_028c();
    *(uint *)(param_1 + -0xd) = uVar3 & 0xff;
    uVar3 = FUN_20e6_0298();
    *(uint *)(param_1 + -0xb) = uVar3 & 0xff;
    if ((*(char *)((int)*(undefined4 *)(param_1 + -8) + 0x23) != '\0') &&
       (*(char *)((int)*(undefined4 *)(param_1 + -8) + 0x27) == '\0')) {
      if (*(char *)0xb8f2 == '\0') {
        FUN_20e6_0260(*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) + 1,
                      *(undefined1 *)((int)*(undefined4 *)(param_1 + -8) + 0x1e));
      }
      else {
        FUN_20e6_0260((0xd - *(int *)0xb86c) + *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c),
                      (*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + 0x27) - *(int *)0xb86e)
        ;
      }
      if (*(char *)(*(int *)0xe52d * 0x719 +
                    *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) * 0x4f +
                    *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + 0x70d) != '\0') {
        iVar4 = *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) * 0x4f;
        uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        iVar5 = (int)uVar1 + iVar4 + *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e);
        uVar7 = iVar5 == 0;
        uVar12 = CONCAT11((char)((uint)iVar4 >> 8),*(undefined1 *)(iVar5 + -0x50));
        puVar11 = local_48;
        uVar6 = unaff_SS;
        FUN_214c_08af(puVar11);
        FUN_214c_08be(CONCAT11(extraout_AH_01,*(undefined1 *)0x1));
        FUN_214c_08be(CONCAT11(extraout_AH_02,*(undefined1 *)0x3));
        FUN_214c_0933(puVar11,uVar6,uVar12);
        if ((bool)uVar7) {
          uVar12 = 0xe654;
          iVar4 = *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) * 0x4f;
          uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
          uVar6 = unaff_DS;
          FUN_214c_1799(0,CONCAT11((char)((uint)iVar4 >> 8),
                                   *(undefined1 *)
                                    ((int)uVar1 + iVar4 +
                                     *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + -0x50)));
          FUN_214c_1755(uVar12,uVar6);
          goto LAB_1000_de55;
        }
      }
      FUN_1000_0094();
    }
LAB_1000_de55:
    *(undefined1 *)
     (*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) * 0x4f +
      *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + -0xc) = 0x20;
    *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) = local_8;
    *(uint *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) = local_6;
    if (*(char *)0xb8f0 != '\0') {
      local_4 = FUN_214c_1162(0x1c);
      local_4 = local_4 + 1;
      *(undefined1 *)((int)*(undefined4 *)(param_1 + -8) + 1) =
           *(undefined1 *)(local_4 * 0x2a + -0x5007);
      *(int *)((int)*(undefined4 *)(param_1 + -8) + 4) = local_4;
    }
    *(undefined1 *)
     (*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) * 0x4f +
      *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + -0xc) =
         *(undefined1 *)((int)*(undefined4 *)(param_1 + -8) + 1);
    if (((*(char *)0xb8f8 != '\0') && (*(char *)0xb8f2 == '\0')) &&
       (*(char *)((int)*(undefined4 *)(param_1 + -8) + 0x27) == '\0')) {
      FUN_1000_0428(CONCAT11((char)((uint)(local_8 * 0x4f) >> 8),
                             *(undefined1 *)(local_8 * 0x4f + local_6 + -0xc)),local_6,local_8);
    }
    *(undefined1 *)((int)*(undefined4 *)(param_1 + -8) + 0x23) = *(undefined1 *)0xb8f8;
    uVar6 = (undefined2)((ulong)*(undefined4 *)(param_1 + -8) >> 0x10);
    iVar4 = (int)*(undefined4 *)(param_1 + -8);
    if (*(int *)(iVar4 + 0x2e) == 0 && *(int *)(iVar4 + 0x30) == 0) {
      iVar4 = *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) * 0x4f;
      uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
      iVar5 = (int)uVar1 + iVar4 + *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e);
      uVar7 = iVar5 == 0;
      uVar12 = CONCAT11((char)((uint)iVar4 >> 8),*(undefined1 *)(iVar5 + -0x50));
      puVar11 = local_48;
      uVar6 = unaff_SS;
      FUN_214c_0885(0x20,0xb7cf,unaff_DS);
      FUN_214c_0933(puVar11,uVar6,uVar12);
      if (!(bool)uVar7) {
        uVar3 = (uint)*(byte *)*(undefined4 *)(param_1 + -8);
        puVar11 = local_68;
        uVar6 = unaff_SS;
        FUN_214c_08af(puVar11);
        FUN_214c_08be(CONCAT11(extraout_AH_03,0x56));
        FUN_214c_08be(CONCAT11(extraout_AH_04,0x46));
        FUN_214c_08be(CONCAT11(extraout_AH_05,0x4f));
        FUN_214c_08be(CONCAT11(extraout_AH_06,0x67));
        FUN_214c_08be(CONCAT11(extraout_AH_07,0x55));
        FUN_214c_08be(CONCAT11(extraout_AH_08,0x54));
        FUN_214c_08be(CONCAT11(extraout_AH_09,0x4e));
        FUN_214c_08be(CONCAT11(extraout_AH_10,0x44));
        FUN_214c_08be(CONCAT11(extraout_AH_11,1));
        FUN_214c_08be(CONCAT11(extraout_AH_12,0x42));
        FUN_214c_0933(puVar11,uVar6,uVar3);
        if (!(bool)uVar7) {
          FUN_214c_1178();
          bVar8 = false;
          bVar10 = true;
          FUN_214c_0cc5();
          if (!bVar8 && !bVar10) {
            FUN_1000_1988((int)*(undefined4 *)(param_1 + -8) + 0x2e,
                          (int)((ulong)*(undefined4 *)(param_1 + -8) >> 0x10),
                          (int)*(undefined4 *)(param_1 + -8) + 0x1e,
                          (int)((ulong)*(undefined4 *)(param_1 + -8) >> 0x10),
                          (int)*(undefined4 *)(param_1 + -8) + 0x1c,
                          (int)((ulong)*(undefined4 *)(param_1 + -8) >> 0x10));
            uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
            *(undefined1 *)
             ((int)uVar1 + *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) * 0x4f +
              *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + -0x50) = 0x20;
            FUN_1000_14ab(*(int *)0xe52d * 4 + -0x54d9,unaff_DS,
                          (int)*(undefined4 *)(param_1 + -8) + 0x2e,
                          (int)((ulong)*(undefined4 *)(param_1 + -8) >> 0x10));
          }
        }
      }
    }
    FUN_20e6_0260(*(undefined1 *)(param_1 + -0xb),*(undefined1 *)(param_1 + -0xd));
    return;
  }
  uVar7 = *(char *)0xb8f1 == '\0';
  if ((bool)uVar7) {
    cVar2 = FUN_1000_06d5(0x12);
    uVar7 = cVar2 == '\0';
    if (!(bool)uVar7) goto LAB_1000_e0d6;
  }
  else {
LAB_1000_e0d6:
    uVar3 = (uint)*(byte *)*(undefined4 *)(param_1 + -8);
    puVar11 = local_28;
    uVar6 = unaff_SS;
    FUN_214c_0885(0x20,0xb80f,unaff_DS);
    FUN_214c_0933(puVar11,uVar6,uVar3);
    if (!(bool)uVar7) goto LAB_1000_e115;
  }
  FUN_1000_7ebc((int)param_2,(int)((ulong)param_2 >> 0x10),(int)*(undefined4 *)(param_1 + 4),
                (int)((ulong)*(undefined4 *)(param_1 + 4) >> 0x10),param_1 + -8,unaff_SS);
LAB_1000_e115:
  if ((*(char *)0xb8f0 != '\0') && (*(int *)(param_1 + -8) != 0 || *(int *)(param_1 + -6) != 0)) {
    iVar4 = FUN_214c_1162(0x23);
    *(undefined1 *)((int)*(undefined4 *)(param_1 + -8) + 1) =
         *(undefined1 *)((iVar4 + 1) * 0x2a + -0x5007);
    *(int *)((int)*(undefined4 *)(param_1 + -8) + 4) = iVar4 + 1;
    *(undefined1 *)
     (*(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1c) * 0x4f +
      *(int *)((int)*(undefined4 *)(param_1 + -8) + 0x1e) + -0xc) =
         *(undefined1 *)((int)*(undefined4 *)(param_1 + -8) + 1);
  }
  return;
}



void FUN_1000_e193(char *param_1)

{
  byte *pbVar1;
  byte bVar2;
  undefined4 uVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
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
  int iVar8;
  undefined1 extraout_AH_13;
  undefined1 extraout_AH_14;
  undefined1 extraout_AH_15;
  undefined1 extraout_AH_16;
  byte *pbVar10;
  undefined2 uVar11;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar12;
  bool bVar13;
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
  int local_15;
  int local_13;
  int local_11;
  char local_b;
  undefined4 local_a;
  byte *local_6;
  int local_4;
  
  if (9 < *(int *)(*(int *)0xe52d * 2 + 0x799b)) {
    FUN_1000_76a4();
  }
  local_a = (byte *)*(undefined4 *)(*(int *)0xe52d * 4 + -0x5499);
LAB_1000_e1be:
  do {
    if (*param_1 == '\0') {
      return;
    }
    if ((byte *)local_a == (byte *)0x0 && local_a._2_2_ == 0) {
      return;
    }
    bVar2 = *local_a;
    if (bVar2 == 0xea) {
      if (*(int *)((byte *)local_a + 10) < 500) {
        *(int *)((byte *)local_a + 10) = *(int *)((byte *)local_a + 10) + 1;
      }
      iVar5 = FUN_214c_1162(0x41);
      if (iVar5 == 0) {
        uVar11 = (undefined2)((ulong)local_a >> 0x10);
        uVar3 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        *(undefined1 *)
         ((int)uVar3 + *(int *)((byte *)local_a + 0x1c) * 0x4f + *(int *)((byte *)local_a + 0x1e) +
         -0x50) = *(undefined1 *)0x3;
      }
    }
    else if (bVar2 == 0xe8) {
      uVar6 = *(uint *)((byte *)local_a + 10);
      uVar14 = uVar6 < 0x15e;
      uVar15 = uVar6 == 0x15e;
      if ((int)uVar6 < 0x15e) {
        FUN_214c_1178();
        FUN_214c_0cc5();
        if (!(bool)uVar14 && !(bool)uVar15) {
          uVar11 = (undefined2)((ulong)local_a >> 0x10);
          *(int *)((byte *)local_a + 10) = *(int *)((byte *)local_a + 10) + 1;
        }
      }
    }
    else if (bVar2 == 1) {
      uVar6 = *(uint *)((byte *)local_a + 10);
      uVar14 = uVar6 < 0x96;
      uVar15 = uVar6 == 0x96;
      if ((int)uVar6 < 0x96) {
        FUN_214c_1178();
        FUN_214c_0cc5();
        if (!(bool)uVar14 && !(bool)uVar15) {
          uVar11 = (undefined2)((ulong)local_a >> 0x10);
          *(int *)((byte *)local_a + 10) = *(int *)((byte *)local_a + 10) + 1;
        }
      }
    }
    else if (bVar2 == 0xe4) {
      if (*(int *)((byte *)local_a + 10) < 100) {
        FUN_214c_1178();
        bVar12 = false;
        bVar13 = true;
        FUN_214c_0cc5();
        if (!bVar12 && !bVar13) {
          uVar11 = (undefined2)((ulong)local_a >> 0x10);
          *(int *)((byte *)local_a + 10) = *(int *)((byte *)local_a + 10) + 1;
        }
      }
      iVar5 = FUN_214c_1162(0x46);
      if (iVar5 == 0) {
        uVar11 = (undefined2)((ulong)local_a >> 0x10);
        uVar3 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
        *(undefined1 *)
         ((int)uVar3 + *(int *)((byte *)local_a + 0x1c) * 0x4f + *(int *)((byte *)local_a + 0x1e) +
         -0x50) = *(undefined1 *)0x3;
      }
    }
    uVar11 = (undefined2)((ulong)local_a >> 0x10);
    pbVar10 = (byte *)local_a;
    if (*(int *)(pbVar10 + 0x2a) != 0) {
      *(int *)(pbVar10 + 0x2a) = *(int *)(pbVar10 + 0x2a) + -1;
    }
    cVar4 = FUN_1000_06d5(6);
    if ((cVar4 == '\0') && (*(char *)0xb8f5 == '\0')) {
LAB_1000_e3f9:
      if (*(char *)0xb8f6 == '\0') {
        uVar14 = ((byte *)local_a)[0x28] == 0;
        if (!(bool)uVar14) {
          uVar6 = (uint)*local_a;
          puVar16 = local_97;
          uVar11 = unaff_SS;
          FUN_214c_08af(puVar16);
          FUN_214c_08be(CONCAT11(extraout_AH_07,0x48));
          FUN_214c_08be(CONCAT11(extraout_AH_08,0x58));
          FUN_214c_0933(puVar16,uVar11,uVar6);
          if ((bool)uVar14) goto LAB_1000_e7c2;
        }
        uVar11 = (undefined2)((ulong)local_a >> 0x10);
        pbVar10 = (byte *)local_a;
        if (*(int *)(pbVar10 + 0x2a) == 0) {
          if ((pbVar10[0x25] == 0) || (pbVar10[0x26] == 0)) {
            local_17 = *(int *)0xb86c - *(int *)(pbVar10 + 0x1c);
            local_13 = FUN_1000_0000(&local_17,unaff_SS);
            local_15 = *(int *)0xb86e - *(int *)((byte *)local_a + 0x1e);
            uVar15 = local_15 == 0;
            local_11 = FUN_1000_0000(&local_15,unaff_SS);
            local_b = '\0';
            uVar6 = (uint)*local_a;
            puVar16 = local_b7;
            uVar11 = unaff_SS;
            FUN_214c_08af(puVar16);
            FUN_214c_08be(CONCAT11(extraout_AH_09,0x43));
            FUN_214c_08be(CONCAT11(extraout_AH_10,0x61));
            FUN_214c_0933(puVar16,uVar11,uVar6);
            uVar14 = extraout_AH_11;
            if ((bool)uVar15) {
LAB_1000_e4ef:
              uVar7 = CONCAT11(uVar14,*local_a);
              puVar16 = local_d7;
              uVar11 = unaff_SS;
              FUN_214c_08af(puVar16);
              FUN_214c_08be(CONCAT11(extraout_AH_13,0x45));
              FUN_214c_08be(CONCAT11(extraout_AH_14,0x48));
              FUN_214c_0933(puVar16,uVar11,uVar7);
              pbVar10 = (byte *)local_a;
              uVar11 = (undefined2)((ulong)local_a >> 0x10);
              if ((bool)uVar15) {
                if ((*local_a == 0xea) && (pbVar10[0x22] != 0)) {
                  *(int *)(pbVar10 + 0x20) = *(int *)(pbVar10 + 0x20) + -1;
                  if (*(int *)(pbVar10 + 0x20) < 0) {
                    pbVar10[0x22] = 0;
                  }
                }
                else if ((*local_a == 0x58) && (pbVar10[0x28] != 0)) {
                  if (*(int *)0xe52d == 0) {
                    iVar5 = (int)*(undefined4 *)0x4 + *(int *)0xb86c * 0x4f + *(int *)0xb86e;
                    uVar14 = iVar5 == 0;
                    uVar7 = CONCAT11((char)((uint)(*(int *)0xb86c * 0x4f) >> 8),
                                     *(undefined1 *)(iVar5 + -0x50));
                    puVar16 = local_f7;
                    uVar11 = unaff_SS;
                    FUN_214c_08af(puVar16);
                    FUN_214c_08be(CONCAT11(extraout_AH_15,0xf7));
                    FUN_214c_08be(CONCAT11(extraout_AH_16,0x7e));
                    FUN_214c_0933(puVar16,uVar11,uVar7);
                    if (!(bool)uVar14) {
                      ((byte *)local_a)[0x28] = 0;
                    }
                  }
                }
                else if (pbVar10[0x22] == 0) {
                  FUN_1000_dc2b(&stack0xfffe,&local_b,unaff_SS,local_11,local_13);
                }
                else {
                  FUN_1000_dc2b(&stack0xfffe,&local_b,unaff_SS,-local_11,-local_13);
                }
              }
              else {
                if ((*local_a == 0x48) &&
                   (cVar4 = FUN_1000_d827(*(undefined2 *)0xb86e,*(undefined2 *)0xb86c,
                                          *(undefined2 *)(pbVar10 + 0x1e),
                                          *(undefined2 *)(pbVar10 + 0x1c)), cVar4 != '\0')) {
                  cVar4 = FUN_1000_1cd1((byte *)local_a,local_a._2_2_);
                  if (cVar4 != '\0') {
                    uVar11 = (undefined2)((ulong)local_a >> 0x10);
                    ((byte *)local_a)[0x22] = 1;
                    ((byte *)local_a)[0x28] = 0;
                  }
                }
                uVar11 = (undefined2)((ulong)local_a >> 0x10);
                if ((((byte *)local_a)[0x28] == 0) || (((byte *)local_a)[0x22] != 0)) {
                  FUN_1000_dc2b(&stack0xfffe,&local_b,unaff_SS,local_11,local_13);
                }
              }
            }
            else {
              FUN_214c_1178();
              bVar12 = false;
              uVar15 = true;
              FUN_214c_0cc5();
              uVar14 = extraout_AH_12;
              if (bVar12 || (bool)uVar15) goto LAB_1000_e4ef;
              iVar5 = FUN_214c_1162(3);
              iVar5 = iVar5 + -1;
              iVar8 = FUN_214c_1162(3);
              FUN_1000_dc2b(&stack0xfffe,&local_b,unaff_SS,iVar8 + -1,iVar5);
            }
            pbVar10 = (byte *)local_a;
            iVar5 = local_a._2_2_;
            if ((byte *)local_a != (byte *)0x0 || local_a._2_2_ != 0) {
              ((byte *)local_a)[0x26] = ((byte *)local_a)[0x26] == 0;
              if (((((byte *)local_a)[0x25] != 0) || (((byte *)local_a)[0x24] != 0)) &&
                 (*(int *)((byte *)local_a + 0x20) = *(int *)((byte *)local_a + 0x20) + -1,
                 *(int *)((byte *)local_a + 0x20) == 0)) {
                ((byte *)local_a)[0x25] = 0;
                ((byte *)local_a)[0x24] = 0;
              }
              uVar3 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
              if (*(char *)((int)uVar3 + *(int *)((byte *)local_a + 0x1c) * 0x4f +
                            *(int *)((byte *)local_a + 0x1e) + -0x50) == -9) {
                bVar2 = *local_a;
                if (((bVar2 == 0x41) || (bVar2 == 0x67)) || (bVar2 == 0x56)) {
                  pbVar1 = (byte *)local_a + 0x32;
                  local_b = '\x01';
                  local_4 = local_a._2_2_;
                  local_6 = (byte *)local_a;
                  local_a = *(byte **)pbVar1;
                  FUN_1000_79ea((uint)(byte)((ulong)*(byte **)pbVar1 >> 8) << 8,pbVar10,iVar5);
                }
                else if ((bVar2 == 0x44) || (bVar2 == 0x92)) {
                  uVar3 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
                  *(undefined1 *)
                   ((int)uVar3 + *(int *)((byte *)local_a + 0x1c) * 0x4f +
                    *(int *)((byte *)local_a + 0x1e) + -0x50) = 0x20;
                }
                else {
                  uVar14 = bVar2 < 0x4d;
                  uVar15 = bVar2 == 0x4d;
                  if (!(bool)uVar15) {
                    uVar14 = bVar2 < 0x4e;
                    uVar15 = bVar2 == 0x4e;
                    if (!(bool)uVar15) {
                      uVar14 = bVar2 < 0x42;
                      uVar15 = bVar2 == 0x42;
                      if (!(bool)uVar15) {
                        uVar14 = bVar2 == 0;
                        uVar15 = bVar2 == 1;
                        if (!(bool)uVar15) {
                          uVar14 = bVar2 < 0x73;
                          uVar15 = bVar2 == 0x73;
                          if (!(bool)uVar15) goto LAB_1000_e77e;
                        }
                      }
                    }
                  }
                  FUN_214c_1178();
                  FUN_214c_0cc5();
                  if (!(bool)uVar14 && !(bool)uVar15) {
                    *(undefined1 *)(*(int *)0xe52d + 0x796d) = 1;
                  }
                }
              }
LAB_1000_e77e:
              if (local_b == '\0') {
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
      uVar6 = (uint)*local_a;
      puVar16 = local_37;
      uVar11 = unaff_SS;
      FUN_214c_08af(puVar16);
      FUN_214c_08be(CONCAT11(extraout_AH,0x4e));
      FUN_214c_08be(CONCAT11(extraout_AH_00,0x45));
      FUN_214c_0933(puVar16,uVar11,uVar6);
      if (!(bool)uVar15) goto LAB_1000_e3f9;
      uVar6 = (uint)*local_a;
      puVar16 = local_57;
      uVar11 = unaff_SS;
      FUN_214c_08af(puVar16);
      FUN_214c_08be(CONCAT11(extraout_AH_01,0x46));
      FUN_214c_08be(CONCAT11(extraout_AH_02,0x61));
      FUN_214c_0933(puVar16,uVar11,uVar6);
      uVar9 = extraout_AH_03;
      if (!(bool)uVar15) {
        FUN_214c_1178();
        uVar11 = FUN_214c_0cc5();
        uVar9 = (undefined1)((uint)uVar11 >> 8);
        if (!(bool)uVar14 && !(bool)uVar15) goto LAB_1000_e3f9;
      }
      uVar7 = CONCAT11(uVar9,*local_a);
      puVar16 = local_77;
      uVar11 = unaff_SS;
      FUN_214c_08af(puVar16);
      FUN_214c_08be(CONCAT11(extraout_AH_04,0x42));
      FUN_214c_08be(CONCAT11(extraout_AH_05,0x44));
      FUN_214c_08be(CONCAT11(extraout_AH_06,0x92));
      FUN_214c_0933(puVar16,uVar11,uVar7);
      if (!(bool)uVar15) {
        FUN_214c_1178();
        FUN_214c_0cc5();
        if (!(bool)uVar14 && !(bool)uVar15) goto LAB_1000_e3f9;
      }
    }
LAB_1000_e7c2:
    local_a = *(byte **)((byte *)local_a + 0x32);
  } while( true );
}



void FUN_1000_e7da(char param_1)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  undefined2 unaff_DS;
  
  if (param_1 == '\0') {
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    *(undefined1 *)((int)uVar1 + *(int *)0xb86c * 0x4f + *(int *)0xb86e + -0x50) =
         *(undefined1 *)0x0;
  }
  FUN_1000_20dd();
  *(int *)0xe52d = *(int *)0xe52d + 1;
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  if (*(char *)((int)uVar1 + 0x71a) == '\0') {
    FUN_1000_3a12(*(undefined2 *)0xe52d);
    FUN_1000_3b34(*(undefined2 *)0xe52d);
    FUN_1000_40c0(*(undefined2 *)0xe52d);
  }
  FUN_1000_1a1a(*(undefined2 *)0xe52d);
  *(undefined1 *)0xb919 = 0;
  if (param_1 == '\0') {
    cVar2 = FUN_1000_06d5(0xe);
    if (cVar2 == '\0') {
      FUN_214c_0cc9();
      FUN_214c_0cb5();
      iVar3 = FUN_214c_0ccd();
      *(int *)0xb870 = iVar3 + 1;
    }
  }
  else {
    *(undefined2 *)0xb86c = *(undefined2 *)(*(int *)0xe52d * 4 + 0x78ed);
    *(undefined2 *)0xb86e = *(undefined2 *)(*(int *)0xe52d * 4 + 0x78ef);
  }
  FUN_1000_11fc(0x17);
  FUN_1000_0296();
  return;
}



undefined4 FUN_1000_e8ad(undefined2 param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  long lVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  int iVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar6;
  undefined1 *puVar7;
  undefined1 local_44 [32];
  undefined1 local_24 [32];
  undefined1 local_4;
  
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  iVar5 = (int)uVar1 + param_3 * 0x4f + param_2;
  uVar6 = iVar5 == 0;
  uVar3 = CONCAT11((char)(param_3 * 0x4f >> 8),*(undefined1 *)(iVar5 + -0x50));
  puVar7 = local_24;
  uVar4 = unaff_SS;
  FUN_214c_0885(0x20,0xb76f,unaff_DS);
  FUN_214c_0933(puVar7,uVar4,uVar3);
  if (((bool)uVar6) || (*(char *)0xb8f3 != '\0')) {
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    iVar5 = (int)uVar1 + param_3 * 0x4f + param_2;
    uVar6 = iVar5 == 0;
    uVar4 = CONCAT11((char)(param_3 * 0x4f >> 8),*(undefined1 *)(iVar5 + -0x50));
    puVar7 = local_44;
    FUN_214c_0885(0x20,0xb7af,unaff_DS);
    FUN_214c_0933(puVar7,unaff_SS,uVar4);
    if ((bool)uVar6) {
      local_4 = 1;
      goto LAB_1000_e938;
    }
  }
  local_4 = 0;
LAB_1000_e938:
  lVar2 = (ulong)param_3 * 0x4f;
  if (*(char *)((int)lVar2 + param_2 + -0xc) != ' ') {
    local_4 = 1;
  }
  return CONCAT22((int)((ulong)lVar2 >> 0x10),CONCAT11((char)((ulong)lVar2 >> 8),local_4));
}



void FUN_1000_e96e(char *param_1,char *param_2,int param_3)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 uVar3;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  uint uVar4;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  int iVar5;
  int iVar6;
  int iVar7;
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
  char local_b;
  int local_a;
  int local_8;
  
  uVar10 = 0x1000;
  *param_2 = '\0';
  local_a = *(int *)0xb86c;
  local_8 = *(int *)0xb86e;
  if (*(char *)0xb8ef != '\0') {
    uVar10 = 0x214c;
    param_3 = FUN_214c_1162(4);
    param_3 = param_3 + 1;
  }
  cVar2 = FUN_1000_e8ad(&stack0xfffe,*(int *)0xb86e + *(int *)(param_3 * 4 + -0x464c),
                        *(int *)0xb86c + *(int *)(param_3 * 4 + -0x464e));
  if (cVar2 == '\0') {
    *param_2 = '\x01';
  }
  else {
    local_a = *(int *)0xb86c + *(int *)(param_3 * 4 + -0x464e);
    local_8 = *(int *)0xb86e + *(int *)(param_3 * 4 + -0x464c);
  }
  if ((*param_2 != '\0') || (*(char *)0xb8f6 != '\0')) {
    FUN_1000_0428(0x20,*(undefined2 *)0xb86e,*(undefined2 *)0xb86c);
    *(int *)0xb86c = local_a;
    *(int *)0xb86e = local_8;
    FUN_1000_0e28();
    goto LAB_1000_ed19;
  }
  local_b = '\x01';
  cVar2 = FUN_1000_06d5(5);
  pcVar8 = (char *)param_1;
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  if (cVar2 == '\0') {
LAB_1000_ea57:
    if (*(char *)(local_a * 0x4f + local_8 + -0xc) == ' ') {
LAB_1000_eadc:
      uVar12 = 0;
      if (*(char *)0xb919 != '\0') {
        FUN_214c_1178();
        uVar10 = 0x214c;
        FUN_214c_0cc5();
        if ((bool)uVar12) {
          FUN_1000_0040();
          FUN_1000_016a(5);
          goto LAB_1000_eb33;
        }
      }
      *(undefined1 *)0xb919 = 0;
      FUN_1000_d7c9(pcVar8,uVar3,&local_b,unaff_SS);
      FUN_1000_0428(CONCAT11(extraout_AH_00,0x20),*(undefined2 *)0xb86e,*(undefined2 *)0xb86c);
      *(int *)0xb86c = local_a;
      *(int *)0xb86e = local_8;
      FUN_1000_0e28();
    }
    else {
      if ((*(char *)0xb8f1 != '\0') || (cVar2 = FUN_1000_06d5(0x12), cVar2 != '\0')) {
        iVar9 = local_a * 0x4f + local_8;
        uVar12 = iVar9 == 0;
        uVar16 = CONCAT11((char)((uint)(local_a * 0x4f) >> 8),*(undefined1 *)(iVar9 + -0xc));
        puVar14 = local_4b;
        uVar15 = unaff_SS;
        FUN_214c_0885(0x20,0xb80f,unaff_DS);
        puVar13 = local_2b;
        uVar10 = unaff_SS;
        FUN_214c_08af(puVar13);
        FUN_214c_08be(CONCAT11(extraout_AH,0x67));
        FUN_214c_096f(puVar13,uVar10);
        uVar10 = 0x214c;
        FUN_214c_0933(puVar14,uVar15,uVar16);
        if (!(bool)uVar12) goto LAB_1000_eadc;
      }
      FUN_1000_8573(pcVar8,uVar3,local_8,local_a);
      local_b = '\0';
    }
  }
  else {
    uVar10 = 0x214c;
    iVar9 = FUN_214c_1162(0xf);
    if (iVar9 != 0) goto LAB_1000_ea57;
    FUN_1000_0428(0x20,*(undefined2 *)0xb86e,*(undefined2 *)0xb86c);
    FUN_1000_2363(0xe52d,unaff_DS,0xb86e,unaff_DS,0xb86c,unaff_DS);
    *(undefined1 *)0xb919 = 0;
    if (*(char *)0xb8f2 != '\0') {
      FUN_1000_11fc(0x17);
    }
    FUN_1000_0e28();
  }
LAB_1000_eb33:
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  if ((((*(char *)((int)uVar1 + *(int *)0xb86c * 0x4f + *(int *)0xb86e + -0x50) == -9) &&
       (*(char *)0xb8f1 == '\0')) && (cVar2 = FUN_1000_06d5(0x12), cVar2 == '\0')) &&
     (*(char *)0xb8f6 == '\0')) {
    FUN_1000_0040();
    uVar16 = 0xe654;
    uVar15 = unaff_DS;
    FUN_214c_17f7(0,0xe966,uVar10);
    FUN_214c_1755(uVar16,uVar15);
    FUN_1000_7849(CONCAT11(extraout_AH_01,1));
    if (*(int *)0xb909 < 400) {
      *(undefined2 *)0xb909 = 3000;
      if (*(char *)(*(int *)0xe52d + 0x796d) != '\0') {
        cVar2 = FUN_1000_06d5(2);
        uVar12 = 0;
        uVar11 = cVar2 == '\0';
        if (!(bool)uVar11) {
          FUN_214c_1178();
          FUN_214c_0cc5();
          if ((bool)uVar12 || (bool)uVar11) goto LAB_1000_ec9a;
        }
        uVar12 = 0;
        uVar11 = *(int *)0xb898 == 0 && *(int *)0xb89a == 0;
        if (*(int *)0xb898 != 0 || *(int *)0xb89a != 0) {
          FUN_214c_1178();
          FUN_214c_0cc5();
          if ((bool)uVar12 || (bool)uVar11) goto LAB_1000_ec9a;
        }
        iVar9 = FUN_214c_1162(2);
        *(int *)0xb874 = (*(int *)0xb874 + -1) - iVar9;
        if (*(int *)0xb874 < 1) {
          FUN_1000_7364(pcVar8,uVar3,0x65);
        }
        else {
          FUN_1000_016a(0x24);
        }
        FUN_1000_0296();
      }
    }
    else if (0x13 < *(int *)0xb8c0) {
      iVar9 = 0x1e - *(int *)0xb8c0 >> 0xf;
      FUN_214c_0cc9();
      uVar12 = 0;
      uVar11 = 1;
      uVar10 = FUN_214c_0cbb();
      FUN_214c_1178(uVar10,in_BX,iVar9);
      FUN_214c_0cc5();
      if ((!(bool)uVar12 && !(bool)uVar11) && (cVar2 = FUN_1000_06d5(0x10), cVar2 == '\0')) {
        uVar12 = 0;
        uVar11 = *(int *)0xb898 == 0 && *(int *)0xb89a == 0;
        if (*(int *)0xb898 != 0 || *(int *)0xb89a != 0) {
          FUN_214c_1178();
          FUN_214c_0cc5();
          if ((bool)uVar12 || (bool)uVar11) goto LAB_1000_ec9a;
        }
        FUN_1000_7364(pcVar8,uVar3,0x6e);
      }
    }
  }
LAB_1000_ec9a:
  if ((*param_1 != '\0') && (local_b != '\0')) {
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    iVar9 = (int)uVar1 + *(int *)0xb86c * 0x4f + *(int *)0xb86e;
    uVar12 = iVar9 == 0;
    uVar3 = CONCAT11((char)((uint)(*(int *)0xb86c * 0x4f) >> 8),*(undefined1 *)(iVar9 + -0x50));
    puVar14 = local_2b;
    uVar10 = unaff_SS;
    FUN_214c_0885(0x20,0xb7cf,unaff_DS);
    FUN_214c_0933(puVar14,uVar10,uVar3);
    if ((!(bool)uVar12) &&
       ((*(char *)0xb8f1 == '\0' && (cVar2 = FUN_1000_06d5(0x12), cVar2 == '\0')))) {
      FUN_1000_9099();
    }
  }
LAB_1000_ed19:
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  iVar9 = (int)uVar1 + *(int *)0xb86c * 0x4f + *(int *)0xb86e;
  uVar12 = iVar9 == 0;
  uVar3 = CONCAT11((char)((uint)(*(int *)0xb86c * 0x4f) >> 8),*(undefined1 *)(iVar9 + -0x50));
  puVar14 = local_2b;
  uVar10 = unaff_SS;
  FUN_214c_08af(puVar14);
  FUN_214c_08be(CONCAT11(extraout_AH_02,*(undefined1 *)0x0));
  FUN_214c_08be(CONCAT11(extraout_AH_03,*(undefined1 *)0x1));
  FUN_214c_0933(puVar14,uVar10,uVar3);
  if ((((!(bool)uVar12) && (*(char *)0xb8f1 == '\0')) &&
      (uVar4 = FUN_1000_06d5(0x12), (char)uVar4 == '\0')) && (*(char *)0xb8f6 == '\0')) {
    FUN_1000_e7da(uVar4 & 0xff00);
  }
  uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
  iVar9 = (int)uVar1 + *(int *)0xb86c * 0x4f + *(int *)0xb86e;
  uVar12 = iVar9 == 0;
  uVar10 = CONCAT11((char)((uint)(*(int *)0xb86c * 0x4f) >> 8),*(undefined1 *)(iVar9 + -0x50));
  puVar14 = local_2b;
  FUN_214c_08af(puVar14);
  FUN_214c_08be(CONCAT11(extraout_AH_04,*(undefined1 *)0x2));
  FUN_214c_08be(CONCAT11(extraout_AH_05,*(undefined1 *)0x3));
  FUN_214c_0933(puVar14,unaff_SS,uVar10);
  if (((!(bool)uVar12) && (*(char *)0xb8f1 == '\0')) &&
     ((cVar2 = FUN_1000_06d5(0x12), cVar2 == '\0' && (*(char *)0xb8f6 == '\0')))) {
    iVar9 = FUN_214c_1162(5);
    iVar5 = FUN_214c_1162(5);
    iVar6 = FUN_214c_1162(5);
    iVar7 = FUN_214c_1162(5);
    *(int *)0xb870 = ((((*(int *)0xb870 + -4) - iVar7) - iVar6) - iVar5) - iVar9;
    if (*(int *)0xe52d == 0xf) {
      iVar9 = FUN_214c_1162(5);
      iVar5 = FUN_214c_1162(5);
      iVar6 = FUN_214c_1162(5);
      iVar7 = FUN_214c_1162(5);
      *(int *)0xb870 = ((((*(int *)0xb870 + -4) - iVar7) - iVar6) - iVar5) - iVar9;
    }
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    *(undefined1 *)((int)uVar1 + *(int *)0xb86c * 0x4f + *(int *)0xb86e + -0x50) = 0x20;
    iVar9 = FUN_214c_1162(2);
    FUN_1000_016a(iVar9 + 0x1a6);
    FUN_1000_0296();
  }
  return;
}



void FUN_1000_eed5(int param_1)

{
  int iVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  iVar1 = FUN_214c_1162(0xb);
  *(int *)0xb86c = (iVar1 + 1) * 2;
  iVar1 = FUN_214c_1162(0x27);
  *(int *)0xb86e = (iVar1 + 1) * 2;
  FUN_1000_1a1a(1);
  FUN_1000_0296();
  *(undefined1 *)(param_1 + -7) = 1;
  *(undefined2 *)0xe535 = 1;
  *(undefined2 *)0xe537 = 1;
  FUN_1000_0e28();
  return;
}



void FUN_1000_ef1d(int param_1,byte param_2)

{
  uint uVar1;
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
  uVar1 = (uint)param_2;
  puVar5 = local_22;
  uVar2 = unaff_SS;
  FUN_214c_08af(puVar5);
  FUN_214c_08be(CONCAT11(extraout_AH,1));
  FUN_214c_08be(CONCAT11(extraout_AH_00,2));
  FUN_214c_08be(CONCAT11(extraout_AH_01,3));
  FUN_214c_08be(CONCAT11(extraout_AH_02,6));
  FUN_214c_0933(puVar5,uVar2,uVar1);
  if (!(bool)uVar4) {
    FUN_1000_11fc(0x17);
  }
  FUN_1000_0040();
  uVar4 = param_2 == 0;
  if ((bool)uVar4) {
    FUN_1000_016a(3);
    uVar3 = extraout_AH_04;
  }
  else {
    uVar4 = param_2 == 4;
    if ((bool)uVar4) {
      FUN_1000_016a(6);
      FUN_1000_20dd();
      uVar3 = extraout_AH_05;
    }
    else {
      uVar4 = param_2 == 1;
      if ((bool)uVar4) {
        FUN_1000_016a(0xc);
        uVar3 = extraout_AH_06;
      }
      else {
        uVar4 = param_2 == 2;
        if ((bool)uVar4) {
          FUN_1000_016a(0x18);
          uVar3 = extraout_AH_07;
        }
        else {
          uVar4 = param_2 == 3;
          if ((bool)uVar4) {
            FUN_1000_016a(0x14b);
            uVar3 = extraout_AH_08;
          }
          else {
            uVar4 = param_2 == 5;
            if ((bool)uVar4) {
              FUN_1000_016a(0xa0);
              uVar3 = extraout_AH_09;
            }
            else {
              uVar4 = param_2 == 8;
              uVar3 = extraout_AH_03;
              if ((bool)uVar4) {
                uVar4 = param_1 + -7 == 0;
                FUN_1000_7364(param_1 + -7,unaff_SS,0x7a);
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
  FUN_214c_08af(puVar5);
  FUN_214c_08be(CONCAT11(extraout_AH_11,7));
  FUN_214c_08be(CONCAT11(extraout_AH_12,9));
  FUN_214c_08be(CONCAT11(extraout_AH_13,10));
  FUN_214c_08be(CONCAT11(extraout_AH_14,0xb));
  FUN_214c_08be(CONCAT11(extraout_AH_15,6));
  FUN_214c_08be(CONCAT11(extraout_AH_16,8));
  FUN_214c_08be(CONCAT11(extraout_AH_17,0xc));
  FUN_214c_0933(puVar5,unaff_SS,uVar2);
  if ((bool)uVar4) {
    FUN_1000_1448();
  }
  return;
}



void FUN_1000_f020(int param_1,undefined1 *param_2)

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
    local_3 = FUN_20e6_0357();
  }
  else {
    local_3 = 0x2e;
    *(undefined1 *)0xb914 = 0;
  }
  FUN_1000_0040();
  *(undefined1 *)(param_1 + -5) = 1;
  uVar4 = extraout_AH;
  if (*(int *)0xb87a < 1) {
    FUN_1000_7364(param_1 + -7,unaff_SS,100);
    uVar4 = extraout_AH_00;
  }
  if (*(char *)(param_1 + -7) == '\0') goto LAB_1000_f547;
  if ((((local_3 == 0x32) || (local_3 == 0x34)) || (local_3 == 0x36)) || (local_3 == 0x38)) {
    FUN_1000_e96e(param_1 + -7,unaff_SS,param_1 + -5,unaff_SS,(int)(local_3 - 0x30) / 2);
    uVar4 = extraout_AH_01;
  }
  else if (local_3 == 0) {
    uVar2 = FUN_20e6_0357();
    local_3 = (byte)uVar2;
    if (local_3 == 0x4b) {
      uVar2 = FUN_1000_e96e(param_1 + -7,unaff_SS,param_1 + -5,unaff_SS,2);
    }
    else if (local_3 == 0x4d) {
      uVar2 = FUN_1000_e96e(param_1 + -7,unaff_SS,param_1 + -5,unaff_SS,3);
    }
    else if (local_3 == 0x48) {
      uVar2 = FUN_1000_e96e(param_1 + -7,unaff_SS,param_1 + -5,unaff_SS,4);
    }
    else if (local_3 == 0x50) {
      uVar2 = FUN_1000_e96e(param_1 + -7,unaff_SS,param_1 + -5,unaff_SS,1);
    }
    uVar4 = (undefined1)((uint)uVar2 >> 8);
  }
  else if (local_3 == 0x3c) {
    iVar3 = *(int *)0xb86c * 0x4f;
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    if ((((*(char *)((int)uVar1 + iVar3 + *(int *)0xb86e + -0x50) == -0x11) &&
         (*(char *)0xb8f1 == '\0')) && (iVar3 = FUN_1000_06d5(0x12), (char)iVar3 == '\0')) ||
       (uVar4 = (undefined1)((uint)iVar3 >> 8), *(char *)0xb917 != '\0')) {
      iVar3 = *(int *)(*(int *)0xe52d * 4 + 0x792d);
      if (((iVar3 == *(int *)0xb86c) &&
          (iVar3 = *(int *)(*(int *)0xe52d * 4 + 0x792f), iVar3 == *(int *)0xb86e)) ||
         (*(char *)0xb917 != '\0')) {
        FUN_1000_e7da(CONCAT11((char)((uint)iVar3 >> 8),1));
        *(undefined1 *)0xb914 = 1;
        uVar4 = extraout_AH_02;
      }
      else {
        FUN_1000_0040();
        FUN_1000_016a(0x20);
        uVar4 = extraout_AH_03;
      }
    }
  }
  else if (local_3 == 0x3e) {
    iVar3 = *(int *)0xb86c * 0x4f;
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    if ((*(char *)((int)uVar1 + iVar3 + *(int *)0xb86e + -0x50) == -0x11) ||
       (*(char *)0xb917 != '\0')) {
      if (((*(int *)(*(int *)0xe52d * 4 + 0x78ed) == *(int *)0xb86c) &&
          (*(int *)(*(int *)0xe52d * 4 + 0x78ef) == *(int *)0xb86e)) || (*(char *)0xb917 != '\0')) {
        FUN_1000_20dd();
        *(int *)0xe52d = *(int *)0xe52d + -1;
        if (*(int *)0xe52d < 1) {
          iVar3 = FUN_1000_7364(param_1 + -7,unaff_SS,0x67);
        }
        else {
          FUN_1000_1a1a(*(undefined2 *)0xe52d);
          *(undefined1 *)0xb919 = 0;
          *(undefined2 *)0xb86c = *(undefined2 *)(*(int *)0xe52d * 4 + 0x792d);
          *(undefined2 *)0xb86e = *(undefined2 *)(*(int *)0xe52d * 4 + 0x792f);
          iVar3 = FUN_1000_11fc(0x17);
          *(undefined1 *)0xb914 = 1;
        }
      }
      else {
        FUN_1000_0040();
        iVar3 = FUN_1000_016a(0x3c);
      }
    }
    uVar4 = (undefined1)((uint)iVar3 >> 8);
  }
  else if (local_3 == 0x51) {
    FUN_1000_763d(param_1 + -7,unaff_SS,CONCAT11(uVar4,0x51));
    uVar4 = extraout_AH_04;
  }
  else if (local_3 == 0x13) {
    FUN_1000_763d(param_1 + -7,unaff_SS,CONCAT11(uVar4,0x73));
    uVar4 = extraout_AH_05;
  }
  else if (local_3 == 0x10) {
    if ((*(char *)0xb8ed == '\0') && (*(char *)0xb8ee == '\0')) {
      FUN_1000_11fc(0x17);
      uVar4 = extraout_AH_06;
    }
  }
  else if (local_3 == 0x16) {
    FUN_1000_4b52();
    uVar4 = extraout_AH_07;
  }
  else if (local_3 == 7) {
    *(bool *)0xe539 = *(char *)0xe539 == '\0';
  }
  else if (local_3 == 8) {
    FUN_1000_6921();
    FUN_1000_11fc(0x17);
    uVar4 = extraout_AH_08;
  }
  else if (local_3 == 0x14) {
    FUN_1000_6a56();
    uVar4 = extraout_AH_09;
  }
  else if (local_3 == 0x35) {
    if (*(char *)0xb917 != '\0') {
      *(bool *)0xb8f3 = *(char *)0xb8f3 == '\0';
    }
  }
  else if (local_3 == 0x3f) {
    FUN_1000_6249();
    uVar4 = extraout_AH_10;
  }
  else if (local_3 == 0x6c) {
    if (*(char *)0xb8ed == '\0') {
      FUN_1000_d2bb(param_1 + -7,unaff_SS,CONCAT11(uVar4,0x6c));
      uVar4 = extraout_AH_11;
    }
  }
  else if (((((local_3 == 0x61) || (local_3 == 0x42)) || (local_3 == 0x72)) ||
           (((local_3 == 0x45 || (local_3 == 0x54)) ||
            ((local_3 == 0x4c || ((local_3 == 0x52 || (local_3 == 0x6c)))))))) || (local_3 == 0x62))
  {
    FUN_1000_d2bb(param_1 + -7,unaff_SS,CONCAT11(uVar4,local_3));
    uVar4 = extraout_AH_12;
  }
  else if (local_3 == 0x65) {
    FUN_1000_9f40();
    uVar4 = extraout_AH_13;
  }
  else if (local_3 == 0x4e) {
    FUN_1000_a74b();
    uVar4 = extraout_AH_14;
  }
  else if (local_3 == 0x6d) {
    FUN_1000_a45b();
    uVar4 = extraout_AH_15;
  }
  else if (local_3 == 0x68) {
    iVar3 = *(int *)0xb86c * 0x4f;
    uVar1 = *(undefined4 *)(*(int *)0xe52d * 4 + 4);
    if (*(char *)((int)uVar1 + iVar3 + *(int *)0xb86e + -0x50) == -0x65) {
      iVar3 = FUN_1000_95ee();
    }
    uVar4 = (undefined1)((uint)iVar3 >> 8);
  }
  else if ((local_3 == 0x69) || (local_3 == 0x2a)) {
    FUN_1000_5fd2();
    uVar4 = extraout_AH_16;
  }
  else if (local_3 == 99) {
    FUN_1000_4c49();
    uVar4 = extraout_AH_17;
  }
  else if (local_3 == 0x73) {
    FUN_20e6_020d();
    FUN_1000_6f02();
    FUN_20e6_0260(CONCAT11(extraout_AH_18,0x19),CONCAT11(extraout_AH_18,0x41));
    FUN_1000_1448();
    FUN_1000_11fc(0x17);
    uVar4 = extraout_AH_19;
  }
  else if (local_3 == 0x49) {
    if (*(char *)0xb917 != '\0') {
      FUN_1000_d2bb(param_1 + -7,unaff_SS,CONCAT11(uVar4,0x49));
      uVar4 = extraout_AH_20;
    }
  }
  else if (local_3 == 0x53) {
    if (*(char *)0xb917 != '\0') {
      FUN_1000_65d3();
      uVar4 = extraout_AH_21;
    }
  }
  else if (local_3 == 0x41) {
    if (*(char *)0xb917 != '\0') {
      FUN_1000_6887();
      uVar4 = extraout_AH_22;
    }
  }
  else if (local_3 == 0x43) {
    if (*(char *)0xb917 != '\0') {
      FUN_1000_d81d();
      uVar4 = extraout_AH_23;
    }
  }
  else if (local_3 == 0xe6) {
    if (*(char *)0xb917 != '\0') {
      *(bool *)0xb8f8 = *(char *)0xb8f8 == '\0';
      *(undefined2 *)0xb911 = 0x7fff;
    }
  }
  else if (local_3 == 0x25) {
    if (*(char *)0xb917 != '\0') {
      FUN_1000_62b7();
      uVar4 = extraout_AH_24;
    }
  }
  else if ((local_3 == 0x4f) && (*(char *)0xb917 != '\0')) {
    FUN_1000_6431();
    uVar4 = extraout_AH_25;
  }
  uVar5 = *(char *)(param_1 + -5) == '\0';
  if ((bool)uVar5) {
LAB_1000_f53f:
    uVar4 = 1;
  }
  else {
    uVar2 = CONCAT11(uVar4,local_3);
    puVar6 = local_25;
    FUN_214c_08af(puVar6);
    FUN_214c_08be(CONCAT11(extraout_AH_26,0x2e));
    FUN_214c_08be(CONCAT11(extraout_AH_27,0x6c));
    FUN_214c_08be(CONCAT11(extraout_AH_28,0x61));
    FUN_214c_08be(CONCAT11(extraout_AH_29,0x42));
    FUN_214c_08be(CONCAT11(extraout_AH_30,0x62));
    FUN_214c_08be(CONCAT11(extraout_AH_31,0x65));
    FUN_214c_08be(CONCAT11(extraout_AH_32,0x6d));
    FUN_214c_08be(CONCAT11(extraout_AH_33,0x72));
    FUN_214c_08be(CONCAT11(extraout_AH_34,0x45));
    FUN_214c_08be(CONCAT11(extraout_AH_35,0x4e));
    FUN_214c_08be(CONCAT11(extraout_AH_36,0x4c));
    FUN_214c_08be(CONCAT11(extraout_AH_37,0x54));
    FUN_214c_08be(CONCAT11(extraout_AH_38,0x3e));
    FUN_214c_08be(CONCAT11(extraout_AH_39,0x3c));
    FUN_214c_0933(puVar6,unaff_SS,uVar2);
    if (!(bool)uVar5) goto LAB_1000_f53f;
    uVar4 = 0;
  }
  *param_2 = uVar4;
LAB_1000_f547:
  FUN_1000_0296();
  return;
}



void FUN_1000_f550(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_4;
  
  FUN_1000_084b(&local_4,unaff_SS,9);
  if (local_4 != 0) {
    iVar1 = local_4;
    if (local_4 < 0) {
      iVar1 = -local_4;
    }
    uVar2 = FUN_214c_1162(iVar1 + 3);
    if (2 < uVar2) {
      if (local_4 < 0) {
        local_4 = -local_4;
      }
      FUN_214c_1162(local_4 / 2 + 2);
      iVar1 = FUN_214c_02dc();
      *(int *)0xb870 = *(int *)0xb870 + iVar1;
      if (*(int *)0xb872 < *(int *)0xb870) {
        *(undefined2 *)0xb870 = *(undefined2 *)0xb872;
      }
      FUN_1000_0296();
    }
  }
  if (*(int *)0xb870 < 1) {
    FUN_1000_7364(param_1 + -7,unaff_SS,0x72);
  }
  return;
}



void __cdecl16near FUN_1000_f5f2(void)

{
  char cVar1;
  int iVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  char local_a;
  char local_9;
  char local_8 [6];
  
  FUN_1000_eed5(&stack0xfffe);
  while (local_9 != '\0') {
    FUN_1000_0e28();
    local_8[0] = '\x01';
    if (4000 < *(int *)0xb892) {
      FUN_1000_7364(&local_9,unaff_SS,0x62);
    }
    if (*(char *)0xb915 == '\0') {
      FUN_1000_f020(&stack0xfffe,local_8,unaff_SS);
    }
    else {
      *(int *)0xb91a = *(int *)0xb91a + -1;
      if (*(int *)0xb91a == 0) {
        FUN_1000_0040();
        FUN_1000_016a(0xb1);
        FUN_1000_1448();
        *(undefined1 *)0xb915 = 0;
      }
    }
    if (local_8[0] != '\0') {
      if (*(int *)0xb892 % 0x14 == 0) {
        FUN_1000_3544();
        cVar1 = FUN_1000_06d5(0xb);
        if ((cVar1 != '\0') || (*(int *)0xb8a0 != 0 || *(int *)0xb8a2 != 0)) {
          FUN_1000_3544();
          FUN_1000_3544();
          FUN_1000_3544();
        }
      }
      FUN_1000_a518(&local_9,unaff_SS);
      local_a = '\0';
      while( true ) {
        if ((*(char *)(local_a + -0x4714) != '\0') &&
           (*(int *)(local_a * 2 + -0x4707) = *(int *)(local_a * 2 + -0x4707) + -1,
           *(int *)(local_a * 2 + -0x4707) < 1)) {
          *(undefined1 *)(local_a + -0x4714) = 0;
          FUN_1000_ef1d(&stack0xfffe,(int)local_a);
        }
        if (local_a == '\f') break;
        local_a = local_a + '\x01';
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
      if (local_9 != '\0') {
        if (*(char *)0xb8ec != '\0') {
          FUN_1000_f020(&stack0xfffe,local_8,unaff_SS);
          FUN_1000_0e28();
        }
        if ((*(int *)0xb890 == 0) && (*(int *)0xb870 < *(int *)0xb872)) {
          *(int *)0xb870 = *(int *)0xb870 + 1;
          *(int *)0xb890 = (0xf - *(int *)0xe52d) / 2;
          FUN_1000_0296();
        }
        else if (0 < *(int *)0xb890) {
          *(int *)0xb890 = *(int *)0xb890 + -1;
        }
        FUN_1000_f550(&stack0xfffe);
        FUN_1000_e193(&local_9,unaff_SS);
        if (*(char *)0xb916 != '\0') {
          FUN_1000_e193(&local_9,unaff_SS);
          *(int *)0xb91c = *(int *)0xb91c + -1;
          if (*(int *)0xb91c == 0) {
            *(undefined1 *)0xb916 = 0;
            FUN_1000_0040();
            FUN_1000_016a(0xb4);
          }
        }
        cVar1 = FUN_1000_06d5(6);
        if ((cVar1 != '\0') &&
           (*(int *)((int)*(undefined4 *)0xabaf + 9) = *(int *)((int)*(undefined4 *)0xabaf + 9) + -1
           , *(int *)((int)*(undefined4 *)0xabaf + 9) == 0)) {
          FUN_1000_7364(&local_9,unaff_SS,0x61);
        }
        cVar1 = FUN_1000_06d5(0x12);
        if (cVar1 != '\0') {
          FUN_1000_0662(0x12);
        }
        cVar1 = FUN_1000_06d5(0x13);
        if (((cVar1 != '\0') && (iVar2 = FUN_214c_1162(200), iVar2 == 0)) && (1 < *(int *)0xb874)) {
          FUN_1000_0662(0x13);
          *(int *)0xb874 = *(int *)0xb874 + -1;
          *(undefined2 *)0xb876 = *(undefined2 *)0xb874;
          FUN_1000_0296();
        }
      }
    }
    if (*(char *)0xb8f0 == '\0') {
      FUN_1000_d26a();
    }
  }
  return;
}



void __cdecl16near FUN_1000_f841(void)

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
  char local_3;
  
  do {
    FUN_20e6_020d();
    FUN_20e6_0260(CONCAT11(extraout_AH,1),CONCAT11(extraout_AH,1));
    FUN_1000_016a(0x149);
    FUN_20e6_0260(CONCAT11(extraout_AH_00,10),CONCAT11(extraout_AH_00,0x1e));
    FUN_1000_016a(0x7c);
    local_5 = 0;
    while( true ) {
      FUN_20e6_0260(local_5 * 2 + 0xf,0x14);
      FUN_1000_016a(local_5 + 0x34);
      if (local_5 == 3) break;
      local_5 = local_5 + 1;
    }
    FUN_20e6_0260(0x17,0x32);
    FUN_1000_016a(0x7d);
    FUN_20e6_0260(CONCAT11(extraout_AH_01,0x17),CONCAT11(extraout_AH_01,0x46));
    uVar1 = FUN_20e6_0357();
    local_3 = (char)uVar1;
    uVar3 = (undefined1)((uint)uVar1 >> 8);
    uVar4 = local_3 == 'e';
    if (((bool)uVar4) || (uVar4 = local_3 == 'E', (bool)uVar4)) {
      FUN_1000_6921();
      uVar3 = extraout_AH_02;
    }
    else {
      uVar4 = local_3 == 's';
      if (((bool)uVar4) || (uVar4 = local_3 == 'S', (bool)uVar4)) {
        FUN_20e6_020d();
        FUN_1000_6c94();
        FUN_1000_6f02();
        FUN_20e6_0260(CONCAT11(extraout_AH_03,0x19),CONCAT11(extraout_AH_03,0x3c));
        FUN_1000_1448();
        uVar3 = extraout_AH_04;
      }
      else {
        uVar4 = local_3 == 'j';
        if (((bool)uVar4) || (uVar4 = local_3 == 'J', (bool)uVar4)) {
          FUN_20e6_020d();
          FUN_1f98_137a();
          FUN_1f98_14b7();
          FUN_1f98_1155();
          FUN_1000_6c94();
          FUN_1000_48b7();
          FUN_20e6_020d();
          FUN_1000_f5f2();
          FUN_1000_1b91();
          uVar3 = extraout_AH_05;
        }
      }
    }
    uVar2 = CONCAT11(uVar3,local_3);
    puVar5 = local_25;
    uVar1 = unaff_SS;
    FUN_214c_08af(puVar5);
    FUN_214c_08be(CONCAT11(extraout_AH_06,0x66));
    FUN_214c_08be(CONCAT11(extraout_AH_07,0x46));
    FUN_214c_0933(puVar5,uVar1,uVar2);
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
  FUN_214c_0000();
  DAT_3000_557e = 0x214c;
  DAT_3000_557c = 0xf956;
  FUN_20e6_0000();
  DAT_3000_557e = 0x20e6;
  DAT_3000_557c = 0xf95d;
  FUN_1f98_0000();
  DAT_3000_557e = 0x1f98;
  DAT_3000_557c = 0xf962;
  FUN_1f98_1107();
  DAT_3000_557e = 0x1f98;
  DAT_3000_557c = 0xf967;
  FUN_1f98_042e();
  DAT_3000_557e = 0x1f98;
  DAT_3000_557c = 0xf96c;
  FUN_214c_11e8();
  DAT_3000_557e = CONCAT11(extraout_AH,0xf);
  DAT_3000_557c = 0x214c;
  DAT_3000_557a = 0xf974;
  FUN_20e6_02a4();
  DAT_3000_557e = 0xf977;
  FUN_1000_f841();
  DAT_3000_557e = 0x20e6;
  DAT_3000_557c = 0xf980;
  FUN_214c_01f3();
  DAT_3000_557e = 0x4000;
  DAT_3000_557c = 0x214c;
  DAT_3000_557a = 0xf98b;
  FUN_214c_02ad();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xf998;
  FUN_214c_08af();
  uRam00035538 = CONCAT11(extraout_AH_00,0xc4);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9a0;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_01,0xc1);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9a8;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_02,0xc2);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9b0;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_03,0xc5);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9b8;
  FUN_214c_08be();
  uRam00035536 = 0xb72f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xf9c6;
  FUN_214c_0913();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xf9d0;
  FUN_214c_08af();
  uRam00035538 = CONCAT11(extraout_AH_04,0xb3);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9d8;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_05,0xc3);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9e0;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_06,0xb4);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9e8;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_07,0xc5);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xf9f0;
  FUN_214c_08be();
  uRam00035536 = 0xb74f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xf9fe;
  FUN_214c_0913();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035536 = 0xb74f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfa11;
  FUN_214c_0885();
  uRam00035538 = 0x3158;
  uRam00035536 = 0x3fbe;
  uRam00035532 = 0xb72f;
  uRam00035530 = 0x20;
  uRam0003552e = 0x214c;
  uRam0003552c = 0xfa24;
  FUN_214c_0885();
  uRam00035534 = 0x214c;
  uRam00035532 = 0xfa29;
  FUN_214c_0954();
  uRam00035536 = 0xb76f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfa37;
  FUN_214c_0913();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xfa41;
  FUN_214c_08af();
  uRam00035538 = CONCAT11(extraout_AH_08,0xda);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa49;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_09,0xbf);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa51;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_10,0xc0);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa59;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_11,0xd9);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa61;
  FUN_214c_08be();
  uRam00035536 = 0xb78f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfa6f;
  FUN_214c_0913();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xfa79;
  FUN_214c_08af();
  uRam00035538 = CONCAT11(extraout_AH_12,0xc2);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa81;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_13,0xc1);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa89;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_14,0xc3);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa91;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_15,0xb4);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfa99;
  FUN_214c_08be();
  uRam00035536 = 0xb7af;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfaa7;
  FUN_214c_0913();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xfab1;
  FUN_214c_08af();
  uRam00035538 = CONCAT11(extraout_AH_16,0x24);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfab9;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_17,0x3a);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfac1;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_18,0xad);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfac9;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_19,0x3d);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfad1;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_20,0x7f);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfad9;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_21,0x3f);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfae1;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_22,0xf8);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfae9;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_23,0x2f);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfaf1;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_24,0xf);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfaf9;
  FUN_214c_08be();
  uRam00035536 = 0xb7cf;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfb07;
  FUN_214c_0913();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xfb11;
  FUN_214c_08af();
  uRam00035538 = CONCAT11(extraout_AH_25,0xea);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb19;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_26,1);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb21;
  FUN_214c_08be();
  uRam00035536 = 0xb82f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfb2f;
  FUN_214c_0913();
  uRam0003553c = 0x3158;
  uRam0003553a = 0x3fde;
  uRam00035538 = 0x214c;
  uRam00035536 = 0xfb39;
  FUN_214c_08af();
  uRam00035538 = CONCAT11(extraout_AH_27,0x53);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb41;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_28,0x41);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb49;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_29,0x52);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb51;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_30,0x4c);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb59;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_31,0x57);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb61;
  FUN_214c_08be();
  uRam00035538 = CONCAT11(extraout_AH_32,0x67);
  uRam00035536 = 0x214c;
  uRam00035534 = 0xfb69;
  FUN_214c_08be();
  uRam00035536 = 0xb80f;
  uRam00035534 = 0x20;
  uRam00035532 = 0x214c;
  uRam00035530 = 0xfb77;
  uRam00035538 = unaff_DS;
  FUN_214c_0913();
  return;
}



void __cdecl16far FUN_1f98_0000(void)

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
  FUN_214c_02ad();
  puVar3 = local_22;
  uVar2 = unaff_SS;
  FUN_214c_08af(puVar3);
  FUN_214c_08be(CONCAT11(extraout_AH,0xc4));
  FUN_214c_08be(CONCAT11(extraout_AH_00,0xc1));
  FUN_214c_08be(CONCAT11(extraout_AH_01,0xc2));
  FUN_214c_08be(CONCAT11(extraout_AH_02,0xc5));
  FUN_214c_0913(0x20,0xb72f,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  uVar2 = unaff_SS;
  FUN_214c_08af(puVar3);
  FUN_214c_08be(CONCAT11(extraout_AH_03,0xb3));
  FUN_214c_08be(CONCAT11(extraout_AH_04,0xc3));
  FUN_214c_08be(CONCAT11(extraout_AH_05,0xb4));
  FUN_214c_08be(CONCAT11(extraout_AH_06,0xc5));
  FUN_214c_0913(0x20,0xb74f,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  uVar4 = unaff_SS;
  FUN_214c_0885(0x20,0xb74f,unaff_DS);
  puVar1 = local_42;
  uVar2 = unaff_SS;
  FUN_214c_0885(0x20,0xb72f,unaff_DS);
  FUN_214c_0954(puVar1,uVar2);
  FUN_214c_0913(0x20,0xb76f,unaff_DS,puVar3,uVar4);
  puVar3 = local_22;
  uVar2 = unaff_SS;
  FUN_214c_08af(puVar3);
  FUN_214c_08be(CONCAT11(extraout_AH_07,0xda));
  FUN_214c_08be(CONCAT11(extraout_AH_08,0xbf));
  FUN_214c_08be(CONCAT11(extraout_AH_09,0xc0));
  FUN_214c_08be(CONCAT11(extraout_AH_10,0xd9));
  FUN_214c_0913(0x20,0xb78f,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  uVar2 = unaff_SS;
  FUN_214c_08af(puVar3);
  FUN_214c_08be(CONCAT11(extraout_AH_11,0xc2));
  FUN_214c_08be(CONCAT11(extraout_AH_12,0xc1));
  FUN_214c_08be(CONCAT11(extraout_AH_13,0xc3));
  FUN_214c_08be(CONCAT11(extraout_AH_14,0xb4));
  FUN_214c_0913(0x20,0xb7af,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  uVar2 = unaff_SS;
  FUN_214c_08af();
  FUN_214c_08be(CONCAT11(extraout_AH_15,0x24));
  FUN_214c_08be(CONCAT11(extraout_AH_16,0x3a));
  FUN_214c_08be(CONCAT11(extraout_AH_17,0xad));
  FUN_214c_08be(CONCAT11(extraout_AH_18,0x3d));
  FUN_214c_08be(CONCAT11(extraout_AH_19,0x7f));
  FUN_214c_08be(CONCAT11(extraout_AH_20,0x3f));
  FUN_214c_08be(CONCAT11(extraout_AH_21,0xf8));
  FUN_214c_08be(CONCAT11(extraout_AH_22,0x2f));
  FUN_214c_08be(CONCAT11(extraout_AH_23,0xf));
  FUN_214c_0913(0x20,0xb7cf,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  uVar2 = unaff_SS;
  FUN_214c_08af();
  FUN_214c_08be(CONCAT11(extraout_AH_24,0xea));
  FUN_214c_08be(CONCAT11(extraout_AH_25,1));
  FUN_214c_0913(0x20,0xb82f,unaff_DS,puVar3,uVar2);
  puVar3 = local_22;
  FUN_214c_08af();
  FUN_214c_08be(CONCAT11(extraout_AH_26,0x53));
  FUN_214c_08be(CONCAT11(extraout_AH_27,0x41));
  FUN_214c_08be(CONCAT11(extraout_AH_28,0x52));
  FUN_214c_08be(CONCAT11(extraout_AH_29,0x4c));
  FUN_214c_08be(CONCAT11(extraout_AH_30,0x57));
  FUN_214c_08be(CONCAT11(extraout_AH_31,0x67));
  FUN_214c_0913(0x20,0xb80f,unaff_DS,puVar3,unaff_SS);
  return;
}



ulong FUN_1f98_01fb(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined2 unaff_SS;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  
  uVar5 = 0x1f;
  FUN_214c_02ad();
  uVar4 = (undefined1)unaff_SS;
  uVar3 = (undefined1)(param_1 + -0x10d);
  uVar1 = FUN_214c_177f(uVar3);
  *(undefined1 *)(param_1 + -0xb) = uVar1;
  FUN_214c_1712(uVar3,uVar4);
  FUN_214c_0277(uVar5);
  if (*(char *)(param_1 + -0xb) == -1) {
    *(undefined1 *)(param_1 + -0xb) = 0x1a;
  }
  iVar2 = ((uint)*(byte *)(param_1 + -0xb) + *(int *)(param_1 + -0x111) + 0xfe) -
          *(int *)(param_1 + -0x10f);
  *(uint *)(param_1 + -0x111) = (uint)*(byte *)(param_1 + -0xb);
  return CONCAT22(iVar2 / 0xfe,iVar2 % 0xfe) & 0xffff00ff;
}



int FUN_1f98_027a(undefined2 param_1)

{
  uint uVar1;
  undefined2 uVar2;
  
  uVar2 = 0x1f98;
  FUN_214c_02ad();
  uVar1 = FUN_1f98_01fb(param_1,uVar2);
  return (uVar1 & 0xff) - 0x28;
}



void FUN_1f98_029f(int param_1,byte *param_2)

{
  undefined2 uVar1;
  uint uVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  byte *pbVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined1 uVar5;
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
  FUN_214c_02ad();
  *param_2 = 0;
  do {
    puVar8 = local_202;
    uVar4 = (undefined2)((ulong)param_2 >> 0x10);
    pbVar3 = (byte *)param_2;
    uVar9 = unaff_SS;
    FUN_214c_0693(pbVar3,uVar4);
    puVar6 = local_102;
    uVar7 = unaff_SS;
    uVar1 = FUN_1f98_01fb(param_1,puVar6);
    FUN_214c_07ae(uVar1);
    FUN_214c_0720(puVar6,uVar7);
    FUN_214c_06ad(0x50,pbVar3,uVar4,puVar8,uVar9);
    uVar5 = pbVar3 + *param_2 == (byte *)0x0;
    uVar2 = (uint)pbVar3[*param_2];
    puVar8 = local_22;
    uVar7 = unaff_SS;
    FUN_214c_08af(puVar8);
    FUN_214c_08be(CONCAT11(extraout_AH,10));
    FUN_214c_08be(CONCAT11(extraout_AH_00,0xd));
    FUN_214c_0933(puVar8,uVar7,uVar2);
  } while ((bool)uVar5);
  FUN_214c_082f(1,*param_2,pbVar3,uVar4);
  uVar5 = FUN_1f98_01fb(param_1);
  *(undefined1 *)(param_1 + -0xb) = uVar5;
  return;
}



void __cdecl16far FUN_1f98_042e(void)

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
  bool bVar8;
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
  int local_a;
  int local_8;
  undefined2 local_6;
  undefined2 local_4;
  
  local_4 = 0x1f98;
  local_6 = 0xfdb9;
  FUN_214c_02ad();
  FUN_214c_1383(0x346,0x214c,local_10f,unaff_SS);
  FUN_214c_13f3(0x214c,local_10f);
  FUN_214c_0277();
  iVar3 = FUN_214c_026d();
  if (iVar3 != 1) {
    FUN_1f98_029f(&stack0xfffe,0xbba5,unaff_DS);
    uVar11 = 0xe654;
    FUN_214c_17f7(0,0xbba5,unaff_DS);
    FUN_214c_173c(0x214c,uVar11);
    FUN_214c_0277();
    local_c = 1;
    while( true ) {
      iVar3 = FUN_214c_0285();
      FUN_1f98_029f(&stack0xfffe,iVar3 * 0x49 + -0x44a4,unaff_DS);
      if (local_c == 0x1f) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = FUN_214c_0285();
      FUN_1f98_029f(&stack0xfffe,iVar3 * 0x33 + -0x3bb7,unaff_DS);
      if (local_c == 0x5a) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = FUN_214c_0285();
      FUN_1f98_029f(&stack0xfffe,iVar3 * 0x1f + -0x29b5,unaff_DS);
      if (local_c == 0x6d) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = FUN_214c_0285();
      FUN_1f98_029f(&stack0xfffe,iVar3 * 0x10 + -0x1c73,unaff_DS);
      if (local_c == 0x19) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      local_a = 1;
      while( true ) {
        FUN_1f98_027a(&stack0xfffe);
        uVar11 = FUN_214c_0285();
        iVar3 = FUN_214c_0285();
        iVar3 = iVar3 << 1;
        iVar4 = FUN_214c_0285();
        *(undefined2 *)(iVar4 * 4 + iVar3 + -18000) = uVar11;
        if (local_a == 2) break;
        local_a = local_a + 1;
      }
      if (local_c == 4) break;
      local_c = local_c + 1;
    }
    FUN_1f98_01fb(&stack0xfffe);
    local_e = FUN_214c_0285();
    FUN_1f98_01fb(&stack0xfffe);
    local_e = FUN_214c_0285();
    local_f = '\x02';
    while( true ) {
      iVar3 = FUN_1f98_027a(&stack0xfffe);
      iVar3 = iVar3 >> 0xf;
      uVar11 = FUN_214c_0285();
      iVar4 = FUN_214c_0285();
      *(undefined2 *)(iVar4 * 4 + 0x79b3) = uVar11;
      *(int *)(iVar4 * 4 + 0x79b5) = iVar3;
      if (local_f == '\b') break;
      local_f = local_f + '\x01';
    }
    local_c = 1;
    while( true ) {
      local_f = '\0';
      while( true ) {
        FUN_1f98_027a(&stack0xfffe);
        uVar11 = FUN_214c_0285();
        iVar3 = FUN_214c_0285();
        iVar3 = iVar3 << 1;
        iVar4 = FUN_214c_0285();
        *(undefined2 *)(iVar4 * 0x30 + iVar3 + 0x79d5) = uVar11;
        if (local_f == '\b') break;
        local_f = local_f + '\x01';
      }
      if (local_c == 3) break;
      local_c = local_c + 1;
    }
    FUN_1f98_01fb(&stack0xfffe);
    local_e = FUN_214c_0285();
    FUN_22de_cd9b(&stack0xfffe);
    local_e = FUN_214c_0285();
    local_c = 1;
    while( true ) {
      iVar3 = FUN_214c_0285();
      FUN_22de_ce3f(&stack0xfffe,iVar3 * 0x10 + -0x5e49);
      if (local_c == 0x18) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = FUN_214c_0285();
      FUN_22de_ce3f(&stack0xfffe,iVar3 * 0x10 + -0x5b49);
      if (local_c == 0x13) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = FUN_214c_0285();
      FUN_22de_ce3f(&stack0xfffe,iVar3 * 0x10 + -0x58e9);
      if (local_c == 0x16) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = FUN_214c_0285();
      FUN_22de_ce3f(&stack0xfffe,iVar3 * 0x10 + -0x5629);
      if (local_c == 10) break;
      local_c = local_c + 1;
    }
    local_c = 1;
    while( true ) {
      iVar3 = FUN_214c_0285();
      *(undefined1 *)(iVar3 * 4 + -0x469e) = 0;
      local_a = 1;
      while( true ) {
        puVar10 = local_313;
        uVar6 = unaff_SS;
        iVar3 = FUN_214c_0285(puVar10);
        FUN_214c_0693(iVar3 * 4 + -0x469e,unaff_DS);
        puVar9 = local_213;
        uVar11 = unaff_SS;
        uVar5 = FUN_22de_cd9b(&stack0xfffe,puVar9);
        FUN_214c_07ae(uVar5);
        FUN_214c_0720(puVar9,uVar11);
        iVar3 = FUN_214c_0285();
        FUN_214c_06ad(3,iVar3 * 4 + -0x469e,unaff_DS,puVar10,uVar6);
        if (local_a == 3) break;
        local_a = local_a + 1;
      }
      if (local_c == 0x14) break;
      local_c = local_c + 1;
    }
    FUN_22de_cd9b(&stack0xfffe);
    local_e = FUN_214c_0285();
    FUN_22de_cd9b(&stack0xfffe);
    local_e = FUN_214c_0285();
    local_c = 1;
    while( true ) {
      iVar3 = FUN_214c_0285();
      _local_117 = CONCAT22(unaff_DS,iVar3 * 0x2a + -0x5017);
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x15) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x17) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x13) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x19) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x1b) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x11) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x1f) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x1d) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x21) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x23) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      uVar11 = FUN_214c_0285();
      *(undefined2 *)((int)_local_117 + 0x25) = uVar11;
      FUN_22de_ce1a(&stack0xfffe);
      local_8 = FUN_214c_0285();
      uVar11 = (undefined2)((ulong)_local_117 >> 0x10);
      if (local_8 == 0) {
        *(undefined1 *)((int)_local_117 + 0x27) = 0;
      }
      else {
        *(undefined1 *)((int)_local_117 + 0x27) = 1;
      }
      FUN_22de_ce1a(&stack0xfffe);
      local_8 = FUN_214c_0285();
      uVar11 = (undefined2)((ulong)_local_117 >> 0x10);
      if (local_8 == 0) {
        *(undefined1 *)((int)_local_117 + 0x28) = 0;
      }
      else {
        *(undefined1 *)((int)_local_117 + 0x28) = 1;
      }
      FUN_22de_ce1a(&stack0xfffe);
      local_8 = FUN_214c_0285();
      uVar11 = (undefined2)((ulong)_local_117 >> 0x10);
      if (local_8 == 0) {
        *(undefined1 *)((int)_local_117 + 0x29) = 0;
      }
      else {
        *(undefined1 *)((int)_local_117 + 0x29) = 1;
      }
      local_a = 0;
      while( true ) {
        FUN_22de_ce1a(&stack0xfffe);
        uVar11 = FUN_214c_0285();
        iVar3 = FUN_214c_0285();
        iVar3 = iVar3 << 1;
        iVar4 = FUN_214c_0285();
        *(undefined2 *)(iVar4 * 0x20 + iVar3 + -0x546d) = uVar11;
        if (local_a == 0xf) break;
        local_a = local_a + 1;
      }
      FUN_22de_cd9b(&stack0xfffe);
      uVar2 = FUN_214c_0285();
      iVar3 = FUN_214c_0285();
      *(undefined1 *)(iVar3 * 0x2a + -0x5007) = uVar2;
      iVar3 = FUN_214c_0285();
      FUN_22de_ce3f(&stack0xfffe,iVar3 * 0x2a + -0x5017);
      FUN_214c_0285();
      uVar2 = 1;
      uVar6 = FUN_214c_0285();
      puVar10 = local_133;
      uVar11 = unaff_SS;
      FUN_214c_08af(puVar10);
      FUN_214c_08be(CONCAT11(extraout_AH,0x41));
      FUN_214c_08be(CONCAT11(extraout_AH_00,0x43));
      FUN_214c_08be(CONCAT11(extraout_AH_01,0x46));
      FUN_214c_08be(CONCAT11(extraout_AH_02,0x73));
      FUN_214c_0933(puVar10,uVar11,uVar6);
      if ((bool)uVar2) {
        uVar6 = 0x214c;
        uVar11 = 0x40e;
        iVar3 = FUN_214c_0285(0x40e,0x214c);
        FUN_214c_06ad(4,iVar3 * 5 + -0x4985,unaff_DS,uVar11,uVar6);
      }
      else {
        uVar6 = 0x214c;
        uVar11 = 0x409;
        iVar3 = FUN_214c_0285(0x409,0x214c);
        FUN_214c_06ad(4,iVar3 * 5 + -0x4985,unaff_DS,uVar11,uVar6);
      }
      FUN_214c_0285();
      uVar2 = 1;
      uVar6 = FUN_214c_0285();
      puVar10 = local_133;
      uVar11 = unaff_SS;
      FUN_214c_08af(puVar10);
      FUN_214c_08be(CONCAT11(extraout_AH_03,0x41));
      FUN_214c_08be(CONCAT11(extraout_AH_04,0x45));
      FUN_214c_08be(CONCAT11(extraout_AH_05,0x4f));
      FUN_214c_08be(CONCAT11(extraout_AH_06,0x55));
      FUN_214c_08be(CONCAT11(extraout_AH_07,0x61));
      FUN_214c_08be(CONCAT11(extraout_AH_08,0x9e));
      FUN_214c_0933(puVar10,uVar11,uVar6);
      if ((bool)uVar2) {
        FUN_214c_0285();
        uVar2 = 1;
        uVar6 = FUN_214c_0285();
        puVar10 = local_153;
        uVar11 = unaff_SS;
        FUN_214c_08af(puVar10);
        FUN_214c_08be(CONCAT11(extraout_AH_09,0x43));
        FUN_214c_08be(CONCAT11(extraout_AH_10,0x46));
        FUN_214c_08be(CONCAT11(extraout_AH_11,0x73));
        FUN_214c_0933(puVar10,uVar11,uVar6);
        if ((bool)uVar2) {
          uVar6 = 0x214c;
          uVar11 = 0x41a;
          iVar3 = FUN_214c_0285(0x41a,0x214c);
          FUN_214c_06ad(4,iVar3 * 5 + -0x4a34,unaff_DS,uVar11,uVar6);
        }
        else {
          uVar6 = 0x214c;
          uVar11 = 0x416;
          iVar3 = FUN_214c_0285(0x416,0x214c);
          FUN_214c_06ad(4,iVar3 * 5 + -0x4a34,unaff_DS,uVar11,uVar6);
        }
      }
      else {
        uVar6 = 0x214c;
        uVar11 = 0x412;
        iVar3 = FUN_214c_0285(0x412,0x214c);
        FUN_214c_06ad(4,iVar3 * 5 + -0x4a34,unaff_DS,uVar11,uVar6);
      }
      iVar3 = FUN_214c_0285();
      uVar2 = *(char *)(iVar3 * 0x2a + -0x5007) == 'a';
      if ((bool)uVar2) {
        uVar6 = 0x214c;
        uVar11 = 0x412;
        iVar3 = FUN_214c_0285(0x412,0x214c);
        iVar3 = iVar3 * 5 + -0x4985;
        uVar2 = iVar3 == 0;
        FUN_214c_06ad(4,iVar3,unaff_DS,uVar11,uVar6);
      }
      uVar6 = FUN_214c_0285();
      puVar10 = local_133;
      uVar11 = unaff_SS;
      FUN_214c_08af(puVar10);
      FUN_214c_08df(CONCAT11(extraout_AH_12,0x23),CONCAT11(extraout_AH_12,0x1d));
      FUN_214c_0933(puVar10,uVar11,uVar6);
      if (!(bool)uVar2) {
        iVar3 = FUN_214c_0285();
        *(undefined1 *)(iVar3 * 5 + -0x4a34) = 0;
        iVar3 = FUN_214c_0285();
        *(undefined1 *)(iVar3 * 5 + -0x4985) = 0;
      }
      if (local_c == 0x23) break;
      local_c = local_c + 1;
    }
    local_f = '\x02';
    while( true ) {
      FUN_214c_0285();
      iVar3 = FUN_214c_0285();
      _local_117 = CONCAT22(iVar3,local_117);
      if (0 < iVar3) {
        local_c = 1;
        while( true ) {
          iVar3 = FUN_214c_0285();
          iVar3 = iVar3 * 0x1d;
          iVar4 = FUN_214c_0285();
          FUN_22de_ce3f(&stack0xfffe,iVar4 * 0x2b8 + iVar3 + 0x75fa);
          uVar1 = _local_117;
          iVar7 = (int)((ulong)_local_117 >> 0x10);
          bVar8 = local_c == iVar7;
          _local_117 = uVar1;
          if (bVar8) break;
          local_c = local_c + 1;
        }
      }
      if (local_f == '\b') break;
      local_f = local_f + '\x01';
    }
    local_f = '\x02';
    while( true ) {
      FUN_214c_0285();
      iVar3 = FUN_214c_0285();
      _local_117 = CONCAT22(iVar3,local_117);
      if (0 < iVar3) {
        local_c = 1;
        while( true ) {
          FUN_22de_ce1a(&stack0xfffe);
          uVar11 = FUN_214c_0285();
          iVar3 = FUN_214c_0285();
          iVar3 = iVar3 << 1;
          iVar4 = FUN_214c_0285();
          uVar1 = _local_117;
          *(undefined2 *)(iVar4 * 0x30 + iVar3 + -0x6513) = uVar11;
          iVar7 = (int)((ulong)_local_117 >> 0x10);
          bVar8 = local_c == iVar7;
          _local_117 = uVar1;
          if (bVar8) break;
          local_c = local_c + 1;
        }
      }
      if (local_f == '\b') break;
      local_f = local_f + '\x01';
    }
    FUN_22de_cd9b(&stack0xfffe);
    local_e = FUN_214c_0285();
    FUN_22de_cd9b(&stack0xfffe);
    local_e = FUN_214c_0285();
    iVar3 = FUN_214c_0285();
    if (0 < iVar3) {
      local_c = 1;
      while( true ) {
        FUN_22de_ce1a(&stack0xfffe);
        uVar11 = FUN_214c_0285();
        iVar7 = FUN_214c_0285();
        *(undefined2 *)(iVar7 * 4 + -0x6305) = uVar11;
        if (local_c == iVar3) break;
        local_c = local_c + 1;
      }
    }
    local_f = '\x05';
    while( true ) {
      FUN_214c_0285();
      iVar3 = FUN_214c_0285();
      if (0 < iVar3) {
        local_c = 1;
        while( true ) {
          FUN_22de_ce1a(&stack0xfffe);
          uVar11 = FUN_214c_0285();
          iVar7 = FUN_214c_0285();
          iVar7 = iVar7 << 2;
          iVar4 = FUN_214c_0285();
          *(undefined2 *)(iVar4 * 0x60 + iVar7 + -0x6425) = uVar11;
          if (local_c == iVar3) break;
          local_c = local_c + 1;
        }
      }
      if (local_f == '\a') break;
      local_f = local_f + '\x01';
    }
    iVar3 = FUN_214c_0285();
    if (0 < iVar3) {
      local_c = 1;
      while( true ) {
        FUN_22de_ce1a(&stack0xfffe);
        uVar11 = FUN_214c_0285();
        iVar7 = FUN_214c_0285();
        *(undefined2 *)(iVar7 * 4 + -0x6243) = uVar11;
        if (local_c == iVar3) break;
        local_c = local_c + 1;
      }
    }
    iVar3 = FUN_214c_0285();
    if (0 < iVar3) {
      local_c = 1;
      while( true ) {
        FUN_22de_ce1a(&stack0xfffe);
        uVar11 = FUN_214c_0285();
        iVar7 = FUN_214c_0285();
        *(undefined2 *)(iVar7 * 2 + -0x6123) = uVar11;
        if (local_c == iVar3) break;
        local_c = local_c + 1;
      }
    }
    FUN_22de_cd9b(&stack0xfffe);
    local_e = FUN_214c_0285();
    FUN_22de_cd9b(&stack0xfffe);
    local_e = FUN_214c_0285();
    local_f = '\x06';
    while( true ) {
      FUN_214c_0285();
      iVar3 = FUN_214c_0285();
      if (0 < iVar3) {
        local_c = 1;
        while( true ) {
          FUN_22de_ce1a(&stack0xfffe);
          uVar11 = FUN_214c_0285();
          iVar7 = FUN_214c_0285();
          iVar7 = iVar7 << 1;
          iVar4 = FUN_214c_0285();
          *(undefined2 *)(iVar4 * 0x30 + iVar7 + -0x71d3) = uVar11;
          FUN_22de_ce1a(&stack0xfffe);
          FUN_214c_0285();
          FUN_214c_0285();
          uVar11 = FUN_214c_0285();
          iVar7 = FUN_214c_0285();
          iVar7 = iVar7 << 1;
          iVar4 = FUN_214c_0285();
          *(undefined2 *)(iVar4 * 0x30 + iVar7 + -0x71d3) = uVar11;
          if (local_c == iVar3) break;
          local_c = local_c + 1;
        }
      }
      FUN_22de_cd9b(&stack0xfffe);
      local_e = FUN_214c_0285();
      FUN_22de_cd9b(&stack0xfffe);
      local_e = FUN_214c_0285();
      if (local_f == '\a') break;
      local_f = local_f + '\x01';
    }
    *(undefined2 *)0xb948 = 0;
    local_c = 1;
    while( true ) {
      FUN_22de_ce1a(&stack0xfffe);
      local_6 = FUN_214c_0285();
      FUN_22de_ce1a(&stack0xfffe);
      local_4 = FUN_214c_0285();
      uVar11 = FUN_214c_0285();
      iVar3 = FUN_214c_0285();
      *(undefined2 *)(iVar3 * 2 + -0x46b8) = uVar11;
      if (local_c == 0xe) break;
      local_c = local_c + 1;
    }
    return;
  }
  uVar11 = 0xe654;
  FUN_214c_17f7(0,0x351,0x214c);
  FUN_214c_1755(uVar11,unaff_DS);
  FUN_214c_0277();
  return;
}



void __cdecl16far FUN_1f98_1107(void)

{
  undefined2 unaff_DS;
  
  FUN_214c_02ad();
  FUN_214c_06ad(0xb,0xb9c6,unaff_DS,0x10f0,0x214c);
  FUN_214c_06ad(9,0xb9ed,unaff_DS,0x10fc,0x214c);
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
  int iVar2;
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
  FUN_214c_02ad();
  *(undefined2 *)0xe52d = 1;
  local_6 = 1;
  while( true ) {
    local_76f[local_6 * 0x9e + 1] = 0xb3;
    local_71f[local_6 * 0x9e + -1] = 0xb3;
    local_76f[(local_6 * 2 + 1) * 0x4f + 1] = 0xc3;
    local_71f[(local_6 * 2 + 1) * 0x4f + -1] = 0xb4;
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
    for (local_4 = 1; local_76f[(local_6 * 2 + 1) * 0x4f + local_4 * 2 + 1] = 0xc5, local_4 != 0x26;
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
    FUN_214c_038e();
    uVar1 = *(undefined4 *)(local_6 * 4 + 4);
    uVar3 = (undefined2)((ulong)uVar1 >> 0x10);
    iVar2 = (int)uVar1;
    *(undefined2 *)(iVar2 + 0x723) = 0;
    *(undefined2 *)(iVar2 + 0x725) = 0;
    puStack_723 = local_71f;
    uVar1 = *(undefined4 *)(local_6 * 4 + 4);
    uStack_725 = (undefined2)((ulong)uVar1 >> 0x10);
    uStack_727 = (undefined2)uVar1;
    uStack_729 = 0x719;
    uStack_72b = 0x214c;
    uStack_72d = 0xc6d;
    FUN_214c_02c0();
    uVar1 = *(undefined4 *)(local_6 * 4 + 4);
    *(undefined1 *)((int)uVar1 + 0x719) = 0;
    uVar1 = *(undefined4 *)(local_6 * 4 + 4);
    *(undefined1 *)((int)uVar1 + 0x71a) = 0;
    if (local_6 == 0xf) break;
    local_6 = local_6 + 1;
  }
  local_6 = 1;
  while( true ) {
    for (local_4 = 1; *(undefined1 *)(local_6 * 0x4f + local_4 + -0xc) = 0x20, local_4 != 0x4f;
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
  int iVar1;
  undefined2 unaff_DS;
  undefined1 local_a;
  undefined2 local_8;
  undefined2 local_6;
  undefined2 local_4;
  
  FUN_214c_02ad();
  local_a = '\x02';
  while( true ) {
    iVar1 = *(int *)(local_a * 4 + 0x79b3);
    if (0 < iVar1) {
      local_8 = 1;
      while( true ) {
        *(undefined1 *)(local_a * 0x18 + local_8 + -0x65a2) = 0;
        *(undefined1 *)(local_a * 0x18 + local_8 + -0x6542) = 0;
        FUN_214c_06ad(0x1c,local_a * 0x2b8 + local_8 * 0x1d + -0x75de,unaff_DS,0x1375,0x214c);
        if (local_8 == iVar1) break;
        local_8 = local_8 + 1;
      }
    }
    if (local_a == '\x05') break;
    local_a = local_a + '\x01';
  }
  local_4 = 0;
  while( true ) {
    *(undefined2 *)(local_4 * 4 + -0x5499) = 0;
    *(undefined2 *)(local_4 * 4 + -0x5497) = 0;
    *(undefined2 *)(local_4 * 4 + -0x54d9) = 0;
    *(undefined2 *)(local_4 * 4 + -0x54d7) = 0;
    *(undefined1 *)(local_4 + 0x796d) = 0;
    local_8 = 1;
    while( true ) {
      for (local_6 = 1; *(undefined1 *)(local_4 * 0x719 + local_8 * 0x4f + local_6 + 0x70d) = 0,
          local_6 != 0x4f; local_6 = local_6 + 1) {
      }
      if (local_8 == 0x17) break;
      local_8 = local_8 + 1;
    }
    if (local_4 == 0xf) break;
    local_4 = local_4 + 1;
  }
  for (local_8 = 1; *(undefined2 *)(local_8 * 2 + -0x460b) = 0, local_8 != 0x23;
      local_8 = local_8 + 1) {
  }
  return;
}



void __cdecl16far FUN_1f98_14b7(void)

{
  undefined2 unaff_DS;
  
  FUN_214c_02ad();
  *(undefined2 *)0xe52d = 1;
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
  FUN_20e6_0379(0xe554,unaff_DS);
  FUN_214c_13f3(0x20e6,0xe554);
  FUN_20e6_0379(0xe654,unaff_DS);
  FUN_214c_13f8(0x214c,0xe654);
  return;
}



// WARNING: Removing unreachable block (ram,0x00020ed4)

void __cdecl16near FUN_20e6_002e(void)

{
  byte bVar1;
  byte extraout_AH;
  undefined2 unaff_DS;
  
  bVar1 = FUN_20e6_0653();
  if ((bVar1 != 7) && (3 < bVar1)) {
    FUN_20e6_00b9();
  }
  FUN_20e6_011b();
  FUN_20e6_0653();
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
  FUN_20e6_0653();
  if ((char)((uint)in_AX >> 8) != '\0') {
    FUN_20e6_0653();
    FUN_20e6_0653();
    if (extraout_DL == '*') {
      DAT_0000_0487 = DAT_0000_0487 | 1;
      FUN_20e6_0653();
      if (DAT_0000_0449 == '\a') {
        out(_DAT_0000_0463,0x14);
        out(_DAT_0000_0463 + 1,7);
      }
      FUN_20e6_0653();
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
  
  uVar1 = FUN_20e6_0653();
  FUN_20e6_0653();
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
  FUN_20e6_04c6();
  FUN_20e6_04c6();
  FUN_20e6_04bf();
  pcVar1 = (code *)swi(0x23);
  (*pcVar1)();
  FUN_20e6_00b9();
  FUN_20e6_011b();
  *(undefined1 *)0xe540 = *(undefined1 *)0xe551;
  return;
}



void __cdecl16far FUN_20e6_020d(void)

{
  FUN_20e6_0653();
  thunk_FUN_20e6_0653();
  return;
}



void __cdecl16far FUN_20e6_0227(void)

{
  thunk_FUN_20e6_0653();
  FUN_20e6_0653();
  return;
}



void __stdcall16far FUN_20e6_0260(char param_1,char param_2)

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



char __cdecl16far FUN_20e6_028c(void)

{
  char extraout_DL;
  undefined2 unaff_DS;
  
  thunk_FUN_20e6_0653();
  return (extraout_DL - *(char *)0xe541) + '\x01';
}



char __cdecl16far FUN_20e6_0298(void)

{
  char extraout_DH;
  undefined2 unaff_DS;
  
  thunk_FUN_20e6_0653();
  return (extraout_DH - *(char *)0xe542) + '\x01';
}



void __stdcall16far FUN_20e6_02a4(byte param_1)

{
  undefined2 unaff_DS;
  
  if ((param_1 & 0xf0) != 0) {
    param_1 = param_1 & 0xf | 0x80;
  }
  *(byte *)0xe540 = *(byte *)0xe540 & 0x70;
  *(byte *)0xe540 = *(byte *)0xe540 | param_1;
  return;
}



void __stdcall16far FUN_20e6_02be(byte param_1)

{
  undefined2 unaff_DS;
  
  *(byte *)0xe540 = *(byte *)0xe540 & 0x8f;
  *(byte *)0xe540 = *(byte *)0xe540 | (param_1 & 7) << 4;
  return;
}



void __stdcall16far FUN_20e6_02e9(int param_1)

{
  int extraout_DX;
  
  if (param_1 != 0) {
    do {
      FUN_20e6_0309();
    } while (extraout_DX != 1);
  }
  return;
}



void __cdecl16near FUN_20e6_0309(void)

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



undefined2 __stdcall16far FUN_20e6_0311(uint param_1)

{
  byte bVar1;
  undefined2 uVar2;
  undefined1 uVar3;
  
  uVar2 = 0x34dd;
  if (0x12 < param_1) {
    uVar3 = (undefined1)(0x1234dd / (ulong)param_1 >> 8);
    bVar1 = in(0x61);
    if ((bVar1 & 3) == 0) {
      out(0x61,bVar1 | 3);
      out(0x43,0xb6);
    }
    out(0x42,(char)(0x1234dd / (ulong)param_1));
    uVar2 = CONCAT11(uVar3,uVar3);
    out(0x42,uVar3);
  }
  return uVar2;
}



byte __cdecl16far FUN_20e6_033e(void)

{
  byte bVar1;
  
  bVar1 = in(0x61);
  out(0x61,bVar1 & 0xfc);
  return bVar1 & 0xfc;
}



void __cdecl16far FUN_20e6_0357(void)

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



void __stdcall16far FUN_20e6_0379(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  *(undefined2 *)(iVar1 + 2) = 0xd7b0;
  *(undefined2 *)(iVar1 + 4) = 0x80;
  *(int *)(iVar1 + 0xc) = iVar1 + 0x80;
  *(undefined2 *)(iVar1 + 0xe) = uVar2;
  *(undefined2 *)(iVar1 + 0x10) = 0x3a4;
  *(undefined2 *)(iVar1 + 0x12) = 0x20e6;
  *(undefined1 *)(iVar1 + 0x30) = 0;
  return;
}



void __stdcall16far FUN_20e6_03dc(undefined4 param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint extraout_DX;
  uint extraout_DX_00;
  uint extraout_DX_01;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 unaff_DS;
  
  uVar8 = (undefined2)((ulong)param_1 >> 0x10);
  iVar6 = (int)param_1;
  uVar3 = *(int *)(iVar6 + 4) - 2;
  uVar9 = (undefined2)((ulong)*(undefined4 *)(iVar6 + 0xc) >> 0x10);
  iVar7 = (int)*(undefined4 *)(iVar6 + 0xc);
  uVar4 = 0;
  uVar5 = *(uint *)(iVar6 + 8);
LAB_20e6_03f2:
  do {
    *(undefined1 *)0xe552 = 0;
    bVar1 = FUN_20e6_0357();
    iVar2 = 1;
    if ((bVar1 == 8) || (bVar1 == 0x13)) {
LAB_20e6_0436:
      do {
        if (uVar4 == 0) break;
        FUN_20e6_04c6();
        FUN_20e6_04c6();
        FUN_20e6_04c6();
        uVar4 = uVar4 - 1;
        iVar2 = iVar2 + -1;
        uVar3 = extraout_DX_00;
      } while (iVar2 != 0);
      goto LAB_20e6_03f2;
    }
    if (bVar1 == 4) {
LAB_20e6_044e:
      do {
        if ((uVar4 == uVar5) || (*(byte *)(uVar4 + iVar7) < 0x20)) break;
        FUN_20e6_04c6();
        uVar4 = uVar4 + 1;
        iVar2 = iVar2 + -1;
        uVar3 = extraout_DX_01;
      } while (iVar2 != 0);
    }
    else {
      iVar2 = 0;
      if ((bVar1 == 0x1b) || (bVar1 == 1)) goto LAB_20e6_0436;
      if (bVar1 == 6) goto LAB_20e6_044e;
      if (bVar1 == 0x1a) {
        if (*(char *)0xe53b != '\0') {
          *(undefined1 *)(uVar4 + iVar7) = 0x1a;
          iVar7 = uVar4 + 1;
LAB_20e6_0478:
          *(undefined2 *)(iVar6 + 8) = 0;
          *(int *)(iVar6 + 10) = iVar7;
          return;
        }
      }
      else {
        if (bVar1 == 0xd) {
          FUN_20e6_04bf();
          *(undefined2 *)(uVar4 + iVar7) = 0xa0d;
          iVar7 = uVar4 + 2;
          goto LAB_20e6_0478;
        }
        if ((0x1f < bVar1) && (uVar4 != uVar3)) {
          *(byte *)(uVar4 + iVar7) = bVar1;
          uVar4 = uVar4 + 1;
          FUN_20e6_04c6();
          uVar3 = extraout_DX;
          if (uVar5 < uVar4) {
            uVar5 = uVar4;
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

void FUN_20e6_04bf(void)

{
  FUN_20e6_04c6();
  thunk_FUN_20e6_0653();
  FUN_20e6_051f();
  thunk_FUN_20e6_0653();
  return;
}



void __cdecl16near FUN_20e6_04c6(void)

{
  char in_AL;
  char extraout_DL;
  undefined2 unaff_DS;
  
  thunk_FUN_20e6_0653();
  if (in_AL == '\a') {
    FUN_20e6_0653();
  }
  else if (((in_AL != '\b') && (in_AL != '\r')) &&
          ((in_AL == '\n' || (FUN_20e6_0653(), *(byte *)0xe543 < (byte)(extraout_DL + 1U))))) {
    FUN_20e6_051f();
  }
  thunk_FUN_20e6_0653();
  return;
}



void __cdecl16near FUN_20e6_051f(void)

{
  undefined2 in_DX;
  undefined2 unaff_DS;
  
  if (*(byte *)0xe544 < (byte)((char)((uint)in_DX >> 8) + 1U)) {
    FUN_20e6_0653();
  }
  return;
}



void __cdecl16near thunk_FUN_20e6_0653(void)

{
  FUN_20e6_0653();
  return;
}



void __cdecl16near thunk_FUN_20e6_0653(void)

{
  FUN_20e6_0653();
  return;
}



void __cdecl16near FUN_20e6_0653(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}



void __cdecl16far FUN_214c_0000(void)

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
  FUN_214c_1383();
  in_stack_0000001a = 0x214c;
  in_stack_00000018 = 0x1587;
  FUN_214c_13f3();
  in_stack_0000001a = uVar2;
  in_stack_00000018 = 0xe654;
  in_stack_00000016 = uVar2;
  in_stack_00000014 = 0xe654;
  in_stack_00000012 = 0x214c;
  FUN_214c_1383();
  in_stack_00000016 = 0x214c;
  in_stack_00000014 = 0x159b;
  FUN_214c_13f8();
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined2 __cdecl16far FUN_214c_01ec(void)

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

undefined2 __cdecl16far FUN_214c_01f3(void)

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



undefined2 __cdecl16far FUN_214c_026d(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined2 *)0xe78b;
  *(undefined2 *)0xe78b = 0;
  return uVar1;
}



void __cdecl16far FUN_214c_0277(void)

{
  undefined2 unaff_DS;
  
  if (*(int *)0xe78b == 0) {
    return;
  }
  FUN_214c_01ec();
  return;
}



void __cdecl16far FUN_214c_0285(void)

{
  uint in_AX;
  int in_DX;
  uint *unaff_DI;
  undefined2 in_stack_00000002;
  
  if ((((int)unaff_DI[1] < in_DX) || (((int)unaff_DI[1] <= in_DX && (*unaff_DI <= in_AX)))) &&
     ((in_DX < (int)unaff_DI[3] || ((in_DX <= (int)unaff_DI[3] && (in_AX <= unaff_DI[2])))))) {
    return;
  }
  FUN_214c_01ec();
  return;
}



void __cdecl16far FUN_214c_02ad(void)

{
  undefined1 *in_AX;
  
  if ((in_AX <= &stack0x0000) && (0x1ff < (uint)((int)&stack0x0000 - (int)in_AX))) {
    return;
  }
  FUN_214c_01ec();
  return;
}



void __stdcall16far FUN_214c_02c0(int param_1,undefined1 *param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  puVar3 = (undefined1 *)param_3;
  puVar4 = (undefined1 *)param_2;
  for (; param_1 != 0; param_1 = param_1 + -1) {
    puVar2 = puVar4;
    puVar4 = puVar4 + 1;
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar2 = *puVar1;
  }
  return;
}



int __cdecl16far FUN_214c_02dc(void)

{
  int in_AX;
  int in_CX;
  
  return in_AX * in_CX;
}



uint __cdecl16far FUN_214c_02f7(void)

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
    uVar2 = FUN_214c_01ec();
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



void __stdcall16far FUN_214c_038e(undefined2 param_1,undefined2 *param_2)

{
  int iVar1;
  undefined2 in_CX;
  undefined2 in_BX;
  undefined2 unaff_DS;
  undefined1 in_CF;
  
  do {
    FUN_214c_04a2();
    if (!(bool)in_CF) goto LAB_214c_03ab;
    iVar1 = (*(code *)*(undefined2 *)0xe764)(0x214c,param_1);
    in_CF = 0;
    if (iVar1 == 0) {
      FUN_214c_01ec();
      return;
    }
  } while (iVar1 != 1);
  in_CX = 0;
  in_BX = 0;
LAB_214c_03ab:
  *param_2 = in_CX;
  ((undefined2 *)param_2)[1] = in_BX;
  return;
}



// WARNING: Removing unreachable block (ram,0x000219ce)
// WARNING: Removing unreachable block (ram,0x00021999)

void __cdecl16near FUN_214c_04a2(void)

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
  
  uVar7 = FUN_214c_0674();
  uVar1 = (uint)(uVar7 >> 0x10);
  uVar6 = (undefined2)((ulong)*(undefined4 *)0xe75e >> 0x10);
  puVar5 = (uint *)(uint *)*(undefined4 *)0xe75e;
  do {
    if (puVar5 == (uint *)0x0) {
      uVar7 = FUN_214c_062a();
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
          FUN_214c_0615();
        }
        return;
      }
    }
    puVar5 = puVar5 + 4;
  } while( true );
}



void __cdecl16near FUN_214c_0615(void)

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



void __cdecl16near FUN_214c_062a(void)

{
  undefined2 unaff_DS;
  
  if ((*(int *)0xe75e == 0) && (*(int *)0xe762 == 0)) {
    return;
  }
  return;
}



ulong __cdecl16near FUN_214c_0674(void)

{
  uint in_AX;
  
  return CONCAT22(in_AX >> 4,in_AX) & 0xffff000f;
}



void __stdcall16far FUN_214c_0693(byte *param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar4 = (byte *)param_2;
  pbVar3 = (byte *)param_1;
  bVar1 = *param_1;
  *param_2 = bVar1;
  uVar2 = (uint)bVar1;
  while( true ) {
    pbVar4 = pbVar4 + 1;
    pbVar3 = pbVar3 + 1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    *pbVar4 = *pbVar3;
  }
  return;
}



void __stdcall16far FUN_214c_06ad(byte param_1,byte *param_2,byte *param_3)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar3 = (byte *)param_3;
  pbVar4 = (byte *)param_2;
  bVar1 = *param_3;
  if (param_1 < *param_3) {
    bVar1 = param_1;
  }
  *param_2 = bVar1;
  uVar2 = (uint)bVar1;
  while( true ) {
    pbVar4 = pbVar4 + 1;
    pbVar3 = pbVar3 + 1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    *pbVar4 = *pbVar3;
  }
  return;
}



void __stdcall16far FUN_214c_06df(uint param_1,uint param_2,byte *param_3,byte *param_4)

{
  byte *pbVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar4 = (byte *)param_4;
  if ((int)param_2 < 1) {
    param_2 = 1;
  }
  pbVar3 = (byte *)param_3 + param_2;
  if (*param_3 < param_2) {
    uVar2 = 0;
  }
  else {
    uVar2 = (*param_3 - param_2) + 1;
    if ((int)param_1 < 0) {
      param_1 = 0;
    }
    if (param_1 < uVar2) {
      uVar2 = param_1;
    }
  }
  *param_4 = (byte)uVar2;
  for (; pbVar4 = pbVar4 + 1, uVar2 != 0; uVar2 = uVar2 - 1) {
    pbVar1 = pbVar3;
    pbVar3 = pbVar3 + 1;
    *pbVar4 = *pbVar1;
  }
  return;
}



void __stdcall16far FUN_214c_0720(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar5 = (byte *)param_1;
  bVar2 = *param_2;
  bVar3 = *param_1;
  bVar1 = *param_2;
  *param_2 = *param_2 + bVar3;
  if (CARRY1(bVar1,bVar3)) {
    *param_2 = 0xff;
    bVar3 = ~bVar2;
  }
  pbVar6 = (byte *)param_2 + bVar2;
  uVar4 = (uint)bVar3;
  while( true ) {
    pbVar6 = pbVar6 + 1;
    pbVar5 = pbVar5 + 1;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    *pbVar6 = *pbVar5;
  }
  return;
}



int __stdcall16far FUN_214c_074c(byte *param_1,byte *param_2)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool bVar9;
  
  pbVar7 = (byte *)param_1;
  uVar3 = (uint)*param_2;
  if (uVar3 <= *param_1) {
    iVar2 = 1;
    if (uVar3 == 0) {
      return 1;
    }
    iVar5 = (*param_1 - uVar3) + 1;
    do {
      pbVar7 = pbVar7 + 1;
      bVar9 = pbVar7 == (byte *)0x0;
      uVar4 = uVar3;
      pbVar8 = pbVar7;
      pbVar6 = (byte *)param_2;
      do {
        pbVar6 = pbVar6 + 1;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pbVar1 = pbVar8;
        pbVar8 = pbVar8 + 1;
        bVar9 = *pbVar6 == *pbVar1;
      } while (bVar9);
      if (bVar9) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  return 0;
}



void __stdcall16far FUN_214c_0783(byte *param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar3 = (byte *)param_2;
  pbVar4 = (byte *)param_1;
  bVar1 = *param_2;
  if (*param_1 < *param_2) {
    bVar1 = *param_1;
  }
  if (bVar1 != 0) {
    uVar2 = (uint)bVar1;
    do {
      pbVar4 = pbVar4 + 1;
      pbVar3 = pbVar3 + 1;
      if (uVar2 == 0) {
        return;
      }
      uVar2 = uVar2 - 1;
    } while (*pbVar3 == *pbVar4);
  }
  return;
}



void __stdcall16far FUN_214c_07ae(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = 1;
  ((undefined1 *)param_2)[1] = param_1;
  return;
}



void __stdcall16far
FUN_214c_07db(int param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

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
  uVar2 = (undefined2)((ulong)param_3 >> 0x10);
  uVar1 = (undefined2)param_3;
  uVar5 = unaff_SS;
  FUN_214c_06df(param_1 + -1,1,uVar1,uVar2);
  FUN_214c_0720((int)param_4,(int)((ulong)param_4 >> 0x10));
  puVar3 = local_202;
  FUN_214c_06df(0xff,param_1,uVar1,uVar2);
  FUN_214c_0720(puVar3,unaff_SS);
  FUN_214c_06ad(param_2,uVar1,uVar2,puVar4,uVar5);
  return;
}



void __stdcall16far FUN_214c_082f(int param_1,int param_2,undefined4 param_3)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined1 local_202 [256];
  undefined1 local_102 [256];
  
  if (0 < param_1) {
    puVar4 = local_102;
    uVar2 = (undefined2)((ulong)param_3 >> 0x10);
    uVar1 = (undefined2)param_3;
    uVar5 = unaff_SS;
    FUN_214c_06df(param_2 + -1,1,uVar1,uVar2);
    puVar3 = local_202;
    FUN_214c_06df(0xff,param_2 + param_1,uVar1,uVar2);
    FUN_214c_0720(puVar3,unaff_SS);
    FUN_214c_06ad(0xff,uVar1,uVar2,puVar4,uVar5);
  }
  return;
}



void __stdcall16far FUN_214c_0885(uint param_1,undefined1 *param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  uint uVar3;
  byte bVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined2 uVar7;
  
  uVar7 = (undefined2)((ulong)param_3 >> 0x10);
  puVar6 = (undefined1 *)param_3;
  puVar5 = (undefined1 *)param_2;
  bVar4 = (byte)(param_1 >> 8);
  for (uVar3 = (uint)bVar4; uVar3 != 0; uVar3 = uVar3 - 1) {
    puVar1 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar1 = 0;
  }
  for (uVar3 = param_1 & 0xff; uVar3 != 0; uVar3 = uVar3 - 1) {
    puVar2 = puVar6;
    puVar6 = puVar6 + 1;
    puVar1 = puVar5;
    puVar5 = puVar5 + 1;
    *puVar2 = *puVar1;
  }
  for (uVar3 = (uint)(byte)((' ' - (char)param_1) - bVar4); uVar3 != 0; uVar3 = uVar3 - 1) {
    puVar1 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar1 = 0;
  }
  return;
}



void __cdecl16far FUN_214c_08af(undefined2 *param_1)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 *puVar3;
  
  puVar3 = (undefined2 *)param_1;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar1 = 0;
  }
  return;
}



void __stdcall16far FUN_214c_08be(byte param_1,undefined4 param_2)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)((uint)(param_1 >> 3) + (int)param_2);
  *pbVar1 = *pbVar1 | '\x01' << (param_1 & 7);
  return;
}



void __stdcall16far FUN_214c_08df(byte param_1,byte param_2,undefined4 param_3)

{
  byte *pbVar1;
  byte bVar2;
  char cVar3;
  uint uVar4;
  bool bVar5;
  
  if (param_2 <= param_1) {
    cVar3 = (param_1 - param_2) + '\x01';
    uVar4 = (uint)(param_2 >> 3);
    bVar2 = '\x01' << (param_2 & 7);
    do {
      pbVar1 = (byte *)(uVar4 + (int)param_3);
      *pbVar1 = *pbVar1 | bVar2;
      bVar5 = (char)bVar2 < '\0';
      bVar2 = bVar2 << 1 | bVar5;
      uVar4 = uVar4 + bVar5;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  return;
}



void __stdcall16far FUN_214c_0913(uint param_1,undefined1 *param_2,undefined4 param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  puVar4 = (undefined1 *)param_2;
  puVar3 = (undefined1 *)((int)param_3 + (param_1 >> 8));
  for (param_1 = param_1 & 0xff; param_1 != 0; param_1 = param_1 - 1) {
    puVar2 = puVar4;
    puVar4 = puVar4 + 1;
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar2 = *puVar1;
  }
  return;
}



char __stdcall16far FUN_214c_0933(undefined2 param_1,undefined2 param_2,byte param_3)

{
  return '\x01' << (param_3 & 7);
}



void __stdcall16far FUN_214c_0954(uint *param_1,uint *param_2)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  undefined2 uVar7;
  
  puVar6 = (uint *)param_2;
  uVar7 = (undefined2)((ulong)param_1 >> 0x10);
  puVar5 = (uint *)param_1;
  iVar4 = 0x10;
  do {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar6;
    puVar3 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar3 = *puVar2 | *puVar1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}



void __stdcall16far FUN_214c_096f(uint *param_1,uint *param_2)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  undefined2 uVar7;
  
  puVar6 = (uint *)param_2;
  uVar7 = (undefined2)((ulong)param_1 >> 0x10);
  puVar5 = (uint *)param_1;
  iVar4 = 0x10;
  do {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar6;
    puVar3 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar3 = ~*puVar2 & *puVar1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}



undefined4 FUN_214c_09db(void)

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



undefined4 __cdecl16near FUN_214c_09df(void)

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



undefined2 __cdecl16near FUN_214c_0ab5(void)

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
    uVar15 = FUN_214c_0bbb();
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



long __cdecl16near FUN_214c_0b32(void)

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
    lVar14 = FUN_214c_0bbb();
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



undefined4 __cdecl16near FUN_214c_0bbb(void)

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



void __cdecl16near FUN_214c_0bde(void)

{
  uint in_DX;
  uint unaff_DI;
  bool bVar1;
  
  if ((int)(in_DX ^ unaff_DI) < 0) {
    return;
  }
  bVar1 = (in_DX & 0x8000) == 0;
  if ((!bVar1) && (FUN_214c_0bf5(), !bVar1)) {
    return;
  }
  return;
}



void __cdecl16near FUN_214c_0bf5(void)

{
  return;
}



void __cdecl16near FUN_214c_0c08(void)

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



undefined4 __cdecl16near FUN_214c_0c47(void)

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



void __cdecl16far FUN_214c_0ca3(void)

{
  undefined1 in_CF;
  
  FUN_214c_09df();
  if (!(bool)in_CF) {
    return;
  }
  FUN_214c_01ec();
  return;
}



void __cdecl16far FUN_214c_0ca9(void)

{
  undefined1 in_CF;
  
  FUN_214c_09db();
  if (!(bool)in_CF) {
    return;
  }
  FUN_214c_01ec();
  return;
}



void __cdecl16far FUN_214c_0cb5(void)

{
  undefined1 in_CF;
  
  FUN_214c_0ab5();
  if (!(bool)in_CF) {
    return;
  }
  FUN_214c_01ec();
  return;
}



void __cdecl16far FUN_214c_0cbb(void)

{
  char in_CL;
  bool bVar1;
  
  bVar1 = false;
  if (in_CL == '\0') {
    FUN_214c_01ec();
    return;
  }
  FUN_214c_0b32();
  if (!bVar1) {
    return;
  }
  FUN_214c_01ec();
  return;
}



void __cdecl16far FUN_214c_0cc5(void)

{
  FUN_214c_0bde();
  return;
}



void __cdecl16far FUN_214c_0cc9(void)

{
  FUN_214c_0c08();
  return;
}



void __cdecl16far FUN_214c_0ccd(void)

{
  undefined1 in_CF;
  
  FUN_214c_0c47();
  if (!(bool)in_CF) {
    return;
  }
  FUN_214c_01ec();
  return;
}



void __cdecl16far FUN_214c_0cd5(void)

{
  undefined1 in_CF;
  
  FUN_214c_0c47();
  if (!(bool)in_CF) {
    return;
  }
  FUN_214c_01ec();
  return;
}



void __cdecl16near FUN_214c_0cef(void)

{
  FUN_214c_09df();
  return;
}



undefined2 __cdecl16far FUN_214c_0e79(void)

{
  char in_AL;
  undefined2 uVar1;
  uint in_DX;
  undefined2 uVar2;
  undefined4 uVar3;
  
  if ((in_AL != '\0') && ((in_DX & 0x8000) == 0)) {
    FUN_214c_0ab5(in_AL + '\x7f');
    uVar1 = 0;
    uVar3 = FUN_214c_0cef();
    uVar2 = 0;
    FUN_214c_09df((int)uVar3,uVar1,(int)((ulong)uVar3 >> 0x10));
    FUN_214c_0b32();
    FUN_214c_10fa();
    uVar3 = FUN_214c_09df();
    FUN_214c_0c08((int)uVar3,uVar2,(int)((ulong)uVar3 >> 0x10));
    FUN_214c_0ab5();
    uVar1 = FUN_214c_09df();
    if ((byte)uVar1 < 0x67) {
      uVar1 = 0;
    }
    return uVar1;
  }
  uVar1 = FUN_214c_01ec();
  return uVar1;
}



char __cdecl16far FUN_214c_0f22(void)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  byte bVar4;
  uint in_DX;
  undefined2 in_BX;
  undefined4 uVar5;
  undefined2 uVar6;
  
  uVar5 = FUN_214c_0b32();
  uVar6 = (undefined2)uVar5;
  if ((byte)uVar5 < 0x88) {
    uVar3 = FUN_214c_0c47(uVar6,in_BX,(int)((ulong)uVar5 >> 0x10));
    FUN_214c_0c08(uVar6);
    FUN_214c_09db();
    bVar1 = FUN_214c_1113();
    bVar4 = (byte)(uVar3 >> 1);
    if ((uVar3 & 1) != 0) {
      bVar1 = FUN_214c_0ab5();
    }
    cVar2 = bVar1 + bVar4;
    if (!CARRY1(bVar1,bVar4)) {
      if ((in_DX & 0x8000) != 0) {
        cVar2 = FUN_214c_0b32();
      }
      return cVar2;
    }
  }
  cVar2 = FUN_214c_01ec();
  return cVar2;
}



void FUN_214c_10fa(void)

{
  FUN_214c_0ab5();
  FUN_214c_1113();
  FUN_214c_0ab5();
  return;
}



void __cdecl16near FUN_214c_1113(void)

{
  int in_CX;
  int unaff_DI;
  undefined2 uStack_a;
  
  uStack_a = in_CX;
  while( true ) {
    FUN_214c_0ab5();
    unaff_DI = unaff_DI + 6;
    uStack_a = uStack_a + -1;
    if (uStack_a == 0) break;
    FUN_214c_09df(unaff_DI);
  }
  FUN_214c_09df();
  return;
}



uint __stdcall16far FUN_214c_1162(uint param_1)

{
  uint uVar1;
  uint extraout_DX;
  
  FUN_214c_11b0();
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = extraout_DX % param_1;
  }
  return uVar1;
}



char __cdecl16far FUN_214c_1178(void)

{
  char cVar1;
  int iVar2;
  ulong uVar3;
  
  uVar3 = FUN_214c_11b0();
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



void __cdecl16near FUN_214c_11b0(void)

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



void __cdecl16far FUN_214c_11e8(void)

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



void __cdecl16near FUN_214c_11f5(void)

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



undefined4 __cdecl16near FUN_214c_126f(void)

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



undefined2 __stdcall16far FUN_214c_1352(uint *param_1,byte *param_2)

{
  undefined2 uVar1;
  uint uVar2;
  byte *pbVar3;
  bool bVar4;
  
  bVar4 = false;
  uVar2 = (uint)*param_2;
  pbVar3 = (byte *)param_2;
  while ((pbVar3 = pbVar3 + 1, uVar2 != 0 && (bVar4 = *pbVar3 < 0x20, *pbVar3 == 0x20))) {
    uVar2 = uVar2 - 1;
  }
  uVar1 = FUN_214c_126f();
  if ((bVar4) || (uVar2 != 0)) {
    uVar2 = (int)pbVar3 - (int)(byte *)param_2;
    uVar1 = 0;
  }
  *param_1 = uVar2;
  return uVar1;
}



void __stdcall16far FUN_214c_1383(byte *param_1,undefined2 *param_2)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  undefined2 *puVar6;
  byte *pbVar7;
  undefined2 uVar8;
  
  uVar8 = (undefined2)((ulong)param_2 >> 0x10);
  puVar6 = (undefined2 *)param_2;
  pbVar5 = (byte *)param_1;
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
  for (iVar3 = 0xe; pbVar7 = pbVar7 + 2, iVar3 != 0; iVar3 = iVar3 + -1) {
    pbVar7[0] = 0;
    pbVar7[1] = 0;
  }
  bVar2 = *param_1;
  if (0x4f < bVar2) {
    bVar2 = 0x4f;
  }
  for (uVar4 = (uint)bVar2; pbVar5 = pbVar5 + 1, uVar4 != 0; uVar4 = uVar4 - 1) {
    pbVar1 = pbVar7;
    pbVar7 = pbVar7 + 1;
    *pbVar1 = *pbVar5;
  }
  *pbVar7 = 0;
  return;
}



void FUN_214c_13f3(void)

{
  FUN_214c_1400();
  return;
}



void FUN_214c_13f8(void)

{
  FUN_214c_1400();
  return;
}



void __stdcall16far FUN_214c_1400(undefined4 param_1)

{
  int iVar1;
  undefined2 in_DX;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  bool bVar4;
  
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar2 = (int)param_1;
  iVar1 = *(int *)(iVar2 + 2);
  if ((iVar1 == -0x284f) || (iVar1 == -0x284e)) {
    FUN_214c_1490();
  }
  else if (iVar1 != -0x2850) {
    *(undefined2 *)0xe78b = 0x66;
    return;
  }
  bVar4 = true;
  *(undefined2 *)(iVar2 + 2) = in_DX;
  *(undefined2 *)(iVar2 + 8) = 0;
  *(undefined2 *)(iVar2 + 10) = 0;
  FUN_214c_1496();
  if (!bVar4) {
    *(undefined2 *)(iVar2 + 2) = 0xd7b0;
  }
  return;
}



void __stdcall16far FUN_214c_1456(undefined4 param_1)

{
  undefined1 in_ZF;
  
  FUN_214c_146d();
  if ((bool)in_ZF) {
    FUN_214c_1490();
    *(undefined2 *)((int)param_1 + 2) = 0xd7b0;
  }
  return;
}



void __cdecl16near FUN_214c_146d(void)

{
  int unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  if ((*(int *)(unaff_DI + 2) != -0x284f) && (*(int *)(unaff_DI + 2) != -0x284e)) {
    *(undefined2 *)0xe78b = 0x67;
  }
  return;
}



void __cdecl16near FUN_214c_1484(void)

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



void FUN_214c_1490(void)

{
  int iVar1;
  int unaff_DI;
  undefined2 unaff_DS;
  
  FUN_214c_1484();
  iVar1 = (*(code *)*(undefined2 *)(unaff_DI + 0x1c))(0x214c);
  if (iVar1 != 0) {
    *(int *)0xe78b = iVar1;
  }
  return;
}



void __cdecl16near FUN_214c_1496(void)

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



void __cdecl16near FUN_214c_1618(void)

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



undefined1 __cdecl16near FUN_214c_1640(void)

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



void FUN_214c_167d(int param_1,undefined2 param_2)

{
  undefined2 in_BX;
  code *in_stack_00000000;
  
  *(undefined2 *)(param_1 + 8) = in_BX;
                    // WARNING: Could not recover jumptable at 0x00022b45. Too many branches
                    // WARNING: Treating indirect jump as call
  (*in_stack_00000000)();
  return;
}



void __cdecl16near FUN_214c_1687(void)

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



void __cdecl16near FUN_214c_16af(void)

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



void FUN_214c_16e5(int param_1,undefined2 param_2)

{
  undefined2 in_BX;
  code *in_stack_00000000;
  
  *(undefined2 *)(param_1 + 8) = in_BX;
                    // WARNING: Could not recover jumptable at 0x00022bad. Too many branches
                    // WARNING: Treating indirect jump as call
  (*in_stack_00000000)();
  return;
}



void FUN_214c_16ef(undefined2 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  FUN_214c_1618();
  if ((bool)in_ZF) {
    do {
      cVar1 = FUN_214c_1640();
      if (cVar1 == '\x1a') goto LAB_214c_170e;
    } while (cVar1 != '\r');
    FUN_214c_1640();
LAB_214c_170e:
    FUN_214c_167d();
  }
  uVar3 = (undefined2)((ulong)param_2 >> 0x10);
  iVar2 = (int)param_2;
  if (*(int *)(iVar2 + 2) == -0x284f) {
    if (*(int *)0xe78b != 0) {
      return;
    }
    iVar2 = (*(code *)*(undefined2 *)(iVar2 + 0x18))(0x214c,iVar2,uVar3);
    if (iVar2 == 0) {
      return;
    }
  }
  else {
    iVar2 = 0x68;
  }
  *(int *)0xe78b = iVar2;
  return;
}



void __stdcall16far FUN_214c_1712(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  if (*(int *)(iVar1 + 2) == -0x284f) {
    if (*(int *)0xe78b != 0) {
      return;
    }
    iVar1 = (*(code *)*(undefined2 *)(iVar1 + 0x18))(0x214c,iVar1,uVar2);
    if (iVar1 == 0) {
      return;
    }
  }
  else {
    iVar1 = 0x68;
  }
  *(int *)0xe78b = iVar1;
  return;
}



void FUN_214c_173c(undefined2 param_1,undefined4 param_2)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  FUN_214c_1687();
  if ((bool)in_ZF) {
    FUN_214c_16af();
    FUN_214c_16af();
    FUN_214c_16e5();
  }
  uVar2 = (undefined2)((ulong)param_2 >> 0x10);
  iVar1 = (int)param_2;
  if (*(int *)(iVar1 + 2) == -0x284e) {
    if (*(int *)0xe78b != 0) {
      return;
    }
    iVar1 = (*(code *)*(undefined2 *)(iVar1 + 0x18))(0x214c,iVar1,uVar2);
    if (iVar1 == 0) {
      return;
    }
  }
  else {
    iVar1 = 0x69;
  }
  *(int *)0xe78b = iVar1;
  return;
}



void __stdcall16far FUN_214c_1755(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  if (*(int *)(iVar1 + 2) == -0x284e) {
    if (*(int *)0xe78b != 0) {
      return;
    }
    iVar1 = (*(code *)*(undefined2 *)(iVar1 + 0x18))(0x214c,iVar1,uVar2);
    if (iVar1 == 0) {
      return;
    }
  }
  else {
    iVar1 = 0x69;
  }
  *(int *)0xe78b = iVar1;
  return;
}



undefined1 __cdecl16far FUN_214c_177f(void)

{
  undefined1 uVar1;
  undefined1 in_ZF;
  
  FUN_214c_1618();
  if ((bool)in_ZF) {
    FUN_214c_1640();
    uVar1 = FUN_214c_167d();
  }
  else {
    uVar1 = 0x1a;
  }
  return uVar1;
}



void __stdcall16far FUN_214c_1799(int param_1)

{
  int iVar1;
  undefined1 in_ZF;
  
  FUN_214c_1687();
  if ((bool)in_ZF) {
    iVar1 = param_1 + -1;
    if (iVar1 != 0 && 0 < param_1) {
      do {
        FUN_214c_16af();
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    FUN_214c_16af();
    FUN_214c_16e5();
  }
  return;
}



void __stdcall16far FUN_214c_17be(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined2 uVar4;
  undefined1 in_ZF;
  
  FUN_214c_1618();
  if ((bool)in_ZF) {
    uVar4 = (undefined2)((ulong)param_2 >> 0x10);
    pcVar3 = (char *)param_2;
    iVar2 = 0;
    do {
      cVar1 = FUN_214c_1640();
      if ((cVar1 == '\r') || (cVar1 == '\x1a')) break;
      iVar2 = iVar2 + 1;
      pcVar3 = pcVar3 + 1;
      *pcVar3 = cVar1;
    } while (iVar2 != param_1);
    pcVar3[-iVar2] = (char)iVar2;
    FUN_214c_167d();
  }
  else {
    *param_2 = '\0';
  }
  return;
}



void __stdcall16far FUN_214c_17f7(int param_1,byte *param_2)

{
  int iVar1;
  uint uVar2;
  undefined1 in_ZF;
  
  FUN_214c_1687();
  if ((bool)in_ZF) {
    uVar2 = (uint)*param_2;
    iVar1 = param_1 - uVar2;
    if (iVar1 != 0 && (int)uVar2 <= param_1) {
      do {
        FUN_214c_16af();
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    for (; uVar2 != 0; uVar2 = uVar2 - 1) {
      FUN_214c_16af();
    }
    FUN_214c_16e5();
  }
  return;
}



undefined2 __cdecl16far FUN_214c_182b(void)

{
  byte bVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  bool bVar5;
  byte local_20 [32];
  
  bVar5 = &stack0x0000 == (undefined1 *)0x20;
  FUN_214c_1618();
  if (bVar5) {
    iVar3 = 0;
    do {
      bVar1 = FUN_214c_1640();
      uVar4 = bVar1 < 0x1a;
      if (bVar1 == 0x1a) goto LAB_214c_185c;
    } while (bVar1 < 0x21);
    while( true ) {
      bVar1 = FUN_214c_1640();
      uVar4 = bVar1 < 0x20;
      if (bVar1 < 0x21) break;
      if (iVar3 != 0x20) {
        local_20[iVar3] = bVar1;
        iVar3 = iVar3 + 1;
      }
    }
LAB_214c_185c:
    FUN_214c_167d();
    if (iVar3 != 0) {
      uVar2 = FUN_214c_126f();
      if ((!(bool)uVar4) && (iVar3 == 0)) {
        return uVar2;
      }
      *(undefined2 *)0xe78b = 0x6a;
    }
  }
  return 0;
}



void __stdcall16far FUN_214c_1882(int param_1)

{
  int iVar1;
  int in_CX;
  undefined1 uVar2;
  
  uVar2 = &stack0x0000 == (undefined1 *)0x20;
  FUN_214c_11f5();
  FUN_214c_1687();
  if ((bool)uVar2) {
    iVar1 = param_1 - in_CX;
    if (iVar1 != 0 && in_CX <= param_1) {
      do {
        FUN_214c_16af();
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    do {
      FUN_214c_16af();
      in_CX = in_CX + -1;
    } while (in_CX != 0);
    FUN_214c_16e5();
  }
  return;
}



undefined1 __stdcall16far FUN_214c_18d2(void)

{
  byte bVar1;
  undefined1 uVar2;
  byte bVar3;
  undefined1 in_ZF;
  
  bVar3 = 0;
  FUN_214c_1618();
  if ((bool)in_ZF) {
    do {
      bVar1 = FUN_214c_1640();
      if ((bVar1 == 0x1a) || ((((bVar3 & 1) != 0 && (bVar1 == 0xd)) || ((bVar3 & 2) == 0)))) break;
    } while (bVar1 < 0x21);
    uVar2 = FUN_214c_167d();
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



byte __stdcall16far FUN_214c_190c(byte param_1)

{
  if ((0x60 < param_1) && (param_1 < 0x7b)) {
    param_1 = param_1 - 0x20;
  }
  return param_1;
}


