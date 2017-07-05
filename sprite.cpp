#include "sprite.hpp"

Sprite::Sprite()
{

}

Sprite::Sprite(SDL_Texture** img)
{
	image = img;
}

Sprite::~Sprite()
{
	image = nullptr;
}

void Sprite::set_dimensions(int w, int h)
{
	rect.w = w;
	rect.h = h;
}

void Sprite::set_position(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Sprite::set_image(SDL_Texture** img)
{
	image = img;
	SDL_QueryTexture(*img, NULL, NULL, &rect.w, &rect.h);
}