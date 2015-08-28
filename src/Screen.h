#ifndef SCREEN_H
#define SCREEN_H
//This class holds my screen layout. Boxes go here.

#include <cassert>

#include <vector>
#include <string>
#include "Definitions.h"
#include "GraphicsSystem.h"
#include "Box.h"
#include "tinyxml/tinyxml.h"
#include "Texture.h"

class Screen {
public:

	std::vector<Box> boxes;

	Screen() = default;

	~Screen() = default;

	bool init(std::string layout_file)
	{
		graphics_system.init("Boxes", G_WINDOW_WIDTH, G_WINDOW_HEIGHT);

		TiXmlDocument doc(layout_file.c_str());
		if (!doc.LoadFile())
		{
			LOG_ERROR("Can't find file : %s", layout_file.c_str());
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
		
		return true;
	}

	bool destroy() {
		graphics_system.destroy();
		return true;
	}

	void draw_boxes()
	{
		for (auto b : boxes)
		{
			//std::cout << b;
			b.draw();
		}
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
		//doing this by hand is actually shorter and cleaner than std::find_if
		Box * result = nullptr;

		//find an iterator to the first box with the name
		for (auto i = boxes.begin(); i != boxes.end(); ++i)
		{
			if (i->name == name)
			{
				//deref the iterator to get the box, then pass it's address to result
				result = &(*i);
			}
		}

		return result;
	}

	//private:
	Graphics_System graphics_system;
};


#endif
