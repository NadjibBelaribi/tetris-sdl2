#ifndef _UTILS_H_
#define _UTILS_H_


// WINDOWS SIZES
const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 630;

const int GRID_WIDTH = 360;
const int GRID_HEIGHT = 630;

const int INFO_BEGIN_X = 360;
const int INFO_BEGIN_Y = 0;

typedef enum {
	I = 0,
	J,
	L,
	O,
	S,
	T,
	Z,
	NSHAPES
} TetrominoShape;

const std::vector< std::vector< std::pair<int8_t, int8_t> > > POSITIONS {
	// I
	{
		std::make_pair(5, 0),
		std::make_pair(5, -1),
		std::make_pair(5, -2),
		std::make_pair(5, -3)
	},
	// J
	{
		std::make_pair(5, 0),
		std::make_pair(6, 0),
		std::make_pair(6, -1),
		std::make_pair(6, -2)
	},
	// L
	{
		std::make_pair(5, 0),
		std::make_pair(6, 0),
		std::make_pair(5, -1),
		std::make_pair(5, -2)
	},
	// O
	{
		std::make_pair(5, 0),
		std::make_pair(6, 0),
		std::make_pair(5, -1),
		std::make_pair(6, -1)
	},
	// S
	{
		std::make_pair(4, 0),
		std::make_pair(5, 0),
		std::make_pair(5, -1),
		std::make_pair(6, -1)
	},
	// T
	{
		std::make_pair(4, -1),
		std::make_pair(5, -1),
		std::make_pair(6, -1),
		std::make_pair(5, 0)
	},
	// Z
	{
		std::make_pair(4, -1),
		std::make_pair(5, -1),
		std::make_pair(5, 0),
		std::make_pair(6, 0)
	},
};

typedef enum {
	Right,
	Left,
	Down,
	Hold
} Direction;


#endif