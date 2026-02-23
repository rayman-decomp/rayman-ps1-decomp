#include "unknown/AACC.h"

void PS1_EmptyFunction1(void) {}

/* AAD4 8012F2D4 -O2 -msoft-float */
void PouvoirsParMap(void)
{
    RaymanEvents sp0 = D_801CEE84;
    RaymanEvents sp8 = D_801CEE88;
    RaymanEvents sp10 = D_801CEE8C;
    RaymanEvents sp18 = D_801CEE90;
    RaymanEvents sp20 = D_801CEE94;
    RaymanEvents sp28 = PS1_DefaultRayEvts;

    switch (num_world)
    {
    case 1:
        if (num_level <= 3)
            RayEvts = sp0;
        if (num_level >= 4 && num_level <= 8)
            RayEvts = sp8;
        if (num_level >= 9 && num_level <= 15)
            RayEvts = sp10;
        if (num_level >= 16)
            RayEvts = sp18;
        break;
    case 2:
        if (num_level <= 11)
            RayEvts = sp18;
        if (num_level >= 12)
            RayEvts = sp20;
        break;
    case 3:
        if (num_level <= 11)
            RayEvts = sp20;
        if (num_level >= 12)
            RayEvts = sp28;
        break;
    default:
        RayEvts = sp28;
        break;
    }
}

/* AD40 8012F540 -O2 -msoft-float */
void PS1_ResetSaveZone(void)
{
    s32 i;
    s32 len = LEN(save_zone);

    for (i = 0; i < len; i++)
        save_zone[i] = 0;
}

/* AD70 8012F570 -O2 -msoft-float */
void PS1_IncrementUnusedValue(void)
{
    D_801CEEA0++;
}
