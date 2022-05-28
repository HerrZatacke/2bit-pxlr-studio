#pragma bank 1

#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>
#include "../res/maps.h"
#include "../res/frames/frame_pxlr.h"
#include "../res/font.h"
#include "../res/tiles.h"
#include "./banks/banks.h"
#include "./bankedData.h"
#include "./joypad.h"
#include "./defines.h"
#include "./globals.h"
#include "./utils.h"
#include "./imageIndexing.h"

#define PALETTE_EXPOSE_0 0b00000011u
#define PALETTE_EXPOSE_1 0b00001111u
#define PALETTE_EXPOSE_2 0b00111111u

#define MSB2LSB(b) (((b)&1?128:0)|((b)&2?64:0)|((b)&4?32:0)|((b)&8?16:0)|((b)&16?8:0)|((b)&32?4:0)|((b)&64?2:0)|((b)&128?1:0))

const unsigned char exposePalettes[3] = {
  PALETTE_EXPOSE_0,
  PALETTE_EXPOSE_1,
  PALETTE_EXPOSE_2,
};

unsigned char exposeIndex = 0;

// ToDo: convert this to a "flipTiles" function and then use set_data() to write to vram
void set_bkg_data_flipped(unsigned char from, unsigned char length, const unsigned char tiles[], const unsigned char vramHighLow) BANKED OLDCALL {

  unsigned char flippedTiles[HALF_IMAGE_SIZE];
  memcpy(flippedTiles, tiles, HALF_IMAGE_SIZE);

  for (uint16_t i = 0; i < 1792; i += 1) {
    flippedTiles[i] = MSB2LSB(flippedTiles[i]);
  }

  if (vramHighLow) {
    LCDC_REG &= ~LCDCF_BG8000;
  } else {
    LCDC_REG |= LCDCF_BG8000;
  }

  set_bkg_data(from, length, flippedTiles);
}

void set_flipped_map(const unsigned char map[], unsigned char offset) BANKED OLDCALL {
  unsigned char flippedMap[360];
  for (uint16_t yc = 0; yc < 360; yc += 20) {
    for (unsigned char xc = 0; xc < 20; xc += 1) {
      flippedMap[xc + yc] = map[yc + 19 - xc];
    }
  }
  set_bkg_based_tiles(0, 0, 20, 18, flippedMap, offset);
}

void loadImageTilesFlipped() BANKED OLDCALL {
  unsigned char imageSlot = getImageSlot(imageIndex);
  SWITCH_RAM(images[imageSlot]->bank);

  set_bkg_data_flipped(0, 112, images[imageSlot]->tilesUpper, 1);
  set_bkg_data_flipped(0, 112, images[imageSlot]->tilesLower, 0);
  set_bkg_tiles_banked(2, 2, 16, 14, map_flipped, 1);
}


void expose() BANKED OLDCALL {
  BGP_REG = PALETTE_BLANK;

  // ToDo - Use functions in banked.h
  unsigned char savedBank = _current_bank;
  SWITCH_ROM(1);
  set_bkg_data_flipped(OFFSET_FONT, FRAME_PXLR_TILE_COUNT, frame_pxlr_tiles, 1);
  set_flipped_map(frame_pxlr_map, OFFSET_FONT);
  SWITCH_ROM(savedBank);

  loadImageTilesFlipped();
  waitRelease();

  while (jp != J_B) {

    BGP_REG = exposePalettes[exposeIndex];
    exposeIndex = (exposeIndex + 1) % 3;

//    BGP_REG = PALETTE_INVERTED;
//    BGP_REG = PALETTE_NORMAL;

    wait_vbl_done();
    wait_vbl_done();
    wait_vbl_done();
  }

  joypadConsumed();
  waitRelease();


  // Back to normal
  BGP_REG = PALETTE_BLANK;
  clearBkg();
  set_bkg_data_banked(OFFSET_FONT, NUM_FONT_CHARS, font, 1);
  set_bkg_data_banked(OFFSET_TILES, NUM_CONSTANT_TILES, constantTiles, 1);
  set_bkg_tiles_banked(2, 2, 16, 14, map_normal, 1);

  BGP_REG = PALETTE_NORMAL;
}
