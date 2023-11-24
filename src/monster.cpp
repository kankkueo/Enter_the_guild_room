#include "monster.hpp"
#include <iostream>

Monster::Monster(int hp, int dmg, int max_speed, int x, int y, int size_x, int size_y): 
Entity(x, y, size_x, size_y) {
    alive_ = true;
    hp_ = hp;
    dmg_ = dmg;
    max_speed_ = max_speed;
}


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

/*
MeleeMob::MeleeMob(int hp, int dmg, int max_speed, int x, int y, int size_x, int size_y): 
Monster(hp, dmg, max_speed, x, y, size_x, size_y) {}
*/

void Monster::setMove(Player& p) {
    Coordinate pc = p.center();
    float x_diff = pc.x - x_;
    float y_diff = pc.y - y_;
    if (x_diff > 0) {
        direction_ = atan(-y_diff/x_diff);
    }
    else if (x_diff < 0) {
        direction_ = atan(-y_diff/x_diff) + 3.1415927;
    }

    speed_ = max_speed_; 
}

