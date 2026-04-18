#include <stdlib.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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


