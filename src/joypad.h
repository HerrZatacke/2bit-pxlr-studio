
// global joypad store variable
unsigned char jp = 0;

inline void captureJoypad() {
  if (jp == 0) {
    jp = joypad();
  }
}

inline void joypadConsumed() {
  jp = 0;
}


void waitPush(unsigned char what) {
  // Wait until "what" has been pressed
  while (what != joypad()) {
    wait_vbl_done();
  }
}

void waitRelease() {
  // Wait until A has been released
  while (joypad() != 0) {
    wait_vbl_done();
  }
}

void waitabit() {
  for (unsigned char i = 0; i < 15; i ++) {
    wait_vbl_done();
    if (joypad() == 0) {
      i = 15;
    }
  }
  return;
}
