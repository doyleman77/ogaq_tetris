#pragma once

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
		Tetronimo();
        Tetronimo(Shape);
        ~Tetronimo();
		void	construct_piece(Shape);
        void    update();
		void	move_left();
		void	move_right();
		void	rotate();
    private:
		int rotation;
        int x, y;
        int shape[4][4];
		short update_time;
};