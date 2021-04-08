#include "grille.hpp"
#include "utils.hpp"
#include "block.hpp"

Grille::Grille(uint8_t w, uint8_t h, uint8_t b,uint8_t index) {
	this->_width = w;
	this->_height = h;
	this->_border = b;
    this->index_grille = index;
    this->map = std::vector< std::vector<Color> >
		(h + this->_border,
		 std::vector<Color>(w + 2*this->_border));
	this->setMap();
}

Grille::~Grille() {

}

void Grille::render(SDL_Renderer *renderer) {
	Block b(20);
	for(int y = 0; y < this->map.size(); y++) {
		for(int x = 0; x < this->map[y].size(); x++) {
			b.setPosition(x, y);
			b.setColor(this->map[y][x]);
			b.render(renderer, this);
		}
	}
}

void Grille::setMap() {
	for(int y = 0; y < this->map.size(); y++) {
		for(int x = 0; x < this->map[y].size(); x++) {
			if(x == 0 ||
			   x == this->map[y].size() - 1 ||
			   y == this->map.size() - 1)
				this->map[y][x] = CYAN;
			else
				this->map[y][x] = BLACK;
		}
	}
}

std::pair<int, int> Grille::map_cord(int8_t x, int8_t y) const {

	int w_step = GRID_WIDTH / this->map[0].size() - 7;
	w_step =  w_step * x;

	int h_step = GRID_HEIGHT / this->map.size() - 7;
	h_step = h_step * y;

	return std::make_pair(w_step,h_step);
}


uint8_t Grille::width() const {
	return this->_width;
}

uint8_t Grille::height() const {
	return this->_height;
}

uint8_t Grille::border() const {
	return this->_border;
}

bool Grille::moveTetromino(Tetromino t, Direction d) {
	for(auto block : t.blocks()) {
		std::pair<uint8_t, uint8_t> offset = std::make_pair(0, 0);
		auto pos = block.getPosition();
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
		pos.first += offset.first;
		pos.second += offset.second;

		if(pos.second > this->_height ||
		   pos.first > this->_width ||
		   (pos.second > 0 &&
			this->map[pos.second][pos.first] != BLACK)) {
			return false;
		}
	}
	return true;
}

void Grille::setColor(Tetromino t) {
	auto color = t.color();
	for(auto block : t.blocks()) {
		auto pos = block.getPosition();
		auto x = pos.first;
		auto y = pos.second;
		if(y >= 0)
			this->map[y][x] = color;
	}
}

uint32_t Grille::isTetris() {
	uint32_t points = 0;
	bool tetris;
	// map.size() - 2 to exclude bottom border row
	for(int i = this->map.size() - 2 ; i >= 0; i--) {
		tetris = true;
		for(auto color : this->map[i]) {
			if(color == BLACK) {
				tetris = false;
				break;
			}
		}
		if(tetris) {
			printf("TETRIS line %d\n", i);
  			points += 100;
			printf("Updating board...\n");
			this->updateMap(i);
			i++;
		}
	}
	return points;
}

void Grille::updateMap(uint8_t row) {
	for(uint8_t i = row; i > 0; i--) {
		this->map[i] = this->map[i-1];
	}
 	this->map[0] = std::vector<Color>(this->_width + 2*this->_border);
	this->map[0][0] = GREY;
	this->map[0][this->map[0].size()-1] = GREY;
 }
