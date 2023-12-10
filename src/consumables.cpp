#include "consumables.hpp"

std::string HealingPotion::toString() {
    return getName() + " +" + std::to_string(getHealing()) + " hp";
}

HealingPotion* genPotion(Renderer& r, int level) {
    int rand_int = (rand() % (20 - 10 + 1)) + 10;
    int healing = 100 + rand_int * level;
    HealingPotion* h = NULL;
    h = new HealingPotion("healing potion", 10, healing);
    h->texture_ = r.loadTexture("./assets/healing-potion.png");
    return h;
}
