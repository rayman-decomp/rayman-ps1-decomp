#include "draw/text_18118.h"

#ifdef BSS_DEFS
u8 colour;
s16 D_801F81B0;
#endif

/* 18118 8013C918 -O2 -msoft-float */
u8 PS1_deter_num_let_old(s32 param_1)
{
    s32 res;

    if ((u8) (param_1 - 'a') < 0x1a)
        res = param_1 - ']';
    else
    {
        if ((u8) (param_1 - 'A') >= 0x1a)
        {
            if ((u8) (param_1 - '0') >= 0xa)
            {
                switch ((u8) param_1)
                {
                case 0:
                case 1:
                default:
                    res = 0;
                    break;
                case '?':
                    res = 1;
                    break;
                case '!':
                    res = 2;
                    break;
                case '.':
                    res = 3;
                    break;
                }
            }
            else
                res = param_1 - 0x12;
        }
        else
            res = param_1 - 0x3D;
    }
    return res;
}

/* 181A4 8013C9A4 -O2 -msoft-float */
s16 SizeLettre(s16 sprite, u8 font)
{
    switch (font)
    {
    case 2:
        return D_801C7228[sprite];
    case 1:
        return D_801C71F8[sprite];
    default:
        return D_801C71CC[sprite];
    }
}

/* 18214 8013CA14 -O2 -msoft-float */
s32 calc_let_Width(u8 font, s16 sprite)
{
    return SizeLettre(sprite, font);
}

/* 18244 8013CA44 -O2 -msoft-float */
s16 SizeLigne(u8 *str, u8 font)
{
    s16 res = 0;
    u8 i = 0;

    while (str[i] != 0)
    {
        res += SizeLettre(deter_num_let(str[i]), font);
        i++;
    }
    return res;
}

/* 182D0 8013CAD0 -O2 -msoft-float */
void PS1_DisplayMenuText(u8 *str, u8 param_2, u8 color)
{
    GetClut(color * 16 + 64, 509);
    display_text(
        str,
        (SCREEN_WIDTH - SizeLigne(str, 0)) >> 1,
        param_2 * 36 + 4,
        0,
        color
    );
}

/* 1835C 8013CB5C -O2 -msoft-float */
void PS1_DisplayMenuTexts(u8 index, MenuText *in_menus)
{
    u8 sel_row;
    u8 *count;
    s32 unk_1;
    u8 i;
    s32 unk_2;
    MenuText *menu = &in_menus[index];

    PS1_PolygonsCount = 0;
    PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[6];
    sel_row = menu->selected_row;
    count = &menu->rows_count;
    if (sel_row < SCREEN_HEIGHT)
    {
        unk_1 = sel_row + 6;
        draw_sprite(&alpha.sprites[40], 39, (unk_1 - *count) * 36 + 4, 0);
    }
    PS1_DisplayMenuText(menu->header, 1, menu->color);

    for (i = 0; i < *count; i++)
    {
        unk_2 = i + 7;
        PS1_DisplayMenuText(menu->rows[i], unk_2 - *count, menu->color);
    }
}

/* 1845C 8013CC5C -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/draw/text_18118", display_blackboxborder);
#else
/* clean up */
void display_blackboxborder(s16 x, s16 y, s16 w, s16 h, u8 brightness)
{
    u8 i;
    u16 test_2 = 0xFFFD; /* not signed? */

    PS1_CurrentDisplay->fond_box_tiles[0].x0 = x + test_2;
    PS1_CurrentDisplay->fond_box_tiles[0].y0 = y + test_2;
    PS1_CurrentDisplay->fond_box_tiles[0].w = w + 6;
    PS1_CurrentDisplay->fond_box_tiles[0].h = 3;
    PS1_CurrentDisplay->fond_box_tiles[0].r0 = 0;
    PS1_CurrentDisplay->fond_box_tiles[0].g0 = 0;
    PS1_CurrentDisplay->fond_box_tiles[0].b0 = 255;
    PS1_CurrentDisplay->fond_box_tiles[1].x0 = x + w;
    PS1_CurrentDisplay->fond_box_tiles[1].y0 = y;
    PS1_CurrentDisplay->fond_box_tiles[1].w = 3;
    PS1_CurrentDisplay->fond_box_tiles[1].h = h;
    PS1_CurrentDisplay->fond_box_tiles[1].r0 = 0;
    PS1_CurrentDisplay->fond_box_tiles[1].g0 = 0;
    PS1_CurrentDisplay->fond_box_tiles[1].b0 = 255;
    PS1_CurrentDisplay->fond_box_tiles[2].x0 = x + test_2;
    PS1_CurrentDisplay->fond_box_tiles[2].y0 = y + h;
    PS1_CurrentDisplay->fond_box_tiles[2].w = w + 6;
    PS1_CurrentDisplay->fond_box_tiles[2].h = 3;
    PS1_CurrentDisplay->fond_box_tiles[2].r0 = 0;
    PS1_CurrentDisplay->fond_box_tiles[2].g0 = 0;
    PS1_CurrentDisplay->fond_box_tiles[2].b0 = 255;
    PS1_CurrentDisplay->fond_box_tiles[3].x0 = x + test_2;
    PS1_CurrentDisplay->fond_box_tiles[3].y0 = y;
    PS1_CurrentDisplay->fond_box_tiles[3].w = 3;
    PS1_CurrentDisplay->fond_box_tiles[3].h = h;
    PS1_CurrentDisplay->fond_box_tiles[3].r0 = 0;
    PS1_CurrentDisplay->fond_box_tiles[3].g0 = 0;
    PS1_CurrentDisplay->fond_box_tiles[3].b0 = 255;

    for (i = 0; i < LEN(PS1_CurrentDisplay->fond_box_tiles); i++)
    {
        SetTile(&PS1_CurrentDisplay->fond_box_tiles[i]);
        SetSemiTrans(&PS1_CurrentDisplay->fond_box_tiles[i], false);
        SetShadeTex(&PS1_Displays[0].fond_box_tiles[i], true); /* why PS1_Displays[0]? */
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->fond_box_tiles[i]);
    }

    SetTile(&PS1_CurrentDisplay->fond_box_tile);
    SetShadeTex(&PS1_CurrentDisplay->fond_box_tile, true);
    PS1_CurrentDisplay->fond_box_tile.x0 = x;
    PS1_CurrentDisplay->fond_box_tile.y0 = y;
    PS1_CurrentDisplay->fond_box_tile.w = w;
    PS1_CurrentDisplay->fond_box_tile.h = h;
    if (brightness == 255)
    {
        SetSemiTrans(&PS1_CurrentDisplay->fond_box_tile, false);
        PS1_CurrentDisplay->fond_box_tile.r0 = 0;
        PS1_CurrentDisplay->fond_box_tile.g0 = 0;
        PS1_CurrentDisplay->fond_box_tile.b0 = 0;
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->fond_box_tile);
    }
    else
    {
        PS1_CurrentDisplay->fond_box_tile.r0 = brightness;
        PS1_CurrentDisplay->fond_box_tile.g0 = brightness;
        PS1_CurrentDisplay->fond_box_tile.b0 = brightness;
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->fond_box_tile);
        PS1_CurrentDisplay->drawing_environment.tpage = GetTPage(1, 2, 0, 256);
        SetDrawEnv(&PS1_CurrentDisplay->unk_dr_env, &PS1_CurrentDisplay->drawing_environment);
        AddPrim(&PS1_CurrentDisplay->ordering_table[9], &PS1_CurrentDisplay->unk_dr_env);
    }
}
#endif

/* 1875C 8013CF5C -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/draw/text_18118", display_blackbox);
#else
/* some way to reduce duplication? */
static inline DRENVAndTile *display_blackbox_1()
{
    return &PS1_CurrentDisplay->field_0x60bc_0x660b[D_801F81B0 + 7];
}

static inline TILE *display_blackbox_2()
{
    return &PS1_CurrentDisplay->field_0x60bc_0x660b[D_801F81B0 + 7].tile;
}

#define display_blackbox_3 (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)
/* these two would still be matching? but can't be what they did, surely? */
#define display_blackbox_4 (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile
#define display_blackbox_5 PS1_CurrentDisplay->field_0x60bc_0x660b[D_801F81B0 + 7].drawing_environment

void display_blackbox(s16 x, s16 y, s16 w, s16 h, u8 brightness)
{
    D_801F81B0++;
    SetTile(&(PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile);
    SetShadeTex(&(PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile, 1);
    (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile.x0 = x;
    (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile.y0 = y;
    (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile.w = w;
    (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile.h = h;
    if (brightness == 255)
    {
        SetSemiTrans(&(PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile, 0);
        (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile.r0 = 0;
        (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile.g0 = 0;
        (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile.b0 = 0;
        AddPrim(
            &PS1_CurrentDisplay->ordering_table[9],
            &(PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile
        );
    }
    else
    {
        SetSemiTrans(&(PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile, 1);
        (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile.r0 = brightness;
        (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile.g0 = brightness;
        (PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile.b0 = brightness;
        AddPrim(
            &PS1_CurrentDisplay->ordering_table[9],
            &(PS1_CurrentDisplay->field_0x60bc_0x660b + D_801F81B0 + 7)->tile
        );
        (PS1_CurrentDisplay->drawing_environment).tpage = GetTPage(1, 2, 0, 256);
        SetDrawEnv(
            &PS1_CurrentDisplay->field_0x60bc_0x660b[D_801F81B0 + 7].drawing_environment,
            &PS1_CurrentDisplay->drawing_environment
        );
        AddPrim(
            &PS1_CurrentDisplay->ordering_table[9],
            &PS1_CurrentDisplay->field_0x60bc_0x660b[D_801F81B0 + 7].drawing_environment
        );
    }
}
#endif

/* 18A1C 8013D21C -O2 -msoft-float */
void DISPLAY_BLACKBOX(u16 x, u16 y, u16 w, u16 h, u8 param_5, u8 is_fond)
{
    if (is_fond)
        display_blackboxborder(x, y, w, h, 255 - param_5);
    else
        display_blackbox(x, y, w, h, 255 - param_5);
}

/* 18A88 8013D288 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/draw/text_18118", display_text_sin);
#else
/*
PS1_CurrentDisplay accesses, duplication
no idea how to macro/inline the y calculation/ashr16 thing
*/
/* this would match, unsurprisingly */
#define display_text_sin_1 (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)

void display_text_sin(u8 *text, s16 in_x, s16 in_y, s16 temps, u8 font_size, u8 clut_x)
{
    s16 let_width;
    u8 sprite_ind;
    s16 unk_y_1;
    s16 unk_1;
    s16 space_width;
    s16 unk_x;
    s16 unk_y_2;
    s16 i;
    u8 let;
    Sprite *sprite;
    s16 unk_y_3;

    sprite_ind = 0;
    if (font_size == 2)
    {
        unk_y_1 = 15;
        unk_1 = 1;
        space_width = 8;
    }
    else if (font_size == 1)
    {
        unk_y_1 = 23;
        unk_1 = 3;
        space_width = 10;
    }
    else
    {
        unk_y_1 = 36;
        unk_1 = 3;
        space_width = 12;
    }

    unk_x = in_x;
    unk_y_2 = in_y;
    if (text[0] != 0) /* ??? */
    {
        i = 0;
        while (text[i] != 0)
        {
            let = text[i];
            if (let == '/')
            {
                unk_x = in_x - (calc_largmax_text(text, i, space_width, unk_1, font_size) >> 1);
                if (i > 1)
                    unk_y_2 += unk_y_1;
                sprite_ind = 0;
            }
            else if (let == ' ')
            {
                unk_x += space_width;
                sprite_ind = 0;
            }
            else
                sprite_ind = deter_num_let(let);

            if (sprite_ind != 0)
            {
                let_width = calc_let_Width(font_size, sprite_ind);
                calc_num_let_spr(font_size, &sprite_ind);
                /*
                tried to reduce duplication:
                using goto
                using fall-through with if (font_size == 2)
                using nested switch
                */
                switch (font_size)
                {
                case 0:
                case 1:
                    sprite = &alpha2.sprites[sprite_ind];
                    sprite->clut = GetClut(clut_x * 16 + 768, 492);
                    unk_y_3 = costab[(temps + (i << 5)) % ((s16) LEN(costab) - 1)];
                    draw_sprite(sprite, unk_x, (unk_y_2 - sprite->height) + ashr16(__builtin_abs(unk_y_3), 5), 0);
                    break;
                case 2:
                    sprite = &alpha.sprites[sprite_ind];
                    sprite->clut = GetClut(clut_x * 16 + 768, 492);
                    unk_y_3 = costab[(temps + (i << 5)) % ((s16) LEN(costab) - 1)];
                    draw_sprite(sprite, unk_x, (unk_y_2 - sprite->height) + ashr16(__builtin_abs(unk_y_3), 5), 0);
                    break;
                }

                if (let_shadow)
                {
                    PS1_PolygonIndexTable[PS1_PolygonIndexTableCount] = PS1_PolygonsCount;
                    PS1_PolygonIndexTableCount++;
                    SetSemiTrans(PS1_CurrentDisplay->polygons + PS1_PolygonsCount, true);
                    SetShadeTex(PS1_CurrentDisplay->polygons + PS1_PolygonsCount, false);

                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->r0 = 20;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->g0 = 20;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->b0 = 20;

                    PS1_CurrentDisplay->polygons[PS1_PolygonsCount].clut = sprite->clut;
                    getparam((s16) sprite->tpage); /* TODO: sprite tpage s16 maybe? */
                    PS1_CurrentDisplay->polygons[PS1_PolygonsCount].tpage = GetTPage(0, 0, PS1_TPage_x, PS1_TPage_y);

                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->u0 = sprite->page_x;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->v0 = sprite->page_y;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->u1 = sprite->page_x + sprite->width;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->v1 = sprite->page_y;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->u2 = sprite->page_x;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->v2 = sprite->page_y + sprite->height;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->u3 = sprite->page_x + sprite->width;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->v3 = sprite->page_y + sprite->height;

                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->x0 = unk_x + 5;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->y0 =
                        unk_y_2 - sprite->height + 5 +
                        ashr16(__builtin_abs(costab[(temps + (i << 5)) % ((s16) LEN(costab) - 1)]), 5);
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->x1 = unk_x + 5 + sprite->width;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->y1 =
                        unk_y_2 - sprite->height + 5 +
                        ashr16(__builtin_abs(costab[(temps + (i << 5)) % ((s16) LEN(costab) - 1)]), 5);
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->x2 = unk_x + 5;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->y2 =
                        sprite->height +
                        (unk_y_2 - sprite->height + 5 +
                        ashr16(__builtin_abs(costab[(temps + (i << 5)) % ((s16) LEN(costab) - 1)]), 5));
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->x3 = unk_x + 5 + sprite->width;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->y3 =
                        sprite->height +
                        (unk_y_2 - sprite->height + 5 +
                        ashr16(__builtin_abs(costab[(temps + (i << 5)) % ((s16) LEN(costab) - 1)]), 5));
                    AddPrim(
                        &PS1_CurrentDisplay->ordering_table[5],
                        PS1_CurrentDisplay->polygons + PS1_PolygonsCount
                    );
                    PS1_PolygonsCount++;
                }
                unk_x += let_width - unk_1;
            }
            i++;
        }
    }
}
#endif

/* 1925C 8013DA5C -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/draw/text_18118", display_text);
#else
/*
score of 346
stack size?
*/
void display_text(u8 *text, s16 in_x, s16 in_y, u8 font_size, u8 param_5)
{
    u8 sprite_ind;
    u8 sp28;
    s16 unk_y_1;
    s16 unk_1;
    s16 space_width;
    s16 sp48;
    Sprite *sprite;
    s16 unk_y_2;
    s16 var_s7;
    s16 let_width;
    u32 var_s6;
    s16 unk_x;
    u8 *var_s5;
    u8 let;
    u8 temp_a1_2;
    u8 clut_x;

    /*var_s1 = saved_reg_s1;
    var_s7 = saved_reg_s7;*/
    sprite_ind = 0;
    sp28 = param_5;
    switch (param_5 & 0x70)
    {
    case 0x10:
        var_s5 = D_801C3590;
        var_s7 = 6;
        break;
    case 0x20:
        var_s5 = D_801C3580;
        var_s7 = 6;
        break;
    case 0x30:
        var_s5 = D_801C3588;
        var_s7 = 6;
        break;
    case 0x40:
        var_s5 = D_801C3598;
        var_s7 = 6;
        break;
    case 0x50:
        var_s5 = D_801C35A0;
        var_s7 = 0x000A;
        break;
    case 0x60:
        var_s5 = D_801C35AC;
        var_s7 = 0x000E;
        break;
    case 0:
    default:
        var_s5 = null;
        break;
    }

    temp_a1_2 = sp28 & 0xF;
    var_s6 = temp_a1_2;
    if (sp28 & 0x80)
    {
        var_s6 = PS1_GlobalTimer;
    }
    sp28 = temp_a1_2;
    PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[0xA];
    if (font_size == 2)
    {
        unk_y_1 = 0x000F;
        unk_1 = 1;
        space_width = 8;
    }
    else if (font_size == 1)
    {
        unk_y_1 = 0x0017;
        unk_1 = 3;
        space_width = 0x000A;
    }
    else
    {
        unk_y_1 = 0x0024;
        unk_1 = 3;
        space_width = 0x000C;
    }
    unk_x = in_x;
    unk_y_2 = in_y;
    if (*text != 0)
    {
        sp48 = 0;
        do
        {
            let = text[(s16) sp48];
            if (let == '/')
            {
                unk_x = in_x - (calc_largmax_text(text, (s16) sp48, space_width, unk_1, font_size) >> 1);
                if ((s16) sp48 >= 2)
                {
                    unk_y_2 += unk_y_1;
                }
                sprite_ind = 0;
            }
            else if (let == ' ')
            {
                unk_x += space_width;
                sprite_ind = 0;
            }
            else
            {
                sprite_ind = deter_num_let(let);
            }
            if (sprite_ind != 0)
            {
                let_width = calc_let_Width(font_size, sprite_ind);
                calc_num_let_spr(font_size, &sprite_ind);
                if (var_s5 != null)
                {
                    clut_x = var_s5[var_s6 % var_s7];
                }
                else
                {
                    clut_x = sp28;
                }
                var_s6 += 1;

                switch (font_size)
                {
                case 0:
                case 1:
                    sprite = &alpha2.sprites[sprite_ind];
                    sprite->clut = GetClut((clut_x * 0x10) + 0x300, 0x000001EC);
                    draw_sprite(sprite, (s16) unk_x, unk_y_2 - sprite->height, 0U);
                    break;
                case 2:
                    sprite = &alpha.sprites[sprite_ind];
                    sprite->clut = GetClut((clut_x * 0x10) + 0x300, 0x000001EC);
                    draw_sprite(sprite, (s16) unk_x, unk_y_2 - sprite->height, 0U);
                    break;
                }

                if (let_shadow)
                {
                    PS1_PolygonIndexTable[PS1_PolygonIndexTableCount] = PS1_PolygonsCount;
                    PS1_PolygonIndexTableCount += 1;
                    SetSemiTrans(PS1_CurrentDisplay->polygons + PS1_PolygonsCount, 1);
                    SetShadeTex(PS1_CurrentDisplay->polygons + PS1_PolygonsCount, 0);

                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->r0 = 0x14;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->g0 = 0x14;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->b0 = 0x14;

                    PS1_CurrentDisplay->polygons[PS1_PolygonsCount].clut = sprite->clut;
                    getparam((s16) sprite->tpage); /* TODO: sprite tpage s16 maybe? */
                    PS1_CurrentDisplay->polygons[PS1_PolygonsCount].tpage = GetTPage(0, 0, PS1_TPage_x, PS1_TPage_y);

                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->u0 = sprite->page_x;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->v0 = sprite->page_y;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->u1 = sprite->page_x + sprite->width;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->v1 = sprite->page_y;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->u2 = sprite->page_x;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->v2 = sprite->page_y + sprite->height;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->u3 = sprite->page_x + sprite->width;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->v3 = sprite->page_y + sprite->height;

                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->x0 = unk_x + 5;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->y0 = (unk_y_2 - sprite->height) + 5;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->x1 = unk_x + (sprite->width + 5);
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->y1 = (unk_y_2 - sprite->height) + 5;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->x2 = unk_x + 5;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->y2 = unk_y_2 + 5;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->x3 = unk_x + (sprite->width + 5);
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->y3 = unk_y_2;
                    (PS1_CurrentDisplay->polygons + PS1_PolygonsCount)->y3 += 5; /* TODO: */

                    AddPrim(&PS1_CurrentDisplay->ordering_table[9], PS1_CurrentDisplay->polygons + PS1_PolygonsCount);
                    PS1_PolygonsCount = (u16) PS1_PolygonsCount + 1;
                }
                unk_x += let_width - unk_1;
            }
            sp48 = sp48 + 1;
        } while (text[sp48] != 0);
    }
}
#endif

/* 19990 8013E190 -O2 -msoft-float */
void display_box_text(TextToDisplay *txt)
{
    s16 x = txt->centered_x_pos;
    s16 y = txt->centered_y_pos;
    s16 w = txt->width;
    s16 h = txt->height;

    if (txt->field8_0x3d != 0 || txt->is_fond)
        DISPLAY_BLACKBOX(x - 3, y - 3, w + 6, h + 6, 254, txt->is_fond);

    display_text(txt->text, txt->x_pos, txt->y_pos, txt->font_size, txt->color);
}
