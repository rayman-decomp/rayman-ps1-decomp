#include "obj/poing.h"

#ifdef BSS_DEFS
s16 poing_obj_id;
Poing poing;
s16 id_obj_grapped;
#endif

/* 476F0 8016BEF0 -O2 -msoft-float */
void fist_U_turn(Obj *obj, u8 param_2)
{
    switch (obj->sub_etat)
    {
    case 1:
        set_sub_etat(obj, 2);
        break;
    case 3:
        set_sub_etat(obj, 4);
        break;
    case 5:
        set_sub_etat(obj, 6);
        break;
    case 8:
        set_sub_etat(obj, 9);
        break;
    case 10:
        set_sub_etat(obj, 11);
        break;
    case 12:
        set_sub_etat(obj, 13);
        break;
    }

    if (param_2)
        obj->anim_frame = 7;
}

/* 477D4 8016BFD4 -O2 -msoft-float */
void CALC_FIST_POS(void)
{
    Obj *obj = &level.objects[poing_obj_id];

    obj->screen_y_pos = (poing.field0_0x0 >> 4) - ymap;
    obj->screen_x_pos = obj->x_pos - xmap;
}

/* 47828 8016C028 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/poing", RAY_THROW_FIST);
#else
/* the unk_1 thing? */
void RAY_THROW_FIST(void)
{
    s32 unk_1;
    s16 unk_2;
    Obj *poing_obj = &level.objects[poing_obj_id];

    if (ray.main_etat == 2 && (ray.sub_etat == 25 || ray.sub_etat == 26))
        set_sub_etat(&ray, 29);
    else if (ray.main_etat == 2 && (ray.sub_etat == 27 || ray.sub_etat == 28))
        set_sub_etat(&ray, 30);
    else if (!(ray.main_etat == 2 && (ray.sub_etat == 17 || ray.sub_etat == 18 || ray.sub_etat == 19)))
        set_sub_etat(&ray, 13);

    if (ray.main_etat == 0)
    {
        if (ray.flags & FLG(OBJ_FLIP_X))
            decalage_en_cours -= poing.charge * 0x10; /* TODO: fixed point? */
        else
            decalage_en_cours += poing.charge * 0x10;
    }
    poing.is_charging = false;
    poing.is_active = true;
    poing.is_boum = false;
    poing.is_returning = false;
    poing_obj->flags = (poing_obj->flags & ~FLG(OBJ_FLIP_X)) | (ray.flags & FLG(OBJ_FLIP_X));
    poing_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
    poing_obj->speed_y = 0;
    poing_obj->anim_frame = 0;
    poing_obj->field20_0x36 = -1;
    set_main_and_sub_etat(poing_obj, poing_obj->init_main_etat, poing_obj->init_sub_etat);
    poing_obj->anim_index = poing_obj->eta[poing_obj->main_etat][poing_obj->sub_etat].anim_index;
    poing_obj->x_pos = ray_zdc_x + (ray_zdc_w >> 1) - poing_obj->offset_bx;
    poing_obj->x_pos -= 5 * FLIP_X_SGN(&ray);
    poing.damage = ashr16(poing.charge, 4) + 1;

    switch (poing_obj->init_sub_etat)
    {
    case 12:
        poing.damage += 2;
    case 5:
        poing.speed_x = 11;
        break;
    case 10:
        poing.damage += 2;
    case 3:
        poing.speed_x = 8;
        break;
    case 8:
        poing.damage += 2;
    case 1:
        poing.speed_x = 5;
        break;
    }

    if (
        ray.flags & FLG(OBJ_FLIP_X) ?
            decalage_en_cours > 0 :
            decalage_en_cours < 0
    )
        poing.speed_x += MAX_1(__builtin_abs(ray.speed_x) - 5, 0);

    poing.speed_x = MIN_1(poing.speed_x, 16);

    if (poing_obj->flags & FLG(OBJ_FLIP_X))
    {
        poing_obj->x_pos += 11;
        poing_obj->speed_x = poing.speed_x;
    }
    else
    {
        poing_obj->x_pos -= 11;
        poing_obj->speed_x = -poing.speed_x;
    }
    unk_1 = -40; /* tried applying pattern from fin_poing_follow */
    poing.field4_0xa = (poing.charge * 130 / 64) - (poing.speed_x * 3 + unk_1);
    unk_2 = ashl16(poing.charge, 8);
    poing.charge = unk_2;
    poing.field1_0x4 = unk_2;
    poing.field4_0xa = unk_2 * poing.speed_x / poing.field4_0xa;
    poing_obj->y_pos = ray_zdc_y + (ray_zdc_h >> 1) - ((poing_obj->offset_by + poing_obj->offset_hy) >> 1);
    poing.field0_0x0 = ashl16(poing_obj->y_pos, 4);
    CALC_FIST_POS();
}
#endif

/* 47CFC 8016C4FC -O2 -msoft-float */
void RAY_PREPARE_FIST(void)
{
    ObjState *eta_main;
    u8 anim_spd;

    if (ray.eta[ray.main_etat][ray.sub_etat].flags & 2)
    {
        if (ray.main_etat == 2)
        {
            if (ray.speed_y > 0)
            {
                eta_main = ray.eta[ray.main_etat];
                anim_spd = eta_main[2].anim_speed;
            }
            else
            {
                eta_main = ray.eta[ray.main_etat];
                anim_spd = eta_main[0].anim_speed;
            }
            eta_main[13].anim_speed =
                eta_main[13].anim_speed & 0xf |
                anim_spd & 0xf0;

            poing.charge = 32;
            RAY_THROW_FIST();
            helico_time = -1;
            if (RayEvts.super_helico)
                button_released = 0;
        }
        else
        {
            RAY_STOP();
            set_sub_etat(&ray, 11);
            poing.is_charging = true;
            poing.charge = 5;
        }
    }
}

/* 47E1C 8016C61C -O2 -msoft-float */
void RAY_GROW_FIST(void)
{
    poing.charge++;
    MIN_2(poing.charge, 63);
}

/* 47E54 8016C654 -O2 -msoft-float */
void fin_poing_follow(Obj *poing_obj, u8 param_2)
{
    Obj *unk_obj;
    s16 ray_y;
    s16 unk_y;

    if (poing_obj->field20_0x36 != -1)
    {
        unk_obj = &level.objects[poing_obj->field20_0x36];
        unk_obj->speed_x = 0;
        unk_obj->speed_y = 0;
        poing_obj->field20_0x36 = -1;
        if (param_2 || !(poing_obj->flags & FLG(OBJ_ALIVE)))
        {
            unk_obj->x_pos = ray.x_pos + ray.offset_bx - unk_obj->offset_bx;
            ray_y = ray_zdc_y + (ray_zdc_h >> 1);
            unk_y = ((unk_obj->offset_by + unk_obj->offset_hy) >> 1) + 5;
            unk_obj->y_pos = ray_y - unk_y;
        }
        else
        {
            unk_obj->x_pos = unk_obj->init_x_pos;
            unk_obj->y_pos = unk_obj->init_y_pos;
        }
    }
}

/* 47F1C 8016C71C -O2 -msoft-float */
void POING_FOLLOW(Obj *poing_obj)
{
    Obj *unk_obj = &level.objects[poing_obj->field20_0x36];

    unk_obj->speed_x = poing_obj->speed_x;
    unk_obj->speed_y = poing_obj->speed_y;
    if (!(ray.iframes_timer == -1 && unk_obj->flags & FLG(OBJ_ACTIVE)))
        fin_poing_follow(poing_obj, false);
}

/* 47F9C 8016C79C -O2 -msoft-float */
void alter_fist_speed(Obj *obj)
{
    u8 accel_x;
    s32 abs_spd_x = __builtin_abs(obj->speed_x);

    if (abs_spd_x > 10)
        accel_x = 2;
    else if (abs_spd_x > 7)
        accel_x = 1;
    else
        accel_x = horloge[2] != 0;

    if (obj->flags & FLG(OBJ_FLIP_X))
        obj->speed_x -= accel_x;
    else
        obj->speed_x += accel_x;
}

/* 48014 8016C814 -O2 -msoft-float */
void switch_off_fist(Obj *obj)
{
    poing.is_active = false;
    poing.is_boum = false;
    poing.charge = 5;
    poing.is_returning = false;
    obj->flags &= ~FLG(OBJ_ALIVE);
    obj->flags &= ~FLG(OBJ_ACTIVE);
    obj->sub_etat = obj->init_sub_etat;
    fin_poing_follow(obj, false);
}

/* 48078 8016C878 -O2 -msoft-float */
void DO_POING(Obj *obj)
{
    s32 ray_diff_x; s32 ray_diff_y;
    s16 unk_x_1; s32 unk_y_1;
    s32 unk_1;

    if (poing.is_active)
    {
        if (obj->speed_x != 0)
        {
            if (!poing.is_boum)
                DO_POING_COLLISION();

            CALC_FIST_POS();
            obj->y_pos = poing.field0_0x0 >> 4;
            if (poing.charge > 0)
            {
                if (poing.charge < poing.field4_0xa)
                    poing.charge = 0;
                else
                    poing.charge -= poing.field4_0xa;

                if (poing.charge == 0)
                    fist_U_turn(obj, false);
            }
            else if (poing.is_returning == false)
                alter_fist_speed(obj);
            else if (poing.is_returning == true)
            {
                if (__builtin_abs(obj->speed_x) < poing.speed_x)
                    alter_fist_speed(obj);

                ray_diff_x = ray_zdc_x + (ray_zdc_w >> 1) - obj->offset_bx;
                ray_diff_x += 11 * FLIP_X_SGN(obj);

                if (ray.main_etat == 4)
                    ray_diff_x += 11 * FLIP_X_SGN(obj);

                ray_diff_y =
                    (ray_zdc_y + (ray_zdc_h >> 1) -
                    ((obj->offset_by + obj->offset_hy) >> 1)) * 16;

                /* TODO: also a macro? see RAY_THROW_FIST */
                if (
                    obj->flags & FLG(OBJ_FLIP_X) ?
                        ray_diff_x >= obj->x_pos :
                        ray_diff_x <= obj->x_pos
                )
                    switch_off_fist(obj);
                else
                {
                    unk_x_1 = ray_diff_x - obj->x_pos;
                    unk_y_1 = ray_diff_y - poing.field0_0x0;
                    if (unk_x_1 != 0)
                        unk_y_1 = unk_y_1 / unk_x_1;
                    obj->speed_y = unk_y_1 * obj->speed_x;

                    unk_1 = obj->speed_y + poing.field0_0x0;
                    if (
                        unk_1 >= MIN_1(poing.field0_0x0, ray_diff_y) &&
                        unk_1 <= MAX_1(poing.field0_0x0, ray_diff_y)
                    )
                        obj->speed_y >>= 4;
                    else
                        obj->speed_y = (ray_diff_y - poing.field0_0x0) >> 4;
                }
            }
        }
        else
        {
            poing.is_returning = true;
            if (obj->flags & FLG(OBJ_FLIP_X))
                obj->speed_x--;
            else
                obj->speed_x++;
        }

        if (obj->field20_0x36 != -1)
            POING_FOLLOW(obj);
    }
}

/* 483C8 8016CBC8 -O2 -msoft-float */
void allocatePoingBoum(void)
{
    Obj *poing_obj;
    s16 poing_x; s16 poing_y; s16 poing_w; s16 poing_h;
    s16 boum_x; s16 boum_y; s16 boum_w; s16 boum_h;
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_BOUM && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            poing_obj = &level.objects[poing_obj_id];
            GET_ANIM_POS(poing_obj, &poing_x, &poing_y, &poing_w, &poing_h);
            GET_ANIM_POS(cur_obj, &boum_x, &boum_y, &boum_w, &boum_h);
            cur_obj->anim_frame = 0;
            cur_obj->x_pos = poing_x - cur_obj->offset_bx;
            if (poing_obj->speed_x > 0)
                cur_obj->x_pos += poing_w;
            cur_obj->y_pos =
                poing_y + (poing_h >> 1) - ((cur_obj->offset_by + cur_obj->offset_hy) >> 1);
            calc_obj_pos_map(cur_obj);
            cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
            break;
        }
        cur_obj++;
        i++;
    }
}
