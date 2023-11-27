#include "monster.hpp"
#include <iostream>

/*
 *  Methods common for all monsters
 */

Monster::Monster(int hp, int dmg, int max_speed, int x, int y, int size_x, int size_y): 
Entity(x, y, size_x, size_y) {
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

void Monster::action(Player&) {}

/*
 *  Melee mob
 */

MeleeMob::MeleeMob(int hp, int dmg, int max_speed, int x, int y, int size_x, int size_y): 
Monster(hp, dmg, max_speed, x, y, size_x, size_y) {}


void MeleeMob::setMove(Player& p) {
    Coordinate pc = p.center();
    float x_diff = pc.x - x_;
    float y_diff = pc.y - y_;
    if (x_diff > 0) {
        direction_ = atan(-y_diff/x_diff);
    }
    else if (x_diff < 0) {
        direction_ = atan(-y_diff/x_diff) + 3.1415927;
    }

    float random_modifier = (float)(rand() % 1000 - 500) / 1200 ;
    direction_ += random_modifier;

    speed_ = max_speed_; 
}

void MeleeMob::action(Player& p) {}

/*
 *  Ranged mob
 */

RangedMob::RangedMob(int hp, int dmg, int max_speed, int x, int y, int size_x, int size_y): 
Monster(hp, dmg, max_speed, x, y, size_x, size_y) {}

void RangedMob::setMove(Player& p) {
    Coordinate pc = p.center();
    float x_diff = pc.x - x_;
    float y_diff = pc.y - y_;
    if (x_diff > 0) {
        direction_ = atan(-y_diff/x_diff) + 3.1415927;
    }
    else if (x_diff < 0) {
        direction_ = atan(-y_diff/x_diff);
    }

    float random_modifier = (float)(rand() % 1000 - 500) / 1200 ;
    direction_ += random_modifier;

    speed_ = max_speed_;
}

void RangedMob::action(Player& p) {}

