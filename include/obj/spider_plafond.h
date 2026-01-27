#ifndef SPIDER_PLAFOND_H
#define SPIDER_PLAFOND_H

#include "common.h"
#include "unknown/48528.h"

/**/
extern u8 position_ray;

void get_spi_zdc(Obj *param_1, s16 *param_2, s16 *param_3, s16 *param_4, s16 *param_5);
void DO_SPIDER_PLAFOND(Obj *spipl_obj);
void DO_SPIDER_PLAFOND_POING_COLLISION(Obj *obj);
void SPIDER_PLAFOND_REACT(Obj *obj);
void DO_DARD_PLAFOND_ALWAYS(Obj *obj);

#endif