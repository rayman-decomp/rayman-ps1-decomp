#include "obj_update.h"

#ifdef BSS_DEFS
ObjHandlers ObjectsFonctions[256];
ObjType ot;
s16 id_Cling_1up;
s16 id_Cling_Pow;
u8 ray_in_fee_zone;
#endif

void DO_BALLE(Obj *obj);
void DO_BAT_COMMAND(Obj *obj);
void DO_BB1_PLAT_CMD(Obj *obj);
void DO_BLKTOON_COMMAND(Obj *obj);
void DO_BLKTOON_EYES_CMD(Obj *obj);
void DO_BOUEE_JOE_COMMAND(Obj *obj);
void DO_CLOWN_TNT2_COMMAND(Obj *obj);
void DO_CLOWN_TNT3_COMMAND(Obj *obj);
void DO_CLOWN_TNT_COMMAND(Obj *obj);
void DO_DARD_PLAFOND_ALWAYS(Obj *obj);
void DO_DARK2_SORT_COMMAND(Obj *obj);
void DO_DARK2_TOONS_COMMAND(Obj *obj);
void DO_DARK_COMMAND(Obj *obj);
void DO_DARK_PHASE2_COMMAND(Obj *obj);
void DO_DROP_COMMAND(Obj *obj);
void DO_EAU_QUI_MONTE(Obj *obj);
void DO_ECLAIR_COMMAND(Obj *obj);
void DO_ENSEIGNE_COMMAND(Obj *obj);
void DO_FLASH_COMMAND(Obj *obj);
void DO_HYB_BBF2_LAS(Obj *obj);
void DO_IDC_COMMAND(Obj *obj);
void DO_JOE_COMMAND(Obj *obj);
void DO_MITE2_COMMAND(Obj *obj);
void DO_MIT_COMMAND(Obj *obj);
void DO_MOVING_WITH_INDICATOR_COMMAND(Obj *obj);
void DO_MST_SCROLL_COMMAND(Obj *obj);
void DO_MUSICIEN(Obj *obj);
void DO_NOMOVE_STONEWOMAN_COMMAND(Obj *obj);
void DO_NOVA2_COMMAND(Obj *obj);
void DO_ONE_NGW_COMMAND(Obj *obj);
void DO_ONE_NGW_RING_COMMAND(Obj *obj);
void DO_ONE_PAR_COMMAND(Obj *obj);
void DO_ONE_PINK_CMD(Obj *obj);
void DO_ONE_STONECHIP_COMMAND(Obj *obj);
void DO_PAC_COMMAND(Obj *obj);
void DO_PAR_BOMB_COMMAND(Obj *obj);
void DO_PETIT_COUTEAU_COMMAND(Obj *obj);
void FUN_80172704(Obj *obj);
void DO_PIRATE_POELLE(Obj *obj);
void DO_POELLE_COMMAND(Obj *obj);
void DO_POING(Obj *obj);
void DO_PTI_ESQUIVE(Obj *obj);
void DO_REDUCTEUR(Obj *obj);
void DO_ROLL_EYES(Obj *obj);
void DO_SPIDER_PLAFOND(Obj *obj);
void DO_SPIDER_TIR(Obj *obj);
void DO_STONEBOMB_COMMAND(Obj *obj);
void DO_STONEDOG_COMMAND(Obj *obj);
void DO_STONEMAN1_TIR(Obj *obj);
void DO_STONEMAN2_TIR(Obj *obj);
void DO_STONEWOMAN_COMMAND(Obj *obj);
void DO_TARZAN(Obj *obj);
void DO_TEN_COMMAND(Obj *obj);
void DO_TIRE_BOUCHON_COMMAND(Obj *obj);
void DO_TRP_COMMAND(Obj *obj);
void DO_VITRAIL_COMMAND(Obj *obj);
void DoFlammeCommand(Obj *obj);
void doBBF2command(Obj *obj);
void doBlackRaymanCommand(Obj *obj);
void doHerseCommand(Obj *obj);
void doMOSAMScommand(Obj *obj);
void doSTOSKOcommand(Obj *obj);
void doShipCommand(Obj *obj);

/* 2C214 80150A14 -O2 -msoft-float */
s32 DO_PESANTEUR(Obj *obj)
{
    s16 spd_y;
    s32 res = false;
    s16 y_accel = 0;
    u8 anim_speed_div = obj->eta[obj->main_etat][obj->sub_etat].anim_speed >> 4;

    if (anim_speed_div != 0)
    {
        if (obj->type == TYPE_TAMBOUR1 || obj->type == TYPE_TAMBOUR2)
        {
            if (obj->field56_0x69 != 0)
                obj->field56_0x69--;
            else if (obj->gravity_value_1 == 0)
            {
                obj->speed_y++;
                res = true;
            }
        }
        else
        {
            switch (anim_speed_div)
            {
            case 6:
                if (horloge[2] == 0)
                {
                    y_accel = 1;
                    res = true;
                }
                break;
            case 1:
                if (obj->gravity_value_1 == 0)
                {
                    y_accel = 1;
                    res = true;
                }
                break;
            case 2:
                if (obj->gravity_value_2 == 0)
                {
                    y_accel = 1;
                    res = true;
                }
                break;
            case 3:
                spd_y = obj->speed_y;
                if (spd_y > 0)
                {
                    if (spd_y > 1)
                        y_accel = -1;
                }
                else
                    y_accel = 1;
                break;
            case 4:
                spd_y = obj->speed_y;
                if (spd_y < -1)
                {
                    if (spd_y < -2)
                        y_accel = 1;
                }
                else
                    y_accel = -1;
                break;
            case 5:
                if (obj->gravity_value_1 == 0)
                    y_accel = -1;
                break;
            case 10:
                obj->gravity_value_1++;
                if (obj->gravity_value_1 >= obj->gravity_value_2)
                {
                    obj->gravity_value_1 = 0;
                    y_accel = 1;
                    res = true;
                }
                break;
            case 11:
                obj->gravity_value_1++;
                if (obj->gravity_value_1 >= obj->gravity_value_2)
                {
                    obj->gravity_value_1 = 0;
                    y_accel = -1;
                    res = true;
                }
                break;
            }
        }

        if (flags[obj->type].flags1 >> OBJ1_USE_INSTANT_SPEED_Y & 1)
            y_accel = ashl16(y_accel, 4);
        obj->speed_y += y_accel;
    }
    return res;
}

/* 2C45C 80150C5C -O2 -msoft-float */
void freezeAnim(Obj *obj, u8 param_2)
{
    s16 count = obj->animations[obj->anim_index].frames_count - 1;
    s32 count_capped;

    if (obj->eta[obj->main_etat][obj->sub_etat].flags & 0x10)
    {
        /* duplicate... */
        count_capped = count;
        MIN_3(count_capped, param_2);
        obj->anim_frame = count - count_capped + 1;
    }
    else
    {
        count_capped = count;
        MIN_3(count_capped, param_2);
        obj->anim_frame = count_capped;
    }
}

/* 2C50C 80150D0C -O2 -msoft-float */
void DO_ANIM(Obj *obj)
{
    Animation *new_anim;
    u8 new_frame;
    s32 changed;
    u8 old_ind = obj->anim_index;
    s16 old_frame = obj->anim_frame;
    Animation *old_anim = &obj->animations[old_ind];
    ObjState *eta = &obj->eta[obj->main_etat][obj->sub_etat];
    s32 anim_speed = eta->anim_speed & 0xF;

    if (anim_speed != 0 && horloge[anim_speed] == 0)
    {
        if (!(eta->flags >> 4 & 1))
            obj->anim_frame++;
        else
            obj->anim_frame--;
    }
    obj->anim_index = eta->anim_index;
    new_anim = &obj->animations[obj->anim_index];

    switch (obj->change_anim_mode)
    {
    case ANIMMODE_RESET_IF_NEW:
        if (obj->anim_index != old_ind)
        {
            if (!(eta->flags & 0x10))
                obj->anim_frame = 0;
            else
                obj->anim_frame = new_anim->frames_count - 1;
        }
        PlaySnd(obj->eta[obj->main_etat][obj->sub_etat].sound, obj->id);
        break;
    case ANIMMODE_RESET:
        if (!(eta->flags & 0x10))
            obj->anim_frame = 0;
        else
            obj->anim_frame = new_anim->frames_count - 1;
        PlaySnd(obj->eta[obj->main_etat][obj->sub_etat].sound, obj->id);
        break;
    }

    if (obj->anim_frame >= new_anim->frames_count || obj->anim_frame == 0xFF)
    {
        obj->sub_etat = eta->next_sub_etat;
        obj->main_etat = eta->next_main_etat;
        eta = &obj->eta[obj->main_etat][obj->sub_etat];

        obj->anim_index = eta->anim_index;
        new_anim = &obj->animations[obj->anim_index];
        if (
            (
                (
                    obj->type == TYPE_RAYMAN &&
                    ray_old_sub_etat == 8 && (ray_old_main_etat == 2 || ray_old_main_etat == 6) &&
                    obj->sub_etat != ray_old_sub_etat
                ) ||
                (
                    ray_old_sub_etat == 61 && ray_old_main_etat == 0 &&
                    obj->sub_etat != ray_old_sub_etat
                )
            ) && ray.iframes_timer > 60
        )
            ray.iframes_timer = 60;

        if (eta->flags & 0x10)
            new_frame = new_anim->frames_count - 1;
        else
            new_frame = 0;
        obj->anim_frame = new_frame;
        PlaySnd(obj->eta[obj->main_etat][obj->sub_etat].sound, obj->id);
    }

    obj->change_anim_mode = ANIMMODE_NONE;
    if (obj->flags & FLG(OBJ_FOLLOW_ENABLED))
        CALC_FOLLOW_SPRITE_SPEED(obj, new_anim, old_anim, old_frame);

    changed = (old_frame != obj->anim_frame || old_ind != obj->anim_index);
    obj->flags = (obj->flags & ~FLG(OBJ_FLAG_A)) | (changed << OBJ_FLAG_A);
}

/* 2C89C 8015109C -O2 -msoft-float */
s16 prof_in_bloc(Obj *obj)
{
    s32 y = obj->y_pos + obj->offset_by;
    return y - (y / 16 * 16);
}

/* 2C8D0 801510D0 -O2 -msoft-float */
void do_boing(Obj *obj, u8 main_etat, u8 sub_etat)
{
    if (obj->speed_y < 2)
    {
        obj->speed_y = 0;
        set_main_and_sub_etat(obj, main_etat, sub_etat);
        if (main_etat != 2)
            recale_position(obj);
    }
    else
    {
        if (horloge[2] == 0)
        {
            switch (obj->btypes[0])
            {
            case BTYP_NONE:
                break;
            case BTYP_SOLID_RIGHT_45:
            case BTYP_SLIPPERY_RIGHT_45:
                obj->speed_y = 1 - (obj->speed_y >> 1);
                obj->speed_x -= 2;
                break;
            case BTYP_SOLID_LEFT_45:
            case BTYP_SLIPPERY_LEFT_45:
                obj->speed_y = 1 - (obj->speed_y >> 1);
                obj->speed_x += 2;
                break;
            case BTYP_SOLID_RIGHT1_30:
            case BTYP_SOLID_RIGHT2_30:
            case BTYP_SLIPPERY_RIGHT1_30:
            case BTYP_SLIPPERY_RIGHT2_30:
                obj->speed_y = 1 - ((obj->speed_y + 1) >> 1);
                obj->speed_x--;
                break;
            case BTYP_SOLID_LEFT1_30:
            case BTYP_SOLID_LEFT2_30:
            case BTYP_SLIPPERY_LEFT1_30:
            case BTYP_SLIPPERY_LEFT2_30:
                obj->speed_y = 1 - ((obj->speed_y + 1) >> 1);
                obj->speed_x++;
                break;
            case BTYP_SOLID_PASSTHROUGH:
            case BTYP_SOLID:
            case BTYP_SLIPPERY:
                obj->speed_y = -((obj->speed_y + 1) >> 1);
                break;
            case BTYP_RESSORT:
                obj->speed_y = -((obj->speed_y + 3) >> 1);
                break;
            }
        }

        if (obj->speed_y < 0)
            set_sub_etat(obj, 0);
    }
}

/* 2CA58 80151258 -O2 -msoft-float */
u8 underSlope(Obj *obj)
{
    u8 res = false;
    if (block_flags[obj->btypes[0]] & FLG(BLOCK_FULLY_SOLID))
        res = block_flags[obj->btypes[3]] >> BLOCK_SLOPE & 1;

    return res;
}

/* 2CAAC 801512AC -O2 -msoft-float */
void DO_STONEBOMB_REBOND(Obj *obj)
{
    s16 new_spd_x; s16 new_spd_y;
    ObjType obj_type = obj->type;

    if (obj_type == TYPE_STONEBOMB2)
    {
        new_spd_x = 32;
        new_spd_y = -4;
    }
    else if (obj_type == TYPE_STONEBOMB3)
    {
        new_spd_x = 48;
        new_spd_y = -6;
    }

    if (underSlope(obj))
        obj->btypes[0] = obj->btypes[3];

    switch (obj->btypes[0])
    {
    case BTYP_SOLID_LEFT1_30:
    case BTYP_SOLID_LEFT2_30:
    case BTYP_SLIPPERY_LEFT1_30:
    case BTYP_SLIPPERY_LEFT2_30:
        obj->speed_y = new_spd_y;
        obj->speed_x = new_spd_x;
        break;
    case BTYP_SOLID_RIGHT1_30:
    case BTYP_SOLID_RIGHT2_30:
    case BTYP_SLIPPERY_RIGHT1_30:
    case BTYP_SLIPPERY_RIGHT2_30:
        obj->speed_y = new_spd_y;
        obj->speed_x = -new_spd_x;
        break;
    case BTYP_SOLID_LEFT_45:
    case BTYP_SLIPPERY_LEFT_45:
        obj->speed_y = new_spd_y + 2;
        obj->speed_x = new_spd_x + 16;
        break;
    case BTYP_SOLID_RIGHT_45:
    case BTYP_SLIPPERY_RIGHT_45:
        obj->speed_y = new_spd_y + 2;
        obj->speed_x = -16 - new_spd_x;
        break;
    case BTYP_SOLID_PASSTHROUGH:
    case BTYP_SOLID:
    case BTYP_SLIPPERY:
        obj->speed_y = new_spd_y;
        break;
    case BTYP_RESSORT:
        obj->speed_y = new_spd_y - 3;
        break;
    }
    obj->gravity_value_1 = 0;
    obj->gravity_value_2 = 2;
}

/* 2CBC4 801513C4 -O2 -msoft-float */
void DO_THROWN_BOMB_REBOND(Obj *obj, s16 pesanteur, s16 param_3)
{
    ObjType old_type;
    u8 under;
    u8 btyp;
    u8 anim_speed;
    s32 mul_45 = 5;
    s32 mul_30 = 3;
    u8 div_45 = 1;
    u8 div_30 = 1;

    if (obj->main_etat == 2)
    {
        if (obj->sub_etat == 1)
        {
            DO_STONE_EXPLOSION(obj);
            return;
        }
        if (obj->sub_etat == 0)
        {
            old_type = obj->type;
            obj->type = TYPE_STONEBOMB2;
            DO_STONEBOMB_REBOND(obj);
            obj->type = old_type;
            return;
        }
    }

    if (obj->speed_y >= 0)
    {
        under = underSlope(obj);
        if (under)
            btyp = obj->btypes[3];
        else
            btyp = obj->btypes[0];

        switch (btyp)
        {
        case BTYP_NONE:
        case BTYP_SLIPPERY:
            break;
        case BTYP_SOLID_RIGHT_45:
        case BTYP_SLIPPERY_RIGHT_45:
            if (obj->speed_y == 0)
                obj->speed_y++;
            obj->speed_x -= mul_45 * obj->speed_y / div_45;
            break;
        case BTYP_SOLID_LEFT_45:
        case BTYP_SLIPPERY_LEFT_45:
            if (obj->speed_y == 0)
                obj->speed_y++;
            obj->speed_x += mul_45 * obj->speed_y / div_45;
            break;
        case BTYP_SOLID_RIGHT1_30:
        case BTYP_SOLID_RIGHT2_30:
        case BTYP_SLIPPERY_RIGHT1_30:
        case BTYP_SLIPPERY_RIGHT2_30:
            if (obj->speed_y == 0)
                obj->speed_y++;
            obj->speed_x -= mul_30 * obj->speed_y / div_30;
            break;
        case BTYP_SOLID_LEFT1_30:
        case BTYP_SOLID_LEFT2_30:
        case BTYP_SLIPPERY_LEFT1_30:
        case BTYP_SLIPPERY_LEFT2_30:
            if (obj->speed_y == 0)
                obj->speed_y++;
            obj->speed_x += mul_30 * obj->speed_y / div_30;
            break;
        case BTYP_RESSORT:
            if (obj->speed_y == 0)
                obj->speed_y++;
            break;
        }
        if (param_3 > 0)
        {
            if (obj->speed_y >= 2)
            {
                obj->speed_y = param_3 - obj->speed_y;
                if (pesanteur)
                    obj->speed_y++;
            }
            else
                obj->speed_y = 0;
        }
        else
            obj->speed_y = -3;

        if (under)
        {
            while (
                BTYP(
                    obj->x_pos + obj->offset_bx,
                    obj->y_pos + obj->offset_by
                ) == obj->btypes[0]
            )
                obj->y_pos--;

            recale_position(obj);
            calc_btyp(obj);
        }
        else if (
            block_flags[obj->btypes[0]] & FLG(BLOCK_FULLY_SOLID) &&
            prof_in_bloc(obj) >= 4 && obj->speed_y < 3
        )
        {
            if (obj->speed_y == 0)
                obj->speed_y = 1;
        }
        else
            recale_position(obj);
    }
    obj->gravity_value_1 = 0;
    anim_speed = obj->eta[obj->main_etat][obj->sub_etat].anim_speed >> 4;
    if (!(anim_speed == 10 || anim_speed == 11))
        obj->gravity_value_2 = 0;
}

/* 2D008 80151808 -O2 -msoft-float */
void DO_FRUIT_REBOND(Obj *obj, s16 pesanteur, s16 param_3)
{
    u8 under;
    u8 btyp;
    ObjType obj_type;
    u8 anim_speed;
    s16 accel_x;
    s16 speed_x_bnd;
    s32 mul_45;
    s32 mul_30;
    u8 div_45;
    u8 div_30;

    if (obj->type == TYPE_GRAINE)
    {
        accel_x = 1;
        speed_x_bnd = 1;
        mul_45 = 1;
        mul_30 = 1;
        div_45 = 1;
        div_30 = 2;
    }
    else
    {
        accel_x = 5;
        speed_x_bnd = 4;
        mul_45 = 5;
        mul_30 = 3;
        div_45 = 1;
        div_30 = 1;
    }

    if (obj->speed_y >= 0)
    {
        if (obj->speed_x > 0)
            obj->speed_x -= accel_x;
        else if (obj->speed_x < 0)
            obj->speed_x += accel_x;

        if (obj->speed_x >= -speed_x_bnd && obj->speed_x <= speed_x_bnd)
            obj->speed_x = 0;

        under = underSlope(obj);
        if (under)
            btyp = obj->btypes[3];
        else
            btyp = obj->btypes[0];

        switch (btyp)
        {
        case BTYP_NONE:
        case BTYP_SLIPPERY:
            break;
        case BTYP_SOLID_RIGHT_45:
        case BTYP_SLIPPERY_RIGHT_45:
            if (obj->speed_y == 0)
                obj->speed_y++;
            obj->speed_x -= mul_45 * obj->speed_y / div_45;
            break;
        case BTYP_SOLID_LEFT_45:
        case BTYP_SLIPPERY_LEFT_45:
            if (obj->speed_y == 0)
                obj->speed_y++;
            obj->speed_x += mul_45 * obj->speed_y / div_45;
            break;
        case BTYP_SOLID_RIGHT1_30:
        case BTYP_SOLID_RIGHT2_30:
        case BTYP_SLIPPERY_RIGHT1_30:
        case BTYP_SLIPPERY_RIGHT2_30:
            if (obj->speed_y == 0)
                obj->speed_y++;
            obj->speed_x -= mul_30 * obj->speed_y / div_30;
            break;
        case BTYP_SOLID_LEFT1_30:
        case BTYP_SOLID_LEFT2_30:
        case BTYP_SLIPPERY_LEFT1_30:
        case BTYP_SLIPPERY_LEFT2_30:
            if (obj->speed_y == 0)
                obj->speed_y++;
            obj->speed_x += mul_30 * obj->speed_y / div_30;
            break;
        case BTYP_RESSORT:
            if (obj->speed_y == 0)
                obj->speed_y++;
            break;
        }

        if (param_3 > 0)
        {
            if (obj->speed_y >= 2)
            {
                obj->speed_y = param_3 - obj->speed_y;
                if (pesanteur)
                    obj->speed_y++;
            }
            else
            {
                obj->speed_y = 0;
                obj->hit_points = 2;
            }
        }
        else
        {
            obj_type = obj->type;
            if (
                obj_type == TYPE_FALLING_OBJ || obj_type == TYPE_FALLING_OBJ2 || obj_type == TYPE_FALLING_OBJ3 ||
                obj_type == TYPE_FALLING_YING || obj_type == TYPE_FALLING_YING_OUYE
            )
            {
                if (ray.field20_0x36 == obj->id)
                {
                    if (ray.scale == 0)
                        obj->speed_y = -3;
                    else
                        obj->speed_y = -4;
                }
                else
                    obj->speed_y = -5;

                if (obj->type == TYPE_FALLING_YING_OUYE)
                    obj->speed_y++;
            }
            else
                obj->speed_y = -3;
        }

        if (under)
        {
            while (
                BTYP(
                    obj->x_pos + obj->offset_bx,
                    obj->y_pos + obj->offset_by
                ) == obj->btypes[0]
            )
                obj->y_pos--;

            calc_btyp(obj);
            recale_position(obj);
        }
        else if (
            block_flags[obj->btypes[0]] & FLG(BLOCK_FULLY_SOLID) &&
            prof_in_bloc(obj) >= 4 && obj->speed_y < 3
        )
        {
            if (obj->speed_y == 0)
                obj->speed_y = 1;
        }
        else
            recale_position(obj);
    }

    obj->gravity_value_1 = 0;
    anim_speed = obj->eta[obj->main_etat][obj->sub_etat].anim_speed >> 4;
    if (!(anim_speed == 10 || anim_speed == 11))
        obj->gravity_value_2 = 0;
}

/* 2D4F8 80151CF8 -O2 -msoft-float */
void Drop_Atter(Obj *obj)
{
    set_main_and_sub_etat(obj, 2, 3);
    obj->speed_y = 0;
    obj->speed_x = 0;
}

/* 2D52C 80151D2C -O2 -msoft-float */
void BadGuyAtter(Obj *obj)
{
    u8 sub_etat;
    u8 label;

    recale_position(obj);
    if (obj->hit_points != obj->init_hit_points)
    {
        if (obj->eta[obj->main_etat][obj->sub_etat].flags & 0x40)
            sub_etat = 2;
        else
            sub_etat = 11;
        set_main_and_sub_etat(obj, 1, sub_etat);
    }
    else
    {
        set_main_and_sub_etat(obj, 1, 0);
        obj->flags |= FLG(OBJ_READ_CMDS);
    }

    calc_obj_dir(obj);
    if (obj->flags & FLG(OBJ_FLIP_X))
        label = 3;
    else
        label = 2;
    skipToLabel(obj, label, true);
}

/* 2D5F8 80151DF8 -O2 -msoft-float */
void MiteAtter(Obj *obj)
{
    if (obj->speed_y > 0)
    {
        recale_position(obj);
        skipToLabel(obj, 2, true);
        if (obj->field20_0x36 > 500)
            obj->field20_0x36 = 0;
    }
}

/* 2D658 80151E58 -O2 -msoft-float */
void Clown_Music_Atter(Obj *obj)
{
    if (obj->hit_points != obj->init_hit_points)
    {
        if (obj->main_etat == 2 && obj->sub_etat == 1)
        {
            set_main_and_sub_etat(obj, 0, 2);
            obj->speed_x = 0;
            obj->flags |= FLG(OBJ_READ_CMDS);
        }
    }
    else
    {
        set_main_etat(obj, 1);
        set_sub_etat(obj, 0);
        obj->flags |= FLG(OBJ_READ_CMDS);
    }

    obj->speed_y = 0;
    if (!(obj->flags & FLG(OBJ_FLIP_X)))
        skipToLabel(obj, 2, true);
    else
        skipToLabel(obj, 3, true);
}

/* 2D71C 80151F1C -O2 -msoft-float */
void LidolPinkAtter(Obj *obj)
{
    if (gerbe && obj->sub_etat == 1)
        do_boing(obj, 1, 0);
    else if (obj->sub_etat != 0)
    {
        skipToLabel(obj, 1, true);
        obj->speed_y = 0;
        recale_position(obj);
    }
}

/* 2D790 80151F90 -O2 -msoft-float */
void stoneDogAtter(Obj *obj)
{
    if (obj->sub_etat == 2)
    {
        skipToLabel(obj, 4, true);
        recale_position(obj);
    }
}

/* 2D7D0 80151FD0 -O2 -msoft-float */
void stoneDogBounces(Obj *obj)
{
    s32 x = obj->x_pos + obj->offset_bx;
    s32 y = obj->y_pos + obj->offset_by;
    s32 block_l = mp.map[((x - 2) >> 4) + ((y >> 4) * mp.width)] >> 10;
    s32 block_r = mp.map[((x + 2) >> 4) + ((y >> 4) * mp.width)] >> 10;

    if (
        obj->main_etat == 2 &&
        !(block_flags[obj->btypes[0]] >> BLOCK_SOLID & 1) &&
        (
            (block_flags[block_l] & FLG(BLOCK_FULLY_SOLID) && !(obj->flags & FLG(OBJ_FLIP_X))) ||
            (block_flags[block_r] & FLG(BLOCK_FULLY_SOLID) && obj->flags & FLG(OBJ_FLIP_X))
        )
    )
    {
        if (obj->speed_y < 0)
        {
            if (obj->flags & FLG(OBJ_FLIP_X))
                skipToLabel(obj, 6, true);
            else
                skipToLabel(obj, 7, true);
        }
        else
        {
            obj->x_pos += obj->speed_x / 16;
            skipToLabel(obj, 4, true);
            obj->flags = obj->flags & ~FLG(OBJ_FLIP_X) | ((obj->flags >> OBJ_FLIP_X ^ 1) & 1) << OBJ_FLIP_X;
        }
    }
}

/* 2D998 80152198 -O2 -msoft-float */
void Spider_Atter(Obj *obj)
{
    set_main_and_sub_etat(obj, 1, 0);
    if (obj->flags & FLG(OBJ_FLIP_X))
        skipToLabel(obj, 3, true);
    else
        skipToLabel(obj, 1, true);
}

/* 2D9EC 801521EC -O2 -msoft-float */
void trompetteAtter(Obj *obj)
{
    skipToLabel(obj, 8, true);
    recale_position(obj);
}

/* 2DA20 80152220 -O2 -msoft-float */
void NormalAtter(Obj *obj)
{
    set_main_and_sub_etat(obj, obj->init_main_etat, obj->init_sub_etat);
    recale_position(obj);
}

/* 2DA58 80152258 -O2 -msoft-float */
void OBJ_IN_THE_AIR(Obj *obj)
{
    s16 pesanteur;
    s16 spd_y;
    s16 spr_x; s16 spr_y; s16 spr_w; s16 spr_h;
    s16 flip_x;
    u8 anim_speed_div = obj->eta[obj->main_etat][obj->sub_etat].anim_speed >> 4;

    if (!(anim_speed_div == 10 || anim_speed_div == 11))
    {
        obj->gravity_value_1++;
        if (obj->gravity_value_1 > 2)
            obj->gravity_value_1 = 0;

        obj->gravity_value_2++;
        if (obj->gravity_value_2 > 3)
            obj->gravity_value_2 = 0;
    }

    pesanteur = DO_PESANTEUR(obj);
    if (obj->type == TYPE_LIDOLPINK)
    {
        if (obj->speed_y >= 0 && obj->sub_etat == 0)
            set_sub_etat(obj, 1);

        if (!gerbe && obj->speed_y > 2 && obj->sub_etat == 1)
        {
            set_sub_etat(obj, 2);
            obj->speed_x = 0;
        }
    }
    else if (obj->type == TYPE_STONEDOG || obj->type == TYPE_STONEDOG2)
    {
        stoneDogBounces(obj);
        if (obj->main_etat == 2)
        {
            spd_y = obj->speed_y;
            if (spd_y > 0)
            {
                if (obj->sub_etat != 2)
                    set_sub_etat(obj, 2);
            }
            else if (spd_y < 0 && (block_flags[(u8) calc_typ_trav(obj, 1)] >> BLOCK_FULLY_SOLID & 1))
                obj->speed_y = 0;
        }
    }
    else if (obj->type == TYPE_NOTE1)
    {
        if (--obj->iframes_timer == 0)
            DO_EXPLOSE_NOTE1(obj);
    }

    if (
        flags[obj->type].flags3 >> OBJ3_STOP_MOVING_UP_WHEN_HIT_BLOCK & 1 &&
        obj->speed_y < 0
    )
    {
        if (obj->flags & FLG(OBJ_FOLLOW_ENABLED))
        {
            GET_SPRITE_POS(obj, obj->follow_sprite, &spr_x, &spr_y, &spr_w, &spr_h);
            spr_x = obj->x_pos + obj->offset_bx;
            spr_y = spr_y + obj->offset_hy;
        }
        else
        {
            spr_x = obj->x_pos + obj->offset_bx;
            spr_y = obj->y_pos + obj->offset_hy;
        }

        if (block_flags[BTYP(spr_x, spr_y + obj->speed_y)] >> BLOCK_FLAG_4 & 1)
            obj->speed_y = 0;
    }
    if (
        flags[obj->type].flags2 >> OBJ2_MOVE_ON_BLOCK & 1 &&
        block_flags[obj->btypes[0]] >> BLOCK_SOLID & 1
    )
    {
        switch (obj->type)
        {
        case TYPE_TROMPETTE:
            trompetteAtter(obj);
            break;
        case TYPE_HYBRIDE_MOSAMS:
            calc_obj_dir(obj);
            recale_position(obj);
            skipToLabel(obj, 3, true);
            if (ray.main_etat != 2)
            {
                allocateLandingSmoke(obj);
                set_main_and_sub_etat(&ray, 0, 0);
                button_released = 1;
                ray_jump();
                ray.speed_y = -8;
            }
            screen_trembling = 1;
            break;
        case TYPE_BLACKTOON1:
            switch (obj->follow_sprite)
            {
            case 3:
            case 5:
            case 6:
                break;
            case 7:
                obj->field56_0x69 = 2;
                calc_obj_dir(obj);
            case 1:
            case 4:
                set_main_and_sub_etat(obj, 1, 0);
                if (obj->flags & FLG(OBJ_FLIP_X))
                    skipToLabel(obj, 3, true);
                else
                    skipToLabel(obj, 2, true);

                recale_position(obj);
                obj->speed_y = 0;
                break;
            case 2:
                set_main_and_sub_etat(obj, 0, 0);
                recale_position(obj);
                obj->speed_y = 0;
                break;
            }
            break;
        case TYPE_WASHING_MACHINE:
            if (obj->speed_y > 0)
            {
                recale_position(obj);
                obj->speed_y = -obj->speed_y;
            }
            break;
        case TYPE_DROP:
            Drop_Atter(obj);
            break;
        case TYPE_MITE:
        case TYPE_MITE2:
            MiteAtter(obj);
            break;
        case TYPE_STONEWOMAN:
            if (obj->speed_y >= 0)
            {
                skipToLabel(obj, 16, true);
                obj->field56_0x69 = 0;
            }
            break;
        case TYPE_TNT_BOMB:
            PlaySnd(187, obj->id);
            BombExplosion(obj);
            break;
        case TYPE_BADGUY1:
        case TYPE_BADGUY2:
        case TYPE_BADGUY3:
            BadGuyAtter(obj);
            break;
        case TYPE_STONEBOMB2:
        case TYPE_STONEBOMB3:
            if (obj->speed_y != 0)
                PlaySnd(200, obj->id);
            DO_STONEBOMB_REBOND(obj);
            break;
        case TYPE_STONEBOMB:
            if (obj->speed_y != 0)
                PlaySnd(200, obj->id);
            DO_THROWN_BOMB_REBOND(obj, pesanteur, 1);
            break;
        case TYPE_STONEDOG:
        case TYPE_STONEDOG2:
            stoneDogAtter(obj);
            break;
        case TYPE_PIRATE_BOMB:
            DO_FRUIT_REBOND(obj, pesanteur, 1);
            break;
        case TYPE_MST_SHAKY_FRUIT:
            if (obj->field23_0x3c != 0)
            {
                PlaySnd(45, obj->id);
                obj->speed_y = 6;
                DO_FRUIT_REBOND(obj, 1, 1);
                obj->field23_0x3c--;
            }
            break;
        case TYPE_MST_FRUIT1:
            if (obj->field23_0x3c != 0)
            {
                PlaySnd(45, obj->id);
                obj->speed_y = 7;
                DO_FRUIT_REBOND(obj, 1, 1);
                obj->field23_0x3c--;
            }
            break;
        case TYPE_MST_FRUIT2:
            if (obj->field23_0x3c != 0)
            {
                PlaySnd(45, obj->id);
                obj->speed_y = 6;
                DO_THROWN_BOMB_REBOND(obj, 1, 1);
                obj->field23_0x3c--;
            }
            break;
        case TYPE_FALLING_OBJ:
        case TYPE_FALLING_OBJ2:
        case TYPE_FALLING_OBJ3:
        case TYPE_FALLING_YING:
        case TYPE_FALLING_YING_OUYE:
        case TYPE_GRAINE:
        case TYPE_BLACKTOON_EYES:
            switch (obj->type)
            {
            case TYPE_FALLING_OBJ:
            case TYPE_FALLING_OBJ3:
            case TYPE_FALLING_OBJ2:
                PlaySnd(45, obj->id);
                break;
            case TYPE_FALLING_YING:
            case TYPE_FALLING_YING_OUYE:
                PlaySnd(140, obj->id);
                break;
            case TYPE_GRAINE:
            case TYPE_BLACKTOON_EYES:
                PlaySnd(0, obj->id);
                break;
            }
            DO_FRUIT_REBOND(obj, pesanteur, 0);
            break;
        case TYPE_CAGE:
            set_main_and_sub_etat(obj, 0, 11);
            obj->speed_y = 0;
            break;
        case TYPE_LIDOLPINK:
            LidolPinkAtter(obj);
            break;
        case TYPE_PIRATE_GUETTEUR:
        case TYPE_PIRATE_GUETTEUR2:
            if (obj->sub_etat == 2)
                set_main_and_sub_etat(obj, 0, 7);
            else if (obj->speed_y >= 0)
                set_main_and_sub_etat(obj, 0, 10);
            recale_position(obj);
            obj->speed_y = 0;
            obj->speed_x = 0;
            break;
        case TYPE_PIRATE_NGAWE:
            recale_position(obj);
            set_main_and_sub_etat(obj, 0, 5);
            obj->speed_y = 0;
            obj->speed_x = 0;
            break;
        case TYPE_SUPERHELICO:
            obj->speed_x = 0;
            obj->speed_y = 0;
            break;
        case TYPE_NOTE0:
        case TYPE_NOTE1:
        case TYPE_NOTE2:
        case TYPE_BONNE_NOTE:
        case TYPE_NOTE3:
            DO_NOTE_REBOND(obj);
            break;
        case TYPE_BBL:
            DO_BBL_REBOND(obj);
            break;
        case TYPE_BIG_CLOWN:
        case TYPE_WAT_CLOWN:
            Clown_Music_Atter(obj);
            break;
        case TYPE_SPIDER:
            Spider_Atter(obj);
            break;
        case TYPE_BB1:
            if (obj->iframes_timer < 10)
                DO_BBMONT_ATTER(obj);
            break;
        case TYPE_BB12:
            DO_BBMONT2_ATTER(obj);
            break;
        case TYPE_BB13:
            DO_BBMONT3_ATTER(obj);
            break;
        case TYPE_SAXO2:
            DO_SAXO2_ATTER(obj);
            break;
        case TYPE_SAXO:
            DO_SAXO_ATTER(obj);
            break;
        case TYPE_MAMA_PIRATE:
            DO_PMA_ATTER(obj);
            break;
        case TYPE_COUTEAU:
            DO_COU_ATTER(obj);
            break;
        case TYPE_BOUT_TOTEM:
            DO_TOTBT_REBOND(obj);
            break;
        case TYPE_SPIDER_PLAFOND:
            if (obj->main_etat == 2 && obj->speed_y > 0)
            {
                set_main_and_sub_etat(obj, 0, 29);
                obj->speed_x = 0;
                obj->speed_y = 0;
                flip_x = ray.x_pos > obj->x_pos;
                obj->flags = obj->flags & ~FLG(OBJ_FLIP_X) | flip_x << OBJ_FLIP_X;
            }
            break;
        case TYPE_BALLE1:
        case TYPE_BALLE2:
        case TYPE_BIG_BOING_PLAT:
        case TYPE_BLACK_FIST:
        case TYPE_BLACK_RAY:
        case TYPE_BNOTE:
        case TYPE_BOING_PLAT:
        case TYPE_BULLET:
        case TYPE_CORDEBAS:
        case TYPE_DARK_PHASE2:
        case TYPE_DARK:
        case TYPE_MARACAS_BAS:
        case TYPE_MOSKITO:
        case TYPE_MOSKITO2:
        case TYPE_MST_SCROLL:
        case TYPE_PI_BOUM:
        case TYPE_POI1:
        case TYPE_POI2:
        case TYPE_POI3:
        case TYPE_RING:
        case TYPE_SCORPION:
        case TYPE_SPACE_MAMA:
        case TYPE_SPACE_MAMA2:
        case TYPE_TAMBOUR1:
        case TYPE_TAMBOUR2:
            break;
        default:
            NormalAtter(obj);
            break;
        }
    }
    if (flags[obj->type].flags1 >> OBJ1_USE_INSTANT_SPEED_Y & 1)
    {
        MIN_2(obj->speed_y, 96);
        MAX_2(obj->speed_y, -128)
    }
    else
    {
        MIN_2(obj->speed_y, 6);
        MAX_2(obj->speed_y, -8)
    }
}

/* 2E458 80152C58 -O2 -msoft-float */
void test_fall_in_water(Obj *obj)
{
    if (obj->btypes[0] == BTYP_WATER && !(obj->type == TYPE_RAYMAN && ray.main_etat == 6))
    {
        if (obj->type == TYPE_MST_FRUIT2)
            obj->flags &= ~FLG(OBJ_ALIVE);
        else
        {
            if (flags[obj->type].flags2 >> OBJ2_FALL_IN_WATER & 1)
            {
                if (!(obj->flags & FLG(OBJ_FLAG_9)))
                {
                    allocate_splash(obj);
                    obj->speed_y = 0;
                    obj->speed_x = 0;
                }
                if (flags[obj->type].flags3 >> OBJ3_DIE_IN_WATER & 1)
                {
                    obj->flags &= ~FLG(OBJ_ACTIVE);
                    obj->y_pos = ymap + 484;
                }
            }
        }
    }
}

/* still rather difficult to read tbh? */
/* 2E55C 80152D5C -O2 -msoft-float */
void MOVE_OBJECT(Obj *obj)
{    
    s16 speed_x_1; s16 speed_y_1;
    s16 speed_x_2; s16 speed_y_2;
    s16 x_pos_1;
    s16 x_pos_2;
    s16 y_pos;
    u8 unk_1;

    if (*(s32 *) &obj->speed_x != 0)
    {
        speed_x_1 = obj->speed_x;
        speed_y_1 = obj->speed_y;
        if (
            flags[obj->type].flags2 >> OBJ2_INCREASE_SPEED_X &&
            obj->field56_0x69 == 1 && horloge[20] == 0
        )
        {
            if (speed_x_1 <= 0)
                obj->speed_x = speed_x_1 + 1;
            else
                obj->speed_x = speed_x_1 - 1;
            if (obj->speed_x == 0)
                obj->field56_0x69 = 0;
        }

        if (obj->type == TYPE_POING)
        {
            poing.field0_0x0 += ashl16(speed_y_1, 4);
            obj->y_pos = poing.field0_0x0 >> 4;
            obj->x_pos = obj->x_pos + obj->speed_x;
        }
        else
        {
            if ((flags[obj->type].flags1 >> OBJ1_USE_INSTANT_SPEED_Y) & 1)
                speed_y_2 = instantSpeed(obj->speed_y);
            else
                speed_y_2 = speed_y_1;

            if ((flags[obj->type].flags1 >> OBJ1_USE_INSTANT_SPEED_X) & 1)
                speed_x_2 = instantSpeed(obj->speed_x);
            else
                speed_x_2 = speed_x_1;

            if (flags[obj->type].flags2 >> OBJ2_UTURN_ON_BLOCK & 1)
            {
                x_pos_1 = obj->x_pos + obj->offset_bx;
                x_pos_2 = x_pos_1 + speed_x_2;
                y_pos = obj->y_pos + obj->offset_by - 8;
                if (
                    (
                        !(block_flags[BTYP(x_pos_1, y_pos)] >> BLOCK_FLAG_4 & 1) &&
                        block_flags[BTYP(x_pos_2, y_pos)] >> BLOCK_FLAG_4 & 1
                    ) ||
                    x_pos_2 < 0 || (x_pos_2 > xmapmax + SCREEN_WIDTH)
                )
                {
                    speed_x_2 = -speed_x_2;
                    obj->speed_x = -obj->speed_x;
                }
            }
            obj->x_pos += speed_x_2;
            obj->y_pos += speed_y_2;
        }

        unk_1 = false;
        if (!(speed_x_2 == 0 && speed_y_2 == 0))
            unk_1 = true;
        obj->flags = obj->flags & ~FLG(OBJ_FLAG_B) | (unk_1 << OBJ_FLAG_B);
        test_fall_in_water(obj);
    }
    else
        obj->flags &= ~FLG(OBJ_FLAG_B);
}

/* 2E860 80153060 -O2 -msoft-float */
void DO_RAY_IN_ZONE(Obj *obj)
{
    s16 blkt_x; s16 blkt_y; s16 blkt_w; s16 blkt_h;
    u8 lbl;
    u8 sub_etat; /* ??? */

    if (OBJ_IN_ZONE(obj))
    {
        switch (obj->type)
        {
        case TYPE_MUS_WAIT:
            if (obj->sub_etat == 1)
                set_sub_etat(obj, 5);
            break;
        case TYPE_MST_SHAKY_FRUIT:
            if (!(obj->main_etat == 2 || obj->sub_etat == 1))
            {
                obj->field23_0x3c = 1;
                skipToLabel(obj, 0, true);
                obj->gravity_value_2 = 4;
            }
            break;
        case TYPE_FEE:
            if (obj->sub_etat == 0)
            {
                if (ray.main_etat == 2)
                {
                    ray.speed_x = 0;
                    ray.field24_0x3e = 0;
                    ray_in_fee_zone = true;
                    decalage_en_cours = 0;
                }
                else if (
                    ray.main_etat == 0 || ray.main_etat == 1 ||
                    (ray.main_etat == 3 && ray.sub_etat == 20)
                )
                {
                    remoteRayXToReach = obj->x_pos - (ray.offset_bx + 2);
                    if (ray.x_pos & 1) /* ??? */
                        remoteRayXToReach |= 1;
                    else
                        remoteRayXToReach &= ~1;

                    ray_in_fee_zone = false;
                }
            }
            else
                ray_in_fee_zone = false;
            break;
        case TYPE_SAXO3:
            DO_SAXO3_DEBUT(obj);
            break;
        case TYPE_SCROLL_SAX:
            DO_SAXO_MARCHE(obj->hit_points);
            break;
        case TYPE_BB1_VIT:
            DO_BBMONT2_MARCHE(obj->hit_points);
            break;
        case TYPE_MST_SCROLL:
            DO_MST_CHANGE_COMMAND(obj->hit_points);
            break;
        case TYPE_BLACKTOON1:
            switch (obj->follow_sprite)
            {
            case 7:
                if (
                    obj->main_etat == 1 && obj->sub_etat == 1 &&
                    ray.main_etat != 2
                )
                    skipToLabel(obj, 5, true);
                break;
            case 4:
                if (ray.main_etat != 2)
                {
                    GET_ANIM_POS(obj, &blkt_x, &blkt_y, &blkt_w, &blkt_h);
                    blkt_y -= obj->detect_zone + blkt_h;
                    blkt_x -= blkt_w >> 1;
                    blkt_w += blkt_w;
                    blkt_h += obj->detect_zone;
                    if (
                        obj->main_etat == 1 && obj->sub_etat == 0 &&
                        inter_box(
                            blkt_x, blkt_y, blkt_w, blkt_h,
                            ray_zdc_x, ray_zdc_y, ray_zdc_w, ray_zdc_h
                        )
                    )
                    {
                        calc_obj_dir(obj);
                        obj->field23_0x3c = ray_zdc_y - obj->offset_hy;
                        if (obj->field23_0x3c < obj->y_pos - 16)
                        {
                            skipToLabel(obj, 4, true);
                            obj->gravity_value_1 = 0;
                            obj->gravity_value_2 = 6;
                            obj->y_pos--;
                        }
                    }
                }
                break;
            case 3:
                if (
                    obj->main_etat == 0 && obj->sub_etat == 0 &&
                    ray.main_etat != 2
                )
                {
                    calc_obj_dir(obj);
                    obj->field23_0x3c = ray.y_pos + ray.offset_hy - obj->offset_hy;
                    if (obj->field23_0x3c < obj->y_pos - 16)
                    {
                        skipToLabel(obj, 4, true);
                        obj->gravity_value_2 = 6;
                        obj->gravity_value_1 = 0;
                        obj->timer = 0xFF;
                        obj->y_pos--;
                    }
                }
                break;
            case 2:
                if (
                    obj->main_etat == 0 && obj->sub_etat == 0 &&
                    ray.main_etat != 2
                )
                {
                    calc_obj_dir(obj);
                    skipToLabel(obj, 4, true);
                    obj->gravity_value_1 = 0;
                    obj->gravity_value_2 = 6;
                    obj->y_pos--;
                }
                break;
            }
            break;
        case TYPE_STALAG:
            if (obj->sub_etat == 4)
                skipToLabel(obj, 99, true);
            break;
        case TYPE_LIDOLPINK:
            if (obj->eta[obj->main_etat][obj->sub_etat].flags & 1)
                skipToLabel(obj, 0, true);
            break;
        case TYPE_BADGUY2:
        case TYPE_BADGUY3:
            if (obj->main_etat == 1 && obj->sub_etat == 11)
                set_sub_etat(obj, 14);
            else if (
                (obj->main_etat == 0 && obj->sub_etat == 0) ||
                (obj->main_etat == 1 && obj->sub_etat == 0)
            )
            {
                set_main_and_sub_etat(obj, 1, 11);
                obj->flags &= ~FLG(OBJ_READ_CMDS);
                if (obj->flags & FLG(OBJ_FLIP_X))
                    lbl = 3;
                else
                    lbl = 2;
                skipToLabel(obj, lbl, true);
            }
            break;
        case TYPE_BADGUY1:
            if (
                (ray.flags & FLG(OBJ_FLIP_X)) != (obj->flags & FLG(OBJ_FLIP_X)) &&
                (
                    (obj->main_etat == 1 && obj->sub_etat == 0) ||
                    (obj->main_etat == 0 && obj->sub_etat == 0)
                ) && ray.main_etat == 0 && ray.sub_etat == 18
            )
            {
                obj->speed_x = 0;
                obj->speed_y = 0;
                set_main_and_sub_etat(obj, 0, 2);
                if (obj->flags & FLG(OBJ_FLIP_X))
                    skipToLabel(obj, 8, true);
                else
                    skipToLabel(obj, 7, true);
            }
            break;
        case TYPE_TROMPETTE:
            if (
                obj->timer == 0 &&
                (
                    (obj->main_etat == 0 && obj->sub_etat == 0) ||
                    (obj->main_etat == 1 && obj->sub_etat == 0)
                )
            )
                skipToLabel(obj, 5, true);
            break;
        case TYPE_BIG_CLOWN:
        case TYPE_WAT_CLOWN:
            if (
                (obj->main_etat == 0 && obj->sub_etat == 0) ||
                (obj->main_etat == 1 && obj->sub_etat == 0)
            )
                skipToLabel(obj, 5, true);
            break;
        case TYPE_CLOWN_TNT:
            if (obj->field24_0x3e == 0)
            {
                skipToLabel(obj, 7, true);
                obj->timer = 0;
                obj->field24_0x3e = 1;
            }
            break;
        case TYPE_GENEBADGUY:
            obj->field24_0x3e = 1;
            break;
        case TYPE_STONEDOG2:
            if (
                (obj->main_etat == 0 && obj->sub_etat == 0) ||
                (obj->main_etat == 1 && obj->sub_etat == 0)
            )
            {
                skipToLabel(obj, 2, true);
                obj->gravity_value_2 = 7;
                obj->gravity_value_1 = 0;
            }
            break;
        case TYPE_STONEMAN1:
        case TYPE_STONEMAN2:
            if (
                !(
                    obj->main_etat == 0 &&
                    (
                        obj->sub_etat == 1 || obj->sub_etat == 2 ||
                        obj->sub_etat == 5 || obj->sub_etat == 6 ||
                        obj->sub_etat == 3 || obj->sub_etat == 7 ||
                        obj->sub_etat == 4
                    )
                )
            )
                skipToLabel(obj, 7, true);
            break;
        case TYPE_POI3:
            if (
                !(
                    obj->main_etat == 2 &&
                    (obj->sub_etat == 16 || (sub_etat = obj->sub_etat, sub_etat == 17) || sub_etat == 18)
                ) &&
                (
                    ray.x_pos + ray.offset_bx - obj->x_pos - obj->offset_bx >= 0
                    ? obj->flags & FLG(OBJ_FLIP_X)
                    : !(obj->flags & FLG(OBJ_FLIP_X))
                )
            )
            {
                if (obj->flags & FLG(OBJ_FLIP_X))
                    obj->speed_x = 3;
                else
                    obj->speed_x = -3;

                obj->speed_y = -5;
                set_main_etat(obj, 2);
                set_sub_etat(obj, 16);
                skipToLabel(obj, 11, true);
            }
            break;
        case TYPE_SPIDER:
            if (
                obj->main_etat == 1 && obj->sub_etat == 0 &&
                obj->field24_0x3e == 0
            )
            {
                obj->anim_frame = 0;
                if (!(obj->flags & FLG(OBJ_FLIP_X)))
                {
                    obj->flags |= FLG(OBJ_FLIP_X);
                    skipToLabel(obj, 3, true);
                }
                else
                {
                    obj->flags &= ~FLG(OBJ_FLIP_X);
                    skipToLabel(obj, 1, true);
                }
                pushToLabel(obj, 5, true);
            }
            break;
        case TYPE_CHASSEUR1:
        case TYPE_CHASSEUR2:
            if (obj->main_etat == 0 && (obj->sub_etat == 0 || obj->sub_etat == 2))
            {
                obj->speed_x = 0;
                obj->speed_y = 0;
                set_main_and_sub_etat(obj, 0, 2);
                obj->flags &= ~FLG(OBJ_READ_CMDS);
                calc_obj_dir(obj);
                if (obj->flags & FLG(OBJ_FLIP_X))
                    obj->cmd = GO_RIGHT;
                else
                    obj->cmd = GO_LEFT;
            }
            break;
        case TYPE_PIRATE_NGAWE:
            NGW_REACT_TO_RAY_IN_ZONE(obj);
            break;
        case TYPE_PIRATE_GUETTEUR:
        case TYPE_PIRATE_GUETTEUR2:
            PAR_REACT_TO_RAY_IN_ZONE(obj);
            break;
        case TYPE_CAISSE_CLAIRE:
            if (obj->main_etat == 0 && obj->sub_etat == 0)
            {
                set_main_and_sub_etat(obj, 1, 0);
                if (obj->flags & FLG(OBJ_FLIP_X))
                    skipToLabel(obj, 3, true);
                else
                    skipToLabel(obj, 2, true);
            }
            break;
        case TYPE_SCORPION:
            SKO_ray_in_zone(obj);
            break;
        case TYPE_BATTEUR_FOU:
            BAT_ray_in_zone(obj);
            break;
        case TYPE_PIRATE_POELLE:
        case TYPE_PIRATE_POELLE_D:
        case TYPE_PIRATE_P_45:
        case TYPE_PIRATE_P_D_45:
            PIRATE_POELLE_REACT(obj);
            break;
        case TYPE_SPIDER_PLAFOND:
            SPIDER_PLAFOND_REACT(obj);
            break;
        case TYPE_DARK:
            DO_DARK_REACT(obj);
            break;
        case TYPE_JOE:
            if (
                obj->main_etat == 0 && obj->sub_etat == 1 &&
                !joe_exp_probleme
            )
            {
                vignet_joe_affichee = false;
                skipToLabel(obj, 2, true);
                joe_exp_probleme = true;
            }
            if (obj->main_etat == 0 && obj->sub_etat == 2)
                skipToLabel(obj, 4, true);
            break;
        }
    }
    else
    {
        if (
            obj->detect_zone_flag == 0 &&
            (obj->type == TYPE_CHASSEUR1 || obj->type == TYPE_CHASSEUR2) &&
            obj->main_etat == 0 && obj->sub_etat == 21 &&
            obj->anim_frame >= obj->animations[obj->anim_index].frames_count - 1
        )
            set_main_and_sub_etat(obj, 0, 0);
    }
}

/* 2F3B4 80153BB4 -O2 -msoft-float */
void DO_ONE_OBJECT(Obj *obj)
{
    if (flags[ot].flags0 >> OBJ0_BALLE & 1)
        DO_BALLE(obj);
    if (flags[ot].flags0 >> OBJ0_DETECT_ZONE & 1)
        SET_DETECT_ZONE_FLAG(obj);
    if (flags[ot].flags2 >> OBJ2_MOVE_ON_BLOCK & 1)
        calc_btyp(obj);
    if (flags[ot].flags1 >> OBJ1_READ_CMD & 1)
        GET_OBJ_CMD(obj);
    else
        obj->cmd = GO_NOP;

    ObjectsFonctions[ot].do_obj(obj);

    if (obj->main_etat == 2)
        OBJ_IN_THE_AIR(obj);
    if (obj->flags & FLG(OBJ_FOLLOW_ENABLED))
        SET_RAY_DIST(obj);
    else
        obj->ray_dist = 10000;
    if (flags[ot].flags1 >> OBJ1_SPECIAL_PLATFORM & 1)
        DO_SPECIAL_PLATFORM(obj);
    if (flags[ot].flags0 >> OBJ0_DETECT_ZONE & 1)
        DO_RAY_IN_ZONE(obj);
}

/* 2F5A4 80153DA4 -O2 -msoft-float */
void fptr_init(void)
{
    ObjType obj_type;
    ObjHandlers *obj_fonction;
    void (*sel_fonction)(Obj *);

    for (obj_type = 0; obj_type < LEN(ObjectsFonctions) - 1; obj_type++)
    {
        switch (obj_type)
        {
        case TYPE_POING:
            obj_fonction = &ObjectsFonctions[obj_type]; /* why does this need to happen every case??? */
            sel_fonction = DO_POING;
            break;
        case TYPE_BLACKTOON_EYES:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BLKTOON_EYES_CMD;
            break;
        case TYPE_PETIT_COUTEAU:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_PETIT_COUTEAU_COMMAND;
            break;
        case TYPE_TIRE_BOUCHON:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_TIRE_BOUCHON_COMMAND;
            break;
        case TYPE_MUS_WAIT:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_MUSICIEN;
            break;
        case TYPE_FALLING_OBJ:
        case TYPE_FALLING_OBJ2:
        case TYPE_FALLING_OBJ3:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_FALLING_OBJ_CMD;
            break;
        case TYPE_DROP:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_DROP_COMMAND;
            break;
        case TYPE_SMA_BOMB:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = mereDenisBombCommand;
            break;
        case TYPE_SMA_GRAND_LASER:
        case TYPE_SMA_PETIT_LASER:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = mereDenisBigLaserCommand;
            break;
        case TYPE_JOE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_JOE_COMMAND;
            break;
        case TYPE_BOUEE_JOE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BOUEE_JOE_COMMAND;
            break;
        case TYPE_BATEAU:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = doShipCommand;
            break;
        case TYPE_HYB_BBF2_D:
        case TYPE_HYB_BBF2_G:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = doBBF2command;
            break;
        case TYPE_HYB_BBF2_LAS:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_HYB_BBF2_LAS;
            break;
        case TYPE_CORDE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_CORDE_COMMAND;
            break;
        case TYPE_CFUMEE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_CFUMEE_COMMAND;
            break;
        case TYPE_PIERREACORDE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_PAC_COMMAND;
            break;
        case TYPE_HYBRIDE_STOSKO:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = doSTOSKOcommand;
            break;
        case TYPE_HYBRIDE_MOSAMS:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = doMOSAMScommand;
            break;
        case TYPE_BLACK_RAY:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = doBlackRaymanCommand;
            break;
        case TYPE_HERSE_BAS:
        case TYPE_HERSE_BAS_NEXT:
        case TYPE_HERSE_HAUT:
        case TYPE_HERSE_HAUT_NEXT:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = doHerseCommand;
            break;
        case TYPE_STONEWOMAN:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_STONEWOMAN_COMMAND;
            break;
        case TYPE_STONEWOMAN2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_NOMOVE_STONEWOMAN_COMMAND;
            break;
        case TYPE_MOSKITO:
        case TYPE_MOSKITO2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = doMoskitoCommand;
            break;
        case TYPE_BLACKTOON1:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BLKTOON_COMMAND;
            break;
        case TYPE_MOVE_PLAT:
        case TYPE_MOVE_AUTOJUMP_PLAT:
        case TYPE_MOVE_OUYE:
        case TYPE_MOVE_START_PLAT:
        case TYPE_MOVE_START_NUA:
        case TYPE_MOVE_MARTEAU:
        case TYPE_MOVE_RUBIS:
        case TYPE_PAILLETTE:
        case TYPE_DESTROYING_DOOR:
        case TYPE_PT_GRAPPIN:
        case TYPE_ROULETTE:
        case TYPE_ROULETTE2:
        case TYPE_ROULETTE3:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_MOVING_PLATFORM_COMMAND;
            break;
        case TYPE_UFO_IDC:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_MOVING_WITH_INDICATOR_COMMAND;
            break;
        case TYPE_MARACAS:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_MOVE_MARACAS_COMMAND;
            break;
        case TYPE_LIDOLPINK:
        case TYPE_LIDOLPINK2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_ONE_PINK_CMD;
            break;
        case TYPE_WIZARD1:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = TEST_WIZARD;
            break;
        case TYPE_SPACE_MAMA:
        case TYPE_SPACE_MAMA2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = doMereDenisCommand;
            break;
        case TYPE_STONEMAN1:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_STONEMAN1_TIR;
            break;
        case TYPE_STONEMAN2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_STONEMAN2_TIR;
            break;
        case TYPE_STONEDOG:
        case TYPE_STONEDOG2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_STONEDOG_COMMAND;
            break;
        case TYPE_STONEBOMB:
        case TYPE_STONEBOMB2:
        case TYPE_STONEBOMB3:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_STONEBOMB_COMMAND;
            break;
        case TYPE_REDUCTEUR:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_REDUCTEUR;
            break;
        case TYPE_EAU:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_EAU_QUI_MONTE;
            break;
        case TYPE_SPIDER:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_SPIDER_TIR;
            break;
        case TYPE_FLASH:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_FLASH_COMMAND;
            break;
        case TYPE_TOTEM:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_TOTEM_COMMAND;
            break;
        case TYPE_BB1:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BBMONT_COMMAND;
            break;
        case TYPE_BB12:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BBMONT2_COMMAND;
            break;
        case TYPE_BB13:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BBMONT3_COMMAND;
            break;
        case TYPE_BB14:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BBMONT4_COMMAND;
            break;
        case TYPE_SAXO:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_SAXO_COMMAND;
            break;
        case TYPE_SAXO2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_SAXO2_COMMAND;
            break;
        case TYPE_SAXO3:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_SAXO3_COMMAND;
            break;
        case TYPE_BBL:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BBL_COMMAND;
            break;
        case TYPE_BAG1:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BAG1_COMMAND;
            break;
        case TYPE_CAGE2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_CAGE2;
            break;
        case TYPE_ECLAIR:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_ECLAIR_COMMAND;
            break;
        case TYPE_BB1_PLAT:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BB1_PLAT_CMD;
            break;
        case TYPE_CAGE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_CAGE;
            break;
        case TYPE_PIRATE_NGAWE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_ONE_NGW_COMMAND;
            break;
        case TYPE_PIRATE_GUETTEUR:
        case TYPE_PIRATE_GUETTEUR2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_ONE_PAR_COMMAND;
            break;
        case TYPE_RING:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_ONE_NGW_RING_COMMAND;
            break;
        case TYPE_STONECHIP:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_ONE_STONECHIP_COMMAND;
            break;
        case TYPE_TROMPETTE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_TRP_COMMAND;
            break;
        case TYPE_CYMBALE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_CYMBAL_COMMAND;
            break;
        case TYPE_GENEBADGUY:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_TEN_COMMAND;
            break;
        case TYPE_MITE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_MIT_COMMAND;
            break;
        case TYPE_MITE2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_MITE2_COMMAND;
            break;
        case TYPE_NOTE:
        case TYPE_NOTE2:
        case TYPE_BONNE_NOTE:
        case TYPE_NOTE3:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_NOTE_CMD;
            break;
        case TYPE_POI2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_POISSON_VERT_CMD;
            break;
        case TYPE_POI3:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_POISSON_BLEU_CMD;
            break;
        case TYPE_ROLLING_EYES:
        case TYPE_KILLING_EYES:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_ROLL_EYES;
            break;
        case TYPE_CLOWN_TNT:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_CLOWN_TNT_COMMAND;
            break;
        case TYPE_CLOWN_TNT2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_CLOWN_TNT2_COMMAND;
            break;
        case TYPE_CLOWN_TNT3:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_CLOWN_TNT3_COMMAND;
            break;
        case TYPE_PIRATE_BOMB:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_PAR_BOMB_COMMAND;
            break;
        case TYPE_MST_SCROLL:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_MST_SCROLL_COMMAND;
            break;
        case TYPE_CAISSE_CLAIRE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_CCL_COMMAND;
            break;
        case TYPE_WALK_NOTE_1:
        case TYPE_WALK_NOTE_2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_WLKNOT_COMMAND;
            break;
        case TYPE_FEE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_FEE;
            break;
        case TYPE_SCORPION:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_SKO;
            break;
        case TYPE_CYMBAL1:
        case TYPE_CYMBAL2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_2_PARTS_CYMBAL;
            break;
        case TYPE_BADGUY3:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_PTI_ESQUIVE;
            break;
        case TYPE_FISH:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_PYRANHA;
            break;
        case TYPE_TARZAN:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_TARZAN;
            break;
        case TYPE_PHOTOGRAPHE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = FUN_80172704;
            break;
        case TYPE_BATTEUR_FOU:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_BAT_COMMAND;
            break;
        case TYPE_PIRATE_POELLE:
        case TYPE_PIRATE_POELLE_D:
        case TYPE_PIRATE_P_45:
        case TYPE_PIRATE_P_D_45:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_PIRATE_POELLE;
            break;
        case TYPE_MAMA_PIRATE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_PMA_COMMAND;
            break;
        case TYPE_COUTEAU:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_COU_COMMAND;
            break;
        case TYPE_MEDAILLON_TOON:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_MEDAILLON_TOON;
            break;
        case TYPE_SPIDER_PLAFOND:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_SPIDER_PLAFOND;
            break;
        case TYPE_DARD_PLAFOND:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_DARD_PLAFOND_ALWAYS;
            break;
        case TYPE_INDICATOR:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_IDC_COMMAND;
            break;
        case TYPE_PIEDS_RAYMAN:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_PIEDS_RAYMAN;
            break;
        case TYPE_POELLE:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_POELLE_COMMAND;
            break;
        case TYPE_DARK:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_DARK_COMMAND;
            break;
        case TYPE_DARK_SORT:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_DARK_SORT_COMMAND;
            break;
        case TYPE_NOVA2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_NOVA2_COMMAND;
            break;
        case TYPE_ENS:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_ENSEIGNE_COMMAND;
            break;
        case TYPE_VITRAIL:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_VITRAIL_COMMAND;
            break;
        case TYPE_DARK_PHASE2:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_DARK_PHASE2_COMMAND;
            break;
        case TYPE_DARK2_SORT:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_DARK2_SORT_COMMAND;
            break;
        case TYPE_DARK2_PINK_FLY:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_DARK2_TOONS_COMMAND;
            break;
        case TYPE_FIRE_LEFT:
        case TYPE_FIRE_RIGHT:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DoFlammeCommand;
            break;
        default:
            obj_fonction = &ObjectsFonctions[obj_type];
            sel_fonction = DO_ONE_CMD;
            break;
        }
        obj_fonction->do_obj = sel_fonction;
    }
}

/* 2FF64 80154764 -O2 -msoft-float */
void build_active_table(void)
{
    Obj *last_obj;
    s32 x_left; s32 x_right;
    s32 y_top; s32 y_bottom;
    Obj *cur_obj;
    s16 *cur_actobj;
    s16 *prev_addr;

    actobj.num_active_objects = 0;
    actobj.objects[0] = -1;
    last_obj = &level.objects[level.nb_objects - 1];
    x_left = xmap - 500;
    x_right = xmap + 820;
    y_top = ymap - 500;
    y_bottom = ymap + 740;
    for (cur_obj = level.objects; cur_obj <= last_obj; cur_obj++)
        cur_obj->flags &= ~FLG(OBJ_FLAG_5);

    for (cur_obj = level.objects; cur_obj <= last_obj; cur_obj++)
    {
        if (!(cur_obj->flags & FLG(OBJ_FLAG_5)))
        {
            if (
                (flags[cur_obj->type].flags0 >> OBJ0_KEEP_ACTIVE & 1) ||
                (
                    cur_obj->x_pos > x_left && cur_obj->x_pos < x_right &&
                    cur_obj->y_pos > y_top && cur_obj->y_pos < y_bottom
                )
            )
                SET_ACTIVE_FLAG(cur_obj->x_pos - xmap, cur_obj->y_pos - ymap, cur_obj);
            else
                cur_obj->flags &= ~FLG(OBJ_ACTIVE);
        }
    }

    cur_actobj = &actobj.objects[actobj.num_active_objects];
    prev_addr = cur_actobj;
    for (cur_obj = level.objects; cur_obj <= last_obj; cur_obj++)
    {
        if (cur_obj->flags & FLG(OBJ_ACTIVE))
        {
            cur_obj->screen_x_pos = cur_obj->x_pos - xmap;
            cur_obj->screen_y_pos = cur_obj->y_pos - ymap;
            *cur_actobj = cur_obj->id;
            cur_actobj++;
        }
    }
    *cur_actobj = -1;

    actobj.num_active_objects += cur_actobj - prev_addr;
}

/* 301D4 801549D4 -O2 -msoft-float */
void Add_One_RAY_lives(void)
{
    status_bar.num_lives++;
    MIN_2(status_bar.num_lives, 99);

    if (status_bar.max_hp == 4)
        ray.hit_points = 4;
    else
        ray.hit_points = 2;
}

/* 3022C 80154A2C -O2 -msoft-float */
void DO_CLING_ANIMS(void)
{
    Obj *obj;

    if (id_Cling_1up != -1)
    {
        obj = &level.objects[id_Cling_1up];
        if (obj->timer != 0)
        {
            obj->anim_frame = 0;
            obj->timer--;
        }

        if (EOA(obj))
        {
            id_Cling_1up = -1;
            if (!(ray_mode == MODE_MORT_DE_RAYMAN || ray_mode == MODE_MORT_DE_RAYMAN_ON_MS))
                Add_One_RAY_lives();
            obj->flags &= ~FLG(OBJ_ALIVE);
        }
    }

    if (id_Cling_Pow != -1)
    {
        obj = &level.objects[id_Cling_Pow];
        if (obj->timer != 0)
        {
            obj->anim_frame = 0;
            obj->timer--;
        }

        if (EOA(obj))
        {
            id_Cling_Pow = -1;
            if (!(ray_mode == MODE_MORT_DE_RAYMAN || ray_mode == MODE_MORT_DE_RAYMAN_ON_MS))
            {
                ray.hit_points = 4;
                status_bar.max_hp = 4;
            }
            obj->flags &= ~FLG(OBJ_ALIVE);
        }
    }
}

/* 304D4 80154CD4 -O2 -msoft-float */
void DO_OBJECTS_ANIMS(void)
{
    s16 i = 0;
    Obj *cur_obj = &level.objects[actobj.objects[i]];

    while (i < actobj.num_active_objects)
    {
        if (!(cur_obj->type == TYPE_BLACK_RAY || cur_obj->type == TYPE_BLACK_FIST))
            DO_ANIM(cur_obj);
        i++;
        cur_obj = &level.objects[actobj.objects[i]];
    }
}

/* 30594 80154D94 -O2 -msoft-float */
void DO_OBJECTS(void)
{
    s16 i;
    Obj *cur_obj;

    if (!(id_Cling_1up == -1 && id_Cling_Pow == -1))
        DO_CLING_ANIMS();
    if (lidol_to_allocate != 0)
    {
        allocate_toons(lidol_source_obj, 7);
        lidol_to_allocate = 0;
    }

    i = 0;
    cur_obj = &level.objects[actobj.objects[i]];
    while (i < actobj.num_active_objects)
    {
        ot = cur_obj->type;
        setvol(actobj.objects[i], FUN_801473dc(cur_obj));
        setpan(actobj.objects[i], FUN_801473d4(cur_obj));
        i++;
        cur_obj = &level.objects[actobj.objects[i]];
    }

    i = 0;
    cur_obj = &level.objects[actobj.objects[i]];
    while (i < actobj.num_active_objects)
    {
        ot = cur_obj->type;
        if (
            flags[ot].flags3 >> OBJ3_SWITCH_OFF & 1 ||
            (ot == TYPE_WIZ && cur_obj->sub_etat == 23) ||
            (ot == TYPE_EXPLOSION && cur_obj->sub_etat == 1) ||
            (ot == TYPE_DARK2_SORT && cur_obj->sub_etat != 35)
        )
            switchOff(cur_obj);
        if (ot != TYPE_WIZ)
        {
            DO_ONE_OBJECT(cur_obj);
            if (
                !(flags[ot].flags0 >> OBJ0_BOSS & 1) &&
                cur_obj->hit_points == 0 &&
                cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].flags & 8
            )
                cur_obj->hit_points++;
        }
        i++;
        cur_obj = &level.objects[actobj.objects[i]];
    }
}

/* 3088C 8015508C -O2 -msoft-float */
void MOVE_OBJECTS(void)
{
    s16 i = 0;
    Obj *cur_obj = &level.objects[actobj.objects[i]];

    while (i < actobj.num_active_objects)
    {
        MOVE_OBJECT(cur_obj);
        i++;
        cur_obj = &level.objects[actobj.objects[i]];
    }
}

/* 30930 80155130 -O2 -msoft-float */
void RECALE_ALL_OBJECTS(void)
{
    s16 x; s16 y; s16 w; s16 h;
    s16 i = 0;
    Obj *cur_obj = &level.objects[actobj.objects[0]];

    while (i < actobj.num_active_objects)
    {
        calc_obj_pos_map(cur_obj);
        i++;
        cur_obj = &level.objects[actobj.objects[i]];
    }

    if (ray.field20_0x36 != -1)
    {
        cur_obj = &level.objects[ray.field20_0x36];
        if (cur_obj->flags & FLG(OBJ_ACTIVE))
        {
            GET_SPRITE_POS(cur_obj, cur_obj->follow_sprite, &x, &y, &w, &h);
            ray.y_pos = y + cur_obj->offset_hy - ray.offset_by;
            calc_obj_pos_map(&ray);
        }
    }
}
