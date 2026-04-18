#ifndef GET_PIXELS_H
#define GET_PIXELS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

uint8_t **get_pixels(const char *filename);

#endif