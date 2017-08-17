#pragma once

#ifdef _WIN32
#include "SDL.h"
#endif

#ifndef _WIN32
#include "SDL2/SDL.h"
#endif


enum Shape
{
    I = 0,
    L,
    J,
    S,
    Z,
    T,
    O
};

class Tetronimo
{
    public:
		Tetronimo(SDL_Texture* tex, int board[20][10]);
        Tetronimo(Shape);
        ~Tetronimo();
		void	construct_piece(Shape);
        void    update(int time_passed);
		void	move_left();
		void	move_right();
		void    move_down();
		void	rotate();
		void    draw(SDL_Renderer* renderer);
    private:
        SDL_Texture* texture;
        SDL_Rect texture_rect;
		int rotation;
        int x, y, x_offset, y_offset;
        int shape[4][4];
        Shape tetro_shape;
		int update_time;
        bool placed;
        int (*board)[10];
		bool collision_check();

};
