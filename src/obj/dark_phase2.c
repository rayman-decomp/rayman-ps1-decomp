#include "obj/dark_phase2.h"

#ifdef BSS_DEFS
Obj *dark_obj;
s16 phase_dark2;
u8 TextDark2_Affiche;
s16 XText;
s16 YText;
s16 temps_text;
u8 txt_dark2[104];
s16 dark2_rayon_dx_1;
s16 dark2_rayon_dx_2;
s16 dark2_rayon_dy_1;
s16 dark2_rayon_dy_2;
s16 PosXSin1;
s16 PosYSin1;
s16 PosXSin2;
s16 PosYSin2;
s16 VitesseYText;
u8 num_dark2_phrase;
u8 sens_sinus_1;
u8 sens_sinus_2;
u8 sinus_actif;
#endif

/* 76A14 8019B214 -O2 -msoft-float */
void AllocateDarkPhase2(Obj *mr_drk_obj)
{
    Obj *cur_obj = &level.objects[0];
    s16 i = 0;
    s16 nb_objs = level.nb_objects;

    while (i < nb_objs)
    {
        if ((cur_obj->type == TYPE_DARK_PHASE2) && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
        {
            cur_obj->init_x_pos = cur_obj->x_pos = mr_drk_obj->x_pos;
            cur_obj->init_y_pos = cur_obj->y_pos = mr_drk_obj->y_pos;
            cur_obj->speed_x = 0;
            cur_obj->speed_y = 0;
            cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
            set_main_and_sub_etat(cur_obj, 0, 38);

            dark_obj = mr_drk_obj;
            phase_dark2 = 0;
            mr_drk_obj->flags &= ~FLG(OBJ_ALIVE);
            mr_drk_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        }
        cur_obj++;
        i++;
    }
}

/* 76B00 8019B300 -O2 -msoft-float */
void DO_DARK2_AFFICHE_TEXT(void)
{
    s32 x; s32 y;

    if (TextDark2_Affiche)
    {
        let_shadow = true;
        x = XText;
        y = YText;
        temps_text += 3;
        display_text_sin(txt_dark2, x, y, temps_text & 0xFFFF, 2, 10);
    }
}

/* 76B74 8019B374 -O2 -msoft-float */
void DO_DARK_PHASE2_COMMAND(Obj *dp2_obj)
{
    s16 dp2_x; s16 dp2_y; s16 dp2_w; s16 dp2_h;
    s16 ds2_x; s16 ds2_y;
    Obj *poing_obj;

    if (dp2_obj->main_etat == 0 && dp2_obj->sub_etat == 38)
    {
        RayEvts.poing = false;
        RayEvts.unused_death = false;
        sinus_actif = 0;
        flammes_actives = 0;
        phase_dark2 = 0;
        TextDark2_Affiche = false;
        scroll_end_x = 0;
        scroll_start_x = 0;
        ToonJustGivePoing = 0;
        dark_obj->flags &= ~FLG(OBJ_ALIVE);
        dark_obj->flags &= ~FLG(OBJ_ACTIVE);
    }

    switch (phase_dark2)
    {
    case 0:
        if (sinus_actif == 0)
        {
            sinus_actif = 1;
            set_sub_etat(dp2_obj, 30);
        }
        else if (sinus_actif == 2)
            phase_dark2 = 1;
        break;
    case 1:
        if (flammes_actives == 0)
        {
            flammes_actives = 1;
            set_sub_etat(dp2_obj, 31);
        }
        else if (flammes_actives == 2)
        {
            if (
                level.objects[flamme_gauche_id].cmd == GO_NOP &&
                level.objects[flamme_droite_id].cmd == GO_NOP
            )
            {
                skipToLabel(&level.objects[flamme_droite_id], 2, true);
                skipToLabel(&level.objects[flamme_gauche_id], 2, true);
                phase_dark2 = 2;
            }
        }
        break;
    case 2:
        if (
            level.objects[flamme_gauche_id].cmd == GO_NOP &&
            level.objects[flamme_droite_id].cmd == GO_NOP
        )
        {
            phase_dark2 = 3;
            sinus_actif = 0;
        }
        break;
    case 3:
        if (sinus_actif == 0)
        {
            sinus_actif = 1;
            set_sub_etat(dp2_obj, 30);
        }
        else if (sinus_actif == 2)
            phase_dark2 = 4;
        break;
    case 4:
        skipToLabel(&level.objects[flamme_droite_id], 3, true);
        skipToLabel(&level.objects[flamme_gauche_id], 3, true);
        phase_dark2 = 5;
        break;
    case 5:
        if (
            level.objects[flamme_gauche_id].cmd == GO_NOP &&
            level.objects[flamme_droite_id].cmd == GO_NOP
        )
        {
            if (sinus_actif == 0)
            {
                sinus_actif = 1;
                set_sub_etat(dp2_obj, 30);
            }
            else if (sinus_actif == 2)
            {
                phase_dark2 = 6;
                sinus_actif = 0;
            }
        }
        else
            sinus_actif = 0;
        break;
    case 6:
        if (sinus_actif == 0)
        {
            skipToLabel(&level.objects[flamme_droite_id], 2, true);
            skipToLabel(&level.objects[flamme_gauche_id], 2, true);
            sinus_actif = 1;
            set_sub_etat(dp2_obj, 30);
        }
        else if (sinus_actif == 2)
        {
            if (
                level.objects[flamme_gauche_id].cmd == GO_NOP &&
                level.objects[flamme_droite_id].cmd == GO_NOP
            )
            {
                phase_dark2 = 7;
                sinus_actif = 0;
            }
        }
        break;
    case 7:
        if (dp2_obj->sub_etat != 33)
        {
            set_sub_etat(dp2_obj, 33);
            num_dark2_phrase = 0;
            TextDark2_Affiche = true;
        }
        else if (num_dark2_phrase == 2)
        {
            set_sub_etat(dp2_obj, 32);
            phase_dark2 = 8;
            TextDark2_Affiche = false;
        }
        break;
    case 8:
        skipToLabel(&level.objects[flamme_gauche_id], 4, true);
        phase_dark2 = 9;
        PosArXToon1 = -1;
        break;
    case 9:
        if (RayEvts.poing)
            phase_dark2 = 10;
        else
        {
            if (PosArXToon1 == -1 && level.objects[flamme_gauche_id].speed_x == 4)
            {
                AllocateToons();
                poing_obj = &level.objects[poing_obj_id];
                PosArXToon1 = poing_obj->x_pos + 64;
                PosArYToon1 = poing_obj->y_pos + 50;
                PosArXToon2 = poing_obj->x_pos + 48;
                PosArYToon2 = poing_obj->y_pos + 50;
            }
        }
        break;
    case 10:
        set_main_and_sub_etat(&level.objects[flamme_gauche_id], 0, 4);
        set_main_and_sub_etat(&level.objects[flamme_droite_id], 0, 4);
        phase_dark2 = 11;
        break;
    case 11:
        if (
            ToonJustGivePoing == 1 &&
            (block_flags[mp.map[ray.ray_dist] >> 10] >> BLOCK_SOLID & 1) &&
            !(ray.main_etat == 3 && ray.sub_etat == 23)
        )
        {
            ToonJustGivePoing = 2;
            set_main_and_sub_etat(&ray, 3, 23);
            ray.speed_x = 0;
            ray.speed_y = 0;
        }

        if (
            !(
                (level.objects[flamme_gauche_id].flags & FLG(OBJ_ACTIVE)) ||
                (dp2_obj->main_etat == 0 && dp2_obj->sub_etat == 34) ||
                (dp2_obj->main_etat == 2 && dp2_obj->sub_etat == 1) ||
                (ray.main_etat == 3 && ray.sub_etat == 23) ||
                ToonJustGivePoing != 2
            )
        )
        {
            ToonJustGivePoing = 0;
            set_main_and_sub_etat(dp2_obj, 0, 34);
        }
        else
        {
            if (dp2_obj->anim_frame == 4)
            {
                if (dp2_obj->main_etat == 0 && dp2_obj->sub_etat == 34)
                {
                    dp2_obj->speed_y = -4;
                    phase_dark2 = 12;
                    goto_phase3(dark_obj);
                }
            }
        }
        break;
    }

    if (dp2_obj->main_etat == 0)
    {
        switch (dp2_obj->sub_etat)
        {
        case 31:
            if (dp2_obj->anim_frame == 22)
            {
                GET_SPRITE_POS(dp2_obj, 3, &dp2_x, &dp2_y, &dp2_w, &dp2_h);
                dark2_rayon_dx_2 = 0;
                dark2_rayon_dx_1 = 0;
                dark2_rayon_dy_2 = -15;
                dark2_rayon_dy_1 = -15;
                ds2_x = dp2_x + (dp2_w >> 1) - 96;
                ds2_y = dp2_y + (dp2_h >> 1) - 128;
                allocate_DARK2_SORT(ds2_x, ds2_y, 37, 1);
                allocate_DARK2_SORT(ds2_x, ds2_y, 37, 0);
            }
            break;
        case 30:
            if (dp2_obj->anim_frame == 22)
            {
                GET_SPRITE_POS(dp2_obj, 3, &dp2_x, &dp2_y, &dp2_w, &dp2_h);
                dark2_rayon_dx_2 = -16;
                dark2_rayon_dx_1 = -16;
                dark2_rayon_dy_1 = 76;
                dark2_rayon_dy_2 = -76;
                sens_sinus_1 = 0;
                sens_sinus_2 = 1;
                PosXSin1 =
                PosXSin2 =
                    dp2_x + (dp2_w >> 1) - 96;
                PosYSin1 =
                PosYSin2 =
                    dp2_y + (dp2_h >> 1) - 128;
                allocate_DARK2_SORT(PosXSin1, PosYSin1, 35, 1);
                allocate_DARK2_SORT(PosXSin2, PosYSin2, 35, 0);
            }
            break;
        case 33:
            if (num_dark2_phrase == 0)
            {
                __builtin_memcpy(txt_dark2, s_youre_doomed_rayman__8012c1e4, sizeof(s_youre_doomed_rayman__8012c1e4));
                XText = SCREEN_WIDTH / 2;
                YText = -10;
                VitesseYText = 40;
                temps_text = 0;
                num_dark2_phrase = 1;
            }
            else
            {
                if (YText < -20)
                {
                    temps_text = 0;
                    XText = SCREEN_WIDTH / 2;
                    YText = -10;
                    VitesseYText = 40;
                    num_dark2_phrase++;
                }
                else
                {
                    YText += ashr16(VitesseYText, 4);
                    if (VitesseYText != 0)
                    {
                        if (horloge[4] == 0)
                            VitesseYText--;
                    }
                    else
                    {
                        if (horloge[6] == 0)
                            VitesseYText--;
                    }
                }
            }
            break;
        }
    }
}

/* 77778 8019BF78 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/dark_phase2", DO_DARK2_SORT_COMMAND);
#else
/*
attempts: 2
goto, sgn-like (not on android) garbage
*/
void DO_DARK2_SORT_COMMAND(Obj *ds2_obj)
{
    s16 unk_1;
    s32 unk_x_1;
    s16 unk_y_1;
    s16 unk_y_2;
    s16 unk_4;
    s16 unk_x_2;
    s32 unk_2;
    s16 unk_3;

    if (ds2_obj->hit_points != 0)
    {
        if (ds2_obj->sub_etat == 35 || ds2_obj->sub_etat == 36)
        {
            if (ds2_obj->x_pos < -ds2_obj->offset_bx)
            {
                sinus_actif = 2;
                ds2_obj->hit_points = 0;
            }
            else
            {
                if (ds2_obj->iframes_timer != 0)
                {
                    if (sens_sinus_1 != 0)
                    {
                        dark2_rayon_dy_1 += 3;
                        if (dark2_rayon_dy_1 > 76)
                            sens_sinus_1 = 0;
                    }
                    else
                    {
                        dark2_rayon_dy_1 -= 3;
                        if (dark2_rayon_dy_1 < -76)
                            sens_sinus_1 = 1;
                    }
                    PosXSin1 += ashr16(dark2_rayon_dx_1, 4);
                    unk_y_1 = PosYSin1 + ashr16(dark2_rayon_dy_1, 4);
                    PosYSin1 = unk_y_1;
                    if (ds2_obj->anim_frame == 1)
                    {
                        unk_x_1 = PosXSin1;
block_1:
                        allocate_DARK2_SORT(unk_x_1, unk_y_1, ds2_obj->sub_etat, ds2_obj->iframes_timer);
                        ds2_obj->hit_points = 0;
                    }
                }
                else
                {
                    if (sens_sinus_2 != 0)
                    {
                        dark2_rayon_dy_2 += 3;
                        if (dark2_rayon_dy_2 > 76)
                            sens_sinus_2 = 0;
                    }
                    else
                    {
                        dark2_rayon_dy_2 -= 3;
                        if (dark2_rayon_dy_2 < -76)
                            sens_sinus_2 = 1;
                    }
                    PosXSin2 += ashr16(dark2_rayon_dx_2, 4);
                    unk_y_1 = PosYSin2 + ashr16(dark2_rayon_dy_2, 4);
                    PosYSin2 = unk_y_1;
                    if (ds2_obj->anim_frame == 1)
                    {
                        unk_x_1 = PosXSin2;
                        goto block_1;
                    }
                }
            }
        }
        else if (ds2_obj->sub_etat == 37)
        {
            if (ds2_obj->iframes_timer != 0)
                unk_x_2 = 240 - (ds2_obj->x_pos + ds2_obj->offset_bx);
            else
                unk_x_2 = 5 - (ds2_obj->x_pos + ds2_obj->offset_bx);
            unk_y_2 = firstFloorBelow(ds2_obj) - (ds2_obj->y_pos + ds2_obj->offset_by);
            unk_1 = __builtin_abs(unk_x_2) + __builtin_abs(unk_y_2);

            if (unk_1 < 10)
            {
                ds2_obj->hit_points = 0;
                AllocateFlammes(ds2_obj->iframes_timer);
            }
            else
            {
                if (unk_1 > 0)
                {
                    unk_x_2 = ashl16(unk_x_2, 4) / unk_1;
                    unk_y_2 = ashl16(unk_y_2, 4) / unk_1;
                }

                if (ds2_obj->anim_frame == 1)
                {
                    if (ds2_obj->iframes_timer != 0)
                    {
                        dark2_rayon_dx_1 += SGN(unk_x_2 - dark2_rayon_dx_1);
                        dark2_rayon_dy_1 += SGN(unk_y_2 - dark2_rayon_dy_1);

                        allocate_DARK2_SORT(
                            ds2_obj->x_pos + dark2_rayon_dx_1,
                            ds2_obj->y_pos + dark2_rayon_dy_1,
                            ds2_obj->sub_etat,
                            ds2_obj->iframes_timer
                        );
                        ds2_obj->hit_points = 0;
                    }
                    else
                    {
                        dark2_rayon_dx_2 += SGN(unk_x_2 - dark2_rayon_dx_2);
                        dark2_rayon_dy_2 += SGN(unk_y_2 - dark2_rayon_dy_2);

                        allocate_DARK2_SORT(
                            ds2_obj->x_pos + dark2_rayon_dx_2,
                            ds2_obj->y_pos + dark2_rayon_dy_2,
                            ds2_obj->sub_etat,
                            ds2_obj->iframes_timer
                        );
                        ds2_obj->hit_points = 0;
                    }
                }
            }
        }
    }
}
#endif

/* 77C64 8019C464 -O2 -msoft-float */
void allocate_DARK2_SORT(s32 param_1, s16 param_2, s16 param_3, s16 param_4)
{
    Obj *temp_t6;
    Obj *cur_obj_1;
    Obj *cur_obj_2;
    Obj *cur_obj_3;
    Obj *var_a0_4;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 cnt_1;
    s16 check_1;
    s32 check_2;
    s32 check_3;
    Obj *var_v1_1;
    Obj *var_v1_2;
    Obj *var_v1_3;
    s16 nb_objs;
    int new_var;

    check_1 = 0;
    cnt_1 = 0;
    cur_obj_1 = level.objects;
    nb_objs = level.nb_objects;
    do
    {
        if ((cur_obj_1->type == 0x21) && !(cur_obj_1->flags & 0x800))
        {
            check_1 = 1;
        }
        cur_obj_1 += 1;
        cnt_1 = cnt_1 + 1;
    } while ((check_1 == 0) && (cnt_1 < nb_objs));
    cur_obj_1 = cur_obj_1 - 1;

    if (check_1 == 0)
        return;

    temp_t6 = cur_obj_1;
    check_1 = 0;
    do
    {
        if ((cur_obj_1->type == 0x21) && (cur_obj_1->flags & 0x800))
        {
            check_1 = 1;
        }
        cur_obj_1 += 1;
        cnt_1 = cnt_1 + 1;
    } while ((check_1 == 0) && (cnt_1 < nb_objs));
    cur_obj_1 = cur_obj_1 - 1;

    if (check_1 == 0)
    {
        check_1 = 1;
        cur_obj_1 = temp_t6;
    }
    else
    {
        check_1 = 0;
        do
        {
            if ((cur_obj_1->type == 0x21) && !(cur_obj_1->flags & 0x800))
            {
                check_1 = 1;
            }
            cur_obj_1 += 1;
            cnt_1 = cnt_1 + 1;
        } while ((check_1 == 0) && (cnt_1 < nb_objs));
        cur_obj_1 = cur_obj_1 - 1;
        if (check_1 == 0)
        {
            check_1 = 1;
            cur_obj_1 = temp_t6;
        }
    }

    if (check_1 == 0)
        return;
    
    cur_obj_1->flags |= 0xC00;
    cur_obj_1->x_pos = param_1;
    cur_obj_1->y_pos = param_2;
    cur_obj_1->hit_points = 1;
    cur_obj_1->iframes_timer = param_4;
    cur_obj_1->field23_0x3c = 0;
    set_main_and_sub_etat(cur_obj_1, 0, param_3);
}
