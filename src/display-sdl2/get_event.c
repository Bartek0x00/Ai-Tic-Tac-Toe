#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "window.h"
#include "display.h"

static inline char get_square_clicked(int x, int y)
{
	int row = y / CELL_SIZE;
	int col = x / CELL_SIZE;
	return ((row * GRID_SIZE + col) + '0');
}

bool get_event(unsigned char *output)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT:
			*output = 'q';
			return true;
		
		case SDL_MOUSEBUTTONDOWN:
			*output = get_square_clicked(
				event.motion.x,
				event.motion.y
			);
			
			if (*output >= '0' && *output <= '8') 
				return true;	
		}
	}
	return false;
}
