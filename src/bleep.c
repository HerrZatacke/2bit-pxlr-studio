#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>
#include "globals.h"
#include "images.h"
#include "defines.h"
#include "joypad.h"
#include "imageIndexing.h"
#include "images.h"

// Manual selection of tones
//const uint8_t freqLookupN33[] = { 0x00, 0x44, 0x70, 0x90, 0xa4, 0xb4, 0xc2, 0xcd, 0xd7, 0xde, 0xe4, 0xe8, 0xed, 0xf0, 0xf2, 0xf4, };
//const uint8_t freqLookupN34[] = { 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7,  };


// Manual selection of tones ~ 100Hz steps
// 809, 910, 1024, 1130, 1214, 1338, 1425, 1489, 1560, 1638, 1771, 1928, 2114, 2260, 2427, 2521 | 2979, 3449
const uint8_t freqLookupN33[] = { 0xaf, 0xb8, 0xc0, 0xc6, 0xca, 0xcf, 0xd2, 0xd4, 0xd6, 0xd8, 0xdb, 0xde, 0xe1, 0xe3, 0xe5, 0xe6, 0xea, 0xed, };
const uint8_t freqLookupN34[] = { 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, };

inline void silence() {
  NR30_REG=0x00;
}

uint8_t breakBleep = 0;

inline void loadWaveform() {
  const uint8_t sinewave[16] = { 0x89, 0xbc, 0xde, 0xff, 0xff, 0xfe, 0xdb, 0xa8, 0x75, 0x42, 0x10, 0x00, 0x00, 0x12, 0x34, 0x67 };
//  const uint8_t sinewavex2[16] = { 0x8b, 0xdf, 0xfe, 0xc9, 0x63, 0x10, 0x02, 0x47, 0xbd, 0xff, 0xec, 0x96, 0x31, 0x00, 0x24, 0x7b };
//  const uint8_t randwave[16] = { 0x13, 0x08, 0xd2, 0x53, 0xa1, 0xa0, 0x4f, 0x4c, 0x99, 0xbc, 0xe8, 0x7f, 0x62, 0xe7, 0x5b, 0xd6 };
//  const uint8_t sawtoothwave[16] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
//  const uint8_t sawtoothwave2[16] = { 0x02, 0x46, 0x8a, 0xce, 0x02, 0x46, 0x8a, 0xce, 0x02, 0x46, 0x8a, 0xce, 0x02, 0x46, 0x8a, 0xce, };
//  const uint8_t single[16] = { 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

  memcpy(_AUD3WAVERAM, sinewave, 16);
}

void breakSound(uint8_t times) BANKED {
  for(uint8_t i = 0; i < times; i++) {
    wait_vbl_done();
    if (jp == J_B) {
      breakBleep = 1;
      move_sprite(SPRITE_BLEEP_CURSOR, 0, 0);
      silence();
      return;
    }
  }
}

void playBeep(uint8_t r1, uint8_t r2) BANKED {
  NR30_REG=0x80;
  NR31_REG=0x00;
  NR32_REG=0x20;
  NR33_REG=r1;
  NR34_REG=r2;

  breakSound(1);
  silence();
  breakSound(1);
}

void bleep() BANKED {
  breakBleep = 0;
  loadWaveform();
  uint8_t imageAddress = getAddressForIndex(imageIndex);
  SWITCH_RAM(images[imageAddress]->bank);
  uint8_t i = 0;

  playBeep(freqLookupN33[17], freqLookupN34[17]);

  for (i = 0; i < 32; i += 1) {
    playBeep(freqLookupN33[i % 16], freqLookupN34[i % 16]);

    if (breakBleep == 1) {
      move_sprite(SPRITE_BLEEP_CURSOR, 0, 0);
      joypadConsumed();
      return;
    }
  }

  // Loop upper part
  for (uint16_t i = 0; i < HALF_IMAGE_SIZE; i++) {
    uint8_t tileByte = images[imageAddress]->tilesUpper[i];

    if (i % 16 == 0) {
      uint8_t tileIndex = i >> 4;
      uint8_t cursorX = tileIndex % 16;
      uint8_t cursorY = tileIndex >> 4;
      move_sprite(SPRITE_BLEEP_CURSOR, (cursorX << 3) + 24, (cursorY << 3) + 32);
      playBeep(freqLookupN33[17], freqLookupN34[17]);
    }

    playBeep(freqLookupN33[tileByte >> 4], freqLookupN34[tileByte >> 4]);
    playBeep(freqLookupN33[tileByte % 16], freqLookupN34[tileByte % 16]);

    if (breakBleep == 1) {
      move_sprite(SPRITE_BLEEP_CURSOR, 0, 0);
      joypadConsumed();
      return;
    }
  }

  // Loop lower part
  for (uint16_t i = 0; i < HALF_IMAGE_SIZE; i++) {
    uint8_t tileByte = images[imageAddress]->tilesLower[i];

    if (i % 16 == 0) {
      uint8_t tileIndex = i >> 4;
      uint8_t cursorX = tileIndex % 16;
      uint8_t cursorY = tileIndex >> 4;
      move_sprite(SPRITE_BLEEP_CURSOR, (cursorX << 3) + 24, (cursorY << 3) + 32 + 56);
      playBeep(freqLookupN33[17], freqLookupN34[17]);
    }

    playBeep(freqLookupN33[tileByte >> 4], freqLookupN34[tileByte >> 4]);
    playBeep(freqLookupN33[tileByte % 16], freqLookupN34[tileByte % 16]);

    if (breakBleep == 1) {
      move_sprite(SPRITE_BLEEP_CURSOR, 0, 0);
      joypadConsumed();
      return;
    }
  }

  playBeep(freqLookupN33[17], freqLookupN34[17]);

  move_sprite(SPRITE_BLEEP_CURSOR, 0, 0);
  joypadConsumed();
}
