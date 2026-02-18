#ifndef FIRST_INIT_H
#define FIRST_INIT_H

#include "common.h"
#include "LIBGPU.H"
#include "psyq_3_0_missing/LIBCD.H"
#include "draw/fade.h"
#include "draw/rollup_trans.h"
#include "unknown/7BB28.h"
#include "unknown/5C2BC.h"
#include "unknown/A3B0.h"

/* .data */
extern RECT D_801CF0E0;
extern RECT D_801CF0E8;

/* .data */
extern u8 D_801CF438;
extern u8 D_801CF440;

s16 prg_vig_loader1(void);
s16 prg_vig_loader2(void);
void loader(void);
u8 PS1_OldLoadingScreen(void);
void curtainroll(u8 param_1);
void START_WORLD_VIGNET(void);
void FUN_8019fd40(void);
u8 FUN_8019fda0(void);
void FUN_8019fdd0(void);
void GAME_INIT2(void);
void PS1_SetLevelto_4_1(void);
void FIRST_INIT(void);

#endif