#ifndef SCREEN_H
#define SCREEN_H
//This class holds my screen layout. Boxes go here.

#include <vector>
#include <string>
#include "Definitions.h"
#include "GraphicsSystem.h"
#include "Box.h"
#include "tinyxml/tinyxml.h"
#include <algorithm>
//TODO: rm
#include <SDL.h>
#include <SDL_image.h>


class Screen {
public:

    SDL_Rect scale;
    SDL_Texture * tex;

	std::vector<Box> boxes;

	Screen() = default;

	~Screen() = default;

	bool init(const char* layout_file)
	{
		graphics_system.init("Boxes", G_WINDOW_WIDTH, G_WINDOW_HEIGHT);

		TiXmlDocument doc(layout_file);
		if (!doc.LoadFile())
		{
			LOG_ERROR("Can't find file : %s", layout_file);
			return false;
		}
		TiXmlElement* node = doc.FirstChildElement("box");
		if (!node)
		{
			TiXmlHandle hDoc(&doc);
			LOG_ERROR("Can't find box. Element found: %s", hDoc.FirstChildElement().Element()->Value());
			return false;
		}
		create_box_tree(nullptr, graphics_system.get_renderer(), node);
                //TODO: rm
                load_image();
                return true;
	}

        //TODO: move a Texture into it's own class
        void load_image()
        {
		std::string image_path = "./Assets/Images/hello.bmp";
		SDL_Surface * bmp = SDL_LoadBMP(image_path.c_str());
		tex = SDL_CreateTextureFromSurface(graphics_system.get_renderer(), bmp);
                SDL_FreeSurface(bmp);
		// SDL_RenderClear(screen.graphics_system.get_renderer());
		// Box * b;
		// b = (screen.get_box_by_name("Game")); 
		// std::cout << *b; //this is where it's failing ^ ^ 
		// scale.x = b->x1;
		// scale.y = b->y1;
		// scale.w = b->x2 - b->x1;
		// scale.h = b->y2 - b->y1;

		scale.x = 0;
		scale.y = 0;
		scale.w = 100;
		scale.h = 100;
        }

	bool destroy() {
		return true;
	}

	void draw()
	{
		graphics_system.begin();
		for (auto b : boxes)
		{
			//std::cout << b;
			b.draw();
		}

                //TODO: rm
                // draw the bmp (this has to be horribly inefficient
		SDL_RenderCopy(graphics_system.get_renderer(), tex, NULL, &scale);

		graphics_system.present();
	}

	bool create_box_tree(Box* parent, SDL_Renderer* renderer, TiXmlElement* node)
	{
		Box b;
		if (!b.init(parent, renderer, node))
		{
			LOG_ERROR("Bad node");
			return false;
		}
		boxes.push_back(b);

		for (TiXmlElement* child = node->FirstChildElement("box"); child; child = child->NextSiblingElement("box"))
		{
			//To iterate is human; to recurse, divine.
			if (!create_box_tree(&b, renderer, child))
			{
				return false;
			}
		}

		return true;
	}

	Box * get_box_by_name(std::string name)
	{
		//use std::find_if here.
	}

//private:
	Graphics_System graphics_system;
};


#endif
