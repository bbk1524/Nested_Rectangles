#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//You can format arguments using printf notations: EX: LOG_ERROR("problem with file %s", filename);
//See http://c.learncodethehardway.org/book/ex20.html for more detail
// Formatted strings must be char* (call std::string::c_str() on std::string)
#define LOG_ERROR(M, ...) fprintf(stderr, "[ERROR] (%s : %s : %d: ) " M "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

//global variables yay!

const int G_WINDOW_WIDTH = 800;
const int G_WINDOW_HEIGHT = 600;

enum class game_event
{
	QUIT
};

#endif
