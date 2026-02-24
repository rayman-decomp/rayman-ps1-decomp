#ifndef MENU_82008_H
#define MENU_82008_H

#include "common.h"
#include "psyq_3_0_missing/STRINGS.H"
#include "menu/menu_7EEE4.h"
#include "menu/menu_7F4B4.h"

extern s16 D_801D7AA0;
extern s16 D_801F5498; /* used as loop bound */
extern s16 PS1_Music_Max;
extern s16 PS1_Soundfx_Max;
extern s16 delai_barre;
extern s16 delai_stereo;

void PS1_InitGameOptionsMenu(void);
void PS1_LoadOptions(void);
void PS1_NewGame(u8 param_1);
void DO_COMMANDE_OPTIONS(void);
void PS1_DisplayGameOptions(void);

#endif