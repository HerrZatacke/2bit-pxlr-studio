#include <gbdk/platform.h>
#include <gb/gb.h>
#include "globals.h"

static uint8_t savedBank;

void set_bkg_tiles_banked(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t *map, uint8_t bank) {
  savedBank = _current_bank;
  SWITCH_ROM(bank);
  set_bkg_tiles(x, y, w, h, map);
  SWITCH_ROM(savedBank);
}

void set_bkg_data_banked(uint8_t offset, uint8_t length, uint8_t *data, uint8_t bank) {
  savedBank = _current_bank;
  SWITCH_ROM(bank);
  set_bkg_data(offset, length, data);
  SWITCH_ROM(savedBank);
}

void set_data_banked(uint16_t *address, uint8_t *data, uint16_t length, uint8_t bank) {
  savedBank = _current_bank;
  SWITCH_ROM(bank);
  set_data(address, data, length);
  SWITCH_ROM(savedBank);
}
