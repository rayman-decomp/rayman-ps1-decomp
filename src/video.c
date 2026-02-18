#include "video.h"

/* TODO: DecDCTout constant 1664? */

#ifdef BSS_DEFS
VideoPlayState PS1_VideoPlayState;
s16 PS1_VideoLength;
#endif

/* E098 80132898 -O2 -msoft-float */
void PS1_PlayVideo(Video video)
{
    Display *new_disp;

    switch (video)
    {
    case VIDEO_PRES:
    case VIDEO_INTRO:
    case VIDEO_MAP_INTRO:
        PS1_VideoLength = 1806;
        break;
    case VIDEO_DEMO:
        PS1_VideoLength = 144;
        break;
    case VIDEO_WIN:
        PS1_VideoLength = 244;
        break;
    }
    PS1_LoadVideoTables();
    PS1_VideoPlayState = VIDEO_PRES;
    SsSetSerialVol(SS_SERIAL_A, 0, 0);
    PS1_PlayVideoFile(video);
    new_disp = &PS1_Displays[0];
    if (PS1_CurrentDisplay == &PS1_Displays[0])
        new_disp = &PS1_Displays[1];
    PS1_CurrentDisplay = new_disp;
    if (video == VIDEO_WIN)
        DO_FADE_OUT();
    D_801CF0CD = false;
}

// NOTE: Function name casing is unknown since the name comes from always lowercase hook names in the 30th anniversary edition
/* E180 80132980 -O2 -msoft-float */
void videonext(void)
{
    LoadImage(&PS1_CurrentVideoState.frame_rect, (u32 *) PS1_CurrentVideoState.decoded_frame);
    DrawSync(0);
    PS1_CurrentVideoState.frame_rect.x += 16;
    if (PS1_CurrentVideoState.frame_rect.x < SCREEN_WIDTH)
        DecDCTout(PS1_CurrentVideoState.decoded_frame, 1664);
    else
    {
        if (PS1_CurrentDisplay == &PS1_Displays[0])
        {
            PS1_CurrentDisplay = &PS1_Displays[1];
            PS1_CurrentVideoState.frame_rect.x = 0;
            PS1_CurrentVideoState.frame_rect.y = 276;
        }
        else
        {
            PS1_CurrentDisplay = &PS1_Displays[0];
            PS1_CurrentVideoState.frame_rect.x = 0;
            PS1_CurrentVideoState.frame_rect.y = 20;
        }

        PS1_CurrentVideoState.has_swapped_display = true;
    }
}

/* E244 80132A44 -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/video", PS1_PlayVideoFile);
#else
/* score of ??? */
void PS1_PlayVideoFile(s16 video)
{
    short sVar1;
    int iVar2;
    u32 *pbVar3;
    u8 temp_s3;
    u16 frame_count;

    ResetCallback();
    DecDCTReset(0);
    temp_s3 = 1;
    if (video == 4)
    {
        PS1_LoadVideoFile(&PS1_VdoFiles[video].file.pos, 0x6b9);
    }
    else
    {
        PS1_LoadVideoFile(&PS1_VdoFiles[video].file.pos, 1);
    }
    videosetup(&PS1_CurrentVideoState);
    DecDCToutCallback(videonext);
    PutDispEnv(&PS1_CurrentDisplay->field0_0x0);
    PS1_ReadVideoFile(PS1_CurrentVideoState.encoded_frame_buffers[PS1_CurrentVideoState.current_encode_buffer_index], video);
    PS1_CurrentVideoState.vsync_counter = 0;
    while ((PS1_VideoPlayState < 2) && ((u16) PS1_CurrentVideoState.frame_count < PS1_VideoLength))
    {
        PS1_CurrentVideoState.has_swapped_display = 0;
        if (temp_s3)
        {
            readinput();
        }
        DecDCTout((u32 *) PS1_CurrentVideoState.decoded_frame, 1664);
        DecDCTin(PS1_CurrentVideoState.encoded_frame_buffers[PS1_CurrentVideoState.current_encode_buffer_index], 0);

        if (PS1_CurrentVideoState.current_encode_buffer_index)
        {
            PS1_CurrentVideoState.current_encode_buffer_index = 0;
            pbVar3 = PS1_CurrentVideoState.encoded_frame_buffers[0];
        }
        else
        {
            PS1_CurrentVideoState.current_encode_buffer_index = 1;
            pbVar3 = PS1_CurrentVideoState.encoded_frame_buffers[1];
        }
        PS1_ReadVideoFile(pbVar3, video);
        if ((temp_s3) &&
            ((sVar1 = but1pressed(0), sVar1 != 0 || (iVar2 = butstart(0), iVar2 != 0))))
        {
            PS1_VideoPlayState = 2;
        }
        while (PS1_CurrentVideoState.has_swapped_display == 0) {};
        while (PS1_CurrentVideoState.vsync_counter != 0) {};
    }
    SsSetSerialVol('\0', 0, 0);
    CdControlB('\t', (u_char *) 0x0, (u_char *) 0x0);
    PS1_CurrentVideoState.has_swapped_display = 0;
    DecDCTout((u32 *) PS1_CurrentVideoState.decoded_frame, 1664);
    DecDCTin((u32 *) (&PS1_CurrentVideoState.encoded_frame_buffers[0])[PS1_CurrentVideoState.current_encode_buffer_index], 0);
    do
    {
    } while (PS1_CurrentVideoState.has_swapped_display == 0);
    do
    {
    } while (PS1_CurrentVideoState.vsync_counter != 0);
    DecDCTinCallback(0);
    DecDCToutCallback(0);
    CdDataCallback(0);
    CdReadyCallback((void *) 0x0);
    VSyncCallback((void *) 0x0);
    iVar2 = 1;
    do
    {
        VSync(0);
        iVar2 = iVar2 + 1;
    } while (iVar2 < 4);

    while (temp_s3 != 0 && (((s16) but1pressed(0)) || (butstart(0))))
    {
        readinput();
    }
    return;
}
#endif

// NOTE: Function name casing is unknown since the name comes from always lowercase hook names in the 30th anniversary edition
/* E574 80132D74 -O2 -msoft-float */
void videosetup(VideoState *param_1)
{
    param_1->current_encode_buffer_index = 0;
    param_1->frame_count = 1;
    param_1->frame_rect.w = 16;
    param_1->frame_rect.h = 200;
    param_1->encoded_frame_buffers[0] = D_801CEEDC;
    param_1->encoded_frame_buffers[1] = D_801CEEE0;
    param_1->decoded_frame = D_801CEEE8;
    if (PS1_CurrentDisplay == PS1_Displays)
        param_1->frame_rect.y = 20;
    else
        param_1->frame_rect.y = 276;
    param_1->frame_rect.x = 0;
    VSyncCallback(FUN_80132f8c);
}

/* E604 80132E04 -O2 -msoft-float */
void PS1_LoadVideoFile(CdlLOC *lba, u32 param_2)
{
    CdlLOC unk_1;

    CdIntToPos(CdPosToInt(lba) + (param_2 - 5) * 10, &unk_1);
    StSetRing(D_801CEEE4, 32);
    StSetStream(0, param_2, 0x0FFFFFFF, null, null);
    while (!CdControl(CdlSeekL, &unk_1.minute, null)) {};
    CdSync(1, null);
    while (!CdRead2(CdlModeStream | CdlModeSpeed | CdlModeRT)) {};
}

/* E6A0 80132EA0 -O2 -msoft-float */
void PS1_ReadVideoFile(u32 *param_1, Video video)
{
    u32 *user_data; /* also StHEADER? */
    StHEADER *header;
    u8 vol;

    while (StGetNext(&user_data, (u32 **) &header)) {}
    PS1_CurrentVideoState.frame_count = header->frameCount;

    if (video == VIDEO_PRES)
        SsSetSerialVol(SS_SERIAL_A, 80, 80);
    else
    {
        vol = options_jeu.Music * 127 / 20;
        SsSetSerialVol(SS_SERIAL_A, vol, vol);
    }

    DecDCTvlc(user_data, param_1);
    StFreeRing(user_data);
}

/* E78C 80132F8C -O2 -msoft-float */
void FUN_80132f8c(void)
{
    PS1_CurrentVideoState.vsync_counter = PS1_CurrentVideoState.vsync_counter + 1;
    /*__asm__("lbu     $v0,0($v1)\nnop");*/
    PS1_CurrentVideoState.vsync_counter;
    if ((PS1_CurrentVideoState.vsync_counter > 3) && (PS1_CurrentVideoState.has_swapped_display != 0)) {
        PS1_CurrentVideoState.vsync_counter = 0;
        PutDrawEnv(&PS1_CurrentDisplay->drawing_environment);
        PutDispEnv(&PS1_CurrentDisplay->field0_0x0);
    }
}

void FUN_80133010(void) {}
