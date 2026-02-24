#include "menu/menu_card_7C028.h"

const u8 s_press_x_button_to_continue_8012c378[] = "/press x button to continue/";
const u8 s_reading_memory_card_8012c398[] = "/reading memory card/";

#ifdef BSS_DEFS
u8 NBRE_SAVE;
u8 PS1_positiony_mc;
u8 PS1_CardStringDisplayed;
s16 PS1_compteur_mc;
u8 PS1_DisplayCardContinueText;
u8 PS1_NoCard;
u8 D_801E5238;
#endif

/* 7C028 801A0828 -O2 -msoft-float */
void PS1_PromptCardInput(void)
{
    if (downjoy(0) && inter_select == 0)
    {
        PS1_positiony_mc++;
        if (PS1_positiony_mc < 3)
            PlaySnd_old(68);
    }
    else if (upjoy(0) && inter_select == 0)
    {
        PS1_positiony_mc--;
        if (PS1_positiony_mc != 0)
            PlaySnd_old(68);
    }

    MIN_2(PS1_positiony_mc, 2);
    if (PS1_positiony_mc == 0)
        PS1_positiony_mc = 1;

    if (++inter_select > 5)
        inter_select = 0;
}

/* 7C164 801A0964 -O2 -msoft-float */
s16 PS1_PromptCardYesNo(void)
{
    s16 done;

    DO_FADE();
    CLRSCR();
    display_text(PS1_CardStrings[PS1_CardStringDisplayed], 160, 140, 2, 0);
    display_text(s_yes_801cf0f4, 160, 173, 2, 0);
    display_text(s_no_801cf0fc, 160, 195, 2, 0);
    PS1_PromptCardDisplayPoing();
    PS1_PromptCardInput();
    readinput();
    if (PS1_compteur_mc != 0)
        PS1_compteur_mc--;

    done = false;
    if (but0pressed__CROSS())
        done = PS1_compteur_mc == 0;
    if (done)
        PlaySnd_old(69);

    return done;
}

/* 7C264 801A0A64 -O2 -msoft-float */
s16 display_Card_TestBut(void)
{
    s16 done;

    DO_FADE();
    CLRSCR();
    display_text(PS1_CardStrings[PS1_CardStringDisplayed], 160, 145, 2, 0);
    if (PS1_DisplayCardContinueText)
        display_text(s_press_x_button_to_continue_8012c378, 160, 195, 2, 0);
    readinput();
    if (PS1_compteur_mc != 0)
        PS1_compteur_mc--;

    done = false;
    if (but0pressed__CROSS())
        done = PS1_compteur_mc == 0;

    return done;
}

/* 7C338 801A0B38 -O2 -msoft-float */
s16 PS1_PleaseInsertPad(void)
{
    s16 done;

    DO_FADE();
    CLRSCR();
    display_text(PS1_CardStrings[PS1_CardStringDisplayed], 160, 145, 2, 0);
    readinput();
    if (PS1_compteur_mc != 0)
        PS1_compteur_mc--;

    done = false;
    if (PS1_InitPAD())
        done = PS1_compteur_mc == 0;

    return done;
}

/* 7C3E0 801A0BE0 -O2 -msoft-float */
void PS1_CheckCardChanged(void)
{
    if (has_MemCard_Changed())
    {
        clearbothdrawenv();
        DO_FADE_OUT();
        INIT_FADE_IN();
        while (InitMemCard_IN())
        {
            PS1_CardStringDisplayed = 8;
            PS1_DisplayCardContinueText = false;
            SYNCHRO_LOOP(display_Card_TestBut);
        }
        DO_FADE_OUT();
        INIT_FADE_IN();
    }
}

/* 7C468 801A0C68 -O2 -msoft-float */
void PS1_NoCardIfMemoryCardChanged(void)
{
    if (has_MemCard_Changed())
        PS1_NoCard = true;
}

/* 7C498 801A0C98 -O2 -msoft-float */
void PS1_SetNoCard(void)
{
    if (PS1_TestCardZero())
        PS1_NoCard = true;
    else
        PS1_NoCard = false;
}

/* 7C4D8 801A0CD8 -O2 -msoft-float */
void PS1_DoYouHaveCard(void)
{
    s16 i;

    if ((s16) PS1_TestCardZero())
    {
        PS1_CardStringDisplayed = 0;
        inter_select = 0;
        PS1_compteur_mc = 10;
        PS1_positiony_mc = 2;
        SYNCHRO_LOOP(PS1_PromptCardYesNo);
        PS1_NoCardIfMemoryCardChanged();
        PS1_compteur_mc = 10;
        if (!PS1_NoCard)
        {
            if (PS1_positiony_mc == 1)
            {
                PS1_CardStringDisplayed = 1;
                PS1_DisplayCardContinueText = false;
                SYNCHRO_LOOP(display_Card_TestBut);
                PS1_NoCard = true;
                for (i = 0; i < 30; i++)
                    VSync(0);
                PS1_NoCardIfMemoryCardChanged();
            }
            else
            {
                PS1_CardStringDisplayed = 2;
                PS1_DisplayCardContinueText = true;
                SYNCHRO_LOOP(display_Card_TestBut);
                PS1_NoCardIfMemoryCardChanged();
                NBRE_SAVE = 0;
            }
        }
    }
}

/* 7C608 801A0E08 -O2 -msoft-float */
void PS1_PromptCardFormat(void)
{
    if (PS1_CardUnformatted())
    {
        PS1_CardStringDisplayed = 3;
        inter_select = 0;
        PS1_compteur_mc = 10;
        PS1_positiony_mc = 2;
        SYNCHRO_LOOP(PS1_PromptCardYesNo);
        PS1_NoCardIfMemoryCardChanged();
        PS1_compteur_mc = 10;
        if (!PS1_NoCard)
        {
            if (PS1_positiony_mc == 2)
            {
                PS1_CardStringDisplayed = 4;
                PS1_DisplayCardContinueText = true;
                SYNCHRO_LOOP(display_Card_TestBut);
                PS1_NoCardIfMemoryCardChanged();
                NBRE_SAVE = 0;
            }
            else
            {
                PS1_FormatMemoryCard();
                PS1_NoCard = true;
            }
        }
    }
}

/* 7C6F0 801A0EF0 -O2 -msoft-float */
void PS1_GetNbreSave1(void)
{
    u8 save_itoa;

    NBRE_SAVE = PS1_GetNbreSave2();
    PS1_compteur_mc = 10;
    if (NBRE_SAVE == 0)
    {
        PS1_CardStringDisplayed = 6;
        PS1_DisplayCardContinueText = true; /* TODO: maybe do this with the goto instead to reduce duplication? */
        SYNCHRO_LOOP(display_Card_TestBut);
        PS1_NoCardIfMemoryCardChanged();
    }
    else if (NBRE_SAVE < 3)
    {
        PS1_CardStringDisplayed = 5;
        PS1_itoa((s16) NBRE_SAVE, &save_itoa, 5);
        PS1_CardStrings[PS1_CardStringDisplayed][6] = save_itoa;
        PS1_CardStrings[PS1_CardStringDisplayed][67] = save_itoa;
        if (NBRE_SAVE < 2)
        {
            PS1_CardStrings[PS1_CardStringDisplayed][79] = ' ';
            PS1_CardStrings[PS1_CardStringDisplayed][12] = ' ';
            PS1_CardStrings[PS1_CardStringDisplayed][14] = 'i';
            PS1_CardStrings[PS1_CardStringDisplayed][15] = 's';
            PS1_CardStrings[PS1_CardStringDisplayed][16] = ' ';
        }
        PS1_DisplayCardContinueText = true;
        SYNCHRO_LOOP(display_Card_TestBut);
        PS1_NoCardIfMemoryCardChanged();
    }
}

void PS1_EmptyFunction14(void) {}

/* 7C8AC 801A10AC -O2 -msoft-float */
s16 PS1_ReadingMemoryCard(void)
{
    CLRSCR();
    display_text(s_reading_memory_card_8012c398, 160, 173, 2, 0);
    D_801CF101++;
    return D_801CF101 == 2;
}

/* 7C910 801A1110 -O2 -msoft-float */
void PS1_LoadMemoryCard(void)
{
    u8 unk_1 = true;

    if (fade == 0)
        INIT_FADE_IN();

    do
    {
        do
        {
            do
            {
                PS1_Checksum = card_checksum(0);
                NBRE_SAVE = 3;
                PS1_NoCard = false;
                PS1_DoYouHaveCard();
                if (unk_1 && !PS1_NoCard && NBRE_SAVE != 0)
                {
                    unk_1 = false;
                    SYNCHRO_LOOP(PS1_ReadingMemoryCard);
                }

                if (!PS1_NoCard)
                {
                    if (NBRE_SAVE != 0)
                        PS1_PromptCardFormat();

                    if (!PS1_NoCard && NBRE_SAVE != 0)
                        PS1_NoCardIfMemoryCardChanged();
                }
                D_801E5238 = PS1_NoCard;
            } while (PS1_NoCard);

            if (NBRE_SAVE != 0)
                PS1_GetNbreSave1();
        } while (PS1_NoCard);

        if (NBRE_SAVE != 0)
            PS1_NoCardIfMemoryCardChanged();
    } while (PS1_NoCard);

    DO_FADE_OUT();
    if (NBRE_SAVE != 0)
        PS1_InitSaveRayAndFilenames(0);
}

/* 7CAB8 801A12B8 -O2 -msoft-float */
void PS1_PromptPad(void)
{
    clearbothdrawenv();
    if (fade == 0)
        INIT_FADE_IN();
    PS1_CardStringDisplayed = 12;
    PS1_DisplayCardContinueText = true;
    SYNCHRO_LOOP(PS1_PleaseInsertPad);
    DO_FADE_OUT();
}

/* 7CB24 801A1324 -O2 -msoft-float */
void PS1_PromptCardErase(void)
{
    PS1_CardStringDisplayed = 9;
    inter_select = 0;
    PS1_compteur_mc = 10;
    PS1_positiony_mc = 2;
    DO_FADE_OUT();
    INIT_FADE_IN();
    SYNCHRO_LOOP(PS1_PromptCardYesNo);
    DO_FADE_OUT();
    INIT_FADE_IN();
}

/* 7CB98 801A1398 -O2 -msoft-float */
u8 PS1_PromptSaveWldMap(void)
{
    PS1_CardStringDisplayed = 10;
    inter_select = 0;
    PS1_compteur_mc = 10;
    PS1_positiony_mc = 1;
    DO_FADE_OUT();
    INIT_FADE_IN();
    SYNCHRO_LOOP(PS1_PromptCardYesNo);
    DO_FADE_OUT();
    INIT_FADE_IN();
    return PS1_positiony_mc == 1;
}

/* 7CC1C 801A141C -O2 -msoft-float */
u8 PS1_PromptQuit(void)
{
    PS1_CardStringDisplayed = 11;
    inter_select = 0;
    PS1_compteur_mc = 10;
    PS1_positiony_mc = 2;
    DO_FADE_OUT();
    INIT_FADE_IN();
    SYNCHRO_LOOP(PS1_PromptCardYesNo);
    DO_FADE_OUT();
    INIT_FADE_IN();
    return PS1_positiony_mc == 1;
}
