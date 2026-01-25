#ifndef CARD_H
#define CARD_H

#include "common.h"
#include "common/rayevts.h"
#ifdef PLATFORM_PSYZ
#include <kernel.h>
#if !(defined(_MSC_VER) || defined(__MINGW32__))
#include <sys/file.h>
#endif
#else
#include "KERNEL.H"
#include "SYS/FILE.H"
#endif
#include "menu/menu_7F4B4.h"
#include "input_ED20.h"
#include "save.h"

typedef struct CardFrame0
{
    u8 sc_magic[2];
    u8 icon_display_flag;
    u8 block_num;
    u8 Rayman_save_ray_pct[64];
    u8 Maga[28];
    u8 icon_palette[32];
} CardFrame0;

typedef struct LoadInfoRay
{
    u8 num_lives;
    u8 num_wiz;
    u8 num_cages;
    u8 num_continues;
} LoadInfoRay;

/* .data */
extern s32 D_801CF01C;
extern s32 D_801CF020;
extern u8 s_Error_801cf024[7];
extern u8 s__801cf02c[2];
extern u8 s_no_card_801cf030[8];
extern u8 s_error_801cf038[6] __attribute__((aligned(4)));
extern u8 s_bu02x_801cf040[8];
extern u8 s__Done_801cf048[7];
extern u8 s_Maga_801cf050[5];
extern u8 s_ss_801cf058[5];

/**/
extern LoadInfoRay loadInfoRay[6];
extern u8 D_801F7F08[34];
extern s32 PS1_SwCARD_EvSpERROR;
extern s32 PS1_SwCARD_EvSpIOE;
extern s32 PS1_SwCARD_EvSpNEW;
extern s32 PS1_SwCARD_EvSpTIMOUT;
extern s32 PS1_HwCARD_EvSpERROR;
extern s32 PS1_HwCARD_EvSpIOE;
extern s32 PS1_HwCARD_EvSpNEW;
extern s32 PS1_HwCARD_EvSpTIMOUT;
extern s32 PS1_Checksum;
extern u8 PS1_SaveFilenames[3][32];

s32 PS1_InitPAD(void);
s32 PS1_TestSwCARD(void);
void PS1_TestSwCARDOnce(void);
s32 PS1_TestHwCARD(void);
void PS1_TestHwCARDOnce(void);
u8 PS1_TestCard(u8 par_chan);
s32 PS1_GetNbreFiles(u8 *name_start, struct DIRENTRY *in_files);
s32 PS1_CardFilenameChecksum(u8 chan);
void PS1_InitializeCard(u8 chan);
u8 PS1_FormatFs(u8 param_1);
void PS1_InitSaveRayAndFilenames(u8 param_1);
s32 PS1_WriteSave(u8 chan_par, u8 slot_par);
u8 *FUN_8016b2e8(u8 param_1, u8 param_2, u8 *param_3);
s32 SaveGameOnDisk(u8 slot);
s32 SaveFileRead(s32 file_desc, void *buf, s16 n_bytes);
void PS1_LoadSave(s32 param_1, u8 *filename);
void LoadGameOnDisk(u8 slot);
s32 LoadInfoGame(u8 slot);
void FUN_8016bbe4(void);
u8 PS1_GetNbreSave3(u8 param_1);
s32 PS1_CardFilenameChecksumChanged(void);
s32 PS1_TestCardZero(void);
s16 PS1_CardUnformatted(void);
u8 PS1_GetNbreSave2(void);
s32 FUN_8016be9c(void);
void FUN_8016bec0(void);

#endif