#ifndef ROOM
#define ROOM

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include "monster.hpp"
#include "renderer.hpp"


class Room {
public:
    Room(const std::string&, int, int, SDL_Texture*, SDL_Texture*);
    ~Room();

    void addRandomMonsters(Renderer&, int, int);
    void addAdvanceDoor();
    
    std::string name_;
    SDL_Texture *texture_;
    SDL_Texture *advanceDoor_;
    int advanceDoorX_;
    int advanceDoorY_;
    int width_;
    int height_;
    std::list<Monster*> monsters_;

};

typedef struct {
    std::string name;
    std::string texture_location;
    int width;
    int height;
    int mobs_min;
    int mobs_max;
} RoomTemplate;


Room* genRoom(Renderer&, int);

#endif
