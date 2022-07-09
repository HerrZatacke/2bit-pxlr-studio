#pragma bank 255

#include "shutter.h"

volatile uint8_t shutter_value;

inline void SIO_request_transfer() {
    SC_REG = 0x80;  // start transfer with external clock
}
inline void SIO_cancel_transfer() {
    SC_REG = 0x00;  // reset transfer request
}

void isr_SIO() NONBANKED {
    shutter_value = SB_REG; 
    SIO_request_transfer();
}

void init_shutter() BANKED {
    CRITICAL {
        add_SIO(isr_SIO);
    }
}

uint8_t activate_shutter(uint8_t value) BANKED {
    if (value) {
        set_interrupts(IE_REG | SIO_IFLAG);
        SIO_request_transfer();
    } else {
        set_interrupts(IE_REG & ~SIO_IFLAG);
        SIO_cancel_transfer();
    }
    return value;
}
