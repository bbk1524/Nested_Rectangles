# Use with:
# include_directories(${tinyxml_SOURCE_DIR})
# and, to include the library in your solution:
# target_link_libraries(tinyxml) #no ${}
project(tinyxml)

include_directories(./tinyxml)

add_library(tinyxml STATIC
	tinyxml/tinystr.h
	tinyxml/tinyxml.h
	tinyxml/tinystr.cpp
	tinyxml/tinyxml.cpp
	tinyxml/tinyxmlerror.cpp
	tinyxml/tinyxmlparser.cpp
)

# define TIXML_USE_STL in this target
target_compile_definitions(tinyxml PUBLIC TIXML_USE_STL)