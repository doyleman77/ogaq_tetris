#include <iostream>
#include "game.hpp"

Game::Game()
{
    if(!SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "Error initializing SDL!" << std::endl;
    }
    screen_width = 420; /// 320 for tetronimos' 10w grid and 100 for extra UI
    screen_height = 740; /// 640 for tetronimos' 20h grid and 100 for extra UI
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
};

Game::Game(int width, int height)
{
    screen_width = width;
    screen_height = height;
	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

};

Game::~Game()
{
	SDL_DestroyWindow(window);
}

