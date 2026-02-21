#ifndef UNK_48528_H
#define UNK_48528_H

#include "common.h"
#include "common/obj.h"
#include "input_ED20.h"

/* .data */
extern s16 PS1_VRAMDisplayXPos;
extern s16 PS1_VRAMDisplayYPos;

void debugw(void);
s16 test_allowed(Obj *obj, s16 unk_x, s16 unk_y);
void obj_jump(Obj *obj);
void DO_ONE_PINK_CMD(Obj *obj);
void FUN_8016d418(Obj *obj);

#endif