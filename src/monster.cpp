#include "monster.hpp"
#include "renderer.hpp"
#include "weapon.hpp"
#include "consumables.hpp"
#include <iostream>

#define death_sound_amount 2
#define attack_sound_amount 2
#define taunt_sound_amount 2
#define hit_sound_amount 2

std::string death_sounds[death_sound_amount] = {
    "./assets/sounds/oyoyoy.wav",
    "./assets/sounds/hammasratas.wav"
};

std::string attack_sounds[attack_sound_amount] = {
    "",
    ""
};

std::string taunt_sounds[taunt_sound_amount] = {
    "./assets/sounds/yykaakone.wav",
    "./assets/sounds/hammasratas.wav"
};

std::string hit_sounds[hit_sound_amount] = {
    "",
    ""
};

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

    sounds_.attack_ = NULL;
    sounds_.hit_ = NULL;
    sounds_.death_ = NULL;
    sounds_.taunt_ = NULL;
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

Mix_Chunk* Monster::getAttackSound() {
    return sounds_.attack_;
}

bool Monster::isAlive() {
    return alive_;
}

void Monster::setMove(Player&) {}

bool Monster::attack(Player&, std::list<Projectile>&) {
    return false;
}

void Monster::dropWeapon(std::list<Weapon*>&) {}

void Monster::dropPotion(std::list<HealingPotion*>&) {}

/*
 *  Melee mob
 */

MeleeMob::MeleeMob(int level, int x, int y, int size_x, int size_y, HealingPotion* potion): 
Monster("Melee chump", 50 + 15*level*level, 100 + 10*level*level, 
    5 + 0.5*level, x, y, size_x, size_y) {
    attack_cooldown_ = 60 + rand() % 300;
    attack_ticks_ = 0;
    potion_ = potion;
}

void MeleeMob::dropPotion(std::list<HealingPotion*>& potions) {
    potion_->x_ = x_;
    potion_->y_ = y_;
    potions.push_back(potion_);
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

bool MeleeMob::attack(Player& p, std::list<Projectile>&) {
    Coordinate pc = p.center();
    float x_diff = pc.x - x_;
    float y_diff = pc.y - y_;

    if (attack_ticks_ <= 0 && x_diff * x_diff + y_diff * y_diff <= 150 * 150) {
        p.TakeDMG(dmg_);
        attack_ticks_ = attack_cooldown_;
        
        return true;
    }
    else {
        attack_ticks_--;
        return false;
    }
}


/*
 *  Ranged mob
 */

RangedMob::RangedMob(int level, int x, int y, int size_x, int size_y, Weapon* weapon): 
Monster("Gun guy", 20 + 3*level*level, level*level, 
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

bool RangedMob::attack(Player& p, std::list<Projectile>& projectiles) {
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

        return true;

    }
    else {
        attack_ticks_--;
        return false;
    }
}

void RangedMob::dropWeapon(std::list<Weapon*>& weapons) {
    weapon_->x_ = x_;
    weapon_->y_ = y_;
    weapons.push_back(weapon_);
}

Mix_Chunk* RangedMob::getAttackSound() {
    return weapon_->sound_;
}

/*
 *  Final boss
 */

Boss::Boss(int level):
Monster("Final boss", 300 + 300 * level * level, 5 * level * level, 12, 500, 500, 200, 200) {
    optimal_distance_ = 600;
    attack_ticks_ = 0;
    attack_cooldown_ = 70;
    attack_pattern_ = 0;
}

bool Boss::attack(Player& p, std::list<Projectile>& projectiles) {
    Coordinate pc = p.center();
    float x_diff = pc.x - x_;
    float y_diff = pc.y - y_;


    if (attack_pattern_ == 0) {
        if (attack_ticks_ <= 0 && x_diff * x_diff + y_diff * y_diff <= 150 * 150) {
            p.TakeDMG(dmg_);
            attack_ticks_ = attack_cooldown_;
            return true;
        }
    }
    else if (attack_pattern_ == 1) {
        if (attack_ticks_ <= 0) {
            attack_ticks_ = 60 / weapon_->getFirerate();
            float d;

            if (x_diff > 0) {
                d = atan(-y_diff/x_diff);
            }
            else if (x_diff < 0) {
                d = atan(-y_diff/x_diff) + 3.1415927;
            }

            weapon_->shoot(projectiles, *this, dmg_, d, false);

            return true;
        }
    }

    attack_ticks_--;
    return false;
}

Mix_Chunk* Boss::getAttackSound() {
    if (attack_pattern_ == 0) {
        return sounds_.attack_;
    }
    else {
        return weapon_->sound_;
    }
}

void Boss::setMove(Player& p) {
    Coordinate pc = p.center();
    float x_diff = pc.x - x_;
    float y_diff = pc.y - y_;

    if (rand() % 500 == 1) {
        if (attack_pattern_ == 0) {
            attack_pattern_ = 1;
        }
        else {
            attack_pattern_ = 0;
        }
    }

    if (attack_pattern_ == 0) {
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
    }
    else if (attack_pattern_== 1) {
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
    }

    speed_ = max_speed_;
}

/*
 *  Non-member functions
 */

Monster* genRandomMob(Renderer& r, int level, int room_width, int room_height) {

    int x = rand() % (room_width - 150) + 150;
    int y = rand() % (room_height - 150) + 150;

    int type = rand() % 2;

    Monster* m = NULL;

    switch (type) {
        case MeleeMobType: {
            HealingPotion* h = genPotion(r, level);
            m = new MeleeMob(level, x, y, 60, 90, h);
            m->texture_ = r.loadTexture("./assets/Koneteekkari.png");
            m->sounds_.death_ = r.loadSound("");

            std::cout << "Generated melee mob " << m->getName() << " with: dmg =" << m->GetDMG();
            std::cout << ", attack cooldown = " << ((MeleeMob*)m)->attack_cooldown_ << std::endl;

            break;
        }
        case RangedMobType: {
            Weapon* w = genRandomWeapon(r, level);
            m = new RangedMob(level, x, y, 60, 90, w);
            m->texture_ = r.loadTexture("./assets/Koneteekkari.png"); // Different textures for mob types??
                                                                      
            std::cout << "Generated ranged mob " << m->getName() << " with: dmg =" << m->GetDMG() << std::endl;
                                                                     
            break;
        }
        default:
            break;
    }

    m->sounds_.attack_ = r.loadSound((attack_sounds[rand() % attack_sound_amount]).c_str());
    m->sounds_.death_ = r.loadSound((death_sounds[rand() % death_sound_amount]).c_str());
    m->sounds_.taunt_ = r.loadSound((taunt_sounds[rand() % taunt_sound_amount]).c_str());
    m->sounds_.hit_ = r.loadSound((hit_sounds[rand() % hit_sound_amount]).c_str());

    return m;
}

