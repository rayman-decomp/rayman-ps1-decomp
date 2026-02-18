#include "demo_7F2BC.h"

const u8 s_press_start_or_x_button_8012c468[] = "/press start or x button/";

#ifdef BSS_DEFS
s32 TempsDemo;
#endif

/* 7F2BC 801A3ABC -O1, -O2 */
void PS1_ShowDemoText(void)
{
    display_text(s_start_801cf118, 160, 180, 1, 144);
    display_text(s_press_start_or_x_button_8012c468, 160, 203, 2, 10);
}

/* 7F314 801A3B14 -O1 -O2 */
s16 PS1_DemoLoop(void)
{
    u8 done;

    done = false;
    DISPLAY_FOND3();
    DO_FADE();
    PS1_ShowDemoText();

    readinput();
    if (!fade && (but0pressed__CROSS() || but1pressed__START()))
        PS1_MENU_RETURN2 = true;

    TempsDemo++;
    if (TempsDemo >= RunTimeDemo && !fin_du_jeu && !PS1_MENU_RETURN2)
        InitDemoJeu();

    if (PS1_VideoPlayState != VIDEOST_NOT_PLAYING)
        done = true;
    if (fin_du_jeu || ModeDemo || PS1_MENU_RETURN2 || MENU_RETURN)
        done = true;
    return done;
}

/* 7F450 801A3C50 -O1, -O2 */
void PS1_PlayDemo(void)
{
    PS1_LoadImgSplash();
    start_cd_rap();
    INIT_FADE_IN();
    PS1_MENU_RETURN2 = false;
    MENU_RETURN = false;
    let_shadow = true;
    SYNCHRO_LOOP(PS1_DemoLoop);
    DO_FADE_OUT();
}