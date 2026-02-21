#ifndef FILEINFO_H
#define FILEINFO_H

#include "common.h"
#include "LIBCD.H"

typedef struct FileInfo
{
    u8 *path;
    u8 *dest; /* u32 * based on datafile_read/CdRead? */
    u8 *dest_debug;
    CdlFILE file;
} FileInfo;

#endif