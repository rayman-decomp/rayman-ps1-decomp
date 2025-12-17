#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"
#ifdef PLATFORM_PSYZ
#include <libgpu.h>
#else
#include "LIBGPU.H"
#endif

typedef struct DRENVAndTile
{
    DR_ENV drawing_environment;
    TILE tile;
} DRENVAndTile;

typedef struct Display
{
    DISPENV display_environment;
    DRAWENV drawing_environment;
    DR_ENV map_drawing_environment_primitives[25];
    u8 field_0x6b0_0x7d7[296]; /* unused? */
    u32 map_ordering_tables[6]; /* TODO: size correct? */
    OT_TYPE ordering_table[11]; /* TODO: not sure this is correct, see compiler warnings for synchro_loop.c and main_moteur.c */
    SPRT_16 tiles[360];
    SPRT_8 field_0x1e9c_0x321b[312];
    TILE_1 tile1s[240];
    SPRT sprites[50];
    POLY_FT4 polygons[200];
    TILE field_0x6084_0x6093;
    POLY_G4 field_0x6094_0x60b7;
    u8 field_0x60b8_0x60bb[4];
    DRENVAndTile field_0x60bc_0x660b[17];
    DR_ENV unk_dr_env;
    u8 field_0x664c_0x668b[64]; /* unused? */
    TILE fond_box_tiles[4];
    TILE fond_box_tile;
    TILE field_0x66dc_0x673b[6];
    POLY_F4 unk_poly_f4s[16];
    POLY_G4 unk_poly_g4s[16];
    POLY_G3 unk_poly_g3s[16];
} Display;

/* .data */
extern Display *PS1_CurrentDisplay;

/**/
extern Display PS1_Displays[2];
extern s16 D_801E4BE0; /* used as index for map_drawing_environment_primitives (0x70) */

#endif