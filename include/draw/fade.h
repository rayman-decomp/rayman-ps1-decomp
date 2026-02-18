#ifndef FADE_H
#define FADE_H

#include "common.h"
#include "common/display.h"
#include "draw/draw_548CC.h"

typedef struct RGBAArray
{
    u8 data[4];
} RGBAArray;

/* .data */
extern void (*D_801C7D68[4])(RGBAArray *, s16);
extern RGBAArray *D_801C7D78[11];

/* .data */
extern RGBAArray D_801CEFE0[5];
extern s16 D_801CEFF4;
extern s16 D_801CEFF6; /* lightning "phase" more or less? */
extern RGBAArray D_801CEFFC[3];
extern RGBAArray D_801CF008;
extern s16 D_801CF00C;
extern u16 D_801CF00E;
extern s16 D_801CF010;
extern s16 D_801CF012;
extern s16 D_801CF014;
extern s16 D_801CF016;
extern s16 D_801CF018;
extern u8 PS1_DisableInputs; /* might seem weird to have in this file, but DO_FADE is only place this is being set true */

/* .data */
extern s16 D_801CF410;

/**/
extern s16 fade;
extern u8 D_801F7FF0;
extern u8 D_801F8480;

void initeffet(Display *disp);
void effet(u32 param_1, s16 param_2);
void eclair(s16 param_1);
void fadenuitbleu(RGBAArray *param_1, s16 param_2);
void FUN_80169ac8(RGBAArray *param_1, s16 param_2);
void FUN_80169b54(RGBAArray *param_1, s16 param_2);
void FUN_80169b5c(RGBAArray *param_1, s16 param_2);
void INIT_FADE_OUT(void);
void INIT_FADE_IN(void);
void DO_FADE(void);
s16 PS1_DO_FADE_OUT_PRG(void);
void DO_FADE_OUT(void);
void tele(void);

#endif