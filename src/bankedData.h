#ifndef BANKEDDATA_H
#define BANKEDDATA_H

#include <gbdk/platform.h>

extern void set_bkg_tiles_banked(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t *map, uint8_t bank);
extern void set_bkg_data_banked(uint8_t offset, uint8_t length, uint8_t *data, uint8_t bank);
extern void set_data_banked(unsigned int *address, uint8_t *data, unsigned int length, uint8_t bank);

#endif
