unsigned char last_seen_upper[1792];    // 0x0000 - 0x0699
unsigned char last_seen_lower[1792];    // 0x0700 - 0x0DFF
unsigned char last_seen_padding[512];   // 0x0E00 - 0x0FFF

unsigned char game_data_meta_pad_0[434];

unsigned char game_data_meta_imageslots[30];
unsigned char game_data_meta_magic[5];
unsigned char game_data_meta_imageslots_checksum[2];

unsigned char game_data_meta_imageslots_echo[30];
unsigned char game_data_meta_magic_echo[5];
unsigned char game_data_meta_imageslots_echo_checksum[2];

unsigned char game_data_meta[3588];
