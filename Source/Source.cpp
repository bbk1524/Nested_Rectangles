#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>

int main (int argc, char** argv)
{
	//init libraries at the top level so I can avoid having to init systems in an order
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	IMG_Init(IMG_INIT_PNG);

	Game game;
	game.init();
	game.run();
	game.destroy();

	//stop libraries
	IMG_Quit();
	SDL_Quit();

	return 0;
}
