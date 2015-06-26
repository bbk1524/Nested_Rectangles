#include <SDL.h>
#include <SDL2_gfx-1.0.1/SDL2_gfxPrimitives.h>


//I need to define this somewhere to query string attributes. If I do it here, I get linker errors.
//Following http ://www.gamedev.net/topic/610820-tinyxml-linker-errors-help-beginner-please/,
//If I use VS to define it for projects tinyxml and this one, it works.
//#define TIXML_USE_STL
//Also works if I define it in tinyxml.h at the top
#include <tinyxml/tinyxml.h>

#include <string>
#include <fstream>
#include <iostream>


//You can format arguments using printf notations: EX: LOG_ERROR("problem with file %s", filename);
//See http://c.learncodethehardway.org/book/ex20.html for more detail
// Formatted strings must be char* (call std::string::c_str() on std::string)
#define LOG_ERROR(M, ...) fprintf(stderr, "[ERROR] (%s : %s : %d: ) " M "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
 
//global variables yay!
const int G_WINDOW_WIDTH = 800;
const int G_WINDOW_HEIGHT = 600;

class Box 
{
public:
	SDL_Renderer* renderer;
	std::string name;
	Sint16 x1;
	Sint16 y1;
	Sint16 x2;
	Sint16 y2;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;

	bool draw()
	{
		Uint8 r_old, g_old, b_old, a_old;
		int result = 0;
		// All of the below operations produce -1 on failure. ORing them with zero checks to see if they failed.
		result |= SDL_GetRenderDrawColor(renderer, &r_old, &g_old, &b_old, &a_old);
		result |= boxRGBA(renderer, x1, y1, x2, y2, r, g, b, a);
		result |= SDL_SetRenderDrawColor(renderer, r_old, g_old, b_old, a_old);
		return result == 0;
	}

	void set_colors(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void set_position(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
	// Make a sub-box from the percentages of the width and height of the parent.
	void set_percentage(const Box & parent, float perc_x1, float perc_y1, float perc_x2, float perc_y2)
	{
		Sint16 parent_width = parent.x2 - parent.x1;
		Sint16 parent_height = parent.y2 - parent.y1;
		//TODO: test this cast
		x1 = Sint16(parent.x1 + perc_x1 * parent_width);
		y1 = Sint16(parent.y1 + perc_y1 * parent_height);
		x2 = Sint16(parent.x2 - perc_x2 * parent_width);
		y2 = Sint16(parent.y2 - perc_y2 * parent_height);
	}

	void set_offset(const Box& parent, Sint16 off_x1, Sint16 off_y1, Sint16 off_x2, Sint16 off_y2)
	{
		x1 = parent.x1 + off_x1;
		y1 = parent.y1 + off_y1;
		x2 = parent.x2 - off_x2;
		y2 = parent.y2 - off_y2;
	}

	Box()
	{
		renderer = nullptr;
		name = "none";
		x1 = 0; y1 = 0; x2 = 0; y2 = 0;
		r = 0; g = 0; b = 0; a = 0;
	}


	//I probably don't need all of these inits...
	//just something to init the renderer and name
	bool init(SDL_Renderer* renderer,
		Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2,
		Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		this->renderer = renderer;
		set_colors(r, g, b, a);
		set_position(x1, y1, x2, y2);
		return this->renderer != nullptr;
	}

	bool init(const Box & parent,
		float perc_x1, float perc_y1, float perc_x2, float perc_y2,
		Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		this->renderer = parent.renderer;
		set_colors(r, g, b, a);
		set_percentage(parent, perc_x1, perc_y1, perc_x2, perc_y2);
		return this->renderer != nullptr;
	}

	bool init(const Box & parent,
		Sint16 off_x1, Sint16 off_y1, Sint16 off_x2, Sint16 off_y2,
		Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		this->renderer = parent.renderer;
		set_colors(r, g, b, a);
		set_offset(parent, off_x1, off_y1, off_x2, off_y2);
		return this->renderer != nullptr;
	}

	//I'm sure I could make this better if I had a state machine or something
	bool init(Box const * parent, SDL_Renderer* renderer, TiXmlElement* node)
	{
		//Get Name if available
		std::string name;
		if (node->QueryStringAttribute("name", &name) == TIXML_SUCCESS)
		{
			this->name = name;
		}

		//Get colors
		//TODO: make boxes get their parent's colors if this isn't found
		TiXmlElement* color = node->FirstChildElement("color");
		if (color)
		{
			unsigned int r, g, b, a; //can static_cast these to Uint8

			color->QueryUnsignedAttribute("r", &r);
			color->QueryUnsignedAttribute("g", &g);
			color->QueryUnsignedAttribute("b", &b);
			color->QueryUnsignedAttribute("a", &a);
			//TODO: maybe test them for the range [0-255]
			//set colors
			set_colors(static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a));
		}
		else
		{
			LOG_ERROR("no color found");
			return false;
		}

		TiXmlElement* position = node->FirstChildElement("position");
		if (position)
		{
			this->renderer = renderer;
			//TinyXML only lets me get ints. I'm using a C-style cast to get to Sint16 because a static_cast won't work
			//TODO: check if the cast works for all platforms. Works on Windows
			int x1, y1, x2, y2; //also used for offsets
			position->QueryIntAttribute("x1", &x1);
			position->QueryIntAttribute("y1", &y1);
			position->QueryIntAttribute("x2", &x2);
			position->QueryIntAttribute("y2", &y2);


			//put in screen boundaries if necessary
			if (x1 == -1) {x1 = 0;}
			if (y1 == -1) {y1 = 0;}
			if (x2 == -1) {x2 = G_WINDOW_WIDTH;}
			if (y2 == -1) {y2 = G_WINDOW_HEIGHT;}

			//NOTE: Casting to Sint16 from int is undefined. Works on Windows
			set_position(Sint16(x1), Sint16(y1), Sint16(x2), Sint16(y2));
			return this->renderer != nullptr;
		}
		else if (parent)
		{
			this->renderer = parent->renderer;

			TiXmlElement* offset = node->FirstChildElement("offset");
			TiXmlElement* percentage = node->FirstChildElement("percentage");
			if (offset)
			{
				int off_x1, off_y1, off_x2, off_y2;

				offset->QueryIntAttribute("off_x1", &off_x1);
				offset->QueryIntAttribute("off_y1", &off_y1);
				offset->QueryIntAttribute("off_x2", &off_x2);
				offset->QueryIntAttribute("off_y2", &off_y2);

				//NOTE: another undefined cast...
				set_offset(*parent, Sint16(off_x1), Sint16(off_y1), Sint16(off_x2), Sint16(off_y2));
				return renderer != nullptr;
			}
			else if (percentage)
			{
				float perc_x1, perc_y1, perc_x2, perc_y2;
				percentage->QueryFloatAttribute("perc_x1", &perc_x1);
				percentage->QueryFloatAttribute("perc_y1", &perc_y1);
				percentage->QueryFloatAttribute("perc_x2", &perc_x2);
				percentage->QueryFloatAttribute("perc_y2", &perc_y2);


				set_percentage(*parent, perc_x1, perc_y1, perc_x2, perc_y2);
				return this->renderer != nullptr;
			}
			else 
			{
				LOG_ERROR("No offset or no position");
				return false;
			}
		}
		else
		{
			LOG_ERROR("No position or no parent");
			return false;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const Box& box);

};

std::ostream& operator<<(std::ostream& os, const Box& box)
{
	os << "Name: " << box.name << std::endl;
	os << "Position : " << box.x1 << " " << box.y1 << " " << box.x2 << " " << box.y2 << std::endl;
	//the '+' casts to Uint32 for numerical output
	os << "Color : " << +box.r << " " << +box.g << " " << +box.b << " " << +box.a << std::endl;
	return os;
}

bool create_box_tree(Box* parent, SDL_Renderer* renderer, TiXmlElement* node)
{
	Box b;
	if (!b.init(parent, renderer, node))
	{
		LOG_ERROR("Bad node");
		return false;
	}
	std::cout << b;
	b.draw();

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

bool load_boxes(const char* layout_file, SDL_Renderer* renderer)
{
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
	return create_box_tree(nullptr, renderer, node);


}

bool test_box_init(SDL_Renderer* renderer)
{
	Box b;
	b.init(renderer, 0, 0, G_WINDOW_WIDTH, G_WINDOW_HEIGHT, 255, 0, 0, 255);
	std::cout << b;
	std::cout << b.draw() << std::endl;


	Box ba;
	ba.init(b, .2f, .3f, .2f, .3f, 0, 0, 255, 255);
	std::cout << ba;
	std::cout << ba.draw() << std::endl;

	Box baa;
	baa.init(ba, Sint16(2), Sint16(2), Sint16(2), Sint16(2), 255, 255, 0, 255);
	std::cout << baa;
	std::cout << baa.draw() << std::endl;

	return true;
}

int main (int argc, char** argv)
{
	SDL_Window* window = NULL;
	window = SDL_CreateWindow(
		"Nested_Rectangles",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		G_WINDOW_WIDTH,
		G_WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
		);

	// Setup renderer
	SDL_Renderer* G_renderer = NULL;
	G_renderer =  SDL_CreateRenderer( window, 0, SDL_RENDERER_ACCELERATED);

	// Set render color to black ( background will be rendered in this color )
	SDL_SetRenderDrawColor( G_renderer, 0, 0, 0, 255 );

	// Clear winow
	SDL_RenderClear( G_renderer ); 

	// load boxes from file
	const char* layout_file = "./Config/layout.xml";
	load_boxes(layout_file, G_renderer);

	// Render to the screen
	SDL_RenderPresent(G_renderer);

	// Wait for a little
	SDL_Delay( 6000 );

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
