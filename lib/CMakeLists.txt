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

if(MSVC)
	# Find and copy 32-bit DLLs to Game folder
	file(GLOB X86_DLL_FILES
			${SDL2_WIN}/lib/x86/*.dll
			${SDL2_IMAGE_WIN}/lib/x86/*.dll
			${SDL2_MIXER_WIN}/lib/x86/*.dll
			${SDL2_TTF_WIN}/lib/x86/*.dll
	)

	# Important to note that this happens at the cmake step, not the game's compilation.
	# If you remove these, re-run cmake to get them back.
	file(COPY ${X86_DLL_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/bin)
endif()

# Find static libraries (no dlls).
# Include with:
# include_directories(<target_name> ${<static_library_name>_SOURCE_DIR})
# Link with:
# target_link_libraries(<target_name> <static_library_name>) #no ${} needed 

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

project(SDL2_gfx)
include_directories(./SDL2_gfx-1.0.1 ${SDL2_INCLUDE_DIR})
add_library(SDL2_gfx STATIC
	SDL2_gfx-1.0.1/SDL2_framerate.c
	SDL2_gfx-1.0.1/SDL2_framerate.h
	SDL2_gfx-1.0.1/SDL2_gfxPrimitives.c
	SDL2_gfx-1.0.1/SDL2_gfxPrimitives.h
	SDL2_gfx-1.0.1/SDL2_gfxPrimitives_font.h
	SDL2_gfx-1.0.1/SDL2_imageFilter.c
	SDL2_gfx-1.0.1/SDL2_imageFilter.h
	SDL2_gfx-1.0.1/SDL2_rotozoom.c
	SDL2_gfx-1.0.1/SDL2_rotozoom.h
)

project(tinyxml2)
include_directories(./tinyxml2-master)
add_library(tinyxml2 STATIC
	tinyxml2-master/tinyxml2.cpp
	tinyxml2-master/tinyxml2.h
)

add_subdirectory(Box2D-master/Box2D)
