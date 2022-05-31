#ifndef MODE_SHHOOTING_MANUAL_H
#define MODE_SHHOOTING_MANUAL_H

#include <gbdk/platform.h>

#define SETTINGS_REQUIRE_RESET TRUE
#define SETTINGS_REQUIRE_NO_RESET FALSE

extern void renderManualMenu() BANKED;
extern void initManualMode() BANKED;
extern void storeSettings() BANKED;
extern void restoreDefaults() BANKED;
extern uint8_t loadSettingsFromRAM() BANKED;
extern void renderManualMenu() BANKED;
extern void menuAction() BANKED;
extern void manualShootMenu() BANKED;

#endif
