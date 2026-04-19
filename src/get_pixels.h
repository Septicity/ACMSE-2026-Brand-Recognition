#ifndef GET_PIXELS_H
#define GET_PIXELS_H

#include <stdint.h>

extern uint8_t colors[];
#define PALETTE_SIZE 255
#include "gifenc.h"

uint8_t** get_pixels(const char* filename, int* width, int* height);
int save_pixels(const char* filename, uint16_t** pixels, int width, int height);
int countZeros(uint16_t** segmentMap, int height, int width);
int saveGifFrame(ge_GIF* gif, uint16_t** segmentMap, int width, int height);

#endif