#include "../version.h"
#include "../branch.h"

inline void init_gfx() {
  ENABLE_RAM;
  SHOW_BKG;
  BGP_REG = PALETTE_NORMAL;

  OBP0_REG = OBP1_REG = PALETTE_SPRITES;
  SHOW_SPRITES;
  SPRITES_8x8;

  SHOW_WIN;
  move_win(7, 146);

  set_sprite_tile(SPRITE_MENU_INDICATOR, OFFSET_MENU_ARROW);
  set_sprite_tile(SPRITE_BLEEP_CURSOR, OFFSET_BLEEP_CURSOR);
}

inline void init_sound() {
  // This enables sound, registers must be in this specific order!
  NR52_REG = 0x80;
  NR50_REG = 0x77;
  NR51_REG = 0xFF;
}

inline void beep() {
  NR21_REG=0x80;
  NR22_REG=0xA2;
  NR23_REG=0x60;
  NR24_REG=0x87;
}

inline void boop() {
  NR21_REG=0x80;
  NR22_REG=0xA2;
  NR23_REG=0xD7;
  NR24_REG=0x86;
}

inline void clonk() {
  NR41_REG=0x01;
  NR42_REG=0xC1;
  NR43_REG=0x70;
  NR44_REG=0xC0;
}

inline void clearBkg() {
  fill_bkg_rect(0, 0, 20, 18, OFFSET_BLANK);
}

inline void pause(unsigned char frames) {
  for (unsigned char i = 0; i < frames; i++) {
    wait_vbl_done();
  }
}

unsigned char digits_map[10];
void writeNumber(unsigned char x, unsigned char y, unsigned char length, unsigned char number) {
  BCD bcd = MAKE_BCD(0);
  uint2bcd(number, &bcd);
  bcd2text(&bcd, OFFSET_FONT + 16u, digits_map);

  unsigned char digits[3] = { 0x80, 0x80 , 0x80, };

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
void dead(/*unsigned char reason*/) {
  while (1) {
    boop();
    for(unsigned char i = 0; i < 120; i++) {
      wait_vbl_done();
    }
  }
}

inline unsigned char splash() {
/*
  set_data(VRAM_9000, logo_tiles, LOGO_TILE_COUNT * 16);
  set_data(VRAM_8000, logo_tiles, LOGO_TILE_COUNT * 16);

  set_bkg_tiles(0, 0, 20, 18, logo_map);
*/
  set_bkg_based_tiles(0, 16, sizeof(branch), 1, branch, OFFSET_FONT - 32);
  set_bkg_based_tiles(0, 17, sizeof(version), 1, version, OFFSET_FONT - 32);
  set_bkg_based_tiles(13, 16, 7, 2, "Shoot A Menu B", OFFSET_FONT - 32);

  while (jp != J_A && jp != J_B) {
    wait_vbl_done();
  }

  unsigned char result = jp;

  waitRelease(); // waitRelease() resets `jp`

  return result;
}
