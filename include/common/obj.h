#ifndef OBJ_H
#define OBJ_H

#include "common.h"
#define printf(...)

typedef struct Sprite
{
    s32 img_buffer_offset; /*unused for final release*/
    u8 id;  /*0 is invalid*/
    u8 width;  /*full width*/
    u8 height;  /*full height*/
    u8 sprite_width;  /*sprite width*/
    u8 sprite_height;  /*sprite height*/
    u8 sprite_pos;  /*x and y as 4-bit values*/
    u8 field7_0xa;
    u8 field8_0xb;
    u16 clut;  /*palette*/
    u16 tpage;  /*texture page*/
    u8 page_x;
    u8 page_y;
} Sprite;

typedef struct AnimationLayer
{
    u8 flip_x;
    u8 x_pos;
    u8 y_pos;
    u8 sprite;
} AnimationLayer;

typedef struct AnimationFrame
{
    u8 x;
    u8 y;
    u8 width;
    u8 height;
} AnimationFrame;

typedef struct Animation
{
    AnimationLayer *layers;
    AnimationFrame *frames;
    u16 layers_count;
    u16 frames_count;
} Animation;

typedef struct ObjState
{
    s8 speed_x_right;
    s8 speed_x_left;
    u8 anim_index;
    u8 next_main_etat;
    u8 next_sub_etat;
    u8 anim_speed;
    u8 sound;
    u8 flags;
} ObjState;

typedef struct CmdContext
{
    s16 cmd_offset;
    u16 count;
} CmdContext;

/*TODO: bitfields?*/
typedef u8 BlockFlags;
#define BLOCK_FULLY_SOLID 0
#define BLOCK_SOLID 1
#define BLOCK_HURT 2
#define BLOCK_SLIPPERY 3
#define BLOCK_FLAG_4 4
#define BLOCK_CH_DIR 5
#define BLOCK_SLOPE 6
#define BLOCK_FLAG_7 7

#define FLG_BLOCK_NONE 0

typedef u8 BlockType;
#define BTYP_NONE 0
#define BTYP_CHDIR 1 /*reactionary*/
#define BTYP_SOLID_RIGHT_45 2
#define BTYP_SOLID_LEFT_45 3
#define BTYP_SOLID_RIGHT1_30 4
#define BTYP_SOLID_RIGHT2_30 5
#define BTYP_SOLID_LEFT1_30 6
#define BTYP_SOLID_LEFT2_30 7
#define BTYP_HURT 8
#define BTYP_RESSORT 9 /*bounce*/
#define BTYP_WATER 10
#define BTYP_LIANE 12 /*climb*/
#define BTYP_SOLID_PASSTHROUGH 14
#define BTYP_SOLID 15
#define BTYP_SLIPPERY_RIGHT_45 18
#define BTYP_SLIPPERY_LEFT_45 19
#define BTYP_SLIPPERY_RIGHT1_30 20
#define BTYP_SLIPPERY_RIGHT2_30 21
#define BTYP_SLIPPERY_LEFT1_30 22
#define BTYP_SLIPPERY_LEFT2_30 23
#define BTYP_SPIKES 24
#define BTYP_CLIFF 25
#define BTYP_SLIPPERY 30

typedef u8 ObjCommand;
#define GO_LEFT 0
#define GO_RIGHT 1
#define GO_WAIT 2
#define GO_UP 3
#define GO_DOWN 4
#define GO_SUBSTATE 5
#define GO_SKIP 6
#define GO_ADD 7
#define GO_STATE 8
#define GO_PREPARELOOP 9
#define GO_DOLOOP 10
#define GO_LABEL 11
#define GO_GOTO 12
#define GO_GOSUB 13
#define GO_RETURN 14
#define GO_BRANCHTRUE 15
#define GO_BRANCHFALSE 16
#define GO_TEST 17
#define GO_SETTEST 18
#define GO_WAITSTATE 19
#define GO_SPEED 20
#define GO_X 21
#define GO_Y 22
#define RESERVED_GO_SKIP 23
#define RESERVED_GO_GOTO 24
#define RESERVED_GO_GOSUB 25
#define RESERVED_GO_GOTOT 26
#define RESERVED_GO_GOTOF 27
#define RESERVED_GO_SKIPT 28
#define RESERVED_GO_SKIPF 29
#define GO_NOP 30
#define GO_SKIPTRUE 31
#define GO_SKIPFALSE 32
#define INVALID_CMD 33

typedef u8 ChangeAnimMode;
#define ANIMMODE_NONE 0
#define ANIMMODE_RESET_IF_NEW 1
#define ANIMMODE_RESET 2

typedef u8 ObjType;
#define TYPE_BADGUY1 0
#define TYPE_PLATFORM 1
#define TYPE_POWERUP 2
#define TYPE_LIDOLPINK 3
#define TYPE_NEUTRAL 4
#define TYPE_WIZARD1 5
#define TYPE_FALLING_YING_OUYE 6
#define TYPE_MORNINGSTAR 7
#define TYPE_FALLING_OBJ 8
#define TYPE_BADGUY2 9
#define TYPE_FISH 10
#define TYPE_BOUM 11
#define TYPE_CHASSEUR1 12
#define TYPE_BALLE1 13
#define TYPE_CHASSEUR2 14
#define TYPE_BALLE2 15
#define TYPE_FALLPLAT 16
#define TYPE_LIFTPLAT 17
#define TYPE_BTBPLAT 18
#define TYPE_SPLASH 19
#define TYPE_GENEBADGUY 20
#define TYPE_PHOTOGRAPHE 21
#define TYPE_MOVE_PLAT 22
#define TYPE_RAYMAN 23
#define TYPE_INTERACTPLT 24
#define TYPE_INST_PLAT 25
#define TYPE_CRUMBLE_PLAT 26
#define TYPE_BOING_PLAT 27
#define TYPE_ONOFF_PLAT 28
#define TYPE_AUTOJUMP_PLAT 29
#define TYPE_AUDIOSTART 30
#define TYPE_ONEUP_ALWAYS 31
#define TYPE_DARK_PHASE2 32
#define TYPE_DARK2_SORT 33
#define TYPE_MOVE_AUTOJUMP_PLAT 34
#define TYPE_STONEMAN1 35
#define TYPE_STONEBOMB 36
#define TYPE_TARZAN 37
#define TYPE_GRAINE 38
#define TYPE_NEN_GRAINE 39
#define TYPE_STONEDOG 40
#define TYPE_OUYE 41
#define TYPE_SIGNPOST 42
#define TYPE_STONEMAN2 43
#define TYPE_CLASH 44
#define TYPE_MOVE_OUYE 45
#define TYPE_BB1 46
#define TYPE_STONEBOMB2 47
#define TYPE_FLAMME2 48
#define TYPE_MOVE_START_PLAT 49
#define TYPE_MOSKITO 50
#define TYPE_MST_FRUIT1 51
#define TYPE_MST_FRUIT2 52
#define TYPE_MST_SHAKY_FRUIT 53
#define TYPE_MEDAILLON 54
#define TYPE_MUS_WAIT 55
#define TYPE_STONEWOMAN2 56
#define TYPE_STALAG 57
#define TYPE_CAGE 58
#define TYPE_CAGE2 59
#define TYPE_BIG_CLOWN 60
#define TYPE_WAT_CLOWN 61
#define TYPE_DROP 62
#define TYPE_MOVE_START_NUA 63
#define TYPE_SCROLL 64
#define TYPE_SPIDER 65
#define TYPE_DARD 66
#define TYPE_SWING_PLAT 67
#define TYPE_BIG_BOING_PLAT 68
#define TYPE_STONEBOMB3 69
#define TYPE_TROMPETTE 70
#define TYPE_NOTE 71
#define TYPE_PIRATE_NGAWE 72
#define TYPE_RING 73
#define TYPE_SAXO 74
#define TYPE_PAILLETTE 75
#define TYPE_DESTROYING_DOOR 76
#define TYPE_PIRATE_GUETTEUR 77
#define TYPE_PIRATE_BOMB 78
#define TYPE_STONECHIP 79
#define TYPE_BIGSTONE 80
#define TYPE_CYMBALE 81
#define TYPE_JAUGEUP 82
#define TYPE_EXPLOSION 83
#define TYPE_TIBETAIN 84
#define TYPE_ROLLING_EYES 85
#define TYPE_MARACAS 86
#define TYPE_TAMBOUR1 87
#define TYPE_TAMBOUR2 88
#define TYPE_JOE 89
#define TYPE_NOTE0 90
#define TYPE_NOTE1 91
#define TYPE_NOTE2 92
#define TYPE_BONNE_NOTE 93
#define TYPE_POING 94
#define TYPE_POING_POWERUP 95
#define TYPE_TOTEM 96
#define TYPE_BBL 97
#define TYPE_SPACE_MAMA 98
#define TYPE_RAY_POS 99
#define TYPE_MITE 100
#define TYPE_MORNINGSTAR_MOUNTAI 101
#define TYPE_BNOTE 102
#define TYPE_POI1 103
#define TYPE_POI2 104
#define TYPE_MARTEAU 105
#define TYPE_MOVE_MARTEAU 106
#define TYPE_GROSPIC 107
#define TYPE_DARK2_PINK_FLY 108
#define TYPE_PI 109
#define TYPE_PI_BOUM 110
#define TYPE_PI_MUS 111
#define TYPE_WASHING_MACHINE 112
#define TYPE_BAG1 113
#define TYPE_UNUSED_114 114
#define TYPE_BB1_PLAT 115
#define TYPE_CLOWN_TNT 116
#define TYPE_CLOWN_TNT2 117
#define TYPE_CLOWN_TNT3 118
#define TYPE_TNT_BOMB 119
#define TYPE_BATTEUR_FOU 120
#define TYPE_ECLAIR 121
#define TYPE_STONEDOG2 122
#define TYPE_BLACKTOON1 123
#define TYPE_PANCARTE 124
#define TYPE_BON3 125
#define TYPE_FOURCHETTE 126
#define TYPE_COUTEAU_SUISSE 127
#define TYPE_TIRE_BOUCHON 128
#define TYPE_PETIT_COUTEAU 129
#define TYPE_BLACKTOON_EYES 130
#define TYPE_BAG3 131
#define TYPE_POI3 132
#define TYPE_SUPERHELICO 133
#define TYPE_FALLING_OBJ2 134
#define TYPE_ETINC 135
#define TYPE_DEMI_RAYMAN 136
#define TYPE_REDUCTEUR 137
#define TYPE_ROULETTE 138
#define TYPE_MARACAS_BAS 139
#define TYPE_PT_GRAPPIN 140
#define TYPE_NEIGE 141
#define TYPE_ONEUP 142
#define TYPE_NOVA2 143
#define TYPE_LIDOLPINK2 144
#define TYPE_KILLING_EYES 145
#define TYPE_FLASH 146
#define TYPE_MST_SCROLL 147
#define TYPE_GRAP_BONUS 148
#define TYPE_CLE_SOL 149
#define TYPE_SCORPION 150
#define TYPE_BULLET 151
#define TYPE_CAISSE_CLAIRE 152
#define TYPE_FEE 153
#define TYPE_ROULETTE2 154
#define TYPE_ROULETTE3 155
#define TYPE_WALK_NOTE_1 156
#define TYPE_EAU 157
#define TYPE_PALETTE_SWAPPER 158
#define TYPE_TIBETAIN_6 159
#define TYPE_TIBETAIN_2 160
#define TYPE_WIZ 161
#define TYPE_UFO_IDC 162
#define TYPE_INDICATOR 163
#define TYPE_GENERATING_DOOR 164
#define TYPE_BADGUY3 165
#define TYPE_LEVIER 166
#define TYPE_FALLING_OBJ3 167
#define TYPE_CYMBAL1 168
#define TYPE_CYMBAL2 169
#define TYPE_RAYON 170
#define TYPE_MST_COPAIN 171
#define TYPE_STONEWOMAN 172
#define TYPE_BATEAU 173
#define TYPE_PIRATE_POELLE 174
#define TYPE_PUNAISE1 175
#define TYPE_CRAYON_BAS 176
#define TYPE_FALLING_YING 177
#define TYPE_HERSE_BAS 178
#define TYPE_HERSE_BAS_NEXT 179
#define TYPE_SAXO2 180
#define TYPE_SCROLL_SAX 181
#define TYPE_NOTE3 182
#define TYPE_SAXO3 183
#define TYPE_PIRATE_POELLE_D 184
#define TYPE_WALK_NOTE_2 185
#define TYPE_POELLE_ALWAYS 186
#define TYPE_MAMA_PIRATE 187
#define TYPE_RUBIS 188
#define TYPE_MOVE_RUBIS 189
#define TYPE_COUTEAU 190
#define TYPE_FALLING_CRAYON 191
#define TYPE_SMA_GRAND_LASER 192
#define TYPE_SMA_BOMB 193
#define TYPE_SMA_BOMB_CHIP 194
#define TYPE_SPIDER_PLAFOND 195
#define TYPE_DARD_PLAFOND 196
#define TYPE_MEDAILLON_TOON 197
#define TYPE_BB12 198
#define TYPE_BB1_VIT 199
#define TYPE_BB13 200
#define TYPE_BB14 201
#define TYPE_RAY_ETOILES 202
#define TYPE_SMA_WEAPON 203
#define TYPE_BLACK_RAY 204
#define TYPE_BLACK_FIST 205
#define TYPE_PIEDS_RAYMAN 206
#define TYPE_POELLE 207
#define TYPE_LANDING_SMOKE 208
#define TYPE_FIRE_LEFT 209
#define TYPE_FIRE_RIGHT 210
#define TYPE_BOUT_TOTEM 211
#define TYPE_DARK 212
#define TYPE_SPACE_MAMA2 213
#define TYPE_BOUEE_JOE 214
#define TYPE_DARK_SORT 215
#define TYPE_ENS 216
#define TYPE_MITE2 217
#define TYPE_HYBRIDE_MOSAMS 218
#define TYPE_CORDE 219
#define TYPE_PIERREACORDE 220
#define TYPE_CFUMEE 221
#define TYPE_CORDEBAS 222
#define TYPE_HYBRIDE_STOSKO 223
#define TYPE_STOSKO_PINCE 224
#define TYPE_PIRATE_P_45 225
#define TYPE_PIRATE_P_D_45 226
#define TYPE_MOSKITO2 227
#define TYPE_PRI 228
#define TYPE_PUNAISE2 229
#define TYPE_PUNAISE3 230
#define TYPE_HYB_BBF2_D 231
#define TYPE_HYB_BBF2_G 232
#define TYPE_HYB_BBF2_LAS 233
#define TYPE_LAVE 234
#define TYPE_PUNAISE4 235
#define TYPE_ANNULE_SORT_DARK 236
#define TYPE_GOMME 237
#define TYPE_POING_FEE 238
#define TYPE_PIRATE_GUETTEUR2 239
#define TYPE_CRAYON_HAUT 240
#define TYPE_HERSE_HAUT 241
#define TYPE_HERSE_HAUT_NEXT 242
#define TYPE_MARK_AUTOJUMP_PLAT 243
#define TYPE_SMA_PETIT_LASER 244
#define TYPE_DUNE 245
#define TYPE_CORDE_DARK 246
#define TYPE_VITRAIL 247
#define TYPE_SKO_PINCE 248
#define TYPE_RIDEAU 249
#define TYPE_PUNAISE5 250
#define TYPE_VAGUE_DEVANT 251
#define TYPE_VAGUE_DERRIERE 252
#define TYPE_PLANCHES 253
#define TYPE_SLOPEY_PLAT 254
#define TYPE_INVALID 255

typedef u8 ObjActiveFlag;
#define ACTIVE_ALIVE 0
#define ACTIVE_DEAD 1
#define ACTIVE_REINIT 2
#define ACTIVE_SPECIAL 4

#define FLG_ACTIVE_ALIVE 0

/* couldn't get 6A180 8018E980 FIN_WORLD_CHOICE, handle_RESERVED_GO_BRANCHTRUE or skipToLabel to match with actual bitfields */
typedef u32 ObjFlags;
#define OBJ_FLAG_0 8
#define OBJ_CMD_TEST 9
#define OBJ_ALIVE 10
#define OBJ_ACTIVE 11
#define OBJ_LINKED 12
#define OBJ_FLAG_5 13
#define OBJ_FLIP_X 14
#define OBJ_READ_CMDS 15
#define OBJ_FOLLOW_ENABLED 16
#define OBJ_FLAG_9 17
#define OBJ_FLAG_A 18
#define OBJ_FLAG_B 19

#define FLG_OBJ_NONE 0
#define FLG_OBJ_ANIM_COUNT_MASK 0xFF

typedef struct Obj
{
    Sprite *sprites;
    Animation *animations;
    u8 *img_buffer;
    ObjState **eta;
    u8 *cmds;
    s16 *cmd_labels;
    CmdContext cmd_contexts[1];
    s16 x_pos;
    s16 y_pos;
    s16 id;
    s16 screen_x_pos;
    s16 screen_y_pos;
    s16 field12_0x26;
    s16 init_x_pos;
    s16 init_y_pos;
    s16 speed_x;
    s16 speed_y;
    u16 nb_sprites;
    s16 cmd_offset;
    s16 nb_cmd;
    s16 field20_0x36; /*For Rayman this is the current follow obj id*/
    s16 follow_y;
    s16 follow_x;
    s16 field23_0x3c;
    s16 field24_0x3e;
    s16 ray_dist;
    s16 iframes_timer;
    s16 test_block_index;
    s16 scale;
    u16 zdc;
    s16 active_timer;
    BlockType btypes[5]; /* TODO: enum for its indexing? */
    u8 field32_0x51;
    u8 offset_bx;
    u8 offset_by;
    u8 anim_index;
    u8 anim_frame;
    u8 main_etat;
    u8 init_main_etat;
    u8 sub_etat;
    u8 init_sub_etat;
    ObjCommand cmd;
    u8 gravity_value_1;
    u8 gravity_value_2;
    ChangeAnimMode change_anim_mode;
    u8 offset_hy;
    u8 follow_sprite;
    u8 hit_points;
    u8 init_hit_points;
    u8 init_flag;
    ObjType type;
    u8 hit_sprite;
    ObjActiveFlag active_flag;
    u8 detect_zone;
    u8 detect_zone_flag;
    u8 cmd_context_index;
    u8 field56_0x69;
    u8 display_prio;
    u8 timer;
    ObjFlags flags;
} Obj;

#ifdef USE_CUSTOM_FILE_HEAP
static inline void REMAP_OBJ(Obj *obj)
{
    if (((uintptr_t) obj->sprites & 0xFF000000u) == 0x80000000u)
        obj->sprites = (Sprite *) FILE_HEAP(obj->sprites);

    if (((uintptr_t) obj->animations & 0xFF000000u) == 0x80000000u)
    {
        obj->animations = (Animation *) FILE_HEAP(obj->animations);
        int num_anims = (obj->flags & FLG_OBJ_ANIM_COUNT_MASK);
        for (int i = 0; i < num_anims; i++)
        {
            if (((uintptr_t) obj->animations[i].layers & 0xFF000000u) == 0x80000000u)
                obj->animations[i].layers = (AnimationLayer *) FILE_HEAP((u32) obj->animations[i].layers);
            if (((uintptr_t) obj->animations[i].frames & 0xFF000000u) == 0x80000000u)
                obj->animations[i].frames = (AnimationFrame *) FILE_HEAP((u32) obj->animations[i].frames);
        }
    }

    if (((uintptr_t) obj->img_buffer & 0xFF000000u) == 0x80000000u)
        obj->img_buffer = FILE_HEAP((u32) obj->img_buffer);

    if((uintptr_t)obj->eta != (uintptr_t)0x7fa4e9b0 && (((uintptr_t) obj->eta & 0xFF000000u) == 0x80000000u)) // there is one object in the game without an eta
    {
        obj->eta = (ObjState **) FILE_HEAP((u32) obj->eta);
        if (((uintptr_t) obj->eta[0] & 0xFF000000u) == 0x80000000u)
            obj->eta[0] = (ObjState *) FILE_HEAP((u32) obj->eta[0]);
        int num_eta = (((u32) obj->eta[0]) - ((u32) obj->eta)) / 4;
        printf("num_eta: %i\n", num_eta);
        for (int i = 1; i < num_eta; i++)
        {
            if (obj->eta[i] && ((uintptr_t) obj->eta[i] & 0xFF000000u) == 0x80000000u)
                obj->eta[i] = (ObjState *) FILE_HEAP((u32) obj->eta[i]);
        }
    }
    if (obj->cmds != NULL && (((uintptr_t) obj->cmds & 0xFF000000u) == 0x80000000u))
        obj->cmds = FILE_HEAP((u32) obj->cmds);

    if (obj->cmd_labels != NULL && (((uintptr_t) obj->cmd_labels & 0xFF000000u) == 0x80000000u))
        obj->cmd_labels = (s16 *) FILE_HEAP((u32) obj->cmd_labels);
}
#endif

#endif