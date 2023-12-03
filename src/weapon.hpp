#ifndef WEAPON
#define WEAPON

#include "item.hpp"
#include "entity.hpp"
#include "renderer.hpp"
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
    Weapon(const std::string& name, int size, int dmg, int pspeed, int firerate);
    int getDmg();
    int getProjectileSpeed();
    int getFirerate();
    std::string getName();

    virtual void shoot(std::list<Projectile>& projectiles, Entity source, int dmg, float direction, bool damage_monsters);
    virtual std::string toString();

    SDL_Texture* texture_;
    SDL_Texture* projectile_texture_;
    
protected:
    int dmg_;
    int projectile_speed_;
    int firerate_;  // Rounds per second
    int projectile_size_x_ = 10;
    int projectile_size_y_ = 10;
    std::string name_;
};


class Pistol: public Weapon {
public:
    Pistol(const std::string& name, int size, int dmg, int pspeed, int firerate);

};

class SMG: public Weapon {
public:
    SMG(const std::string& name, int size, int dmg, int pspeed, int firerate);

};

class Shotgun: public Weapon {
public:
    Shotgun(const std::string& name, int size, int dmg, int pspeed, int firerate, int pellets, float spread);
    void shoot(std::list<Projectile>& projectiles, Entity source, int dmg, float direction, bool damage_monsters);
    int getPellets();
    float getSpread();
    std::string toString();

private:
    int pellets_;
    float spread_;

};

enum GunType {
    PistolType,
    SMGType,
    ShotgunType
};

Weapon* genRandomWeapon(Renderer&, int);

#endif
