#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include "renderer.hpp"
#include "input.hpp"


class Entity {

public:
    int x_;
    int y_;
    int speed_;

    SDL_Texture *texture_;

    Entity() {
        x_ = 0;
        y_ = 0;
        speed_ = 10;
    }

};



class Game {
    
public:
    bool running_;
    Input input_;

    Entity entity1_;

    Game();
    void movePlayer();
    void parseInput();
    int tick();

    void playerMove(InputState); //placeholder

};


#endif
