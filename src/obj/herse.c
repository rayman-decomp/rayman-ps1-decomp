#include "obj/herse.h"

/* 4ED80 80173580 -O2 -msoft-float */
void allocateOtherPosts(Obj *her_bh_obj)
{
    Obj *cur_obj;
    s32 unk_1;
    s16 cur_id = link_init[her_bh_obj->id];
    u8 her_bh_frames = her_bh_obj->animations[
        her_bh_obj->eta[her_bh_obj->main_etat][her_bh_obj->sub_etat].anim_index
    ].frames_count;
    s16 i = 0;

    while (cur_id != her_bh_obj->id)
    {
        i++;
        cur_obj = &level.objects[cur_id];
        cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
        cur_obj->anim_frame = (her_bh_obj->anim_frame + i) % her_bh_frames;
        cur_obj->init_x_pos = her_bh_obj->init_x_pos + i * ((her_bh_obj->hit_points - 2) << 5);
        cur_obj->init_y_pos = her_bh_obj->init_y_pos;
        unk_1 = i << 8;
        cur_obj->field23_0x3c = her_bh_obj->field23_0x3c - unk_1;
        cur_obj->x_pos = cur_obj->init_x_pos;
        cur_obj->y_pos = cur_obj->init_y_pos;
        calc_obj_pos_map(her_bh_obj);
        cur_id = link_init[cur_id];
    }
}

/* 4EF0C 8017370C -O2 -msoft-float */
void doHerseCommand(Obj *obj)
{
    if (
        (obj->type == TYPE_HERSE_BAS || obj->type == TYPE_HERSE_HAUT) &&
        obj->field24_0x3e == 0
    )
    {
        obj->anim_frame = myRand(obj->animations[obj->anim_index].frames_count - 1);
        obj->field23_0x3c = 0x1000;
        allocateOtherPosts(obj);
        obj->field24_0x3e = 1;
    }
    else
    {
        obj->speed_y = sinYspeed(obj, 24, 40, &obj->field23_0x3c);
        obj->speed_x = 0;
    }
}
