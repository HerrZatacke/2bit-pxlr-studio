unsigned char last_seen_upper[1792];    // 0x0000 - 0x0699
unsigned char last_seen_lower[1792];    // 0x0700 - 0x0DFF
unsigned char last_seen_padding[512];   // 0x0E00 - 0x0FFF

// https://funtography.online/wiki/Cartridge_RAM
// position of frame in ram: 0x0F54
// position of frame in meta: 0x01B0 -> 84
// + 92
// position of frame in ram: 0x0FB0
// position of frame in meta: 0x01B0 -> 176

unsigned char game_data_meta[4096];
