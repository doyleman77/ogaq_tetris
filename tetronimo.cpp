#include "tetronimo.hpp"

Tetronimo::Tetronimo()
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			shape[x][y] = 0;
	rotation = 0;
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
    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++)
            shape[x][y] = 0;

	switch (eshape)
	{
	case Shape::I:
        shape[1][0] = shape[1][1] = shape[1][2] = shape[1][3] = 1;
		break;
	case Shape::J:
        shape[1][1] = shape[2][1] = shape[3][1] = shape[3][2] = 2;
		break;
	case Shape::L:
        shape[1][1] = shape[2][1] = shape[3][1] = shape[1][2] = 3;
		break;
	case Shape::O:
        shape[1][1] = shape[1][2] = shape[2][1] = shape[2][2] = 4;
		break;
	case Shape::S:
        shape[0][2] = shape[1][1] = shape[1][2] = shape[2][1] = 5;
		break;
	case Shape::Z:
        shape[0][1] = shape[1][1] = shape[1][2] = shape[2][2] = 6;
		break;
	case Shape::T:
        shape[1][2] = shape[2][1] = shape[2][2] = shape[3][2] = 7;
		break;
	}
}

void Tetronimo::update()
{

}

void Tetronimo::move_left()
{

}

void Tetronimo::move_right()
{

}

void Tetronimo::rotate()
{

}
