#ifndef _TETRIS_H_
#define _TETRIS_H_

class Tetris;

#include <memory>
#include <random>
#include "grille.hpp"
#include "tetromino.hpp"
#include <cstdlib>
#include <cstdio>
#include <ctime>

extern App app;

class Tetris
{
public:
	Tetris(uint8_t);
	~Tetris();
	void handleInput();
	bool isFinished();
	void handleText(SDL_Renderer *);
	uint32_t getScore();

	std::unique_ptr<Tetromino> currTetromino;
	int index_grille;
	std::unique_ptr<Grille> grille;
	std::unique_ptr<Tetromino> nextTetromino;

private:
	bool end;
	SDL_TimerID chrono;
	uint32_t score;

	static Uint32 handleProgress(Uint32, void *);
	void exchangeTetromino();
	void sendNext();
	void tomberTetromino();
};

#endif
