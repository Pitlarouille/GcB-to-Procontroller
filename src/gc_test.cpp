#include <cstdio>
#include <gx2/surface.h>
#include <gx2/swap.h>
#include <nn/hpad/hpad.h>
#include <notifications/notifications.h>
#include <wups.h>

extern bool gNotificationInitDone;

DECL_FUNCTION(void, GX2CopyColorBufferToScanBuffer, GX2ColorBuffer *colorBuffer, GX2ScanTarget scan_target) {
    if (scan_target == GX2_SCAN_TARGET_TV) {
        static int frameCounter = 0;
        frameCounter++;

        if (frameCounter >= 60) { // environ une fois par seconde
            frameCounter = 0;

            HPADStatus status{};
            int32_t res = HPADRead(HPAD_CHAN_0, &status, 1);

            if (gNotificationInitDone) {
                char msg[96];
                snprintf(msg, sizeof(msg), "HPADRead res=%d err=%d hold=0x%04X",
                         (int) res, (int) status.error, (unsigned int) status.hold);
                NotificationModule_AddInfoNotification(msg);
            }
        }
    }

    real_GX2CopyColorBufferToScanBuffer(colorBuffer, scan_target);
}

WUPS_MUST_REPLACE(GX2CopyColorBufferToScanBuffer, WUPS_LOADER_LIBRARY_GX2, GX2CopyColorBufferToScanBuffer);