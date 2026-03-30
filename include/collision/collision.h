#ifndef COLLISION_H
#define COLLISION_H

#include "common.h"
#include "common/ray.h"
#include "common/level.h"
#include "common/rayevts.h"
#include "common/mapdata.h"
#include "obj_init_kill.h"
#include "bonus_35FB4.h"
#include "ray/angle_rayman.h"
#include "obj/mus_wait.h"
#include "obj/joe_command.h"
#include "obj/blacktoon1.h"
#include "obj/pi_boum.h"
#include "obj/ufo_idc.h"
#include "obj/hyb_bbf2.h"
#include "obj/dark2_pink_fly.h"

typedef struct ZDC
{
    s16 x_pos;
    s16 y_pos;
    u8 width;
    u8 height;
    u8 flags;
    u8 sprite;
} ZDC;

/* .data */
extern ZDC zdc_tab[512];
extern u16 type_zdc[256];

/* .data */
extern s16 bagDy[20];
extern s16 bagW[20];
extern s16 bagH[20];

/**/
extern s16 ray_zdc_x;
extern s16 ray_zdc_y;
extern s16 ray_zdc_w;
extern s16 ray_zdc_h;
extern u8 in_air_because_hit;
extern s16 ZDCPTR;
extern s16 ray_speed_inv;
extern u8 life_becoz_wiz;

void PS1_SetZDC(s16 x, s16 y, u8 w, u8 h, u8 flags, u8 sprite);
void PS1_SetTypeZDC(ObjType type, u16 param_2, s32 param_3);
u16 get_nb_zdc(Obj *obj);
u16 get_zdc_index(Obj *obj);
ZDC *get_zdc(Obj *obj, s16 param_2);
s16 get_ZDCPTR(void);
s16 in_coll_sprite_list(Obj *obj, s16 param_2);
s32 box_inter_v_line(s16 param_1, s16 param_2, s16 param_3, s16 param_4, s16 param_5, s16 param_6, s16 param_7);
s32 box_inter_h_line(s16 param_1, s16 param_2, s16 param_3, s16 param_4, s16 param_5, s16 param_6, s16 param_7);
s16 inter_box(s32 x_1, s32 y_1, s32 w_1, s32 h_1, s16 x_2, s16 y_2, s32 w_2, s32 h_2); /* BOX_IN_COLL_ZONES forces s16 return? */
void GET_OBJ_ZDC(Obj *obj, s16 *out_x, s16 *out_y, s16 *out_w, s16 *out_h);
s16 GET_SPRITE_ZDC(Obj *obj, s16 index, s16 *out_x, s16 *out_y, s16 *out_w, s16 *out_h);
s32 BOX_HIT_SPECIAL_ZDC(s16 in_x, s16 in_y, s16 in_w, s16 in_h, Obj *obj);
s32 BOX_IN_COLL_ZONES(s16 obj_type, s16 in_x, s16 in_y, s16 in_w, s16 in_h, Obj *obj);
s32 COLL_BOX_SPRITE(s16 in_x, s16 in_y, s16 in_w, s16 in_h, Obj *obj); /* return can be u32/s32? */
s16 CHECK_BOX_COLLISION(s16 obj_type, s16 x, s16 y, s16 w, s16 h, Obj *obj);
s16 possible_sprite(Obj *obj, s16 index);
s16 setToleranceDist(s16 in_x, s16 in_w, s16 in_y);
void SET_RAY_DIST_MULTISPR_CANTCHANGE(Obj *obj);
void SET_RAY_DIST_PI(Obj *obj);
void SET_RAY_DIST_BAG(Obj *obj);
void SET_RAY_DIST(Obj *obj);
void do_boum(void);
void DO_PNG_COLL_STONEMAN(Obj *obj);
void DO_PNG_COLL_STONEWOMAN(Obj *obj);
void DO_POING_COLLISION(void);
s32 COLL_BOX_ALL_SPRITES(s16 in_x, s16 in_y, s16 in_w, s16 in_h, Obj *obj);
s16 COLL_RAY_PIC(void);
void COLL_RAY_BLK_MORTEL(void);
void RAY_KO(void);
void RAY_HIT(u8 hurt, Obj *obj);
void standard_frontZone(Obj *obj, s16 *x, s16 *w);
void SET_DETECT_ZONE_FLAG(Obj *obj);
void goToRay(Obj *obj);
void unleashMonsterHost(Obj *obj);
void DO_COLL_RAY_CYMBALE(Obj *cym_obj);
void DoAudioStartRaymanCollision(Obj *obj);
void PS1_DoRaymanCollision(void);
void DO_COLLISIONS(void);
void DO_OBJ_COLLISIONS(Obj *in_obj, s32 offs);

#endif