#ifndef COMMON_H
#define COMMON_H

#ifdef PLATFORM_PSYZ
#include <psyz.h>
#include "sys/types.h"
#include <stdint.h>
#else
#include "SYS/TYPES.H"
#endif
#include "include_asm.h"

/*#define NUGGET*/
#define MATCHES_BUT

#ifdef PLATFORM_PSYZ
#define NUGGET
#define USE_CUSTOM_FILE_HEAP
#define USE_EXTERNAL_FILE_LOADING // TODO: Allow game to run with this off
#endif

#ifndef PLATFORM_PSYZ
#define OT_TYPE u_long
#endif

// The game reserves this memory area for loading files
#define FILE_HEAP_START 0x80010000
#define FILE_HEAP_SIZE 0x115000

#ifdef USE_CUSTOM_FILE_HEAP
#define FILE_HEAP_START 0x80010000
#define FILE_HEAP_SIZE 0x115000
extern unsigned char file_heap[FILE_HEAP_SIZE];
#define FILE_HEAP(address) &file_heap[(uintptr_t)address-FILE_HEAP_START]
#else
#define FILE_HEAP(address) address
#endif

#ifdef NUGGET
#define BSS_DEFS
#define MATCHES_BUT
#define NONMATCHINGS
#endif

#define FLG(x) (1 << x)
#define LEN(x) (sizeof(x) / sizeof(x[0]))
#define MAX_1(x, y) ((x) > (y) ? (x) : (y))
#define MAX_2(x, y) if (x < y) x = y;
#define MAX_3(x, y) if (y > x) x = y;
#define MIN_1(x, y) ((x) < (y) ? (x) : (y))
#define MIN_2(x, y) if (x > y) x = y;
#define MIN_3(x, y) if (y < x) x = y;
#define ABS(x) (x >= 0 ? (x) : -(x))
#define SGN(x) (x >= 0 ? (x > 0 ? 1 : 0) : -1)

#define true 1
#define false 0
#define null 0

typedef unsigned char u8; /* unsigned  8-bit */
typedef unsigned short u16; /* unsigned 16-bit */
#ifdef PLATFORM_PSYZ
typedef unsigned int u32; /* unsigned 32-bit */
#else
typedef unsigned long u32; /* unsigned 32-bit */
#endif

typedef signed char s8; /* signed  8-bit */
typedef short s16; /* signed 16-bit */
#ifdef PLATFORM_PSYZ
typedef signed int s32; /* signed 32-bit */
#else
typedef long s32; /* signed 32-bit */
#endif

typedef volatile unsigned char vu8; /* unsigned  8-bit */
typedef volatile unsigned short vu16; /* unsigned 16-bit */
typedef volatile unsigned long vu32; /* unsigned 32-bit */

typedef volatile signed char vs8; /* signed  8-bit */
typedef volatile short vs16; /* signed 16-bit */
typedef volatile long vs32; /* signed 32-bit */

#endif