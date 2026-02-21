#include "draw/draw_548CC.h"

#ifdef BSS_DEFS
DVECTOR D_801E4E60[16];
DVECTOR D_801E4EA8[16];
DVECTOR D_801FAA48[2];
DVECTOR D_801FAA58[2];
s32 D_801F8168;
s32 D_801F816C;
s32 PS1_TPage_x;
s32 PS1_TPage_y;
#endif

/* 548CC 801790CC -O2 -msoft-float */
void InitLuciolle(Display *display)
{
    u16 i;
    u16 unk_2;
    u16 unk_1 = 0x100;

    for (i = 0; i < LEN(display->field_0x66dc_0x673b); i++)
    {
        SetTile(display->field_0x66dc_0x673b + i);
        (display->field_0x66dc_0x673b + i)->r0 = 0;
        (display->field_0x66dc_0x673b + i)->g0 = 0;
        (display->field_0x66dc_0x673b + i)->b0 = 0;
    }

    i = 0;
    unk_2 = 0;
    while (i < LEN(D_801E4E60))
    {
        D_801E4E60[i].vx = rcos(unk_2) * 45 >> 12;
        D_801E4E60[i].vy = rsin(unk_2) * 45 >> 12;
        D_801E4EA8[i].vx = (u32) rcos(unk_2) * 5 >> 8;
        D_801E4EA8[i].vy = (u32) rsin(unk_2) * 5 >> 8;
        i++;
        unk_2 -= unk_1;
    }
}

/* 54A18 80179218 -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/draw/draw_548CC", Luciolle);
#else
/* score of 7043 */
/*
every save to stack is sh instr.
80179248 var_v1 = rand()
80179260 var_v0 = var_v1 - ((var_v1 / 4) * 8);
80179264 var_a0 = var_v0 + 0x97; (s16)
8017926c var_a1 = var_a0 >> 2;
80179270 var_v1 = var_a0 >> 1;
80179278 sp38 = var_a1 + var_v1;
8017927c var_s4 = var_v0;
80179280 sp10 = var_a1;
80179290 sp20 = var_v1;
80179294 sp18 = sp10;
801792a0 sp28 = sp20;
801792ac sp30 = var_a0;
801792b8 sp40 = sp38;
*/
void Luciolle(void)
{
    s16 unk_1;
    s16 unk_y_2_3_fourth;
    s16 unk_x_2_3_first;
    s16 unk_y_2_3_snd;
    s16 unk_y_2_3_third;
    s16 unk_x_2_3_fourth;
    s16 unk_x_2_3_third;
    s16 unk_x_2_3_snd;
    s16 unk_y_2_3_first;
    s32 var_a1_1;
    s16 var_s3_3;
    s32 temp_s1_2;
    s32 temp_v0_1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    u16 var_s2_1;
    s32 var_v0;
    s16 unk_1_div_4;
    s16 unk_1_div_2;
    s16 sp38;
    s16 var_s4;
    s16 sp10;
    s16 sp20;
    s16 sp18;
    s16 sp28;
    s16 sp30;
    s16 sp40;
    u16 test_1 = 0x100;

    var_v0 = rand();
    temp_v0_1 = var_v0 - ((var_v0 / 4) * 4);
    unk_1 = temp_v0_1 + 0x97;
    unk_1_div_4 = unk_1 >> 2;
    unk_1_div_2 = unk_1 >> 1;
    sp38 = unk_1_div_4 + unk_1_div_2;
    var_s4 = temp_v0_1;
    sp10 = unk_1_div_4;
    sp20 = unk_1_div_2;
    sp18 = sp10;
    sp28 = sp20;
    sp30 = unk_1;
    sp40 = sp38;
    if (dead_time >= 0x40U && PS1_CanPlayDeathMusic != 0) /* bad jump? */
    {
        var_s3_3 = 0;
        var_s2_1 = 0;
        if (D_801CF06C != 0)
        {
            while (var_s3_3 < 0x10)
            {
                D_801E4E60[var_s3_3].vx = ((rcos(var_s2_1) * 0x2D) >> 0xC);
                D_801E4E60[var_s3_3].vy = ((rsin(var_s2_1) * 0x2D) >> 0xC);
                D_801E4EA8[var_s3_3].vx = ((u32) (rcos(var_s2_1) * 5) >> 8);
                D_801E4EA8[var_s3_3].vy = ((u32) (rsin(var_s2_1) * 5) >> 8);
                var_s3_3 = var_s3_3 + 1;
                var_s2_1 -= test_1;
            }
            D_801CF064 = 0;
            D_801CF068 = 1;
            D_801CF066 = 1;
            D_801CF06C = 0;
        }
        D_801CF418 = x_luc - sp20; /* TODO: stack? */
        D_801CF428 = var_s4 + x_luc;
        D_801CF420 = y_luc - sp28;
        D_801CF430 = var_s4 + y_luc;
    }
    else
    {
        var_s3_3 = 0;
block_9:
        var_s2_1 = 0;
        D_801CF066 = 0x2D - D_801CF064;
        D_801CF068 = 0x50 - D_801CF064;
        while (var_s3_3 < 0x10)
        {
            if (D_801CF066 > 0)
            {
                D_801E4E60[var_s3_3].vx = ((D_801CF066 * rcos(var_s2_1)) >> 0xC);
                D_801E4E60[var_s3_3].vy = ((D_801CF066 * rsin(var_s2_1)) >> 0xC);
            }
            if (D_801CF068 > 0)
            {
                D_801E4EA8[var_s3_3].vx = ((D_801CF068 * rcos(var_s2_1)) >> 0xC);
                D_801E4EA8[var_s3_3].vy = ((D_801CF068 * rsin(var_s2_1)) >> 0xC);
            }
            var_s3_3 = var_s3_3 + 1;
            var_s2_1 -= test_1;
        }
        D_801CF06C = 1;
        D_801CF064 = D_801CF064 + 1;
    }
    var_s3_3 = 0;
    while (var_s3_3 < 0x10)
    {
        SetPolyF4(&PS1_CurrentDisplay->unk_poly_f4s[var_s3_3]);
        SetSemiTrans(&PS1_CurrentDisplay->unk_poly_f4s[var_s3_3], 0);
        SetShadeTex(&PS1_CurrentDisplay->unk_poly_f4s[var_s3_3], 1);

        (PS1_CurrentDisplay->unk_poly_f4s + var_s3_3)->r0 = 0; /* TODO: bleh */
        PS1_CurrentDisplay->unk_poly_f4s[var_s3_3].g0 = 0;
        PS1_CurrentDisplay->unk_poly_f4s[var_s3_3].b0 = 0;
        SetPolyG4(&PS1_CurrentDisplay->unk_poly_g4s[var_s3_3]);
        SetSemiTrans(&PS1_CurrentDisplay->unk_poly_g4s[var_s3_3], 1);
        SetShadeTex(&PS1_CurrentDisplay->unk_poly_g4s[var_s3_3], 1);
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].r0 = 0x0A;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].g0 = 0x1E;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].b0 = 0x50;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].r1 = 0x0A;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].g1 = 0x1E;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].b1 = 0x50;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].r2 = 0xFF;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].g2 = 0xFF;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].b2 = 0xFF;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].r3 = 0xFF;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].g3 = 0xFF;
        PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].b3 = 0xFF;
        /*temp_s1_2 = var_s3_3 * 0x1C;*/
        SetPolyG3(&PS1_CurrentDisplay->unk_poly_g3s[var_s3_3]);
        SetSemiTrans(&PS1_CurrentDisplay->unk_poly_g3s[var_s3_3], 1);
        SetShadeTex(&PS1_CurrentDisplay->unk_poly_g3s[var_s3_3], 1);
        PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].r0 = 0x0A;
        PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].g0 = 0x1E;
        PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].b0 = 0x64;
        PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].r1 = 0x0A;
        PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].g1 = 0x1E;
        PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].b1 = 0x50;
        PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].r2 = 0x0A;
        PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].g2 = 0x1E;
        PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].b2 = 0x50;
        var_s3_3 = var_s3_3 + 1;
        /*(temp_s1_2 + PS1_CurrentDisplay)->unk6B12 = 0x50;*/
    }
    if ((D_801CF066 > 0) || (D_801CF068 > 0))
    {

        PS1_CurrentDisplay->field_0x66dc_0x673b[0].x0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].y0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].w = 0x0140;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].h = MAX_1(D_801CF420, 0);
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].code &= 0xFD;

        PS1_CurrentDisplay->field_0x66dc_0x673b[1].x0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[1].y0 = unk_1 + D_801CF420;
        PS1_CurrentDisplay->field_0x66dc_0x673b[1].w = 0x0140;
        PS1_CurrentDisplay->field_0x66dc_0x673b[1].h = MAX_1(0xF0 - D_801CF420 - unk_1, 0); /* order of subs correct? */
        PS1_CurrentDisplay->field_0x66dc_0x673b[1].code &= 0xFD;

        PS1_CurrentDisplay->field_0x66dc_0x673b[2].x0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[2].y0 = D_801CF420;
        PS1_CurrentDisplay->field_0x66dc_0x673b[2].w = MAX_1(D_801CF418, 0);
        PS1_CurrentDisplay->field_0x66dc_0x673b[2].h = unk_1;
        PS1_CurrentDisplay->field_0x66dc_0x673b[2].code &= 0xFD;

        PS1_CurrentDisplay->field_0x66dc_0x673b[3].x0 = sp30 + D_801CF418;
        PS1_CurrentDisplay->field_0x66dc_0x673b[3].y0 = D_801CF420;
        PS1_CurrentDisplay->field_0x66dc_0x673b[3].code &= 0xFD; /* ??? */
        PS1_CurrentDisplay->field_0x66dc_0x673b[3].w = MAX_1(0x140 - D_801CF418 - sp30, 0); /* order of subs correct? */
        PS1_CurrentDisplay->field_0x66dc_0x673b[3].h = unk_1;

        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x66dc_0x673b[0]);
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x66dc_0x673b[1]);
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x66dc_0x673b[2]);
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x66dc_0x673b[3]);
        goto skipped_1;
addprim_1:
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].x0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].y0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].w = 0x0140;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].h = 0x00F0;
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x66dc_0x673b[0]);
        return;
skipped_1:
        unk_x_2_3_first = sp30 + D_801CF418;
        unk_y_2_3_fourth = unk_1 + D_801CF420;
        unk_x_2_3_snd = sp40 + D_801CF418;
        unk_y_2_3_third = sp38 + D_801CF420;
        unk_x_2_3_third = sp20 + D_801CF418;
        unk_y_2_3_first = sp28 + D_801CF420;
        unk_x_2_3_fourth = sp10 + D_801CF418;
        unk_y_2_3_snd = sp18 + D_801CF420;

        PS1_CurrentDisplay->unk_poly_f4s[0].x0 = D_801E4EA8[0].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0].y0 = D_801E4EA8[0].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0].x1 = D_801E4EA8[1].vx + D_801CF428;

        PS1_CurrentDisplay->unk_poly_f4s[0].x2 = unk_x_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[0].x3 = unk_x_2_3_first;

        PS1_CurrentDisplay->unk_poly_f4s[0].y2 = unk_y_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[0].y1 = D_801E4EA8[1].vy + D_801CF430;

        PS1_CurrentDisplay->unk_poly_f4s[0].y3 = unk_y_2_3_snd;
        PS1_CurrentDisplay->unk_poly_f4s[1].x0 = D_801E4EA8[1].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[1].y0 = D_801E4EA8[1].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[1].x1 = D_801E4EA8[2].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[1].x2 = unk_x_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[1].y2 = unk_y_2_3_snd;
        PS1_CurrentDisplay->unk_poly_f4s[1].x3 = unk_x_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[1].y3 = D_801CF420;
        PS1_CurrentDisplay->unk_poly_f4s[1].y1 = D_801E4EA8[2].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[2].x0 = D_801E4EA8[2].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[2].y0 = D_801E4EA8[2].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[2].x1 = D_801E4EA8[3].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[2].x2 = unk_x_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[2].y2 = D_801CF420;
        PS1_CurrentDisplay->unk_poly_f4s[2].y3 = D_801CF420;

        PS1_CurrentDisplay->unk_poly_f4s[2].x3 = unk_x_2_3_snd;
        PS1_CurrentDisplay->unk_poly_f4s[2].y1 = D_801E4EA8[3].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[3].x0 = D_801E4EA8[3].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[3].y0 = D_801E4EA8[3].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[3].x1 = D_801E4EA8[4].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[3].x2 = unk_x_2_3_snd;
        PS1_CurrentDisplay->unk_poly_f4s[3].y2 = D_801CF420;
        PS1_CurrentDisplay->unk_poly_f4s[3].y3 = D_801CF420;

        PS1_CurrentDisplay->unk_poly_f4s[3].x3 = unk_x_2_3_third;
        PS1_CurrentDisplay->unk_poly_f4s[3].y1 = D_801E4EA8[4].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[4].x0 = D_801E4EA8[4].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[4].y0 = D_801E4EA8[4].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[4].x1 = D_801E4EA8[5].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[4].x2 = unk_x_2_3_third;
        PS1_CurrentDisplay->unk_poly_f4s[4].y2 = D_801CF420;

        PS1_CurrentDisplay->unk_poly_f4s[4].x3 = unk_x_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[4].y3 = D_801CF420;
        PS1_CurrentDisplay->unk_poly_f4s[4].y1 = D_801E4EA8[5].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[5].x0 = D_801E4EA8[5].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[5].y0 = D_801E4EA8[5].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[5].x1 = D_801E4EA8[6].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[5].x2 = unk_x_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[5].y2 = D_801CF420;
        PS1_CurrentDisplay->unk_poly_f4s[5].x3 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[5].y3 = D_801CF420;
        PS1_CurrentDisplay->unk_poly_f4s[5].y1 = D_801E4EA8[6].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[6].x0 = D_801E4EA8[6].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[6].y0 = D_801E4EA8[6].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[6].x1 = D_801E4EA8[7].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[6].x2 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[6].y2 = D_801CF420;
        PS1_CurrentDisplay->unk_poly_f4s[6].x3 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[6].y3 = unk_y_2_3_snd;
        PS1_CurrentDisplay->unk_poly_f4s[6].y1 = D_801E4EA8[7].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[7].x0 = D_801E4EA8[7].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[7].y0 = D_801E4EA8[7].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[7].x1 = D_801E4EA8[8].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[7].x2 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[7].y2 = unk_y_2_3_snd;
        PS1_CurrentDisplay->unk_poly_f4s[7].x3 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[7].y3 = unk_y_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[7].y1 = D_801E4EA8[8].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[8].x0 = D_801E4EA8[8].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[8].y0 = D_801E4EA8[8].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[8].x1 = D_801E4EA8[9].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[8].x2 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[8].y2 = unk_y_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[8].x3 = D_801CF418;

        PS1_CurrentDisplay->unk_poly_f4s[8].y3 = unk_y_2_3_third;
        PS1_CurrentDisplay->unk_poly_f4s[8].y1 = D_801E4EA8[9].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[9].x0 = D_801E4EA8[9].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[9].y0 = D_801E4EA8[9].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[9].x1 = D_801E4EA8[10].vx + D_801CF428;

        PS1_CurrentDisplay->unk_poly_f4s[9].x2 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[9].y2 = unk_y_2_3_third;
        PS1_CurrentDisplay->unk_poly_f4s[9].x3 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[9].y3 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[9].y1 = D_801E4EA8[10].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[9].x0 = D_801E4EA8[9].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[9].y0 = D_801E4EA8[9].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[9].x1 = D_801E4EA8[10].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[9].x2 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[9].y2 = unk_y_2_3_third;
        PS1_CurrentDisplay->unk_poly_f4s[9].x3 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[9].y1 = D_801E4EA8[10].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[9].y3 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xA].x0 = D_801E4EA8[10].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xA].y0 = D_801E4EA8[10].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xA].x1 = D_801E4EA8[11].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xA].x2 = D_801CF418;
        PS1_CurrentDisplay->unk_poly_f4s[0xA].y2 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xA].x3 = unk_x_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xA].y3 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xA].y1 = D_801E4EA8[11].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xB].x0 = D_801E4EA8[11].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xB].y0 = D_801E4EA8[11].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xB].x1 = D_801E4EA8[12].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xB].x2 = unk_x_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xB].y2 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xB].x3 = unk_x_2_3_third;
        PS1_CurrentDisplay->unk_poly_f4s[0xB].y3 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xB].y1 = D_801E4EA8[12].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xC].x0 = D_801E4EA8[12].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xC].y0 = D_801E4EA8[12].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xC].x1 = D_801E4EA8[13].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xC].x2 = unk_x_2_3_third;
        PS1_CurrentDisplay->unk_poly_f4s[0xC].y1 = D_801E4EA8[13].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xC].y2 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xC].x3 = unk_x_2_3_snd;
        PS1_CurrentDisplay->unk_poly_f4s[0xC].y3 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xD].x0 = D_801E4EA8[13].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xD].y0 = D_801E4EA8[13].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xD].x1 = D_801E4EA8[14].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xD].x2 = unk_x_2_3_snd;
        PS1_CurrentDisplay->unk_poly_f4s[0xD].y2 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xD].x3 = unk_x_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[0xD].y3 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xD].y1 = D_801E4EA8[14].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xE].x0 = D_801E4EA8[14].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xE].y0 = D_801E4EA8[14].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xE].x1 = D_801E4EA8[15].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xE].x2 = unk_x_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[0xE].y2 = unk_y_2_3_fourth;
        PS1_CurrentDisplay->unk_poly_f4s[0xE].x3 = unk_x_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[0xE].y3 = unk_y_2_3_third;
        PS1_CurrentDisplay->unk_poly_f4s[0xE].y1 = D_801E4EA8[15].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xF].x0 = D_801E4EA8[15].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xF].y0 = D_801E4EA8[15].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xF].x1 = D_801E4EA8[0].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_f4s[0xF].y1 = D_801E4EA8[0].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_f4s[0xF].x2 = unk_x_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[0xF].y2 = unk_y_2_3_third;
        PS1_CurrentDisplay->unk_poly_f4s[0xF].x3 = unk_x_2_3_first;
        PS1_CurrentDisplay->unk_poly_f4s[0xF].y3 = unk_y_2_3_first;
        var_s3_3 = 0;
        while (var_s3_3 < 0x10)
        {
            AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->unk_poly_f4s[var_s3_3]);
            var_s3_3 = var_s3_3 + 1;
        }
        var_s3_3 = 0;
        while (var_s3_3 < 0xF)
        {
            temp_v1_2 = var_s3_3 + 1;
            PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].x0 = D_801E4E60[var_s3_3].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].y0 = D_801E4E60[var_s3_3].vy + D_801CF430;
            PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].x1 = D_801E4E60[temp_v1_2].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].y1 = D_801E4E60[temp_v1_2].vy + D_801CF430;
            PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].x2 = D_801E4EA8[var_s3_3].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].y2 = D_801E4EA8[var_s3_3].vy + D_801CF430;
            PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].x3 = D_801E4EA8[temp_v1_2].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g4s[var_s3_3].y3 = ((D_801E4EA8[temp_v1_2].vy) + D_801CF430);
            var_s3_3 = var_s3_3 + 1;
        }
        PS1_CurrentDisplay->unk_poly_g4s[0xF].x0 = D_801E4E60[15].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].y0 = D_801E4E60[15].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].x1 = D_801E4E60[0].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].y1 = D_801E4E60[0].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].x2 = D_801E4EA8[15].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].y2 = D_801E4EA8[15].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].x3 = D_801E4EA8[0].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].y3 = D_801E4EA8[0].vy + D_801CF430;

        var_s3_3 = 0;
        while (var_s3_3 < 0x10)
        {
            AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->unk_poly_g4s[var_s3_3]);
            var_s3_3 = var_s3_3 + 1;
        }
        PS1_CurrentDisplay->drawing_environment.tpage = GetTPage(1, 2, 0x00000100, 0);
        SetDrawEnv(&PS1_CurrentDisplay->map_drawing_environment_primitives[D_801E4BE0], &PS1_CurrentDisplay->drawing_environment);
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->map_drawing_environment_primitives[D_801E4BE0]);
        var_s3_3 = 0;
        D_801E4BE0 = D_801E4BE0 + 1;
        while (var_s3_3 < 0xF)
        {
            (PS1_CurrentDisplay->unk_poly_g3s + var_s3_3)->x0 = D_801CF428;
            PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].y0 = D_801CF430;
            PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].x1 = D_801E4E60[var_s3_3].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].y1 = (D_801E4E60[var_s3_3].vy) + D_801CF430;
            PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].x2 = D_801E4E60[var_s3_3 + 1].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g3s[var_s3_3].y2 = ((D_801E4E60[var_s3_3 + 1].vy) + D_801CF430);
            var_s3_3 = var_s3_3 + 1;
        }
        PS1_CurrentDisplay->unk_poly_g3s[0xF].x0 = D_801CF428;
        PS1_CurrentDisplay->unk_poly_g3s[0xF].y0 = D_801CF430;
        PS1_CurrentDisplay->unk_poly_g3s[0xF].x1 = D_801E4E60[15].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g3s[0xF].y1 = D_801E4E60[15].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_g3s[0xF].x2 = D_801E4E60[0].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g3s[0xF].y2 = D_801E4E60[0].vy + D_801CF430;

        var_s3_3 = 0;
        while (var_s3_3 < 0x10)
        {
            AddPrim(&PS1_CurrentDisplay->ordering_table[5], &PS1_CurrentDisplay->unk_poly_g3s[var_s3_3]);
            var_s3_3 = var_s3_3 + 1;
        }
        PS1_CurrentDisplay->drawing_environment.tpage = GetTPage(1, 2, 0x00000100, 0);
        SetDrawEnv(&PS1_CurrentDisplay->map_drawing_environment_primitives[D_801E4BE0], &PS1_CurrentDisplay->drawing_environment);
        AddPrim(&PS1_CurrentDisplay->ordering_table[5], &PS1_CurrentDisplay->map_drawing_environment_primitives[D_801E4BE0]);
        D_801E4BE0 = D_801E4BE0 + 1;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].code |= 2;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].h = unk_1;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].x0 = D_801CF418;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].y0 = D_801CF420;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].w = unk_1;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].r0 = 0x78;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].g0 = 0x78;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].b0 = 0x50;
        AddPrim(&PS1_CurrentDisplay->ordering_table[5], &PS1_CurrentDisplay->field_0x66dc_0x673b[4]);
        PS1_CurrentDisplay->drawing_environment.tpage = GetTPage(1, 1, 0x00000100, 0);
        SetDrawEnv(&PS1_CurrentDisplay->map_drawing_environment_primitives[D_801E4BE0], &PS1_CurrentDisplay->drawing_environment);
        AddPrim(&PS1_CurrentDisplay->ordering_table[5], &PS1_CurrentDisplay->map_drawing_environment_primitives[D_801E4BE0]);
        D_801E4BE0 = D_801E4BE0 + 1;
        return;
    }
    goto addprim_1;
}
#endif

/* 55EF8 8017A6F8 -O2 -msoft-float */
void volet_perfect_bonus(void)
{
    s32 unk_1;
    u16 unk_2;
    u16 unk_3 = 160;
    u16 unk_4 = 120;
    u16 unk_5 = 256;
    u16 i = 0; /* couldn't move this to create for-loop */
    CVECTOR *col_1 = &D_801CF070;
    CVECTOR *col_2 = &D_801CF074;
    CVECTOR *col_3 = &D_801CF078;
    CVECTOR *col_4 = &D_801CF07C;

    while (i < LEN(PS1_CurrentDisplay->unk_poly_g3s))
    {
        SetPolyG3(&PS1_CurrentDisplay->unk_poly_g3s[i]);
        SetSemiTrans(&PS1_CurrentDisplay->unk_poly_g3s[i], false);
        SetShadeTex(&PS1_CurrentDisplay->unk_poly_g3s[i], true);
        unk_1 = i;
        unk_1 &= 3;
        if (unk_1 == 0)
        {
            (PS1_CurrentDisplay->unk_poly_g3s + i)->r1 = col_1->r;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->g1 = col_1->g;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->b1 = col_1->b;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->r2 = col_2->r;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->g2 = col_2->g;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->b2 = col_2->b;
        }
        else if (unk_1 == 1)
        {
            (PS1_CurrentDisplay->unk_poly_g3s + i)->r1 = col_2->r;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->g1 = col_2->g;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->b1 = col_2->b;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->r2 = col_3->r;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->g2 = col_3->g;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->b2 = col_3->b;
        }
        else if (unk_1 == 2)
        {
            (PS1_CurrentDisplay->unk_poly_g3s + i)->r1 = col_3->r;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->g1 = col_3->g;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->b1 = col_3->b;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->r2 = col_4->r;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->g2 = col_4->g;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->b2 = col_4->b;
        }
        else
        {
            (PS1_CurrentDisplay->unk_poly_g3s + i)->r1 = col_4->r;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->g1 = col_4->g;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->b1 = col_4->b;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->r2 = col_1->r;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->g2 = col_1->g;
            (PS1_CurrentDisplay->unk_poly_g3s + i)->b2 = col_1->b;
        }
        (PS1_CurrentDisplay->unk_poly_g3s + i)->r0 = 0;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->g0 = 0;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->b0 = 0;

        D_801FAA48[0].vx = (D_801CF08A * rcos(D_801CF086) >> 12) + unk_3;
        D_801FAA48[0].vy = (D_801CF08A * rsin(D_801CF086) >> 12) + unk_4;
        unk_2 = D_801CF086 + unk_5;
        D_801FAA48[1].vx = (D_801CF08A * rcos(unk_2) >> 12) + unk_3;
        D_801FAA48[1].vy = (D_801CF08A * rsin(unk_2) >> 12) + unk_4;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->x0 = unk_3;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->y0 = unk_4;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->x1 = D_801FAA48[0].vx;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->y1 = D_801FAA48[0].vy;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->x2 = D_801FAA48[1].vx;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->y2 = D_801FAA48[1].vy;
        AddPrim(PS1_CurrentDisplay->ordering_table, &PS1_CurrentDisplay->unk_poly_g3s[i]);
        D_801CF086 += unk_5;
        i++;
    }
    D_801CF088 += 10;
    D_801CF086 = D_801CF088;
}

/* 5638C 8017AB8C -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/draw/draw_548CC", volet);
#else
/* clean up */
void volet(void)
{
    s32 unk_2;
    u16 ind_1;
    u16 ind_2;
    u16 unk_1 = 256;
    u16 offs_x = SCREEN_WIDTH / 2;
    u16 offs_y = SCREEN_HEIGHT / 2;
    u16 cnt_1 = 0;

    while (cnt_1 < LEN(PS1_CurrentDisplay->unk_poly_g4s)) /* or unk_poly_g3s? */
    {
        SetPolyG4(PS1_CurrentDisplay->unk_poly_g4s + cnt_1);
        SetSemiTrans(PS1_CurrentDisplay->unk_poly_g4s + cnt_1, false);
        SetShadeTex(PS1_CurrentDisplay->unk_poly_g4s + cnt_1, true);
        SetPolyG3(PS1_CurrentDisplay->unk_poly_g3s + cnt_1);
        SetSemiTrans(PS1_CurrentDisplay->unk_poly_g3s + cnt_1, false);
        SetShadeTex(PS1_CurrentDisplay->unk_poly_g3s + cnt_1, true);

        unk_2 = cnt_1; /* TODO: ??? */
        ind_1 = unk_2 & 3;
        if (ind_1 != 3)
            ind_2 = ind_1 + 1;
        else
            ind_2 = 0;

        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->r0 = D_801C7EAC[ind_1].r;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->g0 = D_801C7EAC[ind_1].g;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->b0 = D_801C7EAC[ind_1].b;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->r1 = D_801C7EAC[ind_2].r;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->g1 = D_801C7EAC[ind_2].g;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->b1 = D_801C7EAC[ind_2].b;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->r1 = D_801C7EAC[ind_1].r;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->g1 = D_801C7EAC[ind_1].g;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->b1 = D_801C7EAC[ind_1].b;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->r2 = D_801C7EAC[ind_2].r;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->g2 = D_801C7EAC[ind_2].g;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->b2 = D_801C7EAC[ind_2].b;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->r2 = 0;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->g2 = 0;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->b2 = 0;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->r3 = 0;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->g3 = 0;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->b3 = 0;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->r0 = 0;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->g0 = 0;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->b0 = 0;

        D_801FAA48[0].vx = (D_801CF096 * rcos(D_801CF090) >> 12) + offs_x;
        D_801FAA48[0].vy = (D_801CF096 * rsin(D_801CF090) >> 12) + offs_y;
        D_801FAA58[0].vx = (D_801CF098 * rcos(D_801CF090) >> 12) + offs_x;
        D_801FAA58[0].vy = (D_801CF098 * rsin(D_801CF090) >> 12) + offs_y;
        ind_1 = D_801CF090 + unk_1; /* TODO: ??? */
        D_801FAA48[1].vx = (D_801CF096 * rcos(ind_1) >> 12) + offs_x;
        D_801FAA48[1].vy = (D_801CF096 * rsin(ind_1) >> 12) + offs_y;
        D_801FAA58[1].vx = (D_801CF098 * rcos(ind_1) >> 12) + offs_x;
        D_801FAA58[1].vy = (D_801CF098 * rsin(ind_1) >> 12) + offs_y;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->x0 = D_801FAA48[0].vx;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->y0 = D_801FAA48[0].vy;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->x1 = D_801FAA48[1].vx;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->y1 = D_801FAA48[1].vy;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->x2 = D_801FAA58[0].vx;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->y2 = D_801FAA58[0].vy;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->x3 = D_801FAA58[1].vx;
        (PS1_CurrentDisplay->unk_poly_g4s + cnt_1)->y3 = D_801FAA58[1].vy;
        AddPrim(PS1_CurrentDisplay->ordering_table, PS1_CurrentDisplay->unk_poly_g4s + cnt_1);
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->x0 = offs_x;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->y0 = offs_y;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->x1 = D_801FAA48[0].vx;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->y1 = D_801FAA48[0].vy;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->x2 = D_801FAA48[1].vx;
        (PS1_CurrentDisplay->unk_poly_g3s + cnt_1)->y2 = D_801FAA48[1].vy;
        AddPrim(PS1_CurrentDisplay->ordering_table, PS1_CurrentDisplay->unk_poly_g3s + cnt_1);
        D_801CF090 += unk_1;
        cnt_1++;
    }
    D_801CF096 = (rsin(D_801CF094) * 75 >> 12) + 105;
    (PS1_CurrentDisplay->drawing_environment).tpage = GetTPage(1, 0, 256, 0);
    SetDrawEnv(
        PS1_CurrentDisplay->map_drawing_environment_primitives + D_801E4BE0,
        &PS1_CurrentDisplay->drawing_environment
    );
    AddPrim(
        &PS1_CurrentDisplay->ordering_table[10],
        PS1_CurrentDisplay->map_drawing_environment_primitives + D_801E4BE0
    );
    D_801E4BE0++;

    D_801CF090 = D_801CF092;
    D_801CF094 += 10;
    D_801CF092 += 10;
}
#endif

/* 56A60 8017B260 -O2 -msoft-float */
void getparam(u16 param_1)
{
    if (GetGraphType() != 0)
    {
        D_801F8168 = (param_1 >> 9);
        D_801F816C = (param_1 >> 7) & 3;
        PS1_TPage_y = (param_1 << 3) & 768;
        PS1_TPage_x = (param_1 << 6) & 1023;
    }
    else
    {
        D_801F8168 = (param_1 >> 7);
        D_801F816C = (param_1 >> 5) & 3;
        PS1_TPage_y = (param_1 << 4) & 256;
        PS1_TPage_x = (param_1 << 6) & 1023;
    }
}
