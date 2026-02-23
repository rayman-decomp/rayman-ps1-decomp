#include "unknown/48528.h"

/* 48528 8016CD28 -O2 -msoft-float */
void debugw(void)
{
    s32 l1_pressed;
    DISPENV prev_disp_env;

    TOUCHE(INPUT_READ);
    l1_pressed = 0;
    prev_disp_env = PS1_Displays[0].field0_0x0;
    while (l1_pressed == 0)
    {
        if (leftmenu(0))
            PS1_VRAMDisplayXPos -= 32;
        if (rightmenu(0))
            PS1_VRAMDisplayXPos += 32;
        if (upmenu(0))
            PS1_VRAMDisplayYPos -= 32;
        if (downmenu(0))
            PS1_VRAMDisplayYPos += 32;

        if (butdbw(0))
            l1_pressed = 0xFF;

        if (PS1_VRAMDisplayYPos > 304)
            PS1_VRAMDisplayYPos = 280;
        if (PS1_VRAMDisplayYPos < 0)
            PS1_VRAMDisplayYPos = 0;
        if (PS1_VRAMDisplayXPos > 736)
            PS1_VRAMDisplayXPos = 712;
        if (PS1_VRAMDisplayXPos < 0)
            PS1_VRAMDisplayXPos = 0;

        SetDefDispEnv(
            &PS1_Displays[0].field0_0x0,
            PS1_VRAMDisplayXPos, PS1_VRAMDisplayYPos,
            SCREEN_WIDTH, SCREEN_HEIGHT
        );
        PS1_Displays[0].field0_0x0.pad0 =
        PS1_Displays[1].field0_0x0.pad0 = 1;
        PutDispEnv(&PS1_Displays[0].field0_0x0);
        TOUCHE(INPUT_READ);
    }

    while (PS1_NoButtonPressed(0) == 0)
        TOUCHE(INPUT_READ);

    PS1_Displays[0].field0_0x0 = prev_disp_env;
}

/* 487A4 8016CFA4 -O2 -msoft-float */
s16 test_allowed(Obj *obj, s16 unk_x, s16 unk_y)
{
    s16 map_index =
        ((unk_x + obj->x_pos) >> 4) +
        ((unk_y + obj->y_pos) >> 4) * mp.width;
    u8 res = false;

    if (map_index != obj->test_block_index)
    {
        obj->test_block_index = map_index;
        res = true;
    }
    return res;
}

/* 4880C 8016D00C -O2 -msoft-float */
void obj_jump(Obj *obj)
{
    s16 spd_y;
    u8 unk_1 = 0;
    s16 spd_x = obj->speed_x;
    u8 label = 0xFF;

    switch (obj->type)
    {
    case TYPE_STONEWOMAN:
        if (obj->eta[obj->main_etat][obj->sub_etat].flags & 1)
        {
            label = 15;
            set_main_and_sub_etat(obj, 2, 3);
            spd_y = -3;
            unk_1 = 5;
        }
        break;
    case TYPE_BLACKTOON1:
        if (obj->field56_0x69 & 2)
        {
            label = 1;
            set_main_and_sub_etat(obj, 2, 5);
            spd_y = -3;
        }
        break;
    }

    if (label != 0xFF)
    {
        skipToLabel(obj, label, true);
        obj->speed_x = spd_x;
        obj->speed_y = spd_y;
        obj->gravity_value_1 = 0;
        obj->gravity_value_2 = unk_1;
        obj->y_pos -= 12;
        calc_btyp(obj);
    }
}

/* 48920 8016D120 -O2 -msoft-float */
void DO_ONE_PINK_CMD(Obj *obj)
{
    if (obj->iframes_timer != 0)
        obj->iframes_timer--;

    if (
        (gerbe && (obj->eta[obj->main_etat][obj->sub_etat].flags & 2)) ||
        (obj->main_etat == 2 && obj->sub_etat == 1 && obj->speed_y > 2)
    )
    {
        set_main_and_sub_etat(obj, 0, 5);
        obj->speed_x = 0;
        obj->speed_y = -10;
    }

    switch (obj->main_etat * 0x100 + obj->sub_etat)
    {
    case 0x2:
        if (EOA(obj))
            obj->flags =
                obj->flags & ~FLG(OBJ_FLIP_X) |
                ((obj->flags >> OBJ_FLIP_X ^ 1) & 1) << OBJ_FLIP_X;
        break;
    case 0x100:
        SET_X_SPEED(obj);
        if (block_flags[calc_typ_travd(obj, false)] >> BLOCK_FULLY_SOLID & 1)
        {
            obj->flags =
                obj->flags & ~FLG(OBJ_FLIP_X) |
                ((obj->flags >> OBJ_FLIP_X ^ 1) & 1) << OBJ_FLIP_X;
        }
        CALC_MOV_ON_BLOC(obj);
        return;
    case 0x202:
        obj->speed_x = 0;
    case 0x200:
    case 0x201:
        if (obj->speed_y < 0 && (block_flags[(u8) calc_typ_trav(obj, 1)] >> BLOCK_FLAG_4 & 1))
        {
            if (!gerbe)
                set_sub_etat(obj, 2);
            obj->speed_y = 0;
        }
        break;
    case 0x0:
    case 0x1:
    case 0x3:
    case 0x4:
    case 0x5:
    default:
        break;
    }
}

/* 48C18 8016D418 -O2 -msoft-float */
void FUN_8016d418(Obj *obj)
{
    switch (obj->cmd)
    {
    case GO_UP:
        obj->speed_y = -1;
        break;
    case GO_DOWN:
        obj->speed_y = 1;
        break;
    case GO_WAIT:
        obj->speed_y = 0;
        break;
    }

    SET_X_SPEED(obj);
    if (obj->main_etat == 1 && (block_flags[calc_typ_travd(obj, false)] >> BLOCK_FULLY_SOLID & 1))
    {
        switch (obj->type)
        {
        case TYPE_POI1:
            set_main_and_sub_etat(obj, 0, 0);
            break;
        case TYPE_POI2:
            set_main_and_sub_etat(obj, 0, 1);
            break;
        case TYPE_POI3:
            set_main_and_sub_etat(obj, 0, 4);
            break;
        }
        obj->speed_x = 0;
        obj->flags =
            obj->flags & ~FLG(OBJ_FLIP_X) |
            (1 - (obj->flags >> OBJ_FLIP_X & 1) & 1) << OBJ_FLIP_X; /* TODO: ??? */
    }
}
