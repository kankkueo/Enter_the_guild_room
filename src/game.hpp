#include <SDL2/SDL.h>

class Game {
    
public:
    SDL_Renderer *renderer;
	SDL_Window *window;
	int up;
	int down;
	int left;
	int right;
};
