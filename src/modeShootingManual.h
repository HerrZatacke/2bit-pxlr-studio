#ifndef MODE_SHHOOTING_MANUAL_H
#define MODE_SHHOOTING_MANUAL_H

#include <gbdk/platform.h>

extern void renderManualMenu();
extern void initManualMode();
extern void storeSettings();
extern void restoreDefaults();
extern uint8_t loadSettingsFromRAM();
extern void renderManualMenu();
extern void menuAction();
extern void manualShootMenu();

#endif
