#include "SDL2/SDL.h"

struct SDL_Deleter
{
    void operator()(SDL_Window *w) const
    {
        SDL_DestroyWindow(w);
    }
    void operator()(SDL_Renderer *r) const
    {
        SDL_DestroyRenderer(r);
    }
};

int main(int argc, char *argv[])
{

    SDL_Window *wind = NULL;
    SDL_Renderer *rend = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    wind = SDL_CreateWindow("Tetris_NH", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!wind)
    {
        SDL_Log("Unable to initialize Window: %s", SDL_GetError());
        exit(1);
    }

    rend = SDL_CreateRenderer(wind, -1, 0);
    if (!rend)
    {
        SDL_Log("Unable to initialize renderer: %s", SDL_GetError());
        exit(1);
    }

    std::unique_ptr<SDL_Window, SDL_Deleter> window = std::unique_ptr<SDL_Window, SDL_Deleter>(wind);
    std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>(rend);

    return 0;
}