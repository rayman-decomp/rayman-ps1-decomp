#ifndef ROLLUP_TRANS_H
#define ROLLUP_TRANS_H

#include "common.h"
#include "common/display.h"
#include "LIBGPU.H"
#include "draw/draw_548CC.h"

/* .data */
extern DVECTOR D_801CEDE4;
extern DVECTOR D_801CEDE8;
extern DVECTOR D_801CEDEC[2];

/**/
extern s16 PS1_RollUpPosition;
extern SVECTOR D_801F3EC0[82];
extern SVECTOR D_801F56B8;
extern VECTOR D_801F57D0;
extern s16 D_801F84D8;
extern s16 D_801F98F8;
extern s16 D_801F9930;
extern s16 D_801F9938;
extern s32 D_801F6390;

void PS1_InitCurtainRollPolygons(DVECTOR tpage_pos, DVECTOR param_2, s16 step_width, s16 step_height, s16 poly_count);
void PS1_InitCurtainRollGeometry(void);
void PS1_InitCurtainRoll(s16 start_pos);
void PS1_DoCurtainRoll(s16 rollup_pos, s16 left_to_right);
s16 PS1_DoCurtainRollRToL(void);
s16 PS1_DoCurtainRollLToR(void);
void PS1_UnusedInitCurtainRoll(void);

#endif