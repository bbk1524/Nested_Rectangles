#include "Game.h"
#include <SDL.h>

int main (int argc, char** argv)
{

	Game game;
	game.init();
	game.run();
	game.destroy();

	return 0;
}
