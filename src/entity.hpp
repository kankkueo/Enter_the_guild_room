#ifndef ENTITY 
#define ENTITY

#include <SDL2/SDL.h>

class Entity {

public:
    int x_;
    int y_;
    int speed_;
    float direction_;
    SDL_Texture *texture_;

    Entity();
    void move();
};


#endif
