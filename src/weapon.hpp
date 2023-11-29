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
    bool damage_monsters_;
};

class Weapon: public Item {

public:
    Weapon(std::string name, int size, int dmg, int pspeed, int firerate): 
    Item(name, size) {
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

    virtual void shoot(std::list<Projectile>& projectiles, Entity source, int dmg, float direction, bool damage_monsters) {
        Coordinate c = source.center();
        Projectile p = Projectile(c.x, c.y, projectile_size_x_, projectile_size_y_,
            dmg_ + dmg, direction, projectile_speed_);

        p.damage_monsters_ = damage_monsters;
        p.texture_ = projectile_texture_;

        projectiles.push_back(p);
    }

    SDL_Texture* texture_;
    SDL_Texture* projectile_texture_;
    
protected:
    int dmg_;
    int projectile_speed_;
    int firerate_;  // Rounds per second
    int projectile_size_x_ = 10;
    int projectile_size_y_ = 10;
};


class Pistol: public Weapon {
public:
    Pistol(std::string name, int size, int dmg, int pspeed, int firerate):
    Weapon(name, size, dmg, pspeed, firerate) {}

};

class Shotgun: public Weapon {
public:
    Shotgun(std::string name, int size, int dmg, int pspeed, int firerate, int pellets, float spread):
    Weapon(name, size, dmg, pspeed, firerate) {
        pellets_ = pellets;
        spread_ = spread;
    }

    void shoot(std::list<Projectile>& projectiles, Entity source, int dmg, float direction, bool damage_monsters) {
        Coordinate c = source.center();
        float d_step = spread_ / pellets_;
        float d = direction - ((float) pellets_ / 2) * d_step;

        for (int i = 0; i < pellets_; i++) {
            Projectile p = Projectile(c.x, c.y, projectile_size_x_, projectile_size_y_,
                dmg_ + dmg, d, projectile_speed_);

            p.damage_monsters_ = damage_monsters;
            p.texture_ = projectile_texture_;
            projectiles.push_back(p);

            d += d_step;
        }
    }

private:
    int pellets_;
    float spread_;

};

#endif
