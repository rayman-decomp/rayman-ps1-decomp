#include "draw/fond_10B3C.h"

/* BinarySerializer.Ray1/DataTypes/PS1/Vignette */

#ifdef BSS_DEFS
u8 PS1_FondSpritesIsSemiTrans[16];
u8 PS1_FondSpritesABR[16];
u8 NbSprite;
DVECTOR *PS1_BackgroundPositions;
Sprite *PS1_BackgroundSprites;
u8 PS1_FondType;
u8 PS1_Tile_clut_y_offs[944];

Unk_801f8008 D_801E63F8[6];
u8 D_801F5788[16];
Unk_801f8008 D_801F8008[6];
u8 PS1_BandeBackCount;
u8 PS1_BandeFrontCount;
u8 D_801F4F58;
s16 D_801F55B8[8];
u8 D_801F84E0;
u8 D_801F9900;
s16 PS1_FondHeight;
u8 *D_801E4F50;
u8 *D_801F8180;

u8 *PS1_FondImages[6];

s16 PS1_FondImagesCount;
s16 PS1_FondWidth;
u8 D_801E4BC8;
u8 PS1_CurrentVitrailClignotement[5];
#endif

/* 10B3C 8013533C -O2 -msoft-float */
void init_bgm(void)
{
    DR_ENV *dr_env_0; DR_ENV *dr_env_1;
    SPRT *cur_sprt_0; SPRT *cur_sprt_1;
    Sprite *cur_sprite_bg;
    u8 i;
    u8 bg_id;

    PS1_BackgroundPositions = &PS1_LevelBGBlock->sprite_positions[0];
    PS1_BackgroundSprites = &PS1_LevelBGBlock->sprites[0];
    if (PS1_FondType == 6 || PS1_FondType == 7)
    {
        dr_env_0 = &PS1_Displays[0].map_drawing_environment_primitives[9];
        dr_env_1 = &PS1_Displays[1].map_drawing_environment_primitives[9];
        cur_sprt_0 = PS1_Displays[0].sprites;
        cur_sprt_1 = PS1_Displays[1].sprites;
        cur_sprite_bg = &PS1_LevelBGBlock->sprites[0];
        i = 0;
        while (i < NbSprite)
        {
            bg_id = cur_sprite_bg->id;

            SetSemiTrans(cur_sprt_0, PS1_FondSpritesIsSemiTrans[bg_id - 1]);
            SetShadeTex(cur_sprt_0, true);
            cur_sprt_0[0].u0 = cur_sprite_bg->page_x;
            cur_sprt_0[0].v0 = cur_sprite_bg->page_y;
            cur_sprt_0[0].w = cur_sprite_bg->width;
            cur_sprt_0[0].h = cur_sprite_bg->height;
            cur_sprt_0[0].clut = cur_sprite_bg->clut;
            __builtin_memcpy(&cur_sprt_0[0x10], &cur_sprt_0[0], sizeof(SPRT));
            __builtin_memcpy(&cur_sprt_0[0x20], &cur_sprt_0[0x10], sizeof(SPRT));
            __builtin_memcpy(&cur_sprt_0[0x10], &cur_sprt_0[0], sizeof(SPRT));
            __builtin_memcpy(&cur_sprt_0[0x20], &cur_sprt_0[0x10], sizeof(SPRT));

            SetSemiTrans(cur_sprt_1, PS1_FondSpritesIsSemiTrans[bg_id - 1]);
            SetShadeTex(cur_sprt_1, true);
            cur_sprt_1[0].u0 = cur_sprite_bg->page_x;
            cur_sprt_1[0].v0 = cur_sprite_bg->page_y;
            cur_sprt_1[0].w = cur_sprite_bg->width;
            cur_sprt_1[0].h = cur_sprite_bg->height;
            cur_sprt_1[0].clut = cur_sprite_bg->clut;
            __builtin_memcpy(&cur_sprt_1[0x10], &cur_sprt_1[0], sizeof(SPRT));
            __builtin_memcpy(&cur_sprt_1[0x20], &cur_sprt_1[0x10], sizeof(SPRT));
            __builtin_memcpy(&cur_sprt_1[0x10], &cur_sprt_1[0], sizeof(SPRT));
            __builtin_memcpy(&cur_sprt_1[0x20], &cur_sprt_1[0x10], sizeof(SPRT));

            getparam((s16) cur_sprite_bg->tpage);
            PS1_Displays[0].drawing_environment.tpage =
                GetTPage(1, PS1_FondSpritesABR[bg_id - 1], PS1_TPage_x, PS1_TPage_y);
            SetDrawEnv(dr_env_0, &PS1_Displays[0].drawing_environment);
            PS1_Displays[1].drawing_environment.tpage =
                GetTPage(1, PS1_FondSpritesABR[bg_id - 1], PS1_TPage_x, PS1_TPage_y);
            SetDrawEnv(dr_env_1, &PS1_Displays[1].drawing_environment);

            cur_sprt_0++;
            cur_sprt_1++;
            cur_sprite_bg++;
            dr_env_0++;
            dr_env_1++;
            i++;
        }
    }
}

/* 10EE0 801356E0 -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/draw/fond_10B3C", init_bgi);
#else
/*
score of 215
https://github.com/BinarySerializer/BinarySerializer.Ray1/blob/7da0e97301dd6502d027ff3c92ec2b5a00ef6e6e/src/BinarySerializer.Ray1/DataTypes/PS1/Vignette/FondSpriteData.cs
*/
void init_bgi(void)
{
    s32 temp_a0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    u16 var_s1_1;
    u8 *temp_s0_12;
    u32 *var_s0_2;
    s16 temp_t1; /* PalettesCount */
    u16 test_1; /* if i didn't use this, all the lhu's would be lbu's? */

    temp_s0_12 = D_801E4F50;
    test_1 = *(u16 *) temp_s0_12;
    NbSprite = test_1;
    temp_s0_12 += 2;
    PS1_BandeBackCount = *temp_s0_12++;
    PS1_BandeFrontCount = *temp_s0_12++;
    temp_t1 = *temp_s0_12;
    var_s1_1 = 0;
    temp_s0_12 += 4;
    while ((var_s1_1) < PS1_BandeBackCount)
    {
        test_1 = *(u16 *) temp_s0_12;
        D_801F8008[var_s1_1].unk_0 = test_1;
        temp_s0_12 += 2;
        test_1 = *(u16 *) temp_s0_12;
        D_801F8008[var_s1_1].unk_1 = test_1;
        temp_s0_12 += 2;
        test_1 = *(u16 *) temp_s0_12;
        PS1_FondSpritesIsSemiTrans[var_s1_1] = test_1;
        temp_s0_12 += 2;
        test_1 = *(u16 *) temp_s0_12;
        PS1_FondSpritesABR[var_s1_1] = test_1;
        temp_s0_12 += 2;
        test_1 = *(u16 *) temp_s0_12;
        D_801F5788[var_s1_1] = test_1;
        var_s1_1 += 1;
        temp_s0_12 += 2;
    }
    var_s1_1 = 0;
    while (var_s1_1 < PS1_BandeFrontCount)
    {
        temp_v0_2 = var_s1_1 * 4;
        test_1 = *(u16 *) temp_s0_12;
        D_801E63F8[var_s1_1].unk_0 = test_1;
        temp_s0_12 += 2;
        test_1 = *(u16 *) temp_s0_12;
        D_801E63F8[var_s1_1].unk_1 = test_1;
        temp_s0_12 += 2;
        test_1 = *(u16 *) temp_s0_12;
        PS1_FondSpritesIsSemiTrans[PS1_BandeBackCount + var_s1_1] = test_1;
        temp_s0_12 += 2;
        test_1 = *(u16 *) temp_s0_12;
        PS1_FondSpritesABR[PS1_BandeBackCount + var_s1_1] = test_1;
        temp_s0_12 += 2;
        test_1 = *(u16 *) temp_s0_12;
        D_801F5788[PS1_BandeBackCount + var_s1_1] = test_1;
        temp_s0_12 += 2;
        var_s1_1 += 1;
    }
    temp_v0_3 = PS1_BandeBackCount + PS1_BandeFrontCount;
    temp_s0_12 = temp_s0_12 + ((temp_v0_3 - (temp_v0_3 & 0x1FE)) * 2);
    var_s1_1 = 0;
    while ((u32) (var_s1_1) < temp_t1)
    {
        LoadClut((u32 *) temp_s0_12, 768, 503 - var_s1_1);
        var_s1_1 += 1;
        temp_s0_12 += 0x200;
    }
}
#endif

/* 11130 80135930 -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/draw/fond_10B3C", InitBG);
#else
/* score of ??? */
typedef struct Fond
{
    u8 unk_0;
    u8 unk_1;
    s16 width;
    s16 height;
    u8 unk_6;
    u8 type;
} Fond;

void InitBG(void)
{
    s32 value1;
    int i;
    s32 value2;
    int fi_count;
    void **cur_dest;
    u8 *cur_src;
    u8 uStack_18;
    u8 uStack_17;
    short width;
    short height;
    u8 uStack_12;
    u8 bStack_11;
    Fond test_1;
    s32 inc;
    u8 *new_var;
    u8 *test_2;

    memset(&D_801F55B8, 0, 10);
    __builtin_memcpy(&test_1, &D_801F8180[0], sizeof(Fond));
    D_801F84E0 = test_1.unk_0;
    D_801F9900 = test_1.unk_1;
    PS1_FondWidth = test_1.width;
    PS1_FondHeight = test_1.height;
    D_801F4F58 = test_1.unk_6;
    PS1_FondType = test_1.type;

    if (PS1_FondType == 0xc)
    {
        PS1_FondImagesCount = 2;
    }
    else
    {
        PS1_FondImagesCount = PS1_FondWidth >> 6;
    }

    cur_src = &D_801F8180[sizeof(Fond)];
    i = 0;
    if (i < PS1_FondImagesCount)
    {
        fi_count = PS1_FondImagesCount;
        cur_dest = &PS1_FondImages[i];
        inc = PS1_FondHeight << 7;
        while (i < fi_count)
        {
            *cur_dest = cur_src;
            cur_dest = cur_dest + 1;
            i = i + 1;
            cur_src = cur_src + inc;
        }
    }

    if ((((PS1_FondType == 6 || PS1_FondType == 7) || (PS1_FondType == 8)) || (PS1_FondType == 0xb)) ||
        ((PS1_FondType == 9 || PS1_FondType == 10 || (PS1_FondType == 0xc))))
    {
        init_bgm();
        init_bgi();
    }
    else
    {
        NbSprite = 0;
    }
}
#endif

/* 112B0 80135AB0 -O2 -msoft-float */
void DrawBG_spr_v(s16 param_1, s16 *param_2)
{
    u8 i;
    DVECTOR *cur_pos;
    DR_ENV *cur_dr_env;
    SPRT *cur_sprt;
    Sprite *cur_bg_sprite;
    u16 unk_1;
    s16 unk_x_1; s16 unk_y_1;

    i = 0;
    cur_pos = &PS1_BackgroundPositions[i];
    PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[i];
    cur_dr_env = &PS1_CurrentDisplay->map_drawing_environment_primitives[9];
    cur_sprt = &PS1_CurrentDisplay->sprites[D_801E4BC8];
    cur_bg_sprite = &PS1_BackgroundSprites[i];
    while (i < NbSprite)
    {
        unk_1 = param_2[cur_bg_sprite->id - 1];
        unk_x_1 = cur_pos->vx - param_1;
        unk_y_1 = cur_pos->vy - (unk_1 % PS1_FondHeight);
        if (PS1_BandeBackCount < cur_bg_sprite->id)
            PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[8];

        PS1_CurrentDisplay->drawing_environment.tpage = cur_bg_sprite->tpage;
        SetDrawEnv(cur_dr_env, &PS1_CurrentDisplay->drawing_environment);
        AddPrim(PS1_PrevPrim, cur_dr_env);
        PS1_PrevPrim = cur_dr_env;
        cur_dr_env++;

        cur_sprt->u0 = cur_bg_sprite->page_x;
        cur_sprt->v0 = cur_bg_sprite->page_y;
        cur_sprt->w = cur_bg_sprite->width;
        cur_sprt->h = cur_bg_sprite->height;
        cur_sprt->clut = cur_bg_sprite->clut;
        cur_sprt->code = cur_sprt->code & ~FLG(1) | FLG(0);
        cur_sprt->x0 = unk_x_1;
        cur_sprt->y0 = unk_y_1;
        AddPrim(PS1_PrevPrim, cur_sprt);
        PS1_PrevPrim = cur_sprt;
        cur_sprt++;
        D_801E4BC8++;
        if (PS1_FondHeight < unk_1 + SCREEN_HEIGHT)
        {
            __builtin_memcpy(cur_sprt, cur_sprt - 1, sizeof(SPRT));
            cur_sprt->y0 += PS1_FondHeight;
            AddPrim(PS1_PrevPrim, cur_sprt);
            PS1_PrevPrim = cur_sprt;
            cur_sprt++;
            D_801E4BC8++;
        }
        i++;
        cur_pos++;
        cur_bg_sprite++;
    }
}

/* 1155C 80135D5C -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/draw/fond_10B3C", DrawBG_spr_h);
#else
/* score of 2810 */
void DrawBG_spr_h(s32 param_1, u16 *param_2, s32 param_3, s16 param_4)
{
    s16 sVar1_1;
    Display *pDVar2;
    u32 *ppuVar3;
    u8 bVar4;
    s32 fw_1;
    s32 fw_2;
    s16 fw_3;
    s16 fw_4;
    u8 uVar7;
    s16 sVar9;
    SPRT *pSVar10;
    SPRT *cur_sprt;
    DR_ENV *cur_dr_env;
    DVECTOR *cur_pos;
    Sprite *cur_bg_sprite;
    u8 cnt_1;
    s16 test_1;
    s16 temp_v0_4;
    u32 *new_var_1; /* ??? was permuter sugg. */
    s16 new_var_2;

    cnt_1 = 0;
    fw_1 = PS1_FondWidth;
    fw_2 = PS1_FondWidth * 2;
    fw_4 = ((PS1_FondWidth * 2 - 0x140));
    fw_3 = ((PS1_FondWidth - 0x140));
    /*test_1 = ((NbSprite + 0xffff) << 0x10) >> 0x10;*/
    test_1 = ((NbSprite - 1));
    cur_pos = &PS1_BackgroundPositions[test_1];
    pDVar2 = PS1_CurrentDisplay;
    cur_bg_sprite = &PS1_BackgroundSprites[test_1];
    PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[8];
    cur_dr_env = &PS1_CurrentDisplay->map_drawing_environment_primitives[9 + test_1];

    cur_sprt = &PS1_CurrentDisplay->sprites[test_1];
    bVar4 = NbSprite;
    while (cnt_1 < bVar4)
    {
        uVar7 = cur_bg_sprite->id - 1;
        sVar9 = 1000;
        if (uVar7 == PS1_BandeBackCount)
        {
            sVar1_1 = param_2[uVar7] % param_4;
            new_var_2 = cur_pos->vx - sVar1_1;
            temp_v0_4 = cur_pos->vy - param_3;
            if (sVar9 > temp_v0_4)
            {
                sVar9 = temp_v0_4;
            }
            cur_sprt[0].x0 = new_var_2;
            cur_sprt[0].y0 = sVar9;
            ppuVar3 = PS1_PrevPrim;
            cur_sprt[0].tag = cur_sprt[0].tag & 0xff000000 | *ppuVar3 & 0xffffff;
            *ppuVar3 = (*ppuVar3 & 0xff000000 | (uint) &cur_sprt[0] & 0xffffff);
            if (fw_3 < sVar1_1)
            {
                cur_sprt[0x10].x0 = param_4 + cur_sprt[0].x0;
                cur_sprt[0x10].y0 = cur_sprt[0].y0;
                new_var_1 = &cur_sprt[0x10].tag;
                cur_sprt[0x10].tag = *new_var_1 & 0xff000000 | *ppuVar3 & 0xffffff;
                *ppuVar3 = (*ppuVar3 & 0xff000000 | (uint) (&cur_sprt[0x10]) & 0xffffff);
            }
        }
        else
        {
            PS1_PrevPrim = pDVar2->ordering_table;
            ppuVar3 = PS1_PrevPrim;
            sVar1_1 = param_2[uVar7] % (s16) fw_1;
            new_var_2 = cur_pos->vx - sVar1_1;
            temp_v0_4 = cur_pos->vy - param_1;
            if (sVar9 > temp_v0_4)
            {
                sVar9 = temp_v0_4;
            }
            cur_sprt[0].x0 = new_var_2;
            cur_sprt[0].y0 = sVar9;
            cur_sprt[0].tag = cur_sprt[0].tag & 0xff000000 | *ppuVar3 & 0xffffff;
            *ppuVar3 =
                (*ppuVar3 & 0xff000000 | (uint) &cur_sprt[0] & 0xffffff);
            if (fw_3 < sVar1_1)
            {
                cur_sprt[0x10].x0 = cur_sprt[0].x0 + fw_1;
                cur_sprt[0x10].y0 = cur_sprt[0].y0;
                new_var_1 = &cur_sprt[0x10].tag;
                cur_sprt[0x10].tag =
                    *new_var_1 & 0xff000000 | *ppuVar3 & 0xffffff;
                *ppuVar3 =
                    (*ppuVar3 & 0xff000000 | (uint) (&cur_sprt[0x10]) & 0xffffff);
                if (fw_4 < sVar1_1)
                {
                    cur_sprt[0x20].x0 = cur_sprt[0].x0 + fw_2;
                    cur_sprt[0x20].y0 = cur_sprt[0].y0;
                    cur_sprt[0x20].tag = cur_sprt[0x20].tag & 0xff000000 | *ppuVar3 & 0xffffff;
                    *ppuVar3 =
                        (*ppuVar3 & 0xff000000 | (uint) (&cur_sprt[0x20]) & 0xffffff);
                }
            }
        }

        cnt_1++;
        cur_pos--;
        cur_bg_sprite--;
        pSVar10--;
        cur_sprt--;
        ppuVar3 = PS1_PrevPrim;
        bVar4 = NbSprite;
        cur_dr_env->tag = cur_dr_env->tag & 0xff000000 | *ppuVar3 & 0xffffff;
        *ppuVar3 = (*ppuVar3 & 0xff000000 | (uint) cur_dr_env & 0xffffff);
        cur_dr_env--;
    }
}
#endif

/* 1193C 8013613C -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/draw/fond_10B3C", DrawBG_bande_h);
#else
void DrawBG_bande_h(u8 param_1, u32 param_2, u8 param_3, u32 param_4)
{
    u8 bVar1;
    int iVar2;
    uint uVar3;
    short sVar4;
    u8 bVar5;
    int iVar6;
    u8 uVar7;
    RECT local_48;
    uint local_40;
    int local_38;
    int local_30;
    s16 test_1;
    int new_var;

    param_4 &= 0xffff;
    uVar7 = param_4 & 0x3f;
    if (param_3 < 0xf0 && param_1 != 0)
    {
        if (0xf0 < param_3 + param_1)
            param_1 = 0xf0 - param_3;

        local_40 = (param_4) >> 6;
        bVar5 = test_1 = 6;
        local_38 = (param_2 & 0xffff) << 7;
        while (bVar5 != 0)
        {
            new_var = 5;
            if (bVar5 == test_1)
            {
                bVar1 = 0;
                sVar4 = 100;
            }
            else
            {
                sVar4 = 0;
                bVar1 = bVar5;
            }

            if (bVar1 == new_var)
            {
                sVar4 = -100;
            }

            if ((bVar1 != new_var) || uVar7 != 0)
            {
                iVar2 = PS1_FondImagesCount;
                iVar6 = bVar1 * 0x40 - uVar7;
                local_48.x = iVar6 + (PS1_CurrentDisplay->drawing_environment).clip.x + sVar4;
                local_48.y = (PS1_CurrentDisplay->drawing_environment).clip.y + param_3;
                local_48.w = 0x40;
                local_48.h = param_1;

                LoadImage(&local_48, (u_long *) (PS1_FondImages[(int) ((local_40) + bVar1) % iVar2] + local_38));
                if (bVar1 == 0)
                {
                    local_48.x = (PS1_CurrentDisplay->drawing_environment).clip.x + sVar4;
                    local_48.w = 0x40 - uVar7;
                    MoveImage(&local_48, (PS1_CurrentDisplay->drawing_environment).clip.x, local_48.y);
                }
                if (sVar4 == -100)
                {
                    local_48.w = (short) uVar7;
                    MoveImage(&local_48, iVar6 + (PS1_CurrentDisplay->drawing_environment).clip.x, local_48.y);
                }
            }
            bVar5 = bVar5 - 1;
        }
    }
}
#endif

/* 11B40 80136340 -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/draw/fond_10B3C", DrawBG_bande_v);
#else
/* thanks! https://decomp.me/scratch/sMPT6 */
/* still couldn't get fp38 */
void DrawBG_bande_v(u16 *param_1, u32 param_2)
{
    short sVar1;
    u16 bVar5;
    uint uVar10;
    int iVar11;
    RECT fp10;
    u16 fp20;
    uint fp28;
    int fp38;
    u16 var_a2;
    u32 test_1;
    int new_var_2;
    int temp_v0;
    int temp_v1;
    int temp_a2;
    u16 var_s7[PS1_FondImagesCount];
    u16 var_s6[PS1_FondImagesCount];
    u16 var_s5[PS1_FondImagesCount];

    param_2 = (u16) param_2;
    uVar10 = param_2 & 0x3f;
    fp28 = (param_2 >> 6);
    test_1 = 5;

    for (fp20 = 1; fp20 < 3; fp20++)
    {
        if (fp20 == 1)
        {
            for (var_a2 = 0; var_a2 < PS1_FondImagesCount; var_a2++)
            {
                var_s7[var_a2] = 0;
                var_s6[var_a2] =
                    (PS1_FondHeight < (param_1[var_a2] + 0xf0)) ? PS1_FondHeight - param_1[var_a2] : 0xf0;
                var_s5[var_a2] = param_1[var_a2];
            }
        }
        else
        {
            for (var_a2 = 0; var_a2 < PS1_FondImagesCount; var_a2++)
            {
                var_s7[var_a2] = var_s6[var_a2];
                var_s6[var_a2] = 0xf0 - var_s6[var_a2];
                var_s5[var_a2] = 0;
            }
        }

        /* inline??????????
        looks like DrawBG_bande_h */
        new_var_2 = 6;

        for (bVar5 = test_1 + 1; bVar5 != 0; bVar5--)
        {
            fp38 = 0x40 - uVar10;
            if (bVar5 == new_var_2)
            {
                var_a2 = 0;
                sVar1 = 0x40;
            }
            else
            {
                sVar1 = 0;
                var_a2 = bVar5;
            }

            if (var_a2 == test_1)
            {
                sVar1 = -0x40;

                if ((uVar10 == 0))
                {
                    continue;
                }
            }

            iVar11 = (int) (fp28 + var_a2) % PS1_FondImagesCount;
            if (var_s6[iVar11] != 0)
            {
                temp_v0 = var_s6[iVar11];
                temp_v1 = var_s7[iVar11];
                temp_a2 = var_s5[iVar11];
                fp10.x = sVar1 + (var_a2 * 0x40 - uVar10 + (u16) (PS1_CurrentDisplay->drawing_environment).clip.x);
                fp10.y = temp_v1 + (PS1_CurrentDisplay->drawing_environment).clip.y;
                fp10.w = 0x40;
                fp10.h = temp_v0;
                LoadImage(&fp10, (u_long *) (PS1_FondImages[iVar11] + temp_a2 * 0x80));
                if (var_a2 == 0)
                {
                    fp10.x = sVar1 + (PS1_CurrentDisplay->drawing_environment).clip.x;
                    fp10.w = fp38;
                    MoveImage(&fp10, (PS1_CurrentDisplay->drawing_environment).clip.x, fp10.y);
                }
                if (sVar1 == -0x40)
                {
                    fp10.w = uVar10;
                    MoveImage(&fp10, (var_a2 * 0x40 - uVar10) + (PS1_CurrentDisplay->drawing_environment).clip.x, fp10.y);
                }
            }
        }
    }
}
#endif

/* 11EAC 801366AC -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/draw/fond_10B3C", DrawBG_new);
#else
/* score of 1905 */
void DrawBG_new(void)
{
    RECT local_88;
    u16 sp30;
    short local_80[12];
    s16 var_s5;
    s32 temp_a0_2;
    s32 temp_hi;
    s32 temp_lo_1;
    s32 temp_lo_7;
    s32 temp_s7;
    s32 var_a0_1;
    s16 var_a0_2;
    u8 var_fp;
    u8 var_s0_1;
    u8 var_s0_3;
    s16 var_s2;
    s16 var_s3;
    s32 var_s4;
    u16 var_s6;
    s32 var_v1_1;
    s16 temp_s1_1;
    s16 new_var2;

    u8 test_2;
    s32 new_var = 0xF0;

    /*var_s3 = saved_reg_s3;*/
    switch (PS1_FondType)
    {
    case 2:
        if (
            num_world == 1 &&
            (num_level == 0x14 || num_level == 0x15 || num_level == 0x12 || num_level == 0x13)
        )
        {
        case 0:
            var_s3 = 0;
            var_s6 = 0;
            var_s2 = 0;
            var_s5 = 0;
        }
        else
        {
            var_s3 = (-((ymapmax - ymap) + 0xf0) + PS1_FondHeight) / D_801F9900;
            if ((PS1_FondHeight < 0xF0) && ((s16) var_s3 > (PS1_FondHeight - 0xF0)))
            {
                var_s2 = 0xF0 - PS1_FondHeight;
                var_s6 = 0;
            }
            else
            {
                var_s6 = var_s3;
                if (var_s3 >= 0)
                {
                    var_s2 = 0;
                }
                else
                {
                    var_s3 = -var_s3;
                    MIN_2(var_s3, 0xf0);
                    var_s2 = var_s3;
                    var_s6 = 0;
                }
            }
            var_s5 = 0;
            var_s3 = 0;
        }
        break;
    case 3:
        /* never sets var_s3 */
        var_s6 = ymap / D_801F9900;
        if (var_s6 > PS1_FondHeight)
        {
            var_s5 = 0x00F0;
        }
        else
        {
            if (var_s6 >= (PS1_FondHeight - 0xF0))
            {
                var_s5 = 0xF0 - (PS1_FondHeight - var_s6);
            }
            else
                var_s5 = 0;
        }
        var_s2 = 0;
        break;
    case 4:
        var_s6 = (ymap / D_801F9900) % PS1_FondHeight;
        var_s3 = 0;
        var_s2 = 0;
        var_s5 = 0;
        break;
    case 1:
        var_s6 = 0;
        if ((num_world == 3) && (num_level == 0x000A))
        {
            var_s3 = ymap / D_801F9900;
        }
        else
        {
            var_s3 = (u16) PS1_FondHeight - 0xF0;
        }
        var_s2 = 0;
        var_s5 = 0;
        break;
    case 8:
        var_s6 = 0;
        var_s2 = 0;
        var_s5 = 0;
        var_s3 = (u16) PS1_FondHeight - 0xF0;

        temp_s1_1 = PS1_FondWidth;
        PS1_FondWidth = 0x0180;
        var_s0_1 = 0;
        while ((var_s0_1) < PS1_BandeBackCount)
        {
            local_80[var_s0_1] =
                ((xmap + D_801F55B8[var_s0_1]) /
                D_801F8008[var_s0_1].unk_1);
            D_801F55B8[var_s0_1] =
                ((D_801F55B8[var_s0_1] + D_801F5788[var_s0_1]) %
                (PS1_FondWidth * D_801F8008[var_s0_1].unk_1));
            var_s0_1 += 1;
        }
        var_s0_1 = 0;
        while ((var_s0_1) < PS1_BandeFrontCount)
        {
            temp_a0_2 = PS1_BandeBackCount + var_s0_1;
            local_80[temp_a0_2] =
                (xmap + (D_801F55B8[temp_a0_2] / D_801E63F8[var_s0_1].unk_1));
            D_801F55B8[temp_a0_2] =
                ((D_801F55B8[var_s0_1] + D_801F5788[var_s0_1]) %
                (PS1_FondWidth * D_801E63F8[var_s0_1].unk_1));
            var_s0_1 += 1;
        }
        draw_spr_brume(var_s3, local_80, (var_s3 - ymapmax) + ymap, PS1_FondWidth);
        PS1_FondWidth = temp_s1_1;
        break;
    case 9:
    case 10:
        var_s3 = 0;
        var_s6 = 0;
        var_s2 = 0;
        var_s5 = 0;
        if ((num_world != 2) || ((num_level != 4)))
        {
            draw_spr_fix(PS1_FondType);
        }
        break;
    case 11:
        sp30 = xmap;
        xmap = 0;
        var_s6 = 0;
        var_s2 = 0;
        var_s5 = 0;
        var_s3 = (u16) PS1_FondHeight - 0xF0;
        do_allume_vitraux(PS1_CurrentVitrailClignotement);
        break;
    default:
        var_s6 = 0;
        var_s2 = 0;
        var_s5 = 0;
        var_s3 = (ymap * (PS1_FondHeight - 0xF0)) / ymapmax;
        break;
    }

    /*sp48 = var_s6;*/
    /*sp50 = var_s2 < 0xF0;*/
    /*sp58 = (0xF0 - var_s6) - var_s2;*/
    /*sp60 = 0xF0 - (s16) var_s2;*/
    /*sp68 = 0xF0 - var_s2; */
    /*var_v1_1 = 6 & 0xFF;*/
    new_var2 = (s16) var_s2;
    for (var_fp = 6; var_fp & 0xFF; var_fp--)
    {

        if (var_fp == 6)
        {
            var_s0_1 = 0;
            var_s4 = 0x64;
        }
        else
        {
            var_s4 = 0;
            var_s0_1 = var_fp;
        }

        if (var_s0_1 != 5 || (var_s4 = -0x64, (xmap / D_801F84E0) & 0x3F))
        {
            var_a0_1 = xmap / D_801F84E0;
            temp_s7 = (var_s0_1 << 6) - (var_a0_1 - ((var_a0_1 / 64) << 6));
            local_88.x = var_s4 + (temp_s7 + PS1_CurrentDisplay->drawing_environment.clip.x);
            local_88.w = 0x0040;
            temp_hi = (var_s0_1 + (var_a0_1 / 64)) % PS1_FondImagesCount;
            if (
                var_s6 != 0 ||
                (PS1_FondType == 2 && (new_var2 < 0xF0)) || /* var_s2 < 0xf0 not placed in sp50? */
                (PS1_FondType == 3 && (s16) var_s5 < 0xF0)
            )
            {
                local_88.y = var_s2 + PS1_CurrentDisplay->drawing_environment.clip.y;
                if ((PS1_FondType == 2) && (PS1_FondHeight < 0xF0))
                {
                    local_88.h = (0xF0 - var_s6) - var_s2; /* sp58 */
                }
                else
                {
                    local_88.h = (PS1_FondHeight - var_s6) - var_s2;
                }
                if ((0xF0 - new_var2) < local_88.h) /* ??? */
                {
                    local_88.h = 0xF0 - (new_var2);
                }
                LoadImage(&local_88, &PS1_FondImages[temp_hi][((var_s3 + var_s6) << 7)]);
                var_a0_2 = var_s5 + (var_s2 + (u16) local_88.h);
            }
            else
            {
                var_a0_2 = 0;
            }
            if ((u16) var_a0_2 < 0xF0U)
            {
                if (var_s6 == 0)
                {
                    local_88.y = PS1_CurrentDisplay->drawing_environment.clip.y;
                    local_88.h = 0x00F0;
                }
                else
                {
                    local_88.y = var_a0_2 + PS1_CurrentDisplay->drawing_environment.clip.y;
                    local_88.h = 0xF0 - var_a0_2;
                }
                if (local_88.h > 0xF0)
                {
                    local_88.h = 0x00F0;
                }
                LoadImage(&local_88, &PS1_FondImages[temp_hi][((var_s3 << 7))]);
            }
            if (var_s0_1 == 5)
            {
                temp_lo_7 = xmap / D_801F84E0;
                local_88.x = var_s4 + (temp_s7 + PS1_CurrentDisplay->drawing_environment.clip.x);
                local_88.y = PS1_CurrentDisplay->drawing_environment.clip.y;
                local_88.w = temp_lo_7 - ((temp_lo_7 / 64) << 6);
                local_88.h = 0x00F0;
                MoveImage(&local_88, temp_s7 + PS1_CurrentDisplay->drawing_environment.clip.x, local_88.y);
            }
            if (var_s0_1 == 0)
            {
                temp_lo_7 = xmap / D_801F84E0;
                local_88.x = var_s4 + PS1_CurrentDisplay->drawing_environment.clip.x;
                local_88.y = PS1_CurrentDisplay->drawing_environment.clip.y;
                local_88.w = 0x40 - (temp_lo_7 - ((temp_lo_7 / 64) << 6));
                local_88.h = 0x00F0;
                MoveImage(&local_88, PS1_CurrentDisplay->drawing_environment.clip.x, local_88.y);
            }
        }
    }

    if (var_s2 != 0)
    {
        local_88.x = PS1_CurrentDisplay->drawing_environment.clip.x;
        local_88.y = PS1_CurrentDisplay->drawing_environment.clip.y;
        local_88.w = 0x0140;
        local_88.h = var_s2;
        /*ClearImage(&local_88, (PS1_FondImages[0][0].r * 8),
                   (PS1_FondImages[0][0].g * 8),
                   (PS1_FondImages[0][0].b * 8));*/
        ClearImage(&local_88, (u8)((*(ushort *)PS1_FondImages[0] & (0x1f << 0)) << 3),
                   (u8)((*(ushort *)PS1_FondImages[0] & (0x1f << 5)) >> 2),
                   (u8)((*(ushort *)PS1_FondImages[0] & (0x1f << 10)) >> 7));
        
    }
    if (var_s5 != 0)
    {
        local_88.x = PS1_CurrentDisplay->drawing_environment.clip.x;
        local_88.y = PS1_CurrentDisplay->drawing_environment.clip.y - (var_s5 - new_var); /* TODO: new_var??? */
        local_88.w = 0x0140;
        local_88.h = var_s5;
        /*ClearImage(&local_88, (PS1_FondImages[1][-1].r * 8),
                   (PS1_FondImages[1][-1].g * 8),
                   (PS1_FondImages[1][-1].b * 8));*/ /* -1 index??? */
        ClearImage(&local_88, (u8)((*(ushort *)(PS1_FondImages[1] + -2) & (0x1f << 0)) << 3),
                   (u8)((*(ushort *)(PS1_FondImages[1] + -2) & (0x1f << 5)) >> 2),
                   (u8)((*(ushort *)(PS1_FondImages[1] + -2) & (0x1f << 10)) >> 7));
    }
    if (PS1_FondType == 0x0B)
    {
        xmap = sp30;
    }
}
#endif

/* 12B3C 8013733C -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/draw/fond_10B3C", DrawBG_gen);
#else
/*
score of 405
DrawBG_bande_h param_4???
*/
void DrawBG_gen(void)
{
    s16 sp10[12];
    s16 sp28[12];
    Unk_801f8008 *var_s3_1;
    s16 *temp_a1_1;
    s16 *temp_a2_2;
    s16 *var_s0_1;
    s16 *var_s2;
    s16 temp_hi;
    u8 var_a1;
    u8 var_s1_1;
    u8 var_s1_2;
    s16 var_s5;
    u8 temp_a2_1;
    u8 temp_s2_1;
    s16 var_s6;
    s16 *test_2;
    s32 test_3;
    s16 var_s7[PS1_FondImagesCount]; /* see https://decomp.me/scratch/sMPT6 */
    s16 *new_var_1;
    s16 *new_var_2;

    var_s3_1 = &D_801F8008[0];
    var_s6 = 0;
    if (PS1_FondType == 6)
    {

        D_801E4BC8 = 0;

        if (ymapmax >= (PS1_FondHeight >> 2))
        {
            var_s5 = (ymap * (PS1_FondHeight - 0xF0)) / ymapmax;
        }
        else
            var_s5 = PS1_FondHeight - 0xF0;

        var_s0_1 = &sp28[0];
        if ((u8) var_s3_1->unk_1 < 0xFFU)
        {
            test_2 = &D_801F55B8[0]; /* cannot make duplicates of this use test_2 also??? */
            *var_s0_1 = ((xmap + *test_2) / var_s3_1->unk_1);
            *test_2 = ((*test_2 + D_801F5788[0]) % (PS1_FondWidth * var_s3_1->unk_1));
        }
        else
        {
            *var_s0_1 = 0;
        }
        temp_s2_1 = var_s3_1->unk_0;
        var_s3_1++;

        DrawBG_bande_h(temp_s2_1 - var_s5, var_s5, var_s6, *var_s0_1);
        var_s6 += temp_s2_1;
        var_s0_1++;
        var_s1_1 = 1;
        new_var_2 = &D_801E63F8[0].unk_0; /* i don't even */
        while (var_s1_1 < (u8) PS1_BandeBackCount)
        {
            temp_a2_1 = var_s3_1->unk_1;
            if (temp_a2_1 < 0xFFU)
            {
                *var_s0_1 = ((xmap + D_801F55B8[var_s1_1]) / temp_a2_1);
                D_801F55B8[var_s1_1] = ((D_801F55B8[var_s1_1] + D_801F5788[var_s1_1]) % (PS1_FondWidth * var_s3_1->unk_1));
            }
            else
            {
                *var_s0_1 = 0;
            }
            temp_s2_1 = var_s3_1->unk_0;
            var_s3_1 += 1;
            DrawBG_bande_h(temp_s2_1, var_s6, var_s6 - var_s5, *var_s0_1);
            var_s6 += temp_s2_1;
            var_s0_1 += 1;
            var_s1_1 += 1;
        }

        *var_s0_1 = (xmap + D_801F55B8[var_s1_1]) * D_801E63F8[0].unk_1;
        D_801F55B8[var_s1_1] = ((D_801F55B8[var_s1_1] + D_801F5788[var_s1_1]) % PS1_FondWidth);
        DrawBG_spr_h(var_s5, sp28, (var_s5 - ymapmax) + ymap, *new_var_2);
    }
    else if ((PS1_FondType == 7) || (PS1_FondType == 0x0C))
    {
        var_s1_1 = 0;
        D_801E4BC8 = 0;
        var_s2 = sp10;
        var_s0_1 = &var_s7[0];
        while (var_s1_1 < (u8) PS1_BandeBackCount)
        {
            var_a1 = 0;
            temp_hi = (ymap / var_s3_1->unk_1) % PS1_FondHeight;
            *var_s2 = temp_hi;

            var_s2 += 1;

            while (var_a1 < var_s3_1->unk_0)
            {
                *var_s0_1 = temp_hi;
                var_s0_1 += 1;
                var_a1 += 1;
            }
            var_s1_1 += 1;
            var_s3_1 += 1;
        }
        if (PS1_FondType == 7)
        {
            DrawBG_bande_v(&var_s7[0], ((xmap) >> 3));
        }
        else
        {
            CLRSCR();
        }

        if (PS1_BandeFrontCount != 0)
        {
            *var_s2 = ((ymap * D_801E63F8[0].unk_1) % PS1_FondHeight);
        }

        if (PS1_FondType == 7)
        {
            DrawBG_spr_v(xmap >> 3, sp10);
        }
        else
        {
            draw_spr_v1(xmap >> 3, sp10);
        }
    }
    else if ((PS1_FondType == 8) || (PS1_FondType == 0x0B) || (PS1_FondType == 9 || PS1_FondType == 10))
    {
        D_801E4BC8 = 0;
        DrawBG_new();
    }
    else
        DrawBG_new();
}
#endif

/* 13198 80137998 -O2 -msoft-float */
u8 PS1_GetTileOrderingTableIndex(u8 param_1, u8 param_2, s32 param_3)
{
    s16 unk_1 = ((param_1 - 8) << 8) + param_2 + (param_3 & ~0xF);

    if (param_1 < 10 && unk_1 >= 480)
        unk_1 += 32;
    return (unk_1 >> 8) + 8;
}

/* 131F8 801379F8 -O2 -msoft-float */
u8 PS1_GetTileV(u8 param_1, u8 param_2, s32 tile)
{
    s16 unk_1 = ((param_1 - 8) << 8) + param_2 + (tile & ~0xF);

    if (param_1 < 10 && unk_1 >= 480)
        unk_1 += 32;
    return unk_1 & 0xF0;
}

/* 1324C 80137A4C -O2 -msoft-float */
u8 PS1_GetTileU(s32 param_1)
{
    return (param_1 & 0xF) * 16;
}

/* 13258 80137A58 -O2 -msoft-float */
void AddBlks(void)
{
  u32 uVar1;
  u32 uVar2;
  u_short uVar3;
  int iVar4;
  int y_pos;
  u32 puVar5;
  int tile_index;
  uint uVar6;
  int x_pos;
  SPRT_16 *pSVar7;
  s32 iVar8;
  s16 test_1;
  s32 new_var2;
  s32 test_2;
  
  iVar4 = -(((((u16) xmap << 0x10) >> 0x10) + ((((u16) xmap << 0x10) >> 0x10) / 16) * -0x10) << 0x10 >> 0x10);
  y_pos = -(new_var2 = ((((((ushort) ymap) << 0x10) >> 0x10) + ((((((ushort) ymap) << 0x10) >> 0x10) / 16) * (-0x10))) << 0x10) >> 0x10);
  iVar8 = (((ushort)ymap << 0x10) >> 0x14) * mp.width;
  test_2 = ((u16) xmap << 0x10) >> 0x14;
  pSVar7 = PS1_CurrentDisplay->tiles;
    while (y_pos < (PS1_CurrentDisplay->drawing_environment).clip.h) {
      tile_index = test_2 + iVar8;
      x_pos = iVar4;
        while (x_pos < 0x140) {
          puVar5 = mp.map[tile_index] & 0x3ff;
          tile_index = tile_index + 1;
          if ((puVar5 != 0) && (PS1_Tile_clut_y_offs[puVar5] != 0xff)) {
            pSVar7->clut = GetClut(0x300,PS1_Tile_clut_y_offs[puVar5] + 504);
            pSVar7->x0 = x_pos;
            pSVar7->y0 = y_pos;
            uVar1 = PS1_GetTileU(puVar5);
            uVar2 = PS1_GetTileV(D_801F5440,D_801F55D8,puVar5);
            test_1 = PS1_GetTileOrderingTableIndex(D_801F5440,D_801F55D8,puVar5);
            pSVar7->u0 = uVar1;
            pSVar7->v0 = uVar2;
            /*new_var = PS1_CurrentDisplay->ordering_table;*/
            AddPrim(PS1_CurrentDisplay->ordering_table + (test_1) - 6,pSVar7);
            pSVar7 = pSVar7 + 1;
          }
          x_pos = x_pos + 0x10;
        }
      y_pos = y_pos + 0x10;
      iVar8 = iVar8 + mp.width;
    }
  AddPrim(PS1_CurrentDisplay->ordering_table + 2,
          PS1_CurrentDisplay->map_drawing_environment_primitives);
  AddPrim(PS1_CurrentDisplay->ordering_table + 3,
          PS1_CurrentDisplay->map_drawing_environment_primitives + 1);
  AddPrim(PS1_CurrentDisplay->ordering_table + 4,
          PS1_CurrentDisplay->map_drawing_environment_primitives + 2);
  AddPrim(PS1_CurrentDisplay->ordering_table + 5,
          PS1_CurrentDisplay->map_drawing_environment_primitives + 3);
  return;
}

const u8 D_80127734[] __attribute__((aligned(2))) =
{
    5,   6,   7,   5,   6,   7,   3,   4,   3,   4, 
    0,   1,   2,   0,   1,   2,   3,   4,   3,   4, 
    5,   6,   7,   5,   6,   7,  14,   5,   6,   7, 
    5,   6,   7,   3,   4,   3,   4,   0,   1,   2, 
    0,   1,   2,   3,   4,   3,   4,   5,   6,   7, 
    5,   6,   7
};

const u8 D_8012776C[] __attribute__((aligned(2))) =
{
    1,   1,   1,   1,   1,   1,   1,   1,   1,   1, 
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
    0,   0,   0,   0,   0,   0,   0,   1,   1,   1, 
    1,   1,   1,   1,   1,   1,   1,   0,   0,   0, 
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
    0,   0,   0
};

const u8 D_801277A4[] __attribute__((aligned(2))) =
{
    0,   0,   0,   0,   0,   1,   0,   0,   0,   1, 
    0,   0,   0,   0,   0,   1,   0,   0,   0,   1, 
    0,   0,   0,   0,   0,   1,   1,   0,   0,   0, 
    0,   0,   1,   0,   0,   0,   1,   0,   0,   0, 
    0,   0,   1,   0,   0,   0,   1,   0,   0,   0, 
    0,   0,   1
};

/* 134C8 80137CC8 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/draw/fond_10B3C", draw_spr_v1);
#else
/* unknowns? */
void draw_spr_v1(s16 param_1, s16 *param_2)
{
    u8 sp10[LEN(D_80127734)];
    u8 sp48[LEN(D_8012776C)];
    u8 sp80[LEN(D_801277A4)];
    POLY_FT4 *cur_poly;
    u8 i;
    u8 unk_1;
    Sprite *cur_bg_sprite;
    u16 unk_w_2; u16 unk_h_2;
    s16 unk_x_1; s16 unk_y_1;
    s16 unk_w_1; s16 unk_h_1; /* cannot move these up? */

    __builtin_memcpy(sp10, D_80127734, sizeof(D_80127734));
    __builtin_memcpy(sp48, D_8012776C, sizeof(D_8012776C));
    __builtin_memcpy(sp80, D_801277A4, sizeof(D_801277A4));
    unk_w_1 = 24;
    unk_h_1 = 0;
    cur_poly = &PS1_CurrentDisplay->polygons[PS1_PolygonsCount];
    for (i = 0; i < 53; i++) /* LEN of which one? */
    {
        unk_1 = sp10[i];
        if (unk_1 < 10)
        {
            cur_bg_sprite = &PS1_BackgroundSprites[unk_1];
            unk_w_2 = cur_bg_sprite->width;
            unk_h_2 = param_2[cur_bg_sprite->id - 1];
            unk_x_1 = unk_w_1 - param_1;
            unk_y_1 = unk_h_1 - (unk_h_2 % PS1_FondHeight);
            if ((unk_x_1 < unk_w_2 + SCREEN_WIDTH) && unk_x_1 > -unk_w_2)
            {
                if (sp48[i])
                {
                    cur_poly->u0 = cur_bg_sprite->page_x + cur_bg_sprite->width - 1;
                    cur_poly->v0 = cur_bg_sprite->page_y;
                    cur_poly->u1 = cur_bg_sprite->page_x - 1;
                    cur_poly->v1 = cur_bg_sprite->page_y;
                    cur_poly->u2 = cur_bg_sprite->page_x + cur_bg_sprite->width - 1;
                    cur_poly->v2 = cur_bg_sprite->page_y + cur_bg_sprite->height;
                    cur_poly->u3 = cur_bg_sprite->page_x - 1;
                    cur_poly->v3 = cur_bg_sprite->page_y + cur_bg_sprite->height;
                }
                else
                {
                    cur_poly->u0 = cur_bg_sprite->page_x;
                    cur_poly->v0 = cur_bg_sprite->page_y;
                    cur_poly->u1 = cur_bg_sprite->page_x + cur_bg_sprite->width;
                    cur_poly->v1 = cur_bg_sprite->page_y;
                    cur_poly->u2 = cur_bg_sprite->page_x;
                    cur_poly->v2 = cur_bg_sprite->page_y + cur_bg_sprite->height;
                    cur_poly->u3 = cur_bg_sprite->page_x + cur_bg_sprite->width;
                    cur_poly->v3 = cur_bg_sprite->page_y + cur_bg_sprite->height;
                }

                cur_poly->x0 = unk_x_1;
                cur_poly->y0 = unk_y_1;
                cur_poly->x1 = unk_x_1 + cur_bg_sprite->width;
                cur_poly->y1 = unk_y_1;
                cur_poly->x2 = unk_x_1;
                cur_poly->y2 = unk_y_1 + cur_bg_sprite->height;
                cur_poly->x3 = unk_x_1 + cur_bg_sprite->width;
                cur_poly->y3 = unk_y_1 + cur_bg_sprite->height;
                cur_poly->clut = cur_bg_sprite->clut;
                cur_poly->tpage = cur_bg_sprite->tpage;
                AddPrim(&PS1_CurrentDisplay->ordering_table[0], cur_poly);
                cur_poly++;
                PS1_PolygonsCount++;
                if (PS1_FondHeight < unk_h_2 + SCREEN_HEIGHT)
                {
                    /* better way of writing the - 1 accesses? */
                    __builtin_memcpy(cur_poly, cur_poly - 1, sizeof(POLY_FT4));

                    cur_poly->x0 = unk_x_1;
                    cur_poly->y0 = (cur_poly - 1)->y0 + PS1_FondHeight;
                    cur_poly->x1 = unk_x_1 + cur_bg_sprite->width;
                    cur_poly->y1 = (cur_poly - 1)->y0 + PS1_FondHeight;
                    cur_poly->x2 = unk_x_1;
                    cur_poly->y2 = (cur_poly - 1)->y0 + PS1_FondHeight + cur_bg_sprite->height;
                    cur_poly->x3 = unk_x_1 + cur_bg_sprite->width;
                    cur_poly->y3 = (cur_poly - 1)->y0 + PS1_FondHeight + cur_bg_sprite->height;
                    AddPrim(PS1_CurrentDisplay->ordering_table, cur_poly);
                    cur_poly++;
                    PS1_PolygonsCount++;
                }
            }

            if (sp80[i])
            {
                unk_w_1 += cur_bg_sprite->width;
                if (sp10[i] <= 2)
                    unk_w_1 -= 2;
            }

            unk_h_1 += cur_bg_sprite->height;
            if (unk_h_1 == PS1_FondHeight)
                unk_h_1 = 0;
        }
        else
        {
            unk_w_1 += sp10[i];
            unk_h_1 = 0;
        }
    }
}
#endif

/* 13B38 80138338 -O2 -msoft-float */
void allume_vitraux(u8 (*param_1)[5])
{
    __builtin_memcpy(PS1_CurrentVitrailClignotement, param_1, sizeof(*param_1));
}

/* 13B60 80138360 -O2 -msoft-float */
void do_allume_vitraux(u8 *vit_clig)
{
    u8 i;
    DVECTOR *cur_bg_pos;
    Sprite *cur_bg_sprite;
    DR_ENV *cur_dr_env = &PS1_CurrentDisplay->map_drawing_environment_primitives[9];

    for (i = 0; i < NbSprite; i++)
    {
        if (vit_clig[i] != 0)
        {
            cur_bg_pos = &PS1_BackgroundPositions[i];
            cur_bg_sprite = &PS1_BackgroundSprites[i];
            /* gross... */
            SetSemiTrans((PS1_CurrentDisplay->sprites + D_801E4BC8), true);
            SetShadeTex((PS1_CurrentDisplay->sprites + D_801E4BC8), false);
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->r0 = PS1_Glass_brightness[i];
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->g0 = PS1_Glass_brightness[i];
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->b0 = PS1_Glass_brightness[i];
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->u0 = cur_bg_sprite->page_x;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->v0 = cur_bg_sprite->page_y;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->w = cur_bg_sprite->width;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->h = cur_bg_sprite->height;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->clut = cur_bg_sprite->clut;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->x0 = cur_bg_pos->vx;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->y0 = cur_bg_pos->vy;
            getparam((s16) cur_bg_sprite->tpage);
            AddPrim(PS1_CurrentDisplay->ordering_table, (PS1_CurrentDisplay->sprites + D_801E4BC8));
            D_801E4BC8++;
            PS1_CurrentDisplay->drawing_environment.tpage = GetTPage(1, 1, PS1_TPage_x, PS1_TPage_y);
            SetDrawEnv(cur_dr_env, &PS1_CurrentDisplay->drawing_environment);
            AddPrim(PS1_CurrentDisplay->ordering_table, cur_dr_env);
            cur_dr_env++;
            if (PS1_Glass_brightness[i] == 0xFF)
                PS1_Glass_brightness_diff[i] = -5;
            else if (PS1_Glass_brightness[i] == 0)
                PS1_Glass_brightness_diff[i] = 5;
            PS1_Glass_brightness[i] += PS1_Glass_brightness_diff[i];
            if (D_801C71C0[i] == 100)
            {
                vit_clig[i] = 0;
                D_801C71C0[i] = 0;
            }
            else
                D_801C71C0[i]++;
        }
    }
}

/* 13F18 80138718 -O2 -msoft-float */
void draw_spr_fix(u8 param_1) /* param_1 = PS1_FondType */
{
    DVECTOR *temp_s1;
    DR_ENV *var_s4;
    Sprite *temp_s2;
    s16 temp_s1_2;
    s32 temp_hi;
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s6;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a1;
    u8 var_s0;
    u8 var_s3;
    u16 temp_s5;
    void *temp_v0_3;
    u16 new_var;
    SPRT *test_1;

    var_s3 = 0;
    var_s4 = &PS1_CurrentDisplay->map_drawing_environment_primitives[9];
    if (NbSprite != 0)
    {
        do
        {
            temp_s1 = &PS1_BackgroundPositions[var_s3];
            temp_s2 = &PS1_BackgroundSprites[var_s3];
            if (param_1 == 0xA)
            {
                var_s0 = rand() % param_1;
            }
            else
            {
                var_s0 = 0;
            }
            temp_hi = xmap / (D_801F84E0 + 2) % PS1_FondWidth;
            temp_s5 = temp_s1->vy;
            temp_s1_2 = temp_s1->vx - temp_hi;
            temp_s6 = temp_hi;
            SetSemiTrans(&PS1_CurrentDisplay->sprites[D_801E4BC8], 1);
            
            if (var_s3 != 3)
            {
                
                var_a0 = D_801E4BC8;
                var_a1 = 0;
            }
            else
            {
                
                var_a0 = D_801E4BC8;
                var_a1 = 1;
            }
            SetShadeTex(&PS1_CurrentDisplay->sprites[var_a0], var_a1);
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->r0 = var_s0 + D_801CEF51;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->g0 = var_s0 + D_801CEF51;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->b0 = var_s0 + D_801CEF51;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->u0 = temp_s2->page_x;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->v0 = temp_s2->page_y;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->w = temp_s2->width;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->h = temp_s2->height;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->clut = temp_s2->clut;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->x0 = temp_s1_2;
            (PS1_CurrentDisplay->sprites + D_801E4BC8)->y0 = temp_s5;
            
            AddPrim(PS1_CurrentDisplay->ordering_table, &PS1_CurrentDisplay->sprites[D_801E4BC8]);
            D_801E4BC8 += 1;
            if (PS1_FondWidth < ((s16) temp_s6 + 0x140))
            {
                PS1_CurrentDisplay->sprites[D_801E4BC8] = PS1_CurrentDisplay->sprites[D_801E4BC8 - 1];
                PS1_CurrentDisplay->sprites[D_801E4BC8].x0 = PS1_CurrentDisplay->sprites[D_801E4BC8].x0 + PS1_FondWidth;
                AddPrim(PS1_CurrentDisplay->ordering_table, &PS1_CurrentDisplay->sprites[D_801E4BC8]);
                D_801E4BC8 += 1;
            }
            var_s3 += 1;
            getparam((s16) temp_s2->tpage);
            PS1_CurrentDisplay->drawing_environment.tpage = GetTPage(1, 1, PS1_TPage_x, PS1_TPage_y);
            SetDrawEnv(var_s4, &PS1_CurrentDisplay->drawing_environment);
            AddPrim(PS1_CurrentDisplay->ordering_table, var_s4);
            var_s4 += 1;
        } while (var_s3 < NbSprite);
    }
}

/* 14384 80138B84 -O2 -msoft-float */
void draw_spr_brume(s16 in_h_1, s16 *param_2, s16 in_h_2, s16 in_w_1)
{
    u8 unk_1[8];
    u8 i;
    DVECTOR *cur_pos;
    DR_ENV *cur_dr_env;
    SPRT *cur_sprt;
    Sprite *cur_bg_sprite;
    u8 bg_id;
    s16 unk_2;
    s16 unk_w_1; s16 unk_h_1;
    s16 unk_3;
    s16 unk_x_1; s16 unk_y_1;

    __builtin_memcpy(unk_1, D_801CEF6C, sizeof(D_801CEF6C));
    i = 0;
    cur_pos = &PS1_BackgroundPositions[i];
    PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[i];
    cur_dr_env = &PS1_CurrentDisplay->map_drawing_environment_primitives[9];
    cur_sprt = &PS1_CurrentDisplay->sprites[i];
    cur_bg_sprite = &PS1_BackgroundSprites[i];
    while (i < NbSprite)
    {
        bg_id = cur_bg_sprite->id - 1;
        unk_2 = param_2[bg_id];
        SetSemiTrans(cur_sprt, PS1_FondSpritesIsSemiTrans[bg_id]);
        SetShadeTex(cur_sprt, false);
        cur_sprt->r0 = D_801CEF54[bg_id];
        cur_sprt->g0 = D_801CEF54[bg_id];
        cur_sprt->b0 = D_801CEF54[bg_id];
        if (unk_1[bg_id] == 0 && (map_time & 129) == 0)
        {
            if (D_801CEF54[bg_id] == D_801CEF5C[bg_id])
            {
                D_801CEF5C[bg_id] = rand() & 129;
                D_801CEF64[bg_id] =
                    D_801CEF5C[bg_id] > D_801CEF54[bg_id] ? 1 : 0xFF;
            }
            else
                D_801CEF54[bg_id] += D_801CEF64[bg_id];

            unk_1[bg_id] = 1;
        }
        getparam((s16) cur_bg_sprite->tpage);
        cur_bg_sprite->tpage = GetTPage(1, PS1_FondSpritesABR[bg_id], PS1_TPage_x, PS1_TPage_y);
        if (bg_id >= PS1_BandeBackCount)
        {
            unk_w_1 = in_w_1;
            unk_h_1 = in_h_2;
            PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[8];
        }
        else
        {
            unk_w_1 = PS1_FondWidth;
            unk_h_1 = in_h_1;
        }
        unk_3 = unk_2 % unk_w_1;
        unk_x_1 = cur_pos->vx - unk_3;
        unk_y_1 = cur_pos->vy - unk_h_1;
        PS1_CurrentDisplay->drawing_environment.tpage = cur_bg_sprite->tpage;
        SetDrawEnv(cur_dr_env, &PS1_CurrentDisplay->drawing_environment);
        AddPrim(PS1_PrevPrim, cur_dr_env);
        PS1_PrevPrim = cur_dr_env;
        cur_dr_env++;

        cur_sprt->u0 = cur_bg_sprite->page_x;
        cur_sprt->v0 = cur_bg_sprite->page_y;
        cur_sprt->w = cur_bg_sprite->width;
        cur_sprt->h = cur_bg_sprite->height;
        cur_sprt->clut = cur_bg_sprite->clut;
        cur_sprt->x0 = unk_x_1;
        cur_sprt->y0 = unk_y_1;
        AddPrim(PS1_PrevPrim, cur_sprt);
        PS1_PrevPrim = cur_sprt;
        cur_sprt++;
        D_801E4BC8++;
        if (PS1_FondWidth < unk_3 + SCREEN_WIDTH)
        {
            __builtin_memcpy(cur_sprt, cur_sprt - 1, sizeof(SPRT));
            cur_sprt->x0 += unk_w_1;
            AddPrim(PS1_PrevPrim, cur_sprt);
            PS1_PrevPrim = cur_sprt;
            cur_sprt++;
            D_801E4BC8++;
        }
        i++;
        cur_pos++;
        cur_bg_sprite++;
    }
}

/* 14814 80139014 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/draw/fond_10B3C", DISPLAY_ANYSIZE_FND);
#else
/* applying these would let us remove new_var_1, test_6? */
static inline s32 DISPLAY_ANYSIZE_FND_1(s32 param_1)
{
    return param_1 / 0x40;
}

static inline s32 DISPLAY_ANYSIZE_FND_2(s16 param_1)
{
    return param_1 - DISPLAY_ANYSIZE_FND_1(param_1) * 0x40;
}

void DISPLAY_ANYSIZE_FND(s16 param_1, s16 param_2, s16 param_3, s16 param_4, s16 param_5, s16 param_6)
{
    s32 iVar7;
    s16 var_s3;
    u8 uVar9;
    u8 i;
    RECT local_58;
    s32 new_var_1;
    s32 new_var_2;
    s32 test_6;

    for (i = (param_6 / 0x40) + 1; i != 0; i--)
    {
        var_s3 = 0;

        if (i == (param_6 / 0x40) + 1U)
        {
            uVar9 = 0;
            var_s3 = 0x40;
        }
        else
            uVar9 = i;

        if (uVar9 == param_6 / 0x40)
        {
            var_s3 = -0x40;
            if ((param_1 & (0x40 - 1)) == 0)
                continue;
        }
        new_var_2 = uVar9 * 0x40;
        new_var_1 = param_1 + (param_1 / 0x40) * -0x40;
        iVar7 = new_var_2 - ((s16) new_var_1);
        local_58.x = iVar7 + PS1_CurrentDisplay->drawing_environment.clip.x + param_3 + var_s3;
        local_58.y = PS1_CurrentDisplay->drawing_environment.clip.y + param_4;
        local_58.w = 0x40;
        local_58.h = param_5;

        LoadImage(&local_58, (u32 *) &PS1_FondImages[(uVar9 + param_1 / 0x40) % PS1_FondImagesCount][param_2 << 7]);
        if (uVar9 == 0)
        {
            local_58.x = PS1_CurrentDisplay->drawing_environment.clip.x + param_3 + var_s3;
            test_6 = param_1 + (param_1 / 0x40) * -0x40;
            local_58.w = 0x40 - test_6;
            MoveImage(&local_58, PS1_CurrentDisplay->drawing_environment.clip.x + param_3, local_58.y);
        }
        if (uVar9 == param_6 / 0x40)
        {
            local_58.x = iVar7 + PS1_CurrentDisplay->drawing_environment.clip.x + var_s3 + param_3;
            local_58.w = param_6 - iVar7;
            MoveImage(&local_58, iVar7 + PS1_CurrentDisplay->drawing_environment.clip.x + param_3, local_58.y);
        }
    }
    DrawSync(0);
}
#endif

void PS1_EmptyFunction9(void) {}

void PS1_EmptyFunction10(void) {}
