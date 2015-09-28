#include "Definitions.h"

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