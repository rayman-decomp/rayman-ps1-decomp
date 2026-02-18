#ifndef LOADING_DA64_H
#define LOADING_DA64_H

#include "common.h"
#include "common/obj.h"
#include "common/level.h"
#include "common/ray.h"
#include "common/mapdata.h"
#include "draw/draw_14FF4.h"
#include "obj_update.h"
#include "loading_794DC.h"
#include "draw/draw_hud.h"
#include "gendoor.h"
#include "draw/fond_10B3C.h"

typedef struct Font
{
    Sprite *sprites;
    u8 *img_buffer;
    s32 nb_sprites;
} Font;

typedef struct AllFixData
{
    Font alpha;
    Font alpha2;
    Obj objects[29];
} AllFixData;

/**/
extern AllFixData *PS1_AllFixData;
extern Font alpha;
extern Font alpha2;
extern s16 D_801D7A60;
extern s16 D_801F8188;
extern s16 D_801F84A8;
extern void *D_801F7E90; /* see loading_794DC, type? Obj * based on init_ini? */
extern s32 D_801D7868[2]; /* TODO: type? should be struct? first 4 bytes are pointer, next 4 bytes??? */

void load_unimap(MapData *data);
void FUN_80132304(u32 *data, u8 height);
void FUN_8013234c(u8 *param_1);
void init_ini(void);
void InitFix(void);
void InitLevel(void);
void swap_level(s16 param_1);

#endif