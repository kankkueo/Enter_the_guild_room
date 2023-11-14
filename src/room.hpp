#include <list>
#include <string>
#include <SDL2/SDL.h>
//#include "monster.hpp"


class Room {
public:
    Room(std::string name, int width, int height, SDL_Texture *texture);

    
    std::string name_;
    SDL_Texture *texture_;
    int width_;
    int height_;
    //std::list<Monster> monsters_;


};