#ifndef INPUT_ED20_H
#define INPUT_ED20_H

#include "common.h"
#include "common/record.h"
#include "menu/menu_7F4B4.h"
#include "draw/fade.h"

typedef u8 Input;
#define INPUT_NONE 0
#define INPUT_LEFT 1
#define INPUT_RIGHT 2
#define INPUT_UP 3
#define INPUT_DOWN 4
#define INPUT_CROSS 5
#define INPUT_CIRCLE 6
#define INPUT_SQUARE 7
#define INPUT_TRIANGLE 8
#define INPUT_START 9
#define INPUT_SELECT 10
#define INPUT_R1 11
#define INPUT_R2 12
#define INPUT_L1 13
#define INPUT_L2 14
#define INPUT_DISABLE_DEBUG 15 /* unused */
#define INPUT_ENABLE_DEBUG 16 /* unused */
#define INPUT_START_SELECT 17
#define INPUT_UNUSED_12 18
#define INPUT_13 19
#define INPUT_14 20
#define INPUT_UNUSED_15 21
#define INPUT_UNUSED_16 22
#define INPUT_17 23
#define INPUT_18 24
#define INPUT_UNUSED_19 25
#define INPUT_UNUSED_1A 26
#define INPUT_READ 255

/* TODO: these are also defined in libetc.h */
/*typedef u32 PsxPadButtonStates;
#define PAD_NONE 0
#define PAD_L2 1
#define PAD_R2 2
#define PAD_L1 4
#define PAD_R1 8
#define PAD_TRIANGLE 16
#define PAD_CIRCLE 32
#define PAD_CROSS 64
#define PAD_SQUARE 128
#define PAD_SELECT 256
#define PAD_L3 512
#define PAD_R3 1024
#define PAD_START 2048
#define PAD_UP 4096
#define PAD_RIGHT 8192
#define PAD_DOWN 16384
#define PAD_LEFT 32768*/

/* .data */
extern s32 PS1_ButtonStates[18];

/**/
extern s32 PS1_GlobalTimer;
extern u8 PS1_PadReceiveBuffer[34];
extern s16 D_801E4C08;
extern s16 joy_rec_left;
extern s16 joy_rec_right;
extern s16 joy_rec_down;
extern s16 D_801F8428;
extern s16 D_801F8430;
extern s16 D_801F8438;
extern s16 D_801F8448;
extern s32 D_801E4B60;
extern s16 D_801F5688;

s32 readinput(void);
s32 upjoy(s32 param_1);
s32 leftjoy(s32 param_1);
s32 rightjoy(s32 param_1);
s32 downjoy(s32 param_1);
s32 upmenu(s32 param_1);
s32 leftmenu(s32 param_1);
s32 rightmenu(s32 param_1);
s32 downmenu(s32 param_1);
s32 but0pressed(s32 param_1);
s32 but1pressed(s32 param_1);
s32 but2pressed(s32 param_1);
s32 but3pressed(s32 param_1);
s32 PS1_LPressed(s32 param_1);
s32 PS1_RPressed(s32 param_1);
s32 PS1_IsInputtingCheatCode(s32 param_1);
s32 PS1_L1Pressed(s32 param_1);
s32 PS1_R1Pressed(s32 param_1);
s32 PS1_SelectPressed(s32 param_1);
s32 PS1_L1Pressed2(s32 param_1);
s32 PS1_L2Pressed2(s32 param_1);
s32 PS1_R1Pressed2(s32 param_1);
s32 PS1_R2Pressed2(s32 param_1);
s32 butL1(s32 param_1);
s32 butL2(s32 param_1);
s32 butR1(s32 param_1);
s32 butR2(s32 param_1);
s32 but0pressed2__SQUARE(s32 param_1);
s32 but1pressed2__CROSS(s32 param_1);
s32 but2pressed__TRIANGLE(s32 param_1);
s32 but3pressed__CIRCLE(s32 param_1);
s32 butstart(s32 param_1);
s32 butSelectPressed(s32 param_1);
s32 PS1_NoButtonPressed(s32 param_1);
s32 butvbl(s32 param_1);
s32 butdbw(s32 param_1);
s32 butmode(s32 param_1);
s32 butR2_2(s32 param_1);
s32 butR1_1(s32 param_1);
s32 cheat_start(s32 param_1);
s32 cheat1_start(s32 param_1);
s32 cheat2_start(s32 param_1);
s32 cheat3_start(s32 param_1);
s32 cheat4_start(s32 param_1);
s32 cheat5_start(s32 param_1);
s32 cheat6_start(s32 param_1);
s32 cheat7_start(s32 param_1);
s32 PS1_UnusedCheat8Start(s32 param_1);
s32 PS1_UnusedCheat9Start(s32 param_1);
s32 cheat_stop(s32 param_1);
s32 PS1_StartSelectPressed(s32 param_1);
s32 but0pressed__CROSS(void);
s32 but1pressed__START(void);
s32 butStartPressed(void);
s32 but2pressed__SELECT(void);
void PS1_GetRecordedInputs(u8 param_1); /* PS1_Demo_SetInputs? */
u8 PS1_SetRecordedInputs(void); /* PS1_Demo_GetInputs? names don't make sense based on record_input though? */
void record_input(Record *record);
void PS1_EmptyFunction8(void);
s32 TOUCHE(Input param_1);
s32 padd(Input param_1);

#endif