#ifndef BANKEDDATA_H
#define BANKEDDATA_H

extern void set_bkg_tiles_banked(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char *map, unsigned char bank);
extern void set_bkg_data_banked(unsigned char offset, unsigned char length, unsigned char *data, unsigned char bank);
extern void set_data_banked(unsigned int *address, unsigned char *data, unsigned int length, unsigned char bank);

#endif
