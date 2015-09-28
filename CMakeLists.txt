cmake_minimum_required(VERSION 3.1)

# Solution name
project(Bens-Game-Solution)

# Supposed to help YCM for vim completion
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# Add stuff
add_subdirectory(lib EXCLUDE_FROM_ALL)

add_subdirectory(assets)

# Add config
add_subdirectory(config)

# Add Project Folder
add_subdirectory(src)
