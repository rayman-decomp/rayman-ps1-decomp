#include "save.h"

#ifdef BSS_DEFS
SaveState save1;
SaveState save2;
u8 save_zone[2688];
WorldInfoSave wi_save_zone[24];
#endif

/* 3F170 80163970 -O2 -msoft-float */
void initGameSave(void)
{
    save1.has_saved = false;
}

/* 3F180 80163980 -O2 -msoft-float */
void doneGameSave(void)
{
    save1.has_saved = false;
}

/* 3F190 80163990 -O2 -msoft-float */
void saveGameState(Obj *obj, SaveState *state)
{
    u8 i;
    s16 j;
    Obj *cur_obj;
    s16 nb_objs;
    s32 unk_1;
    s32 unk_2;

    state->num_wiz = status_bar.num_wiz;
    state->x_map = xmap;
    state->y_map = ymap;
    state->time = PS1_MoteurTime;
    state->ray_x_pos = ray.x_pos;
    state->ray_y_pos = ray.y_pos;
    state->ray_screen_x = ray.screen_x_pos;
    state->ray_screen_y = ray.screen_y_pos;
    state->ray_flip_x = ray.flags >> OBJ_FLIP_X & 1;
    state->rayevts_0 = RayEvts.reverse; /* RAYEVTS1_REVERSE and RAYEVTS1_FLAG6 */
    state->rayevts_1 = RayEvts.super_helico;
    state->rayevts_2 = RayEvts.poing;
    if (obj)
    {
        state->save_obj_id = obj->id;
        state->save_obj_x_pos = obj->x_pos;
        state->save_obj_y_pos = obj->y_pos;
        state->save_obj_detect_zone_flag = obj->detect_zone_flag;
        state->field18_0x14b = obj->flags >> OBJ_FLAG_0 & 1;
    }
    else
        state->save_obj_id = -1;

    memcpy(state->link_init, link_init, level.nb_objects);

    for (i = 0; i < LEN(ray.btypes); i++)
        state->ray_btypes[i] = ray.btypes[i];
    state->ray_anim_index = ray.anim_index;
    state->ray_anim_frame = ray.anim_frame;
    state->ray_main_etat = ray.main_etat;
    state->ray_sub_etat = ray.sub_etat;

    for (i = 0; i < LEN(nb_floc); i++)
        state->nb_floc[i] = nb_floc[i];
    state->vent_x = VENT_X;
    state->vent_y = VENT_Y;
    state->poing_sub_etat = poing.sub_etat;

    j = 0;
    cur_obj = &level.objects[0];
    nb_objs = level.nb_objects;
    while (j < nb_objs)
    {
        if (cur_obj->type == TYPE_NEIGE || cur_obj->type == TYPE_GENERATING_DOOR)
        {
            unk_1 = j >> 5;
            unk_2 = 1 << (j & 0x1F);
            if (cur_obj->flags & FLG(OBJ_ALIVE))
                state->triggered_objects[unk_1] |= unk_2;
            else
                state->triggered_objects[unk_1] &= ~unk_2;
        }
        j++;
        cur_obj++;
    }
    state->dead_time = dead_time;
    state->has_saved = true;
}

/* 3F484 80163C84 -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/save", restoreGameState);
#else
/* score of 385 */
void restoreGameState(SaveState *save_param)
{
    Obj *temp_a2;
    s16 temp_v1_1;
    s16 var_a3_2;
    s16 var_v0_3;
    u8 temp_a0;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a2_2;
    u8 var_a2_3;
    s32 var_a2_4;
    s32 var_v1_2;
    Obj *cur_obj;
    u32 var_v0_4;
    u32 var_v1;
    u8 temp_a1;
    u8 temp_a1_2; /* being used for two different save_param fields */
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v1_3;
    u8 var_v0_2;
    s16 nb_objs;
    u8 test_1;
    s16 test_2;
    u8 test_3;
    Obj *new_var;

    if (save_param->has_saved)
    {
        if (RayEvts.demi)
        {
            __builtin_memcpy(&ray, &rms, sizeof(Obj));
            RayEvts.demi = false;
        }
        status_bar.num_wiz = save_param->num_wiz;
        xmap = save_param->x_map;
        ymap = save_param->y_map;
        temp_a1_2 = save_param->time;
        PS1_MoteurTime = temp_a1_2;
        ray.x_pos = save_param->ray_x_pos;
        ray.y_pos = save_param->ray_y_pos;
        ray.screen_x_pos = save_param->ray_screen_x;
        ray.screen_y_pos = save_param->ray_screen_y;
        /*PS1_MoteurTime = save->unk38;*/

        var_v0_2 = 1;
        ray.flags = (ray.flags & ~0x4000) | ((save_param->ray_flip_x & var_v0_2) << 0xE);
        RayEvts.super_helico = save_param->rayevts_1;
        if ((num_world == 6) && (num_level == 3))
        {
            RayEvts.poing = save_param->rayevts_2;
            RayEvts.reverse = save_param->rayevts_0;
        }
        /* tried using cur_obj */
        temp_v1_1 = save_param->save_obj_id;
        if (temp_v1_1 != -1)
        {
            temp_a2 = &level.objects[temp_v1_1];
            temp_a2->x_pos = save_param->save_obj_x_pos;
            temp_a2->y_pos = save_param->save_obj_y_pos;
            temp_a2->detect_zone_flag = save_param->save_obj_detect_zone_flag;
            var_v0_3 = ((save_param->field18_0x14b & 1) << 8);
            temp_a2->flags = (temp_a2->flags & ~0x100) | var_v0_3;
        }
        if (save_param == &save1)
        {
            var_a2_3 = 0;
            while (var_a2_3 < level.nb_objects) /* not saved into s16 var? */
            {
                temp_a0 = save_param->link_init[var_a2_3];
                link_init[var_a2_3] = temp_a0;
                if (temp_a0 != var_a2_3)
                {
                    level.objects[var_a2_3].flags |= 0x1000;
                }
                else
                {
                    level.objects[temp_a0].flags &= ~0x1000;
                }
                var_a2_3 += 1;
            }
        }
        var_a2_3 = 0;
        do
        {
            ray.btypes[var_a2_3] = save_param->ray_btypes[var_a2_3];
            var_a2_3 += 1;
        } while (var_a2_3 < 5U);
        ray.anim_index = save_param->ray_anim_index;
        ray.anim_frame = save_param->ray_anim_frame;
        ray.main_etat = save_param->ray_main_etat;
        ray.sub_etat = save_param->ray_sub_etat;
        if (save_param == &save1)
        {
            switch (save1.poing_sub_etat)
            {
            case 5:
            case 12:
                save_param->poing_sub_etat = 3;
                break;
            case 1:
            case 3:
            case 8:
            case 10:
                save_param->poing_sub_etat = 1;
                break;
            }
        }
        temp_a1_2 = save_param->poing_sub_etat;
        poing.sub_etat = temp_a1_2;
        level.objects[poing_obj_id].init_sub_etat = temp_a1_2;
        dead_time = save_param->dead_time;
        decalage_en_cours = 0;
        ray_wind_force = 0;

        var_a2_3 = 0;
        do
        {
            nb_floc[var_a2_3] = save_param->nb_floc[var_a2_3];
            var_a2_3 += 1;
        } while (var_a2_3 < 8U);

        VENT_X = save_param->vent_x;
        VENT_Y = save_param->vent_y;
        ray.speed_x = 0;
        ray.speed_y = 0;
        ray.iframes_timer = -1;

        /* ??? */
        var_a3_2 = 0; /* this is s16, while var_a2_3 is u8 */
        cur_obj = &level.objects[var_a3_2];
        ray.flags |= 0xC00;
        nb_objs = level.nb_objects;
        /* ???*/

        h_scroll_speed = 0;
        v_scroll_speed = 0;

        while (var_a3_2 < nb_objs)
        {
            temp_v1_3 = cur_obj->type;
            if (temp_v1_3 == 0x3 || temp_v1_3 == 0xD || temp_v1_3 == 0xF || temp_v1_3 == 0x3B || temp_v1_3 == 0x24 || temp_v1_3 == 0x42 || temp_v1_3 == 0x3E)
            {
                cur_obj->flags = cur_obj->flags & ~0x400;
            }
            else if (temp_v1_3 == 0x8D || temp_v1_3 == 0xA4)
            {
                if ((1 << (var_a3_2 & 0x1F)) & save_param->triggered_objects[var_a3_2 >> 5])
                {
                    cur_obj->flags = cur_obj->flags | 0x400;
                }
                else
                {
                    cur_obj->flags = cur_obj->flags & ~0x400;
                }
            }
            var_a3_2 = var_a3_2 + 1;
            cur_obj += 1;
        }
        gerbe = 0;
    }
}
#endif

/* 3F9C0 801641C0 -O2 -msoft-float */
void DO_PHOTOGRAPHE_CMD(void)
{
    s16 i = 0;
    Obj *cur_obj = &level.objects[actobj.objects[i]];

    while (i < actobj.num_active_objects)
    {
        if (cur_obj->type == TYPE_PHOTOGRAPHE)
        {
            if (cur_obj->sub_etat == 1)
            {
                if (++cur_obj->timer == 0)
                    cur_obj->timer++;
            }
            else
            {
                if (cur_obj->timer != 0)
                {
                    ray.flags |= FLG(OBJ_ACTIVE);
                    restore_gendoor_link();
                    saveGameState(cur_obj, &save1);
                    correct_gendoor_link();
                    cur_obj->timer = 0;
                }
                else
                {
                    if (
                        !RayEvts.demi && !(cur_obj->flags & FLG(OBJ_FLAG_0)) && OBJ_IN_ZONE(cur_obj) &&
                        ray.field20_0x36 == -1 && decalage_en_cours == 0 &&
                        ray.main_etat == 0 && ray.sub_etat == 0 &&
                        inter_box(
                            (s16) (cur_obj->x_pos + 42), (s16) (cur_obj->y_pos + 48), 5, 15,
                            ray_zdc_x, ray_zdc_y, ray_zdc_w, ray_zdc_h
                        )
                    )
                    {
                        ray.speed_x = 0;
                        cur_obj->flags |= FLG(OBJ_FLAG_0);
                        ray.flags &= ~FLG(OBJ_ACTIVE);
                        skipToLabel(cur_obj, 0, true);
                    }
                }
            }
        }
        i++;
        cur_obj = &level.objects[actobj.objects[i]];
    }
}

/* 3FC20 80164420 -O2 -msoft-float */
s16 get_offset_in_save_zone(s16 event_index)
{
    s16 unk_1 = 0;
    s16 i = 1;
    while (i < num_world)
    {
        unk_1 += nb_levels_in_world[i] * 32;
        i++;
    }

    i = 1;
    while (i < num_level)
    {
        unk_1 += 32;
        i++;
    }

    return (unk_1 + ashr16(event_index, 3));
}

/* 3FCE4 801644E4 -O2 -msoft-float */
void reset_save_zone_level(void)
{
    memset(&save_zone[get_offset_in_save_zone(0)], 0, 32);
}

/* 3FD24 80164524 -O2 -msoft-float */
void take_bonus(s16 event_index)
{
    save_zone[get_offset_in_save_zone(event_index)] |= ashr16(1 << 7, event_index & 7);
}

/* 3FD98 80164598 -O2 -msoft-float */
u8 bonus_taken(s16 event_index)
{
    return save_zone[get_offset_in_save_zone(event_index)] & ashr16(1 << 7, event_index & 7);
}

/* 3FDFC 801645FC -O2 -msoft-float */
void PS1_WriteWiSaveZone(void)
{
    s16 i;

    for (i = 0; i < (s16) LEN(t_world_info); i++)
    {
        wi_save_zone[i].is_unlocked = t_world_info[i].is_unlocked;
        wi_save_zone[i].is_unlocking = t_world_info[i].is_unlocking;
        wi_save_zone[i].nb_cages = t_world_info[i].nb_cages;
    }
}

/* 3FED4 801646D4 -O2 -msoft-float */
void PS1_LoadWiSaveZone(void)
{
    s16 i;

    for (i = 0; i < (s16) LEN(t_world_info); i++)
    {
        t_world_info[i].is_unlocked = wi_save_zone[i].is_unlocked;
        t_world_info[i].is_unlocking = wi_save_zone[i].is_unlocking;
        t_world_info[i].nb_cages = wi_save_zone[i].nb_cages;
    }
}