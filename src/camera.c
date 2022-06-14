#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>

#include "gbcamera.h"
#include "globals.h"
#include "defines.h"
#include "menus/shootingManualMenuItems.h"
#include "modeShootingManual.h"
#include "utils.h"
#include "joypad.h"
#include "values.h"

void setDitherMatrix(uint8_t ditherSet, uint8_t contrast) BANKED {
  SWITCH_RAM(16);

  for (uint16_t i = 0; i < 48; i += 1) {
    if (ditherSet == DITHERSET_HIGH | DITHER_ON) {
      memcpy(CAM_REG_DITHERPATTERN, ditherHighLightValues[contrast], 48);
    } else if (ditherSet == DITHERSET_LOW | DITHER_ON) {
      memcpy(CAM_REG_DITHERPATTERN, ditherLowLightValues[contrast], 48);
    } else if (ditherSet == DITHERSET_HIGH | DITHER_OFF) {
      memcpy(CAM_REG_DITHERPATTERN, ditherNoHighLightValues[contrast], 48);
    } else if (ditherSet == DITHERSET_LOW | DITHER_OFF) {
      memcpy(CAM_REG_DITHERPATTERN, ditherNoLowLightValues[contrast], 48);
    }
  }
}

void initCam() BANKED {
  if (
      loadSettingsFromRAM() == SETTINGS_REQUIRE_RESET ||
      (joypad() == (J_START | J_SELECT)) // "factory" reset
      ) {
    restoreDefaults(); // reset all sensor params to default
    boop();
    pause(20);
    beep();
  }

  setDitherMatrix(getMenuValue(&ditherSetsMenu), getMenuValue(&contrastsMenu));
}

void capture(uint8_t capt, uint8_t edExOpGain, uint16_t expTime, uint8_t edRInvVref, uint8_t zeroVout) BANKED {
  SWITCH_RAM(16);

  CAM_REG_EDEXOPGAIN = edExOpGain;
  CAM_REG_EXPTIME = expTime;
  CAM_REG_EDRAINVVREF = edRInvVref;
  CAM_REG_ZEROVOUT = zeroVout;

  isCapturing = 1;

  CAM_REG_CAPTURE = capt;

  captureJoypadISR();

  while (CAM_REG_CAPTURE % 2) {
    if (!jp) {
      captureJoypadISR();
    }
  }

  isCapturing = 0;
}
