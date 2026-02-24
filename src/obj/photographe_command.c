#include "obj/photographe_command.h"

/* 4DF04 80172704 -O2 -msoft-float */
void PS1_PhotographerCommand(Obj *obj)
{
    u8 anim_spd;

    DO_ONE_CMD(obj);
    anim_spd = (obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf);

    if (obj->anim_index == 4 && obj->anim_frame == 10 && horloge[anim_spd] == 0)
        PlaySnd(40, obj->id);
}
