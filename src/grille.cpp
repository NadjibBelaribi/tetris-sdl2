#include "grille.hpp"
#include "utils.hpp"
#include "block.hpp"

Grille::Grille(uint8_t w, uint8_t h, uint8_t b, uint8_t index)
{
    this->_width = w;
    this->_height = h;
    this->_border = b;
    this->index_grille = index;
    uint8_t lig = h + b;
    uint8_t col = w + 2 * b;

    this->map = std::vector<std::vector<Color>>(lig, std::vector<Color>(col));
    this->setMap();
}

Grille::~Grille()
{
}

void Grille::render(SDL_Renderer *renderer)
{
    Block b(20);
    for (int y = 0; y < this->map.size(); y++)
    {
        for (int x = 0; x < this->map[y].size(); x++)
        {
            b.setPosition(x, y);
            b.setColor(this->map[y][x]);
            b.render(renderer, this);
        }
    }
}

// initialise the map matrix 
void Grille::setMap()
{
    for (int y = 0; y < this->map.size(); y++)
    {
        for (int x = 0; x < this->map[y].size(); x++)
        {
            if (x == 0 || x == this->map[y].size() - 1 || y == this->map.size() - 1)
                this->map[y][x] = CYAN;
            else
                this->map[y][x] = BLACK;
        }
    }
}

// Console position 
std::pair<int, int> Grille::map_cord(int8_t x, int8_t y) const
{

    int shiftX = GRID_WIDTH / this->map[0].size() - 7;
    int shiftY = GRID_HEIGHT / this->map.size() - 7;

    return {shiftX * x, shiftY * y};
}

// can we move tetromino down ? 
bool Grille::moveTetromino(Tetromino t, Direction d) {
    for(auto block : t.blocks()) {
        std::pair<uint8_t, uint8_t> offset = {0,0} ;
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

void Grille::setColor(Tetromino t)
{
    for (auto block : t.blocks())
    {
        auto pos = block.getPosition();
        if (pos.second >= 0)
            this->map[pos.second][pos.first] = t.color();
    }
}

// Check if a map's line is empty from Black default color
uint32_t Grille::isTetris()
{
    uint32_t points = 0;
    for (int i = this->map.size() - 2; i >= 0; i--)
    {
        auto tetris = true;
        for (auto color : this->map[i])
        {
            if (color == BLACK)
            {
                tetris = false;
                break;
            }
        }
        if (tetris)
        {
            points += 10;
            if (mode == DUO)
                hand = (hand + 1) % 2;
            this->updateMap(i++);
        }
    }
    return points;
}

void Grille::updateMap(uint8_t rowIndex)
{
    this->map[0] = std::vector<Color>(this->_width + 2 * this->_border);
    this->map[0][0] = CYAN;
    this->map[0][this->map[0].size() - 1] = CYAN;

    // overwrite the tetris line
    for (uint8_t i = rowIndex; i > 0; i--)
            this->map[i] = this->map[i - 1];

}
