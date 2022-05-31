#ifndef MODE_SHHOOTING_MANUAL_H
#define MODE_SHHOOTING_MANUAL_H

#include <gbdk/platform.h>

extern void renderManualMenu() BANKED;
extern void initManualMode() BANKED;
extern void storeSettings() BANKED;
extern void restoreDefaults() BANKED;
extern uint8_t loadSettingsFromRAM() BANKED;
extern void renderManualMenu() BANKED;
extern void menuAction() BANKED;
extern void manualShootMenu() BANKED;

#endif
