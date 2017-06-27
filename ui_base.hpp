#pragma once
#include "SDL.h"

class UI_Base
{
public:
private:
	int xpos, ypos;
	int width, height;
	SDL_Texture* texture;
};