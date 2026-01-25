#include "card.h"

#ifdef PLATFORM_PSYZ
#include <libapi.h>
#include <libetc.h>
#endif

#ifdef BSS_DEFS
LoadInfoRay loadInfoRay[6];
u8 D_801F7F08[34];
s32 PS1_SwCARD_EvSpERROR;
s32 PS1_SwCARD_EvSpIOE;
s32 PS1_SwCARD_EvSpNEW;
s32 PS1_SwCARD_EvSpTIMOUT;
s32 PS1_HwCARD_EvSpERROR;
s32 PS1_HwCARD_EvSpIOE;
s32 PS1_HwCARD_EvSpNEW;
s32 PS1_HwCARD_EvSpTIMOUT;
s32 PS1_Checksum;
u8 PS1_SaveFilenames[3][32];
#endif

/* TODO:
(only once strncmp is declared)
warning: passing arg 2 of `strncmp' discards `const' from pointer target type
in functions:
PS1_InitSaveRayAndFilenames
FUN_8016b2e8

change "s_BISLUS00005_8012aca8, 12" in strncmps to use sizeof instead?
*/

const u8 s__Testing_memory_card_in_slot_d_8012ac14[] = "\nTesting memory card in slot %d\n\n";
const u8 s_Card_exist_8012ac38[] = "Card exist\n";
const u8 s_No_card_8012ac44[] = "No card\n";
const u8 s_New_card_8012ac50[] = "New card\n";
const u8 s_Formatted_8012ac5c[] = "Formatted\n";
const u8 s_Unformatted_8012ac68[] = "Unformatted\n";
const u8 s_unformat_8012ac78[] = "unformat";
const u8 s__FORMATING_8012ac84[] = "\nFORMATING";
const u8 s__Error_in_formatting_8012ac90[] = "\nError in formatting\n";
const u8 s_BISLUS00005_8012aca8[] = "BISLUS-00005";
const u8 PS1_SaveIcon1[] __attribute__((aligned(2))) =
{
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x2A, 0x33, 0xD4, 0xAA, 0xAA, 0xAA, 0x2A, 0x11, 0xB4, 
  0x4B, 0xEB, 0xAA, 0xAA, 0xAA, 0x12, 0xB3, 0xED, 0xBD, 0x24, 
  0xAE, 0xAA, 0xAA, 0x31, 0xAB, 0xAA, 0xDE, 0xBE, 0xE2, 0xAA, 
  0xAA, 0x2A, 0xAB, 0xBA, 0x87, 0xE8, 0xEB, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x0C, 0x58, 0xB5, 0xAE, 0xAA, 0xAA, 0xAA, 0xAA, 0xC0, 
  0xB8, 0x8D, 0xAF, 0xAA, 0xAA, 0xAA, 0xAA, 0xF7, 0x5B, 0xD5, 
  0xAF, 0xAA, 0xAA, 0xAA, 0x5A, 0x53, 0x87, 0xB5, 0xAF, 0xAA, 
  0xAA, 0xAA, 0x33, 0x33, 0x53, 0x8D, 0xAF, 0xAA, 0xAA, 0xAA, 
  0x33, 0x33, 0xB5, 0x89, 0xAF, 0xAA, 0xAA, 0xAA, 0x58, 0x55, 
  0xD8, 0x8B, 0xAF, 0xAA, 0xAA, 0xAA, 0x8A, 0xBB, 0x8B, 0xF8, 
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
};
const u8 PS1_SaveIcon2and3[] __attribute__((aligned(2))) =
{
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x2A, 0x33, 0xD4, 0xAA, 0xAA, 0xAA, 0x2A, 0x11, 0xB4, 
  0x4B, 0xEB, 0xAA, 0xAA, 0xAA, 0x12, 0xB3, 0xED, 0xBD, 0x24, 
  0xAE, 0xAA, 0xAA, 0x31, 0xAB, 0xAA, 0xBE, 0xBE, 0xE2, 0xAA, 
  0xAA, 0x2A, 0xAB, 0xBA, 0xC7, 0xE7, 0xEB, 0xAA, 0xAA, 0xAA, 
  0xAA, 0x0C, 0x00, 0xC0, 0xAE, 0xAA, 0xAA, 0xAA, 0xAA, 0xC0, 
  0x00, 0x70, 0xAF, 0xAA, 0xAA, 0xAA, 0xAA, 0x7F, 0x0F, 0xC0, 
  0xAF, 0xAA, 0xAA, 0xAA, 0x5A, 0x53, 0x67, 0xBC, 0xAF, 0xAA, 
  0xAA, 0xAA, 0x33, 0x33, 0x53, 0x8B, 0xAF, 0xAA, 0xAA, 0xAA, 
  0x33, 0x33, 0x85, 0x8D, 0xAF, 0xAA, 0xAA, 0xAA, 0x58, 0x55, 
  0xD8, 0x89, 0xAF, 0xAA, 0xAA, 0xAA, 0x8A, 0xBB, 0x8B, 0xF8, 
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
};
const u8 PS1_SaveIconPalette[] __attribute__((aligned(2))) =
{
  0xFF, 0x7F, 0xFF, 0x63, 0xFD, 0x2A, 0xFC, 0x4E, 0x9B, 0x16, 
  0x59, 0x36, 0x78, 0x7B, 0xF7, 0x7E, 0xF7, 0x29, 0x56, 0x18, 
  0xD6, 0x77, 0x93, 0x1D, 0x72, 0x6E, 0x2F, 0x11, 0xCC, 0x0C, 
  0x00, 0x00
};
const u8 s__Saving_file_8012add8[] = "\nSaving file\n";
const u8 s_bu02xss4u_8012ade8[] = "bu%02x:%s%s%4u";
const u8 s_Rayman_s_03d_8012adf8[] = "Rayman %s %03d%%";
const u8 s__Cant_open_file_8012ae0c[] = "\nCan't open file\n";
const u8 s__Cannot_create_file_8012ae20[] = "\nCannot create file\n";
const u8 s_bu02xss_8012ae38[] = "bu%02x:%s%s";

/* 45A7C 8016A27C -O2 -msoft-float */
s32 PS1_InitPAD(void)
{
#ifdef PLATFORM_PSYZ
    InitPAD(PS1_PadReceiveBuffer, D_801F7F08, D_801CF01C, D_801CF020);
#else
    InitPAD(PS1_PadReceiveBuffer, D_801CF01C, D_801F7F08, D_801CF020);
#endif
    VSync(0);
    VSync(0);
    VSync(0);
    VSync(0);
    return PS1_PadReceiveBuffer[0] == 0 && PS1_PadReceiveBuffer[1] == 0x41;
}

/* 45B04 8016A304 -O2 -msoft-float */
s32 PS1_TestSwCARD(void)
{
    while (true)
    {
        if (TestEvent(PS1_SwCARD_EvSpIOE) == 1)
            return 0;
        if (TestEvent(PS1_SwCARD_EvSpERROR) == 1)
            return 1;
        if (TestEvent(PS1_SwCARD_EvSpTIMOUT) == 1)
            return 2;
        if (TestEvent(PS1_SwCARD_EvSpNEW) == 1)
            return 3;
    }
}

/* 45B84 8016A384 -O2 -msoft-float */
void PS1_TestSwCARDOnce(void)
{
    TestEvent(PS1_SwCARD_EvSpIOE);
    TestEvent(PS1_SwCARD_EvSpERROR);
    TestEvent(PS1_SwCARD_EvSpTIMOUT);
    TestEvent(PS1_SwCARD_EvSpNEW);
}

/* 45BDC 8016A3DC -O2 -msoft-float */
s32 PS1_TestHwCARD(void)
{
    while (true)
    {
        if (TestEvent(PS1_HwCARD_EvSpIOE) == 1)
            return 0;
        if (TestEvent(PS1_HwCARD_EvSpERROR) == 1)
            return 1;
        if (TestEvent(PS1_HwCARD_EvSpTIMOUT) == 1)
            return 2;
        if (TestEvent(PS1_HwCARD_EvSpNEW) == 1)
            return 3;
    }
}

/* 45C5C 8016A45C -O2 -msoft-float */
void PS1_TestHwCARDOnce(void)
{
    TestEvent(PS1_HwCARD_EvSpIOE);
    TestEvent(PS1_HwCARD_EvSpERROR);
    TestEvent(PS1_HwCARD_EvSpTIMOUT);
    TestEvent(PS1_HwCARD_EvSpNEW);
}

/* 45CB4 8016A4B4 -O2 -msoft-float */
u8 PS1_TestCard(u8 par_chan)
{
    s32 test_res;

    _card_info(par_chan);
    test_res = PS1_TestSwCARD();
    FntPrint(s__Testing_memory_card_in_slot_d_8012ac14, par_chan >> 4);
    switch (test_res)
    {
    case 2:
        FntPrint(s_No_card_8012ac44);
        return 0;
    case 0:
    case 3:
        switch (test_res)
        {
        case 0:
            FntPrint(s_Card_exist_8012ac38);
            break;
        case 3:
            FntPrint(s_New_card_8012ac50);
            PS1_TestHwCARDOnce();
            _card_clear(par_chan);
            PS1_TestHwCARD();
            break;
        }
        PS1_TestSwCARDOnce();
        _card_load(par_chan);
        test_res = PS1_TestSwCARD();
        switch (test_res)
        {
        case 0:
            FntPrint(s_Formatted_8012ac5c);
            return 2;
        case 2:
            FntPrint(s_No_card_8012ac44);
            return 0;
        case 3:
            FntPrint(s_Unformatted_8012ac68);
            return 1;
        default:
            FntPrint(s_Error_801cf024);
            return 0xFF; /* TODO: callers check -1 instead */
        }
        break;
    default:
        FntPrint(s_Error_801cf024);
        return 0xFF;
    }
}

/* 45E34 8016A634 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/card", PS1_GetNbreFiles);
#else
/*
matches, but
inline with 0x4b
assigning char pointers to (s32 *)
do{}while();
*/

static inline u8 test_lt()
{
    return 0x4b;
}

s32 PS1_GetNbreFiles(u8 *name_start, struct DIRENTRY *in_files)
{
    u8 filename[128]; /* size correct? */
    s32 *cpy_src;
    struct DIRENTRY *cur_file;
    s32 unk_1;
    s32 unk_2;

#ifdef PLATFORM_PSYZ
    strcpy((char *)filename, (const char *)name_start);
    strcat((char *)filename, (const char *)s__801cf02c);
#else
    strcpy(filename, name_start);
    strcat(filename, s__801cf02c);
#endif

    switch (PS1_TestCard(0))
    {
    case 0:
        cpy_src = (s32 *) s_no_card_801cf030;
        cur_file = in_files;
        unk_1 = 0;
        do
        {
            __builtin_memcpy(cur_file->name, cpy_src, sizeof(s_no_card_801cf030));
            cur_file++;
            unk_1 += 5;
        } while (unk_1 < test_lt());

        return 0x0000000F;
    case 1:
        cpy_src = (s32 *) s_unformat_8012ac78;
        cur_file = in_files;
        unk_1 = 0;
        do
        {
            __builtin_memcpy(cur_file->name, cpy_src, sizeof(s_unformat_8012ac78));
            cur_file++;
            unk_1 += 5;
        } while (unk_1 < test_lt());

        return 0x0000000F;
    case -1:
        cur_file = in_files;
        unk_1 = 0;
        do
        {
            __builtin_memcpy(cur_file->name, s_error_801cf038, sizeof(s_error_801cf038));
            cur_file++;
            unk_1 += 5;
        } while (unk_1 < test_lt());

        return 0x0000000F;
    default:
        unk_2 = 0;
        if (firstfile(filename, in_files) == in_files)
        {
            do
            {
                unk_2++;
                in_files++;
            } while (nextfile(in_files) == in_files);
        }

        return unk_2;
    }
}

#ifdef ALTERNATIVE
s32 PS1_GetNbreFiles(u8 *name_start, struct DIRENTRY *in_files)
{
    u8 sp10[128]; /* size correct? */
    s32 temp_v1;
    u8 *var_a2_1;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_s1;
    s32 var_v0;
    struct DIRENTRY *var_a3_1;
    struct DIRENTRY *var_a3_2;
    struct DIRENTRY *var_s0;
    u16 test_1;

#ifdef PLATFORM_PSYZ
    strcpy((char *)sp10, (const char *)name_start);
    strcat((char *)sp10, (const char *)s__801cf02c);
#else
    strcpy(sp10, name_start);
    strcat(sp10, s__801cf02c);
#endif

    switch (PS1_TestCard(0))
    {
    case 0:
        /*
        15 * 5
        tried rewriting as for()
        tried rewriting as var_a3_1 != &file[15]
        var_a2_1 as struct size 5
        checked in debugger
        */
        var_a3_1 = in_files;
        var_a2_1 = 0;
        while (var_a2_1 < 0x4b)
        {
            __builtin_memcpy(var_a3_1->name, s_no_card_801cf030, sizeof(s_no_card_801cf030));
            var_a3_1 += 1;
            var_a2_1 += 5;
        }

        return 0x0000000F;
    case 1:
        var_a3_1 = in_files;
        var_a2_1 = 0;
        while (var_a2_1 < 0x4b)
        {
            __builtin_memcpy(var_a3_1->name, s_unformat_8012ac78, sizeof(s_unformat_8012ac78));
            var_a3_1 += 1;
            var_a2_1 += 5;
        }

        return 0x0000000F;
        break;
    case -1:
        var_a3_1 = in_files;
        var_a2_1 = 0;
        while (var_a2_1 < 0x4b)
        {
            __builtin_memcpy(var_a3_1->name, s_error_801cf038, sizeof(s_error_801cf038));
            var_a3_1 += 1;
            var_a2_1 += 5;
        }
        return 0x0000000F;
    default:
        var_v0 = 0;
        if (firstfile(sp10, in_files) == in_files)
        {
            do
            {
                var_v0 += 1;
                in_files += 1;
            } while (nextfile(in_files) == in_files);
        }
        return var_v0;
    }
}
#endif
#endif

/* 45F90 8016A790 -O2 -msoft-float */
s32 PS1_CardFilenameChecksum(u8 chan)
{
    struct DIRENTRY files[15];
    u8 name_start[8];
    s32 nbre_files;
    u8 cur_file; u8 cur_char;
    s32 sum = 0;

    sprintf(name_start, s_bu02x_801cf040, chan);
    nbre_files = PS1_GetNbreFiles(name_start, files);

    for (cur_file = 0; cur_file < nbre_files; cur_file++)
        for (cur_char = 0; cur_char < (u32) strlen(files[cur_file].name); cur_char++)
            sum += (u8) files[cur_file].name[cur_char] << cur_file;

    return sum;
}

/* 4607C 8016A87C -O2 -msoft-float */
void PS1_InitializeCard(u8 chan)
{
    EnterCriticalSection();
    PS1_SwCARD_EvSpIOE = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, null);
    PS1_SwCARD_EvSpERROR = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, null);
    PS1_SwCARD_EvSpTIMOUT = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, null);
    PS1_SwCARD_EvSpNEW = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, null);
    PS1_HwCARD_EvSpIOE = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, null);
    PS1_HwCARD_EvSpERROR = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, null);
    PS1_HwCARD_EvSpTIMOUT = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, null);
    PS1_HwCARD_EvSpNEW = OpenEvent(HwCARD, EvSpNEW, EvMdNOINTR, null);
    EnableEvent(PS1_SwCARD_EvSpIOE);
    EnableEvent(PS1_SwCARD_EvSpERROR);
    EnableEvent(PS1_SwCARD_EvSpTIMOUT);
    EnableEvent(PS1_SwCARD_EvSpNEW);
    EnableEvent(PS1_HwCARD_EvSpIOE);
    EnableEvent(PS1_HwCARD_EvSpERROR);
    EnableEvent(PS1_HwCARD_EvSpTIMOUT);
    EnableEvent(PS1_HwCARD_EvSpNEW);
    ExitCriticalSection();
    InitCARD(1);
    StartCARD();
    _bu_init();
    _card_auto(1);
    if (PS1_TestCard(chan) == 2)
        PS1_Checksum = PS1_CardFilenameChecksum(chan);
}

/* 46270 8016AA70 -O2 -msoft-float */
u8 PS1_FormatFs(u8 param_1)
{
    u8 fs[8];

    FntPrint(s__FORMATING_8012ac84);
    sprintf(fs, s_bu02x_801cf040, param_1);
    if (format(fs) == 1)
    {
        FntPrint(s__Done_801cf048);
        return 0;
    }
    else
    {
        FntPrint(s__Error_in_formatting_8012ac90);
        return 0xFF;
    }
}

/* 462F4 8016AAF4 -O2 -msoft-float */
void PS1_InitSaveRayAndFilenames(u8 param_1)
{
    struct DIRENTRY files[15];
    struct DIRENTRY *cur_file;
    u8 name_start[8];
    s32 nbre_files;
    u8 cnt1;
    u8 cnt2 = 0;

    sprintf(name_start, s_bu02x_801cf040, param_1);
    nbre_files = PS1_GetNbreFiles(name_start, files);
    for (cnt1 = 0; cnt1 < nbre_files; cnt1++)
    {
        cur_file = &files[cnt1];
        if (strncmp(cur_file->name, s_BISLUS00005_8012aca8, 12) == 0)
        {
            strncpy(save_ray[cnt2 + 1], &cur_file->name[12], 3);
            strncpy(&PS1_SaveFilenames[cnt2][0], name_start, 6);
            strncpy(&PS1_SaveFilenames[cnt2][5], cur_file->name, 21);
            cnt2++;
            if (cnt2 > 2)
                break;
        }
    }
    for (; cnt1 = cnt2, cnt2 < 3; cnt2++)
        *PS1_SaveFilenames[cnt2] = *save_ray[cnt2 + 1] = 0;
}

/* 46464 8016AC64 -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/card", PS1_WriteSave);
#else
/*
score of 295
returns u8 instead? see SaveGameOnDisk and betw1 var
*/
/* TODO: macro for 0x80 size? also in PS1_LoadSave */
s32 PS1_WriteSave(u8 chan_par, u8 slot_par)
{
    u8 *pbVar1;
    int event_res;
    long fd;
    s32 betw1;
    s32 betw2;
    int cnt;
    s32 betw3;
    s32 *frame_from;
    s32 *frame_to;
    u8 *devname;
    s32 chan_local;
    s32 slot_local;
    u8 test_4[32];
    u8 saveicon1[128];
    u8 saveicon2and3[128];
    u8 saveiconpalette[32];
    s32 local_c0;
    s32 local_bc;
    s32 local_b8;
    s32 local_b4;
    s32 local_b0;
    s32 local_ac;
    s32 local_a8;
    s32 local_a4;
    CardFrame0 card_frame0;
    u8 local_20;
    u8 *test_2;
    u8 *new_var;
    s32 test_3;

    __builtin_memcpy(saveicon1, PS1_SaveIcon1, sizeof(PS1_SaveIcon1));
    __builtin_memcpy(saveicon2and3, PS1_SaveIcon2and3, sizeof(PS1_SaveIcon2and3));
    __builtin_memcpy(saveiconpalette, PS1_SaveIconPalette, sizeof(PS1_SaveIconPalette));
    _card_info(chan_par);
    event_res = PS1_TestSwCARD();
    if (event_res - 1U >= 2)
    {
        if (event_res == 3)
        {
            PS1_TestHwCARDOnce();
            _card_clear(chan_par);
            PS1_TestHwCARD();
        }
        PS1_TestSwCARDOnce();
        _card_load(chan_par);
        PS1_TestSwCARD();
        FntPrint(s__Saving_file_8012add8);
        devname = &PS1_SaveFilenames[slot_par - 1][0];
        if (devname[0] == 0)
        {
            sprintf(devname, s_bu02xss4u_8012ade8, chan_par, s_BISLUS00005_8012aca8, save_ray[slot_par], (u16) PS1_GlobalTimer);
        }
        fd = open(devname, 0x10200);
        if (fd != -1)
        {
            PS1_WriteWiSaveZone();
            loadInfoRay[slot_par - 1].num_cages = 0;
            cnt = 0;
            do
            {
                loadInfoRay[slot_par - 1].num_cages = loadInfoRay[slot_par - 1].num_cages + (wi_save_zone[cnt].nb_cages);
                cnt = cnt + 1;
            } while (cnt < 24);
            chan_local = loadInfoRay[slot_par - 1].num_cages * 100;
            card_frame0.sc_magic[0] = 'S';
            card_frame0.sc_magic[1] = 'C';
            card_frame0.icon_display_flag = 0x13;
            card_frame0.block_num = 1;
            sprintf(card_frame0.Rayman_save_ray_pct, s_Rayman_s_03d_8012adf8, save_ray[slot_par], (short) (chan_local / 102));
            strncpy(card_frame0.Maga, s_Maga_801cf050, 0x1c);
            __builtin_memcpy(card_frame0.icon_palette, saveiconpalette, sizeof(saveiconpalette));
            write(fd, &card_frame0, 0x80);
            write(fd, saveicon1, 0x80);
            write(fd, saveicon2and3, 0x80);
            write(fd, saveicon2and3, 0x80);
            write(fd, &nb_continue, 0x80);
            write(fd, wi_save_zone, 0x80);
            write(fd, &RayEvts, 0x80);
            write(fd, &poing, 0x80);
            write(fd, &status_bar, 0x80);
            write(fd, &ray.hit_points, 0x80);
            write(fd, save_zone, 0xa80);
            write(fd, bonus_perfect, 0x80);
            write(fd, &options_jeu, 0x80);
            if (dans_la_map_monde)
            {
                write(fd, &num_world_choice, 0x80);
                write(fd, &xmap, 0x80);
                write(fd, &ymap, 0x80);
                local_20 = (u8) (ray.flags >> 0xe) & 1;
                write(fd, &local_20, 0x80);
            }
            else
            {
                write(fd, &world_index, 0x80);
                write(fd, &xwldmapsave, 0x80);
                write(fd, &ywldmapsave, 0x80);
                write(fd, &dir_on_wldmap, 0x80);
            }
            write(fd, &finBosslevel, 0x80);
            close(fd);
            CHANGE_STAGE_NAMES();
            PS1_Checksum = PS1_CardFilenameChecksum(chan_par);
            betw1 = 1;
        }
        else
        {
            FntPrint(s__Cant_open_file_8012ae0c);
            betw1 = 0xfd;
        }
    }
    else
    {
        FntPrint(s__Cannot_create_file_8012ae20);
        betw1 = 0xfc;
    }
    return betw1;
}
#endif

/* 46AE8 8016B2E8 -O2 -msoft-float */
u8 *FUN_8016b2e8(u8 param_1, u8 param_2, u8 *param_3)
{
    struct DIRENTRY files[15];
    struct DIRENTRY *cur_file;
    u8 name_start[8];
    s32 nbre_files;
    u8 cnt1;
    u8 cnt2 = 0;

    sprintf(name_start, s_bu02x_801cf040, param_1);
    nbre_files = PS1_GetNbreFiles(name_start, files);
    for (cnt1 = 0; cnt1 < nbre_files; cnt1++)
    {
        cur_file = &files[cnt1];
        if (strncmp(cur_file->name, s_BISLUS00005_8012aca8, 12) == 0)
        {
            cnt2++;
            if (cnt2 == param_2)
            {
                sprintf(param_3, s_bu02xss_8012ae38, param_1, s_BISLUS00005_8012aca8, &cur_file->name[12]);
                return param_3;
            }
        }
    }
    return null;
}

/* 46BFC 8016B3FC -O2 -msoft-float */
s32 SaveGameOnDisk(u8 slot)
{
    u8 filename[32];
    s32 res = NBRE_SAVE;

    if (res != 0)
    {
        PS1_CheckCardChanged();
#ifdef PLATFORM_PSYZ
        strcpy((char *)filename, (const char *)PS1_SaveFilenames[slot - 1]);
#else
        strcpy(filename, PS1_SaveFilenames[slot - 1]);
#endif
        if (filename[0] != '\0')
#ifdef PLATFORM_PSYZ
            erase (filename);
        strncpy((char *)&PS1_SaveFilenames[slot - 1][17], (const char *)save_ray[slot], 3);
#else
            delete (filename);
        strncpy(&PS1_SaveFilenames[slot - 1][17], save_ray[slot], 3);
#endif
        res = (u8) PS1_WriteSave(0, slot);
    }
    return res;
}

/* 46CA0 8016B4A0 -O2 -msoft-float */
s32 SaveFileRead(s32 file_desc, void *buf, s16 n_bytes)
{
    s16 n_read;
    u8 i = 0;

    do
    {
        n_read = read(file_desc, buf, n_bytes);
    } while (n_read == -1 && i++ < 10);
    return n_read;
}

/* 46D24 8016B524 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/card", PS1_LoadSave);
#else
/*
matches, but options_jeu as memcpy somehow?
SaveFileRead() macro _only_ for this function?
*/
void PS1_LoadSave(s32 param_1, u8 *filename)
{
    s32 file_desc = open(filename, O_RDONLY);
    u16 file_buffer[64];

    if (file_desc != -1)
    {
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&nb_continue, file_buffer, sizeof(nb_continue));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&wi_save_zone, file_buffer, sizeof(wi_save_zone));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&RayEvts, file_buffer, sizeof(RayEvts));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&poing, file_buffer, sizeof(poing));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&status_bar, file_buffer, sizeof(status_bar));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&ray.hit_points, file_buffer, sizeof(ray.hit_points));
        SaveFileRead(file_desc, save_zone, sizeof(save_zone));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(bonus_perfect, file_buffer, sizeof(bonus_perfect));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        /*__builtin_memcpy(&options_jeu.Jump, &file_buffer[8], 22);*/
        /* also tried assigning to another local with OptionsJeu * or u16 * type beforehand */
        options_jeu.Jump = file_buffer[8];
        options_jeu.Fist = file_buffer[9];
        options_jeu.field6_0x14 = file_buffer[10];
        options_jeu.Action = file_buffer[11];
        options_jeu.Music = file_buffer[12];
        options_jeu.Soundfx = file_buffer[13];
        options_jeu.StereoEnabled = file_buffer[14];
        options_jeu.field11_0x1e = file_buffer[15];
        options_jeu.field12_0x20 = file_buffer[16];
        options_jeu.field13_0x22 = file_buffer[17];
        options_jeu.field14_0x24 = file_buffer[18];
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&world_index, file_buffer, sizeof(world_index));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&xwldmapsave, file_buffer, sizeof(xwldmapsave));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&ywldmapsave, file_buffer, sizeof(ywldmapsave));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&dir_on_wldmap, file_buffer, sizeof(dir_on_wldmap));
        SaveFileRead(file_desc, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&finBosslevel, file_buffer, sizeof(finBosslevel));
        close(file_desc);
        PS1_LoadWiSaveZone();
        POINTEUR_BOUTONS_OPTIONS_BIS();
    }
    else
        FntPrint(s__Cant_open_file_8012ae0c);
}
#endif

/* 470E4 8016B8E4 -O2 -msoft-float */
void LoadGameOnDisk(u8 slot)
{
    if (NBRE_SAVE != 0)
    {
        PS1_CheckCardChanged();
        PS1_LoadSave(0, PS1_SaveFilenames[slot - 1]);
    }
}

/* 47134 8016B934 -O2 -msoft-float */
s32 LoadInfoGame(u8 slot)
{
    u8 unk_1[32];
    s32 file = open(PS1_SaveFilenames[slot - 1], O_RDONLY); /* TODO: slot - 1 macro? */
    u8 file_buffer[128];
    s32 i;

    if (file == -1)
        return 1;
    else
    {
        SaveFileRead(file, file_buffer, sizeof(file_buffer));
        SaveFileRead(file, file_buffer, sizeof(file_buffer));
        SaveFileRead(file, file_buffer, sizeof(file_buffer));
        SaveFileRead(file, file_buffer, sizeof(file_buffer));
        SaveFileRead(file, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&nb_continue, file_buffer, sizeof(nb_continue));
        SaveFileRead(file, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&wi_save_zone, file_buffer, sizeof(wi_save_zone));
        SaveFileRead(file, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&RayEvts, file_buffer, sizeof(RayEvts));
        SaveFileRead(file, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&poing, file_buffer, sizeof(poing));
        SaveFileRead(file, file_buffer, sizeof(file_buffer));
        __builtin_memcpy(&status_bar, file_buffer, sizeof(status_bar));
        close(file);

        loadInfoRay[slot - 1].num_continues = nb_continue;
        loadInfoRay[slot - 1].num_cages = 0;
        for (i = 0; i < 24; i++)
            loadInfoRay[slot - 1].num_cages += wi_save_zone[i].nb_cages;
        loadInfoRay[slot - 1].num_lives = status_bar.num_lives;
        loadInfoRay[slot - 1].num_wiz = status_bar.num_wiz;
        return 0;
    }
}

/* 473E4 8016BBE4 -O2 -msoft-float */
void FUN_8016bbe4(void)
{
    u8 *filename;

    if (NBRE_SAVE != 0)
    {
        PS1_CheckCardChanged();
        filename = PS1_SaveFilenames[fichier_selectionne - 1];
        if (filename[0] != '\0')
#ifdef PLATFORM_PSYZ
            erase (filename);
#else
            delete (filename);
#endif
        PS1_Checksum = PS1_CardFilenameChecksum(0);
        *save_ray[fichier_selectionne] = '\0';
        *PS1_SaveFilenames[fichier_selectionne - 1] = '\0';
    }
}

/* 47488 8016BC88 -O2 -msoft-float */
u8 PS1_GetNbreSave3(u8 param_1)
{
    u8 saves_found = 0;
    u8 blocks_used = 0;
    s32 nbre_files;
    struct DIRENTRY files[15];
    u8 name_start[8];
    u8 i;
    u8 buf[128];
    u8 dev_name[32];
    s32 fd;
    u8 res;

    sprintf(name_start, s_bu02x_801cf040, param_1);
    nbre_files = PS1_GetNbreFiles(name_start, files);
    for (i = 0; i < nbre_files; i++)
    {
        sprintf(dev_name, s_ss_801cf058, name_start, files[i].name);
        fd = open(dev_name, O_RDONLY);
        SaveFileRead(fd, buf, sizeof(buf));
        blocks_used += buf[3];
        close(fd);
        if (strncmp(files[i].name, s_BISLUS00005_8012aca8, 12) == 0)
            saves_found++;
    }
    res = saves_found - (u8) (blocks_used - 15); /* underflow? couldn't retype */
    MIN_2(res, 3);
    return res;
}

/* 475C4 8016BDC4 -O2 -msoft-float */
s32 PS1_CardFilenameChecksumChanged(void)
{
    return PS1_Checksum != PS1_CardFilenameChecksum(0);
}

/* 475F4 8016BDF4 -O2 -msoft-float */
s32 PS1_TestCardZero(void)
{
    return PS1_TestCard(0) == 0;
}

/* 47618 8016BE18 -O2 -msoft-float */
s16 PS1_CardUnformatted(void)
{
    s32 unk_1 = true; /* least ugly permuter suggestion imo */
    if (unk_1 && PS1_TestCard(0) != 2)
    {
        VSync(0);
        VSync(0);
        VSync(0);
        return PS1_TestCard(0) != 2;
    }
    else
        return false;
}

/* 4767C 8016BE7C -O2 -msoft-float */
u8 PS1_GetNbreSave2(void)
{
    return PS1_GetNbreSave3(0);
}

/* 4769C 8016BE9C -O2 -msoft-float */
s32 FUN_8016be9c(void)
{
    return (s16) PS1_CardFilenameChecksumChanged();
}

/* 476C0 8016BEC0 -O2 -msoft-float */
void FUN_8016bec0(void)
{
    PS1_FormatFs(0);
    PS1_Checksum = PS1_CardFilenameChecksum(0);
}