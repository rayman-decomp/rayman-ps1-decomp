#include "obj_util.h"

#ifdef BSS_DEFS
u8 lidol_to_allocate;
Obj *lidol_source_obj;
#endif

/* 243B8 80148BB8 -O2 -msoft-float */
void init_obj_in_the_air(Obj *obj)
{
    obj->gravity_value_1 = 0;
    obj->gravity_value_2 = 0;
}

/* 243C4 80148BC4 -O2 -msoft-float */
void make_my_fruit_go_down(Obj *obj, s16 x_accel)
{
    if (obj->main_etat == 2 && __builtin_abs(obj->speed_x) < 32)
        obj->speed_x += x_accel;
    if (obj->type == TYPE_FALLING_YING_OUYE)
    {
        if (obj->main_etat != 2 || obj->sub_etat != 0)
        {
            set_main_and_sub_etat(obj, 2, 0);
            init_obj_in_the_air(obj);
        }
    }
    else
    {
        if (obj->main_etat != 2 || obj->sub_etat != 2)
        {
            set_main_and_sub_etat(obj, 2, 2);
            init_obj_in_the_air(obj);
        }
    }
}

/* 24494 80148C94 -O2 -msoft-float */
void allocate_toons(Obj *src_obj, u8 count)
{
    Obj *obj;
    s16 i;
    Obj *max_obj;
    u8 layers;
    s16 spr_x; s16 spr_y; s16 spr_w; s16 spr_h;

    obj = findfirstObject(TYPE_LIDOLPINK);
    i = 0;
    max_obj = &obj[14];
    if (src_obj->type == TYPE_RAYMAN)
        layers = ray.animations[ray.anim_index].layers_count; /* u16 loaded into u8? */
    else
        layers = 1;

    while (obj < max_obj)
    {
        if (!(obj->flags & FLG(OBJ_ACTIVE)) && obj->type == TYPE_LIDOLPINK)
        {
            set_main_and_sub_etat(obj, 2, 0);
            obj->iframes_timer = 20;
            obj->gravity_value_1 = 0;
            obj->gravity_value_2 = 5;
            obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            obj->speed_y = PS1_Toon_Speeds_y[i];
            obj->speed_x = PS1_Toon_Speeds_x[i];
            if (obj->speed_x >= 1)
            {
                obj->eta[2][0].speed_x_right = obj->speed_x;
                obj->eta[2][0].speed_x_left = -obj->speed_x;
                obj->flags |= FLG(OBJ_FLIP_X);
                skipToLabel(obj, 2, true);
            }
            else
            {
                obj->eta[2][0].speed_x_right = -obj->speed_x;
                obj->eta[2][0].speed_x_left = obj->speed_x;
                obj->flags &= ~FLG(OBJ_FLIP_X);
                skipToLabel(obj, 2, true);
            }
            obj->eta[2][1].speed_x_right = obj->eta[2][0].speed_x_right;
            obj->eta[2][1].speed_x_left = obj->eta[2][0].speed_x_left;
            GET_SPRITE_POS(src_obj, i % layers, &spr_x, &spr_y, &spr_w, &spr_h);
            obj->x_pos = spr_x + (spr_w >> 1) - obj->offset_bx;
            obj->y_pos = spr_y + (spr_h >> 1) - obj->offset_by;
            calc_obj_pos_map(obj);
            obj->anim_frame = 0;
            obj->anim_index = obj->eta[obj->main_etat][obj->sub_etat].anim_index;
            obj->flags &= ~FLG(OBJ_FLAG_9);
            i++;
            if (i == count)
                break;
        }
        obj++;
    }
}

/* 2479C 80148F9C -O2 -msoft-float */
void special_flags_init(void)
{
    u8 i;

    for (i = 0; i < 255; i++) /* TODO: LEN(zonediff) or LEN(flags) ??? */
    {
        if (i == 0)
        {
            if (num_level == 3)
                zonediffx[i] = -120;
            else
                zonediffx[i] = 0;
        }

        if (i == 16 || i == 17 || i == 24)
        {
            if (num_world == 1)
                flags[i].flags1 |= FLG(OBJ1_RAY_DIST_MULTISPR_CANTCHANGE);
            else
                flags[i].flags1 &= ~FLG(OBJ1_RAY_DIST_MULTISPR_CANTCHANGE);
        }

        if (i == 170)
            if (num_world == 4)
                zonediffx[i] = 150;
    }
}

/* 24894 80149094 -O2 -msoft-float */
void switchOff(Obj *obj)
{
    if (EOA(obj))
    {
        obj->flags &= ~FLG(OBJ_ACTIVE);
        obj->flags &= ~FLG(OBJ_ALIVE);
        if (obj->type == TYPE_RAYON)
        {
            obj->x_pos = -32000;
            obj->y_pos = -32000;
        }
    }
}

/* 2498C 8014918C -O2 -msoft-float */
void obj_hurt(Obj *obj)
{
    if (obj->hit_points < poing.damage)
        obj->hit_points = 0;
    else
        obj->hit_points -= poing.damage;
}

/* 249D0 801491D0 -O2 -msoft-float */
void Projectil_to_RM(Obj *obj, s16 *out_spd_x, s16 *out_spd_y, s16 new_spd_x, s16 new_spd_y)
{
    s16 diff_x; s16 diff_y;
    s16 diff_x_abs; s16 diff_y_abs;
    s16 unk_x; s16 unk_y;
    s32 spd_x;

    *out_spd_x = 0;
    *out_spd_y = 0;
    diff_x = ray.offset_bx + obj->follow_x - obj->x_pos - obj->offset_bx;
    diff_y = ray.offset_by + obj->follow_y - obj->y_pos - obj->offset_by;
    diff_x_abs = __builtin_abs(diff_x);
    diff_y_abs = __builtin_abs(diff_y);
    if (diff_x != 0 && diff_y != 0)
    {
        if (diff_x_abs > diff_y_abs)
        {
            unk_x = diff_x / diff_y_abs;
            unk_y = diff_y / diff_y_abs;
            *out_spd_x = new_spd_x;
            if (diff_x <= 0)
                *out_spd_x = -new_spd_x;
            *out_spd_y = diff_y * new_spd_y / diff_x_abs;
            if (*out_spd_y == 0)
            {
                spd_x = *out_spd_x;
                if (diff_x > 0)
                    spd_x += 16;
                else
                    spd_x -= 16;
                *out_spd_x = spd_x;
            }
        }
        else
        {
            unk_y = diff_y / diff_x_abs;
            unk_x = diff_x / diff_x_abs;
            *out_spd_y = new_spd_y;
            if (diff_y <= 0)
                *out_spd_y = -new_spd_y;
            *out_spd_x = diff_x * new_spd_x / diff_y_abs;
        }
    }
    else if (diff_y == 0)
    {
        *out_spd_x = new_spd_x;
        if (diff_x > 0)
            *out_spd_x = -new_spd_x;
        unk_x = -1;
        if (diff_x > 0)
            unk_x = 1;
        unk_y = 0;
    }
    else
    {
        *out_spd_y = new_spd_y;
        if (diff_y <= 0)
            *out_spd_y = -new_spd_y;
        unk_x = 0;
        unk_y = -1;
        if (diff_y > 0)
            unk_y = 1;
    }

    if (
        (!(obj->flags & FLG(OBJ_FLIP_X)) && *out_spd_x > 0) ||
        (obj->flags & FLG(OBJ_FLIP_X) && *out_spd_x < 0)
    )
    {
        *out_spd_x = -*out_spd_x;
        if (*out_spd_y == 0)
            *out_spd_y = 2;
    }

    obj->follow_x += unk_x * 2;
    obj->follow_y += unk_y * 2;
}

/* 24D00 80149500 -O2 -msoft-float */
void del_actobj(Obj *in_obj)
{
    s16 i;
    Obj *cur_obj;
    s16 j;

    in_obj->flags &= ~FLG(OBJ_ACTIVE);
    i = 0;
    cur_obj = &level.objects[actobj.objects[i]];
    while (i < actobj.num_active_objects)
    {
        if (cur_obj->id == in_obj->id)
            break;
        i++;
        cur_obj = &level.objects[actobj.objects[i]];
    }

    for (j = i; j <= actobj.num_active_objects; j++)
        actobj.objects[j - 1] = actobj.objects[j];

    actobj.num_active_objects--;
}