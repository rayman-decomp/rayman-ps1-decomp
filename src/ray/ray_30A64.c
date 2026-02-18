#include "ray/ray_30A64.h"

#ifdef BSS_DEFS
StatusBar status_bar;
s16 sbar_obj_id;
u8 nb_wiz;
u8 nb_wiz_collected;
s16 special_ray_mov_win_x_left;
s16 special_ray_mov_win_x_right;
#endif

/* 30A64 80155264 -O2 -msoft-float */
s16 RayCoince(s16 dir)
{
    s16 x_pos;
    s16 y_pos;
    s32 pos_to_check;
    s32 map_ind;
    u8 res = false;

    if (ray.flags & FLG(OBJ_FLIP_X))
        x_pos = ray.x_pos + 70;
    else
        x_pos = ray.x_pos + 58;
    y_pos = ray.y_pos + 32;

    switch (dir)
    {
    case 2:
        pos_to_check = y_pos - (y_pos / 16 * 16);
        if ((s16) pos_to_check < 3)
        {
            map_ind = (x_pos >> 4) + (mp.width * (y_pos >> 4));
            if (block_flags[mp.map[map_ind] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
            if (block_flags[mp.map[++map_ind] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
            if (block_flags[mp.map[++map_ind] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
        }
        break;
    case 3:
        pos_to_check = y_pos - (y_pos / 16 * 16);
        if ((s16) pos_to_check > 12)
        {
            map_ind = (x_pos >> 4) + (mp.width * ((y_pos + 16 * 4) >> 4));
            if (block_flags[mp.map[map_ind] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
            if (block_flags[mp.map[++map_ind] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
            if (block_flags[mp.map[++map_ind] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
        }
        break;
    case 0:
        pos_to_check = x_pos - (x_pos / 16 * 16);
        if ((s16) pos_to_check < 3)
        {
            map_ind = ((x_pos >> 4) + (mp.width * ((y_pos + 16) >> 4))) - 1;
            if (block_flags[mp.map[map_ind] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
            if (block_flags[mp.map[map_ind += mp.width] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
            if (block_flags[mp.map[map_ind += mp.width] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
        }
        break;
    case 1:
        pos_to_check = x_pos - (x_pos / 16 * 16);
        if ((s16) pos_to_check > 12)
        {
            map_ind = ((x_pos >> 4) + (mp.width * ((y_pos + 16) >> 4))) + 3;
            if (block_flags[mp.map[map_ind] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
            if (block_flags[mp.map[map_ind += mp.width] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
            if (block_flags[mp.map[map_ind += mp.width] >> 10] >> BLOCK_FULLY_SOLID & 1)
                res = true;
        }
        break;
    }

    return res;
}

/* 30E34 80155634 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/ray/ray_30A64", move_up_ray);
#else
/* unk_y_2? */
void move_up_ray(void)
{
    s16 unk_y_1;
    s16 unk_y_2;

    if (ray_mode == MODE_RAY_ON_MS && RayCoince(2))
        ray.speed_y = 0;

    if (!(ray.eta[ray.main_etat][ray.sub_etat].flags & 0x40) && ray.scale == 0)
        unk_y_1 = 25;
    else
        unk_y_1 = 40;

    ray.y_pos += ray.speed_y;
    unk_y_2 = 20;
    if (ray.y_pos < scroll_start_y - (unk_y_1 + unk_y_2))
    {
        ray.y_pos = scroll_start_y - (unk_y_1 + unk_y_2);
        ray.speed_y = 0;
        if (ray.field20_0x36 != -1)
            RAY_HIT(ray.iframes_timer == -1, null);
    }
    calc_obj_pos(&ray);
    v_scroll_speed = 0;
}
#endif

/* 30E34 80155634 -O2 -msoft-float */
void move_down_ray(void)
{
    if (ray_mode == MODE_RAY_ON_MS && RayCoince(3))
        ray.speed_y = 0;

    ray.y_pos += ray.speed_y;
    calc_obj_pos(&ray);
    if (ray.main_etat == 2)
    {
        if ((scroll_end_y - ymap > ray.speed_y) && ray.screen_y_pos >= 100)
            v_scroll_speed = ray.speed_y;
        else
            v_scroll_speed = 0;
    }
}

/* 3103C 8015583C -O2 -msoft-float */
void recale_ray_pos(void)
{
    s16 unk_y_1; s16 unk_y_2;
    s32 v_scr_temp;
    s32 spd_y_abs_1; s16 spd_y_abs_2;
    s16 unk_x_1; s16 unk_x_2; s16 unk_x_3;
    Obj *other_obj;

    if (!(ray.main_etat == 3 && ray.sub_etat == 23))
    {
        if (scroll_y == -1)
        {
            unk_y_1 = ((ray_zdc_h >> 1) - ray.offset_by) + 136;
            if (
                !(ray.main_etat == 2 && !(ray.sub_etat == 15 && ray_Suphelico_bis)) &&
                screen_trembling == 0
            )
            {
                if (v_scroll_speed != 0x00FF || decalage_en_cours != 0)
                {
                    unk_y_2 = ray.screen_y_pos - unk_y_1;
                    v_scr_temp =
                    v_scroll_speed =
                        ashr16(unk_y_2, 2);
                    spd_y_abs_1 = __builtin_abs(ray.speed_y);
                    if (__builtin_abs(v_scr_temp) >= spd_y_abs_1)
                    {
                        MAX_2(spd_y_abs_1, 3);
                        spd_y_abs_2 = spd_y_abs_1;
                        if (v_scr_temp > 0)
                        {
                            MIN_2(v_scroll_speed, (s16) spd_y_abs_1);
                        }
                        else if (v_scr_temp < 0)
                        {
                            MAX_2(v_scr_temp, -spd_y_abs_2);
                            v_scroll_speed = v_scr_temp;
                        }
                        else
                        {
                            if (unk_y_2 > 0)
                                v_scroll_speed = 1;
                            else if (unk_y_2 < 0)
                                v_scroll_speed = -1;
                        }
                    }
                }
                else if (ray.main_etat != 1)
                {
                    if (ray.screen_y_pos < unk_y_1 + 48)
                        v_scroll_speed = -4;
                    else
                        v_scroll_speed = 0;
                }
            }
            else
            {
                if (
                    (
                        ymap != scroll_end_y &&
                        (unk_y_1 < ray.screen_y_pos - ray.speed_y) &&
                        ray.speed_y > 0
                    ) ||
                    (
                        ymap != scroll_start_y &&
                        (-ray.offset_hy - 16 >= ray.screen_y_pos) &&
                        ray.speed_y < 0
                    )
                )
                {
                    if (ray.speed_y <= 16)
                        v_scroll_speed = ray.speed_y;
                    else
                        v_scroll_speed = 0;
                }
            }
        }

        if (scroll_x == -1)
        {
            unk_x_1 = (112 - ray.offset_bx) - special_ray_mov_win_x_left;
            unk_x_2 = special_ray_mov_win_x_right - (ray.offset_bx - 208);
            if (decalage_en_cours > 0 || ray.speed_x > 0)
            {
                unk_x_3 = ashr16(ray.screen_x_pos - unk_x_1, 2);
                if (unk_x_3 >= dhspeed)
                {
                    if (unk_x_3 > dhspeed)
                        dhspeed++;
                }
                else
                    dhspeed--;
            }
            else if (decalage_en_cours < 0 || ray.speed_x < 0)
            {
                unk_x_3 = ashr16(ray.screen_x_pos - unk_x_2, 2);
                if (unk_x_3 > dhspeed)
                    dhspeed++;
                else if (unk_x_3 < dhspeed)
                    dhspeed--;
            }
            else
            {
                if (ray.flags & FLG(OBJ_FLIP_X))
                {
                    unk_x_3 = ashr16(ray.screen_x_pos - unk_x_1, 2);
                    if (unk_x_3 >= dhspeed)
                    {
                        if (unk_x_3 > dhspeed)
                            dhspeed++;
                    }
                    else
                        dhspeed--;
                }
                else
                {
                    unk_x_3 = ashr16(ray.screen_x_pos - unk_x_2, 2);
                    if (unk_x_3 > dhspeed)
                        dhspeed++;
                    else if (unk_x_3 < dhspeed)
                        dhspeed--;
                }
            }

            if (dans_la_map_monde)
            {
                if (__builtin_abs(dhspeed) > 4)
                    dhspeed = dhspeed > 0 ? 4 : -4;
            }

            h_scroll_speed += ashr16(dhspeed, 2);
            if (
                (unk_x_2 > ray.screen_x_pos && ray.speed_x < 0) ||
                (unk_x_1 < ray.screen_x_pos && ray.speed_x > 0)
            )
                h_scroll_speed += ray.speed_x;
        }

        if (scroll_y == -1 && ray.field20_0x36 != -1)
        {
            other_obj = &level.objects[ray.field20_0x36];
            if (flags[other_obj->type].flags1 >> OBJ1_USE_INSTANT_SPEED_Y & 1)
                v_scroll_speed += instantSpeed(other_obj->speed_y);
            else
                v_scroll_speed += other_obj->speed_y;
            v_scroll_speed += other_obj->follow_y;
        }
    }
}

/* 31690 80155E90 -O2 -msoft-float */
void RAY_TO_THE_RIGHT(void)
{
    s16 max_x;

    if (ray_mode == MODE_RAY_ON_MS && RayCoince(1))
    {
        ray.speed_x = 0;
        decalage_en_cours = 0;
    }
    ray.x_pos += ray.speed_x;
    max_x = xmap - ray.offset_bx + 300;
    if (ray.x_pos > max_x)
    {
        ray.x_pos = max_x;
        ray.speed_x = 0;
        decalage_en_cours = 0;
        if (ray.main_etat != 2)
            ray.speed_y = 0;
    }
    calc_obj_pos(&ray);
}

/* 3176C 80155F6C -O2 -msoft-float */
void RAY_TO_THE_LEFT(void)
{
    s32 unk_x;
    s16 min_x;

    if (ray_mode == MODE_RAY_ON_MS && RayCoince(0))
    {
        ray.speed_x = 0;
        decalage_en_cours = 0;
    }
    ray.x_pos += ray.speed_x;
    if (scroll_x == -1)
    {
        unk_x = ray.offset_bx - 20;
        min_x = xmap - unk_x;
        if (ray.x_pos < min_x)
        {
            ray.x_pos = min_x;
            decalage_en_cours = 0;
            if (ray.main_etat != 2)
                ray.speed_y = 0;
        }
    }
}

/* 31840 80156040 -O2 -msoft-float */
void make_ray_slide(void)
{
    if (num_world == 5 && ray.main_etat == 4)
    {
        switch (ray.sub_etat)
        {
        case 0:
        case 1:
            ray.speed_y = 1;
            break;
        case 2:
            if (horloge[8] != 0)
                ray.speed_y = 0;
            else
                ray.speed_y = 1;
            break;
        case 3:
            ray.speed_y = 2;
            break;
        }
    }
}

/* 318D8 801560D8 -O2 -msoft-float */
void TEST_FIN_FOLLOW(void)
{
    u16 unk_1;
    s16 btyp;

    if (block_flags[calc_typ_travd(&ray, false)] >> BLOCK_FULLY_SOLID & 1)
        ray.speed_x = 0;

    unk_1 = !(ray.eta[ray.main_etat][ray.sub_etat].flags & 0x40) * 2;
    if (ray.speed_y > 0)
    {
        ray.y_pos -= ray.speed_y;
        btyp = BTYP(ray.x_pos + ray.offset_bx, ray.y_pos + ray.offset_by);
        ray.y_pos += ray.speed_y;
    }
    else
        btyp = (u8) calc_typ_trav(&ray, unk_1);

    if (block_flags[btyp] >> BLOCK_SOLID & 1)
    {
        ray.y_pos -= ray.speed_y;
        if (!(block_flags[ray.btypes[4]] >> BLOCK_SOLID & 1) && ray.speed_y < 0)
        {
            ray.y_pos += 4;
            ray.speed_y = 0;
        }
        else
            recale_position(&ray);

        ray.speed_x = 0;
        ray.field20_0x36 = -1;
    }
}

/* 31AA8 801562A8 -O2 -msoft-float */
void RAY_FOLLOW(void)
{
    s16 other_spd_x;
    s16 other_spd_y;
    Obj *other_obj = &level.objects[ray.field20_0x36];

    if (flags[other_obj->type].flags1 >> OBJ1_USE_INSTANT_SPEED_X & 1)
        other_spd_x = instantSpeed(other_obj->speed_x);
    else
        other_spd_x = (u16) other_obj->speed_x;

    if (flags[other_obj->type].flags1 >> OBJ1_USE_INSTANT_SPEED_Y & 1)
        other_spd_y = instantSpeed(other_obj->speed_y);
    else
        other_spd_y = (u16) other_obj->speed_y;

    ray.speed_x = other_spd_x + ray.speed_x;
    ray.speed_x += other_obj->follow_x; /* a little strange */
    ray.speed_y = other_spd_y + (ray.speed_y + other_obj->follow_y);
    TEST_FIN_FOLLOW();
    if (!(other_obj->flags & FLG(OBJ_ACTIVE)))
        ray.field20_0x36 = -1;
}

/* interesting function... */
/* 31BE8 801563E8 -O2 -msoft-float */
void DO_FIXE(void)
{
    if (status_bar.max_hp == 2)
    {
        status_bar.hp_sprites[0] = 0;
        status_bar.hp_sprites[1] = ray.hit_points;
    }
    else if (ray.hit_points < 3)
    {
        status_bar.hp_sprites[0] = 0;
        status_bar.hp_sprites[1] = ray.hit_points;
    }
    else
    {
        status_bar.hp_sprites[1] = 2;
        status_bar.hp_sprites[0] = ray.hit_points - 2;
    }

    status_bar.lives_digits[1] = status_bar.num_lives % 10;
    status_bar.lives_digits[0] = status_bar.num_lives / 10;
    status_bar.num_wiz = MIN_1(status_bar.num_wiz, 99);
    status_bar.wiz_digits[0] = (status_bar.num_wiz / 10);
    status_bar.wiz_digits[1] = (status_bar.num_wiz % 10U);
}
