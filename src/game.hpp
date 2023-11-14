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
    float direction_;
    SDL_Texture *texture_;

    Entity();
    void move();
};



class Game {
    
public:
    Room *room_;
    bool running_;
    Input input_;

    Entity entity1_;

    Game();
    void movePlayer();
    void parseInput();
    int tick();

    int playerMove(InputState); //placeholder

};


#endif
