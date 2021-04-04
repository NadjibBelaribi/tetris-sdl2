#ifndef _BLOCK_H_
#define _BLOCK_H_

class Block;

#include <SDL2/SDL.h>
#include <utility>
 #include "color.hpp"

class Block {
public:
	Block();
	Block(int);
	Block(int8_t, int8_t, Color, int);
	~Block();
	void render(SDL_Renderer *, Grid *);
	void setPosition(int8_t, int8_t);
	void translate(int8_t, int8_t);
	void setColor(Color c);
	std::pair<int8_t, int8_t> position();
private:
	std::pair<int8_t, int8_t> _position;
	Color _color;
	int _size;
};

#endif
