#include "tetromino.hpp"

Tetromino::Tetromino()
{
	TetrominoShape shape = (TetrominoShape)(rand() % NSHAPES);
	this->setTetromino(shape);
}

Tetromino::Tetromino(TetrominoShape shape)
{
	this->setTetromino(shape);
}

void Tetromino::setTetromino(TetrominoShape shape)
{
	auto pos = TETRO_POS[shape];
	this->move_off = false;
	this->_shape = shape;

	switch (this->_shape)
	{
	case I:
		this->_pivot = {5, -1};
		this->_color = GREEN;
		break;
	case J:
		this->_pivot = {6, 0};
		this->_color = BLUE;
		break;
	case L:
		this->_pivot = {5, 0};
		this->_color = ORANGE;
		break;
	case O:
		this->_pivot = {6, 0};
		this->_color = YELLOW;
		break;
	case S:
		this->_pivot = {5, 0};
		this->_color = GREY;
		break;
	case T:
		this->_pivot = {5, -1};
		this->_color = PURPLE;
		break;
	case Z:
		this->_pivot = {5, 0};
		this->_color = RED;
		break;
	default:
		this->_pivot = {0, 0};
		this->_color = WHITE;
		break;
	}

	for (auto p : pos)
	{
		Block b(p.first, p.second, this->_color, 20);
		this->_blocks.push_back(b);
	}
}

Tetromino::~Tetromino()
{
}

void Tetromino::render(SDL_Renderer *renderer, Grille *grid) const
{
	for (auto block : this->_blocks)
	{
		block.render(renderer, grid);
	}
}

bool Tetromino::ableMove(Direction d, Grille *g)
{

	if (!g->moveTetromino(*this, d) ) {
        if (d == Down) {
            this->move_off = true;
        }
        return false;

    }
	else {
        this->move(d);
        return true;
    }
}

void Tetromino::rotate(Grille *g)
{
	if (this->_shape != O)
	{
		auto newTetromino = Tetromino(this->_shape);
		bool rotate = true;

		// calculate the new tetromino positions
		for (int i = 0; i < this->_blocks.size(); i++)
		{
			auto x_new = this->_pivot.first + this->_pivot.second - this->_blocks[i].getPosition().second  ;
			auto y_new = this->_blocks[i].getPosition().first + this->_pivot.second - this->_pivot.first;

            newTetromino.blocks()[i].setPosition(x_new, y_new);
		}

		// test if the new can be move
		if (!g->moveTetromino(newTetromino, Hold))
		{
 			if (!newTetromino.ableMove(Right, g) || !newTetromino.ableMove(Left, g))
				rotate = false;
		}

		// set the new tetromino official position
		if (rotate)
		{
 			for (int i = 0; i < newTetromino.blocks().size(); i++){
				auto pos = newTetromino.blocks()[i].getPosition();
				this->_blocks[i].setPosition(pos.first, pos.second);
			}
		}
	}
}

void Tetromino::translate(int8_t x, int8_t y)
{
	// translate each block
	for (int i = 0; i < this->_blocks.size(); i++)
	{
		this->_blocks[i].translate(x, y);
	}
}

void Tetromino::move(Direction d)
{
	int8_t x = 0, y = 0 ;
	switch (d)
	{
	case Right:
		x = 1;
		break;
	case Left:
		x = -1;
		break;
	case Down:
		y = 1;
		break;
	default:
		break;
	}
	for (int i = 0; i < this->_blocks.size(); i++)
		this->_blocks[i].translate(x,y);

    this->_pivot.first += x;
    this->_pivot.second += y;
}

bool Tetromino::getState()
{
	return this->move_off;
}

std::vector<Block> &Tetromino::blocks()
{
	return this->_blocks;
}

Color &Tetromino::color()
{
	return this->_color;
}

TetrominoShape Tetromino::shape() const
{
	return this->_shape;
}
