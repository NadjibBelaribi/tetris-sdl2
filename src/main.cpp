#include "tetris.hpp"
#include <SDL_image.h>

 int hand = 0 ;
GAME_MODE mode = NONE;
bool replay = false ;
struct App app ;

void HomeScreen(SDL_Renderer *r,SDL_Texture *tetris,SDL_Event event){
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
}
void GameScreen(SDL_Renderer *r,SDL_Texture *bg,SDL_Texture *box){
    SDL_Rect rect ;
    rect.h = 200 ;
    rect.w = 150 ;
    rect.x = 600 ;
    rect.y = 50 ;

    switch (mode) {
        case SOLO :
        {
            Tetris *t = new Tetris(0);
            std::unique_ptr<Tetris> game = std::unique_ptr<Tetris>(t);
            while (!game->isFinished())
            {
                SDL_RenderClear(r);
                SDL_RenderCopy(r, bg, NULL, NULL);
               // SDL_RenderCopy(r, box, NULL, &rect);

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
            Tetris *game = new Tetris(0);
            Tetris *game1 = new Tetris(1);

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
}

bool gameOverScreen(SDL_Renderer *r , SDL_Texture *gover,SDL_Event event){
    bool chosen = false ;
    //  HANDLE MODE CHOICE
    while(SDL_PollEvent(&event) || !chosen ) {
        SDL_RenderCopy(r, gover, NULL, NULL);
        SDL_RenderPresent(r);
        switch(event.type) {
            case SDL_QUIT:
                exit(1) ;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_y:
                         chosen = true;
                         replay = true;
                        break;
                    case SDLK_n:
                         chosen = true;
                         replay = false ;
                        break;
                }
                break;

        }
    }
    return replay ;
}

void initSDL(){
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    app.w = SDL_CreateWindow("Tetris",
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             WINDOW_WIDTH,
                             WINDOW_HEIGHT,
                             0);
    if (!app.w)
    {
        SDL_Log("Unable to initialize Window: %s", SDL_GetError());
        exit(1);
    }

    app.r = SDL_CreateRenderer(app.w, -1, 0);
    if (!app.r)
    {
        SDL_Log("Unable to initialize renderer: %s", SDL_GetError());
        exit(1);
    }
}

int main()
{

    SDL_Texture *tetris = NULL;
    SDL_Texture *bg = NULL;
    SDL_Texture *gover = NULL;
    SDL_Texture *box = NULL;

    SDL_Event event;
    bool play = true ;


    initSDL() ;
    tetris = IMG_LoadTexture(app.r, "../assets/tetris.png");
    bg = IMG_LoadTexture(app.r, "../assets/bg.png");
    gover = IMG_LoadTexture(app.r, "../assets/game-over.png");
    box = IMG_LoadTexture(app.r, "../assets/box.png");

    while (play){
        hand = 0 ;
        mode = NONE ;
        replay = false ;
        HomeScreen(app.r,tetris,event) ;
        GameScreen(app.r,bg,box) ;
        play = gameOverScreen(app.r,gover,event) ;

    }

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(tetris);
    SDL_DestroyTexture(gover);
    IMG_Quit();

    SDL_DestroyRenderer(app.r);
    SDL_DestroyWindow(app.w);
    SDL_Quit();

    return 0;
}

