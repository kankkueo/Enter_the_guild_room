#include <SDL2/SDL.h>

/*
Class for representing all kinds of entities in the game
*/ 
class Entity {

public:
    int x;
    int y;
    SDL_Texture *texture;
};
