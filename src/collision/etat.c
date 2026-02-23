#include "collision/etat.h"

/* 22A98 80147298 -O2 -msoft-float */
s32 vblToEOA(Obj *obj, u8 factor)
{
    ObjState *eta = &obj->eta[obj->main_etat][obj->sub_etat];
    s32 anim_speed = eta->anim_speed & 15;
    s32 res =
        (s16) (obj->animations[eta->anim_index].frames_count *
        anim_speed * factor - horloge[anim_speed] + 1);
    MAX_2(res, 1);

    return res;
}

/* 22B30 80147330 -O2 -msoft-float */
void GET_ANIM_POS(Obj *obj, s16 *x, s16 *y, s16 *w, s16 *h)
{
    AnimationFrame *frame = &obj->animations[obj->anim_index].frames[obj->anim_frame];

    *w = frame->width;
    *h = frame->height;
    if (!(obj->flags & FLG(OBJ_FLIP_X)))
        *x = obj->x_pos + frame->x;
    else
        *x = obj->x_pos + obj->offset_bx * 2 - frame->x - *w;
    *y = obj->y_pos + frame->y;
}

/* 22BD4 801473D4 -O2 -msoft-float */
u8 PS1_GetObjPan(Obj *obj)
{
    return 0;
}

/* 22BDC 801473DC -O2 -msoft-float */
u8 PS1_GetObjVolume(Obj *obj)
{
    return 0;
}

/* 22BE4 801473E4 -O2 -msoft-float */
void add_actobj(s16 obj_id)
{
    s16 num = actobj.num_active_objects++;

    actobj.objects[num] = obj_id;
    actobj.objects[num + 1] = -1;
}

/* 22C24 80147424 -O2 -msoft-float */
s16 BTYP(s32 x, s32 y)
{
    return (u8) PS1_GetBTYPFromTilePos((s16) x >> 4, (s16) y >> 4);
}

/* 22C50 80147450 -O2 -msoft-float */
void set_sub_etat(Obj *obj, u8 sub_etat)
{
    obj->sub_etat = sub_etat;
    obj->change_anim_mode = ANIMMODE_RESET_IF_NEW;
}

/* 22C60 80147460 -O2 -msoft-float */
void set_main_etat(Obj *obj, u8 main_etat)
{
    obj->main_etat = main_etat;
    obj->change_anim_mode = ANIMMODE_RESET_IF_NEW;
}

/* 22C70 80147470 -O2 -msoft-float */
void set_main_and_sub_etat(Obj *obj, u8 main_etat, u8 sub_etat)
{
    obj->main_etat = main_etat;
    obj->sub_etat = sub_etat;
    obj->change_anim_mode = ANIMMODE_RESET_IF_NEW;
}
