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
	switch (eshape)
	{
	case Shape::I:
		shape[4][4] =
		{ {0,1,0,0},
		 {0,1,0,0},
		 {0,1,0,0},
		 {0,1,0,0} };
		break;
	case Shape::J:
		break;
	case Shape::L:
		break;
	case Shape::O:
		break;
	case Shape::S:
		break;
	case Shape::T:
		break;
	case Shape::Z:
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