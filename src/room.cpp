#include "room.hpp"

Room::Room(std::string name, int width, int height, SDL_Texture *texture, SDL_Texture *advanceDoor)
    : name_(name), width_(width), height_(height), texture_(texture), advanceDoor_(advanceDoor) {
        monsters_ = std::list<Monster*>();
        advanceDoorX_ = rand() % (width - 80);
        advanceDoorY_ = rand() % (height - 80);
 }

void Room::addMonster() {
    MeleeMob* monster1 = new MeleeMob(50, 5, 4, 300, 300, 60, 90); // randomize these?
    RangedMob* monster2 = new RangedMob(50, 5, 4, 600, 600, 60, 90); // randomize these?
    monsters_.push_back(monster1);
    monsters_.push_back(monster2);
}
