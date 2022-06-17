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
  uint16_t start = sys_time;

  histogram->white = 0;
  histogram->lgrey = 0;
  histogram->dgrey = 0;
  histogram->black = 0;

  uint8_t *lower = data;
  uint8_t *upper = data + 1;
  uint8_t invUpper;
  uint8_t invLower;
  uint8_t cpUpper;
  uint8_t cpLower;

  for (uint16_t i = 0; i < CAMERA_IMAGE_SIZE; i += 2, lower += 2, upper += 2) {
    invUpper = ~*upper;
    invLower = ~*lower;
    cpUpper = *upper;
    cpLower = *lower;
    histogram->white += (uint16_t)bitsSetLUT[(uint8_t)(invLower & invUpper)];
    histogram->lgrey += (uint16_t)bitsSetLUT[(uint8_t)( cpLower & invUpper)];
    histogram->dgrey += (uint16_t)bitsSetLUT[(uint8_t)(invLower &  cpUpper)];
    histogram->black += (uint16_t)bitsSetLUT[(uint8_t)( cpLower &  cpUpper)];
  }

  histogram->time = sys_time - start;
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
        "  Time              "
        "    ?????           "
        "                    ",
        360);

  uint2bcd(histogram.white, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[84], &digits[3], 5);

  uint2bcd(histogram.lgrey, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[144], &digits[3], 5);

  uint2bcd(histogram.dgrey, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[204], &digits[3], 5);

  uint2bcd(histogram.black, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[264], &digits[3], 5);

  uint2bcd(histogram.time, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[324], &digits[3], 5);
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
