#include "draw/draw_hud.h"

#ifdef BSS_DEFS
GrpStar grp_stars[30];
s16 current_star;
Obj div_obj;
#endif

/* TODO: Display struct */
/*extern s32 PS1_CurrentDisplay;*/

/* 19A38 8013E238 -O2 */
/*? ClearImage(s32, ?, ?, ?);*/

void CLRSCR(void)
{
    ClearImage(&(PS1_CurrentDisplay->drawing_environment).clip, 0, 0, 0);
}

/* 19A6C 8013E26C -O2 */
/*? PS1_DrawSprite(Sprite *, s16, s16, ?);
u8 myRand(?, ? *);*/

void display_etoile(s32 in_x, s32 in_y)
{
    u8 loc_star_spr[8];
    GrpStar *temp;
    GrpStar *star;
    u8 rand_res;
    s16 draw_x;
    s16 draw_y;
    u8 sprite;

    __builtin_memcpy(loc_star_spr, PS1_star_spr, sizeof(PS1_star_spr));

    temp = &grp_stars[current_star];
    star = temp;
    star->timer++;
    if (star->timer > star->length)
    {
        rand_res = myRand(7);
        star->timer = 0;
        star->length = myRand(5);
        star->dist = rand_res;
        star->sprite_table_index = rand_res;
    }
    draw_x = star->dist + (in_x - xmap) - 8;
    draw_y = star->dist + (in_y - ymap);
    if (
        draw_x > 0 && SCREEN_WIDTH - draw_x > 0 &&
        draw_y > 0 && SCREEN_HEIGHT - draw_y > 0
    )
    {
        sprite = loc_star_spr[star->sprite_table_index];
        PS1_DrawSprite(
            &level.objects[poing_obj_id].sprites[sprite],
            draw_x,
            draw_y,
            0
        );
    }
    if (current_star < (s16) LEN(grp_stars))
        current_star++;
}

/* 19C08 8013E408
/*? Bresenham(void (*)(s32, s32), s16, s16, s16, s32, s32, s32);
? GET_SPRITE_POS(u8 *, ?, u16 *, u16 *, u16 *, u16 *);*/

void display_grp_stars(void)
{
    Obj *grapped;
    s16 x; s16 y; s16 w; s16 h;
    s16 cen_x;
    s16 grapped_x;

    if (ray.main_etat == 7 && (ray.flags & FLG(OBJ_ALIVE)))
    {
        current_star = 0;
        grapped = &level.objects[id_obj_grapped];
        GET_SPRITE_POS(&ray, 1, &x, &y, &w, &h);

        cen_x = x + (w >> 1);
        grapped_x = grapped->offset_bx + grapped->x_pos;
        Bresenham(
            display_etoile,
            cen_x, (s16) (y + (h >> 1) - 6),
            grapped_x, (s16) (grapped->offset_hy + grapped->y_pos),
            5,
            100
        );
    }
}

/* 19D20 8013E520 -O2 -msoft-float */
void DISPLAY_TEXT_FEE(void)
{
    u8 txt_fee;
    Obj *obj;
    TextToDisplay ttd;
    s16 cen_x;
    s16 obj_x;
    s16 marg_x;

    DISPLAY_BLACKBOX(0, 0, SCREEN_WIDTH, 20, 0, false);
    DISPLAY_BLACKBOX(0, 190, SCREEN_WIDTH, 50, 0, false);
    txt_fee = display_txt_fee;
    if (txt_fee != 0xff)
    {
        obj = &level.objects[png_or_fee_id];
        __builtin_memcpy(&ttd, &text_to_display[txt_fee], sizeof(TextToDisplay));
        if (ttd.text[0] != '\0')
        {
            if (obj->flags & FLG(OBJ_ALIVE))
            {
                obj->screen_y_pos = 220 - obj->offset_by;
                cen_x = ttd.centered_x_pos;
                obj_x = obj->offset_bx + obj->screen_x_pos;
                marg_x = 8;
                if (cen_x < obj_x - marg_x)
                {
                    if (cen_x + ttd.width > obj_x)
                    {
                        ttd.text[(s16) ((obj_x - (cen_x + marg_x)) / 7)] = '\0';
                        display_box_text(&ttd);
                    }
                    else
                        display_box_text(&ttd);
                }
                else if (cen_x + ttd.width <= obj_x)
                    display_box_text(&ttd);

                DISPLAY_BLACKBOX(
                    obj_x,
                    obj->screen_y_pos + obj->offset_by - 20,
                    30,
                    18,
                    0,
                    false
                );
                display2(obj);
            }
            else
                display_box_text(&ttd);
        }
    }

    txt_fee = old_txt_fee;
    if (txt_fee != 0xff)
    {
        __builtin_memcpy(&ttd, &text_to_display[txt_fee], sizeof(TextToDisplay));
        if (ttd.text[0] != '\0')
            display_box_text(&ttd);
    }
}

/* 1A04C 8013E84C -O2 */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/draw/draw_hud", DisplayJumellesNormal);
#else
/* do{}while(0); */
void DisplayJumellesNormal(void)
{
    s32 x_3;
    s32 x_5;
    s16 y_4;
    s32 y_1;
    s32 y_2;
    s32 y_3;
    s32 x_6;
    s32 x_4;
    s32 w_1;
    s32 w_h;
    s32 x_2;
    Sprite *sprite;
    s32 x_1;
    s32 width_2;
    s32 height_1;
    s32 width_1;
    s16 height_2;
    Sprite *sprites;

    sprites = mapobj[24].sprites;
    PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[9];
    sprite = &sprites[1];

    height_1 = sprite->height;
    width_1 = sprite->width;
    do
    {
        x_4 = 160 - width_1 * 2;
        PS1_DrawColoredSprite(sprite, x_4, 53, 1);
    } while (0);
    x_3 = x_4 + sprite->width;
    PS1_DrawColoredSprite(sprite, x_3, 53, 0);
    x_3 += sprite->width;
    PS1_DrawColoredSprite(sprite, x_3, 53, 1);
    x_3 += sprite->width;
    PS1_DrawColoredSprite(sprite, x_3, 53, 0);
    x_1 = (x_4 - height_1) + 5;
    x_3 += sprite->width;
    y_1 = height_1 + 48;
    PS1_DrawColoredSprite(sprite, x_1, y_1, 4);
    PS1_DrawColoredSprite(sprite, x_1, sprite->width + y_1, 6);
    x_2 = x_3 - 5;
    PS1_DrawColoredSprite(sprite, x_2, y_1, 7);
    y_2 = y_1 + sprite->width;
    PS1_DrawColoredSprite(sprite, x_2, y_2, 5);
    w_h = height_1 - 5;
    DISPLAY_BLACKBOX(x_1, 53, w_h, w_h, 0, 0);
    DISPLAY_BLACKBOX(x_3, 53, w_h, w_h, 0, 0);
    y_2 += sprite->width;
    DISPLAY_BLACKBOX(x_1, y_2, w_h, w_h, 0, 0);
    DISPLAY_BLACKBOX(x_3, y_2, w_h, w_h, 0, 0);
    y_3 = y_2 - 5;
    PS1_DrawColoredSprite(sprite, x_4, y_3, 3);
    x_5 = x_4 + sprite->width;
    PS1_DrawColoredSprite(sprite, x_5, y_3, 2);
    x_5 += sprite->width;
    PS1_DrawColoredSprite(sprite, x_5, y_3, 3);
    PS1_DrawColoredSprite(sprite, sprite->width + x_5, y_3, 2);

    height_2 = sprite->height;
    w_1 = x_4 - height_2;
    width_2 = sprite->width;
    x_6 = w_1 + (height_2 + width_2 * 2) * 2;
    y_4 = (width_2 + height_2) * 2 + 53;
    DISPLAY_BLACKBOX(0, 0, SCREEN_WIDTH, 53, 0, 0);
    DISPLAY_BLACKBOX(0, y_4 - 10, SCREEN_WIDTH, 250 - y_4, 0, 0);
    DISPLAY_BLACKBOX(0, 53, w_1 + 5, y_4 - 58, 0, 0);
    DISPLAY_BLACKBOX(x_6 - 5, 53, x_6 - w_1, y_4 - 58, 0, 0);
}
#endif

/* 1A338 8013EB38 -O2 */
/*? FUN_80139014(s16, s16, s16, s16, s32, s32);*/

void PS1_DisplayWorldMapBg1(s16 x1, s16 y1, s16 x2, s16 y2)
{
    PS1_DisplayWorldMapBg2(x1, y1, x2, y2, 130, SCREEN_WIDTH - x2);
}

/* 1A388 8013EB88 -O2 -msoft-float */
static inline s32 calc_y(s16 y)
{
    return (debut_options + y * (ecarty + 23) - 23);
}

void DISPLAY_SAVE_SPRITES(s16 x, s16 y)
{
    Obj *loc_mapobj;
    u8 num_lives;
    s32 pct;
    s16 sprite_ind_1;
    s16 sprite_ind_2;
    s16 sprite_ind_3;

    loc_mapobj = mapobj;
    num_lives = loadInfoRay[y].num_lives;
    sprite_ind_1 = ((s32) num_lives / 10) + 28;
    sprite_ind_2 = (num_lives % 10) + 28;
    display_sprite(&div_obj, 27, x, calc_y(y), 0);
    x += div_obj.sprites[27].width;
    display_sprite(&div_obj, sprite_ind_1, x, calc_y(y), 0);
    x += div_obj.sprites[sprite_ind_1].width;
    display_sprite(&div_obj, sprite_ind_2, x, calc_y(y), 0);
    x = x + div_obj.sprites[28].width + 10;

    sprite_ind_1 = (loadInfoRay[y].num_continues % 10) + 28;
    display_sprite(loc_mapobj, 57, x, calc_y(y), 0);
    x += loc_mapobj->sprites[57].width;
    display_sprite(&div_obj, sprite_ind_1, x, calc_y(y), 0);

    pct = loadInfoRay[y].num_cages * 100 / 102;
    sprite_ind_1 = ((s16) pct / 100) + 28;
    sprite_ind_2 = ((s16) pct / 10 % 10) + 28;
    sprite_ind_3 = ((s16) pct % 10) + 28;
    x = x + div_obj.sprites[37].width + 10;
    display_sprite(&div_obj, sprite_ind_1, x, calc_y(y), 0);
    x += div_obj.sprites[sprite_ind_1].width;
    display_sprite(&div_obj, sprite_ind_2, x, calc_y(y), 0);
    x += div_obj.sprites[sprite_ind_2].width;
    display_sprite(&div_obj, sprite_ind_3, x, calc_y(y), 0);
    display_text(s__801cef84, (s16) (x + div_obj.sprites[sprite_ind_3].width), debut_options + (y * (ecarty + 23)), 1, colour);
}

/* 1A8C0 8013F0C0 -O2 */
/*? display_sprite(Obj *, ?, s32, s32, s32);*/

void DISPLAY_SAVE_POING(void)
{
    Obj *obj;
    s16 temp;

    obj = mapobj;
    display_sprite(obj, 2, 10, debut_options + (positiony - 1) * (ecarty + 23) - 23, 1);
    temp = 11;
    display_sprite(obj, 2, (positionx2 - 1) * 100, debut_sortie - ((obj->sprites[2].height >> 1) + temp), 1);
    if (fichier_a_copier != 0)
        display_sprite(obj, 1, 10, debut_options + (fichier_a_copier - 1) * (ecarty + 23) - 23, 1);
}

/* 1A9D8 8013F1D8 -O2 -msoft-float */
void display_time(s16 time)
{
    Obj *sbar_obj;
    u8 text[24];
    u8 nb_wiz_text[8];
    s32 time_div;
    u32 col;
    u32 col_add;

    sbar_obj = &level.objects[sbar_obj_id];
    if (time != -2)
    {
        if (D_801CF018 == -1)
        {
            display_text(s_time_801cef88, 268, 202, 2, 7);
            time_div = time / 60;
            display_sprite(sbar_obj, (time_div / 10) + 28, 270, 204, 0);
            display_sprite(sbar_obj, (time_div % 10) + 28, 285, 204, 0);
        }
        if (map_time < 0x65)
        {
            __builtin_memcpy(text, s__801cef90, sizeof(s__801cef90));
            ray.flags &= ~FLG(OBJ_ACTIVE);
#ifdef PLATFORM_PSYZ
            PS1_itoa(nb_wiz, (u8*)&nb_wiz_text, 0xA);
#else
            PS1_itoa(nb_wiz, &nb_wiz_text, 0xA);
#endif
            strcat(text, nb_wiz_text);
            strcat(text, " tings to get/");
            if (horloge[8] < 4)
            {
                col = PS1_TingsToGet_Col;
                col_add = PS1_TingsToGet_ColAdd;
                PS1_TingsToGet_Col = col + col_add;
                if (PS1_TingsToGet_Col >= 6)
                {
                    PS1_TingsToGet_ColAdd *= -1;
                    PS1_TingsToGet_Col = 5;
                }
                else if (PS1_TingsToGet_Col == 0)
                {
                    PS1_TingsToGet_ColAdd *= -1;
                    PS1_TingsToGet_Col = 1;
                }

                if (D_801CF018 == -1)
                    display_text(text, 160, 120, 2, PS1_TingsToGet_Col);
            }
        }
        else if (map_time - 121 < 40U)
        {
            __builtin_memcpy(text, s_go__801cef94, sizeof(s_go__801cef94));
            display_text(text, 160, 120, 0, 8);
        }
    }
}

#ifdef PLATFORM_PSYZ
#define IMAGE_CAST (u_long *)
#else
#define IMAGE_CAST
#endif
/* 1AC60 8013F460 -O2 */
void PS1_LoadPts(void)
{
    u8 image [250];
    RECT rect;
    u8 *pixel_1;
    u8 *pixel_2;
    s32 i;
    
    rect.x = SCREEN_WIDTH; rect.y = 0; rect.w = 40; rect.h = 8;
    ClearImage(&rect, 0, 0, 0);
    i = 63;
    pixel_1 = image + i;
    while (i >= 0)
    {
        *pixel_1 = 0;
        i--;
        pixel_1--;
    }

    rect.w = 4;
    image[1] = 4; image[8] = 5;
    LoadImage(&rect, IMAGE_CAST&image);
    DrawSync(0);

    image[0] = 6; image[8] = 7; image[1] = 7; image[9] = 8;
    rect.x = rect.x + rect.w;
    LoadImage(&rect, IMAGE_CAST&image);
    DrawSync(0);
    
    image[0] = 0; image[17] = 6; image[10] = 6; image[8] = 6;
    image[1] = 6; image[9] = 8;
    rect.x = rect.x + rect.w;
    LoadImage(&rect, IMAGE_CAST&image);
    DrawSync(0);

    image[10] = 2; image[1] = 2; image[17] = 3; image[8]= 3;
    image[2] = 4; image[9] = 5;
    rect.x = rect.x + rect.w;
    LoadImage(&rect, IMAGE_CAST&image);
    DrawSync(0);

    image[8] = 0; image[1] = 0; image[11] = 2; image[2] = 2;
    image[18] = 3; image[9] = 3; image[3] = 3; image[25] = 4;
    image[16] = 4; image[10] = 4; image[17] = 5; image[24] = 6;
    rect.x = rect.x + rect.w;
    LoadImage(&rect, IMAGE_CAST&image);
    DrawSync(0);

    image[3] = 0; image[24] = 0; image[26] = 6; image[25] = 6;
    image[19] = 6; image[16] = 6; image[11] = 6; image[8] = 6;
    image[2] = 6; image[1] = 6; image[18] = 7; image[17] = 7;
    image[10] = 7; image[9] = 7;
    rect.x = rect.x + rect.w;
    LoadImage(&rect, IMAGE_CAST&image);
    DrawSync(0);

    image[26] = 6; image[25] = 6; image[19] = 6; image[16] = 6;
    image[11] = 6; image[8] = 6; image[2] = 6; image[1] = 6;
    image[18] = 8; image[17] = 8; image[10] = 8; image[9] = 8;
    rect.x = rect.x + rect.w;
    LoadImage(&rect, IMAGE_CAST&image);
    DrawSync(0);

    image[8] = 0; image[1] = 0; image[43] = 6; image[42] = 6;
    image[29] = 6; image[24] = 6; image[21] = 6; image[16] = 6;
    image[3] = 6; image[2] = 6; image[36] = 7; image[33] = 7;
    image[12] = 7; image[9] = 7; image[20] = 8; image[19] = 8;
    image[18] = 8; image[17] = 8; image[11] = 8; image[10] = 8;
    image[35] = 8; image[34] = 8; image[28] = 8; image[27] = 8;
    image[26] = 8; image[25] = 8;
    rect.x = rect.x + rect.w;
    LoadImage(&rect, IMAGE_CAST&image);
    DrawSync(0);
    i = 63;
    pixel_2 = image + i;
    rect.x = rect.x + rect.w;
    while (i > -1)
    {
        *pixel_2 = 0;
        i--;
        pixel_2--;
    }

    image[8] = 12; image[1] = 12; image[26] = 80; image[25] = 80;
    image[19] = 80; image[16] = 80; image[11] = 80; image[2] = 80;
    image[9] = 14; image[18] = 9; image[17] = 10; image[10] = 10;
    LoadImage(&rect, IMAGE_CAST&image);
    DrawSync(0);
}
#undef IMAGE_CAST

/* modulo but no tge... */
/* 1AFFC 8013F7FC -O2 */
void DISPLAY_CONTINUE_SPR(void)
{
    u32 dig_0;
    u32 dig_1;

    dig_0 = nb_continue / 10;
    dig_1 = nb_continue % 10;
    if (loop_timing == 0x00FF)
        display_text(s_the_end_801cef9c, 177, 182, 2, 0);
    else
    {
        display_sprite(&div_obj, dig_0 + 28, 184, 162, 0);
        display_sprite(&div_obj, dig_1 + 28, 199, 162, 0);
    }
    display2(&ray);
    display2(&clock_obj);
    if (mapobj->flags & FLG(OBJ_ALIVE))
        display2(mapobj);
}

/* 1B0F8 8013F8F8 -O2 */
/*? display_sprite(Obj *, ?, ?, s32, s32);*/

void PS1_PromptCardDisplayPoing(void)
{
    display_sprite(mapobj, 2, 120, ((PS1_positiony_mc - 1) * 22) + 157, 1);
}

/* 1B150 8013F950 -O2 */
/*? display_sprite(Obj *, ?, s32, s32, s32);*/

void DISPLAY_OPTIONS_POING(void)
{
    Obj *obj;

    obj = mapobj;
    if (position == 7)
        display_sprite(obj, 2, text_to_display[7].centered_x_pos - 35, PS1_display_y1 - 14, 1);
    else
        display_sprite(obj, 2, 20, debut_sortie + position * (PS1_display_y2 + 0xF) - 0xF, 1);
}
