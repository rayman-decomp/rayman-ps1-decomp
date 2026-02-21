#include "obj/falling_obj_command.h"

/* 5088C 8017508C -O2 */
void move_fruit_in_water(Obj *obj)
{
    s16 btyp;
    ObjFlags obj_flip_x;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s32 x2;

    obj_flip_x = obj->flags >> OBJ_FLIP_X & 1;
    if (obj->main_etat == 0)
    {
        if (obj->sub_etat == 0xd && ray.field20_0x36 == obj->id)
            set_main_and_sub_etat(obj, 0, 0xf);

        if (obj->main_etat == 0 && obj->sub_etat == 0xf)
        {
            if (obj->type == TYPE_FALLING_OBJ2 && ray.field20_0x36 == -1)
            {
                set_sub_etat(obj, 0xd);
                obj->speed_x = 0;
            }
            else if (ray.field20_0x36 == obj->id)
            {
                obj->flags = obj->flags & ~FLG(OBJ_FLIP_X) | ray.flags & FLG(OBJ_FLIP_X);
                SET_X_SPEED(obj);
                obj->flags = obj->flags & ~FLG(OBJ_FLIP_X) | obj_flip_x << OBJ_FLIP_X;
            }

            if (obj->speed_x != 0)
            {
                GET_ANIM_POS(obj, &x, &y, &w, &h);
                x2 = x;
                if (obj->speed_x > -1)
                    x2 += w;
                btyp = BTYP(x2, y + 0x10);
                if (block_flags[btyp] >> BLOCK_SOLID & 1)
                {
                    set_main_and_sub_etat(obj, 0, 0xd);
                    obj->speed_x = 0;
                }
            }
        }
    }
}

/* 50A30 80175230 -O2 */
void DO_FALLING_OBJ_CMD(Obj *obj)
{
    if (obj->main_etat == 2 && obj->btypes[0] == BTYP_WATER)
    {
        set_main_and_sub_etat(obj, 0, 0xe);
        obj->y_pos = (obj->offset_by + obj->y_pos & 0xfff0) - obj->offset_by + 7;
    }
    move_fruit_in_water(obj);
    DO_OBJ_COLLISIONS(obj, 10);
    if (obj->sub_etat == 9)
        REINIT_OBJECT(obj);
}