#ifndef MENU_7F4B4_H
#define MENU_7F4B4_H

#include "common.h"
#include "common/text_to_display.h"
#include "psyq_3_0_missing/STRINGS.H"
#include "menu/menu_7EEE4.h"
#include "draw/fade.h"
#include "demo_7F2BC.h"
#include "menu/menu_82008.h"
#include "card.h"

/* but0pressed etc. return int in ghidra */
typedef struct OptionsJeu
{
    s16 (*Fire1ButtonFunc)();
    s16 (*Fire0ButtonFunc)();
    s16 (*Button4Func)();
    s16 (*Button3Func)();
    u16 Jump;
    u16 Fist;
    u16 field6_0x14;
    u16 Action;
    u16 Music;
    u16 Soundfx;
    u16 StereoEnabled;
    s16 field11_0x1e;
    s16 field12_0x20;
    s16 field13_0x22;
    s16 field14_0x24;
} OptionsJeu;

/* .data */
extern u8 *PS1_SettingStrings[8]; /* if creates conflict here, put in menu_82008 */

/* .data */
extern u8 s_exit_801cee14[7];
extern u8 s_mono_801cee1c[5];
extern u8 s_stereo_801cee24[7];
extern u8 s_music_801cee2c[6];
extern u8 s_action_801cee34[7];
extern u8 s_fist_801cee3c[5];
extern u8 s_jump_801cee44[5];
extern u8 s_rayman_801cee4c[7];
extern u8 s_with_801cee54[7];

/* .data */
extern u8 s_start_801cf118[8];
extern u8 s__801cf120[1];
extern u8 s_copy_801cf124[5];
extern u8 s_erase_801cf12c[6];
extern u8 s_start_801cf134[6];
extern u8 s__801cf13c[2];
extern u8 s_801cf141[1];
extern u8 s_empty_801cf144[6];
extern u8 s_options_801cf14c[8];
extern u8 s__801cf154[2];
extern u8 s_aaa_801cf158[4];

/**/
extern s16 PS1_SaveMode;
extern u8 button_released; /* TODO: not a bool? based on RAY_HELICO */
extern s16 compteur;
extern s16 max_compteur;
extern s16 repetition;
extern s16 delai_repetition;
extern s16 positionx;
extern s16 positiony;
extern s16 PS1_Settings[6];
extern s16 D_801D7A50;
extern s16 basex;
extern s16 ecart_barre;
extern OptionsJeu options_jeu;
extern OptionsJeu options_jeu_save; /* from include/demo_9FD4.h, move back? */
extern s16 debut_titre;
extern s16 debut_options;
extern s16 debut_sortie;
extern s16 ecarty;
extern s16 fichier_a_copier;
extern s16 positionx2;
extern s16 positiony2;
extern s16 PS1_display_y1;
extern s16 PS1_display_y2;
extern s16 position;
extern s16 fichier_existant;
extern s16 fichier_selectionne;
extern s16 realisation_effectuee;
extern u8 D_801F7F68[4];
extern s16 action;
extern s16 fin_saisie_nom;
extern u8 save_ray[4][4];
extern s16 sortie_save;
extern s16 compteur_clignote;
extern s16 D_801F5448; /* bool? */
extern s16 PS1_CharXSpacing;
extern s16 selection_effectuee;
extern s16 affiche_bon_ecran;

void PS1_TextBoxCardOrPassword(void);
void PS1_InputCardOrPassword(void);
void PS1_DisplayCardOrPassword(void);
s16 selection_save_option_prg(void);
void DO_SAVE_CHOICE(void);
s16 saisie_nom_prg(void);
s16 PS1_MemoryCardSaveSelectionPrg(void);
void PS1_MemoryCardSaveSelection(void);
void AFFICHE_ECRAN_SAVE(void);
s16 options_choice_prg(void);
void PS1_DoGameOptions(void);
void AFFICHE_ECRAN_OPTIONS(void);
void INIT_SAVE_CHOICE(void);
void INIT_SAVE_CONTINUE(void);
void DO_COMMANDE_SAVE(void);
void SELECTION_SAVE_OPTION(void);
void INIT_AFFICHE_ECRAN_SAVE(void);
void SAISIE_NOM(void);
void REALISATION_ACTION(void);

#endif