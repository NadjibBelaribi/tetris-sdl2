#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_image.h>

 // WINDOWS SIZES
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;

// GRIDS POSITIONS
const int X_GRILLE_1 = 50;
const int Y_GRILLE = 60;
const int X_GRILLE_CENTERED = 300 ;
const int X_GRILLE_2 = 450;

// GRID SIZE
const int GRID_WIDTH = 360;
const int GRID_HEIGHT = 630;

// GAME MODES
typedef enum {
	SOLO,
	DUO,
	NONE
} GAME_MODE;

// TETROMINOS SHAPES
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

// App frame
 struct App {
    SDL_Window *w ;
    SDL_Renderer *r ;
    TTF_Font *font;

 };

// INITIAL TETROMINOS POSITIONS
const std::vector< std::vector< std::pair<int8_t, int8_t>>> TETRO_POS {

	{{5, 0},{5, -1},{5, -2},{5, -3}},
	{{5, 0},{6, 0},{6, -1},{6, -2}},
	{{5, 0},{6, 0},{5, -1},{5, -2}},
	{{5, 0},{6, 0},{5, -1},{6, -1}},
	{{4, 0},{5, 0},{5, -1},{6, -1}},
	{{4, -1},{5, -1},{6, -1},{5, 0}},
	{{4, -1},{5, -1},{5, 0},{6, 0}},
};

// POSSIBLE MANIPULATIONS
typedef enum {
	Right,
	Left,
	Down,
	Hold
} Direction;



#endif