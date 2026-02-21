#include "world_map_95CC.h"

#ifdef BSS_DEFS
s16 num_world;
s16 num_level;
s16 xmap;
s16 ymap;

s16 new_world;
s16 new_level;
s16 num_world_choice;
s16 num_level_choice;
u8 old_num_world;
u8 world_index;

s16 inter_select;
s16 level_select;
#endif

/* 95CC 8012DDCC -O2 */
s16 select_level_prg(void)
{
    u8 num[10];

    readinput();

    DISPLAY_FOND_SELECT();
    display_text(s_level_801cedf4, 100, 100, 0, colour);
    PS1_itoa(level_select, &num, 10);
    display_text(num, 200, 100, 0, colour);

    if (rightjoy(0) && inter_select == 0)
        level_select++;
    else if (leftjoy(0) && inter_select == 0)
        level_select--;

    if (level_select > 30)
        level_select = 30;
    if (level_select < 1)
        level_select = 1;

    inter_select++;
    if (inter_select > 3)
        inter_select = 0;

    /* TODO: either *pressed() functions return s16 or this is cast */
    return (s16) but0pressed(0) || (s16) but1pressed(0);
}

/* 975C 8012DF5C -O2 */
/*void SYNCHRO_LOOP(void *);*/
s16 SELECT_LEVEL(s16 sel)
{
    level_select = sel;
    inter_select = 0;
    SYNCHRO_LOOP(select_level_prg);
    return level_select;
}

/* 979C 8012DF9C -O2 */
/*? display_box_text(? *);*/

void DISPLAY_STAGE_NAMES(void)
{
    TextToDisplay *cur;

    if (&text_to_display[1])
        display_box_text(&text_to_display[1]);

    cur = &text_to_display[0];
    if (cur)
        display_box_text(cur);

    cur = &text_to_display[3];
    if (cur)
        display_box_text(cur);

    cur = &text_to_display[2];
    if (cur)
        display_box_text(cur);
}

/* 980C 8012E00C -O2 */
s16 WORLD_CHOICE(void)
{
    let_shadow = false;
    DO_FADE();
    DISPLAY_JUMELLES_FOND(xmap, ymap, 44, 55);
    DISPLAY_PTS_WAY();
    put_env_point_way();
    display(&ray);
    DO_CHEMIN();
    DISPLAY_PLAT_WAY();
    DISPLAY_JUMELLES();
    DISPLAY_STAGE_NAMES();

    readinput();
    PROC_EXIT = but2pressed__SELECT() != 0;
    return new_world || PROC_EXIT;
}

/* 98D4 8012E0D4 -O2 */
void DO_WORLD_MAP(void)
{
    if (ModeDemo == 0)
        charge_wm();

    start_cd_rap();
    INIT_FADE_IN();
    INIT_RAY(new_level);
    INIT_CHEMIN();
    if (ModeDemo == 0)
    {
        readinput();
        if (ModeDemo == 0)
            SYNCHRO_LOOP(WORLD_CHOICE);
    }
    if (PROC_EXIT)
    {
        world_index = num_world_choice;
        fin_du_jeu = true;
        menuEtape = 4;
        num_world_choice = num_world;
        num_world = 0;
        num_level_choice = num_level;
        PlaySnd_old(77);
    }
    else
    {
        DETER_WORLD_AND_LEVEL();
        if (ModeDemo == 0)
            PlaySnd_old(69);
    }
    INIT_FADE_OUT();
    FIN_WORLD_CHOICE();
    stop_cd();
}