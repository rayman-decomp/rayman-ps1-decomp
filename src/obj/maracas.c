#include "obj/maracas.h"

/* 3AB5C 8015F35C -O2 */
void MARACAS_GO(Obj *in_obj)
{
    ObjFlags cur_obj_not_flip;
    ObjFlags in_obj_get_flip;
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if ((cur_obj->type == TYPE_MARACAS_BAS) && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj_not_flip = ~FLG(OBJ_FLIP_X);
            cur_obj_not_flip &= cur_obj->flags;
            in_obj_get_flip = in_obj->flags & FLG(OBJ_FLIP_X);
            cur_obj->flags = cur_obj_not_flip | in_obj_get_flip;

            cur_obj->speed_y = 0;
            cur_obj->speed_x = 0;
            cur_obj->x_pos = in_obj->x_pos;
            cur_obj->y_pos = in_obj->y_pos;
            calc_obj_pos_map(cur_obj);
            cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
            cur_obj->gravity_value_1 = 0;
            cur_obj->gravity_value_2 = 7;
            break;
        }
        cur_obj++;
        i++;
    }

    skipToLabel(in_obj, 99, true);
    if (in_obj->cmd == GO_SPEED)
    {
        in_obj->speed_x = cur_obj->iframes_timer;
        in_obj->speed_y = cur_obj->field20_0x36;
    }
    set_main_and_sub_etat(in_obj, 0, 12);
}