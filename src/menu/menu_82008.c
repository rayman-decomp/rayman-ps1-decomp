#include "menu/menu_82008.h"

#ifdef BSS_DEFS
s16 D_801D7AA0;
s16 D_801F5498;
s16 PS1_Music_Max;
s16 PS1_Soundfx_Max;
s16 delai_barre;
s16 delai_stereo;
#endif

/* 82008 801A6808 -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/menu/menu_82008", PS1_InitGameOptionsMenu);
#else
/*
score of ???
INIT_OPTIONS_CHOICE on android?

generates division checks if:
-function arg is involved
-global is involved
-uninitialized local var is involved

still to see more

PS1_display_y2 is vert spacing on options screen
*/
void PS1_InitGameOptionsMenu(void)
{
    s32 test_1;
    s32 temp_lo;
    /*s32 test_4[2];*/
    volatile long long test_4;
    s32 test_3 = 0x64;

    if (test_4)
    {
        test_1 = 0x5a;
    }
    position = 7;
    temp_lo = (test_3 - test_1) / position;
    PS1_Music_Max = 0x0014;
    PS1_Soundfx_Max = 0x0014;
    D_801F5498 = 6;
    ecart_barre = 4;
    button_released = 1;
    compteur = 0;
    max_compteur = 0x0064;
    delai_repetition = 0x000C;
    repetition = 6;
    delai_stereo = 8;
    delai_barre = 3;
    D_801D7AA0 = 0x0037;
    basex = 0x0032;
    debut_titre = 0x001D;
    test_3 = test_3 + 0x3b;
    PS1_display_y1 = test_3;
    PS1_display_y2 = temp_lo;
    PROC_EXIT = 0;
    D_801D7A50 = 0;
    PS1_Settings[0] = options_jeu.Jump;
    PS1_Settings[1] = options_jeu.Fist;
    PS1_Settings[2] = options_jeu.Action;
    PS1_Settings[3] = options_jeu.Music;
    PS1_Settings[4] = options_jeu.Soundfx;
    PS1_Settings[5] = options_jeu.StereoEnabled;
    debut_sortie = temp_lo + 0x33;
}
#endif

/* 82184 801A6984 -O2 -msoft-float */
void PS1_LoadOptions(void)
{
    options_jeu.Jump = PS1_Settings[0];
    options_jeu.Fist = PS1_Settings[1];
    options_jeu.Action = PS1_Settings[2];
    options_jeu.Music = PS1_Settings[3];
    options_jeu.Soundfx = PS1_Settings[4];
    options_jeu.StereoEnabled = PS1_Settings[5];
    POINTEUR_BOUTONS_OPTIONS_BIS();
}

/* 82204 801A6A04 -O2 -msoft-float */
void PS1_NewGame(u8 param_1)
{
    fichier_existant = false;
    fichier_selectionne = 0;
    NBRE_SAVE = 0;
    TempsDemo = 0;
    nouvelle_partie = true;
    INIT_NEW_GAME();
    if (param_1)
        PS1_MenuPassword();
}

/* 82268 801A6A68 -O2 -msoft-float */
/* still pretty gross. repeated sections, position == x check then x used as constant */
void DO_COMMANDE_OPTIONS(void)
{
    s16 new_pos;
    s16 i;

    if (but2pressed__SELECT())
    {
        while (but2pressed__SELECT())
            readinput();
        MENU_RETURN = true;
    }

    if (upjoy(0) && !rightjoy(0) && !leftjoy(0))
    {
        if (button_released != 0 || (compteur > delai_repetition && compteur % repetition == 0))
        {
            PlaySnd_old(68);
            if (position == 0)
                new_pos = 7;
            else
            {
                if (position == 7)
                    new_pos = position - 2;
                else
                    new_pos = position - 1;
            }
            position = new_pos;
        }
    }

    if (downjoy(0) && !rightjoy(0) && !leftjoy(0))
    {
        if (button_released != 0 || (compteur > delai_repetition && compteur % repetition == 0))
        {
            PlaySnd_old(68);
            if (position == 7)
                position = 0;
            else
            {
                if (position == 5)
                    new_pos = position + 2;
                else
                    new_pos = position + 1;
                position = new_pos;
            }
        }
    }
    if (rightjoy(0) && !downjoy(0) && !upjoy(0))
    {
        if (position == 5)
        {
            if (button_released != 0 || (compteur > delai_repetition && compteur % delai_stereo == 0))
            {
                PlaySnd_old(68);
                if (PS1_Settings[5] == 1)
                    PS1_Settings[5] = 0;
                else
                    PS1_Settings[5] = 1;
            }
        }
        if (position == 3 && (PS1_Settings[3] < PS1_Music_Max))
        {
            if (button_released != 0 || (compteur > delai_repetition && compteur % delai_barre == 0))
            {
                PlaySnd_old(68);
                PS1_Settings[3]++;
            }
        }
        if (position == 4 && (PS1_Settings[4] < PS1_Soundfx_Max))
        {
            if (button_released != 0 || (compteur > delai_repetition && compteur % delai_barre == 0))
            {
                PlaySnd_old(68);
                PS1_Settings[4]++;
            }
        }
    }
    if (leftjoy(0) && !downjoy(0) && !upjoy(0))
    {
        if (position == 5)
        {
            if (button_released != 0 || (compteur > delai_repetition && compteur % delai_stereo == 0))
            {
                PlaySnd_old(68);
                if (PS1_Settings[5] == 1)
                    PS1_Settings[5] = 0;
                else
                    PS1_Settings[5] = 1;
            }
        }
        if (position == 3 && PS1_Settings[3] > 0)
        {
            if (button_released != 0 || (compteur > delai_repetition && compteur % delai_barre == 0))
            {
                PlaySnd_old(68);
                PS1_Settings[3]--;
            }
        }
        if (position == 4 && PS1_Settings[4] >= 1)
        {
            if (button_released != 0 || (compteur > delai_repetition && compteur % delai_barre == 0))
            {
                PlaySnd_old(68);
                PS1_Settings[4]--;
            }
        }
    }
    if (position == 5 && but0pressed__CROSS())
    {
        PlaySnd_old(68);
        if (PS1_Settings[5] == 1)
            PS1_Settings[5] = 0;
        else
            PS1_Settings[5] = 1;
        while (but0pressed__CROSS())
            readinput();
    }
    if ((u16) position < 3)
    {
        if ((s16) but0pressed(0) && PS1_Settings[position] != 0 && button_released != 0)
        {
            PlaySnd_old(68);
            i = 0;
            if (PS1_Settings[0] != 0)
            {
                while (i < 3)
                {
                    i++;
                    if (PS1_Settings[i] == 0)
                        break;
                }
            }
            if (i < 3)
                PS1_Settings[i] = PS1_Settings[position];
            PS1_Settings[position] = 0;
        }
        if ((u16) position < 3)
        {
            if ((s16) but1pressed(0) && PS1_Settings[position] != 1 && button_released != 0)
            {
                PlaySnd_old(68);
                i = 0;
                if (PS1_Settings[0] != 1)
                {
                    while (i < 3)
                    {
                        i++;
                        if (PS1_Settings[i] == 1)
                            break;
                    }
                }
                if (i < 3)
                    PS1_Settings[i] = PS1_Settings[position];
                PS1_Settings[position] = 1;
            }
            if ((u16) position < 3)
            {
                if ((s16) but2pressed(0) && PS1_Settings[position] != 2 && button_released != 0)
                {
                    PlaySnd_old(68);
                    i = 0;
                    if (PS1_Settings[0] != 2)
                    {
                        while (i < 3)
                        {
                            i++;
                            if (PS1_Settings[i] == 2)
                                break;
                        }
                    }
                    if (i < 3)
                        PS1_Settings[i] = PS1_Settings[position];
                    PS1_Settings[position] = 2;
                }
                if (
                    (u16) position < 3 &&
                    (s16) but3pressed(0) && PS1_Settings[position] != 3 && button_released != 0
                )
                {
                    PlaySnd_old(68);
                    i = 0;
                    if (PS1_Settings[0] != 3)
                    {
                        while (i < 3)
                        {
                            i++;
                            if (PS1_Settings[i] == 3)
                                break;
                        }
                    }
                    if (i < 3)
                        PS1_Settings[i] = PS1_Settings[position];
                    PS1_Settings[position] = 3;
                }
            }
        }
    }
    if (
        !upjoy(0) && !downjoy(0) && !rightjoy(0) && !leftjoy(0) &&
        !(s16) but0pressed(0) && !(s16) but1pressed(0) && !(s16) but2pressed(0) && !(s16) but3pressed(0)
    )
    {
        button_released = 1;
        compteur = 0;
    }
    else
        button_released = 0;
}

/* 82EE4 801A76E4 -O2 -msoft-float */
void PS1_DisplayGameOptions(void)
{
    s16 i;
    u8 seven;

    for (i = 0; i < (D_801F5498 + 2); i++)
    {
        strcpy(&text_to_display[i], PS1_SettingStrings[i]);
        seven = 7;
        if (i == seven)
        {
            text_to_display[seven].x_pos = 0x00A0;
            text_to_display[seven].font_size = 2;
            text_to_display[seven].y_pos = PS1_display_y1;
        }
        else
        {
            text_to_display[i].x_pos = basex;
            if (i >= 6)
                text_to_display[i].y_pos = debut_sortie + (PS1_display_y2 + 15) * (i - 1);
            else
                text_to_display[i].y_pos = debut_sortie + (PS1_display_y2 + 15) * i;

            text_to_display[i].font_size = 2;
        }
        text_to_display[i].is_fond = 1;
        text_to_display[i].field8_0x3d = 0;
        INIT_TXT_BOX(&text_to_display[i]);
    }
}