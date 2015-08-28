# Dynamic Libraries for Windows!
It's safe to unzip the following here:

- SDL2_image-devel-2.0.0-VC.zip
- SDL2_mixer-devel-2.0-VC.zip
- SDL2_ttf-devel-2.0.12-VC.zip
- SDL2-devel-2.0.3-VC.zip

If these folders change, see the root CMakeLists.txt

# Static Libraries for everyone!

It's safe to unzip **Box2D_v2.1.2** here.

**liquidfun-1.1.0.zip** should be unzipped inside liquidfun-1.1.0/
Then, edit `liquidfun-1.1.0/liquidfun/Box2D/CMakeLists.txt` by adding 
`FindPackage(Threads)` beneath `project(Box2D)` so it will build properly.
Alternatively, use the original Box2D library in the root CMakeLists.txt.
By doing this, the project will build faster, but you will lose functionality.

**SDL2_gfx-1.0.1.zip** should be unzipped inside SDL2_gfx/

**tinyxml_2_6_2.zip** should be unzipped inside tinyxml/
Additionally, to use the STL component of tinyxml, place a 
`#define TIXML_USE_STL` at the top of **tinyxml/tinyxml.h**


To "trim" the folders of unnecessary files, run `trim_libraries.py`.
Please, ***PAY CLOSE ATTENTION TO THE FILES BEING DELETED!***
