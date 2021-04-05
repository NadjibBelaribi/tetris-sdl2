#ifndef _TETRIS_H_
#define _TETRIS_H_

class Tetris;

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <random>
#include "grille.hpp"
#include "tetromino.hpp"


class Tetris
{
public:
	Tetris(uint8_t);
	~Tetris();
	void update();
	void render(SDL_Renderer *);
	bool isFinished();
	std::unique_ptr<Tetromino> currTetromino;
    int index_grille ;
private:
	bool end;

	std::unique_ptr<Grille> grille;
	static Uint32 handleProgress(Uint32, void *);
	SDL_TimerID chrono;
	std::unique_ptr<Tetromino> nextShape;
	void exchangeTetromino();
	void sendNext();
	void tomberTetromino();
	void handleText(SDL_Renderer *);
	uint32_t score;
	TTF_Font *text;
};

#endif
