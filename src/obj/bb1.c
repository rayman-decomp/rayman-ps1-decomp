#include "obj/bb1.h"

#ifdef BSS_DEFS
BB1Data bb1;
s16 PS1_AlwaysObjects[100];
s16 PS1_AlwaysObjectsCount;
s16 PosPierre;
s16 IndAtak;
s16 IndSerie;
s16 NextAtak;
s16 YaDesChiens;
s16 PierreDoitExploser;
s16 RMrepere;
s16 horlogeDog;
#endif

/* TODO: check rodata padding once everything is matching */

/* 5783C 8017C03C -O2 -msoft-float */
/*? set_sub_etat(Obj *, ?);*/

void DO_TOTEM_TOUCHE(Obj *obj, s16 sprite)
{
    s16 x_pos;

    if (sprite == 6 && obj->field23_0x3c == 0)
    {
        if (level.objects[poing_obj_id].speed_x > 0)
        {
            set_sub_etat(obj, 4);
            x_pos = obj->init_x_pos + 71;
        }
        else
        {
            set_sub_etat(obj, 5);
            x_pos = obj->init_x_pos - 85;
        }
        obj->x_pos = x_pos;
        obj->iframes_timer = 0;
        obj->field23_0x3c = 0x00FF;
        obj->anim_frame = 0xFF;
    }
    else if (sprite >= 2)
    {
        if (level.objects[poing_obj_id].speed_x > 0)
            set_sub_etat(obj, 7);
        else
            set_sub_etat(obj, 6);
    }
}

/* 57950 8017C150 -O2 -msoft-float */
void DO_TOTEM_COMMAND(Obj *tot_obj)
{
    s16 x; s16 y; s16 w; s16 h;
    u8 nb_objs;
    s16 i;
    s16 j;
    Obj *cur_obj;
    s16 new_spd_x;
    u8 unk_1;
    s16 new_x;

    tot_obj->field23_0x3c--;
    if (tot_obj->field23_0x3c < 0)
        tot_obj->field23_0x3c = 0;
    if (bb1.field2_0x4 == 3)
    {
        tot_obj->flags &= ~FLG(OBJ_ACTIVE);
        tot_obj->flags &= ~FLG(OBJ_ALIVE);
        nb_objs = level.nb_objects;
        i = 0;
        cur_obj = level.objects;
        if (nb_objs != 0)
        {
            do
            {
                if (cur_obj->type == TYPE_BOUT_TOTEM)
                {

                    for (j = 0; j < 6; cur_obj++, j++)
                    {
                        GET_SPRITE_POS(tot_obj, j, &x, &y, &w, &h);
                        cur_obj->x_pos = x;
                        cur_obj->y_pos = y;
                        cur_obj->flags |= FLG(OBJ_ACTIVE) | FLG(OBJ_ALIVE);
                        if (j == 0)
                        {
                            cur_obj->speed_x = 0;
                            cur_obj->speed_y = 0;
                        }
                        else
                        {
                            new_spd_x = 2 - myRand(4);
                            cur_obj->speed_x = new_spd_x;
                            if (new_spd_x == 0)
                                cur_obj->speed_x = 1;
                            cur_obj->speed_y = -4 - myRand(3);
                        }
                        cur_obj->gravity_value_1 = 0;
                        cur_obj->gravity_value_2 = 5;
                        switch (j)
                        {
                        case 1:
                            set_main_and_sub_etat(cur_obj, 2, 8);
                            cur_obj->offset_by = 43;
                            cur_obj->offset_bx = 25;
                            cur_obj->flags &= ~FLG(OBJ_FLIP_X);
                            cur_obj->anim_index = 31;
                            break;
                        case 2:
                            set_main_and_sub_etat(cur_obj, 2, 10);
                            cur_obj->offset_by = 17;
                            cur_obj->offset_bx = 12;
                            cur_obj->flags &= ~FLG(OBJ_FLIP_X);
                            cur_obj->anim_index = 33;
                            break;
                        case 3:
                            set_main_and_sub_etat(cur_obj, 2, 11);
                            cur_obj->offset_by = 7;
                            cur_obj->offset_bx = 7;
                            cur_obj->flags &= ~FLG(OBJ_FLIP_X);
                            cur_obj->anim_index = 34;
                            break;
                        case 4:
                            set_main_and_sub_etat(cur_obj, 2, 9);
                            cur_obj->offset_by = 28;
                            cur_obj->offset_bx = 17;
                            cur_obj->flags &= ~FLG(OBJ_FLIP_X);
                            cur_obj->anim_index = 32;
                            break;
                        case 5:
                            set_main_and_sub_etat(cur_obj, 2, 10);
                            cur_obj->offset_by = 17;
                            cur_obj->offset_bx = 12;
                            cur_obj->flags = (cur_obj->flags | FLG(OBJ_FLIP_X));
                            cur_obj->anim_index = 33;
                            break;
                        case 0:
                            set_main_and_sub_etat(cur_obj, 0, 21);
                            cur_obj->flags &= ~FLG(OBJ_FLIP_X);
                            cur_obj->anim_index = 37;
                            break;
                        }
                    }
                    break;
                }
                i++;
                cur_obj++;
            } while (i < nb_objs);
        }
    }
    else if (!(tot_obj->sub_etat == 6 || tot_obj->sub_etat == 7 || tot_obj->sub_etat == 3))
    {
        GET_SPRITE_POS(tot_obj, 6, &x, &y, &w, &h);
        x += 5; y += 5; w -= 10; h -= 10;
        if (inter_box(x, y, w, h, bb1.sprite6_x, bb1.sprite6_y, 32, 32) && bb1.field2_0x4 == 0)
        {

            bb1.field2_0x4 = 1;
            tot_obj->iframes_timer = 4;
            IndSerie++;
            if (IndSerie > 5)
                IndSerie--;
            IndAtak = 0;
        }

        if (tot_obj->anim_frame == (tot_obj->animations[tot_obj->anim_index].frames_count - 1))
            unk_1 = horloge[tot_obj->eta[tot_obj->main_etat][tot_obj->sub_etat].anim_speed & 0xf] == 0;
        else
            unk_1 = false;

        switch (tot_obj->sub_etat)
        {
        case 3:
        case 6:
        case 7:
            break;
        case 4:
            if (unk_1)
            {
                if (++tot_obj->iframes_timer < 4)
                {
                    set_sub_etat(tot_obj, 5);
                    tot_obj->x_pos = tot_obj->init_x_pos - 85;
                }
                else
                {
                    set_sub_etat(tot_obj, 6);
                    tot_obj->x_pos = tot_obj->init_x_pos;
                }
            }
            break;
        case 5:
            if (unk_1)
            {
                if (++tot_obj->iframes_timer < 4)
                {
                    set_sub_etat(tot_obj, 4);
                    tot_obj->x_pos = tot_obj->init_x_pos + 71;
                }
                else
                {
                    set_sub_etat(tot_obj, 7);
                    tot_obj->x_pos = tot_obj->init_x_pos;
                }
            }
            break;
        }
    }
}

/* 57EC4 8017C6C4 -O2 -msoft-float */
void DO_TOTBT_REBOND(Obj *obj)
{
    if (obj->speed_y > 0 && obj->y_pos + obj->offset_by >= 265)
    {
        obj->speed_x /= 2;
        obj->speed_y = -obj->speed_y / 2;
        if (obj->speed_y == 0)
            obj->gravity_value_2 = 0xFF;
        obj->gravity_value_1 = 5 - obj->gravity_value_1;
    }
}

/* 57F48 8017C748 -O2 -msoft-float */
/*? PlaySnd_old(?);
? allocateExplosion(Obj *);
? allocateStoneChips(Obj *);*/

void DO_PI_EXPLOSION2(Obj *obj)
{
    PlaySnd_old(0x54);
    obj->speed_x = -1;
    obj->x_pos += 20;
    allocateStoneChips(obj);
    obj->speed_x = 1;
    obj->x_pos -= 40;
    allocateStoneChips(obj);
    obj->x_pos += 20;
    allocateExplosion(obj);
}

/* 57FBC 8017C7BC -O2 -msoft-float */
/*? PlaySnd(?, s16);
? recale_position(Obj *);
? set_main_and_sub_etat(s16 *, ?, ?);*/

void DO_BBL_REBOND(Obj *obj)
{
    s32 x_pos;
    s16 x_pierre;

    PlaySnd(0xC8, obj->id);
    switch (obj->field23_0x3c)
    {
    case 0:
        obj->speed_y = -5;
        obj->gravity_value_1 = 3 - obj->gravity_value_1;
        break;
    case 2:
        obj->speed_y = -5;
        obj->gravity_value_1 = 3 - obj->gravity_value_1;
        x_pos = obj->x_pos;
        if (obj->flags & FLG(OBJ_FLIP_X))
            x_pierre = x_pos - 130;
        else
            x_pierre = x_pos + 25;
        PosPierre = x_pierre;
        break;
    case 4:
        DO_PI_EXPLOSION2(obj);
        obj->flags &= ~FLG(OBJ_ACTIVE);
        obj->flags &= ~FLG(OBJ_ALIVE);
        if (ray.field20_0x36 == obj->id)
        {
            ray.field20_0x36 = -1;
            obj->ray_dist = 1000;
            set_main_and_sub_etat(&ray, 2, 2);
        }
        PS1_AlwaysObjectsCount -= 1;
        break;
    }
    recale_position(obj);
}

/* 580F8 8017C8F8 -O2 -msoft-float */
void allocateDog(Obj *bb1_obj)
{
    s16 new_x;
    s16 nb_objs = level.nb_objects;
    Obj *cur = level.objects;
    s16 i = 0;

    if (nb_objs != 0)
    {
        do
        {
            if (cur->type == TYPE_STONEDOG2 && !(cur->flags & FLG(OBJ_ACTIVE)))
            {
                if (!((((bb1_obj->flags >> OBJ_FLIP_X) & 1) + YaDesChiens) & 1))
                {
                    new_x = -20;
                    cur->flags |= FLG(OBJ_FLIP_X);
                }
                else
                {
                    new_x = 260;
                    cur->flags &= ~FLG(OBJ_FLIP_X);
                }
                obj_init(cur);
                cur->cmd_offset = -1;
                cur->x_pos = new_x;
                cur->y_pos = bb1_obj->y_pos - 20;
                cur->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
                cur->speed_x = 0;
                cur->speed_y = 0;
                cur->main_etat = 2;
                cur->flags = cur->flags & ~FLG(OBJ_FLAG_9);
                cur->sub_etat = 2;
                if (cur->flags & FLG(OBJ_FLIP_X))
                    skipToLabel(cur, 1, true);
                else
                    skipToLabel(cur, 0, true);
                calc_obj_pos_map(cur);
                if (niveau == 0)
                    cur->hit_points = 1;
                break;
            }
            cur++;
            i++;
        } while (i < nb_objs);
    }
}

/* 58278 8017CA78 -O2 -msoft-float */
void allocateTir(Obj *bb1_obj, s16 param_2)
{
    s32 sprite_ind;
    s16 x; s16 y; s16 w; s16 h;
    s32 new_x_1;
    s32 bb1_x;
    s32 new_spd_x;
    s32 new_x_2;
    u8 nb_objs = level.nb_objects;
    s16 i = 0;
    Obj *cur_obj = level.objects;

    if (nb_objs != 0)
    {
        do
        {
            if (cur_obj->type == TYPE_BBL && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
            {
                if (param_2 != 0)
                    sprite_ind = 8;
                else
                    sprite_ind = 9;
                cur_obj->flags &= ~FLG(OBJ_FLIP_X);
                GET_SPRITE_POS(bb1_obj, sprite_ind, &x, &y, &w, &h);
                if (param_2 == 1)
                {
                    new_x_1 = x - cur_obj->offset_bx + (w >> 1);
                    if (bb1_obj->flags & FLG(OBJ_FLIP_X))
                        new_x_1 += 64;
                    else
                        new_x_1 -= 64;
                    cur_obj->x_pos = new_x_1;
                    cur_obj->y_pos = y - 40;
                    if (bb1_obj->flags & FLG(OBJ_FLIP_X))
                        new_spd_x = 12;
                    else
                        new_spd_x = -12;
                    cur_obj->speed_x = new_spd_x;
                    cur_obj->speed_y = 0;
                    cur_obj->flags = cur_obj->flags & ~FLG(OBJ_FLIP_X) | bb1_obj->flags & FLG(OBJ_FLIP_X);
                }
                else if (param_2 == 0)
                {
                    new_x_1 = (x - cur_obj->offset_bx) + (w >> 1);
                    if (bb1_obj->flags & FLG(OBJ_FLIP_X))
                        new_x_1 += 9;
                    else
                        new_x_1 -= 9;
                    cur_obj->x_pos = new_x_1;
                    cur_obj->y_pos = y - 40;
                    if (bb1_obj->flags & FLG(OBJ_FLIP_X))
                        new_spd_x = 2;
                    else
                        new_spd_x = -2;
                    cur_obj->speed_x = new_spd_x;
                    cur_obj->speed_y = -5;
                    cur_obj->flags = cur_obj->flags & ~FLG(OBJ_FLIP_X) | bb1_obj->flags & FLG(OBJ_FLIP_X);
                }
                else
                {
                    if (param_2 == 3)
                    {
                        bb1_x = bb1_obj->x_pos;
                        if (!(bb1_obj->flags & FLG(OBJ_FLIP_X)))
                            cur_obj->x_pos = bb1_x - 36;
                        else
                            cur_obj->x_pos = bb1_x + 120;
                        cur_obj->y_pos = bb1_obj->y_pos - 185;
                        cur_obj->speed_y = 4;
                    }
                    else
                    {
                        if (param_2 < 10)
                        {
                            cur_obj->x_pos = ray.x_pos;
                            if (cur_obj->x_pos < 40)
                                cur_obj->x_pos = 40;
                            if (cur_obj->x_pos > 200)
                                cur_obj->x_pos = 200;
                        }
                        else
                        {
                            if (bb1_obj->flags & FLG(OBJ_FLIP_X))
                                new_x_2 = 240 - bb1.field8_0xe * 50;
                            else
                            {
                                new_x_2 = bb1.field8_0xe * 50 - 20;
                            }
                            cur_obj->x_pos = new_x_2;
                        }
                        cur_obj->y_pos = bb1_obj->y_pos - 200;
                        cur_obj->speed_y = 0;
                    }
                    cur_obj->speed_x = 0;
                }
                cur_obj->iframes_timer = 38;
                if (param_2 != 3)
                    cur_obj->gravity_value_2 = 10;
                else
                    cur_obj->gravity_value_2 = 7;

                if (param_2 == 0)
                    cur_obj->gravity_value_2 = 3;
                cur_obj->main_etat = 2;
                cur_obj->sub_etat = 6;
                skipToLabel(cur_obj, 1, true);
                calc_obj_pos_map(cur_obj);
                cur_obj->gravity_value_1 = 0;
                cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
                if (param_2 < 10)
                    cur_obj->field23_0x3c = param_2;
                else
                    cur_obj->field23_0x3c = 4;
                if (param_2 != 3)
                {
                    PS1_AlwaysObjects[PS1_AlwaysObjectsCount] = cur_obj->id;
                    PS1_AlwaysObjectsCount++;
                }
                break;
            }
            cur_obj++;
            i++;
        } while (i < nb_objs);
    }
}

/* 58644 8017CE44 -O2 -msoft-float */
void CreateFirstBBL(void)
{
    Obj *obj;
    s16 i;
    u8 nb_objs;

    obj = level.objects;
    i = 0;
    nb_objs = level.nb_objects;
    if (nb_objs != 0)
    {
        do
        {
            if (obj->type == TYPE_BBL && !(obj->flags & FLG(OBJ_ACTIVE)))
            {
                obj->x_pos = -40;
                PosPierre = -15;
                obj->y_pos = 160;
                obj->speed_x = 0;
                obj->speed_y = 0;
                obj->iframes_timer = 38;
                obj->gravity_value_2 = 3;
                obj->main_etat = 2;
                obj->sub_etat = 6;
                obj->flags = obj->flags & ~FLG(OBJ_FLIP_X);
                skipToLabel(obj, 1, true);
                calc_obj_pos_map(obj);
                obj->gravity_value_1 = 0;
                obj->field23_0x3c = 2;
                obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
                PS1_AlwaysObjects[PS1_AlwaysObjectsCount] = obj->id;
                PS1_AlwaysObjectsCount++;
                break;
            }
            obj++;
            i++;
        } while (nb_objs > i);
    }
}

/* 58784 8017CF84 -O2 -msoft-float */
void INIT_BBMONT(Obj *obj)
{
    calc_obj_pos_map(obj);
    obj->field23_0x3c = 0;
    obj->gravity_value_2 = 10;
    Phase = 0;
    WaitForAnim = false;
    WaitForFinAtan = 10;
    PosPierre = 9999;
    PierreDoitExploser = 0;
    IndSerie = 0;
    IndAtak = 0;
    RMrepere = 0;
    YaDesChiens = 0;
    screen_trembling2 = 0;
    obj->flags |= FLG(OBJ_ALIVE);
    obj->flags &= ~FLG(OBJ_ACTIVE);
    bb1.field1_0x2 = -1;
    bb1.speed_x = 0;
    bb1.saved_cmd = 0;
    bb1.field2_0x4 = 0;
    bb1.field8_0xe = 1;
}

/* 5884C 8017D04C -O2 -msoft-float */
void DO_BBL_COMMAND(Obj *obj)
{
    s16 new_spd_x;
    s32 spd_x_abs;
    s32 spd_x;
    s32 bb1_x;
    s16 unk_x;

    if (PierreDoitExploser)
    {
        DO_PI_EXPLOSION2(obj);
        obj->flags &= ~FLG(OBJ_ACTIVE);
        obj->flags &= ~FLG(OBJ_ALIVE);
        if (ray.field20_0x36 == obj->id)
        {
            ray.field20_0x36 = -1;
            obj->ray_dist = 1000;
            set_main_and_sub_etat(&ray, 2, 2);
        }
        PierreDoitExploser = false;
        PosPierre = 9999;
        PS1_AlwaysObjectsCount--;
    }

    if (obj->field23_0x3c == 3 && --obj->iframes_timer == 0)
    {
        obj->flags &= ~FLG(OBJ_ACTIVE);
        obj->flags &= ~FLG(OBJ_ALIVE);
    }

    if (obj->speed_x < 0)
        unk_x = -20;
    else
        unk_x = 20;

    if (
        block_flags [
            (u16) mp.map [
                (s16) (((obj->x_pos + obj->offset_bx + unk_x) >> 4) + mp.width * ((obj->y_pos + 40) >> 4))
            ] >> 10
        ] >> BLOCK_FLAG_4 & 1
    )
    {
        switch (obj->field23_0x3c)
        {
        case 1:
            PlaySnd(200, obj->id);
            spd_x = obj->speed_x;
            spd_x_abs = __builtin_abs(spd_x);
            if (spd_x_abs == 12)
            {

                if (spd_x > 0)
                    new_spd_x = -13;
                else
                    new_spd_x = 13;
                obj->speed_x = new_spd_x;
                obj->speed_y = 0;
            }
            else if (spd_x_abs == 13)
            {
                if (spd_x > 0)
                    new_spd_x = -14;
                else
                    new_spd_x = 14;
                obj->speed_x = new_spd_x;
                obj->speed_y = 0;
            }
            else if (spd_x_abs == 14)
            {
                if (spd_x > 0)
                    new_spd_x = -15;
                else
                    new_spd_x = 15;
                obj->speed_x = new_spd_x;
                obj->speed_y = 0;
            }
            else if (spd_x_abs == 15)
            {
                DO_PI_EXPLOSION2(obj);
                obj->flags &= ~FLG(OBJ_ACTIVE);
                obj->flags &= ~FLG(OBJ_ALIVE);
                if (ray.field20_0x36 == obj->id)
                {
                    ray.field20_0x36 = -1;
                    obj->ray_dist = 1000;
                    set_main_and_sub_etat(&ray, 2, 2);
                }
                PS1_AlwaysObjectsCount--;
                return;
            }
            break;
        case 0:
            PlaySnd(200, obj->id);
            obj->speed_x = 0;
            obj->field23_0x3c = 2;
            break;
        }
    }
}

/* 58B04 8017D304 -O2 -msoft-float */
void BBMONT_ECLAIR(Obj *bb1_obj)
{
    s16 new_spd_x;
    s32 new_x;
    s16 x; s16 y; s16 w; s16 h;
    u8 nb_objs = level.nb_objects;
    s16 i = 0;
    Obj *cur_obj = level.objects;

    if (nb_objs != 0)
    {
        do
        {
            if (cur_obj->type == TYPE_ECLAIR && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
            {
                cur_obj->flags = cur_obj->flags & ~FLG(OBJ_FLIP_X) | bb1_obj->flags & FLG(OBJ_FLIP_X);
                cur_obj->speed_y = 0;
                if (!(cur_obj->flags & FLG(OBJ_FLIP_X)))
                    cur_obj->speed_x = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_left;
                else
                    cur_obj->speed_x = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].speed_x_right;
                GET_SPRITE_POS(bb1_obj, 10, &x, &y, &w, &h);
                new_x = (x + w) - cur_obj->offset_bx;
                if ((bb1_obj->flags & FLG(OBJ_FLIP_X)))
                    new_x += 16;
                else
                    new_x -= 16;
                cur_obj->x_pos = new_x;
                cur_obj->y_pos = y;
                cur_obj->init_x_pos = cur_obj->x_pos;
                cur_obj->init_y_pos = cur_obj->y_pos;
                skipToLabel(cur_obj, cur_obj->flags >> OBJ_FLIP_X & 1, true);
                calc_obj_pos_map(cur_obj);
                cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                allocateExplosion(cur_obj);
                break;
            }
            cur_obj++;
            i++;
        } while (i < nb_objs);
    }
}

/* 58CC4 8017D4C4 -O2 -msoft-float */
void BBMONT_ETINCELLES(Obj *in_obj)
{
    s16 in_x; s16 in_y; s16 in_w; s16 in_h;
    s16 i = 0;
    Obj *cur_obj = &level.objects[0];
    u8 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_ETINC && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
      /* sprite 3 */
            cur_obj->flags = cur_obj->flags & ~FLG(OBJ_FLIP_X) | in_obj->flags & FLG(OBJ_FLIP_X);
            cur_obj->speed_y = 0;
            if (!(cur_obj->flags & FLG(OBJ_FLIP_X)))
                cur_obj->speed_x = 7;
            else
                cur_obj->speed_x = -7;

            GET_SPRITE_POS(in_obj, 3, &in_x, &in_y, &in_w, &in_h);
            if (!(in_obj->flags & FLG(OBJ_FLIP_X)))
                in_w = 0;

            cur_obj->x_pos = in_x + in_w - cur_obj->offset_bx;
            cur_obj->y_pos = in_y - 8;
            cur_obj->init_x_pos = cur_obj->x_pos;
            cur_obj->init_y_pos = cur_obj->y_pos;
            skipToLabel(cur_obj, cur_obj->flags >> OBJ_FLIP_X & 1, true);
            calc_obj_pos_map(cur_obj);
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);

      /* sprite 2 */
            cur_obj++;
            cur_obj->flags = cur_obj->flags & ~FLG(OBJ_FLIP_X) | in_obj->flags & FLG(OBJ_FLIP_X);
            cur_obj->speed_y = 0;
            if (!(cur_obj->flags & FLG(OBJ_FLIP_X)))
                cur_obj->speed_x = 7;
            else
                cur_obj->speed_x = -7;

            GET_SPRITE_POS(in_obj, 2, &in_x, &in_y, &in_w, &in_h);
            if (!(in_obj->flags & FLG(OBJ_FLIP_X)))
                in_w = 0;

            cur_obj->x_pos = in_x + in_w - cur_obj->offset_bx;
            cur_obj->y_pos = in_y - 8;
            cur_obj->init_x_pos = cur_obj->x_pos;
            cur_obj->init_y_pos = cur_obj->y_pos;
            skipToLabel(cur_obj, cur_obj->flags >> OBJ_FLIP_X & 1, true);
            calc_obj_pos_map(cur_obj);
            cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));

            allocateExplosion(cur_obj);
            break;
        }
        cur_obj++;
        i++;
    }
}

/* 58F14 8017D714 -O2 -msoft-float */
void BBMONT_TIRE(Obj *obj)
{
    allocateTir(obj, 1);
}

/* 58F34 8017D734 -O2 -msoft-float */
void Cree_BBL(Obj *obj)
{
    allocateTir(obj, 0);
}

/* 58F54 8017D754 -O2 -msoft-float */
void BB_Attaque(Obj *obj)
{
    switch (NextAtak)
    {
    case 0:
        set_main_and_sub_etat(obj, 0, 4);
        Phase = 1;
        break;
    case 1:
        set_main_and_sub_etat(obj, 0, 3);
        Phase = 2;
        break;
    case 2:
        set_main_and_sub_etat(obj, 0, 6);
        Phase = 3;
        break;
    case 3:
        set_main_and_sub_etat(obj, 0, 7);
        Phase = 4;
        break;
    case 4:
        set_main_and_sub_etat(obj, 0, 2);
        Phase = 5;
        break;
    case 5:
        set_main_and_sub_etat(obj, 0, 4);
        Phase = 12;
        break;
    case 6:
        set_main_and_sub_etat(obj, 2, 3);
        obj->iframes_timer = 35;
        Phase = 11;
        bb1.field8_0xe = 1;
        break;
    case 7:
        set_main_and_sub_etat(obj, 0, 22);
        Phase = 13;
    }
}

/* 5908C 8017D88C -O2 -msoft-float */
void Fin_BB_Attaque(Obj *obj)
{
    IndAtak++;
    if (IndAtak < 7)
        NextAtak = SerieAtakBB[IndSerie][IndAtak].attack;
    else
        NextAtak = 0xff;

    if (NextAtak == 0xff)
    {
        IndAtak = 0;
        NextAtak = SerieAtakBB[IndSerie][IndAtak].attack;
    }
    WaitForFinAtan = SerieAtakBB[IndSerie][IndAtak].wait_for_fin_atan;
    BB_Attaque(obj);
}

/* 59198 8017D998 -O2 -msoft-float */
void BB_Atan(Obj *obj)
{
    if (WaitForFinAtan != 0)
    {
        set_main_and_sub_etat(obj, 0, 0);
        skipToLabel(obj, 0, 1);
        Phase = 6;
    }
    else
        Fin_BB_Attaque(obj);
}

/* 591FC 8017D9FC -O2 -msoft-float */
/*? allocateLandingSmoke(Obj *);
? recale_position();
? set_sub_etat(Obj *, ?);*/

void DO_BBMONT_ATTER(Obj *obj)
{
    obj->speed_y = 0;
    obj->speed_x = 0;
    recale_position(obj);
    set_sub_etat(obj, 6);
    allocateLandingSmoke(obj);
    screen_trembling3 = 1;
}

/* 59248 8017DA48 -O2 -msoft-float */
void DO_BBMONT_COMMAND(Obj *obj)
{
    s16 unk_1; s16 unk_2;
    s32 x_1;
    s32 x_2;
    s32 pos_pierre;
    u8 wait;
    s16 new_dogs;
    s16 new_spd_x_1;
    s16 new_spd_x_2;

    scrollLocked = true;
    if (YaDesChiens != 0 && --horlogeDog < 0)
    {
        horlogeDog = 50;
        allocateDog(obj);
        YaDesChiens--;
    }
    GET_SPRITE_POS(obj, 6, &bb1.sprite6_x, &bb1.sprite6_y, &unk_1, &unk_2);
    unk_1 = obj->x_pos;
    unk_2 = obj->y_pos;
    if (
        obj->anim_frame == obj->animations[obj->anim_index].frames_count - 1 &&
        horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0
    )
        FinAnim = true;
    else
        FinAnim = false;

    if (bb1.field2_0x4 == 2 && FinAnim)
    {
        if (obj->hit_points == obj->init_hit_points - 1)
        {
            skipToLabel(obj, 4, true);
            Phase = 7;
        }
        set_main_and_sub_etat(obj, bb1.saved_main_etat, bb1.saved_sub_etat);
        WaitForFinAtan = 1;
        obj->cmd = bb1.saved_cmd;
    }
    if (bb1.field2_0x4 == 1)
    {
        if (!(obj->main_etat == 0 && obj->sub_etat == 9))
        {
            bb1.saved_main_etat = obj->main_etat;
            bb1.saved_sub_etat = obj->sub_etat;
            set_main_and_sub_etat(obj, 0, 9);
            bb1.field2_0x4 = 2;
            FinAnim = false;
            obj->speed_x = 0;
            obj->hit_points--;
            bb1.saved_cmd = obj->cmd;
            if (obj->hit_points == 0)
            {
                bb1.field2_0x4 = 3;
                set_main_and_sub_etat(obj, 0, 20);
                obj->speed_x = 0;
                bb1.saved_cmd = 420;
            }
        }
        else
            bb1.field2_0x4 = 0;
    }

    if (bb1.field2_0x4 == 3)
    {
        if (--bb1.saved_cmd <= 0)
        {
            fin_boss = true;
            bb1.saved_cmd = 999;
            finBosslevel.mr_stone = true;
        }
    }
    else
    {
        switch (obj->cmd)
        {
        case GO_LEFT:
            obj->flags &= ~FLG(OBJ_FLIP_X);
        case GO_RIGHT:
            if (obj->cmd == GO_RIGHT)
                obj->flags |= FLG(OBJ_FLIP_X);
            SET_X_SPEED(obj);
            if (block_flags[calc_typ_travd(obj, false)] >> BLOCK_FLAG_4 & 1)
            {
                /* toggle, i assume? */
                obj->flags = obj->flags & ~FLG(OBJ_FLIP_X) | ((obj->flags >> OBJ_FLIP_X ^ 1) & 1) << OBJ_FLIP_X;
                skipToLabel(obj, 6, true);
                if (IndSerie > 3)
                    WaitForFinAtan = 2;
                Phase = 8;
            }

            if (Phase == 7)
            {
                /* different way to write this, or is this the nicest??? */
                pos_pierre = PosPierre;
                x_1 = obj->x_pos;
                if (
                    (obj->flags & FLG(OBJ_FLIP_X) && (x_1 < pos_pierre + 14)) ||
                    (!(obj->flags & FLG(OBJ_FLIP_X)) && (x_1 < pos_pierre - 6))
                )
                {
                    pos_pierre = PosPierre;
                    x_2 = obj->x_pos;
                    if (
                        (obj->flags & FLG(OBJ_FLIP_X) && (x_2 > pos_pierre + 6)) ||
                        (!(obj->flags & FLG(OBJ_FLIP_X)) && (x_2 > pos_pierre - 14))
                    )
                    {
                        set_main_and_sub_etat(obj, 0, 2);
                        skipToLabel(obj, 0, true);
                        Phase = 9;
                    }
                }
            }
            CALC_MOV_ON_BLOC(obj);
            break;
        case GO_WAIT:
            switch (Phase)
            {
            case 0:
                if (bb1.field8_0xe != 0)
                {
                    CreateFirstBBL();
                    WaitForAnim = true;
                    bb1.field8_0xe = 0;
                }

                if (FinAnim && WaitForAnim)
                {
                    obj->anim_frame = 0;
                    IndSerie = 0;
                    IndAtak = 0;
                    WaitForFinAtan = SerieAtakBB[IndSerie][IndAtak].wait_for_fin_atan;
                    NextAtak = SerieAtakBB[IndSerie][IndAtak].attack;
                    BB_Attaque(obj);
                }
                break;
            case 1:
                if (
                    obj->sub_etat == 4 && obj->anim_frame == 14 &&
                    horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0 &&
                    screen_trembling2 == 0
                )
                {
                    screen_trembling2 = 1;
                    allocateTir(obj, 4);
                }

                if (FinAnim)
                    BB_Atan(obj);
                break;
            case 2:
                if (
                    obj->sub_etat == 11 && obj->anim_frame == 23 &&
                    horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0
                )
                    allocateTir(obj, 1);
                if (
                    obj->sub_etat == 3 && obj->anim_frame == 14 &&
                    horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0 &&
                    screen_trembling2 == 0
                )
                {
                    screen_trembling2 = 1;
                    allocateTir(obj, 3);
                    wait = WaitForFinAtan;
                    if (niveau == 0)
                        WaitForFinAtan = wait + 3;
                    else
                        WaitForFinAtan = wait + 1;
                }
                if (obj->sub_etat == 10 && FinAnim)
                {
                    if (--WaitForFinAtan != 0)
                    {
                        obj->anim_frame = 0;
                        set_sub_etat(obj, 10);
                    }
                }
                if (obj->sub_etat == 11 && FinAnim)
                {
                    Phase = 11;
                    obj->iframes_timer = 35;
                }
                break;
            case 3:
                if (
                    obj->sub_etat == 6 && obj->anim_frame == 64 &&
                    horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0
                )
                {
                    if (niveau == 0)
                        new_dogs = 3;
                    else
                        new_dogs = 4;
                    YaDesChiens = new_dogs;
                    horlogeDog = 0;
                }

                if (FinAnim)
                    BB_Atan(obj);
                break;
            case 4:
                if (
                    obj->sub_etat == 7 && obj->anim_frame == 44 &&
                    horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0
                )
                {
                    BBMONT_ETINCELLES(obj);
                    PlaySnd(114, obj->id);
                }

                if (FinAnim)
                    BB_Atan(obj);
                break;
            case 5:
                if (
                    obj->sub_etat == 2 && obj->anim_frame == 21 &&
                    horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0
                )
                {
                    BBMONT_ECLAIR(obj);
                    PlaySnd(114, obj->id);
                }

                if (FinAnim)
                {
                    obj->anim_frame = 0;
                    set_sub_etat(obj, 1);
                    Phase = 10;
                }
                break;
            case 6:
                if (FinAnim && --WaitForFinAtan == 0)
                    Fin_BB_Attaque(obj);
                break;
            case 7:
                if (
                    obj->sub_etat == 8 && obj->anim_frame == 14 &&
                    horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0
                )
                    allocateTir(obj, 0);
                else
                {
                    if (FinAnim)
                    {
                        if (--WaitForFinAtan == 0)
                        {
                            set_main_and_sub_etat(obj, 1, 2);
                            if (obj->flags & FLG(OBJ_FLIP_X))
                                skipToLabel(obj, 5, true);
                            else
                                skipToLabel(obj, 4, true);
                        }
                        else
                            set_sub_etat(obj, 1);
                    }
                }

                break;
            case 8:
                if (FinAnim)
                {
                    if (obj->sub_etat != 9)
                    {
                        if (WaitForFinAtan == 2)
                        {
                            set_main_and_sub_etat(obj, 0, 1);
                            WaitForFinAtan--;
                        }
                        else
                        {
                            if (bb1.field8_0xe == 0)
                            {
                                /* ... */
                                WaitForFinAtan = SerieAtakBB[IndSerie][0].wait_for_fin_atan;
                                NextAtak = SerieAtakBB[IndSerie][0].attack;
                                IndAtak = 0;
                                BB_Attaque(obj);
                            }
                            else
                            {
                                Fin_BB_Attaque(obj);
                                bb1.field8_0xe = 0;
                            }
                        }
                    }
                }
                break;
            case 9:
                if (
                    obj->anim_frame == 20 &&
                    horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0 &&
                    obj->sub_etat != 9
                )
                    PierreDoitExploser = true;

                if (FinAnim && bb1.field2_0x4 != 2)
                {
                    set_main_and_sub_etat(obj, 1, 0);
                    if (obj->flags & FLG(OBJ_FLIP_X))
                        skipToLabel(obj, 5, true);
                    else
                        skipToLabel(obj, 4, true);
                    PierreDoitExploser = false;
                }
                break;
            case 10:
                if (FinAnim)
                {
                    obj->anim_frame = 0;
                    set_main_and_sub_etat(obj, 1, 1);
                    if (obj->flags & FLG(OBJ_FLIP_X))
                        skipToLabel(obj, 5, true);
                    else
                        skipToLabel(obj, 4, true);
                }
                break;
            case 11:
                switch (obj->sub_etat)
                {
                case 0:
                case 3:
                    if (--obj->iframes_timer > 1)
                    {
                        obj->speed_y = -8;
                        obj->gravity_value_1 = 0;
                        if (obj->flags & FLG(OBJ_FLIP_X))
                            new_spd_x_1 = 4;
                        else
                            new_spd_x_1 = -4;
                        obj->speed_x = new_spd_x_1;
                    }
                    else
                    {
                        set_sub_etat(obj, 4);
                        if (obj->flags & FLG(OBJ_FLIP_X))
                            new_spd_x_2 = 2;
                        else
                            new_spd_x_2 = -2;
                        obj->speed_x = new_spd_x_2;
                    }
                    break;
                case 6:
                    if (FinAnim)
                    {
                        set_main_and_sub_etat(obj, 1, 0);
                        if (obj->flags & FLG(OBJ_FLIP_X))
                            skipToLabel(obj, 5, true);
                        else
                            skipToLabel(obj, 4, true);
                    }
                    break;
                }
                break;
            case 12:
                if (
                    obj->sub_etat == 4 && obj->anim_frame == 14 &&
                    horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0 &&
                    screen_trembling2 == 0
                )
                {
                    screen_trembling2 = 1;
                    allocateTir(obj, bb1.field8_0xe + 10);
                    bb1.field8_0xe++;
                }

                if (FinAnim && bb1.field8_0xe == 3)
                {
                    bb1.field8_0xe = 0;
                    BB_Atan(obj);
                }
                break;
            case 13:
                if (obj->sub_etat == 22)
                {
                    if (
                        obj->anim_frame == 63 &&
                        horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0
                    )
                        allocateTir(obj, 1);
                    if (
                        obj->anim_frame == 14 &&
                        horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0 &&
                        screen_trembling2 == 0
                    )
                    {
                        screen_trembling2 = 1;
                        allocateTir(obj, 3);
                    }

                    if (FinAnim)
                    {
                        Phase = 11;
                        obj->iframes_timer = 35;
                        bb1.field8_0xe = 1;
                    }
                }
            }
            break;
        }

        if (FinAnim && bb1.field2_0x4 == 2)
            bb1.field2_0x4 = 0;
    }
}

/* 5A260 8017EA60 -O2 -msoft-float */
void DO_BBMONT_TOUCHE(Obj *obj)
{
    set_sub_etat(obj, 8);
    obj->anim_frame = 0;
    Phase = 7;
    WaitForFinAtan = 2;
}

/* 5A2A4 8017EAA4 -O2 -msoft-float */
#ifndef NONMATCHINGS
INCLUDE_ASM("asm/nonmatchings/obj/bb1", DO_BBMONT2_COMMAND);
#else
/* score of ??? */
static inline void test_123098(Obj *obj)
{
    switch (bb1.speed_x)
    {
    case 2:
        set_main_and_sub_etat(obj, 1U, 1U);
        break;
    case 3:
        set_main_and_sub_etat(obj, 1U, 2U);
        break;
    case 0:
    default:
        set_main_and_sub_etat(obj, 1U, 0U);
        break;
    }
}

void DO_BBMONT2_COMMAND(Obj *obj)
{
    s16 temp_s2;
    s16 temp_s3;
    s32 temp_v0_2;
    s16 temp_v0_3;
    s16 var_v0_2;
    s16 var_v1;
    s32 temp_v0;
    s32 var_a0;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v1_2;
    u16 temp_v0_4;
    u16 var_v0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    BB1Data *test_1;
    s32 test_2;
    s32 test_3;
    u8 test_4;
    u8 test_5;
    u32 test_6;

    temp_s2 = (u16) obj->x_pos + obj->offset_bx;
    temp_s3 = obj->offset_hy + (u16) obj->y_pos + 0x40;
    if ((obj->anim_frame == (obj->animations[obj->anim_index].frames_count - 1)) && (horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0))
    {
        FinAnim = 1;
    }
    else
    {
        FinAnim = 0;
    }
    if (((u8) Phase < 2U) && (obj->main_etat != 2) && ((u32) ((ray_zdc_x - temp_s2) + 0x10) < 0x21U) && (ray_zdc_y < (temp_s3 - 0x20)))
    {
        set_main_and_sub_etat(obj, 0U, 0x10U);
        obj->speed_x = 0;
        obj->speed_y = 0;
    }

    if (obj->main_etat == 1)
    {
        if (Phase == 0)
        {
            Phase = 1;
        }
        SET_X_SPEED(obj);
        if ((u8) Phase < 4U)
        {
            CALC_MOV_ON_BLOC(obj);
        }
        if ((FinAnim != 0) && (bb1.speed_x != (obj->sub_etat + 1)))
        {
            test_123098(obj);
        }
    }
    if ((bb1.field1_0x2 < 8) && (Phase != 0) && (Phase != 5))
    {
        if (scroll_end_x == xmapmax)
        {
            scroll_end_x = xmap;
            if (xmap < temp_s2)
            {
                scroll_end_x = temp_s2;
            }
        }
        else if (scroll_end_x < temp_s2)
        {
            bb1.saved_cmd = 1;
        }
        if (bb1.saved_cmd != 0)
        {
            if (obj->main_etat == 1)
            {
                scroll_end_x = (u16) scroll_end_x + (obj->sub_etat + 1);
            }
            else
            {
                scroll_end_x = scroll_end_x + (u16) obj->speed_x;
            }
        }
    }
    else
    {
        scroll_end_x = xmapmax;
    }
    switch (Phase)
    {
    case 0:
        /* gotos-only does not fix this case */
        temp_v0 = ((u8) block_flags[obj->btypes[0]] >> 1) & 1;
        var_a0 = 0x28;
        if ((temp_v0 == 0) && (var_a0 = 0x3C, (temp_v0 == 0)))
        {
            if (((temp_s2 + var_a0) < ray_zdc_x) && (obj->main_etat == 0) && (bb1.speed_x != 0))
            {
                obj->flags |= 0x4000;
                set_main_and_sub_etat(obj, 2U, 1U);
                obj->speed_y = 2;
                return;
            }
        }
        else if ((obj->main_etat == 0) && (obj->sub_etat == 0) && ((var_a0 + temp_s2) < ray_zdc_x))
        {
            Phase = 1;
            test_123098(obj);
        }
        break;
    case 1:
        if (
            (obj->main_etat == 1) &&
            !(block_flags [
                (u16) mp.map [
                    (s16) (((obj->x_pos + obj->offset_bx) >> 4) + mp.width * ((obj->y_pos + obj->offset_by + 8) >> 4))
                ] >> 10
            ] >> 1 & 1)
        )
        {
            set_main_and_sub_etat(obj, 2U, 4U);
            obj->gravity_value_2 = 5;
            obj->gravity_value_1 = 0;
            obj->speed_y = -8;
            obj->speed_x = 3;
        }
        break;
    case 2:
        if (
            (obj->main_etat == 1) &&
            !(block_flags [
                (u16) mp.map [
                    (s16) (((obj->x_pos + (obj->offset_bx - 8)) >> 4) + mp.width * ((obj->y_pos + obj->offset_by + 8) >> 4))
                ] >> 10
            ] >> 1 & 1)
        )
        {
            set_main_and_sub_etat(obj, 2U, 1U);
            obj->gravity_value_2 = 5;
            obj->gravity_value_1 = 0;
            obj->speed_y = 0;
            obj->speed_x = 0;
            bb1.field1_0x2 = -1;
        }
        break;
    case 3:
        scroll_end_x = MAX_1(scroll_end_x, 0x15cc);

        if (((temp_s2 + 0x20) < ray_zdc_x) && (bb1.field1_0x2 == -1) && (temp_s3 < ray_zdc_y))
        {
            if (bb1.speed_x != -1)
            {
                test_123098(obj);
                bb1.field1_0x2 = 0;
            }
            else
            {
                if (obj->field23_0x3c < 0xC8)
                {
                    if (++obj->field23_0x3c == 0x00C8)
                    {
                        bb1.speed_x = 1;
                        set_main_and_sub_etat(obj, 1U, 0U);
                        bb1.field1_0x2 = 0;
                        obj->field23_0x3c = 0x00FF;
                    }
                }
                scroll_end_x = xmap;
                if (scroll_end_x < temp_s2)
                {
                    test_2 = ray.speed_x;
                    if (test_2 < 1)
                        test_2 = 1;
                    scroll_end_x = scroll_end_x + test_2;
                }
            }
        }
        if (FinAnim != 0)
        {
            if ((obj->main_etat == 0) && (obj->sub_etat == 0x10))
            {
                test_123098(obj);
            }
            if ((FinAnim != 0) && (obj->main_etat == 0) && (obj->sub_etat == 1))
            {
                test_123098(obj);
            }
        }
        if (obj->main_etat == 1)
        {
            if (
                !(block_flags [
                    (u16) mp.map [
                        (s16) (((obj->x_pos + (obj->offset_bx - 8)) >> 4) + mp.width * ((obj->y_pos + obj->offset_by + 8) >> 4))
                    ] >> 10
                ] >> 1 & 1)
            )
            {
                obj->speed_y = -6;
                obj->speed_x = 3;
                set_main_and_sub_etat(obj, 2U, 4U);
                obj->gravity_value_2 = 5;
                obj->gravity_value_1 = 0;
            }
            if ((obj->main_etat != 2) && ((u32) ((ray_zdc_x - temp_s2) + 0x10) < 0x21U))
            {
                if (ray_zdc_y < (temp_s3 - 0x20))
                {
                    set_main_and_sub_etat(obj, 0U, 0x10U);
                    obj->speed_y = 0;
                }
                else
                {
                    set_main_and_sub_etat(obj, 0U, 1U);
                    obj->speed_y = 0;
                }
                obj->speed_x = 0;
            }
        }
        break;
    case 4:
        if (bb1.sprite6_y < scroll_end_y)
        {
            scroll_end_y -= 1;
        }
        if (FinAnim != 0)
        {
            if ((obj->main_etat == 2) && (obj->sub_etat == 2))
            {
                bb1.speed_x = 1;
                set_main_and_sub_etat(obj, 1U, 0U);
            }
            else if ((obj->main_etat == 0) && (obj->sub_etat == 5))
            {
                if (++bb1.sprite6_x < 3)
                {
                    bb1.speed_x = 1;
                    set_main_and_sub_etat(obj, 1U, 0U);
                }
                else
                {
                    set_main_and_sub_etat(obj, 0U, 2U);
                    Phase = 5;
                    bb1.sprite6_y = ymap;
                }
            }
        }
        if (obj->main_etat == 1)
        {
            if (
                !(block_flags [
                    (u16) mp.map [
                        (s16) (((obj->x_pos + obj->offset_bx + (!(obj->flags & 0x4000) ? -0x10 : 0x10)) >> 4) + mp.width * ((obj->y_pos + obj->offset_by + 8) >> 4))
                    ] >> 10
                ] >> 1 & 1)
            )
            {
                obj->speed_y = 0;
                obj->speed_x = 0;
                /* see also: makeUturn() case TYPE_SPIDER_PLAFOND */
                obj->flags = obj->flags & ~0x4000 | (((1 - ((obj->flags >> 0xE) & 1)) & 1) << 0xE);
                set_main_and_sub_etat(obj, 0U, 5U);
            }
        }
        if ((temp_s2 - (ray_zdc_x + ((s16) ray_zdc_w >> 1))) >= 0)
        {
            if ((temp_s2 - (ray_zdc_x + ((s16) ray_zdc_w >> 1))) >= 0xFB)
            {
                goto block_172;
            }
            return;
        }
        if (((ray_zdc_x + ((s16) ray_zdc_w >> 1)) - temp_s2) >= 0xFB)
        {
block_172:
            obj->flags &= ~0x400;
            IsBossThere = 0;
            Phase = 0;
            scroll_end_x = xmapmax;
            scroll_end_y = ymapmax;
            obj->flags &= ~0x800;
        }
        break;
    case 5:
        if (bb1.field1_0x2 < 0)
        {
            scroll_end_y = bb1.sprite6_y - horloge[5];
            bb1.field1_0x2 = bb1.field1_0x2 + 1;
        }
        if (FinAnim != 0)
        {
            if (obj->main_etat == 0)
            {
                if (obj->sub_etat == 5)
                {
                    do { } while (0); /* TODO: ??? */
                    bb1.speed_x = 3;
                    test_123098(obj);
                }
                goto block_147;
            }
        }
        else
        {
block_147:
            if ((obj->main_etat == 0) && (obj->sub_etat == 2))
            {
                if (FinAnim != 0)
                {
                    bb1.speed_x = 2;
                    test_123098(obj);
                }
                else
                {
                    /* already knows main_etat and sub_etat ... */
                    if ((obj->anim_frame == 0x15) && (horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0))
                    {
                        bb1.field1_0x2 = -0x001E;
                    }
                }
            }
        }
        if (obj->main_etat == 1)
        {
            if (
                !(block_flags [
                    (u16) mp.map [
                        (s16) (((obj->x_pos + obj->offset_bx + (!(obj->flags & 0x4000) ? -0x10 : 0x10)) >> 4) + mp.width * ((obj->y_pos + obj->offset_by + 8) >> 4))
                    ] >> 10
                ] >> 1 & 1)
            )
            {
                if (bb1.speed_x == 3)
                {
                    set_main_and_sub_etat(obj, 2U, 4U);
                    obj->gravity_value_2 = 0xFF;
                    obj->gravity_value_1 = 0;
                    obj->speed_y = -2;
                    obj->speed_x = 4;
                    scroll_end_y = ymapmax;
                    scroll_end_x = xmapmax;
                }
                else
                {
                    obj->speed_y = 0;
                    obj->speed_x = 0;
                    obj->flags = obj->flags & ~0x4000 | (((1 - ((obj->flags >> 0xE) & 1)) & 1) << 0xE);
                    set_main_and_sub_etat(obj, 0U, 5U);
                }
            }
        }
        if ((temp_s2 - (ray_zdc_x + ((s16) ray_zdc_w >> 1))) >= 0)
        {
            if ((temp_s2 - (ray_zdc_x + ((s16) ray_zdc_w >> 1))) >= 0x191)
            {
                goto block_173;
            }
            return;
        }
        if (((ray_zdc_x + ((s16) ray_zdc_w >> 1)) - temp_s2) >= 0x191)
        {
block_173:
            obj->flags &= ~0x400;
            IsBossThere = 0;
            Phase = 0;
            scroll_end_x = xmapmax;
            scroll_end_y = ymapmax;
            obj->flags &= ~0x800;
        }
        break;
    }
}
#endif

/* 5B388 8017FB88 -O2 -msoft-float */
void DO_BBMONT2_MARCHE(s16 hp)
{
    bb1.speed_x = hp;
}

/* 5B398 8017FB98 -O2 -msoft-float */
/*? recale_position();
? set_main_and_sub_etat(Obj *, ?, ?);
? set_sub_etat(Obj *, ?);*/

void DO_BBMONT2_ATTER(Obj *obj)
{
    if (obj->speed_y >= 2)
    {
        obj->speed_y = 0;
        obj->speed_x = 0;
        recale_position(obj);
        switch (Phase)
        {
        case 0:
            set_sub_etat(obj, 2);
            break;
        case 1:
            switch (bb1.speed_x)
            {
            case 2:
                set_main_and_sub_etat(obj, 1, 1);
                break;
            case 3:
                set_main_and_sub_etat(obj, 1, 2);
                break;
            case 0:
            default:
                set_main_and_sub_etat(obj, 1, 0);
                break;
            }
            Phase = 2;
            obj->speed_x = bb1.speed_x;
            break;
        case 2:
            set_sub_etat(obj, 2);
            Phase = 3;
            obj->x_pos -= 32;
            bb1.speed_x = -1;
            obj->field23_0x3c = 0;
            break;
        case 3:
            bb1.field1_0x2 += 1;
            obj->gravity_value_2 = 5;
            obj->gravity_value_1 = 0;
            obj->speed_x = 2;
            set_sub_etat(obj, 2);
            obj->speed_x = 0;
            bb1.sprite6_y = 691;
            bb1.sprite6_x = 0;
            scroll_end_y = ymap;
            if (ymap < 691)
            {
                scroll_end_y = 691;
            }
            Phase = 4;
            obj->speed_y = 0;
            break;
        }
    }
}

/* 5B568 8017FD68 -O2 -msoft-float */
/*? CALC_MOV_ON_BLOC(Obj *);
? SET_X_SPEED(Obj *);
? set_main_and_sub_etat(Obj *, ?, ?);
extern s32 D_801F4438;*/

void DO_BBMONT3_COMMAND(Obj *obj)
{
    u8 eight;

    if (
        obj->anim_frame == (obj->animations[obj->anim_index].frames_count - 1) &&
        horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0
    )
        FinAnim = true;
    else
        FinAnim = false;

    if (obj->main_etat == 1)
    {
        SET_X_SPEED(obj);
        CALC_MOV_ON_BLOC(obj);
        if (FinAnim && (bb1.speed_x != obj->sub_etat + 1))
        {
            switch (bb1.speed_x)
            {
            case 2:
                set_main_and_sub_etat(obj, 1, 1);
                break;
            case 3:
                set_main_and_sub_etat(obj, 1, 2);
                break;
            case 0:
            default:
                set_main_and_sub_etat(obj, 1, 0);
                break;
            }
        }
    }
    switch (Phase)
    {
    case 0:
        obj->flags &= ~FLG(OBJ_FLIP_X);
        if (obj->main_etat != 2)
            CALC_MOV_ON_BLOC(obj);

        if (FinAnim && obj->main_etat == 0)
        {
            bb1.speed_x = 2;
            set_main_and_sub_etat(obj, 1, 1);
        }
        eight = 8;
        if (
            (obj->main_etat == 1) &&
            ((block_flags
                [
                    mp.map[
                        (s16)(((obj->x_pos + (obj->offset_bx - eight)) >> 4) +
                        mp.width * ((obj->y_pos + obj->offset_by + eight) >> 4))
                    ] >> 10
                ] >> 1 & 1) == 0
            )
        )
        {
            set_main_and_sub_etat(obj, 2, 4);
            obj->gravity_value_2 = 5;
            obj->gravity_value_1 = 0;
            obj->speed_y = -8;
            obj->speed_x = -2;
        }
        break;
    case 1:
        if (
            (obj->main_etat == 1) &&
            ((block_flags
                [
                    mp.map[
                        (s16)(((obj->x_pos + (obj->offset_bx)) >> 4) +
                        mp.width * ((obj->y_pos + obj->offset_by + 8) >> 4))
                    ] >> 10
                ] >> 1 & 1) == 0
            )
        )
        {
            set_main_and_sub_etat(obj, 0, 1);
            obj->speed_y = 0;
            obj->speed_x = 0;
            Phase = 2;
        }
        break;
    }
}

/* 5B8C0 801800C0 -O2 -msoft-float */
/*? CALC_MOV_ON_BLOC();
? set_main_and_sub_etat(Obj *, ?, ?);*/

void DO_BBMONT3_ATTER(Obj *obj)
{
    if (obj->speed_y >= 2)
    {
        obj->speed_y = 0;
        obj->speed_x = 0;
        CALC_MOV_ON_BLOC(obj);
        if (Phase == 0)
        {
            switch (bb1.speed_x)
            {
            case 2:
                set_main_and_sub_etat(obj, 1, 1);
                break;
            case 3:
                set_main_and_sub_etat(obj, 1, 2);
                break;
            case 0:
            default:
                set_main_and_sub_etat(obj, 1, 0);
                break;
            }
            Phase = 1;
        }
    }
}

/* 5B984 80180184 -O2 -msoft-float */
/*? set_sub_etat(Obj *, ?);*/

void DO_BBMONT4_COMMAND(Obj *obj)
{
    obj->flags |= FLG(OBJ_FLIP_X);
    if (
        obj->anim_frame == (obj->animations[obj->anim_index].frames_count - 1) &&
        horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0
    )
        FinAnim = true;
    else
        FinAnim = false;

    if (obj->main_etat == 0)
    {
        if (
            obj->sub_etat == 7 &&
            obj->anim_frame == 0x2C &&
            horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xf] == 0
        )
            BBMONT_ETINCELLES(obj);
        if (FinAnim && obj->sub_etat == 0)
            set_sub_etat(obj, 7);
    }
}
