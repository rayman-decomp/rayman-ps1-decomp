#ifndef TEXT_18118_H
#define TEXT_18118_H

#include "common.h"
#include "common/text_to_display.h"
#include "LIBGPU.H"
#include "draw/draw_14FF4.h"
#include "draw/draw_548CC.h"
#include "text_24E10.h" /* TODO: circular? */

typedef struct MenuText
{
    u8 *header;
    u8 *rows[6];
    RECT vignette_rect;
    s32 vignette;
    s32 music;
    u8 rows_count;
    u8 selected_row;
    u8 color;
    /*u8 unk_1;*/ /* packed? */
} MenuText;

/* .data */
extern u8 D_801C3580[6];
extern u8 D_801C3588[6];
extern u8 D_801C3590[6];
extern u8 D_801C3598[6];
extern u8 D_801C35A0[10];
extern u8 D_801C35AC[14];

/* .data */
extern u8 D_801C71CC[44];
extern u8 D_801C71F8[48];
extern u8 D_801C7228[48];

/* .data */
extern u8 D_801CEE10;
extern u8 let_shadow;

/**/
extern u8 colour;
extern s16 D_801F81B0;

u8 PS1_deter_num_let_old(s32 param_1);
s16 SizeLettre(s16 sprite, u8 font);
s32 calc_let_Width(u8 font, s16 sprite);
s16 SizeLigne(u8 *str, u8 font);
void PS1_DisplayMenuText(u8 *str, u8 param_2, u8 color);
void PS1_DisplayMenuTexts(u8 index, MenuText *in_menus); /* unused */
void display_blackboxborder(s16 x, s16 y, s16 w, s16 h, u8 brightness);
void display_blackbox(s16 x, s16 y, s16 w, s16 h, u8 brightness);
void DISPLAY_BLACKBOX(u16 x, u16 y, u16 w, u16 h, u8 param_5, u8 is_fond);
void display_text_sin(u8 *text, s16 in_x, s16 in_y, s16 temps, u8 font_size, u8 clut_x);
void display_text(u8 *text, s16 in_x, s16 in_y, u8 font_size, u8 param_5);
void display_box_text(TextToDisplay *txt);

#endif