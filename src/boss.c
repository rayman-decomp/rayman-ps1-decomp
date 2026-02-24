#include "boss.h"

#ifdef BSS_DEFS
Obj *PS1_BossObj;

s16 bossScrollStartX;
s16 bossScrollStartY;
s16 bossScrollEndX;
s16 bossScrollEndY;
s16 floorLine;
s32 bossSpeedFactor;
s32 alternateBossSpeedFactor;

u8 bossEncounter;
u8 saveBossEncounter;
u8 bossReachingAccuracyX;
u8 bossReachingAccuracyY;
u8 bossReachingTimer;
u8 bossSafeTimer;
s16 bossXToReach;
s16 bossYToReach;

u8 curAct;
u8 currentBossAction;
u8 saveCurrentBossAction;
u8 currentBossActionIsOver;

u8 Phase;
u8 WaitForFinAtan;
u8 FinAnim;
u8 WaitForAnim;
#endif

/* TODO: still lots of unknowns */
/* 66BE8 8018B3E8 -O2 -msoft-float */
void setBossReachingSpeeds(Obj *obj, u8 horloge_ind, u8 unk_x, u8 unk_y)
{
    s16 diff_x_1;
    s16 diff_y_1;
    s32 diff_x_abs;
    s32 diff_y_abs;
    s32 unk_1;
    s16 unk_2;
    s32 unk_3;
    s16 unk_4;
    s16 unk_5;

    if ((bossXToReach != -32000) && (bossYToReach != -32000))
    {
        unk_1 = obj->eta[obj->main_etat][obj->sub_etat].speed_x_right * (bossSpeedFactor + alternateBossSpeedFactor);
        if (unk_1 < 0)
            unk_1 += 0x3FFF;
        unk_1 = unk_1 >> 0xE;
        diff_x_1 = (bossXToReach - obj->x_pos) * 16;
        diff_y_1 = (bossYToReach - obj->y_pos) * 16;
        if (!(diff_x_1 == 0 && diff_y_1 == 0) && unk_1 != 0)
        {
            diff_x_abs = __builtin_abs(diff_x_1);
            diff_y_abs = __builtin_abs(diff_y_1);
            unk_2 = MAX_1(diff_x_abs, diff_y_abs);
            unk_1 = MIN_1(unk_2, unk_1);
            unk_3 = ashl16(unk_2, 4) / unk_1;
            unk_4 = ashl16(diff_x_1, 4) / unk_3;
            unk_5 = ashl16(diff_y_1, 4) / unk_3;
            if (horloge[horloge_ind] == 0)
            {
                obj->speed_x = (obj->speed_x * (0xFF - unk_x) + (unk_4 * unk_x)) / 255;
                if (obj->main_etat == 2)
                {
                    if (unk_1 >= diff_y_1)
                        unk_y = 0xFF;
                }
                obj->speed_y = (obj->speed_y * (0xFF - unk_y) + (unk_5 * unk_y)) / 255;
            }
        }
        else
        {
            obj->speed_x = 0;
            obj->speed_y = 0;
        }
    }
    else
    {
        obj->speed_x = 0;
        obj->speed_y = 0;
    }
}

/* 66EFC 8018B6FC -O2 -msoft-float */
s16 testActionEnd(Obj *obj)
{
    s16 res = false;

    if (bossXToReach == -32000 && bossYToReach == -32000)
        res = obj->nb_cmd == 0;
    else if (obj->x_pos == bossXToReach && obj->y_pos == bossYToReach)
        res = true;
    if (res)
        currentBossActionIsOver = true;
    return res;
}

/* 66F8C 8018B78C -O2 -msoft-float */
void PS1_CalcCenteredValue(s16 *param_1, s16 *horloge_ind, s16 *param_3, s16 *param_4, u8 param_5)
{
    s16 sVar1;
    u16 unk_2;
    s16 sVar3;
    s16 sVar4;
    s32 sVar5;

    sVar1 = *param_3;
    unk_2 = *param_1;
    sVar3 = *param_4;
    sVar4 = *horloge_ind;
    *param_3 -= param_5;
    *param_4 -= param_5;
    sVar5 = unk_2 + (sVar1 >> 1);
    unk_2 = sVar4 + (sVar3 >> 1);
    if (*param_3 < 10)
        *param_3 = 10;
    if (*param_4 < 10)
        *param_4 = 10;
    *param_1 = sVar5 - (*param_3 >> 1);
    *horloge_ind = unk_2 - (*param_4 >> 1);
}

/* 6703C 8018B83C -O2 -msoft-float */
s16 firstFloorBelow(Obj *obj)
{
    s16 x = obj->offset_bx + obj->x_pos;
    s16 y = obj->offset_by + obj->y_pos;
    u8 btyp = BTYP(x, y);

    while (!(block_flags[btyp] >> BLOCK_SOLID & 1) && (y <= ymapmax + SCREEN_HEIGHT))
    {
        y += 16;
        btyp = BTYP(x, y);
    }

    return dist_to_bloc_floor(btyp, x & 0xf, 0) + (y & ~0xf);
}