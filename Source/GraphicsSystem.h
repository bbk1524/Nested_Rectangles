#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

#include <SDL.h>
#include <string>
#include <SDL_image.h>

//This class just gives me a window.That's all it does. I need a screen class to draw my boxes

class Graphics_System {
public:
	Graphics_System()
	{
		window = nullptr;
		renderer = nullptr;
	}

	~Graphics_System() = default;


	//TODO: make this actually check for errors
	bool init(std::string window_name, int window_width, int window_height)
	{

		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

		IMG_Init(IMG_INIT_PNG);

		window = SDL_CreateWindow(
			window_name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			window_width,
			window_height,
			SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
		return true;
	}

	//I'm assuming that this is the last system to end;
	bool destroy()
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void begin() 
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	}

	void draw() 
	{
		//my boxes will all draw themselves. I'm going to put the draw method in Screen instead.
	}

	void present() 
	{
		SDL_RenderPresent(renderer);
	}

	SDL_Renderer * get_renderer() {
		return renderer;
	}
	SDL_Window* get_window() {
		return window;
	}

private:
	SDL_Renderer* renderer;
	SDL_Window* window;
};

#endif 