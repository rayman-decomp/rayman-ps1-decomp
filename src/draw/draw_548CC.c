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
/* 54A18 80179218 -O2 -msoft-float */
void Luciolle(void)
{
    s16 size;
    s16 x_1_4;
    s16 y_1_4;
    s16 x_1_2;
    s16 y_1_2;
    s16 x_full;
    s16 y_3_4;
    s16 x_3_4;
    s16 i;
    s32 next;
    u16 angle;
    s16 jitter;
    u16 angle_step = 0x100;

    /* The do-while(0) wrappers are required to match. */
    do { size = (jitter = rand() % 4) + 0x97; } while (0);
    x_1_4 = size >> 2;
    x_1_2 = size >> 1;
    y_3_4 = (size >> 2) + (size >> 1);
    y_1_4 = size >> 2;
    y_1_2 = size >> 1;
    x_full = size;
    x_3_4 = y_3_4;
    if (dead_time >= 0x40U && PS1_CanPlayDeathMusic != 0)
    {
        if (D_801CF06C != 0)
        {
            for (i = 0, angle = 0; i < 0x10; i++, angle -= angle_step)
            {
                D_801E4E60[i].vx = ((rcos(angle) * 0x2D) >> 0xC);
                D_801E4E60[i].vy = ((rsin(angle) * 0x2D) >> 0xC);
                D_801E4EA8[i].vx = ((u32) (rcos(angle) * 5) >> 8);
                D_801E4EA8[i].vy = ((u32) (rsin(angle) * 5) >> 8);
            }
            D_801CF064 = 0;
            D_801CF068 = 1;
            D_801CF066 = 1;
            D_801CF06C = 0;
        }
        do { D_801CF418 = x_luc - x_1_2; } while (0);
        D_801CF428 = jitter + x_luc;
        D_801CF420 = y_luc - y_1_2;
        D_801CF430 = jitter + y_luc;
    }
    else
    {
        D_801CF066 = 0x2D - D_801CF064;
        D_801CF068 = 0x50 - D_801CF064;
        for (i = 0, angle = 0; i < 0x10; i++, angle -= angle_step)
        {
            if (D_801CF066 > 0)
            {
                D_801E4E60[i].vx = ((D_801CF066 * rcos(angle)) >> 0xC);
                D_801E4E60[i].vy = ((D_801CF066 * rsin(angle)) >> 0xC);
            }
            if (D_801CF068 > 0)
            {
                D_801E4EA8[i].vx = ((D_801CF068 * rcos(angle)) >> 0xC);
                D_801E4EA8[i].vy = ((D_801CF068 * rsin(angle)) >> 0xC);
            }
        }
        D_801CF06C = 1;
        D_801CF064 = D_801CF064 + 1;
    }
    for (i = 0; i < 0x10; i++)
    {
        SetPolyF4(&PS1_CurrentDisplay->unk_poly_f4s[i]);
        SetSemiTrans(&PS1_CurrentDisplay->unk_poly_f4s[i], 0);
        SetShadeTex(&PS1_CurrentDisplay->unk_poly_f4s[i], 1);

        (PS1_CurrentDisplay->unk_poly_f4s + i)->r0 = 0;
        (PS1_CurrentDisplay->unk_poly_f4s + i)->g0 = 0;
        (PS1_CurrentDisplay->unk_poly_f4s + i)->b0 = 0;
        SetPolyG4(&PS1_CurrentDisplay->unk_poly_g4s[i]);
        SetSemiTrans(&PS1_CurrentDisplay->unk_poly_g4s[i], 1);
        SetShadeTex(&PS1_CurrentDisplay->unk_poly_g4s[i], 1);
        (PS1_CurrentDisplay->unk_poly_g4s + i)->r0 = 0x0A;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->g0 = 0x1E;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->b0 = 0x50;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->r1 = 0x0A;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->g1 = 0x1E;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->b1 = 0x50;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->r2 = 0xFF;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->g2 = 0xFF;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->b2 = 0xFF;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->r3 = 0xFF;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->g3 = 0xFF;
        (PS1_CurrentDisplay->unk_poly_g4s + i)->b3 = 0xFF;

        SetPolyG3(&PS1_CurrentDisplay->unk_poly_g3s[i]);
        SetSemiTrans(&PS1_CurrentDisplay->unk_poly_g3s[i], 1);
        SetShadeTex(&PS1_CurrentDisplay->unk_poly_g3s[i], 1);
        (PS1_CurrentDisplay->unk_poly_g3s + i)->r0 = 0x0A;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->g0 = 0x1E;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->b0 = 0x64;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->r1 = 0x0A;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->g1 = 0x1E;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->b1 = 0x50;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->r2 = 0x0A;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->g2 = 0x1E;
        (PS1_CurrentDisplay->unk_poly_g3s + i)->b2 = 0x50;
    }
    if ((D_801CF066 > 0) || (D_801CF068 > 0))
    {
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].x0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].y0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].w = 0x0140;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].h = MAX_1(D_801CF420, 0);
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].code &= 0xFD;

        PS1_CurrentDisplay->field_0x66dc_0x673b[1].x0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[1].y0 = size + D_801CF420;
        PS1_CurrentDisplay->field_0x66dc_0x673b[1].w = 0x0140;
        PS1_CurrentDisplay->field_0x66dc_0x673b[1].h = MAX_1(0xF0 - D_801CF420 - size, 0);
        PS1_CurrentDisplay->field_0x66dc_0x673b[1].code &= 0xFD;

        PS1_CurrentDisplay->field_0x66dc_0x673b[2].x0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[2].y0 = D_801CF420;
        PS1_CurrentDisplay->field_0x66dc_0x673b[2].w = MAX_1(D_801CF418, 0);
        PS1_CurrentDisplay->field_0x66dc_0x673b[2].h = size;
        PS1_CurrentDisplay->field_0x66dc_0x673b[2].code &= 0xFD;

        PS1_CurrentDisplay->field_0x66dc_0x673b[3].x0 = x_full + D_801CF418;
        PS1_CurrentDisplay->field_0x66dc_0x673b[3].y0 = D_801CF420;
        PS1_CurrentDisplay->field_0x66dc_0x673b[3].code &= 0xFD;
        PS1_CurrentDisplay->field_0x66dc_0x673b[3].w = MAX_1(0x140 - D_801CF418 - x_full, 0);
        PS1_CurrentDisplay->field_0x66dc_0x673b[3].h = size;

        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x66dc_0x673b[0]);
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x66dc_0x673b[1]);
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x66dc_0x673b[2]);
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x66dc_0x673b[3]);
        /* The goto layout is required to match. */
        goto skipped_1;
addprim_1:
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].x0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].y0 = 0;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].w = 0x0140;
        PS1_CurrentDisplay->field_0x66dc_0x673b[0].h = 0x00F0;
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x66dc_0x673b[0]);
        return;
skipped_1:

        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[0], D_801E4EA8[0].vx + D_801CF428, D_801E4EA8[0].vy + D_801CF430, D_801E4EA8[1].vx + D_801CF428, D_801E4EA8[1].vy + D_801CF430, (x_full + D_801CF418), (y_1_2 + D_801CF420), (x_full + D_801CF418), (y_1_4 + D_801CF420));
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[1], D_801E4EA8[1].vx + D_801CF428, D_801E4EA8[1].vy + D_801CF430, D_801E4EA8[2].vx + D_801CF428, D_801E4EA8[2].vy + D_801CF430, (x_full + D_801CF418), (y_1_4 + D_801CF420), (x_full + D_801CF418), D_801CF420);
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[2], D_801E4EA8[2].vx + D_801CF428, D_801E4EA8[2].vy + D_801CF430, D_801E4EA8[3].vx + D_801CF428, D_801E4EA8[3].vy + D_801CF430, (x_full + D_801CF418), D_801CF420, (x_3_4 + D_801CF418), D_801CF420);
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[3], D_801E4EA8[3].vx + D_801CF428, D_801E4EA8[3].vy + D_801CF430, D_801E4EA8[4].vx + D_801CF428, D_801E4EA8[4].vy + D_801CF430, (x_3_4 + D_801CF418), D_801CF420, (x_1_2 + D_801CF418), D_801CF420);
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[4], D_801E4EA8[4].vx + D_801CF428, D_801E4EA8[4].vy + D_801CF430, D_801E4EA8[5].vx + D_801CF428, D_801E4EA8[5].vy + D_801CF430, (x_1_2 + D_801CF418), D_801CF420, (x_1_4 + D_801CF418), D_801CF420);
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[5], D_801E4EA8[5].vx + D_801CF428, D_801E4EA8[5].vy + D_801CF430, D_801E4EA8[6].vx + D_801CF428, D_801E4EA8[6].vy + D_801CF430, (x_1_4 + D_801CF418), D_801CF420, D_801CF418, D_801CF420);
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[6], D_801E4EA8[6].vx + D_801CF428, D_801E4EA8[6].vy + D_801CF430, D_801E4EA8[7].vx + D_801CF428, D_801E4EA8[7].vy + D_801CF430, D_801CF418, D_801CF420, D_801CF418, (y_1_4 + D_801CF420));
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[7], D_801E4EA8[7].vx + D_801CF428, D_801E4EA8[7].vy + D_801CF430, D_801E4EA8[8].vx + D_801CF428, D_801E4EA8[8].vy + D_801CF430, D_801CF418, (y_1_4 + D_801CF420), D_801CF418, (y_1_2 + D_801CF420));
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[8], D_801E4EA8[8].vx + D_801CF428, D_801E4EA8[8].vy + D_801CF430, D_801E4EA8[9].vx + D_801CF428, D_801E4EA8[9].vy + D_801CF430, D_801CF418, (y_1_2 + D_801CF420), D_801CF418, (y_3_4 + D_801CF420));
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[9], D_801E4EA8[9].vx + D_801CF428, D_801E4EA8[9].vy + D_801CF430, D_801E4EA8[10].vx + D_801CF428, D_801E4EA8[10].vy + D_801CF430, D_801CF418, (y_3_4 + D_801CF420), D_801CF418, (size + D_801CF420));
        /* Duplicate required to match. */
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[9], D_801E4EA8[9].vx + D_801CF428, D_801E4EA8[9].vy + D_801CF430, D_801E4EA8[10].vx + D_801CF428, D_801E4EA8[10].vy + D_801CF430, D_801CF418, (y_3_4 + D_801CF420), D_801CF418, (size + D_801CF420));
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[10], D_801E4EA8[10].vx + D_801CF428, D_801E4EA8[10].vy + D_801CF430, D_801E4EA8[11].vx + D_801CF428, D_801E4EA8[11].vy + D_801CF430, D_801CF418, (size + D_801CF420), (x_1_4 + D_801CF418), (size + D_801CF420));
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[11], D_801E4EA8[11].vx + D_801CF428, D_801E4EA8[11].vy + D_801CF430, D_801E4EA8[12].vx + D_801CF428, D_801E4EA8[12].vy + D_801CF430, (x_1_4 + D_801CF418), (size + D_801CF420), (x_1_2 + D_801CF418), (size + D_801CF420));
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[12], D_801E4EA8[12].vx + D_801CF428, D_801E4EA8[12].vy + D_801CF430, D_801E4EA8[13].vx + D_801CF428, D_801E4EA8[13].vy + D_801CF430, (x_1_2 + D_801CF418), (size + D_801CF420), (x_3_4 + D_801CF418), (size + D_801CF420));
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[13], D_801E4EA8[13].vx + D_801CF428, D_801E4EA8[13].vy + D_801CF430, D_801E4EA8[14].vx + D_801CF428, D_801E4EA8[14].vy + D_801CF430, (x_3_4 + D_801CF418), (size + D_801CF420), (x_full + D_801CF418), (size + D_801CF420));
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[14], D_801E4EA8[14].vx + D_801CF428, D_801E4EA8[14].vy + D_801CF430, D_801E4EA8[15].vx + D_801CF428, D_801E4EA8[15].vy + D_801CF430, (x_full + D_801CF418), (size + D_801CF420), (x_full + D_801CF418), (y_3_4 + D_801CF420));
        setXY4(&PS1_CurrentDisplay->unk_poly_f4s[15], D_801E4EA8[15].vx + D_801CF428, D_801E4EA8[15].vy + D_801CF430, D_801E4EA8[0].vx + D_801CF428, D_801E4EA8[0].vy + D_801CF430, (x_full + D_801CF418), (y_3_4 + D_801CF420), (x_full + D_801CF418), (y_1_2 + D_801CF420));
        for (i = 0; i < 0x10; i++)
        {
            AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->unk_poly_f4s[i]);
        }
        for (i = 0; i < 0xF; i++)
        {
            next = i + 1;
            (PS1_CurrentDisplay->unk_poly_g4s + i)->x0 = D_801E4E60[i].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g4s[i].y0 = D_801E4E60[i].vy + D_801CF430;
            PS1_CurrentDisplay->unk_poly_g4s[i].x1 = D_801E4E60[next].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g4s[i].y1 = D_801E4E60[next].vy + D_801CF430;
            PS1_CurrentDisplay->unk_poly_g4s[i].x2 = D_801E4EA8[i].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g4s[i].y2 = D_801E4EA8[i].vy + D_801CF430;
            PS1_CurrentDisplay->unk_poly_g4s[i].x3 = D_801E4EA8[next].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g4s[i].y3 = ((D_801E4EA8[next].vy) + D_801CF430);
        }
        PS1_CurrentDisplay->unk_poly_g4s[0xF].x0 = D_801E4E60[15].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].y0 = D_801E4E60[15].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].x1 = D_801E4E60[0].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].y1 = D_801E4E60[0].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].x2 = D_801E4EA8[15].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].y2 = D_801E4EA8[15].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].x3 = D_801E4EA8[0].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g4s[0xF].y3 = D_801E4EA8[0].vy + D_801CF430;

        for (i = 0; i < 0x10; i++)
        {
            AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->unk_poly_g4s[i]);
        }
        PS1_CurrentDisplay->drawing_environment.tpage = GetTPage(1, 2, 0x00000100, 0);
        SetDrawEnv(&PS1_CurrentDisplay->map_drawing_environment_primitives[D_801E4BE0], &PS1_CurrentDisplay->drawing_environment);
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->map_drawing_environment_primitives[D_801E4BE0]);
        D_801E4BE0 = D_801E4BE0 + 1;
        for (i = 0; i < 0xF; i++)
        {
            (PS1_CurrentDisplay->unk_poly_g3s + i)->x0 = D_801CF428;
            PS1_CurrentDisplay->unk_poly_g3s[i].y0 = D_801CF430;
            PS1_CurrentDisplay->unk_poly_g3s[i].x1 = D_801E4E60[i].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g3s[i].y1 = (D_801E4E60[i].vy) + D_801CF430;
            PS1_CurrentDisplay->unk_poly_g3s[i].x2 = D_801E4E60[i + 1].vx + D_801CF428;
            PS1_CurrentDisplay->unk_poly_g3s[i].y2 = ((D_801E4E60[i + 1].vy) + D_801CF430);
        }
        PS1_CurrentDisplay->unk_poly_g3s[0xF].x0 = D_801CF428;
        PS1_CurrentDisplay->unk_poly_g3s[0xF].y0 = D_801CF430;
        PS1_CurrentDisplay->unk_poly_g3s[0xF].x1 = D_801E4E60[15].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g3s[0xF].y1 = D_801E4E60[15].vy + D_801CF430;
        PS1_CurrentDisplay->unk_poly_g3s[0xF].x2 = D_801E4E60[0].vx + D_801CF428;
        PS1_CurrentDisplay->unk_poly_g3s[0xF].y2 = D_801E4E60[0].vy + D_801CF430;

        for (i = 0; i < 0x10; i++)
        {
            AddPrim(&PS1_CurrentDisplay->ordering_table[5], &PS1_CurrentDisplay->unk_poly_g3s[i]);
        }
        PS1_CurrentDisplay->drawing_environment.tpage = GetTPage(1, 2, 0x00000100, 0);
        SetDrawEnv(&PS1_CurrentDisplay->map_drawing_environment_primitives[D_801E4BE0], &PS1_CurrentDisplay->drawing_environment);
        AddPrim(&PS1_CurrentDisplay->ordering_table[5], &PS1_CurrentDisplay->map_drawing_environment_primitives[D_801E4BE0]);
        D_801E4BE0 = D_801E4BE0 + 1;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].w = x_full;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].h = size;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].x0 = D_801CF418;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].y0 = D_801CF420;
        PS1_CurrentDisplay->field_0x66dc_0x673b[4].code |= 2;
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
