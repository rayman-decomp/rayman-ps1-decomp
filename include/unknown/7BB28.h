#ifndef UNK_7BB28_H
#define UNK_7BB28_H

#include "common.h"
#include "common/display.h"
#include "sound.h"

/* .data */
extern u8 s_d_801cf0f0[3];

void PS1_StopLevelMusic(void);
void InitDB(Display *display);
void FUN_801a0750(void);
void PS1_itoa(s16 param_1, u8 *param_2, u8 param_3);
void FUN_801a07b0(void);
void PS1_PlayMapIntro(void);

#endif