#ifndef ENTITY 
#define ENTITY

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct {
    int x;
    int y;
} Coordinate;


typedef struct {
    Mix_Chunk* attack_;
    Mix_Chunk* hit_;
    Mix_Chunk* death_;
    Mix_Chunk* taunt_;
} SoundSet;

/*!
 * Base class for entities in the game
 */

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
    Coordinate newPos();
    Coordinate center();
    Coordinate newCenter();
    bool collidesWith(Entity&);

};


#endif
