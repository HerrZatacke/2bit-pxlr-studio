#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>
#include <gbdk/bcd.h>
#include "typedefs/Histogram.h"
#include "gbcamera.h"
#include "globals.h"
#include "defines.h"
#include "joypad.h"
#include "images.h"


const uint8_t bitsSetLUT[256] = {
    0u, 1u, 1u, 2u, 1u, 2u, 2u, 3u, 1u, 2u, 2u, 3u, 2u, 3u, 3u, 4u,
    1u, 2u, 2u, 3u, 2u, 3u, 3u, 4u, 2u, 3u, 3u, 4u, 3u, 4u, 4u, 5u,
    1u, 2u, 2u, 3u, 2u, 3u, 3u, 4u, 2u, 3u, 3u, 4u, 3u, 4u, 4u, 5u,
    2u, 3u, 3u, 4u, 3u, 4u, 4u, 5u, 3u, 4u, 4u, 5u, 4u, 5u, 5u, 6u,
    1u, 2u, 2u, 3u, 2u, 3u, 3u, 4u, 2u, 3u, 3u, 4u, 3u, 4u, 4u, 5u,
    2u, 3u, 3u, 4u, 3u, 4u, 4u, 5u, 3u, 4u, 4u, 5u, 4u, 5u, 5u, 6u,
    2u, 3u, 3u, 4u, 3u, 4u, 4u, 5u, 3u, 4u, 4u, 5u, 4u, 5u, 5u, 6u,
    3u, 4u, 4u, 5u, 4u, 5u, 5u, 6u, 4u, 5u, 5u, 6u, 5u, 6u, 6u, 7u,
    1u, 2u, 2u, 3u, 2u, 3u, 3u, 4u, 2u, 3u, 3u, 4u, 3u, 4u, 4u, 5u,
    2u, 3u, 3u, 4u, 3u, 4u, 4u, 5u, 3u, 4u, 4u, 5u, 4u, 5u, 5u, 6u,
    2u, 3u, 3u, 4u, 3u, 4u, 4u, 5u, 3u, 4u, 4u, 5u, 4u, 5u, 5u, 6u,
    3u, 4u, 4u, 5u, 4u, 5u, 5u, 6u, 4u, 5u, 5u, 6u, 5u, 6u, 6u, 7u,
    2u, 3u, 3u, 4u, 3u, 4u, 4u, 5u, 3u, 4u, 4u, 5u, 4u, 5u, 5u, 6u,
    3u, 4u, 4u, 5u, 4u, 5u, 5u, 6u, 4u, 5u, 5u, 6u, 5u, 6u, 6u, 7u,
    3u, 4u, 4u, 5u, 4u, 5u, 5u, 6u, 4u, 5u, 5u, 6u, 5u, 6u, 6u, 7u,
    4u, 5u, 5u, 6u, 5u, 6u, 6u, 7u, 5u, 6u, 6u, 7u, 6u, 7u, 7u, 8u,
};

void createHistogram(uint8_t *data, Histogram *histogram) BANKED {
  histogram->white = 0;
  histogram->lgrey = 0;
  histogram->dgrey = 0;
  histogram->black = 0;

  for (uint16_t i = 0; i < CAMERA_IMAGE_SIZE; i += 2) {
    histogram->white += (uint16_t)bitsSetLUT[(uint8_t)(~data[i] & ~data[i + 1])];
    histogram->lgrey += (uint16_t)bitsSetLUT[(uint8_t)( data[i] & ~data[i + 1])];
    histogram->dgrey += (uint16_t)bitsSetLUT[(uint8_t)(~data[i] &  data[i + 1])];
    histogram->black += (uint16_t)bitsSetLUT[(uint8_t)( data[i] &  data[i + 1])];
  }
}

void getHistogram(uint8_t imageIndex, uint8_t *tileMap) BANKED {
  Histogram histogram;
  uint8_t imageSlot = getImageSlot(imageIndex);
  uint8_t i;
  uint8_t digits[10];
  BCD bcd = MAKE_BCD(0);

  SWITCH_RAM(images[imageSlot]->bank);
  createHistogram(images[imageSlot]->tilesUpper, &histogram);
  memcpy(&tileMap[0],
        "                    "
        "                    "
        "  Histogram         "
        "                    "
        "  White             "
        "    ?????           "
        "                    "
        "  Light grey        "
        "    ?????           "
        "                    "
        "  Dark grey         "
        "    ?????           "
        "                    "
        "  Black             "
        "    ?????           "
        "                    "
        "                    "
        "                    ",
        360);

  uint2bcd(histogram.white, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[104], &digits[3], 5);

  uint2bcd(histogram.lgrey, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[164], &digits[3], 5);

  uint2bcd(histogram.dgrey, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[224], &digits[3], 5);

  uint2bcd(histogram.black, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[284], &digits[3], 5);
}

void displayHistogram(uint8_t imageIndex) BANKED {
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);

  getHistogram(imageIndex, imageInfo);

  waitRelease();

  fill_win_rect(0, 0, 20, 18, OFFSET_BLANK);
  move_win(6, 0);
  set_win_based_tiles(0, 0, 20, 18, imageInfo, OFFSET_FONT - 32);

  while (jp != J_B && jp != J_A) {
    wait_vbl_done();
  }

  fill_win_rect(0, 0, 20, 18, OFFSET_BLANK);
  move_win(78, 0);
}
