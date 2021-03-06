#pragma once
#include <iostream>

#ifdef _WIN32
#include "SDL.h"
#endif

#ifndef _WIN32
#include "SDL2/SDL.h"	
#endif

class Sprite
{
public:
	Sprite();
	Sprite(SDL_Texture** image);
	~Sprite();

	void set_image(SDL_Texture** img);
	void set_position(int x, int y);
	void set_dimensions(int w, int h);
private:
	SDL_Rect rect;
	SDL_Texture** image; // point to a texture out of game's texture_cache;
};
