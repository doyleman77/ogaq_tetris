#include <iostream>
#include "game.hpp"

Game::Game()
{
    if(!SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "Error initializing SDL!" << std::endl;
    }
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
};

Game::Game(int width, int height)
{

};


