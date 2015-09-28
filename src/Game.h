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

	Game()
		: screen(base_path + "config/layout.xml")
	{
		const std::string layout_path = base_path + "config/layout.xml";
		input_system.init();
		const std::string image_path = base_path + "assets/images/hello.bmp";
		image.init(screen.graphics_system.get_renderer(), image_path, *screen.get_box_by_name("Game"));
		if (!(screen.is_valid() && image.is_valid() && input_system.is_valid()))
		{
			valid = false;
		}
	}
	~Game() = default;

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

	bool is_valid() const
	{
		return valid;
	}

private:
	bool quit{ false };
	bool valid{ true };
	Screen screen;
	Input_System input_system;
};

#endif 
