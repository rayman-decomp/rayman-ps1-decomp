#include "obj/hyb_bbf2.h"

#ifdef BSS_DEFS
u8 BBF2DEsk;
u8 BBF2GEsk;
s16 NiveauSol;
s16 YPosBBF2D;
s16 YPosBBF2G;
Obj *TirBBF2D;
Obj *TirBBF2G;
#endif

/* 75B14 8019A314 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/hyb_bbf2", doBBF2command);
#else
/*
duplication?
var_v1?
*/
void doBBF2command(Obj *bbf2_obj)
{
    s16 spr_x; s16 spr_y_1; s16 spr_w; s16 spr_h;
    s16 spr_y_2;
    s16 bbf2_y_1;
    s32 bbf2_y_2;
    s16 bbf2_y_3;
    s16 var_v1;
    u16 unk_2;
    s16 unk_1;

    if (!(bbf2_obj->main_etat == 0 && bbf2_obj->sub_etat == 2))
    {
        if (bbf2_obj->type == TYPE_HYB_BBF2_D)
        {
            if (BBF2DEsk == 0)
            {
                unk_1 = 0x5A;
                YPosBBF2D =
                    NiveauSol - (ray.offset_by - ray.offset_hy) -
                    (((ray.x_pos + ray.offset_bx - xmap) >> 1) - unk_1);
            }
            else
            {
                if (BBF2DEsk == 100)
                {
                    bbf2_y_1 = bbf2_obj->y_pos + ((bbf2_obj->offset_by + bbf2_obj->offset_hy) >> 1);
                    GET_SPRITE_POS(TirBBF2G, 8, &spr_x, &spr_y_1, &spr_w, &spr_h);
                    if (
                        (spr_y_1 + spr_h) < bbf2_y_1 &&
                        ((spr_y_1 + spr_h) > bbf2_obj->y_pos + bbf2_obj->offset_hy - 0xA)
                    )
                        YPosBBF2D += 50;
                    else if (
                        spr_y_1 > bbf2_y_1 &&
                        (spr_y_1 < (bbf2_obj->y_pos + bbf2_obj->offset_by + 0xA))
                    )
                        YPosBBF2D -= 50;
                    else if (
                        (spr_y_1 > ((bbf2_obj->y_pos + bbf2_obj->offset_hy) - 0xA)) &&
                        ((spr_y_1 + spr_h) < (bbf2_obj->y_pos + bbf2_obj->offset_by + 0xA))
                    )
                        YPosBBF2D -= 80;
                    else
                    {
                        unk_1 = 0x5A;
                        YPosBBF2D =
                            NiveauSol - (ray.offset_by - ray.offset_hy) -
                            (((ray.x_pos + ray.offset_bx - xmap) >> 1) - unk_1);
                    }
                }
                BBF2DEsk--;
            }
            unk_2 = YPosBBF2D - 150 - bbf2_obj->y_pos;
        }
        else if (bbf2_obj->type == TYPE_HYB_BBF2_G)
        {
            if (BBF2GEsk == 0)
            {
                unk_1 = 0x46;
                YPosBBF2G =
                    NiveauSol - (ray.offset_by - ray.offset_hy) +
                    (((ray.x_pos + ray.offset_bx - xmap) >> 1) - unk_1);
            }
            else
            {
                if (BBF2GEsk == 100)
                {
                    bbf2_y_1 = bbf2_obj->y_pos + ((bbf2_obj->offset_by + bbf2_obj->offset_hy) >> 1);
                    GET_SPRITE_POS(TirBBF2D, 8, &spr_x, &spr_y_1, &spr_w, &spr_h);
                    if (
                        ((spr_y_1 + spr_h) < bbf2_y_1) &&
                        ((spr_y_1 + spr_h) > ((bbf2_obj->y_pos + bbf2_obj->offset_hy) - 0xA))
                    )
                        YPosBBF2G += 50;
                    else if (
                        (spr_y_1 > bbf2_y_1) &&
                        (spr_y_1 < (bbf2_obj->y_pos + bbf2_obj->offset_by + 0xA))
                    )
                        YPosBBF2G -= 50;
                    else if (
                        (spr_y_1 > ((bbf2_obj->y_pos + bbf2_obj->offset_hy) - 0xA)) &&
                        ((spr_y_1 + spr_h) < (bbf2_obj->y_pos + bbf2_obj->offset_by + 0xA))
                    )
                    {
                        YPosBBF2G -= 80;
                    }
                    else
                    {
                        unk_1 = 0x46;
                        YPosBBF2G =
                            NiveauSol - (ray.offset_by - ray.offset_hy) +
                            (((ray.x_pos + ray.offset_bx - xmap) >> 1) - unk_1);
                    }
                }
                BBF2GEsk--;
            }
            unk_2 = YPosBBF2G - 150 - bbf2_obj->y_pos;
        }

        bbf2_y_2 = bbf2_obj->y_pos;
        if (
            ((bbf2_y_2 > ymap + 90) && (s16) unk_2 > 0) ||
            ((bbf2_y_2 < ymap - 150) && (s16) unk_2 < 0)
        )
        {
            unk_2 = 0;
            bbf2_obj->speed_y = 0;
        }

        var_v1 = (s16) unk_2; /* TODO: ??? */
        if (var_v1 != 0)
        {
            bbf2_obj->speed_y = MAX_1(-48, MIN_1(48,
                SGN(((s16) unk_2) - bbf2_obj->speed_y) + bbf2_obj->speed_y));
        }
    }
    GET_SPRITE_POS(&ray, 5, &spr_x, &spr_y_2, &spr_w, &spr_h);
    spr_y_2 += 15;
    bbf2_y_3 = bbf2_obj->y_pos + 150;
    if (
        bbf2_obj->sub_etat == 0 &&
        (spr_y_2 > bbf2_y_3 - 15) && (spr_y_2 < bbf2_y_3 + 15)
    )
        set_sub_etat(bbf2_obj, 5);
    else if (
        (bbf2_obj->sub_etat == 6 || bbf2_obj->sub_etat == 4) &&
        ((spr_y_2 < bbf2_y_3 - 20) || (spr_y_2 > bbf2_y_3 + 20))
    )
        set_sub_etat(bbf2_obj, 7);
    else if (
        (bbf2_obj->sub_etat == 5 || bbf2_obj->sub_etat == 6) &&
        (spr_y_2 > bbf2_y_3 - 7) && (spr_y_2 < bbf2_y_3 + 7)
    )
        set_sub_etat(bbf2_obj, 3);
    else if (bbf2_obj->sub_etat == 3 && bbf2_obj->anim_frame == 3)
    {
        AllocateTirBBF2(bbf2_obj);
        if (bbf2_obj->type == TYPE_HYB_BBF2_D)
            BBF2GEsk = 100;
        else
            BBF2DEsk = 100;
    }
}
#endif

/* 76300 8019AB00 -O2 -msoft-float */
void DO_HYB_BBF2_POING_COLLISION(Obj *obj)
{
    /* TODO: ??? switch instead didn't work */
    if (obj->sub_etat == 2)
    {}
    else if (obj->sub_etat == 1)
    {}
    else
    {
        if (level.objects[obj->field24_0x3e].sub_etat != 1)
        {
            obj->hit_points--;
            level.objects[obj->field24_0x3e].hit_points = obj->hit_points;
            if (obj->hit_points != 0)
                set_main_and_sub_etat(obj, 0, 1);
            else
            {
                set_main_and_sub_etat(obj, 0, 2);
                obj->speed_y = -128;
                obj->speed_x = 0;
                obj->flags &= ~FLG(OBJ_READ_CMDS);
                obj->field23_0x3c = 1;

                set_main_and_sub_etat(&level.objects[obj->field24_0x3e], 0, 2);
                level.objects[obj->field24_0x3e].speed_y = -128;
                level.objects[obj->field24_0x3e].speed_x = 0;
                level.objects[obj->field24_0x3e].flags &= ~FLG(OBJ_READ_CMDS);
                level.objects[obj->field24_0x3e].field23_0x3c = 1;
            }
        }
    }
}

/* 764B4 8019ACB4 -O2 -msoft-float */
void AllocateTirBBF2(Obj *bbf2_obj)
{
    Obj *cur_obj = &level.objects[0];
    s16 i = 0;
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_HYB_BBF2_LAS && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj->display_prio = 4;
            cur_obj->init_x_pos = cur_obj->x_pos = bbf2_obj->x_pos;
            cur_obj->init_y_pos = cur_obj->y_pos = bbf2_obj->y_pos;
            if (bbf2_obj->type == TYPE_HYB_BBF2_D)
            {
                cur_obj->speed_x = -5;
                TirBBF2D = cur_obj;
                cur_obj->flags &= ~FLG(OBJ_FLIP_X);
            }
            else
            {
                cur_obj->speed_x = 5;
                TirBBF2G = cur_obj;
                cur_obj->flags |= FLG(OBJ_FLIP_X);
            }
            cur_obj->speed_y = 0;
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            cur_obj->field24_0x3e = bbf2_obj->field24_0x3e;
            break;
        }
        cur_obj++;
        i++;
    }
}

/* 765B8 8019ADB8 -O2 -msoft-float */
void DO_HYB_BBF2_LAS(Obj *las_obj)
{
    Obj *unk_obj;
    s16 i;
    Obj *cur_obj_1;
    s16 nb_objs;
    s16 j;
    s16 las_x; s16 las_y; s16 las_w; s16 las_h;
    s16 cur_x; s16 cur_y; s16 cur_w; s16 cur_h;
    s16 unk_1 = las_obj->field24_0x3e;

    if (level.objects[unk_1].type == TYPE_HYB_BBF2_D || level.objects[unk_1].type == TYPE_HYB_BBF2_G)
    {
        unk_obj = &level.objects[unk_1];
        if ((s16) OBJ_IN_COL_ZDC(las_obj, unk_obj))
        {
            i = 0;
            cur_obj_1 = &level.objects[i];
            nb_objs = level.nb_objects;
            while (i < nb_objs)
            {
                if (cur_obj_1->type == TYPE_BOUM && !(cur_obj_1->flags & FLG(OBJ_ACTIVE)))
                {
                    GET_ANIM_POS(las_obj, &las_x, &las_y, &las_w, &las_h);
                    GET_ANIM_POS(cur_obj_1, &cur_x, &cur_y, &cur_w, &cur_h);
                    cur_obj_1->anim_frame = 0;
                    cur_obj_1->x_pos = las_x - cur_obj_1->offset_bx;
                    if (las_obj->speed_x > 0)
                        cur_obj_1->x_pos += las_w;
                    cur_obj_1->y_pos = las_y + (las_h >> 1) - ((cur_obj_1->offset_by + cur_obj_1->offset_hy) >> 1);
                    calc_obj_pos_map(cur_obj_1);
                    cur_obj_1->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                    break;
                }
                cur_obj_1++;
                i++;
            }
            DO_HYB_BBF2_POING_COLLISION(unk_obj);
            las_obj->flags &= ~FLG(OBJ_ALIVE);
            las_obj->flags &= ~FLG(OBJ_ACTIVE);
        }
    }

    if (las_obj->speed_y == 0)
    {
        j = 0;
        unk_obj = &level.objects[actobj.objects[j]];
        while (j < actobj.num_active_objects)
        {
            if (
                unk_obj->type == TYPE_HYB_BBF2_LAS &&
                unk_obj->id != las_obj->id && (s16) OBJ_IN_COL_ZDC(las_obj, unk_obj)
            )
            {
                unk_obj->speed_x = 0;
                las_obj->speed_x = 0;
                unk_obj->speed_y = 3;
                las_obj->speed_y = 3;
                las_obj->field24_0x3e = unk_obj->id;
                unk_obj->field24_0x3e = las_obj->id;
                break;
            }
            j++;
            unk_obj = &level.objects[actobj.objects[j]];
        }
    }
}

/* 76870 8019B070 -O2 -msoft-float */
s32 OBJ_IN_COL_ZDC(Obj *obj1, Obj *obj2)
{
    s16 x1; s16 y1; s16 w1;
    s16 x2; s16 y2; s16 w2;
    s16 h;
    ZDC *zdc1 = get_zdc(obj1, 0);
    ZDC *zdc2 = get_zdc(obj2, 0);

    GET_SPRITE_POS(obj1, zdc1->sprite, &x1, &y1, &w1, &h);
    GET_SPRITE_POS(obj2, zdc2->sprite, &x2, &y2, &w2, &h);

    if (!(obj1->flags & FLG(OBJ_FLIP_X)))
        x1 += zdc1->x_pos;
    else
        x1 = (x1 + w1) - (zdc1->x_pos + zdc1->width);

    if (!(obj2->flags & FLG(OBJ_FLIP_X)))
        x2 += zdc2->x_pos;
    else
        x2 = (x2 + w2) - (zdc2->width + zdc2->x_pos);
    y1 += zdc1->y_pos;
    y2 += zdc2->y_pos;

    return inter_box(x1, y1, zdc1->width, zdc1->height, x2, y2, zdc2->width, zdc2->height);
}
