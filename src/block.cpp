#include "block.hpp"

Block::Block() {
	this->_position = std::make_pair(10,0);
	this->_color;
	this->_size = 0;
}

Block::Block(int size) {
	this->_position = std::make_pair(10,0);
	this->_color;
	this->_size = size;
}

Block::Block(int8_t x, int8_t y, Color c, int s) {
	this->_position = std::make_pair(x, y);
	this->_color = c;
	this->_size = s;
}

Block::~Block() = default;

std::pair<int8_t, int8_t> Block::position() {
	return this->_position;
}

void Block::setPosition(int8_t x, int8_t y) {
    this->_position.first = x;
    this->_position.second = y;
}

void Block::setColor(Color c) {
    this->_color = c;
}

void Block::translate(int8_t x, int8_t y) {
    this->_position.first += x;
    this->_position.second += y;
}
