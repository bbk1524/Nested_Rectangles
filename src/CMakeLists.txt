# Name the Project and give files
project(Bens-Game)

# Usage: create_unmade <file1>...
# creates files if they don't exist. Starts looking in the directory of the CMakeLists.txt file it's called in
function(create_unmade)
	foreach(word ${ARGV}) # ${ARGV} expands to all arguments
		if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${word})
			message("---- creating: ${word} ----")
			file(WRITE ${word} "")
		endif()
	endforeach()
endfunction()

set(Add_Me_To_Exe "")

# Usage: make_group <name> <file1>...
# creates a files, puts them in a source group, and adds them to the exe list
function(make_group name)
	create_unmade(${ARGN}) # ARGN expands to all unexpected arguments. In our case, everything after the first arg, name
	#append _Files to the name
	source_group(${name}_Files FILES ${ARGN})
	# ${Add_Me_To_Exe} will be linked soon :)
	set(Add_Me_To_Exe ${Add_Me_To_Exe} ${ARGN} PARENT_SCOPE)
endfunction()

make_group(Misc
	Source.cpp
	Game.h
	Game.cpp
	Definitions.h
	InputSystem.h
	InputSystem.cpp
	Logger.h
	Logger.cpp
)

make_group(Graphics
	Box.h
	Box.cpp
	GraphicsSystem.h
	GraphicsSystem.cpp
	Screen.h
	Screen.cpp
	Texture.h
	Texture.cpp
)

make_group(Components
	Component.cpp
	Component.h
	Entity.cpp
	Entity.h
)

add_executable(${PROJECT_NAME}
	${Add_Me_To_Exe}
)

# Includes..
include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2_MIXER_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
	# ${Box2D_SOURCE_DIR}
	${tinyxml_SOURCE_DIR}
	${SDL2_gfx_SOURCE_DIR}
	${tinyxml2_SOURCE_DIR}
)

# What it should link against
target_link_libraries(${PROJECT_NAME}
	${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_MIXER_LIBRARY}
	${SDL2_TTF_LIBRARY}
	# Box2D
	tinyxml
	SDL2_gfx
	tinyxml2
)
# add warnings to all projects
if(MSVC)
	# compile with high warnings, but omit the ones about unused parameters and declarations hiding class members
	target_compile_options(${PROJECT_NAME} PUBLIC /W4 /wd4100 /wd4458)
else(MSVC)
	if(APPLE)
		set(CSTD -std=c++1y)
	else()
		set(CSTD -std=c++14)
	endif(APPLE)

	target_compile_options(${PROJECT_NAME} PUBLIC ${CSTD} -Wall -Wextra -pedantic -Wno-unused-parameter)
endif(MSVC)

# Tell VS where to build the executable for both debug and release versions
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")

# These copies need to be run every time the game is compiled in case something changed
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/config ${CMAKE_SOURCE_DIR}/bin/config/
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_SOURCE_DIR}/bin/assets/
)

