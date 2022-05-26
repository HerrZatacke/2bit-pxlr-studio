
unsigned char savedBank;
void set_bkg_tiles_banked(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char *map, unsigned char bank) {
  savedBank = _current_bank;
  SWITCH_ROM(bank);
  set_bkg_tiles(x, y, w, h, map);
  SWITCH_ROM(savedBank);
}

void set_bkg_data_banked(unsigned char offset, unsigned char length, unsigned char *data, unsigned char bank) {
  savedBank = _current_bank;
  SWITCH_ROM(bank);
  set_bkg_data(offset, length, data);
  SWITCH_ROM(savedBank);
}

void set_data_banked(unsigned int *address, unsigned char *data, unsigned int length, unsigned char bank) {
  savedBank = _current_bank;
  SWITCH_ROM(bank);
  set_data(address, data, length);
  SWITCH_ROM(savedBank);
}
