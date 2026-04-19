#include <stdlib.h>
#include <stdint.h>

#include "gifenc.c"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "get_pixels.h"

uint8_t** get_pixels(const char* filename, int* Width, int* Height) {
	
	int width, height, channels;
	
	// Grab data from STB
	uint8_t* data = stbi_load(filename, &width, &height, &channels, 4);
	if(!data) return NULL;
	
	// Allocate matrix
	uint8_t** res = malloc(height * sizeof(uint8_t*));
	if(!res) {
		
		stbi_image_free(data);
		return NULL;
		
	}
	for(int x = 0; x < height; x++) {
		
		res[x] = malloc(width * sizeof(uint8_t));
		
		if(!res[x]) {
			
			// cleanup if we fail
			for (int i = 0; i < x; i++) free(res[i]);
			free(res);
			stbi_image_free(data);
			return NULL;
			
		}
		
	}

	// Grab the red channel from the RGBA buffer
	for(int y = 0; y < height; y++) {
		
		for(int x = 0; x < width; x++) {
			
			res[y][x] = data[(y * width + x) * 4]; // red channel
			
		}
		
	}

	stbi_image_free(data);
	
	// Write to the height/width values if we supply an argument
	if (Width) *Width = width;
	if (Height) *Height = height;

	return res;
}

int save_pixels(const char* filename, uint16_t** pixels, int width, int height) {

	// Make buffer
	uint8_t* data = malloc(width * height * 4);
	if (!data) return 0;

	// Fill buffer
	for (int y = 0; y < height; y++) {
		
		for (int x = 0; x < width; x++) {

			uint16_t val = pixels[y][x];

			int idx = (y * width + x) * 4;
			
			//if((int)val * 20 > 255) printf("Overflow Detected at: %d %d\n", y, x);
			srand(pixels[y][x]);
			data[idx + 0] = (uint8_t)((rand() * 10) % 255); // R
			data[idx + 1] = (uint8_t)((rand() * 20) % 255); // G
			data[idx + 2] = (uint8_t)((rand() * 30) % 255); // B
			data[idx + 3] = 255; // A
		}
		
	}

	// Write PNG (stride = width * 4)
	int success = stbi_write_png(filename, width, height, 4, data, width * 4);

	free(data);
	return success;
	
}

int saveGif(const char* filename, uint16_t** segmentMap, int width, int height) {
    int i, j;

    ge_GIF *gif = ge_new_gif(
        filename,
        width, height,
        (uint8_t []) {  // palette
           // All segments must be a fully saturated color.
            // As such, we can use a 256-color rainbow as the palette, enumerated
            // by hue.
            0xFF, 0x00, 0x00, /* 0 -> black */
            0xFF, 0x00, 0x00, /* 1 -> red */
            0x00, 0xFF, 0x00, /* 2 -> green */
            0x00, 0x00, 0xFF, /* 3 -> blue */
        },
        2,              /* palette depth == log2(# of colors) */
        -1,             /* no transparency */
        0               /* infinite loop */
    );
    /* draw some frames */
    for (i = 0; i < 4*6/3; i++) {
        for (j = 0; j < width*height; j++)
            gif->frame[j] = (i*3 + j) / 6 % 4;
        ge_add_frame(gif, 10);
    }
    /* remember to close the GIF */
    ge_close_gif(gif);
    return 0;
}

int countZeros(uint16_t** segmentMap, int height, int width) {
	
	int zeroCount = 0;
	
	for(int y = 0; y < height; y++) {
		
		for(int x = 0; x < width; x++) {
			
			zeroCount = (segmentMap[y][x] == 0) ? (zeroCount + 1) : zeroCount;
			
		}
		
	}
	
	return zeroCount;

}