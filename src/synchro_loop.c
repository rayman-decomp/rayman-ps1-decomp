#include "synchro_loop.h"

void FUN_801802d8(void) {}

/* 5BAE0 801802E0 -O2 -msoft-float */
void SYNCHRO_LOOP(s16 (*func)())
{
    Display *new_disp_1;
    RECT *new_rect;
    Display *new_disp_2;
    s16 i;
    s16 func_done;

    do
    {
        if (PS1_MemoryUsageDisplayMode != 0)
            ClearImage(PTR_PS1_MemoryUsageRect_801cee70, 0, 0, 0);

        new_disp_1 = &PS1_Displays[0];
        if (PS1_CurrentDisplay == &PS1_Displays[0])
            new_disp_1 = &PS1_Displays[1];
        PS1_CurrentDisplay = new_disp_1;
        DrawSync(0);
        VSync(0);
        PutDispEnv(&PS1_CurrentDisplay->field0_0x0);
        PutDrawEnv(&PS1_CurrentDisplay->drawing_environment);

        if (PTR_PS1_MemoryUsageRect_801cee70 == &PS1_MemoryUsageRects[0])
            new_rect = &PS1_MemoryUsageRects[1];
        else
            new_rect = &PS1_MemoryUsageRects[0];
        PTR_PS1_MemoryUsageRect_801cee70 = new_rect;

        if (PS1_MemoryUsageDisplayMode != 0)
            ClearImage(PTR_PS1_MemoryUsageRect_801cee70, 0, 0, 128);
        ClearOTag((u32 *) PS1_CurrentDisplay->ordering_table, LEN(PS1_CurrentDisplay->ordering_table));

        new_disp_2 = &PS1_Displays[0];
        if (PS1_CurrentDisplay == &PS1_Displays[0])
            new_disp_2 = &PS1_Displays[1];

        for (i = 0; i < PS1_PolygonIndexTableCount; i++)
        {
            SetPolyFT4(&new_disp_2->polygons[PS1_PolygonIndexTable[i]]);
            SetSemiTrans(&new_disp_2->polygons[PS1_PolygonIndexTable[i]], false);
            SetShadeTex(&new_disp_2->polygons[PS1_PolygonIndexTable[i]], true);
        }
        PS1_PolygonIndexTableCount = 0;
        D_801E4BE0 = 0x0019;
        D_801F4A28 = 0;
        PS1_Disp_Cur_Tile1 = 0;
        PS1_PolygonsCount = 0;
        D_801F81B0 = 0;
        PS1_PrevPrim = &PS1_CurrentDisplay->ordering_table[6];
        func_done = func();
        if (PS1_MemoryUsageDisplayMode == 2)
            ClearImage(PTR_PS1_MemoryUsageRect_801cee70, 128, 0, 128);
        handle_pad();
        if (PS1_MemoryUsageDisplayMode == 2)
            ClearImage(PTR_PS1_MemoryUsageRect_801cee70, 128, 0, 128);
        DrawOTag((u32 *) PS1_CurrentDisplay->ordering_table);
    } while (!func_done);
}
