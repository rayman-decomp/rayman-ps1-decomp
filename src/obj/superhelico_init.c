#include "obj/superhelico_init.h"

/* 3EECC 801636CC -O2 */
void allocateSupHelico(Obj *mus_obj)
{
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_SUPERHELICO && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            cur_obj->x_pos = mus_obj->x_pos;
            cur_obj->y_pos = mus_obj->y_pos;
            set_main_and_sub_etat(cur_obj, 2, 18);
            cur_obj->screen_x_pos = cur_obj->x_pos - xmap;
            cur_obj->screen_y_pos = cur_obj->y_pos - ymap;
            cur_obj->speed_y = -2;
            cur_obj->speed_x = 1;
            calc_obj_pos_map(cur_obj);
            break;
        }
        cur_obj++;
        i++;
    }
}