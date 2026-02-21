#include "draw/fade.h"

void (*D_801C7D68[])(RGBAArray *, s16) =
{
    fadenuitbleu,
    FUN_80169ac8,
    FUN_80169b54,
    FUN_80169b5c
};

RGBAArray *D_801C7D78[] =
{
    &D_801CEFE0[0],
    &D_801CEFE0[1],
    &D_801CEFE0[2],
    &D_801CEFE0[3],
    &D_801CEFE0[4],
    null,
    null,
    null,
    &D_801CEFFC[0],
    &D_801CEFFC[1],
    &D_801CEFFC[2]
};