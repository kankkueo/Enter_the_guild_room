#include "room.hpp"

Room::Room(std::string name, int width, int height, SDL_Texture *texture, SDL_Texture *advanceDoor)
    : name_(name), width_(width), height_(height), texture_(texture), advanceDoor_(advanceDoor) {
        monsters_ = std::list<Monster*>();
        advanceDoorX_ = rand() % (width - 80);
        advanceDoorY_ = rand() % (height - 80);
 }

void Room::addMonster(Renderer& r) {
    MeleeMob* monster1 = new MeleeMob(50, 5, 4, 600, 600, 60, 90); // randomize these?
    RangedMob* monster2 = new RangedMob(50, 5, 4, 600, 600, 60, 90, new Pistol("mobp", 10, 5, 10, 3)); // randomize these?
    monster2->weapon_->texture_ = r.loadTexture("./assets/gun1.png");
    monster2->weapon_->projectile_texture_ = r.loadTexture("./assets/bulet1.png");
    monsters_.push_back(monster1);
    monsters_.push_back(monster2);
}
