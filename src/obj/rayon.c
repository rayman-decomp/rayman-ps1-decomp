#include "obj/rayon.h"

/* 3EFC4 801637C4 -O2 -msoft-float */
void allocatePaillette(Obj *ray_obj)
{
    Obj *found_obj = null;
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_RAYON && !(cur_obj->flags & 0x800))
        {
            found_obj = cur_obj;
            break;
        }
        i++;
        cur_obj++;
    }

    if (!found_obj)
        found_obj = findfirstObject(TYPE_RAYON);

    found_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
    found_obj->flags &= ~FLG(OBJ_FLAG_9);
    found_obj->active_timer = 0;
    found_obj->x_pos = ray_obj->x_pos - 40;
    found_obj->y_pos = ray_obj->y_pos - 20;
    found_obj->anim_index = 0;
    found_obj->anim_frame = 1;
    found_obj->main_etat = 0;
    found_obj->init_main_etat = 0;
    found_obj->init_sub_etat = 0;
    found_obj->sub_etat = 0;
    calc_obj_pos_map(found_obj);
}
