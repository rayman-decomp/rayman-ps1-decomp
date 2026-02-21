#include "obj/hybride_stosko.h"

/* 75600 80199E00 -O2 -msoft-float */
void allocateStoskoClaw(Obj *stsk_obj)
{
    Obj *cur_obj;
    s16 i;
    s16 nb_objs;

    stsk_obj->field24_0x3e = -1;
    cur_obj = level.objects;
    i = 0;
    nb_objs = level.nb_objects;
    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_STOSKO_PINCE && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj->x_pos = stsk_obj->x_pos;
            cur_obj->y_pos = stsk_obj->y_pos;
            cur_obj->speed_x = 0;
            calc_obj_pos_map(cur_obj);
            cur_obj->cmd_offset = -1;
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            cur_obj->nb_cmd = 0;
            stsk_obj->field24_0x3e = i;
            break;
        }
        cur_obj++;
        i++;
    }
}

/* 756DC 80199EDC -O2 -msoft-float */
void doSTOSKOcommand(Obj *stsk_obj)
{
    u8 main_etat; u8 sub_etat;
    Obj *unk_obj;

    scrollLocked = true;
    switch (stsk_obj->main_etat * 0x100 + stsk_obj->sub_etat)
    {
    case 0x100:
        if (stsk_obj->x_pos <= stsk_obj->init_x_pos)
        {
            set_main_and_sub_etat(stsk_obj, 0, 0);
            set_main_and_sub_etat(&ray, 0, 0);
            remoteRayXToReach = -32000;
        }
        else
        {
            remoteRayXToReach = scroll_start_x;
            if (ray.main_etat == 3 && ray.sub_etat == 20)
                ray.flags |= FLG(OBJ_FLIP_X);
        }
        SET_X_SPEED(stsk_obj);
        break;
    case 0x8:
        stsk_obj->speed_x = 0;
        stsk_obj->speed_y = -8;
        break;
    case 0x0:
        if (!(poing.is_active || ray.main_etat == 2))
        {
            if (stsk_obj->timer != 0)
                stsk_obj->timer--;
            else
                set_sub_etat(stsk_obj, 1);
        }
        else
            set_sub_etat(stsk_obj, 5);
        break;
    case 0x1:
        if (poing.is_active)
        {
            if (
                __builtin_abs((s16) (ray.y_pos + ray.offset_by - stsk_obj->y_pos - stsk_obj->offset_by)) < 48 ||
                stsk_obj->anim_frame >= 10
            )
            {
                main_etat = 0;
                sub_etat = 10;
                set_sub_etat(stsk_obj, sub_etat);
                stsk_obj->anim_index = stsk_obj->eta[main_etat][sub_etat].anim_index;
            }
            else
                set_sub_etat(stsk_obj, 5);
        }
        else
        {
            if (EOA(stsk_obj))
                allocateStoskoClaw(stsk_obj);
        }
        break;
    case 0x4:
        stsk_obj->timer = 50;
    case 0x2:
        unk_obj = &level.objects[stsk_obj->field24_0x3e];
        if (unk_obj->speed_x > 0 && unk_obj->x_pos >= stsk_obj->x_pos)
        {
            stsk_obj->field24_0x3e = -1;
            unk_obj->flags &= ~FLG(OBJ_ALIVE);
            set_sub_etat(stsk_obj, 3);
        }
        break;
    case 0xD:
        stsk_obj->timer = 50;
        break;
    case 0x3:
    case 0x7:
    case 0xC:
        stsk_obj->timer = 50;
        break;
    case 0xB:
        if (!poing.is_active)
            set_sub_etat(stsk_obj, 12);
        break;
    case 0x6:
        if (!(ray.main_etat == 2 || poing.is_active))
            set_sub_etat(stsk_obj, 7);
        break;
    case 0x5:
    case 0x9:
        break;
    }
}
