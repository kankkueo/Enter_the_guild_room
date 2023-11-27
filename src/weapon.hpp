#ifndef WEAPON
#define WEAPON

#include "item.hpp"
#include "entity.hpp"
#include <list>
#include <SDL2/SDL_render.h>
#include <string>

class Projectile: public Entity {
public:
    Projectile(int x, int y, int size_x, int size_y, int dmg, float direction, int speed):
    Entity(x, y, size_x, size_y) {
        dmg_ = dmg;
        direction_ = direction;
        speed_ = speed;
    }

    int dmg_;
};

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

    int getFirerate() {
        return firerate_;
    }

    void shoot(std::list<Entity>& projectiles, Entity source, int dmg, float direction) {
        Coordinate c = source.center();
        Projectile p = Projectile(c.x, c.y, projectile_size_x_, projectile_size_y_,
            dmg_ + dmg, direction, projectile_speed_);

        p.texture_ = projectile_texture_;

        projectiles.push_back(p);
    }

    SDL_Texture* texture_;
    SDL_Texture* projectile_texture_;
    
private:
    int dmg_;
    int projectile_speed_;
    int firerate_;  // Rounds per second
    int projectile_size_x_ = 10;
    int projectile_size_y_ = 10;
};

#endif
