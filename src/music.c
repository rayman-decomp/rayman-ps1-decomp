#include "music.h"

#ifdef PLATFORM_PSYZ
#include <libapi.h>
#endif

/* TODO: PS1_TrkFiles and PS1_TracksExist are different size? correct? */

#define PS1_SECTORS_P_SEC 75
#define PS1_SEC_P_MIN 60
#define PS1_LEVEL_MUSIC_IND(ind) PS1_LevelMusicTable[PS1_LevelMusic_World][PS1_LevelMusic_Level][ind]
#define PS1_LEVEL_MUSIC_CUR PS1_LEVEL_MUSIC_IND(PS1_LevelMusic_CmdInd)

const u8 s__CDPlayer_TEST_80125c28[] = "\n\n\n\t\t CD-Player TEST\n";
const u8 s_Fade02d_80125c40[] = "Fade:%02d ";
const u8 s_ind_faded_80125c4c[] = "ind_fade:%d\n";
const u8 s_stat_02x_trackd_80125c5c[] = "stat  =%02x track=%d";
const u8 s_Ready_data_d_Complete_d_80125c74[] = "Ready data #%d, Complete #%d\n";
const u8 s_occuped_etat_d_pcomd_80125c94[] = "occupe=%d, etat= %d, pcom=%d\n";
const u8 s_intr_datar3d_intr_compl3d_80125cb4[] = "intr_datar=%3d intr_compl=%3d\n";
const u8 s_Deb_2d2d2d_80125cd4[] = "Deb: %2d:%2d:%2d\n";
const u8 s_Pos_2d2d2d_08x_80125ce8[] = "Pos: %2d:%2d:%2d (%08x)\n";
const u8 s_Fin_08x_80125d04[] = "Fin: %08x\n";
const u8 s_Num_seqddd_typd_80125d10[] = "Num_seq:%d-%d-%d typ:%d\n";
const u8 s_iseosd_80125d2c[] = "iseos:%d\n";
const u8 s_will_anticips_fadeouts_80125d38[] = "will anticip:%s  fadeout:%s\n";
const u8 s_2d_markddd_80125d58[] = "%2d mark:%d-%d-%d\n";

#ifdef BSS_DEFS
s16 D_801E64B0;
s16 PS1_ScrollLockedAudio;
CdlLOC D_801F41D0[53];
s32 D_801F7CA8;
s16 PS1_LevelMusic_World;
s16 PS1_LevelMusic_Level;
s16 PS1_LevelMusic_CmdInd;
s16 D_801F9940;
s32 PS1_CurTrack;
u8 PS1_Music_etat;
u8 PS1_Music_track;
u8 PS1_Music_Amin;
u8 PS1_Music_Asec;
u8 PS1_Music_Aframe;
u8 PS1_Music_LevelHL;
s16 PS1_Music_Complete_data;
s16 PS1_Music_Fade;
s32 PS1_Music_Fin[53];
s16 PS1_Music_Ready_data;
s16 PS1_Music_fadeout;
s16 PS1_Music_ind_fade;
s32 PS1_Music_intr_compl;
s32 PS1_Music_intr_datar;
u8 PS1_Music_occupe;
s16 PS1_Music_will_anticip;
s16 D_801F5798;
s16 D_801E4D10;
s32 D_801E5240;
s32 D_801E57C0[53];
s32 D_801F42A8[53];
s16 D_801F5248;
s16 D_801F7ED0;
s16 PS1_Mark_access_num;
s16 PS1_Mark_seq_num;
s16 PS1_Mark_data;
CdlLOC D_801F4E68;
u8 PS1_CdMode;
s32 D_801F54B0[53];
s32 D_801F7AA8[53];
s32 D_801F7D88[53];
u32 PS1_TrackSizes[53];
s16 PS1_TracksExist[53];
s16 D_801E4B78;
s16 D_801FAA50;
s16 D_801F7A90[4];
s16 D_801F7C80;
CdlLOC D_801E4EF8;
s32 D_801F4FA0;
s16 D_801FA570;
#endif

/* B848 80130048 -O2 -msoft-float */
void FUN_80130048(void)
{
    PadStop();
    StopPAD();
    ResetGraph(3);
    stop_cd();
    CdSync(null, null);
    SsVabClose(D_801F5798);
    SsEnd();
    StopCallback();
}

/* B8AC 801300AC -O2 -msoft-float */
#ifdef PLATFORM_PSYZ
void PS1_CdReadyCallback(u_char status, u_char *result)
#else
void PS1_CdReadyCallback(s32 status, u8 *result)
#endif
{
    PS1_Music_intr_datar = status;
    switch (status)
    {
    case CdlDataReady:
        D_801E4D10 = false;
        PS1_Music_Ready_data++;
        PS1_Music_etat = result[0];
        PS1_Music_track = result[1];
        PS1_Music_Amin = result[3];
        PS1_Music_Asec = result[4];
        PS1_Music_Aframe = result[5];
        PS1_Music_LevelHL = result[6] + result[7];
        D_801F7CA8 = (btoi(PS1_Music_Amin) << 16) + (btoi(PS1_Music_Asec) << 8) + btoi(PS1_Music_Aframe);
        if (PS1_Music_fadeout && D_801F7CA8 > D_801F42A8[PS1_CurTrack])
        {
            PS1_Music_fadeout = false;
            FUN_80131e40();
        }
        if (PS1_Music_will_anticip && D_801F7CA8 > D_801E57C0[PS1_CurTrack])
        {
            PS1_Music_will_anticip = false;
            PS1_PlayMusic();
        }
        if (D_801F7ED0 && D_801F7CA8 > D_801E5240)
        {
            D_801F7ED0 = false;
            FUN_80131e40();
        }
        if (D_801CEFD8)
            CdControl(CdlPause, null, null);
        break;
    case CdlDiskError:
        D_801E4D10 = true;
        D_801CEEBC = true;
        break;
    case CdlDataEnd:
        D_801CEEBC = true;
        if (D_801F5248)
        {
            D_801F5248 = false;
            D_801F9940 = 0;
        }
        if (D_801F9940 == 1)
            PS1_PlayMusic();
        break;
    }
}

/* BB6C 8013036C -O2 -msoft-float */
#ifdef PLATFORM_PSYZ
void PS1_CdSyncCallback(u_char status, u_char *result)
#else
void PS1_CdSyncCallback(s32 status, u8 *result)
#endif
{
    PS1_Music_Complete_data++;
    PS1_Music_intr_compl = status;
    if (status == CdlComplete)
    {
        D_801E4D10 = false;
        PS1_Music_Ready_data = 0;
        if (D_801F9940 == 1 && PS1_Music_pcom == CdlPause && !D_801CEFD8)
        {
            if (D_801F5248)
            {
                D_801F9940 = 0;
                D_801F5248 = false;
            }
            else
                PS1_PlayMusic();
        }
    }
}

/* BC28 80130428 -O2 -msoft-float */
void PS1_Mark_Callback(s16 access_num, s16 seq_num, s16 data)
{
    PS1_Mark_access_num = access_num;
    PS1_Mark_seq_num = seq_num;
    PS1_Mark_data = data;
    PS1_Mark_counter++;
}

/* BC5C 8013045C -O2 -msoft-float */
void FUN_8013045c(void)
{
    if (D_801CEEA6 && !SsIsEos(PS1_Music_access_num, 0))
    {
        PS1_PlayMusic();
        D_801CEEA6 = false;
    }
    if (D_801CEEA8)
    {
        D_801CEEA8 = false;
        PS1_Music_pcom = CdlSetloc;
        CdControl(PS1_Music_pcom, (u8 *) &D_801F4E68, null);
    }
    if (PS1_Music_Fade != 0 && !D_801CEFD8)
        PS1_Music_Apply_Fade();
}

/* BD14 80130514 -O2 -msoft-float */
void PS1_SsSetSerialVolA(s16 vol)
{
    SsSetSerialVol(SS_SERIAL_A, vol, vol);
}

/* BD40 80130540 -O2 -msoft-float */
void FUN_80130540(void)
{
    ResetCallback();
}

/* BD60 80130560 -O2 -msoft-float */
void PS1_Cd_Callbacks_Disable(void)
{
    CdSyncCallback(null);
    CdReadyCallback(null);
}

/* BD88 80130588 -O2 -msoft-float */
void PS1_Mark_Callback_Disable(void)
{
    SsSetMarkCallback(PS1_Music_access_num, 0, null);
}

/* BDB4 801305B4 -O2 -msoft-float */
void PS1_Cd_Callbacks_Enable(void)
{
    CdSyncCallback(PS1_CdSyncCallback);
    CdReadyCallback(PS1_CdReadyCallback);
}

/* BDEC 801305EC -O2 -msoft-float */
void PS1_Mark_Callback_Enable(void)
{
    SsSetMarkCallback(PS1_Music_access_num, 0, PS1_Mark_Callback);
}

/* BE1C 8013061C -O2 -msoft-float */
void PS1_InitMusic(void)
{
    u8 *mode = &PS1_CdMode;

    *mode = CdlModeRept | CdlModeAP | CdlModeDA;
    PS1_Music_pcom = CdlSetmode;
    CdControlB(PS1_Music_pcom, mode, null);
    PS1_InitTracks();
    PS1_SetMusicVolume(13);
}

/* BE6C 8013066C -O2 -msoft-float */
void FUN_8013066c(void)
{
    D_801E64B0 = false;
    PS1_ScrollLockedAudio = false;
}

/* BE84 80130684 -O2 -msoft-float */
void FUN_80130684(void)
{
    u8 *occupe_str;
    u8 *anticip_str;
    u8 *fadeout_str;

    FntPrint(s__CDPlayer_TEST_80125c28);
    FntPrint(s_Fade02d_80125c40, PS1_Music_Fade);
    FntPrint(s_ind_faded_80125c4c, PS1_Music_ind_fade);
    FntPrint(s_stat_02x_trackd_80125c5c, btoi(PS1_Music_etat), PS1_Music_track);

    if (PS1_Music_occupe)
        occupe_str = s_idle_801ceec4;
    else
        occupe_str = s_busy_801ceecc;
    FntPrint(s_s_801ceec0, occupe_str);
    FntPrint(s_Ready_data_d_Complete_d_80125c74, PS1_Music_Ready_data, PS1_Music_Complete_data);
    FntPrint(s_occuped_etat_d_pcomd_80125c94, PS1_Music_occupe, PS1_Music_etat, PS1_Music_pcom);
    FntPrint(s_intr_datar3d_intr_compl3d_80125cb4, PS1_Music_intr_datar, PS1_Music_intr_compl);
    FntPrint(
        s_Deb_2d2d2d_80125cd4,
        btoi(D_801F41D0[PS1_CurTrack].minute),
        btoi(D_801F41D0[PS1_CurTrack].second),
        btoi(D_801F41D0[PS1_CurTrack].sector)
    );
    FntPrint(
        s_Pos_2d2d2d_08x_80125ce8,
        btoi(PS1_Music_Amin),
        btoi(PS1_Music_Asec),
        btoi(PS1_Music_Aframe),
        D_801F7CA8
    );
    FntPrint(s_Fin_08x_80125d04, PS1_Music_Fin[PS1_CurTrack]);
    FntPrint(s_Num_seqddd_typd_80125d10, PS1_LevelMusic_World, PS1_LevelMusic_Level, PS1_LevelMusic_CmdInd, D_801F9940);
    FntPrint(s_iseosd_80125d2c, SsIsEos(PS1_Music_access_num, 0));

    if (PS1_Music_will_anticip)
        anticip_str = s_yes_801ceed4;
    else
        anticip_str = s_no_801ceed8;

    if (PS1_Music_fadeout)
        fadeout_str = s_yes_801ceed4;
    else
        fadeout_str = s_no_801ceed8;
    FntPrint(s_will_anticips_fadeouts_80125d38, anticip_str, fadeout_str);
}

void FUN_801309b0(void) {}

/* C1B8 801309B8 -O2 -msoft-float */
u8 FUN_801309b8(u8 param_1, u8 param_2, u8 *param_3, u8 param_4)
{
    u8 unk_1 = btoi(param_1) + btoi(param_2) + btoi(*param_3);

    if (unk_1 > param_4)
    {
        unk_1 -= 1;
        unk_1 -= param_4;
        *param_3 = itob(unk_1);
        return 1;
    }
    else
    {
        *param_3 = itob(unk_1);
        return 0;
    }
}

/* C298 80130A98 -O2 -msoft-float */
void FUN_80130a98(CdlLOC *param_1, CdlLOC *param_2, CdlLOC *param_3)
{
    param_3->sector = 0;
    param_3->second = FUN_801309b8(param_1->sector, param_2->sector, &param_3->sector, PS1_SECTORS_P_SEC - 1);
    param_3->minute = FUN_801309b8(param_1->second, param_2->second, &param_3->second, PS1_SEC_P_MIN - 1);
    FUN_801309b8(param_1->minute, param_2->minute, &param_3->minute, PS1_SEC_P_MIN - 1); /* TODO: should this be min/hour instead? */
}

/* C318 80130B18 -O2 -msoft-float */
void FUN_80130b18(u32 param_1, CdlLOC *param_2)
{
    param_2->sector = itob(param_1 % PS1_SECTORS_P_SEC);
    param_2->second = itob(param_1 / PS1_SECTORS_P_SEC % PS1_SEC_P_MIN);
    param_2->minute = itob(param_1 / PS1_SECTORS_P_SEC / PS1_SEC_P_MIN);
}

/* C3C4 80130BC4 -O2 -msoft-float */
s32 FUN_80130bc4(CdlLOC loc)
{
    return btoi(loc.sector) + (btoi(loc.second) << 8) + (btoi(loc.minute) << 16);
}

/* C458 80130C58 -O2 -msoft-float */
s32 FUN_80130c58(s32 param_1)
{
    return (param_1 % PS1_SECTORS_P_SEC) +
           (((param_1 / PS1_SECTORS_P_SEC) % PS1_SEC_P_MIN) << 8) +
           ((param_1 / (PS1_SECTORS_P_SEC * PS1_SEC_P_MIN)) << 16); /* can't say i follow this */
}

/* C500 80130D00 -O2 -msoft-float */
s32 FUN_80130d00(s32 param_1, s32 param_2)
{
    /* add zeroth, first and second 8-bit parts of param_1/param_2? */
    s32 unk_0 = (param_1 & 0xFF) + (param_2 & 0xFF);
    s32 unk_1 = ((param_1 >> 8) & 0xFF) + ((param_2 >> 8) & 0xFF);
    s32 unk_2 = (((param_1 >> 16) & 0xFF) + ((param_2 >> 16) & 0xFF));

    /* then ??? */
    return ((unk_0 / PS1_SECTORS_P_SEC) << 8) + (unk_0 % PS1_SECTORS_P_SEC) +
           ((unk_1 % PS1_SEC_P_MIN) << 8) + ((unk_1 / PS1_SEC_P_MIN) << 16) +
           (unk_2 << 16);
}

/* C5C0 80130DC0 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/music", PS1_InitTracks);
#else
/*
duplication?
any common.h return type seems to work
c89 3.6.6.4 The return statement: behavior is undefined
*/

/* nope */
static inline s32 PS1_InitTracks_1(CdlLOC param_1, s32 param_2)
{
    return FUN_80130d00(FUN_80130bc4(param_1), param_2);
}

#define PS1_InitTracks_2(param_1, param_2) FUN_80130d00(FUN_80130bc4(param_1), param_2)

u8 PS1_InitTracks(void)
{
    u32 size;
    CdlLOC unk_2;
    s32 unk_3[53];
    s32 unk_4;
    CdlLOC *unk_5;
    s32 unk_6;
    CdlLOC *unk_7;
    s32 unk_8;
    s32 unk_1 = true;
    s32 i = 0;
    s32 *track_sizes = &PS1_TrackSizes[i];
    s16 *tracks_exist = &PS1_TracksExist[i];

    while (i < (s16) LEN(PS1_TrkFiles))
    {
        size = PS1_TrkFiles[i].file.size;
        if (size != 0)
        {
            *track_sizes = (size >> 11) - 40;
            *tracks_exist = unk_1;
        }
        else
        {
            *tracks_exist = false;
            *track_sizes = 0;
        }
        track_sizes++;
        tracks_exist++;
        i++;
    }

    for (i = 0; i < (s16) LEN(PS1_TrkFiles); i++)
    {
        if (PS1_TracksExist[i])
        {
            D_801F41D0[i] = PS1_TrkFiles[i].file.pos;
            PS1_TrackSizes[i] = (PS1_TrkFiles[i].file.size >> 11) - 40;
            FUN_80130b18(PS1_TrackSizes[i], &unk_2);
            unk_3[i] = FUN_80130bc4(unk_2);
        }
    }

    unk_4 = FUN_80130c58(1500);
    for (i = 0; i < (s16) LEN(PS1_TrkFiles); i++)
    {
        if (PS1_TracksExist[i])
        {
            unk_5 = &D_801F41D0[i];
            PS1_Music_Fin[i] = FUN_80130d00(FUN_80130bc4(*unk_5), unk_3[i]);
            if (PS1_TrackSizes[i] < 1500)
                D_801F7D88[i] = FUN_80130d00(FUN_80130bc4(*unk_5), unk_3[i]);
            else
                D_801F7D88[i] = FUN_80130d00(FUN_80130bc4(*unk_5), unk_4);
        }
    }

    unk_6 = FUN_80130c58(1388);
    for (i = 0; i < (s16) LEN(PS1_TrkFiles); i++)
    {
        if (PS1_TracksExist[i])
        {
            unk_3[i] = FUN_80130c58(PS1_TrackSizes[i] - 112);
            unk_7 = &D_801F41D0[i];
            D_801F42A8[i] = FUN_80130d00(FUN_80130bc4(*unk_7), unk_3[i]);
            if (PS1_TrackSizes[i] < 1500)
                D_801F7AA8[i] = FUN_80130d00(FUN_80130bc4(*unk_7), unk_3[i]);
            else
                D_801F7AA8[i] = FUN_80130d00(FUN_80130bc4(*unk_7), unk_6);
        }
    }

    unk_8 = FUN_80130c58(1404);
    for (i = 0; i < (s16) LEN(PS1_TrkFiles); i++)
    {
        if (PS1_TracksExist[i])
        {
            unk_3[i] = FUN_80130c58(PS1_TrackSizes[i] - 96);
            unk_7 = &D_801F41D0[i];
            D_801E57C0[i] = FUN_80130d00(FUN_80130bc4(*unk_7), unk_3[i]);
            if (PS1_TrackSizes[i] < 1500)
                D_801F54B0[i] = FUN_80130d00(FUN_80130bc4(*unk_7), unk_3[i]);
            else
                D_801F54B0[i] = FUN_80130d00(FUN_80130bc4(*unk_7), unk_8);
        }
    }
}
#endif

/* CC74 80131474 -O2 -msoft-float */
s16 FUN_80131474(s16 *param_1, s16 param_2, s16 param_3)
{
    do
    {
        if (*param_1 == param_3)
            break;
        param_3++;
    } while (param_3 < param_2);

    return param_3 != param_2;
}

/* kinda unreadable still due to unknowns, the shift in table_ind calc */
/* CCC4 801314C4 -O2 -msoft-float */
void FUN_801314c4(void)
{
    D_801CEEA8 = false;
    D_801E4B78 = PS1_LevelMusic_CmdInd + 1;
    do
    {
        D_801F7A90[D_801CEEB8++] = D_801E4B78;
        D_801FAA50 = PS1_LEVEL_MUSIC_IND(D_801E4B78).cmd_and_flags & 0xF;
        switch (D_801FAA50)
        {
        case 1:
            D_801CEEBA = true;
            D_801F4E68 = D_801F41D0[PS1_LEVEL_MUSIC_IND(D_801E4B78).param];
            D_801CEEA8 = true;
            break;
        case 3:
            D_801E4B78 = PS1_LEVEL_MUSIC_IND(D_801E4B78).param;
            break;
        }
    } while (
        !D_801CEEA8 &&
        (D_801CEEB8 < (s16) LEN(D_801F7A90)) &&
        !FUN_80131474(D_801F7A90, D_801CEEB8, D_801E4B78)
    );
}

/* CE78 80131678 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/music", PS1_PlayMusic);
#else
/* too many unknowns, hard to read, unsure about some labels */
void PS1_PlayMusic(void)
{
    s16 done;
    u8 *mode;
    CdlLOC unk_3;
    CdlLOC unk_4;
    CdlLOC unk_1;
    CdlLOC *unk_2;

    D_801FA570 = false;
    done = false;
    if (++PS1_LevelMusic_CmdInd == 4) /* TODO: what should i take LEN() of? */
        PS1_LevelMusic_CmdInd = 0;

    while (!done)
    {
        mode = &PS1_CdMode;
        D_801F9940 = PS1_LEVEL_MUSIC_CUR.cmd_and_flags & 0xF;
        PS1_Music_will_anticip = PS1_LEVEL_MUSIC_CUR.cmd_and_flags & 0x10;
        PS1_Music_fadeout = PS1_LEVEL_MUSIC_CUR.cmd_and_flags & 0x80;
        D_801F7ED0 = PS1_LEVEL_MUSIC_CUR.cmd_and_flags & 0x20;
        switch (D_801F9940)
        {
        case 1:
            D_801CEEBC = false;
            *mode = CdlModeRept | CdlModeAP | CdlModeDA;
            PS1_CurTrack = PS1_LEVEL_MUSIC_CUR.param;
            if (PS1_TracksExist[PS1_CurTrack])
            {
                PS1_Music_pcom = CdlSetmode;
                CdControl(PS1_Music_pcom, mode, null);
                unk_2 = &unk_1;
                if (D_801F7ED0)
                {
                    FUN_80130b18(D_801C4B28[D_801CEEA4++], unk_2);
                    FUN_80130a98(&D_801F41D0[PS1_CurTrack], unk_2, &D_801E4EF8);
                    if (D_801CEEA4 == (s16) LEN(D_801C4B28))
                        D_801CEEA4 = 0;
                    FUN_80130b18(1410, &unk_3);
                    FUN_80130a98(&D_801E4EF8, &unk_3, &unk_4);
                    D_801E5240 = FUN_80130bc4(unk_4);
                    PS1_Music_pcom = CdlSetloc;
                    CdControl(PS1_Music_pcom, (u8 *) &D_801E4EF8, null);
                }
                else
                {
                    PS1_Music_pcom = CdlSetloc;
                    CdControl(PS1_Music_pcom, (u8 *) &D_801F41D0[PS1_CurTrack], null);
                }

                done = true;
                if (D_801CEFD8 == 0)
                {
                    PS1_Music_pcom = CdlPlay;
                    CdControl(PS1_Music_pcom, null, null);
                }

                if (PS1_LEVEL_MUSIC_CUR.cmd_and_flags & 0x40)
                    FUN_80131e5c();
                else
                {
                    PS1_Music_Fade = 0;
                    PS1_SsSetSerialVolA(PS1_Music_Vol[PS1_CurTrack] * D_801F7C80 >> 7);
                }
            }
            else
            {
                D_801F9940 = 0;
                D_801CEEBC = true;
                done = true;
            }
            break;
        case 2:
            D_801F4FA0 = PS1_LEVEL_MUSIC_CUR.param;
            D_801CEEA6 = true;
            SsSeqPlay(PS1_Music_access_num, SSPLAY_PLAY, 1);
            PS1_Mark_Callback_Enable();
            if (PS1_LEVEL_MUSIC_CUR.cmd_and_flags & 0x40)
            {
                SsSeqSetVol(PS1_Music_access_num, 0, 0);
                SsSeqSetCrescendo(PS1_Music_access_num, 127, 240);
            }
            FUN_801314c4();
            done = true;
            break;
        case 3:
            PS1_LevelMusic_CmdInd = PS1_LEVEL_MUSIC_CUR.param;
            break;
        case 0:
            done = true;
            break;
        }
    }
}
#endif

/* D3A8 80131BA8 -O2 -msoft-float */
void playLevelMusic(s16 world, s16 lvl)
{
    D_801CEEBC = false;
    PS1_Cd_Callbacks_Disable();
    FUN_8013066c();
    PS1_Cd_Pause();
    CdSync(0, null);
    PS1_Cd_Callbacks_Enable();
    PS1_LevelMusic_World = world;
    PS1_LevelMusic_Level = lvl;
    PS1_LevelMusic_CmdInd = -1;
    PS1_PlayMusic();
}

/* D428 80131C28 -O2 -msoft-float */
void start_cd_gros_rayman(void)
{
    playLevelMusic(0, 9);
}

/* D44C 80131C4C -O2 -msoft-float */
void start_cd_suspence(void)
{
    playLevelMusic(0, 6);
}

/* D470 80131C70 -O2 -msoft-float */
void start_cd_replay(void)
{
    playLevelMusic(0, 5);
}

/* D494 80131C94 -O2 -msoft-float */
void start_cd_credits(void)
{
    playLevelMusic(0, 8);
    stop_all_snd();
}

/* D4C0 80131CC0 -O2 -msoft-float */
void start_cd_gagne(void)
{
    D_801F5248 = true;
    FUN_80131e40();
    if (PS1_SongIsPlaying(21) == 0)
    {
        PS1_StopPlayingAllSnd();
        stop_all_snd();
        PS1_PlaySnd(13, 1);
    }
}

/* D518 80131D18 -O2 -msoft-float */
void start_cd_perdu(void)
{
    FUN_8016617c();
    PS1_StopPlayingAllSnd();
    playLevelMusic(0, 1);
}

/* D54C 80131D4C -O2 -msoft-float */
void start_cd_rap(void)
{
    playLevelMusic(0, 3);
}

/* D570 80131D70 -O2 -msoft-float */
void start_cd_gameover(void)
{
    playLevelMusic(0, 2);
}

/* D594 80131D94 -O2 -msoft-float */
void start_cd_continue(void)
{
    playLevelMusic(0, 5);
}

/* D5B8 80131DB8 -O2 -msoft-float */
s32 FUN_80131db8(void)
{
    return D_801CEEBC;
}

/* D5C8 80131DC8 -O2 -msoft-float */
void PS1_Cd_Pause(void)
{
    CdControl(CdlPause, null, null);
}

/* D5F0 80131DF0 -O2 -msoft-float */
void stop_cd(void)
{
    CdControl(CdlStop, null, null);
}

/* D618 80131E18 -O2 -msoft-float */
void PS1_Volume_Zero(void)
{
    SsSetSerialVol(SS_SERIAL_A, 0, 0);
}

/* D640 80131E40 -O2 -msoft-float */
void FUN_80131e40(void)
{
    PS1_Music_Fade = 2;
    PS1_Music_ind_fade = 0;
}

/* D65C 80131E5C -O2 -msoft-float */
void FUN_80131e5c(void)
{
    PS1_Volume_Zero();
    PS1_Music_Fade = 1;
    PS1_Music_ind_fade = 89;
}

/* D694 80131E94 -O2 -msoft-float */
void PS1_Music_Apply_Fade(void)
{
    s16 vol;

    if (PS1_Music_Fade != 1)
    {
        if (PS1_Music_Fade == 2)
        {
            if (PS1_Music_ind_fade < 90)
                vol =
                    D_801C4948[PS1_Music_ind_fade++] *
                    D_801F7C80 * PS1_Music_Vol[PS1_CurTrack] >> 14;
            else
            {
                vol = 0;
                PS1_Music_Fade = 0;
                PS1_Music_pcom = CdlPause;
                CdControl(CdlPause, null, null);
            }
        }
    }
    else
    {
        if (PS1_Music_ind_fade > 0)
        {
            if (PS1_Music_Ready_data > 0)
                vol =
                    D_801C4A00[PS1_Music_ind_fade--] *
                    D_801F7C80 * PS1_Music_Vol[PS1_CurTrack] >> 14;
            else
                vol = 0;
        }
        else
        {
            vol = D_801F7C80 * PS1_Music_Vol[PS1_CurTrack] >> 7;
            PS1_Music_Fade = 0;
        }
    }
    SsSetSerialVol(SS_SERIAL_A, vol, vol);
}

/* D82C 8013202C -O2 -msoft-float */
void FUN_8013202c(void)
{
    D_801E64B0 = true;
    PS1_LevelMusic_CmdInd = 1;
    PS1_PlayMusic();
}

/* D860 80132060 -O2 -msoft-float */
void change_audio_track_moskito_acc(void)
{
    if (PS1_Music_Ready_data > 0)
    {
        PS1_LevelMusic_CmdInd = 1;
        PS1_PlayMusic();
    }
}

/* D898 80132098 -O2 -msoft-float */
void change_audio_track_moskito_dec(void)
{
    if (PS1_Music_Ready_data > 0)
    {
        PS1_LevelMusic_CmdInd = -1;
        PS1_PlayMusic();
    }
}

/* D8D0 801320D0 -O2 -msoft-float */
void change_audio_track_puit(void)
{
    if (PS1_Music_Ready_data > 0)
    {
        PS1_ScrollLockedAudio = true;
        PS1_LevelMusic_CmdInd = 1;
        PS1_PlayMusic();
    }
}

/* D910 80132110 -O2 -msoft-float */
void start_cd_bbdead(void)
{
    D_801F5248 = true;
    FUN_80131e40();
    PS1_PlaySnd(21, 0);
}

void FUN_80132148(void) {}

void FUN_80132150(void) {}

void FUN_80132158(void) {}

void FUN_80132160(void) {}

/* D968 80132168 -O2 -msoft-float */
void PS1_SetMusicVolume(s16 param_1)
{
    D_801F7C80 = param_1 * 127 / 20;
    PS1_SsSetSerialVolA(PS1_Music_Vol[PS1_CurTrack] * D_801F7C80 >> 7);
}

/* D9FC 801321FC -O2 -msoft-float */
void FUN_801321fc(void)
{
    FntPrint(s_2d_markddd_80125d58, PS1_Mark_counter, PS1_Mark_access_num, PS1_Mark_seq_num, PS1_Mark_data);
}

/* DA44 80132244 -O2 -msoft-float */
void FUN_80132244(void)
{
#ifdef PLATFORM_PSYZ
    exit(0);
#else
    exit();
#endif
}
