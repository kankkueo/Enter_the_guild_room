#include "room.hpp"
#include "monster.hpp"

Room::Room(std::string name, int width, int height, SDL_Texture *texture, SDL_Texture *advanceDoor)
    : name_(name), width_(width), height_(height), texture_(texture), advanceDoor_(advanceDoor) {
        monsters_ = std::list<Monster*>();
        advanceDoorX_ = rand() % (width - 80) + 80;
        advanceDoorY_ = rand() % (height - 80) + 80;
}

void Room::addRandomMonsters(Renderer& r, int level, int amount) {
    for (int i = 0; i < amount; i++) {
        monsters_.push_back(genRandomMob(r, level, width_, height_));
    }
}
