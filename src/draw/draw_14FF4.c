#include "draw/draw_14FF4.h"

#ifdef BSS_DEFS
Display PS1_Displays[2];
s16 D_801E4BE0;

s16 PS1_PolygonIndexTable[200];
s16 PS1_PolygonsCount;
s16 D_801F4A28;
u16 PS1_Disp_Cur_Tile1;
OT_TYPE *PS1_PrevPrim;
u8 D_801E4C20;
s16 D_801E4DF8;
#endif

/* 14FF4 801397F4 -O2 -msoft-float */
void PS1_DrawColoredSprite(Sprite *sprite, s16 in_x, s16 in_y, u8 disp_mode)
{
    POLY_FT4 *poly;
    s32 offs;
    s16 page_x; s16 page_y;
    s16 width; s16 height;
    s16 page_x_end; s16 page_y_end;
    s16 unk_x_1; s16 unk_y_1;
    s16 unk_x_2; s16 unk_y_2;

    if (PS1_PolygonsCount < 200)
        poly = &PS1_CurrentDisplay->polygons[PS1_PolygonsCount++];
    else
    {
        offs = PS1_PolygonsCount * sizeof(POLY_FT4);
        if (PS1_CurrentDisplay != PS1_Displays)
            poly = (POLY_FT4 *) (FILE_HEAP(0x800E3F2C) + offs);
        else
            poly = (POLY_FT4 *) (FILE_HEAP(0x800D772C) + offs);
        SetPolyFT4(poly);
        PS1_PolygonsCount++;
    }

    if (sprite->id != 0)
    {
        page_x = sprite->page_x;
        page_y = sprite->page_y;
        width = sprite->width;
        height = sprite->height;
        page_x_end = page_x + width;
        page_y_end = page_y + height;
        unk_x_1 = in_x + width;
        unk_y_1 = in_y + height;
        unk_x_2 = in_x + height;
        unk_y_2 = in_y + width;
        poly->clut = sprite->clut;
        poly->tpage = sprite->tpage;
        switch (disp_mode)
        {
        case 1:
            page_x--;
            page_x_end--;
            poly->u0 = page_x_end;
            poly->v0 = page_y;
            poly->u1 = page_x;
            poly->v1 = page_y;
            poly->u2 = page_x_end;
            poly->v2 = page_y_end;
            poly->u3 = page_x;
            poly->v3 = page_y_end;
            poly->x0 = in_x;
            poly->y0 = in_y;
            poly->x1 = unk_x_1;
            poly->y1 = in_y;
            poly->x2 = in_x;
            poly->y2 = unk_y_1;
            poly->x3 = unk_x_1;
            poly->y3 = unk_y_1;
            break;
        case 2:
            page_y--;
            page_y_end--;
            poly->u0 = page_x;
            poly->v0 = page_y_end;
            poly->u1 = page_x_end;
            poly->v1 = page_y_end;
            poly->u2 = page_x;
            poly->v2 = page_y;
            poly->u3 = page_x_end;
            poly->v3 = page_y;
            poly->x0 = in_x;
            poly->y0 = in_y;
            poly->x1 = unk_x_1;
            poly->y1 = in_y;
            poly->x2 = in_x;
            poly->y2 = unk_y_1;
            poly->x3 = unk_x_1;
            poly->y3 = unk_y_1;
            break;
        case 3:
            page_x--;
            page_x_end--;
            page_y--;
            page_y_end--;
            poly->u0 = page_x_end;
            poly->v0 = page_y_end;
            poly->u1 = page_x;
            poly->v1 = page_y_end;
            poly->u2 = page_x_end;
            poly->v2 = page_y;
            poly->u3 = page_x;
            poly->v3 = page_y;
            poly->x0 = in_x;
            poly->y0 = in_y;
            poly->x1 = unk_x_1;
            poly->y1 = in_y;
            poly->x2 = in_x;
            poly->y2 = unk_y_1;
            poly->x3 = unk_x_1;
            poly->y3 = unk_y_1;
            break;
        case 4:
            page_x--;
            page_x_end--;
            poly->u0 = page_x_end;
            poly->v0 = page_y;
            poly->u1 = page_x_end;
            poly->v1 = page_y_end;
            poly->u2 = page_x;
            poly->v2 = page_y;
            poly->u3 = page_x;
            poly->v3 = page_y_end;
            poly->x0 = in_x;
            poly->y0 = in_y;
            poly->x1 = unk_x_2;
            poly->y1 = in_y;
            poly->x2 = in_x;
            poly->y2 = unk_y_2;
            poly->x3 = unk_x_2;
            poly->y3 = unk_y_2;
            break;
        case 5:
            page_y--;
            page_y_end--;
            poly->u0 = page_x;
            poly->v0 = page_y_end;
            poly->u1 = page_x;
            poly->v1 = page_y;
            poly->u2 = page_x_end;
            poly->v2 = page_y_end;
            poly->u3 = page_x_end;
            poly->v3 = page_y;
            poly->x0 = in_x;
            poly->y0 = in_y;
            poly->x1 = unk_x_2;
            poly->y1 = in_y;
            poly->x2 = in_x;
            poly->y2 = unk_y_2;
            poly->x3 = unk_x_2;
            poly->y3 = unk_y_2;
            break;
        case 6:
            poly->u0 = page_x;
            poly->v0 = page_y;
            poly->u1 = page_x;
            poly->v1 = page_y_end;
            poly->u2 = page_x_end;
            poly->v2 = page_y;
            poly->u3 = page_x_end;
            poly->v3 = page_y_end;
            poly->x0 = in_x;
            poly->y0 = in_y;
            poly->x1 = unk_x_2;
            poly->y1 = in_y;
            poly->x2 = in_x;
            poly->y2 = unk_y_2;
            poly->x3 = unk_x_2;
            poly->y3 = unk_y_2;
            break;
        case 7:
            page_x--;
            page_x_end--;
            page_y--;
            page_y_end--;
            poly->u0 = page_x_end;
            poly->v0 = page_y_end;
            poly->u1 = page_x_end;
            poly->v1 = page_y;
            poly->u2 = page_x;
            poly->v2 = page_y_end;
            poly->u3 = page_x;
            poly->v3 = page_y;
            poly->x0 = in_x;
            poly->y0 = in_y;
            poly->x1 = unk_x_2;
            poly->y1 = in_y;
            poly->x2 = in_x;
            poly->y2 = unk_y_2;
            poly->x3 = unk_x_2;
            poly->y3 = unk_y_2;
            break;
        case 0:
        default:
            poly->u0 = page_x;
            poly->v0 = page_y;
            poly->u1 = page_x_end;
            poly->v1 = page_y;
            poly->u2 = page_x;
            poly->v2 = page_y_end;
            poly->u3 = page_x_end;
            poly->v3 = page_y_end;
            poly->x0 = in_x;
            poly->y0 = in_y;
            poly->x1 = unk_x_1;
            poly->y1 = in_y;
            poly->x2 = in_x;
            poly->y2 = unk_y_1;
            poly->x3 = unk_x_1;
            poly->y3 = unk_y_1;
            break;
        }
        SetShadeTex(poly, true);
        if (PS1_DrawSpriteSemiTrans)
            SetSemiTrans(poly, true);
        else
            SetSemiTrans(poly, false);
        AddPrim(PS1_PrevPrim, poly);
        PS1_PrevPrim = (OT_TYPE*)poly;
    }
}

/* 15340 80139B40 -O2 -msoft-float */
void PS1_DrawSprite(Sprite *sprite, s16 x, s16 y, u8 param_4)
{
    PS1_DrawColoredSprite(sprite, x, y, param_4);
}

/* 15370 80139B70 -O2 -msoft-float */
void PS1_DrawScaledSprite(Sprite *sprite, s16 x, s16 y, u8 is_flipped, s16 param_5)
{
    s16 page_x; s16 page_y;
    s16 width; s16 height;
    s32 unk_width_1; s32 unk_height_1;
    s16 unk_x_1;
    s16 unk_x_2;
    s16 unk_y_1;
    s16 unk_x_3;
    s16 unk_y_2;
    POLY_FT4 *poly = &PS1_CurrentDisplay->polygons[PS1_PolygonsCount++];

    if (sprite->id != 0)
    {
        page_x = sprite->page_x;
        page_y = sprite->page_y;
        if (param_5 > 0)
        {
            width = sprite->width;
            height = sprite->height + 1;
        }
        else
        {
            width = sprite->width - 1;
            height = sprite->height - 1;
        }
        unk_width_1 = get_proj_dist(param_5, width);
        unk_height_1 = get_proj_dist(param_5, height);
        unk_x_1 = page_x + width;
        unk_x_2 = unk_x_1 - 1;
        unk_y_1 = page_y + height - 1;
        unk_x_3 = x + unk_width_1 - 1;
        unk_y_2 = y + unk_height_1 - 1;
        poly->clut = sprite->clut;
        poly->tpage = sprite->tpage;
        if (is_flipped)
        {
            page_x--;
            poly->u0 = unk_x_2;
            poly->v0 = page_y;
            poly->u1 = page_x;
            poly->v1 = page_y;
            poly->u2 = unk_x_2;
            poly->v2 = unk_y_1;
            poly->u3 = page_x;
            poly->v3 = unk_y_1;
        }
        else
        {
            unk_x_2 = unk_x_1;
            poly->u0 = page_x;
            poly->v0 = page_y;
            poly->u1 = unk_x_2;
            poly->v1 = page_y;
            poly->u2 = page_x;
            poly->v2 = unk_y_1;
            poly->u3 = unk_x_2;
            poly->v3 = unk_y_1;
        }
        unk_x_3++;
        poly->x0 = x;
        poly->y0 = y;
        poly->x1 = unk_x_3;
        poly->y1 = y;
        poly->x2 = x;
        poly->y2 = unk_y_2;
        poly->x3 = unk_x_3;
        poly->y3 = unk_y_2;
        SetShadeTex(poly, true);
        SetSemiTrans(poly, false);
        AddPrim(PS1_PrevPrim, poly);
        PS1_PrevPrim = (OT_TYPE*)poly;
    }
}

/* 1555C 80139D5C -O2 -msoft-float */
void FUN_80139d5c(s16 *p_poly_x, s16 *p_poly_y, s16 param_3, s16 param_4, s16 angle)
{
    s16 old_poly_x = *p_poly_x;
    s16 old_poly_y = *p_poly_y;

    *p_poly_x =
        (old_poly_x * rcos(angle) >> 12) -
        (old_poly_y * rsin(angle) >> 12) +
        (
            (param_3 - (param_3 * rcos(angle) >> 12)) +
            (param_4 * rsin(angle) >> 12)
        );
    *p_poly_y =
        (old_poly_x * rsin(angle) >> 12) +
        (old_poly_y * rcos(angle) >> 12) +
        (
            (param_4 - (param_4 * rcos(angle) >> 12)) -
            (param_3 * rsin(angle) >> 12)
        );
}

/* 15704 80139F04 -O2 -msoft-float */
void PS1_DrawRay(Sprite *sprite, s16 x, s16 y, u8 is_flipped, s16 angle_ind)
{
    s16 unk_x_2;
    s16 unk_y_2;
    s16 page_x; s16 page_y;
    s16 width; s16 height;
    s16 unk_height_1;
    s16 unk_x_1;
    s16 unk_y_1;
    u8 i;
    s32 unk_1;
    s32 unk_2;
    s16 unk_3;
    s16 unk0[16]; s16 unk20[16]; s16 unk40[16]; s16 unk60[16];
    s16 unk80[16]; s16 unkA0[16]; s16 unkC0[16]; s16 unkE0[16];
    POLY_FT4 *poly = &PS1_CurrentDisplay->polygons[PS1_PolygonsCount++];

    if (sprite->id != 0)
    {
        page_x = sprite->page_x;
        page_y = sprite->page_y;
        height = sprite->height;
        width = sprite->width;

        unk_height_1 = height + 1;
        if (D_801E4C20)
            unk_height_1 = height;

        unk_x_1 = page_x + width - 1;
        unk_y_1 = page_y + unk_height_1 - 1;
        unk_x_2 = x + width - 1;
        unk_y_2 = y + unk_height_1 - 1;
        poly->clut = sprite->clut;
        poly->tpage = sprite->tpage;
        if (D_801E4C20 == true && D_801CEF78 == -1)
        {
            D_801E4C20 = true;
            for (i = 0; i < LEN(D_801CF600); i++)
            {
                /* TODO: ??? */
                unk_1 = rand() * 2;
                unk_2 = unk_1;
                D_801CF600[i] = unk_2 - (unk_1 / 4096 * 4096);
            }
            D_801CEF78 = 150;
        }

        if (D_801E4C20)
        {
            unk_1 = D_801CF600[angle_ind] + 81;
            D_801CF600[angle_ind] = unk_1 - (unk_1 / 4096 * 4096);
            if (angle_ind == 0)
                D_801CEF78 -= 3;

            unk80[angle_ind] = x + (width >> 1);
            unkA0[angle_ind] = y + (unk_height_1 >> 1);
            unkC0[angle_ind] =
                unk80[angle_ind] +
                (D_801CEF78 / 2 * rcos(D_801CF600[angle_ind]) >> 12);
            unkE0[angle_ind] =
                unkA0[angle_ind] +
                (D_801CEF78 / 2 * rsin(D_801CF600[angle_ind]) >> 12);

            unk_3 = (D_801CEF78 * 4096 / 75) * 2;
            unk0[angle_ind] = unkC0[angle_ind] - (width >> 1);
            unk20[angle_ind] = unkE0[angle_ind] - (unk_height_1 >> 1);
            unk40[angle_ind] = width + unk0[angle_ind] - 1;
            unk60[angle_ind] = unk_height_1 + unk20[angle_ind] - 1;
            poly->x0 = unk0[angle_ind];
            poly->y0 = unk20[angle_ind];
            poly->x1 = unk40[angle_ind];
            poly->y1 = unk20[angle_ind];
            poly->x2 = unk0[angle_ind];
            poly->y2 = unk60[angle_ind];
            poly->x3 = unk40[angle_ind];
            poly->y3 = unk60[angle_ind];

            FUN_80139d5c(&poly->x0, &poly->y0, unkC0[angle_ind], unkE0[angle_ind], unk_3);
            FUN_80139d5c(&poly->x1, &poly->y1, unkC0[angle_ind], unkE0[angle_ind], unk_3);
            FUN_80139d5c(&poly->x2, &poly->y2, unkC0[angle_ind], unkE0[angle_ind], unk_3);
            FUN_80139d5c(&poly->x3, &poly->y3, unkC0[angle_ind], unkE0[angle_ind], unk_3);
        }

        if (is_flipped)
        {
            if (!D_801E4C20)
                page_x--;
            poly->u0 = unk_x_1;
            poly->v0 = page_y;
            poly->u1 = page_x;
            poly->v1 = page_y;
            poly->u2 = unk_x_1;
            poly->v2 = unk_y_1;
            poly->u3 = page_x;
            poly->v3 = unk_y_1;
        }
        else
        {
            if (!D_801E4C20)
                unk_x_1++;
            poly->u0 = page_x;
            poly->v0 = page_y;
            poly->u1 = unk_x_1;
            poly->v1 = page_y;
            poly->u2 = page_x;
            poly->v2 = unk_y_1;
            poly->u3 = unk_x_1;
            poly->v3 = unk_y_1;
        }

        if (D_801E4C20)
        {
            if (D_801CEF78 <= 0)
            {
                D_801E4C20 = false;
                D_801CEF78 = -1;
            }
        }
        else
        {
            unk_x_2++;
            poly->x0 = x;
            poly->y0 = y;
            poly->x1 = unk_x_2;
            poly->y1 = y;
            poly->x2 = x;
            poly->y2 = unk_y_2;
            poly->x3 = unk_x_2;
            poly->y3 = unk_y_2;
        }

        SetShadeTex(poly, true);
        SetSemiTrans(poly, false);
        AddPrim(PS1_PrevPrim, poly);
        PS1_PrevPrim = (OT_TYPE*)poly;
    }
}

/* 15C54 8013A454 -O2 -msoft-float */
void display_sprite(Obj *param_1, u8 sprite, s16 x, s16 y, u8 param_5)
{
    PS1_DrawSprite(&param_1->sprites[sprite], x, y, param_5);
}

/* 15C9C 8013A49C -O2 -msoft-float */
void display2(Obj *obj)
{
    u8 flip_x;
    s16 i;
    u8 sprite_ind;
    Sprite *sprite;
    s16 x_pos; s16 y_pos;
    s16 unk_1;
    s16 scale = obj->scale;
    Animation *anim = &obj->animations[obj->anim_index];
    s32 layers_count = anim->layers_count & 0x3FFF;
    AnimationLayer *layer = &anim->layers[layers_count * obj->anim_frame];

    if ((u16) (obj->screen_x_pos + SCREEN_WIDTH) <= (SCREEN_WIDTH * 2) && (u16) (obj->screen_y_pos + SCREEN_HEIGHT) <= (SCREEN_HEIGHT * 2))
    {
        flip_x = (obj->flags >> OBJ_FLIP_X) & 1;
        for (i = 0; i < (anim->layers_count & 0x3FFF); i++)
        {
            sprite_ind = layer[i].sprite;
            if (sprite_ind != 0)
            {
                sprite = &obj->sprites[sprite_ind];
                if (!flip_x)
                    x_pos = obj->screen_x_pos + layer[i].x_pos;
                else
                {
                    unk_1 = 0;
                    if (obj->scale == 0x100 && i == 5)
                        unk_1 = -(obj->anim_index - 14 <= 2U) & 0xFFF0;
                    x_pos = unk_1 + (obj->screen_x_pos + obj->offset_bx * 2 - layer[i].x_pos - sprite->width);
                }
                y_pos = layer[i].y_pos + obj->screen_y_pos;
                if (obj == &ray)
                    PS1_DrawRay(
                        sprite,
                        (s16) get_proj_x(ray.scale, x_pos), (s16) get_proj_y(ray.scale, y_pos),
                        flip_x ^ layer[i].flip_x,
                        i
                    );
                else
                {
                    if (scale == 0)
                        PS1_DrawSprite(
                            sprite,
                            x_pos, y_pos,
                            flip_x ^ layer[i].flip_x
                        );
                    else
                        PS1_DrawScaledSprite(
                            sprite,
                            (s16) get_proj_x(scale, x_pos), (s16) get_proj_y(scale, y_pos),
                            flip_x ^ layer[i].flip_x,
                            scale
                        );
                }
            }
        }
        PS1_DrawSpriteSemiTrans = false;
    }
}

/* 15F70 8013A770 -O2 -msoft-float */
void DISPLAY_POING(void)
{
    if (poing.is_active)
        display2(&level.objects[poing_obj_id]);
}

/* 15FB8 8013A7B8 -O2 -msoft-float */
void DISPLAY_CLING(void)
{
    Obj *c_1up;
    Obj *c_pow;

    if (id_Cling_1up != -1)
    {
        c_1up = &level.objects[id_Cling_1up];
        c_1up->screen_x_pos = 53 - c_1up->offset_bx;
        c_1up->screen_y_pos = 10 - c_1up->offset_hy;
        if (c_1up->timer == 0)
            display2(c_1up);
    }
    if (id_Cling_Pow != -1)
    {
        c_pow = &level.objects[id_Cling_Pow];
        c_pow->screen_x_pos = 58 - c_pow->offset_bx;
        c_pow->screen_y_pos = 19 - c_pow->offset_hy;
        if (c_pow->timer == 0)
            display2(c_pow);
    }
}

/* 16080 8013A880 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/draw/draw_14FF4", display_bar_boss);
#else
/*
gross
tried going back to a goto version (set display_sprite param_2 in each case then goto actual call), didn't work
*/
void display_bar_boss(Obj *boss_obj)
{
    u8 hp;
    Obj *poing_obj;
    u8 init_hp;
    s32 unk_1;
    s32 unk_2;
    s32 unk_3;
    s32 disp_mode;

    if (scrollLocked)
    {
        hp = boss_obj->hit_points;
        if (hp != 0)
        {
            poing_obj = &level.objects[poing_obj_id];
            init_hp = boss_obj->init_hit_points;
            unk_1 = 6;
            unk_2 = (29 - init_hp) * unk_1;
            unk_3 = 20 - unk_2;
            disp_mode = 1;
            display_sprite(poing_obj, 61, unk_3 - (init_hp - hp) * unk_1, 217, disp_mode);
            display_sprite(poing_obj, 60, 20 - unk_2 + 1, 216, disp_mode);
            switch (boss_obj->type)
            {
            case TYPE_MOSKITO:
                display_sprite(poing_obj, 62, 0, 206, disp_mode);
                break;
            case TYPE_MOSKITO2:
                display_sprite(poing_obj, 62, 0, 206, disp_mode);
                break;
            case TYPE_BB1:
                display_sprite(poing_obj, 106, 0, 206, disp_mode);
                break;
            case TYPE_BB12:
                display_sprite(poing_obj, 106, 0, 206, disp_mode);
                break;
            case TYPE_SPACE_MAMA:
                display_sprite(poing_obj, 108, 0, 206, disp_mode);
                break;
            case TYPE_SPACE_MAMA2:
                display_sprite(poing_obj, 108, 0, 206, disp_mode);
                break;
            case TYPE_MAMA_PIRATE:
                display_sprite(poing_obj, 111, 0, 206, disp_mode);
                break;
            case TYPE_SCORPION:
                display_sprite(poing_obj, 107, 0, 206, disp_mode);
                break;
            case TYPE_HYB_BBF2_D:
                display_sprite(poing_obj, 110, 0, 206, disp_mode);
                break;
            case TYPE_HYBRIDE_STOSKO:
                display_sprite(poing_obj, 110, 0, 206, disp_mode);
                break;
            case TYPE_HYBRIDE_MOSAMS:
                display_sprite(poing_obj, 110, 0, 206, disp_mode);
                break;
            case TYPE_DARK:
                display_sprite(poing_obj, 110, 0, 206, disp_mode);
                break;
            case TYPE_SAXO:
            case TYPE_SAXO2:
                display_sprite(poing_obj, 109, 0, 206, disp_mode);
                break;
            }
        }
    }
}
#endif

/* 16314 8013AB14 -O2 -msoft-float */
void DISPLAY_FIXE(s16 left_time)
{
    Obj *div_obj;

    PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[10];
    div_obj = &level.objects[sbar_obj_id];
    if (left_time == -2)
    {
        display_sprite(div_obj, 27, 8, 10, 0);
        display_sprite(div_obj, 56, 252, 10, 0);
        display_sprite(div_obj, status_bar.lives_digits[0] + 28, 47, 10, 0);
        display_sprite(div_obj, status_bar.lives_digits[1] + 28, 62, 10, 0);
        if (ray.hit_points != 0xff && !fin_du_jeu)
        {
            display_sprite(div_obj, status_bar.hp_sprites[1] + 17, 27, 32, 0);
            if (status_bar.max_hp == 4)
                display_sprite(div_obj, status_bar.hp_sprites[0] + 20, 51, 32, 0);
        }
        display_sprite(div_obj, status_bar.wiz_digits[0] + 28, 284, 10, 0);
        display_sprite(div_obj, status_bar.wiz_digits[1] + 28, 298, 10, 0);
    }
    else
    {
        if (D_801CF018 == -1)
        {
            display_sprite(div_obj, 56, 14, 202, 0);
            display_sprite(div_obj, status_bar.wiz_digits[0] + 28, 46, 202, 0);
            display_sprite(div_obj, status_bar.wiz_digits[1] + 28, 60, 202, 0);
        }
    }

    if (id_Cling_1up != -1 || id_Cling_Pow != -1)
        DISPLAY_CLING();
    DO_DARK2_AFFICHE_TEXT();
    if (PS1_BossObj)
        display_bar_boss(PS1_BossObj);
}

/* 16554 8013AD54 -O2 -msoft-float */
void FUN_8013ad54(s16 param_1, s16 param_2, s16 param_3)
{
    Obj *sbar_obj = &level.objects[sbar_obj_id];
    u8 spr_3 = (param_1 % 10);
    u8 spr_2 = (param_1 / 10) % 10;
    u8 spr_1 = (param_1 / 100);
    s32 spr_add = 28; /* TODO: did not get this in DISPLAY_FIXE, so define instead? */
    s32 display_mode = 0;

    display_sprite(sbar_obj, spr_1 + spr_add, param_2, param_3, display_mode);
    display_sprite(sbar_obj, spr_2 + spr_add, param_2 + 16, param_3, display_mode);
    display_sprite(sbar_obj, spr_3 + spr_add, param_2 + 32, param_3, display_mode);
}

/* 166AC 8013AEAC -O2 -msoft-float */
void DrawWldPointPlan2Normal(s16 x0, s16 y0)
{
    SPRT_8 *p = &PS1_CurrentDisplay->field_0x1e9c_0x321b[(u16) D_801F4A28++];

    p->x0 = x0; p->y0 = y0;
    p->u0 = 64; p->v0 = 0;
    AddPrim(&PS1_CurrentDisplay->ordering_table[5], p);
}

/* 16714 8013AF14 -O2 -msoft-float */
void PS1_DisplayPtsPrim(void)
{
    AddPrim(&PS1_CurrentDisplay->ordering_table[5], &PS1_CurrentDisplay->map_drawing_environment_primitives[6]);
}

/* 16740 8013AF40 -O2 -msoft-float */
void DISPLAY_POINT(s32 x0, s32 y0)
{
    if (((u16) (x0 - 43) <= 240) && ((u16) (y0 - 54) <= 134))
        DrawWldPointPlan2Normal((s16) x0, (s16) y0 - 2);
}

/* 16790 8013AF90 -O2 -msoft-float */
void DISPLAY_PTS_TO_PLAN2(s32 x1, s32 y1, s32 x2, s32 y2, s16 percentage)
{
    s16 x_offs = 52;
    s16 y_offs = 55;
    s16 new_x1 = x1 + x_offs - xmap;
    s16 new_x2 = x2 + x_offs - xmap;
    s16 new_y1 = y1 + y_offs - ymap;
    s16 new_y2 = y2 + y_offs - ymap;

    Bresenham(
        DISPLAY_POINT,
        new_x1, new_y1,
        new_x2, new_y2,
        7,
        percentage
    );
}

/* 16820 8013B020 -O2 -msoft-float */
void DISPLAY_PLATEAU(Obj *obj)
{
    display2(obj);
}

/* 16840 8013B040 -O2 -msoft-float */
void draw_flocon1_Normal(s16 x0, s16 y0)
{
    TILE_1 *tile = &PS1_CurrentDisplay->tile1s[PS1_Disp_Cur_Tile1++];

    tile->r0 = 187; tile->g0 = 187; tile->b0 = 251;
    tile->x0 = x0; tile->y0 = y0;
    AddPrim(PS1_PrevPrim, tile);
    PS1_PrevPrim = (OT_TYPE*)tile;
}

/* 168C0 8013B0C0 -O2 -msoft-float */
void draw_flocon2_Normal(s16 x0, s16 y0)
{
    TILE_1 *tile = &PS1_CurrentDisplay->tile1s[PS1_Disp_Cur_Tile1++];

    tile->r0 = 199; tile->g0 = 223; tile->b0 = 247;
    tile->x0 = x0; tile->y0 = y0;
    AddPrim(PS1_PrevPrim, tile);
    PS1_PrevPrim = (OT_TYPE*)tile;
}

/* 16944 8013B144 -O2 -msoft-float */
void draw_flocon3_Normal(s16 x0, s16 y0)
{
    SPRT_8 *sprt = &PS1_CurrentDisplay->field_0x1e9c_0x321b[(u16) D_801F4A28++];

    sprt->u0 = 8; sprt->v0 = 0;
    sprt->x0 = x0; sprt->y0 = y0;
    AddPrim(PS1_PrevPrim, sprt);
    PS1_PrevPrim = (OT_TYPE*)sprt;
}

/* 169B4 8013B1B4 -O2 -msoft-float */
void draw_flocon4_Normal(s16 x0, s16 y0)
{
    SPRT_8 *sprt = &PS1_CurrentDisplay->field_0x1e9c_0x321b[(u16) D_801F4A28++];

    sprt->u0 = 16; sprt->v0 = 0;
    sprt->x0 = x0; sprt->y0 = y0;
    AddPrim(PS1_PrevPrim, sprt);
    PS1_PrevPrim = (OT_TYPE*)sprt;
}

/* 16A24 8013B224 -O2 -msoft-float */
void draw_flocon5_Normal(s16 x0, s16 y0)
{
    SPRT_8 *sprt = &PS1_CurrentDisplay->field_0x1e9c_0x321b[(u16) D_801F4A28++];

    sprt->u0 = 40; sprt->v0 = 0;
    sprt->x0 = x0; sprt->y0 = y0;
    AddPrim(PS1_PrevPrim, sprt);
    PS1_PrevPrim = (OT_TYPE*)sprt;
}

/* 16A94 8013B294 -O2 -msoft-float */
void FUN_8013b294(s16 x0, s16 y0)
{
    SPRT_8 *sprt = &PS1_CurrentDisplay->field_0x1e9c_0x321b[(u16) D_801F4A28++];

    sprt->u0 = 48; sprt->v0 = 0;
    sprt->x0 = x0; sprt->y0 = y0;
    AddPrim(PS1_PrevPrim, sprt);
    PS1_PrevPrim = (OT_TYPE*)sprt;
}

/* 16B04 8013B304 -O2 -msoft-float */
void FUN_8013b304(s16 x0, s16 y0)
{
    SPRT_8 *sprt = &PS1_CurrentDisplay->field_0x1e9c_0x321b[(u16) D_801F4A28++];

    sprt->u0 = 56; sprt->v0 = 0;
    sprt->x0 = x0; sprt->y0 = y0;
    AddPrim(PS1_PrevPrim, sprt);
    PS1_PrevPrim = (OT_TYPE*)sprt;
}

/* 16B74 8013B374 -O2 -msoft-float */
void draw_pluie4_Normal(s16 x0, s16 y0)
{
    TILE_1 *tile = &PS1_CurrentDisplay->tile1s[PS1_Disp_Cur_Tile1++];

    tile->r0 = 95; tile->g0 = 107; tile->b0 = 167;
    tile->x0 = x0; tile->y0 = y0;
    AddPrim(PS1_PrevPrim, tile);
    PS1_PrevPrim = (OT_TYPE*)tile;
}

/* 16BF8 8013B3F8 -O2 -msoft-float */
void draw_pluie5_Normal(s16 x0, s16 y0)
{
    SPRT_8 *sprt = &PS1_CurrentDisplay->field_0x1e9c_0x321b[(u16) D_801F4A28++];

    sprt->u0 = 0; sprt->v0 = 0;
    sprt->x0 = x0; sprt->y0 = y0;
    AddPrim(PS1_PrevPrim, sprt);
    PS1_PrevPrim = (OT_TYPE*)sprt;
}

/* 16C64 8013B464 -O2 -msoft-float */
void draw_pluie6_Normal(s16 x0, s16 y0)
{
    SPRT_8 *sprt = &PS1_CurrentDisplay->field_0x1e9c_0x321b[(u16) D_801F4A28++];

    sprt->u0 = 24; sprt->v0 = 0;
    sprt->x0 = x0; sprt->y0 = y0;
    AddPrim(PS1_PrevPrim, sprt);
    PS1_PrevPrim = (OT_TYPE*)sprt;
}

/* 16CD4 8013B4D4 -O2 -msoft-float */
void FUN_8013b4d4(s16 x0, s16 y0)
{
    SPRT_8 *sprt = &PS1_CurrentDisplay->field_0x1e9c_0x321b[(u16) D_801F4A28++];

    sprt->u0 = 32; sprt->v0 = 0;
    sprt->x0 = x0; sprt->y0 = y0;
    AddPrim(PS1_PrevPrim, sprt);
    PS1_PrevPrim = (OT_TYPE*)sprt;
}

/* 16D44 8013B544 -O2 -msoft-float */
void display_flocons_behind(void)
{
    OT_TYPE *ot_1;
    DR_ENV *dr_env;
    s16 prev_pcx; s16 prev_pcy;
    s16 cnt_1; s16 cnt_2; s16 cnt_3;
    s16 unk_mul;
    s16 unk_x; s16 unk_y;
    s16 ind;
    FloconTableEntry *entry;
    s16 max_ind;
    s16 j;

    ot_1 = &PS1_CurrentDisplay->ordering_table[1];
    PS1_PrevPrim = ot_1;
    dr_env = &PS1_CurrentDisplay->map_drawing_environment_primitives[7];
    AddPrim(ot_1, dr_env);
    PS1_PrevPrim = (OT_TYPE*)dr_env;

    prev_pcx = PROJ_CENTER_X;
    prev_pcy = PROJ_CENTER_Y;
    set_proj_center(160, 170);

    cnt_1 = 6;
    cnt_2 = 3;
    cnt_3 = 32;
    while (cnt_3 < 192) /* range of 32 - 160 (incl.) in steps of 32 */
    {
        cnt_1--;
        unk_mul = 0x10000 / (cnt_3 + 256);
        unk_x = PROJ_CENTER_X - (unk_mul * PROJ_CENTER_X / 256);
        unk_y = PROJ_CENTER_Y - (unk_mul * PROJ_CENTER_Y / 256);

        ind = floc_ind[cnt_2];
        entry = &flocon_tab[ind];
        max_ind = ind + nb_floc[cnt_2];
        if (num_world != 1)
        {
            if (cnt_1 == 5)
            {
                for (j = ind; j < max_ind; j++)
                {
                    /* TODO: could see us var-ing/macro-ing the params at least?*/
                    draw_flocon5_Normal(
                        (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                        (unk_mul * entry->field1_0x2 >> 8) + unk_y
                    );
                    entry++;
                }
            }
            else if (cnt_1 == 4)
            {
                for (j = ind; j < max_ind; j++)
                {
                    draw_flocon4_Normal(
                        (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                        (unk_mul * entry->field1_0x2 >> 8) + unk_y
                    );
                    entry++;
                }
            }
            else if (cnt_1 == 3)
            {
                for (j = ind; j < max_ind; j++)
                {
                    draw_flocon3_Normal(
                        (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                        (unk_mul * entry->field1_0x2 >> 8) + unk_y
                    );
                    entry++;
                }
            }
            else if (cnt_1 == 2)
            {
                for (j = ind; j < max_ind; j++)
                {
                    draw_flocon2_Normal(
                        (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                        (unk_mul * entry->field1_0x2 >> 8) + unk_y
                    );
                    entry++;
                }
            }
            else
            {
                for (j = ind; j < max_ind; j++)
                {
                    draw_flocon1_Normal(
                        (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                        (unk_mul * entry->field1_0x2 >> 8) + unk_y
                    );
                    entry++;
                }
            }
        }
        else
        {
            if (cnt_1 == 5)
            {
                for (j = ind; j < max_ind; j++)
                {
                    draw_pluie6_Normal(
                        (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                        (unk_mul * entry->field1_0x2 >> 8) + unk_y
                    );
                    entry++;
                }
            }
            else if (cnt_1 >= 3)
            {
                for (j = ind; j < max_ind; j++)
                {
                    draw_pluie5_Normal(
                        (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                        (unk_mul * entry->field1_0x2 >> 8) + unk_y
                    );
                    entry++;
                }
            }
            else
            {
                for (j = ind; j < max_ind; j++)
                {
                    draw_pluie4_Normal(
                        (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                        (unk_mul * entry->field1_0x2 >> 8) + unk_y
                    );
                    entry++;
                }
            }
        }
        cnt_2++;
        cnt_3 += 32;
    }

    PROJ_CENTER_X = prev_pcx;
    PROJ_CENTER_Y = prev_pcy;
}

/* 173D0 8013BBD0 -O2 -msoft-float */
void display_flocons_before(void)
{
    OT_TYPE *ot_7;
    DR_ENV *dr_env;
    s16 prev_pcx; s16 prev_pcy;
    s16 cnt_1; s16 cnt_2;
    s16 ind;
    FloconTableEntry *entry;
    s16 max_ind;
    s16 unk_x; s16 unk_y;
    s16 unk_mul;
    s16 j;

    ot_7 = &PS1_CurrentDisplay->ordering_table[7];
    PS1_PrevPrim = ot_7;
    dr_env = &PS1_CurrentDisplay->map_drawing_environment_primitives[6];
    AddPrim(ot_7, dr_env);
    PS1_PrevPrim = (OT_TYPE*)dr_env;

    prev_pcx = PROJ_CENTER_X;
    prev_pcy = PROJ_CENTER_Y;
    set_proj_center(160, 170);

    cnt_1 = 0;
    cnt_2 = -64;
    while (cnt_2 < 32)
    {
        ind = floc_ind[cnt_1];
        entry = &flocon_tab[ind];
        unk_mul = 0x10000 / (cnt_2 + 256);
        unk_x = PROJ_CENTER_X - (unk_mul * PROJ_CENTER_X / 256);
        unk_y = PROJ_CENTER_Y - (unk_mul * PROJ_CENTER_Y / 256);
        max_ind = ind + nb_floc[cnt_1];
        if (num_world != 1)
        {
            if (cnt_1 == 0)
            {
                for (j = ind; j < max_ind; j++)
                {
                    FUN_8013b304(
                        (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                        (unk_mul * entry->field1_0x2 >> 8) + unk_y
                    );
                    entry++;
                }
            }
            else
            {
                for (j = ind; j < max_ind; j++)
                {
                    FUN_8013b294(
                        (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                        (unk_mul * entry->field1_0x2 >> 8) + unk_y
                    );
                    entry++;
                }
            }
        }
        else
        {
            for (j = ind; j < max_ind; j++)
            {
                FUN_8013b4d4(
                    (unk_mul * entry->field0_0x0 >> 8) + unk_x,
                    (unk_mul * entry->field1_0x2 >> 8) + unk_y
                );
                entry++;
            }
        }
        cnt_1++;
        cnt_2 += 32;
    }

    PROJ_CENTER_X = prev_pcx;
    PROJ_CENTER_Y = prev_pcy;
}

/* 17740 8013BF40 -O2 -msoft-float */
void display_pix_gerbes(void)
{
    s16 i;
    PixGerbeItem *cur_item;
    s16 j;
    u8 unk_1;
    s16 spd_y;
    u8 color;
    TILE_1 *cur_tile1 = &PS1_CurrentDisplay->tile1s[PS1_Disp_Cur_Tile1];

    for (i = 0; i < (s16) LEN(pix_gerbe); i++)
    {
        if (pix_gerbe[i].is_active)
        {
            cur_item = &pix_gerbe[i].items[0];
            j = 0;
            while (j < (s16) LEN(pix_gerbe[i].items))
            {
                unk_1 = cur_item->unk_1;
                if (unk_1 > 127 && cur_item->y_pos > 0)
                {
                    spd_y = (u8) cur_item->speed_y; /* using abs on android? */
                    if (spd_y > 127)
                        color = 88;
                    else
                        color = (unk_1 & 127) + ((spd_y >> 5) + 4);

                    switch (color)
                    {
                    case 4:
                        cur_tile1->r0 = 123;
                        cur_tile1->g0 = 135;
                        cur_tile1->b0 = 187;
                        break;
                    case 5:
                        cur_tile1->r0 = 151;
                        cur_tile1->g0 = 159;
                        cur_tile1->b0 = 219;
                        break;
                    case 6:
                        cur_tile1->r0 = 187;
                        cur_tile1->g0 = 187;
                        cur_tile1->b0 = 251;
                        break;
                    case 7:
                        cur_tile1->r0 = 199;
                        cur_tile1->g0 = 213;
                        cur_tile1->b0 = 251;
                        break;
                    case 88:
                        cur_tile1->r0 = 255;
                        cur_tile1->g0 = 191;
                        cur_tile1->b0 = 167;
                        break;
                    default:
                        cur_tile1->r0 = 187;
                        cur_tile1->g0 = 187;
                        cur_tile1->b0 = 251;
                        break;
                    }
                    cur_tile1->x0 = cur_item->x_pos >> 6;
                    cur_tile1->y0 = cur_item->y_pos >> 6;
                    if (PS1_Disp_Cur_Tile1 < LEN(PS1_CurrentDisplay->tile1s))
                    {
                        AddPrim(PS1_PrevPrim, cur_tile1);
                        PS1_Disp_Cur_Tile1++;
                        cur_tile1++;
                    }
                }
                cur_item++;
                j++;
            }
        }
    }
}

/* 179B4 8013C1B4 -O2 -msoft-float */
void DISPLAY_CYMBALE(Obj *obj, u8 param_2)
{
    u16 begin; u16 end; u16 i;
    Sprite *sprite;
    s16 x; s16 y;
    Animation *anim = &obj->animations[obj->anim_index];
    AnimationLayer *layer = &anim->layers[(anim->layers_count & 0x3FFF) * obj->anim_frame];

    if (!param_2)
    {
        end = 5;
        begin = 3;
    }
    else
    {
        end = 2;
        begin = 0;
    }

    for (i = begin; i <= end; i++)
    {
        sprite = &obj->sprites[layer[i].sprite];

        y = layer[i].y_pos + obj->screen_y_pos;
        if (sprite->id != 0)
        {
            x = layer[i].x_pos + obj->screen_x_pos;
            PS1_DrawSprite(sprite, x, y, 0);
        }
    }
}

/* 17ABC 8013C2BC -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/draw/draw_14FF4", DISPLAY_ALL_OBJECTS);
#else
/* score of ??? */
void DISPLAY_ALL_OBJECTS(void)
{
    short sVar1;
    Display *pDVar2;
    Display *pDVar3;
    s16 uVar4;
    u_short uVar5;
    s16 iVar6;
    Obj *new_var4;
    ObjType obj_type;
    u32 uVar8;
    short cnt_1;
    Obj *obj;
    s16 iVar10;
    s16 prio;
    Obj *new_var;
    s16 test_1;
    s16 *test_2;
    ActiveObjects *new_var2;
    s16 *new_var3;

    PS1_BossObj = null;
    prio = 7;
    PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[6];
    while (true)
    {
        cnt_1 = 0;
        obj = &level.objects[actobj.objects[cnt_1]];
        while (cnt_1 < actobj.num_active_objects)
        {
            if (prio == 1 && (flags[obj->type].flags0 >> OBJ0_BOSS & 1))
                PS1_BossObj = obj;

            if (obj->display_prio == prio)
            {
                if (num_world == 5 && num_level == 4 && obj->type == TYPE_MEDAILLON_TOON)
                {
                    PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[10];
                    display2(obj);
                    PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[6];
                }
                else if (obj->type == TYPE_EAU && num_world == 5 && num_level == 8)
                {
                    PS1_DrawSpriteSemiTrans = true;
                    if (obj->x_pos >= 300)
                        display2(obj);
                    PS1_DrawSpriteSemiTrans = false;
                }
                else
                {
                    obj_type = obj->type;
                    if (obj_type == TYPE_CYMBALE)
                        DISPLAY_CYMBALE(obj, true);
                    else if (
                        !(
                            obj_type == TYPE_NEIGE || obj_type == TYPE_PALETTE_SWAPPER ||
                            obj_type == TYPE_GENERATING_DOOR ||
                            (obj_type == TYPE_MST_SCROLL && obj->hit_points != 0) ||
                            obj_type == TYPE_SCROLL_SAX || obj_type == TYPE_BB1_VIT
                        )
                    )
                    {
                        if (obj_type == TYPE_LAVE)
                        {
                            if (D_801E4DF8 != D_801CEF7A)
                            {
                                SetPolyG4(&PS1_CurrentDisplay->field_0x6094_0x60b7);
                                SetSemiTrans(&PS1_CurrentDisplay->field_0x6094_0x60b7, true);
                                SetShadeTex(&PS1_CurrentDisplay->field_0x6094_0x60b7, true);

                                PS1_CurrentDisplay->field_0x6094_0x60b7.x0 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.y0 = obj->screen_y_pos + 25;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.x1 = SCREEN_WIDTH;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.y1 = obj->screen_y_pos + 25;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.x2 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.y2 = obj->screen_y_pos + 90;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.x3 = SCREEN_WIDTH;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.y3 = obj->screen_y_pos + 90;

                                PS1_CurrentDisplay->field_0x6094_0x60b7.r0 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.g0 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.b0 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.r1 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.g1 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.b1 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.r2 = 173;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.g2 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.b2 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.r3 = 176;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.g3 = 0;
                                PS1_CurrentDisplay->field_0x6094_0x60b7.b3 = 0;
                                AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->field_0x6094_0x60b7);
                                PS1_CurrentDisplay->drawing_environment.tpage = GetTPage(1, 1, 256, 0);
                                SetDrawEnv(
                                    &PS1_CurrentDisplay->map_drawing_environment_primitives[(u16) D_801E4BE0],
                                    &PS1_CurrentDisplay->drawing_environment
                                );
                                AddPrim(
                                    &PS1_CurrentDisplay->ordering_table[9],
                                    &PS1_CurrentDisplay->map_drawing_environment_primitives[(u16) D_801E4BE0]
                                );
                                D_801E4BE0++;
                                D_801CEF7A = D_801E4DF8;
                            }
                            PS1_DrawSpriteSemiTrans = false;
                            display2(obj);
                        }
                        else
                        {
                            PS1_DrawSpriteSemiTrans = false;
                            display2(obj);
                            PS1_DrawSpriteSemiTrans = false;
                        }
                    }
                }
            }
            cnt_1++;
            obj = &level.objects[actobj.objects[cnt_1]];
        }

        if (prio == 3)
        {
            if (ray.iframes_timer % 2 || ray.iframes_timer > 90)
            {
                if (((ray.flags & (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE))) == (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE))))
                    display2(&ray);
            }
            DISPLAY_POING();
        }
        else if (prio == 2 && nb_cymbal_in_map != 0)
        {
            for (cnt_1 = 0; cnt_1 < nb_cymbal_in_map; cnt_1++)
            {
                obj = (new_var4 = &level.objects[cymbal_obj_id[cnt_1]]);
                if (obj->flags & FLG(OBJ_ACTIVE)) /* getting rid of brackets worsens score??? */
                {
                    DISPLAY_CYMBALE(obj, false);
                }
            }
        }

        prio--;
        if (prio < 1)
        {
            cnt_1 = 0;
            new_var2 = &actobj;
            new_var3 = actobj.objects;
            obj = &level.objects[new_var3[cnt_1]];
            while (cnt_1 < new_var2->num_active_objects)
            {
                cnt_1 = cnt_1 + 1;
                new_var3 = actobj.objects;
                if ((obj->display_prio == 0) && (obj->type == TYPE_DUNE))
                {
                    display2(obj);
                    PS1_DrawSpriteSemiTrans = false;
                    return;
                }
                obj = &level.objects[new_var3[cnt_1]];
            }

            PS1_DrawSpriteSemiTrans = false;
            return;
        }
    }
}
#endif
