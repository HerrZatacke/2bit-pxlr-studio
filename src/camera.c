#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>

#include "banks.h"
#include "globals.h"
#include "defines.h"
#include "menus/shootingManualMenuItems.h"
#include "modeShootingManual.h"
#include "utils.h"
#include "joypad.h"
#include "values.h"

void setDitherMatrix() {
  savedBank = _current_bank;
  SWITCH_ROM(2);
  SWITCH_RAM(16);

  uint8_t ditherSet = getMenuValue(ditherSetsMenu);
  uint8_t contrast = getMenuValue(contrastsMenu);

  for (uint16_t i = 0; i < 48; i += 1) {
    if (ditherSet == DITHER_SET_HIGH) {
      memcpy(CAM_REG_DITHERPATTERN, ditherHighLightValues[contrast], 48);
    } else if (ditherSet == DITHER_SET_LOW) {
      memcpy(CAM_REG_DITHERPATTERN, ditherLowLightValues[contrast], 48);
    } else if (ditherSet == DITHER_SET_NO_HIGH) {
      memcpy(CAM_REG_DITHERPATTERN, ditherNoHighLightValues[contrast], 48);
    } else if (ditherSet == DITHER_SET_NO_LOW) {
      memcpy(CAM_REG_DITHERPATTERN, ditherNoLowLightValues[contrast], 48);
    }
  }

  SWITCH_ROM(savedBank);
}

void initCam() {
  if (
      loadSettingsFromRAM() == SETTINGS_REQUIRE_RESET ||
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

  CAM_REG_EDEXOPGAIN = getMenuValue(edgeOpModesMenu) | getMenuValue(gainsMenu) | getMenuValue(edgeExclusivesMenu);
  CAM_REG_EXPTIME = exposureTimesValues[getMenuValue(exposureTimesMenu)];
  CAM_REG_EDRAINVVREF = getMenuValue(edgeModesMenu) | getMenuValue(voltageRefsMenu) | getMenuValue(invertOutputsMenu);
  CAM_REG_ZEROVOUT = getMenuValue(voltageOutsMenu) | getMenuValue(zeroPointsMenu);

  isCapturing = 1;

  CAM_REG_CAPTURE = getMenuValue(captureModesMenu);

  SWITCH_ROM(savedBank);

  captureJoypadISR();

  while (CAM_REG_CAPTURE % 2) {
    if (!jp) {
      captureJoypadISR();
    }
  }

  isCapturing = 0;
}
