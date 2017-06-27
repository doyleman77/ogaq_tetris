#include <iostream>
#include "SDL.h"

#include "game.hpp"
int main(int argc, char* args[])
{
	Game game;
	game.load_image("bg_tetro");
	game.load_image("blocks");
	game.play();
    return 0;
}
