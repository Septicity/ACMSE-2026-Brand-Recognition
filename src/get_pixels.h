#ifndef GET_PIXELS_H
#define GET_PIXELS_H

#include <stdint.h>

uint8_t** get_pixels(const char* filename, int* width, int* height);
int save_pixels(const char* filename, uint8_t** pixels, int width, int height);

#endif