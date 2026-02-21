#include "obj/saxo.h"

#ifdef BSS_DEFS
SaxData Sax;
s16 IndexSerie;
s16 SaxMarche;
u8 NextNote;
s16 IndexAtak;
SaxAttackEntry attaque;
u8 NiveauDansPhase;
#endif

/* 50CDC 801754DC -O2 -msoft-float */
void INIT_SAXO(Obj *sax_obj)
{
    sax_obj->y_pos = firstFloorBelow(sax_obj) - sax_obj->offset_by;
    calc_obj_pos_map(sax_obj);
    sax_obj->speed_x = 0;
    sax_obj->speed_y = 0;
    Phase = 0;
    IsBossThere = false;
    IndexSerie = 0;
    sax_obj->flags = (sax_obj->flags | FLG(OBJ_ALIVE)) & ~FLG(OBJ_ACTIVE);
    if (sax_obj->type == TYPE_SAXO)
        sax_obj->hit_points = Sax.saved_hp;
    Sax.coup = 0;
    SaxMarche = 0;
    Sax.field10_0x10 = 0;
}

/* TODO: param_2 */
/* 50D7C 8017557C -O2 -msoft-float */
void allocateNote2(Obj *note_obj, s16 param_2)
{
    Obj *cur_obj;
    s16 i;
    u8 nb_objs;
    u8 offs_half;
    u16 offs_x;

    if (note_obj->iframes_timer > 0)
    {
        cur_obj = level.objects;
        i = 0;
        nb_objs = level.nb_objects;
        if (nb_objs != 0)
        {
            do
            {
                if (cur_obj->type == TYPE_NOTE2 && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
                {
                    cur_obj->flags &= ~FLG(OBJ_FLIP_X);
                    cur_obj->speed_y = 0;
                    cur_obj->speed_x = 0;

                    offs_half = note_obj->offset_bx / 2;
                    offs_x = offs_half;
                    if (param_2 != 0)
                        offs_x = -offs_half;
                    cur_obj->x_pos = offs_x + note_obj->x_pos;
                    cur_obj->y_pos = note_obj->y_pos;

                    cur_obj->main_etat = 0;
                    cur_obj->sub_etat = param_2 + 2;
                    cur_obj->init_x_pos = cur_obj->x_pos;
                    cur_obj->init_y_pos = cur_obj->y_pos;
                    skipToLabel(cur_obj, 1, true);
                    calc_obj_pos_map(cur_obj);
                    cur_obj->flags = (cur_obj->flags | FLG(OBJ_ALIVE)) & ~FLG(OBJ_FLAG_9) | FLG(OBJ_ACTIVE);
                    cur_obj->gravity_value_1 = 0;
                    cur_obj->iframes_timer = note_obj->iframes_timer - 1;
                    calc_obj_pos_map(cur_obj);
                    cur_obj->field23_0x3c = 10;
                    allocateExplosion(cur_obj);
                    break;
                }
                cur_obj++;
                i++;
            } while (i < nb_objs);
        }
    }
}

/* 50EE0 801756E0 -O2 -msoft-float */
void DO_EXPLOSE_NOTE2(Obj *obj)
{
    obj->speed_x = 0;
    obj->speed_y = 0;
    calc_obj_pos_map(obj);
    set_main_and_sub_etat(obj, 0, 1);
    PlaySnd(0xf6, obj->id);
    allocateExplosion(obj);
    obj->field23_0x3c = 10;
    obj->iframes_timer = 3;
}

/* 50F40 80175740 -O2 -msoft-float */
void DO_NOTE_CMD(Obj *obj)
{
    s16 calc_x;
    s32 offs_x;
    u8 var_v1;
    u8 temp_v0_2;

    switch (obj->type)
    {
    case TYPE_NOTE3:
        if (obj->speed_x == 0)
        {
            calc_x = obj->offset_bx + obj->x_pos - Sax.note_box_coll_x;
            if (calc_x < 20)
            {
                set_main_and_sub_etat(obj, 2, 0);
                obj->speed_x = 3;
                obj->flags |= FLG(OBJ_FLIP_X);
            }
            else if (calc_x < 200)
            {
                /* vibrate back and forth the closer sax gets */
                var_v1 = (calc_x >> 3) - 2;
                offs_x = 1;
                if (var_v1 < 2)
                    var_v1 = 2;
                temp_v0_2 = var_v1;
                if (calc_x < 50)
                    offs_x = 2;

                if (horloge[temp_v0_2] < (temp_v0_2 / 2))
                    obj->x_pos = obj->init_x_pos + offs_x;
                else
                    obj->x_pos = obj->init_x_pos;
            }
        }
        break;
    case TYPE_NOTE2:
        if (obj->main_etat == 0)
        {
            obj->field23_0x3c--;
            if (obj->field23_0x3c == 0)
            {
                switch (obj->sub_etat)
                {
                case 1:
                    allocateNote2(obj, 1);
                    /* fall through */
                case 2:
                    allocateNote2(obj, 0);
                    obj->flags &= ~FLG(OBJ_ACTIVE);
                    obj->flags &= ~FLG(OBJ_ALIVE);
                    break;
                case 3:
                    allocateNote2(obj, 1);
                    obj->flags &= ~FLG(OBJ_ACTIVE);
                    obj->flags &= ~FLG(OBJ_ALIVE);
                    break;
                }
            }
        }
        break;
    case TYPE_BONNE_NOTE:
        if (
            inter_box(
                obj->x_pos + obj->offset_bx - 8,
                obj->y_pos + obj->offset_by - 8,
                16,
                16,
                Sax.note_box_coll_x,
                Sax.note_box_coll_y,
                20,
                140
            )
        )
        {
            if (Sax.coup == 0)
                Sax.coup = 1;
            obj->flags &= ~FLG(OBJ_ACTIVE);
            obj->flags &= ~FLG(OBJ_ALIVE);
            obj->y_pos += 30;
            PlaySnd(0xF3, obj->id);
            allocateExplosion(obj);
        }
        break;
    }
}

/* 511C4 801759C4 -O2 -msoft-float */
void Cree_Eclat_Note(Obj *bnote, Obj *note1, s16 index)
{
    s16 speed_x;

    if (bnote->type == TYPE_BNOTE)
    {
        if (bnote->flags & FLG(OBJ_ACTIVE))
        {
            do
            {
                bnote++;
                if (bnote->type != TYPE_BNOTE)
                    return;
            } while (bnote->flags & FLG(OBJ_ACTIVE));
        }
    }

    if (bnote->type == TYPE_BNOTE)
    {
        if (index < 4)
        {
            bnote->flags = (bnote->flags & ~FLG(OBJ_FLIP_X)) | ((index % 2) & 1) << OBJ_FLIP_X;
            if (index < 2)
                bnote->speed_y = -1;
            else
                bnote->speed_y = 1;

            if (bnote->flags & FLG(OBJ_FLIP_X))
                speed_x = 1;
            else
                speed_x = -1;
            bnote->speed_x = speed_x;
        }
        else
        {
            bnote->flags = (bnote->flags & ~FLG(OBJ_FLIP_X)) | ((index % 2) & 1) << OBJ_FLIP_X;
            switch (index)
            {
            case 4:
                bnote->speed_y = 0;
                bnote->speed_x = -2;
                break;
            case 5:
                bnote->speed_x = 2;
                bnote->speed_y = 0;
                break;
            case 6:
                bnote->speed_x = 0;
                bnote->speed_y = -2;
                break;
            case 7:
                bnote->speed_x = 0;
                bnote->speed_y = 2;
                break;
            }
        }
        bnote->x_pos = note1->x_pos;
        bnote->y_pos = note1->y_pos;
        bnote->main_etat = 2;
        bnote->sub_etat = 5;
        skipToLabel(bnote, 1, true);
        calc_obj_pos_map(bnote);
        bnote->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
        calc_obj_pos_map(bnote);
    }
}

/* 513AC 80175BAC -O2 -msoft-float */
void DO_EXPLOSE_NOTE1(Obj *obj)
{
    Obj *cur_obj;
    s16 i;
    u8 nb_objs_1;
    u8 nb_objs_2;

    cur_obj = level.objects;
    i = 0;
    nb_objs_1 = level.nb_objects;
    if (nb_objs_1 != 0)
    {
        nb_objs_2 = nb_objs_1;
        do
        {
            if (cur_obj->type == TYPE_BNOTE && !(cur_obj->flags & FLG(OBJ_ACTIVE)))
            {
                PlaySnd(0xf4, obj->id);
                allocateExplosion(obj);
                Cree_Eclat_Note(cur_obj, obj, 0);
                cur_obj++;
                Cree_Eclat_Note(cur_obj, obj, 1);
                cur_obj++;
                Cree_Eclat_Note(cur_obj, obj, 2);
                cur_obj++;
                Cree_Eclat_Note(cur_obj, obj, 3);
                cur_obj++;
                Cree_Eclat_Note(cur_obj, obj, 4);
                cur_obj++;
                Cree_Eclat_Note(cur_obj, obj, 5);
                cur_obj++;
                Cree_Eclat_Note(cur_obj, obj, 6);
                cur_obj++;
                Cree_Eclat_Note(cur_obj, obj, 7);
                obj->flags &= ~FLG(OBJ_ACTIVE);
                obj->flags &= ~FLG(OBJ_ALIVE);
                break;
            }
            cur_obj++;
            i++;
        } while (i < nb_objs_2);
    }
}

/* 514F4 80175CF4 -O2 -msoft-float */
void BonneNote(Obj *orig_obj)
{
    Obj *obj;
    s16 i;
    u8 nb_objs;
    s16 speed_x;

    obj = level.objects;
    i = 0;
    nb_objs = level.nb_objects;
    if (nb_objs != 0)
    {
        do
        {
            if (obj->type == TYPE_BONNE_NOTE && !(obj->flags & FLG(OBJ_ACTIVE)))
            {
                if (orig_obj->speed_x == 0)
                {
                    obj->flags &= ~FLG(OBJ_FLIP_X);
                    obj->speed_x = -1;
                    obj->speed_y = -4;
                    obj->gravity_value_2 = 10;
                    obj->field23_0x3c = 2;
                }
                else
                {
                    speed_x = 4;
                    if (level.objects[poing_obj_id].speed_x < 0)
                        speed_x = -4;
                    obj->speed_x = speed_x;
                    if (speed_x < 0)
                        obj->flags &= ~FLG(OBJ_FLIP_X);
                    else
                        obj->flags |= FLG(OBJ_FLIP_X);
                    obj->gravity_value_2 = 0xff;
                    obj->field23_0x3c = 1;
                    obj->speed_y = -1;
                }
                obj->x_pos = orig_obj->x_pos;
                obj->y_pos = orig_obj->y_pos;
                obj->main_etat = 2;
                obj->sub_etat = 3;
                obj->init_x_pos = obj->x_pos;
                skipToLabel(obj, 1, true);
                calc_obj_pos_map(obj);
                obj->gravity_value_1 = 0;

                obj->flags |= (FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE));
                obj->iframes_timer = 200;
                orig_obj->flags &= ~FLG(OBJ_ACTIVE);
                orig_obj->flags &= ~FLG(OBJ_ALIVE);
                calc_obj_pos_map(obj);
                break;
            }
            obj++;
            i++;
        } while (i < nb_objs);
    }
}

/* 516B4 80175EB4 -O2 -msoft-float */
void DO_NOTE_TOUCHEE(Obj *obj)
{
    switch (obj->type)
    {
    case TYPE_NOTE0:
    case TYPE_NOTE3:
        BonneNote(obj);
        break;
    case TYPE_NOTE1:
        DO_EXPLOSE_NOTE1(obj);
        break;
    case TYPE_BONNE_NOTE:
        obj->speed_x += level.objects[poing_obj_id].speed_x;
        obj->speed_y = -1;
        obj->gravity_value_2 = 0xFF;
        obj->field23_0x3c = 1;
        break;
    }
}

/* 51774 80175F74 -O2 -msoft-float */
void DO_NOTE_REBOND(Obj *obj)
{
    switch (obj->type)
    {
    case TYPE_NOTE2:
        DO_EXPLOSE_NOTE2(obj);
        break;
    case TYPE_NOTE0:
    case TYPE_NOTE3:
    case TYPE_BONNE_NOTE:
        obj->speed_y = -__builtin_abs(obj->speed_y);
        if (obj->speed_y > -3)
            obj->speed_y--;

        obj->gravity_value_1 = 10 - obj->gravity_value_1;
        calc_obj_pos_map(obj);
        break;
    }
}

/* 51828 80176028 -O2 -msoft-float */
void allocateNote(Obj *obj)
{
    Obj *note_obj;
    s16 i;
    u8 nb_objs_1;
    u8 nb_objs_2;

    note_obj = level.objects;
    i = 0;
    nb_objs_1 = level.nb_objects;
    if (nb_objs_1 != 0)
    {
        nb_objs_2 = nb_objs_1;
        do
        {
            if ((note_obj->type == atak[NextNote].type + TYPE_NOTE0))
            {
                if (!(note_obj->flags & FLG(OBJ_ACTIVE)))
                {
                    note_obj->flags = note_obj->flags & ~FLG(OBJ_FLIP_X) | obj->flags & FLG(OBJ_FLIP_X);
                    note_obj->speed_y = atak[NextNote].speed_y;
                    if (note_obj->flags & FLG(OBJ_FLIP_X))
                    {
                        note_obj->speed_x = atak[NextNote].speed_x;
                        note_obj->x_pos = Sax.sprite2_x + 0x17 - note_obj->offset_bx;
                    }
                    else
                    {
                        note_obj->speed_x = -atak[NextNote].speed_x;
                        note_obj->x_pos = Sax.sprite2_x + 9 - note_obj->offset_bx;
                    }
                    note_obj->y_pos = (Sax.sprite2_y - note_obj->offset_by) + 0x19;
                    note_obj->main_etat = 2;
                    note_obj->sub_etat = atak[NextNote].type;
                    skipToLabel(note_obj, 1, true);
                    calc_obj_pos_map(note_obj);
                    note_obj->flags = (note_obj->flags | FLG(OBJ_ALIVE)) & ~FLG(OBJ_FLAG_9) | FLG(OBJ_ACTIVE);
                    note_obj->gravity_value_1 = 0;
                    note_obj->gravity_value_2 = 10;
                    note_obj->iframes_timer = atak[NextNote].initial_iframes;
                    calc_obj_pos_map(note_obj);
                    break;
                }
            }
            note_obj++;
            i++;
        } while (i < nb_objs_2);
    }
}

/* 51A30 80176230 -O2 -msoft-float */
u8 PrepareAtak(void)
{
    s16 is = IndexSerie;
    s16 ia = IndexAtak;

    attaque.next_note = SerieDatak[is][ia].next_note;
    attaque.time = SerieDatak[is][ia].time;
    attaque.end = SerieDatak[is][ia].end;
    if (attaque.end)
        IndexAtak = 0;
    else
        IndexAtak++;

    return attaque.next_note;
}

/* 51AE0 801762E0 -O2 -msoft-float */
void SAXO_TIRE(Obj *obj)
{
    if (obj->type == TYPE_SAXO)
    {
        if (NextNote > 6)
            NextNote--;
        allocateNote(obj);
        WaitForFinAtan = attaque.time + 1;
        NextNote = PrepareAtak();
    }
    else
    {
        NextNote = 0;
        allocateNote(obj);
    }
}

/* 51B80 80176380 -O2 -msoft-float */
void DO_SAXO_COUP(Obj *obj)
{
    u8 hp;

    if (Phase != 100)
    {
        hp = --obj->hit_points;
        if (hp != 0)
        {
            if (obj->main_etat != 2)
            {
                Sax.field8_0xe = obj->main_etat;
                Sax.field9_0xf = obj->sub_etat;
                set_main_and_sub_etat(obj, 0, 3);
                Sax.coup = 2;
            }
            else
                Sax.coup = 0;

            IndexSerie++;
            if (IndexSerie >= 4)
                IndexSerie = 3;
            else
                IndexAtak = 0;
            NextNote = PrepareAtak();
        }
        else
            Sax.coup = 0;
    }
}

/* 51C7C 8017647C -O2 -msoft-float */
void DO_SAXO2_COUP(Obj *obj)
{
    switch (Phase)
    {
    case 1:
        obj->hit_points--;
        if (obj->init_hit_points - obj->hit_points >= 3)
            Phase = 2;
        FinAnim = false;
        set_sub_etat(obj, 3);
        Sax.coup = 2;
        break;
    case 2:
        obj->hit_points--;
        Sax.coup = 0;
        break;
    case 3:
        set_main_and_sub_etat(obj, 0, 3);
        obj->speed_x = 0;
        obj->hit_points--;
        FinAnim = false;
        Sax.coup = 2;
        break;
    }
}

/* 51D7C 8017657C -O2 -msoft-float */
void SetSaxoCollNoteBox(Obj *obj)
{
    s16 x2; s16 y2; s16 w2; s16 h2;
    s16 x5; s16 y5; s16 w5; s16 h5;

    GET_SPRITE_POS(obj, 2, &x2, &y2, &w2, &h2);
    GET_SPRITE_POS(obj, 5, &x5, &y5, &w5, &h5);
    Sax.note_box_coll_y = y5 + 20;
    Sax.note_box_coll_x = x2 + ((w2 - 20) >> 1);
}

/* 51E0C 8017660C -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj/saxo", DO_SAXO_COMMAND);
#else
/* gotos */
void DO_SAXO_COMMAND(Obj *obj)
{
    s16 sp18;
    s16 sp1A;
    s16 temp_a0;
    s16 temp_v0_2;
    s16 temp_v1_7;
    s16 var_a0;
    s16 var_a0_2;
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v1;
    s16 var_v1_2;
    s16 var_v1_3;
    s32 temp_lo_1;
    s32 temp_lo_2;
    s32 temp_s0;
    s32 temp_v1_9;
    u16 temp_v0;
    u16 temp_v0_3;
    s16 temp_v1_1;
    u32 temp_a3;
    s16 temp_v1_8;
    u8 temp_a1;
    s16 temp_s2;
    s16 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_6;
    int new_var;
    s16 *speed_y;

    new_var = 0x20;
    scrollLocked = 1;
    GET_SPRITE_POS(obj, 2, &Sax.sprite2_x, &Sax.sprite2_y, &sp18, &sp1A);
    if (obj->flags & 0x4000)
    {
        Sax.sprite2_x = Sax.sprite2_x - new_var + sp18;
    }
    Sax.sprite2_x += 0xC;
    Sax.sprite2_y += 0xC;
    Sax.x_pos = obj->x_pos;
    Sax.y_pos = obj->y_pos;
    SetSaxoCollNoteBox(obj);
    if ((obj->hit_points == 0) && (Phase != 0x64))
    {
        Sax.coup = 0;
        if (
            (block_flags[
                mp.map[
                    (s16) (((obj->x_pos + obj->offset_bx) >> 4) +
                    (mp.width * ((obj->y_pos + obj->offset_by) >> 4)))
                ] >> 10
            ] >> BLOCK_SOLID & 1)
        )
        {
            obj->anim_frame = 0xFF;
            set_main_and_sub_etat(obj, 0U, 4U);
            skipToLabel(obj, 0, 1);
            Phase = 0x64;
            Sax.field10_0x10 = 0x01A4;
            obj->speed_x = 0;
            obj->speed_y = 0;
        }
    }
    if (Sax.coup == 1)
    {
        DO_SAXO_COUP(obj);
        FinAnim = 0;
    }
    else
    {
        if (
            obj->anim_frame == (obj->animations[obj->anim_index].frames_count - 1) &&
            horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0
        )
        {
            FinAnim = 1;
            WaitForAnim = 0;
        }
        else
        {
            FinAnim = 0;
        }
    }

    temp_v1_1 = obj->x_pos;
    switch (Phase)
    {
    case 0:
        if ((obj->main_etat != 0) || (obj->sub_etat != 0))
        {
            if ((ray.x_pos < (temp_v1_1 + 0xDC)) && (temp_v1_1 < (ray.x_pos + 0x6E)))
            {
                WaitForAnim = 1;
            }
            else
            {
                set_main_and_sub_etat(obj, 0U, 2U);
            }
            if ((WaitForAnim != 0) && (FinAnim != 0))
            {
                Phase = 1;
                NiveauDansPhase = 1;
                IndexAtak = 0;
                IndexSerie = 0;
                NextNote = PrepareAtak();
                set_main_and_sub_etat(obj, 0U, 1U);
            }
        }
        break;
    case 1:
        temp_s0 = ((u32) obj->flags >> 0xE) & 1;
        calc_obj_dir(obj);
        if ((((u32) obj->flags >> 0xE) & 1) != temp_s0)
        {
            set_main_and_sub_etat(obj, 0U, 0U);
            obj->speed_x = 0;
            FinAnim = 0;
        }
        switch (obj->sub_etat)
        {
        case 1:
            if ((horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0) && ((temp_v1_3 = obj->anim_frame, (temp_v1_3 == 0x18)) || ((temp_v1_3 == 0x1C) && (WaitForFinAtan == 0)) || ((temp_v1_3 == 0x20) && (WaitForFinAtan == 0))))
            {
                SAXO_TIRE(obj);
            }
            break;
        case 3:
            if (FinAnim != 0)
            {
                Sax.coup = 0;
            }
            break;
        case 2:
            if (FinAnim != 0)
            {
                if (WaitForFinAtan < 2U)
                {
                    switch (attaque.next_note)
                    {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        set_sub_etat(obj, 1U);
                        break;
                    case 7:
                        set_main_and_sub_etat(obj, 0U, 0x0AU);
                        Phase = 2;
                        Sax.field10_0x10 = 3;
                        break;
                    case 8:
                        set_main_and_sub_etat(obj, 0U, 0x0AU);
                        Phase = 3;
                        Sax.field10_0x10 = 2;
                        break;
                    case 9:
                        set_main_and_sub_etat(obj, 0U, 0x0AU);
                        Phase = 4;
                        break;
                    }
                }
                else
                {
                    WaitForFinAtan--;
                }
            }
            break;
        case 0:
            if (FinAnim != 0)
            {
                set_sub_etat(obj, 1U);
                NextNote = PrepareAtak();
            }
            break;
        }
        break;
    case 2:
        if (FinAnim != 0 && obj->main_etat == 0 && obj->sub_etat == 3)
        {
            set_main_and_sub_etat(obj, Sax.field8_0xe, Sax.field9_0xf);
            Sax.coup = 0;
            FinAnim = 0;
        }

        if (obj->main_etat == 0)
        {
            if (
                !(obj->flags & 0x4000) ?
                    obj->x_pos + obj->offset_bx < 0 :
                    obj->x_pos + obj->offset_bx > xmapmax + SCREEN_WIDTH
            )
                obj->speed_x = 0;

            if (FinAnim != 0)
            {
                switch (obj->sub_etat)
                {
                case 10:
                    obj->gravity_value_2 = 5;
                    obj->gravity_value_1 = 0;
                    obj->speed_y = -6;
                    obj->y_pos += obj->speed_y;
                    var_a0 = -1;
                    if (obj->flags & 0x4000)
                    {
                        var_a0 = 1;
                    }
                    obj->speed_x = var_a0;
                    break;
                case 11:
                    if (--Sax.field10_0x10 > 0)
                    {
                        set_main_and_sub_etat(obj, 0U, 0x0AU);
                        obj->speed_x = 0;
                    }
                    else
                    {
                        set_main_and_sub_etat(obj, 1U, 0U);
                        var_v1_3 = -2;
                        if (obj->flags & 0x4000)
                        {
                            var_v1_3 = 2;
                        }
                        obj->speed_x = var_v1_3;
                    }
                }
            }
        }
        else if (obj->main_etat == 1)
        {
block_666:
            if (
                !(obj->flags & 0x4000) ?
                    (obj->x_pos + 0x40) < 0 :
                    (obj->x_pos + 0xC0) > (xmapmax + 0x140)
            )
            {
                obj->flags = (obj->flags & ~0x4000) | (((1 - ((obj->flags >> 0xE) & 1)) & 1) << 0xE);
                set_main_and_sub_etat(obj, 0U, 0U);
                obj->speed_x = 0;
                Phase = 1;
            }
        }
        break;
    case 3:
        if (FinAnim != 0 && obj->main_etat == 0 && obj->sub_etat == 3)
        {
            set_main_and_sub_etat(obj, Sax.field8_0xe, Sax.field9_0xf);
            Sax.coup = 0;
            FinAnim = 0;
        }

        if (obj->main_etat == 0)
        {
            if (
                !(obj->flags & 0x4000) ?
                    obj->x_pos + obj->offset_bx < 0 :
                    obj->x_pos + obj->offset_bx > xmapmax + SCREEN_WIDTH
            )
                obj->speed_x = 0;

            if (FinAnim != 0)
            {
                switch (obj->sub_etat)
                {
                case 10:
                    obj->gravity_value_2 = 5;
                    obj->gravity_value_1 = 0;
                    obj->speed_y = -6;
                    obj->y_pos += obj->speed_y;
                    var_a0 = -1;
                    if (obj->flags & 0x4000)
                    {
                        var_a0 = 1;
                    }
                    obj->speed_x = var_a0;
                    break;
                case 11:
                    Sax.field10_0x10 -= 1;
                    set_main_and_sub_etat(obj, 1U, 0U);
                    var_v1_2 = -2;
                    if (obj->flags & 0x4000)
                    {
                        var_v1_2 = 2;
                    }
                    obj->speed_x = var_v1_2;
                    obj->iframes_timer = 0x001E;
                    break;
                }
            }
            break;
        }
        else if (obj->main_etat == 1)
        {
            if (Sax.field10_0x10 != 1)
            {
                goto block_666;
            }
            if (--obj->iframes_timer <= 0)
            {
                set_main_and_sub_etat(obj, 0U, 0x0AU);
                obj->speed_x = 0;
            }
        }
        break;
    case 4:
        if (FinAnim != 0 && obj->main_etat == 0 && obj->sub_etat == 3)
        {
            set_main_and_sub_etat(obj, Sax.field8_0xe, Sax.field9_0xf);
            Sax.coup = 0;
            FinAnim = 0;
        }

        if (obj->main_etat == 0)
        {
            if (
                !(obj->flags & 0x4000) ?
                    obj->x_pos + obj->offset_bx < 0 :
                    obj->x_pos + obj->offset_bx > xmapmax + SCREEN_WIDTH
            )
                obj->speed_x = 0;

            if (FinAnim != 0)
            {
                switch (obj->sub_etat)
                {
                case 10:
                    obj->gravity_value_2 = 5;
                    obj->gravity_value_1 = 0;
                    temp_v1_8 = (ray.x_pos - 0x30);
                    temp_v1_8 = obj->x_pos - temp_v1_8;
                    var_a0_2 = temp_v1_8;
                    if (temp_v1_8 < 0)
                    {
                        var_a0_2 = -temp_v1_8;
                    }
                    if (var_a0_2 >= 0x65)
                    {
                        obj->speed_y = var_a0_2 / 20;
                        if (obj->speed_y > 9)
                        {
                            obj->speed_y = 9;
                        }
                        else if (obj->speed_y < 4)
                        {
                            obj->speed_y = 4;
                        }
                        var_v1_3 = -2;
                        if (obj->flags & 0x4000)
                        {
                            var_v1_3 = 2;
                        }
                        obj->speed_x = var_v1_3;
                    }
                    else
                    {
                        obj->speed_y = var_a0_2 / (s32) 10;
                        if (obj->speed_y > 9)
                        {
                            obj->speed_y = 9;
                        }
                        else if (obj->speed_y < 4)
                        {
                            obj->speed_y = 4;
                        }
                        var_v1_3 = -1;
                        if (obj->flags & 0x4000)
                        {
                            var_v1_3 = 1;
                        }
                        obj->speed_x = var_v1_3;
                    }

                    obj->y_pos = obj->y_pos - obj->speed_y;
                    obj->speed_y = -obj->speed_y;
                    break;
                case 11:
                    if (!(obj->flags & 0x4000))
                    {
                        goto block_140;
                    }
                    if ((obj->x_pos + 0x30) < ray.x_pos)
                    {
                        goto block_142;
                    }
                    goto block_145;
block_140:
                    if (ray.x_pos < (obj->x_pos + 0x30))
                    {
                        goto block_142;
                    }
                    goto block_143;
block_142:
                    set_main_and_sub_etat(obj, 0U, 0x0AU);
                    break;
block_143:
                    if ((obj->x_pos + 0x40) < 0)
                    {
                        goto block_155;
                    }
                    goto block_147;
block_145:
                    if ((obj->x_pos + 0xC0) > (xmapmax + 0x140))
                    {
                        goto block_155;
                    }
                    goto block_147;
block_147:
                    set_main_and_sub_etat(obj, 1U, 0U);
                    var_v1_3 = -2;
                    if (obj->flags & 0x4000)
                    {
                        var_v1_3 = 2;
                    }
                    obj->speed_x = var_v1_3;
                    break;
                }
            }
        }
        else if (obj->main_etat == 1)
        {
            if (
                !(obj->flags & 0x4000) ?
                    (obj->x_pos + 0x40) < 0 :
                    (obj->x_pos + 0xC0) > (xmapmax + 0x140)
            )
            {
block_155:
                obj->flags = (obj->flags & ~0x4000) | (((1 - ((obj->flags >> 0xE) & 1)) & 1) << 0xE);
                set_main_and_sub_etat(obj, 0U, 0U);
                obj->speed_x = 0;
                Phase = 1;
            }
        }
        break;
    case 0x64:
        if (--Sax.field10_0x10 <= 0)
        {
            Sax.field10_0x10 = 0x03E7;
            fin_boss = 1;
            finBosslevel.mr_sax = true;
        }
        break;
    }

    temp_v1_9 = obj->x_pos + obj->offset_bx + obj->speed_x;
    if ((temp_v1_9 < 0) || ((xmapmax + 0x13F) < temp_v1_9))
    {
        obj->speed_x = 0;
    }
}
#endif

/* 52BC4 801773C4 -O2 -msoft-float */
void DO_SAXO_ATTER(Obj *obj)
{
    if (obj->speed_y > 0)
    {
        CALC_MOV_ON_BLOC(obj);
        screen_trembling = 1;
        set_main_and_sub_etat(obj, 0, 11);
        obj->speed_x = 0;
        obj->speed_y = 0;
        allocateLandingSmoke(obj);
    }
}

/* 52C28 80177428 -O2 -msoft-float */
void DO_SAXO2_COMMAND(Obj *obj)
{
    s16 sprite_w;
    s16 sprite_h;
    u16 temp_x;
    s16 x_pos;
    u8 anim_frame;
    s32 main_etat;
    s32 offs_x;
    u8 should_dec;
    s32 next_x;

    scrollLocked = true;
    GET_SPRITE_POS(obj, 2, &Sax.sprite2_x, &Sax.sprite2_y, &sprite_w, &sprite_h);
    if (obj->flags & FLG(OBJ_FLIP_X))
    {
        temp_x = Sax.sprite2_x - 32;
        Sax.sprite2_x = temp_x + sprite_w;
    }
    Sax.sprite2_x += 12;
    Sax.sprite2_y += 12;
    Sax.x_pos = obj->x_pos;
    Sax.y_pos = obj->y_pos;
    SetSaxoCollNoteBox(obj);
    if (Sax.coup == 1)
        DO_SAXO2_COUP(obj);
    if (
        obj->anim_frame == (obj->animations[obj->anim_index].frames_count - 1) &&
        horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0
    )
    {
        FinAnim = true;
        WaitForAnim = false;
    }
    else
        FinAnim = false;

    x_pos = obj->x_pos;
    if (xmapmax < ray.x_pos + 150 && (mp.height * 16 - 110) < ray.y_pos)
        Sax.saved_hp = obj->hit_points;

    switch (Phase)
    {
    case 0:
        CALC_MOV_ON_BLOC(obj);
        if (ray.x_pos < x_pos + 220 && ray.x_pos + 220 > x_pos)
            WaitForAnim = true;

        if (WaitForAnim && FinAnim)
        {
            Phase = 1;
            WaitForFinAtan = 2;
            NiveauDansPhase = 0;
            set_main_and_sub_etat(obj, 0, 1);
        }
        break;
    case 1:
        switch (obj->sub_etat)
        {
        case 1:
            if (horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0)
            {
                anim_frame = obj->anim_frame;
                if (
                    anim_frame == 24 ||
                    (anim_frame == 28 && NiveauDansPhase >= 2) ||
                    (anim_frame == 32 && NiveauDansPhase >= 4)
                )
                {
                    SAXO_TIRE(obj);
                    NiveauDansPhase++;
                }
            }
            break;
        case 2:
            if (FinAnim)
            {
                if (WaitForFinAtan < 2)
                    set_sub_etat(obj, 1);
                else
                    WaitForFinAtan--;
            }
            break;
        case 3:
            if (FinAnim)
                Sax.coup = 0;
            break;
        }
        break;
    case 2:
        switch (obj->sub_etat)
        {
        case 3:
            if (FinAnim)
            {
                Sax.coup = 0;
                set_main_and_sub_etat(obj, 0, 0xA);
            }
            break;
        case 10:
            if (FinAnim)
            {
                obj->gravity_value_2 = 5;
                obj->gravity_value_1 = 0;
                obj->speed_y = -6;
                obj->speed_x = -1;
                obj->y_pos -= 6;
                Sax.field10_0x10 = 2;
            }
            break;
        case 11:
            if (FinAnim)
            {
                if (obj->x_pos < ray.x_pos - 50)
                {
                    /* TODO: last part is obj->flags ^ (1 << OBJ_FLIP_X) ? */
                    obj->flags = (obj->flags & ~FLG(OBJ_FLIP_X)) | (((1 - ((obj->flags >> OBJ_FLIP_X) & 1)) & 1) << OBJ_FLIP_X);
                    set_sub_etat(obj, 0);
                    Phase = 3;
                }
                else
                    set_main_and_sub_etat(obj, 0, 0xA);
            }
            break;
        }
        break;
    case 3:
        /* TODO: m2c output was switch */
        main_etat = obj->main_etat;
        if (main_etat != 1)
        {
            if (main_etat < 2 && main_etat == 0 && FinAnim)
            {
                switch (obj->sub_etat)
                {
                case 0:
                case 2:
                case 3:
                case 11:
                    set_main_and_sub_etat(obj, 1, 0);
                    obj->speed_x = Sax.field10_0x10;
                    Sax.coup = 0;
                    break;
                case 10:
                    set_main_and_sub_etat(obj, 2, 1);
                    obj->anim_frame = obj->gravity_value_2;
                    obj->gravity_value_2 = 5;
                    obj->gravity_value_1 = 0;
                    obj->speed_y = -7;
                    obj->speed_x = 2;
                    obj->y_pos -= 7;
                    break;
                }
            }
        }
        else
        {
            offs_x = obj->offset_bx + 50;
            /* TODO: shifts/div? */
            if (
                !(block_flags[
                    mp.map[
                        (s16)(((obj->x_pos + offs_x) >> 4) +
                        (mp.width * ((obj->y_pos + obj->offset_by + 8) >> 4)))
                    ] >> 10
                ] >> BLOCK_SOLID & 1)
            )
            {
                set_main_and_sub_etat(obj, 0, 0xA);
                obj->speed_x = 0;
            }
            else if (xmap < obj->x_pos + 150)
            {
                if (Sax.field10_0x10 == 2)
                {
                    if (horloge[2] != 0)
                    {
                        obj->speed_x = 1;
                        should_dec = horloge[4] < 2;
                    }
                    else
                    {
                        obj->speed_x = 2;
                        break;
                    }
                }
                else
                {
                    obj->speed_x = 1;
                    should_dec = horloge[2];
                }

                if (should_dec != 0)
                    obj->anim_frame--;
            }
            else
                obj->speed_x = 2;
            break;
        }
    }
    next_x = obj->x_pos + obj->offset_bx + obj->speed_x;
    if (next_x < 0 || (xmapmax + SCREEN_WIDTH - 1) < next_x)
        obj->speed_x = 0;
}

/* 533C8 80177BC8 -O2 -msoft-float */
void DO_SAXO2_ATTER(Obj *obj)
{
    switch (Phase)
    {
    case 2:
    case 3:
        if (obj->speed_y > 0)
        {
            CALC_MOV_ON_BLOC(obj);
            screen_trembling3 = 1;
            set_main_and_sub_etat(obj, 0, 11);
            obj->speed_x = 0;
            obj->speed_y = 0;
            allocateLandingSmoke(obj);
        }
        break;
    }
}

/* 53448 80177C48 -O2 -msoft-float */
void DO_SAXO_MARCHE(s16 hp)
{
    Sax.field10_0x10 = hp + 1;
}

/* 5345C 80177C5C -O2 -msoft-float */
void DO_SAXO3_COMMAND(Obj *obj)
{
    s16 sprite_w;
    s16 sprite_h;
    u16 temp_x;
    s32 temp_flags;

    GET_SPRITE_POS(obj, 2, &Sax.sprite2_x, &Sax.sprite2_y, &sprite_w, &sprite_h);
    if (obj->flags & FLG(OBJ_FLIP_X))
    {
        temp_x = Sax.sprite2_x - 32;
        Sax.sprite2_x = temp_x + sprite_w;
    }
    Sax.sprite2_x += 12;
    Sax.sprite2_y += 12;
    Sax.x_pos = obj->x_pos;
    Sax.y_pos = obj->y_pos;
    SetSaxoCollNoteBox(obj);
    if (Phase == 2 && obj->main_etat == 0 && obj->sub_etat != 0)
        Phase = 0;
    if (
        obj->anim_frame == (obj->animations[obj->anim_index].frames_count - 1) &&
        horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0
    )
    {
        FinAnim = true;
        WaitForAnim = false;
    }
    else
        FinAnim = false;

    switch (Phase)
    {
    case 0:
        break;
    case 1:
        switch (obj->sub_etat)
        {
        case 1:
            if ((obj->anim_frame == 24) && (horloge[obj->eta[obj->main_etat][obj->sub_etat].anim_speed & 0xF] == 0))
                SAXO_TIRE(obj);
            if (FinAnim)
            {
                /* TODO: see DO_SAXO2_COMMAND also */
                temp_flags = (obj->flags & ~FLG(OBJ_FLIP_X)) | (((1 - ((obj->flags >> OBJ_FLIP_X) & 1)) & 1) << OBJ_FLIP_X);
                obj->flags = temp_flags;
                set_sub_etat(obj, 0);
                Phase++;
            }
            break;
        case 3:
            if (FinAnim)
                Sax.coup = 0;
            break;
        }
        break;
    case 2:
        if (FinAnim && obj->sub_etat == 0)
        {
            obj->speed_x = 2;
            set_main_and_sub_etat(obj, 1, 0);
        }
        break;
    }
}

/* 53758 80177F58 -O2 -msoft-float */
void DO_SAXO3_DEBUT(Obj *obj)
{
    if (Phase == 0)
    {
        Phase = 1;
        WaitForFinAtan = 1;
        set_main_and_sub_etat(obj, 0, 1);
    }
}

/* 5379C 80177F9C -O2 -msoft-float */
s32 saxo2_get_eject_sens(void)
{
    if (Phase <= 1)
        return -1;
    else
        return 1;
}