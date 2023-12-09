#include "consumables.hpp"

HealingPotion* genPotion(Renderer& r, int level) {
    int healing = 100 + 10 * level;
    HealingPotion* h = NULL;
    h = new HealingPotion("random potion", 10, healing);
    h->texture_ = r.loadTexture("./assets/healing-potion.png");
    return h;
}
