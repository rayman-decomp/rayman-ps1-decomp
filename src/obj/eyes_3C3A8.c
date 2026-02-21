#include "obj/eyes_3C3A8.h"

/* 3C3A8 80160BA8 -O2 -msoft-float */
void DO_REDEYE_FIRE(s16 x_pos, s16 y_pos, s16 param_3)
{
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_FLASH && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj->flags &= ~FLG(OBJ_FLIP_X);
            switch (param_3)
            {
            case 0:
                cur_obj->iframes_timer = 256;
                cur_obj->field20_0x36 = 0;
                break;
            case 1:
                cur_obj->iframes_timer = 252;
                cur_obj->field20_0x36 = -44;
                break;
            case 2:
                cur_obj->iframes_timer = 240;
                cur_obj->field20_0x36 = -87;
                break;
            case 3:
                cur_obj->iframes_timer = 221;
                cur_obj->field20_0x36 = -128;
                break;
            case 4:
                cur_obj->iframes_timer = 196;
                cur_obj->field20_0x36 = -164;
                break;
            case 5:
                cur_obj->iframes_timer = 164;
                cur_obj->field20_0x36 = -196;
                break;
            case 6:
                cur_obj->iframes_timer = 128;
                cur_obj->field20_0x36 = -221;
                break;
            case 7:
                cur_obj->iframes_timer = 87;
                cur_obj->field20_0x36 = -240;
                break;
            case 8:
                cur_obj->iframes_timer = 44;
                cur_obj->field20_0x36 = -252;
                break;
            case 9:
                cur_obj->iframes_timer = -252;
                cur_obj->field20_0x36 = -44;
                break;
            case 10:
                cur_obj->iframes_timer = -240;
                cur_obj->field20_0x36 = -87;
                break;
            case 11:
                cur_obj->iframes_timer = -221;
                cur_obj->field20_0x36 = -128;
                break;
            case 12:
                cur_obj->iframes_timer = -196;
                cur_obj->field20_0x36 = -164;
                break;
            case 13:
                cur_obj->iframes_timer = -164;
                cur_obj->field20_0x36 = -196;
                break;
            case 14:
                cur_obj->iframes_timer = -128;
                cur_obj->field20_0x36 = -221;
                break;
            case 15:
                cur_obj->iframes_timer = -87;
                cur_obj->field20_0x36 = -240;
                break;
            case 16:
                cur_obj->iframes_timer = -44;
                cur_obj->field20_0x36 = -252;
                break;
            case 17:
                cur_obj->iframes_timer = 0;
                cur_obj->field20_0x36 = -256;
                break;
            case 18:
                cur_obj->iframes_timer = -256;
                cur_obj->field20_0x36 = 0;
                break;
            case 19:
                cur_obj->iframes_timer = -252;
                cur_obj->field20_0x36 = 44;
                break;
            case 20:
                cur_obj->iframes_timer = -240;
                cur_obj->field20_0x36 = 87;
                break;
            case 21:
                cur_obj->iframes_timer = -221;
                cur_obj->field20_0x36 = 128;
                break;
            case 22:
                cur_obj->iframes_timer = -196;
                cur_obj->field20_0x36 = 164;
                break;
            case 23:
                cur_obj->iframes_timer = -164;
                cur_obj->field20_0x36 = 196;
                break;
            case 24:
                cur_obj->iframes_timer = -128;
                cur_obj->field20_0x36 = 221;
                break;
            case 25:
                cur_obj->iframes_timer = -87;
                cur_obj->field20_0x36 = 240;
                break;
            case 26:
                cur_obj->iframes_timer = -44;
                cur_obj->field20_0x36 = 252;
                break;
            case 27:
                cur_obj->iframes_timer = 252;
                cur_obj->field20_0x36 = 44;
                break;
            case 28:
                cur_obj->iframes_timer = 240;
                cur_obj->field20_0x36 = 87;
                break;
            case 29:
                cur_obj->iframes_timer = 221;
                cur_obj->field20_0x36 = 128;
                break;
            case 30:
                cur_obj->iframes_timer = 196;
                cur_obj->field20_0x36 = 164;
                break;
            case 31:
                cur_obj->iframes_timer = 164;
                cur_obj->field20_0x36 = 196;
                break;
            case 32:
                cur_obj->iframes_timer = 128;
                cur_obj->field20_0x36 = 221;
                break;
            case 33:
                cur_obj->iframes_timer = 87;
                cur_obj->field20_0x36 = 240;
                break;
            case 34:
                cur_obj->iframes_timer = 44;
                cur_obj->field20_0x36 = 252;
                break;
            case 35:
                cur_obj->iframes_timer = 0;
                cur_obj->field20_0x36 = 256;
                break;
            default:
                break;
            }
            cur_obj->hit_points = param_3;
            cur_obj->x_pos = x_pos;
            cur_obj->y_pos = y_pos;
            cur_obj->speed_x = 0;
            cur_obj->speed_y = 0;
            cur_obj->init_x_pos = cur_obj->iframes_timer;
            cur_obj->init_y_pos = cur_obj->field20_0x36;
            calc_obj_pos_map(cur_obj);
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            PlaySnd(205, i);
            break;
        }
        cur_obj++;
        i++;
    }
}
