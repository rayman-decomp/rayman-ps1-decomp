#include "obj/eclair_command.h"

/* 4C978 80171178 -O2 -msoft-float */
void DO_ECLAIR_COMMAND(Obj *ecl_obj)
{
    s16 i;
    Obj *cur_obj;
    s16 nb_objs;

    switch (ecl_obj->cmd)
    {
    case GO_LEFT:
        ecl_obj->flags &= ~FLG(OBJ_FLIP_X);
    case GO_RIGHT:
        if (ecl_obj->cmd == GO_RIGHT)
            ecl_obj->flags |= FLG(OBJ_FLIP_X);

        SET_X_SPEED(ecl_obj);
        ecl_obj->speed_y = 0;
        if (
            block_flags[
                mp.map[
                    (s16) (((ecl_obj->x_pos + ecl_obj->offset_bx) >> 4) +
                    mp.width * ((ecl_obj->y_pos + ecl_obj->offset_by) >> 4))
                ] >> 10
            ] >> BLOCK_CH_DIR & 1
        )
        {
            i = 0;
            cur_obj = &level.objects[i];
            nb_objs = level.nb_objects;
            while (i < nb_objs)
            {
                if (cur_obj->type == TYPE_BB1_PLAT && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
                {
                    cur_obj->flags &= ~FLG(OBJ_FLIP_X);
                    cur_obj->speed_y = 0;
                    cur_obj->speed_x = 0;
                    cur_obj->x_pos = ecl_obj->x_pos - 32;
                    cur_obj->y_pos = ecl_obj->y_pos - 48;
                    cur_obj->init_x_pos = cur_obj->x_pos;
                    cur_obj->init_y_pos = cur_obj->y_pos;
                    calc_obj_pos_map(cur_obj);
                    cur_obj->iframes_timer = 0x00FF;
                    cur_obj->field23_0x3c = 0x001E;
                    cur_obj->field24_0x3e = 0x001E;
                    cur_obj->main_etat = 0;
                    cur_obj->sub_etat = 4;
                    cur_obj->anim_frame = 0;
                    cur_obj->cmd_offset = -1;
                    cur_obj->nb_cmd = 0;
                    cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                    break;
                }
                cur_obj++;
                i++;
            }

            ecl_obj->flags &= ~FLG(OBJ_ACTIVE);
            ecl_obj->flags &= ~FLG(OBJ_ALIVE);
        }
    }
}