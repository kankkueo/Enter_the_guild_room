#include <SDL2/SDL.h>
#include <string>

class Item {

public:
    Item(std::string name, int size) {
        name_ = name;
        size_ = size;
    }

    void equip() {
        equipped_ = true;
    }
    int getSize() {
        return size_;
    }
    
    SDL_Texture *texture_; 

private:
    std::string name_;
    bool equipped_;
    int size_;

};
