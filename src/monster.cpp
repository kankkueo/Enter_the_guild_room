#include "monster.hpp"
#include "renderer.hpp"
#include "weapon.hpp"
#include <iostream>

/*
 *  Methods common for all monsters
 */

Monster::Monster(const std::string& name, int hp, int dmg, int max_speed, int x, int y, int size_x, int size_y): 
Entity(x, y, size_x, size_y) {
    name_ = name;
    alive_ = true;
    hp_ = hp;
    dmg_ = dmg;
    max_speed_ = max_speed;
}

Monster::~Monster() {}

int Monster::GetHP() {
    return hp_;
}

int Monster::GetDMG() {
    return dmg_;
}

std::string Monster::getName() {
    return name_;
}

void Monster::TakeDMG(int value) {
    if (hp_ - value <= 0) {
        hp_ -= value;
        alive_ = false;
    } else {
        hp_ -= value;
    }
}

bool Monster::isAlive() {
    return alive_;
}

void Monster::setMove(Player&) {}

void Monster::attack(Player&, std::list<Projectile>&) {}

/*
 *  Melee mob
 */

MeleeMob::MeleeMob(int level, int x, int y, int size_x, int size_y): 
Monster("Melee chump", 20 + 0.2*level*level, 10 + 0.4*level*level, 
    5 + 0.1*level, x, y, size_x, size_y) {
    attack_cooldown_ = 60 + rand() % 540;
    attack_ticks_ = 0;
}

void MeleeMob::setMove(Player& p) {
    Coordinate pc = p.center();
    float x_diff = pc.x - x_;
    float y_diff = pc.y - y_;


    if (x_diff * x_diff + y_diff * y_diff > p.size_x_ * p.size_x_) {
        if (x_diff > 0) {
            direction_ = atan(-y_diff/x_diff);
        }
        else if (x_diff < 0) {
            direction_ = atan(-y_diff/x_diff) + 3.1415927;
        }
    }
    else {
        if (x_diff > 0) {
            direction_ = atan(-y_diff/x_diff) + 3.1415927;
        }
        else if (x_diff < 0) {
            direction_ = atan(-y_diff/x_diff);
        }
    }

    float random_modifier = (float)(rand() % 1000 - 500) / 1200 ;
    direction_ += random_modifier;

    speed_ = max_speed_; 
}

void MeleeMob::attack(Player& p, std::list<Projectile>&) {
    Coordinate pc = p.center();
    float x_diff = pc.x - x_;
    float y_diff = pc.y - y_;

    if (attack_ticks_ <= 0 && x_diff * x_diff + y_diff * y_diff <= p.size_x_ * p.size_x_ + 20) {
        p.TakeDMG(dmg_);
        attack_ticks_ = attack_cooldown_;
    }
    else {
        attack_ticks_--;
    }
}

/*
 *  Ranged mob
 */

RangedMob::RangedMob(int level, int x, int y, int size_x, int size_y, Weapon* weapon): 
Monster("Gun guy", 10 + 0.14*level*level, 0.1*level*level, 
    3 + 0.1*level, x, y, size_x, size_y), weapon_(weapon) {
    optimal_distance_ = 300 + rand() % 500;
}

void RangedMob::setMove(Player& p) {
    Coordinate pc = p.center();
    float x_diff = pc.x - x_;
    float y_diff = pc.y - y_;

    if (x_diff * x_diff + y_diff * y_diff < optimal_distance_ * optimal_distance_) {
        if (x_diff > 0) {
            direction_ = atan(-y_diff/x_diff) + 3.1415927;
        }
        else if (x_diff < 0) {
            direction_ = atan(-y_diff/x_diff);
        }
    }
    else {
        if (x_diff > 0) {
            direction_ = atan(-y_diff/x_diff);
        }
        else if (x_diff < 0) {
            direction_ = atan(-y_diff/x_diff) + 3.1415927;
        }
    }

    float random_modifier = (float)(rand() % 1000 - 500) / 1200 ;
    direction_ += random_modifier;

    speed_ = max_speed_;
}

void RangedMob::attack(Player& p, std::list<Projectile>& projectiles) {
    if (attack_ticks_ <= 0) {
        attack_ticks_ = 60 / weapon_->getFirerate();
        float d;

        Coordinate pc = p.center();
        float x_diff = pc.x - x_;
        float y_diff = pc.y - y_;
        if (x_diff > 0) {
            d = atan(-y_diff/x_diff);
        }
        else if (x_diff < 0) {
            d = atan(-y_diff/x_diff) + 3.1415927;
        }

        weapon_->shoot(projectiles, *this, dmg_, d, false);
    }
    else {
        attack_ticks_--;
    }
}

/*
 *  Non-member functions
 */

Monster* genRandomMob(Renderer& r, int level, int room_width, int room_height) {

    int x = rand() % (room_width - 80) + 80;
    int y = rand() % (room_height - 80) + 80;

    int type = rand() % 2;

    Monster* m = NULL;

    switch (type) {
        case MeleeMobType: {
            m = new MeleeMob(level, x, y, 60, 90);
            m->texture_ = r.loadTexture("./assets/Koneteekkari.png");

            std::cout << "Generated melee mob " << m->getName() << " with: dmg =" << m->GetDMG();
            std::cout << ", attack cooldown = " << ((MeleeMob*)m)->attack_cooldown_ << std::endl;

            break;
        }
        case RangedMobType: {
            Weapon* w = genRandomWeapon(r, level);
            m = new RangedMob(level, x, y, 60, 90, w);
            m->texture_ = r.loadTexture("./assets/Koneteekkari.png"); // Different textures for mob types??
                                                                      
            std::cout << "Generated melee mob " << m->getName() << " with: dmg =" << m->GetDMG() << std::endl;
                                                                     
            break;
        }
        default:
            break;
    }

    return m;
}

