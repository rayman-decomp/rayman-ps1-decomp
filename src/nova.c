#include "nova.h"

/* 3AE54 8015F654 -O2 -msoft-float */
Obj *allocateNOVA(void)
{
    Obj *res = null;
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_NOVA2 && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            set_main_and_sub_etat(cur_obj, 5, 20);
            cur_obj->flags |= FLG(OBJ_ALIVE);
            cur_obj->anim_index = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].anim_index;
            cur_obj->anim_frame = 0;
            res = cur_obj;
            break;
        }
        cur_obj++;
        i++;
    }

    return res;
}

/* 3AF28 8015F728 -O2 -msoft-float */
void DO_NOVA(Obj *in_obj)
{
    s16 sp18;
    s16 sp1A;
    s16 sp1C;
    s16 sp1E;
    s16 sp20;
    s16 sp22;
    s16 sp24;
    s16 sp26;
    Obj *temp_v0;
    s16 test_1;
    s16 test_2;
    s16 test_3;
    s16 test_4;
    s16 test_5;
    s16 test_6;
    s16 test_7;
    s16 test_8;

    temp_v0 = allocateNOVA();
    if (temp_v0 != 0)
    {
        temp_v0->x_pos = in_obj->x_pos;
        temp_v0->y_pos = in_obj->y_pos;
        GET_ANIM_POS(temp_v0, &sp18, &sp1A, &sp1C, &sp1E);
        GET_ANIM_POS(in_obj, &sp20, &sp22, &sp24, &sp26);
        temp_v0->flags |= 0x800;
        test_1 = sp24;
        test_2 = sp20;
        test_3 = sp1C;
        test_4 = sp18;
        test_5 = sp26;
        test_6 = sp22;
        test_7 = sp1E;
        test_8 = sp1A;
        temp_v0->display_prio = 1;
        temp_v0->field23_0x3c = 0;
        temp_v0->x_pos += ((test_2 + (test_1 >> 0x1)) - (test_4 + (test_3 >> 0x1)));
        temp_v0->y_pos += ((test_6 + (test_5 >> 0x1)) - (test_8 + (test_7 >> 0x1)));
        calc_obj_pos_map(temp_v0);
    }
}

/* 3B034 8015F834 -O2 -msoft-float */
void DO_NOVA2(Obj *in_obj)
{
    s16 i;
    Obj *nova_obj;
    s16 nova_x; s16 nova_y; s16 nova_w; s16 nova_h;
    s16 in_x; s16 in_y; s16 in_w; s16 in_h;
    s16 new_x; s16 new_y;

    for (i = 0; i < 5; i++)
    {
        nova_obj = allocateNOVA();
        if (nova_obj)
        {
            nova_obj->x_pos = in_obj->x_pos;
            nova_obj->y_pos = in_obj->y_pos;
            GET_ANIM_POS(nova_obj, &nova_x, &nova_y, &nova_w, &nova_h);
            GET_ANIM_POS(in_obj, &in_x, &in_y, &in_w, &in_h);
            new_x = in_x - (nova_x + (nova_w >> 1));
            new_y = in_y - (nova_y + (nova_h >> 1));
            nova_obj->flags |= FLG(OBJ_ACTIVE);
            switch (i)
            {
            case 0:
                break;
            case 1:
                new_x += in_w;
                break;
            case 2:
                new_x += in_w;
                new_y += in_h;
                break;
            case 3:
                new_y += in_h;
                break;
            case 4:
                new_x += in_w >> 1;
                new_y += in_h >> 1;
                break;
            }
            nova_obj->display_prio = 0;
            nova_obj->field23_0x3c = i * 5;
            nova_obj->x_pos += new_x;
            nova_obj->y_pos += new_y;
            calc_obj_pos_map(nova_obj);
        }
    }
}
const u8 rodata_DO_NOVA2[4] = {};

/* 3B1F4 8015F9F4 -O2 -msoft-float */
s32 NOVA_STATUS_BAR(void)
{
    Obj *obj = allocateNOVA();
    s16 res = -1;

    if (obj)
    {
        res = obj->id;
        obj->display_prio = 0;
        obj->x_pos = obj->offset_bx + xmap;
        obj->y_pos = obj->offset_by + ymap;
        obj->timer = 10;
        obj->field23_0x3c = 0xFF;
    }

    return res;
}
