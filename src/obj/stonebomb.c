#include "obj/stonebomb.h"

#ifdef BSS_DEFS
s16 saveRMjumpX;
s16 saveRMjumpY;
#endif

/* 38118 8015C918 -O2 -msoft-float */
void setStoneChipPos(Obj *param_1, Obj *param_2, u8 *param_3)
{
    if (!*param_3)
    {
        param_2->x_pos = (param_1->x_pos + param_1->offset_bx) - param_2->offset_bx;
        param_2->y_pos = (param_1->y_pos + param_1->offset_by) - param_2->offset_by;
        switch (param_2->sub_etat)
        {
        case 9:
            param_2->x_pos -= (param_2->offset_bx >> 1) - param_2->offset_bx;
            param_2->y_pos -= param_2->offset_by + param_2->offset_by / 3;
            break;
        case 10:
            param_2->x_pos += (param_2->offset_bx >> 1) - param_2->offset_bx;
            param_2->y_pos -= param_2->offset_by + param_2->offset_by / 3;
            break;
        case 11:
            param_2->x_pos -= (param_2->offset_bx >> 1) - param_2->offset_bx;
            param_2->y_pos -= param_2->offset_by;
            break;
        case 12:
            param_2->x_pos += (param_2->offset_bx >> 1) - param_2->offset_bx;
            param_2->y_pos -= param_2->offset_by;
            break;
        case 13:
            param_2->x_pos -= (param_2->offset_bx >> 1) - param_2->offset_bx;
            param_2->y_pos += param_2->offset_by / 3 - param_2->offset_by;
            break;
        case 14:
            param_2->x_pos += (param_2->offset_bx >> 1) - param_2->offset_bx;
            param_2->y_pos += param_2->offset_by / 3 - param_2->offset_by;
            break;
        }
        calc_obj_pos_map(param_2);
        param_2->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
        param_2->flags &= ~FLG(OBJ_FLAG_9);
        *param_3 = true;
    }
}

/* 383B0 8015CBB0 -O2 -msoft-float */
void allocateStoneChips(Obj *in_obj)
{
    u8 se_1;
    u8 se_2;
    u8 se_3;
    s16 i;
    Obj *cur_obj;
    s16 nb_objs;
    u8 sub_etat;
    u8 unk_par_3 = false;
    u8 unk_par_2 = false;
    u8 unk_par_1 = false;

    switch (in_obj->speed_x > 0)
    {
    case false:
        se_1 = 10;
        se_2 = 12;
        se_3 = 14;
        break;
    case true:
        se_1 = 9;
        se_2 = 11;
        se_3 = 13;
        break;
    }

    i = 0;
    cur_obj = &level.objects[i];
    nb_objs = level.nb_objects;
    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_STONECHIP && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            sub_etat = cur_obj->sub_etat;
            if (sub_etat == se_1)
                setStoneChipPos(in_obj, cur_obj, &unk_par_1);
            else if (sub_etat == se_2)
                setStoneChipPos(in_obj, cur_obj, &unk_par_2);
            else if (sub_etat == se_3)
                setStoneChipPos(in_obj, cur_obj, &unk_par_3);
        }
        cur_obj++;
        i++;
    }
}

/* 38514 8015CD14 -O2 -msoft-float */
void DO_STONE_EXPLOSION(Obj *obj)
{
    PlaySnd_old(84);
    if (obj->flags & FLG(OBJ_ACTIVE))
    {
        if (obj->main_etat == 2 && obj->sub_etat == 1)
        {
            obj->x_pos += 20;
            obj->speed_x = -1;
            allocateStoneChips(obj);
            obj->x_pos -= 20;
            obj->speed_x = 1;
            allocateStoneChips(obj);
            obj->x_pos += 10;
        }
        else
            allocateStoneChips(obj);

        obj->flags &= ~FLG(OBJ_ACTIVE);
        if (obj->type == TYPE_STONEBOMB)
            obj->flags &= ~FLG(OBJ_ALIVE);
        else
            obj->y_pos = ymap + 484;

        allocateExplosion(obj);
    }
}

/* 38608 8015CE08 -O2 -msoft-float */
void DO_TIR(Obj *param_1)
{
    Obj *var_s2;
    Obj *var_s0;
    s16 temp_a0;
    s16 temp_a1;
    s16 temp_v0_1;
    s16 temp_v0_4;
    s16 var_a0;
    s16 var_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    u32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    u16 var_v1;
    s16 var_a2;
    u8 temp_v1_1;
    u8 temp_v1_2;
    u8 var_a1;
    s16 test_1;
    s32 test_2;
    u32 test_3;
    u32 test_4;

    if (param_1->main_etat == 0)
    {
        if (param_1->sub_etat == 11)
        {
            if (param_1->field24_0x3e == 0)
            {
                var_s2 = level.objects;
                var_a0 = 0;
                test_1 = level.nb_objects;
                while (var_a0 < test_1)
                {
                    temp_v1_2 = var_s2->type;
                    if (((temp_v1_2 == 0x0D) || (temp_v1_2 == 0x0F)) && (((var_s2->flags & 0x800) == 0)))
                    {
                        test_4 = ~0x4000;
                        var_s2->flags = (((test_4 = var_s2->flags & -0x4001) | (param_1->flags & 0x4000) ) | 0xc00);
                        
                        set_main_and_sub_etat(var_s2, 2, 2);
                        var_s2->anim_frame = 0;
                        var_s2->anim_index = (u8) var_s2->eta[2][2].anim_index;
                        temp_v1_4 = (param_1->x_pos + param_1->offset_bx) - var_s2->offset_bx;
                        if (var_s2->flags & 0x4000)
                        {
                            temp_v1_4 = temp_v1_4 + 0x40;
                        }
                        else
                        {
                            temp_v1_4 = temp_v1_4 - 0x40;
                        }
                        var_s2->x_pos = temp_v1_4;
                        var_s2->y_pos = param_1->y_pos;
                        var_s2->init_x_pos = var_s2->x_pos;
                        var_s2->init_y_pos = var_s2->y_pos;
                        calc_obj_pos_map(var_s2);
                        PlaySnd(0x0018, var_s2->id);
                        if (var_s2->flags & 0x4000)
                        {
                            skipToLabel(var_s2, 3, 1U);
                        }
                        else
                        {
                            skipToLabel(var_s2, 1, 1U);
                        }

                        if (param_1->type == 0x0E)
                        {
                            
                            if (param_1->x_pos - ray.x_pos < 0)
                            {
                                var_a2 = (ray.x_pos - param_1->x_pos) >> 5;
                            }
                            else
                                var_a2 = (param_1->x_pos - ray.x_pos) >> 5;
                            var_s2->type = 0x0FU;
                            temp_v1_6 = (ray.y_pos - param_1->y_pos) * 2;
                            test_3 = (s16) var_a2;
                            temp_v0_2 = param_1->x_pos - ray.x_pos;
                            
                            if (temp_v0_2 >= 0)
                            {
                                var_v0 = (temp_v1_6 / temp_v0_2) - test_3;
                            }
                            else
                            {
                                temp_v0_3 = ray.x_pos - param_1->x_pos;
                                var_v0 = (temp_v1_6 / temp_v0_3) - test_3;
                            }
                            var_s2->speed_y = var_v0;
                            var_s2->gravity_value_2 = 0x0A;
                        }
                        else
                        {
                            var_s2->type = 0x0DU;
                            var_s2->speed_y = 0;
                        }
                        calc_obj_pos_map(var_s2);
                        break;
                    }
                    var_s2 += 1;
                    var_a0 = var_a0 + 1;
                }
                param_1->field24_0x3e = 1;
                return;
            }
        }
        else if (param_1->sub_etat == 2)
        {
            param_1->field24_0x3e = 0;
        }
    }
}

/* 388C4 8015D0C4 -O2 -msoft-float */
void allocateStonemanStone(Obj *stmn_obj, s16 param_2, u8 param_3)
{
    s16 i;
    Obj *cur_obj;
    s16 nb_objs;
    u8 stmn_frame;
    s16 stmn_spr;
    s16 stmn_x; s16 stmn_y; s16 stmn_w; s16 stmn_h;

    if (stmn_obj->type == TYPE_STONEMAN1)
    {
        i = 0;
        cur_obj = &level.objects[i];
        nb_objs = level.nb_objects;
        while (i < nb_objs)
        {
            cur_obj->timer = 200;
            if (cur_obj->type == TYPE_STONEBOMB && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
            {
                if (param_3)
                    cur_obj->flags =
                        (cur_obj->flags & ~FLG(OBJ_FLIP_X)) |
                        (stmn_obj->flags & FLG(OBJ_FLIP_X));
                else
                    cur_obj->flags =
                        (cur_obj->flags & ~FLG(OBJ_FLIP_X)) |
                        (((stmn_obj->flags >> OBJ_FLIP_X ^ 1) & 1) << OBJ_FLIP_X);

                cur_obj->speed_y = param_2;
                if (!(cur_obj->flags & FLG(OBJ_FLIP_X)))
                    cur_obj->speed_x = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_left;
                else
                    cur_obj->speed_x = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_right;

                stmn_frame = stmn_obj->anim_frame;
                if (stmn_frame >= 53 && stmn_frame <= 122)
                    stmn_spr = 3;
                else if (stmn_frame >= 123 && stmn_frame <= 144)
                    stmn_spr = 0;
                else
                    stmn_spr = -1;

                if (stmn_spr != -1)
                {
                    GET_SPRITE_POS(stmn_obj, stmn_spr, &stmn_x, &stmn_y, &stmn_w, &stmn_h);
                    cur_obj->x_pos = stmn_x - cur_obj->offset_bx + (stmn_w >> 1);
                    cur_obj->y_pos = stmn_y - cur_obj->offset_hy;
                    cur_obj->init_x_pos = cur_obj->x_pos;
                    cur_obj->init_y_pos = cur_obj->y_pos;
                    set_main_and_sub_etat(cur_obj, 2, 2);
                    SET_X_SPEED(cur_obj);
                    calc_obj_pos_map(cur_obj);
                    cur_obj->gravity_value_1 = 0;
                    cur_obj->gravity_value_2 = 7;
                    cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                    cur_obj->flags &= ~FLG(OBJ_FLAG_9);
                }
                break;
            }
            cur_obj++;
            i++;
        }
    }
    else
    {
        i = 0;
        cur_obj = &level.objects[i];
        nb_objs = level.nb_objects;
        while (i < nb_objs)
        {
            if (cur_obj->type == TYPE_CLASH && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
            {
                PlaySnd(90, cur_obj->id);
                if (param_3)
                    cur_obj->flags =
                        (cur_obj->flags & ~FLG(OBJ_FLIP_X)) |
                        (stmn_obj->flags & FLG(OBJ_FLIP_X));
                else
                    cur_obj->flags =
                        (cur_obj->flags & ~FLG(OBJ_FLIP_X)) |
                        (((stmn_obj->flags >> OBJ_FLIP_X ^ 1) & 1) << OBJ_FLIP_X);

                cur_obj->speed_y = param_2;
                if (!(cur_obj->flags & FLG(OBJ_FLIP_X)))
                    cur_obj->speed_x = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_left;
                else
                    cur_obj->speed_x = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_right;

                GET_SPRITE_POS(stmn_obj, 7, &stmn_x, &stmn_y, &stmn_w, &stmn_h);
                cur_obj->x_pos = stmn_x + stmn_w - cur_obj->offset_bx;
                cur_obj->y_pos = stmn_y - 6;
                cur_obj->init_x_pos = cur_obj->x_pos;
                cur_obj->init_y_pos = cur_obj->y_pos;
                skipToLabel(cur_obj, cur_obj->flags >> OBJ_FLIP_X & 1, true);
                calc_obj_pos_map(cur_obj);
                cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                break;
            }
            cur_obj++;
            i++;
        }
    }
}

/* 38CDC 8015D4DC -O2 -msoft-float */
void DO_STONEMAN1_TIR(Obj *obj)
{
    DO_STONEMAN_COMMAND(obj);
    if (obj->main_etat == 0)
    {
        if (!(obj->sub_etat == 2 && obj->anim_frame >= 144))
            obj->field24_0x3e = 0;

        if (obj->sub_etat == 1 || obj->sub_etat == 2)
        {
            if (EOA(obj))
            {
                if (obj->detect_zone_flag != 0)
                    skipToLabel(obj, 7, true);
                else
                    skipToLabel(obj, 8, true);
            }
        }

        if (
            obj->sub_etat == 2 && obj->field24_0x3e == 0 && obj->anim_frame == 144 &&
            horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0
        )
        {
            allocateStonemanStone(obj, -2, true);
            obj->field24_0x3e = 1;
        }
    }
    else
        obj->field24_0x3e = 0;
}

/* 38EC0 8015D6C0 -O2 -msoft-float */
void DO_STONEMAN2_TIR(Obj *obj)
{
    s32 unk_1;

    DO_STONEMAN_COMMAND(obj);
    if (obj->main_etat == 0)
    {
        if (obj->sub_etat != 6)
            obj->field24_0x3e = 0;

        if (obj->sub_etat == 1 || obj->sub_etat == 6)
        {
            if (EOA(obj))
            {
                if (obj->detect_zone_flag != 0)
                    skipToLabel(obj, 7, true);
                else
                    skipToLabel(obj, 8, true);
            }

            if ((obj->sub_etat == 6) && (obj->field24_0x3e == 0))
            {
                unk_1 = obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf;
                if (horloge[unk_1] == unk_1 - 1)
                {
                    allocateStonemanStone(obj, 0, true);
                    obj->field24_0x3e = 1;
                }
            }
        }
    }
    else
        obj->field24_0x3e = 0;
}

/* 3907C 8015D87C -O2 -msoft-float */
void allocateStonewomanStone(Obj *stwmn_obj, s16 param_2)
{
    s16 sprite;
    s16 spr_x; s16 spr_y; s16 spr_w; s16 spr_h;
    s16 spd_x; s16 spd_y;
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_STONEBOMB && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj->timer = 200;
            if (param_2 != 0)
                cur_obj->flags = (cur_obj->flags & ~FLG(OBJ_FLIP_X)) | (stwmn_obj->flags & FLG(OBJ_FLIP_X));
            else
                cur_obj->flags = (cur_obj->flags & ~FLG(OBJ_FLIP_X)) | (((stwmn_obj->flags >> OBJ_FLIP_X ^ 1) & 1) << OBJ_FLIP_X);

            sprite = -1;
            if (stwmn_obj->main_etat == 0)
            {
                if (stwmn_obj->sub_etat == 13)
                {
                    if (stwmn_obj->anim_frame - 52 < 50U)
                        sprite = 3;
                }
                else if (stwmn_obj->sub_etat == 9)
                {
                    if (stwmn_obj->anim_frame - 16 < 40U)
                        sprite = 3;
                }
            }

            if (sprite != -1)
            {
                GET_SPRITE_POS(stwmn_obj, sprite, &spr_x, &spr_y, &spr_w, &spr_h);
                switch (param_2)
                {
                case 0:
                    spd_y = -2;
                    stwmn_obj->hit_points += poing.damage - 1;
                    break;
                case 1:
                    spd_y = 1;
                    break;
                case 2:
                    if (ray.main_etat == 2)
                    {
                        cur_obj->follow_x = saveRMjumpX;
                        cur_obj->follow_y = saveRMjumpY;
                    }
                    else
                    {
                        cur_obj->follow_x = ray.x_pos;
                        cur_obj->follow_y = ray.y_pos;
                    }
                    break;
                }
                cur_obj->x_pos = spr_x - cur_obj->offset_bx + (spr_w >> 1);
                cur_obj->y_pos = spr_y - cur_obj->offset_hy;
                cur_obj->init_x_pos = cur_obj->x_pos;
                cur_obj->init_y_pos = cur_obj->y_pos;
                if (param_2 != 2)
                {
                    if (!(cur_obj->flags & FLG(OBJ_FLIP_X)))
                        spd_x = (s16) cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_left;
                    else
                        spd_x = (s16) cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_right;
                    SET_X_SPEED(cur_obj);
                    set_sub_etat(cur_obj, 0);
                }
                else
                {
                    set_sub_etat(cur_obj, 1);
                    Projectil_to_RM(cur_obj, &spd_x, &spd_y, 30, 3);
                }

                cur_obj->speed_x = spd_x;
                cur_obj->speed_y = spd_y;
                calc_obj_pos_map(cur_obj);
                cur_obj->gravity_value_1 = 0;
                cur_obj->gravity_value_2 = 7;
                cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                cur_obj->flags &= ~FLG(OBJ_FLAG_9);
            }
            break;
        }
        cur_obj++;
        i++;
    }
}

/* 393E4 8015DBE4 -O2 -msoft-float */
void DO_STONEWOMAN_TIR(Obj *obj)
{
    if (obj->main_etat == 0)
    {
        if (
            !(obj->sub_etat == 13 && obj->anim_frame > 100) &&
            !(obj->sub_etat == 9 && obj->anim_frame > 54)
        )
            obj->field24_0x3e = 0;

        if (
            (obj->sub_etat == 0 || obj->sub_etat == 14 || obj->sub_etat == 8) &&
            obj->anim_frame == 0
        )
        {
            if (obj->detect_zone_flag > 1)
                skipToLabel(obj, 7, true);
            else
                skipToLabel(obj, 12, true);
        }

        if (obj->sub_etat == 13)
        {
            if (
                obj->field24_0x3e == 0 && obj->anim_frame == 101 &&
                horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0
            )
            {
                allocateStonewomanStone(obj, 1);
                obj->field24_0x3e = 1;
            }
        }
        else if (obj->sub_etat == 9)
        {
            if (
                obj->field24_0x3e == 0 && obj->anim_frame == 55 &&
                horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0
            )
            {
                allocateStonewomanStone(obj, 2);
                obj->field24_0x3e = 1;
            }
        }
    }
    else
        obj->field24_0x3e = 0;
}
