#ifndef GAME_H
#define GAME_H

//#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "Screen.h"
#include "Definitions.h"
#include "Texture.h"

class Game {
public:

	//TODO: rm
	Texture image;

	Game() = default;
	~Game() = default;

	bool init()
	{
		quit = false;

		const char* layout_file = "./Config/layout.xml";
		screen.init(layout_file);
		input_system.init();
		
		image.init(screen.graphics_system.get_renderer(), "./Assets/Images/hello.bmp", *screen.get_box_by_name("Inner Left"));

		return true;
	}

	bool destroy()
	{
		screen.destroy();

		return true;
	}

	//gimme a frame
	void update()
	{
		input_system.update();
		if (input_system.get_event(game_event::QUIT))
		{
			quit = true;
		}

		draw();
	}

	void draw()
	{
		screen.graphics_system.begin();

		screen.draw_boxes();

		image.draw();

		screen.graphics_system.present();
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
};

#endif 
