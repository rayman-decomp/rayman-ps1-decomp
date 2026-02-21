#include "moteur_update.h"

#ifdef BSS_DEFS
Obj *star_ray_der;
Obj *star_ray_dev;
s16 ray_wind_force;
s16 weather_wind;
s16 PS1_StartMoteurRayX;
s16 PS1_StartMoteurRayY;
u8 PS1_MoteurTime;
u8 oldPrio;
s16 ray_old_main_etat;
s16 ray_old_sub_etat;
s16 xmap_old;
s16 ymap_old;
s16 reduced_rayman_id;
u8 D_801F57F0;
#endif

/* 35314 80159B14 -O2 -msoft-float */
void PS1_SetWindForce(void)
{
    if (num_world == 3)
        ray_wind_force = 0;
    else
        ray_wind_force = weather_wind;
}

/* 35354 80159B54 -O2 -msoft-float */
void DO_MOTEUR(void)
{
    fades();
    horloges();
    calc_left_time();
    ray_old_main_etat = ray.main_etat;
    ray_old_sub_etat = ray.sub_etat;
    PS1_StartMoteurRayX = ray.x_pos;
    PS1_StartMoteurRayY = ray.y_pos;
    PS1_MoteurTime++;
    xmap_old = xmap;
    ymap_old = ymap;
    if (ray.field20_0x36 != -1)
        level.objects[ray.field20_0x36].display_prio = oldPrio;
    if (RayEvts.luciole)
        DO_LUCIOLE();
    PS1_SetWindForce();
    DO_OBJECTS();
}

/* 3545C 80159C5C -O2 -msoft-float */
void DO_MOTEUR2(void)
{
    Obj *unk_1;

    DO_WIZ_AFTER_BONUS_MAP();
    DO_PERFECT_BONUS_MAP();
    DO_PHOTOGRAPHE_CMD();
    DO_OBJECTS_ANIMS();
    if (ray.flags & FLG(OBJ_ALIVE))
    {
        if (dead_time != 64)
            ray.field20_0x36 = -1;
        switch (ray_mode)
        {
        case MODE_RAYMAN:
            DO_RAYMAN();
            break;
        case MODE_RAY_ON_MS:
            if (ray.main_etat != 6)
                set_main_and_sub_etat(&ray, 6, 0);
            DO_RAY_ON_MS();
            break;
        case MODE_MORT_DE_RAYMAN:
        case MODE_MORT_DE_RAYMAN_ON_MS:
            DO_MORT_DE_RAY();
            break;
        default:
            DO_PLACE_RAY();
            break;
        }

        if (NumScrollObj > 0 && ray_mode > MODE_NONE)
            DO_AUTO_SCROLL();
        else
        {
            scroll_x = -1;
            scroll_y = -1;
        }
        MOVE_OBJECTS();
        calc_obj_pos_map(&ray);
        if (scroll_y != -1 && v_scroll_speed == 0x00FF)
            v_scroll_speed = 0;
        if (gele == 0 && ray_mode > MODE_NONE)
            recale_ray_pos();
        if (ray_mode == MODE_RAY_ON_MS)
        {
            if (scroll_x != -1)
            {
                scroll_x = ray.speed_x;
                ray.speed_x = h_scroll_speed;
                if ((s16) h_scroll_speed > 0)
                    RAY_TO_THE_RIGHT();
                else if ((s16) h_scroll_speed < 0)
                    RAY_TO_THE_LEFT();
                ray.speed_x = scroll_x;
            }
            if (ray.sub_etat != 14)
            {
                switch (ray.sub_etat)
                {
                case 0:
                    if (__builtin_abs(ray.speed_x) >= 2 || __builtin_abs(h_scroll_speed) >= 2)
                        set_sub_etat(&ray, 6);
                    break;
                case 1:
                    if (__builtin_abs(ray.speed_x) < 2 && __builtin_abs(h_scroll_speed) < 2)
                        set_sub_etat(&ray, 7);
                    else
                    {
                        if (__builtin_abs(h_scroll_speed) >= 5 && (xmap < xmapmax - 100))
                        {
                            set_sub_etat(&ray, 2);
                            change_audio_track_moskito_acc();
                        }
                    }
                    break;
                case 5:
                    if (__builtin_abs(h_scroll_speed) < 5)
                    {
                        set_sub_etat(&ray, 3);
                        change_audio_track_moskito_dec();
                    }
                    break;
                }
                if (xmap == xmapmax)
                    scroll_start_x = xmap;
            }
            level.objects[poing_obj_id].x_pos += h_scroll_speed;
            level.objects[poing_obj_id].y_pos += v_scroll_speed;
        }
        DO_SCROLL_MAP(&h_scroll_speed, &v_scroll_speed);
        build_active_table();
        RECALE_ALL_OBJECTS();
        if (ray.field20_0x36 != -1)
        {
            unk_1 = &level.objects[ray.field20_0x36];
            oldPrio = unk_1->display_prio;
            if (oldPrio > 3)
                unk_1->display_prio = 3;
        }
    }
    else
    {
        MOVE_OBJECTS();
        scroll_y = -1;
        build_active_table();
        dead_time--;
    }
    DO_FIXE();
    do_flocons(xmap, ymap, xmap_old, ymap_old);
    DO_SNOW_SEQUENCE();
    do_pix_gerbes();
    if (RayEvts.demi)
    {
        set_zoom_mode(0);
        ray.scale = 0x100;
        if (ray.flags & FLG(OBJ_FLIP_X))
            set_proj_center(ray.screen_x_pos - 8 + ray.offset_bx, ray.screen_y_pos + ray.offset_by);
        else
            set_proj_center(ray.screen_x_pos + ray.offset_bx, ray.screen_y_pos + ray.offset_by);
    }
    AVOID_SOME_BUGS();
}

/* 35A58 8015A258 -O2 -msoft-float */
void RAY_REVERSE_COMMANDS(void)
{
    if (RayEvts.reverse == 0)
    {
        RayEvts.reverse = 1;
        if (star_ray_der != null)
        {
            star_ray_der->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
            star_ray_der->display_prio = 3;
        }
        if (star_ray_dev != null)
        {
            star_ray_dev->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
            star_ray_dev->display_prio = 1;
        }
    }
    else
    {
        RayEvts.reverse = 0;
        if (star_ray_der != null)
        {
            star_ray_der->flags &= ~FLG(OBJ_ALIVE);
            star_ray_der->flags &= ~FLG(OBJ_ACTIVE);
            star_ray_der->display_prio = 3;
        }
        if (star_ray_dev != null)
        {
            star_ray_dev->flags &= ~FLG(OBJ_ALIVE);
            star_ray_dev->flags &= ~FLG(OBJ_ACTIVE);
            star_ray_dev->display_prio = 3;
        }
    }
}

/* 35B30 8015A330 -O2 -msoft-float */
void RAY_DEMIRAY(void)
{
    RayEvts.demi = !RayEvts.demi;
    if (RayEvts.demi)
    {
        __builtin_memcpy(&rms, &ray, sizeof(ray));
        __builtin_memcpy(&ray, &level.objects[reduced_rayman_id], sizeof(Obj));
        ray.animations = rms.animations;
        PlaySnd(206, -1);
    }
    else
    {
        __builtin_memcpy(&raytmp, &rms, sizeof(rms));
        __builtin_memcpy(&rms, &ray, sizeof(ray));
        __builtin_memcpy(&ray, &raytmp, sizeof(raytmp));
        PlaySnd(207, -1);
    }
    ray.type = TYPE_RAYMAN;
    ray.screen_x_pos = rms.screen_x_pos;
    ray.screen_y_pos = rms.screen_y_pos;
    ray.speed_x = rms.speed_x;
    ray.speed_y = rms.speed_y;
    ray.x_pos = rms.x_pos;
    ray.y_pos = rms.y_pos;
    ray.offset_bx = rms.offset_bx;
    ray.offset_by = rms.offset_by;
    ray.offset_hy = rms.offset_hy;
    ray.anim_index = rms.anim_index;
    ray.anim_frame = rms.anim_frame;
    ray.flags = ray.flags & ~FLG(OBJ_FLIP_X) | rms.flags & FLG(OBJ_FLIP_X);
    ray.field23_0x3c = rms.field23_0x3c;
    ray.main_etat = rms.main_etat;
    ray.sub_etat = rms.sub_etat;
    ray.field20_0x36 = rms.field20_0x36;
    ray.flags = ray.flags | (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
    ray.field24_0x3e = rms.field24_0x3e;
    ray.iframes_timer = rms.iframes_timer;
    ray.field56_0x69 = rms.field56_0x69;
    ray.timer = rms.timer;
    ray.hit_points = rms.hit_points;
    ray.init_hit_points = rms.init_hit_points;
    ray.hit_sprite = rms.hit_sprite;

    if (block_flags[(u8) calc_typ_trav(&ray, 2)] >> BLOCK_FLAG_4 & 1)
        set_main_and_sub_etat(&ray, 0, 15);
}

/* 35EF0 8015A6F0 -O2 -msoft-float */
void DO_MOTEUR_GELE(void)
{
    if (gele != 3)
    {
        if (gele == 2)
        {
            horloges();
            TEST_SIGNPOST();
            h_scroll_speed = 0;
            v_scroll_speed = 0;
            DO_ANIM(&ray);
        }
        else
            DO_MEDAILLON_TOON_GELE();
    }
}

/* 35F64 8015A764 -O2 -msoft-float */
void FUN_8015a764(void)
{
    if (gele != 3)
    {
        D_801F57F0 = gele;
        gele = 3;
    }
    else
        gele = D_801F57F0;
}
