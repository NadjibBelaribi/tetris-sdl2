#ifndef _GRID_H_
#define _GRID_H_

class Grille;

#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>
#include <utility>
#include "color.hpp"
#include "tetromino.hpp"
#include "utils.hpp"

class Grille {
public:
	Grille(uint8_t, uint8_t, uint8_t,uint8_t);
	~Grille();
	std::pair<int, int> map_cord(int8_t, int8_t) const;
	void render(SDL_Renderer *);
	void setColor(Tetromino);
    uint8_t index_grille ;
	bool moveTetromino(Tetromino, Direction);
	uint32_t isTetris();
	uint8_t width() const;
	uint8_t height() const;
	uint8_t border() const;
private:
	void setMap();
	uint8_t _width, _height, _border;
	void updateMap(uint8_t);
	std::vector< std::vector<Color> > map;
};

#endif
