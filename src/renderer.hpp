#ifndef RENDERER
#define RENDERER

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


class Renderer {
public:

    //! Create renderer. Takes in window width and height and flags
    Renderer(int, int, uint32_t, uint32_t);
    //! initializes SDL
    void initSDL();
    void prepareScene();
    void presentScene();
    //! Loads a texture into memory. Takes path to texture file
    SDL_Texture* loadTexture(const char*);
    //! Draws a texture on the screen
    void drawTexture(SDL_Texture*, int, int, double, SDL_RendererFlip);
    //! Deinitializes SDL
    void destroy();
    void set_flags(uint32_t, uint32_t);
    int getWinWidth();
    int getWinHeight();
    void draw_text(const char* str, int x, int y, SDL_Color = {255,255,255});
    TTF_Font* GetFont();
    //! Renders text on the screen
    void renderText(SDL_Surface* text, int x, int y);
    SDL_Surface* InitText(char* str);
    //! Plays back a sound
    void playSound(Mix_Chunk*, int);
    //! Loads a sound into memory. Takes path to sound file
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

