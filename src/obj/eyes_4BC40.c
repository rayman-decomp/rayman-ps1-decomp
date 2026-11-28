#include "obj/eyes_4BC40.h"

/* 4BC40 80170440 -O2 -msoft-float */
void DO_ROLL_EYES(Obj *obj)
{
    s32 screen_x;
    s16 unk_x_1;
    s16 unk_y_1;
    s16 diff_x;
    s16 diff_y;
    s16 temp_lo;
    s16 fire_par_3;
    u8 y_gt_0;
    u8 x_gt_0;

    if (obj->type == 0x91)
    {
        switch (obj->sub_etat)
        {
        case 0:
            if (--obj->iframes_timer == 0)
            {
                obj->sub_etat = 3;
                obj->iframes_timer = 0x001E;
            }
            break;
        case 1:
            if (--obj->iframes_timer == 0)
            {
                do
                {
                    obj->sub_etat = 2;
                } while (0); /* required to match */
                obj->iframes_timer = 5;
            }
            break;
        case 2:
        case 5:
            if (--obj->iframes_timer == 0)
            {
                obj->iframes_timer = obj->field23_0x3c;
                obj->sub_etat = 0;
                obj->field23_0x3c = 0x0064;
            }
            break;
        }
        obj->change_anim_mode = 0;
    }
    diff_x = ray.x_pos - obj->x_pos;
    diff_y = ray.y_pos - obj->y_pos;
    unk_x_1 = diff_x + 0x20;
    unk_y_1 = diff_y + 0x19;
    if (obj->type == 0x91)
    {
        unk_x_1 = diff_x + 0x34;
        unk_y_1 = diff_y + 0x23;
    }
    x_gt_0 = unk_x_1 > 0;
    y_gt_0 = unk_y_1 > 0;
    if (x_gt_0 == 0)
    {
        unk_x_1 = -unk_x_1;
    }
    if (y_gt_0 == 0)
    {
        unk_y_1 = -unk_y_1;
    }
    if (unk_x_1 >= 0xC9)
    {
        unk_x_1 = ashr16(unk_x_1, 1U);
        unk_y_1 = ashr16(unk_y_1, 1U);
    }

    if (unk_y_1 == 0)
    {
        if (x_gt_0)
        {
            fire_par_3 = 0x1B;
        }
        else
        {
            if (unk_x_1 != 0)
            {
                fire_par_3 = 9;
            }
            else
                fire_par_3 = -1;
        }
    }
    else
    {
        temp_lo = unk_x_1 * 0x2D / unk_y_1;
        if (x_gt_0)
        {
            if (y_gt_0)
            {
                if (temp_lo >= (s16) LEN(N_anim))
                {
                    fire_par_3 = 0x1B;
                }
                else
                {
                    fire_par_3 = N_anim[temp_lo] + 0x1B;
                }
            }
            else
            {
                if (temp_lo >= (s16) LEN(N_anim))
                {
                    fire_par_3 = 0;
                }
                else
                {
                    fire_par_3 = N_anim[temp_lo];
                }
            }
        }
        else if (y_gt_0)
        {
            if (temp_lo >= (s16) LEN(N_anim))
            {
                fire_par_3 = 0x12;
            }
            else
            {
                fire_par_3 = N_anim[temp_lo] + 0x12;
            }
        }
        else
        {
            if (temp_lo >= (s16) LEN(N_anim))
            {
                fire_par_3 = 9;
            }
            else
            {
                fire_par_3 = N_anim[temp_lo] + 9;
            }
        }
    }
    if (obj->sub_etat == 3)
    {
        if ((--obj->iframes_timer) == 0)
        {
            unk_y_1 = obj->screen_y_pos;
            screen_x = unk_x_1 = obj->screen_x_pos;
            obj->sub_etat = 1;
            obj->iframes_timer = 0x003C;
            if (
                (screen_x >= -0x33) && (unk_y_1 >= -0x23) &&
                (screen_x < 0x131) && (unk_y_1 < 0xEB)
            )
            {
                DO_REDEYE_FIRE(obj->x_pos, obj->y_pos, fire_par_3);
            }
            else
            {
                obj->field23_0x3c = 0x0028;
            }
        }
    }
    if (fire_par_3 != -1)
    {
        obj->anim_frame = fire_par_3 - 1;
    }
}
