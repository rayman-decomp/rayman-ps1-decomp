#include "obj/flash_command.h"

/* 4D1F4 801719F4 -O2 -msoft-float */
void DO_FLASH_COMMAND(Obj *obj)
{
    obj->init_x_pos += obj->iframes_timer;
    while (__builtin_abs(obj->init_x_pos) >= 128)
    {
        if (obj->iframes_timer > 0)
        {
            obj->x_pos++;
            obj->init_x_pos -= 128;
        }
        else
        {
            obj->x_pos--;
            obj->init_x_pos += 128;
        }
    }

    obj->init_y_pos = obj->init_y_pos + obj->field20_0x36;
    while (__builtin_abs(obj->init_y_pos) >= 128)
    {
        if (obj->field20_0x36 > 0)
        {
            obj->y_pos++;
            obj->init_y_pos -= 128;
        }
        else
        {
            obj->y_pos--;
            obj->init_y_pos += 128;
        }
    }

    calc_obj_pos_map(obj);
    obj->anim_frame = obj->hit_points - 1;
}
