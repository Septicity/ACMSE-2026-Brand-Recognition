typedef struct {
	uint32_t x, y;
} Point_t;

typedef struct {
	Point_t *data;
	size_t top;
	size_t capacity;
} Stack;

#define DEFAULT_STACK_ALLOCATION 154401 // The width * height of each image
#define DESCRIMINATION_THRESHOLD 15

#define ERROR -1
#define FAILURE 1
#define SUCCESS 0

/*
	The following is a stack implimentation which will be used to store traversal candidates for our floodfill
	Each operation is O(1) amortized time complexity

*/


// Create the stack
int initStack(Stack *s, size_t capacity) {
	
	s->data = (Point_t *)malloc(sizeof(Point_t) * capacity);
	if(!s->data) return 0;

	s->top = 0;
	s->capacity = capacity;
	
	return 1;
}

// Push
int push(Stack *s, Point_t p) {
	
	if (s->top >= s->capacity) {
		
		// This allows us to resize incase we find we need more space
		size_t newCap = s->capacity * 2;
		Point_t *newData = realloc(s->data, sizeof(Point_t) * newCap);
		if (!newData) return 0;
		
		// The new size/value of the stack
		s->data = newData;
		s->capacity = newCap; 
		
	}

	s->data[s->top++] = p;
	return 1;
	
}

// Pop a point from the stack
int pop(Stack *s, Point_t *out) {
	
	if(s->top == 0) return 0;

	*out = s->data[--s->top];
	
	return 1;
	
}

// Peek a value (will likely be unused for this project)
int peek(Stack *s, Point_t *out) {
	
	if(s->top == 0) return 0;

	*out = s->data[s->top - 1];
	
	return 1;
	
}

//  Free the stack
void freeStack(Stack *s) {
	
	free(s->data);
	s->data = NULL;
	s->top = 0;
	s->capacity = 0;
	
}