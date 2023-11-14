#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include "entity.hpp"
#include "input.hpp"
#include "player.hpp"
#include "room.hpp"
#include "renderer.hpp"

class Game {

public:
    Room *room_;
    bool running_;
    Input input_;
    int x_offset_;
    int y_offset_;

    Player player_;

    Game();
    void movePlayer(InputState s);
    void parseInput();
    int tick();
    void render(Renderer&);
    void calcOffset(Coordinate);

};


#endif

