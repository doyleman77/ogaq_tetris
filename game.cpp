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

    /// init grid
	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 10; x++)
			grid[y][x] = 0;

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    /// Load Tetris and store
	for(int i = 0; i < 8; i++)
	{
        tetri[i].w = 32;
        tetri[i].h = 32;
        tetri[i].y = 0;
        tetri[i].x = 32*i;
	}

	previous_tick_time = SDL_GetTicks();
	delta_time = 0;

	key_left = key_right = key_up = key_down = false;
	lines = level = 0;
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
	const std::string path = "./assets/images/";
	const std::string fullpath = path + file + ".bmp";

	SDL_Surface* temp_surface = SDL_LoadBMP(fullpath.c_str());
	if (!temp_surface)
	{
		std::cout << SDL_GetError() << " " << SDL_GetBasePath() << std::endl;
		//std::cin.get();
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
	bg_printer.x = playfield.x;
	bg_printer.y = playfield.y;

    ///test
    //int iter = 0;


	bg_printer.w = bg_printer.h = 32;

	for (int y = 0; y < 20; y++, bg_printer.y += bg_printer.h)
	{
        bg_printer.x = playfield.x;
		for (int x = 0; x < 10; x++, bg_printer.x += bg_printer.w)
		{
			//display the current grid
			SDL_RenderCopy(renderer, texture_cache["blocks2"], &tetri[grid[y][x]], &bg_printer);
            currentPiece->draw(this->renderer);
			//display the active tetronimo
		}
    }

	//draw end
	SDL_RenderPresent(renderer);
}

void Game::update()
{
    if (key_up) currentPiece->rotate();
    if (key_right) currentPiece->move_right();
    if (key_left) currentPiece->move_left(); ///why do i use snake_case and camelCase? standardize. also, name directions better.
    if (key_down) currentPiece->move_down();
    currentPiece->update(delta_time);
    if(currentPiece->is_placed())
    {
        ///clear lines
        clear_lines();
        Shape new_shape = (Shape)(rand()%7);
        currentPiece->construct_piece(new_shape);
    }
}

void Game::setup()
{

}

void Game::clear_lines()
{

    for(int y = 0; y < 20; y++)
    {
        int row_total = 0;
        for(int x = 0; x < 10; x++)
        {
            row_total += (bool)grid[y][x];
        }
        if(row_total >= 10) ///we have a full line
        {
            lines++;
            level = lines/10;
            currentPiece->set_drop_time(1000-(level*50));
            std::cout << lines << " " << level << std::endl;
            for(int ny = y; ny > 0; ny--)
                for(int x = 0; x < 10; x++)
                {
                    grid[ny][x] = grid[ny-1][x];
                }
        }
    }
}

void Game::play()
{
	SDL_Event eventhandle;
	bool running = true;
	currentPiece = new Tetronimo(this->texture_cache["blocks2"], grid);
	///currentPiece->construct_piece(Shape::Z);
	Shape start_piece = (Shape)(rand()%7);
	currentPiece->construct_piece(start_piece);
	while (running)
	{
        key_left = key_right = key_up = key_down = false;
        previous_tick_time = SDL_GetTicks();
		while (SDL_PollEvent(&eventhandle) != 0)
		{
			if (eventhandle.type == SDL_QUIT) running = false;
			if (eventhandle.key.keysym.sym == SDLK_ESCAPE) running = false;
			if (eventhandle.type == SDL_KEYDOWN)
			{
                if (eventhandle.key.keysym.sym == SDLK_LEFT) key_left = true;
                if (eventhandle.key.keysym.sym == SDLK_RIGHT) key_right = true;
                if (eventhandle.key.keysym.sym == SDLK_DOWN) key_down = true;
                if (eventhandle.key.keysym.sym == SDLK_UP) key_up = true;
			}
		}
		update();
		draw();
		/// RUDIMENTARY DELAY
		SDL_Delay(16);
		delta_time = SDL_GetTicks() - previous_tick_time;

	}
}
