#include "input_ED20.h"

#ifdef BSS_DEFS
s32 PS1_GlobalTimer;
u8 PS1_PadReceiveBuffer[34];
s16 D_801E4C08;
s16 joy_rec_left;
s16 joy_rec_right;
s16 joy_rec_down;
s16 D_801F8428;
s16 D_801F8430;
s16 D_801F8438;
s16 D_801F8448;
s32 D_801E4B60;
s16 D_801F5688;
#endif

/* ED20 80133520 -O2 -msoft-float */
s32 readinput(void)
{
    return (s16) TOUCHE(INPUT_READ);
}

/* ED44 80133544 -O2 -msoft-float */
s32 upjoy(s32 param_1)
{
    s16 res;

    if (!PS1_DisableInputs)
    {
        if (record.is_playing)
            res = (u16) D_801E4C08;
        else
            res = TOUCHE(INPUT_UP);
        return res;
    }
    else
        return false;
}

/* EDA4 801335A4 -O2 -msoft-float */
s32 leftjoy(s32 param_1)
{
    s16 res;

    if (!PS1_DisableInputs)
    {
        if (record.is_playing)
            res = (u16) joy_rec_left;
        else
            res = TOUCHE(INPUT_LEFT);
        return res;
    }
    else
        return false;
}

/* EE04 80133604 -O2 -msoft-float */
s32 rightjoy(s32 param_1)
{
    s16 res;

    if (!PS1_DisableInputs)
    {
        if (record.is_playing)
            res = (u16) joy_rec_right;
        else
            res = TOUCHE(INPUT_RIGHT);
        return res;
    }
    else
        return false;
}

/* EE64 80133664 -O2 -msoft-float */
s32 downjoy(s32 param_1)
{
    s16 res;

    if (!PS1_DisableInputs)
    {
        if (record.is_playing)
            res = (u16) joy_rec_down;
        else
            res = TOUCHE(INPUT_DOWN);
        return res;
    }
    else
        return false;
}

/* EEC4 801336C4 -O2 -msoft-float */
s32 upmenu(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_UP);
    else
        return false;
}

/* EF14 80133714 -O2 -msoft-float */
s32 leftmenu(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_LEFT);
    else
        return false;
}

/* EF64 80133764 -O2 -msoft-float */
s32 rightmenu(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_RIGHT);
    else
        return false;
}

/* EFB4 801337B4 -O2 -msoft-float */
s32 downmenu(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_DOWN);
    else
        return false;
}

/* F004 80133804 -O2 -msoft-float */
s32 but0pressed(s32 param_1)
{
    s16 res;

    if (!PS1_DisableInputs)
    {
        if (record.is_playing)
            res = (u16) D_801F8428;
        else
            res = TOUCHE(INPUT_SQUARE);
        return res;
    }
    else
        return false;
}

/* F064 80133864 -O2 -msoft-float */
s32 but1pressed(s32 param_1)
{
    s16 res;

    if (!PS1_DisableInputs)
    {
        if (record.is_playing)
            res = (u16) D_801F8438;
        else
            res = TOUCHE(INPUT_CROSS);
        return res;
    }
    else
        return false;
}

/* F0C4 801338C4 -O2 -msoft-float */
s32 but2pressed(s32 param_1)
{
    s16 res;

    if (!PS1_DisableInputs)
    {
        if (record.is_playing)
            res = (u16) D_801F8448;
        else
            res = TOUCHE(INPUT_TRIANGLE);
        return res;
    }
    else
        return false;
}

/* F124 80133924 -O2 -msoft-float */
s32 but3pressed(s32 param_1)
{
    s16 res;

    if (!PS1_DisableInputs)
    {
        if (record.is_playing)
            res = (u16) D_801F8430;
        else
            res = TOUCHE(INPUT_CIRCLE);
        return res;
    }
    else
        return false;
}

/* F184 80133984 -O2 -msoft-float */
s32 FUN_80133984(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return TOUCHE(INPUT_L1) || TOUCHE(INPUT_L2);
    else
        return false;
}

/* F1F4 801339F4 -O2 -msoft-float */
s32 FUN_801339f4(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return TOUCHE(INPUT_R1) || TOUCHE(INPUT_R2);
    else
        return false;
}

/* F264 80133A64 -O2 -msoft-float */
s32 PS1_IsInputtingCheatCode(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return TOUCHE(INPUT_R1) && TOUCHE(INPUT_R2);
    else
        return false;
}

/* could also write this with ternary op instead */
/* F2CC 80133ACC -O2 -msoft-float */
s32 FUN_80133acc(s32 param_1)
{
    if (PS1_DisableInputs)
        return false;
    else
        return (s16) TOUCHE(INPUT_L1);
}

/* F308 80133B08 -O2 -msoft-float */
s32 FUN_80133b08(s32 param_1)
{
    if (PS1_DisableInputs)
        return false;
    else
        return (s16) TOUCHE(INPUT_R1);
}

/* F344 80133B44 -O2 -msoft-float */
s32 FUN_80133b44(s32 param_1)
{
    if (PS1_DisableInputs)
        return false;
    else
        return (s16) TOUCHE(INPUT_SELECT);
}

/* F380 80133B80 -O2 -msoft-float */
s32 FUN_80133b80(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_L1);
    else
        return false;
}

/* F3D0 80133BD0 -O2 -msoft-float */
s32 FUN_80133bd0(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_L2);
    else
        return false;
}

/* F420 80133C20 -O2 -msoft-float */
s32 FUN_80133c20(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_R1);
    else
        return false;
}

/* F470 80133C70 -O2 -msoft-float */
s32 FUN_80133c70(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_R2);
    else
        return false;
}

/* F4C0 80133CC0 -O2 -msoft-float */
s32 butL1(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_L1);
    else
        return false;
}

/* F510 80133D10 -O2 -msoft-float */
s32 butL2(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_L2);
    else
        return false;
}

/* F560 80133D60 -O2 -msoft-float */
s32 butR1(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_R1);
    else
        return false;
}

/* F5B0 80133DB0 -O2 -msoft-float */
s32 butR2(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_R2);
    else
        return false;
}

/* F600 80133E00 -O2 -msoft-float */
s32 but0pressed2__SQUARE(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_SQUARE);
    else
        return false;
}

/* F650 80133E50 -O2 -msoft-float */
s32 but1pressed2__CROSS(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_CROSS);
    else
        return false;
}

/* F6A0 80133EA0 -O2 -msoft-float */
s32 but2pressed__TRIANGLE(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_TRIANGLE);
    else
        return false;
}

/* F6F0 80133EF0 -O2 -msoft-float */
s32 but3pressed__CIRCLE(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_CIRCLE);
    else
        return false;
}

/* F740 80133F40 -O2 -msoft-float */
s32 butstart(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_START);
    else
        return false;
}

/* F790 80133F90 -O2 -msoft-float */
s32 butSelectPressed(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_SELECT);
    else
        return false;
}

/* F7E0 80133FE0 -O2 -msoft-float */
s32 FUN_80133fe0(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_NONE);
    else
        return false;
}

/* F830 80134030 -O2 -msoft-float */
s32 butvbl(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_SELECT);
    else
        return false;
}

/* F880 80134080 -O2 -msoft-float */
s32 butdbw(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_L1);
    else
        return false;
}

/* F8D0 801340D0 -O2 -msoft-float */
s32 butmode(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_L2);
    else
        return false;
}

/* F920 80134120 -O2 -msoft-float */
s32 butR2_2(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_R2);
    else
        return false;
}

/* F970 80134170 -O2 -msoft-float */
s32 butR1_1(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) padd(INPUT_R1);
    else
        return false;
}

/* F9C0 801341C0 -O2 -msoft-float */
s32 cheat_start(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_DISABLE_DEBUG);
    else
        return false;
}

/* FA10 80134210 -O2 -msoft-float */
s32 cheat1_start(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_UNUSED_12);
    else
        return false;
}

/* FA60 80134260 -O2 -msoft-float */
s32 cheat2_start(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_13);
    else
        return false;
}

/* FAB0 801342B0 -O2 -msoft-float */
s32 cheat3_start(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_14);
    else
        return false;
}

/* FB00 80134300 -O2 -msoft-float */
s32 cheat4_start(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_UNUSED_15);
    else
        return false;
}

/* FB50 80134350 -O2 -msoft-float */
s32 cheat5_start(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_UNUSED_16);
    else
        return false;
}

/* FBA0 801343A0 -O2 -msoft-float */
s32 cheat6_start(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_17);
    else
        return false;
}

/* FBF0 801343F0 -O2 -msoft-float */
s32 cheat7_start(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_18);
    else
        return false;
}

/* FC40 80134440 -O2 -msoft-float */
s32 FUN_80134440(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_UNUSED_19);
    else
        return false;
}

/* FC90 80134490 -O2 -msoft-float */
s32 FUN_80134490(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_UNUSED_1A);
    else
        return false;
}

/* FCE0 801344E0 -O2 -msoft-float */
s32 cheat_stop(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_ENABLE_DEBUG);
    else
        return false;
}

/* FD30 80134530 -O2 -msoft-float */
s32 FUN_80134530(s32 param_1)
{
    if (!PS1_DisableInputs && !record.is_playing)
        return (s16) TOUCHE(INPUT_START_SELECT);
    else
        return false;
}

/* FD80 80134580 -O2 -msoft-float */
s32 but0pressed__CROSS(void)
{
    return (s16) but1pressed2__CROSS(0);
}

/* FDA4 801345A4 -O2 -msoft-float */
s32 but1pressed__START(void)
{
    return (s16) butstart(0);
}

/* FDC8 801345C8 -O2 -msoft-float */
s32 butStartPressed(void)
{
    return (s16) butstart(0);
}

/* FDEC 801345EC -O2 -msoft-float */
s32 but2pressed__SELECT(void)
{
    return (s16) butSelectPressed(0);
}

/* FE10 80134610 -O2 -msoft-float */
void FUN_80134610(u8 param_1)
{
    D_801F8448 = false;
    D_801F8430 = false;
    D_801F8438 = false;
    D_801F8428 = false;

    if (param_1 & FLG(0))
    {
        switch (options_jeu.Fist)
        {
        case 0:
            D_801F8428 = true;
            break;
        case 1:
            D_801F8438 = true;
            break;
        case 2:
            D_801F8430 = true;
            break;
        case 3:
            D_801F8448 = true;
            break;
        }
    }

    if (param_1 & FLG(1))
    {
        switch (options_jeu.Jump)
        {
        case 0:
            D_801F8428 = true;
            break;
        case 1:
            D_801F8438 = true;
            break;
        case 2:
            D_801F8430 = true;
            break;
        case 3:
            D_801F8448 = true;
            break;
        }
    }

    if (param_1 & FLG(2))
    {
        switch (options_jeu.Action)
        {
        case 0:
            D_801F8428 = true;
            break;
        case 1:
            D_801F8438 = true;
            break;
        case 2:
            D_801F8430 = true;
            break;
        case 3:
            D_801F8448 = true;
            break;
        }
    }

    if (param_1 & FLG(3))
    {
        switch (options_jeu.field6_0x14)
        {
        case 0:
            D_801F8428 = true;
            break;
        case 1:
            D_801F8438 = true;
            break;
        case 2:
            D_801F8430 = true;
            break;
        case 3:
            D_801F8448 = true;
            break;
        }
    }

    if (param_1 & FLG(4))
        joy_rec_left = true;
    else
        joy_rec_left = false;

    if (param_1 & FLG(5))
        joy_rec_right = true;
    else
        joy_rec_right = false;

    if (param_1 & FLG(6))
        D_801E4C08 = true;
    else
        D_801E4C08 = false;

    if (param_1 & FLG(7))
        joy_rec_down = true;
    else
        joy_rec_down = false;
}

/* 1011C 8013491C -O2 -msoft-float */
u8 FUN_8013491c(void)
{
    s32 unk_1 = 0;
    s32 res = unk_1;

    if ((s16) but0pressed(0))
        res |= FLG(0);
    if ((s16) but1pressed(0))
        res |= FLG(1);
    if ((s16) but2pressed(0))
        res |= FLG(2);
    if ((s16) but3pressed(0))
        res |= FLG(3);
    if ((s16) leftjoy(0))
        res |= FLG(4);
    if ((s16) rightjoy(0))
        res |= FLG(5);
    if ((s16) upjoy(0))
        res |= FLG(6);
    if ((s16) downjoy(0))
        res |= FLG(7);

    return res;
}

/* 10200 80134A00 -O2 -msoft-float */
void record_input(Record *record)
{
    u8 unk_1;
    s32 cur_offs = record->current_offset;

    if (record->is_recording)
    {
        unk_1 = FUN_8013491c();
        if (cur_offs == 0)
        {
            record->repeat_index = 0;
            record->data[cur_offs] = unk_1;
            record->is_finished = false;
            record->current_offset++;
        }
        else
        {
            record->repeat_index++;
            if (
                record->data[cur_offs - 1] != unk_1 ||
                record->repeat_index == 0x000000FF ||
                record->is_finished == true
            )
            {
                record->data[cur_offs] = record->repeat_index; /* loaded as u8? */
                cur_offs++;
                record->data[cur_offs] = unk_1;
                cur_offs++;
                record->repeat_index = 0;
                record->current_offset = cur_offs;

                if (record->current_offset >= 10000 || record->is_finished == true)
                {
                    record->current_offset--;
                    record->is_recording = false;
                }
            }
        }
    }
    else if (record->is_playing)
    {
        if (cur_offs == 0)
        {
            record->repeat_index = 0;
            FUN_80134610(record->data[cur_offs]);
            cur_offs++;
            record->repeat_length = record->data[cur_offs];
            record->current_offset = cur_offs;
            record->is_finished = false;
        }
        else
        {
            if (++record->repeat_index == record->repeat_length)
            {
                if (record->is_finished == true || (cur_offs + 1 >= record->length))
                {
                    record->is_playing = false;
                    if (ModeDemo == 1)
                    {
                        ModeDemo = 2;
                        new_world = true;
                    }
                }
                else
                {
                    cur_offs += 2;
                    record->repeat_index = 0;
                    record->repeat_length = record->data[cur_offs];
                    record->current_offset = cur_offs;
                }
            }
            cur_offs--;
            FUN_80134610(record->data[cur_offs]);
        }
    }
}

/* 103E0 80134BE0 -O2 -msoft-float */
void FUN_80134be0(void)
{
    vu8 unk_1;
    vu8 unk_2;

    *(s32 *) &unk_1 = PS1_PadReceiveBuffer[3];
    unk_2 = PS1_PadReceiveBuffer[2];
    *(s32 *) &unk_1 ^= 0xFFFF;
}

/* 10414 80134C14 -O2 -msoft-float */

s32 TOUCHE(Input param_1)
{
    s16 temp_v0_3;
    s16 var_a2;
    s32 temp_t7;
    s32 temp_v0_1;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_a3;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    u32 temp_a0;
    s32 test_1;
    s32 *new_var;
    s32 var_a0;

    /*var_v0 = *(&jtbl_80127304 + (temp_a0 * 4));*/
    switch (param_1)
    {
    case 0xFF:
        PS1_ButtonStates[1] = *PS1_ButtonStates;
        *PS1_ButtonStates = 0;
        
        *PS1_ButtonStates = PS1_PadReceiveBuffer[3] + (PS1_PadReceiveBuffer[2] << 8);
        if (*PS1_ButtonStates != 0)
        {
            *PS1_ButtonStates ^= 0xFFFF;
        }
        
        if (++D_801E4DF8 >= 5)
        {
            D_801E4DF8 = 0;
            PS1_GlobalTimer -= 1;
        }
        if ((ModeDemo == 1) && (*PS1_ButtonStates & 0x840))
        {
            ModeDemo = 2;
            new_world = 1;
        }
        new_var = PS1_ButtonStates;
        if (PS1_ButtonStates[1] != *new_var)
        {
            D_801E4B60 = 0;
            /*__builtin_memcpy(&PS1_ButtonStates[2], &PS1_ButtonStates[1], 15 * sizeof(s32));*/
            PS1_ButtonStates[16] = PS1_ButtonStates[15];
            PS1_ButtonStates[15] = PS1_ButtonStates[14];
            PS1_ButtonStates[14] = PS1_ButtonStates[13];
            PS1_ButtonStates[13] = PS1_ButtonStates[12];
            PS1_ButtonStates[12] = PS1_ButtonStates[11];
            PS1_ButtonStates[11] = PS1_ButtonStates[10];
            PS1_ButtonStates[10] = PS1_ButtonStates[9];
            PS1_ButtonStates[9] = PS1_ButtonStates[8];
            PS1_ButtonStates[8] = PS1_ButtonStates[7];
            PS1_ButtonStates[7] = PS1_ButtonStates[6];
            PS1_ButtonStates[6] = PS1_ButtonStates[5];
            PS1_ButtonStates[5] = PS1_ButtonStates[4];
            PS1_ButtonStates[4] = PS1_ButtonStates[3];
            PS1_ButtonStates[3] = PS1_ButtonStates[2];
            PS1_ButtonStates[2] = PS1_ButtonStates[1];
        }
        else
        {
            D_801E4B60 += 1;
        }
        PS1_DisableInputs = 0;
        return 0;
    case 0xF:
    case 0x10:
    case 0x12:
    case 0x15:
    case 0x16:
    case 0x19:
    case 0x1A:
        return 0;
    case 0x0:
        return *PS1_ButtonStates == 0;
    case 0x1:
        return *PS1_ButtonStates & 0x8000;
    case 0x2:
        return *PS1_ButtonStates & 0x2000;
    case 0x3:
        return *PS1_ButtonStates & 0x1000;
    case 0x4:
        return *PS1_ButtonStates & 0x4000;
    case 0x5:
        return *PS1_ButtonStates & 0x40;
    case 0x6:
        return *PS1_ButtonStates & 0x20;
    case 0x7:
        return *PS1_ButtonStates & 0x80;
    case 0x8:
        return *PS1_ButtonStates & 0x10;
    case 0x9:
        return *PS1_ButtonStates & 0x800 && !(PS1_ButtonStates[2] & 0x800);
    case 0xA:
        return *PS1_ButtonStates & 0x100;
    case 0xB:
        return *PS1_ButtonStates & 8;
    case 0xC:
        return *PS1_ButtonStates & 2;
    case 0xD:
        return *PS1_ButtonStates & 4;
    case 0xE:
        return *PS1_ButtonStates & 1;
    case 0x13:
        if (
            (*PS1_ButtonStates != PS1_ButtonStates[1]) &&
            (*PS1_ButtonStates == 0x100B) &&
            (PS1_ButtonStates[2] == 0x000B) &&
            (PS1_ButtonStates[3] == 0x200B) &&
            (PS1_ButtonStates[4] == PS1_ButtonStates[2]) &&
            (PS1_ButtonStates[5] == 0x400B) &&
            (PS1_ButtonStates[6] == PS1_ButtonStates[4]) &&
            (PS1_ButtonStates[7] == 0x800B) &&
            (PS1_ButtonStates[8] == PS1_ButtonStates[6]) &&
            PS1_ButtonStates[9] == 0x800B
        )
        {
            var_a2 = 1;
        }
        else
            var_a2 = 0;
        D_801F5688 = var_a2;
        return 0;
    case 0x14:
        if (
            *PS1_ButtonStates != PS1_ButtonStates[1] &&
            *PS1_ButtonStates == 0x0022 &&
            (PS1_ButtonStates[2] == 2) &&
            (PS1_ButtonStates[3] == *PS1_ButtonStates) &&
            PS1_ButtonStates[4] == PS1_ButtonStates[2] &&
            PS1_ButtonStates[5] == 0x8002 &&
            PS1_ButtonStates[6] == PS1_ButtonStates[4] &&
            PS1_ButtonStates[7] == PS1_ButtonStates[3] &&
            PS1_ButtonStates[8] == PS1_ButtonStates[6] &&
            PS1_ButtonStates[9] == 0x0022
        )
        {
            var_a3 = 1;
        }
        else
            var_a3 = 0;
        return var_a3;
    case 0x17:
        var_a2 = 0;
        if (
            *PS1_ButtonStates != PS1_ButtonStates[1] &&
            *PS1_ButtonStates == 0x8003 &&
            PS1_ButtonStates[2] == 3 &&
            PS1_ButtonStates[3] == 0x4003 &&
            PS1_ButtonStates[4] == PS1_ButtonStates[2] &&
            PS1_ButtonStates[3] != 3 &&
            PS1_ButtonStates[5] == 0x8002 &&
            PS1_ButtonStates[6] == PS1_ButtonStates[4] &&
            PS1_ButtonStates[7] == 0x8002 &&
            PS1_ButtonStates[8] == PS1_ButtonStates[5]
        )
        {
            
        }
        return var_a2;
    
    case 0x18:
        if (
            *PS1_ButtonStates != PS1_ButtonStates[1] &&
            *PS1_ButtonStates == 0x0020 &&
            PS1_ButtonStates[2] == 0x00A0 &&
            PS1_ButtonStates[3] == 0x00B0 &&
            PS1_ButtonStates[4] == 0x80B0 &&
            PS1_ButtonStates[5] == 0x80A0 &&
            PS1_ButtonStates[6] == 0x8020 &&
            PS1_ButtonStates[7] == 0x8000 &&
            PS1_ButtonStates[8] == 0 &&
            PS1_ButtonStates[9] == *PS1_ButtonStates &&
            PS1_ButtonStates[10] == 0 &&
            PS1_ButtonStates[11] == 8 &&
            PS1_ButtonStates[12] == 0x000A &&
            PS1_ButtonStates[13] == 0x000B &&
            PS1_ButtonStates[14] == 0x000F &&
            PS1_ButtonStates[15] == 0x000D &&
            PS1_ButtonStates[16] == 9
        )
        {
            var_a1 = 1;
        }
        else
            var_a1 = 0;
        return var_a1;
    case 0x11:
        
        if (*PS1_ButtonStates != PS1_ButtonStates[1] && *PS1_ButtonStates == 0x0900)
        {
            var_v0 = 1;
        }
        else
            var_v0 = 0;
        
        return var_v0;
    default:
        /* TODO: no explicit return? */
        break;
    }
}

/* 10B00 80135300 -O2 -msoft-float */
s32 padd(Input param_1)
{
    if (PS1_ButtonStates[0] != PS1_ButtonStates[1])
        return TOUCHE(param_1);
    else
        return false;
}
