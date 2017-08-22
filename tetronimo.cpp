#include "tetronimo.hpp"

Tetronimo::Tetronimo(SDL_Texture* tex, int grid[20][10])
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			shape[x][y] = 0;
	rotation = 0;
	texture = tex;
	texture_rect.x = texture_rect.y = 0;
	texture_rect.w = texture_rect.h = 32;
	update_time = 0;
	board = grid;
}

Tetronimo::Tetronimo(Shape)
{
	//probably wont even use this
}

Tetronimo::~Tetronimo()
{

}

void Tetronimo::construct_piece(Shape eshape)
{
    x = 3;
    y = -1;
    rotation = 0;
    placed = false;
    ///hardcoded because i hate tetris atm
    x_offset = y_offset = 12;

    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++)
            shape[x][y] = 0;

    tetro_shape = eshape;
	switch (eshape)
	{
	case Shape::I:
        shape[0][1] = shape[1][1] = shape[2][1] = shape[3][1] = 1;
        texture_rect.x = 32;
        y = 0;
		break;
	case Shape::J:
        shape[1][1] = shape[2][1] = shape[3][1] = shape[3][2] = 2;
        texture_rect.x = 32*2;
		break;
	case Shape::L:
        shape[1][1] = shape[2][1] = shape[3][1] = shape[1][2] = 3;
		texture_rect.x = 32*3;
		break;
	case Shape::O:
        shape[1][1] = shape[1][2] = shape[2][1] = shape[2][2] = 4;
		texture_rect.x = 32*4;
		break;
	case Shape::S:
        shape[1][2] = shape[2][2] = shape[2][1] = shape[3][1] = 5;
		texture_rect.x = 32*5;
		break;
	case Shape::Z:
        shape[1][1] = shape[2][1] = shape[2][2] = shape[3][2] = 6;
		texture_rect.x = 32*6;
		break;
	case Shape::T:
        shape[1][1] = shape[2][1] = shape[2][2] = shape[3][1] = 7;
		texture_rect.x = 32*7;
		break;
	}
}

void Tetronimo::update(int passed_time)
{
    update_time += passed_time;
    if(update_time > 1500)
    {
        update_time -= 1500;
        move_down();
    }
}

void Tetronimo::draw(SDL_Renderer* renderer)
{
    ///this assumes default 32x32 block sizes. maybe should find a way to pull square info
    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++)
            if(shape[x][y] > 0)
            {
                SDL_Rect dest;
                dest.x = this->x*32 + (x*32) + x_offset;
                dest.y = this->y*32 + (y*32) + y_offset;
                dest.w = 32;
                dest.h = 32;
                SDL_RenderCopy(renderer, texture, &texture_rect, &dest);
            }
}

void Tetronimo::move_left()
{
    if(placed) return;
    x--;
    if(collision_check()) x++;
}

void Tetronimo::move_right()
{
    if(placed) return;
    x++;
    if(collision_check()) x--;
}

void Tetronimo::move_down()
{
    y++;
    if(collision_check())
    {
        y--;
        placed = true;

        ///copy data of tetronimo to board
        for(int cx = 0; cx < 4; cx++)
            for(int cy = 0; cy < 4; cy++)
            {
                if(shape[cx][cy] > 0) ///dont want to blank out spaces.
                            board[y + cy][x + cx] = shape[cx][cy];

            }
        Shape new_shape = (Shape)(rand()%7);
        construct_piece(new_shape);
        return;
    }
    update_time = 0;
}

void Tetronimo::rotate()
{

    rotation++;
    attempt_rotate();
    if(!collision_check()) return;

    if(rotation > 0)rotation--;
    if(rotation == 0) rotation = 3;
    attempt_rotate();
}

bool Tetronimo::attempt_rotate()
{
    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++)
            shape[x][y] = 0;
    if(rotation > 3) rotation = 0;

    switch(tetro_shape)
    {
    case Shape::I:
        ///if(rotation > 1) rotation = 0;
        if(rotation == 0)
            shape[0][1] = shape[1][1] = shape[2][1] = shape[3][1] = 1;
        if(rotation == 1)
            shape[2][0] = shape[2][1] = shape[2][2] = shape[2][3] = 1;
        if(rotation == 2)
            shape[0][1] = shape[1][1] = shape[2][1] = shape[3][1] = 1;
        if(rotation == 3)
            shape[2][0] = shape[2][1] = shape[2][2] = shape[2][3] = 1;
		break;
	case Shape::J:
        if(rotation == 0)
            shape[1][1] = shape[2][1] = shape[3][1] = shape[3][2] = 2;
        if(rotation == 1)
            shape[2][0] = shape[3][0] = shape[2][1] = shape[2][2] = 2;
        if(rotation == 2)
            shape[1][0] = shape[1][1] = shape[2][1] = shape[3][1] = 2;
        if(rotation == 3)
            shape[2][0] = shape[2][1] = shape[2][2] = shape[1][2] = 2;
		break;
	case Shape::L:
        if(rotation == 0)
            shape[1][1] = shape[2][1] = shape[3][1] = shape[1][2] = 3;
        if(rotation == 1)
            shape[2][0] = shape[2][1] = shape[2][2] = shape[3][2] = 3;
        if(rotation == 2)
            shape[1][1] = shape[2][1] = shape[3][1] = shape[3][0] = 3;
        if(rotation == 3)
            shape[1][0] = shape[2][0] = shape[2][1] = shape[2][2] = 3;
		break;
	case Shape::O:
        rotation = 0;
        if(rotation == 0)
            shape[1][1] = shape[1][2] = shape[2][1] = shape[2][2] = 4;
		break;
	case Shape::S:
        ///if(rotation > 1) rotation = 0;
        if(rotation == 0)
            shape[1][2] = shape[2][2] = shape[2][1] = shape[3][1] = 5;
        if(rotation == 1)
            shape[2][0] = shape[2][1] = shape[3][1] = shape[3][2] = 5;
        if(rotation == 2)
            shape[1][2] = shape[2][2] = shape[2][1] = shape[3][1] = 5;
        if(rotation == 3)
            shape[2][0] = shape[2][1] = shape[3][1] = shape[3][2] = 5;
		break;
	case Shape::Z:
        ///if(rotation > 1) rotation = 0;
        if(rotation == 0)
            shape[1][1] = shape[2][1] = shape[2][2] = shape[3][2] = 6;
        if(rotation == 1)
            shape[3][0] = shape[3][1] = shape[2][1] = shape[2][2] = 6;
        if(rotation == 2)
            shape[1][1] = shape[2][1] = shape[2][2] = shape[3][2] = 6;
        if(rotation == 3)
            shape[3][0] = shape[3][1] = shape[2][1] = shape[2][2] = 6;
		break;
	case Shape::T:
        if(rotation == 0)
            shape[1][1] = shape[2][1] = shape[2][2] = shape[3][1] = 7;
        if(rotation == 1)
            shape[2][0] = shape[2][1] = shape[2][2] = shape[3][1] = 7;
        if(rotation == 2)
            shape[1][1] = shape[2][1] = shape[2][0] = shape[3][1] = 7;
        if(rotation == 3)
            shape[2][0] = shape[2][1] = shape[2][2] = shape[1][1] = 7;
		break;
    }

    //return !collision_check();
}

bool Tetronimo::collision_check()
{
    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++)
        {
            ///check for wall
            ///i believe the problem of wall sticking to be here.
            if(shape[x][y] > 0)
                if((this->x + x+1 > 10) || (this->x + x < 0)) return true;
            ///check for floor
            if(shape[x][y] > 0 && (this->y + y == 20)) return true;
            ///check for board
            if(shape[x][y] > 0)
                if(board[this->y + y][this->x + x] > 0) return true;
        }
        return false;
}
