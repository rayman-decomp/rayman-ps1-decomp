#include "ray/ray_32398.h"

#ifdef BSS_DEFS
Obj ray;
Obj raytmp;

u8 PS1_ShoulderL;
u8 PS1_ShoulderR;
u8 RAY_MODE_SPEED;
#endif

/* 32398 80156B98 -O2 -msoft-float */
void INIT_RAY_BEGIN(void)
{
    status_bar.max_hp = 2;
    status_bar.num_wiz = 0;
    RayEvts.poing = false;
    RayEvts.hang = false;
    RayEvts.helico = false;
    RayEvts.run = false;
    RayEvts.handstand_dash = false;
    RayEvts.handstand = false;
    RayEvts.luciole = false;
    RayEvts.force_run = 0;
    RayEvts.reverse = 0;
    RayEvts.grap = false;
    ray.flags &= ~FLG(OBJ_FLAG_0);
}

/* 3240C 80156C0C -O2 -msoft-float */
void INIT_RAY(u8 new_lvl)
{
    s16 j;
    Animation *pAVar2;
    u8 *puVar3;
    ObjState **ppOVar4;
    s16 i;
    Obj *cur_obj;
    Obj *pOVar6;
    Obj *pOVar7;
    s16 nb_objs;
    ObjFlags flag_9;

    gele = 0;
    if (ray.main_etat == 6)
        ray_mode = MODE_RAY_ON_MS;
    else
        ray_mode = MODE_RAYMAN;
    compteur_attente = 0;
    if (RayEvts.demi)
    {
        rms.hit_points = ray.hit_points;
        __builtin_memcpy(&ray, &rms, sizeof(rms));
    }
    xmap = 0;
    ymap = 0;
    ray.type = TYPE_RAYMAN;
    ray.screen_x_pos = 0;
    ray.screen_y_pos = 0;
    ray.speed_x = 0;
    ray.speed_y = 0;
    ray.x_pos = 100;
    ray.y_pos = 10;
    ray.offset_bx = 80;
    ray.offset_by = 78;
    ray.offset_hy = 20;
    ray.anim_index = 0;
    ray.anim_frame = 0;
    ray.main_etat = 2;
    ray.sub_etat = 2;
    ray.field20_0x36 = -1;
    ray.field24_0x3e = -1;
    ray.iframes_timer = -1;
    ray.field56_0x69 = 0;
    ray.timer = 0;
    flag_9 = ~FLG(OBJ_FLAG_9);
    ray.flags |= FLG(OBJ_FLIP_X);
    ray_last_ground_btyp = true;
    remoteRayXToReach = 33536;
    ray_stack_is_full = false;
    ray_pos_in_stack = 0;
    ray_se_noie = false;
    ray_in_fee_zone = false;
    no_ray_landing_smoke = false;
    ray.flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
    decalage_en_cours = 0;
    ray.flags = ray.flags & flag_9;
    fin_dark = false;
    in_air_because_hit = false;

    for (i = 0; i < (s16) LEN(pos_stack) - 1; i++)
        pos_stack[i] = ray.x_pos;

    poing.is_active = false;
    poing.is_charging = false;
    if (new_lvl)
        RayEvts.super_helico = false;
    if ((num_level != 9 || num_world != 1) && ModeDemo == 0)
        RayEvts.grain = false;
    RayEvts.demi = false;
    RayEvts.force_run = 0;
    if (save1.rayevts_0 != 0 && save1.save_obj_id != -1)
    {
        RayEvts.demi = false;
        RayEvts.force_run = 0;
        RayEvts.reverse = 0;
        if ((num_world == 6) && (num_level == 3))
            RAY_REVERSE_COMMANDS();
    }
    else
    {
        RayEvts.reverse = 1;
        RAY_REVERSE_COMMANDS();
    }

    j = 0;
    cur_obj = &level.objects[j];
    nb_objs = level.nb_objects;
    while (j < nb_objs)
    {
        if (cur_obj->type == TYPE_RAY_POS)
        {
            xmap = cur_obj->offset_bx + cur_obj->x_pos - 160;
            ymap = cur_obj->y_pos - 10;
            if (xmapmax <= xmap)
                xmap = xmapmax;
            if (ymapmax <= ymap)
                ymap = ymapmax;
            if (xmap < 0)
                xmap = 0;
            if (ymap < 0)
                ymap = 0;
            ray.x_pos = cur_obj->x_pos;
            ray.y_pos = cur_obj->y_pos;
            break;
        }
        cur_obj++;
        j++;
    }
    calc_btyp(&ray);
}

/* 32898 80157098 -O2 -msoft-float */
s16 is_icy_pente(u8 block)
{
    return block_flags[block] >> BLOCK_SLOPE & 1 &&
           block_flags[block] >> BLOCK_SLIPPERY & 1;
}

/* 328D0 801570D0 -O2 -msoft-float */
void STOPPE_RAY_EN_XY(void)
{
    s16 x;
    s16 y;
    u8 btyp_1;
    u8 btyp_2;
    u8 btyp_3;
    u8 btyp_4;
    s16 stop;

    x = ray.offset_bx + ray.x_pos;
    y = ray.offset_by + ray.y_pos;
    if (block_flags[ray.btypes[0]] >> BLOCK_SLOPE & 1)
        y -= 8;

    x += ray.speed_x * 2;
    btyp_1 = BTYP(x, y - 8);
    btyp_2 = BTYP(x, y - 24);
    btyp_3 = BTYP(x, y - 40);
    btyp_4 = BTYP(x, y - 56);

    stop = false;
    if (block_flags[btyp_1] >> BLOCK_FLAG_4 & 1)
        stop = !is_icy_pente(btyp_2);
    if (
        !(ray.eta[ray.main_etat][ray.sub_etat].flags & 0x40) &&
        !RayEvts.demi
    )
    {
        if (
            !stop &&
            ((block_flags[btyp_2] >> BLOCK_FLAG_4 & 1) && !is_icy_pente(btyp_3) ||
             (block_flags[btyp_3] >> BLOCK_FLAG_4 & 1) && !is_icy_pente(btyp_4)
            )
        )
            stop = true;
    }

    if (stop)
    {
        ray.speed_x = 0;
        decalage_en_cours = 0;
        ray.nb_cmd = 0;
        Reset_air_speed(true);
        Reset_air_speed(false);
    }
}

/* 32AF8 801572F8 -O2 -msoft-float */
/* control flow not great? */
void RAY_RESPOND_TO_ALL_DIRS(void)
{
    if (ray_on_poelle == true)
    {
        if (decalage_en_cours == 0 && ray.speed_y == 0)
        {
            if (!rightjoy(0) || ray.flags & FLG(OBJ_FLIP_X))
            {
                if (leftjoy(0) && ray.flags & FLG(OBJ_FLIP_X))
                    RAY_RESPOND_TO_DIR(0);
            }
            else
                RAY_RESPOND_TO_DIR(1);
        }
        else if (decalage_en_cours > 0 && !(ray.flags & FLG(OBJ_FLIP_X)))
            RAY_RESPOND_TO_DIR(1);
        else if (decalage_en_cours < 0 && ray.flags & FLG(OBJ_FLIP_X))
            RAY_RESPOND_TO_DIR(0);

        if (joy_done == 0)
        {
            RAY_RESPOND_TO_NOTHING();
            return;
        }
        else
        {
            compteur_attente = 0;
            return;
        }
    }

    if (RayEvts.reverse == 0)
    {
        if (rightjoy(0) || RayEvts.force_run != 0)
            RAY_RESPOND_TO_DIR(1);
        if (leftjoy(0) && RayEvts.force_run == 0)
            RAY_RESPOND_TO_DIR(0);
        if (downjoy(0) && joy_done == 0 && RayEvts.force_run == 0)
        {
            RAY_RESPOND_TO_DOWN();
            joy_done++;
        }
        if (upjoy(0))
        {
            if (joy_done == 0)
            {
                if (RayEvts.force_run == 0)
                {
                    RAY_RESPOND_TO_UP();
                    joy_done++;
                }
            }
            else
            {
                compteur_attente = 0;
                return;
            }
        }
        if (joy_done != 0)
        {
            compteur_attente = 0;
            return;
        }
        if (RayEvts.force_run == 0)
        {
            RAY_RESPOND_TO_NOTHING();
            return;
        }
        else
        {
            compteur_attente = 0;
            return;
        }
    }
    if (rightjoy(0))
        RAY_RESPOND_TO_DIR(0);
    if (leftjoy(0))
        RAY_RESPOND_TO_DIR(1);
    if (downjoy(0) && joy_done == 0)
    {
        RAY_RESPOND_TO_DOWN();
        joy_done++;
    }
    if (upjoy(0))
    {
        if (joy_done == 0)
        {
            RAY_RESPOND_TO_UP();
            joy_done++;
        }
        else
        {
            compteur_attente = 0;
            return;
        }
    }

    if (joy_done == 0)
        RAY_RESPOND_TO_NOTHING();
    else
        compteur_attente = 0;
}

/* 32E60 80157660 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/ray/ray_32398", DO_RAYMAN);
#else
/* clean up further? */
void DO_RAYMAN(void)
{
    s16 unk_1;
    s16 ray_x; s16 ray_y; s16 ray_w; s16 ray_h;

    v_scroll_speed = 0;
    h_scroll_speed = 0;
    setvol(-1, FUN_801473dc(&ray));
    if (RAY_DEAD())
    {
        ray.ray_dist =
            ((s16) (ray.x_pos + ray.offset_bx) >> 4) +
            ((s16) (ray.y_pos + ray.offset_by) >> 4) * mp.width;

        COLL_RAY_BLK_MORTEL();
        if (scroll_y != -1 && (ray.screen_y_pos + ray.offset_by < 0))
            ray.speed_y = 0;

        if (
            ray.iframes_timer == -1 &&
            ray.eta[ray.main_etat][ray.sub_etat].flags & FLG(3) &&
            COLL_RAY_PIC()
        )
            RAY_HIT(true, null);

        joy_done = 0;
        calc_obj_pos(&ray);

        unk_1 = ray.field20_0x36;
        if (!(unk_1 == -1 && (calc_btyp(&ray), ray.field20_0x36 == unk_1)))
        {
            ray.speed_x = 0;
            ray.speed_y = 0;
        }

        if (!(remoteRayXToReach == -32000 || (ray.eta[ray.main_etat][ray.sub_etat].flags & FLG(6))))
        {
            /* forcing me to use parens around ray.main_etat == 3 part... */
            if (
                (
                    ray.main_etat == 0 &&
                    !(ray.sub_etat == 4 || ray.sub_etat == 5 || ray.sub_etat == 6 ||
                    ray.sub_etat == 7 || ray.sub_etat == 9 || ray.sub_etat == 10)
                ) ||
                (ray.main_etat == 1 && !(ray.sub_etat == 1)) ||
                (ray.main_etat == 3 && !(ray.sub_etat == 1 || (ray.sub_etat == 2 || ray.sub_etat == 3) || ray.sub_etat == 4))
            )
            {
                if (remoteRayXToReach != 0)
                    set_main_and_sub_etat(&ray, 3, 21);
                else
                    set_main_and_sub_etat(&ray, 3, 20);
            }
        }

        if (ray.main_etat == 2 && (ray.sub_etat == 8 || ray.sub_etat == 31))
            RAY_IN_THE_AIR();
        else if (ray.main_etat == 3)
        {
            if (ray.sub_etat == 16)
            {
                DO_GROWING_PLATFORM();
                if (eau_obj_id != -1)
                {
                    level.objects[eau_obj_id].iframes_timer = 1;
                    if (!D_801E64B0)
                        FUN_8013202c();
                }
            }
            else if (ray.sub_etat == 20 || ray.sub_etat == 21)
                remoteControlRay();

            if (!(ray.sub_etat == 22 || ray.sub_etat == 23 || ray.sub_etat == 32))
                RAY_SWIP();
        }
        else
        {
            /* TODO: section still not great? */
            if (
                !ray_on_poelle && RayEvts.force_run == 0 &&
                (ray.main_etat == 0 || ray.main_etat == 1)
            )
            {
                if (FUN_801339f4(0) && !FUN_80133984(0))
                {
                    PS1_ShoulderR = 1;
                    PS1_ShoulderL = 0;
                }
                else if (!FUN_801339f4(0) && FUN_80133984(0))
                {
                    PS1_ShoulderR = 0;
                    PS1_ShoulderL = 1;
                }
                else if (FUN_801339f4(0) && FUN_80133984(0))
                {
                    if (PS1_ShoulderL == 1)
                    {
                        PS1_ShoulderR = 2;
                        PS1_ShoulderL = 0;
                    }
                    else if (PS1_ShoulderR == 1)
                    {
                        PS1_ShoulderR = 0;
                        PS1_ShoulderL = 2;
                    }
                    else if (PS1_ShoulderR == 0 && PS1_ShoulderL == 0)
                    {
                        if (ray.flags & FLG(OBJ_FLIP_X))
                            PS1_ShoulderR = 2;
                        else
                            PS1_ShoulderL = 2;
                    }
                }
                else
                {
                    PS1_ShoulderR = 0;
                    PS1_ShoulderL = 0;
                }

                if (RayEvts.reverse == 0)
                {
                    if (PS1_ShoulderR == 0)
                    {
                        if (PS1_ShoulderL != 0)
                            PS1_RespondShoulderL();
                    }
                    else
                        PS1_RespondShoulderR();
                }
                else
                {
                    if (PS1_ShoulderR == 0)
                    {
                        if (PS1_ShoulderL != 0)
                            PS1_RespondShoulderR();
                    }
                    else
                        PS1_RespondShoulderL();
                }
            }
            else if (PS1_ShoulderR != 0 || PS1_ShoulderL != 0)
            {
                PS1_ShoulderR = 0;
                PS1_ShoulderL = 0;
            }

            if (options_jeu.Fire1ButtonFunc(options_jeu.field11_0x1e))
                RAY_RESPOND_TO_FIRE1();

            if (options_jeu.Fire0ButtonFunc(options_jeu.field12_0x20))
                RAY_RESPOND_TO_FIRE0();

            if (options_jeu.Button3Func(options_jeu.field14_0x24))
                RAY_RESPOND_TO_BUTTON3();

            if (options_jeu.Button4Func(options_jeu.field13_0x22))
                RAY_RESPOND_TO_BUTTON4();

            if (poing.is_charging)
            {
                if (ray.sub_etat == 12)
                    RAY_GROW_FIST();

                if (!options_jeu.Fire0ButtonFunc(options_jeu.field12_0x20))
                    RAY_THROW_FIST();
            }

            if (ray.main_etat == 7)
                RAY_BALANCE();
            else if (ray.main_etat == 2)
                RAY_IN_THE_AIR();
            else if (!options_jeu.Fire1ButtonFunc(options_jeu.field11_0x1e))
                button_released = 1;

            if (PS1_ShoulderR == 0 && PS1_ShoulderL == 0)
                RAY_RESPOND_TO_ALL_DIRS();
        }

        if (RayEvts.reverse != 0)
        {
            GET_SPRITE_POS(&ray, 5, &ray_x, &ray_y, &ray_w, &ray_h);
            star_ray_der->x_pos =
            star_ray_dev->x_pos =
                ray_x + (ray_w >> 1) - star_ray_dev->offset_bx;
            star_ray_der->y_pos =
            star_ray_dev->y_pos =
                ray_y - star_ray_dev->offset_hy;

            star_ray_der->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            star_ray_der->display_prio = 3;
            star_ray_dev->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            star_ray_dev->display_prio = 1;
        }
        else if (RayEvts.force_run != 0)
        {
            if (RayEvts.force_run == 1)
            {
                RayEvts.force_run = 2;
                RayEvts.run = true;
                DO_NOVA(&ray);
                set_main_and_sub_etat(&ray, 1, 3);
            }
            else if (
                !(
                    (ray.main_etat == 1 && (ray.sub_etat == 3 || ray.sub_etat == 7)) ||
                    ray.main_etat == 2
                )
            )
            {
                RayEvts.run = true;
                set_main_and_sub_etat(&ray, 1, 3);
            }
            else if (RayEvts.force_run == 3 && (ray.main_etat != 2))
                RayEvts.force_run = 0;
        }

        if (ray.field20_0x36 != -1)
            RAY_FOLLOW();

        make_ray_slide();
        if (RayEstIlBloque())
        {
            if (ray.main_etat == 7)
                RAY_FIN_BALANCE();

            ray.speed_x = 0;
            decalage_en_cours = 0;
            ray.nb_cmd = 0;
        }

        if (pierreAcorde_obj_id != -1)
            RepousseRay();

        RAY_SURF();
        STOPPE_RAY_EN_XY();
        if (ray.speed_y > 0)
            move_down_ray();
        else if (ray.speed_y < 0)
            move_up_ray();

        if (ray.speed_x < 0)
            RAY_TO_THE_LEFT();
        else if (ray.speed_x > 0)
            RAY_TO_THE_RIGHT();

        if (ray.flags & FLG(OBJ_ALIVE) && ray.main_etat != 7)
        {
            DO_ANIM(&ray);
            DO_SURF_CHANGE_HAIRS();
        }

        if (!(new_world || new_level))
        {
            GET_RAY_ZDC(&ray, &ray_zdc_x, &ray_zdc_y, &ray_zdc_w, &ray_zdc_h);
            DO_COLLISIONS();
        }

        if (fin_boss)
            TEST_SIGNPOST();
    }

    stackRay();
}
#endif

/* 339AC 801581AC -O2 -msoft-float */
void DO_RAY_ON_MS(void)
{
    v_scroll_speed = 0;
    h_scroll_speed = 0;
    if (!RAY_DEAD())
        return;

    if (++ray.gravity_value_1 > 3)
        ray.gravity_value_1 = 0;
    ray.ray_dist = ((s16) (ray.offset_bx + ray.x_pos) >> 4) + ((s16) (ray.offset_by + ray.y_pos) >> 4) * mp.width;
    if (
        (ray.screen_x_pos + ray.offset_bx + 30) < 0 ||
        (ray.screen_y_pos + ray.offset_by + 20) < 0 ||
        290 < ray.screen_x_pos || 200 < ray.screen_y_pos
    )
    {
        ray.hit_points = 0;
        RAY_HURT();
    }

    if (
        ray.iframes_timer == -1 &&
        ray.eta[ray.main_etat][ray.sub_etat].flags & 8 &&
        COLL_RAY_PIC()
    )
        RAY_HIT(true, null);

    joy_done = 0;
    calc_obj_pos(&ray);
    if (ray.field20_0x36 == -1)
        calc_btyp(&ray);

    if (ray.main_etat != 3 && (ray.main_etat != 6 || ray.sub_etat != 14))
    {
        if (
            options_jeu.Fire0ButtonFunc(options_jeu.field12_0x20) &&
            ray.sub_etat != 4 && ray.sub_etat != 2 && ray.sub_etat != 8 &&
            ray.sub_etat != 5 && ray.sub_etat != 3
        )
            RAY_RESPOND_TO_FIRE0();

        if (options_jeu.Button3Func(options_jeu.field14_0x24))
            RAY_RESPOND_TO_BUTTON3();
        if (options_jeu.Button4Func(options_jeu.field13_0x22))
            RAY_RESPOND_TO_BUTTON4();
        if (poing.is_charging)
        {
            if (ray.sub_etat == 12)
                RAY_GROW_FIST();
            if (!options_jeu.Fire0ButtonFunc(options_jeu.field12_0x20))
                RAY_THROW_FIST();
        }
        if (rightjoy(0))
            RAY_RESPOND_TO_DIR(1);
        if (leftjoy(0))
            RAY_RESPOND_TO_DIR(0);
        if (downjoy(0))
        {
            RAY_RESPOND_TO_DOWN();
            joy_done++;
        }
        if (upjoy(0))
        {
            RAY_RESPOND_TO_UP();
            joy_done++;
        }
        if (joy_done == 0)
            RAY_RESPOND_TO_NOTHING();
        if (ray.screen_x_pos < -20 && ray.speed_x < 0)
            ray.speed_x = 0;
        if (ray.screen_x_pos > 210 && ray.speed_x > 0)
            ray.speed_x = 0;
        if (ray.screen_y_pos < 3 && ray.speed_y < 0)
            ray.speed_y = 0;
        if ((ray.screen_y_pos + ray.offset_by >= 231) && ray.speed_y > 0)
            ray.speed_y = 0;
    }
    if (ray.speed_y > 0)
        move_down_ray();
    else if (ray.speed_y < 0)
        move_up_ray();
    if (ray.speed_x < 0)
        RAY_TO_THE_LEFT();
    else if (ray.speed_x > 0)
        RAY_TO_THE_RIGHT();
    if (ray.flags & FLG(OBJ_ALIVE))
        DO_ANIM(&ray);

    GET_RAY_ZDC(&ray, &ray_zdc_x, &ray_zdc_y, &ray_zdc_w, &ray_zdc_h);
    DO_COLLISIONS();
}

/* 33F1C 8015871C -O2 -msoft-float */
void DO_PLACE_RAY(void)
{
    h_scroll_speed = 0;
    v_scroll_speed = 0;
    ray.speed_x = 0;
    ray.speed_y = 0;

    if (rightjoy(0))
        ray.speed_x += RAY_MODE_SPEED;
    else if (leftjoy(0))
        ray.speed_x -= RAY_MODE_SPEED;

    if (downjoy(0))
        ray.speed_y += RAY_MODE_SPEED / 2;
    else if (upjoy(0))
        ray.speed_y -= RAY_MODE_SPEED / 2;

    if (ray.speed_y >= 1)
        move_down_ray();
    else if (ray.speed_y < 0)
        move_up_ray();

    calc_obj_pos(&ray);
    if (ray.speed_x < 0)
        RAY_TO_THE_LEFT();
    else if (ray.speed_x > 0)
        RAY_TO_THE_RIGHT();

    h_scroll_speed = ray.speed_x;
    v_scroll_speed = ray.speed_y;
}
