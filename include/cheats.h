#ifndef CHEATS_H
#define CHEATS_H

#include "common.h"
#include "common/rayevts.h"
#include "common/fin_du_jeu.h"
#include "main_moteur.h"
#include "ray/ray_30A64.h"
#include "ray/ray_5D190.h"

/* .data */
extern s16 D_801CEFC8;

/* .data */
extern u8 D_801CF0D8;
extern u8 PS1_PictureInPicture;
extern u8 PS1_15fps;

/**/
extern u8 PS1_DebugMode;

void handle_pad(void);

#endif