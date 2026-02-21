#include "vignet.h"

#ifdef BSS_DEFS
s16 loop_nb_trames;
u8 Vignet_To_Display;
#endif

/* 9A14 8012E214 -O2 -msoft-float */
void DISPLAY_TXT_VIGNET(void)
{
    u32 i;

    for (
        i = new_txt_fee;
        text_to_display[i].text[0] != '\0' && (i <= new_txt_fee + 1);
        i++
    )
        display_box_text(&text_to_display[i]);
}

/* 9AC4 8012E2C4 -O2 -msoft-float */
s16 display_vignet_prg(void)
{
    s16 unk_1;
    s16 unk_2;

    readinput();
    DO_FADE();
    DISPLAY_FOND3();
    DISPLAY_TXT_VIGNET();
    if (++loop_nb_trames == 60)
    {
        loop_nb_trames = 0;
        loop_timing--;
    }

    unk_1 = false;
    if (
        (
            (but0pressed__CROSS() || but1pressed__START()) &&
            loop_timing < 4
        ) || loop_timing < 1
    )
        unk_1 = true;

    if (unk_1)
    {
        if (text_to_display[new_txt_fee + 2].text[0] == '\0')
            new_txt_fee = 10;
        else
        {
            unk_1 = false;
            loop_timing = 5;
            new_txt_fee += 2;
        }
    }

    unk_2 = unk_1 && new_txt_fee == 10;
    return unk_2;
}

/* 9C28 8012E428 -O2 -msoft-float */
void DISPLAY_GAME_VIGNET(void)
{
    mute_snd();
    DO_FADE_OUT();
    INIT_FADE_IN();
    INIT_VIGNET();
    SYNCHRO_LOOP(display_vignet_prg);
    DO_FADE_OUT();
    Vignet_To_Display = 0;
    PROC_EXIT = false;
    INIT_FADE_IN();
}
