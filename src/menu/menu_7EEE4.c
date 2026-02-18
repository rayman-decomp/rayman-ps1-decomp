#include "menu/menu_7EEE4.h"

#ifdef BSS_DEFS
u8 menuEtape;
u8 MENU_RETURN;
u8 PS1_MENU_RETURN2;
u8 PROC_EXIT;
u8 D_801E5920;
u8 PS1_CardShouldCheckFirstBoot;
#endif

/* 7EEE4 801A36E4 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/menu/menu_7EEE4", DO_MENUS);
#else
void DO_MENUS(void)
{
    s16 done;

    PS1_SaveMode = 0;
    fin_du_jeu = false;
    dans_la_map_monde = false;
    PS1_MENU_RETURN2 = false;
    MENU_RETURN = false;
    PROC_EXIT = false;
    PS1_VideoPlayState = VIDEOST_NOT_PLAYING;
    done = false;
    while (ModeDemo == 0 && !fin_du_jeu && !done)
    {
        PS1_SetSoundVolume(options_jeu.Soundfx);
        PS1_SetStereoEnabled(options_jeu.StereoEnabled);
        PS1_SetMusicVolume(options_jeu.Music);
do /* TODO: ??? */
{
        switch (menuEtape)
        {
        case 0:
            PS1_PlayDemo();
            if (PS1_VideoPlayState != VIDEOST_NOT_PLAYING)
                PS1_VideoPlayState = VIDEOST_NOT_PLAYING;

            else if (ModeDemo == 0)
            {
                RunTimeDemo = 1800;
                if (PS1_ShouldClearPassword == 2)
                    PS1_ShouldClearPassword = 0;

        case 6: /* TODO: ??? */
                if (PS1_CardShouldCheckFirstBoot == true)
                {
                    FUN_801a1110();
                    PS1_CardShouldCheckFirstBoot = false;
                    D_801E5920 = NBRE_SAVE;
                    if (NBRE_SAVE != 0)
                        menuEtape = 1;
                    else
                        menuEtape = 2;
                }
                else
                {
                    PS1_SetNoCard();
                    if (PS1_NoCard)
                    {
                        NBRE_SAVE = 0;
                        D_801E5920 = 0;
                        PS1_NoCard = false;
                        menuEtape = 2;
                    }
                    else
                        menuEtape = 1;
                }
            }
            break;
        case 1:
            DO_SAVE_CHOICE();
            if (PS1_SaveMode == 1)
                menuEtape = 3;
            else
                menuEtape = 2;
            break;
        case 2:
            DO_SAVE_CHOICE();
            if (PS1_SaveMode == 1)
                menuEtape = 5;
            else
            {
                FUN_801a6a04(false);
                menuEtape = 4;
            }
            break;
        case 3:
            FUN_801a0c68();
            if (PS1_NoCard || D_801E5920 == 0)
            {
                FUN_801a1110();
                D_801E5920 = NBRE_SAVE;
                if (NBRE_SAVE != 0)
                {
                    FUN_801a4790();
                    menuEtape = 4;
                }
                else
                    menuEtape = 2;
            }
            else
            {
                NBRE_SAVE = D_801E5920;
                FUN_801a4790();
                menuEtape = 4;
            }
            break;
        case 5:
            FUN_801a6a04(true);
            if (PS1_SaveMode == 1)
                menuEtape = 4;
            else
            {
                menuEtape = 6;
                MENU_RETURN = false;
            }
            break;
        case 4:
            PS1_DoGameOptions();
            if (MENU_RETURN)
            {
                if (PS1_PromptQuit())
                    MENU_RETURN = true;
                else
                    MENU_RETURN = false;
            }
            else
            {
                done = true;
                fin_du_jeu = false;
                new_world = true;
            }
            break;
        }
} while (0);

        stop_cd();
        if (MENU_RETURN)
        {
            menuEtape = 0;
            MENU_RETURN = false;
        }
    }
}
#endif