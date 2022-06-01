#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>
#include "defines.h"
#include "joypad.h"
#include "utils.h"
#include "gbcamera.h"
#include "mainMenu.h"
#include "overlays/overlays.h"

void debugMenu() BANKED {
  if (jp == J_B) {
    menuSelectMode(MAIN_LOOP_MENU);
    joypadConsumed();
  }
}

void initDebug() BANKED {
  clearBkg();
  hideOverlay();
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);

  SWITCH_RAM(0);
  writeNumber(0, 0, 3, cam_game_data.imageslots[0]);
  writeNumber(4, 0, 3, cam_game_data.imageslots[1]);
  writeNumber(8, 0, 3, cam_game_data.imageslots[2]);
  writeNumber(12, 0, 3, cam_game_data.imageslots[3]);
  writeNumber(16, 0, 3, cam_game_data.imageslots[4]);
  writeNumber(0, 1, 3, cam_game_data.imageslots[5]);
  writeNumber(4, 1, 3, cam_game_data.imageslots[6]);
  writeNumber(8, 1, 3, cam_game_data.imageslots[7]);
  writeNumber(12, 1, 3, cam_game_data.imageslots[8]);
  writeNumber(16, 1, 3, cam_game_data.imageslots[9]);

  writeNumber(0, 2, 3, cam_game_data.imageslots[10]);
  writeNumber(4, 2, 3, cam_game_data.imageslots[11]);
  writeNumber(8, 2, 3, cam_game_data.imageslots[12]);
  writeNumber(12, 2, 3, cam_game_data.imageslots[13]);
  writeNumber(16, 2, 3, cam_game_data.imageslots[14]);
  writeNumber(0, 3, 3, cam_game_data.imageslots[15]);
  writeNumber(4, 3, 3, cam_game_data.imageslots[16]);
  writeNumber(8, 3, 3, cam_game_data.imageslots[17]);
  writeNumber(12, 3, 3, cam_game_data.imageslots[18]);
  writeNumber(16, 3, 3, cam_game_data.imageslots[19]);

  writeNumber(0, 4, 3, cam_game_data.imageslots[20]);
  writeNumber(4, 4, 3, cam_game_data.imageslots[21]);
  writeNumber(8, 4, 3, cam_game_data.imageslots[22]);
  writeNumber(12, 4, 3, cam_game_data.imageslots[23]);
  writeNumber(16, 4, 3, cam_game_data.imageslots[24]);
  writeNumber(0, 5, 3, cam_game_data.imageslots[25]);
  writeNumber(4, 5, 3, cam_game_data.imageslots[26]);
  writeNumber(8, 5, 3, cam_game_data.imageslots[27]);
  writeNumber(12, 5, 3, cam_game_data.imageslots[28]);
  writeNumber(16, 5, 3, cam_game_data.imageslots[29]);

  set_bkg_based_tiles(1, 7, sizeof(cam_game_data.magic), 1, cam_game_data.magic, OFFSET_FONT - 32);
  writeNumber(7, 7, 3, cam_game_data.CRC_add);
  writeNumber(11, 7, 3, cam_game_data.CRC_xor);


  writeNumber(0, 9, 3, cam_game_data_echo.imageslots[0]);
  writeNumber(4, 9, 3, cam_game_data_echo.imageslots[1]);
  writeNumber(8, 9, 3, cam_game_data_echo.imageslots[2]);
  writeNumber(12, 9, 3, cam_game_data_echo.imageslots[3]);
  writeNumber(16, 9, 3, cam_game_data_echo.imageslots[4]);
  writeNumber(0, 10, 3, cam_game_data_echo.imageslots[5]);
  writeNumber(4, 10, 3, cam_game_data_echo.imageslots[6]);
  writeNumber(8, 10, 3, cam_game_data_echo.imageslots[7]);
  writeNumber(12, 10, 3, cam_game_data_echo.imageslots[8]);
  writeNumber(16, 10, 3, cam_game_data_echo.imageslots[9]);

  writeNumber(0, 11, 3, cam_game_data_echo.imageslots[10]);
  writeNumber(4, 11, 3, cam_game_data_echo.imageslots[11]);
  writeNumber(8, 11, 3, cam_game_data_echo.imageslots[12]);
  writeNumber(12, 11, 3, cam_game_data_echo.imageslots[13]);
  writeNumber(16, 11, 3, cam_game_data_echo.imageslots[14]);
  writeNumber(0, 12, 3, cam_game_data_echo.imageslots[15]);
  writeNumber(4, 12, 3, cam_game_data_echo.imageslots[16]);
  writeNumber(8, 12, 3, cam_game_data_echo.imageslots[17]);
  writeNumber(12, 12, 3, cam_game_data_echo.imageslots[18]);
  writeNumber(16, 12, 3, cam_game_data_echo.imageslots[19]);

  writeNumber(0, 13, 3, cam_game_data_echo.imageslots[20]);
  writeNumber(4, 13, 3, cam_game_data_echo.imageslots[21]);
  writeNumber(8, 13, 3, cam_game_data_echo.imageslots[22]);
  writeNumber(12, 13, 3, cam_game_data_echo.imageslots[23]);
  writeNumber(16, 13, 3, cam_game_data_echo.imageslots[24]);
  writeNumber(0, 14, 3, cam_game_data_echo.imageslots[25]);
  writeNumber(4, 14, 3, cam_game_data_echo.imageslots[26]);
  writeNumber(8, 14, 3, cam_game_data_echo.imageslots[27]);
  writeNumber(12, 14, 3, cam_game_data_echo.imageslots[28]);
  writeNumber(16, 14, 3, cam_game_data_echo.imageslots[29]);

  set_bkg_based_tiles(1, 16, sizeof(cam_game_data_echo.magic), 1, cam_game_data_echo.magic, OFFSET_FONT - 32);
  writeNumber(7, 16, 3, cam_game_data_echo.CRC_add);
  writeNumber(11, 16, 3, cam_game_data_echo.CRC_xor);
}
