#ifndef CAM_SCROLL_29B5C_H
#define CAM_SCROLL_29B5C_H

#include "common.h"
#include "collision/bit_util.h"

/* .data */
extern s16 expsin[64];
extern s16 expsin2[50];

/* .data */
extern u8 D_801CEDFC;
extern s16 dhspeed;
extern s16 dvspeed;
extern u8 joy_done;

/**/
extern s16 h_scroll_speed;
extern s16 v_scroll_speed;
extern s16 scroll_start_x;
extern s16 scroll_start_y;
extern s16 scroll_end_x;
extern s16 scroll_end_y;
extern u8 scrollLocked;
extern s16 screen_trembling;
extern s16 screen_trembling2;
extern s16 screen_trembling3;

s16 frapsol(s16 param_1);
void DO_SCREEN_TREMBLE(void);
void DO_SCREEN_TREMBLE3(void);
void DO_SCREEN_TREMBLE2(void);
void DO_SCROLL_MAP(s16 *h_speed, s16 *v_speed);

#endif