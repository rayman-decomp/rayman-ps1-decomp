#include "cam_scroll_29B5C.h"

#ifdef BSS_DEFS
s16 h_scroll_speed;
s16 v_scroll_speed;
s16 scroll_start_x;
s16 scroll_start_y;
s16 scroll_end_x;
s16 scroll_end_y;
u8 scrollLocked;
s16 screen_trembling;
s16 screen_trembling2;
s16 screen_trembling3;
#endif

/* 29B5C 8014E35C -O2 -msoft-float */
s16 frapsol(s16 param_1)
{
    return ashr16(expsin[param_1], 7);
}

/* 29B98 8014E398 -O2 -msoft-float */
void DO_SCREEN_TREMBLE(void)
{
    s16 unk_1;

    if (screen_trembling != 0)
    {
        unk_1 = frapsol(screen_trembling);
        screen_trembling++;
        if (unk_1 == 0xFF)
        {
            unk_1 = 0;
            screen_trembling = 0;
        }
        ymap += unk_1;
    }
}

/* 29C14 8014E414 -O2 -msoft-float */
void DO_SCREEN_TREMBLE3(void)
{
    s16 unk_1 = expsin2[screen_trembling3];

    if (unk_1 != 0xFF)
    {
        screen_trembling3++;
        ymap += unk_1;
    }
    else
        screen_trembling3 = 0;
}

/* 29C7C 8014E47C -O2 -msoft-float */
void DO_SCREEN_TREMBLE2(void)
{
    s16 unk_1 = expsin2[screen_trembling2];

    if (unk_1 != 0xFF)
    {
        screen_trembling2++;
        xmap += unk_1;
    }
    else
        screen_trembling2 = 0;
}

/* 29CE4 8014E4E4 -O2 -msoft-float */
void DO_SCROLL_MAP(s16 *h_speed, s16 *v_speed)
{
    if (*v_speed == 0xFF)
        *v_speed = 0;

    if (num_world == 6 && num_level == 4)
        *h_speed = 0;
    if (num_world == 5 && num_level == 11)
        *h_speed = 0;
    if (num_world == 5 && num_level == 3)
    {
        *h_speed = 0;
        *v_speed = 0;
    }

    DO_SCREEN_TREMBLE();
    if (screen_trembling2 > 0)
        DO_SCREEN_TREMBLE2();
    if (screen_trembling3 > 0)
        DO_SCREEN_TREMBLE3();

    ymap += *v_speed;
    xmap += *h_speed;
    if (xmap < scroll_start_x)
    {
        *h_speed += scroll_start_x - xmap;
        xmap = scroll_start_x;
        dhspeed = 0;
    }
    else if (xmap > scroll_end_x)
    {
        *h_speed -= xmap - scroll_end_x;
        xmap = scroll_end_x;
        dhspeed = 0;
    }

    if (ymap < scroll_start_y)
    {
        *v_speed += scroll_start_y - ymap;
        ymap = scroll_start_y;
        dvspeed = 0;
    }
    else if (ymap > scroll_end_y)
    {
        *v_speed -= ymap - scroll_end_y;
        ymap = scroll_end_y;
        dvspeed = 0;
    }

    calc_obj_pos_map(&ray);
}
