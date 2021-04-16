#include "block.hpp"

Block::Block()
{
	this->_position = {10,0};
	this->_color;
	this->blockSize = 0;
}

Block::Block(int size)
{
	this->_position = {10,0};
	this->_color;
	this->blockSize = size;
}

Block::Block(int8_t x, int8_t y, Color c, int bs)
{
	this->_position = std::make_pair(x, y);
	this->_color = c;
	this->blockSize = bs;
}

Block::~Block()
{
}

void Block::render(SDL_Renderer *renderer, Grille *grid) const
{
	auto pos = this->_position;
	auto pixels = grid->map_cord(pos.first, pos.second);
	Color primary;
	SDL_Rect r;

	SDL_GetRenderDrawColor(renderer, &primary.r, &primary.g, &primary.b, &primary.a);
	SDL_SetRenderDrawColor(renderer, this->_color.r, this->_color.g, this->_color.b, this->_color.a);

	if (grid->index_grille == 0)
		if (mode == SOLO)
			r.x = pixels.first + X_GRILLE_CENTERED;
		else
			r.x = pixels.first + X_GRILLE_1;
	else
		r.x = pixels.first + X_GRILLE_2;

	r.y = pixels.second + Y_GRILLE;
	r.w = r.h = this->blockSize;

	SDL_RenderFillRect(renderer, &r);
	SDL_SetRenderDrawColor(renderer, primary.r, primary.g, primary.b, primary.a);
}

