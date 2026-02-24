#ifndef GENDOOR_H
#define GENDOOR_H

#include "common.h"
#include "common/obj.h"
#include "common/level.h"
#include "obj/bateau_command.h"
#include "obj_init_kill.h"

/**/
extern u8 *link_init; /* not sure if this should be here? since non-gendoor things use links? */

void deactivate_ship_links(void);
s16 linkListHoldsAGendoor(Obj *obj);
s16 PS1_ObjectCanOnlyBeLinkedToAGendoor(Obj *obj);
s16 PS1_ObjectCanNotBeLinked(Obj *obj);
void correct_gendoor_link(void);
void suppressFromLinkList(Obj *obj);
void correct_link(void);

#endif