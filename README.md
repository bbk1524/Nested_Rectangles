# Nested_Rectangles

Loads an XML file and renders it with SDL.

## Building on Windows
1. Install CMake 3.1 or above
2. From this folder in Windows Explorer, Shift + Right Click an empty spot and click *Open
   Command Window Here*.
3. Enter the following commands:
```
mkdir Build
cd Build
cmake -G "Visual Studio 12" ..
```
# Notes and TODOs
Instead of copying Assets/ to a folder where Visual Studio or make can find it, I'm going to use SDL_GetBasePath()
to do it.