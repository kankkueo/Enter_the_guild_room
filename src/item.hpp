#ifndef ITEM
#define ITEM

#include <SDL2/SDL.h>
#include <string>

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
