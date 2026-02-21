#include "victoire.h"

#ifdef BSS_DEFS
u8 You_Win;
u8 display_Vignet;
u8 first_credit;
u8 last_credit;
s16 nb_credits_lines;
#endif

/* 9C90 8012E490 -O2 -msoft-float */
void DISPLAY_TXT_CREDITS(void)
{
    u32 i;

    for (i = first_credit; i <= last_credit; i++)
        display_text(
            credits[i].text,
            credits[i].x_pos, credits[i].y_pos,
            credits[i].font,
            credits[i].color
        );
}

/* 9D4C 8012E54C -O2 -msoft-float */
s16 display_credits_prg(void)
{
    s16 done;
    u8 prev_exit;

    readinput();
    DO_FADE();
    DO_CREDITS();
    DISPLAY_FOND3();
    DISPLAY_TXT_CREDITS();
    prev_exit = PROC_EXIT;
    PROC_EXIT = false;

    if (but0pressed__CROSS() || but2pressed__SELECT())
    {
        PROC_EXIT = true;
        display_Vignet = 5;
    }

    done = false;
    if (PROC_EXIT || prev_exit)
        done = true;
    return done;
}

/* 9DF4 8012E5F4 -O2 -msoft-float */
void DISPLAY_CREDITS(void)
{
    start_cd_replay();
    INIT_CREDITS();
    let_shadow = false;
    while (display_Vignet < 6)
    {
        LOAD_CREDITS_VIGNET();
        if (display_Vignet == 0)
            start_cd_victory();
        INIT_FADE_IN();
        SYNCHRO_LOOP(display_credits_prg);
        PROC_EXIT = false;
        display_Vignet++;
    }
    INIT_FADE_IN();
}

/* 9EB0 8012E6B0 -O2 -msoft-float */
void DISPLAY_PROTOON_BACK(void)
{
    display_Vignet = 0;
    INIT_FADE_IN();
    loop_nb_trames = 0;
    loop_timing = 4;
    new_txt_fee = 0;
    INIT_TEXT_TO_DISPLAY();
    SYNCHRO_LOOP(display_vignet_prg);
    DO_FADE_OUT();
}

/* 9F14 8012E714 -O2 -msoft-float */
void DO_VICTOIRE(void)
{
    star_ray_der = null;
    star_ray_dev = null;
    if (You_Win)
    {
        start_cd_rap();
        if (num_level_choice > 1)
        {
            DO_FADE_OUT();
            PS1_PlayVideo(VIDEO_WIN);
        }
        else
        {
            num_level = 4;
            num_world = 6;
            LOAD_VIGNET_GAME();
        }

        if (num_level_choice == 1)
            DISPLAY_PROTOON_BACK();
        charge_let2();
        DISPLAY_CREDITS();
    }
    PROC_EXIT = false;
}
