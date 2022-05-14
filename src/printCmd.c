// Original library by DragonEagles from http://shen.mansell.tripod.com/games/gameboy/gameboy.html
// Ported to GBDK 2020 by T0biasCZe			
// Print Screen function added by Christianr
// Print Screen (360 tile mode) added by T0biasCZe

#include <gb/gb.h>
uint8_t PrinterStatus[3];

const uint8_t PRINTER_INIT[]={
    10,0x88,0x33,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00
};
const uint8_t PRINTER_STATUS[]={
    10,0x88,0x33,0x0F,0x00,0x00,0x00,0x0F,0x00,0x00,0x00
};
const uint8_t PRINTER_EOF[]={
    10,0x88,0x33,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00
};
const uint8_t PRINTER_START[]={
    14,0x88,0x33,0x02,0x00,0x04,0x00,0x01,0x03,0xE4,0x7F,0x6D,0x01,0x00,0x00
};
const uint8_t PRINT_TILE[]={
    6,0x88,0x33,0x04,0x00,0x80,0x02
};
const uint8_t PRINTER_LINE[]={
    14,0x88,0x33,0x02,0x00,0x04,0x00,0x01,0x00,0xE4,0x7F,0x6A,0x01,0x00,0x00
};

uint8_t tile_num, packet_num;

uint16_t CRC;

uint8_t SendPrinterByte(uint8_t byte){
    uint8_t result;
    disable_interrupts();
    SB_REG = byte; //data to send
    SC_REG = 0x81; //1000 0001 - start, internal clock
    while (SC_REG & 0x80){} //wait until b1 reset
    result = SB_REG; //return response stored in SB_REG
    enable_interrupts();
    return result;
}

void SendByte(uint8_t byte){
    uint8_t result;
    result = SendPrinterByte(byte);
    PrinterStatus[0]=PrinterStatus[1];
    PrinterStatus[1]=PrinterStatus[2];
    PrinterStatus[2]=result;
}

void SendPrinterCommand(uint8_t *Command){
    uint8_t length,index;
    index=0;
    length=*Command;
    while(index < length){
        index++;
        SendByte(*(Command+index));
    }
}

void PrinterInit (void)
{
    tile_num = 0;
    CRC = 0;
    packet_num = 0;

    SendPrinterCommand(PRINTER_INIT);
}

int CheckLinkCable(){
    if(PrinterStatus[0] != 0){
        return 2;
    }
    if((PrinterStatus[1] & 0xF0) != 0x80){
        return 2;
    }
    return 0;
}

int GetPrinterStatus(){
    SendPrinterCommand(PRINTER_STATUS);
    return CheckLinkCable();
}

int CheckForErrors(){
    if(PrinterStatus[2] & 128){
        return 1;
    }
    if(PrinterStatus[2] & 64){
        return 4;
    }
    if(PrinterStatus[2] & 32){
        return 3;
    }
    return 0;
}

uint8_t CheckBusy() {
    SendPrinterCommand(PRINTER_STATUS);
    return (PrinterStatus[2] & 0x2);
}

uint8_t GetHigh(uint16_t w) {
    return (w & 0xFF00u) >> 8;
}

uint8_t GetLow(uint16_t w) {
    return (w & 0xFFu);
}

void PrintTileData(uint8_t *TileData, uint8_t lf, uint8_t num_packets){
    uint8_t TileIndex;
    
    if (tile_num == 0)
    {
        SendPrinterCommand(PRINT_TILE);
        CRC = 0x04 + 0x80 + 0x02;
    }      
    
    tile_num ++;

    for(TileIndex = 0; TileIndex < 16; TileIndex++)
    {
        CRC += TileData[TileIndex];
        SendByte(TileData[TileIndex]);
    }

    if (tile_num == 40)
    {
        SendByte(GetLow(CRC));
        SendByte(GetHigh(CRC));
        SendByte(0x00);
        SendByte(0x00);
        tile_num = 0;  
        CRC = 0;
        packet_num ++;

        if (packet_num == num_packets) // all done the page
        {
            SendPrinterCommand(PRINTER_EOF); // data end packet
            if (lf)
                SendPrinterCommand(PRINTER_START);
            else
                SendPrinterCommand(PRINTER_LINE);
            packet_num = 0;
            SendPrinterCommand(PRINTER_STATUS);
        }
    }
}

void PrintScreen(uint8_t linefeed) {
    uint8_t x, y;
    uint8_t p_data[16];
    for (y=0; y<18; y++) {
        for (x=0; x<20; x++) {
            get_bkg_data(get_vram_byte(get_bkg_xy_addr(x, y)), 1, p_data);
            PrintTileData(p_data, linefeed, 9);
        }
    }
}

void PrintImage(uint8_t* lower, uint8_t* upper) {
    // We need to print a border of 16x16 pixels (2x2 tiles)
    uint8_t x, y;
    const uint8_t border[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint8_t* image = upper;
    for (y=0; y<18; y++) {
        for (x=0; x<20; x++) {
            if (x==0 && y==9) {
                image = lower;
            }
            if (x<2 || y<2 || x>=18 || y>=16) {
                PrintTileData(border, TRUE, 9);
            } else {
                PrintTileData(image, TRUE, 9);
                image += 16;
            }
        }
    }
}
