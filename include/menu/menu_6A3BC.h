#ifndef MENU_6A3BC_H
#define MENU_6A3BC_H

#include "common.h"
#include "common/obj.h"
#include "common/ray.h"
#include "menu/menu_7EEE4.h"
#include "menu/menu_7F4B4.h"
#include "obj/dark_729F0.h"
#include "ray/ray_32398.h"

/* .data */
extern s32 PS1_Button_Text_Square;
extern s32 PS1_Button_Text_Cross;
extern s32 PS1_Button_Text_Triangle;
extern s32 PS1_Button_Text_Circle;

/**/
extern Obj clock_obj;
extern s16 loop_timing;
extern u8 nb_continue;
extern u8 Etape_History;
extern u8 fin_continue;
extern Obj bigray;

void INIT_NEW_GAME(void);
void POINTEUR_BOUTONS_OPTIONS_BIS(void);
void DISPLAY_SYMBOLE(s16 button, s16 x, s16 y, u8 font_size, u8 param_5);
void INIT_CONTINUE(void);
void CHEAT_MODE_CONTINUE(void);
void MAIN_CONTINUE_PRG(void);
void FIN_CONTINUE_PRG(void);
void MAIN_NO_MORE_CONTINUE_PRG(void);
void INIT_VIGNET(void);
void INIT_CREDITS(void);
void DO_CREDITS(void);
void INIT_LOADER_ANIM(void);
void DO_LOADER_ANIM(void);
void SPECIAL_INIT(void);

#endif