#include <iostream>

#ifdef _WIN32
#include "SDL.h"
#endif

#ifndef _WIN32
#include "SDL2/SDL.h"	
#endif

#include "game.hpp"
int main(int argc, char* args[])
{
	Game game;
	/// game.load_image("bg_tetro");
	game.load_image("blocks2");
	game.play();
    return 0;
}
