#ifndef ANALYSIS_H
#define ANALYSIS_H

extern void createHistogram(uint8_t *data) BANKED;
extern void getHistogram(uint8_t imageIndex, uint8_t *tileMap) BANKED;
extern void displayHistogram(uint8_t imageIndex) BANKED;

#endif
