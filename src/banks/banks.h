#ifndef BANKS_H
#define BANKS_H

#include <gbdk/platform.h>
#include "../typedefs/Image.h"

extern uint8_t last_seen_upper[];
extern uint8_t last_seen_lower[];

extern uint8_t game_data_meta_imageslots[30];
extern uint8_t game_data_meta_magic[5];
extern uint8_t game_data_meta_imageslots_checksum[2];
extern uint8_t game_data_meta_imageslots_echo[30];
extern uint8_t game_data_meta_magic_echo[5];
extern uint8_t game_data_meta_imageslots_echo_checksum[2];
extern uint8_t game_data_meta[];

extern const Image *images[30];

extern volatile uint8_t A000;
extern uint8_t A001;
extern uint8_t A002;
extern uint8_t A003;
extern uint8_t A004;
extern uint8_t A005;
extern uint8_t A006A035[48];

extern uint8_t image_01_unused[];
extern uint8_t image_02_unused[];

#endif
