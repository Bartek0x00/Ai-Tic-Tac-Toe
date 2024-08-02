#ifndef _AI_COLOR
#define _AI_COLOR

typedef enum {
	NONE = 0b00,
	RED = 0b01,
	BLUE = 0b10
} Color;

#define COLOR_SWAP(color) ((color) ^ 0b11)

#endif //_AI_COLOR
