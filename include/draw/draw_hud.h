#ifndef DRAW_HUD_H
#define DRAW_HUD_H

#include "common.h"
#include "common/obj.h"
#include "common/level.h"
#include "common/ray.h"
#include "common/display.h"
#include "world_map_677C0.h"
#include "card.h"
#include "menu/menu_6A3BC.h"

typedef struct GrpStar
{
    u8 timer;
    u8 length;
    u8 dist;
    u8 sprite_table_index;
} GrpStar;

/* .data */
extern u8 PS1_star_spr[8] __attribute__((aligned(2)));
extern u8 s__801cef84[2];
extern u8 PS1_TingsToGet_Col;
extern u8 PS1_TingsToGet_ColAdd;
extern u8 s_time_801cef88[5];
extern u8 s__801cef90[2] __attribute__((aligned(4)));
extern u8 s_go__801cef94[7] __attribute__((aligned(4)));
extern u8 s_the_end_801cef9c[8];

/**/
extern GrpStar grp_stars[30];
extern s16 current_star;
extern Obj div_obj;

void CLRSCR(void);
void display_etoile(s32 in_x, s32 in_y);
void display_grp_stars(void);
void DISPLAY_TEXT_FEE(void);
void DISPLAY_JUMELLES(void);
void DISPLAY_JUMELLES_FOND(s16 x1, s16 y1, s16 x2, s16 y2);
void DISPLAY_SAVE_SPRITES(s16 x, s16 y);
void DISPLAY_SAVE_POING(void);
void display_time(s16 param_1);
void init_spr(void);
void DISPLAY_CONTINUE_SPR(void);
void PS1_PromptCardDisplayPoing(void);
void DISPLAY_OPTIONS_POING(void);

#endif