#include "moteur_init_end.h"

#ifdef BSS_DEFS
s16 bonus_map;
s16 xmapmax;
s16 ymapmax;
Obj rms;
s16 ray_X_main_pos_init;
s16 ray_Y_main_pos_init;
s16 xmapsave;
s16 ymapsave;
u8 D_801F75C0;
u8 NewMs;
#endif

/* 347C4 80158FC4 -O2 -msoft-float */
void INIT_MOTEUR(u8 new_lvl)
{
    s16 i; s16 j; s16 *cur_data;
    u8 prev_num_wiz;

    for (i = 0; i < (s16) LEN(pix_gerbe); i++)
    {
        pix_gerbe[i].is_active = false;

        cur_data = (s16 *) &pix_gerbe[i].items[0];
        for (j = 0; j < (s16) (sizeof(pix_gerbe[i].items) / sizeof(s16)); j++)
            *cur_data++ = 0;
    }

    init_flocons();
    if (num_world == 1 && num_level == 9)
        set_SNSEQ_list(11);

    scrollLocked = false;
    Vignet_To_Display = 0;
    loop_time = 0;
    dans_la_map_monde = false;
    sko_rayon_on = 0;
    rubis_list_calculated = false;
    sko_last_action = 0;
    sko_enfonce_enable = 0;
    pixels_enfonce = 0;
    joe_exp_probleme = finBosslevel.helped_joe_2;
    if (num_world == 5 && num_level == 10)
    {
        mp.height = 32;
        ymapmax = scroll_end_y = 312;
    }
    map_time = 0;
    left_time = -2;
    INIT_HORLOGES();
    ray.id = -1;
    actobj.num_active_objects = 0;
    actobj.objects[0] = -1;
    xmap = 0;
    ymap = 0;
    ymapmax = (mp.height * 16) - SCREEN_HEIGHT;
    xmapmax = ((u16) mp.width * 16) - (SCREEN_WIDTH + 1);
    MAX_2(xmapmax, 0);
    MAX_2(ymapmax, 0);
    v_scroll_speed = 0;
    h_scroll_speed = 0;
    dvspeed = 0;
    dhspeed = 0;
    scroll_start_x = 0;
    scroll_start_y = 0;
    jump_time = 0;
    gerbe = false;
    PS1_MoteurTime = 0;
    decalage_en_cours = 0;
    ray_wind_force = 0;
    weather_wind = 0;
    screen_trembling = 0;
    lidol_to_allocate = 0;
    helico_time = -1;
    fin_boss = false;
    scroll_end_x = xmapmax;
    scroll_end_y = ymapmax;
    if (!fin_du_jeu)
        dead_time = 64;

    INIT_RAY(new_lvl);
    if (!bonus_map && departlevel && save1.has_saved)
    {
        prev_num_wiz = status_bar.num_wiz;
        restoreGameState(&save1);
        status_bar.num_wiz = prev_num_wiz;
    }

    if (!departlevel)
    {
        ray.flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
        ray.x_pos = ray_X_main_pos_init;
        ray.y_pos = ray_Y_main_pos_init;
        xmap = xmapsave;
        ymap = ymapsave;
    }
    else
        nb_wiz_collected = 0;

    INIT_OBJECTS(new_lvl);
    correct_link();
    deactivate_ship_links();
    special_flags_init();
    if (RayEvts.luciole)
        INIT_LUCIOLE();

    DO_OBJECTS();
    DO_PHOTOGRAPHE_CMD();
}

/* 34BC8 801593C8 -O2 -msoft-float */
void INIT_MOTEUR_BEGIN(void)
{
    fptr_init();
    PS1_InitAllowedTime();
    init_bonus_perfect();
    LOAD_CONFIG();
    init_finBossLevel();
    new_level = true;
    new_world = true;
    status_bar.num_lives = 3;
    ray.hit_points = 2;
    poing.sub_etat = 1;
    departlevel = true;
    nb_continue = 5;
    gele = 0;
    You_Win = false;
    PS1_RandSum = 17171;
    RandomIndex = 0;
    set_proj_center(160, 170);
    INIT_RAY_BEGIN();
    scroll_x = -1;
    scroll_y = -1;
    special_ray_mov_win_x_left = 0;
    special_ray_mov_win_x_right = 0;
    D_801F75C0 = 0;
    NumDemo = 0;
    PS1_ShouldClearPassword = 1;
    PS1_CardShouldCheckFirstBoot = true;
    left_time = 0;
    life_becoz_wiz = false;
    RunTimeDemo = 1800;
}

/* 34CE8 801594E8 -O2 -msoft-float */
void INIT_MOTEUR_WORLD(void)
{
    new_world = false;
    new_level = true;
}

/* 34D04 80159504 -O2 -msoft-float */
void INIT_MOTEUR_LEVEL(s16 new_lvl)
{
    if (!fin_du_jeu)
    {
        bonus_map = (s16) get_allowed_time() != -2;
        if (!bonus_map && departlevel)
            initGameSave();
        INIT_MOTEUR(new_lvl);
        if (!bonus_map && departlevel)
        {
            saveGameState(null, &save1);
            saveGameState(null, &save2);
            life_becoz_wiz = false;
        }

        if (!departlevel)
        {
            departlevel = true;
            restore_objects_flags();
        }
        else
            nb_wiz_collected = 0;

        correct_gendoor_link();
        new_level = false;
        ray_mode = MODE_RAYMAN;
        RAY_MODE_SPEED = 16;
    }
}

/* 34E30 80159630 -O2 -msoft-float */
void restore_gendoor_link(void)
{
    s16 i;
    s16 oid;
    s16 nb_objects;
    s16 init_oid;
    Obj *object;

    object = level.objects;
    nb_objects = level.nb_objects;

    for (i = 0; i < nb_objects; i++)
    {
        if (object->type == 0xA4)
        {
            if (object->flags & 0x400)
            {
                init_oid = object->field24_0x3e;
                do
                {
                    oid = init_oid;
                    init_oid = link_init[init_oid];
                } while (init_oid != object->field24_0x3e);

                link_init[object->id] = init_oid;
                link_init[oid] = object->id;

                object->flags = object->flags | 0x1000;
                level.objects[oid].flags |= 0x1000;
            }
            else
            {
                oid = object->id;
                init_oid = save1.link_init[oid];

                while (object->id != init_oid)
                {
                    init_oid = save1.link_init[oid];
                    link_init[oid] = init_oid;

                    if (oid != init_oid)
                    {
                        level.objects[oid].flags |= 0x1000;
                    }
                    else
                    {
                        level.objects[oid].flags &= ~0x1000;
                    }
                    oid = init_oid;
                }
            }
        }

        object++;
    }
}

/* 34FEC 801597EC -O2 -msoft-float */
void DONE_MOTEUR_LEVEL(void)
{
    restore_gendoor_link();
    if (!bonus_map && departlevel && !get_next_bonus_level(num_level))
        doneGameSave();

    if (rayman_obj_id != -1 && (new_level || new_world))
    {
        __builtin_memcpy(&raytmp, &ray, sizeof(ray));
        __builtin_memcpy(&ray, &rms, sizeof(rms));
        INIT_RAY(true);
        ray.hit_points = raytmp.hit_points;
        ray.init_hit_points = raytmp.init_hit_points;
        ray.hit_sprite = raytmp.hit_sprite;
        set_main_and_sub_etat(&ray, 0, 0);
        ray_mode = MODE_NONE;
    }

    if (first_boss_meet)
        Change_Wait_Anim();

    if (fee_obj_id != -1)
        record.is_playing = false;
}

/* 351A0 801599A0 -O2 -msoft-float */
void INIT_MOTEUR_DEAD(void)
{
    if (dead_time == 0)
    {
        restore_gendoor_link();
        INIT_MOTEUR(false);
        correct_gendoor_link();
    }
}

/* 351DC 801599DC -O2 -msoft-float */
void INIT_RAY_ON_MS(u8 *new_ms)
{
    if (*new_ms && rayman_obj_id != -1)
    {
        __builtin_memcpy(&rms, &ray, sizeof(ray));
        __builtin_memcpy(&ray, &level.objects[rayman_obj_id], sizeof(level.objects[rayman_obj_id]));
        INIT_RAY(true);
        ray.hit_points = rms.hit_points;
        ray.init_hit_points = rms.init_hit_points;
        ray.hit_sprite = rms.hit_sprite;
        set_main_and_sub_etat(&ray, 6, 0);
        ray_mode = MODE_RAY_ON_MS;
        *new_ms = false;
    }
}
