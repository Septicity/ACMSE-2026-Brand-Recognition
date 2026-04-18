#include "get_pixels.h"


uint8_t **get_pixels(const char *filename) { //returns a 2d array of pixels
    int width, height, channels;

    uint8_t *data = stbi_load(filename, &width, &height, &channels, 4);
    uint8_t *pixels = malloc(width * height * sizeof(uint8_t));

    for (int i = 0; i < width * height; i++) {
        pixels[i] = data[i * 4]; //get the red channel of each pixel
    }


    uint8_t **res = malloc(width * sizeof(uint8_t *));
    for (int i = 0; i < width; i++) {
        res[i] = malloc(height * sizeof(uint8_t));
    }

    for (int x = 0; x < width; x++) { //convert to 2d array
        for (int y = 0; y < height; y++) {
            res[x][y] = pixels[y * width + x];
        }
    }

    return res;
}


