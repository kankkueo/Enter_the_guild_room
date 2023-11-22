#include "room.hpp"

Room::Room(std::string name, int width, int height, SDL_Texture *texture, SDL_Texture *advanceDoor, int advanceDoorX, int advanceDoorY)
    : name_(name), width_(width), height_(height), texture_(texture), advanceDoor_(advanceDoor), advanceDoorX_(advanceDoorX), advanceDoorY_(advanceDoorY) { }

