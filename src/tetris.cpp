
#include "tetris.hpp"

Tetris::Tetris(uint8_t index)  {
	this->end = false;
    this->index_grille = index;
	this->score = 0;
     timePassed = 0 ;
     this->grille = std::unique_ptr<Grille>(new Grille(10, 20, 1, this->index_grille));
    this->chrono = SDL_AddTimer(1000, this->handleProgress, this);
	srand(time(NULL));
	this->currTetromino = std::unique_ptr<Tetromino>(new Tetromino);
	this->nextTetromino = std::unique_ptr<Tetromino>(new Tetromino);
	this->sendNext();

}

Tetris::~Tetris() {
 }

void Tetris::handleInput() {
	SDL_Event e;
 	while(SDL_PollEvent(&e) && hand == this->index_grille) {
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


bool Tetris::isFinished() {
	return this->end;
}

void Tetris::exchangeTetromino() {
	this->grille->setColor(*this->currTetromino);
	std::pair<int8_t, int8_t> offset = std::make_pair(-9, -3);
	switch(this->nextTetromino->shape()) {
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
	this->nextTetromino->translate(offset.first, offset.second);
	this->currTetromino.swap(this->nextTetromino);
	if(!this->currTetromino->ableMove(Down, this->grille.get()))
    {
	    this->end = true;
        hand = (hand + 1) % 2 ;
        if (mode == SOLO ) SDL_RemoveTimer(this->chrono);
    }
	this->score += this->grille->isTetris() * this->timePassed / 2;
 	this->nextTetromino = std::unique_ptr<Tetromino>(new Tetromino);
	this->sendNext();
}

uint32_t Tetris::getScore(){
    return this->score ;
}

void Tetris::sendNext() {
	std::pair<int8_t, int8_t> offset = std::make_pair(9, 3);
	switch(this->nextTetromino->shape()) {
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
	this->nextTetromino->translate(offset.first, offset.second);
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


  	surfaceMessage = TTF_RenderText_Solid(app.font, "Next", White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	if(this->index_grille == 0)
		if (mode == SOLO ) Message_rect.x = X_GRILLE_CENTERED + 300;
		else Message_rect.x = X_GRILLE_1 + 290;
	else 
		Message_rect.x = X_GRILLE_2 + 290;

	Message_rect.y = Y_GRILLE - 30;
	Message_rect.w = 90;
	Message_rect.h = 50;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

 	surfaceMessage = TTF_RenderText_Solid(app.font, "Score", White);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	Message_rect.y += 200;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	char temp[256];
	snprintf(temp, 255, "%d", this->score);
 	surfaceMessage = TTF_RenderText_Solid(app.font, temp, White);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	Message_rect.y += 50;
	Message_rect.x += 30;
	Message_rect.h -= 5;
	Message_rect.w = 30;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    snprintf(temp, 255, "Player %d", this->index_grille + 1);
    surfaceMessage = TTF_RenderText_Solid(app.font, temp, White);
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    Message_rect.y += 280;
    Message_rect.x -= 245;
    Message_rect.h = 30;
    Message_rect.w = 100;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

}

Uint32 Tetris::handleProgress(uint32_t interval, void *param) {
	auto t = (Tetris *) param;
    t->timePassed ++ ;
    if (hand == t->index_grille ||  mode == SOLO )
    {
        t->currTetromino->ableMove(Down, t->grille.get());
        if(t->currTetromino->getState()) {
            t->exchangeTetromino();
        }

        return interval ;
    }
    return interval  ;
}
