#include "obj/ufo_idc.h"

/* 74954 80199154 -O2 -msoft-float */
s16 test_block_chdir(Obj *obj, s16 *out_unk, s16 off_x, s16 off_y)
{
    u8 res = false;
    s16 obj_x = (obj->x_pos + off_x) >> 4;
    s16 obj_y = (obj->y_pos + off_y) >> 4;

    *out_unk = obj_x + obj_y * mp.width;
    if (*out_unk != obj->test_block_index)
    {
        obj->test_block_index = *out_unk;
        if (
            obj_x >= 0 && (mp.width - 1 >= obj_x) &&
            obj_y >= 0 && (mp.height - 1 >= obj_y)
        )
            res = (mp.map[*out_unk] & 0xFC00) == 0x400;
    }
    return res;
}

/* 74A30 80199230 -O2 -msoft-float */
void DO_MOVING_WITH_INDICATOR_COMMAND(Obj *ufo_idc_obj)
{
    s16 block_index[5];
    Obj *idc;
    s16 dir_y;
    u16 neg_speed;
    s16 spd_x;
    s16 speed;
    s16 spd_y;
    s32 abs_y;
    s32 max_speed;
    s16 i;
    s16 dir_x;

    ufo_idc_obj->flags &= ~0x4000;
    if (
        (ufo_idc_obj->main_etat == 0) && (ufo_idc_obj->sub_etat == 14) &&
        test_block_chdir(ufo_idc_obj, block_index, ufo_idc_obj->offset_bx, ufo_idc_obj->offset_by)
    )
    {
        i = 0;
        idc = &level.objects[actobj.objects[i]];
        while (i < actobj.num_active_objects)
        {
            if (idc->type == TYPE_INDICATOR)
            {
                if (
                    (s16) (((idc->x_pos + idc->offset_bx) >> 4) +
                    (((idc->y_pos + idc->offset_by) >> 4) * mp.width))
                    == block_index[0]
                )
                {
                    abs_y = ufo_idc_obj->speed_y;
                    spd_x = ufo_idc_obj->speed_x;
                    spd_y = abs_y;
                    max_speed = __builtin_abs(spd_x);
                    abs_y = __builtin_abs(spd_y);
                    if (max_speed < abs_y)
                    {
                        max_speed = abs_y;
                    }
                    speed = max_speed;
                    switch (idc->sub_etat)
                    {
                    case 8:
                        if (spd_x == 0)
                        {
                            if (spd_y > 0)
                            {
                                spd_y = -speed;
                            }
                            else if (spd_y < 0)
                            {
                                spd_y = speed;
                            }
                        }
                        else if (spd_y == 0)
                        {
                            if (spd_x > 0)
                            {
                                spd_x = -speed;
                            }
                            else if (spd_x < 0)
                            {
                                spd_x = speed;
                            }
                        }
                        else
                        {
                            spd_x = -spd_x;
                            spd_y = -spd_y;
                        }
                        break;
                    case 9:
                    case 10:
                        dir_x = -1;
                        if (idc->sub_etat == 9)
                        {
                            dir_x = 1;
                        }
                        if (spd_y == 0)
                        {
                            if (spd_x > 0)
                            {
                                spd_x = speed + dir_x;
                                if (spd_x > 4)
                                {
                                    spd_x = 4;
                                }
                                if (spd_x < 2)
                                {
                                    spd_x = 2;
                                }
                            }
                            else
                            {
                                if (spd_x < 0)
                                {
                                    spd_x = -speed + dir_x;
                                    if (spd_x > -2)
                                    {
                                        spd_x = -2;
                                    }
                                    if (spd_x < -4)
                                    {
                                        spd_x = -4;
                                    }
                                }
                            }
                        }
                        if (spd_x != 0)
                        {
                            spd_y = 0;
                        }
                        break;
                    case 11:
                    case 12:
                        dir_y = -1;
                        if (idc->sub_etat == 11)
                        {
                            dir_y = 1;
                        }
                        if (spd_x == 0)
                        {
                            if (spd_y > 0)
                            {
                                spd_y = speed + dir_y;
                                if (spd_y > 4)
                                {
                                    spd_y = 4;
                                }
                                if (spd_y < 2)
                                {
                                    spd_y = 2;
                                }
                            }
                            else
                            {
                                if (spd_y < 0)
                                {
                                    neg_speed = -speed;
                                    spd_y = dir_y + neg_speed;
                                    if (spd_y > -2)
                                    {
                                        spd_y = -2;
                                    }
                                    if (spd_y < -4)
                                    {
                                        spd_y = -4;
                                    }
                                }
                            }
                        }
                        if (spd_y != 0)
                        {
                            spd_x = 0;
                        }
                        break;
                    case 4:
                        if (spd_x == 0)
                        {
                            spd_x = speed;
                            spd_y = 0;
                        }
                        else if (spd_y == 0)
                        {
                            spd_x = 0;
                            spd_y = -speed;
                        }
                        break;
                    case 5:
                        if (spd_x == 0)
                        {
                        case 0:
                            spd_x = speed;
                            spd_y = 0;
                        }
                        else if (spd_y == 0)
                        {
                            spd_x = 0;
                            spd_y = speed;
                        }
                        break;
                    case 6:
                        if (spd_x == 0)
                        {
                            spd_x = -speed;
                            spd_y = 0;
                        }
                        else if (spd_y == 0)
                        {
                        case 3:
                            spd_x = 0;
                            spd_y = -speed;
                        }
                        break;
                    case 7:
                        if (spd_x == 0)
                        {
                        case 2:
                            spd_x = -speed;
                            spd_y = 0;
                        }
                        else if (spd_y == 0)
                        {
                        case 1:
                            spd_x = 0;
                            spd_y = speed;
                        }
                        break;
                    }
                    ufo_idc_obj->speed_x = spd_x;
                    ufo_idc_obj->speed_y = spd_y;
                    return;
                }
            }
            i++;
            idc = &level.objects[actobj.objects[i]];
        }
    }
}

/* 74E40 80199640 -O2 -msoft-float */
void DO_IDC_COMMAND(Obj *idc_obj)
{
    switch (idc_obj->sub_etat)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        idc_obj->display_prio = 4;
        idc_obj->flags &= ~FLG(OBJ_FLIP_X);
        break;
    default:
        idc_obj->display_prio = 0;
        break;
    }
}

/* 74E80 80199680 -O2 -msoft-float */
void DO_LEV_POING_COLLISION(Obj *lev_obj)
{
    Obj *idc_obj;

    if (lev_obj->main_etat == 5 && lev_obj->sub_etat == 53)
    {
        PlaySnd(235, lev_obj->id);
        set_main_and_sub_etat(lev_obj, 5, 54);
        idc_obj = &level.objects[link_init[lev_obj->id]];
        if (idc_obj->type == TYPE_INDICATOR)
        {
            switch (idc_obj->sub_etat)
            {
            case 0:
                set_sub_etat(idc_obj, 1);
                return;
            case 1:
                set_sub_etat(idc_obj, 2);
                return;
            case 2:
                set_sub_etat(idc_obj, 3);
                return;
            case 3:
                set_sub_etat(idc_obj, 0);
                break;
            }
        }
    }
}

/* 74F98 80199798 -O2 -msoft-float */
void START_UFO(Obj *ufo_idc_obj)
{
    if (ufo_idc_obj->main_etat == 0 && ufo_idc_obj->sub_etat == 13)
    {
        set_main_and_sub_etat(ufo_idc_obj, 0, 14);
        ufo_idc_obj->speed_x = 2;
        ufo_idc_obj->speed_y = 0;
    }
}
