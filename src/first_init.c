#include "first_init.h"

#ifdef PLATFORM_PSYZ
#include <libapi.h>
#endif

const u8 s_loading_8012c368[] = "/loading.../";

/* 7B048 8019F848 -O2 -msoft-float */
s16 FUN_8019f848(void)
{
    D_801CF438++;
    FUN_801809fc();
    return (D_801CF438 <= 60) ^ 1;
}

/* 7B08C 8019F88C -O2 -msoft-float */
s16 FUN_8019f88c(void)
{
    D_801CF440++;
    FUN_801809fc();
    return (D_801CF440 <= 60) ^ 1;
}

/* 7B0D0 8019F8D0 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/first_init", FUN_8019f8d0);
#else
void FUN_8019f8d0(void)
{
    s32 unk_1; /* TODO: remove */
    RECT fb_rect = D_801CF0E0;
    
    ResetGraph(0);
    SetGraphDebug(0);
    SetDispMask(0);
    PS1_ClearScreen();
    SetDefDispEnv(&PS1_Displays[0].display_environment, 0, 0, 640, 480);
    SetDefDrawEnv(&PS1_Displays[0].drawing_environment, 0, 0, 640, 480);
    SetDefDispEnv(&PS1_Displays[1].display_environment, 0, 0, 640, 480);
    SetDefDrawEnv(&PS1_Displays[1].drawing_environment, 0, 0, 640, 480);
    unk_1 = 1;
    PS1_Displays[unk_1].display_environment.pad0 = 0;
    PS1_Displays[0].display_environment.pad0 = 0;
    PS1_Displays[1].display_environment.isinter = true;
    PS1_Displays[0].display_environment.isinter = true;
    PS1_InitDisplay(&PS1_Displays[0]);
    PS1_InitDisplay(&PS1_Displays[1]);
    ClearImage(&fb_rect, 0, 0, 0);
    PutDispEnv(&PS1_CurrentDisplay->display_environment);
    LOAD_SCREEN();
    playLevelMusic(0, 7);
    SetDispMask(1);
    SYNCHRO_LOOP(FUN_8019f848);
    // This waits for the CDReady callback to be called
    while (FUN_80131db8() == false) {};
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

#ifdef PLATFORM_PSYZ
#define POINTER_CAST (u_long*)
#else
#define POINTER_CAST
#endif
/* 7B294 8019FA94 -O2 -msoft-float */
void FUN_8019fa94(u8 param_1)
{
    RECT fb_rect;

    __builtin_memcpy(&fb_rect, &D_801CF0E8, sizeof(D_801CF0E8));
    StoreImage(&fb_rect, POINTER_CAST FILE_HEAP(D_801C438C[num_world - 1]));
    MoveImage(&PS1_CurrentDisplay->display_environment.disp, fb_rect.x, fb_rect.y);
    DrawSync(0);
    if (param_1)
    {
        FUN_8012d2b0(0);
        SYNCHRO_LOOP(PS1_RollUpRToL);
    }
    LoadImage(&fb_rect, POINTER_CAST FILE_HEAP(D_801C438C[num_world - 1]));
    DrawSync(0);
}

/* 7B384 8019FB84 -O2 -msoft-float */
void FUN_8019fb84(void)
{
    u8 *unk_1;
    RECT fb_rect_1;
    RECT fb_rect_2;

    unk_1 = D_801F4380;
    __builtin_memcpy(&fb_rect_1, &D_801CF0E8, sizeof(D_801CF0E8));
    D_801F4380 = ((u8 *) FILE_HEAP(D_801C438C[num_world - 1]) + 0x45000);
    FUN_8019df1c(num_world_choice);
    StoreImage(&fb_rect_1, POINTER_CAST FILE_HEAP((D_801C438C[num_world - 1])));
    MoveImage(&PS1_CurrentDisplay->display_environment.disp, fb_rect_1.x, fb_rect_1.y);
    DrawSync(0);
    FUN_8012d2b0(0);
    SYNCHRO_LOOP(PS1_RollUpRToL);
    ClearImage(&fb_rect_1, 0, 0, 0);
    fb_rect_2.x = (SCREEN_WIDTH - plan2_width) / 2 + 704;
    fb_rect_2.y = (SCREEN_HEIGHT - plan2_height) / 2;
    fb_rect_2.w = plan2_width;
    fb_rect_2.h = plan2_height;
    LoadImage(&fb_rect_2, POINTER_CAST D_801F4380);
    DrawSync(0);
    FUN_8012d2b0(100);
    SYNCHRO_LOOP(PS1_RollUpLToR);
    LoadImage(&fb_rect_1, POINTER_CAST (FILE_HEAP(D_801C438C[num_world - 1])));
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
    PS1_ClearScreen();
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
    PutDispEnv(&PS1_CurrentDisplay->display_environment);
    PutDrawEnv(&PS1_CurrentDisplay->drawing_environment);
    PS1_InitDisplay(PS1_Displays);
    PS1_InitDisplay(&PS1_Displays[1]);
}

/* 7B68C 8019FE8C -O2 -msoft-float */
void FUN_8019fe8c(void)
{
    PS1_DebugMode = false;
    FUN_80166018();
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
    D_801F4380 = (void *) FILE_HEAP(0x8005866C);
    PS1_Init_ImgLdrVdoTrk_Files();
    FUN_8019fe8c();
    FUN_8019f8d0();
    if (PS1_InitPAD())
    {
        StartPAD();
        ChangeClearPAD(0);
    }
    SetDefDrawEnv(&PS1_Displays[0].drawing_environment, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDispEnv(&PS1_Displays[0].display_environment, 0, 256, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDrawEnv(&PS1_Displays[1].drawing_environment, 0, 256, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDispEnv(&PS1_Displays[1].display_environment, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    PS1_Displays[1].display_environment.pad0 = 0;
    PS1_Displays[0].display_environment.pad0 = 0;
    PS1_LoadImgSplash();
    SetDispMask(false);
    PutDispEnv(&PS1_CurrentDisplay->display_environment);
    PS1_ClearScreen();
    SetDispMask(true);
    PS1_PlayVideo(VIDEO_PRES);
    FUN_8019fdd0();
    FUN_8019dd74();
    PS1_LoadPts();
    FUN_8012ecf0();
    PS1_SetLevelto_4_1();
    PS1_LoadAllFixData();
    no_fnd = -1;
    FUN_8019fa94(true);
}
