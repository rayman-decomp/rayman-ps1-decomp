#include "obj_init_kill.h"

#ifdef BSS_DEFS
LevelData level;

ActiveObjects actobj;
s16 rayman_obj_id;
u8 IsBossThere;
#endif

/* 2A07C 8014E87C -O2 -msoft-float */
s32 Prio(Obj *obj)
{
    s32 res;

    switch (obj->type)
    {
    case TYPE_EAU:
    case TYPE_MEDAILLON_TOON:
        res = 1;
        break;
    case TYPE_AUDIOSTART:
    case TYPE_SPACE_MAMA:
    case TYPE_BLACK_RAY:
    case TYPE_SPACE_MAMA2:
    case TYPE_ANNULE_SORT_DARK:
    case TYPE_POING_FEE:
    case TYPE_DUNE:
        res = 0;
        break;
    case TYPE_MST_SCROLL:
        res = (obj->hit_points == 0) * 2;
        break;
    case TYPE_BOUM:
    case TYPE_SPLASH:
    case TYPE_PHOTOGRAPHE:
    case TYPE_OUYE:
    case TYPE_MOVE_OUYE:
    case TYPE_FLAMME2:
    case TYPE_STALAG:
    case TYPE_CAGE:
    case TYPE_CAGE2:
    case TYPE_STONECHIP:
    case TYPE_EXPLOSION:
    case TYPE_NOTE0:
    case TYPE_NOTE1:
    case TYPE_NOTE2:
    case TYPE_BONNE_NOTE:
    case TYPE_BNOTE:
    case TYPE_PI_BOUM:
    case TYPE_ECLAIR:
    case TYPE_BLACKTOON1:
    case TYPE_ETINC:
    case TYPE_NOVA2:
    case TYPE_FLASH:
    case TYPE_CLE_SOL:
    case TYPE_SCORPION:
    case TYPE_WIZ:
    case TYPE_CYMBAL1:
    case TYPE_RAYON:
    case TYPE_PIERREACORDE:
    case TYPE_CFUMEE:
    case TYPE_STOSKO_PINCE:
    case TYPE_LAVE:
    case TYPE_SKO_PINCE:
        res = 2;
        break;
    case TYPE_ONOFF_PLAT:
    case TYPE_CLASH:
    case TYPE_BB1:
    case TYPE_DARD:
    case TYPE_PIRATE_NGAWE:
    case TYPE_RING:
    case TYPE_SAXO:
    case TYPE_PIRATE_GUETTEUR:
    case TYPE_PIRATE_BOMB:
    case TYPE_MARACAS:
    case TYPE_BBL:
    case TYPE_TNT_BOMB:
    case TYPE_SUPERHELICO:
    case TYPE_ROULETTE:
    case TYPE_ROULETTE2:
    case TYPE_ROULETTE3:
    case TYPE_SAXO2:
    case TYPE_SAXO3:
    case TYPE_MAMA_PIRATE:
    case TYPE_COUTEAU:
    case TYPE_BB12:
    case TYPE_BB13:
    case TYPE_BB14:
    case TYPE_SMA_WEAPON:
    case TYPE_BOUT_TOTEM:
    case TYPE_PIRATE_GUETTEUR2:
    case TYPE_RIDEAU:
        res = 3;
        break;
    case TYPE_PLANCHES:

        if (bateau_obj_id != -1)
            res = 4;
        else
            res = 7;
        break;
    case TYPE_MORNINGSTAR:
    case TYPE_GENEBADGUY:
    case TYPE_PI:
    case TYPE_PI_MUS:
    case TYPE_WASHING_MACHINE:
    case TYPE_VAGUE_DEVANT:
        res = 5;
        break;
    case TYPE_POWERUP:
    case TYPE_MUS_WAIT:
    case TYPE_JAUGEUP:
    case TYPE_POING_POWERUP:
    case TYPE_REDUCTEUR:
    case TYPE_ONEUP:
    case TYPE_GRAP_BONUS:
    case TYPE_BATEAU:
        res = 6;
        break;
    case TYPE_NEUTRAL:
    case TYPE_SIGNPOST:
    case TYPE_TAMBOUR2:
    case TYPE_VAGUE_DERRIERE:
        res = 7;
        break;
    default:
        res = 4;
        break;
    }

    return res;
}

/* 2A12C 8014E92C -O2 -msoft-float */
void first_obj_init(Obj *obj)
{
    ObjType type = obj->type;

    if (
        flags[type].flags0 & FLG(OBJ0_ALWAYS) ||
        (
            (type == TYPE_BADGUY1 || type == TYPE_BADGUY2) &&
            obj->x_pos < 0
        )
    )
    {
        obj->x_pos = -32000;
        obj->y_pos = -32000;
    }
    obj->scale = 0;
    obj->active_flag = ACTIVE_DEAD;
    obj->init_x_pos = obj->x_pos;
    obj->init_y_pos = obj->y_pos;
    obj->init_main_etat = obj->main_etat;
    obj->init_sub_etat = obj->sub_etat;
    obj->init_hit_points = obj->hit_points;

    switch (obj->type)
    {
    case TYPE_SPACE_MAMA:
    case TYPE_SPACE_MAMA2:
        findMereDenisWeapon();
        obj->field24_0x3e = 0;
        break;
    case TYPE_FEE:
        obj->detect_zone = 200;
        obj->field24_0x3e = 0;
        break;
    case TYPE_TROMPETTE:
    case TYPE_MITE2:
        obj->detect_zone = 160;
        obj->field24_0x3e = 0;
        break;
    case TYPE_MOSKITO:
    case TYPE_MOSKITO2:
    case TYPE_WIZARD1:
    case TYPE_SPIDER:
        obj->detect_zone = 60;
        obj->field24_0x3e = 0;
        break;
    case TYPE_CHASSEUR1:
    case TYPE_CHASSEUR2:
    case TYPE_GENEBADGUY:
    case TYPE_SAXO3:
        obj->detect_zone = 180;
        obj->field24_0x3e = 0;
        break;
    case TYPE_STONEWOMAN:
    case TYPE_STONEWOMAN2:
    case TYPE_BIG_CLOWN:
    case TYPE_MITE:
        obj->detect_zone = 220;
        obj->field24_0x3e = 0;
        break;
    case TYPE_STONEMAN1:
    case TYPE_STONEDOG:
    case TYPE_STONEMAN2:
    case TYPE_MUS_WAIT:
    case TYPE_PIRATE_NGAWE:
    case TYPE_BATTEUR_FOU:
    case TYPE_STONEDOG2:
        obj->detect_zone = 100;
        obj->field24_0x3e = 0;
        break;
    case TYPE_PIRATE_POELLE:
    case TYPE_PIRATE_P_45:
        obj->detect_zone = 150;
        obj->field24_0x3e = 0;
        break;
    case TYPE_PIRATE_POELLE_D:
    case TYPE_PIRATE_P_D_45:
        obj->detect_zone = 50;
        obj->field24_0x3e = 0;
        break;
    case TYPE_CLOWN_TNT:
        obj->detect_zone = 200;
        obj->field24_0x3e = 0;
        break;
    case TYPE_STALAG:
        obj->detect_zone = 250;
        obj->field24_0x3e = 0;
        break;
    case TYPE_CYMBALE:
    case TYPE_CYMBAL1:
    case TYPE_CYMBAL2:
        obj->detect_zone = 0;
        obj->field24_0x3e = 0;
        break;
    case TYPE_BAG1:
        obj->field23_0x3c = 0;
        obj->field24_0x3e = 0;
        break;
    case TYPE_SCORPION:
        obj->detect_zone = 160;
        obj->field24_0x3e = 0;
        break;
    case TYPE_WAT_CLOWN:
    case TYPE_MAMA_PIRATE:
        obj->detect_zone = 150;
        obj->field24_0x3e = 0;
        break;
    case TYPE_DARK_PHASE2:
    case TYPE_DARK:
        obj->detect_zone = 150;
        obj->field24_0x3e = 0;
        break;
    default:
        obj->detect_zone = 40;
        obj->field24_0x3e = 0;
        break;
    }
}

/* 2A2A0 8014EAA0 -O2 -msoft-float */
void obj_init(Obj *obj)
{
    s16 unk_1;
    s16 unk_2;

    obj->nb_cmd = 0;
    obj->flags &= ~FLG(OBJ_ACTIVE);
    obj->display_prio = Prio(obj);
    obj->zdc = type_zdc[obj->type];
    if (obj->type != TYPE_INDICATOR)
    {
        obj->main_etat = obj->init_main_etat;
        obj->sub_etat = obj->init_sub_etat;
    }
    obj->anim_frame = 0;
    obj->speed_x = 0;
    obj->speed_y = 0;
    obj->x_pos = obj->init_x_pos;
    obj->y_pos = obj->init_y_pos;
    obj->anim_index = obj->eta[obj->main_etat][obj->sub_etat].anim_index;
    obj->flags &= ~FLG(OBJ_FLIP_X);
    obj->change_anim_mode = ANIMMODE_NONE;
    obj->gravity_value_1 = 0;
    obj->gravity_value_2 = 0;
    obj->detect_zone_flag = 0;
    obj->iframes_timer = -1;
    obj->field20_0x36 = -1;
    obj->cmd_offset = -1;
    unk_1 = obj->cmds != null;
    obj->flags = (obj->flags & ~FLG(OBJ_READ_CMDS)) | (unk_1 << OBJ_READ_CMDS);
    memset(obj->btypes, 0, 5);
    GET_OBJ_CMD(obj);
    obj->test_block_index = 0;
    obj->cmd_context_index = 0xFF;
    obj->active_flag = ACTIVE_DEAD;
    obj->timer = 0;
    obj->field56_0x69 = 0;
    obj->hit_points = obj->init_hit_points;
    obj->flags &= ~FLG(OBJ_FLAG_9);
    obj->flags &= ~FLG(OBJ_FLAG_A);
    obj->flags &= ~FLG(OBJ_FLAG_B);

    switch (obj->type)
    {
    case TYPE_SAXO:
    case TYPE_SAXO2:
    case TYPE_SAXO3:
        INIT_SAXO(obj);
        break;
    case TYPE_PRI:
        if (finBosslevel.helped_joe_2)
        {
            prise_branchee = true;
            set_main_and_sub_etat(obj, 0, 2);
            obj->init_sub_etat = 2;
            skipToLabel(obj, 1, true);
            break;
        }
        break;
    case TYPE_VAGUE_DEVANT:
    case TYPE_VAGUE_DERRIERE:
        obj->x_pos = obj->init_x_pos = -15;
        break;
    case TYPE_HYBRIDE_MOSAMS:
        bossXToReach = obj->x_pos;
        bossYToReach = firstFloorBelow(&ray) - obj->offset_by + 16;
        bossSpeedFactor = 0x4000;
        alternateBossSpeedFactor = 0;
        break;
    case TYPE_CRAYON_BAS:
    case TYPE_CRAYON_HAUT:
        obj->anim_frame = myRand(obj->animations[obj->anim_index].frames_count - 1);
        break;
    case TYPE_FALLING_CRAYON:
    case TYPE_PUNAISE4:
        obj->anim_frame = obj->hit_points;
        break;
    case TYPE_PUNAISE1:
    case TYPE_PUNAISE2:
    case TYPE_PUNAISE3:
    case TYPE_PUNAISE5:
        obj->flags = (obj->flags & ~FLG(OBJ_FLIP_X)) | (obj->hit_points & 1) << OBJ_FLIP_X;
        break;
    case TYPE_MST_FRUIT1:
    case TYPE_MST_SHAKY_FRUIT:
        obj->gravity_value_2 = 5;
        break;
    case TYPE_MST_FRUIT2:
        obj->gravity_value_2 = 10;
        break;
    case TYPE_SPACE_MAMA:
        obj->type = TYPE_SPACE_MAMA2;
    case TYPE_SPACE_MAMA2:
        swapMereDenisCollZones(obj, 1);
        PS1_setBossScrollLimits_spacemama(obj);
        bossSpeedFactor = 0x4000;
        alternateBossSpeedFactor = 0;
        laserSourceSprNumInAnim = 0xFF;
        IsBossThere = false;
        scrollLocked = false;
        obj->timer = 180;
        saveBossEncounter = 0xFF;
        currentBossAction = 0;
        currentBossActionIsOver = false;
        bossEncounter = 0;
        break;
    case TYPE_MOSKITO2:
        bossEncounter = 2;
        PS1_setBossScrollLimits_moskito(obj);
        bossSpeedFactor = 0x4000;
        alternateBossSpeedFactor = 0;
        IsBossThere = false;
        scrollLocked = false;
        obj->timer = 100;
        saveBossEncounter = 0xFF;
        currentBossAction = 0;
        currentBossActionIsOver = false;
        break;
    case TYPE_MOSKITO:
        bossEncounter = 0;
        PS1_setBossScrollLimits_moskito(obj);
        bossSpeedFactor = 0x4000;
        alternateBossSpeedFactor = 0;
        IsBossThere = false;
        scrollLocked = false;
        obj->timer = 100;
        saveBossEncounter = 0xFF;
        currentBossAction = 0;
        currentBossActionIsOver = false;
        break;
    case TYPE_BADGUY1:
        obj->offset_hy = 30;
        obj->flags &= ~FLG(OBJ_FOLLOW_ENABLED);
        break;
    case TYPE_LIDOLPINK2:
        obj->iframes_timer = 0;
        break;
    case TYPE_BLACKTOON1:
        switch (obj->follow_sprite)
        {
        case 1:
            obj->field56_0x69 = 2;
            obj->detect_zone = 0;
            break;
        case 2:
            obj->field56_0x69 = 8;
            obj->detect_zone = 60;
            break;
        case 3:
            obj->field56_0x69 = 24;
            obj->detect_zone = 170;
            break;
        case 4:
            obj->field56_0x69 = 10;
            obj->detect_zone = 100;
            break;
        case 5:
            obj->field20_0x36 = 0;
            obj->field56_0x69 = 1;
            obj->detect_zone = 0;
            break;
        case 6:
            obj->field56_0x69 = 4;
            obj->detect_zone = 60;
            break;
        case 7:
            obj->field56_0x69 = 36;
            obj->detect_zone = 120;
            break;
        }
        break;
    case TYPE_KILLING_EYES:
        obj->iframes_timer = obj->field23_0x3c = 40;
        break;
    case TYPE_PIRATE_NGAWE:
        obj->field56_0x69 = 1;
        break;
    case TYPE_PIRATE_GUETTEUR:
    case TYPE_PIRATE_GUETTEUR2:
        swapGuetteurCollZones(obj, obj->init_sub_etat == 14);
        obj->iframes_timer = 0;
        obj->detect_zone = 80;
        break;
    case TYPE_ONOFF_PLAT:
        obj->iframes_timer = obj->field20_0x36 = 100;
        obj->flags |= FLG(OBJ_ALIVE);
        break;
    case TYPE_CRUMBLE_PLAT:
        if (num_world != 1)
        {
            unk_2 = vblToEOA(obj, 1U) - 2;
            obj->field23_0x3c = unk_2;
            obj->iframes_timer = unk_2;
        }
        else
        {
            obj->field23_0x3c = 40;
            obj->iframes_timer = 20;
        }
        obj->field24_0x3e = 20;
        obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_FOLLOW_ENABLED);
        break;
    case TYPE_INST_PLAT:
        obj->iframes_timer = obj->field20_0x36 = 15;
        obj->flags |= FLG(OBJ_ALIVE);
        break;
    case TYPE_AUTOJUMP_PLAT:
    case TYPE_MOVE_AUTOJUMP_PLAT:
    case TYPE_CAISSE_CLAIRE:
    case TYPE_GOMME:
    case TYPE_MARK_AUTOJUMP_PLAT:
        obj->iframes_timer = obj->field20_0x36 = 1;
        obj->flags |= FLG(OBJ_ALIVE);
        break;
    case TYPE_CLOWN_TNT:
    case TYPE_CLOWN_TNT2:
    case TYPE_CLOWN_TNT3:
        obj->field56_0x69 = 0;
        obj->field24_0x3e = 0;
        break;
    case TYPE_CYMBAL1:
    case TYPE_CYMBAL2:
    case TYPE_HERSE_BAS:
    case TYPE_HERSE_HAUT:
        obj->field24_0x3e = 0;
        break;
    case TYPE_SCORPION:
        obj->detect_zone = 160;
        sko_phase = 0;
        break;
    case TYPE_PHOTOGRAPHE:
        obj->flags |= FLG(OBJ_ALIVE);
        break;
    case TYPE_MORNINGSTAR:
        obj->flags |= FLG(OBJ_ALIVE);
        break;
    case TYPE_PIRATE_POELLE_D:
    case TYPE_PIRATE_P_D_45:
        obj->flags |= FLG(OBJ_FLIP_X);
        break;
    case TYPE_DARK:
        obj->field23_0x3c = 0;
        break;
    case TYPE_MITE2:
        obj->eta[1][0].flags &= 0xef;
        obj->eta[1][2].flags &= 0xef;
        obj->field20_0x36 = 0;
        break;
    case TYPE_RAY_ETOILES:
        if (obj->main_etat == 0 && obj->sub_etat == 57)
            star_ray_der = obj;
        else
            star_ray_dev = obj;
        obj->display_prio = 3;
    case TYPE_RAYON:
    case TYPE_MEDAILLON_TOON:
        obj->flags &= ~FLG(OBJ_ALIVE);
        obj->flags &= ~FLG(OBJ_ACTIVE);
        break;
    }
}

/* 2A8F8 8014F0F8 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj_init_kill", INIT_OBJECTS);
#else
/* see "TODO:" */
void INIT_OBJECTS(u8 new_lvl)
{
    s16 unk_1;
    s16 unk_2;
    s16 cnt_1;
    Obj *cur_obj;
    u8 nb_objs;
    s32 unk_3;
    s32 unk_4;
    s32 unk_5;
    s16 unk_6;
    u16 unk_7;
    s16 unk_8;
    u16 unk_9;
    s32 unk_10;
    s32 unk_11;
    s16 unk_12;
    Obj *prev_obj;
    Obj *pa_obj;
    Obj *eau_obj_1;
    Obj *eau_obj_2;

    unk_1 = -1;
    unk_2 = -1;
    ray_on_poelle = false;
    nb_cymbal_in_map = 0;
    PS1_SplashAlwaysObjectsCount = 0;
    IsBossThere = false;
    PS1_AlwaysObjectsCount = 0;
    Mus_obj_id = unk_1;
    NumScrollObj = 0;
    rayman_obj_id = unk_1;
    reduced_rayman_id = unk_1;
    id_Cling_1up = unk_1;
    id_Cling_Pow = unk_1;
    fee_obj_id = unk_1;
    eau_obj_id = unk_1;
    mst_scroll_obj_id = unk_1;
    bateau_obj_id = unk_1;
    mama_pirate_obj_id = unk_1;
    black_ray_obj_id = unk_1;
    pierreAcorde_obj_id = unk_1;
    nb_wiz = 0;
    stosko_obj_id = unk_1;
    moskitomama_droite_obj_id = unk_1;
    moskitomama_gauche_obj_id = unk_1;
    moskitosaxo_obj_id = unk_1;
    corde_dark_obj_id = unk_1;

    cnt_1 = 0;
    cur_obj = &level.objects[cnt_1];
    nb_objs = level.nb_objects;
    while (cnt_1 < nb_objs)
    {
        cur_obj->id = cnt_1;
        if (new_lvl)
            first_obj_init(cur_obj);

        cur_obj->active_timer = 0;
        if (cur_obj->type == TYPE_INDICATOR)
        {
            cur_obj->main_etat = cur_obj->init_main_etat;
            cur_obj->sub_etat = cur_obj->init_sub_etat;
        }

        obj_init(cur_obj);
        if (flags[cur_obj->type].flags0 & FLG(OBJ0_ALWAYS))
        {
            cur_obj->x_pos = -32000;
            cur_obj->y_pos = -32000;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
        }
        else
            cur_obj->flags |= FLG(OBJ_ALIVE);

        switch (cur_obj->type)
        {
        case TYPE_PLANCHES:
            cur_obj->x_pos = 1;
            break;
        case TYPE_VAGUE_DERRIERE:
            cur_obj->x_pos += 2;
            break;
        case TYPE_SUPERHELICO:
            if (!(RayEvts.super_helico))
            {
                unk_3 = cur_obj->flags & ~FLG(OBJ_ALIVE);
                unk_4 = finBosslevel.helped_musician << OBJ_ALIVE;
                cur_obj->flags = unk_3 | unk_4;
            }
            else
                cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_TOTEM:
            cur_obj->field23_0x3c = 0;
            cur_obj->iframes_timer = 0;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_CORDE_DARK:
            corde_dark_obj_id = cur_obj->id;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_HYBRIDE_STOSKO:
            cur_obj->field23_0x3c = 0;
            stosko_obj_id = cur_obj->id;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_HYBRIDE_MOSAMS:
            cur_obj->field23_0x3c = 0;
            moskitosaxo_obj_id = cur_obj->id;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_HYB_BBF2_D:
            unk_1 = cur_obj->id;
            cur_obj->field23_0x3c = 0;
            moskitomama_droite_obj_id = cur_obj->id;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_HYB_BBF2_G:
            unk_2 = cur_obj->id;
            cur_obj->field23_0x3c = 0;
            moskitomama_gauche_obj_id = cur_obj->id;
            cur_obj->flags |= FLG(OBJ_FLIP_X);
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_STOSKO_PINCE:
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_PIERREACORDE:
            pierreAcorde_obj_id = cnt_1;
            cur_obj->iframes_timer = 0;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_CORDE:
            cur_obj->hit_points = (cur_obj->init_hit_points >> 2);
            cur_obj->flags |= FLG(OBJ_ALIVE);
            if (pierreAcorde_obj_id != -1)
            {
                /* TODO: ??? */
                pa_obj = &level.objects[pierreAcorde_obj_id];
                if (cur_obj->x_pos < pa_obj->x_pos)
                    cur_obj->y_pos = pa_obj->y_pos + 112;
                else
                    cur_obj->y_pos = pa_obj->y_pos + 120;

                cur_obj->y_pos = cur_obj->init_y_pos;
            }
            break;
        case TYPE_SMA_WEAPON:
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_HERSE_BAS_NEXT:
        case TYPE_HERSE_HAUT_NEXT:
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_EAU:
            if (cur_obj->hit_points != 0)
            {
                /* TODO: ??? */
                unk_5 = cur_obj->offset_bx;
                unk_6 = xmap - unk_5;
                cur_obj->x_pos = unk_6;
                if (num_world == 1)
                {
                    if (RayEvts.grain)
                        cur_obj->hit_points = 1;
                    cur_obj->y_pos = ymapmax + SCREEN_HEIGHT;
                }
                else
                {
                    cur_obj->hit_points = 0;
                    cur_obj->field23_0x3c = unk_6;
                    if (!(num_world == 3 && num_level == 7))
                    {
                        cur_obj->init_y_pos =
                        cur_obj->y_pos =
                            ymapmax + 160;
                        if (
                            (num_world == 5 && num_level == 8) ||
                            num_world == 4
                        )
                        {
                            cur_obj->init_y_pos =
                            cur_obj->y_pos =
                                ymapmax + 170;
                        }
                    }
                    else
                    {
                        /* TODO: ??? */
                        unk_7 = cur_obj->init_y_pos;
                        cur_obj->field12_0x26 = 0;
                        cur_obj->init_y_pos = unk_7;
                    }
                }
                eau_obj_id = cnt_1;
                cur_obj->iframes_timer = 0;
                cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                calc_obj_pos_map(cur_obj);
            }
            else if (!(eau_obj_id == -1 || num_world == 1))
            {
                cur_obj->speed_y = 0;
                cur_obj->speed_x = 0;
                cur_obj->flags = (cur_obj->flags & ~FLG(OBJ_FLIP_X));
                eau_obj_1 = &level.objects[eau_obj_id];
                unk_8 = eau_obj_1->field23_0x3c + 101;
                eau_obj_1->field23_0x3c = unk_8;
                cur_obj->x_pos = unk_8;
                cur_obj->y_pos = level.objects[eau_obj_id].y_pos;
                if (!(num_world == 3 && num_level == 7))
                {
                    cur_obj->init_y_pos = ymapmax + 160;
                    if (num_world == 4)
                        cur_obj->init_y_pos = ymapmax + 170;

                    if (num_world == 5 && num_level == 8)
                    {
                        unk_9 = (level.objects[eau_obj_id].y_pos + eau_obj_id) - cur_obj->id;
                        cur_obj->y_pos = unk_9;
                        cur_obj->init_y_pos = unk_9;
                    }
                }
                else
                {
                    cur_obj->init_y_pos = cur_obj->y_pos;
                    cur_obj->field12_0x26 = 0;
                }
                calc_obj_pos_map(cur_obj);
                cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                eau_obj_2 = &level.objects[eau_obj_id];
                cur_obj->sub_etat = ++eau_obj_2->hit_points;
                if (cur_obj->sub_etat >= 4)
                    cur_obj->sub_etat -= 4;
                cur_obj->iframes_timer = 0;
            }
            else
            {
                cur_obj->flags &= ~FLG(OBJ_ALIVE);
                cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            }
            break;
        case TYPE_TARZAN:
            unk_10 = cur_obj->flags & ~FLG(OBJ_ALIVE);
            unk_11 = !RayEvts.grain;
            cur_obj->flags = unk_10 | (unk_11 << OBJ_ALIVE);
            break;
        case TYPE_FEE:
            fee_obj_id = cnt_1;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_MST_SCROLL:
            if (cur_obj->hit_points == 0)
            {
                cur_obj->x_pos =
                cur_obj->init_x_pos =
                    ray.x_pos - 200;
                cur_obj->y_pos = ray.y_pos - 50;
                set_main_and_sub_etat(cur_obj, 0, 9);
                cur_obj->speed_x = 2;
                cur_obj->speed_y = 0;
                cur_obj->field23_0x3c = 0;
                cur_obj->field24_0x3e = 0;
                cur_obj->timer = 0;
                mst_scroll_obj_id = cnt_1;
                cur_obj->flags |= FLG(OBJ_ALIVE) | FLG(OBJ_ACTIVE);
                cur_obj->flags |= FLG(OBJ_FLIP_X);
            }
            else
                cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_DEMI_RAYMAN:
            reduced_rayman_id = cnt_1;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_RAY_POS:
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_SCROLL:
            scroll_obj_id[NumScrollObj] = cnt_1;
            NumScrollObj++;
            cur_obj->y_pos = cur_obj->init_y_pos;
            cur_obj->x_pos = cur_obj->init_x_pos;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_FALLING_OBJ:
        case TYPE_FALLING_OBJ2:
        case TYPE_FALLING_OBJ3:
        case TYPE_FALLING_YING:
        case TYPE_FALLING_YING_OUYE:
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_BADGUY2:
        case TYPE_BADGUY3:
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_STONEDOG2:
            cur_obj->init_flag = 7;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_CYMBALE:
            cymbal_obj_id[nb_cymbal_in_map++] = cnt_1;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_RAYMAN:
            rayman_obj_id = cnt_1;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_BLACK_FIST:
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            black_fist_obj_id = cur_obj->id;
            break;
        case TYPE_POING:
            cur_obj->sub_etat =
            cur_obj->init_sub_etat =
                poing.sub_etat;
            poing_obj_id = cnt_1;
            cur_obj->init_flag = 7;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_BOUM:
            sbar_obj_id = cnt_1;
            cur_obj->init_flag = 7;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_KILLING_EYES:
            cur_obj->iframes_timer = 40;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_PHOTOGRAPHE:
            cur_obj->timer = 0;
            break;
        case TYPE_SPLASH:
            PS1_SplashAlwaysObjects[PS1_SplashAlwaysObjectsCount++] = cnt_1;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_NEN_GRAINE:
            cur_obj->iframes_timer = 0;
        case TYPE_GRAINE:
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_SPIDER:
            cur_obj->field24_0x3e = 0;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_PAILLETTE:
        case TYPE_DESTROYING_DOOR:
            unk_12 = (
                cur_obj->animations[
                    cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].anim_index
                ].frames_count - 1) *
                (cur_obj->eta[cur_obj->main_etat][cur_obj->sub_etat].anim_speed & 0xf);
            cur_obj->init_flag = 7;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->field23_0x3c = unk_12;
            cur_obj->field24_0x3e = unk_12;
            break;
        case TYPE_BB1_PLAT:
            cur_obj->init_flag = 7;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_GENEBADGUY:
            cur_obj->init_flag = 7;
            cur_obj->timer = 0;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_CAGE:
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_BALLE1:
        case TYPE_BALLE2:
        case TYPE_DARK2_SORT:
        case TYPE_STONEBOMB:
        case TYPE_CLASH:
        case TYPE_MST_FRUIT1:
        case TYPE_MST_FRUIT2:
        case TYPE_CAGE2:
        case TYPE_DROP:
        case TYPE_DARD:
        case TYPE_NOTE:
        case TYPE_RING:
        case TYPE_PIRATE_BOMB:
        case TYPE_STONECHIP:
        case TYPE_EXPLOSION:
        case TYPE_NOTE0:
        case TYPE_NOTE1:
        case TYPE_NOTE2:
        case TYPE_BONNE_NOTE:
        case TYPE_BBL:
        case TYPE_BNOTE:
        case TYPE_DARK2_PINK_FLY:
        case TYPE_PI_BOUM:
        case TYPE_WASHING_MACHINE:
        case TYPE_TNT_BOMB:
        case TYPE_ECLAIR:
        case TYPE_BLACKTOON_EYES:
        case TYPE_ETINC:
        case TYPE_MARACAS_BAS:
        case TYPE_NOVA2:
        case TYPE_FLASH:
        case TYPE_POELLE_ALWAYS:
        case TYPE_SMA_GRAND_LASER:
        case TYPE_SMA_BOMB:
        case TYPE_SMA_BOMB_CHIP:
        case TYPE_DARD_PLAFOND:
        case TYPE_MEDAILLON_TOON:
        case TYPE_PIEDS_RAYMAN:
        case TYPE_FIRE_LEFT:
        case TYPE_FIRE_RIGHT:
        case TYPE_DARK_SORT:
        case TYPE_HYB_BBF2_LAS:
        case TYPE_SMA_PETIT_LASER:
            cur_obj->init_flag = 7;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_BLACK_RAY:
            cur_obj->animations = ray.animations;
            cur_obj->init_flag = 7;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            black_ray_obj_id = cur_obj->id;
            break;
        case TYPE_COUTEAU:
            cur_obj->field20_0x36 = 1;
            cur_obj->iframes_timer = 1;
            cur_obj->init_flag = 7;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        case TYPE_LIDOLPINK:
            cur_obj->init_flag = 7;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_FISH:
            if (cnt_1 > 0)
            {
                prev_obj = &level.objects[cnt_1 - 1];
                cur_obj->flags |= FLG(OBJ_ALIVE);
                if (prev_obj->type == TYPE_FISH && prev_obj->x_pos == cur_obj->x_pos)
                {
                    cur_obj->flags &= ~FLG(OBJ_ACTIVE);
                    cur_obj->flags &= ~FLG(OBJ_ALIVE);
                }
            }
            break;
        case TYPE_BB1:
        case TYPE_BB12:
        case TYPE_BB13:
            INIT_BBMONT(cur_obj);
            break;
        case TYPE_POI1:
        case TYPE_POI2:
        case TYPE_POI3:
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_FLAMME2:
        case TYPE_CLE_SOL:
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_PI_MUS:
            if (finBosslevel.helped_musician)
            {
                set_sub_etat(cur_obj, 10);
                cur_obj->init_sub_etat = 10;
            }
        case TYPE_PI:
            cur_obj->init_flag = 7;
            PS1_AlwaysObjects[PS1_AlwaysObjectsCount] = cur_obj->id;
            PS1_AlwaysObjectsCount++;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_MUS_WAIT:
            cur_obj->init_flag = 7;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            Mus_obj_id = cur_obj->id;
            if (finBosslevel.helped_musician)
            {
                cur_obj->init_sub_etat = 4;
                set_main_and_sub_etat(cur_obj, 0, 4);
            }
            break;
        case TYPE_JAUGEUP:
        case TYPE_ONEUP:
        case TYPE_GRAP_BONUS:
            cur_obj->init_flag = 7;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_NEUTRAL:
        case TYPE_TAMBOUR2:
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_TIBETAIN_6:
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_BATEAU:
            cur_obj->field23_0x3c = -1;
            cur_obj->field24_0x3e = 0;
            cur_obj->timer = 0;
            bateau_obj_id = cnt_1;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_MAMA_PIRATE:
            mama_pirate_obj_id = cnt_1;
            cur_obj->flags |= FLG(OBJ_ALIVE);
            break;
        case TYPE_POING_FEE:
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            break;
        case TYPE_DARK_PHASE2:
            cur_obj->init_x_pos = 0;
            cur_obj->x_pos = 0;
            cur_obj->init_y_pos = 0;
            cur_obj->y_pos = 0;
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            break;
        }

        if (t_world_info[world_index].nb_cages == 6 && cur_obj->type == TYPE_CAGE)
        {
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            take_bonus(cur_obj->id);
        }

        if (
            (
                !bonus_map &&
                flags[cur_obj->type].flags1 >> OBJ1_BONUS & 1 &&
                bonus_taken(cur_obj->id)
            ) || (cur_obj->type == TYPE_PALETTE_SWAPPER)
        )
        {
            cur_obj->flags &= ~FLG(OBJ_ACTIVE);
            cur_obj->flags &= ~FLG(OBJ_ALIVE);
        }

        if (bonus_map && cur_obj->type == TYPE_WIZ)
            nb_wiz++;

        cnt_1++;
        cur_obj++;
    }

    if (!(unk_1 == -1 || unk_2 == -1))
    {
        level.objects[unk_1].field24_0x3e = unk_2;
        level.objects[unk_2].field24_0x3e = unk_1;
    }

    if (bonus_map)
    {
        nb_wiz_save = status_bar.num_wiz;
        status_bar.num_wiz = 0;
    }
}
const u8 rodata_INIT_OBJECTS[4] = {};
#endif

/* 2B698 8014FE98 -O2 -msoft-float */
s32 instantSpeed(s16 spd_in)
{
    s32 to_add;
    s32 spd_shr = (s16) ashr16(spd_in, 4);
    s32 spd_abs_max = __builtin_abs(spd_in) & 15;

    if (spd_abs_max != 0)
    {
        to_add =
            ashr32(spd_abs_max * map_time, 4) -
            ashr32(spd_abs_max * map_time - spd_abs_max, 4);
        if (spd_in >= 0)
        {
            if (spd_in > 0)
                spd_shr += to_add;
        }
        else
            spd_shr -= to_add;
    }

    return (s16) spd_shr;
}

/* 2B764 8014FF64 -O2 -msoft-float */
void SET_X_SPEED(Obj *obj)
{
    ObjState *cur_eta;
    s16 spd_x;
    u8 unk_1 = (obj->animations[obj->anim_index].layers_count >> 0xe) + 1;

    if (horloge[unk_1] == 0)
    {
        cur_eta = &obj->eta[obj->main_etat][obj->sub_etat];
        switch (obj->flags >> OBJ_FLIP_X & 1)
        {
        case false:
            spd_x = cur_eta->speed_x_left * unk_1;
            break;
        case true:
            spd_x = cur_eta->speed_x_right * unk_1;
            break;
        }
    }
    else
        spd_x = 0;

    if (obj->type == TYPE_RAYMAN && RayEvts.demi)
        spd_x = ashr16(spd_x, 1);

    obj->speed_x = spd_x;
}

/* 2B878 80150078 -O2 -msoft-float */
void REINIT_OBJECT(Obj *obj)
{
    obj_init(obj);
    obj->active_flag = ACTIVE_REINIT;
    obj->flags |= FLG(OBJ_ALIVE);
    calc_obj_pos_map(obj);
    obj->active_timer = 120;
    obj->flags &= ~FLG(OBJ_ACTIVE);
}

/* 2B8D0 801500D0 -O2 -msoft-float */
void make_active(Obj *obj, u8 do_nova)
{
    if (obj->flags & FLG(OBJ_ALIVE))
    {
        obj->flags |= FLG(OBJ_ACTIVE) | FLG(OBJ_FLAG_5);
        obj->active_flag = ACTIVE_ALIVE;
        if (do_nova)
            DO_NOVA(obj);
    }
}

/* 2B914 80150114 -O2 -msoft-float */
s16 in_action_zone(s32 in_x, s32 in_y, Obj *obj, u8 param_4)
{
    s32 unk_3;
    s32 unk_1 = 0;
    s16 zdiff_x = zonediffx[ot];
    s16 zdiff_y = zonediffy[ot];
    u8 offset_bx = obj->offset_bx;
    s32 unk_x = in_x;
    s32 unk_y = in_y;
    u8 unk_param_4 = param_4;

    if (flags[ot].flags0 >> OBJ0_KEEP_ACTIVE & 1)
    {
        if (flags[ot].flags0 >> OBJ0_BOSS && IsBossThere)
            unk_1 = 1;
        else
        {
            switch (ot)
            {
            case TYPE_FEE:
            case TYPE_POING:
            case TYPE_BATTEUR_FOU:
            case TYPE_BLACK_RAY:
            case TYPE_BLACK_FIST:
            case TYPE_COUTEAU:
            case TYPE_DARK_SORT:
            case TYPE_NOVA2:
                unk_1 = 1;
                break;
            case TYPE_FISH:
            case TYPE_BBL:
                if ((u16) (unk_x + 283) < 727)
                    unk_1 = 1;
                break;
            case TYPE_PIERREACORDE:
                if (((s16) unk_y + zdiff_y > -50) && (u16) (unk_x + 283) < 783)
                {
                    if (level.objects[pierreAcorde_obj_id].hit_points == 0)
                    {
                        level.objects[pierreAcorde_obj_id].hit_points = 10;
                        set_main_and_sub_etat(&level.objects[pierreAcorde_obj_id], 2, 4);
                    }
                }
            case TYPE_CORDE:
                if (level.objects[pierreAcorde_obj_id].hit_points != 0)
                    unk_1 = 1;
                break;
            case TYPE_EAU:
                if ((u16) (unk_x + 283) < 783)
                    unk_1 = 1;
                break;
            case TYPE_STONEDOG2:
                if (((u16) (unk_x + 283) < 727) && ((u16) (unk_y + 99) < 349))
                    unk_1 = 1;
                break;
            case TYPE_SMA_PETIT_LASER:
            case TYPE_SMA_GRAND_LASER:
                offset_bx = 128;
                break;
            case TYPE_PAILLETTE:
            case TYPE_DESTROYING_DOOR:
                if (((u16) (obj->y_pos - 50) > 320) || !IsBossThere)
                {
                    if (ray.field20_0x36 == obj->id)
                    {
                        ray.field20_0x36 = -1;
                        obj->ray_dist = 1000;
                        set_main_and_sub_etat(&ray, 2, 2);
                    }
                    unk_1 = 2;
                }
                else
                    unk_1 = 1;
                break;
            }
        }
    }

    unk_3 = unk_1;
    if (unk_1 == 0)
    {
        if (unk_param_4)
        {
            zdiff_x += 60;
            zdiff_y += 60;
        }

        unk_1 = 1;
        if (
            ((s16) unk_x < -284 - zdiff_x) || ((s16) unk_x > zdiff_x + 444) ||
            ((s16) unk_y < -144 - zdiff_y) || ((s16) unk_y > zdiff_y + 304) ||
            (obj->y_pos + obj->offset_by < -30) || (obj->y_pos > mp.height * 16 + 30) ||
            (obj->x_pos + offset_bx * 2 < 0) || (obj->x_pos > mp.width * 16)
        )
            unk_1 = 0;
        unk_3 = unk_1;
    }

    if (unk_3 == 1)
    {
        if (flags[ot].flags0 >> OBJ0_BOSS & 1)
        {
            IsBossThere = true;
            if (
                (!first_boss_meet && obj->hit_points != 0 && scrollLocked) ||
                (first_boss_meet && obj->hit_points == 0)
            )
                Change_Wait_Anim();
        }
    }
    return !(unk_1 ^ 1);
}

/* 2BE38 80150638 -O2 -msoft-float */
void kill_obj(Obj *obj)
{
    obj->x_pos = -32000;
    obj->y_pos = -32000;
    obj->active_flag = ACTIVE_DEAD;
    obj->flags &= ~FLG(OBJ_ALIVE);
}

/* 2BE60 80150660 -O2 -msoft-float */
#ifndef MATCHES_BUT
INCLUDE_ASM("asm/nonmatchings/obj_init_kill", SET_ACTIVE_FLAG);
#else
/* gotos and other cleanup */
void SET_ACTIVE_FLAG(s16 x, s16 y, Obj *obj)
{
    Obj *temp_s0_2;
    Obj *temp_s0_4;
    u8 var_t0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u32 temp_a0;
    u32 temp_v1_1;
    u8 temp_s0_1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 var_a0;
    u8 var_a0_2;
    u8 var_a0_3;
    u8 var_a1;
    u8 var_a1_2;
    Obj *temp_s0_3;
    u32 test_1;

    ot = obj->type;
    temp_s0_1 = (obj->flags >> 0xB) & 1;
    obj->flags &= ~0x800;
    if (obj->flags & 0x400)
    {
        if (in_action_zone(x, y, obj, temp_s0_1))
        {
            if (
                obj->active_timer == 0 &&
                ((flags[ot].flags1 & 1) || (obj->active_flag != 2 && (obj->active_flag != 4 || ot == 0x0A)))
            )
            {
                test_1 = obj->flags & ~0x800;
                test_1 |= temp_s0_1 << 0xB;
                obj->flags = test_1;
                if (flags[ot].flags0 & 1)
                {
                    var_a1 = 0;
                    if (!(obj->flags & 0x800))
                    {
                        var_a1 = flags[obj->type].flags1 & 1;
                    }
                    make_active(obj, var_a1);
                }
                else
                {
                    var_a0 = obj->id;
                    do
                    {
                        temp_s0_2 = &level.objects[var_a0];
                        var_a1 = 0;
                        if (!(temp_s0_2->flags & 0x800))
                        {
                            var_a1 = flags[obj->type].flags1 & 1;
                        }
                        make_active(temp_s0_2, var_a1);
                        var_a0 = link_init[temp_s0_2->id];
                    } while (var_a0 != obj->id);
                }
            }
            else if (obj->active_timer > 0)
            {
                obj->active_timer -= 1;
            }
        }
        else
        {
            obj->active_timer = 0;
            if (((u8) flags[ot].flags2 >> 5) & 1)
            {
                kill_obj(obj);
            }
            else
            {
                temp_v1_3 = obj->active_flag;
                if (temp_v1_3 == 2)
                {
                    obj->active_flag = 1;
                }
                else if (temp_v1_3 == 0 || obj->active_flag == 4)
                {
                    if (flags[ot].flags0 & 1)
                    {
                        REINIT_OBJECT(obj);
                        return;
block_1:
                        var_t0 = 1;
                        goto block_2;
                    }
                    else
                    {
                        obj->active_flag = 4;
                        var_a0 = obj->id;
                        obj->flags |= 0x800;
                        var_t0 = 0;
                        if (ot != 0x0A)
                        {
                            while (true)
                            {

                                temp_s0_2 = &level.objects[var_a0];
                                if (temp_s0_2->active_flag == 4)
                                {
                                    var_a0 = link_init[temp_s0_2->id];
                                    if (var_a0 == obj->id)
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    goto block_1;
                                    break;
                                }
                            }
                        }
block_2:
                        if ((obj->y_pos + obj->offset_by) < -0x1E)
                        {
                            obj->flags &= ~0x800;
                        }
                        if (!var_t0)
                        {
                            var_a0 = obj->id;
                            do
                            {
                                temp_s0_2 = &level.objects[var_a0];
                                REINIT_OBJECT(temp_s0_2);
                                var_a0 = link_init[temp_s0_2->id];
                            } while (var_a0 != obj->id);
                        }
                    }
                }
            }
        }
    }
}
#endif