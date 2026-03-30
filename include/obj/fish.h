#ifndef FISH_H
#define FISH_H

#include "common.h"
#include "common/obj.h"
#include "common/level.h"
#include "world_map_677C0.h"
#include "gendoor.h"

/**/
extern s16 PS1_SplashAlwaysObjects[10];
extern u8 PS1_SplashAlwaysObjectsCount;

void allocate_splash(Obj *base_obj);
u8 can_free_fish(Obj *fish_obj);
void DESACTIVE_FISH_COLLIS(Obj *fish_obj);
void DO_PYRANHA(Obj *in_obj);

#endif