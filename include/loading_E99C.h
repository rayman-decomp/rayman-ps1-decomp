#ifndef LOADING_E99C_H
#define LOADING_E99C_H

#include "common.h"
#include "common/fileinfo.h"
#include "common/world_map.h"
#include "LIBSND.H"
#include "STDIO.H"
#include "psyq_3_0_missing/LIBETC.H"

/* .data */
extern u8 *D_801CEEEC;
extern u8 *D_801CEEF0;
extern u8 s__801ceef4[7];

void start_data(void);
void PS1_PrintFileInfoTable(s32 param_1, FileInfo *files, u8 count);
s32 PS1_InitFiles(FileInfo *files, s32 count, u8 *name);
s32 PS1_GenerateFileInfoTable(FileInfo *files, s32 count, s32 param_3);
s32 datafile_read(FileInfo *files, s32 file_index, s32 count, s16 param_4);
s32 PS1_LoadVabBody(FileInfo file, s16 in_vabid, s16 param_3);

#endif