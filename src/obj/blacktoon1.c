#include "obj/blacktoon1.h"

/* 67130 8018B930 -O2 -msoft-float */
void allocateBlacktoonEyes(Obj *bt1_obj)
{
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_BLACKTOON_EYES && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj->anim_frame = 0;
            cur_obj->x_pos = bt1_obj->x_pos;
            cur_obj->y_pos = bt1_obj->y_pos;
            cur_obj->speed_y = 0;
            cur_obj->speed_x = 0;
            set_main_and_sub_etat(cur_obj, cur_obj->init_main_etat, cur_obj->init_sub_etat);
            calc_obj_pos_map(cur_obj);
            calc_obj_dir(cur_obj);
            cur_obj->cmd_offset = -1;
            cur_obj->nb_cmd = 0;
            cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
            cur_obj->flags &= ~FLG(OBJ_FLAG_9);
            break;
        }
        cur_obj++;
        i++;
    }
}

/* 6721C 8018BA1C -O2 -msoft-float */
void DO_BLK_SPEED_COMMAND(Obj *obj)
{
    s16 cen_x; s16 cen_y;

    if (obj->field56_0x69 & 4)
    {
        cen_x = get_center_x(obj);
        cen_y = get_center_y(obj);
        if (on_block_chdir(obj, cen_x, cen_y) && test_allowed(obj, cen_x, cen_y))
            skipToLabel(obj, 99, true);

        obj->speed_x = obj->iframes_timer;
        obj->speed_y = obj->field20_0x36;
        if (obj->speed_x > 0)
            obj->flags |= FLG(OBJ_FLIP_X);
        else if (obj->speed_x < 0)
            obj->flags &= ~FLG(OBJ_FLIP_X);
    }
    if (obj->field56_0x69 & 8)
    {
        obj->speed_x = obj->iframes_timer;
        obj->speed_y = obj->field20_0x36;
    }
}

/* 6732C 8018BB2C -O2 -msoft-float */
void DO_BLK_LR_COMMAND(Obj *obj)
{
    s16 cen_x; s16 cen_y;

    if ((obj->main_etat == 0) && (obj->sub_etat == 4))
    {
        SET_X_SPEED(obj);
        obj->speed_x = -obj->speed_x;
    }
    else
    {
        if (obj->cmd == GO_LEFT)
            obj->flags &= ~FLG(OBJ_FLIP_X);
        else
            obj->flags |= FLG(OBJ_FLIP_X);

        if (obj->field56_0x69 & 2)
        {
            SET_X_SPEED(obj);
            if (block_flags[calc_typ_travd(obj, false)] >> BLOCK_FULLY_SOLID & 1)
            {
                if (obj->cmd == GO_LEFT)
                    skipToLabel(obj, 3, true);
                else
                    skipToLabel(obj, 2, true);
            }
            CALC_MOV_ON_BLOC(obj);
        }
        if (obj->field56_0x69 & 1)
        {
            obj->speed_y = sinYspeed(obj, 48, 40, &obj->field20_0x36);
            cen_x = get_center_x(obj);
            cen_y = get_center_y(obj);
            if (on_block_chdir(obj, cen_x, cen_y) && test_allowed(obj, cen_x, cen_y))
            {
                obj->x_pos -= obj->speed_x;
                if (obj->cmd == GO_LEFT)
                {
                    skipToLabel(obj, 3, true);
                    obj->flags |= FLG(OBJ_FLIP_X);
                }
                else
                {
                    skipToLabel(obj, 2, true);
                    obj->flags &= ~FLG(OBJ_FLIP_X);
                }
            }
            SET_X_SPEED(obj);
        }
        if (obj->field56_0x69 & 0x10)
        {
            SET_X_SPEED(obj);
            obj->speed_y = 0;
        }
    }
}

/* 6753C 8018BD3C -O2 -msoft-float */
void DO_BLK_NOP_COMMAND(Obj *obj)
{
    if (
        obj->field56_0x69 & 0x10 &&
        (
            (obj->main_etat == 0 && obj->sub_etat == 2) ||
            (obj->main_etat == 2 && obj->sub_etat == 3)
        )
    )
    {
        if (obj->timer == 0xFF)
        {
            if (
                ((obj->y_pos + obj->speed_y <= obj->field23_0x3c) && obj->y_pos >= obj->field23_0x3c) ||
                obj->speed_y == 0
            )
                obj->timer = 60;
        }
        else if (obj->timer == 0)
        {
            set_main_and_sub_etat(obj, 2, 0);
            if (obj->flags & FLG(OBJ_FLIP_X))
                skipToLabel(obj, 3, true);
            else
                skipToLabel(obj, 2, true);

            obj->speed_y = 0;
        }
        else
        {
            obj->speed_y = 0;
            obj->timer--;
        }
    }

    if (
        (obj->follow_sprite == 4) &&
        (
            (obj->main_etat == 0 && obj->sub_etat == 2) ||
            (obj->main_etat == 2 && obj->sub_etat == 3)
        )
    )
    {
        if (obj->detect_zone_flag != 0)
        {
            if ((obj->y_pos + obj->speed_y <= obj->field23_0x3c) && obj->y_pos >= obj->field23_0x3c)
            {
                set_main_and_sub_etat(obj, 0, 3);
                obj->speed_y = 0;
            }
        }
        else
            set_main_and_sub_etat(obj, 2, 1);
    }

    if (
        obj->field56_0x69 & 2 && obj->speed_x != 0 &&
        block_flags[calc_typ_travd(obj, false)] >> BLOCK_FULLY_SOLID & 1
    )
    {
        if (obj->cmd == GO_LEFT)
            skipToLabel(obj, 3, true);
        else
            skipToLabel(obj, 2, true);
    }
}

/* 71A0 8012B9A0 -O2 -msoft-float */
void DO_BLKTOON_COMMAND(Obj *obj)
{
    switch (obj->cmd)
    {
    case GO_SPEED:
        DO_BLK_SPEED_COMMAND(obj);
        break;
    case GO_LEFT:
    case GO_RIGHT:
        DO_BLK_LR_COMMAND(obj);
        break;
    case GO_NOP:
        DO_BLK_NOP_COMMAND(obj);
    case GO_WAIT:
    default:
        break;
    }
}
