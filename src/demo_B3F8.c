#include "demo_B3F8.h"

/* B3F8 8012FBF8 */
void PS1_FinishRecordingDemo(void)
{
    if (record.is_recording)
    {
        record.is_finished = true;
        record_input(&record);
    }
}