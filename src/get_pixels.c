#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "gifenc.h"

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

int findClosestColor(uint8_t r, uint8_t g, uint8_t b) {
	
	int bestIndex = 0;
	int bestDist = INT_MAX;

	for (int i = 0; i < PALETTE_SIZE; i++) {
		
		int pr = colors[i * 3 + 0];
		int pg = colors[i * 3 + 1];
		int pb = colors[i * 3 + 2];

		int dr = r - pr;
		int dg = g - pg;
		int db = b - pb;

		int dist = dr * dr + dg * dg + db * db; // euclidean distance

		if (dist < bestDist) {
			
			bestDist = dist;
			bestIndex = i;
			
		}
		
	}

	return bestIndex;
	
}

int saveGifFrame(ge_GIF* gif, uint16_t** segmentMap, int width, int height) {
	
	/*
		All segments must be a fully saturated color.
		As such, we can use a 256-color rainbow as the palette, enumerated
		by hue.
	*/
	
    /* draw some frames */
	
	for (int y = 0; y < height; y++) {
		
		for (int x = 0; x < width; x++) {
			
			//if((int)val * 20 > 255) printf("Overflow Detected at: %d %d\n", y, x);
			srand(segmentMap[y][x]);
			
			float r = (float)((rand() * 10) % 255); // R
			float g = (float)((rand() * 20) % 255); // G
			float b = (float)((rand() * 30) % 255); // B
			
			gif->frame[(y * width) + x] = findClosestColor(r, g, b);
			
		}
		
	}
	
	ge_add_frame(gif, 10);
	
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