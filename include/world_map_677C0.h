#ifndef WORLD_MAP_677C0_H
#define WORLD_MAP_677C0_H

#include "common.h"
#include "common/ray.h"
#include "common/world_map.h"
#include "menu/menu_card_7C028.h"
#include "victoire.h"
#include "cam_scroll_29B5C.h"
#include "world_map_95CC.h"
#include "ray/ray_5D190.h"

/* TODO: does padding (between color, level_name) matter? it seems to work even without, but why? */
typedef struct WorldInfo
{
    s16 x_pos;
    s16 y_pos;
    u8 index_up;
    u8 index_down;
    u8 index_left;
    u8 index_right;
    u8 is_unlocked : 1;
    u8 has_drawn_path : 1;
    u8 is_unlocking : 1;
    u8 nb_cages;
    u8 world;
    u8 level;
    u8 color;
    u8 *level_name;
} WorldInfo;

/* .data */
extern WorldInfo t_world_info[24];
extern u8 *PTR_s_save_game_801c353c;
extern u8 *PTR_s_game_saved_801c3540;
extern u8 *PTR_s_no_save_available_801c3544;

/* .data */
extern u8 s___801cf0a4[4];
extern u8 s__801cf0a8[2];

/**/
extern Obj *mapobj;
extern Obj raylittle;
extern u8 chemin_percent;
extern u8 dir_on_wldmap;
extern s16 xmapinit;
extern s16 ymapinit;
extern s16 xwldmapsave;
extern s16 ywldmapsave;
extern u8 nouvelle_partie;
extern u8 dans_la_map_monde;
extern u8 Nb_total_cages;
extern u8 D_801F3EA0;

void CalcObjPosInWorldMap(Obj *obj);
void DoScrollInWorldMap(s16 h_speed, s16 v_speed);
void TEST_DISPLAY_PTS_WAY(s16 from, s16 to, s16 from_x, s16 from_y);
void DISPLAY_PTS_WAY(void);
void DISPLAY_PLAT_WAY(void);
void DO_MEDAILLONS(void);
void INIT_LEVEL_STAGE_NAME(void);
void INIT_WORLD_STAGE_NAME(void);
void INIT_STAGE_NAME(void);
void CHANGE_STAGE_NAMES(void);
void PS1_CardDisplayPassword(void);
void DO_STAGE_NAMES(void);
void INIT_WORLD_INFO(void);
void INIT_LITTLE_RAY(void);
void RESTORE_RAY(void);
void INIT_CHEMIN(void);
void RESPOND_TO_UP(void);
void RESPOND_TO_DOWN(void);
void RESPOND_TO_RIGHT(void);
void RESPOND_TO_LEFT(void);
void move_ray_map(void);
void DO_RAYMAN_IN_WLD_MAP(void);
void DO_CHEMIN(void);
void INIT_PASTILLES_SAUVE(void);
void PASTILLES_SAUVE_SAVED(s16 wld);
void FIN_WORLD_CHOICE(void);
void DETER_WORLD_AND_LEVEL(void);

#endif