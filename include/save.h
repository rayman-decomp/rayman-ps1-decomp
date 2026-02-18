#ifndef SAVE_H
#define SAVE_H

#include "common.h"
#include "common/obj.h"
#include "common/rayevts.h"
#include "common/level.h"
#include "common/world_map.h"
#include "MEMORY.H"
#include "moteur_update.h"
#include "ray/ray_5D190.h"
#include "gendoor.h"
#include "snow.h"

typedef struct SaveState
{
    u32 triggered_objects[8];
    s16 nb_floc[8];
    s16 vent_x;
    s16 vent_y;
    s16 x_map;
    s16 y_map;
    s16 time;
    s16 ray_x_pos;
    s16 ray_y_pos;
    s16 ray_screen_x;
    s16 ray_screen_y;
    s16 ray_flip_x;
    s16 save_obj_id;
    s16 save_obj_x_pos;
    s16 save_obj_y_pos;
    u8 link_init[256];
    u8 save_obj_detect_zone_flag;
    u8 field18_0x14b;
    BlockType ray_btypes[5];
    u8 ray_anim_index;
    u8 ray_anim_frame;
    u8 ray_main_etat;
    u8 ray_sub_etat;
    u8 poing_sub_etat;
    u8 rayevts_0;
    u8 rayevts_1;
    u8 rayevts_2;
    u8 dead_time;
    u8 has_saved;
    u8 num_wiz;
} SaveState;

typedef struct WorldInfoSave
{
    u8 is_unlocked : 1;
    u8 is_unlocking : 1;
    u8 nb_cages : 3;
} WorldInfoSave;

/* .data */
extern u8 nb_levels_in_world[8];

/**/
extern SaveState save1;
extern SaveState save2;
extern u8 save_zone[2688];
extern WorldInfoSave wi_save_zone[24];

void initGameSave(void);
void doneGameSave(void);
void saveGameState(Obj *obj, SaveState *state);
void restoreGameState(SaveState *save);
void DO_PHOTOGRAPHE_CMD(void);
s16 get_offset_in_save_zone(s16 event_index);
void reset_save_zone_level(void);
void take_bonus(s16 event_index);
u8 bonus_taken(s16 event_index);
void PS1_WriteWiSaveZone(void);
void PS1_LoadWiSaveZone(void);

#endif