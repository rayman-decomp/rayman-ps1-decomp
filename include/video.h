#ifndef VIDEO_H
#define VIDEO_H

#include "common.h"
#include "LIBCD.H"
#include "psyq_3_0_missing/LIBCD.H"
#include "LIBPRESS.H"
#include "psyq_3_0_missing/LIBPRESS.H"
#include "draw/fade.h"

typedef s16 Video;
#define VIDEO_NONE 0
#define VIDEO_PRES 1
#define VIDEO_INTRO 2
#define VIDEO_DEMO 3
#define VIDEO_MAP_INTRO 4 /* Same as the normal intro, but only plays the end */
#define VIDEO_WIN 5

typedef u8 VideoPlayState;
#define VIDEOST_NOT_PLAYING 0
#define VIDEOST_PLAYING 1
#define VIDEOST_SKIPPED 2

/* based on videosetup, RayCarrot found volatiles */
typedef struct VideoState
{
    u32 *encoded_frame_buffers[2];
    u32 *decoded_frame;
    RECT frame_rect;
    vu8 has_swapped_display;
    vu8 vsync_counter;
    u8 current_encode_buffer_index;
    /*u8 field7_0x17;*/
    vs16 frame_count;
} VideoState;

/* .data */
extern u32 *D_801CEEDC;
extern u32 *D_801CEEE0;
extern u32 *D_801CEEE4;
extern u32 *D_801CEEE8;

/* .data */
extern VideoState PS1_CurrentVideoState;

/**/
extern VideoPlayState PS1_VideoPlayState;
extern s16 PS1_VideoLength;

void PS1_PlayVideo(Video video);
void videonext(void);
void PS1_PlayVideoFile(Video video);
void videosetup(VideoState *param_1);
void PS1_LoadVideoFile(CdlLOC *lba, u32 param_2);
void PS1_ReadVideoFile(u32 *param_1, Video video); /* param_1 name sugg. DecDCTvlc() runlevel? (LIBOVR section 7-8) */
void FUN_80132f8c(void);
void FUN_80133010(void);

#endif