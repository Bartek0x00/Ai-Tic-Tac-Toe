#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "display.h"

void delete_display(void)
{
	SDL_DestroyTexture(display.circle);
	SDL_DestroyTexture(display.cross);
	SDL_DestroyTexture(display.background);
	SDL_DestroyRenderer(display.renderer);
	SDL_DestroyWindow(display.window);
	TTF_CloseFont(display.font);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
