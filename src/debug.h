inline void debugMenu() {
  if (joypad() == J_B) {
    menuSelectMode(MAIN_LOOP_MENU);
  }
}

inline void initDebug() {
  hideManualModeSprites();
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);
  SWITCH_RAM(0);
  writeNumber(0, 0, 3, game_data_meta_imageslots[0]);
  writeNumber(4, 0, 3, game_data_meta_imageslots[1]);
  writeNumber(8, 0, 3, game_data_meta_imageslots[2]);
  writeNumber(12, 0, 3, game_data_meta_imageslots[3]);
  writeNumber(16, 0, 3, game_data_meta_imageslots[4]);
  writeNumber(0, 1, 3, game_data_meta_imageslots[5]);
  writeNumber(4, 1, 3, game_data_meta_imageslots[6]);
  writeNumber(8, 1, 3, game_data_meta_imageslots[7]);
  writeNumber(12, 1, 3, game_data_meta_imageslots[8]);
  writeNumber(16, 1, 3, game_data_meta_imageslots[9]);

  writeNumber(0, 2, 3, game_data_meta_imageslots[10]);
  writeNumber(4, 2, 3, game_data_meta_imageslots[11]);
  writeNumber(8, 2, 3, game_data_meta_imageslots[12]);
  writeNumber(12, 2, 3, game_data_meta_imageslots[13]);
  writeNumber(16, 2, 3, game_data_meta_imageslots[14]);
  writeNumber(0, 3, 3, game_data_meta_imageslots[15]);
  writeNumber(4, 3, 3, game_data_meta_imageslots[16]);
  writeNumber(8, 3, 3, game_data_meta_imageslots[17]);
  writeNumber(12, 3, 3, game_data_meta_imageslots[18]);
  writeNumber(16, 3, 3, game_data_meta_imageslots[19]);

  writeNumber(0, 4, 3, game_data_meta_imageslots[20]);
  writeNumber(4, 4, 3, game_data_meta_imageslots[21]);
  writeNumber(8, 4, 3, game_data_meta_imageslots[22]);
  writeNumber(12, 4, 3, game_data_meta_imageslots[23]);
  writeNumber(16, 4, 3, game_data_meta_imageslots[24]);
  writeNumber(0, 5, 3, game_data_meta_imageslots[25]);
  writeNumber(4, 5, 3, game_data_meta_imageslots[26]);
  writeNumber(8, 5, 3, game_data_meta_imageslots[27]);
  writeNumber(12, 5, 3, game_data_meta_imageslots[28]);
  writeNumber(16, 5, 3, game_data_meta_imageslots[29]);

  writeNumber(1, 7, 3, game_data_meta_imageslots_checksum[0]);
  writeNumber(5, 7, 3, game_data_meta_imageslots_checksum[1]);


  writeNumber(0, 9, 3, game_data_meta_imageslots_echo[0]);
  writeNumber(4, 9, 3, game_data_meta_imageslots_echo[1]);
  writeNumber(8, 9, 3, game_data_meta_imageslots_echo[2]);
  writeNumber(12, 9, 3, game_data_meta_imageslots_echo[3]);
  writeNumber(16, 9, 3, game_data_meta_imageslots_echo[4]);
  writeNumber(0, 10, 3, game_data_meta_imageslots_echo[5]);
  writeNumber(4, 10, 3, game_data_meta_imageslots_echo[6]);
  writeNumber(8, 10, 3, game_data_meta_imageslots_echo[7]);
  writeNumber(12, 10, 3, game_data_meta_imageslots_echo[8]);
  writeNumber(16, 10, 3, game_data_meta_imageslots_echo[9]);

  writeNumber(0, 11, 3, game_data_meta_imageslots_echo[10]);
  writeNumber(4, 11, 3, game_data_meta_imageslots_echo[11]);
  writeNumber(8, 11, 3, game_data_meta_imageslots_echo[12]);
  writeNumber(12, 11, 3, game_data_meta_imageslots_echo[13]);
  writeNumber(16, 11, 3, game_data_meta_imageslots_echo[14]);
  writeNumber(0, 12, 3, game_data_meta_imageslots_echo[15]);
  writeNumber(4, 12, 3, game_data_meta_imageslots_echo[16]);
  writeNumber(8, 12, 3, game_data_meta_imageslots_echo[17]);
  writeNumber(12, 12, 3, game_data_meta_imageslots_echo[18]);
  writeNumber(16, 12, 3, game_data_meta_imageslots_echo[19]);

  writeNumber(0, 13, 3, game_data_meta_imageslots_echo[20]);
  writeNumber(4, 13, 3, game_data_meta_imageslots_echo[21]);
  writeNumber(8, 13, 3, game_data_meta_imageslots_echo[22]);
  writeNumber(12, 13, 3, game_data_meta_imageslots_echo[23]);
  writeNumber(16, 13, 3, game_data_meta_imageslots_echo[24]);
  writeNumber(0, 14, 3, game_data_meta_imageslots_echo[25]);
  writeNumber(4, 14, 3, game_data_meta_imageslots_echo[26]);
  writeNumber(8, 14, 3, game_data_meta_imageslots_echo[27]);
  writeNumber(12, 14, 3, game_data_meta_imageslots_echo[28]);
  writeNumber(16, 14, 3, game_data_meta_imageslots_echo[29]);

  writeNumber(1, 16, 3, game_data_meta_imageslots_echo_checksum[0]);
  writeNumber(5, 16, 3, game_data_meta_imageslots_echo_checksum[1]);
}
