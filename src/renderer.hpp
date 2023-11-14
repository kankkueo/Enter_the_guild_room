#ifndef RENDERER
#define RENDERER

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>



class Renderer {
public:

    Renderer(int width, int height, uint32_t r_flags, uint32_t w_flags);
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

    int width_;
    int height_;

};


#endif

