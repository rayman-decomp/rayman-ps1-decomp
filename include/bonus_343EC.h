#ifndef BONUS_343EC_H
#define BONUS_343EC_H

#include "common.h"
#include "common/ray.h"
#include "common/world_map.h"
#ifdef PLATFORM_PSYZ
#include <libgpu.h>
#else
#include "LIBGPU.H"
#include "STDIO.H"
#endif
#include "world_map_95CC.h"
#include "timers.h"
#include "draw/fade.h"
#include "nova.h"

/* .data */
extern Obj *PS1_BonusNovas[2];
extern Obj *PS1_BonusOneUps[2];

/* .data */
extern u8 PS1_TimeString[24];

s16 do_perfect_bonus(void); /* TODO: return type? PS1_DemoLoop is u8 still */

#endif