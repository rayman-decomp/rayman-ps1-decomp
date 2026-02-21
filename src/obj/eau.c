#include "obj/eau.h"

#ifdef BSS_DEFS
s16 eau_obj_id;
#endif

/* 4D908 80172108 -O2 -msoft-float */
void ACTIVE_L_EAU(Obj *eau_obj)
{
    s16 i;
    Obj *cur_obj;
    s16 nb_objs;

    eau_obj->field23_0x3c = 130;
    eau_obj->y_pos = ymapmax + 230;
    eau_obj->x_pos = xmap - eau_obj->offset_bx;
    i = 0;
    cur_obj = level.objects;
    nb_objs = level.nb_objects;
    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_EAU && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj->flags &= ~FLG(OBJ_FLIP_X);
            cur_obj->speed_y = 0;
            cur_obj->speed_x = 0;
            cur_obj->x_pos = eau_obj->x_pos + 101 * 1;
            cur_obj->y_pos = eau_obj->y_pos;
            calc_obj_pos_map(cur_obj);
            cur_obj->field23_0x3c = 130;
            cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
            cur_obj->sub_etat = 1;
            break;
        }
        cur_obj++;
        i++;
    }
    cur_obj++;
    cur_obj->flags &= ~FLG(OBJ_FLIP_X);
    cur_obj->speed_y = 0;
    cur_obj->speed_x = 0;
    cur_obj->x_pos = eau_obj->x_pos + 101 * 2;
    cur_obj->y_pos = eau_obj->y_pos;
    calc_obj_pos_map(cur_obj);
    cur_obj->field23_0x3c = 130;
    cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
    cur_obj->sub_etat = 2;

    cur_obj++;
    cur_obj->flags &= ~FLG(OBJ_FLIP_X);
    cur_obj->speed_y = 0;
    cur_obj->speed_x = 0;
    cur_obj->x_pos = eau_obj->x_pos + 101 * 3;
    cur_obj->y_pos = eau_obj->y_pos;
    calc_obj_pos_map(cur_obj);
    cur_obj->field23_0x3c = 130;
    cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
    cur_obj->sub_etat = 3;
}

/* 4DACC 801722CC -O2 -msoft-float */
void DO_EAU_QUI_MONTE(Obj *obj)
{
    extern u32 ray_obj_flags;
    extern u8 ray_obj_main_etat;
    extern u8 ray_obj_sub_etat;
    extern u8 ray_obj_offset_by;
    extern u16 ray_obj_y_pos;
    extern u8 D_801F4EBA;

    if ((ray_obj_flags & 0x400) && ((ray_obj_main_etat != 3) || (ray_obj_sub_etat != 23)))
    {
        switch (num_world)
        {
        case 1:
            if (obj->hit_points != 0)
            {
                if (obj->hit_points == 1)
                {
                    obj->hit_points--;
                    ACTIVE_L_EAU(obj);
                    break;
                }
            }
            else if ((obj->field23_0x3c > 40) || (level.objects[eau_obj_id].iframes_timer == 1))
            {
                if ((D_801F4EBA != 0) && (obj->y_pos > 160))
                {
                    obj->speed_y = -1;
                }
                else
                {
                    obj->speed_y = 0;
                }

                if (obj->field23_0x3c > 0)
                {
                    obj->field23_0x3c--;
                }

                break;
            }
            else
            {
                obj->speed_y = 0;
                break;
            }

            obj->hit_points--;
            break;
        case 3:
            if (pierreAcorde_obj_id == -1)
            {
                if (scroll_y != pierreAcorde_obj_id)
                {
                    obj->init_y_pos = ymap + 160;
                    if ((obj->y_pos - 100) > obj->init_y_pos)
                    {
                        obj->y_pos -= 3;
                    }

                    if (--obj->y_pos > obj->init_y_pos && D_801F4EBA != 0)
                    {
                        obj->y_pos--;
                    }

                    obj->iframes_timer = 1;
                }
                else
                {
                    if (obj->iframes_timer == 1)
                    {
                        obj->init_y_pos = ray_obj_offset_by + ray_obj_y_pos - 30;
                        obj->iframes_timer = 0;
                    }
                    if (obj->init_y_pos < obj->y_pos)
                    {
                        obj->y_pos--;
                    }
                }
            }
            else if ((level.objects[pierreAcorde_obj_id].hit_points != 0) && (obj->y_pos < (ymapmax + 160)))
            {
                obj->field12_0x26 += 14;
                if (obj->field12_0x26 > 16)
                {
                    obj->field12_0x26 -= 16;
                    obj->y_pos++;
                }
            }
            scroll_end_y = obj->y_pos - 160;
        case 4:
        case 5:
            if (obj->screen_x_pos < -166)
            {
                obj->x_pos += 505;
                if (++obj->sub_etat >= 4)
                    obj->sub_etat = 0;
                if (num_level == 8 && num_world == 5)
                {                  
                    obj->init_y_pos -= 5;
                    obj->y_pos = obj->init_y_pos;

                    if (obj->y_pos < (ymapmax + 160))
                    {
                        obj->y_pos = ymapmax + 160;
                    }
                }
            }
            else if (obj->screen_x_pos > 366)
            {
                obj->x_pos -= 505;
                if (--obj->sub_etat >= 4)
                    obj->sub_etat = 3;
                if (num_level == 8 && num_world == 5)
                {
                    obj->init_y_pos += 5;
                    obj->y_pos = obj->init_y_pos;

                    if (obj->y_pos < (ymapmax + 160))
                    {
                        obj->y_pos = ymapmax + 160;
                    }
                }
            }
            break;
        }
    }
    else
    {
        obj->speed_y = 0;
        obj->speed_x = 0;
    }

    if (obj->y_pos < (ymap + 160))
    {
        obj->y_pos = ymap + 160;
    }
}