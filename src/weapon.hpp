#ifndef WEAPON
#define WEAPON

#include "item.hpp"
#include <SDL2/SDL_render.h>
#include <string>

class Weapon: public Item {

public:
    Weapon(std::string name, int size, int dmg, int pspeed, int firerate) 
    : Item(name, size) {
            dmg_ = dmg;
            projectile_speed_ = pspeed;
            firerate_ = firerate;
        }
    int getDmg() {
        return dmg_;
    }

    int getProjectileSpeed() {
        return projectile_speed_;
    }

    SDL_Texture* texture_;
    SDL_Texture* projectile_texture_;
    
private:
    int dmg_;
    int projectile_speed_;
    int firerate_;
};

#endif
