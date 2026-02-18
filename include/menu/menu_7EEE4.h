#ifndef MENU_7EEE4_H
#define MENU_7EEE4_H

#include "common.h"
#include "menu/menu_7F4B4.h"

/**/
extern u8 menuEtape; /* TODO: add enum/defines */
extern u8 MENU_RETURN;
extern u8 PS1_MENU_RETURN2;
extern u8 PROC_EXIT;
extern u8 D_801E5920;
extern u8 PS1_CardShouldCheckFirstBoot; /* near card stuff instead? */

void DO_MENUS(void);

#endif