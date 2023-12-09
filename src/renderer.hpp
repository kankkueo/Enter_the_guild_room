#ifndef RENDERER
#define RENDERER

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


class Renderer {
public:

    Renderer(int width, int height, uint32_t r_flags, uint32_t w_flags);
    void initSDL();
    void prepareScene();
    void presentScene();
    SDL_Texture* loadTexture(const char*);
    void drawTexture(SDL_Texture*, int, int, double, SDL_RendererFlip);
    void destroy();
    void set_flags(uint32_t, uint32_t);
    int getWinWidth();
    int getWinHeight();
    void draw_text(const char* str, int x, int y, SDL_Color = {255,255,255});
    TTF_Font* GetFont();
    void renderText(SDL_Surface* text, int x, int y);
    SDL_Surface* InitText(char* str);
    void playSound(Mix_Chunk*, int);
    Mix_Chunk* loadSound(const char*);
    

private:

    SDL_Renderer* renderer_;
	SDL_Window* window_;
    uint32_t renderer_flags_;
    uint32_t window_flags_;
    TTF_Font *font_;

    int width_;
    int height_;

};


#endif

