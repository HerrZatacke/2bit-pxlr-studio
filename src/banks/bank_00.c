#include <gbdk/platform.h>

uint8_t last_seen_upper_unused[256]; // 0x0000 - 0x00FF
uint8_t last_seen_upper[1792];       // 0x0100 - 0x0799
uint8_t last_seen_lower[1792];       // 0x0800 - 0x0EFF
uint8_t last_seen_padding[256];      // 0x0F00 - 0x0FFF

uint8_t game_data_meta_pad_0[434];

uint8_t game_data_meta_imageslots[30];
uint8_t game_data_meta_magic[5];
uint8_t game_data_meta_imageslots_checksum[2];

uint8_t game_data_meta_imageslots_echo[30];
uint8_t game_data_meta_magic_echo[5];
uint8_t game_data_meta_imageslots_echo_checksum[2];

uint8_t game_data_meta[3588];
