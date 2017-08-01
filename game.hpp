#pragma once
#include <iostream>
#include <map>
#include <string>

#ifdef _WIN32
#include "SDL.h"
#endif

#ifndef _WIN32
#include "SDL2/SDL.h"	
#endif

#include "sprite.hpp"


enum BlockColor
{
    RED = 0,
    ORANGE,
    GREEN,
    PURPLE,
    BLUE,
    YELLOW,
    CYAN
};

class Game
{
public:
    Game();
    Game(int width, int height);
    ~Game();

    void    play();
    void    draw();
    void    update();
	void	load_image(std::string file);
    void    setup();

private:
    int score;
    short fps, level;
	short drop_time;
    int grid[20][10];
    SDL_Rect tetri[8];

	//Sprite grid[20][10];
    bool running, paused;
    int screen_width, screen_height;
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::map<std::string, SDL_Texture*> texture_cache;
	// core gameplay

	// ui crap
	SDL_Rect playfield; // dimensions of the playfield only. should be 320x640, typically.
};
