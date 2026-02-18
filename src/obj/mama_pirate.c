#include "obj/mama_pirate.h"

#ifdef BSS_DEFS
CouteauxInfo CouteauxInfos[5];
u8 pma_attaque;
u8 pma_groupe;
s16 mama_pirate_obj_id;
u8 pma_type_attaque;
u8 cou_place;
s16 cou_tempo;
u8 pma_nb_couteau;
u8 pma_phase;
s16 pma_tempo;
u8 pma_touched;
#endif

/* 25D4C 8014A54C -O2 -msoft-float */
void pmamaFollowsShip(Obj *obj)
{
    if (bateau_obj_id != -1)
        snapToSprite(obj, &level.objects[bateau_obj_id], 6, -165, -94);
    else
    {
        obj->speed_x = 0;
        obj->speed_y = 0;
    }
}

/* 25DB0 8014A5B0 -O2 -msoft-float */
void init_couteaux(void)
{
    u8 cout_ind = 0;
    u8 i = 0;
    Obj *obj = &level.objects[i];
    u8 nb_objs = level.nb_objects;

    while (i < (s16) nb_objs)
    {
        if (cout_ind > 4)
            return;
        if (obj->type == TYPE_COUTEAU)
        {
            CouteauxInfos[cout_ind].x_pos = 0;
            CouteauxInfos[cout_ind].y_pos = 0;
            CouteauxInfos[cout_ind].field2_0x4 = 1;
            CouteauxInfos[cout_ind].field3_0x6 = 1;
            CouteauxInfos[cout_ind].field4_0x8 = 15;
            CouteauxInfos[cout_ind].field5_0xa = 0;
            CouteauxInfos[cout_ind].field6_0xc = 0;
            CouteauxInfos[cout_ind].field7_0xe = 0;
            CouteauxInfos[cout_ind].active = false;
            CouteauxInfos[cout_ind].field9_0x10 = 5;
            CouteauxInfos[cout_ind].id = i;
            obj->flags &= ~FLG(OBJ_ALIVE);
            obj->flags &= ~FLG(OBJ_ACTIVE);
            obj->field23_0x3c = cout_ind;
            cout_ind++;
        }
        obj++;
        i++;
    }
}

/* 25EFC 8014A6FC -O2 -msoft-float */
void reset_couteaux(void)
{
    u8 i;

    for (i = 0; i < LEN(CouteauxInfos); i++)
        CouteauxInfos[i].active = false;
}

/* 25F3C 8014A73C -O2 -msoft-float */
u8 check_couteaux(void)
{
    u8 nb_active;
    u8 i;

    nb_active = 0;
    for (i = 0; i < LEN(CouteauxInfos); i++)
        if (CouteauxInfos[i].active == true)
            nb_active++;

    return nb_active == pma_couteaux[pma_sequence[pma_groupe][pma_attaque]];
}

/* 25FD4 8014A7D4 -O2 -msoft-float */
u8 find_couteau(Obj *obj)
{
    u8 bVar1 = obj->field23_0x3c;

    if (bVar1 > 4)
        bVar1 = 0xff;
    return bVar1;
}

/* 25FF4 8014A7F4 -O2 -msoft-float */
s32 x_pos(u8 param_1, u8 nb_couteau)
{
    s16 x;

    if (nb_couteau == 0)
        x = 0;
    else
    {
        x = (param_1 * 2 + 1) * (240 / (nb_couteau * 2));
        if (level.objects[mama_pirate_obj_id].flags & FLG(OBJ_FLIP_X))
            x += 80;
    }
    return x;
}

/* 26090 8014A890 -O2 -msoft-float */
s32 y_pos(s16 param_1, s16 param_2)
{
    s16 y;

    if (param_2 == 0)
        y = 44;
    else
        y = param_1 * 16 + 44;
    return y;
}

s16 y_floor(s16 x, s16 y)
{
    u8 btyp = BTYP(x, y);

    while (!(block_flags[btyp] >> BLOCK_SOLID & 1))
    {
        y += 16;
        btyp = BTYP(x, y);
    }

    return dist_to_bloc_floor(btyp, x & 0xf, 0) + (y & ~0xf); /* TODO: what do these &s do? */
}

/* 26174 8014A974 -O2 -msoft-float */
void init_move_couteau(Obj *obj)
{
    u8 cout_ind;
    Obj cout_obj;
    s16 x;
    s16 y;
    u8 test_1;

    cout_ind = find_couteau(obj);
    if (cout_ind != 0xff)
    {
        __builtin_memcpy(&cout_obj, &level.objects[CouteauxInfos[cout_ind].id], sizeof(Obj));
        x = cout_obj.x_pos + cout_obj.offset_bx; /* how should i have known this, given that 0x2c on stack was x_pos? */
        y = cout_obj.y_pos + cout_obj.offset_by;
        CouteauxInfos[cout_ind].active = false;

        switch (pma_type_attaque)
        {
        case 0:
        case 1:
        case 2:
        case 5:
            CouteauxInfos[cout_ind].x_pos = x;
            CouteauxInfos[cout_ind].y_pos = y;
            CouteauxInfos[cout_ind].field9_0x10 = 2;
            CouteauxInfos[cout_ind].field2_0x4 = 1;
            CouteauxInfos[cout_ind].field3_0x6 = 1;
            break;
        case 3:
        case 4:
            test_1 = (pma_type_attaque == 3) * 4; /* TODO: this/x_pos param is what? */
            if (cout_ind == 1)
                CouteauxInfos[cout_ind].x_pos = x_pos(test_1, 6);
            else
                CouteauxInfos[cout_ind].x_pos = x_pos(4 - test_1, 6);
            CouteauxInfos[cout_ind].y_pos = y_pos(11 - cout_ind, 1) + 8;
            CouteauxInfos[cout_ind].field9_0x10 = 0;
            if (cout_ind == 0)
                CouteauxInfos[cout_ind].field2_0x4 = 50;
            else
                CouteauxInfos[cout_ind].field2_0x4 = 50;
            CouteauxInfos[cout_ind].field3_0x6 = 70;
            break;
        }
    }
}

/* 263E8 8014ABE8 -O2 -msoft-float */
void init_lance_couteau(u8 index)
{
    Obj *obj;
    u8 main_etat; u8 sub_etat;
    s16 spr_x; s16 spr_y; s16 spr_w; s16 spr_h;

    if (index < pma_nb_couteau && index < LEN(CouteauxInfos))
    {
        obj = &level.objects[CouteauxInfos[index].id];
        if (!(obj->flags & FLG(OBJ_ACTIVE)))
        {
            obj->display_prio = 0;
            obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            CouteauxInfos[index].active = false;
            if (pma_type_attaque == 0 || pma_type_attaque == 3 || pma_type_attaque == 4)
            {
                main_etat = 2;
                sub_etat = 10;
                set_main_and_sub_etat(obj, main_etat, sub_etat);
                obj->anim_index = obj->eta[main_etat][sub_etat].anim_index;
                CouteauxInfos[index].field9_0x10 = 4;
                CouteauxInfos[index].x_pos = x_pos(index, pma_nb_couteau);
                CouteauxInfos[index].y_pos =
                    level.objects[mama_pirate_obj_id].offset_by +
                    level.objects[mama_pirate_obj_id].screen_y_pos -
                    obj->offset_by;
                CouteauxInfos[index].field2_0x4 = 1;
                obj->anim_frame = 0;
            }
            else
            {
                main_etat = 2;
                sub_etat = 11;
                set_main_and_sub_etat(obj, main_etat, sub_etat);
                obj->anim_index = obj->eta[main_etat][sub_etat].anim_index;
                if (pma_type_attaque == 5)
                {
                    CouteauxInfos[index].x_pos = x_pos(index, pma_nb_couteau);
                    CouteauxInfos[index].y_pos = y_pos(0, 0);
                    CouteauxInfos[index].field9_0x10 = 1;
                    CouteauxInfos[index].field2_0x4 = cou_tempo;
                    obj->anim_frame = 0;
                }
                else
                {
                    if (place_sequence[cou_place] <= index)
                        CouteauxInfos[index].x_pos = x_pos(index + 1, pma_nb_couteau + 1);
                    else
                        CouteauxInfos[index].x_pos = x_pos(index, pma_nb_couteau + 1);

                    CouteauxInfos[index].x_pos -= index * 4;
                    CouteauxInfos[index].y_pos = y_pos(0, 0);
                    CouteauxInfos[index].field9_0x10 = 3;
                    if (index == 0)
                        CouteauxInfos[index].field2_0x4 = cou_tempo;
                    else
                        CouteauxInfos[index].field2_0x4 = 1;
                    obj->anim_frame = 0;
                }
            }

            GET_SPRITE_POS(&level.objects[mama_pirate_obj_id], 6, &spr_x, &spr_y, &spr_w, &spr_h);
            if (level.objects[mama_pirate_obj_id].flags & FLG(OBJ_FLIP_X))
                spr_x += spr_w;
            obj->x_pos = spr_x - obj->offset_bx;
            obj->y_pos = spr_y - obj->offset_by;
            obj->init_x_pos = obj->x_pos;
            obj->init_y_pos = obj->y_pos;
        }
    }
}

/* 267EC 8014AFEC -O2 -msoft-float */
u8 couteau_frame(s16 spd_x, s16 spd_y)
{
    u8 frame;
    s16 diff;

    if (spd_x == 0)
        frame = ((u32) spd_y / 4096) & 8;
    else
    {
        if (spd_y == 0)
        {
            if (spd_x > 0)
                frame = 4;
            else
                frame = 12;
        }
        else
        {
            diff = __builtin_abs(spd_x) - __builtin_abs(spd_y);
            if (diff != 0)
            {
                if (diff >= 0)
                    frame = 5;
                else
                    frame = 7;
            }
            else
                frame = 6;

            if (spd_x > 0)
            {
                if (spd_y > 0)
                    frame = 8 - frame;
            }
            else
            {
                if (spd_y < 0)
                    frame = 16 - frame;
                else
                    frame = 8 + frame;
            }
        }
    }
    return frame;
}

/* 268AC 8014B0AC -O2 -msoft-float */
void update_couteau(Obj *obj)
{
    obj->anim_frame = couteau_frame(obj->speed_x, obj->speed_y);
}

/* 268E0 8014B0E0 -O2 -msoft-float */
void get_cou_zdc(Obj *obj, s16 *x, s16 *y, s16 *w, s16 *h)
{
    s16 spr_x; s16 spr_y; s16 spr_w; s16 spr_h;
    u8 sub_etat;

    GET_SPRITE_POS(obj, 0, &spr_x, &spr_y, &spr_w, &spr_h);
    *w = 6;
    *h = 6;
    if (obj->main_etat == 2)
    {
        sub_etat = obj->sub_etat;
        if (sub_etat - 10 <= 1U)
        {
            switch (obj->anim_frame)
            {
            case 0:
                *x = spr_x + (spr_w - *w >> 1);
                *y = spr_y + spr_h - *h;
                return;
            case 1:
            case 2:
            case 3:
                *x = spr_x + spr_w - *w;
                *y = spr_y + spr_h - *h;
                return;
            case 4:
                *w = spr_w;
                *x = spr_x + spr_w - *w;
                *y = spr_y + (spr_h - *h >> 1);
                return;
            case 5:
            case 6:
            case 7:
                *x = spr_x + spr_w - *w;
                *y = spr_y;
                return;
            case 8:
                *x = spr_x + (spr_w - *w >> 1);
                *y = spr_y;
                return;
            case 9:
            case 10:
            case 11:
                *x = spr_x;
                *y = spr_y;
                return;
            case 12:
                *w = spr_w;
                *x = spr_x;
                *y = spr_y + (spr_h - *h >> 1);
                return;
            case 13:
            case 14:
            case 15:
                *x = spr_x;
                *y = spr_y + spr_h - *h;
                return;
            default:
                *x = spr_x + (spr_w - *w >> 1);
                *y = spr_y + spr_h - *h;
                return;
            }
        }
        else
        {
            if (obj->sub_etat == 14 && !(obj->eta[2][obj->sub_etat].anim_speed & 0xf))
            {
                *h = spr_h;
                *x = spr_x + (spr_w - *w >> 1);
                *y = spr_y;
                return;
            }
            if (obj->main_etat == 2)
            {
                if (
                    (obj->sub_etat == 13) ||
                    (obj->sub_etat == 14 && obj->eta[2][obj->sub_etat].anim_speed & 0xf)
                )
                {
                    *x = -((*w >> 1) + -0x80) + obj->x_pos;
                    *y = -((*h >> 1) + -0x60) + obj->y_pos;
                    return;
                }
                if (obj->main_etat == 2 && obj->sub_etat == 12)
                {
                    *x = spr_x + (spr_w - *w >> 1);
                    *y = spr_y + spr_h - *h;
                    return;
                }
            }
        }
    }
    *x = -*w;
    *y = -*h;
}

/* 26C98 8014B498 -O2 -msoft-float */
void pma_attaque_suivante(void)
{
    u8 i;

    if ((pma_type_attaque - 1 < 2U) && (cou_place++, cou_place > 4))
        cou_place = 0;

    if (pma_touched || (pma_attaque++, pma_attaque == 2))
    {
        pma_groupe++;
        pma_attaque = 0;
        if (pma_groupe == 4)
        {
            pma_tempo -= 10;
            cou_tempo -= 10;
            pma_groupe = 0;
        }
    }
    if (pma_tempo < 100)
        pma_tempo = 100;

    if (cou_tempo < 50)
        cou_tempo = 50;
    pma_phase = 0;
    pma_type_attaque = pma_sequence[pma_groupe][pma_attaque];
    pma_nb_couteau = pma_couteaux[pma_type_attaque];
    pma_touched = false;

    for (i = 0; i < LEN(CouteauxInfos); i++)
    {
        level.objects[CouteauxInfos[i].id].flags &= ~FLG(OBJ_ACTIVE);
        level.objects[CouteauxInfos[i].id].flags &= ~FLG(OBJ_ALIVE);
    }
}

/* 26EDC 8014B6DC -O2 -msoft-float */
s16 convertspeed(s16 speed)
{
    return ashl16(speed, 4);
}

/* 26F08 8014B708 -O2 -msoft-float */
void lance_couteau_parabolique(Obj *obj)
{
    s16 diff_x; s16 diff_y;
    s16 spd_x; s16 spd_y;
    u8 cout_ind = find_couteau(obj);

    if (cout_ind != 0xFF)
    {
        diff_x = (xmap + CouteauxInfos[cout_ind].x_pos) - (obj->x_pos + obj->offset_bx);
        diff_y = (ymap + CouteauxInfos[cout_ind].y_pos) - (obj->y_pos + obj->offset_by);
        if (CouteauxInfos[cout_ind].field2_0x4 != 0)
        {
            CouteauxInfos[cout_ind].field2_0x4 = 0;
            if (diff_x == 0)
            {
                obj->speed_x = convertspeed(0);
                obj->speed_y = convertspeed(-1);
            }
            else
            {
                if (diff_x >= 0)
                    spd_x = 2;
                else
                    spd_x = -2;
                spd_y =
                    -(
                        ((diff_y * (spd_x << 4)) << 3) +
                        diff_x * (diff_x << 3)
                    ) /
                    ((diff_x * spd_x) << 3);
                obj->speed_x = convertspeed(spd_x) - 10;
                obj->speed_y = spd_y;
            }
            update_couteau(obj);
            obj->display_prio = 3;
        }
        else
        {
            obj->speed_y += 4;
            if (obj->speed_x * diff_x < 0)
                obj->speed_x = 0;
            update_couteau(obj);
        }
    }
}

/* 270D8 8014B8D8 -O2 -msoft-float */
void lance_couteau_droit(Obj *obj)
{
    u8 cout_ind;
    s16 diff_x;
    s16 diff_y;
    s32 abs_x;
    s32 abs_y;
    s32 divisor;

    cout_ind = find_couteau(obj);
    if (cout_ind != 0xFF)
    {
        diff_x = (xmap + CouteauxInfos[cout_ind].x_pos) - (obj->offset_bx + obj->x_pos);
        diff_y = (ymap + CouteauxInfos[cout_ind].y_pos) - (obj->offset_by + obj->y_pos);
        if (__builtin_abs(diff_x) >= 4 || __builtin_abs(diff_y) >= 4)
        {
            CouteauxInfos[cout_ind].active = false;
            abs_x = __builtin_abs(diff_x);
            abs_y = __builtin_abs(diff_y);
            abs_x = MAX_1(abs_x, abs_y);
            divisor = 4;
            divisor = ashl16(abs_x, 4) / divisor;
            obj->speed_x = convertspeed(ashl16(diff_x, 4) / (s16) divisor);
            obj->speed_y = convertspeed(ashl16(diff_y, 4) / (s16) divisor);
            update_couteau(obj);
            obj->display_prio = 3;
        }
        else
        {
            CouteauxInfos[cout_ind].active = true;
            if ((u32) (pma_type_attaque - 1) >= 2)
            {
                if (obj->main_etat != 2 || obj->sub_etat != 13)
                {
                    obj->main_etat = 2;
                    obj->sub_etat = 13;
                }
            }
            else
                obj->anim_frame = couteau_frame(0, 1);
            obj->speed_x = 0;
            obj->speed_y = 0;
            obj->x_pos = (xmap + CouteauxInfos[cout_ind].x_pos) - obj->offset_bx;
            obj->y_pos = (ymap + CouteauxInfos[cout_ind].y_pos) - obj->offset_by;
            if (check_couteaux())
            {
                pma_phase = 3;
                reset_couteaux();
            }
        }
    }
}

/* 273C4 8014BBC4 -O2 -msoft-float */
void retour_couteau(Obj *obj)
{
    u8 cout_ind;
    s16 diff_x;
    s16 diff_y;
    s32 abs_x;
    s32 abs_y;
    s32 divisor;

    cout_ind = find_couteau(obj);
    if (cout_ind != 0xFF && (cout_ind == 0 || CouteauxInfos[cout_ind - 1].field3_0x6 == 0))
    {
        if (CouteauxInfos[cout_ind].field3_0x6 == 0)
        {
            diff_x = 0;
            diff_y = 0;
            if (CouteauxInfos[cout_ind].field9_0x10 != 2)
            {
                diff_x = (xmap + CouteauxInfos[cout_ind].x_pos) - (obj->offset_bx + obj->x_pos);
                diff_y = (ymap + CouteauxInfos[cout_ind].y_pos) - (obj->offset_by + obj->y_pos);
            }

            if (__builtin_abs(diff_x) >= 2 || __builtin_abs(diff_y) >= 2)
            {
                CouteauxInfos[cout_ind].active = false;
                abs_x = __builtin_abs(diff_x);
                abs_y = __builtin_abs(diff_y);
                if (abs_x < abs_y)
                    abs_x = abs_y;
                divisor = 2;
                divisor = ashl16(abs_x, 4) / divisor;
                obj->speed_x = convertspeed(ashl16(diff_x, 4) / (s16) divisor);
                obj->speed_y = convertspeed(ashl16(diff_y, 4) / (s16) divisor);
            }
            else
            {
                CouteauxInfos[cout_ind].active = true;
                obj->speed_x = convertspeed(0);
                obj->speed_y = convertspeed(0);
                if (CouteauxInfos[cout_ind].field9_0x10 != 2)
                {
                    obj->x_pos = (xmap + CouteauxInfos[cout_ind].x_pos) - obj->offset_bx;
                    obj->y_pos = (ymap + CouteauxInfos[cout_ind].y_pos) - obj->offset_by;
                }
                if (check_couteaux())
                {
                    pma_phase = 3;
                    reset_couteaux();
                }
            }
        }
        else
            CouteauxInfos[cout_ind].field3_0x6--;
    }
}

/* 276F4 8014BEF4 -O2 -msoft-float */
void PS1_retour_couteau_old(Obj *obj)
{
    u8 cout_ind;
    s16 diff_x;
    s16 diff_y;
    s32 abs_x;
    s32 abs_y;
    s32 divisor;

    cout_ind = find_couteau(obj);
    if (cout_ind != 0xFF)
    {
        diff_x = 0;
        diff_y = 0;
        if (CouteauxInfos[cout_ind].field9_0x10 != 2)
        {
            /* addressing is a little weird */
            diff_x = (xmap + CouteauxInfos[cout_ind].x_pos) - (obj->offset_bx + obj->x_pos);
            diff_y = (ymap + (&CouteauxInfos[cout_ind])->y_pos) - (obj->offset_by + obj->y_pos);
        }

        if (__builtin_abs(diff_x) >= 2 || __builtin_abs(diff_y) >= 2)
        {
            CouteauxInfos[cout_ind].active = false;
            abs_x = __builtin_abs(diff_x);
            abs_y = __builtin_abs(diff_y);
            if (abs_x < abs_y)
                abs_x = abs_y;
            divisor = 2;
            divisor = ashl16(abs_x, 4) / divisor;
            obj->speed_x = convertspeed(ashl16(diff_x, 4) / (s16) divisor);
            obj->speed_y = convertspeed(ashl16(diff_y, 4) / (s16) divisor);
        }
        else
        {
            CouteauxInfos[cout_ind].active = true;
            obj->speed_x = convertspeed(0);
            obj->speed_y = convertspeed(0);
            if (CouteauxInfos[cout_ind].field9_0x10 != 2)
            {
                obj->x_pos = (xmap + CouteauxInfos[cout_ind].x_pos) - obj->offset_bx;
                obj->y_pos = (ymap + CouteauxInfos[cout_ind].y_pos) - obj->offset_by;
            }
            if (check_couteaux())
            {
                pma_phase = 3;
                reset_couteaux();
            }
        }
    }
}

/* 279B8 8014C1B8 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/mama_pirate", lance_couteau_lineaire);
#else
/* clean up, still */
void lance_couteau_lineaire(Obj *in_obj)
{
    s16 unk_1;
    Obj *cout_obj;
    s16 cout_x; s16 cout_y;
    s16 unk_2;
    s16 diff_x; s16 diff_y;
    u8 unk_sub_etat;
    s32 unk_3;
    s16 unk_4;
    s16 unk_x_1; s16 unk_y_1;
    u8 unk_anim_frame;
    u8 unk_5;
    ObjState *unk_state_1; ObjState *unk_state_2; ObjState *unk_state_3;    
    u8 cout_ind = find_couteau(in_obj);

    if (cout_ind != 0xFF && (cout_ind == 0 || CouteauxInfos[cout_ind - 1].field2_0x4 == 0))
    {
        unk_1 = CouteauxInfos[cout_ind].field2_0x4;
        if (unk_1 == 0)
        {
            if (!CouteauxInfos[cout_ind].active)
            {
                cout_obj = &level.objects[CouteauxInfos[cout_ind].id];
                cout_x = cout_obj->x_pos + cout_obj->offset_bx;
                cout_y = cout_obj->y_pos + cout_obj->offset_by;
                if (
                    cout_x < -20 || (cout_x > xmapmax + 340) ||
                    cout_y < -20 || (cout_y > ymapmax + 260)
                )
                {
                    CouteauxInfos[cout_ind].active = true;
                    level.objects[CouteauxInfos[cout_ind].id].flags &= ~FLG(OBJ_ACTIVE);
                    level.objects[CouteauxInfos[cout_ind].id].flags &= ~FLG(OBJ_ALIVE);
                    if (check_couteaux())
                    {
                        pma_phase = 4;
                        if (level.objects[mama_pirate_obj_id].hit_points == 0)
                        {
                            fin_boss = true;
                            finBosslevel.viking_mama = true;
                        }
                    }
                }
            }
        }
        else if (unk_1 == 1)
        {
            unk_2 = CouteauxInfos[cout_ind].field4_0x8;
            if (unk_2 == 0x000F)
            {
                CouteauxInfos[cout_ind].x_pos = ray.x_pos + ray.offset_bx;
                CouteauxInfos[cout_ind].y_pos = ray.y_pos + ray.offset_by;
                diff_x = CouteauxInfos[cout_ind].x_pos - (in_obj->x_pos + in_obj->offset_bx);
                diff_y = CouteauxInfos[cout_ind].y_pos - (in_obj->y_pos + in_obj->offset_by);
                switch (CouteauxInfos[cout_ind].field9_0x10)
                {
                case 1:
                    unk_sub_etat = 11;
                    unk_3 = MAX_1(__builtin_abs(diff_x), __builtin_abs(diff_y));
                    unk_4 = 4; /* get rid of this? */
                    unk_4 = ashl16(unk_3, 4) / unk_4;
                    unk_x_1 = convertspeed(ashl16(diff_x, 4) / unk_4);
                    unk_y_1 = convertspeed(ashl16(diff_y, 4) / unk_4);
                    unk_anim_frame = couteau_frame(unk_x_1, unk_y_1);
                    break;
                case 3:
                    unk_sub_etat = 11;
                    unk_x_1 = convertspeed(0);
                    unk_y_1 = convertspeed(3);
                    unk_anim_frame = couteau_frame(unk_x_1, unk_y_1);
                    break;
                case 0:
                    unk_sub_etat = 11;
                    unk_x_1 = convertspeed(3 * (diff_x >= 0 ? 1 : -1));
                    unk_y_1 = convertspeed(0);
                    unk_anim_frame = couteau_frame(unk_x_1, unk_y_1);
                    break;
                case 2:
                    unk_sub_etat = 14;
                    unk_x_1 = convertspeed(-1);
                    unk_y_1 = convertspeed(5);
                    unk_anim_frame = couteau_frame(0, 1);
                    break;
                }

                /* duplication? */
                unk_5 = CouteauxInfos[cout_ind].field9_0x10;
                if (unk_5 == 2)
                {
                    in_obj->sub_etat = unk_sub_etat;
                    in_obj->anim_frame = unk_anim_frame;
                    unk_state_1 = &in_obj->eta[in_obj->main_etat][in_obj->sub_etat];
                    unk_state_1->anim_speed &= 0xF0;
                    CouteauxInfos[cout_ind].field7_0xe = unk_anim_frame;
                    CouteauxInfos[cout_ind].field5_0xa = unk_x_1;
                    CouteauxInfos[cout_ind].field6_0xc = unk_y_1;
                    CouteauxInfos[cout_ind].field4_0x8--;
                    in_obj->speed_x = CouteauxInfos[cout_ind].field5_0xa;
                    in_obj->speed_y = CouteauxInfos[cout_ind].field6_0xc;
                    CouteauxInfos[cout_ind].field4_0x8 = 0x000F;
                    CouteauxInfos[cout_ind].field2_0x4 = 0;
                    CouteauxInfos[cout_ind].active = false;
                    unk_state_2 = &in_obj->eta[in_obj->main_etat][in_obj->sub_etat];
                    unk_state_2->anim_speed = (unk_state_2->anim_speed & 0xF0) | 2;
                    in_obj->gravity_value_1 = 0;
                    in_obj->gravity_value_2 = 8;
                }
                else if (unk_5 == 3)
                {
                    in_obj->sub_etat = unk_sub_etat;
                    in_obj->anim_frame = unk_anim_frame;
                    CouteauxInfos[cout_ind].field5_0xa = unk_x_1;
                    CouteauxInfos[cout_ind].field7_0xe = unk_anim_frame;
                    CouteauxInfos[cout_ind].field6_0xc = unk_y_1;
                    CouteauxInfos[cout_ind].field4_0x8--;
                    in_obj->speed_x = CouteauxInfos[cout_ind].field5_0xa;
                    in_obj->speed_y = CouteauxInfos[cout_ind].field6_0xc;
                    CouteauxInfos[cout_ind].field4_0x8 = 0x000F;
                    CouteauxInfos[cout_ind].field2_0x4 = 0;
                    CouteauxInfos[cout_ind].active = false;
                }
                else if (in_obj->anim_frame == unk_anim_frame)
                {
                    in_obj->sub_etat = unk_sub_etat;
                    in_obj->anim_frame = unk_anim_frame;
                    CouteauxInfos[cout_ind].field7_0xe = unk_anim_frame;
                    CouteauxInfos[cout_ind].field5_0xa = unk_x_1;
                    CouteauxInfos[cout_ind].field6_0xc = unk_y_1;
                    CouteauxInfos[cout_ind].field4_0x8--;
                }
            }
            else if (unk_2 == 0)
            {
                in_obj->speed_x = (s16) CouteauxInfos[cout_ind].field5_0xa;
                in_obj->speed_y = (s16) CouteauxInfos[cout_ind].field6_0xc;
                if (CouteauxInfos[cout_ind].field9_0x10 == 2)
                {
                    unk_state_3 = &in_obj->eta[in_obj->main_etat][in_obj->sub_etat];
                    unk_state_3->anim_speed = (unk_state_3->anim_speed & 0xF0) | 2;
                    in_obj->gravity_value_1 = 0;
                    in_obj->gravity_value_2 = 8;
                }
                CouteauxInfos[cout_ind].field4_0x8 = 0x000F;
                CouteauxInfos[cout_ind].field2_0x4 = 0;
                CouteauxInfos[cout_ind].active = 0;
            }
            else
            {
                in_obj->speed_x = 0;
                in_obj->speed_y = 0;
                in_obj->anim_frame = CouteauxInfos[cout_ind].field7_0xe;
                /* duplication */
                if (CouteauxInfos[cout_ind].field4_0x8 & 1)
                    in_obj->y_pos += 2;
                else
                    in_obj->y_pos -= 2;

                if (CouteauxInfos[cout_ind].field4_0x8 > 0)
                    CouteauxInfos[cout_ind].field4_0x8--;
            }
        }
        else
        {
            /* unk_1 is field2_0x4*/
            if (unk_1 > 1)
                CouteauxInfos[cout_ind].field2_0x4--;

            if (CouteauxInfos[cout_ind].field2_0x4 == 1)
                CouteauxInfos[cout_ind].field4_0x8 = 0x000F;
        }
    }
}
#endif

/* 28338 8014CB38 -O2 -msoft-float */
/*int ashr16(ushort param_1,uint param_2);*/

void DO_COU_COMMAND(Obj *obj)
{
    switch (obj->main_etat)
    {
    case 0:
        if (obj->sub_etat == 9)
        {
            obj->flags |= FLG(OBJ_FOLLOW_ENABLED);
            obj->speed_x = ashr16(obj->speed_x, 1);
            CALC_MOV_ON_BLOC(obj);
            if (screen_trembling == 1 || pma_phase == 2)
            {
                if (pma_phase != 2)
                {
                    pma_phase = 2;
                    reset_couteaux();
                }
                set_main_and_sub_etat(obj, 2, 12);
            }
        }
    default:
        break;
    case 2:
        obj->flags &= ~FLG(OBJ_FOLLOW_ENABLED);
        switch (obj->sub_etat)
        {
        case 10:
            if (pma_phase == 0)
                lance_couteau_parabolique(obj);
            break;
        case 11:
            if (pma_phase == 3)
                lance_couteau_lineaire(obj);
            else if (pma_phase == 0)
                lance_couteau_droit(obj);
            break;
        case 14:
            if (pma_phase == 3)
                lance_couteau_lineaire(obj);
            else if (pma_phase == 0)
                lance_couteau_droit(obj);

            if (obj->speed_y >= 0 && obj->anim_frame == couteau_frame(0, -1))
                obj->eta[obj->main_etat][obj->sub_etat].anim_speed &= 0xF0;
            break;
        case 13:
            if (pma_phase == 2)
                retour_couteau(obj);
            else if (pma_phase == 3)
                lance_couteau_lineaire(obj);
            break;
        case 12:
            obj->speed_x = convertspeed(0);
            obj->speed_y = convertspeed(-1);
            if (EOA(obj))
            {
                if (horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0)
                {
                    obj->speed_y = convertspeed(0);
                    if (pma_phase == 2)
                    {
                        init_move_couteau(obj);
                        set_main_and_sub_etat(obj, 2, 13);
                    }
                    else
                        set_main_and_sub_etat(obj, 0, 9);
                }
            }
            break;
        }
        break;
    }
}

/* 28694 8014CE94 -O2 -msoft-float */
void calc_pma_dir(Obj *obj)
{
    s16 diff_x;
    u8 should_flip;

    diff_x = (ray.offset_bx + ray.x_pos) - (obj->offset_bx + obj->x_pos);
    if (diff_x != 0)
        obj->flags = obj->flags & ~FLG(OBJ_FLIP_X) | (should_flip = diff_x > 0) << OBJ_FLIP_X;
}

/* 286F0 8014CEF0 -O2 -msoft-float */
void DO_PMA_COMMAND(Obj *obj)
{
    s16 main_etat;
    s16 sub_etat;
    s16 i;
    s16 y;

    scrollLocked = true;
    main_etat = obj->main_etat;
    sub_etat = obj->sub_etat;
    switch (main_etat)
    {
    case 0:
        switch (sub_etat)
        {
        case 6:
            obj->speed_x = 1;
            obj->speed_y = 0;
            CALC_MOV_ON_BLOC(obj);
            if ((obj->x_pos + obj->offset_bx) > (xmap + 272))
            {
                obj->speed_x = 0;
                set_main_and_sub_etat(obj, 0, 2);
            }
            break;
        default:
            return;
        case 2:
            calc_pma_dir(obj);
            CALC_MOV_ON_BLOC(obj);
            if (pma_phase == 4)
            {
                reset_couteaux();
                pma_attaque_suivante();
            }
            if (pma_phase == 0)
                set_main_and_sub_etat(obj, 0, 1);
            break;
        case 1:
            CALC_MOV_ON_BLOC(obj);
            if (EOA(obj) && pma_phase == 0)
                set_main_and_sub_etat(obj, 0, 5);
            break;
        case 5:
            CALC_MOV_ON_BLOC(obj);
            if (obj->anim_frame == 35 && (horloge[obj->eta[main_etat][sub_etat].anim_speed & 0xF] == 0))
            {
                PlaySnd(153, obj->id);
                i = 0;
                while (i < pma_nb_couteau && i < 5)
                {
                    init_lance_couteau(i);
                    i++;
                }
            }
            else
            {
                if (EOA(obj))
                    set_main_and_sub_etat(obj, 2, 1);
            }
            break;
        case 7:
            obj->speed_x = 0;
            obj->speed_y = -2;
            if (EOA(obj))
            {
                if (horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0)
                {
                    obj->flags &= ~FLG(OBJ_ACTIVE);
                    obj->flags &= ~FLG(OBJ_ALIVE);
                    for (i = 0; i < 5; i++)
                    {
                        CouteauxInfos[i].field9_0x10 = 2;
                        CouteauxInfos[i].field2_0x4 = 1;
                        CouteauxInfos[i].active = false;
                        CouteauxInfos[i].field4_0x8 = 0xf;
                    }
                    pma_phase = 2;
                    return;
                }
            }
            break;
        }
        break;
    case 2:
        switch (sub_etat)
        {
        case 9:
            obj->speed_x = 0;
            if (EOA(obj) || (obj->hit_points == 1 && obj->speed_y >= 0))
            {
                pma_touched = true;
                obj->hit_points--;
                if (obj->hit_points == 0)
                    set_main_and_sub_etat(obj, 0, 7);
                else
                    set_main_and_sub_etat(obj, 2, 4);
            }
            break;
        case 6:
            obj->speed_x = 0;
            obj->flags &= ~FLG(OBJ_FLIP_X);
            if (obj->anim_frame < 6)
                pmamaFollowsShip(obj);
            else
                obj->speed_y = -2;
            break;
        case 1:
            calc_pma_dir(obj);
            obj->speed_x = 0;
            obj->speed_y = 0;
            break;
        case 8:
            obj->speed_x = 0;
            obj->speed_y = 0;
            break;
        case 2:
            obj->speed_y = -2;
            if (obj->anim_frame >= 15)
                obj->speed_y = 0;
            obj->field23_0x3c = 0;
            return;
        case 3:
            obj->speed_y = 0;
            if (check_couteaux())
            {
                if (pma_phase == 0)
                    pma_phase = 1;

                if (++obj->field23_0x3c == pma_tempo || pma_type_attaque == 5)
                {
                    obj->gravity_value_1 = 0;
                    obj->gravity_value_2 = 3;
                    set_main_and_sub_etat(obj, 2, 4);
                }
            }
            break;
        case 4:
            y = obj->offset_by + obj->y_pos;
            if ((y_floor((s16) (xmap + 160), y) - y) < 5)
            {
                obj->speed_y = 1;
                obj->field23_0x3c = 0;
                set_main_and_sub_etat(obj, 2, 5);
            }
            break;
        case 5:
            if (EOA(obj))
                set_main_and_sub_etat(obj, 0, 2);
            break;
        }
        break;
    }
}

/* 28F78 8014D778 -O2 -msoft-float */
void init_mama_pirate(Obj *obj)
{
    init_couteaux();
    obj->hit_points = 6;
    obj->init_hit_points = 6;
    pma_groupe = 0;
    pma_attaque = 0;
    pma_phase = 0;
    cou_place = 0;
    pma_type_attaque = pma_sequence[0][0];
    pma_tempo = 150;
    cou_tempo = 70;
    pma_nb_couteau = pma_couteaux[pma_type_attaque];
    pma_touched = false;
    obj->flags &= ~FLG(OBJ_FLIP_X);
    obj->speed_x = 0;
    obj->speed_y = 0;
    set_main_and_sub_etat(obj, 2, 6);
    obj->anim_frame = 0;
    obj->anim_index = obj->eta[2][6].anim_index;
}

/* 2905C 8014D85C -O2 -msoft-float */
void PMA_SORT_DU_CANON(Obj *obj)
{
    init_mama_pirate(obj);
    scroll_end_x = xmap;
    scroll_start_x = xmap;
    scroll_end_y = ymap;
    scroll_start_y = ymap;
}

/* 290AC 8014D8AC -O2 -msoft-float */
void DO_PMA_POING_COLLISION(Obj *obj)
{
    if (!pma_touched && obj->main_etat == 2 && obj->sub_etat == 3)
    {
        set_main_and_sub_etat(obj, 2, 9);
        obj->speed_x = 0;
        obj->speed_y = -2;
        obj->gravity_value_1 = 0;
        obj->gravity_value_2 = 8;
    }
}

/* 29118 8014D918 -O2 -msoft-float */
s32 pma_get_eject_sens(Obj *obj)
{
    ray.iframes_timer = 40;
    return -1;
}

/* 2912C 8014D92C -O2 -msoft-float */
void DO_COU_ATTER(Obj *obj)
{
    u8 sub_etat;
    ObjState *eta;

    if (obj->main_etat == 2)
    {
        sub_etat = obj->sub_etat;
        if (sub_etat == 10)
        {
            recale_position(obj);
            CouteauxInfos[obj->field23_0x3c].active = true;
            set_main_and_sub_etat(obj, 0, 9);
            obj->speed_x = 0;
            obj->speed_y = 0;
        }
        else if (sub_etat == 11)
        {
            if ((pma_type_attaque - 1) < 2U)
            {
                CouteauxInfos[obj->field23_0x3c].active = true;
                if (check_couteaux())
                    pma_phase = 1;
                recale_position(obj);
                set_main_and_sub_etat(obj, 0, 9);
                obj->speed_x = 0;
                obj->speed_y = 0;
            }
        }
        else if (sub_etat == 14)
        {
            obj->speed_y = -obj->speed_y;
            obj->gravity_value_1 = obj->gravity_value_2 - obj->gravity_value_1;
            eta = &obj->eta[obj->main_etat][obj->sub_etat];
            eta->anim_speed = eta->anim_speed & 0xf0 | 2;
            recale_position(obj);
        }
    }
}

/* 2929C 8014DA9C -O2 -msoft-float */
void DO_PMA_ATTER(Obj *obj)
{
    if (obj->main_etat == 2)
    {
        if (obj->sub_etat == 7)
        {
            obj->speed_x = 0;
            obj->speed_y = 0;
            recale_position(obj);
            if (screen_trembling == 0)
                screen_trembling = 1;
            set_main_and_sub_etat(obj, 2, 8);
        }
        else if (obj->sub_etat == 5)
        {
            obj->speed_x = 0;
            obj->speed_y = 0;
            if (screen_trembling == 0)
            {
                if (obj->field23_0x3c == 0)
                {
                    recale_position(obj);
                    allocateLandingSmoke(obj);
                    obj->field23_0x3c = 1;
                }
                screen_trembling = 1;
            }
            if (pma_phase == 1)
            {
                pma_phase = 2;
                reset_couteaux();
            }
        }
    }
}
