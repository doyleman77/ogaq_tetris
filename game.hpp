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
#include "tetronimo.hpp"

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
    int fps, level, lines;
	int drop_time;
	int delta_time, previous_tick_time;
    bool key_right, key_left, key_down, key_up;
    int grid[20][10];
    SDL_Rect tetri[8];
    Tetronimo* currentPiece;
	//Sprite grid[20][10];
    bool running, paused;
    int screen_width, screen_height;
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::map<std::string, SDL_Texture*> texture_cache;
	// core gameplay

	// ui crap
	SDL_Rect playfield; // dimensions of the playfield only. should be 320x640, typically.
	void clear_lines();
};
