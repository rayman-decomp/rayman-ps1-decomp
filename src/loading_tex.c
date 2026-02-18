#include "loading_tex.h"

#ifdef BSS_DEFS
s32 D_801E4D30;
s16 D_801E5930;
s16 D_801E63D0;
s32 D_801E4D28;
s16 D_801E5928;
s16 D_801E63C8;
s32 D_801E4D78;
s16 D_801E5A08;
s16 D_801E6410;
s16 D_801E5558;
s16 D_801E59B8;
u8 *D_801F4380;
void *D_801F8190;
u16 D_801F5440;
u16 D_801F55D8;
#endif

/* 14AD8 801392D8 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/loading_tex", Calcul_vram);
#else
/* not sure how to interpret any of the constants/vars/types */
void Calcul_vram(s32 param_1, s16 *param_2, s16 *param_3)
{
    s32 unk_1;

    unk_1 = param_1 >> 7;
    if (param_1 > 0x8DFFF)
        unk_1 += 0x40;

    if (unk_1 < 0x100)
        *param_2 = 0;
    else
        *param_2 = (unk_1 >> 9) + 1;

    if (*param_2 < 2)
        *param_3 = unk_1 & 0xFF;
    else
        *param_3 = (unk_1 >> 1) & 0xFF;
}
#endif

/* 14B30 80139330 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/loading_tex", Calcul_vram256);
#else
/* what is any of this? */
void Calcul_vram256(u32 param_1, s16 *param_2, s16 *param_3)
{
    s32 temp_v1_1;
    s32 temp_v1_2;
    s32 var_v0_3;
    s32 temp_a0;
    s32 test_1;

    test_1 = 0x100;
    temp_v1_1 = param_1 + 0xFFFF0000;
    if (temp_v1_1 < 0)
        *param_2 = param_1 >> 15;
    else
        *param_2 = (temp_v1_1 >> 16) + 2;

    if (temp_v1_1 < 0)
        *param_3 = (param_1 & 0x7FFF) >> 7;
    else
    {
        var_v0_3 = temp_v1_1 & 0xFFFF;
        if (var_v0_3 < 0)
            var_v0_3 += 0xFF;
        *param_3 = (u32) var_v0_3 >> 8;
    }

    if (*param_2 > 7)
    {
        temp_a0 = temp_v1_1 + 0xFFFA0000;
        temp_v1_2 = temp_a0 - (test_1 << 8);

        if (temp_v1_2 < 0)
            *param_2 = 8;
        else
            *param_2 = 9;

        if (temp_v1_2 < 0)
            *param_3 = (u32) temp_a0 >> 8;
        else
            *param_3 = (u32) temp_v1_2 >> 8;
    }
}
#endif

/* 14BC8 801393C8 -O2 -msoft-float */
void load_vram_ini(s32 param_1)
{
    s16 start_pos = 6;
    s16 end_pos = 0;

    Calcul_vram(param_1 + 0x50000, &start_pos, &end_pos);
    load_img(6, start_pos, 0, end_pos, 0, D_801F4380);
}

/* 14C24 80139424 -O2 -msoft-float */
void load_vram_ray(s32 length)
{
    D_801E4D30 = length + 0x400;
    Calcul_vram(D_801E4D30, &D_801E5930, &D_801E63D0);
    load_img(0, D_801E5930, 8, D_801E63D0, 0, D_801F4380);
}

/* 14C8C 8013948C -O2 -msoft-float */
void load_vram_wld(s32 param_1)
{
    D_801E4D28 = param_1 + D_801E4D30;
    Calcul_vram(D_801E4D28, &D_801E5928, &D_801E63C8);
    if (param_1 != 0)
        load_img(D_801E5930, D_801E5928, D_801E63D0, D_801E63C8, 0, D_801F4380);
}

/* 14D14 80139514 -O2 -msoft-float */
void load_vram_lvl(s32 param_1)
{
    D_801E4D78 = param_1 + D_801E4D28;
    Calcul_vram(D_801E4D78, &D_801E5A08, &D_801E6410);
    load_img(D_801E5928, D_801E5A08, D_801E63C8, D_801E6410, D_801C4468[num_world - 1], D_801F4380);
}

/* 14DA8 801395A8 -O2 -msoft-float */
void load_vram_lvl256(s32 param_1)
{
    D_801E4D78 = param_1 + D_801E4D28;
    Calcul_vram256(D_801E4D78, &D_801E5A08, &D_801E6410);
    load_img(D_801E5928, D_801E5A08, D_801E63C8, D_801E6410, 256, D_801F4380);
}

/* 14E24 80139624 -O2 -msoft-float */
void load_vram_let2(s32 param_1)
{
    s16 start_pos = 7;
    s16 end_pos = 80;

    Calcul_vram(param_1 + 0x65000, &start_pos, &end_pos);
    load_img(7, start_pos, 80, end_pos, 0, D_801F4380);
}

/* 14E88 80139688 -O2 -msoft-float */
void FUN_80139688(s32 tile_set_size)
{
    s32 unk_1 = 15;

    Calcul_vram(0xAC000 - tile_set_size, &D_801F5440, &D_801F55D8);
    if (D_801F5440 < 8)
    {
        D_801F5440 = 8;
        D_801F55D8 = 0;
    }
    else if (D_801F55D8 & unk_1)
    {
        D_801F55D8 = (D_801F55D8 + 15) & 65520;
        if (D_801F55D8 >= 256)
        {
            D_801F55D8 = 0;
            D_801F5440++;
        }

        if (D_801F5440 == 9 && D_801F55D8 > 224)
        {
            D_801F5440++;
            D_801F55D8 = (D_801F55D8 + 32) & 240;
        }
    }
    D_801E5558 = 11;
    D_801E59B8 = 224;
    load_img(D_801F5440, 11, D_801F55D8, 224, 0, D_801F8190);
}
