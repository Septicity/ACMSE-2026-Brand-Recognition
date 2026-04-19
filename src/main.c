#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define GIF_IMPL
#include "gifenc.h"

#include "palette.c"

#include "get_pixels.h"
#include "datatypes.c"
#include "floodFill.c"

static void print_usage(const char* program) {
	
    printf("Usage: %s [options]\n", program);
    printf("Options:\n");
	
    printf("  -i <file>           Input file path\n");
    printf("  -o <file>           Output file name\n");
	
    printf("  -g                  Enable GIF output\n");
	printf("  -d                  Change Delta Threshold (default 15)\n");
    printf("  -h, --help          Show this help\n");
	
}

int main(int argc, char** argv) {
	
	char filename[65] = {0};
	char outputName[65] = {0};
	
	bool produceGif = false;
	
	int deltas = 15;
	
	// If invoked without suppling anything
	if(argc < 2) {
		print_usage(argv[0]);
		return 1;
	}
	
	
	for (int i = 1; i < argc; i++) {

		if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			print_usage(argv[0]);
			return 0;
		}

		else if(strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
			strncpy(filename, argv[i + 1], 64);
			filename[64] = '\0';
			i++;
		}

		else if(strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			strncpy(outputName, argv[i + 1], 64);
			outputName[64] = '\0';
			i++;
		}

		else if(strcmp(argv[i], "-g") == 0) {
			produceGif = true;
		}

		else if(strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
			deltas = atoi(argv[i + 1]);
			i++;
		}

		else {
			fprintf(stderr, "Unknown option: %s\n", argv[i]);
			return 1;
		}
		
	}

	// Check the input
	if(strlen(filename) == 0) {
		
		fprintf(stderr, "Error: empty filename\n");
		return 1;
		
	}
	if(strlen(outputName) == 0) {
		
		fprintf(stderr, "Error: missing output filename\n");
		return 1;
		
	}

	// Try opening to validate it
	FILE *f = fopen(filename, "rb");
	if(!f) {
		perror("This file doesn't seem valid");
		return 1;
	}
	fclose(f);
	

	printf("Opened file: %s\n", filename);
	
	int height, width;
	
	uint8_t** pixelMatrix = get_pixels(filename, &width, &height);
	
	printf("The loaded images dimensions are: %d, %d\n", width, height);
	
	printf("Loaded the image into the pixel matrix\n");
	
	uint16_t** segmentMap = malloc(height * sizeof(uint16_t *));
	if(!segmentMap) {
		return ERROR;
		
	}
	for(int y = 0; y < height; y++) {
		
		segmentMap[y] = calloc(width, sizeof(uint16_t)); // Zero out segments
		
		if(!segmentMap[y]) {
			
			// cleanup if we fail
			for (int i = 0; i < y; i++) free(segmentMap[i]);
			free(segmentMap);
			return ERROR;
			
		}
		
	}
	
	printf("Created the segment matrix\n");
	
	// Create the gif struct instance
	const char* gifFilename = "output.gif";
	
	ge_GIF *gif = NULL;
	
	if(produceGif) {
		
		// The numeric arguments are palette depth (log2(number of colors)), transparency seeting, and loop setting;
		gif = ge_new_gif(gifFilename, width, height, colors, 8, -1, 0);
		
		if(!gif) {
			fprintf(stderr, "Failed to create GIF\n");
			return ERROR;
		}
		
	}
	
	int pixelsTraversed = 1;
	
	while(countZeros(segmentMap, height, width) != 0) {
		floodfill(pixelMatrix, segmentMap, &pixelsTraversed, height, width, deltas);
		if(produceGif) saveGifFrame(gif, segmentMap, width, height);
	}
	
	save_pixels(outputName, segmentMap, width, height);
	
	
	if(gif) {
		ge_close_gif(gif);
	}
	
	return SUCCESS;
	
}	