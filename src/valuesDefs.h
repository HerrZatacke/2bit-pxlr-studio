#ifndef VALUES_DEFS_H
#define VALUES_DEFS_H

#define NUM_GAIN_LEVELS 21
#define NUM_EXPOSURE_TIMES 32
#define NUM_CONTRASTS 16
#define NUM_CONTRAST_SIZE 48
#define NUM_DITHERSETS 4
#define NUM_EDGE_MODES 8
#define NUM_VOLTAGE_REFS 8
#define NUM_ZERO_POINTS 3
#define NUM_CAPTURE_MODES 2
#define NUM_VOLTAGE_OUTS 64
#define NUM_EDGE_OP_MODES 4
#define NUM_EDGE_EXCLUSIVE 2
#define NUM_INVERT_OUTPUTS 2

#define DITHER_SET_HIGH 0
#define DITHER_SET_LOW 1
#define DITHER_SET_NO_HIGH 2
#define DITHER_SET_NO_LOW 3

#define A000_MASK_CAPTURE          0b00000011

#define A001_MASK_EDGE_EXCLUSIVE   0b10000000
#define A001_MASK_EDGE_OP_MODE     0b01100000
#define A001_MASK_GAIN             0b00011111

#define A004_MASK_EDGE_RATIO       0b01110000
#define A004_MASK_INVERT_OUTPUT    0b00001000
#define A004_MASK_VOLTAGE_REF      0b00000111

#define A005_MASK_ZERO             0b11000000
#define A005_MASK_VOLTAGE_OUT      0b00111111

#define A000_START_CAPTURE_POSITIVE 0b00000011
#define A000_START_CAPTURE_NEGATIVE 0b00000001

// The Game Boy Camera uses 0x00, 0x04, 0x08 and 0x0
// They are 14.0dB, 20.0dB, 26.0dB and 32dB, which translate to a gain of 5.01, 10.00, 19.95 and 39.81.
#define A001_GAIN_140   0b00000000 // 14.0 (gbcam gain:  5.01)
#define A001_GAIN_155   0b00000001 // 15.5
#define A001_GAIN_170   0b00000010 // 17.0
#define A001_GAIN_185   0b00000010 // 18.5
#define A001_GAIN_200   0b00000100 // 20.0 (gbcam gain: 10.00)
#define A001_GAIN_200_D 0b00010000 // 20.0 (d)
#define A001_GAIN_215   0b00000101 // 21.5
#define A001_GAIN_215_D 0b00010001 // 21.5 (d)
#define A001_GAIN_230   0b00000110 // 23.0
#define A001_GAIN_230_D 0b00010010 // 23.0 (d)
#define A001_GAIN_245   0b00000111 // 24.5
#define A001_GAIN_245_D 0b00010010 // 24.5 (d)
#define A001_GAIN_260   0b00001000 // 26.0 (gbcam gain: 19.95)
#define A001_GAIN_260_D 0b00010100 // 26.0 (d)
#define A001_GAIN_275   0b00010101 // 27.5
#define A001_GAIN_290   0b00001001 // 29.0
#define A001_GAIN_290_D 0b00010110 // 29.0 (d)
#define A001_GAIN_305   0b00010111 // 30.5
#define A001_GAIN_320   0b00001010 // 32.0 (gbcam gain: 39.81)
#define A001_GAIN_320_D 0b00011000 // 32.0 (d)
#define A001_GAIN_350   0b00001011 // 35.0
#define A001_GAIN_350_D 0b00011001 // 35.0 (d)
#define A001_GAIN_380   0b00001100 // 38.0
#define A001_GAIN_380_D 0b00011010 // 38.0 (d)
#define A001_GAIN_410   0b00001101 // 41.0
#define A001_GAIN_410_D 0b00011011 // 41.0 (d)
#define A001_GAIN_440   0b00011100 // 44.0
#define A001_GAIN_455   0b00001110 // 45.5
#define A001_GAIN_470   0b00011101 // 47.0
#define A001_GAIN_515   0b00001111 // 51.5
#define A001_GAIN_515_D 0b00011110 // 51.5 (d)
#define A001_GAIN_575   0b00011111 // 57.5

#define A001_EDGE_OP_MODE_NONE       0b00000000
#define A001_EDGE_OP_MODE_HORIZONTAL 0b00100000
#define A001_EDGE_OP_MODE_VERTICAL   0b01000000
#define A001_EDGE_OP_MODE_2D         0b01100000

#define A001_EDGE_EXCLUSIVE_VERT_ON      0b10000000
#define A001_EDGE_EXCLUSIVE_VERT_OFF     0b00000000

#define A004_EDGE_RATIO_050   0b00000000
#define A004_EDGE_RATIO_075   0b00010000
#define A004_EDGE_RATIO_100   0b00100000
#define A004_EDGE_RATIO_125   0b00110000
#define A004_EDGE_RATIO_200   0b01000000
#define A004_EDGE_RATIO_300   0b01010000
#define A004_EDGE_RATIO_400   0b01100000
#define A004_EDGE_RATIO_500   0b01110000

#define A004_INVERT_OUTPUT_ON    0b00001000
#define A004_INVERT_OUTPUT_OFF   0b00000000

#define A004_VOLTAGE_REF_00   0b00000000
#define A004_VOLTAGE_REF_05   0b00000001
#define A004_VOLTAGE_REF_10   0b00000010
#define A004_VOLTAGE_REF_15   0b00000011
#define A004_VOLTAGE_REF_20   0b00000100
#define A004_VOLTAGE_REF_25   0b00000101
#define A004_VOLTAGE_REF_30   0b00000110
#define A004_VOLTAGE_REF_35   0b00000111

#define A005_ZERO_DISABLED    0b00000000
#define A005_ZERO_POSITIVE    0b10000000
#define A005_ZERO_NEGATIVE    0b01000000

#define A005_VOLTAGE_OUT_NEG_992 0b00011111 // -0.992mV
#define A005_VOLTAGE_OUT_NEG_960 0b00011110 // -0.960mV
#define A005_VOLTAGE_OUT_NEG_928 0b00011101 // -0.928mV
#define A005_VOLTAGE_OUT_NEG_896 0b00011100 // -0.896mV
#define A005_VOLTAGE_OUT_NEG_864 0b00011011 // -0.864mV
#define A005_VOLTAGE_OUT_NEG_832 0b00011010 // -0.832mV
#define A005_VOLTAGE_OUT_NEG_800 0b00011001 // -0.800mV
#define A005_VOLTAGE_OUT_NEG_768 0b00011000 // -0.768mV
#define A005_VOLTAGE_OUT_NEG_736 0b00010111 // -0.736mV
#define A005_VOLTAGE_OUT_NEG_704 0b00010110 // -0.704mV
#define A005_VOLTAGE_OUT_NEG_672 0b00010101 // -0.672mV
#define A005_VOLTAGE_OUT_NEG_640 0b00010100 // -0.640mV
#define A005_VOLTAGE_OUT_NEG_608 0b00010011 // -0.608mV
#define A005_VOLTAGE_OUT_NEG_576 0b00010010 // -0.576mV
#define A005_VOLTAGE_OUT_NEG_544 0b00010001 // -0.544mV
#define A005_VOLTAGE_OUT_NEG_512 0b00010000 // -0.512mV
#define A005_VOLTAGE_OUT_NEG_480 0b00001111 // -0.480mV
#define A005_VOLTAGE_OUT_NEG_448 0b00001110 // -0.448mV
#define A005_VOLTAGE_OUT_NEG_416 0b00001101 // -0.416mV
#define A005_VOLTAGE_OUT_NEG_384 0b00001100 // -0.384mV
#define A005_VOLTAGE_OUT_NEG_352 0b00001011 // -0.352mV
#define A005_VOLTAGE_OUT_NEG_320 0b00001010 // -0.320mV
#define A005_VOLTAGE_OUT_NEG_288 0b00001001 // -0.288mV
#define A005_VOLTAGE_OUT_NEG_256 0b00001000 // -0.256mV
#define A005_VOLTAGE_OUT_NEG_224 0b00000111 // -0.224mV
#define A005_VOLTAGE_OUT_NEG_192 0b00000110 // -0.192mV
#define A005_VOLTAGE_OUT_NEG_160 0b00000101 // -0.160mV
#define A005_VOLTAGE_OUT_NEG_128 0b00000100 // -0.128mV
#define A005_VOLTAGE_OUT_NEG_096 0b00000011 // -0.096mV
#define A005_VOLTAGE_OUT_NEG_064 0b00000010 // -0.064mV
#define A005_VOLTAGE_OUT_NEG_032 0b00000001 // -0.032mV
#define A005_VOLTAGE_OUT_NEG_000 0b00000000 // -0.000mV
#define A005_VOLTAGE_OUT_POS_000 0b00100000 //  0.000mV
#define A005_VOLTAGE_OUT_POS_032 0b00100001 //  0.032mV
#define A005_VOLTAGE_OUT_POS_064 0b00100010 //  0.064mV
#define A005_VOLTAGE_OUT_POS_096 0b00100011 //  0.096mV
#define A005_VOLTAGE_OUT_POS_128 0b00100100 //  0.128mV
#define A005_VOLTAGE_OUT_POS_160 0b00100101 //  0.160mV
#define A005_VOLTAGE_OUT_POS_192 0b00100110 //  0.192mV
#define A005_VOLTAGE_OUT_POS_224 0b00100111 //  0.224mV
#define A005_VOLTAGE_OUT_POS_256 0b00101000 //  0.256mV
#define A005_VOLTAGE_OUT_POS_288 0b00101001 //  0.288mV
#define A005_VOLTAGE_OUT_POS_320 0b00101010 //  0.320mV
#define A005_VOLTAGE_OUT_POS_352 0b00101011 //  0.352mV
#define A005_VOLTAGE_OUT_POS_384 0b00101100 //  0.384mV
#define A005_VOLTAGE_OUT_POS_416 0b00101101 //  0.416mV
#define A005_VOLTAGE_OUT_POS_448 0b00101110 //  0.448mV
#define A005_VOLTAGE_OUT_POS_480 0b00101111 //  0.480mV
#define A005_VOLTAGE_OUT_POS_512 0b00110000 //  0.512mV
#define A005_VOLTAGE_OUT_POS_544 0b00110001 //  0.544mV
#define A005_VOLTAGE_OUT_POS_576 0b00110010 //  0.576mV
#define A005_VOLTAGE_OUT_POS_608 0b00110011 //  0.608mV
#define A005_VOLTAGE_OUT_POS_640 0b00110100 //  0.640mV
#define A005_VOLTAGE_OUT_POS_672 0b00110101 //  0.672mV
#define A005_VOLTAGE_OUT_POS_704 0b00110110 //  0.704mV
#define A005_VOLTAGE_OUT_POS_736 0b00110111 //  0.736mV
#define A005_VOLTAGE_OUT_POS_768 0b00111000 //  0.768mV
#define A005_VOLTAGE_OUT_POS_800 0b00111001 //  0.800mV
#define A005_VOLTAGE_OUT_POS_832 0b00111010 //  0.832mV
#define A005_VOLTAGE_OUT_POS_864 0b00111011 //  0.864mV
#define A005_VOLTAGE_OUT_POS_896 0b00111100 //  0.896mV
#define A005_VOLTAGE_OUT_POS_928 0b00111101 //  0.928mV
#define A005_VOLTAGE_OUT_POS_960 0b00111110 //  0.960mV
#define A005_VOLTAGE_OUT_POS_992 0b00111111 //  0.992mV

#endif
