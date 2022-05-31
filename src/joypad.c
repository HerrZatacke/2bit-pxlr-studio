#pragma bank 1

#include <gb/gb.h>
#include <gbdk/platform.h>

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
  if (jpCooldown && joypad()) {
    jpCooldown--;
  } else {
    jp = joypad();
    jpCooldown = 0;
  }
}
