#include "Game.h"
#include "Logger.h"
#include <SDL.h>
#include <SDL_image.h>

//undef main for VS2015 so SDL_main won't be called
//TODO: check if this actually hurts anything...
#if (_MSC_VER == 1900)
# undef main
#endif

int main (int argc, char** argv)
{
	//init libraries at the top level to avoid game system dependencies and because I'm using SDL_main anyway
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	IMG_Init(IMG_INIT_PNG);

	Game game;
	game.run();
	game.destroy();

	//stop libraries
	IMG_Quit();
	SDL_Quit();

	return 0;
}
