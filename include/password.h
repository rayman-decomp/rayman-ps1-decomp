#ifndef PASSWORD_H
#define PASSWORD_H

#include "common.h"
#include "num_level_36260.h"

typedef struct PasswordTables
{
    u8 xor_table[10];
    u8 verification_table[10];
    u8 display_table[32];
    u8 translate_table[32];
    u8 temp_cage_counts[18];
} PasswordTables;

typedef struct PasswordChar
{
    u8 bit_0 : 1;
    u8 bit_1 : 1;
    u8 bit_2 : 1;
    u8 bit_3 : 1;
    u8 bit_4 : 1;
    u8 bit_5 : 1;
    u8 bit_6 : 1;
    u8 bit_7 : 1;
} PasswordChar;

/* .data */
extern PasswordTables PS1_PasswordTables;

/* .data */
extern u8 PS1_IsPasswordValid;
extern u8 s_ok_801cf108[5];
extern u8 s_s_801cf110[5];

/**/
extern u8 PS1_ShouldClearPassword; /* don't understand its use in PS1_LoadUnusedIntroScreens */
extern PasswordChar PS1_CurrentPassword[10];
extern u8 PS1_CurrentTypingPassword[10];
extern s16 D_801E4E40;
extern s16 D_801E4E48;
extern u8 D_801E57A8;
extern u8 PS1_ValidPassword;

void PS1_EncryptPassword(void);
s32 PS1_VerifyDecryptPassword(void);
void PS1_GeneratePassword_Level(u8 param_1);
u8 PS1_GetLevelFromPassword(void);
void PS1_GeneratePassword_LivesCount(u8 lives_count);
u8 PS1_GetLivesFromPassword(void);
void PS1_GeneratePassword_nbContinue(u8 param_1);
u8 PS1_GetContinuesFromPassword(void);
u8 PS1_ValidatePassword(void);
u8 PS1_GeneratePassword(void);
void PS1_LoadSaveFromPassword(void);
u8 PS1_AttemptLoadSaveFromPassword(void);
void PS1_UnusedGenerateAndPrintPassword(s16 param_1, s16 param_2, u8 param_3, u8 param_4);
void PS1_ClearPassword(void);
void PS1_InitMenuPassword(void);
void PS1_DisplayMenuPasswordText(void);
void PS1_DoMenuPassword(void);
s16 PS1_MenuPasswordPrg(void);
void PS1_MenuPassword(void);
void PS1_GenerateAndDisplayPassword(void);
void DEPART_INIT_LOOP(void);

#endif