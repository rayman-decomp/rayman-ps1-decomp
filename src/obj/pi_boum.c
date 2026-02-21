#include "obj/pi_boum.h"

/* 3A27C 8015EA7C -O2 -msoft-float */
void allocateEclatPS(Obj *in_obj, s16 param_2)
{
    s16 spd_x;
    s16 i;
    Obj *cur_obj;
    s16 nb_objs;

    switch (param_2)
    {
    case 7:
        spd_x = -3;
        break;
    case 8:
        spd_x = 2;
        break;
    case 9:
        spd_x = -1;
        break;
    }
    i = 0;
    cur_obj = &level.objects[i];
    nb_objs = level.nb_objects;
    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_PI_BOUM && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            set_main_and_sub_etat(cur_obj, 2, param_2);
            cur_obj->speed_x = spd_x;
            cur_obj->speed_y = -6;
            cur_obj->x_pos = in_obj->x_pos;
            cur_obj->y_pos = in_obj->y_pos;
            skipToLabel(cur_obj, 1, true);
            calc_obj_pos_map(cur_obj);
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            cur_obj->flags &= ~FLG(OBJ_FLAG_9);
            cur_obj->gravity_value_1 = 0;
            cur_obj->gravity_value_2 = 5;
            break;
        }
        cur_obj++;
        i++;
    }
}

/* 3A3E0 8015EBE0 -O2 -msoft-float */
void DO_PI_EXPLOSION(Obj *pi_obj)
{
    s16 i;
    Obj *first_pi_b;
    s16 nb_objs;
    Obj *after_pi_b;
    s16 j;
    Obj *cur_pi_b;
    s16 pi_x; s16 pi_y; s16 pi_w; s16 pi_h;    

    PlaySnd_old(84);
    i = 0;
    first_pi_b = &level.objects[i];
    nb_objs = level.nb_objects;
    while (i < nb_objs)
    {
        if (first_pi_b->type == TYPE_PI_BOUM)
        {
            after_pi_b = first_pi_b;
            do
            {
                after_pi_b++;
            } while (after_pi_b->type == TYPE_PI_BOUM);
            break;
        }
        i++;
        first_pi_b++;
    }

    if (first_pi_b->type == TYPE_PI_BOUM)
    {
        j = 0;
        while (j < 5)
        {
            cur_pi_b = first_pi_b;
            if (cur_pi_b <= after_pi_b)
            {
                while (cur_pi_b <= after_pi_b) /* almost off-by-one error, if it weren't for the j loop? */
                {
                    if (!(cur_pi_b->flags & FLG(OBJ_ACTIVE)))
                        break;

                    cur_pi_b++;
                }

                if (cur_pi_b <= after_pi_b)
                {
                    set_main_and_sub_etat(cur_pi_b, 2, j);
                    cur_pi_b->flags &= ~FLG(OBJ_FLIP_X);
                    switch (j)
                    {
                    case 0:
                        cur_pi_b->speed_y = 0;
                        cur_pi_b->speed_x = 4;
                        break;
                    case 1:
                        cur_pi_b->speed_y = 0;
                        cur_pi_b->speed_x = -2;
                        break;
                    case 2:
                        cur_pi_b->speed_y = -4;
                        cur_pi_b->speed_x = -4;
                        break;
                    case 3:
                        cur_pi_b->speed_y = -4;
                        cur_pi_b->speed_x = 2;
                        break;
                    case 4:
                        cur_pi_b->speed_y = -6;
                        cur_pi_b->speed_x = -1;
                        break;
                    }
                    GET_SPRITE_POS(pi_obj, j, &pi_x, &pi_y, &pi_w, &pi_h);
                    cur_pi_b->x_pos = pi_x;
                    cur_pi_b->y_pos = pi_y;
                    skipToLabel(cur_pi_b, 1, true);
                    calc_obj_pos_map(cur_pi_b);
                    cur_pi_b->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                }
            }
            j++;
        }
    }
}
const u8 rodata_DO_PI_EXPLOSION[4] = {};
