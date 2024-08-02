#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "images.h"
#include "font.h"
#include "display.h"

void terminate(int stage)
{
	switch (stage) {
	case 4:
		SDL_DestroyRenderer(display.renderer);
	case 3:
		SDL_DestroyWindow(display.window);
	case 2:
		TTF_Quit();
	case 1:
		IMG_Quit();
	case 0:
		SDL_Quit();
	}
}

static SDL_Texture *load_texture(SDL_Window *window,
								SDL_Renderer *renderer, 
								void *mem, 
								const unsigned int len,
								const char *name)
{
	SDL_Surface *surface = IMG_Load_RW(
		SDL_RWFromMem(mem, len), 
		1
	);
	if (!surface) {
		SDL_Log(
			"Failed to load surface %s: %s", name, 
			SDL_GetError()
		);
		terminate(4);
		exit(-1);
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(
		renderer,
		surface
	);
	SDL_FreeSurface(surface);
	if(!texture) {
		SDL_Log(
			"Failed to load texture %s: %s", name,
			SDL_GetError()
		);
		terminate(4);
		exit(-1);
	}

	return texture;
}

void init_display(void)
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log(
			"Failed to init SDL: %s\n", 
			SDL_GetError()
		);
		exit(-1);
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		SDL_Log(
			"Failed to init IMG: %s\n",
			SDL_GetError()
		);
		terminate(0);
		exit(-1);
	}
	if (TTF_Init() == -1) {
		SDL_Log(
			"Failed to init TTF: %s\n",
			SDL_GetError()
		);
		terminate(1);
		exit(-1);
	}

	SDL_Window *window = SDL_CreateWindow(
		WINDOW_TITLE,
		WINDOW_POS_X,
		WINDOW_POS_Y,
		WINDOW_SIZE,
		WINDOW_SIZE + 50,
		SDL_WINDOW_SHOWN
	);
	if (!window) {
		SDL_Log(
			"Failed to create window: %s\n", 
			SDL_GetError()
		);
		terminate(2);
		exit(-1);
	}
	
	SDL_Renderer *renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	if (!renderer) {
		SDL_Log(
			"Failed to create renderer: %s\n", 
			SDL_GetError()
		);
		terminate(3);
		exit(-1);
	}
	
	SDL_Texture *background = load_texture(
		window,
		renderer,
		background_png,
		background_png_len,
		"background.png"
	);
	SDL_Texture *cross = load_texture(
		window,
		renderer,
		cross_png,
		cross_png_len,
		"cross.png"
	);
	SDL_Texture *circle = load_texture(
		window,
		renderer,
		circle_png,
		circle_png_len,
		"circle.png"
	);				

	SDL_RWops *rw = SDL_RWFromMem(font_ttf, font_ttf_len);
	if (!rw) {
		SDL_Log("Failed to make rw: %s\n", SDL_GetError());
		terminate(4);
		exit(-1);
	}
	TTF_Font *font = TTF_OpenFontRW(rw, 1, 64);
	if (!font) {
		SDL_Log("Failed to load font: %s\n", TTF_GetError());
		terminate(4);
		exit(-1);
	}

	display.window = window;
	display.renderer = renderer;
	display.background = background;
	display.circle = circle;
	display.cross = cross;
	display.font = font;
}
