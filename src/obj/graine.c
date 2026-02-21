#include "obj/graine.h"

/* 398E8 8015E0E8 -O2 -msoft-float */
void DO_TARZAN(Obj *tz_obj)
{
    s16 i;
    Obj *cur_obj;
    s16 nb_objs;

    DO_ONE_CMD(tz_obj);
    if (tz_obj->main_etat == 0 && tz_obj->sub_etat == 4)
    {
        Vignet_To_Display = 1;
        i = 0;
        cur_obj = &level.objects[i];
        nb_objs = level.nb_objects;
        while (i < nb_objs)
        {
            if ((cur_obj->type == TYPE_GRAINE) && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
            {
                cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                set_main_and_sub_etat(cur_obj, 2, 2);
                cur_obj->x_pos = tz_obj->x_pos + tz_obj->offset_bx + cur_obj->offset_bx;
                cur_obj->y_pos = tz_obj->y_pos + 50;
                cur_obj->speed_y = -2;
                cur_obj->speed_x = 1;
                calc_obj_pos_map(cur_obj);
                set_sub_etat(tz_obj, 3);
                tz_obj->speed_y = -8;
                break;
            }
            cur_obj++;
            i++;
        }
    }
}

/* 39A14 8015E214 -O2 -msoft-float */
Obj *oldest_planted(void)
{
    s16 ng_ids[2];
    s16 unk_1;
    u8 cnt_2 = 0;
    s16 cnt_1 = 0;
    Obj *cur_obj = &level.objects[0];
    s16 nb_objs = level.nb_objects;

    while (cnt_1 < nb_objs)
    {
        if (cur_obj->type == TYPE_NEN_GRAINE)
        {
            ng_ids[cnt_2++] = cur_obj->id;
            if (!(cur_obj->flags & FLG(OBJ_ACTIVE)))
                cur_obj->iframes_timer = 10;
            else
                cur_obj->iframes_timer++;

            if (cnt_2 >= LEN(ng_ids))
                break;
        }
        cur_obj++;
        cnt_1++;
    }

    cnt_2 = 0;
    unk_1 = ng_ids[cnt_2];
    cur_obj = &level.objects[unk_1];
    cnt_1 = unk_1;
    while (cnt_2 < LEN(ng_ids))
    {
        if (level.objects[cnt_1].iframes_timer > level.objects[unk_1].iframes_timer)
        {
            unk_1 = cnt_1;
            cur_obj = &level.objects[unk_1];
        }
        cnt_2++;
        cnt_1 = ng_ids[cnt_2];
    }

    cur_obj->iframes_timer = 1;
    return cur_obj;
}

/* 39B90 8015E390 -O2 -msoft-float */
void DO_GROWING_PLATFORM(void)
{
    Obj *oldest_obj;
    u8 main_etat; u8 sub_etat;

    if (D_801CF408 != true)
        D_801CF408 = false;

    if (ray.anim_frame == ray.animations[ray.anim_index].frames_count - 1)
    {
        if (D_801CF408 == false)
        {
            oldest_obj = oldest_planted();
            if (oldest_obj->flags & FLG(OBJ_ACTIVE))
                DO_NOVA(oldest_obj);

            oldest_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            main_etat = 0;
            sub_etat = 38;
            set_main_and_sub_etat(oldest_obj, main_etat, sub_etat);
            oldest_obj->anim_frame = 0;
            oldest_obj->anim_index = oldest_obj->eta[main_etat][sub_etat].anim_index;
            oldest_obj->x_pos = (ray.x_pos + ray.offset_bx) - oldest_obj->offset_bx;
            oldest_obj->y_pos = (ray.y_pos + ray.offset_by) - oldest_obj->offset_by;
            calc_obj_pos_map(oldest_obj);
            D_801CF408 = true;
        }
    }
    else
        D_801CF408 = false;
}
