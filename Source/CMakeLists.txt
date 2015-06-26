# Name the Project and give files
set(GAME_NAME Nested_Rectangles)

# I could use this to get all files, but then it wouldn't include headers in the file tree
# or automatically find new files
# file(GLOB CPP_HEADER_SOURCES
	# "*.cpp"
	# ".h"
# )

add_executable(${GAME_NAME}
	NestedRectangles.cpp
)

# Includes..
include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
#	${SDL2_MIXER_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
#	${Box2D_SOURCE_DIR}
	${tinyxml_SOURCE_DIR}
	${SDL2_gfx_SOURCE_DIR}
)

# What it should link against
target_link_libraries(${GAME_NAME}
	${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
#	${SDL2_MIXER_LIBRARY}
	${SDL2_TTF_LIBRARY}
#	Box2D
	tinyxml
	SDL2_gfx
)

# Compile for C++ 11. CMake doesn't know that VS does this by default and whines
if(NOT MSVC)
	set_property(TARGET ${GAME_NAME} PROPERTY CXX_STANDARD 11)
	set_property(TARGET ${GAME_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
endif()

# Tell VS where to build the executable for both debug and release versions
set_target_properties(${GAME_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Game")
set_target_properties(${GAME_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Game")
set_target_properties(${GAME_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Game")

# Not needed now
#ADD_CUSTOM_COMMAND(TARGET ${GAME_NAME} POST_BUILD
#	COMMAND
#	
#	# Copy Assets where both VS can find them (it doesn't look in the Game folder) and the Game folder
#	file(COPY "${CMAKE_SOURCE_DIR}/Assets" DESTINATION ${PROJECT_BINARY_DIR}/Source)
#	file(COPY "${CMAKE_SOURCE_DIR}/Assets" DESTINATION ${CMAKE_SOURCE_DIR}/Game)
#
#	# Copy Config where both VS can find them (it doesn't look in the Game folder) and the Game folder
#	file(COPY "${CMAKE_SOURCE_DIR}/Config" DESTINATION ${PROJECT_BINARY_DIR}/Source)
#	file(COPY "${CMAKE_SOURCE_DIR}/Config" DESTINATION ${CMAKE_SOURCE_DIR}/Game)
#)


# These copies need to be run every time the game is compiled in case something changed
# I'm also copying them to where VS can find them
ADD_CUSTOM_COMMAND(TARGET ${GAME_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Config ${PROJECT_BINARY_DIR}/Source/Config/
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Config ${CMAKE_SOURCE_DIR}/Game/Config/
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets ${PROJECT_BINARY_DIR}/Source/Assets/
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets ${CMAKE_SOURCE_DIR}/Game/Assets/
)

if(MSVC)
	# Find and copy 32-bit DLLs to Game folder
	file(GLOB X86_DLL_FILES
			${SDL2_WIN}/lib/x86/*.dll
			${SDL2_IMAGE_WIN}/lib/x86/*.dll
#			${SDL2_MIXER_WIN}/lib/x86/*.dll
			${SDL2_TTF_WIN}/lib/x86/*.dll
	)
	
	# Important to note that this happens at the cmake step, not the games compilation.
	# If these are removed, re-run cmake to get them back.
	file(COPY ${X86_DLL_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/Game)
endif()
