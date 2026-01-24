#include "main_moteur.h"

#ifdef BSS_DEFS
u8 gele;
#endif

/* AD90 8012F590 -O2 -msoft-float */
void DO_GROS_MOTEUR_NORMAL(void)
{
    PS1_DoDemo(&record);
    if ((!PS1_DebugMode || !D_801CEFC8) && !in_pause)
    {
        if (gele == 0)
        {
            DO_MOTEUR();
            DO_MOTEUR2();
        }
        else
            DO_MOTEUR_GELE();
    }
}

/* AE28 8012F628 -O2 -msoft-float */
void DO_MAIN_LOOP(void)
{
    s16 i;
    Display *new_disp_1;
    Display *new_disp_2;
    RECT *new_rect;

    new_disp_1 = &PS1_Displays[0];
    if (PS1_CurrentDisplay == &PS1_Displays[0])
        new_disp_1 = &PS1_Displays[1];

    for (i = 0; i < PS1_PolygonIndexTableCount; i++)
    {
        SetPolyFT4(&new_disp_1->polygons[PS1_PolygonIndexTable[i]]);
        SetSemiTrans(&new_disp_1->polygons[PS1_PolygonIndexTable[i]], false);
        SetShadeTex(&new_disp_1->polygons[PS1_PolygonIndexTable[i]], true);
    }
    PS1_PolygonIndexTableCount = 0;

    new_disp_2 = &PS1_Displays[0];
    if (PS1_CurrentDisplay == &PS1_Displays[0])
        new_disp_2 = &PS1_Displays[1];
    PS1_CurrentDisplay = new_disp_2;

    ClearOTag((OT_TYPE *) PS1_CurrentDisplay->ordering_table, LEN(PS1_CurrentDisplay->ordering_table));
    D_801E4BE0 = 0x19;
    D_801F4A28 = 0;
    PS1_Disp_Cur_Tile1 = 0;
    PS1_PolygonsCount = 0;
    D_801F81B0 = 0;
    if (PS1_MemoryUsageDisplayMode == 2)
        ClearImage(PTR_PS1_MemoryUsageRect_801cee70, 128, 128, 128);
    readinput();
    if (PS1_MemoryUsageDisplayMode == 2)
        ClearImage(PTR_PS1_MemoryUsageRect_801cee70, 128, 0, 0);
    D_801CEEA0 = 0;
    DO_GROS_MOTEUR_NORMAL();
    PS1_Ingame = true;
    D_801CEEA0 = 0;
    if (xmap < 0)
        xmap = 0;
    if (ymap < 0)
        ymap = 0;
    if (xmapmax < 0)
        xmapmax = 0;
    if (ymapmax < 0)
        ymapmax = 0;

    if (in_pause)
        DO_AFFICHE_PAUSE();
    if (PS1_MemoryUsageDisplayMode == 2)
        ClearImage(PTR_PS1_MemoryUsageRect_801cee70, 0, 128, 0);
    if (num_world == 5 && num_level == 4)
        Display_and_free_luciole();
    if (PS1_MemoryUsageDisplayMode == 2)
        ClearImage(PTR_PS1_MemoryUsageRect_801cee70, 0, 128, 128);
    display_flocons_behind();
    DISPLAY_ALL_OBJECTS();
    display_grp_stars();
    display_pix_gerbes();
    display_flocons_before();
    if ((num_world == 2 && num_level == 4) || (num_world == 4 && num_level == 9))
    {
        if (((PS1_GlobalTimer & 0x3f) == 0) && myRand(256) > 128)
        {
            PlaySnd_old(195);
            PS1_LightningLoop(8, 9);
            D_801CEEA2 = 0;
        }
        else
            PS1_LightningLoop(1, 9);
    }
    if (is_fee)
        DISPLAY_TEXT_FEE();
    else
        DISPLAY_FIXE(left_time);
    display_time(left_time);
    DRAW_MAP();
    if (PS1_PictureInPicture)
        PS1_DO_PICTURE_IN_PICTURE();
    if (PS1_MemoryUsageDisplayMode != 0)
        ClearImage(PTR_PS1_MemoryUsageRect_801cee70, 0, 0, 0);
    DrawSync(0);
    VSync(0);
    if (PS1_15fps)
    {
        VSync(0);
        VSync(0);
        VSync(0);
    }
    PutDispEnv(&PS1_CurrentDisplay->display_environment);
    PutDrawEnv(&PS1_CurrentDisplay->drawing_environment);

    if (PTR_PS1_MemoryUsageRect_801cee70 == &PS1_MemoryUsageRects[0])
        new_rect = &PS1_MemoryUsageRects[1];
    else
        new_rect = &PS1_MemoryUsageRects[0];
    PTR_PS1_MemoryUsageRect_801cee70 = new_rect;
    if (PS1_MemoryUsageDisplayMode != 0)
        ClearImage(new_rect, 0, 0, 128);
#ifndef PLATFORM_PSYZ 
// TODO: Fix this function crashing the game on PC
//       as it's responsible for rendering bgs
    PS1_DisplayFondSprites();
#endif
    DrawSync(0);
    if (PS1_MemoryUsageDisplayMode == 2)
        ClearImage(PTR_PS1_MemoryUsageRect_801cee70, 128, 0, 128);
    DrawOTag((OT_TYPE *) PS1_CurrentDisplay->ordering_table);
    PS1_CheckPauseAndCheatInputs();
    if (dead_time != 64 && PS1_CanPlayDeathMusic)
    {
        start_cd_perdu();
        PS1_CanPlayDeathMusic = false;
    }
    FUN_80168f48();
    CdSync(1, null);
    FUN_8013045c();
    if (scrollLocked && !PS1_ScrollLockedAudio)
        change_audio_track_puit();
    if (Vignet_To_Display != 0)
    {
        PS1_Ingame = false;
        DISPLAY_GAME_VIGNET();
        PS1_Ingame = true;
    }
}