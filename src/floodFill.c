void floodfill(uint8_t** pixelMatrix, uint16_t** segmentMap, int* pixelsTraversed, int height, int width, char* deltac) {
	
	static int iteration = 1;
	//static Point_t lastNonPoint = {-1, -1};

	int seedX, seedY;
	
	// find an unvisited seed
	while(1) {
			
		seedX = rand() % width;
		seedY = rand() % height;

		if (segmentMap[seedY][seedX] == 0) break;
		
	}
	

	Stack stack;
	if (!initStack(&stack, height * width)) return; // Start with some default value and then grow

	// push seed pixel
	push(&stack, (Point_t){seedX, seedY});
	
	/*
	lastNonPoint.x = -1;
	lastNonPoint.y = -1;
	*/
	
	Point_t p;
	
	int base = pixelMatrix[seedY][seedX];

	// while stack not empty
	while(pop(&stack, &p)) {
		
		// skip if we've already visited that pixel
		if (segmentMap[p.y][p.x] != 0) continue;

		segmentMap[p.y][p.x] = iteration;

		// The 4 neighbors each pixel has
		const int dx[4] = {1, -1, 0, 0};
		const int dy[4] = {0, 0, 1, -1};
		

		for(int i = 0; i < 4; i++) {
			
			// Neighbor pixel position
			int nx = p.x + dx[i];
			int ny = p.y + dy[i];

			// So that we don't try to read off the image
			if(nx < 0 || nx >= width || ny < 0 || ny >= height)
				continue;

			// Is that pixel already assigned?
			if(segmentMap[ny][nx] != 0)
				continue;
			
			//printf("Current Point: %d %d, Neighbor Point: %d %d\n", p.x, p.y, nx, ny);
			
			// Grab the neighbor color value 
			// Check if it passes our threshold
			uint8_t val = pixelMatrix[ny][nx];
			int delta = atoi(deltac);
			if((abs(base - val) <= delta) && segmentMap[ny][nx] == 0) {
				push(&stack, (Point_t){nx, ny});
				*pixelsTraversed += 1;
			} /*
			else {
				
				lastNonPoint.x = nx;
				lastNonPoint.y = ny;
				
			}
			*/
			
		}
		
	}
	
	printf("Flood Filled Segment %d\n", iteration);

	freeStack(&stack);
	iteration++;
	
}