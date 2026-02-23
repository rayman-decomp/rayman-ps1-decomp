#include "draw/fade.h"

void (*D_801C7D68[])(RGBAArray *, s16) =
{
    fadenuitbleu,
    PS1_UnknownFadeEffect,
    PS1_EmptyFadeEffect1,
    PS1_EmptyFadeEffect2
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