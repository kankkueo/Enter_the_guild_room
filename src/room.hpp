#ifndef ROOM
#define ROOM

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include "monster.hpp"


class Room {
public:
    Room(std::string name, int width, int height, SDL_Texture *texture, SDL_Texture *advanceDoor, int advanceDoorX, int advanceDoorY);

    void addMonster();
    
    std::string name_;
    SDL_Texture *texture_;
    SDL_Texture *advanceDoor_;
    int advanceDoorX_;
    int advanceDoorY_;
    int width_;
    int height_;
    std::list<Monster> monsters_;


};

#endif
