#include "player.hpp"

Player::Player(const std::string& name)
    : name_(name), alive_(true), hp_(100), dmg_(10), xp_(0), inventory_() { }

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