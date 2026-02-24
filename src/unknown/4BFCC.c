#include "unknown/4BFCC.h"

/* TODO: macro */
/* 4BFCC 801707CC -O2 -msoft-float */
u8 YaUnBloc(Obj *obj, s16 param_2)
{
    s16 unk_y;
    s16 i;
    u8 res = false;

    switch (param_2)
    {
    case 2:
        if (block_flags[(u16) mp.map[((obj->x_pos + obj->offset_bx - 8) >> 4) + mp.width * (obj->y_pos >> 4)] >> 10] >> BLOCK_FULLY_SOLID & 1)
            res = true;
        if (block_flags[(u16) mp.map[((obj->x_pos + obj->offset_bx + 7) >> 4) + mp.width * (obj->y_pos >> 4)] >> 10] >> BLOCK_FULLY_SOLID & 1)
            res = true;
        break;
    case 3:
        if (block_flags[(u16) mp.map[((obj->x_pos + obj->offset_bx - 8) >> 4) + mp.width * ((obj->y_pos + 154) >> 4)] >> 10] >> BLOCK_FULLY_SOLID & 1)
            res = true;
        if (block_flags[(u16) mp.map[((obj->x_pos + obj->offset_bx + 7) >> 4) + mp.width * (obj->y_pos >> 4)] >> 10] >> BLOCK_FULLY_SOLID & 1)
            res = true;
        break;
    case 0:
        unk_y = 6;
        i = 0;
        while (i < 10)
        {
            if (block_flags[(u16) mp.map[((obj->x_pos + obj->offset_bx - 16) >> 4) + mp.width * ((obj->y_pos + unk_y) >> 4)] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
            unk_y += 16;
            i++;
        }
        break;
    case 1:
        unk_y = 6;
        i = 0;
        while (i < 10)
        {
            if (block_flags[(u16) mp.map[((obj->x_pos + obj->offset_bx + 16) >> 4) + mp.width * ((obj->y_pos + unk_y) >> 4)] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
            unk_y += 16;
            i++;
        }
        break;
    }

    return res;
}
