#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "Logger.h"

#include <SDL.h>
#include <string>

std::string get_base_path()
{
	char * base_path_tmp = SDL_GetBasePath();
	if (base_path_tmp)
	{
		std::string base_path(base_path_tmp);
		SDL_free(base_path_tmp);
		return base_path;
	}
	else
	{
		std::string base_path("base path undetermined");
		return base_path;
	}
}

const std::string base_path = get_base_path();

//Global logger. Not thread safe :)
Logger logger;

//You can format arguments using printf notations: EX: LOG_ERROR("problem with file %s", filename);
//See http://c.learncodethehardway.org/book/ex20.html for more detail
// Formatted strings must be char* (call std::string::c_str() on std::string)
// #define LOG_ERROR(M, ...) fprintf(stderr, "[ERROR] (%s : %s : %d: ) " M "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

//global variables yay!

const int G_WINDOW_WIDTH = 800; //TODO: change this to read from an ini file. Maybe make it a field of Screen?
const int G_WINDOW_HEIGHT = 600;

enum class game_event
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ALT_LEFT,
	ALT_RIGHT,
	ALT_UP,
	ALT_DOWN,
	ACTION_ONE,
	ACTION_TWO,
	LEFT_MOUSE_DOWN,
	RIGHT_MOUSE_DOWN,
	QUIT
};

#endif
