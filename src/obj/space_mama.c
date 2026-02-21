#include "obj/space_mama.h"

#ifdef BSS_DEFS
s16 machine_obj_id;
s16 mereDenis_weapon_id;
s16 circleIndex;
s16 circleX;
s16 circleY;
s16 droppedBombIds[8][8];
u8 currentBombSequence;
u8 lastDroppedBombIdInSequence[8];
s16 lastDroppedBombXCenterPos;
u8 currentLaserSize;
u8 currentPhaseHitCounter;
u8 laserSourceSprNumInAnim;
s32 mere_denis_wait_time;
u8 stepsForward;
u8 timerBeforeFirstBomb;
#endif

/* 640F0 801888F0 -O2 -msoft-float */
void findMereDenisWeapon(void)
{
    Obj *cur_obj = &level.objects[0];
    s32 nb_objs = level.nb_objects;
    s16 i = 0;

    mereDenis_weapon_id = -1;
    machine_obj_id = -1;
    while (i < nb_objs)
    {
        if (cur_obj->type == TYPE_SMA_WEAPON)
            mereDenis_weapon_id = i;
        else if (cur_obj->type == TYPE_WASHING_MACHINE)
            machine_obj_id = i;
        cur_obj++;
        i++;
    }
}

/* 64174 80188974 -O2 -msoft-float */
void PS1_setBossScrollLimits_spacemama(Obj *obj)
{
    s16 x; s16 y;

    x = obj->offset_bx + obj->init_x_pos - 220;
    bossScrollEndX = x;
    bossScrollStartX = x;
    y = firstFloorBelow(obj);
    floorLine = y;
    bossScrollStartY = y - 256;
    bossScrollEndY = y - 224;

    MAX_2(bossScrollStartX, 0);
    MIN_2(bossScrollStartX, xmapmax);
    MAX_2(bossScrollEndX, 0);
    MIN_2(bossScrollEndX, xmapmax);
    MAX_2(bossScrollStartY, 0);
    MIN_2(bossScrollStartY, ymapmax);
    MAX_2(bossScrollEndY, 0);
    MIN_2(bossScrollEndY, ymapmax);
}

/* 642C0 80188AC0 -O2 -msoft-float */
u8 mereDenisCanAttak(Obj *obj)
{
    if (!scrollLocked)
    {
        scrollLocked =
            xmap >= bossScrollStartX - h_scroll_speed &&
            xmap <= bossScrollEndX + h_scroll_speed &&
            ymap >= bossScrollStartY - v_scroll_speed &&
            ymap <= bossScrollEndY + v_scroll_speed;
        if (scrollLocked)
        {
            scroll_start_x = bossScrollStartX;
            scroll_end_x = bossScrollEndX;
            scroll_start_y = bossScrollStartY;
            scroll_end_y = bossScrollEndY;
        }
    }
    else if (obj->timer != 0 && horloge[2] == 0)
        obj->timer--;

    return scrollLocked && obj->timer == 0;
}

/* 64418 80188C18 -O2 -msoft-float */
s32 setMereDenisAtScrollBorder(Obj *obj, u8 flip_x)
{
    s32 unk_1;
    s16 res;
    u8 offs_bx;

    unk_1 = SCREEN_WIDTH; /* couldn't remove this */
    switch (flip_x)
    {
    case false:
        res = -1;
        obj->x_pos = scroll_start_x - obj->offset_bx;
        obj->flags |= FLG(OBJ_FLIP_X);
        break;
    case true:
        res = 1;
        obj->x_pos = scroll_end_x - (obj->offset_bx - unk_1);
        obj->flags &= ~FLG(OBJ_FLIP_X);
        break;
    default:
        offs_bx = obj->offset_bx;
        res = offs_bx + obj->x_pos - (scroll_start_x + scroll_end_x + SCREEN_WIDTH) / 2;
        if (res > 0)
        {
            obj->x_pos = scroll_end_x - (offs_bx - unk_1);
            obj->flags &= ~FLG(OBJ_FLIP_X);
        }
        else
        {
            obj->x_pos = scroll_start_x - offs_bx;
            obj->flags |= FLG(OBJ_FLIP_X);
        }
        break;
    }
    return res;
}

/* 64514 80188D14 -O2 -msoft-float */
void setCirclePointToReach(void)
{
    bossXToReach = circleX + sinus(circleIndex) * 100 / 512;
    bossYToReach = circleY + cosinus(circleIndex) * 60 / 512;
    circleIndex += 4;
    if (circleIndex > 512)
        circleIndex = -32000;
}

/* 645F4 80188DF4 -O2 -msoft-float */
void allocateMereDenisBombChips(Obj *bomb_obj)
{
    u8 i;
    Obj *cur_obj;
    s16 j;
    s32 nb_objs;
    u8 unk_1;
    u8 sub_etat_1;
    u8 sub_etat_2;

    for (i = 0; i <= 2; i += 2)
    {
        cur_obj = level.objects;
        j = 0;
        nb_objs = level.nb_objects;
        while (j < nb_objs)
        {
            unk_1 = false;
            switch (bomb_obj->sub_etat)
            {
            case 1:
                sub_etat_1 = 0;
                sub_etat_2 = 1;
                break;
            case 3:
            case 5:
                if (bomb_obj->flags & FLG(OBJ_FLIP_X))
                {
                    sub_etat_1 = 4;
                    sub_etat_2 = 5;
                }
                else
                {
                    sub_etat_1 = 2;
                    sub_etat_2 = 3;
                }
                break;
            case 7:
                if (bomb_obj->flags & FLG(OBJ_FLIP_X))
                    unk_1 = true;
                sub_etat_1 = 6;
                sub_etat_2 = 7;
                break;
            }

            if (
                cur_obj->type == TYPE_SMA_BOMB_CHIP &&
                !(cur_obj->flags & FLG(OBJ_ACTIVE)) &&
                (cur_obj->sub_etat == sub_etat_1 || cur_obj->sub_etat == sub_etat_2)
            )
            {
                cur_obj->flags = (cur_obj->flags & ~FLG(OBJ_FLIP_X) | (bomb_obj->flags & FLG(OBJ_FLIP_X)));
                cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                cur_obj->x_pos = bomb_obj->x_pos;
                cur_obj->y_pos = bomb_obj->y_pos;
                set_main_and_sub_etat(
                    cur_obj, 1, (i == 0 ? sub_etat_1 : sub_etat_2)
                );
                calc_obj_pos_map(cur_obj);
                skipToLabel(
                    cur_obj, (unk_1 ? i == 0 : i != 0), true
                );
                break;
            }
            cur_obj++;
            j++;
        }
    }

    allocateExplosion(bomb_obj);
    PlaySnd(220, bomb_obj->id);
    bomb_obj->flags &= ~FLG(OBJ_ACTIVE);
    bomb_obj->flags &= ~FLG(OBJ_ALIVE);
}

/* 64810 80189010 -O2 -msoft-float */
void mereDenisExplodeBombs(void)
{
    s16 var_t0; s16 var_v0; /* didn't name yet, because dunno which is y, which is x, if it's spatial repr. */
    s16 id;
    Obj *obj;

    for (var_t0 = 0; var_t0 < (s16) LEN(droppedBombIds); var_t0++)
    {
        for (var_v0 = 0; var_v0 < (s16) (LEN(droppedBombIds[var_t0])); var_v0++)
        {
            id = droppedBombIds[var_t0][var_v0];
            if (id != -1)
            {
                obj = &level.objects[id];
                obj->timer = 70;
                droppedBombIds[var_t0][var_v0] = -1;
            }
        }
    }
}

/* 648B4 801890B4 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/space_mama", mereDenisDropBomb);
#else
/* __builtin_abs section */
void mereDenisDropBomb(Obj *smama_obj)
{
    s16 ray_x;
    s16 smama_x_1; s16 smama_x_2;
    Obj *cur_obj;
    s16 j; u8 i;
    s16 nb_objs;
    u8 new_sub_etat;
    u8 new_flip_x;

    if (currentBombSequence == 0xfe && lastDroppedBombXCenterPos == -32000)
    {
        ray_x = ray.x_pos + ray.offset_bx;
        smama_x_1 = smama_obj->x_pos + smama_obj->offset_bx;
        if ((ray_x >= smama_x_1 - 8) && (ray_x <= smama_x_1 + 8))
        {
            cur_obj = level.objects;
            j = 0;
            nb_objs = level.nb_objects;
            while (j < nb_objs)
            {
                if (cur_obj->type == TYPE_SMA_BOMB && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
                {
                    cur_obj->sub_etat = 0;
                    cur_obj->flags &= ~FLG(OBJ_FLIP_X);
                    cur_obj->x_pos = smama_x_1 - cur_obj->offset_bx;
                    cur_obj->y_pos = smama_obj->y_pos + smama_obj->offset_by - cur_obj->offset_by - 33;
                    cur_obj->timer = 50;
                    cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
                    break;
                }
                cur_obj++;
                j++;
            }
            currentBombSequence = 0xff;
            lastDroppedBombXCenterPos = smama_x_1;
        }
    }
    else
    {
        for (i = 0; i < sizeof(lastDroppedBombIdInSequence); i++)
        {
            if (lastDroppedBombIdInSequence[i] == 7)
            {
                currentBombSequence = 0xff;
                lastDroppedBombIdInSequence[i] = 0xff;
                lastDroppedBombXCenterPos = -32000;
            }
            else
            {
                smama_x_2 = smama_obj->x_pos + smama_obj->offset_bx;
                if (i == 0)
                {

                    /* tried __builtin_abs. pc also does abs */
                    #define OPT_2
                    #ifdef OPT_0
                    /* ABS_LT, see DO_POING_COLLISION */
                    if (
                        (smama_x_2 - lastDroppedBombXCenterPos < 0 ? -(smama_x_2 - lastDroppedBombXCenterPos) < 0x25 : (smama_x_2 - lastDroppedBombXCenterPos < 0x25)
                        )
                    )
                        return;
                    #endif
                    #ifdef OPT_1
                    if (__builtin_abs(smama_x_2 - lastDroppedBombXCenterPos) < 0x25)
                    {
                        return;
                    }
                    #endif
                    #ifdef OPT_2
                    if (smama_x_2 - lastDroppedBombXCenterPos < 0)
                    {
                        if (-(smama_x_2 - lastDroppedBombXCenterPos) < 0x25)
                        {
                            return;
                        }
                    }
                    else
                    {
                        if (smama_x_2 - lastDroppedBombXCenterPos < 0x25)
                        {
                            do
                            {
                            } while (0);
                            return;
                        }
                    }
                    #endif
                    #ifdef OPT_3 /* ghidra unmodified */
                    iVar2 = smama_x_2 - lastDroppedBombXCenterPos;
                    if (iVar2 < 0)
                    {
                        iVar2 = lastDroppedBombXCenterPos - smama_x_2;
                    }
                    if (iVar2 < 0x25)
                    {
                        return;
                    }
                    #endif
                }
                lastDroppedBombIdInSequence[i]++;
                switch (bombSequences[currentBombSequence][i][lastDroppedBombIdInSequence[i]])
                {
                case 0:
                case 4:
                    new_sub_etat = 0;
                    new_flip_x = 0;
                    break;
                case 1:
                case 5:
                    new_sub_etat = 2;
                    new_flip_x = smama_obj->flags >> OBJ_FLIP_X & 1;
                    break;
                case 2:
                    new_sub_etat = 6;
                    new_flip_x = smama_obj->flags >> OBJ_FLIP_X & 1;
                    break;
                case 6:
                    new_sub_etat = 6;
                    new_flip_x = (smama_obj->flags >> OBJ_FLIP_X ^ 1) & 1;
                    break;
                case 3:
                case 7:
                    new_sub_etat = 4;
                    new_flip_x = (smama_obj->flags >> OBJ_FLIP_X ^ 1) & 1;
                    break;
                case 8:
                    smama_x_2 = 0;
                    droppedBombIds[i][lastDroppedBombIdInSequence[i]] = -1;
                    break;
                default:
                    break;
                }

                if (smama_x_2 != 0)
                {
                    cur_obj = level.objects;
                    j = 0;
                    nb_objs = level.nb_objects;
                    while (j < nb_objs)
                    {
                        if (cur_obj->type == TYPE_SMA_BOMB && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
                        {
                            cur_obj->sub_etat = new_sub_etat;
                            cur_obj->flags = cur_obj->flags & ~FLG(OBJ_FLIP_X) | (new_flip_x & 1) << OBJ_FLIP_X;
                            droppedBombIds[i][lastDroppedBombIdInSequence[i]] = j;
                            cur_obj->anim_frame = 0;
                            cur_obj->x_pos = smama_x_2 - cur_obj->offset_bx;
                            cur_obj->y_pos = (smama_obj->y_pos + smama_obj->offset_by - cur_obj->offset_by) + (i - 6) * 11;
                            cur_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
                            break;
                        }
                        cur_obj++;
                        j++;
                    }
                    if (j >= nb_objs)
                        droppedBombIds[i][lastDroppedBombIdInSequence[i]] = -1;
                }
                lastDroppedBombXCenterPos = smama_obj->x_pos + smama_obj->offset_bx;
            }
        }
    }
}
#endif

/* 64D48 80189548 -O2 -msoft-float */
void snapWeaponAnimState(Obj *obj, u8 sub_etat)
{
    set_main_and_sub_etat(obj, 0, sub_etat);
    obj->anim_frame = 0;
    obj->anim_index = obj->eta[0][sub_etat].anim_index;
}

/* 64DA0 801895A0 -O2 -msoft-float */
void swapMereDenisCollZones(Obj *obj, u8 smama2)
{
    if (!smama2)
        obj->type = TYPE_SPACE_MAMA;
    else
        obj->type = TYPE_SPACE_MAMA2;

    obj->zdc = type_zdc[obj->type];
}

/* 64DD8 801895D8 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/space_mama", prepareNewMereDenisAttack);
#else
/*
gotos
might have actually written gotos like this?
*/
u8 prepareNewMereDenisAttack(Obj *smama_obj)
{
    u8 cur_act = 0xFF;
    Obj *wep_obj = &level.objects[mereDenis_weapon_id];
    Obj *mach_obj = &level.objects[machine_obj_id];
    Obj *poing_obj;
    s32 old_flip_x;
    s16 i;

    if (circleIndex == -32000)
    {
        while (currentBossActionIsOver)
        {
            cur_act = mereDenisActionSequences[bossEncounter][currentBossAction++];
            switch (cur_act)
            {
            case 0:
                bossEncounter++;
            case 1:
                currentBossAction = 0;
                currentBossActionIsOver = true;
                break;
            case 2:
                currentBossAction = saveCurrentBossAction;
                bossEncounter = saveBossEncounter;
                if (currentBossAction == 0xFF)
                    currentBossAction = saveCurrentBossAction + 1;
                currentBossActionIsOver = true;
                saveBossEncounter = 0xFF;
                break;
            case 46:
                remoteRayXToReach = -32000;
                fin_boss = true;
                smama_obj->nb_cmd = vblToEOA(smama_obj, 1) - 4;
                currentBossActionIsOver = false;
                break;
            case 42:
                set_main_and_sub_etat(smama_obj, 0, 3);
                remoteRayXToReach = ray.x_pos;
                skipToLabel(smama_obj, 0, true);
                smama_obj->nb_cmd = 0;
                fin_boss = true;
                currentBossActionIsOver = true;
                break;
            case 44:
                switch (mach_obj->sub_etat)
                {
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                    set_main_and_sub_etat(smama_obj, 0, 16);
                    snapWeaponAnimState(wep_obj, 43);
                    set_sub_etat(mach_obj, mach_obj->sub_etat + 1);
                    skipToLabel(smama_obj, 0, true);
                    mach_obj->x_pos = smama_obj->x_pos;
                    mach_obj->y_pos = smama_obj->y_pos;
                    mach_obj->anim_frame = 0;
                    currentBossActionIsOver = false;
                    break;
                case 42:
                    wep_obj->flags &= ~FLG(OBJ_ALIVE);
                    currentBossAction = 0;
                    bossEncounter = 6;
                    currentBossActionIsOver = true;
                    mach_obj->flags &= ~FLG(OBJ_ALIVE);
                    break;
                }
                laserSourceSprNumInAnim = 0xFF;
                break;
            case 40:
                poing_obj = &level.objects[poing_obj_id];
                set_main_and_sub_etat(smama_obj, 0, 2);
                bossYToReach = smama_obj->y_pos;
                if (poing_obj->speed_x != 0) /* couldn't make this a var */
                {
                    skipToLabel(smama_obj, 0, true);
                    bossXToReach = smama_obj->eta[0][2].speed_x_right * smama_obj->nb_cmd / 16;
                    if (poing_obj->speed_x < 0)
                        bossXToReach = smama_obj->x_pos + bossXToReach;
                    else if (poing_obj->speed_x > 0)
                        bossXToReach = smama_obj->x_pos - bossXToReach;

                    bossReachingAccuracyX = 0xFF;
                    bossReachingAccuracyY = 0xFF;
                    bossReachingTimer = 1;
                    setBossReachingSpeeds(smama_obj, 1, 0xFF, 0xFF);
                    skipToLabel(smama_obj, 1, true);
                }
                else
                    skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 5:
                fix_numlevel(smama_obj);
                new_level = true;
                currentBossActionIsOver = false;
                finBosslevel.space_mama = true;
                break;
            case 41:
                old_flip_x = smama_obj->flags >> OBJ_FLIP_X & 1;
                calc_obj_dir(smama_obj);
                if ((smama_obj->flags >> OBJ_FLIP_X & 1) != old_flip_x)
                {
                    set_main_and_sub_etat(smama_obj, 0, 4);
                    skipToLabel(smama_obj, 0, true);
                    currentBossActionIsOver = false;
                }
                else
                    currentBossActionIsOver = true;
                break;
            case 7:
                stepsForward = 0;
                currentPhaseHitCounter = 0;
                smama_obj->display_prio = 3;
                swapMereDenisCollZones(smama_obj, true);
                set_main_and_sub_etat(smama_obj, 0, 44);
                setMereDenisAtScrollBorder(smama_obj, 0);
                smama_obj->flags &= ~FLG(OBJ_FLIP_X);
                smama_obj->x_pos = smama_obj->x_pos - 144;
                smama_obj->y_pos = (floorLine - smama_obj->offset_by) - 32;
                bossXToReach = (scroll_start_x - smama_obj->offset_bx) + 50;
                bossYToReach = smama_obj->y_pos;
                bossReachingTimer = 1;
                bossReachingAccuracyX = 0xFF;
                bossReachingAccuracyY = 0xFF;
                setBossReachingSpeeds(smama_obj, 1, 0xFF, 0xFF);
                skipToLabel(smama_obj, 1, true);
                currentBossActionIsOver = false;
                break;
            case 8:
                swapMereDenisCollZones(smama_obj, true);
                circleIndex = 4;
                circleX = smama_obj->x_pos;
                circleY = smama_obj->y_pos - 60;
                setCirclePointToReach();
                setBossReachingSpeeds(smama_obj, 1, 0xFF, 0xFF);
                bossReachingTimer = 1;
                bossReachingAccuracyX = 0xFF;
                bossReachingAccuracyY = 0xFF;
                skipToLabel(smama_obj, 1, true);
                currentBossActionIsOver = false;
                break;
            case 12:
                swapMereDenisCollZones(smama_obj, true);
                bossXToReach = smama_obj->x_pos + 110;
                bossYToReach = (floorLine - smama_obj->offset_by) - 124;
                bossReachingTimer = 1;
                bossReachingAccuracyX = 0xFF;
                bossReachingAccuracyY = 0xFF;
                setBossReachingSpeeds(smama_obj, 1, 0xFF, 0xFF);
                skipToLabel(smama_obj, 1, true);
                currentBossActionIsOver = false;
                break;
            case 38:
                swapMereDenisCollZones(smama_obj, true);
                set_main_and_sub_etat(smama_obj, 2, 1);
                bossYToReach = floorLine - smama_obj->offset_by;
                bossXToReach = smama_obj->x_pos;
                bossReachingTimer = 1;
                bossReachingAccuracyX = 0xFF;
                bossReachingAccuracyY = 0;
                setBossReachingSpeeds(smama_obj, 1, 0xFF, 0);
                skipToLabel(smama_obj, 1, true);
                currentBossActionIsOver = false;
                break;
            case 13:
                swapMereDenisCollZones(smama_obj, true);
                set_main_and_sub_etat(smama_obj, 0, 10);
                wep_obj->x_pos = smama_obj->x_pos;
                wep_obj->y_pos = smama_obj->y_pos;
                mach_obj->x_pos = smama_obj->x_pos;
                mach_obj->y_pos = smama_obj->y_pos;
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 14:
                swapMereDenisCollZones(smama_obj, false);
                set_main_and_sub_etat(mach_obj, 0, 37);
                mach_obj->flags |= FLG(OBJ_ALIVE);
                calc_obj_pos_map(mach_obj);
                currentBossActionIsOver = true;
                break;
            case 36:
                swapMereDenisCollZones(smama_obj, true);
                mach_obj->flags |= FLG(OBJ_ALIVE);
                smama_obj->display_prio = 6;
                wep_obj->flags |= FLG(OBJ_ALIVE);
                set_main_and_sub_etat(smama_obj, 0, 19);
                snapWeaponAnimState(wep_obj, 36);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 15:
                swapMereDenisCollZones(smama_obj, false);
                if ((s16) myRand(1))
                    set_main_and_sub_etat(smama_obj, 0, 0);
                else
                    set_main_and_sub_etat(smama_obj, 0, 9);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 16:
                swapMereDenisCollZones(smama_obj, false);
                stepsForward++;
                set_main_and_sub_etat(smama_obj, 1, 1);
                skipToLabel(smama_obj, 0, true);
                bossYToReach = smama_obj->y_pos;
                bossXToReach = smama_obj->eta[1][1].speed_x_right * smama_obj->nb_cmd / 16;
                if (smama_obj->flags & FLG(OBJ_FLIP_X))
                    bossXToReach = smama_obj->x_pos + bossXToReach;
                else
                    bossXToReach = smama_obj->x_pos - bossXToReach;
                bossReachingTimer = 1;
                bossReachingAccuracyX = 0xFF;
                bossReachingAccuracyY = 0xFF;
                setBossReachingSpeeds(smama_obj, 1, 0xFF, 0xFF);
                skipToLabel(smama_obj, 1, true);
                currentBossActionIsOver = false;
                break;
            case 26:
                swapMereDenisCollZones(smama_obj, false);
                set_main_and_sub_etat(smama_obj, 0, 5);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 18:
                swapMereDenisCollZones(smama_obj, false);
                laserSourceSprNumInAnim = 5;
                currentLaserSize = 4;
                set_main_and_sub_etat(smama_obj, 0, 7);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 34:
                switch (smama_obj->sub_etat)
                {
                case 34:
                    set_sub_etat(smama_obj, 31);
                    snapWeaponAnimState(wep_obj, 33);
                    break;
                case 21:
                case 31:
                case 19:
                    set_sub_etat(smama_obj, 24);
                    snapWeaponAnimState(wep_obj, 25);
                    break;
                }
                goto block_123;
            case 35:
                switch (smama_obj->sub_etat)
                {
                case 22:
                    set_sub_etat(smama_obj, 23);
                    snapWeaponAnimState(wep_obj, 26);
                    break;
                case 21:
                case 23:
                case 19:
                    set_sub_etat(smama_obj, 30);
                    snapWeaponAnimState(wep_obj, 32);
                    break;
                }
block_123:
                swapMereDenisCollZones(smama_obj, true);
                wep_obj->flags |= FLG(OBJ_ALIVE);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 32:
            case 33:
            case 43:
                swapMereDenisCollZones(smama_obj, true);
                laserSourceSprNumInAnim = 8;
                /* data format? */
                currentLaserSize = mereDenisActionSequences[bossEncounter][currentBossAction++];
                switch (cur_act)
                {
                case 33:
                    set_main_and_sub_etat(smama_obj, 0, 22);
                    snapWeaponAnimState(wep_obj, 18);
                    break;
                case 32:
                    set_main_and_sub_etat(smama_obj, 0, 21);
                    snapWeaponAnimState(wep_obj, 17);
                    break;
                case 43:
                    set_main_and_sub_etat(smama_obj, 0, 34);
                    snapWeaponAnimState(wep_obj, 35);
                    break;
                }
                wep_obj->flags |= FLG(OBJ_ALIVE);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 19:
                swapMereDenisCollZones(smama_obj, false);
                set_main_and_sub_etat(smama_obj, 0, 8);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 21:
                swapMereDenisCollZones(smama_obj, false);
                set_main_and_sub_etat(smama_obj, 0, 11);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 39:
                swapMereDenisCollZones(smama_obj, false);
                mach_obj->flags |= FLG(OBJ_ALIVE);
                smama_obj->display_prio = 3;
                mach_obj->speed_y = -6;
                set_main_and_sub_etat(mach_obj, 2, 1);
                mach_obj->speed_x = mach_obj->eta[mach_obj->main_etat][mach_obj->sub_etat].speed_x_left;
                level.objects[machine_obj_id].flags |= FLG(OBJ_ALIVE);
                set_main_and_sub_etat(smama_obj, 0, 14);
                smama_obj->x_pos += 100;
                goto block_90;
            case 22:
                swapMereDenisCollZones(smama_obj, false);
                set_main_and_sub_etat(smama_obj, 0, 13);
block_90:
                bossXToReach = smama_obj->x_pos;
                bossYToReach = scroll_end_y - smama_obj->offset_by - 16;
                setBossReachingSpeeds(smama_obj, 1, 0xFF, 0xFF);
                if (cur_act == 22)
                {
                    bossReachingAccuracyX = 32;
                    bossReachingAccuracyY = 32;
                    bossReachingTimer = 2;
                    if (smama_obj->flags & FLG(OBJ_FLIP_X))
                        bossXToReach += 80;
                    else
                        bossXToReach -= 80;
                }
                skipToLabel(smama_obj, 1, true);
                currentBossActionIsOver = false;
                break;
            case 30:
                smama_obj->flags =
                    smama_obj->flags & ~FLG(OBJ_FLIP_X) |
                    ((smama_obj->flags >> OBJ_FLIP_X ^ 1) & 1) << OBJ_FLIP_X;
                goto block_98;
            case 25:
                smama_obj->flags |= FLG(OBJ_FLIP_X);
                goto block_98;
            case 23:
            case 45:
block_98:
                mere_denis_wait_time = 60;
                swapMereDenisCollZones(smama_obj, false);
                setMereDenisAtScrollBorder(smama_obj, smama_obj->flags >> OBJ_FLIP_X & 1);
                if (cur_act == 45)
                {
                    bossXToReach = ray.offset_bx + ray.x_pos - smama_obj->offset_bx;
                    smama_obj->x_pos = bossXToReach;
                }
                else if (cur_act == 25)
                {
                    bossXToReach = level.objects[machine_obj_id].x_pos + 100;
                    smama_obj->x_pos = bossXToReach + 80;
                }
                else /* cur_act == 30 || cur_act == 23 */
                {
                    if (smama_obj->flags & FLG(OBJ_FLIP_X))
                    {
                        bossXToReach = smama_obj->x_pos + 48;
                        smama_obj->x_pos = bossXToReach + 80;
                    }
                    else
                    {
                        bossXToReach = smama_obj->x_pos - 160;
                        smama_obj->x_pos = bossXToReach - 80;
                    }
                }
                smama_obj->y_pos = scroll_end_y - smama_obj->offset_by - 16;
                bossYToReach = smama_obj->y_pos;
                bossReachingAccuracyX = 24;
                bossReachingAccuracyY = 24;
                bossReachingTimer = 1;
                setBossReachingSpeeds(smama_obj, 1, 0xFF, 0xFF);
                bossYToReach = floorLine - smama_obj->offset_by;
                set_main_and_sub_etat(smama_obj, 0, 14);
                skipToLabel(smama_obj, 1, true);
                currentBossActionIsOver = false;
                break;
            case 24:
                calc_obj_dir(smama_obj);
                swapMereDenisCollZones(smama_obj, false);
                set_main_and_sub_etat(smama_obj, 0, 1);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 37:
                swapMereDenisCollZones(smama_obj, true);
                wep_obj->flags &= ~FLG(OBJ_ALIVE);
                mach_obj->flags &= ~FLG(OBJ_ALIVE);
                set_main_and_sub_etat(smama_obj, 0, 6);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 31:
                swapMereDenisCollZones(smama_obj, true);
                smama_obj->x_pos -= 100;
                mach_obj->flags &= ~FLG(OBJ_ALIVE);
                set_main_and_sub_etat(smama_obj, 0, 20);
                skipToLabel(smama_obj, 0, true);
                currentBossActionIsOver = false;
                break;
            case 27:
                swapMereDenisCollZones(smama_obj, false);
                set_main_and_sub_etat(smama_obj, 0, 15);
                bossXToReach = smama_obj->x_pos;
                bossYToReach = scroll_end_y - smama_obj->offset_by - 16;
                bossReachingAccuracyX = 0xFF;
                bossReachingAccuracyY = 0xFF;
                bossReachingTimer = 1;
                setBossReachingSpeeds(smama_obj, 1, 0xFF, 0xFF);
                skipToLabel(smama_obj, 1, true);
                currentBossActionIsOver = false;
                currentBombSequence = 0xFF;
                break;
            case 28:
                swapMereDenisCollZones(smama_obj, false);
                setMereDenisAtScrollBorder(smama_obj, (smama_obj->flags >> OBJ_FLIP_X ^ 1) & 1);
                if (smama_obj->flags & FLG(OBJ_FLIP_X))
                {
                    smama_obj->x_pos -= 144;
                    bossXToReach = scroll_end_x - smama_obj->offset_bx + 464;
                }
                else
                {
                    smama_obj->x_pos += 144;
                    bossXToReach = scroll_start_x - smama_obj->offset_bx - 144;
                }
                smama_obj->y_pos =
                    floorLine - smama_obj->offset_by -
                    (mereDenisActionSequences[bossEncounter][currentBossAction++] + 32);
                bossYToReach = smama_obj->y_pos;
                set_main_and_sub_etat(smama_obj, 0, 15);
                bossReachingAccuracyX = 0xFF;
                bossReachingAccuracyY = 0xFF;
                bossReachingTimer = 1;
                setBossReachingSpeeds(smama_obj, 1, 0xFF, 0xFF);
                skipToLabel(smama_obj, 1, true);
                timerBeforeFirstBomb = 41;
                currentBombSequence = mereDenisActionSequences[bossEncounter][currentBossAction++];

                if (currentBombSequence == 0xFF)
                {
                    do
                    {
                        do
                        {
                            currentBombSequence = myRand(6);
                        } while (currentBombSequence == 1);
                    } while (currentBombSequence == 6);
                }

                for (i = 0; i < (s16) sizeof(lastDroppedBombIdInSequence); i++)
                    lastDroppedBombIdInSequence[i] = 0xFF;

                lastDroppedBombXCenterPos = -32000;
                currentBossActionIsOver = false;
                break;
            case 29:
                swapMereDenisCollZones(smama_obj, false);
                smama_obj->flags =
                    smama_obj->flags & ~FLG(OBJ_FLIP_X) |
                    ((smama_obj->flags >> OBJ_FLIP_X ^ 1) & 1) << OBJ_FLIP_X;
                set_main_and_sub_etat(smama_obj, 0, 0);
                skipToLabel(smama_obj, 0, true);
                mereDenisExplodeBombs();
                currentBossActionIsOver = false;
                break;
            }
        }
    }

    return cur_act;
}
#endif

/* 6619C 8018A99C -O2 -msoft-float */
void snapLaserToWeapon(Obj *laser_obj, u8 param_2)
{
    Obj *unk_obj = &level.objects[laser_obj->field20_0x36];
    s16 x; s16 y; s16 w; s16 h;
    u8 sub_etat;
    ObjState *eta;

    GET_SPRITE_POS(unk_obj, laser_obj->field24_0x3e, &x, &y, &w, &h);
    if (param_2)
    {
        sub_etat = unk_obj->sub_etat;
        eta = &unk_obj->eta[unk_obj->main_etat][sub_etat];
        switch (sub_etat)
        {
        case 17:
            eta->anim_index = 47;
            break;
        case 18:
            eta->anim_index = 46;
            break;
        case 35:
            eta->anim_index = 48;
            break;
        }
        unk_obj->anim_index = eta->anim_index;
        laser_obj->x_pos = x - laser_obj->offset_bx;
        if (unk_obj->flags & FLG(OBJ_FLIP_X))
        {
            laser_obj->cmd = GO_RIGHT;
            laser_obj->x_pos += w - 5;
        }
        else
        {
            laser_obj->cmd = GO_LEFT;
            laser_obj->x_pos += 5;
        }
    }
    laser_obj->speed_y = 0;
    laser_obj->y_pos = y + (h >> 1) - ((laser_obj->offset_by + laser_obj->offset_hy) / 2) + 2;
}

/* 66310 8018AB10 -O2 -msoft-float */
void allocateSpaceMamaLaser(Obj *smama_obj)
{
    u8 sub_etat;
    u8 obj_type;
    s16 i;
    Obj *cur_obj;
    s16 nb_objs;
    ObjFlags flags_flip;

    switch (currentLaserSize)
    {
    case 1:
        sub_etat = 3;
        obj_type = TYPE_SMA_GRAND_LASER;
        break;
    case 2:
        sub_etat = 4;
        obj_type = TYPE_SMA_GRAND_LASER;
        break;
    case 3:
        sub_etat = 2;
        obj_type = TYPE_SMA_GRAND_LASER;
        break;
    case 4:
        sub_etat = 4;
        obj_type = TYPE_SMA_PETIT_LASER;
        break;
    }

    cur_obj = &level.objects[0];
    i = 0;
    nb_objs = level.nb_objects;
    while (i < nb_objs)
    {
        if (cur_obj->type == obj_type && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            if (smama_obj->type == TYPE_SPACE_MAMA2)
                smama_obj = &level.objects[mereDenis_weapon_id];

            cur_obj->field20_0x36 = smama_obj->id;
            cur_obj->field24_0x3e = laserSourceSprNumInAnim;
            cur_obj->flags &= ~FLG(OBJ_READ_CMDS);
            flags_flip = cur_obj->flags & ~FLG(OBJ_FLIP_X);
            flags_flip |= smama_obj->flags & FLG(OBJ_FLIP_X);
            cur_obj->flags = flags_flip;
            cur_obj->anim_frame = 0;
            cur_obj->sub_etat = sub_etat;
            smama_obj->field20_0x36 = cur_obj->id;
            snapLaserToWeapon(cur_obj, true);
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            calc_obj_pos_map(cur_obj);
            break;
        }
        cur_obj++;
        i++;
    }
    laserSourceSprNumInAnim = 0xFF;
    currentLaserSize = 0;
}

/* 664CC 8018ACCC -O2 -msoft-float */
void doMereDenisCommand(Obj *obj)
{
    if (mere_denis_wait_time != 0)
        mere_denis_wait_time--;
    else if (mereDenisCanAttak(obj))
    {
        if (bossSafeTimer != 0)
            bossSafeTimer--;

        if (!(obj->flags & FLG(OBJ_FLAG_0)))
        {
            if (obj->cmd == GO_WAIT)
            {
                if (laserSourceSprNumInAnim != 0xFF)
                    allocateSpaceMamaLaser(obj);
                bossXToReach = -32000;
                bossYToReach = -32000;
                circleIndex = -32000;
                obj->speed_x = 0;
                obj->speed_y = 0;
            }
            else
            {
                laserSourceSprNumInAnim = 0xFF;
                if (circleIndex != -32000)
                    setCirclePointToReach();
                else if (
                    timerBeforeFirstBomb == 0 &&
                    currentBombSequence != 0xFF &&
                    obj->main_etat == 0 && obj->sub_etat == 15
                )
                    mereDenisDropBomb(obj);
                else if (timerBeforeFirstBomb != 0)
                    timerBeforeFirstBomb--;
                setBossReachingSpeeds(obj, bossReachingTimer, bossReachingAccuracyX, bossReachingAccuracyY);
            }
            testActionEnd(obj);
        }
        prepareNewMereDenisAttack(obj);
    }
    obj->flags &= ~FLG(OBJ_FLAG_0);
}

/* 666A4 8018AEA4 -O2 -msoft-float */
void changeMereDenisPhase(void)
{
    u8 old_encounter;
    u8 *encounter;
    u8 *action;

    if (bossEncounter == 8 || bossEncounter == 9)
    {
        encounter = &saveBossEncounter;
        action = &saveCurrentBossAction;
    }
    else
    {
        encounter = &bossEncounter;
        action = &currentBossAction;
    }
    old_encounter = *encounter;

    switch (*encounter)
    {
    case 1:
        if (currentPhaseHitCounter > 1 && stepsForward > 2)
        {
            *encounter = 2;
            stepsForward = 0;
        }
        break;
    case 2:
        if (currentPhaseHitCounter > 2)
            *encounter = 3;
        break;
    case 3:
    case 4:
    case 5:
    case 6: /* set to this at some point in prepareNewMereDenisAttack, not sure if max for space_mama */
        break;
    }

    if (old_encounter != *encounter)
    {
        *action = 0;
        currentPhaseHitCounter = 0;
    }
}

/* 66790 8018AF90 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/space_mama", fitSaveCurrentAction);
#else
/* wtf even */
void fitSaveCurrentAction(Obj *obj)
{
    u8 unk_1;

    do
    {
        unk_1 = false;
        switch (mereDenisActionSequences[bossEncounter][currentBossAction])
        {
        case 1:
            currentBossAction = 0;
            unk_1 = true;
            break;
        case 29:
            unk_1 = true;
            break;
        case 0:
            currentBossAction = 0;
            bossEncounter++;
            unk_1 = true;
            break;
        case 15:
        case 18:
        case 19:
        case 24:
        case 26:
            currentBossAction++;
            unk_1 = true;
            break;
        case 33:
        case 43:
            currentBossAction++;
        case 34:
        case 35:
        case 36:
            currentBossAction++;
            unk_1 = true;
            break;
        case 28:
            currentBossAction += 2;
            /* ??? prevents jump into case 22 (target 0x27b8) */
            if (currentBossAction && currentBossAction) {}
            unk_1 = true;
            break;
        case 22:
            if (currentBossAction != 0)
            {
                currentBossAction--;
                unk_1 = true;
            }
            break;
        default:
            break;
        }
    } while (unk_1 != 0);
    saveCurrentBossAction = currentBossAction;
    saveBossEncounter = bossEncounter;
}
#endif

/* 668E4 8018B0E4 -O2 -msoft-float */
void doMereDenisHit(Obj *obj, s16 sprite)
{
    s16 unk_1;
    u8 main_etat = obj->main_etat;
    u8 sub_etat = obj->sub_etat;

    if ((obj->eta[main_etat][sub_etat].flags & 1) && bossSafeTimer == 0)
    {
        switch (main_etat * 0x100 + sub_etat)
        {
        case 0x013:
        case 0x015:
        case 0x016:
        case 0x017:
        case 0x018:
        case 0x01e:
        case 0x01f:
        case 0x022:
            unk_1 = 0x00FF;
            break;
        case 0x002:
        case 0x006:
        case 0x00a:
        case 0x00b:
        case 0x00d:
        case 0x00f:
        case 0x025:
        case 0x02c:
            unk_1 = -1;
            break;
        default:
            unk_1 = 1;
            break;
        }

        if (unk_1 == sprite)
        {
            if (unk_1 == 1)
            {
                poing.damage = 1;
                obj_hurt(obj);
                currentPhaseHitCounter++;
                changeMereDenisPhase();
            }

            if (obj->hit_points != 0)
            {
                if (!(bossEncounter == 8 || bossEncounter == 9))
                {
                    fitSaveCurrentAction(obj);
                    if (obj->type == TYPE_SPACE_MAMA)
                        bossEncounter = 8;
                    else
                        bossEncounter = 9;
                }
            }
            else
                bossEncounter = 10;

            currentBossAction = 0;
            bossSafeTimer = 0xFF;
            currentBossActionIsOver = true;
            obj->flags |= FLG(OBJ_FLAG_0);
        }
    }
}

/* 66A64 8018B264 -O2 -msoft-float */
void mereDenisBigLaserCommand(Obj *laser_obj)
{
    u8 max_frame;
    Obj *unk_obj;
    ObjState *unk_eta;

    switch (laser_obj->sub_etat)
    {
    case 3:
    case 5:
        max_frame = 0;
        break;
    case 4:
        max_frame = 7;
        break;
    case 2:
        max_frame = 14;
        break;
    }

    if (laser_obj->anim_frame <= max_frame)
        snapLaserToWeapon(laser_obj, false);
    else
    {
        unk_obj = &level.objects[laser_obj->field20_0x36];
        if (unk_obj->field20_0x36 == laser_obj->id)
        {
            unk_eta = &unk_obj->eta[unk_obj->main_etat][unk_obj->sub_etat];
            switch (unk_obj->anim_index)
            {
            case 46:
                unk_eta->anim_index = 1;
                break;
            case 47:
                unk_eta->anim_index = 0;
                break;
            case 48:
                unk_eta->anim_index = 28;
                break;
            }
        }
    }
    SET_X_SPEED(laser_obj);
}

/* 66B98 8018B398 -O2 -msoft-float */
void mereDenisBombCommand(Obj *bomb_obj)
{
    if (bomb_obj->timer != 0)
    {
        bomb_obj->timer--;
        if (bomb_obj->timer == 0)
            allocateMereDenisBombChips(bomb_obj);
    }
}
