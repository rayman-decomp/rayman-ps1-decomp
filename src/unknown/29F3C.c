#include "unknown/29F3C.h"

/* 29F3C 8014E73C -O2 -msoft-float */
void allocateLandingSmoke(Obj *in_obj)
{
    s16 i;
    s16 j;
    Obj *cur_obj;
    s16 nb_objs;

    for (i = 0; i <= 2; i += 2)
    {
        cur_obj = &level.objects[0];
        nb_objs = level.nb_objects;
        j = 0;
        while (j < nb_objs)
        {
            if (cur_obj->type == TYPE_LANDING_SMOKE && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
            {
                cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                cur_obj->active_timer = 0;
                cur_obj->active_flag = ACTIVE_ALIVE;
                set_main_and_sub_etat(cur_obj, 0, i != 0);
                cur_obj->x_pos = in_obj->x_pos + in_obj->offset_bx - cur_obj->offset_bx;
                cur_obj->y_pos = in_obj->y_pos + in_obj->offset_by - cur_obj->offset_by;
                if (i != 0)
                    cur_obj->display_prio = 2;
                else
                    cur_obj->display_prio = 7;
                calc_obj_pos_map(cur_obj);
                break;
            }
            cur_obj++;
            j++;
        }
    }
}
