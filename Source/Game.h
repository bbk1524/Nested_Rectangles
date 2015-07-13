#ifndef GAME_H
#define GAME_H

//#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "Screen.h"
#include "Definitions.h"


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

		//TODO: rm
		Box * tmp = screen.get_box_by_name("Game");
		std::cout << *tmp;
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
};

#endif 
