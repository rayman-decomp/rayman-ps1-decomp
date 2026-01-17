#include "draw/rollup_trans.h"

#ifdef BSS_DEFS
s16 PS1_RollUpPosition;
SVECTOR D_801F3EC0[82];
SVECTOR D_801F56B8;
VECTOR D_801F57D0;
s16 D_801F84D8;
s16 D_801F98F8;
s16 D_801F9930;
s16 D_801F9938;
s32 D_801F6390;
#endif

/* 8830 8012D030 -O2 -msoft-float */
void FUN_8012d030(DVECTOR tpage_pos, DVECTOR param_2, s16 step_width, s16 step_height, s16 poly_count)
{
    s16 cnt_x; s16 pos_x;
    s16 unk_1;
    s16 unk_x_1;
    s16 cnt_y; s16 pos_y;
    u8 unk_y_1;
    u8 unk_y_2;
    u16 tpage_1 = GetTPage(2, 1, tpage_pos.vx, tpage_pos.vy);
    u16 tpage_2 = GetTPage(2, 1, tpage_pos.vx + 128, tpage_pos.vy);
    s16 steps_x = SCREEN_WIDTH / step_width;
    s16 steps_y = SCREEN_HEIGHT / step_height;
    POLY_FT4 *poly_1 = &PS1_Displays[0].polygons[poly_count];
    POLY_FT4 *poly_2 = &PS1_Displays[1].polygons[poly_count];

    pos_x = 0;
    cnt_x = 0;
    while (cnt_x < steps_x)
    {
        unk_1 = pos_x < 128;
        unk_x_1 = pos_x;
        if (!unk_1)
            unk_x_1 = pos_x - 128;

        cnt_y = 0;
        pos_y = 0;
        while (cnt_y < steps_y)
        {
            poly_1->u0 = unk_x_1;
            poly_1->v0 = pos_y;
            poly_1->u1 = unk_x_1 + step_width;
            poly_1->v1 = pos_y;
            poly_1->u2 = unk_x_1;
            unk_y_1 = pos_y + step_height;
            poly_1->v2 = unk_y_1;
            poly_1->u3 = unk_x_1 + step_width;
            poly_1->v3 = unk_y_1;
            if (unk_1)
                poly_1->tpage = tpage_1;
            else
                poly_1->tpage = tpage_2;

            poly_2->u0 = unk_x_1;
            poly_2->v0 = pos_y;
            poly_2->u1 = unk_x_1 + step_width;
            poly_2->v1 = pos_y;
            poly_2->u2 = unk_x_1;
            unk_y_2 = pos_y + step_height;
            poly_2->v2 = unk_y_2;
            poly_2->u3 = unk_x_1 + step_width;
            poly_2->v3 = unk_y_2;
            if (unk_1)
                poly_2->tpage = tpage_1;
            else
                poly_2->tpage = tpage_2;

            cnt_y++;
            pos_y += step_height;
            poly_1++;
            poly_2++;
        }

        cnt_x++;
        pos_x += step_width;
    }
}

/* 8A7C 8012D27C -O2 -msoft-float */
void FUN_8012d27c(void)
{
    InitGeom();
    SetGeomOffset(160, 120);
    SetGeomScreen(1024);
}

/* 8AB0 8012D2B0 -O2 -msoft-float */
void FUN_8012d2b0(s16 start_pos)
{
    SVECTOR *cur_vec;
    s16 cnt_x; s16 pos_x;
    s16 cnt_y; s16 pos_y;

    PS1_PolygonsCount = 0;
    FUN_8012d27c();
    D_801F9930 = 8;
    D_801F9938 = SCREEN_HEIGHT;
    FUN_8012d030(D_801CEDE4, D_801CEDE8, D_801F9930, D_801F9938 - 1, PS1_PolygonsCount + 2);
    D_801F84D8 = SCREEN_WIDTH / D_801F9930;
    D_801F98F8 = SCREEN_HEIGHT / D_801F9938;

    cur_vec = D_801F3EC0;
    pos_x = 0;
    cnt_x = 0;
    while (cnt_x < D_801F84D8 + 1)
    {
        pos_y = 0;
        cnt_y = 0;
        while (cnt_y < D_801F98F8 + 1)
        {
            cur_vec->vx = pos_x - 160;
            if (pos_y == SCREEN_HEIGHT)
                pos_y = SCREEN_HEIGHT - 1;
            cur_vec->vy = pos_y - 120;
            cur_vec->vz = 0;
            cnt_y++;
            pos_y += D_801F9938;
            cur_vec++;
        }
        cnt_x++;
        pos_x += D_801F9930;
    }
    D_801F56B8.vz = 0; D_801F56B8.vy = 0; D_801F56B8.vx = 0;
    D_801F57D0.vy = 0; D_801F57D0.vx = 0; D_801F57D0.vz = 1024;
    PS1_RollUpPosition = start_pos;
}

/* 8CC0 8012D4C0 -O2 -msoft-float */
void PS1_RollUpTransition(s16 rollup_pos, s16 left_to_right)
{
    MATRIX unk_1;
    s32 unk_2;
    s16 unk_x;
    s16 unk_3;
    s16 unk_4;
    s16 unk_5;
    SVECTOR *cur_vec;
    s16 cnt_x;
    s16 pos_x;
    s16 cnt_y;
    s16 unk_6;
    POLY_FT4 *cur_poly;
    s32 rtp_p;
    s32 rtp_flag;
    s32 avg_z4;

    RotMatrix(&D_801F56B8, &unk_1);
    TransMatrix(&unk_1, &D_801F57D0);
    SetRotMatrix(&unk_1);
    SetTransMatrix(&unk_1);
    rsin(4096 - 1);
    rcos(4096 - 1);

    if (left_to_right == true)
    {
        unk_2 = 395;
        unk_x = SCREEN_WIDTH - (rollup_pos * unk_2 / 100);
    }
    else
    {
        unk_2 = 495;
        unk_x = SCREEN_WIDTH - (rollup_pos * unk_2 / 100);
    }

    unk_3 = 125;
    unk_4 = 20;
    unk_5 = D_801F84D8;
    cur_vec = D_801F3EC0;
    cnt_x = 0;
    pos_x = 0;
    while (cnt_x < (D_801F84D8 + 1))
    {
        cnt_y = 0;
        while (cnt_y < (D_801F98F8 + 1))
        {
            if (left_to_right == true)
            {
                cur_vec->vx = pos_x - 160;
                cur_vec->vz = 0;
            }

            if (pos_x >= unk_x)
            {
                if (pos_x >= unk_x + unk_3)
                {
                    MIN_2(unk_5, cnt_x);
                    break;
                }
                else
                {
                    unk_6 = (pos_x - unk_x) * 651 / unk_4;
                    cur_vec->vx = (unk_x + (unk_4 * rsin(unk_6) >> 12)) - 160;
                    cur_vec->vz = (unk_4 * rcos(unk_6) >> 12) - unk_4;
                }
            }
            cnt_y++;
            cur_vec++;
        }
        cnt_x++;
        pos_x += D_801F9930;
    }

    cur_poly = &PS1_CurrentDisplay->polygons[PS1_PolygonsCount + 2];
    if (left_to_right == true && rollup_pos > 20)
        unk_5--;
    cur_vec = D_801F3EC0;
    cnt_x = 0;
    while (cnt_x < unk_5)
    {
        cnt_y = 0;
        while (cnt_y < D_801F98F8)
        {
#ifdef PLATFORM_PSYZ
            avg_z4 = AverageZ4( 
                RotTransPers(&cur_vec[0], (int*)&cur_poly->x0, &rtp_p, &rtp_flag),
                RotTransPers(&cur_vec[1], (int*)&cur_poly->x2, &rtp_p, &rtp_flag),
                RotTransPers(&cur_vec[D_801F98F8] + 1, (int*)&cur_poly->x1, &rtp_p, &rtp_flag),
                RotTransPers(&cur_vec[D_801F98F8] + 2, (int*)&cur_poly->x3, &rtp_p, &rtp_flag)
            );
#else
            avg_z4 = AverageZ4(
                RotTransPers(&cur_vec[0], (s32 *) &cur_poly->x0, &rtp_p, &rtp_flag),
                RotTransPers(&cur_vec[1], (s32 *) &cur_poly->x2, &rtp_p, &rtp_flag),
                RotTransPers(&cur_vec[D_801F98F8] + 1, (s32 *) &cur_poly->x1, &rtp_p, &rtp_flag),
                RotTransPers(&cur_vec[D_801F98F8] + 2, (s32 *) &cur_poly->x3, &rtp_p, &rtp_flag)
            );
#endif
            AddPrim(&PS1_CurrentDisplay->ordering_table[(16 * 4 + 1) - avg_z4], cur_poly);
            cur_vec++;
            cur_poly++;
            cnt_y++;
        }
        cur_vec++;
        cnt_x++;
    }
}

// PS1_RollUpTransition is broken on PsyZ right now
/* 916C 8012D96C -O2 -msoft-float */
s16 PS1_RollUpRToL(void)
{
    CLRSCR();
    if (PS1_RollUpPosition != 100)
    {
        PS1_RollUpTransition(PS1_RollUpPosition, false);
        PS1_RollUpPosition++;
        return false;
    }
    return true;
}

/* 91C0 8012D9C0 -O2 -msoft-float */
s16 PS1_RollUpLToR(void)
{
    CLRSCR();
    if (PS1_RollUpPosition != 0)
    {
        PS1_RollUpTransition(PS1_RollUpPosition, true);
        PS1_RollUpPosition--;
        return false;
    }
    return true;
}

/* 9214 8012DA14 -O2 -msoft-float */
void FUN_8012da14(void)
{
    DVECTOR tpage_pos[2];

    __builtin_memcpy(&tpage_pos, D_801CEDEC, sizeof(D_801CEDEC));
    FUN_8012d27c();
    PS1_Displays[0].polygons[0].u0 = 0;
    PS1_Displays[0].polygons[0].v0 = 0;
    PS1_Displays[0].polygons[0].u1 = 128;
    PS1_Displays[0].polygons[0].v1 = 0;
    PS1_Displays[0].polygons[0].u2 = 0;
    PS1_Displays[0].polygons[0].v2 = 240 - 1;
    PS1_Displays[0].polygons[0].u3 = 128;
    PS1_Displays[0].polygons[0].v3 = 240 - 1;
    PS1_Displays[1].polygons[0].u0 = 0;
    PS1_Displays[1].polygons[0].v0 = 0;
    PS1_Displays[1].polygons[0].u1 = 128;
    PS1_Displays[1].polygons[0].v1 = 0;
    PS1_Displays[1].polygons[0].u2 = 0;
    PS1_Displays[1].polygons[0].v2 = 240 - 1;
    PS1_Displays[1].polygons[0].u3 = 128;
    PS1_Displays[1].polygons[0].v3 = 240 - 1;
    PS1_Displays[0].polygons[1].u0 = 0;
    PS1_Displays[0].polygons[1].v0 = 0;
    PS1_Displays[0].polygons[1].u1 = 192;
    PS1_Displays[0].polygons[1].v1 = 0;
    PS1_Displays[0].polygons[1].u2 = 0;
    PS1_Displays[0].polygons[1].v2 = 240 - 1;
    PS1_Displays[0].polygons[1].u3 = 192;
    PS1_Displays[0].polygons[1].v3 = 240 - 1;
    PS1_Displays[1].polygons[1].u0 = 0;
    PS1_Displays[1].polygons[1].v0 = 0;
    PS1_Displays[1].polygons[1].u1 = 192;
    PS1_Displays[1].polygons[1].v1 = 0;
    PS1_Displays[1].polygons[1].u2 = 0;
    PS1_Displays[1].polygons[1].v2 = 240 - 1;
    PS1_Displays[1].polygons[1].u3 = 192;
    PS1_Displays[1].polygons[1].v3 = 240 - 1;

    PS1_Displays[0].polygons[0].tpage = GetTPage(2, 1, tpage_pos[0].vx, tpage_pos[0].vy);
    PS1_Displays[0].polygons[1].tpage = GetTPage(2, 1, tpage_pos[0].vx + 128, tpage_pos[0].vy);
    PS1_Displays[1].polygons[0].tpage = GetTPage(2, 1, tpage_pos[0].vx, tpage_pos[0].vy);
    PS1_Displays[1].polygons[1].tpage = GetTPage(2, 1, tpage_pos[0].vx + 128, tpage_pos[0].vy);
    D_801F56B8.vz = 0; D_801F56B8.vy = 0; D_801F56B8.vx = 0;
    D_801F57D0.vy = 0; D_801F57D0.vx = 0; D_801F57D0.vz = 1024;
    D_801F6390 = 0;
    PS1_RollUpPosition = 0;
}
