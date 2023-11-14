#include "monster.hpp"

Monster::Monster(int hp, int dmg)
    : hp_(hp), dmg_(dmg), alive_(true) { }

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