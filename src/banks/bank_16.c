volatile unsigned char A000;
unsigned char A001; // output gain and the edge operation mode.
unsigned char A002; // register 2 of M64282FP - exposure time MSB
unsigned char A003; // register 3 of M64282FP - exposure time LSB
unsigned char A004; // register 7 of M64282FP - sets the output voltage reference, the edge enhancement ratio and it can invert the image
unsigned char A005; // register 0 of M64282FP - sets the output reference voltage and enables the zero point calibration.

unsigned char A006A035[48]; // registers form a 4×4 matrix with 3 bytes per element. They handle dithering and contrast, and they are sorted by rows
