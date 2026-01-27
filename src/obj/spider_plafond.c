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
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/obj/spider_plafond", DO_DARD_PLAFOND_ALWAYS);
#else
/*
score of 3650
look at DO_DARK2_TOONS_COMMAND
*/
void DO_DARD_PLAFOND_ALWAYS(Obj *obj)
{
    s16 temp_a1_3;
    s16 temp_a3;
    s16 temp_v1_1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 temp_v1_5;
    s16 temp_v1_6;
    s16 temp_v1_7;
    s16 temp_v1_8;
    s16 diff_y;
    s16 diff_x;
    s16 var_v0_1;
    s16 var_v0_11;
    s32 var_v0_4;
    s16 var_v0_6;
    s16 var_v1_1;
    s16 var_v1_2;
    s16 var_v1_3;
    s16 var_v1_4;
    s16 var_v1_5;
    s32 temp_a0_1;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a1_1;
    s32 temp_a1_2;
    s32 temp_v0_1;
    s32 temp_v0_10;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1_9;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_5;
    s32 var_v0_7;
    s32 var_v0_8;
    s32 var_v0_9;
    u32 temp_v1_10;
    u32 temp_v1_11;
    u32 var_v0_10;
    u32 var_v0_13;
    u8 var_v0_12;

    if (obj->cmd != 1)
    {
        diff_x = (ray.offset_bx + ray.x_pos) - (obj->offset_bx + (u16) obj->x_pos);
        if (position_ray != 0)
        {
            diff_y = (ray.offset_by + ray.y_pos) - (obj->offset_by + (u16) obj->y_pos);
        }
        else
        {
            diff_y = (((u8) ray.offset_by >> 1) + ray.y_pos) - (obj->offset_by + (u16) obj->y_pos);
        }
        var_v1_1 = __builtin_abs(diff_x);
        var_v0_1 = __builtin_abs(diff_y);
        temp_a3 = var_v1_1 + var_v0_1;
        if (
            (ray.y_pos + ray.offset_by > obj->y_pos + (obj->offset_by - obj->offset_hy)) &&
            (
                temp_a1_1 = ray.x_pos + ray.offset_bx,
                temp_a0_1 = obj->x_pos + obj->offset_bx,
                var_v0_2 = temp_a1_1 < temp_a0_1,
                (
                    temp_a0_1 < temp_a1_1 &&
                    (var_v0_2 = temp_a1_1 < temp_a0_1, !(obj->flags & 0x4000))
                ) ||
                (var_v0_2 && obj->flags & 0x4000)
            )
        )
        {
            if (temp_a3 > 0)
            {
                diff_x = ashl16(diff_x, 5U) / temp_a3;
                diff_y = ashl16(diff_y, 5U) / temp_a3;
            }
            obj->speed_y = MAX_1(MIN_1(SGN(diff_y - obj->speed_y) + obj->speed_y, 32), 0);
            if (obj->speed_y != 0)
            {
                obj->speed_x = MAX_1(MIN_1(SGN(diff_x - obj->speed_x) + obj->speed_x, 32), -32);
            }
            else
            {
                /* should be similar to other obj->speed_x = ... but dunno rn */
                if (obj->flags & 0x4000)
                {
                    temp_v1_1 = obj->speed_x;
                    if (temp_v1_1 < diff_x)
                    {
                        var_v0_7 = diff_x << 0x10;
                        if ((temp_v1_1 - 1) >= 0x20)
                        {
                            goto block_86;
                        }
                        goto block_81;
                    }
                    var_v0_7 = diff_x << 0x10;
                    if (temp_v1_1 < 0x20)
                    {
block_81:
                        /*if (obj->speed_x < (var_v0_7 >> 0x10))*/
                        if (obj->speed_x < diff_x)
                        {
                            var_v0_4 = -0x0020;
                            if ((obj->speed_x - 1) >= -0x1F)
                            {
                                goto block_85;
                            }
                        }
                        else
                        {
                            var_v0_4 = -0x0020;
                            if (obj->speed_x >= -0x1F)
                            {
                                goto block_85;
                            }
                        }
                    }
                    else
                    {

block_85:
block_86:
                        if (obj->speed_x < diff_x && (obj->speed_x - 1) >= 0x20)
                        {
                            var_v0_4 = 0x0020;
                        }
                        else if (obj->speed_x < diff_x || obj->speed_x < 0x20)
                        {
block_90:
                            var_v0_4 = obj->speed_x - (obj->speed_x < diff_x);
                        }
                        else
                        {
                            var_v0_4 = 0x0020;
                        }
                    }
                }
                else
                {

                    /*if (
                        (
                            (var_s3 < obj->speed_x && (obj->speed_x + 1) < 0x20) ||
                            (var_s3 >= obj->speed_x && obj->speed_x < 0x20)
                        ) &&
                        (
                            ((var_s3) < obj->speed_x && (obj->speed_x + 1) >= -0x1F) ||
                            ((var_s3) >= obj->speed_x && obj->speed_x >= -0x1F)
                        )
                    )
                    {
block_100:
                        if (var_s3 < obj->speed_x && (obj->speed_x + 1) >= 0x20)
                        {
                            var_v0_4 = 0x0020;
                        }
                        else if (!(var_s3 >= obj->speed_x && obj->speed_x >= 0x20))
                        {
                            var_v0_4 = obj->speed_x + (var_s3 < obj->speed_x);
                        }
                        else
                        {
                            var_v0_4 = 0x0020;
                        }
                    }
                    else
                    {
                        var_v0_4 = -0x0020;
                    }*/
                    temp_v1_1 = obj->speed_x;
                    if (diff_x < temp_v1_1)
                    {
                        var_v0_8 = diff_x << 0x10;
                        if ((temp_v1_1 + 1) < 0x20)
                        {
                            goto block_96;
                        }
                        else
                            goto block_101;
                    }
                    var_v0_8 = diff_x << 0x10;
                    if (temp_v1_1 < 0x20)
                    {
block_96:
                        /*if ((var_v0_8 >> 0x10) < obj->speed_x)*/
                        if ((diff_x) < obj->speed_x)
                        {
                            var_v0_4 = -0x0020;
                            if ((obj->speed_x + 1) >= -0x1F)
                            {
                                goto block_100;
                            }
                        }
                        else
                        {
                            var_v0_4 = -0x0020;
                            if (obj->speed_x >= -0x1F)
                            {
                                goto block_100;
                            }
                        }
                    }
                    else
                    {
block_100:
block_101:
                        if (diff_x < obj->speed_x && (obj->speed_x + 1) >= 0x20)
                        {
                            var_v0_4 = 0x0020;
                        }
                        else if (!(diff_x >= obj->speed_x && obj->speed_x >= 0x20))
                        {
                            var_v0_4 = obj->speed_x + (diff_x < obj->speed_x);
                        }
                        else
                        {
                            var_v0_4 = 0x0020;
                        }
                    }
                }
                obj->speed_x = var_v0_4;
            }
        }
        else
        {
            var_v1_3 = obj->speed_x * 2;
            var_v0_9 = var_v1_3 < -0x20;
            if (var_v1_3 >= 0x21)
            {
                var_v1_3 = 0x0020;
                var_v0_9 = 0x20 < -0x20;
            }
            if (var_v0_9 != 0)
            {
                var_v1_3 = -0x0020;
            }
            obj->speed_x = var_v1_3;
            var_v1_4 = obj->speed_y * 2;
            if (var_v1_4 >= 0x21)
            {
                var_v1_4 = 0x0020;
            }
            obj->speed_y = var_v1_4;
        }
    }
    else
    {
        temp_a1_2 = (s16) ray.x_pos + ray.offset_bx;
        temp_a0_2 = obj->x_pos + obj->offset_bx;
        if (temp_a0_2 < temp_a1_2)
        {
            var_v0_10 = obj->flags & ~0x4000;
            goto block_119;
        }
        if (temp_a1_2 < temp_a0_2)
        {
            var_v0_10 = obj->flags | 0x4000;
block_119:
            obj->flags = var_v0_10;
        }
    }
    if ((s32) obj->speed_x == 0)
    {
        var_v1_5 = 1;
        if (obj->flags & 0x4000)
        {
            var_v1_5 = -1;
        }
        obj->speed_x = var_v1_5;
    }
    var_v0_11 = obj->speed_x;
    temp_a1_3 = obj->speed_y;
    if (var_v0_11 < 0)
    {
        var_v0_11 = -var_v0_11;
    }
    temp_a0_3 = var_v0_11 * 3;
    if ((temp_a0_3 < temp_a1_3) || (temp_v1_9 = temp_a1_3 * 3, (((var_v0_11 * 4) < temp_v1_9) != 0)))
    {
        obj->anim_frame = 0;
    }
    else
    {
        var_v0_12 = 0x0B;
        if (temp_a0_3 >= (temp_a1_3 * 4))
        {
            var_v0_12 = 0x0A;
            if (var_v0_11 >= temp_v1_9)
            {
                var_v0_12 = 9;
            }
        }
        obj->anim_frame = var_v0_12;
    }
    if (obj->speed_x > 0)
    {
        temp_v1_10 = obj->flags;
        if (temp_v1_10 & 0x4000)
        {
            var_v0_13 = temp_v1_10 & ~0x4000;
            goto block_139;
        }
        goto block_137;
    }
block_137:
    if (obj->speed_x < 0)
    {
        temp_v1_11 = obj->flags;
        var_v0_13 = temp_v1_11 | 0x4000;
        if (!(temp_v1_11 & 0x4000))
        {
block_139:
            obj->flags = var_v0_13;
        }
    }
}
#endif
