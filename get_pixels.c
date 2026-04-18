#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Pixel;

uint8_t **get_pixels(const char *filename) { //returns a 2d array of pixels
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 4);

    //printf("Original channels: %d\n", channels);

    int pixel_count = width * height;

    //create a 2d array of the same length and width as the image
    //and copy the r values into it

    unsigned char *pixels = malloc(width * height * sizeof(unsigned char));

    for (int i = 0; i < width * height; i++) {
        pixels[i] = data[i * 4]; // red channel
    }

    //printf("First pixel: R=%u G=%u B=%u A=%u\n", pixels[0], pixels[0], pixels[0], pixels[0]);
    
    //print the number of pixels
    int count = 0;

        for (int i = 0; i < pixel_count; i++) {
            if (pixels[i] != 0) {
                count++;
            }
        }
    
    //printf("Nonzero red pixels: %d\n", count);

    printf("first pixel: %u\n", pixels[0]);

    uint8_t **res = malloc(width * sizeof(uint8_t *));
    for (int i = 0; i < width; i++) {
        res[i] = malloc(height * sizeof(uint8_t));
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            res[x][y] = pixels[y * width + x];
        }
    }

    return res;
}


