#include "room.hpp"

Room::Room(std::string name, int width, int height, SDL_Texture *texture, SDL_Texture *advanceDoor, int advanceDoorX, int advanceDoorY)
    : name_(name), width_(width), height_(height), texture_(texture), advanceDoor_(advanceDoor), advanceDoorX_(advanceDoorX), advanceDoorY_(advanceDoorY) {
        monsters_ = std::list<Monster>();
     }

void Room::addMonster() {
    Monster monster1 = Monster(50, 5, 4, 300, 300, 60, 90); // randomize these?
    Monster monster2 = Monster(50, 5, 4, 600, 600, 60, 90); // randomize these?
    monsters_.push_back(monster1);
    monsters_.push_back(monster2);
}
