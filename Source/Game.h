#ifndef GAME_H
#define GAME_H

//#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "Screen.h"
#include "Definitions.h"

#include "SDL.h"

class Game {
public:
	Game() = default;
	~Game() = default;

	bool init()
	{
		quit = false;

		const char* layout_file = "./Config/layout.xml";
		screen.init(layout_file);
		input_system.init();

		//put image on screen in a box;

		// std::string image_path = "./Assets/Images/hello.bmp";
		// SDL_Surface * bmp = SDL_LoadBMP(image_path.c_str());
		// tex = SDL_CreateTextureFromSurface(screen.graphics_system.get_renderer(), bmp);
		// SDL_RenderClear(screen.graphics_system.get_renderer());
		// Box * b;
		// b = (screen.get_box_by_name("Game")); 
		// std::cout << *b; //this is where it's failing ^ ^ 
		// SDL_Rect scale;
		// scale.x = b->x1;
		// scale.y = b->y1;
		// scale.w = b->x2 - b->x1;
		// scale.h = b->y2 - b->y1;

		// //scale.x = 0;
		// //scale.y = 0;
		// //scale.w = 100;
		// //scale.h = 100;
		// SDL_RenderCopy(screen.graphics_system.get_renderer(), tex, NULL, &scale);
		// SDL_RenderPresent(screen.graphics_system.get_renderer());
		// SDL_Delay(2000);
		return true;
	}

	bool destroy()
	{
		screen.destroy();
		return true;
	}

	//gimme } frame
	void update()
	{
		input_system.update();
		if (input_system.get_event(game_event::QUIT))
		{
			quit = true;
		}

		//TODO: get rid of this

		// Box b;
		// b = *(screen.get_box_by_name("Game"));

		// SDL_Rect scale;
		// /*scale.x = b.x1;
		// scale.y = b.y1;
		// scale.w = b.x2 - b.x1;
		// scale.h = b.y2 - b.y1;*/
		// scale.x = 0;
		// scale.y = 0;
		// scale.w = 100;
		// scale.h = 100;

		// SDL_RenderCopy(screen.graphics_system.get_renderer(), tex, NULL, &scale);

		screen.draw();
	}

	//gimme all da frames
	void run()
	{
		while (!quit)
		{
			update();
		}
	}

private:
	bool quit;
	Screen screen;
	Input_System input_system;
	// SDL_Texture * tex; //TODO: get rid of this;
};

#endif 
