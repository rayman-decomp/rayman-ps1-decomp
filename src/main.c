#include "main.h"

#ifdef BSS_DEFS
u8 fin_du_jeu;
#endif

#ifdef USE_CUSTOM_FILE_HEAP
unsigned char file_heap[FILE_HEAP_SIZE];
#endif

/* B438 8012FC38 -O2 -msoft-float */
/*extern s32 D_8005866C;*/ /* data from PS1_LoadFiles seems to end up in here */

void main(void)
{
    Display *new_disp;
    RaymanEvents default_evts = PS1_DefaultRayEvts;

#ifdef PLATFORM_PSYZ
    Psyz_SetTitle("Rayman");
    Psyz_SetDiskPath("rom.cue");
#endif
    ResetCallback();
    _96_remove();
    D_801E4D48 = 0;
    FIRST_INIT();
    INIT_MOTEUR_BEGIN();
    DEPART_INIT_LOOP();
    while (!PS1_InitPAD())
        PS1_PromptPad();

    StartPAD();
    ChangeClearPAD(0);
    D_801F4380 = (u8 *) FILE_HEAP(0x8005866C);
    while (true)
    {
        if (menuEtape != 4)
            INIT_WORLD_INFO();

        PS1_LoadFont();
        DO_MENU();
        if (!fin_du_jeu)
        {
            if (status_bar.num_lives > -1 && new_world && ModeDemo == 0)
                PS1_PlayMapIntro();

            while (!fin_du_jeu && status_bar.num_lives > -1 && new_world)
            {
                SPECIAL_INIT();
                PS1_LoadFont();
                DO_WORLD_MAP();
                DEPART_WORLD();
                while (!fin_du_jeu && !new_world && new_level)
                {
                    DEPART_LEVEL();
                    INIT_MOTEUR_LEVEL(new_level);
                    init_fee();
                    init_moustique();
                    PS1_StopPlayingSnd(PS1_NewWorldMusic[num_world]);
                    while (!fin_du_jeu && !new_level && !new_world)
                    {
                        DEPART_DEAD_LOOP();
                        INIT_MOTEUR_DEAD();
                        INIT_RAY_ON_MS(&NewMs);
                        if (num_world == 6 && num_level == 2)
                            RayEvts = default_evts;

                        while (dead_time != 0 && !new_level && !new_world && ModeDemo != 2)
                            DO_MAIN_LOOP();

                        new_disp = &PS1_Displays[0];
                        if (PS1_CurrentDisplay == &PS1_Displays[0])
                            new_disp = &PS1_Displays[1];
                        PS1_CurrentDisplay = new_disp;

                        PS1_Ingame = false;
                        PS1_StopLevelMusic();
                        DO_CONTINUE();
                        DO_VICTOIRE();
                    }
                    DONE_MOTEUR_LEVEL();
                    FIN_DEAD_LOOP();
                }
                if (ModeDemo != 0)
                    fin_du_jeu = true;
            }
        }
        if (ModeDemo != 0)
            FinDemoJeu();
    }
}