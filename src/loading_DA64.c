#include "loading_DA64.h"

#ifdef BSS_DEFS
AllFixData *PS1_AllFixData;
Font alpha;
Font alpha2;
s16 D_801D7A60;
s16 D_801F8188;
s16 D_801F84A8;
void *D_801F7E90;
s32 D_801D7868[2];
#endif

/* DA64 80132264 -O2 -msoft-float */
void PS1_LoadLevelMapBlock(MapData *data)
{
    u8 unk_1 = *((u8 *) PS1_LevelMapBlock + 1);

    if ((*(u8 *) PS1_LevelMapBlock == 0x4D) && unk_1 == 0x4D)
        PS1_LevelMapBlock++;
    D_801F84A8 = *PS1_LevelMapBlock;
    PS1_LevelMapBlock++;
    D_801F8188 = *PS1_LevelMapBlock;
    D_801D7A60 = D_801F84A8 * D_801F8188;
    PS1_LevelMapBlock++;

    data->width = D_801F84A8;
    data->height = D_801F8188;
    data->length = D_801D7A60;
    data->map = PS1_LevelMapBlock;
    printf("data->map: %p\n", data->map);
}

/* DB04 80132304 -O2 -msoft-float */
void FUN_80132304(u32 *data, u8 height)
{
    RECT rect;

    rect.x = 768; rect.y = 504;
    rect.w = 256; rect.h = height;
#ifdef PLATFORM_PSYZ
    LoadImage(&rect, (u_long *) data);
#else
    LoadImage(&rect, data);
#endif
}

/* DB4C 8013234C -O2 -msoft-float */
void FUN_8013234c(u8 *param_1)
{
    /*
    according to ghidra:
    0xE8 * 4 = 0x3A0 in first if/else
    0xD in block after
    hoping this is correct
    */
    __builtin_memcpy(&PS1_Tile_clut_y_offs, param_1, 0x3AD);
}

/* DC24 80132424 -O2 -msoft-float */
void FUN_80132424(void)
{
    __builtin_memcpy(&bigray, D_801F7E90, sizeof(bigray));
}

/* didn't get straight up copy of AllFixData fields to work */
/* DCCC 801324CC -O2 -msoft-float */
void PS1_LoadAllFixData(void)
{
    u8 *cur = (u8 *) PS1_AllFixData;

    __builtin_memcpy(&alpha, cur, sizeof(Font));
    cur += sizeof(Font);
    __builtin_memcpy(&alpha2, cur, sizeof(Font));
    cur += sizeof(Font);
    __builtin_memcpy(&ray, cur, sizeof(Obj));
    cur += sizeof(Obj);
    __builtin_memcpy(&raylittle, cur, sizeof(Obj));
    cur += sizeof(Obj);
    __builtin_memcpy(&clock_obj, cur, sizeof(Obj));
    cur += sizeof(Obj);
    __builtin_memcpy(&div_obj, cur, sizeof(Obj));
    cur += sizeof(Obj);
    mapobj = (Obj *) cur;

    #ifdef USE_CUSTOM_FILE_HEAP
    alpha.sprites = (Sprite *)FILE_HEAP(alpha.sprites);
    alpha.img_buffer = FILE_HEAP(alpha.img_buffer);
    alpha2.sprites = (Sprite *)FILE_HEAP(alpha2.sprites);
    alpha2.img_buffer = FILE_HEAP(alpha2.img_buffer);
    REMAP_OBJ(&ray);
    REMAP_OBJ(&raylittle);
    REMAP_OBJ(&clock_obj);
    REMAP_OBJ(&div_obj);
    for(int i = 0; i < 25; i++)
    {
        REMAP_OBJ(&mapobj[i]);
    }
    #endif
}

/* DFEC 801327EC -O2 -msoft-float */
void PS1_LoadLevelObjBlock(void)
{
    __builtin_memcpy(&level, &PS1_LevelObjBlock[0], 8);
#ifdef USE_CUSTOM_FILE_HEAP
    level.objects = (Obj*)FILE_HEAP(level.objects);
    for(int i = 0; i < level.nb_objects; i++)
            REMAP_OBJ(&level.objects[i]);
#endif

    __builtin_memcpy(D_801D7868, &PS1_LevelObjBlock[8], 8);
#ifdef PLATFORM_PSYZ
    link_init = (u8*)FILE_HEAP((u8*)D_801D7868[0]);
#else
    link_init = (u8*)D_801D7868[0];
#endif
}

/* E064 80132864 -O2 -msoft-float */
void FUN_80132864(s16 param_1)
{
    PS1_LevelMapBlock = (s16 *) (FILE_HEAP(0x80780000));
#ifdef PLATFORM_PSYZ
    D_801F59E0 = (s32 *)FILE_HEAP(D_801C4374[param_1 - 1]);
#else
    D_801F59E0 = FILE_HEAP(D_801C4374[param_1 - 1]);
#endif
}