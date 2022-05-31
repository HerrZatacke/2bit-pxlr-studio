#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>
#include "defines.h"
#include "joypad.h"
#include "utils.h"
#include "overlays/overlays.h"

#define ANSWER_YES 0x01
#define ANSWER_NO 0x00
#define ANSWER_PENDING 0xFF

void appearDialog() BANKED {
  move_win(7, 146);

  for (uint8_t i = 0; i < 8; i += 1) {

    if (i == 4) {
      beep();
    }

    scroll_win(0, -7);
    wait_vbl_done();
  }

  waitRelease();
}

void disappearDialog() BANKED {
  waitRelease();

  for (uint8_t i = 0; i < 8; i += 1) {
    scroll_win(0, 7);
    wait_vbl_done();
  }

  move_win(7, 146);
}

uint8_t dialog(uint8_t *message, uint8_t handleOverlays) BANKED {
  if (handleOverlays) {
    hideLowerOverlay();
  }

  fill_win_rect(0, 0, 20, 1, MENU_BORDER_TOP);
  fill_win_rect(0, 1, 20, 10, OFFSET_BLANK);
  set_win_based_tiles(1, 2, 16, 1, message, OFFSET_FONT - 32);
  set_win_based_tiles(14, 4, 5, 2, "Yes A No B", OFFSET_FONT - 32);

  appearDialog();

  uint8_t answer = ANSWER_PENDING;

  while (answer == ANSWER_PENDING) {
    wait_vbl_done();

    if (jp == J_B) {
      boop();
      disappearDialog();
      answer = ANSWER_NO;
    } else if (jp == J_A) {
      beep();
      disappearDialog();
      answer = ANSWER_YES;
    }
  }

  if (handleOverlays) {
    showOverlay();
  }

  return answer;
}
