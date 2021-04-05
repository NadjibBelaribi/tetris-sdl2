#include "block.hpp"

Block::Block()
{
	this->_position = std::make_pair(10, 0);
	this->_color;
	this->_size = 0;
}

Block::Block(int size)
{
	this->_position = std::make_pair(10, 0);
	this->_color;
	this->_size = size;
}

Block::Block(int8_t x, int8_t y, Color c, int s)
{
	this->_position = std::make_pair(x, y);
	this->_color = c;
	this->_size = s;
}

Block::~Block()
{
}

std::pair<int8_t, int8_t> Block::getPosition()
{
	return this->_position;
}

void Block::render(SDL_Renderer *renderer, Grille *grid)
{
	auto pos = this->_position;
	auto pixels = grid->map_cord(pos.first, pos.second);
	Color primary;

	SDL_GetRenderDrawColor(renderer,
						   &primary.r,
						   &primary.g,
						   &primary.b,
						   &primary.a);

	SDL_SetRenderDrawColor(renderer,
						   this->_color.r,
						   this->_color.g,
						   this->_color.b,
						   this->_color.a);

	SDL_Rect r;

	if
	    (grid->index_grille  == 1 ) r.x = pixels.first + X_GRILLE_1 ;
	else
        r.x = pixels.first + X_GRILLE_2 ;
	r.y = pixels.second;
	r.w = r.h = this->_size;

	SDL_RenderFillRect(renderer, &r);

	SDL_SetRenderDrawColor(renderer,
						   primary.r,
						   primary.g,
						   primary.b,
						   primary.a);
}

void Block::translate(int8_t x, int8_t y)
{
	this->_position.first += x;
	this->_position.second += y;
}

void Block::setPosition(int8_t x, int8_t y)
{
	this->_position.first = x;
	this->_position.second = y;
}

void Block::setColor(Color c)
{
	this->_color = c;
}
