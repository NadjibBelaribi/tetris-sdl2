#ifndef _TETROMINO_H_
#define _TETROMINO_H_

class Tetromino;

#include <memory>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>
#include "block.hpp"
#include "color.hpp"
#include "utils.hpp"


class Tetromino {
public:
	Tetromino();
	Tetromino(TetrominoShape);
	~Tetromino();
	void render(SDL_Renderer *, Grille *)const;

	bool ableMove(Direction, Grille *);
	bool getState();
	void rotate(Grille *);
	void translate(int8_t, int8_t);
	
	// getters
	std::vector<Block> &blocks();
	Color &color();
	TetrominoShape shape() const;
private:
	void setTetromino(TetrominoShape);
	void move(Direction);
	std::vector<Block> _blocks;
	std::pair<int8_t, int8_t> _pivot;
	bool move_off;
	Color _color;
	TetrominoShape _shape;
};



#endif
