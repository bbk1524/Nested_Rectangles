#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture 
{
public:
	Texture()
	{
		texture = nullptr;
		scale.x = 0;
		scale.y = 0;
		scale.w = 0;
		scale.h = 0;
	}
	
	~Texture() = default;

	bool init(SDL_Renderer * renderer, std::string image_path)
	{
		this->renderer = renderer;
		SDL_Surface * bmp = SDL_LoadBMP(image_path.c_str());
		this->texture = SDL_CreateTextureFromSurface(renderer, bmp);
		assert(texture != NULL); //hi there
		SDL_FreeSurface(bmp);
		scale.x = 0;
		scale.y = 0;
		scale.w = 100;
		scale.h = 100;

		return true;
	}

	bool destroy()
	{
		SDL_DestroyTexture(texture);
		return true;
	}

	void draw()
	{
		SDL_RenderCopy(renderer, texture, NULL, &scale);
	}
//private:
	SDL_Renderer * renderer;
	SDL_Rect scale;
	SDL_Texture * texture;
};

#endif