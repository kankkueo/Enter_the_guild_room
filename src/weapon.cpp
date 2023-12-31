
#include <iostream>
#include "weapon.hpp"

#define prefix_amount 10
#define pistol_name_amount 3
#define shotgun_name_amount 3
#define smg_name_amount 3

std::string prefixes[prefix_amount] = {
    "explosive", "hot", "shitty", "poor", "super", "minty", "long", "hairy", "floppy", "slippery"
};

std::string pistol_names[pistol_name_amount] = {
    "pistol","squirter", "handgun"
};

std::string shotgun_names[shotgun_name_amount] = {
    "shotgun", "diarrhea", "jackhammer"
};

std::string smg_names[smg_name_amount] = {
    "smg", "serial killer", "nailgun"
};


/*
 *  Common methods
 */

std::string Weapon::toString(){
    return name_ + "\nDamage: " + std::to_string(dmg_) + "\nFirerate: " + std::to_string(firerate_);
}

Weapon::Weapon(const std::string& name, int size, int dmg, int pspeed, int firerate): 
    Item(name, size) {
        dmg_ = dmg;
        projectile_speed_ = pspeed;
        firerate_ = firerate;
        name_ = name;
    }

int Weapon::getDmg() {
    return dmg_;
}

int Weapon::getProjectileSpeed() {
    return projectile_speed_;
}

int Weapon::getFirerate() {
    return firerate_;
}

std::string Weapon::getName() {
    return name_;
}

void Weapon::shoot(std::list<Projectile>& projectiles, Entity source, int dmg, float direction, bool damage_monsters) {
    Coordinate c = source.center();
    Projectile p = Projectile(c.x, c.y, projectile_size_x_, projectile_size_y_,
        dmg_ + dmg, direction, projectile_speed_);

    p.damage_monsters_ = damage_monsters;
    p.texture_ = projectile_texture_;

    projectiles.push_back(p);
}

/*
 *  Pistol
 */

Pistol::Pistol(const std::string& name, int size, int dmg, int pspeed, int firerate):
    Weapon(name, size, dmg, pspeed, firerate) {}

/*
 *  Shotgun
 */

int Shotgun::getPellets() {
    return pellets_;
}

float Shotgun::getSpread() {
    return spread_;
}

Shotgun::Shotgun(const std::string& name, int size, int dmg, int pspeed, int firerate, int pellets, float spread):
    Weapon(name, size, dmg, pspeed, firerate) {
        pellets_ = pellets;
        spread_ = spread;
    }

void Shotgun::shoot(std::list<Projectile>& projectiles, Entity source, int dmg, float direction, bool damage_monsters) {
    Coordinate c = source.center();
    float d_step = spread_ / pellets_;
    float d = direction - ((float) pellets_ / 2) * d_step;

    for (int i = 0; i < pellets_; i++) {
        Projectile p = Projectile(c.x, c.y, projectile_size_x_, projectile_size_y_,
            ceil(dmg_ + dmg / pellets_), d, projectile_speed_);

        p.damage_monsters_ = damage_monsters;
        p.texture_ = projectile_texture_;
        projectiles.push_back(p);

        d += d_step;
    }
}

std::string Shotgun::toString(){
    return name_ + "\nDamage: " + std::to_string(dmg_) + " x " + std::to_string(pellets_) +
        "\nFirerate: " + std::to_string(firerate_);
}

/*
 *  Non member functions
 */

float randomFloat(float from, float to) {
    float diff = to - from;
    float rf = (float)(rand() % 10000) / 10000;
    std::cout << rf * diff << std::endl;
    return from + rf * diff;
}

Weapon* genRandomWeapon(Renderer& r, int level) {

    int type = rand() % 3;

    Weapon* w = NULL;

    switch (type) {
        case PistolType: {
            int dmg = 6 + ceil(6*level*level * randomFloat(0.5, 1.8));
            int firerate = 1 + rand() % 5;
            int pspeed = ceil(0.05 * level + 15 * randomFloat(0.7, 1.4));
            std::string name = prefixes[rand() % prefix_amount] + " " +
                pistol_names[rand() % pistol_name_amount];

            w = new Pistol(name, 10, dmg, pspeed, firerate);
            w->texture_ = r.loadTexture("./assets/items/pistol.png");
            w->projectile_texture_ = r.loadTexture("./assets/entities/bulet1.png");
            w->sound_ = r.loadSound("./assets/sounds/testi.mp3");

            std::cout << "Generated pistol " << w-> getName() << " with: dmg =" << w->getDmg();
            std::cout << ", firerate = " << w->getFirerate();
            std::cout << ", projectile speed = " << w->getProjectileSpeed() << std::endl;

            break;
        }
        case SMGType: {
            int dmg = 2 + ceil(2*level*level * randomFloat(0.5, 1.8));
            int firerate = 6 + rand() % 10;
            int pspeed = ceil(0.05 * level + 15 * randomFloat(0.7, 1.4));
            std::string name = prefixes[rand() % prefix_amount] + " " +
                smg_names[rand() % smg_name_amount];

            w = new Pistol(name, 10, dmg, pspeed, firerate);
            w->texture_ = r.loadTexture("./assets/items/smg.png");
            w->projectile_texture_ = r.loadTexture("./assets/entities/bulet1.png");
            w->sound_ = r.loadSound("./assets/sounds/testi.mp3");

            std::cout << "Generated SMG " << w-> getName() << " with: dmg =" << w->getDmg();
            std::cout << ", firerate = " << w->getFirerate();
            std::cout << ", projectile speed = " << w->getProjectileSpeed() << std::endl;

            break;
        }
        case ShotgunType: {
            int dmg = 2 + ceil(1*level*level * randomFloat(0.6, 1.3));
            int firerate = 1 + rand() % 3;
            int pspeed = ceil(0.05 * level + 12 * randomFloat(0.7, 1.5));
            int pellets = 3 + rand() % 10;
            float spread = randomFloat(0.1, 0.5);
            std::string name = prefixes[rand() % prefix_amount] + " " +
                shotgun_names[rand() % shotgun_name_amount];

            w = new Shotgun(name, 10, dmg, pspeed, firerate, pellets, spread);
            w->texture_ = r.loadTexture("./assets/items/shotgun.png");
            w->projectile_texture_ = r.loadTexture("./assets/entities/bulet1.png");
            w->sound_ = r.loadSound("./assets/sounds/shotgun.wav");

            std::cout << "Generated shotgun " << w->getName() << " with: dmg =" << w->getDmg();
            std::cout << ", firerate = " << w->getFirerate();
            std::cout << ", projectile speed = " << w->getProjectileSpeed();
            std::cout << ", spread = " << ((Shotgun*)w)->getSpread();
            std::cout << ", pellets = " << ((Shotgun*)w)->getPellets() << std::endl;

            break;
        }

        default:
            break;
    }

    return w;
}

