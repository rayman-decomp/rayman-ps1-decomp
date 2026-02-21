#include "unknown/29A18.h"

/* 29A18 8014E218 -O2 -msoft-float */
void fades(void)
{
    if (map_time == 0)
        INIT_FADE_IN();

    if (dead_time == 32)
        INIT_FADE_OUT();

    if (fade != 0)
        DO_FADE();
}

/* 29A7C 8014E27C -O2 -msoft-float */
void AVOID_SOME_BUGS(void)
{
    if (ray_old_main_etat != 2 && ray.main_etat == 2)
        ray.field24_0x3e = 0;

    if (
        ABS(PS1_StartMoteurRayX - ray.x_pos) > 48 ||
        ABS(PS1_StartMoteurRayY - ray.y_pos) > 48
    )
    {
        ray.x_pos = PS1_StartMoteurRayX;
        ray.y_pos = PS1_StartMoteurRayY;
        calc_obj_pos_map(&ray);
    }
}
