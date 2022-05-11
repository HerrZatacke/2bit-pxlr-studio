
// Manual selection of tones
//const unsigned char freqLookupN33[] = { 0x00, 0x44, 0x70, 0x90, 0xa4, 0xb4, 0xc2, 0xcd, 0xd7, 0xde, 0xe4, 0xe8, 0xed, 0xf0, 0xf2, 0xf4, };
//const unsigned char freqLookupN34[] = { 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7,  };


// Manual selection of tones ~ 100Hz steps
// 809, 910, 1024, 1130, 1214, 1338, 1425, 1489, 1560, 1638, 1771, 1928, 2114, 2260, 2427, 2521 | 2979, 3449
const unsigned char freqLookupN33[] = { 0xaf, 0xb8, 0xc0, 0xc6, 0xca, 0xcf, 0xd2, 0xd4, 0xd6, 0xd8, 0xdb, 0xde, 0xe1, 0xe3, 0xe5, 0xe6, 0xea, 0xed, };
const unsigned char freqLookupN34[] = { 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, };

inline void silence() {
  NR30_REG=0x00;
}

unsigned char breakBleep = 0;

void breakSound(unsigned char times) {
  for(unsigned char i = 0; i < times; i++) {
    if (joypad() == J_B) {
      breakBleep = 1;
      move_sprite(SPRITE_BLEEP_CURSOR, 0, 0);
      silence();
      return;
    }
    wait_vbl_done();
  }
}

void playBeep(unsigned char r1, unsigned char r2) {
  NR30_REG=0x80;
  NR31_REG=0x00;
  NR32_REG=0x20;
  NR33_REG=r1;
  NR34_REG=r2;

  breakSound(1);
  silence();
  breakSound(1);
}

void bleep() {
  unsigned char imageAddress = getAddressForIndex(imageIndex);
  SWITCH_RAM(images[imageAddress]->bank);
  unsigned char i = 0;

  playBeep(freqLookupN33[17], freqLookupN34[17]);

  for (i = 0; i < 16; ++i) {
    playBeep(freqLookupN33[i], freqLookupN34[i]);
  }
  for (i = 0; i < 16; ++i) {
    playBeep(freqLookupN33[i], freqLookupN34[i]);
  }

  // Loop upper part
  for (unsigned int i = 0; i < HALF_IMAGE_SIZE; i++) {
    unsigned char tileByte = images[imageAddress]->tilesUpper[i];

    if (i % 16 == 0) {
      unsigned char tileIndex = i >> 4;
      unsigned char cursorX = tileIndex % 16;
      unsigned char cursorY = tileIndex >> 4;
      move_sprite(SPRITE_BLEEP_CURSOR, (cursorX << 3) + 24, (cursorY << 3) + 32);
      playBeep(freqLookupN33[17], freqLookupN34[17]);
//      breakSound(5);
    }

    playBeep(freqLookupN33[tileByte >> 4], freqLookupN34[tileByte >> 4]);
    playBeep(freqLookupN33[tileByte % 16], freqLookupN34[tileByte % 16]);

    if (breakBleep == 1) {
      breakBleep = 0;
      return;
    }
  }

  // Loop lower part
  for (unsigned int i = 0; i < HALF_IMAGE_SIZE; i++) {
    unsigned char tileByte = images[imageAddress]->tilesLower[i];

    if (i % 16 == 0) {
      unsigned char tileIndex = i >> 4;
      unsigned char cursorX = tileIndex % 16;
      unsigned char cursorY = tileIndex >> 4;
      move_sprite(SPRITE_BLEEP_CURSOR, (cursorX << 3) + 24, (cursorY << 3) + 32 + 56);
      playBeep(freqLookupN33[17], freqLookupN34[17]);
//      breakSound(5);
    }

    playBeep(freqLookupN33[tileByte >> 4], freqLookupN34[tileByte >> 4]);
    playBeep(freqLookupN33[tileByte % 16], freqLookupN34[tileByte % 16]);

    if (breakBleep == 1) {
      breakBleep = 0;
      return;
    }
  }

  playBeep(freqLookupN33[17], freqLookupN34[17]);

  move_sprite(SPRITE_BLEEP_CURSOR, 0, 0);
}
