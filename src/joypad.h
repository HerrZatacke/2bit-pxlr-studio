
// global joypad store variable
unsigned char jp = 0;
unsigned char jpCooldown = 0;

inline void joypadConsumed() {
  jp = 0;
  jpCooldown = 15;
}

void waitRelease() {
  // Wait until all inputs has been released
  while (jp != 0) {
    wait_vbl_done();
  }

  joypadConsumed();
}

inline void captureJoypadISR() {
  if (jpCooldown && joypad()) {
    jpCooldown--;
  } else {
    jp = joypad();
    jpCooldown = 0;
  }
}
