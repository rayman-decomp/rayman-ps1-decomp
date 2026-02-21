#include "obj/fish.h"

#ifdef BSS_DEFS
s16 PS1_SplashAlwaysObjects[12];
u8 PS1_SplashAlwaysObjectsCount;
#endif

/* 37A9C 8015C29C -O2 -msoft-float */
void allocate_splash(Obj *base_obj)
{
    s16 y;
    s16 i;
    Obj *cur_obj;
    s16 offset_by;
    s32 height;

    i = 0;
    while (i < PS1_SplashAlwaysObjectsCount)
    {
        cur_obj = &level.objects[PS1_SplashAlwaysObjects[i]];
        if (!(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj->flags |= FLG(OBJ_ALIVE);
            make_active(cur_obj, false);
            cur_obj->x_pos = base_obj->offset_bx + base_obj->x_pos - cur_obj->offset_bx;
            if (base_obj->btypes[0] == BTYP_WATER)
                y = base_obj->offset_by + base_obj->y_pos - cur_obj->offset_by;
            else
            {
                if (!(block_flags[base_obj->btypes[0]] >> BLOCK_SOLID & 1))
                {
                    offset_by = cur_obj->offset_by;
                    height = (*(u16 *) &mp.height - 1) * 16;
                }
                else
                {
                    height = (*(u16 *) &mp.height - 1) * 16;
                    offset_by = cur_obj->offset_by - 10;
                }
                y = height - offset_by;
            }
            cur_obj->y_pos = y;
            calc_obj_pos_map(cur_obj);
            set_main_and_sub_etat(cur_obj, 0, 0);
            cur_obj->anim_frame = 0;
            base_obj->flags |= FLG(OBJ_FLAG_9); /* bad disassembly */
            break;
        }
        i++;
    }
}

/* 37C18 8015C418 -O2 */
u8 can_free_fish(Obj *fish_obj)
{
    u8 res = true;
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    u8 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (
            cur_obj->type == TYPE_FISH &&
            cur_obj->init_x_pos == fish_obj->init_x_pos &&
            cur_obj->flags & FLG(OBJ_ACTIVE) &&
            cur_obj->timer < 100
        )
        {
            res = false;
            break;
        }
        i++;
        cur_obj++;
    }
    return res;
}

/* 37CB8 8015C4B8 -O2 -msoft-float */
void DESACTIVE_FISH_COLLIS(Obj *fish_obj)
{
    u8 index = link_init[fish_obj->id];
    Obj *unk_obj = &level.objects[index];

    if (unk_obj->y_pos == fish_obj->y_pos)
    {
        unk_obj->y_pos = ymap + SCREEN_HEIGHT;
        unk_obj->flags &= ~FLG(OBJ_ALIVE);
        unk_obj->flags &= ~FLG(OBJ_ACTIVE);
    }

    index = link_init[unk_obj->id];
    unk_obj = &level.objects[index];
    if (unk_obj->y_pos == fish_obj->y_pos)
    {
        unk_obj->flags &= ~FLG(OBJ_ACTIVE);
        unk_obj->y_pos = ymap + SCREEN_HEIGHT;
        unk_obj->flags &= ~FLG(OBJ_ALIVE);
    }
}

/* 37DA4 8015C5A4 -O2 -msoft-float */
void DO_PYRANHA(Obj *in_obj)
{
    u8 can_free;
    s32 in_y_pos;
    s32 in_y;
    Obj *cur_obj;
    s16 i;
    u8 nb_obj;

    DO_ONE_CMD(in_obj);
    can_free = false;
    if (in_obj->main_etat == 0)
    {
        if (in_obj->y_pos + in_obj->offset_by + 20 < ymap + SCREEN_HEIGHT)
            in_obj->timer++;
        if (in_obj->sub_etat == 3)
            in_obj->speed_y = 0;
        else if (in_obj->sub_etat == 9)
        {
            in_y_pos = in_obj->y_pos;
            in_y = in_obj->y_pos + in_obj->offset_hy;
            in_obj->speed_y = 6;
            if (
                ymap + SCREEN_HEIGHT < in_y ||
                in_y_pos + in_obj->offset_by + 14 > mp.height * 16
            )
            {
                if (in_y_pos + in_obj->offset_by + 14 > mp.height * 16)
                    allocate_splash(in_obj);
                in_obj->timer = 0;
                in_obj->flags &= ~FLG(OBJ_ACTIVE);
                in_obj->y_pos = ymap + SCREEN_HEIGHT;
                in_obj->flags &= ~FLG(OBJ_ALIVE);
                can_free = can_free_fish(in_obj);
            }
        }
        else if (in_obj->y_pos + in_obj->offset_by < ymap)
        {
            in_obj->flags &= ~FLG(OBJ_ACTIVE);
            in_obj->y_pos = ymap + SCREEN_HEIGHT;
            in_obj->flags &= ~FLG(OBJ_ALIVE);
            can_free = can_free_fish(in_obj);
        }
    }
    if (in_obj->timer == 100)
        can_free = can_free_fish(in_obj);
    if (can_free)
    {
        cur_obj = level.objects;
        nb_obj = level.nb_objects;
        for (i = 0; nb_obj > i; i++)
        {
            if (
                cur_obj->type == TYPE_FISH &&
                cur_obj->init_x_pos == in_obj->init_x_pos &&
                !(cur_obj->flags & FLG(OBJ_ACTIVE))
            )
            {
                cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                cur_obj->y_pos = ymap + SCREEN_HEIGHT;
                cur_obj->x_pos = in_obj->init_x_pos;
                if (cur_obj->y_pos + cur_obj->offset_by > ((mp.height - 1) << 4))
                {
                    cur_obj->y_pos = -cur_obj->offset_by + ((mp.height - 1) << 4);
                    allocate_splash(cur_obj);
                }
                cur_obj->main_etat = in_obj->init_main_etat;
                cur_obj->sub_etat = in_obj->init_sub_etat;
                cur_obj->hit_points = in_obj->init_hit_points;
                cur_obj->timer = 0;
                cur_obj->flags |= FLG(OBJ_READ_CMDS);
                calc_obj_pos_map(cur_obj);
                skipToLabel(cur_obj, 1, true);
                break;
            }
            cur_obj++;
        }
    }
}