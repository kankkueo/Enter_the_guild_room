#ifndef CONSUMABLES
#define CONSUMABLES

#include <string>
#include "item.hpp"

class HealingPotion: public Item {
public:
    HealingPotion(std::string name, int size, int healing) : Item(name, size) {
        healing_ = healing;
    }
    int getHealing() {
        return healing_;
    }
    
private:
    int healing_;
};

#endif
