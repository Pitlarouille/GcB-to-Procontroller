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

        if (frameCounter >= 60) {
            frameCounter = 0;

            char msg[128];
            int offset = 0;
            for (int port = 0; port < 4; port++) {
                HPADStatus status{};
                int32_t res = HPADRead((HPADChan) port, &status, 1);
                offset += snprintf(msg + offset, sizeof(msg) - offset, "P%d:%d ", port, (int) res);
            }

            if (gNotificationInitDone) {
                NotificationModule_AddInfoNotification(msg);
            }
        }
    }

    real_GX2CopyColorBufferToScanBuffer(colorBuffer, scan_target);
}

WUPS_MUST_REPLACE(GX2CopyColorBufferToScanBuffer, WUPS_LOADER_LIBRARY_GX2, GX2CopyColorBufferToScanBuffer);