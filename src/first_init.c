#include "first_init.h"

const u8 s_loading_8012c368[] = "/loading.../";

/* 7B048 8019F848 -O2 -msoft-float */
s16 prg_vig_loader1(void)
{
    D_801CF438++;
    DISPLAY_FOND640();
    return (D_801CF438 <= 60) ^ 1;
}

/* 7B08C 8019F88C -O2 -msoft-float */
s16 prg_vig_loader2(void)
{
    D_801CF440++;
    DISPLAY_FOND640();
    return (D_801CF440 <= 60) ^ 1;
}

/* 7B0D0 8019F8D0 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/first_init", loader);
#else
void loader(void)
{
    s32 unk_1; /* TODO: remove */
    RECT fb_rect = D_801CF0E0;
    
    ResetGraph(0);
    SetGraphDebug(0);
    SetDispMask(0);
    clearbothdrawenv();
    SetDefDispEnv(&PS1_Displays[0].field0_0x0, 0, 0, 640, 480);
    SetDefDrawEnv(&PS1_Displays[0].drawing_environment, 0, 0, 640, 480);
    SetDefDispEnv(&PS1_Displays[1].field0_0x0, 0, 0, 640, 480);
    SetDefDrawEnv(&PS1_Displays[1].drawing_environment, 0, 0, 640, 480);
    unk_1 = 1;
    PS1_Displays[unk_1].field0_0x0.pad0 = 0;
    PS1_Displays[0].field0_0x0.pad0 = 0;
    PS1_Displays[1].field0_0x0.isinter = true;
    PS1_Displays[0].field0_0x0.isinter = true;
    InitDB(&PS1_Displays[0]);
    InitDB(&PS1_Displays[1]);
    ClearImage(&fb_rect, 0, 0, 0);
    PutDispEnv(&PS1_CurrentDisplay->field0_0x0);
    charge_vig_loader1();
    start_cd(0, 7);
    SetDispMask(1);
    SYNCHRO_LOOP(prg_vig_loader1);
    while (track_is_finished() == false) {};
    DO_FADE_OUT();
}
#endif

/* 7B244 8019FA44 -O2 -msoft-float */
u8 PS1_OldLoadingScreen(void)
{
    DO_FADE();
    DISPLAY_FOND3();
    display_text(s_loading_8012c368, 160, 215, 2, 1);
    return fade == 0;
}

// NOTE: Function name casing is unknown since the name comes from always lowercase hook names in the 30th anniversary edition
/* 7B294 8019FA94 -O2 -msoft-float */
void curtainroll(u8 param_1)
{
    RECT fb_rect;

    __builtin_memcpy(&fb_rect, &D_801CF0E8, sizeof(D_801CF0E8));
    StoreImage(&fb_rect, D_801C438C[num_world - 1]);
    MoveImage(&PS1_CurrentDisplay->field0_0x0.disp, fb_rect.x, fb_rect.y);
    DrawSync(0);
    if (param_1)
    {
        PS1_InitCurtainRoll(0);
        SYNCHRO_LOOP(PS1_DoCurtainRollRToL);
    }
    LoadImage(&fb_rect, D_801C438C[num_world - 1]);
    DrawSync(0);
}

/* 7B384 8019FB84 -O2 -msoft-float */
void START_WORLD_VIGNET(void)
{
    u8 *unk_1;
    RECT fb_rect_1;
    RECT fb_rect_2;

    unk_1 = D_801F4380;
    __builtin_memcpy(&fb_rect_1, &D_801CF0E8, sizeof(D_801CF0E8));
    D_801F4380 = ((u8 *) D_801C438C[num_world - 1] + 0x45000);
    charge_wld_vignette(num_world_choice);
    StoreImage(&fb_rect_1, D_801C438C[num_world - 1]);
    MoveImage(&PS1_CurrentDisplay->field0_0x0.disp, fb_rect_1.x, fb_rect_1.y);
    DrawSync(0);
    PS1_InitCurtainRoll(0);
    SYNCHRO_LOOP(PS1_DoCurtainRollRToL);
    ClearImage(&fb_rect_1, 0, 0, 0);
    fb_rect_2.x = (SCREEN_WIDTH - plan2_width) / 2 + 704;
    fb_rect_2.y = (SCREEN_HEIGHT - plan2_height) / 2;
    fb_rect_2.w = plan2_width;
    fb_rect_2.h = plan2_height;
    LoadImage(&fb_rect_2, (u32 *) D_801F4380);
    DrawSync(0);
    PS1_InitCurtainRoll(100);
    SYNCHRO_LOOP(PS1_DoCurtainRollLToR);
    LoadImage(&fb_rect_1, D_801C438C[num_world - 1]);
    DrawSync(0);
    D_801F4380 = unk_1;
}

/* 7B540 8019FD40 -O2 -msoft-float */
void FUN_8019fd40(void)
{
    u8 unk_1[8];

    PadInit(0);
    ResetGraph(0);
    SetGraphDebug(0);
    SetDispMask(false);
    clearbothdrawenv();
    SsInit();
    PS1_InitializeCard(0);
    CdInit();
    InitSnd();
}

/* 7B5A0 8019FDA0 -O2 -msoft-float */
u8 FUN_8019fda0(void)
{
    DO_FADE();
    DISPLAY_FOND3();
    return fade == 0;
}

/* 7B5D0 8019FDD0 -O2 -msoft-float */
void FUN_8019fdd0(void)
{
    RECT fb_rect;
    Display *new_disp;

    __builtin_memcpy(&fb_rect, &D_801CF0E0, sizeof(D_801CF0E0));
    ClearImage(&fb_rect, 0, 0, 0);
    DISPLAY_FOND3();

    new_disp = &PS1_Displays[0];
    if (PS1_CurrentDisplay == &PS1_Displays[0])
        new_disp = &PS1_Displays[1];
    PS1_CurrentDisplay = new_disp;

    DISPLAY_FOND3();
    PutDispEnv(&PS1_CurrentDisplay->field0_0x0);
    PutDrawEnv(&PS1_CurrentDisplay->drawing_environment);
    InitDB(PS1_Displays);
    InitDB(&PS1_Displays[1]);
}

/* 7B68C 8019FE8C -O2 -msoft-float */
void GAME_INIT2(void)
{
    PS1_DebugMode = false;
    PS1_InitSounds();
    PS1_InitMusic();
    InitGeom();
    D_801F3EA0 = false;
}

/* 7B6CC 8019FECC -O2 -msoft-float */
void PS1_SetLevelto_4_1(void)
{
    num_world = 4;
    num_level = 1;
}

/* 7B6EC 8019FEEC -O2 -msoft-float */
void FIRST_INIT(void)
{
    FUN_8019fd40();
    D_801F4380 = (void *) 0x8005866C;
    PS1_Init_ImgLdrVdoTrk_Files();
    GAME_INIT2();
    loader();
    if (PS1_InitPAD())
    {
        StartPAD();
        ChangeClearPAD(0);
    }
    SetDefDrawEnv(&PS1_Displays[0].drawing_environment, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDispEnv(&PS1_Displays[0].field0_0x0, 0, 256, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDrawEnv(&PS1_Displays[1].drawing_environment, 0, 256, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDispEnv(&PS1_Displays[1].field0_0x0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    PS1_Displays[1].field0_0x0.pad0 = 0;
    PS1_Displays[0].field0_0x0.pad0 = 0;
    PS1_LoadImgSplash();
    SetDispMask(false);
    PutDispEnv(&PS1_CurrentDisplay->field0_0x0);
    clearbothdrawenv();
    SetDispMask(true);
    PS1_PlayVideo(VIDEO_PRES);
    FUN_8019fdd0();
    FUN_8019dd74();
    init_spr();
    DO_GROS_RAYMAN();
    PS1_SetLevelto_4_1();
    InitFix();
    no_fnd = -1;
    curtainroll(true);
}
