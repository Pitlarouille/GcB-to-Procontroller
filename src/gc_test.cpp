#include <cstdio>
#include <gx2/surface.h>
#include <gx2/swap.h>
#include <nn/hpad/hpad.h>
#include <notifications/notifications.h>
#include <wups.h>

extern bool gNotificationInitDone;

#define GC_PORT_COUNT 4

DECL_FUNCTION(void, GX2CopyColorBufferToScanBuffer, GX2ColorBuffer *colorBuffer, GX2ScanTarget scan_target) {
    if (scan_target == GX2_SCAN_TARGET_TV) {
        static int32_t lastHold[GC_PORT_COUNT] = {0};

        for (int port = 0; port < GC_PORT_COUNT; port++) {
            HPADStatus status{};
            int32_t res = HPADRead((HPADChan) port, &status, 1);

            if (res > 0 && status.hold != lastHold[port] && status.hold != 0) {
                if (gNotificationInitDone) {
                    char msg[64];
                    snprintf(msg, sizeof(msg), "Port %d hold: 0x%04X", port, (unsigned int) status.hold);
                    NotificationModule_AddInfoNotification(msg);
                }
            }
            if (res > 0) {
                lastHold[port] = status.hold;
            }
        }
    }

    real_GX2CopyColorBufferToScanBuffer(colorBuffer, scan_target);
}

WUPS_MUST_REPLACE(GX2CopyColorBufferToScanBuffer, WUPS_LOADER_LIBRARY_GX2, GX2CopyColorBufferToScanBuffer);