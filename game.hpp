#pragma once
#include "SDL.h"
#include <iostream>
#include <map>
#include <string>

class Game
{
public:
    Game();
    Game(int width, int height);
    ~Game();

    void    play();
    void    draw();
    void    update();

private:
    int score;
    short fps, level;
    int grid[20][10];
    bool running, paused;
    int screen_width, screen_height;
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::map<std::string, SDL_Texture*> texture_cache;

};
