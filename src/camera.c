#include "./banks/banks.h"
#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>

#include "./globals.h"
#include "./defines.h"
#include "./menus/shootingManualMenuItems.h"
#include "./modeShootingManual.h"
#include "./utils.h"
#include "./joypad.h"
#include "./values.h"

void setDitherMatrix() {
  savedBank = _current_bank;
  SWITCH_ROM(2);
  SWITCH_RAM(16);

  uint8_t ditherSet = getMenuValue(ditherSetsMenu);
  uint8_t contrast = getMenuValue(contrastsMenu);

  for (uint16_t i = 0; i < 48; i += 1) {
    if (ditherSet == DITHER_SET_HIGH) {
      memcpy(A006A035, ditherHighLightValues[contrast], 48);
    } else if (ditherSet == DITHER_SET_LOW) {
      memcpy(A006A035, ditherLowLightValues[contrast], 48);
    } else if (ditherSet == DITHER_SET_NO_HIGH) {
      memcpy(A006A035, ditherNoHighLightValues[contrast], 48);
    } else if (ditherSet == DITHER_SET_NO_LOW) {
      memcpy(A006A035, ditherNoLowLightValues[contrast], 48);
    }
  }

  SWITCH_ROM(savedBank);
}

void initCam() {
  if (
      loadSettingsFromRAM() ||
      (joypad() == (J_START | J_SELECT)) // "factory" reset
      ) {
    restoreDefaults(); // reset all sensor params to default
    boop();
    pause(20);
    beep();
  }

  setDitherMatrix();
}

void capture() {
  SWITCH_RAM(16);

  savedBank = _current_bank;
  SWITCH_ROM(2);

  uint16_t exposureTime = exposureTimesValues[getMenuValue(exposureTimesMenu)];

  A001 = getMenuValue(edgeOpModesMenu) | getMenuValue(gainsMenu) | getMenuValue(edgeExclusivesMenu);
  A002 = (char)(exposureTime >> 8);
  A003 = (char)exposureTime;
  A004 = getMenuValue(edgeModesMenu) | getMenuValue(voltageRefsMenu) | getMenuValue(invertOutputsMenu);
  A005 = getMenuValue(voltageOutsMenu) | getMenuValue(zeroPointsMenu);

  isCapturing = 1;

  A000 = getMenuValue(captureModesMenu);

  SWITCH_ROM(savedBank);

  captureJoypadISR();

  while (A000 % 2) {
    if (!jp) {
      captureJoypadISR();
    }
  }

  isCapturing = 0;
}
