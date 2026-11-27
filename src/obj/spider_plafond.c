#include "obj/spider_plafond.h"

#ifdef BSS_DEFS
u8 position_ray;
#endif

/* 537C0 80177FC0 -O2 -msoft-float */
void get_spi_zdc(Obj *param_1, s16 *param_2, s16 *param_3, s16 *param_4, s16 *param_5)
{
    u8 eta_flags = param_1->eta[param_1->main_etat][param_1->sub_etat].flags;

    if (eta_flags & 0x40)
    {
        *param_2 = param_1->x_pos + 69;
        *param_3 = param_1->y_pos + 38;
        *param_4 = 21;
        *param_5 = 30;
    }
    else if (eta_flags & 0x80)
    {
        *param_2 = param_1->x_pos + 69;
        *param_3 = param_1->y_pos + 86;
        *param_4 = 34;
        *param_5 = 10;
    }
    else
    {
        *param_2 = param_1->x_pos + 71;
        *param_3 = param_1->y_pos + 71;
        *param_4 = 29;
        *param_5 = 19;
    }
}

/* 53894 80178094 -O2 -msoft-float */
void DO_SPIDER_PLAFOND(Obj *spipl_obj)
{
    u8 sub_etat;
    Obj *poing_obj;
    s16 poing_x; s16 poing_y_1; s16 poing_y_2;
    s16 spipl_x; s16 spipl_y_1; s16 spipl_y_2;
    s16 i;
    Obj *cur_obj;
    s16 nb_objs;
    s16 spipl_spr_x; s16 spipl_spr_y; s16 spipl_spr_w; s16 spipl_spr_h;
    u8 new_flip;
    s16 cen_x = get_center_x(spipl_obj);
    s16 cen_y = get_center_y(spipl_obj);

    if (
        (
            spipl_obj->main_etat == 0 &&
            (sub_etat = spipl_obj->sub_etat,
            sub_etat == 27 || sub_etat == 24 || sub_etat == 30 || sub_etat == 11)
        ) ||
        (spipl_obj->main_etat == 1 && spipl_obj->sub_etat == 2)
    )
    {
        if (poing.is_active)
        {
            poing_obj = &level.objects[poing_obj_id];
            poing_x = poing_obj->x_pos + poing_obj->offset_bx;
            poing_y_1 = poing_obj->y_pos + poing_obj->offset_by;
            poing_y_2 = poing_obj->y_pos + poing_obj->offset_hy;

            spipl_x = spipl_obj->x_pos + spipl_obj->offset_bx;
            spipl_y_1 = spipl_obj->y_pos + spipl_obj->offset_by + 5;
            spipl_y_2 = spipl_obj->y_pos + spipl_obj->offset_hy - 5;
            if (
                (poing_y_1 <= spipl_y_1 || poing_y_2 <= spipl_y_1) &&
                (poing_y_1 >= spipl_y_2 || poing_y_2 >= spipl_y_2) &&
                (poing_x <= spipl_x + 60) && (poing_x >= spipl_x - 60)
            )
            {
                spipl_obj->speed_x = 0;
                spipl_obj->speed_y = 0;
                set_main_and_sub_etat(spipl_obj, 0, 25);
            }
        }
    }
    else if (
        spipl_obj->main_etat == 0 && spipl_obj->sub_etat == 26 &&
        !poing.is_active
    )
        set_sub_etat(spipl_obj, 27);

    if (spipl_obj->main_etat == 1 && spipl_obj->sub_etat == 2)
    {
        SET_X_SPEED(spipl_obj);
        if (block_flags[calc_typ_travd(spipl_obj, false)] >> BLOCK_FULLY_SOLID & 1)
        {
            spipl_obj->flags =
                spipl_obj->flags & ~FLG(OBJ_FLIP_X) |
                (1 - (spipl_obj->flags >> OBJ_FLIP_X & 1) & 1) << OBJ_FLIP_X;
            set_main_and_sub_etat(spipl_obj, 0, 24);
            SET_X_SPEED(spipl_obj);
        }
        CALC_MOV_ON_BLOC(spipl_obj);
    }

    if (
        on_block_chdir(spipl_obj, cen_x, cen_y) &&
        test_allowed(spipl_obj, cen_x, cen_y)
    )
    {
        if (spipl_obj->main_etat == 1 && spipl_obj->sub_etat == 2)
        {
            set_main_and_sub_etat(spipl_obj, 0, 21);
            spipl_obj->speed_x = 0;
            spipl_obj->speed_y = 0;
            spipl_obj->flags =
                spipl_obj->flags & ~FLG(OBJ_FLIP_X) |
                (1 - (spipl_obj->flags >> OBJ_FLIP_X & 1) & 1) << OBJ_FLIP_X;
        }
        else if (
            spipl_obj->main_etat == 2 &&
            (spipl_obj->sub_etat == 3 || spipl_obj->sub_etat == 1 || spipl_obj->sub_etat == 2)
        )
        {
            set_main_and_sub_etat(spipl_obj, 0, 12);
            spipl_obj->speed_x = 0;
            spipl_obj->speed_y = 0;
        }
    }
    else
    {
        if (
            spipl_obj->main_etat == 2 && spipl_obj->sub_etat == 1 &&
            spipl_obj->anim_frame == 0
        )
        {
            spipl_obj->speed_x = 0;
            spipl_obj->speed_y = -10;
        }
        else if (
            spipl_obj->main_etat == 0 && spipl_obj->sub_etat == 20 &&
            spipl_obj->anim_frame == 27
        )
        {
            i = 0;
            cur_obj = &level.objects[i];
            nb_objs = level.nb_objects;
            while (i < nb_objs)
            {
                if ((cur_obj->type == TYPE_DARD_PLAFOND) && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
                {
                    GET_SPRITE_POS(spipl_obj, 2, &spipl_spr_x, &spipl_spr_y, &spipl_spr_w, &spipl_spr_h);
                    cur_obj->speed_x = 0;
                    cur_obj->speed_y = 32;
                    cur_obj->cmd_offset = -1;
                    cur_obj->flags &= ~FLG(OBJ_FLIP_X);

                    cur_obj->init_x_pos =
                    cur_obj->x_pos =
                        spipl_spr_x - cur_obj->offset_bx + (spipl_spr_w >> 1);

                    cur_obj->init_y_pos =
                    cur_obj->y_pos =
                        spipl_spr_y - cur_obj->offset_by + (spipl_spr_h >> 1);
                        
                    cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                    cur_obj->flags |= FLG(OBJ_READ_CMDS);
                    cur_obj->nb_cmd = 0;
                    if (ray.eta[ray.main_etat][ray.sub_etat].flags & 0x40)
                        position_ray = true;
                    else
                        position_ray = false;

                    DO_DARD_PLAFOND_ALWAYS(cur_obj);
                    break;
                }
                cur_obj++;
                i++;
            }
        }
    }

    if (
        spipl_obj->main_etat == 0 &&
        (sub_etat = spipl_obj->sub_etat,
        sub_etat == 20 || sub_etat == 13 || sub_etat == 23)
    )
    {
        new_flip = ray.x_pos > spipl_obj->x_pos;
        spipl_obj->flags = spipl_obj->flags & ~FLG(OBJ_FLIP_X) | (new_flip << OBJ_FLIP_X);
    }
}

/* 53E40 80178640 -O2 -msoft-float */
void DO_SPIDER_PLAFOND_POING_COLLISION(Obj *obj)
{
    s32 main_etat;

    if (--obj->hit_points == 0)
    {
        if (
            (
                obj->main_etat == 0 &&
                (obj->sub_etat == 12 || obj->sub_etat == 13 ||
                obj->sub_etat == 23 || obj->sub_etat == 20)
            ) ||
            (
                obj->main_etat == 2 &&
                (obj->sub_etat == 2 || obj->sub_etat == 3 ||
                obj->sub_etat == 28 || obj->sub_etat == 7)
            )
        )
            set_main_and_sub_etat(obj, 0, 19);
        else
            set_main_and_sub_etat(obj, 0, 18);
        obj->speed_y = -8;
        obj->speed_x = 0;
        obj->flags &= ~FLG(OBJ_READ_CMDS);
    }
    else
    {
        main_etat = obj->main_etat;
        if (main_etat == 1 && obj->sub_etat == 2)
        {
            /* this, or goto? */
            set_main_and_sub_etat(obj, 0, 14);
            obj->speed_y = 0;
            obj->speed_x = 0;
        }
        else if (main_etat == 0)
        {
            /*
            using a switch would generate rodata
            using a var for obj->sub_etat doesn't seem to work either
            */
            if (
                obj->sub_etat == 11 || obj->sub_etat == 29 ||
                obj->sub_etat == 25 || obj->sub_etat == 26 ||
                obj->sub_etat == 27 || obj->sub_etat == 24 ||
                obj->sub_etat == 30
            )
            {
                set_main_and_sub_etat(obj, 0, 14);
                obj->speed_y = 0;
                obj->speed_x = 0;
            }
            else if (
                obj->sub_etat == 12 || obj->sub_etat == 13 ||
                obj->sub_etat == 23 || obj->sub_etat == 20
            )
            {
                if (obj->x_pos < ray.x_pos)
                    obj->flags |= FLG(OBJ_FLIP_X);
                else
                    obj->flags &= ~FLG(OBJ_FLIP_X);
                set_main_and_sub_etat(obj, 0, 17);
            }
        }
    }
}

/* 54030 80178830 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/spider_plafond", SPIDER_PLAFOND_REACT);
#else
void SPIDER_PLAFOND_REACT(Obj *obj)
{
    s32 prev_flip;
    u8 new_flip;

    if (obj->main_etat == 0 && (obj->sub_etat == 12 || obj->sub_etat == 13))
        set_sub_etat(obj, 20);
    else if (
        (obj->main_etat == 0 && (obj->sub_etat == 11 || obj->sub_etat == 30)) ||
        (obj->main_etat == 1 && obj->sub_etat == 2)
    )
    {
        prev_flip = obj->flags >> OBJ_FLIP_X;
        prev_flip &= 1;
        if (
            (ray.x_pos > obj->x_pos && prev_flip != true) || /* ??? */
            (ray.x_pos <= obj->x_pos && prev_flip != false)
        )
        {
            new_flip = ray.x_pos > obj->x_pos;
            obj->flags = obj->flags & ~FLG(OBJ_FLIP_X) | (new_flip << OBJ_FLIP_X);
            obj->speed_x = 0;
            obj->speed_y = 0;
            set_main_and_sub_etat(obj, 0, 24);
        }
    }
}
#endif

/* 54138 80178938 -O2 -msoft-float */
void DO_DARD_PLAFOND_ALWAYS(Obj *obj)
{
    s16 diff_x;
    s16 diff_y;
    s16 dist;
    s16 abs_x;
    s16 speed_y;

    if (obj->cmd != 1)
    {
        diff_x = (ray.offset_bx + ray.x_pos) - (obj->offset_bx + obj->x_pos);
        if (position_ray != 0)
        {
            diff_y = (ray.offset_by + ray.y_pos) - (obj->offset_by + obj->y_pos);
        }
        else
        {
            diff_y = ((ray.offset_by >> 1) + ray.y_pos) - (obj->offset_by + obj->y_pos);
        }
        dist = __builtin_abs(diff_x) + __builtin_abs(diff_y);
        if (
            (ray.y_pos + ray.offset_by > obj->y_pos + (obj->offset_by - obj->offset_hy)) &&
            (
                (ray.x_pos + ray.offset_bx > obj->x_pos + obj->offset_bx && !(obj->flags & 0x4000)) ||
                (ray.x_pos + ray.offset_bx < obj->x_pos + obj->offset_bx && obj->flags & 0x4000)
            )
        )
        {
            if (dist > 0)
            {
                diff_x = ashl16(diff_x, 5) / dist;
                diff_y = ashl16(diff_y, 5) / dist;
            }
            obj->speed_y = MAX_1(MIN_1(SGN(diff_y - obj->speed_y) + obj->speed_y, 32), 0);
            if (obj->speed_y != 0)
            {
                obj->speed_x = MAX_1(MIN_1(SGN(diff_x - obj->speed_x) + obj->speed_x, 32), -32);
            }
            else if (obj->flags & 0x4000)
            {
                obj->speed_x = MAX_1(MIN_1(obj->speed_x - (obj->speed_x < diff_x), 32), -32);
            }
            else
            {
                obj->speed_x = MAX_1(MIN_1(obj->speed_x + (diff_x < obj->speed_x), 32), -32);
            }
        }
        else
        {
            obj->speed_x = MAX_1(MIN_1(obj->speed_x * 2, 32), -32);
            obj->speed_y = MIN_1(obj->speed_y * 2, 32);
        }
    }
    else
    {
        if (ray.x_pos + ray.offset_bx > obj->x_pos + obj->offset_bx)
        {
            obj->flags &= ~0x4000;
        }
        else if (ray.x_pos + ray.offset_bx < obj->x_pos + obj->offset_bx)
        {
            obj->flags |= 0x4000;
        }
    }
    if (obj->speed_x == 0 && obj->speed_y == 0)
    {
        obj->speed_x = obj->flags & 0x4000 ? -1 : 1;
    }
    abs_x = __builtin_abs(obj->speed_x);
    speed_y = obj->speed_y;
    if (abs_x * 3 < speed_y || abs_x * 4 < speed_y * 3)
    {
        obj->anim_frame = 0;
    }
    else if (abs_x * 3 < speed_y * 4)
    {
        obj->anim_frame = 0x0B;
    }
    else if (abs_x < speed_y * 3)
    {
        obj->anim_frame = 0x0A;
    }
    else
    {
        obj->anim_frame = 9;
    }
    if (obj->speed_x > 0 && obj->flags & 0x4000)
    {
        obj->flags &= ~0x4000;
    }
    else if (obj->speed_x < 0 && !(obj->flags & 0x4000))
    {
        obj->flags |= 0x4000;
    }
}
