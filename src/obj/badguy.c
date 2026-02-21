#include "obj/badguy.h"

/* 3A868 8015F068 -O2 -msoft-float */
void allocate_badguy(Obj *genbg_obj, s16 param_2, s16 spd_x, s16 spd_y)
{
    s16 i = 0;
    Obj *cur_obj = level.objects;
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (
            (
                (cur_obj->type == TYPE_BADGUY1 && param_2 == 1) ||
                (cur_obj->type == TYPE_BADGUY2 && param_2 == 2)
            ) &&
            cur_obj->init_x_pos < 1 && !(cur_obj->flags & FLG(OBJ_ACTIVE))
        )
        {
            cur_obj->flags &= ~FLG(OBJ_FLAG_9);
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            cur_obj->active_timer = 0;
            set_main_and_sub_etat(cur_obj, 2, 2);
            cur_obj->active_flag = ACTIVE_DEAD;
            cur_obj->x_pos = genbg_obj->x_pos + genbg_obj->offset_bx - cur_obj->offset_bx;
            cur_obj->y_pos = genbg_obj->y_pos - (cur_obj->offset_by >> 2);
            calc_obj_dir(cur_obj);
            cur_obj->speed_y = spd_y;
            if ((cur_obj->flags & FLG(OBJ_FLIP_X)))
                cur_obj->speed_x = spd_x;
            else
                cur_obj->speed_x = -spd_x;
            calc_obj_pos_map(cur_obj);
            cur_obj->flags &= ~FLG(OBJ_READ_CMDS);
            break;
        }
        cur_obj++;
        i++;
    }
}
