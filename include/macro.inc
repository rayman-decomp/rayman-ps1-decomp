# This file is used by modern gas.
# Defines the expected assembly macros

# Evaluate this file only once in case it's included more than once
.ifndef _MACRO_INC_GUARD
.internal _MACRO_INC_GUARD
.set _MACRO_INC_GUARD, 1

.macro glabel label, visibility=global
    .\visibility "\label"
    .type "\label", @function
    "\label":
        .ent "\label"
.endm

.macro jlabel label
    \label:
.endm

.macro dlabel label
    .global \label
    \label:
.endm

.macro nonmatching label, size=1
        .global \label\().NON_MATCHING
        .type \label\().NON_MATCHING, @object
        .size \label\().NON_MATCHING, \size
        \label\().NON_MATCHING:
.endm

# End of a data symbol.
.macro enddlabel label
    .size \label, . - \label
.endm

.include "gte.inc"

.endif
