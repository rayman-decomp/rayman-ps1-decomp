#ifndef ETAT_H
#define ETAT_H

#include "common.h"
#include "obj_update.h"

s32 vblToEOA(Obj *obj, u8 factor);
void GET_ANIM_POS(Obj *obj, s16 *x, s16 *y, s16 *w, s16 *h);
u8 PS1_GetObjPan(Obj *obj);
u8 PS1_GetObjVolume(Obj *obj);
void add_actobj(s16 obj_id);
s16 BTYP(s32 x, s32 y); /* see on_block_chdir() */
void set_sub_etat(Obj *obj, u8 sub_etat);
void set_main_etat(Obj *obj, u8 main_etat);
void set_main_and_sub_etat(Obj *obj, u8 main_etat, u8 sub_etat);

#endif