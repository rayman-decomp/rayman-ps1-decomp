#include "loading_E99C.h"
#ifdef PLATFORM_PSYZ
#include <string.h>
#endif

const u8 s_FILE_INFO_sd___801272a8[] = "FILE_INFO %s[%d] =\r\n{\r\n";
const u8 s__s_void0x08x_void0x_801272c0[] = "\t{\"%s\", (void*)0x%08x, (void*)0x%08x, {{%d,%d,%d,%d},%ld,\"%s\"}},\r\n";

/* E818 80133018 -O2 -msoft-float */
void PS1_Disable_all_Callbacks(void)
{
    ResetCallback();
    CdSyncCallback(null);
    CdReadyCallback(null);
}

/* E848 80133048 -O2 -msoft-float */
void FUN_80133048(s32 param_1, FileInfo *files, u8 count)
{
    u8 i;

    D_801CEEEC = &D_801CEEEC[sprintf(D_801CEEEC, s_FILE_INFO_sd___801272a8, param_1, count)];
    for (i = 0; i < count; i++)
    {
        D_801CEEEC = &D_801CEEEC[sprintf(
            D_801CEEEC,
            s__s_void0x08x_void0x_801272c0,
            files[i].path,
            files[i].dest,
            files[i].dest_debug,
            files[i].file.pos.minute,
            files[i].file.pos.second,
            files[i].file.pos.sector,
            files[i].file.pos.track,
            files[i].file.size,
            files[i].file.name
        )];
    }
    D_801CEEEC = &D_801CEEEC[sprintf(D_801CEEEC, s__801ceef4)];
}

/* E99C 8013319C -O2 -msoft-float */
s32 PS1_InitFiles(FileInfo *files, s32 count, u8 *name) { return 0; }

/* E9A4 801331A4 -O2 -msoft-float */
s32 FUN_801331a4(FileInfo *files, s32 count, s32 param_3)
{
    s16 i;
    s16 j;
    s32 num_not_found = 0;

    for (i = 0; i < count; i++)
    {
        files[i].file.size = 0;
        if (files[i].dest)
        {
            for (j = 0; j < 100; j++)
            {
                CdSync(0, null);
                if (CdSearchFile(&files[i].file, files[i].path))
                    break;
            }
        }
        if (j == 100)
            num_not_found++;
    }

    FUN_80133048(param_3, files, count);
    return num_not_found;
}

#ifdef USE_CUSTOM_FILE_HEAP
extern u8 D_801D8B50[41616];
extern u8 *D_801F4380;
#endif
/* EAB4 801332B4 -O2 -msoft-float */
s32 PS1_LoadFiles(FileInfo *files, s32 file_index, s32 count, s16 param_4)
{
    FileInfo unk_1;
    s32 num_not_found;
    s16 i;
    s16 j;
    s32 num_sectors;
    s32 sectors_rem;
    s16 unk_2;
    s16 unk_3;

    __builtin_memcpy(&unk_1, &files[0], sizeof(FileInfo));
    num_not_found = 0;
    for (i = file_index; i < file_index + count; i++)
    {
        j = 10000;
        if (files[i].dest)
        {
#ifdef USE_CUSTOM_FILE_HEAP
            // These 2 don't need fixing
            if(files[i].dest != &D_801D8B50[0] && files[i].dest != D_801F4380)
            {
                uintptr_t fixed_addr = (uintptr_t)FILE_HEAP(files[i].dest);
                if(fixed_addr > 0) files[i].dest = (u8*)fixed_addr;
            }
#endif
            if (files[i].file.size != 0)
            {
#ifndef USE_EXTERNAL_FILE_LOADING
                for (j = 0; j < 10000; j++)
                {
                    CdSync(0, null);
                    num_sectors = (files[i].file.size + 2047) >> 11;
                    CdControlB(CdlSetloc, &files[i].file.pos.minute, null);
#ifdef PLATFORM_PSYZ
                    CdRead(num_sectors, (u_long *) files[i].dest, CdlModeSpeed);
#else
                    CdRead(num_sectors, (u32 *) files[i].dest, CdlModeSpeed);
#endif
                    while ((sectors_rem = CdReadSync(1, null)) > 0)
                    {
                        if (param_4 != 0)
                        {
                            unk_2 = xmap;
                            xmap = unk_2;
                            unk_3 = ymap;
                            ymap = unk_3;
                        }
                    }
                    if (sectors_rem == 0)
                        break;
                }
            }
        }
        if (j == 10000)
            num_not_found++;
#else
                char buffer[1024];

                // Step 1: Add . to the start
                // Makes "\\RAY\\IMA\\VIG\\FND02.R16;1"
                // into ".\\RAY\\IMA\\VIG\\FND02.R16;1"
                buffer[0] = '.';
                strcpy(buffer+1, files[i].path);

                // Step 2: Replace '\\' by '/'
                for (char *p = buffer; *p; ++p) {
                    if (*p == '\\') {
                        *p = '/';
                    }
                }

                // Step 3: Remove ;1 since we aren't loading from disc
                char *semicolon = strchr(buffer, ';');
                if (semicolon) {
                    *semicolon = '\0';
                }

                // Open file
                FILE* fd = fopen(buffer, "rb");
                if(fd == NULL) ++num_not_found;
                else {
                    fread(files[i].dest, 1, files[i].file.size, fd);
                    fclose(fd);
                }
            }
        }
#endif
    }
    return num_not_found;
}

/* EC98 80133498 -O2 -msoft-float */
s32 PS1_LoadVabBody(FileInfo file, s16 in_vabid, s16 param_3)
{
    s32 out_vabid;
    s16 completed;

    PS1_LoadFiles(&file, 0, 1, param_3);
    SsUtReverbOff();
    out_vabid = SsVabTransBody(file.dest, in_vabid);
    SsUtReverbOn();
    completed = SsVabTransCompleted(SS_WAIT_COMPLETED);
    if (completed != true) /* ??? */
        out_vabid += completed * 0x100;
    return out_vabid;
}