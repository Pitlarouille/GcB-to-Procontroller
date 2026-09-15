#include <notifications/notifications.h>
#include <wups.h>

WUPS_PLUGIN_NAME("GC2Pro");
WUPS_PLUGIN_DESCRIPTION("Fait passer une manette GameCube (adaptateur) pour une manette Pro Controller");
WUPS_PLUGIN_VERSION("v0.1");
WUPS_PLUGIN_AUTHOR("Toi");
WUPS_PLUGIN_LICENSE("GPL");

WUPS_USE_WUT_DEVOPTAB();

bool gNotificationInitDone = false;

INITIALIZE_PLUGIN() {
    if (NotificationModule_InitLibrary() == NOTIFICATION_MODULE_RESULT_SUCCESS) {
        gNotificationInitDone = true;
    }
}

DEINITIALIZE_PLUGIN() {
    if (gNotificationInitDone) {
        NotificationModule_DeInitLibrary();
        gNotificationInitDone = false;
    }
}