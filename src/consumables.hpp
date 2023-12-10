#ifndef CONSUMABLES
#define CONSUMABLES

#include <string>
#include "item.hpp"
#include "renderer.hpp"

/*! Class for healing potion
 *
 *  - Inherits Item base class
 *  - Potions are dropped by melee monsters
 */

class HealingPotion: public Item {
public:
    HealingPotion(std::string name, int size, int healing) : Item(name, size) {
        healing_ = healing;
    }
    int getHealing() {
        return healing_;
    }
    std::string toString();
    
private:
    int healing_;
};

// Non-member functions
HealingPotion* genPotion(Renderer&, int);

#endif
