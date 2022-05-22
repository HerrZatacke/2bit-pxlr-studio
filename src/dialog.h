inline void appearDialog() {
  move_win(7, 146);

  for (unsigned char i = 0; i < 8; i += 1) {

    if (i == 4) {
      beep();
    }

    scroll_win(0, -7);
    wait_vbl_done();
  }

  waitRelease();
}

inline void disappearDialog() {
  waitRelease();

  for (unsigned char i = 0; i < 8; i += 1) {
    scroll_win(0, 7);
    wait_vbl_done();
  }

  move_win(7, 146);
}

unsigned char dialog(unsigned char *message) {
  fill_win_rect(0, 0, 20, 1, MENU_BORDER_TOP);
  fill_win_rect(0, 1, 20, 10, OFFSET_BLANK);
  set_win_based_tiles(1, 2, 16, 1, message, OFFSET_FONT - 32);
  set_win_based_tiles(14, 4, 5, 2, "Yes A No B", OFFSET_FONT - 32);

  appearDialog();

  while (1) {
    wait_vbl_done();

    if (jp == J_B) {
      boop();
      disappearDialog();
      return 0;
    } else if (jp == J_A) {
      beep();
      disappearDialog();
      return 1;
    }
  }
}
