#include "obj/explosion.h"

/* 3A9EC 8015F1EC -O2 -msoft-float */
Obj *allocateExplosion(Obj *unk_obj)
{
    Obj *res = null;
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_EXPLOSION && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            set_main_and_sub_etat(cur_obj, 0, 0);
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            cur_obj->x_pos = unk_obj->x_pos + unk_obj->offset_bx - cur_obj->offset_bx;
            cur_obj->y_pos = unk_obj->y_pos + unk_obj->offset_by - cur_obj->offset_by + 10;
            calc_obj_pos_map(cur_obj);
            cur_obj->anim_index = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].anim_index;
            cur_obj->anim_frame = 0;
            cur_obj->change_anim_mode = ANIMMODE_RESET;
            res = cur_obj;
            break;
        }
        cur_obj++;
        i++;
    }
    return res;
}

/* 3AB20 8015F320 -O2 -msoft-float */
void BombExplosion(Obj *obj)
{
    allocateExplosion(obj);
    obj->flags &= ~FLG(OBJ_ACTIVE);
    obj->flags &= ~FLG(OBJ_ALIVE);
}
