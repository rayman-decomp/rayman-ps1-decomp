#include "unknown/5C2BC.h"

// NOTE: Function name casing is unknown since the name comes from always lowercase hook names in the 30th anniversary edition
/* 5C2BC 80180ABC -O2 -msoft-float */
void clearbothdrawenv(void)
{
    ClearImage(&PS1_Displays[0].drawing_environment.clip, 0, 0, 0);
    ClearImage(&PS1_Displays[1].drawing_environment.clip, 0, 0, 0);
}
