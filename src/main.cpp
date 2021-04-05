 #include "tetris.hpp"

struct SDL_Deleter {
    void operator()(SDL_Window *w) const {
        SDL_DestroyWindow(w);
    }
    void operator()(SDL_Renderer *r) const {
        SDL_DestroyRenderer(r);
    }
};

int main(int argc, char *argv[])
{

    Tetris *t = new Tetris();

    SDL_Window *w = NULL;
    SDL_Renderer *r = NULL;
    int wflags = 0, rflags = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }

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

    std::unique_ptr<SDL_Window, SDL_Deleter> _window =  std::unique_ptr<SDL_Window, SDL_Deleter>(w);
    std::unique_ptr<SDL_Renderer, SDL_Deleter> _renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>(r);
    std::unique_ptr<Tetris> _gs= std::unique_ptr<Tetris>(t);

    while (!_gs->has_ended())
    {
        _gs->update();

        SDL_RenderClear(_renderer.get());

        _gs->render(_renderer.get());

        SDL_RenderPresent(_renderer.get());
    }

    return 0;
}
