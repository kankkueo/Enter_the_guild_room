#ifndef ENTITY 
#define ENTITY

#include <SDL2/SDL.h>

class Entity {

public:
    int x_;
    int y_;
    int size_x_;
    int size_y_;
    int speed_;
    float direction_;
    SDL_Texture *texture_;

    Entity(int, int, int, int);
    void move();
};


#endif
