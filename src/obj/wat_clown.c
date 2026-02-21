#include "obj/wat_clown.h"

/* 39DC8 8015E5C8 -O2 -msoft-float */
void allocatedrop(Obj *watc_obj)
{
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_DROP && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            set_main_and_sub_etat(cur_obj, 2, 0);
            cur_obj->flags = cur_obj->flags & ~FLG(OBJ_FLIP_X) | watc_obj->flags & FLG(OBJ_FLIP_X);
            cur_obj->speed_y = -2;
            if (!(cur_obj->flags & FLG(OBJ_FLIP_X)))
                cur_obj->speed_x = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_left;
            else
                cur_obj->speed_x = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_right;

            cur_obj->x_pos = (watc_obj->x_pos + watc_obj->offset_bx) - cur_obj->offset_bx;
            cur_obj->y_pos = watc_obj->y_pos - 25;
            cur_obj->init_x_pos = cur_obj->x_pos;
            cur_obj->init_y_pos = cur_obj->y_pos;
            cur_obj->gravity_value_2 = 12;
            skipToLabel(cur_obj, cur_obj->flags >> OBJ_FLIP_X & 1, true);
            calc_obj_pos_map(cur_obj);
            cur_obj->flags &= ~FLG(OBJ_FLAG_9);
            cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
            break;
        }
        cur_obj++;
        i++;
    }
}

/* 39F74 8015E774 -O2 -msoft-float */
void DO_WAT_CLOWN_ATTAK(Obj *obj)
{
    /* dunno how to only do obj->main_etat == 0 check once, if possible */
    if (obj->main_etat == 0 && obj->sub_etat == 2)
        obj->field24_0x3e = 0;
    else if (obj->main_etat == 0 && obj->sub_etat == 11 && obj->field24_0x3e == 0)
    {
        obj->field24_0x3e = 1;
        allocatedrop(obj);
    }
    else if (obj->main_etat == 0 && obj->sub_etat == 22)
        skipToLabel(obj, 6, true);
}
