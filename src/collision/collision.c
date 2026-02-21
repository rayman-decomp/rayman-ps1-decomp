#include "collision/collision.h"

#ifdef BSS_DEFS
s16 ray_zdc_x;
s16 ray_zdc_y;
s16 ray_zdc_w;
s16 ray_zdc_h;
u8 in_air_because_hit;
s16 ZDCPTR;
s16 ray_speed_inv;
u8 life_becoz_wiz;
#endif

/* 10000 (dist) could be a #define */

/* 1B1F0 8013F9F0 -O2 -msoft-float */
void PS1_SetZDC(s16 x, s16 y, u8 w, u8 h, u8 flags, u8 sprite)
{
    ZDC *zdc = &zdc_tab[ZDCPTR];

    zdc->x_pos = x;
    zdc->y_pos = y;
    zdc->width = w;
    zdc->height = h;
    zdc->flags = flags;
    zdc->sprite = sprite - 1;
    ZDCPTR++;
}

/* 1B248 8013FA48 -O2 -msoft-float */
void PS1_SetTypeZDC(ObjType type, u16 param_2, s32 param_3)
{
    type_zdc[type] = param_2 | (param_3 << 11);
}

/* 1B270 8013FA70 -O2 -msoft-float */
u16 get_nb_zdc(Obj *obj)
{
    return obj->zdc >> 11;
}

/*
first 11 bits, see
https://github.com/BinarySerializer/BinarySerializer.Ray1/blob/0323431715346d65200f898664351932b86deb8b/src/BinarySerializer.Ray1/DataTypes/Collision/ZDCReference.cs#L6
*/
/* 1B27C 8013FA7C -O2 -msoft-float */
u16 get_zdc_index(Obj *obj)
{
    return obj->zdc & 0x7ff;
}

/* 1B288 8013FA88 -O2 -msoft-float */
ZDC *get_zdc(Obj *obj, s16 param_2)
{
    return &zdc_tab[(s16) get_zdc_index(obj) + param_2];
}

/* 1B2D0 8013FAD0 -O2 -msoft-float */
s16 get_ZDCPTR(void)
{
    return ZDCPTR;
}

/* 1B2E0 8013FAE0 -O2 -msoft-float */
s16 in_coll_sprite_list(Obj *obj, s16 param_2) /* has ugly stuff, but overall fine? */
{
    u8 unk_1[16];
    s16 i;
    s16 res = false;

    switch (obj->type)
    {
    case TYPE_GENEBADGUY:
        unk_1[0] = 0;
        unk_1[1] = 1;
        unk_1[2] = 2;
        unk_1[3] = 0xFF;
        break;
    case TYPE_BADGUY3:
        if (obj->main_etat == 0)
        {
            if (obj->sub_etat == 15 || obj->sub_etat == 16 || obj->sub_etat == 17)
                unk_1[0] = 4;
            else
                unk_1[0] = 2;
        }
        else
            unk_1[0] = 2;
        unk_1[1] = 0xFF;
        break;
    case TYPE_MITE:
    case TYPE_MITE2:
        unk_1[0] = 1;
        if (obj->sub_etat == 11)
        {
            if (obj->main_etat == 2)
                unk_1[1] = 3;
            else
            {
                if (obj->anim_frame > 15)
                    unk_1[1] = 2;
                else
                    unk_1[1] = 0xFF;
            }
            unk_1[2] = 0xFF;
        }
        else
            unk_1[1] = 0xFF;
        break;
    default:
        unk_1[0] = 0;
        unk_1[1] = 0xFF;
        break;
    }

    i = 0;
    do
    {
        res = param_2 == unk_1[i];
        i++;
    } while (unk_1[i] != 0xFF && res != true);

    return res;
}

/* TODO: figure out nicer way of writing these? */
/* 1B43C 8013FC3C -O2 -msoft-float */
s32 box_inter_v_line(s16 param_1, s16 param_2, s16 param_3, s16 param_4, s16 param_5, s16 param_6, s16 param_7)
{
    s32 res = false;

    if (param_1 < param_5 && param_2 > param_5)
    {
        if (param_6 < param_3 && param_7 > param_3)
            res = true;
        else if (param_6 < param_4 && param_7 > param_4)
            res = true;
    }

    return res;
}

/* 1B4DC 8013FCDC -O2 -msoft-float */
s32 box_inter_h_line(s16 param_1, s16 param_2, s16 param_3, s16 param_4, s16 param_5, s16 param_6, s16 param_7)
{
    s32 res = false;

    if (param_3 < param_5 && param_4 > param_5)
    {
        if (param_6 < param_1 && param_7 > param_1)
            res = true;
        else if (param_6 < param_2 && param_7 > param_2)
            res = true;
    }

    return res;
}

/* 1B57C 8013FD7C -O2 -msoft-float */
s16 inter_box(s32 x_1, s32 y_1, s32 w_1, s32 h_1, s16 x_2, s16 y_2, s32 w_2, s32 h_2)
{
    s16 unk_1 = x_1 - w_2;
    s16 unk_2 = y_1 - h_2;
    s16 unk_3 = w_1 + w_2;
    s16 unk_4 = h_1 + h_2;
    u8 res = false;

    if (x_2 >= unk_1 && y_2 >= unk_2 && (unk_1 + unk_3 >= x_2))
        res = (unk_2 + unk_4 < y_2) ^ 1;
    return res;
}

/* 1B600 8013FE00 -O2 -msoft-float */
/*void GET_ANIM_POS(Obj *param_1,short *x,short *y,ushort *w,ushort *h);
void GET_RAY_ZDC(Obj *ray,short *x,short *y,short *w,short *h);
void get_cou_zdc(Obj *param_1,short *param_2,short *param_3,short *param_4,short *param_5);
void get_spi_zdc(int param_1,short *param_2,short *param_3,s16 *param_4,s16 *param_5);*/

void GET_OBJ_ZDC(Obj *obj, s16 *out_x, s16 *out_y, s16 *out_w, s16 *out_h)
{
    s16 anim_x; s16 anim_y; s16 anim_w; s16 anim_h;
    s32 unk_1;
    s32 unk_2;
    s16 old_flip_x;
    s32 bc_x_pos;
    s16 new_x;
    u8 unk_3;
    s16 new_y;

    switch (obj->type)
    {
    case TYPE_STALAG:
        GET_SPRITE_POS(obj, 1, out_x, out_y, out_w, out_h);
        unk_1 = 3;
        if ((s32) *out_w > *out_h)
        {
            *out_x += 4;
            *out_w -= 8;
            *out_y += 8;
            *out_h -= 12;
        }
        else
        {
            *out_x = *out_x - unk_1 + (*out_w >> 1);
            *out_w = 6;
            *out_y += 16;
            *out_h -= 32;
        }
        break;
    case TYPE_BLACK_RAY:
        GET_RAY_ZDC(obj, out_x, out_y, out_w, out_h);
        break;
    case TYPE_STONECHIP:
        GET_ANIM_POS(obj, &anim_x, &anim_y, &anim_w, &anim_h);
        *out_x = anim_x + 13;
        *out_y = anim_y + 13;
        *out_w = 4;
        *out_h = 4;
        break;
    case TYPE_POWERUP:
    case TYPE_FALLING_OBJ:
    case TYPE_FALLING_OBJ2:
    case TYPE_FALLING_OBJ3:
        GET_ANIM_POS(obj, &anim_x, &anim_y, &anim_w, &anim_h);
        *out_x = anim_x + 10;
        *out_y = anim_y + 10;
        *out_w = anim_w - 20;
        *out_h = anim_h - 20;
        break;
    case TYPE_FLASH:
        GET_ANIM_POS(obj, out_x, out_y, out_w, out_h);
        unk_2 = 2;
        *out_x = *out_x - unk_2 + (*out_w >> 1);
        *out_y = *out_y - unk_2 + (*out_h >> 1);
        *out_w = 4;
        *out_h = 4;
        break;
    case TYPE_ECLAIR:
    case TYPE_ETINC:
        GET_ANIM_POS(obj, &anim_x, &anim_y, &anim_w, &anim_h);
        *out_x = anim_x + 10;
        *out_y = anim_y + 4;
        *out_w = anim_w - 30;
        *out_h = anim_h - 8;
        break;
    case TYPE_CLASH:
    case TYPE_NOTE:
        GET_ANIM_POS(obj, &anim_x, &anim_y, &anim_w, &anim_h);
        *out_x = anim_x + 2;
        *out_y = anim_y - 4;
        *out_w = anim_w - 4;
        *out_h = anim_h + 3;
        break;
    case TYPE_BBL:
        old_flip_x = obj->flags >> OBJ_FLIP_X & 1;
        obj->flags &= ~FLG(OBJ_FLIP_X);
        GET_ANIM_POS(obj, &anim_x, &anim_y, &anim_w, &anim_h); /* ... */
        obj->flags = (obj->flags & ~FLG(OBJ_FLIP_X)) | old_flip_x << OBJ_FLIP_X;
        if (obj->field23_0x3c != 2)
        {
            *out_x = anim_x + 3;
            *out_y = anim_y + 20;
            *out_w = 50;
            *out_h = 40;
        }
        else
        {
            *out_x = anim_x + 20;
            *out_y = anim_y + 35;
            *out_w = 1;
            *out_h = 1;
        }
        break;
    case TYPE_MARTEAU:
    case TYPE_MOVE_MARTEAU:
        GET_SPRITE_POS(obj, 2, &anim_x, &anim_y, &anim_w, &anim_h);
        *out_x = anim_x;
        *out_y = anim_y;
        *out_w = 16;
        *out_h = 32;
        break;
    case TYPE_STONEDOG:
    case TYPE_STONEDOG2:
        GET_ANIM_POS(obj, &anim_x, &anim_y, &anim_w, &anim_h);
        *out_x = anim_x + 4;
        *out_y = anim_y + 2;
        *out_w = anim_w - 8;
        *out_h = anim_h - 6;
        break;
    case TYPE_CAGE:
        GET_ANIM_POS(obj, &anim_x, &anim_y, &anim_w, &anim_h);
        *out_x = anim_x + 8;
        *out_y = anim_y + 8;
        *out_w = anim_w - 16;
        *out_h = anim_h - 16;
        break;
    case TYPE_STONEMAN1:
    case TYPE_STONEMAN2:
    case TYPE_STONEWOMAN2:
    case TYPE_STONEWOMAN:
        if (obj->main_etat == 0 && (obj->sub_etat == 3 || obj->sub_etat == 4))
        {
            *out_x = obj->x_pos;
            *out_y = obj->y_pos;
            *out_w = 0;
            *out_h = 0;
        }
        else
        {
            *out_x = obj->x_pos + obj->offset_bx - 10;
            *out_y = obj->y_pos + obj->offset_by - 60;
            *out_w = 20;
            *out_h = 50;
        }
        break;
    case TYPE_CAGE2:
        *out_x = obj->x_pos;
        *out_y = obj->y_pos;
        *out_w = 0;
        *out_h = 0;
        break;
    case TYPE_WIZARD1:
        *out_x = obj->x_pos;
        *out_y = obj->y_pos;
        *out_w = 50;
        *out_h = 110;
        break;
    case TYPE_BIG_CLOWN:
        if (obj->main_etat == 0 && obj->sub_etat == 2 && obj->anim_frame >= 16)
        {
            bc_x_pos = obj->x_pos;
            if (obj->flags & FLG(OBJ_FLIP_X))
                new_x = bc_x_pos + 80;
            else
                new_x = bc_x_pos + 16;
            *out_x = new_x;
            *out_y = obj->y_pos + 40;
            *out_w = 68;
        }
        else if (obj->main_etat == 0 && obj->sub_etat == 2)
        {
            bc_x_pos = obj->x_pos;
            if (obj->flags & FLG(OBJ_FLIP_X))
                new_x = bc_x_pos + 80;
            else
                new_x = bc_x_pos + 48;
            *out_x = new_x;
            *out_y = obj->y_pos + 38;
            *out_w = 32;
        }
        else
        {
            *out_x = obj->x_pos + 64;
            *out_y = obj->y_pos + 38;
            *out_w = 32;
        }
        *out_h = 48;
        break;
    case TYPE_DROP:
        GET_SPRITE_POS(obj, 0, &anim_x, &anim_y, &anim_w, &anim_h);
        if (obj->main_etat == 2)
        {
            if (obj->sub_etat == 2)
            {
                *out_x = anim_x + 5;
                *out_y = anim_y + 28;
                *out_w = 6;
                *out_h = 22;
            }
            else if (obj->sub_etat == 1)
            {
                *out_x = anim_x + 6;
                *out_y = anim_y + 18;
                *out_w = 13;
                *out_h = 11;
            }
            else if (obj->sub_etat == 0)
            {
                *out_x = anim_x + 7;
                *out_y = anim_y + 8;
                *out_w = 19;
                *out_h = 11;
            }
        }
        break;
    case TYPE_TROMPETTE:
        GET_ANIM_POS(obj, &anim_x, &anim_y, &anim_w, &anim_h);
        *out_x = anim_x + 24;
        *out_y = anim_y + 14;
        *out_w = anim_w - 48;
        *out_h = anim_h - 27;
        break;
    case TYPE_TNT_BOMB:
        *out_x = obj->x_pos + 76;
        *out_y = obj->y_pos + 85;
        *out_w = 8;
        *out_h = 8;
        break;
    case TYPE_EXPLOSION:
        *out_x = obj->x_pos;
        *out_y = obj->y_pos;
        if (obj->sub_etat == 0)
        {
            *out_w = 22;
            *out_h = 22;
            *out_x += 68;
            *out_y += 65;
            break;
        }
        *out_w = 0;
        *out_h = 0;
        break;
    case TYPE_COUTEAU:
        get_cou_zdc(obj, out_x, out_y, out_w, out_h);
        break;
    case TYPE_SPIDER_PLAFOND:
        get_spi_zdc(obj, out_x, out_y, out_w, out_h);
        break;
    case TYPE_POI3:
        if (
            (obj->main_etat == 2) &&
            (obj->sub_etat == 15 || obj->sub_etat == 12 || obj->sub_etat == (unk_3 = 13))
        )
        {
            *out_x = obj->x_pos + 54;
            new_y = obj->y_pos + 55;
        }
        else
        {
            *out_x = obj->x_pos + 74;
            new_y = obj->y_pos + 45;
        }
        *out_y = new_y;
        *out_w = 14;
        *out_h = 21;
        break;
    case TYPE_PETIT_COUTEAU:
        if (obj->hit_points == 1)
        {
            *out_x = obj->x_pos + 138;
            *out_y = obj->y_pos + 138;
            *out_w = 43;
            *out_h = 15;
        }
        if (obj->hit_points == 2)
        {
            *out_x = obj->x_pos + 131;
            *out_y = obj->y_pos + 88;
            *out_w = 17;
            *out_h = 49;
        }
        if (obj->hit_points == 3)
        {
            *out_x = obj->x_pos + 62;
            *out_y = obj->y_pos + 138;
            *out_w = 43;
            *out_h = 16;
        }
        if (obj->hit_points == 4)
        {
            *out_x = obj->x_pos + 96;
            *out_y = obj->y_pos + 87;
            *out_w = 17;
            *out_h = 48;
        }
        break;
    default:
        GET_ANIM_POS(obj, out_x, out_y, out_w, out_h);
        break;
    }
}

/* 1C034 80140834 -O2 -msoft-float */
s16 GET_SPRITE_ZDC(Obj *obj, s16 index, s16 *out_x, s16 *out_y, s16 *out_w, s16 *out_h)
{
    s16 type;
    s32 unk_x; s32 unk_y; s32 unk_w; s32 unk_h;
    s16 spr_x; s16 spr_y; s16 spr_w; s16 spr_h;
    s16 succ;
    s16 temp_h;

    type = obj->type;
    unk_h = 0;
    unk_w = 0;
    unk_y = 0;
    unk_x = 0;
    succ = GET_SPRITE_POS(obj, index, &spr_x, &spr_y, &spr_w, &spr_h);
    if (succ)
    {
        switch (type)
        {
        case TYPE_CYMBALE:
            switch (index)
            {
            case 3:
                unk_x = 4;
                unk_y = 2;
                unk_w = -4;
                unk_h = -10;
                break;
            case 4:
                unk_x = 0;
                unk_y = 2;
                unk_w = 0;
                unk_h = -10;
                break;
            case 5:
                unk_x = 0;
                unk_y = 2;
                unk_w = -4;
                unk_h = -10;
                break;
            }
            break;
        case TYPE_GENEBADGUY:
            if (
                (obj->main_etat == 0 && obj->sub_etat == 0) ||
                (obj->main_etat == 1 && obj->sub_etat == 0)
            )
            {
                switch (index)
                {
                case 0:
                    unk_x = 10;
                    unk_y = 0;
                    spr_w = 34;
                    spr_h = 32;
                    break;
                case 1:
                    unk_x = 4;
                    unk_y = 0;
                    spr_w = 26;
                    break;
                case 2:
                    unk_x = 4;
                    unk_y = 0;
                    spr_w = 48;
                    spr_h = 24;
                    break;
                }
            }
            else if (obj->main_etat == 0 && obj->sub_etat == 1)
            {
                spr_x = obj->x_pos + 112;
                spr_y = obj->y_pos + 184;
                spr_w = 32;
                spr_h = 16;
            }
            else
            {
                spr_w = 0;
                spr_h = 0;
                succ = false;
            }
            break;
        case TYPE_BADGUY3:
            if (index != 2)
            {
                if (index == 4)
                {
                    unk_x = -3;
                    unk_y = 0;
                    spr_w = 21;
                    spr_h = 10;
                    break;
                }
            }
            else
            {
                unk_x = 1;
                unk_y = -4;
                unk_w = -2;
                unk_h = 6;
            }
            break;
        case TYPE_MITE:
        case TYPE_MITE2:
            switch (index)
            {
            case 1:
                if (obj->main_etat == 0)
                {
                    if (obj->sub_etat == 9 || obj->sub_etat == 10 || obj->sub_etat == 11)
                    {
                        unk_x = -8;
                        unk_y = 5;
                        spr_w = 26;
                        temp_h = 8;
                    }
                    else
                    {
                        unk_x = 1;
                        unk_y = -5;
                        spr_w = 16;
                        temp_h = 30;
                    }
                }
                else
                {
                    unk_x = 1;
                    unk_y = -5;
                    spr_w = 16;
                    temp_h = 30;
                }
                spr_h = temp_h;
                break;
            case 2:
                unk_x = 0;
                unk_y = 7;
                spr_w = 16;
                spr_h = 16;
                break;
            case 3:
                unk_x = 0;
                unk_y = 2;
                spr_w = 13;
                spr_h = 9;
                break;
            }
            break;
        }
        *out_x = unk_x + spr_x;
        *out_y = unk_y + spr_y;
        *out_w = unk_w + spr_w;
        *out_h = unk_h + spr_h;
    }
    return succ;
}

/* 1C3F8 80140BF8 -O2 -msoft-float */
s32 BOX_HIT_SPECIAL_ZDC(s16 in_x, s16 in_y, s16 in_w, s16 in_h, Obj *obj)
{
    u8 frame;
    s16 d;
    s16 bb1_x_1; s16 bb1_y_1; s16 bb1_w_1; s16 bb1_h_1;
    s16 bb1_x_2; s16 bb1_y_2; s16 bb1_w_2; s16 bb1_h_2;
    s16 res = -1;

    switch (obj->type)
    {
    case TYPE_BAG1:
        frame = obj->anim_frame;
        d = bagD[frame];
        if (d != -1)
        {
            if (inter_box(
                    in_x, in_y, in_w, in_h,
                    obj->x_pos + obj->offset_bx - (bagW[frame] >> 1),
                    obj->y_pos + obj->offset_by + d - bagH[frame],
                    bagW[frame],
                    bagH[frame]
                ))
                res = 1;
        }
        break;
    case TYPE_BB1:
    case TYPE_BB12:
    case TYPE_BB13:
    case TYPE_BB14:
        if (in_h == ray_zdc_h)
        {
            GET_BB1_ZDCs(
                obj,
                &bb1_x_1, &bb1_y_1, &bb1_w_1, &bb1_h_1,
                &bb1_x_2, &bb1_y_2, &bb1_w_2, &bb1_h_2
            );

            /* TODO: write a bit nicer, not sure how yet */
            if (!inter_box(
                    in_x, in_y, in_w, in_h,
                    bb1_x_1, bb1_y_1, bb1_w_1, bb1_h_1
                ))
            {
                if (inter_box(
                        in_x, in_y, in_w, in_h,
                        bb1_x_2, bb1_y_2, bb1_w_2, bb1_h_2
                    ))
                    res = 1;
            }
            else
                res = 1;
        }
        else
        {
            GET_BB1_ZDCs(
                obj,
                &bb1_x_1, &bb1_y_1, &bb1_w_1, &bb1_h_1,
                &bb1_x_2, &bb1_y_2, &bb1_w_2, &bb1_h_2
            );

            if (inter_box(
                    in_x, in_y, in_w, in_h,
                    bb1_x_1, bb1_y_1, bb1_w_1, bb1_h_1
                ))
                res = 6;
            if (inter_box(
                    in_x, in_y, in_w, in_h,
                    bb1_x_2, bb1_y_2, bb1_w_2, bb1_h_2
                ))
                res = 1;

            if (obj->main_etat == 0 && obj->sub_etat == 10)
            {
                GET_SPRITE_POS(obj, 9, &bb1_x_1, &bb1_y_1, &bb1_h_1, &bb1_w_1);
                if (inter_box(
                        in_x, in_y, in_w, in_h,
                        bb1_x_1, bb1_y_1, bb1_w_1, bb1_h_1
                    ))
                    res = 9;
            }
        }
        break;
    }
    return res;
}

/* 1C7E4 80140FE4 -O2 -msoft-float */
s32 BOX_IN_COLL_ZONES(s16 obj_type, s16 in_x, s16 in_y, s16 in_w, s16 in_h, Obj *obj)
{
    s16 res;
    s16 unk_x; s16 unk_y; s16 unk_w; s16 unk_h;
    s16 nb_zdc;
    s16 i;
    ZDC *cur_zdc;
    Animation *cur_anim;
    AnimationLayer *cur_layer;
    s16 layers_count;

    unk_h = 0;
    unk_w = 0;
    unk_y = 0;
    unk_x = 0;
    res = -1;

    if (obj->zdc != 0)
    {
        nb_zdc = get_nb_zdc(obj);
        if (
            num_world == 1 &&
            (
                ((obj->type == TYPE_MOSKITO || obj->type == TYPE_MOSKITO2) &&
                !(obj->eta[obj->main_etat][obj->sub_etat].flags & 0x40)) ||
                (obj->type == TYPE_BADGUY3 &&
                obj->eta[obj->main_etat][obj->sub_etat].flags & 0x40)
            )
        )
            nb_zdc--;

        for (i = 0; i < nb_zdc; i++)
        {
            cur_zdc = get_zdc(obj, i);
            if (!(cur_zdc->flags & 4) || obj_type == TYPE_POING)
            {
                if (cur_zdc->flags & 2)
                {
                    cur_anim = &obj->animations[obj->anim_index];
                    cur_layer = &cur_anim->layers[(cur_anim->layers_count & 0x3FFF) * obj->anim_frame];
                    if (cur_layer[cur_zdc->sprite].sprite != 0)
                    {
                        GET_SPRITE_POS(obj, cur_zdc->sprite, &unk_x, &unk_y, &unk_w, &unk_h);
                        if (obj->flags & FLG(OBJ_FLIP_X))
                            unk_x += unk_w - cur_zdc->width - cur_zdc->x_pos;
                        else
                            unk_x += cur_zdc->x_pos;

                        unk_y += cur_zdc->y_pos;
                        unk_w = cur_zdc->width;
                        unk_h = cur_zdc->height;
                    }
                }
                else
                {
                    unk_x = obj->x_pos + cur_zdc->x_pos;
                    unk_y = obj->y_pos + cur_zdc->y_pos;
                    unk_w = cur_zdc->width;
                    unk_h = cur_zdc->height;
                    /* TODO: can't take << 1 or * 2??? */
                    if (obj->flags & FLG(OBJ_FLIP_X))
                        unk_x =
                            (obj->x_pos + obj->offset_bx) + (obj->x_pos + obj->offset_bx) -
                            (unk_x + unk_w);
                }

                if (inter_box(in_x, in_y, in_w, in_h, unk_x, unk_y, unk_w, unk_h))
                {
                    res = cur_zdc->sprite;
                    break;
                }
            }
        }
    }
    else
    {
        if (obj->hit_sprite == 0xFE)
        {
            GET_OBJ_ZDC(obj, &unk_x, &unk_y, &unk_w, &unk_h);
            if (obj->flags & FLG(OBJ_FLIP_X))
                unk_x =
                    (obj->x_pos + obj->offset_bx) + (obj->x_pos + obj->offset_bx) -
                    (unk_x + unk_w);

            res = inter_box(in_x, in_y, in_w, in_h, unk_x, unk_y, unk_w, unk_h);
            res = res ? res : -1;
        }
        else if (obj->hit_sprite == 0xFF)
        {
            layers_count = obj->animations[obj->anim_index].layers_count & 0x3FFF;
            for (i = 0; i < layers_count; i++)
            {
                if (
                    in_coll_sprite_list(obj, i) &&
                    GET_SPRITE_ZDC(obj, i, &unk_x, &unk_y, &unk_w, &unk_h) &&
                    inter_box(in_x, in_y, in_w, in_h, unk_x, unk_y, unk_w, unk_h)
                )
                {
                    res = i;
                    break;
                }
            }
        }
    }

    return res;
}

/* 1CD38 80141538 -O2 -msoft-float */
s32 COLL_BOX_SPRITE(s16 in_x, s16 in_y, s16 in_w, s16 in_h, Obj *obj)
{
  s16 unk_1;
  s16 spr_x; s16 spr_y; s16 spr_w; s16 spr_h;
  s32 spr;

    unk_1 = GET_SPRITE_POS(obj, obj->hit_sprite, &spr_x, &spr_y, &spr_w, &spr_h);
    if (unk_1 != 0)
        unk_1 = inter_box(in_x, in_y, in_w, in_h, spr_x, spr_y, spr_w, spr_h);
    if (unk_1 != 0)
        spr = obj->hit_sprite;
    else
        spr = -1;
    return spr;
}

/* 1CE18 80141618 -O2 -msoft-float */
s16 CHECK_BOX_COLLISION(s16 obj_type, s16 x, s16 y, s16 w, s16 h, Obj *obj)
{
    s32 h_spr;
    s16 res;

    if (obj->hit_sprite == 0xFD)
        res = BOX_HIT_SPECIAL_ZDC(x, y, w, h, obj);
    else if (((h_spr = obj->hit_sprite) >= 0xFD) && h_spr < 0x100)
        res = BOX_IN_COLL_ZONES(obj_type, x, y, w, h, obj);
    else
        res = COLL_BOX_SPRITE(x, y, w, h, obj);
    return res;
}

/* 1CF08 80141708 -O2 -msoft-float */
s16 possible_sprite(Obj *obj, s16 index)
{
    s16 spr[12];

    switch (obj->type)
    {
    case TYPE_BON3:
        spr[0] = 0;
        spr[1] = 1;
        spr[2] = 2;
        spr[3] = 3;
        spr[4] = 4;
        spr[5] = 0x00FF;
        break;
    case TYPE_CYMBALE:
    case TYPE_CYMBAL2:
        spr[0] = 0;
        spr[1] = 1;
        spr[2] = 2;
        spr[3] = 0x00FF;
        break;
    case TYPE_ROULETTE:
        spr[0] = 5;
        spr[1] = 6;
        spr[2] = 7;
        spr[3] = 8;
        spr[4] = 0x00FF;
        break;
    case TYPE_ROULETTE2:
        spr[0] = 1;
        spr[1] = 2;
        spr[2] = 3;
        spr[3] = 4;
        spr[4] = 0x00FF;
        break;
    case TYPE_ROULETTE3:
        spr[0] = 1;
        spr[1] = 2;
        spr[2] = 3;
        spr[3] = 0x00FF;
        break;
    case TYPE_FALLPLAT:
    case TYPE_LIFTPLAT:
    case TYPE_INTERACTPLT:
        spr[0] = 0;
        spr[1] = 1;
        spr[2] = 0x00FF;
        break;
    case TYPE_TIBETAIN_6:
        if (ray.flags & FLG(OBJ_FLIP_X))
        {
            spr[0] = 4;
            spr[1] = 5;
            spr[2] = 6;
            spr[3] = 7;
            spr[4] = 8;
            spr[5] = 9;
        }
        else
        {
            spr[0] = 9;
            spr[1] = 8;
            spr[2] = 7;
            spr[3] = 6;
            spr[4] = 5;
            spr[5] = 4;
        }
        spr[6] = 0x00FF;
        break;
    case TYPE_TIBETAIN_2:
        spr[0] = 4;
        spr[1] = 5;
        spr[2] = 0x00FF;
        break;
    }
    return spr[index];
}

/* 1D11C 8014191C -O2 -msoft-float */
s16 setToleranceDist(s16 in_x, s16 in_w, s16 in_y)
{
    s16 unk_2;
    s16 dist;
    s16 ray_x = ray.x_pos + ray.offset_bx;
    s16 ray_y = ray.y_pos + ray.offset_by;
    s16 unk_1 = in_x + in_w - 1;

    if (RayEvts.demi)
        unk_2 = 4;
    else
        unk_2 = 8;

    if ((ray_x >= in_x - unk_2) && (ray_x <= unk_1 + unk_2))
    {
        if (ray_x >= in_x && ray_x <= unk_1)
        {
            /* abs??? */
            if (ray_y - in_y >= 0)
                dist = ray_y - in_y;
            else
                dist = in_y - ray_y;
        }
        else
        {
            if (ray_y - in_y < 0)
                dist = ray_y - in_y;
            else
                dist = in_y - ray_y;
            dist--;
        }
    }
    else
        dist = 10000;
    return dist;
}

/* 1D228 80141A28 -O2 -msoft-float */
void SET_RAY_DIST_MULTISPR_CANTCHANGE(Obj *obj)
{
    s16 unk_1;
    s16 i;
    s16 new_dist;
    s16 ray_x; s16 ray_y;
    s16 spr_x; s16 spr_y; s16 spr_w; s16 spr_h;
    s16 diff_x;
    s16 sprite;

    if (RayEvts.demi)
        unk_1 = 4;
    else
        unk_1 = 8;
    i = 0;
    new_dist = 10000;
    ray_x = ray.x_pos + ray.offset_bx;
    ray_y = ray.y_pos + ray.offset_by;

    if (ray.field20_0x36 == obj->id)
    {
        GET_SPRITE_POS(obj, obj->follow_sprite, &spr_x, &spr_y, &spr_w, &spr_h);
        spr_y += obj->offset_hy;
        if (obj->type == TYPE_ROULETTE || obj->type == TYPE_ROULETTE2 || obj->type == TYPE_ROULETTE3)
        {
            spr_w -= 10;
            spr_x += 5;
        }

        if (obj->type == TYPE_TIBETAIN_6 && ray.main_etat == 0 && (obj->anim_frame >= 10 && obj->anim_frame < 40))
        {
            diff_x = (ray.x_pos + ray.offset_bx) - (spr_x + (spr_w >> 1));
            if (diff_x > 0)
                ray.x_pos--;
            else if (diff_x < 0)
                ray.x_pos++;
            ray_x = ray.x_pos + ray.offset_bx;
        }
        new_dist = setToleranceDist(spr_x, spr_w, spr_y);
    }

    if (new_dist == 10000)
    {
        sprite = possible_sprite(obj, i++);
        while (sprite != 0xFF)
        {
            GET_SPRITE_POS(obj, sprite, &spr_x, &spr_y, &spr_w, &spr_h);
            spr_y += obj->offset_hy;
            if (obj->type == TYPE_ROULETTE || obj->type == TYPE_ROULETTE2 || obj->type == TYPE_ROULETTE3)
            {
                spr_w -= 10;
                spr_x += 5;
            }

            if ((ray_x <= spr_x + spr_w + unk_1) && (ray_x >= spr_x - unk_1))
            {
                new_dist = ray_y - spr_y;
                if (obj->type == TYPE_TIBETAIN_6 && (new_dist >= 8 && new_dist <= 10))
                    new_dist = 0;
            }
            else
                new_dist = 10000;

            if (new_dist != 10000)
                obj->follow_sprite = sprite;

            sprite = possible_sprite(obj, i++);
            if (__builtin_abs(new_dist) < 8)
                break;
        }
    }
    obj->ray_dist = new_dist;
}

/* 1D594 80141D94 -O2 -msoft-float */
void SET_RAY_DIST_PI(Obj *obj)
{
    s16 x; s16 y; s16 w; s16 h;
    s16 new_dist;
    s16 prev_flip_x = (obj->flags >> OBJ_FLIP_X & 1) << OBJ_FLIP_X;

    obj->flags &= ~FLG(OBJ_FLIP_X);
    GET_SPRITE_POS(obj, 2, &x, &y, &w, &h);
    obj->flags = obj->flags & ~FLG(OBJ_FLIP_X) | prev_flip_x;
    y += obj->offset_hy;
    x += 4;
    w = 55;
    new_dist = setToleranceDist(x, w, y);
    if (new_dist != 10000)
        obj->follow_sprite = 2;
    obj->ray_dist = new_dist;
}

/* 1D66C 80141E6C -O2 -msoft-float */
void SET_RAY_DIST_BAG(Obj *obj)
{
    s16 x; s16 y; s16 w; s16 h;
    s16 new_w;
    s16 new_dist = 0;

    if (obj->sub_etat == 3 || (obj->sub_etat == 6 && obj->anim_frame < 12))
    {
        GET_SPRITE_POS(obj, obj->follow_sprite, &x, &y, &w, &h);
        new_w = 45;
        y += obj->offset_hy;
        x += ((s16) (w - new_w) >> 1);
        w = new_w;
        new_dist = setToleranceDist(x, w, y);
    }
    else
        new_dist = 10000;

    if (ray.field20_0x36 == obj->id && obj->sub_etat == 6 && obj->anim_frame == 11)
    {
        ray.field20_0x36 = -1;
        set_main_and_sub_etat(&ray, 2, 0);
        new_dist = 10000;
        ray.speed_y -= 10;
    }
    obj->ray_dist = new_dist;
}

/* 1D798 80141F98 -O2 -msoft-float */
void SET_RAY_DIST(Obj *obj)
{
    ObjType type;
    s16 x; s16 y; s16 w; s16 h;

    type = obj->type;
    if (flags[type].flags1 >> OBJ1_RAY_DIST_MULTISPR_CANTCHANGE & 1)
        SET_RAY_DIST_MULTISPR_CANTCHANGE(obj);
    else
    {
        if (type == TYPE_PI || type == TYPE_BBL)
            SET_RAY_DIST_PI(obj);
        else if (type == TYPE_BAG3)
            SET_RAY_DIST_BAG(obj);
        else
        {
            GET_SPRITE_POS(obj, obj->follow_sprite, &x, &y, &w, &h);
            y += obj->offset_hy;
            type = obj->type;
            if (
                type == TYPE_FALLING_OBJ || type == TYPE_FALLING_OBJ2 || type == TYPE_FALLING_OBJ3 ||
                type == TYPE_FALLING_YING || type == TYPE_FALLING_YING_OUYE
            )
            {
                x -= 2;
                w += 4;
            }
            else if (type == TYPE_MOVE_START_NUA || (type == TYPE_PLATFORM && num_world == 2))
                w -= 8;

            obj->ray_dist = setToleranceDist(x, w, y);
        }
    }
}

/* 1D8FC 801420FC -O2 -msoft-float */
void do_boum(void)
{
    Obj *obj;

    allocatePoingBoum();
    poing.is_boum = true;
    obj = &level.objects[poing_obj_id];
    if (!poing.is_returning)
    {
        poing.is_returning = true;
        poing.charge = 0;
        obj->speed_x = 0;
        fist_U_turn(obj, true);
        obj->anim_index = obj->eta[obj->main_etat][obj->sub_etat].anim_index;
    }
}

/* 1D9A0 801421A0 -O2 -msoft-float */
void DO_PNG_COLL_STONEMAN(Obj *obj)
{
    u8 prev_flip_x;

    if (!(obj->main_etat == 0 && obj->sub_etat == 1))
        obj_hurt(obj);
    prev_flip_x = (obj->flags >> OBJ_FLIP_X & 1);
    calc_obj_dir(obj);
    skipToLabel(obj, 8, true);
    if ((obj->flags >> OBJ_FLIP_X & 1) != prev_flip_x)
    {
        skipToLabel(obj, 1, true);
        if (obj->type == TYPE_STONEMAN1)
            allocateStonemanStone(obj, -2, 0);
    }
    if (obj->hit_points < 3)
    {
        if (obj->type == TYPE_STONEMAN1)
            allocateStonemanStone(obj, -2, 0);
        if (obj->hit_points == 0)
        {
            obj->hit_points = obj->init_hit_points;
            skipToLabel(obj, 0, true);
        }
        else
        {
            skipToLabel(obj, 1, true);
            obj->change_anim_mode = ANIMMODE_RESET;
        }
    }
}

/* 1DAC4 801422C4 -O2 -msoft-float */
void DO_PNG_COLL_STONEWOMAN(Obj *obj)
{
    u8 prev_flip_x;

    obj_hurt(obj);
    obj->timer = 0;
    prev_flip_x = (obj->flags >> OBJ_FLIP_X) & 1;
    calc_obj_dir(obj);
    PlaySnd(86, obj->id);
    if ((obj->flags >> OBJ_FLIP_X & 1) != prev_flip_x)
    {
        allocateStonewomanStone(obj, 0);
        skipToLabel(obj, 1, true);
        return;
    }
    if (obj->hit_points < 15)
    {
        allocateStonewomanStone(obj, 0);
        if (obj->hit_points == 0)
        {
            obj->hit_points = obj->init_hit_points;
            skipToLabel(obj, 0, true);
        }
        else
        {
            if (obj->main_etat != 1)
                skipToLabel(obj, 1, true);
            obj->change_anim_mode = ANIMMODE_RESET;
        }
    }
}

/* 1DBBC 801423BC -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/collision/collision", DO_POING_COLLISION);
#else
/* clean up */
void DO_POING_COLLISION(void)
{
    s16 pspr_x; s16 pspr_y; s16 pspr_w; s16 pspr_h;
    u8 label;
    u8 sub_etat;
    Obj *poing_obj;
    Obj *other_obj;
    s16 temp_v0_1;
    s32 sprite;
    s32 unk_1;
    s16 png_spd_x;
    s16 i;
    u8 btyp;
    u8 old_hp;
    s32 fall_x_accel;

    poing_obj = &level.objects[poing_obj_id];
    btyp = 0;
    /* TODO: already being weird in multiple ways */
    GET_SPRITE_POS(poing_obj, 0, &pspr_x, &pspr_y, &pspr_w, &pspr_h);
    if ((temp_v0_1 = poing_obj->speed_x) > 0 || poing_obj->speed_x < 0)
        btyp = BTYP(
            poing_obj->x_pos + poing_obj->offset_bx,
            poing_obj->y_pos + (poing_obj->offset_by + poing_obj->offset_hy >> 1)
        );

    if (block_flags[btyp] >> BLOCK_SOLID & 1)
    {
        do_boum();
        fin_poing_follow(poing_obj, true);
    }
    else
    {
        i = 0;
        other_obj = &level.objects[actobj.objects[i]];
        while (i < actobj.num_active_objects)
        {
            if (new_world || new_level || fin_boss)
                break;

            if (
                other_obj->display_prio != 0 && other_obj->hit_points != 0 &&
                other_obj->eta[other_obj->main_etat][other_obj->sub_etat].flags & FLG(3)
            )
            {
                sprite = CHECK_BOX_COLLISION(TYPE_POING, pspr_x, pspr_y, pspr_w, pspr_h, other_obj);
                if (sprite != -1)
                {
                    old_hp = other_obj->hit_points;
                    switch (other_obj->type)
                    {
                    case TYPE_HYBRIDE_STOSKO:
                        if (
                            sprite == 6 && !poing.is_returning &&
                            other_obj->eta[other_obj->main_etat][other_obj->sub_etat].flags & FLG(0)
                        )
                        {
                            poing.damage = 1;
                            obj_hurt(other_obj);
                            if (other_obj->hit_points != 0)
                            {
                                if (other_obj->sub_etat == 2)
                                    set_sub_etat(other_obj, 4);
                                else
                                    set_sub_etat(other_obj, 13);
                            }
                            else
                            {
                                if (other_obj->sub_etat == 2)
                                {
                                    level.objects[other_obj->field24_0x3e].flags &= ~FLG(OBJ_ALIVE);
                                    DO_NOVA(&level.objects[other_obj->field24_0x3e]);
                                }
                                set_sub_etat(other_obj, 8);
                                other_obj->field23_0x3c = 1;
                            }
                        }
                        break;
                    case TYPE_HYBRIDE_MOSAMS:
                        if (
                            other_obj->eta[other_obj->main_etat][other_obj->sub_etat].flags & FLG(0) &&
                            (sprite == 3 || sprite == 6)
                        )
                        {
                            poing.damage = 1;
                            obj_hurt(other_obj);
                            if (other_obj->hit_points == 0)
                            {
                                skipToLabel(other_obj, 2, true);
                                other_obj->field23_0x3c = 1;
                            }
                            else
                                skipToLabel(other_obj, 4, true);
                        }
                        break;
                    case TYPE_SPACE_MAMA:
                    case TYPE_SPACE_MAMA2:
                        doMereDenisHit(other_obj, sprite);
                        break;
                    case TYPE_DARK:
                        DO_DARK_POING_COLLISION(other_obj);
                        break;
                    case TYPE_BATTEUR_FOU:
                        if (sprite == 2)
                            DO_BAT_POING_COLLISION(other_obj);
                        break;
                    case TYPE_MAMA_PIRATE:
                        if (sprite == 5)
                            DO_PMA_POING_COLLISION(other_obj);
                        break;
                    case TYPE_MOSKITO:
                    case TYPE_MOSKITO2:
                        doMoskitoHit(other_obj);
                        break;
                    case TYPE_ONEUP:
                        if (RayEvts.grap && ray_mode != MODE_MORT_DE_RAYMAN)
                            poing_obj->field20_0x36 = other_obj->id;
                        break;
                    case TYPE_PT_GRAPPIN:
                        if (RayEvts.grap && ray_mode != MODE_MORT_DE_RAYMAN)
                        {
                            if (
                                ABS(
                                    (ray.y_pos + ray.offset_by) -
                                    other_obj->y_pos - other_obj->offset_by
                                ) < 250
                            )
                            {
                                SET_RAY_BALANCE();
                                id_obj_grapped = other_obj->id;

                                other_obj->follow_x =
                                unk_1 =
                                    ANGLE_RAYMAN(other_obj);
                                if (unk_1 > 256)
                                    other_obj->field24_0x3e = -1;
                                else if (unk_1 <= 256)
                                {
                                    if (unk_1 == 256 && !(ray.flags & FLG(OBJ_FLIP_X)))
                                        other_obj->field24_0x3e = -1;
                                    else
                                        other_obj->field24_0x3e = 1;
                                }
                                else /* TODO: ??? */
                                    other_obj->field24_0x3e = 1;

                                if (other_obj->main_etat == 0 && other_obj->sub_etat == 0)
                                    skipToLabel(other_obj, 0, true);

                                poing.is_active = false;
                                poing.is_returning = false;
                                poing_obj->flags &= ~FLG(OBJ_ALIVE);
                                poing_obj->flags &= ~FLG(OBJ_ACTIVE);
                                fin_poing_follow(poing_obj, false);
                            }
                        }
                        break;
                    case TYPE_CAISSE_CLAIRE:
                        if (!(other_obj->main_etat == 0 && other_obj->sub_etat == 2))
                        {
                            set_main_and_sub_etat(other_obj, 1, 1);
                            if (!(other_obj->flags & FLG(OBJ_FLIP_X)))
                            {
                                other_obj->flags |= FLG(OBJ_FLIP_X);
                                skipToLabel(other_obj, 3, true);
                            }
                            else
                            {
                                other_obj->flags &= ~FLG(OBJ_FLIP_X);
                                skipToLabel(other_obj, 2, true);
                            }
                        }
                        break;
                    case TYPE_BLACKTOON1:
                        obj_hurt(other_obj);
                        if (other_obj->hit_points == 0)
                        {
                            set_main_and_sub_etat(other_obj, 0, 4);
                            other_obj->speed_y = 0;
                            /* TODO: rewriting this like TYPE_MORNINGSTAR_MOUNTAI didn't work */
                            png_spd_x = poing_obj->speed_x;
                            if (png_spd_x >= 0)
                            {
                                if (png_spd_x > 0)
                                    other_obj->flags &= ~FLG(OBJ_FLIP_X);
                                else /* png_spd_x == 0 */
                                {
                                    if (poing_obj->flags & FLG(OBJ_FLIP_X))
                                        other_obj->flags &= ~FLG(OBJ_FLIP_X);
                                    else
                                        other_obj->flags |= FLG(OBJ_FLIP_X);
                                }
                            }
                            else if (png_spd_x < 0)
                                other_obj->flags |= FLG(OBJ_FLIP_X);

                            allocateBlacktoonEyes(other_obj);
                            if (other_obj->flags & FLG(OBJ_FLIP_X))
                                skipToLabel(other_obj, 2, true);
                            else
                                skipToLabel(other_obj, 3, true);
                            break;
                        }
                        break;
                    case TYPE_MORNINGSTAR_MOUNTAI:
                        if (sprite == 4 && other_obj->sub_etat == 5)
                        {
                            if (poing_obj->speed_x >= 0 && (poing_obj->speed_x > 0 || poing_obj->flags & FLG(OBJ_FLIP_X)))
                                set_sub_etat(other_obj, 9);
                            else
                                set_sub_etat(other_obj, 6);
                        }
                        break;
                    case TYPE_KILLING_EYES:
                        if (--other_obj->hit_points != 0)
                        {
                            set_sub_etat(other_obj, 5);
                            other_obj->iframes_timer = 50;
                        }
                        else
                            set_sub_etat(other_obj, 6);
                        break;
                    case TYPE_PIRATE_GUETTEUR:
                    case TYPE_PIRATE_GUETTEUR2:
                        DO_PAR_POING_COLLISION(other_obj, sprite);
                        break;
                    case TYPE_PIRATE_NGAWE:
                        DO_NGW_POING_COLLISION(other_obj);
                        break;
                    case TYPE_CAGE:
                        obj_hurt(other_obj);
                        if (other_obj->hit_points == 0)
                        {
                            other_obj->init_main_etat = 0;
                            other_obj->init_sub_etat = 8;
                            other_obj->init_x_pos = other_obj->x_pos;
                            other_obj->init_y_pos = other_obj->y_pos;
                            set_sub_etat(other_obj, 12);
                            other_obj->init_flag = 7;
                            ALLOCATE_MEDAILLON_TOON();
                            lidol_to_allocate = 5;
                            lidol_source_obj = other_obj;
                            Nb_total_cages++;
                            take_bonus(other_obj->id);
                        }
                        else
                            set_sub_etat(other_obj, 10);
                        break;
                    case TYPE_BB1:
                        if (sprite == 9)
                            DO_BBMONT_TOUCHE(other_obj);
                        break;
                    case TYPE_NOTE0:
                    case TYPE_NOTE1:
                    case TYPE_NOTE2:
                    case TYPE_BONNE_NOTE:
                    case TYPE_NOTE3:
                        DO_NOTE_TOUCHEE(other_obj);
                        break;
                    case TYPE_TOTEM:
                        DO_TOTEM_TOUCHE(other_obj, sprite);
                        break;
                    case TYPE_PI_MUS:
                        if (other_obj->main_etat == 0 && Mus_obj_id >= 0)
                        {
                            PlaySnd(83, other_obj->id);
                            other_obj->hit_points--;
                            switch (other_obj->hit_points)
                            {
                            case 3:
                                set_sub_etat(other_obj, 4);
                                allocateEclatPS(other_obj, 7);
                                set_sub_etat(&level.objects[Mus_obj_id], 6);
                                break;
                            case 2:
                                set_sub_etat(other_obj, 6);
                                allocateEclatPS(other_obj, 8);
                                break;
                            case 1:
                                set_sub_etat(other_obj, 8);
                                allocateEclatPS(other_obj, 9);
                                break;
                            case 0:
                                if (level.objects[Mus_obj_id].sub_etat == 6)
                                {
                                    PlaySnd(83, other_obj->id);
                                    set_sub_etat(other_obj, 9);
                                    level.objects[Mus_obj_id].sub_etat = 3;
                                    level.objects[Mus_obj_id].init_sub_etat = 4;
                                    other_obj->init_sub_etat = 10;
                                }
                                break;
                            }
                        }
                        break;
                    case TYPE_PI:
                        if (other_obj->main_etat == 0)
                        {
                            obj_hurt(other_obj);
                            if (other_obj->hit_points == 0)
                            {
                                DO_PI_EXPLOSION(other_obj);
                                other_obj->flags &= ~FLG(OBJ_ACTIVE);
                                if (ray.field20_0x36 == other_obj->id)
                                {
                                    ray.field20_0x36 = -1;
                                    other_obj->ray_dist = 1000;
                                    set_main_and_sub_etat(&ray, 2, 2);
                                }
                                other_obj->flags &= ~FLG(OBJ_ALIVE);
                            }
                            else
                            {
                                set_sub_etat(other_obj, 1);
                                other_obj->anim_frame = 0;
                            }
                        }
                        break;
                    case TYPE_LEVIER:
                        DO_LEV_POING_COLLISION(other_obj);
                        break;
                    case TYPE_SPIDER:
                        obj_hurt(other_obj);
                        if (other_obj->hit_points == 0)
                        {
                            set_main_and_sub_etat(other_obj, 0, 7);
                            other_obj->anim_frame = 0;
                            other_obj->flags &= ~FLG(OBJ_READ_CMDS);
                        }
                        else
                        {
                            if (
                                other_obj->main_etat == 0 &&
                                (other_obj->sub_etat == 2 || other_obj->sub_etat == 3 ||
                                other_obj->sub_etat == 4 || other_obj->sub_etat == 5)
                            )
                                other_obj->cmd_context_index = 0xFF;

                            other_obj->field23_0x3c = 0;
                            if (level.objects[poing_obj_id].speed_x > 0)
                            {
                                skipToLabel(other_obj, 3, true);
                                other_obj->flags |= FLG(OBJ_FLIP_X);
                            }
                            else
                            {
                                skipToLabel(other_obj, 1, true);
                                other_obj->flags &= ~FLG(OBJ_FLIP_X);
                            }
                            pushToLabel(other_obj, 6, true);
                            other_obj->anim_frame = 0;
                            pushToLabel(other_obj, 7, true);
                        }
                        break;
                    case TYPE_STONEDOG:
                    case TYPE_STONEDOG2:
                        obj_hurt(other_obj);
                        if (other_obj->hit_points != 0)
                        {
                            skipToLabel(other_obj, 5, true);
                            other_obj->gravity_value_2 = 7;
                            other_obj->change_anim_mode = ANIMMODE_RESET;
                            if (poing_obj->speed_x > 0)
                                other_obj->flags &= ~FLG(OBJ_FLIP_X);
                            else if (poing_obj->speed_x < 0)
                                other_obj->flags |= FLG(OBJ_FLIP_X);
                        }
                        else
                        {
                            set_main_and_sub_etat(other_obj, 0, 3);
                            other_obj->flags &= ~FLG(OBJ_READ_CMDS);
                        }
                        break;
                    case TYPE_STONEBOMB:
                    case TYPE_STONEBOMB2:
                    case TYPE_STONEBOMB3:
                        set_sub_etat(other_obj, 1);
                        DO_STONE_EXPLOSION(other_obj);
                        break;
                    case TYPE_STONEMAN1:
                    case TYPE_STONEMAN2:
                        DO_PNG_COLL_STONEMAN(other_obj);
                        break;
                    case TYPE_STONEWOMAN2:
                    case TYPE_STONEWOMAN:
                        DO_PNG_COLL_STONEWOMAN(other_obj);
                        break;
                    case TYPE_PLATFORM:
                        if (sprite == other_obj->hit_sprite) /* tempted to rename "sprite" */
                        {
                            if (poing_obj->speed_x > 0)
                                set_sub_etat(other_obj, 25);
                            else if (poing_obj->speed_x < 0)
                                set_sub_etat(other_obj, 26);
                        }
                        break;
                    case TYPE_FALLING_OBJ:
                    case TYPE_FALLING_OBJ2:
                    case TYPE_FALLING_OBJ3:
                    case TYPE_FALLING_YING:
                    case TYPE_FALLING_YING_OUYE:
                        switch (other_obj->type)
                        {
                        case TYPE_FALLING_OBJ:
                        case TYPE_FALLING_OBJ2:
                        case TYPE_FALLING_OBJ3:
                            PlaySnd(44, other_obj->id);
                            break;
                        case TYPE_FALLING_YING:
                        case TYPE_FALLING_YING_OUYE:
                            PlaySnd(139, other_obj->id);
                            break;
                        }

                        switch (poing.sub_etat)
                        {
                        case 1:
                        case 3:
                        case 5:
                            fall_x_accel = poing.damage;
                            break;
                        case 8:
                        case 10:
                        case 12:
                            fall_x_accel = poing.damage - 2;
                        case 2:
                        case 4:
                        case 6:
                        case 7:
                        case 9:
                        case 11:
                            break;
                        }
                        fall_x_accel = fall_x_accel * 5 + 10;
                        if (poing_obj->speed_x < 0)
                            fall_x_accel = -fall_x_accel;

                        make_my_fruit_go_down(other_obj, fall_x_accel);
                        break;
                    case TYPE_TARZAN:
                        set_main_and_sub_etat(other_obj, 0, 1);
                        other_obj->cmd = GO_LEFT;
                        break;
                    case TYPE_GENEBADGUY:
                        if (sprite == 0)
                        {
                            poing.damage = 1;
                            obj_hurt(other_obj);
                            if (other_obj->hit_points == 0)
                                skipToLabel(other_obj, 4, true);
                            else
                                skipToLabel(other_obj, 3, true);
                        }
                        else
                            skipToLabel(other_obj, 2, true);
                        break;
                    case TYPE_CHASSEUR1:
                    case TYPE_CHASSEUR2:
                        if (other_obj->eta[other_obj->main_etat][other_obj->sub_etat].flags & 1)
                        {
                    case TYPE_FISH: /* TODO: kinda gross fall-through? */
                            obj_hurt(other_obj);
                            if (other_obj->hit_points != 0)
                            {
                                other_obj->speed_x = 0;
                                other_obj->speed_y = 0;
                                set_main_and_sub_etat(other_obj, 0, 1);
                            }
                            else
                                set_main_and_sub_etat(other_obj, 0, 3);

                            if (other_obj->type == TYPE_FISH)
                                DESACTIVE_FISH_COLLIS(other_obj);

                            if (!(other_obj->flags & FLG(OBJ_FLIP_X)))
                                other_obj->cmd = GO_LEFT;
                            else
                                other_obj->cmd = GO_RIGHT;
                        }
                        break;
                    case TYPE_BADGUY2:
                    case TYPE_BADGUY3:
                        if (
                            (sprite == 0xFF) ||
                            (other_obj->eta[other_obj->main_etat][other_obj->sub_etat].flags & FLG(0))
                        )
                        {
                            obj_hurt(other_obj);
                            if (other_obj->hit_points == 0)
                            {
                                set_main_and_sub_etat(other_obj, 0, 3);
                                skipToLabel(other_obj, 2, true);
                                other_obj->y_pos -= 2;
                                other_obj->flags &= ~FLG(OBJ_READ_CMDS);
                            }
                            else
                            {
                                if (poing_obj->flags & FLG(OBJ_FLIP_X))
                                {
                                    if (poing_obj->speed_x >= 0)
                                        skipToLabel(other_obj, 3, true);
                                    else if (poing_obj->speed_x < -1)
                                        skipToLabel(other_obj, 2, true);
                                }
                                else
                                {
                                    if (poing_obj->speed_x >= 2)
                                        skipToLabel(other_obj, 3, true);
                                    else if (poing_obj->speed_x <= 0)
                                        skipToLabel(other_obj, 2, true);
                                }
                                other_obj->speed_x = 0;
                                other_obj->speed_y = -4;
                                other_obj->y_pos -= 2;
                                set_main_and_sub_etat(other_obj, 2, 2);
                                PlaySnd(28, other_obj->id);
                            }
                        }
                        break;
                    case TYPE_BADGUY1:
                        obj_hurt(other_obj);
                        if (poing_obj->speed_x > 0)
                            skipToLabel(other_obj, 3, true);
                        else if (poing_obj->speed_x < 0)
                            skipToLabel(other_obj, 2, true);

                        other_obj->speed_x = 0;
                        other_obj->y_pos -= 2;
                        if (other_obj->hit_points != 0)
                        {
                            other_obj->speed_y = -4;
                            if (other_obj->eta[other_obj->main_etat][other_obj->sub_etat].flags & 0x40)
                                sub_etat = 10;
                            else
                                sub_etat = 2;
                            set_main_and_sub_etat(other_obj, 2, sub_etat);
                            PlaySnd(28, other_obj->id);
                        }
                        else
                        {
                            other_obj->speed_y = -8;
                            if (other_obj->eta[other_obj->main_etat][other_obj->sub_etat].flags & 0x40)
                                sub_etat = 6;
                            else
                                sub_etat = 3;
                            set_main_and_sub_etat(other_obj, 0, sub_etat);
                        }
                        break;
                    case TYPE_TROMPETTE:
                        obj_hurt(other_obj);
                        if (poing_obj->speed_x > 0)
                            other_obj->flags &= ~FLG(OBJ_FLIP_X);
                        else if (poing_obj->speed_x < 0)
                            other_obj->flags |= FLG(OBJ_FLIP_X);

                        if (other_obj->hit_points == 0)
                        {
                            set_main_and_sub_etat(other_obj, 0, 1);
                            other_obj->flags &= ~FLG(OBJ_READ_CMDS);
                            other_obj->cmd = GO_WAIT;
                        }
                        else
                        {
                            other_obj->y_pos -= 2;
                            skipToLabel(other_obj, 4, true);
                        }
                        break;
                    case TYPE_BIG_CLOWN:
                    case TYPE_WAT_CLOWN:
                        obj_hurt(other_obj);
                        if (poing_obj->speed_x > 0)
                            other_obj->flags &= ~FLG(OBJ_FLIP_X);
                        else if (poing_obj->speed_x < 0)
                            other_obj->flags |= FLG(OBJ_FLIP_X);

                        if (other_obj->hit_points != 0)
                        {
                            other_obj->y_pos -= 2;
                            skipToLabel(other_obj, 4, true);
                        }
                        else
                        {
                            set_main_and_sub_etat(other_obj, 0, 3);
                            other_obj->flags &= ~FLG(OBJ_READ_CMDS);
                            other_obj->cmd = GO_LEFT;
                        }
                        break;
                    case TYPE_CLOWN_TNT:
                    case TYPE_CLOWN_TNT2:
                    case TYPE_CLOWN_TNT3:
                        obj_hurt(other_obj);
                        if (poing_obj->speed_x > 0)
                            other_obj->flags &= ~FLG(OBJ_FLIP_X);
                        else if (poing_obj->speed_x < 0)
                            other_obj->flags |= FLG(OBJ_FLIP_X);

                        if (other_obj->hit_points != 0)
                        {
                            if (!(other_obj->flags & FLG(OBJ_FLIP_X)))
                                label = 6;
                            else
                                label = 5;
                            skipToLabel(other_obj, label, true);
                        }
                        else
                        {
                            set_main_and_sub_etat(other_obj, 0, 2);
                            other_obj->flags &= ~FLG(OBJ_READ_CMDS);
                        }
                        break;
                    case TYPE_MITE2:
                        if (sprite == 1)
                        {
                            if (poing_obj->speed_x > 0)
                                other_obj->flags &= ~FLG(OBJ_FLIP_X);
                            else if (poing_obj->speed_x < 0)
                                other_obj->flags |= FLG(OBJ_FLIP_X);
                        }
                    case TYPE_MITE:
                        if (sprite == 1)
                        {
                            obj_hurt(other_obj);
                            if (other_obj->hit_points != 0)
                                skipToLabel(other_obj, 4, true);
                            else
                            {
                                set_main_and_sub_etat(other_obj, 0, 3);
                                other_obj->flags &= ~FLG(OBJ_READ_CMDS);
                            }
                        }
                        break;
                    case TYPE_SCORPION:
                        DO_SKO_HIT(other_obj);
                        break;
                    case TYPE_PIRATE_POELLE:
                    case TYPE_PIRATE_POELLE_D:
                    case TYPE_PIRATE_P_45:
                    case TYPE_PIRATE_P_D_45:
                        DO_PIRATE_POELLE_POING_COLLISION(other_obj);
                        break;
                    case TYPE_HYB_BBF2_D:
                    case TYPE_HYB_BBF2_G:
                        DO_HYB_BBF2_POING_COLLISION(other_obj);
                        break;
                    case TYPE_SPIDER_PLAFOND:
                        DO_SPIDER_PLAFOND_POING_COLLISION(other_obj);
                        break;
                    case TYPE_PRI:
                        if (
                            other_obj->screen_x_pos < poing_obj->screen_x_pos + 30 &&
                            other_obj->main_etat == 0 && other_obj->sub_etat == 0
                        )
                        {
                            skipToLabel(other_obj, 2, true);
                            other_obj->init_sub_etat = 2;
                            prise_branchee = true;
                            finBosslevel.helped_joe_2 = true;
                        }
                        break;
                    case TYPE_POI3:
                        if (!(other_obj->main_etat == 2 && other_obj->sub_etat == 18))
                        {
                            skipToLabel(other_obj, 12, true);
                            other_obj->speed_x = 0;
                            other_obj->speed_y = 0;
                            other_obj->hit_points = 0;
                        }
                        break;
                    case TYPE_PETIT_COUTEAU:
                        if (other_obj->hit_points == 2 || other_obj->hit_points == 4)
                            other_obj->hit_points--;
                        break;
                    }
                    do_boum();
                    other_obj->gravity_value_1 = 0;
                    /* TODO: unk_1 is strange (see other use above) */
                    unk_1 = other_obj->eta[other_obj->main_etat][other_obj->sub_etat].anim_speed >> 4;
                    if (!(unk_1 == 10 || unk_1 == 11))
                        other_obj->gravity_value_2 = 0;

                    if (other_obj->hit_points == old_hp && (flags[other_obj->type].flags3 & FLG(OBJ3_POING_COLLISION_SND)))
                        PlaySnd(214, other_obj->id);
                    break;
                }
            }
            i++;
            other_obj = &level.objects[actobj.objects[i]];
        }
    }
}
#endif

/* 1F06C 8014386C -O2 -msoft-float */
s32 COLL_BOX_ALL_SPRITES(s16 in_x, s16 in_y, s16 in_w, s16 in_h, Obj *obj)
{
    s16 i;
    s16 spr_x; s16 spr_y; s16 spr_w; s16 spr_h;
    s16 res;

    for (i = 0; i < (obj->animations[obj->anim_index].layers_count & 0x3FFF); i++)
    {
        GET_SPRITE_POS(obj, i, &spr_x, &spr_y, &spr_w, &spr_h);
        if (inter_box(in_x, in_y, in_w, in_h, spr_x, spr_y, spr_w, spr_h))
        {
            res = i;
            break;
        }
    }
    return res;
}

/* 0xFC00, 0x2000 usages? macro? */
/* 1F1B4 801439B4 -O2 -msoft-float */
s16 COLL_RAY_PIC(void)
{
    s32 ray_dist;
    s32 unk_1;
    s32 unk_2;
    s32 unk_3;
    s32 unk_4;
    s32 unk_5;
    s16 res = false;

    if ((ray.y_pos + ray.offset_by) < (mp.height * 16))
    {
        ray_dist = ray.ray_dist;
        if (ray.field20_0x36 == -1)
            res = (mp.map[ray_dist] & 0xFC00) == 0x2000;
        if (!res)
        {
            unk_1 = ray_dist - mp.width;
            res = (mp.map[unk_1] & 0xFC00) == 0x2000;
            if (!res)
            {
                unk_2 = unk_1 + 1;
                unk_3 = unk_1 - 1;
                if (ray.main_etat != 2 || ray.speed_x != 0)
                {
                    res = false;
                    if (
                        (mp.map[unk_3] & 0xFC00) == 0x2000 ||
                        (mp.map[unk_2] & 0xFC00) == 0x2000
                    )
                        res = true;
                }

                if (
                    !res && !(RayEvts.demi) &&
                    !(ray.eta[ray.main_etat][ray.sub_etat].flags & 0x40)
                )
                {
                    unk_4 = unk_1 - mp.width;
                    unk_5 = unk_4 - mp.width;
                    while (unk_5 < 0)
                        unk_5 += mp.width;
                    while (unk_4 < 0)
                        unk_4 += mp.width;
                    res = false;
                    if (
                        (mp.map[unk_5] & 0xFC00) == 0x2000 ||
                        (mp.map[unk_4] & 0xFC00) == 0x2000
                    )
                        res = true;
                }
            }
        }
    }
    return res;
}

/* 1F3D0 80143BD0 -O2 -msoft-float */
void COLL_RAY_BLK_MORTEL(void)
{
    u16 mp_map;

    if ((ray.y_pos + ray.offset_by) < (mp.height * 16))
    {
        mp_map = mp.map[ray.ray_dist] & 0xfc00;
        if (mp_map == 0x6000)
        {
            set_main_and_sub_etat(&ray, 3, 32);
            dead_time = 1;
            ray.speed_y = 0;
            ray.speed_x = 0;
            ray.y_pos += 5;
            stop_all_snd();
        }
        else if (ray.btypes[3] == BTYP_SPIKES)
        {
            set_main_and_sub_etat(&ray, 3, 32);
            dead_time = 1;
            ray.speed_y = 0;
            ray.speed_x = 0;
            stop_all_snd();
        }
        else if (mp_map == 0x6400)
        {
            set_main_and_sub_etat(&ray, 2, 31);
            scroll_end_y = ymap;
            scroll_start_y = ymap;
        }
        else if (
            RayEvts.unused_death &&
            block_flags[mp.map[ray.ray_dist] >> 10] >> BLOCK_SOLID & 1 &&
            !(ray.main_etat == 3 && ray.sub_etat == 38)
        )
        {
            set_main_and_sub_etat(&ray, 3, 38);
            dead_time = 1;
            ray.speed_y = 0;
            ray.speed_x = 0;
        }
    }
}

/* 1F5B0 80143DB0 -O2 -msoft-float */
void RAY_KO(void)
{
    set_main_and_sub_etat(&ray, 3, 0);
    ray.speed_y = 0;
    ray.speed_x = 0;
    ray.field56_0x69 = 0;
}

/* 1F5F4 80143DF4 -O2 -msoft-float */
void RAY_HIT(u8 hurt, Obj *obj)
{
    u16 ray_x_pos;
    s16 ray_offset_bx;
    u8 typ_trav;
    ObjType obj_type;
    s16 eject_sens;
    s32 diff_spd_x;
    s16 new_speed;

    if (hurt)
    {
        RAY_HURT();
        ray_x_pos = ray.x_pos;
        ray_offset_bx = ray.offset_bx;
    /* not sure how to change into cast... */
        while ((s16) BTYP((ray_offset_bx + ray_x_pos) << 0x10 >> 0x10, ray.y_pos + ray.offset_by) == BTYP_WATER)
            ray.y_pos--;
        ray.btypes[0] = BTYP_NONE;
    }

    if (ray.main_etat == 6)
    {
        set_main_and_sub_etat(&ray, 6, 8);
        ray.speed_y = 0;
        ray.speed_x = 0;
        poing.is_charging = false;
    }
    else if (
        ray.flags & FLG(OBJ_ALIVE) &&
        !(ray.main_etat == 3 && (ray.sub_etat == 22 || ray.sub_etat == 32 || ray.sub_etat == 38)) &&
        !(ray.main_etat == 2 && ray.sub_etat == 31)
    )
    {
        if (
            ray.eta[ray.main_etat][ray.sub_etat].flags & 0x40 &&
            (typ_trav = calc_typ_trav(&ray, 2), block_flags[typ_trav] >> BLOCK_FLAG_4 & 1)
        )
            set_main_and_sub_etat(&ray, 0, 61);
        else
            set_main_and_sub_etat(&ray, 2, 8);

        ray_speed_inv = 0;
        if (!obj && !(ray.main_etat == 0 && ray.sub_etat == 61))
        {
            if (ray.flags & FLG(OBJ_FLIP_X))
                ray.speed_x = -2;
            else
                ray.speed_x = 2;
            ray.speed_y = -3;
        }
        else if (!(ray.main_etat == 0 && ray.sub_etat == 61))
        {
            obj_type = obj->type;
            if (obj_type == TYPE_SAXO2)
                eject_sens = saxo2_get_eject_sens();
            else if (obj_type == TYPE_SCORPION)
                eject_sens = sko_get_eject_sens();
            else if (obj_type == TYPE_BB12)
                eject_sens = 1;
            else if (obj_type == TYPE_BB13)
                eject_sens = -1;
            else if (obj_type == TYPE_MITE)
            {
                if (obj->flags & FLG(OBJ_FLIP_X))
                    eject_sens = 1;
                else
                    eject_sens = -1;
            }
            else if (obj_type == TYPE_BATTEUR_FOU)
                eject_sens = bat_get_eject_sens(obj);
            else if (obj_type == TYPE_MAMA_PIRATE)
                eject_sens = pma_get_eject_sens(obj);
            else if (obj_type == TYPE_FIRE_LEFT)
                eject_sens = 1;
            else if (obj_type == TYPE_FIRE_RIGHT)
                eject_sens = -1;
            else
            {
        /* sgn() call on android */
                diff_spd_x = obj->speed_x - ray.speed_x;
                if (diff_spd_x >= 0)
                    eject_sens = diff_spd_x > 0;
                else
                    eject_sens = -1;
                if (eject_sens == 0)
                {
                    if (ray.flags & FLG(OBJ_FLIP_X))
                        eject_sens = -1;
                    else
                        eject_sens = 1;
                }
            }

            if (flags[obj->type].flags1 >> OBJ1_BIG_RAY_HIT_KNOCKBACK & 1)
                new_speed = 5;
            else if (obj->type == TYPE_SAXO2)
                new_speed = 4;
            else
                new_speed = 2;

            if (eject_sens == 1)
                ray.speed_x = new_speed;
            else if (eject_sens == -1)
                ray.speed_x = -new_speed;
            ray.speed_y = ~new_speed;
        }

        in_air_because_hit = true;
        jump_time = 0;
        helico_time = -1;
        ray.gravity_value_1 = 0;
        ray.gravity_value_2 = 0;
        ray.field20_0x36 = -1;
        poing.is_charging = false;
        decalage_en_cours = 0;
        ray.nb_cmd = 0;
        if (RayEvts.super_helico)
            button_released = 1;
        Reset_air_speed(false);
    }
}

/* 1FA54 80144254 -O2 -msoft-float */
void standard_frontZone(Obj *obj, s16 *x, s16 *w)
{
    if (!(obj->flags & FLG(OBJ_FLIP_X)))
        *x -= obj->detect_zone;
    else
        *x += (*w >> 1);
    *w = obj->detect_zone + (*w >> 1);
}

/* 1FAB4 801442B4 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/collision/collision", SET_DETECT_ZONE_FLAG);
#else
/* unk_1? */
void SET_DETECT_ZONE_FLAG(Obj *obj)
{
    s16 obj_x; s16 obj_y; s16 obj_w; s16 obj_h;
    s32 unk_1;
    u16 det_zn_flg;

    GET_ANIM_POS(obj, &obj_x, &obj_y, &obj_w, &obj_h);
    switch (obj->type)
    {
    case TYPE_FEE:
        obj_x += (obj_h >> 1) - (obj->detect_zone >> 1);
        obj_y -= 16;
        obj_w = obj->detect_zone;
        obj_h += 64;
        break;
    case TYPE_MST_SHAKY_FRUIT:
        obj_y += obj_h;
        obj_h += 240;
        break;
    case TYPE_PIRATE_GUETTEUR:
    case TYPE_PIRATE_GUETTEUR2:
        standard_frontZone(obj, &obj_x, &obj_w);
        if (obj->main_etat == 0 && obj->sub_etat == 4)
        {
            obj_y += (obj_h >> 1);
            obj_h += (obj->detect_zone << 2) + (obj_h >> 1);
        }
        break;
    case TYPE_BLACKTOON1:
        unk_1 = -1;
        switch (obj->follow_sprite)
        {
        case 3:
            if (obj->main_etat == 0 && obj->sub_etat == 0)
            {
                obj_h += obj->detect_zone;
                obj_y -= obj->detect_zone;
                obj_w += obj->detect_zone;
                obj_x -= (obj->detect_zone >> 1);
            }
            break;
        case 7:
            if (obj->main_etat == 1 && obj->sub_etat == 1)
            {
                obj_x = obj_x + unk_1 + (obj_w >> 1);
                obj_y += (obj_h >> 1);
                obj_w = 20;
                obj_h += obj->detect_zone;
                if (!(obj->flags & FLG(OBJ_FLIP_X)))
                    obj_x -= obj_w;
            }
            break;
        case 4:
            obj_y -= obj->detect_zone + obj_h;
            obj_x -= (obj_w >> 1);
            obj_w += obj_w;
            obj_h += obj->detect_zone;
            break;
        case 2:
            obj_y -= obj->detect_zone + obj_h;
            obj_h = obj->detect_zone + obj_h;
            obj_w += obj->detect_zone * 2;
            obj_x -= obj->detect_zone;
            break;
        }
        break;
    case TYPE_POI3:
        obj_x += (obj->flags & FLG(OBJ_FLIP_X)) ? obj_w : -obj_w;
        obj_y -= 50;
        obj_h += 50;
        break;
    case TYPE_MST_SCROLL:
        if (obj->hit_points != 0)
        {
            obj_y = 0;
            obj_h = mp.height << 4;
        }
        break;
    case TYPE_SCROLL_SAX:
    case TYPE_BB1_VIT:
        obj_x = obj->x_pos + obj->offset_bx;
        obj_w = 16;
        obj_y = 0;
        obj_h = mp.height << 4;
        break;
    case TYPE_WAT_CLOWN:
        obj_h += (obj->detect_zone >> 1);
        obj_y -= (obj->detect_zone >> 1);
        standard_frontZone(obj, &obj_x, &obj_w);
        break;
    case TYPE_CHASSEUR2:
        obj_h = obj->detect_zone;
        obj_y -= (obj->detect_zone >> 1);
        obj_w += obj->detect_zone * 2;
        obj_x -= obj->detect_zone;
        break;
    case TYPE_WIZARD1:
    case TYPE_CHASSEUR1:
    case TYPE_GENEBADGUY:
    case TYPE_CYMBALE:
    case TYPE_CYMBAL1:
    case TYPE_CYMBAL2:
        obj_w += obj->detect_zone * 2;
        obj_x -= obj->detect_zone;
        break;
    case TYPE_CLOWN_TNT:
        if (!(obj->flags & FLG(OBJ_FLIP_X)))
            obj_x += (obj_w >> 1) - (obj->detect_zone >> 1);
        else
            obj_x += (obj_w >> 1);

        obj_w = (obj->detect_zone >> 1);
        obj_y += (obj_h >> 1);
        obj_h = (obj_h >> 1) + obj->detect_zone;
        break;
    case TYPE_STONEWOMAN:
    case TYPE_STONEWOMAN2:
        standard_frontZone(obj, &obj_x, &obj_w);
        obj_h = (obj_h << 1);
        break;
    case TYPE_MITE:
        unk_1 = 150;
        if (!(obj->flags & FLG(OBJ_FLIP_X)))
            obj_x -= obj->detect_zone;
        else
            obj_x = obj_x + -unk_1 + (obj_w >> 1);

        obj_w = obj->detect_zone + unk_1;
        obj_y -= ((obj->detect_zone - obj_h) >> 1);
        obj_h = obj->detect_zone;
        break;
    case TYPE_PIRATE_POELLE:
    case TYPE_PIRATE_P_45:
        standard_frontZone(obj, &obj_x, &obj_w);
        obj_h = 150;
        break;
    case TYPE_PIRATE_POELLE_D:
    case TYPE_PIRATE_P_D_45:
        standard_frontZone(obj, &obj_x, &obj_w);
        obj_h = 150;
        obj_x += 70;
        obj_y += 50;
        break;
    case TYPE_SPIDER_PLAFOND:
        if (
            (
                obj->main_etat == 0 &&
                (obj->sub_etat == 24 || obj->sub_etat == 30 || obj->sub_etat == 11)
            ) ||
            (obj->main_etat == 1 && obj->sub_etat == 2)
        )
        {
            obj_h = 10;
            obj_x -= 40;
            obj_w += 80;
        }
        else
        {
            obj_h = 200;
            obj_x -= 130;
            obj_w += 260;
        }
        break;
    case TYPE_DARK:
        standard_frontZone(obj, &obj_x, &obj_w);
        obj_h = 250;
        break;
    case TYPE_JOE:
        obj_h += 20;
        break;
    case TYPE_PHOTOGRAPHE:
        break;
    default:
        standard_frontZone(obj, &obj_x, &obj_w);
        break;
    }

    if (inter_box(obj_x, obj_y, obj_w, obj_h, ray_zdc_x, ray_zdc_y, ray_zdc_w, ray_zdc_h))
    {
        det_zn_flg = obj->detect_zone_flag;
        if (det_zn_flg == 0 || det_zn_flg == 1)
        {
            if (det_zn_flg == 0)
                obj->detect_zone_flag = 1;
            else if (det_zn_flg == 1)
                obj->detect_zone_flag = 2;
        }
        else
        {
            obj->detect_zone_flag++;
            if (obj->detect_zone_flag == 20)
                obj->detect_zone_flag = 2;
        }
    }
    else
    {
        obj->detect_zone_flag = 0;
        if (obj->type == TYPE_PHOTOGRAPHE)
            obj->flags &= ~FLG(OBJ_FLAG_0);
    }
}
#endif

/* 201D8 801449D8 -O2 -msoft-float */
void goToRay(Obj *obj)
{
    s32 follow_sprite;

    PlaySnd(204, obj->id);
    switch (obj->type)
    {
    case TYPE_STALAG:
        if (obj->sub_etat == 4)
            calc_obj_dir(obj);
        else
            obj->flags &= ~FLG(OBJ_FLIP_X);
        break;
    case TYPE_PLATFORM:
    case TYPE_FALLPLAT:
    case TYPE_LIFTPLAT:
    case TYPE_MOVE_PLAT:
    case TYPE_INST_PLAT:
    case TYPE_CRUMBLE_PLAT:
    case TYPE_BOING_PLAT:
    case TYPE_ONOFF_PLAT:
    case TYPE_AUTOJUMP_PLAT:
    case TYPE_OUYE:
    case TYPE_SIGNPOST:
    case TYPE_MOVE_OUYE:
    case TYPE_STONEBOMB2:
    case TYPE_CAGE:
    case TYPE_MOVE_START_NUA:
    case TYPE_BIG_BOING_PLAT:
    case TYPE_STONEBOMB3:
    case TYPE_JAUGEUP:
    case TYPE_MORNINGSTAR_MOUNTAI:
    case TYPE_MARTEAU:
    case TYPE_MOVE_MARTEAU:
    case TYPE_GROSPIC:
    case TYPE_PI:
    case TYPE_ONEUP:
    case TYPE_KILLING_EYES:
    case TYPE_RUBIS:
    case TYPE_MARK_AUTOJUMP_PLAT:
        obj->flags &= ~FLG(OBJ_FLIP_X);
        break;
    case TYPE_BADGUY1:
    case TYPE_BADGUY2:
    case TYPE_BADGUY3:
        calc_obj_dir(obj);
        if (obj->flags & FLG(OBJ_FLIP_X))
            skipToLabel(obj, 3, true);
        else
            skipToLabel(obj, 2, true);
        break;
    case TYPE_BLACKTOON1:
        follow_sprite = obj->follow_sprite;
        if (
            follow_sprite < 2 ||
            (follow_sprite >= 4 && ((s16) follow_sprite >= 8 || follow_sprite < 6))
        )
        {
            calc_obj_dir(obj);
            if (obj->flags & FLG(OBJ_FLIP_X))
                skipToLabel(obj, 3, true);
            else
                skipToLabel(obj, 2, true);
        }
        break;
    case TYPE_BIG_CLOWN:
        calc_obj_dir(obj);
        skipToLabel(obj, 7, true);
        break;
    default:
        calc_obj_dir(obj);
        break;
    }
}

/* 20304 80144B04 -O2 -msoft-float */
void unleashMonsterHost(Obj *in_obj)
{
    Obj *linked_obj;
    s16 prev_id;
    s16 linked_id = in_obj->field24_0x3e;

    if (linked_id != in_obj->id)
    {
        do
        {
            linked_obj = &level.objects[linked_id];
            if (!((flags[linked_obj->type].flags1 >> OBJ1_BONUS & 1) && ((u8) bonus_taken(linked_obj->id))))
            {
                obj_init(linked_obj);
                linked_obj->flags |= FLG(OBJ_ALIVE);
                make_active(linked_obj, true);
                goToRay(linked_obj);
            }
            prev_id = linked_id;
            linked_id = link_init[linked_obj->id];
            suppressFromLinkList(linked_obj);
        } while (prev_id != linked_id);
    }
}

/* 20400 80144C00 -O2 -msoft-float */
void DO_COLL_RAY_CYMBALE(Obj *cym_obj)
{
    s32 cym_sub_etat;
    u8 cym_link_id;
    Obj *cym_link_obj;
    s16 *cym_speed_y;
    s16 ray_speed_y;
    s16 diff_x;
    s16 sprite = 0; /* i think, BOX_IN_COLL_ZONES returned a sprite? */

    if (cym_obj->type == TYPE_CYMBAL2)
    {
        cym_sub_etat = 10;
        cym_link_id = link_init[cym_obj->id];
        if (cym_link_id != cym_obj->id)
        {
            cym_link_obj = &level.objects[cym_link_id];
            if (cym_link_obj->type == TYPE_CYMBAL1)
            {
                cym_speed_y = &cym_link_obj->speed_y;
                if (*cym_speed_y > 128)
                    *cym_speed_y = 1;
                else if (*cym_speed_y < -128)
                    *cym_speed_y = -1;
                cym_link_obj->y_pos += (u16) cym_link_obj->speed_y * 2;
                sprite = BOX_IN_COLL_ZONES(TYPE_RAYMAN, ray_zdc_x, ray_zdc_y, ray_zdc_w, ray_zdc_h, cym_link_obj);
                cym_link_obj->y_pos -= (u16) cym_link_obj->speed_y * 2;
                ray_speed_y = (u16) cym_link_obj->speed_y * 2;
            }
        }
    }
    else
    {
        sprite = BOX_IN_COLL_ZONES(TYPE_RAYMAN, ray_zdc_x, ray_zdc_y, ray_zdc_w, ray_zdc_h, cym_obj);
        cym_sub_etat = 1;
        ray_speed_y = cym_obj->speed_y;
    }
    if (sprite != -1)
    {
        sprite--;
        if (ray.main_etat == 2 && !(ray.sub_etat == 1 || ray.sub_etat == 2))
        {
            if (ray.sub_etat != 8)
                set_sub_etat(&ray, 1);

            if (ray_speed_y > 128)
                ray_speed_y = 1;
            else if (ray_speed_y < -128)
                ray_speed_y = -1;
            ray.y_pos += ray_speed_y;
            ray.field24_0x3e = 0;
            ray.speed_y = 0;
        }

        if (!(ray.main_etat == 2 && ray.sub_etat == 8))
        {
            if (
                !(ray.main_etat == 0 && ray.sub_etat == 61) &&
                cym_obj->anim_frame >= 20 && cym_obj->anim_frame <= 22 &&
                cym_obj->main_etat == 0 && cym_obj->sub_etat == cym_sub_etat
            )
            {
                if (
                    (cym_obj->follow_sprite == 1 || sprite == 1) &&
                    ray.flags & FLG(OBJ_ALIVE) &&
                    !(ray.main_etat == 2 && ray.sub_etat == 8) &&
                    !(ray.main_etat == 0 && ray.sub_etat == 61)
                )
                {
                    diff_x = ray.x_pos + ray.offset_bx - cym_obj->x_pos - cym_obj->offset_bx;
                    if (__builtin_abs(diff_x) < 25)
                    {
                        ray.speed_x = 0;
                        ray.speed_y = 0;
                        decalage_en_cours = 0;
                        ray.flags &= ~FLG(OBJ_ACTIVE);
                        ray.iframes_timer = -1;
                        set_main_and_sub_etat(&ray, 0, 0);
                        ray.field20_0x36 = cym_obj->id;
                    }
                    else
                    {
                        if (diff_x < 0)
                            ray.flags |= FLG(OBJ_FLIP_X);
                        else
                            ray.flags &= ~FLG(OBJ_FLIP_X);
                        RAY_HIT(true, cym_obj);
                    }
                }
                else
                {
                    if (cym_obj->follow_sprite == 0 || sprite == 0)
                        ray.flags |= FLG(OBJ_FLIP_X);
                    else
                        ray.flags &= ~FLG(OBJ_FLIP_X);
                    RAY_HIT(true, cym_obj);
                }
            }
        }
    }
}

/* 2081C 8014501C -O2 -msoft-float */
void DoAudioStartRaymanCollision(Obj *obj)
{
    manage_snd_event(obj);
}

/* 2083C 8014503C -O2 -msoft-float */
/*void DO_NOVA(Obj *obj);
int NOVA_STATUS_BAR(void);
void restoreGameState(SaveState *save);
void set_SNSEQ_list(short param_1);*/

void PS1_DoRaymanCollision(void)
{
    ObjType type;
    s16 unk_1;
    s16 ray_iframes;
    s16 i = 0;
    Obj *cur_obj = &level.objects[actobj.objects[0]];

    while (i < actobj.num_active_objects)
    {
        type = cur_obj->type;
        if (
            flags[type].flags2 >> OBJ2_DO_NOT_CHECK_RAY_COLLISION & 1 &&
            cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].flags & FLG(5) &&
            !(ray.main_etat == 3 && ray.sub_etat == 32)
        )
        {
            if (type == TYPE_CYMBALE || type == TYPE_CYMBAL2)
                unk_1 = 0;
            else
                unk_1 = CHECK_BOX_COLLISION(
                    TYPE_RAYMAN,
                    ray_zdc_x, ray_zdc_y, ray_zdc_w, ray_zdc_h,
                    cur_obj
                );
            if (unk_1 != -1)
            {
                switch (cur_obj->type)
                {
                case TYPE_AUDIOSTART:
                    DoAudioStartRaymanCollision(cur_obj);
                    break;
                case TYPE_WIZ:
                    PlaySnd(14, cur_obj->id);
                    set_sub_etat(cur_obj, 23);
                    if (bonus_map)
                    {
                        nb_wiz--;
                        nb_wiz_collected++;
                        status_bar.num_wiz = nb_wiz_collected;
                        if (nb_wiz == 0)
                        {
                            loop_time = -32;
                            INIT_FADE_OUT();
                        }
                    }
                    else
                        status_bar.num_wiz++;

                    if (status_bar.num_wiz >= 100)
                    {
                        DO_NOVA(cur_obj);
                        if (bonus_map)
                            id_Cling_1up = -1;
                        else
                            id_Cling_1up = NOVA_STATUS_BAR();

                        if (id_Cling_1up == -1)
                            Add_One_RAY_lives();
                        life_becoz_wiz = true;
                        status_bar.num_wiz -= 100;
                    }
                    start_pix_gerbe(cur_obj->screen_x_pos + 10, cur_obj->screen_y_pos + 10);
                    break;
                case TYPE_ONEUP:
                    DO_NOVA(cur_obj);
                    PlaySnd(194, cur_obj->id);
                    if (id_Cling_1up != -1)
                    {
                        Add_One_RAY_lives();
                        level.objects[id_Cling_1up].flags &= ~FLG(OBJ_ALIVE);
                    }
                    id_Cling_1up = NOVA_STATUS_BAR();
                    if (id_Cling_1up == -1)
                        Add_One_RAY_lives();
                    cur_obj->flags &= ~FLG(OBJ_ALIVE);
                    take_bonus(cur_obj->id);
                    break;
                case TYPE_JAUGEUP:
                    DO_NOVA(cur_obj);
                    if (id_Cling_Pow != -1)
                    {
                        status_bar.max_hp = ray.hit_points = 4;
                        level.objects[id_Cling_Pow].flags &= ~FLG(OBJ_ALIVE);
                    }
                    id_Cling_Pow = NOVA_STATUS_BAR();
                    if (id_Cling_Pow == -1)
                        status_bar.max_hp = ray.hit_points = 4;
                    cur_obj->flags &= ~FLG(OBJ_ALIVE);
                    PlaySnd(12, cur_obj->id);
                    break;
                case TYPE_NEIGE:
                    cur_obj->flags &= ~FLG(OBJ_ALIVE);
                    switch (cur_obj->sub_etat)
                    {
                    case 32:
                        set_SNSEQ_list(0);
                        break;
                    case 21:
                        set_SNSEQ_list(1);
                        break;
                    case 22:
                        set_SNSEQ_list(2);
                        break;
                    case 23:
                        set_SNSEQ_list(3);
                        break;
                    case 24:
                        set_SNSEQ_list(4);
                        break;
                    case 25:
                        set_SNSEQ_list(5);
                        break;
                    case 26:
                        set_SNSEQ_list(6);
                        break;
                    case 27:
                        set_SNSEQ_list(7);
                        break;
                    case 28:
                        set_SNSEQ_list(8);
                        break;
                    case 29:
                        set_SNSEQ_list(9);
                        break;
                    case 30:
                        set_SNSEQ_list(10);
                        break;
                    }
                    break;
                case TYPE_GENERATING_DOOR:
                    cur_obj->flags &= ~FLG(OBJ_ACTIVE);
                    cur_obj->flags &= ~FLG(OBJ_ALIVE);
                    unleashMonsterHost(cur_obj);
                    break;
                case TYPE_REDUCTEUR:
                    if (
                        reduced_rayman_id != -1 &&
                        cur_obj->hit_points == cur_obj->init_hit_points
                    )
                    {
                        DO_NOVA(cur_obj);
                        cur_obj->speed_x = 0;
                        cur_obj->speed_y = 0;
                        cur_obj->hit_points--;
                        RAY_DEMIRAY();
                    }
                    break;
                case TYPE_SIGNPOST:
                    TEST_SIGNPOST();
                    life_becoz_wiz = false;
                    break;
                case TYPE_CYMBALE:
                case TYPE_CYMBAL2:
                    DO_COLL_RAY_CYMBALE(cur_obj);
                    break;
                case TYPE_DARK2_PINK_FLY:
                    ToonDonnePoing(cur_obj);
                    break;
                case TYPE_FIRE_LEFT:
                case TYPE_FIRE_RIGHT:
                    ray_iframes = ray.iframes_timer;
                    if (ray_iframes >= 10)
                    {
                        RAY_HIT(true, cur_obj);
                        if (ray_mode != MODE_MORT_DE_RAYMAN)
                            ray.iframes_timer = 10;
                    }
                    else if (ray_iframes == -1)
                    {
                        RAY_HIT(true, cur_obj);
                        if (ray_mode != MODE_MORT_DE_RAYMAN)
                            ray.iframes_timer = 10;
                    }
                    else
                    {
                        RAY_HIT(false, cur_obj);
                        ray.iframes_timer = ray_iframes;
                    }
                    break;
                case TYPE_PANCARTE:
                    if (bonus_map)
                    {
                        status_bar.num_wiz = nb_wiz_save;
                        nb_wiz_save = 0;
                        departlevel = false;
                        fix_numlevel(&ray);
                    }
                    else
                    {
                        if (
                            !(ray.main_etat == 2 && ray.sub_etat == 8) &&
                            ray.hit_points != 0xFF && gele == 0
                        )
                        {
                            restoreGameState(&save2);
                            new_world = true;
                            if (life_becoz_wiz)
                            {
                                if (--status_bar.num_lives == -1)
                                    status_bar.num_lives = 0;
                                life_becoz_wiz = false;
                            }
                        }
                    }
                    break;
                default:
                    ray_iframes = ray.iframes_timer;
                    if (ray_iframes >= 60)
                    {
                        RAY_HIT(false, cur_obj);
                        ray.iframes_timer = ray_iframes;
                    }
                    else if (ray_iframes == -1)
                    {
                        RAY_HIT(true, cur_obj);
                        if (!(ray_mode == MODE_MORT_DE_RAYMAN || ray_mode == MODE_MORT_DE_RAYMAN_ON_MS))
                            ray.iframes_timer = 60;
                    }
                    else
                    {
                        RAY_HIT(false, cur_obj);
                        ray.iframes_timer = ray_iframes;
                    }
                    break;
                }
            }
        }
        i++;
        cur_obj = &level.objects[actobj.objects[i]];
    }
}

/* 210AC 801458AC -O2 -msoft-float */
void DO_COLLISIONS(void)
{
    s16 i;
    Obj *cur_obj;
    Obj *poing_obj;
    ObjType obj_type;
    s16 ray_collided;

    if (ray.field56_0x69 != 0)
        RAY_KO();
    else if (ray.iframes_timer == -1 && ray.eta[ray.main_etat][ray.sub_etat].flags & 8)
    {
        i = 0;
        cur_obj = &level.objects[actobj.objects[i]];
        while (i < actobj.num_active_objects)
        {
            if (new_world || new_level || fin_boss)
                break;

            obj_type = cur_obj->type;
            if (
                !(flags[obj_type].flags0 >> OBJ0_NO_COLLISION & 1) &&
                cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].flags & 0x20
            )
            {
                if (!((flags[obj_type].flags2 >> OBJ2_DO_NOT_CHECK_RAY_COLLISION) & 1))
                {
                    ray_collided = CHECK_BOX_COLLISION(TYPE_RAYMAN, ray_zdc_x, ray_zdc_y, ray_zdc_w, ray_zdc_h, cur_obj);
                    obj_type = cur_obj->type; /* ??? */
                    if (
                        (obj_type == TYPE_RAYON && (cur_obj->anim_frame > 3 || cur_obj->anim_frame == 0)) ||
                        (cur_obj->type == TYPE_MST_SCROLL && cur_obj->hit_points != 0)
                    )
                        ray_collided = -1;

                    if (ray_collided != -1)
                    {
                        switch (cur_obj->type)
                        {
                        case TYPE_DARK2_PINK_FLY:
                            ToonDonnePoing(cur_obj);
                            break;
                        case TYPE_ANNULE_SORT_DARK:
                            if (RayEvts.demi || RayEvts.force_run != 0 || RayEvts.reverse != 0)
                            {
                                DO_NOVA(&ray);
                                if (RayEvts.force_run != 0)
                                    RayEvts.force_run = 3;
                                if (RayEvts.reverse != 0)
                                    RAY_REVERSE_COMMANDS();
                                if (RayEvts.demi)
                                    RAY_DEMIRAY();
                                cur_obj->flags &= ~FLG(OBJ_ALIVE);
                                cur_obj->flags &= ~FLG(OBJ_ACTIVE);
                            }
                            break;
                        case TYPE_HYB_BBF2_LAS:
                            cur_obj->flags &= ~FLG(OBJ_ALIVE);
                            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
                            break;
                        case TYPE_BLACK_RAY:
                        case TYPE_BLACK_FIST:
                            if (ray_stack_is_full == true)
                                ray.hit_points = 0;
                            break;
                        case TYPE_TNT_BOMB:
                        case TYPE_PIRATE_BOMB:
                            BombExplosion(cur_obj);
                            break;
                        case TYPE_CYMBAL2:
                        case TYPE_CYMBALE:
                            DO_COLL_RAY_CYMBALE(cur_obj);
                            break;
                        case TYPE_GRAP_BONUS:
                            DO_NOVA(cur_obj);
                            RayEvts.grap = true;
                            cur_obj->flags &= ~FLG(OBJ_ALIVE);
                            break;
                        case TYPE_POING_POWERUP:
                            poing_obj = &level.objects[poing_obj_id];
                            if (cur_obj->sub_etat == 7)
                            {
                                if (!RayEvts.poing)
                                    poing_obj->init_sub_etat = 8;
                                else
                                {
                                    switch (poing_obj->init_sub_etat)
                                    {
                                    case 1:
                                        poing_obj->init_sub_etat = 8;
                                        break;
                                    case 3:
                                        poing_obj->init_sub_etat = 10;
                                        break;
                                    case 5:
                                        poing_obj->init_sub_etat = 12;
                                        break;
                                    }
                                }
                            }
                            else if (cur_obj->sub_etat == 14)
                            {
                                if (RayEvts.poing)
                                {
                                    switch (poing_obj->init_sub_etat)
                                    {
                                    case 1:
                                        poing_obj->init_sub_etat = 3;
                                        break;
                                    case 3:
                                        poing_obj->init_sub_etat = 5;
                                        break;
                                    case 5:
                                        poing_obj->init_sub_etat = 5;
                                        break;
                                    case 8:
                                        poing_obj->init_sub_etat = 10;
                                        break;
                                    case 10:
                                    case 12:
                                        poing_obj->init_sub_etat = 12;
                                        break;
                                    }
                                }
                                else
                                    poing_obj->init_sub_etat = 1;
                            }
                            DO_NOVA(cur_obj);
                            cur_obj->flags &= ~FLG(OBJ_ALIVE);
                            RayEvts.poing = true;
                            poing_obj->sub_etat = poing_obj->init_sub_etat;
                            poing.sub_etat = poing_obj->init_sub_etat;
                            PlaySnd(11, cur_obj->id);
                            break;
                        case TYPE_POWERUP:
                            DO_NOVA(cur_obj);
                            ray.hit_points += cur_obj->hit_points;
                            if (ray.hit_points > status_bar.max_hp)
                                ray.hit_points = status_bar.max_hp;
                            cur_obj->flags &= ~FLG(OBJ_ALIVE);
                            PlaySnd(8, cur_obj->id);
                            break;
                        case TYPE_ONEUP:
                            DO_NOVA(cur_obj);
                            PlaySnd(194, cur_obj->id);
                            id_Cling_1up = NOVA_STATUS_BAR();
                            if (id_Cling_1up == -1)
                                Add_One_RAY_lives();
                            cur_obj->flags &= ~FLG(OBJ_ALIVE);
                            take_bonus(cur_obj->id);
                            break;
                        case TYPE_SUPERHELICO:
                            PlaySnd(213, cur_obj->id);
                            DO_NOVA(cur_obj);
                            RayEvts.super_helico = true;
                            cur_obj->flags &= ~FLG(OBJ_ALIVE);
                            break;
                        case TYPE_GRAINE:
                            RayEvts.grain = true;
                            cur_obj->flags &= ~FLG(OBJ_ALIVE);
                            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
                            PlaySnd(10, cur_obj->id);
                            break;
                        case TYPE_DARK_SORT:
                            DO_DARK_SORT_COLLISION(cur_obj);
                            break;
                        }

                        if (
                            flags[cur_obj->type].flags0 >> OBJ0_HIT_RAY & 1 &&
                            ray.iframes_timer == -1 &&
                            !(ray.main_etat == 3 && ray.sub_etat == 32) &&
                            !RayEvts.unused_death
                        )
                        {
                            RAY_HIT(true, cur_obj);
                            break;
                        }
                    }
                }
            }
            i++;
            cur_obj = &level.objects[actobj.objects[i]];
        }
    }
    else if (ray.iframes_timer >= 0)
        ray.iframes_timer--;
    PS1_DoRaymanCollision();
}

/* 218C0 801460C0 -O2 -msoft-float */
void DO_OBJ_COLLISIONS(Obj *in_obj, s32 offs)
{
    s16 in_x; s16 in_y; s16 in_w; s16 in_h;
    u8 done;
    s16 i;
    Obj *cur_obj;
    s16 cur_x; s16 cur_y; s16 cur_w; s16 cur_h;

    GET_ANIM_POS(in_obj, &in_x, &in_y, &in_w, &in_h);
    done = false;
    if (in_obj->type == TYPE_FALLING_OBJ || in_obj->type == TYPE_FALLING_OBJ2 || in_obj->type == TYPE_FALLING_OBJ3)
    {
        in_x += 10;
        in_y += 20;
        in_w += -20;
        in_h += -25;
    }
    else
    {
        in_x = offs + in_x;
        in_y = offs + in_y;
        in_w -= offs * 2;
        in_h -= offs * 2;
    }
    i = 0;
    cur_obj = &level.objects[actobj.objects[i]];
    if (i < actobj.num_active_objects)
    {
        do
        {
            if (in_obj != cur_obj)
            {
                switch (cur_obj->type)
                {
                case TYPE_BADGUY1:
                    if (
                        !(cur_obj->main_etat == 2 || (cur_obj->main_etat == 0 && cur_obj->sub_etat == 3)) &&
                        (!(cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].flags & 0x40) &&
                         GET_SPRITE_POS(cur_obj, cur_obj->follow_sprite, &cur_x, &cur_y, &cur_w, &cur_h) &&
                         inter_box(cur_x, cur_y, cur_w, cur_h, in_x, in_y, in_w, in_h)
                        )
                    )
                    {
                        set_main_and_sub_etat(cur_obj, 0, 4);
                        cur_obj->follow_sprite = 4;
                        cur_obj->follow_y = 0;
                        cur_obj->speed_x = 0;
                        cur_obj->speed_y = 0;
                        cur_obj->offset_hy = 11;
                        cur_obj->flags |= FLG(OBJ_FOLLOW_ENABLED);
                        if (ray.field20_0x36 == in_obj->id)
                            RAY_TOMBE();
                        if (cur_obj->cmd == GO_WAIT)
                        {
                            if ((cur_obj->flags & FLG(OBJ_FLIP_X)))
                                skipToLabel(cur_obj, 3, true);
                            else
                                skipToLabel(cur_obj, 2, true);
                        }
                        set_sub_etat(in_obj, 9);
                        in_obj->flags &= ~FLG(OBJ_ACTIVE);
                        done = true;
                    }
                    break;
                case TYPE_BOUEE_JOE:
                    if (
                        GET_SPRITE_POS(cur_obj, cur_obj->follow_sprite, &cur_x, &cur_y, &cur_w, &cur_h) &&
                        in_obj->type == TYPE_POI2 &&
                        inter_box(cur_x, cur_y, cur_w, cur_h, in_x, in_y, in_w, in_h) &&
                        !(cur_obj->main_etat == 2 && cur_obj->sub_etat == 6)
                    )
                    {
                        /* sgn() on android */
                        if (
                            in_obj->flags & FLG(OBJ_FLIP_X) &&
                            (cur_obj->x_pos + cur_obj->offset_bx) - in_obj->x_pos - in_obj->offset_bx > -1
                        )
                        {
                            cur_obj->field56_0x69 = 1;
                            skipToLabel(in_obj, 3, true);
                            cur_obj->speed_x = 8;
                        }
                        if (
                            !(in_obj->flags & FLG(OBJ_FLIP_X)) &&
                            (cur_obj->x_pos + cur_obj->offset_bx) - in_obj->x_pos - in_obj->offset_bx < 0
                        )
                        {
                            cur_obj->field56_0x69 = 1;
                            skipToLabel(in_obj, 4, true);
                            cur_obj->speed_x = -8;
                        }
                    }
                    break;
                }

                if (done)
                    break;
            }
            i++;
            cur_obj = &level.objects[actobj.objects[i]];
        } while (i < actobj.num_active_objects);
    }
}