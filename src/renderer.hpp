#ifndef RENDERER
#define RENDERER

#include <SDL2/SDL.h>

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720


class Renderer {


public:

    Renderer();
    void initSDL();
    void prepareScene();
    void presentScene();
    SDL_Texture* loadTexture(const char*);
    void drawTexture(SDL_Texture*, int, int);
    void destroy();


private:

    SDL_Renderer* renderer_;
	SDL_Window* window_;

};

#endif

void sdltest();  // REMOVE WHEN NOT NECESSARY
