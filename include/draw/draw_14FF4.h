#ifndef DRAW_14FF4_H
#define DRAW_14FF4_H

#include "common.h"
#include "common/obj.h"
#include "common/display.h"
#ifdef PLATFORM_PSYZ
#include "libgte.h"
#include <stdlib.h>
#else
#include "LIBGTE.H"
#include "RAND.H"
#include "psyq_3_0_missing/RAND.H"
#endif
#include "main_moteur.h"
#include "snow.h"
#include "collision/proj.h"
#include "boss.h"
#include "pix_gerbe.h"
#include "obj/cymbal.h"
#include "obj/dark_phase2.h"

/* .data */
extern s16 PS1_PolygonIndexTableCount;
extern u8 PS1_DrawSpriteSemiTrans;
extern s16 D_801CEF78;
extern s16 D_801CEF7A;

/* .data */
extern s16 D_801CF600[16]; /* list of angles? */

/**/
extern s16 PS1_PolygonIndexTable[200];
extern s16 PS1_PolygonsCount;
extern s16 D_801F4A28; /* range of possible values? reset to 0 every frame */
extern u16 PS1_Disp_Cur_Tile1;
extern OT_TYPE *PS1_PrevPrim; /* should this be labelled as ordering table instead? */
extern u8 D_801E4C20;
extern s16 D_801E4DF8;

void PS1_DrawColoredSprite(Sprite *sprite, s16 in_x, s16 in_y, u8 disp_mode);
void PS1_DrawSprite(Sprite *sprite, s16 x, s16 y, u8 param_4);
void PS1_DrawScaledSprite(Sprite *sprite, s16 x, s16 y, u8 is_flipped, s16 param_5); /* param_5 takes Obj.scale */
void FUN_80139d5c(s16 *p_poly_x, s16 *p_poly_y, s16 param_3, s16 param_4, s16 angle);
void PS1_DrawRay(Sprite *sprite, s16 x, s16 y, u8 is_flipped, s16 angle_ind);
void display_sprite(Obj *param_1, u8 sprite, s16 x, s16 y, u8 param_5);
void display2(Obj *obj);
void DISPLAY_POING(void);
void DISPLAY_CLING(void);
void display_bar_boss(Obj *boss_obj);
void DISPLAY_FIXE(s16 left_time);
void FUN_8013ad54(s16 param_1, s16 param_2, s16 param_3);
void DrawWldPointPlan2Normal(s16 x0, s16 y0);
void PS1_DisplayPtsPrim(void);
void DISPLAY_POINT(s32 x0, s32 y0);
void DISPLAY_PTS_TO_PLAN2(s32 x1, s32 y1, s32 x2, s32 y2, s16 percentage);
void DISPLAY_PLATEAU(Obj *obj);
void draw_flocon1_Normal(s16 x0, s16 y0);
void draw_flocon2_Normal(s16 x0, s16 y0);
void draw_flocon3_Normal(s16 x0, s16 y0);
void draw_flocon4_Normal(s16 x0, s16 y0);
void draw_flocon5_Normal(s16 x0, s16 y0);
void FUN_8013b294(s16 x0, s16 y0);
void FUN_8013b304(s16 x0, s16 y0);
void draw_pluie4_Normal(s16 x0, s16 y0);
void draw_pluie5_Normal(s16 x0, s16 y0);
void draw_pluie6_Normal(s16 x0, s16 y0);
void FUN_8013b4d4(s16 x0, s16 y0);
void display_flocons_behind(void);
void display_flocons_before(void);
void display_pix_gerbes(void);
void DISPLAY_CYMBALE(Obj *obj, u8 param_2);
void DISPLAY_ALL_OBJECTS(void);

#endif