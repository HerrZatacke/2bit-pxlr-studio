unsigned char dialog(unsigned char *message) {
  waitRelease();

  while (1) {
    if (jp == J_B) {
      waitRelease();
      return 0;
    } else if (jp == J_A) {
      waitRelease();
      return 1;
    }

    wait_vbl_done();
  }
}
