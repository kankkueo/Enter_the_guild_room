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
    void set_flags(uint32_t, uint32_t);


private:

    SDL_Renderer* renderer_;
	SDL_Window* window_;
    uint32_t renderer_flags_;
    uint32_t window_flags_;

};






int doInput();







#endif

