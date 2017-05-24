#include <iostream>
#include "SDL2/SDL.h"

int main(int argc, char* args[])
{
    const int SCREEN_WIDTH = 320;
    const int SCREEN_HEIGHT = 640;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Event eventhandle;
    bool running = true;
    while(running)
    {
        while(SDL_PollEvent(&eventhandle) != 0)
        {
            if(eventhandle.type == SDL_QUIT) running = false;
        }
    }
    window = nullptr;
    return 0;
}
