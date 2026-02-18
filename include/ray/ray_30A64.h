#ifndef RAY_30A64_H
#define RAY_30A64_H

#include "common.h"
#include "common/mapdata.h"
#include "common/ray.h"
#include "collision/collision.h"

typedef struct StatusBar
{
    s16 num_lives;
    u8 lives_digits[2];
    u8 hp_sprites[2];
    u8 num_wiz;
    u8 wiz_digits[2];
    u8 max_hp;
} StatusBar;

/**/
extern StatusBar status_bar;
extern s16 sbar_obj_id;
extern u8 nb_wiz;
extern u8 nb_wiz_collected;
extern s16 special_ray_mov_win_x_left; /* TODO: goes in this file? */
extern s16 special_ray_mov_win_x_right;

s16 RayCoince(s16 dir);
void move_up_ray(void);
void move_down_ray(void);
void recale_ray_pos(void);
void RAY_TO_THE_RIGHT(void);
void RAY_TO_THE_LEFT(void);
void make_ray_slide(void);
void TEST_FIN_FOLLOW(void);
void RAY_FOLLOW(void);
void DO_FIXE(void);

#endif