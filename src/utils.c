#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>
#include <gbdk/bcd.h>
#include "defines.h"
#include "font.h"
#include "tiles.h"
#include "bankedData.h"

#define EXPOSURE_MICROS_STEP 4096
#define EXPOSURE_NANOS_STEP 16

void clearBkg() BANKED {
  fill_bkg_rect(0, 0, 20, 18, OFFSET_BLANK);
}

void initGfx() BANKED {
  SHOW_BKG;
  BGP_REG = PALETTE_NORMAL;

  OBP0_REG = OBP1_REG = PALETTE_SPRITES;
  SHOW_SPRITES;
  SPRITES_8x8;

  SHOW_WIN;
  move_win(7, 146);

  set_sprite_tile(SPRITE_MENU_INDICATOR, OFFSET_MENU_ARROW);
  set_sprite_tile(SPRITE_BLEEP_CURSOR, OFFSET_BLEEP_CURSOR);

  clearBkg();
  set_bkg_data_banked(OFFSET_FONT, NUM_FONT_CHARS, font, 1);
  set_bkg_data_banked(OFFSET_TILES, NUM_CONSTANT_TILES, constantTiles, 1);
  set_data((uint8_t *)0x9700, upperLowerDoubleTiles, 256);
  set_data((uint8_t *)0x8700, upperLowerDoubleTiles, 256);
}

void initSound() BANKED {
  // This enables sound, registers must be in this specific order!
  NR52_REG = 0x80;
  NR50_REG = 0x77;
  NR51_REG = 0xFF;
}

void beep() BANKED {
  NR21_REG=0x80;
  NR22_REG=0xA2;
  NR23_REG=0x60;
  NR24_REG=0x87;
}

void boop() BANKED {
  NR21_REG=0x80;
  NR22_REG=0xA2;
  NR23_REG=0xD7;
  NR24_REG=0x86;
}

void clonk() BANKED {
  NR41_REG=0x01;
  NR42_REG=0xC1;
  NR43_REG=0x70;
  NR44_REG=0xC0;
}

void pause(uint8_t frames) BANKED {
  for (uint8_t i = 0; i < frames; i++) {
    wait_vbl_done();
  }
}

uint8_t digits_map[10];
void writeNumber(uint8_t x, uint8_t y, uint8_t length, uint8_t number) BANKED {
  BCD bcd = MAKE_BCD(0);
  uint2bcd(number, &bcd);
  bcd2text(&bcd, OFFSET_FONT + 16u, digits_map);

  uint8_t digits[3] = { 0x80, 0x80 , 0x80, };

  if (length == 1) {
    digits[0] = digits_map[7];
    set_bkg_tiles(x + 2, y, 1, 1, digits);
    return;
  }

  if (length == 2) {
    digits[1] = digits_map[7];

    if (number > 9) {
      digits[0] = digits_map[6];
    }

    set_bkg_tiles(x + 1, y, 2, 1, digits);
    return;
  }

  if (length == 3) {
    digits[2] = digits_map[7];

    if (number > 9) {
      digits[1] = digits_map[6];
    }

    if (number > 99) {
      digits[0] = digits_map[5];
    }

    set_bkg_tiles(x, y, 3, 1, digits);
    return;
  }
}

// ToDo: add a "reason" for calling "dead"
void dead(/*uint8_t reason*/) BANKED {
  while (1) {
    boop();
    for(uint8_t i = 0; i < 120; i++) {
      wait_vbl_done();
    }
  }
}

const uint8_t hexCharLUT[] = "0123456789ABCDEF";

void hexChar(uint8_t *target, uint8_t value) BANKED {
  target[0] = hexCharLUT[(value >> 4) & 0b00001111];
  target[1] = hexCharLUT[value & 0b00001111];
}

void fadeIn() BANKED {
  pause(8);
  BGP_REG = PALETTE_FADE_2;
  pause(8);
  BGP_REG = PALETTE_FADE_1;
  pause(8);
  BGP_REG = PALETTE_NORMAL;
}

void fadeOut() BANKED {
  pause(8);
  BGP_REG = PALETTE_FADE_1;
  pause(8);
  BGP_REG = PALETTE_FADE_2;
  pause(8);
  BGP_REG = PALETTE_BLANK;
}

void describeExposureTime(uint16_t exposureTime, uint8_t *target) BANKED {
  BCD bcd = MAKE_BCD(0);
  uint8_t str[10];

  uint32_t lower = (exposureTime >> 8) & 0xff;
  uint32_t upper = exposureTime & 0xff;

  uint32_t micros = upper * EXPOSURE_MICROS_STEP + lower * EXPOSURE_NANOS_STEP;

  uint16_t numericValue = micros / 1000;

  uint8_t decimals = 0;

  if (numericValue < 10) {
    numericValue = micros / 10;
    decimals = 2;
  } else if (numericValue < 100) {
    numericValue = micros / 100;
    decimals = 1;
  }

  uint2bcd(numericValue, &bcd);
  bcd2text(&bcd, 48u, str);
  memcpy(target, &str[4], 4);

  if (decimals == 1) {
    target[0] = str[5];
    target[1] = str[6];
    target[2] = '.';
    target[3] = str[7];
  } else if (decimals == 2) {
    target[0] = str[5];
    target[1] = '.';
    target[2] = str[6];
    target[3] = str[7];
  } else {
    for (uint8_t i = 0; i < 3; i++) {
      if (target[i] != '0') {
        return;
      }
      target[i] = ' ';
    }
  }

}
