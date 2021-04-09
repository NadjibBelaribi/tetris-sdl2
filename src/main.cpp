#include "tetris.hpp"
#include <SDL_image.h>

int hand = 0 ;
GAME_MODE mode = NONE;

int main(int argc, char *argv[])
{
    SDL_Window *w = NULL;
    SDL_Renderer *r = NULL;
    int wflags = 0, rflags = 0;
    SDL_Texture *tetris = NULL;
    SDL_Texture *bg = NULL;

    SDL_Event event;

    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    w = SDL_CreateWindow("Tetris",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         WINDOW_WIDTH,
                         WINDOW_HEIGHT,
                         wflags);
    if (!w)
    {
        SDL_Log("Unable to initialize Window: %s", SDL_GetError());
        exit(1);
    }

    r = SDL_CreateRenderer(w, -1, rflags);
    if (!r)
    {
        SDL_Log("Unable to initialize renderer: %s", SDL_GetError());
        exit(1);
    }

    tetris = IMG_LoadTexture(r, "../assets/tetris.png");
    bg = IMG_LoadTexture(r, "../assets/bg.png");
    bool chosen = false ;

    //  HANDLE MODE CHOICE
    while(SDL_PollEvent(&event) || !chosen ) {
            SDL_RenderCopy(r, tetris, NULL, NULL);

        SDL_RenderPresent(r);
            switch(event.type) {
                case SDL_QUIT:
                    exit(1) ;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_s:
                            mode = SOLO ;
                            chosen = true;
                            break;
                        case SDLK_d:
                            mode = DUO ;
                            chosen = true;
                            break;
                    }
                    break;

            }

        }


    switch (mode) {
        case SOLO :
              {
                  Tetris *t = new Tetris(0);
                  std::unique_ptr<Tetris> game = std::unique_ptr<Tetris>(t);
                  while (!game->isFinished())
                  {
                      SDL_RenderClear(r);
                      SDL_RenderCopy(r, bg, NULL, NULL);
                      game->handleInput() ;
                      game->grille->render(r);
                      if (hand == 0 && !game->isFinished()) {

                          game->currTetromino->render(r, game->grille.get());
                          game->nextShape->render(r, game->grille.get());

                      }
                      game->handleText(r);
                      SDL_RenderPresent(r);
                  }

              }
            break;
        case DUO : {
            Tetris *t = new Tetris(0);
            Tetris *t1 = new Tetris(1);

            std::unique_ptr<Tetris> game = std::unique_ptr<Tetris>(t);
            std::unique_ptr<Tetris> game1 = std::unique_ptr<Tetris>(t1);


            while (!game->isFinished() || !game1->isFinished()) {
                SDL_RenderClear(r);

                if (hand == 0 && !game->isFinished()) game->handleInput();
                if (hand == 1 && !game1->isFinished()) game1->handleInput();
                SDL_RenderCopy(r, bg, NULL, NULL);

                game->grille->render(r);
                if (hand == 0 && !game->isFinished()) {

                    game->currTetromino->render(r, game->grille.get());
                    game->nextShape->render(r, game->grille.get());

                }
                game->handleText(r);

                game1->grille->render(r);
                if (hand == 1 && !game1->isFinished()) {
                    game1->currTetromino->render(r, game1->grille.get());
                    game1->nextShape->render(r, game1->grille.get());
                }
                game1->handleText(r);

                SDL_RenderPresent(r);
            }
        }
            break;
        default:
            break;
     }


    SDL_DestroyTexture(bg);
    IMG_Quit();
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();

    return 0;
}

