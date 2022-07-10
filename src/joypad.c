#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>

#include "remote.h"

// global joypad store variable
volatile uint8_t jp = 0;
static uint8_t jpCooldown = 0;

void joypadConsumed() BANKED {
  jp = 0;
  jpCooldown = 15;
}

void waitRelease() BANKED {
  // Wait until all inputs have been released
  while (jp != 0) {
    wait_vbl_done();
  }

  joypadConsumed();
}

void captureJoypadISR() BANKED {
  uint8_t value = (joypad() | remote_joypad()); 
  if (jpCooldown && (value)) {
    jpCooldown--;
  } else {
    jp = value;
    jpCooldown = 0;
  }
}
