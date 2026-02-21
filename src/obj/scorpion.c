#include "obj/scorpion.h"

#ifdef BSS_DEFS
u8 ecroule_rubis_list[8];
u8 ecroule_plat_index;
s16 rubis_list_calculated;
s32 sko_ecran_tremble;
s16 sko_ecroule_plat;
u8 sko_enfonce_enable;
u8 sko_lave_obj[20];
u8 sko_nb_lave;
s16 sko_pince_obj_id;
s16 D_801E4E10;
s16 sko_rayon_on;
s16 sko_rayon_x;
s16 sko_rayon_y;
s16 sko_rayon_dx;
s16 sko_rayon_dy;
s16 sko_final_x;
s16 sko_final_y;
s32 pixels_enfonce;
s16 sko_last_action;
s16 sko_nb_frap;
s16 sko_nb_hit;
s16 sko_phase;
#endif

/* 6C6E4 80190EE4 -O2 -msoft-float */
void swap(s32 ind_1, s32 ind_2)
{
    u8 temp = ecroule_rubis_list[ind_1];
    ecroule_rubis_list[ind_1] = ecroule_rubis_list[ind_2];
    ecroule_rubis_list[ind_2] = temp;
}

/* 6C72C 80190F2C -O2 -msoft-float */
void set_rubis_list(void)
{
    s32 rubis_ind;
    s32 i;
    Obj *cur_obj;
    s32 nb_objs;
    ObjType type;
    s32 swapped;
    s32 j;
    u16 *mp_height;
    u8 *cur_lave_obj;

    rubis_list_calculated = true;
    rubis_ind = 0;
    sko_nb_lave = 0;
    i = 0;
    cur_obj = &level.objects[i];
    nb_objs = level.nb_objects;
    while (i < nb_objs)
    {
        type = cur_obj->type;
        if (type == TYPE_RUBIS)
        {
            ecroule_rubis_list[rubis_ind] = cur_obj->id;
            rubis_ind++;
        }
        else if (type == TYPE_SKO_PINCE)
            sko_pince_obj_id = i;
        else if (type == TYPE_LAVE)
        {
            sko_lave_obj[sko_nb_lave] = i;
            sko_nb_lave++;
        }
        i++;
        cur_obj++;
    }

    do
    {
        swapped = false;
        for (j = 0; j < (s16) LEN(ecroule_rubis_list) - 1; j++)
        {
            if (
                level.objects[ecroule_rubis_list[j]].x_pos >
                level.objects[ecroule_rubis_list[j + 1]].x_pos
            )
            {
                swap(j, j + 1);
                swapped = true;
            }
        }
    } while (swapped);

    if (ModeDemo != 0)
        ecroule_plat_index = 8;
    else
        ecroule_plat_index = (s16) myRand(177) % 3 << 3;
    sko_ecroule_plat = ecroule_rubis_list[ecroule_rubis_order[ecroule_plat_index]];
    sko_enfonce_enable = 0;

    mp.height = 32;
    ymapmax = scroll_end_y = 272;
    sko_ecran_tremble = 0;
    if (sko_nb_lave != 0)
    {
        mp_height = &mp.height; /* a little weird? */
        cur_lave_obj = &sko_lave_obj[0];
        do
        {
            level.objects[*cur_lave_obj].init_y_pos = *mp_height * 16 - 60;
            level.objects[*cur_lave_obj].y_pos = level.objects[*cur_lave_obj].init_y_pos;
            cur_lave_obj++;
        } while ((s32) cur_lave_obj < (s32) &sko_lave_obj[sko_nb_lave]);
    }
}

/* 6CA0C 8019120C -O2 -msoft-float */
void allocate_rayon(s16 x, s16 y)
{
    s16 found = false;
    s16 i = 0;
    Obj *cur_obj = &level.objects[i];
    u8 nb_objs = level.nb_objects;

    do
    {
        if (cur_obj->type == TYPE_RAYON && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
            found = true;
        cur_obj++;
        i++;
    } while (!found && i < nb_objs);
    i = 999; /* can also assign anything to nb_objs and it has same effect */
    if (found)
    {
        cur_obj--;
        cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
        cur_obj->flags &= ~(FLG(OBJ_FLAG_9));
        cur_obj->x_pos = x;
        cur_obj->y_pos = y;
        cur_obj->speed_x = 0;
        cur_obj->speed_y = 0;
        set_main_etat(cur_obj, 3);
        set_sub_etat(cur_obj, 0);
    }
}

/* 6CAE0 801912E0 -O2 -msoft-float */
void allocate_8_petits_rayons(s16 x, s16 y)
{
    Obj *found_obj;
    s16 i;
    Obj *rayon_obj;

    found_obj = allocateNOVA();
    if (found_obj != null)
    {
        found_obj->x_pos = x + 64;
        found_obj->y_pos = y + 64;
        found_obj->display_prio = 1;
        found_obj->field23_0x3c = 0;
        found_obj->flags |= FLG(OBJ_ACTIVE);
        calc_obj_pos_map(found_obj);
    }
    start_pix_gerbe(x + 140, y + 32);
    found_obj = findfirstObject(TYPE_RAYON);
    i = 0;
    rayon_obj = &found_obj[10];
    while (i < 8)
    {
        rayon_obj->x_pos = x + 8;
        rayon_obj->y_pos = y;
        rayon_obj->main_etat = 3;
        rayon_obj->sub_etat = 2;
        rayon_obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
        rayon_obj->speed_x = D_801C83A4[i];
        rayon_obj->speed_y = D_801C83B4[i];
        rayon_obj->anim_frame = 2;
        i++;
        rayon_obj++;
    }
}

/* 6CBF4 801913F4 -O2 -msoft-float */
void do_sko_rayon(void)
{
    Obj *ecroule_obj;
    s16 diff_x; s16 diff_y;
    s16 dist;
    s16 unk_1;

    if (sko_rayon_on != 0)
    {
        D_801E4E10 = 3;
        sko_rayon_on--;
        ecroule_obj = &level.objects[sko_ecroule_plat];

        diff_y = sko_final_y - sko_rayon_y;
        diff_x = sko_final_x - sko_rayon_x;
        dist = __builtin_abs(diff_x) + __builtin_abs(diff_y);
        if (dist < 8)
        {
            set_main_etat(ecroule_obj, 2);
            set_sub_etat(ecroule_obj, 2);
        }
        if (dist > 0)
        {
            diff_x = ashl16(diff_x, D_801E4E10) / dist;
            diff_y = ashl16(diff_y, D_801E4E10) / dist;
        }

        unk_1 = horloge[4] == 0 && sko_rayon_on < 50;
        if (unk_1)
        {
            sko_rayon_dx += SGN(diff_x - sko_rayon_dx);
            sko_rayon_dy += SGN(diff_y - sko_rayon_dy);
        }
        sko_rayon_x += sko_rayon_dx;
        sko_rayon_y += sko_rayon_dy;

        if (horloge[3] == 0 && dist != 0)
            allocate_rayon(sko_rayon_x, sko_rayon_y);
    }
}

/* 6CE8C 8019168C -O2 -msoft-float */
void do_sko_rayon2(void)
{
    Obj *poing_obj;
    s16 horl_zero;
    s16 diff_x; s16 diff_y;
    s16 dist;

    if (sko_rayon_on != 0)
    {
        sko_rayon_on--;
        if (poing.is_active)
        {
            D_801E4E10 = 3;
            poing_obj = &level.objects[poing_obj_id];
            sko_final_x = poing_obj->x_pos + poing_obj->offset_bx - 104;
            sko_final_y = poing_obj->y_pos + poing_obj->offset_hy - 120;
            horl_zero = horloge[2] == 0;
        }
        else
        {
            D_801E4E10 = 3;
            sko_final_x = ray.x_pos + ray.offset_bx - 120;
            sko_final_y = ray.y_pos + ray.offset_by - 140;
            horl_zero = horloge[8] == 0;
        }

        diff_y = sko_final_y - sko_rayon_y;
        diff_x = sko_final_x - sko_rayon_x;
        dist = __builtin_abs(diff_x) + __builtin_abs(diff_y);
        if (dist > 0)
        {
            diff_x = ashl16(diff_x, (u32) D_801E4E10) / dist;
            diff_y = ashl16(diff_y, (u32) D_801E4E10) / dist;
        }

        if (horl_zero)
        {
            sko_rayon_dx += SGN(diff_x - sko_rayon_dx);
            sko_rayon_dy += SGN(diff_y - sko_rayon_dy);
        }
        sko_rayon_x += sko_rayon_dx;
        sko_rayon_y += sko_rayon_dy;
        if (sko_rayon_x < -150)
        {
            sko_rayon_dx = -sko_rayon_dx;
            sko_rayon_x += sko_rayon_dx;
            sko_rayon_x += sko_rayon_dx;
        }

        horl_zero = horloge[3] == 0;
        if (horl_zero && dist != 0)
            allocate_rayon(sko_rayon_x, sko_rayon_y);

        if (sko_rayon_on == 0)
        {
            sko_rayon_x = -32000;
            sko_rayon_y = -32000;
        }
    }
}

/* 6D1D0 801919D0 -O2 -msoft-float */
void start_sko_rayon(s16 obj_x, s16 obj_y)
{
    Obj *ecroule_obj;

    ecroule_plat_index++;
    sko_ecroule_plat = ecroule_rubis_list[ecroule_rubis_order[ecroule_plat_index]];
    ecroule_obj = &level.objects[sko_ecroule_plat];
    if (sko_rayon_on != 0xFF)
        sko_rayon_on = 60;
    sko_rayon_x = obj_x - 80;
    sko_rayon_dx = -4;
    sko_rayon_y = obj_y - 10;
    sko_rayon_dy = 4;
    sko_final_x = ecroule_obj->offset_bx + ecroule_obj->x_pos - 120;
    sko_final_y = ecroule_obj->offset_hy + ecroule_obj->y_pos - 120;
    allocate_rayon(sko_rayon_x, sko_rayon_y);
}

/* 6D2E0 80191AE0 -O2 -msoft-float */
void start_sko_rayon2(s16 obj_x, s16 obj_y)
{
    Obj *final_obj;

    if (poing.is_active)
        final_obj = &level.objects[poing_obj_id];
    else
        final_obj = &ray;
    sko_rayon_on = 120;
    sko_rayon_x = obj_x - 80;
    sko_rayon_dx = -4;
    sko_rayon_y = obj_y - 10;
    sko_rayon_dy = 2;
    sko_final_x = final_obj->offset_bx + final_obj->x_pos - 120;
    sko_final_y = final_obj->offset_hy + final_obj->y_pos - 120;
    allocate_rayon(sko_rayon_x, sko_rayon_y);
}

/* 6D3B4 80191BB4 -O2 -msoft-float */
void lance_pince(Obj *sko_obj)
{
    Obj *pince_obj = &level.objects[sko_pince_obj_id];
    pince_obj->flags |= FLG(OBJ_ALIVE);
    pince_obj->x_pos = sko_obj->x_pos;
    pince_obj->y_pos = sko_obj->y_pos;
    pince_obj->speed_x = -128;
    pince_obj->speed_y = 0;
    calc_obj_pos_map(pince_obj);
}

/* 6D424 80191C24 -O2 -msoft-float */
s32 sko_get_eject_sens(void)
{
    ray.iframes_timer = 40;
    return -1;
}

/* 6D438 80191C38 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/scorpion", DO_SOL_ENFONCE);
#else
/*
attempts: 2
goto (partially gotos-only)
*/
void DO_SOL_ENFONCE(void)
{
    u8 bVar1;
    int iVar2;
    s16 iVar3;

    if (((ray_mode == MODE_MORT_DE_RAYMAN) || ((ray.main_etat == 2 && (ray.sub_etat == 9)))) ||
        ((ray.main_etat == 3 && ((ray.sub_etat == 0x17 || (ray.sub_etat == 0x34))))))
    {
        sko_enfonce_enable = 0;
        pixels_enfonce = 0;
    }
    if (sko_ecran_tremble != 0)
    {
        sko_ecran_tremble--;
        if (horloge[4] >= 2)
            xmap += 2;
        else
            xmap -= 2;
    }
    if (!(pixels_enfonce < 0x60 && sko_enfonce_enable == 1))
    {
        if (pixels_enfonce < 0xC4 && sko_enfonce_enable == 2)
        {
            goto block_19;
        }
    }
    else if (pixels_enfonce < 0x60 && sko_enfonce_enable == 1 && horloge[2] != 0)
    {
block_19:
        if (((s16) sko_enfonce_enable == 2) && (horloge[4] == 0))
        {
            goto block_21;
        }
    }
    else if (pixels_enfonce < 0x60 && sko_enfonce_enable == 1 && horloge[2] == 0)
    {
block_21:
        if (horloge[4] >= 2)
        {
            xmap += 3;
        }
        else
        {
            xmap -= 3;
        }
        ymapmax = ymapmax + -1;
        scroll_end_y = scroll_end_y + -1;
        pixels_enfonce = pixels_enfonce + 1;
        iVar3 = 0;
        if ((pixels_enfonce & 0xf) == 0)
        {
            mp.height = mp.height + -1;
        }
        iVar2 = 0;
        if (sko_nb_lave != 0)
        {
            do
            {
                iVar2 = iVar2 >> 0x10;
                level.objects[sko_lave_obj[iVar3]].y_pos = level.objects[sko_lave_obj[iVar3]].y_pos + -1;
                level.objects[sko_lave_obj[iVar3]].init_y_pos =
                    level.objects[sko_lave_obj[iVar3]].init_y_pos + -1;
                if ((sko_enfonce_enable == 1) && (horloge[10] == 0))
                {
                    level.objects[sko_lave_obj[iVar3]].y_pos = level.objects[sko_lave_obj[iVar3]].y_pos + -1;
                    level.objects[sko_lave_obj[iVar3]].init_y_pos =
                        level.objects[sko_lave_obj[iVar3]].init_y_pos + -1;
                }
                iVar3 = iVar3 + 1;
            } while (iVar3 < sko_nb_lave);
        }
    }
    if ((pixels_enfonce == 0x60) && (sko_enfonce_enable == 1))
    {
        pixels_enfonce = 0;
        sko_enfonce_enable = 0;
        sko_ecran_tremble = 0x3c;
    }
    if ((pixels_enfonce == 0xc4) && (sko_enfonce_enable == 2))
    {
        pixels_enfonce = 0;
        sko_enfonce_enable = 0;
        sko_ecran_tremble = 0x3c;
    }
}
#endif

/* 6D7FC 80191FFC -O2 -msoft-float */
void DO_SKO_PHASE_0(Obj *sko_obj)
{
    s16 sko_sub_etat = sko_obj->sub_etat;
    Obj *ecroule_obj = &level.objects[sko_ecroule_plat];
    if (sko_obj->main_etat == 0 && sko_sub_etat >= 2)
    {
        if (sko_sub_etat >= 4)
        {
            if (sko_sub_etat == 4 && sko_obj->anim_frame == 27 && screen_trembling == 0)
            {
                screen_trembling = 1;
                sko_nb_frap++;
                if (ecroule_obj->sub_etat == 7)
                {
                    set_main_etat(ecroule_obj, 2);
                    set_sub_etat(ecroule_obj, 2);
                    ecroule_plat_index++;
                    sko_ecroule_plat = ecroule_rubis_list[ecroule_rubis_order[ecroule_plat_index]];
                }
                if (sko_nb_frap == sko_sub_etat)
                    skipToLabel(sko_obj, 4, true);
                if (sko_nb_frap == 5)
                {
                    sko_nb_frap = 0;
                    sko_nb_hit = 0;
                    sko_phase++;
                    skipToLabel(sko_obj, 5, true);
                    ecroule_plat_index--;
                }
            }
        }
        else
        {
            if (sko_last_action == 4)
            {
                set_sub_etat(sko_obj, 8);
                sko_last_action = 8;
            }
            else
            {
                set_sub_etat(sko_obj, 4);
                skipToLabel(sko_obj, 3, true);
                sko_last_action = 4;
            }
        }
    }
}

/* 6D9FC 801921FC -O2 -msoft-float */
void DO_SKO_PHASE_1(Obj *obj)
{
    s16 sub_etat = obj->sub_etat;
    if (
        obj->main_etat == 0 && sub_etat == 4 &&
        obj->anim_frame == 27 && screen_trembling == 0
    )
    {
        screen_trembling = 1;
        sko_nb_frap++;
        if (ray.main_etat == 5)
        {
            set_main_etat(&ray, 2);
            set_sub_etat(&ray, 2);
        }
        if (sko_nb_frap == 3)
        {
            sko_rayon_on = 0;
            sko_phase++;
            skipToLabel(obj, 6, true);
            sko_nb_frap = 0;
            obj->anim_frame = 0;
        }
    }
}

/* 6DAF0 801922F0 -O2 -msoft-float */
void DO_SKO_PHASE_2(Obj *obj)
{
    s16 main_etat = obj->main_etat;
    s16 sub_etat = obj->sub_etat;
    do_sko_rayon();
    switch (main_etat)
    {
    case 0:
        switch (sub_etat)
        {
        case 4:
            switch (sko_nb_frap)
            {
            case 0:
                if (obj->anim_frame == 27)
                {
                    sko_nb_frap++;
                    sko_enfonce_enable = 1;
                }
                break;
            case 1:
                if (obj->anim_frame == 27)
                {
                    sko_nb_frap++;
                    screen_trembling = 1;
                }
                break;
            }
            break;
        case 2:
        case 3:
            set_sub_etat(obj, 5);
            break;
        case 7:
            if (obj->anim_frame == 9 && sko_rayon_on == 0)
            {
                start_sko_rayon(obj->x_pos, obj->y_pos);
                if (++sko_nb_frap == 5)
                {
                    skipToLabel(obj, 7, true);
                    sko_nb_frap = 0;
                    sko_phase++;
                }
            }
            break;
        }
        break;
    default:
        if (
            main_etat == 1 && sub_etat == 15 &&
            obj->nb_cmd == sko_nb_hit
        )
            obj->nb_cmd = 0;
        break;
    }
}

/* 6DCC0 801924C0 -O2 -msoft-float */
void DO_SKO_PHASE_3(Obj *obj)
{
    s16 main_etat = obj->main_etat;
    s16 sub_etat = obj->sub_etat;
    do_sko_rayon();
    switch (main_etat)
    {
    case 0:
        switch (sub_etat)
        {
        case 4:
            if (obj->anim_frame == 27 && sko_nb_frap == 1)
            {
                sko_nb_frap++;
                sko_enfonce_enable = 2;
            }
            break;
        case 2:
            if (sko_nb_frap == 0)
            {
                sko_nb_frap++;
                skipToLabel(obj, 11, true);
            }
            else if (sko_nb_frap == 2)
            {
                set_main_etat(obj, 1);
                set_sub_etat(obj, 15);
                obj->speed_x = 3;
            }
            break;
        }
        break;
    }
}

/* 6DDC0 801925C0 -O2 -msoft-float */
void DO_SKO_PINCE(Obj *obj)
{
    u8 sub_etat;
    s32 pince_id;

    if (obj->main_etat == 0)
    {
        sub_etat = obj->sub_etat;
        if (sub_etat == 8)
        {
            if (obj->anim_frame == 65)
            {
                lance_pince(obj);
                set_sub_etat(obj, 9);
                skipToLabel(obj, 9, true);
            }
        }
        else if (sub_etat == 9)
        {
            pince_id = sko_pince_obj_id;
            level.objects[pince_id].speed_x += 2;
            if (-level.objects[pince_id].speed_x == -110)
                set_sub_etat(obj, 10);
        }
        else if (sub_etat == 10 && obj->anim_frame == 7)
        {
            pince_id = sko_pince_obj_id;
            level.objects[pince_id].flags &= ~FLG(OBJ_ALIVE);
            level.objects[pince_id].x_pos = -32000;
            level.objects[pince_id].y_pos = -32000;
        }
    }
}

/* 6DF18 80192718 -O2 -msoft-float */
void DO_SCORPION_COLLISION(Obj *obj)
{
    s16 iVar1 = -1;
    s16 rayon_x = sko_rayon_x + 120;
    s16 rayon_y = sko_rayon_y + 120;

    s16 unk_1 = 11;
    if (!(obj->main_etat == 0 && (obj->sub_etat == unk_1 || obj->sub_etat == 12)))
    {
        iVar1 = BOX_IN_COLL_ZONES(
            TYPE_SCORPION,
            rayon_x, rayon_y,
            16, 16,
            obj
        );
    }

    if (iVar1 != -1)
    {
        set_sub_etat(obj, 11);
        allocate_8_petits_rayons(sko_rayon_x, sko_rayon_y);
        sko_rayon_x = 33536;
        sko_rayon_y = 33536;
        sko_rayon_on = 0;
        obj->hit_points--;
        if (obj->hit_points == 1)
            skipToLabel(obj, 13, true);
        if (obj->hit_points == 0)
            set_sub_etat(obj, 12);
    }
}

/* 6E034 80192834 -O2 -msoft-float */
void DO_SCORPION_MORT(Obj *obj)
{
    finBosslevel.mr_skops = true;
    if (
        obj->main_etat == 0 && obj->sub_etat == 12 &&
        obj->anim_frame > 126
    )
    {
        obj->anim_frame = 129;
        fin_boss = true;
        TEST_SIGNPOST();
    }
}

/* 6E0B0 801928B0 -O2 -msoft-float */
void DO_SKO(Obj *obj)
{
    s16 main_etat = obj->main_etat;
    s16 sub_etat = obj->sub_etat;
    Obj *cur_obj;
    s16 i;
    u8 nb_objs;

    if (main_etat == 0 && sub_etat == 1)
    {
        if (obj->anim_frame == 0)
            PlaySnd(172, obj->id);
        if (obj->anim_frame == 50)
            PlaySnd(173, obj->id);
        if (obj->anim_frame == 100)
            PlaySnd(177, obj->id);
    }

    if (num_level == 10)
    {
        DO_ONE_CMD(obj);
        if (!rubis_list_calculated)
            set_rubis_list();
        DO_SKO_PINCE(obj);
        DO_SOL_ENFONCE();
        if ((obj->x_pos + obj->offset_bx < ray.x_pos) && ray_mode != MODE_MORT_DE_RAYMAN)
            RAY_HIT(true, obj);
        switch (sko_phase)
        {
        case 0:
            DO_SKO_PHASE_0(obj);
            break;
        case 1:
            DO_SKO_PHASE_1(obj);
            break;
        case 2:
            DO_SKO_PHASE_2(obj);
            break;
        case 3:
            DO_SKO_PHASE_3(obj);
            break;
        }
    }
    else if (num_level == 11)
    {
        if (!rubis_list_calculated)
        {
            scrollLocked = true;
            obj->hit_points = obj->init_hit_points;
            cur_obj = level.objects;
            i = 0;
            nb_objs = level.nb_objects;
            while (i < nb_objs)
            {
                if (cur_obj->type == TYPE_SKO_PINCE)
                {
                    sko_pince_obj_id = i;
                    break;
                }
                cur_obj++;
                i++;
            }
            skipToLabel(obj, 12, true);
            set_main_etat(obj, 0);
            set_sub_etat(obj, 5);
            rubis_list_calculated = true;
            sko_phase = 4;
        }
        DO_ONE_CMD(obj);
        do_sko_rayon2();
        DO_SKO_PINCE(obj);
        DO_SCORPION_COLLISION(obj);
        DO_SCORPION_MORT(obj);
        if (main_etat == 0)
        {
            switch (sub_etat)
            {
            case 7:
                if (obj->anim_frame == 9 && sko_rayon_on == 0)
                {
                    sko_rayon_on = 0xFF;
                    start_sko_rayon2(obj->x_pos, obj->y_pos);
                }
                break;
            case 2:
            case 3:
                if (sko_last_action == 5)
                {
                    set_sub_etat(obj, 8);
                    sko_last_action = 8;
                }
                else
                {
                    set_sub_etat(obj, 5);
                    sko_last_action = 5;
                }
                break;
            }
        }
    }
}

/* 6E3F0 80192BF0 -O2 -msoft-float */
void SKO_ray_in_zone(Obj *obj)
{
    s16 main_etat = obj->main_etat;
    s16 sub_etat = obj->sub_etat;
    switch (sko_phase)
    {
    case 0:
        if (main_etat == 0)
        {
            switch (sub_etat)
            {
            case 0:
                set_sub_etat(obj, 1);
                skipToLabel(obj, 2, true);
                sko_nb_frap = 0;
                break;
            case 2:
            case 3:
                set_sub_etat(obj, 4);
                skipToLabel(obj, 3, true);
                break;
            }
        }
        break;
    case 1:
        break;
    case 2:
    case 3:
        break;
    }
}

/* 6E4A4 80192CA4 -O2 -msoft-float */
void DO_SKO_HIT(Obj *obj)
{
    s16 main_etat = obj->main_etat;
    s16 sub_etat = obj->sub_etat;
    switch (sko_phase)
    {
    case 0:
        if (main_etat == 0)
        {
            switch (sub_etat)
            {
            case 0:
                set_sub_etat(obj, 1);
                skipToLabel(obj, 2, true);
                obj->change_anim_mode = ANIMMODE_NONE;
                obj->anim_frame = 81;
                sko_nb_frap = 0;
                break;
            case 1:
                MAX_2(obj->anim_frame, 81);
                break;
            case 2:
            case 3:
                set_sub_etat(obj, 4);
                skipToLabel(obj, 3, true);
                break;
            }
        }
        break;
    case 1:
        if (main_etat == 0)
        {
            obj->x_pos += 2;
            sko_nb_hit++;
            switch (sub_etat)
            {
            case 2:
            case 3:
                obj->nb_cmd = 0;
                break;
            }
        }
        break;
    case 2:
    case 3:
        break;
    }
}