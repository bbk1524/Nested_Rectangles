# This doesn't work with VS2015 RC, but will with VS2013

cmake_minimum_required(VERSION 3.1)

# Solution name
project(Solution_Name)

# Find dynamic libraries
# include dynamic libraries with:
# include_directories(<target_name> ${<dynamic_library_name>_INCLUDE_DIR})
# link dynamic libraries with:
# target_link_libraries(<target_name> ${<dynamic_library_name>_INCLUDE_DIR})

#Set places to look for dynamic libraries
set(SDL2_WIN "${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.3")
set(SDL2_IMAGE_WIN "${CMAKE_SOURCE_DIR}/lib/SDL2_image-2.0.0")
set(SDL2_MIXER_WIN "${CMAKE_SOURCE_DIR}/lib/SDL2_mixer-2.0.0")
set(SDL2_TTF_WIN "${CMAKE_SOURCE_DIR}/lib/SDL2_ttf-2.0.12")

set(SDL2_INCLUDE_MAC "/usr/local/include/SDL2")
set(SDL_LIB_MAC "/usr/local/lib")

set(SDL2_INCLUDE_LINUX "/usr/include/SDL2")
set(SDL2_LIB_LINUX "/usr/lib/x86_64-linux-gnu")

# When finding the headers, I want the Windows path to be on the bottom.
# It's better that mac and linux find their system headers

# Find SDL2
find_path(SDL2_INCLUDE_DIR SDL.h
    PATHS
    "${SDL2_INCLUDE_MAC}"
    "${SDL2_INCLUDE_LINUX}"
	"${SDL2_WIN}/include"
)
find_library(SDL2_LIBRARY NAMES SDL2
    PATHS
    "${SDL2_LIB_MAC}"
    "${SDL2_LIB_LINUX}"
    "${SDL2_WIN}/lib/x86/"
)
find_library(SDL2MAIN_LIBRARY NAMES SDL2main
    PATHS
    "${SDL2_LIB_MAC}"
    "${SDL2_LIB_LINUX}"
	"${SDL2_WIN}/lib/x86/"
)

# SDL2_image
find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h
    PATHS
    "${SDL2_INCLUDE_MAC}"
    "${SDL2_INCLUDE_LINUX}"
    "${SDL2_IMAGE_WIN}/include"
)
find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image
    PATHS
    "${SDL2_LIB_MAC}"
    "${SDL2_LIB_LINUX}"
    "${SDL2_IMAGE_WIN}/lib/x86"
)

# SDL2_mixer
find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h
    PATHS
    "${SDL2_INCLUDE_MAC}"
    "${SDL2_INCLUDE_LINUX}"
    "${SDL2_MIXER_WIN}/include"
)
find_library(SDL2_MIXER_LIBRARY NAMES SDL2_mixer
    PATHS
    "${SDL2_LIB_MAC}"
    "${SDL2_LIB_LINUX}"
    "${SDL2_MIXER_WIN}/lib/x86"
)

# SDL2_ttf
find_path(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
    PATHS
    "${SDL2_INCLUDE_MAC}"
    "${SDL2_INCLUDE_LINUX}"
    "${SDL2_TTF_WIN}/include"
)
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf
    PATHS
    "${SDL2_LIB_MAC}"
    "${SDL2_LIB_LINUX}"
    "${SDL2_TTF_WIN}/lib/x86"
)

# Find static libraries (no dlls).
# Include with:
# include_directories(<target_name> ${<static_library_name>_SOURCE_DIR})
# Link with:
# target_link_libraries(<target_name> <static_library_name>) #no ${} needed 

# Add tinyXML
add_subdirectory(lib/tinyxml EXCLUDE_FROM_ALL)

# Add SDL2_gfx 
add_subdirectory(lib/SDL2_gfx EXCLUDE_FROM_ALL)

add_subdirectory(assets)

# Add config
add_subdirectory(config)

# Add Project Folder
add_subdirectory(src)