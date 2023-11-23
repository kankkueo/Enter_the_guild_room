#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include <list>
#include "entity.hpp"
#include "input.hpp"
#include "player.hpp"
#include "room.hpp"
#include "renderer.hpp"

class Game {

public:
    std::list<Room> rooms_;
    Room *room_;
    Room *room1_;
    bool running_;
    Input input_;
    int x_offset_;
    int y_offset_;


    Player player_;

    Game();
    void movePlayer(InputState s);
    void parseInput();
    int tick(Renderer&);
    void render(Renderer&);
    void calcOffset();
    void changeRoom(Room *r);
    void calcOffset(Renderer&);

};


#endif

