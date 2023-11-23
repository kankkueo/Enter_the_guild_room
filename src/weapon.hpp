#ifndef WEAPON
#define WEAPON

#include "item.hpp"
#include <string>

class Weapon: public Item {

public:
    Weapon(std::string name, int size, int dmg) 
    : Item(name, size) {
            dmg_ = dmg;
        }
    int getDmg() {
        return dmg_;
    }
    
private:
    int dmg_;
};

#endif
