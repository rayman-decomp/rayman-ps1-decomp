#include "obj/clown_tnt.h"

/* 3A610 8015EE10 -O2 -msoft-float */
void DO_CLOWN_TNT_ATTACK(Obj *ct_obj)
{
    s16 spr_x; s16 spr_y; s16 spr_w; s16 spr_h;
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_TNT_BOMB && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            set_main_and_sub_etat(cur_obj, 2, 0);
            cur_obj->flags = (cur_obj->flags & ~FLG(OBJ_FLIP_X)) | (ct_obj->flags & FLG(OBJ_FLIP_X));
            if (ct_obj->type == TYPE_CLOWN_TNT)
            {
                cur_obj->speed_y = 1;
                if (ray.speed_x < 2)
                    cur_obj->speed_x = 0;
                else if (cur_obj->flags & FLG(OBJ_FLIP_X))
                    cur_obj->speed_x = 1;
                else
                    cur_obj->speed_x = -1;
            }
            else
            {
                cur_obj->speed_y = 0;
                if (!(cur_obj->flags & FLG(OBJ_FLIP_X)))
                    cur_obj->speed_x = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_left;
                else
                    cur_obj->speed_x = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_right;
            }

            if (ct_obj->type == TYPE_CLOWN_TNT)
                GET_SPRITE_POS(ct_obj, 6, &spr_x, &spr_y, &spr_w, &spr_h);
            else
            {
                GET_SPRITE_POS(ct_obj, 9, &spr_x, &spr_y, &spr_w, &spr_h);
                spr_w = 16;
                spr_y += 32;
                spr_x += 16;
            }

            cur_obj->x_pos = spr_x - cur_obj->offset_bx + (spr_w >> 1);
            cur_obj->y_pos = spr_y - cur_obj->offset_hy;
            cur_obj->init_x_pos = cur_obj->x_pos;
            cur_obj->init_y_pos = cur_obj->y_pos;
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            cur_obj->anim_frame = 0;
            calc_obj_pos_map(ct_obj);
            break;
        }
        cur_obj++;
        i++;
    }
}
