#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include "renderer.hpp"
#include "input.hpp"
#include "player.hpp"

class Game {
    
public:
    Room *room_;
    bool running_;
    Input input_;

    Player player_;

    Game();
    void movePlayer();
    void parseInput();
    int tick();

};


#endif
