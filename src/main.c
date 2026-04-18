#include <stdio.h>
#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "stb_image.h"
#include "get_pixels.h"
#include "datatypes.c"
#include "floodFill.c"

Stack pointStack;
initStack(&pointStack, DEFAULT_STACK_ALLOCATION);

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
	
	uint8_t** pixelMatrix = get_pixels(filename, &height, &width);
	
	uint8_t** segmentMap = malloc(width * sizeof(uint8_t *));
	if(!segmentMap) {
		return ERROR;
		
	}
	for(int x = 0; x < width; x++) {
		
		segmentMap[x] = calloc(height, sizeof(uint8_t));
		
		if(!segmentMap[x]) {
			
			// cleanup if we fail
			for (int i = 0; i < x; i++) free(segmentMap[i]);
			free(segmentMap);
			return ERROR;
			
		}
		
	}

	
	freeStack(&pointStack);
	
	return SUCCESS;
	
}	