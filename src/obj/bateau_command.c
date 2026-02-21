#include "obj/bateau_command.h"

#ifdef BSS_DEFS
s16 bateau_obj_id;
#endif

/* 501FC 801749FC -O2 -msoft-float */
void doShipCommand(Obj *obj)
{
    Obj *temp_s0_2;
    s16 temp_a0_1;
    s16 temp_v1_2;
    s32 temp_s0_1;
    u8 var_s2;
    s32 var_v0_1;
    s32 var_v0_2;
    u8 var_v1;
    u8 *var_v0_3;
    u8 temp_a0_2;
    u8 temp_v1;
    s32 temp_v1_3;
    u8 var_s3;
    Obj *test_1;
    LevelData *test_2;
    u8 test_3;
    u32 test_4;
    Obj *test_5;

    /*var_s3 = saved_reg_s3;*/
    temp_v1 = obj->cmd;
    switch (temp_v1)
    {
    case 2:
        obj->speed_y = 0;
        obj->speed_x = 0;
        return;
    case 20:
        obj->speed_x = obj->iframes_timer;
        obj->speed_y = obj->field20_0x36;
        return;
    case 30:
        if (obj->flags & 0x1000)
        {
            temp_a0_1 = obj->field23_0x3c;
            var_v1 = 1;
            if (temp_a0_1 != -1)
            {
                test_5 = &level.objects[temp_a0_1];
                test_4 = test_5->flags & 0x800;
                var_v1 = !test_4;
            }
            if ((var_v1) && (obj->timer != 0) && (horloge[2] != 0))
            {
                obj->timer--;
            }
            do
            {
                var_s2 = 0;
                if (obj->timer == 0)
                {
                    switch (obj->field24_0x3e)
                    {
                    case 0:
                        obj->field24_0x3e = 2;
                    case 4:
                        var_s3 = obj->type;
                        break;
                    case 1:
                        obj->field24_0x3e = 3;
                        var_s3 = 0x4D;
                        break;
                    case 2:
                        obj->field24_0x3e = 1;
                        var_s3 = 0x48;
                        var_s2 = 1;
                        break;
                    case 3:
                        obj->field24_0x3e = 4;
                        var_s3 = 0xBB;
                        break;
                    }
                    if (var_s2 == 0)
                    {
                        obj->timer = 0x32;
                    }
                    if (var_s3 != obj->type)
                    {
                        skipOneCommand(obj);
                        obj->nb_cmd = 0;
                        test_3 = obj->id;
                        do
                        {
                            test_3 = link_init[test_3];
                            test_5 = &level.objects[test_3];
                            temp_v1_3 = test_5->type;
                            if (temp_v1_3 == var_s3)
                            {
                                break;
                            }
                        } while (temp_v1_3 != obj->type);
                        

                        if (temp_v1_3 != obj->type)
                        {
                            switch (temp_v1_3)
                            {
                            case 0x4D:
                                guetteurFollowsShip(test_5);
                                break;
                            case 0x48:
                                ngaweTriesToGrabShip(test_5);
                                break;
                            case 0xBB:
                                pmamaFollowsShip(test_5);
                                PMA_SORT_DU_CANON(test_5);
                                break;
                            }
                            suppressFromLinkList(test_5);
                            MOVE_OBJECT(test_5);
                            calc_obj_pos_map(test_5);
                            test_5->flags |= 0x400;
                            obj->field23_0x3c = test_5->id;
                        }
                    }
                }
            } while (var_s2 != 0);
        }
        return;
    }
}