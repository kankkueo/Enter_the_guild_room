#include <math.h>
#include <iostream>
#include "game.hpp"

Entity::Entity() {
    x_ = 0;
    y_ = 0;
    speed_ = 10;
    direction_ = 0;
}

void Entity::move() {
    x_ += cos(direction_) * speed_;
    y_ -= sin(direction_) * speed_;
}

