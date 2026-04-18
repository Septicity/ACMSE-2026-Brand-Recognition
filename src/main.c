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
	
	

	
	freeStack(&pointStack);
	
	return 0;
	
}	