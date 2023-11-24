#ifndef ROOM
#define ROOM

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include "monster.hpp"


class Room {
public:
    Room(std::string, int, int, SDL_Texture*, SDL_Texture*);

    void addMonster();
    void addAdvanceDoor();
    
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
