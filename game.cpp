#include <iostream>
#include "game.hpp"

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
		std::cout << "Error initializing SDL! " << SDL_GetError() << std::endl;
    }
    screen_width = 420; /// 320 for tetronimos' 10w grid and 100 for extra UI
    screen_height = 740; /// 640 for tetronimos' 20h grid and 100 for extra UI

	playfield.x = 12;
	playfield.y = 12;
	playfield.w = 320;
	playfield.h = 640;

	for (int x = 0; x < 20; x++)
		for (int y = 0; x < 10; x++)
			grid[x][y] = 0;
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Game::Game(int width, int height)
{
    screen_width = width;
    screen_height = height;
	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

}

Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Game::load_image(std::string file)
{
	const std::string path = "../assets/images/";
	const std::string fullpath = path + file + ".bmp";
	SDL_Surface* temp_surface = SDL_LoadBMP(fullpath.c_str());
	if (!temp_surface)
	{
		std::cout << SDL_GetError() << " " << SDL_GetBasePath() << std::endl;
	}
	SDL_Texture* new_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	texture_cache[file] = new_texture;
}

void Game::draw()
{
	SDL_RenderClear(renderer);

	// draw begin

	//-BG render
	SDL_Rect bg_printer;
	bg_printer.x = 0;
	bg_printer.y = 0;

	SDL_QueryTexture(texture_cache["bg_tetro"], NULL, NULL, &bg_printer.w, &bg_printer.h);

	for (bg_printer.x = playfield.x; bg_printer.x < (playfield.x + playfield.w); bg_printer.x += bg_printer.w)
		for (bg_printer.y = playfield.y; bg_printer.y < (playfield.y + playfield.h); bg_printer.y += bg_printer.h)
		{
			SDL_RenderCopy(renderer, texture_cache["bg_tetro"], NULL, &bg_printer);
		}

	//draw end
	SDL_RenderPresent(renderer);
}

void Game::update()
{

}

void Game::play()
{
	SDL_Event eventhandle;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&eventhandle) != 0)
		{
			if (eventhandle.type == SDL_QUIT) running = false;
		}
		update();
		draw();
	}
}