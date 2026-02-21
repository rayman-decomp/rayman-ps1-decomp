#ifndef SOUND_H
#define SOUND_H

#include "common.h"
#include "common/obj.h"
#include "common/level.h"
#include "common/ray.h"
#include "LIBSND.H"
#include "obj_update.h"
#include "loading_794DC.h"
#include "loading_E99C.h"
#include "moteur_update.h"

typedef struct SoundTableEntry
{
    u8 note;
    u8 prog;
    u8 tone;
    u8 volume;
    u8 flags;
} SoundTableEntry;

typedef struct VoiceTableEntry
{
    s16 id;
    s16 field1_0x2;
    s16 field2_0x4; /* pan? see get_pan_snd, setpan */
    s16 field3_0x6; /* hard_sound_table index based on manage_snd? */
    u8 field4_0x8;
    u8 field5_0x9;
    u8 field6_0xa;
    u8 field7_0xb;
} VoiceTableEntry;

typedef struct SepInfo
{
    s16 access_num;
    s16 seq_num;
} SepInfo;

typedef struct Unk_801f7d40
{
    u8 field0_0x0;
    s8 field1_0x1;
    u8 field2_0x2;
    u8 field3_0x3;
    u8 field4_0x4;
} Unk_801f7d40;

typedef struct Unk_801f62a0
{
    s16 id;
    s16 index;
    s16 prog;
    s16 tone;
    s16 note;
    s16 vol;
    /* not sure about these, but every access would otherwise be multiplied by 2 */
    s16 field6_0xc;
    s16 field7_0xe; /* pan? see get_pan_snd, setpan */
    s32 field8_0x10; /* u32? related with map_time? see nettoie_pile_snd and PlaySnd */
    s16 field9_0x14;
    s16 field10_0x16;
} Unk_801f62a0;

typedef struct SndFileInfo
{
    s32 field0_0x0; /* checked == 3 at 80165a80 and != 0 at 80165cec */
    s32 ray_vh_offs; /* body is in RAY*.VB */
    s32 sep_vh_offs; /* body is in SEP*.VB */
    s32 seq_offs;
    s32 size;
} SndFileInfo;

/* .data */
extern SoundTableEntry hard_sound_table[256];
extern u8 frame_snd[256];
extern u8 frame_snd_bis[256];
extern s16 snd_bis[256];
extern u8 bank_to_use[256];
extern s16 D_801C7C78[8]; /* SsSepOpen seq_num? number of elements? */
extern s16 PS1_SepVols[26]; /* number of elements? */
extern SepInfo PS1_SepInfos[25]; /* number of elements? */
extern s16 PS1_NewWorldMusic[8]; /* TODO: number of elements? */
extern s16 PS1_AudioTable[14]; /* bad starting point based on PS1_NewWorldMusic? */
extern u8 voice_is_working[24];

/* .data */
extern s16 Volume_Snd;

/* .data */
extern s16 D_801CEFCC;
extern s16 D_801CEFCE;
extern u8 D_801CEFD0[8]; /* number of elements? */
extern s16 D_801CEFD8; /* bool? toggle for pause and play? see stop_freeze_snd, FUN_801300ac */
extern s16 PS1_CurrentAudio;
extern s16 D_801CEFDC;

/**/
extern s16 PS1_AllFix_Ray_VabId;
extern s16 PS1_AllFix_Sep_VabId;
extern s16 PS1_AllFix_SepAcc;
extern s16 PS1_World_Ray_VabId;
extern s16 PS1_World_Sep_VabId;
extern s16 PS1_World_SepAcc;
extern s16 indice_ray_wait;
extern s16 indice_trz_wait;
extern s16 stk_obj[20];
extern s16 stk_snd[20];
extern VoiceTableEntry voice_table[24];
extern u8 D_801F6850[SS_SEQ_TABSIZ * 2 * 10];
/*cannot do this...: extern u8 D_801D8B50[PS1_BigFiles[0].file.size];*/
extern u8 D_801D8B50[41616];
extern s32 D_801D8B54;
extern s32 D_801D8B58;
extern s32 D_801D8B5C;
extern s16 D_801FA578;
extern Unk_801f7d40 D_801F7D40[8]; /* struct unclear, number of elements unclear */
extern Unk_801f62a0 pile_snd[10]; /* struct unclear, number of elements unclear */
extern s16 pt_pile_snd;
extern SndFileInfo *D_801D7840;

void PS1_StopPlayingAllSnd(void);
void FUN_801658e0(void);
void manage_snd_event(Obj *obj);
void PS1_LoadAllFixSound(void);
void PS1_LoadWorldSound(s16 param_1);
void PS1_PlaySnd(s16 sep_ind, s16 l_count);
void PS1_StopPlayingSnd(s16 sep_ind);
s32 PS1_SongIsPlaying(s16 sep_ind);
void FUN_80166018(void);
void SetVolumeSound(s16 vol);
void setVolumeStereo(void);
void setVolumeMono(void);
void stop_all_snd(void);
void FUN_8016617c(void);
u8 get_pan_snd(Obj *obj);
u8 get_vol_snd(Obj *obj);
void PS1_SetSoundVolume(s16 vol);
void PS1_SetStereoEnabled(s16 enabled);
void InitSnd(void);
void FUN_80166578(void);
s32 last_snd(s16 obj_id);
s16 get_pile_obj(s16 id); /* do these "find" funcs all return s16? */
s16 FUN_80166724(s16 id);
s32 FUN_80166790(s16 id);
s16 get_voice_obj_snd(s16 id, s16 param_2);
void erase_pile_snd(s16 id);
void nettoie_pile_snd(void);
void erase_voice_table(s16 id);
s16 FUN_80166d88(s16 index);
s16 vol_r(s16 param_1, s16 param_2); /* param_1 is vol? param_2 is pan? see get_pan_snd */
s16 vol_l(s16 param_1, s16 param_2);
void PlaySnd(s16 snd, s16 obj_id);
void PlaySnd_old(s16 snd);
void setvol(s16 param_1, u8 param_2);
void setpan(s16 obj_id, u8 param_2);
void FUN_80168f38(s16 param_1);
void FUN_80168f40(void);
void manage_snd(void);
void mute_snd_bouclant(void);
void mute_snd(void);
void start_freeze_snd(void);
void stop_freeze_snd(void);

#endif