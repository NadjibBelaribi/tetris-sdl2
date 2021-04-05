#include "tetromino.hpp"
#include <algorithm>
#include <cstdio>

Tetromino::Tetromino() {
 	TetrominoShape shape = (TetrominoShape) (rand() % NSHAPES);
	this->setTetromino(shape);
}

Tetromino::Tetromino(TetrominoShape shape) {
	this->setTetromino(shape);
}

void Tetromino::setTetromino(TetrominoShape shape) {
	auto pos = POSITIONS[shape];
	this->move_off = false;
	this->_shape = shape;

	switch(this->_shape) {
	case I:
		this->_pivot = std::make_pair(5, -1);
		this->_color = GREEN;
		break;
	case J:
		this->_pivot = std::make_pair(6, 0);
		this->_color = BLUE;
		break;
	case L:
		this->_pivot = std::make_pair(5, 0);
		this->_color = ORANGE;
		break;
	case O:
		this->_pivot = std::make_pair(6, 0);
		this->_color = YELLOW;
		break;
	case S:
		this->_pivot = std::make_pair(5, 0);
		this->_color = GREY;
		break;
	case T:
		this->_pivot = std::make_pair(5, -1);
		this->_color = PURPLE;
		break;
	case Z:
		this->_pivot = std::make_pair(5, 0);
		this->_color = RED;
		break;
	default:
		this->_pivot = std::make_pair(0, 0);
		this->_color = WHITE;
		break;
	}


	for(auto p : pos) {
		Block b(p.first, p.second, this->_color, 20);
		this->_blocks.push_back(b);
	}

}

Tetromino::~Tetromino() {

}

void Tetromino::render(SDL_Renderer *renderer, Grille *grid, bool outline) {
	for(auto block : this->_blocks) {
		block.render(renderer, grid);
	}
}

bool Tetromino::ableMove(Direction d, Grille *g) {

	bool can_move = g->moveTetromino(*this, d);
	if(can_move) {
		this->move(d);
	}
	else {
 		if(d == Down) {
			this->move_off = true;
		}
	}
	return can_move;
}

void Tetromino::rotate(Grille *g) {
	if(this->_shape != O) {
		auto possible_new = Tetromino(this->_shape);
		bool can_rotate = true;
		for(int i = 0; i < this->_blocks.size(); i++) {
			auto block_pos = this->_blocks[i].getPosition();
 			auto x_old = block_pos.first - this->_pivot.first;
			auto y_old = block_pos.second - this->_pivot.second;
 			auto x_new = -y_old + this->_pivot.first;
			auto y_new = x_old + this->_pivot.second;
			possible_new.blocks()[i].setPosition(x_new, y_new);
		}
		
		if(!g->moveTetromino(possible_new, Still)) {
			bool to_right = possible_new.ableMove(Right, g);
			bool to_left = true;
			if(!to_right) {
				to_left = possible_new.ableMove(Left, g);
			}
			if(!to_left) {
				can_rotate = false;
			}
		}
		if(can_rotate) {
			std::pair<int8_t, int8_t> pos;
			for(int i = 0; i < possible_new.blocks().size(); i++) {
				pos = possible_new.blocks()[i].getPosition();
				this->_blocks[i].setPosition(pos.first, pos.second);
			}
		}
	}
}

void Tetromino::translate(int8_t x, int8_t y) {
	// translate each block
	for(int i = 0; i < this->_blocks.size(); i++) {
		this->_blocks[i].translate(x, y);
	}
}

void Tetromino::move(Direction d) {
	std::pair<int8_t, int8_t> offset = std::make_pair(0, 0);
	switch(d) {
	case Right:
		offset.first = 1;
		break;
	case Left:
		offset.first = -1;
		break;
	case Down:
		offset.second = 1;
		break;
	default:
		break;
	}
	for(int i = 0; i < this->_blocks.size(); i++)
		this->_blocks[i].translate(offset.first, offset.second);
	this->_pivot.first += offset.first;
	this->_pivot.second += offset.second;
}

bool Tetromino::getState() {
	return this->move_off;
}

std::vector<Block> &Tetromino::blocks() {
	return this->_blocks;
}

Color &Tetromino::color() {
	return this->_color;
}

TetrominoShape Tetromino::shape() const {
	return this->_shape;
}
