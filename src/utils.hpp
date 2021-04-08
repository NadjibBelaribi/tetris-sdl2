#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <cstdint>
#include <SDL2/SDL_image.h>
// WINDOWS SIZES
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 650;

const int GRID_WIDTH = 360;
const int GRID_HEIGHT = 630;

const int X_GRILLE_1 = 100;
const int Y_GRILLE_1 = 0;

const int X_GRILLE_2 = 600;

typedef enum {
	SOLO,
	DUO,
	NONE
} GAME_MODE;

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