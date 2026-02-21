#ifndef LOADING_794DC_H
#define LOADING_794DC_H

#include "common.h"
#include "common/fileinfo.h"
#include "LIBGPU.H"
#include "loading_DA64.h"
#include "loading_tex.h"
#include "sound.h"
#include "draw/fond_10B3C.h"
#include "menu/menu_6A3BC.h"
#include "password.h"

typedef struct BackgroundData
{
    DVECTOR sprite_positions[16];
    Sprite sprites[16];
} BackgroundData;

/* .data */
extern u32 *D_801C4374[6];
extern u32 *D_801C438C[6];
extern u8 PS1_BackgroundIndexTable[6][30];

/* .data */
extern FileInfo PS1_ImgFiles[3];
extern FileInfo PS1_LdrFiles[2];
extern FileInfo PS1_VdoFiles[6];
extern FileInfo PS1_TrkFiles[53];
extern FileInfo PS1_PreFiles[5];
extern FileInfo PS1_CrdFiles[6];
extern FileInfo PS1_GamFiles[6];
extern FileInfo PS1_VigWldFiles[6];
extern FileInfo PS1_WldFiles[6];
extern FileInfo PS1_MapFiles[126];
extern FileInfo PS1_FndFiles[31];
extern FileInfo PS1_VabFiles[7];
extern FileInfo PS1_BigFiles[7];
extern FileInfo PS1_Vab4sepFiles[7];
extern FileInfo PS1_FxsFiles[2];
extern FileInfo PS1_IniFiles[1];

/* .data */
extern u8 D_801CF0CA;
extern u8 PS1_HasLoadedFont;
extern u8 D_801CF0CC;
extern u8 D_801CF0CD;
extern u8 s_filefxs_801cf0d0[8];

/**/
extern s32 PS1_FileTemp;
extern s16 no_fnd;
extern s16 plan2_height;
extern s16 plan2_width;
extern BackgroundData *PS1_LevelBGBlock;
extern s16 *PS1_LevelMapBlock; /* type? */
extern u8 *PS1_LevelObjBlock; /* type? */
extern u8 D_801E4B58; /* here, or fond_5BD8C.h? */
extern void *D_801F4410;
extern void *D_801F5160; /* type? very prominent in everything up to charge_fnd */
extern s32 *D_801E5260;
extern s32 *D_801F59E0; /* see loading_DA64 */

void PS1_Init_ImgLdrVdoTrk_Files(void);
void FUN_8019dd74(void);
void charge_une_vignette(void);
void charge_wld_vignette(s16 param_1);
void charge_ini(void);
void charge_fix(void);
void charge_wld(s16 world);
s16 charge_lvl(void);
void charge_fnd(void);
void charge_wm(void);
void PS1_LoadVideoTables(void);
void charge_let2(void);
void charge_vig_loader1(void); /* labelled correctly? */
void charge_vig_loader2(void);
void LOAD_CONTINUE_SCREEN(void);
void PS1_LoadImgSplash(void);
void LOAD_SAVE_SCREEN(void);
void FUN_8019eb30(void);
s16 FUN_8019ebc0(void);
void LOAD_CREDITS_VIGNET(void);
void LOAD_VIGNET_GAME(void);

#endif