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

class Screen {
public:

	std::vector<Box> boxes;

	Screen() 
	{

	}

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
		return create_box_tree(nullptr, graphics_system.get_renderer(), node);
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