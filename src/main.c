#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "get_pixels.h"
#include "datatypes.c"
#include "floodFill.c"

int main(int argc, char** argv) {
	
	// If invoked without suppling anything
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	
	// Grab the file name from command line
	const char* filename = argv[1];

	// Check the input
	if (strlen(filename) == 0) {
		fprintf(stderr, "Error: empty filename\n");
		return 1;
	}

	// Try opening to validate it
	FILE *f = fopen(filename, "rb");
	if (!f) {
		perror("This file doesn't seem valid");
		return 1;
	}
	fclose(f);
	

	printf("Opened file: %s\n", filename);
	
	int height, width;
	
	uint8_t** pixelMatrix = get_pixels(filename, &width, &height);
	
	printf("The loaded images dimensions are: %d, %d\n", width, height);
	
	printf("Loaded the image into the pixel matrix\n");
	
	uint8_t** segmentMap = malloc(height * sizeof(uint8_t *));
	if(!segmentMap) {
		return ERROR;
		
	}
	for(int y = 0; y < height; y++) {
		
		segmentMap[y] = calloc(width, sizeof(uint8_t));
		
		if(!segmentMap[y]) {
			
			// cleanup if we fail
			for (int i = 0; i < y; i++) free(segmentMap[i]);
			free(segmentMap);
			return ERROR;
			
		}
		
	}
	
	printf("Created the segment matrix\n");
	
	floodfill(pixelMatrix, segmentMap, height, width);
	
	return SUCCESS;
	
}	