#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

#include "Definitions.h"
#include <map>
#include <SDL.h>

class Input_System {
public:
	Input_System() = default;
	~Input_System() = default;

	bool init()
	{
		current_events[game_event::QUIT] = false;
		return true;
	}

	void update()
	{

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				current_events[game_event::QUIT] = true;
			}
		}
	}

	bool get_event(game_event event_type) 
	{
		return current_events[event_type];
	}

private:
	std::map<game_event, bool> current_events;
	SDL_Event event;
};

#endif