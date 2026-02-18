#include "cheats.h"

#ifdef BSS_DEFS
u8 PS1_DebugMode;
#endif

/* 7ABA0 8019F3A0 -O2 -msoft-float */
void handle_pad(void)
{
    if (PS1_Ingame && butstart(0))
    {
        if (in_pause == true)
        {
            in_pause = false;
            stop_freeze_snd();
        }
        else
        {
            in_pause = true;
            start_freeze_snd();
        }
    }
    if (PS1_DebugMode)
    {
        if (butvbl(0))
            PS1_MemoryUsageDisplayMode = (PS1_MemoryUsageDisplayMode + 1) % 3;
        if (PS1_DebugMode)
        {
            if (butmode(0))
            {
                ray.main_etat = 2;
                ray.sub_etat = 2;
                dead_time = 64;
                ray.field20_0x36 = -1;
                ray_mode = -ray_mode;
            }
            if (PS1_DebugMode)
            {
                if (butR2_2(0))
                {
                    D_801CF0D8++;
                    if (D_801CF0D8 == 8)
                        D_801CF0D8 = 0;
                }
                if (PS1_DebugMode && butR1_1(0))
                    D_801CEFC8 = !D_801CEFC8;
            }
        }
    }
    if (cheat_start(0))
        PS1_DebugMode = true;

    if (in_pause)
    {
        if (cheat1_start(0))
        {
            if (ray.hit_points != 0xFF && !fin_du_jeu)
            {
                ray.hit_points = 4;
                status_bar.max_hp = 4;
            }
            in_pause = false;
            stop_freeze_snd();
        }
        if (in_pause)
        {
            if (cheat6_start(0))
            {
                if (ray.hit_points != 0xFF && !fin_du_jeu)
                {
                    status_bar.num_lives = 5;
                    status_bar.max_hp = ray.hit_points;
                }
                in_pause = false;
                stop_freeze_snd();
            }
            if (in_pause)
            {
                if (cheat7_start(0))
                {
                    if (ray.hit_points != 0xFF && !fin_du_jeu)
                    {
                        status_bar.num_lives = 99;
                        ray.hit_points = 4;
                        status_bar.max_hp = 4;
                    }
                    in_pause = false;
                    stop_freeze_snd();
                }
                if (in_pause)
                {
                    if (cheat3_start(0))
                    {
                        in_pause = false;
                        PS1_PictureInPicture = 1 - PS1_PictureInPicture;
                        stop_freeze_snd();
                    }
                    if (in_pause)
                    {
                        if (cheat5_start(0))
                        {
                            in_pause = false;
                            PS1_15fps = 1 - PS1_15fps;
                            stop_freeze_snd();
                        }
                        if (in_pause)
                        {
                            if (cheat4_start(0))
                            {
                                in_pause = false;
                                fin_boss = 1 - fin_boss;
                                stop_freeze_snd();
                            }
                            if (in_pause && cheat2_start(0))
                            {
                                in_pause = false;
                                RayEvts.poing = true;
                                RayEvts.helico = true;
                                RayEvts.run = true;
                                RayEvts.hang = true;
                                RayEvts.handstand_dash = true;
                                RayEvts.grap = true;
                                stop_freeze_snd();
                            }
                        }
                    }
                }
            }
        }
    }
    if (cheat_stop(0))
    {
        PS1_DebugMode = false;
        D_801CF0D8 = 0;
        D_801CEFC8 = 0;
        PS1_MemoryUsageDisplayMode = 0;
    }
}