#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "tetris.hpp"
#include "block.hpp"
#include "color.hpp"

Tetris::Tetris(uint8_t index)  {
	this->end = false;
    this->index_grille = index;

    this->grille = std::unique_ptr<Grille>(new Grille(10, 20, 1, this->index_grille));
	 this->chrono = SDL_AddTimer(1000, this->handleProgress, this);
	srand(time(NULL));
	this->currTetromino =
		std::unique_ptr<Tetromino>(new Tetromino);
	this->nextShape =
		std::unique_ptr<Tetromino>(new Tetromino);
	this->sendNext();
	this->score = 0;

	TTF_Init();
	this->text = TTF_OpenFont("../assets/font.ttf", 18);
	if(!this->text) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(1);
	}

}

Tetris::~Tetris() {
	TTF_Quit();
}

void Tetris::handleInput() {
	SDL_Event e;
 	while(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			this->end = true;
			break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym) {
			case SDLK_RIGHT:
				this->currTetromino->
					ableMove(Right, this->grille.get());
 				break;
			case SDLK_LEFT:
				this->currTetromino->
					ableMove(Left, this->grille.get());
 				break;
			case SDLK_DOWN:
				this->currTetromino->
					ableMove(Down, this->grille.get());
 				break;
			case SDLK_UP:
				this->currTetromino->rotate(this->grille.get());
 				break;
			case SDLK_SPACE:
				this->tomberTetromino();
				break;
			}
			if(this->currTetromino->getState())
				this->exchangeTetromino();
			break;
		default:
			break;
		}
	}
}

void Tetris::render(SDL_Renderer *renderer) {
	this->grille->render(renderer);
	this->currTetromino->render(renderer, this->grille.get());
	this->nextShape->render(renderer, this->grille.get());
 	this->handleText(renderer);

}

bool Tetris::isFinished() {
	return this->end;
}

void Tetris::exchangeTetromino() {
	this->grille->setColor(*this->currTetromino);
	std::pair<int8_t, int8_t> offset = std::make_pair(-9, -3);
	switch(this->nextShape->shape()) {
	case I:
		offset.second -= 2;
		break;
	case O:
		offset.first += 1;
		break;
	case L:
		offset.second -= 1;
		break;
	case J:
		offset.second -= 1;
		offset.first += 1;
		break;
	default:
		break;
	}
	this->nextShape->translate(offset.first, offset.second);
	this->currTetromino.swap(this->nextShape);
	if(!this->currTetromino->ableMove(Down, this->grille.get()))
		this->end = true;
	this->score += this->grille->isTetris();
 	this->nextShape = std::unique_ptr<Tetromino>(new Tetromino);
	this->sendNext();
}

void Tetris::sendNext() {
	std::pair<int8_t, int8_t> offset = std::make_pair(9, 3);
	switch(this->nextShape->shape()) {
	case I:
		offset.second += 2;
		break;
	case O:
		offset.first -= 1;
		break;
	case L:
		offset.second += 1;
		break;
	case J:
		offset.second += 1;
		offset.first -= 1;
		break;
	default:
		break;
	}
	this->nextShape->translate(offset.first, offset.second);
}


void Tetris::tomberTetromino() {
	Grille *g = this->grille.get();
	while(this->currTetromino->ableMove(Down, g));
	this->exchangeTetromino();
}


void Tetris::handleText(SDL_Renderer *renderer) {
	SDL_Color White = {255, 255, 255};
	SDL_Surface *surfaceMessage = NULL;
	SDL_Rect Message_rect;

 	surfaceMessage = TTF_RenderText_Solid(this->text, "Next", White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	if(this->index_grille == 1) 
		Message_rect.x = X_GRILLE_1 + 300;
	else 
		Message_rect.x = X_GRILLE_2 + 300;

	Message_rect.y = Y_GRILLE_1;
	Message_rect.w = 90;
	Message_rect.h = 50;

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

 	surfaceMessage = TTF_RenderText_Solid(this->text, "Score", White);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	Message_rect.y += 200;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	char points[256];
	snprintf(points, 255, "%d", this->score);

 	surfaceMessage = TTF_RenderText_Solid(this->text, points, White);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	Message_rect.y += 50;
	Message_rect.x += 30;
	Message_rect.h -= 5;
	Message_rect.w = 30;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

Uint32 Tetris::handleProgress(Uint32 interval, void *param) {
	auto t = (Tetris *) param;
	t->currTetromino->ableMove(Down, t->grille.get());
	if(t->currTetromino->getState()) {
		t->exchangeTetromino();
	}

	return interval;
}
