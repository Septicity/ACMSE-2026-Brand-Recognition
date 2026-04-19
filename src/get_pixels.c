#include <stdlib.h>
#include <stdint.h>

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

			data[idx + 0] = (uint8_t)((val * 20) % 255); // R
			data[idx + 1] = (uint8_t)((val * 20) % 255); // G
			data[idx + 2] = (uint8_t)((val * 20) % 255); // B
			data[idx + 3] = 255; // A
		}
		
	}

	// Write PNG (stride = width * 4)
	int success = stbi_write_png(filename, width, height, 4, data, width * 4);

	free(data);
	return success;
	
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