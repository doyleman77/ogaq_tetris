#pragma once
#include "SDL2/SDL.h"

class Game
{
public:
    Game();
    Game(int width, int height);
    ~Game();

    play();
    draw();
    update();

private:
    bool running, paused;
    int screen_width, screen_height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int score;
    short fps, level;
};
