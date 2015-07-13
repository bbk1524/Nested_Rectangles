#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

#include "Definitions.h"
#include <map>
#include <SDL.h>

class Input_System {
public:
	Input_System()
	{
		mouse_x = 0;
		mouse_y = 0;
	}
	~Input_System() = default;

	bool init()
	{
		//keys
		current_events[game_event::LEFT] = false;
		current_events[game_event::RIGHT] = false;
		current_events[game_event::UP] = false;
		current_events[game_event::DOWN] = false;
		current_events[game_event::ALT_LEFT] = false;
		current_events[game_event::ALT_RIGHT] = false;
		current_events[game_event::ALT_UP] = false;
		current_events[game_event::ALT_DOWN] = false;
		current_events[game_event::ACTION_ONE] = false;
		current_events[game_event::ACTION_TWO] = false;
		//mouse
		current_events[game_event::LEFT_MOUSE_DOWN] = false;
		current_events[game_event::RIGHT_MOUSE_DOWN] = false;
		//quit
		current_events[game_event::QUIT] = false;
		return true;
	}

	void update()
	{

		if (SDL_PollEvent(&event))
		{
			//handle the quit
			if (event.type == SDL_QUIT)
			{
				current_events[game_event::QUIT] = true;
			}

			//handle keys
			if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
			{

				//set is_dwon to whether the key is being pressed
				bool is_down = event.type == SDL_KEYDOWN;

				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					current_events[game_event::LEFT] = is_down;
					break;

				case SDLK_RIGHT:
					current_events[game_event::RIGHT] = is_down;
					break;

				case SDLK_UP:
					current_events[game_event::UP] = is_down;
					break;

				case SDLK_DOWN:
					current_events[game_event::DOWN] = is_down;
					break;

				//TODO: finish the buttons

				}
			}


			//handle mouse buttons
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			{
				bool is_down = event.type == SDL_MOUSEBUTTONDOWN;

				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					current_events[game_event::LEFT_MOUSE_DOWN] = is_down;
					break;
				case SDL_BUTTON_RIGHT:
					current_events[game_event::RIGHT_MOUSE_DOWN] = is_down;
					break;
				}

			}

			//handle mouse motion
			if (event.type == SDL_MOUSEMOTION)
			{
				this->mouse_x = event.motion.x;
				this->mouse_y = event.motion.y;
			}

		}
	}

	bool get_event(game_event event_type)
	{
		return current_events[event_type];
	}

	int get_mouse_x()
	{
		return mouse_x;
	}

	int get_mouse_y()
	{
		return mouse_y;
	}

private:
	std::map<game_event, bool> current_events;
	SDL_Event event;
	int mouse_x;
	int mouse_y;
};

#endif