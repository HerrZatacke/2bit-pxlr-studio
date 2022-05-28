#pragma bank 1

#include <gb/gb.h>
#include <gbdk/platform.h>

// global joypad store variable
unsigned char jp = 0;
unsigned char jpCooldown = 0;

void joypadConsumed() BANKED OLDCALL {
  jp = 0;
  jpCooldown = 15;
}

void waitRelease() BANKED OLDCALL {
  // Wait until all inputs have been released
  while (jp != 0) {
    wait_vbl_done();
  }

  joypadConsumed();
}

void captureJoypadISR() BANKED OLDCALL {
  if (jpCooldown && joypad()) {
    jpCooldown--;
  } else {
    jp = joypad();
    jpCooldown = 0;
  }
}
