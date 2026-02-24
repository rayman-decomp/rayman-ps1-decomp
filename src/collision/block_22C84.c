#include "collision/block_22C84.h"

#ifdef BSS_DEFS
MapData mp;

u8 ray_last_ground_btyp;
u16 PS1_RandSum;
s16 RandomIndex;
#endif

/* 22C84 80147484 -O2 -msoft-float */
s16 get_center_x(Obj *obj)
{
    s16 res;

    switch (obj->type)
    {
    case TYPE_MOVE_MARTEAU:
        res = 70;
        break;
    case TYPE_MOVE_PLAT:
        switch (num_world)
        {
        case 1:
            res = 40;
            break;
        case 2:
            res = 64;
            break;
        default:
            res = 40;
            break;
        }
        break;
    case TYPE_MOVE_OUYE:
        /* TODO: ... why does this work? */
        switch (num_world)
        {
        case 1:
            res = 40;
            break;
        case 2:
            res = 64;
            break;
        default:
            res = 40;
            break;
        }
        res = 18;
        break;
    case TYPE_MOVE_RUBIS:
        res = 18;
        break;
    case TYPE_MOVE_START_PLAT:
        res = 128;
        break;
    case TYPE_BLACKTOON1:
        switch (obj->follow_sprite)
        {
        case 5:
        case 6:
        case 7:
            res = 80;
            break;
        default:
            res = 40;
            break;
        }
        break;
    case TYPE_PIRATE_P_45:
    case TYPE_PIRATE_P_D_45:
    case TYPE_PIRATE_POELLE:
    case TYPE_PIRATE_POELLE_D:
        res = 80;
        break;
    case TYPE_ROULETTE:
    case TYPE_ROULETTE2:
    case TYPE_ROULETTE3:
        res = 104;
        break;
    case TYPE_PT_GRAPPIN:
        res = 36;
        break;
    default:
        res = 40;
        break;
    }

    return res;
}

/* 22DEC 801475EC -O2 -msoft-float */
s16 get_center_y(Obj *obj)
{
    s16 res;

    switch (obj->type)
    {
    case TYPE_SPIDER_PLAFOND:
        res = 90;
        break;
    case TYPE_MOVE_MARTEAU:
        res = 40;
        break;
    case TYPE_MOVE_PLAT:
        /* TODO: ... why does this work? */
        switch (num_world)
        {
        case 1:
            res = 40;
            break;
        case 2:
            res = 40;
            break;
        default:
            res = 40;
            break;
        }
        break;
    case TYPE_MOVE_OUYE:
        /* TODO: ... why does this work? */
        switch (num_world)
        {
        case 1:
            res = 40;
            break;
        case 2:
            res = 64;
            break;
        default:
            res = 40;
            break;
        }
        res = 18;
        break;
    case TYPE_MOVE_RUBIS:
        res = 18;
        break;
    case TYPE_MOVE_START_PLAT:
        res = 64;
        break;
    case TYPE_BLACKTOON1:
        switch (obj->follow_sprite)
        {
        case 6:
        case 7:
            if (obj->speed_y > 0)
                res = 64;
            else
                res = 78;
            break;
        case 5:
            res = 72;
            break;
        default:
            /* TODO: ??? */
            break;
        }
        break;
    case TYPE_PIRATE_P_45:
    case TYPE_PIRATE_P_D_45:
    case TYPE_PIRATE_POELLE:
    case TYPE_PIRATE_POELLE_D:
        res = 96;
        break;
    case TYPE_ROULETTE:
    case TYPE_ROULETTE2:
    case TYPE_ROULETTE3:
        res = 104;
        break;
    case TYPE_PT_GRAPPIN:
        res = 32;
        break;
    default:
        res = 40;
        break;
    }

    return res;
}

/* 22F80 80147780 -O2 -msoft-float */
s16 on_block_chdir(Obj *obj, s16 offs_bx, s16 offs_by)
{
    return block_flags[BTYP(obj->x_pos + offs_bx, obj->y_pos + offs_by)] >> BLOCK_CH_DIR & 1;
}

/* 22FE0 801477E0 -O2 -msoft-float */
void CALC_FOLLOW_SPRITE_SPEED(Obj *obj, Animation *anim_1, Animation *anim_2, s16 anim_frame_2)
{
    u8 width_1;
    s32 unk_1;
    s32 x_1;
    s32 x_2;
    s32 unk_2;
    u8 foll_spr = obj->follow_sprite;
    AnimationLayer *layer_1 = &anim_1->layers[(anim_1->layers_count & 0x3FFF) * obj->anim_frame];
    AnimationLayer *layer_2 = &anim_2->layers[(anim_2->layers_count & 0x3FFF) * anim_frame_2];

    width_1 = obj->sprites[layer_1[foll_spr].sprite].width;
    if (obj->flags & FLG(OBJ_FLIP_X))
    {
        unk_1 = (u16) obj->x_pos + (obj->offset_bx * 2) - width_1;
        x_2 = unk_1 - layer_2[foll_spr].x_pos;
        x_1 = unk_1 - layer_1[foll_spr].x_pos;
    }
    else
    {
        unk_2 = (u16) obj->x_pos;
        x_1 = unk_2 + layer_1[foll_spr].x_pos;
        x_2 = unk_2 + layer_2[foll_spr].x_pos;
    }
    obj->follow_y = (layer_1[foll_spr].y_pos + obj->y_pos) - (layer_2[foll_spr].y_pos + obj->y_pos);
    obj->follow_x = x_1 - x_2;
}

/* 230E0 801478E0 -O2 -msoft-float */
s16 GET_SPRITE_POS(Obj *obj, s16 index, s16 *x, s16 *y, s16 *w, s16 *h)
{
    Animation *anim;
    AnimationLayer *layer;
    u8 sprite_ind;
    Sprite *sprite;
    s16 res;

    anim = &obj->animations[obj->anim_index];
    layer = &anim->layers[(anim->layers_count & 0x3FFF) * obj->anim_frame];
    layer += index;
    sprite_ind = layer->sprite;
    sprite = &obj->sprites[sprite_ind];
    if (sprite_ind != 0 && sprite->id != 0)
    {
        *w = sprite->sprite_width;
        *h = sprite->sprite_height;
        if (obj->flags & FLG(OBJ_FLIP_X))
            *x =
                obj->x_pos +
                (
                    obj->offset_bx * 2 -
                    (layer->x_pos + (sprite->sprite_pos & 0xF)) -
                    sprite->width
                );
        else
        {
            *x =
                obj->x_pos +
                layer->x_pos + (sprite->sprite_pos & 0xF);
        }
        *y = layer->y_pos + (sprite->sprite_pos >> 4) + obj->y_pos;
        res = true;
    }
    else
        res = false;
    return res;
}

/* 23204 80147A04 -O2 -msoft-float */
void GET_RAY_ZDC(Obj *ray, s16 *x, s16 *y, s16 *w, s16 *h)
{
    u8 main_etat = ray->main_etat;
    s32 frame;

    if (ray->eta[main_etat][ray->sub_etat].flags & 0x40)
    {
        *x = ray->x_pos + 72;
        *y = ray->y_pos + 64;
        *w = 16;
        *h = 14;
    }
    else if (main_etat == 5)
    {
        *x = ray->x_pos + 72;
        *y = ray->y_pos + 40;
        *w = 16;
        *h = 46;
    }
    else if (main_etat == 7)
    {
        frame = ray->anim_frame;
        if (frame > 32)
            frame -= 32;
        frame -= 10;
        if ((s16) frame < 13U)
        {
            *x = ray->x_pos + 64;
            *y = ray->y_pos + 54;
            *w = 36;
            *h = 20;
        }
        else
        {
            *x = ray->x_pos + 70;
            *y = ray->y_pos + 40;
            *w = 20;
            *h = 40;
        }
    }
    else
    {
        *x = ray->x_pos + 72;
        *y = ray->y_pos + 24;
        *w = 16;
        *h = 54;
    }
    if (ray->scale != 0)
    {
        set_proj_center(ray->x_pos + ray->offset_bx, ray->y_pos + ray->offset_by);
        *x = get_proj_x(ray->scale, *x);
        *y = get_proj_y(ray->scale, *y);
        *w = get_proj_dist2(ray->scale, *w);
        *h = get_proj_dist2(ray->scale, *h);
        set_proj_center(ray->screen_x_pos + ray->offset_bx, ray->screen_y_pos + ray->offset_by);
    }
}

/* 2344C 80147C4C -O2 -msoft-float */
void GET_BB1_ZDCs(Obj *obj, s16 *x_1, s16 *y_1, s16 *w_1, s16 *h_1, s16 *x_2, s16 *y_2, s16 *w_2, s16 *h_2)
{
    s16 spr_ind = 6;
    s16 h_loc;

    GET_ANIM_POS(obj, x_1, y_1, w_1, &h_loc);
    if (obj->main_etat == 2 && (obj->sub_etat == 0 || obj->sub_etat == 4))
        spr_ind = 3;
    GET_SPRITE_POS(obj, spr_ind, x_1, y_1, w_1, h_1);
    *x_2 = *x_1 - 7;
    *y_2 = *y_1 + *h_1;
    *w_2 = *w_1 + 14;
    *h_2 = h_loc >> 1;
    *x_1 += 4;
    *w_1 -= 8;
    *y_1 += 4;
    *h_1 -= 8;
    if (obj->main_etat == 0 && (obj->sub_etat == 16 || obj->sub_etat == 19))
        GET_SPRITE_POS(obj, 0, x_1, y_1, w_1, h_1);
}

/* 235E8 80147DE8 -O2 -msoft-float */
s32 myRand(s16 max_incl)
{
    s16 max_loc = max_incl + 1;

    PS1_RandSum += RandArray[RandomIndex & (LEN(RandArray) - 1)];
    RandomIndex++;
    return (s16) (PS1_RandSum % max_loc);
}

/* 23674 80147E74 -O2 -msoft-float */
void calc_obj_dir(Obj *obj)
{
    if (ray.x_pos + ray.offset_bx - obj->x_pos - obj->offset_bx > 0)
        obj->flags |= FLG(OBJ_FLIP_X);
    else
        obj->flags &= ~FLG(OBJ_FLIP_X);
}

/* 236C4 80147EC4 -O2 -msoft-float */
s16 OBJ_IN_ZONE(Obj *obj)
{
    switch (obj->type)
    {
    case TYPE_BADGUY2:
    case TYPE_BADGUY3:
    case TYPE_LIDOLPINK:
    case TYPE_LIDOLPINK2:
        return obj->detect_zone_flag == 1;
    default:
        return obj->detect_zone_flag != 0;
    }
}

/* 23730 80147F30 -O2 -msoft-float */
void calc_obj_pos_map(Obj *obj)
{
    obj->screen_y_pos = obj->y_pos - ymap;
    obj->screen_x_pos = obj->x_pos - xmap;
}

/* 2375C 80147F5C -O2 -msoft-float */
void makeUturn(Obj *obj)
{
    u8 label = 0xFF;
    u8 foll_spr;
    Obj *unk_1;

    switch (obj->type)
    {
    case TYPE_BLACKTOON1:
        foll_spr = obj->follow_sprite;
        if (foll_spr == 1 || foll_spr == 2 || obj->follow_sprite == 4 || obj->follow_sprite == 7)
        {
            if (obj->cmd == GO_LEFT)
            {
                label = 3;
                obj->flags |= FLG(OBJ_FLIP_X);
            }
            else if (obj->cmd == GO_RIGHT)
            {
                label = 2;
                obj->flags &= ~FLG(OBJ_FLIP_X);
            }
        }
        break;
    case TYPE_MITE:
        if (!(obj->main_etat == 0 && obj->sub_etat == 3))
        {
            label = 3;
            obj->field20_0x36 = 0;
        }
        break;
    case TYPE_BADGUY1:
        if (
            !(obj->main_etat == 0 &&
            (obj->sub_etat == 3 || obj->sub_etat == 1 || obj->sub_etat == 4 ||
            obj->sub_etat == 5 || obj->sub_etat == 6))
        )
        {
            if (obj->cmd == GO_LEFT)
            {
                label = 1;
                obj->flags |= FLG(OBJ_FLIP_X);
            }
            else if (obj->cmd == GO_RIGHT)
            {
                label = 0;
                obj->flags &= ~FLG(OBJ_FLIP_X);
            }
        }
        break;
    case TYPE_BADGUY2:
    case TYPE_BADGUY3:
        if (!(obj->main_etat == 0 && (obj->sub_etat == 3 || obj->sub_etat == 1)))
        {
            if (obj->flags & FLG(OBJ_READ_CMDS))
            {
                if (obj->cmd == GO_LEFT)
                {
                    label = 1;
                    obj->flags |= FLG(OBJ_FLIP_X);
                }
                else if (obj->cmd == GO_RIGHT)
                {
                    label = 0;
                    obj->flags &= ~FLG(OBJ_FLIP_X);
                }
            }
            else
            {
                if (obj->cmd == GO_LEFT)
                {
                    label = 6;
                    obj->flags |= FLG(OBJ_FLIP_X);
                }
                else if (obj->cmd == GO_RIGHT)
                {
                    label = 5;
                    obj->flags &= ~FLG(OBJ_FLIP_X);
                }
            }
        }
        break;
    case TYPE_GENEBADGUY:
        if (!(obj->main_etat == 0 && obj->sub_etat == 3))
        {
            if (obj->cmd == GO_LEFT)
            {
                label = 1;
                obj->flags |= FLG(OBJ_FLIP_X);
            }
            else if (obj->cmd == GO_RIGHT)
            {
                label = 0;
                obj->flags &= ~FLG(OBJ_FLIP_X);
            }
        }
        break;
    case TYPE_STONEMAN1:
    case TYPE_STONEMAN2:
        if (obj->cmd == GO_LEFT)
        {
            label = 5;
            obj->flags |= FLG(OBJ_FLIP_X);
        }
        else if (obj->cmd == GO_RIGHT)
        {
            label = 4;
            obj->flags &= ~FLG(OBJ_FLIP_X);
        }
        break;
    case TYPE_TROMPETTE:
        if (!(obj->main_etat == 0 && obj->sub_etat == 1))
        {
            if (obj->flags & FLG(OBJ_READ_CMDS))
            {
                if (obj->cmd == GO_LEFT)
                {
                    label = 1;
                    obj->flags |= FLG(OBJ_FLIP_X);
                }
                else if (obj->cmd == GO_RIGHT)
                {
                    label = 0;
                    obj->flags &= ~FLG(OBJ_FLIP_X);
                }
            }
        }
        break;
    case TYPE_BIG_CLOWN:
    case TYPE_WAT_CLOWN:
        if (obj->flags & FLG(OBJ_READ_CMDS))
        {
            if (obj->cmd == GO_LEFT)
            {
                label = 1;
                obj->flags |= FLG(OBJ_FLIP_X);
            }
            else if (obj->cmd == GO_RIGHT)
            {
                label = 0;
                obj->flags &= ~FLG(OBJ_FLIP_X);
            }
        }
        break;
    case TYPE_SPIDER:
        if (obj->cmd == GO_LEFT)
        {
            label = 2;
            obj->flags |= FLG(OBJ_FLIP_X);
        }
        else
        {
            label = 0;
            obj->flags &= ~FLG(OBJ_FLIP_X);
        }
        break;
    case TYPE_MITE2:
        if (!(obj->flags & FLG(OBJ_FLIP_X)))
            obj->flags |= FLG(OBJ_FLIP_X);
        else
            obj->flags &= ~FLG(OBJ_FLIP_X);

        if (!(obj->main_etat == 0 && obj->sub_etat == 3))
        {
            label = 3;
            obj->field20_0x36 = 0;
        }
        break;
    case TYPE_CAISSE_CLAIRE:
        if (!(obj->main_etat == 0 && obj->sub_etat == 2))
        {
            set_main_and_sub_etat(obj, 1, 1);
            if (!(obj->flags & FLG(OBJ_FLIP_X)))
            {
                obj->flags |= FLG(OBJ_FLIP_X);
                label = 3;
            }
            else
            {
                obj->flags &= ~FLG(OBJ_FLIP_X);
                label = 2;
            }
        }
        break;
    case TYPE_WALK_NOTE_1:
        if (obj->cmd == GO_LEFT)
        {
            label = 2;
            obj->flags |= FLG(OBJ_FLIP_X);
        }
        else if (obj->cmd == GO_RIGHT)
        {
            label = 1;
            obj->flags &= ~FLG(OBJ_FLIP_X);
        }
        break;
    case TYPE_SPIDER_PLAFOND:
        /* TODO: clean up somehow? */
        unk_1 = obj;
        if (!(obj->main_etat == 0 && (obj->sub_etat == 24 || unk_1->sub_etat == 18 || obj->sub_etat == 19)))
        {
            set_main_and_sub_etat(obj, 0, 24);
            obj->speed_y = 0;
            obj->speed_x = 0;
            obj->flags = obj->flags & ~FLG(OBJ_FLIP_X) | ((1 - (obj->flags >> OBJ_FLIP_X & 1) & 1) << OBJ_FLIP_X);
        }
        break;
    }

    if (label != 0xFF)
    {
        obj->x_pos -= obj->speed_x;
        obj->speed_x = 0;
        skipToLabel(obj, label, true);
    }
}

/* 23CAC 801484AC -O2 -msoft-float */
u16 PS1_GetBTYPFromTilePos(s16 x, s16 y)
{
    if (x >= 0 && (x <= mp.width - 1) && y >= 0 && (y <= mp.height - 1))
        return mp.map[x + y * mp.width] >> 10;
    return BTYP_NONE;
}

/* 23D38 80148538 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/collision/block_22C84", calc_btyp_square);
#else
/*
remove x_2???
attempts: 2?
not sure there is a good solution
*/
void calc_btyp_square(Obj *obj)
{
    u8 x_offs;
    s16 x_1;
    s32 y_1;
    s16 x_3;
    s16 y_2;
    s16 x_4;
    s16 x_5;
    s32 x_2;

    if (obj->type == TYPE_RAYMAN)
    {
        if (RayEvts.demi)
            x_offs = 4;
        else
            x_offs = 8;
    }
    else
        x_offs = 16;

    x_1 = (s16) (obj->x_pos + obj->offset_bx);
    y_1 = (s16) (obj->y_pos + obj->offset_by);
    y_2 = ashr16(y_1, 4);
    x_2 = x_1;
    x_3 = ashr16(x_2, 4);
    x_4 = ashr16(x_2 - x_offs, 4);
    x_5 = ashr16(x_2 + x_offs, 4);
    obj->btypes[3] = PS1_GetBTYPFromTilePos(x_3, y_2 + -1);
    obj->btypes[1] = PS1_GetBTYPFromTilePos(x_4, y_2);
    if (obj->main_etat == 2)
    {
        /* fixed point math */
        obj->btypes[0] = bloc_floor(
            (u8) PS1_GetBTYPFromTilePos(x_3, y_2),
            (s16) (x_2 - (x_2 / 16 * 16)),
            (s16) (y_1 - (y_1 / 16 * 16))
        );
    }
    else
    {
        obj->btypes[0] = PS1_GetBTYPFromTilePos(x_3, y_2);
    }
    obj->btypes[2] = PS1_GetBTYPFromTilePos(x_5, y_2);
    obj->btypes[4] = PS1_GetBTYPFromTilePos(x_3, y_2 + 1);
}
#endif

/* 23F10 80148710 -O2 -msoft-float */
void DO_OBJ_REBOND_EN_X(Obj *obj)
{
    if (
        block_flags[obj->btypes[2]] >> BLOCK_FLAG_4 & 1 ||
        block_flags[obj->btypes[1]] >> BLOCK_FLAG_4 & 1
    )
        obj->speed_x = -obj->speed_x;
}

/* 23F80 80148780 -O2 -msoft-float */
u32 calc_btyp(Obj *obj)
{
    u8 btyp;
    u8 btypes_1_2_solid;
    s32 ray_x; s32 ray_y;
    BlockType *ray_btypes;
    BlockType *new_btyp;
    u8 foll_spr;

    calc_btyp_square(obj);

    if (obj->type == TYPE_RAYMAN)
    {
        ray.field23_0x3c = -1;
        switch (ray.btypes[0])
        {
        case BTYP_NONE:
        case BTYP_CHDIR:
            break;
        case BTYP_SOLID_RIGHT_45:
        case BTYP_SOLID_LEFT_45:
        case BTYP_SOLID_RIGHT1_30:
        case BTYP_SOLID_RIGHT2_30:
        case BTYP_SOLID_LEFT1_30:
        case BTYP_SOLID_LEFT2_30:
        case BTYP_LIANE:
        case BTYP_SOLID_PASSTHROUGH:
        case BTYP_SOLID:
            ray_last_ground_btyp = true;
            break;
        case BTYP_SLIPPERY_RIGHT_45:
        case BTYP_SLIPPERY_LEFT_45:
        case BTYP_SLIPPERY_RIGHT1_30:
        case BTYP_SLIPPERY_RIGHT2_30:
        case BTYP_SLIPPERY_LEFT1_30:
        case BTYP_SLIPPERY_LEFT2_30:
        case BTYP_SLIPPERY:
            ray_last_ground_btyp = false;
            break;
        }
    }

    if (!(block_flags[obj->btypes[0]] >> BLOCK_SOLID & 1))
    {
        if (obj->type == TYPE_RAYMAN)
            btyp = mp.map[ray.ray_dist] >> 10;
        else
            btyp = BTYP(obj->x_pos + obj->offset_bx, obj->y_pos + obj->offset_by);

        if (obj->main_etat == 2 && !(block_flags[btyp] >> BLOCK_SOLID & 1))
            btyp = BTYP(obj->x_pos + obj->offset_bx, obj->y_pos + obj->offset_by + 16);

        if (!(block_flags[btyp] >> BLOCK_SOLID & 1))
        {
            btypes_1_2_solid = (block_flags[obj->btypes[1]] >> BLOCK_SOLID & 1) | (block_flags[obj->btypes[2]] & (1 << BLOCK_SOLID));
            if (btypes_1_2_solid == 3) /* both 1 and 2 have solid flag */
            {
                if (((obj->offset_bx + (u16) obj->x_pos) & 0xF) < 8)
                    btypes_1_2_solid = 1;
                else
                    btypes_1_2_solid = 2;
            }

            if (btypes_1_2_solid != 0)
            {
                btypes_1_2_solid--;
                if (obj->type == TYPE_RAYMAN)
                {
                    if (ray_last_ground_btyp == true)
                    {
                        ray_x = ray.x_pos + ray.offset_bx;
                        if (btypes_1_2_solid)
                            ray_x += 16;
                        else
                            ray_x -= 16;
                        ray_y = ray.y_pos + ray.offset_by - 16;
                        if (!(block_flags[(u8) BTYP(ray_x, ray_y)] >> BLOCK_SOLID & 1))
                        {
                            if (ray.main_etat != 2)
                            {
                                /* ??? don't understand */
                                if (btypes_1_2_solid != (ray.flags >> OBJ_FLIP_X & 1))
                                    obj->field23_0x3c = 0;
                                else
                                    obj->field23_0x3c = 1;
                            }

                            ray_btypes = ray.btypes;
                            if (btypes_1_2_solid)
                                new_btyp = &ray_btypes[2];
                            else
                                new_btyp = &ray_btypes[1];
                            ray_btypes[0] = *new_btyp;
                        }
                    }
                }
                else
                {
                    if (
                        (obj->flags >> OBJ_FLIP_X & 1) != btypes_1_2_solid &&
                        obj->main_etat != 2 &&
                        (
                            (obj->type == TYPE_BADGUY1 && obj->flags & FLG(OBJ_READ_CMDS)) ||
                            obj->type == TYPE_BADGUY2 || obj->type == TYPE_BADGUY3 || obj->type == TYPE_GENEBADGUY ||
                            obj->type == TYPE_STONEMAN1 || obj->type == TYPE_STONEMAN2 ||
                            obj->type == TYPE_BIG_CLOWN || obj->type == TYPE_WAT_CLOWN ||
                            (obj->type == TYPE_SPIDER && obj->field23_0x3c != 0) ||
                            obj->type == TYPE_TROMPETTE || obj->type == TYPE_MITE || obj->type == TYPE_MITE2 ||
                            obj->type == TYPE_CAISSE_CLAIRE || obj->type == TYPE_WALK_NOTE_1 || obj->type == TYPE_SPIDER_PLAFOND ||
                            (obj->type == TYPE_BLACKTOON1 &&
                                (foll_spr = obj->follow_sprite, foll_spr == 1 || foll_spr == 4 || (foll_spr == 7 && obj->field56_0x69 == 2)) &&
                                !(obj->main_etat == 0 && obj->sub_etat == 4)
                            )
                        )
                    )
                    {
                        makeUturn(obj);
                        obj->btypes[0] = BTYP_SOLID;
                    }
                }
            }
            btyp = obj->btypes[0];
            return btyp;
        }
        else
            return btyp;
    }
    else
    {
        btyp = obj->btypes[0];
        return btyp;
    }
}