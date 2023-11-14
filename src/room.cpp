#include "room.hpp"

Room::Room(std::string name, int width, int height, SDL_Texture *texture)
    : name_(name), width_(width), height_(height), texture_(texture) { }

