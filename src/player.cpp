
#include "player.hpp"

Player::Player(const std::string& name, int x, int y): 
//Entity(x, y, 128, 128), weapon_(new Shotgun("Starter weapon", 10, 10, 30, 5, 10, 0.5)) {
Entity(x, y, 128, 128), weapon_(NULL) {
    name_ = name;
    alive_ = true;
    hp_ = 200;
    dmg_ = 10;
    xp_ = 0;
    max_speed_ = 15;
    inventory_ = std::list<std::string>();
    level_ = 0;
    xp_to_Level_up_ = 100;
    shoot_ticks_ = 0;
}

void Player::equipWeapon(Weapon* w) {
    weapon_ = w;
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

int Player::GetLevel() {
    return level_;
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
}

void Player::setAttack(InputState s) {

    if (s.attackUp && s.attackRight) {
        attack_direction_ = 0.7853982;
    }
    else if (s.attackUp && s.attackLeft) {
        attack_direction_ = 2.3561945;
    }
    else if (s.attackDown && s.attackRight) {
        attack_direction_ = 5.4977871;
    }
    else if (s.attackDown && s.attackLeft) {
        attack_direction_ = 3.9269908;
    }
    else if (s.attackUp) {
        attack_direction_ = 1.5707963;
    }
    else if (s.attackDown) {
        attack_direction_ = 4.7123890;
    }
    else if (s.attackLeft) {
        attack_direction_ = 3.1415927;
    }
    else if (s.attackRight) {
        attack_direction_ = 0;
    }
    else {
        return;
    }
}

float Player::getAttackDirection() {
    return attack_direction_;
}

void Player::gainXP(int amount) {
    xp_ += amount;
    if (xp_ >= xp_to_Level_up_) {
        level_++;
        xp_ -= xp_to_Level_up_;
        dmg_ += level_ * 0.1 * 10;
        hp_ += level_ * 0.1 * 100;
        xp_to_Level_up_ += level_ * 0.1 * 100;
    }
}

bool Player::isAlive() {
    return alive_;
}
