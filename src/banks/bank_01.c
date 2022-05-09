unsigned char image_01_upper[1792];
unsigned char image_01_lower[1792];
unsigned char image_01_thumbnail[256];
unsigned char image_01_meta[92];
unsigned char image_01_meta_echo[92];
unsigned char image_01_padding[51];
unsigned char image_01_unused[21];

unsigned char image_02_upper[1792];
unsigned char image_02_lower[1792];
unsigned char image_02_thumbnail[256];
unsigned char image_02_meta[92];
unsigned char image_02_meta_echo[92];
unsigned char image_02_padding[51];
unsigned char image_02_unused[21];

// https://funtography.online/wiki/Cartridge_RAM
// position of frame in ram: 0xnF54
// position of frame in meta: 0xn1B0 -> 84
// + 92
// position of frame in ram: 0xnFB0
// position of frame in meta: 0xn1B0 -> 176
