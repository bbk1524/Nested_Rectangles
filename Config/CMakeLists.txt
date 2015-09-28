project(config)

add_custom_target(config
	SOURCES
	layout.xml
	Notes.md
)

# If a file in Config or Assets is changed, re-build this project to copy them to the right places
# This doesn't seem to work from VS. Instead, recompile the game to copy this stuff.
ADD_CUSTOM_COMMAND(TARGET config PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Config ${PROJECT_BINARY_DIR}/Source/Config/
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Config ${CMAKE_SOURCE_DIR}/Game/Config/
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets ${PROJECT_BINARY_DIR}/Source/Assets/
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets ${CMAKE_SOURCE_DIR}/Game/Assets/
)