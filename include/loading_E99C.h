#ifndef LOADING_E99C_H
#define LOADING_E99C_H

#include "common.h"
#include "common/fileinfo.h"
#include "common/world_map.h"
#ifdef PLATFORM_PSYZ
#include <libsnd.h>
#include <libetc.h>
#else
#include "LIBSND.H"
#include "STDIO.H"
#include "psyq_3_0_missing/LIBETC.H"
#endif

/* .data */
extern u8 *D_801CEEEC;
extern u8 *D_801CEEF0;
extern u8 s__801ceef4[7];

void PS1_Disable_all_Callbacks(void);
void FUN_80133048(s32 param_1, FileInfo *files, u8 count);
s32 PS1_InitFiles(FileInfo *files, s32 count, u8 *name);
s32 FUN_801331a4(FileInfo *files, s32 count, s32 param_3);
s32 PS1_LoadFiles(FileInfo *files, s32 file_index, s32 count, s16 param_4);
s32 PS1_LoadVabBody(FileInfo file, s16 in_vabid, s16 param_3);

#endif