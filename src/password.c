#include "password.h"

/*
pre-bitfield version found in https://github.com/fuerchter/rayman-ps1-decomp/tree/41e4fcfbed817cea65fb049787fa27c8e40988b4

TODO:
uses of 0x1f are either based on LEN(display_table) or LEN(translate_table) ??? or default char, see PS1_ClearPassword
replace x_pos 160 with macro?
*/

const u8 s_x__validate_password_8012c3b0[] = "/x : validate password/";
const u8 s_left__right__move_8012c3c8[] = "/left | right : move/";
const u8 s_up__down__browse_8012c3e0[] = "/up | down : browse/";
const u8 s_x__validate_letter_8012c3f8[] = "/x : validate letter/";
const u8 s_wrong_password_8012c410[] = "/wrong password/";
const u8 s_enter_password_8012c424[] = "/enter password/";
const u8 s_select__return_8012c438[] = "/select : return/";

#ifdef BSS_DEFS
u8 PS1_ShouldClearPassword;
PasswordChar PS1_CurrentPassword[10];
u8 PS1_CurrentTypingPassword[10];
s16 D_801E4E40;
s16 D_801E4E48;
u8 D_801E57A8;
u8 PS1_ValidPassword;
#endif

/* 7CCA0 801A14A0 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/password", PS1_EncryptPassword);
#else
/* casts, unk_1? */
void PS1_EncryptPassword(void)
{
    u8 i;
    s16 unk_1;
    u16 sum = 0;
    
    for (i = 0; i < LEN(PS1_CurrentPassword); i++)
    {
        *(u8 *) &PS1_CurrentPassword[i] ^= PS1_PasswordTables.xor_table[i];
        sum += (*(u8 *) &PS1_CurrentPassword[i] >> 1) * PS1_PasswordTables.verification_table[i];
    }

    unk_1 = sum >> 0;
    PS1_CurrentPassword[9].bit_0 = unk_1;
    PS1_CurrentPassword[7].bit_0 = sum >> 1;
    PS1_CurrentPassword[6].bit_0 = sum >> 2;
    PS1_CurrentPassword[8].bit_0 = sum >> 3;
    PS1_CurrentPassword[5].bit_0 = sum >> 4;
    PS1_CurrentPassword[0].bit_0 = sum >> 5;
    PS1_CurrentPassword[1].bit_0 = sum >> 6;
    PS1_CurrentPassword[3].bit_0 = sum >> 7;
    PS1_CurrentPassword[2].bit_0 = sum >> 8;
    PS1_CurrentPassword[4].bit_0 = sum >> 9;
}
#endif

/* 7CE74 801A1674 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/password", PS1_VerifyDecryptPassword);
#else
/* casts, having to add PS1_CurrentPassword[9] separately? */
s32 PS1_VerifyDecryptPassword(void)
{
    u8 i;
    u16 sum_2;
    u16 sum_1 = 0;
    
    for (i = 0; i < LEN(PS1_CurrentPassword); i++)
    {
        sum_1 += (*(u8 *) &PS1_CurrentPassword[i] >> 1) * PS1_PasswordTables.verification_table[i];
        *(u8 *) &PS1_CurrentPassword[i] ^= PS1_PasswordTables.xor_table[i];
    }

    sum_2 = (PS1_CurrentPassword[9].bit_0 << 0);
    sum_2 = sum_2 +
        (PS1_CurrentPassword[7].bit_0 << 1) +
        (PS1_CurrentPassword[6].bit_0 << 2) +
        (PS1_CurrentPassword[8].bit_0 << 3) +
        (PS1_CurrentPassword[5].bit_0 << 4) +
        (PS1_CurrentPassword[0].bit_0 << 5) +
        (PS1_CurrentPassword[1].bit_0 << 6) +
        (PS1_CurrentPassword[3].bit_0 << 7) +
        (PS1_CurrentPassword[2].bit_0 << 8) +
        (PS1_CurrentPassword[4].bit_0 << 9);

    return sum_1 == sum_2;
}
#endif

/* thanks! https://decomp.me/scratch/LRbGF */
/* 7CFC8 801A17C8 -O2 -msoft-float */
void FUN_801a17c8(u8 param_1)
{
    PS1_CurrentPassword[4].bit_2 = param_1 >> 0 & 1;
    PS1_CurrentPassword[2].bit_2 = param_1 >> 1 & 1;
    PS1_CurrentPassword[3].bit_2 = param_1 >> 2 & 1;
    PS1_CurrentPassword[1].bit_2 = param_1 >> 3 & 1;
    PS1_CurrentPassword[0].bit_2 = param_1 >> 4 & 1;
}

/* 7D070 801A1870 -O2 -msoft-float */
u8 PS1_GetLevelFromPassword(void)
{
    return (PS1_CurrentPassword[4].bit_2 << 0) +
           (PS1_CurrentPassword[2].bit_2 << 1) +
           (PS1_CurrentPassword[3].bit_2 << 2) +
           (PS1_CurrentPassword[1].bit_2 << 3) +
           (PS1_CurrentPassword[0].bit_2 << 4);
}

/* 7D0D0 801A18D0 -O2 -msoft-float */
void PS1_GeneratePassword_LivesCount(u8 lives_count)
{
    PS1_CurrentPassword[3].bit_3 = lives_count >> 0 & 1;
    PS1_CurrentPassword[2].bit_3 = lives_count >> 1 & 1;
    PS1_CurrentPassword[5].bit_3 = lives_count >> 2 & 1;
    PS1_CurrentPassword[1].bit_3 = lives_count >> 3 & 1;
    PS1_CurrentPassword[4].bit_3 = lives_count >> 4 & 1;
    PS1_CurrentPassword[0].bit_3 = lives_count >> 5 & 1;
    PS1_CurrentPassword[7].bit_3 = lives_count >> 6 & 1;
}

/* 7D1B8 801A19B8 -O2 -msoft-float */
u8 PS1_GetLivesFromPassword(void)
{
    return (PS1_CurrentPassword[3].bit_3 << 0) +
           (PS1_CurrentPassword[2].bit_3 << 1) +
           (PS1_CurrentPassword[5].bit_3 << 2) +
           (PS1_CurrentPassword[1].bit_3 << 3) +
           (PS1_CurrentPassword[4].bit_3 << 4) +
           (PS1_CurrentPassword[0].bit_3 << 5) +
           (PS1_CurrentPassword[7].bit_3 << 6);
}

/* 7D240 801A1A40 -O2 -msoft-float */
void PS1_GeneratePassword_nbContinue(u8 param_1)
{
    PS1_CurrentPassword[5].bit_2 = param_1 >> 0 & 1;
    PS1_CurrentPassword[7].bit_2 = param_1 >> 1 & 1;
    PS1_CurrentPassword[6].bit_2 = param_1 >> 2 & 1;
    PS1_CurrentPassword[9].bit_4 = param_1 >> 3 & 1;
}

/* 7D2C8 801A1AC8 -O2 -msoft-float */
u8 PS1_GetContinuesFromPassword(void)
{
    return (PS1_CurrentPassword[5].bit_2 << 0) +
           (PS1_CurrentPassword[7].bit_2 << 1) +
           (PS1_CurrentPassword[6].bit_2 << 2) +
           (PS1_CurrentPassword[9].bit_4 << 3);
}

/* 7D314 801A1B14 -O2 -msoft-float */
u8 PS1_ValidatePassword(void)
{
    u8 is_valid;
    u8 cc_sum;
    u8 i;
    u8 lvl = PS1_GetLevelFromPassword();

    PS1_PasswordTables.temp_cage_counts[0] = PS1_CurrentPassword[0].bit_1;
    PS1_PasswordTables.temp_cage_counts[1] = PS1_CurrentPassword[2].bit_1;
    PS1_PasswordTables.temp_cage_counts[2] = PS1_CurrentPassword[4].bit_1;
    PS1_PasswordTables.temp_cage_counts[3] = PS1_CurrentPassword[1].bit_1;
    PS1_PasswordTables.temp_cage_counts[4] = PS1_CurrentPassword[3].bit_1;
    PS1_PasswordTables.temp_cage_counts[5] = PS1_CurrentPassword[5].bit_1;
    PS1_PasswordTables.temp_cage_counts[6] = PS1_CurrentPassword[7].bit_1;
    PS1_PasswordTables.temp_cage_counts[7] = PS1_CurrentPassword[6].bit_1;
    PS1_PasswordTables.temp_cage_counts[8] = PS1_CurrentPassword[8].bit_1;
    PS1_PasswordTables.temp_cage_counts[9] = PS1_CurrentPassword[9].bit_1;
    PS1_PasswordTables.temp_cage_counts[10] = PS1_CurrentPassword[4].bit_4;
    PS1_PasswordTables.temp_cage_counts[11] = PS1_CurrentPassword[0].bit_4;
    PS1_PasswordTables.temp_cage_counts[12] = PS1_CurrentPassword[2].bit_4;
    PS1_PasswordTables.temp_cage_counts[13] = PS1_CurrentPassword[1].bit_4;
    PS1_PasswordTables.temp_cage_counts[14] = PS1_CurrentPassword[5].bit_4;
    PS1_PasswordTables.temp_cage_counts[15] = PS1_CurrentPassword[3].bit_4;
    PS1_PasswordTables.temp_cage_counts[16] = PS1_CurrentPassword[7].bit_4;
    PS1_PasswordTables.temp_cage_counts[17] = PS1_CurrentPassword[6].bit_4;

    is_valid =
        lvl < LEN(PS1_PasswordTables.temp_cage_counts) &&
        !(lvl == 2 || lvl == 3 || lvl == 6 || lvl == 7);

    if (!is_valid)
        return 2;

    if (PS1_GetLivesFromPassword() >= 100)
        return 3;

    if (PS1_GetContinuesFromPassword() >= 10)
        return 4;

    is_valid =
        PS1_CurrentPassword[9].bit_3
        ? (PS1_CurrentPassword[8].bit_2 && lvl > 3)
        : lvl < 9;

    if (!is_valid)
        return 5;

    is_valid =
        PS1_CurrentPassword[8].bit_3
        ? (PS1_CurrentPassword[9].bit_2 && lvl > 7)
        : is_valid;

    if (!is_valid)
        return 6;

    is_valid =
        PS1_CurrentPassword[8].bit_4
        ? lvl > 9
        : lvl < 11 && PS1_PasswordTables.temp_cage_counts[11] == 0;

    if (!is_valid)
        return 7;

    is_valid =
        PS1_CurrentPassword[6].bit_3
        ? (lvl > 15 && PS1_CurrentPassword[8].bit_4 && PS1_CurrentPassword[9].bit_3)
        : (lvl < 17 && PS1_PasswordTables.temp_cage_counts[17] == 0);

    if (!is_valid)
        return 8;

    is_valid =
        PS1_CurrentPassword[8].bit_2
        ? lvl > 3
        : (PS1_PasswordTables.temp_cage_counts[3] == 0 && !PS1_CurrentPassword[9].bit_3);

    if (!is_valid)
        return 0x0F;

    is_valid =
        PS1_CurrentPassword[9].bit_2
        ? lvl > 7
        : (PS1_PasswordTables.temp_cage_counts[7] == 0 && !PS1_CurrentPassword[8].bit_3);

    if (!is_valid)
        return 0x10;

    is_valid =
        PS1_PasswordTables.temp_cage_counts[3] != 0
        ? PS1_CurrentPassword[8].bit_2
        : is_valid;

    if (!is_valid)
        return 0x0C;

    if (PS1_PasswordTables.temp_cage_counts[7] != 0)
    {
        is_valid = PS1_CurrentPassword[9].bit_2;
        if (!is_valid)
            return 0x0D;
    }

    cc_sum = 0;
    for (i = lvl + 1; i < LEN(PS1_PasswordTables.temp_cage_counts); i++)
        cc_sum += PS1_PasswordTables.temp_cage_counts[i];

    is_valid = cc_sum == 0;
    if (!is_valid)
        return 0x0E;

    if (lvl > 8)
        is_valid = PS1_CurrentPassword[9].bit_3 && PS1_CurrentPassword[8].bit_2;

    if (!is_valid)
        return 9;

    if (lvl > 10)
    {
        is_valid = PS1_CurrentPassword[8].bit_4;
        if (!is_valid)
            return 0x0A;
    }

    if (lvl == 17 || PS1_PasswordTables.temp_cage_counts[17] != 0)
    {
        cc_sum = 0;
        for (i = 0; i < LEN(PS1_PasswordTables.temp_cage_counts) - 1; i++)
            cc_sum += PS1_PasswordTables.temp_cage_counts[i];

        is_valid =
            cc_sum == 17 &&
            PS1_CurrentPassword[6].bit_3 &&
            PS1_CurrentPassword[9].bit_2 &&
            PS1_CurrentPassword[8].bit_2;
    }

    if (is_valid)
        return is_valid;
    else
        return 0x0B;
}

/* 7D948 801A2148 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/password", PS1_GeneratePassword);
#else
/* duplication? */
/* thanks! https://decomp.me/scratch/6aOG2 */
u8 PS1_GeneratePassword(void)
{
    u8 i;

    memset(&PS1_CurrentPassword, 0, sizeof(PS1_CurrentPassword));
    PS1_CurrentPassword[0].bit_1 = t_world_info[0].nb_cages == 6;
    PS1_CurrentPassword[2].bit_1 = t_world_info[1].nb_cages == 6;
    PS1_CurrentPassword[4].bit_1 = t_world_info[2].nb_cages == 6;
    PS1_CurrentPassword[1].bit_1 = t_world_info[3].nb_cages == 6;
    PS1_CurrentPassword[3].bit_1 = t_world_info[4].nb_cages == 6;
    PS1_CurrentPassword[5].bit_1 = t_world_info[5].nb_cages == 6;
    PS1_CurrentPassword[7].bit_1 = t_world_info[6].nb_cages == 6;
    PS1_CurrentPassword[6].bit_1 = t_world_info[7].nb_cages == 6;
    PS1_CurrentPassword[8].bit_1 = t_world_info[8].nb_cages == 6;
    PS1_CurrentPassword[9].bit_1 = t_world_info[9].nb_cages == 6;
    PS1_CurrentPassword[4].bit_4 = t_world_info[10].nb_cages == 6;
    PS1_CurrentPassword[0].bit_4 = t_world_info[11].nb_cages == 6;
    PS1_CurrentPassword[2].bit_4 = t_world_info[12].nb_cages == 6;
    PS1_CurrentPassword[1].bit_4 = t_world_info[13].nb_cages == 6;
    PS1_CurrentPassword[5].bit_4 = t_world_info[14].nb_cages == 6;
    PS1_CurrentPassword[3].bit_4 = t_world_info[15].nb_cages == 6;
    PS1_CurrentPassword[7].bit_4 = t_world_info[16].nb_cages == 6;
    PS1_CurrentPassword[6].bit_4 = finBosslevel.mr_dark;
    PS1_CurrentPassword[8].bit_2 = t_world_info[3].is_unlocked || t_world_info[3].is_unlocking;
    PS1_CurrentPassword[9].bit_2 = t_world_info[7].is_unlocked || t_world_info[7].is_unlocking;

    i = 18;
    do
    {
        i--;
        if (i == 3 || i == 7)
            i -= 2;
    } while (!(t_world_info[i].is_unlocked == true || t_world_info[i].is_unlocking == true));

    FUN_801a17c8(i);
    PS1_CurrentPassword[9].bit_3 = finBosslevel.moskito;
    PS1_CurrentPassword[6].bit_3 = finBosslevel.mr_skops;
    PS1_CurrentPassword[8].bit_4 = finBosslevel.helped_musician;
    PS1_CurrentPassword[8].bit_3 = finBosslevel.mr_sax;
    PS1_GeneratePassword_LivesCount((u8) status_bar.num_lives);
    PS1_GeneratePassword_nbContinue(nb_continue);

    PS1_IsPasswordValid = PS1_ValidatePassword();
    if (PS1_IsPasswordValid == true)
        PS1_EncryptPassword();

    return PS1_IsPasswordValid;
}
#endif

/* thanks! https://decomp.me/scratch/5n1p8 */
/* 7DDEC 801A25EC -O2 -msoft-float */
void PS1_LoadSaveFromPassword(void)
{
    u8 lvl;
    u8 i;

    INIT_NEW_GAME();
    lvl = PS1_GetLevelFromPassword();

    for (i = 0; i <= lvl; i++)
        t_world_info[i].is_unlocked = true;

    t_world_info[7].is_unlocked = PS1_CurrentPassword[9].bit_2;
    t_world_info[3].is_unlocked = PS1_CurrentPassword[8].bit_2;
    t_world_info[18].is_unlocked = lvl > 0;
    t_world_info[19].is_unlocked = lvl > 4;
    t_world_info[20].is_unlocked = lvl > 6 && PS1_CurrentPassword[9].bit_2;
    t_world_info[21].is_unlocked = lvl > 9;
    t_world_info[22].is_unlocked = lvl > 13;
    t_world_info[23].is_unlocked = lvl > 15;
    t_world_info[0].nb_cages = PS1_CurrentPassword[0].bit_1 ? 6 : 0; /* TODO: macro */
    t_world_info[1].nb_cages = PS1_CurrentPassword[2].bit_1 ? 6 : 0;
    t_world_info[2].nb_cages = PS1_CurrentPassword[4].bit_1 ? 6 : 0;
    t_world_info[3].nb_cages = PS1_CurrentPassword[1].bit_1 ? 6 : 0;
    t_world_info[4].nb_cages = PS1_CurrentPassword[3].bit_1 ? 6 : 0;
    t_world_info[5].nb_cages = PS1_CurrentPassword[5].bit_1 ? 6 : 0;
    t_world_info[6].nb_cages = PS1_CurrentPassword[7].bit_1 ? 6 : 0;
    t_world_info[7].nb_cages = PS1_CurrentPassword[6].bit_1 ? 6 : 0;
    t_world_info[8].nb_cages = PS1_CurrentPassword[8].bit_1 ? 6 : 0;
    t_world_info[9].nb_cages = PS1_CurrentPassword[9].bit_1 ? 6 : 0;
    t_world_info[10].nb_cages = PS1_CurrentPassword[4].bit_4 ? 6 : 0;
    t_world_info[11].nb_cages = PS1_CurrentPassword[0].bit_4 ? 6 : 0;
    t_world_info[12].nb_cages = PS1_CurrentPassword[2].bit_4 ? 6 : 0;
    t_world_info[13].nb_cages = PS1_CurrentPassword[1].bit_4 ? 6 : 0;
    t_world_info[14].nb_cages = PS1_CurrentPassword[5].bit_4 ? 6 : 0;
    t_world_info[15].nb_cages = PS1_CurrentPassword[3].bit_4 ? 6 : 0;
    t_world_info[16].nb_cages = PS1_CurrentPassword[7].bit_4 ? 6 : 0;
    t_world_info[17].nb_cages = 0;

    memset(&RayEvts, 0, sizeof(RayEvts));
    RayEvts.poing = lvl > 0;
    RayEvts.hang = lvl > 3;
    RayEvts.grap = PS1_CurrentPassword[9].bit_3;
    RayEvts.helico = lvl > 7;
    RayEvts.run = lvl > 10;

    memset(&finBosslevel, 0, sizeof(finBosslevel));
    finBosslevel.bzzit = lvl > 3;
    finBosslevel.moskito = PS1_CurrentPassword[9].bit_3;
    finBosslevel.mr_sax = PS1_CurrentPassword[8].bit_3;
    finBosslevel.mr_stone = lvl > 10;
    finBosslevel.viking_mama = lvl > 11;
    finBosslevel.space_mama = lvl > 13;
    finBosslevel.mr_skops = PS1_CurrentPassword[6].bit_3;
    finBosslevel.mr_dark = PS1_CurrentPassword[6].bit_4;
    finBosslevel.helped_musician = PS1_CurrentPassword[8].bit_4;

    status_bar.num_lives = PS1_GetLivesFromPassword();
    nb_continue = PS1_GetContinuesFromPassword();
    world_index = 0;
    xwldmapsave = 0;
    ywldmapsave = 158;
    dir_on_wldmap = 1;
}

/* 7E2F0 801A2AF0 -O2 -msoft-float */
u8 PS1_AttemptLoadSaveFromPassword(void)
{
    if (
        (PS1_IsPasswordValid = PS1_VerifyDecryptPassword()) == true &&
        (PS1_IsPasswordValid = PS1_ValidatePassword()) == true
    )
        PS1_LoadSaveFromPassword();
    return PS1_IsPasswordValid;
}

/* 7E35C 801A2B5C -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/password", PS1_UnusedGenerateAndPrintPassword);
#else
/* casts? */
void PS1_UnusedGenerateAndPrintPassword(s16 param_1, s16 param_2, u8 param_3, u8 param_4)
{
    u8 i;
    u8 pass[16];

    PS1_IsPasswordValid = PS1_GeneratePassword();
    for (i = 0; i < LEN(PS1_CurrentPassword); i++)
        pass[i] = PS1_PasswordTables.display_table[*(u8 *) &PS1_CurrentPassword[i] & 0x1F];

    if (PS1_IsPasswordValid == true)
        pass[10] = '\0';
    else
    {
        pass[10] = ' ';
        pass[11] = 'e';
        pass[12] = '\0';
    }
    display_text(pass, param_1, param_2, param_3, param_4);
}
#endif

/* 7E35C 801A2B5C -O2 -msoft-float */
void PS1_ClearPassword(void)
{
    memset(&PS1_CurrentTypingPassword, 0x1F, LEN(PS1_CurrentTypingPassword));
}

/* 7E478 801A2C78 -O2 -msoft-float */
void FUN_801a2c78(void)
{
    basex = 75;
    debut_titre = 35;
    debut_options = 95;
    PS1_display_y1 = 131;
    D_801E4E40 = 174;
    D_801E4E48 = 215;
    PS1_CharXSpacing = 21;
    positionx = 0;
    MENU_RETURN = false;
    positiony = 0;
    D_801E57A8 = 0;
    PS1_ValidPassword = false;
    max_compteur = 100;
    delai_repetition = 25;
    if (PS1_ShouldClearPassword == 1)
        PS1_ClearPassword();
}

/* 7E540 801A2D40 -O2 -msoft-float */
void FUN_801a2d40(void)
{
    s32 char_ind;
    u8 character[2];
    s16 max_clignote = 40;

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

    if (compteur_clignote < max_clignote)
        compteur_clignote++;
    else
        compteur_clignote = 0;

    for (char_ind = 0; char_ind < (s16) LEN(PS1_CurrentTypingPassword); char_ind++)
    {
        character[0] =
            PS1_PasswordTables.display_table[
                PS1_PasswordTables.translate_table[
                    PS1_CurrentTypingPassword[char_ind] & 0x1F
                ]
            ];
        character[1] = '\0';

        if (positionx == char_ind && positiony == 0)
        {
            if (!(D_801F5448 && (compteur_clignote > max_clignote >> 1)))
                display_text(
                    character,
                    basex + (char_ind - 1) * PS1_CharXSpacing,
                    debut_options, 1, 6
                );
        }
        else
            display_text(
                character,
                basex + (char_ind - 1) * PS1_CharXSpacing,
                debut_options,
                1, 1
            );
    }

    if (positiony == 1)
    {

        if (!(D_801F5448 && (compteur_clignote > max_clignote >> 1)))
            display_text(s_ok_801cf108, 160, PS1_display_y1, 1, 6);
        display_text(s_x__validate_password_8012c3b0, 160, D_801E4E40, 2, 10);
        display_text(s_left__right__move_8012c3c8, 160, D_801E4E48, 2, 10);
    }
    else if (positiony == 0)
    {
        display_text(s_ok_801cf108, 160, PS1_display_y1, 1, 1);
        display_text(s_up__down__browse_8012c3e0, 160, D_801E4E40, 2, 10);
        display_text(s_x__validate_letter_8012c3f8, 160, D_801E4E40 + 15, 2, 10);
        display_text(s_left__right__move_8012c3c8, 160, D_801E4E48, 2, 10);
    }
    else
        display_text(s_wrong_password_8012c410, 160, D_801E4E40, 1, 1);
}

/* 7E864 801A3064 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/password", FUN_801a3064);
#else
/* casts */
void FUN_801a3064(void)
{
    s32 char_ind;
    u8 valid_prs = but0pressed__CROSS();

    if ((compteur > delai_repetition || button_released != 0) && positiony != 2)
    {
        if ((positiony == 1 && valid_prs) || but1pressed__START())
        {
            PlaySnd_old(69);
            for (char_ind = 0; char_ind < (s16) LEN(PS1_CurrentTypingPassword); char_ind++)
            {
                *(u8 *) &PS1_CurrentPassword[char_ind] =
                    PS1_PasswordTables.translate_table[
                        PS1_CurrentTypingPassword[char_ind]
                    ];
            }
            if (PS1_AttemptLoadSaveFromPassword() != true)
                positiony = 2;
            else
                PS1_ValidPassword = true;
        }

        if (!(upjoy(0) || downjoy(0)))
        {
            if (leftjoy(0))
            {
                compteur = 0;
                if (positiony == 0)
                {
                    if (positionx <= 0)
                    {
                        positiony = 1;
                        positionx = 0;
                    }
                    else
                        positionx--;
                }
                else
                {
                    positiony = 0;
                    positionx = (s16) LEN(PS1_CurrentTypingPassword) - 1;
                }
                PlaySnd_old(68);
            }
            else if (rightjoy(0) || (valid_prs && positiony == 0))
            {
                compteur = 0;
                if (positiony == 0)
                {
                    if (positionx >= (s16) LEN(PS1_CurrentTypingPassword) - 1)
                    {
                        positionx = (s16) LEN(PS1_CurrentTypingPassword) - 1;
                        positiony = 1;
                    }
                    else
                        positionx++;
                }
                else
                {
                    positiony = 0;
                    positionx = 0;
                }

                if (valid_prs && positiony == 0)
                    PlaySnd_old(69);
                else
                    PlaySnd_old(68);
            }
            D_801E57A8 = PS1_CurrentTypingPassword[positionx];
        }

        if (!(rightjoy(0) || leftjoy(0)) && positiony == 0)
        {
            if (upjoy(0))
            {
                D_801E57A8++;
                D_801E57A8 &= 0x1F;
                if (button_released != 0)
                    PlaySnd_old(68);
            }
            else if (downjoy(0))
            {
                D_801E57A8 += 0x1F;
                D_801E57A8 &= 0x1F;
                if (button_released != 0)
                    PlaySnd_old(68);
            }
            PS1_CurrentTypingPassword[positionx] = D_801E57A8;
        }
    }
    if (
        !(
            upjoy(0) || downjoy(0) ||
            rightjoy(0) || leftjoy(0) ||
            valid_prs || PS1_ValidPassword
        )
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
}
#endif

/* 7EC58 801A3458 -O2 -msoft-float */
s16 PS1_MenuPassword(void)
{
    s16 x_pos;
    u8 should_ret = false;

    CLRSCR();
    volet();
    DO_FADE();
    readinput();

    x_pos = 160;
    display_text(s_enter_password_8012c424, x_pos, debut_titre, 1, 1);
    display_text(s_select__return_8012c438, x_pos, D_801E4E48 + 15, 2, 10);
    FUN_801a3064();
    FUN_801a2d40();

    if (but2pressed__SELECT() != 0)
    {
        should_ret = true;
        MENU_RETURN = true;

        while (but2pressed__SELECT())
            readinput();
    }

    return should_ret || PS1_ValidPassword;
}

/* 7ED50 801A3550 -O2 -msoft-float */
void FUN_801a3550(void)
{
    LOAD_SAVE_SCREEN();
    INIT_FADE_IN();
    FUN_801a2c78();
    SYNCHRO_LOOP(PS1_MenuPassword);
    DO_FADE_OUT();
    if (PS1_ValidPassword || MENU_RETURN)
    {
        if (positiony == 2)
        {
            PS1_SaveMode = 2;
            MENU_RETURN = false;
        }
        else
            PS1_SaveMode = 1;
    }
}

/* 7EDF8 801A35F8 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/password", PS1_GenerateAndDisplayPassword);
#else
/* casts */
void PS1_GenerateAndDisplayPassword(void)
{
    /* TODO: correct sizes? */
    u8 i;
    u8 pass[21];
    u8 pass_cen[32];

    PS1_IsPasswordValid = PS1_GeneratePassword();
    for (i = 0; i < LEN(PS1_CurrentPassword); i++)
    {
        pass[i * 2] = PS1_PasswordTables.display_table[*(u8 *) &PS1_CurrentPassword[i] & 0x1f];
        pass[i * 2 + 1] = ' ';
    }

    if (PS1_IsPasswordValid == true)
        pass[20] = '\0';
    sprintf(pass_cen, s_s_801cf110, pass);
    strcpy(text_to_display[0].text, pass_cen);
}
#endif

/* TODO: bad split? here or menu_7EEE4? */
/* 7EEB4 801A36B4 -O2 -msoft-float */
void DEPART_INIT_LOOP(void)
{
    menuEtape = 0;
    dans_la_map_monde = false;
    PS1_ClearPassword();
}
