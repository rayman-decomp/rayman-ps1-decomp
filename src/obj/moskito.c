#include "obj/moskito.h"

#ifdef BSS_DEFS
u8 fistAvoided;
u8 mstMustLeaveScreenToProceed;
#endif

/* 6F914 80194114 -O2 -msoft-float */
void getIdealStingCoords(Obj *obj, s16 *out_x, s16 *out_y)
{
    s16 x;
    s16 calc_y;
    s16 calc_x;

    x = ray_zdc_x;
    calc_y = ray_zdc_y + (ray_zdc_h >> 1);
    calc_x = x + (ray_zdc_w >> 1) - obj->offset_bx;
    *out_x = calc_x;
    if (obj->flags & FLG(OBJ_FLIP_X))
        calc_x -= 48;
    else
        calc_x += 48;
    *out_x = calc_x;
    *out_y = calc_y - 112;
}

/* 6F988 80194188 -O2 -msoft-float */
u8 closeEnoughToSting(Obj *obj, u16 min_x, u16 min_y)
{
    s16 sting_x; s16 sting_y;

    getIdealStingCoords(obj, &sting_x, &sting_y);
    sting_x = __builtin_abs((s16) (sting_x - obj->x_pos));
    sting_y = __builtin_abs((s16) (sting_y - obj->y_pos));
    if (sting_x < min_x && sting_y < min_y)
        return true;
    else
        return false;
}

/* 6FA3C 8019423C -O2 -msoft-float */
/*s16 firstFloorBelow();*/

void PS1_setBossScrollLimits_moskito(Obj *obj)
{
    s16 x;

    x = obj->offset_bx + obj->init_x_pos - 272;
    bossScrollStartX = x;
    bossScrollEndX = x;

    floorLine = firstFloorBelow(obj);
    bossScrollStartY = floorLine - 256;
    bossScrollEndY = floorLine - 176;

    if (bossScrollStartX < 0)
        bossScrollStartX = 0;
    if (bossScrollStartX > xmapmax)
        bossScrollStartX = xmapmax;
    if (bossScrollEndX < 0)
        bossScrollEndX = 0;
    if (bossScrollEndX > xmapmax)
        bossScrollEndX = xmapmax;
    if (bossScrollStartY < 0)
        bossScrollStartY = 0;
    if (bossScrollStartY > ymapmax)
        bossScrollStartY = ymapmax;
    if (bossScrollEndY < 0)
        bossScrollEndY = 0;
    if (bossScrollEndY > ymapmax)
        bossScrollEndY = ymapmax;
}

/* 6FB88 80194388 -O2 -msoft-float */
u8 moskitoCanAttak(Obj *obj)
{
    u8 locked;
    u32 res;

    if (!scrollLocked)
    {
        locked = false;
        if (
            xmap >= bossScrollStartX - h_scroll_speed &&
            xmap <= bossScrollEndX + h_scroll_speed &&
            ymap >= bossScrollStartY - v_scroll_speed
        )
            locked = (ymap <= bossScrollEndY + v_scroll_speed);
        scrollLocked = locked;

        if (scrollLocked)
        {
            scroll_start_x = bossScrollStartX;
            scroll_end_x = bossScrollEndX;
            scroll_start_y = bossScrollStartY;
            scroll_end_y = bossScrollEndY;
        }
    }
    else if (obj->timer != 0)
        obj->timer--;
    res = false;
    if (scrollLocked)
        res = (obj->timer == 0);
    return res;
}

/* 6FCCC 801944CC -O2 -msoft-float */
/* param_2 is some moskito obj flag */
s16 setMoskitoAtScrollBorder(Obj *obj, u8 param_2)
{
    s32 width;
    s16 res;

    width = SCREEN_WIDTH;
    switch (param_2)
    {
    case 0:
        res = -1;
        obj->x_pos = scroll_start_x - obj->offset_bx;
        obj->flags &= ~FLG(OBJ_FLIP_X);
        break;
    case 1:
        res = 1;
        obj->x_pos = scroll_end_x - (obj->offset_bx - width);
        obj->flags |= FLG(OBJ_FLIP_X);
        break;
    default:
        res = obj->offset_bx + obj->x_pos - ((scroll_start_x + scroll_end_x + SCREEN_WIDTH) / 2);
        if (res >= 1)
        {
            obj->x_pos = scroll_end_x - (obj->offset_bx - width);
            obj->flags &= ~FLG(OBJ_FLIP_X);
        }
        else
        {
            obj->x_pos = scroll_start_x - obj->offset_bx;
            obj->flags |= FLG(OBJ_FLIP_X);
        }
        break;
    }
    return res;
}

/* 6FDC8 801945C8 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/moskito", prepareNewMoskitoAttack);
#else
/* many heads were scratched that day */
void prepareNewMoskitoAttack(Obj *mst_obj)
{
    Obj *cur_obj;
    s16 i;
    s16 prev_flip_x;
    s32 temp_s0_2;
    s16 unk_2;
    u32 unk_1;
    u8 curAct_tmp_1;
    u8 nb_obj;
    s32 half_wid;

    unk_1 = scroll_start_x + scroll_end_x + SCREEN_WIDTH;
    unk_2 = (unk_1 + (unk_1 >> 31)) >> 1;
    while (currentBossActionIsOver)
    {
        curAct = moskitoActionSequences[bossEncounter][currentBossAction++];
        alternateBossSpeedFactor = 0;
        switch (curAct)
        {
        case 3:
            bossEncounter++;
        case 2:
            currentBossAction = 0;
            currentBossActionIsOver = true;
            break;
        case 5:
            bossEncounter = saveBossEncounter;
            currentBossAction = saveCurrentBossAction;
            curAct = moskitoActionSequences[bossEncounter][currentBossAction];
            if (curAct == 26 || curAct == 14)
            {
                while (curAct == 26 || curAct == 14)
                    curAct = moskitoActionSequences[bossEncounter][++currentBossAction];
            }
            else if (curAct == 18 || curAct == 19 || (curAct == 21))
            {
                if (curAct == 21)
                    currentBossAction++;

                curAct = moskitoActionSequences[bossEncounter][++currentBossAction];
                while (curAct == 20 || curAct == 21)
                {
                    if (curAct == 21)
                        currentBossAction++;

                    curAct = moskitoActionSequences[bossEncounter][++currentBossAction];
                }
            }
            saveBossEncounter = 0xFF;
            currentBossActionIsOver = true;
            mstMustLeaveScreenToProceed = false;
            break;
        case 12:
            curAct_tmp_1 = moskitoActionSequences[bossEncounter][currentBossAction++];
            currentBossAction = 0;
            if (curAct_tmp_1 == bossEncounter)
                bossEncounter++;
            else
                bossEncounter = curAct_tmp_1;

            currentBossActionIsOver = false;
            break;
        case 25:
            if (mst_obj->init_hit_points == 5)
            {
                ChangeLevel();
                finBosslevel.bzzit = true;
            }
            else
            {
                remoteRayXToReach = -32000;
                finBosslevel.moskito = true;
                set_main_and_sub_etat(&ray, 3, 52);
                mst_obj->nb_cmd = vblToEOA(&ray, 1) + 1;
                fin_boss = true;
            }
            currentBossActionIsOver = false;
            break;
        case 22:
            if (mst_obj->init_hit_points == 12)
                set_main_and_sub_etat(mst_obj, 0, 19);
            else
            {
                i = 0;
                cur_obj = &level.objects[i];
                nb_obj = level.nb_objects;
                while (i < nb_obj)
                {
                    if (cur_obj->type == TYPE_MST_COPAIN)
                    {
                        mst_obj->sprites = cur_obj->sprites;
                        mst_obj->animations = cur_obj->animations;
                        mst_obj->img_buffer = cur_obj->img_buffer;
                        mst_obj->eta = cur_obj->eta;
                        mst_obj->main_etat = cur_obj->main_etat;
                        mst_obj->sub_etat = cur_obj->sub_etat;
                        mst_obj->anim_index = cur_obj->anim_index;
                        mst_obj->anim_frame = 0;
                        mst_obj->offset_by += 4;
                        mst_obj->flags &= ~FLG(OBJ_FLIP_X);

                        ray.flags &= ~FLG(OBJ_ACTIVE);
                        break;
                    }
                    i++;
                    cur_obj++;
                }
            }
            skipToLabel(mst_obj, 1, true);
            currentBossActionIsOver = false;
            mst_obj->nb_cmd += 128;
            break;
        case 24:
            if (mst_obj->init_hit_points == 12)
                mst_obj->offset_by += SCREEN_HEIGHT;

            mst_obj->flags &= ~FLG(OBJ_FLIP_X);
            bossXToReach =
            mst_obj->x_pos =
                scroll_start_x - (mst_obj->offset_bx - SCREEN_WIDTH / 2);
            bossYToReach = floorLine - mst_obj->offset_by;
            set_main_and_sub_etat(mst_obj, 2, 1);
            skipToLabel(mst_obj, 2, true);
            bossReachingAccuracyX = 0xFF;
            bossReachingAccuracyY = 0;
            bossReachingTimer = 1;
            currentBossActionIsOver = false;
            break;
        case 17:
            half_wid = SCREEN_WIDTH / 2; /* TODO: ??? */
            bossXToReach = scroll_start_x - (mst_obj->offset_bx - half_wid);
            bossYToReach = floorLine - 230;
            set_main_and_sub_etat(mst_obj, 0, 6);
            skipToLabel(mst_obj, 2, true);
            bossReachingAccuracyX = 0xFF;
            bossReachingAccuracyY = 0xFF;
            bossReachingTimer = 1;
            setBossReachingSpeeds(mst_obj, 1, 0xFF, 0xFF);
            currentBossActionIsOver = false;
            break;
        case 16:
            set_main_and_sub_etat(mst_obj, 0, 5);
            skipToLabel(mst_obj, 1, true);
            currentBossActionIsOver = false;
            break;
        case 6:
            set_main_and_sub_etat(mst_obj, 0, 13);
            skipToLabel(mst_obj, 1, true);
            currentBossActionIsOver = false;
            break;
        case 26:
            /* TODO: temp_s0_2? */
            temp_s0_2 = mst_obj->main_etat == 0;
            if (temp_s0_2 && mst_obj->sub_etat == 0x14)
            {
                calc_obj_dir(mst_obj);
                set_main_and_sub_etat(mst_obj, 0, 0x15);
                skipToLabel(mst_obj, 1, true);
                currentBossActionIsOver = false;
            }
            else
            {
                prev_flip_x = mst_obj->flags >> OBJ_FLIP_X & 1;
                calc_obj_dir(mst_obj);
                if ((mst_obj->flags >> OBJ_FLIP_X & 1) != prev_flip_x)
                {
                    mst_obj->flags = mst_obj->flags & ~FLG(OBJ_FLIP_X) | prev_flip_x << OBJ_FLIP_X;
                    set_main_and_sub_etat(mst_obj, 0, 0x15);
                    temp_s0_2 = vblToEOA(mst_obj, 1);
                    set_main_and_sub_etat(mst_obj, 0, 0x16);
                    skipToLabel(mst_obj, 1, true);
                    currentBossActionIsOver = false;
                    mst_obj->nb_cmd = temp_s0_2 + mst_obj->nb_cmd;
                }
            }
            break;
        case 23:
            remoteRayXToReach = scroll_start_x - mst_obj->offset_bx + 112;
            if (ray.x_pos & 1) /* ??? */
                remoteRayXToReach |= 1;
            else
                remoteRayXToReach &= ~1;
            goto block_52;
        case 11:
            bossSafeTimer = 0;
            mst_obj->display_prio = 3;
            if (mstMustLeaveScreenToProceed == 0)
            {
                /* TODO: this control flow is extra weird? */
                currentBossActionIsOver = true;
            }
            else
            {
                mstMustLeaveScreenToProceed = 0;
                curAct = 4;
                goto block_52;
            }
            break;
        case 4:
block_52:
            bossXToReach = mst_obj->x_pos;
            bossYToReach = scroll_start_y - 128;
            if (curAct == 4)
                set_main_and_sub_etat(mst_obj, 0, 8);
            else
                set_main_and_sub_etat(mst_obj, 0, 6);

            bossReachingAccuracyX = 0xFF;
            bossReachingAccuracyY = 0xFF;
            bossReachingTimer = 1;
            setBossReachingSpeeds(mst_obj, 1, 0xFF, 0xFF);
            skipToLabel(mst_obj, 2, true);
            currentBossActionIsOver = false;
            break;
        case 15:
            set_main_and_sub_etat(mst_obj, 0, 20);
            skipToLabel(mst_obj, 1, true);
            currentBossActionIsOver = false;
            break;
        case 14:
            set_main_and_sub_etat(mst_obj, 0, 15);
            skipToLabel(mst_obj, 1, true);
            currentBossActionIsOver = false;
            break;
        case 10:
            calc_obj_dir(mst_obj);
            setMoskitoAtScrollBorder(mst_obj, (mst_obj->flags >> OBJ_FLIP_X ^ 1) & 1);
            mst_obj->y_pos = scroll_start_y - 128;
            if (mst_obj->flags & FLG(OBJ_FLIP_X))
            {
                mst_obj->x_pos -= 48;
                mst_obj->flags &= ~FLG(OBJ_FLIP_X);
            }
            else
            {
                mst_obj->x_pos += 48;
                mst_obj->flags |= FLG(OBJ_FLIP_X);
            }
        case 13:
            fistAvoided = false;
            prev_flip_x = mst_obj->flags >> OBJ_FLIP_X & 1;
            calc_obj_dir(mst_obj);
            getIdealStingCoords(mst_obj, &bossXToReach, &bossYToReach);
            set_main_and_sub_etat(mst_obj, 0, 8);
            bossReachingAccuracyX = 16;
            bossReachingAccuracyY = 16;
            bossReachingTimer = 2;
            setBossReachingSpeeds(mst_obj, 1, 0xFF, 0xFF);
            if (curAct == 13)
                mst_obj->speed_y = -64;
            else
                mst_obj->speed_x = 0;

            mst_obj->flags = mst_obj->flags & ~FLG(OBJ_FLIP_X) | prev_flip_x << OBJ_FLIP_X;
            skipToLabel(mst_obj, 2, true);
            currentBossActionIsOver = false;
            break;
        case 7:
            set_main_and_sub_etat(mst_obj, 0, 12);
        case 8:
            if (curAct == 8)
                set_main_and_sub_etat(mst_obj, 0, 11);

            if (setMoskitoAtScrollBorder(mst_obj, 2) > 0)
            {
                mst_obj->flags &= ~FLG(OBJ_FLIP_X);
                mst_obj->x_pos += 48;
                bossXToReach = scroll_start_x - mst_obj->offset_bx - 48;
            }
            else
            {
                mst_obj->flags |= FLG(OBJ_FLIP_X);
                mst_obj->x_pos -= 48;
                bossXToReach = scroll_end_x - mst_obj->offset_bx + 368;
            }
            bossYToReach =
            mst_obj->y_pos =
                floorLine - 230;
            alternateBossSpeedFactor = moskitoActionSequences[bossEncounter][currentBossAction++] << 10;
            bossReachingAccuracyX = 0xFF;
            bossReachingAccuracyY = 0xFF;
            bossReachingTimer = 1;
            setBossReachingSpeeds(mst_obj, 1, 0xFF, 0xFF);
            skipToLabel(mst_obj, 2, true);
            currentBossActionIsOver = false;
            break;
        case 9:
            set_main_and_sub_etat(mst_obj, 0, 9);
            if (setMoskitoAtScrollBorder(mst_obj, 2) > 0)
            {
                mst_obj->flags &= ~FLG(OBJ_FLIP_X);
                mst_obj->x_pos += 80;
                bossXToReach = scroll_start_x - mst_obj->offset_bx - 80;
            }
            else
            {
                mst_obj->flags |= FLG(OBJ_FLIP_X);
                mst_obj->x_pos -= 96;
                bossXToReach = scroll_end_x - mst_obj->offset_bx + 384;
            }
            bossYToReach =
            mst_obj->y_pos =
                floorLine - 180;
            alternateBossSpeedFactor = moskitoActionSequences[bossEncounter][currentBossAction++] << 10;
            bossReachingAccuracyX = 0xFF;
            bossReachingAccuracyY = 0xFF;
            bossReachingTimer = 1;
            setBossReachingSpeeds(mst_obj, 1, 0xFF, 0xFF);
            skipToLabel(mst_obj, 2, true);
            currentBossActionIsOver = false;
            break;
        case 18:
        case 19:
            mst_obj->y_pos = floorLine - 72;
            if (curAct == 19)
                mst_obj->y_pos = floorLine - 120;

            if (setMoskitoAtScrollBorder(mst_obj, 2) > 0)
            {
                mst_obj->flags &= ~FLG(OBJ_FLIP_X);
                mst_obj->x_pos += 68;
                bossXToReach = mst_obj->x_pos - 24;
            }
            else
            {
                mst_obj->flags |= FLG(OBJ_FLIP_X);
                mst_obj->x_pos -= 76;
                bossXToReach = mst_obj->x_pos + 16;
            }

            set_main_and_sub_etat(mst_obj, 0, 14);
            bossReachingAccuracyX = 0xFF;
            bossReachingAccuracyY = 0xFF;
            bossReachingTimer = 1;
            bossYToReach = mst_obj->y_pos;
            setBossReachingSpeeds(mst_obj, 1, 0xFF, 0xFF);
            skipToLabel(mst_obj, 2, true);
            currentBossActionIsOver = false;
            break;
        case 21:
            set_main_and_sub_etat(mst_obj, 0, 14);
            skipToLabel(mst_obj, 1, true);
            mst_obj->nb_cmd *= moskitoActionSequences[bossEncounter][currentBossAction++];
            currentBossActionIsOver = false;
            break;
        case 20:
            if (mst_obj->x_pos + mst_obj->offset_bx > unk_2)
            {
                mst_obj->flags &= ~FLG(OBJ_FLIP_X);
                bossXToReach = scroll_start_x - mst_obj->offset_bx - 56;
            }
            else
            {
                mst_obj->flags |= FLG(OBJ_FLIP_X);
                bossXToReach = scroll_end_x - mst_obj->offset_bx + 368;
            }

            bossYToReach = mst_obj->y_pos;
            set_main_and_sub_etat(mst_obj, 0, 4);
            skipToLabel(mst_obj, 2, true);
            bossReachingAccuracyX = 0xFF;
            bossReachingAccuracyY = 0xFF;
            bossReachingTimer = 1;
            setBossReachingSpeeds(mst_obj, 1, 0xFF, 0xFF);
            currentBossActionIsOver = false;
            break;
        }
    }
}
#endif

/* 70C64 80195464 -O2 -msoft-float */
Obj *allocateMoskitoFruit(Obj *mst2_obj)
{
    u8 spr_ind;
    ObjType type_check;
    s16 i;
    Obj *cur_obj;
    s16 nb_objs;
    ObjType cur_obj_type;
    s16 unk_x; s16 unk_y; s16 unk_w; s16 unk_h;
    Obj *res = null;

    switch (mst2_obj->sub_etat)
    {
    case 12:
        spr_ind = 3;
        type_check = TYPE_MST_FRUIT1;
        break;
    case 11:
        spr_ind = 3;
        type_check = TYPE_MST_FRUIT2;
        break;
    }

    i = 0;
    cur_obj = &level.objects[i];
    nb_objs = level.nb_objects;
    while (i < (nb_objs))
    {
        cur_obj_type = cur_obj->type;
        if (cur_obj_type == type_check && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            GET_SPRITE_POS(mst2_obj, spr_ind, &unk_x, &unk_y, &unk_w, &unk_h);
            cur_obj->x_pos = unk_x - cur_obj->offset_bx + (unk_w >> 1);
            cur_obj->y_pos = unk_y - cur_obj->offset_hy;
            cur_obj->init_x_pos = cur_obj->x_pos;
            cur_obj->init_y_pos = cur_obj->y_pos;
            switch (cur_obj_type)
            {
            case TYPE_MST_FRUIT1:
                cur_obj->field23_0x3c = 1;
                cur_obj->speed_x = 0;
                break;
            case TYPE_MST_FRUIT2:
                cur_obj->field23_0x3c = 3;
                cur_obj->speed_x = mst2_obj->speed_x;
                break;
            }
            cur_obj->speed_y = 0;
            cur_obj->anim_index = cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].anim_index;
            cur_obj->anim_frame = 0;
            calc_obj_pos_map(cur_obj);
            cur_obj->gravity_value_1 = 0;
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            cur_obj->flags = (cur_obj->flags & ~FLG(OBJ_FLIP_X)) | (mst2_obj->flags & FLG(OBJ_FLIP_X));
            cur_obj->flags &= ~FLG(OBJ_FLAG_9);
            res = cur_obj;
            break;
        }
        cur_obj++;
        i++;
    }

    return res;
}

/* 70E50 80195650 -O2 -msoft-float */
void moskitoDropFruitOnRay(Obj *obj)
{
    s16 x_1;
    s16 x_2;
    u8 sub_etat;
    s32 speed_x;
    s16 y_1;
    s16 cen_x;
    s16 cen_y;
    s16 unk_1;
    s32 unk_2;
    s16 unk_3;
    s16 unk_4;

    x_1 = obj->offset_bx + obj->x_pos;
    x_2 = x_1;
    sub_etat = obj->sub_etat;
    if (sub_etat != 11)
    {
        if (sub_etat == 12)
        {
            speed_x = obj->speed_x;
            if (speed_x < 0)
                speed_x += 7;
            speed_x = speed_x >> 3;
            unk_1 = speed_x;
            /* ??? */
            unk_2 = (s32) (((u32) speed_x >> 31) + speed_x) >> 1;
            x_1 -= unk_2;
        }
    }
    else
    {
        unk_2 = obj->speed_x * 120;
        unk_1 = unk_2 >> 4;
        if (unk_2 < 0)
            unk_1 = (unk_2 + 15) >> 4;
    }

    unk_3 = __builtin_abs(unk_1);
    if (unk_1 < 0)
        x_1 += unk_1;
    y_1 = obj->offset_by + obj->y_pos;
    unk_4 = scroll_end_y - scroll_start_y + 240;
    cen_x = ray_zdc_x + (ray_zdc_w >> 1);
    cen_y = ray_zdc_y + (ray_zdc_h >> 1);
    if (
        scroll_start_x <= x_2 &&
        scroll_end_x + SCREEN_WIDTH >= x_2 &&
        cen_x >= x_1 &&
        cen_y >= y_1 &&
        cen_x <= x_1 + unk_3 &&
        cen_y <= y_1 + unk_4
    )
    {
        allocateMoskitoFruit(obj);
        set_main_and_sub_etat(obj, 0, 16);
        bossYToReach -= 64;
    }
}

/* 71030 80195830 -O2 -msoft-float */
/*? calc_obj_dir(Obj *);
s32 closeEnoughToSting(Obj *, ?, ?);
? moskitoDropFruitOnRay(Obj *);
? prepareNewMoskitoAttack(Obj *);
? setBossReachingSpeeds(Obj *, u8, u8, u8);
? testActionEnd(Obj *);*/

void doMoskitoCommand(Obj *obj)
{
    ObjFlags flags;
    Obj *poing_obj;

    if (moskitoCanAttak(obj))
    {
        if (bossSafeTimer != 0)
            bossSafeTimer--;
        flags = obj->flags;
        if (!(flags & FLG(OBJ_FLAG_0)))
        {
            if (obj->cmd == 2)
            {
                if (PS1_MsAnimIndex == 0x0E && obj->anim_index == 0x0F)
                    obj->flags = flags & ~FLG(OBJ_FLIP_X) | (((flags >> OBJ_FLIP_X ^ 1) & 1) << OBJ_FLIP_X);
                bossXToReach = -32000;
                bossYToReach = -32000;
                obj->speed_x = 0;
                obj->speed_y = 0;
            }
            else
            {
                switch (curAct)
                {
                case 10:
                case 13:
                    calc_obj_dir(obj);
                    getIdealStingCoords(obj, &bossXToReach, &bossYToReach);
                    if (closeEnoughToSting(obj, 24, 24))
                        currentBossActionIsOver = true;
                    /* fall through */
                case 4:
                    if (
                        obj->hit_points < 2 &&
                        poing.is_active &&
                        !fistAvoided &&
                        ModeDemo == 0 &&
                        !record.is_recording
                    )
                    {
                        fistAvoided = true;
                        poing_obj = &level.objects[poing_obj_id];
                        if (
                            obj->y_pos + (obj->offset_by + obj->offset_hy) / 2 >
                            poing_obj->y_pos + (poing_obj->offset_by + poing_obj->offset_hy) / 2
                        )
                            obj->speed_y += 80;
                        else
                            obj->speed_y -= 80;

                        if ((obj->x_pos + obj->offset_bx) > (poing_obj->x_pos + poing_obj->offset_bx))
                            obj->speed_x += 80;
                        else
                            obj->speed_x -= 80;
                    }
                    break;
                }
                setBossReachingSpeeds(obj, bossReachingTimer, bossReachingAccuracyX, bossReachingAccuracyY);
                if (obj->main_etat == 0 && (u8) (obj->sub_etat - 0xB) < 2)
                    moskitoDropFruitOnRay(obj);
            }
            testActionEnd(obj);
        }
        prepareNewMoskitoAttack(obj);
    }
    obj->flags &= ~FLG(OBJ_FLAG_0);
    PS1_MsAnimIndex = obj->anim_index;
}

/* 71330 80195B30 -O2 -msoft-float */
u8 tellNextMoskitoAction(Obj *obj)
{
    u8 *actions;

    if (bossEncounter != 8)
        actions = &moskitoActionSequences[bossEncounter][currentBossAction];
    else
        actions = &moskitoActionSequences[saveBossEncounter][saveCurrentBossAction];

    switch (actions[0])
    {
    case 2:
        return moskitoActionSequences[bossEncounter][0];
    case 3:
        return moskitoActionSequences[bossEncounter + 1][0];
    case 5:
        return moskitoActionSequences[saveBossEncounter][0];
    case 12:
        return moskitoActionSequences[actions[1]][0];
    default:
        return actions[0];
    }
}

/* 7144C 80195C4C -O2 -msoft-float */
void changeMoskitoPhase(Obj *obj)
{
    u8 *enc;
    u8 *act;
    u8 enc_prev;
    u8 hp;

    if (bossEncounter == 8)
    {
        enc = &saveBossEncounter;
        act = &saveCurrentBossAction;
    }
    else
    {
        enc = &bossEncounter;
        act = &currentBossAction;
    }

    enc_prev = *enc;
    if (obj->init_hit_points == 12)
    {
        hp = obj->hit_points;
        if (hp >= 10)
            *enc = 3;
        else if (hp >= 8)
            *enc = 5;
        else if (hp >= 5)
            *enc = 6;
        else if (hp != 0)
            *enc = 7;
        else
        {
            *enc = 9;
            bossSafeTimer = 0;
        }

        if (enc_prev != *enc)
            *act = 0;
    }
}

/* 7151C 80195D1C -O2 -msoft-float */
/*? obj_hurt();*/

void doMoskitoHit(Obj *obj)
{
    s32 act_next;
    s32 act_18;
    u8 hp;
    s32 dividend;
    s32 divisor;

    if (bossSafeTimer == 0)
    {
        poing.damage = 1;
        obj_hurt(obj);
        bossSafeTimer = 0xFF;
        obj->flags |= FLG(OBJ_FLAG_0);
        changeMoskitoPhase(obj);
        act_next = tellNextMoskitoAction(obj);
        act_18 = 18;
        if (
            act_next >= 7 &&
            (act_next <= 10 || (act_next <= 21 && act_next >= act_18))
        )
            mstMustLeaveScreenToProceed = true;

        hp = obj->hit_points;
        if (hp != 0)
        {
            dividend = obj->init_hit_points * 0x1000;
            divisor = hp + obj->init_hit_points;
            bossSpeedFactor = (dividend / divisor) + 0x4000;

            if (bossEncounter != 8)
            {
                saveBossEncounter = bossEncounter;
                saveCurrentBossAction = currentBossAction;
                bossEncounter = 8;
            }
        }
        else
        {
            bossEncounter = 9;
            bossSpeedFactor = 0x4000;
        }
        currentBossAction = 0;
        currentBossActionIsOver = true;
    }
}