#ifndef _BLOCK_H_
#define _BLOCK_H_

class Block;

#include <utility>
#include "grille.hpp"
#include "block.hpp"
#include "utils.hpp"
#include "color.hpp"

extern GAME_MODE mode ;

class Block {
public:
	Block();
	Block(int);
	Block(int8_t, int8_t, Color, int);
	~Block();
	void render(SDL_Renderer *, Grille *) const;
	inline void translate(int8_t x, int8_t y){this->_position.first += x;this->_position.second += y;}
	inline void setPosition(int8_t x, int8_t y){this->_position.first = x;this->_position.second = y;}
	inline void setColor(Color c){this->_color = c;}
	inline std::pair<int8_t, int8_t> getPosition(){return this->_position;}
private:
	std::pair<int8_t, int8_t> _position;
	Color _color;
	int blockSize;
};

#endif
