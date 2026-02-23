#include "loading_794DC.h"

/* TODO: go through this entire file again and try to actually reverse things... */

/* used as FileInfo::dest
undefined reference, even if specified in addrs-u.txt??? */
/* 0x8005866C */

/*extern s32 D_80058674;
extern s32 D_80058678;
extern s32 D_8005867C;
extern s32 D_80058684;*/

/*
before rodata even, what is this?
can write *(s32*)0x800D0004 instead of it e.g.
*/
/*extern s32 D_800D0004;
extern s32 D_80010004;
extern s32 D_80010008;
extern s32 D_8001000C;*/

const u8 s_img_file_8012c230[] = "img_file";
const u8 s_ldr_file_8012c23c[] = "ldr_file";
const u8 s_vdo_file_8012c248[] = "vdo_file";
const u8 s_trk_file_8012c254[] = "trk_file";
const u8 s_pre_file_8012c260[] = "pre_file";
const u8 s_crd_file_8012c26c[] = "crd_file";
const u8 s_gam_file_8012c278[] = "gam_file";
const u8 s_vig_wld_file_8012c284[] = "vig_wld_file";
const u8 s_wld_file_8012c294[] = "wld_file";
const u8 s_map_file0_8012c2a0[] = "map_file[0]";
const u8 s_fnd_file_8012c2ac[] = "fnd_file";
const u8 s_vab_file_8012c2b8[] = "vab_file";
const u8 s_big_file_8012c2c4[] = "big_file";
const u8 s_vab4sep_file_8012c2d0[] = "vab4sep_file";
const u8 s_ini_file_8012c2e0[] = "ini_file";

#ifdef BSS_DEFS
s32 PS1_FileTemp;
s16 no_fnd;
s16 plan2_height;
s16 plan2_width;
BackgroundData *PS1_LevelBGBlock;
s16 *PS1_LevelMapBlock;
u8 *PS1_LevelObjBlock;
u8 D_801E4B58;
void *D_801F4410;
void *D_801F5160;
s32 *D_801E5260;
s32 *D_801F59E0;
#endif

/* 794DC 8019DCDC -O2 -msoft-float */
void PS1_Init_ImgLdrVdoTrk_Files(void)
{
    PS1_FileTemp = PS1_InitFiles(PS1_ImgFiles, 3, s_img_file_8012c230);
    PS1_FileTemp = PS1_InitFiles(PS1_LdrFiles, 2, s_ldr_file_8012c23c);
    PS1_FileTemp = PS1_InitFiles(PS1_VdoFiles, 6, s_vdo_file_8012c248);
    PS1_FileTemp = PS1_InitFiles(PS1_TrkFiles, 53, s_trk_file_8012c254);
}

/* 79574 8019DD74 -O2 -msoft-float */
void FUN_8019dd74(void)
{
    PS1_InitFiles(PS1_PreFiles, 5, s_pre_file_8012c260);
    PS1_InitFiles(PS1_CrdFiles, 6, s_crd_file_8012c26c);
    PS1_InitFiles(PS1_GamFiles, 6, s_gam_file_8012c278);
    PS1_InitFiles(PS1_VigWldFiles, 6, s_vig_wld_file_8012c284);
    PS1_InitFiles(PS1_WldFiles, 6, s_wld_file_8012c294);
    PS1_InitFiles(PS1_MapFiles, 126, s_map_file0_8012c2a0);
    PS1_InitFiles(PS1_FndFiles, 31, s_fnd_file_8012c2ac);
    PS1_InitFiles(PS1_VabFiles, 7, s_vab_file_8012c2b8);
    PS1_InitFiles(PS1_BigFiles, 7, s_big_file_8012c2c4);
    PS1_InitFiles(PS1_Vab4sepFiles, 7, s_vab4sep_file_8012c2d0);
    PS1_InitFiles(PS1_FxsFiles, 2, s_filefxs_801cf0d0);
    PS1_InitFiles(PS1_IniFiles, 1, s_ini_file_8012c2e0);
}

/* 796AC 8019DEAC -O2 -msoft-float */
void charge_une_vignette(void)
{
    PS1_ImgFiles[0].dest = D_801F4380;
    PS1_FileTemp = datafile_read(PS1_ImgFiles, 0, 1, 0);
    plan2_width = 320;
    plan2_height = 240;
    D_801E4B58 = false;
    D_801CF0CA = 0;
}

/* 7971C 8019DF1C -O2 -msoft-float */
void charge_wld_vignette(s16 param_1)
{
    s32 index_1;
    s16 index_2;

    index_1 = param_1 - 1;
    PS1_VigWldFiles[index_1].dest = D_801F4380;
    PS1_FileTemp = datafile_read(PS1_VigWldFiles, index_1, 1, 0);
    index_2 = param_1 - 1;
    switch (index_2)
    {
    case 0:
        plan2_width = 219;
        plan2_height = 180;
        D_801E4B58 = false;
        D_801CF0CA = 0;
        break;
    case 1:
        plan2_width = 231;
        plan2_height = 214;
        D_801E4B58 = false;
        D_801CF0CA = 0;
        break;
    case 2:
        plan2_width = 257;
        plan2_height = 180;
        D_801E4B58 = false;
        D_801CF0CA = 0;
        break;
    case 3:
        plan2_width = 200;
        plan2_height = 180;
        D_801E4B58 = false;
        D_801CF0CA = 0;
        break;
    case 4:
        plan2_width = 146;
        plan2_height = 180;
        D_801E4B58 = false;
        D_801CF0CA = 0;
        break;
    case 5:
        plan2_width = 203;
        plan2_height = 180;
        D_801E4B58 = false;
        D_801CF0CA = 0;
        break;
    }
}

/* 7981C 8019E01C -O2 -msoft-float */
void charge_ini(void)
{
    u8 *unk_1 = D_801F4380;
    PS1_FileTemp = datafile_read(PS1_IniFiles, 0, 1, 0);
    D_801F4410 = (void *) 0x800D0000;
    D_801F5160 = (void *) 0x800D0000;
    D_801F7E90 = *(s32 *) 0x800D0004 + (void *) 0x800D0000;
    init_ini();
    D_801F4380 = &D_801F4410[((s32 *) D_801F5160)[2]];
    load_vram_ini(((s32 *) D_801F5160)[3] - ((s32 *) D_801F5160)[2]);
    LoadClut(&D_801F4410[((s32 *) D_801F5160)[3]], 768, 490);
    LoadClut(&D_801F4410[((s32 *) D_801F5160)[4]], 768, 491);
    DrawSync(0);
    D_801F4380 = unk_1;
}

/* 79918 8019E118 -O2 -msoft-float */
void charge_fix(void)
{
    u8 *unk_1 = D_801F4380;
    PS1_FileTemp = datafile_read(PS1_FxsFiles, 0, 1, 0);
    D_801F4410 = (void *) 0x80010000;
    D_801F5160 = (void *) 0x80010000;
    PS1_AllFixData = *(s32 *) 0x80010004 + (void *) 0x80010000;
    D_801F4380 = *(s32 *) 0x80010008 + (void *) 0x80010000;
    load_vram_ray(*(s32 *) 0x8001000C - *(s32 *) 0x80010008);
    LoadClut(&D_801F4410[((s32 *) D_801F5160)[3]], 768, 492);
    LoadClut(&D_801F4410[((s32 *) D_801F5160)[4]], 768, 495);
    LoadClut(&D_801F4410[((s32 *) D_801F5160)[5]], 768, 490);
    LoadClut(&D_801F4410[((s32 *) D_801F5160)[6]], 768, 491);
    LoadClut(&D_801F4410[((s32 *) D_801F5160)[7]], 768, 493);
    LoadClut(&D_801F4410[((s32 *) D_801F5160)[8]], 768, 494);
    DrawSync(0);
    D_801F4380 = unk_1;
    PS1_LoadAllFixSound();
}

/* 79A98 8019E298 -O2 -msoft-float */
void charge_wld(s16 world)
{
    start_data();
    PS1_FileTemp = datafile_read(&PS1_WldFiles[world - 1], 0, 1, 0);
    D_801F4410 = (void *) 0x8005866C;
    D_801F5160 = (void *) 0x8005866C;
    D_801D7840 = *(s32 *) 0x80058674 + (void *) 0x8005866C;
    D_801F4380 = *(s32 *) 0x80058678 + (void *) 0x8005866C;
    D_801F8190 = *(s32 *) 0x80058684 + (void *) 0x8005866C;
    load_vram_wld(*(s32 *) 0x8005867C - *(s32 *) 0x80058678);
    LoadClut(&D_801F4410[((s32 *) D_801F5160)[4]], 768, 490);
    LoadClut(&D_801F4410[((s32 *) D_801F5160)[5]], 768, 491);
    PS1_LoadTileSet(((s32 *) D_801F5160)[7] - ((s32 *) D_801F5160)[6]);
    D_801CF0CC = 0;
    D_801CF0CD = false;
    PS1_LoadTilePalettes(&D_801F4410[((s32 *) D_801F5160)[7]], (u8) ((u32) (*((s32 *) D_801F5160 + 8) - ((s32 *) D_801F5160)[7]) >> 9));
    PS1_LoadTilePaletteMappingTable(&D_801F4410[((s32 *) D_801F5160)[8]]);
    D_801CEE9C = world;
    D_801CEE9A = 0;
    no_fnd = -1;
    D_801E5260 = D_801C438C[world - 1];
    D_801F59E0 = D_801C4374[world - 1];
    PS1_LoadWorldSound(world);
}

/* 79C78 8019E478 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/loading_794DC", charge_lvl);
#else
/* s16 without return (see c89 3.6.6.4 The return statement) */
s16 charge_lvl(void)
{
    start_data();
    D_801F4410 = D_801F59E0;
    D_801F5160 = D_801F59E0;
    PS1_FileTemp = datafile_read(&PS1_MapFiles[num_world * 21 - 21], num_level - 1, 1, 0);
    PS1_LevelBGBlock = &D_801F4410[((s32 *) D_801F5160)[1]];
    PS1_LevelObjBlock = &D_801F4410[((s32 *) D_801F5160)[2]];
    PS1_LevelMapBlock = &D_801F4410[((s32 *) D_801F5160)[3]];
    D_801F4380 = &D_801F4410[((s32 *) D_801F5160)[4]];
    if (
        (num_world == 4 && (num_level == 11 || num_level == 4)) ||
        (num_world == 6 && num_level == 4)
    )
        load_vram_lvl256(((s32 *) D_801F5160)[5] - ((s32 *) D_801F5160)[4]);
    else
        load_vram_lvl(((s32 *) D_801F5160)[5] - ((s32 *) D_801F5160)[4]);
    load_unimap(&mp);
    InitLevel();
    init_bgm();
    PS1_HasLoadedFont = false;
    D_801CEE9A = num_level;
    switch (num_world)
    {
    case 1:
        if (num_level >= 18)
            charge_let2();
        break;
    case 2:
        if (num_level >= 17)
            charge_let2();
        break;
    case 3:
        if (num_level >= 12)
            charge_let2();
        break;
    case 4:
        if (num_level >= 12)
            charge_let2();
        break;
    case 5:
        if (num_level >= 12)
            charge_let2();
        break;
    }
}
#endif

/* 79E94 8019E694 -O2 -msoft-float */
void charge_fnd(void)
{
    u8 *unk_1;

    if (no_fnd != PS1_BackgroundIndexTable[num_world - 1][num_level - 1])
    {
        no_fnd = PS1_BackgroundIndexTable[num_world - 1][num_level - 1];
        start_data();
        PS1_FileTemp = datafile_read(PS1_FndFiles, no_fnd, 1, 0);
        unk_1 = D_801E5260;
        D_801F4410 = unk_1;
        D_801F5160 = unk_1;
        D_801F8180 = &unk_1[D_801E5260[1]];
        D_801E4F50 = &unk_1[D_801E5260[2]];
        InitBG();
    }
}

/* 79F70 8019E770 -O2 -msoft-float */
void charge_wm(void)
{
    no_fnd = -1;
    start_data();
    PS1_ImgFiles[2].dest = D_801F4380;
    D_801F8180 = D_801F4380;
    PS1_FileTemp = datafile_read(PS1_ImgFiles, 2, 1, 0);
    D_801CF0CD = false;
    InitBG();
}

/* 79FE4 8019E7E4 -O2 -msoft-float */
void PS1_LoadVideoTables(void)
{
    start_data();
    PS1_FileTemp = datafile_read(PS1_VdoFiles, 0, 1, 0);
}

/* 7A024 8019E824 -O2 -msoft-float */
void charge_let2(void)
{
    if (!PS1_HasLoadedFont)
    {
        PS1_FxsFiles[1].dest = D_801F4380;
        PS1_FileTemp = datafile_read(PS1_FxsFiles, 1, 1, 0);
        load_vram_let2(PS1_FxsFiles[1].file.size);
        PS1_HasLoadedFont = true;
    }
}

/* 7A094 8019E894 -O2 -msoft-float */
void charge_vig_loader1(void)
{
    D_801F4380 = (void *) 0x8005866C;
    PS1_LdrFiles[0].dest = (void *) 0x8005866C;
    start_data();
    PS1_FileTemp = datafile_read(PS1_LdrFiles, 0, 1, 0);
    plan2_width = 640;
    plan2_height = 262;
    D_801E4B58 = false;
    D_801CF0CA = 0;
}

/* 7A114 8019E914 -O2 -msoft-float */
void charge_vig_loader2(void)
{
    D_801F4380 = (void *) 0x8005866C;
    PS1_LdrFiles[1].dest = (void *) 0x8005866C;
    start_data();
    PS1_FileTemp = datafile_read(PS1_LdrFiles, 1, 1, 0);
    plan2_width = 279;
    plan2_height = 90;
    D_801E4B58 = false;
    D_801CF0CA = 0;
}

/* 7A194 8019E994 -O2 -msoft-float */
void LOAD_CONTINUE_SCREEN(void)
{
    PS1_ImgFiles[1].dest = D_801F4380;
    start_data();
    PS1_FileTemp = datafile_read(PS1_ImgFiles, 1, 1, 0);
    plan2_width = 320;
    plan2_height = 137;
    D_801E4B58 = true;
    D_801CF0CA = 0;
}

/* 7A210 8019EA10 -O2 -msoft-float */
void PS1_LoadImgSplash(void)
{
    if (!D_801CF0CD)
    {
        PS1_ImgFiles[0].dest = D_801F4380;
        start_data();
        PS1_FileTemp = datafile_read(PS1_ImgFiles, 0, 1, 0);
        plan2_width = 320;
        plan2_height = 240;
        D_801E4B58 = false;
        D_801CF0CA = 0;
        D_801CF0CD = true;
    }
}

/* 7A2A0 8019EAA0 -O2 -msoft-float */
void LOAD_SAVE_SCREEN(void)
{
    if (!D_801CF0CD)
    {
        PS1_ImgFiles[0].dest = D_801F4380;
        start_data();
        PS1_FileTemp = datafile_read(PS1_ImgFiles, 0, 1, 0);
        plan2_width = 320;
        plan2_height = 240;
        D_801E4B58 = false;
        D_801CF0CA = 0;
        D_801CF0CD = true;
    }
}

/* 7A330 8019EB30 -O2 -msoft-float */
void FUN_8019eb30(void)
{
    if (!D_801CF0CD)
    {
        PS1_ImgFiles[0].dest = D_801F4380;
        start_data();
        PS1_FileTemp = datafile_read(PS1_ImgFiles, 0, 1, 0);
        plan2_width = 320;
        plan2_height = 240;
        D_801E4B58 = false;
        D_801CF0CA = 0;
        D_801CF0CD = true;
    }
}

/* 7A3C0 8019EBC0 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/loading_794DC", FUN_8019ebc0);
#else
/* s16 without return (see c89 3.6.6.4 The return statement) */
s16 FUN_8019ebc0(void)
{
    if (PS1_ShouldClearPassword)
    {
        switch (Etape_History)
        {
        case 1:
            D_801F4380 = (void *) 0x8005866C;
            PS1_PreFiles[0].dest = (void *) 0x8005866C;
            PS1_FileTemp = datafile_read(PS1_PreFiles, 0, 1, 0);
            D_801F4380 += 0x19000;
            PS1_PreFiles[1].dest = D_801F4380;
            PS1_FileTemp = datafile_read(PS1_PreFiles, 1, 1, 0);
            D_801F4380 += 0x19000;
            PS1_PreFiles[2].dest = D_801F4380;
            PS1_FileTemp = datafile_read(PS1_PreFiles, 2, 1, 0);
            D_801F4380 += 0x19000;
            PS1_PreFiles[3].dest = D_801F4380;
            PS1_FileTemp = datafile_read(PS1_PreFiles, 3, 1, 0);
            D_801F4380 += 0x19000;
            PS1_PreFiles[4].dest = D_801F4380;
            PS1_FileTemp = datafile_read(PS1_PreFiles, 4, 1, 0);
            D_801F4380 = (void *) 0x8005866C;
            plan2_width = 254;
            plan2_height = 180;
            D_801E4B58 = false;
            D_801CF0CA = 0;
            break;
        case 2:
            D_801F4380 += 0x19000;
            plan2_width = 208;
            plan2_height = 180;
            D_801E4B58 = false;
            D_801CF0CA = 0;
            break;
        case 3:
            D_801F4380 += 0x19000;
            plan2_width = 200;
            plan2_height = 200;
            D_801E4B58 = false;
            D_801CF0CA = 0;
            break;
        case 4:
            D_801F4380 += 0x19000;
            plan2_width = 200;
            plan2_height = 180;
            D_801E4B58 = false;
            D_801CF0CA = 0;
            break;
        case 5:
            D_801F4380 += 0x19000;
            plan2_width = 146;
            plan2_height = 150;
            D_801E4B58 = false;
            D_801CF0CA = 0;
            break;
        }
    }
    else
    {
        D_801F4380 = (void *) 0x8005866C;
        PS1_PreFiles[4].dest = (void *) 0x8005866C;
        PS1_FileTemp = datafile_read(PS1_PreFiles, 4, 1, 0);
        plan2_width = 146;
        plan2_height = 150;
        D_801E4B58 = false;
        D_801CF0CA = 0;
    }
}
#endif

/* 7A688 8019EE88 -O2 -msoft-float */
void LOAD_CREDITS_VIGNET(void)
{
    switch (display_Vignet)
    {
    case 0:
        D_801F4380 = (void *) 0x8005866C;
        PS1_CrdFiles[0].dest = (void *) 0x8005866C;
        PS1_FileTemp = datafile_read(PS1_CrdFiles, 0, 1, 0);
        D_801F4380 += 0x15800;
        PS1_CrdFiles[1].dest = D_801F4380;
        PS1_FileTemp = datafile_read(PS1_CrdFiles, 1, 1, 0);
        D_801F4380 += 0x15800;
        PS1_CrdFiles[2].dest = D_801F4380;
        PS1_FileTemp = datafile_read(PS1_CrdFiles, 2, 1, 0);
        D_801F4380 += 0x15800;
        PS1_CrdFiles[3].dest = D_801F4380;
        PS1_FileTemp = datafile_read(PS1_CrdFiles, 3, 1, 0);
        D_801F4380 += 0x15800;
        PS1_CrdFiles[4].dest = D_801F4380;
        PS1_FileTemp = datafile_read(PS1_CrdFiles, 4, 1, 0);
        D_801F4380 += 0x15800;
        PS1_CrdFiles[5].dest = D_801F4380;
        PS1_FileTemp = datafile_read(PS1_CrdFiles, 5, 1, 0);
        D_801F4380 = (void *) 0x8005866C;
        plan2_width = 206;
        plan2_height = 200;
        D_801E4B58 = false;
        D_801CF0CA = 255;
        break;
    case 1:
        D_801F4380 += 0x15800;
        plan2_width = 199;
        plan2_height = 200;
        D_801E4B58 = false;
        D_801CF0CA = 255;
        break;
    case 2:
        D_801F4380 += 0x15800;
        plan2_width = 182;
        plan2_height = 200;
        D_801E4B58 = false;
        D_801CF0CA = 255;
        break;
    case 3:
        D_801F4380 += 0x15800;
        plan2_width = 195;
        plan2_height = 200;
        D_801E4B58 = false;
        D_801CF0CA = 255;
        break;
    case 4:
        D_801F4380 += 0x15800;
        plan2_width = 214;
        plan2_height = 200;
        D_801E4B58 = false;
        D_801CF0CA = 255;
        break;
    case 5:
        D_801F4380 += 0x15800;
        plan2_width = 187;
        plan2_height = 200;
        D_801E4B58 = false;
        D_801CF0CA = 255;
        break;
    }
}

/* 7A924 8019F124 -O2 -msoft-float */
void LOAD_VIGNET_GAME(void)
{
    s16 unk_1 = num_world - 1;

    switch (unk_1)
    {
    case 0:
        if (num_level == 9)
        {
            PS1_GamFiles[0].dest = D_801F4380;
            PS1_FileTemp = datafile_read(PS1_GamFiles, 0, 1, 0);
            plan2_width = 178;
            plan2_height = 150;
            D_801E4B58 = false;
            D_801CF0CA = 0;
        }
        break;
    case 2:
        if (num_level == 6)
        {
            PS1_GamFiles[1].dest = D_801F4380;
            PS1_FileTemp = datafile_read(PS1_GamFiles, 1, 1, 0);
            plan2_width = 159;
            plan2_height = 150;
            D_801E4B58 = false;
            D_801CF0CA = 0;
        }
        break;
    case 3:
        if (num_level == 11)
        {
            PS1_GamFiles[2].dest = D_801F4380;
            PS1_FileTemp = datafile_read(PS1_GamFiles, 2, 1, 0);
            plan2_width = 171;
            plan2_height = 150;
            D_801E4B58 = false;
            D_801CF0CA = 0;
        }
        break;
    case 4:
        if (num_level == 3)
        {
            PS1_GamFiles[3].dest = D_801F4380;
            PS1_FileTemp = datafile_read(PS1_GamFiles, 3, 1, 0);
            plan2_width = 162;
            plan2_height = 150;
            D_801E4B58 = false;
            D_801CF0CA = 0;
        }
        if (num_level == 11)
        {
            PS1_GamFiles[4].dest = D_801F4380;
            PS1_FileTemp = datafile_read(PS1_GamFiles, 4, 1, 0);
            plan2_width = 168;
            plan2_height = 150;
            D_801E4B58 = false;
            D_801CF0CA = 0;
        }
        break;
    case 5:
        if (num_level == 4)
        {
            PS1_GamFiles[5].dest = D_801F4380;
            PS1_FileTemp = datafile_read(PS1_GamFiles, 5, 1, 0);
            plan2_width = 306;
            plan2_height = 240;
            D_801E4B58 = false;
            D_801CF0CA = 0;
        }
        break;
    }
}