#include "world_map_677C0.h"

const u8 s_password_8012ba1c[] = "/password/";
const u8 s_the_dream_forest_8012ba28[] = "/the dream forest/";
const u8 s_band_land_8012ba3c[] = "/band land/";
const u8 s_blue_mountains_8012ba48[] = "/blue mountains/";
const u8 s_picture_city_8012ba5c[] = "/picture city/";
const u8 s_the_cave_of_skops_8012ba6c[] = "/the cave of skops/";
const u8 s_candy_chateau_8012ba80[] = "/candy chateau/";

#ifdef BSS_DEFS
Obj *mapobj;
Obj raylittle;
u8 chemin_percent;
u8 dir_on_wldmap;
s16 xmapinit;
s16 ymapinit;
s16 xwldmapsave;
s16 ywldmapsave;
u8 nouvelle_partie;
u8 dans_la_map_monde;
u8 Nb_total_cages;
u8 D_801F3EA0;
#endif

/* 677C0 8018BFC0 -O2 */
static void calc_obj_pos_map(Obj *obj)
{
    obj->screen_x_pos = obj->x_pos - xmap + 52;
    obj->screen_y_pos = obj->y_pos - ymap + 55;
}

/* 677F4 8018BFF4 -O2 -msoft-float */
static void DO_SCROLL_MAP(s16 h_speed, s16 v_speed)
{
    ymap += v_speed;
    xmap += h_speed;

    if (xmap < scroll_start_x)
    {
        xmap = scroll_start_x;
        dhspeed = 0;
    }
    else if (xmap > scroll_end_x)
    {
        xmap = scroll_end_x;
        dhspeed = 0;
    }
    if (ymap < scroll_start_y)
    {
        ymap = scroll_start_y;
        dvspeed = 0;
    }
    else if (ymap > scroll_end_y)
    {
        ymap = scroll_end_y;
        dvspeed = 0;
    }
    calc_obj_pos_map(&ray);
}

/* 678DC 8018C0DC -O2 */
void TEST_DISPLAY_PTS_WAY(s16 from, s16 to, s16 from_x, s16 from_y)
{
    if (to != from)
    {
        if (!(t_world_info[to].has_drawn_path))
        {
            if (t_world_info[to].is_unlocked)
            {
                DISPLAY_PTS_TO_PLAN2(
                    from_x,
                    from_y,
                    t_world_info[to].x_pos,
                    t_world_info[to].y_pos,
                    100
                );
            }
            else if (t_world_info[to].is_unlocking)
            {
                DISPLAY_PTS_TO_PLAN2(
                    from_x,
                    from_y,
                    t_world_info[to].x_pos,
                    t_world_info[to].y_pos,
                    chemin_percent
                );
            }
        }
    }
}

/* 679D4 8018C1D4 -O2 -msoft-float */
void DISPLAY_PTS_WAY(void)
{
    s16 i;
    WorldInfo *cur_wi;
    s16 x_pos; s16 y_pos;

    i = 0;
    cur_wi = &t_world_info[i];
    while (i < (s16) LEN(t_world_info))
    {
        cur_wi->has_drawn_path = false;
        i++;
        cur_wi++;
    }

    i = 0;
    cur_wi = &t_world_info[i];
    while (i < (s16) LEN(t_world_info))
    {
        x_pos = cur_wi->x_pos;
        y_pos = cur_wi->y_pos;
        if (cur_wi->is_unlocked)
        {
            TEST_DISPLAY_PTS_WAY(i, cur_wi->index_up, x_pos, y_pos);
            TEST_DISPLAY_PTS_WAY(i, cur_wi->index_down, x_pos, y_pos);
            TEST_DISPLAY_PTS_WAY(i, cur_wi->index_right, x_pos, y_pos);
            TEST_DISPLAY_PTS_WAY(i, cur_wi->index_left, x_pos, y_pos);
            cur_wi->has_drawn_path = true;
        }
        i++;
        cur_wi++;
    }
}

/* 67B0C 8018C30C -O2 -msoft-float */
void DISPLAY_PLAT_WAY(void)
{
    s16 i = 0;
    WorldInfo *cur_wi = &t_world_info[i];
    Obj *cur_obj = &mapobj[i];

    while (i < (s16) LEN(t_world_info))
    {
        if (
            (cur_wi->is_unlocked || i == 17) &&
            cur_obj->screen_x_pos + (u32) cur_obj->offset_bx - 37 <= 256 &&
            cur_obj->screen_y_pos + (u32) cur_obj->offset_by - 46 <= 150
        )
            DISPLAY_PLATEAU(cur_obj);

        cur_wi++;
        cur_obj++;
        i++;
    }
}

/* 67BE8 8018C3E8 -O2 -msoft-float */
void DO_MEDAILLONS(void)
{
    s16 i;
    Obj *cur_obj;
    WorldInfo *cur_wi;
    u8 nb_cages;
    u8 flag_set;

    if (chemin_percent <= 99 && horloge[2] != 0)
        chemin_percent++;

    i = 0;
    cur_obj = &mapobj[i];
    cur_wi = &t_world_info[i];
    while (i < (s16) LEN(t_world_info))
    {
        calc_obj_pos_map(cur_obj);
        if (cur_wi->is_unlocking && chemin_percent >= 99)
        {
            cur_wi->is_unlocking = false;
            cur_wi->is_unlocked = true;
            set_sub_etat(cur_obj, 46);
        }

        if (
            i == 17 &&
            !(cur_obj->sub_etat == 59 || cur_obj->sub_etat == 46) &&
            cur_wi->is_unlocked
        )
            set_sub_etat(cur_obj, 59);
        else if (
            (i == 18 || i == 19 || i == 20 || i == 21 || i == 22 || i == 23) &&
            !(cur_obj->sub_etat == 58 || cur_obj->sub_etat == 46) &&
            cur_wi->is_unlocked
        )
            set_sub_etat(cur_obj, 58);
        else
        {
            nb_cages = cur_wi->nb_cages;
            if (nb_cages > 5 && cur_obj->sub_etat == 51 && EOA(cur_obj))
                set_sub_etat(cur_obj, 52);
            else if (nb_cages > 4 && cur_obj->sub_etat == 50 && EOA(cur_obj))
                set_sub_etat(cur_obj, 51);
            else if (nb_cages > 3 && cur_obj->sub_etat == 49 && EOA(cur_obj))
                set_sub_etat(cur_obj, 50);
            else if (nb_cages > 2 && cur_obj->sub_etat == 48 && EOA(cur_obj))
                set_sub_etat(cur_obj, 49);
            else if (nb_cages > 1 && cur_obj->sub_etat == 47 && EOA(cur_obj))
                set_sub_etat(cur_obj, 48);
        }
        DO_ANIM(cur_obj);
        cur_obj++;
        i++;
        cur_wi++;
    }
}

/* 68220 8018CA20 -O2 */
/*? INIT_TXT_BOX(s8 *);
? PS1_GenerateAndDisplayPassword();*/

void INIT_LEVEL_STAGE_NAME(void)
{
    if (t_world_info[num_world_choice].world == 7 && NBRE_SAVE == 0)
        PS1_GenerateAndDisplayPassword();
    else
        __builtin_memcpy(&text_to_display[0].text, t_world_info[num_world_choice].level_name, sizeof(text_to_display[0].text));

    text_to_display[0].font_size = 2;
    text_to_display[0].x_pos = 450;
    text_to_display[0].y_pos = 220;
    text_to_display[0].is_fond = false;
    text_to_display[0].field8_0x3d = true;
    INIT_TXT_BOX(text_to_display);
    text_to_display[0].centered_y_pos -= 6;
    text_to_display[0].width += 10;
    text_to_display[0].height += 6;
    text_to_display[0].color = t_world_info[num_world_choice].color;
}

/* 683FC 8018CBFC -O2 */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/world_map_677C0", INIT_WORLD_STAGE_NAME);
#else
/* casts? */
void INIT_WORLD_STAGE_NAME(void)
{
    u8 new_color;
    u8 save_text[80];

    switch (t_world_info[num_world_choice].world)
    {
    case 7:
        new_color = t_world_info[num_world_choice].color;
        switch (fichier_selectionne)
        {
        case 0:
            if (NBRE_SAVE != 0)
                __builtin_memcpy(text_to_display[2].text, s___801cf0a4, sizeof(text_to_display[2].text));
            else
                __builtin_memcpy(text_to_display[2].text, s_password_8012ba1c, sizeof(s_password_8012ba1c));
            break;
        case 1:
            *(u16 *) &save_text[0] = *(u16 *) &s__801cf0a8[0];
            strcat(save_text, save_ray[fichier_selectionne]);
            strcat(save_text, s__801cf0a8);
            __builtin_memcpy(text_to_display[2].text, save_text, sizeof(text_to_display[2].text));
            break;
        case 2:
            *(u16 *) &save_text[0] = *(u16 *) &s__801cf0a8[0];
            strcat(save_text, save_ray[fichier_selectionne]);
            strcat(save_text, s__801cf0a8);
            __builtin_memcpy(text_to_display[2].text, save_text, sizeof(text_to_display[2].text));
            break;
        case 3:
            *(u16 *) &save_text[0] = *(u16 *) &s__801cf0a8[0];
            strcat(save_text, save_ray[fichier_selectionne]);
            strcat(save_text, s__801cf0a8);
            __builtin_memcpy(text_to_display[2].text, save_text, sizeof(text_to_display[2].text));
            break;
        }
        break;
    case 1:
        __builtin_memcpy(text_to_display[2].text, s_the_dream_forest_8012ba28, sizeof(text_to_display[2].text));
        new_color = 7;
        break;
    case 2:
        __builtin_memcpy(text_to_display[2].text, s_band_land_8012ba3c, sizeof(text_to_display[2].text));
        new_color = 4;
        break;
    case 3:
        __builtin_memcpy(text_to_display[2].text, s_blue_mountains_8012ba48, sizeof(text_to_display[2].text));
        new_color = 13;
        break;
    case 4:
        __builtin_memcpy(text_to_display[2].text, s_picture_city_8012ba5c, sizeof(text_to_display[2].text));
        new_color = 0;
        break;
    case 5:
        __builtin_memcpy(text_to_display[2].text, s_the_cave_of_skops_8012ba6c, sizeof(text_to_display[2].text));
        new_color = 2;
        break;
    case 6:
        __builtin_memcpy(text_to_display[2].text, s_candy_chateau_8012ba80, sizeof(text_to_display[2].text));
        new_color = 1;
        break;
    }

    text_to_display[2].font_size = 1;
    text_to_display[2].x_pos = 450;
    text_to_display[2].y_pos = 40;
    text_to_display[2].is_fond = false;
    text_to_display[2].field8_0x3d = true;
    text_to_display[2].color = new_color;
    INIT_TXT_BOX(&text_to_display[2]);
    text_to_display[2].width += 10;
    text_to_display[2].height += 2;
}
const u8 rodata_INIT_WORLD_STAGE_NAME[4] = {};
#endif

/* 68CB8 8018D4B8 -O2 */
void INIT_STAGE_NAME(void)
{
    INIT_TEXT_TO_DISPLAY();
    INIT_LEVEL_STAGE_NAME();
    INIT_WORLD_STAGE_NAME();

    text_to_display[1].x_pos = 160;
    text_to_display[1].y_pos = 250;
    text_to_display[1].field8_0x3d = false;
    text_to_display[1].is_fond = false;

    text_to_display[3].x_pos = 160;
    text_to_display[3].y_pos = -50;
    text_to_display[3].field8_0x3d = false;
    text_to_display[3].is_fond = false;
}

/* 68D34 8018D534 -O2 */
/*? INIT_LEVEL_STAGE_NAME(s32, s32, ? *, void *);
? INIT_WORLD_STAGE_NAME(s32, s32, ? *, void *);*/

void CHANGE_STAGE_NAMES(void)
{
    __builtin_memcpy(&text_to_display[1], &text_to_display[0], sizeof(TextToDisplay));
    INIT_LEVEL_STAGE_NAME();
    if (t_world_info[num_world_choice].world != t_world_info[old_num_world].world)
    {
        __builtin_memcpy(&text_to_display[3], &text_to_display[2], sizeof(TextToDisplay));
        INIT_WORLD_STAGE_NAME();
    }
}

/* 68EF4 8018D6F4 -O2 */
void PS1_CardDisplayPassword(void)
{
    u8 color;

    __builtin_memcpy(&text_to_display[1], &text_to_display[0], sizeof(TextToDisplay));
    __builtin_memcpy(&text_to_display[3], &text_to_display[2], sizeof(TextToDisplay));

    PS1_GenerateAndDisplayPassword();

    color = t_world_info[num_world_choice].color;
    text_to_display[2].font_size = 1;
    text_to_display[2].color = color;
    text_to_display[2].x_pos = 450;
    text_to_display[2].y_pos = 40;
    text_to_display[2].is_fond = false;
    text_to_display[2].field8_0x3d = 0;
    INIT_TXT_BOX(&text_to_display[2]);

    text_to_display[0].font_size = 2;
    text_to_display[0].x_pos = 450;
    text_to_display[0].y_pos = 220;
    text_to_display[0].is_fond = false;
    text_to_display[0].field8_0x3d = 0;
    text_to_display[2].width += 10;
    text_to_display[2].height += 2;
    INIT_TXT_BOX(&text_to_display[0]);

    text_to_display[0].centered_y_pos -= 6;
    text_to_display[0].width += 10;
    text_to_display[0].height += 6;
    text_to_display[0].color = t_world_info[num_world_choice].color;
    text_to_display[1].x_pos = 160;
    text_to_display[1].y_pos = 250;
    text_to_display[1].field8_0x3d = 0;
    text_to_display[1].is_fond = false;
    text_to_display[3].x_pos = 160;
    text_to_display[3].y_pos = -50;
    text_to_display[3].field8_0x3d = 0;
    text_to_display[3].is_fond = false;
}

/* 691E0 8018D9E0 -O2 */
void DO_STAGE_NAMES(void)
{
    if (text_to_display[0].x_pos > 160)
    {
        text_to_display[0].x_pos -= 6;
        text_to_display[0].centered_x_pos -= 6;
    }
    if (text_to_display[2].x_pos > 160)
    {
        text_to_display[2].x_pos -= 6;
        text_to_display[2].centered_x_pos -= 6;
    }
    if (text_to_display[1].y_pos < 320)
    {
        text_to_display[1].y_pos += 2;
        text_to_display[1].centered_y_pos += 2;
    }
    if (text_to_display[3].y_pos > -60)
    {
        text_to_display[3].y_pos -= 2;
        text_to_display[3].centered_y_pos -= 2;
    }
}

/* 692CC 8018DACC -O2 -msoft-float */
void INIT_WORLD_INFO(void)
{
    s16 i;

    if (D_801F3EA0)
    {
        for (i = 0; i < (s16) LEN(t_world_info); i++)
        {
            t_world_info[i].is_unlocked = true;
            t_world_info[i].is_unlocking = false;
        }
    }
    num_world = 0;
    num_level = 0;
    new_world = true;
    new_level = true;
    world_index = 0;
    xwldmapsave = 0;
    ywldmapsave = 158;
    dir_on_wldmap = 1;
    You_Win = false;
    fin_du_jeu = false;
    INIT_PASTILLES_SAUVE();
}

/* 693B4 8018DBB4 -O2 */
void INIT_LITTLE_RAY(void)
{
    __builtin_memcpy(&raytmp, &ray, sizeof(Obj));
    ray.scale = 0x100;
    ray.sprites = raylittle.sprites;
    ray.img_buffer = raylittle.img_buffer;
}

/* 69428 8018DC28 -O2 */
void RESTORE_RAY(void)
{
    ray.scale = 0;
    ray.sprites = raytmp.sprites;
    ray.img_buffer = raytmp.img_buffer;
    ray.nb_sprites = raytmp.nb_sprites;
}

/* 69468 8018DC68 -O2 -msoft-float */
void INIT_CHEMIN(void)
{
    u8 world_ind;
    s16 i;
    Obj *cur_obj;

    PROC_EXIT = false;
    dans_la_map_monde = true;
    gele = 0;

    if (ModeDemo == 0)
    {
        new_world = false;
        num_world_choice = world_index;
    }
    old_num_world = num_world_choice;

    INIT_LITTLE_RAY();
    set_main_and_sub_etat(&ray, 0, 0);
    ray.x_pos = t_world_info[num_world_choice].x_pos - ray.offset_bx + 4;
    ray.y_pos = t_world_info[num_world_choice].y_pos - ray.offset_by + 8;
    ray.speed_x = 0;
    ray.speed_y = 0;
    set_zoom_mode(0);
    chemin_percent = 0;
    Nb_total_cages = 0;

    world_ind = 0; /* why does this exist? */
    i = 0;
    cur_obj = &mapobj[world_ind];
    while (i < (s16) LEN(t_world_info))
    {
        cur_obj->type = TYPE_MEDAILLON;
        cur_obj->init_x_pos = t_world_info[world_ind].x_pos - 78;
        cur_obj->init_y_pos = t_world_info[world_ind].y_pos - 64;
        cur_obj->init_main_etat = 5;

        if (!(t_world_info[world_ind].is_unlocking))
        {
            if (t_world_info[world_ind].nb_cages != 0)
            {
                Nb_total_cages += t_world_info[world_ind].nb_cages;

                if (t_world_info[world_ind].nb_cages == 6)
                    cur_obj->init_sub_etat = 52;
                else
                    cur_obj->init_sub_etat = 47;
            }
            else
            {
                if (i == 17)
                    cur_obj->init_sub_etat = cur_obj->sub_etat = 59;
                else
                    cur_obj->init_sub_etat = 39;
            }
        }
        else
            cur_obj->init_sub_etat = 46;

        cur_obj->scale = 0;
        cur_obj->offset_bx = 80;
        cur_obj->offset_by = 64;
        obj_init(cur_obj);
        calc_obj_pos_map(cur_obj);
        cur_obj->anim_frame =
            i % cur_obj->animations[
                cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].anim_index
            ].frames_count;

        world_ind++;
        MIN_2(world_ind, LEN(t_world_info));
        cur_obj++;
        i++;
    }

    if (!(t_world_info[17].is_unlocked) && Nb_total_cages >= 102)
        t_world_info[17].is_unlocking = true;

    scroll_end_x = 156;
    scroll_end_y = 158;
    scroll_x = -1;
    scroll_y = -1;
    special_ray_mov_win_x_left = 30;
    special_ray_mov_win_x_right = 30;
    scroll_start_x = 0;
    scroll_start_y = 0;
    xmapinit = xmap;
    ymapinit = ymap;
    xmap = xwldmapsave;
    ymap = ywldmapsave;
    ray.flags = ray.flags & ~FLG(OBJ_FLIP_X) | (dir_on_wldmap & 1) << OBJ_FLIP_X;
    INIT_PASTILLES_SAUVE();
    INIT_STAGE_NAME();
    if (nouvelle_partie)
    {
        if (NBRE_SAVE != 0)
            SaveGameOnDisk(fichier_selectionne);
        nouvelle_partie = false;
    }
}

/* https://decomp.me/scratch/6ivxi PSYQ3.3 (gcc 2.6.0 + aspsx 2.21) -O1 */
/* 698B4 8018E0B4 -O2 */
void RESPOND_TO_UP(void)
{
    num_world_choice = t_world_info[num_world_choice].index_up;
}

/* 698F0 8018E0F0 -O2 */
void RESPOND_TO_DOWN(void)
{
    num_world_choice = t_world_info[num_world_choice].index_down;
}

/* 6992C 8018E12C -O2 */
void RESPOND_TO_RIGHT(void)
{
    num_world_choice = t_world_info[num_world_choice].index_right;
}

/* 69968 8018E168 -O2 */
void RESPOND_TO_LEFT(void)
{
    num_world_choice = t_world_info[num_world_choice].index_left;
}

/* 699A4 8018E1A4 -O2 */
void move_ray_map(void)
{
    h_scroll_speed = ray.speed_x;
    v_scroll_speed = ray.speed_y;
    ray.x_pos += ray.speed_x;
    decalage_en_cours = ray.speed_x;
    ray.y_pos += ray.speed_y;
}

/* 699FC 8018E1FC -O2 -msoft-float */
void DO_RAYMAN_IN_WLD_MAP(void)
{
    s16 diff_x;
    s16 diff_y;
    s16 unk_0;
    s16 unk_1;
    s32 unk_2;
    s16 unk_3;
    s32 unk_4;
    s16 unk_5;
    Obj *unk_6;

    if (num_world_choice == old_num_world)
    {
        if (
            (s16) but0pressed(0) || (s16) but1pressed(0) ||
            (s16) but2pressed(0) || (s16) but3pressed(0)
        )
        {
            if (
                num_world_choice == 18 || num_world_choice == 19 ||
                num_world_choice == 20 || num_world_choice == 21 ||
                num_world_choice == 22 || num_world_choice == 23
            )
            {
                if (
                    NBRE_SAVE != 0 &&
                    t_world_info[num_world_choice].level_name == PTR_s_save_game_801c353c
                )
                {
                    if (PS1_PromptSaveWldMap())
                    {
                        SaveGameOnDisk(fichier_selectionne);
                        PASTILLES_SAUVE_SAVED(num_world_choice);
                        CHANGE_STAGE_NAMES();
                    }
                    else
                        PS1_CardDisplayPassword();
                }
            }
            else
                new_world = true;
        }
        else if (rightjoy(0))
            RESPOND_TO_RIGHT();
        else if (leftjoy(0))
            RESPOND_TO_LEFT();
        else if (downjoy(0))
            RESPOND_TO_DOWN();
        else if (upjoy(0))
            RESPOND_TO_UP();

        if (num_world_choice != old_num_world)
        {
            if (t_world_info[num_world_choice].is_unlocked)
            {
                ray.timer = 0;
                set_main_and_sub_etat(&ray, 1, 0);
                CHANGE_STAGE_NAMES();
            }
            else
                num_world_choice = old_num_world;
        }
    }
    else
    {
        diff_x = t_world_info[num_world_choice].x_pos - t_world_info[old_num_world].x_pos;
        diff_y = t_world_info[num_world_choice].y_pos - t_world_info[old_num_world].y_pos;
        if (diff_x < 0)
            ray.flags &= ~FLG(OBJ_FLIP_X);
        else
            ray.flags |= FLG(OBJ_FLIP_X);

        if (diff_x != 0 && diff_y != 0)
        {
            if (__builtin_abs(diff_y) > __builtin_abs(diff_x))
            {
                unk_0 = __builtin_abs(ray.timer * diff_x / diff_y);
                unk_1 = ray.timer;
            }
            else
            {
                unk_1 = __builtin_abs(ray.timer * diff_y / diff_x);
                unk_0 = ray.timer;
            }
        }
        else if (diff_x == 0)
            unk_1 = ray.timer;
        else if (diff_y == 0)
            unk_0 = ray.timer;
        ray.timer++;

        unk_2 = unk_0;
        if (diff_x >= 0)
            unk_3 = -(diff_x > 0) & unk_2;
        else
            unk_3 = -unk_2;
        unk_4 = unk_1;
        if (diff_y >= 0)
            unk_5 = -(diff_y > 0) & unk_4;
        else
            unk_5 = -unk_4;

        ray.speed_x = t_world_info[old_num_world].x_pos + unk_3 - ray.offset_bx - ray.x_pos;
        ray.speed_y = t_world_info[old_num_world].y_pos + unk_5 - ray.offset_by - (s16) (ray.y_pos - 8);
        if (
            __builtin_abs(unk_0) >= __builtin_abs(diff_x) &&
            __builtin_abs(unk_1) >= __builtin_abs(diff_y)
        )
        {
            old_num_world = num_world_choice;
            if (ray.main_etat != 0)
            {
                set_main_and_sub_etat(&ray, 0, 0);
                ray.speed_x = 0;
                ray.speed_y = 0;
                ray.x_pos = t_world_info[num_world_choice].x_pos - ray.offset_bx;
                ray.y_pos = t_world_info[num_world_choice].y_pos - ray.offset_by + 8;
            }
        }
    }

    move_ray_map();
    calc_obj_pos_map(&ray);
    unk_6 = &ray; /* TODO: clean up somehow */
    set_proj_center(ray.screen_x_pos + ray.offset_bx, ray.screen_y_pos + ray.offset_by);
    DO_ANIM(unk_6);
}

/* 6A070 8018E870 -O2 */
void DO_CHEMIN(void)
{
    horloges();
    DO_RAYMAN_IN_WLD_MAP();
    DO_MEDAILLONS();
    recale_ray_pos();
    DO_SCROLL_MAP(h_scroll_speed, v_scroll_speed);
    DO_STAGE_NAMES();
}

/* 6A0C8 8018E8C8 -O2 -msoft-float */
void INIT_PASTILLES_SAUVE(void)
{
    u8 *name;

    if (NBRE_SAVE != 0)
        name = PTR_s_save_game_801c353c;
    else
        name = PTR_s_no_save_available_801c3544;

    t_world_info[18].level_name = name;
    t_world_info[19].level_name = name;
    t_world_info[20].level_name = name;
    t_world_info[21].level_name = name;
    t_world_info[22].level_name = name;
    t_world_info[23].level_name = name;
}

/* 6A130 8018E930 -O2 */
void PASTILLES_SAUVE_SAVED(s16 wld)
{
    INIT_PASTILLES_SAUVE();
    t_world_info[wld].level_name = PTR_s_game_saved_801c3540;
}

/* 6A180 8018E980 -O2 */
/*void INIT_PASTILLES_SAUVE(void);*/

void FIN_WORLD_CHOICE(void)
{
    xwldmapsave = xmap;
    ywldmapsave = ymap;
    xmap = xmapinit;
    ymap = ymapinit;

    dir_on_wldmap = ray.flags >> OBJ_FLIP_X & 1;
    RESTORE_RAY();
    INIT_PASTILLES_SAUVE();
    PROC_EXIT = false;
    if (ray.hit_points == 0xFF)
        ray.hit_points = 0;
}

/* 6A224 8018EA24 -O2 */
void DETER_WORLD_AND_LEVEL(void)
{
    world_index = num_world_choice;
    if (ModeDemo == 0)
    {
        num_level_choice = t_world_info[num_world_choice].level;
        num_world_choice = t_world_info[num_world_choice].world;
    }

    if (
        num_world_choice == 5 && num_level_choice == 3 &&
        finBosslevel.helped_joe_1
    )
    {
        num_level_choice++;
        RayEvts.luciole = true;
    }
    else if (
        num_world_choice == 5 && num_level_choice == 4 &&
        finBosslevel.helped_joe_1 && ModeDemo != 0
    )
        RayEvts.luciole = true;
    else if (
        num_world_choice == 6 &&
        finBosslevel.mr_dark
    )
    {
        You_Win = true;
        fin_du_jeu = true;
        fin_dark = true;
        new_world = true;
    }
}