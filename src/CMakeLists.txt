# Name the Project and give files
# set(GAME_NAME Nested_Rectangles)

project(Game_Name)

add_executable(${PROJECT_NAME}
	Source.cpp
	Box.h
	Box.cpp
	Game.h
	Game.cpp
	GraphicsSystem.h
	GraphicsSystem.cpp
	Definitions.h
	Screen.h
	Screen.cpp
	InputSystem.h
	InputSystem.cpp
	Texture.h
	Texture.cpp
)

# Includes..
include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2_MIXER_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
#	${Box2D_SOURCE_DIR}
	${tinyxml_SOURCE_DIR}
	${SDL2_gfx_SOURCE_DIR}
)

# What it should link against
target_link_libraries(${PROJECT_NAME}
	${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_MIXER_LIBRARY}
	${SDL2_TTF_LIBRARY}
#	Box2D
	tinyxml
	SDL2_gfx
)
# add warnings to all projects
if(MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /W4 /wd4100)
else(MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC -std=c++1y -Wall -Wextra -pedantic -Wno-unused-parameter)
endif(MSVC)

# Tell VS where to build the executable for both debug and release versions
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")

# These copies need to be run every time the game is compiled in case something changed
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Config ${CMAKE_SOURCE_DIR}/bin/Config/
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_SOURCE_DIR}/bin/assets/
)

if(MSVC)
	# Find and copy 32-bit DLLs to Game folder
	file(GLOB X86_DLL_FILES
			${SDL2_WIN}/lib/x86/*.dll
			${SDL2_IMAGE_WIN}/lib/x86/*.dll
			${SDL2_MIXER_WIN}/lib/x86/*.dll
			${SDL2_TTF_WIN}/lib/x86/*.dll
	)
	
	# Important to note that this happens at the cmake step, not the games compilation.
	# If you remove these, re-run cmake to get them back.
	file(COPY ${X86_DLL_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/bin)
endif()
