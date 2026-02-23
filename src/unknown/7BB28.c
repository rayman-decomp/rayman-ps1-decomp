#include "unknown/7BB28.h"

/* 7BB28 801A0328 -O2 -msoft-float */
void PS1_StopLevelMusic(void)
{
    s16 i = 0;

    if (PS1_CurTrack == 7 || PS1_SongIsPlaying(13))
    {
        while (PS1_SongIsPlaying(13) && i < 8 * 60)
        {
            VSync(0);
            i++;
        }
    }
    PS1_CanPlayDeathMusic = true;
    stop_cd();
    PS1_StopPlayingAllSnd();
    stop_all_snd();
    PS1_EmptyFunction12();
}

/* 7BBC4 801A03C4 -O2 -msoft-float */
void InitDB(Display *display)
{
    s32 i;

    for (i = 0; i < (s16) LEN(display->tiles); i++)
    {
        SetSprt16(&display->tiles[i]);
        SetSemiTrans(&display->tiles[i], false);
        SetShadeTex(&display->tiles[i], true);
        display->tiles[i].u0 = 128;
        display->tiles[i].v0 = 0;
    }
    for (i = 0; i < (s16) LEN(display->sprites); i++)
    {
        SetSprt(&display->sprites[i]);
        SetSemiTrans(&display->sprites[i], false);
        SetShadeTex(&display->sprites[i], true);
    }
    for (i = 0; i < (s16) LEN(display->polygons); i++)
    {
        SetPolyFT4(&display->polygons[i]);
        SetSemiTrans(&display->polygons[i], false);
        SetShadeTex(&display->polygons[i], true);
    }
    for (i = 0; i < (s16) LEN(display->tile1s); i++)
    {
        SetTile1(&display->tile1s[i]);
        SetSemiTrans(&display->tile1s[i], false);
        SetShadeTex(&display->tile1s[i], true);
    }
    for (i = 0; i < (s16) LEN(display->field_0x1e9c_0x321b); i++)
    {
        SetSprt8(&display->field_0x1e9c_0x321b[i]);
        SetSemiTrans(&display->field_0x1e9c_0x321b[i], false);
        SetShadeTex(&display->field_0x1e9c_0x321b[i], true);
        display->field_0x1e9c_0x321b[i].clut = GetClut(768, 490);
    }

    display->drawing_environment.tpage = GetTPage(1, 1, 768, 0);
    SetDrawEnv(&display->map_drawing_environment_primitives[0], &display->drawing_environment);
    display->drawing_environment.tpage = GetTPage(1, 1, 768, 256);
    SetDrawEnv(&display->map_drawing_environment_primitives[1], &display->drawing_environment);
    display->drawing_environment.tpage = GetTPage(1, 1, 928, 0);
    SetDrawEnv(&display->map_drawing_environment_primitives[2], &display->drawing_environment);
    display->drawing_environment.tpage = GetTPage(1, 1, 928, 256);
    SetDrawEnv(&display->map_drawing_environment_primitives[3], &display->drawing_environment);
    display->drawing_environment.tpage = GetTPage(1, 1, 0, 256);
    for (i = 4; i < (s16) LEN(display->map_drawing_environment_primitives); i++)
        SetDrawEnv(&display->map_drawing_environment_primitives[i], &display->drawing_environment);
    display->drawing_environment.tpage = GetTPage(1, 2, 0, 256);
    SetDrawEnv(&display->map_drawing_environment_primitives[8], &display->drawing_environment);
    display->drawing_environment.tpage = GetTPage(1, 1, 320, 0);
    SetDrawEnv(&display->map_drawing_environment_primitives[6], &display->drawing_environment);
    SetDrawEnv(&display->map_drawing_environment_primitives[7], &display->drawing_environment);

    SetPolyG4(&display->field_0x6094_0x60b7);
    SetSemiTrans(&display->field_0x6094_0x60b7, true);
    SetShadeTex(&display->field_0x6094_0x60b7, true);
    display->field_0x6094_0x60b7.x0 = 0;
    display->field_0x6094_0x60b7.y0 = 0;
    display->field_0x6094_0x60b7.x1 = SCREEN_WIDTH;
    display->field_0x6094_0x60b7.y1 = 0;
    display->field_0x6094_0x60b7.x2 = 0;
    display->field_0x6094_0x60b7.y2 = SCREEN_HEIGHT;
    display->field_0x6094_0x60b7.x3 = SCREEN_WIDTH;
    display->field_0x6094_0x60b7.y3 = SCREEN_HEIGHT;
    display->field_0x6094_0x60b7.r0 = 255;
    display->field_0x6094_0x60b7.g0 = 255;
    display->field_0x6094_0x60b7.b0 = 255;
    display->field_0x6094_0x60b7.r1 = 0;
    display->field_0x6094_0x60b7.g1 = 0;
    display->field_0x6094_0x60b7.b1 = 0;
    display->field_0x6094_0x60b7.r2 = 0;
    display->field_0x6094_0x60b7.g2 = 0;
    display->field_0x6094_0x60b7.b2 = 0;
    display->field_0x6094_0x60b7.r3 = 0;
    display->field_0x6094_0x60b7.g3 = 0;
    display->field_0x6094_0x60b7.b3 = 0;

    SetTile(&display->field_0x6084_0x6093);
    SetSemiTrans(&display->field_0x6084_0x6093, true);
    SetShadeTex(&display->field_0x6084_0x6093, true);
    display->field_0x6084_0x6093.x0 = 0;
    display->field_0x6084_0x6093.y0 = 0;
    display->field_0x6084_0x6093.w = SCREEN_WIDTH;
    display->field_0x6084_0x6093.h = SCREEN_HEIGHT;
    display->field_0x6084_0x6093.r0 = 255;
    display->field_0x6084_0x6093.g0 = 255;
    display->field_0x6084_0x6093.b0 = 255;
    InitLuciolle(display);
    initeffet(display);
}

/* 7BF50 801A0750 -O2 -msoft-float */
void FUN_801a0750(void)
{
    if (PS1_SelectPressed(0))
        PROC_EXIT = true;
}

/* 7BF80 801A0780 -O2 -msoft-float */
void PS1_itoa(s16 param_1, u8 *param_2, u8 param_3)
{
    sprintf(param_2, s_d_801cf0f0, param_1);
}

/* 7BFB0 801A07B0 -O2 -msoft-float */
void FUN_801a07b0(void)
{
    if (ModeDemo == 0)
    {
        PS1_PlayVideo(VIDEO_INTRO);
        PROC_EXIT = false;
        PS1_ShouldClearPassword = 0;
    }
}

/* 7BFEC 801A07EC -O2 -msoft-float */
void PS1_PlayMapIntro(void)
{
    if (ModeDemo == 0)
    {
        PS1_PlayVideo(VIDEO_MAP_INTRO);
        PROC_EXIT = false;
        PS1_ShouldClearPassword = 0;
    }
}
