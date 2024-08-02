#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "display.h"
#include "../AI/color.h"

void terminate(int stage);

void show_text(char *text, Color color)
{
	SDL_Color text_color = {0, 0, 0, 255};

	if (color == NONE) {
		text_color.r = 227;
		text_color.g = 227;
		text_color.b = 227;
	}

	if (color == RED)
		text_color.r = 255;

	if (color == BLUE)
		text_color.b = 255;
	
	SDL_Surface *text_surface = TTF_RenderText_Blended(
		display.font, 
		text,
		text_color
	);
	if (!text_surface) {
		SDL_Log(
			"Failed to create textSurface: %s\n",
			TTF_GetError()	
		);
		terminate(4);
		exit(-1);
	}

	SDL_Texture *text_texture = SDL_CreateTextureFromSurface(
		display.renderer,
		text_surface
	);
	if (!text_texture) {
		SDL_Log(
			"Failed to create textTexture: %s\n",
			SDL_GetError()
		);
		SDL_FreeSurface(text_surface);
		terminate(4);
		exit(-1);
	}
	
	SDL_Rect text_rect = {0, 600, 600, 50};

	SDL_SetRenderDrawColor(display.renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(display.renderer, &text_rect);

	text_rect.w = (strlen(text) * 16);
	text_rect.x = 300 - (text_rect.w / 2);
	SDL_RenderCopy(display.renderer, text_texture, NULL, &text_rect);
	//SDL_RenderPresent(display.renderer);
	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(text_texture);
}
