#ifndef MENU_CARD_7C028_H
#define MENU_CARD_7C028_H

#include "common.h"
#include "sound.h"
#include "synchro_loop.h"
#include "unknown/5C2BC.h"

/* .data */
extern u8 *PS1_CardStrings[13];

/* .data */
extern u8 s_yes_801cf0f4[6];
extern u8 s_no_801cf0fc[5];
extern u8 D_801CF101;

/**/
extern u8 NBRE_SAVE;
extern u8 PS1_positiony_mc;
extern u8 PS1_CardStringDisplayed;
extern s16 PS1_compteur_mc;
extern u8 PS1_DisplayCardContinueText;
extern u8 PS1_NoCard;
extern u8 D_801E5238;

void PS1_PromptCardInput(void);
s16 PS1_PromptCardYesNo(void);
s16 display_Card_TestBut(void);
s16 PS1_PleaseInsertPad(void);
void PS1_CheckCardChanged(void);
void FUN_801a0c68(void);
void PS1_SetNoCard(void);
void PS1_DoYouHaveCard(void);
void PS1_PromptCardFormat(void);
void PS1_GetNbreSave1(void);
void FUN_801a10a4(void);
s16 PS1_ReadingMemoryCard(void);
void FUN_801a1110(void);
void PS1_PromptPad(void);
void PS1_PromptCardErase(void);
u8 PS1_PromptSaveWldMap(void);
u8 PS1_PromptQuit(void);

#endif