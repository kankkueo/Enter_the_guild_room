#ifndef ITEM
#define ITEM

#include <SDL2/SDL.h>
#include <string>

/*!
 * Base class for all types of items found in the game
 *
 * Inherited by Weapon and HealingPotion classes
 */
class Item {

public:
    Item(std::string name, int size) {
        name_ = name;
        size_ = size;
        x_ = 0;
        y_ = 0;
    }

    void equip() {
        equipped_ = true;
    }
    int getSize() {
        return size_;
    }
    std::string getName() {
        return name_;
    }
    
    SDL_Texture *texture_; 

    // For world location
    int x_;
    int y_;

private:
    std::string name_;
    bool equipped_;
    int size_;

};

#endif
