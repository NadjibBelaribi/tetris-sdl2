#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <cstdint>

 // WINDOWS SIZES
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;

const int GRID_WIDTH = 360;
const int GRID_HEIGHT = 630;

const int X_GRILLE_1 = 50;
const int Y_GRILLE = 50;
const int X_GRILLE_CENTERED = 300 ;
const int X_GRILLE_2 = 500;

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

 struct App {
    SDL_Window *w ;
    SDL_Renderer *r ;
};

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