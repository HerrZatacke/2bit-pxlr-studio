#ifndef BANKS_H
#define BANKS_H

#include "../typedefs/Image.h"

extern unsigned char last_seen_upper[];
extern unsigned char last_seen_lower[];

extern unsigned char game_data_meta_imageslots[30];
extern unsigned char game_data_meta_magic[5];
extern unsigned char game_data_meta_imageslots_checksum[2];
extern unsigned char game_data_meta_imageslots_echo[30];
extern unsigned char game_data_meta_magic_echo[5];
extern unsigned char game_data_meta_imageslots_echo_checksum[2];
extern unsigned char game_data_meta[];

extern const Image *images[30];

extern volatile unsigned char A000;
extern unsigned char A001;
extern unsigned char A002;
extern unsigned char A003;
extern unsigned char A004;
extern unsigned char A005;
extern unsigned char A006A035[48];

extern unsigned char image_01_unused[];
extern unsigned char image_02_unused[];

#endif
