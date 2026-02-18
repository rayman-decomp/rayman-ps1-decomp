#include "menu/menu_7F4B4.h"

const u8 s_use_memory_card_8012c484[] = "/use memory card/";
const u8 s_enter_password_8012c498[] = "/enter password/";
const u8 s_use_password_8012c4ac[] = "/use password/";
const u8 s_x__validate_8012c4bc[] = "/x : validate/";
const u8 s_select__return_8012c4cc[] = "/select : return/";
const u8 s_choose_a_game_8012c4e0[] = "/choose a game/";
const u8 s_up__down__browse_8012c4f0[] = "/up | down : browse/";
const u8 s_x__validate_letter_8012c508[] = "/x : validate letter/";
const u8 s_press_wished_button_8012c520[] = "/press wished button/";
const u8 s_left__right__modify_options_8012c538[] = "/left | right : modify options/";
const u8 s_up__down__choose_options_8012c558[] = "/up | down : choose options/";
const u8 s_x_validate_select_quit_game_8012c578[] = "/x: validate select: quit game/";

#ifdef BSS_DEFS
s16 PS1_SaveMode;
u8 button_released;
s16 compteur;
s16 max_compteur;
s16 repetition;
s16 delai_repetition;
s16 positionx;
s16 positiony;
s16 PS1_Settings[6];
s16 D_801D7A50;
s16 basex;
s16 ecart_barre;
OptionsJeu options_jeu;
OptionsJeu options_jeu_save;
s16 debut_titre;
s16 debut_options;
s16 debut_sortie;
s16 ecarty;
s16 fichier_a_copier;
s16 positionx2;
s16 positiony2;
s16 PS1_display_y1;
s16 PS1_display_y2;
s16 position;
s16 fichier_existant;
s16 fichier_selectionne;
s16 realisation_effectuee;
u8 D_801F7F68[4];
s16 action;
s16 fin_saisie_nom;
u8 save_ray[4][4];
s16 sortie_save;
s16 compteur_clignote;
s16 D_801F5448;
s16 PS1_CharXSpacing;
s16 selection_effectuee;
s16 affiche_bon_ecran;
#endif

/*
should probably be macro/inline:

button_released != 0 ||
(compteur > delai_repetition && (compteur % [some_var] == 0))
*/

/* 7F4B4 801A3CB4 -O2 */
void PS1_TextBoxCardOrPassword(void)
{
    switch (menuEtape)
    {
    case 1:
        __builtin_memcpy(text_to_display[1].text, s_use_memory_card_8012c484, sizeof(s_use_memory_card_8012c484));
        break;
    case 2:
        __builtin_memcpy(text_to_display[1].text, s_enter_password_8012c498, sizeof(s_enter_password_8012c498));
        break;
    }
    text_to_display[1].x_pos = 160;
    text_to_display[1].y_pos = 80;
    text_to_display[1].font_size = 1;
    text_to_display[1].is_fond = false;
    text_to_display[1].field8_0x3d = false;
    text_to_display[1].color = 11;
    INIT_TXT_BOX(&text_to_display[1]);
    switch (menuEtape)
    {
    case 1:
        __builtin_memcpy(text_to_display[2].text, s_use_password_8012c4ac, sizeof(s_use_password_8012c4ac));
        break;
    case 2:
        __builtin_memcpy(text_to_display[2].text, s_start_801cf118, sizeof(s_start_801cf118));
        break;
    }
    text_to_display[2].x_pos = 160;
    text_to_display[2].y_pos = 140;
    text_to_display[2].font_size = 1;
    text_to_display[2].is_fond = false;
    text_to_display[2].field8_0x3d = false;
    text_to_display[2].color = 11;
    INIT_TXT_BOX(&text_to_display[2]);
    positiony = 1;
    button_released = 1;
    compteur = 0;
    max_compteur = 100;
    delai_repetition = 12;
    repetition = 6;
    PS1_SaveMode = 0;
    MENU_RETURN = false;
    PS1_MENU_RETURN2 = false;
}

/* 7F754 801A3F54 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/menu/menu_7F4B4", PS1_InputCardOrPassword);
#else
/*
goto?

!valid_pressed && !select_pressed
PS1_MENU_RETURN2 == 0 ...
if (!valid_pressed) goto block_28;
if (select_pressed) no

!valid_pressed && select_pressed
if (!valid_pressed) goto block_28;
if (select_pressed) yes

valid_pressed && !select_pressed
if (positiony == ...)
if (select_pressed) no

valid_pressed && select_pressed
if (positiony == ...)
if (select_pressed) yes
*/
void PS1_InputCardOrPassword(void)
{
    s16 valid_pressed = but0pressed__CROSS();
    s16 select_pressed = but2pressed__SELECT();

    if (!valid_pressed)
    {
        if (!select_pressed)
        {
            if (PS1_MENU_RETURN2 == 0)
            {
                if (upjoy(0) && !leftjoy(0) && !rightjoy(0))
                {
                    if (
                        button_released != 0 ||
                        (compteur > delai_repetition && compteur % repetition == 0)
                    )
                    {
                        if (positiony > 1)
                            positiony--;
                        else
                            positiony = 2;
                        TempsDemo = 0;
                        PlaySnd_old(68);
                    }
                }
                if (downjoy(0) && !leftjoy(0) && !rightjoy(0))
                {
                    if (
                        button_released != 0 ||
                        (compteur > delai_repetition && compteur % repetition == 0)
                    )
                    {
                        if (positiony > 1)
                            positiony = 1;
                        else
                            positiony++;
                        TempsDemo = 0;
                        PlaySnd_old(68);
                    }
                }
            }
        }
        /*
        ???
        this is closest to the assembly
        flipping + else around positiony checks doesn't let me remove this either
        */
        if (!valid_pressed)
            goto block_28;
    }
    if (positiony == 1)
    {
        TempsDemo = 0;
        PS1_SaveMode = 1;
        button_released = 0;
        PS1_MENU_RETURN2 = true;
        PlaySnd_old(69);
    }
    if (positiony == 2)
    {
        TempsDemo = 0;
        PS1_SaveMode = 2;
        button_released = 0;
        PS1_MENU_RETURN2 = true;
        PlaySnd_old(69);
    }
block_28:
    if (select_pressed)
    {
        MENU_RETURN = true;
        PlaySnd_old(77);
    }
    if (menuEtape == 2 && but1pressed__START())
    {
        PS1_MENU_RETURN2 = true;
        PS1_SaveMode = 2;
    }
    if (
        ((downjoy(0) || upjoy(0) || rightjoy(0) || leftjoy(0)) && !PS1_MENU_RETURN2) ||
        valid_pressed || select_pressed
    )
        button_released = 0;
    else
    {
        button_released = 1;
        compteur = 0;
    }
}
#endif

/* 7FAE8 801A42E8 -O2 -msoft-float */
void PS1_DisplayCardOrPassword(void)
{
    if (compteur < max_compteur)
    {
        if (button_released == 0)
            compteur++;
        else
            compteur = 0;
    }
    else if (button_released == 0)
        compteur = delai_repetition + 1;
    else
        compteur = 0;

    if (positiony > 0)
    {
        text_to_display[positiony].color = 144;
        display_box_text(&text_to_display[positiony]);
    }
    let_shadow = true;

    switch (positiony)
    {
    case 1:
        text_to_display[2].color = 10;
        display_box_text(&text_to_display[2]);
        break;
    case 2:
        text_to_display[1].color = 10;
        display_box_text(&text_to_display[1]);
        break;
    }
    display_text(s_x__validate_8012c4bc, 160, 208, 2, 10);
    display_text(s_select__return_8012c4cc, 160, 223, 2, 10);
}

/* 7FC58 801A4458 -O2 */
s16 selection_save_option_prg(void)
{
    u8 done;

    if (fade == 0)
        PS1_InputCardOrPassword();

    CLRSCR();
    volet();
    DO_FADE();
    PS1_DisplayCardOrPassword();
    readinput();
    done = false;
    if ((PS1_SaveMode != 0 || MENU_RETURN == true) && button_released != 0)
        done = true;

    return done;
}

/* 7FCEC 801A44EC -O2 */
void DO_SAVE_CHOICE(void)
{
    LOAD_SAVE_SCREEN();
    PS1_TextBoxCardOrPassword();
    start_cd_rap();
    INIT_FADE_IN();
    SYNCHRO_LOOP(selection_save_option_prg);
    DO_FADE_OUT();
}

/* 7FD3C 801A453C -O2 -msoft-float */
s16 saisie_nom_prg(void)
{
    u8 done; /* fine as u8 or s16? */

    readinput();
    SAISIE_NOM();
    readinput();
    AFFICHE_ECRAN_SAVE();
    if (action == 3)
        sortie_save = true;
    done = false;
    if (fin_saisie_nom || MENU_RETURN)
    {
        done = true;
        if (MENU_RETURN)
        {
            if (action == 1)
                strcpy(save_ray[fichier_selectionne], &D_801F7F68);
            else
                save_ray[fichier_selectionne][0] = s__801cf120[0];
        }
    }
    return done;
}

/* 7FE30 801A4630 -O2 -msoft-float */
s16 FUN_801a4630(void)
{
    s32 done;

    readinput();
    DO_COMMANDE_SAVE();
    AFFICHE_ECRAN_SAVE();
    SELECTION_SAVE_OPTION();
    REALISATION_ACTION();
    if (
        (action == 1 && fichier_selectionne != 0) ||
        (action == 3 && !fichier_existant && fichier_selectionne != 0)
    )
    {
        if (!fin_saisie_nom)
            SYNCHRO_LOOP(saisie_nom_prg);
        if (!MENU_RETURN)
            SaveGameOnDisk(fichier_selectionne);
    }
    while (but0pressed__CROSS())
        readinput();
    if (realisation_effectuee)
        INIT_SAVE_CONTINUE();
    action = 0;
    done = false;
    if (fin_du_jeu || sortie_save || MENU_RETURN)
        done = true;
    return done;
}

/* 7FF90 801A4790 -O2 -msoft-float */
void FUN_801a4790(void)
{
    let_shadow = true;
    LOAD_SAVE_SCREEN();
    PS1_CheckCardChanged();
    start_cd_rap();
    INIT_FADE_IN();
    INIT_SAVE_CHOICE();
    INIT_SAVE_CONTINUE();
    TempsDemo = 0;
    SYNCHRO_LOOP(FUN_801a4630);
    DO_FADE_OUT();
}

/* 80004 801A4804 -O2 -msoft-float */
void AFFICHE_ECRAN_SAVE(void)
{
    s16 cur_save;
    s16 cur_char;
    u8 save_ray_cpy[4];
    u8 prev_char;
    s32 c_max = 30;

    INIT_AFFICHE_ECRAN_SAVE();
    if (compteur < max_compteur)
    {
        if (button_released == 0)
            compteur++;
        else
            compteur = 0;
    }
    else if (button_released == 0)
        compteur = delai_repetition + 1;
    else
        compteur = 0;

    if (compteur_clignote < c_max)
        compteur_clignote++;
    else
        compteur_clignote = 0;
    DO_FADE();
    CLRSCR();
    volet();
    display_text(s_choose_a_game_8012c4e0, 160, debut_titre, 1, 11);
    display_text(s_copy_801cf124, 30, debut_sortie, 1, 8);
    display_text(s_erase_801cf12c, 125, debut_sortie, 1, 8);
    display_text(s_start_801cf134, 223, debut_sortie, 1, 8);

    for (cur_save = 0; cur_save < NBRE_SAVE; cur_save++)
    {
        if (strcmp(save_ray[cur_save + 1], s__801cf120) != 0)
        {

            for (cur_char = 1; (u32) cur_char <= strlen(save_ray[cur_save + 1]); cur_char++)
            {
                if (
                    positionx != cur_char || positiony != (cur_save + 1) ||
                    compteur_clignote <= c_max / 2 ||
                    D_801F5448 == 0
                )
                {
                    strcpy(save_ray_cpy, save_ray[cur_save + 1]);
                    save_ray_cpy[cur_char] = 0;
                    prev_char = save_ray_cpy[cur_char - 1];
                    if (prev_char == '~')
                    {
                        display_text(
                            s__801cf13c,
                            basex + (cur_char - 1) * PS1_CharXSpacing - 10,
                            debut_options + cur_save * (ecarty + 23),
                            1, 3
                        );
                    }
                    else if (prev_char == ' ')
                    {
                        display_text(
                            s_801cf141,
                            basex + (cur_char - 1) * PS1_CharXSpacing,
                            debut_options + cur_save * (ecarty + 23),
                            1, 3
                        );
                    }
                    else
                    {
                        display_text(
                            save_ray_cpy + (cur_char - 1),
                            basex + (cur_char - 1) * PS1_CharXSpacing,
                            debut_options + cur_save * (ecarty + 23),
                            1,
                            colour
                        );
                    }
                }
            }
            DISPLAY_SAVE_SPRITES((s16) (basex + (PS1_CharXSpacing + 11) * 3 - 30), cur_save);
        }
        else
        {
            let_shadow = true;
            display_text(s_empty_801cf144, basex, debut_options + cur_save * (ecarty + 0x17), 1, 3);
        }
    }
    DISPLAY_SAVE_POING();
    if (
        (action == 1 && fichier_selectionne != 0) ||
        (action == 3 && fichier_selectionne != 0)
    )
    {
        display_text(s_up__down__browse_8012c4f0, 160, 193, 2, 10);
        display_text(s_x__validate_letter_8012c508, 160, 208, 2, 10);
    }
    else
    {
        display_text(s_x__validate_8012c4bc, 160, 208, 2, 10);
    }
    display_text(s_select__return_8012c4cc, 160, 223, 2, 10);
}

/* 80538 801A4D38 -O2 -msoft-float*/
s16 options_choice_prg(void)
{
    s32 done;

    readinput();
    AFFICHE_ECRAN_OPTIONS();
    DO_COMMANDE_OPTIONS();
    PS1_SetSoundVolume(PS1_Settings[4]);
    PS1_SetStereoEnabled(PS1_Settings[5]);
    PS1_SetMusicVolume(PS1_Settings[3]);
    if ((but0pressed__CROSS() && position == 7) || but1pressed__START())
    {
        D_801D7A50 = true;
        PlaySnd_old(69);
    }
    if (MENU_RETURN)
    {
        while ((s16) but0pressed(0) || (s16) but1pressed(0) || (s16) but2pressed(0) || (s16) but3pressed(0))
            readinput();
    }
    done = false;
    if (fin_du_jeu || D_801D7A50 || MENU_RETURN)
        done = true;
    return done;
}

/* 80690 801A4E90 -O2 -msoft-float */
void PS1_DoGameOptions(void)
{
    FUN_801a6808();
    FUN_8019eb30();
    INIT_FADE_IN();
    FUN_801a76e4();
    SYNCHRO_LOOP(options_choice_prg);
    FUN_801a6984();
    DO_FADE_OUT();
}

/* TODO: display_text x and y calculations as macro */
/* 806E8 801A4EE8 -O2 -msoft-float */
void AFFICHE_ECRAN_OPTIONS(void)
{
    s16 i;

    DO_FADE();
    CLRSCR();
    volet();
    DISPLAY_OPTIONS_POING();
    if (compteur < max_compteur)
    {
        if (button_released == 0)
            compteur++;
        else
            compteur = 0;
    }
    else
    {
        if (button_released == 0)
            compteur = delai_repetition + 1;
        else
            compteur = 0;
    }

    let_shadow = false;
    if (PS1_Settings[5] == 0 && position == 5)
        display_text(PS1_SettingStrings[6], basex, debut_sortie + 5 * (PS1_display_y2 + 15), 2, 144);
    else if (position == 7)
        display_text(s_start_801cf134, 135, PS1_display_y1, 2, 144);
    else
        display_text(PS1_SettingStrings[position], basex, debut_sortie + position * (PS1_display_y2 + 15), 2, 144);

    display_text(s_options_801cf14c, 118, debut_titre, 1, 11);
    display_text(s_start_801cf134, 135, PS1_display_y1, 2, 8);
    display_text(PS1_SettingStrings[0], basex, debut_sortie + 0 * (PS1_display_y2 + 15), 2, 7);
    display_text(PS1_SettingStrings[1], basex, debut_sortie + 1 * (PS1_display_y2 + 15), 2, 8);
    display_text(PS1_SettingStrings[2], basex, debut_sortie + 2 * (PS1_display_y2 + 15), 2, 9);
    display_text(PS1_SettingStrings[3], basex, debut_sortie + 3 * (PS1_display_y2 + 15), 2, 10);
    display_text(PS1_SettingStrings[4], basex, debut_sortie + 4 * (PS1_display_y2 + 15), 2, 11);
    if (PS1_Settings[5] == 1)
        display_text(PS1_SettingStrings[5], basex, debut_sortie + 5 * (PS1_display_y2 + 15), 2, 12);
    else
        display_text(PS1_SettingStrings[6], basex, debut_sortie + 5 * (PS1_display_y2 + 15), 2, 12);
    DISPLAY_SYMBOLE(PS1_Settings[0], 150, debut_sortie + 0 * (PS1_display_y2 + 15), 2, 0);
    DISPLAY_SYMBOLE(PS1_Settings[1], 150, debut_sortie + 1 * (PS1_display_y2 + 15), 2, 0);
    DISPLAY_SYMBOLE(PS1_Settings[2], 150, debut_sortie + 2 * (PS1_display_y2 + 15), 2, 0);

    for (i = 0; i < PS1_Settings[3]; i++)
    {
        /* TODO: checks can't be reordered (smaller, then larger)? */
        if (i < PS1_Music_Max * 1 / 3)
            display_text(s__801cf154, basex + (ecart_barre * i) + 100, debut_sortie + 3 * (PS1_display_y2 + 15), 2, 6);
        if ((i < PS1_Music_Max * 2 / 3) && (i >= PS1_Music_Max * 1 / 3))
            display_text(s__801cf154, basex + (ecart_barre * i) + 100, debut_sortie + 3 * (PS1_display_y2 + 15), 2, 4);
        if ((i < PS1_Music_Max * 3 / 3) && (i >= PS1_Music_Max * 2 / 3))
            display_text(s__801cf154, basex + (ecart_barre * i) + 100, debut_sortie + 3 * (PS1_display_y2 + 15), 2, 1);
    }

    for (i = 0; i < PS1_Settings[4]; i++)
    {
        if ((i < PS1_Soundfx_Max * 1 / 3))
            display_text(s__801cf154, basex + (ecart_barre * i) + 100, debut_sortie + 4 * (PS1_display_y2 + 15), 2, 6);
        if ((i < PS1_Soundfx_Max * 2 / 3) && (i >= PS1_Soundfx_Max * 1 / 3))
            display_text(s__801cf154, basex + (ecart_barre * i) + 100, debut_sortie + 4 * (PS1_display_y2 + 15), 2, 4);
        if ((i < PS1_Soundfx_Max * 3 / 3) && (i >= PS1_Soundfx_Max * 2 / 3))
            display_text(s__801cf154, basex + (ecart_barre * i) + 100, debut_sortie + 4 * (PS1_display_y2 + 15), 2, 1);
    }

    if (position < 3)
        display_text(s_press_wished_button_8012c520, (SCREEN_WIDTH / 2), 195, 2, 10);
    else if (position < 7)
        display_text(s_left__right__modify_options_8012c538, (SCREEN_WIDTH / 2), 195, 2, 10);
    display_text(s_up__down__choose_options_8012c558, (SCREEN_WIDTH / 2), 209, 2, 10);
    display_text(s_x_validate_select_quit_game_8012c578, (SCREEN_WIDTH / 2), 223, 2, 10);
}

/* 81074 801A5874 -O2 -msoft-float */
void INIT_SAVE_CHOICE(void)
{
    s16 i;
    s32 unk_1;

    D_801F5498 = 3;
    positiony = 1;
    positionx2 = 3;
    button_released = 1;
    compteur = 0;
    max_compteur = 100;
    nouvelle_partie = false;
    delai_repetition = 12;
    repetition = 6;
    MENU_RETURN = false;
    basex = 40;
    sortie_save = false;
    positiony2 = NBRE_SAVE + 1;
    if (NBRE_SAVE && (unk_1 = NBRE_SAVE != false)) /* but, but why though??? */
    {
        i = 0;
        do
        {
            LoadInfoGame(i + 1);
            i++;
        } while (i < NBRE_SAVE);
    }
}

/* 8116C 801A596C -O2 -msoft-float */
void INIT_SAVE_CONTINUE(void)
{
    selection_effectuee = 0;
    realisation_effectuee = false;
    fichier_selectionne = 0;
    fichier_a_copier = 0;
    action = 0;
    fin_saisie_nom = false;
    affiche_bon_ecran = false;
    D_801F5448 = 0;
    compteur_clignote = 0;
    positionx = 1;
}

/* 811C8 801A59C8 -O2 -msoft-float */
void DO_COMMANDE_SAVE(void) /* TODO: macro(s)? */
{
    if (
        rightjoy(0) && !upjoy(0) && !downjoy(0) &&
        fichier_a_copier == 0 &&
        (
            button_released != 0 ||
            (compteur > delai_repetition && compteur % repetition == 0)
        )
    )
    {
        if (positionx2 == D_801F5498)
            positionx2 = 1;
        else
            positionx2++;

        TempsDemo = 0;
        PlaySnd_old(68);
    }

    if (
        leftjoy(0) && !upjoy(0) && !downjoy(0) &&
        fichier_a_copier == 0 &&
        (
            button_released != 0 ||
            (compteur > delai_repetition && compteur % repetition == 0)
        )
    )
    {
        if (positionx2 == 1)
            positionx2 = D_801F5498;
        else
            positionx2--;

        TempsDemo = 0;
        PlaySnd_old(68);
    }

    if (
        upjoy(0) && !leftjoy(0) && !rightjoy(0) &&
        (
            button_released != 0 ||
            (compteur > delai_repetition && compteur % repetition == 0)
        )
    )
    {
        if (positiony < 2)
            positiony = NBRE_SAVE;
        else
            positiony--;

        TempsDemo = 0;
        PlaySnd_old(68);
    }

    if (
        downjoy(0) && !leftjoy(0) && !rightjoy(0) &&
        (
            button_released != 0 ||
            (compteur > delai_repetition && compteur % repetition == 0)
        )
    )
    {
        if (positiony == NBRE_SAVE)
            positiony = 1;
        else
            positiony++;

        TempsDemo = 0;
        PlaySnd_old(68);
    }

    if (!rightjoy(0) && !leftjoy(0) && !downjoy(0) && !upjoy(0))
    {
        button_released = 1;
        compteur = 0;
    }
    else
        button_released = 0;

    if (but2pressed__SELECT() && button_released != 0)
        MENU_RETURN = true;
}

/* 81634 801A5E34 -O2 -msoft-float */
void SELECTION_SAVE_OPTION(void)
{
    if (positionx2 == 1 && but0pressed__CROSS())
    {
        action = 1;
        while (but0pressed__CROSS())
            readinput();
        PlaySnd_old(69);
    }
    if (positionx2 == 2 && but0pressed__CROSS())
    {
        action = 2;
        while (but0pressed__CROSS())
            readinput();
        PlaySnd_old(69);
    }
    if ((positionx2 == 3 && but0pressed__CROSS()) || but1pressed__START())
    {
        action = 3;
        while ((s16) but0pressed(0) || (s16) but1pressed(0) || (s16) but2pressed(0) || (s16) but3pressed(0))
            readinput();
        PlaySnd_old(69);
    }
}

/* 81794 801A5F94 -O2 -msoft-float */
void INIT_AFFICHE_ECRAN_SAVE(void)
{
    u8 fix_stack[8];
    s16 y = (108 - NBRE_SAVE * 23) / (NBRE_SAVE + 1);

    basex = 50;
    debut_titre = 29;
    PS1_CharXSpacing = 21;
    debut_sortie = 167;
    ecarty = y;
    debut_options = y + 59;
}

/* 81834 801A6034 -O2 -msoft-float */
void SAISIE_NOM(void)
{
    u8 *cur_save_1;
    u8 *cur_char_1;
    u8 *cur_save_2;
    u8 *cur_char_2;
    u8 new_char;

    if (!fichier_existant && action != 1)
    {
        __builtin_memcpy(save_ray[positiony], s_aaa_801cf158, sizeof(s_aaa_801cf158));
        fichier_existant = true;
    }
    if (affiche_bon_ecran)
        fin_saisie_nom = true;
    if (but0pressed__CROSS())
    {
        cur_save_1 = save_ray[positiony];
        cur_char_1 = &cur_save_1[positionx];
        if (*(cur_char_1 - 1) == '~') /* ??? */
        {
            if (positionx != 1)
            {
                *(cur_char_1 - 1) = 'a';
                positionx--;
                PlaySnd_old(68);
            }
        }
        else if (positionx < 3)
        {
            positionx++;
            PlaySnd_old(68);
        }
        else
        {
            PlaySnd_old(69);
            affiche_bon_ecran = true;
        }
        while (but0pressed__CROSS())
            readinput();
    }
    if (upjoy(0) && !rightjoy(0) && !leftjoy(0))
    {
        if (
            button_released != 0 ||
            (compteur > delai_repetition && compteur % 3 == 0)
        )
        {
            cur_save_2 = save_ray[positiony];
            cur_char_2 = &cur_save_2[positionx];
            if (*(cur_char_2 - 1) == 'z')
                new_char = ' ';
            else if (*(cur_char_2 - 1) == ' ')
                new_char = '~';
            else if (*(cur_char_2 - 1) == '~')
                new_char = 'a';
            else
                new_char = *(cur_char_2 - 1) + 1;
            *(cur_char_2 - 1) = new_char;
            PlaySnd_old(68);
        }
    }
    if (downjoy(0) && !rightjoy(0) && !leftjoy(0))
    {
        if (
            button_released != 0 ||
            (compteur > delai_repetition && compteur % 3 == 0)
        )
        {
            cur_save_2 = save_ray[positiony];
            cur_char_2 = &cur_save_2[positionx];
            if (*(cur_char_2 - 1) == 'a')
                new_char = '~';
            else if (*(cur_char_2 - 1) == '~')
                new_char = ' ';
            else if (*(cur_char_2 - 1) == ' ')
                new_char = 'z';
            else
                new_char = *(cur_char_2 - 1) - 1;
            *(cur_char_2 - 1) = new_char;
            PlaySnd_old(68);
        }
    }
    if (
        !upjoy(0) && !downjoy(0) && !rightjoy(0) && !leftjoy(0) &&
        !affiche_bon_ecran && !fin_saisie_nom
    )
    {
        button_released = 1;
        D_801F5448 = 1;
        compteur = 0;
    }
    else
    {
        button_released = 0;
        D_801F5448 = 0;
    }
    if (but2pressed__SELECT() && button_released != 0)
        MENU_RETURN = true;
}

/* 81C84 801A6484 -O2 -msoft-float */
void REALISATION_ACTION(void)
{
    u8 should_load = false;

    switch (action)
    {
    case 1:
        if (fichier_a_copier != 0)
        {
            if ((strcmp(save_ray[fichier_a_copier], s__801cf120) != 0) || (u8) PS1_PromptSaveWldMap())
                should_load = true;
            if (should_load)
            {
                fichier_selectionne = positiony;
                strcpy(D_801F7F68, save_ray[positiony]);
                strcpy(save_ray[fichier_selectionne], save_ray[fichier_a_copier]);
                /* ??? */
                loadInfoRay[fichier_selectionne - 1].num_lives = loadInfoRay[fichier_a_copier - 1].num_lives;
                loadInfoRay[fichier_selectionne - 1].num_wiz = loadInfoRay[fichier_a_copier - 1].num_wiz;
                loadInfoRay[fichier_selectionne - 1].num_cages = loadInfoRay[fichier_a_copier - 1].num_cages;
                loadInfoRay[fichier_selectionne - 1].num_continues = loadInfoRay[fichier_a_copier - 1].num_continues;
                LoadGameOnDisk(fichier_a_copier);
            }
            realisation_effectuee = true;
        }
        else if (strcmp(save_ray[positiony], s__801cf120) != 0)
            fichier_a_copier = positiony;
        break;
    case 2:
        if (strcmp(save_ray[positiony], s__801cf120) != 0)
        {
            PS1_PromptCardErase();
            if (PS1_positiony_mc == 1)
            {
                fichier_selectionne = positiony;
                FUN_8016bbe4();
                *save_ray[fichier_selectionne] = *s__801cf120;
            }
            realisation_effectuee = true;
        }
        break;
    case 3:
        fichier_selectionne = positiony;
        if (strcmp(s__801cf120, save_ray[positiony]) == 0)
        {
            fichier_existant = false;
            nouvelle_partie = true;
            INIT_NEW_GAME();
        }
        else
        {
            fichier_existant = true;
            LoadGameOnDisk(fichier_selectionne);
            sortie_save = true;
            new_world = true;
        }
        break;
    }
}