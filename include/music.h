#ifndef MUSIC_H
#define MUSIC_H

#include "common.h"
#include "LIBCD.H"
#include "LIBSND.H"
#include "LIBGPU.H"
#include "psyq_3_0_missing/LIBGPU.H"
#include "psyq_3_0_missing/STDLIB.H"
#include "psyq_3_0_missing/LIBAPI.H"
#include "psyq_3_0_missing/LIBETC.H"
#include "sound.h"
#include "loading_794DC.h"

typedef struct MusicCommand
{
    u8 cmd_and_flags; /* TODO: label bits */
    u8 param;
} MusicCommand;

/* .data */
extern MusicCommand PS1_LevelMusicTable[7][22][4];
extern s16 D_801C4948[92];
extern s16 D_801C4A00[92];
extern u8 PS1_Music_Vol[112];
extern s32 D_801C4B28[4];

/* .data */
extern s16 D_801CEEA4;
extern s16 D_801CEEA6;
extern s16 D_801CEEA8;
extern s16 PS1_Mark_counter;
extern s16 PS1_Music_access_num;
extern u8 PS1_Music_pcom;
extern s16 D_801CEEB8;
extern s16 D_801CEEBA;
extern s16 D_801CEEBC;
extern u8 s_s_801ceec0[4];
extern u8 s_idle_801ceec4[5];
extern u8 s_busy_801ceecc[5];
extern u8 s_yes_801ceed4[4];
extern u8 s_no_801ceed8[3];

/**/
extern s16 D_801E64B0;
extern s16 PS1_ScrollLockedAudio;
extern CdlLOC D_801F41D0[53];
extern s32 D_801F7CA8;
extern s16 PS1_LevelMusic_World;
extern s16 PS1_LevelMusic_Level;
extern s16 PS1_LevelMusic_CmdInd;
extern s16 D_801F9940; /* enum? */
extern s32 PS1_CurTrack;
extern u8 PS1_Music_etat;
extern u8 PS1_Music_track;
extern u8 PS1_Music_Amin;
extern u8 PS1_Music_Asec;
extern u8 PS1_Music_Aframe;
extern u8 PS1_Music_LevelHL;
extern s16 PS1_Music_Complete_data;
extern s16 PS1_Music_Fade;
extern s32 PS1_Music_Fin[53];
extern s16 PS1_Music_Ready_data;
extern s16 PS1_Music_fadeout;
extern s16 PS1_Music_ind_fade;
extern s32 PS1_Music_intr_compl;
extern s32 PS1_Music_intr_datar;
extern u8 PS1_Music_occupe;
extern s16 PS1_Music_will_anticip;
extern s16 D_801F5798;
extern s16 D_801E4D10; /* never read */
extern s32 D_801E5240;
extern s32 D_801E57C0[53];
extern s32 D_801F42A8[53];
extern s16 D_801F5248;
extern s16 D_801F7ED0;
extern s16 PS1_Mark_access_num;
extern s16 PS1_Mark_seq_num;
extern s16 PS1_Mark_data;
extern CdlLOC D_801F4E68; /* last time i checked held the data that was at 801f41dc? */
extern u8 PS1_CdMode;
extern s32 D_801F54B0[53];
extern s32 D_801F7AA8[53];
extern s32 D_801F7D88[53];
extern u32 PS1_TrackSizes[53];
extern s16 PS1_TracksExist[53];
extern s16 D_801E4B78;
extern s16 D_801FAA50;
extern s16 D_801F7A90[4];
extern s16 D_801F7C80; /* volume related */
extern CdlLOC D_801E4EF8;
extern s32 D_801F4FA0;
extern s16 D_801FA570;

void PS1_StopAll(void);
void PS1_CdReadyCallback(s32 status, u8 *result);
void PS1_CdSyncCallback(s32 status, u8 *result);
void PS1_MarkCallback(s16 access_num, s16 seq_num, s16 data);
void PS1_ManageCdMusic(void);
void PS1_SsSetSerialVolA(s16 vol);
void PS1_ResetCallback(void);
void PS1_RemoveCdCallbacks(void);
void PS1_RemoveMarkCallback(void);
void PS1_SetCdCallbacks(void);
void PS1_SetMarkCallback(void);
void PS1_InitMusic(void);
void PS1_ResetSpecialMusicFlags(void);
void PS1_CdPlayerTest(void);
void PS1_EmptyFunction2(void);
u8 PS1_AddBCD(u8 param_1, u8 param_2, u8 *param_3, u8 param_4);
void PS1_AddCdLOC(CdlLOC *param_1, CdlLOC *param_2, CdlLOC *param_3);
void PS1_LBAToCdLOC(u32 param_1, CdlLOC *param_2);
s32 PS1_CdLOCToMSF(CdlLOC loc);
s32 PS1_LBAToMSF(s32 param_1);
s32 PS1_AddMSF(s32 param_1, s32 param_2);
u8 PS1_InitTracks(void);
s16 PS1_HasCommandIndex(s16 *param_1, s16 param_2, s16 param_3);
void PS1_ProcessMusicCommand2(void);
void PS1_PlayMusic(void);
void start_cd(s16 world, s16 lvl);
void start_cd_gros_rayman(void);
void start_cd_suspence(void);
void start_cd_replay(void);
void start_cd_victory(void);
void start_cd_gagne(void);
void start_cd_perdu(void);
void start_cd_rap(void);
void start_cd_gameover(void);
void start_cd_continue(void);
s32 track_is_finished(void);
void pause_cd(void);
void stop_cd(void);
void PS1_SetVolumeTo0(void);
void PS1_InitMusicFadeOut(void);
void PS1_InitMusicFadeIn(void);
void PS1_DoMusicFade(void);
void PS1_PlayWaterRisingMusic(void);
void change_audio_track_moskito_acc(void);
void change_audio_track_moskito_dec(void);
void change_audio_track_puit(void);
void start_cd_bbdead(void);
void PS1_EmptyFunction3(void);
void PS1_EmptyFunction4(void);
void PS1_EmptyFunction5(void);
void PS1_EmptyFunction6(void);
void PS1_SetMusicVolume(s16 param_1);
void PS1_PrintMark(void);
void PS1_Exit(void);

#endif