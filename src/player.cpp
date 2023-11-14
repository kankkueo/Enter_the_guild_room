#ifndef PLAYER
#define PLAYER

#include "player.hpp"

Player::Player(const std::string& name, int x, int y): 
Entity(x, y, 20, 20) {
    name_ = name;
    alive_ = true;
    hp_ = 100;
    dmg_ = 10;
    xp_ = 0;
    max_speed_ = 5;
    inventory_ = std::list<std::string>();
}

const std::string Player::GetName() const {
    return name_;
}

int Player::GetHP() {
    return hp_;
}

int Player::GetXP() {
    return xp_;
}

int Player::GetDMG() {
    return dmg_;
}

int Player::GetMaxSpeed() {
    return max_speed_;
}

void Player::TakeDMG(int value) {
    if (hp_ - value <= 0) {
        hp_ -= value;
        alive_ = false;
    } else {
        hp_ -= value;
    }
}

void Player::Heal(int value) {
    if (hp_ + value >= 100) {
        hp_ = 100;
    } else {
        hp_ += value;
    }
}

void Player::UpdateXP(int value) {
    xp_ += value;
}

void Player::UpdateDMG(int value) {
    dmg_  += value;
}

void Player::setMove(InputState s) {

    if (s.up && s.right) {
        direction_ = 0.7853982;
    }
    else if (s.up && s.left) {
        direction_ = 2.3561945;
    }
    else if (s.down && s.right) {
        direction_ = 5.4977871;
    }
    else if (s.down && s.left) {
        direction_ = 3.9269908;
    }
    else if (s.up) {
        direction_ = 1.5707963;
    }
    else if (s.down) {
        direction_ = 4.7123890;
    }
    else if (s.left) {
        direction_ = 3.1415927;
    }
    else if (s.right) {
        direction_ = 0;
    }
    else {
        speed_ = 0;
        return;
    }

    speed_ = GetMaxSpeed();
    move();
}

#endif
