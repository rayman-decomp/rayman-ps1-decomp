#include "fond_5BD8C.h"

/* 5BD8C 8018058C -O2 -msoft-float */
void DISPLAY_ANYSIZE_PICTURE(u32 *image, s32 param_2, s32 param_3, s16 x, s16 y, s16 h, s16 w)
{
    RECT sp10 = {x, y, w, h};
    RECT sp18;
    RECT sp20;
    RECT sp28;
    RECT sp30;

    if (w == 0) {
        w = 320;
    }

    if (h == 0) {
        h = 240;
    }

    sp10.x = x + PS1_CurrentDisplay->drawing_environment.clip.x;
    sp10.y = y + PS1_CurrentDisplay->drawing_environment.clip.y;
    sp10.w = w;
    sp10.h = h;
    LoadImage(&sp10,image);

    sp18.x = 0;
    sp18.y = PS1_CurrentDisplay->drawing_environment.clip.y;
    sp18.w = 320;
    sp18.h = y;
    if (sp18.h != 0) {
        ClearImage(&sp18,D_801CF0CA,D_801CF0CA,D_801CF0CA);
    }

    sp20.x = 0;
    sp20.y = y + PS1_CurrentDisplay->drawing_environment.clip.y + h;
    sp20.w = 320;
    sp20.h = 240 - y - h;
    if (sp20.h != 0) {
        ClearImage(&sp20,D_801CF0CA,D_801CF0CA,D_801CF0CA);
    }

    sp28.x = 0;
    sp28.y = y + PS1_CurrentDisplay->drawing_environment.clip.y;
    sp28.w = x;
    sp28.h = h;
    if (sp28.w != 0) {
        ClearImage(&sp28,D_801CF0CA,D_801CF0CA,D_801CF0CA);
    }

    sp30.x = x + w;
    sp30.y = y + PS1_CurrentDisplay->drawing_environment.clip.y;
    sp30.w = 320 - x - w;
    sp30.h = h;
    if (sp30.w != 0) {
        ClearImage(&sp30,D_801CF0CA,D_801CF0CA,D_801CF0CA);
    }
}

/* 5BF84 80180784 -O2 -msoft-float */
void DISPLAY_FOND3(void)
{
    s16 y = (SCREEN_HEIGHT - plan2_height) >> 1;
    s16 x = (SCREEN_WIDTH - plan2_width) >> 1;

    if (D_801E4B58 == true)
        y = 0;
    DISPLAY_ANYSIZE_PICTURE((u32 *) D_801F4380, 0, 0, x, y, plan2_height, plan2_width);
}

/* 5C004 80180804 -O2 -msoft-float */
void DISPLAY_ANYSIZE_PICTURE640(u32 *param_1, s32 param_2, s32 param_3, s16 x, s16 y, s16 h, s16 w)
{
    RECT sp10 = {x, y, w, h};
    
    RECT sp18;
    RECT sp20;
    RECT sp28;
    RECT sp30;
    
    if (w == 0) {
        w = 0x280;
    }
    if (h == 0) {
        h = 0x1e0;
    }
    sp10.x = x + (PS1_CurrentDisplay->drawing_environment).clip.x;
    sp10.y = y + (PS1_CurrentDisplay->drawing_environment).clip.y;
    sp10.w = w;
    sp10.h = h;
    LoadImage(&sp10,param_1);
    sp18.x = 0;
    sp18.y = (PS1_CurrentDisplay->drawing_environment).clip.y;
    sp18.w = 0x280;
    sp18.h = y;
    if (y != 0) {
        ClearImage(&sp18,D_801CF0CA,D_801CF0CA,D_801CF0CA);
    }
    sp20.x = 0;
    sp20.y = (PS1_CurrentDisplay->drawing_environment).clip.y + y + h;
    sp20.w = 0x280;
    sp20.h = (0x1e0 - y) - h;
    if (sp20.h != 0) {
        ClearImage(&sp20,D_801CF0CA,D_801CF0CA,D_801CF0CA);
    }
    sp28.x = 0;
    sp28.y = y + (PS1_CurrentDisplay->drawing_environment).clip.y;
    sp28.w = x;
    sp28.h = h;
    if (x != 0) {
        ClearImage(&sp28,D_801CF0CA,D_801CF0CA,D_801CF0CA);
    }
    sp30.x = x + w;
    sp30.y = y + (PS1_CurrentDisplay->drawing_environment).clip.y;
    sp30.w = (0x280 - x) - w;
    sp30.h = h;
    if (sp30.w != 0) {
        ClearImage(&sp30,D_801CF0CA,D_801CF0CA,D_801CF0CA);
    }
    return;
}

/* 5C1FC 801809FC -O2 -msoft-float */
void DISPLAY_FOND640(void)
{
    s16 y = (SCREEN_HEIGHT * 2 - plan2_height) >> 1;
    s16 x = (SCREEN_WIDTH * 2 - plan2_width) >> 1;

    if (D_801E4B58 == true)
        y = 0;
    DISPLAY_ANYSIZE_PICTURE640((u32 *) D_801F4380, 0, 0, x, y, plan2_height, plan2_width);
}

/* 5C27C 80180A7C -O2 -msoft-float */
void DISPLAY_FOND_CONTINUE(void)
{
    DISPLAY_FOND3();
}

/* 5C29C 80180A9C -O2 -msoft-float */
void DISPLAY_FOND_SELECT(void)
{
    CLRSCR();
}
