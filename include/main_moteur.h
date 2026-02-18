#ifndef MAIN_MOTEUR_H
#define MAIN_MOTEUR_H

#include "common.h"
#include "common/display.h"
#include "common/record.h"
#include "cheats.h"
#include "draw/draw_14FF4.h"
#include "input_ED20.h"
#include "obj/fee_3D76C.h"
#include "music.h"
#include "vignet.h"
#include "moteur_init_end.h"
#include "unknown/A3B0.h"

/* .data */
extern RECT PS1_MemoryUsageRects[2];

/* .data */
extern RECT *PTR_PS1_MemoryUsageRect_801cee70;
extern u8 PS1_MemoryUsageDisplayMode;

/* .data */
extern u8 in_pause;
extern u8 PS1_Ingame;
extern RaymanEvents D_801CEE84;
extern RaymanEvents D_801CEE88;
extern RaymanEvents D_801CEE8C;
extern RaymanEvents D_801CEE90;
extern RaymanEvents D_801CEE94;
extern RaymanEvents PS1_DefaultRayEvts; /* originally in include/main.h */
extern s16 D_801CEE9A;
extern s16 D_801CEE9C;
extern s16 PS1_CanPlayDeathMusic;
extern s16 D_801CEEA0;
extern u8 D_801CEEA2;

/**/
extern u8 gele;

void DO_GROS_MOTEUR(void);
void DO_MAIN_LOOP_SNY(void);

#endif