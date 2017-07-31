#include <iostream>
#include "SDL2/SDL.h"

#include "game.hpp"
int main(int argc, char* args[])
{
	Game game;
	/// game.load_image("bg_tetro");
	game.load_image("blocks2");
	game.play();
    return 0;
}
