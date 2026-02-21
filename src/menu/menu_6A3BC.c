#include "menu/menu_6A3BC.h"

#ifdef BSS_DEFS
Obj clock_obj;
s16 loop_timing;
u8 nb_continue;
u8 Etape_History;
u8 fin_continue;
Obj bigray;
#endif

/* 6A3BC 8018EBBC -O2 -msoft-float */
void INIT_NEW_GAME(void)
{
    s16 i;

    new_level = true;
    new_world = true;
    status_bar.num_lives = 3;
    ray.hit_points = 2;
    poing.sub_etat = 1;
    departlevel = true;
    fin_du_jeu = false;
    nb_continue = 5;
    ray.flags &= ~FLG(OBJ_FLAG_0);
    memset(wi_save_zone, 0, LEN(wi_save_zone));
    memset(save_zone, 0, LEN(save_zone));
    INIT_RAY_BEGIN();

    t_world_info[0].is_unlocked = true;
    t_world_info[0].is_unlocking = false;
    t_world_info[0].has_drawn_path = false;
    t_world_info[0].nb_cages = 0;
    for (i = 1; i < (s16) LEN(t_world_info); i++)
    {
        t_world_info[i].is_unlocked = false;
        t_world_info[i].is_unlocking = false;
        t_world_info[i].has_drawn_path = false;
        t_world_info[i].nb_cages = 0;
    }

    loadInfoRay[positiony - 1].num_lives = 3;
    loadInfoRay[positiony - 1].num_wiz = 0;
    loadInfoRay[positiony - 1].num_cages = 0;
    loadInfoRay[positiony - 1].num_continues = 5;

    for (i = 0; i < (s16) LEN(bonus_perfect) - 1; i++)
        bonus_perfect[i] = 0;

    init_finBossLevel();
    INIT_WORLD_INFO();

    #ifdef CHEATS
    for (i = 1; i < (s16) LEN(t_world_info); i++)
    {
        t_world_info[i].is_unlocked = true;
    }
    ((u8*)&RayEvts)[0] = 0x87;
    ((u8*)&RayEvts)[1] = 0x01;
    #endif
}

/*
TODO: not sure what we need to do about these warnings
changing OptionsJeu.Fire1ButtonFunc etc. to return s32 forces casts in other places?
*/
/* 6A5F0 8018EDF0 -O2 -msoft-float */
void POINTEUR_BOUTONS_OPTIONS_BIS(void)
{
    s16 (*but0)() = &but0pressed;
    s16 val0 = 0;
    s16 (*but1)() = &but1pressed;
    s16 val1 = 0;
    s16 (*but2)() = &but2pressed;
    s16 val2 = 0;
    s16 (*but3)() = &but3pressed;
    s16 val3 = 0;

    switch (options_jeu.Jump)
    {
    case 0:
        options_jeu.Fire1ButtonFunc = but0;
        options_jeu.field11_0x1e = val0;
        break;
    case 1:
        options_jeu.Fire1ButtonFunc = but1;
        options_jeu.field11_0x1e = val1;
        break;
    case 2:
        options_jeu.Fire1ButtonFunc = but2;
        options_jeu.field11_0x1e = val2;
        break;
    case 3:
        options_jeu.Fire1ButtonFunc = but3;
        options_jeu.field11_0x1e = val3;
        break;
    }

    switch (options_jeu.Fist)
    {
    case 0:
        options_jeu.Fire0ButtonFunc = but0;
        options_jeu.field12_0x20 = val0;
        break;
    case 1:
        options_jeu.Fire0ButtonFunc = but1;
        options_jeu.field12_0x20 = val1;
        break;
    case 2:
        options_jeu.Fire0ButtonFunc = but2;
        options_jeu.field12_0x20 = val2;
        break;
    case 3:
        options_jeu.Fire0ButtonFunc = but3;
        options_jeu.field12_0x20 = val3;
        break;
    default:
        break;
    }

    switch (options_jeu.field6_0x14)
    {
    case 0:
        options_jeu.Button4Func = but0;
        options_jeu.field13_0x22 = val0;
        break;
    case 1:
        options_jeu.Button4Func = but1;
        options_jeu.field13_0x22 = val1;
        break;
    case 2:
        options_jeu.Button4Func = but2;
        options_jeu.field13_0x22 = val2;
        break;
    case 3:
        options_jeu.Button4Func = but3;
        options_jeu.field13_0x22 = val3;
        break;
    }

    switch (options_jeu.Action)
    {
    case 0:
        options_jeu.Button3Func = but0;
        options_jeu.field14_0x24 = val0;
        break;
    case 1:
        options_jeu.Button3Func = but1;
        options_jeu.field14_0x24 = val1;
        break;
    case 2:
        options_jeu.Button3Func = but2;
        options_jeu.field14_0x24 = val2;
        break;
    case 3:
        options_jeu.Button3Func = but3;
        options_jeu.field14_0x24 = val3;
        break;
    }
}

/* 6A890 8018F090 -O2 -msoft-float */
/*? display_text(? *, s16, s16, s32);*/

void DISPLAY_SYMBOLE(s16 button, s16 x, s16 y, u8 font_size, u8 param_5)
{
    switch (button)
    {
    case 0:
        display_text((u8 *) &PS1_Button_Text_Square, x, y, font_size, 0);
        break;
    case 1:
        display_text((u8 *) &PS1_Button_Text_Cross, x, y, font_size, 14);
        break;
    case 2:
        display_text((u8 *) &PS1_Button_Text_Triangle, x, y, font_size, 8);
        break;
    case 3:
        display_text((u8 *) &PS1_Button_Text_Circle, x, y, font_size, 2);
        break;
    }
}

/* 6A948 8018F148 -O2 -msoft-float */
/*void set_zoom_mode(u8 zoomMode);
? set_main_etat(s16 *, ?);
? set_sub_etat(s16 *, ?);*/

void INIT_CONTINUE(void)
{
    Obj *mapobj_1;
    Obj *mapobj_2;
    Obj *mapobj_3;

    loop_nb_trames = 0;
    loop_timing = 10;
    fin_continue = false;
    compteur = 0;
    joy_done = 0;
    Etape_History = 0;
    ray.y_pos = 135 - ray.offset_by;
    ray.anim_frame = 0;
    if (nb_continue != 0)
    {
        set_main_and_sub_etat(&ray, 3, 24);
        ray.x_pos = 225 - ray.offset_bx;
    }
    else
    {
        ray.x_pos = 80 - ray.offset_bx;
        set_main_etat(&ray, 3);
        loop_timing = 0xff;
        if (horloge[20] >= 11)
            set_sub_etat(&ray, 51);
        else
            set_sub_etat(&ray, 50);
    }

    ray.flags &= ~FLG(OBJ_FLIP_X);
    ray.speed_x = 0;
    ray.speed_y = 0;
    set_zoom_mode(0);
    clock_obj.x_pos = 80;
    clock_obj.y_pos = 130;
    set_main_and_sub_etat(&clock_obj, 0, 0);
    mapobj_1 = mapobj;
    mapobj_1->offset_bx = 80;
    mapobj_1->screen_x_pos = 120;
    mapobj_1->screen_y_pos = 110;
    mapobj_2 = mapobj;
    mapobj_2->offset_by = 64;
    mapobj_3 = mapobj;
    mapobj_3->timer = 0;
    mapobj_3->flags &= ~FLG(OBJ_ALIVE);
    set_main_and_sub_etat(mapobj, 5, 20);
    xmapinit = xmap;
    ymapinit = ymap;
    xmap = 0;
    ymap = 0;
    PROC_EXIT = false;
}

/* 6AB48 8018F348 -O2 -msoft-float */
void CHEAT_MODE_CONTINUE(void)
{
    if (joy_done == 0 && ++compteur >= 6)
        compteur = 0;

    if (compteur == 0)
    {
        if (upjoy(0))
            joy_done = 1;
        else if (downjoy(0))
            joy_done = 2;
        else if (rightjoy(0))
            joy_done = 3;
        else if (leftjoy(0))
            joy_done = 4;
    }

    switch (Etape_History)
    {
    case 0:
        if (joy_done == 1 && nb_continue < 4)
        {
            joy_done = 0;
            Etape_History++;
        }
        else if (joy_done != 0)
            Etape_History = 0;
        break;
    case 1:
        if (joy_done == 2)
        {
            joy_done = 0;
            Etape_History++;
        }
        else if (joy_done != 0)
            Etape_History = 0;
        break;
    case 2:
        if (joy_done == 3)
        {
            joy_done = 0;
            Etape_History++;
        }
        else if (joy_done != 0)
            Etape_History = 0;
        break;
    case 3:
        if (joy_done == 4)
            nb_continue = 10;
        else if (joy_done != 0)
            Etape_History = 0;
        break;
    }
}

/* 6AD14 8018F514 -O2 -msoft-float */
void MAIN_CONTINUE_PRG(void)
{
    u8 flag_set;

    horloges();
    manage_snd();
    if (but0pressed__CROSS() || but1pressed__START() || but2pressed__SELECT())
    {
        if (ray.sub_etat == 25 || ray.sub_etat == 26 || ray.sub_etat == 27)
        {
            if (mapobj->timer != 128)
                mapobj->flags |= FLG(OBJ_ALIVE);
            start_cd_continue();
            PlaySnd_old(216);
            if (ray.sub_etat != 27)
                set_main_and_sub_etat(&ray, 3, 31);
            else
            {
                set_main_and_sub_etat(&ray, 3, 29);
                ray.flags |= FLG(OBJ_FLIP_X);
            }
            ray.anim_frame = 0;
            set_main_and_sub_etat(&clock_obj, 0, 1);
        }
    }
    SET_X_SPEED(&ray);
    ray.speed_x = instantSpeed(ray.speed_x);
    switch (ray.sub_etat)
    {
    case 25:
        if (ray.x_pos + ray.offset_bx < 70)
        {
            set_main_and_sub_etat(&ray, 3, 26);
            ray.anim_frame = 0;
        }
        break;
    case 26:
        if (ray.anim_frame >= 7)
            ray.speed_x = 0;
        break;
    case 27:
        if (++loop_nb_trames == 60)
        {
            loop_nb_trames = 0;
            loop_timing--;
        }
        break;
    case 31:
        if (EOA(&ray) && horloge[2] != 0)
            ray.flags |= FLG(OBJ_FLIP_X);
        break;
    case 29:
        ray.flags |= FLG(OBJ_FLIP_X);
        if ((ray.x_pos + ray.offset_bx > 180) && EOA(&ray))
        {
            set_sub_etat(&ray, 28);
            ray.anim_frame = 0;
        }
        else
        {
            if (ray.anim_frame < 64)
                ray.speed_x = 0;
        }
        break;
    case 30:
        if (ray.x_pos + ray.offset_bx > 175 && EOA(&ray))
        {
            set_sub_etat(&ray, 28);
            ray.anim_frame = 0;
        }
        break;
    case 28:
        if (ray.anim_frame > 40)
            fin_continue = true;
        if (ray.anim_frame > 16)
            ray.speed_x = 0;
        break;
    default:
        break;
    }

    if (horloge[2] == 0)
    {
        ray.x_pos = ray.x_pos + ray.speed_x;
        calc_obj_pos_map(&ray);
        DO_ANIM(&ray);
    }

    calc_obj_pos_map(&clock_obj);
    DO_ANIM(&clock_obj);
    if (mapobj->flags & FLG(OBJ_ALIVE))
    {
        DO_ANIM(mapobj);
        if (EOA(mapobj))
        {
            if (mapobj->timer != 128)
                nb_continue--;
            mapobj->flags &= ~FLG(OBJ_ALIVE);
        }
    }
    if (loop_timing != 0xFF)
        CHEAT_MODE_CONTINUE();
    else
        MAIN_NO_MORE_CONTINUE_PRG();
}

/* 6B4C4 8018FCC4 -O2 -msoft-float */
void FIN_CONTINUE_PRG(void)
{
    if (loop_timing == 0xff)
    {
        fin_du_jeu = true;
        menuEtape = 0;
    }
    else if (loop_timing != -1)
    {
        status_bar.num_lives = 3;
        ray.hit_points = 2;
        status_bar.max_hp = 2;
        fin_du_jeu = false;
        LOAD_VIGNET_GAME();
    }
    else
        menuEtape = 0;
    xmap = xmapinit;
    ymap = ymapinit;
}

/* 6B568 8018FD68 -O2 -msoft-float */
void MAIN_NO_MORE_CONTINUE_PRG(void)
{
    PROC_EXIT = but2pressed__SELECT() != false;
    if (EOA(&ray))
        PROC_EXIT = true;

    if (PROC_EXIT)
        fin_continue = true;
}

const u8 s_tarayzan_gives_rayman_a_magic_s_8012bad0[] = "/tarayzan gives rayman a magic seed/";
const u8 s_press_the__button_to_use_the_s_8012baf8[] = "/press the ? button to use the seed/";
const u8 s_the_musician_gives_rayman_8012bb20[] = "/the musician gives rayman/";
const u8 s_a_super_helicopter_power_8012bb3c[] = "/a super helicopter power/";
const u8 s_press_the__button_to_use_it_8012bb58[] = "/press the ? button to use it/";
const u8 s_press__again_to_go_higher_8012bb78[] = "/press ? again to go higher/";
const u8 s_mr_dark_kidnaps_betilla_the_fai_8012bb98[] = "/mr dark kidnaps betilla the fairy/";
const u8 s_joe_offers_rayman_a_firefly__8012bbbc[] = "/joe offers rayman a firefly /";
const u8 s_to_light_up_the_dark_8012bbdc[] = "/to light up the dark/";
const u8 s_rayman_please_help_me_hurry_8012bbf4[] = "/rayman please help me! hurry!/";

/* 6B6A0 8018FEA0 -O2 -msoft-float */
/*void Deter_Option_Caract(char *param_1,short param_2,uint param_3);
void start_cd_suspence(void);*/

void INIT_VIGNET(void)
{
    s32 base;
    s32 i;

    loop_nb_trames = 0;
    loop_timing = 5;
    new_txt_fee = 0;
    INIT_TEXT_TO_DISPLAY();
    if (You_Win)
    {
        INIT_CREDITS();
        return;
    }

    switch (num_world)
    {
    case 1:
        __builtin_memcpy(text_to_display[0].text, s_tarayzan_gives_rayman_a_magic_s_8012bad0, sizeof(s_tarayzan_gives_rayman_a_magic_s_8012bad0));
        __builtin_memcpy(text_to_display[1].text, s_press_the__button_to_use_the_s_8012baf8, sizeof(s_press_the__button_to_use_the_s_8012baf8));
        Deter_Option_Caract(text_to_display[1].text, options_jeu.Action, 11);
        break;
    case 3:
        __builtin_memcpy(text_to_display[0].text, s_the_musician_gives_rayman_8012bb20, sizeof(s_the_musician_gives_rayman_8012bb20));
        __builtin_memcpy(text_to_display[1].text, s_a_super_helicopter_power_8012bb3c, sizeof(s_a_super_helicopter_power_8012bb3c));
        __builtin_memcpy(text_to_display[2].text, s_press_the__button_to_use_it_8012bb58, sizeof(s_press_the__button_to_use_it_8012bb58));
        __builtin_memcpy(text_to_display[3].text, s_press__again_to_go_higher_8012bb78, sizeof(s_press__again_to_go_higher_8012bb78));
        Deter_Option_Caract(text_to_display[2].text, options_jeu.Jump, 11);
        Deter_Option_Caract(text_to_display[3].text, options_jeu.Jump, 7);
        break;
    case 4:
        start_cd_suspence();
        __builtin_memcpy(text_to_display[0].text, s_mr_dark_kidnaps_betilla_the_fai_8012bb98, sizeof(s_mr_dark_kidnaps_betilla_the_fai_8012bb98));
        break;
    case 5:
        if (num_level == 3)
        {
            __builtin_memcpy(text_to_display[0].text, s_joe_offers_rayman_a_firefly__8012bbbc, sizeof(s_joe_offers_rayman_a_firefly__8012bbbc));
            __builtin_memcpy(text_to_display[1].text, s_to_light_up_the_dark_8012bbdc, sizeof(s_to_light_up_the_dark_8012bbdc));
        }
        if (num_level == 11)
            __builtin_memcpy(text_to_display[0].text, s_rayman_please_help_me_hurry_8012bbf4, sizeof(s_rayman_please_help_me_hurry_8012bbf4));
        break;
    }

    base = 0;
    i = 0;
    while (i < 5)
    {
        if (text_to_display[base].text[0] != '\0')
        {
            text_to_display[base].x_pos = 160;
            text_to_display[base].y_pos = 203;
            text_to_display[base].font_size = 2;
        }
        if (text_to_display[base + 1].text[0] != '\0')
        {
            text_to_display[base + 1].x_pos = 160;
            text_to_display[base + 1].y_pos = 218;
            text_to_display[base + 1].font_size = 2;
        }
        base += 2;
        i++;
    }
}

/* 6BE68 80190668 -O2 -msoft-float */
/*? SaveGameOnDisk(s16);*/

void INIT_CREDITS(void)
{
    s16 i = -1;

    dans_la_map_monde = false;
    SaveGameOnDisk(fichier_selectionne);
    first_credit = 0;
    last_credit = 0;
    nb_credits_lines = 0;
    PROC_EXIT = false;
    display_Vignet = 0;
    menuEtape = 0;
    do
    {
        i++;
        credits[i].y_pos = 260;
    } while (credits[i].cmd != 0xff);
}

/* 6BF14 80190714 -O2 -msoft-float */
void DO_CREDITS(void)
{
    s32 i;
    s16 last_cmd;
    s16 unk_1;

    if (You_Win)
    {
        horloges();
        if (horloge[2] == 0)
        {
            for (i = first_credit; i <= last_credit; i++)
                credits[i].y_pos--;

            nb_credits_lines++;
            last_cmd = credits[last_credit].cmd;
            if (last_cmd == 0)
            {
                switch (credits[last_credit].font)
                {
                case 0:
                    unk_1 = 36;
                    break;
                case 1:
                    unk_1 = 23;
                    break;
                case 2:
                    unk_1 = 15;
                    break;
                }
            }
            else if (last_cmd == 0xFF)
                unk_1 = 160;
            else if (last_cmd > 100)
                unk_1 = last_cmd - 85;
            else
                unk_1 = last_cmd * 15;

            if (nb_credits_lines >= unk_1)
            {
                nb_credits_lines = 0;
                if (last_cmd == 0xFF || (last_credit++, last_credit % 19 == 0))
                    INIT_FADE_OUT();
            }
            if (credits[first_credit].y_pos < -4)
                first_credit++;
            if (D_801F7FF0 == 1 && fade == 0)
                PROC_EXIT = true;
        }
    }
}

/* 6C198 80190998 -O2 -msoft-float */
void INIT_LOADER_ANIM(void)
{
    bigray.offset_bx = 200;
    bigray.offset_by = 240;
    bigray.screen_x_pos = 120;
    bigray.screen_y_pos = -32;
    bigray.main_etat = 1;
    bigray.sub_etat = 0;
    bigray.flags &= ~FLG(OBJ_FLIP_X);
    bigray.cmd = GO_LEFT;
    bigray.flags &= ~FLG(OBJ_FLIP_X);
}

/* 6C210 80190A10 -O2 -msoft-float */
void DO_LOADER_ANIM(void)
{
    u8 anim_speed = bigray.eta[bigray.main_etat][bigray.sub_etat].anim_speed;

    bigray.speed_x = 0;
    if (((anim_speed & 0xf) != 0) && (horloge[anim_speed & 0xf] == 0))
        SET_X_SPEED(&bigray);

    bigray.screen_x_pos += bigray.speed_x;
    if (PROC_EXIT == true)
    {
        bigray.cmd = GO_SUBSTATE;
        set_main_and_sub_etat(&bigray, 0, 2);
        bigray.timer = 2;
        bigray.screen_x_pos = 144 - bigray.offset_bx;
        bigray.flags &= ~FLG(OBJ_FLIP_X);
        PROC_EXIT = false;
    }

    switch (bigray.cmd)
    {
    case GO_LEFT:
        if ((s32) (bigray.screen_x_pos + bigray.offset_bx) < -100)
        {
            bigray.cmd += GO_RIGHT;
            set_main_and_sub_etat(&bigray, 1, 1);
            bigray.screen_x_pos = -bigray.offset_bx - 60;
            bigray.flags |= FLG(OBJ_FLIP_X);
        }
        break;
    case GO_RIGHT:
        if ((s32) (bigray.screen_x_pos + bigray.offset_bx) > 400)
        {
            bigray.cmd += GO_RIGHT;
            set_main_and_sub_etat(&bigray, 1, 2);
            bigray.anim_frame = 0;
            bigray.screen_x_pos = -bigray.offset_bx + 350;
            bigray.flags &= ~FLG(OBJ_FLIP_X);
        }
        break;
    case GO_WAIT:
        if (bigray.main_etat == 0 && bigray.sub_etat == 0)
            bigray.cmd += GO_RIGHT;
        break;
    case GO_UP:
        if (EOA(&bigray))
        {
            bigray.cmd += GO_RIGHT;
            set_main_and_sub_etat(&bigray, 1, 3);
            bigray.screen_x_pos = -60 - bigray.offset_bx;
            bigray.flags |= FLG(OBJ_FLIP_X);
        }
        break;
    case GO_DOWN:
        if ((s32) (bigray.screen_x_pos + bigray.offset_bx) > 400)
        {
            bigray.cmd += GO_RIGHT;
            set_main_and_sub_etat(&bigray, 0, 1);
            bigray.screen_x_pos = 144 - bigray.offset_bx;
            bigray.flags &= ~FLG(OBJ_FLIP_X);
        }
        break;
    case GO_SUBSTATE:
        if (bigray.main_etat == 0 && bigray.sub_etat == 2)
        {
            if (bigray.timer == 0)
                PROC_EXIT = true;
            else
                bigray.timer--;
        }
    }
    DO_ANIM(&bigray);
}

/* 6C6A0 80190EA0 -O2 -msoft-float */
void SPECIAL_INIT(void)
{
    dark_phase = 0;
    if (ray_on_poelle == true)
    {
        PS1_RestoreSauveRayEvts();
        ray_on_poelle = false;
    }
}
